function [settings, setRepr, aggr] = getNewStrategy(nr)

% 0 = box, 1 = carl_polytope, 2 = constraint_set
% 3 = polytope_h, 4 = polytope_v
% 5 = ppl_polytope, 6 = support_function, 7 = taylor_model
% 8 = zonotope, 9 = difference_bounds,

settings = {};
setRepr = {};
aggr = {};
if nr == 1
    settings.timeStep = 0.01;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 1;
elseif nr == 2
    settings.timeStep = 0.01;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 1;
elseif nr == 3
    settings.timeStep = 0.01;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 4
    settings.timeStep = 0.01;
    settings.clustering = -1;
    setRepr = 0;
    aggr = 0;
elseif nr == 5
    settings.timeStep = 0.1;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 1;
elseif nr == 6
    settings.timeStep = 0.1;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 1;
elseif nr == 7
    settings.timeStep = 0.1;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 8
    settings.timeStep = 0.1;
    settings.clustering = -1;
    setRepr = 0;
    aggr = 0;
elseif nr == 9
    settings.timeStep = 0.05;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 1;
elseif nr == 10
    settings.timeStep = 0.05;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 1;
elseif nr == 11
    settings.timeStep = 0.05;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 12
    settings.timeStep = 0.05;
    settings.clustering = -1;
    setRepr = 0;
    aggr = 0;
elseif nr == 13
    settings.timeStep = 0.02;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 1;
elseif nr == 14
    settings.timeStep = 0.02;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 1;
elseif nr == 15
    settings.timeStep = 0.02;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 16
    settings.timeStep = 0.02;
    settings.clustering = -1;
    setRepr = 0;
    aggr = 0;
elseif nr == 17
    settings.timeStep = 0.00005;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 1;
elseif nr == 18
    settings.timeStep = 0.00005;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 1;
elseif nr == 19
    settings.timeStep = 0.00005;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 20
    settings.timeStep = 0.00005;
    settings.clustering = -1;
    setRepr = 0;
    aggr = 0;
elseif nr == 21
    settings.timeStep = 0.001;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 1;
elseif nr == 21
    settings.timeStep = 0.001;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 1;
elseif nr == 22
    settings.timeStep = 0.001;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 23
    settings.timeStep = 0.001;
    settings.clustering = -1;
    setRepr = 0;
    aggr = 0;
elseif nr == 24
    settings.timeStep = 0.005;
    settings.clustering = 5;
    setRepr = 0;
    aggr = 1;
elseif nr == 25
    settings.timeStep = 0.005;
    settings.clustering = 3;
    setRepr = 0;
    aggr = 1;
elseif nr == 26
    settings.timeStep = 0.005;
    settings.clustering = 0;
    setRepr = 0;
    aggr = 1;
elseif nr == 27
    settings.timeStep = 0.005;
    settings.clustering = -1;
    setRepr = 0;
    aggr = 0;
elseif nr == 28
    settings.timeStep = 0.01;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 2;
elseif nr == 29
    settings.timeStep = 0.01;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 2;
elseif nr == 30
    settings.timeStep = 0.01;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 31
    settings.timeStep = 0.01;
    settings.clustering = -1;
    setRepr = 6;
    aggr = 0;
elseif nr == 32
    settings.timeStep = 0.1;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 2;
elseif nr == 33
    settings.timeStep = 0.1;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 2;
elseif nr == 34
    settings.timeStep = 0.1;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 35
    settings.timeStep = 0.1;
    settings.clustering = -1;
    setRepr = 6;
    aggr = 0;
elseif nr == 36
    settings.timeStep = 0.05;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 2;
elseif nr == 37
    settings.timeStep = 0.05;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 2;
elseif nr == 38
    settings.timeStep = 0.05;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 39
    settings.timeStep = 0.05;
    settings.clustering = -1;
    setRepr = 6;
    aggr = 0;
elseif nr == 40
    settings.timeStep = 0.02;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 2;
elseif nr == 41
    settings.timeStep = 0.02;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 2;
elseif nr == 42
    settings.timeStep = 0.02;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 43
    settings.timeStep = 0.02;
    settings.clustering = -1;
    setRepr = 6;
    aggr = 0;
elseif nr == 44
    settings.timeStep = 0.00005;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 2;
elseif nr == 45
    settings.timeStep = 0.00005;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 2;
elseif nr == 46
    settings.timeStep = 0.00005;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 47
    settings.timeStep = 0.00005;
    settings.clustering = -1;
    setRepr = 6;
    aggr = 0;
elseif nr == 48
    settings.timeStep = 0.001;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 2;
elseif nr == 49
    settings.timeStep = 0.001;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 2;
elseif nr == 50
    settings.timeStep = 0.001;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 51
    settings.timeStep = 0.001;
    settings.clustering = -1;
    setRepr = 6;
    aggr = 0;
elseif nr == 52
    settings.timeStep = 0.005;
    settings.clustering = 5;
    setRepr = 6;
    aggr = 2;
