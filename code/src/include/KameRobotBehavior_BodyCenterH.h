#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_BodyCenterH : public KameRobotBehavior {
    public:
        KameRobotBehavior_BodyCenterH(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("center body horizontal");
            setDescription("Centers the body horizontally.");
        }
        virtual ~KameRobotBehavior_BodyCenterH() override {}

        void run(const String* value) override {
            getRobot()->getFrontLeftLeg()->centerHorizontal();
            getRobot()->getFrontRightLeg()->centerHorizontal();
            getRobot()->getBackLeftLeg()->centerHorizontal();
            getRobot()->getBackRightLeg()->centerHorizontal();
        }
};