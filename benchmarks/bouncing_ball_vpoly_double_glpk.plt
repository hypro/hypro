# settings
set term pdf font ',10'
set output "bouncing_ball_vpoly_double_glpk.pdf
set xtics autofreq
set ytics autofreq
set grid back
# axis settings
set xzeroaxis
set zeroaxis
set xtics axis
set xrange [-16.5984:13.0669]
set yzeroaxis
set ytics axis
set yrange [-1.02004:11.2204]

# plotting sets
set object 1 polygon from \
  -0.098223, 10.1999 to \
  -0.000123034, 10.2004 to \
  0.000123034, 10.2004 to \
  0.000123034, 9.99963 to \
  -0.097977, 9.99914 to \
  -0.098223, 9.99914 to \
  -0.098223, 10.1999 front fs empty border lc rgb '#6165' lw 0.2
set object 2 polygon from \
  -0.196323, 10.1984 to \
  -0.098223, 10.1999 to \
  -0.097977, 10.1999 to \
  -0.097977, 9.99914 to \
  -0.196077, 9.99767 to \
  -0.196323, 9.99767 to \
  -0.196323, 10.1984 front fs empty border lc rgb '#6165' lw 0.2
set object 3 polygon from \
  -0.294423, 10.196 to \
  -0.196323, 10.1984 to \
  -0.196077, 10.1984 to \
  -0.196077, 9.99767 to \
  -0.294177, 9.99522 to \
  -0.294423, 9.99521 to \
  -0.294423, 10.196 front fs empty border lc rgb '#6165' lw 0.2
set object 4 polygon from \
  -0.392523, 10.1925 to \
  -0.294423, 10.196 to \
  -0.294177, 10.196 to \
  -0.294177, 9.99522 to \
  -0.392277, 9.99179 to \
  -0.392523, 9.99178 to \
  -0.392523, 10.1925 front fs empty border lc rgb '#6165' lw 0.2
set object 5 polygon from \
  -0.490623, 10.1881 to \
  -0.392523, 10.1925 to \
  -0.392277, 10.1925 to \
  -0.392277, 9.99179 to \
  -0.490377, 9.98737 to \
  -0.490623, 9.98736 to \
  -0.490623, 10.1881 front fs empty border lc rgb '#6165' lw 0.2
set object 6 polygon from \
  -0.588723, 10.1827 to \
  -0.490623, 10.1881 to \
  -0.490377, 10.1881 to \
  -0.490377, 9.98738 to \
  -0.588477, 9.98198 to \
  -0.588723, 9.98197 to \
  -0.588723, 10.1827 front fs empty border lc rgb '#6165' lw 0.2
set object 7 polygon from \
  -0.686823, 10.1763 to \
  -0.588723, 10.1827 to \
  -0.588477, 10.1827 to \
  -0.588477, 9.98198 to \
  -0.686577, 9.9756 to \
  -0.686823, 9.97559 to \
  -0.686823, 10.1763 front fs empty border lc rgb '#6165' lw 0.2
set object 8 polygon from \
  -0.784923, 10.169 to \
  -0.686823, 10.1763 to \
  -0.686577, 10.1763 to \
  -0.686577, 9.97561 to \
  -0.784677, 9.96825 to \
  -0.784923, 9.96823 to \
  -0.784923, 10.169 front fs empty border lc rgb '#6165' lw 0.2
set object 9 polygon from \
  -0.883023, 10.1606 to \
  -0.784923, 10.169 to \
  -0.784677, 10.169 to \
  -0.784677, 9.96825 to \
  -0.882777, 9.95991 to \
  -0.883023, 9.95989 to \
  -0.883023, 10.1606 front fs empty border lc rgb '#6165' lw 0.2
set object 10 polygon from \
  -0.981123, 10.1513 to \
  -0.883023, 10.1606 to \
  -0.882777, 10.1606 to \
  -0.882777, 9.95991 to \
  -0.980877, 9.95059 to \
  -0.981123, 9.95057 to \
  -0.981123, 10.1513 front fs empty border lc rgb '#6165' lw 0.2
set object 11 polygon from \
  -1.07922, 10.141 to \
  -0.981123, 10.1513 to \
  -0.980877, 10.1513 to \
  -0.980877, 9.95059 to \
  -1.07898, 9.94029 to \
  -1.07922, 9.94027 to \
  -1.07922, 10.141 front fs empty border lc rgb '#6165' lw 0.2
set object 12 polygon from \
  -1.17732, 10.1297 to \
  -1.07922, 10.141 to \
  -1.07898, 10.141 to \
  -1.07898, 9.94029 to \
  -1.17708, 9.92901 to \
  -1.17732, 9.92899 to \
  -1.17732, 10.1297 front fs empty border lc rgb '#6165' lw 0.2
set object 13 polygon from \
  -1.27542, 10.1175 to \
  -1.17732, 10.1297 to \
  -1.17708, 10.1298 to \
  -1.17708, 9.92901 to \
  -1.27518, 9.91675 to \
  -1.27542, 9.91672 to \
  -1.27542, 10.1175 front fs empty border lc rgb '#6165' lw 0.2
set object 14 polygon from \
  -1.37352, 10.1042 to \
  -1.27542, 10.1175 to \
  -1.27518, 10.1175 to \
  -1.27518, 9.91675 to \
  -1.37328, 9.90351 to \
  -1.37352, 9.90348 to \
  -1.37352, 10.1042 front fs empty border lc rgb '#6165' lw 0.2
set object 15 polygon from \
  -1.47162, 10.09 to \
  -1.37352, 10.1042 to \
  -1.37328, 10.1042 to \
  -1.37328, 9.90351 to \
  -1.47138, 9.88929 to \
  -1.47162, 9.88925 to \
  -1.47162, 10.09 front fs empty border lc rgb '#6165' lw 0.2
set object 16 polygon from \
  -1.56972, 10.0748 to \
  -1.47162, 10.09 to \
  -1.47138, 10.09 to \
  -1.47138, 9.88929 to \
  -1.56948, 9.87408 to \
  -1.56972, 9.87405 to \
  -1.56972, 10.0748 front fs empty border lc rgb '#6165' lw 0.2
set object 17 polygon from \
  -1.66782, 10.0586 to \
  -1.56972, 10.0748 to \
  -1.56948, 10.0748 to \
  -1.56948, 9.87408 to \
  -1.66758, 9.8579 to \
  -1.66782, 9.85786 to \
  -1.66782, 10.0586 front fs empty border lc rgb '#6165' lw 0.2
set object 18 polygon from \
  -1.76592, 10.0414 to \
  -1.66782, 10.0586 to \
  -1.66758, 10.0586 to \
  -1.66758, 9.8579 to \
  -1.76568, 9.84073 to \
  -1.76592, 9.84069 to \
  -1.76592, 10.0414 front fs empty border lc rgb '#6165' lw 0.2
set object 19 polygon from \
  -1.86402, 10.0233 to \
  -1.76592, 10.0414 to \
  -1.76568, 10.0415 to \
  -1.76568, 9.84073 to \
  -1.86378, 9.82258 to \
  -1.86402, 9.82254 to \
  -1.86402, 10.0233 front fs empty border lc rgb '#6165' lw 0.2
set object 20 polygon from \
  -1.96212, 10.0041 to \
  -1.86402, 10.0233 to \
  -1.86378, 10.0233 to \
  -1.86378, 9.82258 to \
  -1.96188, 9.80346 to \
  -1.96212, 9.80341 to \
  -1.96212, 10.0041 front fs empty border lc rgb '#6165' lw 0.2
set object 21 polygon from \
  -2.06022, 9.98403 to \
  -1.96212, 10.0041 to \
  -1.96188, 10.0042 to \
  -1.96188, 9.80346 to \
  -2.05998, 9.78335 to \
  -2.06022, 9.7833 to \
  -2.06022, 9.98403 front fs empty border lc rgb '#6165' lw 0.2
set object 22 polygon from \
  -2.15832, 9.96294 to \
  -2.06022, 9.98403 to \
  -2.05998, 9.98408 to \
  -2.05998, 9.78335 to \
  -2.15808, 9.76226 to \
  -2.15832, 9.7622 to \
  -2.15832, 9.96294 front fs empty border lc rgb '#6165' lw 0.2
set object 23 polygon from \
  -2.25642, 9.94087 to \
  -2.15832, 9.96294 to \
  -2.15808, 9.96299 to \
  -2.15808, 9.76226 to \
  -2.25618, 9.74018 to \
  -2.25642, 9.74013 to \
  -2.25642, 9.94087 front fs empty border lc rgb '#6165' lw 0.2
set object 24 polygon from \
  -2.35452, 9.91781 to \
  -2.25642, 9.94087 to \
  -2.25618, 9.94092 to \
  -2.25618, 9.74019 to \
  -2.35428, 9.71713 to \
  -2.35452, 9.71708 to \
  -2.35452, 9.91781 front fs empty border lc rgb '#6165' lw 0.2
set object 25 polygon from \
  -2.45262, 9.89378 to \
  -2.35452, 9.91781 to \
  -2.35428, 9.91787 to \
  -2.35428, 9.71713 to \
  -2.45238, 9.6931 to \
  -2.45262, 9.69304 to \
  -2.45262, 9.89378 front fs empty border lc rgb '#6165' lw 0.2
set object 26 polygon from \
  -2.55072, 9.86876 to \
  -2.45262, 9.89378 to \
  -2.45238, 9.89384 to \
  -2.45238, 9.6931 to \
  -2.55048, 9.66808 to \
  -2.55072, 9.66802 to \
  -2.55072, 9.86876 front fs empty border lc rgb '#6165' lw 0.2
set object 27 polygon from \
  -2.64882, 9.84276 to \
  -2.55072, 9.86876 to \
  -2.55048, 9.86882 to \
  -2.55048, 9.66809 to \
  -2.64858, 9.64209 to \
  -2.64882, 9.64203 to \
  -2.64882, 9.84276 front fs empty border lc rgb '#6165' lw 0.2
set object 28 polygon from \
  -2.74692, 9.81578 to \
  -2.64882, 9.84276 to \
  -2.64858, 9.84283 to \
  -2.64858, 9.64209 to \
  -2.74668, 9.61511 to \
  -2.74692, 9.61505 to \
  -2.74692, 9.81578 front fs empty border lc rgb '#6165' lw 0.2
set object 29 polygon from \
  -2.84502, 9.78782 to \
  -2.74692, 9.81578 to \
  -2.74668, 9.81585 to \
  -2.74668, 9.61511 to \
  -2.84478, 9.58716 to \
  -2.84502, 9.58709 to \
  -2.84502, 9.78782 front fs empty border lc rgb '#6165' lw 0.2
