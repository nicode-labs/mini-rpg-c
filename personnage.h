#ifndef PERSONNAGE_H
#define PERSONNAGE_H

struct Personnage // Ce struct est la base de chaque personnage du jeu
{
    char nom[20];
    char classe[20];
    int pv;
    int attaque;
    int pvMax;
    int xp;
    int niveau;
    int orPossede;
    int potions;
};

void afficherMenu();
void afficherfiche(struct Personnage perso);
void attaquer(struct Personnage *attaquant, struct Personnage *defenseur);
void soigner(struct Personnage *soignant, int soins);
void gagnerXp(struct Personnage *progression, struct Personnage butinXp);
void boutique(struct Personnage *achat);
void sauvegarder(struct Personnage heros);
int charger(struct Personnage *heros);



#endif