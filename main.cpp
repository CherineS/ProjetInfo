#include <iostream>
#include "bloc.h"
#include "coord.h"
#include "header.h"
#include "svgfile.h"

using namespace std;

int main()
{
        Bloc*racine;
        lireFichier(racine);
        Svgfile svgout;

        racine->calcul_xy_de_1_a_4(); // Initialise les point d'attache
        racine->afficher(svgout);



        return 0;
}
