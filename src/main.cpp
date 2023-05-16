#include <config.h>

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages)
{
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++)
  {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID)
    {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start")
    {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Monitoring kebakaran.\n\n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/state")
    {
      bot.sendMessage(chat_id, "LED is ON", "");
    }
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, ledState);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (millis() > lastTimeBotRan + botRequestDelay)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

  // MQ2
  int mq2Value = digitalRead(mq2);
  Serial.print("MQ2:");
  Serial.println(mq2Value);

  // FLAME SENSOR
  int flameValue = digitalRead(flame);
  Serial.print("FLAME:");
  Serial.println(flameValue);

  if (mq2Value == 1 || flameValue == 0)
  {
    digitalWrite(buzz, HIGH);
    ledState = HIGH;
    bot.sendMessage(CHAT_ID, "Kebakaran Terdeteksi", "");
  }
  else
  {
    digitalWrite(buzz, LOW);
    ledState = LOW;
  }
}
