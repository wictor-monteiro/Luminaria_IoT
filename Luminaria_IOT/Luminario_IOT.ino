//Definições para uso de rede e suporte ao BLynk
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLQsEyyFs4"
#define BLYNK_AUTH_TOKEN "ylcDwlv-qp4y-82O4mveiPluEQZo9wjw"
//Bibliotecas usadas para o controle 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
//Definiçẽos de pino do LED, sensores e buzzer
#define COMMON_ANODE
int redPin = D5;     
int greenPin = D2;   
int bluePin = D1; 
int sensorPIR = D8;
int buzzer = D7;
//Variaveis para ajudar nas manipulações de funções
int r;
int g;
int b;
int greenValue;
int redValue;
int blueValue;
float h;
float t;
float hif; 
//Variaveis para os botões virtuais do Blynk
int Seguranca;
bool tempColor;
int botaoLampada;
//Configurações do Blynk
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "o m e n";
char pass[] = "Belamentira45";
//Configurações do sensor de temperatura DHT11
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timerDHT11; // Criação do Timer do DHT11
BlynkTimer timerMovimento; //Timer para controle do LED 
//Envio de dados dos sensores
void sendSensor(){
  bool state = digitalRead(sensorPIR);
  if (Seguranca == 1){
    Serial.println("Sistema de segurança ligado!");  
    if (state == HIGH){
    Blynk.logEvent("movimento");
    tone(buzzer,1800);
   }else
    if(state == 0){
     noTone(buzzer);
    }
  }
  if(Seguranca == 0){
        Serial.println("Sistema de segurança desligado!");
        noTone(buzzer);
    }
   Serial.print("Valor do sensor: ");
   Serial.println(state);
   h = dht.readHumidity(); //Realiza a leitura da umidade e armazena na variável h
   t = dht.readTemperature(); //Realiza a leitura da temperatura e armazena na variável t
   hif = dht.computeHeatIndex(t, h); //Utiliza os parametros de temperatura e umidade do sensor para criar dados de sensação do ambiente
   Serial.print("Temperatura: ");
   Serial.print(t);
   Serial.print(" *C");
   Serial.print(" Sensacação termica: ");
   Serial.print(hif);
   Serial.print(" Umidade: ");
   Serial.print(h);
   Serial.println(" %t");
  if (isnan(h) || isnan(t)) { //Verifica se houve falha na leitura do sensor
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h); //Escreve no pino virtual V5 o valor de h (umidade)
  Blynk.virtualWrite(V6, t); //Escreve no pino virtual v6 o valor de t (temperatura)
  Blynk.virtualWrite(V7,sensorPIR);//Escreve no pino virtual V7 o valor do sensor PIR(quando há movimento)
  Blynk.virtualWrite(V8, hif); //Escreve no pino virtual V8 o valor de sensação termica do ambiente entre h e t 
}
void setup()
{ 
   Serial.begin(9600);
   pinMode(sensorPIR,INPUT);
   Blynk.begin(auth, ssid, pass);
   dht.begin();
   timerDHT11.setInterval(1000l,sendSensor);
   timerMovimento.setInterval(100l,MovimentoPIR);
}
void loop(){
   Blynk.run();//Acionando o Blynk
   timerDHT11.run(); // Inicializa o Timer do DHT11
   timerMovimento.run(); //Inicio do Timer para controle do LED
}
void rgb (int r,int g,int b){    
  analogWrite(redPin, r);   
  analogWrite(bluePin, b); 
  analogWrite(greenPin, g); 
}
void MovimentoPIR(){
  if(tempColor == 1){
    if(dht.readTemperature()<= 10){
      rgb(235,255,198);
      delay(10);
    }
    if(dht.readTemperature()>10 && dht.readTemperature()<=25){
        rgb(255,255,0);
        delay(10);
    }
    if(dht.readTemperature()>25 && dht.readTemperature()<=30){
        rgb(255,0,255);
        delay(10);
    }
    if(dht.readTemperature()>30 && dht.readTemperature()<=40){
        rgb(66,125,0);
        delay(10);
     }
     if(dht.readTemperature()>45){
        rgb(0,255,255);
        delay(10);
      }
   }
  if(tempColor == 0){
     rgb(255,255,255);
   }
  if(botaoLampada == 1){
    rgb(91,143,255);
   }
   if(botaoLampada == 0){
     rgb(255,255,255);
     delay(10);
   }
   if(blueValue>1){
    analogWrite(bluePin, blueValue); 
   }
   if(greenValue>1){
    analogWrite(greenPin, greenValue); 
   }
   if(redValue>1){
    analogWrite(redPin, redValue);
   } 
}
BLYNK_WRITE(V9){//Botão para o controle de segurança
  Seguranca = param.asInt();
}
BLYNK_WRITE(V0) {//Botão para o modo de cor pela temperatura do sensor 
  tempColor = param.asInt();
}
BLYNK_WRITE(V1){//Botão de nível individual do LED vermelho
   redValue= param.asInt();  
}

BLYNK_WRITE(V2){//Botão de nível individual do LED verde
   greenValue = param.asInt();
}

BLYNK_WRITE(V3){//Botão de nível individual do LED azul
   blueValue = param.asInt();    
}
BLYNK_WRITE(V4){//Botão para acionar o modo lampada
   botaoLampada = param.asInt(); 
}
