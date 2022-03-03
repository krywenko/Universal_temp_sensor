
#include <math.h>
float Vo = 3.29;  // the more acturate the better 
int sample = 50;
float To = 298.15; // Nominal Temperature

// β coefficients of  resistance 
float Ro1 = 10, B =  3950; //Nominal resistance 50K, Beta constant
float R1 = 10;// Series resistor 10K

float Ro2 = 1.10201, B2 = -316.44; // //kilo ohms 
float R2 = 1;  //kilo ohms 

float Ro3 = .94479, B3 =  -1071.31; //Nominal resistance 50K, Beta constant
float R3 = 10;// Series resistor 10K

float Ro4 = 10, B4 =  3950; //Nominal resistance 50K, Beta constant
float R4 = 10;// Series resistor 10K

// Steinhart-Hart coefficients  for resistance and  thermocouplers
 
int TYPE_1 =0;  // 0 for resister type 1 for thermo coupler
const double A1 = 0.0010059783701056113;   /// example 10k 3950
const double b1 = 0.0002564639419274676;
const double C1 = -1.596587342625349e-8;

int TYPE_2 =0;   // 0 for resister type 1 for thermo coupler
const double A2 = 0.06501312861989986;     /// example PT1000
const double b2 = -0.01161716353567784;
const double C2 = 0.00005732815001133613;

int TYPE_3 =1;    // 0 for resister type 1 for thermo coupler
const double A3 = 0.008423966182197377;       /// example type K
const double b3 = -0.000556941469920589;
const double C3 = -0.0000036838368067031806;

int TYPE_4 = 0;    // 0 for resister type 1 for thermo coupler
const double A4 = 0.0010059783701056113;
const double b4 = 0.0002564639419274676;
const double C4 = -1.596587342625349e-8;

float Tc1 =0; // NTC 10  
float Tc2 =0;  // PT1000 
float Tc3 =0;  // NTC 10
float Tc4 =0;   // NTC 10
double Tc2a =0;
double Tc2b =0;
double Tc2c =0;
double Tc2d =0;

float Via=0;
float Vib=0;
float Vic=0;
float Vid=0;

float ohm1 =0;
float ohm2 =0;
float ohm3 =0;
float ohm4=0;

float Vi = 0;
//float f2 =0;
#include "ADS1X15.h"

ADS1115 ADS(0x48);


void setup() {
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  ADS.begin();
}


void loop() 
{
 THERMO();
 
  Serial.print("β coefficients #1 "); Serial.println( Tc1, 3 );
  Serial.print("β coefficients #2 ");Serial.println( Tc2, 3 );
  Serial.print("β coefficients #3 ");Serial.println( Tc3, 3 );
  Serial.print("β coefficients #4 ");Serial.println( Tc4, 3 );
  Serial.println("");
  Serial.print("Steinhart-Hart coefficients  for #1 "); Serial.println(Tc2a ,3);
  Serial.print("Steinhart-Hart coefficients  for #2 "); Serial.println(Tc2b ,3);
  Serial.print("Steinhart-Hart coefficients  for #3 ");Serial.println(Tc2c ,3);
  Serial.print("Steinhart-Hart coefficients  for #4 "); Serial.println(Tc2d ,3);
    
    //Serial.print("K ohm on #2 "); Serial.println(ohm2, 6);
  Serial.println("------------------------- "); 
  delay(100);
  Tc1 = 0; // resets thermo sampling  
  Tc2 = 0;
  Tc3 = 0;
  Tc4 = 0;
  Tc2a = 0;
  Tc2b = 0;
  Tc2c = 0;
  Tc2d = 0;
  ohm1 = 0;
  ohm2 = 0;
  ohm3 = 0;
  ohm4 = 0;
  Via = 0;
  Vib = 0;
  Vic = 0;
  Vid = 0;

  
}

