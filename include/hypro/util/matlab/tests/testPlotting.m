function res = testPlotting

try
   box = MHyProBox('intervals', [1 2; 3 4]);
   box.plot([1 2]);
catch
   disp('Not possible to plot MBox');
end

try
   fct = MHyProSupportFunction('intervals', [1 2; 3 4; 5 6]);
   fct.plot([2 3]);
catch
   disp('Not possible to plot MSupportFunction');
end


res = 1;