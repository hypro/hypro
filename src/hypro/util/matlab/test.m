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

% disp('Empty'); 
% box_8 = HyProBox('new_intervals',inter);
% old_intervals = HyProBox('intervals',box_8);
% disp('Old intervals:');
% disp(old_intervals);
% HyProBox('empty',box_8, 2);
% new_intervals = HyProBox('intervals',box_8);
% disp('New intervals:');
% disp(new_intervals);
% HyProBox('delete', box_8);

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

disp('Evaluate');
%box_21

disp('MutliEvaluate');
%box_22

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

% disp('Make Symmetric');
% box_30 = HyProBox('new_intervals',[1 2; 1 4]);
% old_intervals = HyProBox('intervals',box_30);
% disp('Old intervals:');
% disp(old_intervals);
% HyProBox('makeSymmetric',box_30);
% new_intervals = HyProBox('intervals',box_30);
% disp('New intervals:');
% disp(new_intervals);
% HyProBox('delete', box_30);

disp('Constraints');
box_31 = HyProBox('new_intervals', inter);
const = HyProBox('constraints', box_31);
disp('Box 31 constrains:');
disp('normal:');
disp(const.normal);
disp('offset:');
disp(const.offset);
HyProBox('delete', box_31);




res = 1;