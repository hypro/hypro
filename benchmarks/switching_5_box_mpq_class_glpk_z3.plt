# settings
set term pdf
set output "switching_5_box_mpq_class_glpk_z3.pdf
set xtics autofreq
set ytics autofreq
set grid back
# axis settings
set xzeroaxis 
set zeroaxis 
set xtics axis 
set xrange [-11.4176:5.53328] 
set yzeroaxis 
set ytics axis 
set yrange [-2.48025:8.32041] 

# plotting sets
set object 1 polygon from \
  3.09983, 4.00011 to \
  3.13242, 4.00011 to \
  3.13242, 3.97066 to \
  3.09983, 3.97066 to \
  3.09983, 4.00011 front fs empty border lc rgb '#6165' lw 0.200001
set object 2 polygon from \
  3.13164, 3.97092 to \
  3.16464, 3.97092 to \
  3.16464, 3.9411 to \
  3.13164, 3.9411 to \
  3.13164, 3.97092 front fs empty border lc rgb '#6165' lw 0.200001
set object 3 polygon from \
  3.16298, 3.94146 to \
  3.1964, 3.94146 to \
  3.1964, 3.91126 to \
  3.16298, 3.91126 to \
  3.16298, 3.94146 front fs empty border lc rgb '#6165' lw 0.200001
set object 4 polygon from \
  3.19384, 3.91175 to \
  3.22769, 3.91175 to \
  3.22769, 3.88117 to \
  3.19384, 3.88117 to \
  3.19384, 3.91175 front fs empty border lc rgb '#6165' lw 0.200001
set object 5 polygon from \
  3.22423, 3.88179 to \
  3.25851, 3.88179 to \
  3.25851, 3.85081 to \
  3.22423, 3.85081 to \
  3.22423, 3.88179 front fs empty border lc rgb '#6165' lw 0.200001
set object 6 polygon from \
  3.25413, 3.85158 to \
  3.28885, 3.85158 to \
  3.28885, 3.82021 to \
  3.25413, 3.82021 to \
  3.25413, 3.85158 front fs empty border lc rgb '#6165' lw 0.200001
set object 7 polygon from \
  3.28355, 3.82113 to \
  3.31871, 3.82113 to \
  3.31871, 3.78936 to \
  3.28355, 3.78936 to \
  3.28355, 3.82113 front fs empty border lc rgb '#6165' lw 0.200001
set object 8 polygon from \
  3.31246, 3.79045 to \
  3.34808, 3.79045 to \
  3.34808, 3.75827 to \
  3.31246, 3.75827 to \
  3.31246, 3.79045 front fs empty border lc rgb '#6165' lw 0.200001
set object 9 polygon from \
  3.34088, 3.75954 to \
  3.37696, 3.75954 to \
  3.37696, 3.72695 to \
  3.34088, 3.72695 to \
  3.34088, 3.75954 front fs empty border lc rgb '#6165' lw 0.200001
set object 10 polygon from \
  3.36879, 3.72841 to \
  3.40535, 3.72841 to \
  3.40535, 3.6954 to \
  3.36879, 3.6954 to \
  3.36879, 3.72841 front fs empty border lc rgb '#6165' lw 0.200001
set object 11 polygon from \
  3.3962, 3.69706 to \
  3.43323, 3.69706 to \
  3.43323, 3.66363 to \
  3.3962, 3.66363 to \
  3.3962, 3.69706 front fs empty border lc rgb '#6165' lw 0.200001
set object 12 polygon from \
  3.42309, 3.66551 to \
  3.46061, 3.66551 to \
  3.46061, 3.63164 to \
  3.42309, 3.63164 to \
  3.42309, 3.66551 front fs empty border lc rgb '#6165' lw 0.200001
set object 13 polygon from \
  3.44946, 3.63376 to \
  3.48748, 3.63376 to \
  3.48748, 3.59945 to \
  3.44946, 3.59945 to \
  3.44946, 3.63376 front fs empty border lc rgb '#6165' lw 0.200001
set object 14 polygon from \
  3.47531, 3.60181 to \
  3.51384, 3.60181 to \
  3.51384, 3.56705 to \
  3.47531, 3.56705 to \
  3.47531, 3.60181 front fs empty border lc rgb '#6165' lw 0.200001
set object 15 polygon from \
  3.50064, 3.56967 to \
  3.53968, 3.56967 to \
  3.53968, 3.53446 to \
  3.50064, 3.53446 to \
  3.50064, 3.56967 front fs empty border lc rgb '#6165' lw 0.200001
set object 16 polygon from \
  3.52543, 3.53735 to \
  3.565, 3.53735 to \
  3.565, 3.50168 to \
  3.52543, 3.50168 to \
  3.52543, 3.53735 front fs empty border lc rgb '#6165' lw 0.200001
set object 17 polygon from \
  3.54969, 3.50485 to \
  3.58979, 3.50485 to \
  3.58979, 3.46872 to \
  3.54969, 3.46872 to \
  3.54969, 3.50485 front fs empty border lc rgb '#6165' lw 0.200001
set object 18 polygon from \
  3.57341, 3.47219 to \
  3.61405, 3.47219 to \
  3.61405, 3.43558 to \
  3.57341, 3.43558 to \
  3.57341, 3.47219 front fs empty border lc rgb '#6165' lw 0.200001
set object 19 polygon from \
  3.59658, 3.43936 to \
  3.63777, 3.43936 to \
  3.63777, 3.40226 to \
  3.59658, 3.40226 to \
  3.59658, 3.43936 front fs empty border lc rgb '#6165' lw 0.200001
set object 20 polygon from \
  3.61921, 3.40637 to \
  3.66096, 3.40637 to \
  3.66096, 3.36879 to \
  3.61921, 3.36879 to \
  3.61921, 3.40637 front fs empty border lc rgb '#6165' lw 0.200001
set object 21 polygon from \
  3.64129, 3.37323 to \
  3.68361, 3.37323 to \
  3.68361, 3.33515 to \
  3.64129, 3.33515 to \
  3.64129, 3.37323 front fs empty border lc rgb '#6165' lw 0.200001
set object 22 polygon from \
  3.66282, 3.33995 to \
  3.70572, 3.33995 to \
  3.70572, 3.30137 to \
  3.66282, 3.30137 to \
  3.66282, 3.33995 front fs empty border lc rgb '#6165' lw 0.200001
set object 23 polygon from \
  3.68379, 3.30653 to \
  3.72728, 3.30653 to \
  3.72728, 3.26744 to \
  3.68379, 3.26744 to \
  3.68379, 3.30653 front fs empty border lc rgb '#6165' lw 0.200001
set object 24 polygon from \
  3.70419, 3.27299 to \
  3.74828, 3.27299 to \
  3.74828, 3.23337 to \
  3.70419, 3.23337 to \
  3.70419, 3.27299 front fs empty border lc rgb '#6165' lw 0.200001
set object 25 polygon from \
  3.72404, 3.23931 to \
  3.76874, 3.23931 to \
  3.76874, 3.19916 to \
  3.72404, 3.19916 to \
  3.72404, 3.23931 front fs empty border lc rgb '#6165' lw 0.200001
set object 26 polygon from \
  3.74332, 3.20552 to \
  3.78864, 3.20552 to \
  3.78864, 3.16484 to \
  3.74332, 3.16484 to \
  3.74332, 3.20552 front fs empty border lc rgb '#6165' lw 0.200001
set object 27 polygon from \
  3.76202, 3.17162 to \
  3.80797, 3.17162 to \
  3.80797, 3.13039 to \
  3.76202, 3.13039 to \
  3.76202, 3.17162 front fs empty border lc rgb '#6165' lw 0.200001
set object 28 polygon from \
  3.78016, 3.13762 to \
  3.82675, 3.13762 to \
  3.82675, 3.09583 to \
  3.78016, 3.09583 to \
  3.78016, 3.13762 front fs empty border lc rgb '#6165' lw 0.200001
set object 29 polygon from \
  3.79772, 3.10352 to \
  3.84496, 3.10352 to \
  3.84496, 3.06117 to \
  3.79772, 3.06117 to \
  3.79772, 3.10352 front fs empty border lc rgb '#6165' lw 0.200001
set object 30 polygon from \
  3.8147, 3.06932 to \
  3.86261, 3.06932 to \
  3.86261, 3.02641 to \
  3.8147, 3.02641 to \
  3.8147, 3.06932 front fs empty border lc rgb '#6165' lw 0.200001
set object 31 polygon from \
  3.8311, 3.03505 to \
  3.87968, 3.03505 to \
  3.87968, 2.99155 to \
  3.8311, 2.99155 to \
  3.8311, 3.03505 front fs empty border lc rgb '#6165' lw 0.200001
set object 32 polygon from \
  3.84692, 3.00069 to \
  3.89618, 3.00069 to \
  3.89618, 2.95661 to \
  3.84692, 2.95661 to \
  3.84692, 3.00069 front fs empty border lc rgb '#6165' lw 0.200001
set object 33 polygon from \
  3.86216, 2.96627 to \
  3.91211, 2.96627 to \
  3.91211, 2.92158 to \
  3.86216, 2.92158 to \
  3.86216, 2.96627 front fs empty border lc rgb '#6165' lw 0.200001
set object 34 polygon from \
  3.8768, 2.93178 to \
  3.92747, 2.93178 to \
  3.92747, 2.88649 to \
  3.8768, 2.88649 to \
  3.8768, 2.93178 front fs empty border lc rgb '#6165' lw 0.200001
set object 35 polygon from \
  3.89086, 2.89723 to \
  3.94224, 2.89723 to \
  3.94224, 2.85132 to \
  3.89086, 2.85132 to \
  3.89086, 2.89723 front fs empty border lc rgb '#6165' lw 0.200001
set object 36 polygon from \
  3.90432, 2.86264 to \
  3.95644, 2.86264 to \
  3.95644, 2.8161 to \
  3.90432, 2.8161 to \
  3.90432, 2.86264 front fs empty border lc rgb '#6165' lw 0.200001
set object 37 polygon from \
  3.9172, 2.828 to \
  3.97005, 2.828 to \
  3.97005, 2.78082 to \
  3.9172, 2.78082 to \
  3.9172, 2.828 front fs empty border lc rgb '#6165' lw 0.200001
set object 38 polygon from \
  3.92947, 2.79332 to \
  3.98309, 2.79332 to \
  3.98309, 2.7455 to \
  3.92947, 2.7455 to \
  3.92947, 2.79332 front fs empty border lc rgb '#6165' lw 0.200001
set object 39 polygon from \
  3.94115, 2.75861 to \
  3.99553, 2.75861 to \
  3.99553, 2.71014 to \
  3.94115, 2.71014 to \
  3.94115, 2.75861 front fs empty border lc rgb '#6165' lw 0.200001
set object 40 polygon from \
  3.95223, 2.72388 to \
  4.0074, 2.72388 to \
  4.0074, 2.67474 to \
  3.95223, 2.67474 to \
  3.95223, 2.72388 front fs empty border lc rgb '#6165' lw 0.200001
set object 41 polygon from \
  3.96272, 2.68913 to \
  4.01867, 2.68913 to \
  4.01867, 2.63931 to \
  3.96272, 2.63931 to \
  3.96272, 2.68913 front fs empty border lc rgb '#6165' lw 0.200001
set object 42 polygon from \
  3.9726, 2.65437 to \
  4.02936, 2.65437 to \
  4.02936, 2.60387 to \
  3.9726, 2.60387 to \
  3.9726, 2.65437 front fs empty border lc rgb '#6165' lw 0.200001
set object 43 polygon from \
  3.98188, 2.61961 to \
  4.03946, 2.61961 to \
  4.03946, 2.5684 to \
  3.98188, 2.5684 to \
  3.98188, 2.61961 front fs empty border lc rgb '#6165' lw 0.200001
set object 44 polygon from \
  3.99056, 2.58485 to \
  4.04897, 2.58485 to \
  4.04897, 2.53293 to \
  3.99056, 2.53293 to \
  3.99056, 2.58485 front fs empty border lc rgb '#6165' lw 0.200001
set object 45 polygon from \
  3.99863, 2.5501 to \
  4.05789, 2.5501 to \
  4.05789, 2.49746 to \
  3.99863, 2.49746 to \
  3.99863, 2.5501 front fs empty border lc rgb '#6165' lw 0.200001
set object 46 polygon from \
  4.0061, 2.51536 to \
  4.06622, 2.51536 to \
  4.06622, 2.462 to \
  4.0061, 2.462 to \
  4.0061, 2.51536 front fs empty border lc rgb '#6165' lw 0.200001
