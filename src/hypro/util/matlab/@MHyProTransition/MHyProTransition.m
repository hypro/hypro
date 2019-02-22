classdef MHyProTransition < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro('Transition', 'delete', obj.Handle);
        end
        
        %Auxiliary functions
        function out = iscelloftype(cell, type)
            for i=(1:length(cell))
                elem = cell(i);
                if strcmp(elem.Type, type) == 0
                    out = 0;
                end
            end
            out = 1;
        end
    end
    
    methods (Access = public)
        
        %Constructor
         function obj = MHyProLocation(varargin)

            if nargin == 1
                % Call the constructor for empty flow
                obj.Handle = MHyPro('Transition', 'new_empty');
            elseif nargin == 2
                if isa(varargin{2}, 'uint64')
                    % Call the copy constructor
                    obj.Handle = MHyPro('Transition', 'copy', varargin{2});
                else
                    error('MHyProTransition - Constructor: Wrong type of at least one argument.');
                end
            elseif nargin == 3
                if isa(varargin{2}, "MHyProLocation") && isa(varargin{3}, "MHyProLocation")
                    % Call the source-target constructor
                    obj.Handle = MHyPro('Transition', 'new_source_target' ,varargin{2}, varargin{3});
                else
                    error('MHyproTransition - Constructor: Wrong type of at leat one argument.');
                end
            elseif nargin == 5
                if isa(varargin{2}, "MHyProLocation") && isa(varargin{3}, "MHyProLocation") && ...
                        isa(varargin{4}, "MHyProCondition") && isa(varargin{5}, "MHyProReset")
                    % Call the constructor for full transition
                    obj.Handle = MHyPro('Transition', 'new_full', varargin{2}, varargin{3},...
                        varargin{4}, varargin{5});
                else
                    error('MHyproTransition - Constructor: Wrong type of at leat one argument.');
                end
            else
                error('MHyproTransition - Constructor: Wrong type of at leat one argument.');
            end
         end
        
        function out = getTarget(obj)
            out = MHyPro('Transition', 'getTarget', obj.Handle);
        end
        
        function out = getSource(obj)
            out = MHyPro('Transition', 'getSource', obj.Handle);
        end
        
        function out = getGuard(obj)
            out = MHyPro('Transition', 'getGuard', obj.Handle);
        end
        
        function out = getReset(obj)
            out = MHyPro('Transition', 'getReset', obj.Handle);
        end
        
        function out = getAggregation(obj)
            %TODO
            out = MHyPro('Transition', 'getAggregation', obj.Handle);
        end
        
        function out = isUrgent(obj)
            out = MHyPro('Transition', 'isUrgent', obj.Handle);
        end
        
        function out = isTimeTriggered(obj)
            out = MHyPro('Transition', 'isTimeTriggered', obj.Handle);
        end
        
        function out = hasIdentityReset(obj)
            out = MHyPro('Transition', 'hasIdentityReset', obj.Handle);
        end
        
        function out = getLabels(obj)
            out = MHyPro('Transition', 'getLabels', obj.Handle);
        end
        
        function out = hash(obj)
            out = MHyPro('Transition', 'hash', obj.Handle);
        end
        
        function setSource(obj, loc)
            if isa(loc, 'MHyProLocation') 
                MHyPro('Transition', 'setSource', obj.Handle, loc);
            else
                error("MHyProTransition - setSource: Wrong type of at leat one argument.");
            end
        end
        
        function setTarget(obj, loc)
            if isa(loc, 'MHyProLocation') 
                MHyPro('Transition', 'setTarget', obj.Handle, loc);
            else
                error("MHyProTransition - setTarget: Wrong type of at leat one argument.");
            end
        end
        
        function setGuard(obj, loc)
            if isa(loc, 'MHyProCondition') 
                MHyPro('Transition', 'setGuard', obj.Handle, loc);
            else
                error("MHyProTransition - setGuard: Wrong type of at leat one argument.");
            end
        end
        
        function setReset(obj, res)
            if isa(res, 'MHyProReset') 
                MHyPro('Transition', 'setReset', obj.Handle, res);
            else
                error("MHyProTransition - setReset: Wrong type of at leat one argument.");
            end
        end
        
        function setAggregation(obj, agg)
            %TODO
%             if iscelloftype(loc, 'MHyProLocation') 
%                 MHyPro('Transition', 'setSource', obj.Handle, loc);
%             else
%                 error("MHyProTransition - setSource: Wrong type of at leat one argument.");
%             end
        end
        
        function setUrgent(obj, urg)
            if urg == 1 || urg == 0 
                MHyPro('Transition', 'setUrgent', obj.Handle, urg);
            else
                error("MHyProTransition - setUrgent: Wrong type of at leat one argument.");
            end
        end
        
        function setTriggerTime(obj, time)
            if isdouble(time) 
                MHyPro('Transition', 'setTriggerTime', obj.Handle, time);
            else
                error("MHyProTransition - setTriggerTime: Wrong type of at leat one argument.");
            end
        end
        
        function setLabels(obj, labs)
            if iscelloftype(labs, 'MHyProLabels') 
                MHyPro('Transition', 'setSource', obj.Handle, loc);
            else
                error("MHyProTransition - setLabels: Wrong type of at leat one argument.");
            end
        end
        
        function addLabel(obj, lab)
            if isa(lab, 'MHyProLabel') 
                MHyPro('Transition', 'addLabel', obj.Handle, lab);
            else
                error("MHyProTransition - addLabel: Wrong type of at leat one argument.");
            end
        end
        
        function out = getDotRepresentation(obj, vars)
            if isstring(vars) 
                out = MHyPro('Transition', 'getDotRepresentation', obj.Handle, vars);
            else
                error("MHyProTransition - getDotRepresentation: Wrong type of at leat one argument.");
            end
        end
        
        function out = isComposedOf(obj, loc)
            %TODO
%             if iscelloftype(loc, 'MHyProLocation') 
%                 MHyPro('Transition', 'setSource', obj.Handle, loc);
%             else
%                 error("MHyProTransition - setSource: Wrong type of at leat one argument.");
%             end
        end
        
        function decompose
            %TODO
        end
        
        function eq(obj, rhs)
            if isa(rhs, 'MHyProTransition') 
                MHyPro('Transition', 'equals', obj.Handle, rhs.Handle);
            else
                error("MHyProTransition - equals: Wrong type of at leat one argument.");
            end
        end
        
        function ne(obj, rhs)
            if isa(rhs, 'MHyProTransition') 
                MHyPro('Transition', 'unequals', obj.Handle, rhs.Handle);
            else
                error("MHyProTransition - equals: Wrong type of at leat one argument.");
            end
        end
        
    end
end