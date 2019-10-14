#pragma once

#include "KameRobot.h"

class KameRobotBehavior {
    private:
        String name;
        String description;
        KameRobot* robot;

    public:
        KameRobotBehavior(KameRobot* robot) {
            this->robot = robot;
        }
        virtual ~KameRobotBehavior() {};
        
        String getName() {
            return name;
        }
        
        String getDescription() {
            return description;
        }

        virtual void run(const String* value = NULL) = 0;

    protected:
        void setName(String n) {
            name = n;
        }

        void setDescription(String d) {
            description = d;
        }

        KameRobot* getRobot() {
            return robot;
        }
};