set object 47 polygon from \
  4.01296, 2.48065 to \
  4.07395, 2.48065 to \
  4.07395, 2.42654 to \
  4.01296, 2.42654 to \
  4.01296, 2.48065 front fs empty border lc rgb '#6165' lw 0.200001
set object 48 polygon from \
  4.01922, 2.44597 to \
  4.0811, 2.44597 to \
  4.0811, 2.39111 to \
  4.01922, 2.39111 to \
  4.01922, 2.44597 front fs empty border lc rgb '#6165' lw 0.200001
set object 49 polygon from \
  4.02487, 2.41132 to \
  4.08765, 2.41132 to \
  4.08765, 2.35569 to \
  4.02487, 2.35569 to \
  4.02487, 2.41132 front fs empty border lc rgb '#6165' lw 0.200001
set object 50 polygon from \
  4.02991, 2.37672 to \
  4.09361, 2.37672 to \
  4.09361, 2.32031 to \
  4.02991, 2.32031 to \
  4.02991, 2.37672 front fs empty border lc rgb '#6165' lw 0.200001
set object 51 polygon from \
  4.03435, 2.34216 to \
  4.09898, 2.34216 to \
  4.09898, 2.28497 to \
  4.03435, 2.28497 to \
  4.03435, 2.34216 front fs empty border lc rgb '#6165' lw 0.200001
set object 52 polygon from \
  4.03818, 2.30767 to \
  4.10376, 2.30767 to \
  4.10376, 2.24967 to \
  4.03818, 2.24967 to \
  4.03818, 2.30767 front fs empty border lc rgb '#6165' lw 0.200001
set object 53 polygon from \
  4.0414, 2.27323 to \
  4.10794, 2.27323 to \
  4.10794, 2.21442 to \
  4.0414, 2.21442 to \
  4.0414, 2.27323 front fs empty border lc rgb '#6165' lw 0.200001
set object 54 polygon from \
  4.04402, 2.23886 to \
  4.11153, 2.23886 to \
  4.11153, 2.17922 to \
  4.04402, 2.17922 to \
  4.04402, 2.23886 front fs empty border lc rgb '#6165' lw 0.200001
set object 55 polygon from \
  4.04603, 2.20457 to \
  4.11454, 2.20457 to \
  4.11454, 2.14409 to \
  4.04603, 2.14409 to \
  4.04603, 2.20457 front fs empty border lc rgb '#6165' lw 0.200001
set object 56 polygon from \
  4.04743, 2.17036 to \
  4.11695, 2.17036 to \
  4.11695, 2.10903 to \
  4.04743, 2.10903 to \
  4.04743, 2.17036 front fs empty border lc rgb '#6165' lw 0.200001
set object 57 polygon from \
  4.04823, 2.13624 to \
  4.11877, 2.13624 to \
  4.11877, 2.07404 to \
  4.04823, 2.07404 to \
  4.04823, 2.13624 front fs empty border lc rgb '#6165' lw 0.200001
set object 58 polygon from \
  4.04842, 2.10221 to \
  4.12, 2.10221 to \
  4.12, 2.03913 to \
  4.04842, 2.03913 to \
  4.04842, 2.10221 front fs empty border lc rgb '#6165' lw 0.200001
set object 59 polygon from \
  4.048, 2.06828 to \
  4.12064, 2.06828 to \
  4.12064, 2.00431 to \
  4.048, 2.00431 to \
  4.048, 2.06828 front fs empty border lc rgb '#6165' lw 0.200001
set object 60 polygon from \
  4.04698, 2.03447 to \
  4.1207, 2.03447 to \
  4.1207, 1.96958 to \
  4.04698, 1.96958 to \
  4.04698, 2.03447 front fs empty border lc rgb '#6165' lw 0.200001
set object 61 polygon from \
  4.04536, 2.00076 to \
  4.12017, 2.00076 to \
  4.12017, 1.93496 to \
  4.04536, 1.93496 to \
  4.04536, 2.00076 front fs empty border lc rgb '#6165' lw 0.200001
set object 62 polygon from \
  4.04313, 1.96718 to \
  4.11905, 1.96718 to \
  4.11905, 1.90043 to \
  4.04313, 1.90043 to \
  4.04313, 1.96718 front fs empty border lc rgb '#6165' lw 0.200001
set object 63 polygon from \
  4.04031, 1.93372 to \
  4.11736, 1.93372 to \
  4.11736, 1.86603 to \
  4.04031, 1.86603 to \
  4.04031, 1.93372 front fs empty border lc rgb '#6165' lw 0.200001
set object 64 polygon from \
  4.03688, 1.90039 to \
  4.11508, 1.90039 to \
  4.11508, 1.83173 to \
  4.03688, 1.83173 to \
  4.03688, 1.90039 front fs empty border lc rgb '#6165' lw 0.200001
set object 65 polygon from \
  4.03286, 1.86721 to \
  4.11222, 1.86721 to \
  4.11222, 1.79757 to \
  4.03286, 1.79757 to \
  4.03286, 1.86721 front fs empty border lc rgb '#6165' lw 0.200001
set object 66 polygon from \
  4.02824, 1.83417 to \
  4.10878, 1.83417 to \
  4.10878, 1.76353 to \
  4.02824, 1.76353 to \
  4.02824, 1.83417 front fs empty border lc rgb '#6165' lw 0.200001
set object 67 polygon from \
  4.02302, 1.80128 to \
  4.10476, 1.80128 to \
  4.10476, 1.72963 to \
  4.02302, 1.72963 to \
  4.02302, 1.80128 front fs empty border lc rgb '#6165' lw 0.200001
set object 68 polygon from \
  4.01721, 1.76855 to \
  4.10017, 1.76855 to \
  4.10017, 1.69587 to \
  4.01721, 1.69587 to \
  4.01721, 1.76855 front fs empty border lc rgb '#6165' lw 0.200001
set object 69 polygon from \
  4.0108, 1.73598 to \
  4.095, 1.73598 to \
  4.095, 1.66226 to \
  4.0108, 1.66226 to \
  4.0108, 1.73598 front fs empty border lc rgb '#6165' lw 0.200001
set object 70 polygon from \
  4.00381, 1.70358 to \
  4.08927, 1.70358 to \
  4.08927, 1.6288 to \
  4.00381, 1.6288 to \
  4.00381, 1.70358 front fs empty border lc rgb '#6165' lw 0.200001
set object 71 polygon from \
  3.99623, 1.67135 to \
  4.08296, 1.67135 to \
  4.08296, 1.5955 to \
  3.99623, 1.5955 to \
  3.99623, 1.67135 front fs empty border lc rgb '#6165' lw 0.200001
set object 72 polygon from \
  3.98806, 1.63931 to \
  4.07609, 1.63931 to \
  4.07609, 1.56236 to \
  3.98806, 1.56236 to \
  3.98806, 1.63931 front fs empty border lc rgb '#6165' lw 0.200001
set object 73 polygon from \
  3.9793, 1.60746 to \
  4.06866, 1.60746 to \
  4.06866, 1.5294 to \
  3.9793, 1.5294 to \
  3.9793, 1.60746 front fs empty border lc rgb '#6165' lw 0.200001
set object 74 polygon from \
  3.96997, 1.5758 to \
  4.06066, 1.5758 to \
  4.06066, 1.49661 to \
  3.96997, 1.49661 to \
  3.96997, 1.5758 front fs empty border lc rgb '#6165' lw 0.200001
set object 75 polygon from \
  3.96005, 1.54434 to \
  4.05211, 1.54434 to \
  4.05211, 1.464 to \
  3.96005, 1.464 to \
  3.96005, 1.54434 front fs empty border lc rgb '#6165' lw 0.200001
set object 76 polygon from \
  3.94956, 1.51308 to \
  4.043, 1.51308 to \
  4.043, 1.43158 to \
  3.94956, 1.43158 to \
  3.94956, 1.51308 front fs empty border lc rgb '#6165' lw 0.200001
set object 77 polygon from \
  3.93849, 1.48203 to \
  4.03334, 1.48203 to \
  4.03334, 1.39936 to \
  3.93849, 1.39936 to \
  3.93849, 1.48203 front fs empty border lc rgb '#6165' lw 0.200001
set object 78 polygon from \
  3.92685, 1.4512 to \
  4.02313, 1.4512 to \
  4.02313, 1.36733 to \
  3.92685, 1.36733 to \
  3.92685, 1.4512 front fs empty border lc rgb '#6165' lw 0.200001
set object 79 polygon from \
  3.91464, 1.4206 to \
  4.01237, 1.4206 to \
  4.01237, 1.3355 to \
  3.91464, 1.3355 to \
  3.91464, 1.4206 front fs empty border lc rgb '#6165' lw 0.200001
set object 80 polygon from \
  3.90187, 1.39022 to \
  4.00107, 1.39022 to \
  4.00107, 1.30388 to \
  3.90187, 1.30388 to \
  3.90187, 1.39022 front fs empty border lc rgb '#6165' lw 0.200001
set object 81 polygon from \
  3.88853, 1.36007 to \
  3.98923, 1.36007 to \
  3.98923, 1.27248 to \
  3.88853, 1.27248 to \
  3.88853, 1.36007 front fs empty border lc rgb '#6165' lw 0.200001
set object 82 polygon from \
  3.87463, 1.33016 to \
  3.97685, 1.33016 to \
  3.97685, 1.2413 to \
  3.87463, 1.2413 to \
  3.87463, 1.33016 front fs empty border lc rgb '#6165' lw 0.200001
set object 83 polygon from \
  3.86018, 1.3005 to \
  3.96393, 1.3005 to \
  3.96393, 1.21034 to \
  3.86018, 1.21034 to \
  3.86018, 1.3005 front fs empty border lc rgb '#6165' lw 0.200001
set object 84 polygon from \
  3.84517, 1.27109 to \
  3.95049, 1.27109 to \
  3.95049, 1.17961 to \
  3.84517, 1.17961 to \
  3.84517, 1.27109 front fs empty border lc rgb '#6165' lw 0.200001
set object 85 polygon from \
  3.82961, 1.24193 to \
  3.93653, 1.24193 to \
  3.93653, 1.14912 to \
  3.82961, 1.14912 to \
  3.82961, 1.24193 front fs empty border lc rgb '#6165' lw 0.200001
set object 86 polygon from \
  3.8135, 1.21303 to \
  3.92204, 1.21303 to \
  3.92204, 1.11886 to \
  3.8135, 1.11886 to \
  3.8135, 1.21303 front fs empty border lc rgb '#6165' lw 0.200001
set object 87 polygon from \
  3.79685, 1.1844 to \
  3.90703, 1.1844 to \
  3.90703, 1.08885 to \
  3.79685, 1.08885 to \
  3.79685, 1.1844 front fs empty border lc rgb '#6165' lw 0.200001
set object 88 polygon from \
  3.77966, 1.15604 to \
  3.89151, 1.15604 to \
  3.89151, 1.05909 to \
  3.77966, 1.05909 to \
  3.77966, 1.15604 front fs empty border lc rgb '#6165' lw 0.200001
set object 89 polygon from \
  3.76193, 1.12795 to \
  3.87548, 1.12795 to \
  3.87548, 1.02958 to \
  3.76193, 1.02958 to \
  3.76193, 1.12795 front fs empty border lc rgb '#6165' lw 0.200001
set object 90 polygon from \
  3.74368, 1.10015 to \
  3.85894, 1.10015 to \
  3.85894, 1.00033 to \
  3.74368, 1.00033 to \
  3.74368, 1.10015 front fs empty border lc rgb '#6165' lw 0.200001
set object 91 polygon from \
  3.72489, 1.07263 to \
  3.84191, 1.07263 to \
  3.84191, 0.971344 to \
  3.72489, 0.971344 to \
  3.72489, 1.07263 front fs empty border lc rgb '#6165' lw 0.200001
set object 92 polygon from \
  3.70558, 1.04541 to \
  3.82437, 1.04541 to \
  3.82437, 0.942627 to \
  3.70558, 0.942627 to \
  3.70558, 1.04541 front fs empty border lc rgb '#6165' lw 0.200001
set object 93 polygon from \
  3.68575, 1.01847 to \
  3.80635, 1.01847 to \
  3.80635, 0.914184 to \
  3.68575, 0.914184 to \
  3.68575, 1.01847 front fs empty border lc rgb '#6165' lw 0.200001
set object 94 polygon from \
  3.6654, 0.99184 to \
  3.78783, 0.99184 to \
  3.78783, 0.886017 to \
  3.6654, 0.886017 to \
  3.6654, 0.99184 front fs empty border lc rgb '#6165' lw 0.200001
