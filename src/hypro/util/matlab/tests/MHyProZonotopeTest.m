function tests = MHyProZonotopeTest
    tests = functiontests(localfunctions);
end

function testZonotopes(testCase)

disp('z1');
z1 = MHyProZonotope();
disp('z2');
z2 = MHyProZonotope('dimension', 13);
disp('z3');
z3 = MHyProZonotope([1 1 0], [1 0 0; 0 1 0; 0 0 1]);
disp('z4');
z4 = MHyProZonotope(z3, 0, 2);
disp('z5');
z5 = MHyProZonotope(z2);


ans = z1.isempty();
assert(ans == 1);

ans = z2.isempty();
assert(ans == 0);

s = z1.supremum();
assert(isnan(s) == 1);

s = z3.supremum();
assert(s == 4);


z3 = MHyProZonotope([1;1;0], [1 0 0; 0 1 0; 0 0 1]);

z_center = z3.center();
z_gen = z3.generators();
assert(isequal(z_center,[1;1;0]));
assert(isequal(z_gen,eye(3)));

ord = z2.order();
assert(ord >= 0.0769);

z2.setCenter([1 0 0 2 0 0 2 1 0 0 1 1 2]);
c = z2.center();
assert(isequal([1;0;0;2;0;0;2;1;0;0;1;1;2],c));

disp('Get generators');
z2.setGenerators(eye(13));
g = z2.generators();
assert(isequal(g,eye(13)));

disp('Add generators');
g = z4.generators();
z4.addGenerators([1 2 3; 3 4 5]);
g = z4.generators();

c = z3.center();

bound = z5.computeZonotopeBoundary();
assert(isequal(bound,[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]));

%Plot
z6 = MHyProZonotope([1;2;1], eye(3));
z6.plotObj([1 3]);

end