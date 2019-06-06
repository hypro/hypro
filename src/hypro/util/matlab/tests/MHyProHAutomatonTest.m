function tests = MHyProHAutomatonTest
    tests = functiontests(localfunctions);
end

function testHAutomaton(testCase)

automaton = MHyProHAutomaton();

loc = MHyProLocation();
tran = MHyProTransition();
reset = MHyProReset();
guard = MHyProCondition();

% Set invariant
inv_mat = [-1 0];
inv_vec = 0;
inv = MHyProCondition(inv_mat, inv_vec);
loc.setInvariant(inv);

% Set flow
flowMatrix = [0 1 0; 0 0 -9.81; 0 0 0];
loc.setFlow(flowMatrix);

% Set guard
guardVector = [0;0;0];
guardMatrix = [1 0; -1 0; 0 1];
guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard.setVector(guardVector);


% Set reset
constReset = [0; 0];
linReset = [1 0; 0 -0.9];
reset.setMatrix(linReset);
reset.setVector(constReset);


% Setup transition
tran.setAggregation(2);
tran.setGuard(guard);
tran.setSource(loc);
tran.setTarget(loc);
tran.setReset(reset);
loc.addTransition(tran);

% Create initial set
boxVector = [10.2; -10; 0; 0];
boxMatrix = [1 0; -1 0; 0 1; 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(loc, initialCond);

% Creat new automaton from locations and initial set mapping

loc1 = MHyProLocation();
loc2 = MHyProLocation();
locs = {loc1, loc2};

initialState = MHyProCondition();
initialState.setMatrix([-1 0 0 0 0 0 0 0 0 0]); % First set the matrix then the vector!?
initialState.setVector(-1.7);
initialStates(1).loc = loc1;
initialStates(1).cond = initialState;
initialStates(2).loc = loc2;
initialStates(2).cond = initialState;

automaton = MHyProHAutomaton(locs, initialStates);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Tests for getters

% automaton = MHyProHAutomaton();
% automaton.getLocation_by_name('loc1');
% disp('Create Location 1');
% loc1 = MHyProLocation();
% disp('Create Location 2');
% loc2 = MHyProLocation();
% disp('Set name');
% loc1.setName('loc1');
% disp('Add location');
% automaton.addLocation(loc1);
% disp(['Loc1 object handle: ', num2str(loc1.ObjectHandle)]);
% disp('Get Location by name');
% locs = automaton.getLocation_by_name('loc1');
% disp(['Get handle of the getted location: ', num2str(locs.ObjectHandle)]);

% disp('New invariant:');
% cond = MHyProCondition();
% disp('New location');
% loc1 = MHyProLocation();
% disp('set invariant');
% loc1.setInvariant(cond);
% disp('get invariant');
% loc1.getInvariant();

% automaton_locs_init
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
end
