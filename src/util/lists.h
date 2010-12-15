/*!
	@todo surement Ã  enlever!

    Implémentation des listes pour pouvoir faire des listes de tout type
    (voire objets)

    Le tout est rassemblé dans un seul .h à cause des templates, qui ne peuvent se déclarer que dans un seul fichier.

    /!\ Pour la libération de mémoire ces listes ne marchent QUE pour des listes de POINTEURS alloués... Malgré le typeid, je compilateur n'es pas content
**/


#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED

#include <iostream>
#include <typeinfo>


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
        cell<T> * m_last;               /* Avant curseur */
    public :
        List();                         /* Constructeur */
        List(cell<T> * l);              /* Constructeur surchargé pour forcer m_list */
        ~List();                        /* Destructeur */
        void void_list();               /* Vide la liste en gardant la sentinelle */
        void add(T element);            /* Ajoute un élément à la tête de m_list */
        void cut();                     /* Suppression de la tête de m_list avec libération de la mémoire */
        bool empty();                   /* Retourne true si la liste est vide */
        T head();                       /* Retourne la tête de la liste */

        void init();                    /* Met le curseur au début de la liste */
        void next();                    /* Le curseur va sur l'élément suivant */
        T element();                    /* Retourne l'élément sur le curseur */
        bool end();                     /* Retourne si le curseur est à la fin de la liste */
        void delete_element(bool cond); /* Supprime l'élément sur curseur si cond */
        void free_element(bool cond);   /* Supprime l'élément sur curseur si cond, et libère la mémoire */

        void do_list(void (*fct)(T));   /* Applique une void fonction à chaque élément de la liste */
};


/*****Méthodes*****/

template <class T> List<T>::List()
{
    m_list = NULL;
    T a;            /* Sentinelle puis ajout */
    cell<T> * p = new cell<T>;
    p->head = new T;
    *(p->head) = a;
    p->back = m_list;
    m_list = p;
    init();
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

template <class T> void List<T>::void_list()
{
    while ( m_list->back != NULL ) {
        cut();
    }
}

template <class T> void List<T>::init()
{
    m_cursor = m_list->back;
    m_last = m_list;
}

template <class T> void List<T>::next()
{
    m_cursor = m_cursor->back;
    m_last = m_last->back;
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
    p->back = m_list->back;
    m_list->back = p;
    init();
}

template <class T> void List<T>::cut()
{
    cell<T> * p = m_list->back->back;
    delete *(m_list->back->head);
    delete m_list->back->head;
    delete m_list->back;
    m_list->back = p;
    if ( m_list != NULL ) {
        init();
    } else {
        m_cursor = NULL;
        m_last = NULL;
    }
}

template <class T> bool List<T>::empty()
{
    return (m_list->back == NULL);
}

template <class T> T List<T>::head()
{
    return *(m_list->head);
}

/* Attention ! La suppréssion ne libère pas la mémoire !!!!!!!! */
template <class T> void List<T>::delete_element(bool cond)
{
    if ( cond ) {
        cell<T> * temp = m_last->back->back;
        m_cursor = m_cursor->back;
        delete m_last->back->head;
        delete m_last->back;
        m_last->back = temp;
    }
}

template <class T> void List<T>::free_element(bool cond)
{
    if ( cond ) {
        cell<T> * temp = m_last->back->back;
        m_cursor = m_cursor->back;
        delete *(m_last->back->head);
        delete m_last->back->head;
        delete m_last->back;
        m_last->back = temp;
    }
}

template <class T> void List<T>::do_list(void (*fct)(T))
{
    cell<T> * l = m_list->back;
    while ( l != NULL ) {
        fct(*(l->head));
        l = l->back;
    }
}

#endif // LISTS_H_INCLUDED
