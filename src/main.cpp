#include <USB.h>
#include <USBHIDConsumerControl.h>
#include "Arduino.h"
#include <USBHIDKeyboard.h>

#define BTN_VOL_UP        10  // GPIO dla podgłaśniania
#define BTN_VOL_DOWN      11  // GPIO dla ściszania
#define BTN_MUTE          12  // GPIO dla wyciszania
#define BTN_MUTE_DISCORD  13  // GPIO dla wyciszania Discorda


USBHIDConsumerControl ConsumerControl;
USBHIDKeyboard Keyboard;
USBHID HID;

bool muteState = false;  // Przechowuje stan mute
bool discordMuteState = false;  // Przechowuje stan mute Discorda

void setup() {
    Serial.begin(115200);
    pinMode(BTN_VOL_UP, INPUT_PULLUP);
    pinMode(BTN_VOL_DOWN, INPUT_PULLUP);
    pinMode(BTN_MUTE, INPUT_PULLUP);
    pinMode(BTN_MUTE_DISCORD, INPUT_PULLUP);

    USB.begin();
    ConsumerControl.begin();
    Keyboard.begin();
    Serial.println("ESP32-S3 jako USB Audio");
}

void loop() {
    static bool lastMuteState = HIGH;
    static bool lastDiscordMuteState = HIGH;

    if (digitalRead(BTN_VOL_UP) == LOW) {  
        Serial.println("Volume Up");
        ConsumerControl.press(CONSUMER_CONTROL_VOLUME_INCREMENT);
        delay(10);
        ConsumerControl.release();
        delay(100);
    }

    if (digitalRead(BTN_VOL_DOWN) == LOW) {  
        Serial.println("Volume Down");
        ConsumerControl.press(CONSUMER_CONTROL_VOLUME_DECREMENT);
        delay(10);
        ConsumerControl.release();
        delay(100);  
    }

    bool currentMuteState = digitalRead(BTN_MUTE);
    if (currentMuteState == LOW && lastMuteState == HIGH) {
        muteState = !muteState;
        Serial.println(muteState ? "Mute ON" : "Mute OFF");
        ConsumerControl.press(CONSUMER_CONTROL_MUTE);
        delay(10);
        ConsumerControl.release();
        delay(10);
    }
    lastMuteState = currentMuteState;

    /*
    TODO
    */

}
