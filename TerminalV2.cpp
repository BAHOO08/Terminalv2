// TerminalV2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "ComPortInit.h"
#include "CMDMapping.h"
#include "Commands.h"

#include <fstream>

#include <vector>
#include "csvWorker.h"
#include <thread>

#include <chrono>
#include <memory>
#include "TerminalFnct.h"
#include <Windows.h>
int main()
{
	GlobalCmd glSwitch;
	//Enums::GlobCommands
    CMDMapping mainMapping;
	csvWorker file("params.csv");
	file.ReadCSV();
	mainMapping.SetMapParam(file.MapCmd());
	SettingComPort();
	std::string cmd;
	 
	std::string data;

/*	std::thread readCom(ComPortRead);
	readCom.detach();*/
	std::cout << sizeof(char);
	// Reader thread
/*	std::thread consoleReader([&data]()
	{
		while (true) 
		{
			std::string tmp; // race condition
			std::getline(std::cin, tmp); // полностью извлекаем строку в переменную myName
			data = tmp;
		}
	});
	consoleReader.detach();
	*/

	while (true)
	{
		/*std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		std::cout << data << std::endl;*/

		std::getline(std::cin, data);
		 
		if (glSwitch.CheckExistingElement(data))
		{
			switch (glSwitch.GetMap()[data])
			{
			case GlobalCmd::GlobCommands::HELP:
				GetHelp();
				OutputDebugStringW(L"Help page\n");
				break;
			case GlobalCmd::GlobCommands::READ_PARAM:
				OutputDebugStringW(L"Read param page\n");
				ReadParam(mainMapping);
				break;
			case GlobalCmd::GlobCommands::RESETTING_COM:
				CloseComPort();
				OutputDebugStringW(L"Close comport\n");

				SettingComPort();
				OutputDebugStringW(L"Setting comport\n");

				std::cout << " Dont work resetting " << std::endl;
				break;
			case GlobalCmd::GlobCommands::WRITE_PARAM:
				WriteParam(mainMapping);
				break;
			default:
				break;
			}
		}

		//ComPortRead();

		OutputDebugStringW(L"Main While\n");
	}

    std::cout << "Hello World!\n";
}

