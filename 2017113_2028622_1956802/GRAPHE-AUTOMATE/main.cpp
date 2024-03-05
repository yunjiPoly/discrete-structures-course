//////////////////////////////////////////////////////////////////////
/// @file main.cpp
/// @author Yun Ji Liao
/// @date 6/9/2021
/// @version 1.0
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "Graphe.h"

using namespace std;


enum Option {
	LIRE = 1,
	AFFICHER,
	FRONTIERE,
	DISJ,
	QUITTER,
	JEU
} choix;


//prototypoes
int menu();
Graphe* creerGraphe(const string&);
void lireGraphe(Graphe*);
void shortestPath(Graphe*, const string&, const string&);
void SelectionJeuInstructf();
/*Corps du fonction*/
int main() {
	Graphe* graphe = nullptr;
	string sauvegarde;
	int choix;
	bool lock = true;

	while ((choix = menu()) != QUITTER) {
		switch (choix) {
		case LIRE: {
			std::string nomFichier;
			std::cout << "Entrez le nom du ficher a lire sans mettre txt\n";
			std::cin >> nomFichier;
			cin.ignore();
			graphe = creerGraphe(nomFichier);
			sauvegarde = nomFichier;
			cout << "\nGraph cree!" << endl;
			break;
		}
		case  AFFICHER: {
			if (graphe == nullptr) {
				cout << "Madame veuillez indiquer le nom fichier(option 1) svp\n";
			}
			else {
				lireGraphe(graphe);
			}
			break;
		}
		case FRONTIERE: {
			lock = false;
			if (graphe->isColored()) {
				cout << "\n\nfrontiere deja coloree\n\n";
				break;
			}
			else {
				cout << "\n\nLes frontieres sont maintenant colorees" << endl << endl;
				graphe->colorer();
				break;
			}
		}
		case DISJ: {

			if (lock == false) {
				cout << "\nPoint de depart (nom du pays): ";
				string paysDepart;

				while (!(cin >> paysDepart)) {

					cin.clear();
					cin.ignore(256, '\n');
					cout << "\n\nERREUR! Veuillez entrer une charactere" << endl
						<< "Reinserez le point de depart : ";
				}

				cout << "\nDestination (nom du pays): ";
				string paysDestination;

				while (!(cin >> paysDestination)) {
					cin.clear();
					cin.ignore(256, '\n');
					cout << "\n\nERREUR! Veuillez entrer une charactere" << "\n"
						<< "Reinserez le point de destination : ";
				}

				cout << "\nCouleur: ";
				string couleur;
				Graphe* newgraphe;
				if (!graphe->exist(paysDepart) || !graphe->exist(paysDestination)) {
					cout << "les pays passé en paramètre n'existe pas" << endl;
					break;
				}
				while (!(cin >> couleur)) {
					cin.clear();
					cin.ignore(256, '\n');
					cout << "\n\nERREUR! euillez entrer une charactere" << "\n";
					//		<< "Reinserez le couleur a eviter : ";
				}
				if (couleur == "bleu" || couleur == "jaune" || couleur == "rouge" || couleur == "vert") {
					newgraphe = graphe->extractionGraphe(couleur);
				}
				else if (couleur == "neutre") { newgraphe = graphe; }

				else {
					cerr << "\n\nCe couleur ne peut pas etre utiliser!" << endl << "Reinserez le couleur a eviter\n";
					break;
				}

				// verifie si le pays n'est pas extracted
				if (newgraphe->findPaysCouleur(paysDepart) && newgraphe->findPaysCouleur(paysDestination)) {
					// trouver le plus court chemin
					shortestPath(newgraphe, paysDepart, paysDestination);
					graphe = creerGraphe(sauvegarde);
				}

				else
				{
					//	cerr << "\n\n ERROR! Le pays de depart ou le pays de destination a ete enleve en raison du couleur a eviter ou il n'existe pas\n";
					cout << "ERROR!" << endl << "Le pays de depart " << paysDepart << " ou le pays de destination " << paysDestination << "a ete enleve en raison du couleur a eviter ou le chemin entre les deux n'existe pas" << endl;
					break;
				}
			}
			else if (graphe == nullptr) {
				cerr << "\n\n ERROR! Allez sur option1";
				break;
			}
			else if (!(graphe->isColored())) {
				cout << "\n\nAllez colorez le graphe(option3)\n";
				break;
			}
			break;
		}
		case JEU:
			SelectionJeuInstructf();
			break;
		default:
			break;
		}
	}
}

