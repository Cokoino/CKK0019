/*****************************************************
 
 * This code applies to cokoino 4WD Control Board for Arduino
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0019
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
#define LED 10

int PWM_data;
void setup() {
  pinMode(LED,OUTPUT);  
}

void loop() 
{
for(PWM_data=0;PWM_data<=255;PWM_data++){
  analogWrite(LED,PWM_data);  // PWM 
  delay(10);  
  }  
for(PWM_data=255;PWM_data>=0;PWM_data--){
  analogWrite(LED,PWM_data); 
  delay(10); 
  }        
}
