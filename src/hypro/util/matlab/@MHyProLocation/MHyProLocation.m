classdef MHyProLocation < handle
    
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
         function obj = MHyProLocation(varargin)
            if nargin == 0
                % Call the constructor for empty flow
                obj.Handle = MHyPro('Location', 'new_empty');
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.Handle = varargin{1};
                elseif isa(varargin{1}, 'MHyProLocation')
                    obj.Handle = MHyPro('Location', 'copy', varargin{1}.Handle);
                elseif ismatrix(varargin{1})
                    % Call the matrix constructor
                    obj.Handle = MHyPro('Location', 'new_mat', varargin{1});
                else
                    error('MHyProLocation - Constructor: Wrong type of at least one argument.');
                end
            elseif nargin == 3
                if ismatrix(varargin{1}) && iscell(varargin{2}) && isa(varargin{3}, 'MHyProCondition')
                    objects = cell(1, size(varargin{2}, 2));
                    for i = 1:length(varargin{2})
                        if isa(varargin{2}{i}, 'MHyProTransition')
                            objects{i} = varargin{2}{i}.Handle;
                        else
                            error('MHyProBox - unite: Wrong type of input argument.');
                        end
                    end
                    % Call the matrix-vector constructor for affine flow
                    obj.Handle = MHyPro('Location', 'new_mat_tran_inv' ,varargin{1}, objects, varargin{3}.Handle);
                else
                    error('MHyProLocation - Constructor: Wrong type of at least one argument.');
                end
            else
                error('MHyProLocation - Constructor: Wrong type of at least one argument.');
            end
         end
        
        function out = getNumberFlow(obj)
            out = MHyPro('Location', 'getNumberFlow', obj.Handle);
        end
        
        function out = getLinearFlow(obj)
            ptr = MHyPro('Location', 'getLinearFlow', obj.Handle);
            out = MHyProFlow('linearFlow', ptr);
        end
        
        function out = getInvariant(obj)
            ptr = MHyPro('Location', 'getInvariant', obj.Handle);
            out = MHyProCondition(ptr);
        end
        
        function out = getTransitions(obj)
            ptrscell = MHyPro('Location', 'getTransitions', obj.Handle);
            out = cell(1, size(ptrscell,2));
            for i = 1:size(ptrscell,2)
                ptr = ptrscell{i};
                out{i} = MHyProTransition(ptr);
            end
        end
        
        function out = getExternalInput(obj)
            if obj.hasExternalInput()
                out = MHyPro('Location', 'getExternalInput', obj.Handle);
            else
                error('MHyProLocation - getExternalInput: Object has no external input.');
            end
        end
        
        function out = hasExternalInput(obj)
            out = MHyPro('Location', 'hasExternalInput', obj.Handle);
        end
        
        function out = hash(obj)
            out = MHyPro('Location', 'hash', obj.Handle);
        end
        
        function out = getName(obj)
            out = MHyPro('Location', 'getName', obj.Handle);
        end
        
        function out = dimension(obj)
            out = MHyPro('Location', 'dimension', obj.Handle);
        end
        
        function out = dimension_at(obj, pos)
            if mod(pos,1) == 0
                out = MHyPro('Location', 'dimension_at', obj.Handle, pos);
            else
                error("MHyProLocation - dimension_at: Wrong type of at leat one argument. Note: strings in MATLAB have to be written in "".");
            end
        end
        
        function setName(obj, name)
            if ischar(name)
                MHyPro('Location', 'setName', obj.Handle, name);
            else
                error("MHyProLocation - setName: Wrong type of at leat one argument. Note: strings in MATLAB have to be written in "".");
            end
        end
        
        function setFlow(obj, mat)
            if ismatrix(mat)
                MHyPro('Location', 'setFlow', obj.Handle, mat);
            else
                error("MHyProLocation - setFlow: Wrong type of at leat one argument.");
            end
        end
        
        function setLinearFlow(obj, linFlow, pos)
            if isa(linFlow, "MHyProFlow") && strcmp(linFlow.Type, "linearFlow") && mod(pos,1) == 0
                MHyPro('Location', 'setLinearFlow', obj.Handle, linFlow.Handle, pos - 1);
            else
                error("MHyProLocation - setLinearFlow: Wrong type of at leat one argument.");
            end
        end
        
        function setLinearFlows(obj, linFlows)
            if iscelloftype(linFlows, 'linearFlow') 
                MHyPro('Location', 'setLinearFlows', obj.Handle, linFlows);
            else
                error("MHyProLocation - setLinearFlows: Wrong type of at leat one argument.");
            end
        end
           
        function setInvariant(obj, cond)
            if isa(cond, 'MHyProCondition') 
                MHyPro('Location', 'setInvariant', obj.Handle, cond.Handle);
            else
                error("MHyProLocation - setInvariant: Wrong type of at leat one argument.");
            end
        end
        
        function setExtInput(obj, ints)
            if areIntervals(ints)
                MHyPro('Location', 'setExtInput', obj.Handle, ints);
            else
                error("MHyProLocation - setExtInput: Wrong type of at leat one argument.");
            end
        end
        
        function out = isComposedOf(obj)
            %TODO
            out = 0;
        end
        
        function out = getDotRepresentation(obj, vars)
            if isstring(vars)
                out = MHyPro('Location', 'getDotRepresentation', obj.Handle, vars);
            else
                error("MHyProLocation - getDotRepresentation: Wrong type of at leat one argument.");
            end
        end
        
        function out = decompose(obj)
            %TODO
        end
        
        function out = lt(obj, rhs)
            if isa(rhs, "MHyProLocation")
                out = MHyPro('Location', 'less', obj.Handle, rhs.Handle);
            else
                error("MHyProLocation - less: Wrong type of at leat one argument.");
            end
        end
        
        function out = eq(obj, rhs)
            if isa(rhs, "MHyProLocation")
                out = MHyPro('Location', 'equals', obj.Handle, rhs.Handle);
            else
                error("MHyProLocation - equals: Wrong type of at leat one argument.");
            end
        end
        
        function out = ne(obj, rhs)
            if isa(rhs, "MHyProLocation")
                out = MHyPro('Location', 'unequals', obj.Handle, rhs.Handle);
            else
                error("MHyProLocation - unequals: Wrong type of at leat one argument.");
            end
        end
        
    end
end