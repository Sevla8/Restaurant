/*
	INF3105 - Structures de données et algorithmes
	UQAM / Département d'informatique
	Automne 2019
*/

#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

Date::Date() {}

bool Date::operator<(const Date& date) const {
	if (this->jour < date.jour)
		return true;
	if (this->jour > date.jour)
		return false;
	if (this->heure < date.heure)
		return true;
	if (this->heure > date.heure)
		return false;
	if (this->minute < date.minute)
		return true;
	if (this->minute > date.minute)
		return false;
	return false;
}

bool Date::operator<=(const Date& date) const {
	if (this->jour < date.jour)
		return true;
	if (this->jour > date.jour)
		return false;
	if (this->heure < date.heure)
		return true;
	if (this->heure > date.heure)
		return false;
	if (this->minute < date.minute)
		return true;
	if (this->minute > date.minute)
		return false;
	return true;
}

bool Date::operator>(const Date& date) const {
	return *this >= date && *this != date;
}

bool Date::operator>=(const Date& date) const {
	return !(*this < date);
}

bool Date::operator==(const Date& date) const {
	return *this <= date && *this >= date;
}

bool Date::operator!=(const Date& date) const {
	return !(*this == date);
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
	char chaine[10];
	sprintf(chaine, "%dj_%02dh%02dm", date.jour, date.heure, date.minute);
	os << chaine;
	return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
	char j, m, h, underscore;
	is >> date.jour >> j >> underscore >> date.heure >> h >> date.minute >> m;
	assert(j == 'j' && underscore == '_' && h == 'h' && m == 'm');
	return is;
}

Intervalle::Intervalle() {}

Date Intervalle::getDebut() const {
	return this->debut;
}

Date Intervalle::getFin() const {
	return this->fin;
}

std::ostream& operator<<(std::ostream& os, const Intervalle& inter) {
	os << inter.debut << inter.fin;
	return os;
}

std::istream& operator>>(std::istream& is, Intervalle& inter) {
	char crochetgauche, crochetdroit, virgule;
	is >> crochetgauche >> inter.debut >> virgule >> inter.fin >> crochetdroit;
	assert(crochetgauche == '[' && virgule == ',' && crochetdroit == ']');
	return is;
}
