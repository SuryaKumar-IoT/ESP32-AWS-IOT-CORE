// Import required libraries
#include <AWS_IOT.h>
#include "cert.c"
#include "WiFi.h"
// Replace with your network credentials

AWS_IOT madblocks;   // AWS_IOT instance
const char* ssid ="abhinav"; //Replace with your WiFi Name
const char* password ="abhi1827"; // Replace with your WiFi Password
char HOST_ADDRESS[]="a366shaagepcsd-ats.iot.eu-west-1.amazonaws.com"; //Replace with your AWS Custom endpoint Address

char CLIENT_ID[]= "DHT11";
char TOPIC_NAME[]= "ESP32/DHT11";
int status = WL_IDLE_STATUS;
char payload[512];

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }  
  Serial.println("Connected to wifi");
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  if(madblocks.connect(HOST_ADDRESS,CLIENT_ID)== 0) // Connect to AWS using Host Address and Client ID
    {
        Serial.println("Connected to AWS");
        delay(1000);
    }
    else
    {
        Serial.println("AWS connection failed, Check the HOST Address");
        while(1);
    }  
}
 
void loop()
{
    //Random Temperature and Humidity value generated
    float Temperature = random(20, 31);
    float Humidity = random(60,100);
    sprintf(payload,"{\"DeviceID\":DHT0125896, \"Humidity\":%f, \"Temperature\":%f}",Humidity,Temperature); // Create the payload for publishing
    if(madblocks.publish(TOPIC_NAME,payload) == 0)   // Publish the message(Temp and humidity)
    {        
        Serial.print("Publish Message:");   
        Serial.println(payload);
    }
    else
    {
        Serial.println("Publish failed");
    }
    // publish the temp and humidity every 5 seconds.
    vTaskDelay(5000 / portTICK_RATE_MS);               
  
}
