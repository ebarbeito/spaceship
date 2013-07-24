#ifndef _GAME_H
#define	_GAME_H

#include <SDL/SDL.h>
#include "player.h"

#define GAMENAME      "Spaceship"
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP    24
#define FLAGS_INIT   (SDL_INIT_VIDEO)
#define FLAGS_VIDEO  (SDL_HWSURFACE | SDL_DOUBLEBUF)
#define UPDATE_FPS   20

class Game
{
	private:
		enum error_t		// Tipo de error que puede producirse
		{
			ERR_INIT = 1,	// SDL_Init falla
			ERR_VIDEO_NA,	// SDL_VideModeOK falla (NA = Not Available)
			ERR_VIDEO_SET,	// SDL_SetVideoMode falla
			ERR_KEY_REPEAT,	// SDL_EnableKeyRepeat falla
			ERR_NEW_GAME,	// Fallo reservando memoria para un Game
			ERR_NEW_PJ		// Fallo reservando memoria para un Player
		};

		SDL_Surface *screen;
		int width;
		int height;
		int bpp;
		Uint32 flags;
		static Game *app;
		Player *pj;

		Game (void);
		Game (const Game &);
		Game & operator = (const Game &);

		void Init (void);
	
	public:
		~Game (void);
		static Game * GetInstance (void);
		static void ErrorHandler (const error_t, const bool = true);

		void EventHandler (bool &);
		void Loop (void);
		void Refresh (SDL_Surface *, SDL_Rect);
};

#endif	/* _GAME_H */

