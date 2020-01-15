# settings
set term pdf
set output "rod_reactor_vpoly_double_glpk_z3.pdf
set xtics autofreq
set ytics autofreq
set grid back
# axis settings
set xzeroaxis 
set zeroaxis 
set xtics axis 
set xrange [506.002:553.98] 
set yzeroaxis 
set ytics axis 
set yrange [18.391:37.6991] 

# plotting sets
set object 1 polygon from \
  510, 20.0001 to \
  510.001, 20.0001 to \
  510.001, 20 to \
  510, 20 to \
  510, 20.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 2 polygon from \
  510.01, 20.0101 to \
  510.011, 20.0101 to \
  510.011, 20.01 to \
  510.01, 20.01 to \
  510.01, 20.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 3 polygon from \
  510.02, 20.0201 to \
  510.021, 20.0201 to \
  510.021, 20.02 to \
  510.02, 20.02 to \
  510.02, 20.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 4 polygon from \
  510.03, 20.0301 to \
  510.031, 20.0301 to \
  510.031, 20.03 to \
  510.03, 20.03 to \
  510.03, 20.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 5 polygon from \
  510.04, 20.0401 to \
  510.041, 20.0401 to \
  510.041, 20.04 to \
  510.04, 20.04 to \
  510.04, 20.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 6 polygon from \
  510.05, 20.0501 to \
  510.051, 20.0501 to \
  510.051, 20.05 to \
  510.05, 20.05 to \
  510.05, 20.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 7 polygon from \
  510.06, 20.0601 to \
  510.061, 20.0601 to \
  510.061, 20.06 to \
  510.06, 20.06 to \
  510.06, 20.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 8 polygon from \
  510.07, 20.0701 to \
  510.071, 20.0701 to \
  510.071, 20.07 to \
  510.07, 20.07 to \
  510.07, 20.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 9 polygon from \
  510.08, 20.0801 to \
  510.081, 20.0801 to \
  510.081, 20.08 to \
  510.08, 20.08 to \
  510.08, 20.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 10 polygon from \
  510.09, 20.0901 to \
  510.092, 20.0901 to \
  510.092, 20.09 to \
  510.09, 20.09 to \
  510.09, 20.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 11 polygon from \
  510.1, 20.1001 to \
  510.102, 20.1001 to \
  510.102, 20.1 to \
  510.1, 20.1 to \
  510.1, 20.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 12 polygon from \
  510.11, 20.1101 to \
  510.112, 20.1101 to \
  510.112, 20.11 to \
  510.11, 20.11 to \
  510.11, 20.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 13 polygon from \
  510.121, 20.1201 to \
  510.122, 20.1201 to \
  510.122, 20.12 to \
  510.121, 20.12 to \
  510.121, 20.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 14 polygon from \
  510.131, 20.1301 to \
  510.132, 20.1301 to \
  510.132, 20.13 to \
  510.131, 20.13 to \
  510.131, 20.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 15 polygon from \
  510.141, 20.1401 to \
  510.142, 20.1401 to \
  510.142, 20.14 to \
  510.141, 20.14 to \
  510.141, 20.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 16 polygon from \
  510.151, 20.1501 to \
  510.152, 20.1501 to \
  510.152, 20.15 to \
  510.151, 20.15 to \
  510.151, 20.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 17 polygon from \
  510.161, 20.1601 to \
  510.162, 20.1601 to \
  510.162, 20.16 to \
  510.161, 20.16 to \
  510.161, 20.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 18 polygon from \
  510.171, 20.1701 to \
  510.173, 20.1701 to \
  510.173, 20.17 to \
  510.171, 20.17 to \
  510.171, 20.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 19 polygon from \
  510.181, 20.1801 to \
  510.183, 20.1801 to \
  510.183, 20.18 to \
  510.181, 20.18 to \
  510.181, 20.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 20 polygon from \
  510.192, 20.1901 to \
  510.193, 20.1901 to \
  510.193, 20.19 to \
  510.192, 20.19 to \
  510.192, 20.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 21 polygon from \
  510.202, 20.2001 to \
  510.203, 20.2001 to \
  510.203, 20.2 to \
  510.202, 20.2 to \
  510.202, 20.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 22 polygon from \
  510.212, 20.2101 to \
  510.213, 20.2101 to \
  510.213, 20.21 to \
  510.212, 20.21 to \
  510.212, 20.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 23 polygon from \
  510.222, 20.2201 to \
  510.224, 20.2201 to \
  510.224, 20.22 to \
  510.222, 20.22 to \
  510.222, 20.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 24 polygon from \
  510.233, 20.2301 to \
  510.234, 20.2301 to \
  510.234, 20.23 to \
  510.233, 20.23 to \
  510.233, 20.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 25 polygon from \
  510.243, 20.2401 to \
  510.244, 20.2401 to \
  510.244, 20.24 to \
  510.243, 20.24 to \
  510.243, 20.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 26 polygon from \
  510.253, 20.2501 to \
  510.254, 20.2501 to \
  510.254, 20.25 to \
  510.253, 20.25 to \
  510.253, 20.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 27 polygon from \
  510.263, 20.2601 to \
  510.265, 20.2601 to \
  510.265, 20.26 to \
  510.263, 20.26 to \
  510.263, 20.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 28 polygon from \
  510.274, 20.2701 to \
  510.275, 20.2701 to \
  510.275, 20.27 to \
  510.274, 20.27 to \
  510.274, 20.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 29 polygon from \
  510.284, 20.2801 to \
  510.285, 20.2801 to \
  510.285, 20.28 to \
  510.284, 20.28 to \
  510.284, 20.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 30 polygon from \
  510.294, 20.2901 to \
  510.295, 20.2901 to \
  510.295, 20.29 to \
  510.294, 20.29 to \
  510.294, 20.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 31 polygon from \
  510.304, 20.3001 to \
  510.306, 20.3001 to \
  510.306, 20.3 to \
  510.304, 20.3 to \
  510.304, 20.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 32 polygon from \
  510.315, 20.3101 to \
  510.316, 20.3101 to \
  510.316, 20.31 to \
  510.315, 20.31 to \
  510.315, 20.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 33 polygon from \
  510.325, 20.3201 to \
  510.326, 20.3201 to \
  510.326, 20.32 to \
  510.325, 20.32 to \
  510.325, 20.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 34 polygon from \
  510.335, 20.3301 to \
  510.337, 20.3301 to \
  510.337, 20.33 to \
  510.335, 20.33 to \
  510.335, 20.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 35 polygon from \
  510.346, 20.3401 to \
  510.347, 20.3401 to \
  510.347, 20.34 to \
  510.346, 20.34 to \
  510.346, 20.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 36 polygon from \
  510.356, 20.3501 to \
  510.357, 20.3501 to \
  510.357, 20.35 to \
  510.356, 20.35 to \
  510.356, 20.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 37 polygon from \
  510.366, 20.3601 to \
  510.368, 20.3601 to \
  510.368, 20.36 to \
  510.366, 20.36 to \
  510.366, 20.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 38 polygon from \
  510.377, 20.3701 to \
  510.378, 20.3701 to \
  510.378, 20.37 to \
  510.377, 20.37 to \
  510.377, 20.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 39 polygon from \
  510.387, 20.3801 to \
  510.388, 20.3801 to \
  510.388, 20.38 to \
  510.387, 20.38 to \
  510.387, 20.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 40 polygon from \
  510.398, 20.3901 to \
  510.399, 20.3901 to \
  510.399, 20.39 to \
  510.398, 20.39 to \
  510.398, 20.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 41 polygon from \
  510.408, 20.4001 to \
  510.409, 20.4001 to \
  510.409, 20.4 to \
  510.408, 20.4 to \
  510.408, 20.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 42 polygon from \
  510.418, 20.4101 to \
  510.42, 20.4101 to \
  510.42, 20.41 to \
  510.418, 20.41 to \
  510.418, 20.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 43 polygon from \
  510.429, 20.4201 to \
  510.43, 20.4201 to \
  510.43, 20.42 to \
  510.429, 20.42 to \
  510.429, 20.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 44 polygon from \
  510.439, 20.4301 to \
  510.441, 20.4301 to \
  510.441, 20.43 to \
  510.439, 20.43 to \
  510.439, 20.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 45 polygon from \
  510.45, 20.4401 to \
  510.451, 20.4401 to \
  510.451, 20.44 to \
  510.45, 20.44 to \
  510.45, 20.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 46 polygon from \
  510.46, 20.4501 to \
  510.461, 20.4501 to \
  510.461, 20.45 to \
  510.46, 20.45 to \
  510.46, 20.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 47 polygon from \
  510.471, 20.4601 to \
  510.472, 20.4601 to \
  510.472, 20.46 to \
  510.471, 20.46 to \
  510.471, 20.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 48 polygon from \
  510.481, 20.4701 to \
  510.482, 20.4701 to \
  510.482, 20.47 to \
  510.481, 20.47 to \
  510.481, 20.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 49 polygon from \
  510.492, 20.4801 to \
  510.493, 20.4801 to \
  510.493, 20.48 to \
  510.492, 20.48 to \
  510.492, 20.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 50 polygon from \
  510.502, 20.4901 to \
  510.503, 20.4901 to \
  510.503, 20.49 to \
  510.502, 20.49 to \
  510.502, 20.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 51 polygon from \
  510.513, 20.5001 to \
  510.514, 20.5001 to \
  510.514, 20.5 to \
  510.513, 20.5 to \
  510.513, 20.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 52 polygon from \
  510.523, 20.5101 to \
  510.524, 20.5101 to \
  510.524, 20.51 to \
  510.523, 20.51 to \
  510.523, 20.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 53 polygon from \
  510.534, 20.5201 to \
  510.535, 20.5201 to \
  510.535, 20.52 to \
  510.534, 20.52 to \
  510.534, 20.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 54 polygon from \
  510.544, 20.5301 to \
  510.545, 20.5301 to \
  510.545, 20.53 to \
  510.544, 20.53 to \
  510.544, 20.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 55 polygon from \
  510.555, 20.5401 to \
  510.556, 20.5401 to \
  510.556, 20.54 to \
  510.555, 20.54 to \
  510.555, 20.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 56 polygon from \
  510.565, 20.5501 to \
  510.567, 20.5501 to \
  510.567, 20.55 to \
  510.565, 20.55 to \
  510.565, 20.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 57 polygon from \
  510.576, 20.5601 to \
  510.577, 20.5601 to \
  510.577, 20.56 to \
  510.576, 20.56 to \
  510.576, 20.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 58 polygon from \
  510.586, 20.5701 to \
  510.588, 20.5701 to \
  510.588, 20.57 to \
  510.586, 20.57 to \
  510.586, 20.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 59 polygon from \
  510.597, 20.5801 to \
  510.598, 20.5801 to \
  510.598, 20.58 to \
  510.597, 20.58 to \
  510.597, 20.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 60 polygon from \
  510.608, 20.5901 to \
  510.609, 20.5901 to \
  510.609, 20.59 to \
  510.608, 20.59 to \
  510.608, 20.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 61 polygon from \
  510.618, 20.6001 to \
  510.62, 20.6001 to \
  510.62, 20.6 to \
  510.618, 20.6 to \
  510.618, 20.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 62 polygon from \
  510.629, 20.6101 to \
  510.63, 20.6101 to \
  510.63, 20.61 to \
  510.629, 20.61 to \
  510.629, 20.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 63 polygon from \
  510.639, 20.6201 to \
  510.641, 20.6201 to \
  510.641, 20.62 to \
  510.639, 20.62 to \
  510.639, 20.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 64 polygon from \
  510.65, 20.6301 to \
  510.651, 20.6301 to \
  510.651, 20.63 to \
  510.65, 20.63 to \
  510.65, 20.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 65 polygon from \
  510.661, 20.6401 to \
  510.662, 20.6401 to \
  510.662, 20.64 to \
  510.661, 20.64 to \
  510.661, 20.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 66 polygon from \
  510.671, 20.6501 to \
  510.673, 20.6501 to \
  510.673, 20.65 to \
  510.671, 20.65 to \
  510.671, 20.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 67 polygon from \
  510.682, 20.6601 to \
  510.683, 20.6601 to \
  510.683, 20.66 to \
  510.682, 20.66 to \
  510.682, 20.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 68 polygon from \
  510.693, 20.6701 to \
  510.694, 20.6701 to \
  510.694, 20.67 to \
  510.693, 20.67 to \
  510.693, 20.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 69 polygon from \
  510.703, 20.6801 to \
  510.705, 20.6801 to \
  510.705, 20.68 to \
  510.703, 20.68 to \
  510.703, 20.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 70 polygon from \
  510.714, 20.6901 to \
  510.716, 20.6901 to \
  510.716, 20.69 to \
  510.714, 20.69 to \
  510.714, 20.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 71 polygon from \
  510.725, 20.7001 to \
  510.726, 20.7001 to \
  510.726, 20.7 to \
  510.725, 20.7 to \
  510.725, 20.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 72 polygon from \
  510.736, 20.7101 to \
  510.737, 20.7101 to \
  510.737, 20.71 to \
  510.736, 20.71 to \
  510.736, 20.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 73 polygon from \
  510.746, 20.7201 to \
  510.748, 20.7201 to \
  510.748, 20.72 to \
  510.746, 20.72 to \
  510.746, 20.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 74 polygon from \
  510.757, 20.7301 to \
  510.758, 20.7301 to \
  510.758, 20.73 to \
  510.757, 20.73 to \
  510.757, 20.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 75 polygon from \
  510.768, 20.7401 to \
  510.769, 20.7401 to \
  510.769, 20.74 to \
  510.768, 20.74 to \
  510.768, 20.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 76 polygon from \
  510.779, 20.7501 to \
  510.78, 20.7501 to \
  510.78, 20.75 to \
  510.779, 20.75 to \
  510.779, 20.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 77 polygon from \
  510.789, 20.7601 to \
  510.791, 20.7601 to \
  510.791, 20.76 to \
  510.789, 20.76 to \
  510.789, 20.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 78 polygon from \
  510.8, 20.7701 to \
  510.802, 20.7701 to \
  510.802, 20.77 to \
  510.8, 20.77 to \
  510.8, 20.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 79 polygon from \
  510.811, 20.7801 to \
  510.812, 20.7801 to \
  510.812, 20.78 to \
  510.811, 20.78 to \
  510.811, 20.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 80 polygon from \
  510.822, 20.7901 to \
  510.823, 20.7901 to \
  510.823, 20.79 to \
  510.822, 20.79 to \
  510.822, 20.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 81 polygon from \
  510.833, 20.8001 to \
  510.834, 20.8001 to \
  510.834, 20.8 to \
  510.833, 20.8 to \
  510.833, 20.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 82 polygon from \
  510.844, 20.8101 to \
  510.845, 20.8101 to \
  510.845, 20.81 to \
  510.844, 20.81 to \
  510.844, 20.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 83 polygon from \
  510.854, 20.8201 to \
  510.856, 20.8201 to \
  510.856, 20.82 to \
  510.854, 20.82 to \
  510.854, 20.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 84 polygon from \
  510.865, 20.8301 to \
  510.867, 20.8301 to \
  510.867, 20.83 to \
  510.865, 20.83 to \
  510.865, 20.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 85 polygon from \
  510.876, 20.8401 to \
  510.877, 20.8401 to \
  510.877, 20.84 to \
  510.876, 20.84 to \
  510.876, 20.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 86 polygon from \
  510.887, 20.8501 to \
  510.888, 20.8501 to \
  510.888, 20.85 to \
  510.887, 20.85 to \
  510.887, 20.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 87 polygon from \
  510.898, 20.8601 to \
  510.899, 20.8601 to \
  510.899, 20.86 to \
  510.898, 20.86 to \
  510.898, 20.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 88 polygon from \
  510.909, 20.8701 to \
  510.91, 20.8701 to \
  510.91, 20.87 to \
  510.909, 20.87 to \
  510.909, 20.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 89 polygon from \
  510.92, 20.8801 to \
  510.921, 20.8801 to \
  510.921, 20.88 to \
  510.92, 20.88 to \
  510.92, 20.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 90 polygon from \
  510.931, 20.8901 to \
  510.932, 20.8901 to \
  510.932, 20.89 to \
  510.931, 20.89 to \
  510.931, 20.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 91 polygon from \
  510.942, 20.9001 to \
  510.943, 20.9001 to \
  510.943, 20.9 to \
  510.942, 20.9 to \
  510.942, 20.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 92 polygon from \
  510.952, 20.9101 to \
  510.954, 20.9101 to \
  510.954, 20.91 to \
  510.952, 20.91 to \
  510.952, 20.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 93 polygon from \
  510.963, 20.9201 to \
  510.965, 20.9201 to \
  510.965, 20.92 to \
  510.963, 20.92 to \
  510.963, 20.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 94 polygon from \
  510.974, 20.9301 to \
  510.976, 20.9301 to \
  510.976, 20.93 to \
  510.974, 20.93 to \
  510.974, 20.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 95 polygon from \
  510.985, 20.9401 to \
  510.987, 20.9401 to \
  510.987, 20.94 to \
  510.985, 20.94 to \
  510.985, 20.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 96 polygon from \
  510.996, 20.9501 to \
  510.998, 20.9501 to \
  510.998, 20.95 to \
  510.996, 20.95 to \
  510.996, 20.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 97 polygon from \
  511.007, 20.9601 to \
  511.009, 20.9601 to \
  511.009, 20.96 to \
  511.007, 20.96 to \
  511.007, 20.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 98 polygon from \
  511.018, 20.9701 to \
  511.02, 20.9701 to \
  511.02, 20.97 to \
  511.018, 20.97 to \
  511.018, 20.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 99 polygon from \
  511.029, 20.9801 to \
  511.031, 20.9801 to \
  511.031, 20.98 to \
  511.029, 20.98 to \
  511.029, 20.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 100 polygon from \
  511.04, 20.9901 to \
  511.042, 20.9901 to \
  511.042, 20.99 to \
  511.04, 20.99 to \
  511.04, 20.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 101 polygon from \
  511.052, 21.0001 to \
  511.053, 21.0001 to \
  511.053, 21 to \
  511.052, 21 to \
  511.052, 21.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 102 polygon from \
  511.063, 21.0101 to \
  511.064, 21.0101 to \
  511.064, 21.01 to \
  511.063, 21.01 to \
  511.063, 21.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 103 polygon from \
  511.074, 21.0201 to \
  511.075, 21.0201 to \
  511.075, 21.02 to \
  511.074, 21.02 to \
  511.074, 21.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 104 polygon from \
  511.085, 21.0301 to \
  511.086, 21.0301 to \
  511.086, 21.03 to \
  511.085, 21.03 to \
  511.085, 21.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 105 polygon from \
  511.096, 21.0401 to \
  511.097, 21.0401 to \
  511.097, 21.04 to \
  511.096, 21.04 to \
  511.096, 21.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 106 polygon from \
  511.107, 21.0501 to \
  511.108, 21.0501 to \
  511.108, 21.05 to \
  511.107, 21.05 to \
  511.107, 21.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 107 polygon from \
  511.118, 21.0601 to \
  511.119, 21.0601 to \
  511.119, 21.06 to \
  511.118, 21.06 to \
  511.118, 21.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 108 polygon from \
  511.129, 21.0701 to \
  511.131, 21.0701 to \
  511.131, 21.07 to \
  511.129, 21.07 to \
  511.129, 21.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 109 polygon from \
  511.14, 21.0801 to \
  511.142, 21.0801 to \
  511.142, 21.08 to \
  511.14, 21.08 to \
  511.14, 21.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 110 polygon from \
  511.151, 21.0901 to \
  511.153, 21.0901 to \
  511.153, 21.09 to \
  511.151, 21.09 to \
  511.151, 21.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 111 polygon from \
  511.163, 21.1001 to \
  511.164, 21.1001 to \
  511.164, 21.1 to \
  511.163, 21.1 to \
  511.163, 21.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 112 polygon from \
  511.174, 21.1101 to \
  511.175, 21.1101 to \
  511.175, 21.11 to \
  511.174, 21.11 to \
  511.174, 21.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 113 polygon from \
  511.185, 21.1201 to \
  511.186, 21.1201 to \
  511.186, 21.12 to \
  511.185, 21.12 to \
  511.185, 21.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 114 polygon from \
  511.196, 21.1301 to \
  511.198, 21.1301 to \
  511.198, 21.13 to \
  511.196, 21.13 to \
  511.196, 21.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 115 polygon from \
  511.207, 21.1401 to \
  511.209, 21.1401 to \
  511.209, 21.14 to \
  511.207, 21.14 to \
  511.207, 21.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 116 polygon from \
  511.219, 21.1501 to \
  511.22, 21.1501 to \
  511.22, 21.15 to \
  511.219, 21.15 to \
  511.219, 21.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 117 polygon from \
  511.23, 21.1601 to \
  511.231, 21.1601 to \
  511.231, 21.16 to \
  511.23, 21.16 to \
  511.23, 21.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 118 polygon from \
  511.241, 21.1701 to \
  511.242, 21.1701 to \
  511.242, 21.17 to \
  511.241, 21.17 to \
  511.241, 21.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 119 polygon from \
  511.252, 21.1801 to \
  511.254, 21.1801 to \
  511.254, 21.18 to \
  511.252, 21.18 to \
  511.252, 21.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 120 polygon from \
  511.263, 21.1901 to \
  511.265, 21.1901 to \
  511.265, 21.19 to \
  511.263, 21.19 to \
  511.263, 21.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 121 polygon from \
  511.275, 21.2001 to \
  511.276, 21.2001 to \
  511.276, 21.2 to \
  511.275, 21.2 to \
  511.275, 21.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 122 polygon from \
  511.286, 21.2101 to \
  511.287, 21.2101 to \
  511.287, 21.21 to \
  511.286, 21.21 to \
  511.286, 21.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 123 polygon from \
  511.297, 21.2201 to \
  511.299, 21.2201 to \
  511.299, 21.22 to \
  511.297, 21.22 to \
  511.297, 21.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 124 polygon from \
  511.309, 21.2301 to \
  511.31, 21.2301 to \
  511.31, 21.23 to \
  511.309, 21.23 to \
  511.309, 21.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 125 polygon from \
  511.32, 21.2401 to \
  511.321, 21.2401 to \
  511.321, 21.24 to \
  511.32, 21.24 to \
  511.32, 21.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 126 polygon from \
  511.331, 21.2501 to \
  511.333, 21.2501 to \
  511.333, 21.25 to \
  511.331, 21.25 to \
  511.331, 21.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 127 polygon from \
  511.343, 21.2601 to \
  511.344, 21.2601 to \
  511.344, 21.26 to \
  511.343, 21.26 to \
  511.343, 21.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 128 polygon from \
  511.354, 21.2701 to \
  511.355, 21.2701 to \
  511.355, 21.27 to \
  511.354, 21.27 to \
  511.354, 21.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 129 polygon from \
  511.365, 21.2801 to \
  511.367, 21.2801 to \
  511.367, 21.28 to \
  511.365, 21.28 to \
  511.365, 21.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 130 polygon from \
  511.377, 21.2901 to \
  511.378, 21.2901 to \
  511.378, 21.29 to \
  511.377, 21.29 to \
  511.377, 21.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 131 polygon from \
  511.388, 21.3001 to \
  511.39, 21.3001 to \
  511.39, 21.3 to \
  511.388, 21.3 to \
  511.388, 21.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 132 polygon from \
  511.399, 21.3101 to \
  511.401, 21.3101 to \
  511.401, 21.31 to \
  511.399, 21.31 to \
  511.399, 21.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 133 polygon from \
  511.411, 21.3201 to \
  511.412, 21.3201 to \
  511.412, 21.32 to \
  511.411, 21.32 to \
  511.411, 21.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 134 polygon from \
  511.422, 21.3301 to \
  511.424, 21.3301 to \
  511.424, 21.33 to \
  511.422, 21.33 to \
  511.422, 21.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 135 polygon from \
  511.434, 21.3401 to \
  511.435, 21.3401 to \
  511.435, 21.34 to \
  511.434, 21.34 to \
  511.434, 21.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 136 polygon from \
  511.445, 21.3501 to \
  511.447, 21.3501 to \
  511.447, 21.35 to \
  511.445, 21.35 to \
  511.445, 21.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 137 polygon from \
  511.457, 21.3601 to \
  511.458, 21.3601 to \
  511.458, 21.36 to \
  511.457, 21.36 to \
  511.457, 21.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 138 polygon from \
  511.468, 21.3701 to \
  511.47, 21.3701 to \
  511.47, 21.37 to \
  511.468, 21.37 to \
  511.468, 21.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 139 polygon from \
  511.48, 21.3801 to \
  511.481, 21.3801 to \
  511.481, 21.38 to \
  511.48, 21.38 to \
  511.48, 21.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 140 polygon from \
  511.491, 21.3901 to \
  511.492, 21.3901 to \
  511.492, 21.39 to \
  511.491, 21.39 to \
  511.491, 21.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 141 polygon from \
  511.503, 21.4001 to \
  511.504, 21.4001 to \
  511.504, 21.4 to \
  511.503, 21.4 to \
  511.503, 21.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 142 polygon from \
  511.514, 21.4101 to \
  511.515, 21.4101 to \
  511.515, 21.41 to \
  511.514, 21.41 to \
  511.514, 21.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 143 polygon from \
  511.526, 21.4201 to \
  511.527, 21.4201 to \
  511.527, 21.42 to \
  511.526, 21.42 to \
  511.526, 21.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 144 polygon from \
  511.537, 21.4301 to \
  511.539, 21.4301 to \
  511.539, 21.43 to \
  511.537, 21.43 to \
  511.537, 21.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 145 polygon from \
  511.549, 21.4401 to \
  511.55, 21.4401 to \
  511.55, 21.44 to \
  511.549, 21.44 to \
  511.549, 21.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 146 polygon from \
  511.56, 21.4501 to \
  511.562, 21.4501 to \
  511.562, 21.45 to \
  511.56, 21.45 to \
  511.56, 21.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 147 polygon from \
  511.572, 21.4601 to \
  511.573, 21.4601 to \
  511.573, 21.46 to \
  511.572, 21.46 to \
  511.572, 21.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 148 polygon from \
  511.583, 21.4701 to \
  511.585, 21.4701 to \
  511.585, 21.47 to \
  511.583, 21.47 to \
  511.583, 21.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 149 polygon from \
  511.595, 21.4801 to \
  511.596, 21.4801 to \
  511.596, 21.48 to \
  511.595, 21.48 to \
  511.595, 21.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 150 polygon from \
  511.606, 21.4901 to \
  511.608, 21.4901 to \
  511.608, 21.49 to \
  511.606, 21.49 to \
  511.606, 21.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 151 polygon from \
  511.618, 21.5001 to \
  511.62, 21.5001 to \
  511.62, 21.5 to \
  511.618, 21.5 to \
  511.618, 21.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 152 polygon from \
  511.63, 21.5101 to \
  511.631, 21.5101 to \
  511.631, 21.51 to \
  511.63, 21.51 to \
  511.63, 21.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 153 polygon from \
  511.641, 21.5201 to \
  511.643, 21.5201 to \
  511.643, 21.52 to \
  511.641, 21.52 to \
  511.641, 21.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 154 polygon from \
  511.653, 21.5301 to \
  511.654, 21.5301 to \
  511.654, 21.53 to \
  511.653, 21.53 to \
  511.653, 21.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 155 polygon from \
  511.665, 21.5401 to \
  511.666, 21.5401 to \
  511.666, 21.54 to \
  511.665, 21.54 to \
  511.665, 21.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 156 polygon from \
  511.676, 21.5501 to \
  511.678, 21.5501 to \
  511.678, 21.55 to \
  511.676, 21.55 to \
  511.676, 21.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 157 polygon from \
  511.688, 21.5601 to \
  511.689, 21.5601 to \
  511.689, 21.56 to \
  511.688, 21.56 to \
  511.688, 21.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 158 polygon from \
  511.7, 21.5701 to \
  511.701, 21.5701 to \
  511.701, 21.57 to \
  511.7, 21.57 to \
  511.7, 21.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 159 polygon from \
  511.711, 21.5801 to \
  511.713, 21.5801 to \
  511.713, 21.58 to \
  511.711, 21.58 to \
  511.711, 21.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 160 polygon from \
  511.723, 21.5901 to \
  511.725, 21.5901 to \
  511.725, 21.59 to \
  511.723, 21.59 to \
  511.723, 21.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 161 polygon from \
  511.735, 21.6001 to \
  511.736, 21.6001 to \
  511.736, 21.6 to \
  511.735, 21.6 to \
  511.735, 21.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 162 polygon from \
  511.747, 21.6101 to \
  511.748, 21.6101 to \
  511.748, 21.61 to \
  511.747, 21.61 to \
  511.747, 21.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 163 polygon from \
  511.758, 21.6201 to \
  511.76, 21.6201 to \
  511.76, 21.62 to \
  511.758, 21.62 to \
  511.758, 21.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 164 polygon from \
  511.77, 21.6301 to \
  511.772, 21.6301 to \
  511.772, 21.63 to \
  511.77, 21.63 to \
  511.77, 21.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 165 polygon from \
  511.782, 21.6401 to \
  511.783, 21.6401 to \
  511.783, 21.64 to \
  511.782, 21.64 to \
  511.782, 21.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 166 polygon from \
  511.794, 21.6501 to \
  511.795, 21.6501 to \
  511.795, 21.65 to \
  511.794, 21.65 to \
  511.794, 21.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 167 polygon from \
  511.805, 21.6601 to \
  511.807, 21.6601 to \
  511.807, 21.66 to \
  511.805, 21.66 to \
  511.805, 21.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 168 polygon from \
  511.817, 21.6701 to \
  511.819, 21.6701 to \
  511.819, 21.67 to \
  511.817, 21.67 to \
  511.817, 21.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 169 polygon from \
  511.829, 21.6801 to \
  511.831, 21.6801 to \
  511.831, 21.68 to \
  511.829, 21.68 to \
  511.829, 21.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 170 polygon from \
  511.841, 21.6901 to \
  511.842, 21.6901 to \
  511.842, 21.69 to \
  511.841, 21.69 to \
  511.841, 21.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 171 polygon from \
  511.853, 21.7001 to \
  511.854, 21.7001 to \
  511.854, 21.7 to \
  511.853, 21.7 to \
  511.853, 21.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 172 polygon from \
  511.865, 21.7101 to \
  511.866, 21.7101 to \
  511.866, 21.71 to \
  511.865, 21.71 to \
  511.865, 21.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 173 polygon from \
  511.877, 21.7201 to \
  511.878, 21.7201 to \
  511.878, 21.72 to \
  511.877, 21.72 to \
  511.877, 21.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 174 polygon from \
  511.888, 21.7301 to \
  511.89, 21.7301 to \
  511.89, 21.73 to \
  511.888, 21.73 to \
  511.888, 21.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 175 polygon from \
  511.9, 21.7401 to \
  511.902, 21.7401 to \
  511.902, 21.74 to \
  511.9, 21.74 to \
  511.9, 21.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 176 polygon from \
  511.912, 21.7501 to \
  511.914, 21.7501 to \
  511.914, 21.75 to \
  511.912, 21.75 to \
  511.912, 21.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 177 polygon from \
  511.924, 21.7601 to \
  511.926, 21.7601 to \
  511.926, 21.76 to \
  511.924, 21.76 to \
  511.924, 21.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 178 polygon from \
  511.936, 21.7701 to \
  511.938, 21.7701 to \
  511.938, 21.77 to \
  511.936, 21.77 to \
  511.936, 21.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 179 polygon from \
  511.948, 21.7801 to \
  511.95, 21.7801 to \
  511.95, 21.78 to \
  511.948, 21.78 to \
  511.948, 21.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 180 polygon from \
  511.96, 21.7901 to \
  511.961, 21.7901 to \
  511.961, 21.79 to \
  511.96, 21.79 to \
  511.96, 21.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 181 polygon from \
  511.972, 21.8001 to \
  511.973, 21.8001 to \
  511.973, 21.8 to \
  511.972, 21.8 to \
  511.972, 21.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 182 polygon from \
  511.984, 21.8101 to \
  511.985, 21.8101 to \
  511.985, 21.81 to \
  511.984, 21.81 to \
  511.984, 21.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 183 polygon from \
  511.996, 21.8201 to \
  511.997, 21.8201 to \
  511.997, 21.82 to \
  511.996, 21.82 to \
  511.996, 21.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 184 polygon from \
  512.008, 21.8301 to \
  512.009, 21.8301 to \
  512.009, 21.83 to \
  512.008, 21.83 to \
  512.008, 21.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 185 polygon from \
  512.02, 21.8401 to \
  512.021, 21.8401 to \
  512.021, 21.84 to \
  512.02, 21.84 to \
  512.02, 21.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 186 polygon from \
  512.032, 21.8501 to \
  512.033, 21.8501 to \
  512.033, 21.85 to \
  512.032, 21.85 to \
  512.032, 21.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 187 polygon from \
  512.044, 21.8601 to \
  512.045, 21.8601 to \
  512.045, 21.86 to \
  512.044, 21.86 to \
  512.044, 21.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 188 polygon from \
  512.056, 21.8701 to \
  512.058, 21.8701 to \
  512.058, 21.87 to \
  512.056, 21.87 to \
  512.056, 21.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 189 polygon from \
  512.068, 21.8801 to \
  512.07, 21.8801 to \
  512.07, 21.88 to \
  512.068, 21.88 to \
  512.068, 21.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 190 polygon from \
  512.08, 21.8901 to \
  512.082, 21.8901 to \
  512.082, 21.89 to \
  512.08, 21.89 to \
  512.08, 21.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 191 polygon from \
  512.092, 21.9001 to \
  512.094, 21.9001 to \
  512.094, 21.9 to \
  512.092, 21.9 to \
  512.092, 21.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 192 polygon from \
  512.104, 21.9101 to \
  512.106, 21.9101 to \
  512.106, 21.91 to \
  512.104, 21.91 to \
  512.104, 21.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 193 polygon from \
  512.116, 21.9201 to \
  512.118, 21.9201 to \
  512.118, 21.92 to \
  512.116, 21.92 to \
  512.116, 21.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 194 polygon from \
  512.129, 21.9301 to \
  512.13, 21.9301 to \
  512.13, 21.93 to \
  512.129, 21.93 to \
  512.129, 21.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 195 polygon from \
  512.141, 21.9401 to \
  512.142, 21.9401 to \
  512.142, 21.94 to \
  512.141, 21.94 to \
  512.141, 21.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 196 polygon from \
  512.153, 21.9501 to \
  512.154, 21.9501 to \
  512.154, 21.95 to \
  512.153, 21.95 to \
  512.153, 21.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 197 polygon from \
  512.165, 21.9601 to \
  512.167, 21.9601 to \
  512.167, 21.96 to \
  512.165, 21.96 to \
  512.165, 21.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 198 polygon from \
  512.177, 21.9701 to \
  512.179, 21.9701 to \
  512.179, 21.97 to \
  512.177, 21.97 to \
  512.177, 21.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 199 polygon from \
  512.189, 21.9801 to \
  512.191, 21.9801 to \
  512.191, 21.98 to \
  512.189, 21.98 to \
  512.189, 21.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 200 polygon from \
  512.202, 21.9901 to \
  512.203, 21.9901 to \
  512.203, 21.99 to \
  512.202, 21.99 to \
  512.202, 21.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 201 polygon from \
  512.214, 22.0001 to \
  512.215, 22.0001 to \
  512.215, 22 to \
  512.214, 22 to \
  512.214, 22.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 202 polygon from \
  512.226, 22.0101 to \
  512.228, 22.0101 to \
  512.228, 22.01 to \
  512.226, 22.01 to \
  512.226, 22.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 203 polygon from \
  512.238, 22.0201 to \
  512.24, 22.0201 to \
  512.24, 22.02 to \
  512.238, 22.02 to \
  512.238, 22.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 204 polygon from \
  512.25, 22.0301 to \
  512.252, 22.0301 to \
  512.252, 22.03 to \
  512.25, 22.03 to \
  512.25, 22.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 205 polygon from \
  512.263, 22.0401 to \
  512.264, 22.0401 to \
  512.264, 22.04 to \
  512.263, 22.04 to \
  512.263, 22.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 206 polygon from \
  512.275, 22.0501 to \
  512.277, 22.0501 to \
  512.277, 22.05 to \
  512.275, 22.05 to \
  512.275, 22.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 207 polygon from \
  512.287, 22.0601 to \
  512.289, 22.0601 to \
  512.289, 22.06 to \
  512.287, 22.06 to \
  512.287, 22.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 208 polygon from \
  512.3, 22.0701 to \
  512.301, 22.0701 to \
  512.301, 22.07 to \
  512.3, 22.07 to \
  512.3, 22.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 209 polygon from \
  512.312, 22.0801 to \
  512.313, 22.0801 to \
  512.313, 22.08 to \
  512.312, 22.08 to \
  512.312, 22.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 210 polygon from \
  512.324, 22.0901 to \
  512.326, 22.0901 to \
  512.326, 22.09 to \
  512.324, 22.09 to \
  512.324, 22.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 211 polygon from \
  512.337, 22.1001 to \
  512.338, 22.1001 to \
  512.338, 22.1 to \
  512.337, 22.1 to \
  512.337, 22.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 212 polygon from \
  512.349, 22.1101 to \
  512.35, 22.1101 to \
  512.35, 22.11 to \
  512.349, 22.11 to \
  512.349, 22.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 213 polygon from \
  512.361, 22.1201 to \
  512.363, 22.1201 to \
  512.363, 22.12 to \
  512.361, 22.12 to \
  512.361, 22.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 214 polygon from \
  512.374, 22.1301 to \
  512.375, 22.1301 to \
  512.375, 22.13 to \
  512.374, 22.13 to \
  512.374, 22.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 215 polygon from \
  512.386, 22.1401 to \
  512.388, 22.1401 to \
  512.388, 22.14 to \
  512.386, 22.14 to \
  512.386, 22.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 216 polygon from \
  512.398, 22.1501 to \
  512.4, 22.1501 to \
  512.4, 22.15 to \
  512.398, 22.15 to \
  512.398, 22.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 217 polygon from \
  512.411, 22.1601 to \
  512.412, 22.1601 to \
  512.412, 22.16 to \
  512.411, 22.16 to \
  512.411, 22.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 218 polygon from \
  512.423, 22.1701 to \
  512.425, 22.1701 to \
  512.425, 22.17 to \
  512.423, 22.17 to \
  512.423, 22.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 219 polygon from \
  512.436, 22.1801 to \
  512.437, 22.1801 to \
  512.437, 22.18 to \
  512.436, 22.18 to \
  512.436, 22.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 220 polygon from \
  512.448, 22.1901 to \
  512.45, 22.1901 to \
  512.45, 22.19 to \
  512.448, 22.19 to \
  512.448, 22.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 221 polygon from \
  512.46, 22.2001 to \
  512.462, 22.2001 to \
  512.462, 22.2 to \
  512.46, 22.2 to \
  512.46, 22.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 222 polygon from \
  512.473, 22.2101 to \
  512.475, 22.2101 to \
  512.475, 22.21 to \
  512.473, 22.21 to \
  512.473, 22.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 223 polygon from \
  512.485, 22.2201 to \
  512.487, 22.2201 to \
  512.487, 22.22 to \
  512.485, 22.22 to \
  512.485, 22.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 224 polygon from \
  512.498, 22.2301 to \
  512.499, 22.2301 to \
  512.499, 22.23 to \
  512.498, 22.23 to \
  512.498, 22.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 225 polygon from \
  512.51, 22.2401 to \
  512.512, 22.2401 to \
  512.512, 22.24 to \
  512.51, 22.24 to \
  512.51, 22.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 226 polygon from \
  512.523, 22.2501 to \
  512.525, 22.2501 to \
  512.525, 22.25 to \
  512.523, 22.25 to \
  512.523, 22.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 227 polygon from \
  512.535, 22.2601 to \
  512.537, 22.2601 to \
  512.537, 22.26 to \
  512.535, 22.26 to \
  512.535, 22.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 228 polygon from \
  512.548, 22.2701 to \
  512.55, 22.2701 to \
  512.55, 22.27 to \
  512.548, 22.27 to \
  512.548, 22.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 229 polygon from \
  512.561, 22.2801 to \
  512.562, 22.2801 to \
  512.562, 22.28 to \
  512.561, 22.28 to \
  512.561, 22.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 230 polygon from \
  512.573, 22.2901 to \
  512.575, 22.2901 to \
  512.575, 22.29 to \
  512.573, 22.29 to \
  512.573, 22.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 231 polygon from \
  512.586, 22.3001 to \
  512.587, 22.3001 to \
  512.587, 22.3 to \
  512.586, 22.3 to \
  512.586, 22.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 232 polygon from \
  512.598, 22.3101 to \
  512.6, 22.3101 to \
  512.6, 22.31 to \
  512.598, 22.31 to \
  512.598, 22.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 233 polygon from \
  512.611, 22.3201 to \
  512.612, 22.3201 to \
  512.612, 22.32 to \
  512.611, 22.32 to \
  512.611, 22.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 234 polygon from \
  512.624, 22.3301 to \
  512.625, 22.3301 to \
  512.625, 22.33 to \
  512.624, 22.33 to \
  512.624, 22.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 235 polygon from \
  512.636, 22.3401 to \
  512.638, 22.3401 to \
  512.638, 22.34 to \
  512.636, 22.34 to \
  512.636, 22.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 236 polygon from \
  512.649, 22.3501 to \
  512.65, 22.3501 to \
  512.65, 22.35 to \
  512.649, 22.35 to \
  512.649, 22.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 237 polygon from \
  512.661, 22.3601 to \
  512.663, 22.3601 to \
  512.663, 22.36 to \
  512.661, 22.36 to \
  512.661, 22.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 238 polygon from \
  512.674, 22.3701 to \
  512.676, 22.3701 to \
  512.676, 22.37 to \
  512.674, 22.37 to \
  512.674, 22.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 239 polygon from \
  512.687, 22.3801 to \
  512.688, 22.3801 to \
  512.688, 22.38 to \
  512.687, 22.38 to \
  512.687, 22.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 240 polygon from \
  512.699, 22.3901 to \
  512.701, 22.3901 to \
  512.701, 22.39 to \
  512.699, 22.39 to \
  512.699, 22.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 241 polygon from \
  512.712, 22.4001 to \
  512.714, 22.4001 to \
  512.714, 22.4 to \
  512.712, 22.4 to \
  512.712, 22.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 242 polygon from \
  512.725, 22.4101 to \
  512.727, 22.4101 to \
  512.727, 22.41 to \
  512.725, 22.41 to \
  512.725, 22.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 243 polygon from \
  512.738, 22.4201 to \
  512.739, 22.4201 to \
  512.739, 22.42 to \
  512.738, 22.42 to \
  512.738, 22.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 244 polygon from \
  512.75, 22.4301 to \
  512.752, 22.4301 to \
  512.752, 22.43 to \
  512.75, 22.43 to \
  512.75, 22.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 245 polygon from \
  512.763, 22.4401 to \
  512.765, 22.4401 to \
  512.765, 22.44 to \
  512.763, 22.44 to \
  512.763, 22.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 246 polygon from \
  512.776, 22.4501 to \
  512.778, 22.4501 to \
  512.778, 22.45 to \
  512.776, 22.45 to \
  512.776, 22.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 247 polygon from \
  512.789, 22.4601 to \
  512.79, 22.4601 to \
  512.79, 22.46 to \
  512.789, 22.46 to \
  512.789, 22.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 248 polygon from \
  512.801, 22.4701 to \
  512.803, 22.4701 to \
  512.803, 22.47 to \
  512.801, 22.47 to \
  512.801, 22.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 249 polygon from \
  512.814, 22.4801 to \
  512.816, 22.4801 to \
  512.816, 22.48 to \
  512.814, 22.48 to \
  512.814, 22.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 250 polygon from \
  512.827, 22.4901 to \
  512.829, 22.4901 to \
  512.829, 22.49 to \
  512.827, 22.49 to \
  512.827, 22.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 251 polygon from \
  512.84, 22.5001 to \
  512.842, 22.5001 to \
  512.842, 22.5 to \
  512.84, 22.5 to \
  512.84, 22.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 252 polygon from \
  512.853, 22.5101 to \
  512.854, 22.5101 to \
  512.854, 22.51 to \
  512.853, 22.51 to \
  512.853, 22.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 253 polygon from \
  512.866, 22.5201 to \
  512.867, 22.5201 to \
  512.867, 22.52 to \
  512.866, 22.52 to \
  512.866, 22.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 254 polygon from \
  512.879, 22.5301 to \
  512.88, 22.5301 to \
  512.88, 22.53 to \
  512.879, 22.53 to \
  512.879, 22.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 255 polygon from \
  512.891, 22.5401 to \
  512.893, 22.5401 to \
  512.893, 22.54 to \
  512.891, 22.54 to \
  512.891, 22.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 256 polygon from \
  512.904, 22.5501 to \
  512.906, 22.5501 to \
  512.906, 22.55 to \
  512.904, 22.55 to \
  512.904, 22.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 257 polygon from \
  512.917, 22.5601 to \
  512.919, 22.5601 to \
  512.919, 22.56 to \
  512.917, 22.56 to \
  512.917, 22.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 258 polygon from \
  512.93, 22.5701 to \
  512.932, 22.5701 to \
  512.932, 22.57 to \
  512.93, 22.57 to \
  512.93, 22.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 259 polygon from \
  512.943, 22.5801 to \
  512.945, 22.5801 to \
  512.945, 22.58 to \
  512.943, 22.58 to \
  512.943, 22.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 260 polygon from \
  512.956, 22.5901 to \
  512.958, 22.5901 to \
  512.958, 22.59 to \
  512.956, 22.59 to \
  512.956, 22.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 261 polygon from \
  512.969, 22.6001 to \
  512.971, 22.6001 to \
  512.971, 22.6 to \
  512.969, 22.6 to \
  512.969, 22.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 262 polygon from \
  512.982, 22.6101 to \
  512.984, 22.6101 to \
  512.984, 22.61 to \
  512.982, 22.61 to \
  512.982, 22.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 263 polygon from \
  512.995, 22.6201 to \
  512.997, 22.6201 to \
  512.997, 22.62 to \
  512.995, 22.62 to \
  512.995, 22.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 264 polygon from \
  513.008, 22.6301 to \
  513.01, 22.6301 to \
  513.01, 22.63 to \
  513.008, 22.63 to \
  513.008, 22.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 265 polygon from \
  513.021, 22.6401 to \
  513.023, 22.6401 to \
  513.023, 22.64 to \
  513.021, 22.64 to \
  513.021, 22.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 266 polygon from \
  513.034, 22.6501 to \
  513.036, 22.6501 to \
  513.036, 22.65 to \
  513.034, 22.65 to \
  513.034, 22.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 267 polygon from \
  513.047, 22.6601 to \
  513.049, 22.6601 to \
  513.049, 22.66 to \
  513.047, 22.66 to \
  513.047, 22.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 268 polygon from \
  513.06, 22.6701 to \
  513.062, 22.6701 to \
  513.062, 22.67 to \
  513.06, 22.67 to \
  513.06, 22.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 269 polygon from \
  513.073, 22.6801 to \
  513.075, 22.6801 to \
  513.075, 22.68 to \
  513.073, 22.68 to \
  513.073, 22.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 270 polygon from \
  513.086, 22.6901 to \
  513.088, 22.6901 to \
  513.088, 22.69 to \
  513.086, 22.69 to \
  513.086, 22.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 271 polygon from \
  513.099, 22.7001 to \
  513.101, 22.7001 to \
  513.101, 22.7 to \
  513.099, 22.7 to \
  513.099, 22.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 272 polygon from \
  513.112, 22.7101 to \
  513.114, 22.7101 to \
  513.114, 22.71 to \
  513.112, 22.71 to \
  513.112, 22.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 273 polygon from \
  513.126, 22.7201 to \
  513.127, 22.7201 to \
  513.127, 22.72 to \
  513.126, 22.72 to \
  513.126, 22.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 274 polygon from \
  513.139, 22.7301 to \
  513.14, 22.7301 to \
  513.14, 22.73 to \
  513.139, 22.73 to \
  513.139, 22.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 275 polygon from \
  513.152, 22.7401 to \
  513.153, 22.7401 to \
  513.153, 22.74 to \
  513.152, 22.74 to \
  513.152, 22.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 276 polygon from \
  513.165, 22.7501 to \
  513.167, 22.7501 to \
  513.167, 22.75 to \
  513.165, 22.75 to \
  513.165, 22.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 277 polygon from \
  513.178, 22.7601 to \
  513.18, 22.7601 to \
  513.18, 22.76 to \
  513.178, 22.76 to \
  513.178, 22.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 278 polygon from \
  513.191, 22.7701 to \
  513.193, 22.7701 to \
  513.193, 22.77 to \
  513.191, 22.77 to \
  513.191, 22.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 279 polygon from \
  513.205, 22.7801 to \
  513.206, 22.7801 to \
  513.206, 22.78 to \
  513.205, 22.78 to \
  513.205, 22.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 280 polygon from \
  513.218, 22.7901 to \
  513.219, 22.7901 to \
  513.219, 22.79 to \
  513.218, 22.79 to \
  513.218, 22.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 281 polygon from \
  513.231, 22.8001 to \
  513.233, 22.8001 to \
  513.233, 22.8 to \
  513.231, 22.8 to \
  513.231, 22.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 282 polygon from \
  513.244, 22.8101 to \
  513.246, 22.8101 to \
  513.246, 22.81 to \
  513.244, 22.81 to \
  513.244, 22.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 283 polygon from \
  513.257, 22.8201 to \
  513.259, 22.8201 to \
  513.259, 22.82 to \
  513.257, 22.82 to \
  513.257, 22.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 284 polygon from \
  513.271, 22.8301 to \
  513.272, 22.8301 to \
  513.272, 22.83 to \
  513.271, 22.83 to \
  513.271, 22.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 285 polygon from \
  513.284, 22.8401 to \
  513.286, 22.8401 to \
  513.286, 22.84 to \
  513.284, 22.84 to \
  513.284, 22.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 286 polygon from \
  513.297, 22.8501 to \
  513.299, 22.8501 to \
  513.299, 22.85 to \
  513.297, 22.85 to \
  513.297, 22.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 287 polygon from \
  513.311, 22.8601 to \
  513.312, 22.8601 to \
  513.312, 22.86 to \
  513.311, 22.86 to \
  513.311, 22.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 288 polygon from \
  513.324, 22.8701 to \
  513.326, 22.8701 to \
  513.326, 22.87 to \
  513.324, 22.87 to \
  513.324, 22.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 289 polygon from \
  513.337, 22.8801 to \
  513.339, 22.8801 to \
  513.339, 22.88 to \
  513.337, 22.88 to \
  513.337, 22.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 290 polygon from \
  513.351, 22.8901 to \
  513.352, 22.8901 to \
  513.352, 22.89 to \
  513.351, 22.89 to \
  513.351, 22.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 291 polygon from \
  513.364, 22.9001 to \
  513.366, 22.9001 to \
  513.366, 22.9 to \
  513.364, 22.9 to \
  513.364, 22.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 292 polygon from \
  513.377, 22.9101 to \
  513.379, 22.9101 to \
  513.379, 22.91 to \
  513.377, 22.91 to \
  513.377, 22.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 293 polygon from \
  513.391, 22.9201 to \
  513.392, 22.9201 to \
  513.392, 22.92 to \
  513.391, 22.92 to \
  513.391, 22.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 294 polygon from \
  513.404, 22.9301 to \
  513.406, 22.9301 to \
  513.406, 22.93 to \
  513.404, 22.93 to \
  513.404, 22.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 295 polygon from \
  513.417, 22.9401 to \
  513.419, 22.9401 to \
  513.419, 22.94 to \
  513.417, 22.94 to \
  513.417, 22.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 296 polygon from \
  513.431, 22.9501 to \
  513.433, 22.9501 to \
  513.433, 22.95 to \
  513.431, 22.95 to \
  513.431, 22.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 297 polygon from \
  513.444, 22.9601 to \
  513.446, 22.9601 to \
  513.446, 22.96 to \
  513.444, 22.96 to \
  513.444, 22.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 298 polygon from \
  513.458, 22.9701 to \
  513.46, 22.9701 to \
  513.46, 22.97 to \
  513.458, 22.97 to \
  513.458, 22.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 299 polygon from \
  513.471, 22.9801 to \
  513.473, 22.9801 to \
  513.473, 22.98 to \
  513.471, 22.98 to \
  513.471, 22.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 300 polygon from \
  513.485, 22.9901 to \
  513.486, 22.9901 to \
  513.486, 22.99 to \
  513.485, 22.99 to \
  513.485, 22.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 301 polygon from \
  513.498, 23.0001 to \
  513.5, 23.0001 to \
  513.5, 23 to \
  513.498, 23 to \
  513.498, 23.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 302 polygon from \
  513.512, 23.0101 to \
  513.513, 23.0101 to \
  513.513, 23.01 to \
  513.512, 23.01 to \
  513.512, 23.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 303 polygon from \
  513.525, 23.0201 to \
  513.527, 23.0201 to \
  513.527, 23.02 to \
  513.525, 23.02 to \
  513.525, 23.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 304 polygon from \
  513.539, 23.0301 to \
  513.54, 23.0301 to \
  513.54, 23.03 to \
  513.539, 23.03 to \
  513.539, 23.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 305 polygon from \
  513.552, 23.0401 to \
  513.554, 23.0401 to \
  513.554, 23.04 to \
  513.552, 23.04 to \
  513.552, 23.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 306 polygon from \
  513.566, 23.0501 to \
  513.568, 23.0501 to \
  513.568, 23.05 to \
  513.566, 23.05 to \
  513.566, 23.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 307 polygon from \
  513.579, 23.0601 to \
  513.581, 23.0601 to \
  513.581, 23.06 to \
  513.579, 23.06 to \
  513.579, 23.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 308 polygon from \
  513.593, 23.0701 to \
  513.595, 23.0701 to \
  513.595, 23.07 to \
  513.593, 23.07 to \
  513.593, 23.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 309 polygon from \
  513.607, 23.0801 to \
  513.608, 23.0801 to \
  513.608, 23.08 to \
  513.607, 23.08 to \
  513.607, 23.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 310 polygon from \
  513.62, 23.0901 to \
  513.622, 23.0901 to \
  513.622, 23.09 to \
  513.62, 23.09 to \
  513.62, 23.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 311 polygon from \
  513.634, 23.1001 to \
  513.636, 23.1001 to \
  513.636, 23.1 to \
  513.634, 23.1 to \
  513.634, 23.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 312 polygon from \
  513.648, 23.1101 to \
  513.649, 23.1101 to \
  513.649, 23.11 to \
  513.648, 23.11 to \
  513.648, 23.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 313 polygon from \
  513.661, 23.1201 to \
  513.663, 23.1201 to \
  513.663, 23.12 to \
  513.661, 23.12 to \
  513.661, 23.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 314 polygon from \
  513.675, 23.1301 to \
  513.677, 23.1301 to \
  513.677, 23.13 to \
  513.675, 23.13 to \
  513.675, 23.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 315 polygon from \
  513.689, 23.1401 to \
  513.69, 23.1401 to \
  513.69, 23.14 to \
  513.689, 23.14 to \
  513.689, 23.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 316 polygon from \
  513.702, 23.1501 to \
  513.704, 23.1501 to \
  513.704, 23.15 to \
  513.702, 23.15 to \
  513.702, 23.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 317 polygon from \
  513.716, 23.1601 to \
  513.718, 23.1601 to \
  513.718, 23.16 to \
  513.716, 23.16 to \
  513.716, 23.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 318 polygon from \
  513.73, 23.1701 to \
  513.731, 23.1701 to \
  513.731, 23.17 to \
  513.73, 23.17 to \
  513.73, 23.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 319 polygon from \
  513.743, 23.1801 to \
  513.745, 23.1801 to \
  513.745, 23.18 to \
  513.743, 23.18 to \
  513.743, 23.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 320 polygon from \
  513.757, 23.1901 to \
  513.759, 23.1901 to \
  513.759, 23.19 to \
  513.757, 23.19 to \
  513.757, 23.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 321 polygon from \
  513.771, 23.2001 to \
  513.773, 23.2001 to \
  513.773, 23.2 to \
  513.771, 23.2 to \
  513.771, 23.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 322 polygon from \
  513.785, 23.2101 to \
  513.786, 23.2101 to \
  513.786, 23.21 to \
  513.785, 23.21 to \
  513.785, 23.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 323 polygon from \
  513.798, 23.2201 to \
  513.8, 23.2201 to \
  513.8, 23.22 to \
  513.798, 23.22 to \
  513.798, 23.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 324 polygon from \
  513.812, 23.2301 to \
  513.814, 23.2301 to \
  513.814, 23.23 to \
  513.812, 23.23 to \
  513.812, 23.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 325 polygon from \
  513.826, 23.2401 to \
  513.828, 23.2401 to \
  513.828, 23.24 to \
  513.826, 23.24 to \
  513.826, 23.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 326 polygon from \
  513.84, 23.2501 to \
  513.842, 23.2501 to \
  513.842, 23.25 to \
  513.84, 23.25 to \
  513.84, 23.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 327 polygon from \
  513.854, 23.2601 to \
  513.856, 23.2601 to \
  513.856, 23.26 to \
  513.854, 23.26 to \
  513.854, 23.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 328 polygon from \
  513.868, 23.2701 to \
  513.869, 23.2701 to \
  513.869, 23.27 to \
  513.868, 23.27 to \
  513.868, 23.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 329 polygon from \
  513.882, 23.2801 to \
  513.883, 23.2801 to \
  513.883, 23.28 to \
  513.882, 23.28 to \
  513.882, 23.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 330 polygon from \
  513.895, 23.2901 to \
  513.897, 23.2901 to \
  513.897, 23.29 to \
  513.895, 23.29 to \
  513.895, 23.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 331 polygon from \
  513.909, 23.3001 to \
  513.911, 23.3001 to \
  513.911, 23.3 to \
  513.909, 23.3 to \
  513.909, 23.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 332 polygon from \
  513.923, 23.3101 to \
  513.925, 23.3101 to \
  513.925, 23.31 to \
  513.923, 23.31 to \
  513.923, 23.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 333 polygon from \
  513.937, 23.3201 to \
  513.939, 23.3201 to \
  513.939, 23.32 to \
  513.937, 23.32 to \
  513.937, 23.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 334 polygon from \
  513.951, 23.3301 to \
  513.953, 23.3301 to \
  513.953, 23.33 to \
  513.951, 23.33 to \
  513.951, 23.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 335 polygon from \
  513.965, 23.3401 to \
  513.967, 23.3401 to \
  513.967, 23.34 to \
  513.965, 23.34 to \
  513.965, 23.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 336 polygon from \
  513.979, 23.3501 to \
  513.981, 23.3501 to \
  513.981, 23.35 to \
  513.979, 23.35 to \
  513.979, 23.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 337 polygon from \
  513.993, 23.3601 to \
  513.995, 23.3601 to \
  513.995, 23.36 to \
  513.993, 23.36 to \
  513.993, 23.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 338 polygon from \
  514.007, 23.3701 to \
  514.009, 23.3701 to \
  514.009, 23.37 to \
  514.007, 23.37 to \
  514.007, 23.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 339 polygon from \
  514.021, 23.3801 to \
  514.023, 23.3801 to \
  514.023, 23.38 to \
  514.021, 23.38 to \
  514.021, 23.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 340 polygon from \
  514.035, 23.3901 to \
  514.037, 23.3901 to \
  514.037, 23.39 to \
  514.035, 23.39 to \
  514.035, 23.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 341 polygon from \
  514.049, 23.4001 to \
  514.051, 23.4001 to \
  514.051, 23.4 to \
  514.049, 23.4 to \
  514.049, 23.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 342 polygon from \
  514.063, 23.4101 to \
  514.065, 23.4101 to \
  514.065, 23.41 to \
  514.063, 23.41 to \
  514.063, 23.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 343 polygon from \
  514.077, 23.4201 to \
  514.079, 23.4201 to \
  514.079, 23.42 to \
  514.077, 23.42 to \
  514.077, 23.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 344 polygon from \
  514.091, 23.4301 to \
  514.093, 23.4301 to \
  514.093, 23.43 to \
  514.091, 23.43 to \
  514.091, 23.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 345 polygon from \
  514.105, 23.4401 to \
  514.107, 23.4401 to \
  514.107, 23.44 to \
  514.105, 23.44 to \
  514.105, 23.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 346 polygon from \
  514.12, 23.4501 to \
  514.121, 23.4501 to \
  514.121, 23.45 to \
  514.12, 23.45 to \
  514.12, 23.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 347 polygon from \
  514.134, 23.4601 to \
  514.135, 23.4601 to \
  514.135, 23.46 to \
  514.134, 23.46 to \
  514.134, 23.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 348 polygon from \
  514.148, 23.4701 to \
  514.15, 23.4701 to \
  514.15, 23.47 to \
  514.148, 23.47 to \
  514.148, 23.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 349 polygon from \
  514.162, 23.4801 to \
  514.164, 23.4801 to \
  514.164, 23.48 to \
  514.162, 23.48 to \
  514.162, 23.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 350 polygon from \
  514.176, 23.4901 to \
  514.178, 23.4901 to \
  514.178, 23.49 to \
  514.176, 23.49 to \
  514.176, 23.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 351 polygon from \
  514.19, 23.5001 to \
  514.192, 23.5001 to \
  514.192, 23.5 to \
  514.19, 23.5 to \
  514.19, 23.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 352 polygon from \
  514.204, 23.5101 to \
  514.206, 23.5101 to \
  514.206, 23.51 to \
  514.204, 23.51 to \
  514.204, 23.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 353 polygon from \
  514.219, 23.5201 to \
  514.22, 23.5201 to \
  514.22, 23.52 to \
  514.219, 23.52 to \
  514.219, 23.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 354 polygon from \
  514.233, 23.5301 to \
  514.235, 23.5301 to \
  514.235, 23.53 to \
  514.233, 23.53 to \
  514.233, 23.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 355 polygon from \
  514.247, 23.5401 to \
  514.249, 23.5401 to \
  514.249, 23.54 to \
  514.247, 23.54 to \
  514.247, 23.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 356 polygon from \
  514.261, 23.5501 to \
  514.263, 23.5501 to \
  514.263, 23.55 to \
  514.261, 23.55 to \
  514.261, 23.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 357 polygon from \
  514.276, 23.5601 to \
  514.277, 23.5601 to \
  514.277, 23.56 to \
  514.276, 23.56 to \
  514.276, 23.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 358 polygon from \
  514.29, 23.5701 to \
  514.292, 23.5701 to \
  514.292, 23.57 to \
  514.29, 23.57 to \
  514.29, 23.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 359 polygon from \
  514.304, 23.5801 to \
  514.306, 23.5801 to \
  514.306, 23.58 to \
  514.304, 23.58 to \
  514.304, 23.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 360 polygon from \
  514.319, 23.5901 to \
  514.32, 23.5901 to \
  514.32, 23.59 to \
  514.319, 23.59 to \
  514.319, 23.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 361 polygon from \
  514.333, 23.6001 to \
  514.335, 23.6001 to \
  514.335, 23.6 to \
  514.333, 23.6 to \
  514.333, 23.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 362 polygon from \
  514.347, 23.6101 to \
  514.349, 23.6101 to \
  514.349, 23.61 to \
  514.347, 23.61 to \
  514.347, 23.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 363 polygon from \
  514.362, 23.6201 to \
  514.363, 23.6201 to \
  514.363, 23.62 to \
  514.362, 23.62 to \
  514.362, 23.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 364 polygon from \
  514.376, 23.6301 to \
  514.378, 23.6301 to \
  514.378, 23.63 to \
  514.376, 23.63 to \
  514.376, 23.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 365 polygon from \
  514.39, 23.6401 to \
  514.392, 23.6401 to \
  514.392, 23.64 to \
  514.39, 23.64 to \
  514.39, 23.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 366 polygon from \
  514.405, 23.6501 to \
  514.407, 23.6501 to \
  514.407, 23.65 to \
  514.405, 23.65 to \
  514.405, 23.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 367 polygon from \
  514.419, 23.6601 to \
  514.421, 23.6601 to \
  514.421, 23.66 to \
  514.419, 23.66 to \
  514.419, 23.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 368 polygon from \
  514.434, 23.6701 to \
  514.435, 23.6701 to \
  514.435, 23.67 to \
  514.434, 23.67 to \
  514.434, 23.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 369 polygon from \
  514.448, 23.6801 to \
  514.45, 23.6801 to \
  514.45, 23.68 to \
  514.448, 23.68 to \
  514.448, 23.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 370 polygon from \
  514.462, 23.6901 to \
  514.464, 23.6901 to \
  514.464, 23.69 to \
  514.462, 23.69 to \
  514.462, 23.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 371 polygon from \
  514.477, 23.7001 to \
  514.479, 23.7001 to \
  514.479, 23.7 to \
  514.477, 23.7 to \
  514.477, 23.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 372 polygon from \
  514.491, 23.7101 to \
  514.493, 23.7101 to \
  514.493, 23.71 to \
  514.491, 23.71 to \
  514.491, 23.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 373 polygon from \
  514.506, 23.7201 to \
  514.508, 23.7201 to \
  514.508, 23.72 to \
  514.506, 23.72 to \
  514.506, 23.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 374 polygon from \
  514.52, 23.7301 to \
  514.522, 23.7301 to \
  514.522, 23.73 to \
  514.52, 23.73 to \
  514.52, 23.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 375 polygon from \
  514.535, 23.7401 to \
  514.537, 23.7401 to \
  514.537, 23.74 to \
  514.535, 23.74 to \
  514.535, 23.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 376 polygon from \
  514.549, 23.7501 to \
  514.551, 23.7501 to \
  514.551, 23.75 to \
  514.549, 23.75 to \
  514.549, 23.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 377 polygon from \
  514.564, 23.7601 to \
  514.566, 23.7601 to \
  514.566, 23.76 to \
  514.564, 23.76 to \
  514.564, 23.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 378 polygon from \
  514.579, 23.7701 to \
  514.58, 23.7701 to \
  514.58, 23.77 to \
  514.579, 23.77 to \
  514.579, 23.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 379 polygon from \
  514.593, 23.7801 to \
  514.595, 23.7801 to \
  514.595, 23.78 to \
  514.593, 23.78 to \
  514.593, 23.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 380 polygon from \
  514.608, 23.7901 to \
  514.61, 23.7901 to \
  514.61, 23.79 to \
  514.608, 23.79 to \
  514.608, 23.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 381 polygon from \
  514.622, 23.8001 to \
  514.624, 23.8001 to \
  514.624, 23.8 to \
  514.622, 23.8 to \
  514.622, 23.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 382 polygon from \
  514.637, 23.8101 to \
  514.639, 23.8101 to \
  514.639, 23.81 to \
  514.637, 23.81 to \
  514.637, 23.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 383 polygon from \
  514.652, 23.8201 to \
  514.654, 23.8201 to \
  514.654, 23.82 to \
  514.652, 23.82 to \
  514.652, 23.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 384 polygon from \
  514.666, 23.8301 to \
  514.668, 23.8301 to \
  514.668, 23.83 to \
  514.666, 23.83 to \
  514.666, 23.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 385 polygon from \
  514.681, 23.8401 to \
  514.683, 23.8401 to \
  514.683, 23.84 to \
  514.681, 23.84 to \
  514.681, 23.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 386 polygon from \
  514.696, 23.8501 to \
  514.698, 23.8501 to \
  514.698, 23.85 to \
  514.696, 23.85 to \
  514.696, 23.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 387 polygon from \
  514.71, 23.8601 to \
  514.712, 23.8601 to \
  514.712, 23.86 to \
  514.71, 23.86 to \
  514.71, 23.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 388 polygon from \
  514.725, 23.8701 to \
  514.727, 23.8701 to \
  514.727, 23.87 to \
  514.725, 23.87 to \
  514.725, 23.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 389 polygon from \
  514.74, 23.8801 to \
  514.742, 23.8801 to \
  514.742, 23.88 to \
  514.74, 23.88 to \
  514.74, 23.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 390 polygon from \
  514.755, 23.8901 to \
  514.756, 23.8901 to \
  514.756, 23.89 to \
  514.755, 23.89 to \
  514.755, 23.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 391 polygon from \
  514.769, 23.9001 to \
  514.771, 23.9001 to \
  514.771, 23.9 to \
  514.769, 23.9 to \
  514.769, 23.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 392 polygon from \
  514.784, 23.9101 to \
  514.786, 23.9101 to \
  514.786, 23.91 to \
  514.784, 23.91 to \
  514.784, 23.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 393 polygon from \
  514.799, 23.9201 to \
  514.801, 23.9201 to \
  514.801, 23.92 to \
  514.799, 23.92 to \
  514.799, 23.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 394 polygon from \
  514.814, 23.9301 to \
  514.816, 23.9301 to \
  514.816, 23.93 to \
  514.814, 23.93 to \
  514.814, 23.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 395 polygon from \
  514.829, 23.9401 to \
  514.83, 23.9401 to \
  514.83, 23.94 to \
  514.829, 23.94 to \
  514.829, 23.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 396 polygon from \
  514.843, 23.9501 to \
  514.845, 23.9501 to \
  514.845, 23.95 to \
  514.843, 23.95 to \
  514.843, 23.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 397 polygon from \
  514.858, 23.9601 to \
  514.86, 23.9601 to \
  514.86, 23.96 to \
  514.858, 23.96 to \
  514.858, 23.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 398 polygon from \
  514.873, 23.9701 to \
  514.875, 23.9701 to \
  514.875, 23.97 to \
  514.873, 23.97 to \
  514.873, 23.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 399 polygon from \
  514.888, 23.9801 to \
  514.89, 23.9801 to \
  514.89, 23.98 to \
  514.888, 23.98 to \
  514.888, 23.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 400 polygon from \
  514.903, 23.9901 to \
  514.905, 23.9901 to \
  514.905, 23.99 to \
  514.903, 23.99 to \
  514.903, 23.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 401 polygon from \
  514.918, 24.0001 to \
  514.92, 24.0001 to \
  514.92, 24 to \
  514.918, 24 to \
  514.918, 24.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 402 polygon from \
  514.933, 24.0101 to \
  514.935, 24.0101 to \
  514.935, 24.01 to \
  514.933, 24.01 to \
  514.933, 24.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 403 polygon from \
  514.948, 24.0201 to \
  514.95, 24.0201 to \
  514.95, 24.02 to \
  514.948, 24.02 to \
  514.948, 24.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 404 polygon from \
  514.963, 24.0301 to \
  514.965, 24.0301 to \
  514.965, 24.03 to \
  514.963, 24.03 to \
  514.963, 24.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 405 polygon from \
  514.978, 24.0401 to \
  514.979, 24.0401 to \
  514.979, 24.04 to \
  514.978, 24.04 to \
  514.978, 24.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 406 polygon from \
  514.993, 24.0501 to \
  514.994, 24.0501 to \
  514.994, 24.05 to \
  514.993, 24.05 to \
  514.993, 24.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 407 polygon from \
  515.008, 24.0601 to \
  515.009, 24.0601 to \
  515.009, 24.06 to \
  515.008, 24.06 to \
  515.008, 24.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 408 polygon from \
  515.023, 24.0701 to \
  515.024, 24.0701 to \
  515.024, 24.07 to \
  515.023, 24.07 to \
  515.023, 24.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 409 polygon from \
  515.038, 24.0801 to \
  515.04, 24.0801 to \
  515.04, 24.08 to \
  515.038, 24.08 to \
  515.038, 24.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 410 polygon from \
  515.053, 24.0901 to \
  515.055, 24.0901 to \
  515.055, 24.09 to \
  515.053, 24.09 to \
  515.053, 24.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 411 polygon from \
  515.068, 24.1001 to \
  515.07, 24.1001 to \
  515.07, 24.1 to \
  515.068, 24.1 to \
  515.068, 24.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 412 polygon from \
  515.083, 24.1101 to \
  515.085, 24.1101 to \
  515.085, 24.11 to \
  515.083, 24.11 to \
  515.083, 24.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 413 polygon from \
  515.098, 24.1201 to \
  515.1, 24.1201 to \
  515.1, 24.12 to \
  515.098, 24.12 to \
  515.098, 24.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 414 polygon from \
  515.113, 24.1301 to \
  515.115, 24.1301 to \
  515.115, 24.13 to \
  515.113, 24.13 to \
  515.113, 24.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 415 polygon from \
  515.128, 24.1401 to \
  515.13, 24.1401 to \
  515.13, 24.14 to \
  515.128, 24.14 to \
  515.128, 24.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 416 polygon from \
  515.143, 24.1501 to \
  515.145, 24.1501 to \
  515.145, 24.15 to \
  515.143, 24.15 to \
  515.143, 24.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 417 polygon from \
  515.158, 24.1601 to \
  515.16, 24.1601 to \
  515.16, 24.16 to \
  515.158, 24.16 to \
  515.158, 24.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 418 polygon from \
  515.174, 24.1701 to \
  515.175, 24.1701 to \
  515.175, 24.17 to \
  515.174, 24.17 to \
  515.174, 24.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 419 polygon from \
  515.189, 24.1801 to \
  515.191, 24.1801 to \
  515.191, 24.18 to \
  515.189, 24.18 to \
  515.189, 24.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 420 polygon from \
  515.204, 24.1901 to \
  515.206, 24.1901 to \
  515.206, 24.19 to \
  515.204, 24.19 to \
  515.204, 24.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 421 polygon from \
  515.219, 24.2001 to \
  515.221, 24.2001 to \
  515.221, 24.2 to \
  515.219, 24.2 to \
  515.219, 24.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 422 polygon from \
  515.234, 24.2101 to \
  515.236, 24.2101 to \
  515.236, 24.21 to \
  515.234, 24.21 to \
  515.234, 24.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 423 polygon from \
  515.25, 24.2201 to \
  515.252, 24.2201 to \
  515.252, 24.22 to \
  515.25, 24.22 to \
  515.25, 24.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 424 polygon from \
  515.265, 24.2301 to \
  515.267, 24.2301 to \
  515.267, 24.23 to \
  515.265, 24.23 to \
  515.265, 24.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 425 polygon from \
  515.28, 24.2401 to \
  515.282, 24.2401 to \
  515.282, 24.24 to \
  515.28, 24.24 to \
  515.28, 24.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 426 polygon from \
  515.295, 24.2501 to \
  515.297, 24.2501 to \
  515.297, 24.25 to \
  515.295, 24.25 to \
  515.295, 24.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 427 polygon from \
  515.311, 24.2601 to \
  515.313, 24.2601 to \
  515.313, 24.26 to \
  515.311, 24.26 to \
  515.311, 24.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 428 polygon from \
  515.326, 24.2701 to \
  515.328, 24.2701 to \
  515.328, 24.27 to \
  515.326, 24.27 to \
  515.326, 24.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 429 polygon from \
  515.341, 24.2801 to \
  515.343, 24.2801 to \
  515.343, 24.28 to \
  515.341, 24.28 to \
  515.341, 24.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 430 polygon from \
  515.357, 24.2901 to \
  515.359, 24.2901 to \
  515.359, 24.29 to \
  515.357, 24.29 to \
  515.357, 24.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 431 polygon from \
  515.372, 24.3001 to \
  515.374, 24.3001 to \
  515.374, 24.3 to \
  515.372, 24.3 to \
  515.372, 24.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 432 polygon from \
  515.387, 24.3101 to \
  515.389, 24.3101 to \
  515.389, 24.31 to \
  515.387, 24.31 to \
  515.387, 24.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 433 polygon from \
  515.403, 24.3201 to \
  515.405, 24.3201 to \
  515.405, 24.32 to \
  515.403, 24.32 to \
  515.403, 24.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 434 polygon from \
  515.418, 24.3301 to \
  515.42, 24.3301 to \
  515.42, 24.33 to \
  515.418, 24.33 to \
  515.418, 24.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 435 polygon from \
  515.434, 24.3401 to \
  515.436, 24.3401 to \
  515.436, 24.34 to \
  515.434, 24.34 to \
  515.434, 24.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 436 polygon from \
  515.449, 24.3501 to \
  515.451, 24.3501 to \
  515.451, 24.35 to \
  515.449, 24.35 to \
  515.449, 24.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 437 polygon from \
  515.465, 24.3601 to \
  515.467, 24.3601 to \
  515.467, 24.36 to \
  515.465, 24.36 to \
  515.465, 24.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 438 polygon from \
  515.48, 24.3701 to \
  515.482, 24.3701 to \
  515.482, 24.37 to \
  515.48, 24.37 to \
  515.48, 24.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 439 polygon from \
  515.496, 24.3801 to \
  515.498, 24.3801 to \
  515.498, 24.38 to \
  515.496, 24.38 to \
  515.496, 24.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 440 polygon from \
  515.511, 24.3901 to \
  515.513, 24.3901 to \
  515.513, 24.39 to \
  515.511, 24.39 to \
  515.511, 24.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 441 polygon from \
  515.527, 24.4001 to \
  515.529, 24.4001 to \
  515.529, 24.4 to \
  515.527, 24.4 to \
  515.527, 24.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 442 polygon from \
  515.542, 24.4101 to \
  515.544, 24.4101 to \
  515.544, 24.41 to \
  515.542, 24.41 to \
  515.542, 24.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 443 polygon from \
  515.558, 24.4201 to \
  515.56, 24.4201 to \
  515.56, 24.42 to \
  515.558, 24.42 to \
  515.558, 24.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 444 polygon from \
  515.573, 24.4301 to \
  515.575, 24.4301 to \
  515.575, 24.43 to \
  515.573, 24.43 to \
  515.573, 24.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 445 polygon from \
  515.589, 24.4401 to \
  515.591, 24.4401 to \
  515.591, 24.44 to \
  515.589, 24.44 to \
  515.589, 24.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 446 polygon from \
  515.604, 24.4501 to \
  515.606, 24.4501 to \
  515.606, 24.45 to \
  515.604, 24.45 to \
  515.604, 24.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 447 polygon from \
  515.62, 24.4601 to \
  515.622, 24.4601 to \
  515.622, 24.46 to \
  515.62, 24.46 to \
  515.62, 24.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 448 polygon from \
  515.636, 24.4701 to \
  515.638, 24.4701 to \
  515.638, 24.47 to \
  515.636, 24.47 to \
  515.636, 24.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 449 polygon from \
  515.651, 24.4801 to \
  515.653, 24.4801 to \
  515.653, 24.48 to \
  515.651, 24.48 to \
  515.651, 24.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 450 polygon from \
  515.667, 24.4901 to \
  515.669, 24.4901 to \
  515.669, 24.49 to \
  515.667, 24.49 to \
  515.667, 24.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 451 polygon from \
  515.683, 24.5001 to \
  515.685, 24.5001 to \
  515.685, 24.5 to \
  515.683, 24.5 to \
  515.683, 24.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 452 polygon from \
  515.698, 24.5101 to \
  515.7, 24.5101 to \
  515.7, 24.51 to \
  515.698, 24.51 to \
  515.698, 24.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 453 polygon from \
  515.714, 24.5201 to \
  515.716, 24.5201 to \
  515.716, 24.52 to \
  515.714, 24.52 to \
  515.714, 24.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 454 polygon from \
  515.73, 24.5301 to \
  515.732, 24.5301 to \
  515.732, 24.53 to \
  515.73, 24.53 to \
  515.73, 24.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 455 polygon from \
  515.745, 24.5401 to \
  515.747, 24.5401 to \
  515.747, 24.54 to \
  515.745, 24.54 to \
  515.745, 24.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 456 polygon from \
  515.761, 24.5501 to \
  515.763, 24.5501 to \
  515.763, 24.55 to \
  515.761, 24.55 to \
  515.761, 24.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 457 polygon from \
  515.777, 24.5601 to \
  515.779, 24.5601 to \
  515.779, 24.56 to \
  515.777, 24.56 to \
  515.777, 24.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 458 polygon from \
  515.793, 24.5701 to \
  515.795, 24.5701 to \
  515.795, 24.57 to \
  515.793, 24.57 to \
  515.793, 24.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 459 polygon from \
  515.809, 24.5801 to \
  515.811, 24.5801 to \
  515.811, 24.58 to \
  515.809, 24.58 to \
  515.809, 24.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 460 polygon from \
  515.824, 24.5901 to \
  515.826, 24.5901 to \
  515.826, 24.59 to \
  515.824, 24.59 to \
  515.824, 24.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 461 polygon from \
  515.84, 24.6001 to \
  515.842, 24.6001 to \
  515.842, 24.6 to \
  515.84, 24.6 to \
  515.84, 24.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 462 polygon from \
  515.856, 24.6101 to \
  515.858, 24.6101 to \
  515.858, 24.61 to \
  515.856, 24.61 to \
  515.856, 24.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 463 polygon from \
  515.872, 24.6201 to \
  515.874, 24.6201 to \
  515.874, 24.62 to \
  515.872, 24.62 to \
  515.872, 24.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 464 polygon from \
  515.888, 24.6301 to \
  515.89, 24.6301 to \
  515.89, 24.63 to \
  515.888, 24.63 to \
  515.888, 24.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 465 polygon from \
  515.904, 24.6401 to \
  515.906, 24.6401 to \
  515.906, 24.64 to \
  515.904, 24.64 to \
  515.904, 24.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 466 polygon from \
  515.92, 24.6501 to \
  515.922, 24.6501 to \
  515.922, 24.65 to \
  515.92, 24.65 to \
  515.92, 24.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 467 polygon from \
  515.936, 24.6601 to \
  515.938, 24.6601 to \
  515.938, 24.66 to \
  515.936, 24.66 to \
  515.936, 24.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 468 polygon from \
  515.952, 24.6701 to \
  515.954, 24.6701 to \
  515.954, 24.67 to \
  515.952, 24.67 to \
  515.952, 24.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 469 polygon from \
  515.967, 24.6801 to \
  515.969, 24.6801 to \
  515.969, 24.68 to \
  515.967, 24.68 to \
  515.967, 24.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 470 polygon from \
  515.983, 24.6901 to \
  515.985, 24.6901 to \
  515.985, 24.69 to \
  515.983, 24.69 to \
  515.983, 24.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 471 polygon from \
  515.999, 24.7001 to \
  516.001, 24.7001 to \
  516.001, 24.7 to \
  515.999, 24.7 to \
  515.999, 24.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 472 polygon from \
  516.015, 24.7101 to \
  516.017, 24.7101 to \
  516.017, 24.71 to \
  516.015, 24.71 to \
  516.015, 24.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 473 polygon from \
  516.031, 24.7201 to \
  516.033, 24.7201 to \
  516.033, 24.72 to \
  516.031, 24.72 to \
  516.031, 24.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 474 polygon from \
  516.048, 24.7301 to \
  516.05, 24.7301 to \
  516.05, 24.73 to \
  516.048, 24.73 to \
  516.048, 24.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 475 polygon from \
  516.064, 24.7401 to \
  516.066, 24.7401 to \
  516.066, 24.74 to \
  516.064, 24.74 to \
  516.064, 24.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 476 polygon from \
  516.08, 24.7501 to \
  516.082, 24.7501 to \
  516.082, 24.75 to \
  516.08, 24.75 to \
  516.08, 24.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 477 polygon from \
  516.096, 24.7601 to \
  516.098, 24.7601 to \
  516.098, 24.76 to \
  516.096, 24.76 to \
  516.096, 24.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 478 polygon from \
  516.112, 24.7701 to \
  516.114, 24.7701 to \
  516.114, 24.77 to \
  516.112, 24.77 to \
  516.112, 24.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 479 polygon from \
  516.128, 24.7801 to \
  516.13, 24.7801 to \
  516.13, 24.78 to \
  516.128, 24.78 to \
  516.128, 24.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 480 polygon from \
  516.144, 24.7901 to \
  516.146, 24.7901 to \
  516.146, 24.79 to \
  516.144, 24.79 to \
  516.144, 24.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 481 polygon from \
  516.16, 24.8001 to \
  516.162, 24.8001 to \
  516.162, 24.8 to \
  516.16, 24.8 to \
  516.16, 24.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 482 polygon from \
  516.176, 24.8101 to \
  516.178, 24.8101 to \
  516.178, 24.81 to \
  516.176, 24.81 to \
  516.176, 24.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 483 polygon from \
  516.193, 24.8201 to \
  516.195, 24.8201 to \
  516.195, 24.82 to \
  516.193, 24.82 to \
  516.193, 24.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 484 polygon from \
  516.209, 24.8301 to \
  516.211, 24.8301 to \
  516.211, 24.83 to \
  516.209, 24.83 to \
  516.209, 24.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 485 polygon from \
  516.225, 24.8401 to \
  516.227, 24.8401 to \
  516.227, 24.84 to \
  516.225, 24.84 to \
  516.225, 24.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 486 polygon from \
  516.241, 24.8501 to \
  516.243, 24.8501 to \
  516.243, 24.85 to \
  516.241, 24.85 to \
  516.241, 24.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 487 polygon from \
  516.257, 24.8601 to \
  516.26, 24.8601 to \
  516.26, 24.86 to \
  516.257, 24.86 to \
  516.257, 24.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 488 polygon from \
  516.274, 24.8701 to \
  516.276, 24.8701 to \
  516.276, 24.87 to \
  516.274, 24.87 to \
  516.274, 24.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 489 polygon from \
  516.29, 24.8801 to \
  516.292, 24.8801 to \
  516.292, 24.88 to \
  516.29, 24.88 to \
  516.29, 24.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 490 polygon from \
  516.306, 24.8901 to \
  516.308, 24.8901 to \
  516.308, 24.89 to \
  516.306, 24.89 to \
  516.306, 24.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 491 polygon from \
  516.323, 24.9001 to \
  516.325, 24.9001 to \
  516.325, 24.9 to \
  516.323, 24.9 to \
  516.323, 24.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 492 polygon from \
  516.339, 24.9101 to \
  516.341, 24.9101 to \
  516.341, 24.91 to \
  516.339, 24.91 to \
  516.339, 24.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 493 polygon from \
  516.355, 24.9201 to \
  516.357, 24.9201 to \
  516.357, 24.92 to \
  516.355, 24.92 to \
  516.355, 24.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 494 polygon from \
  516.372, 24.9301 to \
  516.374, 24.9301 to \
  516.374, 24.93 to \
  516.372, 24.93 to \
  516.372, 24.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 495 polygon from \
  516.388, 24.9401 to \
  516.39, 24.9401 to \
  516.39, 24.94 to \
  516.388, 24.94 to \
  516.388, 24.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 496 polygon from \
  516.404, 24.9501 to \
  516.407, 24.9501 to \
  516.407, 24.95 to \
  516.404, 24.95 to \
  516.404, 24.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 497 polygon from \
  516.421, 24.9601 to \
  516.423, 24.9601 to \
  516.423, 24.96 to \
  516.421, 24.96 to \
  516.421, 24.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 498 polygon from \
  516.437, 24.9701 to \
  516.439, 24.9701 to \
  516.439, 24.97 to \
  516.437, 24.97 to \
  516.437, 24.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 499 polygon from \
  516.454, 24.9801 to \
  516.456, 24.9801 to \
  516.456, 24.98 to \
  516.454, 24.98 to \
  516.454, 24.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 500 polygon from \
  516.47, 24.9901 to \
  516.472, 24.9901 to \
  516.472, 24.99 to \
  516.47, 24.99 to \
  516.47, 24.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 501 polygon from \
  516.487, 25.0001 to \
  516.489, 25.0001 to \
  516.489, 25 to \
  516.487, 25 to \
  516.487, 25.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 502 polygon from \
  516.503, 25.0101 to \
  516.505, 25.0101 to \
  516.505, 25.01 to \
  516.503, 25.01 to \
  516.503, 25.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 503 polygon from \
  516.52, 25.0201 to \
  516.522, 25.0201 to \
  516.522, 25.02 to \
  516.52, 25.02 to \
  516.52, 25.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 504 polygon from \
  516.536, 25.0301 to \
  516.538, 25.0301 to \
  516.538, 25.03 to \
  516.536, 25.03 to \
  516.536, 25.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 505 polygon from \
  516.553, 25.0401 to \
  516.555, 25.0401 to \
  516.555, 25.04 to \
  516.553, 25.04 to \
  516.553, 25.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 506 polygon from \
  516.569, 25.0501 to \
  516.571, 25.0501 to \
  516.571, 25.05 to \
  516.569, 25.05 to \
  516.569, 25.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 507 polygon from \
  516.586, 25.0601 to \
  516.588, 25.0601 to \
  516.588, 25.06 to \
  516.586, 25.06 to \
  516.586, 25.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 508 polygon from \
  516.602, 25.0701 to \
  516.605, 25.0701 to \
  516.605, 25.07 to \
  516.602, 25.07 to \
  516.602, 25.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 509 polygon from \
  516.619, 25.0801 to \
  516.621, 25.0801 to \
  516.621, 25.08 to \
  516.619, 25.08 to \
  516.619, 25.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 510 polygon from \
  516.636, 25.0901 to \
  516.638, 25.0901 to \
  516.638, 25.09 to \
  516.636, 25.09 to \
  516.636, 25.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 511 polygon from \
  516.652, 25.1001 to \
  516.654, 25.1001 to \
  516.654, 25.1 to \
  516.652, 25.1 to \
  516.652, 25.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 512 polygon from \
  516.669, 25.1101 to \
  516.671, 25.1101 to \
  516.671, 25.11 to \
  516.669, 25.11 to \
  516.669, 25.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 513 polygon from \
  516.686, 25.1201 to \
  516.688, 25.1201 to \
  516.688, 25.12 to \
  516.686, 25.12 to \
  516.686, 25.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 514 polygon from \
  516.702, 25.1301 to \
  516.704, 25.1301 to \
  516.704, 25.13 to \
  516.702, 25.13 to \
  516.702, 25.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 515 polygon from \
  516.719, 25.1401 to \
  516.721, 25.1401 to \
  516.721, 25.14 to \
  516.719, 25.14 to \
  516.719, 25.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 516 polygon from \
  516.736, 25.1501 to \
  516.738, 25.1501 to \
  516.738, 25.15 to \
  516.736, 25.15 to \
  516.736, 25.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 517 polygon from \
  516.753, 25.1601 to \
  516.755, 25.1601 to \
  516.755, 25.16 to \
  516.753, 25.16 to \
  516.753, 25.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 518 polygon from \
  516.769, 25.1701 to \
  516.771, 25.1701 to \
  516.771, 25.17 to \
  516.769, 25.17 to \
  516.769, 25.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 519 polygon from \
  516.786, 25.1801 to \
  516.788, 25.1801 to \
  516.788, 25.18 to \
  516.786, 25.18 to \
  516.786, 25.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 520 polygon from \
  516.803, 25.1901 to \
  516.805, 25.1901 to \
  516.805, 25.19 to \
  516.803, 25.19 to \
  516.803, 25.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 521 polygon from \
  516.82, 25.2001 to \
  516.822, 25.2001 to \
  516.822, 25.2 to \
  516.82, 25.2 to \
  516.82, 25.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 522 polygon from \
  516.837, 25.2101 to \
  516.839, 25.2101 to \
  516.839, 25.21 to \
  516.837, 25.21 to \
  516.837, 25.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 523 polygon from \
  516.853, 25.2201 to \
  516.856, 25.2201 to \
  516.856, 25.22 to \
  516.853, 25.22 to \
  516.853, 25.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 524 polygon from \
  516.87, 25.2301 to \
  516.872, 25.2301 to \
  516.872, 25.23 to \
  516.87, 25.23 to \
  516.87, 25.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 525 polygon from \
  516.887, 25.2401 to \
  516.889, 25.2401 to \
  516.889, 25.24 to \
  516.887, 25.24 to \
  516.887, 25.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 526 polygon from \
  516.904, 25.2501 to \
  516.906, 25.2501 to \
  516.906, 25.25 to \
  516.904, 25.25 to \
  516.904, 25.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 527 polygon from \
  516.921, 25.2601 to \
  516.923, 25.2601 to \
  516.923, 25.26 to \
  516.921, 25.26 to \
  516.921, 25.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 528 polygon from \
  516.938, 25.2701 to \
  516.94, 25.2701 to \
  516.94, 25.27 to \
  516.938, 25.27 to \
  516.938, 25.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 529 polygon from \
  516.955, 25.2801 to \
  516.957, 25.2801 to \
  516.957, 25.28 to \
  516.955, 25.28 to \
  516.955, 25.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 530 polygon from \
  516.972, 25.2901 to \
  516.974, 25.2901 to \
  516.974, 25.29 to \
  516.972, 25.29 to \
  516.972, 25.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 531 polygon from \
  516.989, 25.3001 to \
  516.991, 25.3001 to \
  516.991, 25.3 to \
  516.989, 25.3 to \
  516.989, 25.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 532 polygon from \
  517.006, 25.3101 to \
  517.008, 25.3101 to \
  517.008, 25.31 to \
  517.006, 25.31 to \
  517.006, 25.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 533 polygon from \
  517.023, 25.3201 to \
  517.025, 25.3201 to \
  517.025, 25.32 to \
  517.023, 25.32 to \
  517.023, 25.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 534 polygon from \
  517.04, 25.3301 to \
  517.042, 25.3301 to \
  517.042, 25.33 to \
  517.04, 25.33 to \
  517.04, 25.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 535 polygon from \
  517.057, 25.3401 to \
  517.059, 25.3401 to \
  517.059, 25.34 to \
  517.057, 25.34 to \
  517.057, 25.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 536 polygon from \
  517.074, 25.3501 to \
  517.076, 25.3501 to \
  517.076, 25.35 to \
  517.074, 25.35 to \
  517.074, 25.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 537 polygon from \
  517.091, 25.3601 to \
  517.093, 25.3601 to \
  517.093, 25.36 to \
  517.091, 25.36 to \
  517.091, 25.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 538 polygon from \
  517.108, 25.3701 to \
  517.11, 25.3701 to \
  517.11, 25.37 to \
  517.108, 25.37 to \
  517.108, 25.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 539 polygon from \
  517.125, 25.3801 to \
  517.127, 25.3801 to \
  517.127, 25.38 to \
  517.125, 25.38 to \
  517.125, 25.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 540 polygon from \
  517.142, 25.3901 to \
  517.144, 25.3901 to \
  517.144, 25.39 to \
  517.142, 25.39 to \
  517.142, 25.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 541 polygon from \
  517.159, 25.4001 to \
  517.162, 25.4001 to \
  517.162, 25.4 to \
  517.159, 25.4 to \
  517.159, 25.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 542 polygon from \
  517.177, 25.4101 to \
  517.179, 25.4101 to \
  517.179, 25.41 to \
  517.177, 25.41 to \
  517.177, 25.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 543 polygon from \
  517.194, 25.4201 to \
  517.196, 25.4201 to \
  517.196, 25.42 to \
  517.194, 25.42 to \
  517.194, 25.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 544 polygon from \
  517.211, 25.4301 to \
  517.213, 25.4301 to \
  517.213, 25.43 to \
  517.211, 25.43 to \
  517.211, 25.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 545 polygon from \
  517.228, 25.4401 to \
  517.23, 25.4401 to \
  517.23, 25.44 to \
  517.228, 25.44 to \
  517.228, 25.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 546 polygon from \
  517.245, 25.4501 to \
  517.248, 25.4501 to \
  517.248, 25.45 to \
  517.245, 25.45 to \
  517.245, 25.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 547 polygon from \
  517.263, 25.4601 to \
  517.265, 25.4601 to \
  517.265, 25.46 to \
  517.263, 25.46 to \
  517.263, 25.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 548 polygon from \
  517.28, 25.4701 to \
  517.282, 25.4701 to \
  517.282, 25.47 to \
  517.28, 25.47 to \
  517.28, 25.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 549 polygon from \
  517.297, 25.4801 to \
  517.299, 25.4801 to \
  517.299, 25.48 to \
  517.297, 25.48 to \
  517.297, 25.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 550 polygon from \
  517.315, 25.4901 to \
  517.317, 25.4901 to \
  517.317, 25.49 to \
  517.315, 25.49 to \
  517.315, 25.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 551 polygon from \
  517.332, 25.5001 to \
  517.334, 25.5001 to \
  517.334, 25.5 to \
  517.332, 25.5 to \
  517.332, 25.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 552 polygon from \
  517.349, 25.5101 to \
  517.351, 25.5101 to \
  517.351, 25.51 to \
  517.349, 25.51 to \
  517.349, 25.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 553 polygon from \
  517.367, 25.5201 to \
  517.369, 25.5201 to \
  517.369, 25.52 to \
  517.367, 25.52 to \
  517.367, 25.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 554 polygon from \
  517.384, 25.5301 to \
  517.386, 25.5301 to \
  517.386, 25.53 to \
  517.384, 25.53 to \
  517.384, 25.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 555 polygon from \
  517.401, 25.5401 to \
  517.404, 25.5401 to \
  517.404, 25.54 to \
  517.401, 25.54 to \
  517.401, 25.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 556 polygon from \
  517.419, 25.5501 to \
  517.421, 25.5501 to \
  517.421, 25.55 to \
  517.419, 25.55 to \
  517.419, 25.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 557 polygon from \
  517.436, 25.5601 to \
  517.438, 25.5601 to \
  517.438, 25.56 to \
  517.436, 25.56 to \
  517.436, 25.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 558 polygon from \
  517.454, 25.5701 to \
  517.456, 25.5701 to \
  517.456, 25.57 to \
  517.454, 25.57 to \
  517.454, 25.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 559 polygon from \
  517.471, 25.5801 to \
  517.473, 25.5801 to \
  517.473, 25.58 to \
  517.471, 25.58 to \
  517.471, 25.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 560 polygon from \
  517.489, 25.5901 to \
  517.491, 25.5901 to \
  517.491, 25.59 to \
  517.489, 25.59 to \
  517.489, 25.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 561 polygon from \
  517.506, 25.6001 to \
  517.508, 25.6001 to \
  517.508, 25.6 to \
  517.506, 25.6 to \
  517.506, 25.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 562 polygon from \
  517.524, 25.6101 to \
  517.526, 25.6101 to \
  517.526, 25.61 to \
  517.524, 25.61 to \
  517.524, 25.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 563 polygon from \
  517.541, 25.6201 to \
  517.543, 25.6201 to \
  517.543, 25.62 to \
  517.541, 25.62 to \
  517.541, 25.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 564 polygon from \
  517.559, 25.6301 to \
  517.561, 25.6301 to \
  517.561, 25.63 to \
  517.559, 25.63 to \
  517.559, 25.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 565 polygon from \
  517.576, 25.6401 to \
  517.579, 25.6401 to \
  517.579, 25.64 to \
  517.576, 25.64 to \
  517.576, 25.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 566 polygon from \
  517.594, 25.6501 to \
  517.596, 25.6501 to \
  517.596, 25.65 to \
  517.594, 25.65 to \
  517.594, 25.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 567 polygon from \
  517.611, 25.6601 to \
  517.614, 25.6601 to \
  517.614, 25.66 to \
  517.611, 25.66 to \
  517.611, 25.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 568 polygon from \
  517.629, 25.6701 to \
  517.631, 25.6701 to \
  517.631, 25.67 to \
  517.629, 25.67 to \
  517.629, 25.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 569 polygon from \
  517.647, 25.6801 to \
  517.649, 25.6801 to \
  517.649, 25.68 to \
  517.647, 25.68 to \
  517.647, 25.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 570 polygon from \
  517.664, 25.6901 to \
  517.667, 25.6901 to \
  517.667, 25.69 to \
  517.664, 25.69 to \
  517.664, 25.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 571 polygon from \
  517.682, 25.7001 to \
  517.684, 25.7001 to \
  517.684, 25.7 to \
  517.682, 25.7 to \
  517.682, 25.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 572 polygon from \
  517.7, 25.7101 to \
  517.702, 25.7101 to \
  517.702, 25.71 to \
  517.7, 25.71 to \
  517.7, 25.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 573 polygon from \
  517.717, 25.7201 to \
  517.72, 25.7201 to \
  517.72, 25.72 to \
  517.717, 25.72 to \
  517.717, 25.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 574 polygon from \
  517.735, 25.7301 to \
  517.737, 25.7301 to \
  517.737, 25.73 to \
  517.735, 25.73 to \
  517.735, 25.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 575 polygon from \
  517.753, 25.7401 to \
  517.755, 25.7401 to \
  517.755, 25.74 to \
  517.753, 25.74 to \
  517.753, 25.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 576 polygon from \
  517.771, 25.7501 to \
  517.773, 25.7501 to \
  517.773, 25.75 to \
  517.771, 25.75 to \
  517.771, 25.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 577 polygon from \
  517.788, 25.7601 to \
  517.791, 25.7601 to \
  517.791, 25.76 to \
  517.788, 25.76 to \
  517.788, 25.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 578 polygon from \
  517.806, 25.7701 to \
  517.809, 25.7701 to \
  517.809, 25.77 to \
  517.806, 25.77 to \
  517.806, 25.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 579 polygon from \
  517.824, 25.7801 to \
  517.826, 25.7801 to \
  517.826, 25.78 to \
  517.824, 25.78 to \
  517.824, 25.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 580 polygon from \
  517.842, 25.7901 to \
  517.844, 25.7901 to \
  517.844, 25.79 to \
  517.842, 25.79 to \
  517.842, 25.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 581 polygon from \
  517.86, 25.8001 to \
  517.862, 25.8001 to \
  517.862, 25.8 to \
  517.86, 25.8 to \
  517.86, 25.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 582 polygon from \
  517.878, 25.8101 to \
  517.88, 25.8101 to \
  517.88, 25.81 to \
  517.878, 25.81 to \
  517.878, 25.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 583 polygon from \
  517.896, 25.8201 to \
  517.898, 25.8201 to \
  517.898, 25.82 to \
  517.896, 25.82 to \
  517.896, 25.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 584 polygon from \
  517.913, 25.8301 to \
  517.916, 25.8301 to \
  517.916, 25.83 to \
  517.913, 25.83 to \
  517.913, 25.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 585 polygon from \
  517.931, 25.8401 to \
  517.934, 25.8401 to \
  517.934, 25.84 to \
  517.931, 25.84 to \
  517.931, 25.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 586 polygon from \
  517.949, 25.8501 to \
  517.952, 25.8501 to \
  517.952, 25.85 to \
  517.949, 25.85 to \
  517.949, 25.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 587 polygon from \
  517.967, 25.8601 to \
  517.97, 25.8601 to \
  517.97, 25.86 to \
  517.967, 25.86 to \
  517.967, 25.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 588 polygon from \
  517.985, 25.8701 to \
  517.987, 25.8701 to \
  517.987, 25.87 to \
  517.985, 25.87 to \
  517.985, 25.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 589 polygon from \
  518.003, 25.8801 to \
  518.005, 25.8801 to \
  518.005, 25.88 to \
  518.003, 25.88 to \
  518.003, 25.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 590 polygon from \
  518.021, 25.8901 to \
  518.023, 25.8901 to \
  518.023, 25.89 to \
  518.021, 25.89 to \
  518.021, 25.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 591 polygon from \
  518.039, 25.9001 to \
  518.042, 25.9001 to \
  518.042, 25.9 to \
  518.039, 25.9 to \
  518.039, 25.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 592 polygon from \
  518.057, 25.9101 to \
  518.06, 25.9101 to \
  518.06, 25.91 to \
  518.057, 25.91 to \
  518.057, 25.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 593 polygon from \
  518.075, 25.9201 to \
  518.078, 25.9201 to \
  518.078, 25.92 to \
  518.075, 25.92 to \
  518.075, 25.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 594 polygon from \
  518.093, 25.9301 to \
  518.096, 25.9301 to \
  518.096, 25.93 to \
  518.093, 25.93 to \
  518.093, 25.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 595 polygon from \
  518.112, 25.9401 to \
  518.114, 25.9401 to \
  518.114, 25.94 to \
  518.112, 25.94 to \
  518.112, 25.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 596 polygon from \
  518.13, 25.9501 to \
  518.132, 25.9501 to \
  518.132, 25.95 to \
  518.13, 25.95 to \
  518.13, 25.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 597 polygon from \
  518.148, 25.9601 to \
  518.15, 25.9601 to \
  518.15, 25.96 to \
  518.148, 25.96 to \
  518.148, 25.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 598 polygon from \
  518.166, 25.9701 to \
  518.168, 25.9701 to \
  518.168, 25.97 to \
  518.166, 25.97 to \
  518.166, 25.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 599 polygon from \
  518.184, 25.9801 to \
  518.186, 25.9801 to \
  518.186, 25.98 to \
  518.184, 25.98 to \
  518.184, 25.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 600 polygon from \
  518.202, 25.9901 to \
  518.205, 25.9901 to \
  518.205, 25.99 to \
  518.202, 25.99 to \
  518.202, 25.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 601 polygon from \
  518.221, 26.0001 to \
  518.223, 26.0001 to \
  518.223, 26 to \
  518.221, 26 to \
  518.221, 26.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 602 polygon from \
  518.239, 26.0101 to \
  518.241, 26.0101 to \
  518.241, 26.01 to \
  518.239, 26.01 to \
  518.239, 26.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 603 polygon from \
  518.257, 26.0201 to \
  518.259, 26.0201 to \
  518.259, 26.02 to \
  518.257, 26.02 to \
  518.257, 26.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 604 polygon from \
  518.275, 26.0301 to \
  518.278, 26.0301 to \
  518.278, 26.03 to \
  518.275, 26.03 to \
  518.275, 26.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 605 polygon from \
  518.294, 26.0401 to \
  518.296, 26.0401 to \
  518.296, 26.04 to \
  518.294, 26.04 to \
  518.294, 26.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 606 polygon from \
  518.312, 26.0501 to \
  518.314, 26.0501 to \
  518.314, 26.05 to \
  518.312, 26.05 to \
  518.312, 26.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 607 polygon from \
  518.33, 26.0601 to \
  518.333, 26.0601 to \
  518.333, 26.06 to \
  518.33, 26.06 to \
  518.33, 26.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 608 polygon from \
  518.349, 26.0701 to \
  518.351, 26.0701 to \
  518.351, 26.07 to \
  518.349, 26.07 to \
  518.349, 26.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 609 polygon from \
  518.367, 26.0801 to \
  518.369, 26.0801 to \
  518.369, 26.08 to \
  518.367, 26.08 to \
  518.367, 26.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 610 polygon from \
  518.385, 26.0901 to \
  518.388, 26.0901 to \
  518.388, 26.09 to \
  518.385, 26.09 to \
  518.385, 26.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 611 polygon from \
  518.404, 26.1001 to \
  518.406, 26.1001 to \
  518.406, 26.1 to \
  518.404, 26.1 to \
  518.404, 26.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 612 polygon from \
  518.422, 26.1101 to \
  518.424, 26.1101 to \
  518.424, 26.11 to \
  518.422, 26.11 to \
  518.422, 26.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 613 polygon from \
  518.44, 26.1201 to \
  518.443, 26.1201 to \
  518.443, 26.12 to \
  518.44, 26.12 to \
  518.44, 26.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 614 polygon from \
  518.459, 26.1301 to \
  518.461, 26.1301 to \
  518.461, 26.13 to \
  518.459, 26.13 to \
  518.459, 26.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 615 polygon from \
  518.477, 26.1401 to \
  518.48, 26.1401 to \
  518.48, 26.14 to \
  518.477, 26.14 to \
  518.477, 26.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 616 polygon from \
  518.496, 26.1501 to \
  518.498, 26.1501 to \
  518.498, 26.15 to \
  518.496, 26.15 to \
  518.496, 26.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 617 polygon from \
  518.514, 26.1601 to \
  518.517, 26.1601 to \
  518.517, 26.16 to \
  518.514, 26.16 to \
  518.514, 26.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 618 polygon from \
  518.533, 26.1701 to \
  518.535, 26.1701 to \
  518.535, 26.17 to \
  518.533, 26.17 to \
  518.533, 26.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 619 polygon from \
  518.551, 26.1801 to \
  518.554, 26.1801 to \
  518.554, 26.18 to \
  518.551, 26.18 to \
  518.551, 26.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 620 polygon from \
  518.57, 26.1901 to \
  518.572, 26.1901 to \
  518.572, 26.19 to \
  518.57, 26.19 to \
  518.57, 26.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 621 polygon from \
  518.589, 26.2001 to \
  518.591, 26.2001 to \
  518.591, 26.2 to \
  518.589, 26.2 to \
  518.589, 26.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 622 polygon from \
  518.607, 26.2101 to \
  518.61, 26.2101 to \
  518.61, 26.21 to \
  518.607, 26.21 to \
  518.607, 26.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 623 polygon from \
  518.626, 26.2201 to \
  518.628, 26.2201 to \
  518.628, 26.22 to \
  518.626, 26.22 to \
  518.626, 26.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 624 polygon from \
  518.644, 26.2301 to \
  518.647, 26.2301 to \
  518.647, 26.23 to \
  518.644, 26.23 to \
  518.644, 26.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 625 polygon from \
  518.663, 26.2401 to \
  518.665, 26.2401 to \
  518.665, 26.24 to \
  518.663, 26.24 to \
  518.663, 26.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 626 polygon from \
  518.682, 26.2501 to \
  518.684, 26.2501 to \
  518.684, 26.25 to \
  518.682, 26.25 to \
  518.682, 26.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 627 polygon from \
  518.7, 26.2601 to \
  518.703, 26.2601 to \
  518.703, 26.26 to \
  518.7, 26.26 to \
  518.7, 26.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 628 polygon from \
  518.719, 26.2701 to \
  518.722, 26.2701 to \
  518.722, 26.27 to \
  518.719, 26.27 to \
  518.719, 26.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 629 polygon from \
  518.738, 26.2801 to \
  518.74, 26.2801 to \
  518.74, 26.28 to \
  518.738, 26.28 to \
  518.738, 26.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 630 polygon from \
  518.757, 26.2901 to \
  518.759, 26.2901 to \
  518.759, 26.29 to \
  518.757, 26.29 to \
  518.757, 26.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 631 polygon from \
  518.775, 26.3001 to \
  518.778, 26.3001 to \
  518.778, 26.3 to \
  518.775, 26.3 to \
  518.775, 26.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 632 polygon from \
  518.794, 26.3101 to \
  518.797, 26.3101 to \
  518.797, 26.31 to \
  518.794, 26.31 to \
  518.794, 26.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 633 polygon from \
  518.813, 26.3201 to \
  518.815, 26.3201 to \
  518.815, 26.32 to \
  518.813, 26.32 to \
  518.813, 26.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 634 polygon from \
  518.832, 26.3301 to \
  518.834, 26.3301 to \
  518.834, 26.33 to \
  518.832, 26.33 to \
  518.832, 26.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 635 polygon from \
  518.851, 26.3401 to \
  518.853, 26.3401 to \
  518.853, 26.34 to \
  518.851, 26.34 to \
  518.851, 26.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 636 polygon from \
  518.87, 26.3501 to \
  518.872, 26.3501 to \
  518.872, 26.35 to \
  518.87, 26.35 to \
  518.87, 26.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 637 polygon from \
  518.888, 26.3601 to \
  518.891, 26.3601 to \
  518.891, 26.36 to \
  518.888, 26.36 to \
  518.888, 26.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 638 polygon from \
  518.907, 26.3701 to \
  518.91, 26.3701 to \
  518.91, 26.37 to \
  518.907, 26.37 to \
  518.907, 26.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 639 polygon from \
  518.926, 26.3801 to \
  518.929, 26.3801 to \
  518.929, 26.38 to \
  518.926, 26.38 to \
  518.926, 26.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 640 polygon from \
  518.945, 26.3901 to \
  518.948, 26.3901 to \
  518.948, 26.39 to \
  518.945, 26.39 to \
  518.945, 26.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 641 polygon from \
  518.964, 26.4001 to \
  518.967, 26.4001 to \
  518.967, 26.4 to \
  518.964, 26.4 to \
  518.964, 26.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 642 polygon from \
  518.983, 26.4101 to \
  518.985, 26.4101 to \
  518.985, 26.41 to \
  518.983, 26.41 to \
  518.983, 26.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 643 polygon from \
  519.002, 26.4201 to \
  519.004, 26.4201 to \
  519.004, 26.42 to \
  519.002, 26.42 to \
  519.002, 26.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 644 polygon from \
  519.021, 26.4301 to \
  519.023, 26.4301 to \
  519.023, 26.43 to \
  519.021, 26.43 to \
  519.021, 26.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 645 polygon from \
  519.04, 26.4401 to \
  519.043, 26.4401 to \
  519.043, 26.44 to \
  519.04, 26.44 to \
  519.04, 26.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 646 polygon from \
  519.059, 26.4501 to \
  519.062, 26.4501 to \
  519.062, 26.45 to \
  519.059, 26.45 to \
  519.059, 26.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 647 polygon from \
  519.078, 26.4601 to \
  519.081, 26.4601 to \
  519.081, 26.46 to \
  519.078, 26.46 to \
  519.078, 26.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 648 polygon from \
  519.097, 26.4701 to \
  519.1, 26.4701 to \
  519.1, 26.47 to \
  519.097, 26.47 to \
  519.097, 26.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 649 polygon from \
  519.116, 26.4801 to \
  519.119, 26.4801 to \
  519.119, 26.48 to \
  519.116, 26.48 to \
  519.116, 26.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 650 polygon from \
  519.136, 26.4901 to \
  519.138, 26.4901 to \
  519.138, 26.49 to \
  519.136, 26.49 to \
  519.136, 26.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 651 polygon from \
  519.155, 26.5001 to \
  519.157, 26.5001 to \
  519.157, 26.5 to \
  519.155, 26.5 to \
  519.155, 26.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 652 polygon from \
  519.174, 26.5101 to \
  519.176, 26.5101 to \
  519.176, 26.51 to \
  519.174, 26.51 to \
  519.174, 26.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 653 polygon from \
  519.193, 26.5201 to \
  519.195, 26.5201 to \
  519.195, 26.52 to \
  519.193, 26.52 to \
  519.193, 26.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 654 polygon from \
  519.212, 26.5301 to \
  519.215, 26.5301 to \
  519.215, 26.53 to \
  519.212, 26.53 to \
  519.212, 26.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 655 polygon from \
  519.231, 26.5401 to \
  519.234, 26.5401 to \
  519.234, 26.54 to \
  519.231, 26.54 to \
  519.231, 26.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 656 polygon from \
  519.251, 26.5501 to \
  519.253, 26.5501 to \
  519.253, 26.55 to \
  519.251, 26.55 to \
  519.251, 26.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 657 polygon from \
  519.27, 26.5601 to \
  519.272, 26.5601 to \
  519.272, 26.56 to \
  519.27, 26.56 to \
  519.27, 26.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 658 polygon from \
  519.289, 26.5701 to \
  519.292, 26.5701 to \
  519.292, 26.57 to \
  519.289, 26.57 to \
  519.289, 26.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 659 polygon from \
  519.309, 26.5801 to \
  519.311, 26.5801 to \
  519.311, 26.58 to \
  519.309, 26.58 to \
  519.309, 26.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 660 polygon from \
  519.328, 26.5901 to \
  519.33, 26.5901 to \
  519.33, 26.59 to \
  519.328, 26.59 to \
  519.328, 26.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 661 polygon from \
  519.347, 26.6001 to \
  519.35, 26.6001 to \
  519.35, 26.6 to \
  519.347, 26.6 to \
  519.347, 26.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 662 polygon from \
  519.367, 26.6101 to \
  519.369, 26.6101 to \
  519.369, 26.61 to \
  519.367, 26.61 to \
  519.367, 26.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 663 polygon from \
  519.386, 26.6201 to \
  519.388, 26.6201 to \
  519.388, 26.62 to \
  519.386, 26.62 to \
  519.386, 26.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 664 polygon from \
  519.405, 26.6301 to \
  519.408, 26.6301 to \
  519.408, 26.63 to \
  519.405, 26.63 to \
  519.405, 26.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 665 polygon from \
  519.425, 26.6401 to \
  519.427, 26.6401 to \
  519.427, 26.64 to \
  519.425, 26.64 to \
  519.425, 26.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 666 polygon from \
  519.444, 26.6501 to \
  519.447, 26.6501 to \
  519.447, 26.65 to \
  519.444, 26.65 to \
  519.444, 26.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 667 polygon from \
  519.464, 26.6601 to \
  519.466, 26.6601 to \
  519.466, 26.66 to \
  519.464, 26.66 to \
  519.464, 26.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 668 polygon from \
  519.483, 26.6701 to \
  519.486, 26.6701 to \
  519.486, 26.67 to \
  519.483, 26.67 to \
  519.483, 26.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 669 polygon from \
  519.503, 26.6801 to \
  519.505, 26.6801 to \
  519.505, 26.68 to \
  519.503, 26.68 to \
  519.503, 26.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 670 polygon from \
  519.522, 26.6901 to \
  519.525, 26.6901 to \
  519.525, 26.69 to \
  519.522, 26.69 to \
  519.522, 26.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 671 polygon from \
  519.542, 26.7001 to \
  519.544, 26.7001 to \
  519.544, 26.7 to \
  519.542, 26.7 to \
  519.542, 26.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 672 polygon from \
  519.561, 26.7101 to \
  519.564, 26.7101 to \
  519.564, 26.71 to \
  519.561, 26.71 to \
  519.561, 26.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 673 polygon from \
  519.581, 26.7201 to \
  519.583, 26.7201 to \
  519.583, 26.72 to \
  519.581, 26.72 to \
  519.581, 26.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 674 polygon from \
  519.6, 26.7301 to \
  519.603, 26.7301 to \
  519.603, 26.73 to \
  519.6, 26.73 to \
  519.6, 26.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 675 polygon from \
  519.62, 26.7401 to \
  519.622, 26.7401 to \
  519.622, 26.74 to \
  519.62, 26.74 to \
  519.62, 26.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 676 polygon from \
  519.64, 26.7501 to \
  519.642, 26.7501 to \
  519.642, 26.75 to \
  519.64, 26.75 to \
  519.64, 26.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 677 polygon from \
  519.659, 26.7601 to \
  519.662, 26.7601 to \
  519.662, 26.76 to \
  519.659, 26.76 to \
  519.659, 26.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 678 polygon from \
  519.679, 26.7701 to \
  519.681, 26.7701 to \
  519.681, 26.77 to \
  519.679, 26.77 to \
  519.679, 26.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 679 polygon from \
  519.699, 26.7801 to \
  519.701, 26.7801 to \
  519.701, 26.78 to \
  519.699, 26.78 to \
  519.699, 26.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 680 polygon from \
  519.718, 26.7901 to \
  519.721, 26.7901 to \
  519.721, 26.79 to \
  519.718, 26.79 to \
  519.718, 26.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 681 polygon from \
  519.738, 26.8001 to \
  519.741, 26.8001 to \
  519.741, 26.8 to \
  519.738, 26.8 to \
  519.738, 26.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 682 polygon from \
  519.758, 26.8101 to \
  519.76, 26.8101 to \
  519.76, 26.81 to \
  519.758, 26.81 to \
  519.758, 26.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 683 polygon from \
  519.778, 26.8201 to \
  519.78, 26.8201 to \
  519.78, 26.82 to \
  519.778, 26.82 to \
  519.778, 26.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 684 polygon from \
  519.797, 26.8301 to \
  519.8, 26.8301 to \
  519.8, 26.83 to \
  519.797, 26.83 to \
  519.797, 26.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 685 polygon from \
  519.817, 26.8401 to \
  519.82, 26.8401 to \
  519.82, 26.84 to \
  519.817, 26.84 to \
  519.817, 26.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 686 polygon from \
  519.837, 26.8501 to \
  519.839, 26.8501 to \
  519.839, 26.85 to \
  519.837, 26.85 to \
  519.837, 26.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 687 polygon from \
  519.857, 26.8601 to \
  519.859, 26.8601 to \
  519.859, 26.86 to \
  519.857, 26.86 to \
  519.857, 26.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 688 polygon from \
  519.877, 26.8701 to \
  519.879, 26.8701 to \
  519.879, 26.87 to \
  519.877, 26.87 to \
  519.877, 26.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 689 polygon from \
  519.897, 26.8801 to \
  519.899, 26.8801 to \
  519.899, 26.88 to \
  519.897, 26.88 to \
  519.897, 26.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 690 polygon from \
  519.916, 26.8901 to \
  519.919, 26.8901 to \
  519.919, 26.89 to \
  519.916, 26.89 to \
  519.916, 26.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 691 polygon from \
  519.936, 26.9001 to \
  519.939, 26.9001 to \
  519.939, 26.9 to \
  519.936, 26.9 to \
  519.936, 26.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 692 polygon from \
  519.956, 26.9101 to \
  519.959, 26.9101 to \
  519.959, 26.91 to \
  519.956, 26.91 to \
  519.956, 26.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 693 polygon from \
  519.976, 26.9201 to \
  519.979, 26.9201 to \
  519.979, 26.92 to \
  519.976, 26.92 to \
  519.976, 26.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 694 polygon from \
  519.996, 26.9301 to \
  519.999, 26.9301 to \
  519.999, 26.93 to \
  519.996, 26.93 to \
  519.996, 26.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 695 polygon from \
  520.016, 26.9401 to \
  520.019, 26.9401 to \
  520.019, 26.94 to \
  520.016, 26.94 to \
  520.016, 26.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 696 polygon from \
  520.036, 26.9501 to \
  520.039, 26.9501 to \
  520.039, 26.95 to \
  520.036, 26.95 to \
  520.036, 26.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 697 polygon from \
  520.056, 26.9601 to \
  520.059, 26.9601 to \
  520.059, 26.96 to \
  520.056, 26.96 to \
  520.056, 26.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 698 polygon from \
  520.076, 26.9701 to \
  520.079, 26.9701 to \
  520.079, 26.97 to \
  520.076, 26.97 to \
  520.076, 26.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 699 polygon from \
  520.097, 26.9801 to \
  520.099, 26.9801 to \
  520.099, 26.98 to \
  520.097, 26.98 to \
  520.097, 26.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 700 polygon from \
  520.117, 26.9901 to \
  520.119, 26.9901 to \
  520.119, 26.99 to \
  520.117, 26.99 to \
  520.117, 26.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 701 polygon from \
  520.137, 27.0001 to \
  520.139, 27.0001 to \
  520.139, 27 to \
  520.137, 27 to \
  520.137, 27.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 702 polygon from \
  520.157, 27.0101 to \
  520.159, 27.0101 to \
  520.159, 27.01 to \
  520.157, 27.01 to \
  520.157, 27.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 703 polygon from \
  520.177, 27.0201 to \
  520.18, 27.0201 to \
  520.18, 27.02 to \
  520.177, 27.02 to \
  520.177, 27.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 704 polygon from \
  520.197, 27.0301 to \
  520.2, 27.0301 to \
  520.2, 27.03 to \
  520.197, 27.03 to \
  520.197, 27.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 705 polygon from \
  520.217, 27.0401 to \
  520.22, 27.0401 to \
  520.22, 27.04 to \
  520.217, 27.04 to \
  520.217, 27.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 706 polygon from \
  520.238, 27.0501 to \
  520.24, 27.0501 to \
  520.24, 27.05 to \
  520.238, 27.05 to \
  520.238, 27.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 707 polygon from \
  520.258, 27.0601 to \
  520.26, 27.0601 to \
  520.26, 27.06 to \
  520.258, 27.06 to \
  520.258, 27.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 708 polygon from \
  520.278, 27.0701 to \
  520.281, 27.0701 to \
  520.281, 27.07 to \
  520.278, 27.07 to \
  520.278, 27.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 709 polygon from \
  520.298, 27.0801 to \
  520.301, 27.0801 to \
  520.301, 27.08 to \
  520.298, 27.08 to \
  520.298, 27.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 710 polygon from \
  520.319, 27.0901 to \
  520.321, 27.0901 to \
  520.321, 27.09 to \
  520.319, 27.09 to \
  520.319, 27.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 711 polygon from \
  520.339, 27.1001 to \
  520.342, 27.1001 to \
  520.342, 27.1 to \
  520.339, 27.1 to \
  520.339, 27.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 712 polygon from \
  520.359, 27.1101 to \
  520.362, 27.1101 to \
  520.362, 27.11 to \
  520.359, 27.11 to \
  520.359, 27.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 713 polygon from \
  520.38, 27.1201 to \
  520.382, 27.1201 to \
  520.382, 27.12 to \
  520.38, 27.12 to \
  520.38, 27.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 714 polygon from \
  520.4, 27.1301 to \
  520.403, 27.1301 to \
  520.403, 27.13 to \
  520.4, 27.13 to \
  520.4, 27.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 715 polygon from \
  520.421, 27.1401 to \
  520.423, 27.1401 to \
  520.423, 27.14 to \
  520.421, 27.14 to \
  520.421, 27.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 716 polygon from \
  520.441, 27.1501 to \
  520.444, 27.1501 to \
  520.444, 27.15 to \
  520.441, 27.15 to \
  520.441, 27.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 717 polygon from \
  520.462, 27.1601 to \
  520.464, 27.1601 to \
  520.464, 27.16 to \
  520.462, 27.16 to \
  520.462, 27.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 718 polygon from \
  520.482, 27.1701 to \
  520.485, 27.1701 to \
  520.485, 27.17 to \
  520.482, 27.17 to \
  520.482, 27.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 719 polygon from \
  520.502, 27.1801 to \
  520.505, 27.1801 to \
  520.505, 27.18 to \
  520.502, 27.18 to \
  520.502, 27.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 720 polygon from \
  520.523, 27.1901 to \
  520.526, 27.1901 to \
  520.526, 27.19 to \
  520.523, 27.19 to \
  520.523, 27.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 721 polygon from \
  520.544, 27.2001 to \
  520.546, 27.2001 to \
  520.546, 27.2 to \
  520.544, 27.2 to \
  520.544, 27.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 722 polygon from \
  520.564, 27.2101 to \
  520.567, 27.2101 to \
  520.567, 27.21 to \
  520.564, 27.21 to \
  520.564, 27.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 723 polygon from \
  520.585, 27.2201 to \
  520.587, 27.2201 to \
  520.587, 27.22 to \
  520.585, 27.22 to \
  520.585, 27.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 724 polygon from \
  520.605, 27.2301 to \
  520.608, 27.2301 to \
  520.608, 27.23 to \
  520.605, 27.23 to \
  520.605, 27.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 725 polygon from \
  520.626, 27.2401 to \
  520.628, 27.2401 to \
  520.628, 27.24 to \
  520.626, 27.24 to \
  520.626, 27.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 726 polygon from \
  520.647, 27.2501 to \
  520.649, 27.2501 to \
  520.649, 27.25 to \
  520.647, 27.25 to \
  520.647, 27.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 727 polygon from \
  520.667, 27.2601 to \
  520.67, 27.2601 to \
  520.67, 27.26 to \
  520.667, 27.26 to \
  520.667, 27.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 728 polygon from \
  520.688, 27.2701 to \
  520.69, 27.2701 to \
  520.69, 27.27 to \
  520.688, 27.27 to \
  520.688, 27.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 729 polygon from \
  520.709, 27.2801 to \
  520.711, 27.2801 to \
  520.711, 27.28 to \
  520.709, 27.28 to \
  520.709, 27.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 730 polygon from \
  520.729, 27.2901 to \
  520.732, 27.2901 to \
  520.732, 27.29 to \
  520.729, 27.29 to \
  520.729, 27.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 731 polygon from \
  520.75, 27.3001 to \
  520.753, 27.3001 to \
  520.753, 27.3 to \
  520.75, 27.3 to \
  520.75, 27.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 732 polygon from \
  520.771, 27.3101 to \
  520.773, 27.3101 to \
  520.773, 27.31 to \
  520.771, 27.31 to \
  520.771, 27.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 733 polygon from \
  520.792, 27.3201 to \
  520.794, 27.3201 to \
  520.794, 27.32 to \
  520.792, 27.32 to \
  520.792, 27.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 734 polygon from \
  520.812, 27.3301 to \
  520.815, 27.3301 to \
  520.815, 27.33 to \
  520.812, 27.33 to \
  520.812, 27.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 735 polygon from \
  520.833, 27.3401 to \
  520.836, 27.3401 to \
  520.836, 27.34 to \
  520.833, 27.34 to \
  520.833, 27.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 736 polygon from \
  520.854, 27.3501 to \
  520.857, 27.3501 to \
  520.857, 27.35 to \
  520.854, 27.35 to \
  520.854, 27.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 737 polygon from \
  520.875, 27.3601 to \
  520.878, 27.3601 to \
  520.878, 27.36 to \
  520.875, 27.36 to \
  520.875, 27.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 738 polygon from \
  520.896, 27.3701 to \
  520.898, 27.3701 to \
  520.898, 27.37 to \
  520.896, 27.37 to \
  520.896, 27.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 739 polygon from \
  520.917, 27.3801 to \
  520.919, 27.3801 to \
  520.919, 27.38 to \
  520.917, 27.38 to \
  520.917, 27.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 740 polygon from \
  520.938, 27.3901 to \
  520.94, 27.3901 to \
  520.94, 27.39 to \
  520.938, 27.39 to \
  520.938, 27.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 741 polygon from \
  520.959, 27.4001 to \
  520.961, 27.4001 to \
  520.961, 27.4 to \
  520.959, 27.4 to \
  520.959, 27.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 742 polygon from \
  520.98, 27.4101 to \
  520.982, 27.4101 to \
  520.982, 27.41 to \
  520.98, 27.41 to \
  520.98, 27.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 743 polygon from \
  521, 27.4201 to \
  521.003, 27.4201 to \
  521.003, 27.42 to \
  521, 27.42 to \
  521, 27.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 744 polygon from \
  521.022, 27.4301 to \
  521.024, 27.4301 to \
  521.024, 27.43 to \
  521.022, 27.43 to \
  521.022, 27.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 745 polygon from \
  521.043, 27.4401 to \
  521.045, 27.4401 to \
  521.045, 27.44 to \
  521.043, 27.44 to \
  521.043, 27.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 746 polygon from \
  521.064, 27.4501 to \
  521.066, 27.4501 to \
  521.066, 27.45 to \
  521.064, 27.45 to \
  521.064, 27.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 747 polygon from \
  521.085, 27.4601 to \
  521.087, 27.4601 to \
  521.087, 27.46 to \
  521.085, 27.46 to \
  521.085, 27.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 748 polygon from \
  521.106, 27.4701 to \
  521.108, 27.4701 to \
  521.108, 27.47 to \
  521.106, 27.47 to \
  521.106, 27.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 749 polygon from \
  521.127, 27.4801 to \
  521.13, 27.4801 to \
  521.13, 27.48 to \
  521.127, 27.48 to \
  521.127, 27.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 750 polygon from \
  521.148, 27.4901 to \
  521.151, 27.4901 to \
  521.151, 27.49 to \
  521.148, 27.49 to \
  521.148, 27.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 751 polygon from \
  521.169, 27.5001 to \
  521.172, 27.5001 to \
  521.172, 27.5 to \
  521.169, 27.5 to \
  521.169, 27.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 752 polygon from \
  521.19, 27.5101 to \
  521.193, 27.5101 to \
  521.193, 27.51 to \
  521.19, 27.51 to \
  521.19, 27.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 753 polygon from \
  521.212, 27.5201 to \
  521.214, 27.5201 to \
  521.214, 27.52 to \
  521.212, 27.52 to \
  521.212, 27.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 754 polygon from \
  521.233, 27.5301 to \
  521.235, 27.5301 to \
  521.235, 27.53 to \
  521.233, 27.53 to \
  521.233, 27.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 755 polygon from \
  521.254, 27.5401 to \
  521.257, 27.5401 to \
  521.257, 27.54 to \
  521.254, 27.54 to \
  521.254, 27.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 756 polygon from \
  521.275, 27.5501 to \
  521.278, 27.5501 to \
  521.278, 27.55 to \
  521.275, 27.55 to \
  521.275, 27.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 757 polygon from \
  521.297, 27.5601 to \
  521.299, 27.5601 to \
  521.299, 27.56 to \
  521.297, 27.56 to \
  521.297, 27.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 758 polygon from \
  521.318, 27.5701 to \
  521.321, 27.5701 to \
  521.321, 27.57 to \
  521.318, 27.57 to \
  521.318, 27.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 759 polygon from \
  521.339, 27.5801 to \
  521.342, 27.5801 to \
  521.342, 27.58 to \
  521.339, 27.58 to \
  521.339, 27.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 760 polygon from \
  521.361, 27.5901 to \
  521.363, 27.5901 to \
  521.363, 27.59 to \
  521.361, 27.59 to \
  521.361, 27.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 761 polygon from \
  521.382, 27.6001 to \
  521.385, 27.6001 to \
  521.385, 27.6 to \
  521.382, 27.6 to \
  521.382, 27.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 762 polygon from \
  521.403, 27.6101 to \
  521.406, 27.6101 to \
  521.406, 27.61 to \
  521.403, 27.61 to \
  521.403, 27.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 763 polygon from \
  521.425, 27.6201 to \
  521.427, 27.6201 to \
  521.427, 27.62 to \
  521.425, 27.62 to \
  521.425, 27.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 764 polygon from \
  521.446, 27.6301 to \
  521.449, 27.6301 to \
  521.449, 27.63 to \
  521.446, 27.63 to \
  521.446, 27.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 765 polygon from \
  521.468, 27.6401 to \
  521.47, 27.6401 to \
  521.47, 27.64 to \
  521.468, 27.64 to \
  521.468, 27.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 766 polygon from \
  521.489, 27.6501 to \
  521.492, 27.6501 to \
  521.492, 27.65 to \
  521.489, 27.65 to \
  521.489, 27.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 767 polygon from \
  521.511, 27.6601 to \
  521.513, 27.6601 to \
  521.513, 27.66 to \
  521.511, 27.66 to \
  521.511, 27.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 768 polygon from \
  521.532, 27.6701 to \
  521.535, 27.6701 to \
  521.535, 27.67 to \
  521.532, 27.67 to \
  521.532, 27.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 769 polygon from \
  521.554, 27.6801 to \
  521.556, 27.6801 to \
  521.556, 27.68 to \
  521.554, 27.68 to \
  521.554, 27.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 770 polygon from \
  521.575, 27.6901 to \
  521.578, 27.6901 to \
  521.578, 27.69 to \
  521.575, 27.69 to \
  521.575, 27.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 771 polygon from \
  521.597, 27.7001 to \
  521.6, 27.7001 to \
  521.6, 27.7 to \
  521.597, 27.7 to \
  521.597, 27.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 772 polygon from \
  521.618, 27.7101 to \
  521.621, 27.7101 to \
  521.621, 27.71 to \
  521.618, 27.71 to \
  521.618, 27.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 773 polygon from \
  521.64, 27.7201 to \
  521.643, 27.7201 to \
  521.643, 27.72 to \
  521.64, 27.72 to \
  521.64, 27.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 774 polygon from \
  521.662, 27.7301 to \
  521.664, 27.7301 to \
  521.664, 27.73 to \
  521.662, 27.73 to \
  521.662, 27.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 775 polygon from \
  521.683, 27.7401 to \
  521.686, 27.7401 to \
  521.686, 27.74 to \
  521.683, 27.74 to \
  521.683, 27.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 776 polygon from \
  521.705, 27.7501 to \
  521.708, 27.7501 to \
  521.708, 27.75 to \
  521.705, 27.75 to \
  521.705, 27.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 777 polygon from \
  521.727, 27.7601 to \
  521.73, 27.7601 to \
  521.73, 27.76 to \
  521.727, 27.76 to \
  521.727, 27.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 778 polygon from \
  521.749, 27.7701 to \
  521.751, 27.7701 to \
  521.751, 27.77 to \
  521.749, 27.77 to \
  521.749, 27.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 779 polygon from \
  521.77, 27.7801 to \
  521.773, 27.7801 to \
  521.773, 27.78 to \
  521.77, 27.78 to \
  521.77, 27.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 780 polygon from \
  521.792, 27.7901 to \
  521.795, 27.7901 to \
  521.795, 27.79 to \
  521.792, 27.79 to \
  521.792, 27.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 781 polygon from \
  521.814, 27.8001 to \
  521.817, 27.8001 to \
  521.817, 27.8 to \
  521.814, 27.8 to \
  521.814, 27.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 782 polygon from \
  521.836, 27.8101 to \
  521.838, 27.8101 to \
  521.838, 27.81 to \
  521.836, 27.81 to \
  521.836, 27.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 783 polygon from \
  521.858, 27.8201 to \
  521.86, 27.8201 to \
  521.86, 27.82 to \
  521.858, 27.82 to \
  521.858, 27.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 784 polygon from \
  521.879, 27.8301 to \
  521.882, 27.8301 to \
  521.882, 27.83 to \
  521.879, 27.83 to \
  521.879, 27.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 785 polygon from \
  521.901, 27.8401 to \
  521.904, 27.8401 to \
  521.904, 27.84 to \
  521.901, 27.84 to \
  521.901, 27.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 786 polygon from \
  521.923, 27.8501 to \
  521.926, 27.8501 to \
  521.926, 27.85 to \
  521.923, 27.85 to \
  521.923, 27.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 787 polygon from \
  521.945, 27.8601 to \
  521.948, 27.8601 to \
  521.948, 27.86 to \
  521.945, 27.86 to \
  521.945, 27.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 788 polygon from \
  521.967, 27.8701 to \
  521.97, 27.8701 to \
  521.97, 27.87 to \
  521.967, 27.87 to \
  521.967, 27.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 789 polygon from \
  521.989, 27.8801 to \
  521.992, 27.8801 to \
  521.992, 27.88 to \
  521.989, 27.88 to \
  521.989, 27.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 790 polygon from \
  522.011, 27.8901 to \
  522.014, 27.8901 to \
  522.014, 27.89 to \
  522.011, 27.89 to \
  522.011, 27.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 791 polygon from \
  522.033, 27.9001 to \
  522.036, 27.9001 to \
  522.036, 27.9 to \
  522.033, 27.9 to \
  522.033, 27.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 792 polygon from \
  522.055, 27.9101 to \
  522.058, 27.9101 to \
  522.058, 27.91 to \
  522.055, 27.91 to \
  522.055, 27.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 793 polygon from \
  522.077, 27.9201 to \
  522.08, 27.9201 to \
  522.08, 27.92 to \
  522.077, 27.92 to \
  522.077, 27.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 794 polygon from \
  522.099, 27.9301 to \
  522.102, 27.9301 to \
  522.102, 27.93 to \
  522.099, 27.93 to \
  522.099, 27.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 795 polygon from \
  522.121, 27.9401 to \
  522.124, 27.9401 to \
  522.124, 27.94 to \
  522.121, 27.94 to \
  522.121, 27.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 796 polygon from \
  522.144, 27.9501 to \
  522.146, 27.9501 to \
  522.146, 27.95 to \
  522.144, 27.95 to \
  522.144, 27.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 797 polygon from \
  522.166, 27.9601 to \
  522.168, 27.9601 to \
  522.168, 27.96 to \
  522.166, 27.96 to \
  522.166, 27.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 798 polygon from \
  522.188, 27.9701 to \
  522.191, 27.9701 to \
  522.191, 27.97 to \
  522.188, 27.97 to \
  522.188, 27.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 799 polygon from \
  522.21, 27.9801 to \
  522.213, 27.9801 to \
  522.213, 27.98 to \
  522.21, 27.98 to \
  522.21, 27.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 800 polygon from \
  522.232, 27.9901 to \
  522.235, 27.9901 to \
  522.235, 27.99 to \
  522.232, 27.99 to \
  522.232, 27.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 801 polygon from \
  522.255, 28.0001 to \
  522.257, 28.0001 to \
  522.257, 28 to \
  522.255, 28 to \
  522.255, 28.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 802 polygon from \
  522.277, 28.0101 to \
  522.28, 28.0101 to \
  522.28, 28.01 to \
  522.277, 28.01 to \
  522.277, 28.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 803 polygon from \
  522.299, 28.0201 to \
  522.302, 28.0201 to \
  522.302, 28.02 to \
  522.299, 28.02 to \
  522.299, 28.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 804 polygon from \
  522.321, 28.0301 to \
  522.324, 28.0301 to \
  522.324, 28.03 to \
  522.321, 28.03 to \
  522.321, 28.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 805 polygon from \
  522.344, 28.0401 to \
  522.347, 28.0401 to \
  522.347, 28.04 to \
  522.344, 28.04 to \
  522.344, 28.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 806 polygon from \
  522.366, 28.0501 to \
  522.369, 28.0501 to \
  522.369, 28.05 to \
  522.366, 28.05 to \
  522.366, 28.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 807 polygon from \
  522.388, 28.0601 to \
  522.391, 28.0601 to \
  522.391, 28.06 to \
  522.388, 28.06 to \
  522.388, 28.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 808 polygon from \
  522.411, 28.0701 to \
  522.414, 28.0701 to \
  522.414, 28.07 to \
  522.411, 28.07 to \
  522.411, 28.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 809 polygon from \
  522.433, 28.0801 to \
  522.436, 28.0801 to \
  522.436, 28.08 to \
  522.433, 28.08 to \
  522.433, 28.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 810 polygon from \
  522.456, 28.0901 to \
  522.459, 28.0901 to \
  522.459, 28.09 to \
  522.456, 28.09 to \
  522.456, 28.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 811 polygon from \
  522.478, 28.1001 to \
  522.481, 28.1001 to \
  522.481, 28.1 to \
  522.478, 28.1 to \
  522.478, 28.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 812 polygon from \
  522.501, 28.1101 to \
  522.503, 28.1101 to \
  522.503, 28.11 to \
  522.501, 28.11 to \
  522.501, 28.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 813 polygon from \
  522.523, 28.1201 to \
  522.526, 28.1201 to \
  522.526, 28.12 to \
  522.523, 28.12 to \
  522.523, 28.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 814 polygon from \
  522.546, 28.1301 to \
  522.549, 28.1301 to \
  522.549, 28.13 to \
  522.546, 28.13 to \
  522.546, 28.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 815 polygon from \
  522.568, 28.1401 to \
  522.571, 28.1401 to \
  522.571, 28.14 to \
  522.568, 28.14 to \
  522.568, 28.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 816 polygon from \
  522.591, 28.1501 to \
  522.594, 28.1501 to \
  522.594, 28.15 to \
  522.591, 28.15 to \
  522.591, 28.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 817 polygon from \
  522.613, 28.1601 to \
  522.616, 28.1601 to \
  522.616, 28.16 to \
  522.613, 28.16 to \
  522.613, 28.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 818 polygon from \
  522.636, 28.1701 to \
  522.639, 28.1701 to \
  522.639, 28.17 to \
  522.636, 28.17 to \
  522.636, 28.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 819 polygon from \
  522.659, 28.1801 to \
  522.662, 28.1801 to \
  522.662, 28.18 to \
  522.659, 28.18 to \
  522.659, 28.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 820 polygon from \
  522.681, 28.1901 to \
  522.684, 28.1901 to \
  522.684, 28.19 to \
  522.681, 28.19 to \
  522.681, 28.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 821 polygon from \
  522.704, 28.2001 to \
  522.707, 28.2001 to \
  522.707, 28.2 to \
  522.704, 28.2 to \
  522.704, 28.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 822 polygon from \
  522.727, 28.2101 to \
  522.73, 28.2101 to \
  522.73, 28.21 to \
  522.727, 28.21 to \
  522.727, 28.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 823 polygon from \
  522.75, 28.2201 to \
  522.752, 28.2201 to \
  522.752, 28.22 to \
  522.75, 28.22 to \
  522.75, 28.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 824 polygon from \
  522.772, 28.2301 to \
  522.775, 28.2301 to \
  522.775, 28.23 to \
  522.772, 28.23 to \
  522.772, 28.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 825 polygon from \
  522.795, 28.2401 to \
  522.798, 28.2401 to \
  522.798, 28.24 to \
  522.795, 28.24 to \
  522.795, 28.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 826 polygon from \
  522.818, 28.2501 to \
  522.821, 28.2501 to \
  522.821, 28.25 to \
  522.818, 28.25 to \
  522.818, 28.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 827 polygon from \
  522.841, 28.2601 to \
  522.844, 28.2601 to \
  522.844, 28.26 to \
  522.841, 28.26 to \
  522.841, 28.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 828 polygon from \
  522.864, 28.2701 to \
  522.866, 28.2701 to \
  522.866, 28.27 to \
  522.864, 28.27 to \
  522.864, 28.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 829 polygon from \
  522.886, 28.2801 to \
  522.889, 28.2801 to \
  522.889, 28.28 to \
  522.886, 28.28 to \
  522.886, 28.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 830 polygon from \
  522.909, 28.2901 to \
  522.912, 28.2901 to \
  522.912, 28.29 to \
  522.909, 28.29 to \
  522.909, 28.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 831 polygon from \
  522.932, 28.3001 to \
  522.935, 28.3001 to \
  522.935, 28.3 to \
  522.932, 28.3 to \
  522.932, 28.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 832 polygon from \
  522.955, 28.3101 to \
  522.958, 28.3101 to \
  522.958, 28.31 to \
  522.955, 28.31 to \
  522.955, 28.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 833 polygon from \
  522.978, 28.3201 to \
  522.981, 28.3201 to \
  522.981, 28.32 to \
  522.978, 28.32 to \
  522.978, 28.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 834 polygon from \
  523.001, 28.3301 to \
  523.004, 28.3301 to \
  523.004, 28.33 to \
  523.001, 28.33 to \
  523.001, 28.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 835 polygon from \
  523.024, 28.3401 to \
  523.027, 28.3401 to \
  523.027, 28.34 to \
  523.024, 28.34 to \
  523.024, 28.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 836 polygon from \
  523.047, 28.3501 to \
  523.05, 28.3501 to \
  523.05, 28.35 to \
  523.047, 28.35 to \
  523.047, 28.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 837 polygon from \
  523.07, 28.3601 to \
  523.073, 28.3601 to \
  523.073, 28.36 to \
  523.07, 28.36 to \
  523.07, 28.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 838 polygon from \
  523.093, 28.3701 to \
  523.096, 28.3701 to \
  523.096, 28.37 to \
  523.093, 28.37 to \
  523.093, 28.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 839 polygon from \
  523.116, 28.3801 to \
  523.119, 28.3801 to \
  523.119, 28.38 to \
  523.116, 28.38 to \
  523.116, 28.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 840 polygon from \
  523.14, 28.3901 to \
  523.142, 28.3901 to \
  523.142, 28.39 to \
  523.14, 28.39 to \
  523.14, 28.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 841 polygon from \
  523.163, 28.4001 to \
  523.166, 28.4001 to \
  523.166, 28.4 to \
  523.163, 28.4 to \
  523.163, 28.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 842 polygon from \
  523.186, 28.4101 to \
  523.189, 28.4101 to \
  523.189, 28.41 to \
  523.186, 28.41 to \
  523.186, 28.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 843 polygon from \
  523.209, 28.4201 to \
  523.212, 28.4201 to \
  523.212, 28.42 to \
  523.209, 28.42 to \
  523.209, 28.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 844 polygon from \
  523.232, 28.4301 to \
  523.235, 28.4301 to \
  523.235, 28.43 to \
  523.232, 28.43 to \
  523.232, 28.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 845 polygon from \
  523.256, 28.4401 to \
  523.258, 28.4401 to \
  523.258, 28.44 to \
  523.256, 28.44 to \
  523.256, 28.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 846 polygon from \
  523.279, 28.4501 to \
  523.282, 28.4501 to \
  523.282, 28.45 to \
  523.279, 28.45 to \
  523.279, 28.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 847 polygon from \
  523.302, 28.4601 to \
  523.305, 28.4601 to \
  523.305, 28.46 to \
  523.302, 28.46 to \
  523.302, 28.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 848 polygon from \
  523.325, 28.4701 to \
  523.328, 28.4701 to \
  523.328, 28.47 to \
  523.325, 28.47 to \
  523.325, 28.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 849 polygon from \
  523.349, 28.4801 to \
  523.352, 28.4801 to \
  523.352, 28.48 to \
  523.349, 28.48 to \
  523.349, 28.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 850 polygon from \
  523.372, 28.4901 to \
  523.375, 28.4901 to \
  523.375, 28.49 to \
  523.372, 28.49 to \
  523.372, 28.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 851 polygon from \
  523.395, 28.5001 to \
  523.398, 28.5001 to \
  523.398, 28.5 to \
  523.395, 28.5 to \
  523.395, 28.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 852 polygon from \
  523.419, 28.5101 to \
  523.422, 28.5101 to \
  523.422, 28.51 to \
  523.419, 28.51 to \
  523.419, 28.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 853 polygon from \
  523.442, 28.5201 to \
  523.445, 28.5201 to \
  523.445, 28.52 to \
  523.442, 28.52 to \
  523.442, 28.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 854 polygon from \
  523.466, 28.5301 to \
  523.469, 28.5301 to \
  523.469, 28.53 to \
  523.466, 28.53 to \
  523.466, 28.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 855 polygon from \
  523.489, 28.5401 to \
  523.492, 28.5401 to \
  523.492, 28.54 to \
  523.489, 28.54 to \
  523.489, 28.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 856 polygon from \
  523.513, 28.5501 to \
  523.516, 28.5501 to \
  523.516, 28.55 to \
  523.513, 28.55 to \
  523.513, 28.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 857 polygon from \
  523.536, 28.5601 to \
  523.539, 28.5601 to \
  523.539, 28.56 to \
  523.536, 28.56 to \
  523.536, 28.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 858 polygon from \
  523.56, 28.5701 to \
  523.563, 28.5701 to \
  523.563, 28.57 to \
  523.56, 28.57 to \
  523.56, 28.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 859 polygon from \
  523.583, 28.5801 to \
  523.586, 28.5801 to \
  523.586, 28.58 to \
  523.583, 28.58 to \
  523.583, 28.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 860 polygon from \
  523.607, 28.5901 to \
  523.61, 28.5901 to \
  523.61, 28.59 to \
  523.607, 28.59 to \
  523.607, 28.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 861 polygon from \
  523.631, 28.6001 to \
  523.634, 28.6001 to \
  523.634, 28.6 to \
  523.631, 28.6 to \
  523.631, 28.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 862 polygon from \
  523.654, 28.6101 to \
  523.657, 28.6101 to \
  523.657, 28.61 to \
  523.654, 28.61 to \
  523.654, 28.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 863 polygon from \
  523.678, 28.6201 to \
  523.681, 28.6201 to \
  523.681, 28.62 to \
  523.678, 28.62 to \
  523.678, 28.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 864 polygon from \
  523.702, 28.6301 to \
  523.705, 28.6301 to \
  523.705, 28.63 to \
  523.702, 28.63 to \
  523.702, 28.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 865 polygon from \
  523.725, 28.6401 to \
  523.728, 28.6401 to \
  523.728, 28.64 to \
  523.725, 28.64 to \
  523.725, 28.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 866 polygon from \
  523.749, 28.6501 to \
  523.752, 28.6501 to \
  523.752, 28.65 to \
  523.749, 28.65 to \
  523.749, 28.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 867 polygon from \
  523.773, 28.6601 to \
  523.776, 28.6601 to \
  523.776, 28.66 to \
  523.773, 28.66 to \
  523.773, 28.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 868 polygon from \
  523.797, 28.6701 to \
  523.8, 28.6701 to \
  523.8, 28.67 to \
  523.797, 28.67 to \
  523.797, 28.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 869 polygon from \
  523.82, 28.6801 to \
  523.823, 28.6801 to \
  523.823, 28.68 to \
  523.82, 28.68 to \
  523.82, 28.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 870 polygon from \
  523.844, 28.6901 to \
  523.847, 28.6901 to \
  523.847, 28.69 to \
  523.844, 28.69 to \
  523.844, 28.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 871 polygon from \
  523.868, 28.7001 to \
  523.871, 28.7001 to \
  523.871, 28.7 to \
  523.868, 28.7 to \
  523.868, 28.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 872 polygon from \
  523.892, 28.7101 to \
  523.895, 28.7101 to \
  523.895, 28.71 to \
  523.892, 28.71 to \
  523.892, 28.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 873 polygon from \
  523.916, 28.7201 to \
  523.919, 28.7201 to \
  523.919, 28.72 to \
  523.916, 28.72 to \
  523.916, 28.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 874 polygon from \
  523.94, 28.7301 to \
  523.943, 28.7301 to \
  523.943, 28.73 to \
  523.94, 28.73 to \
  523.94, 28.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 875 polygon from \
  523.964, 28.7401 to \
  523.967, 28.7401 to \
  523.967, 28.74 to \
  523.964, 28.74 to \
  523.964, 28.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 876 polygon from \
  523.988, 28.7501 to \
  523.991, 28.7501 to \
  523.991, 28.75 to \
  523.988, 28.75 to \
  523.988, 28.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 877 polygon from \
  524.012, 28.7601 to \
  524.015, 28.7601 to \
  524.015, 28.76 to \
  524.012, 28.76 to \
  524.012, 28.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 878 polygon from \
  524.036, 28.7701 to \
  524.039, 28.7701 to \
  524.039, 28.77 to \
  524.036, 28.77 to \
  524.036, 28.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 879 polygon from \
  524.06, 28.7801 to \
  524.063, 28.7801 to \
  524.063, 28.78 to \
  524.06, 28.78 to \
  524.06, 28.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 880 polygon from \
  524.084, 28.7901 to \
  524.087, 28.7901 to \
  524.087, 28.79 to \
  524.084, 28.79 to \
  524.084, 28.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 881 polygon from \
  524.108, 28.8001 to \
  524.111, 28.8001 to \
  524.111, 28.8 to \
  524.108, 28.8 to \
  524.108, 28.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 882 polygon from \
  524.132, 28.8101 to \
  524.135, 28.8101 to \
  524.135, 28.81 to \
  524.132, 28.81 to \
  524.132, 28.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 883 polygon from \
  524.156, 28.8201 to \
  524.159, 28.8201 to \
  524.159, 28.82 to \
  524.156, 28.82 to \
  524.156, 28.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 884 polygon from \
  524.18, 28.8301 to \
  524.183, 28.8301 to \
  524.183, 28.83 to \
  524.18, 28.83 to \
  524.18, 28.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 885 polygon from \
  524.205, 28.8401 to \
  524.208, 28.8401 to \
  524.208, 28.84 to \
  524.205, 28.84 to \
  524.205, 28.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 886 polygon from \
  524.229, 28.8501 to \
  524.232, 28.8501 to \
  524.232, 28.85 to \
  524.229, 28.85 to \
  524.229, 28.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 887 polygon from \
  524.253, 28.8601 to \
  524.256, 28.8601 to \
  524.256, 28.86 to \
  524.253, 28.86 to \
  524.253, 28.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 888 polygon from \
  524.277, 28.8701 to \
  524.28, 28.8701 to \
  524.28, 28.87 to \
  524.277, 28.87 to \
  524.277, 28.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 889 polygon from \
  524.302, 28.8801 to \
  524.305, 28.8801 to \
  524.305, 28.88 to \
  524.302, 28.88 to \
  524.302, 28.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 890 polygon from \
  524.326, 28.8901 to \
  524.329, 28.8901 to \
  524.329, 28.89 to \
  524.326, 28.89 to \
  524.326, 28.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 891 polygon from \
  524.35, 28.9001 to \
  524.353, 28.9001 to \
  524.353, 28.9 to \
  524.35, 28.9 to \
  524.35, 28.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 892 polygon from \
  524.375, 28.9101 to \
  524.378, 28.9101 to \
  524.378, 28.91 to \
  524.375, 28.91 to \
  524.375, 28.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 893 polygon from \
  524.399, 28.9201 to \
  524.402, 28.9201 to \
  524.402, 28.92 to \
  524.399, 28.92 to \
  524.399, 28.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 894 polygon from \
  524.423, 28.9301 to \
  524.427, 28.9301 to \
  524.427, 28.93 to \
  524.423, 28.93 to \
  524.423, 28.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 895 polygon from \
  524.448, 28.9401 to \
  524.451, 28.9401 to \
  524.451, 28.94 to \
  524.448, 28.94 to \
  524.448, 28.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 896 polygon from \
  524.472, 28.9501 to \
  524.475, 28.9501 to \
  524.475, 28.95 to \
  524.472, 28.95 to \
  524.472, 28.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 897 polygon from \
  524.497, 28.9601 to \
  524.5, 28.9601 to \
  524.5, 28.96 to \
  524.497, 28.96 to \
  524.497, 28.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 898 polygon from \
  524.521, 28.9701 to \
  524.524, 28.9701 to \
  524.524, 28.97 to \
  524.521, 28.97 to \
  524.521, 28.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 899 polygon from \
  524.546, 28.9801 to \
  524.549, 28.9801 to \
  524.549, 28.98 to \
  524.546, 28.98 to \
  524.546, 28.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 900 polygon from \
  524.57, 28.9901 to \
  524.573, 28.9901 to \
  524.573, 28.99 to \
  524.57, 28.99 to \
  524.57, 28.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 901 polygon from \
  524.595, 29.0001 to \
  524.598, 29.0001 to \
  524.598, 29 to \
  524.595, 29 to \
  524.595, 29.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 902 polygon from \
  524.62, 29.0101 to \
  524.623, 29.0101 to \
  524.623, 29.01 to \
  524.62, 29.01 to \
  524.62, 29.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 903 polygon from \
  524.644, 29.0201 to \
  524.647, 29.0201 to \
  524.647, 29.02 to \
  524.644, 29.02 to \
  524.644, 29.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 904 polygon from \
  524.669, 29.0301 to \
  524.672, 29.0301 to \
  524.672, 29.03 to \
  524.669, 29.03 to \
  524.669, 29.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 905 polygon from \
  524.694, 29.0401 to \
  524.697, 29.0401 to \
  524.697, 29.04 to \
  524.694, 29.04 to \
  524.694, 29.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 906 polygon from \
  524.718, 29.0501 to \
  524.721, 29.0501 to \
  524.721, 29.05 to \
  524.718, 29.05 to \
  524.718, 29.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 907 polygon from \
  524.743, 29.0601 to \
  524.746, 29.0601 to \
  524.746, 29.06 to \
  524.743, 29.06 to \
  524.743, 29.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 908 polygon from \
  524.768, 29.0701 to \
  524.771, 29.0701 to \
  524.771, 29.07 to \
  524.768, 29.07 to \
  524.768, 29.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 909 polygon from \
  524.793, 29.0801 to \
  524.796, 29.0801 to \
  524.796, 29.08 to \
  524.793, 29.08 to \
  524.793, 29.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 910 polygon from \
  524.817, 29.0901 to \
  524.82, 29.0901 to \
  524.82, 29.09 to \
  524.817, 29.09 to \
  524.817, 29.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 911 polygon from \
  524.842, 29.1001 to \
  524.845, 29.1001 to \
  524.845, 29.1 to \
  524.842, 29.1 to \
  524.842, 29.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 912 polygon from \
  524.867, 29.1101 to \
  524.87, 29.1101 to \
  524.87, 29.11 to \
  524.867, 29.11 to \
  524.867, 29.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 913 polygon from \
  524.892, 29.1201 to \
  524.895, 29.1201 to \
  524.895, 29.12 to \
  524.892, 29.12 to \
  524.892, 29.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 914 polygon from \
  524.917, 29.1301 to \
  524.92, 29.1301 to \
  524.92, 29.13 to \
  524.917, 29.13 to \
  524.917, 29.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 915 polygon from \
  524.942, 29.1401 to \
  524.945, 29.1401 to \
  524.945, 29.14 to \
  524.942, 29.14 to \
  524.942, 29.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 916 polygon from \
  524.967, 29.1501 to \
  524.97, 29.1501 to \
  524.97, 29.15 to \
  524.967, 29.15 to \
  524.967, 29.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 917 polygon from \
  524.992, 29.1601 to \
  524.995, 29.1601 to \
  524.995, 29.16 to \
  524.992, 29.16 to \
  524.992, 29.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 918 polygon from \
  525.017, 29.1701 to \
  525.02, 29.1701 to \
  525.02, 29.17 to \
  525.017, 29.17 to \
  525.017, 29.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 919 polygon from \
  525.042, 29.1801 to \
  525.045, 29.1801 to \
  525.045, 29.18 to \
  525.042, 29.18 to \
  525.042, 29.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 920 polygon from \
  525.067, 29.1901 to \
  525.07, 29.1901 to \
  525.07, 29.19 to \
  525.067, 29.19 to \
  525.067, 29.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 921 polygon from \
  525.092, 29.2001 to \
  525.095, 29.2001 to \
  525.095, 29.2 to \
  525.092, 29.2 to \
  525.092, 29.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 922 polygon from \
  525.117, 29.2101 to \
  525.12, 29.2101 to \
  525.12, 29.21 to \
  525.117, 29.21 to \
  525.117, 29.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 923 polygon from \
  525.142, 29.2201 to \
  525.145, 29.2201 to \
  525.145, 29.22 to \
  525.142, 29.22 to \
  525.142, 29.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 924 polygon from \
  525.167, 29.2301 to \
  525.17, 29.2301 to \
  525.17, 29.23 to \
  525.167, 29.23 to \
  525.167, 29.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 925 polygon from \
  525.192, 29.2401 to \
  525.196, 29.2401 to \
  525.196, 29.24 to \
  525.192, 29.24 to \
  525.192, 29.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 926 polygon from \
  525.218, 29.2501 to \
  525.221, 29.2501 to \
  525.221, 29.25 to \
  525.218, 29.25 to \
  525.218, 29.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 927 polygon from \
  525.243, 29.2601 to \
  525.246, 29.2601 to \
  525.246, 29.26 to \
  525.243, 29.26 to \
  525.243, 29.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 928 polygon from \
  525.268, 29.2701 to \
  525.271, 29.2701 to \
  525.271, 29.27 to \
  525.268, 29.27 to \
  525.268, 29.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 929 polygon from \
  525.293, 29.2801 to \
  525.297, 29.2801 to \
  525.297, 29.28 to \
  525.293, 29.28 to \
  525.293, 29.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 930 polygon from \
  525.319, 29.2901 to \
  525.322, 29.2901 to \
  525.322, 29.29 to \
  525.319, 29.29 to \
  525.319, 29.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 931 polygon from \
  525.344, 29.3001 to \
  525.347, 29.3001 to \
  525.347, 29.3 to \
  525.344, 29.3 to \
  525.344, 29.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 932 polygon from \
  525.369, 29.3101 to \
  525.373, 29.3101 to \
  525.373, 29.31 to \
  525.369, 29.31 to \
  525.369, 29.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 933 polygon from \
  525.395, 29.3201 to \
  525.398, 29.3201 to \
  525.398, 29.32 to \
  525.395, 29.32 to \
  525.395, 29.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 934 polygon from \
  525.42, 29.3301 to \
  525.423, 29.3301 to \
  525.423, 29.33 to \
  525.42, 29.33 to \
  525.42, 29.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 935 polygon from \
  525.446, 29.3401 to \
  525.449, 29.3401 to \
  525.449, 29.34 to \
  525.446, 29.34 to \
  525.446, 29.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 936 polygon from \
  525.471, 29.3501 to \
  525.474, 29.3501 to \
  525.474, 29.35 to \
  525.471, 29.35 to \
  525.471, 29.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 937 polygon from \
  525.497, 29.3601 to \
  525.5, 29.3601 to \
  525.5, 29.36 to \
  525.497, 29.36 to \
  525.497, 29.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 938 polygon from \
  525.522, 29.3701 to \
  525.525, 29.3701 to \
  525.525, 29.37 to \
  525.522, 29.37 to \
  525.522, 29.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 939 polygon from \
  525.548, 29.3801 to \
  525.551, 29.3801 to \
  525.551, 29.38 to \
  525.548, 29.38 to \
  525.548, 29.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 940 polygon from \
  525.573, 29.3901 to \
  525.576, 29.3901 to \
  525.576, 29.39 to \
  525.573, 29.39 to \
  525.573, 29.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 941 polygon from \
  525.599, 29.4001 to \
  525.602, 29.4001 to \
  525.602, 29.4 to \
  525.599, 29.4 to \
  525.599, 29.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 942 polygon from \
  525.624, 29.4101 to \
  525.628, 29.4101 to \
  525.628, 29.41 to \
  525.624, 29.41 to \
  525.624, 29.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 943 polygon from \
  525.65, 29.4201 to \
  525.653, 29.4201 to \
  525.653, 29.42 to \
  525.65, 29.42 to \
  525.65, 29.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 944 polygon from \
  525.676, 29.4301 to \
  525.679, 29.4301 to \
  525.679, 29.43 to \
  525.676, 29.43 to \
  525.676, 29.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 945 polygon from \
  525.701, 29.4401 to \
  525.705, 29.4401 to \
  525.705, 29.44 to \
  525.701, 29.44 to \
  525.701, 29.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 946 polygon from \
  525.727, 29.4501 to \
  525.73, 29.4501 to \
  525.73, 29.45 to \
  525.727, 29.45 to \
  525.727, 29.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 947 polygon from \
  525.753, 29.4601 to \
  525.756, 29.4601 to \
  525.756, 29.46 to \
  525.753, 29.46 to \
  525.753, 29.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 948 polygon from \
  525.779, 29.4701 to \
  525.782, 29.4701 to \
  525.782, 29.47 to \
  525.779, 29.47 to \
  525.779, 29.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 949 polygon from \
  525.804, 29.4801 to \
  525.808, 29.4801 to \
  525.808, 29.48 to \
  525.804, 29.48 to \
  525.804, 29.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 950 polygon from \
  525.83, 29.4901 to \
  525.833, 29.4901 to \
  525.833, 29.49 to \
  525.83, 29.49 to \
  525.83, 29.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 951 polygon from \
  525.856, 29.5001 to \
  525.859, 29.5001 to \
  525.859, 29.5 to \
  525.856, 29.5 to \
  525.856, 29.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 952 polygon from \
  525.882, 29.5101 to \
  525.885, 29.5101 to \
  525.885, 29.51 to \
  525.882, 29.51 to \
  525.882, 29.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 953 polygon from \
  525.908, 29.5201 to \
  525.911, 29.5201 to \
  525.911, 29.52 to \
  525.908, 29.52 to \
  525.908, 29.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 954 polygon from \
  525.934, 29.5301 to \
  525.937, 29.5301 to \
  525.937, 29.53 to \
  525.934, 29.53 to \
  525.934, 29.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 955 polygon from \
  525.96, 29.5401 to \
  525.963, 29.5401 to \
  525.963, 29.54 to \
  525.96, 29.54 to \
  525.96, 29.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 956 polygon from \
  525.986, 29.5501 to \
  525.989, 29.5501 to \
  525.989, 29.55 to \
  525.986, 29.55 to \
  525.986, 29.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 957 polygon from \
  526.012, 29.5601 to \
  526.015, 29.5601 to \
  526.015, 29.56 to \
  526.012, 29.56 to \
  526.012, 29.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 958 polygon from \
  526.038, 29.5701 to \
  526.041, 29.5701 to \
  526.041, 29.57 to \
  526.038, 29.57 to \
  526.038, 29.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 959 polygon from \
  526.064, 29.5801 to \
  526.067, 29.5801 to \
  526.067, 29.58 to \
  526.064, 29.58 to \
  526.064, 29.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 960 polygon from \
  526.09, 29.5901 to \
  526.093, 29.5901 to \
  526.093, 29.59 to \
  526.09, 29.59 to \
  526.09, 29.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 961 polygon from \
  526.116, 29.6001 to \
  526.119, 29.6001 to \
  526.119, 29.6 to \
  526.116, 29.6 to \
  526.116, 29.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 962 polygon from \
  526.142, 29.6101 to \
  526.145, 29.6101 to \
  526.145, 29.61 to \
  526.142, 29.61 to \
  526.142, 29.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 963 polygon from \
  526.168, 29.6201 to \
  526.171, 29.6201 to \
  526.171, 29.62 to \
  526.168, 29.62 to \
  526.168, 29.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 964 polygon from \
  526.194, 29.6301 to \
  526.198, 29.6301 to \
  526.198, 29.63 to \
  526.194, 29.63 to \
  526.194, 29.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 965 polygon from \
  526.22, 29.6401 to \
  526.224, 29.6401 to \
  526.224, 29.64 to \
  526.22, 29.64 to \
  526.22, 29.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 966 polygon from \
  526.247, 29.6501 to \
  526.25, 29.6501 to \
  526.25, 29.65 to \
  526.247, 29.65 to \
  526.247, 29.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 967 polygon from \
  526.273, 29.6601 to \
  526.276, 29.6601 to \
  526.276, 29.66 to \
  526.273, 29.66 to \
  526.273, 29.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 968 polygon from \
  526.299, 29.6701 to \
  526.303, 29.6701 to \
  526.303, 29.67 to \
  526.299, 29.67 to \
  526.299, 29.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 969 polygon from \
  526.326, 29.6801 to \
  526.329, 29.6801 to \
  526.329, 29.68 to \
  526.326, 29.68 to \
  526.326, 29.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 970 polygon from \
  526.352, 29.6901 to \
  526.355, 29.6901 to \
  526.355, 29.69 to \
  526.352, 29.69 to \
  526.352, 29.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 971 polygon from \
  526.378, 29.7001 to \
  526.382, 29.7001 to \
  526.382, 29.7 to \
  526.378, 29.7 to \
  526.378, 29.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 972 polygon from \
  526.405, 29.7101 to \
  526.408, 29.7101 to \
  526.408, 29.71 to \
  526.405, 29.71 to \
  526.405, 29.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 973 polygon from \
  526.431, 29.7201 to \
  526.434, 29.7201 to \
  526.434, 29.72 to \
  526.431, 29.72 to \
  526.431, 29.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 974 polygon from \
  526.458, 29.7301 to \
  526.461, 29.7301 to \
  526.461, 29.73 to \
  526.458, 29.73 to \
  526.458, 29.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 975 polygon from \
  526.484, 29.7401 to \
  526.487, 29.7401 to \
  526.487, 29.74 to \
  526.484, 29.74 to \
  526.484, 29.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 976 polygon from \
  526.51, 29.7501 to \
  526.514, 29.7501 to \
  526.514, 29.75 to \
  526.51, 29.75 to \
  526.51, 29.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 977 polygon from \
  526.537, 29.7601 to \
  526.54, 29.7601 to \
  526.54, 29.76 to \
  526.537, 29.76 to \
  526.537, 29.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 978 polygon from \
  526.564, 29.7701 to \
  526.567, 29.7701 to \
  526.567, 29.77 to \
  526.564, 29.77 to \
  526.564, 29.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 979 polygon from \
  526.59, 29.7801 to \
  526.594, 29.7801 to \
  526.594, 29.78 to \
  526.59, 29.78 to \
  526.59, 29.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 980 polygon from \
  526.617, 29.7901 to \
  526.62, 29.7901 to \
  526.62, 29.79 to \
  526.617, 29.79 to \
  526.617, 29.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 981 polygon from \
  526.643, 29.8001 to \
  526.647, 29.8001 to \
  526.647, 29.8 to \
  526.643, 29.8 to \
  526.643, 29.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 982 polygon from \
  526.67, 29.8101 to \
  526.673, 29.8101 to \
  526.673, 29.81 to \
  526.67, 29.81 to \
  526.67, 29.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 983 polygon from \
  526.697, 29.8201 to \
  526.7, 29.8201 to \
  526.7, 29.82 to \
  526.697, 29.82 to \
  526.697, 29.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 984 polygon from \
  526.723, 29.8301 to \
  526.727, 29.8301 to \
  526.727, 29.83 to \
  526.723, 29.83 to \
  526.723, 29.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 985 polygon from \
  526.75, 29.8401 to \
  526.754, 29.8401 to \
  526.754, 29.84 to \
  526.75, 29.84 to \
  526.75, 29.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 986 polygon from \
  526.777, 29.8501 to \
  526.78, 29.8501 to \
  526.78, 29.85 to \
  526.777, 29.85 to \
  526.777, 29.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 987 polygon from \
  526.804, 29.8601 to \
  526.807, 29.8601 to \
  526.807, 29.86 to \
  526.804, 29.86 to \
  526.804, 29.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 988 polygon from \
  526.831, 29.8701 to \
  526.834, 29.8701 to \
  526.834, 29.87 to \
  526.831, 29.87 to \
  526.831, 29.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 989 polygon from \
  526.857, 29.8801 to \
  526.861, 29.8801 to \
  526.861, 29.88 to \
  526.857, 29.88 to \
  526.857, 29.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 990 polygon from \
  526.884, 29.8901 to \
  526.888, 29.8901 to \
  526.888, 29.89 to \
  526.884, 29.89 to \
  526.884, 29.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 991 polygon from \
  526.911, 29.9001 to \
  526.915, 29.9001 to \
  526.915, 29.9 to \
  526.911, 29.9 to \
  526.911, 29.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 992 polygon from \
  526.938, 29.9101 to \
  526.941, 29.9101 to \
  526.941, 29.91 to \
  526.938, 29.91 to \
  526.938, 29.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 993 polygon from \
  526.965, 29.9201 to \
  526.968, 29.9201 to \
  526.968, 29.92 to \
  526.965, 29.92 to \
  526.965, 29.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 994 polygon from \
  526.992, 29.9301 to \
  526.995, 29.9301 to \
  526.995, 29.93 to \
  526.992, 29.93 to \
  526.992, 29.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 995 polygon from \
  527.019, 29.9401 to \
  527.022, 29.9401 to \
  527.022, 29.94 to \
  527.019, 29.94 to \
  527.019, 29.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 996 polygon from \
  527.046, 29.9501 to \
  527.049, 29.9501 to \
  527.049, 29.95 to \
  527.046, 29.95 to \
  527.046, 29.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 997 polygon from \
  527.073, 29.9601 to \
  527.077, 29.9601 to \
  527.077, 29.96 to \
  527.073, 29.96 to \
  527.073, 29.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 998 polygon from \
  527.1, 29.9701 to \
  527.104, 29.9701 to \
  527.104, 29.97 to \
  527.1, 29.97 to \
  527.1, 29.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 999 polygon from \
  527.127, 29.9801 to \
  527.131, 29.9801 to \
  527.131, 29.98 to \
  527.127, 29.98 to \
  527.127, 29.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1000 polygon from \
  527.154, 29.9901 to \
  527.158, 29.9901 to \
  527.158, 29.99 to \
  527.154, 29.99 to \
  527.154, 29.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1001 polygon from \
  527.182, 30.0001 to \
  527.185, 30.0001 to \
  527.185, 30 to \
  527.182, 30 to \
  527.182, 30.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1002 polygon from \
  527.209, 30.0101 to \
  527.212, 30.0101 to \
  527.212, 30.01 to \
  527.209, 30.01 to \
  527.209, 30.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1003 polygon from \
  527.236, 30.0201 to \
  527.239, 30.0201 to \
  527.239, 30.02 to \
  527.236, 30.02 to \
  527.236, 30.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1004 polygon from \
  527.263, 30.0301 to \
  527.267, 30.0301 to \
  527.267, 30.03 to \
  527.263, 30.03 to \
  527.263, 30.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1005 polygon from \
  527.291, 30.0401 to \
  527.294, 30.0401 to \
  527.294, 30.04 to \
  527.291, 30.04 to \
  527.291, 30.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1006 polygon from \
  527.318, 30.0501 to \
  527.321, 30.0501 to \
  527.321, 30.05 to \
  527.318, 30.05 to \
  527.318, 30.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1007 polygon from \
  527.345, 30.0601 to \
  527.349, 30.0601 to \
  527.349, 30.06 to \
  527.345, 30.06 to \
  527.345, 30.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1008 polygon from \
  527.373, 30.0701 to \
  527.376, 30.0701 to \
  527.376, 30.07 to \
  527.373, 30.07 to \
  527.373, 30.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1009 polygon from \
  527.4, 30.0801 to \
  527.403, 30.0801 to \
  527.403, 30.08 to \
  527.4, 30.08 to \
  527.4, 30.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1010 polygon from \
  527.427, 30.0901 to \
  527.431, 30.0901 to \
  527.431, 30.09 to \
  527.427, 30.09 to \
  527.427, 30.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1011 polygon from \
  527.455, 30.1001 to \
  527.458, 30.1001 to \
  527.458, 30.1 to \
  527.455, 30.1 to \
  527.455, 30.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1012 polygon from \
  527.482, 30.1101 to \
  527.486, 30.1101 to \
  527.486, 30.11 to \
  527.482, 30.11 to \
  527.482, 30.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1013 polygon from \
  527.51, 30.1201 to \
  527.513, 30.1201 to \
  527.513, 30.12 to \
  527.51, 30.12 to \
  527.51, 30.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1014 polygon from \
  527.537, 30.1301 to \
  527.541, 30.1301 to \
  527.541, 30.13 to \
  527.537, 30.13 to \
  527.537, 30.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1015 polygon from \
  527.565, 30.1401 to \
  527.568, 30.1401 to \
  527.568, 30.14 to \
  527.565, 30.14 to \
  527.565, 30.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1016 polygon from \
  527.592, 30.1501 to \
  527.596, 30.1501 to \
  527.596, 30.15 to \
  527.592, 30.15 to \
  527.592, 30.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1017 polygon from \
  527.62, 30.1601 to \
  527.623, 30.1601 to \
  527.623, 30.16 to \
  527.62, 30.16 to \
  527.62, 30.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1018 polygon from \
  527.648, 30.1701 to \
  527.651, 30.1701 to \
  527.651, 30.17 to \
  527.648, 30.17 to \
  527.648, 30.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1019 polygon from \
  527.675, 30.1801 to \
  527.679, 30.1801 to \
  527.679, 30.18 to \
  527.675, 30.18 to \
  527.675, 30.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1020 polygon from \
  527.703, 30.1901 to \
  527.706, 30.1901 to \
  527.706, 30.19 to \
  527.703, 30.19 to \
  527.703, 30.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1021 polygon from \
  527.731, 30.2001 to \
  527.734, 30.2001 to \
  527.734, 30.2 to \
  527.731, 30.2 to \
  527.731, 30.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1022 polygon from \
  527.758, 30.2101 to \
  527.762, 30.2101 to \
  527.762, 30.21 to \
  527.758, 30.21 to \
  527.758, 30.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1023 polygon from \
  527.786, 30.2201 to \
  527.79, 30.2201 to \
  527.79, 30.22 to \
  527.786, 30.22 to \
  527.786, 30.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1024 polygon from \
  527.814, 30.2301 to \
  527.818, 30.2301 to \
  527.818, 30.23 to \
  527.814, 30.23 to \
  527.814, 30.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1025 polygon from \
  527.842, 30.2401 to \
  527.845, 30.2401 to \
  527.845, 30.24 to \
  527.842, 30.24 to \
  527.842, 30.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1026 polygon from \
  527.87, 30.2501 to \
  527.873, 30.2501 to \
  527.873, 30.25 to \
  527.87, 30.25 to \
  527.87, 30.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1027 polygon from \
  527.898, 30.2601 to \
  527.901, 30.2601 to \
  527.901, 30.26 to \
  527.898, 30.26 to \
  527.898, 30.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1028 polygon from \
  527.925, 30.2701 to \
  527.929, 30.2701 to \
  527.929, 30.27 to \
  527.925, 30.27 to \
  527.925, 30.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1029 polygon from \
  527.953, 30.2801 to \
  527.957, 30.2801 to \
  527.957, 30.28 to \
  527.953, 30.28 to \
  527.953, 30.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1030 polygon from \
  527.981, 30.2901 to \
  527.985, 30.2901 to \
  527.985, 30.29 to \
  527.981, 30.29 to \
  527.981, 30.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1031 polygon from \
  528.009, 30.3001 to \
  528.013, 30.3001 to \
  528.013, 30.3 to \
  528.009, 30.3 to \
  528.009, 30.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1032 polygon from \
  528.037, 30.3101 to \
  528.041, 30.3101 to \
  528.041, 30.31 to \
  528.037, 30.31 to \
  528.037, 30.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1033 polygon from \
  528.065, 30.3201 to \
  528.069, 30.3201 to \
  528.069, 30.32 to \
  528.065, 30.32 to \
  528.065, 30.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1034 polygon from \
  528.094, 30.3301 to \
  528.097, 30.3301 to \
  528.097, 30.33 to \
  528.094, 30.33 to \
  528.094, 30.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1035 polygon from \
  528.122, 30.3401 to \
  528.125, 30.3401 to \
  528.125, 30.34 to \
  528.122, 30.34 to \
  528.122, 30.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1036 polygon from \
  528.15, 30.3501 to \
  528.153, 30.3501 to \
  528.153, 30.35 to \
  528.15, 30.35 to \
  528.15, 30.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1037 polygon from \
  528.178, 30.3601 to \
  528.182, 30.3601 to \
  528.182, 30.36 to \
  528.178, 30.36 to \
  528.178, 30.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1038 polygon from \
  528.206, 30.3701 to \
  528.21, 30.3701 to \
  528.21, 30.37 to \
  528.206, 30.37 to \
  528.206, 30.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1039 polygon from \
  528.234, 30.3801 to \
  528.238, 30.3801 to \
  528.238, 30.38 to \
  528.234, 30.38 to \
  528.234, 30.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1040 polygon from \
  528.263, 30.3901 to \
  528.266, 30.3901 to \
  528.266, 30.39 to \
  528.263, 30.39 to \
  528.263, 30.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1041 polygon from \
  528.291, 30.4001 to \
  528.294, 30.4001 to \
  528.294, 30.4 to \
  528.291, 30.4 to \
  528.291, 30.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1042 polygon from \
  528.319, 30.4101 to \
  528.323, 30.4101 to \
  528.323, 30.41 to \
  528.319, 30.41 to \
  528.319, 30.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1043 polygon from \
  528.348, 30.4201 to \
  528.351, 30.4201 to \
  528.351, 30.42 to \
  528.348, 30.42 to \
  528.348, 30.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1044 polygon from \
  528.376, 30.4301 to \
  528.379, 30.4301 to \
  528.379, 30.43 to \
  528.376, 30.43 to \
  528.376, 30.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1045 polygon from \
  528.404, 30.4401 to \
  528.408, 30.4401 to \
  528.408, 30.44 to \
  528.404, 30.44 to \
  528.404, 30.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1046 polygon from \
  528.433, 30.4501 to \
  528.436, 30.4501 to \
  528.436, 30.45 to \
  528.433, 30.45 to \
  528.433, 30.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1047 polygon from \
  528.461, 30.4601 to \
  528.465, 30.4601 to \
  528.465, 30.46 to \
  528.461, 30.46 to \
  528.461, 30.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1048 polygon from \
  528.49, 30.4701 to \
  528.493, 30.4701 to \
  528.493, 30.47 to \
  528.49, 30.47 to \
  528.49, 30.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1049 polygon from \
  528.518, 30.4801 to \
  528.522, 30.4801 to \
  528.522, 30.48 to \
  528.518, 30.48 to \
  528.518, 30.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1050 polygon from \
  528.547, 30.4901 to \
  528.55, 30.4901 to \
  528.55, 30.49 to \
  528.547, 30.49 to \
  528.547, 30.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1051 polygon from \
  528.575, 30.5001 to \
  528.579, 30.5001 to \
  528.579, 30.5 to \
  528.575, 30.5 to \
  528.575, 30.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1052 polygon from \
  528.604, 30.5101 to \
  528.607, 30.5101 to \
  528.607, 30.51 to \
  528.604, 30.51 to \
  528.604, 30.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1053 polygon from \
  528.632, 30.5201 to \
  528.636, 30.5201 to \
  528.636, 30.52 to \
  528.632, 30.52 to \
  528.632, 30.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1054 polygon from \
  528.661, 30.5301 to \
  528.665, 30.5301 to \
  528.665, 30.53 to \
  528.661, 30.53 to \
  528.661, 30.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1055 polygon from \
  528.69, 30.5401 to \
  528.693, 30.5401 to \
  528.693, 30.54 to \
  528.69, 30.54 to \
  528.69, 30.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1056 polygon from \
  528.718, 30.5501 to \
  528.722, 30.5501 to \
  528.722, 30.55 to \
  528.718, 30.55 to \
  528.718, 30.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1057 polygon from \
  528.747, 30.5601 to \
  528.751, 30.5601 to \
  528.751, 30.56 to \
  528.747, 30.56 to \
  528.747, 30.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1058 polygon from \
  528.776, 30.5701 to \
  528.78, 30.5701 to \
  528.78, 30.57 to \
  528.776, 30.57 to \
  528.776, 30.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1059 polygon from \
  528.805, 30.5801 to \
  528.808, 30.5801 to \
  528.808, 30.58 to \
  528.805, 30.58 to \
  528.805, 30.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1060 polygon from \
  528.834, 30.5901 to \
  528.837, 30.5901 to \
  528.837, 30.59 to \
  528.834, 30.59 to \
  528.834, 30.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1061 polygon from \
  528.862, 30.6001 to \
  528.866, 30.6001 to \
  528.866, 30.6 to \
  528.862, 30.6 to \
  528.862, 30.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1062 polygon from \
  528.891, 30.6101 to \
  528.895, 30.6101 to \
  528.895, 30.61 to \
  528.891, 30.61 to \
  528.891, 30.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1063 polygon from \
  528.92, 30.6201 to \
  528.924, 30.6201 to \
  528.924, 30.62 to \
  528.92, 30.62 to \
  528.92, 30.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1064 polygon from \
  528.949, 30.6301 to \
  528.953, 30.6301 to \
  528.953, 30.63 to \
  528.949, 30.63 to \
  528.949, 30.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1065 polygon from \
  528.978, 30.6401 to \
  528.982, 30.6401 to \
  528.982, 30.64 to \
  528.978, 30.64 to \
  528.978, 30.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1066 polygon from \
  529.007, 30.6501 to \
  529.011, 30.6501 to \
  529.011, 30.65 to \
  529.007, 30.65 to \
  529.007, 30.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1067 polygon from \
  529.036, 30.6601 to \
  529.04, 30.6601 to \
  529.04, 30.66 to \
  529.036, 30.66 to \
  529.036, 30.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1068 polygon from \
  529.065, 30.6701 to \
  529.069, 30.6701 to \
  529.069, 30.67 to \
  529.065, 30.67 to \
  529.065, 30.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1069 polygon from \
  529.094, 30.6801 to \
  529.098, 30.6801 to \
  529.098, 30.68 to \
  529.094, 30.68 to \
  529.094, 30.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1070 polygon from \
  529.123, 30.6901 to \
  529.127, 30.6901 to \
  529.127, 30.69 to \
  529.123, 30.69 to \
  529.123, 30.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1071 polygon from \
  529.152, 30.7001 to \
  529.156, 30.7001 to \
  529.156, 30.7 to \
  529.152, 30.7 to \
  529.152, 30.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1072 polygon from \
  529.182, 30.7101 to \
  529.185, 30.7101 to \
  529.185, 30.71 to \
  529.182, 30.71 to \
  529.182, 30.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1073 polygon from \
  529.211, 30.7201 to \
  529.215, 30.7201 to \
  529.215, 30.72 to \
  529.211, 30.72 to \
  529.211, 30.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1074 polygon from \
  529.24, 30.7301 to \
  529.244, 30.7301 to \
  529.244, 30.73 to \
  529.24, 30.73 to \
  529.24, 30.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1075 polygon from \
  529.269, 30.7401 to \
  529.273, 30.7401 to \
  529.273, 30.74 to \
  529.269, 30.74 to \
  529.269, 30.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1076 polygon from \
  529.299, 30.7501 to \
  529.302, 30.7501 to \
  529.302, 30.75 to \
  529.299, 30.75 to \
  529.299, 30.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1077 polygon from \
  529.328, 30.7601 to \
  529.332, 30.7601 to \
  529.332, 30.76 to \
  529.328, 30.76 to \
  529.328, 30.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1078 polygon from \
  529.357, 30.7701 to \
  529.361, 30.7701 to \
  529.361, 30.77 to \
  529.357, 30.77 to \
  529.357, 30.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1079 polygon from \
  529.387, 30.7801 to \
  529.39, 30.7801 to \
  529.39, 30.78 to \
  529.387, 30.78 to \
  529.387, 30.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1080 polygon from \
  529.416, 30.7901 to \
  529.42, 30.7901 to \
  529.42, 30.79 to \
  529.416, 30.79 to \
  529.416, 30.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1081 polygon from \
  529.445, 30.8001 to \
  529.449, 30.8001 to \
  529.449, 30.8 to \
  529.445, 30.8 to \
  529.445, 30.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1082 polygon from \
  529.475, 30.8101 to \
  529.479, 30.8101 to \
  529.479, 30.81 to \
  529.475, 30.81 to \
  529.475, 30.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1083 polygon from \
  529.504, 30.8201 to \
  529.508, 30.8201 to \
  529.508, 30.82 to \
  529.504, 30.82 to \
  529.504, 30.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1084 polygon from \
  529.534, 30.8301 to \
  529.538, 30.8301 to \
  529.538, 30.83 to \
  529.534, 30.83 to \
  529.534, 30.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1085 polygon from \
  529.563, 30.8401 to \
  529.567, 30.8401 to \
  529.567, 30.84 to \
  529.563, 30.84 to \
  529.563, 30.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1086 polygon from \
  529.593, 30.8501 to \
  529.597, 30.8501 to \
  529.597, 30.85 to \
  529.593, 30.85 to \
  529.593, 30.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1087 polygon from \
  529.623, 30.8601 to \
  529.626, 30.8601 to \
  529.626, 30.86 to \
  529.623, 30.86 to \
  529.623, 30.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1088 polygon from \
  529.652, 30.8701 to \
  529.656, 30.8701 to \
  529.656, 30.87 to \
  529.652, 30.87 to \
  529.652, 30.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1089 polygon from \
  529.682, 30.8801 to \
  529.686, 30.8801 to \
  529.686, 30.88 to \
  529.682, 30.88 to \
  529.682, 30.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1090 polygon from \
  529.712, 30.8901 to \
  529.715, 30.8901 to \
  529.715, 30.89 to \
  529.712, 30.89 to \
  529.712, 30.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1091 polygon from \
  529.741, 30.9001 to \
  529.745, 30.9001 to \
  529.745, 30.9 to \
  529.741, 30.9 to \
  529.741, 30.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1092 polygon from \
  529.771, 30.9101 to \
  529.775, 30.9101 to \
  529.775, 30.91 to \
  529.771, 30.91 to \
  529.771, 30.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1093 polygon from \
  529.801, 30.9201 to \
  529.805, 30.9201 to \
  529.805, 30.92 to \
  529.801, 30.92 to \
  529.801, 30.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1094 polygon from \
  529.831, 30.9301 to \
  529.834, 30.9301 to \
  529.834, 30.93 to \
  529.831, 30.93 to \
  529.831, 30.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1095 polygon from \
  529.861, 30.9401 to \
  529.864, 30.9401 to \
  529.864, 30.94 to \
  529.861, 30.94 to \
  529.861, 30.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1096 polygon from \
  529.89, 30.9501 to \
  529.894, 30.9501 to \
  529.894, 30.95 to \
  529.89, 30.95 to \
  529.89, 30.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1097 polygon from \
  529.92, 30.9601 to \
  529.924, 30.9601 to \
  529.924, 30.96 to \
  529.92, 30.96 to \
  529.92, 30.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1098 polygon from \
  529.95, 30.9701 to \
  529.954, 30.9701 to \
  529.954, 30.97 to \
  529.95, 30.97 to \
  529.95, 30.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1099 polygon from \
  529.98, 30.9801 to \
  529.984, 30.9801 to \
  529.984, 30.98 to \
  529.98, 30.98 to \
  529.98, 30.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1100 polygon from \
  530.01, 30.9901 to \
  530.014, 30.9901 to \
  530.014, 30.99 to \
  530.01, 30.99 to \
  530.01, 30.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1101 polygon from \
  530.04, 31.0001 to \
  530.044, 31.0001 to \
  530.044, 31 to \
  530.04, 31 to \
  530.04, 31.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1102 polygon from \
  530.07, 31.0101 to \
  530.074, 31.0101 to \
  530.074, 31.01 to \
  530.07, 31.01 to \
  530.07, 31.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1103 polygon from \
  530.1, 31.0201 to \
  530.104, 31.0201 to \
  530.104, 31.02 to \
  530.1, 31.02 to \
  530.1, 31.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1104 polygon from \
  530.131, 31.0301 to \
  530.134, 31.0301 to \
  530.134, 31.03 to \
  530.131, 31.03 to \
  530.131, 31.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1105 polygon from \
  530.161, 31.0401 to \
  530.164, 31.0401 to \
  530.164, 31.04 to \
  530.161, 31.04 to \
  530.161, 31.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1106 polygon from \
  530.191, 31.0501 to \
  530.195, 31.0501 to \
  530.195, 31.05 to \
  530.191, 31.05 to \
  530.191, 31.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1107 polygon from \
  530.221, 31.0601 to \
  530.225, 31.0601 to \
  530.225, 31.06 to \
  530.221, 31.06 to \
  530.221, 31.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1108 polygon from \
  530.251, 31.0701 to \
  530.255, 31.0701 to \
  530.255, 31.07 to \
  530.251, 31.07 to \
  530.251, 31.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1109 polygon from \
  530.282, 31.0801 to \
  530.285, 31.0801 to \
  530.285, 31.08 to \
  530.282, 31.08 to \
  530.282, 31.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1110 polygon from \
  530.312, 31.0901 to \
  530.316, 31.0901 to \
  530.316, 31.09 to \
  530.312, 31.09 to \
  530.312, 31.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1111 polygon from \
  530.342, 31.1001 to \
  530.346, 31.1001 to \
  530.346, 31.1 to \
  530.342, 31.1 to \
  530.342, 31.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1112 polygon from \
  530.373, 31.1101 to \
  530.376, 31.1101 to \
  530.376, 31.11 to \
  530.373, 31.11 to \
  530.373, 31.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1113 polygon from \
  530.403, 31.1201 to \
  530.407, 31.1201 to \
  530.407, 31.12 to \
  530.403, 31.12 to \
  530.403, 31.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1114 polygon from \
  530.433, 31.1301 to \
  530.437, 31.1301 to \
  530.437, 31.13 to \
  530.433, 31.13 to \
  530.433, 31.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1115 polygon from \
  530.464, 31.1401 to \
  530.468, 31.1401 to \
  530.468, 31.14 to \
  530.464, 31.14 to \
  530.464, 31.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1116 polygon from \
  530.494, 31.1501 to \
  530.498, 31.1501 to \
  530.498, 31.15 to \
  530.494, 31.15 to \
  530.494, 31.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1117 polygon from \
  530.525, 31.1601 to \
  530.529, 31.1601 to \
  530.529, 31.16 to \
  530.525, 31.16 to \
  530.525, 31.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1118 polygon from \
  530.555, 31.1701 to \
  530.559, 31.1701 to \
  530.559, 31.17 to \
  530.555, 31.17 to \
  530.555, 31.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1119 polygon from \
  530.586, 31.1801 to \
  530.59, 31.1801 to \
  530.59, 31.18 to \
  530.586, 31.18 to \
  530.586, 31.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1120 polygon from \
  530.616, 31.1901 to \
  530.62, 31.1901 to \
  530.62, 31.19 to \
  530.616, 31.19 to \
  530.616, 31.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1121 polygon from \
  530.647, 31.2001 to \
  530.651, 31.2001 to \
  530.651, 31.2 to \
  530.647, 31.2 to \
  530.647, 31.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1122 polygon from \
  530.678, 31.2101 to \
  530.682, 31.2101 to \
  530.682, 31.21 to \
  530.678, 31.21 to \
  530.678, 31.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1123 polygon from \
  530.708, 31.2201 to \
  530.712, 31.2201 to \
  530.712, 31.22 to \
  530.708, 31.22 to \
  530.708, 31.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1124 polygon from \
  530.739, 31.2301 to \
  530.743, 31.2301 to \
  530.743, 31.23 to \
  530.739, 31.23 to \
  530.739, 31.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1125 polygon from \
  530.77, 31.2401 to \
  530.774, 31.2401 to \
  530.774, 31.24 to \
  530.77, 31.24 to \
  530.77, 31.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1126 polygon from \
  530.801, 31.2501 to \
  530.805, 31.2501 to \
  530.805, 31.25 to \
  530.801, 31.25 to \
  530.801, 31.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1127 polygon from \
  530.832, 31.2601 to \
  530.835, 31.2601 to \
  530.835, 31.26 to \
  530.832, 31.26 to \
  530.832, 31.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1128 polygon from \
  530.862, 31.2701 to \
  530.866, 31.2701 to \
  530.866, 31.27 to \
  530.862, 31.27 to \
  530.862, 31.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1129 polygon from \
  530.893, 31.2801 to \
  530.897, 31.2801 to \
  530.897, 31.28 to \
  530.893, 31.28 to \
  530.893, 31.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1130 polygon from \
  530.924, 31.2901 to \
  530.928, 31.2901 to \
  530.928, 31.29 to \
  530.924, 31.29 to \
  530.924, 31.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1131 polygon from \
  530.955, 31.3001 to \
  530.959, 31.3001 to \
  530.959, 31.3 to \
  530.955, 31.3 to \
  530.955, 31.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1132 polygon from \
  530.986, 31.3101 to \
  530.99, 31.3101 to \
  530.99, 31.31 to \
  530.986, 31.31 to \
  530.986, 31.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1133 polygon from \
  531.017, 31.3201 to \
  531.021, 31.3201 to \
  531.021, 31.32 to \
  531.017, 31.32 to \
  531.017, 31.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1134 polygon from \
  531.048, 31.3301 to \
  531.052, 31.3301 to \
  531.052, 31.33 to \
  531.048, 31.33 to \
  531.048, 31.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1135 polygon from \
  531.079, 31.3401 to \
  531.083, 31.3401 to \
  531.083, 31.34 to \
  531.079, 31.34 to \
  531.079, 31.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1136 polygon from \
  531.11, 31.3501 to \
  531.114, 31.3501 to \
  531.114, 31.35 to \
  531.11, 31.35 to \
  531.11, 31.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1137 polygon from \
  531.141, 31.3601 to \
  531.145, 31.3601 to \
  531.145, 31.36 to \
  531.141, 31.36 to \
  531.141, 31.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1138 polygon from \
  531.173, 31.3701 to \
  531.176, 31.3701 to \
  531.176, 31.37 to \
  531.173, 31.37 to \
  531.173, 31.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1139 polygon from \
  531.204, 31.3801 to \
  531.208, 31.3801 to \
  531.208, 31.38 to \
  531.204, 31.38 to \
  531.204, 31.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1140 polygon from \
  531.235, 31.3901 to \
  531.239, 31.3901 to \
  531.239, 31.39 to \
  531.235, 31.39 to \
  531.235, 31.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1141 polygon from \
  531.266, 31.4001 to \
  531.27, 31.4001 to \
  531.27, 31.4 to \
  531.266, 31.4 to \
  531.266, 31.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1142 polygon from \
  531.297, 31.4101 to \
  531.301, 31.4101 to \
  531.301, 31.41 to \
  531.297, 31.41 to \
  531.297, 31.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1143 polygon from \
  531.329, 31.4201 to \
  531.333, 31.4201 to \
  531.333, 31.42 to \
  531.329, 31.42 to \
  531.329, 31.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1144 polygon from \
  531.36, 31.4301 to \
  531.364, 31.4301 to \
  531.364, 31.43 to \
  531.36, 31.43 to \
  531.36, 31.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1145 polygon from \
  531.392, 31.4401 to \
  531.395, 31.4401 to \
  531.395, 31.44 to \
  531.392, 31.44 to \
  531.392, 31.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1146 polygon from \
  531.423, 31.4501 to \
  531.427, 31.4501 to \
  531.427, 31.45 to \
  531.423, 31.45 to \
  531.423, 31.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1147 polygon from \
  531.454, 31.4601 to \
  531.458, 31.4601 to \
  531.458, 31.46 to \
  531.454, 31.46 to \
  531.454, 31.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1148 polygon from \
  531.486, 31.4701 to \
  531.49, 31.4701 to \
  531.49, 31.47 to \
  531.486, 31.47 to \
  531.486, 31.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1149 polygon from \
  531.517, 31.4801 to \
  531.521, 31.4801 to \
  531.521, 31.48 to \
  531.517, 31.48 to \
  531.517, 31.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1150 polygon from \
  531.549, 31.4901 to \
  531.553, 31.4901 to \
  531.553, 31.49 to \
  531.549, 31.49 to \
  531.549, 31.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1151 polygon from \
  531.58, 31.5001 to \
  531.584, 31.5001 to \
  531.584, 31.5 to \
  531.58, 31.5 to \
  531.58, 31.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1152 polygon from \
  531.612, 31.5101 to \
  531.616, 31.5101 to \
  531.616, 31.51 to \
  531.612, 31.51 to \
  531.612, 31.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1153 polygon from \
  531.644, 31.5201 to \
  531.648, 31.5201 to \
  531.648, 31.52 to \
  531.644, 31.52 to \
  531.644, 31.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1154 polygon from \
  531.675, 31.5301 to \
  531.679, 31.5301 to \
  531.679, 31.53 to \
  531.675, 31.53 to \
  531.675, 31.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1155 polygon from \
  531.707, 31.5401 to \
  531.711, 31.5401 to \
  531.711, 31.54 to \
  531.707, 31.54 to \
  531.707, 31.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1156 polygon from \
  531.739, 31.5501 to \
  531.743, 31.5501 to \
  531.743, 31.55 to \
  531.739, 31.55 to \
  531.739, 31.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1157 polygon from \
  531.77, 31.5601 to \
  531.774, 31.5601 to \
  531.774, 31.56 to \
  531.77, 31.56 to \
  531.77, 31.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1158 polygon from \
  531.802, 31.5701 to \
  531.806, 31.5701 to \
  531.806, 31.57 to \
  531.802, 31.57 to \
  531.802, 31.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1159 polygon from \
  531.834, 31.5801 to \
  531.838, 31.5801 to \
  531.838, 31.58 to \
  531.834, 31.58 to \
  531.834, 31.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1160 polygon from \
  531.866, 31.5901 to \
  531.87, 31.5901 to \
  531.87, 31.59 to \
  531.866, 31.59 to \
  531.866, 31.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1161 polygon from \
  531.898, 31.6001 to \
  531.902, 31.6001 to \
  531.902, 31.6 to \
  531.898, 31.6 to \
  531.898, 31.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1162 polygon from \
  531.93, 31.6101 to \
  531.934, 31.6101 to \
  531.934, 31.61 to \
  531.93, 31.61 to \
  531.93, 31.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1163 polygon from \
  531.962, 31.6201 to \
  531.966, 31.6201 to \
  531.966, 31.62 to \
  531.962, 31.62 to \
  531.962, 31.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1164 polygon from \
  531.994, 31.6301 to \
  531.998, 31.6301 to \
  531.998, 31.63 to \
  531.994, 31.63 to \
  531.994, 31.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1165 polygon from \
  532.026, 31.6401 to \
  532.03, 31.6401 to \
  532.03, 31.64 to \
  532.026, 31.64 to \
  532.026, 31.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1166 polygon from \
  532.058, 31.6501 to \
  532.062, 31.6501 to \
  532.062, 31.65 to \
  532.058, 31.65 to \
  532.058, 31.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1167 polygon from \
  532.09, 31.6601 to \
  532.094, 31.6601 to \
  532.094, 31.66 to \
  532.09, 31.66 to \
  532.09, 31.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1168 polygon from \
  532.122, 31.6701 to \
  532.126, 31.6701 to \
  532.126, 31.67 to \
  532.122, 31.67 to \
  532.122, 31.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1169 polygon from \
  532.154, 31.6801 to \
  532.158, 31.6801 to \
  532.158, 31.68 to \
  532.154, 31.68 to \
  532.154, 31.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1170 polygon from \
  532.186, 31.6901 to \
  532.19, 31.6901 to \
  532.19, 31.69 to \
  532.186, 31.69 to \
  532.186, 31.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1171 polygon from \
  532.218, 31.7001 to \
  532.222, 31.7001 to \
  532.222, 31.7 to \
  532.218, 31.7 to \
  532.218, 31.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1172 polygon from \
  532.251, 31.7101 to \
  532.255, 31.7101 to \
  532.255, 31.71 to \
  532.251, 31.71 to \
  532.251, 31.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1173 polygon from \
  532.283, 31.7201 to \
  532.287, 31.7201 to \
  532.287, 31.72 to \
  532.283, 31.72 to \
  532.283, 31.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1174 polygon from \
  532.315, 31.7301 to \
  532.319, 31.7301 to \
  532.319, 31.73 to \
  532.315, 31.73 to \
  532.315, 31.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1175 polygon from \
  532.348, 31.7401 to \
  532.352, 31.7401 to \
  532.352, 31.74 to \
  532.348, 31.74 to \
  532.348, 31.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1176 polygon from \
  532.38, 31.7501 to \
  532.384, 31.7501 to \
  532.384, 31.75 to \
  532.38, 31.75 to \
  532.38, 31.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1177 polygon from \
  532.412, 31.7601 to \
  532.416, 31.7601 to \
  532.416, 31.76 to \
  532.412, 31.76 to \
  532.412, 31.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1178 polygon from \
  532.445, 31.7701 to \
  532.449, 31.7701 to \
  532.449, 31.77 to \
  532.445, 31.77 to \
  532.445, 31.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1179 polygon from \
  532.477, 31.7801 to \
  532.481, 31.7801 to \
  532.481, 31.78 to \
  532.477, 31.78 to \
  532.477, 31.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1180 polygon from \
  532.51, 31.7901 to \
  532.514, 31.7901 to \
  532.514, 31.79 to \
  532.51, 31.79 to \
  532.51, 31.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1181 polygon from \
  532.542, 31.8001 to \
  532.546, 31.8001 to \
  532.546, 31.8 to \
  532.542, 31.8 to \
  532.542, 31.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1182 polygon from \
  532.575, 31.8101 to \
  532.579, 31.8101 to \
  532.579, 31.81 to \
  532.575, 31.81 to \
  532.575, 31.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1183 polygon from \
  532.607, 31.8201 to \
  532.611, 31.8201 to \
  532.611, 31.82 to \
  532.607, 31.82 to \
  532.607, 31.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1184 polygon from \
  532.64, 31.8301 to \
  532.644, 31.8301 to \
  532.644, 31.83 to \
  532.64, 31.83 to \
  532.64, 31.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1185 polygon from \
  532.673, 31.8401 to \
  532.677, 31.8401 to \
  532.677, 31.84 to \
  532.673, 31.84 to \
  532.673, 31.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1186 polygon from \
  532.705, 31.8501 to \
  532.709, 31.8501 to \
  532.709, 31.85 to \
  532.705, 31.85 to \
  532.705, 31.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1187 polygon from \
  532.738, 31.8601 to \
  532.742, 31.8601 to \
  532.742, 31.86 to \
  532.738, 31.86 to \
  532.738, 31.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1188 polygon from \
  532.771, 31.8701 to \
  532.775, 31.8701 to \
  532.775, 31.87 to \
  532.771, 31.87 to \
  532.771, 31.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1189 polygon from \
  532.804, 31.8801 to \
  532.808, 31.8801 to \
  532.808, 31.88 to \
  532.804, 31.88 to \
  532.804, 31.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1190 polygon from \
  532.836, 31.8901 to \
  532.841, 31.8901 to \
  532.841, 31.89 to \
  532.836, 31.89 to \
  532.836, 31.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1191 polygon from \
  532.869, 31.9001 to \
  532.873, 31.9001 to \
  532.873, 31.9 to \
  532.869, 31.9 to \
  532.869, 31.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1192 polygon from \
  532.902, 31.9101 to \
  532.906, 31.9101 to \
  532.906, 31.91 to \
  532.902, 31.91 to \
  532.902, 31.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1193 polygon from \
  532.935, 31.9201 to \
  532.939, 31.9201 to \
  532.939, 31.92 to \
  532.935, 31.92 to \
  532.935, 31.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1194 polygon from \
  532.968, 31.9301 to \
  532.972, 31.9301 to \
  532.972, 31.93 to \
  532.968, 31.93 to \
  532.968, 31.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1195 polygon from \
  533.001, 31.9401 to \
  533.005, 31.9401 to \
  533.005, 31.94 to \
  533.001, 31.94 to \
  533.001, 31.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1196 polygon from \
  533.034, 31.9501 to \
  533.038, 31.9501 to \
  533.038, 31.95 to \
  533.034, 31.95 to \
  533.034, 31.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1197 polygon from \
  533.067, 31.9601 to \
  533.071, 31.9601 to \
  533.071, 31.96 to \
  533.067, 31.96 to \
  533.067, 31.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1198 polygon from \
  533.1, 31.9701 to \
  533.104, 31.9701 to \
  533.104, 31.97 to \
  533.1, 31.97 to \
  533.1, 31.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1199 polygon from \
  533.133, 31.9801 to \
  533.137, 31.9801 to \
  533.137, 31.98 to \
  533.133, 31.98 to \
  533.133, 31.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1200 polygon from \
  533.166, 31.9901 to \
  533.171, 31.9901 to \
  533.171, 31.99 to \
  533.166, 31.99 to \
  533.166, 31.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1201 polygon from \
  533.2, 32.0001 to \
  533.204, 32.0001 to \
  533.204, 32 to \
  533.2, 32 to \
  533.2, 32.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1202 polygon from \
  533.233, 32.0101 to \
  533.237, 32.0101 to \
  533.237, 32.01 to \
  533.233, 32.01 to \
  533.233, 32.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1203 polygon from \
  533.266, 32.0201 to \
  533.27, 32.0201 to \
  533.27, 32.02 to \
  533.266, 32.02 to \
  533.266, 32.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1204 polygon from \
  533.299, 32.0301 to \
  533.304, 32.0301 to \
  533.304, 32.03 to \
  533.299, 32.03 to \
  533.299, 32.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1205 polygon from \
  533.333, 32.0401 to \
  533.337, 32.0401 to \
  533.337, 32.04 to \
  533.333, 32.04 to \
  533.333, 32.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1206 polygon from \
  533.366, 32.0501 to \
  533.37, 32.0501 to \
  533.37, 32.05 to \
  533.366, 32.05 to \
  533.366, 32.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1207 polygon from \
  533.399, 32.0601 to \
  533.404, 32.0601 to \
  533.404, 32.06 to \
  533.399, 32.06 to \
  533.399, 32.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1208 polygon from \
  533.433, 32.0701 to \
  533.437, 32.0701 to \
  533.437, 32.07 to \
  533.433, 32.07 to \
  533.433, 32.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1209 polygon from \
  533.466, 32.0801 to \
  533.47, 32.0801 to \
  533.47, 32.08 to \
  533.466, 32.08 to \
  533.466, 32.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1210 polygon from \
  533.5, 32.0901 to \
  533.504, 32.0901 to \
  533.504, 32.09 to \
  533.5, 32.09 to \
  533.5, 32.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1211 polygon from \
  533.533, 32.1001 to \
  533.537, 32.1001 to \
  533.537, 32.1 to \
  533.533, 32.1 to \
  533.533, 32.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1212 polygon from \
  533.567, 32.1101 to \
  533.571, 32.1101 to \
  533.571, 32.11 to \
  533.567, 32.11 to \
  533.567, 32.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1213 polygon from \
  533.6, 32.1201 to \
  533.605, 32.1201 to \
  533.605, 32.12 to \
  533.6, 32.12 to \
  533.6, 32.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1214 polygon from \
  533.634, 32.1301 to \
  533.638, 32.1301 to \
  533.638, 32.13 to \
  533.634, 32.13 to \
  533.634, 32.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1215 polygon from \
  533.668, 32.1401 to \
  533.672, 32.1401 to \
  533.672, 32.14 to \
  533.668, 32.14 to \
  533.668, 32.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1216 polygon from \
  533.701, 32.1501 to \
  533.706, 32.1501 to \
  533.706, 32.15 to \
  533.701, 32.15 to \
  533.701, 32.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1217 polygon from \
  533.735, 32.1601 to \
  533.739, 32.1601 to \
  533.739, 32.16 to \
  533.735, 32.16 to \
  533.735, 32.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1218 polygon from \
  533.769, 32.1701 to \
  533.773, 32.1701 to \
  533.773, 32.17 to \
  533.769, 32.17 to \
  533.769, 32.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1219 polygon from \
  533.803, 32.1801 to \
  533.807, 32.1801 to \
  533.807, 32.18 to \
  533.803, 32.18 to \
  533.803, 32.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1220 polygon from \
  533.836, 32.1901 to \
  533.841, 32.1901 to \
  533.841, 32.19 to \
  533.836, 32.19 to \
  533.836, 32.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1221 polygon from \
  533.87, 32.2001 to \
  533.875, 32.2001 to \
  533.875, 32.2 to \
  533.87, 32.2 to \
  533.87, 32.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1222 polygon from \
  533.904, 32.2101 to \
  533.908, 32.2101 to \
  533.908, 32.21 to \
  533.904, 32.21 to \
  533.904, 32.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1223 polygon from \
  533.938, 32.2201 to \
  533.942, 32.2201 to \
  533.942, 32.22 to \
  533.938, 32.22 to \
  533.938, 32.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1224 polygon from \
  533.972, 32.2301 to \
  533.976, 32.2301 to \
  533.976, 32.23 to \
  533.972, 32.23 to \
  533.972, 32.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1225 polygon from \
  534.006, 32.2401 to \
  534.01, 32.2401 to \
  534.01, 32.24 to \
  534.006, 32.24 to \
  534.006, 32.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1226 polygon from \
  534.04, 32.2501 to \
  534.044, 32.2501 to \
  534.044, 32.25 to \
  534.04, 32.25 to \
  534.04, 32.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1227 polygon from \
  534.074, 32.2601 to \
  534.078, 32.2601 to \
  534.078, 32.26 to \
  534.074, 32.26 to \
  534.074, 32.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1228 polygon from \
  534.108, 32.2701 to \
  534.112, 32.2701 to \
  534.112, 32.27 to \
  534.108, 32.27 to \
  534.108, 32.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1229 polygon from \
  534.142, 32.2801 to \
  534.147, 32.2801 to \
  534.147, 32.28 to \
  534.142, 32.28 to \
  534.142, 32.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1230 polygon from \
  534.176, 32.2901 to \
  534.181, 32.2901 to \
  534.181, 32.29 to \
  534.176, 32.29 to \
  534.176, 32.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1231 polygon from \
  534.211, 32.3001 to \
  534.215, 32.3001 to \
  534.215, 32.3 to \
  534.211, 32.3 to \
  534.211, 32.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1232 polygon from \
  534.245, 32.3101 to \
  534.249, 32.3101 to \
  534.249, 32.31 to \
  534.245, 32.31 to \
  534.245, 32.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1233 polygon from \
  534.279, 32.3201 to \
  534.283, 32.3201 to \
  534.283, 32.32 to \
  534.279, 32.32 to \
  534.279, 32.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1234 polygon from \
  534.313, 32.3301 to \
  534.318, 32.3301 to \
  534.318, 32.33 to \
  534.313, 32.33 to \
  534.313, 32.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1235 polygon from \
  534.348, 32.3401 to \
  534.352, 32.3401 to \
  534.352, 32.34 to \
  534.348, 32.34 to \
  534.348, 32.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1236 polygon from \
  534.382, 32.3501 to \
  534.386, 32.3501 to \
  534.386, 32.35 to \
  534.382, 32.35 to \
  534.382, 32.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1237 polygon from \
  534.417, 32.3601 to \
  534.421, 32.3601 to \
  534.421, 32.36 to \
  534.417, 32.36 to \
  534.417, 32.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1238 polygon from \
  534.451, 32.3701 to \
  534.455, 32.3701 to \
  534.455, 32.37 to \
  534.451, 32.37 to \
  534.451, 32.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1239 polygon from \
  534.485, 32.3801 to \
  534.49, 32.3801 to \
  534.49, 32.38 to \
  534.485, 32.38 to \
  534.485, 32.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1240 polygon from \
  534.52, 32.3901 to \
  534.524, 32.3901 to \
  534.524, 32.39 to \
  534.52, 32.39 to \
  534.52, 32.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1241 polygon from \
  534.554, 32.4001 to \
  534.559, 32.4001 to \
  534.559, 32.4 to \
  534.554, 32.4 to \
  534.554, 32.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1242 polygon from \
  534.589, 32.4101 to \
  534.593, 32.4101 to \
  534.593, 32.41 to \
  534.589, 32.41 to \
  534.589, 32.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1243 polygon from \
  534.624, 32.4201 to \
  534.628, 32.4201 to \
  534.628, 32.42 to \
  534.624, 32.42 to \
  534.624, 32.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1244 polygon from \
  534.658, 32.4301 to \
  534.663, 32.4301 to \
  534.663, 32.43 to \
  534.658, 32.43 to \
  534.658, 32.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1245 polygon from \
  534.693, 32.4401 to \
  534.697, 32.4401 to \
  534.697, 32.44 to \
  534.693, 32.44 to \
  534.693, 32.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1246 polygon from \
  534.728, 32.4501 to \
  534.732, 32.4501 to \
  534.732, 32.45 to \
  534.728, 32.45 to \
  534.728, 32.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1247 polygon from \
  534.762, 32.4601 to \
  534.767, 32.4601 to \
  534.767, 32.46 to \
  534.762, 32.46 to \
  534.762, 32.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1248 polygon from \
  534.797, 32.4701 to \
  534.802, 32.4701 to \
  534.802, 32.47 to \
  534.797, 32.47 to \
  534.797, 32.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1249 polygon from \
  534.832, 32.4801 to \
  534.836, 32.4801 to \
  534.836, 32.48 to \
  534.832, 32.48 to \
  534.832, 32.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1250 polygon from \
  534.867, 32.4901 to \
  534.871, 32.4901 to \
  534.871, 32.49 to \
  534.867, 32.49 to \
  534.867, 32.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1251 polygon from \
  534.902, 32.5001 to \
  534.906, 32.5001 to \
  534.906, 32.5 to \
  534.902, 32.5 to \
  534.902, 32.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1252 polygon from \
  534.937, 32.5101 to \
  534.941, 32.5101 to \
  534.941, 32.51 to \
  534.937, 32.51 to \
  534.937, 32.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1253 polygon from \
  534.972, 32.5201 to \
  534.976, 32.5201 to \
  534.976, 32.52 to \
  534.972, 32.52 to \
  534.972, 32.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1254 polygon from \
  535.007, 32.5301 to \
  535.011, 32.5301 to \
  535.011, 32.53 to \
  535.007, 32.53 to \
  535.007, 32.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1255 polygon from \
  535.042, 32.5401 to \
  535.046, 32.5401 to \
  535.046, 32.54 to \
  535.042, 32.54 to \
  535.042, 32.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1256 polygon from \
  535.077, 32.5501 to \
  535.081, 32.5501 to \
  535.081, 32.55 to \
  535.077, 32.55 to \
  535.077, 32.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1257 polygon from \
  535.112, 32.5601 to \
  535.116, 32.5601 to \
  535.116, 32.56 to \
  535.112, 32.56 to \
  535.112, 32.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1258 polygon from \
  535.147, 32.5701 to \
  535.151, 32.5701 to \
  535.151, 32.57 to \
  535.147, 32.57 to \
  535.147, 32.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1259 polygon from \
  535.182, 32.5801 to \
  535.186, 32.5801 to \
  535.186, 32.58 to \
  535.182, 32.58 to \
  535.182, 32.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1260 polygon from \
  535.217, 32.5901 to \
  535.222, 32.5901 to \
  535.222, 32.59 to \
  535.217, 32.59 to \
  535.217, 32.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1261 polygon from \
  535.252, 32.6001 to \
  535.257, 32.6001 to \
  535.257, 32.6 to \
  535.252, 32.6 to \
  535.252, 32.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1262 polygon from \
  535.288, 32.6101 to \
  535.292, 32.6101 to \
  535.292, 32.61 to \
  535.288, 32.61 to \
  535.288, 32.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1263 polygon from \
  535.323, 32.6201 to \
  535.328, 32.6201 to \
  535.328, 32.62 to \
  535.323, 32.62 to \
  535.323, 32.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1264 polygon from \
  535.358, 32.6301 to \
  535.363, 32.6301 to \
  535.363, 32.63 to \
  535.358, 32.63 to \
  535.358, 32.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1265 polygon from \
  535.394, 32.6401 to \
  535.398, 32.6401 to \
  535.398, 32.64 to \
  535.394, 32.64 to \
  535.394, 32.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1266 polygon from \
  535.429, 32.6501 to \
  535.434, 32.6501 to \
  535.434, 32.65 to \
  535.429, 32.65 to \
  535.429, 32.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1267 polygon from \
  535.465, 32.6601 to \
  535.469, 32.6601 to \
  535.469, 32.66 to \
  535.465, 32.66 to \
  535.465, 32.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1268 polygon from \
  535.5, 32.6701 to \
  535.505, 32.6701 to \
  535.505, 32.67 to \
  535.5, 32.67 to \
  535.5, 32.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1269 polygon from \
  535.536, 32.6801 to \
  535.54, 32.6801 to \
  535.54, 32.68 to \
  535.536, 32.68 to \
  535.536, 32.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1270 polygon from \
  535.571, 32.6901 to \
  535.576, 32.6901 to \
  535.576, 32.69 to \
  535.571, 32.69 to \
  535.571, 32.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1271 polygon from \
  535.607, 32.7001 to \
  535.611, 32.7001 to \
  535.611, 32.7 to \
  535.607, 32.7 to \
  535.607, 32.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1272 polygon from \
  535.642, 32.7101 to \
  535.647, 32.7101 to \
  535.647, 32.71 to \
  535.642, 32.71 to \
  535.642, 32.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1273 polygon from \
  535.678, 32.7201 to \
  535.683, 32.7201 to \
  535.683, 32.72 to \
  535.678, 32.72 to \
  535.678, 32.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1274 polygon from \
  535.714, 32.7301 to \
  535.718, 32.7301 to \
  535.718, 32.73 to \
  535.714, 32.73 to \
  535.714, 32.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1275 polygon from \
  535.749, 32.7401 to \
  535.754, 32.7401 to \
  535.754, 32.74 to \
  535.749, 32.74 to \
  535.749, 32.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1276 polygon from \
  535.785, 32.7501 to \
  535.79, 32.7501 to \
  535.79, 32.75 to \
  535.785, 32.75 to \
  535.785, 32.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1277 polygon from \
  535.821, 32.7601 to \
  535.826, 32.7601 to \
  535.826, 32.76 to \
  535.821, 32.76 to \
  535.821, 32.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1278 polygon from \
  535.857, 32.7701 to \
  535.861, 32.7701 to \
  535.861, 32.77 to \
  535.857, 32.77 to \
  535.857, 32.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1279 polygon from \
  535.893, 32.7801 to \
  535.897, 32.7801 to \
  535.897, 32.78 to \
  535.893, 32.78 to \
  535.893, 32.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1280 polygon from \
  535.929, 32.7901 to \
  535.933, 32.7901 to \
  535.933, 32.79 to \
  535.929, 32.79 to \
  535.929, 32.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1281 polygon from \
  535.965, 32.8001 to \
  535.969, 32.8001 to \
  535.969, 32.8 to \
  535.965, 32.8 to \
  535.965, 32.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1282 polygon from \
  536.001, 32.8101 to \
  536.005, 32.8101 to \
  536.005, 32.81 to \
  536.001, 32.81 to \
  536.001, 32.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1283 polygon from \
  536.037, 32.8201 to \
  536.041, 32.8201 to \
  536.041, 32.82 to \
  536.037, 32.82 to \
  536.037, 32.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1284 polygon from \
  536.073, 32.8301 to \
  536.077, 32.8301 to \
  536.077, 32.83 to \
  536.073, 32.83 to \
  536.073, 32.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1285 polygon from \
  536.109, 32.8401 to \
  536.113, 32.8401 to \
  536.113, 32.84 to \
  536.109, 32.84 to \
  536.109, 32.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1286 polygon from \
  536.145, 32.8501 to \
  536.149, 32.8501 to \
  536.149, 32.85 to \
  536.145, 32.85 to \
  536.145, 32.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1287 polygon from \
  536.181, 32.8601 to \
  536.186, 32.8601 to \
  536.186, 32.86 to \
  536.181, 32.86 to \
  536.181, 32.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1288 polygon from \
  536.217, 32.8701 to \
  536.222, 32.8701 to \
  536.222, 32.87 to \
  536.217, 32.87 to \
  536.217, 32.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1289 polygon from \
  536.253, 32.8801 to \
  536.258, 32.8801 to \
  536.258, 32.88 to \
  536.253, 32.88 to \
  536.253, 32.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1290 polygon from \
  536.29, 32.8901 to \
  536.294, 32.8901 to \
  536.294, 32.89 to \
  536.29, 32.89 to \
  536.29, 32.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1291 polygon from \
  536.326, 32.9001 to \
  536.331, 32.9001 to \
  536.331, 32.9 to \
  536.326, 32.9 to \
  536.326, 32.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1292 polygon from \
  536.362, 32.9101 to \
  536.367, 32.9101 to \
  536.367, 32.91 to \
  536.362, 32.91 to \
  536.362, 32.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1293 polygon from \
  536.399, 32.9201 to \
  536.403, 32.9201 to \
  536.403, 32.92 to \
  536.399, 32.92 to \
  536.399, 32.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1294 polygon from \
  536.435, 32.9301 to \
  536.44, 32.9301 to \
  536.44, 32.93 to \
  536.435, 32.93 to \
  536.435, 32.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1295 polygon from \
  536.472, 32.9401 to \
  536.476, 32.9401 to \
  536.476, 32.94 to \
  536.472, 32.94 to \
  536.472, 32.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1296 polygon from \
  536.508, 32.9501 to \
  536.513, 32.9501 to \
  536.513, 32.95 to \
  536.508, 32.95 to \
  536.508, 32.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1297 polygon from \
  536.545, 32.9601 to \
  536.549, 32.9601 to \
  536.549, 32.96 to \
  536.545, 32.96 to \
  536.545, 32.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1298 polygon from \
  536.581, 32.9701 to \
  536.586, 32.9701 to \
  536.586, 32.97 to \
  536.581, 32.97 to \
  536.581, 32.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1299 polygon from \
  536.618, 32.9801 to \
  536.622, 32.9801 to \
  536.622, 32.98 to \
  536.618, 32.98 to \
  536.618, 32.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1300 polygon from \
  536.654, 32.9901 to \
  536.659, 32.9901 to \
  536.659, 32.99 to \
  536.654, 32.99 to \
  536.654, 32.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1301 polygon from \
  536.691, 33.0001 to \
  536.696, 33.0001 to \
  536.696, 33 to \
  536.691, 33 to \
  536.691, 33.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1302 polygon from \
  536.728, 33.0101 to \
  536.732, 33.0101 to \
  536.732, 33.01 to \
  536.728, 33.01 to \
  536.728, 33.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1303 polygon from \
  536.765, 33.0201 to \
  536.769, 33.0201 to \
  536.769, 33.02 to \
  536.765, 33.02 to \
  536.765, 33.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1304 polygon from \
  536.801, 33.0301 to \
  536.806, 33.0301 to \
  536.806, 33.03 to \
  536.801, 33.03 to \
  536.801, 33.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1305 polygon from \
  536.838, 33.0401 to \
  536.843, 33.0401 to \
  536.843, 33.04 to \
  536.838, 33.04 to \
  536.838, 33.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1306 polygon from \
  536.875, 33.0501 to \
  536.88, 33.0501 to \
  536.88, 33.05 to \
  536.875, 33.05 to \
  536.875, 33.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1307 polygon from \
  536.912, 33.0601 to \
  536.917, 33.0601 to \
  536.917, 33.06 to \
  536.912, 33.06 to \
  536.912, 33.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1308 polygon from \
  536.949, 33.0701 to \
  536.954, 33.0701 to \
  536.954, 33.07 to \
  536.949, 33.07 to \
  536.949, 33.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1309 polygon from \
  536.986, 33.0801 to \
  536.991, 33.0801 to \
  536.991, 33.08 to \
  536.986, 33.08 to \
  536.986, 33.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1310 polygon from \
  537.023, 33.0901 to \
  537.028, 33.0901 to \
  537.028, 33.09 to \
  537.023, 33.09 to \
  537.023, 33.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1311 polygon from \
  537.06, 33.1001 to \
  537.065, 33.1001 to \
  537.065, 33.1 to \
  537.06, 33.1 to \
  537.06, 33.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1312 polygon from \
  537.097, 33.1101 to \
  537.102, 33.1101 to \
  537.102, 33.11 to \
  537.097, 33.11 to \
  537.097, 33.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1313 polygon from \
  537.134, 33.1201 to \
  537.139, 33.1201 to \
  537.139, 33.12 to \
  537.134, 33.12 to \
  537.134, 33.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1314 polygon from \
  537.171, 33.1301 to \
  537.176, 33.1301 to \
  537.176, 33.13 to \
  537.171, 33.13 to \
  537.171, 33.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1315 polygon from \
  537.208, 33.1401 to \
  537.213, 33.1401 to \
  537.213, 33.14 to \
  537.208, 33.14 to \
  537.208, 33.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1316 polygon from \
  537.246, 33.1501 to \
  537.25, 33.1501 to \
  537.25, 33.15 to \
  537.246, 33.15 to \
  537.246, 33.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1317 polygon from \
  537.283, 33.1601 to \
  537.288, 33.1601 to \
  537.288, 33.16 to \
  537.283, 33.16 to \
  537.283, 33.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1318 polygon from \
  537.32, 33.1701 to \
  537.325, 33.1701 to \
  537.325, 33.17 to \
  537.32, 33.17 to \
  537.32, 33.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1319 polygon from \
  537.358, 33.1801 to \
  537.362, 33.1801 to \
  537.362, 33.18 to \
  537.358, 33.18 to \
  537.358, 33.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1320 polygon from \
  537.395, 33.1901 to \
  537.4, 33.1901 to \
  537.4, 33.19 to \
  537.395, 33.19 to \
  537.395, 33.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1321 polygon from \
  537.432, 33.2001 to \
  537.437, 33.2001 to \
  537.437, 33.2 to \
  537.432, 33.2 to \
  537.432, 33.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1322 polygon from \
  537.47, 33.2101 to \
  537.475, 33.2101 to \
  537.475, 33.21 to \
  537.47, 33.21 to \
  537.47, 33.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1323 polygon from \
  537.507, 33.2201 to \
  537.512, 33.2201 to \
  537.512, 33.22 to \
  537.507, 33.22 to \
  537.507, 33.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1324 polygon from \
  537.545, 33.2301 to \
  537.55, 33.2301 to \
  537.55, 33.23 to \
  537.545, 33.23 to \
  537.545, 33.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1325 polygon from \
  537.582, 33.2401 to \
  537.587, 33.2401 to \
  537.587, 33.24 to \
  537.582, 33.24 to \
  537.582, 33.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1326 polygon from \
  537.62, 33.2501 to \
  537.625, 33.2501 to \
  537.625, 33.25 to \
  537.62, 33.25 to \
  537.62, 33.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1327 polygon from \
  537.658, 33.2601 to \
  537.662, 33.2601 to \
  537.662, 33.26 to \
  537.658, 33.26 to \
  537.658, 33.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1328 polygon from \
  537.695, 33.2701 to \
  537.7, 33.2701 to \
  537.7, 33.27 to \
  537.695, 33.27 to \
  537.695, 33.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1329 polygon from \
  537.733, 33.2801 to \
  537.738, 33.2801 to \
  537.738, 33.28 to \
  537.733, 33.28 to \
  537.733, 33.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1330 polygon from \
  537.771, 33.2901 to \
  537.776, 33.2901 to \
  537.776, 33.29 to \
  537.771, 33.29 to \
  537.771, 33.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1331 polygon from \
  537.809, 33.3001 to \
  537.813, 33.3001 to \
  537.813, 33.3 to \
  537.809, 33.3 to \
  537.809, 33.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1332 polygon from \
  537.846, 33.3101 to \
  537.851, 33.3101 to \
  537.851, 33.31 to \
  537.846, 33.31 to \
  537.846, 33.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1333 polygon from \
  537.884, 33.3201 to \
  537.889, 33.3201 to \
  537.889, 33.32 to \
  537.884, 33.32 to \
  537.884, 33.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1334 polygon from \
  537.922, 33.3301 to \
  537.927, 33.3301 to \
  537.927, 33.33 to \
  537.922, 33.33 to \
  537.922, 33.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1335 polygon from \
  537.96, 33.3401 to \
  537.965, 33.3401 to \
  537.965, 33.34 to \
  537.96, 33.34 to \
  537.96, 33.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1336 polygon from \
  537.998, 33.3501 to \
  538.003, 33.3501 to \
  538.003, 33.35 to \
  537.998, 33.35 to \
  537.998, 33.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1337 polygon from \
  538.036, 33.3601 to \
  538.041, 33.3601 to \
  538.041, 33.36 to \
  538.036, 33.36 to \
  538.036, 33.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1338 polygon from \
  538.074, 33.3701 to \
  538.079, 33.3701 to \
  538.079, 33.37 to \
  538.074, 33.37 to \
  538.074, 33.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1339 polygon from \
  538.112, 33.3801 to \
  538.117, 33.3801 to \
  538.117, 33.38 to \
  538.112, 33.38 to \
  538.112, 33.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1340 polygon from \
  538.15, 33.3901 to \
  538.155, 33.3901 to \
  538.155, 33.39 to \
  538.15, 33.39 to \
  538.15, 33.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1341 polygon from \
  538.189, 33.4001 to \
  538.193, 33.4001 to \
  538.193, 33.4 to \
  538.189, 33.4 to \
  538.189, 33.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1342 polygon from \
  538.227, 33.4101 to \
  538.232, 33.4101 to \
  538.232, 33.41 to \
  538.227, 33.41 to \
  538.227, 33.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1343 polygon from \
  538.265, 33.4201 to \
  538.27, 33.4201 to \
  538.27, 33.42 to \
  538.265, 33.42 to \
  538.265, 33.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1344 polygon from \
  538.303, 33.4301 to \
  538.308, 33.4301 to \
  538.308, 33.43 to \
  538.303, 33.43 to \
  538.303, 33.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1345 polygon from \
  538.342, 33.4401 to \
  538.346, 33.4401 to \
  538.346, 33.44 to \
  538.342, 33.44 to \
  538.342, 33.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1346 polygon from \
  538.38, 33.4501 to \
  538.385, 33.4501 to \
  538.385, 33.45 to \
  538.38, 33.45 to \
  538.38, 33.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1347 polygon from \
  538.418, 33.4601 to \
  538.423, 33.4601 to \
  538.423, 33.46 to \
  538.418, 33.46 to \
  538.418, 33.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1348 polygon from \
  538.457, 33.4701 to \
  538.462, 33.4701 to \
  538.462, 33.47 to \
  538.457, 33.47 to \
  538.457, 33.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1349 polygon from \
  538.495, 33.4801 to \
  538.5, 33.4801 to \
  538.5, 33.48 to \
  538.495, 33.48 to \
  538.495, 33.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1350 polygon from \
  538.534, 33.4901 to \
  538.539, 33.4901 to \
  538.539, 33.49 to \
  538.534, 33.49 to \
  538.534, 33.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1351 polygon from \
  538.572, 33.5001 to \
  538.577, 33.5001 to \
  538.577, 33.5 to \
  538.572, 33.5 to \
  538.572, 33.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1352 polygon from \
  538.611, 33.5101 to \
  538.616, 33.5101 to \
  538.616, 33.51 to \
  538.611, 33.51 to \
  538.611, 33.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1353 polygon from \
  538.65, 33.5201 to \
  538.654, 33.5201 to \
  538.654, 33.52 to \
  538.65, 33.52 to \
  538.65, 33.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1354 polygon from \
  538.688, 33.5301 to \
  538.693, 33.5301 to \
  538.693, 33.53 to \
  538.688, 33.53 to \
  538.688, 33.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1355 polygon from \
  538.727, 33.5401 to \
  538.732, 33.5401 to \
  538.732, 33.54 to \
  538.727, 33.54 to \
  538.727, 33.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1356 polygon from \
  538.766, 33.5501 to \
  538.771, 33.5501 to \
  538.771, 33.55 to \
  538.766, 33.55 to \
  538.766, 33.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1357 polygon from \
  538.804, 33.5601 to \
  538.809, 33.5601 to \
  538.809, 33.56 to \
  538.804, 33.56 to \
  538.804, 33.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1358 polygon from \
  538.843, 33.5701 to \
  538.848, 33.5701 to \
  538.848, 33.57 to \
  538.843, 33.57 to \
  538.843, 33.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1359 polygon from \
  538.882, 33.5801 to \
  538.887, 33.5801 to \
  538.887, 33.58 to \
  538.882, 33.58 to \
  538.882, 33.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1360 polygon from \
  538.921, 33.5901 to \
  538.926, 33.5901 to \
  538.926, 33.59 to \
  538.921, 33.59 to \
  538.921, 33.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1361 polygon from \
  538.96, 33.6001 to \
  538.965, 33.6001 to \
  538.965, 33.6 to \
  538.96, 33.6 to \
  538.96, 33.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1362 polygon from \
  538.999, 33.6101 to \
  539.004, 33.6101 to \
  539.004, 33.61 to \
  538.999, 33.61 to \
  538.999, 33.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1363 polygon from \
  539.038, 33.6201 to \
  539.043, 33.6201 to \
  539.043, 33.62 to \
  539.038, 33.62 to \
  539.038, 33.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1364 polygon from \
  539.077, 33.6301 to \
  539.082, 33.6301 to \
  539.082, 33.63 to \
  539.077, 33.63 to \
  539.077, 33.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1365 polygon from \
  539.116, 33.6401 to \
  539.121, 33.6401 to \
  539.121, 33.64 to \
  539.116, 33.64 to \
  539.116, 33.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1366 polygon from \
  539.155, 33.6501 to \
  539.16, 33.6501 to \
  539.16, 33.65 to \
  539.155, 33.65 to \
  539.155, 33.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1367 polygon from \
  539.194, 33.6601 to \
  539.199, 33.6601 to \
  539.199, 33.66 to \
  539.194, 33.66 to \
  539.194, 33.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1368 polygon from \
  539.234, 33.6701 to \
  539.239, 33.6701 to \
  539.239, 33.67 to \
  539.234, 33.67 to \
  539.234, 33.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1369 polygon from \
  539.273, 33.6801 to \
  539.278, 33.6801 to \
  539.278, 33.68 to \
  539.273, 33.68 to \
  539.273, 33.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1370 polygon from \
  539.312, 33.6901 to \
  539.317, 33.6901 to \
  539.317, 33.69 to \
  539.312, 33.69 to \
  539.312, 33.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1371 polygon from \
  539.352, 33.7001 to \
  539.356, 33.7001 to \
  539.356, 33.7 to \
  539.352, 33.7 to \
  539.352, 33.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1372 polygon from \
  539.391, 33.7101 to \
  539.396, 33.7101 to \
  539.396, 33.71 to \
  539.391, 33.71 to \
  539.391, 33.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1373 polygon from \
  539.43, 33.7201 to \
  539.435, 33.7201 to \
  539.435, 33.72 to \
  539.43, 33.72 to \
  539.43, 33.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1374 polygon from \
  539.47, 33.7301 to \
  539.475, 33.7301 to \
  539.475, 33.73 to \
  539.47, 33.73 to \
  539.47, 33.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1375 polygon from \
  539.509, 33.7401 to \
  539.514, 33.7401 to \
  539.514, 33.74 to \
  539.509, 33.74 to \
  539.509, 33.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1376 polygon from \
  539.549, 33.7501 to \
  539.554, 33.7501 to \
  539.554, 33.75 to \
  539.549, 33.75 to \
  539.549, 33.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1377 polygon from \
  539.588, 33.7601 to \
  539.593, 33.7601 to \
  539.593, 33.76 to \
  539.588, 33.76 to \
  539.588, 33.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1378 polygon from \
  539.628, 33.7701 to \
  539.633, 33.7701 to \
  539.633, 33.77 to \
  539.628, 33.77 to \
  539.628, 33.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1379 polygon from \
  539.668, 33.7801 to \
  539.673, 33.7801 to \
  539.673, 33.78 to \
  539.668, 33.78 to \
  539.668, 33.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1380 polygon from \
  539.707, 33.7901 to \
  539.712, 33.7901 to \
  539.712, 33.79 to \
  539.707, 33.79 to \
  539.707, 33.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1381 polygon from \
  539.747, 33.8001 to \
  539.752, 33.8001 to \
  539.752, 33.8 to \
  539.747, 33.8 to \
  539.747, 33.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1382 polygon from \
  539.787, 33.8101 to \
  539.792, 33.8101 to \
  539.792, 33.81 to \
  539.787, 33.81 to \
  539.787, 33.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1383 polygon from \
  539.827, 33.8201 to \
  539.832, 33.8201 to \
  539.832, 33.82 to \
  539.827, 33.82 to \
  539.827, 33.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1384 polygon from \
  539.866, 33.8301 to \
  539.871, 33.8301 to \
  539.871, 33.83 to \
  539.866, 33.83 to \
  539.866, 33.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1385 polygon from \
  539.906, 33.8401 to \
  539.911, 33.8401 to \
  539.911, 33.84 to \
  539.906, 33.84 to \
  539.906, 33.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1386 polygon from \
  539.946, 33.8501 to \
  539.951, 33.8501 to \
  539.951, 33.85 to \
  539.946, 33.85 to \
  539.946, 33.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1387 polygon from \
  539.986, 33.8601 to \
  539.991, 33.8601 to \
  539.991, 33.86 to \
  539.986, 33.86 to \
  539.986, 33.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1388 polygon from \
  540.026, 33.8701 to \
  540.031, 33.8701 to \
  540.031, 33.87 to \
  540.026, 33.87 to \
  540.026, 33.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1389 polygon from \
  540.066, 33.8801 to \
  540.071, 33.8801 to \
  540.071, 33.88 to \
  540.066, 33.88 to \
  540.066, 33.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1390 polygon from \
  540.106, 33.8901 to \
  540.111, 33.8901 to \
  540.111, 33.89 to \
  540.106, 33.89 to \
  540.106, 33.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1391 polygon from \
  540.146, 33.9001 to \
  540.152, 33.9001 to \
  540.152, 33.9 to \
  540.146, 33.9 to \
  540.146, 33.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1392 polygon from \
  540.187, 33.9101 to \
  540.192, 33.9101 to \
  540.192, 33.91 to \
  540.187, 33.91 to \
  540.187, 33.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1393 polygon from \
  540.227, 33.9201 to \
  540.232, 33.9201 to \
  540.232, 33.92 to \
  540.227, 33.92 to \
  540.227, 33.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1394 polygon from \
  540.267, 33.9301 to \
  540.272, 33.9301 to \
  540.272, 33.93 to \
  540.267, 33.93 to \
  540.267, 33.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1395 polygon from \
  540.307, 33.9401 to \
  540.312, 33.9401 to \
  540.312, 33.94 to \
  540.307, 33.94 to \
  540.307, 33.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1396 polygon from \
  540.348, 33.9501 to \
  540.353, 33.9501 to \
  540.353, 33.95 to \
  540.348, 33.95 to \
  540.348, 33.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1397 polygon from \
  540.388, 33.9601 to \
  540.393, 33.9601 to \
  540.393, 33.96 to \
  540.388, 33.96 to \
  540.388, 33.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1398 polygon from \
  540.428, 33.9701 to \
  540.434, 33.9701 to \
  540.434, 33.97 to \
  540.428, 33.97 to \
  540.428, 33.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1399 polygon from \
  540.469, 33.9801 to \
  540.474, 33.9801 to \
  540.474, 33.98 to \
  540.469, 33.98 to \
  540.469, 33.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1400 polygon from \
  540.509, 33.9901 to \
  540.515, 33.9901 to \
  540.515, 33.99 to \
  540.509, 33.99 to \
  540.509, 33.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1401 polygon from \
  540.55, 34.0001 to \
  540.555, 34.0001 to \
  540.555, 34 to \
  540.55, 34 to \
  540.55, 34.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1402 polygon from \
  540.591, 34.0101 to \
  540.596, 34.0101 to \
  540.596, 34.01 to \
  540.591, 34.01 to \
  540.591, 34.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1403 polygon from \
  540.631, 34.0201 to \
  540.636, 34.0201 to \
  540.636, 34.02 to \
  540.631, 34.02 to \
  540.631, 34.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1404 polygon from \
  540.672, 34.0301 to \
  540.677, 34.0301 to \
  540.677, 34.03 to \
  540.672, 34.03 to \
  540.672, 34.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1405 polygon from \
  540.712, 34.0401 to \
  540.718, 34.0401 to \
  540.718, 34.04 to \
  540.712, 34.04 to \
  540.712, 34.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1406 polygon from \
  540.753, 34.0501 to \
  540.758, 34.0501 to \
  540.758, 34.05 to \
  540.753, 34.05 to \
  540.753, 34.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1407 polygon from \
  540.794, 34.0601 to \
  540.799, 34.0601 to \
  540.799, 34.06 to \
  540.794, 34.06 to \
  540.794, 34.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1408 polygon from \
  540.835, 34.0701 to \
  540.84, 34.0701 to \
  540.84, 34.07 to \
  540.835, 34.07 to \
  540.835, 34.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1409 polygon from \
  540.876, 34.0801 to \
  540.881, 34.0801 to \
  540.881, 34.08 to \
  540.876, 34.08 to \
  540.876, 34.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1410 polygon from \
  540.917, 34.0901 to \
  540.922, 34.0901 to \
  540.922, 34.09 to \
  540.917, 34.09 to \
  540.917, 34.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1411 polygon from \
  540.957, 34.1001 to \
  540.963, 34.1001 to \
  540.963, 34.1 to \
  540.957, 34.1 to \
  540.957, 34.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1412 polygon from \
  540.998, 34.1101 to \
  541.004, 34.1101 to \
  541.004, 34.11 to \
  540.998, 34.11 to \
  540.998, 34.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1413 polygon from \
  541.039, 34.1201 to \
  541.045, 34.1201 to \
  541.045, 34.12 to \
  541.039, 34.12 to \
  541.039, 34.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1414 polygon from \
  541.081, 34.1301 to \
  541.086, 34.1301 to \
  541.086, 34.13 to \
  541.081, 34.13 to \
  541.081, 34.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1415 polygon from \
  541.122, 34.1401 to \
  541.127, 34.1401 to \
  541.127, 34.14 to \
  541.122, 34.14 to \
  541.122, 34.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1416 polygon from \
  541.163, 34.1501 to \
  541.168, 34.1501 to \
  541.168, 34.15 to \
  541.163, 34.15 to \
  541.163, 34.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1417 polygon from \
  541.204, 34.1601 to \
  541.209, 34.1601 to \
  541.209, 34.16 to \
  541.204, 34.16 to \
  541.204, 34.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1418 polygon from \
  541.245, 34.1701 to \
  541.25, 34.1701 to \
  541.25, 34.17 to \
  541.245, 34.17 to \
  541.245, 34.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1419 polygon from \
  541.286, 34.1801 to \
  541.292, 34.1801 to \
  541.292, 34.18 to \
  541.286, 34.18 to \
  541.286, 34.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1420 polygon from \
  541.328, 34.1901 to \
  541.333, 34.1901 to \
  541.333, 34.19 to \
  541.328, 34.19 to \
  541.328, 34.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1421 polygon from \
  541.369, 34.2001 to \
  541.374, 34.2001 to \
  541.374, 34.2 to \
  541.369, 34.2 to \
  541.369, 34.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1422 polygon from \
  541.41, 34.2101 to \
  541.416, 34.2101 to \
  541.416, 34.21 to \
  541.41, 34.21 to \
  541.41, 34.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1423 polygon from \
  541.452, 34.2201 to \
  541.457, 34.2201 to \
  541.457, 34.22 to \
  541.452, 34.22 to \
  541.452, 34.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1424 polygon from \
  541.493, 34.2301 to \
  541.499, 34.2301 to \
  541.499, 34.23 to \
  541.493, 34.23 to \
  541.493, 34.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1425 polygon from \
  541.535, 34.2401 to \
  541.54, 34.2401 to \
  541.54, 34.24 to \
  541.535, 34.24 to \
  541.535, 34.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1426 polygon from \
  541.576, 34.2501 to \
  541.582, 34.2501 to \
  541.582, 34.25 to \
  541.576, 34.25 to \
  541.576, 34.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1427 polygon from \
  541.618, 34.2601 to \
  541.623, 34.2601 to \
  541.623, 34.26 to \
  541.618, 34.26 to \
  541.618, 34.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1428 polygon from \
  541.66, 34.2701 to \
  541.665, 34.2701 to \
  541.665, 34.27 to \
  541.66, 34.27 to \
  541.66, 34.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1429 polygon from \
  541.701, 34.2801 to \
  541.707, 34.2801 to \
  541.707, 34.28 to \
  541.701, 34.28 to \
  541.701, 34.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1430 polygon from \
  541.743, 34.2901 to \
  541.748, 34.2901 to \
  541.748, 34.29 to \
  541.743, 34.29 to \
  541.743, 34.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1431 polygon from \
  541.785, 34.3001 to \
  541.79, 34.3001 to \
  541.79, 34.3 to \
  541.785, 34.3 to \
  541.785, 34.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1432 polygon from \
  541.827, 34.3101 to \
  541.832, 34.3101 to \
  541.832, 34.31 to \
  541.827, 34.31 to \
  541.827, 34.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1433 polygon from \
  541.869, 34.3201 to \
  541.874, 34.3201 to \
  541.874, 34.32 to \
  541.869, 34.32 to \
  541.869, 34.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1434 polygon from \
  541.91, 34.3301 to \
  541.916, 34.3301 to \
  541.916, 34.33 to \
  541.91, 34.33 to \
  541.91, 34.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1435 polygon from \
  541.952, 34.3401 to \
  541.958, 34.3401 to \
  541.958, 34.34 to \
  541.952, 34.34 to \
  541.952, 34.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1436 polygon from \
  541.994, 34.3501 to \
  542, 34.3501 to \
  542, 34.35 to \
  541.994, 34.35 to \
  541.994, 34.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1437 polygon from \
  542.036, 34.3601 to \
  542.042, 34.3601 to \
  542.042, 34.36 to \
  542.036, 34.36 to \
  542.036, 34.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1438 polygon from \
  542.078, 34.3701 to \
  542.084, 34.3701 to \
  542.084, 34.37 to \
  542.078, 34.37 to \
  542.078, 34.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1439 polygon from \
  542.12, 34.3801 to \
  542.126, 34.3801 to \
  542.126, 34.38 to \
  542.12, 34.38 to \
  542.12, 34.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1440 polygon from \
  542.163, 34.3901 to \
  542.168, 34.3901 to \
  542.168, 34.39 to \
  542.163, 34.39 to \
  542.163, 34.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1441 polygon from \
  542.205, 34.4001 to \
  542.21, 34.4001 to \
  542.21, 34.4 to \
  542.205, 34.4 to \
  542.205, 34.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1442 polygon from \
  542.247, 34.4101 to \
  542.252, 34.4101 to \
  542.252, 34.41 to \
  542.247, 34.41 to \
  542.247, 34.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1443 polygon from \
  542.289, 34.4201 to \
  542.295, 34.4201 to \
  542.295, 34.42 to \
  542.289, 34.42 to \
  542.289, 34.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1444 polygon from \
  542.332, 34.4301 to \
  542.337, 34.4301 to \
  542.337, 34.43 to \
  542.332, 34.43 to \
  542.332, 34.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1445 polygon from \
  542.374, 34.4401 to \
  542.379, 34.4401 to \
  542.379, 34.44 to \
  542.374, 34.44 to \
  542.374, 34.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1446 polygon from \
  542.416, 34.4501 to \
  542.422, 34.4501 to \
  542.422, 34.45 to \
  542.416, 34.45 to \
  542.416, 34.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1447 polygon from \
  542.459, 34.4601 to \
  542.464, 34.4601 to \
  542.464, 34.46 to \
  542.459, 34.46 to \
  542.459, 34.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1448 polygon from \
  542.501, 34.4701 to \
  542.507, 34.4701 to \
  542.507, 34.47 to \
  542.501, 34.47 to \
  542.501, 34.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1449 polygon from \
  542.544, 34.4801 to \
  542.549, 34.4801 to \
  542.549, 34.48 to \
  542.544, 34.48 to \
  542.544, 34.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1450 polygon from \
  542.586, 34.4901 to \
  542.592, 34.4901 to \
  542.592, 34.49 to \
  542.586, 34.49 to \
  542.586, 34.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1451 polygon from \
  542.629, 34.5001 to \
  542.634, 34.5001 to \
  542.634, 34.5 to \
  542.629, 34.5 to \
  542.629, 34.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1452 polygon from \
  542.672, 34.5101 to \
  542.677, 34.5101 to \
  542.677, 34.51 to \
  542.672, 34.51 to \
  542.672, 34.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1453 polygon from \
  542.714, 34.5201 to \
  542.72, 34.5201 to \
  542.72, 34.52 to \
  542.714, 34.52 to \
  542.714, 34.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1454 polygon from \
  542.757, 34.5301 to \
  542.762, 34.5301 to \
  542.762, 34.53 to \
  542.757, 34.53 to \
  542.757, 34.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1455 polygon from \
  542.8, 34.5401 to \
  542.805, 34.5401 to \
  542.805, 34.54 to \
  542.8, 34.54 to \
  542.8, 34.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1456 polygon from \
  542.843, 34.5501 to \
  542.848, 34.5501 to \
  542.848, 34.55 to \
  542.843, 34.55 to \
  542.843, 34.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1457 polygon from \
  542.885, 34.5601 to \
  542.891, 34.5601 to \
  542.891, 34.56 to \
  542.885, 34.56 to \
  542.885, 34.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1458 polygon from \
  542.928, 34.5701 to \
  542.934, 34.5701 to \
  542.934, 34.57 to \
  542.928, 34.57 to \
  542.928, 34.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1459 polygon from \
  542.971, 34.5801 to \
  542.977, 34.5801 to \
  542.977, 34.58 to \
  542.971, 34.58 to \
  542.971, 34.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1460 polygon from \
  543.014, 34.5901 to \
  543.02, 34.5901 to \
  543.02, 34.59 to \
  543.014, 34.59 to \
  543.014, 34.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1461 polygon from \
  543.057, 34.6001 to \
  543.063, 34.6001 to \
  543.063, 34.6 to \
  543.057, 34.6 to \
  543.057, 34.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1462 polygon from \
  543.1, 34.6101 to \
  543.106, 34.6101 to \
  543.106, 34.61 to \
  543.1, 34.61 to \
  543.1, 34.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1463 polygon from \
  543.144, 34.6201 to \
  543.149, 34.6201 to \
  543.149, 34.62 to \
  543.144, 34.62 to \
  543.144, 34.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1464 polygon from \
  543.187, 34.6301 to \
  543.192, 34.6301 to \
  543.192, 34.63 to \
  543.187, 34.63 to \
  543.187, 34.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1465 polygon from \
  543.23, 34.6401 to \
  543.235, 34.6401 to \
  543.235, 34.64 to \
  543.23, 34.64 to \
  543.23, 34.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1466 polygon from \
  543.273, 34.6501 to \
  543.279, 34.6501 to \
  543.279, 34.65 to \
  543.273, 34.65 to \
  543.273, 34.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1467 polygon from \
  543.316, 34.6601 to \
  543.322, 34.6601 to \
  543.322, 34.66 to \
  543.316, 34.66 to \
  543.316, 34.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1468 polygon from \
  543.36, 34.6701 to \
  543.365, 34.6701 to \
  543.365, 34.67 to \
  543.36, 34.67 to \
  543.36, 34.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1469 polygon from \
  543.403, 34.6801 to \
  543.409, 34.6801 to \
  543.409, 34.68 to \
  543.403, 34.68 to \
  543.403, 34.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1470 polygon from \
  543.447, 34.6901 to \
  543.452, 34.6901 to \
  543.452, 34.69 to \
  543.447, 34.69 to \
  543.447, 34.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1471 polygon from \
  543.49, 34.7001 to \
  543.496, 34.7001 to \
  543.496, 34.7 to \
  543.49, 34.7 to \
  543.49, 34.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1472 polygon from \
  543.534, 34.7101 to \
  543.539, 34.7101 to \
  543.539, 34.71 to \
  543.534, 34.71 to \
  543.534, 34.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1473 polygon from \
  543.577, 34.7201 to \
  543.583, 34.7201 to \
  543.583, 34.72 to \
  543.577, 34.72 to \
  543.577, 34.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1474 polygon from \
  543.621, 34.7301 to \
  543.626, 34.7301 to \
  543.626, 34.73 to \
  543.621, 34.73 to \
  543.621, 34.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1475 polygon from \
  543.664, 34.7401 to \
  543.67, 34.7401 to \
  543.67, 34.74 to \
  543.664, 34.74 to \
  543.664, 34.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1476 polygon from \
  543.708, 34.7501 to \
  543.714, 34.7501 to \
  543.714, 34.75 to \
  543.708, 34.75 to \
  543.708, 34.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1477 polygon from \
  543.752, 34.7601 to \
  543.757, 34.7601 to \
  543.757, 34.76 to \
  543.752, 34.76 to \
  543.752, 34.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1478 polygon from \
  543.796, 34.7701 to \
  543.801, 34.7701 to \
  543.801, 34.77 to \
  543.796, 34.77 to \
  543.796, 34.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1479 polygon from \
  543.839, 34.7801 to \
  543.845, 34.7801 to \
  543.845, 34.78 to \
  543.839, 34.78 to \
  543.839, 34.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1480 polygon from \
  543.883, 34.7901 to \
  543.889, 34.7901 to \
  543.889, 34.79 to \
  543.883, 34.79 to \
  543.883, 34.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1481 polygon from \
  543.927, 34.8001 to \
  543.933, 34.8001 to \
  543.933, 34.8 to \
  543.927, 34.8 to \
  543.927, 34.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1482 polygon from \
  543.971, 34.8101 to \
  543.977, 34.8101 to \
  543.977, 34.81 to \
  543.971, 34.81 to \
  543.971, 34.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1483 polygon from \
  544.015, 34.8201 to \
  544.021, 34.8201 to \
  544.021, 34.82 to \
  544.015, 34.82 to \
  544.015, 34.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1484 polygon from \
  544.059, 34.8301 to \
  544.065, 34.8301 to \
  544.065, 34.83 to \
  544.059, 34.83 to \
  544.059, 34.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1485 polygon from \
  544.103, 34.8401 to \
  544.109, 34.8401 to \
  544.109, 34.84 to \
  544.103, 34.84 to \
  544.103, 34.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1486 polygon from \
  544.147, 34.8501 to \
  544.153, 34.8501 to \
  544.153, 34.85 to \
  544.147, 34.85 to \
  544.147, 34.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1487 polygon from \
  544.192, 34.8601 to \
  544.197, 34.8601 to \
  544.197, 34.86 to \
  544.192, 34.86 to \
  544.192, 34.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1488 polygon from \
  544.236, 34.8701 to \
  544.241, 34.8701 to \
  544.241, 34.87 to \
  544.236, 34.87 to \
  544.236, 34.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1489 polygon from \
  544.28, 34.8801 to \
  544.286, 34.8801 to \
  544.286, 34.88 to \
  544.28, 34.88 to \
  544.28, 34.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1490 polygon from \
  544.324, 34.8901 to \
  544.33, 34.8901 to \
  544.33, 34.89 to \
  544.324, 34.89 to \
  544.324, 34.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1491 polygon from \
  544.369, 34.9001 to \
  544.374, 34.9001 to \
  544.374, 34.9 to \
  544.369, 34.9 to \
  544.369, 34.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1492 polygon from \
  544.413, 34.9101 to \
  544.419, 34.9101 to \
  544.419, 34.91 to \
  544.413, 34.91 to \
  544.413, 34.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1493 polygon from \
  544.457, 34.9201 to \
  544.463, 34.9201 to \
  544.463, 34.92 to \
  544.457, 34.92 to \
  544.457, 34.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1494 polygon from \
  544.502, 34.9301 to \
  544.508, 34.9301 to \
  544.508, 34.93 to \
  544.502, 34.93 to \
  544.502, 34.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1495 polygon from \
  544.546, 34.9401 to \
  544.552, 34.9401 to \
  544.552, 34.94 to \
  544.546, 34.94 to \
  544.546, 34.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1496 polygon from \
  544.591, 34.9501 to \
  544.597, 34.9501 to \
  544.597, 34.95 to \
  544.591, 34.95 to \
  544.591, 34.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1497 polygon from \
  544.636, 34.9601 to \
  544.641, 34.9601 to \
  544.641, 34.96 to \
  544.636, 34.96 to \
  544.636, 34.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1498 polygon from \
  544.68, 34.9701 to \
  544.686, 34.9701 to \
  544.686, 34.97 to \
  544.68, 34.97 to \
  544.68, 34.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1499 polygon from \
  544.725, 34.9801 to \
  544.731, 34.9801 to \
  544.731, 34.98 to \
  544.725, 34.98 to \
  544.725, 34.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1500 polygon from \
  544.77, 34.9901 to \
  544.775, 34.9901 to \
  544.775, 34.99 to \
  544.77, 34.99 to \
  544.77, 34.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1501 polygon from \
  544.815, 35.0001 to \
  544.82, 35.0001 to \
  544.82, 35 to \
  544.815, 35 to \
  544.815, 35.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1502 polygon from \
  544.859, 35.0101 to \
  544.865, 35.0101 to \
  544.865, 35.01 to \
  544.859, 35.01 to \
  544.859, 35.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1503 polygon from \
  544.904, 35.0201 to \
  544.91, 35.0201 to \
  544.91, 35.02 to \
  544.904, 35.02 to \
  544.904, 35.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1504 polygon from \
  544.949, 35.0301 to \
  544.955, 35.0301 to \
  544.955, 35.03 to \
  544.949, 35.03 to \
  544.949, 35.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1505 polygon from \
  544.994, 35.0401 to \
  545, 35.0401 to \
  545, 35.04 to \
  544.994, 35.04 to \
  544.994, 35.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1506 polygon from \
  545.039, 35.0501 to \
  545.045, 35.0501 to \
  545.045, 35.05 to \
  545.039, 35.05 to \
  545.039, 35.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1507 polygon from \
  545.084, 35.0601 to \
  545.09, 35.0601 to \
  545.09, 35.06 to \
  545.084, 35.06 to \
  545.084, 35.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1508 polygon from \
  545.129, 35.0701 to \
  545.135, 35.0701 to \
  545.135, 35.07 to \
  545.129, 35.07 to \
  545.129, 35.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1509 polygon from \
  545.175, 35.0801 to \
  545.18, 35.0801 to \
  545.18, 35.08 to \
  545.175, 35.08 to \
  545.175, 35.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1510 polygon from \
  545.22, 35.0901 to \
  545.225, 35.0901 to \
  545.225, 35.09 to \
  545.22, 35.09 to \
  545.22, 35.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1511 polygon from \
  545.265, 35.1001 to \
  545.271, 35.1001 to \
  545.271, 35.1 to \
  545.265, 35.1 to \
  545.265, 35.1001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1512 polygon from \
  545.31, 35.1101 to \
  545.316, 35.1101 to \
  545.316, 35.11 to \
  545.31, 35.11 to \
  545.31, 35.1101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1513 polygon from \
  545.356, 35.1201 to \
  545.361, 35.1201 to \
  545.361, 35.12 to \
  545.356, 35.12 to \
  545.356, 35.1201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1514 polygon from \
  545.401, 35.1301 to \
  545.407, 35.1301 to \
  545.407, 35.13 to \
  545.401, 35.13 to \
  545.401, 35.1301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1515 polygon from \
  545.446, 35.1401 to \
  545.452, 35.1401 to \
  545.452, 35.14 to \
  545.446, 35.14 to \
  545.446, 35.1401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1516 polygon from \
  545.492, 35.1501 to \
  545.498, 35.1501 to \
  545.498, 35.15 to \
  545.492, 35.15 to \
  545.492, 35.1501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1517 polygon from \
  545.537, 35.1601 to \
  545.543, 35.1601 to \
  545.543, 35.16 to \
  545.537, 35.16 to \
  545.537, 35.1601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1518 polygon from \
  545.583, 35.1701 to \
  545.589, 35.1701 to \
  545.589, 35.17 to \
  545.583, 35.17 to \
  545.583, 35.1701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1519 polygon from \
  545.629, 35.1801 to \
  545.634, 35.1801 to \
  545.634, 35.18 to \
  545.629, 35.18 to \
  545.629, 35.1801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1520 polygon from \
  545.674, 35.1901 to \
  545.68, 35.1901 to \
  545.68, 35.19 to \
  545.674, 35.19 to \
  545.674, 35.1901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1521 polygon from \
  545.72, 35.2001 to \
  545.726, 35.2001 to \
  545.726, 35.2 to \
  545.72, 35.2 to \
  545.72, 35.2001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1522 polygon from \
  545.766, 35.2101 to \
  545.771, 35.2101 to \
  545.771, 35.21 to \
  545.766, 35.21 to \
  545.766, 35.2101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1523 polygon from \
  545.811, 35.2201 to \
  545.817, 35.2201 to \
  545.817, 35.22 to \
  545.811, 35.22 to \
  545.811, 35.2201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1524 polygon from \
  545.857, 35.2301 to \
  545.863, 35.2301 to \
  545.863, 35.23 to \
  545.857, 35.23 to \
  545.857, 35.2301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1525 polygon from \
  545.903, 35.2401 to \
  545.909, 35.2401 to \
  545.909, 35.24 to \
  545.903, 35.24 to \
  545.903, 35.2401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1526 polygon from \
  545.949, 35.2501 to \
  545.955, 35.2501 to \
  545.955, 35.25 to \
  545.949, 35.25 to \
  545.949, 35.2501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1527 polygon from \
  545.995, 35.2601 to \
  546.001, 35.2601 to \
  546.001, 35.26 to \
  545.995, 35.26 to \
  545.995, 35.2601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1528 polygon from \
  546.041, 35.2701 to \
  546.047, 35.2701 to \
  546.047, 35.27 to \
  546.041, 35.27 to \
  546.041, 35.2701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1529 polygon from \
  546.087, 35.2801 to \
  546.093, 35.2801 to \
  546.093, 35.28 to \
  546.087, 35.28 to \
  546.087, 35.2801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1530 polygon from \
  546.133, 35.2901 to \
  546.139, 35.2901 to \
  546.139, 35.29 to \
  546.133, 35.29 to \
  546.133, 35.2901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1531 polygon from \
  546.179, 35.3001 to \
  546.185, 35.3001 to \
  546.185, 35.3 to \
  546.179, 35.3 to \
  546.179, 35.3001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1532 polygon from \
  546.226, 35.3101 to \
  546.231, 35.3101 to \
  546.231, 35.31 to \
  546.226, 35.31 to \
  546.226, 35.3101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1533 polygon from \
  546.272, 35.3201 to \
  546.278, 35.3201 to \
  546.278, 35.32 to \
  546.272, 35.32 to \
  546.272, 35.3201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1534 polygon from \
  546.318, 35.3301 to \
  546.324, 35.3301 to \
  546.324, 35.33 to \
  546.318, 35.33 to \
  546.318, 35.3301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1535 polygon from \
  546.364, 35.3401 to \
  546.37, 35.3401 to \
  546.37, 35.34 to \
  546.364, 35.34 to \
  546.364, 35.3401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1536 polygon from \
  546.411, 35.3501 to \
  546.417, 35.3501 to \
  546.417, 35.35 to \
  546.411, 35.35 to \
  546.411, 35.3501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1537 polygon from \
  546.457, 35.3601 to \
  546.463, 35.3601 to \
  546.463, 35.36 to \
  546.457, 35.36 to \
  546.457, 35.3601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1538 polygon from \
  546.504, 35.3701 to \
  546.51, 35.3701 to \
  546.51, 35.37 to \
  546.504, 35.37 to \
  546.504, 35.3701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1539 polygon from \
  546.55, 35.3801 to \
  546.556, 35.3801 to \
  546.556, 35.38 to \
  546.55, 35.38 to \
  546.55, 35.3801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1540 polygon from \
  546.597, 35.3901 to \
  546.603, 35.3901 to \
  546.603, 35.39 to \
  546.597, 35.39 to \
  546.597, 35.3901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1541 polygon from \
  546.643, 35.4001 to \
  546.649, 35.4001 to \
  546.649, 35.4 to \
  546.643, 35.4 to \
  546.643, 35.4001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1542 polygon from \
  546.69, 35.4101 to \
  546.696, 35.4101 to \
  546.696, 35.41 to \
  546.69, 35.41 to \
  546.69, 35.4101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1543 polygon from \
  546.737, 35.4201 to \
  546.743, 35.4201 to \
  546.743, 35.42 to \
  546.737, 35.42 to \
  546.737, 35.4201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1544 polygon from \
  546.784, 35.4301 to \
  546.79, 35.4301 to \
  546.79, 35.43 to \
  546.784, 35.43 to \
  546.784, 35.4301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1545 polygon from \
  546.83, 35.4401 to \
  546.836, 35.4401 to \
  546.836, 35.44 to \
  546.83, 35.44 to \
  546.83, 35.4401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1546 polygon from \
  546.877, 35.4501 to \
  546.883, 35.4501 to \
  546.883, 35.45 to \
  546.877, 35.45 to \
  546.877, 35.4501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1547 polygon from \
  546.924, 35.4601 to \
  546.93, 35.4601 to \
  546.93, 35.46 to \
  546.924, 35.46 to \
  546.924, 35.4601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1548 polygon from \
  546.971, 35.4701 to \
  546.977, 35.4701 to \
  546.977, 35.47 to \
  546.971, 35.47 to \
  546.971, 35.4701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1549 polygon from \
  547.018, 35.4801 to \
  547.024, 35.4801 to \
  547.024, 35.48 to \
  547.018, 35.48 to \
  547.018, 35.4801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1550 polygon from \
  547.065, 35.4901 to \
  547.071, 35.4901 to \
  547.071, 35.49 to \
  547.065, 35.49 to \
  547.065, 35.4901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1551 polygon from \
  547.112, 35.5001 to \
  547.118, 35.5001 to \
  547.118, 35.5 to \
  547.112, 35.5 to \
  547.112, 35.5001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1552 polygon from \
  547.159, 35.5101 to \
  547.165, 35.5101 to \
  547.165, 35.51 to \
  547.159, 35.51 to \
  547.159, 35.5101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1553 polygon from \
  547.207, 35.5201 to \
  547.213, 35.5201 to \
  547.213, 35.52 to \
  547.207, 35.52 to \
  547.207, 35.5201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1554 polygon from \
  547.254, 35.5301 to \
  547.26, 35.5301 to \
  547.26, 35.53 to \
  547.254, 35.53 to \
  547.254, 35.5301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1555 polygon from \
  547.301, 35.5401 to \
  547.307, 35.5401 to \
  547.307, 35.54 to \
  547.301, 35.54 to \
  547.301, 35.5401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1556 polygon from \
  547.348, 35.5501 to \
  547.354, 35.5501 to \
  547.354, 35.55 to \
  547.348, 35.55 to \
  547.348, 35.5501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1557 polygon from \
  547.396, 35.5601 to \
  547.402, 35.5601 to \
  547.402, 35.56 to \
  547.396, 35.56 to \
  547.396, 35.5601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1558 polygon from \
  547.443, 35.5701 to \
  547.449, 35.5701 to \
  547.449, 35.57 to \
  547.443, 35.57 to \
  547.443, 35.5701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1559 polygon from \
  547.491, 35.5801 to \
  547.497, 35.5801 to \
  547.497, 35.58 to \
  547.491, 35.58 to \
  547.491, 35.5801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1560 polygon from \
  547.538, 35.5901 to \
  547.544, 35.5901 to \
  547.544, 35.59 to \
  547.538, 35.59 to \
  547.538, 35.5901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1561 polygon from \
  547.586, 35.6001 to \
  547.592, 35.6001 to \
  547.592, 35.6 to \
  547.586, 35.6 to \
  547.586, 35.6001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1562 polygon from \
  547.633, 35.6101 to \
  547.639, 35.6101 to \
  547.639, 35.61 to \
  547.633, 35.61 to \
  547.633, 35.6101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1563 polygon from \
  547.681, 35.6201 to \
  547.687, 35.6201 to \
  547.687, 35.62 to \
  547.681, 35.62 to \
  547.681, 35.6201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1564 polygon from \
  547.729, 35.6301 to \
  547.735, 35.6301 to \
  547.735, 35.63 to \
  547.729, 35.63 to \
  547.729, 35.6301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1565 polygon from \
  547.776, 35.6401 to \
  547.782, 35.6401 to \
  547.782, 35.64 to \
  547.776, 35.64 to \
  547.776, 35.6401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1566 polygon from \
  547.824, 35.6501 to \
  547.83, 35.6501 to \
  547.83, 35.65 to \
  547.824, 35.65 to \
  547.824, 35.6501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1567 polygon from \
  547.872, 35.6601 to \
  547.878, 35.6601 to \
  547.878, 35.66 to \
  547.872, 35.66 to \
  547.872, 35.6601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1568 polygon from \
  547.92, 35.6701 to \
  547.926, 35.6701 to \
  547.926, 35.67 to \
  547.92, 35.67 to \
  547.92, 35.6701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1569 polygon from \
  547.968, 35.6801 to \
  547.974, 35.6801 to \
  547.974, 35.68 to \
  547.968, 35.68 to \
  547.968, 35.6801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1570 polygon from \
  548.016, 35.6901 to \
  548.022, 35.6901 to \
  548.022, 35.69 to \
  548.016, 35.69 to \
  548.016, 35.6901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1571 polygon from \
  548.064, 35.7001 to \
  548.07, 35.7001 to \
  548.07, 35.7 to \
  548.064, 35.7 to \
  548.064, 35.7001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1572 polygon from \
  548.112, 35.7101 to \
  548.118, 35.7101 to \
  548.118, 35.71 to \
  548.112, 35.71 to \
  548.112, 35.7101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1573 polygon from \
  548.16, 35.7201 to \
  548.166, 35.7201 to \
  548.166, 35.72 to \
  548.16, 35.72 to \
  548.16, 35.7201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1574 polygon from \
  548.208, 35.7301 to \
  548.214, 35.7301 to \
  548.214, 35.73 to \
  548.208, 35.73 to \
  548.208, 35.7301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1575 polygon from \
  548.257, 35.7401 to \
  548.263, 35.7401 to \
  548.263, 35.74 to \
  548.257, 35.74 to \
  548.257, 35.7401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1576 polygon from \
  548.305, 35.7501 to \
  548.311, 35.7501 to \
  548.311, 35.75 to \
  548.305, 35.75 to \
  548.305, 35.7501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1577 polygon from \
  548.353, 35.7601 to \
  548.359, 35.7601 to \
  548.359, 35.76 to \
  548.353, 35.76 to \
  548.353, 35.7601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1578 polygon from \
  548.402, 35.7701 to \
  548.408, 35.7701 to \
  548.408, 35.77 to \
  548.402, 35.77 to \
  548.402, 35.7701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1579 polygon from \
  548.45, 35.7801 to \
  548.456, 35.7801 to \
  548.456, 35.78 to \
  548.45, 35.78 to \
  548.45, 35.7801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1580 polygon from \
  548.498, 35.7901 to \
  548.505, 35.7901 to \
  548.505, 35.79 to \
  548.498, 35.79 to \
  548.498, 35.7901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1581 polygon from \
  548.547, 35.8001 to \
  548.553, 35.8001 to \
  548.553, 35.8 to \
  548.547, 35.8 to \
  548.547, 35.8001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1582 polygon from \
  548.596, 35.8101 to \
  548.602, 35.8101 to \
  548.602, 35.81 to \
  548.596, 35.81 to \
  548.596, 35.8101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1583 polygon from \
  548.644, 35.8201 to \
  548.65, 35.8201 to \
  548.65, 35.82 to \
  548.644, 35.82 to \
  548.644, 35.8201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1584 polygon from \
  548.693, 35.8301 to \
  548.699, 35.8301 to \
  548.699, 35.83 to \
  548.693, 35.83 to \
  548.693, 35.8301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1585 polygon from \
  548.742, 35.8401 to \
  548.748, 35.8401 to \
  548.748, 35.84 to \
  548.742, 35.84 to \
  548.742, 35.8401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1586 polygon from \
  548.79, 35.8501 to \
  548.796, 35.8501 to \
  548.796, 35.85 to \
  548.79, 35.85 to \
  548.79, 35.8501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1587 polygon from \
  548.839, 35.8601 to \
  548.845, 35.8601 to \
  548.845, 35.86 to \
  548.839, 35.86 to \
  548.839, 35.8601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1588 polygon from \
  548.888, 35.8701 to \
  548.894, 35.8701 to \
  548.894, 35.87 to \
  548.888, 35.87 to \
  548.888, 35.8701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1589 polygon from \
  548.937, 35.8801 to \
  548.943, 35.8801 to \
  548.943, 35.88 to \
  548.937, 35.88 to \
  548.937, 35.8801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1590 polygon from \
  548.986, 35.8901 to \
  548.992, 35.8901 to \
  548.992, 35.89 to \
  548.986, 35.89 to \
  548.986, 35.8901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1591 polygon from \
  549.035, 35.9001 to \
  549.041, 35.9001 to \
  549.041, 35.9 to \
  549.035, 35.9 to \
  549.035, 35.9001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1592 polygon from \
  549.084, 35.9101 to \
  549.09, 35.9101 to \
  549.09, 35.91 to \
  549.084, 35.91 to \
  549.084, 35.9101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1593 polygon from \
  549.133, 35.9201 to \
  549.139, 35.9201 to \
  549.139, 35.92 to \
  549.133, 35.92 to \
  549.133, 35.9201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1594 polygon from \
  549.182, 35.9301 to \
  549.188, 35.9301 to \
  549.188, 35.93 to \
  549.182, 35.93 to \
  549.182, 35.9301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1595 polygon from \
  549.231, 35.9401 to \
  549.238, 35.9401 to \
  549.238, 35.94 to \
  549.231, 35.94 to \
  549.231, 35.9401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1596 polygon from \
  549.281, 35.9501 to \
  549.287, 35.9501 to \
  549.287, 35.95 to \
  549.281, 35.95 to \
  549.281, 35.9501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1597 polygon from \
  549.33, 35.9601 to \
  549.336, 35.9601 to \
  549.336, 35.96 to \
  549.33, 35.96 to \
  549.33, 35.9601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1598 polygon from \
  549.379, 35.9701 to \
  549.386, 35.9701 to \
  549.386, 35.97 to \
  549.379, 35.97 to \
  549.379, 35.9701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1599 polygon from \
  549.429, 35.9801 to \
  549.435, 35.9801 to \
  549.435, 35.98 to \
  549.429, 35.98 to \
  549.429, 35.9801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1600 polygon from \
  549.478, 35.9901 to \
  549.484, 35.9901 to \
  549.484, 35.99 to \
  549.478, 35.99 to \
  549.478, 35.9901 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1601 polygon from \
  549.528, 36.0001 to \
  549.534, 36.0001 to \
  549.534, 36 to \
  549.528, 36 to \
  549.528, 36.0001 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1602 polygon from \
  549.577, 36.0101 to \
  549.584, 36.0101 to \
  549.584, 36.01 to \
  549.577, 36.01 to \
  549.577, 36.0101 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1603 polygon from \
  549.627, 36.0201 to \
  549.633, 36.0201 to \
  549.633, 36.02 to \
  549.627, 36.02 to \
  549.627, 36.0201 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1604 polygon from \
  549.677, 36.0301 to \
  549.683, 36.0301 to \
  549.683, 36.03 to \
  549.677, 36.03 to \
  549.677, 36.0301 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1605 polygon from \
  549.726, 36.0401 to \
  549.732, 36.0401 to \
  549.732, 36.04 to \
  549.726, 36.04 to \
  549.726, 36.0401 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1606 polygon from \
  549.776, 36.0501 to \
  549.782, 36.0501 to \
  549.782, 36.05 to \
  549.776, 36.05 to \
  549.776, 36.0501 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1607 polygon from \
  549.826, 36.0601 to \
  549.832, 36.0601 to \
  549.832, 36.06 to \
  549.826, 36.06 to \
  549.826, 36.0601 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1608 polygon from \
  549.876, 36.0701 to \
  549.882, 36.0701 to \
  549.882, 36.07 to \
  549.876, 36.07 to \
  549.876, 36.0701 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1609 polygon from \
  549.926, 36.0801 to \
  549.932, 36.0801 to \
  549.932, 36.08 to \
  549.926, 36.08 to \
  549.926, 36.0801 front fs empty border lc rgb '#57ab27' lw 0.200001
set object 1610 polygon from \
  549.975, 36.0901 to \
  549.982, 36.0901 to \
  549.982, 36.09 to \
  549.975, 36.09 to \
  549.975, 36.0901 front fs empty border lc rgb '#57ab27' lw 0.200001
plot [506.002:553.98] [18.391:37.6991] NaN notitle 

