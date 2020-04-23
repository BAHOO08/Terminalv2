#include <iostream>
#include <Windows.h>

#include "ComPortInit.h"
#include <chrono>
#include "mutexes.h"
HANDLE hSerial;

enum class READ_STATE
{
	DO_NOTHING,
	WAIT_ANSWER_CMD,
	WAIT_FOUR_BYTE,
	CHECK_CONFIRMATIONS_PARAMS
};

READ_STATE stateReader = READ_STATE::DO_NOTHING;
void SettingComPort()
{
	std::cout << "Hello!! Write number of COM port(only number)" << std::endl;

	LPCTSTR dataCOMs[10] =
	{
		L"COM0", L"COM1", L"COM2",L"COM3",L"COM4",L"COM5",L"COM6",L"COM7",L"COM8",L"COM9"
	};

	while (true)
	{
		int comport;

		std::cin >> comport;
		for (; comport > sizeof(dataCOMs) || comport == 0; std::cin >> comport)
		{
			// Check correct form
			if (std::cin.failbit)
			{
				std::cin.clear();
				std::cin.ignore(32727, '\n');
			}

			std::cout << "This COM port not support" << std::endl;
		}

		LPCTSTR sPortName = dataCOMs[comport];

		hSerial = CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (hSerial == INVALID_HANDLE_VALUE)
		{
			if (GetLastError() == ERROR_FILE_NOT_FOUND)
			{
				std::cout << "This comport not exist. Try again\n";
			}
			else
			{
				std::cout << "some other error occurred.\n";
			}
		}
		else
		{
			std::cout << "You connected to COM " << comport << std::endl;
			break;
		}
	}

	//Setting ComPort parameters like boadrate and etc
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		std::cout << "getting state error\n";
	}


	int boudrate;

	std::cout << "Chose your boudrate" << std::endl;
	while (true)
	{
		std::cin >> boudrate;
		//cin >> boudrate;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32727, '\n');

			std::cout << "your form uncorrected" << std::endl;
		}
		else
		{
			//cout << "COM port seted on " << boudrate << endl;
			break;
		}
	}

	std::cout << "Seted boudrate " << boudrate << std::endl;

	dcbSerialParams.BaudRate = boudrate;//CBR_9600;//CBR_256000
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		std::cout << "error setting serial port state\n";
	}
}
char sReceivedFourChar[4];
void ComPortRead()
{

	DWORD iSize;
	char sReceivedChar;
	OutputDebugStringW(L"Start readComport switch\n");
	while (true)
	{

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		mtx.lock();
		switch (stateReader)
		{
		case READ_STATE::DO_NOTHING:
			//OutputDebugStringW(L"Do nothing read switch\n");

			break;
		case READ_STATE::WAIT_ANSWER_CMD:

			if(ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0));
			if (iSize > 0)
			{
				std::cout << sReceivedChar;
				stateReader = READ_STATE::CHECK_CONFIRMATIONS_PARAMS;

				OutputDebugStringW(L"ANSWER state read switch\n");
			}
			break;
		case READ_STATE::CHECK_CONFIRMATIONS_PARAMS:

			if (ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0))
			{
				if (iSize > 0)
				{
					std::cout << sReceivedChar;
					stateReader = READ_STATE::WAIT_FOUR_BYTE;
					OutputDebugStringW(L"CHECK_CONFIRMATIONS_PARAMS state read switch\n");
				}
			}
			else
			{
				std::cout << "Confirm params ERROR" << std:: endl;
			}
			break;
		case READ_STATE::WAIT_FOUR_BYTE:
			OutputDebugStringW(L"WAIT_FOUR_BYTE state read switch\n");
			ReadFile(hSerial, &sReceivedFourChar, 4, &iSize, 0);
			if (iSize > 3)
			{
				std::cout << CreateFloatFromChar() << std::endl;  
				stateReader = READ_STATE::DO_NOTHING;
			}

			break;
		default:
			break;
		}
		mtx.unlock();
	}

}

void CloseComPort()
{
	CloseHandle(hSerial);
	std::cout << "Com port closed" << std::endl;
}

void SendCmd(char * ch)
{

	mtx.lock();
	DWORD dwSize = 1;
	DWORD dwBytesWritten;
	LPOVERLAPPED ov;


	//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	BOOL iRet = WriteFile(hSerial, ch, dwSize, &dwBytesWritten, NULL);
	stateReader = READ_STATE::WAIT_ANSWER_CMD;
	mtx.unlock();


	OutputDebugStringW(L"Send cmd\n");
}

float CreateFloatFromChar()
{
	float *data = (float*)sReceivedFourChar;

	return *data;
}
