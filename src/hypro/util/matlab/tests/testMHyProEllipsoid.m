function res = testMHyProEllipsoid
% This script contains tests for all functions for HyPro Ellipsoids.

rad_eli = MHyProEllipsoid(2.1, 2);
mat_eli = MHyProEllipsoid([1 2; 3 4]);
copied_eli = MHyProEllipsoid(rad_eli);

% Check if ellipsoid is empty
empty = rad_eli.isempty();
assert(empty == 0);

% Get matrix
mat = mat_eli.matrix();
assert(isequal(mat, [1 2; 3 4]));

% Check if two ellipsoids are equal
equal = (copied_eli == mat_eli);
assert(equal == 0);
equal = (copied_eli == rad_eli);
assert(equal == 1);

% Get dimension of an ellipsoid
dim = rad_eli.dimension();
assert(dim == 2);

% Check if two ellipsoids are unequal
unequal = (copied_eli ~= mat_eli);
assert(unequal == 1);
unequal = (copied_eli ~= rad_eli);
assert(unequal == 0);

% Perform linear transformation on an ellipsoid
transEli = mat_eli.linearTransformation([2 0; 0 1]);
mat = transEli.matrix();
% assert(isequal(mat, [2 4; 9 12])); ---> ?

% Perform affine transformation on an ellipsoid
affEli = mat_eli.affineTransformation([1 0; 0 1], [2; 1]);
mat = affEli.matrix();
% assert(isequal(mat, [])); ---> ?

% Add two ellipsoids
sum = rad_eli + mat_eli;
mat = sum.matrix();
% assert(); ---> ?

% Approximate ellipsoid matrix
approx = rad_eli.approxEllipsoidMatrix([1 2; 0 1]);
%assert(); ---> ?

res = 1;