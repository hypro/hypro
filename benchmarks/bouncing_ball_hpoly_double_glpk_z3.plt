# settings
set term pdf
set output "bouncing_ball_hpoly_double_glpk_z3.pdf
set xtics autofreq
set ytics autofreq
set grid back
# axis settings
set xzeroaxis 
set zeroaxis 
set xtics axis 
set xrange [-9.23399e+35:7.26932e+35] 
set yzeroaxis 
set ytics axis 
set yrange [-1.04012e+31:1.14414e+32] 

# plotting sets
set object 1 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  0.000123034, 6.58992e+30 to \
  0.000123034, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 2 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -0.0979769, 6.58992e+30 to \
  -0.0979769, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 3 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -0.196076, 6.58992e+30 to \
  -0.196076, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 4 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -0.294176, 6.58992e+30 to \
  -0.294176, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 5 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -0.392276, 6.58992e+30 to \
  -0.392276, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 6 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -0.490376, 6.58992e+30 to \
  -0.490376, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 7 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -0.588476, 6.58992e+30 to \
  -0.588476, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 8 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -0.686576, 6.58992e+30 to \
  -0.686576, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 9 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -0.784676, 6.58992e+30 to \
  -0.784676, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 10 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -0.882776, 6.58992e+30 to \
  -0.882776, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 11 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -0.980876, 6.58992e+30 to \
  -0.980876, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 12 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -1.07897, 6.58992e+30 to \
  -1.07897, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 13 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -1.17707, 6.58992e+30 to \
  -1.17707, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 14 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -1.27517, 6.58992e+30 to \
  -1.27517, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 15 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -1.37327, 6.58992e+30 to \
  -1.37327, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 16 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -1.47137, 6.58992e+30 to \
  -1.47137, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 17 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -1.56947, 6.58992e+30 to \
  -1.56947, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 18 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -1.66757, 6.58992e+30 to \
  -1.66757, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 19 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -1.76567, 6.58992e+30 to \
  -1.76567, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 20 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -1.86377, 6.58992e+30 to \
  -1.86377, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 21 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -1.96187, 6.58992e+30 to \
  -1.96187, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 22 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -2.05997, 6.58992e+30 to \
  -2.05997, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 23 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -2.15807, 6.58992e+30 to \
  -2.15807, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 24 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -2.25617, 6.58992e+30 to \
  -2.25617, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 25 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -2.35427, 6.58992e+30 to \
  -2.35427, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 26 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -2.45237, 6.58992e+30 to \
  -2.45237, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 27 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -2.55047, 6.58992e+30 to \
  -2.55047, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 28 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -2.64857, 6.58992e+30 to \
  -2.64857, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 29 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -2.74667, 6.58992e+30 to \
  -2.74667, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 30 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -2.84477, 6.58992e+30 to \
  -2.84477, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 31 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -2.94287, 6.58992e+30 to \
  -2.94287, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 32 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -3.04097, 6.58992e+30 to \
  -3.04097, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 33 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -3.13907, 6.58992e+30 to \
  -3.13907, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 34 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -3.23717, 6.58992e+30 to \
  -3.23717, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 35 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -3.33527, 6.58992e+30 to \
  -3.33527, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 36 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -3.43337, 6.58992e+30 to \
  -3.43337, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 37 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -3.53147, 6.58992e+30 to \
  -3.53147, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 38 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -3.62957, 6.58992e+30 to \
  -3.62957, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 39 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -3.72767, 6.58992e+30 to \
  -3.72767, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 40 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -3.82577, 6.58992e+30 to \
  -3.82577, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 41 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -3.92387, 6.58992e+30 to \
  -3.92387, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 42 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -4.02197, 6.58992e+30 to \
  -4.02197, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 43 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -4.12007, 6.58992e+30 to \
  -4.12007, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 44 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -4.21817, 6.58992e+30 to \
  -4.21817, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 45 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -4.31627, 6.58992e+30 to \
  -4.31627, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 46 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -4.41437, 6.58992e+30 to \
  -4.41437, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 47 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -4.51247, 6.58992e+30 to \
  -4.51247, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 48 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -4.61057, 6.58992e+30 to \
  -4.61057, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 49 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -4.70867, 6.58992e+30 to \
  -4.70867, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 50 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -4.80677, 6.58992e+30 to \
  -4.80677, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 51 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -4.90487, 6.58992e+30 to \
  -4.90487, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 52 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.00297, 6.58992e+30 to \
  -5.00297, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 53 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.10107, 6.58992e+30 to \
  -5.10107, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 54 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.19917, 6.58992e+30 to \
  -5.19917, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 55 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.29727, 6.58992e+30 to \
  -5.29727, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 56 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.39537, 6.58992e+30 to \
  -5.39537, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 57 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.49347, 6.58992e+30 to \
  -5.49347, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 58 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.59157, 6.58992e+30 to \
  -5.59157, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 59 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.68967, 6.58992e+30 to \
  -5.68967, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 60 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.78777, 6.58992e+30 to \
  -5.78777, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 61 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.88587, 6.58992e+30 to \
  -5.88587, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 62 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -5.98397, 6.58992e+30 to \
  -5.98397, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 63 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -6.08207, 6.58992e+30 to \
  -6.08207, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 64 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -6.18017, 6.58992e+30 to \
  -6.18017, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 65 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -6.27827, 6.58992e+30 to \
  -6.27827, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 66 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -6.37637, 6.58992e+30 to \
  -6.37637, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 67 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -6.47447, 6.58992e+30 to \
  -6.47447, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 68 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -6.57257, 6.58992e+30 to \
  -6.57257, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 69 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -6.67067, 6.58992e+30 to \
  -6.67067, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 70 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -6.76877, 6.58992e+30 to \
  -6.76877, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 71 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -6.86687, 6.58992e+30 to \
  -6.86687, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 72 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -6.96497, 6.58992e+30 to \
  -6.96497, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 73 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -7.06307, 6.58992e+30 to \
  -7.06307, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 74 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -7.16117, 6.58992e+30 to \
  -7.16117, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 75 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -7.25927, 6.58992e+30 to \
  -7.25927, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 76 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -7.35737, 6.58992e+30 to \
  -7.35737, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 77 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -7.45547, 6.58992e+30 to \
  -7.45547, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 78 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -7.55357, 6.58992e+30 to \
  -7.55357, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 79 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -7.65167, 6.58992e+30 to \
  -7.65167, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 80 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -7.74977, 6.58992e+30 to \
  -7.74977, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 81 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -7.84787, 6.58992e+30 to \
  -7.84787, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 82 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -7.94597, 6.58992e+30 to \
  -7.94597, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 83 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -8.04407, 6.58992e+30 to \
  -8.04407, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 84 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -8.14217, 6.58992e+30 to \
  -8.14217, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 85 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -8.24027, 6.58992e+30 to \
  -8.24027, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 86 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -8.33837, 6.58992e+30 to \
  -8.33837, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 87 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -8.43647, 6.58992e+30 to \
  -8.43647, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 88 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -8.53457, 6.58992e+30 to \
  -8.53457, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 89 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -8.63267, 6.58992e+30 to \
  -8.63267, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 90 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -8.73077, 6.58992e+30 to \
  -8.73077, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 91 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -8.82887, 6.58992e+30 to \
  -8.82887, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 92 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -8.92697, 6.58992e+30 to \
  -8.92697, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 93 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -9.02507, 6.58992e+30 to \
  -9.02507, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 94 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -9.12317, 6.58992e+30 to \
  -9.12317, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 95 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -9.22127, 6.58992e+30 to \
  -9.22127, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 96 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -9.31937, 6.58992e+30 to \
  -9.31937, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 97 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -9.41747, 6.58992e+30 to \
  -9.41747, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 98 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -9.51557, 6.58992e+30 to \
  -9.51557, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 99 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -9.61367, 6.58992e+30 to \
  -9.61367, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 100 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -9.71177, 6.58992e+30 to \
  -9.71177, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 101 polygon from \
  -4.53914e+15, 6.58992e+30 to \
  -9.80987, 6.58992e+30 to \
  -9.80987, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 102 polygon from \
  -4.459e+15, 6.58992e+30 to \
  1.11476e+15, 6.58992e+30 to \
  -9.90797, -0 to \
  -4.53914e+15, -0 to \
  -4.459e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 103 polygon from \
  -4.41529e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -10.006, -0 to \
  -4.53914e+15, -0 to \
  -4.41529e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 104 polygon from \
  -4.37242e+15, 6.58992e+30 to \
  1.09311e+15, 6.58992e+30 to \
  -10.1041, -0 to \
  -4.53914e+15, -0 to \
  -4.37242e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 105 polygon from \
  -4.33038e+15, 6.58992e+30 to \
  1.0826e+15, 6.58992e+30 to \
  -10.2022, -0 to \
  -4.53914e+15, -0 to \
  -4.33038e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 106 polygon from \
  -4.28914e+15, 6.58992e+30 to \
  1.07229e+15, 6.58992e+30 to \
  -10.3003, -0 to \
  -4.53914e+15, -0 to \
  -4.28914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 107 polygon from \
  1.06217e+15, 6.58992e+30 to \
  -10.3984, -0 to \
  -4.53914e+15, -0 to \
  -5.31084e+15, 6.58992e+30 to \
  1.06217e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 108 polygon from \
  1.05225e+15, 6.58992e+30 to \
  -10.4965, -0 to \
  -4.53914e+15, -0 to \
  -5.26121e+15, 6.58992e+30 to \
  1.05225e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 109 polygon from \
  1.0425e+15, 6.58992e+30 to \
  -10.5946, -0 to \
  -4.53914e+15, -0 to \
  -5.21249e+15, 6.58992e+30 to \
  1.0425e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 110 polygon from \
  -0, 6.58992e+30 to \
  -10.6927, -0 to \
  -4.53914e+15, -0 to \
  -5.16467e+15, 6.58992e+30 to \
  -0, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 111 polygon from \
  -4.09418e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -10.7908, -0 to \
  -4.53914e+15, -0 to \
  -4.09418e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 112 polygon from \
  1.01433e+15, 6.58992e+30 to \
  -10.8889, -0 to \
  -4.53914e+15, -0 to \
  -5.07162e+15, 6.58992e+30 to \
  1.01433e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 113 polygon from \
  -4.02107e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -10.987, -0 to \
  -4.53914e+15, -0 to \
  -4.02107e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 114 polygon from \
  -3.98548e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -11.0851, -0 to \
  -4.53914e+15, -0 to \
  -3.98548e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 115 polygon from \
  -3.95052e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -11.1832, -0 to \
  -4.53914e+15, -0 to \
  -3.95052e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 116 polygon from \
  9.79044e+14, 6.58992e+30 to \
  -11.2813, -0 to \
  -4.53914e+15, -0 to \
  -4.89521e+15, 6.58992e+30 to \
  9.79044e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 117 polygon from \
  9.70604e+14, 6.58992e+30 to \
  -11.3794, -0 to \
  -4.53914e+15, -0 to \
  -4.85301e+15, 6.58992e+30 to \
  9.70604e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 118 polygon from \
  9.62308e+14, 6.58992e+30 to \
  -11.4775, -0 to \
  -4.53914e+15, -0 to \
  -4.81153e+15, 6.58992e+30 to \
  9.62308e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 119 polygon from \
  9.54153e+14, 6.58992e+30 to \
  -11.5756, -0 to \
  -4.53914e+15, -0 to \
  -4.77076e+15, 6.58992e+30 to \
  9.54153e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 120 polygon from \
  -3.78453e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -11.6737, -0 to \
  -4.53914e+15, -0 to \
  -3.78453e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 121 polygon from \
  9.3825e+14, 6.58992e+30 to \
  -11.7718, -0 to \
  -4.53914e+15, -0 to \
  -4.69124e+15, 6.58992e+30 to \
  9.3825e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 122 polygon from \
  -3.72198e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -11.8699, -0 to \
  -4.53914e+15, -0 to \
  -3.72198e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 123 polygon from \
  -0, 6.58992e+30 to \
  -11.968, -0 to \
  -4.53914e+15, -0 to \
  -5.53721e+15, 6.58992e+30 to \
  -0, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 124 polygon from \
  -0, 6.58992e+30 to \
  -12.0661, -0 to \
  -4.53914e+15, -0 to \
  -4.57682e+15, 6.58992e+30 to \
  -0, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 125 polygon from \
  -0, 6.58992e+30 to \
  -12.1642, -0 to \
  -4.53914e+15, -0 to \
  -4.53991e+15, 6.58992e+30 to \
  -0, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 126 polygon from \
  -4.50359e+15, 6.58992e+30 to \
  9.0072e+14, 6.58992e+30 to \
  -12.2623, -0 to \
  -4.53914e+15, -0 to \
  -4.50359e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 127 polygon from \
  8.93572e+14, 6.58992e+30 to \
  -12.3604, -0 to \
  -4.53914e+15, -0 to \
  -5.36142e+15, 6.58992e+30 to \
  8.93572e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 128 polygon from \
  -4.43267e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -12.4585, -0 to \
  -4.53914e+15, -0 to \
  -4.43267e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 129 polygon from \
  -4.39804e+15, 6.58992e+30 to \
  8.7961e+14, 6.58992e+30 to \
  -12.5566, -0 to \
  -4.53914e+15, -0 to \
  -4.39804e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 130 polygon from \
  -4.36395e+15, 6.58992e+30 to \
  8.72791e+14, 6.58992e+30 to \
  -12.6547, -0 to \
  -4.53914e+15, -0 to \
  -4.36395e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 131 polygon from \
  -4.33038e+15, 6.58992e+30 to \
  8.66077e+14, 6.58992e+30 to \
  -12.7528, -0 to \
  -4.53914e+15, -0 to \
  -4.33038e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 132 polygon from \
  -4.29732e+15, 6.58992e+30 to \
  8.59466e+14, 6.58992e+30 to \
  -12.8509, -0 to \
  -4.53914e+15, -0 to \
  -4.29732e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 133 polygon from \
  -4.26477e+15, 6.58992e+30 to \
  8.52955e+14, 6.58992e+30 to \
  -12.949, -0 to \
  -4.53914e+15, -0 to \
  -4.26477e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 134 polygon from \
  -4.2327e+15, 6.58992e+30 to \
  8.46542e+14, 6.58992e+30 to \
  -13.0471, -0 to \
  -4.53914e+15, -0 to \
  -4.2327e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 135 polygon from \
  -4.20111e+15, 6.58992e+30 to \
  8.40224e+14, 6.58992e+30 to \
  -13.1452, -0 to \
  -4.53914e+15, -0 to \
  -4.20111e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 136 polygon from \
  -4.16999e+15, 6.58992e+30 to \
  8.34e+14, 6.58992e+30 to \
  -13.2433, -0 to \
  -4.53914e+15, -0 to \
  -4.16999e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 137 polygon from \
  -4.13933e+15, 6.58992e+30 to \
  8.27868e+14, 6.58992e+30 to \
  -13.3414, -0 to \
  -4.53914e+15, -0 to \
  -4.13933e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 138 polygon from \
  8.21825e+14, 6.58992e+30 to \
  -13.4395, -0 to \
  -4.53914e+15, -0 to \
  -4.93094e+15, 6.58992e+30 to \
  8.21825e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 139 polygon from \
  -4.07934e+15, 6.58992e+30 to \
  8.1587e+14, 6.58992e+30 to \
  -13.5376, -0 to \
  -4.53914e+15, -0 to \
  -4.07934e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 140 polygon from \
  -4.04999e+15, 6.58992e+30 to \
  8.1e+14, 6.58992e+30 to \
  -13.6357, -0 to \
  -4.53914e+15, -0 to \
  -4.04999e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 141 polygon from \
  8.04215e+14, 6.58992e+30 to \
  -13.7338, -0 to \
  -4.53914e+15, -0 to \
  -4.82528e+15, 6.58992e+30 to \
  8.04215e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 142 polygon from \
  7.98511e+14, 6.58992e+30 to \
  -13.8319, -0 to \
  -4.53914e+15, -0 to \
  -4.79106e+15, 6.58992e+30 to \
  7.98511e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 143 polygon from \
  7.92888e+14, 6.58992e+30 to \
  -13.93, -0 to \
  -4.53914e+15, -0 to \
  -4.75732e+15, 6.58992e+30 to \
  7.92888e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 144 polygon from \
  7.87343e+14, 6.58992e+30 to \
  -14.0281, -0 to \
  -4.53914e+15, -0 to \
  -4.72405e+15, 6.58992e+30 to \
  7.87343e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 145 polygon from \
  7.81875e+14, 6.58992e+30 to \
  -14.1262, -0 to \
  -4.53914e+15, -0 to \
  -4.69124e+15, 6.58992e+30 to \
  7.81875e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 146 polygon from \
  7.76483e+14, 6.58992e+30 to \
  -14.2243, -0 to \
  -4.53914e+15, -0 to \
  -4.65889e+15, 6.58992e+30 to \
  7.76483e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 147 polygon from \
  7.71165e+14, 6.58992e+30 to \
  -14.3224, -0 to \
  -4.53914e+15, -0 to \
  -4.62698e+15, 6.58992e+30 to \
  7.71165e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 148 polygon from \
  7.65919e+14, 6.58992e+30 to \
  -14.4205, -0 to \
  -4.53914e+15, -0 to \
  -4.5955e+15, 6.58992e+30 to \
  7.65919e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 149 polygon from \
  -3.80371e+15, 6.58992e+30 to \
  7.60744e+14, 6.58992e+30 to \
  -14.5186, -0 to \
  -4.53914e+15, -0 to \
  -3.80371e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 150 polygon from \
  -4.53382e+15, 6.58992e+30 to \
  7.55638e+14, 6.58992e+30 to \
  -14.6167, -0 to \
  -4.53914e+15, -0 to \
  -4.53382e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 151 polygon from \
  -4.50359e+15, 6.58992e+30 to \
  7.506e+14, 6.58992e+30 to \
  -14.7148, -0 to \
  -4.53914e+15, -0 to \
  -4.50359e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 152 polygon from \
  -4.47377e+15, 6.58992e+30 to \
  7.4563e+14, 6.58992e+30 to \
  -14.8129, -0 to \
  -4.53914e+15, -0 to \
  -4.47377e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 153 polygon from \
  -4.44434e+15, 6.58992e+30 to \
  7.40724e+14, 6.58992e+30 to \
  -14.911, -0 to \
  -4.53914e+15, -0 to \
  -4.44434e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 154 polygon from \
  -4.41529e+15, 6.58992e+30 to \
  7.35883e+14, 6.58992e+30 to \
  -15.0091, -0 to \
  -4.53914e+15, -0 to \
  -4.41529e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 155 polygon from \
  -4.38662e+15, 6.58992e+30 to \
  7.31104e+14, 6.58992e+30 to \
  -15.1072, -0 to \
  -4.53914e+15, -0 to \
  -4.38662e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 156 polygon from \
  -4.35832e+15, 6.58992e+30 to \
  7.26388e+14, 6.58992e+30 to \
  -15.2053, -0 to \
  -4.53914e+15, -0 to \
  -4.35832e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 157 polygon from \
  -4.33038e+15, 6.58992e+30 to \
  7.21731e+14, 6.58992e+30 to \
  -15.3034, -0 to \
  -4.53914e+15, -0 to \
  -4.33038e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 158 polygon from \
  7.17134e+14, 6.58992e+30 to \
  -15.4015, -0 to \
  -4.53914e+15, -0 to \
  -5.01993e+15, 6.58992e+30 to \
  7.17134e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 159 polygon from \
  -4.27556e+15, 6.58992e+30 to \
  7.12595e+14, 6.58992e+30 to \
  -15.4996, -0 to \
  -4.53914e+15, -0 to \
  -4.27556e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 160 polygon from \
  -4.24867e+15, 6.58992e+30 to \
  7.08114e+14, 6.58992e+30 to \
  -15.5977, -0 to \
  -4.53914e+15, -0 to \
  -4.24867e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 161 polygon from \
  -4.22212e+15, 6.58992e+30 to \
  7.03688e+14, 6.58992e+30 to \
  -15.6958, -0 to \
  -4.53914e+15, -0 to \
  -4.22212e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 162 polygon from \
  -4.1959e+15, 6.58992e+30 to \
  6.99317e+14, 6.58992e+30 to \
  -15.7939, -0 to \
  -4.53914e+15, -0 to \
  -4.1959e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 163 polygon from \
  -4.16999e+15, 6.58992e+30 to \
  6.95e+14, 6.58992e+30 to \
  -15.892, -0 to \
  -4.53914e+15, -0 to \
  -4.16999e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 164 polygon from \
  -4.14441e+15, 6.58992e+30 to \
  6.90737e+14, 6.58992e+30 to \
  -15.9901, -0 to \
  -4.53914e+15, -0 to \
  -4.14441e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 165 polygon from \
  -4.11914e+15, 6.58992e+30 to \
  6.86525e+14, 6.58992e+30 to \
  -16.0882, -0 to \
  -4.53914e+15, -0 to \
  -4.11914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 166 polygon from \
  -4.09418e+15, 6.58992e+30 to \
  6.82364e+14, 6.58992e+30 to \
  -16.1863, -0 to \
  -4.53914e+15, -0 to \
  -4.09418e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 167 polygon from \
  -4.06951e+15, 6.58992e+30 to \
  6.78253e+14, 6.58992e+30 to \
  -16.2844, -0 to \
  -4.53914e+15, -0 to \
  -4.06951e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 168 polygon from \
  6.74192e+14, 6.58992e+30 to \
  -16.3825, -0 to \
  -4.53914e+15, -0 to \
  -4.71934e+15, 6.58992e+30 to \
  6.74192e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 169 polygon from \
  -4.02107e+15, 6.58992e+30 to \
  6.70179e+14, 6.58992e+30 to \
  -16.4806, -0 to \
  -4.53914e+15, -0 to \
  -4.02107e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 170 polygon from \
  6.66213e+14, 6.58992e+30 to \
  -16.5787, -0 to \
  -4.53914e+15, -0 to \
  -4.66349e+15, 6.58992e+30 to \
  6.66213e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 171 polygon from \
  -3.97376e+15, 6.58992e+30 to \
  6.62295e+14, 6.58992e+30 to \
  -16.6768, -0 to \
  -4.53914e+15, -0 to \
  -3.97376e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 172 polygon from \
  -3.95052e+15, 6.58992e+30 to \
  6.58421e+14, 6.58992e+30 to \
  -16.7749, -0 to \
  -4.53914e+15, -0 to \
  -3.95052e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 173 polygon from \
  6.54593e+14, 6.58992e+30 to \
  -16.873, -0 to \
  -4.53914e+15, -0 to \
  -4.58215e+15, 6.58992e+30 to \
  6.54593e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 174 polygon from \
  6.5081e+14, 6.58992e+30 to \
  -16.9711, -0 to \
  -4.53914e+15, -0 to \
  -4.55566e+15, 6.58992e+30 to \
  6.5081e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 175 polygon from \
  -4.52948e+15, 6.58992e+30 to \
  6.47069e+14, 6.58992e+30 to \
  -17.0692, -0 to \
  -4.53914e+15, -0 to \
  -4.52948e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 176 polygon from \
  -4.50359e+15, 6.58992e+30 to \
  6.43372e+14, 6.58992e+30 to \
  -17.1673, -0 to \
  -4.53914e+15, -0 to \
  -4.50359e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 177 polygon from \
  -4.47801e+15, 6.58992e+30 to \
  1.27944e+15, 6.58992e+30 to \
  -17.2654, -0 to \
  -4.53914e+15, -0 to \
  -4.47801e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 178 polygon from \
  -4.45271e+15, 6.58992e+30 to \
  6.36102e+14, 6.58992e+30 to \
  -17.3635, -0 to \
  -4.53914e+15, -0 to \
  -4.45271e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 179 polygon from \
  -4.42769e+15, 6.58992e+30 to \
  6.32529e+14, 6.58992e+30 to \
  -17.4616, -0 to \
  -4.53914e+15, -0 to \
  -4.42769e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 180 polygon from \
  -4.40296e+15, 6.58992e+30 to \
  6.28995e+14, 6.58992e+30 to \
  -17.5597, -0 to \
  -4.53914e+15, -0 to \
  -4.40296e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 181 polygon from \
  -4.37849e+15, 6.58992e+30 to \
  6.255e+14, 6.58992e+30 to \
  -17.6578, -0 to \
  -4.53914e+15, -0 to \
  -4.37849e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 182 polygon from \
  -4.3543e+15, 6.58992e+30 to \
  6.22045e+14, 6.58992e+30 to \
  -17.7559, -0 to \
  -4.53914e+15, -0 to \
  -4.3543e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 183 polygon from \
  -4.33038e+15, 6.58992e+30 to \
  6.18627e+14, 6.58992e+30 to \
  -17.854, -0 to \
  -4.53914e+15, -0 to \
  -4.33038e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 184 polygon from \
  6.15246e+14, 6.58992e+30 to \
  -17.9521, -0 to \
  -4.53914e+15, -0 to \
  -4.92196e+15, 6.58992e+30 to \
  6.15246e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 185 polygon from \
  6.11903e+14, 6.58992e+30 to \
  -18.0502, -0 to \
  -4.53914e+15, -0 to \
  -4.89521e+15, 6.58992e+30 to \
  6.11903e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 186 polygon from \
  -4.26016e+15, 6.58992e+30 to \
  1.21719e+15, 6.58992e+30 to \
  -18.1483, -0 to \
  -4.53914e+15, -0 to \
  -4.26016e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 187 polygon from \
  -4.23725e+15, 6.58992e+30 to \
  6.05323e+14, 6.58992e+30 to \
  -18.2464, -0 to \
  -4.53914e+15, -0 to \
  -4.23725e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 188 polygon from \
  -4.21459e+15, 6.58992e+30 to \
  6.02086e+14, 6.58992e+30 to \
  -18.3445, -0 to \
  -4.53914e+15, -0 to \
  -4.21459e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 189 polygon from \
  1.19777e+15, 6.58992e+30 to \
  -18.4426, -0 to \
  -4.53914e+15, -0 to \
  -4.79106e+15, 6.58992e+30 to \
  1.19777e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 190 polygon from \
  5.95715e+14, 6.58992e+30 to \
  -18.5407, -0 to \
  -4.53914e+15, -0 to \
  -4.76571e+15, 6.58992e+30 to \
  5.95715e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 191 polygon from \
  5.92579e+14, 6.58992e+30 to \
  -18.6388, -0 to \
  -4.53914e+15, -0 to \
  -4.74063e+15, 6.58992e+30 to \
  5.92579e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 192 polygon from \
  -4.12633e+15, 6.58992e+30 to \
  5.89477e+14, 6.58992e+30 to \
  -18.7369, -0 to \
  -4.53914e+15, -0 to \
  -4.12633e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 193 polygon from \
  5.86407e+14, 6.58992e+30 to \
  -18.835, -0 to \
  -4.53914e+15, -0 to \
  -4.69124e+15, 6.58992e+30 to \
  5.86407e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 194 polygon from \
  1.16674e+15, 6.58992e+30 to \
  -18.9331, -0 to \
  -4.53914e+15, -0 to \
  -4.66694e+15, 6.58992e+30 to \
  1.16674e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 195 polygon from \
  1.16073e+15, 6.58992e+30 to \
  -19.0312, -0 to \
  -4.53914e+15, -0 to \
  -4.64288e+15, 6.58992e+30 to \
  1.16073e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 196 polygon from \
  5.77385e+14, 6.58992e+30 to \
  -19.1293, -0 to \
  -4.53914e+15, -0 to \
  -4.61907e+15, 6.58992e+30 to \
  5.77385e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 197 polygon from \
  5.74439e+14, 6.58992e+30 to \
  -19.2274, -0 to \
  -4.53914e+15, -0 to \
  -4.5955e+15, 6.58992e+30 to \
  5.74439e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 198 polygon from \
  1.14305e+15, 6.58992e+30 to \
  -19.3255, -0 to \
  -4.53914e+15, -0 to \
  -4.57218e+15, 6.58992e+30 to \
  1.14305e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 199 polygon from \
  1.13728e+15, 6.58992e+30 to \
  -19.4236, -0 to \
  -4.53914e+15, -0 to \
  -4.54909e+15, 6.58992e+30 to \
  1.13728e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 200 polygon from \
  -3.96045e+15, 6.58992e+30 to \
  5.65779e+14, 6.58992e+30 to \
  -19.5217, -0 to \
  -4.53914e+15, -0 to \
  -3.96045e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 201 polygon from \
  -4.50359e+15, 6.58992e+30 to \
  5.6295e+14, 6.58992e+30 to \
  -19.6198, -0 to \
  -4.53914e+15, -0 to \
  -4.50359e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 202 polygon from \
  -4.48119e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -19.7179, -0 to \
  -4.53914e+15, -0 to \
  -4.48119e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 203 polygon from \
  -4.459e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -19.816, -0 to \
  -4.53914e+15, -0 to \
  -4.459e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 204 polygon from \
  -4.43704e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -19.9141, -0 to \
  -4.53914e+15, -0 to \
  -4.43704e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 205 polygon from \
  -4.41529e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -20.0122, -0 to \
  -4.53914e+15, -0 to \
  -4.41529e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 206 polygon from \
  -4.39375e+15, 6.58992e+30 to \
  5.4922e+14, 6.58992e+30 to \
  -20.1103, -0 to \
  -4.53914e+15, -0 to \
  -4.39375e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 207 polygon from \
  -4.37242e+15, 6.58992e+30 to \
  5.46554e+14, 6.58992e+30 to \
  -20.2084, -0 to \
  -4.53914e+15, -0 to \
  -4.37242e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 208 polygon from \
  5.43913e+14, 6.58992e+30 to \
  -20.3065, -0 to \
  -4.53914e+15, -0 to \
  -4.89521e+15, 6.58992e+30 to \
  5.43913e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 209 polygon from \
  5.41299e+14, 6.58992e+30 to \
  -20.4046, -0 to \
  -4.53914e+15, -0 to \
  -4.87168e+15, 6.58992e+30 to \
  5.41299e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 210 polygon from \
  -4.30966e+15, 6.58992e+30 to \
  5.38709e+14, 6.58992e+30 to \
  -20.5027, -0 to \
  -4.53914e+15, -0 to \
  -4.30966e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 211 polygon from \
  -4.28914e+15, 6.58992e+30 to \
  5.36143e+14, 6.58992e+30 to \
  -20.6008, -0 to \
  -4.53914e+15, -0 to \
  -4.28914e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 212 polygon from \
  5.33602e+14, 6.58992e+30 to \
  -20.6989, -0 to \
  -4.53914e+15, -0 to \
  -4.80241e+15, 6.58992e+30 to \
  5.33602e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 213 polygon from \
  -4.24867e+15, 6.58992e+30 to \
  5.31085e+14, 6.58992e+30 to \
  -20.797, -0 to \
  -4.53914e+15, -0 to \
  -4.24867e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 214 polygon from \
  5.28592e+14, 6.58992e+30 to \
  -20.8951, -0 to \
  -4.53914e+15, -0 to \
  -4.75732e+15, 6.58992e+30 to \
  5.28592e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 215 polygon from \
  5.26122e+14, 6.58992e+30 to \
  -20.9932, -0 to \
  -4.53914e+15, -0 to \
  -4.73509e+15, 6.58992e+30 to \
  5.26122e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 216 polygon from \
  5.23675e+14, 6.58992e+30 to \
  -21.0913, -0 to \
  -4.53914e+15, -0 to \
  -4.71306e+15, 6.58992e+30 to \
  5.23675e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 217 polygon from \
  5.2125e+14, 6.58992e+30 to \
  -21.1894, -0 to \
  -4.53914e+15, -0 to \
  -4.69124e+15, 6.58992e+30 to \
  5.2125e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 218 polygon from \
  -4.15078e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -21.2875, -0 to \
  -4.53914e+15, -0 to \
  -4.15078e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 219 polygon from \
  5.16468e+14, 6.58992e+30 to \
  -21.3856, -0 to \
  -4.53914e+15, -0 to \
  -4.64821e+15, 6.58992e+30 to \
  5.16468e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 220 polygon from \
  5.1411e+14, 6.58992e+30 to \
  -21.4837, -0 to \
  -4.53914e+15, -0 to \
  -4.62698e+15, 6.58992e+30 to \
  5.1411e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 221 polygon from \
  5.11773e+14, 6.58992e+30 to \
  -21.5818, -0 to \
  -4.53914e+15, -0 to \
  -4.60595e+15, 6.58992e+30 to \
  5.11773e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 222 polygon from \
  -0, 6.58992e+30 to \
  -21.6799, -0 to \
  -4.53914e+15, -0 to \
  -4.58511e+15, 6.58992e+30 to \
  -0, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 223 polygon from \
  -0, 6.58992e+30 to \
  -21.778, -0 to \
  -4.53914e+15, -0 to \
  -4.56445e+15, 6.58992e+30 to \
  -0, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 224 polygon from \
  5.04888e+14, 6.58992e+30 to \
  -21.8761, -0 to \
  -4.53914e+15, -0 to \
  -4.54399e+15, 6.58992e+30 to \
  5.04888e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 225 polygon from \
  -0, 6.58992e+30 to \
  -21.9742, -0 to \
  -4.53914e+15, -0 to \
  -5.02633e+15, 6.58992e+30 to \
  -0, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 226 polygon from \
  -4.50359e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -22.0723, -0 to \
  -4.53914e+15, -0 to \
  -4.50359e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 227 polygon from \
  -4.48367e+15, 6.58992e+30 to \
  4.98186e+14, 6.58992e+30 to \
  -22.1704, -0 to \
  -4.53914e+15, -0 to \
  -4.48367e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 228 polygon from \
  -4.46392e+15, 6.58992e+30 to \
  4.95992e+14, 6.58992e+30 to \
  -22.2685, -0 to \
  -4.53914e+15, -0 to \
  -4.46392e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 229 polygon from \
  -4.44434e+15, 6.58992e+30 to \
  4.93816e+14, 6.58992e+30 to \
  -22.3666, -0 to \
  -4.53914e+15, -0 to \
  -4.44434e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 230 polygon from \
  -4.42493e+15, 6.58992e+30 to \
  4.9166e+14, 6.58992e+30 to \
  -22.4647, -0 to \
  -4.53914e+15, -0 to \
  -4.42493e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 231 polygon from \
  -4.40569e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -22.5628, -0 to \
  -4.53914e+15, -0 to \
  -4.40569e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 232 polygon from \
  4.87403e+14, 6.58992e+30 to \
  -22.6609, -0 to \
  -4.53914e+15, -0 to \
  -4.87402e+15, 6.58992e+30 to \
  4.87403e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 233 polygon from \
  -4.36771e+15, 6.58992e+30 to \
  4.85302e+14, 6.58992e+30 to \
  -22.759, -0 to \
  -4.53914e+15, -0 to \
  -4.36771e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 234 polygon from \
  -4.34896e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -22.8571, -0 to \
  -4.53914e+15, -0 to \
  -4.34896e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 235 polygon from \
  -4.33038e+15, 6.58992e+30 to \
  4.81154e+14, 6.58992e+30 to \
  -22.9552, -0 to \
  -4.53914e+15, -0 to \
  -4.33038e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 236 polygon from \
  -4.31195e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -23.0533, -0 to \
  -4.53914e+15, -0 to \
  -4.31195e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 237 polygon from \
  4.77077e+14, 6.58992e+30 to \
  -23.1514, -0 to \
  -4.53914e+15, -0 to \
  -4.77076e+15, 6.58992e+30 to \
  4.77077e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 238 polygon from \
  4.75064e+14, 6.58992e+30 to \
  -23.2495, -0 to \
  -4.53914e+15, -0 to \
  -4.75063e+15, 6.58992e+30 to \
  4.75064e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 239 polygon from \
  4.73068e+14, 6.58992e+30 to \
  -23.3476, -0 to \
  -4.53914e+15, -0 to \
  -4.73067e+15, 6.58992e+30 to \
  4.73068e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 240 polygon from \
  -4.23979e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -23.4457, -0 to \
  -4.53914e+15, -0 to \
  -4.23979e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 241 polygon from \
  4.69125e+14, 6.58992e+30 to \
  -23.5438, -0 to \
  -4.53914e+15, -0 to \
  -4.69124e+15, 6.58992e+30 to \
  4.69125e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 242 polygon from \
  4.67179e+14, 6.58992e+30 to \
  -23.6419, -0 to \
  -4.53914e+15, -0 to \
  -4.67178e+15, 6.58992e+30 to \
  4.67179e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 243 polygon from \
  -4.18723e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -23.74, -0 to \
  -4.53914e+15, -0 to \
  -4.18723e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 244 polygon from \
  4.63334e+14, 6.58992e+30 to \
  -23.8381, -0 to \
  -4.53914e+15, -0 to \
  -4.63333e+15, 6.58992e+30 to \
  4.63334e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 245 polygon from \
  4.61435e+14, 6.58992e+30 to \
  -23.9362, -0 to \
  -4.53914e+15, -0 to \
  -4.61434e+15, 6.58992e+30 to \
  4.61435e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 246 polygon from \
  -0, 6.58992e+30 to \
  -24.0343, -0 to \
  -4.53914e+15, -0 to \
  -4.5955e+15, 6.58992e+30 to \
  -0, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 247 polygon from \
  4.57683e+14, 6.58992e+30 to \
  -24.1324, -0 to \
  -4.53914e+15, -0 to \
  -4.57682e+15, 6.58992e+30 to \
  4.57683e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 248 polygon from \
  4.5583e+14, 6.58992e+30 to \
  -24.2305, -0 to \
  -4.53914e+15, -0 to \
  -4.55829e+15, 6.58992e+30 to \
  4.5583e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 249 polygon from \
  4.53992e+14, 6.58992e+30 to \
  -24.3286, -0 to \
  -4.53914e+15, -0 to \
  -4.53991e+15, 6.58992e+30 to \
  4.53992e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 250 polygon from \
  -4.52168e+15, 6.58992e+30 to \
  4.52169e+14, 6.58992e+30 to \
  -24.4267, -0 to \
  -4.53914e+15, -0 to \
  -4.52168e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 251 polygon from \
  -4.50359e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -24.5248, -0 to \
  -4.53914e+15, -0 to \
  -4.50359e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 252 polygon from \
  -4.48565e+15, 6.58992e+30 to \
  4.48566e+14, 6.58992e+30 to \
  -24.6229, -0 to \
  -4.53914e+15, -0 to \
  -4.48565e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 253 polygon from \
  4.46786e+14, 6.58992e+30 to \
  -24.721, -0 to \
  -4.53914e+15, -0 to \
  -4.91464e+15, 6.58992e+30 to \
  4.46786e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 254 polygon from \
  4.4502e+14, 6.58992e+30 to \
  -24.8191, -0 to \
  -4.53914e+15, -0 to \
  -4.89521e+15, 6.58992e+30 to \
  4.4502e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 255 polygon from \
  -4.43267e+15, 6.58992e+30 to \
  4.43268e+14, 6.58992e+30 to \
  -24.9172, -0 to \
  -4.53914e+15, -0 to \
  -4.43267e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 256 polygon from \
  4.4153e+14, 6.58992e+30 to \
  -25.0153, -0 to \
  -4.53914e+15, -0 to \
  -4.85682e+15, 6.58992e+30 to \
  4.4153e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 257 polygon from \
  4.39805e+14, 6.58992e+30 to \
  -25.1134, -0 to \
  -4.53914e+15, -0 to \
  -4.83785e+15, 6.58992e+30 to \
  4.39805e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 258 polygon from \
  -4.38093e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -25.2115, -0 to \
  -4.53914e+15, -0 to \
  -4.38093e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 259 polygon from \
  -4.36395e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -25.3096, -0 to \
  -4.53914e+15, -0 to \
  -4.36395e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 260 polygon from \
  -4.3471e+15, 6.58992e+30 to \
  -0, 6.58992e+30 to \
  -25.4077, -0 to \
  -4.53914e+15, -0 to \
  -4.3471e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 261 polygon from \
  -4.33038e+15, 6.58992e+30 to \
  4.33039e+14, 6.58992e+30 to \
  -25.5058, -0 to \
  -4.53914e+15, -0 to \
  -4.33038e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 262 polygon from \
  -4.31379e+15, 6.58992e+30 to \
  4.3138e+14, 6.58992e+30 to \
  -25.6039, -0 to \
  -4.53914e+15, -0 to \
  -4.31379e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 263 polygon from \
  -4.29732e+15, 6.58992e+30 to \
  4.29733e+14, 6.58992e+30 to \
  -25.702, -0 to \
  -4.53914e+15, -0 to \
  -4.29732e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 264 polygon from \
  -4.28098e+15, 6.58992e+30 to \
  4.28099e+14, 6.58992e+30 to \
  -25.8001, -0 to \
  -4.53914e+15, -0 to \
  -4.28098e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 265 polygon from \
  4.26478e+14, 6.58992e+30 to \
  -25.8982, -0 to \
  -4.53914e+15, -0 to \
  -4.69124e+15, 6.58992e+30 to \
  4.26478e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 266 polygon from \
  4.24868e+14, 6.58992e+30 to \
  -25.9963, -0 to \
  -4.53914e+15, -0 to \
  -4.67354e+15, 6.58992e+30 to \
  4.24868e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 267 polygon from \
  -4.2327e+15, 6.58992e+30 to \
  4.23271e+14, 6.58992e+30 to \
  -26.0944, -0 to \
  -4.53914e+15, -0 to \
  -4.2327e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 268 polygon from \
  -4.21685e+15, 6.58992e+30 to \
  4.21686e+14, 6.58992e+30 to \
  -26.1925, -0 to \
  -4.53914e+15, -0 to \
  -4.21685e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 269 polygon from \
  4.20112e+14, 6.58992e+30 to \
  -26.2906, -0 to \
  -4.53914e+15, -0 to \
  -4.62123e+15, 6.58992e+30 to \
  4.20112e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 270 polygon from \
  -4.1855e+15, 6.58992e+30 to \
  4.18551e+14, 6.58992e+30 to \
  -26.3887, -0 to \
  -4.53914e+15, -0 to \
  -4.1855e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 271 polygon from \
  -4.16999e+15, 6.58992e+30 to \
  4.17e+14, 6.58992e+30 to \
  -26.4868, -0 to \
  -4.53914e+15, -0 to \
  -4.16999e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 272 polygon from \
  4.15462e+14, 6.58992e+30 to \
  -26.5849, -0 to \
  -4.53914e+15, -0 to \
  -4.57007e+15, 6.58992e+30 to \
  4.15462e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 273 polygon from \
  -4.13933e+15, 6.58992e+30 to \
  4.13934e+14, 6.58992e+30 to \
  -26.683, -0 to \
  -4.53914e+15, -0 to \
  -4.13933e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 274 polygon from \
  -4.53659e+15, 6.58992e+30 to \
  4.12418e+14, 6.58992e+30 to \
  -26.7811, -0 to \
  -4.53914e+15, -0 to \
  -4.53659e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 275 polygon from \
  -4.52003e+15, 6.58992e+30 to \
  4.10913e+14, 6.58992e+30 to \
  -26.8792, -0 to \
  -4.53914e+15, -0 to \
  -4.52003e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 276 polygon from \
  -4.50359e+15, 6.58992e+30 to \
  4.09419e+14, 6.58992e+30 to \
  -26.9773, -0 to \
  -4.53914e+15, -0 to \
  -4.50359e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 277 polygon from \
  -4.48728e+15, 6.58992e+30 to \
  4.07935e+14, 6.58992e+30 to \
  -27.0754, -0 to \
  -4.53914e+15, -0 to \
  -4.48728e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 278 polygon from \
  -4.47108e+15, 6.58992e+30 to \
  4.06463e+14, 6.58992e+30 to \
  -27.1735, -0 to \
  -4.53914e+15, -0 to \
  -4.47108e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 279 polygon from \
  -4.45499e+15, 6.58992e+30 to \
  4.05e+14, 6.58992e+30 to \
  -27.2716, -0 to \
  -4.53914e+15, -0 to \
  -4.45499e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 280 polygon from \
  -4.43903e+15, 6.58992e+30 to \
  4.03549e+14, 6.58992e+30 to \
  -27.3697, -0 to \
  -4.53914e+15, -0 to \
  -4.43903e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 281 polygon from \
  -4.42317e+15, 6.58992e+30 to \
  4.02108e+14, 6.58992e+30 to \
  -27.4678, -0 to \
  -4.53914e+15, -0 to \
  -4.42317e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 282 polygon from \
  -4.40743e+15, 6.58992e+30 to \
  4.00677e+14, 6.58992e+30 to \
  -27.5659, -0 to \
  -4.53914e+15, -0 to \
  -4.40743e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 283 polygon from \
  -4.3918e+15, 6.58992e+30 to \
  3.99256e+14, 6.58992e+30 to \
  -27.664, -0 to \
  -4.53914e+15, -0 to \
  -4.3918e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 284 polygon from \
  -4.37628e+15, 6.58992e+30 to \
  3.97845e+14, 6.58992e+30 to \
  -27.7621, -0 to \
  -4.53914e+15, -0 to \
  -4.37628e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 285 polygon from \
  -4.36087e+15, 6.58992e+30 to \
  3.96444e+14, 6.58992e+30 to \
  -27.8602, -0 to \
  -4.53914e+15, -0 to \
  -4.36087e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 286 polygon from \
  -4.34557e+15, 6.58992e+30 to \
  3.95053e+14, 6.58992e+30 to \
  -27.9583, -0 to \
  -4.53914e+15, -0 to \
  -4.34557e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 287 polygon from \
  -4.33038e+15, 6.58992e+30 to \
  3.93672e+14, 6.58992e+30 to \
  -28.0564, -0 to \
  -4.53914e+15, -0 to \
  -4.33038e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 288 polygon from \
  -4.31529e+15, 6.58992e+30 to \
  3.923e+14, 6.58992e+30 to \
  -28.1545, -0 to \
  -4.53914e+15, -0 to \
  -4.31529e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 289 polygon from \
  3.90938e+14, 6.58992e+30 to \
  -28.2526, -0 to \
  -4.53914e+15, -0 to \
  -4.69124e+15, 6.58992e+30 to \
  3.90938e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 290 polygon from \
  -4.28543e+15, 6.58992e+30 to \
  3.89585e+14, 6.58992e+30 to \
  -28.3507, -0 to \
  -4.53914e+15, -0 to \
  -4.28543e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 291 polygon from \
  -4.27065e+15, 6.58992e+30 to \
  3.88242e+14, 6.58992e+30 to \
  -28.4488, -0 to \
  -4.53914e+15, -0 to \
  -4.27065e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 292 polygon from \
  3.86908e+14, 6.58992e+30 to \
  -28.5469, -0 to \
  -4.53914e+15, -0 to \
  -4.64288e+15, 6.58992e+30 to \
  3.86908e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 293 polygon from \
  -4.2414e+15, 6.58992e+30 to \
  3.85583e+14, 6.58992e+30 to \
  -28.645, -0 to \
  -4.53914e+15, -0 to \
  -4.2414e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 294 polygon from \
  -4.22692e+15, 6.58992e+30 to \
  3.84267e+14, 6.58992e+30 to \
  -28.7431, -0 to \
  -4.53914e+15, -0 to \
  -4.22692e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 295 polygon from \
  3.8296e+14, 6.58992e+30 to \
  -28.8412, -0 to \
  -4.53914e+15, -0 to \
  -4.5955e+15, 6.58992e+30 to \
  3.8296e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 296 polygon from \
  3.81661e+14, 6.58992e+30 to \
  -28.9393, -0 to \
  -4.53914e+15, -0 to \
  -4.57993e+15, 6.58992e+30 to \
  3.81661e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 297 polygon from \
  3.80372e+14, 6.58992e+30 to \
  -29.0374, -0 to \
  -4.53914e+15, -0 to \
  -4.56445e+15, 6.58992e+30 to \
  3.80372e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 298 polygon from \
  3.79091e+14, 6.58992e+30 to \
  -29.1355, -0 to \
  -4.53914e+15, -0 to \
  -4.54909e+15, 6.58992e+30 to \
  3.79091e+14, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 299 polygon from \
  -4.53382e+15, 6.58992e+30 to \
  3.77819e+14, 6.58992e+30 to \
  -29.2336, -0 to \
  -4.53914e+15, -0 to \
  -4.53382e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 300 polygon from \
  -4.51866e+15, 6.58992e+30 to \
  3.76556e+14, 6.58992e+30 to \
  -29.3317, -0 to \
  -4.53914e+15, -0 to \
  -4.51866e+15, 6.58992e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 301 polygon from \
  -0.000123033, 0.00176759 to \
  3.40436e+15, 0.00176759 to \
  3.40436e+15, 0 to \
  -0.000123033, -0 to \
  -0.000123033, 0.00176759 front fs empty border lc rgb '#6165' lw 0.200001
