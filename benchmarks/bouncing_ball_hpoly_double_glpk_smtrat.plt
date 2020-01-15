# settings
set term pdf
set output "bouncing_ball_hpoly_double_glpk_smtrat.pdf
set xtics autofreq
set ytics autofreq
set grid back
# axis settings
set xzeroaxis 
set zeroaxis 
set xtics axis 
set xrange [-17.2461:13.1261] 
set yzeroaxis 
set ytics axis 
set yrange [-1.01998:11.2199] 

# plotting sets
set object 1 polygon from \
  -0.098223, 10.1999 to \
  -0.0979769, 10.1999 to \
  0.000123034, 10.0004 to \
  0.000123034, 0 to \
  -0.098223, -0 to \
  -0.098223, 10.1999 front fs empty border lc rgb '#6165' lw 0.200001
set object 2 polygon from \
  -0.196323, 10.1985 to \
  -0.196076, 10.1985 to \
  -0.0979769, 9.99988 to \
  -0.0979769, -0 to \
  -0.196323, -0 to \
  -0.196323, 10.1985 front fs empty border lc rgb '#6165' lw 0.200001
set object 3 polygon from \
  -0.294423, 10.196 to \
  -0.294423, 10.196 to \
  -0.294176, 10.196 to \
  -0.196076, 9.99841 to \
  -0.196076, -0 to \
  -0.294423, -0 to \
  -0.294423, 10.196 front fs empty border lc rgb '#6165' lw 0.200001
set object 4 polygon from \
  -0.392523, 10.1926 to \
  -0.392523, 10.1926 to \
  -0.392276, 10.1926 to \
  -0.294176, 9.99596 to \
  -0.294176, -0 to \
  -0.392523, -0 to \
  -0.392523, 10.1926 front fs empty border lc rgb '#6165' lw 0.200001
set object 5 polygon from \
  -0.490623, 10.1882 to \
  -0.490376, 10.1882 to \
  -0.392276, 9.99253 to \
  -0.392276, -0 to \
  -0.490623, -0 to \
  -0.490623, 10.1882 front fs empty border lc rgb '#6165' lw 0.200001
set object 6 polygon from \
  -0.588723, 10.1828 to \
  -0.588476, 10.1828 to \
  -0.490376, 9.98812 to \
  -0.490376, -0 to \
  -0.588723, -0 to \
  -0.588723, 10.1828 front fs empty border lc rgb '#6165' lw 0.200001
set object 7 polygon from \
  -0.686823, 10.1764 to \
  -0.686576, 10.1764 to \
  -0.588476, 9.98272 to \
  -0.588476, -0 to \
  -0.686823, -0 to \
  -0.686823, 10.1764 front fs empty border lc rgb '#6165' lw 0.200001
set object 8 polygon from \
  -0.784923, 10.169 to \
  -0.784676, 10.169 to \
  -0.686576, 9.97635 to \
  -0.686576, -0 to \
  -0.784923, -0 to \
  -0.784923, 10.169 front fs empty border lc rgb '#6165' lw 0.200001
set object 9 polygon from \
  -0.883023, 10.1607 to \
  -0.882776, 10.1607 to \
  -0.784676, 9.96899 to \
  -0.784676, -0 to \
  -0.883023, -0 to \
  -0.883023, 10.1607 front fs empty border lc rgb '#6165' lw 0.200001
set object 10 polygon from \
  -0.981123, 10.1514 to \
  -0.981123, 10.1514 to \
  -0.980876, 10.1514 to \
  -0.882776, 9.96065 to \
  -0.882776, -0 to \
  -0.981123, -0 to \
  -0.981123, 10.1514 front fs empty border lc rgb '#6165' lw 0.200001
set object 11 polygon from \
  -1.07922, 10.1411 to \
  -1.07897, 10.1411 to \
  -0.980876, 9.95134 to \
  -0.980876, -0 to \
  -1.07922, -0 to \
  -1.07922, 10.1411 front fs empty border lc rgb '#6165' lw 0.200001
set object 12 polygon from \
  -1.17732, 10.1298 to \
  -1.17732, 10.1298 to \
  -1.17707, 10.1298 to \
  -1.07897, 9.94104 to \
  -1.07897, -0 to \
  -1.17732, -0 to \
  -1.17732, 10.1298 front fs empty border lc rgb '#6165' lw 0.200001
set object 13 polygon from \
  -1.27542, 10.1175 to \
  -1.27517, 10.1175 to \
  -1.17707, 9.92976 to \
  -1.17707, -0 to \
  -1.27542, -0 to \
  -1.27542, 10.1175 front fs empty border lc rgb '#6165' lw 0.200001
set object 14 polygon from \
  -1.37352, 10.1043 to \
  -1.37352, 10.1043 to \
  -1.37327, 10.1043 to \
  -1.27517, 9.91749 to \
  -1.27517, -0 to \
  -1.37352, -0 to \
  -1.37352, 10.1043 front fs empty border lc rgb '#6165' lw 0.200001
set object 15 polygon from \
  -1.47162, 10.09 to \
  -1.47137, 10.0901 to \
  -1.37327, 9.90425 to \
  -1.37327, -0 to \
  -1.47162, -0 to \
  -1.47162, 10.09 front fs empty border lc rgb '#6165' lw 0.200001
set object 16 polygon from \
  -1.56972, 10.0748 to \
  -1.56947, 10.0749 to \
  -1.47137, 9.89003 to \
  -1.47137, -0 to \
  -1.56972, -0 to \
  -1.56972, 10.0748 front fs empty border lc rgb '#6165' lw 0.200001
set object 17 polygon from \
  -1.66782, 10.0586 to \
  -1.66757, 10.0587 to \
  -1.56947, 9.87482 to \
  -1.56947, -0 to \
  -1.66782, -0 to \
  -1.66782, 10.0586 front fs empty border lc rgb '#6165' lw 0.200001
set object 18 polygon from \
  -1.76592, 10.0415 to \
  -1.76592, 10.0415 to \
  -1.76567, 10.0415 to \
  -1.66757, 9.85864 to \
  -1.66757, -0 to \
  -1.76592, -0 to \
  -1.76592, 10.0415 front fs empty border lc rgb '#6165' lw 0.200001
set object 19 polygon from \
  -1.86402, 10.0233 to \
  -1.86377, 10.0234 to \
  -1.76567, 9.84147 to \
  -1.76567, -0 to \
  -1.86402, -0 to \
  -1.86402, 10.0233 front fs empty border lc rgb '#6165' lw 0.200001
set object 20 polygon from \
  -1.96212, 10.0042 to \
  -1.96187, 10.0042 to \
  -1.86377, 9.82333 to \
  -1.86377, -0 to \
  -1.96212, -0 to \
  -1.96212, 10.0042 front fs empty border lc rgb '#6165' lw 0.200001
set object 21 polygon from \
  -2.06022, 9.98404 to \
  -2.06022, 9.98404 to \
  -2.05997, 9.98409 to \
  -1.96187, 9.8042 to \
  -1.96187, -0 to \
  -2.06022, -0 to \
  -2.06022, 9.98404 front fs empty border lc rgb '#6165' lw 0.200001
set object 22 polygon from \
  -2.15832, 9.96295 to \
  -2.15832, 9.96295 to \
  -2.15807, 9.963 to \
  -2.05997, 9.78409 to \
  -2.05997, -0 to \
  -2.15832, -0 to \
  -2.15832, 9.96295 front fs empty border lc rgb '#6165' lw 0.200001
set object 23 polygon from \
  -2.25642, 9.94087 to \
  -2.25617, 9.94093 to \
  -2.15807, 9.763 to \
  -2.15807, -0 to \
  -2.25642, -0 to \
  -2.25642, 9.94087 front fs empty border lc rgb '#6165' lw 0.200001
set object 24 polygon from \
  -2.35452, 9.91782 to \
  -2.35427, 9.91787 to \
  -2.25617, 9.74093 to \
  -2.25617, -0 to \
  -2.35452, -0 to \
  -2.35452, 9.91782 front fs empty border lc rgb '#6165' lw 0.200001
set object 25 polygon from \
  -2.45262, 9.89378 to \
  -2.45237, 9.89384 to \
  -2.35427, 9.71787 to \
  -2.35427, -0 to \
  -2.45262, -0 to \
  -2.45262, 9.89378 front fs empty border lc rgb '#6165' lw 0.200001
set object 26 polygon from \
  -2.55072, 9.86876 to \
  -2.55047, 9.86883 to \
  -2.45237, 9.69384 to \
  -2.45237, -0 to \
  -2.55072, -0 to \
  -2.55072, 9.86876 front fs empty border lc rgb '#6165' lw 0.200001
set object 27 polygon from \
  -2.64882, 9.84277 to \
  -2.64857, 9.84283 to \
  -2.55047, 9.66883 to \
  -2.55047, -0 to \
  -2.64882, -0 to \
  -2.64882, 9.84277 front fs empty border lc rgb '#6165' lw 0.200001
set object 28 polygon from \
  -2.74692, 9.81579 to \
  -2.74692, 9.81579 to \
  -2.74667, 9.81585 to \
  -2.64857, 9.64283 to \
  -2.64857, -0 to \
  -2.74692, -0 to \
  -2.74692, 9.81579 front fs empty border lc rgb '#6165' lw 0.200001
set object 29 polygon from \
  -2.84502, 9.78783 to \
  -2.84502, 9.78783 to \
  -2.84477, 9.7879 to \
  -2.74667, 9.61586 to \
  -2.74667, -0 to \
  -2.84502, -0 to \
  -2.84502, 9.78783 front fs empty border lc rgb '#6165' lw 0.200001
set object 30 polygon from \
  -2.94312, 9.75889 to \
  -2.94312, 9.75889 to \
  -2.94287, 9.75896 to \
  -2.84477, 9.5879 to \
  -2.84477, -0 to \
  -2.94312, -0 to \
  -2.94312, 9.75889 front fs empty border lc rgb '#6165' lw 0.200001
set object 31 polygon from \
  -3.04122, 9.72897 to \
  -3.04122, 9.72897 to \
  -3.04097, 9.72904 to \
  -2.94287, 9.55896 to \
  -2.94287, -0 to \
  -3.04122, -0 to \
  -3.04122, 9.72897 front fs empty border lc rgb '#6165' lw 0.200001
set object 32 polygon from \
  -3.13932, 9.69806 to \
  -3.13932, 9.69806 to \
  -3.13907, 9.69814 to \
  -3.04097, 9.52904 to \
  -3.04097, -0 to \
  -3.13932, -0 to \
  -3.13932, 9.69806 front fs empty border lc rgb '#6165' lw 0.200001
set object 33 polygon from \
  -3.23742, 9.66618 to \
  -3.23742, 9.66618 to \
  -3.23717, 9.66626 to \
  -3.13907, 9.49814 to \
  -3.13907, -0 to \
  -3.23742, -0 to \
  -3.23742, 9.66618 front fs empty border lc rgb '#6165' lw 0.200001
set object 34 polygon from \
  -3.33552, 9.63331 to \
  -3.33552, 9.63331 to \
  -3.33527, 9.6334 to \
  -3.23717, 9.46626 to \
  -3.23717, -0 to \
  -3.33552, -0 to \
  -3.33552, 9.63331 front fs empty border lc rgb '#6165' lw 0.200001
set object 35 polygon from \
  -3.43362, 9.59947 to \
  -3.43337, 9.59955 to \
  -3.33527, 9.4334 to \
  -3.33527, -0 to \
  -3.43362, -0 to \
  -3.43362, 9.59947 front fs empty border lc rgb '#6165' lw 0.200001
set object 36 polygon from \
  -3.53172, 9.56464 to \
  -3.53172, 9.56464 to \
  -3.53147, 9.56473 to \
  -3.43337, 9.39955 to \
  -3.43337, -0 to \
  -3.53172, -0 to \
  -3.53172, 9.56464 front fs empty border lc rgb '#6165' lw 0.200001
set object 37 polygon from \
  -3.62982, 9.52883 to \
  -3.62957, 9.52892 to \
  -3.53147, 9.36473 to \
  -3.53147, -0 to \
  -3.62982, -0 to \
  -3.62982, 9.52883 front fs empty border lc rgb '#6165' lw 0.200001
set object 38 polygon from \
  -3.72792, 9.49205 to \
  -3.72767, 9.49214 to \
  -3.62957, 9.32892 to \
  -3.62957, -0 to \
  -3.72792, -0 to \
  -3.72792, 9.49205 front fs empty border lc rgb '#6165' lw 0.200001
set object 39 polygon from \
  -3.82602, 9.45428 to \
  -3.82602, 9.45428 to \
  -3.82577, 9.45437 to \
  -3.72767, 9.29214 to \
  -3.72767, -0 to \
  -3.82602, -0 to \
  -3.82602, 9.45428 front fs empty border lc rgb '#6165' lw 0.200001
set object 40 polygon from \
  -3.92412, 9.41553 to \
  -3.92412, 9.41553 to \
  -3.92387, 9.41562 to \
  -3.82577, 9.25437 to \
  -3.82577, -0 to \
  -3.92412, -0 to \
  -3.92412, 9.41553 front fs empty border lc rgb '#6165' lw 0.200001
set object 41 polygon from \
  -4.02222, 9.37579 to \
  -4.02222, 9.37579 to \
  -4.02197, 9.37589 to \
  -3.92387, 9.21562 to \
  -3.92387, -0 to \
  -4.02222, -0 to \
  -4.02222, 9.37579 front fs empty border lc rgb '#6165' lw 0.200001
set object 42 polygon from \
  -4.12032, 9.33508 to \
  -4.12032, 9.33508 to \
  -4.12007, 9.33518 to \
  -4.02197, 9.17589 to \
  -4.02197, -0 to \
  -4.12032, -0 to \
  -4.12032, 9.33508 front fs empty border lc rgb '#6165' lw 0.200001
set object 43 polygon from \
  -4.21842, 9.29339 to \
  -4.21842, 9.29339 to \
  -4.21817, 9.29349 to \
  -4.12007, 9.13518 to \
  -4.12007, -0 to \
  -4.21842, -0 to \
  -4.21842, 9.29339 front fs empty border lc rgb '#6165' lw 0.200001
set object 44 polygon from \
  -4.31652, 9.25071 to \
  -4.31652, 9.25071 to \
  -4.31627, 9.25082 to \
  -4.21817, 9.09349 to \
  -4.21817, -0 to \
  -4.31652, -0 to \
  -4.31652, 9.25071 front fs empty border lc rgb '#6165' lw 0.200001
set object 45 polygon from \
  -4.41462, 9.20706 to \
  -4.41462, 9.20706 to \
  -4.41437, 9.20716 to \
  -4.31627, 9.05082 to \
  -4.31627, -0 to \
  -4.41462, -0 to \
  -4.41462, 9.20706 front fs empty border lc rgb '#6165' lw 0.200001
set object 46 polygon from \
  -4.51272, 9.16242 to \
  -4.51272, 9.16242 to \
  -4.51247, 9.16253 to \
  -4.41437, 9.00717 to \
  -4.41437, -0 to \
  -4.51272, -0 to \
  -4.51272, 9.16242 front fs empty border lc rgb '#6165' lw 0.200001
set object 47 polygon from \
  -4.61082, 9.1168 to \
  -4.61057, 9.11692 to \
  -4.51247, 8.96253 to \
  -4.51247, -0 to \
  -4.61082, -0 to \
  -4.61082, 9.1168 front fs empty border lc rgb '#6165' lw 0.200001
set object 48 polygon from \
  -4.70892, 9.0702 to \
  -4.70867, 9.07032 to \
  -4.61057, 8.91692 to \
  -4.61057, -0 to \
  -4.70892, -0 to \
  -4.70892, 9.0702 front fs empty border lc rgb '#6165' lw 0.200001
set object 49 polygon from \
  -4.80702, 9.02262 to \
  -4.80677, 9.02274 to \
  -4.70867, 8.87032 to \
  -4.70867, -0 to \
  -4.80702, -0 to \
  -4.80702, 9.02262 front fs empty border lc rgb '#6165' lw 0.200001
set object 50 polygon from \
  -4.90512, 8.97406 to \
  -4.90487, 8.97418 to \
  -4.80677, 8.82274 to \
  -4.80677, -0 to \
  -4.90512, -0 to \
  -4.90512, 8.97406 front fs empty border lc rgb '#6165' lw 0.200001
set object 51 polygon from \
  -5.00322, 8.92452 to \
  -5.00297, 8.92464 to \
  -4.90487, 8.77418 to \
  -4.90487, -0 to \
  -5.00322, -0 to \
  -5.00322, 8.92452 front fs empty border lc rgb '#6165' lw 0.200001
set object 52 polygon from \
  -5.10132, 8.874 to \
  -5.10107, 8.87412 to \
  -5.00297, 8.72465 to \
  -5.00297, -0 to \
  -5.10132, -0 to \
  -5.10132, 8.874 front fs empty border lc rgb '#6165' lw 0.200001
set object 53 polygon from \
  -5.19942, 8.82249 to \
  -5.19917, 8.82262 to \
  -5.10107, 8.67413 to \
  -5.10107, -0 to \
  -5.19942, -0 to \
  -5.19942, 8.82249 front fs empty border lc rgb '#6165' lw 0.200001
set object 54 polygon from \
  -5.29752, 8.77001 to \
  -5.29727, 8.77014 to \
  -5.19917, 8.62262 to \
  -5.19917, -0 to \
  -5.29752, -0 to \
  -5.29752, 8.77001 front fs empty border lc rgb '#6165' lw 0.200001
set object 55 polygon from \
  -5.39562, 8.71654 to \
  -5.39537, 8.71668 to \
  -5.29727, 8.57014 to \
  -5.29727, -0 to \
  -5.39562, -0 to \
  -5.39562, 8.71654 front fs empty border lc rgb '#6165' lw 0.200001
set object 56 polygon from \
  -5.49372, 8.6621 to \
  -5.49347, 8.66223 to \
  -5.39537, 8.51668 to \
  -5.39537, -0 to \
  -5.49372, -0 to \
  -5.49372, 8.6621 front fs empty border lc rgb '#6165' lw 0.200001
set object 57 polygon from \
  -5.59182, 8.60667 to \
  -5.59157, 8.60681 to \
  -5.49347, 8.46223 to \
  -5.49347, -0 to \
  -5.59182, -0 to \
  -5.59182, 8.60667 front fs empty border lc rgb '#6165' lw 0.200001
set object 58 polygon from \
  -5.68992, 8.55026 to \
  -5.68967, 8.5504 to \
  -5.59157, 8.40681 to \
  -5.59157, -0 to \
  -5.68992, -0 to \
  -5.68992, 8.55026 front fs empty border lc rgb '#6165' lw 0.200001
set object 59 polygon from \
  -5.78802, 8.49287 to \
  -5.78777, 8.49301 to \
  -5.68967, 8.3504 to \
  -5.68967, -0 to \
  -5.78802, -0 to \
  -5.78802, 8.49287 front fs empty border lc rgb '#6165' lw 0.200001
set object 60 polygon from \
  -5.88612, 8.4345 to \
  -5.88587, 8.43465 to \
  -5.78777, 8.29302 to \
  -5.78777, -0 to \
  -5.88612, -0 to \
  -5.88612, 8.4345 front fs empty border lc rgb '#6165' lw 0.200001
set object 61 polygon from \
  -5.98422, 8.37515 to \
  -5.98397, 8.3753 to \
  -5.88587, 8.23465 to \
  -5.88587, -0 to \
  -5.98422, -0 to \
  -5.98422, 8.37515 front fs empty border lc rgb '#6165' lw 0.200001
set object 62 polygon from \
  -6.08232, 8.31482 to \
  -6.08207, 8.31497 to \
  -5.98397, 8.1753 to \
  -5.98397, -0 to \
  -6.08232, -0 to \
  -6.08232, 8.31482 front fs empty border lc rgb '#6165' lw 0.200001
set object 63 polygon from \
  -6.18042, 8.2535 to \
  -6.18017, 8.25366 to \
  -6.08207, 8.11497 to \
  -6.08207, -0 to \
  -6.18042, -0 to \
  -6.18042, 8.2535 front fs empty border lc rgb '#6165' lw 0.200001
set object 64 polygon from \
  -6.27852, 8.19121 to \
  -6.27827, 8.19136 to \
  -6.18017, 8.05366 to \
  -6.18017, -0 to \
  -6.27852, -0 to \
  -6.27852, 8.19121 front fs empty border lc rgb '#6165' lw 0.200001
set object 65 polygon from \
  -6.37662, 8.12793 to \
  -6.37637, 8.12809 to \
  -6.27827, 7.99136 to \
  -6.27827, -0 to \
  -6.37662, -0 to \
  -6.37662, 8.12793 front fs empty border lc rgb '#6165' lw 0.200001
set object 66 polygon from \
  -6.47472, 8.06368 to \
  -6.47447, 8.06384 to \
  -6.37637, 7.92809 to \
  -6.37637, -0 to \
  -6.47472, -0 to \
  -6.47472, 8.06368 front fs empty border lc rgb '#6165' lw 0.200001
set object 67 polygon from \
  -6.57282, 7.99844 to \
  -6.57257, 7.9986 to \
  -6.47447, 7.86384 to \
  -6.47447, -0 to \
  -6.57282, -0 to \
  -6.57282, 7.99844 front fs empty border lc rgb '#6165' lw 0.200001
set object 68 polygon from \
  -6.67092, 7.93222 to \
  -6.67067, 7.93238 to \
  -6.57257, 7.7986 to \
  -6.57257, -0 to \
  -6.67092, -0 to \
  -6.67092, 7.93222 front fs empty border lc rgb '#6165' lw 0.200001
