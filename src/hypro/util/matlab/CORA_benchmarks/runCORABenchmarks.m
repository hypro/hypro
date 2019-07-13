function runCORABenchmarks(benchmark, diff)

savePath = '/home/marta/Desktop';
plot = 0;
saveFig = 0;
logs = {};
log_counter = 1;
names = {'cora_bouncing_ball','cora_cruise_control',...
    'cora_oscillator_4','cora_oscillator_8','cora_oscillator_16',...
    'cora_switching_system','cora_rendezvous', 'cora_rod_reactor' ,'cora_two_tanks',...
    'cora_vehicle_platoon'};

    if benchmark == 1
        filename = strcat(names{1},'_',num2str(diff));
        logs{log_counter} = bouncing_ball(saveFig,savePath,filename, diff, plot);
        log_counter = log_counter + 1;
        saveFig = 0;
        plot = 0;
    elseif benchmark == 2
        filename = strcat(names{2},'_',num2str(diff));
        logs{log_counter} = cruise_control(saveFig,savePath,filename, diff, plot);
        log_counter = log_counter + 1;
        saveFig = 0;
        plot = 0;
    elseif benchmark == 3
        filename = strcat(names{3},'_',num2str(diff));
        logs{log_counter} = filtered_oscillator_4(saveFig,savePath,filename, diff, plot);
        log_counter = log_counter + 1;
        saveFig = 0;
        plot = 0;
    elseif benchmark == 4
        filename = strcat(names{4},'_',num2str(diff));
        logs{log_counter} = filtered_oscillator_8(saveFig,savePath,filename, diff, plot);
        log_counter = log_counter + 1;
        saveFig = 0;
        plot = 0;
    elseif benchmark == 5
        filename = strcat(names{5},'_',num2str(diff));
        logs{log_counter} = filtered_oscillator_16(saveFig,savePath,filename, diff, plot);
        log_counter = log_counter + 1;
        saveFig = 0;
        plot = 0;
    elseif benchmark == 6
        filename = strcat(names{6},'_',num2str(diff));
        logs{log_counter} = linear_switch(saveFig,savePath,filename, diff, plot);
        log_counter = log_counter + 1;
        saveFig = 0;
        plot = 0;
    elseif benchmark == 7
        filename = strcat(names{7},'_',num2str(diff));
        logs{log_counter} = rendezvousSX4np(saveFig,savePath,filename, diff, plot);
        log_counter = log_counter + 1;
        saveFig = 0;
        plot = 0;
    elseif benchmark == 8
        filename = strcat(names{8},'_',num2str(diff));
        logs{log_counter} = rod_reactor(saveFig,savePath,filename, diff, plot);
        log_counter = log_counter + 1;
        saveFig = 0;
        plot = 0;
    elseif benchmark == 9
        filename = strcat(names{9},'_',num2str(diff));
        logs{log_counter} = two_tanks(saveFig,savePath,filename, diff, plot);
        log_counter = log_counter + 1;
        saveFig = 0;
        plot = 0;
    else
        filename = strcat(names{10},'_',num2str(diff));
        logs{log_counter} = vehicle_platoon(saveFig,savePath,filename, diff, plot);
        log_counter = log_counter + 1;
        saveFig = 0;
        plot = 0; 
    end
    
    fileID = fopen(fullfile(savePath, 'CORA_benchmark_results.txt'),'a');
    disp(num2str(log_counter))
    for i = 1:length(logs)
        fprintf(fileID, '%s\n',logs{i});
    end
    fclose(fileID);

end