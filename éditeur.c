
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"

void editer(SDL_Surface* cran)
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
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        i=event.button.x/ TAILLE_BLOCS;
                        j=event.button.y/ TAILLE_BLOCS;
                        carte[i][j]=MUR;
                        break;
                    case SDL_BUTTON_RIGHT:
                        i=event.button.x/ TAILLE_BLOCS;
                        j=event.button.y/ TAILLE_BLOCS;
                        carte[i][j]=VIDE;
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                i=event.motion.x/TAILLE_BLOCS;
                j=event.motion.y/TAILLE_BLOCS;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        cont=0;
                        break;
                    case SDLK_KP1:

                            carte[i][j]=MUR;

                        break;
                    case SDLK_KP2:

                            carte[i][j]=CAISSE;

                        break;
                    case SDLK_KP3:

                            carte[i][j]=OBJECTIF;

                        break;
                    case SDLK_KP4:

                            carte[i][j]=MARIO;

                        break;
                    case SDLK_KP5:

                            carte[i][j]=CAISSE_OK;

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
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseok);
    SDL_FreeSurface(mur);
    for(i=0;i<4;i++)
        SDL_FreeSurface(mario[i]);
}
