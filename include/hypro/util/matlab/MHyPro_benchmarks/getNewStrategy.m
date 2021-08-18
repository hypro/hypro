function [settings, setRepr, aggr] = getNewStrategy(nr)

% initial staretegies
% bb: 3
% fo: 9
% sr: 3
% sw: 24 
% rr: 3
% tt: 3
% vp: 33

settings = {};
setRepr = {};
aggr = {};

if nr == 1
    settings.timeStep = 0.01;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 0;
elseif nr == 2
    settings.timeStep = 0.01;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 0;
elseif nr == 3
    settings.timeStep = 0.01;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 4
    settings.timeStep = 0.1;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 0;
elseif nr == 5
    settings.timeStep = 0.1;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 0;
elseif nr == 6
    settings.timeStep = 0.1;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 7
    settings.timeStep = 0.05;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 0;
elseif nr == 8
    settings.timeStep = 0.05;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 0;
elseif nr == 9
    settings.timeStep = 0.05;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 10
    settings.timeStep = 0.02;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 0;
elseif nr == 11
    settings.timeStep = 0.02;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 0;
elseif nr == 12
    settings.timeStep = 0.02;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 13
    settings.timeStep = 0.00005;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 0;
elseif nr == 14
    settings.timeStep = 0.00005;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 0;
elseif nr == 15
    settings.timeStep = 0.00005;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 16
    settings.timeStep = 0.001;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 0;
elseif nr == 17
    settings.timeStep = 0.001;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 0;
elseif nr == 18
    settings.timeStep = 0.001;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 19
    settings.timeStep = 0.005;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 0;
elseif nr == 20
    settings.timeStep = 0.005;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 0;
elseif nr == 21
    settings.timeStep = 0.005;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 22
    settings.timeStep = 0.01;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 0;
elseif nr == 23
    settings.timeStep = 0.01;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 0;
elseif nr == 24
    settings.timeStep = 0.01;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 25
    settings.timeStep = 0.1;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 0;
elseif nr == 26
    settings.timeStep = 0.1;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 0;
elseif nr == 27
    settings.timeStep = 0.1;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 28
    settings.timeStep = 0.05;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 0;
elseif nr == 29
    settings.timeStep = 0.05;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 0;
elseif nr == 30
    settings.timeStep = 0.05;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 31
    settings.timeStep = 0.02;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 0;
elseif nr == 32
    settings.timeStep = 0.02;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 0;
elseif nr == 33
    settings.timeStep = 0.02;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 34
    settings.timeStep = 0.00005;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 0;
elseif nr == 35
    settings.timeStep = 0.00005;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 0;
elseif nr == 36
    settings.timeStep = 0.00005;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 37
    settings.timeStep = 0.001;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 0;
elseif nr == 38
    settings.timeStep = 0.001;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 0;
elseif nr == 39
    settings.timeStep = 0.001;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 40
    settings.timeStep = 0.005;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 0;
elseif nr == 41
    settings.timeStep = 0.005;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 0;
elseif nr == 42
    settings.timeStep = 0.005;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
end
end