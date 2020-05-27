#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <Arduino.h>

class PidController
{
public:
    PidController(double kp, double ki, double kd) : kp_(kp), ki_(ki), kd_(kd), last_error_(0), target_value_(0), output_(0), last_integral_(0), last_update_time_(millis()) {}
    void SetTargetValue(double value);
    void Update(double value);
    double GetOutput();

private:
    double kp_, ki_, kd_, last_error_, target_value_, output_, last_integral_;
    unsigned long last_update_time_;
};

#endif /* PID_CONTROLLER_H */