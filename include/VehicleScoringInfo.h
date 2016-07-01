#pragma once

struct VehicleScoringInfo
{
	char mDriverName[32];          // driver name
	char mVehicleName[64];         // vehicle name
	short mTotalLaps;              // laps completed
	signed char mSector;           // 0=sector3, 1=sector1, 2=sector2 (don't ask why)
	signed char mFinishStatus;     // 0=none, 1=finished, 2=dnf, 3=dq
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
	// no current laptime because it instantly becomes "last"

	short mNumPitstops;            // number of pitstops made
	short mNumPenalties;           // number of outstanding penalties
};