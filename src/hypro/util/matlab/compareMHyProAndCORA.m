function compareMHyProAndCORA(benchmark, timeHorizon, diff)

saveFig = 0;
savePath = '/home/marta/Desktop';

if diff > 0
    mhStrategies{1} = [20,45,4,45];
    mhStrategies{2} = [2,2,2,2]; % TODO
    mhStrategies{3} = [2,20,67,67];
    mhStrategies{4} = [58,23,23,23];
    mhStrategies{5} = [11,66,23,23];
    mhStrategies{6} = [4,4,71,4];
    mhStrategies{7} = [11,66,59,59];
    mhStrategies{8} = [1,1,1,1];%TODO
    mhStrategies{9} = [1,1,1,1];%TODO
    mhStrategies{10} = [28,68,68,28];

    coraStrategies{1} = [35,13,10,13];
    coraStrategies{2} = [1,1,1,1]; %TODO
    coraStrategies{3} = [9,17,17,17]; %TODO
    coraStrategies{4} = [8,17,14,14];
    coraStrategies{5} = [1,1,1,1]; %TODO
    coraStrategies{6} = [29,4,4,4];
    coraStrategies{7} = [18,18,17,17];
    coraStrategies{8} = [31,1,1,1]; %TODO
    coraStrategies{9} = [1,1,1,1]; %TODO
    coraStrategies{10} = [10,10,22,22];
    mhStrategyNr = mhStrategies{benchmark}(diff);
    cStrategyNr = coraStrategies{benchmark}(diff);
else
    % Standard strategies
    mhStrategies{1} = 1; 
    mhStrategies{2} = 2;
    mhStrategies{3} = 3;
    mhStrategies{4} = 3;
    mhStrategies{5} = 3;
    mhStrategies{6} = 4;
    mhStrategies{7} = 1;
    mhStrategies{8} = 1;
    mhStrategies{9} = 1;
    mhStrategies{10} = 4;

    coraStrategies{1} = 2;
    coraStrategies{2} = 1; 
    coraStrategies{3} = 9; 
    coraStrategies{4} = 9;
    coraStrategies{5} = 9; 
    coraStrategies{6} = 28;
    coraStrategies{7} = 2;
    coraStrategies{8} = 2;
    coraStrategies{9} = 2; 
    coraStrategies{10} = 17;
    
    mhStrategyNr = mhStrategies{benchmark};
    cStrategyNr = coraStrategies{benchmark};
end

[settings, setRepr, aggr] = getStrategy(mhStrategyNr);
mhStrat.timeStep = settings{1}.timeStep;
mhStrat.clustering = settings{1}.clustering;
mhStrat.setRepr = setRepr{1};
mhStrat.aggr = aggr{1};
[timeStep, tTerms, zOrder, pOrder] = getCORAStrategy(cStrategyNr);
cStrat.timeStep = timeStep;
cStrat.tT = tTerms;
cStrat.zO = zOrder;
cStrat.pO = pOrder;

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
    fname = strcat('comp_SS','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareSS_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 7
    fname = strcat('comp_REND','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareREND_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 8
    fname = strcat('comp_RR','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareRR_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
elseif benchmark == 9
    fname = strcat('comp_TT','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareTT_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
else
    fname = strcat('comp_VP','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareVP_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff);
end

end