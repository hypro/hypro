# settings
set term pdf
set output "bouncing_ball_box_mpq_class_glpk_z3.pdf
set xtics autofreq
set ytics autofreq
set grid back
# axis settings
set xzeroaxis 
set zeroaxis 
set xtics axis 
set xrange [-1.02003:11.2205] 
set yzeroaxis 
set ytics axis 
set yrange [-16.7139:13.158] 

# plotting sets
set object 1 polygon from \
  9.99915, 0.000123034 to \
  10.2004, 0.000123034 to \
  10.2004, -0.098223 to \
  9.99915, -0.098223 to \
  9.99915, 0.000123034 front fs empty border lc rgb '#6165' lw 0.200001
set object 2 polygon from \
  9.99767, -0.0979769 to \
  10.1999, -0.0979769 to \
  10.1999, -0.196323 to \
  9.99767, -0.196323 to \
  9.99767, -0.0979769 front fs empty border lc rgb '#6165' lw 0.200001
set object 3 polygon from \
  9.99522, -0.196076 to \
  10.1985, -0.196076 to \
  10.1985, -0.294423 to \
  9.99522, -0.294423 to \
  9.99522, -0.196076 front fs empty border lc rgb '#6165' lw 0.200001
set object 4 polygon from \
  9.99179, -0.294176 to \
  10.196, -0.294176 to \
  10.196, -0.392523 to \
  9.99179, -0.392523 to \
  9.99179, -0.294176 front fs empty border lc rgb '#6165' lw 0.200001
set object 5 polygon from \
  9.98737, -0.392276 to \
  10.1926, -0.392276 to \
  10.1926, -0.490623 to \
  9.98737, -0.490623 to \
  9.98737, -0.392276 front fs empty border lc rgb '#6165' lw 0.200001
set object 6 polygon from \
  9.98197, -0.490376 to \
  10.1882, -0.490376 to \
  10.1882, -0.588723 to \
  9.98197, -0.588723 to \
  9.98197, -0.490376 front fs empty border lc rgb '#6165' lw 0.200001
set object 7 polygon from \
  9.97559, -0.588476 to \
  10.1828, -0.588476 to \
  10.1828, -0.686823 to \
  9.97559, -0.686823 to \
  9.97559, -0.588476 front fs empty border lc rgb '#6165' lw 0.200001
set object 8 polygon from \
  9.96824, -0.686576 to \
  10.1764, -0.686576 to \
  10.1764, -0.784923 to \
  9.96824, -0.784923 to \
  9.96824, -0.686576 front fs empty border lc rgb '#6165' lw 0.200001
set object 9 polygon from \
  9.9599, -0.784676 to \
  10.169, -0.784676 to \
  10.169, -0.883023 to \
  9.9599, -0.883023 to \
  9.9599, -0.784676 front fs empty border lc rgb '#6165' lw 0.200001
set object 10 polygon from \
  9.95058, -0.882776 to \
  10.1607, -0.882776 to \
  10.1607, -0.981123 to \
  9.95058, -0.981123 to \
  9.95058, -0.882776 front fs empty border lc rgb '#6165' lw 0.200001
set object 11 polygon from \
  9.94027, -0.980876 to \
  10.1514, -0.980876 to \
  10.1514, -1.07922 to \
  9.94027, -1.07922 to \
  9.94027, -0.980876 front fs empty border lc rgb '#6165' lw 0.200001
set object 12 polygon from \
  9.92899, -1.07897 to \
  10.1411, -1.07897 to \
  10.1411, -1.17732 to \
  9.92899, -1.17732 to \
  9.92899, -1.07897 front fs empty border lc rgb '#6165' lw 0.200001
set object 13 polygon from \
  9.91673, -1.17707 to \
  10.1298, -1.17707 to \
  10.1298, -1.27542 to \
  9.91673, -1.27542 to \
  9.91673, -1.17707 front fs empty border lc rgb '#6165' lw 0.200001
set object 14 polygon from \
  9.90348, -1.27517 to \
  10.1175, -1.27517 to \
  10.1175, -1.37352 to \
  9.90348, -1.37352 to \
  9.90348, -1.27517 front fs empty border lc rgb '#6165' lw 0.200001
set object 15 polygon from \
  9.88926, -1.37327 to \
  10.1043, -1.37327 to \
  10.1043, -1.47162 to \
  9.88926, -1.47162 to \
  9.88926, -1.37327 front fs empty border lc rgb '#6165' lw 0.200001
set object 16 polygon from \
  9.87405, -1.47137 to \
  10.0901, -1.47137 to \
  10.0901, -1.56972 to \
  9.87405, -1.56972 to \
  9.87405, -1.47137 front fs empty border lc rgb '#6165' lw 0.200001
set object 17 polygon from \
  9.85786, -1.56947 to \
  10.0749, -1.56947 to \
  10.0749, -1.66782 to \
  9.85786, -1.66782 to \
  9.85786, -1.56947 front fs empty border lc rgb '#6165' lw 0.200001
set object 18 polygon from \
  9.84069, -1.66757 to \
  10.0587, -1.66757 to \
  10.0587, -1.76592 to \
  9.84069, -1.76592 to \
  9.84069, -1.66757 front fs empty border lc rgb '#6165' lw 0.200001
set object 19 polygon from \
  9.82254, -1.76567 to \
  10.0415, -1.76567 to \
  10.0415, -1.86402 to \
  9.82254, -1.86402 to \
  9.82254, -1.76567 front fs empty border lc rgb '#6165' lw 0.200001
set object 20 polygon from \
  9.80341, -1.86377 to \
  10.0234, -1.86377 to \
  10.0234, -1.96212 to \
  9.80341, -1.96212 to \
  9.80341, -1.86377 front fs empty border lc rgb '#6165' lw 0.200001
set object 21 polygon from \
  9.7833, -1.96187 to \
  10.0042, -1.96187 to \
  10.0042, -2.06022 to \
  9.7833, -2.06022 to \
  9.7833, -1.96187 front fs empty border lc rgb '#6165' lw 0.200001
set object 22 polygon from \
  9.76221, -2.05997 to \
  9.98409, -2.05997 to \
  9.98409, -2.15832 to \
  9.76221, -2.15832 to \
  9.76221, -2.05997 front fs empty border lc rgb '#6165' lw 0.200001
set object 23 polygon from \
  9.74014, -2.15807 to \
  9.963, -2.15807 to \
  9.963, -2.25642 to \
  9.74014, -2.25642 to \
  9.74014, -2.15807 front fs empty border lc rgb '#6165' lw 0.200001
set object 24 polygon from \
  9.71708, -2.25617 to \
  9.94093, -2.25617 to \
  9.94093, -2.35452 to \
  9.71708, -2.35452 to \
  9.71708, -2.25617 front fs empty border lc rgb '#6165' lw 0.200001
set object 25 polygon from \
  9.69304, -2.35427 to \
  9.91787, -2.35427 to \
  9.91787, -2.45262 to \
  9.69304, -2.45262 to \
  9.69304, -2.35427 front fs empty border lc rgb '#6165' lw 0.200001
set object 26 polygon from \
  9.66803, -2.45237 to \
  9.89384, -2.45237 to \
  9.89384, -2.55072 to \
  9.66803, -2.55072 to \
  9.66803, -2.45237 front fs empty border lc rgb '#6165' lw 0.200001
set object 27 polygon from \
  9.64203, -2.55047 to \
  9.86883, -2.55047 to \
  9.86883, -2.64882 to \
  9.64203, -2.64882 to \
  9.64203, -2.55047 front fs empty border lc rgb '#6165' lw 0.200001
set object 28 polygon from \
  9.61505, -2.64857 to \
  9.84283, -2.64857 to \
  9.84283, -2.74692 to \
  9.61505, -2.74692 to \
  9.61505, -2.64857 front fs empty border lc rgb '#6165' lw 0.200001
set object 29 polygon from \
  9.58709, -2.74667 to \
  9.81586, -2.74667 to \
  9.81586, -2.84502 to \
  9.58709, -2.84502 to \
  9.58709, -2.74667 front fs empty border lc rgb '#6165' lw 0.200001
set object 30 polygon from \
  9.55815, -2.84477 to \
  9.7879, -2.84477 to \
  9.7879, -2.94312 to \
  9.55815, -2.94312 to \
  9.55815, -2.84477 front fs empty border lc rgb '#6165' lw 0.200001
set object 31 polygon from \
  9.52823, -2.94287 to \
  9.75896, -2.94287 to \
  9.75896, -3.04122 to \
  9.52823, -3.04122 to \
  9.52823, -2.94287 front fs empty border lc rgb '#6165' lw 0.200001
set object 32 polygon from \
  9.49733, -3.04097 to \
  9.72904, -3.04097 to \
  9.72904, -3.13932 to \
  9.49733, -3.13932 to \
  9.49733, -3.04097 front fs empty border lc rgb '#6165' lw 0.200001
set object 33 polygon from \
  9.46544, -3.13907 to \
  9.69814, -3.13907 to \
  9.69814, -3.23742 to \
  9.46544, -3.23742 to \
  9.46544, -3.13907 front fs empty border lc rgb '#6165' lw 0.200001
set object 34 polygon from \
  9.43258, -3.23717 to \
  9.66626, -3.23717 to \
  9.66626, -3.33552 to \
  9.43258, -3.33552 to \
  9.43258, -3.23717 front fs empty border lc rgb '#6165' lw 0.200001
set object 35 polygon from \
  9.39873, -3.33527 to \
  9.6334, -3.33527 to \
  9.6334, -3.43362 to \
  9.39873, -3.43362 to \
  9.39873, -3.33527 front fs empty border lc rgb '#6165' lw 0.200001
set object 36 polygon from \
  9.36391, -3.43337 to \
  9.59955, -3.43337 to \
  9.59955, -3.53172 to \
  9.36391, -3.53172 to \
  9.36391, -3.43337 front fs empty border lc rgb '#6165' lw 0.200001
set object 37 polygon from \
  9.3281, -3.53147 to \
  9.56473, -3.53147 to \
  9.56473, -3.62982 to \
  9.3281, -3.62982 to \
  9.3281, -3.53147 front fs empty border lc rgb '#6165' lw 0.200001
set object 38 polygon from \
  9.29131, -3.62957 to \
  9.52892, -3.62957 to \
  9.52892, -3.72792 to \
  9.29131, -3.72792 to \
  9.29131, -3.62957 front fs empty border lc rgb '#6165' lw 0.200001
set object 39 polygon from \
  9.25354, -3.72767 to \
  9.49214, -3.72767 to \
  9.49214, -3.82602 to \
  9.25354, -3.82602 to \
  9.25354, -3.72767 front fs empty border lc rgb '#6165' lw 0.200001
set object 40 polygon from \
  9.21479, -3.82577 to \
  9.45437, -3.82577 to \
  9.45437, -3.92412 to \
  9.21479, -3.92412 to \
  9.21479, -3.82577 front fs empty border lc rgb '#6165' lw 0.200001
set object 41 polygon from \
  9.17506, -3.92387 to \
  9.41562, -3.92387 to \
  9.41562, -4.02222 to \
  9.17506, -4.02222 to \
  9.17506, -3.92387 front fs empty border lc rgb '#6165' lw 0.200001
set object 42 polygon from \
  9.13434, -4.02197 to \
  9.37589, -4.02197 to \
  9.37589, -4.12032 to \
  9.13434, -4.12032 to \
  9.13434, -4.02197 front fs empty border lc rgb '#6165' lw 0.200001
set object 43 polygon from \
  9.09265, -4.12007 to \
  9.33518, -4.12007 to \
  9.33518, -4.21842 to \
  9.09265, -4.21842 to \
  9.09265, -4.12007 front fs empty border lc rgb '#6165' lw 0.200001
set object 44 polygon from \
  9.04998, -4.21817 to \
  9.29349, -4.21817 to \
  9.29349, -4.31652 to \
  9.04998, -4.31652 to \
  9.04998, -4.21817 front fs empty border lc rgb '#6165' lw 0.200001
set object 45 polygon from \
  9.00632, -4.31627 to \
  9.25082, -4.31627 to \
  9.25082, -4.41462 to \
  9.00632, -4.41462 to \
  9.00632, -4.31627 front fs empty border lc rgb '#6165' lw 0.200001
set object 46 polygon from \
  8.96168, -4.41437 to \
  9.20717, -4.41437 to \
  9.20717, -4.51272 to \
  8.96168, -4.51272 to \
  8.96168, -4.41437 front fs empty border lc rgb '#6165' lw 0.200001
set object 47 polygon from \
  8.91607, -4.51247 to \
  9.16253, -4.51247 to \
  9.16253, -4.61082 to \
  8.91607, -4.61082 to \
  8.91607, -4.51247 front fs empty border lc rgb '#6165' lw 0.200001
set object 48 polygon from \
  8.86947, -4.61057 to \
  9.11692, -4.61057 to \
  9.11692, -4.70892 to \
  8.86947, -4.70892 to \
  8.86947, -4.61057 front fs empty border lc rgb '#6165' lw 0.200001
set object 49 polygon from \
  8.82189, -4.70867 to \
  9.07032, -4.70867 to \
  9.07032, -4.80702 to \
  8.82189, -4.80702 to \
  8.82189, -4.70867 front fs empty border lc rgb '#6165' lw 0.200001
set object 50 polygon from \
  8.77333, -4.80677 to \
  9.02274, -4.80677 to \
  9.02274, -4.90512 to \
  8.77333, -4.90512 to \
  8.77333, -4.80677 front fs empty border lc rgb '#6165' lw 0.200001
set object 51 polygon from \
  8.72378, -4.90487 to \
  8.97418, -4.90487 to \
  8.97418, -5.00322 to \
  8.72378, -5.00322 to \
  8.72378, -4.90487 front fs empty border lc rgb '#6165' lw 0.200001
set object 52 polygon from \
  8.67326, -5.00297 to \
  8.92465, -5.00297 to \
  8.92465, -5.10132 to \
  8.67326, -5.10132 to \
  8.67326, -5.00297 front fs empty border lc rgb '#6165' lw 0.200001
set object 53 polygon from \
  8.62176, -5.10107 to \
  8.87413, -5.10107 to \
  8.87413, -5.19942 to \
  8.62176, -5.19942 to \
  8.62176, -5.10107 front fs empty border lc rgb '#6165' lw 0.200001
set object 54 polygon from \
  8.56927, -5.19917 to \
  8.82262, -5.19917 to \
  8.82262, -5.29752 to \
  8.56927, -5.29752 to \
  8.56927, -5.19917 front fs empty border lc rgb '#6165' lw 0.200001
set object 55 polygon from \
  8.51581, -5.29727 to \
  8.77014, -5.29727 to \
  8.77014, -5.39562 to \
  8.51581, -5.39562 to \
  8.51581, -5.29727 front fs empty border lc rgb '#6165' lw 0.200001
set object 56 polygon from \
  8.46136, -5.39537 to \
  8.71668, -5.39537 to \
  8.71668, -5.49372 to \
  8.46136, -5.49372 to \
  8.46136, -5.39537 front fs empty border lc rgb '#6165' lw 0.200001
set object 57 polygon from \
  8.40593, -5.49347 to \
  8.66223, -5.49347 to \
  8.66223, -5.59182 to \
  8.40593, -5.59182 to \
  8.40593, -5.49347 front fs empty border lc rgb '#6165' lw 0.200001
set object 58 polygon from \
  8.34952, -5.59157 to \
  8.60681, -5.59157 to \
  8.60681, -5.68992 to \
  8.34952, -5.68992 to \
  8.34952, -5.59157 front fs empty border lc rgb '#6165' lw 0.200001
set object 59 polygon from \
  8.29213, -5.68967 to \
  8.5504, -5.68967 to \
  8.5504, -5.78802 to \
  8.29213, -5.78802 to \
  8.29213, -5.68967 front fs empty border lc rgb '#6165' lw 0.200001
set object 60 polygon from \
  8.23376, -5.78777 to \
  8.49302, -5.78777 to \
  8.49302, -5.88612 to \
  8.23376, -5.88612 to \
  8.23376, -5.78777 front fs empty border lc rgb '#6165' lw 0.200001
set object 61 polygon from \
  8.17441, -5.88587 to \
  8.43465, -5.88587 to \
  8.43465, -5.98422 to \
  8.17441, -5.98422 to \
  8.17441, -5.88587 front fs empty border lc rgb '#6165' lw 0.200001
set object 62 polygon from \
  8.11408, -5.98397 to \
  8.3753, -5.98397 to \
  8.3753, -6.08232 to \
  8.11408, -6.08232 to \
  8.11408, -5.98397 front fs empty border lc rgb '#6165' lw 0.200001
set object 63 polygon from \
  8.05277, -6.08207 to \
  8.31497, -6.08207 to \
  8.31497, -6.18042 to \
  8.05277, -6.18042 to \
  8.05277, -6.08207 front fs empty border lc rgb '#6165' lw 0.200001
set object 64 polygon from \
  7.99047, -6.18017 to \
  8.25366, -6.18017 to \
  8.25366, -6.27852 to \
  7.99047, -6.27852 to \
  7.99047, -6.18017 front fs empty border lc rgb '#6165' lw 0.200001
set object 65 polygon from \
  7.9272, -6.27827 to \
  8.19136, -6.27827 to \
  8.19136, -6.37662 to \
  7.9272, -6.37662 to \
  7.9272, -6.27827 front fs empty border lc rgb '#6165' lw 0.200001
set object 66 polygon from \
  7.86294, -6.37637 to \
  8.12809, -6.37637 to \
  8.12809, -6.47472 to \
  7.86294, -6.47472 to \
  7.86294, -6.37637 front fs empty border lc rgb '#6165' lw 0.200001
set object 67 polygon from \
  7.7977, -6.47447 to \
  8.06384, -6.47447 to \
  8.06384, -6.57282 to \
  7.7977, -6.57282 to \
  7.7977, -6.47447 front fs empty border lc rgb '#6165' lw 0.200001
set object 68 polygon from \
  7.73148, -6.57257 to \
  7.9986, -6.57257 to \
  7.9986, -6.67092 to \
  7.73148, -6.67092 to \
  7.73148, -6.57257 front fs empty border lc rgb '#6165' lw 0.200001
set object 69 polygon from \
  7.66428, -6.67067 to \
  7.93239, -6.67067 to \
  7.93239, -6.76902 to \
  7.66428, -6.76902 to \
  7.66428, -6.67067 front fs empty border lc rgb '#6165' lw 0.200001
set object 70 polygon from \
  7.5961, -6.76877 to \
  7.86519, -6.76877 to \
  7.86519, -6.86712 to \
  7.5961, -6.86712 to \
  7.5961, -6.76877 front fs empty border lc rgb '#6165' lw 0.200001
set object 71 polygon from \
  7.52694, -6.86687 to \
  7.79701, -6.86687 to \
  7.79701, -6.96522 to \
  7.52694, -6.96522 to \
  7.52694, -6.86687 front fs empty border lc rgb '#6165' lw 0.200001
set object 72 polygon from \
  7.4568, -6.96497 to \
  7.72785, -6.96497 to \
  7.72785, -7.06332 to \
  7.4568, -7.06332 to \
  7.4568, -6.96497 front fs empty border lc rgb '#6165' lw 0.200001
set object 73 polygon from \
  7.38567, -7.06307 to \
  7.65771, -7.06307 to \
  7.65771, -7.16142 to \
  7.38567, -7.16142 to \
  7.38567, -7.06307 front fs empty border lc rgb '#6165' lw 0.200001
set object 74 polygon from \
  7.31357, -7.16117 to \
  7.58659, -7.16117 to \
  7.58659, -7.25952 to \
  7.31357, -7.25952 to \
  7.31357, -7.16117 front fs empty border lc rgb '#6165' lw 0.200001
set object 75 polygon from \
  7.24048, -7.25927 to \
  7.51449, -7.25927 to \
  7.51449, -7.35762 to \
  7.24048, -7.35762 to \
  7.24048, -7.25927 front fs empty border lc rgb '#6165' lw 0.200001
set object 76 polygon from \
  7.16642, -7.35737 to \
  7.4414, -7.35737 to \
  7.4414, -7.45572 to \
  7.16642, -7.45572 to \
  7.16642, -7.35737 front fs empty border lc rgb '#6165' lw 0.200001
set object 77 polygon from \
  7.09137, -7.45547 to \
  7.36734, -7.45547 to \
  7.36734, -7.55382 to \
  7.09137, -7.55382 to \
  7.09137, -7.45547 front fs empty border lc rgb '#6165' lw 0.200001
set object 78 polygon from \
  7.01534, -7.55357 to \
  7.29229, -7.55357 to \
  7.29229, -7.65192 to \
  7.01534, -7.65192 to \
  7.01534, -7.55357 front fs empty border lc rgb '#6165' lw 0.200001
set object 79 polygon from \
  6.93833, -7.65167 to \
  7.21627, -7.65167 to \
  7.21627, -7.75002 to \
  6.93833, -7.75002 to \
  6.93833, -7.65167 front fs empty border lc rgb '#6165' lw 0.200001
set object 80 polygon from \
  6.86034, -7.74977 to \
  7.13926, -7.74977 to \
  7.13926, -7.84812 to \
  6.86034, -7.84812 to \
  6.86034, -7.74977 front fs empty border lc rgb '#6165' lw 0.200001
set object 81 polygon from \
  6.78137, -7.84787 to \
  7.06127, -7.84787 to \
  7.06127, -7.94622 to \
  6.78137, -7.94622 to \
  6.78137, -7.84787 front fs empty border lc rgb '#6165' lw 0.200001
set object 82 polygon from \
  6.70142, -7.94597 to \
  6.9823, -7.94597 to \
  6.9823, -8.04432 to \
  6.70142, -8.04432 to \
  6.70142, -7.94597 front fs empty border lc rgb '#6165' lw 0.200001
