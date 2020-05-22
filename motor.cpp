#include "motor.h"

Motor::Motor(int pwm, int in_one, int in_two)
{
    this->pwm_ = pwm;
    this->in_one_ = in_one;
    this->in_two_ = in_two;

    pinMode(this->pwm_, OUTPUT);
    pinMode(this->in_one_, OUTPUT);
    pinMode(this->in_two_, OUTPUT);

    digitalWrite(this->in_one_, LOW);
    digitalWrite(this->in_two_, HIGH);

    analogWrite(this->pwm_, 0);
}

void Motor::SetDirection(MotorDirection direction)
{
    switch (direction)
    {
    case MotorDirection::Reverse:
        digitalWrite(this->in_one_, HIGH);
        digitalWrite(this->in_two_, LOW);
        break;
    case MotorDirection::Forward:
    default:
        digitalWrite(this->in_one_, LOW);
        digitalWrite(this->in_two_, HIGH);
    }
}

void Motor::SetPower(double power)
{
    power = constrain(power, 0, 1);
    int val = (power * (255 - MOTOR_MIN_SPEED)) + MOTOR_MIN_SPEED;
    if (power == 0)
    {
        val = 0;
    }

    analogWrite(this->pwm_, val);
}