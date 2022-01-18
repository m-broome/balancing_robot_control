# ifndef COMMANDS_H
# define COMMANDS_H

# include "config.h"
# include "robot.h"
# include <ArduinoJson.h>
# include <string>


class Commands
{
    public:
        bool executeCommand(StaticJsonDocument<JSON_DOCUMENT_SIZE> json, Robot&robot);

    private:
        void setBalanceAngle(const JsonObject& payload, Robot& robot);
        
        void setPositionHold(const JsonObject& payload, Robot& robot);
        
        void setMotorEnable(const JsonObject& payload, Robot& robot);
        
        void setLinearSpeed(const JsonObject& payload, Robot& robot);
        
        void setAngularSpeed(const JsonObject& payload, Robot& robot);
        
        void setCombinedSpeed(const JsonObject& payload, Robot& robot);
        
        void setLinearPosition(const JsonObject& payload, Robot& robot);
        
        void setAngularPosition(const JsonObject& payload, Robot& robot);
        
        void setCombinedPosition(const JsonObject& payload, Robot& robot);
};

# endif