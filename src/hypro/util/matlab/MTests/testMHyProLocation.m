function res = testMHyProLocation

loc1 = MHyProLocation();
loc2 = MHyProLocation([1 0 1; 2 1 3; 1 1 1]);

tran1 = MHyProTransition();
tran2 = MHyProTransition();
transitions = {tran1, tran2};
cond = MHyProCondition([1 2; 3 4], [1; 2]);
loc3 = MHyProLocation([1 2; 3 4], transitions, cond);





res = 1;