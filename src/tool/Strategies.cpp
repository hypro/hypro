
// #include "Strategies.h"

// namespace hydra {
// namespace strategies {

// static hypro::Strategy<State> test_1 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1})});

// // box_agg, refine with precise sf_agg
// static hypro::Strategy<State> tacas18_1 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::NO_AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// // box_agg, refine with precise sf_no_agg
// static hypro::Strategy<State> tacas18_2 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::NO_AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::NO_AGG, -1})});

// // box_agg, refine with sf_no_agg
// static hypro::Strategy<State> tacas18_3 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::NO_AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::NO_AGG, -1})});

// static hypro::Strategy<State> tacas18_4 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(10000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> tacas18_5 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> tacas18_6 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(10000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> tacas18_7 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> tacas18_8 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<HPolyType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> tacas18_9 = hypro::Strategy<State>({
//     hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//     hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, 3}),
//     hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, 3})
//     //,hypro::StrategyNode<SFType>({tNumber(1)/tNumber(100),
//     // hypro::AGG_SETTING::AGG, -1})
// });

// static hypro::Strategy<State> adhs18_1 = hypro::Strategy<State>(
//     {hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> adhs18_2 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> adhs18_3 = hypro::Strategy<State>(
//     {hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> adhs18_4 = hypro::Strategy<State>(
//     {hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::NO_AGG, 5})});

// static hypro::Strategy<State> adhs18_5 = hypro::Strategy<State>(
//     {hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> adhs18_6 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> adhs18_7 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::NO_AGG, 3})});

