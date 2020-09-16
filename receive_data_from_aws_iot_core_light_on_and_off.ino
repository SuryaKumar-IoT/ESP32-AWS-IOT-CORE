#include <AWS_IOT.h>
#include "cert.c"
#include <WiFi.h>

AWS_IOT madblocks;

char WIFI_SSID[]="abhinav";
char WIFI_PASSWORD[]="abhi1827";
char HOST_ADDRESS[]="a366shaagepcsd-ats.iot.eu-west-1.amazonaws.com"; //Replace with your AWS Custom endpoint Address

char CLIENT_ID[]= "Surya";//mention any name as client id
char TOPIC_NAME[]= "Surya/DEMO";//you can give of your own topic name


int status = WL_IDLE_STATUS;
int tick=0,msgCount=0,msgReceived = 0;
char payload[512];
char rcvdPayload[512];

void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
    strncpy(rcvdPayload,payLoad,payloadLen);
    rcvdPayload[payloadLen] = 0;
    msgReceived = 1;
}



void setup()
{
    Serial.begin(115200);
    delay(2000);

    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(WIFI_SSID);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        // wait 5 seconds for connection:
        delay(5000);
    }
    Serial.println("Connected to wifi");
    if(madblocks.connect(HOST_ADDRESS,CLIENT_ID)== 0)
    {
        Serial.println("Connected to AWS");
        delay(1000);

        if(0==madblocks.subscribe(TOPIC_NAME,mySubCallBackHandler))
        {
            Serial.println("Subscribe Successfull");
        }
        else
        {
            Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
            while(1);
        }
    }
    else
    {
        Serial.println("AWS connection failed, Check the HOST Address");
        while(1);
    }

    delay(2000);

}

void loop() 
{
    if(msgReceived == 1)
    {
        msgReceived = 0;
        Serial.print("Received Message:");
        Serial.println(rcvdPayload);
        if(!strcmp(rcvdPayload,"on"))
        {
          Serial.println("light On");
        }
        else if(!strcmp(rcvdPayload,"off"))
        {
          Serial.println("light OFF");
        }
        else
        {
          Serial.println("Please Send Command Properly");
        }
    } 
    vTaskDelay(1000 / portTICK_RATE_MS); 
    tick++;
}
