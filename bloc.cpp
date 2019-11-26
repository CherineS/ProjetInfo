#include "bloc.h"

Bloc::Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur) :
        m_largeur{largeur},m_hauteur{hauteur},m_x{x},m_y{y},m_nom{nom},m_couleur{couleur}, m_conteneur(nullptr){
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

                output.addRect((*it_bloc)->m_x1,(*it_bloc)->m_y1,(*it_bloc)->m_x2,(*it_bloc)->m_y2,(*it_bloc)->m_x3,(*it_bloc)->m_y3,(*it_bloc)->m_x4,(*it_bloc)->m_y4,(*it_bloc)->m_couleur,0.1,"black");

                // On envoie les enfant de maniere recursive
                if((*it_bloc)->m_bloc_enfant.size()!=0) // Si il possede des enfant
                {
                        (*it_bloc)->afficher(output);
                }


        }

}

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
                                m_x1=(*it_bloc)->m_conteneur->x_refpos;         /*x1*/
                                m_x3=(*it_bloc)->m_conteneur->x_refpos;         /*x3*/
                                m_x2=(*it_bloc)->m_conteneur->x_refpos+(*it_bloc)->m_largeur;         /*x2*/
                                m_x4=(*it_bloc)->m_conteneur->x_refpos+(*it_bloc)->m_largeur;         /*x4*/
                                m_y1=(*it_bloc)->m_conteneur->y_refpos;         /*y1*/
                                m_y2=(*it_bloc)->m_conteneur->y_refpos;         /*y2*/
                                m_y3=(*it_bloc)->m_conteneur->y_refpos+(*it_bloc)->m_hauteur;         /*y3*/
                                m_y4=(*it_bloc)->m_conteneur->y_refpos+(*it_bloc)->m_hauteur;         /*y4*/

                        }
                        else if ((*it_bloc)->basepos=="ml")
                        {
                                m_x1=(*it_bloc)->m_conteneur->x_refpos /*x1*/;
                                m_x3=(*it_bloc)->m_conteneur->x_refpos /*x3*/;
                                m_x2=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur /*x2*/;
                                m_x4=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur /*x4*/;
                                m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur/(double)2 /*y1*/;
                                m_y2=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur/(double)2 /*y2*/;
                                m_y3=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur/(double)2 /*y3*/;
                                m_y4=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur/(double)2 /*y4*/;
                        }
                        else if ((*it_bloc)->basepos=="bl")
                        {
                                m_x1=(*it_bloc)->m_conteneur->x_refpos;
                                m_x3=(*it_bloc)->m_conteneur->x_refpos;
                                m_x2=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur;
                                m_x4=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur;
                                m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur;
                                m_y2=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur;
                                m_y3=(*it_bloc)->m_conteneur->y_refpos;
                                m_y4=(*it_bloc)->m_conteneur->y_refpos;

                        }


                        else if((*it_bloc)->basepos=="tr")
                        {
                                m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur;         /*x1*/
                                m_x3=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur;         /*x3*/
                                m_x2=(*it_bloc)->m_conteneur->x_refpos;         /*x2*/
                                m_x4=(*it_bloc)->m_conteneur->x_refpos;           /*x4*/
                                m_y1=(*it_bloc)->m_conteneur->y_refpos;         /*y1*/
                                m_y2=(*it_bloc)->m_conteneur->y_refpos;         /*y2*/
                                m_y3=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur;         /*y3*/
                                m_y4=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur;         /*y4*/

                        }
                        else if ((*it_bloc)->basepos=="mr")
                        {
                                m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur;         /*x1*/
                                m_x3=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur;         /*x3*/
                                m_x2=(*it_bloc)->m_conteneur->x_refpos;         /*x2*/
                                m_x4=(*it_bloc)->m_conteneur->x_refpos;         /*x4*/
                                m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur/(double)2;         /*y1*/
                                m_y2=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur/(double)2;         /*y2*/
                                m_y3=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur/(double)2;         /*y3*/
                                m_y4=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur/(double)2;         /*y4*/

                        }
                        else if ((*it_bloc)->basepos=="br")
                        {
                                m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur;
                                m_x3=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur;
                                m_x2=(*it_bloc)->m_conteneur->x_refpos;
                                m_x4=(*it_bloc)->m_conteneur->x_refpos;
                                m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur;
                                m_y2=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur;
                                m_y3=(*it_bloc)->m_conteneur->y_refpos;
                                m_y4=(*it_bloc)->m_conteneur->y_refpos;
                        }
                        else if ((*it_bloc)->basepos=="bc")
                        {
                                m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur/(double)2;
                                m_x3=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur/(double)2;
                                m_x2=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur/(double)2;
                                m_x4=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur/(double)2;
                                m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur;
                                m_y2=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur;
                                m_y3=(*it_bloc)->m_conteneur->y_refpos;
                                m_y4=(*it_bloc)->m_conteneur->y_refpos;
                        }

                        else if((*it_bloc)->basepos=="mc")
                        {
                                m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur/(double)2;
                                m_x3=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur/(double)2;
                                m_x2=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur/(double)2;
                                m_x4=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur/(double)2;
                                m_y1=(*it_bloc)->m_conteneur->y_refpos;
                                m_y2=(*it_bloc)->m_conteneur->y_refpos;
                                m_y3=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur;
                                m_y4=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur;
                        }
                        else if((*it_bloc)->basepos=="tc")
                        {
                                m_x1=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur/(double)2;
                                m_x3=(*it_bloc)->m_conteneur->x_refpos - (*it_bloc)->m_largeur/(double)2;
                                m_x2=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur/(double)2;
                                m_x4=(*it_bloc)->m_conteneur->x_refpos + (*it_bloc)->m_largeur/(double)2;
                                m_y1=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur/(double)2;
                                m_y2=(*it_bloc)->m_conteneur->y_refpos - (*it_bloc)->m_hauteur/(double)2;
                                m_y3=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur/(double)2;
                                m_y4=(*it_bloc)->m_conteneur->y_refpos + (*it_bloc)->m_hauteur/(double)2;

                        }
                        else
                        {
                                std::cout << "Erreur code dans .rom" << std::endl;
                        }


                }
                else // si non on l'oriente ver la droite par defaut avec ces coordonner m_x et m_y
                {
                        //x1,y1,x2,y2,x3,y3,x4,y4,couleur,epaisseur,couleur_epaisseur
                        m_x1=(*it_bloc)->m_x /*x1*/;
                        m_y1=(*it_bloc)->m_y /*y1*/;
                        m_x2=(*it_bloc)->m_x+(*it_bloc)->m_largeur /*x2*/;
                        m_y2=(*it_bloc)->m_y /*y2*/;
                        m_x3=(*it_bloc)->m_x /*x3*/;
                        m_y3=(*it_bloc)->m_y+(*it_bloc)->m_hauteur /*y3*/;
                        m_x4=(*it_bloc)->m_x+(*it_bloc)->m_largeur /*x4*/;
                        m_y4=(*it_bloc)->m_y+(*it_bloc)->m_hauteur /*y4*/;


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
                x_refpos = m_x;
                y_refpos = m_y;
                break;
        case 2:
                x_refpos = m_x+ (m_largeur/(double)2);
                y_refpos = m_y;
                break;
        case 3:
                x_refpos = m_x+m_largeur;
                y_refpos = m_y;
                break;
        case 4:
                x_refpos = m_x;
                y_refpos = m_y+(m_hauteur/(double)2);
                break;
        case 5:
                x_refpos = m_x+ (m_largeur/(double)2);
                y_refpos = m_y+(m_hauteur/(double)2);
                break;
        case 6:
                x_refpos = m_x+ m_largeur;
                y_refpos = y_refpos = m_y+(m_hauteur/(double)2);
                break;
        case 7:
                x_refpos = m_x;
                y_refpos = m_y+m_hauteur;
                break;
        case 8:
                x_refpos = m_x+ (m_largeur/(double)2);
                y_refpos = m_y+m_hauteur;
                break;
        case 9:
                x_refpos = m_x+m_largeur;
                y_refpos = m_y+m_hauteur;
                break;

        default:
                x_refpos = m_x;
                y_refpos = m_y;
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
