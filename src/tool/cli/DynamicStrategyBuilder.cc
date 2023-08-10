
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

// #include "../../include/cli/DynamicStrategyBuilder.h"

// namespace hydra {
// namespace cli {

// DynamicStrategyBuilder::DynamicStrategyBuilder(){
// 	mOptions.add_options()
//         ("help,h","All commands in a nutshell:")
//         ("rep", po::value<std::string>(), "Enter --rep <representation_name> to use the chosen representation.") 
//         ("timestep", po::value<mpq_class>(), "Enter --timestep <Number> to use the chosen time step size.")
//         ("agg", po::value<std::string>(), "Enter --agg <aggregation> to enter the wished aggregation setting.")
//         ("cluster", po::value<int>(), "Enter --cluster <Number> to enter the clustering size.")
//         ("add", "Enter new strategyNode.")
//         ("show", "Enter --show to print the strategy and the current strategy node.")
//         ("clear", "Enter --clear to rewrite all settings of the current node.")
//         ("remove", "Enter --remove to remove the last added node.")
//         ("done", "Enter --done to finish building your strategy. Starts reachability analysis.");
// }

// DynamicStrategyBuilder::DynamicStrategyBuilder(const std::vector<std::vector<std::string>>& snodeStrings){
//     for(const auto& snodeArgs : snodeStrings){

//         if(snodeArgs.size() < 3){
//             CERR("Too few arguments to build a strategy node via snode option! Please enter \n1. The representation name \n2. A representation setting \n3. The time step, and optionally \n4. The aggregation\n5. The clustering\n");
//             exit(0);
//         }
//         if(snodeArgs.size() > 5){
//             CERR("Too many arguments for strategy node building via snode option! Please enter only once \n1. The representation name \n2. A representation setting \n3. The time step, and optionally \n4. The aggregation\n5. The clustering\n");
//             exit(0);
//         }

//         //Get representation name
//         if(inputToRep.find(snodeArgs[0]) != inputToRep.end()){
//             mChosenRep = inputToRep.at(snodeArgs[0]);    
//         } else {
//             CERR("No representation found in snode option!\n");
//             exit(0);
//         }

//         //Get setting
//         bool foundSetting = false;
//         for(unsigned i = 0; i < rep_settings.at(mChosenRep).size(); ++i){
//             if(snodeArgs[1] == rep_settings.at(mChosenRep).at(i)){
//                 mChosenSetting = rep_settings.at(mChosenRep).at(i);
//                 foundSetting = true;
//                 break;
//             }
//         }
//         if(!foundSetting){
//             CERR("No fitting setting found for representaiton in snode option!\n");
//             exit(0);
//         }

//         //Get timestep
//         std::stringstream sstream(snodeArgs[2]);
//         sstream >> mStratSettings.timeStep;
//         if(mStratSettings.timeStep <= tNumber(0)){
//             CERR("Timestep cannot be 0 or below in snode option!\n");
//             exit(0);
//         }

//         //Get Aggregation
//         if(snodeArgs.size() == 3){
//             mStratSettings.aggregation = hypro::AGG_SETTING::AGG;
//         } else if(snodeArgs.size() >= 4){
//             if(snodeArgs[3] == "MODEL" || snodeArgs[3] == "model"){
//                 mStratSettings.aggregation = hypro::AGG_SETTING::MODEL;
//             } else if(snodeArgs[3] == "AGG" || snodeArgs[3] == "agg" || snodeArgs[3] == "1"){
//                 mStratSettings.aggregation = hypro::AGG_SETTING::AGG;
//             } else if(snodeArgs[3] == "NO_AGG" || snodeArgs[3] == "no_agg" || snodeArgs[3] == "0"){
//                 mStratSettings.aggregation = hypro::AGG_SETTING::NO_AGG;
//             } else {
//                 CERR("Stated aggregation type does not exist in snode option!\n");
//                 exit(0);
//             }
//         }

//         //Get Clustering
//         if(snodeArgs.size() <= 4){
//             mStratSettings.clustering = -1;
//         } else if(snodeArgs.size() == 5){
//             sstream = std::stringstream(snodeArgs[4]);
//             sstream >> mStratSettings.clustering;
//         } else {
//             CERR("This should not be reachable.\n");
//             exit(0);
//         }

//         //Build stratNode and add to mStrategy
//         std::cout << "Representation: " << mChosenRep << " Setting: " << mChosenSetting << " strategy settings: " << mStratSettings << std::endl;
//         if(mChosenRep != hypro::representation_name::UNDEF){
//             mStrategy.emplace_back(repCreationMap.at(mChosenSetting)(mStratSettings));
//         } else {
//             CERR("UNDEF is not a valid representation name in snode option!\n");
//             exit(0);
//         }
//     }
// }

