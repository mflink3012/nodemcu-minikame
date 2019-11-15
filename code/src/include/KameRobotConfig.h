
#pragma once

#include <Servo.h>
#include <vector>

class KameRobotConfig {
    protected:
        std::vector<int> pins = {D1, D2, D3, D4, D5, D6, D7, D8};
        std::vector<bool> inverted = { true, true, true, false, false, false, false, true };
        std::vector<int> maxAngle = { 180, 180, 180, 180, 180, 180, 180, 180 };
        std::vector<uint16_t> minUs = { MIN_PULSE_WIDTH, MIN_PULSE_WIDTH, MIN_PULSE_WIDTH, MIN_PULSE_WIDTH, MIN_PULSE_WIDTH, MIN_PULSE_WIDTH, MIN_PULSE_WIDTH, MIN_PULSE_WIDTH };
        std::vector<uint16_t> maxUs = { MAX_PULSE_WIDTH, MAX_PULSE_WIDTH, MAX_PULSE_WIDTH, MAX_PULSE_WIDTH, MAX_PULSE_WIDTH, MAX_PULSE_WIDTH, MAX_PULSE_WIDTH, MAX_PULSE_WIDTH };
        unsigned int stepDuration = 200;
    public:
        enum SERVOS {
            FRONT_LEFT_TURNING_SERVO = 0,
            FRONT_LEFT_LIFTING_SERVO = 1,
            FRONT_RIGHT_TURNING_SERVO = 2,
            FRONT_RIGHT_LIFTING_SERVO = 3,
            BACK_LEFT_TURNING_SERVO = 4,
            BACK_LEFT_LIFTING_SERVO = 5,
            BACK_RIGHT_TURNING_SERVO = 6,
            BACK_RIGHT_LIFTING_SERVO = 7
        };

        KameRobotConfig() {}

        void setFrontLeftLegPins(int turningServoPin, int liftingServoPin) {
            pins[SERVOS::FRONT_LEFT_TURNING_SERVO] = turningServoPin;
            pins[SERVOS::FRONT_LEFT_LIFTING_SERVO] = liftingServoPin;
        }
        void setFrontRightLegPins(int turningServoPin, int liftingServoPin) {
            pins[SERVOS::FRONT_RIGHT_TURNING_SERVO] = turningServoPin;
            pins[SERVOS::FRONT_RIGHT_LIFTING_SERVO] = liftingServoPin;
        }
        void setBackLeftLegPins(int turningServoPin, int liftingServoPin) {
            pins[SERVOS::BACK_LEFT_TURNING_SERVO] = turningServoPin;
            pins[SERVOS::BACK_LEFT_LIFTING_SERVO] = liftingServoPin;
        }
        void setBackRightLegPins(int turningServoPin, int liftingServoPin) {
            pins[SERVOS::BACK_RIGHT_TURNING_SERVO] = turningServoPin;
            pins[SERVOS::BACK_RIGHT_LIFTING_SERVO] = liftingServoPin;
        }

        void setPulseWidth(int min, int max) {
            for (size_t i = 0; i < this->minUs.size(); ++i) {
                this->minUs[i] = min;
            }
            for (size_t i = 0; i < this->maxUs.size(); ++i) {
                this->maxUs[i] = max;
            }
        }

        void setMaxAngle(int angle) {
            for (size_t i = 0; i < this->maxAngle.size(); ++i) {
                this->maxAngle[i] = angle;
            }
        }

        int getServoPin(SERVOS servo) {
            return pins[servo];
        }

        uint16_t getServoMinUs(SERVOS servo) {
            return minUs[servo];
        }
        uint16_t getServoMaxUs(SERVOS servo) {
            return maxUs[servo];
        }

        bool isInverted(SERVOS servo) {
            return inverted[servo];
        }

        int getMaxAngle(SERVOS servo) {
            return maxAngle[servo];
        }

        unsigned int getStepDuration() {
            return stepDuration;
        }
};