
#pragma once
#include "types.h"
#include "representations/SupportFunction/util.h"

namespace hypro {

	template<typename Number>
	class TrafoParameters {
		private:
			matrix_t<Number> mMatrix;
			vector_t<Number> mVector;
			std::shared_ptr<lintrafoParameters<Number>> mLintrafoParameters;
		public:
			TrafoParameters() = default;

			TrafoParameters(const matrix_t<Number>& A, const vector_t<Number>& b) :
				mMatrix(A),
				mVector(b),
				mLintrafoParameters(std::make_shared<lintrafoParameters<Number>>(A,b))
			{}

			TrafoParameters(std::shared_ptr<lintrafoParameters<Number>> parameters) :
				mMatrix(parameters.matrix()),
				mVector(parameters.vector()),
				mLintrafoParameters(parameters)
			{}

			const matrix_t<Number>& matrix() const {
				return mMatrix;
			}

			const vector_t<Number>& vector() const {
				return mVector;
			}

			std::shared_ptr<lintrafoParameters<Number>> parameters() const {
				return mLintrafoParameters;
			}

			void setMatrix(const matrix_t<Number>& A){
				mMatrix = A;
			}

			void setVector(const vector_t<Number>& b){
				mVector = b;
			}
	};

} // namespace hypro
