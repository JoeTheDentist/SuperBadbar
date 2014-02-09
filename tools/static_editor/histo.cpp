#include "histo.h"
#include "collitem.h"
#include <iostream>

Histo::Histo()
{
}

Histo::~Histo()
{
}


std::list<collAndPos> *Histo::lastSequence()
{
    return m_sequences.top();
}

void Histo::popLastSequence()
{
    m_sequences.pop();
}

void Histo::newSequence()
{
    if (m_sequences.empty() || !emptySequence() )
        m_sequences.push (new std::list<collAndPos>() );
}

void Histo::saveColl (int coll, int i, int j)
{
    collAndPos plop;
    plop.coll = coll;
    plop.i = i;
    plop.j = j;
    m_sequences.top()->push_front (plop);
    // si on pushback, la suppression se fera à l'envers
    // => effets non désirés
}

bool Histo::emptySequence()
{
    return m_sequences.top()->empty();
}

bool Histo::canUndo()
{
    return !m_sequences.empty();
}
