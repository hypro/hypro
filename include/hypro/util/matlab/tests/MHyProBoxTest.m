function tests = MHyProBoxTest
    tests = functiontests(localfunctions);
end

function testBox(testCase)
%Test Basic Functionality
%This script contains tests for all functions for HyPro Boxes.

inter = [-6 27; 23 179; 5 153; -41 -24; -25 145];
points = [0 2; 0 1; 32 -109];

% Construct an empty box
empty_box = MHyProBox();
isEmpty = empty_box.isempty();
assert(isEmpty == 1);

% Construct a box from single interval
box = MHyProBox('interval', [2 5]);
interval = box.intervals();
assert(isequal(interval, [2 5]));

% Construct a box from a list of intervals
intervals_box = MHyProBox('intervals',inter);
intervals = intervals_box.intervals();
assert(isequal(inter,intervals));

% Construct box from a pair of points
points_box = MHyProBox('points',points);
intervals = points_box.intervals();
assert(isequal(intervals, [0 2; 0 1; 0 0]));

% Empty box in given dimension
empty_box = points_box.empty(7);
intervals = empty_box.intervals();
assert(isequal(intervals, zeros(7,2)));

% Get verices of 3D box
box = MHyProBox('intervals', [0 1; 0 1; 0 1]);
ver = box.vertices();
assert(isequal(ver, [0 1 0 1 0 1 0 1; 0 0 1 1 0 0 1 1; 0 0 0 0 1 1 1 1]));

% Copy a box
points_box = MHyProBox('points',points);
copied_box = MHyProBox(points_box);
assert(points_box == copied_box);

% Construct box from matrix and vector
mat_vec_box = MHyProBox([1 0; -1 0; 0 1; 0 -1],[1;-1;1;-1]);
matrix = mat_vec_box.matrix();
vector = mat_vec_box.vector();
assert(isequal(matrix, [1 0; -1 0; 0 1; 0 -1]));
assert(isequal(vector, [1;-1;1;-1]));

% Construct box from single interval
interval_box = MHyProBox('interval',[2 4]);
intervals = interval_box.intervals();
assert(isequal(intervals, [2 4]));

% Insert an interval to a box
intervals_box = MHyProBox('intervals',[1 2; 3 4; 5 6]);
intervals_box.insert([11 12]);
intervals = intervals_box.intervals();
assert(isequal([1 2; 3 4; 5 6; 11 12], intervals));

% Construct an empty box of required dimension
box = MHyProBox();
box = box.empty(50);
assert(box.dimension() == 50);

% Get limits of intervals_box
box = MHyProBox('intervals', [0 2; 0 1]);
limits = box.limits();
assert(isequal([0 2; 0 1], limits));

% Get constraints defining a box
box = MHyProBox('points', [1 1; 2 3]);
[h_mat, h_vec] = box.constraints();
assert(isequal(h_mat, [1 0; -1 0; 0 1; 0 -1]));
assert(isequal(h_vec, [1;-1;3;-2]));


% Get an interval at certain position
box = MHyProBox('intervals',inter);
interval = box.interval(2);
assert(isequal(interval, [23 179]));

% Get interval representation at certain position
box = MHyProBox('intervals',inter);
interval = box.at(2);
assert(isequal(interval,[23 179]));

% Check if a matrix is symmetric
notsymmetric_box = MHyProBox('intervals', [1 2; 1 2]);
out = notsymmetric_box.isSymmetric();
assert(out == 0);
symmetric_box = MHyProBox('intervals', [-1 1; -1 1]);
out = symmetric_box.isSymmetric();
assert(out == 1);

% Get maximal point of box
notsymmetric_box = MHyProBox('intervals', [1 2; 1 2]);
maximal = notsymmetric_box.max();
assert(isequal(maximal, [2; 2]));

% Get minimal point of box
notsymmetric_box = MHyProBox('intervals', [1 2; 1 2]);
minimal = notsymmetric_box.min();
assert(isequal(minimal, [1;1]));

% Get supremum of box
symmetric_box = MHyProBox('intervals', [-1 1; -1 1]);
supremum = symmetric_box.supremum();
assert(supremum == 1);

% Check if points_box and copied_box are equal
box = MHyProBox('intervals', [1 2; 1 2]);
box_copy = MHyProBox(box);
equal = (box == box_copy);
assert(equal == 1);

% Check if points_box equals box
box1 = MHyProBox('intervals', [1 2; 3 4; 5 6]);
box2 = MHyProBox('intervals', [1 2; 1 2]);
equal = (box1 == box2);
assert(equal == 0);

% Check if points_box unequals copied_box
box = MHyProBox('intervals', [1 2; 1 2]);
box_copy = MHyProBox(box);
unequal = (box ~= box_copy);
assert(unequal == 0);

% Check if points_box unequals box
box1 = MHyProBox('interval', [1 2; 3 4; 5 6]);
box2 = MHyProBox('intervals', [1 2; 1 2]);
unequal = (box1 ~= box2);
assert(unequal == 1);

