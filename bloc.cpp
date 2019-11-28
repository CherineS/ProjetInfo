#include "bloc.h"

Bloc::Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur) :
        m_largeur{largeur},m_hauteur{hauteur},m_x1{x},m_y1{y},m_nom{nom},m_couleur{couleur}, m_conteneur(nullptr){
}

/**Si refpos et basepos
Bloc::Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur) :
        m_largeur{largeur},m_hauteur{hauteur},m_x{x},m_y{y},m_nom{nom},m_couleur{couleur},refpos{""},basepos{""}{
}

Bloc::Bloc(double largeur,double hauteur,std::string nom,std::string couleur,std::string rp,std::string bp) :
        m_largeur{largeur},m_hauteur{hauteur},m_x{0},m_y{0},m_nom{nom},m_couleur{couleur},refpos{rp},basepos{bp}{
}
**/


Bloc::Bloc() : m_largeur{0},m_hauteur{0},m_x1{0},m_y1{0},m_nom{"vide"},m_couleur{"noir"}, m_conteneur(nullptr){
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

void Bloc::afficher(Svgfile& output, bool racine)
{
    std::vector<Bloc*>::iterator it_bloc;

    ///Afficher la racine
    if(racine==1)
    {
        output.addRect(m_x /*x1*/, m_y /*y1*/, m_x+m_largeur /*x2*/, m_y /*y2*/, m_x /*x3*/,m_y+m_hauteur /*y3*/,
                               m_x+m_largeur /*x4*/, m_y+m_hauteur /*y4*/, m_couleur,0.15,"black");
        racine=0;
    }

        ///Afficher la racine
        if(racine==1)
        {
                output.addRect(m_x1,m_y1,m_x2,m_y1,m_x1,m_y3,m_x2, m_y3, m_couleur,0.15,"black");
                racine=0;
        }


        for(it_bloc = m_bloc_enfant.begin(); it_bloc!=m_bloc_enfant.end(); ++it_bloc)
        {

                output.addRect((*it_bloc)->m_x1 /*x1*/,(*it_bloc)->m_y1 /*y1*/,(*it_bloc)->m_x2 /*x2*/,(*it_bloc)->m_y1 /*y2*/,(*it_bloc)->m_x1 /*x3*/,(*it_bloc)->m_y3 /*y3*/,(*it_bloc)->m_x2 /*4*/,(*it_bloc)->m_y3 /*y4*/,(*it_bloc)->m_couleur,0.1,"black");

                // On envoie les enfant de maniere recursive
                if((*it_bloc)->m_bloc_enfant.size()!=0) // Si il possede des enfant
                {
                        (*it_bloc)->afficher(output,0);
                }

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

void Bloc::calcul_xy_de_1_a_4()
{
        std::vector<Bloc*>::iterator it_bloc;

        for(it_bloc = m_bloc_enfant.begin(); it_bloc!=m_bloc_enfant.end(); ++it_bloc)
        {

                if((*it_bloc)->m_conteneur != nullptr) // Si il a un parent on regarde sa position d'encrage pour orienter le bloc ver la droite ou la gauche
                {                                         // On base la position sur refpos du parent

                        //On orriente le rect ver gauche
                        if((*it_bloc)->basepos=="tl")
                        {
                                (*it_bloc)->m_x1=(*it_bloc)->m_conteneur->x_refpos;         /*x1*/
                                (*it_bloc)->m_x2=(*it_bloc)->m_conteneur->x_refpos+(*it_bloc)->m_largeur;
                                (*it_bloc)->m_y1=(*it_bloc)->m_conteneur->y_refpos;         /*y1*/
                                (*it_bloc)->m_y3=(*it_bloc)->m_conteneur->y_refpos+(*it_bloc)->m_hauteur;
                        }
                        else if ((*it_bloc)->basepos=="ml")
                        {

                                (*it_bloc)->m_x1=(*it_bloc)->m_conteneur->x_refpos /*x1*/;
                                (*it_bloc)->m_x2=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur /*x2*/;
                                (*it_bloc)->m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur/(double)2 /*y1*/;
                                (*it_bloc)->m_y3=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur/(double)2 /*y3*/;
                        }
                        else if ((*it_bloc)->basepos=="bl")
                        {
                                (*it_bloc)->m_x1=(*it_bloc)->m_conteneur->x_refpos;
                                (*it_bloc)->m_x2=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur;
                                (*it_bloc)->m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur;
                                (*it_bloc)->m_y3=(*it_bloc)->m_conteneur->y_refpos;
                        }


                        else if((*it_bloc)->basepos=="tr")
                        {
                                (*it_bloc)->m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur;         /*x1*/
                                (*it_bloc)->m_x2=(*it_bloc)->m_conteneur->x_refpos;         /*x2*/           /*x4*/
                                (*it_bloc)->m_y1=(*it_bloc)->m_conteneur->y_refpos;         /*y1*/
                                (*it_bloc)->m_y3=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur;         /*y3*/         /*y4*/

                        }
                        else if ((*it_bloc)->basepos=="mr")
                        {
                                (*it_bloc)->m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur;         /*x1*/
                                (*it_bloc)->m_x2=(*it_bloc)->m_conteneur->x_refpos;         /*x2*/
                                (*it_bloc)->m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur/(double)2;         /*y1*/
                                (*it_bloc)->m_y3=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur/(double)2;         /*y3*/

                        }
                        else if ((*it_bloc)->basepos=="br")
                        {
                                (*it_bloc)->m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur;
                                (*it_bloc)->m_x2=(*it_bloc)->m_conteneur->x_refpos;
                                (*it_bloc)->m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur;
                                (*it_bloc)->m_y3=(*it_bloc)->m_conteneur->y_refpos;
                        }
                        else if ((*it_bloc)->basepos=="bc")
                        {
                                (*it_bloc)->m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur/(double)2;
                                (*it_bloc)->m_x2=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur/(double)2;
                                (*it_bloc)->m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur;
                                (*it_bloc)->m_y3=(*it_bloc)->m_conteneur->y_refpos;
                        }

                        else if((*it_bloc)->basepos=="mc")
                        {
                                (*it_bloc)->m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur/(double)2;
                                (*it_bloc)->m_x2=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur/(double)2;
                                (*it_bloc)->m_y1=(*it_bloc)->m_conteneur->y_refpos;
                                (*it_bloc)->m_y3=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur;
                        }
                        else if((*it_bloc)->basepos=="tc")
                        {
                                (*it_bloc)->m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur/(double)2;
                                (*it_bloc)->m_x2=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur/(double)2;
                                (*it_bloc)->m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur/(double)2;
                                (*it_bloc)->m_y3=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur/(double)2;

                        }
                        else
                        {
                                std::cout << "Erreur code dans .rom" << std::endl;
                        }


                }
                else // si non on l'oriente ver la droite par defaut avec ces coordonner m_x et m_y
                {
                        //x1,y1,x2,y2,x3,y3,x4,y4,couleur,epaisseur,couleur_epaisseur
                        m_x2=(*it_bloc)->m_x1+(*it_bloc)->m_largeur /*x2*/;
                        m_y3=(*it_bloc)->m_y1+(*it_bloc)->m_hauteur /*y3*/;

                }
                // On envoie les enfant de maniere recursive
                if((*it_bloc)->m_bloc_enfant.size()!=0) // Si il possede des enfant
                {
                        (*it_bloc)->calcul_xy_de_1_a_4();
                }
        }
}
// Calcule les coord de ref et base pose
void Bloc::calcule_xy_ref_base_pos()
{
        // Creation d'une paire entre la position en string et un int pour utiliser le switch
        std::map<std::string,int> pair_pos_int;
        pair_pos_int["tl"] = 1;
        pair_pos_int["tc"] = 2;
        pair_pos_int["tr"] = 3;
        pair_pos_int["ml"] = 4;
        pair_pos_int["mc"] = 5;
        pair_pos_int["mr"] = 6;
        pair_pos_int["bl"] = 7;
        pair_pos_int["bc"] = 8;
        pair_pos_int["br"] = 9;

// On calcule ici les position x,y des points d'attache
        switch(pair_pos_int[refpos])
        {
        case 1:
                x_refpos = m_x1;
                y_refpos = m_y1;
                break;
        case 2:
                x_refpos = m_x1+ (m_largeur/(double)2);
                y_refpos = m_y1;
                break;
        case 3:
                x_refpos = m_x1+m_largeur;
                y_refpos = m_y1;
                break;
        case 4:
                x_refpos = m_x1;
                y_refpos = m_y1+(m_hauteur/(double)2);
                break;
        case 5:
                x_refpos = m_x1+ (m_largeur/(double)2);
                y_refpos = m_y1+(m_hauteur/(double)2);
                break;
        case 6:
                x_refpos = m_x1+ m_largeur;
                y_refpos = m_y1+(m_hauteur/(double)2);
                break;
        case 7:
                x_refpos = m_x1;
                y_refpos = m_y1+m_hauteur;
                break;
        case 8:
                x_refpos = m_x1+ (m_largeur/(double)2);
                y_refpos = m_y1+m_hauteur;
                break;
        case 9:
                x_refpos = m_x1+m_largeur;
                y_refpos = m_y1+m_hauteur;
                break;

        default:
                x_refpos = m_x1;
                y_refpos = m_y1;
                break;


        }
// Basepose(x,y) = m_x;m_y

// de meme pour la position d'attache en tant que fils
/*        switch(pair_pos_int[basepos])
        {
        case 1:
                x_basepos = m_x;
                y_basepos = m_y;
                break;
        case 2:
                x_basepos = m_x+ (m_largeur/(double)2);
                y_basepos = m_y;
                break;
        case 3:
                x_basepos = m_x+m_largeur;
                y_basepos = m_y;
                break;
        case 4:
                x_basepos = m_x;
                y_basepos = m_y+(m_hauteur/(double)2);
                break;
        case 5:
                x_basepos = m_x+ (m_largeur/(double)2);
                y_basepos = m_y+(m_hauteur/(double)2);
                break;
        case 6:
                x_basepos = m_x+ m_largeur;
                y_basepos = y_refpos = m_y+(m_hauteur/(double)2);
                break;
        case 7:
                x_basepos = m_x;
                y_basepos = m_y+m_hauteur;
                break;
        case 8:
                x_basepos = m_x+ (m_largeur/(double)2);
                y_basepos = m_y+m_hauteur;
                break;
        case 9:
                x_basepos = m_x+m_largeur;
                y_basepos = m_y+m_hauteur;
                break;
        default:
                x_basepos = m_x;
                y_basepos = m_y;
                break;


        } */
}