set object 30 polygon from \
  -2.94312, 9.75888 to \
  -2.84502, 9.78782 to \
  -2.84478, 9.78789 to \
  -2.84478, 9.58716 to \
  -2.94288, 9.55822 to \
  -2.94312, 9.55815 to \
  -2.94312, 9.75888 front fs empty border lc rgb '#6165' lw 0.2
set object 31 polygon from \
  -3.04122, 9.72896 to \
  -2.94312, 9.75888 to \
  -2.94288, 9.75896 to \
  -2.94288, 9.55822 to \
  -3.04098, 9.5283 to \
  -3.04122, 9.52822 to \
  -3.04122, 9.72896 front fs empty border lc rgb '#6165' lw 0.2
set object 32 polygon from \
  -3.13932, 9.69806 to \
  -3.04122, 9.72896 to \
  -3.04098, 9.72904 to \
  -3.04098, 9.5283 to \
  -3.13908, 9.4974 to \
  -3.13932, 9.49732 to \
  -3.13932, 9.69806 front fs empty border lc rgb '#6165' lw 0.2
set object 33 polygon from \
  -3.23742, 9.66617 to \
  -3.13932, 9.69806 to \
  -3.13908, 9.69814 to \
  -3.13908, 9.4974 to \
  -3.23718, 9.46552 to \
  -3.23742, 9.46544 to \
  -3.23742, 9.66617 front fs empty border lc rgb '#6165' lw 0.2
set object 34 polygon from \
  -3.33552, 9.63331 to \
  -3.23742, 9.66617 to \
  -3.23718, 9.66625 to \
  -3.23718, 9.46552 to \
  -3.33528, 9.43265 to \
  -3.33552, 9.43257 to \
  -3.33552, 9.63331 front fs empty border lc rgb '#6165' lw 0.2
set object 35 polygon from \
  -3.43362, 9.59946 to \
  -3.33552, 9.63331 to \
  -3.33528, 9.63339 to \
  -3.33528, 9.43266 to \
  -3.43338, 9.39881 to \
  -3.43362, 9.39873 to \
  -3.43362, 9.59946 front fs empty border lc rgb '#6165' lw 0.2
set object 36 polygon from \
  -3.53172, 9.56464 to \
  -3.43362, 9.59946 to \
  -3.43338, 9.59955 to \
  -3.43338, 9.39881 to \
  -3.53148, 9.36399 to \
  -3.53172, 9.3639 to \
  -3.53172, 9.56464 front fs empty border lc rgb '#6165' lw 0.2
set object 37 polygon from \
  -3.62982, 9.52883 to \
  -3.53172, 9.56464 to \
  -3.53148, 9.56472 to \
  -3.53148, 9.36399 to \
  -3.62958, 9.32818 to \
  -3.62982, 9.32809 to \
  -3.62982, 9.52883 front fs empty border lc rgb '#6165' lw 0.2
set object 38 polygon from \
  -3.72792, 9.49204 to \
  -3.62982, 9.52883 to \
  -3.62958, 9.52892 to \
  -3.62958, 9.32818 to \
  -3.72768, 9.2914 to \
  -3.72792, 9.2913 to \
  -3.72792, 9.49204 front fs empty border lc rgb '#6165' lw 0.2
set object 39 polygon from \
  -3.82602, 9.45427 to \
  -3.72792, 9.49204 to \
  -3.72768, 9.49213 to \
  -3.72768, 9.2914 to \
  -3.82578, 9.25363 to \
  -3.82602, 9.25353 to \
  -3.82602, 9.45427 front fs empty border lc rgb '#6165' lw 0.2
set object 40 polygon from \
  -3.92412, 9.41552 to \
  -3.82602, 9.45427 to \
  -3.82578, 9.45437 to \
  -3.82578, 9.25363 to \
  -3.92388, 9.21488 to \
  -3.92412, 9.21478 to \
  -3.92412, 9.41552 front fs empty border lc rgb '#6165' lw 0.2
set object 41 polygon from \
  -4.02222, 9.37579 to \
  -3.92412, 9.41552 to \
  -3.92388, 9.41562 to \
  -3.92388, 9.21488 to \
  -4.02198, 9.17515 to \
  -4.02222, 9.17505 to \
  -4.02222, 9.37579 front fs empty border lc rgb '#6165' lw 0.2
set object 42 polygon from \
  -4.12032, 9.33508 to \
  -4.02222, 9.37579 to \
  -4.02198, 9.37589 to \
  -4.02198, 9.17515 to \
  -4.12008, 9.13444 to \
  -4.12032, 9.13434 to \
  -4.12032, 9.33508 front fs empty border lc rgb '#6165' lw 0.2
set object 43 polygon from \
  -4.21842, 9.29338 to \
  -4.12032, 9.33507 to \
  -4.12008, 9.33518 to \
  -4.12008, 9.13444 to \
  -4.21818, 9.09275 to \
  -4.21842, 9.09265 to \
  -4.21842, 9.29338 front fs empty border lc rgb '#6165' lw 0.2
set object 44 polygon from \
  -4.31652, 9.25071 to \
  -4.21842, 9.29338 to \
  -4.21818, 9.29349 to \
  -4.21818, 9.09275 to \
  -4.31628, 9.05008 to \
  -4.31652, 9.04997 to \
  -4.31652, 9.25071 front fs empty border lc rgb '#6165' lw 0.2
set object 45 polygon from \
  -4.41462, 9.20705 to \
  -4.31652, 9.25071 to \
  -4.31628, 9.25081 to \
  -4.31628, 9.05008 to \
  -4.41438, 9.00642 to \
  -4.41462, 9.00632 to \
  -4.41462, 9.20705 front fs empty border lc rgb '#6165' lw 0.2
set object 46 polygon from \
  -4.51272, 9.16241 to \
  -4.41462, 9.20705 to \
  -4.41438, 9.20716 to \
  -4.41438, 9.00642 to \
  -4.51248, 8.96179 to \
  -4.51272, 8.96168 to \
  -4.51272, 9.16241 front fs empty border lc rgb '#6165' lw 0.2
set object 47 polygon from \
  -4.61082, 9.1168 to \
  -4.51272, 9.16241 to \
  -4.51248, 9.16253 to \
  -4.51248, 8.96179 to \
  -4.61058, 8.91617 to \
  -4.61082, 8.91606 to \
  -4.61082, 9.1168 front fs empty border lc rgb '#6165' lw 0.2
set object 48 polygon from \
  -4.70892, 9.0702 to \
  -4.61082, 9.1168 to \
  -4.61058, 9.11691 to \
  -4.61058, 8.91618 to \
  -4.70868, 8.86958 to \
  -4.70892, 8.86946 to \
  -4.70892, 9.0702 front fs empty border lc rgb '#6165' lw 0.2
set object 49 polygon from \
  -4.80702, 9.02262 to \
  -4.70892, 9.0702 to \
  -4.70868, 9.07032 to \
  -4.70868, 8.86958 to \
  -4.80678, 8.822 to \
  -4.80702, 8.82188 to \
  -4.80702, 9.02262 front fs empty border lc rgb '#6165' lw 0.2
set object 50 polygon from \
  -4.90512, 8.97406 to \
  -4.80702, 9.02262 to \
  -4.80678, 9.02274 to \
  -4.80678, 8.822 to \
  -4.90488, 8.77344 to \
  -4.90512, 8.77332 to \
  -4.90512, 8.97406 front fs empty border lc rgb '#6165' lw 0.2
set object 51 polygon from \
  -5.00322, 8.92452 to \
  -4.90512, 8.97406 to \
  -4.90488, 8.97418 to \
  -4.90488, 8.77344 to \
  -5.00298, 8.7239 to \
  -5.00322, 8.72378 to \
  -5.00322, 8.92452 front fs empty border lc rgb '#6165' lw 0.2
set object 52 polygon from \
  -5.10132, 8.87399 to \
  -5.00322, 8.92452 to \
  -5.00298, 8.92464 to \
  -5.00298, 8.7239 to \
  -5.10108, 8.67338 to \
  -5.10132, 8.67326 to \
  -5.10132, 8.87399 front fs empty border lc rgb '#6165' lw 0.2
set object 53 polygon from \
  -5.19942, 8.82249 to \
  -5.10132, 8.87399 to \
  -5.10108, 8.87412 to \
  -5.10108, 8.67338 to \
  -5.19918, 8.62188 to \
  -5.19942, 8.62175 to \
  -5.19942, 8.82249 front fs empty border lc rgb '#6165' lw 0.2
set object 54 polygon from \
  -5.29752, 8.77001 to \
  -5.19942, 8.82249 to \
  -5.19918, 8.82262 to \
  -5.19918, 8.62188 to \
  -5.29728, 8.5694 to \
  -5.29752, 8.56927 to \
  -5.29752, 8.77001 front fs empty border lc rgb '#6165' lw 0.2
set object 55 polygon from \
  -5.39562, 8.71654 to \
  -5.29752, 8.77 to \
  -5.29728, 8.77014 to \
  -5.29728, 8.5694 to \
  -5.39538, 8.51594 to \
  -5.39562, 8.5158 to \
  -5.39562, 8.71654 front fs empty border lc rgb '#6165' lw 0.2
set object 56 polygon from \
  -5.49372, 8.66209 to \
  -5.39562, 8.71654 to \
  -5.39538, 8.71667 to \
  -5.39538, 8.51594 to \
  -5.49348, 8.46149 to \
  -5.49372, 8.46136 to \
  -5.49372, 8.66209 front fs empty border lc rgb '#6165' lw 0.2
set object 57 polygon from \
  -5.59182, 8.60666 to \
  -5.49372, 8.66209 to \
  -5.49348, 8.66223 to \
  -5.49348, 8.46149 to \
  -5.59158, 8.40607 to \
  -5.59182, 8.40593 to \
  -5.59182, 8.60666 front fs empty border lc rgb '#6165' lw 0.2
set object 58 polygon from \
  -5.68992, 8.55026 to \
  -5.59182, 8.60666 to \
  -5.59158, 8.6068 to \
  -5.59158, 8.40607 to \
  -5.68968, 8.34966 to \
  -5.68992, 8.34952 to \
  -5.68992, 8.55026 front fs empty border lc rgb '#6165' lw 0.2
set object 59 polygon from \
  -5.78802, 8.49287 to \
  -5.68992, 8.55025 to \
  -5.68968, 8.5504 to \
  -5.68968, 8.34966 to \
  -5.78778, 8.29227 to \
  -5.78802, 8.29213 to \
  -5.78802, 8.49287 front fs empty border lc rgb '#6165' lw 0.2
set object 60 polygon from \
  -5.88612, 8.4345 to \
  -5.78802, 8.49287 to \
  -5.78778, 8.49301 to \
  -5.78778, 8.29227 to \
  -5.88588, 8.2339 to \
  -5.88612, 8.23376 to \
  -5.88612, 8.4345 front fs empty border lc rgb '#6165' lw 0.2
