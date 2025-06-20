#include<LiquidCrystal.h>
#include <IRremote.h>

#define analog_pin 1
#define ir_receiver_pin 3

int last_command;
IRrecv irrecv(ir_receiver_pin);
LiquidCrystal lcd(7, 8, 9, 10, 11,12); // pins for lcd display....
IRData results;


void setup() {
  Serial.begin(9600);
  irrecv.begin(ir_receiver_pin);
  lcd.begin(16,2);
  lcd.setCursor(0, 0);

}



void loop() {


  

  int tempReading = analogRead(analog_pin);  // read A1 ANALOG PIN
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));


  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK ))* tempK ); //A B C parameters x kelvin 
  
  float tempC = tempK - 273.15;  //farenheit
  float tempF = (tempC * 9.0)/ 5.0 + 32.0;  //celsius

  if (irrecv.decode()) {
    last_command=irrecv.decodedIRData.command;  // Mostrar solo el comando IR
    Serial.println(last_command);
    irrecv.resume();
    }



    if(last_command==12){
    lcd.clear();

    lcd.print(tempC);
    lcd.print(" Celsius");
    }
    
    
  
  
  if(last_command==24){
    lcd.clear();
    lcd.print(tempF);
    lcd.print(" Farenheit");

    
    
  }

  if(last_command==94){
    lcd.clear();
    lcd.print(tempK);
    lcd.print(" Kelvin");
 
    
  }
  if(last_command != 94 && last_command != 24 && last_command != 12){
    lcd.clear();
    lcd.print("press 1,2 or 3");
  }

  delay(100);

  
    //lcd.setCursor(0,1);
  //lcd.print(tempF);


  // put your main code here, to run repeatedly:

}



