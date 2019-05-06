classdef MHyProTransition < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro(7, 1, obj.Handle);
        end
    end
    
    methods (Access = public)
        
        %Constructor
         function obj = MHyProTransition(varargin)

            if nargin == 0
                % Call the constructor for empty flow
                obj.Handle = MHyPro(7, 2);
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    % Call the copy constructor
                    obj.Handle = varargin{1};
                elseif isa(varargin{1}, 'MHyProTransition')
                    obj.Handle = MHyPro(7, 3, varargin{1}.Handle);
                else
                    error('MHyProTransition - Constructor: Wrong type of at least one argument.');
                end
            elseif nargin == 2
                if isa(varargin{1}, 'MHyProLocation') && isa(varargin{2}, 'MHyProLocation')
                    % Call the source-target constructor
                    obj.Handle = MHyPro(7, 4 ,varargin{1}.Handle, varargin{2}.Handle);
                else
                    error('MHyproTransition - Constructor: Wrong type of at leat one argument.');
                end
            elseif nargin == 4
                if isa(varargin{1}, 'MHyProLocation') && isa(varargin{2}, 'MHyProLocation') && ...
                        isa(varargin{3}, 'MHyProCondition') && isa(varargin{4}, 'MHyProReset')
                    % Call the constructor for full transition
                    obj.Handle = MHyPro(7, 5, varargin{1}.Handle, varargin{2}.Handle,...
                        varargin{3}.Handle, varargin{4}.Handle);
                else
                    error('MHyproTransition - Constructor: Wrong type of at leat one argument.');
                end
            else
                error('MHyproTransition - Constructor: Wrong type of at leat one argument.');
            end
         end
        
        function out = getTarget(obj)
            ptr = MHyPro(7, 6, obj.Handle);
            out = MHyProLocation(ptr);
        end
        
        function out = getSource(obj)
            ptr = MHyPro(7, 7, obj.Handle);
            out = MHyProLocation(ptr);
        end
        
        function out = getGuard(obj)
            ptr = MHyPro(7, 8, obj.Handle);
            out = MHyProCondition(ptr);
        end
        
        function out = getReset(obj)
            ptr = MHyPro(7, 9, obj.Handle);
            out = MHyProReset(ptr);
        end
        
        function getAggregation(obj)
            MHyPro(7, 10, obj.Handle);
        end
        
        function out = getTriggerTime(obj)
            out = MHyPro(7, 11, obj.Handle);
        end
        
        function out = isUrgent(obj)
            out = MHyPro(7, 12, obj.Handle);
        end
        
        function out = isTimeTriggered(obj)
            out = MHyPro(7, 13, obj.Handle);
        end
        
        function out = hasIdentityReset(obj)
            out = MHyPro(7, 14, obj.Handle);
        end
        
        function out = getLabels(obj)
            ptrscell = MHyPro(7, 15, obj.Handle);
            out = cell(1, size(ptrscell, 2));
            for i = 1:size(ptrscell,2)
                ptr = ptrscell{i};
                out{i} = MHyProLabel(ptr);
            end
        end
        
        function out = hash(obj)
            out = MHyPro(7, 16, obj.Handle);
        end
        
        function setSource(obj, loc)
            if isa(loc, 'MHyProLocation') 
                MHyPro(7, 17, obj.Handle, loc.Handle);
            else
                error('MHyProTransition - setSource: Wrong type of at leat one argument.');
            end
        end
        
        function setTarget(obj, loc)
            if isa(loc, 'MHyProLocation') 
                MHyPro(7, 18, obj.Handle, loc.Handle);
            else
                error('MHyProTransition - setTarget: Wrong type of at leat one argument.');
            end
        end
        
        function setGuard(obj, cond)
            if isa(cond, 'MHyProCondition') 
                MHyPro(7, 19, obj.Handle, cond.Handle);
            else
                error('MHyProTransition - setGuard: Wrong type of at leat one argument.');
            end
        end
        
        function setReset(obj, res)
            if isa(res, 'MHyProReset') 
                MHyPro(7, 20, obj.Handle, res.Handle);
            else
                error('MHyProTransition - setReset: Wrong type of at leat one argument.');
            end
        end
        
        function setAggregation(obj, agg)
           if agg == 0 || agg == 1 || agg == 2
                MHyPro(7, 21, obj.Handle, agg);
           else
                error('MHyProTransition - setAggregation: Wrong type of at leat one argument.');
           end
        end
        
        function setUrgent(obj, urg)
            if urg == 1 || urg == 0 
                MHyPro(7, 22, obj.Handle, urg);
            else
                error('MHyProTransition - setUrgent: Wrong type of at leat one argument.');
            end
        end
        
        function setTriggerTime(obj, time)
            if isreal(time) 
                MHyPro(7, 23, obj.Handle, time);
            else
                error('MHyProTransition - setTriggerTime: Wrong type of at leat one argument.');
            end
        end
        
        function setLabels(obj, labs)
            objects = cell(1, length(labs));
            for i = 1:length(labs)
                if isa(labs{i}, 'MHyProLabel')
                    objects{i} = labs{i}.Handle;
                else
                    error('MHyProTransition - setLabels: Wrong type of input argument.');
                end
            end
            MHyPro(7, 24, obj.Handle, objects);
        end
        
        function addLabel(obj, lab)
            if isa(lab, 'MHyProLabel') 
                MHyPro(7, 25, obj.Handle, lab.Handle);
            else
                error('MHyProTransition - addLabel: Wrong type of at leat one argument.');
            end
        end
        
        function out = getDotRepresentation(obj, vars)
            if isstring(vars) 
                out = MHyPro(7, 26, obj.Handle, vars);
            else
                error('MHyProTransition - getDotRepresentation: Wrong type of at leat one argument.');
            end
        end
        
        function out = isComposedOf(obj, loc)
            %TODO
%             if iscelloftype(loc, 'MHyProLocation') 
%                 MHyPro(7, 27, obj.Handle, loc);
%             else
%                 error('MHyProTransition - setSource: Wrong type of at leat one argument.');
%             end
        end
        
        function decompose
            %TODO 28
        end
        
        function out = eq(obj, rhs)
            if isa(rhs, 'MHyProTransition') 
                out = MHyPro(7, 29, obj.Handle, rhs.Handle);
            else
                error('MHyProTransition - equals: Wrong type of at leat one argument.');
            end
        end
        
        function out = ne(obj, rhs)
            if isa(rhs, 'MHyProTransition') 
                out = MHyPro(7, 30, obj.Handle, rhs.Handle);
            else
                error('MHyProTransition - equals: Wrong type of at leat one argument.');
            end
        end
        
    end
end