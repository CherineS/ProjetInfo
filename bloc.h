#ifndef BLOC_H_INCLUDED
#define BLOC_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "svgfile.h"
#include <map>

class Bloc
{

public:
Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur);
Bloc();
~Bloc();
void ajouterbloc();
Bloc* GetConteneur();
void afficher(Svgfile& output);
void calcule_xy_ref_base_pos();
void calcul_xy_de_1_a_4();

private:
double m_largeur;
double m_hauteur;
double m_x;
double m_y;
std::string m_nom;
std::string m_couleur;
std::vector<Bloc*> m_bloc_enfant;
Bloc* m_conteneur;

double m_x1;
double m_x2;
double m_x3;
double m_x4;
double m_y1;
double m_y2;
double m_y3;
double m_y4;

std::string refpos; // Point d'encrage du bloc parrent
std::string basepos; // Point d'encrage du bloc enfant
std::string endpos; // Point du bloc parrent maximal d'encrage lors de la translation

double x_refpos;
double y_refpos;
double x_basepos;
double y_basepos;

friend Bloc* ajouterFichier(double& larg, double& haut, double& x, double& y, std::string& id, std::string& color);
friend void lireFichier(Bloc*& racine);

};


#endif // BLOC_H_INCLUDED
