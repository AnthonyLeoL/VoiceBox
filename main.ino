#include "SD.h"

#include "TMRpcm.h"
#include "SPI.h"
#include <avr/sleep.h>

#define button 2
#define led 7
#define SD_ChipSelectPin 10
#define range 39
char fileName[20];

TMRpcm tmrpcm;
void setup(){
  digitalWrite(led,HIGH);
  randomSeed(analogRead(0));
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  while(!Serial);
  Serial.print("starting...");
  if (!SD.begin(SD_ChipSelectPin)) {
  Serial.println("SD fail");
  return;
  }
  pinMode(button,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  tmrpcm.setVolume(5);
  
  play(); 
}

void play(){
  while(!SD.exists(fileName)){
    int fileToPlay = random(range);
    sprintf(fileName, "%d.wav", fileToPlay);
  }
  tmrpcm.play(fileName);
}
void loop(){
  if(!tmrpcm.isPlaying()){
    digitalWrite(led,LOW);
    sleep_enable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_cpu();
    
  }
}