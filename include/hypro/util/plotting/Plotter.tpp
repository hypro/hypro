/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Plotter.h"

#include <future>

namespace hypro {

    template<typename Number>
    Plotter<Number>::~Plotter() {
        while (!gnuplotThreads.empty()) {
            auto &oldestTask = gnuplotThreads.front();
            oldestTask.wait();
            gnuplotThreads.pop();
        }
    }

    template<typename Number>
    void Plotter<Number>::setFilename(const std::string &_filename) {
        mSettings.filename = _filename;
        mSettings.name = _filename;
        std::replace(mSettings.name.begin(), mSettings.name.end(), '_', '-');
    }

    template<typename Number>
    void Plotter<Number>::updateSettings(const plotting::gnuplotSettings &_settings) {
        mSettings = _settings;
    }

    template<typename Number>
    const plotting::gnuplotSettings &Plotter<Number>::settings() const {
        return mSettings;
    }

    template<typename Number>
    plotting::gnuplotSettings &Plotter<Number>::rSettings() {
        return mSettings;
    }

    template<typename Number>
    void Plotter<Number>::plot2d(PLOTTYPE outformat, bool runGnuplot) const {
        std::size_t cnt = 0;
        std::string filename = mSettings.filename;
        std::string title = mSettings.name;
        if (!mSettings.overwriteFiles) {
            while (file_exists(filename + "_" + plotting::to_string(outformat) + ".plt")) {
                std::stringstream ss;
                ss << mSettings.filename << "-" << cnt;
                filename = ss.str();
                ++cnt;
            }
        }

        mOutfile.open(filename + "_" + plotting::to_string(outformat) + ".plt");

        if ((!mObjects.empty() && !mObjects.begin()->second.vertices.empty()) || !mPoints.empty() ||
            !mVectors.empty()) {  // || mSettings.dimensions() != std::pair<unsigned,unsigned>()) {

            // preamble
            mOutfile << "# settings\n";
            if (mSettings.title) {
                mOutfile << "set title \"" << mSettings.name << "\"\n";
            }
            if (mSettings.keepAspectRatio) {
                mOutfile << "set size ratio -1\n";
            }

            switch (outformat) {
                case PLOTTYPE::pdf:
                    // mOutfile << "set term pdf font ',10'\n";
                    mOutfile << "set term pdfcairo enhanced crop font ',10'\n";
                    break;
                case PLOTTYPE::tex:
                    mOutfile
                            << "set terminal lua tikz latex standalone color header \"\\\\usepackage[T1]{fontenc}\\\n\\\\usepackage{mathptmx}\\\n\\\\usepackage{helvet}\\\n\\\\usepackage{amsmath}\"\n";
                    break;
                case PLOTTYPE::eps:
                    mOutfile << "set terminal postscript eps  enhanced color font 'Helvetica,20' linewidth 2\n";
                    break;
                case PLOTTYPE::png:
                    mOutfile << "set terminal png size " << mSettings.resolution.first << ","
                             << mSettings.resolution.second << "\n";
                    break;
                default:
                    break;
            }

            mOutfile << "set output \"" << filename << "." + plotting::to_string(outformat) + "\n";

            // gen-format has to be written manually
            if (outformat != PLOTTYPE::gen) {
                writeGnuplot();
            } else {
                writeGen();
            }
        }
        mOutfile.close();

        if (runGnuplot) {
#ifdef GNUPLOT_FOUND
            std::stringstream ss;
            ss << "gnuplot " + filename + "_" + plotting::to_string(outformat) + ".plt";
            // if there are already many plotting tasks running, wait for the oldest one to finish
            if (gnuplotThreads.size() >= std::thread::hardware_concurrency()) {
                auto &oldestTask = gnuplotThreads.front();
                oldestTask.wait();
                gnuplotThreads.pop();
            }
            gnuplotThreads.emplace(std::async(std::launch::async, [&]() { std::system(ss.str().c_str()); }));
#endif
        }
    }

    template<typename Number>
    void Plotter<Number>::plotTex() const {
        plot2d(PLOTTYPE::tex);
    }

    template<typename Number>
    void Plotter<Number>::plotEps() const {
        plot2d(PLOTTYPE::eps);
    }

    template<typename Number>
    void Plotter<Number>::plotPng() const {
        plot2d(PLOTTYPE::png);
    }

    template<typename Number>
    void Plotter<Number>::plotGen() const {
        plot2d(PLOTTYPE::gen);
    }