set object 302 polygon from \
  -0.098223, 0.00127586 to \
  -0.04905, -0 to \
  -0.098223, -0 to \
  -0.098223, 0.00127586 front fs empty border lc rgb '#6165' lw 0.200001
set object 303 polygon from \
  -0.186479, -0 to \
  -0.0980999, -0 to \
  -0.186479, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 304 polygon from \
  -0.206069, -0 to \
  -0.147149, -0 to \
  -0.206069, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 305 polygon from \
  -0.240389, -0 to \
  -0.196199, -0 to \
  -0.240389, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 306 polygon from \
  -0.280601, -0 to \
  -0.245249, -0 to \
  -0.280601, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 307 polygon from \
  -0.323759, -0 to \
  -0.294299, -0 to \
  -0.323759, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 308 polygon from \
  -0.368601, -0 to \
  -0.343349, -0 to \
  -0.368601, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 309 polygon from \
  -0.414494, -0 to \
  -0.392399, -0 to \
  -0.414494, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 310 polygon from \
  -0.461089, -0 to \
  -0.441449, -0 to \
  -0.461089, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 311 polygon from \
  -0.508175, -0 to \
  -0.490499, -0 to \
  -0.508175, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 312 polygon from \
  -0.555618, -0 to \
  -0.539549, -0 to \
  -0.555618, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 313 polygon from \
  -0.603329, -0 to \
  -0.588599, -0 to \
  -0.603329, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 314 polygon from \
  -0.651246, -0 to \
  -0.637649, -0 to \
  -0.651246, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 315 polygon from \
  -0.699325, -0 to \
  -0.686699, -0 to \
  -0.699325, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 316 polygon from \
  3.74612e+12, 5.61917e+11 to \
  -0.735749, -0 to \
  -0.747533, -0 to \
  3.74612e+12, 5.61917e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 317 polygon from \
  3.03257e+12, 4.85211e+11 to \
  -0.784799, -0 to \
  -0.795847, -0 to \
  3.03257e+12, 4.85211e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 318 polygon from \
  2.6535e+12, 4.51095e+11 to \
  -0.833849, -0 to \
  -0.844247, -0 to \
  2.6535e+12, 4.51095e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 319 polygon from \
  2.35867e+12, 4.2456e+11 to \
  -0.882899, -0 to \
  -0.892719, -0 to \
  2.35867e+12, 4.2456e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 320 polygon from \
  2.05432e+12, 3.90321e+11 to \
  -0.931949, -0 to \
  -0.941253, -0 to \
  2.05432e+12, 3.90321e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 321 polygon from \
  1.87306e+12, 3.74612e+11 to \
  -0.980999, -0 to \
  -0.989837, -0 to \
  1.87306e+12, 3.74612e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 322 polygon from \
  1.6759e+12, 3.51938e+11 to \
  -1.03004, -0 to \
  -1.03846, -0 to \
  1.6759e+12, 3.51938e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 323 polygon from \
  1.55327e+12, 3.41719e+11 to \
  -1.07909, -0 to \
  -1.08713, -0 to \
  1.55327e+12, 3.41719e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 324 polygon from \
  1.44737e+12, 3.32894e+11 to \
  -1.12814, -0 to \
  -1.13583, -0 to \
  1.44737e+12, 3.32894e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 325 polygon from \
  1.35498e+12, 3.25195e+11 to \
  -1.17719, -0 to \
  -1.18456, -0 to \
  1.35498e+12, 3.25195e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 326 polygon from \
  1.29968e+12, 3.24918e+11 to \
  -1.22624, -0 to \
  -1.23332, -0 to \
  1.29968e+12, 3.24918e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 327 polygon from \
  1.2247e+12, 3.1842e+11 to \
  -1.27529, -0 to \
  -1.28209, -0 to \
  1.2247e+12, 3.1842e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 328 polygon from \
  1.098e+12, 2.9646e+11 to \
  -1.32434, -0 to \
  -1.33089, -0 to \
  1.098e+12, 2.9646e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 329 polygon from \
  9.95061e+11, 2.78618e+11 to \
  -1.37339, -0 to \
  -1.37971, -0 to \
  9.95061e+11, 2.78618e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 330 polygon from \
  9.0977e+11, 2.63834e+11 to \
  -1.42244, -0 to \
  -1.42854, -0 to \
  9.0977e+11, 2.63834e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 331 polygon from \
  8.37946e+11, 2.51384e+11 to \
  -1.47149, -0 to \
  -1.47739, -0 to \
  8.37946e+11, 2.51384e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 332 polygon from \
  7.58142e+11, 2.35024e+11 to \
  -1.52054, -0 to \
  -1.52625, -0 to \
  7.58142e+11, 2.35024e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 333 polygon from \
  7.07599e+11, 2.26432e+11 to \
  -1.56959, -0 to \
  -1.57512, -0 to \
  7.07599e+11, 2.26432e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 334 polygon from \
  6.63374e+11, 2.18914e+11 to \
  -1.61864, -0 to \
  -1.624, -0 to \
  6.63374e+11, 2.18914e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 335 polygon from \
  6.12346e+11, 2.08198e+11 to \
  -1.66769, -0 to \
  -1.67289, -0 to \
  6.12346e+11, 2.08198e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 336 polygon from \
  5.78945e+11, 2.02631e+11 to \
  -1.71674, -0 to \
  -1.7218, -0 to \
  5.78945e+11, 2.02631e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 337 polygon from \
  5.49e+11, 1.9764e+11 to \
  -1.76579, -0 to \
  -1.7707, -0 to \
  5.49e+11, 1.9764e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 338 polygon from \
  5.1358e+11, 1.90025e+11 to \
  -1.81484, -0 to \
  -1.81962, -0 to \
  5.1358e+11, 1.90025e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 339 polygon from \
  4.89877e+11, 1.86153e+11 to \
  -1.86389, -0 to \
  -1.86855, -0 to \
  4.89877e+11, 1.86153e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 340 polygon from \
  4.61478e+11, 1.79977e+11 to \
  -1.91294, -0 to \
  -1.91748, -0 to \
  4.61478e+11, 1.79977e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 341 polygon from \
  4.4225e+11, 1.769e+11 to \
  -1.96199, -0 to \
  -1.96641, -0 to \
  4.4225e+11, 1.769e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 342 polygon from \
  4.18973e+11, 1.71779e+11 to \
  -2.01104, -0 to \
  -2.01536, -0 to \
  4.18973e+11, 1.71779e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 343 polygon from \
  3.98025e+11, 1.67171e+11 to \
  -2.06009, -0 to \
  -2.0643, -0 to \
  3.98025e+11, 1.67171e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 344 polygon from \
  3.83638e+11, 1.64965e+11 to \
  -2.10914, -0 to \
  -2.11326, -0 to \
  3.83638e+11, 1.64965e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 345 polygon from \
  3.66e+11, 1.6104e+11 to \
  -2.15819, -0 to \
  -2.16221, -0 to \
  3.66e+11, 1.6104e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 346 polygon from \
  3.49912e+11, 1.57461e+11 to \
  -2.20724, -0 to \
  -2.21117, -0 to \
  3.49912e+11, 1.57461e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 347 polygon from \
  3.35179e+11, 1.54183e+11 to \
  -2.25629, -0 to \
  -2.26014, -0 to \
  3.35179e+11, 1.54183e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 348 polygon from \
  3.24918e+11, 1.52712e+11 to \
  -2.30534, -0 to \
  -2.30911, -0 to \
  3.24918e+11, 1.52712e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 349 polygon from \
  3.15267e+11, 1.51329e+11 to \
  -2.35439, -0 to \
  -2.35808, -0 to \
  3.15267e+11, 1.51329e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 350 polygon from \
  3.06173e+11, 1.50025e+11 to \
  -2.40344, -0 to \
  -2.40705, -0 to \
  3.06173e+11, 1.50025e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 351 polygon from \
  3.00396e+11, 1.50198e+11 to \
  -2.45249, -0 to \
  -2.45603, -0 to \
  3.00396e+11, 1.50198e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 352 polygon from \
  2.89473e+11, 1.47631e+11 to \
  -2.50154, -0 to \
  -2.50501, -0 to \
  2.89473e+11, 1.47631e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 353 polygon from \
  2.745e+11, 1.4274e+11 to \
  -2.55059, -0 to \
  -2.55399, -0 to \
  2.745e+11, 1.4274e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 354 polygon from \
  2.61e+11, 1.3833e+11 to \
  -2.59964, -0 to \
  -2.60298, -0 to \
  2.61e+11, 1.3833e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 355 polygon from \
  2.48766e+11, 1.34334e+11 to \
  -2.64869, -0 to \
  -2.65197, -0 to \
  2.48766e+11, 1.34334e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 356 polygon from \
  2.37627e+11, 1.30695e+11 to \
  -2.69774, -0 to \
  -2.70096, -0 to \
  2.37627e+11, 1.30695e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 357 polygon from \
  2.27443e+11, 1.27368e+11 to \
  -2.74679, -0 to \
  -2.74995, -0 to \
  2.27443e+11, 1.27368e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 358 polygon from \
  2.18096e+11, 1.24315e+11 to \
  -2.79584, -0 to \
  -2.79895, -0 to \
  2.18096e+11, 1.24315e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 359 polygon from \
  2.09487e+11, 1.21503e+11 to \
  -2.84489, -0 to \
  -2.84794, -0 to \
  2.09487e+11, 1.21503e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 360 polygon from \
  2.01532e+11, 1.18904e+11 to \
  -2.89394, -0 to \
  -2.89694, -0 to \
  2.01532e+11, 1.18904e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 361 polygon from \
  1.94159e+11, 1.16495e+11 to \
  -2.94299, -0 to \
  -2.94594, -0 to \
  1.94159e+11, 1.16495e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 362 polygon from \
  1.85128e+11, 1.12928e+11 to \
  -2.99204, -0 to \
  -2.99494, -0 to \
  1.85128e+11, 1.12928e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 363 polygon from \
  1.78888e+11, 1.10911e+11 to \
  -3.04109, -0 to \
  -3.04395, -0 to \
  1.78888e+11, 1.10911e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 364 polygon from \
  1.73055e+11, 1.09025e+11 to \
  -3.09014, -0 to \
  -3.09295, -0 to \
  1.73055e+11, 1.09025e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 365 polygon from \
  1.6759e+11, 1.07258e+11 to \
  -3.13919, -0 to \
  -3.14196, -0 to \
  1.6759e+11, 1.07258e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 366 polygon from \
  1.60818e+11, 1.04532e+11 to \
  -3.18824, -0 to \
  -3.19096, -0 to \
  1.60818e+11, 1.04532e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 367 polygon from \
  1.56088e+11, 1.03019e+11 to \
  -3.23729, -0 to \
  -3.23997, -0 to \
  1.56088e+11, 1.03019e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 368 polygon from \
  1.51629e+11, 1.01591e+11 to \
  -3.28634, -0 to \
  -3.28898, -0 to \
  1.51629e+11, 1.01591e+11 front fs empty border lc rgb '#6165' lw 0.200001
