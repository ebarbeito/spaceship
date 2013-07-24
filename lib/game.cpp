#include <cstdlib>
#include <SDL/SDL_events.h>	// EXIT_FAILURE
#include <iostream>
#include "game.h"
#include "player.h"

using std::cerr;
using std::cout;
using std::endl;

/* -------------------------------------------------------------------------- *
 * Datos miembro y métodos de clase
 * -------------------------------------------------------------------------- */

Game *
Game::app = NULL;

Game *
Game::GetInstance (void)
{
	// Instancia del juego en modo Singleton
	if (Game::app == NULL)
	{
		Game::app = new Game ();
		if (Game::app == NULL)
			Game::ErrorHandler (ERR_NEW_GAME);
	}

	return Game::app;
}

void
Game::ErrorHandler (const error_t nerr, const bool kill)
{
	// Mostramos el mensaje de error
	cerr << "Ha ocurrido un error:\n";
	switch (nerr)
	{
		case ERR_INIT:
			cerr << "No se pudo iniciar SDL: ";
			break;

		case ERR_VIDEO_NA:
			cerr << "Modo de vídeo no soportado: ";
			break;

		case ERR_VIDEO_SET:
			cerr << "No se pudo iniciar el modo de vídeo: ";
			break;

		case ERR_KEY_REPEAT:
			cerr << "No se pudo establecer el modo repetición de tecla:";
			break;

		case ERR_NEW_GAME:
			cerr << "No es posible reservar memoria para Game.";
			break;

		case ERR_NEW_PJ:
			cerr << "No es posible reservar memoria para Player.";
			break;

		default:
			cerr << "No definido.";
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

Game::~Game (void)
{
	delete this->pj;
	SDL_FreeSurface (this->screen);
	SDL_Quit ();
	
	this->pj     = NULL;
	this->screen = NULL;
	Game::app    = NULL;
}

void
Game::EventHandler (bool &loop)
{
	SDL_Event event;
	static bool keyup    = false, // Flecha arriba pulsada
	            keydown  = false, // Flecha abajo pulsada
	            keyleft  = false, // Felcha izquierda pulsada
	            keyright = false; // Flecha derecha pulsada

	// Captura de eventos mediante Polling o Sondeo
	while (SDL_PollEvent (&event))
	{
		/*
		 * Forma 1 de obtener el estado de las teclas: Snapshot de TODO el teclado
		 * - Ventaja: Controlamos fácilmente la pulsación de varias teclas a la vez
		 * - Desventaja: No debe ser muy óptimo
		 *
		 * Código COMENTADO
		Uint8 *keystate = NULL;
		keystate = SDL_GetKeyState (NULL);
		
		if (keystate[SDLK_UP])
			this->pj->MoveUp (MOVE_DIST, 0);

		if (keystate[SDLK_DOWN])
			this->pj->MoveDown (MOVE_DIST, SCREEN_HEIGHT);

		if (keystate[SDLK_LEFT])
			this->pj->MoveLeft (MOVE_DIST, 0);

		if (keystate[SDLK_RIGHT])
			this->pj->MoveRight (MOVE_DIST, SCREEN_WIDTH);

		if (keystate[SDLK_f])
			SDL_WM_ToggleFullScreen (this->screen);

		if (keystate[SDLK_ESCAPE])
			loop = false;
		*/
		
		/*
		 * Forma 2 de obtener el estado de las teclas: mediante evento recién desencolado
		 * Ventaja: No perdemos ningún evento.
		 * Desventaja: Tenemos que procesar pulsación por pulsación (no parece
		 *             poder obtener combinaciones de teclas pulsadas
		 *
		 * Código COMENTADO

		switch (event.type)
		{
			// Eventos para TECLA PULSADA
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						this->pj->MoveUp (MOVE_DIST, 0);
						break;

					case SDLK_DOWN:
						this->pj->MoveDown (MOVE_DIST, SCREEN_HEIGHT);
						break;

					case SDLK_RIGHT:
						this->pj->MoveRight (MOVE_DIST, SCREEN_WIDTH);
						break;

					case SDLK_LEFT:
						this->pj->MoveLeft (MOVE_DIST, 0);
						break;
				}
				break;

			// Evento de salida
			case SDL_QUIT:
				loop = false;
				break;
		}

		 */

		/*
		 * Forma 3: Recogida de teclas idem que la forma anterior pero empleando
		 *          centinelas para conocer qué flechas están pulsadas al mismo
		 *          tiempo. Posteriormente se realiza el tratamiento.
		 *
		 * "Método dos refinado", de los tres es el que más me convence.
		 * **/
		
		switch (event.type)
		{
			// Tecla pulsada
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					// Flechas de dirección
					case SDLK_UP    : keyup    = true; break;
					case SDLK_DOWN  : keydown  = true; break;
					case SDLK_LEFT  : keyleft  = true; break;
					case SDLK_RIGHT : keyright = true; break;

					// Resto de teclas
					case SDLK_f:
						SDL_WM_ToggleFullScreen (this->screen);
						break;

					case SDLK_ESCAPE:
						loop = false;
						break;

					default:
						break;
				}
				break;

			// Tecla soltada
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					// Flechas de dirección
					case SDLK_UP    : keyup    = false; break;
					case SDLK_DOWN  : keydown  = false; break;
					case SDLK_LEFT  : keyleft  = false; break;
					case SDLK_RIGHT : keyright = false; break;
					default:                            break;
				}
				break;

			// Movimiento del ratón
			case SDL_MOUSEMOTION:
				this->pj->MoveXY (event.motion.x, event.motion.y);
				break;

			// Botón de ratón pulsado
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
					// Botón izquierdo
					case 1:
						cout << "Botón izquierdo del raton. ";
						break;

					// Botón central
					case 2:
						cout << "Botón central del raton. ";
						break;

					// Botón derecho
					case 3:
						cout << "Botón derecho del raton. ";
						break;

					default:
						break;

				}
				
				cout << "(x,y) = (" << event.button.x << ','
				                    << event.button.y << ')' << endl;
				break;

			// Evento de salida
			case SDL_QUIT:
				loop = false;
				break;
		}

		// Realizar movimientos en función a las teclas pulsadas
		if (keyup == true)
			this->pj->MoveUp (MOVE_DIST, 0);

		if (keydown == true)
			this->pj->MoveDown (MOVE_DIST, SCREEN_HEIGHT);

		if (keyleft == true)
			this->pj->MoveLeft (MOVE_DIST, 0);

		if (keyright == true)
			this->pj->MoveRight (MOVE_DIST, SCREEN_WIDTH);
	}
}

