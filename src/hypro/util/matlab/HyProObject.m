classdef HyProObject < handle
    properties (SetAccess = public, GetAccess = public)
        Type
        Pointer
    end
    
    methods (Access = private)
        % Delete a HyPro object - Destructor
        function delete(obj)
            if strcmp(obj.Type,'Box') || strcmp(obj.Type,'ConstraintSet')...
              || strcmp(obj.Type,'DifferenceBounds') || strcmp(obj.Type,'Ellipsoid')...
              || strcmp(obj.Type,'Polytope') || strcmp(obj.Type,'Polytopes')...
              || strcmp(obj.Type,'SupportFunction') || strcmp(obj.Type,'TaylorModel')...
              || strcmp(obj.Type,'Zonotope')
          
                MHyPro(obj.Type,'delete', obj.Pointer);
            else
                error('HyProObject - delete: Unknown object type.');
            end
        end
    end
    
    methods (Access = public)
        
        % Create a HyPro object
        function obj = HyProObject(varargin) 
            if strcmp(varargin{1},'Box') || strcmp(varargin{1},'ConstraintSet')...
              || strcmp(varargin{1},'DifferenceBounds') || strcmp(varargin{1},'Ellipsoid')...
              || strcmp(varargin{1},'Polytope') || strcmp(varargin{1},'Polytopes')...
              || strcmp(varargin{1},'SupportFunction') || strcmp(varargin{1},'TaylorModel')...
              || strcmp(varargin{1},'Zonotope')
          
                obj.Type = varargin{1};
            else
                error('HyProObject - Constructor: Unknown type.');
            end
                
            if nargin == 2
                if isa(varargin{2}, 'uint64')
                    obj.Pointer = varargin{2};
                else
                    obj.Pointer = MHyPro(varargin{1}, varargin{2});
                end
            elseif nargin == 3
                if strcmp(varargin{2},'copy')
                    obj.Pointer = MHyPro(varargin{1}, varargin{2}, varargin{3}.Pointer);
                else
                    obj.Pointer = MHyPro(varargin{1}, varargin{2}, varargin{3});
                end
            elseif nargin == 4
                obj.Pointer = MHyPro(varargin{1}, varargin{2}, varargin{3}, varargin{4});
            elseif nargin == 5
                obj.Pointer = MHyPro(varargin{1}, varargin{2}, varargin{3}, varargin{4}, varargin{5});
            elseif nargin == 6
                obj.Pointer = MHyPro(varargin{1}, varargin{2}, varargin{3}, varargin{4}, varargin{5}, varargin{6});
            end
        end

        
        function out = dimension(obj)
            if isa(obj, 'HyProObject')
                out = MHyPro(obj.Type, 'dimension', obj.Pointer);
            else
                error('HyProObject - dimension: Wrong type of input argument.');
            end
        end
        
        function out = getSettings(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'getSettings', obj.Pointer);
            else
                error('HyProObject - getSetting: Not allowed for this type of HyProObject');
            end
        end
        
        function out = empty(obj,dim)
            if isreal(dim)
                ptr = MHyPro(obj.Type, 'empty', obj.Pointer, dim);
                out = HyProObject(obj.Type, ptr);
            else
                error('HyProObject - empty: Wrong type of input argument.');
            end
        end
        
        function out = vertices(obj)
           out = MHyPro(obj.Type, 'vertices', obj.Pointer);
        end
       
        function [containment, out] = satisfiesHalfspace(obj, normal, offset)
            if isreal(normal) && isreal(offset)
                [containment, ptr] = MHyPro(obj.Type, 'satisfiesHalfspace', obj.Pointer, normal, offset);
                out = HyProObject(obj.Type, ptr);
            else
                error('HyProObject - satisfiesHalfspace: Wrong type of input argument.');
            end
        end
        
        function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
            if isreal(mat) && isreal(vec)
                [containment, ptr] = MHyPro(obj.Type, 'satisfiesHalfspace', obj.Pointer, mat, vec);
                out = HyProObject(obj.Type, ptr);
            else
                error('HyProObject - satisfiesHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = project(obj, dim)
            if isreal(dim)
                ptr = MHyPro(obj.Type, 'project', obj.Pointer, dim);
                out = HyProObject(obj.Type, ptr);
            else
                error('HyProObject - project: Wrong type of input argument.');
            end
        end
        
        function out = linearTransformation(obj, mat)
            if isreal(mat)
                ptr = MHyPro(obj.Type, 'linearTransformation', obj.Pointer, mat);
                out = HyProObject(obj.Type, ptr);
            else
                error('HyProObject - linearTransformation: Wrong type of input argument.');
            end
        end
        
        function out = affineTransformation(obj, mat, vec)
            if isreal(mat) && isreal(vec)
                ptr = MHyPro(obj.Type, 'affineTransformation', obj.Pointer, mat, vec);
                out = HyProObject(obj.Type, ptr);
            else
                error('HyProObject - affineTransformation: Wrong type of input argument.');
            end 
        end
        
        function out = plus(obj, rhs)
            if isa(rhs, 'HyProObject')
                ptr = MHyPro(obj.Type, 'minkowskiSum', obj.Pointer, rhs.Pointer);
                out = HyProObject(obj.Type, ptr);
            else
                error('HyProObject - minkowskiSum: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspace(obj, mat, vec)
            if isreal(mat) && isreal(vec)
                ptr = MHyPro(obj.Type, 'intersectHalfspace', obj.Pointer, mat, vec);
                out = HyProObject(obj.Type, ptr);
            else
                error('HyProObject - intersectHalfspace: Wrong type of input argument.');
            end
        end
        
        function out = contains(obj, arg)
            if isreal(arg)
                out = MHyPro(obj.Type, 'contains_point', obj.Pointer, arg);
            elseif isa(arg, 'HyProObject')
                out = MHyPro(obj.Type, 'contains', obj.Pointer, arg.Pointer);
            else
                error('HyProObject - contains: Wrong type of input argument.');
            end
        end
        
        function out = unite(obj, rhs)
            if isa(rhs, 'HyProObject') && strcmp(obj.Type, rhs.Type)
                ptr = MHyPro(obj.Type, 'unite', obj.Pointer, rhs.Pointer);
                out = HyProObject(obj.Type, ptr);
            elseif strcmp(obj.Type, 'Box') && iscell(rhs)
                objects = uint64.empty(length(rhs),0);
                for i = 1:length(rhs)
                    objects{i} = rhs{i}.Pointer;
                end
                ptr = MHyPro(obj.Type, 'unite_objects', obj.Pointer, objects{:});
                out = HyProObject(obj.Type, ptr);
            else
                error('HyProObject - unite: Wrong type of input argument.');
            end
        end
        
        function out = reduceRepresentation(obj)
            out = MHyPro(obj.Type, 'reduceRepresentation', obj.Pointer);
        end
        
        function ostream(obj)
            MHyPro(obj.Type, '<<', obj.Pointer);
        end
        
        function plot(obj, dims)
            if strcmp(obj.Type, 'Box')
                isempty = MHyPro(obj.Type, 'isEmpty', obj.Pointer);
                if isempty
                    warning('HyProObject - plot: It is not possible to plot an empty object.');
                else
                    %ver = MHyPro('Box', 'vertices', obj.Pointer);
                    
                    
                    
                    intervals = MHyPro('Box', 'intervals', obj.Pointer);
                    inter_1 = intervals(dims(1),:);
                    inter_2 = intervals(dims(2),:);
                    [dimy, dimx] = size(inter_1);
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
            else
                warning('HyProObject - plot: Not implemented yet.');
            end
        end
        
        function out = eq(obj, rhs)
            if isa(rhs, 'HyProObject')
                out = MHyPro(obj.Type, '==', obj.Pointer, rhs.Pointer);
            else
                error('HyProObject - equal: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = ne(obj, rhs)
            if isa(rhs, 'HyProObject')
                out = MHyPro(obj.Type, '!=', obj.Pointer, rhs.Pointer);
            else
                error('HyProObject - unequal: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = matrix(obj)
            out = MHyPro(obj.Type, 'matrix', obj.Pointer);
        end
        
        function out = vector(obj)
            if ~strcmp(obj.Type, 'Ellipse')
                out = MHyPro(obj.Type, 'vector', obj.Pointer);
            else
                error('HyProObject - insert: Not allowed for this type of HyProObject');
            end
        end
        
        function out = isempty(obj)
            out = MHyPro(obj.Type, 'isEmpty', obj.Pointer);
        end
        
        function out = removeRedundancy(obj)
            out = MHyPro(obj.Type, 'removeRedundancy', obj.Pointer);
        end
        
        function out = type(obj)
            out = MHyPro(obj.Type, 'type', obj.Pointer);
        end
        
        function out = reduceNumberRepresentation(obj)
            ptr = MHyPro(obj.Type, 'reduceNumberRepresentation', obj.Pointer);
            out = HyProObject('Box', ptr);
        end
        
        function out = clear(obj)
            out = MHyPro(obj.Type, 'clear', obj.Pointer, rhs.Pointer);
        end  
        
        %******************************************************************
        %               Object Specific Functions
        %******************************************************************
        
        % BOX
       
        function out = intervals(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'intervals', obj.Pointer);
            else
                error('HyProObject - intervals: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = limits(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'limits', obj.Pointer);
            else
                error('HyProObject - limits: Not allowed for this type of HyProObject.');
            end
        end
        
        function [containment, box] = constraints(obj)
            if strcmp(obj.Type, 'Box')
                [containment, box] = MHyPro(obj.Type, 'constraints', obj.Pointer);
            else
                error('HyProObject - constraints: Not allowed for this type of HyProObject.');
            end
        end
        
        function insert(obj, inter)
            if strcmp(obj.Type, 'Box') && isreal(inter)
                MHyPro(obj.Type, 'insert', obj.Pointer, inter);
            else
                error('HyProObject - insert: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = interval(obj, dim)
            if strcmp(obj.Type, 'Box') && isreal(dim)
                out = MHyPro(obj.Type, 'interval', obj.Pointer, dim);
            else
                error('HyProObject - interval: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = at(obj, dim)
            if strcmp(obj.Type, 'Box') && isreal(dim)
                out = MHyPro(obj.Type, 'at', obj.Pointer, dim);
            else
                error('HyProObject - at: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = isSymmetric(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'isSymmetric', obj.Pointer);
            else
                error('HyProObject - isSymmetric: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = max(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'max', obj.Pointer);
            else
                error('HyProObject - max: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = min(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'min', obj.Pointer);
            else
                error('HyProObject - min: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = supremum(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'supremum', obj.Pointer);
            else
                error('HyProObject - supremum: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = evaluate(obj, vec, dir)
            if strcmp(obj.Type, 'Box') && isreal(vec) && islogical(dir)
                out = MHyPro(obj.Type, 'evaluate', obj.Pointer, vec, dir);
            else
                error('HyProObject - evaluate: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = multiEvaluate(obj, mat, dir)
            if strcmp(obj.Type, 'Box') && isreal(mat) && islogical(dir)
                out = MHyPro(obj.Type, 'multiEvaluate', obj.Pointer, mat, dir);
            else
                error('HyProObject - multiEvaluate: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = mtimes(obj, scalar)
            if strcmp(obj.Type, 'Box') && isreal(scalar)
                ptr = MHyPro(obj.Type, '*', obj.Pointer, scalar);
                out = HyProObject('Box', ptr);
            else
                error('HyProObject - scale: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function makeSymmetric(obj)
            if strcmp(obj.Type, 'Box')
                MHyPro(obj.Type, 'makeSymmetric', obj.Pointer);
            else
                error('HyProObject - makeSymmetric: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = minkowskiDecomposition(obj, rhs)
            if strcmp(obj.Type, 'Box') && isa(rhs, 'HyProObject') && strcmp(rhs.Type, 'Box')
                ptr = MHyPro(obj.Type, 'minkowskiDecomposition', obj.Pointer, rhs.Pointer);
                out = HyProObject('Box', ptr);
            else
                error('HyProObject - minkowskiDecomposition: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = intersect(obj, rhs)
            if strcmp(obj.Type, 'Box') && isa(rhs, 'HyProObject') && strcmp(rhs.Type, 'Box')
                ptr = MHyPro(obj.Type, 'intersect', obj.Pointer, rhs.Pointer);
                out = HyProObject('Box', ptr);
            else
                error('HyProObject - intersect: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
       
       
       % ELLIPSOID
       
       function out = approxEllipsoidMatrix(obj, mat)
           if strcmp(obj.Type, 'Ellipsoid')
               out = MHyPro('Ellipsoid', 'approxEllipsoidTMatrix', obj.Pointer, mat);
           else
                error('HyProObject - approxEllipsoidMatrix: Not allowed for this type of HyProObject or wrong type of argument.');
           end
       end
       
       % CONSTRAINT SET
       
       function out = isAxisAligned(obj)
           if strcmp(obj.Type, 'ConstraintSet')
               out = MHyPro('ConstraintSet', 'isAxisAligned', obj.Pointer);
           else
               error('HyProObject - isAxisAligned: Not allowed for this type of HyProObject.');
           end
       end
       
       function addConstraint(obj, vec, off)
           if strcmp(obj.Type, 'ConstraintSet') && isreal(vec) && isreal(off)
                MHyPro('ConstraintSet', 'addConstraint', obj.Pointer, vec, off);
           else
                error('HyProObject - isAxisAligned: Not allowed for this type of HyProObject.');
           end
       end
       
%        function convert(obj, from, to, s)
%            if strcmp(obj.Type, 'ConstraintSet')
%                MHyPro('ConstraintSet', 'convert', obj.Pointer, from, to, s)
%            else
%                error('HyProObject - isAxisAligned: Not allowed for this type of HyProObject.');
%            end
%        end
       
       % SUPPORT FUNCTIONS
       
        
       
    end
end