set object 95 polygon from \
  3.64454, 0.965516 to \
  3.76883, 0.965516 to \
  3.76883, 0.858133 to \
  3.64454, 0.858133 to \
  3.64454, 0.965516 front fs empty border lc rgb '#6165' lw 0.200001
set object 96 polygon from \
  3.62318, 0.939502 to \
  3.74936, 0.939502 to \
  3.74936, 0.830535 to \
  3.62318, 0.830535 to \
  3.62318, 0.939502 front fs empty border lc rgb '#6165' lw 0.200001
set object 97 polygon from \
  3.60131, 0.913803 to \
  3.72941, 0.913803 to \
  3.72941, 0.803227 to \
  3.60131, 0.803227 to \
  3.60131, 0.913803 front fs empty border lc rgb '#6165' lw 0.200001
set object 98 polygon from \
  3.57894, 0.888424 to \
  3.70899, 0.888424 to \
  3.70899, 0.776213 to \
  3.57894, 0.776213 to \
  3.57894, 0.888424 front fs empty border lc rgb '#6165' lw 0.200001
set object 99 polygon from \
  3.55608, 0.863368 to \
  3.68811, 0.863368 to \
  3.68811, 0.749499 to \
  3.55608, 0.749499 to \
  3.55608, 0.863368 front fs empty border lc rgb '#6165' lw 0.200001
set object 100 polygon from \
  3.53273, 0.838642 to \
  3.66677, 0.838642 to \
  3.66677, 0.723087 to \
  3.53273, 0.723087 to \
  3.53273, 0.838642 front fs empty border lc rgb '#6165' lw 0.200001
set object 101 polygon from \
  3.5089, 0.814249 to \
  3.64498, 0.814249 to \
  3.64498, 0.696982 to \
  3.5089, 0.696982 to \
  3.5089, 0.814249 front fs empty border lc rgb '#6165' lw 0.200001
set object 102 polygon from \
  3.48458, 0.790193 to \
  3.62274, 0.790193 to \
  3.62274, 0.671188 to \
  3.48458, 0.671188 to \
  3.48458, 0.790193 front fs empty border lc rgb '#6165' lw 0.200001
set object 103 polygon from \
  3.45979, 0.766479 to \
  3.60006, 0.766479 to \
  3.60006, 0.645708 to \
  3.45979, 0.645708 to \
  3.45979, 0.766479 front fs empty border lc rgb '#6165' lw 0.200001
set object 104 polygon from \
  3.43454, 0.743111 to \
  3.57694, 0.743111 to \
  3.57694, 0.620547 to \
  3.43454, 0.620547 to \
  3.43454, 0.743111 front fs empty border lc rgb '#6165' lw 0.200001
set object 105 polygon from \
  3.40881, 0.720092 to \
  3.55339, 0.720092 to \
  3.55339, 0.595708 to \
  3.40881, 0.595708 to \
  3.40881, 0.720092 front fs empty border lc rgb '#6165' lw 0.200001
set object 106 polygon from \
  3.38263, 0.697428 to \
  3.52941, 0.697428 to \
  3.52941, 0.571196 to \
  3.38263, 0.571196 to \
  3.38263, 0.697428 front fs empty border lc rgb '#6165' lw 0.200001
set object 107 polygon from \
  3.35599, 0.675123 to \
  3.50502, 0.675123 to \
  3.50502, 0.547012 to \
  3.35599, 0.547012 to \
  3.35599, 0.675123 front fs empty border lc rgb '#6165' lw 0.200001
set object 108 polygon from \
  3.32891, 0.653179 to \
  3.48021, 0.653179 to \
  3.48021, 0.523161 to \
  3.32891, 0.523161 to \
  3.32891, 0.653179 front fs empty border lc rgb '#6165' lw 0.200001
set object 109 polygon from \
  3.30138, 0.631601 to \
  3.45499, 0.631601 to \
  3.45499, 0.499647 to \
  3.30138, 0.499647 to \
  3.30138, 0.631601 front fs empty border lc rgb '#6165' lw 0.200001
set object 110 polygon from \
  3.27341, 0.610393 to \
  3.42937, 0.610393 to \
  3.42937, 0.476472 to \
  3.27341, 0.476472 to \
  3.27341, 0.610393 front fs empty border lc rgb '#6165' lw 0.200001
set object 111 polygon from \
  3.24501, 0.589559 to \
  3.40336, 0.589559 to \
  3.40336, 0.453641 to \
  3.24501, 0.453641 to \
  3.24501, 0.589559 front fs empty border lc rgb '#6165' lw 0.200001
set object 112 polygon from \
  3.21618, 0.569102 to \
  3.37695, 0.569102 to \
  3.37695, 0.431155 to \
  3.21618, 0.431155 to \
  3.21618, 0.569102 front fs empty border lc rgb '#6165' lw 0.200001
set object 113 polygon from \
  3.18693, 0.549025 to \
  3.35016, 0.549025 to \
  3.35016, 0.409019 to \
  3.18693, 0.409019 to \
  3.18693, 0.549025 front fs empty border lc rgb '#6165' lw 0.200001
set object 114 polygon from \
  3.15727, 0.529333 to \
  3.32299, 0.529333 to \
  3.32299, 0.387235 to \
  3.15727, 0.387235 to \
  3.15727, 0.529333 front fs empty border lc rgb '#6165' lw 0.200001
set object 115 polygon from \
  3.12719, 0.510029 to \
  3.29546, 0.510029 to \
  3.29546, 0.365806 to \
  3.12719, 0.365806 to \
  3.12719, 0.510029 front fs empty border lc rgb '#6165' lw 0.200001
set object 116 polygon from \
  3.09671, 0.491116 to \
  3.26755, 0.491116 to \
  3.26755, 0.344735 to \
  3.09671, 0.344735 to \
  3.09671, 0.491116 front fs empty border lc rgb '#6165' lw 0.200001
set object 117 polygon from \
  3.06583, 0.472597 to \
  3.23929, 0.472597 to \
  3.23929, 0.324026 to \
  3.06583, 0.324026 to \
  3.06583, 0.472597 front fs empty border lc rgb '#6165' lw 0.200001
set object 118 polygon from \
  3.03456, 0.454476 to \
  3.21068, 0.454476 to \
  3.21068, 0.303679 to \
  3.03456, 0.303679 to \
  3.03456, 0.454476 front fs empty border lc rgb '#6165' lw 0.200001
set object 119 polygon from \
  3.0029, 0.436755 to \
  3.18172, 0.436755 to \
  3.18172, 0.283699 to \
  3.0029, 0.283699 to \
  3.0029, 0.436755 front fs empty border lc rgb '#6165' lw 0.200001
set object 120 polygon from \
  3, 0.419439 to \
  3.15242, 0.419439 to \
  3.15242, 0.264088 to \
  3, 0.264088 to \
  3, 0.419439 front fs empty border lc rgb '#6165' lw 0.200001
set object 121 polygon from \
  3, 0.402278 to \
  3.12279, 0.402278 to \
  3.12279, 0.244848 to \
  3, 0.244848 to \
  3, 0.402278 front fs empty border lc rgb '#6165' lw 0.200001
set object 122 polygon from \
  3, 0.385248 to \
  3.09283, 0.385248 to \
  3.09283, 0.225982 to \
  3, 0.225982 to \
  3, 0.385248 front fs empty border lc rgb '#6165' lw 0.200001
set object 123 polygon from \
  3, 0.368348 to \
  3.06254, 0.368348 to \
  3.06254, 0.207495 to \
  3, 0.207495 to \
  3, 0.368348 front fs empty border lc rgb '#6165' lw 0.200001
set object 124 polygon from \
  3, 0.351577 to \
  3.03193, 0.351577 to \
  3.03193, 0.189388 to \
  3, 0.189388 to \
  3, 0.351577 front fs empty border lc rgb '#6165' lw 0.200001
set object 125 polygon from \
  3, 0.334936 to \
  3.00099, 0.334936 to \
  3.00099, 0.171666 to \
  3, 0.171666 to \
  3, 0.334936 front fs empty border lc rgb '#6165' lw 0.200001
set object 126 polygon from \
  2.96554, 0.4262 to \
  3.00006, 0.4262 to \
  3.00006, 0.171612 to \
  2.96554, 0.171612 to \
  2.96554, 0.4262 front fs empty border lc rgb '#98a1' lw 0.200001
set object 127 polygon from \
  2.93094, 0.433051 to \
  2.97075, 0.433051 to \
  2.97075, 0.177016 to \
  2.93094, 0.177016 to \
  2.93094, 0.433051 front fs empty border lc rgb '#98a1' lw 0.200001
set object 128 polygon from \
  2.89619, 0.440044 to \
  2.94133, 0.440044 to \
  2.94133, 0.182547 to \
  2.89619, 0.182547 to \
  2.89619, 0.440044 front fs empty border lc rgb '#98a1' lw 0.200001
set object 129 polygon from \
  2.86131, 0.44718 to \
  2.91181, 0.44718 to \
  2.91181, 0.188205 to \
  2.86131, 0.188205 to \
  2.86131, 0.44718 front fs empty border lc rgb '#98a1' lw 0.200001
set object 130 polygon from \
  2.8263, 0.454458 to \
  2.88219, 0.454458 to \
  2.88219, 0.19399 to \
  2.8263, 0.19399 to \
  2.8263, 0.454458 front fs empty border lc rgb '#98a1' lw 0.200001
set object 131 polygon from \
  2.79116, 0.461878 to \
  2.85247, 0.461878 to \
  2.85247, 0.199899 to \
  2.79116, 0.199899 to \
  2.79116, 0.461878 front fs empty border lc rgb '#98a1' lw 0.200001
set object 132 polygon from \
  2.7559, 0.469438 to \
  2.82265, 0.469438 to \
  2.82265, 0.205932 to \
  2.7559, 0.205932 to \
  2.7559, 0.469438 front fs empty border lc rgb '#98a1' lw 0.200001
set object 133 polygon from \
  2.72052, 0.477138 to \
  2.79275, 0.477138 to \
  2.79275, 0.212088 to \
  2.72052, 0.212088 to \
  2.72052, 0.477138 front fs empty border lc rgb '#98a1' lw 0.200001
set object 134 polygon from \
  2.68503, 0.484978 to \
  2.76277, 0.484978 to \
  2.76277, 0.218367 to \
  2.68503, 0.218367 to \
  2.68503, 0.484978 front fs empty border lc rgb '#98a1' lw 0.200001
set object 135 polygon from \
  2.64943, 0.492958 to \
  2.73272, 0.492958 to \
  2.73272, 0.224767 to \
  2.64943, 0.224767 to \
  2.64943, 0.492958 front fs empty border lc rgb '#98a1' lw 0.200001
set object 136 polygon from \
  2.61372, 0.501075 to \
  2.70259, 0.501075 to \
  2.70259, 0.231288 to \
  2.61372, 0.231288 to \
  2.61372, 0.501075 front fs empty border lc rgb '#98a1' lw 0.200001
set object 137 polygon from \
  2.57792, 0.509331 to \
  2.67239, 0.509331 to \
  2.67239, 0.237928 to \
  2.57792, 0.237928 to \
  2.57792, 0.509331 front fs empty border lc rgb '#98a1' lw 0.200001
set object 138 polygon from \
  2.54201, 0.517724 to \
  2.64214, 0.517724 to \
  2.64214, 0.244686 to \
  2.54201, 0.244686 to \
  2.54201, 0.517724 front fs empty border lc rgb '#98a1' lw 0.200001
set object 139 polygon from \
  2.50602, 0.526253 to \
  2.61182, 0.526253 to \
  2.61182, 0.251563 to \
  2.50602, 0.251563 to \
  2.50602, 0.526253 front fs empty border lc rgb '#98a1' lw 0.200001
set object 140 polygon from \
  2.46993, 0.534918 to \
  2.58145, 0.534918 to \
  2.58145, 0.258555 to \
  2.46993, 0.258555 to \
  2.46993, 0.534918 front fs empty border lc rgb '#98a1' lw 0.200001
set object 141 polygon from \
  2.43376, 0.543718 to \
  2.55104, 0.543718 to \
  2.55104, 0.265664 to \
  2.43376, 0.265664 to \
  2.43376, 0.543718 front fs empty border lc rgb '#98a1' lw 0.200001
set object 142 polygon from \
  2.39751, 0.552653 to \
  2.52058, 0.552653 to \
  2.52058, 0.272886 to \
  2.39751, 0.272886 to \
  2.39751, 0.552653 front fs empty border lc rgb '#98a1' lw 0.200001
