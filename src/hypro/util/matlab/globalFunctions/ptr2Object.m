function out = ptr2Object(type, ptr)

    if type == 0
        out = MHyProBox(ptr);
    elseif type == 1
        out = MHyProEllipsoid(ptr);
    elseif type == 2
        out = MHyProConstraintSet(ptr);
    elseif type == 3
        out = MHyProSupportFunction(ptr);
    elseif type == 14
        out = MHyProZonotope(ptr);
    else
        error('ptr2Object - wrong type.');
    end

end