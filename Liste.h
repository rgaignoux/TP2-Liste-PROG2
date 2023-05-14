#ifndef LISTE_LISTE_H_
#define LISTE_LISTE_H_
#include "cyclicNode.h"
#include <cassert>
#include <iostream>

template<class T>
class Liste {

protected:
	typedef DataStructure::cyclicNode<T> Chainon;
	Chainon *sentinelle;
	int liste_size;

public:
	/**
	 * Constructeur par défaut
	 */
	Liste() {
		sentinelle = new Chainon();
		liste_size = 0;
	}

	/**
	 * Constructeur de copie
	 *
	 * @param l la liste à copier
	 */
	Liste(const Liste &l) {
		copierListe(l);
	}

	/**
	 * Afficher les chainons de la liste
	 */
	void afficherListe() {
		std::cout << "Noeuds de la liste : " << std::endl;

		iterator courant = begin();
		while (courant != end()) {
			std::cout << *courant << " ";
			++courant;
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}

	/**
	 * Copier une liste donnée dans la liste courante
	 *
	 * @param l la liste à copier
	 */
	void copierListe(const Liste &l) {
		sentinelle = new Chainon();

		const_iterator courant = l.begin();

		while (courant != l.end()) {
			push_back(*courant); // copier dans le même ordre
			++courant;
		}

		liste_size = l.liste_size;
	}

	/**
	 * Opérateur d'affectation
	 *
	 * @param l la liste à affecter à la liste courante
	 */
	Liste& operator=(const Liste &l) {
		// si la liste est differente de la liste courante, on détruit les chainons contenus dans la liste courante et on copie la nouvelle liste dans la liste courante
		if (this != &l) {
			if (!empty()) {
				while (!empty()) {
					pop_back();
				}
			}
			copierListe(l);
		}

		return (*this);
	}

	/**
	 * Opérateur de concanténation
	 *
	 * @param l la liste à concatener
	 * @return this + l
	 */
	Liste& operator+(const Liste &l) {
		const_iterator courant = l.begin();
		while (courant != l.end()) {
			push_back(*courant);
			++courant;
		}

		return (*this);
	}

	/**
	 * Destructeur
	 */
	~Liste() {
		while (!empty()) {
			pop_back();
		}
		delete sentinelle;
	}

	/**
	 * Indique si la liste est vide ou non
	 */
	bool empty() const {
		return liste_size == 0;
	}

	/**
	 * Indique la taille de la liste
	 */
	int size() const {
		return liste_size;
	}

	/**
	 * Renvoie la valeur en tête de liste (non modifiable)
	 */
	T& front() const {
		assert(!empty());
		return sentinelle->next()->data();
	}

	/**
	 * Renvoie la valeur en tête de liste (modifiable)
	 */
	T& front() {
		assert(!empty());
		return sentinelle->next()->data();
	}

	/**
	 * Renvoie la valeur en fin de liste (non modifiable)
	 */
	T& back() const {
		assert(!empty());
		return sentinelle->previous()->data();
	}

	/**
	 * Renvoie la valeur en fin de liste (modifiable)
	 */
	T& back() {
		assert(!empty());
		return sentinelle->previous()->data();
	}

	/**
	 * Inserer un élément en tête de liste
	 *
	 * @param t l'élément à inserer
	 */
	void push_front(T t) {
		Chainon *nouvelle_tete = new Chainon(t);
		sentinelle->insertAfter(nouvelle_tete);
		liste_size++;
	}

	/**
	 * Inserer un élément en fin de liste
	 *
	 * @param l'élément à inserer
	 */
	void push_back(T t) {
		Chainon *nouvelle_fin = new Chainon(t);
		sentinelle->insertBefore(nouvelle_fin);
		liste_size++;
	}

	/**
	 * Supprimer l'élément en tête de liste
	 *
	 * @param l'élément à supprimer
	 */
	void pop_front() {
		assert(!empty());
		Chainon *tete = sentinelle->next();
		Chainon *nouvelle_tete = tete->next();
		delete tete; // on détache le noeud de début
		sentinelle->insertAfter(nouvelle_tete);
		liste_size--;

	}

	/**
	 * Supprimmer l'élément en fin de liste
	 *
	 * @param l'élément à supprimer
	 */
	void pop_back() {
		assert(!empty());
		Chainon *fin = sentinelle->previous();
		Chainon *nouvelle_fin = fin->previous();
		delete fin; // on détache le noeud de fin
		sentinelle->insertBefore(nouvelle_fin);
		liste_size--;
	}

	class const_iterator {
	private:
		friend class Liste;

	protected:
		typedef DataStructure::cyclicNode<T> Chainon;
		Chainon *courant;
		Chainon *sentinelle;

		const_iterator(Chainon *c, Chainon *s) {
			courant = c;
			sentinelle = s;
		}

	public:

		~const_iterator() {
		}

		/**
		 * opérateur ++ préfixé
		 * positionne l'itérateur sur l'élément suivant
		 * @pre l'itérateur désigne une position valide dans la liste (=/=end())
		 * @return nouvelle valeur de l'itérateur
		 */
		const_iterator& operator ++() {
			assert(sentinelle != courant);
			courant = courant->next();
			return (*this);
		}

		/**
		 * opérateur −− préfixé
		 * positionne l'itérateur sur l'élément précédent
		 * @pre l'itérateur ne désigne pas l'élément de tête (=/=begin())
		 * @return nouvelle valeur de l'itérateur
		 */
		const_iterator& operator --() {
			assert(sentinelle->next() != courant);
			courant = courant->previous();
			return (*this);
		}

		/**
		 * opérateur d'indirection ∗ (accès NON modifiable)
		 * @pre l'itérateur désigne une position valide dans la liste (=/=end())
		 * @return valeur de l'élément désigné par l'itérateur
		 */
		const T& operator *() const {
			assert(sentinelle != courant);
			return courant->data();
		}

		/**
		 * opérateur d'indirection −> (accès NON modifiable)
		 * @pre l'itérateur désigne une position valide (=/=end())
		 * @return adresse de l'élément désigné par l'itérateur
		 */
		const T* operator ->() const {
			assert(sentinelle != courant);
			return &(courant->data());
		}

		/**
		 * opérateur d'égalité =
		 * @param it un itérateur
		 * @return true si l'itérateur `it` est égal à this
		 */
		const bool operator ==(const const_iterator &it) const {
			const bool eq = this->courant == it.courant
					&& this->sentinelle == it.sentinelle;
			return eq;
		}

		/**
		 * opérateur d'inégalité !=
		 * @param it un itérateur
		 * @return true si l'itérateur `it` n'est égal à this
		 */
		const bool operator !=(const const_iterator &it) const {
			const bool noteq = this->courant != it.courant
					|| this->sentinelle != it.sentinelle;
			return noteq;
		}

	};

	class iterator {
	private:
		friend class Liste;

	protected:
		typedef DataStructure::cyclicNode<T> Chainon;
		Chainon *courant;
		Chainon *sentinelle;

		iterator(Chainon *c, Chainon *s) {
			courant = c;
			sentinelle = s;
		}

	public:

		~iterator() {
		}

		/**
		 * opérateur ++ préfixé
		 * positionne l'itérateur sur l'élément suivant
		 * @pre l'itérateur désigne une position valide dans la liste (=/=end())
		 * @return nouvelle valeur de l'itérateur
		 */
		iterator& operator ++() {
			assert(sentinelle != courant);
			courant = courant->next();
			return (*this);
		}

		/**
		 * opérateur −− préfixé
		 * positionne l'itérateur sur l'élément précédent
		 * @pre l'itérateur ne désigne pas l'élément de tête (=/=begin())
		 * @return nouvelle valeur de l'itérateur
		 */
		iterator& operator --() {
			assert(sentinelle->next() != courant);
			courant = courant->previous();
			return (*this);
		}

		/**
		 * opérateur d'indirection ∗ (accès MODIFIABLE)
		 * @pre l'itérateur désigne une position valide dans la liste (=/=end())
		 * @return valeur de l'élément désigné par l'itérateur
		 */
		T& operator *() const {
			assert(sentinelle != courant);
			return courant->data();
		}

		/**
		 * opérateur d'indirection −> (accès MODIFIABLE)
		 * @pre l'itérateur désigne une position valide (=/=end())
		 * @return adresse de l'élément désigné par l'itérateur
		 */
		T* operator ->() const {
			assert(sentinelle != courant);
			return &(courant->data());
		}

		/**
		 * opérateur d'égalité =
		 * @param it un itérateur
		 * @return true si l'itérateur `it` est égal à this
		 */
		const bool operator ==(const iterator &it) const {
			const bool eq = this->courant == it.courant
					&& this->sentinelle == it.sentinelle;
			return eq;
		}

		/**
		 * opérateur d'inégalité !=
		 * @param it un itérateur
		 * @return true si l'itérateur `it` n'est égal à this
		 */
		const bool operator !=(const iterator &it) const {
			const bool noteq = this->courant != it.courant
					|| this->sentinelle != it.sentinelle;
			return noteq;
		}

	};

	/** renvoie un const_iterator qui désigne une position située après le dernier élément
	 */
	const_iterator end() const {
		return const_iterator(sentinelle, sentinelle);
	}

	/**
	 * renvoie un const_iterator sur le début de liste
	 * cet itérateur désigne le premier élément de la liste si elle n'est pas vide;
	 * sinon, il désigne la même position que l'itérateur renvoyé par end()
	 */
	const_iterator begin() const {
		if (empty())
			return const_iterator(sentinelle, sentinelle);
		return const_iterator(sentinelle->next(), sentinelle);
	}

	/** renvoie un itérateur qui désigne une position située après le dernier élément
	 */
	iterator end() {
		return iterator(sentinelle, sentinelle);
	}

	/**Chainon *sentinelle_l = l.sentinelle;
	 Chainon *courant = sentinelle_l->next();

	 while (courant != sentinelle_l) {
	 push_back(courant->data()); // copier dans le même ordre
	 courant = courant->next();
	 }
	 * renvoie un itérateur sur le début de liste
	 * cet itérateur désigne le premier élément de la liste si elle n'est pas vide;
	 * sinon, il désigne la même position que l'itérateur renvoyé par end()
	 */
	iterator begin() {
		if (empty())
			return iterator(sentinelle, sentinelle);
		return iterator(sentinelle->next(), sentinelle);
	}

	/**
	 * insère un nouvel élément, dont la valeur est donnée en paramètre,
	 * avant l'élément désigné par l'itérateur donné en paramètre
	 * si l'itérateur vaut end(), l'ajout se fait en fin de liste
	 *
	 * @param position un itérateur
	 * @param T x la valeur à inserer
	 * @return un iterateur sur l'élément inséré
	 */
	iterator insert(iterator position, const T &x) {
		assert(position.sentinelle == sentinelle);

		Chainon *node_to_insert = new Chainon(x);
		Chainon *current_node = position.courant;

		current_node->insertBefore(node_to_insert);
		liste_size++;

		return --position;
	}

	/**
	 * supprime l'élément désigné (qu'on suppose exister) par l'itérateur passé en paramètre
	 *
	 * @param iterateur position de l'élément à supprimer
	 * @return itérateur qui désigne l'élément qui suit celui supprimé
	 */
	iterator erase(iterator position) {
		assert(position.sentinelle == sentinelle);
		assert(position.courant != position.sentinelle);
		assert(!empty());

		iterator suivant(position.courant->next(), position.sentinelle);
		delete position.courant;
		liste_size--;
		return suivant;
	}
};

/**
 * chercher un élément dans la séquence [premier, dernier[
 *
 * @param premier : début de la séquence
 * @param dernier : fin de la séquence
 * @param x : valeur cherchée
 * @return itérateur qui désigne x s'il est trouvé; cet itérateur est égal à dernier si x est absent
 */
template<class InputIterator, class T>
InputIterator find(InputIterator premier, InputIterator dernier, const T &x) {

	while (premier != dernier) {
		if (*premier == x) {
			return premier;
		}
		++premier;
	}

	return dernier;
}

/**
 * Opérateur d'affichage
 *
 * @param out le flux de sortie
 */
template<class T>
std::ostream& operator<<(std::ostream &out, Liste<T> &l) {
	out << "<";

	typename Liste<T>::iterator courant = l.begin();
	while (courant != l.end()) {
		out << *courant << " ";
		++courant;
	}

	out << ">";

	return out;
}

#endif /* LISTE_LISTE_H_ */
