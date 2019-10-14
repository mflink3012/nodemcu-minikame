#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_ServosEnable : public KameRobotBehavior {
    public:
        KameRobotBehavior_ServosEnable(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("enable servos");
            setDescription("Enables the robots servos.");
        }
        virtual ~KameRobotBehavior_ServosEnable() override {}

        void run(const String* value) override {
            getRobot()->getFrontLeftLeg()->enable();
            getRobot()->getFrontRightLeg()->enable();
            getRobot()->getBackLeftLeg()->enable();
            getRobot()->getBackRightLeg()->enable();
            getRobot()->setState(ROBOT_STATES::IDLE);
        }
};