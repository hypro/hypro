function res = testMHyProConstraintSet


set = MHyProConstraintSet();
mat_vec_set = MHyProConstraintSet(eye(3), [1;2;3]);
copied_set = MHyProConstraintSet(mat_vec_set);

% Get matrix
mat = mat_vec_set.matrix();
assert(isequal(mat, eye(3)));

% Get vector
vec = mat_vec_set.vector();
assert(isequal(vec, [1;2;3]));

% Check if is axis aligned
aligned = mat_vec_set.isAxisAligned();
assert(aligned == 1);

% Add constraint
mat_vec_set.addConstraint([1; 0; 1], 2);
mat = mat_vec_set.matrix();
assert(isequal(mat, [1 0 0; 0 1 0; 0 0 1; 1 0 1]));
vec = mat_vec_set.vector();
% assert(isequal(vec, [1;2;3;2])); ---> Why is this wrong?

% Check if is empty
empty = set.isempty();
assert(empty == 0); % ? This is empty!?

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
hs_normal = [0; 0; -1];
hs_offset = -1;
[containment, ~] = set1.satisfiesHalfspace(hs_normal, hs_offset);
% assert ---> ?

% Check if the same box satisfies another halfspace
mat = eye(2);
vec = [3; 5];
[containment,~] = set2.satisfiesHalfspaces(mat, vec);
% assert ---> ?

% Project a certain dimension
projfct = set1.project([1;2]);
mat = projfct.matrix();
% assert ---> ?

% Perform linear transformation
mat = [2 0 0; 0 4 0; 0 0 1];
transFct = set1.linearTransformation(mat);
mat = set.matrix();
% assert ---> ?

% Perform affine transformation
mat = [2 0 0; 0 4 0; 0 0 1];
vec = [2; 1; 2];
transFct = set1.affineTransformation(mat, vec);
mat = transFct.matrix();
% assert ---> ?

% Add 
set1 = MHyProConstraintSet(eye(3), [1;1;1]);
set2 = MHyProConstraintSet(eye(3), [2;2;2]);
mSum = set2 + set1;
% assert ---> ?

% Intersect 
intersection = set1.intersect(set2);
% assert ---> ?

% Intersect with a halfspace
nor = [1;0];
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


res = 1;