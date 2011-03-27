#ifndef _EDITOR_BABAR_ITEM_H_
#define _EDITOR_BABAR_ITEM_H_

#include "myitem.h"
#include "data.h"

class BabarItem: public MyItem {
	private:
		int m_age;
	public:
	/*!
	*	@brief Constructeur
	*	@param item L'objet à encapsuler
	*	@param fileName Le nom du fichier, contenant "statics/chemindufichier"
	*/
	BabarItem(QGraphicsScene *scene, int age = 1);
	
	/*!
	*	@brief Destructeur
	*/
	~BabarItem();

	/*!
	*	@brief Cree une instance identique a l'instance actuelle
	*	@param scene La scene de l'editeur (ici inutile)
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
	
	virtual void edit();

	/*!
	*	@brief transforme le nom du fichier ecrit dans un .lvl
	*	en le chemin relatif vers l'image de l'objet depuis l'editeur
	*	@return Ce chemin
	*/
	static QString picPathFromEditor(QString fileName);
	
	void setBabarAge(int entier);

};

#endif
