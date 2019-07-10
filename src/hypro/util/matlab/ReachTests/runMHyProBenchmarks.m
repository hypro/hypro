function runMHyProBenchmarks()

statPath = '/home/marta/Desktop';
statFName = 'mhypro_times.txt';
safePath = '/home/marta/Desktop';
runAll = 0;
bad = 1;
times = {};
    names = {'mhypro_bouncing_ball','mhypro_car','mhypro_cruise_control',...
        'mhypro_oscillator_4','mhypro_oscillator_8','mhypro_oscillator_16',...
        'mhypro_rendezvous', 'mhypro_rod_reactor' ,'mhypro_switching_system','mhypro_two_tanks',...
        'mhypro_vehicle_platoon', 'buck_boost_converter'};


if runAll
    statFileID = fopen(fullfile(statPath,statFName), 'a');

    times{1} = BouncingBallTest(0,safePath,names{1}, bad, 1);
    times{2} = carMHyProTest(0,safePath,names{2}, bad, 1);
    times{3} = cruiseControl(0,safePath,names{3}, bad, 1);
    times{4} = FilteredOscillator4(0,safePath,names{4}, bad, 1);
    times{5} = FilteredOscillator8(0,safePath,names{5}, bad, 1);
    times{6} = FilteredOscillator16(0,safePath,names{6}, bad, 1);
    times{7} = rendezvousSX4npMHyPro(0,safePath,names{7}, bad, 1);
    times{8} = RodReactorTest(0,safePath,names{8}, bad, 1);
    times{9} = switchingSystem(0,safePath,names{9}, bad, 1);
    times{10} = TwoTanksTest(0,safePath,names{10}, bad, 1);
    times{11} = VehiclePlatoonTest(0,safePath,names{11}, bad, 1);


    for i = 1:length(times)
        fprintf(statFileID,'%s %f\n', names{i}, times{i});
    end
else
    BouncingBallTest(0,safePath,names{1}, bad, 1);
%     carMHyProTest(0,safePath,names{2}, bad, 1);
%     cruiseControl(0,safePath,names{3}, bad, 1);
%     FilteredOscillator4(1,safePath,names{4}, bad, 1);
%     FilteredOscillator8(0,safePath,names{5}, bad, 1);
%     FilteredOscillator16(0,safePath,names{6}, bad, 1);
%     rendezvousSX4npMHyPro(0,safePath,names{7}, bad, 1);
%     RodReactorTest(0,safePath,names{8}, bad, 1);
%     switchingSystem(0,safePath,names{9}, bad, 1);
%     TwoTanksTest(0,safePath,names{10}, bad, 1);
%     VehiclePlatoonTest(0,safePath,names{11}, bad, 1);
%     buck_boost_converter(0,safePath,names{12}, bad, 1);
end
end