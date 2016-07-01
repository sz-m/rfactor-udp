#pragma once

#include "TelemVect3.h"
#include "TelemWheel.h"

struct TelemInfo
{
	// Time
	float mDeltaTime;              // time since last update (seconds)
	long mLapNumber;               // current lap number
	float mLapStartET;             // time this lap was started
	char mVehicleName[64];         // current vehicle name
	char mTrackName[64];           // current track name

	// Position and derivatives
	TelemVect3 mPos;               // world position in meters
	TelemVect3 mLocalVel;          // velocity (meters/sec) in local vehicle coordinates
	TelemVect3 mLocalAccel;        // acceleration (meters/sec^2) in local vehicle coordinates

	// Orientation and derivatives
	TelemVect3 mOriX;              // top row of orientation matrix (also converts local vehicle vectors into world X using dot product)
	TelemVect3 mOriY;              // mid row of orientation matrix (also converts local vehicle vectors into world Y using dot product)
	TelemVect3 mOriZ;              // bot row of orientation matrix (also converts local vehicle vectors into world Z using dot product)
	TelemVect3 mLocalRot;          // rotation (radians/sec) in local vehicle coordinates
	TelemVect3 mLocalRotAccel;     // rotational acceleration (radians/sec^2) in local vehicle coordinates

	// Vehicle status
	long mGear;                    // -1=reverse, 0=neutral, 1+=forward gears
	float mEngineRPM;              // engine RPM
	float mEngineWaterTemp;        // Celsius
	float mEngineOilTemp;          // Celsius
	float mClutchRPM;              // clutch RPM

	// Driver input
	float mUnfilteredThrottle;     // ranges  0.0-1.0
	float mUnfilteredBrake;        // ranges  0.0-1.0
	float mUnfilteredSteering;     // ranges -1.0-1.0 (left to right)
	float mUnfilteredClutch;       // ranges  0.0-1.0

	// Wheel info (front left, front right, rear left, rear right)
	float mSteeringArmForce;       // force on steering arms
	TelemWheel mWheel[4];
};