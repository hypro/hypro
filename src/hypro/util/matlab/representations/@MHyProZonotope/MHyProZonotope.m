classdef MHyProZonotope < MHyProGeometricObject
    
    methods (Access = public)
        
        % Create a HyPro zonotope
        function obj = MHyProZonotope(varargin) 
            obj.Type = 14;
            if nargin == 0
                % Call default constructor
                obj.ObjectHandle = MHyPro(14, 121);
            elseif nargin == 1
                if isa(varargin{1}, 'uint64')
                    % This constructor is needed in case HyPro returns
                    % a new zonotope
                    obj.ObjectHandle = varargin{1};
                elseif isa(varargin{1}, 'MHyProZonotope')
                    % Call copy constructor
                    obj.ObjectHandle = MHyPro(14, 122, varargin{1}.ObjectHandle);
                else
                    error('MHyProZonotope - Constructor: Wrong type of argument.');
                end
            elseif nargin == 2
                if strcmp(varargin{1}, 'dimension') && mod(varargin{2}, 1) == 0
                    obj.ObjectHandle = MHyPro(14, 100, varargin{2});
                elseif isvector(varargin{1}) && ismatrix(varargin{2})
                    vec = conv2HyProVector(varargin{1});
                    obj.ObjectHandle = MHyPro(14, 101, vec, varargin{2});
                else
                    error('MHyProZonotope - Constructor: Wrong arguments.');
                end
            elseif nargin == 3
                
                if isa(varargin{1},'MHyProZonotope') && mod(varargin{2},1) == 0 && mod(varargin{3},1) == 0 &&...
                        varargin{2} ~= varargin{3}
                    maxDim = varargin{1}.dimension();       
                    if 0 <= varargin{2} && varargin{2} < maxDim && ...
                            0 <= varargin{3} && varargin{3} < maxDim
                        obj.ObjectHandle = MHyPro(14, 102, varargin{1}.ObjectHandle,varargin{2},varargin{3});
                    else
                        error('MHyProZonotope - Constructor: Wrong arguments.');
                    end
                else
                    error('MHyProZonotope - Constructor: Wrong arguments.');
                end
            else
                error('MHyProZonotope - Constructor: wrong arguments.');
            end
        end
        
        function out = supremum(obj)
            if ~obj.isempty()
                out = MHyPro(14, 103, obj.ObjectHandle);
            else
                out = NaN;
            end
        end
        
        function out = emptyAt(obj, dim)
            ptr = MHyPro(14, 104, obj.ObjectHandle,dim);
            out = MHyProZonotope(ptr);
        end
        
        function setCenter(obj, vec)
            if isvector(vec)
                vec = conv2HyProVector(vec);
            else
                error('MHyProZonotope - setCenter: Wrong type of argument.');
            end
            MHyPro(14, 105, obj.ObjectHandle, vec);
        end
        
        function setGenerators(obj, mat)
            if ismatrix(mat)
                MHyPro(14, 106, obj.ObjectHandle, mat);
            else
                error('MHyProZonotope - setGenerators: Wrong type of argument.');
            end
        end
        
        function out = addGenerators(obj,mat)
            if ismatrix(mat)
                out = MHyPro(14, 107, obj.ObjectHandle, mat);
            else
                error('MHyProZonotope - addGenerators: Wrong type of argument.');
            end
        end
        
        function out = center(obj)
            out = MHyPro(14, 108, obj.ObjectHandle);
        end
        
        function out = generators(obj)
            out = MHyPro(14, 109, obj.ObjectHandle);
        end
        
        function out = order(obj)
            out = MHyPro(14, 110, obj.ObjectHandle);
        end
        
        function removeEmptyGenerators(obj)
            MHyPro(14, 111, obj.ObjectHandle);
        end
        
        function uniteEqualVectors(obj)
            MHyPro(14, 112, obj.ObjectHandle);
        end
        
        function out = changeDimension(obj, new_dim)
            if mod(new_dim,1) == 0
               out = MHyPro(14, 113, obj.ObjectHandle, new_dim);
            else
                error('MHyProZonotope - changeDimension: Wrong type of argument.');
            end
        end
        
        function clear(obj)
            MHyPro(14, 114, obj.ObjectHandle);
        end
        
        function reduceOrder(obj, limit)
            if mod(limit,1) == 0
                MHyPro(14, 116, obj.ObjectHandle, limit);
            else
                error('MHyProZonotope - reduceOrder: Wrong type of argument.');
            end
        end
        
        function out = computeZonotopeBoundary(obj)
            out = MHyPro(14, 117, obj.ObjectHandle);
        end
        
        function out = intersectHalfspacesMethod(obj, normal_matrix, offset_vec, method)
            if ismatrix(normal_matrix) && isvector(offset_vec) && mod(method,1) == 0
                offset_vec = conv2HyProVector(offset_vec);
                ptr = MHyPro(14, 118, obj.ObjectHandle, normal_matrix, offset_vec, method);
                out = MHyProZonotope(ptr);
            else
                error('MHyProZonotope - intersectHalfspacesMethod: Wrong type of argument.');
            end
        end
        
        
        function out = intersectMinMax(obj, normal_vec, offset, matrix, method)
            if isvector(normal_vec) && isa(offset, 'double') && ismatrix(matrix) && mod(method,1) == 0
                normal_vec = conv2HyProVector(normal_vec);
                ptr = MHyPro(14, 119, obj.ObjectHandle, normal_vec, offset, matrix, method);
                out = MHyProZonotope(ptr);
            else
                error('MHyProZonotope - intersectMinMax: Wrong type of argument.');
            end
        end
        
        function out = intervaintervalHulllHull(obj)
            ptr = MHyPro(14, 120, obj.ObjectHandle);
            out = MHyProZonotope(ptr);
        end
        
        function out = type(obj)
            out = MHyPro(14, 123, obj.ObjectHandle);
        end
    end
end