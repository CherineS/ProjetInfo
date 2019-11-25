#include <iostream>
#include "bloc.h"
#include "coord.h"
#include "header.h"
#include "svgfile.h"

int main()
{
        Bloc*racine;
        lireFichier(racine);
        Svgfile svgout;


        racine->afficher(svgout);



        return 0;
}