// void DynamicStrategyBuilder::showMessage(){
// 	COUT("===============================\n");
//     COUT("= HyDRA custom strategy mode! =\n");
//     COUT("===============================\n\n");
//     COUT("Build your own reachability strategy by adding strategy nodes that contain information about how the reachability analysis should be carried out.\n");
//     COUT("Each added strategy node is used in the next level of refinement during the reachability analysis.\n");
//     COUT("At first, the reachability analysis is performed using the settings in the first strategy node.\n");
//     COUT("If the analysis cannot be verified as safe using the first strategy node, then the current flowpipe is recalculated using the second strategy node and so on.\n\n");
//     COUT("Type in the desired representation, its setting and the wanted timestep.\n"); //In future add aggregation setting and clustering setting
//     COUT("IMPORTANT: You have to at least enter the representation and the timestep.\n\n");
//     COUT("1. To enter a new strategy node, first enter \"hydra\", then the wanted parameters.\n");
//     COUT("2. Enter \"hydra --rep <representation_name>\" to use the chosen representation. Possible representation names are: \n\t box, support_function, zonotope, polytope_h, polytope_v, SFN, carl_polytope, difference_bounds\n");
//     COUT("3. Enter \"hydra --timestep <Number>\" to use the chosen time step size. \n");
//     COUT("4. Enter \"hydra --agg <agg>\" to choose the aggregation. Possible inputs are: \n\t agg, no_agg, model\n");
//     COUT("5. Enter \"hydra --cluster <Number>\" to choose the clustering size.\n");
//     COUT("6. Enter \"hydra --add\" to add the current strategy node to the strategy.\n");
//     COUT("6. Enter \"hydra --show\" to print the complete strategy as well as the currently edited strategy node.\n");
//     COUT("7. Enter \"hydra --clear\" to rewrite all settings of the current node.\n");
//     COUT("8. Enter \"hydra --remove\" to remove the last added node.\n");
//     COUT("9. Enter \"hydra --done\" to finish building your strategy. This will also directly start the reachability analysis with the entered strategy.\n");
// }

// void DynamicStrategyBuilder::parse(){

//     //Wait for input
//     std::string line;
//     std::getline(std::cin,line);

//     //Get current argc and argv
//     std::vector<std::string> argvString;
//     std::istringstream input(line);
//     std::string option;
//     while(std::getline(input,option,' ')){
//         argvString.push_back(option);
//     }

//     //convert argvString into a pointer to a char array
//     std::vector<const char*> argv;
//     for(const auto& arg : argvString){
//         argv.push_back(arg.c_str());
//     }

//     //Parse into vmStrat
//     po::store(po::parse_command_line(argv.size(), argv.data(), mOptions), vmStrat);
// }

// void DynamicStrategyBuilder::handle(){

//     try {

//     	//Check which options have been entered
//         //--rep: save
//         if(vmStrat.count("rep") == 1){

//             //Get representation name from string
//             mChosenRep = inputToRep.at(vmStrat["rep"].as<std::string>());

//             std::cout << "Chosen representation: " << mChosenRep << std::endl;
//             std::cout << "Please select a fitting setting for this representation by typing in the ID in the squared brackets:" << std::endl;

//             //Print out description of each
//             auto it = rep_settings.find(mChosenRep);
//             for(unsigned i = 0; i < it->second.size(); ++i){
//                 std::cout << "[" << i << "] " << it->second.at(i) << std::endl;
//             }
//             std::cout << "> ";

//             //Wait for input
//             string input;
//             unsigned inputId = 0;
//             bool isInputValid = false;
//             while(!isInputValid){
//                 std::getline(std::cin,input);
//                 std::stringstream ss(input);
//                 ss >> inputId;
//                 if(!ss.fail() && inputId < it->second.size()){
//                     isInputValid = true;
//                 } else {
//                     ss.clear();
//                     std::cout << "Index not recognized. Try again!" << std::endl;    
//                     std::cout << "> ";
//                 }
//             }

//             //Set as setting
//             mChosenSetting = it->second.at(inputId);
//             std::cout << "Chosen setting is: " << mChosenSetting << std::endl;
//         }

//         //--timeStep: save into mStratSettings
//         if(vmStrat.count("timestep") == 1){
//             mStratSettings.timeStep = vmStrat["timestep"].as<mpq_class>();
//         } else if(vmStrat.count("timestep") > 1) {
//             std::cout << "Please refrain from entering multiple time step sizes. No time step size has been chosen." << std::endl;
//         }

//         //--aggregation
//         if(!vmStrat.count("agg")){
//             mStratSettings.aggregation = hypro::AGG_SETTING::AGG;
//         } else {
//             if(vmStrat.count("agg") == 1){
//                 if(vmStrat["agg"].as<std::string>() == "MODEL" || vmStrat["agg"].as<std::string>() == "model"){
//                     mStratSettings.aggregation = hypro::AGG_SETTING::MODEL;
//                 } else if(vmStrat["agg"].as<std::string>() == "AGG" || vmStrat["agg"].as<std::string>() == "agg" || vmStrat["agg"].as<std::string>() == "1"){
//                     mStratSettings.aggregation = hypro::AGG_SETTING::AGG;
//                 } else if(vmStrat["agg"].as<std::string>() == "NO_AGG" || vmStrat["agg"].as<std::string>() == "no_agg" || vmStrat["agg"].as<std::string>() == "0"){
//                     mStratSettings.aggregation = hypro::AGG_SETTING::NO_AGG;
//                 } else {
//                     CERR("Stated aggregation type does not exist!\n");
//                 }    
//             } else {
//                 CERR("Please refrain from entering the aggregation setting multiple times.\n");
//             }
//         }

