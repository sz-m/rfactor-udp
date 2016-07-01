#include "../include/serialize.h"

void serialize_s_ScoringInfo(struct s_ScoringInfo* si, char *data)
{
	char *c = (char*)data;
	int i = 0;
	while(i < 64)
	{
		*c = si->mTrackName[i];
		c++;
		i++;
	}

	long *l = (long*)c;
	*l = si->mSession; l++;
	*l = si->mNumVehicles; l++;
	*l = si->mMaxLaps; l++;

	float *f = (float*)l;
	*f = si->mCurrentET; f++;
	*f = si->mEndET; f++;
	*f = si->mLapDist; f++;
}

void serialize_s_TelemInfo(struct s_TelemInfo* ti, char *data)
{
	char *c = (char*)data;
	int i = 0;
	while (i < 64)
	{
		*c = ti->mVehicleName[i];
		c++;
		i++;
	}
	i = 0;
	while (i < 64)
	{
		*c = ti->mTrackName[i];
		c++;
		i++;
	}

	long *l = (long*)c;
	*l = ti->mLapNumber; l++;
	*l = ti->mGear; l++;

	float *f = (float*)l;
	*f = ti->mDeltaTime; f++;
	*f = ti->mLapStartET; f++;
	*f = ti->mEngineRPM; f++;
	*f = ti->mEngineWaterTemp; f++;
	*f = ti->mEngineOilTemp; f++;
	*f = ti->mClutchRPM; f++;
	*f = ti->mUnfilteredThrottle; f++;
	*f = ti->mUnfilteredBrake; f++;
	*f = ti->mUnfilteredSteering; f++;
	*f = ti->mUnfilteredClutch; f++;
	*f = ti->mSteeringArmForce; f++;
	*f = ti->mVelocity; f++;

}


void serialize_s_VehicleInfo(struct s_VehicleScoringInfo* vi, char *data)
{
	char *c = (char*)data;
	int i = 0;
	while (i < 64)
	{
		*c = vi->mDriverName[i];
		c++;
		i++;
	}
	i = 0;
	while (i < 64)
	{
		*c = vi->mVehicleName[i];
		c++;
		i++;
	}

	*c = vi->mSector; c++;
	*c = vi->mFinishStatus; c++;

	short *s = (short*)c;
	*s = vi->mNumPitstops; s++;
	*s = vi->mNumPenalties; s++;
	*s = vi->mTotalLaps; s++;
	*s = vi->mDriverNum; s++;

	float *f = (float*)s;
	*f = vi->mLapDist; f++;
	*f = vi->mPathLateral; f++;
	*f = vi->mTrackEdge; f++;
	*f = vi->mBestSector1; f++;
	*f = vi->mBestSector2; f++;
	*f = vi->mBestLapTime; f++;
	*f = vi->mLastSector1; f++;
	*f = vi->mLastSector2; f++;
	*f = vi->mLastLapTime; f++;
	*f = vi->mCurSector1; f++;
	*f = vi->mCurSector2; f++;
	
}