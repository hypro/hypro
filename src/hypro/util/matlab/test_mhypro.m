function res = test_mhypro

%**************************************************************************
% Tests for HyPro Boxes
%**************************************************************************
inter = [1 2; 3 4; 5 6; 7 8; 9 10];
points = [0 0; 2 2];
insert_inter = [12 41];
mat = [1 0 0; 0 1 0; 0 0 1];
vec = [1; 2; 3];
single_inter = [2 4];


%****************************Constructors**********************************

disp('Construct empty box');
box_0 = HyProObject('Box','new_empty');
intervals_box_0 = box_0.intervals();
disp('Box 0 intervals:');
disp(intervals_box_0);

disp('Construct box from list of intervals');
box_1 = HyProObject('Box','new_intervals',inter);
intervals_box_1 = box_1.intervals();
disp('Box 1 intervals:');
disp(intervals_box_1);

disp('Construct box from a pair of points');
box_2 = HyProObject('Box','new_points',points);
box_2_inter = box_2.intervals();
disp('Box 2 intervals:');
disp(box_2_inter);

disp('Copy a box');
box_3 = HyProObject('Box','new_intervals',inter);
box_4 = HyProObject('Box', 'copy', box_3);
box_4_inter = box_4.intervals();
disp('Box 4 intervals:');
disp(box_4_inter);

disp('Construct box from matrix and vector');
box_5 = HyProObject('Box','new_matrix',mat,vec);
box_5_inter = box_5.intervals();
disp('Box 5 intervals:');
disp(box_5_inter);

disp('Construct box from single interval');
box_6 = HyProObject('Box','new_interval',single_inter);
box_6_inter = box_6.intervals();
disp('Box 6 interval:');
disp(box_6_inter);

%**************************Getters&Setters*********************************

disp('Insert');
box_7 = HyProObject('Box', 'new_intervals',inter);
old_intervals = box_7.intervals();
disp('Old intervals:');
disp(old_intervals);
box_7.insert(insert_inter);
new_intervals = box_7.intervals();
disp('New intervals:');
disp(new_intervals);

% disp('Empty'); TODO
% box_8 = HyProObject('Box','new_intervals',inter);
% old_intervals = box_8.intervals();
% disp('Old intervals:');
% disp(old_intervals);
% box_8_1 = box_8.empty_dim(2);
% new_intervals = box_8_1.intervals();
% disp('New intervals:');
% disp(new_intervals);

disp('Limits');
box_9 = HyProObject('Box','new_intervals',inter);
limits = box_9.limits();
disp('Limits of box 9:');
disp(limits);

disp('Constraints');
%box_10

disp('Interval');
box_11 = HyProObject('Box','new_intervals',inter);
inter_11 = box_11.interval(2);
disp('Box 11 interval at position 2:');
disp(inter_11);

disp('At');
box_12 = HyProObject('Box', 'new_intervals',inter);
inter_12 = box_12.at(3);
disp('Box 12 interval at position 3:');
disp(inter_12);

% disp('Is Empty');
% box_13 = HyProObject('Box', 'new_intervals',inter);
% a = box_13.empty();
% disp('Is box 13 empty? :');
% disp(a);
% box_14 = HyProObject('Box', 'new_empty');
% b = box_14.empty();
% disp('Is box 14 empty? :');
% disp(b);

disp('Is Symmetric');
box_15 = HyProObject('Box','new_intervals', [1 2; 1 2]);
a = box_15.isSymmetric();
disp('Is box 15 symmetric? :');
disp(a);
box_16 = HyProObject('Box', 'new_intervals', [-1 1; -1 1]);
b = box_16.isSymmetric();
disp('Is box 16 symmetric? :');
disp(b);

disp('Get Max');
box_17 = HyProObject('Box','new_intervals', [1 2; 1 2]);
m = box_17.max();
disp('Box 17 max:');
disp(m);

