/**
    Impl�mentation des listes pour pouvoir faire des listes de tout type
    (voire objets)

    Le tout est rassembl� dans un seul .h � cause des templates, qui ne peuvent se d�clarer que dans un seul fichier.

    /!\ Pour la lib�ration de m�moire ces listes supportent :
            - Variable normales (int, float,...) car pas besoin de lib�rer
            - Les objets (appel de destructeur)

    Remarque : on peut faire la lib�ration de m�moire de liste de pointeurs via la librairie typeinfo, � faire si besoin.
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
        List(cell<T> * l);              /* Constructeur surcharg� pour forcer m_list */
        ~List();                        /* Destructeur */
        void add(T element);            /* Ajoute un �l�ment � la t�te de m_list */
        void cut();                     /* Suppression de la t�te de m_list avec lib�ration de la m�moire */
        bool empty();                   /* Retourne true si la liste est vide */
        T head();                       /* Retourne la t�te de la liste */

        void init();                    /* Met le curseur au d�but de la liste */
        void next();                    /* Le curseur va sur l'�l�ment suivant */
        T element();                    /* Retourne l'�l�ment sur le curseur */
        bool end();                     /* Retourne si le curseur est � la fin de la liste */

        void do_list(void (*fct)(T));   /* Applique une void fonction � chaque �l�ment de la liste */
        void delete_elements(bool (*fct)(T)); /* Supprime les �l�ments qui v�rifient fct */
};


/*****M�thodes*****/

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
    cell<T> * last = m_list; /* Pointeur sur le pr�c�dent */
    next(); /* Pour que le curseur ne soit pas au m�me endroit que last */
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
