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

void Bloc::afficher(Svgfile& output)
{
        std::vector<Bloc*>::iterator it_bloc;


        for(it_bloc = m_bloc_enfant.begin(); it_bloc!=m_bloc_enfant.end(); ++it_bloc)
        {
                //x1,y1,x2,y2,x3,y3,x4,y4,couleur,epaisseur,couleur_epaisseur
                output.addRect((*it_bloc)->m_x /*x1*/, (*it_bloc)->m_y /*y1*/, (*it_bloc)->m_x+(*it_bloc)->m_largeur /*x2*/, (*it_bloc)->m_y /*y2*/
                               ,(*it_bloc)->m_x /*x3*/,(*it_bloc)->m_y+(*it_bloc)->m_hauteur /*y3*/,(*it_bloc)->m_x+(*it_bloc)->m_largeur /*x4*/, (*it_bloc)->m_y+(*it_bloc)->m_hauteur /*y4*/,
                               (*it_bloc)->m_couleur,0.15,"black");
                if((*it_bloc)->m_bloc_enfant.size()!=0) // Si il possede des enfant
                {
                        (*it_bloc)->afficher(output);
                }


        }

}
