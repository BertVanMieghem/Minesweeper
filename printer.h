#ifndef PRINTER_H_
#define PRINTER_H_

#include <stdio.h>

#include "grid.h"
#include "settings.h"

/*
 * Print het hele veld. Deze functie gaat ervan uit dat de dimensies (de breedte en de hoogte) van het veld
 * gelijk zijn aan de dimensies die gedefinieerd staan in settings.h.
 *
 * Hoe dit veld juist moet geprint worden, mag je zelf kiezen.
 */
void print_grid();

#endif /* PRINTER_H_ */
