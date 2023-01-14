#include <SoftwareSerial.h>

SoftwareSerial SIM900(8, 7); // RX, TX

void setup() {
  SIM900.begin(19200); // set the baud rate for the SIM900
  Serial.begin(19200); // set the baud rate for the serial monitor

  // check the connection of the SIM900 module
  SIM900.print("AT\r"); // send the AT command to check if the module is responding
  delay(1000); // give the SIM900 time to respond
  while (SIM900.available()) {
    char c = SIM900.read();
    Serial.print(c); // print the response from the SIM900 to the serial monitor
  }

  SIM900.print("AT+CUSD=1\r"); // enable USSD commands
  delay(1000); // give the SIM900 time to respond
}

int loopCount = 1;

void loop() {
  if (loopCount >= 6) {
    return;
  }
  delay(1000);
  Serial.print("Loop count: ");
  Serial.println(loopCount);
  delay(1000);

  Serial.println("Sending USSD command to check balance:");
  SIM900.print("AT+CUSD=1,\"*1#\"\r"); // send USSD command to check balance
  delay(1500); // give the SIM900 time to respond

  String response = "";
  while (SIM900.available()) {
    char c = SIM900.read();
    response += c;
  }
  Serial.println(response);


  loopCount++;
}
