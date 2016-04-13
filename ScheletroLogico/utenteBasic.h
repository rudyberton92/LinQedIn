#ifndef UT_BASIC
#define UT_BASIC

#include "utente.h"

class UtBasic: public Utente{
public:
    UtBasic();
    UtBasic(const Username&, const Profilo&, Rete* =0, string ="basic");
    UtBasic(const UtBasic&);
    virtual string ricercaUt(string, const Database&) const;
    virtual ~UtBasic();
};
#endif
