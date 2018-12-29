function res = test

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
box_0 = HyProBox('new_empty');
intervals_box_0 = HyProBox('intervals',box_0);
disp('Box 0 intervals:');
disp(intervals_box_0);
HyProBox('delete',box_0);

disp('Construct box from list of intervals');
box_1 = HyProBox('new_intervals',inter);
intervals_box_1 = HyProBox('intervals',box_1);
disp('Box 1 intervals:');
disp(intervals_box_1);
HyProBox('delete',box_1);

disp('Construct box from a pair of points');
box_2 = HyProBox('new_points',points);
box_2_inter = HyProBox('intervals',box_2);
disp('Box 2 intervals:');
disp(box_2_inter);
HyProBox('delete',box_2);

disp('Copy a box');
box_3 = HyProBox('new_intervals',inter);
box_4 = HyProBox('copy', box_3);
box_4_inter = HyProBox('intervals',box_4);
disp('Box 4 intervals:');
disp(box_4_inter);
HyProBox('delete', box_3);
HyProBox('delete', box_4);

disp('Construct box from matrix and vector');
box_5 = HyProBox('new_matrix',mat,vec);
box_5_inter = HyProBox('intervals',box_5);
disp('Box 5 intervals:');
disp(box_5_inter);
HyProBox('delete', box_5);

disp('Construct box from single interval');
box_6 = HyProBox('new_interval',single_inter);
box_6_inter = HyProBox('intervals',box_6);
disp('Box 6 interval:');
disp(box_6_inter);
HyProBox('delete', box_6);

%**************************Getters&Setters*********************************

disp('Insert');
box_7 = HyProBox('new_intervals',inter);
old_intervals = HyProBox('intervals',box_7);
disp('Old intervals:');
disp(old_intervals);
HyProBox('insert',box_7,insert_inter);
new_intervals = HyProBox('intervals',box_7);
disp('New intervals:');
disp(new_intervals);
HyProBox('delete', box_7);

disp('Empty'); 
box_8 = HyProBox('new_intervals',inter);
old_intervals = HyProBox('intervals',box_8);
disp('Old intervals:');
disp(old_intervals);
box_8_1 = HyProBox('empty',box_8, 2);
new_intervals = HyProBox('intervals',box_8_1);
disp('New intervals:');
disp(new_intervals);
HyProBox('delete', box_8);
HyProBox('delete', box_8_1);

disp('Limits');
box_9 = HyProBox('new_intervals',inter);
limits = HyProBox('limits',box_9);
disp('Limits of box 9:');
disp(limits);
HyProBox('delete', box_9);

disp('Constraints');
%box_10

disp('Interval');
box_11 = HyProBox('new_intervals',inter);
inter_11 = HyProBox('interval', box_11, 2);
disp('Box 11 interval at position 2:');
disp(inter_11);
HyProBox('delete', box_11);

disp('At');
box_12 = HyProBox('new_intervals',inter);
inter_12 = HyProBox('at', box_12, 3);
disp('Box 12 interval at position 3:');
disp(inter_12);
HyProBox('delete', box_12);

disp('Is Empty');
box_13 = HyProBox('new_intervals',inter);
a = HyProBox('isEmpty', box_13);
disp('Is box 13 empty? :');
disp(a);
HyProBox('delete', box_13);
box_14 = HyProBox('new_empty');
b = HyProBox('isEmpty',box_14);
disp('Is box 14 empty? :');
disp(b);
HyProBox('delete',box_14);

disp('Is Symmetric');
box_15 = HyProBox('new_intervals', [1 2; 1 2]);
a = HyProBox('isSymmetric', box_15);
disp('Is box 15 symmetric? :');
disp(a);
HyProBox('delete', box_15);
box_16 = HyProBox('new_intervals', [-1 1; -1 1]);
b = HyProBox('isSymmetric',box_16);
disp('Is box 16 symmetric? :');
disp(b);
HyProBox('delete',box_16);


disp('Get Max');
box_17 = HyProBox('new_intervals', [1 2; 1 2]);
m = HyProBox('max', box_17);
disp('Box 17 max:');
disp(m);
HyProBox('delete', box_17);

disp('Get Min');
box_18 = HyProBox('new_intervals', [1 2; 1 2]);
m = HyProBox('min', box_18);
disp('Box 18 min:');
disp(m);
HyProBox('delete', box_18);

disp('Get Supremum');
box_19 = HyProBox('new_intervals', [1 2; 1 2]);
m = HyProBox('supremum', box_19);
disp('Box 19 supremum:');
disp(m);
HyProBox('delete', box_19);

