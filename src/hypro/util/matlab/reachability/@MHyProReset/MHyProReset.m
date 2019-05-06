classdef MHyProReset < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro(11, 1, obj.Handle);
        end
 
    end
    
    methods (Access = public)
        
        %Constructor
        function obj = MHyProReset(varargin)
            if nargin == 0
                % Call default constructor
                obj.Handle = MHyPro(11, 2);
            elseif nargin == 1
                if isa(varargin{1},'uint64')
                    obj.Handle = varargin{1};
                elseif isa(varargin{1}, 'MHyProReset')
                    obj.Handle = MHyPro(11, 3, varargin{1}.Handle);
                elseif ismatrix(varargin{1})
                    % Construct from intervals
                    obj.Handle = MHyPro(11, 4, varargin{1});
                else
                    error('MHyProReset - Constructor: Wrong type of at least one argument.');
                end
            elseif nargin == 2
                if ismatrix(varargin{1}) && isvector(varargin{2})
                    % Construct from matrix and vector
                    obj.Handle = MHyPro('Label', 5, varargin{1}, varargin{2});
                else
                    error('MHyProReset - Constructor: Wrong type of at least one argument.');
                end
            end
        end
        
        function out = isempty(obj)
            out = MHyPro(11, 6, obj.Handle);
        end
        
        function out = size(obj)
            out = MHyPro(11, 7, obj.Handle);
        end
        
        function out = getVector(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at -1 >= 0
                out = MHyPro(11, 8, obj.Handle, at - 1);
            else
                error('MHyProReset - getVector: Wrong type of at least one argument.');
            end
        end
        
        function out = getMatrix(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at -1 >= 0
                out = MHyPro(11, 9, obj.Handle, at - 1);
            else
                error('MHyProReset - getIntervals: Wrong type of at least one argument.');
            end
        end
        
        function out = getIntervals(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at - 1 >= 0
                out = MHyPro(11, 10, obj.Handle, at - 1);
            else
                error('MHyProReset - getIntervals: Wrong type of at least one argument.');
            end
        end
        
        function out = getAffineReset(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at - 1 >= 0
                ptr = MHyPro(11, 11, obj.Handle, at - 1);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProReset - getAffineReset: Wrong type of at least one argument.');
            end
        end
                
        function out = getAffineResets(obj)
            ptrscell = MHyPro(11, 12, obj.Handle);
            out = cell(1, size(ptrscell, 2));
            for i = 1:size(ptrscell,2)
                ptr = ptrscell{i};
                out{i} = MHyProConstraintSet(ptr);
            end
        end
        
        function out = getIntervalReset(obj, at)
            if mod(at, 1) == 0 && at <= obj.size() && at - 1 >= 0
                out = MHyPro(11, 13, obj.Handle, at - 1);
            else
                error('MHyProReset - getIntervalReset: Wrong type of at least one argument.');
            end
        end
        
        function out = getIntervalResets(obj)
            out = MHyPro(11, 14, obj.Handle);
        end
        
        function setVector(varargin)
            if isa(varargin{1}, 'MHyProReset')
                if nargin == 2 && isvector(varargin{2})
                    MHyPro(11, 15, varargin{1}.Handle, varargin{2}, 0);
                elseif nargin == 3 && isvector(varargin{2}) && mod(varargin{3},1) == 0
                    MHyPro(11, 15, varargin{1}.Handle, varargin{2}, varargin{3} - 1);
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
                    MHyPro(11, 16, varargin{1}.Handle, varargin{2}, 0);
                elseif nargin == 3 && ismatrix(varargin{2}) && mod(varargin{3},1) == 0
                    MHyPro(11, 16, varargin{1}.Handle, varargin{2}, varargin{3} - 1);
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
                    MHyPro(11, 17, varargin{1}.Handle, varargin{2}, 0);
                elseif nargin == 3 && areIntervals(varargin{2}) && mod(varargin{3},1) == 0
                    MHyPro(11, 17, varargin{1}.Handle, varargin{2}, varargin{3} - 1);
                else
                    error('MHyProReset - setIntervals: Wrong type of at least one argument.');
                end
            else
                error('MHyProReset - setIntervals: The first argument must be a MHyProReset.');
            end
        end
        
        function out = isIdentity(obj)
            out = MHyPro(11, 18, obj.Handle);
        end
        
        function out = hash(obj)
            out = MHyPro(11, 19, obj.Handle);
        end
        
        function out = decompose(obj)
            %TODO
%             out = MHyPro(11, 20, obj.Handle);
        end
        
        function out = combine(obj)
            %TODO 21
        end
  
    end   
end
        
