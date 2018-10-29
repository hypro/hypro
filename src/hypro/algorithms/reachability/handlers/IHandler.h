#pragma once
#include "../../../datastructures/HybridAutomaton/State.h"
#include "../../../types.h"

namespace hypro {

	class IHandler {
	public:
		virtual void handle() = 0;		
		virtual const char* handlerName() = 0;
	};

	template<typename Number>
	class IFirstSegmentHandler : public IHandler {
	public:
		virtual void handle() = 0;
		virtual const char* handlerName() = 0;

		virtual matrix_t<Number> getTrafo() = 0;
		virtual vector_t<Number> getTranslation() = 0;
	};

	class IInvariantHandler : public IHandler {
	public:
		virtual ~IInvariantHandler(){}
		virtual void handle() = 0;
		virtual const char* handlerName() = 0;
		// provides information whether the handlers set fullfils containment conditions (eg. invariant)
		virtual CONTAINMENT getContainment() = 0;
		virtual bool getMarkedForDelete() = 0;
		virtual void setMarkedForDelete(bool toDelete) = 0;
	};

	class IBadStateHandler : public IHandler {
	public:
		virtual ~IBadStateHandler(){}
		virtual void handle() = 0;
		virtual const char* handlerName() = 0;
		// provides information whether the handlers set intersects its bad states
		virtual bool intersectsBadState() = 0;
		virtual bool getMarkedForDelete() = 0;
		virtual void setMarkedForDelete(bool toDelete) = 0;
	};

	template<typename Number>
	class IGuardHandler : public IHandler {
	public:
		virtual ~IGuardHandler(){}
		virtual void handle() = 0;
		virtual const char* handlerName() = 0;
		// provides information whether the handlers set intersects the transitions guard
		virtual bool satisfiesGuard() = 0;
		virtual std::shared_ptr<State_t<Number>> getState()=0;		
		virtual void setState(std::shared_ptr<State_t<Number>> ptr) =0;
		virtual void reinitialize()=0;
		virtual double getSortIndex() = 0;
		virtual void setSortIndex(double sortIndex) = 0;
		virtual bool getMarkedForDelete() = 0;
		virtual void setMarkedForDelete(bool toDelete) = 0;
	};

	class ITimeEvolutionHandler : public IHandler {
	public:
		virtual void handle() = 0;
		virtual const char* handlerName() = 0;
	};

	class IResetHandler : public IHandler {
	public:
		virtual void handle() = 0;
		virtual const char* handlerName() = 0;
	};

	class IJumpHandler : public IHandler{
	public:
		virtual void handle() = 0;
		virtual const char* handlerName() = 0;
	};
} // namespace hypro