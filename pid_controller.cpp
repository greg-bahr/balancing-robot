#include "pid_controller.h"

void PidController::SetTargetValue(double value)
{
    this->target_value_ = value;
}

double PidController::GetOutput()
{
    return this->output_;
}

void PidController::Update(double value)
{
    double error = this->target_value_ - value;

    unsigned long time = millis();
    unsigned long delta_time = time - this->last_update_time_;

    double integral = this->last_integral_ + (error * this->ki_);
    if (integral > 0.5)
    {
        integral = 0.5;
    }
    else if (integral < -0.5)
    {
        integral = -0.5;
    }

    double derivative = (error - this->last_error_) / delta_time;

    // Serial.println(this->kp_ * error, 8);
    // Serial.println(integral, 8);
    // Serial.println(this->kd_ * derivative, 8);

    this->output_ = (this->kp_ * error) + integral + (this->kd_ * derivative);

    this->last_integral_ = integral;
    this->last_error_ = error;
    this->last_update_time_ = time;

    if (error > 50 || error < -50)
    {
        this->output_ = 0;
    }
}