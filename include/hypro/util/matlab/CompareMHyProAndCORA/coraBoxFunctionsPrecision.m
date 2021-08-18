function coraBoxFunctionsPrecision

disp('');
disp('---------------------------');
disp('bspline0');
disp('---------------------------');

u = interval(0,1);
tic;
res = 1/6 * (1 - u)^3;
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

low = -(infimum(res) - 0)/(1/6 - 0)* 100;
up = (supremum(res) - 1/6)/(1/6 - 0)* 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);

disp('');
disp('---------------------------');
disp('bspline1');
disp('---------------------------');

tic;
res = 1/6 * (3*u^3 - 6 * u^2 + 4);
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

rl = 1/6;
ru = 2/3;
low = -(infimum(res) - rl)/(ru - rl)* 100;
up = (supremum(res) - ru)/(ru - rl)* 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);

disp('');
disp('---------------------------');
disp('bspline2');
disp('---------------------------');

tic;
res = 1/6 * (-3 * u^3 + 3 * u^2 + 3 * u + 1);
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

rl = 1/6;
ru = 2/3;
low = -(infimum(res) - rl)/(ru - rl)* 100;
up = (supremum(res) - ru)/(ru - rl)* 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);

disp('');
disp('---------------------------');
disp('bspline3');
disp('---------------------------');

tic;
res = 1/6 * (-1 * u^3);
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

rl = -1/6;
ru = 0;
low = -(infimum(res) - rl)/(ru - rl)* 100;
up = (supremum(res) - ru)/(ru - rl)* 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);

disp('');
disp('---------------------------');
disp('savitzky-golay filter');
disp('---------------------------');

x1 = interval(-2,2);

tic;
res = 7 * x1^3 - 984 * x1^3 - 76 * (x1^2) * x1 + 92 * x1 * x1^2 + 7 * x1^2 -39 * x1 * x1 - 46 * x1^2 + 7* x1 - 46 * x1 - 75;
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

rl = -9.453;
ru = 9.303;
low = -(infimum(res) - rl)/(ru - rl)* 100;
up = (supremum(res) - ru)/(ru - rl)* 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);

disp('');
disp('---------------------------');
disp('image rejection unit');
disp('---------------------------');

x2 = interval(0,1);

tic;
res = 16384 * (x2^4 + x2^4) + 64767 * (x2^2 - x2^2) + x2 - x2 + 57344 * x2 * x2 * (x2 -x2);
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

rl = -5.51e4;
ru = 8.79e4;
low = -(infimum(res) - rl)/(ru - rl)* 100;
up = (supremum(res) - ru)/(ru - rl)* 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);

disp('');
disp('---------------------------');
disp('random function');
disp('---------------------------');

x3 = interval(-2,2);

tic;
res = (x3 - 1) * (x3 + 2) * (x3 + 1) * (x3 - 2) * x3^2;
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

rl = -36;
ru = 64;
low = -(infimum(res) - rl)/(ru - rl)* 100;
up = (supremum(res) - ru)/(ru - rl)* 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);


disp('');
disp('---------------------------');
disp('Mitchell function');
disp('---------------------------');

x4 = interval(-2,2);

tic;
res = 4 * (x4^4 + (x4^2 + x4^4)^2) + 17 * x4^2 * (x4^2 + x4^2) - 20 * (x4^2 + x4^2 + x4^2) +17;
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

rl = -8;
ru = 641;
low = -(infimum(res) - rl)/(ru - rl) * 100;
up = (supremum(res) - ru)/(ru - rl) * 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);

disp('');
disp('---------------------------');
disp('matyas function');
disp('---------------------------');

x5 = interval(-100,100);

tic;
res = 0.26 * (x5^2 + x5^2) - 0.48 * x5 * x5;
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

rl = 0;
ru = 10000;
low = -(infimum(res) - rl)/(ru - rl)* 100;
up = (supremum(res) - ru)/(ru - rl)* 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);


disp('');
disp('---------------------------');
disp('three hump function');
disp('---------------------------');

x6 = interval(-10,10);

tic;
res = 12 * x6^2 - 6.3 * x6^4 - x6^6 + 6 * x6 * (x6 -x6);
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

rl = 0;
ru = 0.94e6;
low = -(infimum(res) - rl)/(ru - rl)* 100;
up = (supremum(res) - ru)/(ru - rl)* 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);

disp('');
disp('---------------------------');
disp('ratscheck function');
disp('---------------------------');

x7 = interval(-100, 100);

tic;
res = 4 * x7^2 - 2.1 * x7^4 + (1/3) * x7^6 + x7 * x7 - 4 * x7^2 + 4 * x7^4;
stop = toc;
disp(['Result: [', num2str(infimum(res)), ', ',num2str(supremum(res)), ']']);

rl = -1.03;
ru = 0.33e12;
low = -(infimum(res) - rl)/(ru - rl)* 100;
up = (supremum(res) - ru)/(ru - rl)* 100;
disp(['Error: [', num2str(low), ', ',num2str(up), ']']);
disp(['Time needed: ' , num2str(stop)]);









end