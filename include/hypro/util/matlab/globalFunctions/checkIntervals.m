function out = checkIntervals(intervals)
    out = 1;
    if ismatrix(intervals)
        % Check if number of columns is two
        [rows, cols] = size(intervals);
        if cols == 2
            % Check if bounds are correct
            for i = 1:rows
                if intervals(i, 1) > intervals(i,2)
                    out = 0;
                    error("checkIntervals: Lower bound is larger than upper bound.");
                end
            end
        else
            out = 0;
            error("chekIntervals: Argument is not a n x 2 matrix.");
        end
    else
        out = 0;
        error("checkIntervals: Argument is not a n x 2 matrix.");
    end
end
