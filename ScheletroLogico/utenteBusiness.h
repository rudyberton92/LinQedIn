#ifndef UT_BUSINESS
#define UT_BUSINESS

#include "utenteBasic.h"

class UtBusiness: public UtBasic{
public:
    UtBusiness();
    UtBusiness(const Username&,const Profilo&, Rete* =0, string ="business");
    UtBusiness(const UtBusiness&);
    virtual string ricercaUt(string, const Database&) const;
    virtual ~UtBusiness();
};

#endif