set object 369 polygon from \
  1.46064e+11, 9.93236e+10 to \
  -3.33539, -0 to \
  -3.33799, -0 to \
  1.46064e+11, 9.93236e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 370 polygon from \
  1.42152e+11, 9.80846e+10 to \
  -3.38444, -0 to \
  -3.38701, -0 to \
  1.42152e+11, 9.80846e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 371 polygon from \
  1.38444e+11, 9.69103e+10 to \
  -3.43349, -0 to \
  -3.43602, -0 to \
  1.38444e+11, 9.69103e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 372 polygon from \
  1.3379e+11, 9.49907e+10 to \
  -3.48254, -0 to \
  -3.48503, -0 to \
  1.3379e+11, 9.49907e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 373 polygon from \
  1.305e+11, 9.39599e+10 to \
  -3.53159, -0 to \
  -3.53405, -0 to \
  1.305e+11, 9.39599e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 374 polygon from \
  1.26357e+11, 9.22406e+10 to \
  -3.58064, -0 to \
  -3.58307, -0 to \
  1.26357e+11, 9.22406e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 375 polygon from \
  1.23419e+11, 9.13297e+10 to \
  -3.62969, -0 to \
  -3.63208, -0 to \
  1.23419e+11, 9.13297e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 376 polygon from \
  1.19707e+11, 8.978e+10 to \
  -3.67874, -0 to \
  -3.6811, -0 to \
  1.19707e+11, 8.978e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 377 polygon from \
  1.17066e+11, 8.89702e+10 to \
  -3.72779, -0 to \
  -3.73012, -0 to \
  1.17066e+11, 8.89702e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 378 polygon from \
  1.13722e+11, 8.75654e+10 to \
  -3.77684, -0 to \
  -3.77914, -0 to \
  1.13722e+11, 8.75654e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 379 polygon from \
  1.11336e+11, 8.68417e+10 to \
  -3.82589, -0 to \
  -3.82816, -0 to \
  1.11336e+11, 8.68417e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 380 polygon from \
  1.08306e+11, 8.55617e+10 to \
  -3.87494, -0 to \
  -3.87718, -0 to \
  1.08306e+11, 8.55617e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 381 polygon from \
  1.0614e+11, 8.49119e+10 to \
  -3.92399, -0 to \
  -3.9262, -0 to \
  1.0614e+11, 8.49119e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 382 polygon from \
  1.03383e+11, 8.37402e+10 to \
  -3.97304, -0 to \
  -3.97523, -0 to \
  1.03383e+11, 8.37402e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 383 polygon from \
  1.00766e+11, 8.26279e+10 to \
  -4.02209, -0 to \
  -4.02425, -0 to \
  1.00766e+11, 8.26279e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 384 polygon from \
  9.88881e+10, 8.20771e+10 to \
  -4.07114, -0 to \
  -4.07327, -0 to \
  9.88881e+10, 8.20771e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 385 polygon from \
  9.64908e+10, 8.10523e+10 to \
  -4.12019, -0 to \
  -4.1223, -0 to \
  9.64908e+10, 8.10523e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 386 polygon from \
  9.4207e+10, 8.0076e+10 to \
  -4.16924, -0 to \
  -4.17132, -0 to \
  9.4207e+10, 8.0076e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 387 polygon from \
  9.25639e+10, 7.96049e+10 to \
  -4.21829, -0 to \
  -4.22035, -0 to \
  9.25639e+10, 7.96049e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 388 polygon from \
  9.04601e+10, 7.87003e+10 to \
  -4.26734, -0 to \
  -4.26938, -0 to \
  9.04601e+10, 7.87003e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 389 polygon from \
  8.84499e+10, 7.78359e+10 to \
  -4.31639, -0 to \
  -4.3184, -0 to \
  8.84499e+10, 7.78359e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 390 polygon from \
  8.65271e+10, 7.70091e+10 to \
  -4.36544, -0 to \
  -4.36743, -0 to \
  8.65271e+10, 7.70091e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 391 polygon from \
  8.51389e+10, 7.66251e+10 to \
  -4.41449, -0 to \
  -4.41646, -0 to \
  8.51389e+10, 7.66251e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 392 polygon from \
  8.33559e+10, 7.58539e+10 to \
  -4.46354, -0 to \
  -4.46549, -0 to \
  8.33559e+10, 7.58539e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 393 polygon from \
  8.16461e+10, 7.51144e+10 to \
  -4.51259, -0 to \
  -4.51452, -0 to \
  8.16461e+10, 7.51144e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 394 polygon from \
  8.00049e+10, 7.44046e+10 to \
  -4.56164, -0 to \
  -4.56355, -0 to \
  8.00049e+10, 7.44046e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 395 polygon from \
  7.84285e+10, 7.37228e+10 to \
  -4.61069, -0 to \
  -4.61258, -0 to \
  7.84285e+10, 7.37228e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 396 polygon from \
  7.6913e+10, 7.30673e+10 to \
  -4.65974, -0 to \
  -4.66161, -0 to \
  7.6913e+10, 7.30673e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 397 polygon from \
  7.54549e+10, 7.24367e+10 to \
  -4.70879, -0 to \
  -4.71064, -0 to \
  7.54549e+10, 7.24367e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 398 polygon from \
  7.43971e+10, 7.21652e+10 to \
  -4.75784, -0 to \
  -4.75967, -0 to \
  7.43971e+10, 7.21652e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 399 polygon from \
  7.33686e+10, 7.19012e+10 to \
  -4.80689, -0 to \
  -4.8087, -0 to \
  7.33686e+10, 7.19012e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 400 polygon from \
  7.23681e+10, 7.16444e+10 to \
  -4.85594, -0 to \
  -4.85773, -0 to \
  7.23681e+10, 7.16444e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 401 polygon from \
  7.17161e+10, 7.17161e+10 to \
  -4.90499, -0 to \
  -4.90676, -0 to \
  7.17161e+10, 7.17161e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 402 polygon from \
  7.10061e+10, 7.17161e+10 to \
  -4.95404, -0 to \
  -4.9558, -0 to \
  7.10061e+10, 7.17161e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 403 polygon from \
  6.90655e+10, 7.04468e+10 to \
  -5.00309, -0 to \
  -5.00483, -0 to \
  6.90655e+10, 7.04468e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 404 polygon from \
  6.72055e+10, 6.92217e+10 to \
  -5.05214, -0 to \
  -5.05386, -0 to \
  6.72055e+10, 6.92217e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 405 polygon from \
  6.57023e+10, 6.83304e+10 to \
  -5.10119, -0 to \
  -5.10289, -0 to \
  6.57023e+10, 6.83304e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 406 polygon from \
  6.39782e+10, 6.71772e+10 to \
  -5.15024, -0 to \
  -5.15193, -0 to \
  6.39782e+10, 6.71772e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 407 polygon from \
  6.25825e+10, 6.63374e+10 to \
  -5.19929, -0 to \
  -5.20096, -0 to \
  6.25825e+10, 6.63374e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 408 polygon from \
  6.09813e+10, 6.52499e+10 to \
  -5.24834, -0 to \
  -5.25, -0 to \
  6.09813e+10, 6.52499e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 409 polygon from \
  5.96828e+10, 6.44574e+10 to \
  -5.29739, -0 to \
  -5.29903, -0 to \
  5.96828e+10, 6.44574e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 410 polygon from \
  5.81929e+10, 6.34302e+10 to \
  -5.34644, -0 to \
  -5.34807, -0 to \
  5.81929e+10, 6.34302e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 411 polygon from \
  5.69828e+10, 6.2681e+10 to \
  -5.39549, -0 to \
  -5.3971, -0 to \
  5.69828e+10, 6.2681e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 412 polygon from \
  5.58102e+10, 6.19494e+10 to \
  -5.44454, -0 to \
  -5.44614, -0 to \
  5.58102e+10, 6.19494e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 413 polygon from \
  5.44642e+10, 6.09999e+10 to \
  -5.49359, -0 to \
  -5.49517, -0 to \
  5.44642e+10, 6.09999e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 414 polygon from \
  5.33688e+10, 6.03068e+10 to \
  -5.54264, -0 to \
  -5.54421, -0 to \
  5.33688e+10, 6.03068e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 415 polygon from \
  5.23063e+10, 5.96292e+10 to \
  -5.59169, -0 to \
  -5.59325, -0 to \
  5.23063e+10, 5.96292e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 416 polygon from \
  5.12753e+10, 5.89666e+10 to \
  -5.64074, -0 to \
  -5.64228, -0 to \
  5.12753e+10, 5.89666e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 417 polygon from \
  5.02747e+10, 5.83186e+10 to \
  -5.68979, -0 to \
  -5.69132, -0 to \
  5.02747e+10, 5.83186e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 418 polygon from \
  4.93032e+10, 5.76847e+10 to \
  -5.73884, -0 to \
  -5.74036, -0 to \
  4.93032e+10, 5.76847e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 419 polygon from \
  4.83597e+10, 5.70645e+10 to \
  -5.78789, -0 to \
  -5.78939, -0 to \
  4.83597e+10, 5.70645e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 420 polygon from \
  4.74432e+10, 5.64574e+10 to \
  -5.83694, -0 to \
  -5.83843, -0 to \
  4.74432e+10, 5.64574e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 421 polygon from \
  4.65526e+10, 5.58631e+10 to \
  -5.88599, -0 to \
  -5.88747, -0 to \
  4.65526e+10, 5.58631e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 422 polygon from \
  4.5687e+10, 5.52812e+10 to \
  -5.93504, -0 to \
  -5.93651, -0 to \
  4.5687e+10, 5.52812e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 423 polygon from \
  4.48453e+10, 5.47113e+10 to \
  -5.98409, -0 to \
  -5.98554, -0 to \
  4.48453e+10, 5.47113e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 424 polygon from \
  4.40269e+10, 5.4153e+10 to \
  -6.03314, -0 to \
  -6.03458, -0 to \
  4.40269e+10, 5.4153e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 425 polygon from \
  4.32307e+10, 5.3606e+10 to \
  -6.08219, -0 to \
  -6.08362, -0 to \
  4.32307e+10, 5.3606e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 426 polygon from \
  4.2598e+10, 5.32475e+10 to \
  -6.13124, -0 to \
  -6.13266, -0 to \
  4.2598e+10, 5.32475e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 427 polygon from \
  4.18401e+10, 5.27185e+10 to \
  -6.18029, -0 to \
  -6.1817, -0 to \
  4.18401e+10, 5.27185e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 428 polygon from \
  4.11023e+10, 5.22e+10 to \
  -6.22934, -0 to \
  -6.23074, -0 to \
  4.11023e+10, 5.22e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 429 polygon from \
  4.0384e+10, 5.16915e+10 to \
  -6.27839, -0 to \
  -6.27978, -0 to \
  4.0384e+10, 5.16915e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 430 polygon from \
  3.98124e+10, 5.1358e+10 to \
  -6.32744, -0 to \
  -6.32882, -0 to \
  3.98124e+10, 5.1358e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 431 polygon from \
  3.91275e+10, 5.08658e+10 to \
  -6.37649, -0 to \
  -6.37785, -0 to \
  3.91275e+10, 5.08658e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 432 polygon from \
  3.84602e+10, 5.03829e+10 to \
  -6.42554, -0 to \
  -6.42689, -0 to \
  3.84602e+10, 5.03829e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 433 polygon from \
  3.79288e+10, 5.0066e+10 to \
  -6.47459, -0 to \
  -6.47593, -0 to \
  3.79288e+10, 5.0066e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 434 polygon from \
  3.72918e+10, 4.95981e+10 to \
  -6.52364, -0 to \
  -6.52497, -0 to \
  3.72918e+10, 4.95981e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 435 polygon from \
  3.66708e+10, 4.91389e+10 to \
  -6.57269, -0 to \
  -6.57401, -0 to \
  3.66708e+10, 4.91389e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 436 polygon from \
  3.61759e+10, 4.88374e+10 to \
  -6.62174, -0 to \
  -6.62305, -0 to \
  3.61759e+10, 4.88374e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 437 polygon from \
  3.55824e+10, 4.83921e+10 to \
  -6.67079, -0 to \
  -6.67209, -0 to \
  3.55824e+10, 4.83921e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 438 polygon from \
  3.51093e+10, 4.80997e+10 to \
  -6.71984, -0 to \
  -6.72114, -0 to \
  3.51093e+10, 4.80997e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 439 polygon from \
  3.45418e+10, 4.76676e+10 to \
  -6.76889, -0 to \
  -6.77018, -0 to \
  3.45418e+10, 4.76676e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 440 polygon from \
  3.40892e+10, 4.73839e+10 to \
  -6.81794, -0 to \
  -6.81922, -0 to \
  3.40892e+10, 4.73839e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 441 polygon from \
  3.36454e+10, 4.71035e+10 to \
  -6.86699, -0 to \
  -6.86826, -0 to \
  3.36454e+10, 4.71035e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 442 polygon from \
  3.31129e+10, 4.66891e+10 to \
  -6.91604, -0 to \
  -6.9173, -0 to \
  3.31129e+10, 4.66891e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 443 polygon from \
  3.2688e+10, 4.64169e+10 to \
  -6.96509, -0 to \
  -6.96634, -0 to \
  3.2688e+10, 4.64169e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 444 polygon from \
  3.21779e+10, 4.60144e+10 to \
  -7.01414, -0 to \
  -7.01538, -0 to \
  3.21779e+10, 4.60144e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 445 polygon from \
  3.17708e+10, 4.575e+10 to \
  -7.06319, -0 to \
  -7.06442, -0 to \
  3.17708e+10, 4.575e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 446 polygon from \
  3.13714e+10, 4.54885e+10 to \
  -7.11224, -0 to \
  -7.11346, -0 to \
  3.13714e+10, 4.54885e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 447 polygon from \
  3.08918e+10, 4.5102e+10 to \
  -7.16129, -0 to \
  -7.16251, -0 to \
  3.08918e+10, 4.5102e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 448 polygon from \
  3.05088e+10, 4.48479e+10 to \
  -7.21034, -0 to \
  -7.21155, -0 to \
  3.05088e+10, 4.48479e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 449 polygon from \
  3.01329e+10, 4.45966e+10 to \
  -7.25939, -0 to \
  -7.26059, -0 to \
  3.01329e+10, 4.45966e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 450 polygon from \
  2.96812e+10, 4.4225e+10 to \
  -7.30844, -0 to \
  -7.30963, -0 to \
  2.96812e+10, 4.4225e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 451 polygon from \
  2.93204e+10, 4.39806e+10 to \
  -7.35749, -0 to \
  -7.35867, -0 to \
  2.93204e+10, 4.39806e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 452 polygon from \
  2.89662e+10, 4.3739e+10 to \
  -7.40654, -0 to \
  -7.40772, -0 to \
  2.89662e+10, 4.3739e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 453 polygon from \
  2.86184e+10, 4.35e+10 to \
  -7.45559, -0 to \
  -7.45676, -0 to \
  2.86184e+10, 4.35e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 454 polygon from \
  2.82769e+10, 4.32636e+10 to \
  -7.50464, -0 to \
  -7.5058, -0 to \
  2.82769e+10, 4.32636e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 455 polygon from \
  2.78661e+10, 4.29137e+10 to \
  -7.55369, -0 to \
  -7.55484, -0 to \
  2.78661e+10, 4.29137e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 456 polygon from \
  2.75378e+10, 4.26836e+10 to \
  -7.60274, -0 to \
  -7.60389, -0 to \
  2.75378e+10, 4.26836e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 457 polygon from \
  2.72154e+10, 4.2456e+10 to \
  -7.65179, -0 to \
  -7.65293, -0 to \
  2.72154e+10, 4.2456e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 458 polygon from \
  2.68986e+10, 4.22307e+10 to \
  -7.70084, -0 to \
  -7.70197, -0 to \
  2.68986e+10, 4.22307e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 459 polygon from \
  2.65873e+10, 4.20079e+10 to \
  -7.74989, -0 to \
  -7.75101, -0 to \
  2.65873e+10, 4.20079e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 460 polygon from \
  2.62814e+10, 4.17874e+10 to \
  -7.79894, -0 to \
  -7.80006, -0 to \
  2.62814e+10, 4.17874e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 461 polygon from \
  2.59808e+10, 4.15692e+10 to \
  -7.84799, -0 to \
  -7.8491, -0 to \
  2.59808e+10, 4.15692e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 462 polygon from \
  2.56187e+10, 4.12461e+10 to \
  -7.89704, -0 to \
  -7.89814, -0 to \
  2.56187e+10, 4.12461e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 463 polygon from \
  2.53293e+10, 4.10335e+10 to \
  -7.94609, -0 to \
  -7.94719, -0 to \
  2.53293e+10, 4.10335e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 464 polygon from \
  2.50448e+10, 4.08231e+10 to \
  -7.99514, -0 to \
  -7.99623, -0 to \
  2.50448e+10, 4.08231e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 465 polygon from \
  2.47651e+10, 4.06148e+10 to \
  -8.04419, -0 to \
  -8.04527, -0 to \
  2.47651e+10, 4.06148e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 466 polygon from \
  2.44901e+10, 4.04086e+10 to \
  -8.09324, -0 to \
  -8.09432, -0 to \
  2.44901e+10, 4.04086e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 467 polygon from \
  2.42196e+10, 4.02045e+10 to \
  -8.14229, -0 to \
  -8.14336, -0 to \
  2.42196e+10, 4.02045e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 468 polygon from \
  2.39536e+10, 4.00025e+10 to \
  -8.19134, -0 to \
  -8.1924, -0 to \
  2.39536e+10, 4.00025e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 469 polygon from \
  2.3692e+10, 3.98025e+10 to \
  -8.24039, -0 to \
  -8.24145, -0 to \
  2.3692e+10, 3.98025e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 470 polygon from \
  2.34346e+10, 3.96045e+10 to \
  -8.28944, -0 to \
  -8.29049, -0 to \
  2.34346e+10, 3.96045e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 471 polygon from \
  2.31814e+10, 3.94084e+10 to \
  -8.33849, -0 to \
  -8.33953, -0 to \
  2.31814e+10, 3.94084e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 472 polygon from \
  2.29323e+10, 3.92143e+10 to \
  -8.38754, -0 to \
  -8.38858, -0 to \
  2.29323e+10, 3.92143e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 473 polygon from \
  2.26873e+10, 3.9022e+10 to \
  -8.43659, -0 to \
  -8.43762, -0 to \
  2.26873e+10, 3.9022e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 474 polygon from \
  2.24461e+10, 3.88317e+10 to \
  -8.48564, -0 to \
  -8.48667, -0 to \
  2.24461e+10, 3.88317e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 475 polygon from \
  2.22088e+10, 3.86432e+10 to \
  -8.53469, -0 to \
  -8.53571, -0 to \
  2.22088e+10, 3.86432e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 476 polygon from \
  2.20284e+10, 3.85496e+10 to \
  -8.58374, -0 to \
  -8.58476, -0 to \
  2.20284e+10, 3.85496e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 477 polygon from \
  2.17977e+10, 3.83638e+10 to \
  -8.63279, -0 to \
  -8.6338, -0 to \
  2.17977e+10, 3.83638e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 478 polygon from \
  2.15706e+10, 3.81798e+10 to \
  -8.68184, -0 to \
  -8.68284, -0 to \
  2.15706e+10, 3.81798e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 479 polygon from \
  2.1347e+10, 3.79976e+10 to \
  -8.73089, -0 to \
  -8.73189, -0 to \
  2.1347e+10, 3.79976e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 480 polygon from \
  2.11269e+10, 3.78171e+10 to \
  -8.77994, -0 to \
  -8.78093, -0 to \
  2.11269e+10, 3.78171e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 481 polygon from \
  2.09102e+10, 3.76383e+10 to \
  -8.82899, -0 to \
  -8.82998, -0 to \
  2.09102e+10, 3.76383e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 482 polygon from \
  2.06968e+10, 3.74612e+10 to \
  -8.87804, -0 to \
  -8.87902, -0 to \
  2.06968e+10, 3.74612e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 483 polygon from \
  2.04867e+10, 3.72857e+10 to \
  -8.92709, -0 to \
  -8.92807, -0 to \
  2.04867e+10, 3.72857e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 484 polygon from \
  2.03271e+10, 3.71986e+10 to \
  -8.97614, -0 to \
  -8.97711, -0 to \
  2.03271e+10, 3.71986e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 485 polygon from \
  2.01226e+10, 3.70256e+10 to \
  -9.02519, -0 to \
  -9.02616, -0 to \
  2.01226e+10, 3.70256e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 486 polygon from \
  1.99212e+10, 3.68542e+10 to \
  -9.07424, -0 to \
  -9.0752, -0 to \
  1.99212e+10, 3.68542e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 487 polygon from \
  1.97228e+10, 3.66843e+10 to \
  -9.12329, -0 to \
  -9.12425, -0 to \
  1.97228e+10, 3.66843e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 488 polygon from \
  1.95273e+10, 3.6516e+10 to \
  -9.17234, -0 to \
  -9.17329, -0 to \
  1.95273e+10, 3.6516e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 489 polygon from \
  1.93348e+10, 3.63493e+10 to \
  -9.22139, -0 to \
  -9.22234, -0 to \
  1.93348e+10, 3.63493e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 490 polygon from \
  1.91887e+10, 3.62665e+10 to \
  -9.27044, -0 to \
  -9.27138, -0 to \
  1.91887e+10, 3.62665e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 491 polygon from \
  1.90011e+10, 3.6102e+10 to \
  -9.31949, -0 to \
  -9.32043, -0 to \
  1.90011e+10, 3.6102e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 492 polygon from \
  1.88163e+10, 3.5939e+10 to \
  -9.36854, -0 to \
  -9.36947, -0 to \
  1.88163e+10, 3.5939e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 493 polygon from \
  1.86341e+10, 3.57775e+10 to \
  -9.41759, -0 to \
  -9.41852, -0 to \
  1.86341e+10, 3.57775e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 494 polygon from \
  1.8496e+10, 3.56973e+10 to \
  -9.46664, -0 to \
  -9.46756, -0 to \
  1.8496e+10, 3.56973e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 495 polygon from \
  1.83185e+10, 3.55379e+10 to \
  -9.51569, -0 to \
  -9.51661, -0 to \
  1.83185e+10, 3.55379e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 496 polygon from \
  1.81436e+10, 3.538e+10 to \
  -9.56474, -0 to \
  -9.56565, -0 to \
  1.81436e+10, 3.538e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 497 polygon from \
  1.79712e+10, 3.52234e+10 to \
  -9.61379, -0 to \
  -9.6147, -0 to \
  1.79712e+10, 3.52234e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 498 polygon from \
  1.78799e+10, 3.52234e+10 to \
  -9.66284, -0 to \
  -9.66374, -0 to \
  1.78799e+10, 3.52234e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 499 polygon from \
  1.77504e+10, 3.51457e+10 to \
  -9.71189, -0 to \
  -9.71279, -0 to \
  1.77504e+10, 3.51457e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 500 polygon from \
  1.76223e+10, 3.50683e+10 to \
  -9.76094, -0 to \
  -9.76183, -0 to \
  1.76223e+10, 3.50683e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 501 polygon from \
  1.74956e+10, 3.49912e+10 to \
  -9.80999, -0 to \
  -9.81088, -0 to \
  1.74956e+10, 3.49912e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 502 polygon from \
  1.73704e+10, 3.49145e+10 to \
  -9.85904, -0 to \
  -9.85992, -0 to \
  1.73704e+10, 3.49145e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 503 polygon from \
  1.72089e+10, 3.4762e+10 to \
  -9.90809, -0 to \
  -9.90897, -0 to \
  1.72089e+10, 3.4762e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 504 polygon from \
  1.70497e+10, 3.46109e+10 to \
  -9.95714, -0 to \
  -9.95802, -0 to \
  1.70497e+10, 3.46109e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 505 polygon from \
  1.69293e+10, 3.45358e+10 to \
  -10.0061, -0 to \
  -10.007, -0 to \
  1.69293e+10, 3.45358e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 506 polygon from \
  1.6774e+10, 3.43866e+10 to \
  -10.0552, -0 to \
  -10.0561, -0 to \
  1.6774e+10, 3.43866e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 507 polygon from \
  1.66208e+10, 3.42387e+10 to \
  -10.1042, -0 to \
  -10.1051, -0 to \
  1.66208e+10, 3.42387e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 508 polygon from \
  1.6505e+10, 3.41652e+10 to \
  -10.1533, -0 to \
  -10.1542, -0 to \
  1.6505e+10, 3.41652e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 509 polygon from \
  1.63554e+10, 3.40192e+10 to \
  -10.2023, -0 to \
  -10.2032, -0 to \
  1.63554e+10, 3.40192e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 510 polygon from \
  1.62079e+10, 3.38745e+10 to \
  -10.2514, -0 to \
  -10.2522, -0 to \
  1.62079e+10, 3.38745e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 511 polygon from \
  1.60965e+10, 3.38025e+10 to \
  -10.3004, -0 to \
  -10.3013, -0 to \
  1.60965e+10, 3.38025e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 512 polygon from \
  1.59525e+10, 3.36596e+10 to \
  -10.3495, -0 to \
  -10.3503, -0 to \
  1.59525e+10, 3.36596e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 513 polygon from \
  1.58104e+10, 3.35179e+10 to \
  -10.3985, -0 to \
  -10.3994, -0 to \
  1.58104e+10, 3.35179e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 514 polygon from \
  1.57031e+10, 3.34475e+10 to \
  -10.4476, -0 to \
  -10.4484, -0 to \
  1.57031e+10, 3.34475e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 515 polygon from \
  1.55643e+10, 3.33075e+10 to \
  -10.4966, -0 to \
  -10.4975, -0 to \
  1.55643e+10, 3.33075e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 516 polygon from \
  1.54274e+10, 3.31687e+10 to \
  -10.5457, -0 to \
  -10.5465, -0 to \
  1.54274e+10, 3.31687e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 517 polygon from \
  1.5324e+10, 3.30998e+10 to \
  -10.5947, -0 to \
  -10.5956, -0 to \
  1.5324e+10, 3.30998e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 518 polygon from \
  1.51902e+10, 3.29627e+10 to \
  -10.6438, -0 to \
  -10.6446, -0 to \
  1.51902e+10, 3.29627e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 519 polygon from \
  1.50893e+10, 3.28946e+10 to \
  -10.6928, -0 to \
  -10.6937, -0 to \
  1.50893e+10, 3.28946e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 520 polygon from \
  1.49586e+10, 3.27593e+10 to \
  -10.7419, -0 to \
  -10.7427, -0 to \
  1.49586e+10, 3.27593e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 521 polygon from \
  1.48296e+10, 3.2625e+10 to \
  -10.7909, -0 to \
  -10.7918, -0 to \
  1.48296e+10, 3.2625e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 522 polygon from \
  1.47323e+10, 3.25583e+10 to \
  -10.84, -0 to \
  -10.8408, -0 to \
  1.47323e+10, 3.25583e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 523 polygon from \
  1.46062e+10, 3.24257e+10 to \
  -10.889, -0 to \
  -10.8898, -0 to \
  1.46062e+10, 3.24257e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 524 polygon from \
  1.45111e+10, 3.23598e+10 to \
  -10.9381, -0 to \
  -10.9389, -0 to \
  1.45111e+10, 3.23598e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 525 polygon from \
  1.43879e+10, 3.22287e+10 to \
  -10.9871, -0 to \
  -10.9879, -0 to \
  1.43879e+10, 3.22287e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 526 polygon from \
  1.42662e+10, 3.20988e+10 to \
  -11.0362, -0 to \
  -11.037, -0 to \
  1.42662e+10, 3.20988e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 527 polygon from \
  1.41745e+10, 3.20342e+10 to \
  -11.0852, -0 to \
  -11.086, -0 to \
  1.41745e+10, 3.20342e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 528 polygon from \
  1.40555e+10, 3.19058e+10 to \
  -11.1343, -0 to \
  -11.1351, -0 to \
  1.40555e+10, 3.19058e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 529 polygon from \
  1.39658e+10, 3.1842e+10 to \
  -11.1833, -0 to \
  -11.1841, -0 to \
  1.39658e+10, 3.1842e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 530 polygon from \
  1.38494e+10, 3.17151e+10 to \
  -11.2324, -0 to \
  -11.2332, -0 to \
  1.38494e+10, 3.17151e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 531 polygon from \
  1.37618e+10, 3.16521e+10 to \
  -11.2814, -0 to \
  -11.2822, -0 to \
  1.37618e+10, 3.16521e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 532 polygon from \
  1.3648e+10, 3.15267e+10 to \
  -11.3305, -0 to \
  -11.3313, -0 to \
  1.3648e+10, 3.15267e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 533 polygon from \
  1.35623e+10, 3.14644e+10 to \
  -11.3795, -0 to \
  -11.3803, -0 to \
  1.35623e+10, 3.14644e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 534 polygon from \
  1.34509e+10, 3.13405e+10 to \
  -11.4286, -0 to \
  -11.4294, -0 to \
  1.34509e+10, 3.13405e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 535 polygon from \
  1.33671e+10, 3.1279e+10 to \
  -11.4776, -0 to \
  -11.4784, -0 to \
  1.33671e+10, 3.1279e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 536 polygon from \
  1.32581e+10, 3.11566e+10 to \
  -11.5267, -0 to \
  -11.5275, -0 to \
  1.32581e+10, 3.11566e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 537 polygon from \
  1.31762e+10, 3.10957e+10 to \
  -11.5757, -0 to \
  -11.5765, -0 to \
  1.31762e+10, 3.10957e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 538 polygon from \
  1.30695e+10, 3.09747e+10 to \
  -11.6248, -0 to \
  -11.6255, -0 to \
  1.30695e+10, 3.09747e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 539 polygon from \
  1.29893e+10, 3.09146e+10 to \
  -11.6738, -0 to \
  -11.6746, -0 to \
  1.29893e+10, 3.09146e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 540 polygon from \
  1.2885e+10, 3.0795e+10 to \
  -11.7229, -0 to \
  -11.7236, -0 to \
  1.2885e+10, 3.0795e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 541 polygon from \
  1.27818e+10, 3.06763e+10 to \
  -11.7719, -0 to \
  -11.7727, -0 to \
  1.27818e+10, 3.06763e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 542 polygon from \
  1.27043e+10, 3.06173e+10 to \
  -11.821, -0 to \
  -11.8217, -0 to \
  1.27043e+10, 3.06173e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 543 polygon from \
  1.26275e+10, 3.05585e+10 to \
  -11.87, -0 to \
  -11.8708, -0 to \
  1.26275e+10, 3.05585e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 544 polygon from \
  1.25275e+10, 3.04417e+10 to \
  -11.9191, -0 to \
  -11.9198, -0 to \
  1.25275e+10, 3.04417e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 545 polygon from \
  1.24523e+10, 3.03836e+10 to \
  -11.9681, -0 to \
  -11.9689, -0 to \
  1.24523e+10, 3.03836e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 546 polygon from \
  1.23543e+10, 3.02681e+10 to \
  -12.0172, -0 to \
  -12.0179, -0 to \
  1.23543e+10, 3.02681e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 547 polygon from \
  1.22808e+10, 3.02106e+10 to \
  -12.0662, -0 to \
  -12.067, -0 to \
  1.22808e+10, 3.02106e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 548 polygon from \
  1.21848e+10, 3.00964e+10 to \
  -12.1153, -0 to \
  -12.116, -0 to \
  1.21848e+10, 3.00964e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 549 polygon from \
  1.21128e+10, 3.00396e+10 to \
  -12.1643, -0 to \
  -12.1651, -0 to \
  1.21128e+10, 3.00396e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 550 polygon from \
  1.20188e+10, 2.99267e+10 to \
  -12.2134, -0 to \
  -12.2141, -0 to \
  1.20188e+10, 2.99267e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 551 polygon from \
  1.19482e+10, 2.98705e+10 to \
  -12.2624, -0 to \
  -12.2632, -0 to \
  1.19482e+10, 2.98705e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 552 polygon from \
  1.18562e+10, 2.97589e+10 to \
  -12.3115, -0 to \
  -12.3122, -0 to \
  1.18562e+10, 2.97589e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 553 polygon from \
  1.17871e+10, 2.97034e+10 to \
  -12.3605, -0 to \
  -12.3613, -0 to \
  1.17871e+10, 2.97034e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 554 polygon from \
  1.16968e+10, 2.95929e+10 to \
  -12.4096, -0 to \
  -12.4103, -0 to \
  1.16968e+10, 2.95929e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 555 polygon from \
  1.16292e+10, 2.9538e+10 to \
  -12.4586, -0 to \
  -12.4593, -0 to \
  1.16292e+10, 2.9538e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 556 polygon from \
  1.15408e+10, 2.94288e+10 to \
  -12.5077, -0 to \
  -12.5084, -0 to \
  1.15408e+10, 2.94288e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 557 polygon from \
  1.14745e+10, 2.93745e+10 to \
  -12.5567, -0 to \
  -12.5574, -0 to \
  1.14745e+10, 2.93745e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 558 polygon from \
  1.14088e+10, 2.93204e+10 to \
  -12.6058, -0 to \
  -12.6065, -0 to \
  1.14088e+10, 2.93204e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 559 polygon from \
  1.13228e+10, 2.92128e+10 to \
  -12.6548, -0 to \
  -12.6555, -0 to \
  1.13228e+10, 2.92128e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 560 polygon from \
  1.12585e+10, 2.91593e+10 to \
  -12.7039, -0 to \
  -12.7046, -0 to \
  1.12585e+10, 2.91593e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 561 polygon from \
  1.11742e+10, 2.90529e+10 to \
  -12.7529, -0 to \
  -12.7536, -0 to \
  1.11742e+10, 2.90529e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 562 polygon from \
  1.11111e+10, 2.9e+10 to \
  -12.802, -0 to \
  -12.8027, -0 to \
  1.11111e+10, 2.9e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 563 polygon from \
  1.10286e+10, 2.88947e+10 to \
  -12.851, -0 to \
  -12.8517, -0 to \
  1.10286e+10, 2.88947e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 564 polygon from \
  1.09667e+10, 2.88424e+10 to \
  -12.9001, -0 to \
  -12.9008, -0 to \
  1.09667e+10, 2.88424e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 565 polygon from \
  1.09054e+10, 2.87902e+10 to \
  -12.9491, -0 to \
  -12.9498, -0 to \
  1.09054e+10, 2.87902e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 566 polygon from \
  1.08251e+10, 2.86865e+10 to \
  -12.9982, -0 to \
  -12.9989, -0 to \
  1.08251e+10, 2.86865e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 567 polygon from \
  1.0765e+10, 2.86349e+10 to \
  -13.0472, -0 to \
  -13.0479, -0 to \
  1.0765e+10, 2.86349e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 568 polygon from \
  1.06863e+10, 2.85323e+10 to \
  -13.0963, -0 to \
  -13.097, -0 to \
  1.06863e+10, 2.85323e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 569 polygon from \
  1.06274e+10, 2.84812e+10 to \
  -13.1453, -0 to \
  -13.146, -0 to \
  1.06274e+10, 2.84812e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 570 polygon from \
  1.05689e+10, 2.84304e+10 to \
  -13.1944, -0 to \
  -13.1951, -0 to \
  1.05689e+10, 2.84304e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 571 polygon from \
  1.04923e+10, 2.83292e+10 to \
  -13.2434, -0 to \
  -13.2441, -0 to \
  1.04923e+10, 2.83292e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 572 polygon from \
  1.0435e+10, 2.82789e+10 to \
  -13.2925, -0 to \
  -13.2932, -0 to \
  1.0435e+10, 2.82789e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 573 polygon from \
  1.03599e+10, 2.81788e+10 to \
  -13.3415, -0 to \
  -13.3422, -0 to \
  1.03599e+10, 2.81788e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 574 polygon from \
  1.03037e+10, 2.8129e+10 to \
  -13.3906, -0 to \
  -13.3912, -0 to \
  1.03037e+10, 2.8129e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 575 polygon from \
  1.0248e+10, 2.80794e+10 to \
  -13.4396, -0 to \
  -13.4403, -0 to \
  1.0248e+10, 2.80794e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 576 polygon from \
  1.01748e+10, 2.79807e+10 to \
  -13.4887, -0 to \
  -13.4893, -0 to \
  1.01748e+10, 2.79807e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 577 polygon from \
  1.01202e+10, 2.79316e+10 to \
  -13.5377, -0 to \
  -13.5384, -0 to \
  1.01202e+10, 2.79316e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 578 polygon from \
  1.00484e+10, 2.78339e+10 to \
  -13.5868, -0 to \
  -13.5874, -0 to \
  1.00484e+10, 2.78339e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 579 polygon from \
  9.99472e+09, 2.77853e+10 to \
  -13.6358, -0 to \
  -13.6365, -0 to \
  9.99472e+09, 2.77853e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 580 polygon from \
  9.94154e+09, 2.77369e+10 to \
  -13.6849, -0 to \
  -13.6855, -0 to \
  9.94154e+09, 2.77369e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 581 polygon from \
  9.87164e+09, 2.76406e+10 to \
  -13.7339, -0 to \
  -13.7346, -0 to \
  9.87164e+09, 2.76406e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 582 polygon from \
  9.81946e+09, 2.75927e+10 to \
  -13.783, -0 to \
  -13.7836, -0 to \
  9.81946e+09, 2.75927e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 583 polygon from \
  9.76771e+09, 2.7545e+10 to \
  -13.832, -0 to \
  -13.8327, -0 to \
  9.76771e+09, 2.7545e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 584 polygon from \
  9.69964e+09, 2.745e+10 to \
  -13.8811, -0 to \
  -13.8817, -0 to \
  9.69964e+09, 2.745e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 585 polygon from \
  9.64885e+09, 2.74028e+10 to \
  -13.9301, -0 to \
  -13.9308, -0 to \
  9.64885e+09, 2.74028e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 586 polygon from \
  9.59847e+09, 2.73557e+10 to \
  -13.9792, -0 to \
  -13.9798, -0 to \
  9.59847e+09, 2.73557e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 587 polygon from \
  9.53215e+09, 2.7262e+10 to \
  -14.0282, -0 to \
  -14.0289, -0 to \
  9.53215e+09, 2.7262e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 588 polygon from \
  9.4827e+09, 2.72154e+10 to \
  -14.0773, -0 to \
  -14.0779, -0 to \
  9.4827e+09, 2.72154e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 589 polygon from \
  9.41758e+09, 2.71227e+10 to \
  -14.1263, -0 to \
  -14.127, -0 to \
  9.41758e+09, 2.71227e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 590 polygon from \
  9.36903e+09, 2.70765e+10 to \
  -14.1754, -0 to \
  -14.176, -0 to \
  9.36903e+09, 2.70765e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 591 polygon from \
  9.32087e+09, 2.70306e+10 to \
  -14.2244, -0 to \
  -14.2251, -0 to \
  9.32087e+09, 2.70306e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 592 polygon from \
  9.25741e+09, 2.69391e+10 to \
  -14.2735, -0 to \
  -14.2741, -0 to \
  9.25741e+09, 2.69391e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 593 polygon from \
  9.21012e+09, 2.68936e+10 to \
  -14.3225, -0 to \
  -14.3232, -0 to \
  9.21012e+09, 2.68936e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 594 polygon from \
  9.16321e+09, 2.68482e+10 to \
  -14.3716, -0 to \
  -14.3722, -0 to \
  9.16321e+09, 2.68482e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 595 polygon from \
  9.10134e+09, 2.6758e+10 to \
  -14.4206, -0 to \
  -14.4213, -0 to \
  9.10134e+09, 2.6758e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 596 polygon from \
  9.05527e+09, 2.67131e+10 to \
  -14.4697, -0 to \
  -14.4703, -0 to \
  9.05527e+09, 2.67131e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 597 polygon from \
  9.00957e+09, 2.66683e+10 to \
  -14.5187, -0 to \
  -14.5193, -0 to \
  9.00957e+09, 2.66683e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 598 polygon from \
  8.94925e+09, 2.65793e+10 to \
  -14.5678, -0 to \
  -14.5684, -0 to \
  8.94925e+09, 2.65793e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 599 polygon from \
  8.90435e+09, 2.6535e+10 to \
  -14.6168, -0 to \
  -14.6174, -0 to \
  8.90435e+09, 2.6535e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 600 polygon from \
  8.85981e+09, 2.64909e+10 to \
  -14.6659, -0 to \
  -14.6665, -0 to \
  8.85981e+09, 2.64909e+10 front fs empty border lc rgb '#6165' lw 0.200001
