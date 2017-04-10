#include "..\Fichiers header\FenetreYoan.h"
/*Fenetre* game = new Fenetre();
	Carte* map=game->load();
	game->idle(map);*/
#include <SFML\Window\Event.hpp>

#include <iostream>

#include "..\Fichiers header\Carte.h"
#include "..\Fichiers header\Case.h"
#include "..\Fichiers header\Fichier.h"

#define MAXI 16 //1280 1024
#define MAXJ 34

#define TAILLESPRITE_X 78
#define TAILLESPRITE_Y 45

#define TAILLEMENU_X 960

#define TAILLEDEBASEY 540
#define TAILLEMENU_Y 150


#define ECRAN_BAS (6 * 45) // decalage pour le menu du bas

using namespace std;
using namespace sf;

FenetreYoan::FenetreYoan(sf::Vector2u dimension,Joueur* playerss)
{
	// DEBUG
	sf::RenderWindow *window = new RenderWindow(sf::VideoMode(960, 540), "Debug Window", sf::Style::Titlebar);
	this->debug = window;
	this->debug->setPosition(sf::Vector2i(0, 0));
	//

	// choix joueur aleatoirement 
	srand(time(NULL));
	this->joueur= rand() % 2;
	//

	// parametrage fenetre de jeu
	this->create(VideoMode(dimension.x, dimension.y), "Ages of Strategies",sf::Style::Titlebar);
	this->setFramerateLimit(60); // limit� a 60fps
	this->setPosition(sf::Vector2i(960, 0));
	this->dimension_x = dimension.x;
	this->dimension_y = dimension.y;
	this->max_x = (dimension.x / TAILLESPRITE_X)-1;
	this->max_y = ((dimension.y - ECRAN_BAS)/ TAILLESPRITE_Y)*2;
	//
	// variable pour multi resolution 
	if (this->max_x > MAXI) {
		this->max_x = MAXI;
	}
	if (this->max_y > MAXJ) {
		this->max_y = MAXJ;
	}

	this->scaleMenuBasX = (double)this->dimension_x / TAILLEMENU_X;
	this->scaleMenuBasY= ((double)this->dimension_y/(TAILLEDEBASEY/ TAILLEMENU_Y))/TAILLEMENU_Y;
	//

	// Initialisation des Joueurs
	this->players= playerss;
	Personnage* p_good = new Personnage[4];
	Personnage* p_good2 = new Personnage[4];
	for (int i = 0; i < 4; i++) {
		Personnage *p = new Personnage("constr");
		p_good[i] = *p;
		p_good2[i] = *p;
	}
	this->players[0].p_placer = p_good;
	this->players[1].p_placer = p_good2;

	//Initialisation de la map virtuel
		std::map<char*, sf::Vector2u*,char_cmp> *dicoo = new std::map<char*, sf::Vector2u*,char_cmp>;
		std::map<char*, sf::Vector2u*, char_cmp> *dicooIJ = new std::map<char*, sf::Vector2u*, char_cmp>;
		std::map<char*, sf::Vector2u*, char_cmp> *dicooXY = new std::map<char*, sf::Vector2u*, char_cmp>;
		BlendModee *bmm = new BlendModee(dicoo, dicooIJ, dicooXY);
		this->bm = *bmm;

		//Initialisation des personnages 
		Sprite* sPerso = new Sprite[4];
		this->sPersonnage = sPerso;

}
Sprite FenetreYoan::getSpritebyname(std::string str) {

	if (str == "archer") {
		return this->sPersonnage[0];
	}
	else if (str == "epeiste") {
		return this->sPersonnage[1];
	}
	else if (str == "lancier") {
		return this->sPersonnage[3];
	}
	else if (str == "paladin") {
		return this->sPersonnage[2];
	}

}
bool FenetreYoan::verifContrainte(int x,int y) {
	if (this->map->caseJeu[y][x]->who != -1) {
		printf("impossible\n");
		return false;
	}
	std::string s = this->map->caseJeu[y][x]->types;
	printf("%s", s);
	if (s == "eau") {
		printf("impossible\n");
		return false;
	}
	return true;
}

