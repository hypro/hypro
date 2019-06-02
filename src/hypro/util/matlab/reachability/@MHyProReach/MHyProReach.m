classdef MHyProReach < handle
    
    properties (SetAccess = public, GetAccess = public)
        Handle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro(12, 1, obj.Handle);
        end
        
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProReach(varargin)
            if nargin == 1 && isa(varargin{1}, 'MHyProHAutomaton')
                obj.Handle = MHyPro(12, 2, varargin{1}.Handle);
            else
                error('MHyProReach - Constructor: Wrong type of at least one argument.');
            end
        end
        
        function out = computeForwardReachability(obj)
            flowpipes = MHyPro(12, 3, obj.Handle);
            out = cell(1, length(flowpipes));
                for i = 1:length(flowpipes)
                    states = flowpipes(i).flowpipe;
                    fPipe = cell(1,length(states));
                    for j = 1:length(states)
                        if isa(states{j}, 'uint64')
                            fPipe{j} = MHyProState(states{j});
                        else
                            error('MHyProReach - computeForwardReach: Wrong type of input argument.');
                        end
                    end
                    out{i} = fPipe;
                end 
        end
        
        function setSettings(obj, settings)
            if isstruct(settings)
                fields = fieldnames(settings);         
                for i = 1:length(fields)
                    currentField = fields{i};
                    if ~strcmp(currentField, 'timeBound') && ~strcmp(currentField, 'jumpDepth')...
                            && ~strcmp(currentField, 'timeStep') && ~strcmp(currentField, 'plotDimensions')...
                            && ~strcmp(currentField, 'pplDenomimator') && ~strcmp(currentField, 'uniformBloating')...
                            && ~strcmp(currentField, 'fileName')
                        error(['MHyProReach - setSettings: Unknown field name ', currentField]);
                    end
                end
                MHyPro(12, 4, obj.Handle, settings);
            else
                error('MHyProReach - setSettings: Wrong type of at least one argument.');
            end       
        end
        
        function setRepresentationType(obj, type)
            % MHyProBox=0, MHyProConstraintSet = 1, MHyProSupportFunction = 2
            if type == 0 || type == 1 || type == 2
                MHyPro(12, 5, obj.Handle, type);
            else
                error('MHyProReach - setRepresentationType: Wrong type of at least one argument.');
            end
        end
        
        function settings(obj)
            MHyPro(12, 6, obj.Handle);
        end
        
         function plotVertices(obj, vertices, dims)
            %Compute projection
            temp = vertices(dims(1):dims(2),:);
            ver = unique(temp.','rows').';
            ver_x = ver(1,:);
            ver_y = ver(2,:);
            cx = mean(ver_x);
            cy = mean(ver_y);
            a = atan2(ver_y - cy, ver_x - cx);
            [~, order] = sort(a);
            ver_x = ver_x(order);
            ver_y = ver_y(order);

            pgon = polyshape(ver_x, ver_y);
            plot(pgon);           
        end
        
        function plot(obj, flowpipes, type, dims)
            num_flowpipes = length(flowpipes);
            for pipe = 1:num_flowpipes
                currentFlowpipe =  flowpipes{pipe};
                num_states = length(currentFlowpipe);
                disp(['Number of states: ', num2str(num_states)]);
                figure()
                for state = 1:num_states
                    currentState = currentFlowpipe{state};
                    vertices = currentState.vertices(1);
                    obj.plotVertices(vertices, dims);
                    hold on
                end  
            end
        end
        
        function plot3D(obj, flowpipes, type, dims)
            num_flowpipes = length(flowpipes);
            for pipe = 1:num_flowpipes
                currentFlowpipe =  flowpipes{pipe};
                num_states = length(currentFlowpipe);
                disp(['Number of states: ', num2str(num_states)]);
                figure()
                for state = 1:num_states
                    currentState = currentFlowpipe{state};
                    vertices = currentState.vertices(1);
                    obj.plotVertices(vertices, dims);
                    hold on
                end  
            end
        end
        
    end
    
end