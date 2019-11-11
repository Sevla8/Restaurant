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
	for (ArbreMap<std::string, ArbreMap<Date, int>>::IterateurConst iter = autre.arbreMap.debutConst(); iter; ++iter) {
		for (ArbreMap<Date, int>::IterateurConst iter2 = iter.valeur().debutConst(); iter2; ++iter2)
			this->arbreMap[iter.cle()][iter2.cle()] += iter2.valeur();
	}
	return *this;
}

Inventaire& Inventaire::operator-=(const ListeIngredients& listeIngredients) {
	ListeIngredients ingredients(listeIngredients);
	for (ArbreMap<std::string, ArbreMap<Date, int>>::Iterateur iter1 = this->arbreMap.debut(); iter1; ++iter1) {
		for (ArbreMap<Date, int>::Iterateur iter2 = iter1.valeur().debut(); iter2; ++iter2) {
			for (ArbreMap<std::string, int>::Iterateur iter3 = ingredients.arbreMap.debut(); iter3; ++iter3) {
				if (iter3.valeur() != 0 && iter3.cle() == iter1.cle()) {
					int valeurInventaire = iter2.valeur();
					if (valeurInventaire != 0) {
						if (valeurInventaire < iter3.valeur()) {
							iter2.valeur() = 0;
							iter3.valeur() -= valeurInventaire;
						}
						else {
							iter2.valeur() -= iter3.valeur();
							iter3.valeur() = 0;
						}
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
		inventaire.arbreMap[chaine][expiration] += quantite;
		is >> chaine;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Inventaire& inventaire) {
	return os << inventaire.arbreMap;
}

void Inventaire::listeIngredientsDisponibles(ListeIngredients& ingredients) const {
	for (ArbreMap<std::string, ArbreMap<Date, int>>::IterateurConst iter1 = this->arbreMap.debutConst(); iter1; ++iter1) {
		for (ArbreMap<Date, int>::IterateurConst iter2 = iter1.valeur().debutConst(); iter2; ++iter2)
			ingredients.arbreMap[iter1.cle()] += iter2.valeur();
	}
}

void Inventaire::liquiderProduitsPerimes(const Date& date) {
	for (ArbreMap<std::string, ArbreMap<Date, int>>::Iterateur iter1 = this->arbreMap.debut(); iter1; ++iter1) {
		for (ArbreMap<Date, int>::Iterateur iter2 = iter1.valeur().debut(); iter2; ++iter2) {
			if (iter2.cle() <= date)
				iter2.valeur() = 0;
			else
				break;
		}
	}
}
