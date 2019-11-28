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

Bloc* Bloc::GetConteneur()
{
        return m_conteneur;
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
                output.addDisk((*it_bloc)->m_x /*x*/, (*it_bloc)->m_y /*y*/, (*it_bloc)->m_largeur /*rayon*/,(*it_bloc)->m_couleur);

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
                output.addCircle((*it_bloc)->m_x /*x*/, (*it_bloc)->m_y /*y*/, (*it_bloc)->m_largeur /*rayon*/,2,"yellow");
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

void Bloc::commandedeplacement(Svgfile& output, bool racine,std::vector<std::string>& mots)
{
    afficher(output,racine);
    racine=0;
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
            if(a!=-1)
            {
                for (i=0;i<taille;++i)
                {
                b=mots[i].find("move");
                d=mots[i].find("rotate");
                if (b!=-1||d!=-1) break;
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
                            if(b!=-1)
                            {
                                ///programme deplacement selon la position actuel avec 'somme' move
                                std::cout<<mots[i+1][0]<<somme<<" move"<<std::endl;
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
                                std::cout<<somme<<" move"<<std::endl;
                            }
                            if(d!=-1)
                            {
                                ///programme deplacement selon la position actuel avec 'somme' rotate
                                std::cout<<somme<<" rotate"<<std::endl;
                            }
                        }
                        }
                    }
                    else
                        {
                            std::cout<<"nombre non valide"<<std::endl;
                        }
                  }
                }
            }
        }
}














