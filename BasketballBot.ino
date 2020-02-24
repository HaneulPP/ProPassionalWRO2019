#include <PRIZM.h>
#include <Arduino.h>
#include "TELEOP.h"
#include "controller.h"
#include "motor_ids.h"
#include "movement_motors.h"
#include "state.h"

PRIZM prizm;
PS4 ps4;
Controller *controller;
MovementMotors *movementMotors;
EXPANSION expansion;
State state = Init;
bool AutoDrive = false; 

void inits()
{
	movementMotors = new MovementMotors(
		DCMotor(1, 2),//LeftFrontMotorId
		DCMotor(2, 2),//LeftBackMotorId
		DCMotor(1, 1),//RightFrontMotorId
		DCMotor(2, 1),//RightBackMotorId
		DCMotor(LaunchingMotorId, 0),
		DCMotor(BallLifterMotorId,0),
		ServoMotor(1,25),
		ServoMotor(2,115));
	controller = new Controller(*movementMotors);
}

void setup() 
{
	Serial.begin(115200);
	inits();
 	prizm.PrizmBegin();
	delay(1000);

	DCMotor lm = (*movementMotors).launchingMotor;
	lm.setDegree(15,-300);	
	(*movementMotors).ballStopperMotorR.setPos(60);
	(*movementMotors).ballStopperMotorL.setPos(100);


}

void loop() 
{
	DCMotor lm = (*movementMotors).launchingMotor;

	if (state == Init && prizm.readLineSensor(2) == LOW)
	{
		lm.resetEncoder();
		lm.stop();
		state = Idle;

		ps4.setRumble(SLOW);
		delay(250);
		ps4.setRumble(STOP);
		return;
	}

	if(state!=Init&&!AutoDrive)
	{
		(*movementMotors).launchingMotor.setDegree(50, 38);
		delay(2000);
		(*movementMotors).launchingMotor.setDegree(530, -22);
		delay(2000);
		state = reloading;
		AutoDrive = true;
	}
	
	if(state == reloading)
	{
		lm.setDegree(15, -300);
		if (prizm.readLineSensor(2) == LOW)
		{
			lm.resetEncoder();
			lm.setDegree(5,0);
			state = Idle;

			//right stopper
			if(prizm.readLineSensor(3) == LOW)
			{
				(*movementMotors).ReloadR();
			}
			//left stopper
			else
			{
				(*movementMotors).ReloadL();
			}

			ps4.setRumble(SLOW);
			delay(250);
			ps4.setRumble(STOP);
		}
		return;
	}

	ps4.getPS4();
	if (!ps4.Connected)
	{
		Serial.println("disconnected");
		return;
	}

	
	(*controller).CheckKeyCombs();
}








