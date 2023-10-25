
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
void jouer(SDL_Surface* ecran);
void editer(SDL_Surface* ecran);

int main ( int argc, char** argv )
{
    SDL_Surface* ecran=NULL;
    SDL_Surface* menu=NULL;

    SDL_Event event;
    bool continuer=true;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            fprintf(stderr, "Erreur d'initialisation de la SDL ");
            exit(EXIT_FAILURE);
        }

    SDL_WM_SetIcon(IMG_Load("caisse.jpg"), NULL);
    ecran=SDL_SetVideoMode(LONGUEUR_FENETRE,LARGEUR_FENETRE,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mario Sokoban",NULL);
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    menu=IMG_Load("menu.jpg");
    SDL_Rect posMenu;
    posMenu.x=0;
    posMenu.y=0;
    SDL_BlitSurface(menu,NULL,ecran,&posMenu);




    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer=false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP1:
                        jouer(ecran);
                        break;
                    case SDLK_KP2:
                        editer(ecran);
                        break;
                    case SDLK_ESCAPE:
                        continuer=false;
                        break;
                }
                break;
        }
        SDL_BlitSurface(menu,NULL,ecran,&posMenu);
        SDL_Flip(ecran);
    }


    SDL_Quit();
    return EXIT_SUCCESS;
}

void jouer(SDL_Surface* cran)
{
    SDL_Surface *mario[4]={NULL};
    SDL_Surface *marioActuel=NULL, *mur=NULL, *caisseok=NULL, *caisse=NULL, *objectif=NULL, *vide=NULL;
    long carte[NB_BLOCS_LARGEUR][NB_BLOCS_LONGUEUR]={0};
    long i=0,j=0,objectifRestants=0;
    SDL_Event event;
    SDL_Rect posJoueur,pos;
    int cont=1;

    vide=SDL_CreateRGBSurface(SDL_HWSURFACE,TAILLE_BLOCS,TAILLE_BLOCS,32,0,0,0,0);
    SDL_FillRect(vide,NULL,SDL_MapRGB(vide->format,255,255,255));
    mur=IMG_Load("mur.jpg");
    objectif=IMG_Load("objectif.png");
    caisse=IMG_Load("caisse.jpg");
    caisseok=IMG_Load("caisse_ok.jpg");
    mario[HAUT]=IMG_Load("mario_haut.gif");
    mario[BAS]=IMG_Load("mario_bas.gif");
    mario[DROITE]=IMG_Load("mario_droite.gif");
    mario[GAUCHE]=IMG_Load("mario_gauche.gif");
    marioActuel=mario[BAS];

    if(!chargerniveau(carte))
        exit(EXIT_FAILURE);

    SDL_FillRect(cran,NULL,SDL_MapRGB(cran->format,255,255,255));
    SDL_EnableKeyRepeat(100, 100);
    while(cont)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
      {
        case SDL_QUIT:
            cont=0;
            break;
        case SDL_KEYDOWN:
            for(i=0;i<NB_BLOCS_LARGEUR;i++)
                {
                    for(j=0;j<NB_BLOCS_LONGUEUR;j++)
                        {
                            if(carte[i][j]==MARIO)
                            {
                                posJoueur.x=i;
                                posJoueur.y=j;
                                carte[i][j]=VIDE;
                            }
                        }
                }
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    cont=0;
                    break;
                case SDLK_UP:
                    marioActuel=mario[HAUT];
                    deplacerJoueur(carte,&posJoueur,HAUT);
                    break;
                case SDLK_DOWN:
                    marioActuel=mario[BAS];
                    deplacerJoueur(carte,&posJoueur,BAS);
                    break;
                case SDLK_LEFT:
                    marioActuel=mario[GAUCHE];
                    deplacerJoueur(carte,&posJoueur,GAUCHE);
                    break;
                case SDLK_RIGHT:
                    marioActuel=mario[DROITE];
                    deplacerJoueur(carte,&posJoueur,DROITE);
                    break;
            }
            break;

      }
      objectifRestants=0;
      SDL_FillRect(cran,NULL,SDL_MapRGB(cran->format,255,255,255));
      for(i=0;i<NB_BLOCS_LARGEUR;i++)
      {
          for(j=0;j<NB_BLOCS_LONGUEUR;j++)
          {
              pos.x=i*TAILLE_BLOCS;
              pos.y=j*TAILLE_BLOCS;
              switch(carte[i][j])
              {
                case VIDE:
                    SDL_BlitSurface(vide,NULL,cran,&pos);
                    break;
                case MUR:
                    SDL_BlitSurface(mur,NULL,cran,&pos);
                    break;
                case CAISSE_OK:
                    SDL_BlitSurface(caisseok,NULL,cran,&pos);
                    break;
                case CAISSE:
                    SDL_BlitSurface(caisse,NULL,cran,&pos);
                    break;
                case MARIO:
                    SDL_BlitSurface(marioActuel,NULL,cran,&pos);
                    break;
                case OBJECTIF:
                    SDL_BlitSurface(objectif,NULL,cran,&pos);
                    objectifRestants=1;
                    break;
              }
          }
        }

          if(!objectifRestants)
            gagne(&cont,cran);
          SDL_Flip(cran);
    }

    SDL_EnableKeyRepeat(0,0);
    SDL_FreeSurface(marioActuel);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseok);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(vide);
    for(i=0;i<4;i++)
        SDL_FreeSurface(mario[i]);
}

