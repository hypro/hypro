classdef MHyProSupportFunction < MHyProGeometricObject
    
    
%     methods (Static)
% 
%         function out = uniteMultiple(objects)
%             if iscell(objects)
%                 objectPtrs = cell(1, length(objects));
%                 for i = 1:length(objects)
%                     if isa(objects{i}, 'MHyProSupportFunction')
%                         objectPtrs{i} = objects{i}.ObjectHandle;
%                     else
%                         error('MHyProSupportFunction - uniteMultiple: Wrong type of input argument.');
%                     end
%                 end
%                 
%                 ptr = MHyPro(3, 34, objectPtrs);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - uniteMultiple: Wrong type of input argument.');
%             end
%         end
%         
%     end

    methods (Access = public)
        
        % Create a HyPro support function
        function obj = MHyProSupportFunction(varargin) 
            obj.Type = 3;
            
            if nargin == 0
                % Call default constructor
                obj.ObjectHandle = MHyPro(3, 100);
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.ObjectHandle = varargin{1};
                elseif ismatrix(varargin{1})
                    % Construct using matrix
                    obj.ObjectHandle = MHyPro(3, 101, varargin{1});
                elseif isa(varargin{1}, 'MHyProSupportFunction')
                    % Call copy constructor
                    obj.ObjectHandle = MHyPro(3, 102, varargin{1}.ObjectHandle);
                else
                    error('MHyProSupportFunction - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if strcmp(varargin{1}, 'points') && ismatrix(varargin{2})
                    obj.ObjectHandle = MHyPro(3, 103, varargin{2});
                elseif strcmp(varargin{1}, 'intervals') && areIntervals(varargin{2})
                    obj.ObjectHandle = MHyPro(3, 104, varargin{2}); 
                elseif ismatrix(varargin{1}) && isvector(varargin{2})
                    if isvector(varargin{2})
                        varargin{2} = conv2HyProVector(varargin{2});
                    else
                        error('MHyProConstraintSet - Constructor: Wrong type of argument.');
                    end
                    obj.ObjectHandle = MHyPro(3, 105, varargin{1}, varargin{2});
                else
                    error('MHyProSupportFunction - Constructor: Wrong arguments.');
                end
            elseif narargin == 3
                if strcmp(varargin{1}, 'halfspaces') && ismatrix(varargin{2})
                    if isvector(varargin{3})
                        varargin{3} = conv2HyProVector(varargin{3});
                    else
                        error('MHyProSupportFunction - Constructor: Wrong type of argument.');
                    end
                    % Construct form halfspaces
                    obj.ObjectHandle = MHyPro(3, 106, varargin{2}, varargin{3});
                else
                    error('MHyProSupportFunction - Constructor: Wrong arguments.');
                end
            else
                error('MHyProSupportFunction - Constructor: wrong arguments.');
            end
        end

%         function [containment, out] = satisfiesHalfspace(obj, normal, offset)
%             if isvector(normal) && isreal(offset)
%                 [containment, ptr] = MHyPro(3, 22, obj.ObjectHandle, normal, offset);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - satisfiesHalfspace: Wrong type of input argument.');
%             end
%         end
%         
%         function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
%             if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
%                 [containment, ptr] = MHyPro(3, 23, obj.ObjectHandle, mat, vec);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - satisfiesHalfspaces: Wrong type of input argument.');
%             end
%         end
        
%         function out = project(obj, dim)
%             if isreal(dim)
%                 ptr = MHyPro(3, 24, obj.ObjectHandle, dim);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - project: Wrong type of input argument.');
%             end
%         end
%         
%         function out = linearTransformation(obj, mat)
%             if ismatrix(mat)
%                 ptr = MHyPro(3, 25, obj.ObjectHandle, mat);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - linearTransformation: Wrong type of input argument.');
%             end
%         end
%         
%         function out = affineTransformation(obj, mat, vec)
%             if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
%                 ptr = MHyPro(3, 26, obj.ObjectHandle, mat, vec);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - affineTransformation: Wrong type of input argument.');
%             end 
%         end
%         
%         function out = plus(obj, rhs)
%             if isa(rhs, 'MHyProSupportFunction')
%                 ptr = MHyPro(3, 27, obj.ObjectHandle, rhs.ObjectHandle);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - minkowskiSum: Wrong type of input argument.');
%             end
%         end
%         
%         function out = intersectHalfspace(obj, mat, vec)
%             if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
%                 ptr = MHyPro(3, 28, obj.ObjectHandle, mat, vec);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - intersectHalfspace: Wrong type of input argument.');
%             end
%         end
%         
%         function out = intersectHalfspaces(obj, mat, vec)
%             if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
%                 ptr = MHyPro(3, 29, obj.ObjectHandle, mat, vec);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - intersectHalfspaces: Wrong type of input argument.');
%             end
%         end
%         
%         function out = contains(obj, arg)
%             if isvector(arg)
%                 out = MHyPro(3, 30, obj.ObjectHandle, arg);
%             elseif isa(arg, 'MHyProSupportFunction')
%                 out = MHyPro(3, 31, obj.ObjectHandle, arg.ObjectHandle);
%             else
%                 error('MHyProSupportFunction - contains: Wrong type of input argument.');
%             end
%         end
        
        function out = containsPoint(obj, pnt)
            if isvector(pnt)
                pnt = conv2HyProVector(pnt);
                out = MHyPro(3, 107, obj.ObjectHandle, pnt);
            else
                error('MHyProSupportFunction - containsPoint: Wrong type of argument.');
            end
        end
        
%         function out = unite(obj, rhs)
%             if isa(rhs, 'MHyProSupportFunction')
%                 ptr = MHyPro(3, 33, obj.ObjectHandle, rhs.ObjectHandle);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - unite: Wrong type of input argument.');
%             end
%         end
% 
%         function reduceNumberRepresentation(obj)
%             MHyPro(3, 35, obj.ObjectHandle);
%         end

        function out = supremum(obj)
            if obj.Type == 3
                out = MHyPro(obj.Type, 108, obj.ObjectHandle);
            else
                error('MHyProObject - supremum: Not allowed for this type of HyProObject.');
            end
        end

%         function out = intersect(obj, rhs)
%             if isa(rhs, 'MHyProSupportFunction') 
%                 ptr = MHyPro(3, 37, obj.ObjectHandle, rhs.ObjectHandle);
%                 out = MHyProSupportFunction(ptr);
%             else
%                 error('MHyProSupportFunction - intersect: Wrong type of argument.');
%             end
%         end
        
        function cleanUp(obj)
            MHyPro(3, 109, obj.ObjectHandle);
        end
       
        function out = depth(obj)
            out = MHyPro(3, 110, obj.ObjectHandle);
        end
       
        function out = operationCount(obj)
        	 out = MHyPro(3, 111, obj.ObjectHandle);
        end

       function out = contains_dir(obj,rhs, dir)
           if isa(rhs, 'MHyProSupportFunction') && isreal(dir)
                out = MHyPro(3, 112, obj.ObjectHandle, rhs.ObjectHandle, dir);
           else
                error('MHyProSupportFunction - contains_dir: Wrong argument.');
           end
       end

       function swap(obj, rhs1, rhs2)
           if isa(rhs1, 'MHyProSupportFunction') && isa(rhs2, 'MHyProSupportFunction')
                MHyPro(3, 113, obj.ObjectHandle, rhs1.ObjectHandle, rhs2.ObjectHandle);
           else
                error('MHyProObject - swap: Wrong argument.');
           end
       end

       function forceLinTransReduction(obj)
         	MHyPro(3, 114, obj.ObjectHandle);
       end

       function out = collectProjections(obj)
         	out = MHyPro(3, 115, obj.ObjectHandle);
       end
       
       function out = mtimes(obj, scalar)
            if isreal(scalar)
                ptr = MHyPro(3, 116, obj.ObjectHandle, scalar);
                out = MHyProBox(ptr);
            else
                error('MHyProSupportFunction - scale: Wrong type of argument.');
            end
       end        
    end
end