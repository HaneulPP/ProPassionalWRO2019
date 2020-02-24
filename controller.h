
#pragma once
#include <TELEOP.h>
#include "movement_motors.h"
#include <stdarg.h>

class Controller
{
public:
  Controller(MovementMotors movementMotors)
  {
    _movementMotors = movementMotors;
  }
  void CheckKeyCombs();
  bool CheckButtons(int btn, ...);
  int GetMotor(int stick);
  int GetMotorDir(int stick);
private:
  MovementMotors _movementMotors;
  bool MovementKeyCheck(long speed);
  bool MovementKeyCheck2(long speed);
};