void gagne(int *contin,SDL_Surface *screen)
{
    SDL_Event event;
    SDL_Surface *bravo=NULL;
    bravo=IMG_Load("bravo.jpg");
    SDL_Rect posi;
    posi.x=0;
    posi.y=0;
    SDL_BlitSurface(bravo,NULL,screen,&posi);
    SDL_Flip(screen);
    int continuer=1;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer=0;
                break;
            case SDL_KEYDOWN:
                continuer=0;
                *contin=0;
                break;
        }
    }
    SDL_FreeSurface(bravo);
}

void deplacerJoueur(long carte[][NB_BLOCS_LONGUEUR],SDL_Rect*posJ,long direction)
{
    switch(direction)
    {
        case HAUT:
            if(posJ->y-1<0)
            break;
            if(carte[posJ->x][posJ->y-1]==MUR)
            break;
            if((carte[posJ->x][posJ->y-1]==CAISSE || carte[posJ->x][posJ->y-1]==CAISSE_OK) &&
                (posJ->y-2<0 || carte[posJ->x][posJ->y-2]==MUR || carte[posJ->x][posJ->y-2]==CAISSE || carte[posJ->x][posJ->y-2]==CAISSE_OK))
                    break;
            posJ->y--;
            if(carte[posJ->x][posJ->y]==CAISSE )
            {
                if(carte[posJ->x][posJ->y-1]==OBJECTIF)
                    carte[posJ->x][posJ->y-1]=CAISSE_OK;
                if(carte[posJ->x][posJ->y-1]==VIDE)
                    carte[posJ->x][posJ->y-1]=CAISSE;
            }
            if(carte[posJ->x][posJ->y]==CAISSE_OK)
            {
                if(carte[posJ->x][posJ->y-1]==OBJECTIF)
                    carte[posJ->x][posJ->y-1]=CAISSE_OK;
                if(carte[posJ->x][posJ->y-1]==VIDE)
                    carte[posJ->x][posJ->y-1]=CAISSE;
                    carte[posJ->x][posJ->y]=OBJECTIF;
            }
            carte[posJ->x][posJ->y]=MARIO;
            break;
        case BAS:
            if(posJ->y+1>11)
            break;
            if(carte[posJ->x][posJ->y+1]==MUR)
            break;
            if((carte[posJ->x][posJ->y+1]==CAISSE || carte[posJ->x][posJ->y+1]==CAISSE_OK) &&
                (posJ->y+2>11 || carte[posJ->x][posJ->y+2]==MUR || carte[posJ->x][posJ->y+2]==CAISSE || carte[posJ->x][posJ->y+2]==CAISSE_OK))
                    break;
            posJ->y++;
            if(carte[posJ->x][posJ->y]==CAISSE )
            {
                if(carte[posJ->x][posJ->y+1]==OBJECTIF)
                    carte[posJ->x][posJ->y+1]=CAISSE_OK;
                if(carte[posJ->x][posJ->y+1]==VIDE)
                    carte[posJ->x][posJ->y+1]=CAISSE;
            }
            if(carte[posJ->x][posJ->y]==CAISSE_OK)
            {
                if(carte[posJ->x][posJ->y+1]==OBJECTIF)
                    carte[posJ->x][posJ->y+1]=CAISSE_OK;
                if(carte[posJ->x][posJ->y+1]==VIDE)
                    carte[posJ->x][posJ->y+1]=CAISSE;
                    carte[posJ->x][posJ->y]=OBJECTIF;
            }
            carte[posJ->x][posJ->y]=MARIO;
            break;
        case GAUCHE:
            if(posJ->x-1<0)
            break;
            if(carte[posJ->x-1][posJ->y]==MUR)
            break;
            if((carte[posJ->x-1][posJ->y]==CAISSE || carte[posJ->x-1][posJ->y]==CAISSE_OK) &&
                (posJ->x-2<0 || carte[posJ->x-2][posJ->y]==MUR || carte[posJ->x-2][posJ->y]==CAISSE || carte[posJ->x-2][posJ->y]==CAISSE_OK))
                    break;
            posJ->x--;
            if(carte[posJ->x][posJ->y]==CAISSE )
            {
                if(carte[posJ->x-1][posJ->y]==OBJECTIF)
                    carte[posJ->x-1][posJ->y]=CAISSE_OK;
                if(carte[posJ->x-1][posJ->y]==VIDE)
                    carte[posJ->x-1][posJ->y]=CAISSE;
            }
            if(carte[posJ->x][posJ->y]==CAISSE_OK)
            {
                if(carte[posJ->x-1][posJ->y]==OBJECTIF)
                    carte[posJ->x-1][posJ->y]=CAISSE_OK;
                if(carte[posJ->x-1][posJ->y]==VIDE)
                    carte[posJ->x-1][posJ->y]=CAISSE;
                carte[posJ->x][posJ->y]=OBJECTIF;
            }
            carte[posJ->x][posJ->y]=MARIO;
            break;
        case DROITE:
            if(posJ->x+1>11)
            break;
            if(carte[posJ->x+1][posJ->y]==MUR)
            break;
            if((carte[posJ->x+1][posJ->y]==CAISSE || carte[posJ->x+1][posJ->y]==CAISSE_OK) &&
                (posJ->x+2>11 || carte[posJ->x+2][posJ->y]==MUR || carte[posJ->x+2][posJ->y]==CAISSE || carte[posJ->x+2][posJ->y]==CAISSE_OK))
                    break;
            posJ->x++;
            if(carte[posJ->x][posJ->y]==CAISSE )
            {
                if(carte[posJ->x+1][posJ->y]==OBJECTIF)
                    carte[posJ->x+1][posJ->y]=CAISSE_OK;
                if(carte[posJ->x+1][posJ->y]==VIDE)
                    carte[posJ->x+1][posJ->y]=CAISSE;
            }
            if(carte[posJ->x][posJ->y]==CAISSE_OK)
            {
                if(carte[posJ->x+1][posJ->y]==OBJECTIF)
                    carte[posJ->x+1][posJ->y]=CAISSE_OK;
                if(carte[posJ->x+1][posJ->y]==VIDE)
                    carte[posJ->x+1][posJ->y]=CAISSE;
                carte[posJ->x][posJ->y]=OBJECTIF;
            }
            carte[posJ->x][posJ->y]=MARIO;
            break;
    }
}

