#pragma once

#include "PluginObject.h"

#include "TelemInfo.h"
#include "GraphicsInfo.h"

// Note: use class InternalsPlugin   for GetVersion()==1,
//       use class InternalsPluginV2 for GetVersion()==2
class InternalsPlugin : public PluginObject
{
public:

	// General internals methods
	InternalsPlugin() {}
	virtual ~InternalsPlugin() {}

	virtual void Startup() {}                                    // game startup
	virtual void Shutdown() {}                                   // game shutdown

	virtual void EnterRealtime() {}                              // entering realtime (where the vehicle can be driven)
	virtual void ExitRealtime() {}                               // exiting realtime

	// GAME OUTPUT
	virtual bool WantsTelemetryUpdates() { return(false); }    // whether we want telemetry updates
	virtual void UpdateTelemetry(const TelemInfo &info) {}     // update plugin with telemetry info

	virtual bool WantsGraphicsUpdates() { return(false); }     // whether we want graphics updates
	virtual void UpdateGraphics(const GraphicsInfo &info) {}   // update plugin with graphics info

	// GAME INPUT
	virtual bool HasHardwareInputs() { return(false); }        // whether plugin has hardware plugins
	virtual void UpdateHardware(const float fDT) {}            // update the hardware with the time between frames
	virtual void EnableHardware() {}                             // message from game to enable hardware
	virtual void DisableHardware() {}                            // message from game to disable hardware

	// See if the plugin wants to take over a hardware control.  If the plugin takes over the
	// control, this method returns true and sets the value of the float pointed to by the
	// second arg.  Otherwise, it returns false and leaves the float unmodified.
	virtual bool CheckHWControl(const char * const controlName, float &fRetVal) { return false; }

	virtual bool ForceFeedback(float &forceValue) { return(false); } // alternate force feedback computation - return true if editing the value
};