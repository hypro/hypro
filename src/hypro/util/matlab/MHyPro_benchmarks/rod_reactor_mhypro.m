function [reachabilityTime, verificationTime, time, safe] = rod_reactor_mhypro(saveFig, savePath, figName, bad, diff,settings,setRepr,aggr, plotting)

timeHorizon = 15;

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(4));
dummy_reset.setVector([0; 0; 0; 0]);

%-----------------------------------------------%
%              Location rod1
%-----------------------------------------------%
loc_rod1 = MHyProLocation();
loc_rod1.setName('rod1');

% Set flow: x' = 0.1x - 56 c1' = 1 c2' = 1 gc' = 1
flow_rod1 = [0.1 0 0 0 -56; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 0];
loc_rod1.setFlow(flow_rod1);

% Set inv: x >= 510 & gc <= timeHorizon
inv_rod1 = MHyProCondition([-1 0 0 0; 0 0 0 1], [-510;timeHorizon]);
loc_rod1.setInvariant(inv_rod1);

%-----------------------------------------------%
%              Location noRods
%-----------------------------------------------%
loc_no = MHyProLocation();
loc_no.setName('noRods');

% Set flow: x' = 0.1x - 50 c1' = 1 c2' = 1 gc' = 1
flow_no = [0.1 0 0 0 -50; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 0];
loc_no.setFlow(flow_no);

% Set inv: x <= 550 & gc <= timeHorizon
inv_no = MHyProCondition([1 0 0 0; 0 0 0 1], [550;timeHorizon]);
loc_no.setInvariant(inv_no);

%-----------------------------------------------%
%              Location rod2
%-----------------------------------------------%
loc_rod2 = MHyProLocation();
loc_rod2.setName('rod2');

% Set flow: x' = 0.1x - 60 c1' = 1 c2' = 1 gc' = 1
flow_rod2 = [0.1 0 0 0 -60; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 0];
loc_rod2.setFlow(flow_rod2);

% Set inv: x >= 510 & gc <= timeHorizon
inv_rod2 = MHyProCondition([-1 0 0 0; 0 0 0 1], [-510;timeHorizon]);
loc_rod2.setInvariant(inv_rod2);

%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
sink = MHyProLocation();
sink.setName('sink');
sink.setFlow(zeros(4));


%-----------------------------------------------%
%              Add locations to HA
%-----------------------------------------------%

rod1 = automaton.addLocation(loc_rod1);
rod2 = automaton.addLocation(loc_rod2);
noRod = automaton.addLocation(loc_no);
s = automaton.addLocation(sink);

%-----------------------------------------------%
%              rod1 --> noRods
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard: x = 510
guard1 = MHyProCondition();
guard1.setMatrix([1 0 0 0; -1 0 0 0]);
guard1.setVector([510; -510]);
% Set reset: c1 := 0
reset1 = MHyProReset();
reset1.setMatrix([1 0 0 0; 0 0 0 0; 0 0 1 0; 0 0 0 1]);
reset1.setVector([0; 0; 0; 0]);

tran1.setAggregation(aggr);
tran1.setGuard(guard1);
tran1.setSource(rod1);
tran1.setTarget(noRod);
tran1.setReset(reset1);
tran1.setLabels({MHyProLabel('tran1')});

rod1.addTransition(tran1);

%-----------------------------------------------%
%              noRods --> rod1
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard: x = 550 & c1 >= 20
guard2 = MHyProCondition();
guard2.setMatrix([1 0 0 0; -1 0 0 0; 0 -1 0 0]);
guard2.setVector([550; -550; -20]);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(noRod);
tran2.setTarget(rod1);
tran2.setReset(dummy_reset);
tran2.setLabels({MHyProLabel('tran2')});

noRod.addTransition(tran2);

%-----------------------------------------------%
%              noRods --> rod2
%-----------------------------------------------%
tran3 = MHyProTransition();
% Set guard: x = 550 & c2 >= 20
guard3 = MHyProCondition();
guard3.setMatrix([1 0 0 0; -1 0 0 0; 0 0 -1 0]);
guard3.setVector([550; -550; -20]);

tran3.setAggregation(aggr);
tran3.setGuard(guard3);
tran3.setSource(noRod);
tran3.setTarget(rod2);
tran3.setReset(dummy_reset);
tran3.setLabels({MHyProLabel('tran3')});

noRod.addTransition(tran3);

%-----------------------------------------------%
%              rod2 --> noRods
%-----------------------------------------------%
tran4 = MHyProTransition();
% Set guard: x = 510
guard4 = MHyProCondition();
guard4.setMatrix([1 0 0 0; -1 0 0 0]); % First set the matrix then the vector!?
guard4.setVector([510; -510]);
% Set reset: c2 := 0
reset4 = MHyProReset();
reset4.setMatrix([1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1]);
reset4.setVector([0; 0; 0; 0]);

tran4.setAggregation(aggr);
tran4.setGuard(guard4);
tran4.setSource(rod2);
tran4.setTarget(noRod);
tran4.setReset(reset4);
tran4.setLabels({MHyProLabel('tran4')});

rod2.addTransition(tran4);

%-----------------------------------------------%
%              rod1 --> sink
%-----------------------------------------------%