set object 61 polygon from \
  -5.98422, 8.37514 to \
  -5.88612, 8.43449 to \
  -5.88588, 8.43464 to \
  -5.88588, 8.23391 to \
  -5.98398, 8.17456 to \
  -5.98422, 8.17441 to \
  -5.98422, 8.37514 front fs empty border lc rgb '#6165' lw 0.2
set object 62 polygon from \
  -6.08232, 8.31481 to \
  -5.98422, 8.37514 to \
  -5.98398, 8.37529 to \
  -5.98398, 8.17456 to \
  -6.08208, 8.11422 to \
  -6.08232, 8.11407 to \
  -6.08232, 8.31481 front fs empty border lc rgb '#6165' lw 0.2
set object 63 polygon from \
  -6.18042, 8.2535 to \
  -6.08232, 8.31481 to \
  -6.08208, 8.31496 to \
  -6.08208, 8.11423 to \
  -6.18018, 8.05291 to \
  -6.18042, 8.05276 to \
  -6.18042, 8.2535 front fs empty border lc rgb '#6165' lw 0.2
set object 64 polygon from \
  -6.27852, 8.1912 to \
  -6.18042, 8.2535 to \
  -6.18018, 8.25365 to \
  -6.18018, 8.05291 to \
  -6.27828, 7.99062 to \
  -6.27852, 7.99047 to \
  -6.27852, 8.1912 front fs empty border lc rgb '#6165' lw 0.2
set object 65 polygon from \
  -6.37662, 8.12793 to \
  -6.27852, 8.1912 to \
  -6.27828, 8.19136 to \
  -6.27828, 7.99062 to \
  -6.37638, 7.92735 to \
  -6.37662, 7.92719 to \
  -6.37662, 8.12793 front fs empty border lc rgb '#6165' lw 0.2
set object 66 polygon from \
  -6.47472, 8.06367 to \
  -6.37662, 8.12793 to \
  -6.37638, 8.12809 to \
  -6.37638, 7.92735 to \
  -6.47448, 7.86309 to \
  -6.47472, 7.86293 to \
  -6.47472, 8.06367 front fs empty border lc rgb '#6165' lw 0.2
set object 67 polygon from \
  -6.57282, 7.99843 to \
  -6.47472, 8.06367 to \
  -6.47448, 8.06383 to \
  -6.47448, 7.86309 to \
  -6.57258, 7.79786 to \
  -6.57282, 7.7977 to \
  -6.57282, 7.99843 front fs empty border lc rgb '#6165' lw 0.2
set object 68 polygon from \
  -6.67092, 7.93221 to \
  -6.57282, 7.99843 to \
  -6.57258, 7.9986 to \
  -6.57258, 7.79786 to \
  -6.67068, 7.73164 to \
  -6.67092, 7.73148 to \
  -6.67092, 7.93221 front fs empty border lc rgb '#6165' lw 0.2
set object 69 polygon from \
  -6.76902, 7.86501 to \
  -6.67092, 7.93221 to \
  -6.67068, 7.93238 to \
  -6.67068, 7.73164 to \
  -6.76878, 7.66444 to \
  -6.76902, 7.66428 to \
  -6.76902, 7.86501 front fs empty border lc rgb '#6165' lw 0.2
set object 70 polygon from \
  -6.86712, 7.79683 to \
  -6.76902, 7.86501 to \
  -6.76878, 7.86518 to \
  -6.76878, 7.66445 to \
  -6.86688, 7.59627 to \
  -6.86712, 7.5961 to \
  -6.86712, 7.79683 front fs empty border lc rgb '#6165' lw 0.2
set object 71 polygon from \
  -6.96522, 7.72767 to \
  -6.86712, 7.79683 to \
  -6.86688, 7.797 to \
  -6.86688, 7.59627 to \
  -6.96498, 7.52711 to \
  -6.96522, 7.52694 to \
  -6.96522, 7.72767 front fs empty border lc rgb '#6165' lw 0.2
set object 72 polygon from \
  -7.06332, 7.65753 to \
  -6.96522, 7.72767 to \
  -6.96498, 7.72785 to \
  -6.96498, 7.52711 to \
  -7.06308, 7.45697 to \
  -7.06332, 7.45679 to \
  -7.06332, 7.65753 front fs empty border lc rgb '#6165' lw 0.2
set object 73 polygon from \
  -7.16142, 7.58641 to \
  -7.06332, 7.65753 to \
  -7.06308, 7.6577 to \
  -7.06308, 7.45697 to \
  -7.16118, 7.38585 to \
  -7.16142, 7.38567 to \
  -7.16142, 7.58641 front fs empty border lc rgb '#6165' lw 0.2
set object 74 polygon from \
  -7.25952, 7.5143 to \
  -7.16142, 7.5864 to \
  -7.16118, 7.58658 to \
  -7.16118, 7.38585 to \
  -7.25928, 7.31374 to \
  -7.25952, 7.31356 to \
  -7.25952, 7.5143 front fs empty border lc rgb '#6165' lw 0.2
set object 75 polygon from \
  -7.35762, 7.44121 to \
  -7.25952, 7.5143 to \
  -7.25928, 7.51448 to \
  -7.25928, 7.31374 to \
  -7.35738, 7.24066 to \
  -7.35762, 7.24048 to \
  -7.35762, 7.44121 front fs empty border lc rgb '#6165' lw 0.2
set object 76 polygon from \
  -7.45572, 7.36715 to \
  -7.35762, 7.44121 to \
  -7.35738, 7.4414 to \
  -7.35738, 7.24066 to \
  -7.45548, 7.1666 to \
  -7.45572, 7.16641 to \
  -7.45572, 7.36715 front fs empty border lc rgb '#6165' lw 0.2
set object 77 polygon from \
  -7.55382, 7.2921 to \
  -7.45572, 7.36715 to \
  -7.45548, 7.36733 to \
  -7.45548, 7.1666 to \
  -7.55358, 7.09155 to \
  -7.55382, 7.09136 to \
  -7.55382, 7.2921 front fs empty border lc rgb '#6165' lw 0.2
set object 78 polygon from \
  -7.65192, 7.21607 to \
  -7.55382, 7.2921 to \
  -7.55358, 7.29229 to \
  -7.55358, 7.09155 to \
  -7.65168, 7.01552 to \
  -7.65192, 7.01533 to \
  -7.65192, 7.21607 front fs empty border lc rgb '#6165' lw 0.2
set object 79 polygon from \
  -7.75002, 7.13906 to \
  -7.65192, 7.21607 to \
  -7.65168, 7.21626 to \
  -7.65168, 7.01553 to \
  -7.74978, 6.93852 to \
  -7.75002, 6.93833 to \
  -7.75002, 7.13906 front fs empty border lc rgb '#6165' lw 0.2
set object 80 polygon from \
  -7.84812, 7.06107 to \
  -7.75002, 7.13906 to \
  -7.74978, 7.13925 to \
  -7.74978, 6.93852 to \
  -7.84788, 6.86053 to \
  -7.84812, 6.86033 to \
  -7.84812, 7.06107 front fs empty border lc rgb '#6165' lw 0.2
set object 81 polygon from \
  -7.94622, 6.9821 to \
  -7.84812, 7.06107 to \
  -7.84788, 7.06127 to \
  -7.84788, 6.86053 to \
  -7.94598, 6.78156 to \
  -7.94622, 6.78136 to \
  -7.94622, 6.9821 front fs empty border lc rgb '#6165' lw 0.2
set object 82 polygon from \
  -8.04432, 6.90215 to \
  -7.94622, 6.9821 to \
  -7.94598, 6.9823 to \
  -7.94598, 6.78156 to \
  -8.04408, 6.70161 to \
  -8.04432, 6.70141 to \
  -8.04432, 6.90215 front fs empty border lc rgb '#6165' lw 0.2
set object 83 polygon from \
  -8.14242, 6.82121 to \
  -8.04432, 6.90215 to \
  -8.04408, 6.90235 to \
  -8.04408, 6.70161 to \
  -8.14218, 6.62068 to \
  -8.14242, 6.62048 to \
  -8.14242, 6.82121 front fs empty border lc rgb '#6165' lw 0.2
set object 84 polygon from \
  -8.24052, 6.7393 to \
  -8.14242, 6.82121 to \
  -8.14218, 6.82142 to \
  -8.14218, 6.62068 to \
  -8.24028, 6.53877 to \
  -8.24052, 6.53856 to \
  -8.24052, 6.7393 front fs empty border lc rgb '#6165' lw 0.2
set object 85 polygon from \
  -8.33862, 6.6564 to \
  -8.24052, 6.7393 to \
  -8.24028, 6.7395 to \
  -8.24028, 6.53877 to \
  -8.33838, 6.45587 to \
  -8.33862, 6.45567 to \
  -8.33862, 6.6564 front fs empty border lc rgb '#6165' lw 0.2
set object 86 polygon from \
  -8.43672, 6.57253 to \
  -8.33862, 6.6564 to \
  -8.33838, 6.65661 to \
  -8.33838, 6.45587 to \
  -8.43648, 6.372 to \
  -8.43672, 6.37179 to \
  -8.43672, 6.57253 front fs empty border lc rgb '#6165' lw 0.2
set object 87 polygon from \
  -8.53482, 6.48767 to \
  -8.43672, 6.57252 to \
  -8.43648, 6.57274 to \
  -8.43648, 6.372 to \
  -8.53458, 6.28714 to \
  -8.53482, 6.28693 to \
  -8.53482, 6.48767 front fs empty border lc rgb '#6165' lw 0.2
set object 88 polygon from \
  -8.63292, 6.40183 to \
  -8.53482, 6.48767 to \
  -8.53458, 6.48788 to \
  -8.53458, 6.28714 to \
  -8.63268, 6.20131 to \
  -8.63292, 6.20109 to \
  -8.63292, 6.40183 front fs empty border lc rgb '#6165' lw 0.2
set object 89 polygon from \
  -8.73102, 6.31501 to \
  -8.63292, 6.40183 to \
  -8.63268, 6.40204 to \
  -8.63268, 6.20131 to \
  -8.73078, 6.11449 to \
  -8.73102, 6.11427 to \
  -8.73102, 6.31501 front fs empty border lc rgb '#6165' lw 0.2
set object 90 polygon from \
  -8.82912, 6.22721 to \
  -8.73102, 6.31501 to \
  -8.73078, 6.31523 to \
  -8.73078, 6.11449 to \
  -8.82888, 6.02669 to \
  -8.82912, 6.02647 to \
  -8.82912, 6.22721 front fs empty border lc rgb '#6165' lw 0.2
set object 91 polygon from \
  -8.92722, 6.13843 to \
  -8.82912, 6.22721 to \
  -8.82888, 6.22743 to \
  -8.82888, 6.02669 to \
  -8.92698, 5.93791 to \
  -8.92722, 5.93769 to \
  -8.92722, 6.13843 front fs empty border lc rgb '#6165' lw 0.2
