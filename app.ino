#include "motor.h"
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
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup(void)
{
    Serial.begin(9600);
    left = new Motor(ENA, IN1, IN2);
    right = new Motor(ENB, IN3, IN4);

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
    /* Get a new sensor event */
    sensors_event_t event;
    bno.getEvent(&event);

    /* Display the floating point data */
    // Serial.print("X: ");
    // Serial.print(event.orientation.x, 4);
    // Serial.print("\tY: ");
    // Serial.print(event.orientation.y, 4);
    // Serial.print("\tZ: ");
    // Serial.print(event.orientation.z, 4);
    // Serial.println("");
}