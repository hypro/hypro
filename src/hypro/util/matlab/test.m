function res = test

%**************************************************************************
% Tests for HyPro Boxes
%**************************************************************************
inter = [1 2; 3 4; 5 6; 7 8; 9 10];
points = [0 0; 2 2];
insert_inter = [12 41];

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

% Test insert
box_3 = HyProBox('new_intervals',inter);
old_intervals = HyProBox('intervals',box_3);
disp('Old intervals:');
disp(old_intervals);
HyProBox('insert',box_3,insert_inter);
new_intervals = HyProBox('intervals',box_3);
disp('New intervals:');
disp(new_intervals);
HyProBox('delete', box_3);
%HyProBox('delete',new_box_3);


res = 1;