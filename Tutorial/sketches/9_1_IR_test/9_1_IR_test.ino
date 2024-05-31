/*****************************************************
 
 * This code applies to cokoino 4WD Control Board for Arduino
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0019
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
 
#include <IRremote.h>
int RECV_PIN = 3;//Set infrared remote control pins
long results;//Receive infrared data
 
void setup()
{
  Serial.begin(115200);//set baud rate
  IrReceiver.begin(RECV_PIN);// Set the pins of the infrared receiver
}
 
 
void loop() {
  if (IrReceiver.decode()) 
  {
    results=IrReceiver.decodedIRData.decodedRawData;//Decoding successful, put the data into the results variable
    Serial.println(results,HEX); // Display infrared encoding
    IrReceiver.resume(); 

  }
  delay(100);
}