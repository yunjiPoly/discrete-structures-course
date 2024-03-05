//////////////////////////////////////////////////////////////////////
/// @file Graphe.cpp
/// @author Yun Ji Liao
/// @date 6/9/2021
/// @version 1.0
//////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphe.h"
#include<functional>
#include <queue>
#include <iostream>
#include<set>
#include <vector>
#include <cmath>
using namespace std;

////////////////////////////////////////////////////////////////////////
///
/// @fn Graphe::Graphe ()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Graphe::Graphe() {}

////////////////////////////////////////////////////////////////////////
///
/// @fn Graphe::~Graphe ()
///
/// Destructeur.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Graphe::~Graphe() {}

/// Insert un sommet dans le graphe en lui passant son nom de pays
void Graphe::insererSommet(const std::string& nom) {

	Sommet* sommet = { new Sommet(nom) };
	insererSommet(nom, sommet);
}
/// Insert un sommet dans le graphe en lui passant son nom et un sommet
///
void Graphe::insererSommet(const std::string& nom, Sommet* sommet) {

	graphe_.insert({ nom,sommet });
}

// inserer un nouveau arc pour un sommet
void Graphe::insererArc(const string& sommetS, const string& sommetD, int frontiere) {
	if (sommetS == sommetD) {
		return;
	}
	auto it = graphe_.find(sommetS);
	if (it == graphe_.end())
		return;

	it->second->insererArc(sommetD, frontiere);
}

// Affichage de la carte
void Graphe::lireGraphe() const {
	vector<string> sommet;
	int i = 0;
	for (auto& graphe : graphe_) {

		sommet = graphe.second->getSommet();

		cout << "( " << graphe.first + ", " << graphe.second->getCouleur() + ", (";
		for (auto& voisins : sommet) {

			++i;
			if (i > 1)
				cout << "; ";

			cout << voisins;
			auto it = graphe_.find(voisins);
			if (it != graphe_.end())
				cout << ", " + it->second->getCouleur();

		}

		cout << "))" << endl;
		i = 0;
	}
}

// Trouver l'index dans le graphe le sommet cherché
int Graphe::findIndexMaxDegree(vector<Sommet> sommets) {
	Sommet maxSommet = findMaxDegree(sommets);
	int index = 0;
	for (Sommet sommet : sommets) {
		if (sommet.isEqual(maxSommet)) {
			return index;
		}
		else if (index >= sommets.size()) {
			return -1;
		}
		index++;
	}
	return index;
}



// Trouver le degre d'un sommet
Sommet Graphe::findMaxDegree(std::vector<Sommet> sommets)
{
	Sommet maxSommet = sommets[0];
	for (Sommet sommet : sommets) {
		if (sommet.getDegrees() > maxSommet.getDegrees()) {
			maxSommet = sommet;
		}
	}
	return maxSommet;
}

//fonction qui prend l'attribut graphe_ du graphe et retourne une version vecteur de cela,  la map représentant graphe_
std::vector<Sommet> Graphe::createVectorFromGraphe(std::map<std::string, Sommet*> graphe) {
	vector<Sommet> sommetClassé = {};
	for (auto paireDesommet : graphe) {
		Sommet* sommmetAColorier = paireDesommet.second;
		sommetClassé.push_back(*sommmetAColorier);
	}
	return sommetClassé;
}

/*fonction qui retourne un vecteur de Graphe avec les sommets classé par ordre de degré decroissant
en prenant en paramètre un vecteur de sommet d'ordre quelconque*/
vector<Sommet> Graphe::ClasserSommet(vector<Sommet> sommets) {
	vector<Sommet> sommetsCopy = sommets;
	vector<Sommet> sommetClassé = {};
	while (!sommetsCopy.empty())
	{
		Sommet sommetMaxDegree = findMaxDegree(sommetsCopy);
		int indexMAx = findIndexMaxDegree(sommetsCopy);
		sommetsCopy.erase(sommetsCopy.begin() + indexMAx);
		sommetClassé.push_back(sommetMaxDegree);
	}
	return sommetClassé;
}

/*fonction qui verifie si un element str est contenu dans un vector de str en prenant les 2 en paramètre */
bool Graphe::contains(std::vector<std::string> vecteur, std::string element) const {
	for (std::string elementRef : vecteur) {
		if (elementRef == element) {
			return true;
		}
	}
	return false;
}


/*fonction qui verifie si un pays se trouve dans le graphe en passant en paramètre le nom du pays*/
bool Graphe::exist(std::string nomPays) {
	for (auto sommet : graphe_) {
		if (sommet.first == nomPays) {
			return true;
		}
	}
	return false;
}

