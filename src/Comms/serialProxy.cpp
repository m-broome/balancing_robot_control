# include "serialProxy.h"

# include <SoftwareSerial.h>
# include <ArduinoJson.h>
# include <string>

# include "robot.h"
# include "config.h"
# include "commands.h"


SerialProxy::SerialProxy()
{
    Serial.begin(SERIAL_BAUD_RATE);
}

std::string SerialProxy::readJson()
{
    std::string jsonString{};

    while(Serial.available())
    {
        jsonString += (char)Serial.read();
    } 
    return jsonString;
}

void SerialProxy::writeJson(std::string string)
{
    Serial.print(string.c_str());
}

void SerialProxy::executeCommand(Robot& robot)
{
    // read data from serial buffer 
    std::string jsonString = this->readJson();

    // parse string to json object 
    StaticJsonDocument<JSON_DOCUMENT_SIZE> doc;
    
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
    }

    bool commandExecuted = commands.executeCommand(doc, robot);

    if (!commandExecuted)
        Serial.print("Command not recognised. Please check syntax\n");
}