#include "Spinlock.h"

namespace hypro {
void Spinlock::lock() {
	while ( state_.test_and_set( std::memory_order_acquire ) ) {
		/* busy-wait */
	}
}

void Spinlock::unlock() {
	state_.clear( std::memory_order_release );
}
}  // namespace hypro
