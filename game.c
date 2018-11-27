#include "settings.h"
#include "grid.h"
#include "game.h"

/****************************************************************************************************
 *								  		TE IMPLEMENTEREN FUNCTIES:						  			*
 ****************************************************************************************************/

/*
 * Deze functie wordt aangeroepen als de gebruiker een vlag wil plaatsten op het vakje met positie (x,y)
 * in het veld.
 */
void flag_coordinate(int x, int y){
	int nr_of_flags = NR_OF_MINES;
	if((*get_cell(x , y)).state == FLAGGED){			//if the cell you selected is already flagged, uncover it
		(*get_cell(x , y)).state = COVERED;
		nr_of_flags += 1;}

	if(nr_of_flags > 0){
		if((*get_cell(x , y)).state == COVERED){		//if there are still mines not found and you flag an uncovered cell
			(*get_cell(x , y)).state = FLAGGED;			//simply flag the cell
			nr_of_flags -= 1;
		}
	}
	else printf("No more flags available.");
}

/*
 * Deze functie wordt aangeroepen als de gebruiker het vakje met positie (x,y) in het veld wil onthullen.
 */
void reveal_coordinate(int x, int y){
	(*get_cell(x , y)).state = UNCOVERED;

	if((*get_cell(x , y)).is_mine == 1){
		printf("\nBOOM! Game Over \n");
	}
	if((*get_cell(x , y)).neighbouring_mines == 0){
		if(y < HEIGHT && y > 0){
			if((*get_cell(x , y - 1)).state == COVERED){
				reveal_coordinate(x, y - 1);
			}
		}
		if(y < HEIGHT -1 && y > -1){
			if((*get_cell(x , y + 1)).state == COVERED){
				reveal_coordinate(x , y + 1);
			}
		}
		if(x < WIDTH && x > 0){
					if((*get_cell(x - 1, y)).state == COVERED){
						reveal_coordinate(x - 1, y);
			}
		}
		if(x < WIDTH -1 && x > -1){
			if ((*get_cell(x +1, y)).state == COVERED){
				reveal_coordinate(x + 1, y);
			}
		}
	}
}

/*
 * Deze functie wordt aangeroepen om het hele, onthulde, veld te printen.
 */
void print_grid_uncovered(){
	int i = 0;
	printf("   ");

	while (i < WIDTH - 1){
		printf("%d", i);
		printf(" ");
		i++;
	}
	printf("%d\n", i);
	int a, b = 0;
	for (a = 0; a < HEIGHT; a++){
		printf("%d", a);
		printf(" |");
		for(b = 0; b < WIDTH; b++){
			if((*get_cell(a, b)).is_mine == 1){
				printf("M|");
			}
			else {printf("%d", (*get_cell(a , b)).neighbouring_mines);
				  printf("|");
			}
		}
		printf("\n");
	}
	printf("\n");
}


/*
 * Leest de input van de gebruiker via de console in, en roept daarna de juiste functie op.
 * De gebruiker kan 3 soorten inputs geven:
 *
 * 1)
 * F x y
 * Wordt gebruikt om een vlag te plaatsen op positie (x,y) in het veld. X en y zijn hier integers.
 * handle_input roept hierna de functie flag_coordinate op.
 *
 * 2)
 * R x y
 * Wordt gebruikt om het vakje met positie (x,y) te onthullen. X en y zijn hier integers.
 * handle_input roept hierna de functie reveal_coordinate op.
 *
 * 3)
 * P
 * Print het hele, onthulde veld.
 * handle_input roept hierna de functie print_grid_uncovered op.
 *
 *
 * Elk van deze functies (flag_coordinate, reveal_coordinate en print_grid_uncovered) moeten
 * nog door jullie geïmplementeerd worden.
 *
 */
void handle_input() {
	char command;
	int x, y;
	char input_buffer[20];
	/* Lees het commando van de gebruiker in */
	fgets(input_buffer, 20, stdin);
	sscanf(input_buffer, "%c %i %i", &command, &x, &y);
	switch (command) {
	case 'F': // Flag
		flag_coordinate(x, y);
		break;
	case 'R': // Reveal
		reveal_coordinate(x, y);
		break;
	case 'P': // Print
		print_grid_uncovered();
		break;
	case 'E':
		exit(0);
		break;
	default:
		/* De speler gaf een commando in dat niet begrepen werd door deze functie: probeer opnieuw. */
		printf("Command '%c' not understood, please try again.\n", command);
		handle_input();
	}
}

/*
 * Deze functie wordt in het begin, eens het veld geïnitialiseerd is, aangeroepen.
 * Eens deze functie is aangeroepen moet het spel in beurten verdergaan tot de speler gewonnen of verloren heeft.
 * Na elke beurt moet het hele veld automatisch geprint worden, via de functie print_grid uit printer.h,
 * en moet er geprint worden hoeveel vlaggen nog beschikbaar zijn voor de speler.
 */
void run_game(){
	print_grid(NR_OF_MINES);
	handle_input();
	run_game();
}
