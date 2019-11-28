#include "header.h"

void lireFichier(Bloc*& racine, std::string& nom_fichier)
{
        std::ifstream fichierRom(nom_fichier);
        std::vector<Bloc*> ListeBlocs;

        if(!fichierRom)
        {
                std::cout << "Erreur de lecture du fichier";
                exit(EXIT_FAILURE);
        }
        else
        {
                double larg,haut; // Parametre pour bloc
                bool type,premier=1; // Type est un bool qui nous dit si nous avont a fair a un enfant, vrais pour type = 1
                std::string id, color, refpos, basepos, ligne; // Parametre pour bloc + ligne a l'instant t
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
                                fichierRom >> larg;
                                fichierRom >> haut;
                                fichierRom >> color;
                                fichierRom >> refpos;
                                fichierRom >> basepos;

                                std::cout << "lu\n";

                                Bloc* nouv = new Bloc{larg,haut,id,color,refpos,basepos};

                                ///Affichages test
                                std::cout << nouv->m_largeur << std::endl;
                                std::cout << nouv->m_hauteur << std::endl;
                                std::cout << nouv->m_x1 << std::endl;
                                std::cout << nouv->m_y1 << std::endl;
                                std::cout << nouv->m_nom << std::endl;
                                std::cout << nouv->m_couleur << std::endl;

                                if(type==0)// Si ce n'est pas un enfant
                                {
                                        ListeBlocs.push_back(nouv);

                                        if(premier==0) ///Si c'est le premier
                                        {
                                            ///L'adresse parent du nouveau bloc est la meme que le premier
                                                ListeBlocs[ListeBlocs.size()-1]->m_conteneur=ListeBlocs[0]->m_conteneur;
                                            ///On copie en memoire le nouveau bloc
                                                ListeBlocs[0]->m_conteneur->m_bloc_enfant.push_back(nouv);
                                        }
                                }
                                else // si c'est un enfant
                                {
                                        if(premier==1) ///Si c'est la racine
                                        {
                                                racine=ListeBlocs[0]; ///L'adresse de la racine est l'adresse du bloc actuel
                                                racine->m_conteneur=nullptr; ///La racine n'a pas de parent
                                                premier=0; ///Les prochaines operations n'impliquent pas directement la racine
                                        }
                                        ///On ajoute l'enfant
                                        ListeBlocs[ListeBlocs.size()-1]->ajouterbloc(larg,haut,id,color,refpos,basepos);
                                        ///On attribue l'adresse du parent a l'enfant
                                        ListeBlocs[ListeBlocs.size()-1]->m_bloc_enfant[ListeBlocs[ListeBlocs.size()-1]
                                                                                        ->m_bloc_enfant.size()-1]
                                                                                        ->m_conteneur=ListeBlocs[ListeBlocs.size()-1];
                                        ///On copie l'enfant au vecteur temporaire
                                        ListeBlocs=ListeBlocs[ListeBlocs.size()-1]->m_bloc_enfant;
                                        std::cout << "Changement liste vers enfant : "
                                                  << std::endl << ListeBlocs[0]->m_nom << std::endl;
                                        type=0;
                                }
                        }
                        else{
                                ///On revient au vecteur parent
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


Bloc* Bloc::store() ///Ne fonctionne pas correctement
{
    Bloc* copie = new Bloc{m_largeur,m_hauteur,m_x1,m_y1,m_nom,m_couleur};
    Bloc* buffer, adresse;

    for(size_t i=0;i<m_bloc_enfant.size();++i)
    {
        buffer=m_bloc_enfant[i]->store();
        copie->SetBlocsEnf(buffer);
    }

    return copie;
}
