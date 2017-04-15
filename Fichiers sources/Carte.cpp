
#include "..\Fichiers header\Carte.h"
#define TAILLESPRITE_X 78
#define TAILLESPRITE_X_2 49
#define TAILLESPRITE_Y 45
#define TAILLESPRITE_Y_2 23

Carte::Carte()
{
		
}

// fix bug en hut a droite click

// 
sf::Vector2u Carte::getCasebyCoord(int x, int y, int max_x,int max_y,int dimx,int dimy)
{

	
	sf::Vector2u vec;
	double tailleSpriteX = floor((double)dimx / ((double)max_x+2))-2;
	double tailleSpriteX2 = floor(tailleSpriteX / 2);
	double tailleSpriteY =floor((double) dimy / ((double)max_y + 1));
	double tailleSpriteY2 = ceil(tailleSpriteY / 2);
	//printf("(%f,%f,%f,%f)\n", tailleSpriteX, tailleSpriteY,tailleSpriteX2,tailleSpriteY2);
	//printf("%d\n",max_x);
	int max_map_y = tailleSpriteY*((max_y + 1) / 2);
	if (y > max_map_y) {
		printf("error\n");
		vec.x = -1;
		vec.y = -1;
		return vec;
	}

	int max_map_x = tailleSpriteX*(max_x+1)+ tailleSpriteX2;
	if (x > max_map_x) {
		printf("error\n");
		vec.x = -1;
		vec.y = -1;
		return vec;
	}
	//printf("%d", max_map);
	//printf("(x = %d,y = %d)\n", max_x, max_y);
	double i = floor((double)x / tailleSpriteX);
	int j = 2*floor( (double)y / tailleSpriteY);
	double faux_j = floor((double)y / tailleSpriteY);

	//printf("i,j (%f,%f)\n",i, j);
	/*trouver la coordon�e de x et y dans le contexte du rectangle */

	double x_context_rectangle = floor((double)y - (faux_j * tailleSpriteY));
	double y_context_rectangle = floor((double)x - (i * tailleSpriteX));

	printf("x,y (%f,%f)\n", y_context_rectangle, x_context_rectangle);
	/* chercher sur quel rectangle on es*/
	sf::Vector2u point_x1;
	point_x1.y = 0;
	point_x1.x = tailleSpriteY2;
	sf::Vector2u point_x2;
	point_x2.y = tailleSpriteX2;
	point_x2.x = 0;
	sf::Vector2u point_x3;
	point_x3.y = tailleSpriteX;
	point_x3.x = tailleSpriteY2;
	sf::Vector2u point_x4;
	point_x4.y = tailleSpriteX2;
	point_x4.x = tailleSpriteY;

	int calcul_haut_gauche= (point_x1.y - point_x2.y)* x_context_rectangle + (point_x2.x - point_x1.x)*y_context_rectangle + (point_x1.x*point_x2.y - point_x1.y*point_x2.x);
	int calcul_haut_droit= (point_x2.y - point_x3.y)* x_context_rectangle + (point_x3.x - point_x2.x)*y_context_rectangle + (point_x2.x*point_x3.y - point_x2.y*point_x3.x);

	int calcul_bas_gauche= (point_x4.y - point_x1.y)* x_context_rectangle + (point_x1.x - point_x4.x)*y_context_rectangle + (point_x4.x*point_x1.y - point_x4.y*point_x1.x);
	int calcul_bas_droit= (point_x3.y - point_x4.y)* x_context_rectangle + (point_x4.x - point_x3.x)*y_context_rectangle + (point_x3.x*point_x4.y - point_x3.y*point_x4.x);

	/*printf(" haut gauche = %d\n",calcul_haut_gauche);
	printf("haut droit = %d\n",calcul_haut_droit);
	printf("bas gauche = %d\n",calcul_bas_gauche);
	printf("bas droit = %d\n", calcul_bas_droit);*/
	int real_i = 0;
	int real_j = 0;

	if (calcul_haut_gauche < 0 && calcul_haut_droit < 0 && calcul_bas_droit < 0 && calcul_bas_gauche < 0) {
		printf("in");
		real_i = i;
		real_j = j;
	}
	else if (calcul_haut_gauche >= 0) {
		if (i == 0 || j == 0) {
			real_i = i;
			real_j = j - 2;
			
			if (j == 0) {
				vec.x = -1;
				vec.y = -1;
				return vec;
			}
		}else {
			real_i = i - 1;
			real_j = j - 1;
			printf("1");
		}
		
	}
	else if (calcul_haut_droit>=0) {
		if (j == 0) {
			vec.x = -1;
			vec.y = -1;
			return vec;
		}
		else {
			real_i = i;
			real_j = j - 1;
			printf("2");
		}
			
	}
	else if (calcul_bas_gauche >= 0) {
		if (i == 0 || j == max_y ) {
			real_i = i;
			real_j = j;
			printf("3lol");
		}
		else {
			real_i = i - 1;
			real_j = j + 1;
			printf("3");
		}
		
	}
	else if (calcul_bas_droit >= 0) {
		if (j % 2 == 0 && i == max_x) {
			real_i = i;
			real_j = j;
		}
		else {
			real_i = i;
			real_j = j + 1;
			printf("4");
		}
				}

	//regler les cas particuler

	//(Ay - By)*Mx + (Bx - Ax)*My + (Ax.By - Ay.Bx)

	/*

	La formule g�n�rale est plut�t : signe de "(A^B).M"

"^" : �tant le produit vectoriel
"." : �tant le produit scalaire 

*/

	printf("(%d,%d)\n", real_j, real_i);
	
	vec.x = real_i;
	vec.y = real_j;
	return vec;
}
		
