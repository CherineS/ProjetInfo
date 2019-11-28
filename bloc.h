#ifndef BLOC_H_INCLUDED
#define BLOC_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "svgfile.h"
#include <map>

class Bloc
{

    public:
        Bloc(double largeur,double hauteur,double x,double y,std::string nom,std::string couleur);
        Bloc(double largeur,double hauteur,std::string nom,std::string couleur,std::string rp,std::string bp);
        Bloc(double largeur,double hauteur,std::string nom,std::string couleur);
        Bloc();
        ~Bloc();

        void ajouterbloc();
        void ajouterbloc(double largeur,double hauteur,std::string nom,std::string couleur, std::string refp, std::string basep);;


        ///getters
        Bloc* GetConteneur() const;
        double GetX1() const;
        double GetY1() const;
        std::string GetCouleur() const;
        std::string GetNom() const;
        double GetLargeur() const;
        double GetHauteur() const;
        std::vector<Bloc*> GetBlocsEnf() const;

        ///setters
        void SetConteneur(Bloc* conteneur);
        void SetBlocsEnf(Bloc* &aCopier);

        void afficherIds(Svgfile& output, bool racine);
        void afficher(Svgfile& output, bool racine);
        void calcule_xy_ref_base_pos();
        void calcul_xy_de_1_a_4();
        Bloc* store();

    private:
        double m_largeur;
        double m_hauteur;
        double m_x1; // x1 = x3
        double m_x2; // x2 = x4
        double m_y1; // y1 = y2
        double m_y3; // y3 = y4

        std::string m_nom;
        std::string m_couleur;
        std::vector<Bloc*> m_bloc_enfant;
        Bloc* m_conteneur;

        std::string refpos; // Point d'encrage du bloc parrent
        std::string basepos; // Point d'encrage du bloc enfant
        std::string endpos; // Point du bloc parrent maximal d'encrage lors de la translation

        //Positon d'encrage
        double x_refpos;
        double y_refpos;


        friend Bloc* ajouterFichier(double& larg, double& haut, double& x, double& y, std::string& id, std::string& color);
        friend void lireFichier(Bloc*& racine, std::string& nom_fichier);
        ///friend Bloc* ajouterFichier(double& larg, double& haut, std::string& id, std::string& color, std::string& refp, std::string& basep);

        ///void collisions();
};


#endif // BLOC_H_INCLUDED
