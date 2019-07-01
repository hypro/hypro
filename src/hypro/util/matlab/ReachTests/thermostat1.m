function thermostat1
%thermostat_hypro_separateControllerAndPlant_discreteVars_with_timer

% state var cycle_time, global_time, Temp

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(3));
dummy_reset.setVector([0; 0; 0]);

globalTimeHorizon = 10;
delat = 1;

%-----------------------------------------------%
%              Location rod1
%-----------------------------------------------%
loc_1 = MHyProLocation();
loc_1.setName('loc1');

% Set flow: Temp' = -0.1*Temp +3 & global_time' = 1 & cycle_time' = 1
flow_1 = [-0.1 0 0 3;...
              0 0 0 1;...
              0 0 0 1];
loc_1.setFlow(flow_1);

% Set inv: cycle_time <= delta & global_time <= globalTimeHorizon &
% cycle_time >= 0 & global_time >= 0 & H_plc = 1
inv_1 = MHyProCondition([0 1 0; 0 -1 0; 0 0 1; 0 0 -1], [globalTimeHorizon;0;delta;0]);
loc_1.setInvariant(inv_1);


end