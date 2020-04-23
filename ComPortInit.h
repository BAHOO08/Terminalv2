#pragma once

#include <memory>
void SettingComPort();
void ComPortRead();
void CloseComPort();
void SendCmd(char * ch);
float CreateFloatFromChar();

#include <Windows.h>
extern 	HANDLE hSerial;
extern char sReceivedFourChar[4];