function compareMHyProAndCORA(benchmark, timeHorizon, diff)

saveFig = 0;
simulate = 1;
savePath = '/home/marta/Desktop';

if diff > 0
    mhStrategies{1} = [3,3,4,23];
    mhStrategies{2} = [29,29,29,29];
    mhStrategies{3} = [13,38,38,38];
    mhStrategies{4} = [17,17,23,5];
    mhStrategies{5} = [61,61,61,68];
    mhStrategies{6} = [70, 70, 70,70];
    mhStrategies{7} = [66,66,56,70];
    mhStrategies{8} = [13,13,20,20];
    mhStrategies{9} = [68,68,68,68];
    mhStrategies{10} = [68,68,61,61];

    coraStrategies{1} = [35,35,10,10];
    coraStrategies{2} = [1,1,1,1]; %TODO
    coraStrategies{3} = [15,15,4,4]; %TODO
    coraStrategies{4} = [16,16,14,15];
    coraStrategies{5} = [1,1,1,1]; %TODO
    coraStrategies{6} = [20,4,4,4];
    coraStrategies{7} = [18,18,31,4];
    coraStrategies{8} = [11,11,11,11];
    coraStrategies{9} = [10,10,20,20];
    coraStrategies{10} = [10,10,21,18];
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
    compareBB_gc_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff,simulate);
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