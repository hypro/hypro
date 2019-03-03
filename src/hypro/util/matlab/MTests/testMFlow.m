function res = testMFlow

linFlow = MHyProFlow('linearFlow');

% Check if it has flow
flow = linFlow.hasNoFlow();
% assert(flow == 0); ---> ?

% Add flow matrix to linFlow
flowMatrix = [1 2 0; 3 4 1; 1 0 1];
linFlow.setFlowMatrix(flowMatrix);
mat = linFlow.getFlowMatrix();
assert(isequal(flowMatrix, mat));

% Check dimension (num. columns - 1)
dim = linFlow.dimension();
assert(dim == 2);

% Add new row for flow
linFlow.addRow([1 2 2]);
mat = linFlow.getFlowMatrix();
% assert(isequal(mat, [1 2 0 1; 3 4 1 2; 1 0 1 3; 1 2 1])); ---> ?

% Check if is identity
linFlow1 = MHyProFlow('linearFlow', [1 2 0; 3 4 1; 1 0 1]);
id = linFlow1.isIdentity();
assert(id == 0); 

% Check if is timed
timed = linFlow1.isTimed();
assert(timed == 0);

% Check if is discrete
dis = linFlow1.isDiscrete();
assert(dis == 0);

% Check if are equal
equal = (linFlow == linFlow1);
assert(equal == 0);
linFlow = MHyProFlow('linearFlow', linFlow1);
equal = (linFlow == linFlow1);
assert(equal == 1);

% Check if are unequal
nequal = (linFlow ~= linFlow1);
% assert(nequal == 1); ---> ?
nequal = (linFlow ~= flow);
assert(nequal == 1);


affineFlowEmpt = MHyProFlow('affineFlow');
affineFlow = MHyProFlow('affineFlow', [1 2; 3 4], [1; 1]);

tran = affineFlowEmpt.hasTranslation();
assert(tran == 0);
tran = affineFlow.hasTranslation();
assert(tran == 1);

affineFlowEmpt.setTranslation([1; 2]);
tran = affineFlowEmpt.getTranslation();
assert(isequal(tran,[1 2]));





res = 1;