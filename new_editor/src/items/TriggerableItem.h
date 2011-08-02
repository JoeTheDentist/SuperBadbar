
#ifndef _EDITOR_TRIGGERABLE_ITEM_H
#define _EDITOR_TRIGGERABLE_ITEM_H

#include <QObject>

#include <items/MyItem.h>
#include <editor/Data.h>
#include <util/utils.h>

class QTextEdit;
class TriggerItem;
class QGraphicsLineItem;

class TriggerableItem:  public QObject, public MyItem { // on herite de QObject pour les slots
	Q_OBJECT	
	
	private:
	QString m_script;
	QTextEdit *m_textEdit;	// en parametre pour etre utilise par un slot
	TriggerItem *m_parent;
	QGraphicsLineItem *m_itemSegment;
	public:
	/*!
	*	@brief Constructeur
	*	@param scene La scene de l'editeur
	*	@param parent L'item parent
	*	@param x L'abscisse de depart du triggerable
	*	@param y L'ordonnee de depart du triggerable
	*/
	TriggerableItem(QGraphicsScene *scene, TriggerItem *parent, int x = 0, int y = 0);

	/*!
	*	@brief Constructeur
	*	@param scene La scene de l'editeur
	*	@param parent L'item parent
	*	@param analyser L'analyser pret a lire les donnees du triggerable
	*/	
	TriggerableItem(QGraphicsScene *scene, TriggerItem *parent, Analyser &analyser);

	/*!
	*	@brief Constructeur de copie
	*	@param original L'objet a copier
	*/
	TriggerableItem(TriggerableItem &original);

	/*!
	*	@brief Destructeur
	*/
	~TriggerableItem();
	
	/*!
	*	@brief Cree une instance identique a l'instance actuelle mais dont l'item est invisible
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
	*	@brief Mutateur de position
	*	@param x Nouvelle position x
	*	@param y Nouvelle position y
	*/
	virtual void setPos(int x, int y);
	
	virtual void removeFromScene(QGraphicsScene *scene);

	public slots:
	/*!
	*	@brief Met a jour le champ m_script en fonction des entrees de l'utilisateur dans m_textEdit
	*/
	void slotSetScriptText();
	
	
	/*!
	*	@brief Mise a jour de la ligne reliant l'item a son parent
	*/
	void updateLine();

	private:
		
	/*!
	*	@brief Ajout de la ligne reliant l'item a son parent
	*/
	void addLine();

};


#endif
