#include <SPI.h>
#include <Ethernet.h>
int sen0 = -1, sen1 = -1, sen2 = -1, sen3 = -1;
int pd_1=2; //Photodiode to digital pin 2
int pd_2=3; //Photodiode to digital pin 3
int pd_3=4; //Photodiode to digital pin 4
int pd_4=5; //Photodiode to digital pin 5
int led_1 = 6; //led to digital pin 10
int led_2 = 7; //led to digital pin 11
int led_3 = 8; //led to digital pin 12
int led_4 = 9; //led to digital pin 13
int senRead_0=0; //Readings from sensor to analog pin 0
int senRead_1=1; //readings from sensor to analog pin 1
int senRead_2=2; //readings from sensor to analog pin 2
int senRead_3=3; //readings from sensor to analog pin 3
int limit=850; //Threshold range of an obstacle
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10, 20, 12, 245);
// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
14void setup()
{
pinMode(pd_1,OUTPUT);
pinMode(pd_2,OUTPUT);
pinMode(pd_3,OUTPUT);
pinMode(pd_4,OUTPUT);
pinMode(led_1,OUTPUT);
pinMode(led_2,OUTPUT);
pinMode(led_3,OUTPUT);
pinMode(led_4,OUTPUT);
digitalWrite(pd_1,HIGH); //supply 5 volts to photodiode
digitalWrite(pd_2,HIGH); //supply 5 volts to photodiode
digitalWrite(pd_3,HIGH); //supply 5 volts to photodiode
digitalWrite(pd_4,HIGH); //supply 5 volts to photodiode
digitalWrite(led_1,LOW); //set the buzzer in off mode (initial condition)
digitalWrite(led_2,LOW); //set the buzzer in off mode (initial condition)
digitalWrite(led_3,LOW); //set the buzzer in off mode (initial condition)
digitalWrite(led_4,LOW); //set the buzzer in off mode (initial condition)
Serial.begin(9600); //setting serial monitor at a default bound rate of 9600
// Open serial communications and wait for port to open:
Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
// start the Ethernet connection and the server:
Ethernet.begin(mac, ip);
server.begin();
Serial.print("server is at ");
Serial.println(Ethernet.localIP());
}
15void loop()
{
int val=analogRead(senRead_0); //variable to store values from the photodiode
Serial.println(val); // prints the values from the sensor in serial monitor
if(val <= limit) //If obstacle is nearer than the Threshold range
{
sen0 = 1;
digitalWrite(led_1,HIGH); // led will be in ON state
delay(20);
}
else if(val > limit) //If obstacle is not in Threshold range
{
sen0 = 0;
digitalWrite(led_1,LOW); //led will be in OFF state
delay(20);
}
int val_1=analogRead(senRead_1); //variable to store values from the photodiode
Serial.println(val_1); // prints the values from the sensor in serial monitor
if(val_1 <= limit) //If obstacle is nearer than the Threshold range
{
sen1 = 1;
digitalWrite(led_2,HIGH); // led will be in ON state
delay(20);
}
else if(val_1 > limit) //If obstacle is not in Threshold range
{
sen1 = 0;
digitalWrite(led_2,LOW); //led will be in OFF state
delay(20);
}
int val_2=analogRead(senRead_2); //variable to store values from the photodiode
Serial.println(val_2); // prints the values from the sensor in serial monitor
16if(val_2 <= limit) //If obstacle is nearer than the Threshold range
{
sen2 = 1;
digitalWrite(led_3,HIGH); // led will be in ON state
delay(20);
}
else if(val_2 > limit) //If obstacle is not in Threshold range
{
sen2 = 0;
digitalWrite(led_3,LOW); //led will be in OFF state
delay(20);
}
int val_3=analogRead(senRead_3); //variable to store values from the photodiode
Serial.println(val_3); // prints the values from the sensor in serial monitor
if(val_3 <= limit) //If obstacle is nearer than the Threshold range
{
sen3 = 1;
digitalWrite(led_4,HIGH); // led will be in ON state
delay(20);
}
else if(val_3 > limit) //If obstacle is not in Threshold range
{
sen3 = 0;
digitalWrite(led_4,LOW); //led will be in OFF state
delay(20);
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// listen for incoming clients
EthernetClient client = server.available();
if (client) {
Serial.println("new client");
// an http request ends with a blank line
boolean currentLineIsBlank = true;
17while (client.connected()) {
if (client.available()) {
char c = client.read();
Serial.write(c);
// if you've gotten to the end of the line (received a newline
// character) and the line is blank, the http request has ended,
// so you can send a reply
if (c == '\n' && currentLineIsBlank) {
// send a standard http response header
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close"); // the connection will be closed after completion of the
response
client.println("Refresh: 5"); // refresh the page automatically every 5 sec
client.println();
client.println("<!DOCTYPE HTML>");
client.println("<html>");
// output the value of each analog input pin
//for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
// int sensorReading = analogRead(analogChannel);
client.println("<h1>Street Light System</h1>");
client.println("<br />");
client.print("Sensor 1 :\t");
client.print(sen0);
client.println("<br />");
client.print("Sensor 2 :\t");
client.print(sen1);
client.println("<br />");
client.print("Sensor 3 :\t");
client.print(sen2);
client.println("<br />");
client.print("Sensor 4 :\t");
client.print(sen3);
client.println("<br /><br />");
client.println("<h3>Special Thanks to Prof Anurag Lakhlani</h3>");
//}
18client.println("</html>");
break;
}
if (c == '\n') {
// you're starting a new line
currentLineIsBlank = true;
} else if (c != '\r') {
// you've gotten a character on the current line
currentLineIsBlank = false;
}
}
}
// give the web browser time to receive the data
delay(1);
// close the connection:
client.stop();
Serial.println("client disconnected");
}
}
