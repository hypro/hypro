classdef MHyProState < handle

    properties (SetAccess = public, GetAccess = public)
        ObjectHandle
    end

    methods (Access = private)

        % Destructor
        function delete(obj)
            MHyPro(13, 1, obj.ObjectHandle);
        end
    end

    methods (Access = public)

        % Constructor
        function obj = MHyProState(varargin)
            if nargin == 0
                obj.ObjectHandle = MHyPro(13, 2); %new_empty
            elseif nargin == 1 && isa(varargin{1}, 'uint64')
                obj.ObjectHandle = varargin{1};
            elseif nargin == 1 && isa(varargin{1}, 'MHyProState')
                obj.ObjectHandle = MHyPro(13, 3, varargin{1}.ObjectHandle); % copy
            elseif nargin == 1 && isa(varargin{1}, 'MHyProLocation')
                obj.ObjectHandle = MHyPro(13, 4, varargin{1}.ObjectHandle); % new_loc
            else
                error('MState - Constructor: Wrong type of at least one argument.');
            end
        end


        function out = getSetType(obj)
            out = MHyPro(13, 5, obj.ObjectHandle);
        end

        function out = getSets(obj)
            stateCell = MHyPro(13, 6, obj.ObjectHandle);
            out = cell(1, length(stateCell));
            for i = 1:length(stateCell)
                if isa(stateCell{i}, 'uint64')
                    out{i} = MHyProState(stateCell{i});
                else
                    error('MHyProState - getSets: Wrong type of input argument.');
                end
            end
        end

        function out = getTimestamp(obj)
            out = MHyPro(13, 7, obj.ObjectHandle);
        end

        function out = isempty(obj)
            out = MHyPro(13, 8, obj.ObjectHandle);
        end

        function out = vertices(obj, offset)
            out = MHyPro(13, 9, obj.ObjectHandle, offset);
        end

        function out = projectOn(obj, dims, offset)
            if iscell(dims)
                out = MHyPro(13, 10, obj.ObjectHandle, dims, offset);
            else
                error('MHyProState - wrong input argument.');
            end
        end

        function out = getDimension(obj, offset)
            out = MHyPro(13, 11, obj.ObjectHandle, offset);
        end

        function out = getDimensionOffset(obj, offset)
            out = MHyPro(13, 12, obj.ObjectHandle, offset);
        end

        function out = getLocation(obj)
            temp = MHyPro(13, 13, obj.ObjectHandle);
            out = MHyProLocation(temp);
        end

        function out = getNumberSets(obj)
            out = MHyPro(13, 14, obj.ObjectHandle);
        end

        function out = getSet(obj, pos)
            temp = MHyPro(13, 15, obj.ObjectHandle, pos - 1);
            out = MHyProState(temp);
        end

        function out = getTypes(obj)
            temp = MHyPro(13, 16, obj.ObjectHandle);
            out = cell(1, length(temp));
            for i = 1:length(temp)
                if isa(temp{i}, 'uint64')
                    out{i} = MHyProState(temp{i});
                else
                    error('MHyProState - getTypes: Wrong type of input argument.');
                end
            end
        end

        function setLocation(obj, loc)
            if isa(loc, 'MHyProLocation')
                MHyPro(13, 17, obj.ObjectHandle, loc.ObjectHandle);
            else
                error('MHyProState - setLocation: Wrong type of input argument.');
            end
        end

        % type = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        % 0 = box, 1 = carl_polytope, 2 = constraint_set
        % 3 = polytope_h, 4 = polytope_v
        % 5 = ppl_polytope, 6 = support_function, 7 = taylor_model
        % 8 = zonotope, 9 = difference_bounds,
        function setSetType(obj, type, pos)
            if type >= 0 && type <= 9 && mod(pos, 1) == 0
                MHyPro(13, 18, type, pos - 1);
            else
                error('MHyProState - setSetType: Wrong type of input argument.');
            end
        end

        function setSet(obj, type, at)
            if type == 0 || type == 2 || type == 7
                MHyPro(13, 19, obj.Handle, type, at-1);
            else
                error('MHyProState - setSet: Wrong type of input argument.');
            end
        end


    end
end