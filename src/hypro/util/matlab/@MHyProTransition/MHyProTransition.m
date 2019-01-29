classdef MHyProTransition < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro('Transition', 'delete', obj.Handle);
        end
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProTransition(varargin)
            if nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.Handle = varargin{2};
                else
                    obj.Handle = MHyPro('Transition', varargin{1});
                end
            elseif nargin == 2
                if strcmp(varargin{1},'copy')
                    obj.Handle = MHyPro('Transition', varargin{1}, varargin{2}.Handle);
                else
                    obj.Handle = MHyPro('Transition', varargin{1}, varargin{2});
                end
            elseif nargin == 3
                obj.Handle = MHyPro('Transition', varargin{1}, varargin{2}, varargin{3});
            end
        end
    end
end