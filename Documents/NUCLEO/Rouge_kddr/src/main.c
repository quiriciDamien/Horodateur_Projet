#include "main.h"
#define WINDOW stdscr
int jetonPos;
int Joueur;

void affichage_grille_mrp(int pos_jetonX, int pos_jetonY, int player, char action_fun);
void affichage_grille_p4(int pos_jeton, int player, char action_fun);
void print_jeton(int posx,int posy,int place,int joueur);
void print_grille(int posx, int posy);

extern char grille_matrice_1[7][6];
int c;

int main(void)
{
	//static int grille_jeton[] = { 0, 0, 0, 0, 0, 0, 0 };

	//int cpt=0;

	initscr(); /* init de ncurses */
	clear();
	noecho(); /* pour masquer l'affichage du buffer stdin dans la console */
	cbreak(); /* Line buffering disabled. pass on everything */

	mvprintw(0, 0, "commencez à jouer !!");
	refresh();

	print_grille(4, 25);
	jetonPos = 4;
	Joueur =1;
	print_jeton(4,25,jetonPos,Joueur);

	scrollok(WINDOW, TRUE);
	nodelay(WINDOW, TRUE);
	while (1)
	{
		c = wgetch(WINDOW);
		//cpt++;
		sleep(0.5);
		fflush(stdin);
		//mvprintw(14, 2, "la valeur est %d", c);
		//mvprintw(15, 2, " %d", cpt);
		switch (c)
		{
			case KEY_UP:
				break;
			case KEY_DOWN:
				break;
			case KEY_ENTER:   //enter
				break;
			case 68:
				if (jetonPos > 1)
					jetonPos--;
				else
					jetonPos = 7;
				print_jeton(4, 25, jetonPos, Joueur);
				break;
			case 67:
				if (jetonPos < 7)
					jetonPos++;
				else
					jetonPos = 1;
				print_jeton(4, 25, jetonPos, Joueur);
				break;
			case 66:
				//--------------------
				break;
			default:
				mvprintw(24, 0, "Character pressed is = %3d Hopefully it can be printed as '%c'",c, c);
				refresh();
				break;
		}
	}
	clrtoeol();
	refresh();
	endwin();
	return 0;
}


int main_mrp(void) {
int init_jetonX = 3;
int init_jetonY = 3;
int joueur = 2;
char action = ' ';

while (1) {
	sleep(0.5);
	affichage_grille_mrp(init_jetonX, init_jetonY, joueur, action);
	printf("q(gauche), d(droite), v(valider): \n");
	scanf("%c", &action);
	if (action == 'q') {
		if (init_jetonX == 2) {
			init_jetonX = 4;
		} else {
			init_jetonX--;
		}
	}
	if (action == 'd') {
		if (init_jetonX == 4) {
			init_jetonX = 2;
		} else {
			init_jetonX++;
		}
	}
	if (action == 'z') {
		if (init_jetonY == 2) {
			init_jetonY = 4;
		} else {
			init_jetonY--;
		}
	}
	if (action == 's') {
		if (init_jetonY == 4) {
			init_jetonY = 2;
		} else {
			init_jetonY++;
		}
	}
	if (action == 'v') {
		for (int i = 0; i < 6; i++) {
			printf("|");
			for (int y = 0; y < 7; y++) {
				printf("%c|", grille_matrice_1[i][y]);
			}
			printf("\n");
		}
	}
}
for (int i = 0; i < 6; i++) {
	printf("|");
	for (int y = 0; y < 7; y++) {
		printf("%c|", grille_matrice_1[i][y]);
	}
}
return 0;
}
