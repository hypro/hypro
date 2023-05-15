/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <chrono>
#include <iostream>

class Clock {
private:
    std::chrono::high_resolution_clock::time_point startPoint;
    std::chrono::high_resolution_clock::duration duration;
    bool running = false;

public:
    void start() {
        if (!running) {
            startPoint = std::chrono::high_resolution_clock::now();
            running = true;
        }
    }

    void stop() {
        if (running) {
            duration += std::chrono::high_resolution_clock::now() - startPoint;
            running = false;
        }
    }

    void reset() {
        duration = std::chrono::high_resolution_clock::duration::zero();
        running = false;
    }

    friend std::ostream &operator<<(std::ostream &out, const Clock &clk) {
        out << double(std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1>>>(clk.duration).count())
            << " s";
        return out;
    }
};
