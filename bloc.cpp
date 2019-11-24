#include "bloc.h"

Bloc::Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur) :
        m_largeur{largeur},m_hauteur{hauteur},m_x{x},m_y{y},m_nom{nom},m_couleur{couleur}{
}

Bloc::Bloc() : m_largeur{0},m_hauteur{0},m_x{0},m_y{0},m_nom{"vide"},m_couleur{"noir"}{
}

Bloc::~Bloc()
{
        for(auto blocPtr : m_bloc_enfant)
                delete blocPtr;
}

Bloc* Bloc::GetConteneur()
{
        return m_conteneur;
}


void Bloc::ajouterbloc()
{
        Bloc *bloc = new Bloc();
        m_bloc_enfant.push_back(bloc);
}
