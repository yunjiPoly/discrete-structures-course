///////////////////////////////////////////////////////////////////////////////
/// @file Graph.cpp
/// @author Yun Ji Liao 2017113
/// @date 2021/06/06
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////


#pragma once
#include <memory>
#include <string>
#include "Sommet.h"
#include <vector>
#include <cmath>

class Graphe {
public:
	Graphe();
	~Graphe();
	void setGraphe(std::map<std::string, Sommet*> graphe) { graphe_ = graphe; }
	void insererSommet(const std::string&);
	void insererSommet(const std::string&, Sommet*);
	void insererArc(const std::string&, const std::string&, int);
	void lireGraphe() const;
	void colorer();
	bool exist(std::string nomPays);
	bool isColored() { return isColored(graphe_); };
	bool isNotReliedWitheSameColor(std::string couleur, Sommet sommet) const;
	Graphe* extractionGraphe(const std::string&);
	std::string plusCourtChemin(std::string départ, std::string arrivé, std::string paysAeviter);
	Graphe* dijkstra(const std::string&, const std::string&);
	int getNbSommet() { return graphe_.size(); };
	int getIndexSommet(const std::string&) const;
	void deleteArc(std::string);
	std::map<std::string, Sommet*> getGraphe() {
		return graphe_;
	}
	std::string getSommetNom(int index) const;
	inline	int getMinimalDistanceLength() const {

		return longeurMiniDistance_;
	}
	void printShortestPath() const;
	bool findPaysCouleur(const std::string&) const;
	std::vector<std::string> getpathDjikstra() { return pathDjikstra_; };
	void insertpathDjikstra(std::string pays) { pathDjikstra_.push_back(pays); };
	void settonullpathDjikstra() { pathDjikstra_ = {}; }
private:
	std::map<std::string, Sommet*> graphe_;
	int longeurMiniDistance_ = 0;
	std::vector<std::string> pathDjikstra_;
	std::map<std::string, Sommet*> colorerGraphe(std::map<std::string, Sommet*> lesSommets, std::vector<std::string> couleurs);
	std::vector<Sommet> ClasserSommet(std::vector<Sommet> sommets);
	Sommet findSommet(std::string sommet);
	Sommet findMaxDegree(std::vector<Sommet> sommets);
	int findIndexMaxDegree(std::vector<Sommet> sommets);
	bool isColored(std::map<std::string, Sommet*> graphe_);
	bool isInChemin(Sommet sommetRef, std::vector<std::string> chemin);
	std::vector<Sommet> createVectorFromGraphe(std::map<std::string, Sommet*> graphe);
	bool contains(std::vector<std::string> vecteur, std::string element) const;
	int getDistance(Sommet A, Sommet B);
	Sommet* findMinVoisin(Sommet sommet, std::vector<std::string> exept);
	std::map<std::string, Sommet> SetDistanceToInfinity(std::map<std::string, Sommet*> grapheRef);
	std::string plusCourtChemin(Sommet départ, Sommet arrivé, std::string paysAeviter);
	inline	void setMinimalDistanceLength(int distance) {

		longeurMiniDistance_ = distance;
	}
	Graphe* creerGrapheDijksta(std::vector<int>, const std::string&, const std::string&);

};