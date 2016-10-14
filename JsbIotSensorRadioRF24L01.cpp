/*
*	JsbIotSensorRadioRF24L01.cpp
*	Autor: Jullierme Barros
*/

#include "JsbIotSensorRadioRF24L01.h"

JsbIotSensorRadioRF24L01::JsbIotSensorRadioRF24L01(
	short pinEntrada, short pinSaida, uint64_t pipeEscrita, uint64_t pipeLeitura){

	_pinEntrada = pinEntrada;
	_pinSaida = pinSaida;
	_pipeEscrita = pipeEscrita;
	_pipeLeitura = pipeLeitura;

	_radio = RF24(_pinEntrada,_pinSaida);
}

void JsbIotSensorRadioRF24L01::begin(){
	//Inicializa a comunicacao
	_radio.begin();

	if(_pipeEscrita != NULL){
		if(_ativarLog){
			Serial.println("Entrando em modo de transmissão");
		}

		//Entra em modo de transmissao
		_radio.openWritingPipe(_pipeEscrita);
	}

	if(_pipeLeitura != NULL){
		if(_ativarLog){
			Serial.println("Entrando em modo de recepção");
		}

		//Entra em modo de recepcao
		_radio.openReadingPipe(1,_pipeLeitura);

		_radio.startListening();
		//_radio.printDetails();
	}

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
		imprimirDados(dados);
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

		if(_onDadosRetornados && _onDadosRetornados[0]){
			_onDadosRetornados(_dadosRecebidos);

			if(_ativarLog){
				Serial.println("Dados recebidos ");
				imprimirDados(_dadosRecebidos);
			}
		}
	}
}

void JsbIotSensorRadioRF24L01::onDadosRetornados(vFChar metodo){
	_onDadosRetornados = metodo;
}

void JsbIotSensorRadioRF24L01::imprimirDados(char dados[]){
	int x;

	for(x = 0; x < sizeof(dados); x ++){
		if(dados[x] != NULL){
			Serial.print("Valor posição ");
			Serial.print(x);
			Serial.print(": ");
			Serial.println(dados[x]);
		}
	}
}
