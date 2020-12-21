#include <AWS_IOT.h>
#include <WiFi.h>
#include "cert.c"

AWS_IOT madblocks;
char host[]="a366shaagepcsd-ats.iot.us-east-1.amazonaws.com";
char topic_name[]="esp32_dht_iot";
char client_id[]="ESP32";
char r_payload[512];
int message=0;

void on_message(char *topicName,int payloadLen,char *payLoad)
{
  strncpy(r_payload,payLoad,payloadLen);
  r_payload[payloadLen]=0;
  message=1;
}
void setup()
{
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting to WiFi ");
  WiFi.begin("surya","surya1827");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
  delay(300);
  if(madblocks.connect(host,client_id)==0)
  {
    Serial.println("Connected to AWS IoT Core");
    delay(1000);
    if(madblocks.subscribe(topic_name,on_message)==0)
    {
      Serial.println("Subscribed Successfully");
    }
    else
    {
      Serial.println("Error Please Restart Again");
      while(1);
    }
  }
  else
  {
    Serial.println("Error,Check HOST Address");
    while(1);
  }
}

void loop()
{
  if(message==1)
  {
    message=0;
    Serial.print("Received Payload:");
    Serial.println(r_payload);
    delay(200);
    if(!strcmp(r_payload,"on"))
    {
      Serial.println("Led On");
      digitalWrite(2,HIGH);  
    }
    else if(!strcmp(r_payload,"off"))
    {
      Serial.println("Led Off");
      digitalWrite(2,LOW);  
    }
    else
    {
      Serial.println("No data");
    }
  }
}
