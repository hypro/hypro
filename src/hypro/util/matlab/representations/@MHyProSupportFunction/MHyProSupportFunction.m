classdef MHyProSupportFunction < MHyProGeometricObject

    methods (Access = public)
        
        % Create a HyPro support function
        function obj = MHyProSupportFunction(varargin) 
            obj.Type = 'SupportFunction';
            
            if nargin == 0
                % Call default constructor
                obj.Handle = MHyPro('SupportFunction', 'new_empty');
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.Handle = varargin{1};
                elseif ismatrix(varargin{1})
                    % Construct using matrix
                    obj.Handle = MHyPro('SupportFunction', 'new_matrix', varargin{1});
                elseif isa(varargin{1}, 'MHyProSupportFunction')
                    % Call copy constructor
                    obj.Handle = MHyPro('SupportFunction', 'copy', varargin{1}.Handle);
                elseif ismatrix(varargin{1})
                    obj.Handle = MHyPro('SupportFunction', 'new_matrix', varargin{1});
                else
                    error('MHyProSupportFunction - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if strcmp(varargin{1}, 'points') && ismatrix(varargin{2})
                    obj.Handle = MHyPro('SupportFunction', 'new_points', varargin{2});
                elseif strcmp(varargin{1}, 'intervals') && areIntervals(varargin{2})
                    obj.Handle = MHyPro('SupportFunction', 'new_intervals', varargin{2}); 
                elseif ismatrix(varargin{1}) && isvector(varargin{2})
                    obj.Handle = MHyPro('SupportFunction', 'new_mat_vec', varargin{1}, varargin{2});
                else
                    error('MHyProSupportFunction - Constructor: Wrong arguments.');
                end
            elseif narargin == 3
                if strcmp(varargin{1}, 'halfspaces') && ismatrix(varargin{2}) && isvector(varargin{3})
                    % Construct form halfspaces
                    obj.Handle = MHyPro('SupportFunction', 'new_halfspaces', varargin{2}, varargin{3});
                else
                    error('MHyProSupportFunction - Constructor: Wrong arguments.');
                end
            else
                error('MHyProSupportFunction - Constructor: wrong arguments.');
            end
        end

        function [containment, out] = satisfiesHalfspace(obj, normal, offset)
            if isvector(normal) && isreal(offset)
                [containment, ptr] = MHyPro('SupportFunction', 'satisfiesHalfspace', obj.Handle, normal, offset);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - satisfiesHalfspace: Wrong type of input argument.');
            end
        end
        
        function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                [containment, ptr] = MHyPro('SupportFunction', 'satisfiesHalfspace', obj.Handle, mat, vec);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - satisfiesHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = project(obj, dim)
            if isreal(dim)
                ptr = MHyPro('SupportFunction', 'project', obj.Handle, dim);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - project: Wrong type of input argument.');
            end
        end
        
        function out = linearTransformation(obj, mat)
            if ismatrix(mat)
                ptr = MHyPro('SupportFunction', 'linearTransformation', obj.Handle, mat);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - linearTransformation: Wrong type of input argument.');
            end
        end
        
        function out = affineTransformation(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro('SupportFunction', 'affineTransformation', obj.Handle, mat, vec);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - affineTransformation: Wrong type of input argument.');
            end 
        end
        
        function out = plus(obj, rhs)
            if isa(rhs, 'MHyProSupportFunction')
                ptr = MHyPro('SupportFunction', 'minkowskiSum', obj.Handle, rhs.Handle);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - minkowskiSum: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspace(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro('SupportFunction', 'intersectHalfspace', obj.Handle, mat, vec);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - intersectHalfspace: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro('SupportFunction', 'intersectHalfspaces', obj.Handle, mat, vec);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - intersectHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = contains(obj, arg)
            if isvector(arg)
                out = MHyPro('SupportFunction', 'contains_vec', obj.Handle, arg);
            elseif isa(arg, 'MHyProSupportFunction')
                out = MHyPro('SupportFunction', 'contains_set', obj.Handle, arg.Handle);
            else
                error('MHyProSupportFunction - contains: Wrong type of input argument.');
            end
        end
        
        function out = containsPoint(obj, pnt)
            if isvector(pnt)
                out = MHyPro('SupportFunction', 'contains_point', obj.Handle, pnt);
            else
                error('MHyProSupportFunction - containsPoint: Wrong type of input argument.');
            end
        end
        
        function out = unite(obj, rhs)
            if isa(rhs, 'MHyProSupportFunction')
                ptr = MHyPro('SupportFunction', 'unite', obj.Handle, rhs.Handle);
                out = MHyProSupportFunction(ptr);
            elseif iscell(rhs)
                objects = uint64.empty(length(rhs),0);
                for i = 1:length(rhs)
                    objects{i} = rhs{i}.Handle;
                end
                ptr = MHyPro('SupportFunction', 'unite_objects', obj.Handle, objects{:});
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - unite: Wrong type of input argument.');
            end
        end

        function reduceNumberRepresentation(obj)
            MHyPro('SupportFunction', 'reduceNumberRepresentation', obj.Handle);
        end

        function out = supremum(obj)
            if strcmp(obj.Type, 'SupportFunction') || strcmp(obj.Type, 'SupportFunction')
                out = MHyPro(obj.Type, 'supremum', obj.Handle);
            else
                error('MHyProObject - supremum: Not allowed for this type of HyProObject.');
            end
        end

        function out = intersect(obj, rhs)
            if isa(rhs, 'MHyProSupportFunction') 
                ptr = MHyPro('SupportFunction', 'intersect', obj.Handle, rhs.Handle);
                out = MHyProSupportFunction(ptr);
            else
                error('MHyProSupportFunction - intersect: Wrong type of argument.');
            end
        end
        
        function cleanUp(obj)
            MHyPro('SupportFunction', 'cleanUp', obj.Handle);
        end
       
        function out = depth(obj)
            out = MHyPro('SupportFunction', 'depth', obj.Handle);
        end
       
        function out = operationCount(obj)
        	 out = MHyPro('SupportFunction', 'operationCount', obj.Handle);
        end

        function out = contains_vec(obj, vec)
            if isvector(vec)
                 out = MHyPro('SupportFunction', 'contains_vec', obj.Handle, vec);
            else
                 error('MHyProObject - contains_vec: Wrong argument.');
            end
        end

       function out = contains_dir(obj,rhs, dir)
           if isa(rhs, 'MHyProSupportFunction') && isreal(dir)
                out = MHyPro('SupportFunction', 'contains_dir', obj.Handle, rhs.Handle, dir);
           else
                error('MHyProSupportFunction - contains_dir: Wrong argument.');
           end
       end

       function swap(obj, rhs1, rhs2)
           if isa(rhs1, 'MHyProSupportFunction') && isa(rhs2, 'MHyProSupportFunction')
                MHyPro('SupportFunction', 'swap', obj.Handle, rhs1.Handle, rhs2.Handle);
           else
                error('MHyProObject - swap: Wrong argument.');
           end
       end

       function forceLinTransReduction(obj)
         	MHyPro('SupportFunction', 'forceLinTransReduction', obj.Handle);
       end

       function out = collectProjections(obj)
         	out = MHyPro('SupportFunction', 'collectProjections', obj.Handle);
       end
       
       function out = mtimes(obj, scalar)
            if isreal(scalar)
                ptr = MHyPro('SupportFunction', '*', obj.Handle, scalar);
                out = MHyProBox(ptr);
            else
                error('MHyProSupportFunction - scale: Wrong type of argument.');
            end
       end        
    end
end