set object 92 polygon from \
  -9.02532, 6.04866 to \
  -8.92722, 6.13843 to \
  -8.92698, 6.13865 to \
  -8.92698, 5.93791 to \
  -9.02508, 5.84815 to \
  -9.02532, 5.84793 to \
  -9.02532, 6.04866 front fs empty border lc rgb '#6165' lw 0.2
set object 93 polygon from \
  -9.12342, 5.95792 to \
  -9.02532, 6.04866 to \
  -9.02508, 6.04889 to \
  -9.02508, 5.84815 to \
  -9.12318, 5.75741 to \
  -9.12342, 5.75718 to \
  -9.12342, 5.95792 front fs empty border lc rgb '#6165' lw 0.2
set object 94 polygon from \
  -9.22152, 5.8662 to \
  -9.12342, 5.95792 to \
  -9.12318, 5.95815 to \
  -9.12318, 5.75741 to \
  -9.22128, 5.66569 to \
  -9.22152, 5.66546 to \
  -9.22152, 5.8662 front fs empty border lc rgb '#6165' lw 0.2
set object 95 polygon from \
  -9.31962, 5.77349 to \
  -9.22152, 5.86619 to \
  -9.22128, 5.86643 to \
  -9.22128, 5.66569 to \
  -9.31938, 5.57298 to \
  -9.31962, 5.57275 to \
  -9.31962, 5.77349 front fs empty border lc rgb '#6165' lw 0.2
set object 96 polygon from \
  -9.41772, 5.6798 to \
  -9.31962, 5.77349 to \
  -9.31938, 5.77372 to \
  -9.31938, 5.57299 to \
  -9.41748, 5.4793 to \
  -9.41772, 5.47907 to \
  -9.41772, 5.6798 front fs empty border lc rgb '#6165' lw 0.2
set object 97 polygon from \
  -9.51582, 5.58514 to \
  -9.41772, 5.6798 to \
  -9.41748, 5.68004 to \
  -9.41748, 5.4793 to \
  -9.51558, 5.38464 to \
  -9.51582, 5.3844 to \
  -9.51582, 5.58514 front fs empty border lc rgb '#6165' lw 0.2
set object 98 polygon from \
  -9.61392, 5.48949 to \
  -9.51582, 5.58513 to \
  -9.51558, 5.58537 to \
  -9.51558, 5.38464 to \
  -9.61368, 5.28899 to \
  -9.61392, 5.28875 to \
  -9.61392, 5.48949 front fs empty border lc rgb '#6165' lw 0.2
set object 99 polygon from \
  -9.71202, 5.39286 to \
  -9.61392, 5.48949 to \
  -9.61368, 5.48973 to \
  -9.61368, 5.28899 to \
  -9.71178, 5.19236 to \
  -9.71202, 5.19212 to \
  -9.71202, 5.39286 front fs empty border lc rgb '#6165' lw 0.2
set object 100 polygon from \
  -9.81012, 5.29525 to \
  -9.71202, 5.39286 to \
  -9.71178, 5.3931 to \
  -9.71178, 5.19236 to \
  -9.80988, 5.09475 to \
  -9.81012, 5.09451 to \
  -9.81012, 5.29525 front fs empty border lc rgb '#6165' lw 0.2
set object 101 polygon from \
  -9.90822, 5.19665 to \
  -9.81012, 5.29525 to \
  -9.80988, 5.29549 to \
  -9.80988, 5.09475 to \
  -9.90798, 4.99616 to \
  -9.90822, 4.99592 to \
  -9.90822, 5.19665 front fs empty border lc rgb '#6165' lw 0.2
set object 102 polygon from \
  -10.0063, 5.09757 to \
  -9.90798, 5.1969 to \
  -9.90798, 4.99617 to \
  -10.0063, 4.89634 to \
  -10.0063, 5.09757 front fs empty border lc rgb '#6165' lw 0.2
set object 103 polygon from \
  -10.0061, 4.8966 to \
  -10.0061, 5.09733 to \
  -10.0061, 4.8966 front fs empty border lc rgb '#6165' lw 0.2
set object 104 polygon from \
  -10.1042, 4.79604 to \
  -10.1042, 4.99678 to \
  -10.1042, 4.79604 front fs empty border lc rgb '#6165' lw 0.2
set object 105 polygon from \
  -10.2023, 4.69451 to \
  -10.2023, 4.89525 to \
  -10.2023, 4.69451 front fs empty border lc rgb '#6165' lw 0.2
set object 106 polygon from \
  -10.3004, 4.592 to \
  -10.3004, 4.79273 to \
  -10.3004, 4.592 front fs empty border lc rgb '#6165' lw 0.2
set object 107 polygon from \
  -10.3985, 4.4885 to \
  -10.3985, 4.68924 to \
  -10.3985, 4.4885 front fs empty border lc rgb '#6165' lw 0.2
set object 108 polygon from \
  -10.4966, 4.38403 to \
  -10.4966, 4.58477 to \
  -10.4966, 4.38403 front fs empty border lc rgb '#6165' lw 0.2
set object 109 polygon from \
  -10.5947, 4.27857 to \
  -10.5947, 4.47931 to \
  -10.5947, 4.27857 front fs empty border lc rgb '#6165' lw 0.2
set object 110 polygon from \
  -10.6928, 4.17214 to \
  -10.6928, 4.37287 to \
  -10.6928, 4.17214 front fs empty border lc rgb '#6165' lw 0.2
set object 111 polygon from \
  -10.7909, 4.06472 to \
  -10.7909, 4.26545 to \
  -10.7909, 4.06472 front fs empty border lc rgb '#6165' lw 0.2
set object 112 polygon from \
  -10.889, 3.95632 to \
  -10.889, 4.15705 to \
  -10.889, 3.95632 front fs empty border lc rgb '#6165' lw 0.2
set object 113 polygon from \
  -10.9871, 3.84694 to \
  -10.9871, 4.04767 to \
  -10.9871, 3.84694 front fs empty border lc rgb '#6165' lw 0.2
set object 114 polygon from \
  -11.0852, 3.73658 to \
  -11.0852, 3.93731 to \
  -11.0852, 3.73658 front fs empty border lc rgb '#6165' lw 0.2
set object 115 polygon from \
  -11.1833, 3.62523 to \
  -11.1833, 3.82597 to \
  -11.1833, 3.62523 front fs empty border lc rgb '#6165' lw 0.2
set object 116 polygon from \
  -11.2814, 3.51291 to \
  -11.2814, 3.71365 to \
  -11.2814, 3.51291 front fs empty border lc rgb '#6165' lw 0.2
set object 117 polygon from \
  -11.3795, 3.39961 to \
  -11.3795, 3.60034 to \
  -11.3795, 3.39961 front fs empty border lc rgb '#6165' lw 0.2
set object 118 polygon from \
  -11.4776, 3.28532 to \
  -11.4776, 3.48606 to \
  -11.4776, 3.28532 front fs empty border lc rgb '#6165' lw 0.2
set object 119 polygon from \
  -11.5757, 3.17005 to \
  -11.5757, 3.37079 to \
  -11.5757, 3.17005 front fs empty border lc rgb '#6165' lw 0.2
set object 120 polygon from \
  -11.6738, 3.05381 to \
  -11.6738, 3.25454 to \
  -11.6738, 3.05381 front fs empty border lc rgb '#6165' lw 0.2
set object 121 polygon from \
  -11.7719, 2.93658 to \
  -11.7719, 3.13732 to \
  -11.7719, 2.93658 front fs empty border lc rgb '#6165' lw 0.2
set object 122 polygon from \
  -11.87, 2.81837 to \
  -11.87, 3.01911 to \
  -11.87, 2.81837 front fs empty border lc rgb '#6165' lw 0.2
set object 123 polygon from \
  -11.9681, 2.69918 to \
  -11.9681, 2.89992 to \
  -11.9681, 2.69918 front fs empty border lc rgb '#6165' lw 0.2
set object 124 polygon from \
  -12.0662, 2.57901 to \
  -12.0662, 2.77975 to \
  -12.0662, 2.57901 front fs empty border lc rgb '#6165' lw 0.2
set object 125 polygon from \
  -12.1643, 2.45786 to \
  -12.1643, 2.65859 to \
  -12.1643, 2.45786 front fs empty border lc rgb '#6165' lw 0.2
set object 126 polygon from \
  -12.2624, 2.33572 to \
  -12.2624, 2.53646 to \
  -12.2624, 2.33572 front fs empty border lc rgb '#6165' lw 0.2
set object 127 polygon from \
  -12.3605, 2.21261 to \
  -12.3605, 2.41335 to \
  -12.3605, 2.21261 front fs empty border lc rgb '#6165' lw 0.2
set object 128 polygon from \
  -12.4586, 2.08851 to \
  -12.4586, 2.28925 to \
  -12.4586, 2.08851 front fs empty border lc rgb '#6165' lw 0.2
set object 129 polygon from \
  -12.5567, 1.96344 to \
  -12.5567, 2.16417 to \
  -12.5567, 1.96344 front fs empty border lc rgb '#6165' lw 0.2
set object 130 polygon from \
  -12.6548, 1.83738 to \
  -12.6548, 2.03812 to \
  -12.6548, 1.83738 front fs empty border lc rgb '#6165' lw 0.2
set object 131 polygon from \
  -12.7529, 1.71034 to \
  -12.7529, 1.91108 to \
  -12.7529, 1.71034 front fs empty border lc rgb '#6165' lw 0.2
set object 132 polygon from \
  -12.851, 1.58232 to \
  -12.851, 1.78306 to \
  -12.851, 1.58232 front fs empty border lc rgb '#6165' lw 0.2
set object 133 polygon from \
  -12.9491, 1.45332 to \
  -12.9491, 1.65406 to \
  -12.9491, 1.45332 front fs empty border lc rgb '#6165' lw 0.2
set object 134 polygon from \
  -13.0472, 1.32334 to \
  -13.0472, 1.52408 to \
  -13.0472, 1.32334 front fs empty border lc rgb '#6165' lw 0.2
set object 135 polygon from \
  -13.1453, 1.19238 to \
  -13.1453, 1.39312 to \
  -13.1453, 1.19238 front fs empty border lc rgb '#6165' lw 0.2
set object 136 polygon from \
  -13.2434, 1.06044 to \
  -13.2434, 1.26117 to \
  -13.2434, 1.06044 front fs empty border lc rgb '#6165' lw 0.2
set object 137 polygon from \
  -13.3415, 0.927511 to \
  -13.3415, 1.12825 to \
  -13.3415, 0.927511 front fs empty border lc rgb '#6165' lw 0.2
