/*
	INF3105 - Structures de données et algorithmes
	UQAM / Département d'informatique
	Automne 2019
*/

#include "inventaire.h"

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

std::istream& operator>>(std::istream& is, ListeIngredients& listeIngredients) {
	listeIngredients.arbreMap.vider();

	std::string chaine;
	is >> chaine;
	while (is && chaine != "---") {
		int quantite;
		is >> quantite;
		if (quantite > 0)
			listeIngredients.arbreMap[chaine] = quantite;
		is >> chaine;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const ListeIngredients& listeIngredients) {
	return os << listeIngredients.arbreMap;
}

Inventaire& Inventaire::operator+=(const Inventaire& autre) {
	for (ArbreMap<std::string, ArbreMap<Date, int>>::IterateurConst iter1 = autre.arbreMap.debutConst(); iter1; ++iter1) {
		for (ArbreMap<Date, int>::IterateurConst iter2 = iter1.valeur().debutConst(); iter2; ++iter2)
			this->arbreMap[iter1.cle()][iter2.cle()] += iter2.valeur();
	}
	return *this;
}

Inventaire& Inventaire::operator-=(const ListeIngredients& listeIngredients) { // ne pas mettre listeIngredients const
	ListeIngredients ingredients(listeIngredients);
	for (ArbreMap<std::string, int>::Iterateur iter1 = ingredients.arbreMap.debut(); iter1; ++iter1) {
		for (ArbreMap<Date, int>::Iterateur iter2 = this->arbreMap[iter1.cle()].debut(); iter2 && iter1.valeur() > 0; ++iter2) {
			if (iter2.valeur() != 0) {
				if (iter2.valeur() < iter1.valeur()) {
					iter1.valeur() -= iter2.valeur();
					iter2.valeur() = 0;
				}
				else {
					iter2.valeur() -= iter1.valeur();
					iter1.valeur() = 0;
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
		inventaire.arbreMap[chaine][expiration] += quantite;
		is >> chaine;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Inventaire& inventaire) {
	return os << inventaire.arbreMap;
}

bool Inventaire::ingredientsDisponibles(const ListeIngredients& ingredients) const {
	for (ArbreMap<std::string, int>::IterateurConst iter0 = ingredients.arbreMap.debutConst(); iter0; ++iter0) {
		int quantite = 0;
		if (!this->arbreMap.contient(iter0.cle()))
			return false;
		for (ArbreMap<Date, int>::IterateurConst iter2 = this->arbreMap[iter0.cle()].debutConst(); iter2 && quantite < iter0.valeur(); ++iter2)
			quantite += iter2.valeur();
		if (quantite < iter0.valeur())
			return false;
	}
	return true;
}

void Inventaire::liquiderProduitsPerimes(const Date& date) {
	for (ArbreMap<std::string, ArbreMap<Date, int>>::Iterateur iter = this->arbreMap.debut(); iter; ++iter) {
		for (ArbreMap<Date, int>::IterateurConst iter2 = iter.valeur().debutConst(); iter2 && iter2.cle() <= date; ++iter2)
			iter.valeur().enlever(iter2.cle());
	}
}
