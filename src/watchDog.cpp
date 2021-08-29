#include "watchDog.h"
#include "timer.h"
#include "config.h"

void WatchDog::monitorExecution(void(*loopIteration)()){
    this->timer.getElapsed(this->dt);
    if (this->dt >= 1000/LOOP_FREQUENCY ){
        while(1){};
    loopIteration();
    }
}