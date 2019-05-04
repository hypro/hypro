classdef MHyProState < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro(13, 'delete', obj.Handle);
        end
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProState(varargin)
            if nargin == 0
                obj.Handle = MHyPro(13, 'new_empty');
            elseif nargin == 1 && isa(varargin{1}, 'uint64')
                obj.Handle = varargin{1};
            elseif nargin == 1 && isa(varargin{1}, 'MHyProState')
                obj.Handle = MHyPro(13, 'copy', varargin{1}.Handle);
            elseif nargin == 1 && isa(varargin{1}, 'MHyProLocation')
                obj.Handle = MHyPro(13, 'new_loc', varargin{1}.Handle);
            else
                error('MState - Constructor: Wrong type of at least one argument.');
            end
        end
        
        
        function out = getSetType(obj)
            out = MHyPro(13, 'getSetType', obj.Handle);
        end
        
        function out = getSets(obj)
            stateCell = MHyPro(13, 'getSets', obj.Handle);
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
            out = MHyPro(13, 'getTimestamp', obj.Handle);
        end
        
        function out = isempty(obj)
            out = MHyPro(13, 'isEmpty', obj.Handle);
        end
        
        function out = vertices(obj, offset)
            out = MHyPro(13, 'vertices', obj.Handle, offset-1);
        end
        
        function out = project(obj, dims, offset)
            if iscell(dims)
                out = MHyPro(13, 'project', obj.Handle, dims, offset);
            else
                error('MHyProState - wrong input argument.');
            end
        end
        
        function out = getDimension(obj, offset)
            out = MHyPro(13, 'getDimension', obj.Handle, offset);
        end
        
        function out = getDimensionOffset(obj, offset)
            out = MHyPro(13, 'getDimensionOffset', obj.Handle, offset);
        end   
        
        function out = getLocation(obj)
            temp = MHyPro(13, 'getLocation', obj.Handle);
            out = MHyProLocation(temp);
        end
        
        function out = getNumberSets(obj)
            out = MHyPro(13, 'getNumberSets', obj.Handle);
        end
        
        function out = getSet(obj, pos)
            temp = MHyPro(13, 'getSet', obj.Handle, pos - 1);
            out = MHyProState(temp);
        end
        
        function out = getTypes(obj)
            temp = MHyPro(13, 'getSet', obj.Handle);
            out = cell(1, length(temp));
            for i = 1:length(temp)
                if isa(temp{i}, 'uint64')
                    out{i} = MHyProState(temp{i});
                else
                    error('MHyProState - getTypes: Wrong type of input argument.');
                end
            end
        end
        
        function setLocation(obj, loc)
            if isa(loc, 'MHyProLocation')
                MHyPro(13, 'setLocation', obj.Handle, loc.Handle);
            else
                error('MHyProState - setLocation: Wrong type of input argument.');
            end
        end
        
        % type = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        % 0 = box, 1 = carl_polytope, 2 = constraint_set
        % 3 = difference_bounds, 4 = polytope_h, 5 = polytope_v
        % 6 = ppl_polytope, 7 = support_function, 8 = taylor_model
        % 9 = zonotope
        function setSetType(obj, type, pos)
            if type >= 0 && type <= 9 && mod(pos, 1) == 0
                MHyPro(13, 'setSetType', type, pos - 1);
            else
                error('MHyProState - setSetType: Wrong type of input argument.');
            end      
        end
        
        
        
    end
end