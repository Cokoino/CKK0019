/*****************************************************
 
 * This code applies to cokoino 4WD Control Board for Arduino
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0019
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
#define LED 10

void setup() {
  pinMode(LED,OUTPUT);  
}

void loop() {
digitalWrite(LED，HIGH);//turn on green LED
delay(1000);
digitalWrite(LED,LOW);//turn off green LED
delay(1000);
}
