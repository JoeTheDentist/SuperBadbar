#ifndef _EDITOR_STATIC_ITEM_H_
#define _EDITOR_STATIC_ITEM_H_

#include "myitem.h"
#include "data.h"

class StaticItem: public MyItem {
	private:
	int m_zbuffer; // 0 ou 1
	public:
	/*!
	*	@brief Constructeur
	*	@param item L'objet à encapsuler
	*	@param fileName Le nom du fichier, contenant "statics/chemindufichier"
	*/
	StaticItem(QGraphicsPixmapItem *item, QString fileName);
	
	/*!
	*	@brief Destructeur
	*/
	~StaticItem();
	
	
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
	
	virtual void edit();

	/*!
	*	@brief transforme le nom du fichier ecrit dans un .lvl
	*	en le chemin relatif vers l'image de l'objet depuis l'editeur
	*	@return Ce chemin
	*/
	static QString picPathFromEditor(QString fileName);
	
	private:
		
	void setStaticZBuffer(int buffer);

};


#endif
