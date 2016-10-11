#include "JsbIotSensorRadioRF24L01.h"

short _pinRadioEntrada = 9;
short _pinRadioSaida = 10;

const uint64_t _pipe = 0x4a7362496f74;

//Define os pinos dos botoes
int pino_botao1 = 3;
int pino_botao2 = 4;

JsbIotSensorRadioRF24L01 sensorRadio = JsbIotSensorRadioRF24L01(_pinRadioEntrada,
	_pinRadioSaida, _pipe);

void setup()
{
  //Define os botoes como entrada e ativa pull-up
  pinMode(pino_botao1, INPUT);
  pinMode(pino_botao2, INPUT);

  //Inicializa a serial
  Serial.begin(57600);
  Serial.println("Pressione botao 1 ou 2 para iniciar a comunicacao...");

  sensorRadio.ativarLog();
  sensorRadio.begin();
}

void loop()
{
  if (digitalRead(pino_botao1) == HIGH){
    Serial.println("Botao 1 pressionado !");
    enviarDados('A','D');
  }

  if (digitalRead(pino_botao2) == HIGH){
    Serial.println("Botao 2 pressionado !");
    enviarDados('B','C');
  }
}

void enviarDados(char comando, char valor){
	char dados[32];
	dados[0] = comando;
	dados[1] = valor;
	sensorRadio.enviarDados(dados);
	delay(300);
}
