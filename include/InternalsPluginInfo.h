#pragma once

#include "PluginObjectInfo.h"

// This is used for app to find out information about plugin
class InternalsPluginInfo : public PluginObjectInfo
{
private:
	char m_szFullName[128];

public:
	InternalsPluginInfo();
	~InternalsPluginInfo() {}

	// from PluginObjectInfo
	virtual const char* GetName() const;
	virtual const char* GetFullName() const;
	virtual const char* GetDesc() const;
	virtual const unsigned GetType() const;
	virtual const char* GetSubType() const;
	virtual const unsigned GetVersion() const;
	virtual void* Create() const;
};