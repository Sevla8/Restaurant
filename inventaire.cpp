/*
	INF3105 - Structures de données et algorithmes
	UQAM / Département d'informatique
	Automne 2019
*/

#include "inventaire.h"

ListeIngredients::ListeIngredients() {}

ListeIngredients::ListeIngredients(std::string ingredient, int quantite) {
	this->arbreMap[ingredient] = quantite;
}

ListeIngredients& ListeIngredients::operator+=(const ListeIngredients& autre) {
	for (ArbreMap<std::string, int>::IterateurConst iter = autre.arbreMap.debutConst(); iter; ++iter) {
		this->arbreMap[iter.cle()] += iter.valeur();
	}
	return *this;
}

ListeIngredients& ListeIngredients::operator*=(int facteur) {
	for (ArbreMap<std::string, int>::Iterateur iter = this->arbreMap.debut(); iter; ++iter) {
		iter.valeur() *= facteur;
	}
	return *this;
}

bool ListeIngredients::inclu(const ListeIngredients& autre) const {
	for (ArbreMap<std::string, int>::IterateurConst iter = this->arbreMap.debutConst(); iter; ++iter) {
		if (!autre.arbreMap.contient(iter.cle()))
			return false;
		if (iter.valeur() > autre.arbreMap[iter.cle()])
			return false;
	}
	return true;
}

std::istream& operator>>(std::istream& is, ListeIngredients& listeIngredients) {
	listeIngredients.arbreMap.vider();

	std::string chaine;
	is >> chaine;
	while (is && chaine != "---") {
		int quantite;
		is >> quantite;
		listeIngredients.arbreMap[chaine] = quantite;
		is >> chaine;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const ListeIngredients& listeIngredients) {
	return os << listeIngredients.arbreMap;
}

Inventaire& Inventaire::operator+=(const Inventaire& autre) {
	for (ArbreMap<Date, ListeIngredients>::IterateurConst iter = autre.arbreMap.debutConst(); iter; ++iter)
		this->arbreMap[iter.cle()] += iter.valeur();
	return *this;
}

Inventaire& Inventaire::operator-=(const ListeIngredients& listeIngredients) {
	ListeIngredients ingredients(listeIngredients);
	for (ArbreMap<Date, ListeIngredients>::Iterateur iter1 = this->arbreMap.debut(); iter1; ++iter1) {
		for (ArbreMap<std::string, int>::Iterateur iter2 = ingredients.arbreMap.debut(); iter2; ++iter2) {
			if (iter2.valeur() != 0) {
				int valeurInventaire = iter1.valeur().arbreMap[iter2.cle()];
				if (valeurInventaire != 0) {
					if (valeurInventaire < iter2.valeur()) {
						iter1.valeur().arbreMap[iter2.cle()] = 0;
						iter2.valeur() -= valeurInventaire;
					}
					else {
						iter1.valeur().arbreMap[iter2.cle()] -= iter2.valeur();
						iter2.valeur() = 0;
					}
				}
			}
		}
	}
	return *this;
}

std::istream& operator>>(std::istream& is, Inventaire& inventaire) {
	inventaire.arbreMap.vider();

	std::string chaine;
	is >> chaine;
	while (is && chaine != "---") {
		int quantite;
		Date expiration;
		is >> quantite >> expiration;
		ListeIngredients listeIngredients(chaine, quantite);
		inventaire.arbreMap[expiration] += listeIngredients;
		is >> chaine;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Inventaire& inventaire) {
	return os << inventaire.arbreMap;
}

void Inventaire::listeIngredientsDisponibles(ListeIngredients& ingredients) const {
	for (ArbreMap<Date, ListeIngredients>::IterateurConst iter = this->arbreMap.debutConst(); iter; ++iter) {
		ingredients += iter.valeur();
	}
}

void Inventaire::liquiderProduitsPerimes(const Date& date) {
	for (ArbreMap<Date, ListeIngredients>::Iterateur iter = this->arbreMap.debut(); iter; ++iter) {
		if (iter.cle() <= date)
			this->arbreMap.enlever(iter.cle());
		else
			break;
	}
}
