function compareMHyProAndCORA(benchmark, timeHorizon, diff)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% With this file one can run the comparison of two benchmarks. Their
% plots will be overlaped. First mhypro is plotted then cora. Except
% for the vehicle platoon as the results obtained by mhypro are more
% presice.
% Input: 
%   benchmark: Number of the benchmark
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
%   timeHorizon: Time horizon for the reachability analysis (global)
%   diff: difficulty of the specification
%       1 - no specifications
%       2 - easy specifications
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

saveFig = 0; % If set then figures will be saved in the savePath
savePath = '/home';

mhStrategies{1} = [3,21]; % bb
mhStrategies{2} = [2,1]; % cc
mhStrategies{3} = [9,12]; % fo4 
mhStrategies{4} = [9,121]; % fo8
mhStrategies{5} = [9,12];  % fo16
mhStrategies{6} = [39,41]; % sw
mhStrategies{7} = [3,12]; %sr
mhStrategies{8} = [3,5]; %rr
mhStrategies{9} = [3,3]; %tt
mhStrategies{10} = [33,33]; %vp

coraStrategies{1} = [8,17]; % bb
coraStrategies{2} = [1,1]; %cc
coraStrategies{3} = [34,34]; % fo4
coraStrategies{4} = [34,15]; % fo8
coraStrategies{5} = [36,36];  %fo16
coraStrategies{6} = [33,10]; % sw
coraStrategies{7} = [8,17]; %sr
coraStrategies{8} = [8,11]; %rr
coraStrategies{9} = [35,36]; %tt
coraStrategies{10} = [7,8]; %vp
mhStrategyNr = mhStrategies{benchmark}(diff);
cStrategyNr = coraStrategies{benchmark}(diff);


[settings, setRepr, aggr] = getNewStrategy(mhStrategyNr);
mhStrat.timeStep = settings.timeStep;
mhStrat.clustering = settings.clustering;
mhStrat.setRepr = setRepr;
mhStrat.aggr = aggr;
[timeStep, tTerms, zOrder, pOrder] = getCORAStrategy(cStrategyNr);
cStrat.timeStep = timeStep;
cStrat.tT = tTerms;
cStrat.zO = zOrder;
cStrat.pO = pOrder;

disp(['MHyPro Strategy: ', num2str(mhStrategyNr)]);
disp(['CORA Strategy: ', num2str(cStrategyNr)]);

if benchmark == 1
    fname = strcat('comp_BB','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareBB_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 2
    fname = strcat('comp_CC','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareCC_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 3
    fname = strcat('comp_FO4','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareFO4_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 4
    fname = strcat('comp_FO8','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareFO8_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 5
    fname = strcat('comp_FO16','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareFO16_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 6
    fname = strcat('comp_SW','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareSW_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 7
    fname = strcat('comp_REND','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareREND_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 8
    fname = strcat('comp_RR','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareRR_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 9
    fname = strcat('comp_TT','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareTT_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 10
    fname = strcat('comp_VP','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareVP_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
else
    error('No such benchmark');
end

end
