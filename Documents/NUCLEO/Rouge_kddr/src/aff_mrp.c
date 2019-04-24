
/*
 *Récupère et modifie l'affichage de la position du jeton en fonction des boutons déplacements
 *En modifie la couleur selon le joueur (1 ou 2)
 */

char grille_matrice_1[7][6] = {{"######"},{"######"},{"##   #"},{"##   #"},{"##   #"},{"######"},{"######"}};


void affichage_grille_mrp(int pos_jetonX, int pos_jetonY, int player, char action_fun){
	char grille = '#';
	char grille_vide = ' ';
	char jetonp1 = 'O';
	char jetonp2 = 'X';
	char jeton = ' ';
	int test = 0;

	if(player == 1){
		jeton = jetonp1;
	}
	else if(player == 2){
		jeton = jetonp2;
	}
	for (int i=0;i<6;i++){
		printf("|");
		for(int y=0;y<7;y++){
			if((i>1 && i<5)&&(y>1 && y<5)){
				if(i==pos_jetonY && y==pos_jetonX){
					printf("%c|", jeton);
					if(action_fun == 'v'){
						if(grille_matrice_1[i][y]==' '){
							grille_matrice_1[i][y] = jeton;
						}
						else{
							test=1;
						}
					}
				}
				else{
					printf("%c|", grille_vide);
				}
			}
			else{
				printf("%c|", grille);
			}
		}
		printf("\n");
	}
	if(test != 0){
		printf("Erreur Emplacement déja utilisé\n");
		test=0;
	}
}
