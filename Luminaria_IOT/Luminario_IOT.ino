/*************************************************************
  Download da biblioteca Blynk:
    https://github.com/blynkkk/blynk-library/releases/latest

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
  Blynk library is licensed under MIT license
 *************************************************************
 Guia rápido:

  1. Conecte o seu microcontrolador, e o sensores respeitando os pinos do código
  2. Depois de conectados, ligue o seu microntolado respeitando a tensão de entrada
  3. Envie o código para o seu microcontrolador, só precisa ser realizado uma única vez (Desde que não altere a conexão escolhida)
  4. Agora verifique seu o seu microcontrolador está se conectando normalmente
  5. As próximas configurações são feitas dentro do Blynk

 Dentro Blynk:
  6. Crie um novo projeto;
  7. Com isso o Blynk gera automaticamente o Auth Token, o que você precisa alterar aqui depois;
  8. Adicione 3 botões e 3 botões de valores. Adicione os botões para V0,V4 e V9. Os de valores para V1, V2, e V3;
  9. Despois salve as configurações. É a hora de testar!
 *************************************************************/

//Definições para uso de rede e suporte ao BLynk
#define BLYNK_PRINT Serial //Mostra no serial o estado inicial da conexão com o Blynk
#define BLYNK_TEMPLATE_ID "TMPLQsEyyFs4"
#define BLYNK_AUTH_TOKEN "ylcDwlv-qp4y-82O4mveiPluEQZo9wjw"
//Bibliotecas usadas para o controle 
#include <ESP8266WiFi.h> //Biblioteca para o controle WiFi do NodeMCU
#include <BlynkSimpleEsp8266.h> //Biblioteca para a conexão e funcionalidades do Blynk
#include <DHT.h> //Biblioteca para o sensor de temperatura 
#include <Adafruit_NeoPixel.h> //Biblioteca do LED endereçavel
//Definiçẽos de pino do LED, sensores e buzzer
#define PIN D4 //Define o pino que o anel de LED está conectado 
#define NUMPIXELS 12 //Quantidade de LEDs no anel 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); //Para para o anel as informações de quantidade e pino 
int sensorPIR = D2;
int buzzer = D3;
//Variaveis para ajudar nas manipulações de funções
int r,g,b;
int greenValue,redValue,blueValue;
float umidade,temperatura,sensacao; //Recebe os dados do sensor de temperatura 
//Variaveis para os botões virtuais do Blynk
int Seguranca,CorTemperatura,Lampada;
//Configurações do Blynk
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "o m e n";
char pass[] = "Belamentira45";
//Configurações do sensor de temperatura DHT11
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//Funções de tempo para envio ao Blynk
BlynkTimer timerSensores; // Timer para o sensor DHT11 e o PIR
BlynkTimer timerLED; //Timer para controle do anel de LED 
//Envio de dados dos sensores com timer de conexão
void dadosSensores(){
  //Tratamento do modo de segurança
  bool state = digitalRead(sensorPIR);
  if (Seguranca == 1){
    Serial.println("Sistema de segurança ligado!");  
    if (state == HIGH){
    Blynk.logEvent("movimento"); //Notificação ao usuario, na plataforma Blynk foi configurado para o evento "movimento" uma mensagem.
    tone(buzzer,800);
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
   //Tratamento do sensor DHT11
   umidade = dht.readHumidity(); //Realiza a leitura da umidade e armazena na variável
   temperatura = dht.readTemperature(); //Realiza a leitura da temperatura e armazena na variável 
   sensacao = dht.computeHeatIndex(temperatura, umidade); //Utiliza os parametros de temperatura e umidade do sensor para criar dados de sensação do ambiente
   Serial.print("Temperatura: ");
   Serial.print(temperatura);
   Serial.print(" *C");
   Serial.print(" Sensacação termica: ");
   Serial.print(sensacao);
   Serial.print(" Umidade: ");
   Serial.print(umidade);
   Serial.println(" %t");
  if (isnan(umidade) || isnan(temperatura)) { //Verifica se houve falha na leitura do sensor
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  //Envia ao BLynk os dados gerados pelos sensores
  Blynk.virtualWrite(V5, umidade); //Escreve no pino virtual V5 o valor de h (umidade)
  Blynk.virtualWrite(V6, temperatura); //Escreve no pino virtual v6 o valor de t (temperatura)
  Blynk.virtualWrite(V7,sensorPIR);//Escreve no pino virtual V7 o valor do sensor PIR(quando há movimento)
  Blynk.virtualWrite(V8, sensacao); //Escreve no pino virtual V8 o valor de sensação termica do ambiente entre h e t 
}
void setup(){ 
   Serial.begin(9600);
   pinMode(sensorPIR,INPUT);//Configuração do pino D2
   Blynk.begin(auth, ssid, pass);//Conexão com o Blynk
   dht.begin();//Inicia o sensor DHT11
   timerSensores.setInterval(1000l,dadosSensores);
   timerLED.setInterval(150l,tratamentoLED);
   strip.begin();//Inicia o anel de LED 
   strip.show();//Atribui as configuraçẽos aos LEDs 
}
void loop(){
   Blynk.run();//Acionando o Blynk
   timerSensores.run(); // Inicializa o Timer do DHT11
   timerLED.run(); //Inicio do Timer para controle do LED
}
//Configuraçẽos para as cores dos LEDs
void rgb (int r,int g,int b){    
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(r,g,b));
    strip.show();
  }
}
//Modo que os LEDs "percorrem" o anel ao serem ligados
void Percorrer(uint32_t cor, int tempo) {
  for(uint16_t i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, cor);        
    strip.show();                          
    delay(tempo);                           
   }
}
//Modo criado para gerar um Arco-íris para quando há falha na leitura do sensor DHT11
void ArcoIris(int tempo) {
  for(long primeiroPixelMatriz = 0; primeiroPixelMatriz < 5*65536; primeiroPixelMatriz += 256) {
    for(int i=0; i<strip.numPixels(); i++) {
      int pixelMatriz = primeiroPixelMatriz + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelMatriz)));
    }
    strip.show();
    delay(tempo); //Define uma pausa no ciclos
  }
}
//Configurações para os modos que utilizam o anel de LED
void tratamentoLED(){
   //Se receber 1 da dashboard do Blynk liga o modo, se for 0 desliga
  if (CorTemperatura == 1){
  if(isnan(temperatura)){ //Verifica se houve falha na leitura do sensor, casa aconteça reproduz um Arco-íris
    ArcoIris(5);
  }
   if(temperatura<= 10){
      Percorrer(strip.Color(254,2,224),100); //Violeta
    }
    if(temperatura>10 && temperatura<=25){
      Percorrer(strip.Color(0,0,255),100); //Azul claro
    }
    if(temperatura>25 && temperatura<=30){
      Percorrer(strip.Color(0,255,0),100); //Verde
    }
    if(temperatura>30 && temperatura<=40){
       Percorrer(strip.Color(223,255,0),100); //Amarelo
     }
     if(temperatura>45){
        Percorrer(strip.Color(255,0,0),100); //Vermelho
      }
  }
  if(Lampada == 1){
    Percorrer(strip.Color(201,77,7),100); // Cor quente(alaranjada)
  }
  if(Lampada == 2){
    Percorrer(strip.Color(66,66,199),100); //Cor fria(azulada)
  }
  if(CorTemperatura == 0 && Lampada == 0){
    Percorrer(strip.Color(redValue,greenValue,blueValue),100); //Exibe os valores selecionados, casos os modo anteriores estejam desligados
  }
}
BLYNK_WRITE(V0) {//Botão para o modo de cor pela temperatura do sensor 
   CorTemperatura = param.asInt();
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
BLYNK_WRITE(V4){//Botão para acionar o modo lampada, que recebe o valor 1 para frio e o 2 para quente
   Lampada = param.asInt(); 
}
BLYNK_WRITE(V9){//Botão para o controle de segurança, liga ou desliga o modo
  Seguranca = param.asInt();
}
