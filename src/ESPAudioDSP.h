
#ifndef __ESPAUDIODSP_H__
#define __ESPAUDIODSP_H__

#include "Board.h"
#include "BluetoothAudio.h"
#include "ClassD\ClassD.h"
#include "Screen\ScreenManager.h"
#include "ControlHandler.h"
#include "LedController.h"
#include "AudioManager.h"
#include "WifiManager.h"
#include "AudioDSP/AudioDSP.h"


extern SoftTimer testTimer; //millisecond timer
extern BluetoothAudio btAudio;
extern ClassD classD; //class
extern AudioManager audioManager;
extern AudioDSP audioDSP;

#endif