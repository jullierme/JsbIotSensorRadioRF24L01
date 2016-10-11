/*
*	JsbIotSensorRadioRF24L01.h
*	Autor: Jullierme Barros
*/

#ifndef JsbIotSensorRadioRF24L01_h
#define JsbIotSensorRadioRF24L01_h

#include "Arduino.h"
#include <SPI.h>
#include "RF24.h"

/*Ao adicionar um método aqui, add também em keywords.txt*/
class JsbIotSensorRadioRF24L01{
	typedef void (*vFChar)(char[]);

	public:
		JsbIotSensorRadioRF24L01(short pinEntrada,
			short pinSaida, uint64_t pipe);
		void ativarLog();
		void desativarLog();
		void enviarDados(char[]);
		void iniciarRecepcaoDeDados();
		RF24 getRadio();
		void begin();
		void onDadosRetornados(vFChar);

	private:
		vFChar _onDadosRetornados;
		short _pinEntrada;
		short _pinSaida;
		short _pipe;
		bool _ativarLog;
		void imprimirDados();

		char _dadosRecebidos[32];//a lib RF24 só envia 32 bytes de cada vez

		RF24 _radio = RF24(9,10);
};

#endif
