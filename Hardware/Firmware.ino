licencia gnu gpl 3.0 o superior

#include <eRCaGuy_NewAnalogRead.h>
#include <avr/wdt.h> //watchdog 
#include <avr/sleep.h> //sleep energy management
#include <avr/power.h> 
float GetPlatinumRTD(float R) {
   float RT0=1000;
   float a=0.0039083;
   float b=-0.0000005775;
   float A =b*RT0;
   float B = a*RT0;
   float C = RT0-R;
   float T=0;
   
   //parte positiva de la ecuacion de segundo grado
   T= -B;
   T= T + (sqrt((B*B) - 4.0 * A * C));
   T= T / (2.0 * A);
   
   if(T>0) {
     return T;
   }
   else {
     //parte negativa de la ecuacion de segundo grado.
     T= -B;
     T= T -(sqrt((B*B) - 4.0 * A * C));
     T= T /(2.0 * A);
     return T;
   }
}
float GetResistor(int Analog_pin,float R0, int bits_of_precision, float Vin){
    eRCaGuy_NewAnalogRead rawdata;
    float Vout;
    float RT;
    // set adc frequency to 76.9kHz
    rawdata.setADCSpeed(ADC_FAST);
    float raw = rawdata.newAnalogRead (Analog_pin,bits_of_precision);
    Vout = ((raw*Vin)/(pow(2,bits_of_precision)));
    
    return RT = (R0*Vout)/((Vin-Vout));
    
    }
#define R0 2100

#define bits_of_precision 16
#define Vin 5.0
#define A0 0
define sleep_time WDTO_8S
float R_Pt1000= 1000;
float Temperature;
void setup(){
  Serial.begin(115200);
  
  wdt_disable();
  wdt_enable(sleep_time);
  
 
}
void loop(){
  wdt_reset();
  sleep_disable();
  power_adc_enable();
  R_Pt1000=GetResistor(A0,R0,bits_of_precision,Vin);
  Temperature=GetPlatinumRTD(R_Pt1000);
  Serial.print(Temperature);
  Serial.print("\n");
  Serial.end();
  delay(500);
  
   power_adc_disable(); 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  sleep_enable();

  
   
  
}
