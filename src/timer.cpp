#include "timer.h"
#include "Wire.h"
#include <TimeLib.h>

void Timer::start(){
    this->startt = millis();
}

void Timer::reset(){
    this->startt = millis();
}

void Timer::getElapsed(float& dt){
    dt = millis() - this->startt;
}