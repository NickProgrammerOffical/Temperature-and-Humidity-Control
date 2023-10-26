#include <FastBot.h>
#include <DHT.h>

#define WIFI_SSID "My SSID"
#define WIFI_PASS "Password"
#define BOT_TOKEN "0000000000:xxxxxx-xxx-xxxxxxxxx"
#define CHAT_ID "0000000000"

#define DHTtype DHT22
#define DHTpin 13

int get_started = 0;

int get_recom = 0;

String air_temp;
String air_temp_F;
String air_humidity;

String metric_sys = "C";

int mid_val_of_humidity = 0;
int mid_val_of_temp_C = 0;
int mid_val_of_temp_F = 0;

DHT dht(DHTpin, DHTtype);

FastBot bot(BOT_TOKEN);

void setup() {
  Serial.begin(115200);
  Serial.println();
  dht.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  Serial.println("Connected");
  get_started = 1;

  air_temp = String(float(dht.readTemperature()))+"°C";
  air_temp_F = String(((float(dht.readTemperature()))*1.8)+32)+"°F";
  air_humidity = String(float(dht.readHumidity()))+"%";
  
  bot.attach(newMsg);
}

void newMsg(FB_msg& msg) {
    if(get_started==1){
      bot.sendMessage("I'm online!", msg.chatID);
      bot.sendMessage("Would you like to..\n/request_data\n/get_recommendations", msg.chatID);
      get_started = 0;
    }
    if(String(msg.text)=="/get_recommendations"){
      get_recom = 1;
    }
    if(get_recom==1){
      bot.sendMessage("Select a middle value of humidity in your region.\n/less_than_40_percents\n/from_40_percents_to_70_percents\n/more_than_70_percents", msg.chatID); 
      get_recom = 0;
    }
    if(String(msg.text)=="/less_than_40_percents"){
      mid_val_of_humidity = 39;
      bot.sendMessage("Select your metric system.\n/C\n/F", msg.chatID);
    }
    if(String(msg.text)=="/from_40_percents_to_70_percents"){
      mid_val_of_humidity = 40;
      bot.sendMessage("Select your metric system.\n/C\n/F", msg.chatID);
    }
    if(String(msg.text)=="/more_than_70_percents"){
      mid_val_of_humidity = 71;
      bot.sendMessage("Select your metric system.\n/C\n/F", msg.chatID);
    }

    if(String(msg.text)=="/F"){
      metric_sys = "F";
      bot.sendMessage("Select a middle value of temperature in your region in summer. \n/less_than_75F\n/from_80F_to_90F\n/more_than_91F", msg.chatID);
    }
    if(String(msg.text)=="/C"){
      metric_sys = "C";
      bot.sendMessage("Select a middle value of temperature in your region in summer. \n/less_than_24C\n/from_27C_to_32C\n/more_than_33C", msg.chatID);
    }

    if(String(msg.text)=="/less_than_75F"){
      if(mid_val_of_humidity==39){
        bot.sendMessage("A dry air nicely affects on your skin and health. I'd recomend you to use hand cream.", msg.chatID);
      }
      if(mid_val_of_humidity==40){
        bot.sendMessage("A dry air nicely affects on your skin and health. I'd recomend you to use hand cream.", msg.chatID);
      }
      if(mid_val_of_humidity==71){
        bot.sendMessage("A humid air with low temperature doesn't affects on your health. I'd recomend you to use hand cream.", msg.chatID);
      }
    }
    if(String(msg.text)=="/from_80F_to_90F"){
      if(mid_val_of_humidity==39){
        bot.sendMessage("A dry air nicely affects on your skin and health.", msg.chatID);
      }
      if(mid_val_of_humidity==40){
        bot.sendMessage("A humid air with high temperature badly affects on your skin and health. There's a low probability of heatsroke. Use the sunscreen to protect your skin.", msg.chatID);
      }
      if(mid_val_of_humidity==71){
        bot.sendMessage("A humid air with high temperature badly affects on your skin and health. There's a probability of heatsroke. Use the sunscreen to protect your skin and wear up a hat.", msg.chatID);
      }
    }
    if(String(msg.text)=="/more_than_91F"){
      if(mid_val_of_humidity==39){
        bot.sendMessage("A dry air with high temperature badly affects on your skin and health. There's a low probability of heatsroke. Use the sunscreen to protect your skin.", msg.chatID);
      }
      if(mid_val_of_humidity==40){
        bot.sendMessage("A humid air with high temperature badly affects on your skin and health. There's a high probability of heatsroke. Use the sunscreen to protect your skin and wear up a hat.", msg.chatID);
      }
      if(mid_val_of_humidity==71){
        bot.sendMessage("A humid air with high temperature badly affects on your skin and health. There's a high probability of heatsroke. Use the sunscreen to protect your skin and wear up a hat.", msg.chatID);
      }
    }
    if(String(msg.text)=="/less_than_24C"){
      if(mid_val_of_humidity==39){
        bot.sendMessage("A dry air nicely affects on your skin and health. I'd recomend you to use hand cream.", msg.chatID);
      }
      if(mid_val_of_humidity==40){
        bot.sendMessage("A dry air nicely affects on your skin and health. I'd recomend you to use hand cream.", msg.chatID);
      }
      if(mid_val_of_humidity==71){
        bot.sendMessage("A humid air with low temperature doesn't affects on your health. I'd recomend you to use hand cream.", msg.chatID);
      }
    }
    if(String(msg.text)=="/from_27C_to_32C"){
      if(mid_val_of_humidity==39){
        bot.sendMessage("A dry air nicely affects on your skin and health.", msg.chatID);
      }
      if(mid_val_of_humidity==40){
        bot.sendMessage("A humid air with high temperature badly affects on your skin and health. There's a low probability of heatsroke. Use the sunscreen to protect your skin.", msg.chatID);
      }
      if(mid_val_of_humidity==71){
        bot.sendMessage("A humid air with high temperature badly affects on your skin and health. There's a probability of heatsroke. Use the sunscreen to protect your skin and wear up a hat.", msg.chatID);
      }
    }
    if(String(msg.text)=="/more_than_33C"){
      if(mid_val_of_humidity==39){
        bot.sendMessage("A dry air with high temperature badly affects on your skin and health. There's a low probability of heatsroke. Use the sunscreen to protect your skin.", msg.chatID);
      }
      if(mid_val_of_humidity==40){
        bot.sendMessage("A humid air with high temperature badly affects on your skin and health. There's a high probability of heatsroke. Use the sunscreen to protect your skin and wear up a hat.", msg.chatID);
      }
      if(mid_val_of_humidity==71){
        bot.sendMessage("A humid air with high temperature badly affects on your skin and health. There's a high probability of heatsroke. Use the sunscreen to protect your skin and wear up a hat.", msg.chatID);
      }
   }
   if(String(msg.text)=="/request_data"){
      bot.sendMessage("Air Temperature " + air_temp + ";\n                              " + air_temp_F + ";\nAir Humidity " + air_humidity +"", msg.chatID); 
      bot.sendMessage("Would you like to..\n/request_data\n/get_recommendations", msg.chatID);
   }

}

void loop() {
  bot.tick();
  air_temp = String(float(dht.readTemperature()))+"°C";
  air_temp_F = String(((float(dht.readTemperature()))*1.8)+32)+"°F";
  air_humidity = String(float(dht.readHumidity()))+"%";
  
  delay(500);
}
