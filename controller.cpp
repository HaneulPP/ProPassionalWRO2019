#include "controller.h"
#include "movement_control.h"
#include "PRIZM.h"
#include "state.h"
#include "string.h"
#include "consts.h"

extern PS4 ps4;
extern EXPANSION expansion;
extern State state;
extern PRIZM prizm;

bool R2onPress = false;
bool liftToggle = false;
bool liftPress = false;
bool R1onPress = false;
bool L1onPress = false;
bool reloadPress = false;

void Controller::CheckKeyCombs()
{
	//shift
	if (CheckButtons(1, R2))
	{
		if (MovementKeyCheck2(SlowMovementSpeed))
		{
			state = Moving;
		}
		if (CheckButtons(1, CROSS))
		{
			if (!R2onPress)
			{
				_movementMotors.ballLifterMotor.move(-50);
				delay(200);
				R2onPress = true;
			}

			_movementMotors.ballLifterMotor.move(100);
		}
		else
		{
			_movementMotors.ballLifterMotor.stop();
			R2onPress = false;
		}
		return;
	}
	//normal
	if (MovementKeyCheck2(NormalMovementSpeed))
	{
		state = Moving;
	}

	if (CheckButtons(1, R1))
	{
		_movementMotors.ReloadR();
	}

	if (CheckButtons(1, L1))
	{
		_movementMotors.ReloadL();
	}

	if (CheckButtons(1, TRIANGLE))
	{
		_movementMotors.Shoot();
		state = reloading;
	}
	if (CheckButtons(1, CIRCLE))
	{
		Serial.println("degree:" + String(_movementMotors.launchingMotor.readEncoderDegree()));
		 _movementMotors.launchingMotor.setDegree(1000, -27);
		 delay(1000);
		 state = reloading;
	}
	if (CheckButtons(1, SQUARE))
	{
		if (!reloadPress)
		{
			//right stopper
			if (prizm.readLineSensor(3) == LOW)
			{
				_movementMotors.ballStopperMotorR.setPos(45);
				delay(500);
				_movementMotors.ballStopperMotorR.setPos(60);
			}
			//left stopper
			else
			{
				_movementMotors.ballStopperMotorL.setPos(130);
				delay(450);
				_movementMotors.ballStopperMotorL.setPos(115);
			}
		}
		reloadPress = true;
	}
	else
	{
		reloadPress = false;
	}

	if (CheckButtons(1, CROSS))
	{
		if (!liftPress)
		{
			if (!liftToggle)
			{
				liftToggle = true;
				_movementMotors.ballLifterMotor.move(100);
			}
			else
			{
				liftToggle = false;
				_movementMotors.ballLifterMotor.stop();
			}
			liftPress = true;
		}
	}
	else
	{
		liftPress = false;
	}
}

bool Controller::MovementKeyCheck(long speed)
{
	//Straight,Back
	if (GetMotorDir(LY) == 1 && GetMotorDir(RY) == 1)
	{
		Serial.println("s");
		moveStraight(_movementMotors, speed);
	}

	else if (GetMotorDir(LY) == -1 && GetMotorDir(RY) == -1)
	{
		Serial.println("b");
		moveBack(_movementMotors, speed);
	}

	//Turn
	else if (GetMotorDir(LY) == 1 && GetMotorDir(RY) == -1)
	{
		Serial.println("tr");
		turnRight(_movementMotors, speed);
	}
	else if (GetMotorDir(LY) == -1 && GetMotorDir(RY) == 1)
	{
		Serial.println("tl");
		turnLeft(_movementMotors, speed);
	}

	//SideTurn

	//Front
	else if (GetMotorDir(LY) == 1 && GetMotorDir(RY) == 0)
	{
		Serial.println("tsr");
		turnSideRightFront(_movementMotors, speed);
	}

	else if (GetMotorDir(LY) == 0 && GetMotorDir(RY) == 1)
	{
		Serial.println("tsl");
		turnSideLeftFront(_movementMotors, speed);
	}

	//Back
	else if (GetMotorDir(LY) == -1 && GetMotorDir(RY) == 0)
	{
		Serial.println("tsrf");
		turnSideRightBack(_movementMotors, speed);
	}

	else if (GetMotorDir(LY) == 0 && GetMotorDir(RY) == -1)
	{
		Serial.println("tslf");
		turnSideLeftBack(_movementMotors, speed);
	}

	//Left,Right
	else if (CheckButtons(1, LEFT))
	{
		Serial.println("l");
		moveLeft(_movementMotors, speed);
	}
	else if (CheckButtons(1, RIGHT))
	{
		Serial.println("r");
		moveRight(_movementMotors, speed);
	}
	else
	{
		_movementMotors.MoveAllMovingMotor(0, 0, 0, 0);
		return false;
	}
	return true;
}

bool Controller::MovementKeyCheck2(long speed)
{
	//Straight,Back
	if (CheckButtons(1, UP))
	{
		Serial.println("s");
		moveStraight(_movementMotors, speed);
	}

	else if (CheckButtons(1, DOWN))
	{
		Serial.println("b");
		moveBack(_movementMotors, speed);
	}

	//Turn
	else if (CheckButtons(1, RIGHT))
	{
		Serial.println("tr");
		turnRight(_movementMotors, speed);
	}
	else if (CheckButtons(1, LEFT))
	{
		Serial.println("tl");
		turnLeft(_movementMotors, speed);
	}

	// //SideTurn

	// //Front
	// else if (GetMotorDir(LY) == 1 && GetMotorDir(RY) == 0)
	// {
	// 	Serial.println("tsr");
	// 	turnSideRightFront(_movementMotors,speed);
	// }

	// else if (GetMotorDir(LY) == 0 && GetMotorDir(RY) == 1)
	// {
	// 	Serial.println("tsl");
	// 	turnSideLeftFront(_movementMotors,speed);
	// }

	// //Back
	// else if (GetMotorDir(LY) == -1 && GetMotorDir(RY) == 0)
	// {
	// 	Serial.println("tsrf");
	// 	turnSideRightBack(_movementMotors,speed);
	// }

	// else if (GetMotorDir(LY) == 0 && GetMotorDir(RY) == -1)
	// {
	// 	Serial.println("tslf");
	// 	turnSideLeftBack(_movementMotors,speed);
	// }

	//Left,Right
	else if (GetMotorDir(LX) == -1)
	{
		Serial.println("l");
		moveLeft(_movementMotors, speed);
	}
	else if (GetMotorDir(LX) == 1)
	{
		Serial.println("r");
		moveRight(_movementMotors, speed);
	}
	else
	{
		_movementMotors.MoveAllMovingMotor(0, 0, 0, 0);
		return false;
	}
	return true;
}

bool Controller::CheckButtons(int count, ...)
{
	va_list btns;
	va_start(btns, count);
	for (int i = 0; i < count; i++)
	{
		if (!ps4.Button(va_arg(btns, int)))
		{
			return false;
		}
	}
	return true;
}

inline int Controller::GetMotor(int type)
{
	return ps4.Motor(type);
}

int Controller::GetMotorDir(int type)
{
	int t = ps4.Stick(type);

	float deadzone = 20.5;
	if (t < 127.5 - deadzone)
	{
		return -1;
	}
	else if (t > 127.5 + deadzone)
	{
		return 1;
	}
	else
	{

		return 0;
	}
}
