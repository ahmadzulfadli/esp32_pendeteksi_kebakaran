#ifndef PEMADAM_CONFIG_H

#define PEMADAM_CONFIG_H

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

// Replace with your network credentials
const char *ssid = "vivo Y17";
const char *password = "alex1103";

// Initialize Telegram BOT
#define BOTtoken "6105484670:AAH_VNgSRJEd4KC5bLVNiItuDLREwYgWJj0" // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "5297735611"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int buzz = 5;
bool ledState = LOW;

// MQ2
const int mq2 = 2;

// FLAME SENSOR
const int flame = 4;

#endif