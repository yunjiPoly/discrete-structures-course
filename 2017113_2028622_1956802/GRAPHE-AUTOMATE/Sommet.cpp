//////////////////////////////////////////////////////////////////////
/// @file Pays.h
/// @author Yun Ji Liao
/// @date 6/9/2021
/// @version 1.0
//////////////////////////////////////////////////////////////////////
#include "Sommet.h"
using namespace std;
/*fonction qui modifie le nom du pays de la sommet*/
void Sommet::setSommet(const std::string& nomPays) {
	nom_ = nomPays;
}

/*fonction créateur*/
Sommet::Sommet(const string& nom) : nom_(nom) {}

/*destructeur*/
Sommet::~Sommet() {}

/*fonction qui ajoute un arc voisin au sommet en prenant en paramètre le nom du pays voisin et la distance*/
void Sommet::insererArc(const std::string& destination, int frontiere) {
	Arc* arc{ new Arc(frontiere) };
	sommet_.insert({ destination, arc });
}

/*fonction qui retourne les voisins du sommets*/
vector<string> Sommet::getSommet() const {

	std::vector<string> sommet;
	for (auto& temp : sommet_)
		sommet.push_back(temp.first);

	return sommet;
}

/*fonction qui retourne le degree d'un sommet*/
int Sommet::getDegrees() const {
	int nbrArc = 0;
	for (auto Arc : sommet_) {
		nbrArc++;
	}
	return nbrArc;
}

/*fonction qui retourne la couleur*/
std::string Sommet::getCouleur() const {
	return couleur_;
}

/*fonction qui verifie l'égalité entre deux sommet*/
bool Sommet::isEqual(Sommet sommet) const {
	if (sommet.getCouleur() == getCouleur() && getDegrees() == sommet.getDegrees() && sommet.getNom() == getNom()) {

		return true;
	}
	return false;
}

/*fonction qui verifie si un sommet n'est pas coloré*/
bool Sommet::isNotColored() const {
	return couleur_ == "neutre";
}

/*fonction qui verifie si un sommet A passé en paramètre est voisin de this*/
bool Sommet::isNeighbor(Sommet sommet) const {
	for (auto neighbor : sommet_) {
		if (neighbor.first == sommet.getNom()) {
			return true;
		}
	}
	return false;
}

/*fonction qui retourne l'attribut privée sommet _ représentant les voisins*/
std::map<string, Arc*> Sommet::getAdj() const {

	return sommet_;
}

/*fonction qui supprime un voisin en prenant en paramètre le nom du voisin*/
void Sommet::deleteSommetAdj(std::string nom) {
	for (auto it = sommet_.begin();it != sommet_.end();) {
		if (it->first == nom)
			it = sommet_.erase(it);
		else
			++it;
	}
}

/*fonction qui retourne la distance entre thijs et le sommet voisin en prenant en paramètre le sommet voisin*/
int Sommet::getDistanceArc(const string& sommet) const {

	for (auto& value : sommet_)
		if (value.first == sommet)
			return value.second->getDistance();

	return 0;

}

/*fonction qui retourne le nom du voisin à l'index index passé en paramètre*/
std::string Sommet::getNomAdj(int index) const {
	int i = 0;
	for (auto& temp : sommet_) {
		if (i == index)
			return temp.first;

		++i;
	}

	return "";
}