set object 601 polygon from \
  -7.85871e+35, -0 to \
  -7.85871e+35, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 602 polygon from \
  -3.92935e+35, -0 to \
  -0.04905, -0 to \
  -3.92935e+35, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 603 polygon from \
  -2.61957e+35, -0 to \
  -0.0980999, -0 to \
  -2.61957e+35, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 604 polygon from \
  -1.96467e+35, -0 to \
  -0.147149, -0 to \
  -1.96467e+35, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 605 polygon from \
  -1.57174e+35, -0 to \
  -0.196199, -0 to \
  -1.57174e+35, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 606 polygon from \
  -1.30978e+35, -0 to \
  -0.245249, -0 to \
  -1.30978e+35, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 607 polygon from \
  -1.12267e+35, -0 to \
  -0.294299, -0 to \
  -1.12267e+35, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 608 polygon from \
  -9.82339e+34, -0 to \
  -0.343349, -0 to \
  -9.82339e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 609 polygon from \
  -8.7319e+34, -0 to \
  -0.392399, -0 to \
  -8.7319e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 610 polygon from \
  -7.85871e+34, -0 to \
  -0.441449, -0 to \
  -7.85871e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 611 polygon from \
  -7.14428e+34, -0 to \
  -0.490499, -0 to \
  -7.14428e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 612 polygon from \
  -6.54893e+34, -0 to \
  -0.539549, -0 to \
  -6.54893e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 613 polygon from \
  -6.04516e+34, -0 to \
  -0.588599, -0 to \
  -6.04516e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 614 polygon from \
  -5.61336e+34, -0 to \
  -0.637649, -0 to \
  -5.61336e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 615 polygon from \
  -5.23914e+34, -0 to \
  -0.686699, -0 to \
  -5.23914e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 616 polygon from \
  -4.91169e+34, -0 to \
  -0.735749, -0 to \
  -4.91169e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 617 polygon from \
  -4.62277e+34, -0 to \
  -0.784799, -0 to \
  -4.62277e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 618 polygon from \
  -4.36595e+34, -0 to \
  -0.833849, -0 to \
  -4.36595e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 619 polygon from \
  -4.13616e+34, -0 to \
  -0.882899, -0 to \
  -4.13616e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 620 polygon from \
  -3.92935e+34, -0 to \
  -0.931949, -0 to \
  -3.92935e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 621 polygon from \
  -3.74224e+34, -0 to \
  -0.980999, -0 to \
  -3.74224e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 622 polygon from \
  -3.57214e+34, -0 to \
  -1.03004, -0 to \
  -3.57214e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 623 polygon from \
  -3.41683e+34, -0 to \
  -1.07909, -0 to \
  -3.41683e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 624 polygon from \
  -3.27446e+34, -0 to \
  -1.12814, -0 to \
  -3.27446e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 625 polygon from \
  -3.14348e+34, -0 to \
  -1.17719, -0 to \
  -3.14348e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 626 polygon from \
  -3.02258e+34, -0 to \
  -1.22624, -0 to \
  -3.02258e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 627 polygon from \
  -2.91063e+34, -0 to \
  -1.27529, -0 to \
  -2.91063e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 628 polygon from \
  -2.80668e+34, -0 to \
  -1.32434, -0 to \
  -2.80668e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 629 polygon from \
  -2.7099e+34, -0 to \
  -1.37339, -0 to \
  -2.7099e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 630 polygon from \
  -2.61957e+34, -0 to \
  -1.42244, -0 to \
  -2.61957e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 631 polygon from \
  -2.53507e+34, -0 to \
  -1.47149, -0 to \
  -2.53507e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 632 polygon from \
  -2.45584e+34, -0 to \
  -1.52054, -0 to \
  -2.45584e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 633 polygon from \
  -2.38142e+34, -0 to \
  -1.56959, -0 to \
  -2.38142e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 634 polygon from \
  -2.31138e+34, -0 to \
  -1.61864, -0 to \
  -2.31138e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 635 polygon from \
  -2.24534e+34, -0 to \
  -1.66769, -0 to \
  -2.24534e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 636 polygon from \
  -2.18297e+34, -0 to \
  -1.71674, -0 to \
  -2.18297e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 637 polygon from \
  -2.12397e+34, -0 to \
  -1.76579, -0 to \
  -2.12397e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 638 polygon from \
  -2.06808e+34, -0 to \
  -1.81484, -0 to \
  -2.06808e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 639 polygon from \
  -2.01505e+34, -0 to \
  -1.86389, -0 to \
  -2.01505e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 640 polygon from \
  -1.96467e+34, -0 to \
  -1.91294, -0 to \
  -1.96467e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 641 polygon from \
  -1.91676e+34, -0 to \
  -1.96199, -0 to \
  -1.91676e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 642 polygon from \
  -1.87112e+34, -0 to \
  -2.01104, -0 to \
  -1.87112e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 643 polygon from \
  -1.8276e+34, -0 to \
  -2.06009, -0 to \
  -1.8276e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 644 polygon from \
  -1.78607e+34, -0 to \
  -2.10914, -0 to \
  -1.78607e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 645 polygon from \
  -1.74638e+34, -0 to \
  -2.15819, -0 to \
  -1.74638e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 646 polygon from \
  -1.70841e+34, -0 to \
  -2.20724, -0 to \
  -1.70841e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 647 polygon from \
  -1.67206e+34, -0 to \
  -2.25629, -0 to \
  -1.67206e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 648 polygon from \
  -1.63723e+34, -0 to \
  -2.30534, -0 to \
  -1.63723e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 649 polygon from \
  -1.60381e+34, -0 to \
  -2.35439, -0 to \
  -1.60381e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 650 polygon from \
  -1.57174e+34, -0 to \
  -2.40344, -0 to \
  -1.57174e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 651 polygon from \
  -1.54092e+34, -0 to \
  -2.45249, -0 to \
  -1.54092e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 652 polygon from \
  -1.51129e+34, -0 to \
  -2.50154, -0 to \
  -1.51129e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 653 polygon from \
  -1.48277e+34, -0 to \
  -2.55059, -0 to \
  -1.48277e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 654 polygon from \
  -1.45531e+34, -0 to \
  -2.59964, -0 to \
  -1.45531e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 655 polygon from \
  -1.42885e+34, -0 to \
  -2.64869, -0 to \
  -1.42885e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 656 polygon from \
  -1.40334e+34, -0 to \
  -2.69774, -0 to \
  -1.40334e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 657 polygon from \
  -1.37872e+34, -0 to \
  -2.74679, -0 to \
  -1.37872e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 658 polygon from \
  -1.35495e+34, -0 to \
  -2.79584, -0 to \
  -1.35495e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 659 polygon from \
  -1.33198e+34, -0 to \
  -2.84489, -0 to \
  -1.33198e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 660 polygon from \
  -1.30978e+34, -0 to \
  -2.89394, -0 to \
  -1.30978e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 661 polygon from \
  -1.28831e+34, -0 to \
  -2.94299, -0 to \
  -1.28831e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 662 polygon from \
  -1.26753e+34, -0 to \
  -2.99204, -0 to \
  -1.26753e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 663 polygon from \
  -1.24741e+34, -0 to \
  -3.04109, -0 to \
  -1.24741e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 664 polygon from \
  -1.22792e+34, -0 to \
  -3.09014, -0 to \
  -1.22792e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 665 polygon from \
  -1.20903e+34, -0 to \
  -3.13919, -0 to \
  -1.20903e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 666 polygon from \
  -1.19071e+34, -0 to \
  -3.18824, -0 to \
  -1.19071e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 667 polygon from \
  -1.17294e+34, -0 to \
  -3.23729, -0 to \
  -1.17294e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 668 polygon from \
  -1.15569e+34, -0 to \
  -3.28634, -0 to \
  -1.15569e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 669 polygon from \
  -1.13894e+34, -0 to \
  -3.33539, -0 to \
  -1.13894e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 670 polygon from \
  -1.12267e+34, -0 to \
  -3.38444, -0 to \
  -1.12267e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 671 polygon from \
  -1.10686e+34, -0 to \
  -3.43349, -0 to \
  -1.10686e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 672 polygon from \
  -1.09148e+34, -0 to \
  -3.48254, -0 to \
  -1.09148e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 673 polygon from \
  -1.07653e+34, -0 to \
  -3.53159, -0 to \
  -1.07653e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 674 polygon from \
  -1.06198e+34, -0 to \
  -3.58064, -0 to \
  -1.06198e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 675 polygon from \
  -1.04782e+34, -0 to \
  -3.62969, -0 to \
  -1.04782e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 676 polygon from \
  -1.03404e+34, -0 to \
  -3.67874, -0 to \
  -1.03404e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 677 polygon from \
  -1.02061e+34, -0 to \
  -3.72779, -0 to \
  -1.02061e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 678 polygon from \
  -1.00752e+34, -0 to \
  -3.77684, -0 to \
  -1.00752e+34, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 679 polygon from \
  -9.94774e+33, -0 to \
  -3.82589, -0 to \
  -9.94774e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 680 polygon from \
  -9.82339e+33, -0 to \
  -3.87494, -0 to \
  -9.82339e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 681 polygon from \
  -9.70212e+33, -0 to \
  -3.92399, -0 to \
  -9.70212e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 682 polygon from \
  -9.5838e+33, -0 to \
  -3.97304, -0 to \
  -9.5838e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 683 polygon from \
  -9.46833e+33, -0 to \
  -4.02209, -0 to \
  -9.46833e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 684 polygon from \
  -9.35561e+33, -0 to \
  -4.07114, -0 to \
  -9.35561e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 685 polygon from \
  -9.24554e+33, -0 to \
  -4.12019, -0 to \
  -9.24554e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 686 polygon from \
  -9.13804e+33, -0 to \
  -4.16924, -0 to \
  -9.13804e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 687 polygon from \
  -9.033e+33, -0 to \
  -4.21829, -0 to \
  -9.033e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 688 polygon from \
  -8.93036e+33, -0 to \
  -4.26734, -0 to \
  -8.93036e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 689 polygon from \
  -8.83001e+33, -0 to \
  -4.31639, -0 to \
  -8.83001e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 690 polygon from \
  -8.7319e+33, -0 to \
  -4.36544, -0 to \
  -8.7319e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 691 polygon from \
  -8.63595e+33, -0 to \
  -4.41449, -0 to \
  -8.63595e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 692 polygon from \
  -8.54208e+33, -0 to \
  -4.46354, -0 to \
  -8.54208e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 693 polygon from \
  -8.45023e+33, -0 to \
  -4.51259, -0 to \
  -8.45023e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 694 polygon from \
  -8.36033e+33, -0 to \
  -4.56164, -0 to \
  -8.36033e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 695 polygon from \
  -8.27233e+33, -0 to \
  -4.61069, -0 to \
  -8.27233e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 696 polygon from \
  -8.18616e+33, -0 to \
  -4.65974, -0 to \
  -8.18616e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 697 polygon from \
  -8.10177e+33, -0 to \
  -4.70879, -0 to \
  -8.10177e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 698 polygon from \
  -8.01909e+33, -0 to \
  -4.75784, -0 to \
  -8.01909e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 699 polygon from \
  -7.93809e+33, -0 to \
  -4.80689, -0 to \
  -7.93809e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 700 polygon from \
  -7.85871e+33, -0 to \
  -4.85594, -0 to \
  -7.85871e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 701 polygon from \
  -7.7809e+33, -0 to \
  -4.90499, -0 to \
  -7.7809e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 702 polygon from \
  -7.70462e+33, -0 to \
  -4.95404, -0 to \
  -7.70462e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 703 polygon from \
  -7.62982e+33, -0 to \
  -5.00309, -0 to \
  -7.62982e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 704 polygon from \
  -7.55645e+33, -0 to \
  -5.05214, -0 to \
  -7.55645e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 705 polygon from \
  -7.48449e+33, -0 to \
  -5.10119, -0 to \
  -7.48449e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 706 polygon from \
  -7.41388e+33, -0 to \
  -5.15024, -0 to \
  -7.41388e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 707 polygon from \
  -7.34459e+33, -0 to \
  -5.19929, -0 to \
  -7.34459e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 708 polygon from \
  -7.27659e+33, -0 to \
  -5.24834, -0 to \
  -7.27659e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 709 polygon from \
  -7.20983e+33, -0 to \
  -5.29739, -0 to \
  -7.20983e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 710 polygon from \
  -7.14428e+33, -0 to \
  -5.34644, -0 to \
  -7.14428e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 711 polygon from \
  -7.07992e+33, -0 to \
  -5.39549, -0 to \
  -7.07992e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 712 polygon from \
  -7.01671e+33, -0 to \
  -5.44454, -0 to \
  -7.01671e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 713 polygon from \
  -6.95461e+33, -0 to \
  -5.49359, -0 to \
  -6.95461e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 714 polygon from \
  -6.89361e+33, -0 to \
  -5.54264, -0 to \
  -6.89361e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 715 polygon from \
  -6.83366e+33, -0 to \
  -5.59169, -0 to \
  -6.83366e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 716 polygon from \
  -6.77475e+33, -0 to \
  -5.64074, -0 to \
  -6.77475e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 717 polygon from \
  -6.71685e+33, -0 to \
  -5.68979, -0 to \
  -6.71685e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 718 polygon from \
  -6.65992e+33, -0 to \
  -5.73884, -0 to \
  -6.65992e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 719 polygon from \
  -6.60396e+33, -0 to \
  -5.78789, -0 to \
  -6.60396e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 720 polygon from \
  -6.54893e+33, -0 to \
  -5.83694, -0 to \
  -6.54893e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 721 polygon from \
  -6.4948e+33, -0 to \
  -5.88599, -0 to \
  -6.4948e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 722 polygon from \
  -6.44157e+33, -0 to \
  -5.93504, -0 to \
  -6.44157e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 723 polygon from \
  -6.3892e+33, -0 to \
  -5.98409, -0 to \
  -6.3892e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 724 polygon from \
  -6.33767e+33, -0 to \
  -6.03314, -0 to \
  -6.33767e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 725 polygon from \
  -6.28697e+33, -0 to \
  -6.08219, -0 to \
  -6.28697e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 726 polygon from \
  -6.23707e+33, -0 to \
  -6.13124, -0 to \
  -6.23707e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 727 polygon from \
  -6.18796e+33, -0 to \
  -6.18029, -0 to \
  -6.18796e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 728 polygon from \
  -6.13962e+33, -0 to \
  -6.22934, -0 to \
  -6.13962e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 729 polygon from \
  -6.09202e+33, -0 to \
  -6.27839, -0 to \
  -6.09202e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 730 polygon from \
  -6.04516e+33, -0 to \
  -6.32744, -0 to \
  -6.04516e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 731 polygon from \
  -5.99902e+33, -0 to \
  -6.37649, -0 to \
  -5.99902e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 732 polygon from \
  -5.95357e+33, -0 to \
  -6.42554, -0 to \
  -5.95357e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 733 polygon from \
  -5.9088e+33, -0 to \
  -6.47459, -0 to \
  -5.9088e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 734 polygon from \
  -5.86471e+33, -0 to \
  -6.52364, -0 to \
  -5.86471e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 735 polygon from \
  -5.82127e+33, -0 to \
  -6.57269, -0 to \
  -5.82127e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 736 polygon from \
  -5.77846e+33, -0 to \
  -6.62174, -0 to \
  -5.77846e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 737 polygon from \
  -5.73628e+33, -0 to \
  -6.67079, -0 to \
  -5.73628e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 738 polygon from \
  -5.69472e+33, -0 to \
  -6.71984, -0 to \
  -5.69472e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 739 polygon from \
  -5.65375e+33, -0 to \
  -6.76889, -0 to \
  -5.65375e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 740 polygon from \
  -5.61336e+33, -0 to \
  -6.81794, -0 to \
  -5.61336e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 741 polygon from \
  -5.57355e+33, -0 to \
  -6.86699, -0 to \
  -5.57355e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 742 polygon from \
  -5.5343e+33, -0 to \
  -6.91604, -0 to \
  -5.5343e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 743 polygon from \
  -5.4956e+33, -0 to \
  -6.96509, -0 to \
  -5.4956e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 744 polygon from \
  -5.45744e+33, -0 to \
  -7.01414, -0 to \
  -5.45744e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 745 polygon from \
  -5.4198e+33, -0 to \
  -7.06319, -0 to \
  -5.4198e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 746 polygon from \
  -5.38268e+33, -0 to \
  -7.11224, -0 to \
  -5.38268e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 747 polygon from \
  -5.34606e+33, -0 to \
  -7.16129, -0 to \
  -5.34606e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 748 polygon from \
  -5.30994e+33, -0 to \
  -7.21034, -0 to \
  -5.30994e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 749 polygon from \
  -5.2743e+33, -0 to \
  -7.25939, -0 to \
  -5.2743e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 750 polygon from \
  -5.23914e+33, -0 to \
  -7.30844, -0 to \
  -5.23914e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 751 polygon from \
  -5.20444e+33, -0 to \
  -7.35749, -0 to \
  -5.20444e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 752 polygon from \
  -5.1702e+33, -0 to \
  -7.40654, -0 to \
  -5.1702e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 753 polygon from \
  -5.13641e+33, -0 to \
  -7.45559, -0 to \
  -5.13641e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 754 polygon from \
  -5.10306e+33, -0 to \
  -7.50464, -0 to \
  -5.10306e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 755 polygon from \
  -5.07014e+33, -0 to \
  -7.55369, -0 to \
  -5.07014e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 756 polygon from \
  -5.03763e+33, -0 to \
  -7.60274, -0 to \
  -5.03763e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 757 polygon from \
  -5.00555e+33, -0 to \
  -7.65179, -0 to \
  -5.00555e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 758 polygon from \
  -4.97387e+33, -0 to \
  -7.70084, -0 to \
  -4.97387e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 759 polygon from \
  -4.94258e+33, -0 to \
  -7.74989, -0 to \
  -4.94258e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 760 polygon from \
  -4.91169e+33, -0 to \
  -7.79894, -0 to \
  -4.91169e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 761 polygon from \
  -4.88119e+33, -0 to \
  -7.84799, -0 to \
  -4.88119e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 762 polygon from \
  -4.85106e+33, -0 to \
  -7.89704, -0 to \
  -4.85106e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 763 polygon from \
  -4.82129e+33, -0 to \
  -7.94609, -0 to \
  -4.82129e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 764 polygon from \
  -4.7919e+33, -0 to \
  -7.99514, -0 to \
  -4.7919e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 765 polygon from \
  -4.76285e+33, -0 to \
  -8.04419, -0 to \
  -4.76285e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 766 polygon from \
  -4.73416e+33, -0 to \
  -8.09324, -0 to \
  -4.73416e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 767 polygon from \
  -4.70581e+33, -0 to \
  -8.14229, -0 to \
  -4.70581e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 768 polygon from \
  -4.6778e+33, -0 to \
  -8.19134, -0 to \
  -4.6778e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 769 polygon from \
  -4.65012e+33, -0 to \
  -8.24039, -0 to \
  -4.65012e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 770 polygon from \
  -4.62277e+33, -0 to \
  -8.28944, -0 to \
  -4.62277e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 771 polygon from \
  -4.59574e+33, -0 to \
  -8.33849, -0 to \
  -4.59574e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 772 polygon from \
  -4.56902e+33, -0 to \
  -8.38754, -0 to \
  -4.56902e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 773 polygon from \
  -4.54261e+33, -0 to \
  -8.43659, -0 to \
  -4.54261e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 774 polygon from \
  -4.5165e+33, -0 to \
  -8.48564, -0 to \
  -4.5165e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 775 polygon from \
  -4.49069e+33, -0 to \
  -8.53469, -0 to \
  -4.49069e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 776 polygon from \
  -4.46518e+33, -0 to \
  -8.58374, -0 to \
  -4.46518e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 777 polygon from \
  -4.43995e+33, -0 to \
  -8.63279, -0 to \
  -4.43995e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 778 polygon from \
  -4.415e+33, -0 to \
  -8.68184, -0 to \
  -4.415e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 779 polygon from \
  -4.39034e+33, -0 to \
  -8.73089, -0 to \
  -4.39034e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 780 polygon from \
  -4.36595e+33, -0 to \
  -8.77994, -0 to \
  -4.36595e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 781 polygon from \
  -4.34183e+33, -0 to \
  -8.82899, -0 to \
  -4.34183e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 782 polygon from \
  -4.31797e+33, -0 to \
  -8.87804, -0 to \
  -4.31797e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 783 polygon from \
  -4.29438e+33, -0 to \
  -8.92709, -0 to \
  -4.29438e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 784 polygon from \
  -4.27104e+33, -0 to \
  -8.97614, -0 to \
  -4.27104e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 785 polygon from \
  -4.24795e+33, -0 to \
  -9.02519, -0 to \
  -4.24795e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 786 polygon from \
  -4.22511e+33, -0 to \
  -9.07424, -0 to \
  -4.22511e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 787 polygon from \
  -4.20252e+33, -0 to \
  -9.12329, -0 to \
  -4.20252e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 788 polygon from \
  -4.18016e+33, -0 to \
  -9.17234, -0 to \
  -4.18016e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 789 polygon from \
  -4.15805e+33, -0 to \
  -9.22139, -0 to \
  -4.15805e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 790 polygon from \
  -4.13616e+33, -0 to \
  -9.27044, -0 to \
  -4.13616e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 791 polygon from \
  -4.11451e+33, -0 to \
  -9.31949, -0 to \
  -4.11451e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 792 polygon from \
  -4.09308e+33, -0 to \
  -9.36854, -0 to \
  -4.09308e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 793 polygon from \
  -4.07187e+33, -0 to \
  -9.41759, -0 to \
  -4.07187e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 794 polygon from \
  -4.05088e+33, -0 to \
  -9.46664, -0 to \
  -4.05088e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 795 polygon from \
  -4.03011e+33, -0 to \
  -9.51569, -0 to \
  -4.03011e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 796 polygon from \
  -4.00954e+33, -0 to \
  -9.56474, -0 to \
  -4.00954e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 797 polygon from \
  -3.98919e+33, -0 to \
  -9.61379, -0 to \
  -3.98919e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 798 polygon from \
  -3.96904e+33, -0 to \
  -9.66284, -0 to \
  -3.96904e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 799 polygon from \
  -3.9491e+33, -0 to \
  -9.71189, -0 to \
  -3.9491e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 800 polygon from \
  -3.92935e+33, -0 to \
  -9.76094, -0 to \
  -3.92935e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 801 polygon from \
  -3.9098e+33, -0 to \
  -9.80999, -0 to \
  -3.9098e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 802 polygon from \
  -3.89045e+33, -0 to \
  -9.85904, -0 to \
  -3.89045e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 803 polygon from \
  -3.87128e+33, -0 to \
  -9.90809, -0 to \
  -3.87128e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 804 polygon from \
  -3.85231e+33, -0 to \
  -9.95714, -0 to \
  -3.85231e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 805 polygon from \
  -3.83352e+33, -0 to \
  -10.0061, -0 to \
  -3.83352e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 806 polygon from \
  -3.81491e+33, -0 to \
  -10.0552, -0 to \
  -3.81491e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 807 polygon from \
  -3.79648e+33, -0 to \
  -10.1042, -0 to \
  -3.79648e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 808 polygon from \
  -3.77822e+33, -0 to \
  -10.1533, -0 to \
  -3.77822e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 809 polygon from \
  -3.76015e+33, -0 to \
  -10.2023, -0 to \
  -3.76015e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 810 polygon from \
  -3.74224e+33, -0 to \
  -10.2514, -0 to \
  -3.74224e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 811 polygon from \
  -3.72451e+33, -0 to \
  -10.3004, -0 to \
  -3.72451e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 812 polygon from \
  -3.70694e+33, -0 to \
  -10.3495, -0 to \
  -3.70694e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 813 polygon from \
  -3.68953e+33, -0 to \
  -10.3985, -0 to \
  -3.68953e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 814 polygon from \
  -3.67229e+33, -0 to \
  -10.4476, -0 to \
  -3.67229e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 815 polygon from \
  -3.65521e+33, -0 to \
  -10.4966, -0 to \
  -3.65521e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 816 polygon from \
  -3.63829e+33, -0 to \
  -10.5457, -0 to \
  -3.63829e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 817 polygon from \
  -3.62152e+33, -0 to \
  -10.5947, -0 to \
  -3.62152e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 818 polygon from \
  -3.60491e+33, -0 to \
  -10.6438, -0 to \
  -3.60491e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 819 polygon from \
  -3.58845e+33, -0 to \
  -10.6928, -0 to \
  -3.58845e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 820 polygon from \
  -3.57214e+33, -0 to \
  -10.7419, -0 to \
  -3.57214e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 821 polygon from \
  -3.55598e+33, -0 to \
  -10.7909, -0 to \
  -3.55598e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 822 polygon from \
  -3.53996e+33, -0 to \
  -10.84, -0 to \
  -3.53996e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 823 polygon from \
  -3.52408e+33, -0 to \
  -10.889, -0 to \
  -3.52408e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 824 polygon from \
  -3.50835e+33, -0 to \
  -10.9381, -0 to \
  -3.50835e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 825 polygon from \
  -3.49276e+33, -0 to \
  -10.9871, -0 to \
  -3.49276e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 826 polygon from \
  -3.4773e+33, -0 to \
  -11.0362, -0 to \
  -3.4773e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 827 polygon from \
  -3.46198e+33, -0 to \
  -11.0852, -0 to \
  -3.46198e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 828 polygon from \
  -3.4468e+33, -0 to \
  -11.1343, -0 to \
  -3.4468e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 829 polygon from \
  -3.43175e+33, -0 to \
  -11.1833, -0 to \
  -3.43175e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 830 polygon from \
  -3.41683e+33, -0 to \
  -11.2324, -0 to \
  -3.41683e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 831 polygon from \
  -3.40204e+33, -0 to \
  -11.2814, -0 to \
  -3.40204e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 832 polygon from \
  -3.38737e+33, -0 to \
  -11.3305, -0 to \
  -3.38737e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 833 polygon from \
  -3.37284e+33, -0 to \
  -11.3795, -0 to \
  -3.37284e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 834 polygon from \
  -3.35842e+33, -0 to \
  -11.4286, -0 to \
  -3.35842e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 835 polygon from \
  -3.34413e+33, -0 to \
  -11.4776, -0 to \
  -3.34413e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 836 polygon from \
  -3.32996e+33, -0 to \
  -11.5267, -0 to \
  -3.32996e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 837 polygon from \
  -3.31591e+33, -0 to \
  -11.5757, -0 to \
  -3.31591e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 838 polygon from \
  -3.30198e+33, -0 to \
  -11.6248, -0 to \
  -3.30198e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 839 polygon from \
  -3.28816e+33, -0 to \
  -11.6738, -0 to \
  -3.28816e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 840 polygon from \
  -3.27446e+33, -0 to \
  -11.7229, -0 to \
  -3.27446e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 841 polygon from \
  -3.26087e+33, -0 to \
  -11.7719, -0 to \
  -3.26087e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 842 polygon from \
  -3.2474e+33, -0 to \
  -11.821, -0 to \
  -3.2474e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 843 polygon from \
  -3.23404e+33, -0 to \
  -11.87, -0 to \
  -3.23404e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 844 polygon from \
  -3.22078e+33, -0 to \
  -11.9191, -0 to \
  -3.22078e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 845 polygon from \
  -3.20763e+33, -0 to \
  -11.9681, -0 to \
  -3.20763e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 846 polygon from \
  -3.1946e+33, -0 to \
  -12.0172, -0 to \
  -3.1946e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 847 polygon from \
  -3.18166e+33, -0 to \
  -12.0662, -0 to \
  -3.18166e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 848 polygon from \
  -3.16883e+33, -0 to \
  -12.1153, -0 to \
  -3.16883e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 849 polygon from \
  -3.15611e+33, -0 to \
  -12.1643, -0 to \
  -3.15611e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 850 polygon from \
  -3.14348e+33, -0 to \
  -12.2134, -0 to \
  -3.14348e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 851 polygon from \
  -3.13096e+33, -0 to \
  -12.2624, -0 to \
  -3.13096e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 852 polygon from \
  -3.11853e+33, -0 to \
  -12.3115, -0 to \
  -3.11853e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 853 polygon from \
  -3.10621e+33, -0 to \
  -12.3605, -0 to \
  -3.10621e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 854 polygon from \
  -3.09398e+33, -0 to \
  -12.4096, -0 to \
  -3.09398e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 855 polygon from \
  -3.08184e+33, -0 to \
  -12.4586, -0 to \
  -3.08184e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 856 polygon from \
  -3.06981e+33, -0 to \
  -12.5077, -0 to \
  -3.06981e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 857 polygon from \
  -3.05786e+33, -0 to \
  -12.5567, -0 to \
  -3.05786e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 858 polygon from \
  -3.04601e+33, -0 to \
  -12.6058, -0 to \
  -3.04601e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 859 polygon from \
  -3.03425e+33, -0 to \
  -12.6548, -0 to \
  -3.03425e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 860 polygon from \
  -3.02258e+33, -0 to \
  -12.7039, -0 to \
  -3.02258e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 861 polygon from \
  -3.011e+33, -0 to \
  -12.7529, -0 to \
  -3.011e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 862 polygon from \
  -2.99951e+33, -0 to \
  -12.802, -0 to \
  -2.99951e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 863 polygon from \
  -2.9881e+33, -0 to \
  -12.851, -0 to \
  -2.9881e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 864 polygon from \
  -2.97678e+33, -0 to \
  -12.9001, -0 to \
  -2.97678e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 865 polygon from \
  -2.96555e+33, -0 to \
  -12.9491, -0 to \
  -2.96555e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 866 polygon from \
  -2.9544e+33, -0 to \
  -12.9982, -0 to \
  -2.9544e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 867 polygon from \
  -2.94333e+33, -0 to \
  -13.0472, -0 to \
  -2.94333e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 868 polygon from \
  -2.93235e+33, -0 to \
  -13.0963, -0 to \
  -2.93235e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 869 polygon from \
  -2.92145e+33, -0 to \
  -13.1453, -0 to \
  -2.92145e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 870 polygon from \
  -2.91063e+33, -0 to \
  -13.1944, -0 to \
  -2.91063e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 871 polygon from \
  -2.89989e+33, -0 to \
  -13.2434, -0 to \
  -2.89989e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 872 polygon from \
  -2.88923e+33, -0 to \
  -13.2925, -0 to \
  -2.88923e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 873 polygon from \
  -2.87865e+33, -0 to \
  -13.3415, -0 to \
  -2.87865e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 874 polygon from \
  -2.86814e+33, -0 to \
  -13.3906, -0 to \
  -2.86814e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 875 polygon from \
  -2.85771e+33, -0 to \
  -13.4396, -0 to \
  -2.85771e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 876 polygon from \
  -2.84736e+33, -0 to \
  -13.4887, -0 to \
  -2.84736e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 877 polygon from \
  -2.83708e+33, -0 to \
  -13.5377, -0 to \
  -2.83708e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 878 polygon from \
  -2.82687e+33, -0 to \
  -13.5868, -0 to \
  -2.82687e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 879 polygon from \
  -2.81674e+33, -0 to \
  -13.6358, -0 to \
  -2.81674e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 880 polygon from \
  -2.80668e+33, -0 to \
  -13.6849, -0 to \
  -2.80668e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 881 polygon from \
  -2.79669e+33, -0 to \
  -13.7339, -0 to \
  -2.79669e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 882 polygon from \
  -2.78677e+33, -0 to \
  -13.783, -0 to \
  -2.78677e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 883 polygon from \
  -2.77693e+33, -0 to \
  -13.832, -0 to \
  -2.77693e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 884 polygon from \
  -2.76715e+33, -0 to \
  -13.8811, -0 to \
  -2.76715e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 885 polygon from \
  -2.75744e+33, -0 to \
  -13.9301, -0 to \
  -2.75744e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 886 polygon from \
  -2.7478e+33, -0 to \
  -13.9792, -0 to \
  -2.7478e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 887 polygon from \
  -2.73822e+33, -0 to \
  -14.0282, -0 to \
  -2.73822e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 888 polygon from \
  -2.72872e+33, -0 to \
  -14.0773, -0 to \
  -2.72872e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 889 polygon from \
  -2.71927e+33, -0 to \
  -14.1263, -0 to \
  -2.71927e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 890 polygon from \
  -2.7099e+33, -0 to \
  -14.1754, -0 to \
  -2.7099e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 891 polygon from \
  -2.70059e+33, -0 to \
  -14.2244, -0 to \
  -2.70059e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 892 polygon from \
  -2.69134e+33, -0 to \
  -14.2735, -0 to \
  -2.69134e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 893 polygon from \
  -2.68215e+33, -0 to \
  -14.3225, -0 to \
  -2.68215e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 894 polygon from \
  -2.67303e+33, -0 to \
  -14.3716, -0 to \
  -2.67303e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 895 polygon from \
  -2.66397e+33, -0 to \
  -14.4206, -0 to \
  -2.66397e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 896 polygon from \
  -2.65497e+33, -0 to \
  -14.4697, -0 to \
  -2.65497e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 897 polygon from \
  -2.64603e+33, -0 to \
  -14.5187, -0 to \
  -2.64603e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 898 polygon from \
  -2.63715e+33, -0 to \
  -14.5678, -0 to \
  -2.63715e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 899 polygon from \
  -2.62833e+33, -0 to \
  -14.6168, -0 to \
  -2.62833e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 900 polygon from \
  -2.61957e+33, -0 to \
  -14.6659, -0 to \
  -2.61957e+33, -0 front fs empty border lc rgb '#6165' lw 0.200001