// static hypro::Strategy<State> adhs18_8 = hypro::Strategy<State>(
//     {hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> tacas_poster = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(50), hypro::AGG_SETTING::AGG, -1})
//      //,hypro::StrategyNode<SFType>({tNumber(1)/tNumber(50),
//      // hypro::AGG_SETTING::NO_AGG, 3})
//      ,
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(250), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> fastScout = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> singleSF =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> fmi18_1 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> fmi18_2 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> fmi18_3 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> fmi18_4 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> fmi18_5 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> fmi18_6 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_1 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(500), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_2 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(250), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_3 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(200), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_4 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>(
//          {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1}),
//      hypro::StrategyNode<SFType>(
//          {tNumber(1) / tNumber(3), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_5 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(3), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_6 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_7 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(5000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_8 = hypro::Strategy<State>(
//     {hypro::StrategyNode<SFType>({tNumber(1), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_9 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>({tNumber(1), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_10 = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>({tNumber(1), hypro::AGG_SETTING::AGG, -1})});

// // static hypro::Strategy<State> arch19_11 = hypro::Strategy<State>({
// //	hypro::StrategyNode<BoxType>({tNumber(1), hypro::AGG_SETTING::AGG, -1})
// //});

// static hypro::Strategy<State> arch19_motorcade_box = hypro::Strategy<State>(
//     {hypro::StrategyNode<BoxType>({tNumber(10), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> arch19_motorcade_sf = hypro::Strategy<State>(
//     {hypro::StrategyNode<SFType>({tNumber(10), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> diss_1 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::NO_AGG, -1})});

// static hypro::Strategy<State> diss_2 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> unravel_1 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(2), hypro::AGG_SETTING::MODEL, -1})});

// static hypro::Strategy<State> unravel_2 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// // static hypro::Strategy<State> diss_4 = hypro::Strategy<State>({
// //	hypro::StrategyNode<SFType>({tNumber(1)/tNumber(100),
// // hypro::AGG_SETTING::AGG, -1})
// //	,hypro::StrategyNode<SFType>({tNumber(1)/tNumber(200),
// // hypro::AGG_SETTING::AGG, -1})
// //	,hypro::StrategyNode<SFType>({tNumber(1)/tNumber(1000),
// // hypro::AGG_SETTING::AGG, -1})
// //});

// static hypro::Strategy<State> unravel_3 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> unravel_4 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::NO_AGG, -1})});

// static hypro::Strategy<State> unravel_5 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, 3})});

// static hypro::Strategy<State> unravel_6 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> unravel_7 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> unravel_8 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> unravel_9 =
//     hypro::Strategy<State>({hypro::StrategyNode<HPolyType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> unravel_10 =
//     hypro::Strategy<State>({hypro::StrategyNode<HPolyType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> unravel_11 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(5), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> unravel_12 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(2), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> unravel_13 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(1), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> b1 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> b01 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> b001 =
//     hypro::Strategy<State>({hypro::StrategyNode<BoxType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> h01 =
//     hypro::Strategy<State>({hypro::StrategyNode<HPolyType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> h001 =
//     hypro::Strategy<State>({hypro::StrategyNode<HPolyType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> v01 =
//     hypro::Strategy<State>({hypro::StrategyNode<VPolyType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> v001 =
//     hypro::Strategy<State>({hypro::StrategyNode<VPolyType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> z01 =
//     hypro::Strategy<State>({hypro::StrategyNode<ZonotopeType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> z001 =
//     hypro::Strategy<State>({hypro::StrategyNode<ZonotopeType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> s50 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(5) / tNumber(1), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> s20 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(2) / tNumber(1), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> s10 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(1), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> s1 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(10), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> s01 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> s001 =
//     hypro::Strategy<State>({hypro::StrategyNode<SFType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});

// #ifdef HYPRO_USE_PPL
// static hypro::Strategy<State> p01 =
//     hypro::Strategy<State>({hypro::StrategyNode<PolytopeType>(
//         {tNumber(1) / tNumber(100), hypro::AGG_SETTING::AGG, -1})});

// static hypro::Strategy<State> p001 =
//     hypro::Strategy<State>({hypro::StrategyNode<PolytopeType>(
//         {tNumber(1) / tNumber(1000), hypro::AGG_SETTING::AGG, -1})});
// #endif

// static const std::map<std::string, hypro::Strategy<State>> strategies = {
//     {"test_1", test_1},
//     {"tacas18_1", tacas18_1},
//     {"tacas18_2", tacas18_2},
//     {"tacas18_3", tacas18_3},
//     {"tacas18_4", tacas18_4},
//     {"tacas18_5", tacas18_5},
//     {"tacas18_6", tacas18_6},
//     {"tacas18_7", tacas18_7},
//     {"tacas18_8", tacas18_8},
//     {"tacas18_9", tacas18_9},
//     {"adhs18_1", adhs18_1},
//     {"adhs18_2", adhs18_2},
//     {"adhs18_3", adhs18_3},
//     {"adhs18_4", adhs18_4},
//     {"adhs18_5", adhs18_5},
//     {"adhs18_6", adhs18_6},
//     {"adhs18_7", adhs18_7},
//     {"adhs18_8", adhs18_8},
//     {"tacas_poster", tacas_poster},
//     {"fastScout", fastScout},
//     {"singleSF", singleSF},
//     {"fmi18_1", fmi18_1},
//     {"fmi18_2", fmi18_2},
//     {"fmi18_3", fmi18_3},
//     {"fmi18_4", fmi18_4},
//     {"fmi18_5", fmi18_5},
//     {"fmi18_6", fmi18_6},
//     {"arch19_1", arch19_1},
//     {"arch19_2", arch19_2},
//     {"arch19_3", arch19_3},
//     {"arch19_4", arch19_4},
//     {"arch19_5", arch19_5},
//     {"arch19_6", arch19_6},
//     {"arch19_7", arch19_7},
//     {"arch19_8", arch19_8},
//     {"arch19_9", arch19_9},
//     {"arch19_10", arch19_10}
//     //,{"arch19_11", arch19_11}
//     ,
//     {"arch19_motorcade_box", arch19_motorcade_box},
//     {"arch19_motorcade_sf", arch19_motorcade_sf},
//     {"diss_1", diss_1},
//     {"diss_2", diss_2},
//     {"unravel_1", unravel_1},
//     {"unravel_2", unravel_2},
//     {"unravel_3", unravel_3},
//     {"unravel_4", unravel_4},
//     {"unravel_5", unravel_5},
//     {"unravel_6", unravel_6},
//     {"unravel_7", unravel_7},
//     {"unravel_8", unravel_8},
//     {"unravel_9", unravel_9},
//     {"unravel_10", unravel_10},
//     {"unravel_11", unravel_11},
//     {"unravel_12", unravel_12},
//     {"unravel_13", unravel_13},
//     {"b1", b1},
//     {"b01", b01},
//     {"b001", b001},
//     {"h01", h01},
//     {"h001", h001},
//     {"v01", v01},
//     {"v001", v001},
//     {"z01", z01},
//     {"z001", z001},
//     {"s50", s50},
//     {"s20", s20},
//     {"s10", s10},
//     {"s1", s1},
//     {"s01", s01},
//     {"s001", s001}
// #ifdef HYPRO_USE_PPL
//     ,
//     {"p01", p01},
//     {"p001", p001}
// #endif
//     //,{"diss_3", diss_3}
//     //,{"diss_4", diss_4}
// };
// } // namespace strategies

// std::map<std::string, hypro::Strategy<State>> getStrategiesMap() {
//   return strategies::strategies;
// }

// hypro::Strategy<State> getStrategyFromName(const std::string &name) {

//   auto it = strategies::strategies.find(name);
//   if (it != strategies::strategies.end()) {
//     TRACE("hydra.strategies",
//           "Using given strategy " << std::string(it->first) << std::endl);
//     return it->second;
//   } else {
//     CERR("Strategy string did not match a valid strategy.\n");
//     exit(1);
//   }
// }

// } // namespace hydra