set object 83 polygon from \
  6.62048, -8.04407 to \
  6.90235, -8.04407 to \
  6.90235, -8.14242 to \
  6.62048, -8.14242 to \
  6.62048, -8.04407 front fs empty border lc rgb '#6165' lw 0.200001
set object 84 polygon from \
  6.53857, -8.14217 to \
  6.82142, -8.14217 to \
  6.82142, -8.24052 to \
  6.53857, -8.24052 to \
  6.53857, -8.14217 front fs empty border lc rgb '#6165' lw 0.200001
set object 85 polygon from \
  6.45567, -8.24027 to \
  6.73951, -8.24027 to \
  6.73951, -8.33862 to \
  6.45567, -8.33862 to \
  6.45567, -8.24027 front fs empty border lc rgb '#6165' lw 0.200001
set object 86 polygon from \
  6.37179, -8.33837 to \
  6.65662, -8.33837 to \
  6.65662, -8.43672 to \
  6.37179, -8.43672 to \
  6.37179, -8.33837 front fs empty border lc rgb '#6165' lw 0.200001
set object 87 polygon from \
  6.28694, -8.43647 to \
  6.57274, -8.43647 to \
  6.57274, -8.53482 to \
  6.28694, -8.53482 to \
  6.28694, -8.43647 front fs empty border lc rgb '#6165' lw 0.200001
set object 88 polygon from \
  6.2011, -8.53457 to \
  6.48789, -8.53457 to \
  6.48789, -8.63292 to \
  6.2011, -8.63292 to \
  6.2011, -8.53457 front fs empty border lc rgb '#6165' lw 0.200001
set object 89 polygon from \
  6.11428, -8.63267 to \
  6.40205, -8.63267 to \
  6.40205, -8.73102 to \
  6.11428, -8.73102 to \
  6.11428, -8.63267 front fs empty border lc rgb '#6165' lw 0.200001
set object 90 polygon from \
  6.02648, -8.73077 to \
  6.31523, -8.73077 to \
  6.31523, -8.82912 to \
  6.02648, -8.82912 to \
  6.02648, -8.73077 front fs empty border lc rgb '#6165' lw 0.200001
set object 91 polygon from \
  5.9377, -8.82887 to \
  6.22743, -8.82887 to \
  6.22743, -8.92722 to \
  5.9377, -8.92722 to \
  5.9377, -8.82887 front fs empty border lc rgb '#6165' lw 0.200001
set object 92 polygon from \
  5.84793, -8.92697 to \
  6.13865, -8.92697 to \
  6.13865, -9.02532 to \
  5.84793, -9.02532 to \
  5.84793, -8.92697 front fs empty border lc rgb '#6165' lw 0.200001
set object 93 polygon from \
  5.75719, -9.02507 to \
  6.04889, -9.02507 to \
  6.04889, -9.12342 to \
  5.75719, -9.12342 to \
  5.75719, -9.02507 front fs empty border lc rgb '#6165' lw 0.200001
set object 94 polygon from \
  5.66546, -9.12317 to \
  5.95815, -9.12317 to \
  5.95815, -9.22152 to \
  5.66546, -9.22152 to \
  5.66546, -9.12317 front fs empty border lc rgb '#6165' lw 0.200001
set object 95 polygon from \
  5.57276, -9.22127 to \
  5.86643, -9.22127 to \
  5.86643, -9.31962 to \
  5.57276, -9.31962 to \
  5.57276, -9.22127 front fs empty border lc rgb '#6165' lw 0.200001
set object 96 polygon from \
  5.47907, -9.31937 to \
  5.77373, -9.31937 to \
  5.77373, -9.41772 to \
  5.47907, -9.41772 to \
  5.47907, -9.31937 front fs empty border lc rgb '#6165' lw 0.200001
set object 97 polygon from \
  5.3844, -9.41747 to \
  5.68004, -9.41747 to \
  5.68004, -9.51582 to \
  5.3844, -9.51582 to \
  5.3844, -9.41747 front fs empty border lc rgb '#6165' lw 0.200001
set object 98 polygon from \
  5.28876, -9.51557 to \
  5.58538, -9.51557 to \
  5.58538, -9.61392 to \
  5.28876, -9.61392 to \
  5.28876, -9.51557 front fs empty border lc rgb '#6165' lw 0.200001
set object 99 polygon from \
  5.19213, -9.61367 to \
  5.48973, -9.61367 to \
  5.48973, -9.71202 to \
  5.19213, -9.71202 to \
  5.19213, -9.61367 front fs empty border lc rgb '#6165' lw 0.200001
set object 100 polygon from \
  5.09451, -9.71177 to \
  5.3931, -9.71177 to \
  5.3931, -9.81012 to \
  5.09451, -9.81012 to \
  5.09451, -9.71177 front fs empty border lc rgb '#6165' lw 0.200001
set object 101 polygon from \
  4.99592, -9.80987 to \
  5.2955, -9.80987 to \
  5.2955, -9.90822 to \
  4.99592, -9.90822 to \
  4.99592, -9.80987 front fs empty border lc rgb '#6165' lw 0.200001
set object 102 polygon from \
  4.89635, -9.90797 to \
  5.19691, -9.90797 to \
  5.19691, -10.0063 to \
  4.89635, -10.0063 to \
  4.89635, -9.90797 front fs empty border lc rgb '#6165' lw 0.200001
set object 103 polygon from \
  4.7958, -10.006 to \
  5.09734, -10.006 to \
  5.09734, -10.1044 to \
  4.7958, -10.1044 to \
  4.7958, -10.006 front fs empty border lc rgb '#6165' lw 0.200001
set object 104 polygon from \
  4.69426, -10.1041 to \
  4.99679, -10.1041 to \
  4.99679, -10.2025 to \
  4.69426, -10.2025 to \
  4.69426, -10.1041 front fs empty border lc rgb '#6165' lw 0.200001
set object 105 polygon from \
  4.59175, -10.2022 to \
  4.89525, -10.2022 to \
  4.89525, -10.3006 to \
  4.59175, -10.3006 to \
  4.59175, -10.2022 front fs empty border lc rgb '#6165' lw 0.200001
set object 106 polygon from \
  4.48825, -10.3003 to \
  4.79274, -10.3003 to \
  4.79274, -10.3987 to \
  4.48825, -10.3987 to \
  4.48825, -10.3003 front fs empty border lc rgb '#6165' lw 0.200001
set object 107 polygon from \
  4.38377, -10.3984 to \
  4.68925, -10.3984 to \
  4.68925, -10.4968 to \
  4.38377, -10.4968 to \
  4.38377, -10.3984 front fs empty border lc rgb '#6165' lw 0.200001
set object 108 polygon from \
  4.27831, -10.4965 to \
  4.58477, -10.4965 to \
  4.58477, -10.5949 to \
  4.27831, -10.5949 to \
  4.27831, -10.4965 front fs empty border lc rgb '#6165' lw 0.200001
set object 109 polygon from \
  4.17187, -10.5946 to \
  4.47931, -10.5946 to \
  4.47931, -10.693 to \
  4.17187, -10.693 to \
  4.17187, -10.5946 front fs empty border lc rgb '#6165' lw 0.200001
set object 110 polygon from \
  4.06445, -10.6927 to \
  4.37288, -10.6927 to \
  4.37288, -10.7911 to \
  4.06445, -10.7911 to \
  4.06445, -10.6927 front fs empty border lc rgb '#6165' lw 0.200001
set object 111 polygon from \
  3.95605, -10.7908 to \
  4.26546, -10.7908 to \
  4.26546, -10.8892 to \
  3.95605, -10.8892 to \
  3.95605, -10.7908 front fs empty border lc rgb '#6165' lw 0.200001
set object 112 polygon from \
  3.84667, -10.8889 to \
  4.15706, -10.8889 to \
  4.15706, -10.9873 to \
  3.84667, -10.9873 to \
  3.84667, -10.8889 front fs empty border lc rgb '#6165' lw 0.200001
set object 113 polygon from \
  3.7363, -10.987 to \
  4.04768, -10.987 to \
  4.04768, -11.0854 to \
  3.7363, -11.0854 to \
  3.7363, -10.987 front fs empty border lc rgb '#6165' lw 0.200001
set object 114 polygon from \
  3.62496, -11.0851 to \
  3.93732, -11.0851 to \
  3.93732, -11.1835 to \
  3.62496, -11.1835 to \
  3.62496, -11.0851 front fs empty border lc rgb '#6165' lw 0.200001
set object 115 polygon from \
  3.51263, -11.1832 to \
  3.82598, -11.1832 to \
  3.82598, -11.2816 to \
  3.51263, -11.2816 to \
  3.51263, -11.1832 front fs empty border lc rgb '#6165' lw 0.200001
set object 116 polygon from \
  3.39933, -11.2813 to \
  3.71365, -11.2813 to \
  3.71365, -11.3797 to \
  3.39933, -11.3797 to \
  3.39933, -11.2813 front fs empty border lc rgb '#6165' lw 0.200001
set object 117 polygon from \
  3.28504, -11.3794 to \
  3.60035, -11.3794 to \
  3.60035, -11.4778 to \
  3.28504, -11.4778 to \
  3.28504, -11.3794 front fs empty border lc rgb '#6165' lw 0.200001
set object 118 polygon from \
  3.16977, -11.4775 to \
  3.48606, -11.4775 to \
  3.48606, -11.5759 to \
  3.16977, -11.5759 to \
  3.16977, -11.4775 front fs empty border lc rgb '#6165' lw 0.200001
set object 119 polygon from \
  3.05352, -11.5756 to \
  3.3708, -11.5756 to \
  3.3708, -11.674 to \
  3.05352, -11.674 to \
  3.05352, -11.5756 front fs empty border lc rgb '#6165' lw 0.200001
set object 120 polygon from \
  2.93629, -11.6737 to \
  3.25455, -11.6737 to \
  3.25455, -11.7721 to \
  2.93629, -11.7721 to \
  2.93629, -11.6737 front fs empty border lc rgb '#6165' lw 0.200001
set object 121 polygon from \
  2.81808, -11.7718 to \
  3.13732, -11.7718 to \
  3.13732, -11.8702 to \
  2.81808, -11.8702 to \
  2.81808, -11.7718 front fs empty border lc rgb '#6165' lw 0.200001
set object 122 polygon from \
  2.69889, -11.8699 to \
  3.01911, -11.8699 to \
  3.01911, -11.9683 to \
  2.69889, -11.9683 to \
  2.69889, -11.8699 front fs empty border lc rgb '#6165' lw 0.200001
set object 123 polygon from \
  2.57871, -11.968 to \
  2.89992, -11.968 to \
  2.89992, -12.0664 to \
  2.57871, -12.0664 to \
  2.57871, -11.968 front fs empty border lc rgb '#6165' lw 0.200001
set object 124 polygon from \
  2.45756, -12.0661 to \
  2.77975, -12.0661 to \
  2.77975, -12.1645 to \
  2.45756, -12.1645 to \
  2.45756, -12.0661 front fs empty border lc rgb '#6165' lw 0.200001
set object 125 polygon from \
  2.33542, -12.1642 to \
  2.6586, -12.1642 to \
  2.6586, -12.2626 to \
  2.33542, -12.2626 to \
  2.33542, -12.1642 front fs empty border lc rgb '#6165' lw 0.200001
set object 126 polygon from \
  2.2123, -12.2623 to \
  2.53646, -12.2623 to \
  2.53646, -12.3607 to \
  2.2123, -12.3607 to \
  2.2123, -12.2623 front fs empty border lc rgb '#6165' lw 0.200001
set object 127 polygon from \
  2.08821, -12.3604 to \
  2.41335, -12.3604 to \
  2.41335, -12.4588 to \
  2.08821, -12.4588 to \
  2.08821, -12.3604 front fs empty border lc rgb '#6165' lw 0.200001
set object 128 polygon from \
  1.96313, -12.4585 to \
  2.28926, -12.4585 to \
  2.28926, -12.5569 to \
  1.96313, -12.5569 to \
  1.96313, -12.4585 front fs empty border lc rgb '#6165' lw 0.200001
set object 129 polygon from \
  1.83707, -12.5566 to \
  2.16418, -12.5566 to \
  2.16418, -12.655 to \
  1.83707, -12.655 to \
  1.83707, -12.5566 front fs empty border lc rgb '#6165' lw 0.200001
set object 130 polygon from \
  1.71003, -12.6547 to \
  2.03812, -12.6547 to \
  2.03812, -12.7531 to \
  1.71003, -12.7531 to \
  1.71003, -12.6547 front fs empty border lc rgb '#6165' lw 0.200001
set object 131 polygon from \
  1.58201, -12.7528 to \
  1.91108, -12.7528 to \
  1.91108, -12.8512 to \
  1.58201, -12.8512 to \
  1.58201, -12.7528 front fs empty border lc rgb '#6165' lw 0.200001
set object 132 polygon from \
  1.453, -12.8509 to \
  1.78306, -12.8509 to \
  1.78306, -12.9493 to \
  1.453, -12.9493 to \
  1.453, -12.8509 front fs empty border lc rgb '#6165' lw 0.200001
set object 133 polygon from \
  1.32302, -12.949 to \
  1.65406, -12.949 to \
  1.65406, -13.0474 to \
  1.32302, -13.0474 to \
  1.32302, -12.949 front fs empty border lc rgb '#6165' lw 0.200001
set object 134 polygon from \
  1.19206, -13.0471 to \
  1.52408, -13.0471 to \
  1.52408, -13.1455 to \
  1.19206, -13.1455 to \
  1.19206, -13.0471 front fs empty border lc rgb '#6165' lw 0.200001
set object 135 polygon from \
  1.06011, -13.1452 to \
  1.39312, -13.1452 to \
  1.39312, -13.2436 to \
  1.06011, -13.2436 to \
  1.06011, -13.1452 front fs empty border lc rgb '#6165' lw 0.200001
set object 136 polygon from \
  0.927178, -13.2433 to \
  1.26118, -13.2433 to \
  1.26118, -13.3417 to \
  0.927178, -13.3417 to \
  0.927178, -13.2433 front fs empty border lc rgb '#6165' lw 0.200001
set object 137 polygon from \
  0.79327, -13.3414 to \
  1.12825, -13.3414 to \
  1.12825, -13.4398 to \
  0.79327, -13.4398 to \
  0.79327, -13.3414 front fs empty border lc rgb '#6165' lw 0.200001
set object 138 polygon from \
  0.658382, -13.4395 to \
  0.994343, -13.4395 to \
  0.994343, -13.5379 to \
  0.658382, -13.5379 to \
  0.658382, -13.4395 front fs empty border lc rgb '#6165' lw 0.200001
set object 139 polygon from \
  0.522512, -13.5376 to \
  0.859457, -13.5376 to \
  0.859457, -13.636 to \
  0.522512, -13.636 to \
  0.522512, -13.5376 front fs empty border lc rgb '#6165' lw 0.200001
set object 140 polygon from \
  0.385661, -13.6357 to \
  0.723589, -13.6357 to \
  0.723589, -13.7341 to \
  0.385661, -13.7341 to \
  0.385661, -13.6357 front fs empty border lc rgb '#6165' lw 0.200001
set object 141 polygon from \
  0.247829, -13.7338 to \
  0.586741, -13.7338 to \
  0.586741, -13.8322 to \
  0.247829, -13.8322 to \
  0.247829, -13.7338 front fs empty border lc rgb '#6165' lw 0.200001
set object 142 polygon from \
  0.109017, -13.8319 to \
  0.448912, -13.8319 to \
  0.448912, -13.9303 to \
  0.109017, -13.9303 to \
  0.109017, -13.8319 front fs empty border lc rgb '#6165' lw 0.200001
set object 143 polygon from \
  0, -13.93 to \
  0.310102, -13.93 to \
  0.310102, -14.0284 to \
  0, -14.0284 to \
  0, -13.93 front fs empty border lc rgb '#6165' lw 0.200001
set object 144 polygon from \
  0, -14.0281 to \
  0.17031, -14.0281 to \
  0.17031, -14.1265 to \
  0, -14.1265 to \
  0, -14.0281 front fs empty border lc rgb '#6165' lw 0.200001
set object 145 polygon from \
  0, -14.1262 to \
  0.0295376, -14.1262 to \
  0.0295376, -14.2246 to \
  0, -14.2246 to \
  0, -14.1262 front fs empty border lc rgb '#6165' lw 0.200001
set object 146 polygon from \
  0, 10.6686 to \
  0.106563, 10.6686 to \
  0.106563, 10.3494 to \
  0, 10.3494 to \
  0, 10.6686 front fs empty border lc rgb '#6165' lw 0.200001
set object 147 polygon from \
  0.103003, 10.5705 to \
  0.212758, 10.5705 to \
  0.212758, 10.2513 to \
  0.103003, 10.2513 to \
  0.103003, 10.5705 front fs empty border lc rgb '#6165' lw 0.200001
set object 148 polygon from \
  0.205025, 10.4724 to \
  0.317973, 10.4724 to \
  0.317973, 10.1532 to \
  0.205025, 10.1532 to \
  0.205025, 10.4724 front fs empty border lc rgb '#6165' lw 0.200001
set object 149 polygon from \
  0.306066, 10.3743 to \
  0.422206, 10.3743 to \
  0.422206, 10.0551 to \
  0.306066, 10.0551 to \
  0.306066, 10.3743 front fs empty border lc rgb '#6165' lw 0.200001
set object 150 polygon from \
  0.406126, 10.2762 to \
  0.525459, 10.2762 to \
  0.525459, 9.95694 to \
  0.406126, 9.95694 to \
  0.406126, 10.2762 front fs empty border lc rgb '#6165' lw 0.200001
set object 151 polygon from \
  0.505205, 10.1781 to \
  0.62773, 10.1781 to \
  0.62773, 9.85884 to \
  0.505205, 9.85884 to \
  0.505205, 10.1781 front fs empty border lc rgb '#6165' lw 0.200001
set object 152 polygon from \
  0.603303, 10.08 to \
  0.72902, 10.08 to \
  0.72902, 9.76074 to \
  0.603303, 9.76074 to \
  0.603303, 10.08 front fs empty border lc rgb '#6165' lw 0.200001
set object 153 polygon from \
  0.700419, 9.9819 to \
  0.82933, 9.9819 to \
  0.82933, 9.66264 to \
  0.700419, 9.66264 to \
  0.700419, 9.9819 front fs empty border lc rgb '#6165' lw 0.200001
set object 154 polygon from \
  0.796555, 9.8838 to \
  0.928658, 9.8838 to \
  0.928658, 9.56454 to \
  0.796555, 9.56454 to \
  0.796555, 9.8838 front fs empty border lc rgb '#6165' lw 0.200001
set object 155 polygon from \
  0.89171, 9.7857 to \
  1.02701, 9.7857 to \
  1.02701, 9.46644 to \
  0.89171, 9.46644 to \
  0.89171, 9.7857 front fs empty border lc rgb '#6165' lw 0.200001
set object 156 polygon from \
  0.985884, 9.6876 to \
  1.12438, 9.6876 to \
  1.12438, 9.36834 to \
  0.985884, 9.36834 to \
  0.985884, 9.6876 front fs empty border lc rgb '#6165' lw 0.200001
set object 157 polygon from \
  1.07908, 9.5895 to \
  1.22076, 9.5895 to \
  1.22076, 9.27024 to \
  1.07908, 9.27024 to \
  1.07908, 9.5895 front fs empty border lc rgb '#6165' lw 0.200001
set object 158 polygon from \
  1.17129, 9.4914 to \
  1.31617, 9.4914 to \
  1.31617, 9.17214 to \
  1.17129, 9.17214 to \
  1.17129, 9.4914 front fs empty border lc rgb '#6165' lw 0.200001
set object 159 polygon from \
  1.26252, 9.3933 to \
  1.41059, 9.3933 to \
  1.41059, 9.07404 to \
  1.26252, 9.07404 to \
  1.26252, 9.3933 front fs empty border lc rgb '#6165' lw 0.200001
set object 160 polygon from \
  1.35277, 9.2952 to \
  1.50403, 9.2952 to \
  1.50403, 8.97594 to \
  1.35277, 8.97594 to \
  1.35277, 9.2952 front fs empty border lc rgb '#6165' lw 0.200001
set object 161 polygon from \
  1.44204, 9.1971 to \
  1.59649, 9.1971 to \
  1.59649, 8.87784 to \
  1.44204, 8.87784 to \
  1.44204, 9.1971 front fs empty border lc rgb '#6165' lw 0.200001
set object 162 polygon from \
  1.53033, 9.099 to \
  1.68797, 9.099 to \
  1.68797, 8.77974 to \
  1.53033, 8.77974 to \
  1.53033, 9.099 front fs empty border lc rgb '#6165' lw 0.200001
set object 163 polygon from \
  1.61764, 9.0009 to \
  1.77847, 9.0009 to \
  1.77847, 8.68164 to \
  1.61764, 8.68164 to \
  1.61764, 9.0009 front fs empty border lc rgb '#6165' lw 0.200001
set object 164 polygon from \
  1.70396, 8.9028 to \
  1.86799, 8.9028 to \
  1.86799, 8.58354 to \
  1.70396, 8.58354 to \
  1.70396, 8.9028 front fs empty border lc rgb '#6165' lw 0.200001
set object 165 polygon from \
  1.78931, 8.8047 to \
  1.95653, 8.8047 to \
  1.95653, 8.48544 to \
  1.78931, 8.48544 to \
  1.78931, 8.8047 front fs empty border lc rgb '#6165' lw 0.200001
set object 166 polygon from \
  1.87367, 8.7066 to \
  2.04409, 8.7066 to \
  2.04409, 8.38734 to \
  1.87367, 8.38734 to \
  1.87367, 8.7066 front fs empty border lc rgb '#6165' lw 0.200001
set object 167 polygon from \
  1.95705, 8.6085 to \
  2.13066, 8.6085 to \
  2.13066, 8.28924 to \
  1.95705, 8.28924 to \
  1.95705, 8.6085 front fs empty border lc rgb '#6165' lw 0.200001
