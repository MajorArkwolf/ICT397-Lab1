// LuaBridgeTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include <LuaBridge/LuaBridge.h>


void Task1(lua_State* L);
void Task2(lua_State* L);
void Task3(lua_State* L);
void Task4(lua_State* L);
void Task5(lua_State* L);


using namespace luabridge;
int main()
{
	lua_State* L = luaL_newstate();
	Task1(L);
	Task2(L);
	Task3(L);
	Task4(L);
	Task5(L);
}

void Task1(lua_State* L) {
	luaL_dofile(L, "script.lua");
	LuaRef printMessage = getGlobal(L, "printMessage");
	std::string message = printMessage();
	std::cout << "Hello World from C++\n" << message << "\n";
}

void Task2(lua_State* L) {
	luaL_dofile(L, "script1.lua");
	LuaRef multiplyNumbers = getGlobal(L, "multiplyNumbers");
	int first = 5;
	int second = 3;
	float result = multiplyNumbers(first, second);
	std::cout << first << " times " << second << " equals " << result << "\n";
}

void Task3(lua_State* L) {	
	luaL_dofile(L, "script2.lua");
	luaL_openlibs(L);
	lua_pcall(L, 0, 0, 0);
	LuaRef levelName = luabridge::LuaRef::getGlobal(L, "levelName");
	LuaRef numSectors = luabridge::LuaRef::getGlobal(L, "numSectors");
	LuaRef numRooms = luabridge::LuaRef::getGlobal(L, "numRooms");
	std::string luaString = levelName.cast<std::string>();
	int sectors = numSectors.cast<int>();
	int rooms = numRooms.cast<int>();
	std::cout << "Level Name = " << luaString << std::endl;
	std::cout << "Number of sectors = " << sectors << std::endl;
	std::cout << "Number of rooms = " << rooms << std::endl;
}

void Task4(lua_State* L) {
	luaL_dofile(L, "script3.lua");
	LuaRef AvgNumbers = getGlobal(L, "AvgNumbers");
	int first = 5;
	int second = 3;
	int third = 7;
	float result = AvgNumbers(first, second, third);
	std::cout << "The Average of "<< first << " " << second << " " << third << " is " << result << "\n";
}

int Multiply(int a, int b, int c) {
	return a * b * c;
}

void Task5(lua_State* L) {
	//multiplies 3 numbers and returns the result
	//explose this function to lua
	//create a lua script to call this
	//run the lua script from cpp
	luaL_dofile(L, "script4.lua");
	luaL_openlibs(L);
	lua_pcall(L, 0, 0, 0);
	LuaRef StartMultiplication = getGlobal(L, "StartMultiplication");
	getGlobalNamespace(L).addFunction("Multiply", Multiply);
	int result = StartMultiplication(3, 7, 2);
	std::cout << "The answer is " << result << "\n";
}
