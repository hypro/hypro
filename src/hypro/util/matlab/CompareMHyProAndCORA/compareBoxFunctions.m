function compareBoxFunctions()

% This file compares the performance of the box functions for mhypro and
% cora.

mh_box1 = MHyProBox('intervals', [0 1; 1 12; -1 10; -10 5; 20 34]);
cora_box1 = interval([0;1;-1;-10;20], [1;12;10;5;34]);

mh_box2 = MHyProBox('intervals', [-10 1; 7 12; -5 11; -6 3; 0 3]);
cora_box2 = interval([-10,7,-5,-6,0], [1,12,11,3,3]);

disp(' ');
disp('---------------------------------------');
disp('vertices');
disp('---------------------------------------');



tic;
mh_vert = mh_box1.vertices();
stop = toc;
disp(['MHyPro needed ' , num2str(stop), 's']);

tic;
c_vert = vertices(cora_box1);
stop = toc;
disp(['CORA needed ' , num2str(stop), 's']);

disp(' ');
disp('---------------------------------------');
disp('Minkowski sum');
disp('---------------------------------------');

tic;
res = mh_box1 + mh_box2;
stop = toc;
disp(['MHyPro needed ' , num2str(stop), 's']);

tic;
c_res = cora_box1 + cora_box2;
stop = toc;
disp(['CORA needed ' , num2str(stop), 's']);

disp(' ');
disp('---------------------------------------');
disp('Affine transformation');
disp('---------------------------------------');

A = [10 14 7 -9 14;...
    14 7 -6 -8 -10;...
     7 9 8 11 1;...
   -10 9 -10 8 -1;...
    12 0 -3 -2 9];
b = [1;2;3;4;5];

tic;
res = mh_box1.affineTransformation(A,b);
stop = toc;
disp(['MHyPro needed ' , num2str(stop), 's']);

tic;
c_res = cora_box1 * A + b;
stop = toc;
disp(['CORA needed ' , num2str(stop), 's']);

disp(' ');
disp('---------------------------------------');
disp('union');
disp('---------------------------------------');

tic;
res = mh_box1.unite(mh_box2);
stop = toc;

res.vertices()
disp(['MHyPro needed ' , num2str(stop), 's']);

tic;
res = hull(cora_box1, cora_box2);
stop = toc;
disp(['CORA needed ' , num2str(stop), 's']);

disp(' ');
disp('---------------------------------------');
disp('intersection');
disp('---------------------------------------');

tic;
res = mh_box1.intersect(mh_box2);
stop = toc;
res.vertices()
disp(['MHyPro needed ' , num2str(stop), 's']);

tic;
c_res = cora_box1 & cora_box2;
stop = toc;
disp(['CORA needed ' , num2str(stop), 's']);

disp(' ');
disp('---------------------------------------');
disp('supremum');
disp('---------------------------------------');

tic;
res = mh_box1.supremum();
stop = toc;
disp(['MHyPro needed ' , num2str(stop), 's']);

tic;
c_res = supremum(cora_box1);
stop = toc;
disp(['CORA needed ' , num2str(stop), 's']);

disp(' ');
disp('---------------------------------------');
disp('enlarge/secale');
disp('---------------------------------------');

tic;
res = mh_box1 * 10;
stop = toc;
disp(['MHyPro needed ' , num2str(stop), 's']);

tic;
c_rex = cora_box1 * 10;
stop = toc;
disp(['CORA needed ' , num2str(stop), 's']);

end