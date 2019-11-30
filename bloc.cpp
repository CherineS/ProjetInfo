#include "bloc.h"
#include "header.h"

Bloc::Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur) :
    m_largeur{largeur},m_hauteur{hauteur},m_x1{x},m_y1{y},m_nom{nom},m_couleur{couleur}, m_conteneur(nullptr)
{
}

///Refpos basepos
Bloc::Bloc(double largeur,double hauteur,std::string nom,std::string couleur) :
    m_largeur{largeur},m_hauteur{hauteur},m_x1{0},m_y1{0},m_nom{nom},m_couleur{couleur}, m_conteneur(nullptr),
    refpos{"tl"},basepos{"tl"},x_refpos{0},y_refpos{0}
{
}

Bloc::Bloc(double largeur,double hauteur,std::string nom,std::string couleur,std::string rp,std::string bp) :
    m_largeur{largeur},m_hauteur{hauteur},m_x1{0},m_y1{0},m_nom{nom},m_couleur{couleur}, m_conteneur(nullptr),
    refpos{rp},basepos{bp},x_refpos{0},y_refpos{0}
{
}


Bloc::Bloc() : m_largeur{0},m_hauteur{0},m_x1{0},m_y1{0},m_nom{"vide"},m_couleur{"noir"}, m_conteneur(nullptr)
{
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

double Bloc::GetX1() const
{
    return m_x1;
}

double Bloc::GetY1() const
{
    return m_y1;
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

double Bloc::GetXRef() const
{
    return x_refpos;
}

double Bloc::GetYRef() const
{
    return y_refpos;
}

void Bloc::SetBlocsEnf(Bloc* &aCopier)
{
    Bloc *bloc = new Bloc(aCopier->GetLargeur(),aCopier->GetHauteur(),aCopier->GetX1(),aCopier->GetY1(),
                          aCopier->GetNom(),aCopier->GetCouleur());

    m_bloc_enfant.push_back(bloc);
}

void Bloc::SetConteneur(Bloc* conteneur)
{
    m_conteneur=conteneur;
}

void Bloc::SetXRefpos(double valeur)
{
    x_refpos+=valeur;
    for(size_t i=0;i<m_bloc_enfant.size();++i)
        m_bloc_enfant[i]->SetXRefpos(valeur);
}

void Bloc::SetYRefpos(double valeur)
{
    y_refpos+=valeur;
    for(size_t i=0;i<m_bloc_enfant.size();++i)
        m_bloc_enfant[i]->SetYRefpos(valeur);
}

void Bloc::ajouterbloc(double largeur,double hauteur,std::string nom,std::string couleur, std::string refp, std::string basep)
{
    Bloc *bloc = new Bloc(largeur,hauteur,nom,couleur,refp,basep);
    m_bloc_enfant.push_back(bloc);
}

void Bloc::afficher(Svgfile& output, bool racine)
{
    std::vector<Bloc*>::iterator it_bloc;

    ///Afficher la racine
    if(racine==1)
    {
        output.addRect(m_x1 /*x1*/, m_y1 /*y1*/, m_x1+m_largeur /*x2*/, m_y1 /*y2*/, m_x1 /*x3*/,m_y1+m_hauteur /*y3*/,
                       m_x1+m_largeur /*x4*/, m_y1+m_hauteur /*y4*/, m_couleur,0.15,"black");
        racine=0;
    }


    for(it_bloc = m_bloc_enfant.begin(); it_bloc!=m_bloc_enfant.end(); ++it_bloc)
    {
        if((*it_bloc)->m_hauteur==0) ///On trace un cercle
            output.addDisk(((*it_bloc)->m_x1+(*it_bloc)->m_largeur/2) /*x*/, ((*it_bloc)->m_y1+(*it_bloc)->m_largeur/2-(*it_bloc)->m_largeur) /*y*/, (*it_bloc)->m_largeur/2 /*rayon*/,(*it_bloc)->m_couleur);
        else ///On trace un rectangle
            output.addRect((*it_bloc)->m_x1 /*x1*/,(*it_bloc)->m_y1 /*y1*/,(*it_bloc)->m_x2 /*x2*/,(*it_bloc)->m_y1 /*y2*/,(*it_bloc)->m_x1 /*x3*/,(*it_bloc)->m_y3 /*y3*/,(*it_bloc)->m_x2 /*4*/,(*it_bloc)->m_y3 /*y4*/,(*it_bloc)->m_couleur,0.1,"black");

        // On envoie les enfant de maniere recursive
        if((*it_bloc)->m_bloc_enfant.size()!=0) // Si il possede des enfant
        {
            (*it_bloc)->afficher(output,0);
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
            output.addCircle((*it_bloc)->m_x1+(*it_bloc)->m_largeur/2 /*x*/, (*it_bloc)->m_y1-(*it_bloc)->m_largeur+(*it_bloc)->m_largeur/2 /*y*/, (*it_bloc)->m_largeur/2 /*rayon*/,2,"yellow");
        else ///Contour d'un rectangle
        {
            output.addRect((*it_bloc)->m_x1,(*it_bloc)->m_y1,(*it_bloc)->m_largeur+(*it_bloc)->m_x1,(*it_bloc)->m_y1,
                           (*it_bloc)->m_x1,(*it_bloc)->m_hauteur+(*it_bloc)->m_y1,(*it_bloc)->m_largeur+(*it_bloc)->m_x1
                           ,(*it_bloc)->m_hauteur+(*it_bloc)->m_y1,2,"yellow");
        }

        int decalerx=(*it_bloc)->m_nom.size()*3.5; ///Pour centrer le texte

        output.addText((*it_bloc)->m_x1+((*it_bloc)->m_largeur/2)-decalerx-1,(*it_bloc)->m_y1+((*it_bloc)->m_hauteur/2)+3-1
                       ,(*it_bloc)->m_nom,"yellow");
        output.addText((*it_bloc)->m_x1+((*it_bloc)->m_largeur/2)-decalerx+1,(*it_bloc)->m_y1+((*it_bloc)->m_hauteur/2)+1+3
                       ,(*it_bloc)->m_nom,"yellow");
        output.addText((*it_bloc)->m_x1+((*it_bloc)->m_largeur/2)-decalerx-1,(*it_bloc)->m_y1+((*it_bloc)->m_hauteur/2)+1+3
                       ,(*it_bloc)->m_nom,"yellow");
        output.addText((*it_bloc)->m_x1+((*it_bloc)->m_largeur/2)-decalerx+1,(*it_bloc)->m_y1+((*it_bloc)->m_hauteur/2)-1+3
                       ,(*it_bloc)->m_nom,"yellow");
        output.addText((*it_bloc)->m_x1+((*it_bloc)->m_largeur/2)-decalerx,(*it_bloc)->m_y1+((*it_bloc)->m_hauteur/2)+3
                       ,(*it_bloc)->m_nom,"black");

        if((*it_bloc)->m_bloc_enfant.size()!=0)
            (*it_bloc)->afficherIds(output,racine);
    }
}


///Deplacement
void Bloc::avancer(double valeur)
{
    x_refpos+=valeur;
    y_refpos+=valeur;

    for(size_t i=0;i<m_bloc_enfant.size();++i)
        m_bloc_enfant[i]->avancer(valeur);
    std::cout<<valeur<<" move"<<std::endl;
}


void Bloc::commandedeplacement(std::vector<std::string>& mots)
{
    int a=-1;
    int b=-1;
    int d=-1;
    int i=0;
    int somme=0;
    int c1=0,c2=0,c3=0;

    int taille=mots.size();

    std::vector<Bloc*>::iterator it_bloc;

    for(it_bloc = m_bloc_enfant.begin(); it_bloc!=m_bloc_enfant.end(); ++it_bloc)
    {
        a=mots[0].find((*it_bloc)->m_nom);
        (*it_bloc)->commandedeplacement(mots);
        if(a!=-1)
        {
            for (i=0; i<taille; ++i)
            {
                b=mots[i].find("move");
                d=mots[i].find("rotate");
                if (b!=-1||d!=-1)
                    break;
            }
            if(b!=-1||d!=-1)
            {
                if(taille>i+1)
                {
                    mots[i+1][0];

                    if((mots[i+1][0]=='+')||(mots[i+1][0]=='-'))
                    {

                        if((mots[i+1].size()<5)||(mots[i+1][3]==' '))
                        {
                            c1=mots[i+1][1]-48;
                            c2=mots[i+1][2]-48;
                            c3=mots[i+1][3]-48;

                            if(mots[i+1].size()==2)
                            {
                                somme=c1;

                            }
                            else if(mots[i+1].size()==3)
                            {
                                somme=10*c1+c2;

                            }
                            else if(mots[i+1].size()==4)
                            {
                                somme=100*c1+10*c2+c3;
                            }
                            if(somme>=-100&&somme<=100)
                            {
                                if((mots[i+1][0]=='-'))
                                    somme=-1*somme;
                                if(b!=-1)
                                {
                                    ///programme deplacement selon la position actuel avec 'somme' move
                                    (*it_bloc)->avancer(somme);
                                }
                                if(d!=-1)
                                {
                                    ///programme deplacement selon la position actuel avec 'somme' rotate
                                    std::cout<<mots[i+1][0]<<somme<<" rotate"<<std::endl;
                                }
                            }
                        }
                    }
                    else if(mots[i+1][0]>0)
                    {
                        if((mots[i+1].size()<4)||(mots[i+1][3]==' '))
                        {
                            c1=mots[i+1][0]-48;
                            c2=mots[i+1][1]-48;
                            c3=mots[i+1][2]-48;

                            if(mots[i+1].size()==1)
                            {
                                somme=c1;

                            }
                            else if(mots[i+1].size()==2)
                            {
                                somme=10*c1+c2;

                            }
                            else if(mots[i+1].size()==3)
                            {
                                somme=100*c1+10*c2+c3;

                            }
                            if(somme>=0&&somme<=100)
                            {
                                if(b!=-1)
                                {
                                    ///programme deplacement selon la position actuel avec 'somme' move
                                    (*it_bloc)->avancer(somme);
                                }
                                if(d!=-1)
                                {
                                    ///programme deplacement selon la position actuel avec 'somme' rotate
                                    std::cout<<somme<<" rotate"<<std::endl;
                                }
                            }
                        }
                    }

                }
            }
        }

    }
}


///Collisions
void Bloc::collisions()
{
    for(size_t i=0; i<m_bloc_enfant.size();++i)
    {
        for(size_t j=0; j<m_bloc_enfant.size();++j)
        {
            ///On ne considere pas les collisions avec lui meme et ses enfants
            if(i!=j)
            {
                ///Si le bloc se deplace en x
                if(m_bloc_enfant[j]->GetX1()<m_bloc_enfant[i]->GetX1() && m_bloc_enfant[i]->GetX1()<m_bloc_enfant[j]->GetX1()+m_bloc_enfant[j]->GetLargeur())
                {
                    ///Si son aire est plus importante, elle pousse, sinon elle ne bouge pas
                    if((m_bloc_enfant[i]->GetLargeur()*m_bloc_enfant[i]->GetHauteur())>(m_bloc_enfant[j]->GetLargeur()*m_bloc_enfant[j]->GetHauteur()))
                        m_bloc_enfant[j]->SetXRefpos(m_bloc_enfant[j]->GetX1()+m_bloc_enfant[j]->GetLargeur()-m_bloc_enfant[i]->GetX1());
                }
                else if(m_bloc_enfant[j]->GetX1()+m_bloc_enfant[j]->GetLargeur() > m_bloc_enfant[i]->GetX1()+m_bloc_enfant[i]->GetLargeur() && m_bloc_enfant[i]->GetX1()+m_bloc_enfant[i]->GetLargeur() > m_bloc_enfant[i]->GetX1())
                {
                    if((m_bloc_enfant[i]->GetLargeur()*m_bloc_enfant[i]->GetHauteur())>(m_bloc_enfant[j]->GetLargeur()*m_bloc_enfant[j]->GetHauteur()))
                        m_bloc_enfant[j]->SetXRefpos(m_bloc_enfant[j]->GetX1()+m_bloc_enfant[j]->GetLargeur()-m_bloc_enfant[i]->GetX1()+m_bloc_enfant[i]->GetLargeur());
                }

                ///Si le bloc se deplace en y
                if(m_bloc_enfant[j]->GetY1() < m_bloc_enfant[i]->GetY1() && m_bloc_enfant[i]->GetY1() < m_bloc_enfant[j]->GetY1()+m_bloc_enfant[j]->GetHauteur())
                {
                    if((m_bloc_enfant[i]->GetLargeur()*m_bloc_enfant[i]->GetHauteur())>(m_bloc_enfant[j]->GetLargeur()*m_bloc_enfant[j]->GetHauteur()))
                        m_bloc_enfant[j]->SetYRefpos(m_bloc_enfant[i]->GetY1()-m_bloc_enfant[j]->GetY1()+m_bloc_enfant[j]->GetHauteur());
                }
                else if(m_bloc_enfant[j]->GetY1()+m_bloc_enfant[j]->GetHauteur() > m_bloc_enfant[j]->GetY1()+m_bloc_enfant[i]->GetHauteur() && m_bloc_enfant[i]->GetY1()+m_bloc_enfant[i]->GetHauteur() > m_bloc_enfant[j]->GetY1())
                {
                    if((m_bloc_enfant[i]->GetLargeur()*m_bloc_enfant[i]->GetHauteur())>(m_bloc_enfant[j]->GetLargeur()*m_bloc_enfant[j]->GetHauteur()))
                        m_bloc_enfant[j]->SetYRefpos(m_bloc_enfant[j]->GetY1()+m_bloc_enfant[j]->GetHauteur()-m_bloc_enfant[j]->GetY1()+m_bloc_enfant[i]->GetHauteur());
                }
            }

        }
    }
}


void Bloc::calcul_xy_de_1_a_4(bool reload)
{
    std::vector<Bloc*>::iterator it_bloc;

    for(it_bloc = m_bloc_enfant.begin(); it_bloc!=m_bloc_enfant.end(); ++it_bloc)
    {

        if((*it_bloc)->m_conteneur != nullptr) // Si il a un parent on regarde sa position d'encrage pour orienter le bloc ver la droite ou la gauche
        {
            // On base la position sur refpos du parent

            if(reload==1)
                (*it_bloc)->calcule_xy_ref_base_pos();

            //On orriente le rect ver gauche
            if((*it_bloc)->basepos=="tl")
            {
                (*it_bloc)->m_x1=(*it_bloc)->x_refpos;         /*x1*/
                (*it_bloc)->m_x2=(*it_bloc)->x_refpos+(*it_bloc)->m_largeur;
                (*it_bloc)->m_y1=(*it_bloc)->y_refpos;         /*y1*/
                (*it_bloc)->m_y3=(*it_bloc)->y_refpos+(*it_bloc)->m_hauteur;
            }
            else if ((*it_bloc)->basepos=="ml")
            {

                (*it_bloc)->m_x1=(*it_bloc)->x_refpos /*x1*/;
                (*it_bloc)->m_x2=(*it_bloc)->x_refpos + (*it_bloc)->m_largeur /*x2*/;
                (*it_bloc)->m_y1=(*it_bloc)->y_refpos - (*it_bloc)->m_hauteur/(double)2 /*y1*/;
                (*it_bloc)->m_y3=(*it_bloc)->y_refpos + (*it_bloc)->m_hauteur/(double)2 /*y3*/;
            }
            else if ((*it_bloc)->basepos=="bl")
            {
                (*it_bloc)->m_x1=(*it_bloc)->x_refpos;
                (*it_bloc)->m_x2=(*it_bloc)->x_refpos + (*it_bloc)->m_largeur;
                (*it_bloc)->m_y1=(*it_bloc)->y_refpos - (*it_bloc)->m_hauteur;
                (*it_bloc)->m_y3=(*it_bloc)->y_refpos;
            }


            else if((*it_bloc)->basepos=="tr")
            {
                (*it_bloc)->m_x1=(*it_bloc)->x_refpos - (*it_bloc)->m_largeur;         /*x1*/
                (*it_bloc)->m_x2=(*it_bloc)->x_refpos;         /*x2*/           /*x4*/
                (*it_bloc)->m_y1=(*it_bloc)->y_refpos;         /*y1*/
                (*it_bloc)->m_y3=(*it_bloc)->y_refpos + (*it_bloc)->m_hauteur;         /*y3*/         /*y4*/

            }
            else if ((*it_bloc)->basepos=="mr")
            {
                (*it_bloc)->m_x1=(*it_bloc)->x_refpos - (*it_bloc)->m_largeur;         /*x1*/
                (*it_bloc)->m_x2=(*it_bloc)->x_refpos;         /*x2*/
                (*it_bloc)->m_y1=(*it_bloc)->y_refpos - (*it_bloc)->m_hauteur/(double)2;         /*y1*/
                (*it_bloc)->m_y3=(*it_bloc)->y_refpos + (*it_bloc)->m_hauteur/(double)2;         /*y3*/

            }
            else if ((*it_bloc)->basepos=="br")
            {
                (*it_bloc)->m_x1=(*it_bloc)->x_refpos - (*it_bloc)->m_largeur;
                (*it_bloc)->m_x2=(*it_bloc)->x_refpos;
                (*it_bloc)->m_y1=(*it_bloc)->y_refpos - (*it_bloc)->m_hauteur;
                (*it_bloc)->m_y3=(*it_bloc)->y_refpos;
            }
            else if ((*it_bloc)->basepos=="bc")
            {
                (*it_bloc)->m_x1=(*it_bloc)->x_refpos - (*it_bloc)->m_largeur/(double)2;
                (*it_bloc)->m_x2=(*it_bloc)->x_refpos + (*it_bloc)->m_largeur/(double)2;
                (*it_bloc)->m_y1=(*it_bloc)->y_refpos - (*it_bloc)->m_hauteur;
                (*it_bloc)->m_y3=(*it_bloc)->y_refpos;
            }

            else if((*it_bloc)->basepos=="mc")
            {
                (*it_bloc)->m_x1=(*it_bloc)->x_refpos - (*it_bloc)->m_largeur/(double)2;
                (*it_bloc)->m_x2=(*it_bloc)->x_refpos + (*it_bloc)->m_largeur/(double)2;
                (*it_bloc)->m_y1=(*it_bloc)->y_refpos;
                (*it_bloc)->m_y3=(*it_bloc)->y_refpos + (*it_bloc)->m_hauteur;
            }
            else if((*it_bloc)->basepos=="tc")
            {
                (*it_bloc)->m_x1=(*it_bloc)->x_refpos - (*it_bloc)->m_largeur/(double)2;
                (*it_bloc)->m_x2=(*it_bloc)->x_refpos + (*it_bloc)->m_largeur/(double)2;
                (*it_bloc)->m_y1=(*it_bloc)->y_refpos - (*it_bloc)->m_hauteur/(double)2;
                (*it_bloc)->m_y3=(*it_bloc)->y_refpos + (*it_bloc)->m_hauteur/(double)2;

            }
            else
            {
                std::cout << "Erreur code dans .rom" << std::endl;
            }


        }
        else // si non on l'oriente vers la droite par defaut avec ces coordonner m_x et m_y
        {
            //x1,y1,x2,y2,x3,y3,x4,y4,couleur,epaisseur,couleur_epaisseur
            m_x2=(*it_bloc)->m_x1+(*it_bloc)->m_largeur /*x2*/;
            m_y3=(*it_bloc)->m_y1+(*it_bloc)->m_hauteur /*y3*/;

        }
        // On envoie les enfant de maniere recursive
        if((*it_bloc)->m_bloc_enfant.size()!=0) // Si il possede des enfant
        {
            (*it_bloc)->calcul_xy_de_1_a_4(reload);
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
        x_refpos = m_conteneur->m_x1;
        y_refpos = m_conteneur->m_y1;
        break;
    case 2:
        x_refpos = m_conteneur->m_x1+ (m_conteneur->m_largeur/(double)2);
        y_refpos = m_conteneur->m_y1;
        break;
    case 3:
        x_refpos = m_conteneur->m_x1+m_conteneur->m_largeur;
        y_refpos = m_conteneur->m_y1;
        break;
    case 4:
        x_refpos = m_conteneur->m_x1;
        y_refpos = m_conteneur->m_y1+(m_conteneur->m_hauteur/(double)2);
        break;
    case 5:
        x_refpos = m_conteneur->m_x1+ (m_conteneur->m_largeur/(double)2);
        y_refpos = m_conteneur->m_y1+(m_conteneur->m_hauteur/(double)2);
        break;
    case 6:
        x_refpos = m_conteneur->m_x1+ m_conteneur->m_largeur;
        y_refpos = m_conteneur->m_y1+(m_conteneur->m_hauteur/(double)2);
        break;
    case 7:
        x_refpos = m_conteneur->m_x1;
        y_refpos = m_conteneur->m_y1+m_conteneur->m_hauteur;
        break;
    case 8:
        x_refpos = m_conteneur->m_x1+ (m_conteneur->m_largeur/(double)2);
        y_refpos = m_conteneur->m_y1+m_conteneur->m_hauteur;
        break;
    case 9:
        x_refpos = m_conteneur->m_x1+m_conteneur->m_largeur;
        y_refpos = m_conteneur->m_y1+m_conteneur->m_hauteur;
        break;

    default:
        x_refpos = m_conteneur->m_x1;
        y_refpos = m_conteneur->m_y1;
        break;


    }
}



///Bloc mobile
BlocMobile::BlocMobile(double largeur,double hauteur,std::string nom,std::string couleur,std::string rp,std::string bp,
                       std::string direction, double vitesse)
    : Bloc(largeur,hauteur,nom,couleur,rp,bp), m_direction{direction}, m_vitesse{vitesse}
{ }

BlocMobile::BlocMobile(double largeur,double hauteur,std::string nom,std::string couleur,std::string direction, double vitesse)
    : Bloc(largeur,hauteur,nom,couleur), m_direction{direction}, m_vitesse{vitesse}
{ }

void BlocMobile::avancer(double valeur)
{
    double j=0;

    if(valeur>0) ///Si avance
    {
        while(j<valeur)
        {
            if(m_direction=="h")
            {
                x_refpos+=m_vitesse;
                for(size_t i=0;i<m_bloc_enfant.size();++i)
                    m_bloc_enfant[i]->SetXRefpos(m_vitesse);

            }
            else if(m_direction=="v")
            {
                y_refpos+=m_vitesse;
                for(size_t i=0;i<m_bloc_enfant.size();++i)
                    m_bloc_enfant[i]->SetYRefpos(m_vitesse);
            }
            j+=m_vitesse;

            Bloc* racine=m_conteneur;
            while(racine->GetConteneur()!=nullptr)
                racine=racine->GetConteneur();

            Sleep(1000);

            Svgfile::s_verbose = false;
            Svgfile svgout;
            racine->calcul_xy_de_1_a_4(0);
            racine->afficher(svgout,1);
        }
    }
    else if(valeur<0) ///Si recule
    {
        while(j>valeur)
        {
            if(m_direction=="h")
            {
                x_refpos-=m_vitesse;
                for(size_t i=0;i<m_bloc_enfant.size();++i)
                    m_bloc_enfant[i]->SetXRefpos(-1*m_vitesse);

            }
            else if(m_direction=="v")
            {
                y_refpos-=m_vitesse;
                for(size_t i=0;i<m_bloc_enfant.size();++i)
                    m_bloc_enfant[i]->SetYRefpos(-1*m_vitesse);
            }

            j-=m_vitesse;

            Bloc* racine=m_conteneur;
            while(racine->GetConteneur()!=nullptr)
                racine=racine->GetConteneur();

            Sleep(1000);

            Svgfile::s_verbose = false;
            Svgfile svgout;
            racine->calcul_xy_de_1_a_4(0);
            racine->afficher(svgout,1);
        }
    }

    std::cout<<valeur<<" move"<<std::endl;
}

void Bloc::rulers(Svgfile& svgout) const
{
    for(size_t i=0;i<m_bloc_enfant.size();++i)
        m_bloc_enfant[i]->rulers(svgout);
}

void BlocMobile::rulers(Svgfile& svgout) const
{
    if(m_direction=="h")
    {
        svgout.addCross((m_x1+m_x2)/2,(m_y1+m_y3)/2,5,"red");
        svgout.addLine(m_conteneur->GetX1(),(m_y1+m_y3)/2,m_conteneur->GetX1()+m_conteneur->GetLargeur(),(m_y1+m_y3)/2,"red");
        svgout.addLine(m_conteneur->GetX1(),(m_y1+m_y3)/2-10,m_conteneur->GetX1(),(m_y1+m_y3)/2+10,"red");
        svgout.addLine(m_conteneur->GetX1()+m_conteneur->GetLargeur()-20,(m_y1+m_y3)/2-10,m_conteneur->GetX1()+m_conteneur->GetLargeur(),(m_y1+m_y3)/2,"red");
        svgout.addLine(m_conteneur->GetX1()+m_conteneur->GetLargeur()-20,(m_y1+m_y3)/2+10,m_conteneur->GetX1()+m_conteneur->GetLargeur(),(m_y1+m_y3)/2,"red");
    }
    else if(m_direction=="v")
    {
        svgout.addCross((m_x1+m_x2)/2,(m_y1+m_y3)/2,5,"red");
        svgout.addLine((m_x1+m_x2)/2,m_conteneur->GetY1(),(m_x1+m_x2)/2,m_conteneur->GetY1()+m_conteneur->GetHauteur(),"red");
        svgout.addLine((m_x1+m_x2)/2-10,m_conteneur->GetY1(),(m_x1+m_x2)/2+10,m_conteneur->GetY1(),"red");
        svgout.addLine((m_x1+m_x2)/2-10,m_conteneur->GetY1()+m_conteneur->GetHauteur()-20,(m_x1+m_x2)/2,m_conteneur->GetY1()+m_conteneur->GetHauteur(),"red");
        svgout.addLine((m_x1+m_x2)/2+10,m_conteneur->GetY1()+m_conteneur->GetHauteur()-20,(m_x1+m_x2)/2,m_conteneur->GetY1()+m_conteneur->GetHauteur(),"red");
    }
    for(size_t i=0;i<m_bloc_enfant.size();++i)
        m_bloc_enfant[i]->rulers(svgout);
}


///Bloc immobile
BlocImmobile::BlocImmobile(double largeur,double hauteur,std::string nom,std::string couleur,std::string rp,std::string bp)
    : Bloc(largeur,hauteur,nom,couleur,rp,bp)
{ }

BlocImmobile::BlocImmobile(double largeur,double hauteur,std::string nom,std::string couleur)
    : Bloc(largeur,hauteur,nom,couleur)
{ }

void BlocImmobile::avancer(double valeur)
{
    std::cout << "Un bloc immobile ne peut pas se deplacer !" << std::endl;
}
