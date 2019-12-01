#include <iostream>
#include "bloc.h"
#include "coord.h"
#include "header.h"
#include "svgfile.h"
#include"moteurGraph.h"

void menu()
{
    Bloc*racine, *copie;

    std::string menu="debut";
    std::string nom_fichier="debut";
    bool ids=0, rulers=0;

    std::cout<<"        MENU"<<std::endl
             <<"saisir :"<<std::endl
             <<"'exit'                        -pour quitter l'application"<<std::endl
             <<"'load' 'nom du fichier.rom'   -pour charger un fichier"<<std::endl
             <<"'reload'                      -pour charger le fichier precedemment ouvert"<<std::endl
             <<"'store'                       -pour enregistrer une copie de l'etat actuel de la scene"<<std::endl
             <<"'restore'                     -pour retourner a la copie precedemment enregistre"<<std::endl
             <<"'ids'                         -afficher/cacher les ids"<<std::endl
             <<"'rulers'                      -afficher/cacher les axes"<<std::endl;


    do
    {
        std::cout<<std::endl<<">";
        getline(std::cin,menu);

        if(menu=="load")
        {
            std::cout<<"entrer le nom du ficher (nom_fichier.rom)"<<std::endl;
            getline(std::cin,nom_fichier);
            lireFichier(racine,nom_fichier);
            racine->calcul_xy_de_1_a_4(1);
            //MoteurGraph::calculerPoid(*racine,1);
            std::cout<<nom_fichier<<" loaded"<<std::endl;
        }
        else if(menu=="reload")
        {
            if(nom_fichier=="debut")
                std::cout << "Pas de fichier" << std::endl;
            else
            {
                lireFichier(racine,nom_fichier);
                racine->calcul_xy_de_1_a_4(1);
                std::cout<<nom_fichier<<" reloaded"<<std::endl;
            }
        }
        else if(menu=="store")
        {
            if(nom_fichier=="debut")
                std::cout << "Pas de fichier" << std::endl;
            else
            {
                copie=racine->store();
                std::cout<<"copie enregistre"<<std::endl;
            }
        }
        else if(menu=="restore")
        {
            if(nom_fichier=="debut")
                std::cout << "Pas de fichier" << std::endl;
            else
            {
                racine=copie;
                std::cout<<"restauration du fichier"<<std::endl;
            }
        }
        else if(menu=="ids")
        {
            if(nom_fichier=="debut")
                std::cout << "Pas de fichier" << std::endl;
            else
            {
                if(ids==1)
                {
                    ids=0;
                    std::cout<<"masquage des ids"<<std::endl;
                }
                else
                {
                    ids=1;
                    std::cout<<"affichage des ids"<<std::endl;
                }
            }
        }
        else if(menu=="rulers")
        {
            if(nom_fichier=="debut")
                std::cout << "Pas de fichier" << std::endl;
            else
            {
                if(rulers==1)
                {
                    rulers=0;
                    std::cout<<"masquage des axes"<<std::endl;
                }
                else
                {
                    rulers=1;
                    std::cout<<"affichage des axes"<<std::endl;
                }
            }
        }
        else if(menu[0]=='@')
        {
            std::istringstream ligne(menu);
            std::vector<std::string> mots;
            std::copy(std::istream_iterator<std::string>(ligne), std::istream_iterator<std::string>(), std::back_inserter(mots));   ///s�pare les mots dans un vector

            racine->commandedeplacement(mots);
            //MoteurGraph::detecterColision(*racine);
            racine->collisions();
        }
        else
            std::cout << "Saisie invalide\n";

        ///Fonction permettant de reactualiser la sortie chaque seconde
        if(nom_fichier!="debut")
        {
            Svgfile::s_verbose = false;
            Svgfile svgout;
            racine->calcul_xy_de_1_a_4(0); // Initialise les point d'attache

            if(ids==1)
                racine->afficherIds(svgout,1);
            else if(ids==0)
                racine->afficher(svgout,1);

            if(rulers==1)
                racine->rulers(svgout);
        }

    }
    while(menu!="exit");
}

int main()
{

    menu();

    return 0;
}
