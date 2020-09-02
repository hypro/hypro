function tests = MHyProSupportFunctionTest
    tests = functiontests(localfunctions);
end

function testSupportFunctions(testCase)

% This script contains tests for all functions for HyPro support functions.

fct = MHyProSupportFunction();
mat_fct = MHyProSupportFunction([1 0 0; 0 1 0; 0 0 1]);
int_fct = MHyProSupportFunction('intervals', [1 2; 3 4]);
mat_vec_fct = MHyProSupportFunction([1 0; 0 1], [1; 2]);
halfs_fct = MHyProSupportFunction([-1 0; 1 0], [-2; 2]);

%TODO: Fix me
% points_fct = MHyProSupportFunction('points', [1 2; 2 3; 1 2]);

copied_fct = MHyProSupportFunction(mat_fct);


% Check for emptyness
% TODO: Fix the problem of calling isempty on empty SF
% empty = fct.isempty();
% assert(empty == 1);
empty = mat_vec_fct.isempty();
assert(empty == 0);

% Get vertices
vertices = int_fct.vertices()
% assert ---> ?

% Get supremum
sup = mat_fct.supremum;
% assert ---> ?

% Check for equality
equal = (mat_vec_fct == mat_fct);
assert(equal == 0);
equal = (copied_fct == mat_fct);
assert(equal == 1);

% Get dimension
dim = mat_fct.dimension();
assert(dim == 3);

% Remove redundancy
mat_fct.removeRedundancy();
% assert ---> ?

% Get size
s = mat_fct.size();

% Get type
type = fct.type();
assert(strcmp(type, "MHyProSupportFunction"));

% Reduce the number of representation
mat_vec_fct.reduceNumberRepresentation();

% Check if satisfies a halfspace
hs_normal = [0; 0; -1];
hs_offset = -1;
[containment, ~] = mat_fct.satisfiesHalfspace(hs_normal, hs_offset);
% assert ---> ?

% Check if the same box satisfies another halfspace
mat = eye(2);
vec = [3; 5];
[containment,~] = mat_fct.satisfiesHalfspaces(mat, vec);
% assert ---> ?

% Project a support function on a certain dimension
fct = MHyProSupportFunction('intervals', [3 5; 2 4; 1 2]);
projfct = fct.projectOn([1 2]);
mat = projfct.matrix();
% assert ---> ?

% Perform linear transformation
mat = [2 0 0; 0 4 0; 0 0 1];
transFct = fct.linearTransformation(mat);
mat = transFct.matrix();
% assert ---> ?

% Perform affine transformation
mat = [2 0 0; 0 4 0; 0 0 1];
vec = [2; 1; 2];
transFct = fct.affineTransformation(mat, vec);
mat = transFct.matrix();
% assert ---> ?

% Add functions
fct1 = MHyProSupportFunction('intervals', [1 3; 1 3]);
fct2 = MHyProSupportFunction('intervals', [4 6; 3 5]);
mSum = fct1 + fct2;
mat = mSum.matrix();
% assert ---> ?

% Intersect two boxes
fct2 = MHyProSupportFunction('intervals', [2 4; 2 4]);
intersection = fct1.intersect(fct2);
mat = intersection.matrix();
% assert ---> ?

% Intersect with a halfspace
nor = [1;0];
off = 2;
intersected = fct1.intersectHalfspace(nor,off);
mat = intersected.matrix();
% assert ---> ?

% Intersect with halfspaces
mat = [1 0; 0 1];
vec = [2;2];
intersected = fct1.intersectHalfspaces(mat,vec);
mat = intersected.matrix();
% assert ---> ?

% Check if box contains a point
contains = fct1.containsPoint([2;2]);
assert(contains == 1);

% Check if contains another support function
contains = fct2.contains(fct1);
assert(contains == 0);

% Check if contains vector
contains = fct1.contains([1; 2; 3]);
assert(contains == 1);

% Unite two support functions
fct1 = MHyProSupportFunction('intervals', [1 3; 2 3]);
fct2 = MHyProSupportFunction('intervals', [2 4; 1 4]);
uni = fct2.unite(fct1);

% Unite multiple support functions
fct3 = MHyProSupportFunction('intervals', [3 4; 1 3]);
functions = {fct1,fct2, fct3};
% ufct = MHyProSupportFunction.uniteMultiple(functions); --->!!!

end
