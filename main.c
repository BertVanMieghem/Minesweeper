#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "grid.h"

/*
 * Initialiseert eerst het veld, via de functie initialize_grid uit grid.c, en roept daarna de functie
 * run_game uit game.c aan om het spel effectief te starten.
 */
int main(void) {
	/*
	 * Naar deze statement hoef je nu niet te kijken.
	 */
	srand(time(NULL));

	/*
	 * Initialiseert het speelveld met als dimensies de breedte en de hoogte die gedefinieerd zijn in settings.h,
	 * en met het aantal mijnen gelijk aan NR_OF_MINES uit settings.h.
	 */
	initialize_grid(WIDTH, HEIGHT, NR_OF_MINES);

	/*
	 * Start het eigenlijke spel.
	 */
	run_game();
}