void editer(SDL_Surface* cran)
{
    SDL_Surface *mario[4]={NULL};
    SDL_Surface *marioActuel=NULL, *mur=NULL, *caisseok=NULL, *caisse=NULL, *objectif=NULL, *vide=NULL;
    long carte[NB_BLOCS_LARGEUR][NB_BLOCS_LONGUEUR]={0};
    long i=0,j=0,objectifRestants=0;
    SDL_Event event;
    SDL_Rect posJoueur,pos;
    int cont=1,clicG=0,clicD=0,objetActuel=1;

    vide=SDL_CreateRGBSurface(SDL_HWSURFACE,TAILLE_BLOCS,TAILLE_BLOCS,32,0,0,0,0);
    SDL_FillRect(vide,NULL,SDL_MapRGB(vide->format,255,255,255));
    mur=IMG_Load("mur.jpg");
    objectif=IMG_Load("objectif.png");
    caisse=IMG_Load("caisse.jpg");
    caisseok=IMG_Load("caisse_ok.jpg");
    mario[HAUT]=IMG_Load("mario_haut.gif");
    mario[BAS]=IMG_Load("mario_bas.gif");
    mario[DROITE]=IMG_Load("mario_droite.gif");
    mario[GAUCHE]=IMG_Load("mario_gauche.gif");
    marioActuel=mario[BAS];
    SDL_FillRect(cran,NULL,SDL_MapRGB(cran->format,255,255,255));

    int inta=chargerniveau(carte);

    while(cont)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                cont=0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        i=event.button.x/ TAILLE_BLOCS;
                        j=event.button.y/ TAILLE_BLOCS;
                        carte[i][j]=objetActuel;
                        clicG=1;
                        break;
                    case SDL_BUTTON_RIGHT:
                        i=event.button.x/ TAILLE_BLOCS;
                        j=event.button.y/ TAILLE_BLOCS;
                        carte[i][j]=VIDE;
                        clicD=1;
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                 if (event.button.button == SDL_BUTTON_LEFT)
                    clicG = 0;
                 else if (event.button.button == SDL_BUTTON_RIGHT)
                    clicD= 0;
                break;
            case SDL_MOUSEMOTION:
                if(clicG)
                     carte[event.motion.x / TAILLE_BLOCS][event.motion.y / TAILLE_BLOCS] = objetActuel;
                else if(clicD)
                     carte[event.motion.x / TAILLE_BLOCS][event.motion.y / TAILLE_BLOCS] = VIDE;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        cont=0;
                        break;
                    case SDLK_KP1:
                            objetActuel=MUR;
                        break;
                    case SDLK_KP2:
                            objetActuel=CAISSE;
                        break;
                    case SDLK_KP3:
                            objetActuel=OBJECTIF;
                        break;
                    case SDLK_KP4:
                            objetActuel=MARIO;
                        break;
                    case SDLK_KP5:
                            objetActuel=CAISSE_OK;
                        break;
                    case SDLK_s:
                        sauvegarderNiveau(carte);
                        break;
                }
                break;
        }
        for(i=0;i<NB_BLOCS_LARGEUR;i++)
      {
          for(j=0;j<NB_BLOCS_LONGUEUR;j++)
          {
              pos.x=i*TAILLE_BLOCS;
              pos.y=j*TAILLE_BLOCS;
              switch(carte[i][j])
              {
                case VIDE:
                    SDL_BlitSurface(vide,NULL,cran,&pos);
                    break;
                case MUR:
                    SDL_BlitSurface(mur,NULL,cran,&pos);
                    break;
                case CAISSE_OK:
                    SDL_BlitSurface(caisseok,NULL,cran,&pos);
                    break;
                case CAISSE:
                    SDL_BlitSurface(caisse,NULL,cran,&pos);
                    break;
                case OBJECTIF:
                    SDL_BlitSurface(objectif,NULL,cran,&pos);
                    break;
                case MARIO:
                    SDL_BlitSurface(marioActuel,NULL,cran,&pos);
                    break;
              }
          }
        }
        SDL_Flip(cran);
    }

    SDL_EnableKeyRepeat(0,0);
    SDL_FreeSurface(marioActuel);
    SDL_FreeSurface(vide);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseok);
    SDL_FreeSurface(mur);
    for(i=0;i<4;i++)
        SDL_FreeSurface(mario[i]);
}

