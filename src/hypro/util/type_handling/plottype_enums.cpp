#include "hypro/util/type_handling/plottype_enums.h"

namespace hypro::plotting {

PLOTTYPE outputFormat( const std::string& in ) {
	if ( in == "pdf" ) return PLOTTYPE::pdf;
	if ( in == "png" ) return PLOTTYPE::png;
	if ( in == "eps" ) return PLOTTYPE::eps;
	if ( in == "gen" ) return PLOTTYPE::gen;
	if ( in == "tex" ) return PLOTTYPE::tex;
	return PLOTTYPE::nset;
}

std::string to_string( PLOTTYPE in ) {
	if ( in == PLOTTYPE::pdf ) return "pdf";
	if ( in == PLOTTYPE::png ) return "png";
	if ( in == PLOTTYPE::eps ) return "eps";
	if ( in == PLOTTYPE::gen ) return "gen";
	if ( in == PLOTTYPE::tex ) return "tex";
	return "";
}

}  // namespace hypro::plotting
