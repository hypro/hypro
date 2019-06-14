classdef MHyProBox < MHyProGeometricObject
    
    
%     methods (Static)
% 
%         function out = uniteMultiple(objects)
%             if iscell(objects)
%                 objectPtrs = cell(1, length(objects));
%                 for i = 1:length(objects)
%                     if isa(objects{i}, 'MHyProBox')
%                         objectPtrs{i} = objects{i}.ObjectHandle;
%                     else
%                         error('MHyProBox - uniteMultiple: Wrong type of input argument.');
%                     end
%                 end
%                 ptr = MHyPro(0, 33, objectPtrs);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - uniteMultiple: Wrong type of input argument.');
%             end
%         end
%         
%     end
    
    methods (Access = public)
        
        % Create a HyPro box
        function obj = MHyProBox(varargin) 
            obj.Type = 0;
            if nargin == 0
                % Call default constructor
                obj.ObjectHandle = MHyPro(0, 100);
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    % This constructor is needed in case HyPro returns
                    % a new box
                    obj.ObjectHandle = varargin{1};
                elseif isa(varargin{1}, 'MHyProBox')
                    % Call copy constructor
                    obj.ObjectHandle = MHyPro(0, 101, varargin{1}.ObjectHandle);
                else
                    error('MHyProBox - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if strcmp(varargin{1}, 'points') && ismatrix(varargin{2})
                    obj.ObjectHandle = MHyPro(0, 102, varargin{2});
                elseif strcmp(varargin{1}, 'interval') && checkIntervals(varargin{2})
                    obj.ObjectHandle = MHyPro(0, 103, varargin{2});
                elseif strcmp(varargin{1}, 'intervals') && checkIntervals(varargin{2})
                    obj.ObjectHandle = MHyPro(0, 104, varargin{2});
                elseif ismatrix(varargin{1})
                    if isvector(varargin{2})
                        varargin{2} = conv2HyProVector(varargin{2});
                    else
                        error('MHyProBox - Constructor: Wrong type of input argument.');
                    end
                    obj.ObjectHandle = MHyPro(0, 105, varargin{1}, varargin{2});
                else
                    error('MHyProBox - Constructor: Wrong arguments.');
                end
            else
                error('MHyProBox - Constructor: wrong arguments.');
            end
        end
                        
        function out = empty(obj,dim)
            if mod(dim, 1) == 0
                ptr = MHyPro(0, 106, obj.ObjectHandle, dim);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - empty: Wrong type of input argument.');
            end
        end
       
%         function [containment, out] = satisfiesHalfspace(obj, normal, offset)
%             if isvector(normal)
%                 normal = conv2HyProVector(normal);
%             else
%                 error('MHyProBox - affineTransformation: Wrong type of input argument.');
%             end
%             if isreal(offset)
%                 [containment, ptr] = MHyPro(0, 14, obj.ObjectHandle, normal, offset);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - satisfiesHalfspace: Wrong type of input argument.');
%             end
%         end
%         
%         function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
%             if isvector(vec)
%                 vec = conv2HyProVector(vec);
%             else
%                 error('MHyProBox - affineTransformation: Wrong type of input argument.');
%             end
%             if ismatrix(mat) && size(mat,2) == size(vec,1)
%                 [containment, ptr] = MHyPro(0, 15, obj.ObjectHandle, mat, vec);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - satisfiesHalfspaces: Wrong type of input argument.');
%             end
%         end
        
%         function out = project(obj, dim)
%             if isvector(dim)
%                 dim = conv2HyProVector(dim);
%             else
%                 error('MHyProBox - project: Wrong type of input argument.');
%             end
%             max = obj.dimension();
%             if size(dim, 1) <= max
%                 for i = 1:length(dim)
%                     dim(i) = dim(i)-1;
%                 end
%                 ptr = MHyPro(0, 24, obj.ObjectHandle, dim);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - project: Wrong type of input argument.');
%             end
%         end
        
%         function out = linearTransformation(obj, mat)
%             if ismatrix(mat)
%                 ptr = MHyPro(0, 25, obj.ObjectHandle, mat);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - linearTransformation: Wrong type of input argument.');
%             end
%         end
%         
%         function out = affineTransformation(obj, mat, vec)
%             if isvector(vec)
%                 vec = conv2HyProVector(vec);
%             else
%                 error('MHyProBox - affineTransformation: Wrong type of input argument.');
%             end
%    
%             if ismatrix(mat) && size(mat,2) == size(vec,1)
%                 ptr = MHyPro(0, 26, obj.ObjectHandle, mat, vec);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - affineTransformation: Wrong type of input argument.');
%             end 
%         end
%         
%         function out = plus(obj, rhs)
%             if isa(rhs, 'MHyProBox')
%                 ptr = MHyPro(0, 27, obj.ObjectHandle, rhs.ObjectHandle);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - minkowskiSum: Wrong type of input argument.');
%             end
%         end
%         
%         function out = intersectHalfspace(obj, nor, off)
%             if isvector(nor)
%                 nor = conv2HyProVector(nor);
%             else
%                 error('MHyProBox - intersectHalfspace: Wrong type of input argument.');
%             end
% 
%             if isreal(off)
%                 ptr = MHyPro(0, 28, obj.ObjectHandle, nor, off);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - intersectHalfspace: Wrong type of input argument.');
%             end
%         end
%         
%         function out = intersectHalfspaces(obj, mat, vec)
%             if isvector(vec)
%                 vec = conv2HyProVector(vec);
%             else
%                 error('MHyProBox - intersectHalfspaces: Wrong type of input argument.');
%             end
%             
%             if ismatrix(mat) && size(mat,2) == size(vec,1)
%                 ptr = MHyPro(0, 29, obj.ObjectHandle, mat, vec);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - intersectHalfspaces: Wrong type of input argument.');
%             end
%         end
% 
%         function out = contains(obj, arg)
%             if isreal(arg)
%                 out = MHyPro(0, 30, obj.ObjectHandle, arg);
%             elseif isa(arg, 'MHyProBox')
%                 out = MHyPro(0, 31, obj.ObjectHandle, arg.ObjectHandle);
%             else
%                 error('MHyProBox - contains: Wrong type of input argument.');
%             end
%         end
%  
%         function out = reduceNumberRepresentation(obj)
%             ptr = MHyPro(0, 34, obj.ObjectHandle);
%             out = MHyProBox(ptr);
%         end
        
        function out = intervals(obj)
            out = MHyPro(0, 107, obj.ObjectHandle);
        end
        
        function out = limits(obj)
            out = MHyPro(0, 108, obj.ObjectHandle);
        end
        
        function [containment, box] = constraints(obj)
            [containment, box] = MHyPro(obj.Type, 109, obj.ObjectHandle);
        end
        
        function insert(obj, inter)
            if checkIntervals(inter)
                MHyPro(0, 110, obj.ObjectHandle, inter);
            else
                error('MHyProBox - insert: Wrong type of argument.');
            end
        end
        
        function out = interval(obj, dim)
            if mod(dim, 1) == 0 && dim >= 1
                out = MHyPro(0, 111, obj.ObjectHandle, dim);
            else
                error('MHyProBox - interval: Wrong type of argument.');
            end
        end
        
        function out = at(obj, dim)
            if mod(dim, 1) == 0
                out = MHyPro(0, 112, obj.ObjectHandle, dim);
            else
                error('MHyProBox - at: Wrong type of argument.');
            end
        end
        
        function out = isSymmetric(obj)
            out = MHyPro(0, 113, obj.ObjectHandle);
        end
        
        function out = max(obj)
            out = MHyPro(0, 114, obj.ObjectHandle);
        end
        
        function out = min(obj)
            out = MHyPro(0, 115, obj.ObjectHandle);
        end
        
        function out = supremum(obj)
            out = MHyPro(obj.Type, 116, obj.ObjectHandle);
        end
        
        function out = mtimes(obj, scalar)
            if isreal(scalar)
                ptr = MHyPro(0, 117, obj.ObjectHandle, scalar);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - scale: Wrong type of argument.');
            end
        end
        
        function out = makeSymmetric(obj)
            ptr = MHyPro(0, 118, obj.ObjectHandle);
            out = MHyProBox(ptr);
        end
        
        function out = minkowskiDecomposition(obj, rhs)
            if isa(rhs, 'MHyProBox')
                ptr = MHyPro(obj.Type, 119, obj.ObjectHandle, rhs.ObjectHandle);
                out = MHyProBox(ptr);
            else
                error('MHyProBox - minkowskiDecomposition: Wrong type of argument.');
            end
        end
        
        function out = clear(obj)
            out = MHyPro(obj.Type, 120, obj.ObjectHandle, rhs.ObjectHandle);
        end
        
        
%         function out = intersect(obj, rhs)
%             if isa(rhs, 'MHyProBox') 
%                 ptr = MHyPro(0, 48, obj.ObjectHandle, rhs.ObjectHandle);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - intersect: Wrong type of argument.');
%             end
%         end
%         
%         function out = unite(obj, rhs)
%             if isa(rhs, 'MHyProBox')
%                 ptr = MHyPro(0, 32, obj.ObjectHandle, rhs.ObjectHandle);
%                 out = MHyProBox(ptr);
%             else
%                 error('MHyProBox - unite: Wrong type of input argument.');
%             end
%         end

    end
end