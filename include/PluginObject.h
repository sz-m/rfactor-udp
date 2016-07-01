// PluginObject
//	     - interface used by plugin classess.

#pragma once

#include "PluginObjectProperty.h"



class PluginObject
{
public:
	PluginObject() {}
	virtual ~PluginObject(){};
	virtual void Destroy() = 0;
	virtual class PluginObjectInfo* GetInfo() = 0;

	virtual unsigned GetPropertyCount() const = 0;
	virtual PluginObjectProperty* GetProperty(const unsigned uIndex) = 0;
	virtual PluginObjectProperty* GetProperty(const char* szName) = 0;
};