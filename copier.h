#include "Liste.h"
/**
   3.2.1 chercher une valeur dans une liste triée, nom de la fonction fonction : chercherTri
   @param premier : itérateur positionné sur le premier élément
   @param dernier : itérateur positionné après le dernier élément
   @param x : valeur à chercher
   @return position du premier élément de valeur >= x
   ou end() si un tel élément n'existe pas
 */
template<class T>
typename Liste<T>::iterator chercherTri(typename Liste<T>::iterator premier, typename Liste<T>::iterator dernier, T x) {
	while(premier != dernier && *premier < x) {
		++premier;
	}

	return premier;
}


/**
   3.2.2 créer une copie triée par valeurs croissantes d'une liste, nom de la fonction fonction : copierTri
   @param l : liste à copier
   @return liste triée
*/
template<class T>
Liste<T> * copierTri(Liste<T> & l) {
	Liste<T> * copieTriee = new Liste<T>();
	auto begin = l.begin();
	auto end = l.end();

	while(begin != end) {
		T valeur = *begin;
		copieTriee->insert(chercherTri(copieTriee->begin(), copieTriee->end(), valeur), valeur);
		++begin;
	}

	return copieTriee;
}
