#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "personnage.h"

void attaquer(struct Personnage *attaquant, struct Personnage *defenseur)
{
    int degats;
    degats = attaquant->attaque + rand() % attaquant->attaque; // dégâts entre l’attaque et le double de l’attaque
    defenseur->pv -= degats;
    printf(L_RED "\n\n%s frappe %s ! -%dPV" L_WHITE, attaquant->nom, defenseur->nom, degats);
}
void soigner(struct Personnage *soignant, int soins)
{
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