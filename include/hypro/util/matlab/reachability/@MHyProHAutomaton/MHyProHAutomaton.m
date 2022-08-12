classdef MHyProHAutomaton < handle

    properties (SetAccess = public, GetAccess = public)
        ObjectHandle
    end

    methods (Access = private)

        % Destructor
        function delete(obj)
            MHyPro(4, 1, obj.ObjectHandle);
        end
    end

    methods (Access = public)

        % Constructor
        function obj = MHyProHAutomaton(varargin)
            if nargin == 0
                obj.ObjectHandle = MHyPro(4, 2);
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.ObjectHandle = varargin{1};
                elseif isa(varargin{1}, 'MHyProHAutomaton')
                    obj.ObjectHandle = MHyPro(4, 3, varargin{1}.ObjectHandle);
                else
                    obj.ObjectHandle = MHyPro(4, varargin{1});
                end
            elseif nargin == 2
                %if iscelloftype(varargin{1}, 'MHyProLocation') && isstruct(varargin{2})
                    numberLocations = length(varargin{1});
                    locPointers = cell(1, numberLocations);
                    mappingLen = length(varargin{2});
                    mapping_ObjectHandles = struct();
                    for i = 1:numberLocations
                        locPointers{i} = varargin{1}{i}.ObjectHandle;
                    end
                    for i = 1:mappingLen
                        mapping_ObjectHandles(i).loc = varargin{2}(i).loc.ObjectHandle;
                        mapping_ObjectHandles(i).cond = varargin{2}(i).cond.ObjectHandle;
                    end
                    obj.ObjectHandle = MHyPro(4, 4, locPointers, mapping_ObjectHandles);
               % end
            elseif nargin == 3
                obj.ObjectHandle = MHyPro(4, varargin{1}, varargin{2}, varargin{3});
            end
        end

        function out = dimension(obj)
            out = MHyPro(4, 5, obj.ObjectHandle);
        end

        function out = decompose(obj, vec)
            out = MHyPro(4, 6, obj.ObjectHandle, vec);
        end

        function out = getLocations(obj)
            ptrscell = MHyPro(4, 7, obj.ObjectHandle);
            out = cell(1, size(ptrscell,2));
            for i = 1:size(ptrscell,2)
                ptr = ptrscell{i};
                out{i} = MHyProLocation(ptr);
            end
        end

        function out = getLocation_by_hash(obj, hash)
            if isreal(hash)
                location = MHyPro(4, 8, obj.ObjectHandle, hash);
                out = MHyProLocation(location);

            else
                error('MHyProHAutomaton - getLocations_by_hash: Wrong type of argument.');

            end
        end

        function out = getLocation_by_name(obj, name)
            if ischar(name)
                [location1, location2] = MHyPro(4, 9, obj.ObjectHandle, name);
                out = [MHyProLocation(location1), MHyProLocation(location2)];
            else
                error('MHyProHAutomaton - getLocations_by_name: Wrong type of argument.');
            end
        end

        function out = getTransitions(obj)
            transitions = MHyPro(4, 10, obj.ObjectHandle);
            len = length(transitions);
            out = cell(1,len);
            for i = 1:length(len)
                out{i} = MHyProTransition(transitions{i});
            end
        end

        function out = getInitialStates(obj)
           mapping = MHyPro(4, 11, obj.ObjectHandle);
            len = length(mapping);
            out = struct();
            for i = 1:length(len)
                out(i).loc = MHyProLocation(mapping(i).loc);
                out(i).cond = MHyProCondition(mapping(i).cond);
            end
        end

        function out = getLocalBadStates(obj)
            mapping = MHyPro(4, 12, obj.ObjectHandle);
            len = length(mapping);
            out = struct();
            for i = 1:len
                out(i).loc = MHyProLocation(mapping(i).loc);
                disp(['loc:', num2str(out(i).loc.ObjectHandle)]);
                out(i).cond = MHyProCondition(mapping(i).cond);
                disp(['cond:', num2str(out(i).cond.ObjectHandle)]);
            end
        end

        function out = getGlobalBadStates(obj)
            mapping = MHyPro(4, 13, obj.ObjectHandle);
            len = length(mapping);
            out = struct();
            for i = 1:len
                out(i).loc = MHyProLocation(mapping(i).loc);
                out(i).cond = MHyProCondition(mapping(i).cond);
            end
        end

        function out = getVariables(obj)
            out = MHyPro(4, 14, obj.ObjectHandle);
        end

        function out = getLables(obj)
            labels = MHyPro(4, 15, obj.ObjectHandle);
            len = length(labels);
            out = cell(1,len);
            for i = 1:length(len)
                out{i} = MHyProLocation(labels{i});
            end
        end

        function setLocations(obj, locs)
            if iscell(locs) && isa(locs{0}, 'MHyProLocation')
                len = lengt(locs);
                loc_ObjectHandles = cell(1,len);
                for i = 1:len
                    loc_ObjectHandles{i} = locs{i}.ObjectHandle;
                end
                MHyPro(4, 16, obj.ObjectHandle, loc_ObjectHandles);
            end
        end

        function setInitialStates(obj, mapping)
            len = length(mapping);
            mapping_ObjectHandles = struct();
            for i = 1:len
                mapping_ObjectHandles(i).loc = mapping(i).loc.ObjectHandle;
                mapping_ObjectHandles(i).cond = mapping(i).cond.ObjectHandle;
            end
            MHyPro(4, 17, obj.ObjectHandle, mapping_ObjectHandles);
        end

        function setLocalBadStates(obj, mapping)
            len = length(mapping);
            if isstruct(mapping) && len > 0
                mappingObjectHandles = struct();
                for i = 1:length(mapping)
                    if isa(mapping(i).loc,'MHyProLocation') && isa(mapping(i).cond,'MHyProCondition')
                        mappingObjectHandles(i).loc = mapping(i).loc.ObjectHandle;
                        mappingObjectHandles(i).cond = mapping(i).cond.ObjectHandle;
                    else
                        error('MHyProHAutomaton - setLocalBadStates: Wrong type of an argument.');
                    end
                end
                MHyPro(4, 18, obj.ObjectHandle, mappingObjectHandles);
            else
                error('MHyProHAutomaton - setLocalBadStates: Wrong type of an argument.');
            end
        end

        function setGlobalBadStates(obj, mapping)
            len = length(mapping);
            if isstruct(mapping) && len > 0
                mappingObjectHandles = struct();
                for i = 1:length(mapping)
                    if isa(mapping(i).loc,'MHyProLocation') && isa(mapping(i).cond, 'MHyProCondition')
                        mappingObjectHandles(i).loc = mapping(i).loc.ObjectHandle;
                        mappingObjectHandles(i).cond = mapping(i).cond.ObjectHandle;
                    else
                        error('MHyProHAutomaton - setLocalBadStates: Wrong type of an argument.');
                    end
                end
                MHyPro(4, 19, obj.ObjectHandle, mappingObjectHandles);
            end
        end

        function setVariables(obj, vars)
            MHyPro(4, 20, obj.ObjectHandle);
        end

        function out = addLocation(obj, loc)
            if isa(loc, 'MHyProLocation')
                ptr = MHyPro(4, 21, obj.ObjectHandle, loc.ObjectHandle);
                out = MHyProLocation(ptr);
                out.SmartFlag = 1;
            end
        end

        function addInitialState(obj, loc, cond)
            if isa(loc, 'MHyProLocation') && isa(cond, 'MHyProCondition')
                MHyPro(4, 22, obj.ObjectHandle, loc.ObjectHandle, cond.ObjectHandle);
            else
                error('MHyProHAutomaton - addInitialState: Wrong type of an argument.');
            end
        end

        function addLocalBadStates(obj, loc, cond)
            if isa(loc, 'MHyProLocation') && isa(cond, 'MHyProCondition')
                MHyPro(4, 23, obj.ObjectHandle, loc.ObjectHandle, cond.ObjectHandle);
            else
                error('MHyProHAutomaton - addLocalBadStates: Wrong type of an argument.');
            end
        end

        function addGlobalBadStates(obj, cond)
            if isa(cond, 'MHyProCondition')
                MHyPro(4, 24, obj.ObjectHandle, cond.ObjectHandle);
            else
                error('MHyProHAutomaton - addGlobalBadStates: Wrong type of an argument.');
            end
        end

        function reduce(obj)
            MHyPro(4, 25, obj.ObjectHandle);
        end

        function out = isComposedOf(obj, rhs)
            if isa(rhs, 'MHyProAutomaton')
                 out = MHyPro(4, 26, obj.ObjectHandle, rhs.ObjectHandle);
            else
                error('MHyProHAutomaton - isComposedOf: Wrong type of an argument.');
            end
        end

        function out = getDotRepresentation(obj)
            out = MHyPro(4, 27, obj.ObjectHandle);
        end

        function out = getStatistics(obj)
            out = MHyPro(4, 28, obj.ObjectHandle);
        end

        function out = eq(lhs, rhs)
            if isa(lhs, 'MHyProHAutomaton') && isa(rhs, 'MHyProHAutomaton')
                out = MHyPro(4, 29, lhs.ObjectHandle, rhs.ObjectHandle);
            else
                error('MHyProHAutomaton - ==: Wrong type of an argument.');
            end
        end

        function out = nq(lhs, rhs)
           if isa(lhs, 'MHyProHAutomaton') && isa(rhs, 'MHyProHAutomaton')
                out = MHyPro(4, 30, lhs.ObjectHandle, rhs.ObjectHandle);
            else
                error('MHyProHAutomaton - !=: Wrong type of an argument.');
            end
        end

        function out = plus(lhs, rhs)
            if isa(lhs, 'MHyProHAutomaton') && isa(rhs, 'MHyProHAutomaton')
                out = MHyPro(4, 31, lhs.ObjectHandle, rhs.ObjectHandle);
            else
                error('MHyProHAutomaton - +: Wrong type of an argument.');
            end
        end

        function addTransition(obj, tran)
            if isa(tran, 'MHyProTransition')
                MHyPro(4, 32, obj.ObjectHandle, tran.ObjectHandle);
            else
                error('MHyProHAutomaton - addTransition: Wrong type of an argument.');
            end
        end

    end

end