 
 #include <ESP8266WiFi.h>  
 #include <WiFiClient.h>  
 #include <ThingSpeak.h>  
 
   
int sensorPin = A0;  
int sensorValue = 0;  
int percent = 0;
int k=0;


   
 const char* ssid = "Pirates";  
 const char* password = "1223334444";  
 WiFiClient client;  
 unsigned long myChannelNumber = 623531;  
 const char * myWriteAPIKey = "IRLSVJBL3ME6CWOU";  
 void setup()  
 {  
  Serial.begin(115200);  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
 }  
 void loop()   
 {  
 static boolean data_state = false;  
  sensorValue = analogRead(sensorPin);
  percent = convertToPercent(sensorValue);
  printValuesToSerial();
  delay(1000);
 
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write to field 1.  
  if(percent >100)
  {
      k=percent;  
  }
  /* else
  {
      l=humidity;  
  }*/
  if( data_state )  
  {  
   ThingSpeak.writeField(myChannelNumber, 1, k, myWriteAPIKey);  
   data_state =true;  
  }  
  /*else  
  {  
   ThingSpeak.writeField(myChannelNumber, 2, l, myWriteAPIKey);  
   data_state = true;  
  } */ 
  delay(3000); // ThingSpeak will only accept updates every 15 seconds.
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
