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
				assert(object[object.size()-1].dimension() <= 2); // TODO: Project to 2d	
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
	void Plotter<Number>::addObject(const std::vector<Point<Number>>& _points) {
		mObjects.push_back(_points);
	}

	template<typename Number>
	void Plotter<Number>::init(const std::string& _filename) {
		mOutfile.open(_filename);
	}
}