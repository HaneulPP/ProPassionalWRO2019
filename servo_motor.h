#pragma once

class ServoMotor
{
public:
	ServoMotor(){};
	ServoMotor(int id, int speed)
	{
		_id = id;
		setSpeed(speed);
	}

	void setSpeed(long speed);
    void setPos(long pos);
	void setPos(long pos, long speed);
    int readServo();

private:
	int _id;
    long _speed;
};
