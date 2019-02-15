function res = flowTest

linFlow_empty = MHyProFlow('linearFlow');

empty_mat = linFlow_empty.getFlowMatrix();
disp('getFlowMatrix():');
disp(empty_mat);

flowMatrix = [1 2 0; 3 4 1; 1 0 0];
linFlow_mat = MHyProFlow('linearFlow', flowMatrix);

out = linFlow_mat.hasNoFlow();
disp(['hasNoFlow(): ', num2str(out)]);

size = linFlow_mat.size();
disp(['size(): ', num2str(size)]);





res = 1