set object 69 polygon from \
  -6.76902, 7.86502 to \
  -6.76877, 7.86519 to \
  -6.67067, 7.73238 to \
  -6.67067, -0 to \
  -6.76902, -0 to \
  -6.76902, 7.86502 front fs empty border lc rgb '#6165' lw 0.200001
set object 70 polygon from \
  -6.86712, 7.79684 to \
  -6.86687, 7.79701 to \
  -6.76877, 7.66519 to \
  -6.76877, -0 to \
  -6.86712, -0 to \
  -6.86712, 7.79684 front fs empty border lc rgb '#6165' lw 0.200001
set object 71 polygon from \
  -6.96522, 7.72768 to \
  -6.96497, 7.72785 to \
  -6.86687, 7.59701 to \
  -6.86687, -0 to \
  -6.96522, -0 to \
  -6.96522, 7.72768 front fs empty border lc rgb '#6165' lw 0.200001
set object 72 polygon from \
  -7.06332, 7.65753 to \
  -7.06307, 7.65771 to \
  -6.96497, 7.52785 to \
  -6.96497, -0 to \
  -7.06332, -0 to \
  -7.06332, 7.65753 front fs empty border lc rgb '#6165' lw 0.200001
set object 73 polygon from \
  -7.16142, 7.58641 to \
  -7.16117, 7.58659 to \
  -7.06307, 7.45771 to \
  -7.06307, -0 to \
  -7.16142, -0 to \
  -7.16142, 7.58641 front fs empty border lc rgb '#6165' lw 0.200001
set object 74 polygon from \
  -7.25952, 7.51431 to \
  -7.25927, 7.51449 to \
  -7.16117, 7.38659 to \
  -7.16117, -0 to \
  -7.25952, -0 to \
  -7.25952, 7.51431 front fs empty border lc rgb '#6165' lw 0.200001
set object 75 polygon from \
  -7.35762, 7.44122 to \
  -7.35737, 7.4414 to \
  -7.25927, 7.31449 to \
  -7.25927, -0 to \
  -7.35762, -0 to \
  -7.35762, 7.44122 front fs empty border lc rgb '#6165' lw 0.200001
set object 76 polygon from \
  -7.45572, 7.36715 to \
  -7.45547, 7.36734 to \
  -7.35737, 7.2414 to \
  -7.35737, -0 to \
  -7.45572, -0 to \
  -7.45572, 7.36715 front fs empty border lc rgb '#6165' lw 0.200001
set object 77 polygon from \
  -7.55382, 7.29211 to \
  -7.55357, 7.29229 to \
  -7.45547, 7.16734 to \
  -7.45547, -0 to \
  -7.55382, -0 to \
  -7.55382, 7.29211 front fs empty border lc rgb '#6165' lw 0.200001
set object 78 polygon from \
  -7.65192, 7.21608 to \
  -7.65167, 7.21627 to \
  -7.55357, 7.09229 to \
  -7.55357, -0 to \
  -7.65192, -0 to \
  -7.65192, 7.21608 front fs empty border lc rgb '#6165' lw 0.200001
set object 79 polygon from \
  -7.75002, 7.13907 to \
  -7.74977, 7.13926 to \
  -7.65167, 7.01627 to \
  -7.65167, -0 to \
  -7.75002, -0 to \
  -7.75002, 7.13907 front fs empty border lc rgb '#6165' lw 0.200001
set object 80 polygon from \
  -7.84812, 7.06108 to \
  -7.84787, 7.06127 to \
  -7.74977, 6.93926 to \
  -7.74977, -0 to \
  -7.84812, -0 to \
  -7.84812, 7.06108 front fs empty border lc rgb '#6165' lw 0.200001
set object 81 polygon from \
  -7.94622, 6.9821 to \
  -7.94597, 6.9823 to \
  -7.84787, 6.86127 to \
  -7.84787, -0 to \
  -7.94622, -0 to \
  -7.94622, 6.9821 front fs empty border lc rgb '#6165' lw 0.200001
set object 82 polygon from \
  -8.04432, 6.90215 to \
  -8.04407, 6.90235 to \
  -7.94597, 6.7823 to \
  -7.94597, -0 to \
  -8.04432, -0 to \
  -8.04432, 6.90215 front fs empty border lc rgb '#6165' lw 0.200001
set object 83 polygon from \
  -8.14242, 6.82122 to \
  -8.14217, 6.82142 to \
  -8.04407, 6.70235 to \
  -8.04407, -0 to \
  -8.14242, -0 to \
  -8.14242, 6.82122 front fs empty border lc rgb '#6165' lw 0.200001
set object 84 polygon from \
  -8.24052, 6.7393 to \
  -8.24027, 6.73951 to \
  -8.14217, 6.62142 to \
  -8.14217, -0 to \
  -8.24052, -0 to \
  -8.24052, 6.7393 front fs empty border lc rgb '#6165' lw 0.200001
set object 85 polygon from \
  -8.33862, 6.65641 to \
  -8.33837, 6.65661 to \
  -8.24027, 6.53951 to \
  -8.24027, -0 to \
  -8.33862, -0 to \
  -8.33862, 6.65641 front fs empty border lc rgb '#6165' lw 0.200001
set object 86 polygon from \
  -8.43672, 6.57253 to \
  -8.43647, 6.57274 to \
  -8.33837, 6.45662 to \
  -8.33837, -0 to \
  -8.43672, -0 to \
  -8.43672, 6.57253 front fs empty border lc rgb '#6165' lw 0.200001
set object 87 polygon from \
  -8.53482, 6.48767 to \
  -8.53457, 6.48788 to \
  -8.43647, 6.37274 to \
  -8.43647, -0 to \
  -8.53482, -0 to \
  -8.53482, 6.48767 front fs empty border lc rgb '#6165' lw 0.200001
set object 88 polygon from \
  -8.63292, 6.40183 to \
  -8.63267, 6.40205 to \
  -8.53457, 6.28789 to \
  -8.53457, -0 to \
  -8.63292, -0 to \
  -8.63292, 6.40183 front fs empty border lc rgb '#6165' lw 0.200001
set object 89 polygon from \
  -8.73102, 6.31501 to \
  -8.73077, 6.31523 to \
  -8.63267, 6.20205 to \
  -8.63267, -0 to \
  -8.73102, -0 to \
  -8.73102, 6.31501 front fs empty border lc rgb '#6165' lw 0.200001
set object 90 polygon from \
  -8.82912, 6.22721 to \
  -8.82887, 6.22743 to \
  -8.73077, 6.11523 to \
  -8.73077, -0 to \
  -8.82912, -0 to \
  -8.82912, 6.22721 front fs empty border lc rgb '#6165' lw 0.200001
set object 91 polygon from \
  -8.92722, 6.13843 to \
  -8.92697, 6.13865 to \
  -8.82887, 6.02743 to \
  -8.82887, -0 to \
  -8.92722, -0 to \
  -8.92722, 6.13843 front fs empty border lc rgb '#6165' lw 0.200001
set object 92 polygon from \
  -9.02532, 6.04867 to \
  -9.02507, 6.04889 to \
  -8.92697, 5.93865 to \
  -8.92697, -0 to \
  -9.02532, -0 to \
  -9.02532, 6.04867 front fs empty border lc rgb '#6165' lw 0.200001
set object 93 polygon from \
  -9.12342, 5.95793 to \
  -9.12317, 5.95815 to \
  -9.02507, 5.84889 to \
  -9.02507, -0 to \
  -9.12342, -0 to \
  -9.12342, 5.95793 front fs empty border lc rgb '#6165' lw 0.200001
set object 94 polygon from \
  -9.22152, 5.8662 to \
  -9.22127, 5.86643 to \
  -9.12317, 5.75815 to \
  -9.12317, -0 to \
  -9.22152, -0 to \
  -9.22152, 5.8662 front fs empty border lc rgb '#6165' lw 0.200001
set object 95 polygon from \
  -9.31962, 5.7735 to \
  -9.31937, 5.77373 to \
  -9.22127, 5.66643 to \
  -9.22127, -0 to \
  -9.31962, -0 to \
  -9.31962, 5.7735 front fs empty border lc rgb '#6165' lw 0.200001
set object 96 polygon from \
  -9.41772, 5.67981 to \
  -9.41747, 5.68004 to \
  -9.31937, 5.57373 to \
  -9.31937, -0 to \
  -9.41772, -0 to \
  -9.41772, 5.67981 front fs empty border lc rgb '#6165' lw 0.200001
set object 97 polygon from \
  -9.51582, 5.58514 to \
  -9.51557, 5.58538 to \
  -9.41747, 5.48004 to \
  -9.41747, -0 to \
  -9.51582, -0 to \
  -9.51582, 5.58514 front fs empty border lc rgb '#6165' lw 0.200001
set object 98 polygon from \
  -9.61392, 5.48949 to \
  -9.61367, 5.48973 to \
  -9.51557, 5.38538 to \
  -9.51557, -0 to \
  -9.61392, -0 to \
  -9.61392, 5.48949 front fs empty border lc rgb '#6165' lw 0.200001
set object 99 polygon from \
  -9.71202, 5.39286 to \
  -9.71177, 5.3931 to \
  -9.61367, 5.28973 to \
  -9.61367, -0 to \
  -9.71202, -0 to \
  -9.71202, 5.39286 front fs empty border lc rgb '#6165' lw 0.200001
set object 100 polygon from \
  -9.81012, 5.29525 to \
  -9.80987, 5.2955 to \
  -9.71177, 5.1931 to \
  -9.71177, -0 to \
  -9.81012, -0 to \
  -9.81012, 5.29525 front fs empty border lc rgb '#6165' lw 0.200001
set object 101 polygon from \
  -9.90822, 5.19666 to \
  -9.90797, 5.19691 to \
  -9.80987, 5.0955 to \
  -9.80987, -0 to \
  -9.90822, -0 to \
  -9.90822, 5.19666 front fs empty border lc rgb '#6165' lw 0.200001
set object 102 polygon from \
  -10.0063, 5.09709 to \
  -10.006, 5.09734 to \
  -9.90797, 4.99691 to \
  -9.90797, -0 to \
  -10.0063, -0 to \
  -10.0063, 5.09709 front fs empty border lc rgb '#6165' lw 0.200001
set object 103 polygon from \
  -10.1044, 4.99653 to \
  -10.1041, 4.99678 to \
  -10.006, 4.89734 to \
  -10.006, -0 to \
  -10.1044, -0 to \
  -10.1044, 4.99653 front fs empty border lc rgb '#6165' lw 0.200001
set object 104 polygon from \
  -10.2025, 4.895 to \
  -10.2022, 4.89525 to \
  -10.1041, 4.79679 to \
  -10.1041, -0 to \
  -10.2025, -0 to \
  -10.2025, 4.895 front fs empty border lc rgb '#6165' lw 0.200001
set object 105 polygon from \
  -10.3006, 4.79248 to \
  -10.3003, 4.79274 to \
  -10.2022, 4.69525 to \
  -10.2022, -0 to \
  -10.3006, -0 to \
  -10.3006, 4.79248 front fs empty border lc rgb '#6165' lw 0.200001
set object 106 polygon from \
  -10.3987, 4.68899 to \
  -10.3984, 4.68924 to \
  -10.3003, 4.59274 to \
  -10.3003, -0 to \
  -10.3987, -0 to \
  -10.3987, 4.68899 front fs empty border lc rgb '#6165' lw 0.200001
set object 107 polygon from \
  -10.4968, 4.58451 to \
  -10.4965, 4.58477 to \
  -10.3984, 4.48925 to \
  -10.3984, -0 to \
  -10.4968, -0 to \
  -10.4968, 4.58451 front fs empty border lc rgb '#6165' lw 0.200001
set object 108 polygon from \
  -10.5949, 4.47905 to \
  -10.5946, 4.47931 to \
  -10.4965, 4.38477 to \
  -10.4965, -0 to \
  -10.5949, -0 to \
  -10.5949, 4.47905 front fs empty border lc rgb '#6165' lw 0.200001
set object 109 polygon from \
  -10.693, 4.37261 to \
  -10.6927, 4.37288 to \
  -10.5946, 4.27931 to \
  -10.5946, -0 to \
  -10.693, -0 to \
  -10.693, 4.37261 front fs empty border lc rgb '#6165' lw 0.200001
set object 110 polygon from \
  -10.7911, 4.26519 to \
  -10.7908, 4.26546 to \
  -10.6927, 4.17288 to \
  -10.6927, -0 to \
  -10.7911, -0 to \
  -10.7911, 4.26519 front fs empty border lc rgb '#6165' lw 0.200001
set object 111 polygon from \
  -10.8892, 4.15679 to \
  -10.8889, 4.15706 to \
  -10.7908, 4.06546 to \
  -10.7908, -0 to \
  -10.8892, -0 to \
  -10.8892, 4.15679 front fs empty border lc rgb '#6165' lw 0.200001
set object 112 polygon from \
  -10.9873, 4.0474 to \
  -10.987, 4.04768 to \
  -10.8889, 3.95706 to \
  -10.8889, -0 to \
  -10.9873, -0 to \
  -10.9873, 4.0474 front fs empty border lc rgb '#6165' lw 0.200001
set object 113 polygon from \
  -11.0854, 3.93704 to \
  -11.0851, 3.93732 to \
  -10.987, 3.84768 to \
  -10.987, -0 to \
  -11.0854, -0 to \
  -11.0854, 3.93704 front fs empty border lc rgb '#6165' lw 0.200001
set object 114 polygon from \
  -11.1835, 3.8257 to \
  -11.1832, 3.82597 to \
  -11.0851, 3.73732 to \
  -11.0851, -0 to \
  -11.1835, -0 to \
  -11.1835, 3.8257 front fs empty border lc rgb '#6165' lw 0.200001
set object 115 polygon from \
  -11.2816, 3.71337 to \
  -11.2813, 3.71365 to \
  -11.1832, 3.62598 to \
  -11.1832, -0 to \
  -11.2816, -0 to \
  -11.2816, 3.71337 front fs empty border lc rgb '#6165' lw 0.200001
set object 116 polygon from \
  -11.3797, 3.60006 to \
  -11.3794, 3.60035 to \
  -11.2813, 3.51365 to \
  -11.2813, -0 to \
  -11.3797, -0 to \
  -11.3797, 3.60006 front fs empty border lc rgb '#6165' lw 0.200001
set object 117 polygon from \
  -11.4778, 3.48578 to \
  -11.4775, 3.48606 to \
  -11.3794, 3.40035 to \
  -11.3794, -0 to \
  -11.4778, -0 to \
  -11.4778, 3.48578 front fs empty border lc rgb '#6165' lw 0.200001
set object 118 polygon from \
  -11.5759, 3.37051 to \
  -11.5756, 3.3708 to \
  -11.4775, 3.28606 to \
  -11.4775, -0 to \
  -11.5759, -0 to \
  -11.5759, 3.37051 front fs empty border lc rgb '#6165' lw 0.200001
set object 119 polygon from \
  -11.674, 3.25426 to \
  -11.6737, 3.25455 to \
  -11.5756, 3.1708 to \
  -11.5756, -0 to \
  -11.674, -0 to \
  -11.674, 3.25426 front fs empty border lc rgb '#6165' lw 0.200001
set object 120 polygon from \
  -11.7721, 3.13703 to \
  -11.7718, 3.13732 to \
  -11.6737, 3.05455 to \
  -11.6737, -0 to \
  -11.7721, -0 to \
  -11.7721, 3.13703 front fs empty border lc rgb '#6165' lw 0.200001
set object 121 polygon from \
  -11.8702, 3.01882 to \
  -11.8699, 3.01911 to \
  -11.7718, 2.93732 to \
  -11.7718, -0 to \
  -11.8702, -0 to \
  -11.8702, 3.01882 front fs empty border lc rgb '#6165' lw 0.200001
set object 122 polygon from \
  -11.9683, 2.89962 to \
  -11.968, 2.89992 to \
  -11.8699, 2.81911 to \
  -11.8699, -0 to \
  -11.9683, -0 to \
  -11.9683, 2.89962 front fs empty border lc rgb '#6165' lw 0.200001
set object 123 polygon from \
  -12.0664, 2.77945 to \
  -12.0661, 2.77975 to \
  -11.968, 2.69992 to \
  -11.968, -0 to \
  -12.0664, -0 to \
  -12.0664, 2.77945 front fs empty border lc rgb '#6165' lw 0.200001
set object 124 polygon from \
  -12.1645, 2.65829 to \
  -12.1642, 2.6586 to \
  -12.0661, 2.57975 to \
  -12.0661, -0 to \
  -12.1645, -0 to \
  -12.1645, 2.65829 front fs empty border lc rgb '#6165' lw 0.200001
set object 125 polygon from \
  -12.2626, 2.53616 to \
  -12.2623, 2.53646 to \
  -12.1642, 2.4586 to \
  -12.1642, -0 to \
  -12.2626, -0 to \
  -12.2626, 2.53616 front fs empty border lc rgb '#6165' lw 0.200001
set object 126 polygon from \
  -12.3607, 2.41304 to \
  -12.3604, 2.41335 to \
  -12.2623, 2.33646 to \
  -12.2623, -0 to \
  -12.3607, -0 to \
  -12.3607, 2.41304 front fs empty border lc rgb '#6165' lw 0.200001
set object 127 polygon from \
  -12.4588, 2.28894 to \
  -12.4585, 2.28925 to \
  -12.3604, 2.21335 to \
  -12.3604, -0 to \
  -12.4588, -0 to \
  -12.4588, 2.28894 front fs empty border lc rgb '#6165' lw 0.200001
set object 128 polygon from \
  -12.5569, 2.16387 to \
  -12.5566, 2.16418 to \
  -12.4585, 2.08926 to \
  -12.4585, -0 to \
  -12.5569, -0 to \
  -12.5569, 2.16387 front fs empty border lc rgb '#6165' lw 0.200001
set object 129 polygon from \
  -12.655, 2.03781 to \
  -12.6547, 2.03812 to \
  -12.5566, 1.96418 to \
  -12.5566, -0 to \
  -12.655, -0 to \
  -12.655, 2.03781 front fs empty border lc rgb '#6165' lw 0.200001
set object 130 polygon from \
  -12.7531, 1.91076 to \
  -12.7528, 1.91108 to \
  -12.6547, 1.83812 to \
  -12.6547, -0 to \
  -12.7531, -0 to \
  -12.7531, 1.91076 front fs empty border lc rgb '#6165' lw 0.200001
set object 131 polygon from \
  -12.8512, 1.78274 to \
  -12.8509, 1.78306 to \
  -12.7528, 1.71108 to \
  -12.7528, -0 to \
  -12.8512, -0 to \
  -12.8512, 1.78274 front fs empty border lc rgb '#6165' lw 0.200001
set object 132 polygon from \
  -12.9493, 1.65374 to \
  -12.949, 1.65406 to \
  -12.8509, 1.58306 to \
  -12.8509, -0 to \
  -12.9493, -0 to \
  -12.9493, 1.65374 front fs empty border lc rgb '#6165' lw 0.200001
set object 133 polygon from \
  -13.0474, 1.52376 to \
  -13.0471, 1.52408 to \
  -12.949, 1.45406 to \
  -12.949, -0 to \
  -13.0474, -0 to \
  -13.0474, 1.52376 front fs empty border lc rgb '#6165' lw 0.200001
set object 134 polygon from \
  -13.1455, 1.39279 to \
  -13.1452, 1.39312 to \
  -13.0471, 1.32408 to \
  -13.0471, -0 to \
  -13.1455, -0 to \
  -13.1455, 1.39279 front fs empty border lc rgb '#6165' lw 0.200001
set object 135 polygon from \
  -13.2436, 1.26085 to \
  -13.2433, 1.26118 to \
  -13.1452, 1.19312 to \
  -13.1452, -0 to \
  -13.2436, -0 to \
  -13.2436, 1.26085 front fs empty border lc rgb '#6165' lw 0.200001
set object 136 polygon from \
  -13.3414, 1.12825 to \
  -13.2433, 1.06118 to \
  -13.2433, -0 to \
  -13.3417, -0 to \
  -13.3417, 1.12792 to \
  -13.3414, 1.12825 front fs empty border lc rgb '#6165' lw 0.200001
set object 137 polygon from \
  -13.4398, 0.994007 to \
  -13.4395, 0.994342 to \
  -13.3414, 0.928248 to \
  -13.3414, -0 to \
  -13.4398, -0 to \
  -13.4398, 0.994007 front fs empty border lc rgb '#6165' lw 0.200001
set object 138 polygon from \
  -13.5379, 0.859118 to \
  -13.5376, 0.859455 to \
  -13.4395, 0.794343 to \
  -13.4395, -0 to \
  -13.5379, -0 to \
  -13.5379, 0.859118 front fs empty border lc rgb '#6165' lw 0.200001
set object 139 polygon from \
  -13.636, 0.723248 to \
  -13.6357, 0.723588 to \
  -13.5376, 0.659457 to \
  -13.5376, -0 to \
  -13.636, -0 to \
  -13.636, 0.723248 front fs empty border lc rgb '#6165' lw 0.200001
set object 140 polygon from \
  -13.7341, 0.586398 to \
  -13.7338, 0.58674 to \
  -13.6357, 0.523589 to \
  -13.6357, -0 to \
  -13.7341, -0 to \
  -13.7341, 0.586398 front fs empty border lc rgb '#6165' lw 0.200001
