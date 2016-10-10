/*
*	JsbIotSensorRadioRF24L01.h
*	Autor: Jullierme Barros
*/

#ifndef JsbIotSensorRadioRF24L01_h
#define JsbIotSensorRadioRF24L01_h

#include "Arduino.h"
#include <SPI.h>
#include "RF24.h"

struct JsbIotSensorRadioRF24L01Helper {
	String comando;
	String valor;
};

/*Ao adicionar um método aqui, add também em keywords.txt*/
class JsbIotSensorRadioRF24L01{
	public:
		JsbIotSensorRadioRF24L01(short pinEntrada,
			short pinSaida, uint64_t pipe);
    void ativarLog();
  	void desativarLog();
    //void enviarDados(JsbIotSensorRadioRF24L01Helper);
		void enviarDados(char[]);
    void iniciarRecepcaoDeDados();
		RF24 getRadio();
		void begin();

	private:
		short _pinEntrada;
		short _pinSaida;
		short _pipe;
    bool _ativarLog;
		void imprimirDados();

		//JsbIotSensorRadioRF24L01Helper _dadosRecebidos;
		char _dadosRecebidos[32];

		RF24 _radio = RF24(9,10);
};

#endif
