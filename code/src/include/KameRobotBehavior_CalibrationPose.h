#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_CalibrationPose : public KameRobotBehavior {
    public:
        KameRobotBehavior_CalibrationPose(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("turn into calibration pose");
            setDescription("Moves everything into a pose that eases the calibration.");
        }
        virtual ~KameRobotBehavior_CalibrationPose() override {}

        void run(const String* value) override {
            // Align the legs to the Z-axis
            getRobot()->getFrontLeftLeg()->turnRight();
            getRobot()->getFrontRightLeg()->turnLeft();
            getRobot()->getBackLeftLeg()->turnRight();
            getRobot()->getBackRightLeg()->turnLeft();
            // Lift up the legs
            getRobot()->getFrontLeftLeg()->liftUp();
            getRobot()->getFrontRightLeg()->liftUp();
            getRobot()->getBackLeftLeg()->liftUp();
            getRobot()->getBackRightLeg()->liftUp();
        }
};