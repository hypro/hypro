function thermostat1
%thermostat_hypro_withAggregation_separateControllerAndPlant_discreteVars_with_timer

% state var cycle_time, global_time, Temp

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(3));
dummy_reset.setVector([0; 0; 0]);

globalTimeHorizon = 10;
delat = 1;

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc_1 = MHyProLocation();
loc_1.setName('loc1');

% Set flow: Temp' = -0.1*Temp +3 & global_time' = 1 & cycle_time' = 1
flow_1 = [0 0 0 1;...
          0 0 0 1;...
         -0.1 0 0 3];
loc_1.setFlow(flow_1);

% Set inv: cycle_time <= delta & global_time <= globalTimeHorizon &
% cycle_time >= 0 & global_time >= 0 & H_plc = 1
inv_1 = MHyProCondition([0 1 0; 0 -1 0; 0 0 1; 0 0 -1], [globalTimeHorizon;0;delta;0]);
loc_1.setInvariant(inv_1);

%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc_2 = MHyProLocation();
loc_2.setName('loc2');

% Set flow: Temp' = -0.1*Temp & global_time' = 1 & cycle_time' = 1
flow_2 = [0 0 0 1;...
          0 0 0 1;...
          -0.1 0 0 0];
loc_2.setFlow(flow_2);

% Set inv: cycle_time <= delta & global_time <= globalTimeHorizon &
% cycle_time >= 0 & global_time >= 0 & H_plc = 1
inv_2 = MHyProCondition([0 1 0; 0 -1 0; 0 0 1; 0 0 -1], [globalTimeHorizon;0;delta;0]);
loc_2.setInvariant(inv_2);

%-----------------------------------------------%
%              Location cloc_switch_on_cycle
%-----------------------------------------------%
loc_3 = MHyProLocation();
loc_3.setName('cloc_switch_on_cycle');

% Set flow: Temp' = 0 & global_time' = 1 & cycle_time' = 1
flow_3 = [0 0 0 1;...
              0 0 0 1;...
              0 0 0 0];
loc_3.setFlow(flow_3);

% Set inv: cycle_time1 = 0 & 0 <= global_time < globalTimeHorizon
inv_3 = MHyProCondition([1 0 0; -1 0 0; 0 -1 0; 0 1 0], [0;0;0;globalTimeHorizon]);
loc_3.setInvariant(inv_3);

%-----------------------------------------------%
%              Location clock_switch_on_in_comm
%-----------------------------------------------%
loc_4 = MHyProLocation();
loc_4.setName('cloc_switch_on_in_comm');

% Set flow: Temp' = 0 & global_time' = 1 & cycle_time' = 1
flow_4 = [0 0 0 1;...
          0 0 0 1;...
          0 0 0 0];
loc_4.setFlow(flow_4);

% Set inv: cycle_time1 = 0 & 0 <= global_time < globalTimeHorizon
inv_4 = MHyProCondition([1 0 0; -1 0 0; 0 -1 0; 0 1 0], [0;0;0;globalTimeHorizon]);
loc_4.setInvariant(inv_4);

%-----------------------------------------------%
%              Location clock_switch_on_in_cycle
%-----------------------------------------------%
loc_5 = MHyProLocation();
loc_5.setName('cloc_switch_on_in_cycle');

% Set flow: Temp' = 0 & global_time' = 1 & cycle_time' = 1
flow_5 = [0 0 0 1;...
          0 0 0 1;...
          0 0 0 0];
loc_5.setFlow(flow_5);

% Set inv: cycle_time1 = 0 & 0 <= global_time < globalTimeHorizon
inv_5 = MHyProCondition([1 0 0; -1 0 0; 0 -1 0; 0 1 0], [0;0;0;globalTimeHorizon]);
loc_5.setInvariant(inv_5);

%-----------------------------------------------%
%              Location clock_switch_off_cycle
%-----------------------------------------------%
loc_6 = MHyProLocation();
loc_6.setName('cloc_switch_off_cycle');

% Set flow: Temp' = 0 & global_time' = 1 & cycle_time' = 1
flow_6 = [0 0 0 1;...
          0 0 0 1;...
          0 0 0 0];
loc_6.setFlow(flow_6);

% Set inv: cycle_time1 = 0 & 0 <= global_time < globalTimeHorizon
inv_6 = MHyProCondition([1 0 0; -1 0 0; 0 -1 0; 0 1 0], [0;0;0;globalTimeHorizon]);
loc_6.setInvariant(inv_6);

%-----------------------------------------------%
%              Location clock_switch_off_in_comm
%-----------------------------------------------%
loc_7 = MHyProLocation();
loc_7.setName('cloc_switch_off_in_comm');

% Set flow: Temp' = 0 & global_time' = 1 & cycle_time' = 1
flow_7 = [0 0 0 1;...
          0 0 0 1;...
          0 0 0 0];
loc_7.setFlow(flow_7);

% Set inv: cycle_time1 = 0 & 0 <= global_time < globalTimeHorizon
inv_7 = MHyProCondition([1 0 0; -1 0 0; 0 -1 0; 0 1 0], [0;0;0;globalTimeHorizon]);
loc_7.setInvariant(inv_7);

%-----------------------------------------------%
%              Location clock_switch_on_in_cycle
%-----------------------------------------------%
loc_8 = MHyProLocation();
loc_8.setName('cloc_switch_on_in_cycle');

% Set flow: Temp' = 0 & global_time' = 1 & cycle_time' = 1
flow_8 = [0 0 0 1;...
          0 0 0 1;...
          0 0 0 0];
loc_8.setFlow(flow_8);

% Set inv: cycle_time1 = 0 & 0 <= global_time < globalTimeHorizon
inv_8 = MHyProCondition([1 0 0; -1 0 0; 0 -1 0; 0 1 0], [0;0;0;globalTimeHorizon]);
loc_8.setInvariant(inv_8);



%-----------------------------------------------%
%              Add locations to HA
%-----------------------------------------------%

l1 = automaton.addLocation(loc_1);
l2 = automaton.addLocation(loc_2);
l3 = automaton.addLocation(loc_3);
l4 = automaton.addLocation(loc_4);
l5 = automaton.addLocation(loc_5);
l6 = automaton.addLocation(loc_6);
l7 = automaton.addLocation(loc_7);
l8 = automaton.addLocation(loc_8);

%-----------------------------------------------%
%              loc8 --> loc1
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard: cycle_time1 = 0
guard1 = MHyProCondition();
guard1.setMatrix([1 0 0; -1 0 0]); 
guard1.setVector([0;0]);

tran1.setAggregation(1);
tran1.setGuard(guard1);
tran1.setSource(l8);
tran1.setTarget(l1);
reset1 = MHyProReset();
reset1.setMatrix(eye(3));
reset1.setVector([0; 0; 0]);
tran1.setReset(dummy_reset);
tran1.setLabels({MHyProLabel('tran1')});

l1.addTransition(tran1);



end