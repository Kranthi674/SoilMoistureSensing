#include <ESP8266WiFi.h>
 #include <WiFiClient.h>
 #include <ThingSpeak.h>


const char* ssid = "m";
const char* password = "123907123";

WiFiServer server(80);
int sensorPin = A0;  
int sensorValue = 0;  
int percent = 0;
uint8_t k=0;

 WiFiClient client;  
 unsigned long myChannelNumber = 623531;  
 const char * myWriteAPIKey = "IRLSVJBL3ME6CWOU";  


void setup() {
Serial.begin(9600);
Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  Serial.println("Server started");
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  ThingSpeak.begin(client);  
}

void loop() {
  sensorValue = analogRead(sensorPin);
  percent = convertToPercent(sensorValue);
  printValuesToSerial();
  delay(1000);
    if(sensorValue >100)
  {
      k=sensorValue;  
      ThingSpeak.writeField(myChannelNumber, 1, k, myWriteAPIKey); 
  }
delay(3000); 

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta http-equiv=\"refresh\" content=\"3\">");
  client.println("<h1>Getting NodeMCU Analog values</h1>");
  //int percent = Serial.read();
  client.println("<header>");
  client.println("</header>");
  client.println("<br />");
  client.println("<style>");
  client.println("h1{color: blue;}");
  client.println("</style>");
  client.println("<i>");
  client.print("<h2>");
  client.println("<i>");
  client.println("</i>");
  client.print("&nbsp &nbsp &nbsp &nbsp &nbsp");
  client.print(" Analog value is ");
  client.print(sensorValue);
  client.println("<br>");
  client.print(" percent value is ");
  client.print(percent);
  client.print("</h2>");
  client.println("</html>");
  delay(100);
  Serial.println("Client disconnected");
}
int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 1023, 465, 0, 100);
  return percentValue;
}

void printValuesToSerial()
{
  Serial.print("\n\nAnalog Value: ");
  Serial.print(sensorValue);
  Serial.print("\nPercent: ");
  Serial.print(percent);
  Serial.print("%");
}
