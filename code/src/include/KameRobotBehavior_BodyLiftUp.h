#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_BodyLiftUp : public KameRobotBehavior {
    public:
        KameRobotBehavior_BodyLiftUp(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("lift up the body");
            setDescription("Lifts the body to the upper position.");
        }
        virtual ~KameRobotBehavior_BodyLiftUp() override {}

        void run(const String* value) override {
            // Lifting up the body means lifting down the legs (pressing legs against the floor)
            getRobot()->getFrontLeftLeg()->liftDown();
            getRobot()->getFrontRightLeg()->liftDown();
            getRobot()->getBackLeftLeg()->liftDown();
            getRobot()->getBackRightLeg()->liftDown();
        }
};