# include "commands.h"
# include "robot.h"
# include "config.h"
# include <ArduinoJson.h>
# include <string>


bool Commands::executeCommand(StaticJsonDocument<JSON_DOCUMENT_SIZE> json, Robot& robot)
{
    std::string command{json["Command"]};

    if (command == "SetBalanceAngle")
    {
        Serial.print("SetBalanceAngle received... \n");
        this->setBalanceAngle(json["Payload"], robot);
    }
    else if (command == "SetMotorEnable")
    {
        Serial.print("SetMotorEnable received... \n");
        this->setMotorEnable(json["Payload"], robot);
    }
    else if (command == "SetPositionHold")
    {
        Serial.print("SetPositionHold received... \n");
        this->setPositionHold(json["Payload"], robot);
    }
    // Speed Commands
    else if (command == "SetLinearSpeed")
    {
        Serial.print("SetLinearSpeed received... \n");
        this->setLinearSpeed(json["Payload"], robot);
    }
    else if (command == "SetAngularSpeed")
    {
        Serial.print("SetAngularSpeed received... \n");
        this->setAngularSpeed(json["Payload"], robot);
    }
    else if (command == "SetCombinedSpeed")
    {
        Serial.print("SetCombinedSpeed received... \n");
        this->setCombinedSpeed(json["Payload"], robot);
    }
    // Position Commands 
    else if (command == "SetLinearPosition")
    {
        Serial.print("SetLinearPosition received... \n");
        this->setLinearPosition(json["Payload"], robot);
    }
    else if (command == "SetAngularPosition")
    {
        Serial.print("SetAngularPosition received... \n");
        this->setAngularPosition(json["Payload"], robot);
    }
    else if (command == "SetCombinedPosition")
    {
        Serial.print("SetCombinedPosition received... \n");
        this->setCombinedPosition(json["Payload"], robot);
    }
    else
    {
        return false;
    }

    return true;
}

void Commands::setMotorEnable(const JsonObject& payload, Robot& robot)
{
    bool motorEnable{payload["state"]};

    if (motorEnable){
        robot.setSleep(true);
    }
    else {
        robot.setSleep(false);
    }
}

void Commands::setPositionHold(const JsonObject& payload, Robot& robot)
{
    State reference;
    State state = robot.getState();
    bool positionHold{payload["state"]};

    if (positionHold)

    {
        reference.balanceControl = false;
        reference.positionControl = true;
        reference.speedControl = false;
        reference.x = state.x;
    }
    else
    {
        reference.balanceControl = false;
        reference.positionControl = false;
        reference.speedControl = true;
        reference.velX = state.velX;
    }

    robot.setReference(reference);
}

void Commands::setBalanceAngle(const JsonObject& payload, Robot& robot)
{
    State reference;
    reference.balanceControl = true;
    reference.positionControl = false;
    reference.speedControl = false;
    reference.ry = payload["ry"];
    robot.setReference(reference);
}

void Commands::setLinearSpeed(const JsonObject& payload, Robot& robot)
{
    State reference;
    reference.balanceControl = false;
    reference.positionControl = false;
    reference.speedControl = true;
    reference.velX = payload["velX"];
    robot.setReference(reference);
}

void Commands::setAngularSpeed(const JsonObject& payload, Robot& robot)
{
    State reference;
    reference.balanceControl = false;
    reference.positionControl = false;
    reference.speedControl = true;
    reference.velrz = payload["velrz"];
    robot.setReference(reference);
}

void Commands::setCombinedSpeed(const JsonObject& payload, Robot& robot)
{
    State reference;
    reference.balanceControl = false;
    reference.positionControl = false;
    reference.speedControl = true;
    reference.velX = payload["velX"];
    reference.velrz = payload["velrz"];
    robot.setReference(reference);
}

void Commands::setLinearPosition(const JsonObject& payload, Robot& robot)
{
    State reference;
    reference.balanceControl = false;
    reference.positionControl = true;
    reference.speedControl = false;
    reference.x = payload["x"];
    robot.setReference(reference);
}

void Commands::setAngularPosition(const JsonObject& payload, Robot& robot)
{
    State reference;
    reference.balanceControl = false;
    reference.positionControl = true;
    reference.speedControl = false;
    reference.rz = payload["rz"];
    robot.setReference(reference);

}

void Commands::setCombinedPosition(const JsonObject& payload, Robot& robot)
{
    State reference;
    reference.balanceControl = false;
    reference.positionControl = true;
    reference.speedControl = false;
    reference.x = payload["x"];
    reference.rz = payload["rz"];
    robot.setReference(reference);
}



