function Gearbox

%parameters
theta = 0.9; % coefficient of restitution
m_s = 3.2; %[kg], mass of sleve
m_g2 = 18.1; %[kg], mass of second gear
J_g2 = 0.7; %[kg m^2], inertia of second gear
R_s = 0.08; %[m], radius of sleeve
Theta = 36/180*pi; %[rad], included angle of gear
b = 0.01; %[m], width of gear spline
delta_p = -0.002; %[m], p_x sleeve meshes with gear 
%n = 1; % integer number in guard
n = 0; % integer number in guard
F_s = 70; %[N], shifting force
T_f = 1; %[Mm], resisting moment

%define large and small distance
dist = 1e3;
smallDist = 1e3*eps;

%first guard set
ch_n = [0, 0, -tan(Theta), -1, 0];
ch_d = -2*n*b;
ch_C(1,:) = [0, 0, 1, 0, 0];
ch_C(2,:) = [0, 0, -1, 0, 0];
ch_C(3,:) = [-sin(Theta), -cos(Theta), 0, 0, 0];
ch_D = [delta_p; b/tan(Theta); 0];
guard1 = constrainedHyperplane(halfspace(ch_n,ch_d),ch_C,ch_D);

C1(1,:) = [0, 0, -tan(Theta), -1, 0];
C1(2,:) = [0, 0, 1, 0, 0];
C1(3,:) = [0, 0, -1, 0, 0];
C1(4,:) = [-sin(Theta), -cos(Theta), 0, 0, 0];
C1(5,:) = -C1(1,:);
d1 = [-2*n*b; delta_p; b/tan(Theta); 0; -2*n*b + smallDist];

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(5));
dummy_reset.setVector(zeros(5,1));

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc_1 = MHyProLocation();
loc_1.setName('loc1');

% Set flow: 
flow_1 = [0 0 0 0 0 1/m_s;...
     0 0 0 0 0 0;...
     1 0 0 0 0 0;...
     0 1 0 0 0 0;...
     0 0 0 0 0 0;...
     0 0 0 0 0 0]; 
    
loc_1.setFlow(flow_1);

% Set inv:
invMat = [-C1(1,:); -C2(1,:); -C1(3,:)];
invVec = [d1(1); d2(1); d1(3)];
invVec = invVec + ones(length(dinv),1)*1e-3;
inv_1 = MHyProCondition(invMat, invVec);
loc_1.setInvariant(inv_1);

%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc_2 = MHyProLocation();
loc_2.setName('loc2');

% Set flow: 
flow_2 = zeros(5);
    
loc_2.setFlow(flow_2);
% Set inv:
invMat = [-1*eye(5);eye(5)];
invVec = dist * ones(10,1);
invVec = invVec + ones(length(dinv),1)*1e-3;
inv_1 = MHyProCondition(invMat, invVec);
loc_1.setInvariant(inv_1);


%-----------------------------------------------%
%              loc1 --> loc1
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard:
guard2 = MHyProCondition();
guard2.setMatrix([1 0 0 0 0; -1 0 0 0 0]); 
guard2.setVector([2;-2]);

tran2.setAggregation(1);
tran2.setGuard(guard2);
tran2.setSource(l2);
tran2.setTarget(l3);
tran2.setReset(dummy_reset);
tran2.setLabels({MHyProLabel('tran2')});

l2.addTransition(tran2);
























































end