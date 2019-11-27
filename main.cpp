#include <iostream>
#include "bloc.h"
#include "coord.h"
#include "header.h"
#include "svgfile.h"

int main()
{
    Bloc*racine;
    lireFichier(racine);

    bool premier=1, ids=1;

    ///Fonction du TP7 permettant de reactualiser la sortie chaque seconde
    {
        Svgfile::s_verbose = false;
        Svgfile svgout;
        if(ids==1)
            racine->afficherIds(svgout,premier);
        else if(ids==0)
            racine->afficher(svgout,premier);
    }

    return 0;
}
