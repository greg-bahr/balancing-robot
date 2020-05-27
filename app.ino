#include "motor.h"
#include "pid_controller.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define ENA 5
#define ENB 6
#define IN1 12
#define IN2 11
#define IN3 10
#define IN4 9
#define POT_IN 5

Motor *left, *right;
PidController *pid;
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup(void)
{
    Serial.begin(9600);
    left = new Motor(ENA, IN1, IN2);
    right = new Motor(ENB, IN3, IN4);
    pid = new PidController(0.04, 0, 0);
    pid->SetTargetValue(0);

    if (!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1)
            ;
    }

    delay(1000);

    bno.setExtCrystalUse(true);
}

void loop(void)
{
    sensors_event_t event;
    bno.getEvent(&event);

    pid->Update(event.orientation.z);

    double output = pid->GetOutput();

    // Serial.print("Output: ");
    // Serial.println(output);

    left->SetPower(output);
    right->SetPower(output);
}