elseif nr == 53
    settings.timeStep = 0.005;
    settings.clustering = 3;
    setRepr = 6;
    aggr = 2;
elseif nr == 54
    settings.timeStep = 0.005;
    settings.clustering = 0;
    setRepr = 6;
    aggr = 2;
elseif nr == 55
    settings.timeStep = 0.005;
    settings.clustering = -1;
    setRepr = 6;
    aggr = 0;    
elseif nr == 56
    settings.timeStep = 0.01;
    settings.clustering = 5;
    setRepr = 8;
    aggr = 2;
elseif nr == 57
    settings.timeStep = 0.01;
    settings.clustering = 3;
    setRepr = 8;
    aggr = 2;
elseif nr == 58
    settings.timeStep = 0.01;
    settings.clustering = 0;
    setRepr = 8;
    aggr = 2;
elseif nr == 59
    settings.timeStep = 0.01;
    settings.clustering = -1;
    setRepr = 8;
    aggr = 0;
elseif nr == 60
    settings.timeStep = 0.1;
    settings.clustering = 5;
    setRepr = 8;
    aggr = 2;
elseif nr == 61
    settings.timeStep = 0.1;
    settings.clustering = 3;
    setRepr = 8;
    aggr = 2;
elseif nr == 62
    settings.timeStep = 0.1;
    settings.clustering = 0;
    setRepr = 8;
    aggr = 2;
elseif nr == 63
    settings.timeStep = 0.1;
    settings.clustering = -1;
    setRepr = 8;
    aggr = 0;
elseif nr == 64
    settings.timeStep = 0.05;
    settings.clustering = 5;
    setRepr = 8;
    aggr = 2;
elseif nr == 65
    settings.timeStep = 0.05;
    settings.clustering = 3;
    setRepr = 8;
    aggr = 2;
elseif nr == 66
    settings.timeStep = 0.05;
    settings.clustering = 0;
    setRepr = 8;
    aggr = 2;
elseif nr == 67
    settings.timeStep = 0.05;
    settings.clustering = -1;
    setRepr = 8;
    aggr = 0;
elseif nr == 68
    settings.timeStep = 0.02;
    settings.clustering = 5;
    setRepr = 8;
    aggr = 2;
elseif nr == 69
    settings.timeStep = 0.02;
    settings.clustering = 3;
    setRepr = 8;
    aggr = 2;
elseif nr == 70
    settings.timeStep = 0.02;
    settings.clustering = 0;
    setRepr = 8;
    aggr = 2;
elseif nr == 71
    settings.timeStep = 0.02;
    settings.clustering = -1;
    setRepr = 8;
    aggr = 0;
elseif nr == 72
    settings.timeStep = 0.00005;
    settings.clustering = 5;
    setRepr = 8;
    aggr = 2;
elseif nr == 73
    settings.timeStep = 0.00005;
    settings.clustering = 3;
    setRepr = 8;
    aggr = 2;
elseif nr == 74
    settings.timeStep = 0.00005;
    settings.clustering = 0;
    setRepr = 8;
    aggr = 2;
elseif nr == 75
    settings.timeStep = 0.00005;
    settings.clustering = -1;
    setRepr = 8;
    aggr = 0;
elseif nr == 76
    settings.timeStep = 0.001;
    settings.clustering = 5;
    setRepr = 8;
    aggr = 2;
elseif nr == 77
    settings.timeStep = 0.001;
    settings.clustering = 3;
    setRepr = 8;
    aggr = 2;
elseif nr == 78
    settings.timeStep = 0.001;
    settings.clustering = 0;
    setRepr = 8;
    aggr = 2;
elseif nr == 79
    settings.timeStep = 0.001;
    settings.clustering = -1;
    setRepr = 8;
    aggr = 0;
elseif nr == 80
    settings.timeStep = 0.005;
    settings.clustering = 5;
    setRepr = 8;
    aggr = 2;
elseif nr == 81
    settings.timeStep = 0.005;
    settings.clustering = 3;
    setRepr = 8;
    aggr = 2;
elseif nr == 82
    settings.timeStep = 0.005;
    settings.clustering = 0;
    setRepr = 8;
    aggr = 2;
elseif nr == 83
    settings.timeStep = 0.005;
    settings.clustering = -1;
    setRepr = 8;
    aggr = 0;    
elseif nr == 84
    settings.timeStep = 0.01;
    settings.clustering = 5;
    setRepr = 4; %v_polytope
    aggr = 2;
elseif nr == 85
    settings.timeStep = 0.01;
    settings.clustering = 5;
    setRepr = 3; %h_polytope
    aggr = 2;
elseif nr == 86
    settings.timeStep = 0.01;
    settings.clustering = 5;
    setRepr = 9; %difference bounds
    aggr = 2;    
elseif nr == 87
    settings.timeStep = 0.01;
    settings.clustering = 5;
    setRepr = 7; %taylor model
    aggr = 2;        
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
end