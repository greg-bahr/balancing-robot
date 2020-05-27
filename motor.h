#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define MOTOR_MIN_SPEED 70

class Motor
{
public:
    enum class MotorDirection
    {
        Forward,
        Reverse
    };

    Motor(int pwm, int in_one, int in_two);
    void SetPower(double power);
    void SetDirection(MotorDirection direction);

private:
    int pwm_, in_one_, in_two_;
    MotorDirection current_direction_, direction_;
};

#endif /* MOTOR_H */