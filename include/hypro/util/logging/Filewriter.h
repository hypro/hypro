#pragma once
#include "../multithreading/LockableBase.h"

#include <fstream>

namespace hypro {

class LockedFileWriter : public LockableBase {
  private:
	std::string filename;

  public:
	LockedFileWriter( const std::string& fName )
		: filename( fName ) {}

	void clearFile() const {
		std::ofstream fileStream;
		fileStream.open( filename );
		fileStream.close();
	}

	const LockedFileWriter& operator<<( const std::string& content ) const {
		std::lock_guard<std::mutex> lock( LockableBase::getMutex() );
		std::ofstream fileStream;
		fileStream.open( filename, std::fstream::app );
		fileStream << content;
		fileStream.close();
		return *this;
	}
};

}  // namespace hypro
