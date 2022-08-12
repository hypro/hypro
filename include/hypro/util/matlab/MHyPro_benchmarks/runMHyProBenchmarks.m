function runMHyProBenchmarks(benchmarkNr, diff, strategy)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% With this file all benchmarks for mhypro can be run.
% Input:
%   benchmarkNr: number of the benchmark
%       1 - bouncing ball
%       2 - cruise controll
%       3 - filtered oscillator 4
%       4 - filtered oscillator 8
%       5 - filtered oscillator 16
%       6 - switching system
%       7 - spacecraft rendezvous
%       8 - rod reactor
%       9 - two tanks
%      10 - vehicle platoon
%   diff: difficulty of the specification
%       0 - no specifications
%       1 - easy specifications
%   strategy: number of the strategy that should be used for the
%             reachability analysis. The strategies can be found in
%             the file getNewStrategy.m
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

savePath = '/home';

% This need to be set to verify specifications. Note, when no
% specifications are considerd this flag has to be turned off!!!
bad = 0; 

% If this flag is set then the results will be plotted.
plot = 1;

% If this flag is set then the plot will be saved.
saveFig = 0;


names = {'mhypro_bouncing_ball','mhypro_cruise_control',...
    'mhypro_oscillator_4','mhypro_oscillator_8','mhypro_oscillator_16',...
    'mhypro_switching_system','mhypro_rendezvous', 'mhypro_rod_reactor' ,...
    'mhypro_two_tanks','mhypro_vehicle_platoon'};
