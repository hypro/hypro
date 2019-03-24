classdef MHyProReach < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
        Type
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro('Reach', 'delete', obj.Handle);
        end
        
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProReach(varargin)
            
            obj.Type = varargin{1};
            
            if nargin == 2 && isa(varargin{2}, 'uint64')
                obj.Handle = varargin{2};
            elseif nargin == 3 
                % 0 = Box, 1 = Ellip, 2 = ConstraintSet, 3 =
                % SupportFunction
                obj = MHyPro('Reach', 'new_reach', varargin{2}, varargin{3});
            else
                error('MHyProReach - Constructor: Wrong type of at least one argument.');
            end
        end
        
        function out = computeForwardReachability(obj)
            states = MHyPro('Reach', 'computeForwardReachability', obj.Handle);
            out = cell(1, length(states));
                for i = 1:length(states)
                    if isa(states{i}, 'uint64')
                        out{i} = MHyProState(states{i});
                    else
                        error('MHyProReach - computeForwardReach: Wrong type of input argument.');
                    end
                end 
        end
        
    end
    
end