set object 168 polygon from \
  2.03946, 8.5104 to \
  2.21626, 8.5104 to \
  2.21626, 8.19114 to \
  2.03946, 8.19114 to \
  2.03946, 8.5104 front fs empty border lc rgb '#6165' lw 0.200001
set object 169 polygon from \
  2.12088, 8.4123 to \
  2.30087, 8.4123 to \
  2.30087, 8.09304 to \
  2.12088, 8.09304 to \
  2.12088, 8.4123 front fs empty border lc rgb '#6165' lw 0.200001
set object 170 polygon from \
  2.20132, 8.3142 to \
  2.3845, 8.3142 to \
  2.3845, 7.99494 to \
  2.20132, 7.99494 to \
  2.20132, 8.3142 front fs empty border lc rgb '#6165' lw 0.200001
set object 171 polygon from \
  2.28078, 8.2161 to \
  2.46715, 8.2161 to \
  2.46715, 7.89684 to \
  2.28078, 7.89684 to \
  2.28078, 8.2161 front fs empty border lc rgb '#6165' lw 0.200001
set object 172 polygon from \
  2.35925, 8.118 to \
  2.54882, 8.118 to \
  2.54882, 7.79874 to \
  2.35925, 7.79874 to \
  2.35925, 8.118 front fs empty border lc rgb '#6165' lw 0.200001
set object 173 polygon from \
  2.43675, 8.0199 to \
  2.62951, 8.0199 to \
  2.62951, 7.70064 to \
  2.43675, 7.70064 to \
  2.43675, 8.0199 front fs empty border lc rgb '#6165' lw 0.200001
set object 174 polygon from \
  2.51327, 7.9218 to \
  2.70922, 7.9218 to \
  2.70922, 7.60254 to \
  2.51327, 7.60254 to \
  2.51327, 7.9218 front fs empty border lc rgb '#6165' lw 0.200001
set object 175 polygon from \
  2.5888, 7.8237 to \
  2.78795, 7.8237 to \
  2.78795, 7.50444 to \
  2.5888, 7.50444 to \
  2.5888, 7.8237 front fs empty border lc rgb '#6165' lw 0.200001
set object 176 polygon from \
  2.66336, 7.7256 to \
  2.86569, 7.7256 to \
  2.86569, 7.40634 to \
  2.66336, 7.40634 to \
  2.66336, 7.7256 front fs empty border lc rgb '#6165' lw 0.200001
set object 177 polygon from \
  2.73693, 7.6275 to \
  2.94246, 7.6275 to \
  2.94246, 7.30824 to \
  2.73693, 7.30824 to \
  2.73693, 7.6275 front fs empty border lc rgb '#6165' lw 0.200001
set object 178 polygon from \
  2.80952, 7.5294 to \
  3.01824, 7.5294 to \
  3.01824, 7.21014 to \
  2.80952, 7.21014 to \
  2.80952, 7.5294 front fs empty border lc rgb '#6165' lw 0.200001
set object 179 polygon from \
  2.88113, 7.4313 to \
  3.09305, 7.4313 to \
  3.09305, 7.11204 to \
  2.88113, 7.11204 to \
  2.88113, 7.4313 front fs empty border lc rgb '#6165' lw 0.200001
set object 180 polygon from \
  2.95176, 7.3332 to \
  3.16687, 7.3332 to \
  3.16687, 7.01394 to \
  2.95176, 7.01394 to \
  2.95176, 7.3332 front fs empty border lc rgb '#6165' lw 0.200001
set object 181 polygon from \
  3.02141, 7.2351 to \
  3.23971, 7.2351 to \
  3.23971, 6.91584 to \
  3.02141, 6.91584 to \
  3.02141, 7.2351 front fs empty border lc rgb '#6165' lw 0.200001
set object 182 polygon from \
  3.09008, 7.137 to \
  3.31157, 7.137 to \
  3.31157, 6.81774 to \
  3.09008, 6.81774 to \
  3.09008, 7.137 front fs empty border lc rgb '#6165' lw 0.200001
set object 183 polygon from \
  3.15776, 7.0389 to \
  3.38245, 7.0389 to \
  3.38245, 6.71964 to \
  3.15776, 6.71964 to \
  3.15776, 7.0389 front fs empty border lc rgb '#6165' lw 0.200001
set object 184 polygon from \
  3.22447, 6.9408 to \
  3.45235, 6.9408 to \
  3.45235, 6.62154 to \
  3.22447, 6.62154 to \
  3.22447, 6.9408 front fs empty border lc rgb '#6165' lw 0.200001
set object 185 polygon from \
  3.29019, 6.8427 to \
  3.52127, 6.8427 to \
  3.52127, 6.52344 to \
  3.29019, 6.52344 to \
  3.29019, 6.8427 front fs empty border lc rgb '#6165' lw 0.200001
set object 186 polygon from \
  3.35494, 6.7446 to \
  3.5892, 6.7446 to \
  3.5892, 6.42534 to \
  3.35494, 6.42534 to \
  3.35494, 6.7446 front fs empty border lc rgb '#6165' lw 0.200001
set object 187 polygon from \
  3.4187, 6.6465 to \
  3.65616, 6.6465 to \
  3.65616, 6.32724 to \
  3.4187, 6.32724 to \
  3.4187, 6.6465 front fs empty border lc rgb '#6165' lw 0.200001
set object 188 polygon from \
  3.48148, 6.5484 to \
  3.72213, 6.5484 to \
  3.72213, 6.22914 to \
  3.48148, 6.22914 to \
  3.48148, 6.5484 front fs empty border lc rgb '#6165' lw 0.200001
set object 189 polygon from \
  3.54328, 6.4503 to \
  3.78713, 6.4503 to \
  3.78713, 6.13104 to \
  3.54328, 6.13104 to \
  3.54328, 6.4503 front fs empty border lc rgb '#6165' lw 0.200001
set object 190 polygon from \
  3.6041, 6.3522 to \
  3.85114, 6.3522 to \
  3.85114, 6.03294 to \
  3.6041, 6.03294 to \
  3.6041, 6.3522 front fs empty border lc rgb '#6165' lw 0.200001
set object 191 polygon from \
  3.66394, 6.2541 to \
  3.91417, 6.2541 to \
  3.91417, 5.93484 to \
  3.66394, 5.93484 to \
  3.66394, 6.2541 front fs empty border lc rgb '#6165' lw 0.200001
set object 192 polygon from \
  3.7228, 6.156 to \
  3.97622, 6.156 to \
  3.97622, 5.83674 to \
  3.7228, 5.83674 to \
  3.7228, 6.156 front fs empty border lc rgb '#6165' lw 0.200001
set object 193 polygon from \
  3.78068, 6.0579 to \
  4.03729, 6.0579 to \
  4.03729, 5.73864 to \
  3.78068, 5.73864 to \
  3.78068, 6.0579 front fs empty border lc rgb '#6165' lw 0.200001
set object 194 polygon from \
  3.83757, 5.9598 to \
  4.09738, 5.9598 to \
  4.09738, 5.64054 to \
  3.83757, 5.64054 to \
  3.83757, 5.9598 front fs empty border lc rgb '#6165' lw 0.200001
set object 195 polygon from \
  3.89349, 5.8617 to \
  4.15649, 5.8617 to \
  4.15649, 5.54244 to \
  3.89349, 5.54244 to \
  3.89349, 5.8617 front fs empty border lc rgb '#6165' lw 0.200001
set object 196 polygon from \
  3.94842, 5.7636 to \
  4.21461, 5.7636 to \
  4.21461, 5.44434 to \
  3.94842, 5.44434 to \
  3.94842, 5.7636 front fs empty border lc rgb '#6165' lw 0.200001
set object 197 polygon from \
  4.00238, 5.6655 to \
  4.27176, 5.6655 to \
  4.27176, 5.34624 to \
  4.00238, 5.34624 to \
  4.00238, 5.6655 front fs empty border lc rgb '#6165' lw 0.200001
set object 198 polygon from \
  4.05535, 5.5674 to \
  4.32792, 5.5674 to \
  4.32792, 5.24814 to \
  4.05535, 5.24814 to \
  4.05535, 5.5674 front fs empty border lc rgb '#6165' lw 0.200001
set object 199 polygon from \
  4.10734, 5.4693 to \
  4.38311, 5.4693 to \
  4.38311, 5.15004 to \
  4.10734, 5.15004 to \
  4.10734, 5.4693 front fs empty border lc rgb '#6165' lw 0.200001
set object 200 polygon from \
  4.15835, 5.3712 to \
  4.43731, 5.3712 to \
  4.43731, 5.05194 to \
  4.15835, 5.05194 to \
  4.15835, 5.3712 front fs empty border lc rgb '#6165' lw 0.200001
set object 201 polygon from \
  4.20838, 5.2731 to \
  4.49053, 5.2731 to \
  4.49053, 4.95384 to \
  4.20838, 4.95384 to \
  4.20838, 5.2731 front fs empty border lc rgb '#6165' lw 0.200001
set object 202 polygon from \
  4.25742, 5.175 to \
  4.54277, 5.175 to \
  4.54277, 4.85574 to \
  4.25742, 4.85574 to \
  4.25742, 5.175 front fs empty border lc rgb '#6165' lw 0.200001
set object 203 polygon from \
  4.30549, 5.0769 to \
  4.59403, 5.0769 to \
  4.59403, 4.75764 to \
  4.30549, 4.75764 to \
  4.30549, 5.0769 front fs empty border lc rgb '#6165' lw 0.200001
set object 204 polygon from \
  4.35258, 4.9788 to \
  4.64431, 4.9788 to \
  4.64431, 4.65954 to \
  4.35258, 4.65954 to \
  4.35258, 4.9788 front fs empty border lc rgb '#6165' lw 0.200001
set object 205 polygon from \
  4.39868, 4.8807 to \
  4.69361, 4.8807 to \
  4.69361, 4.56144 to \
  4.39868, 4.56144 to \
  4.39868, 4.8807 front fs empty border lc rgb '#6165' lw 0.200001
set object 206 polygon from \
  4.44381, 4.7826 to \
  4.74192, 4.7826 to \
  4.74192, 4.46334 to \
  4.44381, 4.46334 to \
  4.44381, 4.7826 front fs empty border lc rgb '#6165' lw 0.200001
set object 207 polygon from \
  4.48795, 4.6845 to \
  4.78926, 4.6845 to \
  4.78926, 4.36524 to \
  4.48795, 4.36524 to \
  4.48795, 4.6845 front fs empty border lc rgb '#6165' lw 0.200001
set object 208 polygon from \
  4.53111, 4.5864 to \
  4.83561, 4.5864 to \
  4.83561, 4.26714 to \
  4.53111, 4.26714 to \
  4.53111, 4.5864 front fs empty border lc rgb '#6165' lw 0.200001
set object 209 polygon from \
  4.57329, 4.4883 to \
  4.88099, 4.4883 to \
  4.88099, 4.16904 to \
  4.57329, 4.16904 to \
  4.57329, 4.4883 front fs empty border lc rgb '#6165' lw 0.200001
set object 210 polygon from \
  4.61449, 4.3902 to \
  4.92538, 4.3902 to \
  4.92538, 4.07094 to \
  4.61449, 4.07094 to \
  4.61449, 4.3902 front fs empty border lc rgb '#6165' lw 0.200001
set object 211 polygon from \
  4.65471, 4.2921 to \
  4.96879, 4.2921 to \
  4.96879, 3.97284 to \
  4.65471, 3.97284 to \
  4.65471, 4.2921 front fs empty border lc rgb '#6165' lw 0.200001
set object 212 polygon from \
  4.69395, 4.194 to \
  5.01122, 4.194 to \
  5.01122, 3.87474 to \
  4.69395, 3.87474 to \
  4.69395, 4.194 front fs empty border lc rgb '#6165' lw 0.200001
set object 213 polygon from \
  4.7322, 4.0959 to \
  5.05267, 4.0959 to \
  5.05267, 3.77664 to \
  4.7322, 3.77664 to \
  4.7322, 4.0959 front fs empty border lc rgb '#6165' lw 0.200001
set object 214 polygon from \
  4.76948, 3.9978 to \
  5.09314, 3.9978 to \
  5.09314, 3.67854 to \
  4.76948, 3.67854 to \
  4.76948, 3.9978 front fs empty border lc rgb '#6165' lw 0.200001
set object 215 polygon from \
  4.80578, 3.8997 to \
  5.13262, 3.8997 to \
  5.13262, 3.58044 to \
  4.80578, 3.58044 to \
  4.80578, 3.8997 front fs empty border lc rgb '#6165' lw 0.200001
set object 216 polygon from \
  4.84109, 3.8016 to \
  5.17113, 3.8016 to \
  5.17113, 3.48234 to \
  4.84109, 3.48234 to \
  4.84109, 3.8016 front fs empty border lc rgb '#6165' lw 0.200001
set object 217 polygon from \
  4.87542, 3.7035 to \
  5.20866, 3.7035 to \
  5.20866, 3.38424 to \
  4.87542, 3.38424 to \
  4.87542, 3.7035 front fs empty border lc rgb '#6165' lw 0.200001
set object 218 polygon from \
  4.90877, 3.6054 to \
  5.2452, 3.6054 to \
  5.2452, 3.28614 to \
  4.90877, 3.28614 to \
  4.90877, 3.6054 front fs empty border lc rgb '#6165' lw 0.200001
set object 219 polygon from \
  4.94114, 3.5073 to \
  5.28076, 3.5073 to \
  5.28076, 3.18804 to \
  4.94114, 3.18804 to \
  4.94114, 3.5073 front fs empty border lc rgb '#6165' lw 0.200001
set object 220 polygon from \
  4.97253, 3.4092 to \
  5.31535, 3.4092 to \
  5.31535, 3.08994 to \
  4.97253, 3.08994 to \
  4.97253, 3.4092 front fs empty border lc rgb '#6165' lw 0.200001
set object 221 polygon from \
  5.00294, 3.3111 to \
  5.34895, 3.3111 to \
  5.34895, 2.99184 to \
  5.00294, 2.99184 to \
  5.00294, 3.3111 front fs empty border lc rgb '#6165' lw 0.200001
set object 222 polygon from \
  5.03237, 3.213 to \
  5.38157, 3.213 to \
  5.38157, 2.89374 to \
  5.03237, 2.89374 to \
  5.03237, 3.213 front fs empty border lc rgb '#6165' lw 0.200001
set object 223 polygon from \
  5.06082, 3.1149 to \
  5.41321, 3.1149 to \
  5.41321, 2.79564 to \
  5.06082, 2.79564 to \
  5.06082, 3.1149 front fs empty border lc rgb '#6165' lw 0.200001
set object 224 polygon from \
  5.08828, 3.0168 to \
  5.44387, 3.0168 to \
  5.44387, 2.69754 to \
  5.08828, 2.69754 to \
  5.08828, 3.0168 front fs empty border lc rgb '#6165' lw 0.200001
set object 225 polygon from \
  5.11477, 2.9187 to \
  5.47354, 2.9187 to \
  5.47354, 2.59944 to \
  5.11477, 2.59944 to \
  5.11477, 2.9187 front fs empty border lc rgb '#6165' lw 0.200001
set object 226 polygon from \
  5.14027, 2.8206 to \
  5.50224, 2.8206 to \
  5.50224, 2.50134 to \
  5.14027, 2.50134 to \
  5.14027, 2.8206 front fs empty border lc rgb '#6165' lw 0.200001
set object 227 polygon from \
  5.1648, 2.7225 to \
  5.52996, 2.7225 to \
  5.52996, 2.40324 to \
  5.1648, 2.40324 to \
  5.1648, 2.7225 front fs empty border lc rgb '#6165' lw 0.200001
set object 228 polygon from \
  5.18834, 2.6244 to \
  5.55669, 2.6244 to \
  5.55669, 2.30514 to \
  5.18834, 2.30514 to \
  5.18834, 2.6244 front fs empty border lc rgb '#6165' lw 0.200001
set object 229 polygon from \
  5.2109, 2.5263 to \
  5.58244, 2.5263 to \
  5.58244, 2.20704 to \
  5.2109, 2.20704 to \
  5.2109, 2.5263 front fs empty border lc rgb '#6165' lw 0.200001
set object 230 polygon from \
  5.23248, 2.4282 to \
  5.60722, 2.4282 to \
  5.60722, 2.10894 to \
  5.23248, 2.10894 to \
  5.23248, 2.4282 front fs empty border lc rgb '#6165' lw 0.200001
set object 231 polygon from \
  5.25308, 2.3301 to \
  5.63101, 2.3301 to \
  5.63101, 2.01084 to \
  5.25308, 2.01084 to \
  5.25308, 2.3301 front fs empty border lc rgb '#6165' lw 0.200001
set object 232 polygon from \
  5.27269, 2.232 to \
  5.65382, 2.232 to \
  5.65382, 1.91274 to \
  5.27269, 1.91274 to \
  5.27269, 2.232 front fs empty border lc rgb '#6165' lw 0.200001
set object 233 polygon from \
  5.29133, 2.1339 to \
  5.67565, 2.1339 to \
  5.67565, 1.81464 to \
  5.29133, 1.81464 to \
  5.29133, 2.1339 front fs empty border lc rgb '#6165' lw 0.200001
set object 234 polygon from \
  5.30899, 2.0358 to \
  5.6965, 2.0358 to \
  5.6965, 1.71654 to \
  5.30899, 1.71654 to \
  5.30899, 2.0358 front fs empty border lc rgb '#6165' lw 0.200001
set object 235 polygon from \
  5.32566, 1.9377 to \
  5.71636, 1.9377 to \
  5.71636, 1.61844 to \
  5.32566, 1.61844 to \
  5.32566, 1.9377 front fs empty border lc rgb '#6165' lw 0.200001
set object 236 polygon from \
  5.34136, 1.8396 to \
  5.73525, 1.8396 to \
  5.73525, 1.52034 to \
  5.34136, 1.52034 to \
  5.34136, 1.8396 front fs empty border lc rgb '#6165' lw 0.200001
set object 237 polygon from \
  5.35607, 1.7415 to \
  5.75315, 1.7415 to \
  5.75315, 1.42224 to \
  5.35607, 1.42224 to \
  5.35607, 1.7415 front fs empty border lc rgb '#6165' lw 0.200001
set object 238 polygon from \
  5.3698, 1.6434 to \
  5.77008, 1.6434 to \
  5.77008, 1.32414 to \
  5.3698, 1.32414 to \
  5.3698, 1.6434 front fs empty border lc rgb '#6165' lw 0.200001
set object 239 polygon from \
  5.38255, 1.5453 to \
  5.78602, 1.5453 to \
  5.78602, 1.22604 to \
  5.38255, 1.22604 to \
  5.38255, 1.5453 front fs empty border lc rgb '#6165' lw 0.200001
set object 240 polygon from \
  5.39432, 1.4472 to \
  5.80098, 1.4472 to \
  5.80098, 1.12794 to \
  5.39432, 1.12794 to \
  5.39432, 1.4472 front fs empty border lc rgb '#6165' lw 0.200001
set object 241 polygon from \
  5.40511, 1.3491 to \
  5.81497, 1.3491 to \
  5.81497, 1.02984 to \
  5.40511, 1.02984 to \
  5.40511, 1.3491 front fs empty border lc rgb '#6165' lw 0.200001
set object 242 polygon from \
  5.41492, 1.251 to \
  5.82797, 1.251 to \
  5.82797, 0.931735 to \
  5.41492, 0.931735 to \
  5.41492, 1.251 front fs empty border lc rgb '#6165' lw 0.200001
set object 243 polygon from \
  5.42375, 1.1529 to \
  5.83999, 1.1529 to \
  5.83999, 0.833635 to \
  5.42375, 0.833635 to \
  5.42375, 1.1529 front fs empty border lc rgb '#6165' lw 0.200001
set object 244 polygon from \
  5.43159, 1.0548 to \
  5.85102, 1.0548 to \
  5.85102, 0.735535 to \
  5.43159, 0.735535 to \
  5.43159, 1.0548 front fs empty border lc rgb '#6165' lw 0.200001
set object 245 polygon from \
  5.43846, 0.956691 to \
  5.86108, 0.956691 to \
  5.86108, 0.637435 to \
  5.43846, 0.637435 to \
  5.43846, 0.956691 front fs empty border lc rgb '#6165' lw 0.200001
set object 246 polygon from \
  5.44434, 0.858591 to \
  5.87016, 0.858591 to \
  5.87016, 0.539335 to \
  5.44434, 0.539335 to \
  5.44434, 0.858591 front fs empty border lc rgb '#6165' lw 0.200001
set object 247 polygon from \
  5.44924, 0.760491 to \
  5.87825, 0.760491 to \
  5.87825, 0.441235 to \
  5.44924, 0.441235 to \
  5.44924, 0.760491 front fs empty border lc rgb '#6165' lw 0.200001
set object 248 polygon from \
  5.45316, 0.662391 to \
  5.88537, 0.662391 to \
  5.88537, 0.343135 to \
  5.45316, 0.343135 to \
  5.45316, 0.662391 front fs empty border lc rgb '#6165' lw 0.200001
set object 249 polygon from \
  5.45611, 0.564291 to \
  5.8915, 0.564291 to \
  5.8915, 0.245035 to \
  5.45611, 0.245035 to \
  5.45611, 0.564291 front fs empty border lc rgb '#6165' lw 0.200001
set object 250 polygon from \
  5.45806, 0.466191 to \
  5.89665, 0.466191 to \
  5.89665, 0.146935 to \
  5.45806, 0.146935 to \
  5.45806, 0.466191 front fs empty border lc rgb '#6165' lw 0.200001
set object 251 polygon from \
  5.45904, 0.368091 to \
  5.90083, 0.368091 to \
  5.90083, 0.0488346 to \
  5.45904, 0.0488346 to \
  5.45904, 0.368091 front fs empty border lc rgb '#6165' lw 0.200001
