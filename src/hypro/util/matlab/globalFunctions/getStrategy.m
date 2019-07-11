function [settings, setRepr, aggr] = getStrategy(nr)

    settings = {};
    setRepr = {};
    aggr = {};
    if nr == 1
        settings{1}.timeStep = 0.01;
        settings{1}.clustering = -1;
        setRepr{1} = 0;
        aggr{1} = 0;
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