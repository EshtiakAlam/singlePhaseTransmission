
#include <LiquidCrystal.h>
#define BUZZER_PIN 13
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int mVperAmp = 100;
float I1 = 0.00;
int FT = 1;
int MAP = 0;
double pickup_current = 0.19;
double fault_current = 0;
double Voltage1 = 0;
double Voltage2 = 0;
double VRMS1 = 0;
double VRMS2 = 0;
double AmpsRMS1 = 0;
double AmpsRMS2 = 0;
void setup(){ 
 pinMode(BUZZER_PIN, OUTPUT);
 pinMode (7, OUTPUT);
 pinMode (6, INPUT); 
 lcd.begin(16, 2);
 Serial.begin(9600);
 Serial.begin(9600);
 delay(1000);
  // Initialize LCD display
  Serial.println(" Single Phase ");
  Serial.println(" Transmission ");
  Serial.println(" Line Fault Detection ");
  lcd.print(" Single Phase ");
  lcd.setCursor(0, 1);
  lcd.print("Transmission");
  delay(800);
  lcd.clear();
  lcd.print("  Line Fault  ");
  lcd.setCursor(0, 1);
  lcd.print("  Detection   ");
  delay(800);
}

void loop(){
 Voltage1 = getVPP1();
 VRMS1 = (Voltage1 / 2.0) * 0.707;
 AmpsRMS1 = (VRMS1 * 1000) / mVperAmp;
 Serial.print(AmpsRMS1);
 Serial.println(" RED RMS");
 Voltage2 = getVPP2();
 VRMS2 = (Voltage2 / 2.0) * 0.707;
 AmpsRMS2 = (VRMS2 * 1000) / mVperAmp;
 Serial.print(AmpsRMS2);
 Serial.println(" Neutral RMS");
 if ((AmpsRMS1 > pickup_current) || (AmpsRMS2 > pickup_current)) {
    Serial.println("Fault Detected");
    beep(300, 500);
    lcd.clear();
    lcd.print("Fault Detected");
    FT = 2; // Set fault type
    fault_current = AmpsRMS2;
    digitalWrite(7, HIGH); // Turn on LED or relay
  } else {
    Serial.println("No Fault Detected");
    digitalWrite(7, LOW); // Turn off LED or relay
    lcd.clear();
    lcd.print("No Fault");
    fault_current = AmpsRMS2;
    FT = 1; // Set no fault
  }

 if (fault_current >= 0.33){
  MAP = 2;
  Serial.println("2 KM");
  lcd.setCursor(8, 0);
  lcd.print("2 KM");
  lcd.setCursor(8, 1);
  lcd.print("2 KM");
  
 }
 if ((fault_current >= 0.26) && (fault_current <= 0.32)){
    MAP = 4;
  Serial.println("4 KM");
  lcd.setCursor(8, 0);
  lcd.print("4 KM");
  lcd.setCursor(8, 1);
  lcd.print("4 KM");
  
 }
 if ((fault_current >= 0.23) && (fault_current <= 0.25)){
  MAP = 6;
  Serial.println("6 KM");
  lcd.setCursor(8, 0);
  lcd.print("6 KM");
  lcd.setCursor(8, 1);
  lcd.print("6 KM");
  

 }
 if ((fault_current >= pickup_current) && (fault_current <= 0.22)){
   MAP = 8;
  Serial.println("8 KM");
  lcd.setCursor(8, 0);
  lcd.print("8 KM");
  lcd.setCursor(8, 1);
  lcd.print("8 KM");
  
 }
delay(3000);
 }


float getVPP1()
{
  lcd.clear();
  lcd.print("FAULT DETECTING"); 
  lcd.setCursor (0, 1);  
  lcd.print("----------"); 
  float result1;
  int readValue1;             //value read from the sensor
  int maxValue1 = 0;          // store max value here
  int minValue1 = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue1 = analogRead(A0);
       // see if you have a new maxValue
       if (readValue1 > maxValue1) 
       {
           /*record the maximum sensor value*/
           maxValue1 = readValue1;
       }
       if (readValue1 < minValue1) 
       {
           /*record the minimum sensor value*/
           minValue1 = readValue1;
       }
   }
   

   result1 = ((maxValue1 - minValue1) * 5.0)/1024.0;
      
   return result1;
   
 }
 float getVPP2()
{
  lcd.setCursor (0, 1);  
  lcd.print("------------");
  float result2;
  int readValue2;             //value read from the sensor
  int maxValue2 = 0;          // store max value here
  int minValue2 = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue2 = analogRead(A1);
       // see if you have a new maxValue
       if (readValue2 > maxValue2) 
       {
           /*record the maximum sensor value*/
           maxValue2 = readValue2;
       }
       if (readValue2 < minValue2) 
       {
           /*record the minimum sensor value*/
           minValue2 = readValue2;
       }
   }
   
   // Subtract min from max
   result2 = ((maxValue2 - minValue2) * 5.0)/1024.0;
      
   return result2;
   
 }

 void beep(int frequency, int duration) {
  tone(BUZZER_PIN, frequency);
  delay(duration);
  noTone(BUZZER_PIN);
}
 
 
