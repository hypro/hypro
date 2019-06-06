function tests = MHyProHAutomatonTest
    tests = functiontests(localfunctions);
end

function testHAutomaton(testCase)

% automaton = MHyProHAutomaton();
% 
% loc = MHyProLocation();
% tran = MHyProTransition();
% reset = MHyProReset();
% guard = MHyProCondition();
% 
% % Set invariant
% inv_mat = [-1 0];
% inv_vec = 0;
% inv = MHyProCondition(inv_mat, inv_vec);
% loc.setInvariant(inv);
% 
% % Set flow
% flowMatrix = [0 1 0; 0 0 -9.81; 0 0 0];
% loc.setFlow(flowMatrix);
% 
% % Set guard
% guardVector = [0;0;0];
% guardMatrix = [1 0; -1 0; 0 1];
% guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
% guard.setVector(guardVector);
% 
% 
% % Set reset
% constReset = [0; 0];
% linReset = [1 0; 0 -0.9];
% reset.setMatrix(linReset);
% reset.setVector(constReset);
% 
% 
% % Setup transition
% tran.setAggregation(2);
% tran.setGuard(guard);
% tran.setSource(loc);
% tran.setTarget(loc);
% tran.setReset(reset);
% loc.addTransition(tran);
% 
% % Create initial set
% boxVector = [10.2; -10; 0; 0];
% boxMatrix = [1 0; -1 0; 0 1; 0 -1];
% initialCond = MHyProCondition(boxMatrix, boxVector);
% automaton.addInitialState(loc, initialCond);
% 
% % Creat new automaton from locations and initial set mapping
% 
% loc1 = MHyProLocation();
% loc2 = MHyProLocation();
% locs = {loc1, loc2};
% 
% initialState = MHyProCondition();
% initialState.setMatrix([-1 0 0 0 0 0 0 0 0 0]); % First set the matrix then the vector!?
% initialState.setVector(-1.7);
% initialStates(1).loc = loc1;
% initialStates(1).cond = initialState;
% initialStates(2).loc = loc2;
% initialStates(2).cond = initialState;

% automaton = MHyProHAutomaton(locs, initialStates);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Tests for getters

% automaton = MHyProHAutomaton();
% disp('Create Location 1');
% loc1 = MHyProLocation();
% disp('Create Location 2');
% loc2 = MHyProLocation();
% disp('Set name');
% loc1.setName('loc1');
% disp('Add location');
% automaton.addLocation(loc1);
% disp(['Loc1 object handle: ', num2str(loc1.ObjectHandle)]);
% disp('Get Location by name 1');
% locs1 = automaton.getLocation_by_name('loc1');
% disp(['Get handle of the get location 1: ', num2str(locs1.ObjectHandle)]);
% disp('Get Location by name 2');
% locs2 = automaton.getLocation_by_name('loc1');
% disp(['Get handle of the get location 2: ', num2str(locs2.ObjectHandle)]);
% disp('Get Location by name 3');
% locs3 = automaton.getLocation_by_name('loc1');
% disp(['Get handle of the get location 3: ', num2str(locs3.ObjectHandle)]);
% loc1.setName('newName');
% disp('Get Location by name 2');
% locs2 = automaton.getLocation_by_name('loc1');
% disp(['Get handle of the get location 2: ', num2str(locs2.ObjectHandle)]);
% disp('Get Location by name 3');
% locs3 = automaton.getLocation_by_name('newName');
% disp(['Get handle of the get location 3: ', num2str(locs3.ObjectHandle)]);


disp('New invariant:');
cond = MHyProCondition();
disp('New location');
loc1 = MHyProLocation();
disp('set invariant');
loc1.setInvariant(cond);
disp('get invariant');
inv1 = loc1.getInvariant();
disp('set matrix');
inv1.setMatrix([1 2; 3 4]);
inv2 = loc1.getInvariant();
inv2.getMatrix();

% automaton = MHyProHAutomaton();
% loc1 = automaton.getLocation_by_name('bla');
% disp(['Location 1 handle: ', num2str(loc1.ObjectHandle)]);


%automaton_locs_init
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
end