set object 141 polygon from \
  -13.8322, 0.448566 to \
  -13.8319, 0.448911 to \
  -13.7338, 0.386741 to \
  -13.7338, -0 to \
  -13.8322, -0 to \
  -13.8322, 0.448566 front fs empty border lc rgb '#6165' lw 0.200001
set object 142 polygon from \
  -13.9303, 0.309753 to \
  -13.93, 0.3101 to \
  -13.8319, 0.248912 to \
  -13.8319, -0 to \
  -13.9303, -0 to \
  -13.9303, 0.309753 front fs empty border lc rgb '#6165' lw 0.200001
set object 143 polygon from \
  -14.0284, 0.16996 to \
  -14.0281, 0.170309 to \
  -13.93, 0.110101 to \
  -13.93, -0 to \
  -14.0284, -0 to \
  -14.0284, 0.16996 front fs empty border lc rgb '#6165' lw 0.200001
set object 144 polygon from \
  -14.1265, 0.0291844 to \
  -14.1262, 0.0295363 to \
  -14.0773, -0 to \
  -14.1265, -0 to \
  -14.1265, 0.0291844 front fs empty border lc rgb '#6165' lw 0.200001
set object 145 polygon from \
  -0.000123033, 0.000368285 to \
  10.5951, 0.000368285 to \
  10.5951, 0 to \
  -0.0737799, -0 to \
  -0.000123033, 0.000368285 front fs empty border lc rgb '#6165' lw 0.200001
set object 146 polygon from \
  10.497, 0.105828 to \
  10.497, 0.10546 to \
  -0.04905, -0 to \
  -0.0858784, -0 to \
  10.497, 0.105828 front fs empty border lc rgb '#6165' lw 0.200001
set object 147 polygon from \
  10.3989, 0.210307 to \
  10.3989, 0.209939 to \
  -0.0980999, -0 to \
  -0.116514, -0 to \
  10.3989, 0.210307 front fs empty border lc rgb '#6165' lw 0.200001
set object 148 polygon from \
  10.3008, 0.313805 to \
  10.3008, 0.313436 to \
  -0.147149, -0 to \
  -0.159426, -0 to \
  10.3008, 0.313805 front fs empty border lc rgb '#6165' lw 0.200001
set object 149 polygon from \
  10.2027, 0.416321 to \
  10.2027, 0.415953 to \
  -0.196199, -0 to \
  -0.205407, -0 to \
  10.2027, 0.416321 front fs empty border lc rgb '#6165' lw 0.200001
set object 150 polygon from \
  10.1046, 0.517857 to \
  10.1046, 0.517489 to \
  -0.245249, -0 to \
  -0.252615, -0 to \
  10.1046, 0.517857 front fs empty border lc rgb '#6165' lw 0.200001
set object 151 polygon from \
  10.0065, 0.618412 to \
  10.0065, 0.618043 to \
  -0.294299, -0 to \
  -0.300438, -0 to \
  10.0065, 0.618412 front fs empty border lc rgb '#6165' lw 0.200001
set object 152 polygon from \
  9.90832, 0.717985 to \
  9.90832, 0.717617 to \
  -0.343349, -0 to \
  -0.348611, -0 to \
  9.90832, 0.717985 front fs empty border lc rgb '#6165' lw 0.200001
set object 153 polygon from \
  9.81022, 0.816578 to \
  9.81022, 0.81621 to \
  -0.392399, -0 to \
  -0.397003, -0 to \
  9.81022, 0.816578 front fs empty border lc rgb '#6165' lw 0.200001
set object 154 polygon from \
  9.71212, 0.91419 to \
  9.71212, 0.913821 to \
  -0.441449, -0 to \
  -0.445542, -0 to \
  9.71212, 0.91419 front fs empty border lc rgb '#6165' lw 0.200001
set object 155 polygon from \
  9.61402, 1.01082 to \
  9.61402, 1.01046 to \
  -0.490499, -0 to \
  -0.494182, -0 to \
  9.61402, 1.01082 front fs empty border lc rgb '#6165' lw 0.200001
set object 156 polygon from \
  9.51592, 1.10647 to \
  9.51592, 1.10611 to \
  -0.539549, -0 to \
  -0.542898, -0 to \
  9.51592, 1.10647 front fs empty border lc rgb '#6165' lw 0.200001
set object 157 polygon from \
  9.41782, 1.20114 to \
  9.41782, 1.20077 to \
  -0.588599, -0 to \
  -0.591669, -0 to \
  9.41782, 1.20114 front fs empty border lc rgb '#6165' lw 0.200001
set object 158 polygon from \
  9.31972, 1.29483 to \
  9.31972, 1.29446 to \
  -0.637649, -0 to \
  -0.640482, -0 to \
  9.31972, 1.29483 front fs empty border lc rgb '#6165' lw 0.200001
set object 159 polygon from \
  9.22162, 1.38754 to \
  9.22162, 1.38717 to \
  -0.686699, -0 to \
  -0.68933, -0 to \
  9.22162, 1.38754 front fs empty border lc rgb '#6165' lw 0.200001
set object 160 polygon from \
  9.12352, 1.47926 to \
  9.12352, 1.47889 to \
  -0.735749, -0 to \
  -0.738205, -0 to \
  9.12352, 1.47926 front fs empty border lc rgb '#6165' lw 0.200001
set object 161 polygon from \
  9.02542, 1.57001 to \
  9.02542, 1.56964 to \
  -0.784799, -0 to \
  -0.787101, -0 to \
  9.02542, 1.57001 front fs empty border lc rgb '#6165' lw 0.200001
set object 162 polygon from \
  8.92732, 1.65977 to \
  8.92732, 1.6594 to \
  -0.833849, -0 to \
  -0.836016, -0 to \
  8.92732, 1.65977 front fs empty border lc rgb '#6165' lw 0.200001
set object 163 polygon from \
  8.82922, 1.74855 to \
  8.82922, 1.74819 to \
  -0.882899, -0 to \
  -0.884946, -0 to \
  8.82922, 1.74855 front fs empty border lc rgb '#6165' lw 0.200001
set object 164 polygon from \
  8.73112, 1.83636 to \
  8.73112, 1.83599 to \
  -0.931949, -0 to \
  -0.933888, -0 to \
  8.73112, 1.83636 front fs empty border lc rgb '#6165' lw 0.200001
set object 165 polygon from \
  8.63302, 1.92318 to \
  8.63302, 1.92281 to \
  -0.980999, -0 to \
  -0.982841, -0 to \
  8.63302, 1.92318 front fs empty border lc rgb '#6165' lw 0.200001
set object 166 polygon from \
  8.53492, 2.00902 to \
  8.53492, 2.00865 to \
  -1.03004, -0 to \
  -1.0318, -0 to \
  8.53492, 2.00902 front fs empty border lc rgb '#6165' lw 0.200001
set object 167 polygon from \
  8.43682, 2.09387 to \
  8.43682, 2.09351 to \
  -1.07909, -0 to \
  -1.08077, -0 to \
  8.43682, 2.09387 front fs empty border lc rgb '#6165' lw 0.200001
set object 168 polygon from \
  8.33872, 2.17775 to \
  8.33872, 2.17738 to \
  -1.12814, -0 to \
  -1.12975, -0 to \
  8.33872, 2.17775 front fs empty border lc rgb '#6165' lw 0.200001
set object 169 polygon from \
  8.24062, 2.26065 to \
  8.24062, 2.26028 to \
  -1.17719, -0 to \
  -1.17873, -0 to \
  8.24062, 2.26065 front fs empty border lc rgb '#6165' lw 0.200001
set object 170 polygon from \
  8.14252, 2.34256 to \
  8.14252, 2.3422 to \
  -1.22624, -0 to \
  -1.22772, -0 to \
  8.14252, 2.34256 front fs empty border lc rgb '#6165' lw 0.200001
set object 171 polygon from \
  8.04442, 2.4235 to \
  8.04442, 2.42313 to \
  -1.27529, -0 to \
  -1.27671, -0 to \
  8.04442, 2.4235 front fs empty border lc rgb '#6165' lw 0.200001
set object 172 polygon from \
  7.94632, 2.50345 to \
  7.94632, 2.50308 to \
  -1.32434, -0 to \
  -1.32571, -0 to \
  7.94632, 2.50345 front fs empty border lc rgb '#6165' lw 0.200001
set object 173 polygon from \
  7.84822, 2.58243 to \
  7.84822, 2.58206 to \
  -1.37339, -0 to \
  -1.37471, -0 to \
  7.84822, 2.58243 front fs empty border lc rgb '#6165' lw 0.200001
set object 174 polygon from \
  7.75012, 2.66042 to \
  7.75012, 2.66005 to \
  -1.42244, -0 to \
  -1.42371, -0 to \
  7.75012, 2.66042 front fs empty border lc rgb '#6165' lw 0.200001
set object 175 polygon from \
  7.65202, 2.73743 to \
  7.65202, 2.73706 to \
  -1.47149, -0 to \
  -1.47272, -0 to \
  7.65202, 2.73743 front fs empty border lc rgb '#6165' lw 0.200001
set object 176 polygon from \
  7.55392, 2.81346 to \
  7.55392, 2.81309 to \
  -1.52054, -0 to \
  -1.52173, -0 to \
  7.55392, 2.81346 front fs empty border lc rgb '#6165' lw 0.200001
set object 177 polygon from \
  7.45582, 2.88851 to \
  7.45582, 2.88814 to \
  -1.56959, -0 to \
  -1.57075, -0 to \
  7.45582, 2.88851 front fs empty border lc rgb '#6165' lw 0.200001
set object 178 polygon from \
  7.35772, 2.96257 to \
  7.35772, 2.96221 to \
  -1.61864, -0 to \
  -1.61976, -0 to \
  7.35772, 2.96257 front fs empty border lc rgb '#6165' lw 0.200001
set object 179 polygon from \
  7.25962, 3.03566 to \
  7.25962, 3.03529 to \
  -1.66769, -0 to \
  -1.66878, -0 to \
  7.25962, 3.03566 front fs empty border lc rgb '#6165' lw 0.200001
set object 180 polygon from \
  7.16152, 3.10777 to \
  7.16152, 3.1074 to \
  -1.71674, -0 to \
  -1.7178, -0 to \
  7.16152, 3.10777 front fs empty border lc rgb '#6165' lw 0.200001
set object 181 polygon from \
  7.06342, 3.17889 to \
  7.06342, 3.17852 to \
  -1.76579, -0 to \
  -1.76682, -0 to \
  7.06342, 3.17889 front fs empty border lc rgb '#6165' lw 0.200001
set object 182 polygon from \
  6.96532, 3.24903 to \
  6.96532, 3.24867 to \
  -1.81484, -0 to \
  -1.81584, -0 to \
  6.96532, 3.24903 front fs empty border lc rgb '#6165' lw 0.200001
set object 183 polygon from \
  6.86722, 3.3182 to \
  6.86722, 3.31783 to \
  -1.86389, -0 to \
  -1.86486, -0 to \
  6.86722, 3.3182 front fs empty border lc rgb '#6165' lw 0.200001
set object 184 polygon from \
  6.76912, 3.38638 to \
  6.76912, 3.38601 to \
  -1.91294, -0 to \
  -1.91389, -0 to \
  6.76912, 3.38638 front fs empty border lc rgb '#6165' lw 0.200001
set object 185 polygon from \
  6.67102, 3.45358 to \
  6.67102, 3.45321 to \
  -1.96199, -0 to \
  -1.96292, -0 to \
  6.67102, 3.45358 front fs empty border lc rgb '#6165' lw 0.200001
set object 186 polygon from \
  6.57292, 3.5198 to \
  6.57292, 3.51943 to \
  -2.01104, -0 to \
  -2.01194, -0 to \
  6.57292, 3.5198 front fs empty border lc rgb '#6165' lw 0.200001
set object 187 polygon from \
  6.47482, 3.58504 to \
  6.47482, 3.58467 to \
  -2.06009, -0 to \
  -2.06097, -0 to \
  6.47482, 3.58504 front fs empty border lc rgb '#6165' lw 0.200001
set object 188 polygon from \
  6.37672, 3.6493 to \
  6.37672, 3.64893 to \
  -2.10914, -0 to \
  -2.11, -0 to \
  6.37672, 3.6493 front fs empty border lc rgb '#6165' lw 0.200001
set object 189 polygon from \
  6.27862, 3.71257 to \
  6.27862, 3.7122 to \
  -2.15819, -0 to \
  -2.15903, -0 to \
  6.27862, 3.71257 front fs empty border lc rgb '#6165' lw 0.200001
set object 190 polygon from \
  6.18052, 3.77487 to \
  6.18052, 3.7745 to \
  -2.20724, -0 to \
  -2.20806, -0 to \
  6.18052, 3.77487 front fs empty border lc rgb '#6165' lw 0.200001
set object 191 polygon from \
  6.08242, 3.83618 to \
  6.08242, 3.83581 to \
  -2.25629, -0 to \
  -2.2571, -0 to \
  6.08242, 3.83618 front fs empty border lc rgb '#6165' lw 0.200001
set object 192 polygon from \
  5.98432, 3.89652 to \
  5.98432, 3.89615 to \
  -2.30534, -0 to \
  -2.30613, -0 to \
  5.98432, 3.89652 front fs empty border lc rgb '#6165' lw 0.200001
set object 193 polygon from \
  5.88622, 3.95587 to \
  5.88622, 3.9555 to \
  -2.35439, -0 to \
  -2.35516, -0 to \
  5.88622, 3.95587 front fs empty border lc rgb '#6165' lw 0.200001
set object 194 polygon from \
  5.78812, 4.01424 to \
  5.78812, 4.01387 to \
  -2.40344, -0 to \
  -2.4042, -0 to \
  5.78812, 4.01424 front fs empty border lc rgb '#6165' lw 0.200001
set object 195 polygon from \
  5.69002, 4.07163 to \
  5.69002, 4.07126 to \
  -2.45249, -0 to \
  -2.45323, -0 to \
  5.69002, 4.07163 front fs empty border lc rgb '#6165' lw 0.200001
set object 196 polygon from \
  5.59192, 4.12804 to \
  5.59192, 4.12767 to \
  -2.50154, -0 to \
  -2.50227, -0 to \
  5.59192, 4.12804 front fs empty border lc rgb '#6165' lw 0.200001
set object 197 polygon from \
  5.49382, 4.18347 to \
  5.49382, 4.1831 to \
  -2.55059, -0 to \
  -2.5513, -0 to \
  5.49382, 4.18347 front fs empty border lc rgb '#6165' lw 0.200001
set object 198 polygon from \
  5.39572, 4.23792 to \
  5.39572, 4.23755 to \
  -2.59964, -0 to \
  -2.60034, -0 to \
  5.39572, 4.23792 front fs empty border lc rgb '#6165' lw 0.200001
set object 199 polygon from \
  5.29762, 4.29138 to \
  5.29762, 4.29102 to \
  -2.64869, -0 to \
  -2.64938, -0 to \
  5.29762, 4.29138 front fs empty border lc rgb '#6165' lw 0.200001
set object 200 polygon from \
  5.19952, 4.34387 to \
  5.19952, 4.3435 to \
  -2.69774, -0 to \
  -2.69841, -0 to \
  5.19952, 4.34387 front fs empty border lc rgb '#6165' lw 0.200001
set object 201 polygon from \
  5.10142, 4.39537 to \
  5.10142, 4.39501 to \
  -2.74679, -0 to \
  -2.74745, -0 to \
  5.10142, 4.39537 front fs empty border lc rgb '#6165' lw 0.200001
set object 202 polygon from \
  5.00332, 4.4459 to \
  5.00332, 4.44553 to \
  -2.79584, -0 to \
  -2.79649, -0 to \
  5.00332, 4.4459 front fs empty border lc rgb '#6165' lw 0.200001
set object 203 polygon from \
  4.90522, 4.49544 to \
  4.90522, 4.49507 to \
  -2.84489, -0 to \
  -2.84553, -0 to \
  4.90522, 4.49544 front fs empty border lc rgb '#6165' lw 0.200001
set object 204 polygon from \
  4.80712, 4.544 to \
  4.80712, 4.54363 to \
  -2.89394, -0 to \
  -2.89457, -0 to \
  4.80712, 4.544 front fs empty border lc rgb '#6165' lw 0.200001
set object 205 polygon from \
  4.70902, 4.59158 to \
  4.70902, 4.59121 to \
  -2.94299, -0 to \
  -2.94361, -0 to \
  4.70902, 4.59158 front fs empty border lc rgb '#6165' lw 0.200001
set object 206 polygon from \
  4.61092, 4.63818 to \
  4.61092, 4.63781 to \
  -2.99204, -0 to \
  -2.99265, -0 to \
  4.61092, 4.63818 front fs empty border lc rgb '#6165' lw 0.200001
set object 207 polygon from \
  4.51282, 4.6838 to \
  4.51282, 4.68343 to \
  -3.04109, -0 to \
  -3.04169, -0 to \
  4.51282, 4.6838 front fs empty border lc rgb '#6165' lw 0.200001
set object 208 polygon from \
  4.41472, 4.72844 to \
  4.41472, 4.72807 to \
  -3.09014, -0 to \
  -3.09073, -0 to \
  4.41472, 4.72844 front fs empty border lc rgb '#6165' lw 0.200001
set object 209 polygon from \
  4.31662, 4.7721 to \
  4.31662, 4.77173 to \
  -3.13919, -0 to \
  -3.13977, -0 to \
  4.31662, 4.7721 front fs empty border lc rgb '#6165' lw 0.200001
set object 210 polygon from \
  4.21852, 4.81477 to \
  4.21852, 4.8144 to \
  -3.18824, -0 to \
  -3.18881, -0 to \
  4.21852, 4.81477 front fs empty border lc rgb '#6165' lw 0.200001
set object 211 polygon from \
  4.12042, 4.85647 to \
  4.12042, 4.8561 to \
  -3.23729, -0 to \
  -3.23785, -0 to \
  4.12042, 4.85647 front fs empty border lc rgb '#6165' lw 0.200001
set object 212 polygon from \
  4.02232, 4.89718 to \
  4.02232, 4.89681 to \
  -3.28634, -0 to \
  -3.28689, -0 to \
  4.02232, 4.89718 front fs empty border lc rgb '#6165' lw 0.200001
set object 213 polygon from \
  3.92422, 4.93691 to \
  3.92422, 4.93654 to \
  -3.33539, -0 to \
  -3.33594, -0 to \
  3.92422, 4.93691 front fs empty border lc rgb '#6165' lw 0.200001
set object 214 polygon from \
  3.82612, 4.97566 to \
  3.82612, 4.9753 to \
  -3.38444, -0 to \
  -3.38498, -0 to \
  3.82612, 4.97566 front fs empty border lc rgb '#6165' lw 0.200001
set object 215 polygon from \
  3.72802, 5.01343 to \
  3.72802, 5.01307 to \
  -3.43349, -0 to \
  -3.43402, -0 to \
  3.72802, 5.01343 front fs empty border lc rgb '#6165' lw 0.200001
set object 216 polygon from \
  3.62992, 5.05022 to \
  3.62992, 5.04986 to \
  -3.48254, -0 to \
  -3.48306, -0 to \
  3.62992, 5.05022 front fs empty border lc rgb '#6165' lw 0.200001
set object 217 polygon from \
  3.53182, 5.08603 to \
  3.53182, 5.08566 to \
  -3.53159, -0 to \
  -3.53211, -0 to \
  3.53182, 5.08603 front fs empty border lc rgb '#6165' lw 0.200001
set object 218 polygon from \
  3.43372, 5.12086 to \
  3.43372, 5.12049 to \
  -3.58064, -0 to \
  -3.58115, -0 to \
  3.43372, 5.12086 front fs empty border lc rgb '#6165' lw 0.200001
set object 219 polygon from \
  3.33562, 5.15471 to \
  3.33562, 5.15434 to \
  -3.62969, -0 to \
  -3.63019, -0 to \
  3.33562, 5.15471 front fs empty border lc rgb '#6165' lw 0.200001
set object 220 polygon from \
  3.23752, 5.18757 to \
  3.23752, 5.1872 to \
  -3.67874, -0 to \
  -3.67924, -0 to \
  3.23752, 5.18757 front fs empty border lc rgb '#6165' lw 0.200001
set object 221 polygon from \
  3.13942, 5.21946 to \
  3.13942, 5.21909 to \
  -3.72779, -0 to \
  -3.72828, -0 to \
  3.13942, 5.21946 front fs empty border lc rgb '#6165' lw 0.200001
set object 222 polygon from \
  3.04132, 5.25036 to \
  3.04132, 5.24999 to \
  -3.77684, -0 to \
  -3.77732, -0 to \
  3.04132, 5.25036 front fs empty border lc rgb '#6165' lw 0.200001
set object 223 polygon from \
  2.94322, 5.28028 to \
  2.94322, 5.27991 to \
  -3.82589, -0 to \
  -3.82637, -0 to \
  2.94322, 5.28028 front fs empty border lc rgb '#6165' lw 0.200001
set object 224 polygon from \
  2.84512, 5.30922 to \
  2.84512, 5.30886 to \
  -3.87494, -0 to \
  -3.87541, -0 to \
  2.84512, 5.30922 front fs empty border lc rgb '#6165' lw 0.200001
set object 225 polygon from \
  2.74702, 5.33719 to \
  2.74702, 5.33682 to \
  -3.92399, -0 to \
  -3.92446, -0 to \
  2.74702, 5.33719 front fs empty border lc rgb '#6165' lw 0.200001
set object 226 polygon from \
  2.64892, 5.36417 to \
  2.64892, 5.3638 to \
  -3.97304, -0 to \
  -3.9735, -0 to \
  2.64892, 5.36417 front fs empty border lc rgb '#6165' lw 0.200001
