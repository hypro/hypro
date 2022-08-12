function tests = MHyProLocationTest
    tests = functiontests(localfunctions);
end

function testLocation(testCase)
loc1 = MHyProLocation();
loc2 = MHyProLocation([1 0 1; 2 1 3; 1 1 1]);
loc3 = MHyProLocation([1 0; 2 1]);
loc4 = MHyProLocation([1 0; 0 1]);

tran1_2 = MHyProTransition(loc1, loc2);
tran1_3 = MHyProTransition(loc1, loc3);
tran1_4 = MHyProTransition(loc1, loc4);
tran2_4 = MHyProTransition(loc2, loc4);

lab1 = MHyProLabel('tran1_2');
lab2 = MHyProLabel('tran1_3');
lab3 = MHyProLabel('tran1_4');
lab4 = MHyProLabel('tran2_4');

labels = {lab1, lab2, lab3, lab4};

tran1_2.addLabel(lab1);
tran1_3.addLabel(lab2);
tran1_4.addLabel(lab3);
tran2_4.addLabel(lab4);

transitions = {tran1_2, tran1_3, tran1_4};
cond = MHyProCondition([1 2; 3 4], [1; 2]);
loc3 = MHyProLocation([1 2; 3 4], transitions, cond);
loc4 = MHyProLocation(loc3);

loc1.setName('loc1');
loc2.setName('loc2');
loc3.setName('loc3');
loc4.setName('loc4');

lin_flow = loc2.getLinearFlow();
flow_mat = lin_flow.getFlowMatrix();
assert(isequal(flow_mat, [1 0 1; 2 1 3; 1 1 1]));

num_flow = loc2.getNumberFlow();
assert(num_flow == 1);

% inv = loc4.getInvariant();
% inv_mat = inv.getMatrix();
% inv_vec = inv.getVector();
% assert(isequal(inv_mat,[1 2; 3 4]));
% assert(isequal(inv_vec, [1;2]));

tran = loc3.getTransitions();
for i = 1:length(tran)
    labs = tran{i}.getLabels();
    assert(isequal(labs{1}.getName(), labels{i}.getName()));
end

out = loc3.hasExternalInput();
assert(out == 0);

loc3.setExtInput([1 2; 3 4; 5 6]);

out = loc3.hasExternalInput();
assert(out == 1);

input = loc3.getExternalInput();
assert(isequal(input, [1 2; 3 4; 5 6]));

hash = loc3.hash();
name = loc3.getName();
assert(isequal(name, 'loc3'));

linFlow = MHyProFlow(9, [1 0 0; 0 1 0; 0 0 1]);
loc1.setLinearFlow(linFlow, 1);
flow = loc1.getLinearFlow();
assert(linFlow == flow);

dim = loc3.dimension_at(1); % ---> ?

equal = (loc1 == loc3);
assert(equal == 0);
loc5 = MHyProLocation(loc3);
equal = ( loc3 == loc5);
assert(equal == 1);

nequal = (loc1 ~= loc3);
assert(nequal == 1);
nequal = (loc3 ~= loc5);
assert(nequal == 0);

boxVector = [10.2; -10; 0; 0];
boxMatrix = [1 0; -1 0; 0 1; 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
disp(['initialCond handle: ', num2str(initialCond.ObjectHandle)]);
loc1.setInvariant(initialCond);
blub = loc1.getInvariant()

%assert(initialCond.Handle == invariant.Handle);




end
