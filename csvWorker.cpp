#include "csvWorker.h"
#include <iostream>

csvWorker::csvWorker(const std::string& fileAdr)
{
	_file.open(fileAdr);
}

void csvWorker::ReadCSV()
{
	while (_file.good())
	{
		std::string line;
		int a;
		_file >> a;
		_file.ignore(1);
		std::getline(_file, line);
		
		if (_file.eof()) {
			break;
		}
		_mapDat[line] = a;
	}
}

void csvWorker::PrintDataTable()
{
	std::cout << "----------------" << std::endl;
	for (const auto& [key, value] : _mapDat)
	{
		if (key != "nan") 
		{
			std::cout << "|| " << key << "\t ||" << value << "\t||" << std::endl;

			std::cout << "----------------" << std::endl;
		}
	}
}

std::map<std::string, int> csvWorker::MapCmd()
{

	return _mapDat;
}
