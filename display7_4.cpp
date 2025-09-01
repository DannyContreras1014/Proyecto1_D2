#include "display7_4.h"

// Tabla 0..9 en bits A..G (bit0=A, bit6=G)
static const uint8_t FONT[10] = {
  0b0111111, // 0
  0b0000110, // 1
  0b1011011, // 2
  0b1001111, // 3
  0b1100110, // 4
  0b1101101, // 5
  0b1111101, // 6
  0b0000111, // 7
  0b1111111, // 8
  0b1101111  // 9
};

// Estado deseado
static volatile uint8_t patDig[3] = {0,0,0}; // patrón A..G por dígito
static volatile bool    dpDig[3]  = {false,false,false}; // DP por dígito
static volatile uint8_t cur = 0;           // dígito activo (0..2)

// Timing multiplex (≈ 1 ms por dígito → ~333 Hz totales)
static uint32_t lastUs = 0;
static const uint32_t SLOT_US = 1000;

// Helpers pines (para escribir más compacto)
static inline void segWrite(uint8_t pin, bool on){
#if SEG_ACTIVE_LOW
  digitalWrite(pin, on ? LOW : HIGH);
#else
  digitalWrite(pin, on ? HIGH : LOW);
#endif
}
static inline void digOn(uint8_t digPin){
#if DIG_ACTIVE_HIGH
  digitalWrite(digPin, HIGH);
#else
  digitalWrite(digPin, LOW);
#endif
}
static inline void digOff(uint8_t digPin){
#if DIG_ACTIVE_HIGH
  digitalWrite(digPin, LOW);
#else
  digitalWrite(digPin, HIGH);
#endif
}

void configDisplay7x3(void){
  // Segmentos
  pinMode(dA, OUTPUT); pinMode(dB, OUTPUT); pinMode(dC, OUTPUT); pinMode(dD, OUTPUT);
  pinMode(dE, OUTPUT); pinMode(dF, OUTPUT); pinMode(dG, OUTPUT); pinMode(dP, OUTPUT);
  // Apagar segmentos
#if SEG_ACTIVE_LOW
  digitalWrite(dA, HIGH); digitalWrite(dB, HIGH); digitalWrite(dC, HIGH); digitalWrite(dD, HIGH);
  digitalWrite(dE, HIGH); digitalWrite(dF, HIGH); digitalWrite(dG, HIGH); digitalWrite(dP, HIGH);
#else
  digitalWrite(dA, LOW);  digitalWrite(dB, LOW);  digitalWrite(dC, LOW);  digitalWrite(dD, LOW);
  digitalWrite(dE, LOW);  digitalWrite(dF, LOW);  digitalWrite(dG, LOW);  digitalWrite(dP, LOW);
#endif

  // Dígitos
  pinMode(DIG1, OUTPUT); pinMode(DIG2, OUTPUT); pinMode(DIG3, OUTPUT);
  digOff(DIG1); digOff(DIG2); digOff(DIG3);

  // Inicial
  patDig[0]=patDig[1]=patDig[2]=0;
  dpDig[0]=dpDig[1]=dpDig[2]=false;
  cur = 0;
  lastUs = micros();
}

// Fija la visualización 
void setTemperatureXX_X(float tempC, bool blankLeadingZero){
  if (tempC < 0)    tempC = 0;
  if (tempC > 99.9) tempC = 99.9;

  int tInt = (int)tempC;
  int tens = tInt / 10;
  int ones = tInt % 10;
  int tenths = (int)roundf( (tempC - tInt) * 10.0f );
  if (tenths == 10){ tenths = 0; ones += 1; if(ones==10){ ones=0; tens+=1; } }
  if (tens > 9) tens = 9;

  // DP en el primer dígito
  dpDig[0] = true;  dpDig[1] = false; dpDig[2] = false;

  // Patrones A..G
  patDig[0] = (tens==0 && blankLeadingZero) ? 0 : FONT[tens];
  patDig[1] = FONT[ones];
  patDig[2] = FONT[tenths];
}

// Refresco no-bloqueante 
void refreshDisplay7x3(void){
  uint32_t now = micros();
  if ((now - lastUs) < SLOT_US) return;
  lastUs = now;

  // Apaga todos los dígitos evitar ghosting
  digOff(DIG1); digOff(DIG2); digOff(DIG3);

  // Avanza dígito
  cur = (cur + 1) % 3;

  // Cargar segmentos para el dígito 'cur'
  uint8_t p = patDig[cur];
  segWrite(dA, p & (1<<0)); // A
  segWrite(dB, p & (1<<1)); // B
  segWrite(dC, p & (1<<2)); // C
  segWrite(dD, p & (1<<3)); // D
  segWrite(dE, p & (1<<4)); // E
  segWrite(dF, p & (1<<5)); // F
  segWrite(dG, p & (1<<6)); // G
  segWrite(dP, (cur==0) ? dpDig[0] : false);

  // Enciende dígito actual
  if (cur==0)      digOn(DIG1);
  else if (cur==1) digOn(DIG2);
  else             digOn(DIG3);
}

// Funcion para configurar display
void configDisplay(void){
    
}

// Desplegar numero en diplay
void despNum(uint8_t numero);

// Desplegar punto
void despPunto(uint8_t punto);

