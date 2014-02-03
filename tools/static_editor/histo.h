#ifndef _HISTO_H
#define _HISTO_H

#include <list>
#include <stack>

struct collAndPos {
	int coll;
	int i; // pos en BOX
	int j; // pos en BOX
};

class Histo {
	public:
	Histo();
	~Histo();
	
	
	std::list<collAndPos> *lastSequence();
	void popLastSequence();
	// NE CREE une sequence que si la sequence actuelle est non vide
	void newSequence();
	void saveColl(int coll, int i, int j);
	bool emptySequence();
	bool canUndo();

	private:
	std::stack< std::list<collAndPos>* > m_sequences;
};

#endif
