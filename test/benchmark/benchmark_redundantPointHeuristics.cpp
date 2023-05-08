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
                    points[std::make_pair(dim, numberPoints)].emplace_back(coordinates);
                }
            }
            return mapIt->second;
        }

    private:
        static std::map<std::pair<std::size_t, std::size_t>, std::vector<hypro::Point<double>>> points;
    };


    static void WithHeuristic(::benchmark::State &st) {
        std::size_t reduction = 0;
        auto points = Fixture::getPoints(st.range(0), st.range(1));
        for (auto _: st) {
            auto newPoints = hypro::removeRedundantPoints<double, true>(points);
            reduction += points.size() - newPoints.size();
        }
        st.counters["reduction"] = ::benchmark::Counter(reduction);
    }

    static void WithoutHeuristic(::benchmark::State &st) {
        std::size_t reduction = 0;
        auto points = Fixture::getPoints(st.range(0), st.range(1));
        for (auto _: st) {
            auto newPoints = hypro::removeRedundantPoints<double, false>(points);
            reduction += points.size() - newPoints.size();
        }
        st.counters["reduction"] = ::benchmark::Counter(reduction);
    }

    BENCHMARK(WithHeuristic)->Ranges({{1, 10},
                                      {5, 100}});
    BENCHMARK(WithoutHeuristic)->Ranges({{1, 10},
                                         {5, 100}});

}  // namespace hypro::benchmark
