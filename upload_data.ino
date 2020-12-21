#include "AWS_IOT.h"
#include "WiFi.h"
#include "DHT.h"
#include "cert.c"

AWS_IOT madblocks;
DHT dht(23,DHT11);
char host[]="a366shaagepcsd-ats.iot.us-east-1.amazonaws.com";
char topic_name[]="esp_dht_iot";
char client_id[]="ESP32";
char payload[512];

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("COnnecting to WiFi..");
  dht.begin();
  delay(300);
  WiFi.begin("surya","surya1827");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println("WiFi Connected");
  delay(200);
  if(madblocks.connect(host,client_id)==0)
  {
    Serial.println("Connected to AWS IOT Core");
    delay(1000);
  }
  else
  {
    Serial.println("Error , Kindly Check Your Host Address");
    while(1);
  }  
}

void loop() 
{
  int temp=dht.readTemperature();
  int hum=dht.readHumidity();
  sprintf(payload,"{Device_ID:ESP32/IOT1,Temperature:%d,Humidity:%d}",temp,hum);
  if(madblocks.publish(topic_name,payload)==0)
  {
    Serial.println("Data Sent Successfully");
    Serial.println(payload);
  }
  else
  {
    Serial.println("Failed to Publish");
  }
  delay(5000);
}
