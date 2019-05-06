classdef MHyProLabel < handle

    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro(8, 1, obj.Handle);
        end
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProLabel(varargin)
            if nargin == 1
                if ischar(varargin{1})
                    % Construct new label
                    obj.Handle = MHyPro(8, 2, varargin{1});
                elseif isa(varargin{1}, 'MHyProLabel')
                    obj.Handle = MHyPro(8, 3, varargin{1}.Handle);
                elseif isa(varargin{1}, 'uint64')
                    obj.Handle = varargin{1};
                else
                    error('MHyProLabel - Constructor: Wrong type of at least one argument.');
                end           
            else
                error('MHyproFlow - Constructor: Wrong type of at leat one argument.');
            end
        end
        
        function out = getName(obj)
            out = MHyPro(8, 4, obj.Handle);
        end
        
        function setName(obj, name)
            if ischar(name)
                MHyPro(8, 5, obj.Handle, name);
            end
        end
        
        function out = eq(obj, rhs)
            if isa(rhs, 'MHyProLabel')
                out = MHyPro(8, 6, obj.Handle, rhs.Handle);
            end
        end
        
        function out = ne(obj, rhs)
            if isa(rhs, 'MHyProLabel')
                out = MHyPro(8, 7, obj.Handle, rhs.Handle);
            end
        end
        
        function out = lt(obj, rhs)
            if isa(rhs, 'MHyProLabel')
                out = MHyPro(8, 8, obj.Handle, rhs.Handle);
            end
        end
        
    end
end