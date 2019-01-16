classdef MHyProObject < handle
    properties (SetAccess = public, GetAccess = public)
        Type
        Handle
    end
    
    methods (Access = private)
        % Delete a MHyPro object - Destructor
        function delete(obj)
            if strcmp(obj.Type,'Box') || strcmp(obj.Type,'ConstraintSet')...
              || strcmp(obj.Type,'DifferenceBounds') || strcmp(obj.Type,'Ellipsoid')...
              || strcmp(obj.Type,'Polytope') || strcmp(obj.Type,'Polytopes')...
              || strcmp(obj.Type,'SupportFunction') || strcmp(obj.Type,'TaylorModel')...
              || strcmp(obj.Type,'Zonotope')
          
                MHyPro(obj.Type,'delete', obj.Handle);
            else
                error('MHyProObject - delete: Unknown object type.');
            end
        end
    end
    
    methods (Access = public)
        
        % Create a HyPro object
        function obj = MHyProObject(varargin) 
            if strcmp(varargin{1},'Box') || strcmp(varargin{1},'ConstraintSet')...
              || strcmp(varargin{1},'DifferenceBounds') || strcmp(varargin{1},'Ellipsoid')...
              || strcmp(varargin{1},'Polytope') || strcmp(varargin{1},'Polytopes')...
              || strcmp(varargin{1},'SupportFunction') || strcmp(varargin{1},'TaylorModel')...
              || strcmp(varargin{1},'Zonotope')
          
                obj.Type = varargin{1};
            else
                error('MHyProObject - Constructor: Unknown type.');
            end
                
            if nargin == 2
                if isa(varargin{2}, 'uint64')
                    obj.Handle = varargin{2};
                else
                    obj.Handle = MHyPro(varargin{1}, varargin{2});
                end
            elseif nargin == 3
                if strcmp(varargin{2},'copy')
                    obj.Handle = MHyPro(varargin{1}, varargin{2}, varargin{3}.Handle);
                else
                    obj.Handle = MHyPro(varargin{1}, varargin{2}, varargin{3});
                end
            elseif nargin == 4
                obj.Handle = MHyPro(varargin{1}, varargin{2}, varargin{3}, varargin{4});
            elseif nargin == 5
                obj.Handle = MHyPro(varargin{1}, varargin{2}, varargin{3}, varargin{4}, varargin{5});
            elseif nargin == 6
                obj.Handle = MHyPro(varargin{1}, varargin{2}, varargin{3}, varargin{4}, varargin{5}, varargin{6});
            end
        end

        
        function out = dimension(obj)
            if isa(obj, 'MHyProObject')
                out = MHyPro(obj.Type, 'dimension', obj.Handle);
            else
                error('MHyProObject - dimension: Wrong type of input argument.');
            end
        end
        
        function out = test(obj, set)
            if strcmp(obj.Type, 'Box')
                 
                 out = MHyPro(obj.Type, 'Test', obj.Handle, set);
                %disp('Handle: ');
