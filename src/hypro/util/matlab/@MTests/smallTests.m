function res = smallTests

box1 = MHyProObject('Box','new_empty');
box2 = MHyProObject('Box','new_intervals',[1 2; 3 4]);
box3 = MHyProObject('Box','new_empty');


boxes = {box1.Handle, box2.Handle, box3.Handle};


out = box1.test(boxes);
%box1.isempty();

% str = {'abc','def','ghi'};
% out = box1.getSettings(boxes);




res = 1;