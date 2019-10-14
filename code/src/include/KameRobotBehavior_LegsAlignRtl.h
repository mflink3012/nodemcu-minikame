#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_LegsAlignRightToLeft : public KameRobotBehavior {
    public:
        KameRobotBehavior_LegsAlignRightToLeft(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("align right to left");
            setDescription("Moves the legs the align them from right to left.");
        }
        virtual ~KameRobotBehavior_LegsAlignRightToLeft() override {}

        void run(const String* value) override {
            // Align the legs to the X-axis
            getRobot()->getFrontLeftLeg()->turnLeft();
            getRobot()->getFrontRightLeg()->turnRight();
            getRobot()->getBackLeftLeg()->turnLeft();
            getRobot()->getBackRightLeg()->turnRight();
        }
};