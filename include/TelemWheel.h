#pragma once

struct TelemWheel
{
	float mRotation;               // radians/sec
	float mSuspensionDeflection;   // meters
	float mRideHeight;             // meters
	float mTireLoad;               // Newtons
	float mLateralForce;           // Newtons
	float mGripFract;              // an approximation of what fraction of the contact patch is sliding
	float mBrakeTemp;              // Celsius
	float mPressure;               // kPa
	float mTemperature[3];         // Celsius, left/center/right (not to be confused with inside/center/outside!)
};