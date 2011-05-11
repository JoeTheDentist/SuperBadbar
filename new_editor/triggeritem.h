#ifndef _EDITOR_TRIGGER_ITEM_H
#define _EDITOR_TRIGGER_ITEM_H

#include "myitem.h"
#include "data.h"
#include "eventitem.h"
#include <QObject>

class TriggerableItem;
class QTextEdit;

class TriggerItem:  public QObject, public MyItem { // on herite de QObject pour les slots
	Q_OBJECT	
	
	private:
	int m_trigger_id; // l'identifiant du trigger
	QString m_class_name;
	QString m_level_name; // le nom du level depuis le dossier des levels
	std::list<TriggerableItem *> m_triggerables; // pour le moment remplace par m_text
	QString m_script;
	QGraphicsScene *m_scene;
	QTextEdit *m_textEdit;	// en parametre pour etre utilise par un slot
	public:
	/*!
	*	@brief Constructeur
	*	@param scene La scene de l'editeur
	*	@param fileName Le nom du fichier level depuis au moins la racine du projet
	*/
	TriggerItem(QGraphicsScene *scene, QString fileName, int trigind = -1, int x = 0, int y = 0);

	
	
	
	/*!
	*	@brief Destructeur
	*/
	~TriggerItem();
	
	/*!
	*	@brief Retourne l'item selectionne
	*
	*	Ici il peut s'agire du triggeritem ou de ses fils
	*/
	virtual MyItem* selectItem(int x, int y);

	
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
	*	@brief Methode appelee quand on clique droit sur l'item
	*	@param x Abcisse du clic par rapport a la fenetre
	*	@param y Ordonnee du clic par rapport a la fenetre
	*/
	virtual void rightClic(int x, int y);
	
	
	/*!
	*	@brief Acheve l'ajout de item a au trigger 
	*	@param item L'item a ajouter
	*/
	virtual void addTriggerableItem(TriggerableItem *item);
	
	
	public slots:
	void slotSetScriptText();
	void slotAddPosition();
	void slotAddTriggerable();

};


#endif
