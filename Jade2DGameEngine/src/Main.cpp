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

    // Importing Lua values to C++
    int someVarInsideCpp = lua["some_variable"];
    std::cout << "The value os some_variable in C++ is " << someVarInsideCpp << std::endl;
}


int main(int argc, char* argv[]) {
    
    //Game game;

    //game.Initialize();
    //game.Run();
    //game.Destroy();

    TestLua();

    return 0;
}
