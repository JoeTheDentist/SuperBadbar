#ifndef _EDITOR_MY_ITEM_H
#define _EDITOR_MY_ITEM_H

#include <QTextStream>
#include <QString>
 #include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>

class Data;
class QGraphicsItem;
class MyGraphicsView;

enum miState {
	e_beingAdded, e_beingMoved, e_selected, e_beingResized, e_nothing
};

class MyItem {
	protected:
	static MyGraphicsView *m_view;
	QGraphicsItem *m_item;
	miState m_state;
	QString m_file_name;
	
	
	public:
	/*!
	*	@brief Constructeur
	*	@param item L'item Qt que doit contenir le myitem
	*	@param fileName Nom de fichier (depend de l'instance de myitem)
	*	@param state L'etat courant de l'item
	*/
	MyItem(QGraphicsItem *item, QString fileName, miState state = e_beingAdded);
	
	/*!
	*	@brief Destructeur
	*/
	virtual ~MyItem();
	
	/*!
	*	@brief Changement de la view (commune a tous les myitems)
	*	@param view La nouvelle view
	*/
	static void setView(MyGraphicsView *view);
	
	/*!
	*	@brief Accesseur
	*	@return Le viewer des myitems
	*/
	static MyGraphicsView *getView();
	
	/*!
	*	@brief Cree une instance identique a l'item courant
	*	@param scene La scene de l'editeur
	*	@return Un pointeur vers l'instance
	*/
	virtual MyItem *duplicate(QGraphicsScene *scene) = 0;
	
	/*!
	*	@brief Accesseur
	*	@return L'item Qt contenu dans le myitem
	*/
	QGraphicsItem *getItem();
	
	/*!
	*	@brief Accesseur
	*	@return La position x de l'item
	*/
	virtual int x() {return m_item->x();}
	
	/*!
	*	@brief Accesseur
	*	@return La position y de l'item
	*/	
	virtual int y() {return m_item->y();}
	
	/*!
	*	@brief Sauvegarde l'item dans out
	*	@param out Le QTextStream dans lequel est sauvegarde l'item
	*/
	virtual void saveItem(QTextStream &out) = 0;
	
	/*!
	*	@brief Ajoute l'item a la data 
	*	@param data La data dans laquelle on doit ajouter l'item
	*	@param push_front Indique si on doit mettre l'item au debut
	ou a la fin (influe sur l'affichage)
	*/
	virtual void addToData(Data *data, bool push_front = true) = 0;
	
	/*!
	*	@brief Appele quand l'item a ete ajoute au niveau
	*/
	virtual void signalEndOfAdding();
	
	/*!
	*	@brief Appele quand on double clique sur l'item (ne fait rien
	par defaut)
	*/
	virtual void edit();
	
	/*!
	*	@brief Appele quand l'item est selectionne et que la souris bouge
	*/
	virtual void mouseMoved(int x, int y);
	
	/*!
	*	@brief Appele quand on clique droit sur l'item
	*	@param x La position du clic
	*	@param y La position du clic
	*/
	virtual void rightClic(int x, int y) { Q_UNUSED(x); Q_UNUSED(y);}
	
	/*!
	*	@brief Deplace l'item selon son etat
	*	@param xrel	Deplacement relatif 
	*	@param yrel	Deplacement relatif
	*	@param xabs Deplacement absolu
	*	@param yabs Deplacement absolu
	*
	*	Si l'item est en cours d'ajout, l'item et place en (xabs, yabs)
	*
	*	Sinon, l'item et deplace de (xrel, yrel)
	*/	
	virtual void moveItem(int xrel, int yrel, int xabs = 0, int yabs = 0);
	
	/*!
	*	@brief Mutateur de position (le seul a modifier directement la position)
	*	@param x La nouvelle position
	*	@param y La nouvelle position
	*/
	virtual void setPos(int x, int y);
		
	/*!
	*	@brief Retourne l'item s'il contient le point (x,y)
	*	@param x Le point recherche
	*	@param y Le point recherche
	*	@return L'item s'il contient le point, NULL sinon
	*/
	virtual MyItem* selectItem(int x, int y);
	
	/*!
	*	@brief Supprime l'item de la scene (mais pas des donnees)
	*	@param scene La scene contenant l'item
	*/
	virtual void removeFromScene(QGraphicsScene *scene);
	
	/*!
	*	@brief Mutateur: rend visible (true) ou invisible (false)
	*	@param visible Booleen de visibilite
	*/
	virtual void setVisible(bool visible) { m_item->setVisible(visible);}
	
	/*!
	*	@brief Supprime l'item des donnees 	(mais pas de la scene)
	*	@param data La data contenant l'item
	*/	
	virtual void removeFromData(Data *data);
		
	/*!
	*	@brief Mutateur d'etat
	*/
	virtual void setStateBeingAdded() {m_state = e_beingAdded;}
		
	/*!
	*	@brief Mutateur d'etat
	*/	
	virtual void setStateBeingMoved() {m_state = e_beingMoved;}
	
	/*!
	*	@brief Mutateur d'etat
	*/	
	virtual void setStateSelected();

	/*!
	*	@brief Mutateur d'etat
	*/
	virtual void setStateNothing();
	
	/*!
	*	@brief Accesseur
	*	@return Vrai si l'item est en etat d'ajout
	*/
	bool isBeingAdded() const {return m_state == e_beingAdded ;}
	
	/*!
	*	@brief Accesseur
	*	@return Vrai si l'item est en etat de deplacement
	*/
	bool isBeingMoved() const {return m_state == e_beingMoved ;}
	
	/*!
	*	@brief Accesseur
	*	@return Vrai si l'item est en etat selectionne
	*/
	bool isSelected() const {return m_state == e_selected ;}
	
	/*!
	*	@brief Accesseur
	*	@return Vrai si l'item n'a pas d'etat particulier
	*/
	bool isNothing() const {return m_state == e_nothing ;}
	
	protected:
	
	/*!
	*	@brief Mutateur d'item Qt contenu
	*	@param item Le nouvel item
	*/
	void setItem(QGraphicsItem *item) { m_item = item; }
	
};



#endif
