classdef MHyProLabel < handle

    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro('Label', 'delete', obj.Handle);
        end
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProLabel(varargin)
            if nargin == 1
                if ischar(varargin{1})
                    % Construct new label
                    obj.Handle = MHyPro('Label','new_name', varargin{1});
                elseif isa(varargin{1}, 'MHyProLabel')
                    obj.Handle = MHyPro('Label', 'copy', varargin{1}.Handle);
                else
                    error('MHyProLabel - Constructor: Wrong type of at least one argument.');
                end           
            else
                error('MHyproFlow - Constructor: Wrong type of at leat one argument.');
            end
        end
        
        function out = getName(obj)
            out = MHyPro('Label', 'getName', obj.Handle);
        end
        
        function setName(obj, name)
            if ischar(name)
                MHyPro('Label', 'setName', obj.Handle, name);
            end
        end
        
        function out = eq(obj, rhs)
            if isa(rhs, 'MHyProLabel')
                out = MHyPro('Label', 'equals', obj.Handle, rhs.Handle);
            end
        end
        
        function out = ne(obj, rhs)
            if isa(rhs, 'MHyProLabel')
                out = MHyPro('Label', 'unequals', obj.Handle, rhs.Handle);
            end
        end
        
        function out = lt(obj, rhs)
            if isa(rhs, 'MHyProLabel')
                out = MHyPro('Label', 'less', obj.Handle, rhs.Handle);
            end
        end
        
    end
end