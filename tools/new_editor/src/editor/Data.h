#ifndef _EDITOR_DATA_H_
#define _EDITOR_DATA_H_

#include <list>
#include <QString>

class QGraphicsPixmapItem;
class MyItem;

class Data
{
private:
    MyItem *m_babar_item;
    std::list<MyItem *> m_set_items;
    std::list<MyItem *> m_static_items;
    std::list<MyItem *> m_platform_items;
    std::list<MyItem *> m_falling_platform_items;
    std::list<MyItem *> m_monsters_items;
    std::list<MyItem *> m_event_items;
    std::list<MyItem *> m_triggers_items;
    QString m_background_name;
    QString m_music_name;
    QGraphicsPixmapItem *m_background;
    int m_xpix;
    int m_ypix;

public:
    /*!
    *	@brief Constructeur
    */
    Data();

    /*!
    *	@brief Destructeur
    */
    ~Data();

    /*!
    *	@brief Initialise les donnees du niveau ouvert
    *	@param backgroundName Le chemin relatif ou absolu vers le fond d'ecran du niveau
    *
    *	backgroundName doit contenir la chaine "backgrounds/"
    */
    void initData (QString backgroundName);

    /*!
    *	@brief Accesseur
    *	@return La largeur du niveau
    */
    int levelWidth();

    /*!
    *	@brief Accesseur
    *	@return La hauteur du niveau
    */
    int levelHeight();

    /*!
    *	@brief Mutateur
    *	@param str Le nom de la musique du level (depuis le repertoire des musiques)
    */
    void setMusicName (QString str)
    {
        m_music_name = str;
    }

    /*!
    *	@brief Ajoute un item aux donnees (attention, data ne se charge pas de l'affichage)
    *	@param item L'item a ajouter
    *
    *	L'item possede une methode permettant de choisir entre addStaticItem, addMonsterItem etc.
    *	On n'a donc a priori besoin de addStaticItem, addMonsterItem etc. seulement dans item, et on
    *	utilisera sinon addItem qui fera la distinction
    */
    void addItem (MyItem *item, bool push_front = false);

    /*!
    *	@brief Ajoute un item a la liste des staticItem
    *	@param item L'item a ajouter
    *
    *	Cette méthode ne sera a priori appelée que par les items
    *	On lui préférera dans les autres classes addItem qui appelera lui-meme addStaticItem
    */
    void addBabarItem (MyItem *item);

    /*!
    *	@brief Ajoute un item a la liste des setItem
    *	@param item L'item a ajouter
    *
    *	Cette méthode ne sera a priori appelée que par les items
    *	On lui préférera dans les autres classes addItem qui appelera lui-meme addSetItem
    */
    void addSetItem (MyItem *item, bool push_front = false);

    /*!
    *	@brief Ajoute un item a la liste des staticItem
    *	@param item L'item a ajouter
    *
    *	Cette méthode ne sera a priori appelée que par les items
    *	On lui préférera dans les autres classes addItem qui appelera lui-meme addStaticItem
    */
    void addStaticItem (MyItem *item, bool push_front = false);

    /*!
    *	@brief Ajoute un item a la liste des platformItem
    *	@param item L'item a ajouter
    *
    *	Cette méthode ne sera a priori appelée que par les items
    *	On lui préférera dans les autres classes addItem qui appelera lui-meme addMovingPlatformItem
    */
    void addMovingPlatformItem (MyItem *item, bool push_front = false);

    /*!
    *	@brief Ajoute un item a la liste des fallingplatformItem
    *	@param item L'item a ajouter
    *
    *	Cette méthode ne sera a priori appelée que par les items
    *	On lui préférera dans les autres classes addItem qui appelera lui-meme addFallingPlatformItem
    */
    void addFallingPlatformItem (MyItem *item, bool push_front = false);

    /*!
    *	@brief Ajoute un item a la liste des monstersItem
    *	@param item L'item a ajouter
    *
    *	Cette méthode ne sera a priori appelée que par les items
    *	On lui préférera dans les autres classes addItem qui appelera lui-meme addMonsterItem
    */
    void addMonsterItem (MyItem *item, bool push_front = false);

    /*!
    *	@brief Ajoute un item a la liste des eventItem
    *	@param item L'item a ajouter
    *	@param push_front Indique si l'item doit etre positionne en tete ou en queue
    *
    *	Cette méthode ne sera a priori appelée que par les items
    *	On lui préférera dans les autres classes addItem qui appelera lui-meme addEventItem
    */
    void addEventItem (MyItem *item, bool push_front = true);

    /*!
    *	@brief Ajoute un item a la liste des triggerItem
    *	@param item L'item a ajouter
    *	@param push_front Indique si l'item doit etre positionne en tete ou en queue
    *
    *	Cette méthode ne sera a priori appelée que par les items
    *	On lui préférera dans les autres classes addItem qui appelera lui-meme addTriggerItem
    */
    void addTriggerItem (MyItem *item, bool push_front = true);

    /*!
    *	@brief Cherche le premier item contenant le pixel (x,y) et le retourne
    *	@param x L'abscisse du pixel
    *	@param y L'ordonnée du pixel
    *	@return L'item sélectionné
    *
    *	Les monstres sont prioritaires sur les statics si plusieurs items se superposent
    */
    MyItem *selectItem (int x, int y);

    /*!
    *	@brief Accesseur sur l'item Babar
    *	@return Un pointeur vers le BabarItem contenu dans data
    */
    MyItem *selectBabar();

    /*!
    *	@brief Supprime l'item de la liste MAIS NE LE DELETE PAS
    *	@param item L'item a enlever
    */
    void deleteItem (MyItem *item);

    /*!
    *	@brief Fait remonter l'item dans la pile (utile pour changer l'ordre d'affichage sans toucher au zbuffer)
    *	@param item L'item à remonter
    */
    void upInStack (MyItem *item);

    /*!
    *	@brief Retire l'item de data (attention, data est indépendant de l'affichage)
    *	@param item L'objet a retirer
    */
    void removeItem (MyItem *item);

    /*!
    *	@brief Sauvegarde du niveau dans fileName
    *	@param fileName Le chemin relatif du niveau a sauvegarder
    *
    *	Data possède toutes les informations pour sauvegarder intégralement le niveau
    *	Il n'y a rien d'autre à faire pour enregistrer un .lvl
    */
    void saveData (QString fileName);
};


#endif
