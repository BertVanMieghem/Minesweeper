#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>

#include "grid.h"
#include "printer.h"

/*
 * Deze functie wordt in het begin, eens het veld geïnitialiseerd is, aangeroepen.
 * Eens deze functie is aangeroepen moet het spel in beurten verdergaan tot de speler gewonnen of verloren heeft.
 * Na elke beurt moet het hele veld automatisch geprint worden, via de functie print_grid uit printer.h,
 * en moet er geprint worden hoeveel vlaggen nog beschikbaar zijn voor de speler.
 */
void run_game(void);

#endif /* GAME_H_ */
