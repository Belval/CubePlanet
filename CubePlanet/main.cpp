#include <SFML/Window.hpp>
#include <iostream>
#include "engine.h"
#include "tool.h"



int main()
{
    Tool::CheckTypes();

    Engine engine;
    engine.SetMaxFps(60);
    engine.Start("CubePlanet", 1280, 720, false);
}
