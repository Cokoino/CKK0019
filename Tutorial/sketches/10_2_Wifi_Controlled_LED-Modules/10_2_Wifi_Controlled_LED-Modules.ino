/*****************************************************
 
 * This code applies to cokoino Arduino 4WD Control Board
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0019
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
#include <Regexp.h>

const int NSLEEP1 = 6;       // define pin for PWM used to control rotational speed of M1,M2 motor 
const int AIN1 = 8;          // define pin used to control rotational direction of M1 motor 
const int BIN1 = 7;          // define pin used to control rotational direction of M2 motor 
//SET THE PIN FOR DRV8833(U10)
const int NSLEEP2 = 5;       // define pin for PWM used to control rotational speed of M3,M4 motor 
const int AIN2 = 4;          // define pin used to control rotational direction of M3 motor 
const int BIN2 = A3;         // define pin used to control rotational direction of M4 motor 

#define buzzer_pin 11     //buzzer PIN
#define LED1 2
#define LED2 10



// regular
MatchState ms;
/// Car driving direction control button on the app interface, a total of 8 direction buttons.
const String phone1 = "fS";  // forwardStart:                    
const String phone1_5 = "lfS";  // forward_left_Start            
const String phone2 = "lS";    // leftStart                     
const String phone2_5 = "lbS";  // left_backward_Start        
const String phone3 = "bS";    // backwardStart                    
const String phone3_5 = "rbS";  // backward_right_Start           
const String phone4 = "rS";    // rightStart                     
const String phone4_5 = "rfS";  // right_forward_Start         
/// The other function buttons on the app interface
const String phone5 = "OK";//stop
const String phone6 = "rtl";//rotation left
const String phone7 = "rtr";//rotation right
const String phone8 = "trk";//track line running
const String phone9 = "aod";//Avoid obstacles
const String phone10 = "lgt";//light show
const String phone11 = "muc";//buzzer
const String phone12 = "flt";//fllow light
const String phone13 = "bt1";//button1

String comdata = "";//import the comdata string
char judge = 0;//init the judge


void setup() {

  Serial.begin(115200); 
  delay(100);  // If the information printed out of the serial port is garbled, extend the delay time to solve the problem.
  while (Serial.read() >= 0)
    continue;
  Serial.flush();
  ESP8266_ATCOMMAND();//esp-01 module AT instruction function
  
  pinMode(buzzer_pin, OUTPUT);  // set to output mode 
  pinMode(LED1, OUTPUT);        // set to output mode 
  pinMode(LED2, OUTPUT);        // set to output mode 
  pinMode(NSLEEP1, OUTPUT);     // set to output mode 
  pinMode(AIN1, OUTPUT);        // set to output mode
  pinMode(BIN1, OUTPUT);        // set to output mode
  pinMode(NSLEEP2, OUTPUT);     // set to output mode
  pinMode(AIN2, OUTPUT);        // set to output mode
  pinMode(BIN2, OUTPUT);        // set to output mode
}

void loop() {

  while (Serial.available() > 0) {
    comdata += char(Serial.read());
    delay(1);
  }
  judgement();
}

// ESP8266 set the AT instructionS
void ESP8266_ATCOMMAND() {

  Serial.print(F("AT+RST\r\n"));  //F(): Store string constants in Flash flash to avoid memory depletion due to SRAM usage.
  delay(3000);
  Serial.print(F("AT+CWMODE=3\r\n"));  //set to softAP+station mode
  delay(300);
  Serial.print(F("AT+CWSAP=\"Cokoino_ESP8266-01\",\"12345678\",11,2\r\n"));//wifiname:Cokoino_ESP8266-01,wifipassword:12345678
 //channnel:11 Encryption mode:2 ;Encryption mode should not set to 1,otherwise the wifi can't set successed
  delay(200);
  Serial.print(F("AT+CIPMUX=1\r\n"));//Enable multiple connections
  delay(200);
  Serial.print(F("AT+CIPSERVER=1,3001\r\n"));//Create the server. The default port is 333. Change the port to 3001, which is consistent with the APP
  delay(200);
  Serial.print(F("AT+CIPSTO=7000\r\n"));//Example Set the server timeout period to 7000 seconds
  delay(2000);
}
void judgement() {

  if (comdata.length() > 0) {
    comdata += "\n";  //This sentence must be added, otherwise the matched command character is one less, and the newline is used to assist in the complete match.
    char buf[comdata.length()];
    comdata.toCharArray(buf, comdata.length());
    ms.Target(buf);
    char result = ms.Match("%c*%+IPD, ?[0-9]+, ?[0-9]+: ?([^%c]+)%c*$");
    if (result > 0) {
      ms.GetCapture(buf, 0);
      comdata = String(buf);
      delay(100);
    } else {
      result = ms.Match("%c*%s?([0-9]),%s?([^%c]+)%c*$");  // esp8266 Multi-channel supports up to 5 connections (id:0-4)
      if (result > 0) {
        char buf0[1];  // esp8266 In multi-channel mode. id of the connection at this time
        ms.GetCapture(buf0, 0);
        ms.GetCapture(buf, 1);
        comdata = String(buf);
        if (comdata == "CONNECT")//The APP successfully connects to the wifi of ESP-01 module
        {
          String receiveOkMs = "Welcome to connect to ESP8266-01, ID: " + String(buf0) + " .";//A successful connection message is displayed
          Serial.println("AT+CIPSEND=" + String(buf0) + "," + receiveOkMs.length() + "\r\n");
          delay(10);
          Serial.print(receiveOkMs);
        }
      }
    }
    //comdata = "";
    //return; // When debugging communication with the APP, it needs to be commented out when normal use

     if (comdata == phone1) {
       judge = 1;
     }
     // else if (comdata == phone1_5) {
       //judge = 2;
     //} else if (comdata == phone2) {
       //judge = 3;
     //} else if (comdata == phone2_5) {
       //judge = 4;
     //} 
       else if (comdata == phone3) {
       judge = 5;
     } 
       //else if (comdata == phone3_5) {
       //judge = 6;
     //} else if (comdata == phone4) {
       //judge = 7;
     //} else if (comdata == phone4_5) {
       //judge = 8;
       //} 
       else if (comdata == phone5) {
       judge = 9;
     } 
       //else if (comdata == phone6) {
       //judge = 10;
     //} else if (comdata == phone7) {
       //judge = 11;
     //} else if (comdata == phone8) {
       //judge = 12;
     //} else if (comdata == phone9) {
       //judge = 13;
     //} 
       else if (comdata == phone10) {
       judge = 14;
     } else if (comdata == phone11) {
       judge = 15;
     } 
       //else if (comdata == phone12) {
       //judge = 16;
     //} else if (comdata == phone13) {
       //judge = 17;
     //}
     else {
       judge = 9;
     }
    comdata = "";
  }

  switch (judge) {

    case 1:
      forward();
      break;
    case 5:
      backward();
      break;
    case 9:
      Stop(); 
      break;
    case 14:
      LED(); 
      break;
    case 15:
      music(); 
      delay(2000);
      judge = 9;
      break;  
    default: break;
  }
}

void forward()
{
 analogWrite(NSLEEP1,140); //Start M1,M2 motor and set speed
 //analogWrite(NSLEEP1,Num);Num range from 0 to 255,The larger the Num, the higher the output voltage and the faster the motor speed.
 analogWrite(NSLEEP2,140); //Start M3,M4 motor and set speed
 //analogWrite(NSLEEP2,Num);Num range from 0 to 255,The larger the Num, the higher the output voltage and the faster the motor speed.
 digitalWrite(AIN1,HIGH);  //drive the M1 motor foward rotation
 digitalWrite(BIN1,HIGH);  //drive the M2 motor foward rottion
 digitalWrite(AIN2,HIGH);  //drive the M3 motor foward rotation
 digitalWrite(BIN2,HIGH);  //drive the M4 motor foward rottion
}

void backward()
{
 analogWrite(NSLEEP1,140); //Start M1,M2 motor and set speed
 analogWrite(NSLEEP2,140); //Start M3,M4 motor and set speed
 digitalWrite(AIN1,LOW);  //drive the M1 motor reverse rotation
 digitalWrite(BIN1,LOW);  //drive the M2 motor reverse rottion
 digitalWrite(AIN2,LOW);  //drive the M3 motor reverse rotation
 digitalWrite(BIN2,LOW);  //drive the M4 motor reverse rottion
}
 
void Stop()
{
 analogWrite(NSLEEP1,0);//stop M1,M2 motor
 analogWrite(NSLEEP2,0);//stop M3,M4 motor
 digitalWrite(LED1,LOW);//LED1 OFF
 digitalWrite(LED2,LOW);//LED2 OFF
}
void music()
{
  for(int i = 0;i < 80; i++)
  {
    //The high and low levels constitute a square-wave signal that triggers the passive buzzer to work
    digitalWrite(buzzer_pin, HIGH);
    delay(1);
    digitalWrite(buzzer_pin, LOW);
    delay(1);
  }
  for(int j = 0;j< 100; j++)
  {
    digitalWrite(buzzer_pin, HIGH);
    delay(2);
    digitalWrite(buzzer_pin, LOW);
    delay(2);
  }
}
void LED()
{
  for(int i = 0;i < 15; i++)
  {
    digitalWrite(LED1,HIGH);//LED1 ON
    digitalWrite(LED2,HIGH);//LED2 ON
    delay(100);
    digitalWrite(LED1,LOW);//LED1 OFF
    digitalWrite(LED2,LOW);//LED2 OFF
    delay(100);
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    delay(100);
  }
}
