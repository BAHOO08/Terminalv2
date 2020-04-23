#pragma once
#include <map>
#include <string>

class GlobalCmd
{
public:
	enum GlobCommands
	{
		HELP,
		RESETTING_COM,
		READ_PARAM,
		WRITE_PARAM
	};

	GlobalCmd()
	{
		_mainStMashine["-h"] = GlobCommands::HELP;
		_mainStMashine["-r"] = GlobCommands::READ_PARAM;
		_mainStMashine["-w"] = GlobCommands::WRITE_PARAM;
		_mainStMashine["-rescom"] = GlobCommands::RESETTING_COM;
	}

	bool CheckExistingElement(const std::string& key) const
	{
		return (_mainStMashine.find(key) != _mainStMashine.end());
	}

	std::map <std::string, GlobalCmd::GlobCommands> GetMap()
	{
		return _mainStMashine;
	}
private:
	std::map <std::string, GlobalCmd::GlobCommands> _mainStMashine;
};
