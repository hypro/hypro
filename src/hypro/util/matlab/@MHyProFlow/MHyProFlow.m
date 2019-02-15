classdef MHyProFlow < handle
    
    properties (SetAccess = public, GetAccess = public)
        Type
        Handle
    end
    
    methods (Access = private)
        
    % Destructor
    function delete(obj)
            MHyPro(obj.Type, 'delete', obj.Handle);
        end
    end
    
    methods (Access = public)
        
        function obj = MHyProFlow(varargin)
            if strcmp(varargin{1},'linearFlow') || strcmp(varargin{1},'affineFlow')
                obj.Type = varargin{1};
            else
                error('MHyProFlow - Constructor: Unknown type.');
            end 

            if nargin == 1
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

        function out = type(obj)
            out = MHyPro(obj.Type, 'type', obj.Handle);
        end
        
        function out = isTimed(obj)
            out = MHyPro(obj.Type, 'isTimed', obj.Handle);
        end
        
        function out = isDiscrete(obj)
            out = MHyPro(obj.Type, 'isDiscrete', obj.Handle);
        end
        
        function out = eq(lhs, rhs)
            if strcmp(lhs.Type, rhs.Type)
                out = MHyPro(lhs.Type, '==', lhs.Handle, rhs.Handle);
            else
                out = false;
                warning('MHyProFlow - eq: Different types of flows!');
            end
        end
        
        function out = neq(lhs, rhs)
            if strcmp(lhs.Type, rhs.Type) == 0
                out = true;
                warning('MHyProFlow - neq: Different types of flows!');
            else
                out = MHyPro(lhs.Type, '!=', lhs.Handle, rhs.Handle);
            end
        end
        
        function out = outstream(obj)
            out = MHyPro(obj.Type, 'outstream', obj.Handle);
        end
        
        function out = size(obj)
            if strcmp(obj.Type,'linearFlow')
                out = MHyPro('linearFlow', 'size', obj.Handle);
            else
                error('MHyProFlow - size: Wrong type of input argument.');
            end
        end
        
        function out = hasNoFlow(obj)
            if strcmp(obj.Type, 'linearFlow')
                out = MHyPro('linearFlow', 'hasNoFlow', obj.Handle);
            end
        end
        
        function out = getFlowMatrix(obj)
            if strcmp(obj.Type, 'linearFlow')
                out = MHyPro('linearFlow', 'getFlowMatrix', obj.Handle);
            else
                error('MHyProFlow - getFlowMatrix: Wrong type of input argument.');
            end
        end
        
        function out = setFlowMatrix(obj)
            if strcmp(obj.Type, 'linearFlow')
                out = MHyPro('linearFlow', 'setFlowMatrix', obj.Handle);
            else
                error('MHyProFlow - setFlowMatrix: Wrong type of input argument.');
            end
        end
        
        function addRow(obj, row)
            if strcmp(obj.Type, 'linearFlow') && isvector(row)
                MHyPro('linearFlow', 'addRow', obj.Handle, row);
            else
                error('MHyProFlow - addRow: Wrong type of input argument(s).');
            end
        end
        
        function out = isIdentity(obj)
            if strcmp(obj.Type, 'linearFlow')
                out = MHyPro('linearFlow', 'isIdentity', obj.Handle);
            else
                error('MHyProFlow - isIdentity: Wrong type of input argument.');
            end
        end
        
        function out = hasTranslation(obj)
            if strcmp(obj.Type, 'affineFlow')
                out = MHyPro('affineFlow', 'hasTranslation', obj.Handle);
            else
                error('MHyProFlow - hasTranslation: Wrong type of input argument.');
            end
        end
        
        
        function setTranslation(obj, tran)
            if strcmp(obj.Type, 'affineFlow') && isvector(tran)
                MHyPro('affineFlow', 'setTranslation', obj.Handle, tran);
            else
                error('MHyProFlow - setTranslation: Wrong type of input argument(s).');
            end
        end
        
        function out = getTranslation(obj)
            if strcmp(obj.Type, 'affineFlow')
                out = MHyPro('affineFlow', 'getTranslation', obj.Handle);
            else
                error('MHyProFlow - getTranslation: Wrong type of input argument(s).');
            end
        end
        
    end
end