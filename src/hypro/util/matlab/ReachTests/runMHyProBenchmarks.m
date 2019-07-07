function runMHyProBenchmarks()

statPath = '/home/marta/Desktop';
statFName = 'mhypro_times.txt';
safePath = '/home/marta/Desktop';
runAll = 0;
times = {};
    names = {'mhypro_bouncing_ball','mhypro_car','mhypro_cruise_control',...
        'mhypro_oscillator_4','mhypro_oscillator_8','mhypro_oscillator_16',...
        'mhypro_rendezvous', 'mhypro_rod_reactor' ,'mhypro_switching_system','mhypro_two_tanks',...
        'mhypro_vehicle_platoon'};


if runAll
    statFileID = fopen(fullfile(statPath,statFName), 'a');

    times{1} = BouncingBallTest(0,safePath,names{1});
    times{2} = carMHyProTest(0,safePath,names{2});
    % times{3} = cruiseControl(1,safePath,names{3});
    % times{4} = FilteredOscillator4(1,safePath,names{4});
    % times{5} = FilteredOscillator8(1,safePath,names{5});
    % times{6} = FilteredOscillator16(1,safePath,names{6});
    % times{7} = rendezvousSX4(1,safePath,names{7});
    % times{8} = RodReactorTest(1,safePath,names{8})
    % times{9} = switchingSystem(1,safePath,names{9});
    % times{10} = TwoTanksTest(1,safePath,names{10});
    % times{11} = VehiclePlatoonTest(1,safePath,names{11});


    for i = 1:length(times)
        fprintf(statFileID,'%s %f\n', names{i}, times{i});
    end
else
%     BouncingBallTest(0,safePath,names{1});
%     carMHyProTest(0,safePath,names{2});
%     cruiseControl(0,safePath,names{3});
%     FilteredOscillator4(1,safePath,names{4});
%     FilteredOscillator8(0,safePath,names{5});
%     FilteredOscillator16(0,safePath,names{6});
%     rendezvousSX4(0,safePath,names{7});
%     RodReactorTest(0,safePath,names{8});
    switchingSystem(0,safePath,names{9});
%     TwoTanksTest(0,safePath,names{10});
%     VehiclePlatoonTest(0,safePath,names{11});
end
end