int chargerniveau(long carte[][NB_BLOCS_LONGUEUR])
{
    FILE *fichier=NULL;
    fichier=fopen("niveaux.txt","r");
    char ligneFichier[(NB_BLOCS_LARGEUR*NB_BLOCS_LONGUEUR)+1]={0};
    long i=0,j=0;
    if(fichier==NULL)
        return 0;
    if (fichier!=NULL)
    {
        fgets(ligneFichier,(NB_BLOCS_LARGEUR*NB_BLOCS_LONGUEUR)+1,fichier);
        fclose(fichier);
    }
    for(i=0;i<NB_BLOCS_LONGUEUR;i++)
    {
        for(j=0;j<NB_BLOCS_LARGEUR;j++)
        {
            switch(ligneFichier[(i*NB_BLOCS_LARGEUR)+j])
            {
                case '0':
                    carte[j][i]=0;
                    break;
                case '1':
                    carte[j][i]=1;
                    break;
                case '2':
                    carte[j][i]=2;
                    break;
                case '3':
                    carte[j][i]=3;
                    break;
                case '4':
                    carte[j][i]=4;
                    break;
                case '5':
                    carte[j][i]=5;
                    break;
            }
        }
    }
    return 1;
}

int sauvegarderNiveau(long carte[][NB_BLOCS_LONGUEUR])
{
    FILE *fichier=NULL;
    fichier=fopen("niveaux.txt","w");
    char ligneFichier[(NB_BLOCS_LARGEUR*NB_BLOCS_LONGUEUR)+1]={0};
    ligneFichier[NB_BLOCS_LARGEUR*NB_BLOCS_LONGUEUR]='/0';
    long i=0,j=0;

    if(fichier==NULL)
        return 0;
    for(i=0;i<NB_BLOCS_LONGUEUR;i++)
    {
        for(j=0;j<NB_BLOCS_LARGEUR;j++)
        {
           switch(carte[j][i])
            {
                case 0:
                    ligneFichier[(i*NB_BLOCS_LARGEUR)+j]='0';
                    break;
                case 1:
                    ligneFichier[(i*NB_BLOCS_LARGEUR)+j]='1';
                    break;
                case 2:
                    ligneFichier[(i*NB_BLOCS_LARGEUR)+j]='2';
                    break;
                case 3:
                    ligneFichier[(i*NB_BLOCS_LARGEUR)+j]='3';
                    break;
                case 4:
                    ligneFichier[(i*NB_BLOCS_LARGEUR)+j]='4';
                    break;
                case 5:
                    ligneFichier[(i*NB_BLOCS_LARGEUR)+j]='5';
                    break;
            }
        }
    }

    fprintf(fichier,"%s",ligneFichier);
    fclose(fichier);
    return 1;
}

