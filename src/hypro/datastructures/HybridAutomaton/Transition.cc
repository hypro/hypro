#include "lib/datastructures/HybridAutomaton/Transition.h"

namespace hydra
{
std::ostream& operator<<(std::ostream& ostr, const Transition& t)
{
#ifdef HYDRA_USE_LOGGING
    ostr << "transition(" << std::endl
          << "\t Source = " << t.getSource()->getId() << std::endl
          << "\t Target = " << t.getTarget()->getId() << std::endl
          << "\t urgent = " << t.isUrgent() << std::endl
          << "\t Guard = " << t.getGuard() << std::endl
          << "\t Reset = " << t.getReset() << std::endl
          << ")";
#endif
    return ostr;
}

bool operator==(const Transition& lhs, const Transition& rhs)
{
	if( (*lhs.mSource != *rhs.mSource) ||
		(*lhs.mTarget != *rhs.mTarget) ||
		(lhs.mUrgent != rhs.mUrgent) ||
		(lhs.mGuard != rhs.mGuard) ||
		(lhs.mReset != rhs.mReset) ) {
		return false;
	}

	return true;
}
}