set object 227 polygon from \
  2.55082, 5.39016 to \
  2.55082, 5.3898 to \
  -4.02209, -0 to \
  -4.02254, -0 to \
  2.55082, 5.39016 front fs empty border lc rgb '#6165' lw 0.200001
set object 228 polygon from \
  2.45272, 5.41518 to \
  2.45272, 5.41481 to \
  -4.07114, -0 to \
  -4.07159, -0 to \
  2.45272, 5.41518 front fs empty border lc rgb '#6165' lw 0.200001
set object 229 polygon from \
  2.35462, 5.43922 to \
  2.35462, 5.43885 to \
  -4.12019, -0 to \
  -4.12063, -0 to \
  2.35462, 5.43922 front fs empty border lc rgb '#6165' lw 0.200001
set object 230 polygon from \
  2.25652, 5.46227 to \
  2.25652, 5.46191 to \
  -4.16924, -0 to \
  -4.16968, -0 to \
  2.25652, 5.46227 front fs empty border lc rgb '#6165' lw 0.200001
set object 231 polygon from \
  2.15842, 5.48435 to \
  2.15842, 5.48398 to \
  -4.21829, -0 to \
  -4.21872, -0 to \
  2.15842, 5.48435 front fs empty border lc rgb '#6165' lw 0.200001
set object 232 polygon from \
  2.06032, 5.50544 to \
  2.06032, 5.50507 to \
  -4.26734, -0 to \
  -4.26777, -0 to \
  2.06032, 5.50544 front fs empty border lc rgb '#6165' lw 0.200001
set object 233 polygon from \
  1.96222, 5.52555 to \
  1.96222, 5.52519 to \
  -4.31639, -0 to \
  -4.31681, -0 to \
  1.96222, 5.52555 front fs empty border lc rgb '#6165' lw 0.200001
set object 234 polygon from \
  1.86412, 5.54469 to \
  1.86412, 5.54432 to \
  -4.36544, -0 to \
  -4.36586, -0 to \
  1.86412, 5.54469 front fs empty border lc rgb '#6165' lw 0.200001
set object 235 polygon from \
  1.76602, 5.56284 to \
  1.76602, 5.56247 to \
  -4.41449, -0 to \
  -4.4149, -0 to \
  1.76602, 5.56284 front fs empty border lc rgb '#6165' lw 0.200001
set object 236 polygon from \
  1.66792, 5.58001 to \
  1.66792, 5.57964 to \
  -4.46354, -0 to \
  -4.46395, -0 to \
  1.66792, 5.58001 front fs empty border lc rgb '#6165' lw 0.200001
set object 237 polygon from \
  1.56982, 5.5962 to \
  1.56982, 5.59583 to \
  -4.51259, -0 to \
  -4.513, -0 to \
  1.56982, 5.5962 front fs empty border lc rgb '#6165' lw 0.200001
set object 238 polygon from \
  1.47172, 5.6114 to \
  1.47172, 5.61103 to \
  -4.56164, -0 to \
  -4.56204, -0 to \
  1.47172, 5.6114 front fs empty border lc rgb '#6165' lw 0.200001
set object 239 polygon from \
  1.37362, 5.62563 to \
  1.37362, 5.62526 to \
  -4.61069, -0 to \
  -4.61109, -0 to \
  1.37362, 5.62563 front fs empty border lc rgb '#6165' lw 0.200001
set object 240 polygon from \
  1.27552, 5.63888 to \
  1.27552, 5.63851 to \
  -4.65974, -0 to \
  -4.66013, -0 to \
  1.27552, 5.63888 front fs empty border lc rgb '#6165' lw 0.200001
set object 241 polygon from \
  1.17742, 5.65114 to \
  1.17742, 5.65077 to \
  -4.70879, -0 to \
  -4.70918, -0 to \
  1.17742, 5.65114 front fs empty border lc rgb '#6165' lw 0.200001
set object 242 polygon from \
  1.07932, 5.66242 to \
  1.07932, 5.66206 to \
  -4.75784, -0 to \
  -4.75822, -0 to \
  1.07932, 5.66242 front fs empty border lc rgb '#6165' lw 0.200001
set object 243 polygon from \
  0.981216, 5.67273 to \
  0.981216, 5.67236 to \
  -4.80689, -0 to \
  -4.80727, -0 to \
  0.981216, 5.67273 front fs empty border lc rgb '#6165' lw 0.200001
set object 244 polygon from \
  0.883116, 5.68205 to \
  0.883116, 5.68168 to \
  -4.85594, -0 to \
  -4.85632, -0 to \
  0.883116, 5.68205 front fs empty border lc rgb '#6165' lw 0.200001
set object 245 polygon from \
  0.785016, 5.69039 to \
  0.785016, 5.69002 to \
  -4.90499, -0 to \
  -4.90536, -0 to \
  0.785016, 5.69039 front fs empty border lc rgb '#6165' lw 0.200001
set object 246 polygon from \
  0.686916, 5.69775 to \
  0.686916, 5.69738 to \
  -4.95404, -0 to \
  -4.95441, -0 to \
  0.686916, 5.69775 front fs empty border lc rgb '#6165' lw 0.200001
set object 247 polygon from \
  0.588816, 5.70413 to \
  0.588816, 5.70376 to \
  -5.00309, -0 to \
  -5.00346, -0 to \
  0.588816, 5.70413 front fs empty border lc rgb '#6165' lw 0.200001
set object 248 polygon from \
  0.490716, 5.70952 to \
  0.490716, 5.70916 to \
  -5.05214, -0 to \
  -5.0525, -0 to \
  0.490716, 5.70952 front fs empty border lc rgb '#6165' lw 0.200001
set object 249 polygon from \
  0.392616, 5.71394 to \
  0.392616, 5.71357 to \
  -5.10119, -0 to \
  -5.10155, -0 to \
  0.392616, 5.71394 front fs empty border lc rgb '#6165' lw 0.200001
set object 250 polygon from \
  0.294516, 5.71738 to \
  0.294516, 5.71701 to \
  -5.15024, -0 to \
  -5.1506, -0 to \
  0.294516, 5.71738 front fs empty border lc rgb '#6165' lw 0.200001
set object 251 polygon from \
  0.196416, 5.71983 to \
  0.196416, 5.71946 to \
  -5.19929, -0 to \
  -5.19964, -0 to \
  0.196416, 5.71983 front fs empty border lc rgb '#6165' lw 0.200001
set object 252 polygon from \
  0.0983154, 5.72131 to \
  0.0983154, 5.72094 to \
  -5.24834, -0 to \
  -5.24869, -0 to \
  0.0983154, 5.72131 front fs empty border lc rgb '#6165' lw 0.200001
set object 253 polygon from \
  0.00021531, 5.7218 to \
  0.00021531, 5.72143 to \
  -5.29739, -0 to \
  -5.29774, -0 to \
  0.00021531, 5.7218 front fs empty border lc rgb '#6165' lw 0.200001
set object 254 polygon from \
  -0.0978846, 5.72131 to \
  -0.0978846, 5.72094 to \
  -5.34644, -0 to \
  -5.34678, -0 to \
  -0.0978846, 5.72131 front fs empty border lc rgb '#6165' lw 0.200001
set object 255 polygon from \
  -0.195984, 5.71984 to \
  -0.195984, 5.71947 to \
  -5.39549, -0 to \
  -5.39583, -0 to \
  -0.195984, 5.71984 front fs empty border lc rgb '#6165' lw 0.200001
set object 256 polygon from \
  -0.294084, 5.71739 to \
  -0.294084, 5.71702 to \
  -5.44454, -0 to \
  -5.44488, -0 to \
  -0.294084, 5.71739 front fs empty border lc rgb '#6165' lw 0.200001
set object 257 polygon from \
  -0.392184, 5.71396 to \
  -0.392184, 5.71359 to \
  -5.49359, -0 to \
  -5.49392, -0 to \
  -0.392184, 5.71396 front fs empty border lc rgb '#6165' lw 0.200001
set object 258 polygon from \
  -0.490284, 5.70955 to \
  -0.490284, 5.70918 to \
  -5.54264, -0 to \
  -5.54297, -0 to \
  -0.490284, 5.70955 front fs empty border lc rgb '#6165' lw 0.200001
set object 259 polygon from \
  -0.588384, 5.70415 to \
  -0.588384, 5.70378 to \
  -5.59169, -0 to \
  -5.59202, -0 to \
  -0.588384, 5.70415 front fs empty border lc rgb '#6165' lw 0.200001
set object 260 polygon from \
  -0.686484, 5.69778 to \
  -0.686484, 5.69741 to \
  -5.64074, -0 to \
  -5.64107, -0 to \
  -0.686484, 5.69778 front fs empty border lc rgb '#6165' lw 0.200001
set object 261 polygon from \
  -0.784584, 5.69042 to \
  -0.784584, 5.69005 to \
  -5.68979, -0 to \
  -5.69011, -0 to \
  -0.784584, 5.69042 front fs empty border lc rgb '#6165' lw 0.200001
set object 262 polygon from \
  -0.882684, 5.68209 to \
  -0.882684, 5.68172 to \
  -5.73884, -0 to \
  -5.73916, -0 to \
  -0.882684, 5.68209 front fs empty border lc rgb '#6165' lw 0.200001
set object 263 polygon from \
  -0.980784, 5.67277 to \
  -0.980784, 5.6724 to \
  -5.78789, -0 to \
  -5.78821, -0 to \
  -0.980784, 5.67277 front fs empty border lc rgb '#6165' lw 0.200001
set object 264 polygon from \
  -1.07888, 5.66247 to \
  -1.07888, 5.6621 to \
  -5.83694, -0 to \
  -5.83725, -0 to \
  -1.07888, 5.66247 front fs empty border lc rgb '#6165' lw 0.200001
set object 265 polygon from \
  -1.17698, 5.65119 to \
  -1.17698, 5.65082 to \
  -5.88599, -0 to \
  -5.8863, -0 to \
  -1.17698, 5.65119 front fs empty border lc rgb '#6165' lw 0.200001
set object 266 polygon from \
  -1.27508, 5.63893 to \
  -1.27508, 5.63856 to \
  -5.93504, -0 to \
  -5.93535, -0 to \
  -1.27508, 5.63893 front fs empty border lc rgb '#6165' lw 0.200001
set object 267 polygon from \
  -1.37318, 5.62569 to \
  -1.37318, 5.62532 to \
  -5.98409, -0 to \
  -5.9844, -0 to \
  -1.37318, 5.62569 front fs empty border lc rgb '#6165' lw 0.200001
set object 268 polygon from \
  -1.47128, 5.61147 to \
  -1.47128, 5.6111 to \
  -6.03314, -0 to \
  -6.03344, -0 to \
  -1.47128, 5.61147 front fs empty border lc rgb '#6165' lw 0.200001
set object 269 polygon from \
  -1.56938, 5.59626 to \
  -1.56938, 5.5959 to \
  -6.08219, -0 to \
  -6.08249, -0 to \
  -1.56938, 5.59626 front fs empty border lc rgb '#6165' lw 0.200001
set object 270 polygon from \
  -1.66748, 5.58008 to \
  -1.66748, 5.57971 to \
  -6.13124, -0 to \
  -6.13154, -0 to \
  -1.66748, 5.58008 front fs empty border lc rgb '#6165' lw 0.200001
set object 271 polygon from \
  -1.76558, 5.56291 to \
  -1.76558, 5.56255 to \
  -6.18029, -0 to \
  -6.18059, -0 to \
  -1.76558, 5.56291 front fs empty border lc rgb '#6165' lw 0.200001
set object 272 polygon from \
  -1.86368, 5.54477 to \
  -1.86368, 5.5444 to \
  -6.22934, -0 to \
  -6.22963, -0 to \
  -1.86368, 5.54477 front fs empty border lc rgb '#6165' lw 0.200001
set object 273 polygon from \
  -1.96178, 5.52564 to \
  -1.96178, 5.52527 to \
  -6.27839, -0 to \
  -6.27868, -0 to \
  -1.96178, 5.52564 front fs empty border lc rgb '#6165' lw 0.200001
set object 274 polygon from \
  -2.05988, 5.50553 to \
  -2.05988, 5.50516 to \
  -6.32744, -0 to \
  -6.32773, -0 to \
  -2.05988, 5.50553 front fs empty border lc rgb '#6165' lw 0.200001
set object 275 polygon from \
  -2.15798, 5.48444 to \
  -2.15798, 5.48407 to \
  -6.37649, -0 to \
  -6.37678, -0 to \
  -2.15798, 5.48444 front fs empty border lc rgb '#6165' lw 0.200001
set object 276 polygon from \
  -2.25608, 5.46237 to \
  -2.25608, 5.462 to \
  -6.42554, -0 to \
  -6.42583, -0 to \
  -2.25608, 5.46237 front fs empty border lc rgb '#6165' lw 0.200001
set object 277 polygon from \
  -2.35418, 5.43932 to \
  -2.35418, 5.43895 to \
  -6.47459, -0 to \
  -6.47487, -0 to \
  -2.35418, 5.43932 front fs empty border lc rgb '#6165' lw 0.200001
set object 278 polygon from \
  -2.45228, 5.41529 to \
  -2.45228, 5.41492 to \
  -6.52364, -0 to \
  -6.52392, -0 to \
  -2.45228, 5.41529 front fs empty border lc rgb '#6165' lw 0.200001
set object 279 polygon from \
  -2.55038, 5.39028 to \
  -2.55038, 5.38991 to \
  -6.57269, -0 to \
  -6.57297, -0 to \
  -2.55038, 5.39028 front fs empty border lc rgb '#6165' lw 0.200001
set object 280 polygon from \
  -2.64848, 5.36428 to \
  -2.64848, 5.36391 to \
  -6.62174, -0 to \
  -6.62202, -0 to \
  -2.64848, 5.36428 front fs empty border lc rgb '#6165' lw 0.200001
set object 281 polygon from \
  -2.74658, 5.33731 to \
  -2.74658, 5.33694 to \
  -6.67079, -0 to \
  -6.67107, -0 to \
  -2.74658, 5.33731 front fs empty border lc rgb '#6165' lw 0.200001
set object 282 polygon from \
  -2.84468, 5.30935 to \
  -2.84468, 5.30898 to \
  -6.71984, -0 to \
  -6.72011, -0 to \
  -2.84468, 5.30935 front fs empty border lc rgb '#6165' lw 0.200001
set object 283 polygon from \
  -2.94278, 5.28041 to \
  -2.94278, 5.28004 to \
  -6.76889, -0 to \
  -6.76916, -0 to \
  -2.94278, 5.28041 front fs empty border lc rgb '#6165' lw 0.200001
set object 284 polygon from \
  -3.04088, 5.25049 to \
  -3.04088, 5.25013 to \
  -6.81794, -0 to \
  -6.81821, -0 to \
  -3.04088, 5.25049 front fs empty border lc rgb '#6165' lw 0.200001
set object 285 polygon from \
  -3.13898, 5.21959 to \
  -3.13898, 5.21923 to \
  -6.86699, -0 to \
  -6.86726, -0 to \
  -3.13898, 5.21959 front fs empty border lc rgb '#6165' lw 0.200001
set object 286 polygon from \
  -3.23708, 5.18771 to \
  -3.23708, 5.18735 to \
  -6.91604, -0 to \
  -6.91631, -0 to \
  -3.23708, 5.18771 front fs empty border lc rgb '#6165' lw 0.200001
set object 287 polygon from \
  -3.33518, 5.15485 to \
  -3.33518, 5.15448 to \
  -6.96509, -0 to \
  -6.96535, -0 to \
  -3.33518, 5.15485 front fs empty border lc rgb '#6165' lw 0.200001
set object 288 polygon from \
  -3.43328, 5.12101 to \
  -3.43328, 5.12064 to \
  -7.01414, -0 to \
  -7.0144, -0 to \
  -3.43328, 5.12101 front fs empty border lc rgb '#6165' lw 0.200001
set object 289 polygon from \
  -3.53138, 5.08619 to \
  -3.53138, 5.08582 to \
  -7.06319, -0 to \
  -7.06345, -0 to \
  -3.53138, 5.08619 front fs empty border lc rgb '#6165' lw 0.200001
set object 290 polygon from \
  -3.62948, 5.05038 to \
  -3.62948, 5.05001 to \
  -7.11224, -0 to \
  -7.1125, -0 to \
  -3.62948, 5.05038 front fs empty border lc rgb '#6165' lw 0.200001
set object 291 polygon from \
  -3.72758, 5.0136 to \
  -3.72758, 5.01323 to \
  -7.16129, -0 to \
  -7.16155, -0 to \
  -3.72758, 5.0136 front fs empty border lc rgb '#6165' lw 0.200001
set object 292 polygon from \
  -3.82568, 4.97583 to \
  -3.82568, 4.97546 to \
  -7.21034, -0 to \
  -7.2106, -0 to \
  -3.82568, 4.97583 front fs empty border lc rgb '#6165' lw 0.200001
set object 293 polygon from \
  -3.92378, 4.93708 to \
  -3.92378, 4.93672 to \
  -7.25939, -0 to \
  -7.25964, -0 to \
  -3.92378, 4.93708 front fs empty border lc rgb '#6165' lw 0.200001
set object 294 polygon from \
  -4.02188, 4.89736 to \
  -4.02188, 4.89699 to \
  -7.30844, -0 to \
  -7.30869, -0 to \
  -4.02188, 4.89736 front fs empty border lc rgb '#6165' lw 0.200001
set object 295 polygon from \
  -4.11998, 4.85665 to \
  -4.11998, 4.85628 to \
  -7.35749, -0 to \
  -7.35774, -0 to \
  -4.11998, 4.85665 front fs empty border lc rgb '#6165' lw 0.200001
set object 296 polygon from \
  -4.21808, 4.81496 to \
  -4.21808, 4.81459 to \
  -7.40654, -0 to \
  -7.40679, -0 to \
  -4.21808, 4.81496 front fs empty border lc rgb '#6165' lw 0.200001
set object 297 polygon from \
  -4.31618, 4.77228 to \
  -4.31618, 4.77192 to \
  -7.45559, -0 to \
  -7.45584, -0 to \
  -4.31618, 4.77228 front fs empty border lc rgb '#6165' lw 0.200001
set object 298 polygon from \
  -4.41428, 4.72863 to \
  -4.41428, 4.72826 to \
  -7.50464, -0 to \
  -7.50489, -0 to \
  -4.41428, 4.72863 front fs empty border lc rgb '#6165' lw 0.200001
set object 299 polygon from \
  -4.51238, 4.684 to \
  -4.51238, 4.68363 to \
  -7.55369, -0 to \
  -7.55393, -0 to \
  -4.51238, 4.684 front fs empty border lc rgb '#6165' lw 0.200001
set object 300 polygon from \
  -4.61048, 4.63838 to \
  -4.61048, 4.63802 to \
  -7.60274, -0 to \
  -7.60298, -0 to \
  -4.61048, 4.63838 front fs empty border lc rgb '#6165' lw 0.200001
set object 301 polygon from \
  -4.70858, 4.59179 to \
  -4.70858, 4.59142 to \
  -7.65179, -0 to \
  -7.65203, -0 to \
  -4.70858, 4.59179 front fs empty border lc rgb '#6165' lw 0.200001
set object 302 polygon from \
  -4.80668, 4.54421 to \
  -4.80668, 4.54384 to \
  -7.70084, -0 to \
  -7.70108, -0 to \
  -4.80668, 4.54421 front fs empty border lc rgb '#6165' lw 0.200001
set object 303 polygon from \
  -4.90478, 4.49566 to \
  -4.90478, 4.49529 to \
  -7.74989, -0 to \
  -7.75013, -0 to \
  -4.90478, 4.49566 front fs empty border lc rgb '#6165' lw 0.200001
set object 304 polygon from \
  -5.00288, 4.44612 to \
  -5.00288, 4.44575 to \
  -7.79894, -0 to \
  -7.79918, -0 to \
  -5.00288, 4.44612 front fs empty border lc rgb '#6165' lw 0.200001
set object 305 polygon from \
  -5.10098, 4.3956 to \
  -5.10098, 4.39523 to \
  -7.84799, -0 to \
  -7.84823, -0 to \
  -5.10098, 4.3956 front fs empty border lc rgb '#6165' lw 0.200001
set object 306 polygon from \
  -5.19908, 4.3441 to \
  -5.19908, 4.34373 to \
  -7.89704, -0 to \
  -7.89727, -0 to \
  -5.19908, 4.3441 front fs empty border lc rgb '#6165' lw 0.200001
set object 307 polygon from \
  -5.29718, 4.29162 to \
  -5.29718, 4.29125 to \
  -7.94609, -0 to \
  -7.94632, -0 to \
  -5.29718, 4.29162 front fs empty border lc rgb '#6165' lw 0.200001
set object 308 polygon from \
  -5.39528, 4.23815 to \
  -5.39528, 4.23779 to \
  -7.99514, -0 to \
  -7.99537, -0 to \
  -5.39528, 4.23815 front fs empty border lc rgb '#6165' lw 0.200001
set object 309 polygon from \
  -5.49338, 4.18371 to \
  -5.49338, 4.18334 to \
  -8.04419, -0 to \
  -8.04442, -0 to \
  -5.49338, 4.18371 front fs empty border lc rgb '#6165' lw 0.200001
set object 310 polygon from \
  -5.59148, 4.12829 to \
  -5.59148, 4.12792 to \
  -8.09324, -0 to \
  -8.09347, -0 to \
  -5.59148, 4.12829 front fs empty border lc rgb '#6165' lw 0.200001