/*Interface menu qui propose  choix differente :
1_ Lire une carte
2_Afficher une carte
3_Determiner les frontieres
4_Determiner le plus court chemin
la fonction prend un nombre donné par le flux d'entré cin et affiche le résulat du nombre i donné avec 1<= i <=5 si i ne respecte pas la contrainte ou i n'est pas un entier menu nouos affiche une erreur
*/

int menu() {

	// Interface
	cout << "\nChoisir un des options suivante" << endl
		<< "(1) - Lire une carte" << endl
		<< "(2) - Afficher une carte" << endl
		<< "(3) - Determiner les frontieres" << endl
		<< "(4) - Determiner le plus court chemin" << endl
		<< "(5) - Quitter" << endl
		<< "(6) - Aller sur le jeu instructif" << endl;
	cout << "\nEntrez votre choix : ";
	int choix;

	while (!(cin >> choix)) {
		cin.clear();
		cin.ignore(6, '\n');
		cout << "\nERROR! Expecting an integer!" << endl
			<< "Entrez votre choix : ";
	}

	return choix;
}

// creer le graphe representant la carte des pays a partir d’un fichier texte le nom de ce fichier(sans le txt) étant passé en paramètre
Graphe* creerGraphe(const string& filename) {
	ifstream fichierPays(filename + ".txt");
	Graphe* graphe{ new Graphe() };

	if (!fichierPays) {
		cout << "\nErreur, ce fichier n'existe pas\n";
		return nullptr;
	}

	string premierLigne;
	getline(fichierPays, premierLigne);
	istringstream inputpremierLigne(premierLigne);// operatation en strings
	string nomPays;

	cout << "\n";

	int i = 0;
	while (inputpremierLigne.eof() == 0) {
		i = i + 1;
		getline(inputpremierLigne, nomPays, ';');

		if (nomPays == "")
			break;

		graphe->insererSommet(nomPays);
	}

	string deuxiemeLigne;
	getline(fichierPays, deuxiemeLigne);
	istringstream input2eLigne(deuxiemeLigne);
	string SommetSource, SommetDestination;
	string frontiere;

	cout << endl << endl;
	while (input2eLigne.eof() == 0) {

		getline(input2eLigne, SommetSource, ',');
		getline(input2eLigne, SommetDestination, ',');
		getline(input2eLigne, frontiere, ';');

		if (SommetSource == "")
			break;

		graphe->insererArc(SommetSource, SommetDestination, stoi(frontiere));
		graphe->insererArc(SommetDestination, SommetSource, stoi(frontiere));
	}
	return graphe;
}

/*fonction qui affiche le graphe avec ou sans couleur sous le format (pays, couleur, voisin) et prend en paramètre un pointeur vers graphe*/
void lireGraphe(Graphe* graphe) {

	cout << "\nLisant le Graphe..." << endl;
	graphe->lireGraphe();
}
/*fonction qui determiner, a l’aide de l’algorithme de Dijkstra, le plus court chemin entre deux points dans un graphe
il prend en paramètre un graphe, le pays de départ et le pays de destination et affiche une erreur si le chemin ou les paramètres n'existe pas)
*/
void shortestPath(Graphe* graphe, const string& source, const string& target) {

	Graphe* newGraphe = graphe->dijkstra(source, target);

	if (newGraphe != nullptr) {

		cout << "\nDistance totale : " << newGraphe->getMinimalDistanceLength() << endl;
		// Printing the shortest path

/*	newGraphe->printShortestPath();*/
		for (auto pays : newGraphe->getpathDjikstra()) {
			if (pays != target) {
				cout << pays << "-->";
			}
			else {
				cout << pays;
			}
		}
		newGraphe->settonullpathDjikstra();
		delete newGraphe;
		return;

	}
	cout << "\n\n" << "Le chemin entre " << source << "et " << target << " n'existe pas" << endl;

}




// PARTIE AUTOMATE
// tp2810.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <time.h>

using namespace std;

vector<string> tableau_fichier1;

//Méthode qui demande de rentrer le bon option
void afficherMauvaisChoix() {
	cout << "Veuillez choisir les options 1 ou 2." << endl;
	cout << "Choix: ";
}

//Méthode qui compare deux strings et retourne true si c'est le meme mot ou il y a une difference en caractere sinon false 
bool compare(string str1, string str2) {
	bool c = false;
	for (int i = 0; i < str1.size(); ++i)
		if (str1[i] != str2[i])
			if (!c)
				c = true;
			else
				return false;
	return true;
}

