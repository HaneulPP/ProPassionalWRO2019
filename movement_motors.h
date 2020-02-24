#pragma once
#include "dc_motor.h"
#include "servo_motor.h"
#include <Arduino.h>


struct MovementMotors
{
	MovementMotors(){};
	MovementMotors(DCMotor leftFront, DCMotor leftBack, DCMotor rightFront, DCMotor rightBack, DCMotor launching, DCMotor ballLifter ,ServoMotor ballStopperR,ServoMotor ballStopperL)
	{
		leftFrontMotor = leftFront;
		leftBackMotor = leftBack;
		rightFrontMotor = rightFront;
		rightBackMotor = rightBack;
		launchingMotor = launching;
		ballLifterMotor = ballLifter;
		ballStopperMotorR = ballStopperR;
		ballStopperMotorL = ballStopperL;
	}
	void MoveAllMovingMotor(long leftFront, long leftBack, long rightFront, long rightBack)
	{
		leftFrontMotor.move(leftFront);
		leftBackMotor.move(leftBack);
		rightFrontMotor.move(rightFront);
		rightBackMotor.move(rightBack);
	}
	void MoveAllMovingMotor(int leftFront, int leftBack, int rightFront,  int rightBack, long speed)
	{
		MoveAllMovingMotor(leftFront * speed, leftBack * speed, rightFront * speed, rightBack * speed);
	}
	void ReloadL()
	{
		ballStopperMotorL.setPos(130);
		delay(450);
		ballStopperMotorL.setPos(115);
	}
	void ReloadR()
	{
		ballStopperMotorR.setPos(45);
		delay(500);
		ballStopperMotorR.setPos(60);
	}
	void Shoot()
	{
		launchingMotor.setDegree(50, 38);
		delay(1400);
		launchingMotor.setDegree(515, -22);
		delay(500);
	}

	DCMotor leftFrontMotor;
	DCMotor leftBackMotor;
	DCMotor rightFrontMotor;
	DCMotor rightBackMotor;
	DCMotor launchingMotor;
	DCMotor ballLifterMotor;
	ServoMotor ballStopperMotorR;
	ServoMotor ballStopperMotorL;
};
