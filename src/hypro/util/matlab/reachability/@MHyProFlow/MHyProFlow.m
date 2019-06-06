classdef MHyProFlow < handle

    
    properties (SetAccess = public, GetAccess = public)
        Type
        ObjectHandle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro(obj.Type, 1, obj.ObjectHandle);
        end
        
    end
    
    methods (Access = public)
        
        function obj = MHyProFlow(varargin)
            if (varargin{1} == 9) || (varargin{1} == 10)
                obj.Type = varargin{1};
            else
                error('MHyProFlow - Constructor: Unknown type.');
            end 

            if nargin == 1
                if varargin{1} == 9 || varargin{1} == 10
                    % Call the constructor for empty flow
                    obj.ObjectHandle = MHyPro(varargin{1}, 2);
                else
                    error('MHyProFlow - Constructor: Wrong type of at least one argument.');
                end
            elseif nargin == 2
                if isa(varargin{2}, 'uint64')
                    % Call the copy constructor
                    obj.ObjectHandle = varargin{2};
                elseif isa(varargin{2}, 'MHyProFlow')
                    obj.ObjectHandle = MHyPro(varargin{2}.Type, 3, varargin{2}.ObjectHandle);    
                elseif varargin{1} == 9 && ismatrix(varargin{2})
                    % Call the matrix constructor for linear flow
                    obj.ObjectHandle = MHyPro(9, 4, varargin{2});
                else
                    error('MHyProFlow - Constructor: Wrong type of at least one argument.');
                end
            elseif nargin == 3
                if varargin{1} == 10 && ismatrix(varargin{2}) && isvector(varargin{3}) && size(varargin{2},2) == size(varargin{3},1)
                    % Call the matrix-vector constructor for affine flow
                    obj.ObjectHandle = MHyPro(10, 5 ,varargin{2}, varargin{3});
                else
                    error('MHyproFlow - Constructor: Wrong type of at least one argument.');
                end
            else
                error('MHyproFlow - Constructor: Wrong type of at leat one argument.');
            end
        end

        function out = type(obj)
            out = MHyPro(obj.Type, 6, obj.ObjectHandle);
        end
        
        function out = isTimed(obj)
            out = MHyPro(obj.Type, 7, obj.ObjectHandle);
        end
        
        function out = isDiscrete(obj)
            out = MHyPro(obj.Type, 8, obj.ObjectHandle);
        end
        
        function out = eq(lhs, rhs)
            if lhs.Type == rhs.Type
                out = MHyPro(lhs.Type, 9, lhs.ObjectHandle, rhs.ObjectHandle);
            else
                out = false;
                warning('MHyProFlow - eq: Different types of flows!');
            end
        end
        
        function out = ne(lhs, rhs)
            if lhs.Type ~= rhs.Type
                out = true;
                warning('MHyProFlow - neq: Different types of flows!');
            else
                out = MHyPro(lhs.Type, 10, lhs.ObjectHandle, rhs.ObjectHandle);
            end
        end
        
        function out = ostream(obj)
            out = MHyPro(obj.Type, 11, obj.ObjectHandle);
        end
        
        function out = size(obj)
            if obj.Type == 9
                out = MHyPro(9, 12, obj.ObjectHandle);
            else
                error('MHyProFlow - size: Wrong type of input argument.');
            end
        end
        
        function out = hasNoFlow(obj)
            if obj.Type == 9
                out = MHyPro(9, 13, obj.ObjectHandle);
            end
        end
        
        function out = getFlowMatrix(obj)
            if obj.Type == 9
                out = MHyPro(9, 14, obj.ObjectHandle);
            else
                error('MHyProFlow - getFlowMatrix: Wrong type of input argument.');
            end
        end
        
        function setFlowMatrix(obj, mat)
            if obj.Type == 9
                MHyPro(9, 15, obj.ObjectHandle, mat);
            else
                error('MHyProFlow - setFlowMatrix: Wrong type of input argument.');
            end
        end
        
        function addRow(obj, row)
            if obj.Type == 9 && isvector(row)
                MHyPro(9, 16, obj.ObjectHandle, row);
            else
                error('MHyProFlow - addRow: Wrong type of input argument(s).');
            end
        end
        
        function out = isIdentity(obj)
            if obj.Type == 9
                out = MHyPro(9, 17, obj.ObjectHandle);
            else
                error('MHyProFlow - isIdentity: Wrong type of input argument.');
            end
        end
        
        function out = hasTranslation(obj)
            if obj.Type == 10
                out = MHyPro(10, 18, obj.ObjectHandle);
            else
                error('MHyProFlow - hasTranslation: Wrong type of input argument.');
            end
        end
        
        
        function setTranslation(obj, tran)
            if obj.Type == 10 && isvector(tran)
                MHyPro(10, 19, obj.ObjectHandle, tran);
            else
                error('MHyProFlow - setTranslation: Wrong type of input argument(s).');
            end
        end
        
        function out = getTranslation(obj)
            if obj.Type == 10
                out = MHyPro(10, 20, obj.ObjectHandle);
            else
                error('MHyProFlow - getTranslation: Wrong type of input argument(s).');
            end
        end
        
        function out = dimension(obj)
            out = MHyPro(obj.Type, 21, obj.ObjectHandle);
        end
        
    end
end