set object 143 polygon from \
  2.36118, 0.561722 to \
  2.49009, 0.561722 to \
  2.49009, 0.280222 to \
  2.36118, 0.280222 to \
  2.36118, 0.561722 front fs empty border lc rgb '#98a1' lw 0.200001
set object 144 polygon from \
  2.32478, 0.570924 to \
  2.45956, 0.570924 to \
  2.45956, 0.287671 to \
  2.32478, 0.287671 to \
  2.32478, 0.570924 front fs empty border lc rgb '#98a1' lw 0.200001
set object 145 polygon from \
  2.28832, 0.580258 to \
  2.42901, 0.580258 to \
  2.42901, 0.295231 to \
  2.28832, 0.295231 to \
  2.28832, 0.580258 front fs empty border lc rgb '#98a1' lw 0.200001
set object 146 polygon from \
  2.25179, 0.589723 to \
  2.39843, 0.589723 to \
  2.39843, 0.302901 to \
  2.25179, 0.302901 to \
  2.25179, 0.589723 front fs empty border lc rgb '#98a1' lw 0.200001
set object 147 polygon from \
  2.21519, 0.59932 to \
  2.36784, 0.59932 to \
  2.36784, 0.31068 to \
  2.21519, 0.31068 to \
  2.21519, 0.59932 front fs empty border lc rgb '#98a1' lw 0.200001
set object 148 polygon from \
  2.17855, 0.609047 to \
  2.33723, 0.609047 to \
  2.33723, 0.318567 to \
  2.17855, 0.318567 to \
  2.17855, 0.609047 front fs empty border lc rgb '#98a1' lw 0.200001
set object 149 polygon from \
  2.14185, 0.618903 to \
  2.30661, 0.618903 to \
  2.30661, 0.326561 to \
  2.14185, 0.326561 to \
  2.14185, 0.618903 front fs empty border lc rgb '#98a1' lw 0.200001
set object 150 polygon from \
  2.1051, 0.628888 to \
  2.276, 0.628888 to \
  2.276, 0.33466 to \
  2.1051, 0.33466 to \
  2.1051, 0.628888 front fs empty border lc rgb '#98a1' lw 0.200001
set object 151 polygon from \
  2.06831, 0.639 to \
  2.24538, 0.639 to \
  2.24538, 0.342864 to \
  2.06831, 0.342864 to \
  2.06831, 0.639 front fs empty border lc rgb '#98a1' lw 0.200001
set object 152 polygon from \
  2.03148, 0.64924 to \
  2.21477, 0.64924 to \
  2.21477, 0.351171 to \
  2.03148, 0.351171 to \
  2.03148, 0.64924 front fs empty border lc rgb '#98a1' lw 0.200001
set object 153 polygon from \
  2, 0.659605 to \
  2.18417, 0.659605 to \
  2.18417, 0.359581 to \
  2, 0.359581 to \
  2, 0.659605 front fs empty border lc rgb '#98a1' lw 0.200001
set object 154 polygon from \
  2, 0.670092 to \
  2.15359, 0.670092 to \
  2.15359, 0.368091 to \
  2, 0.368091 to \
  2, 0.670092 front fs empty border lc rgb '#98a1' lw 0.200001
set object 155 polygon from \
  2, 0.680673 to \
  2.12302, 0.680673 to \
  2.12302, 0.376701 to \
  2, 0.376701 to \
  2, 0.680673 front fs empty border lc rgb '#98a1' lw 0.200001
set object 156 polygon from \
  2, 0.691347 to \
  2.09248, 0.691347 to \
  2.09248, 0.385411 to \
  2, 0.385411 to \
  2, 0.691347 front fs empty border lc rgb '#98a1' lw 0.200001
set object 157 polygon from \
  2, 0.702113 to \
  2.06197, 0.702113 to \
  2.06197, 0.394221 to \
  2, 0.394221 to \
  2, 0.702113 front fs empty border lc rgb '#98a1' lw 0.200001
set object 158 polygon from \
  2, 0.712969 to \
  2.03148, 0.712969 to \
  2.03148, 0.40313 to \
  2, 0.40313 to \
  2, 0.712969 front fs empty border lc rgb '#98a1' lw 0.200001
set object 159 polygon from \
  2, 0.723916 to \
  2.00101, 0.723916 to \
  2.00101, 0.412139 to \
  2, 0.412139 to \
  2, 0.723916 front fs empty border lc rgb '#98a1' lw 0.200001
