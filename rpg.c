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
    int pvMax;
};
// Les fonctions que j'utilise dans le code
void afficherMenu()
{
    printf(L_GREEN "\n\n===MINI RPG===\n" L_WHITE);
    printf("1.Nouvelle partie\n");
    printf("2.Les règles du jeu\n");
    printf("3.Quitter le jeu\n");
    printf("Ton choix:");
}
void afficherfiche(struct Personnage perso)
{
    printf(L_WHITE "\nLe personnage se nomme : %s" L_GREEN "\nCaractéristiques :" L_CYAN "\nVitalité :%d" L_MAGENTA "\nAttaque :%d" L_BLUE "\nClasse : %s", perso.nom, perso.pv, perso.attaque, perso.classe);
}
void attaquer(struct Personnage *attaquant, struct Personnage *defenseur)
{
    int degats;                               // Définit la variable dégat pour les combats qui sera aléatoire avec rand
    degats = rand() % attaquant->attaque + 1; // rand renvoie un nombre très grand, donc on met un modulo et le +1 pour que l'attaque soit comprise entre 1 et les dégats max du personnage
    defenseur->pv -= degats;
    printf(L_RED "\n\n%s frappe %s ! -%dPV" L_WHITE, attaquant->nom, defenseur->nom, degats);
}
void soigner(struct Personnage *soignant)
{
    int soins;
    soins = rand() % 10 + 5;
    soignant->pv += soins;
    if (soignant->pv > soignant->pvMax)
    {
        soignant->pv = soignant->pvMax;
        printf(L_GREEN "\n\n%s récupère toute sa vie !" L_WHITE, soignant->nom);
    }
    else
    {
        printf(L_GREEN "\n\n%s se soigne de %dPV" L_WHITE, soignant->nom, soins);
    }
}
////////////////////////////////////////////////////////////////////////

int main()
{
    int choix;           // Variable pour le choix du menue
    int choix_de_classe; // Variable pour le choix de la classe
    srand(time(NULL));   // Permet l'aléatoire pour les combats

    do // boucle du menu principal
    {
        afficherMenu();

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
                    HeroPrincipal.pvMax = 120;
                    break;

                case 2: // L'archer tank et frappe de manière modéré
                    strcpy(HeroPrincipal.classe, "Archer");
                    HeroPrincipal.pv = 95;
                    HeroPrincipal.attaque = 5;
                    HeroPrincipal.pvMax = 95;
                    break;

                case 3: // Le voleur ne tank pas beaucoup mais frappe fort
                    strcpy(HeroPrincipal.classe, "Voleur");
                    HeroPrincipal.pv = 80;
                    HeroPrincipal.attaque = 7;
                    HeroPrincipal.pvMax = 80;
                    break;
                default:
                    printf(L_RED "Choix invalide\n" HOME L_WHITE);
                    break;
                }
            } while (choix_de_classe < 1 || choix_de_classe > 3); // Fin de la boucle choix

            afficherfiche(HeroPrincipal);
            struct Personnage PremierMonstre = {"Grok", "Gobelin", 60, 3, 60}; // Définit le premier monstre

            printf("\n\nUn %s sauvage apparait !!!", PremierMonstre.nom);
            printf(L_RED "\n\nVoici %s le %s !\n" L_WHITE, PremierMonstre.nom, PremierMonstre.classe);
            afficherfiche(PremierMonstre);
            int fuite = 0;
            while (HeroPrincipal.pv > 0 && PremierMonstre.pv > 0 && fuite !=1)
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
                    printf(L_BLUE"\n\n Que fais-tu ?" 
                                 "\n\n 1.Attaquer  2.Soigner  3.Fuir\n" L_WHITE);
                    scanf("%d", &action);
                    switch (action)
                    {
                    case 1:
                        attaquer(&HeroPrincipal, &PremierMonstre);
                        break;
                    case 2: 
                        soigner(&HeroPrincipal);
                        break;
                    case 3: 
                        fuite = rand() % 2;
                        if (fuite == 1)
                        {
                            printf(L_GREEN"\nLa fuite a réussi !"L_WHITE);
                        }
                        else 
                        {
                            printf(L_RED"\n%s te rattrape !"L_WHITE, PremierMonstre.nom);
                        }
                        break;
                    default:
                        printf(L_CYAN "\n\n Tu hésites et perds ton tour..."L_WHITE);
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
            }
            else if (fuite == 1)
            {
                printf("\nTu as pris la fuite !");
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