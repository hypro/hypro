function compareMHyProAndCORA(benchmark, timeHorizon, mhStrategyNr, cStrategyNr)

saveFig = 1;
savePath = '/home/marta/Desktop';

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
    compareBB_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath);
elseif benchmark == 2
    fname = strcat('comp_CC','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareCC_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath);
elseif benchmark == 3
    fname = strcat('comp_FO4','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareFO4_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath);
elseif benchmark == 4
    fname = strcat('comp_FO8','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareFO8_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath);
elseif benchmark == 5
    fname = strcat('comp_FO16','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareFO16_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath);
elseif benchmark == 6
    fname = strcat('comp_SS','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareSS_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath);
elseif benchmark == 7
    fname = strcat('comp_REND','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareREND_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath);
elseif benchmark == 8
    fname = strcat('comp_RR','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareRR_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath);
elseif benchmark == 9
    fname = strcat('comp_TT','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareTT_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath);
else
    fname = strcat('comp_VP','_',num2str(mhStrategyNr),'_',num2str(cStrategyNr));
    compareVP_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath);
end

end