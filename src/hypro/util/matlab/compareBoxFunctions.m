function compareBoxFunctions()


disp(' ');
disp('---------------------------------------');
disp('vertices');
disp('---------------------------------------');

mh_box1 = MHyProBox('points', [-2 2; 2 4; -4 -2]);
cora_box1 = interval([-2;2;-4], [2;4;-2]);

tic;
mh_vert = mh_box1.vertices();
stop = toc;
disp(['MHyPro needed ' , num2str(stop), 's']);

tic;
c_vert = cora_box1.vertices;
stop = toc;
disp(['CORA needed ' , num2str(stop), 's']);

disp(' ');
disp('---------------------------------------');
disp('Minkowski sum');
disp('---------------------------------------');

mh_box2 = MHyProBox('points', [7 20; -12 0; -4 -2]);
cora_box2 = interval([7;-12;-4], [20;0;-2]);

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

A = [1 0 0; 0 cos(45) -sin(45); 0 sin(45) cos(45)];
b = [1;2;3];

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

end