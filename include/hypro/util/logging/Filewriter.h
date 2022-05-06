#pragma once
#include "../multithreading/LockableBase.h"

#include <filesystem>
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

	void deleteFile() const {
		try {
			std::filesystem::remove( filename );
		} catch ( const std::filesystem::filesystem_error& err ) {
			std::cout << "filesystem error: " << err.what() << '\n';
		}
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
