//~ #ifndef _EDITOR_MONSTER_ITEM_H
//~ #define _EDITOR_MONSTER_ITEM_H

//~ #include "myitem.h"
//~ #include "data.h"

//~ class MonsterItem: public MyItem {
//~ 	private:
//~ 	QString m_class_name;
//~ 	
//~ 	public:
//~ 	/*!
//~ 	*	@brief Constructeur
//~ 	*	@param item L'objet à encapsuler
//~ 	*	@param fileName Le nom du fichier, contenant "monsters/chemindufichier"
//~ 	*/
//~ 	MonsterItem(QGraphicsItem *item, QString fileName);
//~ 	
//~ 	/*!
//~ 	*	@brief Destructeur
//~ 	*/
//~ 	~MonsterItem(
//~ 	~MonsterItem();
//~ 	
//~ 	/*!
//~ 	*	@brief Sauvegarde l'objet dans out
//~ 	*	@param out Le flux dans lequel on doit sauvegarder
//~ 	*/
//~ 	virtual void saveItem(QTextStream &out);
//~ 	
//~ 	/*!
//~ 	*	@brief ajoute l'objet correctement à data
//~ 	*	@param data Le conteneur d'objets
//~ 	*/
//~ 	virtual void addToData(Data *data);

//~ 	/*!
//~ 	*	@brief transforme le nom du fichier ecrit dans un .lvl
//~ 	*	en le chemin relatif vers le fichier depuis l'editeur
//~ 	*	@return Ce chemin
//~ 	*/
//~ 	static QString editorRelativePath(QString fileName);

//~ };


//~ #endif);
	
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
	*	@brief transforme le nom du fichier ecrit dans un .lvl
	*	en le chemin relatif vers le fichier depuis l'editeur
	*	@return Ce chemin
	*/
	static QString editorRelativePath(QString fileName);

};


#endif
