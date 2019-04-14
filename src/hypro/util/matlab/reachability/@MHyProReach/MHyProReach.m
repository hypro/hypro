classdef MHyProReach < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro('Reacher', 'delete', obj.Handle);
        end
        
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProReach(varargin)
            if nargin == 2 && isa(varargin{1}, 'MHyProHAutomaton') && isstruct(varargin{2})
                fields = fieldnames(varargin{2});         
                for i = 1:length(fields)
                    currentField = fields{i};
                    if ~strcmp(currentField, 'timeBound') && ~strcmp(currentField, 'jumpDepth')...
                            && ~strcmp(currentField, 'timeStep') && ~strcmp(currentField, 'plotDimensions')...
                            && ~strcmp(currentField, 'pplDenomimator') && ~strcmp(currentField, 'uniformBloating')...
                            && ~strcmp(currentField, 'fileName')
                        error(['MHyProReach - Constructor: Unknown field name ', currentField]);
                    end
                end
                obj.Handle = MHyPro('Reacher', 'new_reach', varargin{1}.Handle, varargin{2});
            else
                error('MHyProReach - Constructor: Wrong type of at least one argument.');
            end
        end
        
        function out = computeForwardReachability(obj)
            states = MHyPro('Reacher', 'computeForwardReachability', obj.Handle);
            out = cell(1, length(states));
                for i = 1:length(states)
                    states(i).flowpipe
%                     if isa(states{i}, 'uint64')
% %                         out{i} = MHyProState(states(i));
%                     else
%                         error('MHyProReach - computeForwardReach: Wrong type of input argument.');
%                     end
                end 
        end
        
    end
    
end