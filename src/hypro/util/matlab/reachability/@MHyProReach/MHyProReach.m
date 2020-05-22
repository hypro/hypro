classdef MHyProReach < handle
    
    properties (SetAccess = public, GetAccess = public)
        ObjectHandle
    end
    
    methods (Access = private)
        
        % Destructor
        function delete(obj)
            MHyPro(12, 1, obj.ObjectHandle);
        end
        
    end
    
    methods (Access = public)
        
        % Constructor
        function obj = MHyProReach(varargin)
            if nargin == 1 && isa(varargin{1}, 'MHyProHAutomaton')
                obj.ObjectHandle = MHyPro(12, 2, varargin{1}.ObjectHandle);
            else
                error('MHyProReach - Constructor: Wrong type of at least one argument.');
            end
        end
        
        function out = computeForwardReachability(obj)
            flowpipes = MHyPro(12, 3, obj.ObjectHandle);
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
                            && ~strcmp(currentField, 'fileName') && ~strcmp(currentField, 'clustering')
                        error(['MHyProReach - setSettings: Unknown field name ', currentField]);
                    end
                end
                MHyPro(12, 4, obj.ObjectHandle, settings);
            else
                error('MHyProReach - setSettings: Wrong type of at least one argument.');
            end       
        end
        
        function setRepresentationType(obj, type)
            %0 = box, 1 = carl_polytope, 2 = constraint_set
            % 3 = polytope_h, 4 = polytope_v
            % 5 = ppl_polytope, 6 = support_function, 7 = taylor_model
            % 8 = zonotope, 9 = difference_bounds, 
            if type >= 0 && type <= 9
                MHyPro(12, 5, obj.ObjectHandle, type);
            else
                error('MHyProReach - setRepresentationType: Wrong type of at least one argument.');
            end
        end
        
        function settings(obj)
             MHyPro(12, 6, obj.ObjectHandle);
        end
        
        function out = reachedBadStates(obj)
            out = MHyPro(12, 7, obj.ObjectHandle);
        end
         
        function plot(obj, flowpipes, dims, labs, save,path, name, ext)
            num_flowpipes = length(flowpipes);
            fig = figure();
            
            %disp(['Reach - plot: number of flowpipes: ', num2str(num_flowpipes)])
            for pipe = 1:num_flowpipes
                currentFlowpipe =  flowpipes{pipe};
                num_states = length(currentFlowpipe);
                %disp(['Reach - plot: number of states: ', num2str(num_states)]);
                
                for state = 1:num_states
                    currentState = currentFlowpipe{state};
                    warning('');
                    vertices = currentState.vertices(0);
                    [msgstr, ~] = lastwarn;
                    if isempty(msgstr)
                        obj.plotVertices(vertices, dims);
                    end
                    hold on
                end 
                hold on
                xlabel(labs(1));
                ylabel(labs(2));
                if save
                    fname = strcat(name,'.',ext);
                    saveas(fig, fullfile(path,fname),ext);
                end
            end
        end
        
        function plotVertices(obj, vertices, dims)
            %Compute projection
            first = vertices(dims(1),:);
            second = vertices(dims(2),:);
            temp = [first;second];
            ver = unique(temp.','rows').';
            ver_x = ver(1,:);
            ver_y = ver(2,:);
            cx = mean(ver_x);
            cy = mean(ver_y);
            a = atan2(ver_y - cy, ver_x - cx);
            [~, order] = sort(a);
            ver_x = ver_x(order);
            ver_y = ver_y(order);
            P = [ver_x;ver_y]';
            pgon = polyshape(P, 'Simplify', false);
            plot(pgon,'FaceColor',[0.2 0.55 0.74], 'EdgeColor', [0.070, 0.250, 0.972]);           
        end
                
        function plotBadStates3D(obj, normalMat, offsetVec, dims, x, y)
            hold on
            for i = 1:size(normalMat,1)
                normal = normalMat(i,1:(size(normalMat,2)));
                A = normal(dims(1));
                B = normal(dims(2));
                D = offsetVec(i);
                ineq = A*x + B*y <= D;
                f = double(ineq);
                surf(x,y,f, 'FaceAlpha',0.5, 'EdgeColor','none', 'FaceColor',[0.831, 0, 0]);
            end
            hold off
        end
        
        function plot3D(obj, flowpipes, dims, labs, save,path, name, ext)
            num_flowpipes = length(flowpipes);
            fig = figure();
            %disp(['Reach - plot3D: number of flowpipes: ', num2str(num_flowpipes)])
            for pipe = 1:num_flowpipes
                currentFlowpipe =  flowpipes{pipe};
                num_states = length(currentFlowpipe);
                %disp(['Reach - plot3D - number of states: ', num2str(num_states)]);
                for state = 1:num_states
                    currentState = currentFlowpipe{state};
                    vertices = currentState.vertices(0);
                    obj.plot3DVertices(vertices, dims);
                    hold on
                end 
                hold on
                xlabel(labs(1));
                ylabel(labs(2));
                zlabel(labs(3));
                if save
                    fname = strcat(name,'.',ext);
                    saveas(fig, fullfile(path,fname),ext);
                end
            end
        end
        
        function plot3DVertices(obj, vertices, dims)
            %Compute projection
            x = vertices(dims(1),:);
            y = vertices(dims(2),:);
            z = vertices(dims(3),:);
            
            cx = mean(x);
            cy = mean(y);
            a = atan2(y - cy, x - cx);
            mat = [x;y;z;a];
            [~, idx] = sort(mat(4,:));
            ordered = mat(:,idx);
            
            x = ordered(1,:);
            y = ordered(2,:);
            z = ordered(3,:);
            
            cy = mean(y);
            cz = mean(z);
            a = atan2(z-cz,y- cy);
            mat = [x;y;z;a];
            [~,idx] = sort(mat(4,:));
            ordered = mat(:,idx);
            
            x = ordered(1,:);
            y = ordered(2,:);
            z = ordered(3,:);
            
            h = fill3(x,y,z, [0.2 0.55 0.74]);
            set(h,'edgecolor',[0.070, 0.250, 0.972]);
        end
        
        function out = verify(obj, flowpipes, specMatrix)
            out = 1;
            num_flowpipes = length(flowpipes);
            cols = size(specMatrix,2);
            linComb = specMatrix(:,1:cols-1);
            rhs = specMatrix(:,cols);
            for pipe = 1:num_flowpipes
                currentFlowpipe = flowpipes{pipe};
                num_states = length(currentFlowpipe);
                for state = 1:num_states
                    currentState = currentFlowpipe{state};
                    vertices = currentState.vertices(0);
                    for s = 1:size(specMatrix,1)
                        for v = 1:size(vertices,2)
                            value = linComb(s,:) * vertices(:,v);
                            if value > rhs(s)
                                %disp(['NOT SAFE - spec. no. ' num2str(s) ' violated following specification: [' num2str(linComb(s,:)) '] <= ' num2str(rhs(s))]) ;
                                out = 0;
                            end
                            if out == 0
                                break;
                            end
                        end
                        if out == 0
                            break;
                        end
                    end
                    if out == 0
                        break;
                    end
                end
                if out == 0
                    break;
                end
            end
        end 
        
        
        function plotComparison(obj, flowpipes, dims, labs)
            num_flowpipes = length(flowpipes);
            %disp(['Reach - plot: number of flowpipes: ', num2str(num_flowpipes)])
            for pipe = 1:num_flowpipes
                currentFlowpipe =  flowpipes{pipe};
                num_states = length(currentFlowpipe);
                %disp(['Reach - plot: number of states: ', num2str(num_states)]);
                
                for state = 1:num_states
                    currentState = currentFlowpipe{state};
                    warning('');
                    vertices = currentState.vertices(0);
                    [msgstr, ~] = lastwarn;
                    if isempty(msgstr)
                        obj.plotVerticesComparison(vertices, dims);
                    end
                    hold on
                end 
                hold on
                xlabel(labs(1));
                ylabel(labs(2));
            end
        end
        
        function plotVerticesComparison(obj, vertices, dims)
            %Compute projection
            first = vertices(dims(1),:);
            second = vertices(dims(2),:);
            temp = [first;second];
            ver = unique(temp.','rows').';
            ver_x = ver(1,:);
            ver_y = ver(2,:);
            cx = mean(ver_x);
            cy = mean(ver_y);
            a = atan2(ver_y - cy, ver_x - cx);
            [~, order] = sort(a);
            ver_x = ver_x(order);
            ver_y = ver_y(order);
            P = [ver_x;ver_y]';
            pgon = polyshape(P, 'Simplify', false);
            plot(pgon,'FaceColor','none', 'EdgeColor', [0.098, 0.784, 0.286]);           
        end
        
    end
    
end