/*fonction qui verifie si tout les sommets du graphe sont coloré en prenant en paramètre l'attribut privée graphe_de graphe*/
bool Graphe::isColored(std::map<std::string, Sommet*> graphe_) {
	for (auto graphe : graphe_) {
		if (graphe.second->getCouleur() == "neutre") {
			return false;
		}
	}
	return true;
}
/*fonction qui vérifie qu'un sommet A et ses voisins ne sont pas coloré d'un même couleur en prenant en paramètre le sommet A et la couleur*/
bool Graphe::isNotReliedWitheSameColor(std::string couleur, Sommet sommet) const {

	for (auto sommetDivers : graphe_) {
		if (sommetDivers.second->getCouleur() != "neutre") {
			if ((*sommetDivers.second).isNeighbor(sommet)) {
				if (sommetDivers.second->getCouleur() == couleur) {
					return false;
				}
			}
		}
	}
	return true;
}

/*fonction qui verifie si un pays se trouve dans le map du graphr */
bool Graphe::findPaysCouleur(const std::string& nomPays) const {
	/*auto search = graphe_.find(nomPays);

	if (search != graphe_.end())
		return true;
	return false;*/
	for (auto sommet : graphe_) {
		if (sommet.first == nomPays) {
			return true;
		}
	}
	return false;
}

/*fonction qui colore le graphe en suivant le théorème des 4 couleurs il prend en paramètre un vecteur qui contient
les 4 couleurs et un map contenant les sommets a colorier
*/

std::map<std::string, Sommet*> Graphe::colorerGraphe(std::map<std::string, Sommet*> lesSommets, std::vector<string> couleurs) {
	int indexCouleur = 0;

	vector<Sommet> sommetClassé = ClasserSommet(createVectorFromGraphe(graphe_));

	while (!isColored()) {
		string couleur = couleurs[indexCouleur];
		int indexSommets = 0;
		for (auto sommet : sommetClassé) {
			if (sommet.isNotColored()) {
				if (isNotReliedWitheSameColor(couleur, sommet)) {
					(*graphe_.find(sommet.getNom())).second->setCouleur(couleur);
					sommetClassé[indexSommets] = *(*graphe_.find(sommet.getNom())).second;
				}
			}
			indexSommets++;
		}
		indexCouleur++;
		indexSommets = 0;
		if (indexCouleur == 4) {
			indexCouleur = 0;
		}

	}
	return lesSommets;
}

/*fonction qui colorie le graphe*/
void Graphe::colorer() {

	vector<string> couleurs = { "rouge", "bleu", "vert", "jaune" };
	colorerGraphe(graphe_, couleurs);
}

// Trouve l'index du sommet dans le graphe
int Graphe::getIndexSommet(const string& sommet) const {
	int index = 0;
	for (auto& it : graphe_) {
		if (it.first == sommet)
			return index;
		index++;
	}
	return index;
}

// Retourner la distance entre 2 pays
int Graphe::getDistance(Sommet A, Sommet B) {
	int distance = -1;
	if (A.isNeighbor(B)) {
		for (auto sommet : A.getSommet_()) {
			if (sommet.first == B.getNom()) {
				distance = sommet.second->getDistance();
			}
		}
	}
	return distance;
}


/*fonction qui verifie si un sommet se trouve dans un vecteur de str contenant le nom des pays
et prend en paramètre le chemin et le sommet à verifier*/
bool Graphe::isInChemin(Sommet sommetRef, std::vector<std::string> chemin) {
	for (auto sommet : chemin) {
		if (sommet == sommetRef.getNom()) {
			return true;
		}
	}
	return false;
}


// Retourner le nom du sommet grace a l'index
string Graphe::getSommetNom(int index) const {

	int i = 0;
	for (auto& graph : graphe_) {
		if (i == index)
			return graph.first;

		++i;
	}

	return "";
}

// extraire le sous-graphe resultant d’un 
//graphe colore, auquel on veut retirer une certaine couleur passee en parametre
Graphe* Graphe::extractionGraphe(const std::string& couleur) {
	Graphe* newGraphe{ new Graphe };
	for (auto it = graphe_.begin(); it != graphe_.end();it++) {
		if (it->second->getCouleur() != couleur) {
			newGraphe->insererSommet(it->first, it->second);
		}

	}
	for (auto it = graphe_.begin(); it != graphe_.end();it++) {
		if (it->second->getCouleur() == couleur) {
			newGraphe->deleteArc(it->second->getNom());
		}
	}
	return newGraphe;

}

/*fonction qui supprime un arc*/
void Graphe::deleteArc(std::string nom) {
	for (auto it = graphe_.begin(); it != graphe_.end();it++) {
		it->second->deleteSommetAdj(nom);
	}

}

