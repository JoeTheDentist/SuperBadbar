#ifndef _RESSOURCES_MAP_H_
#define _RESSOURCES_MAP_H_

#include <map>

template <class K, class T>
class RessourcesMap
{

protected:
    std::map<K, T*> m_map;

public:
    /*!
    *	@brief Constructeur
    */
    RessourcesMap() {}

    /*!
    *	@brief Destructeur
    */
    ~RessourcesMap();

    /*!
    *	@brief Vide le map et detruit les ressources
    */
    virtual void clear();


    /*!
    *	@brief Cree ou retourne la ressource deja existante en fonction de la cle
    *	@param key La cle!
    *	@return a ressource
    */
    virtual T* getOrCreate (K key);

    virtual T* create (K key) = 0;

};

template<class K, class T>
RessourcesMap<K, T>::~RessourcesMap()
{
    clear();
}

template<class K, class T>
void RessourcesMap<K, T>::clear()
{
    typename std::map<K, T*>::iterator it;
    for (it = m_map.begin(); it != m_map.end(); it++)
    {
        delete it->second;
    }
    m_map.clear();
}


template<class K, class T>
T *RessourcesMap<K, T>::getOrCreate (K key)
{
    typename std::map<K, T*>::iterator it = m_map.find (key);
    T *t = 0;
    if (it == m_map.end() )
    {
        t = create (key);
        m_map.insert (typename std::pair<K, T*> (key, t) );
    }
    else
    {
        t = (*it).second;
    }
    return t;
}


#endif
