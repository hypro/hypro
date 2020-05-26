var MHyProReach_8m =
[
    [ "disp", "MHyProReach_8m.html#add30404391d4f00d212fcfbd2bad9523", null ],
    [ "error", "MHyProReach_8m.html#aa9aa9eb371d856c98aabe648185d0e51", null ],
    [ "isempty", "MHyProReach_8m.html#a484a27b4d5e969608af76fb10636399d", null ],
    [ "plot", "MHyProReach_8m.html#a619b2a0a8324c0def2f0faba09ff72b3", null ],
    [ "plotVertices", "MHyProReach_8m.html#aae48675bce91c243f48ebb033c84bd81", null ],
    [ "saveas", "MHyProReach_8m.html#af59f1d9ffdb0b9a83d253ce6be9a556d", null ],
    [ "settings", "MHyProReach_8m.html#a5d6fdd7a4dcb6a817ecc45e7dc44eedb", null ],
    [ "warning", "MHyProReach_8m.html#a2b430442ae110d3f3059eb7951741731", null ],
    [ "xlabel", "MHyProReach_8m.html#ac1b57e35ce2b6b17e34c993d8adacb81", null ],
    [ "ylabel", "MHyProReach_8m.html#addb04878ba0f3550bf46e2f16a780233", null ],
    [ "MHyProReach< handleproperties(SetAccess=public, GetAccess=public) ObjectHandleendmethods(Access=private)%Destructorfunction delete(obj) MHyPro(12, 1, obj.ObjectHandle);endendmethods(Access=public)%Constructorfunction obj=MHyProReach(varargin) if nargin==1 &&isa(varargin{1}, 'MHyProHAutomaton') obj.ObjectHandle=MHyPro(12, 2, varargin{1}.ObjectHandle);elseerror('MHyProReach-Constructor:Wrong type of at least one argument.');endendfunction out=computeForwardReachability(obj) flowpipes=MHyPro(12, 3, obj.ObjectHandle);out=cell(1, length(flowpipes));for i=1:length(flowpipes) states=flowpipes(i).flowpipe;fPipe=cell(1, length(states));for j=1:length(states) if isa(states{j}, 'uint64') fPipe{j}=MHyProState(states{j});elseerror('MHyProReach-computeForwardReach:Wrong type of input argument.');endendout{i}=fPipe;endendfunction setSettings(obj, settings) if isstruct(settings) fields=fieldnames(settings);for i=1:length(fields) currentField=fields{i};if~strcmp(currentField, 'timeBound')&&~strcmp(currentField, 'jumpDepth')...&&~strcmp(currentField, 'timeStep')&&~strcmp(currentField, 'plotDimensions')...&&~strcmp(currentField, 'pplDenomimator')&&~strcmp(currentField, 'uniformBloating')...&&~strcmp(currentField, 'fileName')&&~strcmp(currentField, 'clustering') error(['MHyProReach-setSettings:Unknown field name ', currentField]);endendMHyPro(12, 4, obj.ObjectHandle, settings);elseerror('MHyProReach-setSettings:Wrong type of at least one argument.');endendfunction setRepresentationType(obj, type)%0=box, 1=carl_polytope, 2=constraint_set%3=polytope_h, 4=polytope_v%5=ppl_polytope, 6=support_function, 7=taylor_model%8=zonotope, 9=difference_bounds, if type >", "MHyProReach_8m.html#a351fdf87a709fab088dee30e05e0129d", null ],
    [ "dims", "MHyProReach_8m.html#a21c000e2605df16131e658866b6acc2a", null ],
    [ "fig", "MHyProReach_8m.html#a64aa603bc3c6c1587e7c6542452481ac", null ],
    [ "fname", "MHyProReach_8m.html#a358f0907abcb80946470e08b0c2097da", null ],
    [ "num_states", "MHyProReach_8m.html#a05ab0b43b96869729cd6f3cdafd62175", null ],
    [ "ObjectHandle", "MHyProReach_8m.html#ac1b807d9d8150789657969eab5417e7f", null ],
    [ "out", "MHyProReach_8m.html#ad6e260380110062017189b2e87d38c38", null ],
    [ "second", "MHyProReach_8m.html#acfd440223f806c44323dbd1053b99123", null ],
    [ "state", "MHyProReach_8m.html#ab5c0b4e520cf99652198e3bd757f1d9a", null ],
    [ "temp", "MHyProReach_8m.html#a905c521e05ec8042631a912b71d0454e", null ],
    [ "vertices", "MHyProReach_8m.html#aebcc24217a3bac0520ed4decef6d1ec2", null ]
];