classdef MHyProGeometricObject < handle
    % This class contains all common functions of boxes, support functions
    % and constraint sets. Every object has the following three properties:
    % ObjectHandle: Unique identifier of a object
    % Type: Character vector containing the type of the object

    properties (SetAccess = public, GetAccess = public)
        ObjectHandle
        Type
    end

     methods (Access = private)

        function delete(obj)
            MHyPro(obj.Type, 1, obj.ObjectHandle);
        end

     end

    methods (Access = public)

        function out = dimension(obj)
            out = MHyPro(obj.Type, 2, obj.ObjectHandle);
        end

        function out = vertices(obj)
            if obj.isempty() == 0
                out = MHyPro(obj.Type, 3, obj.ObjectHandle);
            else
                out = [];
            end
        end

        function reduceRepresentation(obj)
            MHyPro(obj.Type, 4, obj.ObjectHandle);
        end

        function out = ostream(obj)
            out = MHyPro(obj.Type, 5, obj.ObjectHandle);
        end

        function out = size(obj)
            out = MHyPro(obj.Type, 6, obj.ObjectHandle);
        end

        function out = eq(obj, rhs)
            if rhs.Type == obj.Type
                out = MHyPro(obj.Type, 7, obj.ObjectHandle, rhs.ObjectHandle);
            else
                error('MHyProGeometricObject - equal: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end

        function out = ne(obj, rhs)
            if obj.Type ~= 3 && rhs.Type == obj.Type
                out = MHyPro(obj.Type, 8, obj.ObjectHandle, rhs.ObjectHandle);
            else
                error('MHyProGeometricObject - unequal: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end

        function out = matrix(obj)
            out = MHyPro(obj.Type, 9, obj.ObjectHandle);
        end

        function out = vector(obj)
            if obj.Type ~= 1
                out = MHyPro(obj.Type, 10, obj.ObjectHandle);
            else
                error('HyProGeometricObjectInterface - vector: Not allowed for this type of HyProObject');
            end
        end

        function out = isempty(obj)
            out = MHyPro(obj.Type, 11, obj.ObjectHandle);
        end

        function removeRedundancy(obj)
            MHyPro(obj.Type, 12, obj.ObjectHandle);
        end

        function out = type(obj)
            out = MHyPro(obj.Type, 13, obj.ObjectHandle);
        end

        function [containment, out] = satisfiesHalfspace(obj, normal, offset)
            if isvector(normal)
                normal = conv2HyProVector(normal);
            else
                error('MHyProGeometricObject - satisfiesHalfspace: Wrong type of argument.');
            end
            if isreal(offset)
                [containment, ptr] = MHyPro(obj.Type, 14, obj.ObjectHandle, normal, offset);
                out = ptr2Object(obj.Type, ptr);
            else
                error('MHyProGeometricObject - satisfiesHalfspace: Wrong type of input argument.');
            end
        end

        function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
            if isvector(vec)
                vec = conv2HyProVector(vec);
            else
                error('MHyProGeometricObject - satisfiesHalfspaces: Wrong type of argument.');
            end
            if ismatrix(mat) && size(mat,2) == size(vec,1)
                [containment, ptr] = MHyPro(obj.Type, 15, obj.ObjectHandle, mat, vec);
                out = ptr2Object(obj.Type, ptr);
            else
                error('MHyProGeometricObject - satisfiesHalfspaces: Wrong type of input argument.');
            end
        end

        function out = projectOn(obj, dim)
            if isvector(dim)
                dim = conv2HyProVector(dim);
            else
                error('MHyProGeometricObject  - project: Wrong type of input argument.');
            end
            max = obj.dimension();
            if size(dim, 1) <= max
                for i = 1:length(dim)
                    dim(i) = dim(i)-1;
                end
                ptr = MHyPro(obj.Type, 16, obj.ObjectHandle, dim);
                out = ptr2Object(obj.Type, ptr);
            else
                error('MHyProGeometricObject  - project: Wrong type of input argument.');
            end
        end

         function out = linearTransformation(obj, mat)
            if ismatrix(mat)
                ptr = MHyPro(obj.Type, 17, obj.ObjectHandle, mat);
                out = ptr2Object(obj.Type, ptr);
            else
                error('MHyProGeometricObject  - linearTransformation: Wrong type of input argument.');
            end
        end

        function out = affineTransformation(obj, mat, vec)
            if isvector(vec)
                vec = conv2HyProVector(vec);
            else
                error('MHyProGeometricObject  - affineTransformation: Wrong type of input argument.');
            end

            if ismatrix(mat) && size(mat,2) == size(vec,1)
                ptr = MHyPro(obj.Type, 18, obj.ObjectHandle, mat, vec);
                out = ptr2Object(obj.Type, ptr);
            else
                error('MHyProGeometricObject - affineTransformation: Wrong type of input argument.');
            end
        end

        function out = plus(obj, rhs)
            if rhs.Type == obj.Type
                ptr = MHyPro(obj.Type, 19, obj.ObjectHandle, rhs.ObjectHandle);
                out = ptr2Object(obj.Type, ptr);
            else
                error('MHyProGeometricObject - minkowskiSum: Wrong type of input argument.');
            end
        end

        function out = intersectHalfspace(obj, nor, off)
            if isvector(nor)
                nor = conv2HyProVector(nor);
            else
                error('MHyProGeometricObject - intersectHalfspace: Wrong type of input argument.');
            end

            if isreal(off)
                ptr = MHyPro(obj.Type, 20, obj.ObjectHandle, nor, off);
                out = ptr2Object(obj.Type, ptr);
            else
                error('MHyProGeometricObject - intersectHalfspace: Wrong type of input argument.');
            end
        end

        function out = intersectHalfspaces(obj, mat, vec)
            if isvector(vec)
                vec = conv2HyProVector(vec);
            else
                error('MHyProGeometricObject - intersectHalfspaces: Wrong type of input argument.');
            end

            if ismatrix(mat) && size(mat,2) == size(vec,1)
                ptr = MHyPro(obj.Type, 21, obj.ObjectHandle, mat, vec);
                out = ptr2Object(obj.Type, ptr);
            else
                error('MHyProGeometricObject - intersectHalfspaces: Wrong type of input argument.');
            end
        end

        function out = contains(obj, arg)
            if isvector(arg)
                out = MHyPro(obj.Type, 22, obj.ObjectHandle, arg);
            elseif isRepresentation(arg) && obj.Type == arg.Type
                out = MHyPro(obj.Type, 23, obj.ObjectHandle, arg.ObjectHandle);
            else
                error('MHyProGeometricObject - contains: Wrong type of input argument.');
            end
        end

        function out = reduceNumberRepresentation(obj)
            ptr = MHyPro(obj.Type, 24, obj.ObjectHandle);
            out = ptr2Object(obj.Type, ptr);
        end

        function out = intersect(obj, rhs)
            if isRepresentation(rhs) && obj.Type == rhs.Type
                ptr = MHyPro(obj.Type, 25, obj.ObjectHandle, rhs.ObjectHandle);
                out = ptr2Object(obj.Type, ptr);
            else
                error('MHyProGeometricObject - intersect: Wrong type of argument.');
            end
        end

        function out = unite(obj, rhs)
            if isRepresentation(rhs) && obj.Type == rhs.Type
                ptr = MHyPro(obj.Type, 26, obj.ObjectHandle, rhs.ObjectHandle);
                out = ptr2Object(obj.Type, ptr);
            else
                error('MHyProGeometricObject - unite: Wrong type of input argument.');
            end
        end

        % Functions that do not use HyPro

        function plotObj(obj, dims)
            isempty = MHyPro(obj.Type, 11, obj.ObjectHandle);
            if isempty
                warning('MHyProGeometricObject - plot: It is not possible to plot an empty object.');
            else

                %Compute projection
                v = obj.vertices();
                temp = v(dims(1):dims(2),:);
                ver = unique(temp.','rows').';
                ver_x = ver(1,:);
                ver_y = ver(2,:);
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

        function plotVertices(obj, vertices, dims)
            isempty = MHyPro(obj.Type, 11, obj.ObjectHandle);
            if isempty
                warning('MHyProGeometricObject - plot: It is not possible to plot an empty object.');
            else

                %Compute projection
                temp = vertices(dims(1):dims(2),:);
                ver = unique(temp.','rows').';
                ver_x = ver(1,:);
                ver_y = ver(2,:);
                cx = mean(ver_x);
                cy = mean(ver_y);
                a = atan2(ver_y - cy, ver_x - cx);
                [~, order] = sort(a);
                ver_x = ver_x(order);
                ver_y = ver_y(order);

                pgon = polyshape(ver_x, ver_y);
                plot(pgon, 'green');
            end
        end
    end

    methods (Static)

        function out = uniteMultiple(objects)
            if ~isempty(objects) && iscelloftype(objects, objects{1}.Type)
                objectPtrs = cell(1, length(objects));
                for i = 1:length(objects)
                    objectPtrs{i} = objects{i}.ObjectHandle;
                end
                ptr = MHyPro(objects{1}.Type, 27, objectPtrs);
                out = ptr2Object(objects{1}.Type, ptr);
            else
                error('MHyProGeometricObject - uniteMultiple: Wrong type of input argument.');
            end
        end

    end
end