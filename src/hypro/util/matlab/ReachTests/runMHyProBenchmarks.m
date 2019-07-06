function runMHyProBenchmarks()

statPath = '/home/marta/Desktop';
statFName = 'mhypro_times.txt';
safePath = '/home/marta/Desktop';
runAll = 1;
times = {};
    names = {'mhypro_bouncing_ball','mhypro_car','mhypro_cruise_control',...
        'mhypro_oscillator_4','mhypro_oscillator_8','mhypro_oscillator_16',...
        'mhypro_rendezvous','mhypro_switching_system','mhypro_two_tanks',...
        'mhypro_vehicle_platoon'}


if runAll
    statFileID = fopen(fullfile(statPath,statFName), 'a');

    times{1} = BouncingBallTest(0,safePath,names{1});
    times{2} = carMHyProTest(0,safePath,names{2});
    % times{3} = cruiseControl(1,safePath,names{3});
    % times{4} = FilteredOscillator4(1,safePath,names{4});
    % times{5} = FilteredOscillator8(1,safePath,names{5});
    % times{6} = FilteredOscillator16(1,safePath,names{6});
    % times{7} = rendezvousSX4(1,safePath,names{7});
    % times{8} = switchingSystem(1,safePath,names{8});
    % times{9} = TwoTanksTest(1,safePath,names{9});
    % times{10} = VehiclePlatoonTest(1,safePath,names{10});


    for i = 1:length(times)
        fprintf(statFileID,'%s %f\n', names{i}, times{i});
    end
else
    carMHyProTest(0,safePath,names{2})
end
end