    template<typename Number>
    unsigned Plotter<Number>::addObject(const std::vector<Point<Number>> &_points, std::optional<std::size_t> _color,
                                        std::optional<plotting::gnuplotSettings> settings) {
        return addObject(_points, "", _color, settings);
    }

    template<typename Number>
    unsigned Plotter<Number>::addObject(const std::vector<Point<Number>> &_points, std::string _objectTitle,
                                        std::optional<std::size_t> _color,
                                        std::optional<plotting::gnuplotSettings> settings, bool isPoints) {
        TRACE("hypro.plotter", "");
        // reduce dimensions
        if (!_points.empty()) {
            if (_points.begin()->dimension() != 2) {
                WARN("hypro.plotting", "Attempted to plot an object that is not 2-dimensional. Object was skipped.")
                return 0;
            }
            updateLimits(_points);
            mObjects.insert(std::make_pair(mId, plotting::PlotObject<Number>{_points, false, false, _color, settings,
                                                                             _objectTitle, isPoints}));
            mId++;
            return (mId - 1);
        }
        return 0;
    }

    template<typename Number>
    unsigned
    Plotter<Number>::addOrderedObject(const std::vector<Point<Number>> &_points, std::optional<std::size_t> _color,
                                      std::optional<plotting::gnuplotSettings> settings) {
        TRACE("hypro.plotter", "");
        // reduce dimensions
        if (!_points.empty()) {
            if (_points.begin()->dimension() != 2) {
                WARN("hypro.plotting", "Attempted to plot an object that is not 2-dimensional. Object was skipped.")
                return 0;
            }
            updateLimits(_points);
            mObjects.insert(std::make_pair(mId, plotting::PlotObject<Number>{_points, true, false, _color, settings}));
            mId++;
            return (mId - 1);
        }
        return 0;
    }

    template<typename Number>
    unsigned Plotter<Number>::addObject(const std::vector<std::vector<Point<Number>>> &_points) {
        for (const auto &part: _points) {
            addObject(part);
            --mId;
        }
        mId++;
        return mId - 1;
    }

    template<typename Number>
    unsigned Plotter<Number>::addObject(const std::vector<Halfspace<Number>> &_planes) {
        mPlanes.insert(std::make_pair(mId++, _planes));
        return mId;
    }

    template<typename Number>
    unsigned Plotter<Number>::addObject(const Halfspace<Number> &_plane) {
        assert(_plane.dimension() == 2);
        std::vector<Halfspace<Number>> tmp;
        tmp.push_back(_plane);
        mPlanes.insert(std::make_pair(mId++, tmp));
        return mId;
    }

    template<typename Number>
    void Plotter<Number>::removeObject(unsigned id) {
        if (mObjects.find(id) != mObjects.end()) {
            mObjects.erase(id);
        }
    }

    template<typename Number>
    void Plotter<Number>::addPolyline(const std::vector<Point<Number>> &points, std::optional<std::size_t> color) {
        if (!points.empty()) {
            bool objectIsTwoDimensional = true;
            if (points.begin()->dimension() != 2) {
                objectIsTwoDimensional = false;
                WARN("hypro.plotting", "Attempted to plot an object that is not 2-dimensional. Object was skipped.")
                return;
            }
            updateLimits(points);
            mLines.insert(std::make_pair(mId, plotting::PlotObject<Number>{points, true, false, color, std::nullopt}));
            mId++;
        }
    }

    template<typename Number>
    unsigned Plotter<Number>::addPoint(const Point<Number> &_point, std::optional<std::size_t> _color,
                                       std::optional<plotting::gnuplotSettings> settings) {
        return addObject({_point}, "", _color, settings, true);
    }

    template<typename Number>
    void Plotter<Number>::addPoints(const std::vector<Point<Number>> &_points) {
        for (const auto &p: _points) {
            assert(p.dimension() == 2);
            addPoint(p);
        }
    }

    template<typename Number>
    void Plotter<Number>::addVector(const vector_t<Number> &_vector, std::optional<vector_t<Number>> origin) {
        if (origin.has_value()) {
            if (origin.value().rows() != 2) {
                throw std::logic_error("The passed origin is not 2-dimensional.");
            }
            std::vector<Point<Number>> points{Point<Number>{_vector}, Point<Number>{origin.value()}};
            updateLimits(points);
            mVectors.insert(std::make_pair(mId++, std::make_pair(origin.value(), _vector)));
        } else {
            std::vector<Point<Number>> points{Point<Number>{_vector}, Point<Number>{vector_t<Number>::Zero(2)}};
            updateLimits(points);
            mVectors.insert(std::make_pair(mId++, std::make_pair(vector_t<Number>::Zero(2), _vector)));
        }
    }