void THERMO() {
 ADS.setGain(1); 
float T1 = 0;
float T2 = 0;
float T3 = 0;
float T4 = 0;

  for (int i = 0; i <= sample; i++) {
  
  int16_t val_0 = ADS.readADC(0);  
  int16_t val_1 = ADS.readADC(1);  
  int16_t val_2 = ADS.readADC(2);  
  int16_t val_3 = ADS.readADC(3); 
    
    delay(50);
  

float f = ADS.toVoltage(1);  // voltage factor
float f1=(val_0 * f);
float f2=(val_1 * f);
float f3=(val_2 * f);
float f4=(val_3 * f);
// Serial.println(f1, 4); //prints the voltage of  f1

   Vi = f1; 

  //All Resistance are in kilo ohms.
  float R = (Vi * R1 ) / (Vo - Vi); // - to increase + to decrease .1 resistance = .5c 
  float T =  1 / ((1 / To) + ((log(R / Ro1)) / B));
  float TcA = T - 273.15; // Converting kelvin to celsius
  T1 = (1 / (A1 + (b1 * log(R*1000)) +  (C1 * ( log(R*1000) * log(R*1000) * log(R*1000))))-273.15 );
  Via =Via +Vi;
  Tc1 = Tc1+TcA;
  Tc2a = Tc2a+T1;
  ohm1 = ohm1 + R;
  /////////////
   Vi = f2; 
   R = (Vi * R2 ) / (Vo - Vi); // - to increase + to decrease .1 resistance = .5c 
   //float TMP = R/R_SH;
   T =  1 / ((1 / To) + ((log(R /Ro2)) / B2));
   float TcB = T - 273.15; // Converting kelvin to celsius
   Tc2 = Tc2+TcB;
  T2 = (1 / (A2 + (b2 * log(R*1000)) +  (C2 * ( log(R*1000) * log(R*1000) * log(R*1000))))-273.15 );
  ohm2 = ohm2 + R;
  Vib =Vib +Vi;
  Tc2b = Tc2b+T2;
 //////////////
   Vi = f3; 
   R = (Vi * R3 ) / (Vo - Vi); // - to increase + to decrease .1 resistance = .5c 
   T =  1 / ((1 / To) + ((log(R / Ro3)) / B3));
   float TcC = T - 273.15; // Converting kelvin to celsius
  T3 = (1 / (A3 + (b3 * log(R*1000)) +  (C3 * ( log(R*1000) * log(R*1000) * log(R*1000))))-273.15 );
Vic =Vic +Vi;
  Tc2c = Tc2c+T3; 
   Tc3 = Tc3+TcC;
   ohm3 = ohm3 +R;
   Vi = f4; 
   R = (Vi * (R4 )) / (Vo - Vi); // - to increase + to decrease .1 resistance = .5c 
   T =  1 / ((1 / To) + ((log(R / Ro4)) / B4));
   float TcD = T - 273.15; // Converting kelvin to celsius 
   T4 = (1 / (A4 + (b4 * log(R*1000)) +  (C4 * ( log(R*1000) * log(R*1000) * log(R*1000))))-273.15 );
Vid =Vid +Vi;
   Tc4 = Tc4+TcD; 
   Tc2d = Tc2d+T4;
  ohm4 =ohm4+ R;
  }

  ohm1=ohm1/sample; 
  ohm2=ohm2/sample;
  ohm3=ohm3/sample;
  ohm4=ohm4/sample;
 // Serial.print(f2, 5); Serial.print(" ");
Serial.println("");
  Serial.print( "max volt"); Serial.println( ADS.getMaxVoltage() );
  Serial.print("Kohm on #1 "); Serial.println(ohm1, 5);
  Serial.print("Kohm on #2 "); Serial.println(ohm2, 5);
  Serial.print("Kohm on #3 "); Serial.println(ohm3, 5);
  Serial.print("Kohm on #4 "); Serial.println(ohm4, 5);
  Tc1 = Tc1/sample;
  Tc2 = Tc2/sample;
  Tc3 = Tc3/sample;
  Tc4 = Tc4/sample; 
  Tc2a=Tc2a/sample;
  Tc2b=Tc2b/sample;
  Tc2c=Tc2c/sample;
  Tc2d=Tc2d/sample; 
  //Via = ((Via/sample)*1000) + 1 ;
  //Vib = ((Vib/sample)*1000) + 1 ;
  //Vic = ((Vic/sample)*1000) + 1 ;
  //Vid = ((Vid/sample)*1000) + 1 ;
  
  if (TYPE_1 == 1){
  float P_R = (ohm1 *100) +1;
  Tc2a = (1 / (A1 + (b1 * log(P_R*1000)) +  (C1 * ( log(P_R*1000) * log(P_R*1000) * log(P_R*1000))))-273.15 );
  
  Serial.print("pseudo Kohm on #1 "); Serial.println(P_R, 5);
  }
  if (TYPE_2 == 1){
  float P_R = (ohm2 *100) +1;
  Tc2b = (1 / (A2 + (b2 * log(P_R*1000)) +  (C2 * ( log(P_R*1000) * log(P_R*1000) * log(P_R*1000))))-273.15 );
  
  Serial.print("pseudo Kohm on #2 "); Serial.println(P_R, 5);
  }
  if (TYPE_3 == 1){
  float P_R = (ohm3 *100) +1;
  Tc2c = (1 / (A3 + (b3 * log(P_R*1000)) +  (C3 * ( log(P_R*1000) * log(P_R*1000) * log(P_R*1000))))-273.15 );
  Serial.print("pseudo Kohm on #3 "); Serial.println(P_R, 5);
  }
  if (TYPE_4 ==1){
   float P_R = (ohm4 *100) +1;
  Tc2d = (1 / (A4 + (b4 * log(P_R*1000)) +  (C4 * ( log(P_R*1000) * log(P_R*1000) * log(P_R*1000))))-273.15 );
 
  Serial.print("pseudo Kohm on #4 "); Serial.println(P_R, 5);
  }
  // Serial.print("volt ") ; Serial.print(Via, 8); Serial.print(" ");
Serial.println("");
return;
}
// -- END OF FILE --
