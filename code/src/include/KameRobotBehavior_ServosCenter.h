#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_ServosCenter : public KameRobotBehavior {
    public:
        KameRobotBehavior_ServosCenter(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("center servos");
            setDescription("Centers all available servos.");
        }
        virtual ~KameRobotBehavior_ServosCenter() override {}

        void run(const String* value) override {
            getRobot()->getFrontLeftLeg()->center();
            getRobot()->getFrontRightLeg()->center();
            getRobot()->getBackLeftLeg()->center();
            getRobot()->getBackRightLeg()->center();
        }
};