set object 252 polygon from \
  5.45904, 0.269991 to \
  5.90402, 0.269991 to \
  5.90402, -0.0492654 to \
  5.45904, -0.0492654 to \
  5.45904, 0.269991 front fs empty border lc rgb '#6165' lw 0.200001
set object 253 polygon from \
  5.45806, 0.171891 to \
  5.90622, 0.171891 to \
  5.90622, -0.147365 to \
  5.45806, -0.147365 to \
  5.45806, 0.171891 front fs empty border lc rgb '#6165' lw 0.200001
set object 254 polygon from \
  5.45609, 0.0737906 to \
  5.90745, 0.0737906 to \
  5.90745, -0.245465 to \
  5.45609, -0.245465 to \
  5.45609, 0.0737906 front fs empty border lc rgb '#6165' lw 0.200001
set object 255 polygon from \
  5.45315, -0.0243094 to \
  5.9077, -0.0243094 to \
  5.9077, -0.343565 to \
  5.45315, -0.343565 to \
  5.45315, -0.0243094 front fs empty border lc rgb '#6165' lw 0.200001
set object 256 polygon from \
  5.44922, -0.122409 to \
  5.90697, -0.122409 to \
  5.90697, -0.441665 to \
  5.44922, -0.441665 to \
  5.44922, -0.122409 front fs empty border lc rgb '#6165' lw 0.200001
set object 257 polygon from \
  5.44432, -0.220509 to \
  5.90525, -0.220509 to \
  5.90525, -0.539765 to \
  5.44432, -0.539765 to \
  5.44432, -0.220509 front fs empty border lc rgb '#6165' lw 0.200001
set object 258 polygon from \
  5.43843, -0.318609 to \
  5.90256, -0.318609 to \
  5.90256, -0.637865 to \
  5.43843, -0.637865 to \
  5.43843, -0.318609 front fs empty border lc rgb '#6165' lw 0.200001
set object 259 polygon from \
  5.43156, -0.416709 to \
  5.89888, -0.416709 to \
  5.89888, -0.735965 to \
  5.43156, -0.735965 to \
  5.43156, -0.416709 front fs empty border lc rgb '#6165' lw 0.200001
set object 260 polygon from \
  5.42371, -0.514809 to \
  5.89422, -0.514809 to \
  5.89422, -0.834065 to \
  5.42371, -0.834065 to \
  5.42371, -0.514809 front fs empty border lc rgb '#6165' lw 0.200001
set object 261 polygon from \
  5.41488, -0.612909 to \
  5.88858, -0.612909 to \
  5.88858, -0.932165 to \
  5.41488, -0.932165 to \
  5.41488, -0.612909 front fs empty border lc rgb '#6165' lw 0.200001
set object 262 polygon from \
  5.40507, -0.711009 to \
  5.88196, -0.711009 to \
  5.88196, -1.03026 to \
  5.40507, -1.03026 to \
  5.40507, -0.711009 front fs empty border lc rgb '#6165' lw 0.200001
set object 263 polygon from \
  5.39427, -0.809109 to \
  5.87436, -0.809109 to \
  5.87436, -1.12836 to \
  5.39427, -1.12836 to \
  5.39427, -0.809109 front fs empty border lc rgb '#6165' lw 0.200001
set object 264 polygon from \
  5.3825, -0.907209 to \
  5.86578, -0.907209 to \
  5.86578, -1.22646 to \
  5.3825, -1.22646 to \
  5.3825, -0.907209 front fs empty border lc rgb '#6165' lw 0.200001
set object 265 polygon from \
  5.36974, -1.0053 to \
  5.85622, -1.0053 to \
  5.85622, -1.32456 to \
  5.36974, -1.32456 to \
  5.36974, -1.0053 front fs empty border lc rgb '#6165' lw 0.200001
set object 266 polygon from \
  5.35601, -1.1034 to \
  5.84568, -1.1034 to \
  5.84568, -1.42266 to \
  5.35601, -1.42266 to \
  5.35601, -1.1034 front fs empty border lc rgb '#6165' lw 0.200001
set object 267 polygon from \
  5.34129, -1.2015 to \
  5.83415, -1.2015 to \
  5.83415, -1.52076 to \
  5.34129, -1.52076 to \
  5.34129, -1.2015 front fs empty border lc rgb '#6165' lw 0.200001
set object 268 polygon from \
  5.32559, -1.2996 to \
  5.82165, -1.2996 to \
  5.82165, -1.61886 to \
  5.32559, -1.61886 to \
  5.32559, -1.2996 front fs empty border lc rgb '#6165' lw 0.200001
set object 269 polygon from \
  5.30891, -1.3977 to \
  5.80816, -1.3977 to \
  5.80816, -1.71696 to \
  5.30891, -1.71696 to \
  5.30891, -1.3977 front fs empty border lc rgb '#6165' lw 0.200001
set object 270 polygon from \
  5.29125, -1.4958 to \
  5.79369, -1.4958 to \
  5.79369, -1.81506 to \
  5.29125, -1.81506 to \
  5.29125, -1.4958 front fs empty border lc rgb '#6165' lw 0.200001
set object 271 polygon from \
  5.27261, -1.5939 to \
  5.77824, -1.5939 to \
  5.77824, -1.91316 to \
  5.27261, -1.91316 to \
  5.27261, -1.5939 front fs empty border lc rgb '#6165' lw 0.200001
set object 272 polygon from \
  5.25299, -1.692 to \
  5.76181, -1.692 to \
  5.76181, -2.01126 to \
  5.25299, -2.01126 to \
  5.25299, -1.692 front fs empty border lc rgb '#6165' lw 0.200001
set object 273 polygon from \
  5.23239, -1.7901 to \
  5.7444, -1.7901 to \
  5.7444, -2.10936 to \
  5.23239, -2.10936 to \
  5.23239, -1.7901 front fs empty border lc rgb '#6165' lw 0.200001
set object 274 polygon from \
  5.2108, -1.8882 to \
  5.72601, -1.8882 to \
  5.72601, -2.20746 to \
  5.2108, -2.20746 to \
  5.2108, -1.8882 front fs empty border lc rgb '#6165' lw 0.200001
set object 275 polygon from \
  5.18824, -1.9863 to \
  5.70664, -1.9863 to \
  5.70664, -2.30556 to \
  5.18824, -2.30556 to \
  5.18824, -1.9863 front fs empty border lc rgb '#6165' lw 0.200001
set object 276 polygon from \
  5.16469, -2.0844 to \
  5.68629, -2.0844 to \
  5.68629, -2.40366 to \
  5.16469, -2.40366 to \
  5.16469, -2.0844 front fs empty border lc rgb '#6165' lw 0.200001
set object 277 polygon from \
  5.14016, -2.1825 to \
  5.66495, -2.1825 to \
  5.66495, -2.50176 to \
  5.14016, -2.50176 to \
  5.14016, -2.1825 front fs empty border lc rgb '#6165' lw 0.200001
set object 278 polygon from \
  5.11465, -2.2806 to \
  5.64264, -2.2806 to \
  5.64264, -2.59986 to \
  5.11465, -2.59986 to \
  5.11465, -2.2806 front fs empty border lc rgb '#6165' lw 0.200001
set object 279 polygon from \
  5.08817, -2.3787 to \
  5.61934, -2.3787 to \
  5.61934, -2.69796 to \
  5.08817, -2.69796 to \
  5.08817, -2.3787 front fs empty border lc rgb '#6165' lw 0.200001
set object 280 polygon from \
  5.0607, -2.4768 to \
  5.59506, -2.4768 to \
  5.59506, -2.79606 to \
  5.0607, -2.79606 to \
  5.0607, -2.4768 front fs empty border lc rgb '#6165' lw 0.200001
set object 281 polygon from \
  5.03224, -2.5749 to \
  5.5698, -2.5749 to \
  5.5698, -2.89416 to \
  5.03224, -2.89416 to \
  5.03224, -2.5749 front fs empty border lc rgb '#6165' lw 0.200001
set object 282 polygon from \
  5.00281, -2.673 to \
  5.54356, -2.673 to \
  5.54356, -2.99226 to \
  5.00281, -2.99226 to \
  5.00281, -2.673 front fs empty border lc rgb '#6165' lw 0.200001
set object 283 polygon from \
  4.9724, -2.7711 to \
  5.51634, -2.7711 to \
  5.51634, -3.09036 to \
  4.9724, -3.09036 to \
  4.9724, -2.7711 front fs empty border lc rgb '#6165' lw 0.200001
set object 284 polygon from \
  4.941, -2.8692 to \
  5.48814, -2.8692 to \
  5.48814, -3.18846 to \
  4.941, -3.18846 to \
  4.941, -2.8692 front fs empty border lc rgb '#6165' lw 0.200001
set object 285 polygon from \
  4.90863, -2.9673 to \
  5.45896, -2.9673 to \
  5.45896, -3.28656 to \
  4.90863, -3.28656 to \
  4.90863, -2.9673 front fs empty border lc rgb '#6165' lw 0.200001
set object 286 polygon from \
  4.87527, -3.0654 to \
  5.42879, -3.0654 to \
  5.42879, -3.38466 to \
  4.87527, -3.38466 to \
  4.87527, -3.0654 front fs empty border lc rgb '#6165' lw 0.200001
set object 287 polygon from \
  4.84094, -3.1635 to \
  5.39765, -3.1635 to \
  5.39765, -3.48276 to \
  4.84094, -3.48276 to \
  4.84094, -3.1635 front fs empty border lc rgb '#6165' lw 0.200001
set object 288 polygon from \
  4.80562, -3.2616 to \
  5.36552, -3.2616 to \
  5.36552, -3.58086 to \
  4.80562, -3.58086 to \
  4.80562, -3.2616 front fs empty border lc rgb '#6165' lw 0.200001
set object 289 polygon from \
  4.76932, -3.3597 to \
  5.33242, -3.3597 to \
  5.33242, -3.67896 to \
  4.76932, -3.67896 to \
  4.76932, -3.3597 front fs empty border lc rgb '#6165' lw 0.200001
set object 290 polygon from \
  4.73204, -3.4578 to \
  5.29833, -3.4578 to \
  5.29833, -3.77706 to \
  4.73204, -3.77706 to \
  4.73204, -3.4578 front fs empty border lc rgb '#6165' lw 0.200001
set object 291 polygon from \
  4.69378, -3.5559 to \
  5.26326, -3.5559 to \
  5.26326, -3.87516 to \
  4.69378, -3.87516 to \
  4.69378, -3.5559 front fs empty border lc rgb '#6165' lw 0.200001
set object 292 polygon from \
  4.65454, -3.654 to \
  5.22721, -3.654 to \
  5.22721, -3.97326 to \
  4.65454, -3.97326 to \
  4.65454, -3.654 front fs empty border lc rgb '#6165' lw 0.200001
set object 293 polygon from \
  4.61431, -3.7521 to \
  5.19018, -3.7521 to \
  5.19018, -4.07136 to \
  4.61431, -4.07136 to \
  4.61431, -3.7521 front fs empty border lc rgb '#6165' lw 0.200001
set object 294 polygon from \
  4.57311, -3.8502 to \
  5.15217, -3.8502 to \
  5.15217, -4.16946 to \
  4.57311, -4.16946 to \
  4.57311, -3.8502 front fs empty border lc rgb '#6165' lw 0.200001
set object 295 polygon from \
  4.53092, -3.9483 to \
  5.11318, -3.9483 to \
  5.11318, -4.26756 to \
  4.53092, -4.26756 to \
  4.53092, -3.9483 front fs empty border lc rgb '#6165' lw 0.200001
set object 296 polygon from \
  4.48776, -4.0464 to \
  5.0732, -4.0464 to \
  5.0732, -4.36566 to \
  4.48776, -4.36566 to \
  4.48776, -4.0464 front fs empty border lc rgb '#6165' lw 0.200001
set object 297 polygon from \
  4.44361, -4.1445 to \
  5.03225, -4.1445 to \
  5.03225, -4.46376 to \
  4.44361, -4.46376 to \
  4.44361, -4.1445 front fs empty border lc rgb '#6165' lw 0.200001
set object 298 polygon from \
  4.39848, -4.2426 to \
  4.99031, -4.2426 to \
  4.99031, -4.56186 to \
  4.39848, -4.56186 to \
  4.39848, -4.2426 front fs empty border lc rgb '#6165' lw 0.200001
set object 299 polygon from \
  4.35237, -4.3407 to \
  4.9474, -4.3407 to \
  4.9474, -4.65996 to \
  4.35237, -4.65996 to \
  4.35237, -4.3407 front fs empty border lc rgb '#6165' lw 0.200001
set object 300 polygon from \
  4.30528, -4.4388 to \
  4.9035, -4.4388 to \
  4.9035, -4.75806 to \
  4.30528, -4.75806 to \
  4.30528, -4.4388 front fs empty border lc rgb '#6165' lw 0.200001
set object 301 polygon from \
  4.25721, -4.5369 to \
  4.85862, -4.5369 to \
  4.85862, -4.85616 to \
  4.25721, -4.85616 to \
  4.25721, -4.5369 front fs empty border lc rgb '#6165' lw 0.200001
set object 302 polygon from \
  4.20816, -4.635 to \
  4.81276, -4.635 to \
  4.81276, -4.95426 to \
  4.20816, -4.95426 to \
  4.20816, -4.635 front fs empty border lc rgb '#6165' lw 0.200001
set object 303 polygon from \
  4.15813, -4.7331 to \
  4.76592, -4.7331 to \
  4.76592, -5.05236 to \
  4.15813, -5.05236 to \
  4.15813, -4.7331 front fs empty border lc rgb '#6165' lw 0.200001
set object 304 polygon from \
  4.10711, -4.8312 to \
  4.7181, -4.8312 to \
  4.7181, -5.15046 to \
  4.10711, -5.15046 to \
  4.10711, -4.8312 front fs empty border lc rgb '#6165' lw 0.200001
set object 305 polygon from \
  4.05512, -4.9293 to \
  4.6693, -4.9293 to \
  4.6693, -5.24856 to \
  4.05512, -5.24856 to \
  4.05512, -4.9293 front fs empty border lc rgb '#6165' lw 0.200001
set object 306 polygon from \
  4.00214, -5.0274 to \
  4.61951, -5.0274 to \
  4.61951, -5.34666 to \
  4.00214, -5.34666 to \
  4.00214, -5.0274 front fs empty border lc rgb '#6165' lw 0.200001
set object 307 polygon from \
  3.94818, -5.1255 to \
  4.56875, -5.1255 to \
  4.56875, -5.44476 to \
  3.94818, -5.44476 to \
  3.94818, -5.1255 front fs empty border lc rgb '#6165' lw 0.200001
set object 308 polygon from \
  3.89324, -5.2236 to \
  4.517, -5.2236 to \
  4.517, -5.54286 to \
  3.89324, -5.54286 to \
  3.89324, -5.2236 front fs empty border lc rgb '#6165' lw 0.200001
set object 309 polygon from \
  3.83733, -5.3217 to \
  4.46428, -5.3217 to \
  4.46428, -5.64096 to \
  3.83733, -5.64096 to \
  3.83733, -5.3217 front fs empty border lc rgb '#6165' lw 0.200001
set object 310 polygon from \
  3.78043, -5.4198 to \
  4.41057, -5.4198 to \
  4.41057, -5.73906 to \
  3.78043, -5.73906 to \
  3.78043, -5.4198 front fs empty border lc rgb '#6165' lw 0.200001
set object 311 polygon from \
  3.72254, -5.5179 to \
  4.35588, -5.5179 to \
  4.35588, -5.83716 to \
  3.72254, -5.83716 to \
  3.72254, -5.5179 front fs empty border lc rgb '#6165' lw 0.200001
set object 312 polygon from \
  3.66368, -5.616 to \
  4.30021, -5.616 to \
  4.30021, -5.93526 to \
  3.66368, -5.93526 to \
  3.66368, -5.616 front fs empty border lc rgb '#6165' lw 0.200001
set object 313 polygon from \
  3.60384, -5.7141 to \
  4.24356, -5.7141 to \
  4.24356, -6.03336 to \
  3.60384, -6.03336 to \
  3.60384, -5.7141 front fs empty border lc rgb '#6165' lw 0.200001
set object 314 polygon from \
  3.54302, -5.8122 to \
  4.18593, -5.8122 to \
  4.18593, -6.13146 to \
  3.54302, -6.13146 to \
  3.54302, -5.8122 front fs empty border lc rgb '#6165' lw 0.200001
set object 315 polygon from \
  3.48121, -5.9103 to \
  4.12732, -5.9103 to \
  4.12732, -6.22956 to \
  3.48121, -6.22956 to \
  3.48121, -5.9103 front fs empty border lc rgb '#6165' lw 0.200001
set object 316 polygon from \
  3.41842, -6.0084 to \
  4.06772, -6.0084 to \
  4.06772, -6.32766 to \
  3.41842, -6.32766 to \
  3.41842, -6.0084 front fs empty border lc rgb '#6165' lw 0.200001
set object 317 polygon from \
  3.35466, -6.1065 to \
  4.00715, -6.1065 to \
  4.00715, -6.42576 to \
  3.35466, -6.42576 to \
  3.35466, -6.1065 front fs empty border lc rgb '#6165' lw 0.200001
set object 318 polygon from \
  3.28991, -6.2046 to \
  3.94559, -6.2046 to \
  3.94559, -6.52386 to \
  3.28991, -6.52386 to \
  3.28991, -6.2046 front fs empty border lc rgb '#6165' lw 0.200001
set object 319 polygon from \
  3.22418, -6.3027 to \
  3.88305, -6.3027 to \
  3.88305, -6.62196 to \
  3.22418, -6.62196 to \
  3.22418, -6.3027 front fs empty border lc rgb '#6165' lw 0.200001
set object 320 polygon from \
  3.15747, -6.4008 to \
  3.81954, -6.4008 to \
  3.81954, -6.72006 to \
  3.15747, -6.72006 to \
  3.15747, -6.4008 front fs empty border lc rgb '#6165' lw 0.200001
set object 321 polygon from \
  3.08978, -6.4989 to \
  3.75504, -6.4989 to \
  3.75504, -6.81816 to \
  3.08978, -6.81816 to \
  3.08978, -6.4989 front fs empty border lc rgb '#6165' lw 0.200001
set object 322 polygon from \
  3.02111, -6.597 to \
  3.68956, -6.597 to \
  3.68956, -6.91626 to \
  3.02111, -6.91626 to \
  3.02111, -6.597 front fs empty border lc rgb '#6165' lw 0.200001
set object 323 polygon from \
  2.95145, -6.6951 to \
  3.6231, -6.6951 to \
  3.6231, -7.01436 to \
  2.95145, -7.01436 to \
  2.95145, -6.6951 front fs empty border lc rgb '#6165' lw 0.200001
set object 324 polygon from \
  2.88082, -6.7932 to \
  3.55566, -6.7932 to \
  3.55566, -7.11246 to \
  2.88082, -7.11246 to \
  2.88082, -6.7932 front fs empty border lc rgb '#6165' lw 0.200001
set object 325 polygon from \
  2.8092, -6.8913 to \
  3.48723, -6.8913 to \
  3.48723, -7.21056 to \
  2.8092, -7.21056 to \
  2.8092, -6.8913 front fs empty border lc rgb '#6165' lw 0.200001
set object 326 polygon from \
  2.73661, -6.9894 to \
  3.41783, -6.9894 to \
  3.41783, -7.30866 to \
  2.73661, -7.30866 to \
  2.73661, -6.9894 front fs empty border lc rgb '#6165' lw 0.200001
set object 327 polygon from \
  2.66303, -7.0875 to \
  3.34745, -7.0875 to \
  3.34745, -7.40676 to \
  2.66303, -7.40676 to \
  2.66303, -7.0875 front fs empty border lc rgb '#6165' lw 0.200001
set object 328 polygon from \
  2.58847, -7.1856 to \
  3.27608, -7.1856 to \
  3.27608, -7.50486 to \
  2.58847, -7.50486 to \
  2.58847, -7.1856 front fs empty border lc rgb '#6165' lw 0.200001
set object 329 polygon from \
  2.51293, -7.2837 to \
  3.20373, -7.2837 to \
  3.20373, -7.60296 to \
  2.51293, -7.60296 to \
  2.51293, -7.2837 front fs empty border lc rgb '#6165' lw 0.200001
set object 330 polygon from \
  2.43641, -7.3818 to \
  3.13041, -7.3818 to \
  3.13041, -7.70106 to \
  2.43641, -7.70106 to \
  2.43641, -7.3818 front fs empty border lc rgb '#6165' lw 0.200001
set object 331 polygon from \
  2.35891, -7.4799 to \
  3.0561, -7.4799 to \
  3.0561, -7.79916 to \
  2.35891, -7.79916 to \
  2.35891, -7.4799 front fs empty border lc rgb '#6165' lw 0.200001
set object 332 polygon from \
  2.28043, -7.578 to \
  2.98081, -7.578 to \
  2.98081, -7.89726 to \
  2.28043, -7.89726 to \
  2.28043, -7.578 front fs empty border lc rgb '#6165' lw 0.200001
set object 333 polygon from \
  2.20097, -7.6761 to \
  2.90454, -7.6761 to \
  2.90454, -7.99536 to \
  2.20097, -7.99536 to \
  2.20097, -7.6761 front fs empty border lc rgb '#6165' lw 0.200001
set object 334 polygon from \
  2.12052, -7.7742 to \
  2.82729, -7.7742 to \
  2.82729, -8.09346 to \
  2.12052, -8.09346 to \
  2.12052, -7.7742 front fs empty border lc rgb '#6165' lw 0.200001
set object 335 polygon from \
  2.0391, -7.8723 to \
  2.74905, -7.8723 to \
  2.74905, -8.19156 to \
  2.0391, -8.19156 to \
  2.0391, -7.8723 front fs empty border lc rgb '#6165' lw 0.200001
