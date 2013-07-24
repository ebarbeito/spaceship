#include <cstdlib>			// EXIT_FAILURE
#include <iostream>
#include "player.h"
#include "game.h"

using std::cerr;
using std::endl;

/* -------------------------------------------------------------------------- *
 * Datos miembro y métodos de clase
 * -------------------------------------------------------------------------- */

void
Player::ErrorHandler (const error_t nerr, const bool kill)
{
	// Mostramos el mensaje de error
	cerr << "Ha ocurrido un error:\n";
	switch (nerr)
	{
		case ERR_SF_INIT:
			cerr << "No se pudo cargar la imagen: ";
			break;
	}
	cerr << SDL_GetError() << endl;

	// Forzamos salida al sistema
	if (kill == true)
		exit (EXIT_FAILURE);
}


/* -------------------------------------------------------------------------- *
 * Métodos públicos
 * -------------------------------------------------------------------------- */

Player::Player (void)
{
	// Cargamos imagen en la superficie jugador
	this->sf = IMG_Load (FILENAME);
	if (this->sf == NULL)
		Player::ErrorHandler (ERR_SF_INIT);

	// Posición inicial del jugador
	this->pos.x = PLAYER_POS_X;
	this->pos.y = PLAYER_POS_Y;
	this->pos.w = this->sf->w;
	this->pos.h = this->sf->h;
}

Player::Player (const Player &player)
{
}

Player::~Player (void)
{
	SDL_FreeSurface (this->sf);
	this->sf = NULL;
}

Player &
Player::operator = (const Player &player)
{
}

void
Player::MoveUp (const short dist, const short limit)
{
	this->pos.y = (this->pos.y - dist < limit ? limit : this->pos.y - dist);
}

void
Player::MoveDown (const short dist, const short limit)
{
	this->pos.y = (this->pos.y + this->sf->h + dist > SCREEN_HEIGHT ? \
	               SCREEN_HEIGHT - this->sf->h : this->pos.y + dist);
}

void
Player::MoveLeft (const short dist, const short limit)
{
	this->pos.x = (this->pos.x - dist < limit ? limit : this->pos.x - dist);
}

void
Player::MoveRight (const short dist, const short limit)
{
	this->pos.x = (this->pos.x + this->sf->w + dist > SCREEN_WIDTH ? \
	               SCREEN_WIDTH - this->sf->w : this->pos.x + dist);
}

void
Player::MoveXY (const int x, const int y)
{
	this->pos.x = (x + this->sf->w > SCREEN_WIDTH ? SCREEN_WIDTH - this->sf->w : x);
	this->pos.y = (y + this->sf->h > SCREEN_HEIGHT ? SCREEN_HEIGHT - this->sf->h : y);
}