//         //--cluster
//         if(vmStrat.count("cluster") == 1){
//             mStratSettings.clustering = vmStrat["cluster"].as<int>();
//         }

//         //--addStrategyNode: All values remembered till now are made into a strat node
//         if(vmStrat.count("add")){
//             if(mChosenRep != hypro::representation_name::UNDEF && mStratSettings.timeStep > 0){
//                 //std::cout << "mChosenRep is: " << mChosenRep << " mChosenSetting is: " << mChosenSetting << " mStratSettings is: " << mStratSettings << std::endl;
//                 std::cout << "Added parameters as strategy node!" << std::endl;
//                 mStrategy.emplace_back(repCreationMap.at(mChosenSetting)(mStratSettings));
//                 mChosenRep = hypro::representation_name::UNDEF;
//                 mStratSettings = hypro::StrategyParameters();
//                 mChosenSetting = "";    
//             } else {
//                 std::cout << "Please choose a representation and enter a timestep via \"add --rep <representation> --timestep <timestep>\" before adding a mStrategy node." << std::endl;
//             }
//         }

//         //--show: show complete mStrategy and currently modified node
//         if(vmStrat.count("show")){
//             std::cout << "Current strategy is: " << std::endl;
//             for(std::size_t i = 0; i < mStrategy.size(); ++i){
//                 std::string rep;
//                 for(const auto& inputRepPair : inputToRep){
//                     if(inputRepPair.second == mStrategy.getParameters(i).representation_type){
//                         rep = inputRepPair.first;
//                     }
//                 }
//                 std::cout << "Node " << i << ": Representation: " << rep << " Parameters: " << mStrategy.getParameters(i) << std::endl;
//             }
//         }

//         //--clear: set all the values back. 
//         if(vmStrat.count("clear")){
//             mChosenRep = hypro::representation_name::UNDEF;
//             mStratSettings = hypro::StrategyParameters();
//             mChosenSetting = "";
//             std::cout << "All entered options for the current mStrategy node have been deleted." << std::endl;
//         }

//         //--remove: remove last strat node
//         if(vmStrat.count("remove")){
//             if(mStrategy.size() >= 1){
//                 mStrategy.removeNode(mStrategy.size()-1);
//                 std::cout << "Removed last node." << std::endl; 
//             }
//         }

//         //--done: All values remembered till now are made into a strat node && pend the loop
//         if(vmStrat.count("done")){
//             if(mChosenRep != hypro::representation_name::UNDEF && mStratSettings.timeStep > 0){
//                 mStrategy.emplace_back(repCreationMap.at(mChosenSetting)(mStratSettings));
//                 //addStrategyNode(mChosenSetting, mStratSettings.timeStep, mStratSettings.aggregation, mStratSettings.clustering);
//             } 
//             if(mStrategy.size() >= 1){
//                 done = true;    
//             } else {
//                 std::cout << "Please choose a representation and enter a timestep via \"add --rep <representation> --timestep <timestep>\" before adding a mStrategy node." << std::endl;
//             }
//         }

//     } catch(std::exception& e) {
//         CERR(e.what());
//         //COUT(mOptions << std::endl);
//         exit(0);
//     }
// }

// void DynamicStrategyBuilder::startGui(){
// 	showMessage();
// 	while(!done){
// 		std::cout << "> ";
// 		parse();
// 		handle();
// 		//Clear variable map for the next round
//         vmStrat.clear();
// 	}
// }

// template<carl::DisableIf<std::is_same<tNumber,double>>>
// void DynamicStrategyBuilder::addStrategyNode(const std::string& setting, const tNumber& timestep, const hypro::AGG_SETTING agg, const int clustering){
//     hypro::StrategyParameters params;
//     params.timeStep = timestep;
//     params.aggregation = agg;
//     params.clustering = clustering;
//     mStrategy.emplace_back(repCreationMap.at(setting)(params));
// }

// void DynamicStrategyBuilder::addStrategyNode(const std::string& setting, const double timestep, const hypro::AGG_SETTING agg, const int clustering){
//     hypro::StrategyParameters params;
//     params.timeStep = carl::convert<double,tNumber>(timestep);
//     params.aggregation = agg;
//     params.clustering = clustering;
//     mStrategy.emplace_back(repCreationMap.at(setting)(params));
// }

// } //namespace cli
// } //namespace hydra
