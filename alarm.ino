#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

#define CASHOUT_AUDIO 1
#define STEALING_CASHOUT_AUDIO 2
#define IR_SENSOR_OUT A5

int currently_playing = 0;
int alarm_on = 1;
int stealing = 0;
unsigned long int started_stealing = 0;
const unsigned long int TIME_TO_STEAL = 7500;

SoftwareSerial soft_serial(10, 11); // RX, TX
DFRobotDFPlayerMini player;

void play_cashout_audio(){
  player.stop();
  player.loop(CASHOUT_AUDIO);
  currently_playing = CASHOUT_AUDIO;
}

void play_stealing_audio(){
  player.stop(); player.play(STEALING_CASHOUT_AUDIO);
  currently_playing = STEALING_CASHOUT_AUDIO;
}

void stop_alarm(){
  player.stop();
  alarm_on = 0;
  stealing = 0;
}

void setup() {
  soft_serial.begin(9600);
  Serial.begin(115200);
  pinMode(IR_SENSOR_OUT, INPUT);

  if (!player.begin(soft_serial)) {
    Serial.println("DFPlayer Mini not detected!");
    while (true);
  }

  player.volume(20);
  play_cashout_audio();
}

void loop() {
  int sensor_state = digitalRead(IR_SENSOR_OUT);
  if (stealing){
    unsigned long int current = millis();
    if (current - started_stealing >= TIME_TO_STEAL){
      stop_alarm();
    }
  }
  if( alarm_on ){
    if (currently_playing == CASHOUT_AUDIO){
      if (sensor_state == 0){
        started_stealing = millis();
        stealing = 1;
        play_stealing_audio();
      }
    } else{
      if (sensor_state == 1){
        stealing = 0;
        play_cashout_audio();
      }
    }
  }
}
