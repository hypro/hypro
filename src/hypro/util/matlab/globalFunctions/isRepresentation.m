function out = isRepresentation(arg)
% This function checks if arg is a state representation.

    if isa(arg, 'MHyProBox') || isa(arg, 'MHyProConstraintSet') ||...
            isa(arg, 'MHyProSupportFunction') || isa(arg, 'MHyProEllipsoid') ||...#
            isa(arg, 'MHyProZonotope')
        out = 1;
    else
        out = 0;
    end
end