void
Game::Loop (void)
{
	bool loop = true;

	/*
	 * Forma 1: Game Loop con temporizador
	 * */
	Uint32 time_last = SDL_GetTicks ();
	while (loop == true)
	{
		// Hacer bloque Update si el tiempo transcurrido es mayor que el nº de
		// veces el tiempo que ha de transcurrir [20 fps cada 50 ms.]
		if ((SDL_GetTicks() - time_last) > (1000 / UPDATE_FPS))
		{
			// Procesamiento de eventos
			this->EventHandler (loop);
		}

		// Actualizar gráficos
		this->Refresh (this->pj->GetSurface (), this->pj->GetPos ());
	}

	/*
	 * Forma 2: Game Loop o bucle principal (modo secuencial)
	 *
	 * Código COMENTADO
	
	do
	{
		// Procesamiento de eventos
		this->EventHandler (loop);

		// Actualizar gráficos
		this->Refresh (this->pj->GetSurface (), this->pj->GetPos ());
	}
	while (loop == true);

	 */
}

void
Game::Refresh (SDL_Surface *sf, SDL_Rect dst)
{
	// Limpieza de pantalla
	SDL_FillRect (this->screen, NULL, 0);

	// Cambio de posición del personaje
	SDL_BlitSurface (sf, NULL, this->screen, &dst);

	// Actualización de la pantalla
	SDL_Flip (this->screen);
}


/* -------------------------------------------------------------------------- *
 * Métodos privados
 * -------------------------------------------------------------------------- */

Game::Game (void)
{
	// Estos valores pueden ser configurables por el usuario. Se pueden guardar
	// en un fichero e iniciar el juego con la última configuración fijada por
	// el usuario.
	this->width  = SCREEN_WIDTH;
	this->height = SCREEN_HEIGHT;
	this->bpp    = SCREEN_BPP;
	this->flags  = FLAGS_VIDEO;
	
	this->pj = NULL;

	// Inicialización del subsistema de vídeo
	if (SDL_Init (FLAGS_INIT) < 0)
		Game::ErrorHandler (ERR_INIT);

	// Comprobamos compatibilidad del modo de vídeo
	if (SDL_VideoModeOK (this->width, this->height, this->bpp, this->flags) == 0)
		Game::ErrorHandler (ERR_VIDEO_NA);

	// Establecemos el modo de vídeo
	this->screen = SDL_SetVideoMode (this->width, this->height, this->bpp, this->flags);
	if (this->screen == NULL)
		Game::ErrorHandler (ERR_VIDEO_SET);

	// Titulo de la ventana
	SDL_WM_SetCaption (GAMENAME, NULL);

	// Inicialización de estructuras de datos
	this->Init ();
}

Game::Game (const Game &game)
{
}

Game &
Game::operator = (const Game &game)
{
	return *this;
}

void
Game::Init (void)
{
	// Instancia del jugador (pj, personaje)
	this->pj = new Player ();
	if (this->pj == NULL)
		Game::ErrorHandler (ERR_NEW_PJ);

	// Activamos la repetición de teclas
	int repeat = SDL_EnableKeyRepeat (1, 1);
	if (repeat < 0)
		Game::ErrorHandler (ERR_KEY_REPEAT, false);

	// Copiamos la imagen en la superficie principal
	SDL_BlitSurface (this->pj->GetSurface(), NULL, this->screen, &this->pj->GetPos());

	// Mostramos la pantalla "oculta" del búffer
	SDL_Flip (this->screen);
}
