/*
 * Created by stefan on 06.09.21.
 */

#ifndef HYPRO_PATHUTIL_H
#define HYPRO_PATHUTIL_H

#include "Pathv2.h"

namespace hypro {

template <typename N>
bool has_discrete_cycle( const Path<N>& path ) {
	for ( auto cur_it = std::begin( path.elements ); cur_it != std::end( path.elements ); ++cur_it ) {
		if ( std::find_if( std::next( cur_it ), std::end( path.elements ), [&cur_it]( const auto& elem ) { return elem.second == cur_it->second; } ) != std::end( path.elements ) ) {
			// std::cout << "Path " << path << " has a discrete cycle with location " << ( ( cur_it )->second->getTarget()->getName() ) << std::endl;
			return true;
		}
	}
	return false;
}

}  // namespace hypro

#endif	// HYPRO_PATHUTIL_H