set object 138 polygon from \
  -13.4396, 0.793606 to \
  -13.4396, 0.994342 to \
  -13.4396, 0.793606 front fs empty border lc rgb '#6165' lw 0.2
set object 139 polygon from \
  -13.5377, 0.65872 to \
  -13.5377, 0.859456 to \
  -13.5377, 0.65872 front fs empty border lc rgb '#6165' lw 0.2
set object 140 polygon from \
  -13.6358, 0.522852 to \
  -13.6358, 0.723589 to \
  -13.6358, 0.522852 front fs empty border lc rgb '#6165' lw 0.2
set object 141 polygon from \
  -13.7339, 0.386004 to \
  -13.7339, 0.586741 to \
  -13.7339, 0.386004 front fs empty border lc rgb '#6165' lw 0.2
set object 142 polygon from \
  -13.832, 0.248175 to \
  -13.832, 0.448911 to \
  -13.832, 0.248175 front fs empty border lc rgb '#6165' lw 0.2
set object 143 polygon from \
  -13.9301, 0.109364 to \
  -13.9301, 0.310101 to \
  -13.9301, 0.109364 front fs empty border lc rgb '#6165' lw 0.2
set object 144 polygon from \
  -14.0282, -0 to \
  -14.0282, 0.17031 to \
  -14.0282, -0 front fs empty border lc rgb '#6165' lw 0.2
set object 145 polygon from \
  -14.1263, -0 to \
  -14.1263, 0.0295375 to \
  -14.1263, -0 front fs empty border lc rgb '#6165' lw 0.2
set object 146 polygon from \
  10.4229, 0.105089 to \
  10.4965, 0.105825 to \
  10.4967, 0.105825 to \
  10.5948, 0.000368285 to \
  10.5948, 0 to \
  10.5207, 0 to \
  10.4229, 0.104353 to \
  10.4229, 0.105089 front fs empty border lc rgb '#6165' lw 0.2
set object 147 polygon from \
  10.4967, 0.105458 to \
  10.4967, 0.105826 to \
  10.4967, 0.105458 front fs empty border lc rgb '#6165' lw 0.2
set object 148 polygon from \
  10.3986, 0.209935 to \
  10.3986, 0.210303 to \
  10.3986, 0.209935 front fs empty border lc rgb '#6165' lw 0.2
set object 149 polygon from \
  10.3005, 0.31343 to \
  10.3005, 0.313799 to \
  10.3005, 0.31343 front fs empty border lc rgb '#6165' lw 0.2
set object 150 polygon from \
  10.2024, 0.415945 to \
  10.2024, 0.416314 to \
  10.2024, 0.415945 front fs empty border lc rgb '#6165' lw 0.2
set object 151 polygon from \
  10.1043, 0.517479 to \
  10.1043, 0.517847 to \
  10.1043, 0.517479 front fs empty border lc rgb '#6165' lw 0.2
set object 152 polygon from \
  10.0062, 0.618032 to \
  10.0062, 0.6184 to \
  10.0062, 0.618032 front fs empty border lc rgb '#6165' lw 0.2
set object 153 polygon from \
  9.90813, 0.717604 to \
  9.90813, 0.717972 to \
  9.90813, 0.717604 front fs empty border lc rgb '#6165' lw 0.2
set object 154 polygon from \
  9.81003, 0.816194 to \
  9.81003, 0.816563 to \
  9.81003, 0.816194 front fs empty border lc rgb '#6165' lw 0.2
set object 155 polygon from \
  9.71193, 0.913804 to \
  9.71193, 0.914173 to \
  9.71193, 0.913804 front fs empty border lc rgb '#6165' lw 0.2
set object 156 polygon from \
  9.61383, 1.01043 to \
  9.61383, 1.0108 to \
  9.61383, 1.01043 front fs empty border lc rgb '#6165' lw 0.2
set object 157 polygon from \
  9.51573, 1.10608 to \
  9.51573, 1.10645 to \
  9.51573, 1.10608 front fs empty border lc rgb '#6165' lw 0.2
set object 158 polygon from \
  9.41763, 1.20075 to \
  9.41763, 1.20112 to \
  9.41763, 1.20075 front fs empty border lc rgb '#6165' lw 0.2
set object 159 polygon from \
  9.31953, 1.29443 to \
  9.31953, 1.2948 to \
  9.31953, 1.29443 front fs empty border lc rgb '#6165' lw 0.2
set object 160 polygon from \
  9.22143, 1.38714 to \
  9.22143, 1.38751 to \
  9.22143, 1.38714 front fs empty border lc rgb '#6165' lw 0.2
set object 161 polygon from \
  9.12333, 1.47886 to \
  9.12333, 1.47923 to \
  9.12333, 1.47886 front fs empty border lc rgb '#6165' lw 0.2
set object 162 polygon from \
  9.02523, 1.5696 to \
  9.02523, 1.56997 to \
  9.02523, 1.5696 front fs empty border lc rgb '#6165' lw 0.2
set object 163 polygon from \
  8.92713, 1.65937 to \
  8.92713, 1.65974 to \
  8.92713, 1.65937 front fs empty border lc rgb '#6165' lw 0.2
set object 164 polygon from \
  8.82903, 1.74815 to \
  8.82903, 1.74852 to \
  8.82903, 1.74815 front fs empty border lc rgb '#6165' lw 0.2
set object 165 polygon from \
  8.73093, 1.83595 to \
  8.73093, 1.83632 to \
  8.73093, 1.83595 front fs empty border lc rgb '#6165' lw 0.2
set object 166 polygon from \
  8.63283, 1.92277 to \
  8.63283, 1.92313 to \
  8.63283, 1.92277 front fs empty border lc rgb '#6165' lw 0.2
set object 167 polygon from \
  8.53473, 2.0086 to \
  8.53473, 2.00897 to \
  8.53473, 2.0086 front fs empty border lc rgb '#6165' lw 0.2
set object 168 polygon from \
  8.43663, 2.09346 to \
  8.43663, 2.09383 to \
  8.43663, 2.09346 front fs empty border lc rgb '#6165' lw 0.2
set object 169 polygon from \
  8.33853, 2.17734 to \
  8.33853, 2.1777 to \
  8.33853, 2.17734 front fs empty border lc rgb '#6165' lw 0.2
set object 170 polygon from \
  8.24043, 2.26023 to \
  8.24043, 2.2606 to \
  8.24043, 2.26023 front fs empty border lc rgb '#6165' lw 0.2
set object 171 polygon from \
  8.14233, 2.34215 to \
  8.14233, 2.34251 to \
  8.14233, 2.34215 front fs empty border lc rgb '#6165' lw 0.2
set object 172 polygon from \
  8.04423, 2.42308 to \
  8.04423, 2.42345 to \
  8.04423, 2.42308 front fs empty border lc rgb '#6165' lw 0.2
set object 173 polygon from \
  7.94613, 2.50303 to \
  7.94613, 2.5034 to \
  7.94613, 2.50303 front fs empty border lc rgb '#6165' lw 0.2
set object 174 polygon from \
  7.84803, 2.582 to \
  7.84803, 2.58237 to \
  7.84803, 2.582 front fs empty border lc rgb '#6165' lw 0.2
set object 175 polygon from \
  7.74993, 2.65999 to \
  7.74993, 2.66036 to \
  7.74993, 2.65999 front fs empty border lc rgb '#6165' lw 0.2
set object 176 polygon from \
  7.65183, 2.737 to \
  7.65183, 2.73737 to \
  7.65183, 2.737 front fs empty border lc rgb '#6165' lw 0.2
set object 177 polygon from \
  7.55373, 2.81303 to \
  7.55373, 2.8134 to \
  7.55373, 2.81303 front fs empty border lc rgb '#6165' lw 0.2
set object 178 polygon from \
  7.45563, 2.88807 to \
  7.45563, 2.88844 to \
  7.45563, 2.88807 front fs empty border lc rgb '#6165' lw 0.2
set object 179 polygon from \
  7.35753, 2.96214 to \
  7.35753, 2.96251 to \
  7.35753, 2.96214 front fs empty border lc rgb '#6165' lw 0.2
set object 180 polygon from \
  7.25943, 3.03522 to \
  7.25943, 3.03559 to \
  7.25943, 3.03522 front fs empty border lc rgb '#6165' lw 0.2
set object 181 polygon from \
  7.16133, 3.10733 to \
  7.16133, 3.1077 to \
  7.16133, 3.10733 front fs empty border lc rgb '#6165' lw 0.2
set object 182 polygon from \
  7.06323, 3.17845 to \
  7.06323, 3.17882 to \
  7.06323, 3.17845 front fs empty border lc rgb '#6165' lw 0.2
set object 183 polygon from \
  6.96513, 3.24859 to \
  6.96513, 3.24896 to \
  6.96513, 3.24859 front fs empty border lc rgb '#6165' lw 0.2
set object 184 polygon from \
  6.86703, 3.31775 to \
  6.86703, 3.31812 to \
  6.86703, 3.31775 front fs empty border lc rgb '#6165' lw 0.2
set object 185 polygon from \
  6.76893, 3.38593 to \
  6.76893, 3.3863 to \
  6.76893, 3.38593 front fs empty border lc rgb '#6165' lw 0.2
set object 186 polygon from \
  6.67083, 3.45313 to \
  6.67083, 3.4535 to \
  6.67083, 3.45313 front fs empty border lc rgb '#6165' lw 0.2
set object 187 polygon from \
  6.57273, 3.51935 to \
  6.57273, 3.51972 to \
  6.57273, 3.51935 front fs empty border lc rgb '#6165' lw 0.2
set object 188 polygon from \
  6.47463, 3.58459 to \
  6.47463, 3.58496 to \
  6.47463, 3.58459 front fs empty border lc rgb '#6165' lw 0.2
set object 189 polygon from \
  6.37653, 3.64884 to \
  6.37653, 3.64921 to \
  6.37653, 3.64884 front fs empty border lc rgb '#6165' lw 0.2
set object 190 polygon from \
  6.27843, 3.71212 to \
  6.27843, 3.71249 to \
  6.27843, 3.71212 front fs empty border lc rgb '#6165' lw 0.2
set object 191 polygon from \
  6.18033, 3.77441 to \
  6.18033, 3.77478 to \
  6.18033, 3.77441 front fs empty border lc rgb '#6165' lw 0.2
set object 192 polygon from \
  6.08223, 3.83572 to \
  6.08223, 3.83609 to \
  6.08223, 3.83572 front fs empty border lc rgb '#6165' lw 0.2
set object 193 polygon from \
  5.98413, 3.89606 to \
  5.98413, 3.89642 to \
  5.98413, 3.89606 front fs empty border lc rgb '#6165' lw 0.2
set object 194 polygon from \
  5.88603, 3.95541 to \
  5.88603, 3.95578 to \
  5.88603, 3.95541 front fs empty border lc rgb '#6165' lw 0.2
