/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME  "con21407"
#define IO_KEY       "aio_glSQ52gJmEP5npf2SiVrkMDx5PTw"

/******************************* WIFI **************************************/
#define WIFI_SSID "DannyCP"
#define WIFI_PASS "DanielaContreras"


// comment out the following lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
