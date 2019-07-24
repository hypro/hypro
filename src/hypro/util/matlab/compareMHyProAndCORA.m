function compareMHyProAndCORA(benchmark, timeHorizon, diff)

saveFig = 1;
savePath = '/home/marta/Desktop';


mhStrategies{1} = [20,45,4];
mhStrategies{2} = [2,2,2]; % TODO
mhStrategies{3} = [2,20,67];
mhStrategies{4} = [58,23,23];
mhStrategies{5} = [11,66,23];
mhStrategies{6} = [4,4,71];
mhStrategies{7} = [11,66,59];
mhStrategies{8} = [1,1,1];%TODO
mhStrategies{9} = [1,1,1];%TODO
mhStrategies{10} = [28,68,68];

coraStrategies{1} = [5,13,10];
coraStrategies{2} = [1,1,1]; %TODO
coraStrategies{3} = [9,17,1]; %TODO
coraStrategies{4} = [8,17,14];
coraStrategies{5} = [1,1,1]; %TODO
coraStrategies{6} = [4,4,4];
coraStrategies{7} = [18,18,17];
coraStrategies{8} = [1,1,1]; %TODO
coraStrategies{9} = [1,1,1]; %TODO
coraStrategies{10} = [10,10,22];



mhStrategyNr = mhStrategies{benchmark}(diff);
cStrategyNr = coraStrategies{benchmark}(diff);



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