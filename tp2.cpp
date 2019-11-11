/*
	INF3105 - Structures de données et algorithmes
	UQAM / Département d'informatique
	Automne 2019
*/

#include <fstream>
#include "inventaire.h"

int tp2(std::istream& entree) {
	ArbreMap<std::string, ListeIngredients> livreRecettes;
	Inventaire inventaire;

	int noCommande = 0;
	Date date;

	while (entree) {
		std::string commande;
		entree >> commande;
		if (!entree)
			break;
		if (commande == "recette") {
			std::string nomRecette;
			entree >> nomRecette;
			ListeIngredients ingredients;
			entree >> ingredients;
			livreRecettes[nomRecette] = ingredients;
			//
			// std::cout << livreRecettes << std::endl;
			//
		}
		else if (commande == "reception") {
			Date date_reception;
			entree >> date_reception;
			// if (date_reception <= date)
			// 	std::cout << "Attention : ce programme supporte uniquement un ordre chronologique (voir section 3.6 / hypothèse 3)!" << std::endl;
			date = date_reception;

			Inventaire inventaireRecu;
			entree >> inventaireRecu;
			inventaire += inventaireRecu;
			//
			std::cout << inventaire << std::endl;
			//
		}
		else if (commande == "reservation") {
			Date date_preparation;
			entree >> date_preparation;
			// if (date_preparation <= date)
			// 	std::cout << "Attention : ce programme supporte uniquement un ordre chronologique (voir section 3.6 / hypothèse 3)!" << std::endl;
			date = date_preparation;

			ListeIngredients ingredientsRequis;
			std::string nomRecette;
			entree >> nomRecette;
			while (entree && nomRecette != "---") {
				int quantite;
				entree >> quantite;
				ListeIngredients tmp = livreRecettes[nomRecette];
				tmp *= quantite;
				ingredientsRequis += tmp;
				entree >> nomRecette;
			}
			//
			// std::cout << ingredientsRequis << std::endl;
			//
			inventaire.liquiderProduitsPerimes(date);
			ListeIngredients ingredientsDisponibles;
			inventaire.listeIngredientsDisponibles(ingredientsDisponibles);
			//
			// std::cout << ingredientsDisponibles << std::endl;
			//
			if (ingredientsRequis.inclu(ingredientsDisponibles)) {
				inventaire -= ingredientsRequis;
				std::cout << noCommande << " : OK" << std::endl;
			}
			else
				std::cout << noCommande << " : Echec" << std::endl;
			noCommande++;
			//
			// std::cout << in⎄/ntaire << std::endl;
			//
		}
		else {
			std::cout << "Commande '" << commande << "' inconnue!" << std::endl;
			return 2;
		}
	}
	return 0;
}

int main(int argc, const char** argv) {
	if (argc > 1) {
		std::ifstream entree_fichier(argv[1]);
		if (entree_fichier.fail()) {
			std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
			return 1;
		}
		return tp2(entree_fichier);
	}
	else
		return tp2(std::cin);
}
