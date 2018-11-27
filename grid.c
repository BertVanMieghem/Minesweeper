#include "grid.h"
#include "settings.h"

/*
 * Stelt het twee-dimensionale veld voor. grid is een tweedimensionale array van pointers naar Cellen.
 * Jullie moeten deze variabele zelf niet gebruiken: in de plaats kan je gebruik maken van de functie get_cell hieronder.
 */
static struct Cell*** grid;

/*
 * Geeft een pointer terug naar de Cell die zich bevindt op positie (x,y) in het veld.
 * Let op: deze functie gaat ervan uit dat het coördinaat dat werd meegegeven correct is, en dus niet buiten
 * de grenzen van het veld valt.
 */
struct Cell *get_cell(int x, int y) {
	return grid[x][y];
}

/*
 * Stelt een positie voor: elke positie heeft een x- en een y-coordinaat.
 */
struct Coordinate {
	int x, y;
};

/****************************************************************************************************
 *								  		TE IMPLEMENTEREN FUNCTIES:						  			*
 ****************************************************************************************************/
/*
 * Gegeven een array van Coördinaten, met lengte gelijk aan nr_of_mines, moet deze functie ervoor zorgen dat er een mijn wordt
 * geplaatst op alle vakjes wiens positie in de mines_coordinates array zit.
 * Zie hiervoor de commentaar bij de Coordinate struct in grid.h.
 */
void place_mines(struct Coordinate mines_coordinates[], int nr_of_mines) {
	for (int n = 0 ; n < nr_of_mines ; n++)
		(*get_cell(mines_coordinates[n].x, mines_coordinates[n].y)).is_mine = 1;
}

/*
 * Gegeven een array van Coördinaten, met lengte gelijk aan nr_of_mines, en gegeven de dimensies van het veld grid_width en
 * grid_height, moet deze functie ervoor zorgen dat voor alle vakjes (Cellen) in het veld het field neighbouring_mines juist wordt berekend.
 * T.t.z. nadat deze functie aangeroepen is, moet elke Cell in het veld het juiste aantal neighbouring_mines bijhouden.
 */
void compute_neighbouring_mines(struct Coordinate *mines_coordinates, int grid_width, int grid_height, int nr_of_mines) {
	int n;
	for( n = 0 ; n < nr_of_mines ; n++){
		int x = (mines_coordinates + n)->x;
		int y = (mines_coordinates + n)->y;
		int a;
		int b;
		for(a = -1 ; a < 2 ; a++){			//one cell left and right of current cell
			for(b = -1 ; b < 2 ; b++){	   //one cell above and below of current cell
				if( x + a < grid_width && x + a >= 0 && y + b < grid_height && y + b >= 0){
					(*get_cell(x + a, y + b)).neighbouring_mines += 1;
				}
			}
		}
	}
}










/************************************************************************************************************
 * De code die hieronder staat hebben jullie normaal gezien NIET nodig.										*
 * Deze code wordt gebruikt om het veld te initialiseren: om de grid-array aan te maken, mijnen te plaatsen *
 * en te berekenen hoeveel naburige mijnen elk vakje bevat.													*
 * Enkel als je beslist om bv. de eerste bonusfeature te implementeren (om het veld pas te initialiseren    *
 * nadat de speler de eerste beurt gedaan heeft, zal je mogelijk deze code moeten aanpassen.				*
 ************************************************************************************************************/

/*
 * Maakt een 1-dimensionale sequentiële array aan van lengte grid_width * grid_height, die opgevuld wordt door de getallen
 * gaande van 0 tot lengte - 1.
 */
static int *generate_sequential_array(int grid_width, int grid_height) {
	int *sequential_array = (int *) malloc(grid_width * grid_height * sizeof(int));

	int i;
	for (i = 0; i < grid_width * grid_height; i++) {
		sequential_array[i] = i;
	}

	return sequential_array;
}

/*
 * Genereert nr_of_mines aantal random, verschillende posities voor de mijnen die initieel in het veld geplaatst worden.
 */
static struct Coordinate* generate_random_mines(int grid_width, int grid_height, int nr_of_mines) {
	// Random, verschillende waarden genereren: http://stackoverflow.com/questions/196017/unique-non-repeating-random-numbers-in-o1

	if (nr_of_mines > grid_width * grid_height) {
		printf("There are more mines than cells in the grid. Aborting...\n");
		exit(1);
	}

	int mines_selected = 0;
	/* De array van coördinaten waar de mijnen zullen geplaatst worden. */
	struct Coordinate *coordinates_of_mines = malloc(nr_of_mines * sizeof(struct Coordinate));
	int *sequential_array = generate_sequential_array(grid_width, grid_height);

	/* Vul de array coordinates_of_mines op. */
	while (mines_selected < nr_of_mines) {
		/* Kies een random index in de sequentiële arra.y */
		int r = rand() % (grid_width * grid_height - mines_selected);
		int i = sequential_array[r];

		/* Verwissel het laatste element in de sequentiële array met het element op positie r. */
		sequential_array[r] = sequential_array[grid_width * grid_height - mines_selected - 1];
		sequential_array[grid_width * grid_height - mines_selected - 1] = i;

		/* Bereken het coordinaat dat overeenkomt met het getal i. */
		int x = i % grid_width;
		int y = i / grid_width;
		struct Coordinate coordinate = { x, y };
		coordinates_of_mines[mines_selected] = coordinate;
		mines_selected++;
	}

	free(sequential_array);

	return coordinates_of_mines;
}

void initialize_grid(int grid_width, int grid_height, int nr_of_mines) {
	grid = allocate_grid(grid_width, grid_height);
	struct Coordinate *mines_coordinates = generate_random_mines(grid_width, grid_height, nr_of_mines);
	place_mines(mines_coordinates, nr_of_mines);
	compute_neighbouring_mines(mines_coordinates, grid_width, grid_height, nr_of_mines);
	free(mines_coordinates);
}