set object 195 polygon from \
  5.78793, 4.01378 to \
  5.78793, 4.01414 to \
  5.78793, 4.01378 front fs empty border lc rgb '#6165' lw 0.2
set object 196 polygon from \
  5.68983, 4.07117 to \
  5.68983, 4.07153 to \
  5.68983, 4.07117 front fs empty border lc rgb '#6165' lw 0.2
set object 197 polygon from \
  5.59173, 4.12757 to \
  5.59173, 4.12794 to \
  5.59173, 4.12757 front fs empty border lc rgb '#6165' lw 0.2
set object 198 polygon from \
  5.49363, 4.183 to \
  5.49363, 4.18337 to \
  5.49363, 4.183 front fs empty border lc rgb '#6165' lw 0.2
set object 199 polygon from \
  5.39553, 4.23745 to \
  5.39553, 4.23781 to \
  5.39553, 4.23745 front fs empty border lc rgb '#6165' lw 0.2
set object 200 polygon from \
  5.29743, 4.29091 to \
  5.29743, 4.29128 to \
  5.29743, 4.29091 front fs empty border lc rgb '#6165' lw 0.2
set object 201 polygon from \
  5.19933, 4.34339 to \
  5.19933, 4.34376 to \
  5.19933, 4.34339 front fs empty border lc rgb '#6165' lw 0.2
set object 202 polygon from \
  5.10123, 4.3949 to \
  5.10123, 4.39527 to \
  5.10123, 4.3949 front fs empty border lc rgb '#6165' lw 0.2
set object 203 polygon from \
  5.00313, 4.44542 to \
  5.00313, 4.44579 to \
  5.00313, 4.44542 front fs empty border lc rgb '#6165' lw 0.2
set object 204 polygon from \
  4.90503, 4.49496 to \
  4.90503, 4.49533 to \
  4.90503, 4.49496 front fs empty border lc rgb '#6165' lw 0.2
set object 205 polygon from \
  4.80693, 4.54352 to \
  4.80693, 4.54389 to \
  4.80693, 4.54352 front fs empty border lc rgb '#6165' lw 0.2
set object 206 polygon from \
  4.70883, 4.5911 to \
  4.70883, 4.59147 to \
  4.70883, 4.5911 front fs empty border lc rgb '#6165' lw 0.2
set object 207 polygon from \
  4.61073, 4.6377 to \
  4.61073, 4.63806 to \
  4.61073, 4.6377 front fs empty border lc rgb '#6165' lw 0.2
set object 208 polygon from \
  4.51263, 4.68331 to \
  4.51263, 4.68368 to \
  4.51263, 4.68331 front fs empty border lc rgb '#6165' lw 0.2
set object 209 polygon from \
  4.41453, 4.72795 to \
  4.41453, 4.72832 to \
  4.41453, 4.72795 front fs empty border lc rgb '#6165' lw 0.2
set object 210 polygon from \
  4.31643, 4.7716 to \
  4.31643, 4.77197 to \
  4.31643, 4.7716 front fs empty border lc rgb '#6165' lw 0.2
set object 211 polygon from \
  4.21833, 4.81428 to \
  4.21833, 4.81465 to \
  4.21833, 4.81428 front fs empty border lc rgb '#6165' lw 0.2
set object 212 polygon from \
  4.12023, 4.85597 to \
  4.12023, 4.85634 to \
  4.12023, 4.85597 front fs empty border lc rgb '#6165' lw 0.2
set object 213 polygon from \
  4.02213, 4.89668 to \
  4.02213, 4.89705 to \
  4.02213, 4.89668 front fs empty border lc rgb '#6165' lw 0.2
set object 214 polygon from \
  3.92403, 4.93641 to \
  3.92403, 4.93678 to \
  3.92403, 4.93641 front fs empty border lc rgb '#6165' lw 0.2
set object 215 polygon from \
  3.82593, 4.97516 to \
  3.82593, 4.97553 to \
  3.82593, 4.97516 front fs empty border lc rgb '#6165' lw 0.2
set object 216 polygon from \
  3.72783, 5.01293 to \
  3.72783, 5.0133 to \
  3.72783, 5.01293 front fs empty border lc rgb '#6165' lw 0.2
set object 217 polygon from \
  3.62973, 5.04972 to \
  3.62973, 5.05009 to \
  3.62973, 5.04972 front fs empty border lc rgb '#6165' lw 0.2
set object 218 polygon from \
  3.53163, 5.08553 to \
  3.53163, 5.08589 to \
  3.53163, 5.08553 front fs empty border lc rgb '#6165' lw 0.2
set object 219 polygon from \
  3.43353, 5.12035 to \
  3.43353, 5.12072 to \
  3.43353, 5.12035 front fs empty border lc rgb '#6165' lw 0.2
set object 220 polygon from \
  3.33543, 5.1542 to \
  3.33543, 5.15457 to \
  3.33543, 5.1542 front fs empty border lc rgb '#6165' lw 0.2
set object 221 polygon from \
  3.23733, 5.18706 to \
  3.23733, 5.18743 to \
  3.23733, 5.18706 front fs empty border lc rgb '#6165' lw 0.2
set object 222 polygon from \
  3.13923, 5.21894 to \
  3.13923, 5.21931 to \
  3.13923, 5.21894 front fs empty border lc rgb '#6165' lw 0.2
set object 223 polygon from \
  3.04113, 5.24985 to \
  3.04113, 5.25021 to \
  3.04113, 5.24985 front fs empty border lc rgb '#6165' lw 0.2
set object 224 polygon from \
  2.94303, 5.27977 to \
  2.94303, 5.28013 to \
  2.94303, 5.27977 front fs empty border lc rgb '#6165' lw 0.2
set object 225 polygon from \
  2.84493, 5.30871 to \
  2.84493, 5.30907 to \
  2.84493, 5.30871 front fs empty border lc rgb '#6165' lw 0.2
set object 226 polygon from \
  2.74683, 5.33666 to \
  2.74683, 5.33703 to \
  2.74683, 5.33666 front fs empty border lc rgb '#6165' lw 0.2
set object 227 polygon from \
  2.64873, 5.36364 to \
  2.64873, 5.36401 to \
  2.64873, 5.36364 front fs empty border lc rgb '#6165' lw 0.2
set object 228 polygon from \
  2.55063, 5.38964 to \
  2.55063, 5.39001 to \
  2.55063, 5.38964 front fs empty border lc rgb '#6165' lw 0.2
set object 229 polygon from \
  2.45253, 5.41466 to \
  2.45253, 5.41502 to \
  2.45253, 5.41466 front fs empty border lc rgb '#6165' lw 0.2
set object 230 polygon from \
  2.35443, 5.43869 to \
  2.35443, 5.43906 to \
  2.35443, 5.43869 front fs empty border lc rgb '#6165' lw 0.2
set object 231 polygon from \
  2.25633, 5.46174 to \
  2.25633, 5.46211 to \
  2.25633, 5.46174 front fs empty border lc rgb '#6165' lw 0.2
set object 232 polygon from \
  2.15823, 5.48382 to \
  2.15823, 5.48418 to \
  2.15823, 5.48382 front fs empty border lc rgb '#6165' lw 0.2
set object 233 polygon from \
  2.06013, 5.50491 to \
  2.06013, 5.50528 to \
  2.06013, 5.50491 front fs empty border lc rgb '#6165' lw 0.2
set object 234 polygon from \
  1.96203, 5.52502 to \
  1.96203, 5.52539 to \
  1.96203, 5.52502 front fs empty border lc rgb '#6165' lw 0.2
set object 235 polygon from \
  1.86393, 5.54415 to \
  1.86393, 5.54452 to \
  1.86393, 5.54415 front fs empty border lc rgb '#6165' lw 0.2
set object 236 polygon from \
  1.76583, 5.5623 to \
  1.76583, 5.56267 to \
  1.76583, 5.5623 front fs empty border lc rgb '#6165' lw 0.2
set object 237 polygon from \
  1.66773, 5.57947 to \
  1.66773, 5.57983 to \
  1.66773, 5.57947 front fs empty border lc rgb '#6165' lw 0.2
set object 238 polygon from \
  1.56963, 5.59565 to \
  1.56963, 5.59602 to \
  1.56963, 5.59565 front fs empty border lc rgb '#6165' lw 0.2
set object 239 polygon from \
  1.47153, 5.61086 to \
  1.47153, 5.61123 to \
  1.47153, 5.61086 front fs empty border lc rgb '#6165' lw 0.2
set object 240 polygon from \
  1.37343, 5.62508 to \
  1.37343, 5.62545 to \
  1.37343, 5.62508 front fs empty border lc rgb '#6165' lw 0.2
set object 241 polygon from \
  1.27533, 5.63833 to \
  1.27533, 5.6387 to \
  1.27533, 5.63833 front fs empty border lc rgb '#6165' lw 0.2
set object 242 polygon from \
  1.17723, 5.65059 to \
  1.17723, 5.65096 to \
  1.17723, 5.65059 front fs empty border lc rgb '#6165' lw 0.2
set object 243 polygon from \
  1.07913, 5.66187 to \
  1.07913, 5.66224 to \
  1.07913, 5.66187 front fs empty border lc rgb '#6165' lw 0.2
set object 244 polygon from \
  0.981031, 5.67217 to \
  0.981031, 5.67254 to \
  0.981031, 5.67217 front fs empty border lc rgb '#6165' lw 0.2
set object 245 polygon from \
  0.882931, 5.68149 to \
  0.882931, 5.68186 to \
  0.882931, 5.68149 front fs empty border lc rgb '#6165' lw 0.2
set object 246 polygon from \
  0.784831, 5.68983 to \
  0.784831, 5.6902 to \
  0.784831, 5.68983 front fs empty border lc rgb '#6165' lw 0.2
set object 247 polygon from \
  0.686731, 5.69719 to \
  0.686731, 5.69756 to \
  0.686731, 5.69719 front fs empty border lc rgb '#6165' lw 0.2
set object 248 polygon from \
  0.588631, 5.70357 to \
  0.588631, 5.70393 to \
  0.588631, 5.70357 front fs empty border lc rgb '#6165' lw 0.2
set object 249 polygon from \
  0.490531, 5.70896 to \
  0.490531, 5.70933 to \
  0.490531, 5.70896 front fs empty border lc rgb '#6165' lw 0.2
set object 250 polygon from \
  0.392431, 5.71338 to \
  0.392431, 5.71374 to \
  0.392431, 5.71338 front fs empty border lc rgb '#6165' lw 0.2
set object 251 polygon from \
  0.294331, 5.71681 to \
  0.294331, 5.71718 to \
  0.294331, 5.71681 front fs empty border lc rgb '#6165' lw 0.2
set object 252 polygon from \
  0.196231, 5.71926 to \
  0.196231, 5.71963 to \
  0.196231, 5.71926 front fs empty border lc rgb '#6165' lw 0.2
