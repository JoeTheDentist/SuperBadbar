#ifndef ANIM_H_INCLUDED
#define ANIM_H_INCLUDED

#include "video/Surface.h"

class Surface;

/* Cyclique, a supprimer a la fin, a laisser sur la derniere image */
enum anim_type {
	CYCLE, ENDED, NOEND
};

class Anim {
protected:
	int m_curr;                 /* image courante */
	int m_size;                 /* nombre d'images stockees */
	anim_type m_type;           /* type de l'animation */
	bool m_finished;            /* si l'animation peut etre interrompue */
	int m_phase;                /* nombre de cycle depuis lequel l'animation a ete cree */

public:

	virtual ~Anim() {}
	/**
	 * @brief Image a afficher.
	 * @return l'image de l'animation a afficher, et MET A JOUR !!! l'image suivante.
 */
	virtual Surface * curr_pic()=0;

	/**
	 * @brief Passe a l'image suivante
	 */
	virtual void next_pic()=0;

	/**
	 * @brief si on peut interrompre l'animation.
	 * @return booleen, true si on peut l'interrompre.
	 */
	virtual bool interruptable()=0;

	/**
	 * @brief si on peut supprimer l'animation.
	 * @return booleen, true si on peut la suppr.
	 */
	virtual bool deletable()=0;

	/**
	 *  @brief Set hauteur et largeur en fonction de l'image courante
	 *  @param pos Rect a modifier
	 */
	virtual void set_rect(Rect &pos)=0;

	/**
	 * @brief Set phase
	 * @param Nouvelle phase
	 */
	virtual void set_img(int p)=0;
};

#endif // ANIM_H_INCLUDED
