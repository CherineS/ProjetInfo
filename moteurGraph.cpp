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

void MoteurGraph::detecterColision(Bloc& Racine)
{
std::vector<Bloc*>::iterator it1;
std::vector<Bloc*>::iterator it2;
std::vector<Bloc*>::iterator it2end;
std::vector<Bloc*>::iterator itTemp;
bool enfant = true; // savoir si on doit comparer les enfant de second

for(it1 = Racine.GetBlocsEnf().begin() ; it1 != Racine.GetBlocsEnf().end(); ++it1)
{
    it2 = it1++; // On compare it1 et it2 qui est le rang d'apres
    while(*it2 != nullptr)
    {
        if(*it1 == *it2) // Surcharger l'operateur == pour renvoyer vrais si collisions
        {
            afficherColision(10,10);
        }

        if(enfant)
        {   // si on s'attaque au enfant
            if( ((*it2)->GetBlocsEnf().size()) != 0 ) // Si il existe des enfants
            {
            it2 = (*it2)->GetBlocsEnf().begin();  // On initialise it2
            itTemp = it2;
            it2end = (*it2)->GetBlocsEnf().end();
            enfant = false;
            }
            else // si non on remonte dans la boucle for pour reprendre depuis les premiers enfants.
            {
                *it2 = nullptr;
            }

        }
        else if(!enfant && it2 != it2end) // si on  est en train de les parcours
        {
            it2++;
            if(it2==it2end) // Si on a atteint le dernier enfant
            {
                enfant = true;
                it2 = itTemp; // On remet le bool a true et reéinitialise it2 pour parcourir les enfant de ces enfant si ils exiistent
            }

        }
        else  // si on a fini de les parcourirs
        {
                *it2 = nullptr;
        }

    }
}

}

void MoteurGraph::afficherColision(double x, double y)
{
        std::cout << "Colison en " << x << ";" << y << std::endl;
}
