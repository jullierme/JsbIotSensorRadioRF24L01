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

	if(_ativarLog){
		Serial.println("Entrando em modo de transmissão");
	}
	//Entra em modo de transmissao
	_radio.openWritingPipe(_pipe);

	if(_ativarLog){
		Serial.println("Entrando em modo de recepção");
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
		imprimirDados();
	}

	_radio.stopListening();
	_radio.write(dados, sizeof(dados));
	_radio.startListening();

	if(_ativarLog){
		Serial.println("Dados enviados!!!");
	}
}

RF24 JsbIotSensorRadioRF24L01::getRadio(){
	return _radio;
}

void JsbIotSensorRadioRF24L01::iniciarRecepcaoDeDados(){
	//Verifica se ha sinal de radio
	if (_radio.available()) {
		_radio.read(&_dadosRecebidos, sizeof(_dadosRecebidos));

		if(_ativarLog){
			Serial.println("Dados recebidos ");
			imprimirDados();
		}
	}
}

void JsbIotSensorRadioRF24L01::imprimirDados(){
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
