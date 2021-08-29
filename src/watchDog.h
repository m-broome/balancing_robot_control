# include "timer.h"

class WatchDog {
private:
    Timer timer;
    double_t dt;

public:
    void monitorExecution(void (*loopIteration)());
};