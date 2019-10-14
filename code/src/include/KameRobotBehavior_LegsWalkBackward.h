#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_LegsWalkBackward : public KameRobotBehavior {
    private:
        int step = 0;
    public:
        KameRobotBehavior_LegsWalkBackward(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("walk backward");
            setDescription("Moves the legs the let the robot walk backward.");
        }
        virtual ~KameRobotBehavior_LegsWalkBackward() override {}

        void run(const String* value) override {
            // TODO: Allow submission of count to let the bot walk continuously to that number of cycles
            getRobot()->setState(ROBOT_STATES::WALK_BACKWARD);
            /*
            walking-pattern is:

               ||        standalone         ||  simultaneous ||    translated
            t  || 0 | 1 | 2 | 3 | 4 | 5 | 6 || 0 | 1 | 2 | 3 ||  0 |  1 |  2 |  3
            ---||---------------------------||---------------||-------------------
            FL || >#| A | < | V |   |   |   || >#| A | < | V || ch#| lu | tl | cv
            BR ||   | > | A | <#| V |   |   || V | > | A | <#|| cv | tr | lu | ch#
            FR ||   |   | >#| A | < | V |   || < | V | >#| A || tr | cv | ch#| lu
            BL ||   |   |   | > | A | <#| V || A | <#| V | > || lu | ch#| cv | tl

            # := movement
            */
            switch (step) {
                case 0:
                    getRobot()->getFrontLeftLeg()->centerHorizontal();
                    getRobot()->getBackRightLeg()->centerVertical();
                    getRobot()->getFrontRightLeg()->turnRight();
                    getRobot()->getBackLeftLeg()->liftUp();
                    break;
                case 1:
                    getRobot()->getFrontLeftLeg()->liftUp();
                    getRobot()->getBackRightLeg()->turnRight();
                    getRobot()->getFrontRightLeg()->centerVertical();
                    getRobot()->getBackLeftLeg()->centerHorizontal();
                    break;
                case 2:
                    getRobot()->getFrontLeftLeg()->turnLeft();
                    getRobot()->getBackRightLeg()->liftUp();
                    getRobot()->getFrontRightLeg()->centerHorizontal();
                    getRobot()->getBackLeftLeg()->centerVertical();
                    break;
                case 3:
                    getRobot()->getFrontLeftLeg()->centerVertical();
                    getRobot()->getBackRightLeg()->centerHorizontal();
                    getRobot()->getFrontRightLeg()->liftUp();
                    getRobot()->getBackLeftLeg()->turnLeft();
                    break;
                default:
                    step = -1;
                    getRobot()->setState(ROBOT_STATES::IDLE);
                    break;
            }
            ++step;
        }
};