set object 336 polygon from \
  1.95669, -7.9704 to \
  2.66984, -7.9704 to \
  2.66984, -8.28966 to \
  1.95669, -8.28966 to \
  1.95669, -7.9704 front fs empty border lc rgb '#6165' lw 0.200001
set object 337 polygon from \
  1.8733, -8.0685 to \
  2.58964, -8.0685 to \
  2.58964, -8.38776 to \
  1.8733, -8.38776 to \
  1.8733, -8.0685 front fs empty border lc rgb '#6165' lw 0.200001
set object 338 polygon from \
  1.78894, -8.1666 to \
  2.50847, -8.1666 to \
  2.50847, -8.48586 to \
  1.78894, -8.48586 to \
  1.78894, -8.1666 front fs empty border lc rgb '#6165' lw 0.200001
set object 339 polygon from \
  1.70359, -8.2647 to \
  2.42631, -8.2647 to \
  2.42631, -8.58396 to \
  1.70359, -8.58396 to \
  1.70359, -8.2647 front fs empty border lc rgb '#6165' lw 0.200001
set object 340 polygon from \
  1.61726, -8.3628 to \
  2.34318, -8.3628 to \
  2.34318, -8.68206 to \
  1.61726, -8.68206 to \
  1.61726, -8.3628 front fs empty border lc rgb '#6165' lw 0.200001
set object 341 polygon from \
  1.52994, -8.4609 to \
  2.25906, -8.4609 to \
  2.25906, -8.78016 to \
  1.52994, -8.78016 to \
  1.52994, -8.4609 front fs empty border lc rgb '#6165' lw 0.200001
set object 342 polygon from \
  1.44165, -8.559 to \
  2.17396, -8.559 to \
  2.17396, -8.87826 to \
  1.44165, -8.87826 to \
  1.44165, -8.559 front fs empty border lc rgb '#6165' lw 0.200001
set object 343 polygon from \
  1.35238, -8.6571 to \
  2.08788, -8.6571 to \
  2.08788, -8.97636 to \
  1.35238, -8.97636 to \
  1.35238, -8.6571 front fs empty border lc rgb '#6165' lw 0.200001
set object 344 polygon from \
  1.26213, -8.7552 to \
  2.00081, -8.7552 to \
  2.00081, -9.07446 to \
  1.26213, -9.07446 to \
  1.26213, -8.7552 front fs empty border lc rgb '#6165' lw 0.200001
set object 345 polygon from \
  1.17089, -8.8533 to \
  1.91277, -8.8533 to \
  1.91277, -9.17256 to \
  1.17089, -9.17256 to \
  1.17089, -8.8533 front fs empty border lc rgb '#6165' lw 0.200001
set object 346 polygon from \
  1.07867, -8.9514 to \
  1.82375, -8.9514 to \
  1.82375, -9.27066 to \
  1.07867, -9.27066 to \
  1.07867, -8.9514 front fs empty border lc rgb '#6165' lw 0.200001
set object 347 polygon from \
  0.985472, -9.0495 to \
  1.73374, -9.0495 to \
  1.73374, -9.36876 to \
  0.985472, -9.36876 to \
  0.985472, -9.0495 front fs empty border lc rgb '#6165' lw 0.200001
set object 348 polygon from \
  0.891294, -9.1476 to \
  1.64276, -9.1476 to \
  1.64276, -9.46686 to \
  0.891294, -9.46686 to \
  0.891294, -9.1476 front fs empty border lc rgb '#6165' lw 0.200001
set object 349 polygon from \
  0.796135, -9.2457 to \
  1.55079, -9.2457 to \
  1.55079, -9.56496 to \
  0.796135, -9.56496 to \
  0.796135, -9.2457 front fs empty border lc rgb '#6165' lw 0.200001
set object 350 polygon from \
  0.699995, -9.3438 to \
  1.45784, -9.3438 to \
  1.45784, -9.66306 to \
  0.699995, -9.66306 to \
  0.699995, -9.3438 front fs empty border lc rgb '#6165' lw 0.200001
set object 351 polygon from \
  0.602874, -9.4419 to \
  1.36392, -9.4419 to \
  1.36392, -9.76116 to \
  0.602874, -9.76116 to \
  0.602874, -9.4419 front fs empty border lc rgb '#6165' lw 0.200001
set object 352 polygon from \
  0.504772, -9.54 to \
  1.26901, -9.54 to \
  1.26901, -9.85926 to \
  0.504772, -9.85926 to \
  0.504772, -9.54 front fs empty border lc rgb '#6165' lw 0.200001
set object 353 polygon from \
  0.405689, -9.6381 to \
  1.17312, -9.6381 to \
  1.17312, -9.95736 to \
  0.405689, -9.95736 to \
  0.405689, -9.6381 front fs empty border lc rgb '#6165' lw 0.200001
set object 354 polygon from \
  0.305624, -9.7362 to \
  1.07624, -9.7362 to \
  1.07624, -10.0554 to \
  0.305624, -10.0554 to \
  0.305624, -9.7362 front fs empty border lc rgb '#6165' lw 0.200001
set object 355 polygon from \
  0.204579, -9.8343 to \
  0.978387, -9.8343 to \
  0.978387, -10.1535 to \
  0.204579, -10.1535 to \
  0.204579, -9.8343 front fs empty border lc rgb '#6165' lw 0.200001
set object 356 polygon from \
  0.102553, -9.9324 to \
  0.879553, -9.9324 to \
  0.879553, -10.2516 to \
  0.102553, -10.2516 to \
  0.102553, -9.9324 front fs empty border lc rgb '#6165' lw 0.200001
set object 357 polygon from \
  0, -10.0305 to \
  0.779739, -10.0305 to \
  0.779739, -10.3497 to \
  0, -10.3497 to \
  0, -10.0305 front fs empty border lc rgb '#6165' lw 0.200001
set object 358 polygon from \
  0, -10.1286 to \
  0.678943, -10.1286 to \
  0.678943, -10.4478 to \
  0, -10.4478 to \
  0, -10.1286 front fs empty border lc rgb '#6165' lw 0.200001
set object 359 polygon from \
  0, -10.2267 to \
  0.577166, -10.2267 to \
  0.577166, -10.5459 to \
  0, -10.5459 to \
  0, -10.2267 front fs empty border lc rgb '#6165' lw 0.200001
set object 360 polygon from \
  0, -10.3248 to \
  0.474409, -10.3248 to \
  0.474409, -10.644 to \
  0, -10.644 to \
  0, -10.3248 front fs empty border lc rgb '#6165' lw 0.200001
set object 361 polygon from \
  0, -10.4229 to \
  0.37067, -10.4229 to \
  0.37067, -10.7421 to \
  0, -10.7421 to \
  0, -10.4229 front fs empty border lc rgb '#6165' lw 0.200001
set object 362 polygon from \
  0, -10.521 to \
  0.265951, -10.521 to \
  0.265951, -10.8402 to \
  0, -10.8402 to \
  0, -10.521 front fs empty border lc rgb '#6165' lw 0.200001
set object 363 polygon from \
  0, -10.6191 to \
  0.16025, -10.6191 to \
  0.16025, -10.9383 to \
  0, -10.9383 to \
  0, -10.6191 front fs empty border lc rgb '#6165' lw 0.200001
set object 364 polygon from \
  0, -10.7172 to \
  0.053568, -10.7172 to \
  0.053568, -11.0364 to \
  0, -11.0364 to \
  0, -10.7172 front fs empty border lc rgb '#6165' lw 0.200001
set object 365 polygon from \
  0, 8.27748 to \
  0.0826513, 8.27748 to \
  0.0826513, 7.42466 to \
  0, 7.42466 to \
  0, 8.27748 front fs empty border lc rgb '#6165' lw 0.200001
set object 366 polygon from \
  0.0737561, 8.17938 to \
  0.164936, 8.17938 to \
  0.164936, 7.32656 to \
  0.0737561, 7.32656 to \
  0.0737561, 8.17938 front fs empty border lc rgb '#6165' lw 0.200001
set object 367 polygon from \
  0.146532, 8.08128 to \
  0.246239, 8.08128 to \
  0.246239, 7.22846 to \
  0.146532, 7.22846 to \
  0.146532, 8.08128 front fs empty border lc rgb '#6165' lw 0.200001
set object 368 polygon from \
  0.218326, 7.98318 to \
  0.326561, 7.98318 to \
  0.326561, 7.13036 to \
  0.218326, 7.13036 to \
  0.218326, 7.98318 front fs empty border lc rgb '#6165' lw 0.200001
set object 369 polygon from \
  0.289139, 7.88508 to \
  0.405903, 7.88508 to \
  0.405903, 7.03226 to \
  0.289139, 7.03226 to \
  0.289139, 7.88508 front fs empty border lc rgb '#6165' lw 0.200001
set object 370 polygon from \
  0.358971, 7.78698 to \
  0.484263, 7.78698 to \
  0.484263, 6.93416 to \
  0.358971, 6.93416 to \
  0.358971, 7.78698 front fs empty border lc rgb '#6165' lw 0.200001
set object 371 polygon from \
  0.427822, 7.68888 to \
  0.561642, 7.68888 to \
  0.561642, 6.83606 to \
  0.427822, 6.83606 to \
  0.427822, 7.68888 front fs empty border lc rgb '#6165' lw 0.200001
set object 372 polygon from \
  0.495692, 7.59078 to \
  0.63804, 7.59078 to \
  0.63804, 6.73796 to \
  0.495692, 6.73796 to \
  0.495692, 7.59078 front fs empty border lc rgb '#6165' lw 0.200001
set object 373 polygon from \
  0.562581, 7.49268 to \
  0.713458, 7.49268 to \
  0.713458, 6.63986 to \
  0.562581, 6.63986 to \
  0.562581, 7.49268 front fs empty border lc rgb '#6165' lw 0.200001
set object 374 polygon from \
  0.628489, 7.39458 to \
  0.787894, 7.39458 to \
  0.787894, 6.54176 to \
  0.628489, 6.54176 to \
  0.628489, 7.39458 front fs empty border lc rgb '#6165' lw 0.200001
set object 375 polygon from \
  0.693416, 7.29648 to \
  0.861349, 7.29648 to \
  0.861349, 6.44366 to \
  0.693416, 6.44366 to \
  0.693416, 7.29648 front fs empty border lc rgb '#6165' lw 0.200001
set object 376 polygon from \
  0.757362, 7.19838 to \
  0.933823, 7.19838 to \
  0.933823, 6.34556 to \
  0.757362, 6.34556 to \
  0.757362, 7.19838 front fs empty border lc rgb '#6165' lw 0.200001
set object 377 polygon from \
  0.820328, 7.10028 to \
  1.00532, 7.10028 to \
  1.00532, 6.24746 to \
  0.820328, 6.24746 to \
  0.820328, 7.10028 front fs empty border lc rgb '#6165' lw 0.200001
set object 378 polygon from \
  0.882312, 7.00218 to \
  1.07583, 7.00218 to \
  1.07583, 6.14936 to \
  0.882312, 6.14936 to \
  0.882312, 7.00218 front fs empty border lc rgb '#6165' lw 0.200001
set object 379 polygon from \
  0.943315, 6.90408 to \
  1.14536, 6.90408 to \
  1.14536, 6.05126 to \
  0.943315, 6.05126 to \
  0.943315, 6.90408 front fs empty border lc rgb '#6165' lw 0.200001
set object 380 polygon from \
  1.00334, 6.80598 to \
  1.21391, 6.80598 to \
  1.21391, 5.95316 to \
  1.00334, 5.95316 to \
  1.00334, 6.80598 front fs empty border lc rgb '#6165' lw 0.200001
set object 381 polygon from \
  1.06238, 6.70788 to \
  1.28148, 6.70788 to \
  1.28148, 5.85506 to \
  1.06238, 5.85506 to \
  1.06238, 6.70788 front fs empty border lc rgb '#6165' lw 0.200001
set object 382 polygon from \
  1.12044, 6.60978 to \
  1.34807, 6.60978 to \
  1.34807, 5.75696 to \
  1.12044, 5.75696 to \
  1.12044, 6.60978 front fs empty border lc rgb '#6165' lw 0.200001
set object 383 polygon from \
  1.17752, 6.51168 to \
  1.41368, 6.51168 to \
  1.41368, 5.65886 to \
  1.17752, 5.65886 to \
  1.17752, 6.51168 front fs empty border lc rgb '#6165' lw 0.200001
set object 384 polygon from \
  1.23362, 6.41358 to \
  1.47831, 6.41358 to \
  1.47831, 5.56076 to \
  1.23362, 5.56076 to \
  1.23362, 6.41358 front fs empty border lc rgb '#6165' lw 0.200001
set object 385 polygon from \
  1.28874, 6.31548 to \
  1.54195, 6.31548 to \
  1.54195, 5.46266 to \
  1.28874, 5.46266 to \
  1.28874, 6.31548 front fs empty border lc rgb '#6165' lw 0.200001
set object 386 polygon from \
  1.34287, 6.21738 to \
  1.60461, 6.21738 to \
  1.60461, 5.36456 to \
  1.34287, 5.36456 to \
  1.34287, 6.21738 front fs empty border lc rgb '#6165' lw 0.200001
set object 387 polygon from \
  1.39603, 6.11928 to \
  1.6663, 6.11928 to \
  1.6663, 5.26646 to \
  1.39603, 5.26646 to \
  1.39603, 6.11928 front fs empty border lc rgb '#6165' lw 0.200001
set object 388 polygon from \
  1.4482, 6.02118 to \
  1.727, 6.02118 to \
  1.727, 5.16836 to \
  1.4482, 5.16836 to \
  1.4482, 6.02118 front fs empty border lc rgb '#6165' lw 0.200001
set object 389 polygon from \
  1.4994, 5.92308 to \
  1.78672, 5.92308 to \
  1.78672, 5.07026 to \
  1.4994, 5.07026 to \
  1.4994, 5.92308 front fs empty border lc rgb '#6165' lw 0.200001
set object 390 polygon from \
  1.54961, 5.82498 to \
  1.84546, 5.82498 to \
  1.84546, 4.97216 to \
  1.54961, 4.97216 to \
  1.54961, 5.82498 front fs empty border lc rgb '#6165' lw 0.200001
set object 391 polygon from \
  1.59884, 5.72688 to \
  1.90322, 5.72688 to \
  1.90322, 4.87406 to \
  1.59884, 4.87406 to \
  1.59884, 5.72688 front fs empty border lc rgb '#6165' lw 0.200001
set object 392 polygon from \
  1.64709, 5.62878 to \
  1.96, 5.62878 to \
  1.96, 4.77596 to \
  1.64709, 4.77596 to \
  1.64709, 5.62878 front fs empty border lc rgb '#6165' lw 0.200001
set object 393 polygon from \
  1.69436, 5.53068 to \
  2.0158, 5.53068 to \
  2.0158, 4.67786 to \
  1.69436, 4.67786 to \
  1.69436, 5.53068 front fs empty border lc rgb '#6165' lw 0.200001
set object 394 polygon from \
  1.74065, 5.43258 to \
  2.07061, 5.43258 to \
  2.07061, 4.57976 to \
  1.74065, 4.57976 to \
  1.74065, 5.43258 front fs empty border lc rgb '#6165' lw 0.200001
set object 395 polygon from \
  1.78595, 5.33448 to \
  2.12445, 5.33448 to \
  2.12445, 4.48166 to \
  1.78595, 4.48166 to \
  1.78595, 5.33448 front fs empty border lc rgb '#6165' lw 0.200001
set object 396 polygon from \
  1.83028, 5.23638 to \
  2.1773, 5.23638 to \
  2.1773, 4.38356 to \
  1.83028, 4.38356 to \
  1.83028, 5.23638 front fs empty border lc rgb '#6165' lw 0.200001
set object 397 polygon from \
  1.87362, 5.13828 to \
  2.22918, 5.13828 to \
  2.22918, 4.28546 to \
  1.87362, 4.28546 to \
  1.87362, 5.13828 front fs empty border lc rgb '#6165' lw 0.200001
set object 398 polygon from \
  1.91599, 5.04018 to \
  2.28007, 5.04018 to \
  2.28007, 4.18736 to \
  1.91599, 4.18736 to \
  1.91599, 5.04018 front fs empty border lc rgb '#6165' lw 0.200001
set object 399 polygon from \
  1.95737, 4.94208 to \
  2.32998, 4.94208 to \
  2.32998, 4.08926 to \
  1.95737, 4.08926 to \
  1.95737, 4.94208 front fs empty border lc rgb '#6165' lw 0.200001
set object 400 polygon from \
  1.99777, 4.84398 to \
  2.37891, 4.84398 to \
  2.37891, 3.99116 to \
  1.99777, 3.99116 to \
  1.99777, 4.84398 front fs empty border lc rgb '#6165' lw 0.200001
set object 401 polygon from \
  2.03719, 4.74588 to \
  2.42686, 4.74588 to \
  2.42686, 3.89306 to \
  2.03719, 3.89306 to \
  2.03719, 4.74588 front fs empty border lc rgb '#6165' lw 0.200001
set object 402 polygon from \
  2.07563, 4.64778 to \
  2.47383, 4.64778 to \
  2.47383, 3.79496 to \
  2.07563, 3.79496 to \
  2.07563, 4.64778 front fs empty border lc rgb '#6165' lw 0.200001
set object 403 polygon from \
  2.11309, 4.54968 to \
  2.51981, 4.54968 to \
  2.51981, 3.69686 to \
  2.11309, 3.69686 to \
  2.11309, 4.54968 front fs empty border lc rgb '#6165' lw 0.200001
set object 404 polygon from \
  2.14957, 4.45158 to \
  2.56482, 4.45158 to \
  2.56482, 3.59876 to \
  2.14957, 3.59876 to \
  2.14957, 4.45158 front fs empty border lc rgb '#6165' lw 0.200001
set object 405 polygon from \
  2.18507, 4.35348 to \
  2.60885, 4.35348 to \
  2.60885, 3.50066 to \
  2.18507, 3.50066 to \
  2.18507, 4.35348 front fs empty border lc rgb '#6165' lw 0.200001
set object 406 polygon from \
  2.21958, 4.25538 to \
  2.65189, 4.25538 to \
  2.65189, 3.40256 to \
  2.21958, 3.40256 to \
  2.21958, 4.25538 front fs empty border lc rgb '#6165' lw 0.200001
set object 407 polygon from \
  2.25312, 4.15728 to \
  2.69395, 4.15728 to \
  2.69395, 3.30446 to \
  2.25312, 3.30446 to \
  2.25312, 4.15728 front fs empty border lc rgb '#6165' lw 0.200001
set object 408 polygon from \
  2.28567, 4.05918 to \
  2.73503, 4.05918 to \
  2.73503, 3.20636 to \
  2.28567, 3.20636 to \
  2.28567, 4.05918 front fs empty border lc rgb '#6165' lw 0.200001
set object 409 polygon from \
  2.31725, 3.96108 to \
  2.77514, 3.96108 to \
  2.77514, 3.10826 to \
  2.31725, 3.10826 to \
  2.31725, 3.96108 front fs empty border lc rgb '#6165' lw 0.200001
set object 410 polygon from \
  2.34784, 3.86298 to \
  2.81426, 3.86298 to \
  2.81426, 3.01016 to \
  2.34784, 3.01016 to \
  2.34784, 3.86298 front fs empty border lc rgb '#6165' lw 0.200001
set object 411 polygon from \
  2.37745, 3.76488 to \
  2.8524, 3.76488 to \
  2.8524, 2.91206 to \
  2.37745, 2.91206 to \
  2.37745, 3.76488 front fs empty border lc rgb '#6165' lw 0.200001
set object 412 polygon from \
  2.40608, 3.66678 to \
  2.88955, 3.66678 to \
  2.88955, 2.81396 to \
  2.40608, 2.81396 to \
  2.40608, 3.66678 front fs empty border lc rgb '#6165' lw 0.200001
set object 413 polygon from \
  2.43373, 3.56868 to \
  2.92573, 3.56868 to \
  2.92573, 2.71586 to \
  2.43373, 2.71586 to \
  2.43373, 3.56868 front fs empty border lc rgb '#6165' lw 0.200001
set object 414 polygon from \
  2.4604, 3.47058 to \
  2.96093, 3.47058 to \
  2.96093, 2.61776 to \
  2.4604, 2.61776 to \
  2.4604, 3.47058 front fs empty border lc rgb '#6165' lw 0.200001
set object 415 polygon from \
  2.48608, 3.37248 to \
  2.99514, 3.37248 to \
  2.99514, 2.51966 to \
  2.48608, 2.51966 to \
  2.48608, 3.37248 front fs empty border lc rgb '#6165' lw 0.200001
set object 416 polygon from \
  2.51079, 3.27438 to \
  3.02838, 3.27438 to \
  3.02838, 2.42156 to \
  2.51079, 2.42156 to \
  2.51079, 3.27438 front fs empty border lc rgb '#6165' lw 0.200001
set object 417 polygon from \
  2.53452, 3.17628 to \
  3.06063, 3.17628 to \
  3.06063, 2.32346 to \
  2.53452, 2.32346 to \
  2.53452, 3.17628 front fs empty border lc rgb '#6165' lw 0.200001
set object 418 polygon from \
  2.55726, 3.07818 to \
  3.0919, 3.07818 to \
  3.0919, 2.22536 to \
  2.55726, 2.22536 to \
  2.55726, 3.07818 front fs empty border lc rgb '#6165' lw 0.200001
set object 419 polygon from \
  2.57902, 2.98008 to \
  3.12219, 2.98008 to \
  3.12219, 2.12726 to \
  2.57902, 2.12726 to \
  2.57902, 2.98008 front fs empty border lc rgb '#6165' lw 0.200001