set object 901 polygon from \
  -0.000123033, 3.27185e+17 to \
  5.89404e+35, 3.27185e+17 to \
  5.89404e+35, 0 to \
  -0.000123033, -0 to \
  -0.000123033, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 902 polygon from \
  -0.098223, 3.27185e+17 to \
  -0.04905, -0 to \
  -0.098223, -0 to \
  -0.098223, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 903 polygon from \
  -0.196323, 3.27185e+17 to \
  -0.0980999, -0 to \
  -0.196323, -0 to \
  -0.196323, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 904 polygon from \
  -0.294423, 3.27185e+17 to \
  -0.147149, -0 to \
  -0.294423, -0 to \
  -0.294423, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 905 polygon from \
  -0.392523, 3.27185e+17 to \
  -0.196199, -0 to \
  -0.392523, -0 to \
  -0.392523, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 906 polygon from \
  -0.490623, 3.27185e+17 to \
  -0.245249, -0 to \
  -0.490623, -0 to \
  -0.490623, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 907 polygon from \
  -0.588723, 3.27185e+17 to \
  -0.294299, -0 to \
  -0.588723, -0 to \
  -0.588723, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 908 polygon from \
  -0.686823, 3.27185e+17 to \
  -0.343349, -0 to \
  -0.686823, -0 to \
  -0.686823, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 909 polygon from \
  -0.784923, 3.27185e+17 to \
  -0.392399, -0 to \
  -0.784923, -0 to \
  -0.784923, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 910 polygon from \
  -0.883023, 3.27185e+17 to \
  -0.441449, -0 to \
  -0.883023, -0 to \
  -0.883023, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 911 polygon from \
  -0.981123, 3.27185e+17 to \
  -0.490499, -0 to \
  -0.981123, -0 to \
  -0.981123, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 912 polygon from \
  -1.07922, 3.27185e+17 to \
  -0.539549, -0 to \
  -1.07922, -0 to \
  -1.07922, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 913 polygon from \
  -1.17732, 3.27185e+17 to \
  -0.588599, -0 to \
  -1.17732, -0 to \
  -1.17732, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 914 polygon from \
  -1.27542, 3.27185e+17 to \
  -0.637649, -0 to \
  -1.27542, -0 to \
  -1.27542, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 915 polygon from \
  -1.37352, 3.27185e+17 to \
  -0.686699, -0 to \
  -1.37352, -0 to \
  -1.37352, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 916 polygon from \
  -1.47162, 3.27185e+17 to \
  6.93417e+32, 1.04013e+32 to \
  -0.735749, -0 to \
  -1.47162, -0 to \
  -1.47162, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 917 polygon from \
  -1.56972, 3.27185e+17 to \
  5.61337e+32, 8.9814e+31 to \
  -0.784799, -0 to \
  -1.56972, -0 to \
  -1.56972, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 918 polygon from \
  -1.66782, 3.27185e+17 to \
  4.9117e+32, 8.34989e+31 to \
  -0.833849, -0 to \
  -1.66782, -0 to \
  -1.66782, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 919 polygon from \
  -1.76592, 3.27185e+17 to \
  4.36596e+32, 7.85872e+31 to \
  -0.882899, -0 to \
  -1.76592, -0 to \
  -1.76592, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 920 polygon from \
  -1.86402, 3.27185e+17 to \
  3.80261e+32, 7.22495e+31 to \
  -0.931949, -0 to \
  -1.86402, -0 to \
  -1.86402, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 921 polygon from \
  -1.96212, 3.27185e+17 to \
  3.46709e+32, 6.93417e+31 to \
  -0.980999, -0 to \
  -1.96212, -0 to \
  -1.96212, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 922 polygon from \
  -2.06022, 3.27185e+17 to \
  3.10213e+32, 6.51447e+31 to \
  -1.03004, -0 to \
  -2.06022, -0 to \
  -2.06022, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 923 polygon from \
  -2.15832, 3.27185e+17 to \
  2.87515e+32, 6.32531e+31 to \
  -1.07909, -0 to \
  -2.15832, -0 to \
  -2.15832, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 924 polygon from \
  -2.25642, 3.27185e+17 to \
  2.67911e+32, 6.16195e+31 to \
  -1.12814, -0 to \
  -2.25642, -0 to \
  -2.25642, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 925 polygon from \
  -2.35452, 3.27185e+17 to \
  2.50811e+32, 6.01945e+31 to \
  -1.17719, -0 to \
  -2.35452, -0 to \
  -2.35452, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 926 polygon from \
  -2.45262, 3.27185e+17 to \
  2.40573e+32, 6.01433e+31 to \
  -1.22624, -0 to \
  -2.45262, -0 to \
  -2.45262, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 927 polygon from \
  -2.55072, 3.27185e+17 to \
  2.26694e+32, 5.89404e+31 to \
  -1.27529, -0 to \
  -2.55072, -0 to \
  -2.55072, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 928 polygon from \
  -2.64882, 3.27185e+17 to \
  2.03243e+32, 5.48756e+31 to \
  -1.32434, -0 to \
  -2.64882, -0 to \
  -2.64882, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 929 polygon from \
  -2.74692, 3.27185e+17 to \
  1.84189e+32, 5.15729e+31 to \
  -1.37339, -0 to \
  -2.74692, -0 to \
  -2.74692, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 930 polygon from \
  -2.84502, 3.27185e+17 to \
  1.68402e+32, 4.88364e+31 to \
  -1.42244, -0 to \
  -2.84502, -0 to \
  -2.84502, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 931 polygon from \
  -2.94312, 3.27185e+17 to \
  1.55107e+32, 4.65319e+31 to \
  -1.47149, -0 to \
  -2.94312, -0 to \
  -2.94312, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 932 polygon from \
  -3.04122, 3.27185e+17 to \
  1.40335e+32, 4.35037e+31 to \
  -1.52054, -0 to \
  -3.04122, -0 to \
  -3.04122, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 933 polygon from \
  -3.13932, 3.27185e+17 to \
  1.30979e+32, 4.19132e+31 to \
  -1.56959, -0 to \
  -3.13932, -0 to \
  -3.13932, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 934 polygon from \
  -3.23742, 3.27185e+17 to \
  1.22793e+32, 4.05216e+31 to \
  -1.61864, -0 to \
  -3.23742, -0 to \
  -3.23742, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 935 polygon from \
  -3.33552, 3.27185e+17 to \
  1.13347e+32, 3.8538e+31 to \
  -1.66769, -0 to \
  -3.33552, -0 to \
  -3.33552, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 936 polygon from \
  -3.43362, 3.27185e+17 to \
  1.07165e+32, 3.75076e+31 to \
  -1.71674, -0 to \
  -3.43362, -0 to \
  -3.43362, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 937 polygon from \
  -3.53172, 3.27185e+17 to \
  1.01622e+32, 3.65837e+31 to \
  -1.76579, -0 to \
  -3.53172, -0 to \
  -3.53172, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 938 polygon from \
  -3.62982, 3.27185e+17 to \
  9.50652e+31, 3.51741e+31 to \
  -1.81484, -0 to \
  -3.62982, -0 to \
  -3.62982, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 939 polygon from \
  -3.72792, 3.27185e+17 to \
  9.06776e+31, 3.44575e+31 to \
  -1.86389, -0 to \
  -3.72792, -0 to \
  -3.72792, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 940 polygon from \
  -3.82602, 3.27185e+17 to \
  8.54209e+31, 3.33142e+31 to \
  -1.91294, -0 to \
  -3.82602, -0 to \
  -3.82602, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 941 polygon from \
  -3.92412, 3.27185e+17 to \
  8.18617e+31, 3.27447e+31 to \
  -1.96199, -0 to \
  -3.92412, -0 to \
  -3.92412, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 942 polygon from \
  -4.02222, 3.27185e+17 to \
  7.75532e+31, 3.17968e+31 to \
  -2.01104, -0 to \
  -4.02222, -0 to \
  -4.02222, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 943 polygon from \
  -4.12032, 3.27185e+17 to \
  7.36755e+31, 3.09437e+31 to \
  -2.06009, -0 to \
  -4.12032, -0 to \
  -4.12032, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 944 polygon from \
  -4.21842, 3.27185e+17 to \
  7.10126e+31, 3.05354e+31 to \
  -2.10914, -0 to \
  -4.21842, -0 to \
  -4.21842, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 945 polygon from \
  -4.31652, 3.27185e+17 to \
  6.77476e+31, 2.9809e+31 to \
  -2.15819, -0 to \
  -4.31652, -0 to \
  -4.31652, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 946 polygon from \
  -4.41462, 3.27185e+17 to \
  6.47697e+31, 2.91464e+31 to \
  -2.20724, -0 to \
  -4.41462, -0 to \
  -4.41462, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 947 polygon from \
  -4.51272, 3.27185e+17 to \
  6.20426e+31, 2.85396e+31 to \
  -2.25629, -0 to \
  -4.51272, -0 to \
  -4.51272, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 948 polygon from \
  -4.61082, 3.27185e+17 to \
  6.01433e+31, 2.82674e+31 to \
  -2.30534, -0 to \
  -4.61082, -0 to \
  -4.61082, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 949 polygon from \
  -4.70892, 3.27185e+17 to \
  5.83569e+31, 2.80113e+31 to \
  -2.35439, -0 to \
  -4.70892, -0 to \
  -4.70892, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 950 polygon from \
  -4.80702, 3.27185e+17 to \
  5.66735e+31, 2.777e+31 to \
  -2.40344, -0 to \
  -4.80702, -0 to \
  -4.80702, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 951 polygon from \
  -4.90512, 3.27185e+17 to \
  5.56042e+31, 2.78021e+31 to \
  -2.45249, -0 to \
  -4.90512, -0 to \
  -4.90512, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 952 polygon from \
  -5.00322, 3.27185e+17 to \
  5.35822e+31, 2.7327e+31 to \
  -2.50154, -0 to \
  -5.00322, -0 to \
  -5.00322, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 953 polygon from \
  -5.10132, 3.27185e+17 to \
  5.08107e+31, 2.64216e+31 to \
  -2.55059, -0 to \
  -5.10132, -0 to \
  -5.10132, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 954 polygon from \
  -5.19942, 3.27185e+17 to \
  4.83118e+31, 2.56053e+31 to \
  -2.59964, -0 to \
  -5.19942, -0 to \
  -5.19942, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 955 polygon from \
  -5.29752, 3.27185e+17 to \
  4.60472e+31, 2.48655e+31 to \
  -2.64869, -0 to \
  -5.29752, -0 to \
  -5.29752, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 956 polygon from \
  -5.39562, 3.27185e+17 to \
  4.39854e+31, 2.4192e+31 to \
  -2.69774, -0 to \
  -5.39562, -0 to \
  -5.39562, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 957 polygon from \
  -5.49372, 3.27185e+17 to \
  4.21003e+31, 2.35762e+31 to \
  -2.74679, -0 to \
  -5.49372, -0 to \
  -5.49372, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 958 polygon from \
  -5.59182, 3.27185e+17 to \
  4.03702e+31, 2.3011e+31 to \
  -2.79584, -0 to \
  -5.59182, -0 to \
  -5.59182, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 959 polygon from \
  -5.68992, 3.27185e+17 to \
  3.87766e+31, 2.24905e+31 to \
  -2.84489, -0 to \
  -5.68992, -0 to \
  -5.68992, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 960 polygon from \
  -5.78802, 3.27185e+17 to \
  3.73041e+31, 2.20094e+31 to \
  -2.89394, -0 to \
  -5.78802, -0 to \
  -5.78802, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 961 polygon from \
  -5.88612, 3.27185e+17 to \
  3.59393e+31, 2.15636e+31 to \
  -2.94299, -0 to \
  -5.88612, -0 to \
  -5.88612, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 962 polygon from \
  -5.98422, 3.27185e+17 to \
  3.42677e+31, 2.09033e+31 to \
  -2.99204, -0 to \
  -5.98422, -0 to \
  -5.98422, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 963 polygon from \
  -6.08232, 3.27185e+17 to \
  3.31126e+31, 2.05298e+31 to \
  -3.04109, -0 to \
  -6.08232, -0 to \
  -6.08232, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 964 polygon from \
  -6.18042, 3.27185e+17 to \
  3.20329e+31, 2.01807e+31 to \
  -3.09014, -0 to \
  -6.18042, -0 to \
  -6.18042, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 965 polygon from \
  -6.27852, 3.27185e+17 to \
  3.10213e+31, 1.98537e+31 to \
  -3.13919, -0 to \
  -6.27852, -0 to \
  -6.27852, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 966 polygon from \
  -6.37662, 3.27185e+17 to \
  2.97679e+31, 1.93492e+31 to \
  -3.18824, -0 to \
  -6.37662, -0 to \
  -6.37662, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 967 polygon from \
  -6.47472, 3.27185e+17 to \
  2.88924e+31, 1.9069e+31 to \
  -3.23729, -0 to \
  -6.47472, -0 to \
  -6.47472, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 968 polygon from \
  -6.57282, 3.27185e+17 to \
  2.80669e+31, 1.88048e+31 to \
  -3.28634, -0 to \
  -6.57282, -0 to \
  -6.57282, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 969 polygon from \
  -6.67092, 3.27185e+17 to \
  2.70369e+31, 1.83851e+31 to \
  -3.33539, -0 to \
  -6.67092, -0 to \
  -6.67092, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 970 polygon from \
  -6.76902, 3.27185e+17 to \
  2.63127e+31, 1.81558e+31 to \
  -3.38444, -0 to \
  -6.76902, -0 to \
  -6.76902, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 971 polygon from \
  -6.86712, 3.27185e+17 to \
  2.56263e+31, 1.79384e+31 to \
  -3.43349, -0 to \
  -6.86712, -0 to \
  -6.86712, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 972 polygon from \
  -6.96522, 3.27185e+17 to \
  2.47649e+31, 1.75831e+31 to \
  -3.48254, -0 to \
  -6.96522, -0 to \
  -6.96522, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 973 polygon from \
  -7.06332, 3.27185e+17 to \
  2.41559e+31, 1.73923e+31 to \
  -3.53159, -0 to \
  -7.06332, -0 to \
  -7.06332, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 974 polygon from \
  -7.16142, 3.27185e+17 to \
  2.33891e+31, 1.7074e+31 to \
  -3.58064, -0 to \
  -7.16142, -0 to \
  -7.16142, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 975 polygon from \
  -7.25952, 3.27185e+17 to \
  2.28452e+31, 1.69054e+31 to \
  -3.62969, -0 to \
  -7.25952, -0 to \
  -7.25952, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 976 polygon from \
  -7.35762, 3.27185e+17 to \
  2.21581e+31, 1.66186e+31 to \
  -3.67874, -0 to \
  -7.35762, -0 to \
  -7.35762, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 977 polygon from \
  -7.45572, 3.27185e+17 to \
  2.16693e+31, 1.64687e+31 to \
  -3.72779, -0 to \
  -7.45572, -0 to \
  -7.45572, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 978 polygon from \
  -7.55382, 3.27185e+17 to \
  2.10502e+31, 1.62087e+31 to \
  -3.77684, -0 to \
  -7.55382, -0 to \
  -7.55382, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 979 polygon from \
  -7.65192, 3.27185e+17 to \
  2.06086e+31, 1.60747e+31 to \
  -3.82589, -0 to \
  -7.65192, -0 to \
  -7.65192, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 980 polygon from \
  -7.75002, 3.27185e+17 to \
  2.00478e+31, 1.58378e+31 to \
  -3.87494, -0 to \
  -7.75002, -0 to \
  -7.75002, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 981 polygon from \
  -7.84812, 3.27185e+17 to \
  1.96468e+31, 1.57175e+31 to \
  -3.92399, -0 to \
  -7.84812, -0 to \
  -7.84812, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 982 polygon from \
  -7.94622, 3.27185e+17 to \
  1.91365e+31, 1.55006e+31 to \
  -3.97304, -0 to \
  -7.94622, -0 to \
  -7.94622, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 983 polygon from \
  -8.04432, 3.27185e+17 to \
  1.86521e+31, 1.52947e+31 to \
  -4.02209, -0 to \
  -8.04432, -0 to \
  -8.04432, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 984 polygon from \
  -8.14242, 3.27185e+17 to \
  1.83045e+31, 1.51928e+31 to \
  -4.07114, -0 to \
  -8.14242, -0 to \
  -8.14242, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 985 polygon from \
  -8.24052, 3.27185e+17 to \
  1.78608e+31, 1.50031e+31 to \
  -4.12019, -0 to \
  -8.24052, -0 to \
  -8.24052, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 986 polygon from \
  -8.33862, 3.27185e+17 to \
  1.7438e+31, 1.48223e+31 to \
  -4.16924, -0 to \
  -8.33862, -0 to \
  -8.33862, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 987 polygon from \
  -8.43672, 3.27185e+17 to \
  1.71339e+31, 1.47351e+31 to \
  -4.21829, -0 to \
  -8.43672, -0 to \
  -8.43672, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 988 polygon from \
  -8.53482, 3.27185e+17 to \
  1.67445e+31, 1.45677e+31 to \
  -4.26734, -0 to \
  -8.53482, -0 to \
  -8.53482, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 989 polygon from \
  -8.63292, 3.27185e+17 to \
  1.63724e+31, 1.44077e+31 to \
  -4.31639, -0 to \
  -8.63292, -0 to \
  -8.63292, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 990 polygon from \
  -8.73102, 3.27185e+17 to \
  1.60165e+31, 1.42547e+31 to \
  -4.36544, -0 to \
  -8.73102, -0 to \
  -8.73102, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 991 polygon from \
  -8.82912, 3.27185e+17 to \
  1.57595e+31, 1.41836e+31 to \
  -4.41449, -0 to \
  -8.82912, -0 to \
  -8.82912, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 992 polygon from \
  -8.92722, 3.27185e+17 to \
  1.54295e+31, 1.40408e+31 to \
  -4.46354, -0 to \
  -8.92722, -0 to \
  -8.92722, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 993 polygon from \
  -9.02532, 3.27185e+17 to \
  1.5113e+31, 1.39039e+31 to \
  -4.51259, -0 to \
  -9.02532, -0 to \
  -9.02532, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 994 polygon from \
  -9.12342, 3.27185e+17 to \
  1.48092e+31, 1.37726e+31 to \
  -4.56164, -0 to \
  -9.12342, -0 to \
  -9.12342, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 995 polygon from \
  -9.22152, 3.27185e+17 to \
  1.45174e+31, 1.36463e+31 to \
  -4.61069, -0 to \
  -9.22152, -0 to \
  -9.22152, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 996 polygon from \
  -9.31962, 3.27185e+17 to \
  1.42369e+31, 1.3525e+31 to \
  -4.65974, -0 to \
  -9.31962, -0 to \
  -9.31962, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 997 polygon from \
  -9.41772, 3.27185e+17 to \
  1.3967e+31, 1.34083e+31 to \
  -4.70879, -0 to \
  -9.41772, -0 to \
  -9.41772, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 998 polygon from \
  -9.51582, 3.27185e+17 to \
  1.37712e+31, 1.3358e+31 to \
  -4.75784, -0 to \
  -9.51582, -0 to \
  -9.51582, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 999 polygon from \
  -9.61392, 3.27185e+17 to \
  1.35808e+31, 1.33092e+31 to \
  -4.80689, -0 to \
  -9.61392, -0 to \
  -9.61392, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1000 polygon from \
  -9.71202, 3.27185e+17 to \
  1.33956e+31, 1.32616e+31 to \
  -4.85594, -0 to \
  -9.71202, -0 to \
  -9.71202, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1001 polygon from \
  -9.81012, 3.27185e+17 to \
  1.32749e+31, 1.32749e+31 to \
  -4.90499, -0 to \
  -9.81012, -0 to \
  -9.81012, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1002 polygon from \
  -0, 3.27185e+17 to \
  1.31435e+31, 1.32749e+31 to \
  -4.95404, -0 to \
  -9.90822, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1003 polygon from \
  -0, 3.27185e+17 to \
  1.27843e+31, 1.304e+31 to \
  -5.00309, -0 to \
  -10.0063, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1004 polygon from \
  -0, 3.27185e+17 to \
  1.244e+31, 1.28132e+31 to \
  -5.05214, -0 to \
  -10.1044, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1005 polygon from \
  -0, 3.27185e+17 to \
  1.21617e+31, 1.26482e+31 to \
  -5.10119, -0 to \
  -10.2025, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1006 polygon from \
  -0, 3.27185e+17 to \
  1.18426e+31, 1.24347e+31 to \
  -5.15024, -0 to \
  -10.3006, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1007 polygon from \
  1.15842e+31, 1.22793e+31 to \
  -10.3987, -0 to \
  -60.3773, 3.27185e+17 to \
  1.15842e+31, 1.22793e+31 front fs empty border lc rgb '#6165' lw 0.200001
