function runMHyProWithStrategy()

statPath = '/home/marta/Desktop';
statFName = 'mhypro_times.txt';
safePath = '/home/marta/Desktop';
bad = 1;
plot = 0;
times = {};
    names = {'mhypro_bouncing_ball','mhypro_car','mhypro_cruise_control',...
        'mhypro_oscillator_4','mhypro_oscillator_8','mhypro_oscillator_16',...
        'mhypro_rendezvous', 'mhypro_rod_reactor' ,'mhypro_switching_system','mhypro_two_tanks',...
        'mhypro_vehicle_platoon', 'buck_boost_converter'};

    strategy = 2;    
    [settings, setRepr, aggr] = getStrategy(strategy); 
    
    for diff = 0:2
        for i = 1:length(settings)
            bouncing_ball_mhypro(0,safePath,names{1}, bad, diff,settings{i},setRepr{i},aggr{i},plot, strategy);
        end
    end
    
    
%     carMHyProTest(0,safePath,names{2}, bad, diff, startegy);
%     cruiseControl(0,safePath,names{3}, bad, diff, startegy);
%     FilteredOscillator4(1,safePath,names{4}, bad, diff, startegy);
%     FilteredOscillator8(0,safePath,names{5}, bad, diff, startegy);
%     FilteredOscillator16(0,safePath,names{6}, bad, diff, startegy);
%     rendezvousSX4npMHyPro(0,safePath,names{7}, bad, diff, startegy);
%     RodReactorTest(0,safePath,names{8}, bad, diff, startegy);
%     switchingSystem(0,safePath,names{9}, bad, diff, startegy);
%     TwoTanksTest(0,safePath,names{10}, bad, diff, startegy);
%     VehiclePlatoonTest(0,safePath,names{11}, bad, diff, startegy);
%     buck_boost_converter(0,safePath,names{12}, bad, diff, startegy);


end