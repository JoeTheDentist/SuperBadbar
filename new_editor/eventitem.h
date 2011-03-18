#ifndef _EDITOR_EVENT_ITEM_H
#define _EDITOR_EVENT_ITEM_H

#include "myitem.h"
#include "data.h"

class EventItem: public MyItem {
	private:
	QString m_class_name;
	
	public:
	/*!
	*	@brief Constructeur
	*	@param item L'objet à encapsuler
	*	@param fileName Le nom du fichier, contenant "monsters/chemindufichier"
	*/
	EventItem(QGraphicsPixmapItem *item, QString fileName);
	
	/*!
	*	@brief Destructeur
	*/
	~EventItem();
	
	/*!
	*	@brief Cree une instance identique a l'instance actuelle
	*	@return Un pointeur vers la copie
	*/
	virtual MyItem *duplicate();
	
	
	/*!
	*	@brief Sauvegarde l'objet dans out
	*	@param out Le flux dans lequel on doit sauvegarder
	*/
	virtual void saveItem(QTextStream &out);
	
	/*!
	*	@brief ajoute l'objet correctement à data
	*	@param data Le conteneur d'objets
	*/
	virtual void addToData(Data *data);

	/*!
	*	@brief transforme le nom du fichier ecrit dans un .evt
	*	en le chemin relatif vers le fichier depuis l'editeur
	*	@return Ce chemin
	*/
	static QString picPathFromEditor(QString fileName);

};


#endif
