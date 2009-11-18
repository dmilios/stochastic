package RandomVariable;

use strict;
use warnings;

# Expect to find "stochastic.h" in ../src relative to the script using this
# module, and libstochastic.so in the current directory...
use FindBin;
use Cwd;
use Inline C => DATA =>
    CC => 'g++' =>
    INC => "-I$FindBin::RealBin/../src" =>
    LIBS => "-L" . cwd . " -lstochastic";

# Check out the overload manpage: binary operations take a third argument
# indicating whether the operands have been swapped so that the first is of the
# right class (e.g. "7 - (RV)x" -> x.sub(7, swapped=true)).
use overload '+' => \&addRandomVariable;

# Can't use 'new' as a method name in C++, so call it _new and alias it here.
#*new = *_new;

1
__DATA__
__C__

#include "stochastic.h"

using namespace stochastic;

SV *
newFromGaussian(char *cname, double mu, double sigma)
{
  printf("newFromGaussian(%s, %g, %g)\n", cname, mu, sigma);
  RandomVariable *rv = new RandomVariable(new Gaussian(mu, sigma));
  SV *obj_ref = sv_setref_pv(newSV(0), cname, (void *) rv);
  SvREADONLY_on(SvRV(obj_ref));
  return obj_ref;
}

SV *
addRandomVariable(SV *_self, SV *_other, SV *swapped)
{
  RandomVariable *self = (RandomVariable *) SvIV(SvRV(_self));
  RandomVariable *other = (RandomVariable *) SvIV(SvRV(_other));
  printf("add(%s, %s)\n", self->getRandomVariableID().c_str(),
      other->getRandomVariableID().c_str());
  RandomVariable *rv = new RandomVariable(*self + *other);
/* Two different ways of doing this: either we can extract self's class
 * and get its name (HvNAME(stash)), and bless with the sv_setref_pv call,
 * *or* we can not bless with the sv_setref_pv call, but bless separately
 * using a direct reference to the class; I think the latter should be more
 * efficient.
 */
#if 0
  HV *stash = SvSTASH(SvRV(_self));
  SV *obj_ref = sv_setref_pv(newSV(0), HvNAME(stash), (void *) rv);
#else
  SV *obj_ref = sv_setref_pv(newSV(0), (char *) NULL, (void *) rv);
  sv_bless(obj_ref, SvSTASH(SvRV(_self)));
#endif
  SvREADONLY_on(SvRV(obj_ref));
  return obj_ref;
}

const char *
get_id(SV *obj)
{
  printf("get_id()\n");
  return ((RandomVariable *) SvIV(SvRV(obj)))->getRandomVariableID().c_str();
}

void
DESTROY(SV *obj)
{
  printf("DESTROY()\n");
  RandomVariable *rv = (RandomVariable *) SvIV(SvRV(obj));
  delete rv;
}
