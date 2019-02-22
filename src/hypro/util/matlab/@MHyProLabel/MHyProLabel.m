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
            if nargin == 1 &&
                % Call the constructor for empty flow
                obj.Handle = MHyPro(varargin{1}, 'new_empty');
            elseif nargin == 2
                if isa(varargin{2}, 'uint64')
                    % Call the copy constructor
                    obj.Handle = MHyPro(varargin{1}, 'copy', varargin{2});
                elseif strcmp(varargin{1}, 'linearFlow') && ismatrix(varargin{2})
                    % Call the matrix constructor for linear flow
                    obj.Handle = MHyPro('linearFlow', 'new_mat', varargin{2});
                else
                    error('MHyProFlow - Constructor: Wrong type of at least one argument.');
                end
            elseif nargin == 3
                if strcmp(varargin{1}, 'affineFlow') && ismatrix(varargin{2}) && isvector(varargin{3})
                    % Call the matrix-vector constructor for affine flow
                    obj.Handle = MHyPro('affineFlow', 'new_mat_vec' ,varargin{2}, varargin{3});
                else
                    error('MHyproFlow - Constructor: Wrong type of at leat one argument.');
                end
            else
                error('MHyproFlow - Constructor: Wrong type of at leat one argument.');
            end
        end
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        function obj = MHyProLabel(varargin)
            if nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.Handle = varargin{2};
                else
                    obj.Handle = MHyPro('Label', varargin{1});
                end
            elseif nargin == 2
                if strcmp(varargin{1},'copy')
                    obj.Handle = MHyPro('Label', varargin{1}, varargin{2}.Handle);
                else
                    obj.Handle = MHyPro('Label', varargin{1}, varargin{2});
                end
            elseif nargin == 3
                obj.Handle = MHyPro('Label', varargin{1}, varargin{2}, varargin{3});
            end
        end
    end
end