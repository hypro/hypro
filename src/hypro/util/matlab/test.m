function res = test

inter = [1 2; 3 4; 5 6];
box = HyProBox('new',inter);
box_inter = HyProBox('intervals',box);
disp('Box intervals:');
disp(box_inter);
HyProBox('delete',box)
res = 1;