disp('Get Min');
box_18 = HyProObject('Box','new_intervals', [1 2; 1 2]);
m = box_18.min();
disp('Box 18 min:');
disp(m);

disp('Get Supremum');
box_19 = HyProObject('Box','new_intervals', [1 2; 1 2]);
m = box_19.supremum();
disp('Box 19 supremum:');
disp(m);

disp('Get Vertices');
box_20 = HyProObject('Box','new_intervals', [0 1; 0 1; 0 1]);
m = box_20.vertices();
disp('Box 20 vertices:');
disp(m);

% disp('Evaluate');
% box_21 = HyProObject('Box','new_intervals', [1 5; 2 7]);
% vec = [1 0];
% dir = 0;
% eval = box_21.evaluate(vec, dir);
% One has to delete eval again! - Destructor needed
% 
% disp('MutliEvaluate');
% %box_22

disp('==');
box_23 = HyProObject('Box', 'new_intervals', [1 2; 1 2]);
box_24 = HyProObject('Box','new_intervals', [1 2; 1 2]);
disp('Are box 23 and box 24 equal? :');
a = box_23.equal(box_24);
disp(a);
box_25 = HyProObject('Box','new_intervals', [1 2; 2 5; 1 2]);
disp('Are box 23 and box 25 equal? :');
a = box_23.equal(box_25);
disp(a);

disp('!=');
box_26 = HyProObject('Box','new_intervals', [1 2; 1 2]);
box_27 = HyProObject('Box','new_intervals', [1 2; 1 2]);
disp('Are box 26 and box 27 unequal? :');
a = box_26.unequal(box_27);
disp(a);
box_28 = HyProObject('Box','new_intervals', [1 2; 2 5; 2 3]);
disp('Are box 26 and box 28 unequal? :');
a = box_26.unequal(box_28);
disp(a);

disp('Dimension');
box_29 = HyProObject('Box','new_intervals', [1 2; 1 2]);
dim = box_29.dimension();
disp('Box 29 dimension: ');
disp(dim);

disp('Make Symmetric');
box_30 = HyProObject('Box','new_intervals',[1 2; 1 4]);
old_intervals = box_30.intervals();
disp('Old intervals:');
disp(old_intervals);
box_30.makeSymmetric();
new_intervals = box_30.intervals();
disp('New intervals:');
disp(new_intervals);

disp('Constraints');
box_31 = HyProObject('Box','new_intervals', [3 5; 2 4]);
[normal_vecs, offsets] = box_31.constraints();
disp(normal_vecs);
disp(offsets);

disp('Satisfies Halfspace');
box_32 = HyProObject('Box','new_intervals', [3 5; 2 4]);
hs_normal = [1 0];
hs_offset = 2;
[containment, box] = box_32.satisfiesHalfspace(hs_normal, hs_offset);
disp('containment:');
disp(containment);

disp('Satisfies Halfspaces');
box_33 = HyProObject('Box', 'new_intervals', [3 5; 2 4]);
mat = [1 0; 0 1];
vec = [2 3];
[containment, box] = box_33.satisfiesHalfspaces(mat, vec);
disp('containment:');
disp(containment);

disp('Project');
box_34 = HyProObject('Box','new_intervals', [3 5; 2 4; 1 2]);
dims = 2;
box = box_34.project(dims);
inter = box.intervals();
disp('Intervals of the new box:');
disp(inter);

disp('Linear Transformation');
box_35 = HyProObject('Box','new_intervals', [3 5; 2 4]);
mat = [2 0; 0 4];
box = box_35.linearTransformation(mat);
inter = box.intervals();
disp('Intervals of the transformed box:');
disp(inter);

disp('Affine Transformation');
box_36 = HyProObject('Box','new_intervals', [3 5; 2 4]);
mat = [2 0; 0 4];
vec = [2 1];
box = box_36.affineTransformation(mat, vec);
inter = box.intervals();
disp('Intervals of the transformed box:');
disp(inter);

