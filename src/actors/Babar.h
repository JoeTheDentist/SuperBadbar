/**
 * 	@file babar.h
 * 	@brief Header de la classe Babar
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#ifndef _BABAR_
#define _BABAR_

#include <list>
#include "../sound/Sonorisable.h"
#include "../util/Analyser.h"
#include "../video/AnimPic.h"
#include "../video/AnimTable.h"
#include "../items/WeaponsArmory.h"
#include "Actor.h"
#include "../actors/ProjectilesManager.h"


#define BABAR_SPEED 15
#define JUMP_TIME 6
#define SOURCE_Y 30  /* décalage en y de la source, par rapport au haut */
#define BABAR_RESU_TIME 50

class Actor;
class CollisionsManager;
class ProjectilesManager;
class Analyser;
class Gun;
class WeaponsArmory;
class BindablePlatform;

const int c_babar_hp_max = 5;
const int c_babar_lifes = 3;


/**
 * 	@class Babar
 * 	@brief Personnage controlé par un joueur
 *
 *	Les touches enfoncées par l'utilisateur sont récupérées par
 *	keyboard, dont l'état est utilisé par les méthodes de tir, de saut,
 *	de mise à jour d'état et de vitesse
 *
 *	#############################
 *	## 	Gestion de la position ##
 *	#############################
 *	Babar possede deux attributs de position: m_pos et m_rel_pos, selon qu'il soit
 *	sur une plateforme mobile. On utilisera tant que possible les accesseurs (position())
 *	et mutateurs (move(int x, int y)) et le moins possible des acces directs au champs de position.
 *
 *	Quand Babar n'est pas sur une plateforme mobile, sa position est m_pos. Sinon, sa position vaut
 *	la somme de la position de la plateforme et de m_rel_pos. Ces attributs doivent etre utilises
 *	directement le moins possible!
 *
 *	########################
 *	## 	Gestion des vies  ##
 *	########################
 *	Babar possede des points de vies (HP). Quand il n'a plus de HP, il perd une vie (life).
 *	Quand il perd une vie, on attend un certain temps puis babar respawn sur le dernier static
 *	sur lequel il etait. Quand il n'a plus de vies, Game over!
 *	Il ne faut pas confondre HP (petites vies) et lifes (grandes vies)
 *	Babar peut recuperer des HP avec les coeurs
 *
 *
 *	@warning Dans cette classe, m_pos ne represente pas toujours la position (cf m_rel_pos)
 *
 */
class Babar: public Actor, public Sonorisable {
    protected:
        unsigned int m_fire_phase;	        /* phase du tir */
        int m_hp;                        	/* nombre de points de vies */
		int m_lifes;						/* nombre de vies */
        int m_invincible;                   /* durée d'invicibilité après avoir été touché */
        int m_crouch_time;                  /* durée depuis laquelle le joueur demande à être accroupis */
        bool m_ready_double_jump;           /* booléen autorisant le double saut */
        bool m_ready_jump;                  /* booleen autorisant le saut */
        bool m_jump;						/* indique que le joueur est en cours de saut (sa vitesse augment) */
        bool m_double_jump;		            /* vaut vrai si Babar est en cours de double saut */

        WeaponsArmory m_weapons_armory;
        BindablePlatform *m_bind;			/* plateforme à laquelle est lié Babar (s'il y en a une) */
        Rect m_rel_pos;					/* position dans le référentiel de la plateforme m_bind (si m_bind != NULL)*/
        bool m_fire;                        /* booléen indiquant si Babar est en train de tirer */
        int m_peanuts;
		int m_lock;
        Rect m_last_pos;                    /* dernière position sur qqch */

        /**
         * 	@brief Charge les images de babar
         *	@param age	L'age de Babar
         */
        void load_anim(char age);
        bool is_on_something();
    public:

        /**
         * 	@brief Constructeur
         *	@param keyboard L'utilitaire qui récupère les entrées clavier du joueur
         *	@param static_data Les données du niveau
         *	@param sound_manager Le gestionnaire de son
         *  @param analyser ouvert sur un fichier lvl, en l'occurence du premier level
         */
        Babar(Analyser *analyser);

        /**
         * 	@brief Destructeur
         */
        ~Babar();

        /**
         *  @brief Charge les attributs de Babar propre au lvl
         *  @param a Analyser ouvert sur le fichier level contenant les coordonnées et l'age de Babar
         */
        void init_babar(Analyser * a);

        /*!
         *	@brief Surcharge de l'accesseur de sprite pour avoir la position meme quand babar est binded
         * 	@return La position actuelle de babar
        */
        virtual Rect position() const;

		/*!
		 *	@brief Mutateur: augmente la position de babar de x et y sans tenir compte des collisions
		 *	@param x Le deplacement x
		 *	@param y Le deplacement y
		*/
        virtual void move(int x, int y);

        /*!
         *	@brief Met à jour la position du sprite
         *	@param static_data Données du jeu
         *	@param CollisionsManager Gestionnaire de collisions
        */
        void update_pos();


        /**
         * 	@brief Met à jour la vitesse de Babar
         */
        void update_speed();

        /**
         * 	@brief Met à jour l'état et la direction de Babar
         *	@param static_data Données du niveau
         *	@param CollisionsManager Gestionnaire de collision
         *	@param ProjectilesManager Gestionnaire des projectiles
         */

        void update_state();

