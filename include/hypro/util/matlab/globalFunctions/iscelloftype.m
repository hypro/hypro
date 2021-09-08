function out = iscelloftype(cellArray, type)
% This function check if all elements of a cell array are of certain type.
%   Input:
%       cellArry: cell array containing MHyPro* (* = Objects, Flow, Location, etc.)
%       type : number representation of the type
%
    out = 1;
    for i= 1:length(cellArray) 
        elem = cellArray{i};
        if elem.Type ~= type
            out = 0;
        end
    end
end