set object 1008 polygon from \
  -0, 3.27185e+17 to \
  1.12879e+31, 1.2078e+31 to \
  -5.24834, -0 to \
  -10.4968, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1009 polygon from \
  -0, 3.27185e+17 to \
  1.10475e+31, 1.19313e+31 to \
  -5.29739, -0 to \
  -10.5949, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1010 polygon from \
  -0, 3.27185e+17 to \
  1.07717e+31, 1.17412e+31 to \
  -5.34644, -0 to \
  -10.693, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1011 polygon from \
  -0, 3.27185e+17 to \
  1.05477e+31, 1.16025e+31 to \
  -5.39549, -0 to \
  -10.7911, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1012 polygon from \
  -0, 3.27185e+17 to \
  1.03307e+31, 1.1467e+31 to \
  -5.44454, -0 to \
  -10.8892, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1013 polygon from \
  -0, 3.27185e+17 to \
  1.00815e+31, 1.12913e+31 to \
  -5.49359, -0 to \
  -10.9873, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1014 polygon from \
  -0, 3.27185e+17 to \
  9.87872e+30, 1.1163e+31 to \
  -5.54264, -0 to \
  -11.0854, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1015 polygon from \
  -0, 3.27185e+17 to \
  9.68204e+30, 1.10376e+31 to \
  -5.59169, -0 to \
  -11.1835, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1016 polygon from \
  -0, 3.27185e+17 to \
  9.49121e+30, 1.09149e+31 to \
  -5.64074, -0 to \
  -11.2816, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1017 polygon from \
  -0, 3.27185e+17 to \
  9.30599e+30, 1.0795e+31 to \
  -5.68979, -0 to \
  -11.3797, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1018 polygon from \
  -0, 3.27185e+17 to \
  9.12616e+30, 1.06777e+31 to \
  -5.73884, -0 to \
  -11.4778, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1019 polygon from \
  -0, 3.27185e+17 to \
  8.95152e+30, 1.05628e+31 to \
  -5.78789, -0 to \
  -11.5759, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1020 polygon from \
  -0, 3.27185e+17 to \
  8.78187e+30, 1.04505e+31 to \
  -5.83694, -0 to \
  -11.674, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1021 polygon from \
  -0, 3.27185e+17 to \
  8.61702e+30, 1.03405e+31 to \
  -5.88599, -0 to \
  -11.7721, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1022 polygon from \
  -0, 3.27185e+17 to \
  8.45679e+30, 1.02328e+31 to \
  -5.93504, -0 to \
  -11.8702, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1023 polygon from \
  -0, 3.27185e+17 to \
  8.301e+30, 1.01273e+31 to \
  -5.98409, -0 to \
  -11.9683, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1024 polygon from \
  -0, 3.27185e+17 to \
  8.1495e+30, 1.00239e+31 to \
  -6.03314, -0 to \
  -12.0664, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1025 polygon from \
  -0, 3.27185e+17 to \
  8.00212e+30, 9.92263e+30 to \
  -6.08219, -0 to \
  -12.1645, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1026 polygon from \
  -0, 3.27185e+17 to \
  7.88501e+30, 9.85626e+30 to \
  -6.13124, -0 to \
  -12.2626, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1027 polygon from \
  -0, 3.27185e+17 to \
  7.74472e+30, 9.75835e+30 to \
  -6.18029, -0 to \
  -12.3607, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1028 polygon from \
  -0, 3.27185e+17 to \
  7.60816e+30, 9.66236e+30 to \
  -6.22934, -0 to \
  -12.4588, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1029 polygon from \
  -0, 3.27185e+17 to \
  7.4752e+30, 9.56825e+30 to \
  -6.27839, -0 to \
  -12.5569, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1030 polygon from \
  -0, 3.27185e+17 to \
  7.36939e+30, 9.50652e+30 to \
  -6.32744, -0 to \
  -12.655, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1031 polygon from \
  -0, 3.27185e+17 to \
  7.24262e+30, 9.4154e+30 to \
  -6.37649, -0 to \
  -12.7531, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1032 polygon from \
  -0, 3.27185e+17 to \
  7.1191e+30, 9.32601e+30 to \
  -6.42554, -0 to \
  -12.8512, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1033 polygon from \
  -0, 3.27185e+17 to \
  7.02073e+30, 9.26736e+30 to \
  -6.47459, -0 to \
  -12.9493, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1034 polygon from \
  -0, 3.27185e+17 to \
  6.90282e+30, 9.18075e+30 to \
  -6.52364, -0 to \
  -13.0474, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1035 polygon from \
  -0, 3.27185e+17 to \
  6.78787e+30, 9.09574e+30 to \
  -6.57269, -0 to \
  -13.1455, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1036 polygon from \
  -0, 3.27185e+17 to \
  6.69625e+30, 9.03994e+30 to \
  -6.62174, -0 to \
  -13.2436, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1037 polygon from \
  -0, 3.27185e+17 to \
  6.58641e+30, 8.95751e+30 to \
  -6.67079, -0 to \
  -13.3417, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1038 polygon from \
  -0, 3.27185e+17 to \
  6.49882e+30, 8.90339e+30 to \
  -6.71984, -0 to \
  -13.4398, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1039 polygon from \
  -0, 3.27185e+17 to \
  6.39378e+30, 8.82342e+30 to \
  -6.76889, -0 to \
  -13.5379, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1040 polygon from \
  -0, 3.27185e+17 to \
  6.31e+30, 8.77089e+30 to \
  -6.81794, -0 to \
  -13.636, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1041 polygon from \
  -0, 3.27185e+17 to \
  6.22786e+30, 8.719e+30 to \
  -6.86699, -0 to \
  -13.7341, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1042 polygon from \
  -0, 3.27185e+17 to \
  6.12928e+30, 8.64229e+30 to \
  -6.91604, -0 to \
  -13.8322, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1043 polygon from \
  -0, 3.27185e+17 to \
  6.05063e+30, 8.5919e+30 to \
  -6.96509, -0 to \
  -13.9303, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1044 polygon from \
  -0, 3.27185e+17 to \
  5.95623e+30, 8.5174e+30 to \
  -7.01414, -0 to \
  -14.0284, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1045 polygon from \
  -0, 3.27185e+17 to \
  5.88087e+30, 8.46845e+30 to \
  -7.06319, -0 to \
  -14.1265, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1046 polygon from \
  -0, 3.27185e+17 to \
  5.80694e+30, 8.42006e+30 to \
  -7.11224, -0 to \
  -14.2246, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1047 polygon from \
  -0, 3.27185e+17 to \
  5.71815e+30, 8.3485e+30 to \
  -7.16129, -0 to \
  -14.3227, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1048 polygon from \
  -0, 3.27185e+17 to \
  5.64726e+30, 8.30147e+30 to \
  -7.21034, -0 to \
  -14.4208, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1049 polygon from \
  -0, 3.27185e+17 to \
  5.57768e+30, 8.25496e+30 to \
  -7.25939, -0 to \
  -14.5189, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1050 polygon from \
  -0, 3.27185e+17 to \
  5.49407e+30, 8.18617e+30 to \
  -7.30844, -0 to \
  -14.617, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1051 polygon from \
  -0, 3.27185e+17 to \
  5.4273e+30, 8.14094e+30 to \
  -7.35749, -0 to \
  -14.7151, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1052 polygon from \
  -0, 3.27185e+17 to \
  5.36173e+30, 8.09621e+30 to \
  -7.40654, -0 to \
  -14.8132, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1053 polygon from \
  -0, 3.27185e+17 to \
  5.29735e+30, 8.05197e+30 to \
  -7.45559, -0 to \
  -14.9113, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1054 polygon from \
  -0, 3.27185e+17 to \
  5.23413e+30, 8.00821e+30 to \
  -7.50464, -0 to \
  -15.0094, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1055 polygon from \
  -0, 3.27185e+17 to \
  5.15809e+30, 7.94345e+30 to \
  -7.55369, -0 to \
  -15.1075, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1056 polygon from \
  -0, 3.27185e+17 to \
  5.09733e+30, 7.90086e+30 to \
  -7.60274, -0 to \
  -15.2056, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1057 polygon from \
  -0, 3.27185e+17 to \
  5.03764e+30, 7.85872e+30 to \
  -7.65179, -0 to \
  -15.3037, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1058 polygon from \
  -0, 3.27185e+17 to \
  4.979e+30, 7.81703e+30 to \
  -7.70084, -0 to \
  -15.4018, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1059 polygon from \
  -0, 3.27185e+17 to \
  4.92138e+30, 7.77578e+30 to \
  -7.74989, -0 to \
  -15.4999, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1060 polygon from \
  -0, 3.27185e+17 to \
  4.86476e+30, 7.73496e+30 to \
  -7.79894, -0 to \
  -15.598, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1061 polygon from \
  -0, 3.27185e+17 to \
  4.80911e+30, 7.69457e+30 to \
  -7.84799, -0 to \
  -15.6961, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1062 polygon from \
  -0, 3.27185e+17 to \
  4.74209e+30, 7.63477e+30 to \
  -7.89704, -0 to \
  -15.7942, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1063 polygon from \
  -0, 3.27185e+17 to \
  4.68853e+30, 7.59541e+30 to \
  -7.94609, -0 to \
  -15.8923, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1064 polygon from \
  -0, 3.27185e+17 to \
  4.63587e+30, 7.55646e+30 to \
  -7.99514, -0 to \
  -15.9904, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1065 polygon from \
  -0, 3.27185e+17 to \
  4.58409e+30, 7.51791e+30 to \
  -8.04419, -0 to \
  -16.0885, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1066 polygon from \
  -0, 3.27185e+17 to \
  4.53318e+30, 7.47975e+30 to \
  -8.09324, -0 to \
  -16.1866, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1067 polygon from \
  -0, 3.27185e+17 to \
  4.48312e+30, 7.44197e+30 to \
  -8.14229, -0 to \
  -16.2847, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1068 polygon from \
  -0, 3.27185e+17 to \
  4.43388e+30, 7.40458e+30 to \
  -8.19134, -0 to \
  -16.3828, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1069 polygon from \
  -0, 3.27185e+17 to \
  4.38545e+30, 7.36755e+30 to \
  -8.24039, -0 to \
  -16.4809, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1070 polygon from \
  -0, 3.27185e+17 to \
  4.33781e+30, 7.3309e+30 to \
  -8.28944, -0 to \
  -16.579, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1071 polygon from \
  -0, 3.27185e+17 to \
  4.29095e+30, 7.29461e+30 to \
  -8.33849, -0 to \
  -16.6771, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1072 polygon from \
  -0, 3.27185e+17 to \
  4.24484e+30, 7.25867e+30 to \
  -8.38754, -0 to \
  -16.7752, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1073 polygon from \
  -0, 3.27185e+17 to \
  4.19947e+30, 7.22309e+30 to \
  -8.43659, -0 to \
  -16.8733, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1074 polygon from \
  -0, 3.27185e+17 to \
  4.15483e+30, 7.18786e+30 to \
  -8.48564, -0 to \
  -16.9714, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1075 polygon from \
  -0, 3.27185e+17 to \
  4.1109e+30, 7.15296e+30 to \
  -8.53469, -0 to \
  -17.0695, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1076 polygon from \
  -0, 3.27185e+17 to \
  4.07751e+30, 7.13564e+30 to \
  -8.58374, -0 to \
  -17.1676, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1077 polygon from \
  -0, 3.27185e+17 to \
  4.03481e+30, 7.10126e+30 to \
  -8.63279, -0 to \
  -17.2657, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1078 polygon from \
  -0, 3.27185e+17 to \
  3.99277e+30, 7.0672e+30 to \
  -8.68184, -0 to \
  -17.3638, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1079 polygon from \
  -0, 3.27185e+17 to \
  3.95139e+30, 7.03346e+30 to \
  -8.73089, -0 to \
  -17.4619, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1080 polygon from \
  -0, 3.27185e+17 to \
  3.91064e+30, 7.00005e+30 to \
  -8.77994, -0 to \
  -17.56, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1081 polygon from \
  -0, 3.27185e+17 to \
  3.87053e+30, 6.96695e+30 to \
  -8.82899, -0 to \
  -17.6581, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1082 polygon from \
  -0, 3.27185e+17 to \
  3.83103e+30, 6.93417e+30 to \
  -8.87804, -0 to \
  -17.7562, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1083 polygon from \
  -0, 3.27185e+17 to \
  3.79214e+30, 6.90169e+30 to \
  -8.92709, -0 to \
  -17.8543, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1084 polygon from \
  -0, 3.27185e+17 to \
  3.76261e+30, 6.88556e+30 to \
  -8.97614, -0 to \
  -17.9524, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1085 polygon from \
  -0, 3.27185e+17 to \
  3.72475e+30, 6.85354e+30 to \
  -9.02519, -0 to \
  -18.0505, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1086 polygon from \
  -0, 3.27185e+17 to \
  3.68747e+30, 6.82181e+30 to \
  -9.07424, -0 to \
  -18.1486, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1087 polygon from \
  -0, 3.27185e+17 to \
  3.65074e+30, 6.79037e+30 to \
  -9.12329, -0 to \
  -18.2467, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1088 polygon from \
  -0, 3.27185e+17 to \
  3.61456e+30, 6.75922e+30 to \
  -9.17234, -0 to \
  -18.3448, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1089 polygon from \
  -0, 3.27185e+17 to \
  3.57892e+30, 6.72836e+30 to \
  -9.22139, -0 to \
  -18.4429, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1090 polygon from \
  -0, 3.27185e+17 to \
  3.55187e+30, 6.71303e+30 to \
  -9.27044, -0 to \
  -18.541, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1091 polygon from \
  -0, 3.27185e+17 to \
  3.51715e+30, 6.68259e+30 to \
  -9.31949, -0 to \
  -18.6391, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1092 polygon from \
  -0, 3.27185e+17 to \
  3.48294e+30, 6.65242e+30 to \
  -9.36854, -0 to \
  -18.7372, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1093 polygon from \
  -0, 3.27185e+17 to \
  3.44923e+30, 6.62252e+30 to \
  -9.41759, -0 to \
  -18.8353, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1094 polygon from \
  -0, 3.27185e+17 to \
  3.42367e+30, 6.60767e+30 to \
  -9.46664, -0 to \
  -18.9334, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1095 polygon from \
  -0, 3.27185e+17 to \
  3.39081e+30, 6.57817e+30 to \
  -9.51569, -0 to \
  -19.0315, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1096 polygon from \
  -0, 3.27185e+17 to \
  3.35843e+30, 6.54894e+30 to \
  -9.56474, -0 to \
  -19.1296, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1097 polygon from \
  -0, 3.27185e+17 to \
  3.32651e+30, 6.51996e+30 to \
  -9.61379, -0 to \
  -19.2277, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1098 polygon from \
  -0, 3.27185e+17 to \
  3.30963e+30, 6.51996e+30 to \
  -9.66284, -0 to \
  -19.3258, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1099 polygon from \
  -0, 3.27185e+17 to \
  3.28564e+30, 6.50557e+30 to \
  -9.71189, -0 to \
  -19.4239, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1100 polygon from \
  -0, 3.27185e+17 to \
  3.26193e+30, 6.49124e+30 to \
  -9.76094, -0 to \
  -19.522, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1101 polygon from \
  -0, 3.27185e+17 to \
  3.23849e+30, 6.47697e+30 to \
  -9.80999, -0 to \
  -19.6201, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1102 polygon from \
  -0, 3.27185e+17 to \
  3.21531e+30, 6.46277e+30 to \
  -9.85904, -0 to \
  -19.7182, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1103 polygon from \
  -0, 3.27185e+17 to \
  3.18542e+30, 6.43454e+30 to \
  -9.90809, -0 to \
  -19.8163, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1104 polygon from \
  -0, 3.27185e+17 to \
  3.15595e+30, 6.40657e+30 to \
  -9.95714, -0 to \
  -19.9144, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1105 polygon from \
  -0, 3.27185e+17 to \
  3.13366e+30, 6.39267e+30 to \
  -10.0061, -0 to \
  -20.0125, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1106 polygon from \
  -0, 3.27185e+17 to \
  3.10491e+30, 6.36506e+30 to \
  -10.0552, -0 to \
  -20.1106, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1107 polygon from \
  -0, 3.27185e+17 to \
  3.07655e+30, 6.33768e+30 to \
  -10.1042, -0 to \
  -20.2087, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1108 polygon from \
  -0, 3.27185e+17 to \
  3.05511e+30, 6.32408e+30 to \
  -10.1533, -0 to \
  -20.3068, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1109 polygon from \
  -0, 3.27185e+17 to \
  3.02743e+30, 6.29705e+30 to \
  -10.2023, -0 to \
  -20.4049, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1110 polygon from \
  -0, 3.27185e+17 to \
  3.00013e+30, 6.27026e+30 to \
  -10.2514, -0 to \
  -20.503, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1111 polygon from \
  -0, 3.27185e+17 to \
  2.9795e+30, 6.25695e+30 to \
  -10.3004, -0 to \
  -20.6011, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1112 polygon from \
  -0, 3.27185e+17 to \
  2.95284e+30, 6.23049e+30 to \
  -10.3495, -0 to \
  -20.6992, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1113 polygon from \
  2.92654e+30, 6.20426e+30 to \
  -20.7973, -0 to \
  -30.1886, 3.27185e+17 to \
  2.92654e+30, 6.20426e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1114 polygon from \
  -0, 3.27185e+17 to \
  2.90668e+30, 6.19122e+30 to \
  -10.4476, -0 to \
  -20.8954, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1115 polygon from \
  -0, 3.27185e+17 to \
  2.88099e+30, 6.16532e+30 to \
  -10.4966, -0 to \
  -20.9935, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1116 polygon from \
  -0, 3.27185e+17 to \
  2.85564e+30, 6.13963e+30 to \
  -10.5457, -0 to \
  -21.0916, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1117 polygon from \
  -0, 3.27185e+17 to \
  2.83651e+30, 6.12686e+30 to \
  -10.5947, -0 to \
  -21.1897, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1118 polygon from \
  -0, 3.27185e+17 to \
  2.81175e+30, 6.10149e+30 to \
  -10.6438, -0 to \
  -21.2878, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1119 polygon from \
  -0, 3.27185e+17 to \
  2.79307e+30, 6.08889e+30 to \
  -10.6928, -0 to \
  -21.3859, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1120 polygon from \
  -0, 3.27185e+17 to \
  2.76887e+30, 6.06383e+30 to \
  -10.7419, -0 to \
  -21.484, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1121 polygon from \
  2.74499e+30, 6.03898e+30 to \
  -21.5821, -0 to \
  -29.0909, 3.27185e+17 to \
  2.74499e+30, 6.03898e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1122 polygon from \
  -0, 3.27185e+17 to \
  2.72698e+30, 6.02663e+30 to \
  -10.84, -0 to \
  -21.6802, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1123 polygon from \
  -0, 3.27185e+17 to \
  2.70364e+30, 6.00208e+30 to \
  -10.889, -0 to \
  -21.7783, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1124 polygon from \
  -0, 3.27185e+17 to \
  2.68605e+30, 5.98988e+30 to \
  -10.9381, -0 to \
  -21.8764, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1125 polygon from \
  -0, 3.27185e+17 to \
  2.66323e+30, 5.96563e+30 to \
  -10.9871, -0 to \
  -21.9745, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1126 polygon from \
  -0, 3.27185e+17 to \
  2.6407e+30, 5.94158e+30 to \
  -11.0362, -0 to \
  -22.0726, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1127 polygon from \
  -0, 3.27185e+17 to \
  2.62373e+30, 5.92962e+30 to \
  -11.0852, -0 to \
  -22.1707, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1128 polygon from \
  -0, 3.27185e+17 to \
  2.6017e+30, 5.90585e+30 to \
  -11.1343, -0 to \
  -22.2688, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1129 polygon from \
  -0, 3.27185e+17 to \
  2.58511e+30, 5.89404e+30 to \
  -11.1833, -0 to \
  -22.3669, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1130 polygon from \
  -0, 3.27185e+17 to \
  2.56357e+30, 5.87056e+30 to \
  -11.2324, -0 to \
  -22.465, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1131 polygon from \
  2.54735e+30, 5.85889e+30 to \
  -22.5631, -0 to \
  -27.826, 3.27185e+17 to \
  2.54735e+30, 5.85889e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1132 polygon from \
  -0, 3.27185e+17 to \
  2.52627e+30, 5.83569e+30 to \
  -11.3305, -0 to \
  -22.6612, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1133 polygon from \
  2.51041e+30, 5.82415e+30 to \
  -22.7593, -0 to \
  -27.5862, 3.27185e+17 to \
  2.51041e+30, 5.82415e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1134 polygon from \
  -0, 3.27185e+17 to \
  2.4898e+30, 5.80122e+30 to \
  -11.4286, -0 to \
  -22.8574, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1135 polygon from \
  -0, 3.27185e+17 to \
  2.47429e+30, 5.78983e+30 to \
  -11.4776, -0 to \
  -22.9555, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1136 polygon from \
  -0, 3.27185e+17 to \
  2.45412e+30, 5.76717e+30 to \
  -11.5267, -0 to \
  -23.0536, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1137 polygon from \
  -0, 3.27185e+17 to \
  2.43894e+30, 5.7559e+30 to \
  -11.5757, -0 to \
  -23.1517, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1138 polygon from \
  -0, 3.27185e+17 to \
  2.4192e+30, 5.7335e+30 to \
  -11.6248, -0 to \
  -23.2498, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1139 polygon from \
  2.40436e+30, 5.72237e+30 to \
  -23.3479, -0 to \
  -26.8907, 3.27185e+17 to \
  2.40436e+30, 5.72237e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1140 polygon from \
  2.38504e+30, 5.70024e+30 to \
  -23.446, -0 to \
  -26.7782, 3.27185e+17 to \
  2.38504e+30, 5.70024e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1141 polygon from \
  -0, 3.27185e+17 to \
  2.36595e+30, 5.67827e+30 to \
  -11.7719, -0 to \
  -23.5441, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1142 polygon from \
  2.3516e+30, 5.66735e+30 to \
  -23.6422, -0 to \
  -26.556, 3.27185e+17 to \
  2.3516e+30, 5.66735e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1143 polygon from \
  -0, 3.27185e+17 to \
  2.33739e+30, 5.65647e+30 to \
  -11.87, -0 to \
  -23.7403, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1144 polygon from \
  -0, 3.27185e+17 to \
  2.31887e+30, 5.63484e+30 to \
  -11.9191, -0 to \
  -23.8384, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1145 polygon from \
  -0, 3.27185e+17 to \
  2.30496e+30, 5.62409e+30 to \
  -11.9681, -0 to \
  -23.9365, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1146 polygon from \
  -0, 3.27185e+17 to \
  2.28682e+30, 5.6027e+30 to \
  -12.0172, -0 to \
  -24.0346, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1147 polygon from \
  -0, 3.27185e+17 to \
  2.2732e+30, 5.59207e+30 to \
  -12.0662, -0 to \
  -24.1327, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1148 polygon from \
  2.25544e+30, 5.57093e+30 to \
  -24.2308, -0 to \
  -25.9109, 3.27185e+17 to \
  2.25544e+30, 5.57093e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1149 polygon from \
  -0, 3.27185e+17 to \
  2.24211e+30, 5.56042e+30 to \
  -12.1643, -0 to \
  -24.3289, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1150 polygon from \
  -0, 3.27185e+17 to \
  2.22471e+30, 5.53951e+30 to \
  -12.2134, -0 to \
  -24.427, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1151 polygon from \
  2.21165e+30, 5.52912e+30 to \
  -24.5251, -0 to \
  -25.6, 3.27185e+17 to \
  2.21165e+30, 5.52912e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1152 polygon from \
  2.19461e+30, 5.50845e+30 to \
  -24.6232, -0 to \
  -25.498, 3.27185e+17 to \
  2.19461e+30, 5.50845e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1153 polygon from \
  2.18182e+30, 5.49817e+30 to \
  -24.7213, -0 to \
  -25.3968, 3.27185e+17 to \
  2.18182e+30, 5.49817e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1154 polygon from \
  2.16512e+30, 5.47774e+30 to \
  -24.8194, -0 to \
  -25.2964, 3.27185e+17 to \
  2.16512e+30, 5.47774e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1155 polygon from \
  -0, 3.27185e+17 to \
  2.15259e+30, 5.46757e+30 to \
  -12.4586, -0 to \
  -24.9175, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1156 polygon from \
  2.13622e+30, 5.44736e+30 to \
  -25.0156, -0 to \
  -25.098, 3.27185e+17 to \
  2.13622e+30, 5.44736e+30 front fs empty border lc rgb '#6165' lw 0.200001