    template<typename Number>
    void Plotter<Number>::setObjectColor(unsigned _id, const std::size_t _color) {
        if (_color != 0 && mObjects.find(_id) != mObjects.end()) {
            mObjects[_id].color = _color;
        } else if (_color != 0 && mPlanes.find(_id) != mPlanes.end()) {
            mObjectColors[_id] = _color;
        }
    }

    template<typename Number>
    void Plotter<Number>::clear() {
        mId = 1;
        mObjects.clear();
        mPlanes.clear();
        mPoints.clear();
        mVectors.clear();
        mLines.clear();
        mObjectColors.clear();
    }

    template<typename Number>
    void Plotter<Number>::updateLimits(const std::vector<Point<Number>> &points) {
        // initialize limits
        if (mObjects.empty() && mPoints.empty() && mVectors.empty()) {
            mLimits.first = points.begin()->rawCoordinates();
            mLimits.second = points.begin()->rawCoordinates();
        }
        // update limits
        for (const auto &point: points) {
            if (point.dimension() == 2) {
                for (unsigned d = 0; d < mLimits.first.rows(); ++d) {
                    mLimits.first(d) =
                            mLimits.first(d) > point.rawCoordinates()(d) ? point.rawCoordinates()(d) : mLimits.first(d);
                    mLimits.second(d) =
                            mLimits.second(d) < point.rawCoordinates()(d) ? point.rawCoordinates()(d) : mLimits.second(
                                    d);
                }
            } else {
                throw std::logic_error("Attempting to plot an object that is not 2-dimensional");
            }
        }
    }

    template<typename Number>
    void Plotter<Number>::init(const std::string &_filename) {
        mOutfile.open(_filename);
    }

