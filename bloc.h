#ifndef BLOC_H_INCLUDED
#define BLOC_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "svgfile.h"

class Bloc
{
    private:
        double m_largeur;
        double m_hauteur;
        double m_x;
        double m_y;
        std::string m_nom;
        std::string m_couleur;
        std::vector<Bloc*> m_bloc_enfant;
/**        std::string refpos,basepos;      **/
        Bloc* m_conteneur;

        friend Bloc* ajouterFichier(double& larg, double& haut, double& x, double& y, std::string& id, std::string& color);
        /**friend Bloc* ajouterFichier(double& larg, double& haut, std::string& id, std::string& color, std::string& refp, std::string& basep);
        **/
        friend void lireFichier(Bloc*& racine);

    public:
        Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur);
        /**Bloc(double largeur,double hauteur,std::string nom,std::string couleur,std::string rp,std::string bp);
        **/
        Bloc();
        ~Bloc();
        /**void ajouterbloc(double largeur,double hauteur,std::string nom,std::string couleur, std::string refp, std::string basep);
        **/
        void ajouterbloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur);
        Bloc* GetConteneur();
        void afficher(Svgfile& output, bool& racine);
        void afficherIds(Svgfile& output, bool racine);
        void commandedeplacement(Svgfile& output, bool racine,std::vector<std::string>& mots);

};


#endif // BLOC_H_INCLUDED