void FenetreYoan::controleur_placement(Event event) {
	// on regarde le type de l'�v�nement...
/*	switch (event.type)
	{
	case Event::KeyPressed:
		return;
			break;
	case  Event::Closed:
		this->close();
		break;
	case sf::Event::Resized:
		this->dimension_x = this->getSize().x;
		this->dimension_y = this->getSize().y;
	case sf::Event::MouseButtonPressed:*/

		if (event.mouseButton.button == sf::Mouse::Left) //
		{
			Color c=this->bm.image.getPixel(event.mouseButton.x, 540-event.mouseButton.y);
			char* s = new char[10];
			memset(s, 0, 10);
			sprintf_s(s, 10, "%00d%00d%00d\0",c.r, c.g, c.b);


			sf::Vector2u* vec = (*(this->bm.dico))[s];
			
			//vec = this->map->getCasebyCoord(event.mouseButton.x, event.mouseButton.y, this->max_x - 1, this->max_y - 1, this->dimension_x, this->dimension_y);
			if (this->players[this->joueur].selected != -1 && this->verifContrainte(vec->x,vec->y) && vec != NULL) {
			//	printf("joueur %d personnage %d sur la case (%d,%d)", this->joueur, this->players[this->joueur].selected, vec->y, vec->x);
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer] = this->players[this->joueur].p[this->players[this->joueur].selected]; //placer le personnage dans le tab de perso placer;
				this->map->caseJeu[vec->y][vec->x]->who = this->joueur;
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer].position.x = vec->x;
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer].position.y = vec->y;
				printf("( %d,%d )\n",vec->x,vec->y);
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer].appartenance.x = this->joueur;
				this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer].appartenance.y = this->players[this->joueur].personnage_placer;
//				printf("%s\n", this->players[this->joueur].p_placer[this->players[this->joueur].personnage_placer].afficher);



				this->players[this->joueur].personnage_placer++;
			}
			this->players[this->joueur].selected = -1;
			this->players[this->joueur].selected = -1;
			this->clear(Color(100, 100, 100));
			this->render(this->joueur);

		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			//printf("%d , %d\n", event.mouseButton.x, event.mouseButton.y);
			if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 370 && event.mouseButton.y<400) {
				printf("perso 1\n");
				this->players[this->joueur].selected = 0;
			}
			else if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 400 && event.mouseButton.y < 430) {
				this->players[this->joueur].selected = 1;
				printf("perso 2\n");
			}
			else if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 430 && event.mouseButton.y < 460) {
				printf("perso 3\n");
				this->players[this->joueur].selected = 2;
			}
			else if (event.mouseButton.x > 7 && event.mouseButton.x < 714 && event.mouseButton.y >= 460 && event.mouseButton.y < 490) {
				printf("perso 4\n");
				this->players[this->joueur].selected = 3;
			}
			/*
			else {
			sur une case ou il y a un personnage alors �a le retire 
			}
			*/
			this->clear(Color(100, 100, 100));
			this->render(this->joueur);
			}
		/*
		break;
	default:
		break;
	}*/
	
}

FenetreYoan::~FenetreYoan()
{
}

