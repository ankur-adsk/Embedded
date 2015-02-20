/**************************************************************************

Filename    :   AttitudePIDCtrl.cpp
Content     :
Created     :   Feb 2015
Authors     :   Ankur Mohan

Copyright   :   Copyright 2015 Ankur Mohan, All Rights reserved.

Use of this software is subject to the terms of the license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "AttitudePIDCtrl.h"
#include "arduino.h"

void AttitudePIDCtrl::Reset()
{
	// Set all accumulated variables to 0
	SetErrorSum(0.0);
}

void AttitudePIDCtrl::SetSpeed(int speed)
{
	QuadSpeed = speed;
}

void AttitudePIDCtrl::SetTunings(double kp, double ki, double kd)
{
   Kp = kp;
   Ki = ki/1000;
   Kd = kd*1000;
}

void AttitudePIDCtrl::SetErrorSum(double val)
{
	Errsum = val;
}

void AttitudePIDCtrl::SetLastError(double val)
{
	LastErr = val;
}

double AttitudePIDCtrl::GetErrorSum()
{
	return Errsum;
}

double AttitudePIDCtrl::GetSetPoint()
{
	return Setpoint;
}

void AttitudePIDCtrl::SetSetPoint(double _setPoint)
{
	Setpoint = _setPoint;
}

void AttitudePIDCtrl::SetNewSetpoint(double _setPoint)
{
	TargetSetpoint = _setPoint;
	StepSize = (TargetSetpoint - Setpoint)/100;
}

double AttitudePIDCtrl::Compute(double input, double unused)
{
	// Did Setpoint change?
	if (fabs(TargetSetpoint - Setpoint) > 2 * fabs(StepSize))
	{
		Setpoint += StepSize;
	}
	/*How long since we last calculated*/
	unsigned long now = millis();
	double timeChange = (double) (now - lastTime);

	/*Compute all the working error variables*/
	double error = (Setpoint - input);
	// Start accumulating I error only when the Quad is approach lift off speed. Otherwise there could be a large accumulated
	// I error before motors start leading to erratic (and potentially dangerous behavior)
	if (QuadSpeed > 500)
	{
		Errsum += (error) * timeChange;
		// Cap Errsum
		Errsum = Errsum > 0? min(20000, Errsum):max(-20000, Errsum);
	}

	double dErr = (error - LastErr) / timeChange;
	/*Compute PID Output*/
	double currentKp = max(0, Kp * (1));
	Output = currentKp * error + Ki * Errsum + Kd * dErr;

	/*Remember some variables for next time*/
	LastErr = error;
	lastTime = now;

	return ApplySafeCheck(Output);
}

double AttitudePIDCtrl::ApplySafeCheck(double Output)
{
	if (fabs(LastOutput) > 150 && fabs(Output) > 150)
	{
		return 0;
	}
	LastOutput = Output;
	return Output;
}
