/*
*	JsbIotSensorRadioRF24L01.cpp
*	Autor: Jullierme Barros
*/

#include "JsbIotSensorRadioRF24L01.h"

JsbIotSensorRadioRF24L01::JsbIotSensorRadioRF24L01(
	short pinEntrada, short pinSaida, uint64_t pipe){

	_pinEntrada = pinEntrada;
	_pinSaida = pinSaida;
	_pipe = pipe;

	_radio = RF24(_pinEntrada,_pinSaida);
}

void JsbIotSensorRadioRF24L01::begin(){
	//Inicializa a comunicacao
  _radio.begin();
	//_radio.setPayloadSize(32);

	if(_ativarLog){
		Serial.println("Entrando em modo de transmissao");
	}
  //Entra em modo de transmissao
  _radio.openWritingPipe(_pipe);

	if(_ativarLog){
		Serial.println("Entrando em modo de recepcao");
	}
	//Entra em modo de recepcao
  _radio.openReadingPipe(1,_pipe);
  _radio.startListening();
	_radio.printDetails();

	if(_ativarLog){
		Serial.println("Fim setup");
	}
}

void JsbIotSensorRadioRF24L01::ativarLog(){
	_ativarLog = true;
}

void JsbIotSensorRadioRF24L01::desativarLog(){
	_ativarLog = false;
}

void JsbIotSensorRadioRF24L01::enviarDados(char dados[]){
	if(_ativarLog){
		Serial.println("Enviando dados ");
		Serial.print("comando ");
		Serial.println(dados[0]);
		Serial.print(" valor ");
		Serial.println(dados[1]);
	}

	_radio.stopListening();
	_radio.write(dados, sizeof(dados));
	_radio.startListening();
}

RF24 JsbIotSensorRadioRF24L01::getRadio(){
	return _radio;
}

void JsbIotSensorRadioRF24L01::iniciarRecepcaoDeDados(){
	//Verifica se ha sinal de radio
  if (_radio.available()) {
		if(_ativarLog){
			Serial.println("");
			Serial.println("Dados recebidos");
			Serial.println("");
		}

		_radio.read(&_dadosRecebidos, sizeof(_dadosRecebidos));

		imprimirDados();
	}
}

void JsbIotSensorRadioRF24L01::imprimirDados(){
	if(_ativarLog){
		int x;

		for(x = 0; x < sizeof(_dadosRecebidos); x ++){
			if(_dadosRecebidos[x] != NULL){
				Serial.print("Valor posição ");
				Serial.print(x);
				Serial.print(": ");
				Serial.println(_dadosRecebidos[x]);
			}
		}
	}
}
