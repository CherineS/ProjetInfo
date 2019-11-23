#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void lireFichier()
{
    std::ifstream fichierRom("fichier.txt");

    if(!fichierRom)
    {
        std::cout << "Erreur de lecture du fichier";
        exit(EXIT_FAILURE);
    }
    else
    {
        bool premier=1,type=0;
        int x,y;
        std::string id, color, ligne;
        std::istringstream iss{ligne};
        while(std::getline(fichierRom, ligne))
        {
            fichierRom >> id; ///On lit la première chaîne
            if(id=="*") ///On ajoute dans la liste de vecteurs du bloc precedent
            {
                fichierRom >> id;
                type=1; ///Type 1 = enfant du parent actuel
            }
            fichierRom >> x;
            fichierRom >> y;
            fichierRom >> color;

            if(type==1)
            {
                std::cout << "enfant :" << id << std::endl;
            }
            else{
                std::cout << "suite :" << id << std::endl;
            }

            type=0; ///On revient a l'ajout par defaut : le parent actuel
        }
    }
}
