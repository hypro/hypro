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
    else
        settings{1}.timeStep = 0.1;
        settings{1}.clustering = 0;
        setRepr{1} = 2;
        aggr{1} = 1;
        settings{2}.timeStep = 0.01;
        settings{2}.clustering = -1;
        setRepr{2} = 2;
        aggr{2} = 2;

    end

end