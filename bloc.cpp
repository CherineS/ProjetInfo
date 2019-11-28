#include "bloc.h"

Bloc::Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur) :
        m_largeur{largeur},m_hauteur{hauteur},m_x{x},m_y{y},m_nom{nom},m_couleur{couleur}{
}

/**Si refpos et basepos
Bloc::Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur) :
        m_largeur{largeur},m_hauteur{hauteur},m_x{x},m_y{y},m_nom{nom},m_couleur{couleur},refpos{""},basepos{""}{
}

Bloc::Bloc(double largeur,double hauteur,std::string nom,std::string couleur,std::string rp,std::string bp) :
        m_largeur{largeur},m_hauteur{hauteur},m_x{0},m_y{0},m_nom{nom},m_couleur{couleur},refpos{rp},basepos{bp}{
}
**/


Bloc::Bloc() : m_largeur{0},m_hauteur{0},m_x{0},m_y{0},m_nom{"vide"},m_couleur{"noir"}{
}

Bloc::~Bloc()
{
        for(auto blocPtr : m_bloc_enfant)
                delete blocPtr;
}

std::string Bloc::GetNom() const
{
        return m_nom;
}

std::string Bloc::GetCouleur() const
{
        return m_couleur;
}

double Bloc::GetX() const
{
        return m_x;
}

double Bloc::GetY() const
{
        return m_y;
}

double Bloc::GetLargeur() const
{
        return m_largeur;
}

double Bloc::GetHauteur() const
{
        return m_hauteur;
}

Bloc* Bloc::GetConteneur() const
{
        return m_conteneur;
}

std::vector<Bloc*> Bloc::GetBlocsEnf() const
{
    return m_bloc_enfant;
}

void Bloc::SetBlocsEnf(Bloc* &aCopier)
{
    Bloc *bloc = new Bloc(aCopier->GetLargeur(),aCopier->GetHauteur(),aCopier->GetX(),aCopier->GetX(),
                          aCopier->GetNom(),aCopier->GetCouleur());

    m_bloc_enfant.push_back(bloc);
}

void Bloc::SetConteneur(Bloc* conteneur)
{
    m_conteneur=conteneur;
}

void Bloc::ajouterbloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur)
{
        Bloc *bloc = new Bloc(largeur,hauteur,x,y,nom,couleur);
/**        Bloc *bloc = new Bloc(largeur,hauteur,nom,couleur,refp,basep);       **/
        m_bloc_enfant.push_back(bloc);
}

void Bloc::afficher(Svgfile& output, bool& racine)
{
    std::vector<Bloc*>::iterator it_bloc;

    ///Afficher la racine
    if(racine==1)
    {
        output.addRect(m_x /*x1*/, m_y /*y1*/, m_x+m_largeur /*x2*/, m_y /*y2*/, m_x /*x3*/,m_y+m_hauteur /*y3*/,
                               m_x+m_largeur /*x4*/, m_y+m_hauteur /*y4*/, m_couleur,0.15,"black");
        racine=0;
    }

    for(it_bloc = m_bloc_enfant.begin(); it_bloc!=m_bloc_enfant.end(); ++it_bloc)
    {
            if((*it_bloc)->m_hauteur!=0)
            {
                //x1,y1,x2,y2,x3,y3,x4,y4,couleur,epaisseur,couleur_epaisseur
                output.addRect((*it_bloc)->m_x /*x1*/, (*it_bloc)->m_y /*y1*/, (*it_bloc)->m_x+(*it_bloc)->m_largeur /*x2*/, (*it_bloc)->m_y /*y2*/
                               ,(*it_bloc)->m_x /*x3*/,(*it_bloc)->m_y+(*it_bloc)->m_hauteur /*y3*/,(*it_bloc)->m_x+(*it_bloc)->m_largeur /*x4*/, (*it_bloc)->m_y+(*it_bloc)->m_hauteur /*y4*/,
                               (*it_bloc)->m_couleur,0.15,"black");
            }
            else ///Disque
                output.addDisk((*it_bloc)->m_x+(*it_bloc)->m_largeur/2 /*x*/, (*it_bloc)->m_y+(*it_bloc)->m_hauteur/2 /*y*/, (*it_bloc)->m_largeur/2 /*rayon*/,(*it_bloc)->m_couleur);

            if((*it_bloc)->m_bloc_enfant.size()!=0) // Si il possede des enfant
            {
                    (*it_bloc)->afficher(output,racine);
            }
    }
}

