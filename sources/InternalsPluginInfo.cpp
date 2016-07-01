#include "../include/InternalsPluginInfo.h"
#include "../rfudp/include/rfudp.h"
#include <cstdio>

InternalsPluginInfo::InternalsPluginInfo()
{
	sprintf_s(m_szFullName, 128, "%s - %s", "rfudp", InternalsPluginInfo::GetName());
}

const char* InternalsPluginInfo::GetName() const {
	return rfudp::GetName();
}

const char* InternalsPluginInfo::GetFullName() const
{
	return m_szFullName;
}

const char* InternalsPluginInfo::GetDesc() const
{
	return "Simple udp bridge.";
}

const unsigned InternalsPluginInfo::GetType() const
{
	return rfudp::GetType();
}

const char* InternalsPluginInfo::GetSubType() const
{
	return rfudp::GetSubType();
}

const unsigned InternalsPluginInfo::GetVersion() const
{
	return rfudp::GetVersion();
}

void* InternalsPluginInfo::Create() const
{
	return new rfudp();
}
