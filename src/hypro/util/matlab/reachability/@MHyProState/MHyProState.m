classdef MHyProState < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro('State', 'delete', obj.Handle);
        end
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProState(varargin)
            if nargin == 1 && isa(varargin{1}, 'uint64')
                obj.Handle = varargin{1};
            elseif nargin == 1 && isa(varargin{1}, 'MHyProState')
                obj = MHyPro('State', 'copy', obj.Handle);
            else
                error('MState - Constructor: Wrong type of at least one argument.');
            end
        end
        
        
        function out = getSetType(obj)
            out = MHyPro('State', 'getSetType', obj.Handle);
        end
        
        function out = getSets(obj)
            stateCell = MHyPro('State', 'getSets', obj.Handle);
            out = cell(1, length(stateCell));
                for i = 1:length(stateCell)
                    if isa(stateCell{i}, 'uint64')
                        out{i} = MHyProState(stateCell{i});
                    else
                        error('MHyProState - getSets: Wrong type of input argument.');
                    end
                end 
        end
        
        function out = getTimestamp(obj)
            out = MHyPro('State', 'getTimestamp', obj.Handle);
        end
        
        function out = isempty(obj)
            out = MHyPro('State', 'isEmpty', obj.Handle);
        end
        
        function out = vertices(obj, offset)
            out = MHyPro('State', 'vertices', obj.Handle, offset);
        end
        
        function out = project(obj, dims, offset)
            if iscell(dims)
                out = MHyPro('State', 'project', obj.Handle, dims, offset);
            else
                error('MHyProState - wrong input argument.');
            end
        end
        
        function out = getDimension(obj, offset)
            out = MHyPro('State', 'getDimension', obj.Handle, offset);
        end
        
        function out = getDimensionOffset(obj, offset)
            out = MHyPro('State', 'getDimensionOffset', obj.Handle, offset);
        end   
        
    end
end