set object 253 polygon from \
  0.0981308, 5.72073 to \
  0.0981308, 5.7211 to \
  0.0981308, 5.72073 front fs empty border lc rgb '#6165' lw 0.2
set object 254 polygon from \
  3.07584e-05, 5.72123 to \
  3.07584e-05, 5.72159 to \
  3.07584e-05, 5.72123 front fs empty border lc rgb '#6165' lw 0.2
set object 255 polygon from \
  -0.0980692, 5.72074 to \
  -0.0980692, 5.7211 to \
  -0.0980692, 5.72074 front fs empty border lc rgb '#6165' lw 0.2
set object 256 polygon from \
  -0.196169, 5.71926 to \
  -0.196169, 5.71963 to \
  -0.196169, 5.71926 front fs empty border lc rgb '#6165' lw 0.2
set object 257 polygon from \
  -0.294269, 5.71681 to \
  -0.294269, 5.71718 to \
  -0.294269, 5.71681 front fs empty border lc rgb '#6165' lw 0.2
set object 258 polygon from \
  -0.392369, 5.71338 to \
  -0.392369, 5.71375 to \
  -0.392369, 5.71338 front fs empty border lc rgb '#6165' lw 0.2
set object 259 polygon from \
  -0.490469, 5.70896 to \
  -0.490469, 5.70933 to \
  -0.490469, 5.70896 front fs empty border lc rgb '#6165' lw 0.2
set object 260 polygon from \
  -0.588569, 5.70357 to \
  -0.588569, 5.70394 to \
  -0.588569, 5.70357 front fs empty border lc rgb '#6165' lw 0.2
set object 261 polygon from \
  -0.686669, 5.69719 to \
  -0.686669, 5.69756 to \
  -0.686669, 5.69719 front fs empty border lc rgb '#6165' lw 0.2
set object 262 polygon from \
  -0.784769, 5.68984 to \
  -0.784769, 5.6902 to \
  -0.784769, 5.68984 front fs empty border lc rgb '#6165' lw 0.2
set object 263 polygon from \
  -0.882869, 5.6815 to \
  -0.882869, 5.68187 to \
  -0.882869, 5.6815 front fs empty border lc rgb '#6165' lw 0.2
set object 264 polygon from \
  -0.980969, 5.67218 to \
  -0.980969, 5.67255 to \
  -0.980969, 5.67218 front fs empty border lc rgb '#6165' lw 0.2
set object 265 polygon from \
  -1.07907, 5.66188 to \
  -1.07907, 5.66225 to \
  -1.07907, 5.66188 front fs empty border lc rgb '#6165' lw 0.2
set object 266 polygon from \
  -1.17717, 5.6506 to \
  -1.17717, 5.65097 to \
  -1.17717, 5.6506 front fs empty border lc rgb '#6165' lw 0.2
set object 267 polygon from \
  -1.27527, 5.63833 to \
  -1.27527, 5.6387 to \
  -1.27527, 5.63833 front fs empty border lc rgb '#6165' lw 0.2
set object 268 polygon from \
  -1.37337, 5.62509 to \
  -1.37337, 5.62546 to \
  -1.37337, 5.62509 front fs empty border lc rgb '#6165' lw 0.2
set object 269 polygon from \
  -1.47147, 5.61087 to \
  -1.47147, 5.61124 to \
  -1.47147, 5.61087 front fs empty border lc rgb '#6165' lw 0.2
set object 270 polygon from \
  -1.56957, 5.59566 to \
  -1.56957, 5.59603 to \
  -1.56957, 5.59566 front fs empty border lc rgb '#6165' lw 0.2
set object 271 polygon from \
  -1.66767, 5.57948 to \
  -1.66767, 5.57984 to \
  -1.66767, 5.57948 front fs empty border lc rgb '#6165' lw 0.2
set object 272 polygon from \
  -1.76577, 5.56231 to \
  -1.76577, 5.56268 to \
  -1.76577, 5.56231 front fs empty border lc rgb '#6165' lw 0.2
set object 273 polygon from \
  -1.86387, 5.54416 to \
  -1.86387, 5.54453 to \
  -1.86387, 5.54416 front fs empty border lc rgb '#6165' lw 0.2
set object 274 polygon from \
  -1.96197, 5.52503 to \
  -1.96197, 5.5254 to \
  -1.96197, 5.52503 front fs empty border lc rgb '#6165' lw 0.2
set object 275 polygon from \
  -2.06007, 5.50492 to \
  -2.06007, 5.50529 to \
  -2.06007, 5.50492 front fs empty border lc rgb '#6165' lw 0.2
set object 276 polygon from \
  -2.15817, 5.48383 to \
  -2.15817, 5.4842 to \
  -2.15817, 5.48383 front fs empty border lc rgb '#6165' lw 0.2
set object 277 polygon from \
  -2.25627, 5.46176 to \
  -2.25627, 5.46213 to \
  -2.25627, 5.46176 front fs empty border lc rgb '#6165' lw 0.2
set object 278 polygon from \
  -2.35437, 5.4387 to \
  -2.35437, 5.43907 to \
  -2.35437, 5.4387 front fs empty border lc rgb '#6165' lw 0.2
set object 279 polygon from \
  -2.45247, 5.41467 to \
  -2.45247, 5.41504 to \
  -2.45247, 5.41467 front fs empty border lc rgb '#6165' lw 0.2
set object 280 polygon from \
  -2.55057, 5.38966 to \
  -2.55057, 5.39002 to \
  -2.55057, 5.38966 front fs empty border lc rgb '#6165' lw 0.2
set object 281 polygon from \
  -2.64867, 5.36366 to \
  -2.64867, 5.36403 to \
  -2.64867, 5.36366 front fs empty border lc rgb '#6165' lw 0.2
set object 282 polygon from \
  -2.74677, 5.33668 to \
  -2.74677, 5.33705 to \
  -2.74677, 5.33668 front fs empty border lc rgb '#6165' lw 0.2
set object 283 polygon from \
  -2.84487, 5.30872 to \
  -2.84487, 5.30909 to \
  -2.84487, 5.30872 front fs empty border lc rgb '#6165' lw 0.2
set object 284 polygon from \
  -2.94297, 5.27978 to \
  -2.94297, 5.28015 to \
  -2.94297, 5.27978 front fs empty border lc rgb '#6165' lw 0.2
set object 285 polygon from \
  -3.04107, 5.24986 to \
  -3.04107, 5.25023 to \
  -3.04107, 5.24986 front fs empty border lc rgb '#6165' lw 0.2
set object 286 polygon from \
  -3.13917, 5.21896 to \
  -3.13917, 5.21933 to \
  -3.13917, 5.21896 front fs empty border lc rgb '#6165' lw 0.2
set object 287 polygon from \
  -3.23727, 5.18708 to \
  -3.23727, 5.18745 to \
  -3.23727, 5.18708 front fs empty border lc rgb '#6165' lw 0.2
set object 288 polygon from \
  -3.33537, 5.15422 to \
  -3.33537, 5.15459 to \
  -3.33537, 5.15422 front fs empty border lc rgb '#6165' lw 0.2
set object 289 polygon from \
  -3.43347, 5.12037 to \
  -3.43347, 5.12074 to \
  -3.43347, 5.12037 front fs empty border lc rgb '#6165' lw 0.2
set object 290 polygon from \
  -3.53157, 5.08555 to \
  -3.53157, 5.08592 to \
  -3.53157, 5.08555 front fs empty border lc rgb '#6165' lw 0.2
set object 291 polygon from \
  -3.62967, 5.04974 to \
  -3.62967, 5.05011 to \
  -3.62967, 5.04974 front fs empty border lc rgb '#6165' lw 0.2
set object 292 polygon from \
  -3.72777, 5.01295 to \
  -3.72777, 5.01332 to \
  -3.72777, 5.01295 front fs empty border lc rgb '#6165' lw 0.2
set object 293 polygon from \
  -3.82587, 4.97519 to \
  -3.82587, 4.97555 to \
  -3.82587, 4.97519 front fs empty border lc rgb '#6165' lw 0.2
set object 294 polygon from \
  -3.92397, 4.93644 to \
  -3.92397, 4.93681 to \
  -3.92397, 4.93644 front fs empty border lc rgb '#6165' lw 0.2
set object 295 polygon from \
  -4.02207, 4.89671 to \
  -4.02207, 4.89708 to \
  -4.02207, 4.89671 front fs empty border lc rgb '#6165' lw 0.2
set object 296 polygon from \
  -4.12017, 4.856 to \
  -4.12017, 4.85636 to \
  -4.12017, 4.856 front fs empty border lc rgb '#6165' lw 0.2
set object 297 polygon from \
  -4.21827, 4.8143 to \
  -4.21827, 4.81467 to \
  -4.21827, 4.8143 front fs empty border lc rgb '#6165' lw 0.2
set object 298 polygon from \
  -4.31637, 4.77163 to \
  -4.31637, 4.772 to \
  -4.31637, 4.77163 front fs empty border lc rgb '#6165' lw 0.2
set object 299 polygon from \
  -4.41447, 4.72798 to \
  -4.41447, 4.72834 to \
  -4.41447, 4.72798 front fs empty border lc rgb '#6165' lw 0.2
set object 300 polygon from \
  -4.51257, 4.68334 to \
  -4.51257, 4.68371 to \
  -4.51257, 4.68334 front fs empty border lc rgb '#6165' lw 0.2
set object 301 polygon from \
  -4.61067, 4.63773 to \
  -4.61067, 4.63809 to \
  -4.61067, 4.63773 front fs empty border lc rgb '#6165' lw 0.2
set object 302 polygon from \
  -4.70877, 4.59113 to \
  -4.70877, 4.5915 to \
  -4.70877, 4.59113 front fs empty border lc rgb '#6165' lw 0.2
set object 303 polygon from \
  -4.80687, 4.54355 to \
  -4.80687, 4.54392 to \
  -4.80687, 4.54355 front fs empty border lc rgb '#6165' lw 0.2
set object 304 polygon from \
  -4.90497, 4.49499 to \
  -4.90497, 4.49536 to \
  -4.90497, 4.49499 front fs empty border lc rgb '#6165' lw 0.2
set object 305 polygon from \
  -5.00307, 4.44545 to \
  -5.00307, 4.44582 to \
  -5.00307, 4.44545 front fs empty border lc rgb '#6165' lw 0.2
set object 306 polygon from \
  -5.10117, 4.39493 to \
  -5.10117, 4.3953 to \
  -5.10117, 4.39493 front fs empty border lc rgb '#6165' lw 0.2
set object 307 polygon from \
  -5.19927, 4.34343 to \
  -5.19927, 4.3438 to \
  -5.19927, 4.34343 front fs empty border lc rgb '#6165' lw 0.2
