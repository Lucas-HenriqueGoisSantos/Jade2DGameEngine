#include "./Game/Game.h"
#include <sol/sol.hpp>
#include <iostream>


void TestLua() {

    // Creating the Lua state in with Sol
    sol::state lua;
    // Importing libs for Lua, all base Sol libs
    lua.open_libraries( sol::lib::base );
    // Importing a Lua Script
    lua.script_file( "./assets/scripts/hello.lua" );

    // Importing a Lua var to C++
    int someVarInsideCpp = lua["some_variable"];
    std::cout << "The value of some_variable in C++ is " << someVarInsideCpp << std::endl;

    // Importing a value from Lua table to C++
    bool isFullScreen = lua["config"]["fullscreen"];
    // Importing a Lua table to C++
    sol::table config = lua["config"];
    int width = config["resolution"]["width"];
    int height = config["resolution"]["height"];

    std::cout << "The value of fullscreen in C++ is " << isFullScreen << ", width is " << width << " and height is " << height << std::endl;

    // Invoke a Lua function through Sol into C++
    Sol::function functionFactorial = lua["factorial"];
    int functionResult = functionFactorial( 9 );

    std::cout << "The Lua script calculated 5! as " << functionResult << std::endl;
}


int main(int argc, char* argv[]) {
    
    //Game game;

    //game.Initialize();
    //game.Run();
    //game.Destroy();

    TestLua();

    return 0;
}