set object 420 polygon from \
  2.5998, 2.88198 to \
  3.1515, 2.88198 to \
  3.1515, 2.02916 to \
  2.5998, 2.02916 to \
  2.5998, 2.88198 front fs empty border lc rgb '#6165' lw 0.200001
set object 421 polygon from \
  2.61961, 2.78388 to \
  3.17983, 2.78388 to \
  3.17983, 1.93106 to \
  2.61961, 1.93106 to \
  2.61961, 2.78388 front fs empty border lc rgb '#6165' lw 0.200001
set object 422 polygon from \
  2.63843, 2.68578 to \
  3.20718, 2.68578 to \
  3.20718, 1.83296 to \
  2.63843, 1.83296 to \
  2.63843, 2.68578 front fs empty border lc rgb '#6165' lw 0.200001
set object 423 polygon from \
  2.65627, 2.58768 to \
  3.23355, 2.58768 to \
  3.23355, 1.73486 to \
  2.65627, 1.73486 to \
  2.65627, 2.58768 front fs empty border lc rgb '#6165' lw 0.200001
set object 424 polygon from \
  2.67312, 2.48958 to \
  3.25893, 2.48958 to \
  3.25893, 1.63676 to \
  2.67312, 1.63676 to \
  2.67312, 2.48958 front fs empty border lc rgb '#6165' lw 0.200001
set object 425 polygon from \
  2.689, 2.39148 to \
  3.28334, 2.39148 to \
  3.28334, 1.53866 to \
  2.689, 1.53866 to \
  2.689, 2.39148 front fs empty border lc rgb '#6165' lw 0.200001
set object 426 polygon from \
  2.7039, 2.29338 to \
  3.30676, 2.29338 to \
  3.30676, 1.44056 to \
  2.7039, 1.44056 to \
  2.7039, 2.29338 front fs empty border lc rgb '#6165' lw 0.200001
set object 427 polygon from \
  2.71781, 2.19528 to \
  3.32921, 2.19528 to \
  3.32921, 1.34246 to \
  2.71781, 1.34246 to \
  2.71781, 2.19528 front fs empty border lc rgb '#6165' lw 0.200001
set object 428 polygon from \
  2.73075, 2.09718 to \
  3.35067, 2.09718 to \
  3.35067, 1.24436 to \
  2.73075, 1.24436 to \
  2.73075, 2.09718 front fs empty border lc rgb '#6165' lw 0.200001
set object 429 polygon from \
  2.7427, 1.99908 to \
  3.37115, 1.99908 to \
  3.37115, 1.14626 to \
  2.7427, 1.14626 to \
  2.7427, 1.99908 front fs empty border lc rgb '#6165' lw 0.200001
set object 430 polygon from \
  2.75367, 1.90098 to \
  3.39065, 1.90098 to \
  3.39065, 1.04816 to \
  2.75367, 1.04816 to \
  2.75367, 1.90098 front fs empty border lc rgb '#6165' lw 0.200001
set object 431 polygon from \
  2.76366, 1.80288 to \
  3.40917, 1.80288 to \
  3.40917, 0.95006 to \
  2.76366, 0.95006 to \
  2.76366, 1.80288 front fs empty border lc rgb '#6165' lw 0.200001
set object 432 polygon from \
  2.77267, 1.70478 to \
  3.42671, 1.70478 to \
  3.42671, 0.85196 to \
  2.77267, 0.85196 to \
  2.77267, 1.70478 front fs empty border lc rgb '#6165' lw 0.200001
set object 433 polygon from \
  2.7807, 1.60668 to \
  3.44327, 1.60668 to \
  3.44327, 0.75386 to \
  2.7807, 0.75386 to \
  2.7807, 1.60668 front fs empty border lc rgb '#6165' lw 0.200001
set object 434 polygon from \
  2.78775, 1.50858 to \
  3.45884, 1.50858 to \
  3.45884, 0.65576 to \
  2.78775, 0.65576 to \
  2.78775, 1.50858 front fs empty border lc rgb '#6165' lw 0.200001
set object 435 polygon from \
  2.79382, 1.41048 to \
  3.47344, 1.41048 to \
  3.47344, 0.55766 to \
  2.79382, 0.55766 to \
  2.79382, 1.41048 front fs empty border lc rgb '#6165' lw 0.200001
set object 436 polygon from \
  2.7989, 1.31238 to \
  3.48705, 1.31238 to \
  3.48705, 0.45956 to \
  2.7989, 0.45956 to \
  2.7989, 1.31238 front fs empty border lc rgb '#6165' lw 0.200001
set object 437 polygon from \
  2.80301, 1.21428 to \
  3.49968, 1.21428 to \
  3.49968, 0.36146 to \
  2.80301, 0.36146 to \
  2.80301, 1.21428 front fs empty border lc rgb '#6165' lw 0.200001
set object 438 polygon from \
  2.80613, 1.11618 to \
  3.51134, 1.11618 to \
  3.51134, 0.26336 to \
  2.80613, 0.26336 to \
  2.80613, 1.11618 front fs empty border lc rgb '#6165' lw 0.200001
set object 439 polygon from \
  2.80827, 1.01808 to \
  3.52201, 1.01808 to \
  3.52201, 0.16526 to \
  2.80827, 0.16526 to \
  2.80827, 1.01808 front fs empty border lc rgb '#6165' lw 0.200001
set object 440 polygon from \
  2.80944, 0.919973 to \
  3.5317, 0.919973 to \
  3.5317, 0.0671591 to \
  2.80944, 0.0671591 to \
  2.80944, 0.919973 front fs empty border lc rgb '#6165' lw 0.200001
set object 441 polygon from \
  2.80962, 0.821873 to \
  3.54041, 0.821873 to \
  3.54041, -0.0309409 to \
  2.80962, -0.0309409 to \
  2.80962, 0.821873 front fs empty border lc rgb '#6165' lw 0.200001
set object 442 polygon from \
  2.80882, 0.723773 to \
  3.54814, 0.723773 to \
  3.54814, -0.12904 to \
  2.80882, -0.12904 to \
  2.80882, 0.723773 front fs empty border lc rgb '#6165' lw 0.200001
set object 443 polygon from \
  2.80704, 0.625673 to \
  3.55488, 0.625673 to \
  3.55488, -0.22714 to \
  2.80704, -0.22714 to \
  2.80704, 0.625673 front fs empty border lc rgb '#6165' lw 0.200001
set object 444 polygon from \
  2.80428, 0.527573 to \
  3.56065, 0.527573 to \
  3.56065, -0.32524 to \
  2.80428, -0.32524 to \
  2.80428, 0.527573 front fs empty border lc rgb '#6165' lw 0.200001
set object 445 polygon from \
  2.80053, 0.429473 to \
  3.56543, 0.429473 to \
  3.56543, -0.42334 to \
  2.80053, -0.42334 to \
  2.80053, 0.429473 front fs empty border lc rgb '#6165' lw 0.200001
set object 446 polygon from \
  2.79581, 0.331373 to \
  3.56924, 0.331373 to \
  3.56924, -0.52144 to \
  2.79581, -0.52144 to \
  2.79581, 0.331373 front fs empty border lc rgb '#6165' lw 0.200001
set object 447 polygon from \
  2.7901, 0.233273 to \
  3.57206, 0.233273 to \
  3.57206, -0.61954 to \
  2.7901, -0.61954 to \
  2.7901, 0.233273 front fs empty border lc rgb '#6165' lw 0.200001
set object 448 polygon from \
  2.78342, 0.135173 to \
  3.5739, 0.135173 to \
  3.5739, -0.71764 to \
  2.78342, -0.71764 to \
  2.78342, 0.135173 front fs empty border lc rgb '#6165' lw 0.200001
set object 449 polygon from \
  2.77575, 0.0370725 to \
  3.57477, 0.0370725 to \
  3.57477, -0.81574 to \
  2.77575, -0.81574 to \
  2.77575, 0.0370725 front fs empty border lc rgb '#6165' lw 0.200001
set object 450 polygon from \
  2.7671, -0.0610275 to \
  3.57465, -0.0610275 to \
  3.57465, -0.91384 to \
  2.7671, -0.91384 to \
  2.7671, -0.0610275 front fs empty border lc rgb '#6165' lw 0.200001
set object 451 polygon from \
  2.75747, -0.159127 to \
  3.57354, -0.159127 to \
  3.57354, -1.01194 to \
  2.75747, -1.01194 to \
  2.75747, -0.159127 front fs empty border lc rgb '#6165' lw 0.200001
set object 452 polygon from \
  2.74686, -0.257227 to \
  3.57146, -0.257227 to \
  3.57146, -1.11004 to \
  2.74686, -1.11004 to \
  2.74686, -0.257227 front fs empty border lc rgb '#6165' lw 0.200001
set object 453 polygon from \
  2.73527, -0.355327 to \
  3.5684, -0.355327 to \
  3.5684, -1.20814 to \
  2.73527, -1.20814 to \
  2.73527, -0.355327 front fs empty border lc rgb '#6165' lw 0.200001
set object 454 polygon from \
  2.7227, -0.453427 to \
  3.56436, -0.453427 to \
  3.56436, -1.30624 to \
  2.7227, -1.30624 to \
  2.7227, -0.453427 front fs empty border lc rgb '#6165' lw 0.200001
set object 455 polygon from \
  2.70915, -0.551527 to \
  3.55933, -0.551527 to \
  3.55933, -1.40434 to \
  2.70915, -1.40434 to \
  2.70915, -0.551527 front fs empty border lc rgb '#6165' lw 0.200001
set object 456 polygon from \
  2.69461, -0.649627 to \
  3.55333, -0.649627 to \
  3.55333, -1.50244 to \
  2.69461, -1.50244 to \
  2.69461, -0.649627 front fs empty border lc rgb '#6165' lw 0.200001
set object 457 polygon from \
  2.6791, -0.747727 to \
  3.54634, -0.747727 to \
  3.54634, -1.60054 to \
  2.6791, -1.60054 to \
  2.6791, -0.747727 front fs empty border lc rgb '#6165' lw 0.200001
set object 458 polygon from \
  2.6626, -0.845827 to \
  3.53837, -0.845827 to \
  3.53837, -1.69864 to \
  2.6626, -1.69864 to \
  2.6626, -0.845827 front fs empty border lc rgb '#6165' lw 0.200001
set object 459 polygon from \
  2.64513, -0.943927 to \
  3.52942, -0.943927 to \
  3.52942, -1.79674 to \
  2.64513, -1.79674 to \
  2.64513, -0.943927 front fs empty border lc rgb '#6165' lw 0.200001
set object 460 polygon from \
  2.62667, -1.04202 to \
  3.51949, -1.04202 to \
  3.51949, -1.89484 to \
  2.62667, -1.89484 to \
  2.62667, -1.04202 front fs empty border lc rgb '#6165' lw 0.200001
set object 461 polygon from \
  2.60723, -1.14012 to \
  3.50858, -1.14012 to \
  3.50858, -1.99294 to \
  2.60723, -1.99294 to \
  2.60723, -1.14012 front fs empty border lc rgb '#6165' lw 0.200001
set object 462 polygon from \
  2.58681, -1.23822 to \
  3.49669, -1.23822 to \
  3.49669, -2.09104 to \
  2.58681, -2.09104 to \
  2.58681, -1.23822 front fs empty border lc rgb '#6165' lw 0.200001
set object 463 polygon from \
  2.56541, -1.33632 to \
  3.48382, -1.33632 to \
  3.48382, -2.18914 to \
  2.56541, -2.18914 to \
  2.56541, -1.33632 front fs empty border lc rgb '#6165' lw 0.200001
set object 464 polygon from \
  2.54303, -1.43442 to \
  3.46996, -1.43442 to \
  3.46996, -2.28724 to \
  2.54303, -2.28724 to \
  2.54303, -1.43442 front fs empty border lc rgb '#6165' lw 0.200001
set object 465 polygon from \
  2.51966, -1.53252 to \
  3.45513, -1.53252 to \
  3.45513, -2.38534 to \
  2.51966, -2.38534 to \
  2.51966, -1.53252 front fs empty border lc rgb '#6165' lw 0.200001
set object 466 polygon from \
  2.49532, -1.63062 to \
  3.43931, -1.63062 to \
  3.43931, -2.48344 to \
  2.49532, -2.48344 to \
  2.49532, -1.63062 front fs empty border lc rgb '#6165' lw 0.200001
set object 467 polygon from \
  2.47, -1.72872 to \
  3.42252, -1.72872 to \
  3.42252, -2.58154 to \
  2.47, -2.58154 to \
  2.47, -1.72872 front fs empty border lc rgb '#6165' lw 0.200001
set object 468 polygon from \
  2.44369, -1.82682 to \
  3.40474, -1.82682 to \
  3.40474, -2.67964 to \
  2.44369, -2.67964 to \
  2.44369, -1.82682 front fs empty border lc rgb '#6165' lw 0.200001
set object 469 polygon from \
  2.4164, -1.92492 to \
  3.38598, -1.92492 to \
  3.38598, -2.77774 to \
  2.4164, -2.77774 to \
  2.4164, -1.92492 front fs empty border lc rgb '#6165' lw 0.200001
set object 470 polygon from \
  2.38813, -2.02302 to \
  3.36624, -2.02302 to \
  3.36624, -2.87584 to \
  2.38813, -2.87584 to \
  2.38813, -2.02302 front fs empty border lc rgb '#6165' lw 0.200001
set object 471 polygon from \
  2.35889, -2.12112 to \
  3.34552, -2.12112 to \
  3.34552, -2.97394 to \
  2.35889, -2.97394 to \
  2.35889, -2.12112 front fs empty border lc rgb '#6165' lw 0.200001
set object 472 polygon from \
  2.32866, -2.21922 to \
  3.32382, -2.21922 to \
  3.32382, -3.07204 to \
  2.32866, -3.07204 to \
  2.32866, -2.21922 front fs empty border lc rgb '#6165' lw 0.200001
set object 473 polygon from \
  2.29744, -2.31732 to \
  3.30113, -2.31732 to \
  3.30113, -3.17014 to \
  2.29744, -3.17014 to \
  2.29744, -2.31732 front fs empty border lc rgb '#6165' lw 0.200001
set object 474 polygon from \
  2.26525, -2.41542 to \
  3.27747, -2.41542 to \
  3.27747, -3.26824 to \
  2.26525, -3.26824 to \
  2.26525, -2.41542 front fs empty border lc rgb '#6165' lw 0.200001
set object 475 polygon from \
  2.23208, -2.51352 to \
  3.25283, -2.51352 to \
  3.25283, -3.36634 to \
  2.23208, -3.36634 to \
  2.23208, -2.51352 front fs empty border lc rgb '#6165' lw 0.200001
set object 476 polygon from \
  2.19793, -2.61162 to \
  3.2272, -2.61162 to \
  3.2272, -3.46444 to \
  2.19793, -3.46444 to \
  2.19793, -2.61162 front fs empty border lc rgb '#6165' lw 0.200001
set object 477 polygon from \
  2.16279, -2.70972 to \
  3.20059, -2.70972 to \
  3.20059, -3.56254 to \
  2.16279, -3.56254 to \
  2.16279, -2.70972 front fs empty border lc rgb '#6165' lw 0.200001
set object 478 polygon from \
  2.12668, -2.80782 to \
  3.17301, -2.80782 to \
  3.17301, -3.66064 to \
  2.12668, -3.66064 to \
  2.12668, -2.80782 front fs empty border lc rgb '#6165' lw 0.200001
set object 479 polygon from \
  2.08958, -2.90592 to \
  3.14444, -2.90592 to \
  3.14444, -3.75874 to \
  2.08958, -3.75874 to \
  2.08958, -2.90592 front fs empty border lc rgb '#6165' lw 0.200001
set object 480 polygon from \
  2.0515, -3.00402 to \
  3.11489, -3.00402 to \
  3.11489, -3.85684 to \
  2.0515, -3.85684 to \
  2.0515, -3.00402 front fs empty border lc rgb '#6165' lw 0.200001
set object 481 polygon from \
  2.01244, -3.10212 to \
  3.08436, -3.10212 to \
  3.08436, -3.95494 to \
  2.01244, -3.95494 to \
  2.01244, -3.10212 front fs empty border lc rgb '#6165' lw 0.200001
set object 482 polygon from \
  1.9724, -3.20022 to \
  3.05284, -3.20022 to \
  3.05284, -4.05304 to \
  1.9724, -4.05304 to \
  1.9724, -3.20022 front fs empty border lc rgb '#6165' lw 0.200001
set object 483 polygon from \
  1.93138, -3.29832 to \
  3.02035, -3.29832 to \
  3.02035, -4.15114 to \
  1.93138, -4.15114 to \
  1.93138, -3.29832 front fs empty border lc rgb '#6165' lw 0.200001
set object 484 polygon from \
  1.88938, -3.39642 to \
  2.98688, -3.39642 to \
  2.98688, -4.24924 to \
  1.88938, -4.24924 to \
  1.88938, -3.39642 front fs empty border lc rgb '#6165' lw 0.200001
set object 485 polygon from \
  1.8464, -3.49452 to \
  2.95242, -3.49452 to \
  2.95242, -4.34734 to \
  1.8464, -4.34734 to \
  1.8464, -3.49452 front fs empty border lc rgb '#6165' lw 0.200001
set object 486 polygon from \
  1.80243, -3.59262 to \
  2.91699, -3.59262 to \
  2.91699, -4.44544 to \
  1.80243, -4.44544 to \
  1.80243, -3.59262 front fs empty border lc rgb '#6165' lw 0.200001
set object 487 polygon from \
  1.75749, -3.69072 to \
  2.88057, -3.69072 to \
  2.88057, -4.54354 to \
  1.75749, -4.54354 to \
  1.75749, -3.69072 front fs empty border lc rgb '#6165' lw 0.200001
set object 488 polygon from \
  1.71156, -3.78882 to \
  2.84317, -3.78882 to \
  2.84317, -4.64164 to \
  1.71156, -4.64164 to \
  1.71156, -3.78882 front fs empty border lc rgb '#6165' lw 0.200001
set object 489 polygon from \
  1.66465, -3.88692 to \
  2.80479, -3.88692 to \
  2.80479, -4.73974 to \
  1.66465, -4.73974 to \
  1.66465, -3.88692 front fs empty border lc rgb '#6165' lw 0.200001
set object 490 polygon from \
  1.61677, -3.98502 to \
  2.76543, -3.98502 to \
  2.76543, -4.83784 to \
  1.61677, -4.83784 to \
  1.61677, -3.98502 front fs empty border lc rgb '#6165' lw 0.200001
set object 491 polygon from \
  1.5679, -4.08312 to \
  2.72509, -4.08312 to \
  2.72509, -4.93594 to \
  1.5679, -4.93594 to \
  1.5679, -4.08312 front fs empty border lc rgb '#6165' lw 0.200001
set object 492 polygon from \
  1.51805, -4.18122 to \
  2.68377, -4.18122 to \
  2.68377, -5.03404 to \
  1.51805, -5.03404 to \
  1.51805, -4.18122 front fs empty border lc rgb '#6165' lw 0.200001
set object 493 polygon from \
  1.46722, -4.27932 to \
  2.64147, -4.27932 to \
  2.64147, -5.13214 to \
  1.46722, -5.13214 to \
  1.46722, -4.27932 front fs empty border lc rgb '#6165' lw 0.200001
set object 494 polygon from \
  1.4154, -4.37742 to \
  2.59819, -4.37742 to \
  2.59819, -5.23024 to \
  1.4154, -5.23024 to \
  1.4154, -4.37742 front fs empty border lc rgb '#6165' lw 0.200001
set object 495 polygon from \
  1.36261, -4.47552 to \
  2.55392, -4.47552 to \
  2.55392, -5.32834 to \
  1.36261, -5.32834 to \
  1.36261, -4.47552 front fs empty border lc rgb '#6165' lw 0.200001
set object 496 polygon from \
  1.30884, -4.57362 to \
  2.50867, -4.57362 to \
  2.50867, -5.42644 to \
  1.30884, -5.42644 to \
  1.30884, -4.57362 front fs empty border lc rgb '#6165' lw 0.200001
set object 497 polygon from \
  1.25408, -4.67172 to \
  2.46245, -4.67172 to \
  2.46245, -5.52454 to \
  1.25408, -5.52454 to \
  1.25408, -4.67172 front fs empty border lc rgb '#6165' lw 0.200001
set object 498 polygon from \
  1.19835, -4.76982 to \
  2.41524, -4.76982 to \
  2.41524, -5.62264 to \
  1.19835, -5.62264 to \
  1.19835, -4.76982 front fs empty border lc rgb '#6165' lw 0.200001
set object 499 polygon from \
  1.14163, -4.86792 to \
  2.36705, -4.86792 to \
  2.36705, -5.72074 to \
  1.14163, -5.72074 to \
  1.14163, -4.86792 front fs empty border lc rgb '#6165' lw 0.200001
set object 500 polygon from \
  1.08393, -4.96602 to \
  2.31788, -4.96602 to \
  2.31788, -5.81884 to \
  1.08393, -5.81884 to \
  1.08393, -4.96602 front fs empty border lc rgb '#6165' lw 0.200001
set object 501 polygon from \
  1.02525, -5.06412 to \
  2.26773, -5.06412 to \
  2.26773, -5.91694 to \
  1.02525, -5.91694 to \
  1.02525, -5.06412 front fs empty border lc rgb '#6165' lw 0.200001
set object 502 polygon from \
  0.965589, -5.16222 to \
  2.2166, -5.16222 to \
  2.2166, -6.01504 to \
  0.965589, -6.01504 to \
  0.965589, -5.16222 front fs empty border lc rgb '#6165' lw 0.200001
set object 503 polygon from \
  0.904948, -5.26032 to \
  2.16449, -5.26032 to \
  2.16449, -6.11314 to \
  0.904948, -6.11314 to \
  0.904948, -5.26032 front fs empty border lc rgb '#6165' lw 0.200001
