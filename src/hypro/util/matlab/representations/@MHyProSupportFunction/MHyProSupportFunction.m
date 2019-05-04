classdef MHyProSupportFunction < MHyProGeometricObject

    methods (Access = public)
        
        % Create a HyPro support function
        function obj = MHyProSupportFunction(varargin) 
            obj.Type = 3;
            
            if nargin == 0
                % Call default constructor
                obj.Handle = MHyPro(3, 'new_empty');
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.Handle = varargin{1};
                elseif ismatrix(varargin{1})
                    % Construct using matrix
                    obj.Handle = MHyPro(3, 'new_matrix', varargin{1});
                elseif isa(varargin{1}, 'MHyProSupportFunction')
                    % Call copy constructor
                    obj.Handle = MHyPro(3, 'copy', varargin{1}.Handle);
                elseif ismatrix(varargin{1})
                    obj.Handle = MHyPro(3, 'new_matrix', varargin{1});
                else
                    error('MHyProSupportFunction - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if strcmp(varargin{1}, 'points') && ismatrix(varargin{2})
                    obj.Handle = MHyPro(3, 'new_points', varargin{2});
                elseif strcmp(varargin{1}, 'intervals') && areIntervals(varargin{2})
                    obj.Handle = MHyPro(3, 'new_intervals', varargin{2}); 
                elseif ismatrix(varargin{1}) && isvector(varargin{2})
                    obj.Handle = MHyPro(3, 'new_mat_vec', varargin{1}, varargin{2});
                else
                    error('MHyProSupportFunction - Constructor: Wrong arguments.');
                end
            elseif narargin == 3
                if strcmp(varargin{1}, 'halfspaces') && ismatrix(varargin{2}) && isvector(varargin{3})
                    % Construct form halfspaces
                    obj.Handle = MHyPro(3, 'new_halfspaces', varargin{2}, varargin{3});
                else
                    error('MHyProSupportFunction - Constructor: Wrong arguments.');
                end
            else
                error('MHyProSupportFunction - Constructor: wrong arguments.');
            end
        end

        function [containment, out] = satisfiesHalfspace(obj, normal, offset)
            if isvector(normal) && isreal(offset)
                [containment, ptr] = MHyPro(3, 'satisfiesHalfspace', obj.Handle, normal, offset);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - satisfiesHalfspace: Wrong type of input argument.');
            end
        end
        
        function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                [containment, ptr] = MHyPro(3, 'satisfiesHalfspace', obj.Handle, mat, vec);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - satisfiesHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = project(obj, dim)
            if isreal(dim)
                ptr = MHyPro(3, 'project', obj.Handle, dim);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - project: Wrong type of input argument.');
            end
        end
        
        function out = linearTransformation(obj, mat)
            if ismatrix(mat)
                ptr = MHyPro(3, 'linearTransformation', obj.Handle, mat);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - linearTransformation: Wrong type of input argument.');
            end
        end
        
        function out = affineTransformation(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro(3, 'affineTransformation', obj.Handle, mat, vec);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - affineTransformation: Wrong type of input argument.');
            end 
        end
        
        function out = plus(obj, rhs)
            if isa(rhs, 'MHyProSupportFunction')
                ptr = MHyPro(3, 'minkowskiSum', obj.Handle, rhs.Handle);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - minkowskiSum: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspace(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro(3, 'intersectHalfspace', obj.Handle, mat, vec);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - intersectHalfspace: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro(3, 'intersectHalfspaces', obj.Handle, mat, vec);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - intersectHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = contains(obj, arg)
            if isvector(arg)
                out = MHyPro(3, 'contains_vec', obj.Handle, arg);
            elseif isa(arg, 'MHyProSupportFunction')
                out = MHyPro(3, 'contains_set', obj.Handle, arg.Handle);
            else
                error('MHyProSupportFunction - contains: Wrong type of input argument.');
            end
        end
        
        function out = containsPoint(obj, pnt)
            if isvector(pnt)
                out = MHyPro(3, 'contains_point', obj.Handle, pnt);
            else
                error('MHyProSupportFunction - containsPoint: Wrong type of input argument.');
            end
        end
        
        function out = unite(obj, rhs)
            if isa(rhs, 'MHyProSupportFunction')
                ptr = MHyPro(3, 'unite', obj.Handle, rhs.Handle);
                out = MHyProSupportFunction(ptr);
            elseif iscell(rhs)
                objects = uint64.empty(length(rhs),0);
                for i = 1:length(rhs)
                    objects{i} = rhs{i}.Handle;
                end
                ptr = MHyPro(3, 'unite_objects', obj.Handle, objects{:});
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - unite: Wrong type of input argument.');
            end
        end

        function reduceNumberRepresentation(obj)
            MHyPro(3, 'reduceNumberRepresentation', obj.Handle);
        end

        function out = supremum(obj)
            if obj.Type == 3
                out = MHyPro(obj.Type, 'supremum', obj.Handle);
            else
                error('MHyProObject - supremum: Not allowed for this type of HyProObject.');
            end
        end

        function out = intersect(obj, rhs)
            if isa(rhs, 'MHyProSupportFunction') 
                ptr = MHyPro(3, 'intersect', obj.Handle, rhs.Handle);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - intersect: Wrong type of argument.');
            end
        end
        
        function cleanUp(obj)
            MHyPro(3, 'cleanUp', obj.Handle);
        end
       
        function out = depth(obj)
            out = MHyPro(3, 'depth', obj.Handle);
        end
       
        function out = operationCount(obj)
        	 out = MHyPro(3, 'operationCount', obj.Handle);
        end

        function out = contains_vec(obj, vec)
            if isvector(vec)
                 out = MHyPro(3, 'contains_vec', obj.Handle, vec);
            else
                 error('MHyProObject - contains_vec: Wrong argument.');
            end
        end

       function out = contains_dir(obj,rhs, dir)
           if isa(rhs, 'MHyProSupportFunction') && isreal(dir)
                out = MHyPro(3, 'contains_dir', obj.Handle, rhs.Handle, dir);
           else
                error('MHyProSupportFunction - contains_dir: Wrong argument.');
           end
       end

       function swap(obj, rhs1, rhs2)
           if isa(rhs1, 'MHyProSupportFunction') && isa(rhs2, 'MHyProSupportFunction')
                MHyPro(3, 'swap', obj.Handle, rhs1.Handle, rhs2.Handle);
           else
                error('MHyProObject - swap: Wrong argument.');
           end
       end

       function forceLinTransReduction(obj)
         	MHyPro(3, 'forceLinTransReduction', obj.Handle);
       end

       function out = collectProjections(obj)
         	out = MHyPro(3, 'collectProjections', obj.Handle);
       end
       
       function out = mtimes(obj, scalar)
            if isreal(scalar)
                ptr = MHyPro(3, '*', obj.Handle, scalar);
                out = MHyProBox(ptr);
            else
                error('MHyProSupportFunction - scale: Wrong type of argument.');
            end
       end        
    end
end