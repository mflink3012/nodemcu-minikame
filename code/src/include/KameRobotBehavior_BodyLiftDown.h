#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_BodyLiftDown : public KameRobotBehavior {
    public:
        KameRobotBehavior_BodyLiftDown(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("lift down the body");
            setDescription("Lifts the body to the lower position.");
        }
        virtual ~KameRobotBehavior_BodyLiftDown() override {}

        void run(const String* value) override {
            // Lifting down the body means lifting up the legs (releasing legs from the floor)
            getRobot()->getFrontLeftLeg()->liftUp();
            getRobot()->getFrontRightLeg()->liftUp();
            getRobot()->getBackLeftLeg()->liftUp();
            getRobot()->getBackRightLeg()->liftUp();
        }
};