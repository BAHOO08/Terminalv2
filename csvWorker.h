#pragma once
#include <string>
#include <map>
#include <fstream>
#include <map>
//"params.csv"
class csvWorker
{
public:
	csvWorker(const std::string& fileAdr);
	void ReadCSV();
	void WriteCSV();
	void PrintDataTable();
	std::map<std::string, int> MapCmd();
private:
	std::map<std::string, int> _mapDat;
	std::string _fileAdres;
	std::ifstream _file;
};

