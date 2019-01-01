classdef HyProEvaluationResult < handle
    properties (Access = private)
        Pointer
    end
    
    methods
        % Create a HyPro object
        function obj = HyProEvaluationResult() 
            obj.Pointer = MHyPro('EvaluationResult', 'newEv');
        end
        
        % Delete a HyPro object - Destructor
        function delete(obj)
           MHyPro('EvaluationResult','delete', obj.Pointer);
        end
               
    end
end