void FenetreYoan::load() {
	// 1) Chargement des resources (texture -> sprite)
	// 2) Chargement des fichiers de "niveau"



	// Todo : Recuperer tableau a 1 dimensions contenant les lettres => NOP!
	Fichier* pFichier = new Fichier();
	string textureId[MAXJ][MAXI];
	pFichier->read("../Fichiers externe/maps/map.txt", textureId);

	//
	Texture* pPlaineTexture = new Texture();
	Texture* pEauTexture = new Texture();
	Texture* pDesertTexture = new Texture();

	Texture* pPlaineTextureMin = new Texture();
	Texture* pEauTextureMin = new Texture();
	Texture* pDesertTextureMin = new Texture();

	const char* szResourcePlaine = "../Fichiers externe/img/plaine.png";
	if (!pPlaineTexture->loadFromFile(szResourcePlaine)) {
		printf("Error load sprite %s", szResourcePlaine);
	}
	const char* szResourceEau = "../Fichiers externe/img/eau.png";
	if (!pEauTexture->loadFromFile(szResourceEau)) {
		printf("Error load sprite %s", szResourceEau);
	}
	const char* szResourceDesert = "../Fichiers externe/img/desert.png";
	if (!pDesertTexture->loadFromFile(szResourceDesert)) {
		printf("Error load sprite %s", szResourceDesert);
	}
	/*  */
	const char* szResourcePlaineMin = "../Fichiers externe/img/plaine_min.png";
	if (!pPlaineTextureMin->loadFromFile(szResourcePlaineMin)) {
		printf("Error load sprite %s", szResourcePlaineMin);
	}
	const char* szResourceEauMin = "../Fichiers externe/img/eau_min.png";
	if (!pEauTextureMin->loadFromFile(szResourceEauMin)) {
		printf("Error load sprite %s", szResourceEauMin);
	}
	const char* szResourceDesertMin = "../Fichiers externe/img/desert_min.png";
	if (!pDesertTextureMin->loadFromFile(szResourceDesertMin)) {
		printf("Error load sprite %s", szResourceDesertMin);
	}

	Case*** pTableau = new Case**[this->max_y];
	Carte* pMap = new Carte();
	string s;
	for (int j = 0; j < this->max_y; j++) {
		pTableau[j] = new Case*[this->max_y];

		for (int i = 0; i < this->max_x; i++) {

			Case* pCase=NULL;
			s= textureId[j][i];
			if (s=="plaine") {
				if (i == 0 && j % 2 == 0 || j == this->max_y -1 || i == this->max_x-1) {
					Sprite *plaine = new Sprite(*pPlaineTexture);
					pCase = new Case(*plaine);
				}
				else {
					
					Sprite *plaineMin = new Sprite(*pPlaineTextureMin);
					pCase = new Case(*plaineMin);
				}
			
			}
			if (s == "eau") {
				if (i == 0 && j % 2 == 0 || j == this->max_y - 1 || i == this->max_x - 1) {
					Sprite *eau = new Sprite(*pEauTexture);
					pCase = new Case(*eau);
				}
				else {
					Sprite *EauMin = new Sprite(*pEauTextureMin);
					pCase = new Case(*EauMin);
				}
			}
				
			
			if (s=="desert") {
				if (i == 0 && j % 2 == 0 || j == this->max_y - 1 || i== this->max_x - 1) {
					
					Sprite *desert = new Sprite(*pDesertTexture);
				pCase = new Case(*desert);
				}
				else {
					Sprite *DesertMin = new Sprite(*pDesertTextureMin);
					pCase = new Case(*DesertMin);
				}
			

				}
			pCase->types = s;

			pTableau[j][i] = pCase;
		}
	}

	pMap->caseJeu = pTableau;
	this->map = pMap;



	// Chargement des resources PERSONNAGES
	Texture* pArcherTexture = new Texture();
	Texture* pEpeisteTexture = new Texture();
	Texture* pPaladinTexture = new Texture();
	Texture* pLancierTexture = new Texture();

	const char* szResourceArcher = "../Fichiers externe/img/archer.png";
	if (!pArcherTexture->loadFromFile(szResourceArcher)) {
		printf("Error load sprite %s", szResourceArcher);
	}
	const char* szResourceEpeiste = "../Fichiers externe/img/epeiste.jpg";
	if (!pEpeisteTexture->loadFromFile(szResourceEpeiste)) {
		printf("Error load sprite %s", szResourceEpeiste);
	}
	const char* szResourcePaladin = "../Fichiers externe/img/paladin.jpg";
	if (!pPaladinTexture->loadFromFile(szResourcePaladin)) {
		printf("Error load sprite %s", szResourcePaladin);
	}
	const char* szResourceLancier = "../Fichiers externe/img/lancier.jpg";
	if (!pLancierTexture->loadFromFile(szResourceLancier)) {
		printf("Error load sprite %s", szResourceLancier);
	}
	Sprite *sArcher = new Sprite(*pArcherTexture);
	Sprite *sEpeiste = new Sprite(*pEpeisteTexture);
	Sprite *sPaladin = new Sprite(*pPaladinTexture);
	Sprite *sLancier = new Sprite(*pLancierTexture);

	this->sPersonnage[0] = *sArcher;
	this->sPersonnage[1] = *sEpeiste;
	this->sPersonnage[2] = *sPaladin;
	this->sPersonnage[3] = *sLancier;
}
// choix 1er joueur choisie

void FenetreYoan::PlacementPersonnage() {
	this->clear(Color(100, 100, 100));
	this->render(this->joueur);
	//Personnage** persos = new Personnage*[2]; // tableau de perso a remplir 
	while (1) {

		while (this->pollEvent(this->event))
		{
			this->controleur_placement(this->event);
		}

		if (this->players[this->joueur].personnage_placer == 4) {
			printf("Joueur %d, a terminer de placer !",this->joueur+1);
			return;
		}
	}
	
	return;
}

void FenetreYoan::idle() {	
	this->PlacementPersonnage();
	this->joueur = (this->joueur == 0) ? 1 : 0;
	this->PlacementPersonnage();

	/* game ( methode ou on verifie click et recupere i,j =>
	si c'est une unit� =>
	- on afficher dans le carre le sprite de l'unit� + sur quelle case elle est
	- on affiche les deplacement possible autour d'elle si il lui reste des pm ;
	- on surligne en bas sur l'unit�

	si cest la case =>
	- on affiche la case dans le carre
	- si auparavant on a cliquer sur une unit� elle se deplacera 
	*/
}

