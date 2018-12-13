
/*
HybridAutomaton<double>* createBB()
{
    hypro::valuation_t<double> valuation;   // stays empty


    locationVector<double>* locs = new locationVector();
    locationVector<double>* initLocations = locs;    // all locations are initial locations
    transitionVector<double>* trans = new transitionVector();

    Location<double>* l1 = new Location<double>();
    Transition<double>* t1 = new Transition<double>();

    // TODO: set values of location and transition correspondent to the exmaple bouncingball.m

    // location:
    // A
    matrix_t<double> A(2,2);
    A(0,0) = 0;
    A(0,1) = 1;
    A(1,0) = 0;
    A(1,1) = 0;

    // b
    vector_t<double> b(2);
    b(0) = 0;
    b(1) = -9.81;



    // transition:
    // R
    matrix_t<double> R(2,2);
    R(0,0) = 1;
    R(0,1) = 0;
    R(1,0) = 0;
    R(1,1) = -0.6;

    // w
    vector_t<double> w(2);
    w(0) = 0;
    w(1) = 0;

    locs->insert(l1);
    trans->insert(t1);

    locations[0] = loc1;
		locations[1] = loc2;

	locSet = std::set<hypro::Location<double>*>(locations, locations+2);
    HybridAutomaton<double>* model = new HybridAutomaton<double>(*initLocations, *locs, *trans, valuation);
    return model;
}

// provide method to free memory?
*/

HybridAutomaton<double, valuation_t<double>>* createBB()
{
    //Hybrid Automaton Objects: Locations, Transitions, Automaton itself
    Location<double>* loc1 = new Location<double>();
    Transition<double>* trans = new Transition<double>();
    HybridAutomaton<double, valuation_t<double>>* hybrid = new HybridAutomaton<double, valuation_t<double>>();

    //Other Objects: Vectors, Matrices, Guards...
    //vector_t<double> invariantVec = vector_t<double>(2,1);
    //operator_e invariantOp;
    //matrix_t<double> invariantMat = matrix_t<double>(2,2);
	//struct Location<double>::invariant inv;

    struct hypro::Transition<double>::guard guard;
    struct hypro::Transition<double>::assignment assign;

    Location<double>* locations[1];
    std::set<hypro::Location<double>*> locSet;

    Location<double>* init[1];
    std::set<hypro::Location<double>*> initLocSet;

    Transition<double>* transition[1];
	std::set<hypro::Transition<double>*> transSet;

	//Point<double>::coordinates_map coordinates;
	//vector_t<double> coordinates = vector_t<double>(2,1);
    //Point<double> p1;
    //hypro::Polytope<double> poly;


         /*
		 * Location
		 */
		//invariantVec(0) = 10;
		//invariantVec(1) = 20;

		//invariantOp = LEQ;

		//invariantMat(0,0) = 2;
		//invariantMat(0,1) = 0;
		//invariantMat(1,0) = 0;
		//invariantMat(1,1) = 3;

		//loc1->setInvariant(invariantMat,invariantVec,invariantOp);

		//inv.op = invariantOp;
		//inv.mat = invariantMat;
		//inv.vec = invariantVec;

		//loc2->setInvariant(inv);

        // A
		matrix_t<double> A(2,2);
        A(0,0) = 0;
        A(0,1) = 1;
        A(1,0) = 0;
        A(1,1) = 0;

        // b
        vector_t<double> b(2);
        b(0) = 0;
        b(1) = -9.81;

		loc1->setActivityMat(A);
        loc1->setActivityVec(b);

        // B
        matrix_t<double> B(2,2);
        B(0,0) = 1;
        B(0,1) = 0;
        B(1,0) = 0;
        B(1,1) = 1;

        loc1->setExtInputMat(B);

		/*
		 * Transition
		 */

		// transition:
        // R
        matrix_t<double> R(2,2);
        R(0,0) = 1;
        R(0,1) = 0;
        R(1,0) = 0;
        R(1,1) = -0.6;

        // w
        vector_t<double> w(2);
        w(0) = 0;
        w(1) = 0;

        matrix_t<double> G(3,2);
        G(0,0) = 1; G(0,1) = 0;
        G(1,0) = -1; G(1,1) = 0;
        G(2,0) = 0; G(2,1) = 1;

        vector_t<double> g(3);
        g(0) = 0;
        g(1) = 0;
        g(2) = 0;

		guard.mat = G;
		guard.op = operator_e::LEQ;
		guard.vec = g;

		assign.translationVec = w;
		assign.transformMat = R;

		trans->setGuard(guard);
		trans->setStartLoc(loc1);
		trans->setTargetLoc(loc1);
		trans->setAssignment(assign);

		/*
		 * Hybrid Automaton
		 */
		locations[0] = loc1;
		locSet = std::set<hypro::Location<double>*>(locations, locations+1);

		init[0] = loc1;
		initLocSet = std::set<hypro::Location<double>*>(init, init+1);

		hybrid->setLocations(locSet);
		hybrid->setInitialLocations(initLocSet);

		transition[0] = trans;
		transSet = std::set<hypro::Transition<double>*>(transition, transition+1);

		hybrid->setTransitions(transSet);
		loc1->setTransitions(transSet);

		//Polytope for InitialValuation & Guard Assignment
		//coordinates.insert( std::make_pair(x, 2) );
		//coordinates.insert( std::make_pair(y, 3) );
		//coordinates(0) = 2;
		//coordinates(1) = 3;

    	//std::vector< vector_t <double> > vecSet;
    	//vecSet.push_back(coordinates);

    	//poly = Polytope<double>(vecSet);

    	/*
		std::map<carl::Variable, double> coordinate;
		coordinate.insert( std::make_pair(x, 2) );
		coordinate.insert( std::make_pair(y, 3) );
		p1 = Point<double>(coordinate);

		poly = Polytope<double>(p1);
		*/

		//hybrid.setValuation(poly);

		return hybrid;
}
