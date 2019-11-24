#ifndef BLOC_H_INCLUDED
#define BLOC_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class Bloc
{
public :
    double m_largeur, m_hauteur, m_x, m_y;
    std::string m_nom, m_couleur;
    std::vector<Bloc*> m_bloc_enfant;
    Bloc* m_conteneur;

//public :
    Bloc(double largeur, double hauteur, double x, double y, std::string nom, std::string couleur);
    Bloc();
    ~Bloc();
    Bloc* GetConteneur();
    void ajouterbloc();
};

Bloc* ajouterFichier(double& larg, double& haut, double& x, double& y, std::string& id, std::string& color);
void lireFichier(Bloc*& racine);

#endif // BLOC_H_INCLUDED
