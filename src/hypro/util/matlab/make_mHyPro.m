%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                            COMPILE MHyPro
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% MHyPro is a Matlab-wrapper for the well known C++ tool HyPro offering
% various state set representations and a reachability analysis tool for
% hybrid systems. 
%
% This is the gateway file for MHypro. In order to compile mhypro just run
% this file. It compiles the MEX function contained in the MHyPro.cpp file.
%
% NOTE: 
%	- First HyPro has to be compiled and every time the MReach.cpp file
%         was changed.
%   - All folders and subfolders contained in hypro/src/hypro/util/matlab
%     have to be added to Matlab path.
%	- This code works only on Linux!
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Name of the file containing the MEX Function
srcFile = 'MHyPro.cpp';

ipaths = {};
if isfile('matlabInput')
    %Load the saved paths
    load('matlabInput');
    ipaths = {mat_str, antl_str, misc_str, atn_str, dfa_str, tree_str,...
                    supp_str, hypro_str, carl_str, loc_str, c_res_str,...
                    comp_str, hy_bu_str, hy_lib_str, cmp_flag, cxx_flag;};
else
   %Create the file
    if ismac
%         %Mac
%         matlab = dir(fullfile('/Applications','**','mex.h'));
%         antlr4_runtime = dir(fullfile('/Users','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/antlr4-common.h'));
%         misc = dir(fullfile('/Users','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/misc/Interval.h'));
%         atn = dir(fullfile('/Users','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/atn/ATN.h'));  
%         dfa = dir(fullfile('/Users','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/dfa/DFA.h')); 
%         tree = dir(fullfile('/Usershome','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/tree/Trees.h'));
%         support = dir(fullfile('/Users','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/support/Any.h'));
%         hypro = dir(fullfile('/Users','**','/hypro/src/hypro/types.h'));
%         carl = dir(fullfile('/Users','**','/carl/src/CMakeLists.txt'));
%         local_include = '/usr/local/include';
%         carl_resources = dir(fullfile('/Users','**','/carl/build/resources/include/gmp.h'));
%         compiler = '/usr/local/opt/llvm/include/c++/v1/';
%         hypro_build = dir(fullfile('/Users','**','/hypro/build/CMakeCache.txt'));
%         %hypro_lib = dir(fullfile('/Users','**','/hypro/build/libhypro.so'));
%         dgtest = '-DGTEST_USE_OWN_TR1_TUPLE=1 -std=c++17 -stdlib=libc++';
%         %llvm = '-L/usr/local/opt/llvm/lib';
%         %hypro_lib_flag = '-hypro';
%         %ld_flag = strcat('LDFLAGS=$LDFLAGS -Wl -rpath', hy_build.folder);
%         
%         mat_str = strcat('-I', matlab.folder);
%         antl_str = strcat('-I', antlr4_runtime.folder);
%         misc_str = strcat('-I', misc.folder);
%         atn_str = strcat('-I', ant.folder);
%         dfa_str = strcat('-I', dfa.folder);
%         tree_str = strcat('-I', tree.folder);
%         supp_str = strcat('-I', support.folder);
%         hypro_str = strcat('-I', hypro.folder);
%         carl_str = strcat('-I', carl.folder);
%         loc_str = strcat('-I', local_include.folder);
%         c_res_str = strcat('-I', carl_resources.folder);
%         comp_str = strcat('-L', compiler.folder);
%         hy_bu_str = strcat('-L', hypro_build.folder);
%         llvm_str = '-L/usr/local/opt/llvm/lib';
%         hy_lib_str = '-hypro';
%         ld_fl_str = strcat('LDFLAGS=$LDFLAGS -Wl -rpath', hy_build.folder);
%         cmp_flag = 'COMPFLAGS=$COMPFLAGS -std=c++17';
%         cxx_flag = 'CXXFLAGS=\$CXXFLAGS -std=c++17';
%         
%         %Save the found paths
%         save 'matlcd nput' mat_str;
%         save 'matlabInput' antl_str;
%         save 'matlabInput' misc_str;
%         save 'matlabInput' atn_str;
%         save 'matlabInput' dfa_str;
%         save 'matlabInput' tree_str;
%         save 'matlabInput' supp_str;
%         save 'matlabInput' hypro_str;
%         save 'matlabInput' carl_str;
%         save 'matlabInput' loc_str;
%         save 'matlabInput' c_res_str;
%         save 'matlabInput' comp_str;
%         save 'matlabInput' hy_bu_str;
%         save 'matlabInput' hy_lib_str;
%         save 'matlabInput' llvm_str;
%         save 'matlabInput' 'ld_fl_str';
%         save 'matlabInput' cmp_flag;
%         save 'matlabInput' 'cxx_flag';
%         
%         ipaths = {mat_str, antl_str, misc_str, atn_str, dfa_str, tree_str,...
%                     supp_str, hypro_str, carl_str, loc_str, c_res_str,...
%                     comp_str, hy_bu_str, hy_lib_str, cmp_flag, cxx_flag;};
        
        
%         ipaths={strcat('-I', matlab.folder),strcat('-I', antlr4_runtime.folder),...
%         strcat('-I', misc.folder), strcat('-I', atn.folder), strcat('-I', dfa.folder),...
%         strcat('-I', tree.folder), strcat('-I', support.folder), strcat('-I', hypro.folder),...
%         strcat('-I', carl.folder), strcat('-I', local_include), strcat('-I', carl_resources.folder),...
%         strcat('-I', compiler), strcat('-L', hypro_build.folder), dgtest, strcat('-L', llvm),...
%         '-lhypro',  strcat('LDFLAGS=$LDFLAGS -Wl -rpath ', hypro_build.folder),...
%         'COMPFLAGS=$COMPFLAGS -std=c++17', 'CXXFLAGS=\$CXXFLAGS -std=c++17';};

        ipaths = {'-I/Applications/MATLAB_R2018b.app/extern/include',...
        '-I/Users/marta/hypro/build/resources/antlr_build/include/antlr4-runtime',...
        '-I/Users/marta/hypro/build/resources/antlr_build/include/antlr4-runtime/misc',...
        '-I/Users/marta/hypro/build/resources/antlr_build/include/antlr4-runtime/atn',...
        '-I/Users/marta/hypro/build/resources/antlr_build/include/antlr4-runtime/dfa',...
        '-I/Users/marta/hypro/build/resources/antlr_build/include/antlr4-runtime/tree',...
        '-I/Users/marta/hypro/build/resources/antlr_build/include/antlr4-runtime/support',...
        '-I/Users/marta/hypro/src','-I/usr/local/opt/llvm/include','-I/Users/marta/carl/src',...
        '-I/usr/local/include','-I/Users/marta/carl/resources/include',...
        '-I/usr/local/opt/llvm/include/c++/v1/ -DGTEST_USE_OWN_TR1_TUPLE=1 -std=c++17 -stdlib=libc++',...
        '-L/usr/local/lib/','-L/usr/local/opt/llvm/lib','-L/Users/marta/hypro/build','-lgmp','-lgmpxx','-lhypro',...
        'LDFLAGS=$LDFLAGS -Wl -rpath /Users/marta/hypro/build';};
        
        %Save the found paths
            mex -setup c++;
            mex('-v',ipaths{:},'CC=/usr/local/opt/llvm/bin/clang','GCC=/usr/local/bin/gcc','CXX=/usr/local/opt/llvm/bin/clang++','CXXFLAGS=\$CXXFLAGS -std=c++17',srcFile);
