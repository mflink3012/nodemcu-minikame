#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_LegsAlignFrontToBack : public KameRobotBehavior {
    public:
        KameRobotBehavior_LegsAlignFrontToBack(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("align front to back");
            setDescription("Moves the legs the align them from front to back.");
        }
        virtual ~KameRobotBehavior_LegsAlignFrontToBack() override {}

        void run(const String* value) override {
            // Align the legs to the Z-axis
            getRobot()->getFrontLeftLeg()->turnRight();
            getRobot()->getFrontRightLeg()->turnLeft();
            getRobot()->getBackLeftLeg()->turnRight();
            getRobot()->getBackRightLeg()->turnLeft();
        }
};