#ifndef UT_EXECUTIVE
#define UT_EXECUTIVE

#include "utenteBusiness.h"

class UtExecutive: public UtBusiness{
public:
    UtExecutive();
    UtExecutive(const Username&,const Profilo&, Rete* =0,string ="executive");
    UtExecutive(const UtExecutive&);
    virtual string ricercaUt(string, const Database&) const;
    virtual ~UtExecutive();


};

#endif