set object 311 polygon from \
  -5.68958, 4.07188 to \
  -5.68958, 4.07151 to \
  -8.14229, -0 to \
  -8.14252, -0 to \
  -5.68958, 4.07188 front fs empty border lc rgb '#6165' lw 0.200001
set object 312 polygon from \
  -5.78768, 4.01449 to \
  -5.78768, 4.01413 to \
  -8.19134, -0 to \
  -8.19157, -0 to \
  -5.78768, 4.01449 front fs empty border lc rgb '#6165' lw 0.200001
set object 313 polygon from \
  -5.88578, 3.95613 to \
  -5.88578, 3.95576 to \
  -8.24039, -0 to \
  -8.24061, -0 to \
  -5.88578, 3.95613 front fs empty border lc rgb '#6165' lw 0.200001
set object 314 polygon from \
  -5.98388, 3.89678 to \
  -5.98388, 3.89641 to \
  -8.28944, -0 to \
  -8.28966, -0 to \
  -5.98388, 3.89678 front fs empty border lc rgb '#6165' lw 0.200001
set object 315 polygon from \
  -6.08198, 3.83645 to \
  -6.08198, 3.83608 to \
  -8.33849, -0 to \
  -8.33871, -0 to \
  -6.08198, 3.83645 front fs empty border lc rgb '#6165' lw 0.200001
set object 316 polygon from \
  -6.18008, 3.77514 to \
  -6.18008, 3.77477 to \
  -8.38754, -0 to \
  -8.38776, -0 to \
  -6.18008, 3.77514 front fs empty border lc rgb '#6165' lw 0.200001
set object 317 polygon from \
  -6.27818, 3.71285 to \
  -6.27818, 3.71248 to \
  -8.43659, -0 to \
  -8.43681, -0 to \
  -6.27818, 3.71285 front fs empty border lc rgb '#6165' lw 0.200001
set object 318 polygon from \
  -6.37628, 3.64958 to \
  -6.37628, 3.64921 to \
  -8.48564, -0 to \
  -8.48586, -0 to \
  -6.37628, 3.64958 front fs empty border lc rgb '#6165' lw 0.200001
set object 319 polygon from \
  -6.47438, 3.58532 to \
  -6.47438, 3.58495 to \
  -8.53469, -0 to \
  -8.53491, -0 to \
  -6.47438, 3.58532 front fs empty border lc rgb '#6165' lw 0.200001
set object 320 polygon from \
  -6.57248, 3.52009 to \
  -6.57248, 3.51972 to \
  -8.58374, -0 to \
  -8.58396, -0 to \
  -6.57248, 3.52009 front fs empty border lc rgb '#6165' lw 0.200001
set object 321 polygon from \
  -6.67058, 3.45387 to \
  -6.67058, 3.4535 to \
  -8.63279, -0 to \
  -8.633, -0 to \
  -6.67058, 3.45387 front fs empty border lc rgb '#6165' lw 0.200001
set object 322 polygon from \
  -6.76868, 3.38668 to \
  -6.76868, 3.38631 to \
  -8.68184, -0 to \
  -8.68205, -0 to \
  -6.76868, 3.38668 front fs empty border lc rgb '#6165' lw 0.200001
set object 323 polygon from \
  -6.86678, 3.3185 to \
  -6.86678, 3.31813 to \
  -8.73089, -0 to \
  -8.7311, -0 to \
  -6.86678, 3.3185 front fs empty border lc rgb '#6165' lw 0.200001
set object 324 polygon from \
  -6.96488, 3.24934 to \
  -6.96488, 3.24897 to \
  -8.77994, -0 to \
  -8.78015, -0 to \
  -6.96488, 3.24934 front fs empty border lc rgb '#6165' lw 0.200001
set object 325 polygon from \
  -7.06298, 3.1792 to \
  -7.06298, 3.17883 to \
  -8.82899, -0 to \
  -8.8292, -0 to \
  -7.06298, 3.1792 front fs empty border lc rgb '#6165' lw 0.200001
set object 326 polygon from \
  -7.16108, 3.10808 to \
  -7.16108, 3.10771 to \
  -8.87804, -0 to \
  -8.87825, -0 to \
  -7.16108, 3.10808 front fs empty border lc rgb '#6165' lw 0.200001
set object 327 polygon from \
  -7.25918, 3.03598 to \
  -7.25918, 3.03561 to \
  -8.92709, -0 to \
  -8.9273, -0 to \
  -7.25918, 3.03598 front fs empty border lc rgb '#6165' lw 0.200001
set object 328 polygon from \
  -7.35728, 2.9629 to \
  -7.35728, 2.96253 to \
  -8.97614, -0 to \
  -8.97635, -0 to \
  -7.35728, 2.9629 front fs empty border lc rgb '#6165' lw 0.200001
set object 329 polygon from \
  -7.45538, 2.88883 to \
  -7.45538, 2.88847 to \
  -9.02519, -0 to \
  -9.0254, -0 to \
  -7.45538, 2.88883 front fs empty border lc rgb '#6165' lw 0.200001
set object 330 polygon from \
  -7.55348, 2.81379 to \
  -7.55348, 2.81342 to \
  -9.07424, -0 to \
  -9.07444, -0 to \
  -7.55348, 2.81379 front fs empty border lc rgb '#6165' lw 0.200001
set object 331 polygon from \
  -7.65158, 2.73776 to \
  -7.65158, 2.7374 to \
  -9.12329, -0 to \
  -9.12349, -0 to \
  -7.65158, 2.73776 front fs empty border lc rgb '#6165' lw 0.200001
set object 332 polygon from \
  -7.74968, 2.66076 to \
  -7.74968, 2.66039 to \
  -9.17234, -0 to \
  -9.17254, -0 to \
  -7.74968, 2.66076 front fs empty border lc rgb '#6165' lw 0.200001
set object 333 polygon from \
  -7.84778, 2.58277 to \
  -7.84778, 2.5824 to \
  -9.22139, -0 to \
  -9.22159, -0 to \
  -7.84778, 2.58277 front fs empty border lc rgb '#6165' lw 0.200001
set object 334 polygon from \
  -7.94588, 2.5038 to \
  -7.94588, 2.50343 to \
  -9.27044, -0 to \
  -9.27064, -0 to \
  -7.94588, 2.5038 front fs empty border lc rgb '#6165' lw 0.200001
set object 335 polygon from \
  -8.04398, 2.42385 to \
  -8.04398, 2.42348 to \
  -9.31949, -0 to \
  -9.31969, -0 to \
  -8.04398, 2.42385 front fs empty border lc rgb '#6165' lw 0.200001
set object 336 polygon from \
  -8.14208, 2.34292 to \
  -8.14208, 2.34255 to \
  -9.36854, -0 to \
  -9.36874, -0 to \
  -8.14208, 2.34292 front fs empty border lc rgb '#6165' lw 0.200001
set object 337 polygon from \
  -8.24018, 2.26101 to \
  -8.24018, 2.26064 to \
  -9.41759, -0 to \
  -9.41779, -0 to \
  -8.24018, 2.26101 front fs empty border lc rgb '#6165' lw 0.200001
set object 338 polygon from \
  -8.33828, 2.17812 to \
  -8.33828, 2.17775 to \
  -9.46664, -0 to \
  -9.46684, -0 to \
  -8.33828, 2.17812 front fs empty border lc rgb '#6165' lw 0.200001
set object 339 polygon from \
  -8.43638, 2.09424 to \
  -8.43638, 2.09388 to \
  -9.51569, -0 to \
  -9.51588, -0 to \
  -8.43638, 2.09424 front fs empty border lc rgb '#6165' lw 0.200001
set object 340 polygon from \
  -8.53448, 2.00939 to \
  -8.53448, 2.00902 to \
  -9.56474, -0 to \
  -9.56493, -0 to \
  -8.53448, 2.00939 front fs empty border lc rgb '#6165' lw 0.200001
set object 341 polygon from \
  -8.63258, 1.92356 to \
  -8.63258, 1.92319 to \
  -9.61379, -0 to \
  -9.61398, -0 to \
  -8.63258, 1.92356 front fs empty border lc rgb '#6165' lw 0.200001
set object 342 polygon from \
  -8.73068, 1.83674 to \
  -8.73068, 1.83637 to \
  -9.66284, -0 to \
  -9.66303, -0 to \
  -8.73068, 1.83674 front fs empty border lc rgb '#6165' lw 0.200001
set object 343 polygon from \
  -8.82878, 1.74894 to \
  -8.82878, 1.74857 to \
  -9.71189, -0 to \
  -9.71208, -0 to \
  -8.82878, 1.74894 front fs empty border lc rgb '#6165' lw 0.200001
set object 344 polygon from \
  -8.92688, 1.66016 to \
  -8.92688, 1.65979 to \
  -9.76094, -0 to \
  -9.76113, -0 to \
  -8.92688, 1.66016 front fs empty border lc rgb '#6165' lw 0.200001
set object 345 polygon from \
  -9.02498, 1.5704 to \
  -9.02498, 1.57004 to \
  -9.80999, -0 to \
  -9.81018, -0 to \
  -9.02498, 1.5704 front fs empty border lc rgb '#6165' lw 0.200001
set object 346 polygon from \
  -9.12308, 1.47966 to \
  -9.12308, 1.4793 to \
  -9.85904, -0 to \
  -9.85923, -0 to \
  -9.12308, 1.47966 front fs empty border lc rgb '#6165' lw 0.200001
set object 347 polygon from \
  -9.22118, 1.38794 to \
  -9.22118, 1.38757 to \
  -9.90809, -0 to \
  -9.90828, -0 to \
  -9.22118, 1.38794 front fs empty border lc rgb '#6165' lw 0.200001
set object 348 polygon from \
  -9.31928, 1.29524 to \
  -9.31928, 1.29487 to \
  -9.95714, -0 to \
  -9.95733, -0 to \
  -9.31928, 1.29524 front fs empty border lc rgb '#6165' lw 0.200001
set object 349 polygon from \
  -9.41738, 1.20156 to \
  -9.41738, 1.20119 to \
  -10.0061, -0 to \
  -10.0063, -0 to \
  -9.41738, 1.20156 front fs empty border lc rgb '#6165' lw 0.200001
set object 350 polygon from \
  -9.51548, 1.10689 to \
  -9.51548, 1.10652 to \
  -10.0552, -0 to \
  -10.0554, -0 to \
  -9.51548, 1.10689 front fs empty border lc rgb '#6165' lw 0.200001
set object 351 polygon from \
  -9.61358, 1.01125 to \
  -9.61358, 1.01088 to \
  -10.1042, -0 to \
  -10.1044, -0 to \
  -9.61358, 1.01125 front fs empty border lc rgb '#6165' lw 0.200001
set object 352 polygon from \
  -9.71168, 0.914616 to \
  -9.71168, 0.914248 to \
  -10.1533, -0 to \
  -10.1535, -0 to \
  -9.71168, 0.914616 front fs empty border lc rgb '#6165' lw 0.200001
set object 353 polygon from \
  -9.80978, 0.817009 to \
  -9.80978, 0.81664 to \
  -10.2023, -0 to \
  -10.2025, -0 to \
  -9.80978, 0.817009 front fs empty border lc rgb '#6165' lw 0.200001
set object 354 polygon from \
  -9.90788, 0.71842 to \
  -9.90788, 0.718052 to \
  -10.2514, -0 to \
  -10.2516, -0 to \
  -9.90788, 0.71842 front fs empty border lc rgb '#6165' lw 0.200001
set object 355 polygon from \
  -10.0059, 0.618851 to \
  -10.0059, 0.618483 to \
  -10.3004, -0 to \
  -10.3006, -0 to \
  -10.0059, 0.618851 front fs empty border lc rgb '#6165' lw 0.200001
set object 356 polygon from \
  -10.104, 0.518301 to \
  -10.104, 0.517932 to \
  -10.3495, -0 to \
  -10.3497, -0 to \
  -10.104, 0.518301 front fs empty border lc rgb '#6165' lw 0.200001
set object 357 polygon from \
  -10.2021, 0.416769 to \
  -10.2021, 0.416401 to \
  -10.3985, -0 to \
  -10.3987, -0 to \
  -10.2021, 0.416769 front fs empty border lc rgb '#6165' lw 0.200001
set object 358 polygon from \
  -10.3002, 0.314257 to \
  -10.3002, 0.313889 to \
  -10.4476, -0 to \
  -10.4478, -0 to \
  -10.3002, 0.314257 front fs empty border lc rgb '#6165' lw 0.200001
set object 359 polygon from \
  -10.3983, 0.210764 to \
  -10.3983, 0.210395 to \
  -10.4966, -0 to \
  -10.4968, -0 to \
  -10.3983, 0.210764 front fs empty border lc rgb '#6165' lw 0.200001
set object 360 polygon from \
  -10.4964, 0.106289 to \
  -10.4964, 0.105921 to \
  -10.5457, -0 to \
  -10.5459, -0 to \
  -10.4964, 0.106289 front fs empty border lc rgb '#6165' lw 0.200001
set object 361 polygon from \
  -10.5945, 0.000833353 to \
  -10.5945, 0.000465068 to \
  -10.5947, -0 to \
  -10.5949, -0 to \
  -10.5945, 0.000833353 front fs empty border lc rgb '#6165' lw 0.200001
set object 362 polygon from \
  -0.000123033, 0.000368285 to \
  7.94636, 0.000368285 to \
  7.94636, 0 to \
  -0.0737799, -0 to \
  -0.000123033, 0.000368285 front fs empty border lc rgb '#6165' lw 0.200001
set object 363 polygon from \
  7.84826, 0.0793413 to \
  7.84826, 0.0789731 to \
  -0.04905, -0 to \
  -0.0858784, -0 to \
  7.84826, 0.0793413 front fs empty border lc rgb '#6165' lw 0.200001
set object 364 polygon from \
  7.75016, 0.157334 to \
  7.75016, 0.156966 to \
  -0.0980999, -0 to \
  -0.116514, -0 to \
  7.75016, 0.157334 front fs empty border lc rgb '#6165' lw 0.200001
set object 365 polygon from \
  7.65206, 0.234345 to \
  7.65206, 0.233977 to \
  -0.147149, -0 to \
  -0.159426, -0 to \
  7.65206, 0.234345 front fs empty border lc rgb '#6165' lw 0.200001
set object 366 polygon from \
  7.55396, 0.310375 to \
  7.55396, 0.310007 to \
  -0.196199, -0 to \
  -0.205407, -0 to \
  7.55396, 0.310375 front fs empty border lc rgb '#6165' lw 0.200001
set object 367 polygon from \
  7.45586, 0.385424 to \
  7.45586, 0.385056 to \
  -0.245249, -0 to \
  -0.252615, -0 to \
  7.45586, 0.385424 front fs empty border lc rgb '#6165' lw 0.200001
set object 368 polygon from \
  7.35776, 0.459492 to \
  7.35776, 0.459124 to \
  -0.294299, -0 to \
  -0.300438, -0 to \
  7.35776, 0.459492 front fs empty border lc rgb '#6165' lw 0.200001
set object 369 polygon from \
  7.25966, 0.532579 to \
  7.25966, 0.532211 to \
  -0.343349, -0 to \
  -0.348611, -0 to \
  7.25966, 0.532579 front fs empty border lc rgb '#6165' lw 0.200001
set object 370 polygon from \
  7.16156, 0.604685 to \
  7.16156, 0.604317 to \
  -0.392399, -0 to \
  -0.397003, -0 to \
  7.16156, 0.604685 front fs empty border lc rgb '#6165' lw 0.200001
set object 371 polygon from \
  7.06346, 0.67581 to \
  7.06346, 0.675442 to \
  -0.441449, -0 to \
  -0.445542, -0 to \
  7.06346, 0.67581 front fs empty border lc rgb '#6165' lw 0.200001
set object 372 polygon from \
  6.96536, 0.745954 to \
  6.96536, 0.745586 to \
  -0.490499, -0 to \
  -0.494182, -0 to \
  6.96536, 0.745954 front fs empty border lc rgb '#6165' lw 0.200001
set object 373 polygon from \
  6.86726, 0.815117 to \
  6.86726, 0.814749 to \
  -0.539549, -0 to \
  -0.542898, -0 to \
  6.86726, 0.815117 front fs empty border lc rgb '#6165' lw 0.200001
set object 374 polygon from \
  6.76916, 0.883299 to \
  6.76916, 0.882931 to \
  -0.588599, -0 to \
  -0.591669, -0 to \
  6.76916, 0.883299 front fs empty border lc rgb '#6165' lw 0.200001
set object 375 polygon from \
  6.67106, 0.9505 to \
  6.67106, 0.950132 to \
  -0.637649, -0 to \
  -0.640482, -0 to \
  6.67106, 0.9505 front fs empty border lc rgb '#6165' lw 0.200001
set object 376 polygon from \
  6.57296, 1.01672 to \
  6.57296, 1.01636 to \
  -0.686699, -0 to \
  -0.68933, -0 to \
  6.57296, 1.01672 front fs empty border lc rgb '#6165' lw 0.200001
set object 377 polygon from \
  6.47486, 1.08196 to \
  6.47486, 1.0816 to \
  -0.735749, -0 to \
  -0.738205, -0 to \
  6.47486, 1.08196 front fs empty border lc rgb '#6165' lw 0.200001
set object 378 polygon from \
  6.37676, 1.14622 to \
  6.37676, 1.14585 to \
  -0.784799, -0 to \
  -0.787101, -0 to \
  6.37676, 1.14622 front fs empty border lc rgb '#6165' lw 0.200001
set object 379 polygon from \
  6.27866, 1.2095 to \
  6.27866, 1.20913 to \
  -0.833849, -0 to \
  -0.836016, -0 to \
  6.27866, 1.2095 front fs empty border lc rgb '#6165' lw 0.200001
set object 380 polygon from \
  6.18056, 1.27179 to \
  6.18056, 1.27143 to \
  -0.882899, -0 to \
  -0.884946, -0 to \
  6.18056, 1.27179 front fs empty border lc rgb '#6165' lw 0.200001
set object 381 polygon from \
  6.08246, 1.33311 to \
  6.08246, 1.33274 to \
  -0.931949, -0 to \
  -0.933888, -0 to \
  6.08246, 1.33311 front fs empty border lc rgb '#6165' lw 0.200001
set object 382 polygon from \
  5.98436, 1.39344 to \
  5.98436, 1.39308 to \
  -0.980999, -0 to \
  -0.982841, -0 to \
  5.98436, 1.39344 front fs empty border lc rgb '#6165' lw 0.200001
set object 383 polygon from \
  5.88626, 1.4528 to \
  5.88626, 1.45243 to \
  -1.03004, -0 to \
  -1.0318, -0 to \
  5.88626, 1.4528 front fs empty border lc rgb '#6165' lw 0.200001
set object 384 polygon from \
  5.78816, 1.51117 to \
  5.78816, 1.5108 to \
  -1.07909, -0 to \
  -1.08077, -0 to \
  5.78816, 1.51117 front fs empty border lc rgb '#6165' lw 0.200001
set object 385 polygon from \
  5.69006, 1.56856 to \
  5.69006, 1.56819 to \
  -1.12814, -0 to \
  -1.12975, -0 to \
  5.69006, 1.56856 front fs empty border lc rgb '#6165' lw 0.200001
set object 386 polygon from \
  5.59196, 1.62497 to \
  5.59196, 1.6246 to \
  -1.17719, -0 to \
  -1.17873, -0 to \
  5.59196, 1.62497 front fs empty border lc rgb '#6165' lw 0.200001
set object 387 polygon from \
  5.49386, 1.6804 to \
  5.49386, 1.68003 to \
  -1.22624, -0 to \
  -1.22772, -0 to \
  5.49386, 1.6804 front fs empty border lc rgb '#6165' lw 0.200001
set object 388 polygon from \
  5.39576, 1.73485 to \
  5.39576, 1.73448 to \
  -1.27529, -0 to \
  -1.27671, -0 to \
  5.39576, 1.73485 front fs empty border lc rgb '#6165' lw 0.200001
set object 389 polygon from \
  5.29766, 1.78831 to \
  5.29766, 1.78795 to \
  -1.32434, -0 to \
  -1.32571, -0 to \
  5.29766, 1.78831 front fs empty border lc rgb '#6165' lw 0.200001
set object 390 polygon from \
  5.19956, 1.8408 to \
  5.19956, 1.84043 to \
  -1.37339, -0 to \
  -1.37471, -0 to \
  5.19956, 1.8408 front fs empty border lc rgb '#6165' lw 0.200001
set object 391 polygon from \
  5.10146, 1.8923 to \
  5.10146, 1.89194 to \
  -1.42244, -0 to \
  -1.42371, -0 to \
  5.10146, 1.8923 front fs empty border lc rgb '#6165' lw 0.200001
set object 392 polygon from \
  5.00336, 1.94283 to \
  5.00336, 1.94246 to \
  -1.47149, -0 to \
  -1.47272, -0 to \
  5.00336, 1.94283 front fs empty border lc rgb '#6165' lw 0.200001
set object 393 polygon from \
  4.90526, 1.99237 to \
  4.90526, 1.992 to \
  -1.52054, -0 to \
  -1.52173, -0 to \
  4.90526, 1.99237 front fs empty border lc rgb '#6165' lw 0.200001
set object 394 polygon from \
  4.80716, 2.04093 to \
  4.80716, 2.04057 to \
  -1.56959, -0 to \
  -1.57075, -0 to \
  4.80716, 2.04093 front fs empty border lc rgb '#6165' lw 0.200001
