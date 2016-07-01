#undef UNICODE

#include <cmath>

#include "../include/rfudp.h"

#include "../../include/Debug.h"


//------------------------------
// plugin information
//------------------------------
unsigned g_uPluginID = 0;
char g_szPluginName[] = "rfudp";
unsigned g_uPluginVersion = 001;
unsigned g_uPluginObjectCount = 1;

//------------------------------
// support variables
//------------------------------
InternalsPluginInfo g_PluginInfo;
unsigned char cTelemetryCounter = 0;
unsigned char cScoringCounter = 0;
char tmp_t[128];
char tmp_s[1024];

struct s_ScoringInfo* s_si;
char data_s_si[sizeof(struct s_ScoringInfo)];

struct s_TelemInfo* s_ti;
char data_s_ti[sizeof(struct s_TelemInfo)];

struct s_VehicleScoringInfo* s_vi;
char data_s_vi[sizeof(struct s_VehicleScoringInfo)];

Debug* dbgGame;
//Debug* dbgTelemetry;
//Debug* dbgScoring;

UDP* udpTelemetry;
UDP* udpScoring;
UDP* udpVehicle;


//------------------------------
// plugin information interface
//------------------------------
extern "C" __declspec(dllexport)
const char* __cdecl GetPluginName() { return g_szPluginName; }

extern "C" __declspec(dllexport)
unsigned __cdecl GetPluginVersion() { return g_uPluginVersion; }

extern "C" __declspec(dllexport)
unsigned __cdecl GetPluginObjectCount() { return g_uPluginObjectCount; }

extern "C" __declspec(dllexport)
PluginObjectInfo* __cdecl GetPluginObjectInfo(const unsigned uIndex)
{
	switch (uIndex)
	{
	case 0:
		return &g_PluginInfo;
	default:
		return 0;
	}
}

//------------------------------
// InternalsPlugin class
//------------------------------
const char rfudp::m_szName[] = "InternalsPlugin";
const char rfudp::m_szSubType[] = "Internals";
const unsigned rfudp::m_uID = 1;
const unsigned rfudp::m_uVersion = 2; // 2 for InternalsPluginV2

PluginObjectInfo* rfudp::GetInfo() { return &g_PluginInfo; }


//------------------------------
// ;)
//------------------------------
void rfudp::Startup() {
	dbgGame = new Debug("logs/gameStatus.txt");
	//dbgTelemetry = new Debug("logs/telemetry.txt");
	//dbgScoring = new Debug("logs/scoring.txt");

	dbgGame->write("Game.Startup()");

	udpTelemetry = new UDP(27015);
	udpTelemetry->setAsBroadcast(true);
	udpTelemetry->setAsNonblocking(true);
	s_ti = new s_TelemInfo;

	dbgGame->write("udpTelemetry...");

	udpScoring = new UDP(27016);
	udpScoring->setAsBroadcast(true);
	udpScoring->setAsNonblocking(true);
	s_si = new s_ScoringInfo;

	dbgGame->write("udpScoring...");

	udpVehicle = new UDP(27017);
	udpVehicle->setAsBroadcast(true);
	udpVehicle->setAsNonblocking(true);
	

}

void rfudp::Shutdown()
{
	dbgGame->write("Game.Shutdown()");

	if (dbgGame) delete dbgGame;
	//if (dbgTelemetry) delete dbgTelemetry;
	//if (dbgScoring) delete dbgScoring;

	if (udpTelemetry) delete udpTelemetry;
	if (udpScoring) delete udpScoring;
	if (udpVehicle) delete udpVehicle;

	if (s_si) delete s_si;
	if (s_ti) delete s_ti;

}

void rfudp::EnterRealtime()
{
	dbgGame->write("Game.EnterRealtime()");
}

void rfudp::ExitRealtime()
{
	dbgGame->write("Game.ExitRealtime()");
}

void rfudp::UpdateTelemetry(const TelemInfo& info)
{
	if (!(++cTelemetryCounter % 10)) {
		strncpy(s_ti->mVehicleName, info.mVehicleName, 64);
		strncpy(s_ti->mTrackName, info.mTrackName, 64);
		s_ti->mLapNumber = info.mLapNumber;
		s_ti->mGear = info.mGear;
		s_ti->mDeltaTime = info.mDeltaTime;
		s_ti->mLapStartET = info.mLapStartET;
		s_ti->mEngineRPM = info.mEngineRPM;
		s_ti->mEngineWaterTemp = info.mEngineWaterTemp;
		s_ti->mEngineOilTemp = info.mEngineOilTemp;
		s_ti->mClutchRPM = info.mClutchRPM;
		s_ti->mUnfilteredThrottle = info.mUnfilteredThrottle;
		s_ti->mUnfilteredBrake = info.mUnfilteredBrake;
		s_ti->mUnfilteredSteering = info.mUnfilteredSteering;
		s_ti->mUnfilteredClutch = info.mUnfilteredClutch;
		s_ti->mSteeringArmForce = info.mSteeringArmForce;
		s_ti->mVelocity = 3.6f * sqrtf((info.mLocalVel.x * info.mLocalVel.x) + (info.mLocalVel.y * info.mLocalVel.y) + (info.mLocalVel.z * info.mLocalVel.z));
	
		serialize_s_TelemInfo(s_ti, data_s_ti);
		udpTelemetry->sendtoBroadcast(data_s_ti, sizeof(data_s_ti));
		
	}
}

void rfudp::UpdateScoring(const ScoringInfo& info)
{
	strncpy(s_si->mTrackName, info.mTrackName, 64);
	s_si->mSession = info.mSession;
	s_si->mNumVehicles = info.mNumVehicles;
	s_si->mMaxLaps = info.mMaxLaps;
	s_si->mCurrentET = info.mCurrentET;
	s_si->mEndET = info.mEndET;
	s_si->mLapDist = info.mLapDist;

	serialize_s_ScoringInfo(s_si, data_s_si);
	udpScoring->sendtoBroadcast(data_s_si, sizeof(data_s_si));

	//for (int v = 0; v < info.mNumVehicles; ++v)
	//{
	//	strncpy(s_vi->mDriverName, )
	//}
}

void rfudp::UpdateGraphics(const GraphicsInfo& info) {}

bool rfudp::CheckHWControl(const char* const controlName, float& fRetVal) { return false; }
bool rfudp::ForceFeedback(float& forceValue) { return false; }






