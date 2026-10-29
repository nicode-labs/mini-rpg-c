/* == MINI RPG Game == */
/* Code permettant d'afficher :
1. Nouvelle partie
2. Les règles du jeu
3. Quitter le jeu */

// Pour compiler le code, utilisez la commande suivante :
// gcc rpg.c combat.c sauvegarde.c personnage.c -o rpg -Wall

#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include <time.h>
#include <string.h>
#include "personnage.h"
#include <unistd.h>

// Les fonctions que j'utilise dans le code

void afficherMenu()
{
    printf(L_GREEN "\n\n===MINI RPG===\n" L_WHITE);
    ecrire("1.Nouvelle partie\n");
    ecrire("2.Les règles du jeu\n");
    ecrire("3.Quitter le jeu\n");
    ecrire(L_BLUE "\nTon choix:" L_WHITE);
}
void attendre(int secondes)
{
    fflush(stdout);
    sleep(secondes);
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

        choix = lireChoix();
        switch (choix) // Définit les plusieurs effets du choix du menu principal
        {
        case 1:
            ecrire(L_GREEN "Le jeu va commencer..\n\n" L_WHITE);
            struct Personnage HeroPrincipal;

            do // Boucle du choix de la classe
            {
                ecrire(L_BLUE "Quelle est ta classe ?\n" L_MAGENTA "1:Chevalier\n2:Archer\n3:Voleur\n" L_GREEN "4:Reprendre Sauvegarde\n");
                ecrire(L_CYAN "\n\nTon choix:" L_WHITE);
                choix_de_classe = lireChoix();
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
                    break;
                default:
                    printf(L_RED "Choix invalide\n" HOME L_WHITE);
                    break;
                }
            } while (choix_de_classe < 1 || choix_de_classe > 4); // Fin de la boucle choix
            if (choix_de_classe == 4)
            {
                printf(L_GREEN "\n Bon retour %s" L_WHITE, HeroPrincipal.nom);
            }
            else
            {
                printf(L_BLUE HOME "Comment se nomme le Hero:\n" L_WHITE);
                while (getchar() != '\n')
                    ;
                fgets(HeroPrincipal.nom, 20, stdin);
                HeroPrincipal.nom[strcspn(HeroPrincipal.nom, "\n")] = '\0';
            }

            afficherfiche(HeroPrincipal);
            char notrehero[200];
            snprintf(notrehero, 200, L_GREEN "\nNotre Hero a" L_BLUE " %d or " L_GREEN "et " L_MAGENTA "%d potions." L_WHITE, HeroPrincipal.orPossede, HeroPrincipal.potions);
            ecrire(notrehero);
            int continuer;
            do
            {
                continuer = 0;
                int nombre = rand() % 4;
                struct Personnage PremierMonstre = bestiaire[nombre]; // Définit le premier monstre
                attendre(2);

                printf(HOME "\n\n%s apparaît !!!", PremierMonstre.nom);
                attendre(1);
                char voicimonstre[200];
                snprintf(voicimonstre, 200, L_RED "\n\nVoici " L_BLUE "%s " L_RED "le " L_BLUE "%s !\n" L_WHITE, PremierMonstre.nom, PremierMonstre.classe);
                ecrire(voicimonstre);
                afficherfiche(PremierMonstre);
                attendre(1);
                int fuite = 0;
                while (HeroPrincipal.pv > 0 && PremierMonstre.pv > 0 && fuite != 1) // boucle comnat
                {
                    attaquer(&PremierMonstre, &HeroPrincipal);
                    attendre(1);
                    if (HeroPrincipal.pv > 0)
                    {
                        printf(HOME"%-10s  ", HeroPrincipal.nom);
                        afficherBarre(HeroPrincipal.pv, HeroPrincipal.pvMax);
                        printf(" %d/%d\n", HeroPrincipal.pv, HeroPrincipal.pvMax);
                    }
                    else if (HeroPrincipal.pv <= 0)
                    {
                        printf(L_RED "\n%s a pris un violent coup et ne pourra pas s'en remettre.." L_WHITE, HeroPrincipal.nom);
                    }

                    if (HeroPrincipal.pv > 0)
                    {
                        int action;
                        int rechoisir;
                        do
                        {
                            printf("%-10s  ", PremierMonstre.nom);
                            afficherBarre(PremierMonstre.pv, PremierMonstre.pvMax);
                            printf(" %d/%d\n", PremierMonstre.pv, PremierMonstre.pvMax);
                            ecrire(L_BLUE "\n\n Que veux-tu faire ?" L_CYAN "\n\n 1.Attaquer  2.Soigner  3.Fuir  4.Potion\n" L_WHITE);
                            action = lireChoix();
                            while (action < 1 || action > 4)
                            {
                                printf("Choisis 1 ou 2 ou 3 ou 4 !\n");
                                action = lireChoix();
                            }
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
                                    sleep(1);
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
                                    if (HeroPrincipal.pv > (HeroPrincipal.pvMax * 80) / 100)
                                    {
                                        int choix_potion;
                                        char tudoispotion[200];
                                        snprintf(tudoispotion, 200, L_YELLOW "\nTu dois avoir peur pour utiliser une potion avec toute cette vie" L_WHITE);
                                        ecrire(tudoispotion);
                                        char surpotion[200];
                                        snprintf(surpotion, 200, L_MAGENTA "\nTu es sûr ? \n1.Utiliser une potion \n2.Etre raisonnable\n" L_WHITE);
                                        ecrire(surpotion);
                                        choix_potion = lireChoix();
                                        while (choix_potion < 1 || choix_potion > 2)
                                        {
                                            printf("Choisis 1 ou 2 !\n");
                                            choix_potion = lireChoix();
                                        }
                                        switch (choix_potion)
                                        {
                                        case 1:
                                            HeroPrincipal.potions -= 1;
                                            soigner(&HeroPrincipal, 40);
                                            break;
                                        case 2:
                                            ecrire(L_GREEN "\nTu ranges ta potion." L_WHITE);
                                            rechoisir = 1;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        HeroPrincipal.potions -= 1;
                                        soigner(&HeroPrincipal, 40);
                                    }
                                }
                                else
                                {
                                    ecrire(L_RED "\nTu n'as pas de potion..." L_WHITE);
                                }
                                break;
                            default:
                                ecrire(L_CYAN "\n\n Tu hésites et perds ton tour..." L_WHITE);
                                break;
                            }
                        } while (rechoisir == 1);
                        if (PremierMonstre.pv > 0 && fuite != 1)
                        {
                            char tuapv[200];
                            snprintf(tuapv, 200, "\n%s a encore %dPV", PremierMonstre.nom, PremierMonstre.pv);
                            ecrire(tuapv);
                            
                        }
                        else if (PremierMonstre.pv <= 0)
                        {
                            printf(L_RED "\n%s va mourir.." L_WHITE, PremierMonstre.nom);
                        }
                    }
                    if (HeroPrincipal.pv <= 0)
                    {
                        printf(L_RED "\nGAME OVER !!! :(" L_WHITE);
                    }
                    else if (PremierMonstre.pv <= 0)
                    {
                        sleep(1);
                        printf(L_GREEN HOME "\nVictoire !!! :)" L_WHITE);
                        HeroPrincipal.orPossede += PremierMonstre.orPossede;
                        HeroPrincipal.potions += PremierMonstre.potions;
                        gagnerXp(&HeroPrincipal, PremierMonstre);
                        if (PremierMonstre.potions == 0)
                        {
                            printf(L_CYAN "\nNotre Hero récupère %d or !"
                                          "\nTu possèdes donc %d or et %d potions" L_WHITE,
                                   PremierMonstre.orPossede, HeroPrincipal.orPossede, HeroPrincipal.potions);
                        }
                        else
                        {
                            printf(L_CYAN "\nNotre Hero récupère %d or et les %d potions du monstre !"
                                          "\nTu possèdes donc %d or et %d potions" L_WHITE,
                                   PremierMonstre.orPossede, PremierMonstre.potions, HeroPrincipal.orPossede, HeroPrincipal.potions);
                        }

                        boutique(&HeroPrincipal);
                        sauvegarder(HeroPrincipal);
                        printf(L_MAGENTA "\nQue veux tu faire ?\n 1.Combat suivant \n2.Retour au menu\n" L_WHITE);
                        continuer = lireChoix();
                        while (continuer < 1 || continuer > 2)
                        {
                            printf("Choisis 1 ou 2 !\n");
                            continuer = lireChoix();
                        }
                    }
                    else if (fuite == 1)
                    {
                        printf("\nTu as pris la fuite !");
                    }
                } //fin de la boucle combat
            } while (continuer == 1); //fin du do combat suivant
            break;

        case 2: // case pour le deuxième menu des règles du jeu
            ecrire(L_CYAN "\n\nVoici les règles du jeu :\n");
            sleep(1);
            printf("\n\n- Tu incarnes un heros qui affronte des monstres au tour par tour.\n");
            printf("- A chaque tour, tu choisis : attaquer, te soigner, fuir ou utiliser une potion.\n");
            printf("- Le monstre riposte apres chacune de tes actions.\n");
            printf("- Si les PV du monstre tombent a 0, tu gagnes de l'XP.\n");
            printf("- Assez d'XP = tu montes de niveau et deviens plus fort.\n");
            printf("- Si tes PV tombent a 0... Game Over !\n" L_WHITE);
            break;
        case 3: // case pour le menu pour quitter le jeu
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