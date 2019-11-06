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
		ListeIngredients();
		ListeIngredients(std::string, int);
		ListeIngredients& operator+=(const ListeIngredients&);
		ListeIngredients& operator*=(int);
		bool inclu(const ListeIngredients&) const;
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
		void listeIngredientsDisponibles(ListeIngredients&) const;
		void liquiderProduitsPerimes(const Date&);
	private:
		ArbreMap<Date, ListeIngredients> arbreMap;
	friend std::istream& operator>>(std::istream&, Inventaire&);
	friend std::ostream& operator<<(std::ostream&, const Inventaire&);
};

#endif
