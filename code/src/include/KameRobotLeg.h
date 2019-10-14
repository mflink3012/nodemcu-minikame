#pragma once

#include "KameRobotConfig.h"
#include "KameRobotServo.h"

class KameRobotLeg {
    protected:
        // The servo for turning left and right on the y-axis
        KameRobotServo* turningServo;
        // The servo for lifting up and down on the z-axis
        KameRobotServo* liftingServo;
        KameRobotConfig* config;
    public:
        KameRobotLeg(KameRobotConfig* config, KameRobotConfig::SERVOS turningServo, KameRobotConfig::SERVOS liftingServo) {
            this->turningServo = new KameRobotServo(config, turningServo);
            this->liftingServo = new KameRobotServo(config, liftingServo);
            this->config = config;
        }
        virtual ~KameRobotLeg() {
            delete turningServo;
            delete liftingServo;
        };

        void enable() {
            this->turningServo->attach();
            this->liftingServo->attach();
        }

        void disable() {
            this->turningServo->detach();
            this->liftingServo->detach();
        }

        bool isEnabled() {
            return turningServo->attached() && liftingServo->attached();
        }

        void lift(float height) {
            height = constrain(height, 0, 100);

            liftingServo->write(height * liftingServo->getMaxAngle());
        }

        void liftUp() {
            lift(100.0f);
        }

        void liftDown() {
            lift(0.0f);
        }

        void turn(float amount) {
            amount = constrain(amount, 0, 100);

            this->turningServo->write(amount * turningServo->getMaxAngle());
        }

        void turnLeft() {
            turn(100.0f);
        }

        void turnRight() {
            turn(0.0f);
        }

        void centerHorizontal() {
            this->turningServo->center();
        }

        void centerVertical() {
            this->liftingServo->center();
        }

        void center() {
            centerHorizontal();
            centerVertical();
        }
};