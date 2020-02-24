#pragma once
#include "movement_motors.h"

void moveStraight(MovementMotors movementMotors, long MovementSpeed)
{
	movementMotors.MoveAllMovingMotor(1, 1, -1, -1, MovementSpeed);
}

void moveBack(MovementMotors movementMotors, long MovementSpeed)
{
	movementMotors.MoveAllMovingMotor(-1,-1,1,1, MovementSpeed);
}

void moveRight(MovementMotors movementMotors, long MovementSpeed)
{
	movementMotors.MoveAllMovingMotor(1, -1, 1, -1, MovementSpeed);
}

void moveLeft(MovementMotors movementMotors, long MovementSpeed)
{
	movementMotors.MoveAllMovingMotor(-1, 1, -1, 1, MovementSpeed);
}

void turnLeft(MovementMotors movementMotors, long MovementSpeed)
{
	movementMotors.MoveAllMovingMotor(-1, -1, -1, -1, MovementSpeed);
}

void turnRight(MovementMotors movementMotors, long MovementSpeed)
{
	movementMotors.MoveAllMovingMotor(1, 1, 1, 1, MovementSpeed);
}

void turnSideLeftFront(MovementMotors movementMotors, long MovementSpeed)
{
	movementMotors.MoveAllMovingMotor(0, 0, -1, -1, MovementSpeed);
}

void turnSideRightFront(MovementMotors movementMotors, long MovementSpeed)
{
	movementMotors.MoveAllMovingMotor(1, 1, 0, 0, MovementSpeed);
}
void turnSideLeftBack(MovementMotors movementMotors, long MovementSpeed)
{
	movementMotors.MoveAllMovingMotor(0, 0, 1, 1, MovementSpeed);
}

void turnSideRightBack(MovementMotors movementMotors, long MovementSpeed)
{
	movementMotors.MoveAllMovingMotor(-1, -1, 0, 0, MovementSpeed);
}