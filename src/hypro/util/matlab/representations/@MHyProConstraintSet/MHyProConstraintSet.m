classdef MHyProConstraintSet < MHyProGeometricObject

    methods (Access = public)
        
        % Create a HyPro constraint set
        function obj = MHyProConstraintSet(varargin) 
            obj.Type = 2;
            
            if nargin == 0
                % Call default constructor
                obj.Handle = MHyPro(2, 15);
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.Handle = varargin{1};
                elseif isa(varargin{1}, 'MHyProConstraintSet')
                    % Call copy constructor
                    obj.Handle = MHyPro(2, 16, varargin{1}.Handle);
                else
                    error('MHyProConstraintSet - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if ismatrix(varargin{1}) && isvector(varargin{2}) && size(varargin{1},1) == size(varargin{2},1)
                    obj.Handle = MHyPro(2, 17, varargin{1}, varargin{2});
                else
                    error('MHyProConstraintSet - Constructor: Wrong arguments.');
                end
            else
                error('MHyProConstraintSet - Constructor: wrong arguments.');
            end
        end

        function [containment, out] = satisfiesHalfspace(obj, normal, offset)
            if isvector(normal) && isreal(offset)
                [containment, ptr] = MHyPro(2, 18, obj.Handle, normal, offset);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - satisfiesHalfspace: Wrong type of input argument.');
            end
        end
        
        function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                [containment, ptr] = MHyPro(2, 19, obj.Handle, mat, vec);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - satisfiesHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = project(obj, dims)
            if isvector(dims)
                ptr = MHyPro(2, 20, obj.Handle, dims);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - project: Wrong type of input argument.');
            end
        end
        
        function out = linearTransformation(obj, mat)
            if ismatrix(mat)
                ptr = MHyPro(2, 21, obj.Handle, mat);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - linearTransformation: Wrong type of input argument.');
            end
        end
        
        function out = affineTransformation(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro(2, 22, obj.Handle, mat, vec);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - affineTransformation: Wrong type of input argument.');
            end 
        end
        
        function out = plus(obj, rhs)
            if isa(rhs, 'MHyProConstraintSet')
                ptr = MHyPro(2, 23, obj.Handle, rhs.Handle);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - minkowskiSum: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspace(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro(2, 24, obj.Handle, mat, vec);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - intersectHalfspace: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro(2, 25, obj.Handle, mat, vec);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - intersectHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = contains(obj, arg)
            if isa(arg, 'MHyProConstraintSet')
                out = MHyPro(2, 26, obj.Handle, arg.Handle);
            else
                error('MHyProConstraintSet - contains: Wrong type of input argument.');
            end
        end
        
        function out = containsPoint(obj, pnt)
            if isvector(pnt)
                out = MHyPro(2, 27, obj.Handle, pnt);
            else
                error('MHyProConstraintSet - contains: Wrong type of input argument.');
            end
        end
        
        function out = unite(obj, rhs)
            if isa(rhs, 'MHyProConstraintSet')
                ptr = MHyPro(2, 28, obj.Handle, rhs.Handle);
                out = MHyProConstraintSet(ptr);
            elseif iscelloftype(rhs, "MHyProConstraintSet")
                objects = uint64.empty(length(rhs),0);
                for i = 1:length(rhs)
                    objects{i} = rhs{i}.Handle;
                end
                object
                out = 1;
%                 ptr = MHyPro(2, 29, obj.Handle, objects);
%                 out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - unite: Wrong type of input argument.');
            end
        end

        function reduceNumberRepresentation(obj)
            MHyPro(2, 30, obj.Handle);
        end
        
        function out = intersect(obj, rhs)
            if isa(rhs, 'MHyProConstraintSet') 
                ptr = MHyPro(2, 31, obj.Handle, rhs.Handle);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - intersect: Wrong type of argument.');
            end
        end

       function out = isAxisAligned(obj)
           out = MHyPro(2, 32, obj.Handle);
       end
       
       function addConstraint(obj, vec, offset)
            if isvector(vec) && isreal(offset)
                MHyPro(2, 33, obj.Handle, vec, offset);
            else
                error('MHyProConstraintSet - addConstraint: Wrong type of argument.');
            end
       end
       
       function plot(obj, dims)
            isempty = MHyPro(obj.Type, 11, obj.Handle);
            if isempty
                warning('MHyProConstraintSet - plot: It is not possible to plot an empty object.');
            else
                vertices = MHyPro(2, 3, obj.Handle);
                plotVertices(obj, vertices, dims);

                % Sort the vertices clockwise
%                 ver_x = vertices(:,1).';
%                 ver_y = vertices(:,2).';
%                 cx = mean(ver_x);
%                 cy = mean(ver_y);
%                 a = atan2(ver_y - cy, ver_x - cx);
%                 [~, order] = sort(a);
%                 ver_x = ver_x(order);
%                 ver_y = ver_y(order);
% 
%                 pgon = polyshape(ver_x, ver_y);
%                 plot(pgon);                
            end
        end

    end
end