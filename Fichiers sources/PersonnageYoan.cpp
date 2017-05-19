#include "..\\Fichiers header\PersonnageYoan.h"
PersonnageYoan::PersonnageYoan(std::string typeConstr){
	this->type = typeConstr;

	char* s = new char[10];
	memset(s, 0, 10);
	sprintf_s(s, 10, "%00d%00d%00d\0", 0, 0, 0);
	this->position.x = -1;
	this->position.y = -1;
	this->id = s;
	this->vitesse_dattaque = 1;
	this->isdead = false;
	this->level = -1;
	if (type == "constr") {
		this->degat = -1;
		this->armure = -1;
		this->deplacement = -1;
		this->deplacementRestante = this->deplacement;
		this->range = -1;
		this->vie = -1;
		this->vieRestante = -1;

	}

	if (type == "Archer") {
		this->degat = 40;
		this->armure = 0;
		this->deplacement = 2;
		this->deplacementRestante = this->deplacement;
		this->range = 2;
		this->vie = 50;
		this->vieRestante = this->vie;

	}
	if (type == "Paladin") {
		this->degat = 20;
		this->armure = 40;
		this->deplacement = 4;
		this->deplacementRestante = this->deplacement;
		this->range = 1;
		this->vie = 100;
		this->vieRestante = this->vie;

	}
	if (type == "Epeiste") {
		this->degat = 40;
		this->armure = 10;
		this->deplacement = 2;
		this->deplacementRestante = this->deplacement;
		this->range = 1;
		this->vie = 90;
		this->vieRestante = this->vie;

	}
	if (type == "Lancier") {
		this->degat = 30;
		this->armure = 30;
		this->deplacement = 3;
		this->deplacementRestante = this->deplacement;
		this->range = 1;
		this->vie = 80;
		this->vieRestante = this->vie;

	}
}
std::string PersonnageYoan::afficher() {
	std::string s = this->type +
		"        " + std::to_string(this->vieRestante) + "/" + std::to_string(this->vie) +
		"    " + std::to_string(this->deplacementRestante) + "/" + std::to_string(this->deplacement) +
		"  " + std::to_string(this->degat) +
		"   " + std::to_string(this->armure) +
		"         " + std::to_string(this->range);

	return s;
}
PersonnageYoan::PersonnageYoan() {

}

int* PersonnageYoan::getNewCaracwithCase(Carte c) {
	int* tab = new int[3];
	if (this->isdead) {
		tab[0] = -1;
		tab[1] = -1;
		tab[2] = -1;
		return tab;
	}
	Case* casee=c.caseJeu[this->position.y][this->position.x];

	
	tab[0] = this->armure + casee->armure;
	tab[1] = this->degat + casee->degat;
	tab[2] = this->range;

	string typ = this->type;
	string typ2 = "Archer";
	if (typ == typ2) {
		tab[2] = this->range + casee->range;

	}
	
	return tab;

}
bool* PersonnageYoan::isChangeCarac(Carte c) {
	bool* tabb = new bool[3];

	if (this->isdead) {
		tabb[0] = false;
		tabb[1] = false;
		tabb[2] = false;
		return tabb;
	}
	Case* casee = c.caseJeu[this->position.y][this->position.x];
	int* tab = new int[3];

	tab[0] = this->armure + casee->armure;
	tab[1] = this->degat + casee->degat;
	tab[2] = this->range;

	string typ = this->type;
	string typ2 = "Archer";
	if (typ == typ2) {
		tab[2] = this->range + casee->range;

	}
	bool* b = new bool[3];

	for (int i = 0; i < 3; i++) {
		b[i] = false;
	}
	if (tab[0] != this->armure) {
		b[0] = true;
	}
	if (tab[1] != this->degat) {
		b[1] = true;
	}
	if (tab[2] != this->range) {
		b[2] = true;
	}

	return b;
}
void PersonnageYoan::setCarac(){
}
