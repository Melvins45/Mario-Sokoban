#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    #define NB_BLOCS_LARGEUR 12
    #define NB_BLOCS_LONGUEUR 12
    #define TAILLE_BLOCS 34
    #define LARGEUR_FENETRE TAILLE_BLOCS*NB_BLOCS_LARGEUR
    #define LONGUEUR_FENETRE TAILLE_BLOCS*NB_BLOCS_LONGUEUR

    enum{HAUT,BAS,GAUCHE,DROITE};
    enum{VIDE,MUR,CAISSE,CAISSE_OK,MARIO,OBJECTIF};

    void deplacerJoueur(long carte[][NB_BLOCS_LONGUEUR],SDL_Rect*posJ,long direction);
    void jouer(SDL_Surface *cran);
    int sauvegarderNiveau(long carte[][NB_BLOCS_LONGUEUR]);
    int chargerniveau(long carte[][NB_BLOCS_LONGUEUR]);
    void editer(SDL_Surface *cran);
    void gagne(int *contin,SDL_Surface *screen);


#endif // DEF_CONSTANTES
