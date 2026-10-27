#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "personnage.h"

void afficherfiche(struct Personnage perso)
{
    printf(L_WHITE "\nLe personnage se nomme : %s" L_GREEN "\nCaractéristiques :" L_CYAN "\nVitalité :%d" L_MAGENTA "\nAttaque :%d" L_BLUE "\nClasse : %s" L_YELLOW "\nIl est de niveau %d et possède %d xp."L_WHITE, perso.nom, perso.pv, perso.attaque, perso.classe, perso.niveau, perso.xp);
}

void gagnerXp(struct Personnage *progression, struct Personnage butinXp)
{
    int xpgagnee;
    xpgagnee = butinXp.xp;
    progression->xp += xpgagnee;
    if (progression->xp >= 100)
    {
        progression->niveau += 1;
        progression->pvMax *= 1.2;
        progression->pv = progression->pvMax;
        progression->attaque += 2;
        progression->xp -= 100;
        printf(L_CYAN "\n%s gagne %dxp !" L_WHITE, progression->nom, xpgagnee);
        printf(L_GREEN "\nNiveau supérieur !" L_WHITE);
        afficherfiche(*progression);
    }
    else
    {
        printf(L_CYAN "\n%s gagne %dxp !" L_WHITE, progression->nom, xpgagnee);
    }
}
void boutique(struct Personnage *achat)
{
    int choix;
    printf(L_MAGENTA"\n1.Acheter potion (20or)   2.Continuer\n"L_WHITE);
    choix = lireChoix();
    if(choix == 1)
    {
        if(achat->orPossede >= 20)
        {
            achat->orPossede -= 20;
            achat->potions += 1;
            printf(L_GREEN"\n Tu donnes 20 pièces d'or et gagne 1 potion !"L_WHITE);
        }
        else 
        {
            printf(L_RED"\nTu n'as pas assez d'or.."L_WHITE);
        }
    }
}
int lireChoix()
{
    int nombre;

    if (scanf("%d", &nombre) != 1)
    {
        while (getchar() != '\n');
        printf("Tape un chiffre, pas une lettre !\n");
        return -1;
    }
    return nombre; 
}