#pragma once

#include <Servo.h>
#include "KameRobotConfig.h"

class KameRobotServo : public Servo {
    protected:
        KameRobotConfig* config;
        KameRobotConfig::SERVOS servoId;
    public:
        KameRobotServo(KameRobotConfig* config, KameRobotConfig::SERVOS servoId) {
            this->config = config;
            this->servoId = servoId;
        }
        virtual ~KameRobotServo() {
            detach();
        }

        KameRobotConfig::SERVOS getServoId() {
            return servoId;
        }

        int getMaxAngle() {
            return config->getMaxAngle(servoId);
        }

        void attach() {
            Servo::attach(config->getServoPin(servoId), config->getServoMinUs(servoId), config->getServoMaxUs(servoId));
        }

        void reset() {
            write(0);
        }

        void center() {
            write(getMaxAngle() / 2);
        }

        void write(int value) {
            if (!attached()) {
                attach();
            }

            // Avoid negative values and going above the maximum angle
            value = constrain(value, 0, getMaxAngle());

            if (!config->isInverted(servoId)) {
                Servo::write(value);
            } else {
                Servo::write(getMaxAngle() - value);
            }
        }
};