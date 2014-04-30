/* 
 * File:   location.h
 * Author: stefan
 *
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

namespace hypro
{
    template<typename Number>
    class Location
    {
        private:
        /**
         * Member
         */
        
        public:
        /**
         * Constructors & Destructor
         */
        Location();
        Location(const Location& _loc);
        
        ~Location()
        {}
    };
}