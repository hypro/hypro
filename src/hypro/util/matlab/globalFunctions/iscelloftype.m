function out = iscelloftype(cellArray, type)
% This function check if all elements of a cell array are of certain type.
%   Input:
%       cellArry: cell array containing MHyPro* (* = Objects, Flow, Location, etc.)
%       type : string containing the name of a MHyProElement
%

    for i=(1:length(cellArray))
        elem = cellArray(i);
        if strcmp(elem.Type, type) == 0
            error("iscelloftype: At least one element in cell has wrong type.");
        end
    end
    
out = 1;
