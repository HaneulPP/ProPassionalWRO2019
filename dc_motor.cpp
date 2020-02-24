#pragma once
#include "dc_motor.h"
#include <PRIZM.h>

extern PRIZM prizm;
extern EXPANSION expansion;

void DCMotor::move(long power)
{
	if (_expansionId == 0)
	{
		prizm.setMotorPower(_id, power);
		return;
	}
	expansion.setMotorPower(_expansionId, _id, power);
}

void DCMotor::stop()
{
	if (_expansionId == 0)
	{
		prizm.setMotorPower(_id, 0);
		return;
	}
	expansion.setMotorPower(_expansionId, _id, 0);
}

void DCMotor::setTarget(long speed, long target)
{
	if (_expansionId == 0)
	{
		prizm.setMotorTarget(_id, speed, target);
		return;
	}
	expansion.setMotorTarget(_expansionId, _id, speed, target);
}

void DCMotor::setDegree(long speed, long degree)
{
	if (_expansionId == 0)
	{
		prizm.setMotorDegree(_id, speed, degree);
		return;
	}
	expansion.setMotorDegree(_expansionId, _id, speed, degree);
}

void DCMotor::setInvert(long invert)
{
	if (_expansionId == 0)
	{
		prizm.setMotorInvert(_id, invert);
		return;
	}
	expansion.setMotorInvert(_expansionId, _id, invert);
}

long DCMotor::readEncoderDegree()
{
	if (_expansionId == 0)
	{
		return prizm.readEncoderDegrees(_id);;
	}
	return expansion.readEncoderDegrees(_expansionId, _id);
}

void DCMotor::resetEncoder()
{
	if (_expansionId == 0)
	{
		prizm.resetEncoder(_id);
		return;
	}
	expansion.resetEncoder(_expansionId,_id);
}