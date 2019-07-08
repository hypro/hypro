function runMHyProBenchmarks()

statPath = '/home/marta/Desktop';
statFName = 'mhypro_times.txt';
safePath = '/home/marta/Desktop';
runAll = 0;
bad = 0;
times = {};
    names = {'mhypro_bouncing_ball','mhypro_car','mhypro_cruise_control',...
        'mhypro_oscillator_4','mhypro_oscillator_8','mhypro_oscillator_16',...
        'mhypro_rendezvous', 'mhypro_rod_reactor' ,'mhypro_switching_system','mhypro_two_tanks',...
        'mhypro_vehicle_platoon', 'buck_boost_converter'};


if runAll
    statFileID = fopen(fullfile(statPath,statFName), 'a');

    times{1} = BouncingBallTest(0,safePath,names{1}, bad);
    times{2} = carMHyProTest(0,safePath,names{2}, bad);
    times{3} = cruiseControl(0,safePath,names{3}, bad);
    times{4} = FilteredOscillator4(0,safePath,names{4}, bad);
    times{5} = FilteredOscillator8(0,safePath,names{5}, bad);
    times{6} = FilteredOscillator16(0,safePath,names{6}, bad);
    times{7} = rendezvousSX4npMHyPro(0,safePath,names{7}, bad);
    times{8} = RodReactorTest(0,safePath,names{8}, bad);
    times{9} = switchingSystem(0,safePath,names{9}, bad);
    times{10} = TwoTanksTest(0,safePath,names{10}, bad);
    times{11} = VehiclePlatoonTest(0,safePath,names{11}, bad);


    for i = 1:length(times)
        fprintf(statFileID,'%s %f\n', names{i}, times{i});
    end
else
    BouncingBallTest(0,safePath,names{1}, bad);
%     carMHyProTest(0,safePath,names{2}, bad);
%     cruiseControl(0,safePath,names{3}, bad);
%     FilteredOscillator4(1,safePath,names{4}, bad);
%     FilteredOscillator8(0,safePath,names{5}, bad);
%     FilteredOscillator16(0,safePath,names{6}, bad);
%     rendezvousSX4npMHyPro(0,safePath,names{7}, bad);
%     RodReactorTest(0,safePath,names{8}, bad);
%     switchingSystem(0,safePath,names{9}, bad);
%     TwoTanksTest(0,safePath,names{10}, bad);
%     VehiclePlatoonTest(0,safePath,names{11}, bad);
%     buck_boost_converter(0,safePath,names{12}, bad);
end
end