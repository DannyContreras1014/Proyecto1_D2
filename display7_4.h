#ifndef __DISP_H__
#define __DISP_H__

#include <Arduino.h>
#include <stdint.h>

// Prototipos de funciones

// Segmentos (A,B,C,D,E,F,G,DP)
#define dA 16
#define dB 17
#define dC 26
#define dD 14
#define dE 13
#define dF 18
#define dG 33
#define dP 27

// Dígitos 
#define DIG1 22
#define DIG2 21
#define DIG3 19

// Display ánodo común + NPN alto-lado
#define SEG_ACTIVE_LOW 1    // LOW enciende segmento
#define DIG_ACTIVE_HIGH 1   // HIGH habilita dígito

// Funcion para configurar display
void configDisplay7x3(void);               // Configura pines y apaga todo
void setTemperatureXX_X(float tempC, bool blankLeadingZero = true);

// Desplegar numero en diplay
void despNum(uint8_t numero);

// Desplegar punto
void despPunto(uint8_t punto);

// Llama MUY frecuente para multiplexeo no-bloqueante
void refreshDisplay7x3(void);

#endif // __DISP_H__