% Get dimension of box
box = MHyProBox('interval', [1 2; 3 4; 5 6]);
dim = box.dimension();
assert(dim == 1);

% Make a non-symmetric box symmetric
box = MHyProBox('interval',[1 2; 1 2]);
symm = box.isSymmetric();
assert(symm == 0);
symmbox = box.makeSymmetric();
symm = symmbox.isSymmetric();
assert(symm == 1);

% Check if box satisfies a halfspace
box = MHyProBox('intervals', [3 5; 2 4]);
hs_normal = [0; 0; -1];
hs_offset = -1;
[containment, ~] = box.satisfiesHalfspace(hs_normal, hs_offset);
assert(containment == "NO");
assert(isequal(hs_normal, [0; 0; -1]));
assert(isequal(hs_offset, -1));

% Check if the same box satisfies another halfspace
box = MHyProBox('intervals', [3 5; 2 4]);
mat = eye(2);
vec = [3; 5];
[containment,~] = box.satisfiesHalfspaces(mat, vec);
assert(containment == "PARTIAL");

% Project a box on a certain dimension
box = MHyProBox('intervals', [3 5; 2 4; 1 2]);
disp('+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++')
projbox = box.projectOn([1;2]);
inter = projbox.intervals();
assert(isequal(inter, [3 5; 2 4]))

% Perform linear transformation of a box
box = MHyProBox('intervals', [3 5; 2 4; 1 2]);
mat = [2 0 0; 0 4 0; 0 0 1];
transBox = box.linearTransformation(mat);
inter = transBox.intervals();
assert(isequal(inter, [6 10; 8 16; 1 2]));

% Perform affine transformation of a box
box = MHyProBox('intervals', [3 5; 2 4; 1 2]);
mat = [2 0 0; 0 4 0; 0 0 1];
vec = [2; 1; 2];
transBox = box.affineTransformation(mat, vec);
inter = transBox.intervals();
assert(isequal(inter, [8 12; 9 17; 3 4]));

% Add two boxes
box1 = MHyProBox('intervals', [1 3; 1 3]);
box2 = MHyProBox('intervals', [4 6; 3 5]);
mSum = box1 + box2;
inter = mSum.intervals();
assert(isequal(inter, [5 9; 4 8]));

% Perform Minkowski decomposition
box1 = MHyProBox('intervals', [1 3; 1 3]);
box2 = MHyProBox('intervals', [4 6; 3 5]);
mDec = box1.minkowskiDecomposition(box2);
inter = mDec.intervals();
assert(isequal(inter, [-3 -3; -2 -2]));

% Intersect two boxes
box1 = MHyProBox('intervals', [1 3; 1 3]);
box2 = MHyProBox('intervals', [2 4; 2 4]);
intersection = box1.intersect(box2);
inter = intersection.intervals();
assert(isequal(inter, [2 3; 2 3]));

% Intersect a box with a halfspace
box1 = MHyProBox('intervals', [1 3; 1 3]);
nor = [1;0];
off = 2;
intersected = box1.intersectHalfspace(nor,off);
inter = intersected.intervals();
assert(isequal(inter, [1 2; 1 3]));

% Intersect a box with halfspaces
box1 = MHyProBox('intervals', [1 3; 1 3]);
mat = [1 0; 0 1];
vec = [2;2];
intersected = box1.intersectHalfspaces(mat,vec);
inter = intersected.intervals();
assert(isequal(inter, [1 2; 1 2]));

% Check if box contains a point
box1 = MHyProBox('intervals', [1 3; 1 3]);
contains = box1.contains([2;2]);
assert(contains == 1);

% Check if a box contains another box
box1 = MHyProBox('intervals', [1 5; 1 7]);
box2 = MHyProBox('intervals', [2 4; 2 3]);
contains = box1.contains(box2);
assert(contains == 1);

% Unite two boxes
box1 = MHyProBox('intervals', [1 5; 1 7]);
box2 = MHyProBox('intervals', [2 7; -1 9]);
uni = box1.unite(box2);
inter = uni.intervals();
assert(isequal(inter, [1 7; -1 9]));

% Unite multiple boxes
box1 = MHyProBox('intervals', [1 5; 1 7]);
box2 = MHyProBox('intervals', [2 7; -1 9]);
box3 = MHyProBox('intervals', [0 1; 9 10]);
boxes = {box1,box2,box3};
united = MHyProBox.uniteMultiple(boxes);
inter = united.intervals();
assert(isequal(inter, [0 1; -1 10]));

% Scale a box
box1 = MHyProBox('intervals', [1 5; 1 7]);
box2 = box1 * 3;
inter = box2.intervals();
assert(isequal(inter, [3 15; 3 21]));

% Reduce number of representation
box1 = MHyProBox('intervals', [1 5; 1 7; 1 2; 2 3]);
box2 = box1.reduceNumberRepresentation();
inter = box2.intervals();
assert(isequal(inter, [1 5; 1 7; 1 2; 2 3]));

%Plot
%box1.plotObj([3 4]);
end