disp('Minkowski Sum');
box_37 = HyProObject('Box','new_intervals', [1 3; 1 3]);
box_38 = HyProObject('Box', 'new_intervals', [4 6; 3 5]);
mSum = box_37.minkowskiSum(box_38);
inter = mSum.intervals();
disp('Intervals of the sum:');
disp(inter);

disp('Minkowski Decomposition');
box_39 = HyProObject('Box', 'new_intervals', [1 3; 1 3]);
box_40 = HyProObject('Box', 'new_intervals', [4 6; 3 5]);
mDec = box_39.minkowskiDecomposition(box_40);
inter = mDec.intervals();
disp('Intervals:');
disp(inter);

disp('Intersect');
box_41 = HyProObject('Box', 'new_intervals', [1 3; 1 3]);
box_42 = HyProObject('Box', 'new_intervals', [4 6; 3 5]);
intersected = box_41.intersect(box_42);
inter = intersected.intervals();
disp('Intervals:');
disp(inter);

disp('Intersect Halfspace');
box_43 = HyProObject('Box','new_intervals', [1 3; 1 3]);
nor = [1 0];
off = 2;
intersected = box_43.intersectHalfspace(nor,off);
inter = intersected.intervals();
disp('Intervals:');
disp(inter);

disp('Intersect Halfspaces');
box_44 = HyProObject('Box','new_intervals', [1 3; 1 3]);
mat = [1 0; 0 1];
vec = [2 3];
intersected = box_44.intersectHalfspace(mat,vec);
inter = intersected.intervals();
disp('Intervals:');
disp(inter);

% disp('Contains Point'); TODO
% box_45 = HyProObject('Box','new_intervals', [1 3; 2 5]);
% point = [2; 3];
% contains = box_45.contains(point);
% disp('Box 45 contains point (2, 3):');
% disp(contains);

% disp('Contains Box'); TODO
% box_46 = HyProObject('new_intervals', [1 5; 1 7]);
% box_47 = HyProObject('new_intervals', [2 4; 2 3]);
% contains = box_46.contains(box_47);
% disp('Box 46 contains box 47:');
% disp(contains);

% disp('Unite Box');
% box_48 = HyProObject('Box', 'new_intervals', [1 5; 1 7]);
% box_49 = HyProObject('Box', 'new_intervals', [2 7; -1 9]);
% uni = box_48.unite(box_49);
% disp('Unite boxes 48 and 49:');
% inter = uni.intervals();
% disp('Intervals:');
% disp(inter);
% 
% disp('Unite Boxes');
% box_50 = HyProObject('new_intervals', [1 5; 1 7]);
% box_51 = HyProObject('new_intervals', [2 7; -1 9]);
% box_52 = HyProObject('new_intervals', [0 1; 9 10]);
% uni = HyProObject('unite_boxes', box_50, boxes);
% disp('Unite boxes 50, 51, and 52:');
% inter = HyProObject('intervals', uni);
% disp('Intervals:');
% disp(inter);
% HyProObject('delete', box_50);
% HyProObject('delete', box_51);
% HyProObject('delete', box_52);
% HyProObject('delete', uni);

disp('* (Scale)');
box_53 = HyProObject('Box', 'new_intervals', [1 5; 1 7]);
box_54 = box_53.scale(3);
inter = box_54.intervals();
disp('Intervals:');
disp(inter);

disp('<<');
box_54 = HyProObject('Box', 'new_intervals', [1 5; 1 7]);
box_54.ostream();

% disp('reduceNumberRepresentation');
% box_55 = HyProObject('Box', 'new_intervals', [1 5; 1 7; 1 2; 2 3]);
% box_56 = box_55.reduceNumberRepresentation();
% inter = box_56.intervals();
% disp('Intervals:');
% disp(inter);


disp('STOP');




res = 1;