set object 1157 polygon from \
  -25, 3.27185e+17 to \
  2.12395e+30, 5.43731e+30 to \
  -12.5567, -0 to \
  -25.1137, -0 to \
  -25, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1158 polygon from \
  -24.9027, 3.27185e+17 to \
  2.11179e+30, 5.4273e+30 to \
  -12.6058, -0 to \
  -25.2118, -0 to \
  -24.9027, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1159 polygon from \
  -0, 3.27185e+17 to \
  2.09589e+30, 5.40738e+30 to \
  -12.6548, -0 to \
  -25.3099, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1160 polygon from \
  -24.7104, 3.27185e+17 to \
  2.08397e+30, 5.39748e+30 to \
  -12.7039, -0 to \
  -25.408, -0 to \
  -24.7104, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1161 polygon from \
  -24.6153, 3.27185e+17 to \
  2.06838e+30, 5.37778e+30 to \
  -12.7529, -0 to \
  -25.5061, -0 to \
  -24.6153, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1162 polygon from \
  -24.521, 3.27185e+17 to \
  2.0567e+30, 5.36798e+30 to \
  -12.802, -0 to \
  -25.6042, -0 to \
  -24.521, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1163 polygon from \
  -0, 3.27185e+17 to \
  2.04141e+30, 5.3485e+30 to \
  -12.851, -0 to \
  -25.7023, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1164 polygon from \
  -0, 3.27185e+17 to \
  2.02997e+30, 5.33881e+30 to \
  -12.9001, -0 to \
  -25.8004, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1165 polygon from \
  -24.2424, 3.27185e+17 to \
  2.01862e+30, 5.32915e+30 to \
  -12.9491, -0 to \
  -25.8985, -0 to \
  -24.2424, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1166 polygon from \
  -0, 3.27185e+17 to \
  2.00376e+30, 5.30995e+30 to \
  -12.9982, -0 to \
  -25.9966, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1167 polygon from \
  -24.0601, 3.27185e+17 to \
  1.99263e+30, 5.3004e+30 to \
  -13.0472, -0 to \
  -26.0947, -0 to \
  -24.0601, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1168 polygon from \
  -23.97, 3.27185e+17 to \
  1.97806e+30, 5.2814e+30 to \
  -13.0963, -0 to \
  -26.1928, -0 to \
  -23.97, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1169 polygon from \
  -0, 3.27185e+17 to \
  1.96715e+30, 5.27195e+30 to \
  -13.1453, -0 to \
  -26.2909, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1170 polygon from \
  -23.7918, 3.27185e+17 to \
  1.95634e+30, 5.26254e+30 to \
  -13.1944, -0 to \
  -26.389, -0 to \
  -23.7918, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1171 polygon from \
  -23.7037, 3.27185e+17 to \
  1.94216e+30, 5.24381e+30 to \
  -13.2434, -0 to \
  -26.4871, -0 to \
  -23.7037, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1172 polygon from \
  -23.6162, 3.27185e+17 to \
  1.93155e+30, 5.2345e+30 to \
  -13.2925, -0 to \
  -26.5852, -0 to \
  -23.6162, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1173 polygon from \
  -0, 3.27185e+17 to \
  1.91764e+30, 5.21597e+30 to \
  -13.3415, -0 to \
  -26.6833, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1174 polygon from \
  -23.4432, 3.27185e+17 to \
  1.90724e+30, 5.20675e+30 to \
  -13.3906, -0 to \
  -26.7814, -0 to \
  -23.4432, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1175 polygon from \
  -23.3576, 3.27185e+17 to \
  1.89693e+30, 5.19757e+30 to \
  -13.4396, -0 to \
  -26.8795, -0 to \
  -23.3576, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1176 polygon from \
  -0, 3.27185e+17 to \
  1.88339e+30, 5.1793e+30 to \
  -13.4887, -0 to \
  -26.9776, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1177 polygon from \
  -0, 3.27185e+17 to \
  1.87327e+30, 5.17021e+30 to \
  -13.5377, -0 to \
  -27.0757, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1178 polygon from \
  -0, 3.27185e+17 to \
  1.85998e+30, 5.15214e+30 to \
  -13.5868, -0 to \
  -27.1738, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1179 polygon from \
  -23.0215, 3.27185e+17 to \
  1.85006e+30, 5.14314e+30 to \
  -13.6358, -0 to \
  -27.2719, -0 to \
  -23.0215, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1180 polygon from \
  -22.939, 3.27185e+17 to \
  1.84021e+30, 5.13418e+30 to \
  -13.6849, -0 to \
  -27.37, -0 to \
  -22.939, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1181 polygon from \
  -22.8571, 3.27185e+17 to \
  1.82727e+30, 5.11636e+30 to \
  -13.7339, -0 to \
  -27.4681, -0 to \
  -22.8571, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1182 polygon from \
  -22.7758, 3.27185e+17 to \
  1.81762e+30, 5.10749e+30 to \
  -13.783, -0 to \
  -27.5662, -0 to \
  -22.7758, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1183 polygon from \
  -22.695, 3.27185e+17 to \
  1.80804e+30, 5.09865e+30 to \
  -13.832, -0 to \
  -27.6643, -0 to \
  -22.695, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1184 polygon from \
  -0, 3.27185e+17 to \
  1.79544e+30, 5.08107e+30 to \
  -13.8811, -0 to \
  -27.7624, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1185 polygon from \
  -0, 3.27185e+17 to \
  1.78603e+30, 5.07233e+30 to \
  -13.9301, -0 to \
  -27.8605, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1186 polygon from \
  -0, 3.27185e+17 to \
  1.77671e+30, 5.06361e+30 to \
  -13.9792, -0 to \
  -27.9586, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1187 polygon from \
  -22.3776, 3.27185e+17 to \
  1.76443e+30, 5.04627e+30 to \
  -14.0282, -0 to \
  -28.0567, -0 to \
  -22.3776, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1188 polygon from \
  -22.2996, 3.27185e+17 to \
  1.75528e+30, 5.03764e+30 to \
  -14.0773, -0 to \
  -28.1548, -0 to \
  -22.2996, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1189 polygon from \
  -22.2222, 3.27185e+17 to \
  1.74323e+30, 5.02048e+30 to \
  -14.1263, -0 to \
  -28.2529, -0 to \
  -22.2222, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1190 polygon from \
  -22.1453, 3.27185e+17 to \
  1.73424e+30, 5.01194e+30 to \
  -14.1754, -0 to \
  -28.351, -0 to \
  -22.1453, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1191 polygon from \
  -22.0689, 3.27185e+17 to \
  1.72532e+30, 5.00343e+30 to \
  -14.2244, -0 to \
  -28.4491, -0 to \
  -22.0689, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1192 polygon from \
  -21.9931, 3.27185e+17 to \
  1.71358e+30, 4.9865e+30 to \
  -14.2735, -0 to \
  -28.5472, -0 to \
  -21.9931, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1193 polygon from \
  -0, 3.27185e+17 to \
  1.70482e+30, 4.97808e+30 to \
  -14.3225, -0 to \
  -28.6453, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1194 polygon from \
  -21.843, 3.27185e+17 to \
  1.69614e+30, 4.96968e+30 to \
  -14.3716, -0 to \
  -28.7434, -0 to \
  -21.843, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1195 polygon from \
  -21.7687, 3.27185e+17 to \
  1.68469e+30, 4.95298e+30 to \
  -14.4206, -0 to \
  -28.8415, -0 to \
  -21.7687, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1196 polygon from \
  -0, 3.27185e+17 to \
  1.67616e+30, 4.94467e+30 to \
  -14.4697, -0 to \
  -28.9396, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1197 polygon from \
  -0, 3.27185e+17 to \
  1.6677e+30, 4.93639e+30 to \
  -14.5187, -0 to \
  -29.0377, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1198 polygon from \
  -21.5488, 3.27185e+17 to \
  1.65654e+30, 4.9199e+30 to \
  -14.5678, -0 to \
  -29.1358, -0 to \
  -21.5488, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1199 polygon from \
  -0, 3.27185e+17 to \
  1.64823e+30, 4.9117e+30 to \
  -14.6168, -0 to \
  -29.2339, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
set object 1200 polygon from \
  -0, 3.27185e+17 to \
  1.63998e+30, 4.90353e+30 to \
  -14.6659, -0 to \
  -29.332, -0 to \
  -0, 3.27185e+17 front fs empty border lc rgb '#6165' lw 0.200001
plot [-9.23399e+35:7.26932e+35] [-1.04012e+31:1.14414e+32] NaN notitle 

