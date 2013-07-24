/*
 *  ____                            _     _
 * / ___| _ __   __ _  ___ ___  ___| |__ (_)_ __
 * \___ \| '_ \ / _` |/ __/ _ \/ __| '_ \| | '_ \
 *  ___) | |_) | (_| | (_|  __/\__ \ | | | | |_) |
 * |____/| .__/ \__,_|\___\___||___/_| |_|_| .__/
 *       |_|                               |_|
 *
 * ------------------------------------------------ */

#include <cstdlib>
#include "game.h"

int main (int argc, char **argv)
{
	// Inicialización y puesta en marcha del juego
	Game *game = Game::GetInstance ();
	game->Loop ();

	// Game over
	delete game;
	game = NULL;

	// Si llega hasta aquí, todo ha ido bien
	return EXIT_SUCCESS;
}
