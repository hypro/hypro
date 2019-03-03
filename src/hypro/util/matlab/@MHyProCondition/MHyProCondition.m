classdef MHyProCondition < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro('Condition', 'delete', obj.Handle);
        end
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProCondition(varargin)
            if nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.Handle = varargin{2};
                elseif isa(varargin{1}, 'MHyProCondition')
                    obj.Handle = MHyPro('Condition', 'copy', varargin{1}.Handle);
                elseif isa(varargin{1}, 'MHyProConstraintSet')
                    obj.Handle = MHyPro('Condition', 'new_constr_set', varargin{1}.Handle);
                else
                    error('MHyProCondition - Constructor: Wrong type of at least one argument.');
                end
            elseif nargin == 2
                if ismatrix(varargin{1}) && isvector(varargin{2}) && size(varargin{1},2) == size(varargin{2},1)
                    obj.Handle = MHyPro('Condition', 'new_mat_vec' ,varargin{1}, varargin{2});
                else
                    error('MHyProCondition - Constructor: Wrong type of at least one argument.');
                end
            else
                error('MHyProCondition - Constructor: Wrong type of at least one argument.');
            end
        end
        
        
        function out = size(obj)
            out = MHyPro('Condition', 'size', obj.Handle);
        end
        
        function out = isempty(obj)
            out = MHyPro('Condition', 'isempty', obj.Handle);
        end
        
        function out = getMatrix(obj)
            out = MHyPro('Condition', 'getMatrix', obj.Handle);
        end
        
        function out = getVector(obj)
            out = MHyPro('Condtion', 'getVector', obj.Handle);
        end
        
        function out = isAxisAligned(obj)
            out = MHyPro('Condtion', 'isAxisAligned', obj.Handle);
        end
        
        function out = isAxisAligned_at(obj, dim)
            if mod(dim, 1) == 0
                out = MHyPro('Condition', 'isAxisAligned_at', obj.Handle, dim);
            else
                error('MHyProCondition - isAxisAligned_at: Wrong type of at least one argument.');
            end
        end
        
        function setMatrix(obj, mat)
            if ismatrix(mat)
                MHyPro('Condition', 'setMatrix', obj.Handle, mat);
            else
                error('MHyProCondition - setMatrix: Wrong type of at least one argument.');
            end
        end
        
        function setVector(obj, vec)
            if isvector(vec)
                MHyPro('Condition', 'setVector', obj.Handle, vec);
            else
                error('MHyProCondition - setVector: Wrong type of at least one argument.');
            end
        end
        
        function out = constraints(obj)
            out = MHyPro('Condition', 'constraints', obj.Handle);
        end
        
        function out = hash(obj)
            out = MHyPro('Condition', 'hash', obj.Handle);
        end
        
        function out = getDotRepresentation(obj)
            out = MHyPro('Condition', 'getDotRepresentation', obj.Handle);
        end
        
        function out = decompose(obj)
            error('MHyProCondition - decompose: Not implemented.');
        end
        
        function out = eq(obj, rhs)
            if isa(rhs, 'MHyProCondition')
                out = MHyPro('Condition', 'equals', obj.Handle, rhs.Handle);
            else
                error('MHyProCondition - equals: Wrong type of at least one argument.');
            end
        end
        
        function out = ne(obj, rhs)
            if isa(rhs, 'MHyProCondition')
                out = MHyPro('Condition', 'unequals', obj.Handle, rhs.Handle);
            else
                error('MHyProCondition - unequals: Wrong type of at least one argument.');
            end
        end
       
        function out = combine(obj)
            error('MHyProCondition - combine: Not implemented.');
        end     
    end
end