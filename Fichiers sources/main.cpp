
#include <stdio.h>
#include<stdlib.h>

#include "..\\Fichiers header\Fenetre.h"
#include "..\\Fichiers header\FenetreYoan.h"
#include "..//Fichiers header/FenetreAlex.h"
#include "..\\Fichiers header\PersonnageYoan.h"
#include "..\\Fichiers header\InteractionBDD.h"
#include"..\\Fichiers header\Personnage.h"
#include <iostream>
#include <fstream>


string lecture() {
	std::string login;
	std::ifstream fichier("testFileWriter.txt");
	if (fichier) 
	{
		fichier >> login;
		cout << login;
	}
	else
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
	}
	return login;
}

int main()
{
	string joueur1;
	string joueur2;
	int choixMenu=5;
	char commande[100] = "java -cp \"mariadb-client.jar;.\" Main";
	sf::Vector2u taille;
	InteractionBDD* bdd = InteractionBDD::Ini();
	std::vector<Personnage>tabPersonnage;
	std::vector<Personnage>tabPersonnage2;
	
	/* on a cr� les 4 personnages du joueur num�ro 1 */
	system(commande);
	// lanc� le java ici !
	

	joueur1=lecture();
	//on lit le login
	tabPersonnage.push_back(Personnage(joueur1, "Archer"));
	tabPersonnage.push_back(Personnage(joueur1,"Paladin"));
	tabPersonnage.push_back(Personnage(joueur1, "Epeiste"));
	tabPersonnage.push_back(Personnage(joueur1, "Lancier"));

	if (joueur1 != "null") {
		Fenetre* fen;
		while (choixMenu!=3) {
			fen = new Fenetre(960, 540, joueur1);
			choixMenu = fen->affichageMenu();
			taille = fen->getTaille();
			printf("%d voici le choixMenu", choixMenu);
			if (choixMenu == 2) { // on appel la fenetre de yoan, il faut r�cup�rer la taille de ma fenetre !!
				joueur2 = fen->adversaireEnter();
				//on d�truit l'objet fenetre
				delete fen;
				if (joueur2 != "null") {
					tabPersonnage2.push_back(Personnage(joueur2, "Archer"));
					tabPersonnage2.push_back(Personnage(joueur2, "Paladin"));
					tabPersonnage2.push_back(Personnage(joueur2, "Epeiste"));
					tabPersonnage2.push_back(Personnage(joueur2, "Lancier"));

					String map_taille = "petite";

					// RECUPERATION DANS LA BASE DE DONNEE ICI
					PersonnageYoan* pj1 = new PersonnageYoan[4];
					PersonnageYoan* p1 = new PersonnageYoan("Archer",tabPersonnage[0]);
					PersonnageYoan* p2 = new PersonnageYoan("Paladin",tabPersonnage[1]);
					PersonnageYoan* p3 = new PersonnageYoan("Epeiste",tabPersonnage[2]);
					PersonnageYoan* p4 = new PersonnageYoan("Lancier",tabPersonnage[3]);

					pj1[0] = *p1;
					pj1[1] = *p2;
					pj1[2] = *p3;
					pj1[3] = *p4;

					PersonnageYoan* pj2 = new PersonnageYoan[4];
					PersonnageYoan* p10 = new PersonnageYoan("Archer",tabPersonnage2[0]);
					PersonnageYoan* p20 = new PersonnageYoan("Paladin",tabPersonnage2[1]);
					PersonnageYoan* p30 = new PersonnageYoan("Epeiste",tabPersonnage2[2]);
					PersonnageYoan* p40 = new PersonnageYoan("Lancier",tabPersonnage2[3]);

					pj2[0] = *p10;
					pj2[1] = *p20;
					pj2[2] = *p30;
					pj2[3] = *p40;
					JoueurYoan * players = new JoueurYoan[2];
					JoueurYoan *player1 = new JoueurYoan();
					JoueurYoan *player2 = new JoueurYoan();
					player1->pseudo = joueur1;
					player2->pseudo = joueur2;
					player1->p = pj1;
					player2->p = pj2;
					players[0] = *player1;
					players[1] = *player2;


					FenetreYoan* game = new FenetreYoan(taille, players);
					game->load();
					game->idle();
				}


			}
			else if (choixMenu == 1) {// on appel la fenetre d'alex
				//on d�truit l'objet fenetre
				delete fen;
				//bdd->setEquipementOnChar("lance en fer","armure",joueur1,"Archer");
				bdd->setXP(10,joueur1,"Archer");
				/*string* armeDropped;
				vector<vector<string>> itemInvent = bdd->getEquipement("dragodia");
				vector<vector<vector<string>>>* equipPerso = new vector<vector<vector<string>>>[4];
				equipPerso[0].push_back(bdd->getEquipementEquiped("dragodia", "Archer"));
				equipPerso[1].push_back(bdd->getEquipementEquiped("dragodia", "Epeiste"));
				equipPerso[2].push_back(bdd->getEquipementEquiped("dragodia", "Lancier"));
				equipPerso[3].push_back(bdd->getEquipementEquiped("dragodia", "Paladin"));
				int* carac[4];
				carac[0] = bdd->getCarac("dragodia", "Archer");
				carac[1] = bdd->getCarac("dragodia", "Epeiste");
				carac[2] = bdd->getCarac("dragodia", "Lancier");
				carac[3] = bdd->getCarac("dragodia", "Paladin");
				FenetreAlex *fenetreAlex = new FenetreAlex(carac, equipPerso, itemInvent);
				fenetreAlex->game();
				bdd->getCarac("dragodia", "Archer");
				/*armeDropped=bdd->dropEquipement("dragodia");
				if (armeDropped[0] != "null") {
					printf("%s\n", armeDropped[0].c_str());
					printf("%s\n", armeDropped[1].c_str());
					printf("%s\n", armeDropped[2].c_str());
				}*/
			}
		}
	}
	
	
	return 0;
}