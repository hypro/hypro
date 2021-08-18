function tests = MHyProConstraintTest
    tests = functiontests(localfunctions);
end

function testConstraintSet(testCase)

% Test Basic Functionality
set = MHyProConstraintSet();
mat_vec_set = MHyProConstraintSet([1 0 0 0; 0 1 0 0; 0 0 1 0],[1;2;3]);
copied_set = MHyProConstraintSet(mat_vec_set);
assert(isequal(mat_vec_set.matrix(), [1 0 0 0; 0 1 0 0; 0 0 1 0]));
assert(isequal(mat_vec_set.vector(), [1; 2; 3]));

% Get matrix
mat = mat_vec_set.matrix();
assert(isequal(mat, [1 0 0 0; 0 1 0 0; 0 0 1 0]));

% Get vector
vec = mat_vec_set.vector();
assert(isequal(vec, [1;2;3]));

% Check if is axis aligned
aligned = mat_vec_set.isAxisAligned();
assert(aligned == 1);

% Add constraint
mat_vec_set.addConstraint([2 3 0 1], 2);
mat = mat_vec_set.matrix();
assert(isequal(mat, [1 0 0 0; 0 1 0 0; 0 0 1 0; 2 3 0 1]));
vec = mat_vec_set.vector();
assert(isequal(vec, [1;2;3;2]));

% Check if is empty
empty = set.isempty();
assert(empty == 0);

% Check for equality
set1 = MHyProConstraintSet(eye(3), [1;2;3]);
set2 = MHyProConstraintSet(set1);
equal = (set1 == set2);
assert(equal == 1);
equal = (set == copied_set);
assert(equal == 0);

% Check for inequality
nequal = (set ~= mat_vec_set);
assert(nequal == 1);
nequal = (set1 ~= set2);
assert(nequal == 0);

% Get dimension
dim = set1.dimension();
assert(dim == 3);

% Remove redundancy
set2.removeRedundancy();

% Check if satisfies a halfspace
set1 = MHyProConstraintSet(eye(3), [2;1;2]);
hs_normal = [0;0;-1];
hs_offset = -5;
[containment, set] = set1.satisfiesHalfspace(hs_normal, hs_offset);
emt = set.isempty();
assert(isequal(containment,'NO'));
assert(emt == 0);

% Check if the same box satisfies another halfspace
set1 = MHyProConstraintSet(eye(3), [1;1;1]);
mat = [1 1 0; 0 1 1; 1 0 1];
vec = [0;0;1];
[containment, set] = set1.satisfiesHalfspaces(mat, vec);
emt = set.isempty();
assert(isequal(containment,'NO'));
assert(emt == 0);

% Project a certain dimension
set1 = MHyProConstraintSet([1 1 0; 0 0 1; 1 0 1], [1;2;1]);
projected = set1.projectOn([1 3]);

% Perform linear transformation
set1 = MHyProConstraintSet([1 2 0 3; 0 0 1 2; 1 0 1 5; 1 1 1 -7], [3;2;4;1]);
mat = [2 1 0 0; 0 4 2 0; 1 1 1 0];
transSet = set1.linearTransformation(mat);
mat = transSet.matrix();
assert(isequal(mat,[1 2 0 3; 0 0 1 2; 1 0 1 5; 1 1 1 -7]));

dim = set.dimension();
assert(dim == 3);

% Perform affine transformation
mat = [2 0 0; 0 4 0; 0 0 1];
vec = [2; 1; 2];
transFct = set1.affineTransformation(mat, vec);
mat = transFct.matrix();
assert(isequal(mat,[1 2 0 3; 0 0 1 2; 1 0 1 5; 1 1 1 -7]));

% Add
set1 = MHyProConstraintSet([1 2 3; 2 2 2; 1 0 0], [2;1; 3]);
set2 = MHyProConstraintSet(1*eye(3), [2;2;2]);
mSum = set1 + set2;
assert(isequal(mSum.matrix(),[1 2 3; 2 2 2; 1 0 0] ));

% Intersect
intersection = set1.intersect(set2);
assert(isequal(intersection.matrix(),[1 2 3; 2 2 2; 1 0 0] ));

% Intersect with a halfspace
disp('+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++');
nor = [1;1;0];
off = 2;
intersected = set1.intersectHalfspace(nor,off);
% assert ---> ?

% Intersect with halfspaces
mat = [1 0; 0 1];
vec = [2;2];
intersected = set1.intersectHalfspaces(mat,vec);
% assert ---> ?

% Check if box contains a point
contains = set1.containsPoint([2;2;1]);
assert(contains == 1);
vertices = set1.vertices();

% Check if contains another constraint set
contains = set1.contains(set2);
assert(contains == 1);


% Unite two sets
uni = set2.unite(set1);
% assert ---> ?

% Unite multiple constraint sets
set1 = MHyProConstraintSet(eye(2), [1; 5]);
set2 = MHyProConstraintSet(eye(3), [2; 7;-1]);
set3 = MHyProConstraintSet(eye(1), [2]);
sets = {set2, set3};
% united = set1.unite(sets);
% assert ---> ?

%set1.plot([1 2]);
end
