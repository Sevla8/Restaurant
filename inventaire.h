/*
	INF3105 - Structures de données et algorithmes
	UQAM / Département d'informatique
	Automne 2019
*/

#ifndef _INVENTAIRE__H_
#define _INVENTAIRE__H_

#include <iostream>
#include "date.h"
#include "MY/arbremap.h"

class ListeIngredients {
	public:
		ListeIngredients();
		ListeIngredients(std::string, int);
		ListeIngredients& operator+=(const ListeIngredients&);
		ListeIngredients& operator*=(int);
		bool inclu(const ListeIngredients&) const;
	private:
		ArbreMap<std::string, int> arbreMap;
	friend std::istream& operator>>(std::istream&, ListeIngredients&);
	friend std::ostream& operator<<(std::ostream&, ListeIngredients&);
	friend class Inventaire;
};

class Inventaire {
	public:
		Inventaire& operator+=(const Inventaire&);
		Inventaire& operator-=(const ListeIngredients&);
		ListeIngredients listeIngredientsDisponibles() const;
		void liquiderProduitsPerimes(Date&);
	private:
		ArbreMap<Date, ListeIngredients> arbreMap;
	friend std::istream& operator>>(std::istream&, Inventaire&);
	friend std::ostream& operator<<(std::ostream&, Inventaire&);
};

#endif
