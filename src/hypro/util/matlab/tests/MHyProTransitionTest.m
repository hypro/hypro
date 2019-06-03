function tests = MHyProTransitionTest
    tests = functiontests(localfunctions);
end

function testTransition(testCase)
tran = MHyProTransition();
copied_tran = MHyProTransition(tran);

loc1 = MHyProLocation([1 0; 2 1]);
loc2 = MHyProLocation([1 0; 0 1]);

tran_1_2 = MHyProTransition(loc1, loc2);

guard = MHyProCondition([1 2; 3 4], [1; 2]);
reset = MHyProReset();
reset.setVector([1; 2; 2], 1);
tran_full = MHyProTransition(loc1, loc2, guard, reset);

tloc = tran_full.getTarget();
assert(tloc == loc2);

sloc = tran_full.getSource();
assert(sloc == loc1);

g = tran_full.getGuard();
assert(g == guard);

g = tran_1_2.getGuard();
emptyCond = MHyProCondition();
assert(g == emptyCond);

r = tran_full.getReset();
assert(isequal(r.getVector(1), reset.getVector(1)));

tran_full.getTriggerTime();

copied_tran.isUrgent();

tran_full.isTimeTriggered();

out = tran.hasIdentityReset();
assert(out == 1);

tran.setTarget(loc2);
tran.setSource(loc1);
tran.setGuard(guard);
tran.setReset(reset);
tran.setUrgent(1);
u = tran.isUrgent();
assert(u == 1);
tran.setTriggerTime(3.1);
time = tran.getTriggerTime();
assert(time == 3.1);

lab1 = MHyProLabel('this');
lab2 = MHyProLabel('is');
lab3 = MHyProLabel('funny');

labs = {lab1, lab2, lab3};
tran.setLabels(labs);
labels = tran.getLabels();
assert(isequal(labels{1}.getName(),'this'));
assert(isequal(labels{2}.getName(),'is'));
assert(isequal(labels{3}.getName(),'funny'));

lab4 = MHyProLabel('!');
tran.addLabel(lab4);
labels = tran.getLabels();
assert(isequal(labels{4}.getName(),'!'));


equal = (tran == tran_1_2);
assert(equal == 0);

nequal = (copied_tran ~= MHyProTransition());
assert(nequal == 1);
end