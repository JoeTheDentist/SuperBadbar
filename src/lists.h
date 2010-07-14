/**
    Impl�mentation des listes pour pouvoir faire des listes de tout type
    (voire objets)

    Le tout est rassembl� dans un seul .h � cause des templates, qui ne peuvent se d�clarer que dans un seul fichier.
**/


#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED

#include <iostream>

using namespace std;

/***************************
    Structure de cellule
***************************/

template <class T> struct cell {
    T head;
    cell * back;
};


/*************************
    Classe list
*************************/

template <class T> class List {
    private :
        cell<T> * m_list;
    public :
        List();                         /* Constructeur */
        List(cell<T> * l);              /* Constructeur surcharg� pour forcer m_list */
        ~List();                        /* Destructeur */
        void add(T element);            /* Ajoute un �l�ment � la t�te de m_list */
        void cut();                     /* Suppression de la t�te de m_list avec lib�ration de la m�moire */
        bool empty();                   /* Retourne si la liste est vide */
        T head();                       /* Retourne la t�te de la liste */

        void do_list(void (*fct)(T));   /* Applique une void fonction � chaque �l�ments de la liste */
};


/*****M�thodes*****/

template <class T> List<T>::List()
{
    m_list = NULL;
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

template <class T> void List<T>::add(T element)
{
    cell<T> * p = new cell<T>;
    p->head = element;
    p->back = m_list;
    m_list = p;
}

template <class T> void List<T>::cut()
{
    cell<T> * p = m_list->back;
    delete m_list;
    m_list = p;
}

template <class T> bool List<T>::empty()
{
    return (m_list == NULL);
}

template <class T> T List<T>::head()
{
    return m_list->head;
}

template <class T> void List<T>::do_list(void (*fct)(T))
{
    cell<T> * l = m_list;
    while(l!= NULL) {
        fct(l->head);
        l = l->back;
    }
}

#endif // LISTS_H_INCLUDED