rT = 0;
vT = 0;
t = 0;
    if benchmarkNr == 1
        % BOUNCING BALL
        [settings, setRepr, aggr] = getNewStrategy(strategy);
        filename = strcat(names{1},'_',num2str(diff),'_',num2str(strategy));
        [reachabilityTime, verificationTime, time, safe] = bouncing_ball_mhypro(saveFig,savePath,filename, bad, diff,settings,setRepr,aggr,plot);
        rT = rT + reachabilityTime;
        vT = vT + verificationTime;
        t = t + time;
        s = safe;
        logs = ['bouncing_ball ', num2str(strategy), ' ', num2str(diff), ' ',...
        num2str(rT), ' ',  num2str(vT), ' ',num2str(t), ' ', num2str(s)];
    elseif benchmarkNr == 2
        % CRUISE CONTROL
        [settings, setRepr, aggr] = getNewStrategy(strategy);
        filename = strcat(names{2},'_',num2str(diff),'_',num2str(strategy));
        [reachabilityTime, verificationTime, time, safe] = cruise_control_mhypro(saveFig,savePath,filename, bad, diff,settings,setRepr,aggr,plot);
        rT = rT + reachabilityTime;
        vT = vT + verificationTime;
        t = t + time;
        s = safe;
        logs = ['cruise_control ', num2str(strategy), ' ', num2str(diff), ' ',...
        num2str(rT), ' ',  num2str(vT), ' ',num2str(t), ' ', num2str(s)];
    elseif benchmarkNr == 3
     % FILTERED OSCILLATOR 4
        [settings, setRepr, aggr] = getNewStrategy(strategy);
        filename = strcat(names{3},'_',num2str(diff),'_',num2str(strategy));
        [reachabilityTime, verificationTime, time, safe] = filtered_oscillator_4_mhypro(saveFig,savePath,filename, bad, diff,settings,setRepr,aggr,plot);
        rT = rT + reachabilityTime;
        vT = vT + verificationTime;
        t = t + time;
        s = safe;
        logs = ['filtered_oscillator_4 ', num2str(strategy), ' ', num2str(diff), ' ',...
        num2str(rT), ' ',  num2str(vT), ' ',num2str(t), ' ', num2str(s)];
    elseif benchmarkNr == 4
        % FILTERED OSCILLATOR 8
        [settings, setRepr, aggr] = getNewStrategy(strategy);
        filename = strcat(names{4},'_',num2str(diff),'_',num2str(strategy));
        [reachabilityTime, verificationTime, time, safe] = filtered_oscillator_8_mhypro(saveFig,savePath,filename, bad, diff,settings,setRepr,aggr,plot);
        rT = rT + reachabilityTime;
        vT = vT + verificationTime;
        t = t + time;
        s = safe;
        logs = ['filtered_oscillator_8 ', num2str(strategy), ' ', num2str(diff), ' ',...
        num2str(rT), ' ',  num2str(vT), ' ',num2str(t), ' ', num2str(s)];
    elseif benchmarkNr == 5
        % FILTERED OSCILLATOR 16
        [settings, setRepr, aggr] = getNewStrategy(strategy);
        filename = strcat(names{5},'_',num2str(diff),'_',num2str(strategy));
        [reachabilityTime, verificationTime, time, safe] = filtered_oscillator_16_mhypro(saveFig,savePath,filename, bad, diff,settings,setRepr,aggr,plot);
        rT = rT + reachabilityTime;
        vT = vT + verificationTime;
        t = t + time;
        s = safe;
        logs = ['filtered_oscillator_16 ', num2str(strategy), ' ', num2str(diff), ' ',...
        num2str(rT), ' ',  num2str(vT), ' ',num2str(t), ' ', num2str(s)];
    elseif benchmarkNr == 6
        % SWITCHING SYSTEM
        [settings, setRepr, aggr] = getNewStrategy(strategy);
        filename = strcat(names{6},'_',num2str(diff),'_',num2str(strategy));
        [reachabilityTime, verificationTime, time, safe] = switching_system_mhypro(saveFig,savePath,filename, bad, diff,settings,setRepr,aggr,plot);
        rT = rT + reachabilityTime;
        vT = vT + verificationTime;
        t = t + time;
        s = safe;
        logs = ['switching_system ', num2str(strategy), ' ', num2str(diff), ' ',...
        num2str(rT), ' ',  num2str(vT), ' ',num2str(t), ' ', num2str(s)];
    elseif benchmarkNr == 7
        % RENDEZVOUZ
        [settings, setRepr, aggr] = getNewStrategy(strategy);
        filename = strcat(names{7},'_',num2str(diff),'_',num2str(strategy));
        [reachabilityTime, verificationTime, time, safe] = rendezvous_4np_mhypro(saveFig,savePath,filename, bad, diff,settings,setRepr,aggr,plot);
        rT = rT + reachabilityTime;
        vT = vT + verificationTime;
        t = t + time;
        s = safe;
        logs = ['rendezvous ', num2str(strategy), ' ', num2str(diff), ' ',...
        num2str(rT), ' ',  num2str(vT), ' ',num2str(t), ' ', num2str(s)];
    elseif benchmarkNr == 8
        % ROD REACTOR
        [settings, setRepr, aggr] = getNewStrategy(strategy);
        filename = strcat(names{8},'_',num2str(diff),'_',num2str(strategy));
        [reachabilityTime, verificationTime, time, safe] = rod_reactor_mhypro(saveFig,savePath,filename, bad, diff,settings,setRepr,aggr,plot);
        rT = rT + reachabilityTime;
        vT = vT + verificationTime;
        t = t + time;
        s = safe;
        logs = ['rod_reactor ', num2str(strategy), ' ', num2str(diff), ' ',...
        num2str(rT), ' ',  num2str(vT), ' ',num2str(t), ' ', num2str(s)];
    elseif benchmarkNr == 9
        % TWO TANKS
        [settings, setRepr, aggr] = getNewStrategy(strategy);
        filename = strcat(names{9},'_',num2str(diff),'_',num2str(strategy));
        [reachabilityTime, verificationTime, time, safe] = two_tanks_mhypro(saveFig,savePath,filename, bad, diff,settings,setRepr,aggr,plot);
        rT = rT + reachabilityTime;
        vT = vT + verificationTime;
        t = t + time;
        s = safe;
        logs = ['two_tanks ', num2str(strategy), ' ', num2str(diff), ' ',...
        num2str(rT), ' ',  num2str(vT), ' ',num2str(t), ' ', num2str(s)];
    else
        % VEHICLE PLATOON
        [settings, setRepr, aggr] = getNewStrategy(strategy);
        filename = strcat(names{10},'_',num2str(diff),'_',num2str(strategy));
        [reachabilityTime, verificationTime, time, safe] = vehicle_platoon_mhypro(saveFig,savePath,filename, bad, diff,settings,setRepr,aggr,plot);
        rT = rT + reachabilityTime;
        vT = vT + verificationTime;
        t = t + time;
        s = safe;
        logs = ['vehicle_platoon ', num2str(strategy), ' ', num2str(diff), ' ',...
        num2str(rT), ' ',  num2str(vT), ' ',num2str(t), ' ', num2str(s)];
    end
    
%     fileID = fopen(fullfile(savePath, 'mhypro_benchmark_results.txt'),'a');
%     fprintf(fileID, '%s\n',logs);
%     fclose(fileID);
end
