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
                if isstring(varargin{1})
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
    end
end