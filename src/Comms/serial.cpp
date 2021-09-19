# include "serial.h"

# include <SoftwareSerial.h>
# include <ArduinoJson.h>
# include <string>
# include <vector>

# include "dataTypes.h"
# include "config.h"
# include "startup.h"


SerialProxy::SerialProxy(){
    Serial.begin(SERIAL_BAUD_RATE);
}

std::string SerialProxy::readJson(){
    std::string jsonString;
    while(Serial.available()){
        jsonString += (char)Serial.read();
    } 
    return jsonString;
}

void SerialProxy::writeJson(std::string string){
    Serial.print(string.c_str());
}

void SerialProxy::executeCommand(StartUp& startup, IMU& imu, State& reference, ControlOutput& ControlOutput){
    // read data from serial buffer 
    std::string jsonString = this->readJson();

    // parse string to json object 
    StaticJsonDocument<JSON_DOCUMENT_SIZE> doc;
    DeserializationError error = deserializeJson(doc, jsonString);
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
    } 

    // execute command
    std::string command = doc["Command"];
    if (command == "SetReference"){
        Serial.print("SetReference received... \n");
        this->setReference(doc["Payload"], reference);
    }
    else if (command == "SetBalanceAngle"){
        Serial.print("SetBalanceAngle received... \n");
        this->setBalanceAngle(doc["Payload"], reference);
    }
    else if (command == "SetMotorEnable"){
        Serial.print("SetMotorEnable received... \n");
        this->setMotorEnable(doc["Payload"], startup);
    }
    else if (command == "SetPositionHold"){
        Serial.print("SetPositionHold received... \n");
        this->setPositionHold(doc["Payload"], reference);
    }
    // Speed Commands
    else if (command == "SetLinearSpeed"){
        Serial.print("SetLinearSpeed received... \n");
        this->setLinearSpeed(doc["Payload"], reference);
    }
    else if (command == "SetAngularSpeed"){
        Serial.print("SetAngularSpeed received... \n");
        this->setAngularSpeed(doc["Payload"], reference);
    }
    else if (command == "SetCombinedSpeed"){
        Serial.print("SetCombinedSpeed received... \n");
        this->setCombinedSpeed(doc["Payload"], reference);
    }
    // Position Commands 
    else if (command == "SetLinearPosition"){
        Serial.print("SetLinearPosition received... \n");
        this->setLinearPosition(doc["Payload"], reference);
    }
    else if (command == "SetAngularPosition"){
        Serial.print("SetAngularPosition received... \n");
        this->setAngularPosition(doc["Payload"], reference);
    }
    else if (command == "SetCombinedPosition"){
        Serial.print("SetCombinedPosition received... \n");
        this->setCombinedPosition(doc["Payload"], reference);
    }
    else 
        Serial.print("Command not recognised. Please check syntax");
}

void SerialProxy::setReference(JsonObject payload, State& reference){
    reference.x = payload["x"];
    reference.ry = payload["ry"];
    reference.rz = payload["rz"];
    reference.velX = payload["velX"];
    reference.velrz = payload["velrz"];
}

void SerialProxy::setMotorEnable(JsonObject payload, StartUp& startUp){
    if (payload["state"] == true){
        startUp.enableMotors();
    }
    else if (payload["state"] == false){
        startUp.disableMotors();
    }
}

void SerialProxy::setPositionHold(JsonObject payload, State& reference){
    if (payload["state"] == true){
        reference.balanceControl = false;
        reference.positionControl = true;
        reference.speedControl = false;
        reference.x = 0;
    }
    else{
        reference.balanceControl = false;
        reference.positionControl = false;
        reference.speedControl = true;
        reference.velX = 0;
    }
}

void SerialProxy::setBalanceAngle(JsonObject payload, State& reference){
    reference.balanceControl = true;
    reference.positionControl = false;
    reference.speedControl = false;
    reference.ry = payload["ry"];
}

void SerialProxy::setLinearSpeed(JsonObject payload, State& reference){
    reference.balanceControl = false;
    reference.positionControl = false;
    reference.speedControl = true;
    reference.velX = payload["velX"];
}

void SerialProxy::setAngularSpeed(JsonObject payload, State& reference){
    reference.balanceControl = false;
    reference.positionControl = false;
    reference.speedControl = true;
    reference.velrz = payload["velrz"];
}

void SerialProxy::setCombinedSpeed(JsonObject payload, State& reference){
    reference.balanceControl = false;
    reference.positionControl = false;
    reference.speedControl = true;
    reference.velX = payload["velX"];
    reference.velrz = payload["velrz"];
}

void SerialProxy::setLinearPosition(JsonObject payload, State& reference){
    reference.balanceControl = false;
    reference.positionControl = true;
    reference.speedControl = false;
    reference.x = payload["x"];
}

void SerialProxy::setAngularPosition(JsonObject payload, State& reference){
    reference.balanceControl = false;
    reference.positionControl = true;
    reference.speedControl = false;
    reference.rz = payload["rz"];
}

void SerialProxy::setCombinedPosition(JsonObject payload, State& reference){
    reference.balanceControl = false;
    reference.positionControl = true;
    reference.speedControl = false;
    reference.x = payload["x"];
    reference.rz = payload["rz"];
}