        /**
         * 	@brief Mise à jour de la direction de Babar en fonction des touches enfoncées
         */
        void update_direction();

        /**
         * 	@brief Indique si Babar peut tirer
         *	@return Vrai si Babar peut tirer
         *
         *	On considère que "Babar peut tirer" si la touche
         *	tirer est enfoncée et s'il est autorisé à tirer
         */
        bool can_fire();

        /**
         * 	@brief Fait tirer Babar
         *	@return La liste de projectiles tirés
         */
        std::list<Projectile*> *fire(int num_player = 1);

        /**
         *  @brief si le joueur demande a marcher et qu'il n'y a rien d'autre
         */
        bool can_walk() const;



        /**
         *  @brief si le joueur demande a s'accroupir
         */
        bool can_crouch() const;

        /**
         *  @brief fait s'accroupir
         */
        void crouch();

        /**
         * 	@brief Indique si Babar peut sauter
         *	@return Vrai si Babar peut sauter
         *
         *	On considère que "Babar peut sauter" si la touche
         *	sauter est enfoncée et s'il est autorisé à sauter
         */
        bool can_jump() const;

        /**
         * 	@brief Fait sauter Babar
         */
        void jump();

        /**
         * 	@brief  Indique si Babar peut faire un double saut
         *	@return Vrai si Babar peut faire un double saut
         *
         *	On considère que "Babar peut faire un double saut" si la touche
         *	sauter est enfoncée et s'il est autorisé à faire un double saut
         */
        bool can_double_jump() const;

        /**
         * 	@brief Fait resauter Bababr
         */
        void double_jump();

        /**
         * 	@brief Indique si Babar peut traverser la plateforme sur laquelle il est
         *	@return vrai si bas et espace sont appuyes, si l'état de babar permet de descendre et si babar est sur un objet de collision bas
         */
        bool can_go_down() const;

        /**
         * 	@brief Effectue la traversee d'une surface de collision bas si elle repond aux criteres de traversee
         *	@param CollisionsManager Le gestionnaire de collisions
         */
        void go_down();

        /**
         * 	@brief Donne une nouvelle arme à Babar
         *	@param weapon La nouvelle arme
         */
        void add_weapon(weapon_type weapon);

        /**
         * 	@brief Accesseur
         *	@return Vrai si Babar est invincible
         */
        bool is_invincible() const;

        /**
         * 	@brief Accesseur
         *	@return Le nombre de points de vies de Babar
         */
        int HP() const;

        /**
         * 	@brief Accesseur
         *	@return Le nombre de vies de Babar
         */
        int lifes() const;

        /**
         * 	@brief Accesseur
         *	@return Le nombre de munitions de l'arme actuelle de Babar
         */
        int munitions() ;

        /**
         * 	@brief Accesseur
         *	@return Le type de l'arme actuelle de Babar
         */
        weapon_type type_of_weapon();

        /**
         * 	@brief Mutateur: fait perdre des vies à Babar et le rend invincible qq secondes
         *	@param damages Le nombre de points de vies à faire perdre
         */
        void damage(int damages);

        /**
         * 	@brief Mutateur: fait gagner des vies a Babar
         *	@param lifes Le nombre de vies à faire gagner
         */
        void lifesup(int lifes);

        /**
         * 	@brief Mutateur: fait gagner des points de vies a Babar
         *	@param HP Le nombre de points de vies à faire gagner
         */
        void HPup(int HP);

		/**
		 *	@brief Tue Babar (fait perdre une vie)
		 */
		void die();

		void lock(int time);
		void unlock();

		bool locked() const;

        /**
         * 	@brief Accesseur
         *	@return La vitesse actuelle de Babar
         */
        Rect speed() const;


        /**
         * 	@brief Accesseur
         *	@return Return vrai si babar est lié à une plateforme
         */
        bool binded() const;

        /**
         * 	@brief Lie babar à la plateforme
         *	@param platform plateforme à lier
         */
        void bind(BindablePlatform *platform);

        /**
         * 	@brief Délie babar de sa plateforme
         */
        void unbind();

        /**
         * 	@brief Accesseur
         *	@return Le nombre de cacahuetes possede par babar
         */
        int peanuts();

        /**
         * 	@brief Mutateur: incremente le nombre de cacahutes
         *	@param peanuts Le nombre de cacahuetes a ajouter
         */
        void incr_peanuts(int peanuts);

		/*!
		*	@brief Accesseur
		*	@return L'etat de babar
		*/
        state_player get_state() const;

		/*!
		*	@brief Interromp le saut
		*/
        void interrupt_jump();

		/*!
		*	@brief Interromp l'accroupissement
		*/
        void interrupt_crouch();

		/*!
		*	@brief Unbind babar d'une plateforme s'il doit l'etre
		*	@return vrai si babar a été unbinded
		*/
        bool check_unbind();

        /**
         *  @brief Remet babar à sa position de dernière collision
         */
        void set_last_pos();

		/**!
		 * 	@brief Mutateur
		 *	@param h La nouvelle hauteur de babar
		 */
		virtual void set_h(int h) { m_pos.h = h; m_rel_pos.h = h;}

		/**!
		 * 	@brief Mutateur
		 *	@param h La nouvelle hauteur de babar
		 */
		virtual void set_w(int w) { m_pos.w = w; m_rel_pos.w = w;}

		void set_peanuts(int pean);

		void set_lifes(int life);
};

#endif


