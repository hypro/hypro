function res = testMHyProBox
% This script contains tests for all functions for HyPro Boxes.

disp('Run Tests for MHyProBoxes');
inter = [1 2; 3 4; 5 6];
points = [0 0; 2 2];
insert_inter = [12 41];
mat = [1 2 3; 4 5 6; 7 8 9];
vec = [1; 2; 3];


% Construct an empty box
empty_box = MHyProBox();
isEmpty = empty_box.isempty();
assert(isEmpty == 1);

%Construct a box from a list of intervals
intervals_box = MHyProBox('intervals',inter);
intervals = intervals_box.intervals();
assert(isequal(inter,intervals));
 
% Construct box from a pair of points
points_box = MHyProBox('points',points);
intervals = points_box.intervals();
assert(isequal(intervals, points));

% Copy a box
copied_box = MHyProBox(points_box);
intervals = copied_box.intervals();
assert(isequal(intervals, points));

% Construct box from matrix and vector
mat_vec_box = MHyProBox([1 0; 0 1],[0;0]);
matrix = mat_vec_box.matrix();
vector = mat_vec_box.vector();
% assert(matrix, mat);
% assert(vector, vec);
% TODO: Shouldn't the assertions be correct?

% Construct box from single interval
interval_box = MHyProBox('interval',[2 4]);
intervals = interval_box.intervals();
assert(isequal(intervals, [2 4]));

% Insert an interval to a box

intervals_box.insert([11 12]);
intervals = intervals_box.intervals();
assert(isequal([1 2; 3 4; 5 6; 11 12], intervals));

% Construct an empty box of required dimension
new_box = intervals_box.empty(5);
intervals = new_box.matrix();
%assert(?);

% Get limits of intervals_box
limits = intervals_box.limits();
assert(isequal([1 2; 3 4; 5 6; 11 12], limits));

% Get constraints defining a box