    template<typename Number>
    void Plotter<Number>::writeGnuplot() const {
        assert(mOutfile.is_open());
        prepareObjects();
        TRACE("hypro.plotter", "Prepared objects.");

        if (!mVectors.empty()) {
            mOutfile << "# plotting vectors normalized to length 1\n";
            for (auto &[_, vector]: mVectors) {
                mOutfile << "set arrow from " << vector.first(0) << "," << vector.first(1) << " to " << vector.second(0)
                         << "," << vector.second(1) << "\n";
            }
            mOutfile << "\n";
        }

        if ((!mObjects.empty() && !mObjects.begin()->second.vertices.empty()) || !mPoints.empty() || !mLines.empty()) {
            TRACE("hypro.plotter", "Start plotting objects.");
            // set object
            vector_t<Number> min = vector_t<Number>(2);
            vector_t<Number> max = vector_t<Number>(2);
            min(0) = mLimits.first(0);
            min(1) = mLimits.first(1);
            max(0) = mLimits.second(0);
            max(1) = mLimits.second(1);
            // extend ranges
            std::map<unsigned, carl::Interval<double>> ranges;
            for (unsigned d = 0; d < min.rows(); ++d) {
                double rangeExt = toDouble((toDouble(max(d)) - toDouble(min(d))) * 0.05);
                if (rangeExt > 0.00001) {
                    ranges[d] = carl::Interval<double>(toDouble(min(d)) - rangeExt, toDouble(max(d)) + rangeExt);
                } else {
                    rangeExt = toDouble(toDouble(min(d)) * 0.05);
                    double leftBound = toDouble(min(d)) - rangeExt;
                    double rightBound = toDouble(max(d)) + rangeExt;
                    // if both bounds are zero, add a slight margin left and right so range is not empty
                    if ((leftBound == rightBound) == 0) {
                        leftBound -= 0.01;
                        rightBound += 0.01;
                    }
                    ranges[d] = carl::Interval<double>(leftBound, rightBound);
                }
            }
            // determine point-radius
            double pointRadius = std::min(ranges[0].diameter(), ranges[1].diameter()) * 0.01;

            // preamble
            mOutfile << "set xtics autofreq\n";
            mOutfile << "set ytics autofreq\n";
            mOutfile << "set bmargin 2\n";

            if (!mSettings.plain) {
                if (mSettings.grid) {
                    mOutfile << "set grid back\n";
                }
                if (mSettings.key) {
                    mOutfile << "set key outside\n";
                }
                if (mSettings.axes) {
                    mOutfile << "# axis settings\n";
                    mOutfile << "set xzeroaxis\n";
                    mOutfile << "set zeroaxis\n";
                    mOutfile << "set xtics axis\n";
                    mOutfile << "set yzeroaxis\n";
                    mOutfile << "set ytics axis\n";
                }
            } else {
                mOutfile << "unset border\nunset xtics\nunset ytics\n";
            }

            if (!isEmpty(mSettings.xPlotInterval)) {
                mOutfile << "set xrange [" << mSettings.xPlotInterval.lower() << ":" << mSettings.xPlotInterval.upper()
                         << "] \n";
            } else {
                mOutfile << "set xrange [" << ranges[0].lower() << ":" << ranges[0].upper() << "] \n";
            }
            if (!isEmpty(mSettings.yPlotInterval)) {
                mOutfile << "set yrange [" << mSettings.yPlotInterval.lower() << ":" << mSettings.yPlotInterval.upper()
                         << "] \n";
            } else {
                mOutfile << "set yrange [" << ranges[1].lower() << ":" << ranges[1].upper() << "] \n";
            }

            unsigned objectCount = 1;
            unsigned currId = 0;
            unsigned tmpId = 0;
            std::string keyContent = "";
            mOutfile << "\n# plotting sets\n";

            for (auto &[id, plotObject]: mObjects) {
                if (currId != id) {
                    currId = id;
                    tmpId++;
                    INFO("hypro.plotter",
                         "Plotting object " << tmpId << "/" << (mObjects.size() + mPoints.size() + mPlanes.size()));
                }
                if (plotObject.vertices.size() > 0) {
                    if (plotObject.isPoints) {
                        for (const auto &p: plotObject.vertices) {
                            mOutfile << "set object " << std::dec << objectCount << " circle at first \\\n";
                            assert(p.dimension() == 2);
                            mOutfile << "  " << toDouble(p.at(0));
                            for (unsigned d = 1; d < p.dimension(); ++d) {
                                mOutfile << ", " << toDouble(p.at(d));
                            }
                            mOutfile << " radius " << pointRadius;
                        }
                    } else {
                        mOutfile << "set object " << std::dec << objectCount << " polygon from \\\n";
                        for (const auto vertex: plotObject.vertices) {
                            assert(vertex.dimension() == 2);
                            if (vertex.dimension() == 0) {
                                continue;
                            }
                            mOutfile << "  " << toDouble(vertex.at(0));
                            for (unsigned d = 1; d < vertex.dimension(); ++d) {
                                mOutfile << ", " << toDouble(vertex.at(d));
                            }
                            mOutfile << " to \\\n";
                        }
                        // assert(objectIt->objectIt->size()-1].dimension() <= 2); // TODO:
                        // Project to 2d	TODO: REINSERT ASSERTION
                        mOutfile << "  " << toDouble(plotObject.vertices[0].at(0));
                        for (unsigned d = 1; d < plotObject.vertices[0].dimension(); ++d) {
                            mOutfile << ", " << toDouble(plotObject.vertices[0].at(d));
                        }
                    }

                    // color lookup
                    auto color = mSettings.color;
                    if (plotObject.color.has_value()) {
                        color = plotObject.color.value();
                    }

                    if (mSettings.fill || (plotObject.settings.has_value() && plotObject.settings.value().fill)) {
                        mOutfile << " front fs transparent solid 0.75 fc rgb '#" << std::hex << color << std::dec
                                 << "' ";
                        if (!mSettings.border ||
                            (plotObject.settings.has_value() && !plotObject.settings.value().border)) {
                            mOutfile << "lw " << mSettings.linewidth << "\n";
                        } else {
                            mOutfile << "lw " << mSettings.linewidth << "lc rgb '#BF" << std::hex << color << std::dec
                                     << "'"
                                     << "\n";
                        }
                    } else {
                        mOutfile << " front fs empty border lc rgb '#" << std::hex << color << std::dec << "' ";
                        if (!mSettings.border ||
                            (plotObject.settings.has_value() && !plotObject.settings.value().border)) {
                            mOutfile << "lw " << mSettings.linewidth << "\n";
                        } else {
                            mOutfile << "lw " << mSettings.linewidth << "lc rgb '#BF" << std::hex << color << std::dec
                                     << "'"
                                     << "\n";
                        }
                    }

                    if (mSettings.key) {
                        mOutfile << "set style line " << std::dec << objectCount << " lc rgb '#" << std::hex << color
                                 << std::dec << "' lt 1 lw 5\n";
                        keyContent = keyContent + ", NaN ls " + std::to_string(objectCount) + " title \"" +
                                     plotObject.objectTitle + "\"";
                    }

                    if (mSettings.cummulative) {
                        mOutfile << "\nplot ";
                        for (unsigned d = 0; d < min.rows(); ++d) {
                            mOutfile << "[" << ranges[d].lower() << ":" << ranges[d].upper() << "] ";
                        }
                        if (mSettings.key) {
                            mOutfile << "NaN notitle" << keyContent << "\n";
                        } else {
                            mOutfile << "NaN notitle\n";
                        }
                    }
                    // mark as plotted
                    plotObject.isPlotted = true;
                }
                ++objectCount;
            }

            // plot polylines
            if (!mLines.empty()) {
                mOutfile << "\n# plot polylines\n";
                std::size_t segmentIdx = 1;
                for (const auto &[id, lineObj]: mLines) {
                    for (auto lineIdx = std::begin(lineObj.vertices);
                         lineIdx != std::next(std::end(lineObj.vertices), -1); ++lineIdx) {
                        auto next = std::next(lineIdx);
                        std::stringstream ss;
                        if (lineObj.color.has_value()) {
                            ss << std::hex << lineObj.color.value() << std::dec;
                        } else {
                            ss << std::hex << mSettings.color << std::dec;
                        }
                        mOutfile << "set arrow " << std::dec << segmentIdx++ << " from \\\n";
                        mOutfile << lineIdx->at(0) << "," << lineIdx->at(1) << " to " << next->at(0) << ","
                                 << next->at(1) << " linecolor rgb '#" << ss.str()
                                 << "' linetype 1 linewidth 2 nohead front\n\n";
                    }
                }
            }

            if (mPlanes.empty() && mPoints.empty()) {
                mOutfile << "plot - NaN notitle\n";
            }

            // create plane functions
            int index = 1;
            if (!mPlanes.empty()) {
                mOutfile << "\n";
                mOutfile << "# plotting Halfspaces\n";
                for (const auto &planePair: mPlanes) {
                    for (const auto &plane: planePair.second) {
                        assert(plane.dimension() == 2);
                        vector_t<Number> normal = plane.normal();

                        if (normal(1) == Number(0)) {
                            mOutfile << "set arrow from " << toDouble(Number(plane.offset() / normal(0)))
                                     << ",graph(0,0) to " << toDouble(Number(plane.offset() / normal(0)))
                                     << ",graph(1,1) nohead\n";
                        } else {
                            mOutfile << "f_" << index << "(x) = " << toDouble(Number(-normal(0) / normal(1))) << "*x";
                            double off = toDouble(Number(plane.offset() / normal(1)));
                            if (off >= 0)
                                mOutfile << "+";
                            mOutfile << off << "\n";
                            ++index;
                        }
                    }
                }
            }

            // plot polylines
            if (!mLines.empty()) {
                mOutfile << "\n# plot polylines\n";
                std::size_t segmentIdx = 1;
                for (const auto &[id, lineObj]: mLines) {
                    for (auto lineIdx = std::begin(lineObj.vertices);
                         lineIdx != std::next(std::end(lineObj.vertices), -1); ++lineIdx) {
                        auto next = std::next(lineIdx);
                        std::stringstream ss;
                        if (lineObj.color.has_value()) {
                            ss << std::hex << lineObj.color.value() << std::dec;
                        } else {
                            ss << std::hex << mSettings.color << std::dec;
                        }
                        mOutfile << "set arrow " << std::dec << segmentIdx++ << " from \\\n";
                        mOutfile << lineIdx->at(0) << "," << lineIdx->at(1) << " to " << next->at(0) << ","
                                 << next->at(1) << " linecolor rgb '#" << ss.str()
                                 << "' linetype 1 linewidth 2 nohead front\n\n";
                    }
                }
            }

            if (!mPoints.empty()) {
                // collect styles
                std::map<std::size_t, std::pair<std::string, std::string>> styles_definitions_calls;
                std::size_t style_index = 1;
                std::stringstream ss;
                ss << std::hex << plotting::colors[plotting::blue] << std::dec;
                styles_definitions_calls[plotting::colors[plotting::blue]] = std::make_pair(std::to_string(style_index),
                                                                                            "set style line " +
                                                                                            std::to_string(
                                                                                                    style_index) +
                                                                                            " lc rgb '#" + ss.str() +
                                                                                            "' pt 7");
                ss.str(std::string());
                ++style_index;
                for (const plotting::PlotObject<Number> &p: mPoints) {
                    if (p.color) {
                        if (styles_definitions_calls.find(p.color.value()) == std::end(styles_definitions_calls)) {
                            ss << std::hex << p.color.value() << std::dec;
                            styles_definitions_calls[p.color.value()] = std::make_pair(std::to_string(style_index),
                                                                                       "set style line " +
                                                                                       std::to_string(style_index) +
                                                                                       " lc rgb '#" + ss.str() +
                                                                                       "' pt 7");
                            ss.str(std::string());
                            ++style_index;
                        }
                    }
                }

                mOutfile << "# plotting points\n";
                mOutfile << "set multiplot\n";
                mOutfile << "unset key\n";
                mOutfile << "set pointsize " << mSettings.pointSize << "\n";
                for (const auto &[_, valuepair]: styles_definitions_calls) {
                    mOutfile << valuepair.second << "\n";
                }
                for (const auto &pObj: mPoints) {
                    auto col = pObj.color ? pObj.color.value() : plotting::colors[plotting::blue];
                    mOutfile << "plot '+' us (" << toDouble(pObj.vertices.front().at(0)) << "):("
                             << toDouble(pObj.vertices.front().at(1)) << ") w p ls "
                             << styles_definitions_calls[col].first << "\n";
                }
            }
            mOutfile << "\n";

            if (!mPlanes.empty()) {
                if (mPoints.empty()) {
                    mOutfile << "set multiplot \n";
                    mOutfile << "unset key\n";
                }
                // plot all planes
                auto color = mSettings.color;
                mOutfile << "set style line 1 linecolor rgb '#" << std::hex << color << std::dec << "' \n";
                while (index > 1) {
                    --index;
                    mOutfile << "plot f_" << index << "(x) with lines linestyle 1\n";
                }
            }

            if (!mPlanes.empty() || !mPoints.empty())
                mOutfile << "\nunset multiplot\n";
        }
    }