%             mex /reachability/@MHyProReach/MReach.cpp

        
        elseif isunix
        %Linux
%         matlab = dir(fullfile('/usr','**','mex.h'));
%         antlr4_runtime = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/antlr4-common.h'));
%         misc = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/misc/Interval.h'));
%         atn = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/atn/ATN.h'));  
%         dfa = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/dfa/DFA.h')); 
%         tree = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/tree/Trees.h'));
%         support = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/support/Any.h'));
%         hypro = dir(fullfile('/home','**','/hypro/src/hypro/types.h'));
%         carl = dir(fullfile('/home','**','/carl/src/CMakeLists.txt'));
%         local_include = '/usr/local/include';
%         carl_resources = dir(fullfile('/home','**','/carl/build/resources/include/'));
%         compiler = '/usr/bin/c++';
%         hypro_build = dir(fullfile('/home','**','/hypro/build/CMakeCache.txt'));
%         hypro_lib = dir(fullfile('/home','**','/hypro/build/libhypro.so'));
%         glpk_lib = dir(fullfile('/usr/local/lib','**','libglpk.so'));
%         
%         mat_str = strcat('-I', matlab.folder);
%         antl_str = strcat('-I', antlr4_runtime.folder);
%         misc_str = strcat('-I', misc.folder);
%         atn_str = strcat('-I', atn.folder);
%         dfa_str = strcat('-I', dfa.folder);
%         tree_str = strcat('-I', tree.folder);
%         supp_str = strcat('-I', support.folder);
%         hypro_str = strcat('-I', hypro.folder);
%         carl_str = strcat('-I', carl.folder);
%         loc_str = strcat('-I', local_include);
%         c_res_str = strcat('-I', carl_resources.folder);
%         comp_str = strcat('-I', compiler);
%         hy_bu_str = strcat('-I', hypro_build.folder);
%         hy_lib_str = strcat('-L', hypro_lib.folder, 'libhypro.so');
%         glpk_lib_str = strcat('-L', glpk_lib.folder, 'libglpk.so');
%         cmp_flag = 'COMPFLAGS=$COMPFLAGS -std=c++17';
%         cxx_flag = 'CXXFLAGS=\$CXXFLAGS -std=c++17';
%         
%         %Save the found paths
%         save 'matlabInput' mat_str;
%         save 'matlabInput' antl_str;
%         save 'matlabInput' misc_str;
%         save 'matlabInput' atn_str;
%         save 'matlabInput' dfa_str;
%         save 'matlabInput' tree_str;
%         save 'matlabInput' supp_str;
%         save 'matlabInput' hypro_str;
%         save 'matlabInput' carl_str;
%         save 'matlabInput' loc_str;
%         save 'matlabInput' c_res_str;
%         save 'matlabInput' comp_str;
%         save 'matlabInput' hy_bu_str;
%         save 'matlabInput' hy_lib_str;
%         save 'matlabInput' cmp_flag;
%         save 'matlabInput' glpk_lib_str;
%         save 'matlabInput' 'cxx_flag';
%         
% %         ipaths = {mat_str, antl_str, misc_str, atn_str, dfa_str, tree_str,...
% %                     supp_str, hypro_str, carl_str, loc_str, c_res_str,...
% %                     comp_str, hy_bu_str, hy_lib_str, glpk_lib_str, cmp_flag, cxx_flag;};
% 
%         ipaths={strcat('-I', matlab.folder),strcat('-I', antlr4_runtime.folder),...
%         strcat('-I', misc.folder), strcat('-I', atn.folder), strcat('-I', dfa.folder),...
%         strcat('-I', tree.folder), strcat('-I', support.folder), strcat('-I', hypro.folder),...
%         strcat('-I', carl.folder), strcat('-I', local_include), strcat('-I', carl_resources.folder),...
%         strcat('-I', compiler), strcat('-I', hypro_build.folder), strcat('-L', hypro_build.folder, 'libhypro.so'),'COMPFLAGS=$COMPFLAGS -std=c++17',...
%         'CXXFLAGS=\$CXXFLAGS -std=c++17';};

    setenv LD_RUN_PATH /home/marta/hypro/build;
    setenv LD_LIBRARY_PATH /usr/lib/gcc/x86_64-linux-gnu/8/lib:/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH;
    setenv LD_LIBRARY_PATH /usr/local/MATLAB/R2018b/bin/glnxa64:/usr/local/MATLAB/R2018b/sys/os/glnxa64;
    setenv LD_LIBRARY_PATH /usr/lib/x86_64-linux-gnu/libstdc++.so.6:$LD_LIBRARY_PATH
    %setenv LD_PRELOAD /usr/lib/x86_64-linux-gnu/libstdc++.so.6
    
    ipaths = {'-I/Applications/MATLAB_R2018b.app/extern/include',...
        '-I/home/marta/hypro/build/resources/antlr_build/include/antlr4-runtime',...
        '-I/home/marta/hypro/build/resources/antlr_build/include/antlr4-runtime/misc',...
        '-I/home/marta/hypro/build/resources/antlr_build/include/antlr4-runtime/atn',...
        '-I/home/marta/hypro/build/resources/antlr_build/include/antlr4-runtime/dfa',...
        '-I/home/marta/hypro/build/resources/antlr_build/include/antlr4-runtime/tree',...
        '-I/home/marta/hypro/build/resources/antlr_build/include/antlr4-runtime/support',...
        '-I/home/marta/hypro/src','-I/usr/bin/c++','-I/home/marta/carl/src',...
        '-I/usr/local/include','-I/home/marta/carl/resources/include',...
        '-L/home/marta/hypro/build','-lhypro','CXXFLAGS=\$CXXFLAGS -std=c++17',...
        '-IC:/Users/marta/carl/build/resources/include','-lgmp';};
    
        mex -setup c++; 
        mex('-v',ipaths{:},srcFile);    
    else
        %Windows
        mexErrMsgTxt('Not implemented');
    end
end

    




