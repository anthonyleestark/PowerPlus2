#pragma once

#ifndef _GLOBAL_H
#define _GLOBAL_H

#include "Core.h"
#include "Language.h"

#define LANGUAGE_VIET 0x00000
#define LANGUAGE_ENG  0x00001

// Static global namespace objects list
static CONFIGURATION stConfig, stSavedConfig;
static SCHEDULE stSchedule;
static NOTIFYICONDATA stNotifyIcon;
static UINT nLanguage;
static ACTION stAction;

#endif // !_GLOBAL_H
