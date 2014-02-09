#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class MyGraphicsView;
class QMenu;
class QAction;
class QToolBar;

/*!
*	@class MainWindow
*	@brief Gestion de la fenetre principale de l'editeur
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
    *	@brief Constructeur
    */
    MainWindow();

    /*!
    *	@brief Destructeur
    */
    ~MainWindow();

private:
    /*!
    *	@brief Initialisation des actions
    */
    void createActions();

    /*!
    *	@brief Initialisation des menus
    */
    void createMenus();

    /*!
    *	@brief Initialisation de la toolbar
    */
    void createToolBars();

    /*!
    *	@brief Charge un fichier .png
    *	@param str Nom du fichier (doit terminer par .png)
    */
    void loadFile (QString str);

    /*!
    *	@brief Enregistre le .col en fonction des modifications faites
    *	@param str Nom au format .png du fichier à sauvegarder
    */
    void saveFile (QString str);

    /*!
    *	@brief Demande a l'utilisateur s'il veut sauvegarder son travail
    */
    void warningSave();


public slots:
    void newFile();
    void open();
    void save();
    void undo();
    void aboutBabarStaticEditor();
    void setCursBox();
    void setCursLine();
    void setCursGreen();
    void setCursRed();
    void setCursErase();


private:
    MyGraphicsView *m_graphic_view; // objet principal de l'éditeur

    QGraphicsScene *m_graphic_scene; // scene liee a m_graphic_view
    bool m_opened_file; // vaut vrai si un fichier est ouvert, faux sinon
    QString m_file_name; // le nom du fichier en cours (si un fichier est ouvert)

    // variables du menu
    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_helpMenu;
    // actions possibles
    QAction *m_newAct;
    QAction *m_openAct;
    QAction *m_exitAct;
    QAction *m_saveAct;
    QAction *m_undoAct;
    QAction *m_aboutBabarStaticEditor;
    QAction *m_curs_box;
    QAction *m_curs_line;
    QAction *m_curs_green;
    QAction *m_curs_red;
    QAction *m_curs_erase;
    //barre d'outils
    QToolBar *m_fileToolBar;



};




#endif
