classdef MHyProReset < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro('Reset', 'delete', obj.Handle);
        end
 
    end
    
    methods (Access = public)
        
        %Constructor
        function obj = MHyProReset(varargin)
            if nargin == 0
                % Call default constructor
                obj.Handle = MHyPro('Reset', 'new_empty');
            elseif nargin == 1
                if isa(varargin{1},'uint64')
                    obj.Handle = varargin{1};
                elseif isa(varargin{1}, 'MHyProReset')
                    obj.Handle = MHyPro('Reset', 'copy', varargin{1}.Handle);
                elseif ismatrix(varargin{1})
                    % Construct from intervals
                    obj.Handle = MHyPro('Reset', 'new_intervals');
                else
                    error('MHyProReset - Constructor: Wrong type of at least one argument.');
                end
            elseif nargin == 2
                if ismatrix(varargin{1}) && isvector(varargin{2})
                    % Construct from matrix and vector
                    obj.Handle = MHyPro('Label', 'new_mat_vec', varargin{1}, varargin{2});
                else
                    error('MHyProReset - Constructor: Wrong type of at least one argument.');
                end
            end
        end
        
        function out = isempty(obj)
            out = MHyPro('Reset', 'empty', obj.Handle);
        end
        
        function out = size(obj)
            out = MHyPro('Reset', 'size', obj.Handle);
        end
        
        function out = getVector(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at -1 >= 0
                out = MHyPro('Reset', 'getVector', obj.Handle, at - 1);
            else
                error('MHyProReset - getVector: Wrong type of at least one argument.');
            end
        end
        
        function out = getMatrix(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at -1 >= 0
                out = MHyPro('Reset', 'getMatrix', obj.Handle, at - 1);
            else
                error('MHyProReset - getIntervals: Wrong type of at least one argument.');
            end
        end
        
        function out = getIntervals(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at - 1 >= 0
                out = MHyPro('Reset', 'getIntervals', obj.Handle, at - 1);
            else
                error('MHyProReset - getIntervals: Wrong type of at least one argument.');
            end
        end
        
        function out = getAffineReset(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at - 1 >= 0
                ptr = MHyPro('Reset', 'getAffineReset_at', obj.Handle, at - 1);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProReset - getAffineReset: Wrong type of at least one argument.');
            end
        end
                
        function out = getAffineResetes(obj)
            ptrscell = MHyPro('Reset', 'getAffineResets', obj.Handle);
            out = cell(1, size(ptrscell, 2));
            for i = 1:size(ptrscell,2)
                ptr = ptrscell{i};
                out{i} = MHyProConstraintSet(ptr);
            end
        end
        
        function out = getIntervalReset(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at - 1 >= 0
                out = MHyPro('Reset', 'getIntervalReset_at', obj.Handle, at - 1);
            else
                error('MHyProReset - getIntervalReset: Wrong type of at least one argument.');
            end
        end
        
        function out = getIntervalResets(obj)
            out = MHyPro('Reset', 'getIntervalResets', obj.Handle);
        end
        
        function setVector(obj, vec, at)
            if isvector(vec) && mod(at,1) == 0 &&  at - 1 >= 0
                MHyPro('Reset', 'setVector', obj.Handle, vec, at - 1);
            else
                error("MHyProReset - setVector: Wrong type of at leat one argument.");
            end
        end
        
        function setMatrix(obj, mat, at)
            if ismatrix(mat) && mod(at,1) == 0 && at - 1 >= 0
                MHyPro('Reset', 'setMatrix', obj.Handle, mat, at - 1);
            else
                error("MHyProReset - setMatrix: Wrong type of at leat one argument.");
            end
        end
        
        function setIntervals(obj, ints, at)
            if areIntervals(ints) && mod(at,1) == 0 && at - 1 >= 0
                MHyPro('Reset', 'setIntervals', obj.Handle, ints, at - 1);
            else
                error("MHyProReset - areIntervals: Wrong type of at leat one argument.");
            end
        end
        
        function out = isIdentity(obj)
            out = MHyPro('Reset', 'isIdentity', obj.Handle);
        end
        
        function out = hash(obj)
            out = MHyPro('Reset', 'hash', obj.Handle);
        end
        
        function out = decompose(obj)
            %TODO
%             out = MHyPro('Reset', 'decompose', obj.Handle);
        end
        
        function out = combine(obj)
            %TODO
        end
  
    end   
end
        
