classdef MHyProGeometricObject < handle
    
    properties (SetAccess = public, GetAccess = public)
        ObjectHandle
        Type
    end
    
    methods (Abstract)
        satisfiesHalfspace(obj, normal, offset)
        satisfiesHalfspaces(obj, mat, vec)
        project(obj, dim)
        linearTransformation(obj, mat)
        affineTransformation(obj, mat, vec)
    end
    
     methods (Access = private)
        % Delete a MHyPro object - Destructor
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
        
        function ostream(obj)
            MHyPro(obj.Type, 5, obj.ObjectHandle);
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

        function out = clear(obj)
            out = MHyPro(obj.Type, 14, obj.ObjectHandle, rhs.ObjectHandle);
        end
     
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
end