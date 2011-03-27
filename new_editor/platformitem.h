#ifndef _EDITOR_PLATEFORM_ITEM_H_
#define _EDITOR_PLATEFORM_ITEM_H_

#include "myitem.h"
#include "staticitem.h"
#include "data.h"
#include "analyser.h"

class MyGraphicsView;

class PlatformItem: public StaticItem {
	protected:
	PlatformItem *m_father;
	PlatformItem *m_son;

	public:
	/*!
	*	@brief Constructeur
	*	@param scene La scene de l'editeur
	*	@param fileName Le nom du fichier, contenant "statics/chemindufichier"
	*	@param father Le pere du plateform (NULL si on souhaite creer le pere)
	*/
	PlatformItem(QGraphicsScene *scene, QString fileName, PlatformItem *father = NULL);
	
	/*!
	*	@brief Constructeur
	*	@param scene La scene de l'editeur
	*	@param fileName Le nom du fichier, contenant "statics/chemindufichier"
	*	@param analyser Un analyseur pret a donner les coordonnees de l'item
	*	@param father Le pere du plateform (NULL si on souhaite creer le pere)
	*/	
	PlatformItem(QGraphicsScene *scene, QString fileName, Analyser &analyser, PlatformItem *father = NULL);
	
	/*!
	*	@brief Destructeur
	*/
	~PlatformItem();
	
	void setFather(PlatformItem *father);
	void setSon(PlatformItem *son);
	
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
	
	virtual void edit();

	/*!
	*	@brief transforme le nom du fichier ecrit dans un .lvl
	*	en le chemin relatif vers l'image de l'objet depuis l'editeur
	*	@return Ce chemin
	*/
	static QString picPathFromEditor(QString fileName);
	
	
	bool isFather() { return m_son; }
	
	PlatformItem *getSon() { return m_son; }

	virtual void moveItem(int x, int y);
	virtual void setPos(int x, int y);	
	
	virtual MyItem* selectItem(int x, int y);


	virtual void removeFromScene(QGraphicsScene *scene);
	
	virtual void setVisible(bool visible);

	protected:
		
	virtual void setStaticZBuffer(int buffer);


};


#endif