set object 395 polygon from \
  4.70906, 2.08851 to \
  4.70906, 2.08815 to \
  -1.61864, -0 to \
  -1.61976, -0 to \
  4.70906, 2.08851 front fs empty border lc rgb '#6165' lw 0.200001
set object 396 polygon from \
  4.61096, 2.13511 to \
  4.61096, 2.13475 to \
  -1.66769, -0 to \
  -1.66878, -0 to \
  4.61096, 2.13511 front fs empty border lc rgb '#6165' lw 0.200001
set object 397 polygon from \
  4.51286, 2.18073 to \
  4.51286, 2.18037 to \
  -1.71674, -0 to \
  -1.7178, -0 to \
  4.51286, 2.18073 front fs empty border lc rgb '#6165' lw 0.200001
set object 398 polygon from \
  4.41476, 2.22537 to \
  4.41476, 2.225 to \
  -1.76579, -0 to \
  -1.76682, -0 to \
  4.41476, 2.22537 front fs empty border lc rgb '#6165' lw 0.200001
set object 399 polygon from \
  4.31666, 2.26903 to \
  4.31666, 2.26866 to \
  -1.81484, -0 to \
  -1.81584, -0 to \
  4.31666, 2.26903 front fs empty border lc rgb '#6165' lw 0.200001
set object 400 polygon from \
  4.21856, 2.3117 to \
  4.21856, 2.31134 to \
  -1.86389, -0 to \
  -1.86486, -0 to \
  4.21856, 2.3117 front fs empty border lc rgb '#6165' lw 0.200001
set object 401 polygon from \
  4.12046, 2.3534 to \
  4.12046, 2.35303 to \
  -1.91294, -0 to \
  -1.91389, -0 to \
  4.12046, 2.3534 front fs empty border lc rgb '#6165' lw 0.200001
set object 402 polygon from \
  4.02236, 2.39411 to \
  4.02236, 2.39375 to \
  -1.96199, -0 to \
  -1.96292, -0 to \
  4.02236, 2.39411 front fs empty border lc rgb '#6165' lw 0.200001
set object 403 polygon from \
  3.92426, 2.43385 to \
  3.92426, 2.43348 to \
  -2.01104, -0 to \
  -2.01194, -0 to \
  3.92426, 2.43385 front fs empty border lc rgb '#6165' lw 0.200001
set object 404 polygon from \
  3.82616, 2.4726 to \
  3.82616, 2.47223 to \
  -2.06009, -0 to \
  -2.06097, -0 to \
  3.82616, 2.4726 front fs empty border lc rgb '#6165' lw 0.200001
set object 405 polygon from \
  3.72806, 2.51037 to \
  3.72806, 2.51 to \
  -2.10914, -0 to \
  -2.11, -0 to \
  3.72806, 2.51037 front fs empty border lc rgb '#6165' lw 0.200001
set object 406 polygon from \
  3.62996, 2.54716 to \
  3.62996, 2.54679 to \
  -2.15819, -0 to \
  -2.15903, -0 to \
  3.62996, 2.54716 front fs empty border lc rgb '#6165' lw 0.200001
set object 407 polygon from \
  3.53186, 2.58297 to \
  3.53186, 2.5826 to \
  -2.20724, -0 to \
  -2.20806, -0 to \
  3.53186, 2.58297 front fs empty border lc rgb '#6165' lw 0.200001
set object 408 polygon from \
  3.43376, 2.6178 to \
  3.43376, 2.61743 to \
  -2.25629, -0 to \
  -2.2571, -0 to \
  3.43376, 2.6178 front fs empty border lc rgb '#6165' lw 0.200001
set object 409 polygon from \
  3.33566, 2.65164 to \
  3.33566, 2.65128 to \
  -2.30534, -0 to \
  -2.30613, -0 to \
  3.33566, 2.65164 front fs empty border lc rgb '#6165' lw 0.200001
set object 410 polygon from \
  3.23756, 2.68451 to \
  3.23756, 2.68414 to \
  -2.35439, -0 to \
  -2.35516, -0 to \
  3.23756, 2.68451 front fs empty border lc rgb '#6165' lw 0.200001
set object 411 polygon from \
  3.13946, 2.71639 to \
  3.13946, 2.71603 to \
  -2.40344, -0 to \
  -2.4042, -0 to \
  3.13946, 2.71639 front fs empty border lc rgb '#6165' lw 0.200001
set object 412 polygon from \
  3.04136, 2.7473 to \
  3.04136, 2.74693 to \
  -2.45249, -0 to \
  -2.45323, -0 to \
  3.04136, 2.7473 front fs empty border lc rgb '#6165' lw 0.200001
set object 413 polygon from \
  2.94326, 2.77722 to \
  2.94326, 2.77685 to \
  -2.50154, -0 to \
  -2.50227, -0 to \
  2.94326, 2.77722 front fs empty border lc rgb '#6165' lw 0.200001
set object 414 polygon from \
  2.84516, 2.80616 to \
  2.84516, 2.8058 to \
  -2.55059, -0 to \
  -2.5513, -0 to \
  2.84516, 2.80616 front fs empty border lc rgb '#6165' lw 0.200001
set object 415 polygon from \
  2.74706, 2.83412 to \
  2.74706, 2.83376 to \
  -2.59964, -0 to \
  -2.60034, -0 to \
  2.74706, 2.83412 front fs empty border lc rgb '#6165' lw 0.200001
set object 416 polygon from \
  2.64896, 2.8611 to \
  2.64896, 2.86074 to \
  -2.64869, -0 to \
  -2.64938, -0 to \
  2.64896, 2.8611 front fs empty border lc rgb '#6165' lw 0.200001
set object 417 polygon from \
  2.55086, 2.8871 to \
  2.55086, 2.88674 to \
  -2.69774, -0 to \
  -2.69841, -0 to \
  2.55086, 2.8871 front fs empty border lc rgb '#6165' lw 0.200001
set object 418 polygon from \
  2.45276, 2.91212 to \
  2.45276, 2.91175 to \
  -2.74679, -0 to \
  -2.74745, -0 to \
  2.45276, 2.91212 front fs empty border lc rgb '#6165' lw 0.200001
set object 419 polygon from \
  2.35466, 2.93616 to \
  2.35466, 2.93579 to \
  -2.79584, -0 to \
  -2.79649, -0 to \
  2.35466, 2.93616 front fs empty border lc rgb '#6165' lw 0.200001
set object 420 polygon from \
  2.25656, 2.95921 to \
  2.25656, 2.95885 to \
  -2.84489, -0 to \
  -2.84553, -0 to \
  2.25656, 2.95921 front fs empty border lc rgb '#6165' lw 0.200001
set object 421 polygon from \
  2.15846, 2.98129 to \
  2.15846, 2.98092 to \
  -2.89394, -0 to \
  -2.89457, -0 to \
  2.15846, 2.98129 front fs empty border lc rgb '#6165' lw 0.200001
set object 422 polygon from \
  2.06036, 3.00238 to \
  2.06036, 3.00202 to \
  -2.94299, -0 to \
  -2.94361, -0 to \
  2.06036, 3.00238 front fs empty border lc rgb '#6165' lw 0.200001
set object 423 polygon from \
  1.96226, 3.0225 to \
  1.96226, 3.02213 to \
  -2.99204, -0 to \
  -2.99265, -0 to \
  1.96226, 3.0225 front fs empty border lc rgb '#6165' lw 0.200001
set object 424 polygon from \
  1.86416, 3.04163 to \
  1.86416, 3.04126 to \
  -3.04109, -0 to \
  -3.04169, -0 to \
  1.86416, 3.04163 front fs empty border lc rgb '#6165' lw 0.200001
set object 425 polygon from \
  1.76606, 3.05978 to \
  1.76606, 3.05941 to \
  -3.09014, -0 to \
  -3.09073, -0 to \
  1.76606, 3.05978 front fs empty border lc rgb '#6165' lw 0.200001
set object 426 polygon from \
  1.66796, 3.07695 to \
  1.66796, 3.07658 to \
  -3.13919, -0 to \
  -3.13977, -0 to \
  1.66796, 3.07695 front fs empty border lc rgb '#6165' lw 0.200001
set object 427 polygon from \
  1.56986, 3.09314 to \
  1.56986, 3.09277 to \
  -3.18824, -0 to \
  -3.18881, -0 to \
  1.56986, 3.09314 front fs empty border lc rgb '#6165' lw 0.200001
set object 428 polygon from \
  1.47176, 3.10835 to \
  1.47176, 3.10798 to \
  -3.23729, -0 to \
  -3.23785, -0 to \
  1.47176, 3.10835 front fs empty border lc rgb '#6165' lw 0.200001
set object 429 polygon from \
  1.37366, 3.12257 to \
  1.37366, 3.12221 to \
  -3.28634, -0 to \
  -3.28689, -0 to \
  1.37366, 3.12257 front fs empty border lc rgb '#6165' lw 0.200001
set object 430 polygon from \
  1.27556, 3.13582 to \
  1.27556, 3.13545 to \
  -3.33539, -0 to \
  -3.33594, -0 to \
  1.27556, 3.13582 front fs empty border lc rgb '#6165' lw 0.200001
set object 431 polygon from \
  1.17746, 3.14808 to \
  1.17746, 3.14772 to \
  -3.38444, -0 to \
  -3.38498, -0 to \
  1.17746, 3.14808 front fs empty border lc rgb '#6165' lw 0.200001
set object 432 polygon from \
  1.07936, 3.15937 to \
  1.07936, 3.159 to \
  -3.43349, -0 to \
  -3.43402, -0 to \
  1.07936, 3.15937 front fs empty border lc rgb '#6165' lw 0.200001
set object 433 polygon from \
  0.981251, 3.16967 to \
  0.981251, 3.1693 to \
  -3.48254, -0 to \
  -3.48306, -0 to \
  0.981251, 3.16967 front fs empty border lc rgb '#6165' lw 0.200001
set object 434 polygon from \
  0.883151, 3.17899 to \
  0.883151, 3.17863 to \
  -3.53159, -0 to \
  -3.53211, -0 to \
  0.883151, 3.17899 front fs empty border lc rgb '#6165' lw 0.200001
set object 435 polygon from \
  0.785051, 3.18733 to \
  0.785051, 3.18697 to \
  -3.58064, -0 to \
  -3.58115, -0 to \
  0.785051, 3.18733 front fs empty border lc rgb '#6165' lw 0.200001
set object 436 polygon from \
  0.686951, 3.19469 to \
  0.686951, 3.19433 to \
  -3.62969, -0 to \
  -3.63019, -0 to \
  0.686951, 3.19469 front fs empty border lc rgb '#6165' lw 0.200001
set object 437 polygon from \
  0.588851, 3.20107 to \
  0.588851, 3.20071 to \
  -3.67874, -0 to \
  -3.67924, -0 to \
  0.588851, 3.20107 front fs empty border lc rgb '#6165' lw 0.200001
set object 438 polygon from \
  0.490751, 3.20647 to \
  0.490751, 3.2061 to \
  -3.72779, -0 to \
  -3.72828, -0 to \
  0.490751, 3.20647 front fs empty border lc rgb '#6165' lw 0.200001
set object 439 polygon from \
  0.392651, 3.21089 to \
  0.392651, 3.21052 to \
  -3.77684, -0 to \
  -3.77732, -0 to \
  0.392651, 3.21089 front fs empty border lc rgb '#6165' lw 0.200001
set object 440 polygon from \
  0.294551, 3.21432 to \
  0.294551, 3.21396 to \
  -3.82589, -0 to \
  -3.82637, -0 to \
  0.294551, 3.21432 front fs empty border lc rgb '#6165' lw 0.200001
set object 441 polygon from \
  0.196451, 3.21678 to \
  0.196451, 3.21641 to \
  -3.87494, -0 to \
  -3.87541, -0 to \
  0.196451, 3.21678 front fs empty border lc rgb '#6165' lw 0.200001
set object 442 polygon from \
  0.098351, 3.21825 to \
  0.098351, 3.21789 to \
  -3.92399, -0 to \
  -3.92446, -0 to \
  0.098351, 3.21825 front fs empty border lc rgb '#6165' lw 0.200001
set object 443 polygon from \
  0.000250911, 3.21875 to \
  0.000250911, 3.21838 to \
  -3.97304, -0 to \
  -3.9735, -0 to \
  0.000250911, 3.21875 front fs empty border lc rgb '#6165' lw 0.200001
set object 444 polygon from \
  -0.097849, 3.21826 to \
  -0.097849, 3.21789 to \
  -4.02209, -0 to \
  -4.02254, -0 to \
  -0.097849, 3.21826 front fs empty border lc rgb '#6165' lw 0.200001
set object 445 polygon from \
  -0.195949, 3.21679 to \
  -0.195949, 3.21642 to \
  -4.07114, -0 to \
  -4.07159, -0 to \
  -0.195949, 3.21679 front fs empty border lc rgb '#6165' lw 0.200001
set object 446 polygon from \
  -0.294049, 3.21434 to \
  -0.294049, 3.21397 to \
  -4.12019, -0 to \
  -4.12063, -0 to \
  -0.294049, 3.21434 front fs empty border lc rgb '#6165' lw 0.200001
set object 447 polygon from \
  -0.392149, 3.21091 to \
  -0.392149, 3.21054 to \
  -4.16924, -0 to \
  -4.16968, -0 to \
  -0.392149, 3.21091 front fs empty border lc rgb '#6165' lw 0.200001
set object 448 polygon from \
  -0.490249, 3.2065 to \
  -0.490249, 3.20613 to \
  -4.21829, -0 to \
  -4.21872, -0 to \
  -0.490249, 3.2065 front fs empty border lc rgb '#6165' lw 0.200001
set object 449 polygon from \
  -0.588349, 3.2011 to \
  -0.588349, 3.20074 to \
  -4.26734, -0 to \
  -4.26777, -0 to \
  -0.588349, 3.2011 front fs empty border lc rgb '#6165' lw 0.200001
set object 450 polygon from \
  -0.686449, 3.19473 to \
  -0.686449, 3.19436 to \
  -4.31639, -0 to \
  -4.31681, -0 to \
  -0.686449, 3.19473 front fs empty border lc rgb '#6165' lw 0.200001
set object 451 polygon from \
  -0.784549, 3.18738 to \
  -0.784549, 3.18701 to \
  -4.36544, -0 to \
  -4.36586, -0 to \
  -0.784549, 3.18738 front fs empty border lc rgb '#6165' lw 0.200001
set object 452 polygon from \
  -0.882649, 3.17904 to \
  -0.882649, 3.17867 to \
  -4.41449, -0 to \
  -4.4149, -0 to \
  -0.882649, 3.17904 front fs empty border lc rgb '#6165' lw 0.200001
set object 453 polygon from \
  -0.980749, 3.16972 to \
  -0.980749, 3.16935 to \
  -4.46354, -0 to \
  -4.46395, -0 to \
  -0.980749, 3.16972 front fs empty border lc rgb '#6165' lw 0.200001
set object 454 polygon from \
  -1.07884, 3.15942 to \
  -1.07884, 3.15906 to \
  -4.51259, -0 to \
  -4.513, -0 to \
  -1.07884, 3.15942 front fs empty border lc rgb '#6165' lw 0.200001
set object 455 polygon from \
  -1.17694, 3.14815 to \
  -1.17694, 3.14778 to \
  -4.56164, -0 to \
  -4.56204, -0 to \
  -1.17694, 3.14815 front fs empty border lc rgb '#6165' lw 0.200001
set object 456 polygon from \
  -1.27504, 3.13589 to \
  -1.27504, 3.13552 to \
  -4.61069, -0 to \
  -4.61109, -0 to \
  -1.27504, 3.13589 front fs empty border lc rgb '#6165' lw 0.200001
set object 457 polygon from \
  -1.37314, 3.12264 to \
  -1.37314, 3.12228 to \
  -4.65974, -0 to \
  -4.66013, -0 to \
  -1.37314, 3.12264 front fs empty border lc rgb '#6165' lw 0.200001
set object 458 polygon from \
  -1.47124, 3.10842 to \
  -1.47124, 3.10805 to \
  -4.70879, -0 to \
  -4.70918, -0 to \
  -1.47124, 3.10842 front fs empty border lc rgb '#6165' lw 0.200001
set object 459 polygon from \
  -1.56934, 3.09322 to \
  -1.56934, 3.09285 to \
  -4.75784, -0 to \
  -4.75822, -0 to \
  -1.56934, 3.09322 front fs empty border lc rgb '#6165' lw 0.200001
set object 460 polygon from \
  -1.66744, 3.07704 to \
  -1.66744, 3.07667 to \
  -4.80689, -0 to \
  -4.80727, -0 to \
  -1.66744, 3.07704 front fs empty border lc rgb '#6165' lw 0.200001
set object 461 polygon from \
  -1.76554, 3.05987 to \
  -1.76554, 3.0595 to \
  -4.85594, -0 to \
  -4.85632, -0 to \
  -1.76554, 3.05987 front fs empty border lc rgb '#6165' lw 0.200001
set object 462 polygon from \
  -1.86364, 3.04172 to \
  -1.86364, 3.04136 to \
  -4.90499, -0 to \
  -4.90536, -0 to \
  -1.86364, 3.04172 front fs empty border lc rgb '#6165' lw 0.200001
set object 463 polygon from \
  -1.96174, 3.0226 to \
  -1.96174, 3.02223 to \
  -4.95404, -0 to \
  -4.95441, -0 to \
  -1.96174, 3.0226 front fs empty border lc rgb '#6165' lw 0.200001
set object 464 polygon from \
  -2.05984, 3.00249 to \
  -2.05984, 3.00212 to \
  -5.00309, -0 to \
  -5.00346, -0 to \
  -2.05984, 3.00249 front fs empty border lc rgb '#6165' lw 0.200001
set object 465 polygon from \
  -2.15794, 2.9814 to \
  -2.15794, 2.98103 to \
  -5.05214, -0 to \
  -5.0525, -0 to \
  -2.15794, 2.9814 front fs empty border lc rgb '#6165' lw 0.200001
set object 466 polygon from \
  -2.25604, 2.95933 to \
  -2.25604, 2.95896 to \
  -5.10119, -0 to \
  -5.10155, -0 to \
  -2.25604, 2.95933 front fs empty border lc rgb '#6165' lw 0.200001
set object 467 polygon from \
  -2.35414, 2.93628 to \
  -2.35414, 2.93591 to \
  -5.15024, -0 to \
  -5.1506, -0 to \
  -2.35414, 2.93628 front fs empty border lc rgb '#6165' lw 0.200001
set object 468 polygon from \
  -2.45224, 2.91225 to \
  -2.45224, 2.91188 to \
  -5.19929, -0 to \
  -5.19964, -0 to \
  -2.45224, 2.91225 front fs empty border lc rgb '#6165' lw 0.200001
set object 469 polygon from \
  -2.55034, 2.88723 to \
  -2.55034, 2.88687 to \
  -5.24834, -0 to \
  -5.24869, -0 to \
  -2.55034, 2.88723 front fs empty border lc rgb '#6165' lw 0.200001
set object 470 polygon from \
  -2.64844, 2.86124 to \
  -2.64844, 2.86087 to \
  -5.29739, -0 to \
  -5.29774, -0 to \
  -2.64844, 2.86124 front fs empty border lc rgb '#6165' lw 0.200001
set object 471 polygon from \
  -2.74654, 2.83427 to \
  -2.74654, 2.8339 to \
  -5.34644, -0 to \
  -5.34678, -0 to \
  -2.74654, 2.83427 front fs empty border lc rgb '#6165' lw 0.200001
set object 472 polygon from \
  -2.84464, 2.80631 to \
  -2.84464, 2.80594 to \
  -5.39549, -0 to \
  -5.39583, -0 to \
  -2.84464, 2.80631 front fs empty border lc rgb '#6165' lw 0.200001
set object 473 polygon from \
  -2.94274, 2.77737 to \
  -2.94274, 2.777 to \
  -5.44454, -0 to \
  -5.44488, -0 to \
  -2.94274, 2.77737 front fs empty border lc rgb '#6165' lw 0.200001
set object 474 polygon from \
  -3.04084, 2.74745 to \
  -3.04084, 2.74709 to \
  -5.49359, -0 to \
  -5.49392, -0 to \
  -3.04084, 2.74745 front fs empty border lc rgb '#6165' lw 0.200001
set object 475 polygon from \
  -3.13894, 2.71656 to \
  -3.13894, 2.71619 to \
  -5.54264, -0 to \
  -5.54297, -0 to \
  -3.13894, 2.71656 front fs empty border lc rgb '#6165' lw 0.200001
set object 476 polygon from \
  -3.23704, 2.68468 to \
  -3.23704, 2.68431 to \
  -5.59169, -0 to \
  -5.59202, -0 to \
  -3.23704, 2.68468 front fs empty border lc rgb '#6165' lw 0.200001
set object 477 polygon from \
  -3.33514, 2.65181 to \
  -3.33514, 2.65145 to \
  -5.64074, -0 to \
  -5.64107, -0 to \
  -3.33514, 2.65181 front fs empty border lc rgb '#6165' lw 0.200001
set object 478 polygon from \
  -3.43324, 2.61797 to \
  -3.43324, 2.6176 to \
  -5.68979, -0 to \
  -5.69011, -0 to \
  -3.43324, 2.61797 front fs empty border lc rgb '#6165' lw 0.200001
set object 479 polygon from \
  -3.53134, 2.58315 to \
  -3.53134, 2.58278 to \
  -5.73884, -0 to \
  -5.73916, -0 to \
  -3.53134, 2.58315 front fs empty border lc rgb '#6165' lw 0.200001
