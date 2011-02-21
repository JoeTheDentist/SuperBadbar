#ifndef _EDITOR_STATIC_ITEM_H_
#define _EDITOR_STATIC_ITEM_H_

#include "myitem.h"
#include "data.h"

class StaticItem: public MyItem {
	public:
	/*!
	*	@brief Constructeur
	*	@param item L'objet à encapsuler
	*	@param fileName Le nom du fichier, contenant "statics/chemindufichier"
	*/
	StaticItem(QGraphicsItem *item, QString fileName);
	
	/*!
	*	@brief Destructeur
	*/
	~StaticItem();
	
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

	static QString editorRelativePath(QString fileName);

};


#endif