void FenetreYoan::player_choice() {
	if (this->players[this->joueur].selected != -1) {
		sf::CircleShape shape(8);
		shape.setFillColor(sf::Color(74, 167, 250));
		// d�finit un contour orange de 10 pixels d'�paisseur
		shape.setOutlineThickness(1);
		shape.setOutlineColor(sf::Color(250, 150, 100));
		shape.setPosition(650, 377+ this->players[this->joueur].selected*30);
		this->draw(shape);
	}
}

void FenetreYoan::render(int quellejoueur) {
	
	/* SHADER */
	sf::Shader shader;

	/* if transparence return transparence else return color param*/

	const std::string fragmentShader = \
		"uniform sampler2D texture;" \
		"uniform vec3 color;" \
		"void main()" \
		"{" \
		" vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);" \
		"if(pixel.a!=0.0) { gl_FragColor = vec4(color.rgb, 1.0);  return ;  } " \
		"gl_FragColor = pixel;" \
		"}";

	// load only the fragment shader

	if (!shader.loadFromMemory(fragmentShader, sf::Shader::Fragment))
	{
		// error...
	}
	shader.setUniform("texture", sf::Shader::CurrentTexture);

	//

	// RENDU SPRITE MENU HAUT

	float offsetX = 0; //25;
	float offsetY = 0; //25;

	const float tileWidth = 78.0;
	const float tileWidth2 = tileWidth / 2.0;
	const float tileHeight = 23.0;
	
	// rendu case de la map 
	sf::RenderTexture renderTexture;
	if (!renderTexture.create(960, 540))
	{
		// erreur...
	}
	renderTexture.clear();
	

	for (int j = 0; j < this->max_y; j++) {
		float offsetPosX = j % 2 == 0 ? offsetX : offsetX + tileWidth2;
		float offsetPosY = offsetY;

		for (int i = 0; i < this->max_x; i++) {
			this->map->caseJeu[j][i]->sprite.setPosition(offsetPosX + i * tileWidth, offsetPosY + j * tileHeight);

			Sprite* a = &this->map->caseJeu[j][i]->sprite;
			/*    */
			//float nombre = 0;
			//srand(time(NULL));
			//nombre = (float)rand() / (float)RAND_MAX;
			//printf("%f", nombre);
			unsigned int r = i*23;
			unsigned int g = j*12;
			unsigned int b = 100;
			
			//std::string a = std::to_string(r) + std::to_string(g) + std::to_string(b);
				//String *s = new String(std::to_string(r) + std::to_string(g) + std::to_string(b));
				char* s = new char[10];
				memset(s, 0, 10);
				sprintf_s(s,10,"%00u%00u%00u\0", r, g, b);
				Vector2u *v = new Vector2u();
				v->x = i;
				v->y = j;
				
				this->bm.dico->insert(std::pair<char*, sf::Vector2u*>(s,v));

			float fr =(float)r / 255.0;
			float fg = (float)g / 255.0;
			float fb = (float)b / 255.0;
			shader.setUniform("color", Glsl::Vec3(fr, fg, fb));
			RenderStates rs(&shader);
			renderTexture.draw(*a, rs); // rendu dans une texture shader
			this->draw(*a); // rendu dans une fenetre
		

		}
	}
	


	// rendu du menu du bas
	Texture* pMenuBas = new Texture();
	const char* szResourceMenuBas = "../Fichiers externe/img/menu_bas.png";
	if (!pMenuBas->loadFromFile(szResourceMenuBas)) {
		printf("Error load sprite %s", szResourceMenuBas);
	}

	Sprite *sMenuBas = new Sprite(*pMenuBas);
	sMenuBas->setPosition(0,360);
	this->draw(*sMenuBas);
	sMenuBas->scale(this->scaleMenuBasX, this->scaleMenuBasY);

	// rendu du text
	sf::Font font;
	if (!font.loadFromFile("../Fichiers externe/arial.ttf"))
	{
		printf("Error load text :%s", font);
	}
	for (int i = 0; i < 4; i++) {
		sf::Text type;
		type.setFont(font);
		type.setCharacterSize(15);
		type.setString(this->players[this->joueur].p[i].type);
		type.setPosition(20, 375 + (i * 30));
		sf::Text pv;
		pv.setFont(font);
		pv.setCharacterSize(12);
		pv.setString(std::to_string(this->players[this->joueur].p[i].vieRestante) + "/" + std::to_string(this->players[this->joueur].p[i].vie));
		pv.setPosition(125, 375 + (i * 30));
		sf::Text pm;
		pm.setFont(font);
		pm.setCharacterSize(15);
		pm.setString(std::to_string(this->players[this->joueur].p[i].deplacementRestante) + "/" + std::to_string(this->players[this->joueur].p[i].deplacement));
		pm.setPosition(220, 375 + (i * 30));
		sf::Text degat;
		degat.setFont(font);
		degat.setCharacterSize(15);
		degat.setString(std::to_string(this->players[this->joueur].p[i].degat));
		degat.setPosition(300, 375 + (i * 30));
		sf::Text armor;
		armor.setFont(font);
		armor.setCharacterSize(15);
		armor.setString(std::to_string(this->players[this->joueur].p[i].armure));
		armor.setPosition(400, 375 + (i * 30));
		sf::Text range;
		range.setFont(font);
		range.setCharacterSize(15);
		range.setString(std::to_string(this->players[this->joueur].p[i].range));
		range.setPosition(550, 375 + (i * 30));

		

		
		//std::string s = this->personnagesJ1[i].afficher();
		
		//	text.setColor(sf::Color::Red);
		this->draw(type);
		this->draw(pv);
		this->draw(pm);
		this->draw(degat);
		this->draw(armor);
		this->draw(range);
		
	}
	sf::Text name;
	name.setFont(font);
	name.setCharacterSize(20);
	name.setString(this->players[this->joueur].pseudo);
	name.setPosition(10, 520);
	this->draw(name);
	this->player_choice();

	// affichage des perso des joueurs
	for(int j = 0;j<2;j++) {
		for (int i = 0; i < 4; i++) {

			char* s = new char[10];
			memset(s, 0, 10);
			sprintf_s(s, 10, "%00d%00d%00d\0", 0, 0, 0);

			int position_x_tmp = this->players[j].p_placer[i].position.x;
			if (position_x_tmp != -1) {
				std::string name = this->players[j].p_placer[i].type;
				sf::Shader shader2;
				Sprite spriteperso = getSpritebyname(name);

				unsigned int r = 10;
				unsigned int g = 63 * (j+1);
				unsigned int b = i * (127+1);

				char* couleurname = new char[10];
				memset(couleurname, 0, 10);
				sprintf_s(couleurname, 10, "%00d%00d%00d\0", r, g, b);


				Vector2u *v = new Vector2u();
				v->x = this->players[j].p_placer[i].position.x;
				v->y = this->players[j].p_placer[i].position.y;
				this->bm.dicoPersonnagesIJ->insert(std::pair<char*, sf::Vector2u*>(couleurname, v));

				//char* id = new char[10];
				//id = this->players[j].p_placer[i].id;
				//sf::Vector2u* res1 = (*.(this->bm.dicoPersonnagesIJ))[id];

				float offsetPosX = this->players[j].p_placer[i].position.x % 2 == 0 ? offsetX : offsetX + tileWidth2;
				
				float offsetPosY = offsetY;

				spriteperso.setPosition((this->players[j].p_placer[i].position.x *80)+20, this->players[j].p_placer[i].position.y *45);
				if (this->players[j].p_placer[i].position.y % 2 == 1) {
					spriteperso.setPosition((this->players[j].p_placer[i].position.x * 80+60), this->players[j].p_placer[i].position.y * 45/2);
				}
				if (this->players[j].p_placer[i].position.y % 2 == 0) {
					spriteperso.setPosition((this->players[j].p_placer[i].position.x * 80)+20, (this->players[j].p_placer[i].position.y/2) * 45 );
				}

				float fr = (float)r / 255.0; // ici arriver a trouver les 3 r g b a partir du char;
				float fg = (float)g / 255.0;
				float fb = (float)b / 255.0;
				shader.setUniform("color", Glsl::Vec3(fr, fg, fb));
				RenderStates rs(&shader);
				this->draw(spriteperso);
				renderTexture.draw(spriteperso, rs); // rendu dans une texture shader
			}
		}
	}


	//DEBUG	
	const sf::Texture& texture = renderTexture.getTexture();
	sf::Sprite sprite(texture);
	Image *image;
	this->debug->draw(sprite);
	this->debug->display();
	this->bm.image = texture.copyToImage();
	this->display();
	
}

