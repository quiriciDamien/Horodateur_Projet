

/*
 *Récupère et modifie l'affichage de la position du jeton en fonction des boutons déplacements
 *En modifie la couleur selon le joueur (1 ou 2)
 */
/*
char grille_matrice_2[7][6]=  {{"      "},{"      "},{"      "},{"      "},{"      "},{"      "},{"      "}};
int grille_jeton[] = { 0, 0, 0, 0, 0, 0, 0 };

void affichage_grille_p4(int pos_jeton, int player, char action_fun) {
	static int grille_jeton[] = { 0, 0, 0, 0, 0, 0, 0 };
	char grille = ' ';
	char jetonp1 = 'O';
	char jetonp2 = 'X';
	char jeton = ' ';
//-----------------------------
	if (player == 1) {
		jeton = jetonp1;
	}
	else if (player == 2) {
		jeton = jetonp2;
	}
//-----------------------------
	printf("-");
	for (int y = 0; y < 7; y++) {
		if (y == pos_jeton) {
			printf("%c-", jeton);
		} else {
			printf("%c-", grille);
		}
	}
	printf("\n");
//-----------------------------
	for (int i = 0; i < 6; i++) {
		printf("|");
		for (int y = 0; y < 7; y++) {
			if (action_fun == 'v' && i == (5 - grille_jeton[pos_jeton])
					&& y == pos_jeton) {
				printf("%c|", jeton);
				grille_jeton[pos_jeton]++;
				grille_matrice_2[i][y] = jeton;
			} else {
				printf("%c|", grille);
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("+++++++++++++++\n");
	for (int i = 0; i < 6; i++) {
		printf("|");
		for (int y = 0; y < 7; y++) {
			printf("%c|", grille_matrice_2[i][y]);
		}
		printf("\n");
	}
	printf("+++++++++++++++\n");

}*/


void print_grille(int posx, int posy)
{
    int lignes=0;
    mvprintw(posx+lignes, posy, "| | | | | | | |");
    mvprintw(posx+lignes+1, posy, "               ");
    while(lignes+2 < 8)
    {
        mvprintw(posx+lignes+2, posy, "| | | | | | | |");
        lignes++;
    }
}



void print_jeton(int posx,int posy,int place,int joueur)
{
    mvprintw(posx, posy, "| | | | | | | |");
    if (joueur == 1)
    mvprintw(posx, posy+(place*2-1), "X");
    else
    mvprintw(posx, posy+(place*2-1), "O");
}
