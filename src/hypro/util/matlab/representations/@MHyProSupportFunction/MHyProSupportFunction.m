classdef MHyProSupportFunction < MHyProGeometricObject

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
                elseif strcmp(varargin{1}, 'intervals') && checkIntervals(varargin{2})
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
        
        function out = containsPoint(obj, pnt)
            if isvector(pnt)
                pnt = conv2HyProVector(pnt);
                out = MHyPro(3, 107, obj.ObjectHandle, pnt);
            else
                error('MHyProSupportFunction - containsPoint: Wrong type of argument.');
            end
        end

        function reduceNumberRepresentation(obj)
            MHyPro(3, 24, obj.ObjectHandle);
        end

        function out = supremum(obj)
            if obj.Type == 3
                out = MHyPro(obj.Type, 108, obj.ObjectHandle);
            else
                error('MHyProObject - supremum: Not allowed for this type of HyProObject.');
            end
        end
        
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