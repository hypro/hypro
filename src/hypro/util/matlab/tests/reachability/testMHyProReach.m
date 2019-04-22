function res = testMHyProReach

% Create Automaton
automaton = MHyProHAutomaton();
loc = MHyProLocation();
tran = MHyProTransition();
reset = MHyProReset();
guard = MHyProCondition();

inv_mat = [-1 0 0];
inv_vec = 0;
inv = MHyProCondition(inv_mat, inv_vec);
loc.setInvariant(inv);
flowMatrix = [1 0 0; 0 1 0; 0 1 1];
loc.setFlow(flowMatrix);

guardVector = [0];
guardMatrix = [1];
guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard.setVector(guardVector);


constReset = [0];
linReset = [1];
reset.setMatrix(linReset);
reset.setVector(constReset);

tran.setAggregation(1);
tran.setGuard(guard);
tran.setSource(loc);
tran.setTarget(loc);
tran.setReset(reset);

loc.addTransition(tran);
boxVector = [1];
boxMatrix = [1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(loc, initialCond);
automaton.addLocation(loc);


% % Set invariant
% inv_mat = [-1 0];
% inv_vec = 0;
% inv = MHyProCondition(inv_mat, inv_vec);
% 
% m = inv.getMatrix();
% v = inv.getVector();
% assert(isequal(m, inv_mat));
% assert(isequal(v, inv_vec));
% 
% loc.setInvariant(inv);
% loc.setName('loc1');
% 
% i = loc.getInvariant();
% im = i.getMatrix();
% iv = i.getVector();
% assert(isequal(im, inv_mat));
% assert(isequal(iv, inv_vec));
% 
% % Set flow
% flowMatrix = [0 1 0; 0 0 -9.81; 0 0 0];
% loc.setFlow(flowMatrix);
% 
% f = loc.getLinearFlow();
% fm = f.getFlowMatrix();
% assert(isequal(flowMatrix, fm));
% 
% % Set guard
% guardVector = [0;0;0];
% guardMatrix = [1 0; -1 0; 0 1];
% guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
% guard.setVector(guardVector);
% gm = guard.getMatrix();
% gv = guard.getVector();
% assert(isequal(gm, guardMatrix));
% assert(isequal(gv, guardVector));
% 
% % Set reset
% constReset = [0; 0];
% linReset = [1 0; 0 -0.9];
% reset.setMatrix(linReset);
% reset.setVector(constReset);
% rm = reset.getMatrix(1);
% rv = reset.getVector(1);
% assert(isequal(rm, linReset));
% assert(isequal(rv, constReset));
% 
% 
% % Setup transition
% tran.setAggregation(2);
% tran.setGuard(guard);
% tran.setSource(loc);
% tran.setTarget(loc);
% tran.setReset(reset);
% tran.setLabels({MHyProLabel('t1')});
% 
% % disp('Aggregation');
% % tran.getAggregation()
% tg = tran.getGuard();
% assert(isequal(tg.getMatrix(), guardMatrix));
% assert(isequal(tg.getVector(), guardVector));
% sloc = tran.getSource();
% assert(isequal(sloc.getName(), loc.getName()));
% tloc = tran.getTarget();
% assert(isequal(tloc.getName(), loc.getName()));
% tres = tran.getReset();
% assert(isequal(tres.getMatrix(1), linReset));
% assert(isequal(tres.getVector(1), constReset));
% 
% loc.addTransition(tran);
% 
% locT = loc.getTransitions();
% assert(length(locT) == 1);
% tLabs = locT{1}.getLabels();
% assert(length(tLabs) == 1);
% assert(isequal(tLabs{1}.getName(), 't1'));
% 
% % Create initial set
% boxVector = [10.2; -10; 0; 0];
% boxMatrix = [1 0; -1 0; 0 1; 0 -1];
% initialCond = MHyProCondition(boxMatrix, boxVector);
% automaton.addInitialState(loc, initialCond);
% automaton.addLocation(loc);
% 
% initState = automaton.getInitialStates();
% il = initState{1}.location;
% ic = initState{1}.condition;
% assert(isequal(il.getName(), loc.getName()));
% assert(isequal(ic.getMatrix(), boxMatrix));
% assert(isequal(ic.getVector(), boxVector));
% 
% aloc = automaton.getLocations();
% assert(length(aloc) == 1);
% assert(isequal(aloc{1}.getName(), loc.getName()));
% fl = loc.getLinearFlow();
% flm = fl.getFlowMatrix();
% alocf = aloc{1}.getLinearFlow();
% alocfm = alocf.getFlowMatrix();
% assert(isequal(flm, alocfm));

% Reachability

settings = struct('timeStep', 0.01, 'timeBound', 2, 'jumpDepth', 3, 'plotDimensions', [1 3; 2 4]);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;

disp("Time needed: ", num2str(time));
num_flowpipes = length(flowpipes);

for pipe = 1:num_flowpipes
    currentFlowpipe =  flowpipes{pipe};
    num_states = length(currentFlowpipe);
    disp(['Number of states: ', num2str(num_states)]);
    figure()
    for state = 1:num_states
        currentState = currentFlowpipe{state};
        vertices = currentState.vertices(1);
        plot(vertices(1), vertices(2), 'bo');
        hold on
    end  
end



res = 1;