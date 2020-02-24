#pragma once

class DCMotor
{
public:
	DCMotor(){};
	DCMotor(int id, int expansionId)
	{
		_id = id;
		_expansionId = expansionId;
	}

	void move(long power);
	void stop();
	void setTarget(long speed, long target);
	void setDegree(long speed, long degree);
	void setInvert(long invert);
	long readEncoderDegree();
	void resetEncoder();

private:
	int _id;
	int _expansionId = 0;
};
