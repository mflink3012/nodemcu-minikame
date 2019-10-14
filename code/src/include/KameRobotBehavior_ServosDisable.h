#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_ServosDisable : public KameRobotBehavior {
    public:
        KameRobotBehavior_ServosDisable(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("disable servos");
            setDescription("Disables the robots servos.");
        }
        virtual ~KameRobotBehavior_ServosDisable() override {}

        void run(const String* value) override {
            getRobot()->setState(ROBOT_STATES::IDLE);
            getRobot()->getFrontLeftLeg()->disable();
            getRobot()->getFrontRightLeg()->disable();
            getRobot()->getBackLeftLeg()->disable();
            getRobot()->getBackRightLeg()->disable();
        }
};