#pragma once

#include "InternalsPlugin.h"
#include "ScoringInfo.h"

class InternalsPluginV2 : public InternalsPlugin
{
public:
	// SCORING INFO
	virtual bool WantsScoringUpdates() { return(true); }
	virtual void UpdateScoring(const ScoringInfo &info) {}
};