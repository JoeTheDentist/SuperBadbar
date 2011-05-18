
#ifndef _EDITOR_ZONE_ITEM_H
#define _EDITOR_ZONE_ITEM_H

#include "myitem.h"
#include "data.h"
#include <QObject>
#include "utils.h"

class QTextEdit;
class TriggerItem;

class ZoneItem: public MyItem {
	
	private:
	TriggerItem *m_parent;
	int m_width;
	int m_height;
	public:
	/*!
	*	@brief Constructeur
	*	@param scene La scene de l'editeur
	*	@param parent L'item parent 
	*	@param x l'abscisse de depart
	*	@param y l'ordonnee de depart
	*	@param w epaisseur de la zone
	*	@param h hauteur de la zone
	*/
	ZoneItem(QGraphicsScene *scene, TriggerItem *parent, int x = 0, int y = 0, int w = 0, int h = 0);

	/*!
	*	@brief Constructeur
	*	@param scene La scene de l'editeur
	*	@param parent L'item parent 
	*	@param analyser L'analyser avec le curseur devant les 4 coordoonnees du rectangle
	*/
	ZoneItem(QGraphicsScene *scene, TriggerItem *parent, Analyser &analyser);

	/*!
	*	@brief Destructeur
	*/
	~ZoneItem();
	
	/*!
	*	@brief Cree une instance identique a l'instance actuelle
	*	@param scene La scene de l'editeur
	*	@return Un pointeur vers la copie
	*/
	virtual MyItem *duplicate(QGraphicsScene *scene);
	
	
	/*!
	*	@brief Sauvegarde l'objet dans out
	*	@param out Le flux dans lequel on doit sauvegarder
	*/
	virtual void saveItem(QTextStream &out);
	
	/*!
	*	@brief ajoute l'objet correctement à data
	*	@param data Le conteneur d'objets
	*	@param push_front Indique si l'item doit etre positionne en tete ou en queue
	*/
	virtual void addToData(Data *data, bool push_front = true);

	/*!
	*	@brief transforme le nom du fichier ecrit dans un .evt
	*	en le chemin relatif vers le fichier depuis l'editeur
	*	@return Ce chemin
	*/
	static QString picPathFromEditor(QString fileName);
	
	/*!
	*	@brief Edition de l'item
	*/
	virtual void edit();

	/*!
	*	@brief Deplacement de l'item 
	*	@param xrel Deplacement horizontal relatif
	*	@param yrel Deplacement vertical relatif
	*	@param xabs Deplacement horizontal absolu
	*	@param yabs Deplacement vertical absolu
	
	*/
	virtual void moveItem(int xrel, int yrel, int xabs = 0, int yabs = 0);
	
	/*!
	*	@brief Methode appelee apres la fin d'ajout a la souris d'un item
	*/
	virtual void signalEndOfAdding();
	
	
	virtual void changeCoordinates(int x, int y, int x2, int y2) ;
	
	virtual int x() {return m_item->x();}
	virtual int y() {return m_item->y();}




};


#endif
