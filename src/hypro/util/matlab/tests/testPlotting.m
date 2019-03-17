function res = testPlotting

try
   box = MHyProBox('intervals', [1 2; 3 4]);
   box.plot([1 2]);
catch
   disp('Not possible to plot MBox');
end

try
   set = MHyProConstraintSet(eye(3), [1;2;3]);
   set.plot([1 2]);
catch
   disp('Not possible to plot MConstraintSet');
end


res = 1;