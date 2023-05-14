#include <iostream>
#include "Liste.h"

using namespace std;
int main() {

	Liste<double> liste;

	liste.push_front(1);
	liste.afficherListe();

	liste.push_front(2);
	liste.afficherListe();

	liste.push_front(3);
	liste.afficherListe();

	liste.push_back(4);
	liste.afficherListe();

	liste.pop_front();
	liste.afficherListe();

	liste.pop_back();
	liste.afficherListe();

	Liste<double> copie(liste);
	copie.afficherListe();


	return 0 ;

};
