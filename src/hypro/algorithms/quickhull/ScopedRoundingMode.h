#pragma once

#include <cfenv>
/**
 * Sets the rounding mode to the value given to the constructor and resets it back to its previous value upon destruction.
 */
class ScopedRoundingMode {
    int previousRoundMode;
public:
    ScopedRoundingMode(int roundingMode) {
        previousRoundMode = std::fegetround();
        std::fesetround(roundingMode);
    }

    ~ScopedRoundingMode() {
        std::fesetround(previousRoundMode);
    }

    //Disallow heap allocation because that makes no sense for this class
private:
    void *operator new( size_t );
    void operator delete( void* );
    void *operator new[]( size_t );
    void operator delete[]( void* );
};