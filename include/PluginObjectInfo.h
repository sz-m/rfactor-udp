//---------------------------------------------------------------------------
//  PluginObjectInfo
//    - interface used by plugin info classes.
//      the purpose of the plugin info classes is to allow the game to get 
//      information about and instantiate the plugin objects contained in 
//      a dll without needing to know anything about the PO in advance
//---------------------------------------------------------------------------
#pragma once

class PluginObjectInfo
{
public:
	virtual ~PluginObjectInfo() {};
	virtual const char* GetName() const = 0;
	virtual const char* GetFullName() const = 0;
	virtual const char* GetDesc() const = 0;
	virtual const unsigned GetType() const = 0;
	virtual const char* GetSubType() const = 0;
	virtual const unsigned GetVersion() const = 0;
	virtual void* Create() const = 0;
};