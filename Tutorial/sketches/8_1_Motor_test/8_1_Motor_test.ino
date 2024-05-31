/*****************************************************
 
 * This code applies to cokoino 4WD Control Board for Arduino
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0019
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
//SET THE PIN FOR DRV8833(U6)
const int NSLEEP1 = 6;       // define pin for PWM used to control rotational speed of M1,M2 motor 
const int AIN1 = 8;          // define pin used to control rotational direction of M1 motor 
const int BIN1 = 7;          // define pin used to control rotational direction of M2 motor 
//SET THE PIN FOR DRV8833(U10)
const int NSLEEP2 = 5;       // define pin for PWM used to control rotational speed of M3,M4 motor 
const int AIN2 = 4;          // define pin used to control rotational direction of M3 motor 
const int BIN2 = A3;         // define pin used to control rotational direction of M4 motor 

void setup() 
{
  Serial.begin(9600);
  pinMode(NSLEEP1, OUTPUT);     // set to output mode 
  pinMode(AIN1, OUTPUT);        // set to output mode
  pinMode(BIN1, OUTPUT);        // set to output mode
  pinMode(NSLEEP2, OUTPUT);     // set to output mode
  pinMode(AIN2, OUTPUT);        // set to output mode
  pinMode(BIN2, OUTPUT);        // set to output mode
}

void loop() {

 analogWrite(NSLEEP1,140); //Start M1,M2 motor and set speed
 //analogWrite(NSLEEP1,Num);Num range from 0 to 255,The larger the Num, the higher the output voltage and the faster the motor speed.
 analogWrite(NSLEEP2,140); //Start M3,M4 motor and set speed
 //analogWrite(NSLEEP2,Num);Num range from 0 to 255,The larger the Num, the higher the output voltage and the faster the motor speed.
 digitalWrite(AIN1,HIGH);  //drive the M1 motor foward rotation
 digitalWrite(BIN1,HIGH);  //drive the M2 motor foward rottion
 digitalWrite(AIN2,HIGH);  //drive the M3 motor foward rotation
 digitalWrite(BIN2,HIGH);  //drive the M4 motor foward rottion
 delay(2000);
 analogWrite(NSLEEP1,140); //Start M1,M2 motor and set speed
 analogWrite(NSLEEP2,140); //Start M3,M4 motor and set speed
 digitalWrite(AIN1,LOW);  //drive the M1 motor reverse rotation
 digitalWrite(BIN1,LOW);  //drive the M2 motor reverse rottion
 digitalWrite(AIN2,LOW);  //drive the M3 motor reverse rotation
 digitalWrite(BIN2,LOW);  //drive the M4 motor reverse rottion
 delay(2000);
 analogWrite(NSLEEP1,0);//stop M1,M2 motor
 analogWrite(NSLEEP2,0);//stop M3,M4 motor
 delay(500);
}
