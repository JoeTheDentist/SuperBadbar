#ifndef BABARSTATE_H
#define BABARSTATE_H

class Babar;

/**
 *	Representation of the states for Babar
 *	State Pattern (no way! really?)
 */
class BabarState
{
public:
	/**
	 *	Ctor
	 *	@param context: context of the state
	 */
	BabarState(Babar *context);

	/**
	 *	Gets the initial state, to hide the states behind
	 *	@param context: context for the state
	 *	@return an new state
	 */
	static BabarState *GetInitialState(Babar *context);

	/**
	 *	Update
	 */
	virtual void update() = 0;

	/**
	 *	Move Up (jump & double jump)
	 */
	virtual void moveUp() = 0;

	/**
	 *	Move Down (crouch)
	 */
	virtual void moveDown() = 0;

	/**
	 *	Move Left
	 */
	virtual void moveLeft();

	/**
	 *	Move Right
	 */
	virtual void moveRight();

	/**
	 *	Fire action
	 */
	virtual void fire();

	/**
	 *	Protect action
	 */
	virtual void protect();

protected:
	bool m_wasFiring;
	bool m_wasCrouched;

	/**
	 *	Getter
	 *	@return context
	 */
	Babar *getContext();

	/**
	 *	Set the animation according to the context
	 */
	void setAnimation();

private:
	Babar *m_context;
};

#endif // BABARSTATE_H
