#include "CEGARAnalyzer.tpp"
using namespace hypro;

template class detail::CEGARAnalyzer_impl<concat<TypeList<double>, RepresentationsList<double, Converter<double>>>>;
template class detail::CEGARAnalyzer_impl<concat<TypeList<mpq_class>, RepresentationsList<mpq_class, Converter<mpq_class>>>>;