%                 disp(temp);
% %                 [a, len] = size(temp);
%                 disp(a);
%                 disp(len);
%                  out = cell(size(len));
%                 for i = 1:(len)
%                     %disp(temp{i});
% %                     MHyProObject('Box', temp{i});
% %                     out{i} = MHyProObject(obj.Type, temp{i});
%                 end
                %outt = 1;
            else
                error('MHyProObject - getSetting: Not allowed for this type of HyProObject');
            end
        end
        
        function out = empty(obj,dim)
            if isreal(dim)
                ptr = MHyPro(obj.Type, 'empty', obj.Handle, dim);
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - empty: Wrong type of input argument.');
            end
        end
        
        function out = vertices(obj)
           out = MHyPro(obj.Type, 'vertices', obj.Handle);
        end
       
        function [containment, out] = satisfiesHalfspace(obj, normal, offset)
            if isreal(normal) && isreal(offset)
                [containment, ptr] = MHyPro(obj.Type, 'satisfiesHalfspace', obj.Handle, normal, offset);
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - satisfiesHalfspace: Wrong type of input argument.');
            end
        end
        
        function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
            if isreal(mat) && isreal(vec)
                [containment, ptr] = MHyPro(obj.Type, 'satisfiesHalfspace', obj.Handle, mat, vec);
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - satisfiesHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = project(obj, dim)
            if isreal(dim)
                ptr = MHyPro(obj.Type, 'project', obj.Handle, dim);
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - project: Wrong type of input argument.');
            end
        end
        
        function out = linearTransformation(obj, mat)
            if isreal(mat)
                ptr = MHyPro(obj.Type, 'linearTransformation', obj.Handle, mat);
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - linearTransformation: Wrong type of input argument.');
            end
        end
        
        function out = affineTransformation(obj, mat, vec)
            if isreal(mat) && isreal(vec)
                ptr = MHyPro(obj.Type, 'affineTransformation', obj.Handle, mat, vec);
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - affineTransformation: Wrong type of input argument.');
            end 
        end
        
        function out = plus(obj, rhs)
            if isa(rhs, 'MHyProObject')
                ptr = MHyPro(obj.Type, 'minkowskiSum', obj.Handle, rhs.Handle);
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - minkowskiSum: Wrong type of input argument.');
            end
        end
        
        function out = intersectHalfspace(obj, mat, vec)
            if isreal(mat) && isreal(vec)
                ptr = MHyPro(obj.Type, 'intersectHalfspace', obj.Handle, mat, vec);
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - intersectHalfspace: Wrong type of input argument.');
            end
        end
        
        function out = contains(obj, arg)
            if isreal(arg)
                out = MHyPro(obj.Type, 'contains_point', obj.Handle, arg);
            elseif isa(arg, 'MHyProObject')
                out = MHyPro(obj.Type, 'contains_set', obj.Handle, arg.Handle);
            else
                error('MHyProObject - contains: Wrong type of input argument.');
            end
        end
        
        function out = unite(obj, rhs)
            if isa(rhs, 'MHyProObject') && strcmp(obj.Type, rhs.Type)
                ptr = MHyPro(obj.Type, 'unite', obj.Handle, rhs.Handle);
                out = MHyProObject(obj.Type, ptr);
            elseif iscell(rhs)
                objects = uint64.empty(length(rhs),0);
                for i = 1:length(rhs)
                    objects{i} = rhs{i}.Handle;
                end
                ptr = MHyPro(obj.Type, 'unite_objects', obj.Handle, objects{:});
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - unite: Wrong type of input argument.');
            end
        end
        
        function reduceRepresentation(obj)
            MHyPro(obj.Type, 'reduceRepresentation', obj.Handle);
        end
        
        function ostream(obj)
            MHyPro(obj.Type, '<<', obj.Handle);
        end
        
        function plot(obj, dims)
            if strcmp(obj.Type, 'Box')
                isempty = MHyPro(obj.Type, 'isEmpty', obj.Handle);
                if isempty
                    warning('MHyProObject - plot: It is not possible to plot an empty object.');
                else
                    %ver = MHyPro('Box', 'vertices', obj.Handle);
                    
                    
                    
                    intervals = MHyPro('Box', 'intervals', obj.Handle);
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
                warning('MHyProObject - plot: Not implemented yet.');
            end
        end
        
        function out = size(obj)
            out = MHyPro(obj.Type, 'size', obj.Handle);
        end
        
        function out = eq(obj, rhs)
            if isa(rhs, 'MHyProObject')
                out = MHyPro(obj.Type, '==', obj.Handle, rhs.Handle);
            else
                error('MHyProObject - equal: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = ne(obj, rhs)
            if ~strcmp(obj.Type, 'SupportFunction') &&isa(rhs, 'MHyProObject')
                out = MHyPro(obj.Type, '!=', obj.Handle, rhs.Handle);
            else
                error('MHyProObject - unequal: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = matrix(obj)
            out = MHyPro(obj.Type, 'matrix', obj.Handle);
        end
        
        function out = vector(obj)
            if ~strcmp(obj.Type, 'Ellipse')
                out = MHyPro(obj.Type, 'vector', obj.Handle);
            else
                error('HyProObject - insert: Not allowed for this type of HyProObject');
            end
        end
        
        function out = isempty(obj)
            out = MHyPro(obj.Type, 'isEmpty', obj.Handle);
        end
        
        function out = removeRedundancy(obj)
            out = MHyPro(obj.Type, 'removeRedundancy', obj.Handle);
        end
        
        function out = type(obj)
            out = MHyPro(obj.Type, 'type', obj.Handle);
        end
        
        function out = reduceNumberRepresentation(obj)
            ptr = MHyPro(obj.Type, 'reduceNumberRepresentation', obj.Handle);
            out = MHyProObject(obj.Type, ptr);
        end
        
        function out = clear(obj)
            out = MHyPro(obj.Type, 'clear', obj.Handle, rhs.Handle);
        end  
        
        %******************************************************************
        %               Object Specific Functions
        %******************************************************************
        
        % BOX
       
        function out = intervals(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'intervals', obj.Handle);
            else
                error('MHyProObject - intervals: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = limits(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'limits', obj.Handle);
            else
                error('MHyProObject - limits: Not allowed for this type of HyProObject.');
            end
        end
        
        function [containment, box] = constraints(obj)
            if strcmp(obj.Type, 'Box')
                [containment, box] = MHyPro(obj.Type, 'constraints', obj.Handle);
            else
                error('MHyProObject - constraints: Not allowed for this type of HyProObject.');
            end
        end
        
        function insert(obj, inter)
            if strcmp(obj.Type, 'Box') && isreal(inter)
                MHyPro(obj.Type, 'insert', obj.Handle, inter);
            else
                error('MHyProObject - insert: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = interval(obj, dim)
            if strcmp(obj.Type, 'Box') && isreal(dim)
                out = MHyPro(obj.Type, 'interval', obj.Handle, dim);
            else
                error('MHyProObject - interval: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = at(obj, dim)
            if strcmp(obj.Type, 'Box') && isreal(dim)
                out = MHyPro(obj.Type, 'at', obj.Handle, dim);
            else
                error('MHyProObject - at: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = isSymmetric(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'isSymmetric', obj.Handle);
            else
                error('MHyProObject - isSymmetric: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = max(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'max', obj.Handle);
            else
                error('MHyProObject - max: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = min(obj)
            if strcmp(obj.Type, 'Box')
                out = MHyPro(obj.Type, 'min', obj.Handle);
            else
                error('MHyProObject - min: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = supremum(obj)
            if strcmp(obj.Type, 'Box') || strcmp(obj.Type, 'SupportFunction')
                out = MHyPro(obj.Type, 'supremum', obj.Handle);
            else
                error('MHyProObject - supremum: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = evaluate(obj, vec, dir)
            if strcmp(obj.Type, 'Box') && isreal(vec) && islogical(dir)
                out = MHyPro(obj.Type, 'evaluate', obj.Handle, vec, dir);
            else
                error('MHyProObject - evaluate: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = multiEvaluate(obj, mat, dir)
            if strcmp(obj.Type, 'Box') && isreal(mat) && islogical(dir)
                out = MHyPro(obj.Type, 'multiEvaluate', obj.Handle, mat, dir);
            else
                error('MHyProObject - multiEvaluate: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = mtimes(obj, scalar)
            if (strcmp(obj.Type, 'Box') || strcmp(obj.Type, 'SupportFunction')) && isreal(scalar)
                ptr = MHyPro(obj.Type, '*', obj.Handle, scalar);
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - scale: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function makeSymmetric(obj)
            if strcmp(obj.Type, 'Box')
                MHyPro(obj.Type, 'makeSymmetric', obj.Handle);
            else
                error('MHyProObject - makeSymmetric: Not allowed for this type of HyProObject.');
            end
        end
        
        function out = minkowskiDecomposition(obj, rhs)
            if strcmp(obj.Type, 'Box') && isa(rhs, 'MHyProObject') && strcmp(rhs.Type, 'Box')
                ptr = MHyPro(obj.Type, 'minkowskiDecomposition', obj.Handle, rhs.Handle);
                out = MHyProObject('Box', ptr);
            else
                error('MHyProObject - minkowskiDecomposition: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
        function out = intersect(obj, rhs)
            if (strcmp(obj.Type, 'Box') || strcmp(obj.Type, 'SupportFunction')) && isa(rhs, 'MHyProObject') && (strcmp(rhs.Type, 'Box')|| strcmp(rhs.Type, 'SupportFunction'))
                ptr = MHyPro(obj.Type, 'intersect', obj.Handle, rhs.Handle);
                out = MHyProObject(obj.Type, ptr);
            else
                error('MHyProObject - intersect: Not allowed for this type of HyProObject or wrong type of argument.');
            end
        end
        
       
       
       % ELLIPSOID
       
       function out = approxEllipsoidMatrix(obj, mat)
           if strcmp(obj.Type, 'Ellipsoid')
               out = MHyPro('Ellipsoid', 'approxEllipsoidTMatrix', obj.Handle, mat);
           else
                error('MHyProObject - approxEllipsoidMatrix: Not allowed for this type of HyProObject or wrong type of argument.');
           end
       end
       
       % CONSTRAINT SET
       
       function out = isAxisAligned(obj)
           if strcmp(obj.Type, 'ConstraintSet')
               out = MHyPro('ConstraintSet', 'isAxisAligned', obj.Handle);
           else
               error('MHyProObject - isAxisAligned: Not allowed for this type of HyProObject.');
           end
       end
       
       function addConstraint(obj, vec, off)
           if strcmp(obj.Type, 'ConstraintSet') && isreal(vec) && isreal(off)
                MHyPro('ConstraintSet', 'addConstraint', obj.Handle, vec, off);
           else
                error('MHyProObject - isAxisAligned: Not allowed for this type of HyProObject.');
           end
       end
       
%        function convert(obj, from, to, s)
%            if strcmp(obj.Type, 'ConstraintSet')
%                MHyPro('ConstraintSet', 'convert', obj.Handle, from, to, s)
%            else
%                error('HyProObject - isAxisAligned: Not allowed for this type of HyProObject.');
%            end
%        end
       
       % SUPPORT FUNCTIONS
       
       function cleanUp(obj)
           if strcmp(obj.Type, 'SupportFunction')
                MHyPro('SupportFunction', 'cleanUp', obj.Handle);
           else
                error('MHyProObject - cleanUp: Not allowed for this type of HyProObject.');
           end
       end
       
       function out = depth(obj)
           if strcmp(obj.Type, 'SupportFunction')
                out = MHyPro('SupportFunction', 'depth', obj.Handle);
           else
                error('MHyProObject - depth: Not allowed for this type of HyProObject.');
           end
       end
       
       function out = operationCount(obj)
           if strcmp(obj.Type, 'SupportFunction')
                out = MHyPro('SupportFunction', 'operationCount', obj.Handle);
           else
                error('MHyProObject - operationCount: Not allowed for this type of HyProObject.');
           end
       end
      
       function out = contains_vec(obj, vec)
           if strcmp(obj.Type, 'SupportFunction') && isreal(vec)
                out = MHyPro(obj.Type, 'contains_vec', obj.Handle, vec);
           else
                error('MHyProObject - contains_vec: Not allowed for this type of HyProObject or wrong argument.');
           end
       end
       
       function out = contains_dir(obj,rhs, dir)
           if strcmp(obj.Type, 'SupportFunction') && isa(rhs,'MHyProObject') && strcmp(rhs.Type, 'SupportFunction') && isreal(dir)
                out = MHyPro(obj.Type, 'contains_dir', obj.Handle, rhs.Handle, dir);
           else
                error('MHyProObject - contains_dir: Not allowed for this type of HyProObject.');
           end
       end
       
       function swap(obj, rhs1, rhs2)
           if strcmp(obj.Type, 'SupportFunction') && isa(rhs1, 'MHyProObject') && strcmp(rhs1.Type, 'SupportFunction')...
                   && isa(rhs2, 'MHyProObject') && strcmp(rhs2.Type, 'SupportFunction')
                MHyPro(obj.Type, 'swap', obj.Handle, rhs1.Handle, rhs2.Handle);
           else
                error('MHyProObject - swap: Not allowed for this type of HyProObject.');
           end
       end
       
       function forceLinTransReduction(obj)
           if strcmp(obj.Type, 'SupportFunction')
                MHyPro(obj.Type, 'forceLinTransReduction', obj.Handle);
           else
                error('MHyProObject - forceLinTransReduction: Not allowed for this type of HyProObject.');
           end
       end
       
       function out = multiplicationsPerEvaluation(obj)
           if strcmp(obj.Type, 'SupportFunction')
                MHyPro(obj.Type, 'multiplicationsPerEvaluation', obj.Handle);
                out = 1;
           else
                error('MHyProObject - multiplicationsPerEvaluation: Not allowed for this type of HyProObject.');
           end
       end
       
       function out = collectProjections(obj)
           if strcmp(obj.Type, 'SupportFunction')
                out = MHyPro(obj.Type, 'collectProjections', obj.Handle);
           else
                error('MHyProObject - collectProjections: Not allowed for this type of HyProObject.');
           end
       end
       
       function evaluateTemplate(obj, dir, force)
           if strcmp(obj.Type, 'SupportFunction') && isreal(dir) && isreal(force)
                MHyPro(obj.Type, 'evaluateTemplate', obj.Handle, dir, force);
           else
                error('MHyProObject - evaluateTemplate: Not allowed for this type of HyProObject.');
           end
       end
       
    end
end