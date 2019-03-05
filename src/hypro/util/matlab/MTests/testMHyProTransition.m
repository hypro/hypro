function res = testMHyProTransition

tran = MHyProTransition();
copied_tran = MHyProTransition(tran);

loc1 = MHyProLocation([1 0; 2 1]);
loc2 = MHyProLocation([1 0; 0 1]);

tran_1_2 = MHyProTransition(loc1, loc2);



res = 1;