srcFile = "HyProBox.cpp";
ipaths = {};
if ismac
    %Mac
%     matlab = dir(fullfile('/Applications','**','mex.h'));
%     antlr4_runtime = dir(fullfile('/Users','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/antlr4-common.h'));
%     misc = dir(fullfile('/Users','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/misc/Interval.h'));
%     atn = dir(fullfile('/Users','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/atn/ATN.h'));  
%     dfa = dir(fullfile('/Users','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/dfa/DFA.h')); 
%     tree = dir(fullfile('/Usershome','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/tree/Trees.h'));
%     support = dir(fullfile('/Users','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/support/Any.h'));
%     hypro = dir(fullfile('/Users','**','/hypro/src/hypro/types.h'));
%     carl = dir(fullfile('/Users','**','/carl/src/CMakeLists.txt'));
%     local_include = '/usr/local/include';
%     carl_resources = dir(fullfile('/Users','**','/carl/build/resources/include/gmp.h'));
%     compiler = '/usr/local/opt/llvm/include/c++/v1/';
%     hypro_build = dir(fullfile('/Users','**','/hypro/build/CMakeCache.txt'));
%     hypro_lib = dir(fullfile('/Users','**','/hypro/build/libhypro.so'));
%     dgtest = '-DGTEST_USE_OWN_TR1_TUPLE=1 -std=c++17 -stdlib=libc++';
%     llvm = '/usr/local/opt/llvm/lib';
%     ipaths={strcat('-I', matlab.folder),strcat('-I', antlr4_runtime.folder),...
%     strcat('-I', misc.folder), strcat('-I', atn.folder), strcat('-I', dfa.folder),...
%     strcat('-I', tree.folder), strcat('-I', support.folder), strcat('-I', hypro.folder),...
%     strcat('-I', carl.folder), strcat('-I', local_include), strcat('-I', carl_resources.folder),...
%     strcat('-I', compiler), strcat('-L', hypro_build.folder), dgtest, strcat('-L', llvm),...
%     '-lhypro',  strcat('LDFLAGS=$LDFLAGS -Wl -rpath ', hypro_build.folder),...
%     'COMPFLAGS=$COMPFLAGS -std=c++17', 'CXXFLAGS=\$CXXFLAGS -std=c++17';};
    
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
    '-L/usr/local/opt/llvm/lib','-L/Users/marta/hypro/build','-lhypro',...
    'LDFLAGS=$LDFLAGS -Wl -rpath /Users/marta/hypro/build';};

elseif isunix
    %Linux
    matlab = dir(fullfile('/usr','**','mex.h'));
    antlr4_runtime = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/antlr4-common.h'));
    misc = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/misc/Interval.h'));
    atn = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/atn/ATN.h'));  
    dfa = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/dfa/DFA.h')); 
    tree = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/tree/Trees.h'));
    support = dir(fullfile('/home','**','/hypro/build/resources/antlr_build/include/antlr4-runtime/support/Any.h'));
    hypro = dir(fullfile('/home','**','/hypro/src/hypro/types.h'));
    carl = dir(fullfile('/home','**','/carl/src/CMakeLists.txt'));
    local_include = '/usr/local/include';
    carl_resources = dir(fullfile('/home','**','/carl/build/resources/include/gmp.h'));
    compiler = '/usr/bin/c++';
    hypro_build = dir(fullfile('/home','**','/hypro/build/CMakeCache.txt'));
    hypro_lib = dir(fullfile('/home','**','/hypro/build/libhypro.so'));
    
    ipaths={strcat('-I', matlab.folder),strcat('-I', antlr4_runtime.folder),...
    strcat('-I', misc.folder), strcat('-I', atn.folder), strcat('-I', dfa.folder),...
    strcat('-I', tree.folder), strcat('-I', support.folder), strcat('-I', hypro.folder),...
    strcat('-I', carl.folder), strcat('-I', local_include), strcat('-I', carl_resources.folder),...
    strcat('-I', compiler), strcat('-L', hypro_build.folder, 'libhypro.so'),'COMPFLAGS=$COMPFLAGS -std=c++17',...
    'CXXFLAGS=\$CXXFLAGS -std=c++17';};

else
    %Windows
    mexErrMsgTxt('Not implemented');
end

    
mex -setup c++;
mex('-v',ipaths{:},'CC=/usr/local/opt/llvm/bin/clang','CXX=/usr/local/opt/llvm/bin/clang++','COMPFLAGS=$COMPFLAGS -std=c++17', 'CXXFLAGS=\$CXXFLAGS -std=c++17',srcFile);
%mex('-v',ipaths{:},srcFile)




