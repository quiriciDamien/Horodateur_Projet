#include "main.h"

int pupitre(void)
{
	ingame = 0;
	//Avant partie lançée
	while(ingame == 0)
	{
		printf("1 = 1 joueur \n"
				"2 = 2 joueurs \n"
				"0 = stop \n"
				"8 = haut \n"
				"4 = gauche \n"
				"6 = droite \n"
				"5 = entrée \n");
		scanf("%d", &saisie);
		if(saisie == 1)
		{
			printf("Partie 1 JOUEUR \n");
			ingame = 1;
			joueur = 1;
		}
		else if(saisie == 2)
		{
		printf("Partie 2 JOUEUR \n");
		ingame = 1;
		joueur = 2;
		}
		else
		{
			continue;
		}

	}

	//Partie en cours
	while(ingame == 1)
	{
		printf("DEBUT DE CE JEU DE CES MORTS !!! \n");
		printf("0 = stop \n"
				"8 = haut \n"
				"4 = gauche \n"
				"6 = droite \n"
				"5 = entrée \n");
		scanf("%d", &saisie);
		switch(saisie)
		{
				case '8' :
					printf("up");
					break;
				case '4' :
					printf("left");
					break;
				case '6':
					printf("right");
					break;
				case '5':
					printf("down");
					break;
				case '0':
					printf("drop");
					break;
		}
	}
//-----------------------------------------------

}
