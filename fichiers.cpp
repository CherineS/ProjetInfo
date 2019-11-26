#include "header.h"

// Cree un nouveau bloc avec les caracteristique recuperer dans le fichier
Bloc* ajouterFichier(double& larg, double& haut, double& x, double& y, std::string& id, std::string& color)
{
        Bloc* nouv = new Bloc{larg,haut,x,y,id,color};

        std::cout << nouv->m_largeur << std::endl;
        std::cout << nouv->m_hauteur << std::endl;
        std::cout << nouv->m_x1 << std::endl;
        std::cout << nouv->m_y1 << std::endl;
        std::cout << nouv->m_nom << std::endl;
        std::cout << nouv->m_couleur << std::endl;

        return nouv;
}

void lireFichier(Bloc*& racine)
{
        std::ifstream fichierRom("fichier.txt");
        std::vector<Bloc*> ListeBlocs;

        if(!fichierRom)
        {
                std::cout << "Erreur de lecture du fichier";
                exit(EXIT_FAILURE);
        }
        else
        {
                double larg,haut,x,y; // Parametre pour bloc
                bool type,premier=1; // Type est un bool qui nous dit si nous avont a fair a un enfant, vrais pour type = 1
                std::string id, color, ligne; // Parametre pour bloc + ligne a l'instant t
                std::istringstream iss{ligne};
                Bloc* nouv = nullptr;

                while(fichierRom >> id)
                {


                        if(id!="]") // si on ne ferme pas une relation Enfant
                        {

                                if(id=="[") // Si enfant
                                {
                                        type=1;
                                        std::cout << "\nEnfant\n";

                                        fichierRom >> id;
                                }
                                // On recupere les info
                                fichierRom >> x;
                                fichierRom >> y;
                                fichierRom >> larg;
                                fichierRom >> haut;
                                fichierRom >> color;

                                std::cout << "lu\n";

                                nouv=ajouterFichier(larg,haut,x,y,id,color); // on cree un bloc
                                if(type==0)// Si c'est pas un enfant
                                {
                                        ListeBlocs.push_back(nouv);
                                        if(premier==0)
                                        {
                                                ListeBlocs[ListeBlocs.size()-1]->m_conteneur=ListeBlocs[0]->m_conteneur;
                                                ListeBlocs[0]->m_conteneur->m_bloc_enfant.push_back(nouv);
                                        }
                                }
                                else // si c'est un enfant
                                {
                                        if(premier==1)
                                        {
                                                racine=ListeBlocs[0];
                                                ListeBlocs[0]->m_conteneur=racine;
                                                premier=0;
                                        }
                                        ListeBlocs[ListeBlocs.size()-1]->m_bloc_enfant.push_back(nouv);
                                        ListeBlocs[ListeBlocs.size()-1]->m_bloc_enfant[ListeBlocs[ListeBlocs.size()-1]
                                                                                       ->m_bloc_enfant.size()-1]
                                        ->m_conteneur=ListeBlocs[ListeBlocs.size()-1];
                                        ListeBlocs=ListeBlocs[ListeBlocs.size()-1]->m_bloc_enfant;
                                        std::cout << "Changement liste vers enfant : "
                                                  << std::endl << ListeBlocs[0]->m_nom << std::endl;
                                        type=0;
                                }
                        }
                        else{
                                nouv=ListeBlocs[0]->m_conteneur;
                                ListeBlocs.clear();
                                ListeBlocs.shrink_to_fit();
                                ListeBlocs.push_back(nouv);
                        }
                }
                ///Verification
                std::cout << std::endl << ListeBlocs[0]->m_nom << std::endl;
                std::cout << ListeBlocs[0]->m_x1 << std::endl;
                std::cout << ListeBlocs[0]->m_y1 << std::endl;
                std::cout << ListeBlocs[0]->m_couleur << std::endl;
                std::cout << "racine : " << racine->m_nom << std::endl;
                std::cout << "ground : " << racine->m_bloc_enfant[0]->m_nom << std::endl;
                std::cout << "robot : " << racine->m_bloc_enfant[0]->m_bloc_enfant[0]->m_nom << std::endl;
                std::cout << "box : " << racine->m_bloc_enfant[1]->m_nom << std::endl;
                std::cout << "flower : " << racine->m_bloc_enfant[1]->m_bloc_enfant[0]->m_nom << std::endl;
        }
}
