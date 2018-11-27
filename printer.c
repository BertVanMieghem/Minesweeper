#include "printer.h"
#include "settings.h"
#include "grid.h"

/*
 * In dit bestand kan je de functie print_grid uit printer.h implementeren.
 */

void print_grid(){
	int i = 0;
	printf("   ");

	while(i < WIDTH){
		printf("%d ", i);
		i++;
	}
	printf("\n");
	int a, b;
	for(a = 0; a < HEIGHT; a++){
		printf("%d", a);
		printf(" |");
		for(b = 0; b < WIDTH; b++){
			if((*get_cell(a , b)).state == COVERED){
				printf(" |");
			}
			if((*get_cell(a , b)).state == UNCOVERED){
				if((*get_cell(a , b)).is_mine == 0){
					printf("%d", (*get_cell(a , b)).neighbouring_mines);
					printf("|");
				}
				else {printf("M|");}
			}
			if((*get_cell(a , b)).state == FLAGGED){
				printf("F|");
			}
		}
		printf("\n");
	}
}
