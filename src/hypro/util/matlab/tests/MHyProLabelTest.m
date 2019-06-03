function tests = MHyProLabelTest
    tests = functiontests(localfunctions);
end

function testLabel(testCase)
% Test Basic Functionality
lab1 = MHyProLabel('lab1');
lab2 = MHyProLabel(lab1);

% Get label names
name1 = lab1.getName();
name2 = lab2.getName();
assert(isequal(name1,'lab1'));
assert(isequal(name2,'lab1'));

% Change name of the second label
lab2.setName('lab2');
name2 = lab2.getName();
assert(isequal(name2, 'lab2'));

% Check if lab1 and lab2 are equal
equal = (lab1 == lab2);
assert(equal == 0);
lab3 = MHyProLabel(lab2);
equal = (lab2 == lab3);
assert(equal == 1);

% Check unequals
nequal = (lab1 ~= lab2);
assert(nequal == 1);
nequal = (lab2 ~= lab3);
assert(nequal == 0);

% Check less
less = (lab1 < lab2);
assert(less == 1);
less = (lab2 < lab1);
assert(less == 0);
end
