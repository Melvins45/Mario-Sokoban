#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"

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
    long i=0,j=0;

    if(fichier==NULL)
        return 0;
    for(i=0;i<NB_BLOCS_LONGUEUR;i++)
    {
        for(j=0;j<NB_BLOCS_LARGEUR;j++)
        {
           fprintf(fichier,'%d',carte[j][i]);
        }
    }
    fclose(fichier);
    return 1;
}
