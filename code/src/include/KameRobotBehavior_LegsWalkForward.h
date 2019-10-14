#pragma once

#include "KameRobotBehavior.h"

class KameRobotBehavior_LegsWalkForward : public KameRobotBehavior {
    private:
        int motion = 0;
    public:
        KameRobotBehavior_LegsWalkForward(KameRobot* robot) : KameRobotBehavior(robot) {
            setName("walk forward");
            setDescription("Moves the legs the let the robot walk forward.");
        }
        virtual ~KameRobotBehavior_LegsWalkForward() override {}

        void run(const String* value) override {
            // TODO: Allow submission of count to let the bot walk continuously to that number of cycles
            getRobot()->setState(ROBOT_STATES::WALK_FORWARD);
            /*
            walking-pattern is:

               ||        standalone         ||  simultaneous ||    translated
            t  || 0 | 1 | 2 | 3 | 4 | 5 | 6 || 0 | 1 | 2 | 3 ||  0 |  1 |  2 |  3
            ---||---------------------------||---------------||-------------------
            FL || <#| A | > | V |   |   |   || <#| A | > | V || tl#| lu | ch | cv
            BR ||   | < | A | >#| V |   |   || V | < | A | >#|| cv | ch | lu | tr#
            FR ||   |   | <#| A | > | V |   || > | V | <#| A || ch | cv | tr#| lu
            BL ||   |   |   | < | A | >#| V || A | >#| V | < || lu | tl#| cv | ch

            # := movement
            */
            switch (motion) {
                case 0:
                    getRobot()->getFrontLeftLeg()->turnLeft();
                    getRobot()->getBackRightLeg()->centerVertical();
                    getRobot()->getFrontRightLeg()->centerHorizontal();
                    getRobot()->getBackLeftLeg()->liftUp();
                    break;
                case 1:
                    getRobot()->getFrontLeftLeg()->liftUp();
                    getRobot()->getBackRightLeg()->centerHorizontal();
                    getRobot()->getFrontRightLeg()->centerVertical();
                    getRobot()->getBackLeftLeg()->turnLeft();
                    break;
                case 2:
                    getRobot()->getFrontLeftLeg()->centerHorizontal();
                    getRobot()->getBackRightLeg()->liftUp();
                    getRobot()->getFrontRightLeg()->turnRight();
                    getRobot()->getBackLeftLeg()->centerVertical();
                    break;
                case 3:
                    getRobot()->getFrontLeftLeg()->centerVertical();
                    getRobot()->getBackRightLeg()->turnRight();
                    getRobot()->getFrontRightLeg()->liftUp();
                    getRobot()->getBackLeftLeg()->centerHorizontal();
                    break;
                default:
                    motion = -1;
                    getRobot()->setState(ROBOT_STATES::IDLE);
                    break;
            }
            ++motion;
        }
};