classdef MHyProEllipsoid < MHyProGeometricObject

    methods (Access = public)
        
        % Create a HyPro Ellipsoid
        function obj = MHyProEllipsoid(varargin) 
            obj.Type = 1;
            
            if nargin == 1
                if isa(varargin{1}, 'uint64')
                    % This constructor is needed in case HyPro returns
                    % a new ellipsoid
                    obj.Handle = varargin{1};
                elseif isa(varargin{1}, 'MHyProEllipsoid')
                    % Call copy constructor
                    obj.Handle = MHyPro(1, 'copy', varargin{1}.Handle);
                elseif ismatrix(varargin{1})
                    % Construct using matrix
                    obj.Handle = MHyPro(1, 'new_mat', varargin{1});
                else
                    error('MHyProEllipsoid - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if isreal(varargin{1}) && mod(varargin{2}, 1) == 0
                    % Construct using radius
                    obj.Handle = MHyPro(1, 'new_rad', varargin{1}, varargin{2});
                else
                    error('MHyProEllipsoid - Constructor: Wrong type of argument.');
                end
            else
                error('MHyProEllipsoid - Constructor: Wrong arguments.');
            end
        end
                               
        function [containment, out] = satisfiesHalfspace(obj, normal, offset)
            if isvector(normal) && isreal(offset)
                [containment, ptr] = MHyPro(1, 'satisfiesHalfspace', obj.Handle, normal, offset);
                out = MHyProEllipsoid(ptr);
            else
                error('MHyProEllipsoid - satisfiesHalfspace: Wrong type of input argument.');
            end
        end
        
        function [containment, out] = satisfiesHalfspaces(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                [containment, ptr] = MHyPro(1, 'satisfiesHalfspace', obj.Handle, mat, vec);
                out = MHyProEllipsoid(ptr);
            else
                error('MHyProEllipsoid - satisfiesHalfspaces: Wrong type of input argument.');
            end
        end
        
        function out = project(obj, dim)
            if isreal(dim)
                ptr = MHyPro(1, 'project', obj.Handle, dim);
                out = MHyProEllipsoid(ptr);
            else
                error('MHyProEllipsoid - project: Wrong type of input argument.');
            end
        end
        
        function out = linearTransformation(obj, mat)
            if ismatrix(mat)
                ptr = MHyPro(1, 'linearTransformation', obj.Handle, mat);
                out = MHyProEllipsoid(ptr);
            else
                error('MHyProEllipsoid - linearTransformation: Wrong type of input argument.');
            end
        end
        
        function out = affineTransformation(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro(1, 'affineTransformation', obj.Handle, mat, vec);
                out = MHyProEllipsoid(ptr);
            else
                error('MHyProEllipsoid - affineTransformation: Wrong type of input argument.');
            end 
        end
        
        function out = plus(obj, rhs)
            if isa(rhs, 'MHyProEllipsoid')
                ptr = MHyPro(1, 'minkowskiSum', obj.Handle, rhs.Handle);
                out = MHyProEllipsoid(ptr);
            else
                error('MHyProEllipsoid - minkowskiSum: Wrong type of input argument.');
            end
        end
                 
        function plot(obj, dims)
            error('MHyProEllipsoid - plot: NOT IMPLEMENTED');
        end

        function out = approxEllipsoidMatrix(obj, mat)
           if ismatrix(mat)
               out = MHyPro(1, 'approxEllipsoidTMatrix', obj.Handle, mat);
           else
                error('MHyProEllipsoid - approxEllipsoidMatrix: Wrong type of argument.');
           end
        end
    end
end