set object 160 polygon from \
  1.96199, 0.734998 to \
  2.00002, 0.734998 to \
  2.00002, 0.359534 to \
  1.96199, 0.359534 to \
  1.96199, 0.734998 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 161 polygon from \
  1.92388, 0.746158 to \
  1.97039, 0.746158 to \
  1.97039, 0.368196 to \
  1.92388, 0.368196 to \
  1.92388, 0.746158 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 162 polygon from \
  1.88577, 0.757441 to \
  1.9408, 0.757441 to \
  1.9408, 0.376957 to \
  1.88577, 0.376957 to \
  1.88577, 0.757441 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 163 polygon from \
  1.84766, 0.768846 to \
  1.91126, 0.768846 to \
  1.91126, 0.385815 to \
  1.84766, 0.385815 to \
  1.84766, 0.768846 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 164 polygon from \
  1.80955, 0.780373 to \
  1.88178, 0.780373 to \
  1.88178, 0.394769 to \
  1.80955, 0.394769 to \
  1.80955, 0.780373 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 165 polygon from \
  1.77145, 0.792021 to \
  1.85235, 0.792021 to \
  1.85235, 0.403817 to \
  1.77145, 0.403817 to \
  1.77145, 0.792021 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 166 polygon from \
  1.73337, 0.803788 to \
  1.82299, 0.803788 to \
  1.82299, 0.412958 to \
  1.73337, 0.412958 to \
  1.73337, 0.803788 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 167 polygon from \
  1.69529, 0.815673 to \
  1.79369, 0.815673 to \
  1.79369, 0.42219 to \
  1.69529, 0.42219 to \
  1.69529, 0.815673 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 168 polygon from \
  1.65724, 0.827676 to \
  1.76447, 0.827676 to \
  1.76447, 0.431512 to \
  1.65724, 0.431512 to \
  1.65724, 0.827676 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 169 polygon from \
  1.61922, 0.839796 to \
  1.73532, 0.839796 to \
  1.73532, 0.440923 to \
  1.61922, 0.440923 to \
  1.61922, 0.839796 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 170 polygon from \
  1.58121, 0.852031 to \
  1.70625, 0.852031 to \
  1.70625, 0.45042 to \
  1.58121, 0.45042 to \
  1.58121, 0.852031 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 171 polygon from \
  1.54324, 0.864381 to \
  1.67727, 0.864381 to \
  1.67727, 0.460002 to \
  1.54324, 0.460002 to \
  1.54324, 0.864381 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 172 polygon from \
  1.5053, 0.876845 to \
  1.64839, 0.876845 to \
  1.64839, 0.469669 to \
  1.5053, 0.469669 to \
  1.5053, 0.876845 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 173 polygon from \
  1.4674, 0.889421 to \
  1.6196, 0.889421 to \
  1.6196, 0.479417 to \
  1.4674, 0.479417 to \
  1.4674, 0.889421 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 174 polygon from \
  1.42954, 0.902108 to \
  1.5909, 0.902108 to \
  1.5909, 0.489246 to \
  1.42954, 0.489246 to \
  1.42954, 0.902108 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 175 polygon from \
  1.39173, 0.914906 to \
  1.56232, 0.914906 to \
  1.56232, 0.499154 to \
  1.39173, 0.499154 to \
  1.39173, 0.914906 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 176 polygon from \
  1.35396, 0.927814 to \
  1.53384, 0.927814 to \
  1.53384, 0.50914 to \
  1.35396, 0.50914 to \
  1.35396, 0.927814 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 177 polygon from \
  1.31624, 0.94083 to \
  1.50548, 0.94083 to \
  1.50548, 0.519202 to \
  1.31624, 0.519202 to \
  1.31624, 0.94083 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 178 polygon from \
  1.27857, 0.953953 to \
  1.47724, 0.953953 to \
  1.47724, 0.529338 to \
  1.27857, 0.529338 to \
  1.27857, 0.953953 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 179 polygon from \
  1.24097, 0.967183 to \
  1.44912, 0.967183 to \
  1.44912, 0.539546 to \
  1.24097, 0.539546 to \
  1.24097, 0.967183 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 180 polygon from \
  1.20342, 0.980518 to \
  1.42113, 0.980518 to \
  1.42113, 0.549826 to \
  1.20342, 0.549826 to \
  1.20342, 0.980518 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 181 polygon from \
  1.16594, 0.993958 to \
  1.39327, 0.993958 to \
  1.39327, 0.560175 to \
  1.16594, 0.560175 to \
  1.16594, 0.993958 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 182 polygon from \
  1.12852, 1.0075 to \
  1.36555, 1.0075 to \
  1.36555, 0.570593 to \
  1.12852, 0.570593 to \
  1.12852, 1.0075 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 183 polygon from \
  1.09118, 1.02115 to \
  1.33797, 1.02115 to \
  1.33797, 0.581076 to \
  1.09118, 0.581076 to \
  1.09118, 1.02115 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 184 polygon from \
  1.0539, 1.03489 to \
  1.31054, 1.03489 to \
  1.31054, 0.591624 to \
  1.0539, 0.591624 to \
  1.0539, 1.03489 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 185 polygon from \
  1.01671, 1.04874 to \
  1.28325, 1.04874 to \
  1.28325, 0.602234 to \
  1.01671, 0.602234 to \
  1.01671, 1.04874 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 186 polygon from \
  1, 1.06268 to \
  1.25613, 1.06268 to \
  1.25613, 0.612906 to \
  1, 0.612906 to \
  1, 1.06268 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 187 polygon from \
  1, 1.07671 to \
  1.22916, 1.07671 to \
  1.22916, 0.623638 to \
  1, 0.623638 to \
  1, 1.07671 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 188 polygon from \
  1, 1.0908 to \
  1.20235, 1.0908 to \
  1.20235, 0.634427 to \
  1, 0.634427 to \
  1, 1.0908 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 189 polygon from \
  1, 1.10496 to \
  1.17571, 1.10496 to \
  1.17571, 0.645275 to \
  1, 0.645275 to \
  1, 1.10496 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 190 polygon from \
  1, 1.11918 to \
  1.14923, 1.11918 to \
  1.14923, 0.65618 to \
  1, 0.65618 to \
  1, 1.11918 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 191 polygon from \
  1, 1.13346 to \
  1.12292, 1.13346 to \
  1.12292, 0.667142 to \
  1, 0.667142 to \
  1, 1.13346 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 192 polygon from \
  1, 1.14781 to \
  1.09677, 1.14781 to \
  1.09677, 0.678159 to \
  1, 0.678159 to \
  1, 1.14781 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 193 polygon from \
  1, 1.16221 to \
  1.07079, 1.16221 to \
  1.07079, 0.689233 to \
  1, 0.689233 to \
  1, 1.16221 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 194 polygon from \
  1, 1.17668 to \
  1.04498, 1.17668 to \
  1.04498, 0.700361 to \
  1, 0.700361 to \
  1, 1.17668 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 195 polygon from \
  1, 1.1912 to \
  1.01935, 1.1912 to \
  1.01935, 0.711543 to \
  1, 0.711543 to \
  1, 1.1912 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 196 polygon from \
  0.962199, 1.20581 to \
  1.00007, 1.20581 to \
  1.00007, 0.612871 to \
  0.962199, 0.612871 to \
  0.962199, 1.20581 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 197 polygon from \
  0.924444, 1.22048 to \
  0.975151, 1.22048 to \
  0.975151, 0.623812 to \
  0.924444, 0.623812 to \
  0.924444, 1.22048 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 198 polygon from \
  0.8868, 1.23524 to \
  0.950419, 1.23524 to \
  0.950419, 0.634804 to \
  0.8868, 0.634804 to \
  0.8868, 1.23524 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 199 polygon from \
  0.849269, 1.25009 to \
  0.925875, 1.25009 to \
  0.925875, 0.645845 to \
  0.849269, 0.645845 to \
  0.849269, 1.25009 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 200 polygon from \
  0.811854, 1.26502 to \
  0.901524, 1.26502 to \
  0.901524, 0.656933 to \
  0.811854, 0.656933 to \
  0.811854, 1.26502 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 201 polygon from \
  0.774558, 1.28005 to \
  0.877371, 1.28005 to \
  0.877371, 0.668065 to \
  0.774558, 0.668065 to \
  0.774558, 1.28005 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 202 polygon from \
  0.737383, 1.29516 to \
  0.853419, 1.29516 to \
  0.853419, 0.679241 to \
  0.737383, 0.679241 to \
  0.737383, 1.29516 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 203 polygon from \
  0.700331, 1.31035 to \
  0.829672, 1.31035 to \
  0.829672, 0.690459 to \
  0.700331, 0.690459 to \
  0.700331, 1.31035 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 204 polygon from \
  0.663404, 1.32563 to \
  0.806135, 1.32563 to \
  0.806135, 0.701716 to \
  0.663404, 0.701716 to \
  0.663404, 1.32563 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 205 polygon from \
  0.626606, 1.34099 to \
  0.782811, 1.34099 to \
  0.782811, 0.71301 to \
  0.626606, 0.71301 to \
  0.626606, 1.34099 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 206 polygon from \
  0.589938, 1.35643 to \
  0.759705, 1.35643 to \
  0.759705, 0.72434 to \
  0.589938, 0.72434 to \
  0.589938, 1.35643 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 207 polygon from \
  0.553402, 1.37195 to \
  0.73682, 1.37195 to \
  0.73682, 0.735704 to \
  0.553402, 0.735704 to \
  0.553402, 1.37195 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 208 polygon from \
  0.517001, 1.38755 to \
  0.714161, 1.38755 to \
  0.714161, 0.747099 to \
  0.517001, 0.747099 to \
  0.517001, 1.38755 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 209 polygon from \
  0.480736, 1.40322 to \
  0.691731, 1.40322 to \
  0.691731, 0.758524 to \
  0.480736, 0.758524 to \
  0.480736, 1.40322 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 210 polygon from \
  0.44461, 1.41898 to \
  0.669534, 1.41898 to \
  0.669534, 0.769977 to \
  0.44461, 0.769977 to \
  0.44461, 1.41898 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 211 polygon from \
  0.408625, 1.43481 to \
  0.647575, 1.43481 to \
  0.647575, 0.781457 to \
  0.408625, 0.781457 to \
  0.408625, 1.43481 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 212 polygon from \
  0.372783, 1.45071 to \
  0.625856, 1.45071 to \
  0.625856, 0.79296 to \
  0.372783, 0.79296 to \
  0.372783, 1.45071 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 213 polygon from \
  0.337086, 1.46669 to \
  0.604383, 1.46669 to \
  0.604383, 0.804485 to \
  0.337086, 0.804485 to \
  0.337086, 1.46669 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 214 polygon from \
  0.301535, 1.48273 to \
  0.583158, 1.48273 to \
  0.583158, 0.816031 to \
  0.301535, 0.816031 to \
  0.301535, 1.48273 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 215 polygon from \
  0.266133, 1.49885 to \
  0.562185, 1.49885 to \
  0.562185, 0.827594 to \
  0.266133, 0.827594 to \
  0.266133, 1.49885 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 216 polygon from \
  0.230881, 1.51504 to \
  0.541469, 1.51504 to \
  0.541469, 0.839174 to \
  0.230881, 0.839174 to \
  0.230881, 1.51504 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 217 polygon from \
  0.19578, 1.5313 to \
  0.521012, 1.5313 to \
  0.521012, 0.850768 to \
  0.19578, 0.850768 to \
  0.19578, 1.5313 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 218 polygon from \
  0.160834, 1.54763 to \
  0.500819, 1.54763 to \
  0.500819, 0.862375 to \
  0.160834, 0.862375 to \
  0.160834, 1.54763 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 219 polygon from \
  0.126043, 1.56402 to \
  0.480894, 1.56402 to \
  0.480894, 0.873991 to \
  0.126043, 0.873991 to \
  0.126043, 1.56402 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 220 polygon from \
  0.0914086, 1.58048 to \
  0.461238, 1.58048 to \
  0.461238, 0.885617 to \
  0.0914086, 0.885617 to \
  0.0914086, 1.58048 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 221 polygon from \
  0.0569331, 1.597 to \
  0.441858, 1.597 to \
  0.441858, 0.897248 to \
  0.0569331, 0.897248 to \
  0.0569331, 1.597 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 222 polygon from \
  0.0226176, 1.61359 to \
  0.422755, 1.61359 to \
  0.422755, 0.908884 to \
  0.0226176, 0.908884 to \
  0.0226176, 1.61359 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 223 polygon from \
  0, 1.63024 to \
  0.403934, 1.63024 to \
  0.403934, 0.920522 to \
  0, 0.920522 to \
  0, 1.63024 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 224 polygon from \
  0, 1.64694 to \
  0.385398, 1.64694 to \
  0.385398, 0.932161 to \
  0, 0.932161 to \
  0, 1.64694 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 225 polygon from \
  0, 1.66367 to \
  0.367149, 1.66367 to \
  0.367149, 0.943798 to \
  0, 0.943798 to \
  0, 1.66367 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 226 polygon from \
  0, 1.68043 to \
  0.349188, 1.68043 to \
  0.349188, 0.955433 to \
  0, 0.955433 to \
  0, 1.68043 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 227 polygon from \
  0, 1.69722 to \
  0.331517, 1.69722 to \
  0.331517, 0.967065 to \
  0, 0.967065 to \
  0, 1.69722 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 228 polygon from \
  0, 1.71405 to \
  0.314134, 1.71405 to \
  0.314134, 0.978693 to \
  0, 0.978693 to \
  0, 1.71405 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 229 polygon from \
  0, 1.7309 to \
  0.297042, 1.7309 to \
  0.297042, 0.990316 to \
  0, 0.990316 to \
  0, 1.7309 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 230 polygon from \
  0, 1.74777 to \
  0.28024, 1.74777 to \
  0.28024, 1.00194 to \
  0, 1.00194 to \
  0, 1.74777 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 231 polygon from \
  0, 1.76468 to \
  0.26373, 1.76468 to \
  0.26373, 1.01355 to \
  0, 1.01355 to \
  0, 1.76468 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 232 polygon from \
  0, 1.7816 to \
  0.247511, 1.7816 to \
  0.247511, 1.02515 to \
  0, 1.02515 to \
  0, 1.7816 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 233 polygon from \
  0, 1.79856 to \
  0.231585, 1.79856 to \
  0.231585, 1.03674 to \
  0, 1.03674 to \
  0, 1.79856 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 234 polygon from \
  0, 1.81553 to \
  0.215951, 1.81553 to \
  0.215951, 1.04832 to \
  0, 1.04832 to \
  0, 1.81553 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 235 polygon from \
  0, 1.83253 to \
  0.200611, 1.83253 to \
  0.200611, 1.05989 to \
  0, 1.05989 to \
  0, 1.83253 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 236 polygon from \
  0, 1.84955 to \
  0.185565, 1.84955 to \
  0.185565, 1.07145 to \
  0, 1.07145 to \
  0, 1.84955 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 237 polygon from \
  0, 1.86658 to \
  0.170813, 1.86658 to \
  0.170813, 1.083 to \
  0, 1.083 to \
  0, 1.86658 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 238 polygon from \
  0, 1.88364 to \
  0.156356, 1.88364 to \
  0.156356, 1.09453 to \
  0, 1.09453 to \
  0, 1.88364 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 239 polygon from \
  0, 1.90072 to \
  0.142194, 1.90072 to \
  0.142194, 1.10605 to \
  0, 1.10605 to \
  0, 1.90072 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 240 polygon from \
  0, 1.91781 to \
  0.128328, 1.91781 to \
  0.128328, 1.11755 to \
  0, 1.11755 to \
  0, 1.91781 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 241 polygon from \
  0, 1.93492 to \
  0.114758, 1.93492 to \
  0.114758, 1.12904 to \
  0, 1.12904 to \
  0, 1.93492 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 242 polygon from \
  0, 1.95204 to \
  0.101485, 1.95204 to \
  0.101485, 1.14051 to \
  0, 1.14051 to \
  0, 1.95204 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 243 polygon from \
  0, 1.96918 to \
  0.0885079, 1.96918 to \
  0.0885079, 1.15196 to \
  0, 1.15196 to \
  0, 1.96918 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 244 polygon from \
  0, 1.98633 to \
  0.075829, 1.98633 to \
  0.075829, 1.16338 to \
  0, 1.16338 to \
  0, 1.98633 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 245 polygon from \
  0, 2.00349 to \
  0.063448, 2.00349 to \
  0.063448, 1.17479 to \
  0, 1.17479 to \
  0, 2.00349 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 246 polygon from \
  0, 2.02067 to \
  0.051365, 2.02067 to \
  0.051365, 1.18618 to \
  0, 1.18618 to \
  0, 2.02067 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 247 polygon from \
  0, 2.03785 to \
  0.0395807, 2.03785 to \
  0.0395807, 1.19754 to \
  0, 1.19754 to \
  0, 2.03785 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 248 polygon from \
  0, 2.05505 to \
  0.0280952, 2.05505 to \
  0.0280952, 1.20888 to \
  0, 1.20888 to \
  0, 2.05505 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 249 polygon from \
  0, 2.07225 to \
  0.0169089, 2.07225 to \
  0.0169089, 1.2202 to \
  0, 1.2202 to \
  0, 2.07225 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 250 polygon from \
  0, 2.08947 to \
  0.0060221, 2.08947 to \
  0.0060221, 1.23148 to \
  0, 1.23148 to \
  0, 2.08947 front fs empty border lc rgb '#bdcd00' lw 0.200001
