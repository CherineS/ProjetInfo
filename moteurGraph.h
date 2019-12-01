#ifndef MOTEUR_GRAPHIQUE
#define MOTEUR_GRAPHIQUE

#include "bloc.h"
#include<iostream>
#include<string>

class MoteurGraph{

public:

MoteurGraph(Bloc& racine);
~MoteurGraph();
static void calculerPoid(Bloc& racine ,bool bracine);
static void detecterColision(Bloc& racine);
static void afficherColision(double x, double y);
static void deplacer();


private:

Bloc& m_racine; // une ref pour utiliser le polymorphisme

};



#endif
