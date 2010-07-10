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
        list();
        list(cell<T> * l);
        ~list();
        void add(T element);
        void cut();
        bool empty();
        T head();
        list<T> back();
        void change_head(T new_head);
        void print();

        void do_list(void (*fct)(T));
        void map(T (*fct)(T));
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
