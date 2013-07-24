#ifndef _PLAYER_H
#define	_PLAYER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define FILENAME     "../data/player.png"
#define MOVE_DIST    2
#define PLAYER_POS_X 320
#define PLAYER_POS_Y 240

class Player
{
	private:
		enum error_t		// Tipo de error que puede producirse
		{
			ERR_SF_INIT = 1	// IMG_Load falla (no se puede cargar imagen)
		};

		SDL_Surface *sf;
		SDL_Rect pos;
	
	public:
		Player (void);
		Player (const Player &);
		~Player (void);
		Player & operator = (const Player &);

		inline SDL_Surface * GetSurface (void) const { return this->sf; }
		inline SDL_Rect GetPos (void) const { return this->pos; }

		void MoveUp (const short, const short);
		void MoveDown (const short, const short);
		void MoveLeft (const short, const short);
		void MoveRight (const short, const short);
		void MoveXY (const int, const int);

		static void ErrorHandler (const error_t, const bool = true);
};

#endif	/* _PLAYER_H */

