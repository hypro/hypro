function runMHyProWithStrategy(benchmarkNr, strategy)

statPath = '/home/marta/Desktop';
statFName = 'mhypro_times.txt';
savePath = '/home/marta/Desktop';
bad = 1;
plot = 0;
saveFig = 0;
logs = {};
log_counter = 1;
    names = {'mhypro_bouncing_ball','mhypro_cruise_control',...
        'mhypro_oscillator_4','mhypro_oscillator_8','mhypro_oscillator_16',...
        'mhypro_switching_system','mhypro_rendezvous', 'mhypro_rod_reactor' ,'mhypro_two_tanks',...
        'mhypro_vehicle_platoon'};
    if benchmarkNr == 1
        % BOUNCING BALL
        for diff = 0:2
            [settings, setRepr, aggr] = getStrategy(strategy);
            for i = 1:length(settings)
                filename = strcat(names{1},'_',num2str(diff),'_',num2str(i));
                logs{log_counter} = bouncing_ball_mhypro(saveFig,savePath,filename, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
                log_counter = log_counter + 1;
                saveFig = 0;
                plot = 0;
            end
        end
    elseif benchmarkNr == 2
        % CRUISE CONTROL
        for diff = 0:2
            [settings, setRepr, aggr] = getStrategy(strategy);
            for i = 1:length(settings)
                filename = strcat(names{2},'_',num2str(diff),'_',num2str(i));
                logs{log_counter} = cruise_control_mhypro(saveFig,savePath,filename, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
                log_counter = log_counter + 1;
                saveFig = 0;
            end
        end
    elseif benchmarkNr == 3
     % FILTERED OSCILLATOR 4
        for diff = 0:2
            [settings, setRepr, aggr] = getStrategy(strategy);
            for i = 1:length(settings)
                filename = strcat(names{3},'_',num2str(diff),'_',num2str(i));
                logs{log_counter} = filtered_oscillator_4_mhypro(saveFig,savePath,filename, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
                log_counter = log_counter + 1;
                saveFig = 0;
                plot = 0;
            end
        end
    elseif benchmarkNr == 4
        % FILTERED OSCILLATOR 8
        for diff = 0:2
            [settings, setRepr, aggr] = getStrategy(strategy);
            for i = 1:length(settings)
                filename = strcat(names{4},'_',num2str(diff),'_',num2str(i));
                logs{log_counter} = filtered_oscillator_8_mhypro(saveFig,savePath,filename, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
                log_counter = log_counter + 1;
                saveFig = 0;
                plot = 0;
            end
        end
    elseif benchmarkNr == 5
        % FILTERED OSCILLATOR 16
        for diff = 0:2
            [settings, setRepr, aggr] = getStrategy(strategy);
            for i = 1:length(settings)
                filename = strcat(names{5},'_',num2str(diff),'_',num2str(i));
                logs{log_counter} = filtered_oscillator_16_mhypro(saveFig,savePath,filename, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
                log_counter = log_counter + 1;
                saveFig = 0;
                plot = 0;
            end
        end
    elseif benchmarkNr == 6
        % SWITCHING SYSTEM
        for diff = 0:2
            [settings, setRepr, aggr] = getStrategy(strategy);
            for i = 1:length(settings)
                filename = strcat(names{6},'_',num2str(diff),'_',num2str(i));
                logs{log_counter} = switching_system_mhypro(saveFig,savePath,filename, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
                log_counter = log_counter + 1;
                saveFig = 0;
                plot = 0;
            end
        end
    elseif benchmarkNr == 7
        % RENDEZVOUZ
        for diff = 0:2
            [settings, setRepr, aggr] = getStrategy(strategy);
            for i = 1:length(settings)
                filename = strcat(names{7},'_',num2str(diff),'_',num2str(i));
                logs{log_counter} = rendezvous_4np_mhypro(saveFig,savePath,filename, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
                log_counter = log_counter + 1;
                saveFig = 0;
            end
        end
    elseif benchmarkNr == 8
        % ROD REACTOR
        for diff = 0:2
            [settings, setRepr, aggr] = getStrategy(strategy);
            for i = 1:length(settings)
                filename = strcat(names{8},'_',num2str(diff),'_',num2str(i));
                logs{log_counter} = rod_reactor_mhypro(saveFig,savePath,filename, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
                log_counter = log_counter + 1;
                saveFig = 0;
                plot = 0;
            end
        end
    elseif benchmarkNr == 9
        % TWO TANKS
        for diff = 0:2
            [settings, setRepr, aggr] = getStrategy(strategy);
            for i = 1:length(settings)
                filename = strcat(names{9},'_',num2str(diff),'_',num2str(i));
                logs{log_counter} = two_tanks_mhypro(saveFig,savePath,filename, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
                log_counter = log_counter + 1;
                saveFig = 0;
                plot = 0;
            end
        end
    else
        % VEHICLE PLATOON
        for diff = 0:2
            [settings, setRepr, aggr] = getStrategy(strategy);
            for i = 1:length(settings)
                filename = strcat(names{10},'_',num2str(diff),'_',num2str(i));
                logs{log_counter} = vehicle_platoon_mhypro(saveFig,savePath,filename, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
                log_counter = log_counter + 1;
                saveFig = 0;
                plot = 0;
            end
        end
    end
    
    fileID = fopen(fullfile(savePath, 'mhypro_benchmark_results.txt'),'a');
    disp(num2str(log_counter))
    for i = 1:length(logs)
        fprintf(fileID, '%s\n',logs{i});
    end
    fclose(fileID);
end