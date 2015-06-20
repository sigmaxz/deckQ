#include <iostream>
#include <stdint.h>
using namespace std;

uint32_t timestamp;

void handleReport(uint8_t * buffer, uint16_t length){
  //assumption: wait for buffer to contain all Bytes 
  if(length >= 7){
     uint16_t deltaX = ((buffer[4] & 0x0C) << 6) | buffer[2];
     uint16_t deltaY = ((buffer[4] & 0x30) << 4) | buffer[3];
     uint8_t buttonState = buffer[4] & 0x03;

     //assumption: there is a timestamp member variable or global
     //uint32_t timestamp maintaining the time
     uint32_t updateTimestamp =  (buffer[6] << 10) | (buffer[5] << 2) | ((buffer[4] & 0xC0) >> 6);

     //overflow detection
     if((timestamp & 0x0003ffff) > (updateTimestamp & 0x0003ffff)){
        timestamp = ((timestamp & 0xfffc0000) + 0x00040000) | updateTimestamp;
     }
  } 
}

int main(){

uint8_t * buffer = (uint8_t*) malloc(8);
*buffer = (uint8_t) 0xFF;
*(buffer+1) = (uint8_t) 0xEE;
*(buffer+2) = (uint8_t) 0xDD;
*(buffer+3) = (uint8_t) 0xCC;
*(buffer+4) = (uint8_t) 0xBB;
*(buffer+5) = (uint8_t) 0xAA;
*(buffer+6) = (uint8_t) 0x99;
*(buffer+8) = '\0';

handleReport(buffer, 7);

free(buffer);
return 0;
}
