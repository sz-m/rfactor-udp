#pragma once

#undef UNICODE


#include "../../include/serialize.h"

#include "../../include/UDP.h"

#include "../../include/InternalsPluginInfo.h"
#include "../../include/InternalsPluginV2.h"
#include "../../include/PluginObjectType.h"

class rfudp : public InternalsPluginV2
{
private:
	float mET;
	bool mEnabled;

protected:
	const static char m_szName[];
	const static char m_szSubType[];
	const static unsigned m_uID;
	const static unsigned m_uVersion;

public:
	rfudp() {};
	~rfudp() {};

	// called from class InternalsPluginInfo to return specific information about plugin
	static const char* GetName() { return m_szName; }
	static const unsigned GetType() { return PO_INTERNALS; }
	static const char* GetSubType() { return m_szSubType; }
	static const unsigned GetVersion() { return m_uVersion; }

	// derived from base class PluginObject
	void Destroy() { Shutdown(); }
	PluginObjectInfo* GetInfo();
	unsigned GetPropertyCount() const { return 0; }
	PluginObjectProperty* GetProperty(const char*) { return 0; }
	PluginObjectProperty* GetProperty(const unsigned) { return 0; }

	// these are the functions derived from base class InternalsPlugin
	// that can be implemented
	void Startup();
	void Shutdown();

	void EnterRealtime();
	void ExitRealtime();

	bool WantsTelemetryUpdates() { return(true); }
	void UpdateTelemetry(const TelemInfo &info);

	bool WantsGraphicsUpdates() { return(false); }
	void UpdateGraphics(const GraphicsInfo &info);

	bool WantsScoringUpdates() { return(true); }
	void UpdateScoring(const ScoringInfo &info);

	bool HasHardwareInputs() { return(false); }
	void UpdateHardware(const float fDT) { mET += fDT; }
	void EnableHardware() { mEnabled = true; }
	void DisableHardware() { mEnabled = false; }

	bool CheckHWControl(const char* const controlName, float &fRetVal);
	bool ForceFeedback(float &forceValue);

};