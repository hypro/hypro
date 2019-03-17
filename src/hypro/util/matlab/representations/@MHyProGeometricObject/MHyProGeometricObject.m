classdef MHyProGeometricObject < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
        Type
    end
    
    methods (Abstract)
        satisfiesHalfspace(obj, normal, offset)
        satisfiesHalfspaces(obj, mat, vec)
        project(obj, dim)
        linearTransformation(obj, mat)
        affineTransformation(obj, mat, vec)
        plot(obj, dims)
    end
    
     methods (Access = private)
        % Delete a MHyPro object - Destructor
        function delete(obj)
            MHyPro(obj.Type,'delete', obj.Handle);
        end
    end
    
    
    methods (Access = public)
        
        function out = dimension(obj)
            out = MHyPro(obj.Type, 'dimension', obj.Handle);
        end
        
        function out = vertices(obj)
            if obj.isempty() == 0
                out = MHyPro(obj.Type, 'vertices', obj.Handle);
            else
                out = [];
            end          
        end
        
        function reduceRepresentation(obj)
            MHyPro(obj.Type, 'reduceRepresentation', obj.Handle);
        end
        
        function ostream(obj)
            MHyPro(obj.Type, '<<', obj.Handle);
        end
        
        function out = size(obj)
            out = MHyPro(obj.Type, 'size', obj.Handle);
        end
        
        function out = eq(obj, rhs)
            if strcmp(rhs.Type, obj.Type)
                out = MHyPro(obj.Type, '==', obj.Handle, rhs.Handle);
            else
                error('MHyProGeometricObject - equal: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = ne(obj, rhs)
            if ~strcmp(obj.Type, 'SupportFunction') && strcmp(rhs.Type, obj.Type)
                out = MHyPro(obj.Type, '!=', obj.Handle, rhs.Handle);
            else
                error('MHyProGeometricObject - unequal: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = matrix(obj)
            out = MHyPro(obj.Type, 'matrix', obj.Handle);
        end
        
        function out = vector(obj)
            if ~strcmp(obj.Type, 'Ellipse')
                out = MHyPro(obj.Type, 'vector', obj.Handle);
            else
                error('HyProGeometricObjectInterface - vector: Not allowed for this type of HyProObject');
            end
        end
        
        function out = isempty(obj)
            out = MHyPro(obj.Type, 'isEmpty', obj.Handle);
        end
        
        function removeRedundancy(obj)
            MHyPro(obj.Type, 'removeRedundancy', obj.Handle);
        end
        
        function out = type(obj)
            out = MHyPro(obj.Type, 'type', obj.Handle);
        end

        function out = clear(obj)
            out = MHyPro(obj.Type, 'clear', obj.Handle, rhs.Handle);
        end
     
    end
end