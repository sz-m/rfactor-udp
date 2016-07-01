#pragma once

#include "VehicleScoringInfo.h"

struct ScoringInfo
{
	char mTrackName[64];           // current track name
	long mSession;                 // current session
	float mCurrentET;              // current time
	float mEndET;                  // ending time
	long  mMaxLaps;                // maximum laps
	float mLapDist;                // distance around track
	char *mResultsStream;          // results stream additions since last update (newline-delimited and NULL-terminated)

	long mNumVehicles;             // current number of vehicles
	VehicleScoringInfo *mVehicle;  // array of vehicle scoring info's
};