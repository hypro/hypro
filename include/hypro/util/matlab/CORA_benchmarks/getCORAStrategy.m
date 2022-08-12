function [timeStep, tTerms, zOrder, pOrder] = getCORAStrategy(nr)

% initial strategies:
% bb: 8
% fo4: 34
% fo8: 34
% fo16: 36
% sr: 8
% sw: 33
% rr: 8
% tt: 35
% vp: 7


    pOrder = 10;
    if nr == 1
        timeStep = 0.1;
        tTerms = 100;
        zOrder = 200;
    elseif nr == 2
        timeStep = 0.01;
        tTerms = 100;
        zOrder = 200;
    elseif nr == 3
        timeStep = 0.001;
        tTerms = 100;
        zOrder = 200;
    elseif nr == 4
        timeStep = 0.001;
        tTerms = 50;
        zOrder = 100;
    elseif nr == 5
        timeStep = 0.1;
        tTerms = 50;
        zOrder = 100;
    elseif nr == 6
        timeStep = 0.1;
        tTerms = 10;
        zOrder = 20;
    elseif nr == 7
        timeStep = 0.02;
        tTerms = 1;
        zOrder = 5;
    elseif nr == 8
        timeStep = 0.01;
        tTerms = 1;
        zOrder = 1;
    elseif nr == 9
        timeStep = 0.005;
        tTerms = 100;
        zOrder = 200;
    elseif nr == 10
        timeStep = 0.01;
        tTerms = 10;
        zOrder = 20;
    elseif nr == 11
        timeStep = 0.5;
        tTerms = 10;
        zOrder = 20;
    elseif nr == 12
        timeStep = 0.01;
        tTerms = 25;
        zOrder = 50;
    elseif nr == 13
        timeStep = 0.1;
        tTerms = 25;
        zOrder = 50;
    elseif nr == 14
        timeStep = 0.01;
        tTerms = 1;
        zOrder = 200;
    elseif nr == 15
        timeStep = 0.01;
        tTerms = 100;
        zOrder = 1;
    elseif nr == 16
        timeStep = 0.02;
        tTerms = 100;
        zOrder = 200;
    elseif nr == 17
        timeStep = 0.2;
        tTerms = 100;
        zOrder = 200;
    elseif nr == 18
        timeStep = 0.01;
        tTerms = 10;
        zOrder = 40;
    elseif nr == 19
        timeStep = 0.01;
        tTerms = 40;
        zOrder = 10;
    elseif nr == 20
        timeStep = 0.0002;
        tTerms = 100;
        zOrder = 200;
    elseif nr == 21
        timeStep = 0.0002;
        tTerms = 5;
        zOrder = 200;
    elseif nr == 22
        timeStep = 0.00005;
        tTerms = 100;
        zOrder = 200;
    elseif nr == 23
        timeStep = 0.5;
        tTerms = 10;
        zOrder = 400;
    elseif nr == 24
        timeStep = 0.001;
        tTerms = 5;
        zOrder = 400;
    elseif nr == 25
        timeStep = 0.1;
        tTerms = 5;
        zOrder = 400;
    elseif nr == 26
        timeStep = 0.01;
        tTerms = 5;
        zOrder = 400;
    elseif nr == 27
        timeStep = 0.02;
        tTerms = 100;
        zOrder = 200;
    elseif nr == 28
        timeStep = 0.02;
        tTerms = 200;
        zOrder = 300;
    elseif nr == 29
        timeStep = 0.01;
        tTerms = 200;
        zOrder = 300;
    elseif nr == 30
        timeStep = 0.001;
        tTerms = 200;
        zOrder = 300;
    elseif nr == 31
        timeStep = 0.1;
        tTerms = 200;
        zOrder = 300;
    elseif nr == 32
        timeStep = 0.05;
        tTerms = 100;
        zOrder = 200;
    elseif nr == 33
        timeStep = 0.001;
        tTerms = 1;
        zOrder = 4;
    elseif nr == 34
        timeStep = 0.05;
        tTerms = 2;
        zOrder = 2;
    elseif nr == 35
        timeStep = 0.01;
        tTerms = 1;
        zOrder = 2;
    elseif nr == 36
        timeStep = 0.05;
        tTerms = 100;
        zOrder = 200;
    end
end