function BouncingBallTest

% Create Automaton
automaton = MHyProHAutomaton();
loc = MHyProLocation();
tran = MHyProTransition();
reset = MHyProReset();
guard = MHyProCondition();


% Set invariant x >= 0
inv_mat = [-1 0];
inv_vec = 0;
inv = MHyProCondition(inv_mat, inv_vec);
loc.setInvariant(inv);
loc.setName('loc1');

% TEST
m = inv.getMatrix();
v = inv.getVector();
assert(isequal(m, inv_mat));
assert(isequal(v, inv_vec));
i = loc.getInvariant();
im = i.getMatrix();
iv = i.getVector();
assert(isequal(im, inv_mat));
assert(isequal(iv, inv_vec));
% TEST END

% Set flow:
% x' = v v' = -9.81
flowMatrix = [0 1 0; 0 0 -9.81; 0 0 0];
loc.setFlow(flowMatrix);

% TEST
f = loc.getLinearFlow();
fm = f.getFlowMatrix();
disp('------------------');
assert(isequal(flowMatrix, fm));
% TEST END

% Set guard:
% x = 0 or v > 0
guardMatrix = [1 0; -1 0; 0 1];
guardVector = [0;0;0];
guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard.setVector(guardVector);

% TEST
gm = guard.getMatrix();
gv = guard.getVector();
assert(isequal(gm, guardMatrix));
assert(isequal(gv, guardVector));
% TEST END

% Set reset
% x:= x v:= -0.9v
constReset = [0; 0];
linReset = [1 0; 0 -0.9];
reset.setMatrix(linReset);
reset.setVector(constReset);

% TEST
rm = reset.getMatrix(1);
rv = reset.getVector(1);
assert(isequal(rm, linReset));
assert(isequal(rv, constReset));
% TEST END

% Setup transition
%tran.setAggregation(0);
tran.setGuard(guard);
tran.setSource(loc);
tran.setTarget(loc);
tran.setReset(reset);
tran.setLabels({MHyProLabel('t1')});

loc.addTransition(tran);

% TEST
% disp('Aggregation');
% tran.getAggregation()
tg = tran.getGuard();
assert(isequal(tg.getMatrix(), guardMatrix));
assert(isequal(tg.getVector(), guardVector));
sloc = tran.getSource();
assert(isequal(sloc.getName(), loc.getName()));
tloc = tran.getTarget();
assert(isequal(tloc.getName(), loc.getName()));
tres = tran.getReset();
assert(isequal(tres.getMatrix(1), linReset));
assert(isequal(tres.getVector(1), constReset));
locT = loc.getTransitions();
assert(length(locT) == 1);
tLabs = locT{1}.getLabels();
assert(length(tLabs) == 1);
assert(isequal(tLabs{1}.getName(), 't1'));
% TEST END


% Create initial set
% x = [10, 10.2] v = 0
boxVector = [10.2; -10; 0; 0];
boxMatrix = [1 0; -1 0; 0 1; 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(loc, initialCond);
automaton.addLocation(loc);

% TEST
initState = automaton.getInitialStates();
il = initState(1).loc;
ic = initState(1).cond;
assert(isequal(il.getName(), loc.getName()));
assert(isequal(ic.getMatrix(), boxMatrix));
assert(isequal(ic.getVector(), boxVector));
aloc = automaton.getLocations();
assert(length(aloc) == 1);
assert(isequal(aloc{1}.getName(), loc.getName()));
fl = loc.getLinearFlow();
flm = fl.getFlowMatrix();
alocf = aloc{1}.getLinearFlow();
alocfm = alocf.getFlowMatrix();
assert(isequal(flm, alocfm));
% TEST END

% Reachability

settings = struct('timeStep', 0.01, 'timeBound', 3.2, 'jumpDepth', 2);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [1 2];
reach.plot(flowpipes, dim);
end