set object 504 polygon from \
  0.843326, -5.35842 to \
  2.11139, -5.35842 to \
  2.11139, -6.21124 to \
  0.843326, -6.21124 to \
  0.843326, -5.35842 front fs empty border lc rgb '#6165' lw 0.200001
set object 505 polygon from \
  0.780723, -5.45652 to \
  2.05732, -5.45652 to \
  2.05732, -6.30934 to \
  0.780723, -6.30934 to \
  0.780723, -5.45652 front fs empty border lc rgb '#6165' lw 0.200001
set object 506 polygon from \
  0.717139, -5.55462 to \
  2.00226, -5.55462 to \
  2.00226, -6.40744 to \
  0.717139, -6.40744 to \
  0.717139, -5.55462 front fs empty border lc rgb '#6165' lw 0.200001
set object 507 polygon from \
  0.652574, -5.65272 to \
  1.94623, -5.65272 to \
  1.94623, -6.50554 to \
  0.652574, -6.50554 to \
  0.652574, -5.65272 front fs empty border lc rgb '#6165' lw 0.200001
set object 508 polygon from \
  0.587028, -5.75082 to \
  1.88921, -5.75082 to \
  1.88921, -6.60364 to \
  0.587028, -6.60364 to \
  0.587028, -5.75082 front fs empty border lc rgb '#6165' lw 0.200001
set object 509 polygon from \
  0.520501, -5.84892 to \
  1.83121, -5.84892 to \
  1.83121, -6.70174 to \
  0.520501, -6.70174 to \
  0.520501, -5.84892 front fs empty border lc rgb '#6165' lw 0.200001
set object 510 polygon from \
  0.452994, -5.94702 to \
  1.77223, -5.94702 to \
  1.77223, -6.79984 to \
  0.452994, -6.79984 to \
  0.452994, -5.94702 front fs empty border lc rgb '#6165' lw 0.200001
set object 511 polygon from \
  0.384505, -6.04512 to \
  1.71227, -6.04512 to \
  1.71227, -6.89794 to \
  0.384505, -6.89794 to \
  0.384505, -6.04512 front fs empty border lc rgb '#6165' lw 0.200001
set object 512 polygon from \
  0.315035, -6.14322 to \
  1.65133, -6.14322 to \
  1.65133, -6.99604 to \
  0.315035, -6.99604 to \
  0.315035, -6.14322 front fs empty border lc rgb '#6165' lw 0.200001
set object 513 polygon from \
  0.244584, -6.24132 to \
  1.5894, -6.24132 to \
  1.5894, -7.09414 to \
  0.244584, -7.09414 to \
  0.244584, -6.24132 front fs empty border lc rgb '#6165' lw 0.200001
set object 514 polygon from \
  0.173152, -6.33942 to \
  1.5265, -6.33942 to \
  1.5265, -7.19224 to \
  0.173152, -7.19224 to \
  0.173152, -6.33942 front fs empty border lc rgb '#6165' lw 0.200001
set object 515 polygon from \
  0.100739, -6.43752 to \
  1.46261, -6.43752 to \
  1.46261, -7.29034 to \
  0.100739, -7.29034 to \
  0.100739, -6.43752 front fs empty border lc rgb '#6165' lw 0.200001
set object 516 polygon from \
  0.0273447, -6.53562 to \
  1.39775, -6.53562 to \
  1.39775, -7.38844 to \
  0.0273447, -7.38844 to \
  0.0273447, -6.53562 front fs empty border lc rgb '#6165' lw 0.200001
set object 517 polygon from \
  0, -6.63372 to \
  1.3319, -6.63372 to \
  1.3319, -7.48654 to \
  0, -7.48654 to \
  0, -6.63372 front fs empty border lc rgb '#6165' lw 0.200001
set object 518 polygon from \
  0, -6.73182 to \
  1.26507, -6.73182 to \
  1.26507, -7.58464 to \
  0, -7.58464 to \
  0, -6.73182 front fs empty border lc rgb '#6165' lw 0.200001
set object 519 polygon from \
  0, -6.82992 to \
  1.19727, -6.82992 to \
  1.19727, -7.68274 to \
  0, -7.68274 to \
  0, -6.82992 front fs empty border lc rgb '#6165' lw 0.200001
set object 520 polygon from \
  0, -6.92802 to \
  1.12848, -6.92802 to \
  1.12848, -7.78084 to \
  0, -7.78084 to \
  0, -6.92802 front fs empty border lc rgb '#6165' lw 0.200001
set object 521 polygon from \
  0, -7.02612 to \
  1.05871, -7.02612 to \
  1.05871, -7.87894 to \
  0, -7.87894 to \
  0, -7.02612 front fs empty border lc rgb '#6165' lw 0.200001
set object 522 polygon from \
  0, -7.12422 to \
  0.987949, -7.12422 to \
  0.987949, -7.97704 to \
  0, -7.97704 to \
  0, -7.12422 front fs empty border lc rgb '#6165' lw 0.200001
set object 523 polygon from \
  0, -7.22232 to \
  0.916216, -7.22232 to \
  0.916216, -8.07514 to \
  0, -8.07514 to \
  0, -7.22232 front fs empty border lc rgb '#6165' lw 0.200001
set object 524 polygon from \
  0, -7.32042 to \
  0.843502, -7.32042 to \
  0.843502, -8.17324 to \
  0, -8.17324 to \
  0, -7.32042 front fs empty border lc rgb '#6165' lw 0.200001
set object 525 polygon from \
  0, -7.41852 to \
  0.769808, -7.41852 to \
  0.769808, -8.27134 to \
  0, -8.27134 to \
  0, -7.41852 front fs empty border lc rgb '#6165' lw 0.200001
set object 526 polygon from \
  0, -7.51662 to \
  0.695132, -7.51662 to \
  0.695132, -8.36944 to \
  0, -8.36944 to \
  0, -7.51662 front fs empty border lc rgb '#6165' lw 0.200001
set object 527 polygon from \
  0, -7.61472 to \
  0.619475, -7.61472 to \
  0.619475, -8.46754 to \
  0, -8.46754 to \
  0, -7.61472 front fs empty border lc rgb '#6165' lw 0.200001
set object 528 polygon from \
  0, -7.71282 to \
  0.542837, -7.71282 to \
  0.542837, -8.56564 to \
  0, -8.56564 to \
  0, -7.71282 front fs empty border lc rgb '#6165' lw 0.200001
set object 529 polygon from \
  0, -7.81092 to \
  0.465219, -7.81092 to \
  0.465219, -8.66374 to \
  0, -8.66374 to \
  0, -7.81092 front fs empty border lc rgb '#6165' lw 0.200001
set object 530 polygon from \
  0, -7.90902 to \
  0.386619, -7.90902 to \
  0.386619, -8.76184 to \
  0, -8.76184 to \
  0, -7.90902 front fs empty border lc rgb '#6165' lw 0.200001
set object 531 polygon from \
  0, -8.00712 to \
  0.307038, -8.00712 to \
  0.307038, -8.85994 to \
  0, -8.85994 to \
  0, -8.00712 front fs empty border lc rgb '#6165' lw 0.200001
set object 532 polygon from \
  0, -8.10522 to \
  0.226476, -8.10522 to \
  0.226476, -8.95804 to \
  0, -8.95804 to \
  0, -8.10522 front fs empty border lc rgb '#6165' lw 0.200001
set object 533 polygon from \
  0, -8.20332 to \
  0.144933, -8.20332 to \
  0.144933, -9.05614 to \
  0, -9.05614 to \
  0, -8.20332 front fs empty border lc rgb '#6165' lw 0.200001
set object 534 polygon from \
  0, -8.30142 to \
  0.0624093, -8.30142 to \
  0.0624093, -9.15424 to \
  0, -9.15424 to \
  0, -8.30142 front fs empty border lc rgb '#6165' lw 0.200001
set object 535 polygon from \
  0, 6.86581 to \
  0.0685346, 6.86581 to \
  0.0685346, 4.87708 to \
  0, 4.87708 to \
  0, 6.86581 front fs empty border lc rgb '#6165' lw 0.200001
set object 536 polygon from \
  0.0482803, 6.76771 to \
  0.136703, 6.76771 to \
  0.136703, 4.77898 to \
  0.0482803, 4.77898 to \
  0.0482803, 6.76771 front fs empty border lc rgb '#6165' lw 0.200001
set object 537 polygon from \
  0.0955795, 6.66961 to \
  0.203889, 6.66961 to \
  0.203889, 4.68088 to \
  0.0955795, 4.68088 to \
  0.0955795, 6.66961 front fs empty border lc rgb '#6165' lw 0.200001
set object 538 polygon from \
  0.141898, 6.57151 to \
  0.270095, 6.57151 to \
  0.270095, 4.58278 to \
  0.141898, 4.58278 to \
  0.141898, 6.57151 front fs empty border lc rgb '#6165' lw 0.200001
set object 539 polygon from \
  0.187235, 6.47341 to \
  0.335319, 6.47341 to \
  0.335319, 4.48468 to \
  0.187235, 4.48468 to \
  0.187235, 6.47341 front fs empty border lc rgb '#6165' lw 0.200001
set object 540 polygon from \
  0.231592, 6.37531 to \
  0.399563, 6.37531 to \
  0.399563, 4.38658 to \
  0.231592, 4.38658 to \
  0.231592, 6.37531 front fs empty border lc rgb '#6165' lw 0.200001
set object 541 polygon from \
  0.274967, 6.27721 to \
  0.462825, 6.27721 to \
  0.462825, 4.28848 to \
  0.274967, 4.28848 to \
  0.274967, 6.27721 front fs empty border lc rgb '#6165' lw 0.200001
set object 542 polygon from \
  0.317361, 6.17911 to \
  0.525107, 6.17911 to \
  0.525107, 4.19038 to \
  0.317361, 4.19038 to \
  0.317361, 6.17911 front fs empty border lc rgb '#6165' lw 0.200001
set object 543 polygon from \
  0.358774, 6.08101 to \
  0.586407, 6.08101 to \
  0.586407, 4.09228 to \
  0.358774, 4.09228 to \
  0.358774, 6.08101 front fs empty border lc rgb '#6165' lw 0.200001
set object 544 polygon from \
  0.399207, 5.98291 to \
  0.646727, 5.98291 to \
  0.646727, 3.99418 to \
  0.399207, 3.99418 to \
  0.399207, 5.98291 front fs empty border lc rgb '#6165' lw 0.200001
set object 545 polygon from \
  0.438658, 5.88481 to \
  0.706066, 5.88481 to \
  0.706066, 3.89608 to \
  0.438658, 3.89608 to \
  0.438658, 5.88481 front fs empty border lc rgb '#6165' lw 0.200001
set object 546 polygon from \
  0.477128, 5.78671 to \
  0.764423, 5.78671 to \
  0.764423, 3.79798 to \
  0.477128, 3.79798 to \
  0.477128, 5.78671 front fs empty border lc rgb '#6165' lw 0.200001
set object 547 polygon from \
  0.514617, 5.68861 to \
  0.8218, 5.68861 to \
  0.8218, 3.69988 to \
  0.514617, 3.69988 to \
  0.514617, 5.68861 front fs empty border lc rgb '#6165' lw 0.200001
set object 548 polygon from \
  0.551125, 5.59051 to \
  0.878195, 5.59051 to \
  0.878195, 3.60178 to \
  0.551125, 3.60178 to \
  0.551125, 5.59051 front fs empty border lc rgb '#6165' lw 0.200001
set object 549 polygon from \
  0.586653, 5.49241 to \
  0.93361, 5.49241 to \
  0.93361, 3.50368 to \
  0.586653, 3.50368 to \
  0.586653, 5.49241 front fs empty border lc rgb '#6165' lw 0.200001
set object 550 polygon from \
  0.621199, 5.39431 to \
  0.988043, 5.39431 to \
  0.988043, 3.40558 to \
  0.621199, 3.40558 to \
  0.621199, 5.39431 front fs empty border lc rgb '#6165' lw 0.200001
set object 551 polygon from \
  0.654764, 5.29621 to \
  1.0415, 5.29621 to \
  1.0415, 3.30748 to \
  0.654764, 3.30748 to \
  0.654764, 5.29621 front fs empty border lc rgb '#6165' lw 0.200001
set object 552 polygon from \
  0.687348, 5.19811 to \
  1.09397, 5.19811 to \
  1.09397, 3.20938 to \
  0.687348, 3.20938 to \
  0.687348, 5.19811 front fs empty border lc rgb '#6165' lw 0.200001
set object 553 polygon from \
  0.718952, 5.10001 to \
  1.14546, 5.10001 to \
  1.14546, 3.11128 to \
  0.718952, 3.11128 to \
  0.718952, 5.10001 front fs empty border lc rgb '#6165' lw 0.200001
set object 554 polygon from \
  0.749574, 5.00191 to \
  1.19597, 5.00191 to \
  1.19597, 3.01318 to \
  0.749574, 3.01318 to \
  0.749574, 5.00191 front fs empty border lc rgb '#6165' lw 0.200001
set object 555 polygon from \
  0.779215, 4.90381 to \
  1.2455, 4.90381 to \
  1.2455, 2.91508 to \
  0.779215, 2.91508 to \
  0.779215, 4.90381 front fs empty border lc rgb '#6165' lw 0.200001
set object 556 polygon from \
  0.807875, 4.80571 to \
  1.29405, 4.80571 to \
  1.29405, 2.81698 to \
  0.807875, 2.81698 to \
  0.807875, 4.80571 front fs empty border lc rgb '#6165' lw 0.200001
set object 557 polygon from \
  0.835554, 4.70761 to \
  1.34161, 4.70761 to \
  1.34161, 2.71888 to \
  0.835554, 2.71888 to \
  0.835554, 4.70761 front fs empty border lc rgb '#6165' lw 0.200001
set object 558 polygon from \
  0.862253, 4.60951 to \
  1.3882, 4.60951 to \
  1.3882, 2.62078 to \
  0.862253, 2.62078 to \
  0.862253, 4.60951 front fs empty border lc rgb '#6165' lw 0.200001
set object 559 polygon from \
  0.88797, 4.51141 to \
  1.4338, 4.51141 to \
  1.4338, 2.52268 to \
  0.88797, 2.52268 to \
  0.88797, 4.51141 front fs empty border lc rgb '#6165' lw 0.200001
set object 560 polygon from \
  0.912706, 4.41331 to \
  1.47843, 4.41331 to \
  1.47843, 2.42458 to \
  0.912706, 2.42458 to \
  0.912706, 4.41331 front fs empty border lc rgb '#6165' lw 0.200001
set object 561 polygon from \
  0.936461, 4.31521 to \
  1.52207, 4.31521 to \
  1.52207, 2.32648 to \
  0.936461, 2.32648 to \
  0.936461, 4.31521 front fs empty border lc rgb '#6165' lw 0.200001
set object 562 polygon from \
  0.959236, 4.21711 to \
  1.56473, 4.21711 to \
  1.56473, 2.22838 to \
  0.959236, 2.22838 to \
  0.959236, 4.21711 front fs empty border lc rgb '#6165' lw 0.200001
set object 563 polygon from \
  0.981029, 4.11901 to \
  1.60641, 4.11901 to \
  1.60641, 2.13028 to \
  0.981029, 2.13028 to \
  0.981029, 4.11901 front fs empty border lc rgb '#6165' lw 0.200001
set object 564 polygon from \
  1.00185, 4.02091 to \
  1.64711, 4.02091 to \
  1.64711, 2.03218 to \
  1.00185, 2.03218 to \
  1.00185, 4.02091 front fs empty border lc rgb '#6165' lw 0.200001
set object 565 polygon from \
  1.02168, 3.92281 to \
  1.68683, 3.92281 to \
  1.68683, 1.93408 to \
  1.02168, 1.93408 to \
  1.02168, 3.92281 front fs empty border lc rgb '#6165' lw 0.200001
set object 566 polygon from \
  1.04053, 3.82471 to \
  1.72557, 3.82471 to \
  1.72557, 1.83598 to \
  1.04053, 1.83598 to \
  1.04053, 3.82471 front fs empty border lc rgb '#6165' lw 0.200001
set object 567 polygon from \
  1.0584, 3.72661 to \
  1.76332, 3.72661 to \
  1.76332, 1.73788 to \
  1.0584, 1.73788 to \
  1.0584, 3.72661 front fs empty border lc rgb '#6165' lw 0.200001
set object 568 polygon from \
  1.07528, 3.62851 to \
  1.8001, 3.62851 to \
  1.8001, 1.63978 to \
  1.07528, 1.63978 to \
  1.07528, 3.62851 front fs empty border lc rgb '#6165' lw 0.200001
set object 569 polygon from \
  1.09119, 3.53041 to \
  1.8359, 3.53041 to \
  1.8359, 1.54168 to \
  1.09119, 1.54168 to \
  1.09119, 3.53041 front fs empty border lc rgb '#6165' lw 0.200001
set object 570 polygon from \
  1.10612, 3.43231 to \
  1.87071, 3.43231 to \
  1.87071, 1.44358 to \
  1.10612, 1.44358 to \
  1.10612, 3.43231 front fs empty border lc rgb '#6165' lw 0.200001
set object 571 polygon from \
  1.12006, 3.33421 to \
  1.90454, 3.33421 to \
  1.90454, 1.34548 to \
  1.12006, 1.34548 to \
  1.12006, 3.33421 front fs empty border lc rgb '#6165' lw 0.200001
set object 572 polygon from \
  1.13303, 3.23611 to \
  1.93739, 3.23611 to \
  1.93739, 1.24738 to \
  1.13303, 1.24738 to \
  1.13303, 3.23611 front fs empty border lc rgb '#6165' lw 0.200001
set object 573 polygon from \
  1.14501, 3.13801 to \
  1.96926, 3.13801 to \
  1.96926, 1.14928 to \
  1.14501, 1.14928 to \
  1.14501, 3.13801 front fs empty border lc rgb '#6165' lw 0.200001
set object 574 polygon from \
  1.15601, 3.03991 to \
  2.00015, 3.03991 to \
  2.00015, 1.05118 to \
  1.15601, 1.05118 to \
  1.15601, 3.03991 front fs empty border lc rgb '#6165' lw 0.200001
set object 575 polygon from \
  1.16603, 2.94181 to \
  2.03006, 2.94181 to \
  2.03006, 0.953073 to \
  1.16603, 0.953073 to \
  1.16603, 2.94181 front fs empty border lc rgb '#6165' lw 0.200001
set object 576 polygon from \
  1.17507, 2.84371 to \
  2.05899, 2.84371 to \
  2.05899, 0.854973 to \
  1.17507, 0.854973 to \
  1.17507, 2.84371 front fs empty border lc rgb '#6165' lw 0.200001
set object 577 polygon from \
  1.18313, 2.74561 to \
  2.08694, 2.74561 to \
  2.08694, 0.756873 to \
  1.18313, 0.756873 to \
  1.18313, 2.74561 front fs empty border lc rgb '#6165' lw 0.200001
set object 578 polygon from \
  1.19021, 2.64751 to \
  2.1139, 2.64751 to \
  2.1139, 0.658773 to \
  1.19021, 0.658773 to \
  1.19021, 2.64751 front fs empty border lc rgb '#6165' lw 0.200001
set object 579 polygon from \
  1.19631, 2.54941 to \
  2.13989, 2.54941 to \
  2.13989, 0.560673 to \
  1.19631, 0.560673 to \
  1.19631, 2.54941 front fs empty border lc rgb '#6165' lw 0.200001
set object 580 polygon from \
  1.20143, 2.45131 to \
  2.16489, 2.45131 to \
  2.16489, 0.462573 to \
  1.20143, 0.462573 to \
  1.20143, 2.45131 front fs empty border lc rgb '#6165' lw 0.200001
set object 581 polygon from \
  1.20556, 2.35321 to \
  2.18891, 2.35321 to \
  2.18891, 0.364473 to \
  1.20556, 0.364473 to \
  1.20556, 2.35321 front fs empty border lc rgb '#6165' lw 0.200001
set object 582 polygon from \
  1.20871, 2.25511 to \
  2.21195, 2.25511 to \
  2.21195, 0.266373 to \
  1.20871, 0.266373 to \
  1.20871, 2.25511 front fs empty border lc rgb '#6165' lw 0.200001
set object 583 polygon from \
  1.21089, 2.15701 to \
  2.23401, 2.15701 to \
  2.23401, 0.168273 to \
  1.21089, 0.168273 to \
  1.21089, 2.15701 front fs empty border lc rgb '#6165' lw 0.200001
set object 584 polygon from \
  1.21208, 2.05891 to \
  2.25509, 2.05891 to \
  2.25509, 0.0701727 to \
  1.21208, 0.0701727 to \
  1.21208, 2.05891 front fs empty border lc rgb '#6165' lw 0.200001
set object 585 polygon from \
  1.21229, 1.96081 to \
  2.27519, 1.96081 to \
  2.27519, -0.0279273 to \
  1.21229, -0.0279273 to \
  1.21229, 1.96081 front fs empty border lc rgb '#6165' lw 0.200001
set object 586 polygon from \
  1.21152, 1.86271 to \
  2.29431, 1.86271 to \
  2.29431, -0.126027 to \
  1.21152, -0.126027 to \
  1.21152, 1.86271 front fs empty border lc rgb '#6165' lw 0.200001
set object 587 polygon from \
  1.20977, 1.76461 to \
  2.31245, 1.76461 to \
  2.31245, -0.224127 to \
  1.20977, -0.224127 to \
  1.20977, 1.76461 front fs empty border lc rgb '#6165' lw 0.200001
set object 588 polygon from \
  1.20704, 1.66651 to \
  2.3296, 1.66651 to \
  2.3296, -0.322227 to \
  1.20704, -0.322227 to \
  1.20704, 1.66651 front fs empty border lc rgb '#6165' lw 0.200001
