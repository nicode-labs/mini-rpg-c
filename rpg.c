/* == MINI RPG Game == */
/* Code permettant d'afficher :
1. Nouvelle partie
2. Les règles du jeu
3. Quitter le jeu */

// Pour compiler le code, utilisez la commande suivante :
// gcc rpg.c -o rpg -Wall

#include <stdio.h>
#include <stdlib.h>
#include "color.h"

int main()
{
    int choix;

    do
    {
        printf(L_GREEN "===MINI RPG===\n" L_WHITE);
        printf("1.Nouvelle partie\n");
        printf("2.Les règles du jeu\n");
        printf("3.Quitter le jeu\n");
        printf("Ton choix:");

        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            printf(L_GREEN "Le jeu va commencer\n" L_WHITE);
            break;
        case 2:
            printf(L_CYAN "Voici les règles du jeu :\n");
            printf("- Tu incarnes un heros qui affronte des monstres au tour par tour.\n");
            printf("- A chaque tour, tu choisis : attaquer, te soigner ou fuir.\n");
            printf("- Le monstre riposte apres chacune de tes actions.\n");
            printf("- Si les PV du monstre tombent a 0, tu gagnes de l'XP.\n");
            printf("- Assez d'XP = tu montes de niveau et deviens plus fort.\n");
            printf("- Si tes PV tombent a 0... Game Over !\n" L_WHITE);
            break;
        case 3:
            printf(L_WHITE "A bientôt\n");
            break;
        default:
            printf(L_RED "Choix invalide\n" L_WHITE);
            break;
        }
        printf("\n");
    } while (choix != 3);

    return (0);
}