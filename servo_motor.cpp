#include "servo_motor.h"
#include "dc_motor.h"
#include <PRIZM.h>

extern PRIZM prizm;

int ServoMotor::readServo()
{
    return prizm.readServoPosition(_id);
}


void ServoMotor::setSpeed(long speed)
{
    _speed = speed;
}

void ServoMotor::setPos(long pos)
{
    prizm.setServoPosition(_id,pos);
}

void ServoMotor::setPos(long pos , long speed)
{
    setSpeed(speed);
    prizm.setServoPosition(_id,pos);
}