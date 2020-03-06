classdef MHyProConstraintSet < MHyProGeometricObject

    methods (Access = public)
        
        % Create a HyPro constraint set
        function obj = MHyProConstraintSet(varargin) 
            obj.Type = 2;
            
            if nargin == 0
                % Call default constructor
                obj.ObjectHandle = MHyPro(2, 100);
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    obj.ObjectHandle = varargin{1};
                elseif isa(varargin{1}, 'MHyProConstraintSet')
                    % Call copy constructor
                    obj.ObjectHandle = MHyPro(2, 101, varargin{1}.ObjectHandle);
                else
                    error('MHyProConstraintSet - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if isvector(varargin{2})
                    varargin{2} = conv2HyProVector(varargin{2});
                else
                    error('MHyProConstraintSet - Constructor: Wrong type of argument.');
                end
                if ismatrix(varargin{1}) && size(varargin{1},1) == size(varargin{2},1)
                    obj.ObjectHandle = MHyPro(2, 102, varargin{1}, varargin{2});
                else
                    error('MHyProConstraintSet - Constructor: Wrong arguments.');
                end
            else
                error('MHyProConstraintSet - Constructor: wrong arguments.');
            end
        end

       function out = containsPoint(obj, pnt)
            if isvector(pnt)
                pnt = conv2HyProVector(pnt);
                out = MHyPro(2, 103, obj.ObjectHandle, pnt);
            else
                error('MHyProConstraintSet- containsPoint: Wrong type of argument.');
            end
       end
        
       function out = isAxisAligned(obj)
           out = MHyPro(2, 104, obj.ObjectHandle);
       end
       
       function addConstraint(obj, vec, offset)
            if isvector(vec) && isreal(offset)
                MHyPro(2, 105, obj.ObjectHandle, vec, offset);
            else
                error('MHyProConstraintSet - addConstraint: Wrong type of argument.');
            end
       end
       
       
       
    end
end