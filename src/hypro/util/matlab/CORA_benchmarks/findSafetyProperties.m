function out = findSafetyProperties(spec, ReachableSet)


% Create vector with variable values
min = zeros(size(spec,1),1);
max = zeros(size(spec,1),1);

spec_counter = 1;
    for row = 1:size(spec,1)
        values = zeros((length(ReachableSet) * length(ReachableSet{1})), 2);
        counter = 1;
        for i=1:length(ReachableSet)
            for j = 1:length(ReachableSet{i})
                % Check every specification for current set
                matrix = diag(spec(spec_counter,:));
                vector = prepareValues(ReachableSet{i}{j}, size(spec,2));
                temp = matrix * vector;
                value = sum(temp);
                values(counter,1) = infimum(value);
                values(counter,2) = supremum(value);
                counter = counter + 1;
            end
        end
        spec_counter = spec_counter + 1;
        min(row) = intmax;
        max(row) = intmin;

        for i = 1: size(values,1)
            if values(i,1) < min(row)
                min(row) = values(i,1);
            end
            if values(i,2) > max(row)
                max(row) = values(i,2);
            end
        end

        matrix = [-1 * spec; spec];
        vect = [-1 * min;max];
        out = [matrix, vect];
        %out = max;
    end
end


% Auxiliary function
function vector = prepareValues(rSet, dim)
    for i = 1:dim
        vec(i) = interval(projectOn(rSet,i));
    end
vector = vec.';
end