function compareMHyProAndCORA(benchmark, timeHorizon, diff)

saveFig = 0;
simulate = 0;
savePath = '/home/marta/Desktop';

if diff > 0

    mhStrategies{1} = [3,21,17,11]; % bb
    mhStrategies{2} = [2,1,1,1]; % cc
    mhStrategies{3} = [9,12,2,27]; % fo4 
    mhStrategies{4} = [9,12,11,15]; % fo8
    mhStrategies{5} = [9,12,5,3];  % fo16
    mhStrategies{6} = [29,41,55,17]; % sw
    mhStrategies{7} = [3,12,30,51]; %sr
    mhStrategies{8} = [3,5,11,1]; %rr
    mhStrategies{9} = [3,3,1,1]; %tt
    mhStrategies{10} = [33,33,13,13]; %vp

    coraStrategies{1} = [8,17,10,10]; % bb
    coraStrategies{2} = [1,1,1,1]; %cc
    coraStrategies{3} = [34,34,4,4]; % fo4
    coraStrategies{4} = [34,15,14,15]; % fo8
    coraStrategies{5} = [36,36,1,1];  %fo16
    coraStrategies{6} = [33,10,4,4]; % sw
    coraStrategies{7} = [8,17,31,4]; %sr
    coraStrategies{8} = [8,11,11,11]; %rr
    coraStrategies{9} = [35,36,20,20]; %tt
    coraStrategies{10} = [7,36,21,18]; %vp
    mhStrategyNr = mhStrategies{benchmark}(diff);
    cStrategyNr = coraStrategies{benchmark}(diff);
else
    % Initial strategies

    mhStrategies{1} = 3; % bb
    mhStrategies{2} = 2; % cc
    mhStrategies{3} = 9; % fo4
    mhStrategies{4} = 9; % fo8
    mhStrategies{5} = 9; % fo16
    mhStrategies{6} = 39; % sw
    mhStrategies{7} = 3; % sr
    mhStrategies{8} = 3; % rr
    mhStrategies{9} = 3; % tt
    mhStrategies{10} = 33; % vp

    coraStrategies{1} = 8; %bb
    coraStrategies{2} = 1; %cc
    coraStrategies{3} = 34; % fo4
    coraStrategies{4} = 34; % fo8
    coraStrategies{5} = 36; % fo16
    coraStrategies{6} = 33; % sw
    coraStrategies{7} = 8; % sr
    coraStrategies{8} = 8; % rr
    coraStrategies{9} = 35; % tt
    coraStrategies{10} = 7; % vp
    
    mhStrategyNr = mhStrategies{benchmark};
    cStrategyNr = coraStrategies{benchmark};
end

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
    compareBB_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
elseif benchmark == 2
    fname = strcat('comp_CC','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareCC_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
elseif benchmark == 3
    fname = strcat('comp_FO4','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareFO4_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
elseif benchmark == 4
    fname = strcat('comp_FO8','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareFO8_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
elseif benchmark == 5
    fname = strcat('comp_FO16','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareFO16_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
elseif benchmark == 6
    fname = strcat('comp_SS','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareSS_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
elseif benchmark == 7
    fname = strcat('comp_REND','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareREND_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
elseif benchmark == 8
    fname = strcat('comp_RR','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareRR_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
elseif benchmark == 9
    fname = strcat('comp_TT','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareTT_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
else
    fname = strcat('comp_VP','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareVP_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
end

end