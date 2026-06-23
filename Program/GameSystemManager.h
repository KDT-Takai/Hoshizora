#pragma once
#include <iostream>
#include <map>

template <typename T>
class GameSystemManager
{
private:
	std::map<std::string, std::unique_ptr<T>> gamesystem;

public:

};