Carte::~Carte()
{
}

// x->i
// y->j
void Carte::getCasesForDeplacement(sf::Vector2u * tab, sf::Vector2u caseDepart,int mobi)
{
	if (caseDepart.y % 2 == 0) {
		for (int i = 0; i < 8; i++) {
			sf::Vector2u *tmp=NULL;
			if (i == 0) { //SUD
				tmp = new sf::Vector2u(caseDepart.x, caseDepart.y + 2);
			}
			else if (i == 1) { // SUD-EST
				tmp = new sf::Vector2u(caseDepart.x, caseDepart.y + 1);
			}
			else if (i == 2) { // EST
			    tmp = new sf::Vector2u(caseDepart.x+1, caseDepart.y);
			}
			else if (i == 3) { // NORD-EST
				tmp = new sf::Vector2u(caseDepart.x, caseDepart.y -1);
			}
			else if (i == 4) { // NORD
				tmp = new sf::Vector2u(caseDepart.x, caseDepart.y - 2);
			}
			else if (i == 5) { // NORD-OUEST
				tmp = new sf::Vector2u(caseDepart.x - 1, caseDepart.y - 1);
			}
			else if (i == 6) { // OUEST
				tmp = new sf::Vector2u(caseDepart.x - 1, caseDepart.y);
			}
			else if (i == 7) { // SUD-OUEST
				tmp = new sf::Vector2u(caseDepart.x - 1, caseDepart.y + 1);
			}		
			tab[i] = *tmp;
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			sf::Vector2u *tmp = NULL;
			if (i == 0) { //SUD
				tmp = new sf::Vector2u(caseDepart.x, caseDepart.y + 2);
			}
			else if (i == 1) { // SUD-EST
				tmp = new sf::Vector2u(caseDepart.x+1, caseDepart.y + 1);
			}
			else if (i == 2) { // EST
				tmp = new sf::Vector2u(caseDepart.x + 1, caseDepart.y);
			}
			else if (i == 3) { // NORD-EST
				tmp = new sf::Vector2u(caseDepart.x+1, caseDepart.y - 1);
			}
			else if (i == 4) { // NORD
				tmp = new sf::Vector2u(caseDepart.x, caseDepart.y - 2);
			}
			else if (i == 5) { // NORD-OUEST
				tmp = new sf::Vector2u(caseDepart.x - 1, caseDepart.y);
			}
			else if (i == 6) { // OUEST
				tmp = new sf::Vector2u(caseDepart.x - 1, caseDepart.y);
			}
			else if (i == 7) { // SUD-OUEST
				tmp = new sf::Vector2u(caseDepart.x, caseDepart.y + 1);
			}
			tab[i] = *tmp;
		}
	}
		
			
}

