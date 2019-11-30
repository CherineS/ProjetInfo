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
        virtual ~Bloc();

        virtual void ajouterbloc(double largeur,double hauteur,std::string nom,std::string couleur, std::string refp, std::string basep);
        virtual void commandedeplacement(std::vector<std::string>& mots);
        ///void collisions();

        ///getters
        virtual Bloc* GetConteneur() const;
        virtual double GetX1() const;
        virtual double GetY1() const;
        virtual std::string GetCouleur() const;
        virtual std::string GetNom() const;
        virtual double GetLargeur() const;
        virtual double GetHauteur() const;
        virtual std::vector<Bloc*> GetBlocsEnf() const;
        virtual double GetXRef() const;
        virtual double GetYRef() const;

        ///setters
        virtual void SetConteneur(Bloc* conteneur);
        virtual void SetBlocsEnf(Bloc* &aCopier);
        virtual void SetXRefpos(double valeur);
        virtual void SetYRefpos(double valeur);

        virtual void afficherIds(Svgfile& output, bool racine);
        virtual void afficher(Svgfile& output, bool racine);
        virtual void calcule_xy_ref_base_pos();
        virtual void calcul_xy_de_1_a_4(bool reload);
        virtual Bloc* store();
        virtual void avancer(double valeur);
        virtual void rulers(Svgfile& svgout) const;
        virtual void collisions();

    protected:
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


        friend void lireFichier(Bloc*& racine, std::string& nom_fichier);
};

class BlocMobile : public Bloc
{
    private :
        std::string m_direction;
        double m_vitesse;

    public :
        BlocMobile(double largeur,double hauteur,std::string nom,std::string couleur,std::string rp,std::string bp,
                   std::string direction, double vitesse);
        BlocMobile(double largeur,double hauteur,std::string nom,std::string couleur,std::string direction, double vitesse);
        void avancer(double valeur);
        void rulers(Svgfile& svgout) const;
};

class BlocImmobile : public Bloc
{
    public :
        BlocImmobile(double largeur,double hauteur,std::string nom,std::string couleur,std::string rp,std::string bp);
        BlocImmobile(double largeur,double hauteur,std::string nom,std::string couleur);
        void avancer(double valeur);
};


#endif // BLOC_H_INCLUDED
