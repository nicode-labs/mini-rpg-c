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
#include "personnage.h"

// Les fonctions que j'utilise dans le codeé
void afficherMenu()
{
    printf(L_GREEN "\n\n===MINI RPG===\n" L_WHITE);
    printf("1.Nouvelle partie\n");
    printf("2.Les règles du jeu\n");
    printf("3.Quitter le jeu\n");
    printf("Ton choix:");
}
///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int choix;           // Variable pour le choix du menue
    int choix_de_classe; // Variable pour le choix de la classe
    srand(time(NULL));   // Permet l'aléatoire pour les combats
    struct Personnage bestiaire[4] = {
        {"Grok", "Gobelin", 60, 3, 60, 50, 0, 10, 0},
        {"Draco", "Dragon", 130, 12, 130, 200, 0, 20, 0},
        {"Ursus", "Ours", 70, 4, 70, 130, 0, 15, 0},
        {"Pétunia", "Fleur", 30, 1, 30, 40, 0, 5, 0},
    };
    do // boucle du menu principal
    {
        afficherMenu();

        scanf("%d", &choix);
        switch (choix) // Définit les plusieurs effets du choix du menu principal
        {
        case 1:
            printf(L_GREEN "Le jeu va commencer\n" L_WHITE);
            struct Personnage HeroPrincipal;
            printf(L_BLUE "Comment se nomme le Hero:\n");
            while (getchar() != '\n');
            fgets(HeroPrincipal.nom, 20, stdin);
            HeroPrincipal.nom[strcspn(HeroPrincipal.nom, "\n")] = '\0';
            do // Boucle du choix de la classe
            {
                printf(L_BLUE "Quelle est ta classe ?\n 1:Chevalier\n 2:Archer\n 3:Voleur\n 4:Reprendre Sauvegarde\n");
                printf("Ton choix:");
                scanf("%d", &choix_de_classe);
                switch (choix_de_classe) // Définit les plusieurs effets du choix des classes
                {
                case 1: // Le chevalier tank beaucoup mais ne frappe pas fort
                    strcpy(HeroPrincipal.classe, "Chevalier");
                    HeroPrincipal.pv = 120;
                    HeroPrincipal.attaque = 6;
                    HeroPrincipal.pvMax = 120;
                    HeroPrincipal.xp = 0;
                    HeroPrincipal.niveau = 1;
                    HeroPrincipal.orPossede = 30;
                    HeroPrincipal.potions = 1;
                    break;

                case 2: // L'archer tank et frappe de manière modéré
                    strcpy(HeroPrincipal.classe, "Archer");
                    HeroPrincipal.pv = 95;
                    HeroPrincipal.attaque = 7;
                    HeroPrincipal.pvMax = 95;
                    HeroPrincipal.xp = 0;
                    HeroPrincipal.niveau = 1;
                    HeroPrincipal.orPossede = 5;
                    HeroPrincipal.potions = 1;
                    break;

                case 3: // Le voleur ne tank pas beaucoup mais frappe fort
                    strcpy(HeroPrincipal.classe, "Voleur");
                    HeroPrincipal.pv = 80;
                    HeroPrincipal.attaque = 9;
                    HeroPrincipal.pvMax = 80;
                    HeroPrincipal.xp = 0;
                    HeroPrincipal.niveau = 1;
                    HeroPrincipal.orPossede = 10;
                    HeroPrincipal.potions = 1;
                    break;
                case 4:
                    if (charger(&HeroPrincipal) == 0)
                    {
                        choix_de_classe = 0;
                    }
                    else
                    {
                        charger(&HeroPrincipal);
                    }
                    break;
                default:
                    printf(L_RED "Choix invalide\n" HOME L_WHITE);
                    break;
                }
            } while (choix_de_classe < 1 || choix_de_classe > 4); // Fin de la boucle choix

            afficherfiche(HeroPrincipal);
            printf(L_GREEN "\nNotre Hero a %d or et %d potions." L_WHITE, HeroPrincipal.orPossede, HeroPrincipal.potions);
            int continuer;
            do
            {
                continuer = 0;
                int nombre = rand() % 4;
                struct Personnage PremierMonstre = bestiaire[nombre]; // Définit le premier monstre

                printf("\n\nUn %s sauvage apparait !!!", PremierMonstre.nom);
                printf(L_RED "\n\nVoici %s le %s !\n" L_WHITE, PremierMonstre.nom, PremierMonstre.classe);
                afficherfiche(PremierMonstre);
                int fuite = 0;
                while (HeroPrincipal.pv > 0 && PremierMonstre.pv > 0 && fuite != 1)
                {
                    attaquer(&PremierMonstre, &HeroPrincipal);
                    if (HeroPrincipal.pv > 0)
                    {
                        printf("\n%s a encore %dPV", HeroPrincipal.nom, HeroPrincipal.pv);
                    }
                    else if (HeroPrincipal.pv <= 0)
                    {
                        printf(L_RED "\n%s a pris un violent coup et ne pourra pas s'en remettre.." L_WHITE, HeroPrincipal.nom);
                    }

                    if (HeroPrincipal.pv > 0)
                    {
                        int action;
                        printf(L_BLUE "\n\n Que fais-tu ?"
                                      "\n\n 1.Attaquer  2.Soigner  3.Fuir 4.Potion\n" L_WHITE);
                        scanf("%d", &action);
                        switch (action)
                        {
                        case 1:
                            attaquer(&HeroPrincipal, &PremierMonstre);
                            break;
                        case 2:
                            soigner(&HeroPrincipal, rand() % 10 + 5);
                            break;
                        case 3:
                            fuite = rand() % 2;
                            if (fuite == 1)
                            {
                                printf(L_GREEN "\nLa fuite a réussi !" L_WHITE);
                            }
                            else
                            {
                                printf(L_RED "\n%s te rattrape !" L_WHITE, PremierMonstre.nom);
                            }
                            break;
                        case 4:
                            if (HeroPrincipal.potions > 0)
                            {
                                HeroPrincipal.potions -= 1;
                                soigner(&HeroPrincipal, 40);
                            }
                            else
                            {
                                printf(L_RED "\nTu n'as pas de potion..." L_WHITE);
                            }
                            break;
                        default:
                            printf(L_CYAN "\n\n Tu hésites et perds ton tour..." L_WHITE);
                            break;
                        }
                        if (PremierMonstre.pv > 0 && fuite != 1)
                        {
                            printf("\n%s a encore %dPV", PremierMonstre.nom, PremierMonstre.pv);
                        }
                        else if (PremierMonstre.pv <= 0)
                        {
                            printf(L_RED "\n%s va mourir.." L_WHITE, PremierMonstre.nom);
                        }
                    }
                }
                if (HeroPrincipal.pv <= 0)
                {
                    printf(L_RED "\nGAME OVER !!! :(" L_WHITE);
                }
                else if (PremierMonstre.pv <= 0)
                {
                    printf(L_GREEN "\nVictoire !!! :)" L_WHITE);
                    HeroPrincipal.orPossede = PremierMonstre.orPossede + HeroPrincipal.orPossede;
                    HeroPrincipal.potions = PremierMonstre.potions + HeroPrincipal.potions;
                    gagnerXp(&HeroPrincipal, PremierMonstre);
                    printf(L_CYAN "\nNotre Hero récupère %d or et les %d potions du monstre !"
                                  "\nTu possèdes donc %d or et %d potions" L_WHITE,
                           PremierMonstre.orPossede, PremierMonstre.potions, HeroPrincipal.orPossede, HeroPrincipal.potions);
                    boutique(&HeroPrincipal);
                    sauvegarder(HeroPrincipal);
                    printf(L_MAGENTA "\nQue veux tu faire ?\n 1.Combat suivant \n2.Retour au menu\n" L_WHITE);
                    scanf("%d", &continuer);
                }
                else if (fuite == 1)
                {
                    printf("\nTu as pris la fuite !");
                }
            } while (continuer == 1);
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
        case 3: // cas  e pour le menu pour quitter le jeu
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