set object 308 polygon from \
  -5.29737, 4.29094 to \
  -5.29737, 4.29131 to \
  -5.29737, 4.29094 front fs empty border lc rgb '#6165' lw 0.2
set object 309 polygon from \
  -5.39547, 4.23748 to \
  -5.39547, 4.23785 to \
  -5.39547, 4.23748 front fs empty border lc rgb '#6165' lw 0.2
set object 310 polygon from \
  -5.49357, 4.18303 to \
  -5.49357, 4.1834 to \
  -5.49357, 4.18303 front fs empty border lc rgb '#6165' lw 0.2
set object 311 polygon from \
  -5.59167, 4.12761 to \
  -5.59167, 4.12798 to \
  -5.59167, 4.12761 front fs empty border lc rgb '#6165' lw 0.2
set object 312 polygon from \
  -5.68977, 4.0712 to \
  -5.68977, 4.07157 to \
  -5.68977, 4.0712 front fs empty border lc rgb '#6165' lw 0.2
set object 313 polygon from \
  -5.78787, 4.01381 to \
  -5.78787, 4.01418 to \
  -5.78787, 4.01381 front fs empty border lc rgb '#6165' lw 0.2
set object 314 polygon from \
  -5.88597, 3.95544 to \
  -5.88597, 3.95581 to \
  -5.88597, 3.95544 front fs empty border lc rgb '#6165' lw 0.2
set object 315 polygon from \
  -5.98407, 3.89609 to \
  -5.98407, 3.89646 to \
  -5.98407, 3.89609 front fs empty border lc rgb '#6165' lw 0.2
set object 316 polygon from \
  -6.08217, 3.83576 to \
  -6.08217, 3.83613 to \
  -6.08217, 3.83576 front fs empty border lc rgb '#6165' lw 0.2
set object 317 polygon from \
  -6.18027, 3.77445 to \
  -6.18027, 3.77482 to \
  -6.18027, 3.77445 front fs empty border lc rgb '#6165' lw 0.2
set object 318 polygon from \
  -6.27837, 3.71216 to \
  -6.27837, 3.71253 to \
  -6.27837, 3.71216 front fs empty border lc rgb '#6165' lw 0.2
set object 319 polygon from \
  -6.37647, 3.64888 to \
  -6.37647, 3.64925 to \
  -6.37647, 3.64888 front fs empty border lc rgb '#6165' lw 0.2
set object 320 polygon from \
  -6.47457, 3.58463 to \
  -6.47457, 3.585 to \
  -6.47457, 3.58463 front fs empty border lc rgb '#6165' lw 0.2
set object 321 polygon from \
  -6.57267, 3.51939 to \
  -6.57267, 3.51976 to \
  -6.57267, 3.51939 front fs empty border lc rgb '#6165' lw 0.2
set object 322 polygon from \
  -6.67077, 3.45317 to \
  -6.67077, 3.45354 to \
  -6.67077, 3.45317 front fs empty border lc rgb '#6165' lw 0.2
set object 323 polygon from \
  -6.76887, 3.38598 to \
  -6.76887, 3.38634 to \
  -6.76887, 3.38598 front fs empty border lc rgb '#6165' lw 0.2
set object 324 polygon from \
  -6.86697, 3.3178 to \
  -6.86697, 3.31817 to \
  -6.86697, 3.3178 front fs empty border lc rgb '#6165' lw 0.2
set object 325 polygon from \
  -6.96507, 3.24864 to \
  -6.96507, 3.249 to \
  -6.96507, 3.24864 front fs empty border lc rgb '#6165' lw 0.2
set object 326 polygon from \
  -7.06317, 3.1785 to \
  -7.06317, 3.17886 to \
  -7.06317, 3.1785 front fs empty border lc rgb '#6165' lw 0.2
set object 327 polygon from \
  -7.16127, 3.10737 to \
  -7.16127, 3.10774 to \
  -7.16127, 3.10737 front fs empty border lc rgb '#6165' lw 0.2
set object 328 polygon from \
  -7.25937, 3.03527 to \
  -7.25937, 3.03564 to \
  -7.25937, 3.03527 front fs empty border lc rgb '#6165' lw 0.2
set object 329 polygon from \
  -7.35747, 2.96219 to \
  -7.35747, 2.96255 to \
  -7.35747, 2.96219 front fs empty border lc rgb '#6165' lw 0.2
set object 330 polygon from \
  -7.45557, 2.88812 to \
  -7.45557, 2.88849 to \
  -7.45557, 2.88812 front fs empty border lc rgb '#6165' lw 0.2
set object 331 polygon from \
  -7.55367, 2.81307 to \
  -7.55367, 2.81344 to \
  -7.55367, 2.81307 front fs empty border lc rgb '#6165' lw 0.2
set object 332 polygon from \
  -7.65177, 2.73705 to \
  -7.65177, 2.73742 to \
  -7.65177, 2.73705 front fs empty border lc rgb '#6165' lw 0.2
set object 333 polygon from \
  -7.74987, 2.66004 to \
  -7.74987, 2.66041 to \
  -7.74987, 2.66004 front fs empty border lc rgb '#6165' lw 0.2
set object 334 polygon from \
  -7.84797, 2.58205 to \
  -7.84797, 2.58242 to \
  -7.84797, 2.58205 front fs empty border lc rgb '#6165' lw 0.2
set object 335 polygon from \
  -7.94607, 2.50308 to \
  -7.94607, 2.50345 to \
  -7.94607, 2.50308 front fs empty border lc rgb '#6165' lw 0.2
set object 336 polygon from \
  -8.04417, 2.42313 to \
  -8.04417, 2.4235 to \
  -8.04417, 2.42313 front fs empty border lc rgb '#6165' lw 0.2
set object 337 polygon from \
  -8.14227, 2.3422 to \
  -8.14227, 2.34256 to \
  -8.14227, 2.3422 front fs empty border lc rgb '#6165' lw 0.2
set object 338 polygon from \
  -8.24037, 2.26028 to \
  -8.24037, 2.26065 to \
  -8.24037, 2.26028 front fs empty border lc rgb '#6165' lw 0.2
set object 339 polygon from \
  -8.33847, 2.17739 to \
  -8.33847, 2.17776 to \
  -8.33847, 2.17739 front fs empty border lc rgb '#6165' lw 0.2
set object 340 polygon from \
  -8.43657, 2.09351 to \
  -8.43657, 2.09388 to \
  -8.43657, 2.09351 front fs empty border lc rgb '#6165' lw 0.2
set object 341 polygon from \
  -8.53467, 2.00866 to \
  -8.53467, 2.00903 to \
  -8.53467, 2.00866 front fs empty border lc rgb '#6165' lw 0.2
set object 342 polygon from \
  -8.63277, 1.92282 to \
  -8.63277, 1.92319 to \
  -8.63277, 1.92282 front fs empty border lc rgb '#6165' lw 0.2
set object 343 polygon from \
  -8.73087, 1.836 to \
  -8.73087, 1.83637 to \
  -8.73087, 1.836 front fs empty border lc rgb '#6165' lw 0.2
set object 344 polygon from \
  -8.82897, 1.7482 to \
  -8.82897, 1.74857 to \
  -8.82897, 1.7482 front fs empty border lc rgb '#6165' lw 0.2
set object 345 polygon from \
  -8.92707, 1.65942 to \
  -8.92707, 1.65979 to \
  -8.92707, 1.65942 front fs empty border lc rgb '#6165' lw 0.2
set object 346 polygon from \
  -9.02517, 1.56966 to \
  -9.02517, 1.57003 to \
  -9.02517, 1.56966 front fs empty border lc rgb '#6165' lw 0.2
set object 347 polygon from \
  -9.12327, 1.47892 to \
  -9.12327, 1.47929 to \
  -9.12327, 1.47892 front fs empty border lc rgb '#6165' lw 0.2
set object 348 polygon from \
  -9.22137, 1.3872 to \
  -9.22137, 1.38756 to \
  -9.22137, 1.3872 front fs empty border lc rgb '#6165' lw 0.2
set object 349 polygon from \
  -9.31947, 1.29449 to \
  -9.31947, 1.29486 to \
  -9.31947, 1.29449 front fs empty border lc rgb '#6165' lw 0.2
set object 350 polygon from \
  -9.41757, 1.20081 to \
  -9.41757, 1.20118 to \
  -9.41757, 1.20081 front fs empty border lc rgb '#6165' lw 0.2
set object 351 polygon from \
  -9.51567, 1.10614 to \
  -9.51567, 1.10651 to \
  -9.51567, 1.10614 front fs empty border lc rgb '#6165' lw 0.2
set object 352 polygon from \
  -9.61377, 1.01049 to \
  -9.61377, 1.01086 to \
  -9.61377, 1.01049 front fs empty border lc rgb '#6165' lw 0.2
set object 353 polygon from \
  -9.71187, 0.913865 to \
  -9.71187, 0.914233 to \
  -9.71187, 0.913865 front fs empty border lc rgb '#6165' lw 0.2
set object 354 polygon from \
  -9.80997, 0.816256 to \
  -9.80997, 0.816624 to \
  -9.80997, 0.816256 front fs empty border lc rgb '#6165' lw 0.2
set object 355 polygon from \
  -9.90807, 0.717666 to \
  -9.90807, 0.718034 to \
  -9.90807, 0.717666 front fs empty border lc rgb '#6165' lw 0.2
set object 356 polygon from \
  -10.0062, 0.618095 to \
  -10.0062, 0.618463 to \
  -10.0062, 0.618095 front fs empty border lc rgb '#6165' lw 0.2
set object 357 polygon from \
  -10.1043, 0.517542 to \
  -10.1043, 0.517911 to \
  -10.1043, 0.517542 front fs empty border lc rgb '#6165' lw 0.2
set object 358 polygon from \
  -10.2024, 0.416009 to \
  -10.2024, 0.416377 to \
  -10.2024, 0.416009 front fs empty border lc rgb '#6165' lw 0.2
set object 359 polygon from \
  -10.3005, 0.313495 to \
  -10.3005, 0.313863 to \
  -10.3005, 0.313495 front fs empty border lc rgb '#6165' lw 0.2
set object 360 polygon from \
  -10.3986, 0.21 to \
  -10.3986, 0.210368 to \
  -10.3986, 0.21 front fs empty border lc rgb '#6165' lw 0.2
set object 361 polygon from \
  -10.4967, 0.105524 to \
  -10.4967, 0.105892 to \
  -10.4967, 0.105524 front fs empty border lc rgb '#6165' lw 0.2
set object 362 polygon from \
  -10.5948, 6.64382e-05 to \
  -10.5948, 0.000434723 to \
  -10.5948, 6.64382e-05 front fs empty border lc rgb '#6165' lw 0.2
plot [-16.5984:13.0669] [-1.02004:11.2204] NaN notitle