set object 480 polygon from \
  -3.62944, 2.54735 to \
  -3.62944, 2.54698 to \
  -5.78789, -0 to \
  -5.78821, -0 to \
  -3.62944, 2.54735 front fs empty border lc rgb '#6165' lw 0.200001
set object 481 polygon from \
  -3.72754, 2.51056 to \
  -3.72754, 2.51019 to \
  -5.83694, -0 to \
  -5.83725, -0 to \
  -3.72754, 2.51056 front fs empty border lc rgb '#6165' lw 0.200001
set object 482 polygon from \
  -3.82564, 2.47279 to \
  -3.82564, 2.47243 to \
  -5.88599, -0 to \
  -5.8863, -0 to \
  -3.82564, 2.47279 front fs empty border lc rgb '#6165' lw 0.200001
set object 483 polygon from \
  -3.92374, 2.43405 to \
  -3.92374, 2.43368 to \
  -5.93504, -0 to \
  -5.93535, -0 to \
  -3.92374, 2.43405 front fs empty border lc rgb '#6165' lw 0.200001
set object 484 polygon from \
  -4.02184, 2.39432 to \
  -4.02184, 2.39395 to \
  -5.98409, -0 to \
  -5.9844, -0 to \
  -4.02184, 2.39432 front fs empty border lc rgb '#6165' lw 0.200001
set object 485 polygon from \
  -4.11994, 2.35361 to \
  -4.11994, 2.35324 to \
  -6.03314, -0 to \
  -6.03344, -0 to \
  -4.11994, 2.35361 front fs empty border lc rgb '#6165' lw 0.200001
set object 486 polygon from \
  -4.21804, 2.31192 to \
  -4.21804, 2.31155 to \
  -6.08219, -0 to \
  -6.08249, -0 to \
  -4.21804, 2.31192 front fs empty border lc rgb '#6165' lw 0.200001
set object 487 polygon from \
  -4.31614, 2.26925 to \
  -4.31614, 2.26888 to \
  -6.13124, -0 to \
  -6.13154, -0 to \
  -4.31614, 2.26925 front fs empty border lc rgb '#6165' lw 0.200001
set object 488 polygon from \
  -4.41424, 2.2256 to \
  -4.41424, 2.22523 to \
  -6.18029, -0 to \
  -6.18059, -0 to \
  -4.41424, 2.2256 front fs empty border lc rgb '#6165' lw 0.200001
set object 489 polygon from \
  -4.51234, 2.18096 to \
  -4.51234, 2.1806 to \
  -6.22934, -0 to \
  -6.22963, -0 to \
  -4.51234, 2.18096 front fs empty border lc rgb '#6165' lw 0.200001
set object 490 polygon from \
  -4.61044, 2.13535 to \
  -4.61044, 2.13498 to \
  -6.27839, -0 to \
  -6.27868, -0 to \
  -4.61044, 2.13535 front fs empty border lc rgb '#6165' lw 0.200001
set object 491 polygon from \
  -4.70854, 2.08876 to \
  -4.70854, 2.08839 to \
  -6.32744, -0 to \
  -6.32773, -0 to \
  -4.70854, 2.08876 front fs empty border lc rgb '#6165' lw 0.200001
set object 492 polygon from \
  -4.80664, 2.04118 to \
  -4.80664, 2.04081 to \
  -6.37649, -0 to \
  -6.37678, -0 to \
  -4.80664, 2.04118 front fs empty border lc rgb '#6165' lw 0.200001
set object 493 polygon from \
  -4.90474, 1.99262 to \
  -4.90474, 1.99225 to \
  -6.42554, -0 to \
  -6.42583, -0 to \
  -4.90474, 1.99262 front fs empty border lc rgb '#6165' lw 0.200001
set object 494 polygon from \
  -5.00284, 1.94308 to \
  -5.00284, 1.94272 to \
  -6.47459, -0 to \
  -6.47487, -0 to \
  -5.00284, 1.94308 front fs empty border lc rgb '#6165' lw 0.200001
set object 495 polygon from \
  -5.10094, 1.89257 to \
  -5.10094, 1.8922 to \
  -6.52364, -0 to \
  -6.52392, -0 to \
  -5.10094, 1.89257 front fs empty border lc rgb '#6165' lw 0.200001
set object 496 polygon from \
  -5.19904, 1.84107 to \
  -5.19904, 1.8407 to \
  -6.57269, -0 to \
  -6.57297, -0 to \
  -5.19904, 1.84107 front fs empty border lc rgb '#6165' lw 0.200001
set object 497 polygon from \
  -5.29714, 1.78858 to \
  -5.29714, 1.78822 to \
  -6.62174, -0 to \
  -6.62202, -0 to \
  -5.29714, 1.78858 front fs empty border lc rgb '#6165' lw 0.200001
set object 498 polygon from \
  -5.39524, 1.73512 to \
  -5.39524, 1.73475 to \
  -6.67079, -0 to \
  -6.67107, -0 to \
  -5.39524, 1.73512 front fs empty border lc rgb '#6165' lw 0.200001
set object 499 polygon from \
  -5.49334, 1.68068 to \
  -5.49334, 1.68031 to \
  -6.71984, -0 to \
  -6.72011, -0 to \
  -5.49334, 1.68068 front fs empty border lc rgb '#6165' lw 0.200001
set object 500 polygon from \
  -5.59144, 1.62526 to \
  -5.59144, 1.62489 to \
  -6.76889, -0 to \
  -6.76916, -0 to \
  -5.59144, 1.62526 front fs empty border lc rgb '#6165' lw 0.200001
set object 501 polygon from \
  -5.68954, 1.56885 to \
  -5.68954, 1.56848 to \
  -6.81794, -0 to \
  -6.81821, -0 to \
  -5.68954, 1.56885 front fs empty border lc rgb '#6165' lw 0.200001
set object 502 polygon from \
  -5.78764, 1.51146 to \
  -5.78764, 1.5111 to \
  -6.86699, -0 to \
  -6.86726, -0 to \
  -5.78764, 1.51146 front fs empty border lc rgb '#6165' lw 0.200001
set object 503 polygon from \
  -5.88574, 1.4531 to \
  -5.88574, 1.45273 to \
  -6.91604, -0 to \
  -6.91631, -0 to \
  -5.88574, 1.4531 front fs empty border lc rgb '#6165' lw 0.200001
set object 504 polygon from \
  -5.98384, 1.39375 to \
  -5.98384, 1.39338 to \
  -6.96509, -0 to \
  -6.96535, -0 to \
  -5.98384, 1.39375 front fs empty border lc rgb '#6165' lw 0.200001
set object 505 polygon from \
  -6.08194, 1.33342 to \
  -6.08194, 1.33305 to \
  -7.01414, -0 to \
  -7.0144, -0 to \
  -6.08194, 1.33342 front fs empty border lc rgb '#6165' lw 0.200001
set object 506 polygon from \
  -6.18004, 1.27211 to \
  -6.18004, 1.27174 to \
  -7.06319, -0 to \
  -7.06345, -0 to \
  -6.18004, 1.27211 front fs empty border lc rgb '#6165' lw 0.200001
set object 507 polygon from \
  -6.27814, 1.20982 to \
  -6.27814, 1.20945 to \
  -7.11224, -0 to \
  -7.1125, -0 to \
  -6.27814, 1.20982 front fs empty border lc rgb '#6165' lw 0.200001
set object 508 polygon from \
  -6.37624, 1.14655 to \
  -6.37624, 1.14618 to \
  -7.16129, -0 to \
  -7.16155, -0 to \
  -6.37624, 1.14655 front fs empty border lc rgb '#6165' lw 0.200001
set object 509 polygon from \
  -6.47434, 1.08229 to \
  -6.47434, 1.08193 to \
  -7.21034, -0 to \
  -7.2106, -0 to \
  -6.47434, 1.08229 front fs empty border lc rgb '#6165' lw 0.200001
set object 510 polygon from \
  -6.57244, 1.01706 to \
  -6.57244, 1.01669 to \
  -7.25939, -0 to \
  -7.25964, -0 to \
  -6.57244, 1.01706 front fs empty border lc rgb '#6165' lw 0.200001
set object 511 polygon from \
  -6.67054, 0.950841 to \
  -6.67054, 0.950473 to \
  -7.30844, -0 to \
  -7.30869, -0 to \
  -6.67054, 0.950841 front fs empty border lc rgb '#6165' lw 0.200001
set object 512 polygon from \
  -6.76864, 0.883645 to \
  -6.76864, 0.883277 to \
  -7.35749, -0 to \
  -7.35774, -0 to \
  -6.76864, 0.883645 front fs empty border lc rgb '#6165' lw 0.200001
set object 513 polygon from \
  -6.86674, 0.815468 to \
  -6.86674, 0.8151 to \
  -7.40654, -0 to \
  -7.40679, -0 to \
  -6.86674, 0.815468 front fs empty border lc rgb '#6165' lw 0.200001
set object 514 polygon from \
  -6.96484, 0.74631 to \
  -6.96484, 0.745942 to \
  -7.45559, -0 to \
  -7.45584, -0 to \
  -6.96484, 0.74631 front fs empty border lc rgb '#6165' lw 0.200001
set object 515 polygon from \
  -7.06294, 0.676171 to \
  -7.06294, 0.675803 to \
  -7.50464, -0 to \
  -7.50489, -0 to \
  -7.06294, 0.676171 front fs empty border lc rgb '#6165' lw 0.200001
set object 516 polygon from \
  -7.16104, 0.605051 to \
  -7.16104, 0.604683 to \
  -7.55369, -0 to \
  -7.55393, -0 to \
  -7.16104, 0.605051 front fs empty border lc rgb '#6165' lw 0.200001
set object 517 polygon from \
  -7.25914, 0.53295 to \
  -7.25914, 0.532582 to \
  -7.60274, -0 to \
  -7.60298, -0 to \
  -7.25914, 0.53295 front fs empty border lc rgb '#6165' lw 0.200001
set object 518 polygon from \
  -7.35724, 0.459868 to \
  -7.35724, 0.4595 to \
  -7.65179, -0 to \
  -7.65203, -0 to \
  -7.35724, 0.459868 front fs empty border lc rgb '#6165' lw 0.200001
set object 519 polygon from \
  -7.45534, 0.385805 to \
  -7.45534, 0.385437 to \
  -7.70084, -0 to \
  -7.70108, -0 to \
  -7.45534, 0.385805 front fs empty border lc rgb '#6165' lw 0.200001
set object 520 polygon from \
  -7.55344, 0.310761 to \
  -7.55344, 0.310393 to \
  -7.74989, -0 to \
  -7.75013, -0 to \
  -7.55344, 0.310761 front fs empty border lc rgb '#6165' lw 0.200001
set object 521 polygon from \
  -7.65154, 0.234736 to \
  -7.65154, 0.234368 to \
  -7.79894, -0 to \
  -7.79918, -0 to \
  -7.65154, 0.234736 front fs empty border lc rgb '#6165' lw 0.200001
set object 522 polygon from \
  -7.74964, 0.15773 to \
  -7.74964, 0.157362 to \
  -7.84799, -0 to \
  -7.84823, -0 to \
  -7.74964, 0.15773 front fs empty border lc rgb '#6165' lw 0.200001
set object 523 polygon from \
  -7.84774, 0.0797428 to \
  -7.84774, 0.0793745 to \
  -7.89704, -0 to \
  -7.89727, -0 to \
  -7.84774, 0.0797428 front fs empty border lc rgb '#6165' lw 0.200001
set object 524 polygon from \
  -7.94584, 0.00077476 to \
  -7.94584, 0.000406475 to \
  -7.94609, -0 to \
  -7.94632, -0 to \
  -7.94584, 0.00077476 front fs empty border lc rgb '#6165' lw 0.200001
