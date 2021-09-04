# include "timer.h"

class WatchDog {
private:
    Timer timer;
    float dt;

public:
    void monitorExecution(void (*loopIteration)());
};