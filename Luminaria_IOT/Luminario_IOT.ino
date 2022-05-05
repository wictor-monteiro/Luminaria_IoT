//Definições para o uso de rede e suporte ao Blynk
#define BLYNK_TEMPLATE_ID "TMPLQsEyyFs4"
#define BLYNK_AUTH_TOKEN "ylcDwlv-qp4y-82O4mveiPluEQZo9wjw"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
//Definições dos pinos para o LED
int redPin = 14;     
int greenPin = 5;   
int bluePin = 4;   
//Variaveis criadadas para ajudar na criação das funçẽos de efeitos do LED
int botaoFade;             
int ultimoFade = 0;      
int redBrilho = 0;            
int redFade = random(1,15);  
int greenBrilho = 0;          
int greenFade = random(1,15);
int blueBrilho = 0;           
int blueFade = random(1,15);
//Configurações do Blynk
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "o m e n";
char pass[] = "Belamentira45";
//Configuraçẽos do sensor de temperatura DHT11
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer; //Objeto criado para ajudar na transferência de dados em tempo 

void sendSensor(){
  float h = dht.readHumidity(); //Realiza a leitura da umidade e armazena na variável h
  float t = dht.readTemperature(); //Realiza a leitura da temperatura e armazena na variável t

  if (isnan(h) || isnan(t)) { //Verificando se houve falha na leitura do sensor 
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h); //Escreve no pino virtual V5 o valor de h (umidade)
  Blynk.virtualWrite(V6, t); //Escreve no pino virtual v6 o valor de t (temperatura)
}

void setup()
{
   Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);
   timer.setInterval(15,randomFade); //Timer para o efeito fade do LED
   dht.begin(); //Inicia a biblioteca DHT para o sensor DHT11
   timer.setInterval(1000l,sendSensor);
}

void loop()
{
   Blynk.run(); //Acionando o Blynk 
   timer.run();  
}

BLYNK_WRITE(V0) //Botão Fade
{
   botaoFade = param.asInt();
}

void randomFade()  
{
  
   if(botaoFade == 0 && ultimoFade == 1) 
      {
         analogWrite(redPin,0);
         analogWrite(greenPin,0);
         analogWrite(bluePin,0);
         redBrilho = random(0,255);
         greenBrilho = random(0,255);      
         blueBrilho = random(0,255);
         ultimoFade = botaoFade;  
      }

   if(botaoFade == 1){
         analogWrite(redPin, redBrilho);
         redBrilho += redFade;    

         analogWrite(greenPin, greenBrilho);
         greenBrilho += greenFade;

         analogWrite(bluePin, blueBrilho);
         blueBrilho += blueFade;

         if (redBrilho > 255){
               redBrilho -= redFade;
               redFade = random(1,15);
               redFade = -redFade; 
            }

         if (redBrilho <= 0){
               redBrilho -= redFade;
               redFade = random(1,15);  
            }
         if (greenBrilho > 255){
               greenBrilho -= greenFade;
               greenFade = random(1,15);
               greenFade = -greenFade;
            }

         if (greenBrilho <= 0){
               greenBrightness -= greenFade;
               greenFade = random(1,15);  
            }

         if (blueBrilho > 255){
               blueBrilho -= blueFade;
               blueFade = random(1,15);
               blueFade = -blueFade;
            }

         if (blueBrilho <= 0){
               blueBrilho -= blueFade;
               blueFade = random(1,15);  
            }  
         ultimoFade = botaoFade;
      }
}

BLYNK_WRITE(V1){
   int valorRed = param.asInt();  
   analogWrite(redPin, valorRed); 
}

BLYNK_WRITE(V2){
   int valorGreen = param.asInt();   
   analogWrite(greenPin, valorGreen);
}

BLYNK_WRITE(V3){ //Botão de nível individual do LED azul
   int valorBlue = param.asInt();   
   analogWrite(bluePin, valorBlue); 
}

BLYNK_WRITE(V4){ //Botão para controlar a função aleatória do LED 
   int botaoAleatorio = param.asInt();  
   
   int aleatorioRed = random(0,255);    
   int aleatorioGreen = random(0,255);  
   int aleatorioBlue = random(0,255);   
   if (botaoAleatorio == 0){
         analogWrite(redPin,255);
         analogWrite(greenPin,255);
         analogWrite(bluePin,255);
      }

   if (botaoAleatorio == 1){
         analogWrite(redPin,aleatorioRed);
         analogWrite(greenPin,aleatorioGreen);
         analogWrite(bluePin,aleatorioBlue);  
      }
}
