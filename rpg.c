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
#include <time.h>
#include <string.h>

struct Personnage // Ce struct est la base de chaque personnage du jeu
{
    char nom[20];
    char classe[20];
    int pv;
    int attaque;
};
int main()
{
    int choix;           // Variable pour le choix du menue
    int choix_de_classe; // Variable pour le choix de la classe
    srand(time(NULL));   // Permet l'aléatoire pour les combats

    do // boucle du menu principal
    {
        printf(L_GREEN "\n\n===MINI RPG===\n" L_WHITE);
        printf("1.Nouvelle partie\n");
        printf("2.Les règles du jeu\n");
        printf("3.Quitter le jeu\n");
        printf("Ton choix:");

        scanf("%d", &choix);
        switch (choix) // Définit les plusieurs effets du choix du menu principal
        {
        case 1:
            printf(L_GREEN "Le jeu va commencer\n" L_WHITE);
            struct Personnage HeroPrincipal;
            printf(HOME L_BLUE "Comment se nomme le Hero:\n");
            scanf("%s", HeroPrincipal.nom);
            do // Boucle du choix de la classe
            {
                printf(L_BLUE "Quelle est ta classe ?\n 1:Chevalier\n 2:Archer\n 3:Voleur\n");
                printf("Ton choix:");
                scanf("%d", &choix_de_classe);
                switch (choix_de_classe) // Définit les plusieurs effets du choix des classes
                {
                case 1: // Le chevalier tank beaucoup mais ne frappe pas fort
                    strcpy(HeroPrincipal.classe, "Chevalier");
                    HeroPrincipal.pv = 120;
                    HeroPrincipal.attaque = 4;
                    break;

                case 2: // L'archer tank et frappe de manière modéré
                    strcpy(HeroPrincipal.classe, "Archer");
                    HeroPrincipal.pv = 95;
                    HeroPrincipal.attaque = 5;
                    break;

                case 3: // Le voleur ne tank pas beaucoup mais frappe fort
                    strcpy(HeroPrincipal.classe, "Voleur");
                    HeroPrincipal.pv = 80;
                    HeroPrincipal.attaque = 7;
                    break;
                default:
                    printf(L_RED "Choix invalide\n" HOME L_WHITE);
                    break;
                }
            } while (choix_de_classe < 1 || choix_de_classe > 3); // Fin de la boucle choix

            printf(HOME L_RED "Nom : %s\n" L_WHITE, HeroPrincipal.nom);
            printf("Classe : %s\n", HeroPrincipal.classe);
            printf(L_GREEN "Caractéristiques :\n" L_WHITE "%d dégats\nVitalité : %d\n" L_WHITE, HeroPrincipal.attaque, HeroPrincipal.pv);
            struct Personnage PremierMonstre = {"Grok", "Gobelin", 60, 3}; // Définit le premier monstre
            

            printf("\n\nUn %s sauvage apparait !!!", PremierMonstre.nom);
            printf(L_RED "\n\nVoici %s le %s !\n" L_WHITE, PremierMonstre.nom, PremierMonstre.classe);
            printf(L_MAGENTA "Caractéristiques :\n" L_WHITE "%d dégats\nVitalité : %d\n", PremierMonstre.attaque, PremierMonstre.pv);
            int degats;                                   // Définit la variable dégat pour les combats qui sera aléatoire avec rand
            degats = rand() % PremierMonstre.attaque + 1; // rand renvoie un nombre très grand, donc on met un modulo et le +1 pour que l'attaque soit comprise entre 1 et les dégats max du personnage
            

            printf(L_GREEN "\n\n%s Frappe %s avec ses griffes !"
                           "\n-%dpv",
                   PremierMonstre.nom, HeroPrincipal.nom, degats);
            HeroPrincipal.pv -= degats;
            printf("\n%s a encore %dPV", HeroPrincipal.nom, HeroPrincipal.pv);
            

            degats = rand() % HeroPrincipal.attaque + 1;
            printf(L_CYAN "\n\n%s contre attaque et frappe %s !"
                          "\n-%dpv",
                   HeroPrincipal.nom, PremierMonstre.nom, degats);
            PremierMonstre.pv -= degats;
            printf("\n%s a encore %dPV", PremierMonstre.nom, PremierMonstre.pv);

            if(HeroPrincipal.pv <= 0){
                printf(L_RED"\nGAME OVER !!! :("L_WHITE);
            }
            else if(PremierMonstre.pv <= 0){
                printf(L_GREEN"\nVictoire !!! :)"L_WHITE);
            }
            else{
                printf(L_MAGENTA"\n%s est encore debout !"L_WHITE, PremierMonstre.nom);
            }

            break;


        case 2: // case pour le deuxième menu des règles du jeu
            printf(L_CYAN "Voici les règles du jeu :\n");
            printf("- Tu incarnes un heros qui affronte des monstres au tour par tour.\n");
            printf("- A chaque tour, tu choisis : attaquer, te soigner ou fuir.\n");
            printf("- Le monstre riposte apres chacune de tes actions.\n");
            printf("- Si les PV du monstre tombent a 0, tu gagnes de l'XP.\n");
            printf("- Assez d'XP = tu montes de niveau et deviens plus fort.\n");
            printf("- Si tes PV tombent a 0... Game Over !\n" L_WHITE);
            break;
        case 3: // caqe pour le menu pour quitter le jeu
            printf(L_WHITE "A bientôt\n");
            break;
        default: // pour les choix du menu invalide
            printf(L_RED "Choix invalide\n" L_WHITE);
            break;
        }
        printf("\n");
    } while (choix != 3);

    return (0);
}