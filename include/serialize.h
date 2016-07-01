#pragma once

struct s_ScoringInfo
{
	char mTrackName[64];           // current track name

	long mSession;                 // current session
	long mNumVehicles;             // current number of vehicles
	long  mMaxLaps;                // maximum laps

	float mCurrentET;              // current time
	float mEndET;                  // ending time
	float mLapDist;                // distance around track
};

struct s_TelemInfo
{

	char mVehicleName[64];         // current vehicle name
	char mTrackName[64];           // current track name

	long mLapNumber;			   // current lap number
	long mGear;                    // -1=reverse, 0=neutral, 1+=forward gears

	float mDeltaTime;              // time since last update (seconds)         
	float mLapStartET;             // time this lap was started
	float mEngineRPM;              // engine RPM
	float mEngineWaterTemp;        // Celsius
	float mEngineOilTemp;          // Celsius
	float mClutchRPM;              // clutch RPM
	float mUnfilteredThrottle;     // ranges  0.0-1.0
	float mUnfilteredBrake;        // ranges  0.0-1.0
	float mUnfilteredSteering;     // ranges -1.0-1.0 (left to right)
	float mUnfilteredClutch;       // ranges  0.0-1.0
	float mSteeringArmForce;       // force on steering arms
	float mVelocity;
};

struct s_VehicleScoringInfo
{
	char mDriverName[32];          // driver name
	char mVehicleName[64];         // vehicle name
	
	signed char mSector;           // 0=sector3, 1=sector1, 2=sector2 (don't ask why)
	signed char mFinishStatus;     // 0=none, 1=finished, 2=dnf, 3=dq
	
	short mNumPitstops;            // number of pitstops made
	short mNumPenalties;           // number of outstanding penalties
	short mTotalLaps;              // laps completed
	short mDriverNum;

	float mLapDist;                // current distance around track
	float mPathLateral;            // lateral position with respect to *very approximate* "center" path
	float mTrackEdge;              // track edge (w.r.t. "center" path) on same side of track as vehicle
	float mBestSector1;            // best sector 1
	float mBestSector2;            // best sector 2 (plus sector 1)
	float mBestLapTime;            // best lap time
	float mLastSector1;            // last sector 1
	float mLastSector2;            // last sector 2 (plus sector 1)
	float mLastLapTime;            // last lap time
	float mCurSector1;             // current sector 1 if valid
	float mCurSector2;             // current sector 2 (plus sector 1) if valid
};

void serialize_s_ScoringInfo(struct s_ScoringInfo* si, char *data);
void serialize_s_TelemInfo(struct s_TelemInfo* ti, char *data);
void serialize_s_VehicleInfo(struct s_VehicleScoringInfo* vi, char *data);