#include "types.h"

namespace hypro {
namespace plotting {
PLOTTYPE outputFormat( const std::string& in ) {
	if ( in == "pdf" ) return PLOTTYPE::pdf;
	if ( in == "png" ) return PLOTTYPE::png;
	if ( in == "eps" ) return PLOTTYPE::eps;
	if ( in == "gen" ) return PLOTTYPE::gen;
	if ( in == "tex" ) return PLOTTYPE::tex;
	return PLOTTYPE::nset;
}
}  // namespace plotting

}  // namespace hypro
