#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

//BOOST_FUSION_ADAPT_STRUCT( hypro::parser::Monomial ,
//							   ( std::vector<std::string>, mVariables ) ( std::vector<unsigned>, mExponents ) )

BOOST_FUSION_ADAPT_STRUCT( hypro::parser::Monomial ,
							   ( std::vector<std::string>, mVariables ) )

BOOST_FUSION_ADAPT_TPL_STRUCT( ( Number ) , ( hypro::parser::Term )( Number ),
							   ( Number, mCoefficient ) ( hypro::parser::Monomial, mMonomial ) )

BOOST_FUSION_ADAPT_TPL_STRUCT( ( Number ) , ( hypro::parser::Polynomial )( Number ),
							   ( std::vector<hypro::parser::Term<Number>>, mTerms ) )

BOOST_FUSION_ADAPT_TPL_STRUCT( ( Number ), ( hypro::parser::Matrix )( Number ),
							   ( std::string, mName )( std::vector<std::vector<Number> >, mMatrix ) )

BOOST_FUSION_ADAPT_TPL_STRUCT( ( Number ), ( hypro::parser::State )( Number ),
							   ( unsigned, mName )( hypro::parser::Matrix<Number>,
													mFlow )( hypro::parser::Matrix<Number>, mInvariant ) )

BOOST_FUSION_ADAPT_TPL_STRUCT( ( Number ), ( hypro::parser::Transition )( Number ),
							   ( int, mId )( unsigned, mName )( unsigned, mSource )( unsigned, mTarget )(
									 hypro::parser::Matrix<Number>, mGuard )( hypro::parser::Matrix<Number>, mReset ) )