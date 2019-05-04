classdef MHyProReset < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro(11, 'delete', obj.Handle);
        end
 
    end
    
    methods (Access = public)
        
        %Constructor
        function obj = MHyProReset(varargin)
            if nargin == 0
                % Call default constructor
                obj.Handle = MHyPro(11, 'new_empty');
            elseif nargin == 1
                if isa(varargin{1},'uint64')
                    obj.Handle = varargin{1};
                elseif isa(varargin{1}, 'MHyProReset')
                    obj.Handle = MHyPro(11, 'copy', varargin{1}.Handle);
                elseif ismatrix(varargin{1})
                    % Construct from intervals
                    obj.Handle = MHyPro(11, 'new_intervals');
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
            out = MHyPro(11, 'empty', obj.Handle);
        end
        
        function out = size(obj)
            out = MHyPro(11, 'size', obj.Handle);
        end
        
        function out = getVector(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at -1 >= 0
                out = MHyPro(11, 'getVector', obj.Handle, at - 1);
            else
                error('MHyProReset - getVector: Wrong type of at least one argument.');
            end
        end
        
        function out = getMatrix(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at -1 >= 0
                out = MHyPro(11, 'getMatrix', obj.Handle, at - 1);
            else
                error('MHyProReset - getIntervals: Wrong type of at least one argument.');
            end
        end
        
        function out = getIntervals(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at - 1 >= 0
                out = MHyPro(11, 'getIntervals', obj.Handle, at - 1);
            else
                error('MHyProReset - getIntervals: Wrong type of at least one argument.');
            end
        end
        
        function out = getAffineReset(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at - 1 >= 0
                ptr = MHyPro(11, 'getAffineReset_at', obj.Handle, at - 1);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProReset - getAffineReset: Wrong type of at least one argument.');
            end
        end
                
        function out = getAffineResetes(obj)
            ptrscell = MHyPro(11, 'getAffineResets', obj.Handle);
            out = cell(1, size(ptrscell, 2));
            for i = 1:size(ptrscell,2)
                ptr = ptrscell{i};
                out{i} = MHyProConstraintSet(ptr);
            end
        end
        
        function out = getIntervalReset(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at - 1 >= 0
                out = MHyPro(11, 'getIntervalReset_at', obj.Handle, at - 1);
            else
                error('MHyProReset - getIntervalReset: Wrong type of at least one argument.');
            end
        end
        
        function out = getIntervalResets(obj)
            out = MHyPro(11, 'getIntervalResets', obj.Handle);
        end
        
        function setVector(varargin)
            if isa(varargin{1}, 'MHyProReset')
                if nargin == 2 && isvector(varargin{2})
                    MHyPro(11, 'setVector', varargin{1}.Handle, varargin{2}, 0);
                elseif nargin == 3 && isvector(varargin{2}) && mod(varargin{3},1) == 0
                    MHyPro(11, 'setVector', varargin{1}.Handle, varargin{2}, varargin{3} - 1);
                else
                    error('MHyProReset - setVector: Wrong type of at least one argument.');
                end
            else
                error('MHyProReset - setVector: The first argument must be a MHyProReset.');
            end
        end

         function setMatrix(varargin)
            if isa(varargin{1}, 'MHyProReset')
                if nargin == 2 && ismatrix(varargin{2})
                    MHyPro(11, 'setMatrix', varargin{1}.Handle, varargin{2}, 0);
                elseif nargin == 3 && ismatrix(varargin{2}) && mod(varargin{3},1) == 0
                    MHyPro(11, 'setMatrix', varargin{1}.Handle, varargin{2}, varargin{3} - 1);
                else
                    error('MHyProReset - setMatrix: Wrong type of at least one argument.');
                end
            else
                error('MHyProReset - setMatrix: The first argument must be a MHyProReset.');
            end
        end

        function setIntervals(varargin)
            if isa(varargin{1}, 'MHyProReset')
                if nargin == 2 && areIntervals(varargin{2})
                    MHyPro(11, 'setIntervals', varargin{1}.Handle, varargin{2}, 0);
                elseif nargin == 3 && areIntervals(varargin{2}) && mod(varargin{3},1) == 0
                    MHyPro(11, 'setIntervals', varargin{1}.Handle, varargin{2}, varargin{3} - 1);
                else
                    error('MHyProReset - setIntervals: Wrong type of at least one argument.');
                end
            else
                error('MHyProReset - setIntervals: The first argument must be a MHyProReset.');
            end
        end
        
        function out = isIdentity(obj)
            out = MHyPro(11, 'isIdentity', obj.Handle);
        end
        
        function out = hash(obj)
            out = MHyPro(11, 'hash', obj.Handle);
        end
        
        function out = decompose(obj)
            %TODO
%             out = MHyPro(11, 'decompose', obj.Handle);
        end
        
        function out = combine(obj)
            %TODO
        end
  
    end   
end
        
