/*
	INF3105 - Structures de données et algorithmes
	UQAM / Département d'informatique
	Automne 2019
*/

#ifndef _INVENTAIRE__H_
#define _INVENTAIRE__H_

#include <iostream>
#include "date.h"
#include "STRUCT/arbremap.h"

class ListeIngredients {
	public:
		ListeIngredients& operator+=(const ListeIngredients&);
		ListeIngredients& operator*=(int);
	private:
		ArbreMap<std::string, int> arbreMap;
	friend std::istream& operator>>(std::istream&, ListeIngredients&);
	friend std::ostream& operator<<(std::ostream&, const ListeIngredients&);
	friend class Inventaire;
};

class Inventaire {
	public:
		Inventaire& operator+=(const Inventaire&);
		Inventaire& operator-=(const ListeIngredients&);
		bool ingredientsDisponibles(const ListeIngredients&) const;
		void liquiderProduitsPerimes(const Date&);
	private:
		ArbreMap<std::string, ArbreMap<Date, int>> arbreMap;
	friend std::istream& operator>>(std::istream&, Inventaire&);
	friend std::ostream& operator<<(std::ostream&, const Inventaire&);
};

#endif
