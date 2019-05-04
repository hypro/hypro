function runTests

disp("[=============================================]");
disp("[                  RUN TESTS                  ]");
disp("[=============================================]");
disp(" ");

if testMHyProBox()
    disp("Boxes:..................................SUCCEED");
else
    disp("Boxes:..................................FAILED");
end

if testMHyProConstraintSet()
    disp("ConstraintSet:..........................SUCCEED");
else
    disp("ConstraintSet:..........................FAILED");
end

if testMHyProEllipsoid()
    disp("Elliposid:..............................SUCCEED");
else
    disp("Ellipsoid:..............................FAILED");
end

if testMHyProSupportFunction()
    disp("SupportFunction:........................SUCCEED");
else
    disp("SupportFunction:........................FAILED");
end

if testMHyProLabel()
    disp("Label:..................................SUCCEED");
else
    disp("Label:..................................FAILED");
end

if testMHyProFlow()
    disp("Flow:...................................SUCCEED");
else
    disp("Flow:...................................FAILED");
end

if testMHyProTransition()
    disp("Transition:.............................SUCCEED");
else
    disp("Transition:.............................FAILED");
end

if testMHyProReset()
    disp("Reset:..................................SUCCEED");
else
    disp("Reset:..................................FAILED");
end

if testMHyProLocation()
    disp("Location:...............................SUCCEED");
else
    disp("Location:...............................FAILED");
end

if testMHyProCondition()
    disp("Condition:..............................SUCCEED");
else
    disp("Condition:..............................FAILED");
end

if testMHyProHAutomaton()
    disp("HAutomaton:.............................SUCCEED");
else
    disp("HAutomaton:.............................FAILED");
end

if testMHyProReach()
    disp("Reach:.............................SUCCEED");
else
    disp("Reach:.............................FAILED");
end