% disp('Interval');
% box_11 = MHyProObject('Box','new_intervals',inter);
% inter_11 = box_11.interval(2);
% disp('Box 11 interval at position 2:');
% disp(inter_11);
% 
% disp('At');
% box_12 = MHyProObject('Box', 'new_intervals',inter);
% inter_12 = box_12.at(3);
% disp('Box 12 interval at position 3:');
% disp(inter_12);
% 
% disp('Is Empty');
% box_13 = MHyProObject('Box', 'new_intervals',inter);
% a = box_13.isempty();
% disp('Is box 13 empty? :');
% disp(a);
% box_14 = MHyProObject('Box', 'new_empty');
% b = box_14.isempty();
% disp('Is box 14 empty? :');
% disp(b);
% 
% disp('Is Symmetric');
% box_15 = MHyProObject('Box','new_intervals', [1 2; 1 2]);
% a = box_15.isSymmetric();
% disp('Is box 15 symmetric? :');
% disp(a);
% box_16 = MHyProObject('Box', 'new_intervals', [-1 1; -1 1]);
% b = box_16.isSymmetric();
% disp('Is box 16 symmetric? :');
% disp(b);
% 
% disp('Get Max');
% box_17 = MHyProObject('Box','new_intervals', [1 2; 1 2]);
% m = box_17.max();
% disp('Box 17 max:');
% disp(m);
% 
% disp('Get Min');
% box_18 = MHyProObject('Box','new_intervals', [1 2; 1 2]);
% m = box_18.min();
% disp('Box 18 min:');
% disp(m);
% 
% disp('Get Supremum');
% box_19 = MHyProObject('Box','new_intervals', [1 2; 1 2]);
% m = box_19.supremum();
% disp('Box 19 supremum:');
% disp(m);
% 
% disp('Get Vertices');
% box_20 = MHyProObject('Box','new_intervals', [0 1; 0 1; 0 1]);
% m = box_20.vertices();
% disp('Box 20 vertices:');
% disp(m);
% 
% disp('==');
% box_23 = MHyProObject('Box', 'new_intervals', [1 2; 1 2]);
% box_24 = MHyProObject('Box','new_intervals', [1 2; 1 2]);
% disp('Are box 23 and box 24 equal? :');
% a = (box_23 == box_24);
% disp(a);
% box_25 = MHyProObject('Box','new_intervals', [1 2; 2 5; 1 2]);
% disp('Are box 23 and box 25 equal? :');
% a = box_23.eq(box_25);
% disp(a);
% 
% disp('!=');
% box_26 = MHyProObject('Box','new_intervals', [1 2; 1 2]);
% box_27 = MHyProObject('Box','new_intervals', [1 2; 1 2]);
% disp('Are box 26 and box 27 unequal? :');
% a = (box_26 ~= box_27);
% disp(a);
% box_28 = MHyProObject('Box','new_intervals', [1 2; 2 5; 2 3]);
% disp('Are box 26 and box 28 unequal? :');
% a = (box_26 ~= box_28);
% disp(a);
% 
% disp('Dimension');
% box_29 = MHyProObject('Box','new_intervals', [1 2; 1 2]);
% dim = box_29.dimension();
% disp('Box 29 dimension: ');
% disp(dim);
% 
% disp('Make Symmetric');
% box_30 = MHyProObject('Box','new_intervals',[1 2; 1 4]);
% old_intervals = box_30.intervals();
% disp('Old intervals:');
% disp(old_intervals);
% box_30.makeSymmetric();
% new_intervals = box_30.intervals();
% disp('New intervals:');
% disp(new_intervals);
% 
% %disp('Constraints');
% % box_31 = MHyProObject('Box','new_intervals', [3 5; 2 4]);
% % [normal_vecs, offsets] = box_31.constraints();
% % disp(normal_vecs);
% % disp(offsets);
% 
% disp('Satisfies Halfspace');
% box_32 = MHyProObject('Box','new_intervals', [3 5; 2 4]);
% hs_normal = [1 0];
% hs_offset = 2;
% [containment, box] = box_32.satisfiesHalfspace(hs_normal, hs_offset);
% disp('containment:');
% disp(containment);
% 
% disp('Satisfies Halfspaces');
% box_33 = MHyProObject('Box', 'new_intervals', [3 5; 2 4]);
% mat = [1 0; 0 1];
% vec = [2 3];
% [containment, box] = box_33.satisfiesHalfspaces(mat, vec);
% disp('containment:');
% disp(containment);
% 
% disp('Project');
% box_34 = MHyProObject('Box','new_intervals', [3 5; 2 4; 1 2]);
% dims = 2;
% box = box_34.project(dims);
% inter = box.intervals();
% disp('Intervals of the new box:');
% disp(inter);
% 
% disp('Linear Transformation');
% box_35 = MHyProObject('Box','new_intervals', [3 5; 2 4]);
% mat = [2 0; 0 4];
% box = box_35.linearTransformation(mat);
% inter = box.intervals();
% disp('Intervals of the transformed box:');
% disp(inter);
% 
% disp('Affine Transformation');
% box_36 = MHyProObject('Box','new_intervals', [3 5; 2 4]);
% mat = [2 0; 0 4];
% vec = [2 1];
% box = box_36.affineTransformation(mat, vec);
% inter = box.intervals();
% disp('Intervals of the transformed box:');
% disp(inter);
% 
% disp('Minkowski Sum');
% box_37 = MHyProObject('Box','new_intervals', [1 3; 1 3]);
% box_38 = MHyProObject('Box', 'new_intervals', [4 6; 3 5]);
% mSum = box_3 + box_38;
% inter = mSum.intervals();
% disp('Intervals of the sum:');
% disp(inter);
% 
% disp('Minkowski Decomposition');
% box_39 = MHyProObject('Box', 'new_intervals', [1 3; 1 3]);
% box_40 = MHyProObject('Box', 'new_intervals', [4 6; 3 5]);
% mDec = box_39.minkowskiDecomposition(box_40);
% inter = mDec.intervals();
% disp('Intervals:');
% disp(inter);
% 
% disp('Intersect');
% box_41 = MHyProObject('Box', 'new_intervals', [1 3; 1 3]);
% box_42 = MHyProObject('Box', 'new_intervals', [4 6; 3 5]);
% intersected = box_41.intersect(box_42);
% inter = intersected.intervals();
% disp('Intervals:');
% disp(inter);
% 
% disp('Intersect Halfspace');
% box_43 = MHyProObject('Box','new_intervals', [1 3; 1 3]);
% nor = [1 0];
% off = 2;
% intersected = box_43.intersectHalfspace(nor,off);
% inter = intersected.intervals();
% disp('Intervals:');
% disp(inter);
% 
% disp('Intersect Halfspaces');
% box_44 = MHyProObject('Box','new_intervals', [1 3; 1 3]);
% mat = [1 0; 0 1];
% vec = [2 3];
% intersected = box_44.intersectHalfspace(mat,vec);
% inter = intersected.intervals();
% disp('Intervals:');
% disp(inter);
% 
% disp('Contains Point');
% box_45 = MHyProObject('Box','new_intervals', [1 3; 2 5]);
% point = [2; 3];
% contains = box_45.contains(point);
% disp('Box 45 contains point (2, 3):');
% disp(contains);
% 
% disp('Contains Box');
% box_46 = MHyProObject('Box', 'new_intervals', [1 5; 1 7]);
% box_47 = MHyProObject('Box', 'new_intervals', [2 4; 2 3]);
% contains = box_46.contains(box_47);
% disp('Box 46 contains box 47:');
% disp(contains);
% 
% disp('Unite Box');
% box_48 = MHyProObject('Box', 'new_intervals', [1 5; 1 7]);
% box_49 = MHyProObject('Box', 'new_intervals', [2 7; -1 9]);
% uni = box_48.unite(box_49);
% disp('Unite boxes 48 and 49:');
% inter = uni.intervals();
% disp('Intervals:');
% disp(inter);
% 
% % disp('Unite Boxes');
% % box_50 = MHyProObject('Box','new_intervals', [1 5; 1 7]);
% % box_51 = MHyProObject('Box','new_intervals', [2 7; -1 9]);
% % box_52 = MHyProObject('Box','new_intervals', [0 1; 9 10]);
% % boxes = {box_51, box_52};
% % box_50.unite(boxes);
% % out = MHyProObject('unite_boxes', box_50, boxes);
% % disp('Unite boxes 50, 51, and 52:');
% % inter = MHyProObject('intervals', uni);
% % disp('Intervals:');
% % disp(inter);
% % HyProObject('delete', box_50);
% % HyProObject('delete', box_51);
% % HyProObject('delete', box_52);
% % HyProObject('delete', uni);
% 
% disp('* (Scale)');
% box_53 = MHyProObject('Box', 'new_intervals', [1 5; 1 7]);
% box_54 = box_53 * 3;
% inter = box_54.intervals();
% disp('Intervals:');
% disp(inter);
% 
% disp('<<');
% box_54 = MHyProObject('Box', 'new_intervals', [1 5; 1 7]);
% box_54.ostream();
% m = box_54.matrix();
% disp('Matrix of box_54');
% disp(m);
% v = box_54.vector();
% disp('Vector of box_54');
% disp(v);
% 
% disp('reduceNumberRepresentation');
% box_55 = MHyProObject('Box', 'new_intervals', [1 5; 1 7; 1 2; 2 3]);
% box_56 = box_55.reduceNumberRepresentation();
% inter = box_56.intervals();
% disp('Intervals:');
% disp(inter);

res = 1;
