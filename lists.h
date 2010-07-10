#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED

#include <iostream>

using namespace std;


template <class T> struct cell {
    T head;
    cell * back;
};



template <class T> class list {
    private :
        cell<T> * m_list;
    public :
        list();                         /* Constructeur */
        list(cell<T> * l);              /* Constructeur surchargé pour forcer m_list */
        ~list();                        /* Destructeur */
        void add(T element);            /* Ajoute un élément à la tête de m_list */
        void cut();                     /* Suppression de la tête de m_list avec libération de la mémoire */
        bool empty();                   /* Retourne si la liste est vide */
        T head();                       /* Retourne la tête de la liste */
        list<T> back();                 /* Retourne la queue de la liste (qui est un objet) */
        void change_head(T new_head);   /* Modifie la tête de la liste (utilisée pour la méthode map) */
        void print();                   /* temp */

        void do_list(void (*fct)(T));   /* Applique une void fonction à chaque éléments de la liste */
        void map(T (*fct)(T));          /* Modif tous les éléments de la liste : x = fct(x) */
};

template <class T> list<T>::list()
{
    m_list = NULL;
}

template <class T> list<T>::list(cell<T> * l)
{
    m_list = l;
}


template <class T> list<T>::~list()
{
    /*while(!empty()) {
        cut();
    }*/
}

template <class T> void list<T>::add(T element)
{
    cell<T> * p = new cell<T>;
    p->head = element;
    p->back = m_list;
    m_list = p;
}

template <class T> void list<T>::cut()
{
    cell<T> * p = m_list->back;
    delete m_list;
    m_list = p;
}

template <class T> bool list<T>::empty()
{
    return (m_list == NULL);
}

template <class T> T list<T>::head()
{
    return m_list->head;
}

template <class T> list<T> list<T>::back()
{
    list<T> l(m_list->back);
    return l;
}

template <class T> void list<T>::change_head(T new_head)
{
    m_list->head = new_head;
}

template <class T> void list<T>::print()
{
    if(m_list != NULL) {
        cout << head() << " ";
        back().print();
    }
    cout << endl;
}

template <class T> void list<T>::do_list(void (*fct)(T))
{
    if(!empty()) {
        fct(head());
        back().do_list(fct);
    }
}

template <class T> void list<T>::map(T (*fct)(T))
{
    if(!empty()) {
        change_head(fct(head()));
        back().map(fct);
    }
}

#endif // LISTS_H_INCLUDED
