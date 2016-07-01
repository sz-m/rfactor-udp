#pragma once

#include "TelemVect3.h"
#include <windows.h>

struct GraphicsInfo              // may be expanded in the future to provide interfaces for drawing onscreen
{
	TelemVect3 mCamPos;            // camera position
	TelemVect3 mCamOri;            // camera orientation
	HWND mHWND;                    // app handle
};