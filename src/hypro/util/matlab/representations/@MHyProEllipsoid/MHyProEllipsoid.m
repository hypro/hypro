classdef MHyProEllipsoid < MHyProGeometricObject

    methods (Access = public)

        % Create a HyPro Ellipsoid
        function obj = MHyProEllipsoid(varargin)
            obj.Type = 1;

            if nargin == 1
                if isa(varargin{1}, 'uint64')
                    % This constructor is needed in case HyPro returns
                    % a new ellipsoid
                    obj.ObjectHandle = varargin{1};
                elseif isa(varargin{1}, 'MHyProEllipsoid')
                    % Call copy constructor
                    obj.ObjectHandle = MHyPro(1, 15, varargin{1}.ObjectHandle);
                elseif ismatrix(varargin{1})
                    % Construct using matrix
                    obj.ObjectHandle = MHyPro(1, 16, varargin{1});
                else
                    error('MHyProEllipsoid - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if isreal(varargin{1}) && mod(varargin{2}, 1) == 0
                    % Construct using radius
                    obj.ObjectHandle = MHyPro(1, 17, varargin{1}, varargin{2});
                else
                    error('MHyProEllipsoid - Constructor: Wrong type of argument.');
                end
            else
                error('MHyProEllipsoid - Constructor: Wrong arguments.');
            end
        end

        function out = linearTransformation(obj, mat)
            if ismatrix(mat)
                ptr = MHyPro(1, 18, obj.ObjectHandle, mat);
                out = MHyProEllipsoid(ptr);
            else
                error('MHyProEllipsoid - linearTransformation: Wrong type of input argument.');
            end
        end

        function out = affineTransformation(obj, mat, vec)
            if ismatrix(mat) && isvector(vec) && size(mat,2) == size(vec,1)
                ptr = MHyPro(1, 19, obj.ObjectHandle, mat, vec);
                out = MHyProEllipsoid(ptr);
            else
                error('MHyProEllipsoid - affineTransformation: Wrong type of input argument.');
            end
        end

        function out = plus(obj, rhs)
            if isa(rhs, 'MHyProEllipsoid')
                ptr = MHyPro(1, 20, obj.ObjectHandle, rhs.ObjectHandle);
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
               out = MHyPro(1, 21, obj.ObjectHandle, mat);
           else
                error('MHyProEllipsoid - approxEllipsoidMatrix: Wrong type of argument.');
           end
        end

        function out = projectOn(obj)
            error('MHyProEllipsoid - project: Not implemented');
        end

        function out = satisfiesHalfspaces(obj)
            error('MHyProEllipsoid - satisfiesHalfspaces: Not implemented.');
        end

        function out = satisfiesHalfspace(obj)
            error('MHyProEllipsoid - satisfiesHalfsapce: Not implemented');
        end
    end
end