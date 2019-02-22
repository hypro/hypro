function out = areIntervals(intervals)

    if ismatrix(intervals)
        % Check if number of columns is two
        [rows, cols] = size(intervals);
        if cols == 2
            % Check if bounds are correct
            for i = 1:rows
                if intervals(i, 1) > intervals(i,2)
                    error("areIntervals: Lower bound is larger than upper bound.");
                end
            end
        else
            error("areIntervals: Argument is not a n x 2 matrix.");
        end
    else
         error("areIntervals: Argument is not a n x 2 matrix.");
    end
    
out = 1;