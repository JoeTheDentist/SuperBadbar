#ifndef _EDITOR_TRIGGER_ITEM_H
#define _EDITOR_TRIGGER_ITEM_H

#include "myitem.h"
#include "data.h"
#include "eventitem.h"

class TriggerItem: public MyItem {
	private:
	QString m_class_name;
	std::list<EventItem *> m_events;
	QGraphicsScene *m_scene;
	
	public:
	/*!
	*	@brief Constructeur
	*	@param scene La scene de l'editeur
	*	@param fileName Pas de sens ici (mettre "")
	*/
	TriggerItem(QGraphicsScene *scene, QString fileName = "");
	
	/*!
	*	@brief Destructeur
	*/
	~TriggerItem();
	
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

};


#endif
