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
    public:
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
        friend void lireFichier(Bloc*& racine,std::string& nom_fichier);

    public:
        Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur);
        /**Bloc(double largeur,double hauteur,std::string nom,std::string couleur,std::string rp,std::string bp);
        **/
        Bloc();
        ~Bloc();
        /**void ajouterbloc(double largeur,double hauteur,std::string nom,std::string couleur, std::string refp, std::string basep);
        **/
        void ajouterbloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur);
        std::string GetNom() const;
        std::string GetCouleur() const;
        double GetX() const;
        double GetY() const;
        double GetLargeur() const;
        double GetHauteur() const;
        Bloc* GetConteneur() const;
        void SetConteneur(Bloc* conteneur);
        std::vector<Bloc*> GetBlocsEnf() const;
        void SetBlocsEnf(Bloc* &aCopier);
        void afficher(Svgfile& output, bool& racine);
        void afficherIds(Svgfile& output, bool racine);
        //void collisions();
        Bloc* store();

};


#endif // BLOC_H_INCLUDED
