/**
    Implémentation des listes pour pouvoir faire des listes de tout type
    (voire objets)

    Le tout est rassemblé dans un seul .h à cause des templates, qui ne peuvent se déclarer que dans un seul fichier.

    /!\ Pour la libération de mémoire ces listes supportent :
            - Variable normales (int, float,...) car pas besoin de libérer
            - Les objets (appel de destructeur)

    Remarque : on peut faire la libération de mémoire de liste de pointeurs via la librairie typeinfo, à faire si besoin.
**/


#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED

#include <iostream>


using namespace std;

/***************************
    Structure de cellule
***************************/

template <class T> struct cell {
    T * head;
    cell * back;
};


/*************************
    Classe list
*************************/

template <class T> class List {
    private :
        cell<T> * m_list;               /* Liste */
        cell<T> * m_cursor;             /* Curseur permettant de parcourir la liste */
    public :
        List();                         /* Constructeur */
        List(cell<T> * l);              /* Constructeur surchargé pour forcer m_list */
        ~List();                        /* Destructeur */
        void add(T element);            /* Ajoute un élément à la tête de m_list */
        void cut();                     /* Suppression de la tête de m_list avec libération de la mémoire */
        bool empty();                   /* Retourne true si la liste est vide */
        T head();                       /* Retourne la tête de la liste */

        void init();                    /* Met le curseur au début de la liste */
        void next();                    /* Le curseur va sur l'élément suivant */
        T element();                    /* Retourne l'élément sur le curseur */
        bool end();                     /* Retourne si le curseur est à la fin de la liste */

        void do_list(void (*fct)(T));   /* Applique une void fonction à chaque élément de la liste */
        void delete_elements(bool (*fct)(T)); /* Supprime les éléments qui vérifient fct */
};


/*****Méthodes*****/

template <class T> List<T>::List()
{
    m_list = NULL;
    m_cursor = NULL;
}

template <class T> List<T>::List(cell<T> * l)
{
    m_list = l;
}

template <class T> List<T>::~List()
{
    while(!empty()) {
        cut();
    }
}

template <class T> void List<T>::init()
{
    m_cursor = m_list;
}

template <class T> void List<T>::next()
{
    m_cursor = m_cursor->back;
}

template <class T> T List<T>::element()
{
    return *(m_cursor->head);
}

template <class T> bool List<T>::end()
{
    return (m_cursor == NULL);
}

template <class T> void List<T>::add(T element)
{
    cell<T> * p = new cell<T>;
    p->head = new T;
    *(p->head) = element;
    p->back = m_list;
    m_list = p;
    init();
}

template <class T> void List<T>::cut()
{
    cell<T> * p = m_list->back;
    delete m_list->head;
    delete m_list;
    m_list = p;
    init();
}

template <class T> bool List<T>::empty()
{
    return (m_list == NULL);
}

template <class T> T List<T>::head()
{
    return *(m_list->head);
}

template <class T> void List<T>::do_list(void (*fct)(T))
{
    cell<T> * l = m_list;
    while(l!= NULL) {
        fct(l->head);
        l = l->back;
    }
}

template <class T> void List<T>::delete_elements(bool (*fct)(T))
{
    T a; /* Sentinelle, Dieu que c'est bien de ne pas devoir initialiser quelque chose qu'on ne connait pas et dont on a pas besoin */
    cell<T> * temp;
    add(a);
    cell<T> * last = m_list; /* Pointeur sur le précédent */
    next(); /* Pour que le curseur ne soit pas au même endroit que last */
    while(!end()) {
        if(fct(*(m_cursor->head))) {
            next();
            temp = last->back->back;
	    delete last->back->head;
            delete last->back;
            last->back = temp;
        }
        else {
            next();
            last = last->back;
        }
    }
    cut(); /* Die fucking sentinelle !!! */
}

#endif // LISTS_H_INCLUDED
