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
	 *	@param context of the state
	 */
	BabarState(Babar *context);

	/**
	 *	Move Up
	 */
	virtual void moveUp() = 0;

	virtual void moveDown() = 0;

protected:
	/**
	 *	Getter
	 *	@return context
	 */
	Babar *getContext();

private:
	Babar *m_context;
};

#endif // BABARSTATE_H
