#pragma once
/*
Miuzei SG90 9G Micro Servo Motor

Mode Number：MS18

Control system: Change the pulse width
Amplifier type: Analog controller
Operating travel: 120°±10°
Maximum travel: 120°
Left&Right travelling Angle deviation: ≤6°
Centering deviation: ≤1°
Rotating direction: Counter Clockwise
Pulse width range: 900μsec → 2100μsec
Neutral position: 1500μsec
Dead band width: 7μsec

Operating Temperature Range: -10℃～50℃
Operating Voltage Range: 4.8V～6.0V

Operating speed (at no load): 0.09s±0.01s/60° (4.8V), 0.08s±0.01s/60° (6V)
Running current (at no load): 400mA±30mA (4.8V), 500mA±30mA (6V)
Stall torque (at locked): 2.0kg·cm±0.20kg·cm (4.8V), 2.2kg·cm±0.20kg·cm (6V)
Stall current (at locked): 1300mA±40mA (4.8V), 1600mA±50mA (6V)
Idle current (at stopped): 6mA±1mA (4.8V), 6mA±1mA (6V)
Running life (at no load): > 350000 Turns (4.8V), > 320000 Turns (6V)
Temperature drift (at 25°C): ≤5°C (4.8V), ≤7°C (6V)

Limit angle: 200°±1°
Weight: 9g±1g
Connector wire gauge: ＃28 PVC
Connector wire length: 250mm±5mm
Spline: 21T
Horn type: Cross,star and bar-type
Excessive play: ≤0.5°

Dimensions (L·W·H): 23mm·12.2mm·29mm
*/

#include "KameRobotConfig.h"

class KameRobotConfig_MSG90 : public KameRobotConfig {
    public:
        KameRobotConfig_MSG90() {
            setPulseWidth(900, 2100);
            setMaxAngle(120);
        }
};