disp('Get Vertices');
box_20 = HyProBox('new_intervals', [0 1; 0 1; 0 1]);
m = HyProBox('vertices', box_20);
disp('Box 20 vertices:');
disp(m);
HyProBox('delete', box_20);

% disp('Evaluate');
% box_21 = HyProBox('new_intervals', [1 5; 2 7]);
% vec = [1 0];
% dir = 0;
% eval = HyProBox('evaluate', box_21, vec, dir);
% HyProBox('delete', box_21);
% One has to delete eval again!
% 
% disp('MutliEvaluate');
% %box_22

disp('==');
box_23 = HyProBox('new_intervals', [1 2; 1 2]);
box_24 = HyProBox('new_intervals', [1 2; 1 2]);
disp('Are box 23 and box 24 equal? :');
a = HyProBox('==', box_23, box_24);
disp(a);
box_25 = HyProBox('new_intervals', [1 2; 2 5; 1 2]);
disp('Are box 23 and box 25 equal? :');
a = HyProBox('==', box_23, box_25);
disp(a);
HyProBox('delete', box_23);
HyProBox('delete', box_24);
HyProBox('delete', box_25);

disp('!=');
box_26 = HyProBox('new_intervals', [1 2; 1 2]);
box_27 = HyProBox('new_intervals', [1 2; 1 2]);
disp('Are box 26 and box 27 unequal? :');
a = HyProBox('!=', box_26, box_27);
disp(a);
box_28 = HyProBox('new_intervals', [1 2; 2 5; 2 3]);
disp('Are box 26 and box 28 unequal? :');
a = HyProBox('!=', box_26, box_28);
disp(a);
HyProBox('delete', box_26);
HyProBox('delete', box_27);
HyProBox('delete', box_28);

disp('Dimension');
box_29 = HyProBox('new_intervals', [1 2; 1 2]);
dim = HyProBox('dimension',box_29);
disp('Box 29 dimension: ');
disp(dim);
HyProBox('delete', box_29);

disp('Make Symmetric');
box_30 = HyProBox('new_intervals',[1 2; 1 4]);
old_intervals = HyProBox('intervals',box_30);
disp('Old intervals:');
disp(old_intervals);
HyProBox('makeSymmetric',box_30);
new_intervals = HyProBox('intervals',box_30);
disp('New intervals:');
disp(new_intervals);
HyProBox('delete', box_30);

disp('Constraints');
box_31 = HyProBox('new_intervals', [3 5; 2 4]);
[normal_vecs, offsets] = HyProBox('constraints', box_31);
disp(normal_vecs);
disp(offsets);
HyProBox('delete', box_31);

disp('Satisfies Halfspace');
box_32 = HyProBox('new_intervals', [3 5; 2 4]);
hs_normal = [1 0];
hs_offset = 2;
[containment, box] = HyProBox('satisfiesHalfspace',box_32, hs_normal, hs_offset);
disp('containment:');
disp(containment);
HyProBox('delete', box_32);
HyProBox('delete', box);

disp('Satisfies Halfspaces');
box_33 = HyProBox('new_intervals', [3 5; 2 4]);
mat = [1 0; 0 1];
vec = [2 3];
[containment, box] = HyProBox('satisfiesHalfspaces',box_33, mat, vec);
disp('containment:');
disp(containment);
HyProBox('delete', box_33);
HyProBox('delete', box);

disp('Project');
box_34 = HyProBox('new_intervals', [3 5; 2 4; 1 2]);
dims = 2;
box = HyProBox('project', box_34, dims);
inter = HyProBox('intervals', box);
disp('Intervals of the new box:');
disp(inter);
HyProBox('delete', box_34);
HyProBox('delete', box);

disp('Linear Transformation');
box_35 = HyProBox('new_intervals', [3 5; 2 4]);
mat = [2 0; 0 4];
box = HyProBox('linearTransformation', box_35, mat);
inter = HyProBox('intervals', box);
disp('Intervals of the transformed box:');
disp(inter);
HyProBox('delete', box_35);
HyProBox('delete', box);

disp('Affine Transformation');
box_36 = HyProBox('new_intervals', [3 5; 2 4]);
mat = [2 0; 0 4];
vec = [2 1];
box = HyProBox('affineTransformation', box_36, mat, vec);
inter = HyProBox('intervals', box);
disp('Intervals of the transformed box:');
disp(inter);
HyProBox('delete', box_36);
HyProBox('delete', box);

