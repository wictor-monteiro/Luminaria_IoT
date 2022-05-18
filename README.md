<h1 align="center"> Weer: uma luminária IoT </h1>

A  **Weer** não é uma luminária comum, você pode selecionar a cor de sua preferência, e a  **Weer** pode atuar como um monitor de segurança para o ambiente aonde se encontra. Você pode controlar a  **Weer** através da plataforma Blynk, com presença de seu aplicativo para telefones (IOS/Android).

## :brain: Da ideia a sua criação:
 + Observando algumas funcionalidades sobre luminárias para mesas, foi observador uma simplicidade em produtos no mercado hoje me dia, assim uma nova luminária que ofereça total controle pode surgir como alternativa. A ideia de intorduzir vários sensores que ajudem a monitora o ambiente veio das novas ideas de IoT, e de conceitos aprendidos sobre sistemas embarcados, é claro prezando pelo preço. Com as novas premissas de sitemas IoT a **Weer** entrega um sistema de controle online, com total preferencia do usuário. 
## 🔨 Funcionalidades: 
 + `Função RGB`: Permite o usuário selecionar a cor de sua preferência no espectro padrão RGB;
 + `Modo Luz`: Modo de luz quente e fria, que transmite funcionalidade onde a luminária for posicionanda;
 + `Temperatura e Umidade`: Pode medir a temperatura e a umidade do ambiente, assim como uma função especifíca de luz que exibe a faixa para que a temperatura estiver;
 + `Modo Segurança`: Utilização de um sensor de movimento PIR (Passive Infrared), dispositivo que mede a luz infravermelha irradiada pelos objetos em seu campo de visão, ao qual foi utilizada para controlar o espaço em que se encontra de até 7 m. Assim, com qualquer movimento em seu campo, o `Modo Segurança` quando ativo emite através de um buzzer passivo uma melodia reconhecível e notifica o usuário. 

## :robot: Técnicas e tecnologias: 

- ``Microcontrolador`` : NodeMCU ESP8266;
- ``Framework e Linguagem`` : Arduino IDE e C++;
- ``Plataforma IoT``: Blynk

## :toolbox:	Materiais utilizados na construção do projeto:

| **Quantidade**   | **Produto**                              |
|:----------------:|------------------------------------------|
|        1         | NodeMCU ESP8266                          |
|        1         | Protoboard                               |
|        1         | Anel de LED endereçavel 12bit (WS2812B)  |
|        1         | Fonte Ajustável para Protoboard(5~12v)   |
|        1         | Sensor de movimento PIR (HC-SR501)       |
|        1         | Sensor DHT11                             |
|        1         | Buzzer passivo de 5V                     |

## 📁 Arquivos do projeto
Você pode conferir o arquivo final do projeto clicando [aqui](https://github.com/wictor-monteiro/Luminaria_IoT/tree/main/Luminaria_IOT).
