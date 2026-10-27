#include <stdio.h>
#include "color.h"
#include "personnage.h"
#include <string.h>

void sauvegarder(struct Personnage heros)
{
    FILE *fichier = fopen("sauvegarde.txt", "w");
    fprintf(fichier, "%s\n", heros.nom);
    fprintf(fichier, "%s\n", heros.classe);
    fprintf(fichier, "%d\n", heros.pv);
    fprintf(fichier, "%d\n", heros.attaque);
    fprintf(fichier, "%d\n", heros.pvMax);
    fprintf(fichier, "%d\n", heros.xp);
    fprintf(fichier, "%d\n", heros.niveau);
    fprintf(fichier, "%d\n", heros.orPossede);
    fprintf(fichier, "%d\n", heros.potions);
    fclose(fichier);
}
int charger(struct Personnage *heros)
{
    FILE *fichier = fopen("sauvegarde.txt", "r");   // "r" = read, lire
    if (fichier == NULL)
{
    printf(L_RED "\nAucune sauvegarde trouvée !\n" L_WHITE);
    return 0;
}
    fgets(heros->nom, 20, fichier);
    heros->nom[strcspn(heros->nom, "\n")] = '\0';
    fscanf(fichier, "%s\n", heros->classe);
    fscanf(fichier, "%d\n", &heros->pv);
    fscanf(fichier, "%d\n", &heros->attaque);
    fscanf(fichier, "%d\n", &heros->pvMax);
    fscanf(fichier, "%d\n", &heros->xp);
    fscanf(fichier, "%d\n", &heros->niveau);
    fscanf(fichier, "%d\n", &heros->orPossede);
    fscanf(fichier, "%d\n", &heros->potions);
    fclose(fichier);
    return 1;
    
}