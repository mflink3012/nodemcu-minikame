#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_BodyCenterV : public KameRobotBehavior {
    public:
        KameRobotBehavior_BodyCenterV(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("center body vertical");
            setDescription("Centers the body vertically.");
        }
        virtual ~KameRobotBehavior_BodyCenterV() override {}

        void run(const String* value) override {
            getRobot()->getFrontLeftLeg()->centerVertical();
            getRobot()->getFrontRightLeg()->centerVertical();
            getRobot()->getBackLeftLeg()->centerVertical();
            getRobot()->getBackRightLeg()->centerVertical();
        }
};