#ifndef SERIAL_H
#define SERIAL_H

# include <string>
# include <ArduinoJson.h>

# include "dataTypes.h"
# include "Drivers/imu.h"
# include "startup.h"


class SerialProxy {
    
private:
    std::string readJson();
    void writeJson(std::string string);
    
    void setReference(JsonObject payload, State& reference);
    void setBalanceAngle(JsonObject payload, State& reference);
    void setPositionHold(JsonObject payload, State& reference);
    void setMotorEnable(JsonObject payload, StartUp& startup);
    void setLinearSpeed(JsonObject payload, State& reference);
    void setAngularSpeed(JsonObject payload, State& reference);
    void setCombinedSpeed(JsonObject payload, State& reference);
    void setLinearPosition(JsonObject payload, State& reference);
    void setAngularPosition(JsonObject payload, State& reference);
    void setCombinedPosition(JsonObject payload, State& reference);

public:
    SerialProxy();
    void executeCommand(StartUp& startup, IMU& imu, State& reference, ControlOutput& ControlOutput);
};

#endif