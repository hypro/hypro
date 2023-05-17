/*
 * Copyright (c) 2021-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <benchmark/benchmark.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <random>
#include <string>

namespace hypro::benchmark {

    class Fixture {
    public:

        static const std::vector<hypro::Point<double>> &getPoints(std::size_t dim, std::size_t numberPoints) {
            static std::map<std::pair<std::size_t, std::size_t>, std::vector<hypro::Point<double>>> points;
            auto mapIt = points.find(std::make_pair(dim, numberPoints));
            if (mapIt == std::end(points)) {
                mapIt = points.insert(
                        std::make_pair(std::make_pair(dim, numberPoints), std::vector<hypro::Point<double>>{})).first;
                std::mt19937 generator;
                std::uniform_real_distribution<double> dist = std::uniform_real_distribution<double>(-1.0, 1.0);
                for (std::size_t p = 0; p < numberPoints; ++p) {
                    std::vector<double> coordinates;
                    for (std::size_t i = 0; i < dim; ++i) {
                        coordinates.emplace_back(dist(generator));
                    }
                    mapIt->second.emplace_back(coordinates);
                }
            }
            return mapIt->second;
        }

    private:

    };


    static void WithHeuristic(::benchmark::State &st) {
        std::size_t reduction = 0;
        auto points = Fixture::getPoints(st.range(0), st.range(1));
        for (auto _: st) {
            auto newPoints = hypro::removeRedundantPoints<double, true>(points);
            reduction += points.size() - newPoints.size();
        }
        st.counters["reduction"] = ::benchmark::Counter(reduction);
        st.counters["dimension"] = st.range(0);
        st.counters["points"] = st.range(1);
    }

    static void WithoutHeuristic(::benchmark::State &st) {
        std::size_t reduction = 0;
        auto points = Fixture::getPoints(st.range(0), st.range(1));
        for (auto _: st) {
            auto newPoints = hypro::removeRedundantPoints<double, false>(points);
            reduction += points.size() - newPoints.size();
        }
        st.counters["reduction"] = ::benchmark::Counter(reduction);
        st.counters["dimension"] = st.range(0);
        st.counters["points"] = st.range(1);
    }

    static void Comparison(::benchmark::State &st) {
        std::size_t reduction = 0;
        auto points = Fixture::getPoints(st.range(0), st.range(1));
        for (auto _: st) {
            auto noHeuristics = hypro::removeRedundantPoints<double, false>(points);
            auto heuristics = hypro::removeRedundantPoints<double, true>(points);
            st.PauseTiming();
            if (noHeuristics != heuristics) {
                std::cout << "Resulting point sets from reduction are not equal. Original point set: ";
                for (const auto &p: points) {
                    std::cout << "\n" << p;
                }
                std::cout << "\nReduced set using no heuristics: ";
                for (const auto &p: noHeuristics) {
                    std::cout << "\n" << p;
                }
                std::cout << "\nReduced set using heuristics: ";
                for (const auto &p: heuristics) {
                    std::cout << "\n" << p;
                }
                std::cout << "\n";
            }
            st.ResumeTiming();
        }
        st.counters["reduction"] = ::benchmark::Counter(reduction);
        st.counters["dimension"] = st.range(0);
        st.counters["points"] = st.range(1);
    }

    BENCHMARK(WithHeuristic)->Name("WithHeuristic")->Ranges({{1, 10},
                                                             {5, 100}});
    BENCHMARK(WithoutHeuristic)->Name("WithoutHeuristic")->Ranges({{1, 10},
                                                                   {5, 100}});
    BENCHMARK(Comparison)->Ranges({{1, 10},
                                   {5, 10}});

}  // namespace hypro::benchmark
