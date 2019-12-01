#include "moteurGraph.h"

MoteurGraph::MoteurGraph(Bloc& racine) : m_racine(racine)
{

}

MoteurGraph::~MoteurGraph(){}


void MoteurGraph::calculerPoid(Bloc& racine, bool bracine)

{
std::vector<Bloc*>::iterator it;

if(bracine==1) // Si c'est la racine
    racine.SetPoid(racine.GetLargeur()*racine.GetHauteur());

    for(it=racine.GetBlocsEnf().begin(); it!=racine.GetBlocsEnf().end(); ++it)
    {
        (*it)->SetPoid((*it)->GetLargeur()*(*it)->GetHauteur());

        if( ((*it)->GetBlocsEnf().size()) != 0)
        {
                MoteurGraph::calculerPoid(**it,0);
        }
    }
}

void MoteurGraph::detecterColision(Bloc& racine)
{
std::vector<Bloc*>::iterator it1;
std::vector<Bloc*>::iterator it2;

for(it1=racine.GetBlocsEnf().begin(); it1!=racine.GetBlocsEnf().end();++it1)
{
    if((*it1)->GetBlocsEnf().size() != 0)
    {


    for(it2=(*it1)->GetBlocsEnf().begin(); it2!=(*it1)->GetBlocsEnf().end(); ++it2 )
    {
                ///Si le bloc se deplace en x
                if((*it2)->GetX1()<(*it1)->GetX1() && (*it1)->GetX1()<(*it2)->GetX1()+(*it2)->GetLargeur())
                {
                    std::cout << "B"<< std::endl;
                                        MoteurGraph::afficherColision(20,10);
                    ///Si son aire est plus importante, elle pousse, sinon elle ne bouge pas
                    if((*it1)->GetPoid() >(*it2)->GetPoid())
                    {
                        (*it2)->SetXRefpos((*it1)->GetX1()+(*it2)->GetLargeur()-(*it1)->GetX1());
                        std::cout << "B"<< std::endl;
                    }

                }
                else if((*it2)->GetX1()+(*it2)->GetLargeur() > (*it1)->GetX1()+(*it1)->GetLargeur() && (*it1)->GetX1()+(*it1)->GetLargeur() >(*it2)->GetX1())
                {
                    std::cout << "B"<< std::endl;
                    if((*it1)->GetPoid() >(*it1)->GetPoid())
                    {
                        std::cout << "B"<< std::endl;
                         (*it2)->SetXRefpos((*it2)->GetX1()+(*it2)->GetLargeur()-(*it1)->GetX1()+(*it1)->GetLargeur());
                    }

                }

                ///Si le bloc se deplace en y
                if((*it2)->GetY1() < (*it1)->GetY1() && (*it1)->GetY1() < (*it2)->GetY1()+(*it2)->GetHauteur())
                {
                    if((*it1)->GetPoid() >(*it2)->GetPoid())
                        (*it2)->SetYRefpos((*it1)->GetY1()-(*it2)->GetY1()+(*it2)->GetHauteur());
                }
                else if((*it2)->GetY1()+(*it2)->GetHauteur() > (*it2)->GetY1()+(*it1)->GetHauteur() && (*it1)->GetY1()+(*it1)->GetHauteur() > (*it2)->GetY1())
                {
                    if((*it1)->GetPoid() > (*it2)->GetPoid())
                        (*it2)->SetYRefpos((*it2)->GetY1()+(*it2)->GetHauteur()-(*it2)->GetY1()+(*it1)->GetHauteur());
                }
        }
    }
}
}

void MoteurGraph::afficherColision(double x, double y)
{
        std::cout << "Colison en " << x << ";" << y << std::endl;
}
