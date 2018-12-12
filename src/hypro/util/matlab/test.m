function res = test

%**************************************************************************
% Tests for HyPro Boxes
%**************************************************************************
inter = [1 2; 3 4; 5 6; 7 8; 9 10];
points = [0 0; 2 2];
insert_inter = [12 41];
mat = [1 0 0; 0 1 0; 0 0 1];
vec = [1; 2; 3];

% Construct empty box
box_0 = HyProBox('new_empty');
intervals_box_0 = HyProBox('intervals',box_0);
disp('Box 0 intervals:');
disp(intervals_box_0);
HyProBox('delete',box_0);

% Construct box from list of intervals
box_1 = HyProBox('new_intervals',inter);
intervals_box_1 = HyProBox('intervals',box_1);
disp('Box 1 intervals:');
disp(intervals_box_1);
HyProBox('delete',box_1);

% Construct box from a pair of points
box_2 = HyProBox('new_points',points);
box_2_inter = HyProBox('intervals',box_2);
disp('Box 2 intervals:');
disp(box_2_inter);
HyProBox('delete',box_2);

% Copy a box
box_3 = HyProBox('new_intervals',inter);
box_4 = HyProBox('copy', box_3);
box_4_inter = HyProBox('intervals',box_4);
disp('Box 4 intervals:');
disp(box_4_inter);
HyProBox('delete', box_3);
HyProBox('delete', box_4);

% Construct box from matrix and vector
box_5 = HyProBox('new_matrix',mat,vec);
box_5_inter = HyProBox('intervals',box_5);
disp('Box 5 intervals:');
disp(box_5_inter);
HyProBox('delete', box_5);

% Test insert
box_6 = HyProBox('new_intervals',inter);
old_intervals = HyProBox('intervals',box_6);
disp('Old intervals:');
disp(old_intervals);
HyProBox('insert',box_6,insert_inter);
new_intervals = HyProBox('intervals',box_6);
disp('New intervals:');
disp(new_intervals);
HyProBox('delete', box_6);


res = 1;