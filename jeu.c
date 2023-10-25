#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"

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
            break;
        case DROITE:
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
            break;
        case GAUCHE:
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
            break;
    }
}

void jouer(SDL_Surface* cran)
{
    SDL_Surface *mario[4]={NULL};
    SDL_Surface *marioActuel=NULL, *mur=NULL, *caisseok=NULL, *caisse=NULL, *objectif=NULL;
    long carte[NB_BLOCS_LARGEUR][NB_BLOCS_LONGUEUR]={0};
    long i=0,j=0,objectifRestants=0;
    SDL_Event event;
    SDL_Rect posJoueur,pos;
    int cont=1;

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
      for(i=0;i<NB_BLOCS_LARGEUR;i++)
      {
          for(j=0;j<NB_BLOCS_LONGUEUR;j++)
          {
              pos.x=i*TAILLE_BLOCS;
              pos.y=j*TAILLE_BLOCS;
              switch(carte[i][j])
              {
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
                    objectifRestants=1;
                    break;

              }
          }
        }
          pos.x=posJoueur.x*TAILLE_BLOCS;
          pos.y=posJoueur.y*TAILLE_BLOCS;
          carte[posJoueur.x][posJoueur.y]=MARIO;
          SDL_BlitSurface(marioActuel,NULL,cran,&pos);
          if(!objectifRestants)
            cont=0;
          SDL_Flip(cran);

    }

    SDL_EnableKeyRepeat(0,0);
    SDL_FreeSurface(marioActuel);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseok);
    SDL_FreeSurface(mur);
    for(i=0;i<4;i++)
        SDL_FreeSurface(mario[i]);
}
