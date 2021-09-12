# include "serial.h"

# include <SoftwareSerial.h>
# include <ArduinoJson.h>
# include <string>
# include <vector>

# include "dataTypes.h"
# include "config.h"


SerialProxy::SerialProxy(){
    Serial.begin(SERIAL_BAUD_RATE);
}

std::string SerialProxy::readJson(){
    std::string jsonString;
    while(Serial.available()){
        char ch = (char)Serial.read();
        jsonString += ch;
    } 
    return jsonString;
}

void SerialProxy::writeJson(std::string string){
    Serial.print(string.c_str());
}

State SerialProxy::setReference(JsonObject data){
    State reference;
    reference.x = data["x"];
    reference.y = data["y"];
    reference.z = data["z"];
    reference.rx = data["rx"];
    reference.ry = data["ry"];
    reference.rz = data["rz"];
    reference.velX = data["velX"];
    reference.velY = data["velY"];
    reference.velZ = data["velZ"];
    reference.velrx = data["velrx"];
    reference.velry = data["velry"];
    reference.velrz = data["velrz"];
    reference.accX = data["accX"];
    reference.accY = data["accY"];
    reference.accZ = data["accZ"];
    reference.accrx = data["accrx"];
    reference.accry = data["accry"];
    reference.accrz = data["accrz"];

    return reference;
}

void SerialProxy::executeCommand(IMU& imu, State& reference, ControlOutput& ControlOutput){
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
    if (doc["Command"] == "SetReference"){
        Serial.print("SetReference received... \n");
        reference = this->setReference(doc["Data"]);
    }
}