#include "TerminalFnct.h"
#include <iostream>
#include "ComPortInit.h"
#include <chrono>
#include <mutex>
#include <Windows.h>
void GetHelp()
{
		//_state->GetHelp(this);
		std::cout << "==========================================" << std::endl;
		std::cout << "    Help menu. It is list of command		" << std::endl;
		std::cout << "==========================================" << std::endl;
		std::cout << "-h		- help							" << std::endl;
		std::cout << "-r name	- read data name				" << std::endl;
		std::cout << "-w name	- w data name					" << std::endl;
		std::cout << "-ld		- data list						" << std::endl;
		std::cout << "-exit		- exit							" << std::endl;
		std::cout << "-ocp		- open com port					" << std::endl;
		std::cout << "-scp		- setting com port				" << std::endl;
		std::cout << "-cprinit	- com port reinit				" << std::endl;
		std::cout << "==========================================" << std::endl;
}

void ReadParam(const CMDMapping& inpMap)
{
	/*std::cout << "Choose one of this parameter for readng:" << std::endl;
	char cmdRead = 'r';
	SendCmd(&cmdRead);
	for (const auto& [key, value] : inpMap.GetMapping())
	{
		std::cout << "Name parameters\t" << key << "\tcommands\t" << "-" << key << std::endl;
	}

	std::string cmd;
	std::getline(std::cin, cmd);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	SendCmd(&cmdRead);
	if (inpMap.CheckExistingElement(cmd))
	{
		char tmp = (inpMap.GetMapping()[cmd] + 30);
		//SendCmd(&tmp);
	}
	else
	{
		std::cout << "Uncnown cmd" << std::endl;
	}
	*/

	std::cout << "Choose one of this parameter for readng:" << std::endl;
	char cmdRead = 'r';
	SendCmd(&cmdRead);

	for (const auto& [key, value] : inpMap.GetMapping())
	{
		std::cout << "Name parameters\t" << key << "\tcommands\t" << "-" << key << std::endl;
	}

	DWORD iSize = 0;
	char sReceivedChar;

	while (iSize == 0)
	{
		ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);
		if (iSize > 0)
		{
			std::cout << sReceivedChar;
			OutputDebugStringW(L"ANSWER state read switch\n");
		}
	}

	if (sReceivedChar != 'r')
	{
		std::cout << "Problem with connecting" << std::endl;
		return;
	}

	iSize = 0;
	std::string cmd;
	std::getline(std::cin, cmd);

	while (!inpMap.CheckExistingElement(cmd))
	{
		std::getline(std::cin, cmd);
		std::cout << "Uncnown cmd" << std::endl;
	}

	char tmp = (inpMap.GetMapping()[cmd] + 30);
	SendCmd(&tmp);

	iSize = 0;
	while (iSize == 0)
	{
		ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);
		if (iSize > 0)
		{
			std::cout << sReceivedChar;
			OutputDebugStringW(L"ANSWER state read switch\n");
		}
	}
	//static char sReceivedFourChar[4];

	iSize = 0;
	while (iSize < 4 || iSize == 0)
	{

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		ReadFile(hSerial, &sReceivedFourChar, 4, &iSize, 0);
		//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		if (iSize > 3)
		{
			std::cout << CreateFloatFromChar() << std::endl;
		}
	}

}

void WriteParam(const CMDMapping& inpMap)
{
	std::cout << "Choose one of this parameter for writing:" << std::endl;
	char cmdRead = 'w';
	//Send CMD to mk fow writing
	SendCmd(&cmdRead);

	for (const auto& [key, value] : inpMap.GetMapping())
	{
		std::cout << "Name parameters\t" << key << "\tcommands\t" << "-" << key << std::endl;
	}

	DWORD iSize = 0;
	char sReceivedChar;

	while (iSize == 0)
	{
		ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);
		if (iSize > 0)
		{
			std::cout << sReceivedChar;
			OutputDebugStringW(L"ANSWER state read switch\n");
		}
	}

	if (sReceivedChar != 'w')
	{
		std::cout << "Problem with sending writing command" << std::endl;
		return;
	}


	// Send num params
	iSize = 0;
	std::string cmd;
	std::getline(std::cin, cmd);

	while (!inpMap.CheckExistingElement(cmd))
	{
		std::getline(std::cin, cmd);
		std::cout << "Uncnown cmd" << std::endl;
	}

	char tmp = (inpMap.GetMapping()[cmd] + 30);
	SendCmd(&tmp);

	iSize = 0;
	while (iSize == 0)
	{
		ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);
		if (iSize > 0)
		{
			std::cout << sReceivedChar;
			OutputDebugStringW(L"ANSWER state read switch\n");
		}
	}
	//static char sReceivedFourChar[4];

	float sendedDat;
	std::cin >> sendedDat;
	write_float(sendedDat);

	/*iSize = 0;
	while (iSize < 4 || iSize == 0)
	{

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		ReadFile(hSerial, &sReceivedFourChar, 4, &iSize, 0);
		//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		if (iSize > 3)
		{
			std::cout << CreateFloatFromChar() << std::endl;
		}
	}*/
}
