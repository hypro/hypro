function [reachabilityTime, verificationTime, time, safe] = bouncing_ball_mhypro(saveFig, savePath, figName, bad, diff,settings,setRepr,aggr, plotting)

% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%                 loc loc_1
%-----------------------------------------------%
loc = MHyProLocation();
loc.setName('loc');

% Set flow:
% x' = v v' = -9.81 t' = 1
flowMatrix = [0 1 0 0; 0 0 0 -9.81;0 0 0 1; 0 0 0 0];
loc.setFlow(flowMatrix);

% Set invariant x >= 0 & t <= 4
inv = MHyProCondition([-1 0 0; 0 0 1], [0; 4]);
loc.setInvariant(inv);

%-----------------------------------------------%
%                 loc sink
%-----------------------------------------------%

loc_sink = MHyProLocation();
loc_sink.setName('sink');

% Set flow:
% x' = 0 v' = 0 t' = 0
flowMatrix = zeros(3);
loc_sink.setFlow(flowMatrix);

% Set invariant x >= 0
% inv = MHyProCondition([-1 0 0], [0]);
% loc.setInvariant(inv);

l = automaton.addLocation(loc);
s = automaton.addLocation(loc_sink);

%-----------------------------------------------%
%                loc -> loc
%-----------------------------------------------%
tran = MHyProTransition();
% Set guard:
% x = 0 & v <= 0
guard = MHyProCondition();
guard.setMatrix([ -1 0 0; 1 0 0; 0 1 0]); 
guard.setVector([0;0;0]);

% Set reset
% x:= x v:= -0.75v t := t
reset = MHyProReset();
reset.setMatrix([1 0 0; 0 -0.75 0; 0 0 1]);
reset.setVector([0;0;0]);

tran.setAggregation(aggr);
tran.setGuard(guard);
tran.setSource(l);
tran.setTarget(l);
tran.setReset(reset);
tran.setLabels({MHyProLabel('t1')});

l.addTransition(tran);

%-----------------------------------------------%
%                loc -> loc_sink
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard:
% t == 4
guard2 = MHyProCondition();
guard2.setMatrix([ 0 0 -1; 0 0 1]);
guard2.setVector([-4;4]);

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
boxVector = [-10; 10.2; 0; 0; 0; 0];
boxMatrix = [-1 0 0; 1 0 0; 0 1 0; 0 -1 0; 0 0 -1; 0 0 1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l, initialCond);


%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

if bad
    if diff == 1
        % easy
%         badState = MHyProCondition();
%         badState.setMatrix([0 -1 0]);
%         badState.setVector(-10.7);
%         badStates(1).loc = l;
%         badStates(1).cond = badState;
        %easy: v <= 10.7
        spec = [0 1 0 10.7]; 
    elseif diff == 2
        % medium
%         badState = MHyProCondition();
%         badState.setMatrix([0 -1 0]);
%         badState.setVector(-10.6569);
%         badStates(1).loc = l;
%         badStates(1).cond = badState;
        %medium: v <= 10.6569
        spec = [0 1 0 10.6569];
    elseif diff == 3
        % hard
%         badState = MHyProCondition();
%         badState.setMatrix([0 -1 0]);
%         badState.setVector(-10.6138);
%         badStates(1).loc = l;
%         badStates(1).cond = badState;
        %hard: v <= 10.6138
        spec = [0 1 0 10.6138];
    elseif diff == 4
%         badState = MHyProCondition();
%         badState.setMatrix([1 0 0]);
%         badState.setVector(-0.000000001);
%         badStates(1).loc = l;
%         badStates(1).cond = badState;
        %special: x >= 0 
        spec = [-1 0 0 0];
    end
        

%     automaton.setLocalBadStates(badStates);
end

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = 4;
settings.jumpDepth = 2;

reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(setRepr);

tic;
flowpipes = reach.computeForwardReachability();
reachabilityTime = toc;
verificationTime = 0;
safe = 0;
if bad
    tic;
    safe = reach.verify(flowpipes, spec);
% 	safe = 1 - reach.reachedBadStates();
    verificationTime = toc;
end

time = reachabilityTime + verificationTime;
disp(['Time needed for reachability: ', num2str(reachabilityTime)]);
% disp(['Time needed for verification: ', num2str(verificationTime)]);
% disp(.'Overall time needed: ', num2str(time)]);
% 
% log = ['bouncing_ball ', num2str(strategy), ' ', num2str(diff), ' ',...
%     num2str(reachabilityTime), ' ',  num2str(verificationTime), ' ',...
%     num2str(time), ' ', num2str(safe)];

if plotting == 1
    dim = [2 1];
    labs = ["v", "x"];
    ext = 'png';
    reach.plot(flowpipes, dim, labs,saveFig,savePath,figName,ext);
    set(gca,'FontSize',15);
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
%     if diff == 0
%         [x, y] = meshgrid(-15:0.5:15,10.7:0.1:15);
%         reach.plotBadStates3D([0 -1 0], -10.7, [2 1], x,y);
%     elseif diff == 1
%         [x, y] = meshgrid(-15:0.5:15,10.6569:0.1:15);
%         reach.plotBadStates3D([0 -1 0], -10.6569, [2 1], x,y);
%     else
%         [x, y] = meshgrid(-15:0.5:15,10.6138:0.1:15);
%         reach.plotBadStates3D([0 -1 0], -10.6138, [2 1], x,y);
%     end
    
end

end
