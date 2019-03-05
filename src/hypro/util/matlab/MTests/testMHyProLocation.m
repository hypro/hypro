function res = testMHyProLocation

loc1 = MHyProLocation();
loc2 = MHyProLocation([1 0 1; 2 1 3; 1 1 1]);

tran1 = MHyProTransition();
tran2 = MHyProTransition();
transitions = {tran1, tran2};
cond = MHyProCondition([1 2; 3 4], [1; 2]);
loc3 = MHyProLocation([1 2; 3 4], transitions, cond);

loc4 = MHyProLocation(loc3);

lin_flow = loc2.getLinearFlow();
flow_mat = lin_flow.getFlowMatrix();
assert(isequal(flow_mat, [1 0 1; 2 1 3; 1 1 1]));

num_flow = loc2.getNumberFlow();
assert(num_flow == 1);

inv = loc4.getInvariant();
inv_mat = inv.getMatrix();
inv_vec = inv.getVector();
assert(isequal(inv_mat,[1 2; 3 4]));
assert(isequal(inv_vec, [1;2]));

tran = loc3.getTransitions();



res = 1;