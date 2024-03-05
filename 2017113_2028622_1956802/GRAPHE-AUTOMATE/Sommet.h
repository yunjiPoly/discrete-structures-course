//////////////////////////////////////////////////////////////////////
/// @file Pays.h
/// @author Yun Ji Liao
/// @date 6/9/2021
/// @version 1.0
//////////////////////////////////////////////////////////////////////
#pragma once
#ifndef __SOMMET_H

#include <string>
#include <map>
#include <vector>
#include "Arc.h"
#include <map>
class Sommet {
public:
	Sommet(const std::string&);
	~Sommet();
	void insererArc(const std::string&, int);
	void setSommet(const std::string&);
	void setCouleur(std::string couleur) { couleur_ = couleur; }
	std::string getNom() const { return nom_; };
	std::map<std::string, Arc*> getSommet_()const { return sommet_; };
	std::string getCouleur() const;
	std::vector<std::string> getSommet() const;
	bool isNotColored() const;
	int getDegrees()const;
	bool isEqual(Sommet sommet) const;
	bool isNeighbor(Sommet sommet) const;
	std::map<std::string, Arc*> getAdj() const;
	void deleteSommetAdj(std::string);
	int getDistanceArc(const std::string& t) const;
	std::string getNomAdj(int index) const;
private:
	std::string nom_;
	std::string couleur_ = "neutre";
	std::map<std::string, Arc*> sommet_;
};
#endif // __SOMMET_H

