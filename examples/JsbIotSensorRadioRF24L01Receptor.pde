#include "JsbIotSensorRadioRF24L01.h"

short _pinRadioEntrada = 9;
short _pinRadioSaida = 10;

const uint64_t _pipe = 0x4a7362496f74;

//Define os pinos dos leds
int LED1 = 2;
int LED2 = 3;

JsbIotSensorRadioRF24L01 sensorRadio = JsbIotSensorRadioRF24L01(_pinRadioEntrada,
	_pinRadioSaida, _pipe);

void setup(){
	//Inicializa a serial
  Serial.begin(57600);

  //Define os pinos dos leds como saida
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  //sensorRadio.ativarLog();
  sensorRadio.begin();
	sensorRadio.onDadosRetornados(onReceberDados);
}

//Sempre vai receber um array de no máximo 32 posições pois a lib RF24 só envia
//no máximo 32 bytes por vez
void onReceberDados(char dados[]){
	Serial.println("");
	Serial.println("Dados recebidos");
	Serial.println("");

	Serial.println(dados[0]);
	Serial.println(dados[1]);
}

void loop(){
  sensorRadio.iniciarRecepcaoDeDados();
	delay(100);
}
