/**
 * Util file which holds conversion functions, in case we run our tests with rationals.
 */


namespace hypro {

	template<typename F, carl::DisableIf< carl::is_rational<F> > = carl::dummy>
	static F testCos(const F& in) {
		return cos(in);
	}

	template<typename F, carl::DisableIf< carl::is_rational<F> > = carl::dummy>
	static F testSin(const F& in) {
		return sin(in);
	}

	template<typename R, carl::EnableIf< carl::is_rational<R> > = carl::dummy>
	static R testCos(const R& in) {
		return carl::rationalize<R>(cos(carl::toDouble(in)));
	}

	template<typename R, carl::EnableIf< carl::is_rational<R> > = carl::dummy>
	static R testSin(const R& in) {
		return carl::rationalize<R>(sin(carl::toDouble(in)));
	}

} // namespace hypro