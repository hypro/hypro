classdef MHyProBox < MHyProGeometricObjectInterface

    methods (Access = public)
        
        % Create a HyPro box
        function obj = MHyProBox(varargin) 
            obj.Type = 'Box';
            if nargin == 0
                % Call default constructor
                obj.Handle = MHyPro('Box', 'new_empty');
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    % This constructor is needed in case HyPro returns
                    % a new box
                    obj.Handle = varargin{1};
                elseif isa(varargin{1}, 'MHyProBox')
                    % Call copy constructor
                    obj.Handle = MHyPro('Box', 'copy', varargin{1}.Handle);
                elseif ismatrix(varargin{1})
                    obj.Handle = MHyPro('Box', 'new_matrix', varargin{1});
                else
                    error('MHyProBox - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if strcmp(varargin{1}, 'points') && ismatrix(varargin{2})
                    obj.Handle = MHyPro('Box', 'new_points', varargin{2});
                elseif strcmp(varargin{1}, 'interval') && areIntervals(varargin{2})
                    obj.Handle = MHyPro('Box', 'new_interval', varargin{2});
                elseif strcmp(varargin{1}, 'intervals') && areIntervals(varargin{2})
                    obj.Handle = MHyPro('Box', 'new_intervals', varargin{2});
                elseif ismatrix(varargin{1}) && isvector(varargin{2}) && (size(varargin{1}, 2)== size(varargin{2},1))
                    obj.Handle = MHyPro('Box', 'new_mat_vec', varargin{1}, varargin{2});
                else
                    error('MHyProBox - Constructor: Wrong arguments.');
                end
            else
                error('MHyProBox - Constructor: wrong arguments.');
            end
        end
        
        function out = test(obj)
            %Test function
        end
        
                
        function out = empty(obj,dim)
            if mod(dim, 1) == 0
                ptr = MHyPro('Box', 'empty', obj.Handle, dim);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - empty: Wrong type of input argument.');
            end
        end
       
        function [containment, out] = satisfiesHalfspace(obj, normal, offset)
            if isvector(normal) && isreal(offset)
                [containment, ptr] = MHyPro('Box', 'satisfiesHalfspace', obj.Handle, normal, offset);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - satisfiesHalfspace: Wrong type of input argument.');
            end
        end
        
        function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                [containment, ptr] = MHyPro('Box', 'satisfiesHalfspace', obj.Handle, mat, vec);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - satisfiesHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = project(obj, dim)
            max = obj.dimension();
            if isvector(dim) && size(dim, 1) <= max 
                new_dim = zeros(max,1);
                for i = 1:size(dim,1)
                    if dim(i) <= max
                        % Has to be reduced to match C++
                        new_dim(i) = dim(i) - 1;
                    else
                        error('MHyProBox - project: Dimension exceeds the dimension of object.');
                    end
                end
                ptr = MHyPro('Box', 'project', obj.Handle, new_dim);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - project: Wrong type of input argument.');
            end
        end
        
        function out = linearTransformation(obj, mat)
            if ismatrix(mat)
                ptr = MHyPro('Box', 'linearTransformation', obj.Handle, mat);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - linearTransformation: Wrong type of input argument.');
            end
        end
        
        function out = affineTransformation(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro('Box', 'affineTransformation', obj.Handle, mat, vec);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - affineTransformation: Wrong type of input argument.');
            end 
        end
        
        function out = plus(obj, rhs)
            if isa(rhs, 'MHyProBox')
                ptr = MHyPro('Box', 'minkowskiSum', obj.Handle, rhs.Handle);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - minkowskiSum: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro('Box', 'intersectHalfspaces', obj.Handle, mat, vec);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - intersectHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspace(obj, nor, off)
            if isvector(nor) && isreal(off)
                ptr = MHyPro('Box', 'intersectHalfspace', obj.Handle, nor, off);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - intersectHalfspace: Wrong type of input argument.');
            end
        end

        function out = contains(obj, arg)
            if isreal(arg)
                out = MHyPro('Box', 'contains_point', obj.Handle, arg);
            elseif isa(arg, 'MHyProBox')
                out = MHyPro('Box', 'contains_set', obj.Handle, arg.Handle);
            else
                error('MHyProBox - contains: Wrong type of input argument.');
            end
        end
        
        function out = unite(obj, rhs)
            if isa(rhs, 'MHyProBox')
                ptr = MHyPro('Box', 'unite', obj.Handle, rhs.Handle);
                out = MHyProBox(ptr);
%             elseif iscell(rhs)
%                 objects = uint64.empty(length(rhs),0);
%                 for i = 1:length(rhs)
%                     objects{i} = rhs{i}.Handle;
%                 end
%                 ptr = MHyPro('Box', 'unite_objects', obj.Handle, objects{:});
            elseif iscell(rhs)
%                 objects = uint64.empty(length(rhs),0);
                objects = cell(1,2);
                for i = 1:length(rhs)
                    if isa(rhs{i}, 'MHyProBox')
                        objects{i} = rhs{i}.Handle;
                    else
                        error('MHyProBox - unite: Wrong type of input argument.');
                    end
                end
                ptr = MHyPro('Box', 'unite_objects', obj.Handle, objects);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - unite: Wrong type of input argument.');
            end
        end
 
        function plot(obj, dims)
            isempty = MHyPro(obj.Type, 'isEmpty', obj.Handle);
            if isempty
                warning('MHyProBox - plot: It is not possible to plot an empty object.');
            else
                %ver = MHyPro('Box', 'vertices', obj.Handle);
                intervals = MHyPro('Box', 'intervals', obj.Handle);
                inter_1 = intervals(dims(1),:);
                inter_2 = intervals(dims(2),:);
                [~, dimx] = size(inter_1);
                ver = zeros(dimx*2, 2);
                counter = 0;

                for i = 1:(dimx)
                    for j = 1:(dimx)
                        ver(j+counter,1) = inter_1(i);
                        ver(j+counter,2) = inter_2(j);
                    end
                    counter = counter + dimx;
                end

                % Sort the vertices clocwise
                ver_x = ver(:,1).';
                ver_y = ver(:,2).';
                cx = mean(ver_x);
                cy = mean(ver_y);
                a = atan2(ver_y - cy, ver_x - cx);
                [~, order] = sort(a);
                ver_x = ver_x(order);
                ver_y = ver_y(order);

                pgon = polyshape(ver_x, ver_y);
                plot(pgon);                
            end
        end

        function out = reduceNumberRepresentation(obj)
            ptr = MHyPro('Box', 'reduceNumberRepresentation', obj.Handle);
            out = MHyProBox(ptr);
        end

        function out = intervals(obj)
            out = MHyPro('Box', 'intervals', obj.Handle);
        end
        
        function out = limits(obj)
            out = MHyPro('Box', 'limits', obj.Handle);
        end
        
        function [containment, box] = constraints(obj)
            [containment, box] = MHyPro(obj.Type, 'constraints', obj.Handle);
        end
        
        function insert(obj, inter)
            if areIntervals(inter)
                MHyPro('Box', 'insert', obj.Handle, inter);
            else
                error('MHyProBox - insert: Wrong type of argument.');
            end
        end
        
        function out = interval(obj, dim)
            if mod(dim, 1) == 0 && dim >= 1
                out = MHyPro('Box', 'interval', obj.Handle, dim);
            else
                error('MHyProBox - interval: Wrong type of argument.');
            end
        end
        
        function out = at(obj, dim)
            if mod(dim, 1) == 0
                out = MHyPro('Box', 'at', obj.Handle, dim);
            else
                error('MHyProBox - at: Wrong type of argument.');
            end
        end
        
        function out = isSymmetric(obj)
            out = MHyPro('Box', 'isSymmetric', obj.Handle);
        end
        
        function out = max(obj)
            out = MHyPro('Box', 'max', obj.Handle);
        end
        
        function out = min(obj)
            out = MHyPro('Box', 'min', obj.Handle);
        end
        
        function out = supremum(obj)
            if strcmp(obj.Type, 'Box') || strcmp(obj.Type, 'SupportFunction')
                out = MHyPro(obj.Type, 'supremum', obj.Handle);
            else
                error('MHyProObject - supremum: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = evaluate(obj, vec, dir)
            if strcmp(obj.Type, 'Box') && isreal(vec) && islogical(dir)
                out = MHyPro(obj.Type, 'evaluate', obj.Handle, vec, dir);
            else
                error('MHyProObject - evaluate: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = mtimes(obj, scalar)
            if isreal(scalar)
                ptr = MHyPro('Box', '*', obj.Handle, scalar);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - scale: Wrong type of argument.');
            end
        end
        
        function out = makeSymmetric(obj)
            ptr = MHyPro('Box', 'makeSymmetric', obj.Handle);
            out = MHyProBox(ptr);
        end
        
        function out = minkowskiDecomposition(obj, rhs)
            if isa(rhs, 'MHyProBox')
                ptr = MHyPro(obj.Type, 'minkowskiDecomposition', obj.Handle, rhs.Handle);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - minkowskiDecomposition: Wrong type of argument.');
            end
        end
        
        function out = intersect(obj, rhs)
            if isa(rhs, 'MHyProBox') 
                ptr = MHyPro('Box', 'intersect', obj.Handle, rhs.Handle);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - intersect: Wrong type of argument.');
            end
        end

    end
end