/*
	INF3105 - Structures de données et algorithmes
	UQAM / Département d'informatique
	Automne 2019
*/

#ifndef _DATE__H_
#define _DATE__H_

#include <iostream>

class Date {
	public:
		Date();
		bool operator<(const Date&) const;
		bool operator<=(const Date&) const;
		bool operator>(const Date&) const;
		bool operator>=(const Date&) const;
		bool operator==(const Date&) const;
		bool operator!=(const Date&) const;
	private:
		int jour;
		int heure;
		int minute;
	friend std::ostream& operator<<(std::ostream&, const Date&);
	friend std::istream& operator>>(std::istream&, Date&);
};

class Intervalle {
	public:
		Intervalle();
		Date getDebut() const;
		Date getFin() const;
	private:
		Date debut;
		Date fin;
	friend std::ostream& operator<<(std::ostream&, const Intervalle&);
	friend std::istream& operator>>(std::istream&, Intervalle&);
};

#endif
