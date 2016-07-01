#pragma once

//  Plugin Object Property
//   - can be used to expose pluginobject settings to rFactor.  
//     In practice this feature has gone almost entirely unused

enum POPType
{
	POPTYPE_INT,
	POPTYPE_FLOAT,
	POPTYPE_STRING,
};

static char POPTypeNames[3][64] =
{
	"POPTYPE_INT",
	"POPTYPE_FLOAT",
	"POPTYPE_STRING",
};

const unsigned POP_MAXNAME = 32;
const unsigned POP_MAXDESC = 256;

struct PluginObjectProperty
{
	union
	{
		int   iValue;
		float fValue;
		char* szValue;
	};

	POPType uPropertyType;
	char szName[POP_MAXNAME];
	char szDesc[POP_MAXDESC];
};