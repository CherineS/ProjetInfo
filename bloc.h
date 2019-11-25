#ifndef BLOC_H_INCLUDED
#define BLOC_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "svgfile.h"

class Bloc
{
private:
double m_largeur;
double m_hauteur;
double m_x;
double m_y;
std::string m_nom;
std::string m_couleur;
std::vector<Bloc*> m_bloc_enfant;
Bloc* m_conteneur;

friend Bloc* ajouterFichier(double& larg, double& haut, double& x, double& y, std::string& id, std::string& color);
friend void lireFichier(Bloc*& racine);

public:
Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur);
Bloc();
~Bloc();
void ajouterbloc();
Bloc* GetConteneur();
void afficher(Svgfile& output);


};


#endif // BLOC_H_INCLUDED
