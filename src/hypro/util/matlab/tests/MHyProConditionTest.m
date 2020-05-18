function tests = MHyProConditionTest
    tests = functiontests(localfunctions);
end

function testCondition(testCase)

cond1 = MHyProCondition();
cond2 = MHyProCondition([1 2; 3 4], [1; 2]);
cond3 = MHyProCondition(cond2);

s = cond1.size();
assert(s == 0);

empty = cond2.isempty();
assert(empty == 0);

mat = cond3.getMatrix();
assert(isequal(mat, [1 2; 3 4]));

vec = cond2.getVector();
assert(isequal(vec, [1;2]));

cond = MHyProCondition([1 0; 0 1], [1; 2]);
aligned = cond.isAxisAligned();
assert(aligned == 1);

cond = MHyProCondition([1 0; 1 1], [1; 1]);
aligned = cond.isAxisAligned_at(2);
% assert(aligned == 0); ---> ?

cond1.setMatrix(eye(3));
mat = cond1.getMatrix();
assert(isequal(mat, eye(3)));

cond1.setVector([1; 2; 3], 1);
vec = cond1.getVector();
% assert(isequal(vec, [1;2;3])); ---> ?

constr = cond3.constraints();

hash = cond3.hash();
end