/*fonction qui affiche le plus court chemin*/
void Graphe::printShortestPath() const {

	vector<string> sommet;
	vector<string> tmp;

	for (auto& graphe : graphe_) {

		sommet = graphe.second->getSommet();


		if (sommet.size() > 0) {

			auto it = find(tmp.begin(), tmp.end(), graphe.first);

			if (it == tmp.end()) {
				cout << graphe.first;

			}
		}

		for (auto& neighbor : sommet) {

			cout << "-->" << neighbor;
			tmp.push_back(neighbor);
		}
	}

}
/// Cette methode utilise l'algorithme de dijstra pour determiner le
/// plus court chemin dans un graphe en lui passant le depart et la destination
/// en utilisant la technique de priority queue
Graphe* Graphe::dijkstra(const string& depart, const string& destination) {
	int nombre = getNbSommet();
	vector<int> distance(nombre, INT_MAX);
	vector<int> previous(nombre, -1);	// Previous node in optimal path from source
	vector<string> sommet;	// to hold all the vertices from the graphe
	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair <int, int> > > priorities;//ordre petit au top
	priorities.push({ 0, getIndexSommet(depart) });

	distance[getIndexSommet(depart)] = 0; //initalise le depart a 0

	while (!priorities.empty()) {

		int u = priorities.top().second;// u =  le plus gros pair

		// test permettant d'extraire le graphe resultant aussitot
		// quon arrive a la destination
		if (u == getIndexSommet(destination)) {
			//Graphe* newgraphe = { new Graphe(*this) };	

			Graphe* newGraphe = creerGrapheDijksta(previous, depart, destination);
			newGraphe->setMinimalDistanceLength(distance[u]);
			return newGraphe;

		}

		priorities.pop();

		// Parcourir le graphe
		for (auto& graphe : graphe_) {

			// geting all adjacent vertices of the current node
			sommet = graphe.second->getSommet();
			bool found = false;

			// If the current vertex in the graph
			// is our current 'u' node
			if (graphe.first == getSommetNom(u)) {

				found = true;
				// looping and working with all adjacent vertices of 'u'
				for (auto& voisin : sommet) {

					int v = getIndexSommet(voisin);	// get vertex index(label) of current adjacent of u
					int weight = 0;

					auto it = graphe_.find(getSommetNom(u));
					if (it != graphe_.end())
						weight = it->second->getDistanceArc(voisin);	// get vertex weight of current incident edge of u


					// if there is a shortest path from u to v
					if (distance[v] > distance[u] + weight) {

						// distance of v gets updated
						distance[v] = distance[u] + weight;
						previous[v] = u;	// by setting previous[v] we will remember what is the previous node on path from  the source
						priorities.push({ distance[v], v });
					}
				}
			}

			// if our current node already found in the graph 
			// then there's no need to check the other vertices
			if (found)
				break;

		}// end outter for loop

	} // end while

	return nullptr;

}


Graphe* Graphe::creerGrapheDijksta(vector<int> path, const string& source, const string& target) {

	/*Reading the shortest path from source to target by reverse iteration*/

	vector<int> tmpPath;
	int v = getIndexSommet(target);	// v take the index of the target position

	while (v != getIndexSommet(source)) {
		tmpPath.push_back(v);
		v = path[v];
	}

	tmpPath.push_back(getIndexSommet(source));
	reverse(tmpPath.begin(), tmpPath.end());



	Graphe* newGraphe{ new Graphe() };

	/// inserter les sommet a partir des index du vecteur chemin
	for (size_t i = 0; i < tmpPath.size(); ++i) {

		newGraphe->insererSommet(getSommetNom(tmpPath[i]));
		newGraphe->insertpathDjikstra(getSommetNom(tmpPath[i]));
	}

	/// inserer les arcs 
	vector<string> vertex;
	for (size_t i = 0; i < tmpPath.size(); ++i) {

		for (auto& graph : graphe_) {

			vertex = graph.second->getSommet();
			bool found = false;

			if (graph.first == getSommetNom(tmpPath[i])) {

				found = true;
				for (size_t j = 0; j < vertex.size() && j < tmpPath.size(); ++j) {

					// Find the current vertex in the old graph
					auto it = graphe_.find(getSommetNom(tmpPath[i]));
					int weight;

					if (it != graphe_.end()) { // found

						size_t k = j;
						if (++k < tmpPath.size()) {

							auto locate = find(vertex.begin(), vertex.end(), getSommetNom(tmpPath[k])); // locating vertex in the path in the
							if (locate != vertex.end()) { // found

								weight = it->second->getDistanceArc(*locate);	// find the distance between the current vertex and its adjacent vertex

								newGraphe->insererArc(getSommetNom(tmpPath[j]), *locate, weight);
							}

						}

					}

				} // end inner for loop
			}

			if (found)
				break;
		} // end outter for loop
	}

	return newGraphe;
}
