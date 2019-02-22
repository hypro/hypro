classdef MHyProReset < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro('Location', 'delete', obj.Handle);
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
                    obj.Handle = MHyPro('Reset', 'copy', varargin{2});
                elseif isa(varargin{1}, 'MHyProReset')
                    obj.Handle = MHyPro('Reset', 'copy', varargin{2}.Handle);
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
        
        function out = empty(obj)
            out = MHyPro('Reset', 'empty', obj.Handle);
        end
        
        function out = size(obj)
            out = MHyPro('Reset', 'size', obj.Handle);
        end
        
        function out = getVector(obj)
            out = MHyPro('Reset', 'getVector', obj.Handle);
        end
        
        function out = getMatrix(obj)
            out = MHyPro('Reset', 'getMatrix', obj.Handle);
        end
        
        function out = getIntervals(obj)
            out = MHyPro('Reset', 'getIntervals', obj.Handle);
        end
        
        function out = getAffineReset(obj)
            out = MHyPro('Reset', 'getAffineReset', obj.Handle);
        end
        
        function out = getAffineResetes(obj)
            out = MHyPro('Reset', 'getAffineResets', obj.Handle);
        end
        
        function out = getIntervalReset(obj)
            out = MHyPro('Reset', 'getIntervalReset', obj.Handle);
        end
        
        function out = getIntervalResets(obj)
            out = MHyPro('Reset', 'getIntervalResets', obj.Handle);
        end
        
        function out = setVector(obj, vec)
            if isvector(vec)
                out = MHyPro('Reset', 'setVector', obj.Handle, vec);
            else
                error("MHyProReset - setVector: Wrong type of at leat one argument.");
            end
        end
        
        function out = setMatrix(obj, mat)
            if ismatrix(mat)
                out = MHyPro('Reset', 'setMatrix', obj.Handle, mat);
            else
                error("MHyProReset - setMatrix: Wrong type of at leat one argument.");
            end
        end
        
        function out = setIntervals(obj, ints)
            if areIntervals(ints)
                out = MHyPro('Reset', 'setIntervals', obj.Handle, ints);
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
        
