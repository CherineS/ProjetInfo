#include <iostream>
#include "bloc.h"
#include "coord.h"
#include "header.h"
#include "svgfile.h"

using namespace std;

int main()
{
        Bloc*racine;
        Svgfile svgout;

        lireFichier(racine);
        racine->calcul_xy_de_1_a_4(); // Initialise les point d'attache
        racine->afficher(svgout,1);




        return 0;
}