disp('Minkowski Sum');
box_37 = HyProBox('new_intervals', [1 3; 1 3]);
box_38 = HyProBox('new_intervals', [4 6; 3 5]);
mSum = HyProBox('minkowskiSum', box_37, box_38);
inter = HyProBox('intervals', mSum);
disp('Intervals of the sum:');
disp(inter);
HyProBox('delete', box_37);
HyProBox('delete', box_38);
HyProBox('delete', mSum);

disp('Minkowski Decomposition');
box_39 = HyProBox('new_intervals', [1 3; 1 3]);
box_40 = HyProBox('new_intervals', [4 6; 3 5]);
mDec = HyProBox('minkowskiDecomposition', box_39, box_40);
inter = HyProBox('intervals', mDec);
disp('Intervals:');
disp(inter);
HyProBox('delete', box_39);
HyProBox('delete', box_40);
HyProBox('delete', mDec);

disp('Intersect');
box_41 = HyProBox('new_intervals', [1 3; 1 3]);
box_42 = HyProBox('new_intervals', [4 6; 3 5]);
intersected = HyProBox('minkowskiDecomposition', box_41, box_42);
inter = HyProBox('intervals', intersected);
disp('Intervals:');
disp(inter);
HyProBox('delete', box_41);
HyProBox('delete', box_42);
HyProBox('delete', intersected);

disp('Intersect Halfspace');
box_43 = HyProBox('new_intervals', [1 3; 1 3]);
nor = [1 0];
off = 2;
intersected = HyProBox('intersectHalfspace', box_43,nor,off);
inter = HyProBox('intervals', intersected);
disp('Intervals:');
disp(inter);
HyProBox('delete', box_43);
HyProBox('delete', intersected);

disp('Intersect Halfspaces');
box_44 = HyProBox('new_intervals', [1 3; 1 3]);
mat = [1 0; 0 1];
vec = [2 3];
intersected = HyProBox('intersectHalfspace', box_44,mat,vec);
inter = HyProBox('intervals', intersected);
disp('Intervals:');
disp(inter);
HyProBox('delete', box_44);
HyProBox('delete', intersected);

disp('Contains Point');
box_45 = HyProBox('new_intervals', [1 3; 2 5]);
point = [2; 3];
contains = HyProBox('contains_point', box_45, point);
disp('Box 45 contains point (2, 3):');
disp(contains);
HyProBox('delete', box_45);

disp('Contains Box');
box_46 = HyProBox('new_intervals', [1 5; 1 7]);
box_47 = HyProBox('new_intervals', [2 4; 2 3]);
contains = HyProBox('contains_box', box_46, box_47);
disp('Box 46 contains box 47:');
disp(contains);
HyProBox('delete', box_46);
HyProBox('delete', box_47);

disp('Unite Box');
box_48 = HyProBox('new_intervals', [1 5; 1 7]);
box_49 = HyProBox('new_intervals', [2 7; -1 9]);
uni = HyProBox('unite_box', box_48, box_49);
disp('Unite boxes 48 and 49:');
inter = HyProBox('intervals', uni);
disp('Intervals:');
disp(inter);
HyProBox('delete', box_48);
HyProBox('delete', box_49);
HyProBox('delete', uni);

% disp('Unite Boxes');
% box_50 = HyProBox('new_intervals', [1 5; 1 7]);
% box_51 = HyProBox('new_intervals', [2 7; -1 9]);
% box_52 = HyProBox('new_intervals', [0 1; 9 10]);
% uni = HyProBox('unite_boxes', box_50, boxes);
% disp('Unite boxes 50, 51, and 52:');
% inter = HyProBox('intervals', uni);
% disp('Intervals:');
% disp(inter);
% HyProBox('delete', box_50);
% HyProBox('delete', box_51);
% HyProBox('delete', box_52);
% HyProBox('delete', uni);

disp('* (Multiply)');
box_53 = HyProBox('new_intervals', [1 5; 1 7]);
box_54 = HyProBox('*', box_53, 3);
inter = HyProBox('intervals', box_54);
disp('Intervals:');
disp(inter);
HyProBox('delete', box_53);
HyProBox('delete', box_54);

disp('<<');
box_54 = HyProBox('new_intervals', [1 5; 1 7]);
HyProBox('<<', box_54);
HyProBox('delete', box_54);

disp('reduceNumberRepresentation');
box_55 = HyProBox('new_intervals', [1 5; 1 7; 1 2; 2 3]);
box_56 = HyProBox('reduceNumberRepresentation', box_55);
inter = HyProBox('intervals', box_56);
disp('Intervals:');
disp(inter);
HyProBox('delete', box_55);
HyProBox('delete', box_56);


disp('STOP');




res = 1;