#ifndef SERIAL_PROXY_H
#define SERIAL_PROXY_H

# include <string>
# include <ArduinoJson.h>

# include "imu.h"
# include "robot.h"
# include "commands.h"


class SerialProxy
{
    public:
        SerialProxy();

        void executeCommand(Robot& robot);

    private:
        Commands commands;

        std::string readJson();

        void writeJson(std::string string);
};

#endif