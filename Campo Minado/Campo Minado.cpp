#pragma once

#include <iostream>
#include "Game.h"
#include <exception>

int main(int argc, char *argv[])
{
    Game game;

    if (!game.init())
    {
        throw new std::exception("Erro ao inicializar o jogo");
    }

    game.start();
    game.close();


    return 0;
}