//Methode qui va afficher le mot avec lequel on doit remplacer notre mot rentré au clavier qui possède une faute
bool corrigerLexique(string motUtilisateur) {


	bool suggestionFound = false;


	cout << "Suggestion(s) to replace word with lenght  " << motUtilisateur.size() << endl;
	//Tableau qui content les suggestions
	for (int i = 0; i < tableau_fichier1.size(); i++)
	{
		if (tableau_fichier1[i][0] == motUtilisateur[0] && tableau_fichier1[i].size() == motUtilisateur.size() && compare(tableau_fichier1[i], motUtilisateur))
		{
			suggestionFound = true;
			cout << tableau_fichier1[i] << endl;

		}
	}

	if (!suggestionFound) {
		cout << "Aucune...." << endl;
	}


	return suggestionFound;
}



//Methode qui va afficher les mots suggérer lorsqu'on a pas completer le mot 
bool creerLexique(string motUtilisateur) {

	// RESTE LEXQIQUE 2-3-4-5-6 

	bool suggestionFound = false;


	cout << "Suggestion(s) to complete word : " << endl;
	//Tableau qui content les suggestions
	for (int i = 0; i < tableau_fichier1.size(); i++)
	{
		if (tableau_fichier1[i].rfind(motUtilisateur, 0) == 0)
		{
			suggestionFound = true;
			cout << tableau_fichier1[i] << endl;

		}
	}

	if (!suggestionFound) {
		cout << "Aucune...." << endl;
	}


	return suggestionFound;

}



//Methode qui affiche le menu
int selectionMenu() {
	cout << endl << "MENU" << endl;
	cout << "1. CORRECTION" << endl;
	cout << "2. QUITTER" << endl;
	cout << "Choix: ";
	int choix;


	while (true)
	{
		cin >> choix;
		if (!cin)
		{
			afficherMauvaisChoix();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else break;
	}

	return choix;
}

//Methode qui anime le jeu 
int traitementCorrection() {

	string mot;
	string motUtilisateur;


	cout << "Choissisez votre lexique (chiffre 1 a 6):   " << endl;
	int nbLexique;
	cin >> nbLexique;

	string proposition;
	string secret;
	int reponse = 0;

	string nomFichier = "lexique" + std::to_string(nbLexique) + ".txt";
	ifstream fichier(nomFichier, ios::in);  // on ouvre le fichier en lecture

	bool fichierExistant = false;
	// instructions
   // throw new exception("Impossible d'ouvrir le fichier !"); // on envoie des erreurs
	for (size_t i = 1; i < 7; i++)
	{
		ifstream tempFichier("lexique" + std::to_string(nbLexique) + ".txt", ios::in);
		if (tempFichier) {
			fichierExistant = true;
		}
	}

	if (!fichierExistant) {
		cerr << "Impossible d'ouvrir au moins un fichier !" << endl;
	}


	if (fichierExistant)  // sinon
	{
		cout << "Lexique " << nbLexique << endl;
		while (getline(fichier, mot))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			tableau_fichier1.push_back(mot);//Ajout des mots dans le tableau
		   // cout << mot << endl;  // on l'affiche
		}

		do {
			cout << "> Quel mot ? " << endl;
			cout << "Reponse : ";

			cin >> motUtilisateur;

			bool trouve = false;
			for (int i = 0; i < tableau_fichier1.size(); i++)
			{
				if (tableau_fichier1[i] == motUtilisateur) {
					trouve = true;
					break;
				}
			}

			if (trouve)
			{
				cout << "Voulez-vous selectionner ce mot?  (1:oui/0:non)" << endl;
				cout << "Reponse pour selection :  ";
				cin >> reponse;
			}
			else {
				corrigerLexique(motUtilisateur);
				creerLexique(motUtilisateur);
			}

		} while (reponse != 1);
		cout << "Mot selectionne : " << motUtilisateur << endl;
		cout << "Le mot possede   " << motUtilisateur.size() << "  lettres" << endl;
	}

	return 0;
}


void SelectionJeuInstructf() {

	int choix = 0;
	do {
		choix = selectionMenu();
		switch (choix) {
		case 1:
			traitementCorrection();
			break;
		case 2:
			break;
		default:
			afficherMauvaisChoix();
		}
	} while (choix != 2);
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
