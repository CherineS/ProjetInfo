#ifndef BLOC_H_INCLUDED
#define BLOC_H_INCLUDED

class bloc
{
private :
    std::string m_nom;
    std::string m_couleur;
    std::string<bloc*> m_enfants;

public :
    bloc(std::string nom,std::string couleur);
};


#endif // BLOC_H_INCLUDED
