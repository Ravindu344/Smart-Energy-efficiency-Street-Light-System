#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int timer1;
int timer2;


float Time;
int s0 = 30;
int s1 = 100;
int s2 = 170;
int s3 = 255;
int flag1 = 0;
int flag2 = 0;

float distance = 5;
float speed;

int ir_s1 = A11;
int ir_s2 = A12;


const int numLEDs = 10;
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int irPins[] = {A1,A2,A3,A4,A5,A6,A7,A8,A9,A10};

const int ldrPin0 = A0;

const int ldrPin1 = A13;



void setup(){
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  for (int i = 0; i < numLEDs; i++) {
    pinMode(irPins[i], INPUT);
  }

  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
 
  Serial.begin(9600);
   lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on backlight

  lcd.clear();
  
}
void(* resetFunc) (void) = 0;
void loop() {


int ldrValue0 = analogRead(ldrPin0);
int ldrValue1 = analogRead(ldrPin1);
int ir1=20;
int d1 = 1500;
int d2 = 1000;
int d3 = 500;
if (ldrValue0 < 600 ) {   


if(digitalRead (ir_s1) == LOW && flag1==0){timer1 = millis(); flag1=1;}

if(digitalRead (ir_s2) == LOW && flag2==0){timer2 = millis(); flag2=1;}

if (flag1==1 && flag2==1){
     if(timer1 > timer2){Time = timer1 - timer2;}
     else if(timer2 > timer1){Time = timer2 - timer1;}
 Time=Time/1000;//convert millisecond to second
 speed=(distance/Time);//v=d/t
 speed=speed*3600;//multiply by seconds per hr
 speed=speed/1000;
 //division by meters per Km
  
}

if(speed==0){ 
lcd.setCursor(0, 1); 
lcd.print("No car  detected");
                   
}

else{
    lcd.clear(); 
    lcd.setCursor(0, 0); 
    lcd.print("Speed:");
    lcd.print(speed,1);
    lcd.print("Km/Hr  ");
    lcd.setCursor(0, 1); 
}
    if (speed !=0 && speed <15 && speed >=5) {
     //ir01
      while (digitalRead(irPins[0]) == LOW) {
      analogWrite(ledPins[0], s1);
      analogWrite(ledPins[1], s1);  
       delay(d1);
      }
      while (digitalRead(irPins[0]) == HIGH)   {
      analogWrite(ledPins[0], s0);
      analogWrite(ledPins[1], s0);
     
      break;
      }//ir 02
       while (digitalRead(irPins[1]) == LOW) {
      analogWrite(ledPins[1], s1);
      analogWrite(ledPins[2], s1);  
       delay(d1);
      }
      while (digitalRead(irPins[1]) == HIGH)   {
      analogWrite(ledPins[1], s0);
      analogWrite(ledPins[2], s0);
      break;
      
      }//ir3
      while (digitalRead(irPins[2]) == LOW) {
        //fault and vehicle pass
       if (ldrValue1 <ir1){
      analogWrite(ledPins[2], s1);
      analogWrite(ledPins[3], s1+155); 
       delay(d1); 
          }
          else {
            //normal and vehicle pass
            analogWrite(ledPins[3], s1);
            analogWrite(ledPins[2], s1); 
             delay(d1);
          }
      }
      while (digitalRead(irPins[2]) == HIGH)   {
        //fault and no vehicle
         if (ldrValue1 <ir1){
      analogWrite(ledPins[2], s0);
      analogWrite(ledPins[3], s0+160);  \
      
          }
          else {
            //normal and no vehicle
            analogWrite(ledPins[3], s0);
            analogWrite(ledPins[2], s0);  
          }
      break;
      }//Ir 04
      while (digitalRead(irPins[3]) == LOW) {
        //fault and vehicle pass
          if (ldrValue1 <ir1){
      analogWrite(ledPins[3], s1+155);
         delay(d1);
          }
          else {
            //no fault and vehicle pass
            analogWrite(ledPins[3], s1);
            analogWrite(ledPins[4], s1);  
             delay(d1);
          }
      }
      while (digitalRead(irPins[3]) == HIGH)   {
        //  fault and no vehicle 
         if (ldrValue1 <ir1){
      analogWrite(ledPins[3], s0+160);

          }
          else {
            // no fault no vehicle
            analogWrite(ledPins[3], s0);
            analogWrite(ledPins[4], s0);  
          }
      break;
      }//ir 05
      while (digitalRead(irPins[4]) == LOW) {
        //fault and vehicle pass
       if (ldrValue1 <ir1){
      analogWrite(ledPins[5], s1+155);
         delay(d1);
          }
          else {
            // no fault and vehicle pass
            analogWrite(ledPins[5], s1);
            analogWrite(ledPins[4], s1);  
             delay(d1);
          }
      } 
      while (digitalRead(irPins[4]) == HIGH)   {
        // fault and no vehicle
       if (ldrValue1 <ir1){
      analogWrite(ledPins[5], s0+160);

          }
          else {
            //no fault and no vehicle
            analogWrite(ledPins[5], s0);
            analogWrite(ledPins[4], s0);  
          }
      break;
      }//ir6
      while (digitalRead(irPins[5]) == LOW) {
      if (ldrValue1 <ir1){
        // fault and vehicle pass
      analogWrite(ledPins[5], s1+155);
         analogWrite(ledPins[6], s1);
          delay(d1);
          }
          else {
            // no fault and vehicle pass
            analogWrite(ledPins[5], s1);
            analogWrite(ledPins[6], s1); 
             delay(d1); 
          }
      }
      while (digitalRead(irPins[5]) == HIGH)   {
        // fault and no vehicle
      if (ldrValue1 <ir1){
      analogWrite(ledPins[5], s0 +160);

          }
          else {
            //no fault and no vehicle
            analogWrite(ledPins[5], s0);
            analogWrite(ledPins[6], s0);  
          }
      break;
      }//ir 07
       while (digitalRead(irPins[6]) == LOW) {
      analogWrite(ledPins[6], s1);
      analogWrite(ledPins[7], s1);  
       delay(d1);
      
      }
      while (digitalRead(irPins[6]) == HIGH)   {
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[7], s0);
      break;
      }//ir8
      while (digitalRead(irPins[7]) == LOW) {
      analogWrite(ledPins[7], s1);
      analogWrite(ledPins[8], s1); 
       delay(d1); 
      
      }
      while (digitalRead(irPins[7]) == HIGH)   {
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[8], s0);
      break;
      }//Ir 09
      while (digitalRead(irPins[8]) == LOW) {
      analogWrite(ledPins[8], s1);
      analogWrite(ledPins[9], s1);  
       delay(d1);
      
      }
      while (digitalRead(irPins[8]) == HIGH)   {
      analogWrite(ledPins[8], s0);
      analogWrite(ledPins[9], s0);
      break;
      }//ir 10
      while (digitalRead(irPins[9]) == LOW) {
      analogWrite(ledPins[9], s1);
       delay(d1);

      }
      while (digitalRead(irPins[9]) == HIGH)   {
      analogWrite(ledPins[9], s0);
      // speed=0;
      break;
      }

    }
    else if (speed <50 && speed >=15) {

      while (digitalRead(irPins[0]) == LOW) {
      analogWrite(ledPins[0], s2);
      analogWrite(ledPins[1], s2);  
      analogWrite(ledPins[2], s2);
      delay(d2);
      
      }
      while (digitalRead(irPins[0]) == HIGH)   {
      analogWrite(ledPins[0], s0);
      analogWrite(ledPins[1], s0);
      analogWrite(ledPins[2], s0);
      break;
      }

      //ir 02
       while (digitalRead(irPins[1]) == LOW) {
        //fault and vehicle pass
         if (ldrValue1 <ir1){
      analogWrite(ledPins[1], s2);
      analogWrite(ledPins[2], s2);
      analogWrite(ledPins[3], s2+85);  
       delay(d2); 
         }
      else{
        //no fault and vehicle pass
      analogWrite(ledPins[1], s2);
      analogWrite(ledPins[2], s2);
      analogWrite(ledPins[3], s2);  
       delay(d2); 

      }
      }
      while (digitalRead(irPins[1]) == HIGH)   {
        if(ldrValue1 <ir1){
          // fault and no vehicle
      analogWrite(ledPins[1], s0);
      analogWrite(ledPins[2], s0);
      analogWrite(ledPins[3], s0+160);
        }
        else{
          //no fault and no vehicle
           analogWrite(ledPins[1], s0);
      analogWrite(ledPins[2], s0);
      analogWrite(ledPins[3], s0);
        }
      break;
      }
      
      //ir3
      while (digitalRead(irPins[2]) == LOW) {
      if (ldrValue1 <ir1){
      // fault and vehicle pass
      analogWrite(ledPins[2], s2);
      analogWrite(ledPins[3], s2+85);
       delay(d2);   
         }
      else{
        // no fault and vehicle pass
      analogWrite(ledPins[4], s2);
      analogWrite(ledPins[2], s2);
      analogWrite(ledPins[3], s2);
       delay(d2);   

      }
      }
      while (digitalRead(irPins[2]) == HIGH)   {
      if(ldrValue1 <ir1){
        //fault and no vehicle
      analogWrite(ledPins[3], s0+160);
      analogWrite(ledPins[2], s0);
      
        }
        else{
          //no fault and no vehicle
      analogWrite(ledPins[1], s0);
      analogWrite(ledPins[2], s0);
      analogWrite(ledPins[3], s0);
        }
      break;
      }
      
      //Ir 04
      while (digitalRead(irPins[3]) == LOW) {
       if (ldrValue1 <ir1){
      //fault and vehicle pass
      analogWrite(ledPins[5], s2+85);
      analogWrite(ledPins[3], s2+85);  
       delay(d2); 
         }
      else{
        //no fault and vehicle pass
      analogWrite(ledPins[4], s2);
      analogWrite(ledPins[5], s2);
      analogWrite(ledPins[3], s2);  
       delay(d2); 

      }
      }
      while (digitalRead(irPins[3]) == HIGH)   {
        //fault and no vehicle
       if(ldrValue1 <ir1){
      analogWrite(ledPins[3], s0+160);
      analogWrite(ledPins[5], s0+160);
      
        }
        else{
          //no fault and no vehicle
      analogWrite(ledPins[4], s0);
      analogWrite(ledPins[5], s0);
      analogWrite(ledPins[3], s0);
        }
      break;
      }
      
      //ir 05
      while (digitalRead(irPins[4]) == LOW) {
        if (ldrValue1 <ir1){
      //fault and vehicle pass
      analogWrite(ledPins[5], s2+85);
      analogWrite(ledPins[6], s2);   
       delay(d2);
         }
      else{
        //no fault and vehicle pass
      analogWrite(ledPins[4], s2);
      analogWrite(ledPins[5], s2);
      analogWrite(ledPins[6], s2);   
       delay(d2);

      }
      
      }
      while (digitalRead(irPins[4]) == HIGH)   {
        //fault and no vehicle
       if(ldrValue1 <ir1){
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[6], s0+160);
      
        }
        else{
          //no fault no vehicle
      analogWrite(ledPins[4], s0);
      analogWrite(ledPins[5], s0);
      analogWrite(ledPins[6], s0);
        }
      break;
      }//ir6
      while (digitalRead(irPins[5]) == LOW) {
       if (ldrValue1 <ir1){
        //fault and vehicle pass
      
      analogWrite(ledPins[5], s2+85);
      analogWrite(ledPins[6], s2);   
       analogWrite(ledPins[7], s2); 
        delay(d2);
         }
      else{
        //no fault and vehicle pass
      analogWrite(ledPins[7], s2);
      analogWrite(ledPins[5], s2);
      analogWrite(ledPins[6], s2);  
       delay(d2); 

      }
      
      }
      while (digitalRead(irPins[5]) == HIGH)   {
        //fault and no vehicle
      if(ldrValue1 <ir1){
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[5], s0+160);
       analogWrite(ledPins[6], s0);
        }
        else{
          //no fault and no vehicle
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[5], s0);
      analogWrite(ledPins[6], s0);
        }
      break;
      }//ir 07
       while (digitalRead(irPins[6]) == LOW) {
      analogWrite(ledPins[6], s2);
      analogWrite(ledPins[7], s2);
      analogWrite(ledPins[8], s2);
       delay(d2);
      
      }
      while (digitalRead(irPins[6]) == HIGH)   {
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[8], s0);
      break;
      }//ir8
      while (digitalRead(irPins[7]) == LOW) {
      analogWrite(ledPins[7], s2);
      analogWrite(ledPins[8], s2);
      analogWrite(ledPins[9], s2);
       delay(d2);
      
      }
      while (digitalRead(irPins[7]) == HIGH)   {
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[8], s0);
      analogWrite(ledPins[9], s0);
      
      break;
      }//Ir 09
      while (digitalRead(irPins[8]) == LOW) {
      analogWrite(ledPins[8], s2);
      analogWrite(ledPins[9], s2);
       delay(d2);
      
      
      }
      while (digitalRead(irPins[8]) == HIGH)   {
      analogWrite(ledPins[8], s0);
      analogWrite(ledPins[9], s0);
      
      break;
      }//ir 10
      while (digitalRead(irPins[9]) == LOW) {
      analogWrite(ledPins[9], s2);
       delay(d2);
   
      
      }
      while (digitalRead(irPins[9]) == HIGH)   {
      analogWrite(ledPins[9], s0);
    
      break;
      }
    }
    // speed>50
    else {
      
      while (digitalRead(irPins[0]) == LOW) {
        // no fault and vehicle pass
      analogWrite(ledPins[0], s3);
      analogWrite(ledPins[1], s3);
      analogWrite(ledPins[2], s3);
      analogWrite(ledPins[3], s3);
      analogWrite(ledPins[4], s3);
       delay(d3);

      
      }
      while (digitalRead(irPins[0]) == HIGH)   {
      if (ldrValue1 <ir1){
        //fault and no vehicle
      analogWrite(ledPins[0], s0);
      analogWrite(ledPins[1], s0);
      analogWrite(ledPins[2], s0);
      analogWrite(ledPins[3], s0+160);
       analogWrite(ledPins[4], s0);

      }
      else{
        //no fault and no vehicle
      analogWrite(ledPins[0], s0);
      analogWrite(ledPins[1], s0);
      analogWrite(ledPins[2], s0);
      analogWrite(ledPins[3], s0);
      analogWrite(ledPins[4], s0);
      }
      break;
      }
      //ir 02
      while (digitalRead(irPins[1]) == LOW) {
        //no fault and vehicle pass
      analogWrite(ledPins[1], s3);
      analogWrite(ledPins[2], s3);
      analogWrite(ledPins[3], s3);
      analogWrite(ledPins[4], s3);
      analogWrite(ledPins[5], s3);
       delay(d3);
      
      }
      while (digitalRead(irPins[1]) == HIGH)   {
      if (ldrValue1 <ir1){
        //fault and no vehicle
      analogWrite(ledPins[5], s0+160);
      analogWrite(ledPins[1], s0);
      analogWrite(ledPins[2], s0);
      analogWrite(ledPins[3], s0+160);
      }
      else{
        //no fault no vehicle
      analogWrite(ledPins[5], s0);
      analogWrite(ledPins[1], s0);
      analogWrite(ledPins[2], s0);
      analogWrite(ledPins[3], s0);
      analogWrite(ledPins[4], s0);
      }
      break;
      }//ir3
      while (digitalRead(irPins[2]) == LOW) {
        //no fault and vehicle pass
      analogWrite(ledPins[2], s3);
      analogWrite(ledPins[3], s3);  
      analogWrite(ledPins[4], s3);
      analogWrite(ledPins[5], s3);
      analogWrite(ledPins[6], s3);
        delay(d3);

      
      }
      while (digitalRead(irPins[2]) == HIGH)   {
       if (ldrValue1 <ir1){
        //fault and no vehicle
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[5], s0+160);
      analogWrite(ledPins[2], s0);
      analogWrite(ledPins[3], s0+160);
      }
      else{
       // no fault and no vehicle
      analogWrite(ledPins[5], s0);
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[2], s0);
      analogWrite(ledPins[3], s0);
      analogWrite(ledPins[4], s0);
      }
      break;
      }//Ir 04
      while (digitalRead(irPins[3]) == LOW) {
        //no fault and vehicle
      analogWrite(ledPins[3], s3);
      analogWrite(ledPins[4], s3);
      analogWrite(ledPins[5], s3);
      analogWrite(ledPins[6], s3);
      analogWrite(ledPins[7], s3);  
       delay(d3);
      
      }
      while (digitalRead(irPins[3]) == HIGH)   {
     if (ldrValue1 <ir1){
      //fault and no vehicle
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[5], s0+160);
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[3], s0+160);
      }
      else{
        //no fault and no vehicle
      analogWrite(ledPins[5], s0);
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[3], s0);
      analogWrite(ledPins[4], s0);
      }
      break;
      }//ir 05
      while (digitalRead(irPins[4]) == LOW) {
        //no fault and vehicle pass
      analogWrite(ledPins[4], s3);
      analogWrite(ledPins[5], s3); 
      analogWrite(ledPins[6], s3);
      analogWrite(ledPins[7], s3);
      analogWrite(ledPins[8], s3); 
       delay(d3);
      
      }
      while (digitalRead(irPins[4]) == HIGH)   {
      if (ldrValue1 <ir1){
        //fault and no vehicle
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[5], s0+160);
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[8], s0);
      }
      else{
        //no fault and no vehicle
      analogWrite(ledPins[5], s0);
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[8], s0);
      analogWrite(ledPins[4], s0);
      }
      break;
      }//ir6
      while (digitalRead(irPins[5]) == LOW) {
        //no fault and vehicle pass
      analogWrite(ledPins[5], s3);
      analogWrite(ledPins[6], s3); 
      analogWrite(ledPins[7], s3);
      analogWrite(ledPins[8], s3);
      analogWrite(ledPins[9], s3); 
       delay(d3);
      
      }
      while (digitalRead(irPins[5]) == HIGH)   {
           if (ldrValue1 <ir1){
            //fault and no vehicle
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[5], s0+160);
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[8], s0);
      analogWrite(ledPins[9], s0);
      }
      else{
        //no fault and no vehicle
      analogWrite(ledPins[5], s0);
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[8], s0);
      analogWrite(ledPins[9], s0);
      }
      break;
      }//ir 07
      while (digitalRead(irPins[6]) == LOW) {
      analogWrite(ledPins[6], s3);
      analogWrite(ledPins[7], s3);
      analogWrite(ledPins[8], s3);
      analogWrite(ledPins[9], s3);
      delay(d3);
      }
      while (digitalRead(irPins[6]) == HIGH)   {
      analogWrite(ledPins[6], s0);
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[8], s0);
      analogWrite(ledPins[9], s0);
      
      break;
      }//ir8
      while (digitalRead(irPins[7]) == LOW) {
      analogWrite(ledPins[7], s3);
      analogWrite(ledPins[8], s3);
      analogWrite(ledPins[9], s3);
       delay(d3);
      
      }
      while (digitalRead(irPins[7]) == HIGH)   {
      analogWrite(ledPins[7], s0);
      analogWrite(ledPins[8], s0);
      analogWrite(ledPins[9], s0);
    
      break;
      }//Ir 09
      while (digitalRead(irPins[8]) == LOW) {
      analogWrite(ledPins[8], s3);
      analogWrite(ledPins[9], s3);
       delay(d3);
      
      }
      while (digitalRead(irPins[8]) == HIGH)   {
      analogWrite(ledPins[8], s0);
      analogWrite(ledPins[9], s0);
    
      break;
      }//ir 10
      while (digitalRead(irPins[9]) == LOW) {
      analogWrite(ledPins[9], s3);
      delay(d3);
      
      }
      while (digitalRead(irPins[9]) == HIGH)   {
      analogWrite(ledPins[9], s0);
    
      break;
      }
    }
    Serial.println(speed);

  }

  else {
    // It's day time, turn off all LEDs
    for (int i = 0; i < numLEDs; i++) {
      
      digitalWrite(ledPins[i], LOW);
}
}
// delay(200);
 if(digitalRead(irPins[9]) == LOW){
  // delay(200);
resetFunc();
}
}