set object 525 polygon from \
  -0.0860015, -0 to \
  -0.0860015, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 526 polygon from \
  -0.116575, -0 to \
  -0.04905, -0 to \
  -0.116575, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 527 polygon from \
  -0.159467, -0 to \
  -0.0980999, -0 to \
  -0.159467, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 528 polygon from \
  -0.205437, -0 to \
  -0.147149, -0 to \
  -0.205437, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 529 polygon from \
  -0.25264, -0 to \
  -0.196199, -0 to \
  -0.25264, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 530 polygon from \
  -0.300458, -0 to \
  -0.245249, -0 to \
  -0.300458, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 531 polygon from \
  -0.348628, -0 to \
  -0.294299, -0 to \
  -0.348628, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 532 polygon from \
  -0.397018, -0 to \
  -0.343349, -0 to \
  -0.397018, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 533 polygon from \
  -0.445555, -0 to \
  -0.392399, -0 to \
  -0.445555, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 534 polygon from \
  -0.494195, -0 to \
  -0.441449, -0 to \
  -0.494195, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 535 polygon from \
  -0.542909, -0 to \
  -0.490499, -0 to \
  -0.542909, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 536 polygon from \
  -0.591679, -0 to \
  -0.539549, -0 to \
  -0.591679, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 537 polygon from \
  -0.640492, -0 to \
  -0.588599, -0 to \
  -0.640492, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 538 polygon from \
  -0.689339, -0 to \
  -0.637649, -0 to \
  -0.689339, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 539 polygon from \
  -0.738213, -0 to \
  -0.686699, -0 to \
  -0.738213, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 540 polygon from \
  -0.787109, -0 to \
  -0.735749, -0 to \
  -0.787109, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 541 polygon from \
  -0.836023, -0 to \
  -0.784799, -0 to \
  -0.836023, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 542 polygon from \
  -0.884952, -0 to \
  -0.833849, -0 to \
  -0.884952, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 543 polygon from \
  -0.933894, -0 to \
  -0.882899, -0 to \
  -0.933894, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 544 polygon from \
  -0.982847, -0 to \
  -0.931949, -0 to \
  -0.982847, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 545 polygon from \
  -1.0318, -0 to \
  -0.980999, -0 to \
  -1.0318, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 546 polygon from \
  -1.08077, -0 to \
  -1.03004, -0 to \
  -1.08077, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 547 polygon from \
  -1.12975, -0 to \
  -1.07909, -0 to \
  -1.12975, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 548 polygon from \
  -1.17873, -0 to \
  -1.12814, -0 to \
  -1.17873, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 549 polygon from \
  -1.22772, -0 to \
  -1.17719, -0 to \
  -1.22772, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 550 polygon from \
  -1.27672, -0 to \
  -1.22624, -0 to \
  -1.27672, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 551 polygon from \
  -1.32571, -0 to \
  -1.27529, -0 to \
  -1.32571, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 552 polygon from \
  -1.37471, -0 to \
  -1.32434, -0 to \
  -1.37471, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 553 polygon from \
  -1.42372, -0 to \
  -1.37339, -0 to \
  -1.42372, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 554 polygon from \
  -1.47273, -0 to \
  -1.42244, -0 to \
  -1.47273, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 555 polygon from \
  -1.52174, -0 to \
  -1.47149, -0 to \
  -1.52174, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 556 polygon from \
  -1.57075, -0 to \
  -1.52054, -0 to \
  -1.57075, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 557 polygon from \
  -1.61976, -0 to \
  -1.56959, -0 to \
  -1.61976, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 558 polygon from \
  -1.66878, -0 to \
  -1.61864, -0 to \
  -1.66878, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 559 polygon from \
  -1.7178, -0 to \
  -1.66769, -0 to \
  -1.7178, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 560 polygon from \
  -1.76682, -0 to \
  -1.71674, -0 to \
  -1.76682, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 561 polygon from \
  -1.81584, -0 to \
  -1.76579, -0 to \
  -1.81584, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 562 polygon from \
  -1.86487, -0 to \
  -1.81484, -0 to \
  -1.86487, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 563 polygon from \
  -1.91389, -0 to \
  -1.86389, -0 to \
  -1.91389, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 564 polygon from \
  -1.96292, -0 to \
  -1.91294, -0 to \
  -1.96292, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 565 polygon from \
  -2.01195, -0 to \
  -1.96199, -0 to \
  -2.01195, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 566 polygon from \
  -2.06097, -0 to \
  -2.01104, -0 to \
  -2.06097, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 567 polygon from \
  -2.11, -0 to \
  -2.06009, -0 to \
  -2.11, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 568 polygon from \
  -2.15903, -0 to \
  -2.10914, -0 to \
  -2.15903, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 569 polygon from \
  -2.20807, -0 to \
  -2.15819, -0 to \
  -2.20807, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 570 polygon from \
  -2.2571, -0 to \
  -2.20724, -0 to \
  -2.2571, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 571 polygon from \
  -2.30613, -0 to \
  -2.25629, -0 to \
  -2.30613, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 572 polygon from \
  -2.35516, -0 to \
  -2.30534, -0 to \
  -2.35516, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 573 polygon from \
  -2.4042, -0 to \
  -2.35439, -0 to \
  -2.4042, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 574 polygon from \
  -2.45323, -0 to \
  -2.40344, -0 to \
  -2.45323, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 575 polygon from \
  -2.50227, -0 to \
  -2.45249, -0 to \
  -2.50227, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 576 polygon from \
  -2.55131, -0 to \
  -2.50154, -0 to \
  -2.55131, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 577 polygon from \
  -2.60034, -0 to \
  -2.55059, -0 to \
  -2.60034, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 578 polygon from \
  -2.64938, -0 to \
  -2.59964, -0 to \
  -2.64938, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 579 polygon from \
  -2.69842, -0 to \
  -2.64869, -0 to \
  -2.69842, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 580 polygon from \
  -2.74745, -0 to \
  -2.69774, -0 to \
  -2.74745, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 581 polygon from \
  -2.79649, -0 to \
  -2.74679, -0 to \
  -2.79649, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 582 polygon from \
  -2.84553, -0 to \
  -2.79584, -0 to \
  -2.84553, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 583 polygon from \
  -2.89457, -0 to \
  -2.84489, -0 to \
  -2.89457, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 584 polygon from \
  -2.94361, -0 to \
  -2.89394, -0 to \
  -2.94361, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 585 polygon from \
  -2.99265, -0 to \
  -2.94299, -0 to \
  -2.99265, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 586 polygon from \
  -3.04169, -0 to \
  -2.99204, -0 to \
  -3.04169, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 587 polygon from \
  -3.09073, -0 to \
  -3.04109, -0 to \
  -3.09073, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 588 polygon from \
  -3.13977, -0 to \
  -3.09014, -0 to \
  -3.13977, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 589 polygon from \
  -3.18881, -0 to \
  -3.13919, -0 to \
  -3.18881, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 590 polygon from \
  -3.23785, -0 to \
  -3.18824, -0 to \
  -3.23785, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 591 polygon from \
  -3.2869, -0 to \
  -3.23729, -0 to \
  -3.2869, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 592 polygon from \
  -3.33594, -0 to \
  -3.28634, -0 to \
  -3.33594, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 593 polygon from \
  -3.38498, -0 to \
  -3.33539, -0 to \
  -3.38498, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 594 polygon from \
  -3.43402, -0 to \
  -3.38444, -0 to \
  -3.43402, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 595 polygon from \
  -3.48307, -0 to \
  -3.43349, -0 to \
  -3.48307, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 596 polygon from \
  -3.53211, -0 to \
  -3.48254, -0 to \
  -3.53211, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 597 polygon from \
  -3.58115, -0 to \
  -3.53159, -0 to \
  -3.58115, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 598 polygon from \
  -3.63019, -0 to \
  -3.58064, -0 to \
  -3.63019, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 599 polygon from \
  -3.67924, -0 to \
  -3.62969, -0 to \
  -3.67924, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 600 polygon from \
  -3.72828, -0 to \
  -3.67874, -0 to \
  -3.72828, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 601 polygon from \
  -3.77732, -0 to \
  -3.72779, -0 to \
  -3.77732, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 602 polygon from \
  -3.82637, -0 to \
  -3.77684, -0 to \
  -3.82637, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 603 polygon from \
  -3.87541, -0 to \
  -3.82589, -0 to \
  -3.87541, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 604 polygon from \
  -3.92446, -0 to \
  -3.87494, -0 to \
  -3.92446, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 605 polygon from \
  -3.9735, -0 to \
  -3.92399, -0 to \
  -3.9735, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 606 polygon from \
  -4.02255, -0 to \
  -3.97304, -0 to \
  -4.02255, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 607 polygon from \
  -4.07159, -0 to \
  -4.02209, -0 to \
  -4.07159, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 608 polygon from \
  -4.12063, -0 to \
  -4.07114, -0 to \
  -4.12063, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 609 polygon from \
  -4.16968, -0 to \
  -4.12019, -0 to \
  -4.16968, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 610 polygon from \
  -4.21872, -0 to \
  -4.16924, -0 to \
  -4.21872, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 611 polygon from \
  -4.26777, -0 to \
  -4.21829, -0 to \
  -4.26777, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 612 polygon from \
  -4.31681, -0 to \
  -4.26734, -0 to \
  -4.31681, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 613 polygon from \
  -4.36586, -0 to \
  -4.31639, -0 to \
  -4.36586, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 614 polygon from \
  -4.41491, -0 to \
  -4.36544, -0 to \
  -4.41491, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 615 polygon from \
  -4.46395, -0 to \
  -4.41449, -0 to \
  -4.46395, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 616 polygon from \
  -4.513, -0 to \
  -4.46354, -0 to \
  -4.513, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 617 polygon from \
  -4.56204, -0 to \
  -4.51259, -0 to \
  -4.56204, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 618 polygon from \
  -4.61109, -0 to \
  -4.56164, -0 to \
  -4.61109, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 619 polygon from \
  -4.66013, -0 to \
  -4.61069, -0 to \
  -4.66013, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 620 polygon from \
  -4.70918, -0 to \
  -4.65974, -0 to \
  -4.70918, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 621 polygon from \
  -4.75823, -0 to \
  -4.70879, -0 to \
  -4.75823, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 622 polygon from \
  -4.80727, -0 to \
  -4.75784, -0 to \
  -4.80727, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 623 polygon from \
  -4.85632, -0 to \
  -4.80689, -0 to \
  -4.85632, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 624 polygon from \
  -4.90536, -0 to \
  -4.85594, -0 to \
  -4.90536, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 625 polygon from \
  -4.95441, -0 to \
  -4.90499, -0 to \
  -4.95441, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 626 polygon from \
  -5.00346, -0 to \
  -4.95404, -0 to \
  -5.00346, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 627 polygon from \
  -5.0525, -0 to \
  -5.00309, -0 to \
  -5.0525, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 628 polygon from \
  -5.10155, -0 to \
  -5.05214, -0 to \
  -5.10155, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 629 polygon from \
  -5.1506, -0 to \
  -5.10119, -0 to \
  -5.1506, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 630 polygon from \
  -5.19964, -0 to \
  -5.15024, -0 to \
  -5.19964, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 631 polygon from \
  -5.24869, -0 to \
  -5.19929, -0 to \
  -5.24869, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 632 polygon from \
  -5.29774, -0 to \
  -5.24834, -0 to \
  -5.29774, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 633 polygon from \
  -5.34678, -0 to \
  -5.29739, -0 to \
  -5.34678, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 634 polygon from \
  -5.39583, -0 to \
  -5.34644, -0 to \
  -5.39583, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 635 polygon from \
  -5.44488, -0 to \
  -5.39549, -0 to \
  -5.44488, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 636 polygon from \
  -5.49392, -0 to \
  -5.44454, -0 to \
  -5.49392, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 637 polygon from \
  -5.54297, -0 to \
  -5.49359, -0 to \
  -5.54297, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 638 polygon from \
  -5.59202, -0 to \
  -5.54264, -0 to \
  -5.59202, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 639 polygon from \
  -5.64107, -0 to \
  -5.59169, -0 to \
  -5.64107, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 640 polygon from \
  -5.69011, -0 to \
  -5.64074, -0 to \
  -5.69011, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 641 polygon from \
  -5.73916, -0 to \
  -5.68979, -0 to \
  -5.73916, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 642 polygon from \
  -5.78821, -0 to \
  -5.73884, -0 to \
  -5.78821, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 643 polygon from \
  -5.83726, -0 to \
  -5.78789, -0 to \
  -5.83726, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 644 polygon from \
  -5.8863, -0 to \
  -5.83694, -0 to \
  -5.8863, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 645 polygon from \
  -5.93535, -0 to \
  -5.88599, -0 to \
  -5.93535, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 646 polygon from \
  -5.9844, -0 to \
  -5.93504, -0 to \
  -5.9844, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 647 polygon from \
  -6.03345, -0 to \
  -5.98409, -0 to \
  -6.03345, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 648 polygon from \
  -6.08249, -0 to \
  -6.03314, -0 to \
  -6.08249, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 649 polygon from \
  -6.13154, -0 to \
  -6.08219, -0 to \
  -6.13154, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 650 polygon from \
  -6.18059, -0 to \
  -6.13124, -0 to \
  -6.18059, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 651 polygon from \
  -6.22964, -0 to \
  -6.18029, -0 to \
  -6.22964, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 652 polygon from \
  -6.27868, -0 to \
  -6.22934, -0 to \
  -6.27868, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 653 polygon from \
  -6.32773, -0 to \
  -6.27839, -0 to \
  -6.32773, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 654 polygon from \
  -6.37678, -0 to \
  -6.32744, -0 to \
  -6.37678, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 655 polygon from \
  -6.42583, -0 to \
  -6.37649, -0 to \
  -6.42583, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 656 polygon from \
  -6.47487, -0 to \
  -6.42554, -0 to \
  -6.47487, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 657 polygon from \
  -6.52392, -0 to \
  -6.47459, -0 to \
  -6.52392, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 658 polygon from \
  -6.57297, -0 to \
  -6.52364, -0 to \
  -6.57297, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 659 polygon from \
  -6.62202, -0 to \
  -6.57269, -0 to \
  -6.62202, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 660 polygon from \
  -6.67107, -0 to \
  -6.62174, -0 to \
  -6.67107, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 661 polygon from \
  -6.72011, -0 to \
  -6.67079, -0 to \
  -6.72011, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 662 polygon from \
  -6.76916, -0 to \
  -6.71984, -0 to \
  -6.76916, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 663 polygon from \
  -6.81821, -0 to \
  -6.76889, -0 to \
  -6.81821, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 664 polygon from \
  -6.86726, -0 to \
  -6.81794, -0 to \
  -6.86726, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 665 polygon from \
  -6.91631, -0 to \
  -6.86699, -0 to \
  -6.91631, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 666 polygon from \
  -6.96536, -0 to \
  -6.91604, -0 to \
  -6.96536, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 667 polygon from \
  -7.0144, -0 to \
  -6.96509, -0 to \
  -7.0144, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 668 polygon from \
  -7.06345, -0 to \
  -7.01414, -0 to \
  -7.06345, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 669 polygon from \
  -7.1125, -0 to \
  -7.06319, -0 to \
  -7.1125, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 670 polygon from \
  -7.16155, -0 to \
  -7.11224, -0 to \
  -7.16155, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 671 polygon from \
  -7.2106, -0 to \
  -7.16129, -0 to \
  -7.2106, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 672 polygon from \
  -7.25964, -0 to \
  -7.21034, -0 to \
  -7.25964, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 673 polygon from \
  -7.30869, -0 to \
  -7.25939, -0 to \
  -7.30869, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 674 polygon from \
  -7.35774, -0 to \
  -7.30844, -0 to \
  -7.35774, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 675 polygon from \
  -7.40679, -0 to \
  -7.35749, -0 to \
  -7.40679, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 676 polygon from \
  -7.45584, -0 to \
  -7.40654, -0 to \
  -7.45584, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 677 polygon from \
  -7.50489, -0 to \
  -7.45559, -0 to \
  -7.50489, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 678 polygon from \
  -7.55393, -0 to \
  -7.50464, -0 to \
  -7.55393, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 679 polygon from \
  -7.60298, -0 to \
  -7.55369, -0 to \
  -7.60298, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 680 polygon from \
  -7.65203, -0 to \
  -7.60274, -0 to \
  -7.65203, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 681 polygon from \
  -7.70108, -0 to \
  -7.65179, -0 to \
  -7.70108, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 682 polygon from \
  -7.75013, -0 to \
  -7.70084, -0 to \
  -7.75013, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 683 polygon from \
  -7.79918, -0 to \
  -7.74989, -0 to \
  -7.79918, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 684 polygon from \
  -7.84823, -0 to \
  -7.79894, -0 to \
  -7.84823, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 685 polygon from \
  -7.89727, -0 to \
  -7.84799, -0 to \
  -7.89727, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 686 polygon from \
  -7.94632, -0 to \
  -7.89704, -0 to \
  -7.94632, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 687 polygon from \
  -7.99537, -0 to \
  -7.94609, -0 to \
  -7.99537, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 688 polygon from \
  -8.04442, -0 to \
  -7.99514, -0 to \
  -8.04442, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 689 polygon from \
  -8.09347, -0 to \
  -8.04419, -0 to \
  -8.09347, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 690 polygon from \
  -8.14252, -0 to \
  -8.09324, -0 to \
  -8.14252, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 691 polygon from \
  -8.19157, -0 to \
  -8.14229, -0 to \
  -8.19157, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 692 polygon from \
  -8.24061, -0 to \
  -8.19134, -0 to \
  -8.24061, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 693 polygon from \
  -8.28966, -0 to \
  -8.24039, -0 to \
  -8.28966, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 694 polygon from \
  -8.33871, -0 to \
  -8.28944, -0 to \
  -8.33871, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 695 polygon from \
  -8.38776, -0 to \
  -8.33849, -0 to \
  -8.38776, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 696 polygon from \
  -8.43681, -0 to \
  -8.38754, -0 to \
  -8.43681, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 697 polygon from \
  -8.48586, -0 to \
  -8.43659, -0 to \
  -8.48586, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 698 polygon from \
  -8.53491, -0 to \
  -8.48564, -0 to \
  -8.53491, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 699 polygon from \
  -8.58396, -0 to \
  -8.53469, -0 to \
  -8.58396, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 700 polygon from \
  -8.633, -0 to \
  -8.58374, -0 to \
  -8.633, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 701 polygon from \
  -8.68205, -0 to \
  -8.63279, -0 to \
  -8.68205, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 702 polygon from \
  -8.7311, -0 to \
  -8.68184, -0 to \
  -8.7311, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 703 polygon from \
  -8.78015, -0 to \
  -8.73089, -0 to \
  -8.78015, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 704 polygon from \
  -8.8292, -0 to \
  -8.77994, -0 to \
  -8.8292, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 705 polygon from \
  -8.87825, -0 to \
  -8.82899, -0 to \
  -8.87825, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 706 polygon from \
  -8.9273, -0 to \
  -8.87804, -0 to \
  -8.9273, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 707 polygon from \
  -8.97635, -0 to \
  -8.92709, -0 to \
  -8.97635, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 708 polygon from \
  -9.0254, -0 to \
  -8.97614, -0 to \
  -9.0254, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 709 polygon from \
  -9.07444, -0 to \
  -9.02519, -0 to \
  -9.07444, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 710 polygon from \
  -9.12349, -0 to \
  -9.07424, -0 to \
  -9.12349, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 711 polygon from \
  -9.17254, -0 to \
  -9.12329, -0 to \
  -9.17254, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 712 polygon from \
  -9.22159, -0 to \
  -9.17234, -0 to \
  -9.22159, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 713 polygon from \
  -9.27064, -0 to \
  -9.22139, -0 to \
  -9.27064, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 714 polygon from \
  -9.31969, -0 to \
  -9.27044, -0 to \
  -9.31969, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 715 polygon from \
  -9.36874, -0 to \
  -9.31949, -0 to \
  -9.36874, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 716 polygon from \
  -9.41779, -0 to \
  -9.36854, -0 to \
  -9.41779, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 717 polygon from \
  -9.46684, -0 to \
  -9.41759, -0 to \
  -9.46684, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 718 polygon from \
  -9.51589, -0 to \
  -9.46664, -0 to \
  -9.51589, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 719 polygon from \
  -9.56493, -0 to \
  -9.51569, -0 to \
  -9.56493, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 720 polygon from \
  -9.61398, -0 to \
  -9.56474, -0 to \
  -9.61398, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 721 polygon from \
  -9.66303, -0 to \
  -9.61379, -0 to \
  -9.66303, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 722 polygon from \
  -9.71208, -0 to \
  -9.66284, -0 to \
  -9.71208, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 723 polygon from \
  -9.76113, -0 to \
  -9.71189, -0 to \
  -9.76113, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 724 polygon from \
  -9.81018, -0 to \
  -9.76094, -0 to \
  -9.81018, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 725 polygon from \
  -9.85923, -0 to \
  -9.80999, -0 to \
  -9.85923, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 726 polygon from \
  -9.90828, -0 to \
  -9.85904, -0 to \
  -9.90828, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 727 polygon from \
  -9.95733, -0 to \
  -9.90809, -0 to \
  -9.95733, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 728 polygon from \
  -10.0063, -0 to \
  -9.95714, -0 to \
  -10.0063, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 729 polygon from \
  -10.0554, -0 to \
  -10.0061, -0 to \
  -10.0554, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 730 polygon from \
  -10.1044, -0 to \
  -10.0552, -0 to \
  -10.1044, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 731 polygon from \
  -10.1535, -0 to \
  -10.1042, -0 to \
  -10.1535, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 732 polygon from \
  -10.2025, -0 to \
  -10.1533, -0 to \
  -10.2025, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 733 polygon from \
  -10.2516, -0 to \
  -10.2023, -0 to \
  -10.2516, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 734 polygon from \
  -10.3006, -0 to \
  -10.2514, -0 to \
  -10.3006, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 735 polygon from \
  -10.3497, -0 to \
  -10.3004, -0 to \
  -10.3497, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 736 polygon from \
  -10.3987, -0 to \
  -10.3495, -0 to \
  -10.3987, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 737 polygon from \
  -10.4478, -0 to \
  -10.3985, -0 to \
  -10.4478, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 738 polygon from \
  -10.4968, -0 to \
  -10.4476, -0 to \
  -10.4968, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 739 polygon from \
  -10.5459, -0 to \
  -10.4966, -0 to \
  -10.5459, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 740 polygon from \
  -10.5949, -0 to \
  -10.5457, -0 to \
  -10.5949, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 741 polygon from \
  -10.644, -0 to \
  -10.5947, -0 to \
  -10.644, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 742 polygon from \
  -10.693, -0 to \
  -10.6438, -0 to \
  -10.693, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 743 polygon from \
  -10.7421, -0 to \
  -10.6928, -0 to \
  -10.7421, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 744 polygon from \
  -10.7911, -0 to \
  -10.7419, -0 to \
  -10.7911, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 745 polygon from \
  -10.8402, -0 to \
  -10.7909, -0 to \
  -10.8402, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 746 polygon from \
  -10.8892, -0 to \
  -10.84, -0 to \
  -10.8892, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 747 polygon from \
  -10.9383, -0 to \
  -10.889, -0 to \
  -10.9383, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 748 polygon from \
  -10.9873, -0 to \
  -10.9381, -0 to \
  -10.9873, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 749 polygon from \
  -11.0364, -0 to \
  -10.9871, -0 to \
  -11.0364, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 750 polygon from \
  -11.0854, -0 to \
  -11.0362, -0 to \
  -11.0854, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 751 polygon from \
  -11.1345, -0 to \
  -11.0852, -0 to \
  -11.1345, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 752 polygon from \
  -11.1835, -0 to \
  -11.1343, -0 to \
  -11.1835, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 753 polygon from \
  -11.2326, -0 to \
  -11.1833, -0 to \
  -11.2326, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 754 polygon from \
  -11.2816, -0 to \
  -11.2324, -0 to \
  -11.2816, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 755 polygon from \
  -11.3307, -0 to \
  -11.2814, -0 to \
  -11.3307, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 756 polygon from \
  -11.3797, -0 to \
  -11.3305, -0 to \
  -11.3797, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 757 polygon from \
  -11.4288, -0 to \
  -11.3795, -0 to \
  -11.4288, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 758 polygon from \
  -11.4778, -0 to \
  -11.4286, -0 to \
  -11.4778, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 759 polygon from \
  -11.5269, -0 to \
  -11.4776, -0 to \
  -11.5269, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 760 polygon from \
  -11.5759, -0 to \
  -11.5267, -0 to \
  -11.5759, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 761 polygon from \
  -11.625, -0 to \
  -11.5757, -0 to \
  -11.625, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 762 polygon from \
  -11.674, -0 to \
  -11.6248, -0 to \
  -11.674, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 763 polygon from \
  -11.7231, -0 to \
  -11.6738, -0 to \
  -11.7231, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 764 polygon from \
  -11.7721, -0 to \
  -11.7229, -0 to \
  -11.7721, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 765 polygon from \
  -11.8212, -0 to \
  -11.7719, -0 to \
  -11.8212, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 766 polygon from \
  -11.8702, -0 to \
  -11.821, -0 to \
  -11.8702, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 767 polygon from \
  -11.9193, -0 to \
  -11.87, -0 to \
  -11.9193, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 768 polygon from \
  -11.9683, -0 to \
  -11.9191, -0 to \
  -11.9683, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 769 polygon from \
  -12.0174, -0 to \
  -11.9681, -0 to \
  -12.0174, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 770 polygon from \
  -12.0664, -0 to \
  -12.0172, -0 to \
  -12.0664, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 771 polygon from \
  -12.1154, -0 to \
  -12.0662, -0 to \
  -12.1154, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 772 polygon from \
  -12.1645, -0 to \
  -12.1153, -0 to \
  -12.1645, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 773 polygon from \
  -12.2135, -0 to \
  -12.1643, -0 to \
  -12.2135, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 774 polygon from \
  -12.2626, -0 to \
  -12.2134, -0 to \
  -12.2626, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 775 polygon from \
  -12.3116, -0 to \
  -12.2624, -0 to \
  -12.3116, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 776 polygon from \
  -12.3607, -0 to \
  -12.3115, -0 to \
  -12.3607, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 777 polygon from \
  -12.4097, -0 to \
  -12.3605, -0 to \
  -12.4097, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 778 polygon from \
  -12.4588, -0 to \
  -12.4096, -0 to \
  -12.4588, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 779 polygon from \
  -12.5078, -0 to \
  -12.4586, -0 to \
  -12.5078, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 780 polygon from \
  -12.5569, -0 to \
  -12.5077, -0 to \
  -12.5569, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 781 polygon from \
  -12.6059, -0 to \
  -12.5567, -0 to \
  -12.6059, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 782 polygon from \
  -12.655, -0 to \
  -12.6058, -0 to \
  -12.655, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 783 polygon from \
  -12.704, -0 to \
  -12.6548, -0 to \
  -12.704, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 784 polygon from \
  -12.7531, -0 to \
  -12.7039, -0 to \
  -12.7531, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 785 polygon from \
  -12.8021, -0 to \
  -12.7529, -0 to \
  -12.8021, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 786 polygon from \
  -12.8512, -0 to \
  -12.802, -0 to \
  -12.8512, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 787 polygon from \
  -12.9002, -0 to \
  -12.851, -0 to \
  -12.9002, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 788 polygon from \
  -12.9493, -0 to \
  -12.9001, -0 to \
  -12.9493, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 789 polygon from \
  -12.9983, -0 to \
  -12.9491, -0 to \
  -12.9983, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 790 polygon from \
  -13.0474, -0 to \
  -12.9982, -0 to \
  -13.0474, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 791 polygon from \
  -13.0964, -0 to \
  -13.0472, -0 to \
  -13.0964, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 792 polygon from \
  -13.1455, -0 to \
  -13.0963, -0 to \
  -13.1455, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 793 polygon from \
  -13.1945, -0 to \
  -13.1453, -0 to \
  -13.1945, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 794 polygon from \
  -13.2436, -0 to \
  -13.1944, -0 to \
  -13.2436, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 795 polygon from \
  -13.2926, -0 to \
  -13.2434, -0 to \
  -13.2926, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 796 polygon from \
  -13.3417, -0 to \
  -13.2925, -0 to \
  -13.3417, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 797 polygon from \
  -13.3907, -0 to \
  -13.3415, -0 to \
  -13.3907, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 798 polygon from \
  -13.4398, -0 to \
  -13.3906, -0 to \
  -13.4398, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 799 polygon from \
  -13.4888, -0 to \
  -13.4396, -0 to \
  -13.4888, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 800 polygon from \
  -13.5379, -0 to \
  -13.4887, -0 to \
  -13.5379, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 801 polygon from \
  -13.5869, -0 to \
  -13.5377, -0 to \
  -13.5869, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 802 polygon from \
  -13.636, -0 to \
  -13.5868, -0 to \
  -13.636, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 803 polygon from \
  -13.685, -0 to \
  -13.6358, -0 to \
  -13.685, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 804 polygon from \
  -13.7341, -0 to \
  -13.6849, -0 to \
  -13.7341, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 805 polygon from \
  -13.7831, -0 to \
  -13.7339, -0 to \
  -13.7831, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 806 polygon from \
  -13.8322, -0 to \
  -13.783, -0 to \
  -13.8322, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 807 polygon from \
  -13.8812, -0 to \
  -13.832, -0 to \
  -13.8812, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 808 polygon from \
  -13.9303, -0 to \
  -13.8811, -0 to \
  -13.9303, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 809 polygon from \
  -13.9793, -0 to \
  -13.9301, -0 to \
  -13.9793, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 810 polygon from \
  -14.0284, -0 to \
  -13.9792, -0 to \
  -14.0284, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 811 polygon from \
  -14.0774, -0 to \
  -14.0282, -0 to \
  -14.0774, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 812 polygon from \
  -14.1265, -0 to \
  -14.0773, -0 to \
  -14.1265, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 813 polygon from \
  -14.1755, -0 to \
  -14.1263, -0 to \
  -14.1755, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 814 polygon from \
  -14.2246, -0 to \
  -14.1754, -0 to \
  -14.2246, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 815 polygon from \
  -14.2736, -0 to \
  -14.2244, -0 to \
  -14.2736, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 816 polygon from \
  -14.3227, -0 to \
  -14.2735, -0 to \
  -14.3227, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 817 polygon from \
  -14.3717, -0 to \
  -14.3225, -0 to \
  -14.3717, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 818 polygon from \
  -14.4208, -0 to \
  -14.3716, -0 to \
  -14.4208, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 819 polygon from \
  -14.4698, -0 to \
  -14.4206, -0 to \
  -14.4698, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 820 polygon from \
  -14.5189, -0 to \
  -14.4697, -0 to \
  -14.5189, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 821 polygon from \
  -14.5679, -0 to \
  -14.5187, -0 to \
  -14.5679, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 822 polygon from \
  -14.617, -0 to \
  -14.5678, -0 to \
  -14.617, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 823 polygon from \
  -14.666, -0 to \
  -14.6168, -0 to \
  -14.666, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 824 polygon from \
  -14.7151, -0 to \
  -14.6659, -0 to \
  -14.7151, -0 front fs empty border lc rgb '#6165' lw 0.200001
plot [-17.2461:13.1261] [-1.01998:11.2199] NaN notitle 

