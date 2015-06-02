#include "Plotter.h"

namespace hypro {

	template<typename Number>
	Plotter<Number>::~Plotter() {
		mOutfile.close();
	}

	template<typename Number>
	void Plotter<Number>::setFilename(const std::string& _filename) {
		mFilename = _filename;
	}

	template<typename Number>
	void Plotter<Number>::updateSettings(gnuplotSettings _settings) {
		mSettings = _settings;
	}

	template<typename Number>
	void Plotter<Number>::plot2d() const {
		mOutfile.open(mFilename + ".plt");

		if(!mObjects.empty()) {
			// set object
			vector_t<Number> min = mObjects[0][0].rawCoordinates();
			vector_t<Number> max = mObjects[0][0].rawCoordinates();

			unsigned objectCount = 1;
			for(const auto& object : mObjects) {
				std::cout << "Create object " << objectCount << std::endl;
				mOutfile << "\n";
				mOutfile << "set object "<< objectCount <<" polygon from \\\n";

				for(unsigned pointIndex = 0; pointIndex < object.size(); ++pointIndex) {
					assert(object[pointIndex].dimension() <= 2); // TODO: Project to 2d
					if(object[pointIndex].dimension() == 0) {
						continue;
					}
					mOutfile << "  " << double(object[pointIndex].at(0));
					
					// update min and max
					min(0) = min(0) < object[pointIndex].at(0) ? min(0) : object[pointIndex].at(0);
					max(0) = max(0) > object[pointIndex].at(0) ? max(0) : object[pointIndex].at(0);
					
					for(unsigned d = 1; d < object[pointIndex].dimension(); ++d) {
						mOutfile << ", " << double(object[pointIndex].at(d));
						// update min and max
						min(d) = min(d) < object[pointIndex].at(d) ? min(d) : object[pointIndex].at(d);
						max(d) = max(d) > object[pointIndex].at(d) ? max(d) : object[pointIndex].at(d);
					}
					mOutfile << " to \\\n";
				}
				//assert(object[object.size()-1].dimension() <= 2); // TODO: Project to 2d	TODO: REINSERT ASSERTION
				std::cout << double(object[0].at(0)) << std::endl;
				mOutfile << "  " << double(object[0].at(0));
				for(unsigned d = 1; d < object[0].dimension(); ++d) {
					mOutfile << ", " << double(object[0].at(d));
				}
				mOutfile << " fs empty border lc rgb '" << mSettings.color << "'\n";
				++objectCount;
			}
			
			mOutfile << "set term post eps\n";
			mOutfile << "set output \"" << mFilename << ".eps\"";
			mOutfile << "\n";
			mOutfile << "plot ";

			for(unsigned d = 0; d < min.rows(); ++d) {
				mOutfile << "[" << min(d)*1.1 << ":" << max(d)*1.1 << "] ";
			}
			mOutfile << "NaN notitle";
		}
		mOutfile.close();
	}

	template<typename Number>
	void Plotter<Number>::addObject(std::vector<Point<Number>> _points) {
		std::vector<Point<Number>> copyPoints;
		for(const auto& point : _points)
			copyPoints.push_back(Point<Number>(point));

		grahamScan(copyPoints);

		mObjects.push_back(copyPoints);
	}

	template<typename Number>
	void Plotter<Number>::init(const std::string& _filename) {
		mOutfile.open(_filename);
	}

	template<typename Number>
	void Plotter<Number>::grahamScan(std::vector<Point<Number>>& _points) {
		if(!_points.empty()) {
			// find minimum Point
			Point<Number> min = _points[0];
			std::map<Number, Point<Number>> sortedPoints;
			for(const auto& point : _points) {
				assert(point.dimension() == 2);
				if(point < min) {
					min = point;
				}
			}

			std::cout << "Min: " << min.rawCoordinates().transpose() << std::endl;

			// sort Points according to polar angle -> we have to insert manually (because of double imprecision)
			for(const auto& point : _points) {
				if(point != min) {
					Number angle = point.polarCoordinates(min)[1];
					std::cout << "Try to insert angle " << angle << std::endl;
					if(sortedPoints.empty()) {
						sortedPoints.insert(std::make_pair(angle, point));
						std::cout << "Inserted angle " << angle << std::endl;
						std::cout << "Stop." << std::endl;
					}
					else {
						for(auto pos = sortedPoints.begin(); pos != sortedPoints.end(); ) {
							// if equal, take the one with bigger radial component
							Number newAngle = pos->second.polarCoordinates(min)[1];
							std::cout << "Angle: " << angle << ", newAngle: " << newAngle << std::endl;
							if(AlmostEqual2sComplement(angle, newAngle)) {
								// if equal, compare radial coordinate (distance)
								if(pos->second.polarCoordinates(min)[0] < point.polarCoordinates(min)[0]) {
									pos = sortedPoints.erase(pos);
									sortedPoints.insert(std::make_pair(angle, point));
									std::cout << "Equal, Inserted angle " << angle << std::endl;
								}
								else {
									std::cout << "Dropped angle " << angle << std::endl;
								}
								break;
							}
							else if(angle > newAngle) {
								++pos;
								if(pos == sortedPoints.end()) {
									sortedPoints.insert(std::make_pair(angle, point));
									std::cout << "Inserted angle " << angle << std::endl;
									break;
								}
							}
							else {
								sortedPoints.insert(std::make_pair(angle, point));
								std::cout << "Inserted angle " << angle << std::endl;
								break;
							}
						}
						std::cout << "Stop." << std::endl;
					}
				}
			}

			// debug
			for(const auto& pointPair : sortedPoints) {
				std::cout << pointPair.first << ": " << pointPair.second << std::endl;
			}
			
			std::stack<Point<Number>> stack;
			stack.push(min);
			stack.push(sortedPoints.begin()->second);
			sortedPoints.erase(sortedPoints.begin());
			unsigned i = 2;
			unsigned n = sortedPoints.size();

			while(i<n) {
				Point<Number> p1 = stack.top();
				stack.pop();
				Point<Number> p2 = stack.top();
				stack.pop();
				if(isLeftTurn(p2,p1,sortedPoints.begin()->second)) {
					stack.push(p2);
					stack.push(p1);
					stack.push(sortedPoints.begin()->second);
					sortedPoints.erase(sortedPoints.begin());
					++i;
				}
				else {
					stack.push(p2);
				}
			}

			std::cout << "Hull result:" << std::endl;
			while(!stack.empty()){
				std::cout << stack.top() << std::endl;
				stack.pop();
			}

		}
	}

	template<typename Number>
	bool Plotter<Number>::isLeftTurn(const Point<Number>& a, const Point<Number>& b, const Point<Number>& c) {
		assert(a.dimension() == 2);
		assert(b.dimension() == 2);
		assert(c.dimension() == 2);

		vector_t<Number> rA = a.rawCoordinates();
		vector_t<Number> rB = b.rawCoordinates();
		vector_t<Number> rC = c.rawCoordinates();

		Number val = (rA(0) - rB(0))*(rC(1) - rA(1)) - (rC(0) - rA(0))*(rB(1) - rA(1));
		std::cout << "Consider " << rA.transpose() << " - " << rB.transpose() << " - " << rC.transpose() << " val: " << val << std::endl;

		return (val > 0);
	}
}