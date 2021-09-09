classdef MHyProLabel < handle

    properties (SetAccess = public, GetAccess = public)
        ObjectHandle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro(8, 1, obj.ObjectHandle);
        end
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProLabel(varargin)
            if nargin == 1
                if ischar(varargin{1})
                    % Construct new label
                    obj.ObjectHandle = MHyPro(8, 2, varargin{1});
                elseif isa(varargin{1}, 'MHyProLabel')
                    obj.ObjectHandle = MHyPro(8, 3, varargin{1}.ObjectHandle);
                elseif isa(varargin{1}, 'uint64')
                    obj.ObjectHandle = varargin{1};
                else
                    error('MHyProLabel - Constructor: Wrong type of at least one argument.');
                end           
            else
                error('MHyproFlow - Constructor: Wrong type of at leat one argument.');
            end
        end
        
        function out = getName(obj)
            out = MHyPro(8, 4, obj.ObjectHandle);
        end
        
        function setName(obj, name)
            if ischar(name)
                MHyPro(8, 5, obj.ObjectHandle, name);
            end
        end
        
        function out = eq(obj, rhs)
            if isa(rhs, 'MHyProLabel')
                out = MHyPro(8, 6, obj.ObjectHandle, rhs.ObjectHandle);
            end
        end
        
        function out = ne(obj, rhs)
            if isa(rhs, 'MHyProLabel')
                out = MHyPro(8, 7, obj.ObjectHandle, rhs.ObjectHandle);
            end
        end
        
        function out = lt(obj, rhs)
            if isa(rhs, 'MHyProLabel')
                out = MHyPro(8, 8, obj.ObjectHandle, rhs.ObjectHandle);
            end
        end
        
    end
end