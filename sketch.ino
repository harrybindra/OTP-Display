#include <Arduino.h>
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiClientSecure.h>
 WiFiClientSecure client;
refresh_token ; //{your refresh_token. ok to get refresh_token you have to use "https://developers.google.com/oauthplayground/" hear you can get refresh_token,you  }
String client_id ; //{your client_id}
String client_secret; //{client_secret}
 String access_token_d_o; //{access_token}
  String leastid;//email id
  String  resuletnum;
ESP8266WiFiClass wifi;
Adafruit_SSD1306  display(128,64,&Wire,-1);

HTTPClient http;

  String refreshgoogletoken(){
client.connect("oauth2.googleapis.com",443);

client.println("POST /token HTTP/1.1 ");
client.println("Host:oauth2.googleapis.com");
client.println("Content-Length: 279");
client.println("Content-Type: application/x-www-form-urlencoded");
client.println();
client.println("client_id="+client_id+"&client_secret="+client_secret+"&refresh_token="+refresh_token+"&grant_type=refresh_token");

//filtering data  
  String respons = client.readString() ;
  Serial.println(respons);
respons.remove(0,respons.indexOf("\": \"")+4);
Serial.println("-------------------------------");
Serial.println(respons);
Serial.println("-------------------------------");
respons.remove(respons.indexOf("\","));
Serial.println("-------------------------------");
Serial.println(respons);
Serial.println("-------------------------------");
client.stop();  
return respons;
}

String getlestdata(){
  client.connect("gmail.googleapis.com",443);
 client.println("GET /gmail/v1/users/{Gmail}/messages?maxResults=1&q=label:{label}&access_token="+access_token_d_o+" HTTP/1.1");
 client.println("Host: gmail.googleapis.com");
    client.println();
//filtering data  
String responsoflest = client.readString();
 Serial.println("-------------------------------");
Serial.println(responsoflest);
Serial.println("-------------------------------");
responsoflest.remove(0,responsoflest.indexOf("\"id\": \"")+7);
 Serial.println("-------------------------------");
Serial.println(responsoflest);
Serial.println("-------------------------------");
responsoflest.remove(responsoflest.indexOf("\","));
 Serial.println("-------------------------------");
Serial.println(responsoflest);
Serial.println("-------------------------------");
return responsoflest;

}

String gmaildata(){
   client.connect("gmail.googleapis.com",443);
 client.println("GET /gmail/v1/users/{Gmail}/messages/"+leastid+"?format=minimal HTTP/1.1");
 client.println("Host: gmail.googleapis.com");
client.println("Authorization: Bearer "+access_token_d_o);
    client.println();
  
  //filtering data  
String responsoflest = client.readString();
 Serial.println("-------------------------------");
Serial.println(responsoflest);
Serial.println("-------------------------------");
responsoflest.remove(0,responsoflest.indexOf("Code: ")+6); //depending on your email you may have to change this part  
 Serial.println("-------------------------------");
Serial.println(responsoflest);
Serial.println("-------------------------------");
responsoflest.remove(responsoflest.indexOf(" If")); //depending on your email you may have to change this part  
 Serial.println("-------------------------------");
Serial.println(responsoflest);
Serial.println("-------------------------------");
return responsoflest;
}
void setup() {
 //connecting to wifi 
 wifi.begin("SSID","PASS");
Serial.begin(9600);
while (wifi.status() != WL_CONNECTED)
{
Serial.println(".");
delay(500);
}
Serial.print(wifi.localIP());
pinMode(14,INPUT);
//Setting up display
display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) 
  client.setInsecure();
    display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(28,28);
display.println("Starting....");
display.display();
access_token_d_o = refreshgoogletoken();
 Serial.println("-------------------------------");
Serial.println(access_token_d_o);
Serial.println("-------------------------------");
    display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(5,28);
display.println("Press the Button-->");
display.display();
}



double timeittakestodoonesycle = 0;

int tm =1;
void loop() {
  
  Serial.println("-------------------------------------------------------------------------------------------------------------------------------------");

//This if statement is to refresh access token 
//well you can remove this refresh access token after 60min you can refresh it every time the loop start but it's going to make everything slow 
if (timeittakestodoonesycle/1000 >= (3600*tm))
{
  display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(28,28);
display.println("Refreshing....");
display.display();
access_token_d_o = refreshgoogletoken();
 Serial.println("-------------------------------");
Serial.println(access_token_d_o);
Serial.println("-------------------------------");

  display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(28,28);
display.println("Refreshed");
display.display();
delay(500);
  display.clearDisplay();
display.setTextSize(2.7);
display.setTextColor(WHITE);
display.setCursor(28,28);
display.println(resuletnum);
display.display();
tm += 1;
}
if(digitalRead(14) == HIGH){
  String carantleast = leastid;
  display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(28,28);
display.println("Searching...");
display.display();
leastid = getlestdata();
 Serial.println("-----------ffffff--------------------");
 Serial.println(leastid);
Serial.println("------------ddddddd-------------------");
if(carantleast == leastid){
 display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(1,28);
display.println("Didn't find any thing new!!!!");
display.display();
}else
{
   display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(1,28);
display.println("I thing we found some thing new...");
display.display();
}

resuletnum = gmaildata();
display.clearDisplay();
display.setTextSize(2.7);
display.setTextColor(WHITE);
display.setCursor(28,28);
display.println(resuletnum);
display.display();
 Serial.println("-----------qqqqqqqq--------------------");
 Serial.println(resuletnum);
Serial.println("------------eeeeeeeee-------------------");
Serial.println("-------------------------------------------------------------------------------------------------------------------------------------");

}
Serial.println(millis()/1000);
Serial.println("-------------------------------------------------------------------------------------------------------------------------------------");

 timeittakestodoonesycle = millis();

}
