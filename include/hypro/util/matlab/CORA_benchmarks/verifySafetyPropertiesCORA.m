function out = verifySafetyProperties(spec_matrix, ReachableSet)

%--------------------------------------------------------------------------
% spec_matrix:  The rows of the matrix contain coefficients of a single
%               safety specification
%
% ReachableSet: Contains the reachable set computed by CORA (OT)
%
% example:      safety specification: x1 + 3 * x2 + 2 * x3 <= 5
%               spec_matrix: [1 3 2 5]
%
%               The last column of spec_matrix always contains the rhs.
%               Moreover, it is always assumed that the operator <= is used
%               for specifying safety properties. For multiple safety prop.
%               just add new row to the matrix
%
% notice:       Do not forget the variable order! -> For the following
%               variable order: x1, x2, x3 and the safety property
%               x3 + 3 * x1 <= 5 the spec_matrix has to have the form:
%               [3 0 1 5]
%--------------------------------------------------------------------------


[~, s_mat_cols] = size(spec_matrix);
spec = spec_matrix(:, 1:(s_mat_cols -1));
rhSides = spec_matrix(:, s_mat_cols);
tmp = true;

tic;
for i=1:length(ReachableSet)
    for j = 1:length(ReachableSet{i})
        % Check every specification for current set

        % sliced var to store the result of parfor
        results = cell(size(spec,1),1);
        %parfor (row = 1: size(spec, 1),M)
        for row = 1: size(spec, 1)
            matrix = diag(spec(row,:));
            rhs = rhSides(row);
%             disp(['Checking: [' num2str(spec(row,:)) '] <= ' num2str(rhs) '...']) ;
            vector = prepareValues(ReachableSet{i}{j}, s_mat_cols-1);
            temp = matrix * vector;
            value = sum(temp);
            % Check for validity
            if  supremum(value) > rhs
                % Specification was violated, exit
                disp(['NOT SAFE - spec. no. ' num2str(row) ' violated following specification: [' num2str(spec(row,:)) '] <= ' num2str(rhs)]) ;
                results{row} = false;
%             elseif rhs < 0 && infimum(value) < rhs
%                 % Specification was violated, exit
%                 disp(['NOT SAFE - spec. no. ' num2str(row) ' violated following specification: [' num2str(spec(row,:)) '] <= ' num2str(rhs)]) ;
%                 results{row} = false;
            end
        end

        if ~isempty(find([results{:}] == false, 1))
            out = 0;
            time = toc;
            disp(['Verification in ', num2str(time)]);
            return
       % else
            %disp('SAFE');
        end
    end
end
% if we end up here, no bad state has been intersected.
out = tmp;
time = toc;
disp(['Verification in ', num2str(time)]);

% Auxiliary function

function vector = prepareValues(rSet, dim)
    for i = 1:dim
        vec(i) = interval(projectOn(rSet,i));
    end
     %vec
vector = vec.';