set object 589 polygon from \
  1.20333, 1.56841 to \
  2.34578, 1.56841 to \
  2.34578, -0.420327 to \
  1.20333, -0.420327 to \
  1.20333, 1.56841 front fs empty border lc rgb '#6165' lw 0.200001
set object 590 polygon from \
  1.19863, 1.47031 to \
  2.36097, 1.47031 to \
  2.36097, -0.518427 to \
  1.19863, -0.518427 to \
  1.19863, 1.47031 front fs empty border lc rgb '#6165' lw 0.200001
set object 591 polygon from \
  1.19296, 1.37221 to \
  2.37518, 1.37221 to \
  2.37518, -0.616527 to \
  1.19296, -0.616527 to \
  1.19296, 1.37221 front fs empty border lc rgb '#6165' lw 0.200001
set object 592 polygon from \
  1.1863, 1.27411 to \
  2.38841, 1.27411 to \
  2.38841, -0.714627 to \
  1.1863, -0.714627 to \
  1.1863, 1.27411 front fs empty border lc rgb '#6165' lw 0.200001
set object 593 polygon from \
  1.17867, 1.17601 to \
  2.40066, 1.17601 to \
  2.40066, -0.812727 to \
  1.17867, -0.812727 to \
  1.17867, 1.17601 front fs empty border lc rgb '#6165' lw 0.200001
set object 594 polygon from \
  1.17005, 1.07791 to \
  2.41193, 1.07791 to \
  2.41193, -0.910827 to \
  1.17005, -0.910827 to \
  1.17005, 1.07791 front fs empty border lc rgb '#6165' lw 0.200001
set object 595 polygon from \
  1.16045, 0.979805 to \
  2.42222, 0.979805 to \
  2.42222, -1.00892 to \
  1.16045, -1.00892 to \
  1.16045, 0.979805 front fs empty border lc rgb '#6165' lw 0.200001
set object 596 polygon from \
  1.14987, 0.881705 to \
  2.43153, 0.881705 to \
  2.43153, -1.10702 to \
  1.14987, -1.10702 to \
  1.14987, 0.881705 front fs empty border lc rgb '#6165' lw 0.200001
set object 597 polygon from \
  1.13831, 0.783605 to \
  2.43986, 0.783605 to \
  2.43986, -1.20512 to \
  1.13831, -1.20512 to \
  1.13831, 0.783605 front fs empty border lc rgb '#6165' lw 0.200001
set object 598 polygon from \
  1.12577, 0.685505 to \
  2.4472, 0.685505 to \
  2.4472, -1.30322 to \
  1.12577, -1.30322 to \
  1.12577, 0.685505 front fs empty border lc rgb '#6165' lw 0.200001
set object 599 polygon from \
  1.11224, 0.587405 to \
  2.45357, 0.587405 to \
  2.45357, -1.40132 to \
  1.11224, -1.40132 to \
  1.11224, 0.587405 front fs empty border lc rgb '#6165' lw 0.200001
set object 600 polygon from \
  1.09774, 0.489305 to \
  2.45895, 0.489305 to \
  2.45895, -1.49942 to \
  1.09774, -1.49942 to \
  1.09774, 0.489305 front fs empty border lc rgb '#6165' lw 0.200001
set object 601 polygon from \
  1.08225, 0.391205 to \
  2.46335, 0.391205 to \
  2.46335, -1.59752 to \
  1.08225, -1.59752 to \
  1.08225, 0.391205 front fs empty border lc rgb '#6165' lw 0.200001
set object 602 polygon from \
  1.06579, 0.293105 to \
  2.46677, 0.293105 to \
  2.46677, -1.69562 to \
  1.06579, -1.69562 to \
  1.06579, 0.293105 front fs empty border lc rgb '#6165' lw 0.200001
set object 603 polygon from \
  1.04834, 0.195005 to \
  2.46921, 0.195005 to \
  2.46921, -1.79372 to \
  1.04834, -1.79372 to \
  1.04834, 0.195005 front fs empty border lc rgb '#6165' lw 0.200001
set object 604 polygon from \
  1.02991, 0.0969044 to \
  2.47067, 0.0969044 to \
  2.47067, -1.89182 to \
  1.02991, -1.89182 to \
  1.02991, 0.0969044 front fs empty border lc rgb '#6165' lw 0.200001
set object 605 polygon from \
  1.01051, -0.00119568 to \
  2.47115, -0.00119568 to \
  2.47115, -1.98992 to \
  1.01051, -1.98992 to \
  1.01051, -0.00119568 front fs empty border lc rgb '#6165' lw 0.200001
set object 606 polygon from \
  0.990112, -0.0992956 to \
  2.47065, -0.0992956 to \
  2.47065, -2.08802 to \
  0.990112, -2.08802 to \
  0.990112, -0.0992956 front fs empty border lc rgb '#6165' lw 0.200001
set object 607 polygon from \
  0.968741, -0.197395 to \
  2.46917, -0.197395 to \
  2.46917, -2.18612 to \
  0.968741, -2.18612 to \
  0.968741, -0.197395 front fs empty border lc rgb '#6165' lw 0.200001
set object 608 polygon from \
  0.946389, -0.295495 to \
  2.4667, -0.295495 to \
  2.4667, -2.28422 to \
  0.946389, -2.28422 to \
  0.946389, -0.295495 front fs empty border lc rgb '#6165' lw 0.200001
set object 609 polygon from \
  0.923056, -0.393595 to \
  2.46326, -0.393595 to \
  2.46326, -2.38232 to \
  0.923056, -2.38232 to \
  0.923056, -0.393595 front fs empty border lc rgb '#6165' lw 0.200001
set object 610 polygon from \
  0.898742, -0.491695 to \
  2.45883, -0.491695 to \
  2.45883, -2.48042 to \
  0.898742, -2.48042 to \
  0.898742, -0.491695 front fs empty border lc rgb '#6165' lw 0.200001
set object 611 polygon from \
  0.873448, -0.589795 to \
  2.45342, -0.589795 to \
  2.45342, -2.57852 to \
  0.873448, -2.57852 to \
  0.873448, -0.589795 front fs empty border lc rgb '#6165' lw 0.200001
set object 612 polygon from \
  0.847172, -0.687895 to \
  2.44703, -0.687895 to \
  2.44703, -2.67662 to \
  0.847172, -2.67662 to \
  0.847172, -0.687895 front fs empty border lc rgb '#6165' lw 0.200001
set object 613 polygon from \
  0.819915, -0.785995 to \
  2.43966, -0.785995 to \
  2.43966, -2.77472 to \
  0.819915, -2.77472 to \
  0.819915, -0.785995 front fs empty border lc rgb '#6165' lw 0.200001
set object 614 polygon from \
  0.791677, -0.884095 to \
  2.43131, -0.884095 to \
  2.43131, -2.87282 to \
  0.791677, -2.87282 to \
  0.791677, -0.884095 front fs empty border lc rgb '#6165' lw 0.200001
set object 615 polygon from \
  0.762459, -0.982195 to \
  2.42198, -0.982195 to \
  2.42198, -2.97092 to \
  0.762459, -2.97092 to \
  0.762459, -0.982195 front fs empty border lc rgb '#6165' lw 0.200001
set object 616 polygon from \
  0.732259, -1.08029 to \
  2.41167, -1.08029 to \
  2.41167, -3.06902 to \
  0.732259, -3.06902 to \
  0.732259, -1.08029 front fs empty border lc rgb '#6165' lw 0.200001
set object 617 polygon from \
  0.701078, -1.17839 to \
  2.40038, -1.17839 to \
  2.40038, -3.16712 to \
  0.701078, -3.16712 to \
  0.701078, -1.17839 front fs empty border lc rgb '#6165' lw 0.200001
set object 618 polygon from \
  0.668916, -1.27649 to \
  2.3881, -1.27649 to \
  2.3881, -3.26522 to \
  0.668916, -3.26522 to \
  0.668916, -1.27649 front fs empty border lc rgb '#6165' lw 0.200001
set object 619 polygon from \
  0.635774, -1.37459 to \
  2.37485, -1.37459 to \
  2.37485, -3.36332 to \
  0.635774, -3.36332 to \
  0.635774, -1.37459 front fs empty border lc rgb '#6165' lw 0.200001
set object 620 polygon from \
  0.60165, -1.47269 to \
  2.36061, -1.47269 to \
  2.36061, -3.46142 to \
  0.60165, -3.46142 to \
  0.60165, -1.47269 front fs empty border lc rgb '#6165' lw 0.200001
set object 621 polygon from \
  0.566545, -1.57079 to \
  2.34539, -1.57079 to \
  2.34539, -3.55952 to \
  0.566545, -3.55952 to \
  0.566545, -1.57079 front fs empty border lc rgb '#6165' lw 0.200001
set object 622 polygon from \
  0.530459, -1.66889 to \
  2.32919, -1.66889 to \
  2.32919, -3.65762 to \
  0.530459, -3.65762 to \
  0.530459, -1.66889 front fs empty border lc rgb '#6165' lw 0.200001
set object 623 polygon from \
  0.493392, -1.76699 to \
  2.31202, -1.76699 to \
  2.31202, -3.75572 to \
  0.493392, -3.75572 to \
  0.493392, -1.76699 front fs empty border lc rgb '#6165' lw 0.200001
set object 624 polygon from \
  0.455345, -1.86509 to \
  2.29385, -1.86509 to \
  2.29385, -3.85382 to \
  0.455345, -3.85382 to \
  0.455345, -1.86509 front fs empty border lc rgb '#6165' lw 0.200001
set object 625 polygon from \
  0.416316, -1.96319 to \
  2.27471, -1.96319 to \
  2.27471, -3.95192 to \
  0.416316, -3.95192 to \
  0.416316, -1.96319 front fs empty border lc rgb '#6165' lw 0.200001
set object 626 polygon from \
  0.376306, -2.06129 to \
  2.25459, -2.06129 to \
  2.25459, -4.05002 to \
  0.376306, -4.05002 to \
  0.376306, -2.06129 front fs empty border lc rgb '#6165' lw 0.200001
set object 627 polygon from \
  0.335315, -2.15939 to \
  2.23349, -2.15939 to \
  2.23349, -4.14812 to \
  0.335315, -4.14812 to \
  0.335315, -2.15939 front fs empty border lc rgb '#6165' lw 0.200001
set object 628 polygon from \
  0.293344, -2.25749 to \
  2.2114, -2.25749 to \
  2.2114, -4.24622 to \
  0.293344, -4.24622 to \
  0.293344, -2.25749 front fs empty border lc rgb '#6165' lw 0.200001
set object 629 polygon from \
  0.250391, -2.35559 to \
  2.18834, -2.35559 to \
  2.18834, -4.34432 to \
  0.250391, -4.34432 to \
  0.250391, -2.35559 front fs empty border lc rgb '#6165' lw 0.200001
set object 630 polygon from \
  0.206457, -2.45369 to \
  2.16429, -2.45369 to \
  2.16429, -4.44242 to \
  0.206457, -4.44242 to \
  0.206457, -2.45369 front fs empty border lc rgb '#6165' lw 0.200001
set object 631 polygon from \
  0.161542, -2.55179 to \
  2.13926, -2.55179 to \
  2.13926, -4.54052 to \
  0.161542, -4.54052 to \
  0.161542, -2.55179 front fs empty border lc rgb '#6165' lw 0.200001
set object 632 polygon from \
  0.115646, -2.64989 to \
  2.11326, -2.64989 to \
  2.11326, -4.63862 to \
  0.115646, -4.63862 to \
  0.115646, -2.64989 front fs empty border lc rgb '#6165' lw 0.200001
set object 633 polygon from \
  0.0687692, -2.74799 to \
  2.08627, -2.74799 to \
  2.08627, -4.73672 to \
  0.0687692, -4.73672 to \
  0.0687692, -2.74799 front fs empty border lc rgb '#6165' lw 0.200001
set object 634 polygon from \
  0.0209115, -2.84609 to \
  2.0583, -2.84609 to \
  2.0583, -4.83482 to \
  0.0209115, -4.83482 to \
  0.0209115, -2.84609 front fs empty border lc rgb '#6165' lw 0.200001
set object 635 polygon from \
  0, -2.94419 to \
  2.02934, -2.94419 to \
  2.02934, -4.93292 to \
  0, -4.93292 to \
  0, -2.94419 front fs empty border lc rgb '#6165' lw 0.200001
set object 636 polygon from \
  0, -3.04229 to \
  1.99941, -3.04229 to \
  1.99941, -5.03102 to \
  0, -5.03102 to \
  0, -3.04229 front fs empty border lc rgb '#6165' lw 0.200001
set object 637 polygon from \
  0, -3.14039 to \
  1.9685, -3.14039 to \
  1.9685, -5.12912 to \
  0, -5.12912 to \
  0, -3.14039 front fs empty border lc rgb '#6165' lw 0.200001
set object 638 polygon from \
  0, -3.23849 to \
  1.9366, -3.23849 to \
  1.9366, -5.22722 to \
  0, -5.22722 to \
  0, -3.23849 front fs empty border lc rgb '#6165' lw 0.200001
set object 639 polygon from \
  0, -3.33659 to \
  1.90373, -3.33659 to \
  1.90373, -5.32532 to \
  0, -5.32532 to \
  0, -3.33659 front fs empty border lc rgb '#6165' lw 0.200001
set object 640 polygon from \
  0, -3.43469 to \
  1.86987, -3.43469 to \
  1.86987, -5.42342 to \
  0, -5.42342 to \
  0, -3.43469 front fs empty border lc rgb '#6165' lw 0.200001
set object 641 polygon from \
  0, -3.53279 to \
  1.83503, -3.53279 to \
  1.83503, -5.52152 to \
  0, -5.52152 to \
  0, -3.53279 front fs empty border lc rgb '#6165' lw 0.200001
set object 642 polygon from \
  0, -3.63089 to \
  1.79922, -3.63089 to \
  1.79922, -5.61962 to \
  0, -5.61962 to \
  0, -3.63089 front fs empty border lc rgb '#6165' lw 0.200001
set object 643 polygon from \
  0, -3.72899 to \
  1.76242, -3.72899 to \
  1.76242, -5.71772 to \
  0, -5.71772 to \
  0, -3.72899 front fs empty border lc rgb '#6165' lw 0.200001
set object 644 polygon from \
  0, -3.82709 to \
  1.72464, -3.82709 to \
  1.72464, -5.81582 to \
  0, -5.81582 to \
  0, -3.82709 front fs empty border lc rgb '#6165' lw 0.200001
set object 645 polygon from \
  0, -3.92519 to \
  1.68587, -3.92519 to \
  1.68587, -5.91392 to \
  0, -5.91392 to \
  0, -3.92519 front fs empty border lc rgb '#6165' lw 0.200001
set object 646 polygon from \
  0, -4.02329 to \
  1.64613, -4.02329 to \
  1.64613, -6.01202 to \
  0, -6.01202 to \
  0, -4.02329 front fs empty border lc rgb '#6165' lw 0.200001
set object 647 polygon from \
  0, -4.12139 to \
  1.60541, -4.12139 to \
  1.60541, -6.11012 to \
  0, -6.11012 to \
  0, -4.12139 front fs empty border lc rgb '#6165' lw 0.200001
set object 648 polygon from \
  0, -4.21949 to \
  1.5637, -4.21949 to \
  1.5637, -6.20822 to \
  0, -6.20822 to \
  0, -4.21949 front fs empty border lc rgb '#6165' lw 0.200001
set object 649 polygon from \
  0, -4.31759 to \
  1.52102, -4.31759 to \
  1.52102, -6.30632 to \
  0, -6.30632 to \
  0, -4.31759 front fs empty border lc rgb '#6165' lw 0.200001
set object 650 polygon from \
  0, -4.41569 to \
  1.47735, -4.41569 to \
  1.47735, -6.40442 to \
  0, -6.40442 to \
  0, -4.41569 front fs empty border lc rgb '#6165' lw 0.200001
set object 651 polygon from \
  0, -4.51379 to \
  1.4327, -4.51379 to \
  1.4327, -6.50252 to \
  0, -6.50252 to \
  0, -4.51379 front fs empty border lc rgb '#6165' lw 0.200001
set object 652 polygon from \
  0, -4.61189 to \
  1.38708, -4.61189 to \
  1.38708, -6.60062 to \
  0, -6.60062 to \
  0, -4.61189 front fs empty border lc rgb '#6165' lw 0.200001
set object 653 polygon from \
  0, -4.70999 to \
  1.34047, -4.70999 to \
  1.34047, -6.69872 to \
  0, -6.69872 to \
  0, -4.70999 front fs empty border lc rgb '#6165' lw 0.200001
set object 654 polygon from \
  0, -4.80809 to \
  1.29288, -4.80809 to \
  1.29288, -6.79682 to \
  0, -6.79682 to \
  0, -4.80809 front fs empty border lc rgb '#6165' lw 0.200001
set object 655 polygon from \
  0, -4.90619 to \
  1.2443, -4.90619 to \
  1.2443, -6.89492 to \
  0, -6.89492 to \
  0, -4.90619 front fs empty border lc rgb '#6165' lw 0.200001
set object 656 polygon from \
  0, -5.00429 to \
  1.19475, -5.00429 to \
  1.19475, -6.99302 to \
  0, -6.99302 to \
  0, -5.00429 front fs empty border lc rgb '#6165' lw 0.200001
set object 657 polygon from \
  0, -5.10239 to \
  1.14422, -5.10239 to \
  1.14422, -7.09112 to \
  0, -7.09112 to \
  0, -5.10239 front fs empty border lc rgb '#6165' lw 0.200001
set object 658 polygon from \
  0, -5.20049 to \
  1.0927, -5.20049 to \
  1.0927, -7.18922 to \
  0, -7.18922 to \
  0, -5.20049 front fs empty border lc rgb '#6165' lw 0.200001
set object 659 polygon from \
  0, -5.29859 to \
  1.04021, -5.29859 to \
  1.04021, -7.28732 to \
  0, -7.28732 to \
  0, -5.29859 front fs empty border lc rgb '#6165' lw 0.200001
set object 660 polygon from \
  0, -5.39669 to \
  0.986728, -5.39669 to \
  0.986728, -7.38542 to \
  0, -7.38542 to \
  0, -5.39669 front fs empty border lc rgb '#6165' lw 0.200001
set object 661 polygon from \
  0, -5.49479 to \
  0.932271, -5.49479 to \
  0.932271, -7.48352 to \
  0, -7.48352 to \
  0, -5.49479 front fs empty border lc rgb '#6165' lw 0.200001
set object 662 polygon from \
  0, -5.59289 to \
  0.876832, -5.59289 to \
  0.876832, -7.58162 to \
  0, -7.58162 to \
  0, -5.59289 front fs empty border lc rgb '#6165' lw 0.200001
set object 663 polygon from \
  0, -5.69099 to \
  0.820413, -5.69099 to \
  0.820413, -7.67972 to \
  0, -7.67972 to \
  0, -5.69099 front fs empty border lc rgb '#6165' lw 0.200001
set object 664 polygon from \
  0, -5.78909 to \
  0.763012, -5.78909 to \
  0.763012, -7.77782 to \
  0, -7.77782 to \
  0, -5.78909 front fs empty border lc rgb '#6165' lw 0.200001
set object 665 polygon from \
  0, -5.88719 to \
  0.704631, -5.88719 to \
  0.704631, -7.87592 to \
  0, -7.87592 to \
  0, -5.88719 front fs empty border lc rgb '#6165' lw 0.200001
set object 666 polygon from \
  0, -5.98529 to \
  0.645268, -5.98529 to \
  0.645268, -7.97402 to \
  0, -7.97402 to \
  0, -5.98529 front fs empty border lc rgb '#6165' lw 0.200001
set object 667 polygon from \
  0, -6.08339 to \
  0.584925, -6.08339 to \
  0.584925, -8.07212 to \
  0, -8.07212 to \
  0, -6.08339 front fs empty border lc rgb '#6165' lw 0.200001
set object 668 polygon from \
  0, -6.18149 to \
  0.5236, -6.18149 to \
  0.5236, -8.17022 to \
  0, -8.17022 to \
  0, -6.18149 front fs empty border lc rgb '#6165' lw 0.200001
set object 669 polygon from \
  0, -6.27959 to \
  0.461295, -6.27959 to \
  0.461295, -8.26832 to \
  0, -8.26832 to \
  0, -6.27959 front fs empty border lc rgb '#6165' lw 0.200001
set object 670 polygon from \
  0, -6.37769 to \
  0.398009, -6.37769 to \
  0.398009, -8.36642 to \
  0, -8.36642 to \
  0, -6.37769 front fs empty border lc rgb '#6165' lw 0.200001
set object 671 polygon from \
  0, -6.47579 to \
  0.333741, -6.47579 to \
  0.333741, -8.46452 to \
  0, -8.46452 to \
  0, -6.47579 front fs empty border lc rgb '#6165' lw 0.200001
set object 672 polygon from \
  0, -6.57389 to \
  0.268493, -6.57389 to \
  0.268493, -8.56262 to \
  0, -8.56262 to \
  0, -6.57389 front fs empty border lc rgb '#6165' lw 0.200001
set object 673 polygon from \
  0, -6.67199 to \
  0.202263, -6.67199 to \
  0.202263, -8.66072 to \
  0, -8.66072 to \
  0, -6.67199 front fs empty border lc rgb '#6165' lw 0.200001
set object 674 polygon from \
  0, -6.77009 to \
  0.135053, -6.77009 to \
  0.135053, -8.75882 to \
  0, -8.75882 to \
  0, -6.77009 front fs empty border lc rgb '#6165' lw 0.200001
set object 675 polygon from \
  0, -6.86819 to \
  0.0668608, -6.86819 to \
  0.0668608, -8.85692 to \
  0, -8.85692 to \
  0, -6.86819 front fs empty border lc rgb '#6165' lw 0.200001
plot [-1.02003:11.2205] [-16.7139:13.158] NaN notitle 

