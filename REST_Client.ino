#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
 
void setup() {
 
  Serial.begin(115200);                      
  WiFi.begin("rb", "987654321*");
  while (WiFi.status() != WL_CONNECTED) {  
    delay(100);
    Serial.println("Waiting for connection");
  }
 
}
 
void loop() {
 
 if(WiFi.status()== WL_CONNECTED){
 
    StaticJsonBuffer<500> JSONbuffer;   
    JsonObject& JSONencoder = JSONbuffer.createObject(); 
 
    JSONencoder["id"] = 1;
    JSONencoder["gpio"] = 12;
    JSONencoder["status1"] = 0;
 
    char JSONmessageBuffer[300];
    
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
 
   HTTPClient http;
   http.begin("http://192.168.31.7:80/leds");      
   http.addHeader("Content-Type", "application/json");   
   int httpCode = http.POST(JSONmessageBuffer);

   String payload = http.getString();      
 
   Serial.println(httpCode);  
   Serial.println(payload);

 
    JSONencoder["id"] = 1;
    JSONencoder["gpio"] = 12;
    JSONencoder["status1"] = 1;
 
    
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
 
   http.begin("http://192.168.31.7:80/leds");      
   http.addHeader("Content-Type", "application/json");   
   int httpcode = http.PUT(JSONmessageBuffer);

   String payload1 = http.getString();      
 
   Serial.println(httpcode);  
   Serial.println(payload1);
   http.end();  
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(30000);  //Send a request every 30 seconds
 
}
