classdef MHyProHAutomaton < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro('HybridAutomaton', 'delete', obj.Handle);
        end
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProHAutomaton(varargin)
            if nargin == 0
                obj.Handle = MHyPro('HybridAutomaton', 'new_empty');
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.Handle = varargin{1};
                elseif isa(varargin{1}, 'MHyProHAutomaton')
                    obj.Handle = MHyPro('HybridAutomaton', 'copy', varargin{1}.Handle);
                else
                    obj.Handle = MHyPro('HybridAutomaton', varargin{1});
                end
            elseif nargin == 2
                
            elseif nargin == 3
                obj.Handle = MHyPro('HybridAutomaton', varargin{1}, varargin{2}, varargin{3});
            end
        end
                
        function out = dimension(obj)
            out = MHyPro('HybridAutomaton', 'dimension', obj.Handle);
        end
        
        function out = decompose(obj, vec)
            out = MHyPro('HybridAutomaton', 'decompose', obj.Handle, vec);
        end
        
        function out = getLocations(obj)
            loc_handle = MHyPro('HybridAutomaton', 'getLocations', obj.Handle);
            out = 0;
            %TODO
        end
        
        function out = getLocations_by_hash(obj, hash)
            if isreal(hash)
                loc_handle = MHyPro('HybridAutomaton', 'getLocation_by_hash', obj.Handle, hash);
                %TODO
            else
                error('MHyProHAutomaton - getLocations_by_hash: Wrong type of argument.');
        
            end
        end
        
        function out = getLocations_by_name(obj, name)
            if isstring(name)
                loc_handle = MHyPro('HybridAutomaton', 'getLocations_by_name', obj.Handle, name);
                %TODO
            else
                error('MHyProHAutomaton - getLocations_by_name: Wrong type of argument.');
            end
        end
        
        function out = getTransitions(obj)
            tran_handle = MHyPro('HybridAutomaton', 'getTransitions', obj.Handle);
            %TODO
        end
        
        function out = getInitialStates(obj)
            handle = MHyPro('HybridAutomaton', 'getInitialStates', obj.Handle);
            %TODO
        end
        
        function out = getLocalBadStates(obj)
            handle = MHyPro('HybridAutomaton', 'getLocalBadStates', obj.Handle);
            %TODO
        end
        
        function out = getGlobalBadStates(obj)
            handle = MHyPro('HybridAutomaton', 'getGlobalBadStates', obj.Handle);
            %TODO
        end
        
        function out = getVariables(obj)
            out = MHyPro('HybridAutomaton', 'getVariables', obj.Handle);
        end
        
        function out = getLables(obj)
            handle = MHyPro('HybridAutomaton', 'getLabels', obj.Handle);
            %TODO
        end
        
        function setLocations(obj, locs)
            if iscell(locs) && isa(locs{0}, 'MHyProLocation')
                MHyPro('HybridAutomaton', 'setLocations', obj.Handle, locs);
                %TODO
            end
        end
        
        function setInitialStates(obj, mapping)
            MHyPro('HybridAutomaton', 'setInitialStates', obj.Handle, mapping);
            %TODO
        end
        
        function setLocalBadStates(obj, mapping)
            MHyPro('HybridAutomaton', 'setLocalBadStates', obj.Handle);
            %TODO
        end
        
        function setGlobalBadStates(obj, mapping)
            MHyPro('HybridAutomaton', 'setGlobalBadStates', obj.Handle);
            %TODO
        end
        
        function setVariables(obj, vars)
            MHyPro('HybridAutomaton', 'setVariables', obj.Handle);
        end
        
        function addLocation(obj, loc)
            if isa(loc, 'MHyProLocation')
                MHyPro('HybridAutomaton', 'addLocation', obj.Handle, loc.Handle);
            end
        end
        
        function addInitialState(obj, loc, cond)
            if isa(loc, 'MHyProLocation') && isa(cond, 'Condition')
                MHyPro('HybridAutomaton', 'addInitialState', obj.Handle, loc.Handle, cond.Handle);
            else
                error('MHyProHAutomaton - addInitialState: Wrong type of an argument.');
            end
        end
        
        function addLocalBadState(obj, loc, cond)
            if isa(loc, 'MHyProLocation') && isa(cond, 'Condition')
                MHyPro('HybridAutomaton', 'addLocalBadState', obj.Handle, loc.Handle, cond.Handle);
            else
                error('MHyProHAutomaton - addLocalBadState: Wrong type of an argument.');
            end
        end
        
        function addGlobalBadState(obj, cond)
            if isa(cond, 'Condition')
                MHyPro('HybridAutomaton', 'addGlobalBadState', obj.Handle, cond.Handle);
            else
                error('MHyProHAutomaton - addGlobalBadState: Wrong type of an argument.');
            end
        end
        
        function reduce(obj)
            MHyPro('HybridAutomaton', 'reduce', obj.Handle);
        end
        
        function out = isComposedOf(obj, rhs)
            if isa(rhs, 'MHyProAutomaton')
                 out = MHyPro('HybridAutomaton', 'isComposedOf', obj.Handle, rhs.Handle);
            else
                error('MHyProHAutomaton - isComposedOf: Wrong type of an argument.');
            end
        end
        
        function out = getDotRepresentation(obj)
            out = MHyPro('HybridAutomaton', 'getDotRepresentation', obj.Handle);
        end
        
        function out = getStatistics(obj)
            out = MHyPro('HybridAutomaton', 'getStatistics', obj.Handle);
        end
        
        function out = eq(lhs, rhs)
            if isa(lhs, 'HybridAutomaton') && isa(rhs, 'HybridAutomaton')
                out = MHyPro('HybridAutomaton', '==', lhs.Handle, rhs.Handle);
            else
                error('MHyProHAutomaton - ==: Wrong type of an argument.');
            end
        end
        
        function out = nq(lhs, rhs)
           if isa(lhs, 'HybridAutomaton') && isa(rhs, 'HybridAutomaton')
                out = MHyPro('HybridAutomaton', '!=', lhs.Handle, rhs.Handle);
            else
                error('MHyProHAutomaton - !=: Wrong type of an argument.');
            end
        end 
        
        function out = plus(lhs, rhs)
            if isa(lhs, 'HybridAutomaton') && isa(rhs, 'HybridAutomaton')
                out = MHyPro('HybridAutomaton', '+', lhs.Handle, rhs.Handle);
            else
                error('MHyProHAutomaton - +: Wrong type of an argument.');
            end
        end
     
    end
    
end