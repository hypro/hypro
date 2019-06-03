function tests = MHyProResetTest
    tests = functiontests(localfunctions);
end

function testReset(testCase)

reset_empty = MHyProReset();

empty = reset_empty.isempty();
assert(empty == 1);

size = reset_empty.size();
assert(size == 0);

reset = MHyProReset();
reset.setVector([1; 2; 2]);
empty = reset.isempty();
assert(empty == 0);

vec = reset.getVector(1)
assert(isequal(vec, [1;2;2]));

reset.setMatrix([1 2 0; 2 3 3; 1 0 0]);
mat = reset.getMatrix(1);
assert(isequal(mat, [1 2 0; 2 3 3; 1 0 0]));

reset1 = MHyProReset();
reset1.setIntervals([1 2; 3 4; 5 6], 1);
inter = reset1.getIntervals(1);
assert(isequal(inter, [1 2; 3 4; 5 6]));

constr = reset1.getAffineReset(1);

reset1.setIntervals([1 3; 3 7; 10 110], 2);
inter = reset1.getIntervals(1);
s = reset1.size();
assert(s == 2);

inter = reset1.getIntervals(2);
assert(isequal(inter, [1 3; 3 7; 10 110]));


inter = reset1.getIntervalReset(2);

intervals = reset1.getIntervalResets();
assert(isequal(intervals{1}, [1 2; 3 4; 5 6]));
assert(isequal(intervals{2}, [1 3; 3 7; 10 110]));

hash = reset1.hash();
end
