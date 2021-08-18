#pragma once
#include <exception>

namespace hypro {
/**
 *	These exceptions can be used to terminate Context computation early
 *   WARNING: Only use those if you are 100% certain that computation in the other
 *	handlers has finished and it is save to terminate the worker
 */

// Hard Terminate computation
class HardTerminateException : public std::exception {
  private:
	const char* m_msg;

  public:
	HardTerminateException() = default;
	HardTerminateException( const char* msg ) {
		m_msg = msg;
	}

	const char* what() const throw() {
		return m_msg;
	}
};

// finish computation with processing of discrete transitions
class FinishWithDiscreteProcessingException : public std::exception {
  private:
	const char* m_msg;

  public:
	FinishWithDiscreteProcessingException() = default;
	FinishWithDiscreteProcessingException( const char* msg ) {
		m_msg = msg;
	}

	const char* what() const throw() {
		return m_msg;
	}
};

}  // namespace hypro
