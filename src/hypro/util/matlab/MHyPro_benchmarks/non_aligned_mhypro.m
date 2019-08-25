function [reachabilityTime, verificationTime, time, safe] = non_aligned_mhypro(saveFig, savePath, figName, bad, diff,settings,setRepr,aggr, plotting)

aggr = 0;
reachabilityTime = 0;
verificationTime = 0;
time = 0;
safe = 0;



% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%                 loc loc_1
%-----------------------------------------------%
loc = MHyProLocation();
loc.setName('loc');

% Set flow:
flowMatrix = [0 0 0 1; 0 0 0 1;0 0 0 1; 0 0 0 0];
loc.setFlow(flowMatrix);

% Set invariant 
inv = MHyProCondition([1 0 0; 0 1 0], [3;3]);
loc.setInvariant(inv);

%-----------------------------------------------%
%                 loc sink
%-----------------------------------------------%

loc_sink = MHyProLocation();
loc_sink.setName('sink');

% Set flow:
% x' = 0 v' = 0 t' = 0
flowMatrix = [0 0 0 1; 0 0 0 4; 0 0 0 1; 0 0 0 0];
loc_sink.setFlow(flowMatrix);

% Set invariant
inv = MHyProCondition([1 0 0;0 1 0], [7;7]);
loc_sink.setInvariant(inv);

l = automaton.addLocation(loc);
s = automaton.addLocation(loc_sink);

%-----------------------------------------------%
%                loc -> loc_sink
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard:
% t == 4
guard2 = MHyProCondition();
guard2.setMatrix([1 1 0;-1 -1 0]); 
guard2.setVector([3;-3]);

% Set reset
reset2 = MHyProReset();
reset2.setMatrix(eye(3));
reset2.setVector([0;0;0]);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(l);
tran2.setTarget(s);
tran2.setReset(reset2);
tran2.setLabels({MHyProLabel('t2')});

l.addTransition(tran2);


%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% Create initial set
% x = [10, 10.2] v = 0 t = 0 
boxVector = [0;0.001;0;0.001;0;0];
boxMatrix = [-1 0 0; 1 0 0; 0 -1 0; 0 1 0; 0 0 -1; 0 0 1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l, initialCond);


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = 4;
settings.jumpDepth = 2;
settings.timeStep = 0.1;

reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(setRepr);

flowpipes = reach.computeForwardReachability();


if plotting == 1
    dim = [2 1];
    labs = ["v", "x"];
    ext = 'png';
    reach.plot(flowpipes, dim, labs,saveFig,savePath,figName,ext);
    if bad
        if diff == 1
            x = [15;15;10.7;10.7];
            y = [15;-2;-2;15];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 2
            x = [15;15;10.6569;10.6569];
            y = [15;-2;-2;15];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 3
            x = [15;15;10.6138;10.6138];
            y = [15;-2;-2;15];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 4
            x = [12;-15;-15;12];
            y = [0;0;-5;-5];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        end
    end
elseif plotting == 2
    dim = [2 1 3];
    labs = ["v", "x", "t"];
    ext = 'png';
    reach.plot3D(flowpipes, dim, labs,saveFig,savePath,figName,ext);
    if diff == 0
        [x, y] = meshgrid(-15:0.5:15,10.7:0.1:15);
        reach.plotBadStates3D([0 -1 0], -10.7, [2 1], x,y);
    elseif diff == 1
        [x, y] = meshgrid(-15:0.5:15,10.6569:0.1:15);
        reach.plotBadStates3D([0 -1 0], -10.6569, [2 1], x,y);
    else
        [x, y] = meshgrid(-15:0.5:15,10.6138:0.1:15);
        reach.plotBadStates3D([0 -1 0], -10.6138, [2 1], x,y);
    end
    
end

end
