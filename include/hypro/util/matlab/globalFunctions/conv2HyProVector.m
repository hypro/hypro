function out = conv2HyProVector(vector)
% This function converts a transposed vector into a vector.
    [rows, cols] = size(vector);
    if cols > rows
        % Vector is transposed
        out = vector';
    else
        out = vector;
    end
end