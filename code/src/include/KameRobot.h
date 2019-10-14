#pragma once

#include "KameRobotConfig.h"
#include "KameRobotLeg.h"

enum ROBOT_STATES {
    IDLE,
    DOWN,
    UP,
    WALK_FORWARD,
    WALK_BACKWARD
};

class KameRobot {
    protected:
        KameRobotLeg* frontLeftLeg;
        KameRobotLeg* frontRightLeg;
        KameRobotLeg* backLeftLeg;
        KameRobotLeg* backRightLeg;
        ROBOT_STATES robotState = ROBOT_STATES::IDLE;
    public:
        KameRobot() {}
        virtual ~KameRobot() {
            delete frontLeftLeg;
            delete frontRightLeg;
            delete backLeftLeg;
            delete backRightLeg;
        }

        void init(KameRobotConfig& config) {
            frontLeftLeg = new KameRobotLeg(&config, config.FRONT_LEFT_TURNING_SERVO, config.FRONT_LEFT_LIFTING_SERVO);
            frontRightLeg = new KameRobotLeg(&config, config.FRONT_RIGHT_TURNING_SERVO, config.FRONT_RIGHT_LIFTING_SERVO);
            backLeftLeg = new KameRobotLeg(&config, config.BACK_LEFT_TURNING_SERVO, config.BACK_LEFT_LIFTING_SERVO);
            backRightLeg = new KameRobotLeg(&config, config.BACK_RIGHT_TURNING_SERVO, config.BACK_RIGHT_LIFTING_SERVO);
        }

        void setState(ROBOT_STATES state) {
            robotState = state;
        }

        ROBOT_STATES getState() { return robotState; }

        KameRobotLeg* getFrontLeftLeg() { return frontLeftLeg; }
        KameRobotLeg* getFrontRightLeg() { return frontRightLeg; }
        KameRobotLeg* getBackLeftLeg() { return backLeftLeg; }
        KameRobotLeg* getBackRightLeg() { return backRightLeg; }
};