% Set guard: gc == timeHorizon
sink_guard = MHyProCondition();
sink_guard.setMatrix([0 0 0 -1; 0 0 0 1]); % First set the matrix then the vector!?
sink_guard.setVector([-timeHorizon;timeHorizon]);


tran1s = MHyProTransition();
tran1s.setAggregation(0);
tran1s.setGuard(sink_guard);
tran1s.setSource(rod1);
tran1s.setTarget(s);
tran1s.setReset(dummy_reset);
tran1s.setLabels({MHyProLabel('tran1s')});

rod1.addTransition(tran1s);

%-----------------------------------------------%
%              rod2 --> sink
%-----------------------------------------------%

tran2s = MHyProTransition();
tran2s.setAggregation(0);
tran2s.setGuard(sink_guard);
tran2s.setSource(rod2);
tran2s.setTarget(s);
tran2s.setReset(dummy_reset);
tran2s.setLabels({MHyProLabel('tran2s')});

rod2.addTransition(tran2s);

%-----------------------------------------------%
%              noRod --> sink
%-----------------------------------------------%

tran3s = MHyProTransition();
tran3s.setAggregation(0);
tran3s.setGuard(sink_guard);
tran3s.setSource(noRod);
tran3s.setTarget(s);
tran3s.setReset(dummy_reset);
tran3s.setLabels({MHyProLabel('tran3s')});

noRod.addTransition(tran3s);

%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

if bad
    if diff == 1
%         %easy
%         badState = MHyProCondition();
%         badState.setMatrix([0 1 0 0; 0 0 1 0]);
%         badState.setVector([35;35]);
%         badStates(1).loc = rod1;
%         badStates(1).cond = badState;
%         badStates(2).loc = rod2;
%         badStates(2).cond = badState;
%         badStates(3).loc = noRod;
%         badStates(3).cond = badState;
            %easy: c2 <= 41.1
            spec = [0 0 1 0 41.1];
    elseif diff == 2
        %medium
%         badState = MHyProCondition();
%         badState.setMatrix([0 1 0 0; 0 0 1 0]);
%         badState.setVector([34.93;34.93]);
%         badStates(1).loc = rod1;
%         badStates(1).cond = badState;
%         badStates(2).loc = rod2;
%         badStates(2).cond = badState;
%         badStates(3).loc = noRod;
%         badStates(3).cond = badState;
        %medium: c1 >= 34.93 & c2 >= 34.93
            spec = [0 -1 0 0 -34.93; 0 0 -1 0 -34.93];
    elseif diff == 3
        %hard
%         badState = MHyProCondition();
%         badState.setMatrix([0 1 0 0; 0 0 1 0]);
%         badState.setVector([34.861;34.861]);
%         badStates(1).loc = rod1;
%         badStates(1).cond = badState;
%         badStates(2).loc = rod2;
%         badStates(2).cond = badState;
%         badStates(3).loc = noRod;
%         badStates(3).cond = badState;
        %hard: c2 <= 40.8600
            spec = [0 0 1 0 40.8600];
    elseif diff == 4
        % spec
%         badState = MHyProCondition();
%         badState.setMatrix([-1 0 0 0]);
%         badState.setVector(-550);
%         badStates(1).loc = rod1;
%         badStates(1).cond = badState;
%         badStates(2).loc = rod2;
%         badStates(2).cond = badState;
%         badStates(3).loc = noRod;
%         badStates(3).cond = badState;
        %spec: x <= 550
            spec = [1 0 0 0 550];
    end
    %automaton.setLocalBadStates(badStates);
end

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x = [510 520] c1 = [20 20] c2 =[20 20] gc = [0 0]
boxVector = [520; -510; 20; -20; 20; -20; 0; 0];
boxMatrix = [1 0 0 0; -1 0 0 0; 0 1 0 0; 0 -1 0 0; 0 0 1 0; 0 0 -1 0; 0 0 0 1; 0 0 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(noRod, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = timeHorizon;
settings.jumpDepth = 5;

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
%     safe = 1 - reach.reachedBadStates();
    verificationTime = toc;
end

time = reachabilityTime + verificationTime;
% disp(['Time needed for reachability: ', num2str(reachabilityTime)]);
% disp(['Time needed for verification: ', num2str(verificationTime)]);
% disp(['Overall time needed: ', num2str(time)]);

if plotting == 1
    dim = [1 3];
    labs = ["x", "c2"];
    ext = 'png';
    reach.plot(flowpipes, dim, labs,saveFig,savePath,figName,ext);
    set(gca,'FontSize',15);
    if bad
        if diff == 1
            y = [60;60;41.1;41.1];
            x = [560;500;500;560];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 2
            y = [60;60;34.93;34.93];
            x = [560;500;500;560];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 3
            y = [60;60;40.86;40.86];
            x = [560;500;500;560];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 4
            k = 550 : 600;
            spec1 = 0*k + 50;
            upper = 15 + 0*k;
            k1 = [k, fliplr(k)];
            inBetweenUpper = [spec1, fliplr(upper)];
            fill(k1,inBetweenUpper,[0.831, 0, 0], 'FaceAlpha',0.5, 'EdgeColor','none');
        end
    end
elseif plotting == 2
    dim = [1 2 3];
    labs = ["x", "c1", "c2"];
    ext = 'png';
    reach.plot3D(flowpipes, dim, labs,saveFig,savePath,figName,ext);
end

end
