#ifndef SERIAL_H
#define SERIAL_H

# include <string>
# include <ArduinoJson.h>

# include "dataTypes.h"
# include "Drivers/imu.h"


class SerialProxy {
    
private:
    std::string readJson();
    void writeJson(std::string string);
    State setReference(JsonObject data);

public:
    SerialProxy();
    void executeCommand(IMU& imu, State& state, ControlOutput& ControlOutput);
};

#endif