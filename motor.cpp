#include "motor.h"

Motor::Motor(int pwm, int in_one, int in_two)
{
    this->pwm_ = pwm;
    this->in_one_ = in_one;
    this->in_two_ = in_two;

    pinMode(this->pwm_, OUTPUT);
    pinMode(this->in_one_, OUTPUT);
    pinMode(this->in_two_, OUTPUT);

    this->direction_ = MotorDirection::Forward;
    this->current_direction_ = MotorDirection::Forward;
    digitalWrite(this->in_one_, LOW);
    digitalWrite(this->in_two_, HIGH);

    analogWrite(this->pwm_, 0);
}

void Motor::SetDirection(MotorDirection direction)
{
    this->direction_ = direction;
    if (this->current_direction_ == direction)
    {
        return;
    }

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

    this->current_direction_ = direction;
}

void Motor::SetPower(double power)
{
    if (power > 0 && this->direction_ != this->current_direction_)
    {
        this->SetDirection(this->direction_);
    }
    else if (power < 0)
    {
        power = -power;

        if (this->direction_ == MotorDirection::Forward && this->current_direction_ == MotorDirection::Forward)
        {
            digitalWrite(this->in_one_, HIGH);
            digitalWrite(this->in_two_, LOW);
            this->current_direction_ = MotorDirection::Reverse;
        }
        else if (this->direction_ == MotorDirection::Reverse && this->current_direction_ == MotorDirection::Reverse)
        {
            digitalWrite(this->in_one_, LOW);
            digitalWrite(this->in_two_, HIGH);
            this->current_direction_ == MotorDirection::Forward;
        }
    }

    power = constrain(power, 0, 1);
    int val = (power * (255 - MOTOR_MIN_SPEED)) + MOTOR_MIN_SPEED;
    if (power == 0)
    {
        val = MOTOR_MIN_SPEED - 15;
    }

    analogWrite(this->pwm_, val);
}