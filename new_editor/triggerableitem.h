
#ifndef _EDITOR_TRIGGERABLE_ITEM_H
#define _EDITOR_TRIGGERABLE_ITEM_H

#include "myitem.h"
#include "data.h"
#include <QObject>

class QTextEdit;
class TriggerItem;

class TriggerableItem:  public QObject, public MyItem { // on herite de QObject pour les slots
	Q_OBJECT	
	
	private:
	QString m_script;
	QTextEdit *m_textEdit;	// en parametre pour etre utilise par un slot
	TriggerItem *m_parent;
	public:
	/*!
	*	@brief Constructeur
	*	@param scene La scene de l'editeur
	*/
	TriggerableItem(QGraphicsScene *scene, TriggerItem *parent, int x = 0, int y = 0);

	/*!
	*	@brief Destructeur
	*/
	~TriggerableItem();
	
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

	
	
	public slots:
	void slotSetScriptText();

};


#endif