set object 251 polygon from \
  -0.0353602, 2.10695 to \
  0.00013151, 2.10695 to \
  0.00013151, 0.920495 to \
  -0.0353602, 0.920495 to \
  -0.0353602, 2.10695 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 252 polygon from \
  -0.0705863, 2.12447 to \
  -0.00827367, 2.12447 to \
  -0.00827367, 0.931386 to \
  -0.0705863, 0.931386 to \
  -0.0705863, 2.12447 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 253 polygon from \
  -0.105643, 2.14206 to \
  -0.0163079, 2.14206 to \
  -0.0163079, 0.942223 to \
  -0.105643, 0.942223 to \
  -0.105643, 2.14206 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 254 polygon from \
  -0.140533, 2.1597 to \
  -0.0239687, 2.1597 to \
  -0.0239687, 0.953005 to \
  -0.140533, 0.953005 to \
  -0.140533, 2.1597 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 255 polygon from \
  -0.175257, 2.17739 to \
  -0.0312532, 2.17739 to \
  -0.0312532, 0.963728 to \
  -0.175257, 0.963728 to \
  -0.175257, 2.17739 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 256 polygon from \
  -0.209816, 2.19514 to \
  -0.0381589, 2.19514 to \
  -0.0381589, 0.974389 to \
  -0.209816, 0.974389 to \
  -0.209816, 2.19514 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 257 polygon from \
  -0.244213, 2.21295 to \
  -0.044683, 2.21295 to \
  -0.044683, 0.984986 to \
  -0.244213, 0.984986 to \
  -0.244213, 2.21295 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 258 polygon from \
  -0.27845, 2.23081 to \
  -0.0508231, 2.23081 to \
  -0.0508231, 0.995516 to \
  -0.27845, 0.995516 to \
  -0.27845, 2.23081 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 259 polygon from \
  -0.312527, 2.24871 to \
  -0.0565764, 2.24871 to \
  -0.0565764, 1.00598 to \
  -0.312527, 1.00598 to \
  -0.312527, 2.24871 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 260 polygon from \
  -0.346448, 2.26667 to \
  -0.0619405, 2.26667 to \
  -0.0619405, 1.01637 to \
  -0.346448, 1.01637 to \
  -0.346448, 2.26667 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 261 polygon from \
  -0.380214, 2.28468 to \
  -0.0669127, 2.28468 to \
  -0.0669127, 1.02668 to \
  -0.380214, 1.02668 to \
  -0.380214, 2.28468 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 262 polygon from \
  -0.413826, 2.30274 to \
  -0.0714905, 2.30274 to \
  -0.0714905, 1.03692 to \
  -0.413826, 1.03692 to \
  -0.413826, 2.30274 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 263 polygon from \
  -0.447288, 2.32085 to \
  -0.0756713, 2.32085 to \
  -0.0756713, 1.04707 to \
  -0.447288, 1.04707 to \
  -0.447288, 2.32085 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 264 polygon from \
  -0.480602, 2.339 to \
  -0.0794527, 2.339 to \
  -0.0794527, 1.05714 to \
  -0.480602, 1.05714 to \
  -0.480602, 2.339 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 265 polygon from \
  -0.513769, 2.3572 to \
  -0.082832, 2.3572 to \
  -0.082832, 1.06712 to \
  -0.513769, 1.06712 to \
  -0.513769, 2.3572 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 266 polygon from \
  -0.546793, 2.37544 to \
  -0.0858068, 2.37544 to \
  -0.0858068, 1.07702 to \
  -0.546793, 1.07702 to \
  -0.546793, 2.37544 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 267 polygon from \
  -0.579675, 2.39373 to \
  -0.0883746, 2.39373 to \
  -0.0883746, 1.08682 to \
  -0.579675, 1.08682 to \
  -0.579675, 2.39373 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 268 polygon from \
  -0.612418, 2.41207 to \
  -0.0905329, 2.41207 to \
  -0.0905329, 1.09653 to \
  -0.612418, 1.09653 to \
  -0.612418, 2.41207 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 269 polygon from \
  -0.645025, 2.43044 to \
  -0.0922792, 2.43044 to \
  -0.0922792, 1.10614 to \
  -0.645025, 1.10614 to \
  -0.645025, 2.43044 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 270 polygon from \
  -0.677498, 2.44887 to \
  -0.093611, 2.44887 to \
  -0.093611, 1.11566 to \
  -0.677498, 1.11566 to \
  -0.677498, 2.44887 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 271 polygon from \
  -0.70984, 2.46733 to \
  -0.0945259, 2.46733 to \
  -0.0945259, 1.12506 to \
  -0.70984, 1.12506 to \
  -0.70984, 2.46733 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 272 polygon from \
  -0.742054, 2.48583 to \
  -0.0950213, 2.48583 to \
  -0.0950213, 1.13437 to \
  -0.742054, 1.13437 to \
  -0.742054, 2.48583 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 273 polygon from \
  -0.774143, 2.50438 to \
  -0.0950948, 2.50438 to \
  -0.0950948, 1.14356 to \
  -0.774143, 1.14356 to \
  -0.774143, 2.50438 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 274 polygon from \
  -0.806109, 2.52296 to \
  -0.094744, 2.52296 to \
  -0.094744, 1.15265 to \
  -0.806109, 1.15265 to \
  -0.806109, 2.52296 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 275 polygon from \
  -0.837956, 2.54159 to \
  -0.0939663, 2.54159 to \
  -0.0939663, 1.16162 to \
  -0.837956, 1.16162 to \
  -0.837956, 2.54159 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 276 polygon from \
  -0.869687, 2.56025 to \
  -0.0927594, 2.56025 to \
  -0.0927594, 1.17048 to \
  -0.869687, 1.17048 to \
  -0.869687, 2.56025 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 277 polygon from \
  -0.901305, 2.57896 to \
  -0.0911207, 2.57896 to \
  -0.0911207, 1.17921 to \
  -0.901305, 1.17921 to \
  -0.901305, 2.57896 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 278 polygon from \
  -0.932813, 2.5977 to \
  -0.0890479, 2.5977 to \
  -0.0890479, 1.18783 to \
  -0.932813, 1.18783 to \
  -0.932813, 2.5977 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 279 polygon from \
  -0.964214, 2.61648 to \
  -0.0865384, 2.61648 to \
  -0.0865384, 1.19632 to \
  -0.964214, 1.19632 to \
  -0.964214, 2.61648 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 280 polygon from \
  -0.995512, 2.6353 to \
  -0.0835898, 2.6353 to \
  -0.0835898, 1.20468 to \
  -0.995512, 1.20468 to \
  -0.995512, 2.6353 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 281 polygon from \
  -1.02671, 2.65416 to \
  -0.0801996, 2.65416 to \
  -0.0801996, 1.21291 to \
  -1.02671, 1.21291 to \
  -1.02671, 2.65416 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 282 polygon from \
  -1.05781, 2.67305 to \
  -0.0763654, 2.67305 to \
  -0.0763654, 1.22101 to \
  -1.05781, 1.22101 to \
  -1.05781, 2.67305 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 283 polygon from \
  -1.08882, 2.69199 to \
  -0.0720846, 2.69199 to \
  -0.0720846, 1.22898 to \
  -1.08882, 1.22898 to \
  -1.08882, 2.69199 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 284 polygon from \
  -1.11974, 2.71096 to \
  -0.0673549, 2.71096 to \
  -0.0673549, 1.23681 to \
  -1.11974, 1.23681 to \
  -1.11974, 2.71096 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 285 polygon from \
  -1.15057, 2.72996 to \
  -0.0621737, 2.72996 to \
  -0.0621737, 1.24449 to \
  -1.15057, 1.24449 to \
  -1.15057, 2.72996 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 286 polygon from \
  -1.18133, 2.74901 to \
  -0.0565384, 2.74901 to \
  -0.0565384, 1.25204 to \
  -1.18133, 1.25204 to \
  -1.18133, 2.74901 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 287 polygon from \
  -1.21201, 2.76809 to \
  -0.0504467, 2.76809 to \
  -0.0504467, 1.25943 to \
  -1.21201, 1.25943 to \
  -1.21201, 2.76809 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 288 polygon from \
  -1.24261, 2.7872 to \
  -0.043896, 2.7872 to \
  -0.043896, 1.26668 to \
  -1.24261, 1.26668 to \
  -1.24261, 2.7872 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 289 polygon from \
  -1.27314, 2.80636 to \
  -0.0368838, 2.80636 to \
  -0.0368838, 1.27378 to \
  -1.27314, 1.27378 to \
  -1.27314, 2.80636 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 290 polygon from \
  -1.30361, 2.82555 to \
  -0.0294075, 2.82555 to \
  -0.0294075, 1.28072 to \
  -1.30361, 1.28072 to \
  -1.30361, 2.82555 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 291 polygon from \
  -1.33402, 2.84478 to \
  -0.0214645, 2.84478 to \
  -0.0214645, 1.28751 to \
  -1.33402, 1.28751 to \
  -1.33402, 2.84478 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 292 polygon from \
  -1.36437, 2.86404 to \
  -0.0130524, 2.86404 to \
  -0.0130524, 1.29413 to \
  -1.36437, 1.29413 to \
  -1.36437, 2.86404 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 293 polygon from \
  -1.39467, 2.88335 to \
  -0.00416855, 2.88335 to \
  -0.00416855, 1.30059 to \
  -1.39467, 1.30059 to \
  -1.39467, 2.88335 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 294 polygon from \
  -1.42492, 2.90269 to \
  0.0051897, 2.90269 to \
  0.0051897, 1.30689 to \
  -1.42492, 1.30689 to \
  -1.42492, 2.90269 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 295 polygon from \
  -1.45513, 2.92206 to \
  0.015025, 2.92206 to \
  0.015025, 1.31302 to \
  -1.45513, 1.31302 to \
  -1.45513, 2.92206 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 296 polygon from \
  -1.4853, 2.94148 to \
  0.0253398, 2.94148 to \
  0.0253398, 1.31898 to \
  -1.4853, 1.31898 to \
  -1.4853, 2.94148 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 297 polygon from \
  -1.51544, 2.96093 to \
  0.036137, 2.96093 to \
  0.036137, 1.32477 to \
  -1.51544, 1.32477 to \
  -1.51544, 2.96093 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 298 polygon from \
  -1.54554, 2.98043 to \
  0.047419, 2.98043 to \
  0.047419, 1.33038 to \
  -1.54554, 1.33038 to \
  -1.54554, 2.98043 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 299 polygon from \
  -1.57563, 2.99996 to \
  0.0591887, 2.99996 to \
  0.0591887, 1.33581 to \
  -1.57563, 1.33581 to \
  -1.57563, 2.99996 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 300 polygon from \
  -1.60569, 3.01953 to \
  0.0714488, 3.01953 to \
  0.0714488, 1.34106 to \
  -1.60569, 1.34106 to \
  -1.60569, 3.01953 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 301 polygon from \
  -1.63574, 3.03914 to \
  0.084202, 3.03914 to \
  0.084202, 1.34613 to \
  -1.63574, 1.34613 to \
  -1.63574, 3.03914 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 302 polygon from \
  -1.66578, 3.0588 to \
  0.097451, 3.0588 to \
  0.097451, 1.35101 to \
  -1.66578, 1.35101 to \
  -1.66578, 3.0588 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 303 polygon from \
  -1.69581, 3.07849 to \
  0.111199, 3.07849 to \
  0.111199, 1.35569 to \
  -1.69581, 1.35569 to \
  -1.69581, 3.07849 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 304 polygon from \
  -1.72585, 3.09823 to \
  0.125448, 3.09823 to \
  0.125448, 1.36019 to \
  -1.72585, 1.36019 to \
  -1.72585, 3.09823 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 305 polygon from \
  -1.75589, 3.11801 to \
  0.140202, 3.11801 to \
  0.140202, 1.36449 to \
  -1.75589, 1.36449 to \
  -1.75589, 3.11801 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 306 polygon from \
  -1.78594, 3.13783 to \
  0.155463, 3.13783 to \
  0.155463, 1.3686 to \
  -1.78594, 1.3686 to \
  -1.78594, 3.13783 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 307 polygon from \
  -1.81602, 3.15769 to \
  0.171234, 3.15769 to \
  0.171234, 1.3725 to \
  -1.81602, 1.3725 to \
  -1.81602, 3.15769 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 308 polygon from \
  -1.84611, 3.1776 to \
  0.187518, 3.1776 to \
  0.187518, 1.3762 to \
  -1.84611, 1.3762 to \
  -1.84611, 3.1776 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 309 polygon from \
  -1.87623, 3.19756 to \
  0.204318, 3.19756 to \
  0.204318, 1.37969 to \
  -1.87623, 1.37969 to \
  -1.87623, 3.19756 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 310 polygon from \
  -1.90639, 3.21756 to \
  0.221637, 3.21756 to \
  0.221637, 1.38297 to \
  -1.90639, 1.38297 to \
  -1.90639, 3.21756 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 311 polygon from \
  -1.93659, 3.23761 to \
  0.239479, 3.23761 to \
  0.239479, 1.38604 to \
  -1.93659, 1.38604 to \
  -1.93659, 3.23761 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 312 polygon from \
  -1.96683, 3.25771 to \
  0.257845, 3.25771 to \
  0.257845, 1.3889 to \
  -1.96683, 1.3889 to \
  -1.96683, 3.25771 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 313 polygon from \
  -1.99712, 3.27786 to \
  0.27674, 3.27786 to \
  0.27674, 1.39154 to \
  -1.99712, 1.39154 to \
  -1.99712, 3.27786 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 314 polygon from \
  -2.02748, 3.29806 to \
  0.296167, 3.29806 to \
  0.296167, 1.39396 to \
  -2.02748, 1.39396 to \
  -2.02748, 3.29806 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 315 polygon from \
  -2.0579, 3.31831 to \
  0.316128, 3.31831 to \
  0.316128, 1.39615 to \
  -2.0579, 1.39615 to \
  -2.0579, 3.31831 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 316 polygon from \
  -2.08838, 3.33862 to \
  0.336628, 3.33862 to \
  0.336628, 1.39812 to \
  -2.08838, 1.39812 to \
  -2.08838, 3.33862 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 317 polygon from \
  -2.11895, 3.35897 to \
  0.357669, 3.35897 to \
  0.357669, 1.39986 to \
  -2.11895, 1.39986 to \
  -2.11895, 3.35897 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 318 polygon from \
  -2.1496, 3.37939 to \
  0.379254, 3.37939 to \
  0.379254, 1.40137 to \
  -2.1496, 1.40137 to \
  -2.1496, 3.37939 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 319 polygon from \
  -2.18033, 3.39986 to \
  0.401388, 3.39986 to \
  0.401388, 1.40264 to \
  -2.18033, 1.40264 to \
  -2.18033, 3.39986 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 320 polygon from \
  -2.21117, 3.42039 to \
  0.424073, 3.42039 to \
  0.424073, 1.40367 to \
  -2.21117, 1.40367 to \
  -2.21117, 3.42039 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 321 polygon from \
  -2.24211, 3.44097 to \
  0.447313, 3.44097 to \
  0.447313, 1.40447 to \
  -2.24211, 1.40447 to \
  -2.24211, 3.44097 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 322 polygon from \
  -2.27315, 3.46162 to \
  0.471111, 3.46162 to \
  0.471111, 1.40502 to \
  -2.27315, 1.40502 to \
  -2.27315, 3.46162 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 323 polygon from \
  -2.30432, 3.48233 to \
  0.495472, 3.48233 to \
  0.495472, 1.40533 to \
  -2.30432, 1.40533 to \
  -2.30432, 3.48233 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 324 polygon from \
  -2.33561, 3.50311 to \
  0.520399, 3.50311 to \
  0.520399, 1.40538 to \
  -2.33561, 1.40538 to \
  -2.33561, 3.50311 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 325 polygon from \
  -2.36703, 3.52395 to \
  0.545895, 3.52395 to \
  0.545895, 1.40519 to \
  -2.36703, 1.40519 to \
  -2.36703, 3.52395 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 326 polygon from \
  -2.39858, 3.54485 to \
  0.571964, 3.54485 to \
  0.571964, 1.40473 to \
  -2.39858, 1.40473 to \
  -2.39858, 3.54485 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 327 polygon from \
  -2.43029, 3.56583 to \
  0.598611, 3.56583 to \
  0.598611, 1.40402 to \
  -2.43029, 1.40402 to \
  -2.43029, 3.56583 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 328 polygon from \
  -2.46214, 3.58688 to \
  0.625839, 3.58688 to \
  0.625839, 1.40305 to \
  -2.46214, 1.40305 to \
  -2.46214, 3.58688 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 329 polygon from \
  -2.49416, 3.608 to \
  0.653651, 3.608 to \
  0.653651, 1.40182 to \
  -2.49416, 1.40182 to \
  -2.49416, 3.608 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 330 polygon from \
  -2.52634, 3.62919 to \
  0.682053, 3.62919 to \
  0.682053, 1.40031 to \
  -2.52634, 1.40031 to \
  -2.52634, 3.62919 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 331 polygon from \
  -2.5587, 3.65046 to \
  0.711047, 3.65046 to \
  0.711047, 1.39854 to \
  -2.5587, 1.39854 to \
  -2.5587, 3.65046 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 332 polygon from \
  -2.59124, 3.67181 to \
  0.740639, 3.67181 to \
  0.740639, 1.39649 to \
  -2.59124, 1.39649 to \
  -2.59124, 3.67181 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 333 polygon from \
  -2.62397, 3.69324 to \
  0.770833, 3.69324 to \
  0.770833, 1.39417 to \
  -2.62397, 1.39417 to \
  -2.62397, 3.69324 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 334 polygon from \
  -2.6569, 3.71476 to \
  0.801632, 3.71476 to \
  0.801632, 1.39157 to \
  -2.6569, 1.39157 to \
  -2.6569, 3.71476 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 335 polygon from \
  -2.69004, 3.73635 to \
  0.833041, 3.73635 to \
  0.833041, 1.38868 to \
  -2.69004, 1.38868 to \
  -2.69004, 3.73635 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 336 polygon from \
  -2.72339, 3.75804 to \
  0.865064, 3.75804 to \
  0.865064, 1.38551 to \
  -2.72339, 1.38551 to \
  -2.72339, 3.75804 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 337 polygon from \
  -2.75697, 3.77981 to \
  0.897707, 3.77981 to \
  0.897707, 1.38205 to \
  -2.75697, 1.38205 to \
  -2.75697, 3.77981 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 338 polygon from \
  -2.79077, 3.80167 to \
  0.930973, 3.80167 to \
  0.930973, 1.3783 to \
  -2.79077, 1.3783 to \
  -2.79077, 3.80167 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 339 polygon from \
  -2.82482, 3.82363 to \
  0.964868, 3.82363 to \
  0.964868, 1.37425 to \
  -2.82482, 1.37425 to \
  -2.82482, 3.82363 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 340 polygon from \
  -2.85911, 3.84569 to \
  0.999395, 3.84569 to \
  0.999395, 1.36991 to \
  -2.85911, 1.36991 to \
  -2.85911, 3.84569 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 341 polygon from \
  -2.89367, 3.86784 to \
  1, 3.86784 to \
  1, 1.36526 to \
  -2.89367, 1.36526 to \
  -2.89367, 3.86784 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 342 polygon from \
  -2.92849, 3.89009 to \
  1, 3.89009 to \
  1, 1.36033 to \
  -2.92849, 1.36033 to \
  -2.92849, 3.89009 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 343 polygon from \
  -2.96358, 3.91245 to \
  1, 3.91245 to \
  1, 1.35513 to \
  -2.96358, 1.35513 to \
  -2.96358, 3.91245 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 344 polygon from \
  -2.99894, 3.93491 to \
  1, 3.93491 to \
  1, 1.34964 to \
  -2.99894, 1.34964 to \
  -2.99894, 3.93491 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 345 polygon from \
  -3.03459, 3.95748 to \
  1, 3.95748 to \
  1, 1.34387 to \
  -3.03459, 1.34387 to \
  -3.03459, 3.95748 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 346 polygon from \
  -3.07053, 3.98015 to \
  1, 3.98015 to \
  1, 1.33782 to \
  -3.07053, 1.33782 to \
  -3.07053, 3.98015 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 347 polygon from \
  -3.10677, 4.00293 to \
  1, 4.00293 to \
  1, 1.33147 to \
  -3.10677, 1.33147 to \
  -3.10677, 4.00293 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 348 polygon from \
  -3.14331, 4.02582 to \
  1, 4.02582 to \
  1, 1.32483 to \
  -3.14331, 1.32483 to \
  -3.14331, 4.02582 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 349 polygon from \
  -3.18015, 4.04882 to \
  1, 4.04882 to \
  1, 1.3179 to \
  -3.18015, 1.3179 to \
  -3.18015, 4.04882 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 350 polygon from \
  -3.21731, 4.07194 to \
  1, 4.07194 to \
  1, 1.31067 to \
  -3.21731, 1.31067 to \
  -3.21731, 4.07194 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 351 polygon from \
  -3.25479, 4.09517 to \
  1, 4.09517 to \
  1, 1.30313 to \
  -3.25479, 1.30313 to \
  -3.25479, 4.09517 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 352 polygon from \
  -3.29259, 4.11851 to \
  1, 4.11851 to \
  1, 1.2953 to \
  -3.29259, 1.2953 to \
  -3.29259, 4.11851 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 353 polygon from \
  -3.33073, 4.14197 to \
  1, 4.14197 to \
  1, 1.28715 to \
  -3.33073, 1.28715 to \
  -3.33073, 4.14197 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 354 polygon from \
  -3.3692, 4.16555 to \
  1, 4.16555 to \
  1, 1.2787 to \
  -3.3692, 1.2787 to \
  -3.3692, 4.16555 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 355 polygon from \
  -3.40802, 4.18925 to \
  1, 4.18925 to \
  1, 1.26994 to \
  -3.40802, 1.26994 to \
  -3.40802, 4.18925 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 356 polygon from \
  -3.4472, 4.21308 to \
  1, 4.21308 to \
  1, 1.26086 to \
  -3.4472, 1.26086 to \
  -3.4472, 4.21308 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 357 polygon from \
  -3.48673, 4.23703 to \
  1, 4.23703 to \
  1, 1.25146 to \
  -3.48673, 1.25146 to \
  -3.48673, 4.23703 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 358 polygon from \
  -3.52662, 4.2611 to \
  1, 4.2611 to \
  1, 1.24175 to \
  -3.52662, 1.24175 to \
  -3.52662, 4.2611 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 359 polygon from \
  -3.56689, 4.28531 to \
  1, 4.28531 to \
  1, 1.2317 to \
  -3.56689, 1.2317 to \
  -3.56689, 4.28531 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 360 polygon from \
  -3.60754, 4.30964 to \
  1, 4.30964 to \
  1, 1.22134 to \
  -3.60754, 1.22134 to \
  -3.60754, 4.30964 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 361 polygon from \
  -3.64857, 4.3341 to \
  1, 4.3341 to \
  1, 1.21064 to \
  -3.64857, 1.21064 to \
  -3.64857, 4.3341 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 362 polygon from \
  -3.69, 4.3587 to \
  1, 4.3587 to \
  1, 1.19961 to \
  -3.69, 1.19961 to \
  -3.69, 4.3587 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 363 polygon from \
  -3.73182, 4.38343 to \
  1, 4.38343 to \
  1, 1.18825 to \
  -3.73182, 1.18825 to \
  -3.73182, 4.38343 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 364 polygon from \
  -3.77405, 4.4083 to \
  1, 4.4083 to \
  1, 1.17654 to \
  -3.77405, 1.17654 to \
  -3.77405, 4.4083 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 365 polygon from \
  -3.81669, 4.43331 to \
  1, 4.43331 to \
  1, 1.1645 to \
  -3.81669, 1.1645 to \
  -3.81669, 4.43331 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 366 polygon from \
  -3.85976, 4.45846 to \
  1, 4.45846 to \
  1, 1.15211 to \
  -3.85976, 1.15211 to \
  -3.85976, 4.45846 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 367 polygon from \
  -3.90325, 4.48375 to \
  1, 4.48375 to \
  1, 1.13937 to \
  -3.90325, 1.13937 to \
  -3.90325, 4.48375 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 368 polygon from \
  -3.94718, 4.50919 to \
  1, 4.50919 to \
  1, 1.12628 to \
  -3.94718, 1.12628 to \
  -3.94718, 4.50919 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 369 polygon from \
  -3.99155, 4.53478 to \
  1, 4.53478 to \
  1, 1.11283 to \
  -3.99155, 1.11283 to \
  -3.99155, 4.53478 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 370 polygon from \
  -4.03637, 4.56052 to \
  1, 4.56052 to \
  1, 1.09903 to \
  -4.03637, 1.09903 to \
  -4.03637, 4.56052 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 371 polygon from \
  -4.08164, 4.58641 to \
  1, 4.58641 to \
  1, 1.08487 to \
  -4.08164, 1.08487 to \
  -4.08164, 4.58641 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 372 polygon from \
  -4.12738, 4.61245 to \
  1, 4.61245 to \
  1, 1.07034 to \
  -4.12738, 1.07034 to \
  -4.12738, 4.61245 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 373 polygon from \
  -4.1736, 4.63865 to \
  1, 4.63865 to \
  1, 1.05545 to \
  -4.1736, 1.05545 to \
  -4.1736, 4.63865 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 374 polygon from \
  -4.22029, 4.66501 to \
  1, 4.66501 to \
  1, 1.04018 to \
  -4.22029, 1.04018 to \
  -4.22029, 4.66501 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 375 polygon from \
  -4.26747, 4.69153 to \
  1, 4.69153 to \
  1, 1.02454 to \
  -4.26747, 1.02454 to \
  -4.26747, 4.69153 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 376 polygon from \
  -4.31515, 4.71822 to \
  1, 4.71822 to \
  1, 1.00852 to \
  -4.31515, 1.00852 to \
  -4.31515, 4.71822 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 377 polygon from \
  -4.36333, 4.74507 to \
  1, 4.74507 to \
  1, 0.992116 to \
  -4.36333, 0.992116 to \
  -4.36333, 4.74507 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 378 polygon from \
  -4.41202, 4.77209 to \
  1, 4.77209 to \
  1, 0.975331 to \
  -4.41202, 0.975331 to \
  -4.41202, 4.77209 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 379 polygon from \
  -4.46124, 4.79928 to \
  1, 4.79928 to \
  1, 0.958159 to \
  -4.46124, 0.958159 to \
  -4.46124, 4.79928 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 380 polygon from \
  -4.51098, 4.82664 to \
  1, 4.82664 to \
  1, 0.940594 to \
  -4.51098, 0.940594 to \
  -4.51098, 4.82664 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 381 polygon from \
  -4.56125, 4.85418 to \
  1, 4.85418 to \
  1, 0.922634 to \
  -4.56125, 0.922634 to \
  -4.56125, 4.85418 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 382 polygon from \
  -4.61208, 4.8819 to \
  1, 4.8819 to \
  1, 0.904275 to \
  -4.61208, 0.904275 to \
  -4.61208, 4.8819 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 383 polygon from \
  -4.66345, 4.9098 to \
  1, 4.9098 to \
  1, 0.885513 to \
  -4.66345, 0.885513 to \
  -4.66345, 4.9098 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 384 polygon from \
  -4.71539, 4.93788 to \
  1, 4.93788 to \
  1, 0.866344 to \
  -4.71539, 0.866344 to \
  -4.71539, 4.93788 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 385 polygon from \
  -4.76789, 4.96615 to \
  1, 4.96615 to \
  1, 0.846765 to \
  -4.76789, 0.846765 to \
  -4.76789, 4.96615 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 386 polygon from \
  -4.82097, 4.99461 to \
  1, 4.99461 to \
  1, 0.826773 to \
  -4.82097, 0.826773 to \
  -4.82097, 4.99461 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 387 polygon from \
  -4.87465, 5.02326 to \
  1, 5.02326 to \
  1, 0.806362 to \
  -4.87465, 0.806362 to \
  -4.87465, 5.02326 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 388 polygon from \
  -4.92891, 5.05211 to \
  1, 5.05211 to \
  1, 0.78553 to \
  -4.92891, 0.78553 to \
  -4.92891, 5.05211 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 389 polygon from \
  -4.98379, 5.08116 to \
  1, 5.08116 to \
  1, 0.764272 to \
  -4.98379, 0.764272 to \
  -4.98379, 5.08116 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 390 polygon from \
  -5.03927, 5.11041 to \
  1, 5.11041 to \
  1, 0.742585 to \
  -5.03927, 0.742585 to \
  -5.03927, 5.11041 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 391 polygon from \
  -5.09538, 5.13986 to \
  1, 5.13986 to \
  1, 0.720465 to \
  -5.09538, 0.720465 to \
  -5.09538, 5.13986 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 392 polygon from \
  -5.15212, 5.16952 to \
  1, 5.16952 to \
  1, 0.697906 to \
  -5.15212, 0.697906 to \
  -5.15212, 5.16952 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 393 polygon from \
  -5.20951, 5.19938 to \
  1, 5.19938 to \
  1, 0.674907 to \
  -5.20951, 0.674907 to \
  -5.20951, 5.19938 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 394 polygon from \
  -5.26754, 5.22947 to \
  1, 5.22947 to \
  1, 0.651461 to \
  -5.26754, 0.651461 to \
  -5.26754, 5.22947 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 395 polygon from \
  -5.32623, 5.25976 to \
  1, 5.25976 to \
  1, 0.627566 to \
  -5.32623, 0.627566 to \
  -5.32623, 5.25976 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 396 polygon from \
  -5.3856, 5.29028 to \
  1, 5.29028 to \
  1, 0.603217 to \
  -5.3856, 0.603217 to \
  -5.3856, 5.29028 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 397 polygon from \
  -5.44564, 5.32102 to \
  1, 5.32102 to \
  1, 0.57841 to \
  -5.44564, 0.57841 to \
  -5.44564, 5.32102 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 398 polygon from \
  -5.50637, 5.35199 to \
  1, 5.35199 to \
  1, 0.55314 to \
  -5.50637, 0.55314 to \
  -5.50637, 5.35199 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 399 polygon from \
  -5.5678, 5.38318 to \
  1, 5.38318 to \
  1, 0.527403 to \
  -5.5678, 0.527403 to \
  -5.5678, 5.38318 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 400 polygon from \
  -5.62994, 5.41461 to \
  1, 5.41461 to \
  1, 0.501195 to \
  -5.62994, 0.501195 to \
  -5.62994, 5.41461 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 401 polygon from \
  -5.6928, 5.44628 to \
  1, 5.44628 to \
  1, 0.474511 to \
  -5.6928, 0.474511 to \
  -5.6928, 5.44628 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 402 polygon from \
  -5.75638, 5.47818 to \
  1, 5.47818 to \
  1, 0.447347 to \
  -5.75638, 0.447347 to \
  -5.75638, 5.47818 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 403 polygon from \
  -5.82071, 5.51033 to \
  1, 5.51033 to \
  1, 0.419699 to \
  -5.82071, 0.419699 to \
  -5.82071, 5.51033 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 404 polygon from \
  -5.88578, 5.54272 to \
  1, 5.54272 to \
  1, 0.391561 to \
  -5.88578, 0.391561 to \
  -5.88578, 5.54272 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 405 polygon from \
  -5.95161, 5.57537 to \
  1, 5.57537 to \
  1, 0.36293 to \
  -5.95161, 0.36293 to \
  -5.95161, 5.57537 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 406 polygon from \
  -6.01822, 5.60826 to \
  1, 5.60826 to \
  1, 0.3338 to \
  -6.01822, 0.3338 to \
  -6.01822, 5.60826 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 407 polygon from \
  -6.0856, 5.64142 to \
  1, 5.64142 to \
  1, 0.304167 to \
  -6.0856, 0.304167 to \
  -6.0856, 5.64142 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 408 polygon from \
  -6.15377, 5.67484 to \
  1, 5.67484 to \
  1, 0.274026 to \
  -6.15377, 0.274026 to \
  -6.15377, 5.67484 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 409 polygon from \
  -6.22275, 5.70852 to \
  1, 5.70852 to \
  1, 0.243372 to \
  -6.22275, 0.243372 to \
  -6.22275, 5.70852 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 410 polygon from \
  -6.29254, 5.74247 to \
  1, 5.74247 to \
  1, 0.2122 to \
  -6.29254, 0.2122 to \
  -6.29254, 5.74247 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 411 polygon from \
  -6.36316, 5.77669 to \
  1, 5.77669 to \
  1, 0.180506 to \
  -6.36316, 0.180506 to \
  -6.36316, 5.77669 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 412 polygon from \
  -6.4346, 5.81119 to \
  1, 5.81119 to \
  1, 0.148284 to \
  -6.4346, 0.148284 to \
  -6.4346, 5.81119 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 413 polygon from \
  -6.5069, 5.84597 to \
  1, 5.84597 to \
  1, 0.115529 to \
  -6.5069, 0.115529 to \
  -6.5069, 5.84597 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 414 polygon from \
  -6.58005, 5.88104 to \
  1, 5.88104 to \
  1, 0.0822365 to \
  -6.58005, 0.0822365 to \
  -6.58005, 5.88104 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 415 polygon from \
  -6.65408, 5.91639 to \
  1, 5.91639 to \
  1, 0.0484011 to \
  -6.65408, 0.0484011 to \
  -6.65408, 5.91639 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 416 polygon from \
  -6.72898, 5.95204 to \
  1, 5.95204 to \
  1, 0.0140176 to \
  -6.72898, 0.0140176 to \
  -6.72898, 5.95204 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 417 polygon from \
  -6.80478, 5.98798 to \
  1, 5.98798 to \
  1, -0.0209194 to \
  -6.80478, -0.0209194 to \
  -6.80478, 5.98798 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 418 polygon from \
  -6.88148, 6.02423 to \
  1, 6.02423 to \
  1, -0.0564153 to \
  -6.88148, -0.0564153 to \
  -6.88148, 6.02423 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 419 polygon from \
  -6.95909, 6.06078 to \
  1, 6.06078 to \
  1, -0.0924753 to \
  -6.95909, -0.0924753 to \
  -6.95909, 6.06078 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 420 polygon from \
  -7.03764, 6.09764 to \
  1, 6.09764 to \
  1, -0.129105 to \
  -7.03764, -0.129105 to \
  -7.03764, 6.09764 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 421 polygon from \
  -7.11712, 6.13481 to \
  1, 6.13481 to \
  1, -0.16631 to \
  -7.11712, -0.16631 to \
  -7.11712, 6.13481 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 422 polygon from \
  -7.19756, 6.1723 to \
  1, 6.1723 to \
  1, -0.204095 to \
  -7.19756, -0.204095 to \
  -7.19756, 6.1723 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 423 polygon from \
  -7.27897, 6.21012 to \
  1, 6.21012 to \
  1, -0.242468 to \
  -7.27897, -0.242468 to \
  -7.27897, 6.21012 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 424 polygon from \
  -7.36135, 6.24826 to \
  1, 6.24826 to \
  1, -0.281432 to \
  -7.36135, -0.281432 to \
  -7.36135, 6.24826 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 425 polygon from \
  -7.44472, 6.28674 to \
  1, 6.28674 to \
  1, -0.320994 to \
  -7.44472, -0.320994 to \
  -7.44472, 6.28674 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 426 polygon from \
  -7.5291, 6.32555 to \
  1, 6.32555 to \
  1, -0.361161 to \
  -7.5291, -0.361161 to \
  -7.5291, 6.32555 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 427 polygon from \
  -7.61449, 6.36471 to \
  1, 6.36471 to \
  1, -0.401937 to \
  -7.61449, -0.401937 to \
  -7.61449, 6.36471 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 428 polygon from \
  -7.70091, 6.40421 to \
  1, 6.40421 to \
  1, -0.443329 to \
  -7.70091, -0.443329 to \
  -7.70091, 6.40421 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 429 polygon from \
  -7.78838, 6.44407 to \
  1, 6.44407 to \
  1, -0.485342 to \
  -7.78838, -0.485342 to \
  -7.78838, 6.44407 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 430 polygon from \
  -7.8769, 6.48428 to \
  1, 6.48428 to \
  1, -0.527984 to \
  -7.8769, -0.527984 to \
  -7.8769, 6.48428 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 431 polygon from \
  -7.96649, 6.52485 to \
  1, 6.52485 to \
  1, -0.57126 to \
  -7.96649, -0.57126 to \
  -7.96649, 6.52485 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 432 polygon from \
  -8.05716, 6.56578 to \
  1, 6.56578 to \
  1, -0.615176 to \
  -8.05716, -0.615176 to \
  -8.05716, 6.56578 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 433 polygon from \
  -8.14893, 6.60709 to \
  1, 6.60709 to \
  1, -0.659739 to \
  -8.14893, -0.659739 to \
  -8.14893, 6.60709 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 434 polygon from \
  -8.24182, 6.64878 to \
  1, 6.64878 to \
  1, -0.704955 to \
  -8.24182, -0.704955 to \
  -8.24182, 6.64878 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 435 polygon from \
  -8.33582, 6.69085 to \
  1, 6.69085 to \
  1, -0.750831 to \
  -8.33582, -0.750831 to \
  -8.33582, 6.69085 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 436 polygon from \
  -8.43097, 6.7333 to \
  1, 6.7333 to \
  1, -0.797374 to \
  -8.43097, -0.797374 to \
  -8.43097, 6.7333 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 437 polygon from \
  -8.52727, 6.77615 to \
  1, 6.77615 to \
  1, -0.844589 to \
  -8.52727, -0.844589 to \
  -8.52727, 6.77615 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 438 polygon from \
  -8.62474, 6.81939 to \
  1, 6.81939 to \
  1, -0.892485 to \
  -8.62474, -0.892485 to \
  -8.62474, 6.81939 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 439 polygon from \
  -8.72339, 6.86304 to \
  1, 6.86304 to \
  1, -0.941066 to \
  -8.72339, -0.941066 to \
  -8.72339, 6.86304 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 440 polygon from \
  -8.82324, 6.9071 to \
  1, 6.9071 to \
  1, -0.990342 to \
  -8.82324, -0.990342 to \
  -8.82324, 6.9071 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 441 polygon from \
  -8.9243, 6.95157 to \
  1, 6.95157 to \
  1, -1.04031 to \
  -8.9243, -1.04031 to \
  -8.9243, 6.95157 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 442 polygon from \
  -9.0266, 6.99646 to \
  1, 6.99646 to \
  1, -1.091 to \
  -9.0266, -1.091 to \
  -9.0266, 6.99646 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 443 polygon from \
  -9.13013, 7.04178 to \
  1, 7.04178 to \
  1, -1.14239 to \
  -9.13013, -1.14239 to \
  -9.13013, 7.04178 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 444 polygon from \
  -9.23492, 7.08752 to \
  1, 7.08752 to \
  1, -1.19451 to \
  -9.23492, -1.19451 to \
  -9.23492, 7.08752 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 445 polygon from \
  -9.34099, 7.13371 to \
  1, 7.13371 to \
  1, -1.24736 to \
  -9.34099, -1.24736 to \
  -9.34099, 7.13371 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 446 polygon from \
  -9.44835, 7.18034 to \
  1, 7.18034 to \
  1, -1.30095 to \
  -9.44835, -1.30095 to \
  -9.44835, 7.18034 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 447 polygon from \
  -9.55701, 7.22742 to \
  1, 7.22742 to \
  1, -1.35528 to \
  -9.55701, -1.35528 to \
  -9.55701, 7.22742 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 448 polygon from \
  -9.667, 7.27495 to \
  1, 7.27495 to \
  1, -1.41036 to \
  -9.667, -1.41036 to \
  -9.667, 7.27495 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 449 polygon from \
  -9.77832, 7.32295 to \
  1, 7.32295 to \
  1, -1.4662 to \
  -9.77832, -1.4662 to \
  -9.77832, 7.32295 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 450 polygon from \
  -9.891, 7.37141 to \
  1, 7.37141 to \
  1, -1.52281 to \
  -9.891, -1.52281 to \
  -9.891, 7.37141 front fs empty border lc rgb '#f6a800' lw 0.200001
set object 451 polygon from \
  -10.005, 7.42035 to \
  1, 7.42035 to \
  1, -1.58019 to \
  -10.005, -1.58019 to \
  -10.005, 7.42035 front fs empty border lc rgb '#f6a800' lw 0.200001
plot [-11.4176:5.53328] [-2.48025:8.32041] NaN notitle 

