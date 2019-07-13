function [settings, setRepr, aggr] = getStrategy(nr)

    settings = {};
    setRepr = {};
    aggr = {};
    if nr == 1
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 2
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 3
        settings{1}.timeStep = 0.05;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 4
        settings{1}.timeStep = 0.00005;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 5
        settings{1}.timeStep = 0.02;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 6
        % ~ tacas18_1
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
        settings{2}.timeStep = 0.001;
        settings{2}.clustering = -1;
        setRepr{2} = 0;
        aggr{2} = 0;
        settings{3}.timeStep = 0.001;
        settings{3}.clustering = -1;
        setRepr{3} = 2;
        aggr{3} = 2;
    elseif nr == 7
        % ~ tacas18_2
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
        settings{2}.timeStep = 0.01;
        settings{2}.clustering = -1;
        setRepr{2} = 0;
        aggr{2} = 0;
        settings{3}.timeStep = 0.01;
        settings{3}.clustering = -1;
        setRepr{3} = 2;
        aggr{3} = 0;
    elseif nr == 8
        % ~ tacas18_3
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
        settings{2}.timeStep = 0.001;
        settings{2}.clustering = -1;
        setRepr{2} = 0;
        aggr{2} = 0;
        settings{3}.timeStep = 0.01;
        settings{3}.clustering = -1;
        setRepr{3} = 2;
        aggr{3} = 0;
    elseif nr == 9
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 1;
        settings{2}.timeStep = 0.1;
        settings{2}.clustering = 3;
        setRepr{2} = 0;
        aggr{2} = 1;
        settings{3}.timeStep = 0.1;
        settings{3}.clustering = -1;
        setRepr{3} = 2;
        aggr{3} = 2;
    elseif nr == 10
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 0;
        setRepr{1} = 2;
        aggr{1} = 2;
    elseif nr == 11
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 12
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 13
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 14
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 15
        settings{1}.timeStep = 0.001;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 16
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = -1;
        setRepr{1} = 2;
        aggr{1} = 0;
    elseif nr == 17
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 18
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 19
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = -1;
        setRepr{1} = 2;
        aggr{1} = 2;
    elseif nr == 20
        settings{1}.timeStep = 0.05;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 21
        settings{1}.timeStep = 0.09;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 22
        settings{1}.timeStep = 0.07;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 23
        settings{1}.timeStep = 0.04;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 24
        settings{1}.timeStep = 0.02;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 25
        settings{1}.timeStep = 0.02;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 26
        settings{1}.timeStep = 0.02;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 27
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = -1;
        setRepr{1} = 2;
        aggr{1} = 0;
    elseif nr == 28
        settings{1}.timeStep = 0.05;
        settings{1}.clustering = -1;
        setRepr{1} = 2;
        aggr{1} = 0;
    elseif nr == 29
        settings{1}.timeStep = 0.5;
        settings{1}.clustering = 3;
        setRepr{1} = 2;
        aggr{1} = 2;
    elseif nr == 30
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 0;
    elseif nr == 31
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 0;
    elseif nr == 32
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 33
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 0;
    elseif nr == 34
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 0;
    elseif nr == 35
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 36
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 37
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 0;
    elseif nr == 38
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 39
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 40
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 0;
    elseif nr == 41
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 42
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 43
        settings{1}.timeStep = 0.001;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 0;
    elseif nr == 45
        settings{1}.timeStep = 0.001;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 46
        settings{1}.timeStep = 0.001;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 47
        settings{1}.timeStep = 0.001;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 0;
    elseif nr == 48
        settings{1}.timeStep = 0.001;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 49
        settings{1}.timeStep = 0.001;
        settings{1}.clustering = 0;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 50
        settings{1}.timeStep = 0.001;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 0;
    elseif nr == 51
        settings{1}.timeStep = 0.001;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 1;
    elseif nr == 52
        settings{1}.timeStep = 0.001;
        settings{1}.clustering = 3;
        setRepr{1} = 0;
        aggr{1} = 2;
    elseif nr == 53
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 3;
        setRepr{1} = 2;
        aggr{1} = 0;
    elseif nr == 54
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 3;
        setRepr{1} = 2;
        aggr{1} = 0;
    elseif nr == 55
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 3;
        setRepr{1} = 2;
        aggr{1} = 1;
    elseif nr == 56
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = -1;
        setRepr{1} = 2;
        aggr{1} = 1;
    elseif nr == 57
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = -1;
        setRepr{1} = 2;
        aggr{1} = 2;
    elseif nr == 58
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = 3;
        setRepr{1} = 2;
        aggr{1} = 0;
    elseif nr == 59
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = 3;
        setRepr{1} = 2;
        aggr{1} = 1;
    elseif nr == 60
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = 3;
        setRepr{1} = 2;
        aggr{1} = 2;
    end

end