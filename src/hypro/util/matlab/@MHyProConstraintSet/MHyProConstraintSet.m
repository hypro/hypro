classdef MHyProConstraintSet < MHyProGeometricObjectInterface

    methods (Access = public)
        
        % Create a HyPro constraint set
        function obj = MHyProConstraintSet(varargin) 
            obj.Type = 'ConstraintSet';
            
            if nargin == 0
                % Call default constructor
                obj.Handle = MHyPro('ConstraintSet', 'new_empty');
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.Handle = varargin{1};
                elseif isa(varargin{1}, 'MHyProConstraintSet')
                    % Call copy constructor
                    obj.Handle = MHyPro('ConstraintSet', 'copy', varargin{1}.Handle);
                else
                    error('MHyProConstraintSet - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if ismatrix(varargin{1}) && isvector(varargin{2}) && size(varargin{1},2) == size(varargin{2},1)
                    obj.Handle = MHyPro('ConstraintSet', 'new_mat_vec', varargin{1}, varargin{2});
                else
                    error('MHyProConstraintSet - Constructor: Wrong arguments.');
                end
            else
                error('MHyProConstraintSet - Constructor: wrong arguments.');
            end
        end

        function [containment, out] = satisfiesHalfspace(obj, normal, offset)
            if isvector(normal) && isreal(offset)
                [containment, ptr] = MHyPro('ConstraintSet', 'satisfiesHalfspace', obj.Handle, normal, offset);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - satisfiesHalfspace: Wrong type of input argument.');
            end
        end
        
        function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                [containment, ptr] = MHyPro('ConstraintSet', 'satisfiesHalfspace', obj.Handle, mat, vec);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - satisfiesHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = project(obj, dim)
            if isreal(dim)
                ptr = MHyPro('ConstraintSet', 'project', obj.Handle, dim);
                out = MHyProConstraintSet( ptr);
            else
                error('MHyProConstraintSet - project: Wrong type of input argument.');
            end
        end
        
        function out = linearTransformation(obj, mat)
            if ismatrix(mat)
                ptr = MHyPro('ConstraintSet', 'linearTransformation', obj.Handle, mat);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - linearTransformation: Wrong type of input argument.');
            end
        end
        
        function out = affineTransformation(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro('ConstraintSet', 'affineTransformation', obj.Handle, mat, vec);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - affineTransformation: Wrong type of input argument.');
            end 
        end
        
        function out = plus(obj, rhs)
            if isa(rhs, 'MHyProConstraintSet')
                ptr = MHyPro('ConstraintSet', 'minkowskiSum', obj.Handle, rhs.Handle);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - minkowskiSum: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspace(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro('ConstraintSet', 'intersectHalfspace', obj.Handle, mat, vec);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - intersectHalfspace: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro('ConstraintSet', 'intersectHalfspaces', obj.Handle, mat, vec);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - intersectHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = contains(obj, arg)
            if isa(arg, 'MHyProConstraintSet')
                out = MHyPro('ConstraintSet', 'contains_set', obj.Handle, arg.Handle);
            else
                error('MHyProConstraintSet - contains: Wrong type of input argument.');
            end
        end
        
        function out = containsPoint(obj, pnt)
            if isvector(pnt)
                out = MHyPro('ConstraintSet', 'contains_point', obj.Handle, pnt);
            else
                error('MHyProConstraintSet - contains: Wrong type of input argument.');
            end
        end
        
        function out = unite(obj, rhs)
            if isa(rhs, 'MHyProConstraintSet')
                ptr = MHyPro('ConstraintSet', 'unite', obj.Handle, rhs.Handle);
                out = MHyProConstraintSet(ptr);
            elseif iscell(rhs)
                objects = uint64.empty(length(rhs),0);
                for i = 1:length(rhs)
                    objects{i} = rhs{i}.Handle;
                end
                ptr = MHyPro('ConstraintSet', 'unite_objects', obj.Handle, objects);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - unite: Wrong type of input argument.');
            end
        end
 
        function plot(obj, dims)
            error('MHyProConstraintSet - plot: NOT IMPLEMENTED')
        end

        function reduceNumberRepresentation(obj)
            MHyPro('ConstraintSet', 'reduceNumberRepresentation', obj.Handle);
        end

        function out = supremum(obj)
            if strcmp(obj.Type, 'ConstraintSet') || strcmp(obj.Type, 'ConstraintSet')
                out = MHyPro(obj.Type, 'supremum', obj.Handle);
            else
                error('MHyProObject - supremum: Not allowed for this type of HyProObject.');
            end
        end

        function out = intersect(obj, rhs)
            if isa(rhs, 'MHyProConstraintSet') 
                ptr = MHyPro('ConstraintSet', 'intersect', obj.Handle, rhs.Handle);
                out = MHyProConstraintSet(ptr);
            else
                error('MHyProConstraintSet - intersect: Wrong type of argument.');
            end
        end
        
        function cleanUp(obj)
            MHyPro('ConstraintSet', 'cleanUp', obj.Handle);
        end
       
        function out = depth(obj)
            out = MHyPro('ConstraintSet', 'depth', obj.Handle);
        end
       
        function out = operationCount(obj)
        	 out = MHyPro('ConstraintSet', 'operationCount', obj.Handle);
        end

        function out = contains_vec(obj, vec)
            if isvector(vec)
                 out = MHyPro('ConstraintSet', 'contains_vec', obj.Handle, vec);
            else
                 error('MHyProObject - contains_vec: Wrong argument.');
            end
        end

       function out = contains_dir(obj,rhs, dir)
           if isa(rhs, 'MHyProConstraintSet') && isreal(dir)
                out = MHyPro('ConstraintSet', 'contains_dir', obj.Handle, rhs.Handle, dir);
           else
                error('MHyProConstraintSet - contains_dir: Wrong argument.');
           end
       end

       function swap(obj, rhs1, rhs2)
           if isa(rhs1, 'MHyProConstraintSet') && isa(rhs2, 'MHyProConstraintSet')
                MHyPro('ConstraintSet', 'swap', obj.Handle, rhs1.Handle, rhs2.Handle);
           else
                error('MHyProObject - swap: Wrong argument.');
           end
       end

       function forceLinTransReduction(obj)
         	MHyPro('ConstraintSet', 'forceLinTransReduction', obj.Handle);
       end

       function out = collectProjections(obj)
         	out = MHyPro('ConstraintSet', 'collectProjections', obj.Handle);
       end
       
       function out = mtimes(obj, scalar)
            if isreal(scalar)
                ptr = MHyPro('ConstraintSet', '*', obj.Handle, scalar);
                out = MHyProBox(ptr);
            else
                error('MHyProConstraintSet - scale: Wrong type of argument.');
            end
       end
        
       function out = isAxisAligned(obj)
           out = MHyPro('ConstraintSet', 'isAxisAligned', obj.Handle);
       end
       
       function addConstraint(obj, vec, offset)
            if isvector(vec) && isreal(offset)
                MHyPro('ConstraintSet', 'addConstraint', obj.Handle, vec, offset);
            else
                error('MHyProConstraintSet - addConstraint: Wrong type of argument.');
            end
       end 

    end
end