    template<typename Number>
    void Plotter<Number>::writeGen() const {
        assert(mOutfile.is_open());
        prepareObjects();

        if (!mVectors.empty()) {
            // TODO: implement gen file plotting for vectors.
        }

        if (!mObjects.empty() || !mObjects.begin()->second.vertices.empty() || !mPoints.empty()) {
            for (const auto &[_, plotObject]: mObjects) {
                if (plotObject.vertices.size() > 0) {
                    for (unsigned pointIndex = 0; pointIndex < plotObject.vertices.size(); ++pointIndex) {
                        assert(plotObject.vertices[pointIndex].dimension() == 2);
                        if (plotObject.vertices[pointIndex].dimension() == 0) {
                            continue;
                        }
                        mOutfile << toDouble(plotObject.vertices[pointIndex].at(0));
                        for (unsigned d = 1; d < plotObject.vertices[pointIndex].dimension(); ++d) {
                            mOutfile << " " << toDouble(plotObject.vertices[pointIndex].at(d));
                        }
                        mOutfile << "\n";
                    }
                    mOutfile << toDouble(plotObject.vertices[0].at(0));
                    for (unsigned d = 1; d < plotObject.vertices[0].dimension(); ++d) {
                        mOutfile << " " << toDouble(plotObject.vertices[0].at(d));
                    }
                    mOutfile << "\n";
                }
                mOutfile << "\n\n\n";
            }

            // create plane functions
            if (!mPlanes.empty()) {
                // TODO: implement.
            }

            if (!mPoints.empty()) {
                // TODO: implement.
            }
        }
    }

    template<typename Number>
    void Plotter<Number>::prepareObjects() const {
        // reduce and sort objects
        if (!mObjects.empty()) {
            TRACE("hypro.plotter", "Prepare " << mObjects.size() << " objects.");
            for (auto &[id, plotObject]: mObjects) {
                if (!plotObject.isPrepared) {
                    // sort objects
                    TRACE("hypro.plotter", "Sort vertices of object " << id);
                    plotObject.vertices = ::hypro::grahamScan(plotObject.vertices);
                    plotObject.isPrepared = true;
                }
            }
        }
    }

}  // namespace hypro