void Bloc::afficherIds(Svgfile& output, bool racine)
{
    afficher(output,racine);
    racine=0;

    std::vector<Bloc*>::iterator it_bloc;

        for(it_bloc = m_bloc_enfant.begin(); it_bloc!=m_bloc_enfant.end(); ++it_bloc)
        {
            if((*it_bloc)->m_hauteur==0) ///Contour disque
                output.addCircle((*it_bloc)->m_x+(*it_bloc)->m_largeur/2 /*x*/, (*it_bloc)->m_y+(*it_bloc)->m_hauteur/2 /*y*/, (*it_bloc)->m_largeur/2 /*rayon*/,2,"yellow");
            else ///Contour d'un rectangle
            {
                output.addRect((*it_bloc)->m_x,(*it_bloc)->m_y,(*it_bloc)->m_largeur+(*it_bloc)->m_x,(*it_bloc)->m_y,
                               (*it_bloc)->m_x,(*it_bloc)->m_hauteur+(*it_bloc)->m_y,(*it_bloc)->m_largeur+(*it_bloc)->m_x
                               ,(*it_bloc)->m_hauteur+(*it_bloc)->m_y,2,"yellow");
            }

            int decalerx=(*it_bloc)->m_nom.size()*3.5; ///Pour centrer le texte

            output.addText((*it_bloc)->m_x+((*it_bloc)->m_largeur/2)-decalerx-1,(*it_bloc)->m_y+((*it_bloc)->m_hauteur/2)+3-1
                                ,(*it_bloc)->m_nom,"yellow");
            output.addText((*it_bloc)->m_x+((*it_bloc)->m_largeur/2)-decalerx+1,(*it_bloc)->m_y+((*it_bloc)->m_hauteur/2)+1+3
                                ,(*it_bloc)->m_nom,"yellow");
            output.addText((*it_bloc)->m_x+((*it_bloc)->m_largeur/2)-decalerx-1,(*it_bloc)->m_y+((*it_bloc)->m_hauteur/2)+1+3
                                ,(*it_bloc)->m_nom,"yellow");
            output.addText((*it_bloc)->m_x+((*it_bloc)->m_largeur/2)-decalerx+1,(*it_bloc)->m_y+((*it_bloc)->m_hauteur/2)-1+3
                                ,(*it_bloc)->m_nom,"yellow");
            output.addText((*it_bloc)->m_x+((*it_bloc)->m_largeur/2)-decalerx,(*it_bloc)->m_y+((*it_bloc)->m_hauteur/2)+3
                            ,(*it_bloc)->m_nom,"black");

            if((*it_bloc)->m_bloc_enfant.size()!=0)
                        (*it_bloc)->afficherIds(output,racine);
        }
}

/*
void Bloc::collisions()
{
    std::vector<Bloc*> Freres=m_conteneur()->GetBlocsEnf();
    for(size_t i=0; i<Freres.size();++i)
    {
        ///On ne considere pas les collisions avec lui meme
        if(Freres[i]->GetNom()!=m_nom)
        {
            ///Si le bloc se deplace en x
            if(m_x<=Freres[i]->GetX())
                ///appeler fonction avancer +10
            else if(m_x+m_largeur>=Freres[i]->GetX+Freres[i]->GetLargeur)
                ///appeler fonction avancer -10

            ///Si le bloc se deplace en y
            if(m_y<=Freres[i]->GetY())
                ///appeler fonction avancer -10
            else if(m_y+m_hauteur>=Freres[i]->GetHauteur()+Freres[i]->GetHauteur())
                ///appeler fonction avancer +10
        }
    }
}
*/
