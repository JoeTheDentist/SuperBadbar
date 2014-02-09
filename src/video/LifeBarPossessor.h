/**
 * 	@file LifeBarPossessor.h
 * 	@brief Header de la classe virtuelle LifeBarPossessor
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date juin 2011
 *
 */

class Dashboard;

/**
*	@class LifeBarPossessor
*	@brief Interface pour toute entite possedant une barre de vie
*
*	L'objet ne possede pas directement une barre de vie: c'est le dashboard
*	qui contiendra et affichera cette barre de vie si connect_to_dashboard est
*	appele. Dans ce cas, le dashboard affichera une barre correspondant a la fraction
*	renvoyee par life_bar_status()
*/


class LifeBarPossessor
{
public:
    /**
    *	@brief Constructeur
    */
    LifeBarPossessor() {}

    /**
    *	@brief Destructeur
    */
    ~LifeBarPossessor() {}

    /**
    *	@brief Accesseur sur l'etat de la barre de vie
    *	@return Une valeur entre 0 et 1
    */
    virtual double life_bar_status() = 0;

    /**
    *	@brief connecte l'objet au dashboard
    */
    virtual void connect_to_dashboard();

    /**
    *	@brief deconnecte l'objet du dashboard
    */
    virtual void disconnect_from_dashboard();

    /**
    *	@brief Initialise le dashboard commun a tous les LifeBarPossessor
    *	@param dashboard Un pointeur vers ce dashboard
    */
    static void setDashboard (Dashboard *dashboard);

public:
    static Dashboard *m_dashboard;
};
