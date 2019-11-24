#ifndef BLOC_H_INCLUDED
#define BLOC_H_INCLUDED
#include<vector>
#include<string>

class Bloc
{
private :
    double m_largeur;
    double m_hauteur;
    double m_x;
    double m_y;
    std::string m_nom;
    std::string m_couleur;
    std::vector<Bloc*> m_bloc_enfant;
    Bloc* m_conteneur;


public :
    Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur);
    Bloc();
    ~Bloc();
    void ajouterbloc();


};


#endif // BLOC_H_INCLUDED
