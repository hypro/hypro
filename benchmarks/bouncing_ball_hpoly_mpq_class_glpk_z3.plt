# settings
set term pdf
set output "bouncing_ball_hpoly_mpq_class_glpk_z3.pdf
set xtics autofreq
set ytics autofreq
set grid back
# axis settings
set xzeroaxis 
set zeroaxis 
set xtics axis 
set xrange [-30.9513:46.6043] 
set yzeroaxis 
set ytics axis 
set yrange [-8.68278:95.5107] 

# plotting sets
set object 1 polygon from \
  -0.098223, 10.1999 to \
  -0.000123033, 10.2004 to \
  40.1414, 10.2004 to \
  -0.0979769, 9.99915 to \
  -20.1718, 9.99915 to \
  -0.098223, 10.1999 front fs empty border lc rgb '#6165' lw 0.200001
set object 2 polygon from \
  -0.196346, 10.1985 to \
  -0.0982284, 10.1999 to \
  40.0434, 10.6013 to \
  -0.196104, 9.99768 to \
  -20.2699, 9.79694 to \
  -0.196346, 10.1985 front fs empty border lc rgb '#6165' lw 0.200001
set object 3 polygon from \
  -0.294471, 10.196 to \
  -0.196314, 10.1985 to \
  39.9453, 11.0013 to \
  -0.29422, 9.99522 to \
  -20.368, 9.59375 to \
  -0.294471, 10.196 front fs empty border lc rgb '#6165' lw 0.200001
set object 4 polygon from \
  -0.39259, 10.1926 to \
  -0.294419, 10.196 to \
  39.8473, 11.4003 to \
  -0.392317, 9.99179 to \
  -20.4661, 9.38958 to \
  -0.39259, 10.1926 front fs empty border lc rgb '#6165' lw 0.200001
set object 5 polygon from \
  -0.490707, 10.1881 to \
  -0.392516, 10.1926 to \
  39.7493, 11.7982 to \
  -0.490443, 9.98738 to \
  -20.5642, 9.18442 to \
  -0.490707, 10.1881 front fs empty border lc rgb '#6165' lw 0.200001
set object 6 polygon from \
  -0.588826, 10.1827 to \
  -0.490617, 10.1882 to \
  39.6513, 12.1952 to \
  -0.588557, 9.98198 to \
  -20.6623, 8.97829 to \
  -0.588826, 10.1827 front fs empty border lc rgb '#6165' lw 0.200001
set object 7 polygon from \
  -0.686923, 10.1764 to \
  -0.588719, 10.1828 to \
  39.5534, 12.5913 to \
  -0.686679, 9.9756 to \
  -20.7604, 8.77117 to \
  -0.686923, 10.1764 front fs empty border lc rgb '#6165' lw 0.200001
set object 8 polygon from \
  -0.785026, 10.169 to \
  -0.686833, 10.1764 to \
  39.4554, 12.9863 to \
  -0.784778, 9.96825 to \
  -20.8585, 8.56308 to \
  -0.785026, 10.169 front fs empty border lc rgb '#6165' lw 0.200001
set object 9 polygon from \
  -0.883155, 10.1607 to \
  -0.784932, 10.169 to \
  39.3574, 13.3804 to \
  -0.882894, 9.95991 to \
  -20.9566, 8.354 to \
  -0.883155, 10.1607 front fs empty border lc rgb '#6165' lw 0.200001
set object 10 polygon from \
  -0.981285, 10.1513 to \
  -0.883028, 10.1607 to \
  39.2594, 13.7735 to \
  -0.980996, 9.95059 to \
  -21.0547, 8.14395 to \
  -0.981285, 10.1513 front fs empty border lc rgb '#6165' lw 0.200001
set object 11 polygon from \
  -1.0794, 10.141 to \
  -0.981113, 10.1514 to \
  39.1614, 14.1656 to \
  -1.07909, 9.94029 to \
  -21.1528, 7.93291 to \
  -1.0794, 10.141 front fs empty border lc rgb '#6165' lw 0.200001
set object 12 polygon from \
  -1.17751, 10.1298 to \
  -1.07921, 10.1411 to \
  39.0635, 14.5568 to \
  -1.1772, 9.929 to \
  -21.2509, 7.72089 to \
  -1.17751, 10.1298 front fs empty border lc rgb '#6165' lw 0.200001
set object 13 polygon from \
  -1.27563, 10.1175 to \
  -1.17732, 10.1298 to \
  38.9655, 14.9469 to \
  -1.2753, 9.91674 to \
  -21.349, 7.50789 to \
  -1.27563, 10.1175 front fs empty border lc rgb '#6165' lw 0.200001
set object 14 polygon from \
  -1.37373, 10.1042 to \
  -1.27543, 10.1175 to \
  38.8675, 15.3361 to \
  -1.3734, 9.9035 to \
  -21.4471, 7.29391 to \
  -1.37373, 10.1042 front fs empty border lc rgb '#6165' lw 0.200001
set object 15 polygon from \
  -1.47184, 10.09 to \
  -1.37353, 10.1043 to \
  38.7695, 15.7243 to \
  -1.47153, 9.88927 to \
  -21.5453, 7.07894 to \
  -1.47184, 10.09 front fs empty border lc rgb '#6165' lw 0.200001
set object 16 polygon from \
  -1.56997, 10.0748 to \
  -1.47162, 10.09 to \
  38.6715, 16.1115 to \
  -1.56967, 9.87406 to \
  -21.6434, 6.863 to \
  -1.56997, 10.0748 front fs empty border lc rgb '#6165' lw 0.200001
set object 17 polygon from \
  -1.66807, 10.0586 to \
  -1.56974, 10.0748 to \
  38.5736, 16.4978 to \
  -1.66781, 9.85786 to \
  -21.7415, 6.64607 to \
  -1.66807, 10.0586 front fs empty border lc rgb '#6165' lw 0.200001
set object 18 polygon from \
  -1.76621, 10.0414 to \
  -1.66784, 10.0586 to \
  38.4756, 16.883 to \
  -1.76594, 9.84069 to \
  -21.8396, 6.42817 to \
  -1.76621, 10.0414 front fs empty border lc rgb '#6165' lw 0.200001
set object 19 polygon from \
  -1.86431, 10.0233 to \
  -1.76594, 10.0415 to \
  38.3776, 17.2673 to \
  -1.86406, 9.82253 to \
  -21.9377, 6.20928 to \
  -1.86431, 10.0233 front fs empty border lc rgb '#6165' lw 0.200001
set object 20 polygon from \
  -1.96244, 10.0041 to \
  -1.86405, 10.0233 to \
  38.2796, 17.6506 to \
  -1.96217, 9.8034 to \
  -22.0358, 5.98941 to \
  -1.96244, 10.0041 front fs empty border lc rgb '#6165' lw 0.200001
set object 21 polygon from \
  -2.06053, 9.98398 to \
  -1.96214, 10.0042 to \
  38.1816, 18.0329 to \
  -2.06027, 9.78329 to \
  -22.1339, 5.76856 to \
  -2.06053, 9.98398 front fs empty border lc rgb '#6165' lw 0.200001
set object 22 polygon from \
  -2.15866, 9.96287 to \
  -2.06023, 9.98403 to \
  38.0836, 18.4143 to \
  -2.15838, 9.76219 to \
  -22.232, 5.54673 to \
  -2.15866, 9.96287 front fs empty border lc rgb '#6165' lw 0.200001
set object 23 polygon from \
  -2.2568, 9.94079 to \
  -2.15832, 9.96295 to \
  37.9856, 18.7946 to \
  -2.2565, 9.74011 to \
  -22.3301, 5.32392 to \
  -2.2568, 9.94079 front fs empty border lc rgb '#6165' lw 0.200001
set object 24 polygon from \
  -2.35493, 9.91772 to \
  -2.25643, 9.94087 to \
  37.8876, 19.174 to \
  -2.35462, 9.71706 to \
  -22.4282, 5.10013 to \
  -2.35493, 9.91772 front fs empty border lc rgb '#6165' lw 0.200001
set object 25 polygon from \
  -2.45307, 9.89367 to \
  -2.35453, 9.91781 to \
  37.7896, 19.5524 to \
  -2.45274, 9.69301 to \
  -22.5263, 4.87536 to \
  -2.45307, 9.89367 front fs empty border lc rgb '#6165' lw 0.200001
set object 26 polygon from \
  -2.55121, 9.86864 to \
  -2.45263, 9.89378 to \
  37.6916, 19.9299 to \
  -2.55088, 9.66798 to \
  -22.6244, 4.64961 to \
  -2.55121, 9.86864 front fs empty border lc rgb '#6165' lw 0.200001
set object 27 polygon from \
  -2.64932, 9.84264 to \
  -2.55074, 9.86876 to \
  37.5936, 20.3063 to \
  -2.64901, 9.64198 to \
  -22.7225, 4.42287 to \
  -2.64932, 9.84264 front fs empty border lc rgb '#6165' lw 0.200001
set object 28 polygon from \
  -2.7474, 9.81566 to \
  -2.64885, 9.84276 to \
  37.4956, 20.6818 to \
  -2.7471, 9.615 to \
  -22.8206, 4.19515 to \
  -2.7474, 9.81566 front fs empty border lc rgb '#6165' lw 0.200001
set object 29 polygon from \
  -2.84549, 9.7877 to \
  -2.74696, 9.81578 to \
  37.3976, 21.0563 to \
  -2.84522, 9.58703 to \
  -22.9187, 3.96646 to \
  -2.84549, 9.7877 front fs empty border lc rgb '#6165' lw 0.200001
set object 30 polygon from \
  -2.9436, 9.75875 to \
  -2.84506, 9.78782 to \
  37.2997, 21.4298 to \
  -2.94334, 9.55808 to \
  -23.0168, 3.73678 to \
  -2.9436, 9.75875 front fs empty border lc rgb '#6165' lw 0.200001
set object 31 polygon from \
  -3.04174, 9.72881 to \
  -2.94316, 9.75887 to \
  37.2018, 21.8024 to \
  -3.04144, 9.52816 to \
  -23.1149, 3.50612 to \
  -3.04174, 9.72881 front fs empty border lc rgb '#6165' lw 0.200001
set object 32 polygon from \
  -3.13988, 9.69789 to \
  -3.04127, 9.72895 to \
  37.1038, 22.174 to \
  -3.13955, 9.49725 to \
  -23.213, 3.27448 to \
  -3.13988, 9.69789 front fs empty border lc rgb '#6165' lw 0.200001
set object 33 polygon from \
  -3.23801, 9.66599 to \
  -3.13937, 9.69805 to \
  37.0058, 22.5445 to \
  -3.23769, 9.46535 to \
  -23.3111, 3.04186 to \
  -3.23801, 9.66599 front fs empty border lc rgb '#6165' lw 0.200001
set object 34 polygon from \
  -3.33615, 9.63311 to \
  -3.23746, 9.66617 to \
  36.9079, 22.9142 to \
  -3.33583, 9.43247 to \
  -23.4092, 2.80826 to \
  -3.33615, 9.63311 front fs empty border lc rgb '#6165' lw 0.200001
set object 35 polygon from \
  -3.43428, 9.59924 to \
  -3.33556, 9.6333 to \
  36.8099, 23.2828 to \
  -3.43396, 9.39861 to \
  -23.5073, 2.57367 to \
  -3.43428, 9.59924 front fs empty border lc rgb '#6165' lw 0.200001
set object 36 polygon from \
  -3.53241, 9.5644 to \
  -3.43367, 9.59945 to \
  36.7119, 23.6504 to \
  -3.5321, 9.36377 to \
  -23.6054, 2.33811 to \
  -3.53241, 9.5644 front fs empty border lc rgb '#6165' lw 0.200001
set object 37 polygon from \
  -3.63054, 9.52857 to \
  -3.53176, 9.56463 to \
  36.6139, 24.0171 to \
  -3.63022, 9.32795 to \
  -23.7035, 2.10156 to \
  -3.63054, 9.52857 front fs empty border lc rgb '#6165' lw 0.200001
set object 38 polygon from \
  -3.72865, 9.49177 to \
  -3.62985, 9.52882 to \
  36.516, 24.3828 to \
  -3.72836, 9.29114 to \
  -23.8016, 1.86404 to \
  -3.72865, 9.49177 front fs empty border lc rgb '#6165' lw 0.200001
set object 39 polygon from \
  -3.82678, 9.45399 to \
  -3.72795, 9.49203 to \
  36.418, 24.7475 to \
  -3.82647, 9.25336 to \
  -23.8997, 1.62553 to \
  -3.82678, 9.45399 front fs empty border lc rgb '#6165' lw 0.200001
set object 40 polygon from \
  -3.92491, 9.41521 to \
  -3.82605, 9.45426 to \
  36.32, 25.1113 to \
  -3.92458, 9.2146 to \
  -23.9978, 1.38604 to \
  -3.92491, 9.41521 front fs empty border lc rgb '#6165' lw 0.200001
set object 41 polygon from \
  -4.02303, 9.37547 to \
  -3.92416, 9.41551 to \
  36.222, 25.474 to \
  -4.02272, 9.17485 to \
  -24.0959, 1.14557 to \
  -4.02303, 9.37547 front fs empty border lc rgb '#6165' lw 0.200001
set object 42 polygon from \
  -4.12116, 9.33473 to \
  -4.02225, 9.37578 to \
  36.124, 25.8358 to \
  -4.12086, 9.13412 to \
  -24.194, 0.904118 to \
  -4.12116, 9.33473 front fs empty border lc rgb '#6165' lw 0.200001
set object 43 polygon from \
  -4.2193, 9.29301 to \
  -4.12034, 9.33507 to \
  36.026, 26.1966 to \
  -4.219, 9.0924 to \
  -24.2921, 0.661687 to \
  -4.2193, 9.29301 front fs empty border lc rgb '#6165' lw 0.200001
set object 44 polygon from \
  -4.31744, 9.25031 to \
  -4.21844, 9.29338 to \
  35.928, 26.5564 to \
  -4.31712, 9.04971 to \
  -24.3902, 0.418274 to \
  -4.31744, 9.25031 front fs empty border lc rgb '#6165' lw 0.200001
set object 45 polygon from \
  -4.41557, 9.20663 to \
  -4.31654, 9.2507 to \
  35.8301, 26.9152 to \
  -4.41525, 9.00604 to \
  -24.4883, 0.173881 to \
  -4.41557, 9.20663 front fs empty border lc rgb '#6165' lw 0.200001
set object 46 polygon from \
  -4.51369, 9.16198 to \
  -4.41464, 9.20705 to \
  35.7321, 27.2731 to \
  -4.51337, 8.96139 to \
  -24.4275, 0 to \
  -24.431, 0 to \
  -4.51369, 9.16198 front fs empty border lc rgb '#6165' lw 0.200001
set object 47 polygon from \
  -4.61178, 9.11635 to \
  -4.51275, 9.16241 to \
  35.6341, 27.63 to \
  -4.61149, 8.91575 to \
  -23.9935, 0 to \
  -24.0082, 0 to \
  -4.61178, 9.11635 front fs empty border lc rgb '#6165' lw 0.200001
set object 48 polygon from \
  -4.7099, 9.06974 to \
  -4.61085, 9.11679 to \
  35.5362, 27.9859 to \
  -4.70961, 8.86914 to \
  -23.5801, 0 to \
  -23.6051, 0 to \
  -4.7099, 9.06974 front fs empty border lc rgb '#6165' lw 0.200001
set object 49 polygon from \
  -4.80803, 9.02214 to \
  -4.70895, 9.07019 to \
  35.4382, 28.3409 to \
  -4.80774, 8.82154 to \
  -23.1859, 0 to \
  -23.2205, 0 to \
  -4.80803, 9.02214 front fs empty border lc rgb '#6165' lw 0.200001
set object 50 polygon from \
  -4.90616, 8.97355 to \
  -4.80705, 9.02261 to \
  35.3403, 28.6948 to \
  -4.90587, 8.77295 to \
  -22.8098, 0 to \
  -22.8532, 0 to \
  -4.90616, 8.97355 front fs empty border lc rgb '#6165' lw 0.200001
set object 51 polygon from \
  -5.00429, 8.92398 to \
  -4.90515, 8.97405 to \
  35.2424, 29.0478 to \
  -5.00396, 8.7234 to \
  -22.4507, 0 to \
  -22.5022, 0 to \
  -5.00429, 8.92398 front fs empty border lc rgb '#6165' lw 0.200001
set object 52 polygon from \
  -5.10242, 8.87343 to \
  -5.00324, 8.92451 to \
  35.1445, 29.3999 to \
  -5.10209, 8.67286 to \
  -22.1077, 0 to \
  -22.1666, 0 to \
  -5.10242, 8.87343 front fs empty border lc rgb '#6165' lw 0.200001
set object 53 polygon from \
  -5.20057, 8.82189 to \
  -5.10134, 8.87399 to \
  35.0465, 29.7509 to \
  -5.20022, 8.62134 to \
  -21.7797, 0 to \
  -21.8456, 0 to \
  -5.20057, 8.82189 front fs empty border lc rgb '#6165' lw 0.200001
set object 54 polygon from \
  -5.29868, 8.76939 to \
  -5.19944, 8.82248 to \
  34.9485, 30.1009 to \
  -5.29833, 8.56883 to \
  -21.4659, 0 to \
  -21.5382, 0 to \
  -5.29868, 8.76939 front fs empty border lc rgb '#6165' lw 0.200001
set object 55 polygon from \
  -5.39683, 8.71588 to \
  -5.29754, 8.77 to \
  34.8506, 30.45 to \
  -5.39646, 8.51534 to \
  -21.1656, 0 to \
  -21.2438, 0 to \
  -5.39683, 8.71588 front fs empty border lc rgb '#6165' lw 0.200001
set object 56 polygon from \
  -5.49495, 8.66142 to \
  -5.39565, 8.71653 to \
  34.7526, 30.7981 to \
  -5.4946, 8.46087 to \
  -20.878, 0 to \
  -20.9617, 0 to \
  -5.49495, 8.66142 front fs empty border lc rgb '#6165' lw 0.200001
set object 57 polygon from \
  -5.59307, 8.60596 to \
  -5.49373, 8.66209 to \
  34.6547, 31.1453 to \
  -5.59271, 8.40542 to \
  -20.6024, 0 to \
  -20.6912, 0 to \
  -5.59307, 8.60596 front fs empty border lc rgb '#6165' lw 0.200001
set object 58 polygon from \
  -5.6912, 8.54952 to \
  -5.59183, 8.60666 to \
  34.5567, 31.4914 to \
  -5.69084, 8.34899 to \
  -20.3381, 0 to \
  -20.4317, 0 to \
  -5.6912, 8.54952 front fs empty border lc rgb '#6165' lw 0.200001
set object 59 polygon from \
  -5.78935, 8.4921 to \
  -5.68994, 8.55025 to \
  34.4588, 31.8365 to \
  -5.78895, 8.29159 to \
  -20.0847, 0 to \
  -20.1827, 0 to \
  -5.78935, 8.4921 front fs empty border lc rgb '#6165' lw 0.200001
set object 60 polygon from \
  -5.88745, 8.43371 to \
  -5.78805, 8.49285 to \
  34.3609, 32.1808 to \
  -5.88708, 8.23319 to \
  -19.8416, 0 to \
  -19.9436, 0 to \
  -5.88745, 8.43371 front fs empty border lc rgb '#6165' lw 0.200001
set object 61 polygon from \
  -5.98559, 8.37432 to \
  -5.88615, 8.43448 to \
  34.263, 32.524 to \
  -5.98519, 8.17382 to \
  -19.6082, 0 to \
  -19.7139, 0 to \
  -5.98559, 8.37432 front fs empty border lc rgb '#6165' lw 0.200001
set object 62 polygon from \
  -6.08372, 8.31396 to \
  -5.98424, 8.37513 to \
  34.165, 32.8662 to \
  -6.08333, 8.11345 to \
  -19.384, 0 to \
  -19.4933, 0 to \
  -6.08372, 8.31396 front fs empty border lc rgb '#6165' lw 0.200001
set object 63 polygon from \
  -6.18184, 8.25261 to \
  -6.08235, 8.3148 to \
  34.067, 33.2075 to \
  -6.18145, 8.05212 to \
  -19.1687, 0 to \
  -19.2812, 0 to \
  -6.18184, 8.25261 front fs empty border lc rgb '#6165' lw 0.200001
set object 64 polygon from \
  -6.27997, 8.19029 to \
  -6.18045, 8.25348 to \
  33.9691, 33.5478 to \
  -6.27957, 7.9898 to \
  -18.9617, 0 to \
  -19.0772, 0 to \
  -6.27997, 8.19029 front fs empty border lc rgb '#6165' lw 0.200001
set object 65 polygon from \
  -6.37809, 8.12699 to \
  -6.27855, 8.19119 to \
  33.8713, 33.8871 to \
  -6.37769, 7.9265 to \
  -18.7628, 0 to \
  -18.8811, 0 to \
  -6.37809, 8.12699 front fs empty border lc rgb '#6165' lw 0.200001
set object 66 polygon from \
  -6.47621, 8.0627 to \
  -6.37665, 8.12791 to \
  33.7732, 34.2254 to \
  -6.47581, 7.86222 to \
  -18.5715, 0 to \
  -18.6924, 0 to \
  -6.47621, 8.0627 front fs empty border lc rgb '#6165' lw 0.200001
set object 67 polygon from \
  -6.57433, 7.99744 to \
  -6.47474, 8.06366 to \
  33.6753, 34.5627 to \
  -6.57393, 7.79696 to \
  -18.3875, 0 to \
  -18.5107, 0 to \
  -6.57433, 7.99744 front fs empty border lc rgb '#6165' lw 0.200001
set object 68 polygon from \
  -6.67247, 7.93118 to \
  -6.57284, 7.99843 to \
  33.5774, 34.8991 to \
  -6.67203, 7.73073 to \
  -18.2104, 0 to \
  -18.3359, 0 to \
  -6.67247, 7.93118 front fs empty border lc rgb '#6165' lw 0.200001
set object 69 polygon from \
  -6.77057, 7.86396 to \
  -6.67094, 7.93221 to \
  33.4794, 35.2345 to \
  -6.77017, 7.66349 to \
  -18.04, 0 to \
  -18.1676, 0 to \
  -6.77057, 7.86396 front fs empty border lc rgb '#6165' lw 0.200001
set object 70 polygon from \
  -6.8687, 7.79574 to \
  -6.76903, 7.86501 to \
  33.3815, 35.5689 to \
  -6.86828, 7.59529 to \
  -17.8759, 0 to \
  -18.0054, 0 to \
  -6.8687, 7.79574 front fs empty border lc rgb '#6165' lw 0.200001
set object 71 polygon from \
  -6.96682, 7.72655 to \
  -6.86714, 7.79683 to \
  33.2837, 35.9025 to \
  -6.96639, 7.52611 to \
  -17.7179, 0 to \
  -17.8492, 0 to \
  -6.96682, 7.72655 front fs empty border lc rgb '#6165' lw 0.200001
set object 72 polygon from \
  -7.06495, 7.65637 to \
  -6.96524, 7.72766 to \
  33.1858, 36.235 to \
  -7.06453, 7.45593 to \
  -17.5658, 0 to \
  -17.6987, 0 to \
  -7.06495, 7.65637 front fs empty border lc rgb '#6165' lw 0.200001
set object 73 polygon from \
  -7.16306, 7.58522 to \
  -7.06333, 7.65752 to \
  33.0879, 36.5665 to \
  -7.16266, 7.38477 to \
  -17.4192, 0 to \
  -17.5537, 0 to \
  -7.16306, 7.58522 front fs empty border lc rgb '#6165' lw 0.200001
set object 74 polygon from \
  -7.26116, 7.5131 to \
  -7.16143, 7.5864 to \
  32.9899, 36.8969 to \
  -7.26077, 7.31265 to \
  -17.278, 0 to \
  -17.4139, 0 to \
  -7.26116, 7.5131 front fs empty border lc rgb '#6165' lw 0.200001
set object 75 polygon from \
  -7.35928, 7.43998 to \
  -7.25953, 7.51429 to \
  32.8921, 37.2265 to \
  -7.35889, 7.23953 to \
  -17.142, 0 to \
  -17.2792, 0 to \
  -7.35928, 7.43998 front fs empty border lc rgb '#6165' lw 0.200001
set object 76 polygon from \
  -7.45742, 7.36587 to \
  -7.35764, 7.44121 to \
  32.7942, 37.5552 to \
  -7.45702, 7.16543 to \
  -17.0109, 0 to \
  -17.1493, 0 to \
  -7.45742, 7.36587 front fs empty border lc rgb '#6165' lw 0.200001
set object 77 polygon from \
  -7.55554, 7.29079 to \
  -7.45574, 7.36714 to \
  32.6962, 37.8827 to \
  -7.55515, 7.09035 to \
  -16.8845, 0 to \
  -17.024, 0 to \
  -7.55554, 7.29079 front fs empty border lc rgb '#6165' lw 0.200001
set object 78 polygon from \
  -7.65366, 7.21473 to \
  -7.55384, 7.29209 to \
  32.5984, 38.2094 to \
  -7.65326, 7.01429 to \
  -16.7627, 0 to \
  -16.9033, 0 to \
  -7.65366, 7.21473 front fs empty border lc rgb '#6165' lw 0.200001
set object 79 polygon from \
  -7.7518, 7.13767 to \
  -7.65194, 7.21606 to \
  32.5005, 38.535 to \
  -7.75139, 6.93725 to \
  -16.6453, 0 to \
  -16.7868, 0 to \
  -7.7518, 7.13767 front fs empty border lc rgb '#6165' lw 0.200001
set object 80 polygon from \
  -7.84991, 7.05966 to \
  -7.75004, 7.13905 to \
  32.4026, 38.8597 to \
  -7.8495, 6.85924 to \
  -16.532, 0 to \
  -16.6744, 0 to \
  -7.84991, 7.05966 front fs empty border lc rgb '#6165' lw 0.200001
set object 81 polygon from \
  -7.94801, 6.98067 to \
  -7.84814, 7.06106 to \
  32.3048, 39.1834 to \
  -7.94762, 6.78024 to \
  -16.4229, 0 to \
  -16.5661, 0 to \
  -7.94801, 6.98067 front fs empty border lc rgb '#6165' lw 0.200001
set object 82 polygon from \
  -8.04613, 6.90068 to \
  -7.94624, 6.98209 to \
  32.2069, 39.5061 to \
  -8.04572, 6.70027 to \
  -16.3176, 0 to \
  -16.4615, 0 to \
  -8.04613, 6.90068 front fs empty border lc rgb '#6165' lw 0.200001
set object 83 polygon from \
  -8.14423, 6.81973 to \
  -8.04434, 6.90213 to \
  32.1089, 39.8279 to \
  -8.14383, 6.61931 to \
  -16.2161, 0 to \
  -16.3607, 0 to \
  -8.14423, 6.81973 front fs empty border lc rgb '#6165' lw 0.200001
set object 84 polygon from \
  -8.24235, 6.73778 to \
  -8.14244, 6.8212 to \
  32.011, 40.1486 to \
  -8.24192, 6.53739 to \
  -16.1183, 0 to \
  -16.2635, 0 to \
  -8.24235, 6.73778 front fs empty border lc rgb '#6165' lw 0.200001
set object 85 polygon from \
  -8.34046, 6.65486 to \
  -8.24054, 6.73928 to \
  31.9131, 40.4684 to \
  -8.34004, 6.45446 to \
  -16.0239, 0 to \
  -16.1696, 0 to \
  -8.34046, 6.65486 front fs empty border lc rgb '#6165' lw 0.200001
set object 86 polygon from \
  -8.43857, 6.57095 to \
  -8.33864, 6.65639 to \
  31.8153, 40.7873 to \
  -8.43816, 6.37055 to \
  -15.9329, 0 to \
  -16.0792, 0 to \
  -8.43857, 6.57095 front fs empty border lc rgb '#6165' lw 0.200001
set object 87 polygon from \
  -8.5367, 6.48605 to \
  -8.43674, 6.57251 to \
  31.7175, 41.1052 to \
  -8.53626, 6.28569 to \
  -15.8452, 0 to \
  -15.9919, 0 to \
  -8.5367, 6.48605 front fs empty border lc rgb '#6165' lw 0.200001
set object 88 polygon from \
  -8.63482, 6.40017 to \
  -8.53484, 6.48765 to \
  31.6195, 41.422 to \
  -8.63438, 6.19981 to \
  -15.7606, 0 to \
  -15.9077, 0 to \
  -8.63482, 6.40017 front fs empty border lc rgb '#6165' lw 0.200001
set object 89 polygon from \
  -8.73293, 6.31332 to \
  -8.63294, 6.40181 to \
  31.5217, 41.738 to \
  -8.7325, 6.11296 to \
  -15.679, 0 to \
  -15.8265, 0 to \
  -8.73293, 6.31332 front fs empty border lc rgb '#6165' lw 0.200001
set object 90 polygon from \
  -8.83105, 6.22549 to \
  -8.73105, 6.31499 to \
  31.4239, 42.0529 to \
  -8.83062, 6.02512 to \
  -15.6004, 0 to \
  -15.7482, 0 to \
  -8.83105, 6.22549 front fs empty border lc rgb '#6165' lw 0.200001
set object 91 polygon from \
  -8.92916, 6.13667 to \
  -8.82915, 6.22719 to \
  31.3261, 42.3669 to \
  -8.92873, 5.93632 to \
  -15.5246, 0 to \
  -15.6727, 0 to \
  -8.92916, 6.13667 front fs empty border lc rgb '#6165' lw 0.200001
set object 92 polygon from \
  -9.02727, 6.04689 to \
  -8.92724, 6.13841 to \
  31.2282, 42.6799 to \
  -9.02684, 5.84654 to \
  -15.4516, 0 to \
  -15.5999, 0 to \
  -9.02727, 6.04689 front fs empty border lc rgb '#6165' lw 0.200001
set object 93 polygon from \
  -9.12539, 5.95611 to \
  -9.02534, 6.04865 to \
  31.1303, 42.9919 to \
  -9.12495, 5.75577 to \
  -15.3812, 0 to \
  -15.5297, 0 to \
  -9.12539, 5.95611 front fs empty border lc rgb '#6165' lw 0.200001
set object 94 polygon from \
  -9.22351, 5.86434 to \
  -9.12344, 5.9579 to \
  31.0325, 43.303 to \
  -9.22306, 5.66402 to \
  -15.3134, 0 to \
  -15.4621, 0 to \
  -9.22351, 5.86434 front fs empty border lc rgb '#6165' lw 0.200001
set object 95 polygon from \
  -9.32164, 5.77159 to \
  -9.22154, 5.86618 to \
  30.9347, 43.6131 to \
  -9.32117, 5.57129 to \
  -15.248, 0 to \
  -15.3969, 0 to \
  -9.32164, 5.77159 front fs empty border lc rgb '#6165' lw 0.200001
set object 96 polygon from \
  -9.41977, 5.67785 to \
  -9.31964, 5.77347 to \
  30.8368, 43.9221 to \
  -9.41929, 5.47756 to \
  -15.1851, 0 to \
  -15.3341, 0 to \
  -9.41977, 5.67785 front fs empty border lc rgb '#6165' lw 0.200001
set object 97 polygon from \
  -9.51788, 5.58316 to \
  -9.41774, 5.67979 to \
  30.739, 44.2303 to \
  -9.51741, 5.38287 to \
  -15.1245, 0 to \
  -15.2737, 0 to \
  -9.51788, 5.58316 front fs empty border lc rgb '#6165' lw 0.200001
set object 98 polygon from \
  -9.61601, 5.48746 to \
  -9.51584, 5.58513 to \
  30.6412, 44.5375 to \
  -9.61552, 5.28719 to \
  -15.0662, 0 to \
  -15.2154, 0 to \
  -9.61601, 5.48746 front fs empty border lc rgb '#6165' lw 0.200001
set object 99 polygon from \
  -9.71413, 5.39078 to \
  -9.61393, 5.48948 to \
  30.5433, 44.8436 to \
  -9.71364, 5.19052 to \
  -15.01, 0 to \
  -15.1593, 0 to \
  -9.71413, 5.39078 front fs empty border lc rgb '#6165' lw 0.200001
set object 100 polygon from \
  -9.81224, 5.29314 to \
  -9.71203, 5.39285 to \
  30.4453, 45.1487 to \
  -9.81176, 5.09288 to \
  -14.956, 0 to \
  -15.1053, 0 to \
  -9.81224, 5.29314 front fs empty border lc rgb '#6165' lw 0.200001
set object 101 polygon from \
  -9.91035, 5.19452 to \
  -9.81013, 5.29524 to \
  30.3475, 45.4529 to \
  -9.90987, 4.99425 to \
  -14.9041, 0 to \
  -15.0534, 0 to \
  -9.91035, 5.19452 front fs empty border lc rgb '#6165' lw 0.200001
set object 102 polygon from \
  -10.0084, 5.09491 to \
  -9.90823, 5.19665 to \
  30.2496, 45.7561 to \
  -10.008, 4.89464 to \
  -14.8541, 0 to \
  -15.0034, 0 to \
  -10.0084, 5.09491 front fs empty border lc rgb '#6165' lw 0.200001
set object 103 polygon from \
  -10.1065, 4.99432 to \
  -10.0063, 5.09708 to \
  30.1518, 46.0584 to \
  -10.1061, 4.79407 to \
  -14.8061, 0 to \
  -14.9554, 0 to \
  -10.1065, 4.99432 front fs empty border lc rgb '#6165' lw 0.200001
set object 104 polygon from \
  -10.2047, 4.89274 to \
  -10.1044, 4.99653 to \
  30.0538, 46.3596 to \
  -10.2042, 4.69249 to \
  -14.76, 0 to \
  -14.9092, 0 to \
  -10.2047, 4.89274 front fs empty border lc rgb '#6165' lw 0.200001
set object 105 polygon from \
  -10.3028, 4.79018 to \
  -10.2025, 4.89499 to \
  29.956, 46.6599 to \
  -10.3023, 4.58994 to \
  -14.7157, 0 to \
  -14.8648, 0 to \
  -10.3028, 4.79018 front fs empty border lc rgb '#6165' lw 0.200001
set object 106 polygon from \
  -10.4009, 4.68665 to \
  -10.3006, 4.79248 to \
  29.8581, 46.9592 to \
  -10.4004, 4.48642 to \
  -14.6732, 0 to \
  -14.8222, 0 to \
  -10.4009, 4.68665 front fs empty border lc rgb '#6165' lw 0.200001
set object 107 polygon from \
  -10.499, 4.58213 to \
  -10.3987, 4.68898 to \
  29.7601, 47.2574 to \
  -10.4985, 4.38191 to \
  -14.6324, 0 to \
  -14.7814, 0 to \
  -10.499, 4.58213 front fs empty border lc rgb '#6165' lw 0.200001
set object 108 polygon from \
  -10.5971, 4.47664 to \
  -10.4968, 4.5845 to \
  29.6623, 47.5548 to \
  -10.5966, 4.27642 to \
  -14.5933, 0 to \
  -14.7421, 0 to \
  -10.5971, 4.47664 front fs empty border lc rgb '#6165' lw 0.200001
set object 109 polygon from \
  -10.6952, 4.37015 to \
  -10.5949, 4.47905 to \
  29.5644, 47.8512 to \
  -10.6947, 4.16995 to \
  -14.5558, 0 to \
  -14.7045, 0 to \
  -10.6952, 4.37015 front fs empty border lc rgb '#6165' lw 0.200001
set object 110 polygon from \
  -10.7934, 4.26269 to \
  -10.693, 4.37261 to \
  29.4666, 48.1467 to \
  -10.7929, 4.06248 to \
  -14.5199, 0 to \
  -14.6685, 0 to \
  -10.7934, 4.26269 front fs empty border lc rgb '#6165' lw 0.200001
set object 111 polygon from \
  -10.8915, 4.15425 to \
  -10.7911, 4.26519 to \
  29.369, 48.4413 to \
  -10.891, 3.95405 to \
  -14.4856, 0 to \
  -14.634, 0 to \
  -10.8915, 4.15425 front fs empty border lc rgb '#6165' lw 0.200001
set object 112 polygon from \
  -10.9896, 4.04483 to \
  -10.8892, 4.15678 to \
  29.2712, 48.7348 to \
  -10.9891, 3.84464 to \
  -14.4527, 0 to \
  -14.601, 0 to \
  -10.9896, 4.04483 front fs empty border lc rgb '#6165' lw 0.200001
set object 113 polygon from \
  -11.0877, 3.93442 to \
  -10.9873, 4.0474 to \
  29.1734, 49.0274 to \
  -11.0872, 3.73423 to \
  -14.4213, 0 to \
  -14.5695, 0 to \
  -11.0877, 3.93442 front fs empty border lc rgb '#6165' lw 0.200001
set object 114 polygon from \
  -11.1858, 3.82305 to \
  -11.0854, 3.93703 to \
  29.0755, 49.3189 to \
  -11.1853, 3.62285 to \
  -14.3914, 0 to \
  -14.5394, 0 to \
  -11.1858, 3.82305 front fs empty border lc rgb '#6165' lw 0.200001
set object 115 polygon from \
  -11.2839, 3.71068 to \
  -11.1835, 3.82569 to \
  28.9776, 49.6095 to \
  -11.2834, 3.5105 to \
  -14.3628, 0 to \
  -14.5106, 0 to \
  -11.2839, 3.71068 front fs empty border lc rgb '#6165' lw 0.200001
set object 116 polygon from \
  -11.382, 3.59733 to \
  -11.2816, 3.71336 to \
  28.8797, 49.899 to \
  -11.3815, 3.39717 to \
  -14.3356, 0 to \
  -14.4832, 0 to \
  -11.382, 3.59733 front fs empty border lc rgb '#6165' lw 0.200001
set object 117 polygon from \
  -11.4801, 3.48302 to \
  -11.3797, 3.60005 to \
  28.7819, 50.1875 to \
  -11.4797, 3.28284 to \
  -14.3097, 0 to \
  -14.4571, 0 to \
  -11.4801, 3.48302 front fs empty border lc rgb '#6165' lw 0.200001
set object 118 polygon from \
  -11.5783, 3.36771 to \
  -11.4778, 3.48576 to \
  28.684, 50.4752 to \
  -11.5778, 3.16755 to \
  -14.2851, 0 to \
  -14.4322, 0 to \
  -11.5783, 3.36771 front fs empty border lc rgb '#6165' lw 0.200001
set object 119 polygon from \
  -11.6764, 3.25143 to \
  -11.5759, 3.3705 to \
  28.5863, 50.7619 to \
  -11.6759, 3.05126 to \
  -14.2617, 0 to \
  -14.4086, 0 to \
  -11.6764, 3.25143 front fs empty border lc rgb '#6165' lw 0.200001
set object 120 polygon from \
  -11.7745, 3.13417 to \
  -11.674, 3.25424 to \
  28.4885, 51.0477 to \
  -11.774, 2.934 to \
  -14.2395, 0 to \
  -14.3863, 0 to \
  -11.7745, 3.13417 front fs empty border lc rgb '#6165' lw 0.200001
set object 121 polygon from \
  -11.8726, 3.01593 to \
  -11.7721, 3.13701 to \
  28.3905, 51.3322 to \
  -11.8721, 2.81576 to \
  -14.2186, 0 to \
  -14.3651, 0 to \
  -11.8726, 3.01593 front fs empty border lc rgb '#6165' lw 0.200001
set object 122 polygon from \
  -11.9707, 2.8967 to \
  -11.8702, 3.01879 to \
  28.2926, 51.6159 to \
  -11.9702, 2.69654 to \
  -14.1987, 0 to \
  -14.345, 0 to \
  -11.9707, 2.8967 front fs empty border lc rgb '#6165' lw 0.200001
set object 123 polygon from \
  -12.0688, 2.7765 to \
  -11.9683, 2.8996 to \
  28.1947, 51.8986 to \
  -12.0683, 2.57634 to \
  -14.1801, 0 to \
  -14.3261, 0 to \
  -12.0688, 2.7765 front fs empty border lc rgb '#6165' lw 0.200001
set object 124 polygon from \
  -12.1669, 2.65531 to \
  -12.0664, 2.77942 to \
  28.0968, 52.1803 to \
  -12.1664, 2.45515 to \
  -14.1625, 0 to \
  -14.3083, 0 to \
  -12.1669, 2.65531 front fs empty border lc rgb '#6165' lw 0.200001
set object 125 polygon from \
  -12.265, 2.53313 to \
  -12.1645, 2.65827 to \
  27.9991, 52.4612 to \
  -12.2645, 2.33299 to \
  -14.146, 0 to \
  -14.2915, 0 to \
  -12.265, 2.53313 front fs empty border lc rgb '#6165' lw 0.200001
set object 126 polygon from \
  -12.3631, 2.40998 to \
  -12.2626, 2.53613 to \
  27.9013, 52.7411 to \
  -12.3626, 2.20984 to \
  -14.1305, 0 to \
  -14.2758, 0 to \
  -12.3631, 2.40998 front fs empty border lc rgb '#6165' lw 0.200001
set object 127 polygon from \
  -12.4612, 2.28584 to \
  -12.3607, 2.41301 to \
  27.8035, 53.02 to \
  -12.4607, 2.08572 to \
  -14.1161, 0 to \
  -14.2611, 0 to \
  -12.4612, 2.28584 front fs empty border lc rgb '#6165' lw 0.200001
set object 128 polygon from \
  -12.5593, 2.16073 to \
  -12.4588, 2.28891 to \
  27.7058, 53.2981 to \
  -12.5588, 1.96061 to \
  -14.1026, 0 to \
  -14.2474, 0 to \
  -12.5593, 2.16073 front fs empty border lc rgb '#6165' lw 0.200001
set object 129 polygon from \
  -12.6574, 2.03463 to \
  -12.5569, 2.16383 to \
  27.6079, 53.5749 to \
  -12.657, 1.83452 to \
  -14.0902, 0 to \
  -14.2347, 0 to \
  -12.6574, 2.03463 front fs empty border lc rgb '#6165' lw 0.200001
set object 130 polygon from \
  -12.7556, 1.90755 to \
  -12.655, 2.03777 to \
  27.5102, 53.851 to \
  -12.7551, 1.70745 to \
  -14.0787, 0 to \
  -14.2229, 0 to \
  -12.7556, 1.90755 front fs empty border lc rgb '#6165' lw 0.200001
set object 131 polygon from \
  -12.8537, 1.7795 to \
  -12.7531, 1.91072 to \
  27.4125, 54.1261 to \
  -12.8532, 1.5794 to \
  -14.0681, 0 to \
  -14.2121, 0 to \
  -12.8537, 1.7795 front fs empty border lc rgb '#6165' lw 0.200001
set object 132 polygon from \
  -12.9518, 1.65046 to \
  -12.8512, 1.7827 to \
  27.3146, 54.4 to \
  -12.9513, 1.45037 to \
  -14.0584, 0 to \
  -14.2021, 0 to \
  -12.9518, 1.65046 front fs empty border lc rgb '#6165' lw 0.200001
set object 133 polygon from \
  -13.0499, 1.52045 to \
  -12.9493, 1.6537 to \
  27.2169, 54.6732 to \
  -13.0494, 1.32036 to \
  -14.0496, 0 to \
  -14.1931, 0 to \
  -13.0499, 1.52045 front fs empty border lc rgb '#6165' lw 0.200001
set object 134 polygon from \
  -13.148, 1.38946 to \
  -13.0474, 1.52371 to \
  27.1191, 54.9453 to \
  -13.1475, 1.18937 to \
  -14.0417, 0 to \
  -14.1849, 0 to \
  -13.148, 1.38946 front fs empty border lc rgb '#6165' lw 0.200001
set object 135 polygon from \
  -13.2461, 1.25748 to \
  -13.1455, 1.39275 to \
  27.0213, 55.2164 to \
  -13.2456, 1.05741 to \
  -14.0347, 0 to \
  -14.1775, 0 to \
  -13.2461, 1.25748 front fs empty border lc rgb '#6165' lw 0.200001
set object 136 polygon from \
  -13.3442, 1.12453 to \
  -13.2436, 1.2608 to \
  26.9237, 55.4868 to \
  -13.3437, 0.924448 to \
  -14.0285, 0 to \
  -14.171, 0 to \
  -13.3442, 1.12453 front fs empty border lc rgb '#6165' lw 0.200001
set object 137 polygon from \
  -13.4423, 0.990578 to \
  -13.3417, 1.12787 to \
  26.8258, 55.7558 to \
  -13.4418, 0.79052 to \
  -14.023, 0 to \
  -14.1653, 0 to \
  -13.4423, 0.990578 front fs empty border lc rgb '#6165' lw 0.200001
set object 138 polygon from \
  -13.5404, 0.855666 to \
  -13.4398, 0.993958 to \
  26.7281, 56.0241 to \
  -13.5399, 0.655609 to \
  -14.0184, 0 to \
  -14.1604, 0 to \
  -13.5404, 0.855666 front fs empty border lc rgb '#6165' lw 0.200001
set object 139 polygon from \
  -13.6385, 0.719771 to \
  -13.5379, 0.85907 to \
  26.6305, 56.2916 to \
  -13.638, 0.519717 to \
  -14.0146, 0 to \
  -14.1563, 0 to \
  -13.6385, 0.719771 front fs empty border lc rgb '#6165' lw 0.200001
set object 140 polygon from \
  -13.7366, 0.582889 to \
  -13.636, 0.7232 to \
  26.5329, 56.558 to \
  -13.7361, 0.38285 to \
  -14.0115, 0 to \
  -14.1529, 0 to \
  -13.7366, 0.582889 front fs empty border lc rgb '#6165' lw 0.200001
set object 141 polygon from \
  -13.8347, 0.445028 to \
  -13.7341, 0.586347 to \
  26.4352, 56.8235 to \
  -13.8342, 0.244995 to \
  -14.0092, 0 to \
  -14.1503, 0 to \
  -13.8347, 0.445028 front fs empty border lc rgb '#6165' lw 0.200001
set object 142 polygon from \
  -13.9328, 0.306187 to \
  -13.8322, 0.448516 to \
  26.3375, 57.088 to \
  -13.9323, 0.106162 to \
  -14.0076, 0 to \
  -14.1484, 0 to \
  -13.9328, 0.306187 front fs empty border lc rgb '#6165' lw 0.200001
set object 143 polygon from \
  -14.0309, 0.166364 to \
  -13.9303, 0.309704 to \
  26.24, 57.3516 to \
  -14.0068, 0 to \
  -14.1472, 0 to \
  -14.0309, 0.166364 front fs empty border lc rgb '#6165' lw 0.200001
set object 144 polygon from \
  -14.129, 0.0255596 to \
  -14.0284, 0.169912 to \
  26.1421, 57.6139 to \
  -14.0069, 0 to \
  -14.1468, 0 to \
  -14.129, 0.0255596 front fs empty border lc rgb '#6165' lw 0.200001
set object 145 polygon from \
  -14.1265, 0.0291362 to \
  26.0445, 57.8755 to \
  -14.0077, 0 to \
  -14.1467, 0 to \
  -14.1265, 0.0291362 front fs empty border lc rgb '#6165' lw 0.200001
set object 146 polygon from \
  25.9467, 58.1359 to \
  -14.0092, 0 to \
  -14.1469, 0 to \
  25.9467, 58.1359 front fs empty border lc rgb '#6165' lw 0.200001
set object 147 polygon from \
  25.8491, 58.3957 to \
  -14.0114, 0 to \
  -14.1478, 0 to \
  25.8491, 58.3957 front fs empty border lc rgb '#6165' lw 0.200001
set object 148 polygon from \
  25.7515, 58.6543 to \
  -14.0142, 0 to \
  -14.1493, 0 to \
  25.7515, 58.6543 front fs empty border lc rgb '#6165' lw 0.200001
set object 149 polygon from \
  25.6538, 58.9119 to \
  -14.0175, 0 to \
  -14.1515, 0 to \
  25.6538, 58.9119 front fs empty border lc rgb '#6165' lw 0.200001
set object 150 polygon from \
  25.556, 59.1685 to \
  -14.0216, 0 to \
  -14.1543, 0 to \
  25.556, 59.1685 front fs empty border lc rgb '#6165' lw 0.200001
set object 151 polygon from \
  25.4582, 59.4239 to \
  -14.0262, 0 to \
  -14.1577, 0 to \
  25.4582, 59.4239 front fs empty border lc rgb '#6165' lw 0.200001
set object 152 polygon from \
  25.3606, 59.6788 to \
  -14.0314, 0 to \
  -14.1617, 0 to \
  25.3606, 59.6788 front fs empty border lc rgb '#6165' lw 0.200001
set object 153 polygon from \
  25.2631, 59.9329 to \
  -14.0371, 0 to \
  -14.1663, 0 to \
  25.2631, 59.9329 front fs empty border lc rgb '#6165' lw 0.200001
set object 154 polygon from \
  25.1654, 60.1856 to \
  -14.0435, 0 to \
  -14.1715, 0 to \
  25.1654, 60.1856 front fs empty border lc rgb '#6165' lw 0.200001
set object 155 polygon from \
  25.0677, 60.4374 to \
  -14.0503, 0 to \
  -14.1773, 0 to \
  25.0677, 60.4374 front fs empty border lc rgb '#6165' lw 0.200001
set object 156 polygon from \
  24.97, 60.6882 to \
  -14.0578, 0 to \
  -14.1836, 0 to \
  24.97, 60.6882 front fs empty border lc rgb '#6165' lw 0.200001
set object 157 polygon from \
  24.8723, 60.9379 to \
  -14.0657, 0 to \
  -14.1905, 0 to \
  24.8723, 60.9379 front fs empty border lc rgb '#6165' lw 0.200001
set object 158 polygon from \
  24.7744, 61.1865 to \
  -14.0742, 0 to \
  -14.1979, 0 to \
  24.7744, 61.1865 front fs empty border lc rgb '#6165' lw 0.200001
set object 159 polygon from \
  24.6767, 61.4344 to \
  -14.0832, 0 to \
  -14.2058, 0 to \
  24.6767, 61.4344 front fs empty border lc rgb '#6165' lw 0.200001
set object 160 polygon from \
  24.5791, 61.6815 to \
  -14.0927, 0 to \
  -14.2142, 0 to \
  24.5791, 61.6815 front fs empty border lc rgb '#6165' lw 0.200001
set object 161 polygon from \
  24.4812, 61.9271 to \
  -14.1027, 0 to \
  -14.2232, 0 to \
  24.4812, 61.9271 front fs empty border lc rgb '#6165' lw 0.200001
set object 162 polygon from \
  24.3835, 62.1721 to \
  -14.1132, 0 to \
  -14.2326, 0 to \
  24.3835, 62.1721 front fs empty border lc rgb '#6165' lw 0.200001
set object 163 polygon from \
  24.2861, 62.4165 to \
  -14.1241, 0 to \
  -14.2426, 0 to \
  24.2861, 62.4165 front fs empty border lc rgb '#6165' lw 0.200001
set object 164 polygon from \
  24.1885, 62.6599 to \
  -14.1355, 0 to \
  -14.253, 0 to \
  24.1885, 62.6599 front fs empty border lc rgb '#6165' lw 0.200001
set object 165 polygon from \
  24.0911, 62.9023 to \
  -14.1474, 0 to \
  -14.2639, 0 to \
  24.0911, 62.9023 front fs empty border lc rgb '#6165' lw 0.200001
set object 166 polygon from \
  23.9937, 63.1439 to \
  -14.1597, 0 to \
  -14.2752, 0 to \
  23.9937, 63.1439 front fs empty border lc rgb '#6165' lw 0.200001
set object 167 polygon from \
  23.8962, 63.3843 to \
  -14.1725, 0 to \
  -14.2871, 0 to \
  23.8962, 63.3843 front fs empty border lc rgb '#6165' lw 0.200001
set object 168 polygon from \
  23.7985, 63.6236 to \
  -14.1857, 0 to \
  -14.2993, 0 to \
  23.7985, 63.6236 front fs empty border lc rgb '#6165' lw 0.200001
set object 169 polygon from \
  23.701, 63.862 to \
  -14.1993, 0 to \
  -14.312, 0 to \
  23.701, 63.862 front fs empty border lc rgb '#6165' lw 0.200001
set object 170 polygon from \
  23.6035, 64.0994 to \
  -14.2133, 0 to \
  -14.3251, 0 to \
  23.6035, 64.0994 front fs empty border lc rgb '#6165' lw 0.200001
set object 171 polygon from \
  23.5056, 64.3354 to \
  -14.2278, 0 to \
  -14.3387, 0 to \
  23.5056, 64.3354 front fs empty border lc rgb '#6165' lw 0.200001
set object 172 polygon from \
  23.408, 64.5707 to \
  -14.2426, 0 to \
  -14.3526, 0 to \
  23.408, 64.5707 front fs empty border lc rgb '#6165' lw 0.200001
set object 173 polygon from \
  23.3104, 64.8053 to \
  -14.2579, 0 to \
  -14.367, 0 to \
  23.3104, 64.8053 front fs empty border lc rgb '#6165' lw 0.200001
set object 174 polygon from \
  23.2129, 65.0389 to \
  -14.2735, 0 to \
  -14.3818, 0 to \
  23.2129, 65.0389 front fs empty border lc rgb '#6165' lw 0.200001
set object 175 polygon from \
  23.1153, 65.2715 to \
  -14.2895, 0 to \
  -14.3969, 0 to \
  23.1153, 65.2715 front fs empty border lc rgb '#6165' lw 0.200001
set object 176 polygon from \
  23.0177, 65.5029 to \
  -14.3059, 0 to \
  -14.4125, 0 to \
  23.0177, 65.5029 front fs empty border lc rgb '#6165' lw 0.200001
set object 177 polygon from \
  22.9201, 65.7336 to \
  -14.3227, 0 to \
  -14.4284, 0 to \
  22.9201, 65.7336 front fs empty border lc rgb '#6165' lw 0.200001
set object 178 polygon from \
  22.8224, 65.963 to \
  -14.3398, 0 to \
  -14.4447, 0 to \
  22.8224, 65.963 front fs empty border lc rgb '#6165' lw 0.200001
set object 179 polygon from \
  22.7248, 66.1915 to \
  -14.3573, 0 to \
  -14.4614, 0 to \
  22.7248, 66.1915 front fs empty border lc rgb '#6165' lw 0.200001
set object 180 polygon from \
  22.6273, 66.4194 to \
  -14.3752, 0 to \
  -14.4784, 0 to \
  22.6273, 66.4194 front fs empty border lc rgb '#6165' lw 0.200001
set object 181 polygon from \
  22.5296, 66.6459 to \
  -14.3934, 0 to \
  -14.4958, 0 to \
  22.5296, 66.6459 front fs empty border lc rgb '#6165' lw 0.200001
set object 182 polygon from \
  22.4323, 66.8722 to \
  -14.4119, 0 to \
  -14.5136, 0 to \
  22.4323, 66.8722 front fs empty border lc rgb '#6165' lw 0.200001
set object 183 polygon from \
  22.3351, 67.0976 to \
  -14.4308, 0 to \
  -14.5317, 0 to \
  22.3351, 67.0976 front fs empty border lc rgb '#6165' lw 0.200001
set object 184 polygon from \
  22.2377, 67.3217 to \
  -14.4499, 0 to \
  -14.5501, 0 to \
  22.2377, 67.3217 front fs empty border lc rgb '#6165' lw 0.200001
set object 185 polygon from \
  22.1399, 67.5443 to \
  -14.4695, 0 to \
  -14.5688, 0 to \
  22.1399, 67.5443 front fs empty border lc rgb '#6165' lw 0.200001
set object 186 polygon from \
  22.0424, 67.7663 to \
  -14.4893, 0 to \
  -14.5879, 0 to \
  22.0424, 67.7663 front fs empty border lc rgb '#6165' lw 0.200001
set object 187 polygon from \
  21.9448, 67.9872 to \
  -14.5094, 0 to \
  -14.6073, 0 to \
  21.9448, 67.9872 front fs empty border lc rgb '#6165' lw 0.200001
set object 188 polygon from \
  21.847, 68.2067 to \
  -14.5299, 0 to \
  -14.627, 0 to \
  21.847, 68.2067 front fs empty border lc rgb '#6165' lw 0.200001
set object 189 polygon from \
  21.7494, 68.4255 to \
  -14.5506, 0 to \
  -14.6471, 0 to \
  21.7494, 68.4255 front fs empty border lc rgb '#6165' lw 0.200001
set object 190 polygon from \
  21.652, 68.6439 to \
  -14.5717, 0 to \
  -14.6674, 0 to \
  21.652, 68.6439 front fs empty border lc rgb '#6165' lw 0.200001
set object 191 polygon from \
  21.5548, 68.8616 to \
  -14.5931, 0 to \
  -14.6881, 0 to \
  21.5548, 68.8616 front fs empty border lc rgb '#6165' lw 0.200001
set object 192 polygon from \
  21.4572, 69.0777 to \
  -14.6147, 0 to \
  -14.709, 0 to \
  21.4572, 69.0777 front fs empty border lc rgb '#6165' lw 0.200001
set object 193 polygon from \
  21.3599, 69.2933 to \
  -14.6366, 0 to \
  -14.7302, 0 to \
  21.3599, 69.2933 front fs empty border lc rgb '#6165' lw 0.200001
set object 194 polygon from \
  21.2625, 69.5077 to \
  -14.6588, 0 to \
  -14.7518, 0 to \
  21.2625, 69.5077 front fs empty border lc rgb '#6165' lw 0.200001
set object 195 polygon from \
  21.1654, 69.7217 to \
  -14.6813, 0 to \
  -14.7736, 0 to \
  21.1654, 69.7217 front fs empty border lc rgb '#6165' lw 0.200001
set object 196 polygon from \
  21.0678, 69.9339 to \
  -14.7041, 0 to \
  -14.7957, 0 to \
  21.0678, 69.9339 front fs empty border lc rgb '#6165' lw 0.200001
set object 197 polygon from \
  20.9704, 70.1455 to \
  -14.7271, 0 to \
  -14.818, 0 to \
  20.9704, 70.1455 front fs empty border lc rgb '#6165' lw 0.200001
set object 198 polygon from \
  20.8731, 70.3563 to \
  -14.7504, 0 to \
  -14.8407, 0 to \
  20.8731, 70.3563 front fs empty border lc rgb '#6165' lw 0.200001
set object 199 polygon from \
  20.7756, 70.5658 to \
  -14.7739, 0 to \
  -14.8636, 0 to \
  20.7756, 70.5658 front fs empty border lc rgb '#6165' lw 0.200001
set object 200 polygon from \
  20.6781, 70.7741 to \
  -14.7977, 0 to \
  -14.8867, 0 to \
  20.6781, 70.7741 front fs empty border lc rgb '#6165' lw 0.200001
set object 201 polygon from \
  20.5806, 70.9816 to \
  -14.8218, 0 to \
  -14.9101, 0 to \
  20.5806, 70.9816 front fs empty border lc rgb '#6165' lw 0.200001
set object 202 polygon from \
  20.4832, 71.1884 to \
  -14.8461, 0 to \
  -14.9338, 0 to \
  20.4832, 71.1884 front fs empty border lc rgb '#6165' lw 0.200001
set object 203 polygon from \
  20.3856, 71.3937 to \
  -14.8706, 0 to \
  -14.9577, 0 to \
  20.3856, 71.3937 front fs empty border lc rgb '#6165' lw 0.200001
set object 204 polygon from \
  20.2885, 71.5991 to \
  -14.8954, 0 to \
  -14.9819, 0 to \
  20.2885, 71.5991 front fs empty border lc rgb '#6165' lw 0.200001
set object 205 polygon from \
  20.1911, 71.8029 to \
  -14.9204, 0 to \
  -15.0063, 0 to \
  20.1911, 71.8029 front fs empty border lc rgb '#6165' lw 0.200001
set object 206 polygon from \
  20.0936, 72.0056 to \
  -14.9457, 0 to \
  -15.031, 0 to \
  20.0936, 72.0056 front fs empty border lc rgb '#6165' lw 0.200001
set object 207 polygon from \
  19.996, 72.207 to \
  -14.9711, 0 to \
  -15.0559, 0 to \
  19.996, 72.207 front fs empty border lc rgb '#6165' lw 0.200001
set object 208 polygon from \
  19.8982, 72.4072 to \
  -14.9969, 0 to \
  -15.081, 0 to \
  19.8982, 72.4072 front fs empty border lc rgb '#6165' lw 0.200001
set object 209 polygon from \
  19.8009, 72.6074 to \
  -15.0228, 0 to \
  -15.1064, 0 to \
  19.8009, 72.6074 front fs empty border lc rgb '#6165' lw 0.200001
set object 210 polygon from \
  19.704, 72.8073 to \
  -15.049, 0 to \
  -15.132, 0 to \
  19.704, 72.8073 front fs empty border lc rgb '#6165' lw 0.200001
set object 211 polygon from \
  19.6063, 73.0047 to \
  -15.0753, 0 to \
  -15.1578, 0 to \
  19.6063, 73.0047 front fs empty border lc rgb '#6165' lw 0.200001
set object 212 polygon from \
  19.5092, 73.2025 to \
  -15.1019, 0 to \
  -15.1838, 0 to \
  19.5092, 73.2025 front fs empty border lc rgb '#6165' lw 0.200001
set object 213 polygon from \
  19.4119, 73.3987 to \
  -15.1287, 0 to \
  -15.2101, 0 to \
  19.4119, 73.3987 front fs empty border lc rgb '#6165' lw 0.200001
set object 214 polygon from \
  19.3146, 73.5941 to \
  -15.1557, 0 to \
  -15.2365, 0 to \
  19.3146, 73.5941 front fs empty border lc rgb '#6165' lw 0.200001
set object 215 polygon from \
  19.2176, 73.789 to \
  -15.1829, 0 to \
  -15.2632, 0 to \
  19.2176, 73.789 front fs empty border lc rgb '#6165' lw 0.200001
set object 216 polygon from \
  19.12, 73.9819 to \
  -15.2104, 0 to \
  -15.2901, 0 to \
  19.12, 73.9819 front fs empty border lc rgb '#6165' lw 0.200001
set object 217 polygon from \
  19.0224, 74.1736 to \
  -15.238, 0 to \
  -15.3172, 0 to \
  19.0224, 74.1736 front fs empty border lc rgb '#6165' lw 0.200001
set object 218 polygon from \
  18.9251, 74.365 to \
  -15.2658, 0 to \
  -15.3444, 0 to \
  18.9251, 74.365 front fs empty border lc rgb '#6165' lw 0.200001
set object 219 polygon from \
  18.8277, 74.5554 to \
  -15.2938, 0 to \
  -15.3719, 0 to \
  18.8277, 74.5554 front fs empty border lc rgb '#6165' lw 0.200001
set object 220 polygon from \
  18.7302, 74.7445 to \
  -15.322, 0 to \
  -15.3996, 0 to \
  18.7302, 74.7445 front fs empty border lc rgb '#6165' lw 0.200001
set object 221 polygon from \
  18.6333, 74.934 to \
  -15.3504, 0 to \
  -15.4275, 0 to \
  18.6333, 74.934 front fs empty border lc rgb '#6165' lw 0.200001
set object 222 polygon from \
  18.5359, 75.1213 to \
  -15.379, 0 to \
  -15.4556, 0 to \
  18.5359, 75.1213 front fs empty border lc rgb '#6165' lw 0.200001
set object 223 polygon from \
  18.4388, 75.3084 to \
  -15.4077, 0 to \
  -15.4838, 0 to \
  18.4388, 75.3084 front fs empty border lc rgb '#6165' lw 0.200001
set object 224 polygon from \
  18.3412, 75.4935 to \
  -15.4367, 0 to \
  -15.5123, 0 to \
  18.3412, 75.4935 front fs empty border lc rgb '#6165' lw 0.200001
set object 225 polygon from \
  18.244, 75.6785 to \
  -15.4658, 0 to \
  -15.5409, 0 to \
  18.244, 75.6785 front fs empty border lc rgb '#6165' lw 0.200001
set object 226 polygon from \
  18.1467, 75.8621 to \
  -15.4951, 0 to \
  -15.5697, 0 to \
  18.1467, 75.8621 front fs empty border lc rgb '#6165' lw 0.200001
set object 227 polygon from \
  18.0495, 76.0451 to \
  -15.5246, 0 to \
  -15.5987, 0 to \
  18.0495, 76.0451 front fs empty border lc rgb '#6165' lw 0.200001
set object 228 polygon from \
  17.9521, 76.2268 to \
  -15.5542, 0 to \
  -15.6279, 0 to \
  17.9521, 76.2268 front fs empty border lc rgb '#6165' lw 0.200001
set object 229 polygon from \
  17.8549, 76.4079 to \
  -15.584, 0 to \
  -15.6572, 0 to \
  17.8549, 76.4079 front fs empty border lc rgb '#6165' lw 0.200001
set object 230 polygon from \
  17.7576, 76.5876 to \
  -15.614, 0 to \
  -15.6867, 0 to \
  17.7576, 76.5876 front fs empty border lc rgb '#6165' lw 0.200001
set object 231 polygon from \
  17.6601, 76.7663 to \
  -15.6441, 0 to \
  -15.7164, 0 to \
  17.6601, 76.7663 front fs empty border lc rgb '#6165' lw 0.200001
set object 232 polygon from \
  17.5633, 76.9452 to \
  -15.6745, 0 to \
  -15.7463, 0 to \
  17.5633, 76.9452 front fs empty border lc rgb '#6165' lw 0.200001
set object 233 polygon from \
  17.4661, 77.1225 to \
  -15.7049, 0 to \
  -15.7763, 0 to \
  17.4661, 77.1225 front fs empty border lc rgb '#6165' lw 0.200001
set object 234 polygon from \
  17.3687, 77.2983 to \
  -15.7356, 0 to \
  -15.8065, 0 to \
  17.3687, 77.2983 front fs empty border lc rgb '#6165' lw 0.200001
set object 235 polygon from \
  17.2714, 77.4734 to \
  -15.7663, 0 to \
  -15.8368, 0 to \
  17.2714, 77.4734 front fs empty border lc rgb '#6165' lw 0.200001
set object 236 polygon from \
  17.1747, 77.6489 to \
  -15.7973, 0 to \
  -15.8673, 0 to \
  17.1747, 77.6489 front fs empty border lc rgb '#6165' lw 0.200001
set object 237 polygon from \
  17.0775, 77.8223 to \
  -15.8284, 0 to \
  -15.898, 0 to \
  17.0775, 77.8223 front fs empty border lc rgb '#6165' lw 0.200001
set object 238 polygon from \
  16.98, 77.9941 to \
  -15.8596, 0 to \
  -15.9288, 0 to \
  16.98, 77.9941 front fs empty border lc rgb '#6165' lw 0.200001
set object 239 polygon from \
  16.8826, 78.1649 to \
  -15.891, 0 to \
  -15.9597, 0 to \
  16.8826, 78.1649 front fs empty border lc rgb '#6165' lw 0.200001
set object 240 polygon from \
  16.7853, 78.3352 to \
  -15.9226, 0 to \
  -15.9908, 0 to \
  16.7853, 78.3352 front fs empty border lc rgb '#6165' lw 0.200001
set object 241 polygon from \
  16.6877, 78.5038 to \
  -15.9543, 0 to \
  -16.0221, 0 to \
  16.6877, 78.5038 front fs empty border lc rgb '#6165' lw 0.200001
set object 242 polygon from \
  16.5905, 78.6722 to \
  -15.9861, 0 to \
  -16.0535, 0 to \
  16.5905, 78.6722 front fs empty border lc rgb '#6165' lw 0.200001
set object 243 polygon from \
  16.4931, 78.8395 to \
  -16.0181, 0 to \
  -16.0851, 0 to \
  16.4931, 78.8395 front fs empty border lc rgb '#6165' lw 0.200001
set object 244 polygon from \
  16.396, 79.0064 to \
  -16.0502, 0 to \
  -16.1168, 0 to \
  16.396, 79.0064 front fs empty border lc rgb '#6165' lw 0.200001
set object 245 polygon from \
  16.2991, 79.1727 to \
  -16.0824, 0 to \
  -16.1486, 0 to \
  16.2991, 79.1727 front fs empty border lc rgb '#6165' lw 0.200001
set object 246 polygon from \
  16.2017, 79.337 to \
  -16.1148, 0 to \
  -16.1806, 0 to \
  16.2017, 79.337 front fs empty border lc rgb '#6165' lw 0.200001
set object 247 polygon from \
  16.1043, 79.5001 to \
  -16.1474, 0 to \
  -16.2128, 0 to \
  16.1043, 79.5001 front fs empty border lc rgb '#6165' lw 0.200001
set object 248 polygon from \
  16.0072, 79.6633 to \
  -16.18, 0 to \
  -16.245, 0 to \
  16.0072, 79.6633 front fs empty border lc rgb '#6165' lw 0.200001
set object 249 polygon from \
  15.9097, 79.8244 to \
  -16.2128, 0 to \
  -16.2774, 0 to \
  15.9097, 79.8244 front fs empty border lc rgb '#6165' lw 0.200001
set object 250 polygon from \
  15.8127, 79.9857 to \
  -16.2457, 0 to \
  -16.3099, 0 to \
  15.8127, 79.9857 front fs empty border lc rgb '#6165' lw 0.200001
set object 251 polygon from \
  15.7152, 80.1447 to \
  -16.2788, 0 to \
  -16.3426, 0 to \
  15.7152, 80.1447 front fs empty border lc rgb '#6165' lw 0.200001
set object 252 polygon from \
  15.6179, 80.3036 to \
  -16.312, 0 to \
  -16.3754, 0 to \
  15.6179, 80.3036 front fs empty border lc rgb '#6165' lw 0.200001
set object 253 polygon from \
  15.5207, 80.4613 to \
  -16.3453, 0 to \
  -16.4083, 0 to \
  15.5207, 80.4613 front fs empty border lc rgb '#6165' lw 0.200001
set object 254 polygon from \
  15.4233, 80.6178 to \
  -16.3787, 0 to \
  -16.4414, 0 to \
  15.4233, 80.6178 front fs empty border lc rgb '#6165' lw 0.200001
set object 255 polygon from \
  15.3256, 80.7726 to \
  -16.4122, 0 to \
  -16.4746, 0 to \
  15.3256, 80.7726 front fs empty border lc rgb '#6165' lw 0.200001
set object 256 polygon from \
  15.2284, 80.9276 to \
  -16.4459, 0 to \
  -16.5079, 0 to \
  15.2284, 80.9276 front fs empty border lc rgb '#6165' lw 0.200001
set object 257 polygon from \
  15.1319, 81.0836 to \
  -16.4797, 0 to \
  -16.5413, 0 to \
  15.1319, 81.0836 front fs empty border lc rgb '#6165' lw 0.200001
set object 258 polygon from \
  15.0347, 81.2369 to \
  -16.5136, 0 to \
  -16.5748, 0 to \
  15.0347, 81.2369 front fs empty border lc rgb '#6165' lw 0.200001
set object 259 polygon from \
  14.9375, 81.389 to \
  -16.5476, 0 to \
  -16.6085, 0 to \
  14.9375, 81.389 front fs empty border lc rgb '#6165' lw 0.200001
set object 260 polygon from \
  14.8404, 81.5404 to \
  -16.5818, 0 to \
  -16.6423, 0 to \
  14.8404, 81.5404 front fs empty border lc rgb '#6165' lw 0.200001
set object 261 polygon from \
  14.7433, 81.6911 to \
  -16.616, 0 to \
  -16.6762, 0 to \
  14.7433, 81.6911 front fs empty border lc rgb '#6165' lw 0.200001
set object 262 polygon from \
  14.6468, 81.8422 to \
  -16.6504, 0 to \
  -16.7102, 0 to \
  14.6468, 81.8422 front fs empty border lc rgb '#6165' lw 0.200001
set object 263 polygon from \
  14.5499, 81.9913 to \
  -16.6849, 0 to \
  -16.7443, 0 to \
  14.5499, 81.9913 front fs empty border lc rgb '#6165' lw 0.200001
set object 264 polygon from \
  14.453, 82.1393 to \
  -16.7195, 0 to \
  -16.7786, 0 to \
  14.453, 82.1393 front fs empty border lc rgb '#6165' lw 0.200001
set object 265 polygon from \
  14.3557, 82.2854 to \
  -16.7542, 0 to \
  -16.8129, 0 to \
  14.3557, 82.2854 front fs empty border lc rgb '#6165' lw 0.200001
set object 266 polygon from \
  14.2582, 82.4301 to \
  -16.789, 0 to \
  -16.8474, 0 to \
  14.2582, 82.4301 front fs empty border lc rgb '#6165' lw 0.200001
set object 267 polygon from \
  14.1607, 82.574 to \
  -16.8239, 0 to \
  -16.882, 0 to \
  14.1607, 82.574 front fs empty border lc rgb '#6165' lw 0.200001
set object 268 polygon from \
  14.0636, 82.7176 to \
  -16.8589, 0 to \
  -16.9167, 0 to \
  14.0636, 82.7176 front fs empty border lc rgb '#6165' lw 0.200001
set object 269 polygon from \
  13.9669, 82.8616 to \
  -16.8941, 0 to \
  -16.9515, 0 to \
  13.9669, 82.8616 front fs empty border lc rgb '#6165' lw 0.200001
set object 270 polygon from \
  13.87, 83.0039 to \
  -16.9293, 0 to \
  -16.9864, 0 to \
  13.87, 83.0039 front fs empty border lc rgb '#6165' lw 0.200001
set object 271 polygon from \
  13.7731, 83.1455 to \
  -16.9646, 0 to \
  -17.0214, 0 to \
  13.7731, 83.1455 front fs empty border lc rgb '#6165' lw 0.200001
set object 272 polygon from \
  13.6762, 83.286 to \
  -17.0001, 0 to \
  -17.0565, 0 to \
  13.6762, 83.286 front fs empty border lc rgb '#6165' lw 0.200001
set object 273 polygon from \
  13.5799, 83.427 to \
  -17.0356, 0 to \
  -17.0917, 0 to \
  13.5799, 83.427 front fs empty border lc rgb '#6165' lw 0.200001
set object 274 polygon from \
  13.4825, 83.5644 to \
  -17.0712, 0 to \
  -17.127, 0 to \
  13.4825, 83.5644 front fs empty border lc rgb '#6165' lw 0.200001
set object 275 polygon from \
  13.3854, 83.7013 to \
  -17.107, 0 to \
  -17.1624, 0 to \
  13.3854, 83.7013 front fs empty border lc rgb '#6165' lw 0.200001
set object 276 polygon from \
  13.2885, 83.838 to \
  -17.1428, 0 to \
  -17.1979, 0 to \
  13.2885, 83.838 front fs empty border lc rgb '#6165' lw 0.200001
set object 277 polygon from \
  13.1911, 83.9724 to \
  -17.1787, 0 to \
  -17.2336, 0 to \
  13.1911, 83.9724 front fs empty border lc rgb '#6165' lw 0.200001
set object 278 polygon from \
  13.0941, 84.1069 to \
  -17.2147, 0 to \
  -17.2693, 0 to \
  13.0941, 84.1069 front fs empty border lc rgb '#6165' lw 0.200001
set object 279 polygon from \
  12.9971, 84.2404 to \
  -17.2508, 0 to \
  -17.3051, 0 to \
  12.9971, 84.2404 front fs empty border lc rgb '#6165' lw 0.200001
set object 280 polygon from \
  12.8998, 84.3721 to \
  -17.2871, 0 to \
  -17.341, 0 to \
  12.8998, 84.3721 front fs empty border lc rgb '#6165' lw 0.200001
set object 281 polygon from \
  12.8029, 84.5039 to \
  -17.3233, 0 to \
  -17.377, 0 to \
  12.8029, 84.5039 front fs empty border lc rgb '#6165' lw 0.200001
set object 282 polygon from \
  12.705, 84.6321 to \
  -17.3597, 0 to \
  -17.413, 0 to \
  12.705, 84.6321 front fs empty border lc rgb '#6165' lw 0.200001
set object 283 polygon from \
  12.6085, 84.7631 to \
  -17.3962, 0 to \
  -17.4492, 0 to \
  12.6085, 84.7631 front fs empty border lc rgb '#6165' lw 0.200001
set object 284 polygon from \
  12.5117, 84.8924 to \
  -17.4328, 0 to \
  -17.4855, 0 to \
  12.5117, 84.8924 front fs empty border lc rgb '#6165' lw 0.200001
set object 285 polygon from \
  12.4153, 85.0218 to \
  -17.4694, 0 to \
  -17.5218, 0 to \
  12.4153, 85.0218 front fs empty border lc rgb '#6165' lw 0.200001
set object 286 polygon from \
  12.3182, 85.1483 to \
  -17.5062, 0 to \
  -17.5583, 0 to \
  12.3182, 85.1483 front fs empty border lc rgb '#6165' lw 0.200001
set object 287 polygon from \
  12.221, 85.2737 to \
  -17.543, 0 to \
  -17.5948, 0 to \
  12.221, 85.2737 front fs empty border lc rgb '#6165' lw 0.200001
set object 288 polygon from \
  12.1238, 85.3981 to \
  -17.5799, 0 to \
  -17.6315, 0 to \
  12.1238, 85.3981 front fs empty border lc rgb '#6165' lw 0.200001
set object 289 polygon from \
  12.0267, 85.5216 to \
  -17.6169, 0 to \
  -17.6682, 0 to \
  12.0267, 85.5216 front fs empty border lc rgb '#6165' lw 0.200001
set object 290 polygon from \
  11.9303, 85.6462 to \
  -17.654, 0 to \
  -17.705, 0 to \
  11.9303, 85.6462 front fs empty border lc rgb '#6165' lw 0.200001
set object 291 polygon from \
  11.8335, 85.7687 to \
  -17.6911, 0 to \
  -17.7418, 0 to \
  11.8335, 85.7687 front fs empty border lc rgb '#6165' lw 0.200001
set object 292 polygon from \
  11.7369, 85.891 to \
  -17.7284, 0 to \
  -17.7788, 0 to \
  11.7369, 85.891 front fs empty border lc rgb '#6165' lw 0.200001
set object 293 polygon from \
  11.6397, 86.0106 to \
  -17.7657, 0 to \
  -17.8158, 0 to \
  11.6397, 86.0106 front fs empty border lc rgb '#6165' lw 0.200001
set object 294 polygon from \
  11.5432, 86.1311 to \
  -17.8031, 0 to \
  -17.853, 0 to \
  11.5432, 86.1311 front fs empty border lc rgb '#6165' lw 0.200001
set object 295 polygon from \
  11.4465, 86.2501 to \
  -17.8406, 0 to \
  -17.8902, 0 to \
  11.4465, 86.2501 front fs empty border lc rgb '#6165' lw 0.200001
set object 296 polygon from \
  11.3493, 86.3669 to \
  -17.8781, 0 to \
  -17.9275, 0 to \
  11.3493, 86.3669 front fs empty border lc rgb '#6165' lw 0.200001
set object 297 polygon from \
  11.2521, 86.4824 to \
  -17.9158, 0 to \
  -17.9648, 0 to \
  11.2521, 86.4824 front fs empty border lc rgb '#6165' lw 0.200001
set object 298 polygon from \
  11.1554, 86.5987 to \
  -17.9535, 0 to \
  -18.0023, 0 to \
  11.1554, 86.5987 front fs empty border lc rgb '#6165' lw 0.200001
set object 299 polygon from \
  11.0585, 86.7132 to \
  -17.9913, 0 to \
  -18.0398, 0 to \
  11.0585, 86.7132 front fs empty border lc rgb '#6165' lw 0.200001
set object 300 polygon from \
  10.9619, 86.8279 to \
  -18.0291, 0 to \
  -18.0774, 0 to \
  10.9619, 86.8279 front fs empty border lc rgb '#6165' lw 0.200001
set object 301 polygon from \
  18.2251, 0.183111 to \
  18.2253, 0.183111 to \
  18.3234, 0.000368285 to \
  18.3234, 0 to \
  10.5047, 0 to \
  10.4063, 0.104923 to \
  18.2251, 0.183111 front fs empty border lc rgb '#6165' lw 0.200001
set object 302 polygon from \
  18.127, 0.364871 to \
  18.1272, 0.364873 to \
  18.2253, 0.183112 to \
  18.2253, 0.182744 to \
  10.4066, 0.104556 to \
  10.3082, 0.208494 to \
  18.127, 0.364871 front fs empty border lc rgb '#6165' lw 0.200001
set object 303 polygon from \
  18.0289, 0.54565 to \
  18.0291, 0.545655 to \
  18.1272, 0.364874 to \
  18.1272, 0.364506 to \
  10.3085, 0.208131 to \
  10.2101, 0.311085 to \
  18.0289, 0.54565 front fs empty border lc rgb '#6165' lw 0.200001
set object 304 polygon from \
  17.9308, 0.725448 to \
  17.931, 0.725455 to \
  18.0291, 0.545655 to \
  18.0291, 0.545288 to \
  10.2104, 0.310725 to \
  10.112, 0.412694 to \
  17.9308, 0.725448 front fs empty border lc rgb '#6165' lw 0.200001
set object 305 polygon from \
  17.8327, 0.904265 to \
  17.8329, 0.904274 to \
  17.931, 0.725455 to \
  17.931, 0.725088 to \
  10.1123, 0.412338 to \
  10.0139, 0.513323 to \
  17.8327, 0.904265 front fs empty border lc rgb '#6165' lw 0.200001
set object 306 polygon from \
  17.7346, 1.08211 to \
  17.7348, 1.08212 to \
  17.8329, 0.904274 to \
  17.8329, 0.903907 to \
  10.0142, 0.51297 to \
  9.91571, 0.612971 to \
  17.7346, 1.08211 front fs empty border lc rgb '#6165' lw 0.200001
set object 307 polygon from \
  17.6365, 1.25896 to \
  17.6367, 1.25897 to \
  17.7348, 1.08212 to \
  17.7348, 1.08175 to \
  9.91605, 0.612621 to \
  9.81761, 0.711637 to \
  17.6365, 1.25896 front fs empty border lc rgb '#6165' lw 0.200001
set object 308 polygon from \
  17.5384, 1.43483 to \
  17.5386, 1.43485 to \
  17.6367, 1.25897 to \
  17.6367, 1.25861 to \
  9.81795, 0.711291 to \
  9.71951, 0.809323 to \
  17.5384, 1.43483 front fs empty border lc rgb '#6165' lw 0.200001
set object 309 polygon from \
  17.4403, 1.60973 to \
  17.4405, 1.60975 to \
  17.5386, 1.43485 to \
  17.5386, 1.43448 to \
  9.71985, 0.80898 to \
  9.62141, 0.906027 to \
  17.4403, 1.60973 front fs empty border lc rgb '#6165' lw 0.200001
set object 310 polygon from \
  17.3422, 1.78364 to \
  17.3424, 1.78366 to \
  17.4405, 1.60975 to \
  17.4405, 1.60938 to \
  9.62175, 0.905688 to \
  9.52331, 1.00176 to \
  17.3422, 1.78364 front fs empty border lc rgb '#6165' lw 0.200001
set object 311 polygon from \
  17.2441, 1.95657 to \
  17.2443, 1.95659 to \
  17.3424, 1.78366 to \
  17.3424, 1.78329 to \
  9.52365, 1.00142 to \
  9.42521, 1.0965 to \
  17.2441, 1.95657 front fs empty border lc rgb '#6165' lw 0.200001
set object 312 polygon from \
  17.146, 2.12852 to \
  17.1462, 2.12855 to \
  17.2443, 1.95659 to \
  17.2443, 1.95623 to \
  9.42555, 1.09617 to \
  9.32711, 1.19026 to \
  17.146, 2.12852 front fs empty border lc rgb '#6165' lw 0.200001
set object 313 polygon from \
  17.0479, 2.29949 to \
  17.0481, 2.29952 to \
  17.1462, 2.12855 to \
  17.1462, 2.12818 to \
  9.32745, 1.18993 to \
  9.22901, 1.28304 to \
  17.0479, 2.29949 front fs empty border lc rgb '#6165' lw 0.200001
set object 314 polygon from \
  16.9498, 2.46948 to \
  16.95, 2.46951 to \
  17.0481, 2.29952 to \
  17.0481, 2.29915 to \
  9.22935, 1.28271 to \
  9.13091, 1.37484 to \
  16.9498, 2.46948 front fs empty border lc rgb '#6165' lw 0.200001
set object 315 polygon from \
  16.8517, 2.63848 to \
  16.8519, 2.63852 to \
  16.95, 2.46951 to \
  16.95, 2.46914 to \
  9.13125, 1.37452 to \
  9.03281, 1.46566 to \
  16.8517, 2.63848 front fs empty border lc rgb '#6165' lw 0.200001
set object 316 polygon from \
  16.7536, 2.80651 to \
  16.7538, 2.80655 to \
  16.8519, 2.63852 to \
  16.8519, 2.63815 to \
  9.03315, 1.46534 to \
  8.93471, 1.5555 to \
  16.7536, 2.80651 front fs empty border lc rgb '#6165' lw 0.200001
set object 317 polygon from \
  16.6555, 2.97355 to \
  16.6557, 2.97359 to \
  16.7538, 2.80655 to \
  16.7538, 2.80618 to \
  8.93505, 1.55518 to \
  8.83661, 1.64435 to \
  16.6555, 2.97355 front fs empty border lc rgb '#6165' lw 0.200001
set object 318 polygon from \
  16.5574, 3.13962 to \
  16.5576, 3.13966 to \
  16.6557, 2.97359 to \
  16.6557, 2.97323 to \
  8.83695, 1.64404 to \
  8.73851, 1.73223 to \
  16.5574, 3.13962 front fs empty border lc rgb '#6165' lw 0.200001
set object 319 polygon from \
  16.4593, 3.3047 to \
  16.4595, 3.30475 to \
  16.5576, 3.13966 to \
  16.5576, 3.13929 to \
  8.73885, 1.73192 to \
  8.64041, 1.81912 to \
  16.4593, 3.3047 front fs empty border lc rgb '#6165' lw 0.200001
set object 320 polygon from \
  16.3612, 3.4688 to \
  16.3614, 3.46885 to \
  16.4595, 3.30475 to \
  16.4595, 3.30438 to \
  8.64075, 1.81882 to \
  8.54231, 1.90504 to \
  16.3612, 3.4688 front fs empty border lc rgb '#6165' lw 0.200001
set object 321 polygon from \
  16.2631, 3.63192 to \
  16.2633, 3.63197 to \
  16.3614, 3.46885 to \
  16.3614, 3.46848 to \
  8.54265, 1.90473 to \
  8.44421, 1.98997 to \
  16.2631, 3.63192 front fs empty border lc rgb '#6165' lw 0.200001
set object 322 polygon from \
  16.165, 3.79406 to \
  16.1652, 3.79412 to \
  16.2633, 3.63197 to \
  16.2633, 3.63161 to \
  8.44455, 1.98967 to \
  8.34611, 2.07392 to \
  16.165, 3.79406 front fs empty border lc rgb '#6165' lw 0.200001
set object 323 polygon from \
  16.0669, 3.95522 to \
  16.0671, 3.95528 to \
  16.1652, 3.79412 to \
  16.1652, 3.79375 to \
  8.34645, 2.07363 to \
  8.24801, 2.15689 to \
  16.0669, 3.95522 front fs empty border lc rgb '#6165' lw 0.200001
set object 324 polygon from \
  15.9688, 4.1154 to \
  15.969, 4.11546 to \
  16.0671, 3.95528 to \
  16.0671, 3.95491 to \
  8.24835, 2.1566 to \
  8.14991, 2.23888 to \
  15.9688, 4.1154 front fs empty border lc rgb '#6165' lw 0.200001
set object 325 polygon from \
  15.8707, 4.2746 to \
  15.8709, 4.27466 to \
  15.969, 4.11546 to \
  15.969, 4.11509 to \
  8.15025, 2.23859 to \
  8.05181, 2.31989 to \
  15.8707, 4.2746 front fs empty border lc rgb '#6165' lw 0.200001
set object 326 polygon from \
  15.7726, 4.43281 to \
  15.7728, 4.43288 to \
  15.8709, 4.27466 to \
  15.8709, 4.27429 to \
  8.05215, 2.3196 to \
  7.95371, 2.39992 to \
  15.7726, 4.43281 front fs empty border lc rgb '#6165' lw 0.200001
set object 327 polygon from \
  15.6745, 4.59005 to \
  15.6747, 4.59011 to \
  15.7728, 4.43288 to \
  15.7728, 4.43251 to \
  7.95405, 2.39964 to \
  7.85561, 2.47896 to \
  15.6745, 4.59005 front fs empty border lc rgb '#6165' lw 0.200001
set object 328 polygon from \
  15.5764, 4.7463 to \
  15.5766, 4.74637 to \
  15.6747, 4.59011 to \
  15.6747, 4.58975 to \
  7.85595, 2.47868 to \
  7.75751, 2.55703 to \
  15.5764, 4.7463 front fs empty border lc rgb '#6165' lw 0.200001
set object 329 polygon from \
  15.4783, 4.90158 to \
  15.4785, 4.90164 to \
  15.5766, 4.74637 to \
  15.5766, 4.746 to \
  7.75785, 2.55675 to \
  7.65941, 2.63411 to \
  15.4783, 4.90158 front fs empty border lc rgb '#6165' lw 0.200001
set object 330 polygon from \
  15.3802, 5.05587 to \
  15.3804, 5.05594 to \
  15.4785, 4.90164 to \
  15.4785, 4.90128 to \
  7.65975, 2.63384 to \
  7.56131, 2.71022 to \
  15.3802, 5.05587 front fs empty border lc rgb '#6165' lw 0.200001
set object 331 polygon from \
  15.2821, 5.20918 to \
  15.2823, 5.20925 to \
  15.3804, 5.05594 to \
  15.3804, 5.05557 to \
  7.56165, 2.70995 to \
  7.46321, 2.78534 to \
  15.2821, 5.20918 front fs empty border lc rgb '#6165' lw 0.200001
set object 332 polygon from \
  15.184, 5.36151 to \
  15.1842, 5.36159 to \
  15.2823, 5.20925 to \
  15.2823, 5.20889 to \
  7.46355, 2.78507 to \
  7.36511, 2.85948 to \
  15.184, 5.36151 front fs empty border lc rgb '#6165' lw 0.200001
set object 333 polygon from \
  15.0859, 5.51286 to \
  15.0861, 5.51294 to \
  15.1842, 5.36159 to \
  15.1842, 5.36122 to \
  7.36545, 2.85922 to \
  7.26701, 2.93264 to \
  15.0859, 5.51286 front fs empty border lc rgb '#6165' lw 0.200001
set object 334 polygon from \
  14.9878, 5.66322 to \
  14.988, 5.66331 to \
  15.0861, 5.51294 to \
  15.0861, 5.51257 to \
  7.26735, 2.93238 to \
  7.16891, 3.00482 to \
  14.9878, 5.66322 front fs empty border lc rgb '#6165' lw 0.200001
set object 335 polygon from \
  14.8897, 5.81261 to \
  14.8899, 5.8127 to \
  14.988, 5.66331 to \
  14.988, 5.66294 to \
  7.16925, 3.00457 to \
  7.07081, 3.07602 to \
  14.8897, 5.81261 front fs empty border lc rgb '#6165' lw 0.200001
set object 336 polygon from \
  14.7916, 5.96102 to \
  14.7918, 5.96111 to \
  14.8899, 5.8127 to \
  14.8899, 5.81233 to \
  7.07115, 3.07577 to \
  6.97271, 3.14624 to \
  14.7916, 5.96102 front fs empty border lc rgb '#6165' lw 0.200001
set object 337 polygon from \
  14.6935, 6.10844 to \
  14.6937, 6.10853 to \
  14.7918, 5.96111 to \
  14.7918, 5.96074 to \
  6.97305, 3.14599 to \
  6.87461, 3.21547 to \
  14.6935, 6.10844 front fs empty border lc rgb '#6165' lw 0.200001
set object 338 polygon from \
  14.5954, 6.25489 to \
  14.5956, 6.25498 to \
  14.6937, 6.10853 to \
  14.6937, 6.10817 to \
  6.87495, 3.21523 to \
  6.77651, 3.28373 to \
  14.5954, 6.25489 front fs empty border lc rgb '#6165' lw 0.200001
set object 339 polygon from \
  14.4973, 6.40035 to \
  14.4975, 6.40044 to \
  14.5956, 6.25498 to \
  14.5956, 6.25461 to \
  6.77685, 3.28349 to \
  6.67841, 3.351 to \
  14.4973, 6.40035 front fs empty border lc rgb '#6165' lw 0.200001
set object 340 polygon from \
  14.3992, 6.54483 to \
  14.3994, 6.54493 to \
  14.4975, 6.40045 to \
  14.4975, 6.40008 to \
  6.67875, 3.35077 to \
  6.58031, 3.4173 to \
  14.3992, 6.54483 front fs empty border lc rgb '#6165' lw 0.200001
set object 341 polygon from \
  14.3011, 6.68833 to \
  14.3013, 6.68843 to \
  14.3994, 6.54493 to \
  14.3994, 6.54456 to \
  6.58065, 3.41706 to \
  6.48221, 3.48261 to \
  14.3011, 6.68833 front fs empty border lc rgb '#6165' lw 0.200001
set object 342 polygon from \
  14.203, 6.83085 to \
  14.2032, 6.83096 to \
  14.3013, 6.68843 to \
  14.3013, 6.68806 to \
  6.48255, 3.48238 to \
  6.38411, 3.54694 to \
  14.203, 6.83085 front fs empty border lc rgb '#6165' lw 0.200001
set object 343 polygon from \
  14.1049, 6.97239 to \
  14.1051, 6.9725 to \
  14.2032, 6.83096 to \
  14.2032, 6.83059 to \
  6.38445, 3.54671 to \
  6.28601, 3.61029 to \
  14.1049, 6.97239 front fs empty border lc rgb '#6165' lw 0.200001
set object 344 polygon from \
  14.0068, 7.11295 to \
  14.007, 7.11306 to \
  14.1051, 6.9725 to \
  14.1051, 6.97213 to \
  6.28635, 3.61007 to \
  6.18791, 3.67266 to \
  14.0068, 7.11295 front fs empty border lc rgb '#6165' lw 0.200001
set object 345 polygon from \
  13.9087, 7.25253 to \
  13.9089, 7.25264 to \
  14.007, 7.11306 to \
  14.007, 7.11269 to \
  6.18825, 3.67244 to \
  6.08981, 3.73405 to \
  13.9087, 7.25253 front fs empty border lc rgb '#6165' lw 0.200001
set object 346 polygon from \
  13.8106, 7.39112 to \
  13.8108, 7.39124 to \
  13.9089, 7.25264 to \
  13.9089, 7.25227 to \
  6.09015, 3.73383 to \
  5.99171, 3.79446 to \
  13.8106, 7.39112 front fs empty border lc rgb '#6165' lw 0.200001
set object 347 polygon from \
  13.7125, 7.52874 to \
  13.7127, 7.52885 to \
  13.8108, 7.39124 to \
  13.8108, 7.39087 to \
  5.99205, 3.79424 to \
  5.89361, 3.85388 to \
  13.7125, 7.52874 front fs empty border lc rgb '#6165' lw 0.200001
set object 348 polygon from \
  13.6144, 7.66537 to \
  13.6146, 7.66549 to \
  13.7127, 7.52885 to \
  13.7127, 7.52848 to \
  5.89395, 3.85367 to \
  5.79551, 3.91233 to \
  13.6144, 7.66537 front fs empty border lc rgb '#6165' lw 0.200001
set object 349 polygon from \
  13.5163, 7.80102 to \
  13.5165, 7.80114 to \
  13.6146, 7.66549 to \
  13.6146, 7.66512 to \
  5.79585, 3.91212 to \
  5.69741, 3.96979 to \
  13.5163, 7.80102 front fs empty border lc rgb '#6165' lw 0.200001
set object 350 polygon from \
  13.4182, 7.93569 to \
  13.4184, 7.93582 to \
  13.5165, 7.80115 to \
  13.5165, 7.80078 to \
  5.69775, 3.96959 to \
  5.59931, 4.02628 to \
  13.4182, 7.93569 front fs empty border lc rgb '#6165' lw 0.200001
set object 351 polygon from \
  13.3201, 8.06939 to \
  13.3203, 8.06951 to \
  13.4184, 7.93582 to \
  13.4184, 7.93545 to \
  5.59965, 4.02608 to \
  5.50121, 4.08178 to \
  13.3201, 8.06939 front fs empty border lc rgb '#6165' lw 0.200001
set object 352 polygon from \
  13.222, 8.2021 to \
  13.2222, 8.20223 to \
  13.3203, 8.06951 to \
  13.3203, 8.06914 to \
  5.50155, 4.08158 to \
  5.40311, 4.1363 to \
  13.222, 8.2021 front fs empty border lc rgb '#6165' lw 0.200001
set object 353 polygon from \
  13.1239, 8.33382 to \
  13.1241, 8.33396 to \
  13.2222, 8.20223 to \
  13.2222, 8.20186 to \
  5.40345, 4.13611 to \
  5.30501, 4.18984 to \
  13.1239, 8.33382 front fs empty border lc rgb '#6165' lw 0.200001
set object 354 polygon from \
  13.0258, 8.46457 to \
  13.026, 8.46471 to \
  13.1241, 8.33396 to \
  13.1241, 8.33359 to \
  5.30535, 4.18965 to \
  5.20691, 4.2424 to \
  13.0258, 8.46457 front fs empty border lc rgb '#6165' lw 0.200001
set object 355 polygon from \
  12.9277, 8.59434 to \
  12.9279, 8.59448 to \
  13.026, 8.46471 to \
  13.026, 8.46434 to \
  5.20725, 4.24222 to \
  5.10881, 4.29398 to \
  12.9277, 8.59434 front fs empty border lc rgb '#6165' lw 0.200001
set object 356 polygon from \
  12.8296, 8.72312 to \
  12.8298, 8.72327 to \
  12.9279, 8.59448 to \
  12.9279, 8.59411 to \
  5.10915, 4.2938 to \
  5.01071, 4.34458 to \
  12.8296, 8.72312 front fs empty border lc rgb '#6165' lw 0.200001
set object 357 polygon from \
  12.7315, 8.85093 to \
  12.7317, 8.85107 to \
  12.8298, 8.72327 to \
  12.8298, 8.7229 to \
  5.01105, 4.3444 to \
  4.91261, 4.39419 to \
  12.7315, 8.85093 front fs empty border lc rgb '#6165' lw 0.200001
set object 358 polygon from \
  12.6334, 8.97775 to \
  12.6336, 8.9779 to \
  12.7317, 8.85108 to \
  12.7317, 8.8507 to \
  4.91295, 4.39402 to \
  4.81451, 4.44283 to \
  12.6334, 8.97775 front fs empty border lc rgb '#6165' lw 0.200001
set object 359 polygon from \
  12.5353, 9.1036 to \
  12.5355, 9.10374 to \
  12.6336, 8.9779 to \
  12.6336, 8.97753 to \
  4.81485, 4.44266 to \
  4.71641, 4.49048 to \
  12.5353, 9.1036 front fs empty border lc rgb '#6165' lw 0.200001
set object 360 polygon from \
  12.4372, 9.22846 to \
  12.4374, 9.22861 to \
  12.5355, 9.10375 to \
  12.5355, 9.10338 to \
  4.71675, 4.49032 to \
  4.61831, 4.53716 to \
  12.4372, 9.22846 front fs empty border lc rgb '#6165' lw 0.200001
set object 361 polygon from \
  12.3391, 9.35234 to \
  12.3393, 9.35249 to \
  12.4374, 9.22861 to \
  12.4374, 9.22824 to \
  4.61865, 4.53699 to \
  4.52021, 4.58285 to \
  12.3391, 9.35234 front fs empty border lc rgb '#6165' lw 0.200001
set object 362 polygon from \
  12.241, 9.47524 to \
  12.2412, 9.4754 to \
  12.3393, 9.3525 to \
  12.3393, 9.35212 to \
  4.52055, 4.58269 to \
  4.42211, 4.62756 to \
  12.241, 9.47524 front fs empty border lc rgb '#6165' lw 0.200001
set object 363 polygon from \
  12.1429, 9.59716 to \
  12.1431, 9.59732 to \
  12.2412, 9.4754 to \
  12.2412, 9.47503 to \
  4.42245, 4.6274 to \
  4.32401, 4.67129 to \
  12.1429, 9.59716 front fs empty border lc rgb '#6165' lw 0.200001
set object 364 polygon from \
  12.0448, 9.7181 to \
  12.045, 9.71826 to \
  12.1431, 9.59732 to \
  12.1431, 9.59695 to \
  4.32435, 4.67114 to \
  4.22591, 4.71404 to \
  12.0448, 9.7181 front fs empty border lc rgb '#6165' lw 0.200001
set object 365 polygon from \
  11.9467, 9.83805 to \
  11.9469, 9.83822 to \
  12.045, 9.71826 to \
  12.045, 9.71789 to \
  4.22625, 4.71389 to \
  4.12781, 4.75581 to \
  11.9467, 9.83805 front fs empty border lc rgb '#6165' lw 0.200001
set object 366 polygon from \
  11.8486, 9.95703 to \
  11.8488, 9.9572 to \
  11.9469, 9.83822 to \
  11.9469, 9.83785 to \
  4.12815, 4.75566 to \
  4.02971, 4.7966 to \
  11.8486, 9.95703 front fs empty border lc rgb '#6165' lw 0.200001
set object 367 polygon from \
  11.7505, 10.0751 to \
  11.7507, 10.0752 to \
  11.8488, 9.9572 to \
  11.8488, 9.95683 to \
  4.03005, 4.79645 to \
  3.93161, 4.83641 to \
  11.7505, 10.0751 front fs empty border lc rgb '#6165' lw 0.200001
set object 368 polygon from \
  11.6524, 10.1921 to \
  11.6526, 10.1923 to \
  11.7507, 10.0752 to \
  11.7507, 10.0749 to \
  3.93195, 4.83626 to \
  3.83351, 4.87523 to \
  11.6524, 10.1921 front fs empty border lc rgb '#6165' lw 0.200001
set object 369 polygon from \
  11.5543, 10.3081 to \
  11.5545, 10.3083 to \
  11.6526, 10.1923 to \
  11.6526, 10.1919 to \
  3.83385, 4.87509 to \
  3.73541, 4.91308 to \
  11.5543, 10.3081 front fs empty border lc rgb '#6165' lw 0.200001
set object 370 polygon from \
  11.4562, 10.4232 to \
  11.4564, 10.4233 to \
  11.5545, 10.3083 to \
  11.5545, 10.3079 to \
  3.73575, 4.91294 to \
  3.63731, 4.94994 to \
  11.4562, 10.4232 front fs empty border lc rgb '#6165' lw 0.200001
set object 371 polygon from \
  11.3581, 10.5372 to \
  11.3583, 10.5374 to \
  11.4564, 10.4233 to \
  11.4564, 10.423 to \
  3.63765, 4.94981 to \
  3.53921, 4.98582 to \
  11.3581, 10.5372 front fs empty border lc rgb '#6165' lw 0.200001
set object 372 polygon from \
  11.26, 10.6503 to \
  11.2602, 10.6505 to \
  11.3583, 10.5374 to \
  11.3583, 10.537 to \
  3.53955, 4.98569 to \
  3.44111, 5.02072 to \
  11.26, 10.6503 front fs empty border lc rgb '#6165' lw 0.200001
set object 373 polygon from \
  11.1619, 10.7624 to \
  11.1621, 10.7626 to \
  11.2602, 10.6505 to \
  11.2602, 10.6501 to \
  3.44145, 5.0206 to \
  3.34301, 5.05464 to \
  11.1619, 10.7624 front fs empty border lc rgb '#6165' lw 0.200001
set object 374 polygon from \
  11.0638, 10.8736 to \
  11.064, 10.8738 to \
  11.1621, 10.7626 to \
  11.1621, 10.7623 to \
  3.34335, 5.05452 to \
  3.24491, 5.08758 to \
  11.0638, 10.8736 front fs empty border lc rgb '#6165' lw 0.200001
set object 375 polygon from \
  10.9657, 10.9837 to \
  10.9659, 10.9839 to \
  11.064, 10.8738 to \
  11.064, 10.8734 to \
  3.24525, 5.08746 to \
  3.14681, 5.11954 to \
  10.9657, 10.9837 front fs empty border lc rgb '#6165' lw 0.200001
set object 376 polygon from \
  10.8676, 11.0929 to \
  10.8678, 11.0931 to \
  10.9659, 10.9839 to \
  10.9659, 10.9835 to \
  3.14715, 5.11943 to \
  3.04871, 5.15052 to \
  10.8676, 11.0929 front fs empty border lc rgb '#6165' lw 0.200001
set object 377 polygon from \
  10.7695, 11.2011 to \
  10.7697, 11.2013 to \
  10.8678, 11.0931 to \
  10.8678, 11.0927 to \
  3.04905, 5.15041 to \
  2.95061, 5.18052 to \
  10.7695, 11.2011 front fs empty border lc rgb '#6165' lw 0.200001
set object 378 polygon from \
  10.6714, 11.3083 to \
  10.6716, 11.3085 to \
  10.7697, 11.2013 to \
  10.7697, 11.2009 to \
  2.95095, 5.18041 to \
  2.85251, 5.20953 to \
  10.6714, 11.3083 front fs empty border lc rgb '#6165' lw 0.200001
set object 379 polygon from \
  10.5733, 11.4145 to \
  10.5735, 11.4147 to \
  10.6716, 11.3085 to \
  10.6716, 11.3081 to \
  2.85285, 5.20943 to \
  2.75441, 5.23757 to \
  10.5733, 11.4145 front fs empty border lc rgb '#6165' lw 0.200001
set object 380 polygon from \
  10.4752, 11.5197 to \
  10.4754, 11.5199 to \
  10.5735, 11.4147 to \
  10.5735, 11.4143 to \
  2.75475, 5.23746 to \
  2.65631, 5.26462 to \
  10.4752, 11.5197 front fs empty border lc rgb '#6165' lw 0.200001
set object 381 polygon from \
  10.3771, 11.624 to \
  10.3773, 11.6242 to \
  10.4754, 11.5199 to \
  10.4754, 11.5196 to \
  2.65665, 5.26452 to \
  2.55821, 5.29069 to \
  10.3771, 11.624 front fs empty border lc rgb '#6165' lw 0.200001
set object 382 polygon from \
  10.279, 11.7273 to \
  10.2792, 11.7275 to \
  10.3773, 11.6242 to \
  10.3773, 11.6238 to \
  2.55855, 5.2906 to \
  2.46011, 5.31578 to \
  10.279, 11.7273 front fs empty border lc rgb '#6165' lw 0.200001
set object 383 polygon from \
  10.1809, 11.8296 to \
  10.1811, 11.8298 to \
  10.2792, 11.7275 to \
  10.2792, 11.7271 to \
  2.46045, 5.31569 to \
  2.36201, 5.33989 to \
  10.1809, 11.8296 front fs empty border lc rgb '#6165' lw 0.200001
set object 384 polygon from \
  10.0828, 11.9309 to \
  10.083, 11.9311 to \
  10.1811, 11.8298 to \
  10.1811, 11.8294 to \
  2.36235, 5.33981 to \
  2.26391, 5.36302 to \
  10.0828, 11.9309 front fs empty border lc rgb '#6165' lw 0.200001
set object 385 polygon from \
  9.98466, 12.0312 to \
  9.9849, 12.0314 to \
  10.083, 11.9311 to \
  10.083, 11.9307 to \
  2.26425, 5.36294 to \
  2.16581, 5.38517 to \
  9.98466, 12.0312 front fs empty border lc rgb '#6165' lw 0.200001
set object 386 polygon from \
  9.88656, 12.1306 to \
  9.8868, 12.1308 to \
  9.9849, 12.0314 to \
  9.9849, 12.0311 to \
  2.16615, 5.38509 to \
  2.06771, 5.40634 to \
  9.88656, 12.1306 front fs empty border lc rgb '#6165' lw 0.200001
set object 387 polygon from \
  9.78846, 12.229 to \
  9.7887, 12.2292 to \
  9.8868, 12.1308 to \
  9.8868, 12.1304 to \
  2.06805, 5.40626 to \
  1.96961, 5.42653 to \
  9.78846, 12.229 front fs empty border lc rgb '#6165' lw 0.200001
set object 388 polygon from \
  9.69036, 12.3264 to \
  9.6906, 12.3266 to \
  9.7887, 12.2292 to \
  9.7887, 12.2288 to \
  1.96995, 5.42645 to \
  1.87151, 5.44573 to \
  9.69036, 12.3264 front fs empty border lc rgb '#6165' lw 0.200001
set object 389 polygon from \
  9.59226, 12.4228 to \
  9.5925, 12.423 to \
  9.6906, 12.3266 to \
  9.6906, 12.3262 to \
  1.87185, 5.44566 to \
  1.77341, 5.46396 to \
  9.59226, 12.4228 front fs empty border lc rgb '#6165' lw 0.200001
set object 390 polygon from \
  9.49416, 12.5182 to \
  9.4944, 12.5184 to \
  9.5925, 12.423 to \
  9.5925, 12.4226 to \
  1.77375, 5.46389 to \
  1.67531, 5.4812 to \
  9.49416, 12.5182 front fs empty border lc rgb '#6165' lw 0.200001
set object 391 polygon from \
  9.39607, 12.6127 to \
  9.3963, 12.6129 to \
  9.4944, 12.5184 to \
  9.4944, 12.5181 to \
  1.67565, 5.48113 to \
  1.57721, 5.49746 to \
  9.39607, 12.6127 front fs empty border lc rgb '#6165' lw 0.200001
set object 392 polygon from \
  9.29796, 12.7061 to \
  9.2982, 12.7064 to \
  9.3963, 12.6129 to \
  9.3963, 12.6125 to \
  1.57755, 5.4974 to \
  1.47911, 5.51274 to \
  9.29796, 12.7061 front fs empty border lc rgb '#6165' lw 0.200001
set object 393 polygon from \
  9.19987, 12.7986 to \
  9.2001, 12.7988 to \
  9.2982, 12.7064 to \
  9.2982, 12.706 to \
  1.47945, 5.51269 to \
  1.38101, 5.52704 to \
  9.19987, 12.7986 front fs empty border lc rgb '#6165' lw 0.200001
set object 394 polygon from \
  9.10176, 12.8901 to \
  9.102, 12.8904 to \
  9.2001, 12.7988 to \
  9.2001, 12.7985 to \
  1.38135, 5.52699 to \
  1.28291, 5.54036 to \
  9.10176, 12.8901 front fs empty border lc rgb '#6165' lw 0.200001
set object 395 polygon from \
  9.00366, 12.9807 to \
  9.0039, 12.9809 to \
  9.102, 12.8904 to \
  9.102, 12.89 to \
  1.28325, 5.54031 to \
  1.18481, 5.5527 to \
  9.00366, 12.9807 front fs empty border lc rgb '#6165' lw 0.200001
set object 396 polygon from \
  8.90556, 13.0702 to \
  8.9058, 13.0704 to \
  9.0039, 12.9809 to \
  9.0039, 12.9805 to \
  1.18515, 5.55265 to \
  1.08671, 5.56406 to \
  8.90556, 13.0702 front fs empty border lc rgb '#6165' lw 0.200001
set object 397 polygon from \
  8.80746, 13.1588 to \
  8.8077, 13.159 to \
  8.9058, 13.0704 to \
  8.9058, 13.0701 to \
  1.08705, 5.56402 to \
  0.988605, 5.57444 to \
  8.80746, 13.1588 front fs empty border lc rgb '#6165' lw 0.200001
set object 398 polygon from \
  8.70936, 13.2464 to \
  8.7096, 13.2466 to \
  8.8077, 13.159 to \
  8.8077, 13.1586 to \
  0.988945, 5.5744 to \
  0.890505, 5.58383 to \
  8.70936, 13.2464 front fs empty border lc rgb '#6165' lw 0.200001
set object 399 polygon from \
  8.61126, 13.333 to \
  8.6115, 13.3332 to \
  8.7096, 13.2466 to \
  8.7096, 13.2462 to \
  0.890845, 5.58379 to \
  0.792405, 5.59225 to \
  8.61126, 13.333 front fs empty border lc rgb '#6165' lw 0.200001
set object 400 polygon from \
  8.51315, 13.4186 to \
  8.5134, 13.4188 to \
  8.6115, 13.3332 to \
  8.6115, 13.3328 to \
  0.792745, 5.59221 to \
  0.694305, 5.59968 to \
  8.51315, 13.4186 front fs empty border lc rgb '#6165' lw 0.200001
set object 401 polygon from \
  8.41506, 13.5032 to \
  8.4153, 13.5035 to \
  8.5134, 13.4188 to \
  8.5134, 13.4184 to \
  0.694645, 5.59965 to \
  0.596205, 5.60613 to \
  8.41506, 13.5032 front fs empty border lc rgb '#6165' lw 0.200001
set object 402 polygon from \
  8.31696, 13.5869 to \
  8.3172, 13.5871 to \
  8.4153, 13.5035 to \
  8.4153, 13.5031 to \
  0.596545, 5.60611 to \
  0.498105, 5.6116 to \
  8.31696, 13.5869 front fs empty border lc rgb '#6165' lw 0.200001
set object 403 polygon from \
  8.21886, 13.6696 to \
  8.2191, 13.6698 to \
  8.3172, 13.5871 to \
  8.3172, 13.5867 to \
  0.498445, 5.61158 to \
  0.400005, 5.61609 to \
  8.21886, 13.6696 front fs empty border lc rgb '#6165' lw 0.200001
set object 404 polygon from \
  8.12076, 13.7513 to \
  8.121, 13.7515 to \
  8.2191, 13.6698 to \
  8.2191, 13.6694 to \
  0.400345, 5.61607 to \
  0.301905, 5.6196 to \
  8.12076, 13.7513 front fs empty border lc rgb '#6165' lw 0.200001
set object 405 polygon from \
  8.02267, 13.832 to \
  8.0229, 13.8322 to \
  8.121, 13.7515 to \
  8.121, 13.7511 to \
  0.302245, 5.61959 to \
  0.203805, 5.62213 to \
  8.02267, 13.832 front fs empty border lc rgb '#6165' lw 0.200001
set object 406 polygon from \
  7.92457, 13.9117 to \
  7.9248, 13.912 to \
  8.0229, 13.8322 to \
  8.0229, 13.8319 to \
  0.204145, 5.62212 to \
  0.105705, 5.62368 to \
  7.92457, 13.9117 front fs empty border lc rgb '#6165' lw 0.200001
set object 407 polygon from \
  7.82647, 13.9905 to \
  7.8267, 13.9907 to \
  7.9248, 13.912 to \
  7.9248, 13.9116 to \
  0.106045, 5.62367 to \
  0.00760413, 5.62425 to \
  7.82647, 13.9905 front fs empty border lc rgb '#6165' lw 0.200001
set object 408 polygon from \
  7.72837, 14.0682 to \
  7.7286, 14.0685 to \
  7.8267, 13.9907 to \
  7.8267, 13.9903 to \
  0.00794489, 5.62424 to \
  -0.0904959, 5.62383 to \
  7.72837, 14.0682 front fs empty border lc rgb '#6165' lw 0.200001
set object 409 polygon from \
  7.63027, 14.145 to \
  7.6305, 14.1453 to \
  7.7286, 14.0685 to \
  7.7286, 14.0681 to \
  -0.0901551, 5.62383 to \
  -0.188595, 5.62244 to \
  7.63027, 14.145 front fs empty border lc rgb '#6165' lw 0.200001
set object 410 polygon from \
  7.53217, 14.2209 to \
  7.5324, 14.2211 to \
  7.6305, 14.1453 to \
  7.6305, 14.1449 to \
  -0.188255, 5.62244 to \
  -0.286695, 5.62006 to \
  7.53217, 14.2209 front fs empty border lc rgb '#6165' lw 0.200001
set object 411 polygon from \
  7.43407, 14.2957 to \
  7.4343, 14.2959 to \
  7.5324, 14.2211 to \
  7.5324, 14.2207 to \
  -0.286355, 5.62006 to \
  -0.384795, 5.6167 to \
  7.43407, 14.2957 front fs empty border lc rgb '#6165' lw 0.200001
set object 412 polygon from \
  7.33596, 14.3695 to \
  7.3362, 14.3698 to \
  7.4343, 14.2959 to \
  7.4343, 14.2956 to \
  -0.384455, 5.61671 to \
  -0.482895, 5.61236 to \
  7.33596, 14.3695 front fs empty border lc rgb '#6165' lw 0.200001
set object 413 polygon from \
  7.23786, 14.4424 to \
  7.2381, 14.4427 to \
  7.3362, 14.3698 to \
  7.3362, 14.3694 to \
  -0.482555, 5.61237 to \
  -0.580996, 5.60704 to \
  7.23786, 14.4424 front fs empty border lc rgb '#6165' lw 0.200001
set object 414 polygon from \
  7.13977, 14.5143 to \
  7.14, 14.5146 to \
  7.2381, 14.4427 to \
  7.2381, 14.4423 to \
  -0.580655, 5.60706 to \
  -0.679096, 5.60074 to \
  7.13977, 14.5143 front fs empty border lc rgb '#6165' lw 0.200001
set object 415 polygon from \
  7.04167, 14.5852 to \
  7.0419, 14.5855 to \
  7.14, 14.5146 to \
  7.14, 14.5142 to \
  -0.678755, 5.60076 to \
  -0.777196, 5.59346 to \
  7.04167, 14.5852 front fs empty border lc rgb '#6165' lw 0.200001
set object 416 polygon from \
  6.94357, 14.6551 to \
  6.9438, 14.6554 to \
  7.0419, 14.5855 to \
  7.0419, 14.5851 to \
  -0.776855, 5.59348 to \
  -0.875296, 5.5852 to \
  6.94357, 14.6551 front fs empty border lc rgb '#6165' lw 0.200001
set object 417 polygon from \
  6.84546, 14.7241 to \
  6.8457, 14.7243 to \
  6.9438, 14.6554 to \
  6.9438, 14.655 to \
  -0.874955, 5.58522 to \
  -0.973396, 5.57596 to \
  6.84546, 14.7241 front fs empty border lc rgb '#6165' lw 0.200001
set object 418 polygon from \
  6.74736, 14.792 to \
  6.7476, 14.7923 to \
  6.8457, 14.7243 to \
  6.8457, 14.724 to \
  -0.973055, 5.57598 to \
  -1.07149, 5.56573 to \
  6.74736, 14.792 front fs empty border lc rgb '#6165' lw 0.200001
set object 419 polygon from \
  6.64927, 14.859 to \
  6.6495, 14.8593 to \
  6.7476, 14.7923 to \
  6.7476, 14.7919 to \
  -1.07115, 5.56576 to \
  -1.16959, 5.55453 to \
  6.64927, 14.859 front fs empty border lc rgb '#6165' lw 0.200001
set object 420 polygon from \
  6.55116, 14.925 to \
  6.55141, 14.9253 to \
  6.6495, 14.8593 to \
  6.6495, 14.8589 to \
  -1.16925, 5.55456 to \
  -1.26769, 5.54234 to \
  6.55116, 14.925 front fs empty border lc rgb '#6165' lw 0.200001
set object 421 polygon from \
  6.45306, 14.99 to \
  6.45331, 14.9903 to \
  6.5514, 14.9253 to \
  6.5514, 14.9249 to \
  -1.26735, 5.54238 to \
  -1.36579, 5.52917 to \
  6.45306, 14.99 front fs empty border lc rgb '#6165' lw 0.200001
set object 422 polygon from \
  6.35497, 15.0541 to \
  6.35521, 15.0544 to \
  6.4533, 14.9903 to \
  6.4533, 14.9899 to \
  -1.36545, 5.52921 to \
  -1.46389, 5.51502 to \
  6.35497, 15.0541 front fs empty border lc rgb '#6165' lw 0.200001
set object 423 polygon from \
  6.25687, 15.1171 to \
  6.25711, 15.1174 to \
  6.3552, 15.0544 to \
  6.3552, 15.054 to \
  -1.46355, 5.51507 to \
  -1.56199, 5.49989 to \
  6.25687, 15.1171 front fs empty border lc rgb '#6165' lw 0.200001
set object 424 polygon from \
  6.15877, 15.1792 to \
  6.15901, 15.1795 to \
  6.2571, 15.1174 to \
  6.2571, 15.117 to \
  -1.56165, 5.49994 to \
  -1.66009, 5.48378 to \
  6.15877, 15.1792 front fs empty border lc rgb '#6165' lw 0.200001
set object 425 polygon from \
  6.06068, 15.2403 to \
  6.06091, 15.2406 to \
  6.159, 15.1795 to \
  6.159, 15.1791 to \
  -1.65975, 5.48384 to \
  -1.75819, 5.46669 to \
  6.06068, 15.2403 front fs empty border lc rgb '#6165' lw 0.200001
set object 426 polygon from \
  5.96257, 15.3004 to \
  5.96281, 15.3007 to \
  6.0609, 15.2406 to \
  6.0609, 15.2402 to \
  -1.75785, 5.46675 to \
  -1.85629, 5.44862 to \
  5.96257, 15.3004 front fs empty border lc rgb '#6165' lw 0.200001
set object 427 polygon from \
  5.86448, 15.3596 to \
  5.86471, 15.3599 to \
  5.9628, 15.3007 to \
  5.9628, 15.3003 to \
  -1.85595, 5.44868 to \
  -1.95439, 5.42957 to \
  5.86448, 15.3596 front fs empty border lc rgb '#6165' lw 0.200001
set object 428 polygon from \
  5.76638, 15.4177 to \
  5.76661, 15.418 to \
  5.8647, 15.3599 to \
  5.8647, 15.3595 to \
  -1.95405, 5.42963 to \
  -2.05249, 5.40953 to \
  5.76638, 15.4177 front fs empty border lc rgb '#6165' lw 0.200001
set object 429 polygon from \
  5.66828, 15.4749 to \
  5.66851, 15.4752 to \
  5.7666, 15.418 to \
  5.7666, 15.4176 to \
  -2.05215, 5.4096 to \
  -2.15059, 5.38852 to \
  5.66828, 15.4749 front fs empty border lc rgb '#6165' lw 0.200001
set object 430 polygon from \
  5.57018, 15.5311 to \
  5.57041, 15.5314 to \
  5.6685, 15.4752 to \
  5.6685, 15.4748 to \
  -2.15025, 5.38859 to \
  -2.24869, 5.36652 to \
  5.57018, 15.5311 front fs empty border lc rgb '#6165' lw 0.200001
set object 431 polygon from \
  5.47208, 15.5863 to \
  5.47231, 15.5866 to \
  5.5704, 15.5314 to \
  5.5704, 15.531 to \
  -2.24835, 5.36659 to \
  -2.34679, 5.34354 to \
  5.47208, 15.5863 front fs empty border lc rgb '#6165' lw 0.200001
set object 432 polygon from \
  5.37398, 15.6405 to \
  5.37421, 15.6408 to \
  5.4723, 15.5866 to \
  5.4723, 15.5862 to \
  -2.34645, 5.34362 to \
  -2.44489, 5.31958 to \
  5.37398, 15.6405 front fs empty border lc rgb '#6165' lw 0.200001
set object 433 polygon from \
  5.27587, 15.6938 to \
  5.27611, 15.6941 to \
  5.3742, 15.6408 to \
  5.3742, 15.6405 to \
  -2.44455, 5.31966 to \
  -2.54299, 5.29465 to \
  5.27587, 15.6938 front fs empty border lc rgb '#6165' lw 0.200001
set object 434 polygon from \
  5.17778, 15.7461 to \
  5.17801, 15.7464 to \
  5.2761, 15.6941 to \
  5.2761, 15.6937 to \
  -2.54265, 5.29473 to \
  -2.64109, 5.26872 to \
  5.17778, 15.7461 front fs empty border lc rgb '#6165' lw 0.200001
set object 435 polygon from \
  5.07969, 15.7974 to \
  5.07991, 15.7977 to \
  5.178, 15.7464 to \
  5.178, 15.746 to \
  -2.64075, 5.26881 to \
  -2.73919, 5.24182 to \
  5.07969, 15.7974 front fs empty border lc rgb '#6165' lw 0.200001
set object 436 polygon from \
  4.98159, 15.8477 to \
  4.98181, 15.848 to \
  5.0799, 15.7977 to \
  5.0799, 15.7973 to \
  -2.73885, 5.24191 to \
  -2.83729, 5.21394 to \
  4.98159, 15.8477 front fs empty border lc rgb '#6165' lw 0.200001
set object 437 polygon from \
  4.8835, 15.897 to \
  4.88371, 15.8973 to \
  4.9818, 15.848 to \
  4.9818, 15.8476 to \
  -2.83695, 5.21403 to \
  -2.93539, 5.18508 to \
  4.8835, 15.897 front fs empty border lc rgb '#6165' lw 0.200001
set object 438 polygon from \
  4.78539, 15.9453 to \
  4.78561, 15.9456 to \
  4.8837, 15.8973 to \
  4.8837, 15.8969 to \
  -2.93505, 5.18517 to \
  -3.03349, 5.15523 to \
  4.78539, 15.9453 front fs empty border lc rgb '#6165' lw 0.200001
set object 439 polygon from \
  4.68729, 15.9927 to \
  4.68751, 15.993 to \
  4.7856, 15.9456 to \
  4.7856, 15.9452 to \
  -3.03315, 5.15533 to \
  -3.13159, 5.12441 to \
  4.68729, 15.9927 front fs empty border lc rgb '#6165' lw 0.200001
set object 440 polygon from \
  4.58919, 16.0391 to \
  4.58941, 16.0394 to \
  4.6875, 15.993 to \
  4.6875, 15.9926 to \
  -3.13125, 5.12451 to \
  -3.22969, 5.0926 to \
  4.58919, 16.0391 front fs empty border lc rgb '#6165' lw 0.200001
set object 441 polygon from \
  4.4911, 16.0845 to \
  4.49131, 16.0848 to \
  4.5894, 16.0394 to \
  4.5894, 16.039 to \
  -3.22935, 5.09271 to \
  -3.32779, 5.05981 to \
  4.4911, 16.0845 front fs empty border lc rgb '#6165' lw 0.200001
set object 442 polygon from \
  4.393, 16.1289 to \
  4.39321, 16.1292 to \
  4.4913, 16.0848 to \
  4.4913, 16.0844 to \
  -3.32745, 5.05992 to \
  -3.42589, 5.02604 to \
  4.393, 16.1289 front fs empty border lc rgb '#6165' lw 0.200001
set object 443 polygon from \
  4.2949, 16.1724 to \
  4.29511, 16.1727 to \
  4.3932, 16.1292 to \
  4.3932, 16.1288 to \
  -3.42555, 5.02616 to \
  -3.52399, 4.9913 to \
  4.2949, 16.1724 front fs empty border lc rgb '#6165' lw 0.200001
set object 444 polygon from \
  4.19679, 16.2148 to \
  4.19701, 16.2151 to \
  4.2951, 16.1727 to \
  4.2951, 16.1723 to \
  -3.52365, 4.99141 to \
  -3.62209, 4.95556 to \
  4.19679, 16.2148 front fs empty border lc rgb '#6165' lw 0.200001
set object 445 polygon from \
  4.09869, 16.2563 to \
  4.09891, 16.2566 to \
  4.197, 16.2151 to \
  4.197, 16.2147 to \
  -3.62175, 4.95568 to \
  -3.72019, 4.91885 to \
  4.09869, 16.2563 front fs empty border lc rgb '#6165' lw 0.200001
set object 446 polygon from \
  4.00059, 16.2968 to \
  4.00081, 16.2971 to \
  4.0989, 16.2566 to \
  4.0989, 16.2562 to \
  -3.71985, 4.91898 to \
  -3.81829, 4.88116 to \
  4.00059, 16.2968 front fs empty border lc rgb '#6165' lw 0.200001
set object 447 polygon from \
  3.9025, 16.3363 to \
  3.90271, 16.3366 to \
  4.0008, 16.2971 to \
  4.0008, 16.2967 to \
  -3.81795, 4.88129 to \
  -3.91639, 4.84249 to \
  3.9025, 16.3363 front fs empty border lc rgb '#6165' lw 0.200001
set object 448 polygon from \
  3.8044, 16.3748 to \
  3.80461, 16.3751 to \
  3.9027, 16.3366 to \
  3.9027, 16.3362 to \
  -3.91605, 4.84262 to \
  -4.01449, 4.80283 to \
  3.8044, 16.3748 front fs empty border lc rgb '#6165' lw 0.200001
set object 449 polygon from \
  3.7063, 16.4124 to \
  3.70651, 16.4127 to \
  3.8046, 16.3751 to \
  3.8046, 16.3748 to \
  -4.01415, 4.80297 to \
  -4.11259, 4.7622 to \
  3.7063, 16.4124 front fs empty border lc rgb '#6165' lw 0.200001
set object 450 polygon from \
  3.60821, 16.449 to \
  3.60841, 16.4493 to \
  3.7065, 16.4127 to \
  3.7065, 16.4123 to \
  -4.11225, 4.76233 to \
  -4.21069, 4.72058 to \
  3.60821, 16.449 front fs empty border lc rgb '#6165' lw 0.200001
set object 451 polygon from \
  3.5101, 16.4846 to \
  3.51031, 16.4849 to \
  3.6084, 16.4493 to \
  3.6084, 16.4489 to \
  -4.21035, 4.72072 to \
  -4.30879, 4.67798 to \
  3.5101, 16.4846 front fs empty border lc rgb '#6165' lw 0.200001
set object 452 polygon from \
  3.412, 16.5192 to \
  3.41221, 16.5195 to \
  3.5103, 16.4849 to \
  3.5103, 16.4845 to \
  -4.30845, 4.67813 to \
  -4.40689, 4.6344 to \
  3.412, 16.5192 front fs empty border lc rgb '#6165' lw 0.200001
set object 453 polygon from \
  3.31391, 16.5528 to \
  3.31411, 16.5531 to \
  3.4122, 16.5195 to \
  3.4122, 16.5191 to \
  -4.40655, 4.63455 to \
  -4.50499, 4.58985 to \
  3.31391, 16.5528 front fs empty border lc rgb '#6165' lw 0.200001
set object 454 polygon from \
  3.21581, 16.5855 to \
  3.21601, 16.5858 to \
  3.3141, 16.5531 to \
  3.3141, 16.5527 to \
  -4.50465, 4.59 to \
  -4.60309, 4.5443 to \
  3.21581, 16.5855 front fs empty border lc rgb '#6165' lw 0.200001
set object 455 polygon from \
  3.11769, 16.6171 to \
  3.11791, 16.6174 to \
  3.216, 16.5858 to \
  3.216, 16.5854 to \
  -4.60275, 4.54446 to \
  -4.70119, 4.49778 to \
  3.11769, 16.6171 front fs empty border lc rgb '#6165' lw 0.200001
set object 456 polygon from \
  3.01958, 16.6478 to \
  3.01981, 16.6481 to \
  3.1179, 16.6174 to \
  3.1179, 16.617 to \
  -4.70085, 4.49794 to \
  -4.79929, 4.45028 to \
  3.01958, 16.6478 front fs empty border lc rgb '#6165' lw 0.200001
set object 457 polygon from \
  2.92148, 16.6775 to \
  2.92171, 16.6778 to \
  3.0198, 16.6481 to \
  3.0198, 16.6477 to \
  -4.79895, 4.45044 to \
  -4.89739, 4.4018 to \
  2.92148, 16.6775 front fs empty border lc rgb '#6165' lw 0.200001
set object 458 polygon from \
  2.82338, 16.7062 to \
  2.82361, 16.7066 to \
  2.9217, 16.6778 to \
  2.9217, 16.6774 to \
  -4.89705, 4.40196 to \
  -4.99549, 4.35233 to \
  2.82338, 16.7062 front fs empty border lc rgb '#6165' lw 0.200001
set object 459 polygon from \
  2.72528, 16.7339 to \
  2.72551, 16.7343 to \
  2.8236, 16.7066 to \
  2.8236, 16.7062 to \
  -4.99515, 4.3525 to \
  -5.09359, 4.30189 to \
  2.72528, 16.7339 front fs empty border lc rgb '#6165' lw 0.200001
set object 460 polygon from \
  2.62718, 16.7607 to \
  2.62741, 16.7611 to \
  2.7255, 16.7343 to \
  2.7255, 16.7339 to \
  -5.09325, 4.30206 to \
  -5.19169, 4.25046 to \
  2.62718, 16.7607 front fs empty border lc rgb '#6165' lw 0.200001
set object 461 polygon from \
  2.52908, 16.7865 to \
  2.52931, 16.7869 to \
  2.6274, 16.7611 to \
  2.6274, 16.7607 to \
  -5.19135, 4.25064 to \
  -5.28979, 4.19805 to \
  2.52908, 16.7865 front fs empty border lc rgb '#6165' lw 0.200001
set object 462 polygon from \
  2.43099, 16.8113 to \
  2.43121, 16.8117 to \
  2.5293, 16.7869 to \
  2.5293, 16.7865 to \
  -5.28945, 4.19823 to \
  -5.38789, 4.14467 to \
  2.43099, 16.8113 front fs empty border lc rgb '#6165' lw 0.200001
set object 463 polygon from \
  2.33288, 16.8351 to \
  2.33311, 16.8355 to \
  2.4312, 16.8117 to \
  2.4312, 16.8113 to \
  -5.38755, 4.14485 to \
  -5.48599, 4.0903 to \
  2.33288, 16.8351 front fs empty border lc rgb '#6165' lw 0.200001
set object 464 polygon from \
  2.23477, 16.8579 to \
  2.23501, 16.8583 to \
  2.3331, 16.8355 to \
  2.3331, 16.8351 to \
  -5.48565, 4.09048 to \
  -5.58409, 4.03495 to \
  2.23477, 16.8579 front fs empty border lc rgb '#6165' lw 0.200001
set object 465 polygon from \
  2.13668, 16.8798 to \
  2.13691, 16.8802 to \
  2.235, 16.8583 to \
  2.235, 16.8579 to \
  -5.58375, 4.03513 to \
  -5.68219, 3.97861 to \
  2.13668, 16.8798 front fs empty border lc rgb '#6165' lw 0.200001
set object 466 polygon from \
  2.03856, 16.9007 to \
  2.03881, 16.9011 to \
  2.1369, 16.8802 to \
  2.1369, 16.8798 to \
  -5.68185, 3.97881 to \
  -5.78029, 3.9213 to \
  2.03856, 16.9007 front fs empty border lc rgb '#6165' lw 0.200001
set object 467 polygon from \
  1.94047, 16.9206 to \
  1.94071, 16.921 to \
  2.0388, 16.9011 to \
  2.0388, 16.9007 to \
  -5.77995, 3.9215 to \
  -5.87839, 3.86301 to \
  1.94047, 16.9206 front fs empty border lc rgb '#6165' lw 0.200001
set object 468 polygon from \
  1.84237, 16.9395 to \
  1.84261, 16.9399 to \
  1.9407, 16.921 to \
  1.9407, 16.9206 to \
  -5.87805, 3.86321 to \
  -5.97649, 3.80373 to \
  1.84237, 16.9395 front fs empty border lc rgb '#6165' lw 0.200001
set object 469 polygon from \
  1.74425, 16.9574 to \
  1.74451, 16.9578 to \
  1.8426, 16.9399 to \
  1.8426, 16.9395 to \
  -5.97615, 3.80394 to \
  -6.07459, 3.74348 to \
  1.74425, 16.9574 front fs empty border lc rgb '#6165' lw 0.200001
set object 470 polygon from \
  1.64614, 16.9743 to \
  1.64641, 16.9748 to \
  1.7445, 16.9578 to \
  1.7445, 16.9574 to \
  -6.07425, 3.74368 to \
  -6.17269, 3.68224 to \
  1.64614, 16.9743 front fs empty border lc rgb '#6165' lw 0.200001
set object 471 polygon from \
  1.54804, 16.9903 to \
  1.54831, 16.9907 to \
  1.6464, 16.9748 to \
  1.6464, 16.9744 to \
  -6.17235, 3.68245 to \
  -6.27079, 3.62002 to \
  1.54804, 16.9903 front fs empty border lc rgb '#6165' lw 0.200001
set object 472 polygon from \
  1.44994, 17.0053 to \
  1.45021, 17.0057 to \
  1.5483, 16.9907 to \
  1.5483, 16.9903 to \
  -6.27045, 3.62024 to \
  -6.36889, 3.55683 to \
  1.44994, 17.0053 front fs empty border lc rgb '#6165' lw 0.200001
set object 473 polygon from \
  1.35184, 17.0193 to \
  1.35211, 17.0197 to \
  1.4502, 17.0057 to \
  1.4502, 17.0053 to \
  -6.36855, 3.55704 to \
  -6.46699, 3.49265 to \
  1.35184, 17.0193 front fs empty border lc rgb '#6165' lw 0.200001
set object 474 polygon from \
  1.25373, 17.0323 to \
  1.25401, 17.0328 to \
  1.3521, 17.0197 to \
  1.3521, 17.0193 to \
  -6.46665, 3.49286 to \
  -6.56509, 3.42749 to \
  1.25373, 17.0323 front fs empty border lc rgb '#6165' lw 0.200001
set object 475 polygon from \
  1.15564, 17.0443 to \
  1.15591, 17.0448 to \
  1.254, 17.0328 to \
  1.254, 17.0324 to \
  -6.56475, 3.42771 to \
  -6.66319, 3.36134 to \
  1.15564, 17.0443 front fs empty border lc rgb '#6165' lw 0.200001
set object 476 polygon from \
  1.05756, 17.0554 to \
  1.05781, 17.0559 to \
  1.1559, 17.0448 to \
  1.1559, 17.0444 to \
  -6.66285, 3.36157 to \
  -6.76129, 3.29422 to \
  1.05756, 17.0554 front fs empty border lc rgb '#6165' lw 0.200001
set object 477 polygon from \
  0.959445, 17.0655 to \
  0.959703, 17.066 to \
  1.0578, 17.0559 to \
  1.0578, 17.0555 to \
  -6.76095, 3.29445 to \
  -6.85939, 3.22612 to \
  0.959445, 17.0655 front fs empty border lc rgb '#6165' lw 0.200001
set object 478 polygon from \
  0.861335, 17.0746 to \
  0.861603, 17.0751 to \
  0.959696, 17.066 to \
  0.959696, 17.0656 to \
  -6.85905, 3.22635 to \
  -6.95749, 3.15703 to \
  0.861335, 17.0746 front fs empty border lc rgb '#6165' lw 0.200001
set object 479 polygon from \
  0.763233, 17.0827 to \
  0.763503, 17.0832 to \
  0.861596, 17.0751 to \
  0.861596, 17.0747 to \
  -6.95715, 3.15727 to \
  -7.05559, 3.08697 to \
  0.763233, 17.0827 front fs empty border lc rgb '#6165' lw 0.200001
set object 480 polygon from \
  0.665124, 17.0899 to \
  0.665403, 17.0904 to \
  0.763496, 17.0832 to \
  0.763496, 17.0828 to \
  -7.05525, 3.08721 to \
  -7.15369, 3.01592 to \
  0.665124, 17.0899 front fs empty border lc rgb '#6165' lw 0.200001
set object 481 polygon from \
  0.567021, 17.096 to \
  0.567303, 17.0965 to \
  0.665396, 17.0904 to \
  0.665396, 17.09 to \
  -7.15335, 3.01616 to \
  -7.25179, 2.94389 to \
  0.567021, 17.096 front fs empty border lc rgb '#6165' lw 0.200001
set object 482 polygon from \
  0.468922, 17.1012 to \
  0.469203, 17.1017 to \
  0.567296, 17.0965 to \
  0.567296, 17.0961 to \
  -7.25145, 2.94414 to \
  -7.34989, 2.87089 to \
  0.468922, 17.1012 front fs empty border lc rgb '#6165' lw 0.200001
set object 483 polygon from \
  0.370843, 17.1054 to \
  0.371103, 17.1059 to \
  0.469196, 17.1017 to \
  0.469196, 17.1013 to \
  -7.34955, 2.87114 to \
  -7.44799, 2.7969 to \
  0.370843, 17.1054 front fs empty border lc rgb '#6165' lw 0.200001
set object 484 polygon from \
  0.272742, 17.1086 to \
  0.273003, 17.1091 to \
  0.371096, 17.1059 to \
  0.371096, 17.1055 to \
  -7.44765, 2.79715 to \
  -7.54609, 2.72193 to \
  0.272742, 17.1086 front fs empty border lc rgb '#6165' lw 0.200001
set object 485 polygon from \
  0.17464, 17.1109 to \
  0.174903, 17.1114 to \
  0.272996, 17.1091 to \
  0.272996, 17.1087 to \
  -7.54575, 2.72218 to \
  -7.64419, 2.64597 to \
  0.17464, 17.1109 front fs empty border lc rgb '#6165' lw 0.200001
set object 486 polygon from \
  0.0765455, 17.1121 to \
  0.0768025, 17.1126 to \
  0.174896, 17.1114 to \
  0.174896, 17.111 to \
  -7.64385, 2.64623 to \
  -7.74229, 2.56904 to \
  0.0765455, 17.1121 front fs empty border lc rgb '#6165' lw 0.200001
set object 487 polygon from \
  -0.0215382, 17.1124 to \
  -0.0212976, 17.1129 to \
  0.076796, 17.1126 to \
  0.076796, 17.1122 to \
  -7.74195, 2.56931 to \
  -7.84039, 2.49113 to \
  -0.0215382, 17.1124 front fs empty border lc rgb '#6165' lw 0.200001
set object 488 polygon from \
  -0.11965, 17.1117 to \
  -0.119397, 17.1122 to \
  -0.021304, 17.1129 to \
  -0.021304, 17.1125 to \
  -7.84005, 2.4914 to \
  -7.93849, 2.41223 to \
  -0.11965, 17.1117 front fs empty border lc rgb '#6165' lw 0.200001
set object 489 polygon from \
  -0.217745, 17.11 to \
  -0.217497, 17.1105 to \
  -0.119404, 17.1122 to \
  -0.119404, 17.1118 to \
  -7.93815, 2.4125 to \
  -8.03659, 2.33236 to \
  -0.217745, 17.11 front fs empty border lc rgb '#6165' lw 0.200001
set object 490 polygon from \
  -0.315853, 17.1074 to \
  -0.315597, 17.1078 to \
  -0.217504, 17.1105 to \
  -0.217504, 17.1101 to \
  -8.03625, 2.33263 to \
  -8.13469, 2.2515 to \
  -0.315853, 17.1074 front fs empty border lc rgb '#6165' lw 0.200001
set object 491 polygon from \
  -0.413945, 17.1037 to \
  -0.413697, 17.1042 to \
  -0.315604, 17.1078 to \
  -0.315604, 17.1074 to \
  -8.13435, 2.25178 to \
  -8.23279, 2.16966 to \
  -0.413945, 17.1037 front fs empty border lc rgb '#6165' lw 0.200001
set object 492 polygon from \
  -0.512059, 17.0991 to \
  -0.511797, 17.0996 to \
  -0.413704, 17.1042 to \
  -0.413704, 17.1038 to \
  -8.23245, 2.16994 to \
  -8.33089, 2.08685 to \
  -0.512059, 17.0991 front fs empty border lc rgb '#6165' lw 0.200001
set object 493 polygon from \
  -0.61015, 17.0935 to \
  -0.609897, 17.094 to \
  -0.511804, 17.0996 to \
  -0.511804, 17.0992 to \
  -8.33055, 2.08713 to \
  -8.42899, 2.00305 to \
  -0.61015, 17.0935 front fs empty border lc rgb '#6165' lw 0.200001
set object 494 polygon from \
  -0.708247, 17.0869 to \
  -0.707997, 17.0874 to \
  -0.609904, 17.094 to \
  -0.609904, 17.0936 to \
  -8.42865, 2.00333 to \
  -8.52709, 1.91827 to \
  -0.708247, 17.0869 front fs empty border lc rgb '#6165' lw 0.200001
set object 495 polygon from \
  -0.806342, 17.0793 to \
  -0.806097, 17.0798 to \
  -0.708004, 17.0874 to \
  -0.708004, 17.087 to \
  -8.52675, 1.91856 to \
  -8.62519, 1.8325 to \
  -0.806342, 17.0793 front fs empty border lc rgb '#6165' lw 0.200001
set object 496 polygon from \
  -0.904455, 17.0707 to \
  -0.904197, 17.0713 to \
  -0.806104, 17.0798 to \
  -0.806104, 17.0794 to \
  -8.62485, 1.8328 to \
  -8.72329, 1.74576 to \
  -0.904455, 17.0707 front fs empty border lc rgb '#6165' lw 0.200001
set object 497 polygon from \
  -1.00255, 17.0612 to \
  -1.00229, 17.0617 to \
  -0.904204, 17.0713 to \
  -0.904204, 17.0708 to \
  -8.72295, 1.74606 to \
  -8.82139, 1.65804 to \
  -1.00255, 17.0612 front fs empty border lc rgb '#6165' lw 0.200001
set object 498 polygon from \
  -1.10067, 17.0507 to \
  -1.10039, 17.0512 to \
  -1.0023, 17.0617 to \
  -1.0023, 17.0613 to \
  -8.82105, 1.65834 to \
  -8.91949, 1.56933 to \
  -1.10067, 17.0507 front fs empty border lc rgb '#6165' lw 0.200001
set object 499 polygon from \
  -1.19878, 17.0391 to \
  -1.19849, 17.0397 to \
  -1.1004, 17.0512 to \
  -1.1004, 17.0508 to \
  -8.91915, 1.56964 to \
  -9.01759, 1.47965 to \
  -1.19878, 17.0391 front fs empty border lc rgb '#6165' lw 0.200001
set object 500 polygon from \
  -1.29688, 17.0267 to \
  -1.29659, 17.0272 to \
  -1.1985, 17.0397 to \
  -1.1985, 17.0393 to \
  -9.01725, 1.47996 to \
  -9.11569, 1.38898 to \
  -1.29688, 17.0267 front fs empty border lc rgb '#6165' lw 0.200001
set object 501 polygon from \
  -1.395, 17.0132 to \
  -1.39469, 17.0138 to \
  -1.2966, 17.0272 to \
  -1.2966, 17.0268 to \
  -9.11535, 1.38929 to \
  -9.21379, 1.29733 to \
  -1.395, 17.0132 front fs empty border lc rgb '#6165' lw 0.200001
set object 502 polygon from \
  -1.49311, 16.9987 to \
  -1.49279, 16.9993 to \
  -1.3947, 17.0138 to \
  -1.3947, 17.0134 to \
  -9.21345, 1.29765 to \
  -9.31189, 1.20471 to \
  -1.49311, 16.9987 front fs empty border lc rgb '#6165' lw 0.200001
set object 503 polygon from \
  -1.59122, 16.9833 to \
  -1.59089, 16.9839 to \
  -1.4928, 16.9993 to \
  -1.4928, 16.9989 to \
  -9.31155, 1.20502 to \
  -9.40999, 1.1111 to \
  -1.59122, 16.9833 front fs empty border lc rgb '#6165' lw 0.200001
set object 504 polygon from \
  -1.68932, 16.9669 to \
  -1.68899, 16.9675 to \
  -1.5909, 16.9839 to \
  -1.5909, 16.9835 to \
  -9.40965, 1.11142 to \
  -9.50809, 1.01651 to \
  -1.68932, 16.9669 front fs empty border lc rgb '#6165' lw 0.200001
set object 505 polygon from \
  -1.78742, 16.9495 to \
  -1.78709, 16.9501 to \
  -1.689, 16.9675 to \
  -1.689, 16.9671 to \
  -9.50775, 1.01683 to \
  -9.60619, 0.920929 to \
  -1.78742, 16.9495 front fs empty border lc rgb '#6165' lw 0.200001
set object 506 polygon from \
  -1.88552, 16.9311 to \
  -1.88519, 16.9318 to \
  -1.7871, 16.9501 to \
  -1.7871, 16.9497 to \
  -9.60585, 0.921259 to \
  -9.70429, 0.824377 to \
  -1.88552, 16.9311 front fs empty border lc rgb '#6165' lw 0.200001
set object 507 polygon from \
  -1.98366, 16.9117 to \
  -1.98329, 16.9124 to \
  -1.8852, 16.9318 to \
  -1.8852, 16.9314 to \
  -9.70395, 0.82471 to \
  -9.80239, 0.726843 to \
  -1.98366, 16.9117 front fs empty border lc rgb '#6165' lw 0.200001
set object 508 polygon from \
  -2.08176, 16.8914 to \
  -2.08139, 16.8921 to \
  -1.9833, 16.9124 to \
  -1.9833, 16.912 to \
  -9.80205, 0.72718 to \
  -9.90049, 0.628329 to \
  -2.08176, 16.8914 front fs empty border lc rgb '#6165' lw 0.200001
set object 509 polygon from \
  -2.17988, 16.87 to \
  -2.17949, 16.8708 to \
  -2.0814, 16.8921 to \
  -2.0814, 16.8917 to \
  -9.90015, 0.628669 to \
  -9.99859, 0.528833 to \
  -2.17988, 16.87 front fs empty border lc rgb '#6165' lw 0.200001
set object 510 polygon from \
  -2.27798, 16.8477 to \
  -2.27759, 16.8485 to \
  -2.1795, 16.8708 to \
  -2.1795, 16.8704 to \
  -9.99825, 0.529177 to \
  -10.0966, 0.428357 to \
  -2.27798, 16.8477 front fs empty border lc rgb '#6165' lw 0.200001
set object 511 polygon from \
  -2.37608, 16.8244 to \
  -2.37569, 16.8253 to \
  -2.2776, 16.8485 to \
  -2.2776, 16.8481 to \
  -10.0963, 0.428704 to \
  -10.1947, 0.326899 to \
  -2.37608, 16.8244 front fs empty border lc rgb '#6165' lw 0.200001
set object 512 polygon from \
  -2.47418, 16.8002 to \
  -2.47379, 16.801 to \
  -2.3757, 16.8253 to \
  -2.3757, 16.8248 to \
  -10.1944, 0.327249 to \
  -10.2928, 0.224461 to \
  -2.47418, 16.8002 front fs empty border lc rgb '#6165' lw 0.200001
set object 513 polygon from \
  -2.57231, 16.7749 to \
  -2.57189, 16.7758 to \
  -2.4738, 16.801 to \
  -2.4738, 16.8006 to \
  -10.2925, 0.224814 to \
  -10.3909, 0.121041 to \
  -2.57231, 16.7749 front fs empty border lc rgb '#6165' lw 0.200001
set object 514 polygon from \
  -2.67041, 16.7487 to \
  -2.66999, 16.7496 to \
  -2.5719, 16.7758 to \
  -2.5719, 16.7754 to \
  -10.3906, 0.121398 to \
  -10.489, 0.0166405 to \
  -2.67041, 16.7487 front fs empty border lc rgb '#6165' lw 0.200001
set object 515 polygon from \
  -2.76852, 16.7215 to \
  -2.76809, 16.7224 to \
  -2.67, 16.7496 to \
  -2.67, 16.7492 to \
  -10.4887, 0.0170009 to \
  -10.5045, 0 to \
  -10.5459, 0 to \
  -2.76852, 16.7215 front fs empty border lc rgb '#6165' lw 0.200001
set object 516 polygon from \
  -2.86662, 16.6933 to \
  -2.86619, 16.6942 to \
  -2.7681, 16.7224 to \
  -2.7681, 16.722 to \
  -10.5457, 0 to \
  -10.5949, 0 to \
  -2.86662, 16.6933 front fs empty border lc rgb '#6165' lw 0.200001
set object 517 polygon from \
  -2.96471, 16.6642 to \
  -2.96429, 16.6651 to \
  -2.8662, 16.6942 to \
  -2.8662, 16.6938 to \
  -10.5947, 0 to \
  -10.644, 0 to \
  -2.96471, 16.6642 front fs empty border lc rgb '#6165' lw 0.200001
set object 518 polygon from \
  -3.06283, 16.634 to \
  -3.06239, 16.6349 to \
  -2.9643, 16.6651 to \
  -2.9643, 16.6646 to \
  -10.6438, 0 to \
  -10.693, 0 to \
  -3.06283, 16.634 front fs empty border lc rgb '#6165' lw 0.200001
set object 519 polygon from \
  -3.16094, 16.6028 to \
  -3.16049, 16.6038 to \
  -3.0624, 16.6349 to \
  -3.0624, 16.6345 to \
  -10.6928, 0 to \
  -10.7421, 0 to \
  -3.16094, 16.6028 front fs empty border lc rgb '#6165' lw 0.200001
set object 520 polygon from \
  -3.25905, 16.5707 to \
  -3.25859, 16.5717 to \
  -3.1605, 16.6038 to \
  -3.1605, 16.6034 to \
  -10.7419, 0 to \
  -10.7911, 0 to \
  -3.25905, 16.5707 front fs empty border lc rgb '#6165' lw 0.200001
set object 521 polygon from \
  -3.35719, 16.5376 to \
  -3.35669, 16.5386 to \
  -3.2586, 16.5717 to \
  -3.2586, 16.5713 to \
  -10.7909, 0 to \
  -10.8402, 0 to \
  -3.35719, 16.5376 front fs empty border lc rgb '#6165' lw 0.200001
set object 522 polygon from \
  -3.45532, 16.5034 to \
  -3.45479, 16.5046 to \
  -3.3567, 16.5386 to \
  -3.3567, 16.5382 to \
  -10.84, 0 to \
  -10.8892, 0 to \
  -3.45532, 16.5034 front fs empty border lc rgb '#6165' lw 0.200001
set object 523 polygon from \
  -3.55346, 16.4683 to \
  -3.55289, 16.4695 to \
  -3.4548, 16.5046 to \
  -3.4548, 16.5042 to \
  -10.889, 0 to \
  -10.9383, 0 to \
  -3.55346, 16.4683 front fs empty border lc rgb '#6165' lw 0.200001
set object 524 polygon from \
  -3.65158, 16.4322 to \
  -3.65099, 16.4335 to \
  -3.5529, 16.4695 to \
  -3.5529, 16.4691 to \
  -10.9381, 0 to \
  -10.9873, 0 to \
  -3.65158, 16.4322 front fs empty border lc rgb '#6165' lw 0.200001
set object 525 polygon from \
  -3.74966, 16.3953 to \
  -3.74909, 16.3965 to \
  -3.651, 16.4335 to \
  -3.651, 16.4331 to \
  -10.9871, 0 to \
  -11.0364, 0 to \
  -3.74966, 16.3953 front fs empty border lc rgb '#6165' lw 0.200001
set object 526 polygon from \
  -3.8478, 16.3572 to \
  -3.84719, 16.3585 to \
  -3.7491, 16.3965 to \
  -3.7491, 16.3961 to \
  -11.0362, 0 to \
  -11.0854, 0 to \
  -3.8478, 16.3572 front fs empty border lc rgb '#6165' lw 0.200001
set object 527 polygon from \
  -3.94591, 16.3182 to \
  -3.94529, 16.3196 to \
  -3.8472, 16.3585 to \
  -3.8472, 16.3581 to \
  -11.0852, 0 to \
  -11.1345, 0 to \
  -3.94591, 16.3182 front fs empty border lc rgb '#6165' lw 0.200001
set object 528 polygon from \
  -4.04403, 16.2782 to \
  -4.04339, 16.2796 to \
  -3.9453, 16.3196 to \
  -3.9453, 16.3192 to \
  -11.1343, 0 to \
  -11.1835, 0 to \
  -4.04403, 16.2782 front fs empty border lc rgb '#6165' lw 0.200001
set object 529 polygon from \
  -4.14212, 16.2373 to \
  -4.14149, 16.2387 to \
  -4.0434, 16.2796 to \
  -4.0434, 16.2792 to \
  -11.1833, 0 to \
  -11.2326, 0 to \
  -4.14212, 16.2373 front fs empty border lc rgb '#6165' lw 0.200001
set object 530 polygon from \
  -4.2402, 16.1954 to \
  -4.23959, 16.1968 to \
  -4.1415, 16.2387 to \
  -4.1415, 16.2383 to \
  -11.2324, 0 to \
  -11.2816, 0 to \
  -4.2402, 16.1954 front fs empty border lc rgb '#6165' lw 0.200001
set object 531 polygon from \
  -4.33832, 16.1525 to \
  -4.33769, 16.1539 to \
  -4.2396, 16.1968 to \
  -4.2396, 16.1964 to \
  -11.2814, 0 to \
  -11.3307, 0 to \
  -4.33832, 16.1525 front fs empty border lc rgb '#6165' lw 0.200001
set object 532 polygon from \
  -4.43641, 16.1086 to \
  -4.43579, 16.1101 to \
  -4.3377, 16.1539 to \
  -4.3377, 16.1535 to \
  -11.3305, 0 to \
  -11.3797, 0 to \
  -4.43641, 16.1086 front fs empty border lc rgb '#6165' lw 0.200001
set object 533 polygon from \
  -4.53452, 16.0637 to \
  -4.53389, 16.0652 to \
  -4.4358, 16.1101 to \
  -4.4358, 16.1096 to \
  -11.3795, 0 to \
  -11.4288, 0 to \
  -4.53452, 16.0637 front fs empty border lc rgb '#6165' lw 0.200001
set object 534 polygon from \
  -4.63263, 16.0179 to \
  -4.63199, 16.0194 to \
  -4.5339, 16.0652 to \
  -4.5339, 16.0648 to \
  -11.4286, 0 to \
  -11.4778, 0 to \
  -4.63263, 16.0179 front fs empty border lc rgb '#6165' lw 0.200001
set object 535 polygon from \
  -4.73075, 15.971 to \
  -4.73009, 15.9726 to \
  -4.632, 16.0194 to \
  -4.632, 16.019 to \
  -11.4776, 0 to \
  -11.5269, 0 to \
  -4.73075, 15.971 front fs empty border lc rgb '#6165' lw 0.200001
set object 536 polygon from \
  -4.82888, 15.9232 to \
  -4.82819, 15.9248 to \
  -4.7301, 15.9726 to \
  -4.7301, 15.9721 to \
  -11.5267, 0 to \
  -11.5759, 0 to \
  -4.82888, 15.9232 front fs empty border lc rgb '#6165' lw 0.200001
set object 537 polygon from \
  -4.92699, 15.8744 to \
  -4.92629, 15.876 to \
  -4.8282, 15.9248 to \
  -4.8282, 15.9244 to \
  -11.5757, 0 to \
  -11.625, 0 to \
  -4.92699, 15.8744 front fs empty border lc rgb '#6165' lw 0.200001
set object 538 polygon from \
  -5.02514, 15.8245 to \
  -5.02439, 15.8263 to \
  -4.9263, 15.876 to \
  -4.9263, 15.8756 to \
  -11.6248, 0 to \
  -11.674, 0 to \
  -5.02514, 15.8245 front fs empty border lc rgb '#6165' lw 0.200001
set object 539 polygon from \
  -5.12326, 15.7737 to \
  -5.12249, 15.7755 to \
  -5.0244, 15.8262 to \
  -5.0244, 15.8258 to \
  -11.6738, 0 to \
  -11.7231, 0 to \
  -5.12326, 15.7737 front fs empty border lc rgb '#6165' lw 0.200001
set object 540 polygon from \
  -5.22137, 15.722 to \
  -5.22059, 15.7238 to \
  -5.1225, 15.7755 to \
  -5.1225, 15.7751 to \
  -11.7229, 0 to \
  -11.7721, 0 to \
  -5.22137, 15.722 front fs empty border lc rgb '#6165' lw 0.200001
set object 541 polygon from \
  -5.31947, 15.6693 to \
  -5.31869, 15.6711 to \
  -5.2206, 15.7238 to \
  -5.2206, 15.7234 to \
  -11.7719, 0 to \
  -11.8212, 0 to \
  -5.31947, 15.6693 front fs empty border lc rgb '#6165' lw 0.200001
set object 542 polygon from \
  -5.41759, 15.6155 to \
  -5.41679, 15.6174 to \
  -5.3187, 15.6711 to \
  -5.3187, 15.6707 to \
  -11.821, 0 to \
  -11.8702, 0 to \
  -5.41759, 15.6155 front fs empty border lc rgb '#6165' lw 0.200001
set object 543 polygon from \
  -5.51571, 15.5608 to \
  -5.51489, 15.5628 to \
  -5.4168, 15.6174 to \
  -5.4168, 15.617 to \
  -11.87, 0 to \
  -11.9193, 0 to \
  -5.51571, 15.5608 front fs empty border lc rgb '#6165' lw 0.200001
set object 544 polygon from \
  -5.61381, 15.5051 to \
  -5.61299, 15.5071 to \
  -5.5149, 15.5628 to \
  -5.5149, 15.5623 to \
  -11.9191, 0 to \
  -11.9683, 0 to \
  -5.61381, 15.5051 front fs empty border lc rgb '#6165' lw 0.200001
set object 545 polygon from \
  -5.71193, 15.4485 to \
  -5.71109, 15.4505 to \
  -5.613, 15.5071 to \
  -5.613, 15.5067 to \
  -11.9681, 0 to \
  -12.0174, 0 to \
  -5.71193, 15.4485 front fs empty border lc rgb '#6165' lw 0.200001
set object 546 polygon from \
  -5.81001, 15.3909 to \
  -5.80919, 15.3929 to \
  -5.7111, 15.4505 to \
  -5.7111, 15.4501 to \
  -12.0172, 0 to \
  -12.0664, 0 to \
  -5.81001, 15.3909 front fs empty border lc rgb '#6165' lw 0.200001
set object 547 polygon from \
  -5.90814, 15.3322 to \
  -5.90729, 15.3343 to \
  -5.8092, 15.3929 to \
  -5.8092, 15.3925 to \
  -12.0662, 0 to \
  -12.1155, 0 to \
  -5.90814, 15.3322 front fs empty border lc rgb '#6165' lw 0.200001
set object 548 polygon from \
  -6.00626, 15.2726 to \
  -6.00539, 15.2748 to \
  -5.9073, 15.3343 to \
  -5.9073, 15.3339 to \
  -12.1153, 0 to \
  -12.1645, 0 to \
  -6.00626, 15.2726 front fs empty border lc rgb '#6165' lw 0.200001
set object 549 polygon from \
  -6.10437, 15.2121 to \
  -6.10349, 15.2142 to \
  -6.0054, 15.2748 to \
  -6.0054, 15.2743 to \
  -12.1643, 0 to \
  -12.2136, 0 to \
  -6.10437, 15.2121 front fs empty border lc rgb '#6165' lw 0.200001
set object 550 polygon from \
  -6.20247, 15.1505 to \
  -6.20159, 15.1527 to \
  -6.1035, 15.2142 to \
  -6.1035, 15.2138 to \
  -12.2134, 0 to \
  -12.2626, 0 to \
  -6.20247, 15.1505 front fs empty border lc rgb '#6165' lw 0.200001
set object 551 polygon from \
  -6.30059, 15.088 to \
  -6.29969, 15.0902 to \
  -6.2016, 15.1527 to \
  -6.2016, 15.1523 to \
  -12.2624, 0 to \
  -12.3117, 0 to \
  -6.30059, 15.088 front fs empty border lc rgb '#6165' lw 0.200001
set object 552 polygon from \
  -6.39871, 15.0244 to \
  -6.39779, 15.0267 to \
  -6.2997, 15.0902 to \
  -6.2997, 15.0898 to \
  -12.3115, 0 to \
  -12.3607, 0 to \
  -6.39871, 15.0244 front fs empty border lc rgb '#6165' lw 0.200001
set object 553 polygon from \
  -6.49684, 14.9598 to \
  -6.49589, 14.9622 to \
  -6.3978, 15.0267 to \
  -6.3978, 15.0263 to \
  -12.3605, 0 to \
  -12.4097, 0 to \
  -6.49684, 14.9598 front fs empty border lc rgb '#6165' lw 0.200001
set object 554 polygon from \
  -6.59498, 14.8943 to \
  -6.59399, 14.8968 to \
  -6.4959, 14.9622 to \
  -6.4959, 14.9618 to \
  -12.4096, 0 to \
  -12.4588, 0 to \
  -6.59498, 14.8943 front fs empty border lc rgb '#6165' lw 0.200001
set object 555 polygon from \
  -6.69308, 14.8279 to \
  -6.69209, 14.8304 to \
  -6.594, 14.8968 to \
  -6.594, 14.8963 to \
  -12.4586, 0 to \
  -12.5078, 0 to \
  -6.69308, 14.8279 front fs empty border lc rgb '#6165' lw 0.200001
set object 556 polygon from \
  -6.79117, 14.7604 to \
  -6.79019, 14.7629 to \
  -6.6921, 14.8303 to \
  -6.6921, 14.8299 to \
  -12.5077, 0 to \
  -12.5569, 0 to \
  -6.79117, 14.7604 front fs empty border lc rgb '#6165' lw 0.200001
set object 557 polygon from \
  -6.88926, 14.6921 to \
  -6.88829, 14.6945 to \
  -6.7902, 14.7629 to \
  -6.7902, 14.7625 to \
  -12.5567, 0 to \
  -12.6059, 0 to \
  -6.88926, 14.6921 front fs empty border lc rgb '#6165' lw 0.200001
set object 558 polygon from \
  -6.98736, 14.6227 to \
  -6.98639, 14.6252 to \
  -6.8883, 14.6945 to \
  -6.8883, 14.6941 to \
  -12.6058, 0 to \
  -12.655, 0 to \
  -6.98736, 14.6227 front fs empty border lc rgb '#6165' lw 0.200001
set object 559 polygon from \
  -7.08549, 14.5523 to \
  -7.08449, 14.5548 to \
  -6.9864, 14.6252 to \
  -6.9864, 14.6247 to \
  -12.6548, 0 to \
  -12.704, 0 to \
  -7.08549, 14.5523 front fs empty border lc rgb '#6165' lw 0.200001
set object 560 polygon from \
  -7.18363, 14.4808 to \
  -7.18259, 14.4835 to \
  -7.0845, 14.5548 to \
  -7.0845, 14.5544 to \
  -12.7039, 0 to \
  -12.7531, 0 to \
  -7.18363, 14.4808 front fs empty border lc rgb '#6165' lw 0.200001
set object 561 polygon from \
  -7.28175, 14.4084 to \
  -7.2807, 14.4112 to \
  -7.1826, 14.4835 to \
  -7.1826, 14.483 to \
  -12.7529, 0 to \
  -12.8021, 0 to \
  -7.28175, 14.4084 front fs empty border lc rgb '#6165' lw 0.200001
set object 562 polygon from \
  -7.37991, 14.335 to \
  -7.37879, 14.3379 to \
  -7.2807, 14.4112 to \
  -7.2807, 14.4107 to \
  -12.802, 0 to \
  -12.8512, 0 to \
  -7.37991, 14.335 front fs empty border lc rgb '#6165' lw 0.200001
set object 563 polygon from \
  -7.478, 14.2607 to \
  -7.4769, 14.2636 to \
  -7.3788, 14.3379 to \
  -7.3788, 14.3374 to \
  -12.851, 0 to \
  -12.9002, 0 to \
  -7.478, 14.2607 front fs empty border lc rgb '#6165' lw 0.200001
set object 564 polygon from \
  -7.57616, 14.1853 to \
  -7.575, 14.1883 to \
  -7.4769, 14.2636 to \
  -7.4769, 14.2632 to \
  -12.9001, 0 to \
  -12.9493, 0 to \
  -7.57616, 14.1853 front fs empty border lc rgb '#6165' lw 0.200001
set object 565 polygon from \
  -7.67427, 14.109 to \
  -7.6731, 14.1121 to \
  -7.575, 14.1883 to \
  -7.575, 14.1879 to \
  -12.9491, 0 to \
  -12.9983, 0 to \
  -7.67427, 14.109 front fs empty border lc rgb '#6165' lw 0.200001
set object 566 polygon from \
  -7.77237, 14.0317 to \
  -7.7712, 14.0349 to \
  -7.6731, 14.1121 to \
  -7.6731, 14.1117 to \
  -12.9982, 0 to \
  -13.0474, 0 to \
  -7.77237, 14.0317 front fs empty border lc rgb '#6165' lw 0.200001
set object 567 polygon from \
  -7.87052, 13.9534 to \
  -7.8693, 13.9567 to \
  -7.7712, 14.0349 to \
  -7.7712, 14.0344 to \
  -13.0472, 0 to \
  -13.0964, 0 to \
  -7.87052, 13.9534 front fs empty border lc rgb '#6165' lw 0.200001
set object 568 polygon from \
  -7.96866, 13.8741 to \
  -7.96739, 13.8775 to \
  -7.8693, 13.9567 to \
  -7.8693, 13.9562 to \
  -13.0963, 0 to \
  -13.1455, 0 to \
  -7.96866, 13.8741 front fs empty border lc rgb '#6165' lw 0.200001
set object 569 polygon from \
  -8.0668, 13.7938 to \
  -8.0655, 13.7973 to \
  -7.9674, 13.8775 to \
  -7.9674, 13.877 to \
  -13.1453, 0 to \
  -13.1945, 0 to \
  -8.0668, 13.7938 front fs empty border lc rgb '#6165' lw 0.200001
set object 570 polygon from \
  -8.1649, 13.7127 to \
  -8.1636, 13.7162 to \
  -8.0655, 13.7973 to \
  -8.0655, 13.7969 to \
  -13.1944, 0 to \
  -13.2436, 0 to \
  -8.1649, 13.7127 front fs empty border lc rgb '#6165' lw 0.200001
set object 571 polygon from \
  -8.26304, 13.6304 to \
  -8.2617, 13.634 to \
  -8.1636, 13.7162 to \
  -8.1636, 13.7157 to \
  -13.2434, 0 to \
  -13.2926, 0 to \
  -8.26304, 13.6304 front fs empty border lc rgb '#6165' lw 0.200001
set object 572 polygon from \
  -8.36115, 13.5473 to \
  -8.3598, 13.5509 to \
  -8.2617, 13.634 to \
  -8.2617, 13.6336 to \
  -13.2925, 0 to \
  -13.3417, 0 to \
  -8.36115, 13.5473 front fs empty border lc rgb '#6165' lw 0.200001
set object 573 polygon from \
  -8.45929, 13.4631 to \
  -8.4579, 13.4669 to \
  -8.3598, 13.5509 to \
  -8.3598, 13.5505 to \
  -13.3415, 0 to \
  -13.3907, 0 to \
  -8.45929, 13.4631 front fs empty border lc rgb '#6165' lw 0.200001
set object 574 polygon from \
  -8.5574, 13.3779 to \
  -8.556, 13.3818 to \
  -8.4579, 13.4668 to \
  -8.4579, 13.4664 to \
  -13.3906, 0 to \
  -13.4398, 0 to \
  -8.5574, 13.3779 front fs empty border lc rgb '#6165' lw 0.200001
set object 575 polygon from \
  -8.65552, 13.2918 to \
  -8.6541, 13.2957 to \
  -8.556, 13.3818 to \
  -8.556, 13.3813 to \
  -13.4396, 0 to \
  -13.4888, 0 to \
  -8.65552, 13.2918 front fs empty border lc rgb '#6165' lw 0.200001
set object 576 polygon from \
  -8.75364, 13.2047 to \
  -8.7522, 13.2087 to \
  -8.6541, 13.2957 to \
  -8.6541, 13.2953 to \
  -13.4887, 0 to \
  -13.5379, 0 to \
  -8.75364, 13.2047 front fs empty border lc rgb '#6165' lw 0.200001
set object 577 polygon from \
  -8.85179, 13.1166 to \
  -8.8503, 13.1207 to \
  -8.7522, 13.2087 to \
  -8.7522, 13.2083 to \
  -13.5377, 0 to \
  -13.5869, 0 to \
  -8.85179, 13.1166 front fs empty border lc rgb '#6165' lw 0.200001
set object 578 polygon from \
  -8.94989, 13.0275 to \
  -8.9484, 13.0317 to \
  -8.8503, 13.1207 to \
  -8.8503, 13.1202 to \
  -13.5868, 0 to \
  -13.636, 0 to \
  -8.94989, 13.0275 front fs empty border lc rgb '#6165' lw 0.200001
set object 579 polygon from \
  -9.04801, 12.9375 to \
  -9.0465, 12.9417 to \
  -8.9484, 13.0317 to \
  -8.9484, 13.0312 to \
  -13.6358, 0 to \
  -13.685, 0 to \
  -9.04801, 12.9375 front fs empty border lc rgb '#6165' lw 0.200001
set object 580 polygon from \
  -9.14612, 12.8465 to \
  -9.1446, 12.8508 to \
  -9.0465, 12.9417 to \
  -9.0465, 12.9413 to \
  -13.6849, 0 to \
  -13.7341, 0 to \
  -9.14612, 12.8465 front fs empty border lc rgb '#6165' lw 0.200001
set object 581 polygon from \
  -9.24422, 12.7546 to \
  -9.2427, 12.7588 to \
  -9.1446, 12.8508 to \
  -9.1446, 12.8503 to \
  -13.7339, 0 to \
  -13.7831, 0 to \
  -9.24422, 12.7546 front fs empty border lc rgb '#6165' lw 0.200001
set object 582 polygon from \
  -9.34235, 12.6616 to \
  -9.3408, 12.6659 to \
  -9.2427, 12.7588 to \
  -9.2427, 12.7584 to \
  -13.783, 0 to \
  -13.8322, 0 to \
  -9.34235, 12.6616 front fs empty border lc rgb '#6165' lw 0.200001
set object 583 polygon from \
  -9.44047, 12.5676 to \
  -9.4389, 12.572 to \
  -9.3408, 12.6659 to \
  -9.3408, 12.6655 to \
  -13.832, 0 to \
  -13.8812, 0 to \
  -9.44047, 12.5676 front fs empty border lc rgb '#6165' lw 0.200001
set object 584 polygon from \
  -9.53861, 12.4726 to \
  -9.537, 12.4771 to \
  -9.4389, 12.572 to \
  -9.4389, 12.5716 to \
  -13.8811, 0 to \
  -13.9303, 0 to \
  -9.53861, 12.4726 front fs empty border lc rgb '#6165' lw 0.200001
set object 585 polygon from \
  -9.63675, 12.3766 to \
  -9.6351, 12.3813 to \
  -9.537, 12.4771 to \
  -9.537, 12.4767 to \
  -13.9301, 0 to \
  -13.9793, 0 to \
  -9.63675, 12.3766 front fs empty border lc rgb '#6165' lw 0.200001
set object 586 polygon from \
  -9.7349, 12.2796 to \
  -9.7332, 12.2844 to \
  -9.6351, 12.3813 to \
  -9.6351, 12.3808 to \
  -13.9792, 0 to \
  -14.0284, 0 to \
  -9.7349, 12.2796 front fs empty border lc rgb '#6165' lw 0.200001
set object 587 polygon from \
  -9.833, 12.1817 to \
  -9.8313, 12.1866 to \
  -9.7332, 12.2844 to \
  -9.7332, 12.284 to \
  -14.0282, 0 to \
  -14.0774, 0 to \
  -9.833, 12.1817 front fs empty border lc rgb '#6165' lw 0.200001
set object 588 polygon from \
  -9.93111, 12.0829 to \
  -9.9294, 12.0878 to \
  -9.8313, 12.1866 to \
  -9.8313, 12.1862 to \
  -14.0773, 0 to \
  -14.1265, 0 to \
  -9.93111, 12.0829 front fs empty border lc rgb '#6165' lw 0.200001
set object 589 polygon from \
  -10.0292, 11.9831 to \
  -10.0275, 11.988 to \
  -9.9294, 12.0878 to \
  -9.9294, 12.0874 to \
  -14.1263, 0 to \
  -14.1755, 0 to \
  -10.0292, 11.9831 front fs empty border lc rgb '#6165' lw 0.200001
set object 590 polygon from \
  -10.1273, 11.8822 to \
  -10.1256, 11.8873 to \
  -10.0275, 11.988 to \
  -10.0275, 11.9876 to \
  -14.1754, 0 to \
  -14.2246, 0 to \
  -10.1273, 11.8822 front fs empty border lc rgb '#6165' lw 0.200001
set object 591 polygon from \
  -10.2254, 11.7803 to \
  -10.2237, 11.7855 to \
  -10.1256, 11.8873 to \
  -10.1256, 11.8868 to \
  -14.2244, 0 to \
  -14.2736, 0 to \
  -10.2254, 11.7803 front fs empty border lc rgb '#6165' lw 0.200001
set object 592 polygon from \
  -10.3236, 11.6775 to \
  -10.3218, 11.6828 to \
  -10.2237, 11.7855 to \
  -10.2237, 11.7851 to \
  -14.2735, 0 to \
  -14.3227, 0 to \
  -10.3236, 11.6775 front fs empty border lc rgb '#6165' lw 0.200001
set object 593 polygon from \
  -10.4217, 11.5737 to \
  -10.4199, 11.5791 to \
  -10.3218, 11.6828 to \
  -10.3218, 11.6823 to \
  -14.3225, 0 to \
  -14.3717, 0 to \
  -10.4217, 11.5737 front fs empty border lc rgb '#6165' lw 0.200001
set object 594 polygon from \
  -10.5198, 11.469 to \
  -10.518, 11.4744 to \
  -10.4199, 11.5791 to \
  -10.4199, 11.5786 to \
  -14.3716, 0 to \
  -14.4208, 0 to \
  -10.5198, 11.469 front fs empty border lc rgb '#6165' lw 0.200001
set object 595 polygon from \
  -10.6179, 11.3632 to \
  -10.6161, 11.3687 to \
  -10.518, 11.4744 to \
  -10.518, 11.4739 to \
  -14.4206, 0 to \
  -14.4698, 0 to \
  -10.6179, 11.3632 front fs empty border lc rgb '#6165' lw 0.200001
set object 596 polygon from \
  -10.7161, 11.2564 to \
  -10.7142, 11.2621 to \
  -10.6161, 11.3687 to \
  -10.6161, 11.3683 to \
  -14.4697, 0 to \
  -14.5189, 0 to \
  -10.7161, 11.2564 front fs empty border lc rgb '#6165' lw 0.200001
set object 597 polygon from \
  -10.8142, 11.1487 to \
  -10.8123, 11.1544 to \
  -10.7142, 11.2621 to \
  -10.7142, 11.2616 to \
  -14.5187, 0 to \
  -14.5679, 0 to \
  -10.8142, 11.1487 front fs empty border lc rgb '#6165' lw 0.200001
set object 598 polygon from \
  -10.9123, 11.04 to \
  -10.9104, 11.0458 to \
  -10.8123, 11.1544 to \
  -10.8123, 11.154 to \
  -14.5678, 0 to \
  -14.617, 0 to \
  -10.9123, 11.04 front fs empty border lc rgb '#6165' lw 0.200001
set object 599 polygon from \
  -11.0104, 10.9305 to \
  -11.0085, 10.9362 to \
  -10.9104, 11.0458 to \
  -10.9104, 11.0454 to \
  -14.6168, 0 to \
  -14.666, 0 to \
  -11.0104, 10.9305 front fs empty border lc rgb '#6165' lw 0.200001
set object 600 polygon from \
  -11.1085, 10.8198 to \
  -11.1066, 10.8256 to \
  -11.0085, 10.9362 to \
  -11.0085, 10.9358 to \
  -14.6659, 0 to \
  -14.7151, 0 to \
  -11.1085, 10.8198 front fs empty border lc rgb '#6165' lw 0.200001
set object 601 polygon from \
  10.9014, 0.109874 to \
  10.9016, 0.109874 to \
  10.9997, 0.000368285 to \
  10.9997, 0 to \
  7.87786, 0 to \
  7.77931, 0.0786531 to \
  10.9014, 0.109874 front fs empty border lc rgb '#6165' lw 0.200001
set object 602 polygon from \
  10.8033, 0.218397 to \
  10.8035, 0.218399 to \
  10.9016, 0.109875 to \
  10.9016, 0.109507 to \
  7.77976, 0.0782881 to \
  7.68121, 0.155956 to \
  10.8033, 0.218397 front fs empty border lc rgb '#6165' lw 0.200001
set object 603 polygon from \
  10.7052, 0.325939 to \
  10.7054, 0.325944 to \
  10.8035, 0.2184 to \
  10.8035, 0.218032 to \
  7.68166, 0.155596 to \
  7.58311, 0.232278 to \
  10.7052, 0.325939 front fs empty border lc rgb '#6165' lw 0.200001
set object 604 polygon from \
  10.6071, 0.4325 to \
  10.6073, 0.432507 to \
  10.7054, 0.325945 to \
  10.7054, 0.325577 to \
  7.58356, 0.231922 to \
  7.48501, 0.307618 to \
  10.6071, 0.4325 front fs empty border lc rgb '#6165' lw 0.200001
set object 605 polygon from \
  10.509, 0.538079 to \
  10.5092, 0.538089 to \
  10.6073, 0.432508 to \
  10.6073, 0.43214 to \
  7.48546, 0.307267 to \
  7.38691, 0.381978 to \
  10.509, 0.538079 front fs empty border lc rgb '#6165' lw 0.200001
set object 606 polygon from \
  10.4109, 0.642678 to \
  10.4111, 0.642691 to \
  10.5092, 0.538091 to \
  10.5092, 0.537722 to \
  7.38736, 0.381631 to \
  7.28881, 0.455356 to \
  10.4109, 0.642678 front fs empty border lc rgb '#6165' lw 0.200001
set object 607 polygon from \
  10.3128, 0.746296 to \
  10.313, 0.746311 to \
  10.4111, 0.642692 to \
  10.4111, 0.642324 to \
  7.28926, 0.455014 to \
  7.19071, 0.527754 to \
  10.3128, 0.746296 front fs empty border lc rgb '#6165' lw 0.200001
set object 608 polygon from \
  10.2147, 0.848933 to \
  10.2149, 0.84895 to \
  10.313, 0.746312 to \
  10.313, 0.745944 to \
  7.19116, 0.527416 to \
  7.09261, 0.59917 to \
  10.2147, 0.848933 front fs empty border lc rgb '#6165' lw 0.200001
set object 609 polygon from \
  10.1166, 0.950589 to \
  10.1168, 0.950609 to \
  10.2149, 0.848952 to \
  10.2149, 0.848583 to \
  7.09306, 0.598837 to \
  6.99451, 0.669606 to \
  10.1166, 0.950589 front fs empty border lc rgb '#6165' lw 0.200001
set object 610 polygon from \
  10.0185, 1.05127 to \
  10.0187, 1.05129 to \
  10.1168, 0.95061 to \
  10.1168, 0.950242 to \
  6.99496, 0.669277 to \
  6.89641, 0.73906 to \
  10.0185, 1.05127 front fs empty border lc rgb '#6165' lw 0.200001
set object 611 polygon from \
  9.92034, 1.15096 to \
  9.92059, 1.15099 to \
  10.0187, 1.05129 to \
  10.0187, 1.05092 to \
  6.89686, 0.738736 to \
  6.79831, 0.807534 to \
  9.92034, 1.15096 front fs empty border lc rgb '#6165' lw 0.200001
set object 612 polygon from \
  9.82224, 1.24968 to \
  9.82249, 1.2497 to \
  9.92059, 1.15099 to \
  9.92059, 1.15062 to \
  6.79876, 0.807214 to \
  6.70021, 0.875026 to \
  9.82224, 1.24968 front fs empty border lc rgb '#6165' lw 0.200001
set object 613 polygon from \
  9.72414, 1.34741 to \
  9.72439, 1.34744 to \
  9.82249, 1.2497 to \
  9.82249, 1.24934 to \
  6.70066, 0.874711 to \
  6.60211, 0.941538 to \
  9.72414, 1.34741 front fs empty border lc rgb '#6165' lw 0.200001
set object 614 polygon from \
  9.62604, 1.44416 to \
  9.62629, 1.44419 to \
  9.72439, 1.34744 to \
  9.72439, 1.34707 to \
  6.60256, 0.941227 to \
  6.50401, 1.00707 to \
  9.62604, 1.44416 front fs empty border lc rgb '#6165' lw 0.200001
set object 615 polygon from \
  9.52794, 1.53993 to \
  9.52819, 1.53996 to \
  9.62629, 1.44419 to \
  9.62629, 1.44382 to \
  6.50446, 1.00677 to \
  6.40591, 1.07162 to \
  9.52794, 1.53993 front fs empty border lc rgb '#6165' lw 0.200001
set object 616 polygon from \
  9.42984, 1.63472 to \
  9.43009, 1.63475 to \
  9.52819, 1.53996 to \
  9.52819, 1.5396 to \
  6.40636, 1.07132 to \
  6.30781, 1.13519 to \
  9.42984, 1.63472 front fs empty border lc rgb '#6165' lw 0.200001
set object 617 polygon from \
  9.33174, 1.72852 to \
  9.33199, 1.72856 to \
  9.43009, 1.63475 to \
  9.43009, 1.63439 to \
  6.30826, 1.13489 to \
  6.20971, 1.19778 to \
  9.33174, 1.72852 front fs empty border lc rgb '#6165' lw 0.200001
set object 618 polygon from \
  9.23364, 1.82135 to \
  9.23389, 1.82139 to \
  9.33199, 1.72857 to \
  9.33199, 1.7282 to \
  6.21016, 1.19749 to \
  6.11161, 1.25938 to \
  9.23364, 1.82135 front fs empty border lc rgb '#6165' lw 0.200001
set object 619 polygon from \
  9.13554, 1.9132 to \
  9.13579, 1.91324 to \
  9.23389, 1.82139 to \
  9.23389, 1.82103 to \
  6.11206, 1.2591 to \
  6.01351, 1.32001 to \
  9.13554, 1.9132 front fs empty border lc rgb '#6165' lw 0.200001
set object 620 polygon from \
  9.03744, 2.00406 to \
  9.03769, 2.00411 to \
  9.13579, 1.91324 to \
  9.13579, 1.91287 to \
  6.01396, 1.31973 to \
  5.91541, 1.37965 to \
  9.03744, 2.00406 front fs empty border lc rgb '#6165' lw 0.200001
set object 621 polygon from \
  8.93934, 2.09395 to \
  8.93959, 2.094 to \
  9.03769, 2.00411 to \
  9.03769, 2.00374 to \
  5.91586, 1.37938 to \
  5.81731, 1.43832 to \
  8.93934, 2.09395 front fs empty border lc rgb '#6165' lw 0.200001
set object 622 polygon from \
  8.84124, 2.18285 to \
  8.84149, 2.1829 to \
  8.93959, 2.094 to \
  8.93959, 2.09363 to \
  5.81776, 1.43804 to \
  5.71921, 1.496 to \
  8.84124, 2.18285 front fs empty border lc rgb '#6165' lw 0.200001
set object 623 polygon from \
  8.74314, 2.27077 to \
  8.74339, 2.27083 to \
  8.84149, 2.1829 to \
  8.84149, 2.18253 to \
  5.71966, 1.49573 to \
  5.62111, 1.5527 to \
  8.74314, 2.27077 front fs empty border lc rgb '#6165' lw 0.200001
set object 624 polygon from \
  8.64504, 2.35771 to \
  8.64529, 2.35777 to \
  8.74339, 2.27083 to \
  8.74339, 2.27046 to \
  5.62156, 1.55244 to \
  5.52301, 1.60842 to \
  8.64504, 2.35771 front fs empty border lc rgb '#6165' lw 0.200001
set object 625 polygon from \
  8.54694, 2.44367 to \
  8.54719, 2.44373 to \
  8.64529, 2.35777 to \
  8.64529, 2.3574 to \
  5.52346, 1.60816 to \
  5.42491, 1.66316 to \
  8.54694, 2.44367 front fs empty border lc rgb '#6165' lw 0.200001
set object 626 polygon from \
  8.44884, 2.52865 to \
  8.44909, 2.52871 to \
  8.54719, 2.44373 to \
  8.54719, 2.44336 to \
  5.42536, 1.66291 to \
  5.32681, 1.71692 to \
  8.44884, 2.52865 front fs empty border lc rgb '#6165' lw 0.200001
set object 627 polygon from \
  8.35074, 2.61265 to \
  8.35099, 2.61271 to \
  8.44909, 2.52871 to \
  8.44909, 2.52835 to \
  5.32726, 1.71667 to \
  5.22871, 1.7697 to \
  8.35074, 2.61265 front fs empty border lc rgb '#6165' lw 0.200001
set object 628 polygon from \
  8.25264, 2.69567 to \
  8.25289, 2.69573 to \
  8.35099, 2.61271 to \
  8.35099, 2.61235 to \
  5.22916, 1.76945 to \
  5.13061, 1.8215 to \
  8.25264, 2.69567 front fs empty border lc rgb '#6165' lw 0.200001
set object 629 polygon from \
  8.15454, 2.7777 to \
  8.15479, 2.77777 to \
  8.25289, 2.69573 to \
  8.25289, 2.69536 to \
  5.13106, 1.82125 to \
  5.03251, 1.87231 to \
  8.15454, 2.7777 front fs empty border lc rgb '#6165' lw 0.200001
set object 630 polygon from \
  8.05644, 2.85876 to \
  8.05669, 2.85883 to \
  8.15479, 2.77777 to \
  8.15479, 2.7774 to \
  5.03296, 1.87207 to \
  4.93441, 1.92215 to \
  8.05644, 2.85876 front fs empty border lc rgb '#6165' lw 0.200001
set object 631 polygon from \
  7.95834, 2.93883 to \
  7.95859, 2.9389 to \
  8.05669, 2.85883 to \
  8.05669, 2.85846 to \
  4.93486, 1.92191 to \
  4.83631, 1.971 to \
  7.95834, 2.93883 front fs empty border lc rgb '#6165' lw 0.200001
set object 632 polygon from \
  7.86024, 3.01792 to \
  7.86049, 3.018 to \
  7.95859, 2.93891 to \
  7.95859, 2.93854 to \
  4.83676, 1.97077 to \
  4.73821, 2.01887 to \
  7.86024, 3.01792 front fs empty border lc rgb '#6165' lw 0.200001
set object 633 polygon from \
  7.76214, 3.09603 to \
  7.76239, 3.09611 to \
  7.86049, 3.018 to \
  7.86049, 3.01763 to \
  4.73866, 2.01865 to \
  4.64011, 2.06576 to \
  7.76214, 3.09603 front fs empty border lc rgb '#6165' lw 0.200001
set object 634 polygon from \
  7.66404, 3.17317 to \
  7.66429, 3.17325 to \
  7.76239, 3.09612 to \
  7.76239, 3.09575 to \
  4.64056, 2.06554 to \
  4.54201, 2.11167 to \
  7.66404, 3.17317 front fs empty border lc rgb '#6165' lw 0.200001
set object 635 polygon from \
  7.56594, 3.24932 to \
  7.56619, 3.2494 to \
  7.66429, 3.17325 to \
  7.66429, 3.17288 to \
  4.54246, 2.11146 to \
  4.44391, 2.1566 to \
  7.56594, 3.24932 front fs empty border lc rgb '#6165' lw 0.200001
set object 636 polygon from \
  7.46784, 3.32448 to \
  7.46809, 3.32457 to \
  7.56619, 3.2494 to \
  7.56619, 3.24903 to \
  4.44436, 2.15639 to \
  4.34581, 2.20055 to \
  7.46784, 3.32448 front fs empty border lc rgb '#6165' lw 0.200001
set object 637 polygon from \
  7.36974, 3.39867 to \
  7.36999, 3.39876 to \
  7.46809, 3.32457 to \
  7.46809, 3.3242 to \
  4.34626, 2.20034 to \
  4.24771, 2.24352 to \
  7.36974, 3.39867 front fs empty border lc rgb '#6165' lw 0.200001
set object 638 polygon from \
  7.27164, 3.47188 to \
  7.27189, 3.47197 to \
  7.36999, 3.39876 to \
  7.36999, 3.39839 to \
  4.24816, 2.24332 to \
  4.14961, 2.28551 to \
  7.27164, 3.47188 front fs empty border lc rgb '#6165' lw 0.200001
set object 639 polygon from \
  7.17354, 3.54411 to \
  7.17379, 3.5442 to \
  7.27189, 3.47197 to \
  7.27189, 3.4716 to \
  4.15006, 2.28531 to \
  4.05151, 2.32651 to \
  7.17354, 3.54411 front fs empty border lc rgb '#6165' lw 0.200001
set object 640 polygon from \
  7.07544, 3.61535 to \
  7.07569, 3.61545 to \
  7.17379, 3.5442 to \
  7.17379, 3.54383 to \
  4.05196, 2.32632 to \
  3.95341, 2.36654 to \
  7.07544, 3.61535 front fs empty border lc rgb '#6165' lw 0.200001
set object 641 polygon from \
  6.97734, 3.68561 to \
  6.97759, 3.68571 to \
  7.07569, 3.61545 to \
  7.07569, 3.61508 to \
  3.95386, 2.36635 to \
  3.85531, 2.40558 to \
  6.97734, 3.68561 front fs empty border lc rgb '#6165' lw 0.200001
set object 642 polygon from \
  6.87924, 3.7549 to \
  6.87949, 3.755 to \
  6.97759, 3.68571 to \
  6.97759, 3.68535 to \
  3.85576, 2.40539 to \
  3.75721, 2.44364 to \
  6.87924, 3.7549 front fs empty border lc rgb '#6165' lw 0.200001
set object 643 polygon from \
  6.78114, 3.8232 to \
  6.78139, 3.8233 to \
  6.87949, 3.755 to \
  6.87949, 3.75463 to \
  3.75766, 2.44346 to \
  3.65911, 2.48072 to \
  6.78114, 3.8232 front fs empty border lc rgb '#6165' lw 0.200001
set object 644 polygon from \
  6.68304, 3.89052 to \
  6.68329, 3.89063 to \
  6.78139, 3.8233 to \
  6.78139, 3.82294 to \
  3.65956, 2.48055 to \
  3.56101, 2.51682 to \
  6.68304, 3.89052 front fs empty border lc rgb '#6165' lw 0.200001
set object 645 polygon from \
  6.58494, 3.95686 to \
  6.58519, 3.95697 to \
  6.68329, 3.89063 to \
  6.68329, 3.89026 to \
  3.56146, 2.51665 to \
  3.46291, 2.55194 to \
  6.58494, 3.95686 front fs empty border lc rgb '#6165' lw 0.200001
set object 646 polygon from \
  6.48684, 4.02222 to \
  6.48709, 4.02233 to \
  6.58519, 3.95697 to \
  6.58519, 3.9566 to \
  3.46336, 2.55178 to \
  3.36481, 2.58608 to \
  6.48684, 4.02222 front fs empty border lc rgb '#6165' lw 0.200001
set object 647 polygon from \
  6.38874, 4.0866 to \
  6.38899, 4.08671 to \
  6.48709, 4.02233 to \
  6.48709, 4.02196 to \
  3.36526, 2.58592 to \
  3.26671, 2.61924 to \
  6.38874, 4.0866 front fs empty border lc rgb '#6165' lw 0.200001
set object 648 polygon from \
  6.29064, 4.14999 to \
  6.29089, 4.15011 to \
  6.38899, 4.08671 to \
  6.38899, 4.08634 to \
  3.26716, 2.61908 to \
  3.16861, 2.65142 to \
  6.29064, 4.14999 front fs empty border lc rgb '#6165' lw 0.200001
set object 649 polygon from \
  6.19254, 4.21241 to \
  6.19279, 4.21253 to \
  6.29089, 4.15011 to \
  6.29089, 4.14974 to \
  3.16906, 2.65126 to \
  3.07051, 2.68261 to \
  6.19254, 4.21241 front fs empty border lc rgb '#6165' lw 0.200001
set object 650 polygon from \
  6.09444, 4.27384 to \
  6.09469, 4.27397 to \
  6.19279, 4.21253 to \
  6.19279, 4.21216 to \
  3.07096, 2.68246 to \
  2.97241, 2.71283 to \
  6.09444, 4.27384 front fs empty border lc rgb '#6165' lw 0.200001
set object 651 polygon from \
  5.99634, 4.3343 to \
  5.99659, 4.33442 to \
  6.09469, 4.27397 to \
  6.09469, 4.2736 to \
  2.97286, 2.71268 to \
  2.87431, 2.74206 to \
  5.99634, 4.3343 front fs empty border lc rgb '#6165' lw 0.200001
set object 652 polygon from \
  5.89824, 4.39377 to \
  5.89849, 4.3939 to \
  5.99659, 4.33442 to \
  5.99659, 4.33405 to \
  2.87476, 2.74192 to \
  2.77621, 2.77031 to \
  5.89824, 4.39377 front fs empty border lc rgb '#6165' lw 0.200001
set object 653 polygon from \
  5.80014, 4.45226 to \
  5.80039, 4.45239 to \
  5.89849, 4.3939 to \
  5.89849, 4.39353 to \
  2.77666, 2.77018 to \
  2.67811, 2.79758 to \
  5.80014, 4.45226 front fs empty border lc rgb '#6165' lw 0.200001
set object 654 polygon from \
  5.70204, 4.50977 to \
  5.70229, 4.5099 to \
  5.80039, 4.45239 to \
  5.80039, 4.45202 to \
  2.67856, 2.79745 to \
  2.58001, 2.82387 to \
  5.70204, 4.50977 front fs empty border lc rgb '#6165' lw 0.200001
set object 655 polygon from \
  5.60394, 4.5663 to \
  5.60419, 4.56644 to \
  5.70229, 4.50991 to \
  5.70229, 4.50954 to \
  2.58046, 2.82375 to \
  2.48191, 2.84918 to \
  5.60394, 4.5663 front fs empty border lc rgb '#6165' lw 0.200001
set object 656 polygon from \
  5.50584, 4.62185 to \
  5.50609, 4.62199 to \
  5.60419, 4.56644 to \
  5.60419, 4.56607 to \
  2.48236, 2.84906 to \
  2.38381, 2.87351 to \
  5.50584, 4.62185 front fs empty border lc rgb '#6165' lw 0.200001
set object 657 polygon from \
  5.40774, 4.67642 to \
  5.40799, 4.67656 to \
  5.50609, 4.62199 to \
  5.50609, 4.62162 to \
  2.38426, 2.87339 to \
  2.28571, 2.89686 to \
  5.40774, 4.67642 front fs empty border lc rgb '#6165' lw 0.200001
set object 658 polygon from \
  5.30964, 4.73001 to \
  5.30989, 4.73015 to \
  5.40799, 4.67656 to \
  5.40799, 4.67619 to \
  2.28616, 2.89675 to \
  2.18761, 2.91923 to \
  5.30964, 4.73001 front fs empty border lc rgb '#6165' lw 0.200001
set object 659 polygon from \
  5.21154, 4.78261 to \
  5.21179, 4.78276 to \
  5.30989, 4.73015 to \
  5.30989, 4.72978 to \
  2.18806, 2.91912 to \
  2.08951, 2.94061 to \
  5.21154, 4.78261 front fs empty border lc rgb '#6165' lw 0.200001
set object 660 polygon from \
  5.11344, 4.83424 to \
  5.11369, 4.83438 to \
  5.21179, 4.78276 to \
  5.21179, 4.78239 to \
  2.08996, 2.94051 to \
  1.99141, 2.96102 to \
  5.11344, 4.83424 front fs empty border lc rgb '#6165' lw 0.200001
set object 661 polygon from \
  5.01534, 4.88488 to \
  5.01559, 4.88503 to \
  5.11369, 4.83439 to \
  5.11369, 4.83402 to \
  1.99186, 2.96092 to \
  1.89331, 2.98044 to \
  5.01534, 4.88488 front fs empty border lc rgb '#6165' lw 0.200001
set object 662 polygon from \
  4.91724, 4.93454 to \
  4.91749, 4.9347 to \
  5.01559, 4.88503 to \
  5.01559, 4.88466 to \
  1.89376, 2.98034 to \
  1.79521, 2.99888 to \
  4.91724, 4.93454 front fs empty border lc rgb '#6165' lw 0.200001
set object 663 polygon from \
  4.81914, 4.98323 to \
  4.81939, 4.98338 to \
  4.91749, 4.9347 to \
  4.91749, 4.93433 to \
  1.79566, 2.99879 to \
  1.69711, 3.01634 to \
  4.81914, 4.98323 front fs empty border lc rgb '#6165' lw 0.200001
set object 664 polygon from \
  4.72104, 5.03093 to \
  4.72129, 5.03108 to \
  4.81939, 4.98338 to \
  4.81939, 4.98301 to \
  1.69756, 3.01626 to \
  1.59901, 3.03282 to \
  4.72104, 5.03093 front fs empty border lc rgb '#6165' lw 0.200001
set object 665 polygon from \
  4.62294, 5.07765 to \
  4.62319, 5.07781 to \
  4.72129, 5.03109 to \
  4.72129, 5.03072 to \
  1.59946, 3.03274 to \
  1.50091, 3.04832 to \
  4.62294, 5.07765 front fs empty border lc rgb '#6165' lw 0.200001
set object 666 polygon from \
  4.52484, 5.12339 to \
  4.52509, 5.12355 to \
  4.62319, 5.07781 to \
  4.62319, 5.07744 to \
  1.50136, 3.04825 to \
  1.40281, 3.06284 to \
  4.52484, 5.12339 front fs empty border lc rgb '#6165' lw 0.200001
set object 667 polygon from \
  4.42674, 5.16814 to \
  4.42699, 5.16831 to \
  4.52509, 5.12355 to \
  4.52509, 5.12318 to \
  1.40326, 3.06277 to \
  1.30471, 3.07638 to \
  4.42674, 5.16814 front fs empty border lc rgb '#6165' lw 0.200001
set object 668 polygon from \
  4.32864, 5.21192 to \
  4.32889, 5.21209 to \
  4.42699, 5.16831 to \
  4.42699, 5.16794 to \
  1.30516, 3.07631 to \
  1.20661, 3.08894 to \
  4.32864, 5.21192 front fs empty border lc rgb '#6165' lw 0.200001
set object 669 polygon from \
  4.23054, 5.25472 to \
  4.23079, 5.25489 to \
  4.32889, 5.21209 to \
  4.32889, 5.21172 to \
  1.20706, 3.08887 to \
  1.10851, 3.10051 to \
  4.23054, 5.25472 front fs empty border lc rgb '#6165' lw 0.200001
set object 670 polygon from \
  4.13244, 5.29653 to \
  4.13269, 5.2967 to \
  4.23079, 5.25489 to \
  4.23079, 5.25452 to \
  1.10896, 3.10045 to \
  1.01041, 3.11111 to \
  4.13244, 5.29653 front fs empty border lc rgb '#6165' lw 0.200001
set object 671 polygon from \
  4.03434, 5.33736 to \
  4.03459, 5.33754 to \
  4.13269, 5.2967 to \
  4.13269, 5.29633 to \
  1.01086, 3.11105 to \
  0.912301, 3.12072 to \
  4.03434, 5.33736 front fs empty border lc rgb '#6165' lw 0.200001
set object 672 polygon from \
  3.93624, 5.37722 to \
  3.93649, 5.37739 to \
  4.03459, 5.33754 to \
  4.03459, 5.33717 to \
  0.912752, 3.12067 to \
  0.814201, 3.12935 to \
  3.93624, 5.37722 front fs empty border lc rgb '#6165' lw 0.200001
set object 673 polygon from \
  3.83814, 5.41609 to \
  3.83839, 5.41627 to \
  3.93649, 5.3774 to \
  3.93649, 5.37703 to \
  0.814652, 3.12931 to \
  0.716101, 3.137 to \
  3.83814, 5.41609 front fs empty border lc rgb '#6165' lw 0.200001
set object 674 polygon from \
  3.74004, 5.45398 to \
  3.74029, 5.45416 to \
  3.83839, 5.41627 to \
  3.83839, 5.4159 to \
  0.716552, 3.13696 to \
  0.618001, 3.14367 to \
  3.74004, 5.45398 front fs empty border lc rgb '#6165' lw 0.200001
set object 675 polygon from \
  3.64194, 5.49089 to \
  3.64219, 5.49107 to \
  3.74029, 5.45416 to \
  3.74029, 5.45379 to \
  0.618452, 3.14364 to \
  0.519901, 3.14936 to \
  3.64194, 5.49089 front fs empty border lc rgb '#6165' lw 0.200001
set object 676 polygon from \
  3.54384, 5.52682 to \
  3.54409, 5.52701 to \
  3.64219, 5.49108 to \
  3.64219, 5.49071 to \
  0.520352, 3.14933 to \
  0.421801, 3.15407 to \
  3.54384, 5.52682 front fs empty border lc rgb '#6165' lw 0.200001
set object 677 polygon from \
  3.44574, 5.56177 to \
  3.44599, 5.56196 to \
  3.54409, 5.52701 to \
  3.54409, 5.52664 to \
  0.422252, 3.15404 to \
  0.323701, 3.1578 to \
  3.44574, 5.56177 front fs empty border lc rgb '#6165' lw 0.200001
set object 678 polygon from \
  3.34764, 5.59573 to \
  3.34789, 5.59593 to \
  3.44599, 5.56196 to \
  3.44599, 5.56159 to \
  0.324152, 3.15778 to \
  0.225601, 3.16055 to \
  3.34764, 5.59573 front fs empty border lc rgb '#6165' lw 0.200001
set object 679 polygon from \
  3.24954, 5.62872 to \
  3.24979, 5.62891 to \
  3.34789, 5.59593 to \
  3.34789, 5.59556 to \
  0.226052, 3.16053 to \
  0.127501, 3.16231 to \
  3.24954, 5.62872 front fs empty border lc rgb '#6165' lw 0.200001
set object 680 polygon from \
  3.15144, 5.66072 to \
  3.15169, 5.66092 to \
  3.24979, 5.62892 to \
  3.24979, 5.62855 to \
  0.127952, 3.1623 to \
  0.0294004, 3.1631 to \
  3.15144, 5.66072 front fs empty border lc rgb '#6165' lw 0.200001
set object 681 polygon from \
  3.05334, 5.69175 to \
  3.05359, 5.69195 to \
  3.15169, 5.66092 to \
  3.15169, 5.66055 to \
  0.0298511, 3.16309 to \
  -0.0686996, 3.1629 to \
  3.05334, 5.69175 front fs empty border lc rgb '#6165' lw 0.200001
set object 682 polygon from \
  2.95524, 5.72179 to \
  2.95549, 5.72199 to \
  3.05359, 5.69195 to \
  3.05359, 5.69158 to \
  -0.0682489, 3.16289 to \
  -0.166799, 3.16172 to \
  2.95524, 5.72179 front fs empty border lc rgb '#6165' lw 0.200001
set object 683 polygon from \
  2.85714, 5.75085 to \
  2.85739, 5.75106 to \
  2.95549, 5.72199 to \
  2.95549, 5.72163 to \
  -0.166348, 3.16172 to \
  -0.264899, 3.15956 to \
  2.85714, 5.75085 front fs empty border lc rgb '#6165' lw 0.200001
set object 684 polygon from \
  2.75904, 5.77893 to \
  2.75929, 5.77914 to \
  2.85739, 5.75106 to \
  2.85739, 5.75069 to \
  -0.264448, 3.15957 to \
  -0.362999, 3.15642 to \
  2.75904, 5.77893 front fs empty border lc rgb '#6165' lw 0.200001
set object 685 polygon from \
  2.66094, 5.80604 to \
  2.66119, 5.80624 to \
  2.75929, 5.77914 to \
  2.75929, 5.77877 to \
  -0.362548, 3.15643 to \
  -0.461099, 3.1523 to \
  2.66094, 5.80604 front fs empty border lc rgb '#6165' lw 0.200001
set object 686 polygon from \
  2.56284, 5.83215 to \
  2.56309, 5.83237 to \
  2.66119, 5.80625 to \
  2.66119, 5.80588 to \
  -0.460648, 3.15232 to \
  -0.559199, 3.1472 to \
  2.56284, 5.83215 front fs empty border lc rgb '#6165' lw 0.200001
set object 687 polygon from \
  2.46474, 5.85729 to \
  2.46499, 5.85751 to \
  2.56309, 5.83237 to \
  2.56309, 5.832 to \
  -0.558748, 3.14722 to \
  -0.657299, 3.14112 to \
  2.46474, 5.85729 front fs empty border lc rgb '#6165' lw 0.200001
set object 688 polygon from \
  2.36664, 5.88145 to \
  2.36689, 5.88167 to \
  2.46499, 5.85751 to \
  2.46499, 5.85714 to \
  -0.656848, 3.14114 to \
  -0.755399, 3.13406 to \
  2.36664, 5.88145 front fs empty border lc rgb '#6165' lw 0.200001
set object 689 polygon from \
  2.26854, 5.90463 to \
  2.26879, 5.90484 to \
  2.36689, 5.88167 to \
  2.36689, 5.8813 to \
  -0.754948, 3.13408 to \
  -0.853499, 3.12601 to \
  2.26854, 5.90463 front fs empty border lc rgb '#6165' lw 0.200001
set object 690 polygon from \
  2.17044, 5.92682 to \
  2.17069, 5.92704 to \
  2.26879, 5.90484 to \
  2.26879, 5.90447 to \
  -0.853048, 3.12604 to \
  -0.951599, 3.11699 to \
  2.17044, 5.92682 front fs empty border lc rgb '#6165' lw 0.200001
set object 691 polygon from \
  2.07234, 5.94803 to \
  2.07259, 5.94826 to \
  2.17069, 5.92704 to \
  2.17069, 5.92667 to \
  -0.951148, 3.11702 to \
  -1.04969, 3.10698 to \
  2.07234, 5.94803 front fs empty border lc rgb '#6165' lw 0.200001
set object 692 polygon from \
  1.97424, 5.96827 to \
  1.97449, 5.96849 to \
  2.07259, 5.94826 to \
  2.07259, 5.94789 to \
  -1.04924, 3.10702 to \
  -1.14779, 3.09599 to \
  1.97424, 5.96827 front fs empty border lc rgb '#6165' lw 0.200001
set object 693 polygon from \
  1.87614, 5.98752 to \
  1.87639, 5.98775 to \
  1.97449, 5.96849 to \
  1.97449, 5.96812 to \
  -1.14734, 3.09604 to \
  -1.24589, 3.08402 to \
  1.87614, 5.98752 front fs empty border lc rgb '#6165' lw 0.200001
set object 694 polygon from \
  1.77804, 6.00579 to \
  1.77829, 6.00602 to \
  1.87639, 5.98775 to \
  1.87639, 5.98738 to \
  -1.24544, 3.08407 to \
  -1.34399, 3.07107 to \
  1.77804, 6.00579 front fs empty border lc rgb '#6165' lw 0.200001
set object 695 polygon from \
  1.67994, 6.02308 to \
  1.68019, 6.02331 to \
  1.77829, 6.00602 to \
  1.77829, 6.00565 to \
  -1.34354, 3.07113 to \
  -1.44209, 3.05714 to \
  1.67994, 6.02308 front fs empty border lc rgb '#6165' lw 0.200001
set object 696 polygon from \
  1.58184, 6.03939 to \
  1.58209, 6.03962 to \
  1.68019, 6.02331 to \
  1.68019, 6.02294 to \
  -1.44164, 3.0572 to \
  -1.54019, 3.04223 to \
  1.58184, 6.03939 front fs empty border lc rgb '#6165' lw 0.200001
set object 697 polygon from \
  1.48374, 6.05471 to \
  1.48399, 6.05495 to \
  1.58209, 6.03963 to \
  1.58209, 6.03925 to \
  -1.53974, 3.04229 to \
  -1.63829, 3.02634 to \
  1.48374, 6.05471 front fs empty border lc rgb '#6165' lw 0.200001
set object 698 polygon from \
  1.38564, 6.06906 to \
  1.38589, 6.0693 to \
  1.48399, 6.05496 to \
  1.48399, 6.05459 to \
  -1.63784, 3.02641 to \
  -1.73639, 3.00947 to \
  1.38564, 6.06906 front fs empty border lc rgb '#6165' lw 0.200001
set object 699 polygon from \
  1.28754, 6.08243 to \
  1.28779, 6.08267 to \
  1.38589, 6.06931 to \
  1.38589, 6.06893 to \
  -1.73594, 3.00954 to \
  -1.83449, 2.99161 to \
  1.28754, 6.08243 front fs empty border lc rgb '#6165' lw 0.200001
set object 700 polygon from \
  1.18944, 6.09481 to \
  1.18969, 6.09506 to \
  1.28779, 6.08267 to \
  1.28779, 6.0823 to \
  -1.83404, 2.99169 to \
  -1.93259, 2.97278 to \
  1.18944, 6.09481 front fs empty border lc rgb '#6165' lw 0.200001
set object 701 polygon from \
  1.09134, 6.10621 to \
  1.09159, 6.10647 to \
  1.18969, 6.09506 to \
  1.18969, 6.09469 to \
  -1.93214, 2.97286 to \
  -2.03069, 2.95296 to \
  1.09134, 6.10621 front fs empty border lc rgb '#6165' lw 0.200001
set object 702 polygon from \
  0.993233, 6.11663 to \
  0.993487, 6.11689 to \
  1.09159, 6.10647 to \
  1.09159, 6.1061 to \
  -2.03024, 2.95304 to \
  -2.12879, 2.93216 to \
  0.993233, 6.11663 front fs empty border lc rgb '#6165' lw 0.200001
set object 703 polygon from \
  0.895134, 6.12608 to \
  0.895387, 6.12634 to \
  0.993486, 6.11689 to \
  0.993486, 6.11652 to \
  -2.12834, 2.93225 to \
  -2.22689, 2.91038 to \
  0.895134, 6.12608 front fs empty border lc rgb '#6165' lw 0.200001
set object 704 polygon from \
  0.797035, 6.13454 to \
  0.797287, 6.1348 to \
  0.895386, 6.12634 to \
  0.895386, 6.12597 to \
  -2.22644, 2.91048 to \
  -2.32499, 2.88762 to \
  0.797035, 6.13454 front fs empty border lc rgb '#6165' lw 0.200001
set object 705 polygon from \
  0.698935, 6.14202 to \
  0.699187, 6.14228 to \
  0.797286, 6.1348 to \
  0.797286, 6.13443 to \
  -2.32454, 2.88772 to \
  -2.42309, 2.86388 to \
  0.698935, 6.14202 front fs empty border lc rgb '#6165' lw 0.200001
set object 706 polygon from \
  0.600833, 6.14852 to \
  0.601087, 6.14878 to \
  0.699186, 6.14228 to \
  0.699186, 6.14191 to \
  -2.42264, 2.86399 to \
  -2.52119, 2.83916 to \
  0.600833, 6.14852 front fs empty border lc rgb '#6165' lw 0.200001
set object 707 polygon from \
  0.502731, 6.15403 to \
  0.502987, 6.1543 to \
  0.601086, 6.14878 to \
  0.601086, 6.14841 to \
  -2.52074, 2.83927 to \
  -2.61929, 2.81346 to \
  0.502731, 6.15403 front fs empty border lc rgb '#6165' lw 0.200001
set object 708 polygon from \
  0.404631, 6.15857 to \
  0.404887, 6.15884 to \
  0.502986, 6.1543 to \
  0.502986, 6.15393 to \
  -2.61884, 2.81357 to \
  -2.71739, 2.78678 to \
  0.404631, 6.15857 front fs empty border lc rgb '#6165' lw 0.200001
set object 709 polygon from \
  0.306531, 6.16212 to \
  0.306787, 6.1624 to \
  0.404886, 6.15884 to \
  0.404886, 6.15847 to \
  -2.71694, 2.78689 to \
  -2.81549, 2.75911 to \
  0.306531, 6.16212 front fs empty border lc rgb '#6165' lw 0.200001
set object 710 polygon from \
  0.208432, 6.1647 to \
  0.208687, 6.16498 to \
  0.306786, 6.1624 to \
  0.306786, 6.16203 to \
  -2.81504, 2.75923 to \
  -2.9136, 2.73047 to \
  0.208432, 6.1647 front fs empty border lc rgb '#6165' lw 0.200001
set object 711 polygon from \
  0.110334, 6.1663 to \
  0.110587, 6.16658 to \
  0.208686, 6.16498 to \
  0.208686, 6.16461 to \
  -2.91314, 2.73059 to \
  -3.0117, 2.70084 to \
  0.110334, 6.1663 front fs empty border lc rgb '#6165' lw 0.200001
set object 712 polygon from \
  0.0122335, 6.16691 to \
  0.0124868, 6.16719 to \
  0.110586, 6.16658 to \
  0.110586, 6.1662 to \
  -3.01124, 2.70097 to \
  -3.1098, 2.67023 to \
  0.0122335, 6.16691 front fs empty border lc rgb '#6165' lw 0.200001
set object 713 polygon from \
  -0.0858681, 6.16654 to \
  -0.0856132, 6.16682 to \
  0.0124859, 6.16719 to \
  0.0124859, 6.16682 to \
  -3.10934, 2.67037 to \
  -3.2079, 2.63864 to \
  -0.0858681, 6.16654 front fs empty border lc rgb '#6165' lw 0.200001
set object 714 polygon from \
  -0.183968, 6.16519 to \
  -0.183713, 6.16548 to \
  -0.0856141, 6.16683 to \
  -0.0856141, 6.16645 to \
  -3.20744, 2.63878 to \
  -3.306, 2.60607 to \
  -0.183968, 6.16519 front fs empty border lc rgb '#6165' lw 0.200001
set object 715 polygon from \
  -0.282069, 6.16286 to \
  -0.281813, 6.16315 to \
  -0.183714, 6.16548 to \
  -0.183714, 6.16511 to \
  -3.30554, 2.60622 to \
  -3.4041, 2.57252 to \
  -0.282069, 6.16286 front fs empty border lc rgb '#6165' lw 0.200001
set object 716 polygon from \
  -0.380169, 6.15955 to \
  -0.379913, 6.15984 to \
  -0.281814, 6.16315 to \
  -0.281814, 6.16278 to \
  -3.40364, 2.57267 to \
  -3.5022, 2.53799 to \
  -0.380169, 6.15955 front fs empty border lc rgb '#6165' lw 0.200001
set object 717 polygon from \
  -0.478268, 6.15526 to \
  -0.478013, 6.15555 to \
  -0.379914, 6.15984 to \
  -0.379914, 6.15947 to \
  -3.50174, 2.53814 to \
  -3.6003, 2.50248 to \
  -0.478268, 6.15526 front fs empty border lc rgb '#6165' lw 0.200001
set object 718 polygon from \
  -0.57637, 6.14998 to \
  -0.576113, 6.15028 to \
  -0.478014, 6.15555 to \
  -0.478014, 6.15518 to \
  -3.59984, 2.50264 to \
  -3.6984, 2.46599 to \
  -0.57637, 6.14998 front fs empty border lc rgb '#6165' lw 0.200001
set object 719 polygon from \
  -0.67447, 6.14373 to \
  -0.674213, 6.14403 to \
  -0.576114, 6.15028 to \
  -0.576114, 6.14991 to \
  -3.69794, 2.46615 to \
  -3.7965, 2.42851 to \
  -0.67447, 6.14373 front fs empty border lc rgb '#6165' lw 0.200001
set object 720 polygon from \
  -0.77257, 6.13649 to \
  -0.772313, 6.1368 to \
  -0.674214, 6.14403 to \
  -0.674214, 6.14366 to \
  -3.79604, 2.42868 to \
  -3.8946, 2.39006 to \
  -0.77257, 6.13649 front fs empty border lc rgb '#6165' lw 0.200001
set object 721 polygon from \
  -0.870671, 6.12827 to \
  -0.870413, 6.12858 to \
  -0.772314, 6.1368 to \
  -0.772314, 6.13643 to \
  -3.89414, 2.39023 to \
  -3.9927, 2.35062 to \
  -0.870671, 6.12827 front fs empty border lc rgb '#6165' lw 0.200001
set object 722 polygon from \
  -0.968773, 6.11907 to \
  -0.968513, 6.11939 to \
  -0.870414, 6.12858 to \
  -0.870414, 6.12821 to \
  -3.99224, 2.35079 to \
  -4.0908, 2.3102 to \
  -0.968773, 6.11907 front fs empty border lc rgb '#6165' lw 0.200001
set object 723 polygon from \
  -1.06687, 6.1089 to \
  -1.06661, 6.10921 to \
  -0.968514, 6.11939 to \
  -0.968514, 6.11902 to \
  -4.09034, 2.31038 to \
  -4.1889, 2.2688 to \
  -1.06687, 6.1089 front fs empty border lc rgb '#6165' lw 0.200001
set object 724 polygon from \
  -1.16497, 6.09774 to \
  -1.16471, 6.09806 to \
  -1.06661, 6.10921 to \
  -1.06661, 6.10884 to \
  -4.18844, 2.26899 to \
  -4.287, 2.22642 to \
  -1.16497, 6.09774 front fs empty border lc rgb '#6165' lw 0.200001
set object 725 polygon from \
  -1.26307, 6.08559 to \
  -1.26281, 6.08592 to \
  -1.16471, 6.09806 to \
  -1.16471, 6.09769 to \
  -4.28654, 2.22661 to \
  -4.3851, 2.18306 to \
  -1.26307, 6.08559 front fs empty border lc rgb '#6165' lw 0.200001
set object 726 polygon from \
  -1.36117, 6.07247 to \
  -1.36091, 6.0728 to \
  -1.26281, 6.08592 to \
  -1.26281, 6.08555 to \
  -4.38464, 2.18326 to \
  -4.4832, 2.13872 to \
  -1.36117, 6.07247 front fs empty border lc rgb '#6165' lw 0.200001
set object 727 polygon from \
  -1.45927, 6.05837 to \
  -1.45901, 6.0587 to \
  -1.36091, 6.0728 to \
  -1.36091, 6.07243 to \
  -4.48274, 2.13892 to \
  -4.5813, 2.0934 to \
  -1.45927, 6.05837 front fs empty border lc rgb '#6165' lw 0.200001
set object 728 polygon from \
  -1.55737, 6.04329 to \
  -1.55711, 6.04362 to \
  -1.45901, 6.0587 to \
  -1.45901, 6.05833 to \
  -4.58084, 2.0936 to \
  -4.6794, 2.04709 to \
  -1.55737, 6.04329 front fs empty border lc rgb '#6165' lw 0.200001
set object 729 polygon from \
  -1.65547, 6.02722 to \
  -1.65521, 6.02756 to \
  -1.55711, 6.04362 to \
  -1.55711, 6.04325 to \
  -4.67894, 2.0473 to \
  -4.7775, 1.99981 to \
  -1.65547, 6.02722 front fs empty border lc rgb '#6165' lw 0.200001
set object 730 polygon from \
  -1.75358, 6.01017 to \
  -1.75331, 6.01052 to \
  -1.65521, 6.02756 to \
  -1.65521, 6.02719 to \
  -4.77704, 2.00002 to \
  -4.8756, 1.95154 to \
  -1.75358, 6.01017 front fs empty border lc rgb '#6165' lw 0.200001
set object 731 polygon from \
  -1.85168, 5.99214 to \
  -1.85141, 5.99249 to \
  -1.75331, 6.01052 to \
  -1.75331, 6.01015 to \
  -4.87514, 1.95176 to \
  -4.9737, 1.9023 to \
  -1.85168, 5.99214 front fs empty border lc rgb '#6165' lw 0.200001
set object 732 polygon from \
  -1.94978, 5.97313 to \
  -1.94951, 5.97349 to \
  -1.85141, 5.99249 to \
  -1.85141, 5.99212 to \
  -4.97324, 1.90252 to \
  -5.0718, 1.85207 to \
  -1.94978, 5.97313 front fs empty border lc rgb '#6165' lw 0.200001
set object 733 polygon from \
  -2.04788, 5.95314 to \
  -2.04761, 5.9535 to \
  -1.94951, 5.97349 to \
  -1.94951, 5.97312 to \
  -5.07134, 1.8523 to \
  -5.1699, 1.80086 to \
  -2.04788, 5.95314 front fs empty border lc rgb '#6165' lw 0.200001
set object 734 polygon from \
  -2.14598, 5.93217 to \
  -2.14571, 5.93254 to \
  -2.04761, 5.9535 to \
  -2.04761, 5.95313 to \
  -5.16944, 1.80109 to \
  -5.268, 1.74867 to \
  -2.14598, 5.93217 front fs empty border lc rgb '#6165' lw 0.200001
set object 735 polygon from \
  -2.24409, 5.91022 to \
  -2.24381, 5.91059 to \
  -2.14571, 5.93254 to \
  -2.14571, 5.93216 to \
  -5.26754, 1.74891 to \
  -5.3661, 1.6955 to \
  -2.24409, 5.91022 front fs empty border lc rgb '#6165' lw 0.200001
set object 736 polygon from \
  -2.34219, 5.88728 to \
  -2.34191, 5.88766 to \
  -2.24381, 5.91059 to \
  -2.24381, 5.91022 to \
  -5.36564, 1.69574 to \
  -5.4642, 1.64135 to \
  -2.34219, 5.88728 front fs empty border lc rgb '#6165' lw 0.200001
set object 737 polygon from \
  -2.44029, 5.86337 to \
  -2.44001, 5.86375 to \
  -2.34191, 5.88766 to \
  -2.34191, 5.88729 to \
  -5.46374, 1.64159 to \
  -5.5623, 1.58622 to \
  -2.44029, 5.86337 front fs empty border lc rgb '#6165' lw 0.200001
set object 738 polygon from \
  -2.53839, 5.83848 to \
  -2.53811, 5.83886 to \
  -2.44001, 5.86375 to \
  -2.44001, 5.86338 to \
  -5.56184, 1.58647 to \
  -5.6604, 1.5301 to \
  -2.53839, 5.83848 front fs empty border lc rgb '#6165' lw 0.200001
set object 739 polygon from \
  -2.63649, 5.8126 to \
  -2.63621, 5.81299 to \
  -2.53811, 5.83886 to \
  -2.53811, 5.83849 to \
  -5.65994, 1.53036 to \
  -5.7585, 1.47301 to \
  -2.63649, 5.8126 front fs empty border lc rgb '#6165' lw 0.200001
set object 740 polygon from \
  -2.73459, 5.78574 to \
  -2.73431, 5.78614 to \
  -2.63621, 5.81299 to \
  -2.63621, 5.81262 to \
  -5.75804, 1.47327 to \
  -5.8566, 1.41493 to \
  -2.73459, 5.78574 front fs empty border lc rgb '#6165' lw 0.200001
set object 741 polygon from \
  -2.83269, 5.7579 to \
  -2.83241, 5.7583 to \
  -2.73431, 5.78614 to \
  -2.73431, 5.78576 to \
  -5.85614, 1.4152 to \
  -5.9547, 1.35588 to \
  -2.83269, 5.7579 front fs empty border lc rgb '#6165' lw 0.200001
set object 742 polygon from \
  -2.93079, 5.72909 to \
  -2.93051, 5.72949 to \
  -2.83241, 5.7583 to \
  -2.83241, 5.75793 to \
  -5.95424, 1.35614 to \
  -6.0528, 1.29584 to \
  -2.93079, 5.72909 front fs empty border lc rgb '#6165' lw 0.200001
set object 743 polygon from \
  -3.02889, 5.69929 to \
  -3.02861, 5.69969 to \
  -2.93051, 5.72949 to \
  -2.93051, 5.72912 to \
  -6.05234, 1.29611 to \
  -6.1509, 1.23482 to \
  -3.02889, 5.69929 front fs empty border lc rgb '#6165' lw 0.200001
set object 744 polygon from \
  -3.127, 5.6685 to \
  -3.12671, 5.66891 to \
  -3.02861, 5.69969 to \
  -3.02861, 5.69932 to \
  -6.15044, 1.2351 to \
  -6.249, 1.17282 to \
  -3.127, 5.6685 front fs empty border lc rgb '#6165' lw 0.200001
set object 745 polygon from \
  -3.2251, 5.63674 to \
  -3.22481, 5.63716 to \
  -3.12671, 5.66892 to \
  -3.12671, 5.66854 to \
  -6.24854, 1.1731 to \
  -6.3471, 1.10984 to \
  -3.2251, 5.63674 front fs empty border lc rgb '#6165' lw 0.200001
set object 746 polygon from \
  -3.3232, 5.60399 to \
  -3.32291, 5.60442 to \
  -3.22481, 5.63716 to \
  -3.22481, 5.63679 to \
  -6.34664, 1.11013 to \
  -6.4452, 1.04588 to \
  -3.3232, 5.60399 front fs empty border lc rgb '#6165' lw 0.200001
set object 747 polygon from \
  -3.42131, 5.57026 to \
  -3.42101, 5.5707 to \
  -3.32291, 5.60442 to \
  -3.32291, 5.60405 to \
  -6.44474, 1.04617 to \
  -6.5433, 0.980934 to \
  -3.42131, 5.57026 front fs empty border lc rgb '#6165' lw 0.200001
set object 748 polygon from \
  -3.51941, 5.53555 to \
  -3.51911, 5.536 to \
  -3.42101, 5.5707 to \
  -3.42101, 5.57033 to \
  -6.54284, 0.981227 to \
  -6.6414, 0.91501 to \
  -3.51941, 5.53555 front fs empty border lc rgb '#6165' lw 0.200001
set object 749 polygon from \
  -3.61752, 5.49986 to \
  -3.61721, 5.50032 to \
  -3.51911, 5.536 to \
  -3.51911, 5.53563 to \
  -6.64094, 0.915308 to \
  -6.7395, 0.848106 to \
  -3.61752, 5.49986 front fs empty border lc rgb '#6165' lw 0.200001
set object 750 polygon from \
  -3.71562, 5.46319 to \
  -3.71531, 5.46365 to \
  -3.61721, 5.50032 to \
  -3.61721, 5.49994 to \
  -6.73904, 0.848408 to \
  -6.8376, 0.78022 to \
  -3.71562, 5.46319 front fs empty border lc rgb '#6165' lw 0.200001
set object 751 polygon from \
  -3.81372, 5.42554 to \
  -3.81341, 5.42601 to \
  -3.71531, 5.46365 to \
  -3.71531, 5.46328 to \
  -6.83714, 0.780527 to \
  -6.9357, 0.711354 to \
  -3.81372, 5.42554 front fs empty border lc rgb '#6165' lw 0.200001
set object 752 polygon from \
  -3.91183, 5.38691 to \
  -3.91151, 5.38739 to \
  -3.81341, 5.42601 to \
  -3.81341, 5.42564 to \
  -6.93524, 0.711665 to \
  -7.0338, 0.641506 to \
  -3.91183, 5.38691 front fs empty border lc rgb '#6165' lw 0.200001
set object 753 polygon from \
  -4.00993, 5.3473 to \
  -4.00961, 5.34778 to \
  -3.91151, 5.38739 to \
  -3.91151, 5.38701 to \
  -7.03334, 0.641822 to \
  -7.1319, 0.570678 to \
  -4.00993, 5.3473 front fs empty border lc rgb '#6165' lw 0.200001
set object 754 polygon from \
  -4.10803, 5.30671 to \
  -4.10771, 5.30719 to \
  -4.00961, 5.34778 to \
  -4.00961, 5.34741 to \
  -7.13144, 0.570998 to \
  -7.23, 0.498868 to \
  -4.10803, 5.30671 front fs empty border lc rgb '#6165' lw 0.200001
set object 755 polygon from \
  -4.20613, 5.26513 to \
  -4.20581, 5.26563 to \
  -4.10771, 5.30719 to \
  -4.10771, 5.30682 to \
  -7.22954, 0.499193 to \
  -7.3281, 0.426078 to \
  -4.20613, 5.26513 front fs empty border lc rgb '#6165' lw 0.200001
set object 756 polygon from \
  -4.30423, 5.22257 to \
  -4.30391, 5.22308 to \
  -4.20581, 5.26563 to \
  -4.20581, 5.26525 to \
  -7.32764, 0.426407 to \
  -7.4262, 0.352306 to \
  -4.30423, 5.22257 front fs empty border lc rgb '#6165' lw 0.200001
set object 757 polygon from \
  -4.40234, 5.17903 to \
  -4.40201, 5.17955 to \
  -4.30391, 5.22308 to \
  -4.30391, 5.2227 to \
  -7.42574, 0.35264 to \
  -7.5243, 0.277554 to \
  -4.40234, 5.17903 front fs empty border lc rgb '#6165' lw 0.200001
set object 758 polygon from \
  -4.50045, 5.13451 to \
  -4.50011, 5.13504 to \
  -4.40201, 5.17955 to \
  -4.40201, 5.17917 to \
  -7.52384, 0.277892 to \
  -7.6224, 0.20182 to \
  -4.50045, 5.13451 front fs empty border lc rgb '#6165' lw 0.200001
set object 759 polygon from \
  -4.59855, 5.08901 to \
  -4.59821, 5.08955 to \
  -4.50011, 5.13504 to \
  -4.50011, 5.13466 to \
  -7.62194, 0.202163 to \
  -7.7205, 0.125106 to \
  -4.59855, 5.08901 front fs empty border lc rgb '#6165' lw 0.200001
set object 760 polygon from \
  -4.69665, 5.04253 to \
  -4.69631, 5.04307 to \
  -4.59821, 5.08955 to \
  -4.59821, 5.08917 to \
  -7.72004, 0.125453 to \
  -7.8186, 0.0474097 to \
  -4.69665, 5.04253 front fs empty border lc rgb '#6165' lw 0.200001
set object 761 polygon from \
  -4.79476, 4.99506 to \
  -4.79441, 4.99562 to \
  -4.69631, 5.04307 to \
  -4.69631, 5.0427 to \
  -7.81814, 0.0477615 to \
  -7.8777, 0 to \
  -7.89728, 0 to \
  -4.79476, 4.99506 front fs empty border lc rgb '#6165' lw 0.200001
set object 762 polygon from \
  -4.89286, 4.94661 to \
  -4.89251, 4.94718 to \
  -4.79441, 4.99562 to \
  -4.79441, 4.99525 to \
  -7.89704, 0 to \
  -7.94632, 0 to \
  -4.89286, 4.94661 front fs empty border lc rgb '#6165' lw 0.200001
set object 763 polygon from \
  -4.99097, 4.89718 to \
  -4.99061, 4.89777 to \
  -4.89251, 4.94719 to \
  -4.89251, 4.94681 to \
  -7.94609, 0 to \
  -7.99537, 0 to \
  -4.99097, 4.89718 front fs empty border lc rgb '#6165' lw 0.200001
set object 764 polygon from \
  -5.08908, 4.84677 to \
  -5.08871, 4.84737 to \
  -4.99061, 4.89777 to \
  -4.99061, 4.8974 to \
  -7.99514, 0 to \
  -8.04442, 0 to \
  -5.08908, 4.84677 front fs empty border lc rgb '#6165' lw 0.200001
set object 765 polygon from \
  -5.18719, 4.79538 to \
  -5.18681, 4.79599 to \
  -5.08871, 4.84737 to \
  -5.08871, 4.847 to \
  -8.04419, 0 to \
  -8.09347, 0 to \
  -5.18719, 4.79538 front fs empty border lc rgb '#6165' lw 0.200001
set object 766 polygon from \
  -5.28528, 4.74302 to \
  -5.28491, 4.74364 to \
  -5.18681, 4.796 to \
  -5.18681, 4.79562 to \
  -8.09324, 0 to \
  -8.14252, 0 to \
  -5.28528, 4.74302 front fs empty border lc rgb '#6165' lw 0.200001
set object 767 polygon from \
  -5.38339, 4.68967 to \
  -5.38301, 4.6903 to \
  -5.28491, 4.74364 to \
  -5.28491, 4.74326 to \
  -8.14229, 0 to \
  -8.19157, 0 to \
  -5.38339, 4.68967 front fs empty border lc rgb '#6165' lw 0.200001
set object 768 polygon from \
  -5.48149, 4.63534 to \
  -5.48111, 4.63598 to \
  -5.38301, 4.6903 to \
  -5.38301, 4.68992 to \
  -8.19134, 0 to \
  -8.24062, 0 to \
  -5.48149, 4.63534 front fs empty border lc rgb '#6165' lw 0.200001
set object 769 polygon from \
  -5.5796, 4.58002 to \
  -5.57921, 4.58067 to \
  -5.48111, 4.63598 to \
  -5.48111, 4.6356 to \
  -8.24039, 0 to \
  -8.28966, 0 to \
  -5.5796, 4.58002 front fs empty border lc rgb '#6165' lw 0.200001
set object 770 polygon from \
  -5.67771, 4.52372 to \
  -5.67731, 4.52439 to \
  -5.57921, 4.58067 to \
  -5.57921, 4.5803 to \
  -8.28944, 0 to \
  -8.33871, 0 to \
  -5.67771, 4.52372 front fs empty border lc rgb '#6165' lw 0.200001
set object 771 polygon from \
  -5.77581, 4.46644 to \
  -5.77541, 4.46713 to \
  -5.67731, 4.52439 to \
  -5.67731, 4.52402 to \
  -8.33849, 0 to \
  -8.38776, 0 to \
  -5.77581, 4.46644 front fs empty border lc rgb '#6165' lw 0.200001
set object 772 polygon from \
  -5.87392, 4.40819 to \
  -5.87351, 4.40888 to \
  -5.77541, 4.46713 to \
  -5.77541, 4.46675 to \
  -8.38754, 0 to \
  -8.43681, 0 to \
  -5.87392, 4.40819 front fs empty border lc rgb '#6165' lw 0.200001
set object 773 polygon from \
  -5.97202, 4.34894 to \
  -5.97161, 4.34966 to \
  -5.87351, 4.40888 to \
  -5.87351, 4.40851 to \
  -8.43659, 0 to \
  -8.48586, 0 to \
  -5.97202, 4.34894 front fs empty border lc rgb '#6165' lw 0.200001
set object 774 polygon from \
  -6.07013, 4.28873 to \
  -6.06971, 4.28945 to \
  -5.97161, 4.34966 to \
  -5.97161, 4.34928 to \
  -8.48564, 0 to \
  -8.53491, 0 to \
  -6.07013, 4.28873 front fs empty border lc rgb '#6165' lw 0.200001
set object 775 polygon from \
  -6.16822, 4.22754 to \
  -6.16781, 4.22826 to \
  -6.06971, 4.28945 to \
  -6.06971, 4.28908 to \
  -8.53469, 0 to \
  -8.58396, 0 to \
  -6.16822, 4.22754 front fs empty border lc rgb '#6165' lw 0.200001
set object 776 polygon from \
  -6.26633, 4.16535 to \
  -6.26591, 4.16609 to \
  -6.16781, 4.22826 to \
  -6.16781, 4.22789 to \
  -8.58374, 0 to \
  -8.63301, 0 to \
  -6.26633, 4.16535 front fs empty border lc rgb '#6165' lw 0.200001
set object 777 polygon from \
  -6.36443, 4.1022 to \
  -6.36401, 4.10294 to \
  -6.26591, 4.1661 to \
  -6.26591, 4.16572 to \
  -8.63279, 0 to \
  -8.68205, 0 to \
  -6.36443, 4.1022 front fs empty border lc rgb '#6165' lw 0.200001
set object 778 polygon from \
  -6.46254, 4.03805 to \
  -6.46211, 4.03881 to \
  -6.36401, 4.10295 to \
  -6.36401, 4.10257 to \
  -8.68184, 0 to \
  -8.7311, 0 to \
  -6.46254, 4.03805 front fs empty border lc rgb '#6165' lw 0.200001
set object 779 polygon from \
  -6.56065, 3.97292 to \
  -6.56021, 3.9737 to \
  -6.46211, 4.03882 to \
  -6.46211, 4.03844 to \
  -8.73089, 0 to \
  -8.78015, 0 to \
  -6.56065, 3.97292 front fs empty border lc rgb '#6165' lw 0.200001
set object 780 polygon from \
  -6.65875, 3.90682 to \
  -6.65831, 3.90761 to \
  -6.56021, 3.9737 to \
  -6.56021, 3.97333 to \
  -8.77994, 0 to \
  -8.8292, 0 to \
  -6.65875, 3.90682 front fs empty border lc rgb '#6165' lw 0.200001
set object 781 polygon from \
  -6.75686, 3.83973 to \
  -6.75641, 3.84054 to \
  -6.65831, 3.90761 to \
  -6.65831, 3.90724 to \
  -8.82899, 0 to \
  -8.87825, 0 to \
  -6.75686, 3.83973 front fs empty border lc rgb '#6165' lw 0.200001
set object 782 polygon from \
  -6.85496, 3.77166 to \
  -6.85451, 3.77248 to \
  -6.75641, 3.84054 to \
  -6.75641, 3.84016 to \
  -8.87804, 0 to \
  -8.9273, 0 to \
  -6.85496, 3.77166 front fs empty border lc rgb '#6165' lw 0.200001
set object 783 polygon from \
  -6.95307, 3.70262 to \
  -6.95261, 3.70345 to \
  -6.85451, 3.77248 to \
  -6.85451, 3.77211 to \
  -8.92709, 0 to \
  -8.97635, 0 to \
  -6.95307, 3.70262 front fs empty border lc rgb '#6165' lw 0.200001
set object 784 polygon from \
  -7.05117, 3.63259 to \
  -7.05071, 3.63343 to \
  -6.95261, 3.70345 to \
  -6.95261, 3.70307 to \
  -8.97614, 0 to \
  -9.0254, 0 to \
  -7.05117, 3.63259 front fs empty border lc rgb '#6165' lw 0.200001
set object 785 polygon from \
  -7.14927, 3.56158 to \
  -7.14881, 3.56243 to \
  -7.05071, 3.63343 to \
  -7.05071, 3.63306 to \
  -9.02519, 0 to \
  -9.07445, 0 to \
  -7.14927, 3.56158 front fs empty border lc rgb '#6165' lw 0.200001
set object 786 polygon from \
  -7.24738, 3.48958 to \
  -7.24691, 3.49045 to \
  -7.14881, 3.56243 to \
  -7.14881, 3.56206 to \
  -9.07424, 0 to \
  -9.12349, 0 to \
  -7.24738, 3.48958 front fs empty border lc rgb '#6165' lw 0.200001
set object 787 polygon from \
  -7.34548, 3.41661 to \
  -7.34501, 3.41749 to \
  -7.24691, 3.49045 to \
  -7.24691, 3.49008 to \
  -9.12329, 0 to \
  -9.17254, 0 to \
  -7.34548, 3.41661 front fs empty border lc rgb '#6165' lw 0.200001
set object 788 polygon from \
  -7.44358, 3.34267 to \
  -7.44311, 3.34355 to \
  -7.34501, 3.41749 to \
  -7.34501, 3.41712 to \
  -9.17234, 0 to \
  -9.22159, 0 to \
  -7.44358, 3.34267 front fs empty border lc rgb '#6165' lw 0.200001
set object 789 polygon from \
  -7.54169, 3.26773 to \
  -7.54121, 3.26863 to \
  -7.44311, 3.34355 to \
  -7.44311, 3.34318 to \
  -9.22139, 0 to \
  -9.27064, 0 to \
  -7.54169, 3.26773 front fs empty border lc rgb '#6165' lw 0.200001
set object 790 polygon from \
  -7.63979, 3.19181 to \
  -7.63931, 3.19273 to \
  -7.54121, 3.26863 to \
  -7.54121, 3.26826 to \
  -9.27044, 0 to \
  -9.31969, 0 to \
  -7.63979, 3.19181 front fs empty border lc rgb '#6165' lw 0.200001
set object 791 polygon from \
  -7.7379, 3.11491 to \
  -7.73741, 3.11584 to \
  -7.63931, 3.19273 to \
  -7.63931, 3.19235 to \
  -9.31949, 0 to \
  -9.36874, 0 to \
  -7.7379, 3.11491 front fs empty border lc rgb '#6165' lw 0.200001
set object 792 polygon from \
  -7.836, 3.03704 to \
  -7.83551, 3.03798 to \
  -7.73741, 3.11585 to \
  -7.73741, 3.11547 to \
  -9.36854, 0 to \
  -9.41779, 0 to \
  -7.836, 3.03704 front fs empty border lc rgb '#6165' lw 0.200001
set object 793 polygon from \
  -7.93411, 2.95818 to \
  -7.93361, 2.95913 to \
  -7.83551, 3.03798 to \
  -7.83551, 3.03761 to \
  -9.41759, 0 to \
  -9.46684, 0 to \
  -7.93411, 2.95818 front fs empty border lc rgb '#6165' lw 0.200001
set object 794 polygon from \
  -8.03221, 2.87835 to \
  -8.03171, 2.87931 to \
  -7.93361, 2.95914 to \
  -7.93361, 2.95876 to \
  -9.46664, 0 to \
  -9.51589, 0 to \
  -8.03221, 2.87835 front fs empty border lc rgb '#6165' lw 0.200001
set object 795 polygon from \
  -8.13031, 2.79752 to \
  -8.12981, 2.7985 to \
  -8.03171, 2.87931 to \
  -8.03171, 2.87893 to \
  -9.51569, 0 to \
  -9.56494, 0 to \
  -8.13031, 2.79752 front fs empty border lc rgb '#6165' lw 0.200001
set object 796 polygon from \
  -8.22841, 2.71573 to \
  -8.22791, 2.71671 to \
  -8.12981, 2.7985 to \
  -8.12981, 2.79813 to \
  -9.56474, 0 to \
  -9.61399, 0 to \
  -8.22841, 2.71573 front fs empty border lc rgb '#6165' lw 0.200001
set object 797 polygon from \
  -8.32652, 2.63294 to \
  -8.32601, 2.63394 to \
  -8.22791, 2.71671 to \
  -8.22791, 2.71634 to \
  -9.61379, 0 to \
  -9.66303, 0 to \
  -8.32652, 2.63294 front fs empty border lc rgb '#6165' lw 0.200001
set object 798 polygon from \
  -8.42462, 2.54918 to \
  -8.42411, 2.55019 to \
  -8.32601, 2.63394 to \
  -8.32601, 2.63357 to \
  -9.66284, 0 to \
  -9.71208, 0 to \
  -8.42462, 2.54918 front fs empty border lc rgb '#6165' lw 0.200001
set object 799 polygon from \
  -8.52273, 2.46444 to \
  -8.52221, 2.46546 to \
  -8.42411, 2.55019 to \
  -8.42411, 2.54982 to \
  -9.71189, 0 to \
  -9.76113, 0 to \
  -8.52273, 2.46444 front fs empty border lc rgb '#6165' lw 0.200001
set object 800 polygon from \
  -8.62083, 2.37871 to \
  -8.62031, 2.37975 to \
  -8.52221, 2.46546 to \
  -8.52221, 2.46508 to \
  -9.76094, 0 to \
  -9.81018, 0 to \
  -8.62083, 2.37871 front fs empty border lc rgb '#6165' lw 0.200001
set object 801 polygon from \
  -8.71893, 2.292 to \
  -8.71841, 2.29305 to \
  -8.62031, 2.37975 to \
  -8.62031, 2.37937 to \
  -9.80999, 0 to \
  -9.85923, 0 to \
  -8.71893, 2.292 front fs empty border lc rgb '#6165' lw 0.200001
set object 802 polygon from \
  -8.81704, 2.20431 to \
  -8.81651, 2.20538 to \
  -8.71841, 2.29305 to \
  -8.71841, 2.29268 to \
  -9.85904, 0 to \
  -9.90828, 0 to \
  -8.81704, 2.20431 front fs empty border lc rgb '#6165' lw 0.200001
set object 803 polygon from \
  -8.91514, 2.11565 to \
  -8.91461, 2.11672 to \
  -8.81651, 2.20538 to \
  -8.81651, 2.205 to \
  -9.90809, 0 to \
  -9.95733, 0 to \
  -8.91514, 2.11565 front fs empty border lc rgb '#6165' lw 0.200001
set object 804 polygon from \
  -9.01325, 2.026 to \
  -9.01271, 2.02709 to \
  -8.91461, 2.11672 to \
  -8.91461, 2.11635 to \
  -9.95714, 0 to \
  -10.0063, 0 to \
  -9.01325, 2.026 front fs empty border lc rgb '#6165' lw 0.200001
set object 805 polygon from \
  -9.11135, 1.93537 to \
  -9.11081, 1.93647 to \
  -9.01271, 2.02709 to \
  -9.01271, 2.02671 to \
  -10.0061, 0 to \
  -10.0554, 0 to \
  -9.11135, 1.93537 front fs empty border lc rgb '#6165' lw 0.200001
set object 806 polygon from \
  -9.20945, 1.84375 to \
  -9.20891, 1.84487 to \
  -9.11081, 1.93647 to \
  -9.11081, 1.93609 to \
  -10.0552, 0 to \
  -10.1044, 0 to \
  -9.20945, 1.84375 front fs empty border lc rgb '#6165' lw 0.200001
set object 807 polygon from \
  -9.30756, 1.75116 to \
  -9.30701, 1.75229 to \
  -9.20891, 1.84487 to \
  -9.20891, 1.8445 to \
  -10.1042, 0 to \
  -10.1535, 0 to \
  -9.30756, 1.75116 front fs empty border lc rgb '#6165' lw 0.200001
set object 808 polygon from \
  -9.40566, 1.65759 to \
  -9.40511, 1.65873 to \
  -9.30701, 1.75229 to \
  -9.30701, 1.75192 to \
  -10.1533, 0 to \
  -10.2025, 0 to \
  -9.40566, 1.65759 front fs empty border lc rgb '#6165' lw 0.200001
set object 809 polygon from \
  -9.50376, 1.56304 to \
  -9.50321, 1.56419 to \
  -9.40511, 1.65873 to \
  -9.40511, 1.65835 to \
  -10.2023, 0 to \
  -10.2516, 0 to \
  -9.50376, 1.56304 front fs empty border lc rgb '#6165' lw 0.200001
set object 810 polygon from \
  -9.60187, 1.4675 to \
  -9.60131, 1.46867 to \
  -9.50321, 1.56419 to \
  -9.50321, 1.56381 to \
  -10.2514, 0 to \
  -10.3006, 0 to \
  -9.60187, 1.4675 front fs empty border lc rgb '#6165' lw 0.200001
set object 811 polygon from \
  -9.69997, 1.37099 to \
  -9.69941, 1.37216 to \
  -9.60131, 1.46867 to \
  -9.60131, 1.46829 to \
  -10.3004, 0 to \
  -10.3497, 0 to \
  -9.69997, 1.37099 front fs empty border lc rgb '#6165' lw 0.200001
set object 812 polygon from \
  -9.79807, 1.27349 to \
  -9.79751, 1.27468 to \
  -9.69941, 1.37216 to \
  -9.69941, 1.37179 to \
  -10.3495, 0 to \
  -10.3987, 0 to \
  -9.79807, 1.27349 front fs empty border lc rgb '#6165' lw 0.200001
set object 813 polygon from \
  -9.89617, 1.17501 to \
  -9.89561, 1.17621 to \
  -9.79751, 1.27468 to \
  -9.79751, 1.2743 to \
  -10.3985, 0 to \
  -10.4478, 0 to \
  -9.89617, 1.17501 front fs empty border lc rgb '#6165' lw 0.200001
set object 814 polygon from \
  -9.99428, 1.07556 to \
  -9.99371, 1.07677 to \
  -9.89561, 1.17621 to \
  -9.89561, 1.17584 to \
  -10.4476, 0 to \
  -10.4968, 0 to \
  -9.99428, 1.07556 front fs empty border lc rgb '#6165' lw 0.200001
set object 815 polygon from \
  -10.0923, 0.975117 to \
  -10.0918, 0.976333 to \
  -9.99371, 1.07677 to \
  -9.99371, 1.07639 to \
  -10.4966, 0 to \
  -10.5459, 0 to \
  -10.0923, 0.975117 front fs empty border lc rgb '#6165' lw 0.200001
set object 816 polygon from \
  -10.1904, 0.873696 to \
  -10.1899, 0.874924 to \
  -10.0918, 0.976334 to \
  -10.0918, 0.975958 to \
  -10.5457, 0 to \
  -10.5949, 0 to \
  -10.1904, 0.873696 front fs empty border lc rgb '#6165' lw 0.200001
set object 817 polygon from \
  -10.2885, 0.771303 to \
  -10.288, 0.772535 to \
  -10.1899, 0.874926 to \
  -10.1899, 0.874549 to \
  -10.5947, 0 to \
  -10.644, 0 to \
  -10.2885, 0.771303 front fs empty border lc rgb '#6165' lw 0.200001
set object 818 polygon from \
  -10.3866, 0.667926 to \
  -10.3861, 0.669164 to \
  -10.288, 0.772536 to \
  -10.288, 0.772159 to \
  -10.6438, 0 to \
  -10.693, 0 to \
  -10.3866, 0.667926 front fs empty border lc rgb '#6165' lw 0.200001
set object 819 polygon from \
  -10.4847, 0.563568 to \
  -10.4842, 0.564812 to \
  -10.3861, 0.669165 to \
  -10.3861, 0.668789 to \
  -10.6928, 0 to \
  -10.7421, 0 to \
  -10.4847, 0.563568 front fs empty border lc rgb '#6165' lw 0.200001
set object 820 polygon from \
  -10.5828, 0.458226 to \
  -10.5823, 0.45948 to \
  -10.4842, 0.564814 to \
  -10.4842, 0.564437 to \
  -10.7419, 0 to \
  -10.7911, 0 to \
  -10.5828, 0.458226 front fs empty border lc rgb '#6165' lw 0.200001
set object 821 polygon from \
  -10.6809, 0.351904 to \
  -10.6804, 0.353166 to \
  -10.5823, 0.459481 to \
  -10.5823, 0.459105 to \
  -10.7909, 0 to \
  -10.8402, 0 to \
  -10.6809, 0.351904 front fs empty border lc rgb '#6165' lw 0.200001
set object 822 polygon from \
  -10.779, 0.244607 to \
  -10.7785, 0.245872 to \
  -10.6804, 0.353168 to \
  -10.6804, 0.352791 to \
  -10.84, 0 to \
  -10.8892, 0 to \
  -10.779, 0.244607 front fs empty border lc rgb '#6165' lw 0.200001
set object 823 polygon from \
  -10.8771, 0.136323 to \
  -10.8766, 0.137596 to \
  -10.7785, 0.245873 to \
  -10.7785, 0.245496 to \
  -10.889, 0 to \
  -10.9383, 0 to \
  -10.8771, 0.136323 front fs empty border lc rgb '#6165' lw 0.200001
set object 824 polygon from \
  -10.9752, 0.0270595 to \
  -10.9747, 0.0283389 to \
  -10.8766, 0.137597 to \
  -10.8766, 0.137221 to \
  -10.9381, 0 to \
  -10.9873, 0 to \
  -10.9752, 0.0270595 front fs empty border lc rgb '#6165' lw 0.200001
set object 825 polygon from \
  -10.9747, 0.0283402 to \
  -10.9747, 0.0279635 to \
  -10.9871, 0 to \
  -10.9999, 0 to \
  -10.9747, 0.0283402 front fs empty border lc rgb '#6165' lw 0.200001
set object 826 polygon from \
  8.15173, 0.0823773 to \
  8.15198, 0.0823773 to \
  8.25008, 0.000368285 to \
  8.25008, 0 to \
  5.90755, 0 to \
  5.80885, 0.0589485 to \
  8.15173, 0.0823773 front fs empty border lc rgb '#6165' lw 0.200001
set object 827 polygon from \
  8.05363, 0.163405 to \
  8.05388, 0.163407 to \
  8.15198, 0.0823786 to \
  8.15198, 0.0820103 to \
  5.80945, 0.058585 to \
  5.71075, 0.116547 to \
  8.05363, 0.163405 front fs empty border lc rgb '#6165' lw 0.200001
set object 828 polygon from \
  7.95553, 0.24345 to \
  7.95578, 0.243455 to \
  8.05388, 0.163408 to \
  8.05388, 0.16304 to \
  5.71135, 0.116189 to \
  5.61265, 0.173164 to \
  7.95553, 0.24345 front fs empty border lc rgb '#6165' lw 0.200001
set object 829 polygon from \
  7.85743, 0.322515 to \
  7.85768, 0.322523 to \
  7.95578, 0.243456 to \
  7.95578, 0.243088 to \
  5.61325, 0.172812 to \
  5.51455, 0.2288 to \
  7.85743, 0.322515 front fs empty border lc rgb '#6165' lw 0.200001
set object 830 polygon from \
  7.75933, 0.400599 to \
  7.75958, 0.400609 to \
  7.85768, 0.322524 to \
  7.85768, 0.322155 to \
  5.51515, 0.228454 to \
  5.41645, 0.283455 to \
  7.75933, 0.400599 front fs empty border lc rgb '#6165' lw 0.200001
set object 831 polygon from \
  7.66123, 0.477702 to \
  7.66148, 0.477714 to \
  7.75958, 0.40061 to \
  7.75958, 0.400242 to \
  5.41705, 0.283115 to \
  5.31835, 0.337129 to \
  7.66123, 0.477702 front fs empty border lc rgb '#6165' lw 0.200001
set object 832 polygon from \
  7.56313, 0.553823 to \
  7.56338, 0.553838 to \
  7.66148, 0.477715 to \
  7.66148, 0.477347 to \
  5.31895, 0.336795 to \
  5.22025, 0.389822 to \
  7.56313, 0.553823 front fs empty border lc rgb '#6165' lw 0.200001
set object 833 polygon from \
  7.46503, 0.628964 to \
  7.46528, 0.628981 to \
  7.56338, 0.553839 to \
  7.56338, 0.553471 to \
  5.22085, 0.389494 to \
  5.12215, 0.441534 to \
  7.46503, 0.628964 front fs empty border lc rgb '#6165' lw 0.200001
set object 834 polygon from \
  7.36693, 0.703124 to \
  7.36718, 0.703144 to \
  7.46528, 0.628983 to \
  7.46528, 0.628614 to \
  5.12275, 0.441212 to \
  5.02405, 0.492265 to \
  7.36693, 0.703124 front fs empty border lc rgb '#6165' lw 0.200001
set object 835 polygon from \
  7.26883, 0.776303 to \
  7.26908, 0.776325 to \
  7.36718, 0.703145 to \
  7.36718, 0.702777 to \
  5.02465, 0.491949 to \
  4.92595, 0.542015 to \
  7.26883, 0.776303 front fs empty border lc rgb '#6165' lw 0.200001
set object 836 polygon from \
  7.17073, 0.848501 to \
  7.17098, 0.848525 to \
  7.26908, 0.776326 to \
  7.26908, 0.775958 to \
  4.92655, 0.541705 to \
  4.82785, 0.590784 to \
  7.17073, 0.848501 front fs empty border lc rgb '#6165' lw 0.200001
set object 837 polygon from \
  7.07263, 0.919717 to \
  7.07288, 0.919744 to \
  7.17098, 0.848526 to \
  7.17098, 0.848158 to \
  4.82845, 0.59048 to \
  4.72975, 0.638572 to \
  7.07263, 0.919717 front fs empty border lc rgb '#6165' lw 0.200001
set object 838 polygon from \
  6.97453, 0.989953 to \
  6.97478, 0.989983 to \
  7.07288, 0.919746 to \
  7.07288, 0.919377 to \
  4.73035, 0.638274 to \
  4.63165, 0.685379 to \
  6.97453, 0.989953 front fs empty border lc rgb '#6165' lw 0.200001
set object 839 polygon from \
  6.87643, 1.05921 to \
  6.87668, 1.05924 to \
  6.97478, 0.989984 to \
  6.97478, 0.989616 to \
  4.63225, 0.685086 to \
  4.53355, 0.731204 to \
  6.87643, 1.05921 front fs empty border lc rgb '#6165' lw 0.200001
set object 840 polygon from \
  6.77833, 1.12749 to \
  6.77858, 1.12752 to \
  6.87668, 1.05925 to \
  6.87668, 1.05888 to \
  4.53415, 0.730918 to \
  4.43545, 0.776049 to \
  6.77833, 1.12749 front fs empty border lc rgb '#6165' lw 0.200001
set object 841 polygon from \
  6.68023, 1.19478 to \
  6.68048, 1.19482 to \
  6.77858, 1.12752 to \
  6.77858, 1.12715 to \
  4.43605, 0.775769 to \
  4.33735, 0.819913 to \
  6.68023, 1.19478 front fs empty border lc rgb '#6165' lw 0.200001
set object 842 polygon from \
  6.58213, 1.26109 to \
  6.58238, 1.26113 to \
  6.68048, 1.19482 to \
  6.68048, 1.19445 to \
  4.33795, 0.819639 to \
  4.23925, 0.862796 to \
  6.58213, 1.26109 front fs empty border lc rgb '#6165' lw 0.200001
set object 843 polygon from \
  6.48403, 1.32642 to \
  6.48428, 1.32646 to \
  6.58238, 1.26113 to \
  6.58238, 1.26076 to \
  4.23985, 0.862528 to \
  4.14115, 0.904698 to \
  6.48403, 1.32642 front fs empty border lc rgb '#6165' lw 0.200001
set object 844 polygon from \
  6.38593, 1.39077 to \
  6.38618, 1.39082 to \
  6.48428, 1.32646 to \
  6.48428, 1.3261 to \
  4.14175, 0.904436 to \
  4.04305, 0.945619 to \
  6.38593, 1.39077 front fs empty border lc rgb '#6165' lw 0.200001
set object 845 polygon from \
  6.28783, 1.45414 to \
  6.28808, 1.45419 to \
  6.38618, 1.39082 to \
  6.38618, 1.39045 to \
  4.04365, 0.945363 to \
  3.94495, 0.985559 to \
  6.28783, 1.45414 front fs empty border lc rgb '#6165' lw 0.200001
set object 846 polygon from \
  6.18973, 1.51653 to \
  6.18998, 1.51658 to \
  6.28808, 1.45419 to \
  6.28808, 1.45382 to \
  3.94555, 0.985309 to \
  3.84685, 1.02452 to \
  6.18973, 1.51653 front fs empty border lc rgb '#6165' lw 0.200001
set object 847 polygon from \
  6.09163, 1.57793 to \
  6.09188, 1.57799 to \
  6.18998, 1.51658 to \
  6.18998, 1.51621 to \
  3.84745, 1.02428 to \
  3.74875, 1.0625 to \
  6.09163, 1.57793 front fs empty border lc rgb '#6165' lw 0.200001
set object 848 polygon from \
  5.99353, 1.63836 to \
  5.99378, 1.63841 to \
  6.09188, 1.57799 to \
  6.09188, 1.57762 to \
  3.74935, 1.06226 to \
  3.65065, 1.0995 to \
  5.99353, 1.63836 front fs empty border lc rgb '#6165' lw 0.200001
set object 849 polygon from \
  5.89543, 1.69781 to \
  5.89568, 1.69786 to \
  5.99378, 1.63842 to \
  5.99378, 1.63805 to \
  3.65125, 1.09927 to \
  3.55255, 1.13551 to \
  5.89543, 1.69781 front fs empty border lc rgb '#6165' lw 0.200001
set object 850 polygon from \
  5.79733, 1.75627 to \
  5.79758, 1.75633 to \
  5.89568, 1.69786 to \
  5.89568, 1.69749 to \
  3.55315, 1.13529 to \
  3.45445, 1.17055 to \
  5.79733, 1.75627 front fs empty border lc rgb '#6165' lw 0.200001
set object 851 polygon from \
  5.69923, 1.81375 to \
  5.69948, 1.81381 to \
  5.79758, 1.75633 to \
  5.79758, 1.75596 to \
  3.45505, 1.17033 to \
  3.35635, 1.2046 to \
  5.69923, 1.81375 front fs empty border lc rgb '#6165' lw 0.200001
set object 852 polygon from \
  5.60113, 1.87025 to \
  5.60138, 1.87032 to \
  5.69948, 1.81381 to \
  5.69948, 1.81345 to \
  3.35695, 1.20439 to \
  3.25825, 1.23768 to \
  5.60113, 1.87025 front fs empty border lc rgb '#6165' lw 0.200001
set object 853 polygon from \
  5.50303, 1.92577 to \
  5.50328, 1.92584 to \
  5.60138, 1.87032 to \
  5.60138, 1.86995 to \
  3.25885, 1.23747 to \
  3.16015, 1.26977 to \
  5.50303, 1.92577 front fs empty border lc rgb '#6165' lw 0.200001
set object 854 polygon from \
  5.40493, 1.98031 to \
  5.40518, 1.98038 to \
  5.50328, 1.92584 to \
  5.50328, 1.92547 to \
  3.16075, 1.26956 to \
  3.06205, 1.30088 to \
  5.40493, 1.98031 front fs empty border lc rgb '#6165' lw 0.200001
set object 855 polygon from \
  5.30683, 2.03387 to \
  5.30708, 2.03394 to \
  5.40518, 1.98038 to \
  5.40518, 1.98002 to \
  3.06265, 1.30068 to \
  2.96395, 1.33101 to \
  5.30683, 2.03387 front fs empty border lc rgb '#6165' lw 0.200001
set object 856 polygon from \
  5.20873, 2.08645 to \
  5.20898, 2.08652 to \
  5.30708, 2.03395 to \
  5.30708, 2.03358 to \
  2.96455, 1.33082 to \
  2.86585, 1.36016 to \
  5.20873, 2.08645 front fs empty border lc rgb '#6165' lw 0.200001
set object 857 polygon from \
  5.11063, 2.13805 to \
  5.11088, 2.13812 to \
  5.20898, 2.08653 to \
  5.20898, 2.08616 to \
  2.86645, 1.35997 to \
  2.76775, 1.38833 to \
  5.11063, 2.13805 front fs empty border lc rgb '#6165' lw 0.200001
set object 858 polygon from \
  5.01253, 2.18866 to \
  5.01278, 2.18874 to \
  5.11088, 2.13813 to \
  5.11088, 2.13776 to \
  2.76835, 1.38815 to \
  2.66965, 1.41551 to \
  5.01253, 2.18866 front fs empty border lc rgb '#6165' lw 0.200001
set object 859 polygon from \
  4.91443, 2.2383 to \
  4.91468, 2.23838 to \
  5.01278, 2.18874 to \
  5.01278, 2.18837 to \
  2.67025, 1.41534 to \
  2.57155, 1.44172 to \
  4.91443, 2.2383 front fs empty border lc rgb '#6165' lw 0.200001
set object 860 polygon from \
  4.81633, 2.28695 to \
  4.81658, 2.28704 to \
  4.91468, 2.23838 to \
  4.91468, 2.23801 to \
  2.57215, 1.44155 to \
  2.47345, 1.46694 to \
  4.81633, 2.28695 front fs empty border lc rgb '#6165' lw 0.200001
set object 861 polygon from \
  4.71823, 2.33462 to \
  4.71848, 2.33471 to \
  4.81658, 2.28704 to \
  4.81658, 2.28667 to \
  2.47405, 1.46678 to \
  2.37535, 1.49119 to \
  4.71823, 2.33462 front fs empty border lc rgb '#6165' lw 0.200001
set object 862 polygon from \
  4.62013, 2.38132 to \
  4.62038, 2.38141 to \
  4.71848, 2.33471 to \
  4.71848, 2.33434 to \
  2.37595, 1.49103 to \
  2.27725, 1.51445 to \
  4.62013, 2.38132 front fs empty border lc rgb '#6165' lw 0.200001
set object 863 polygon from \
  4.52203, 2.42703 to \
  4.52228, 2.42712 to \
  4.62038, 2.38141 to \
  4.62038, 2.38104 to \
  2.27785, 1.5143 to \
  2.17915, 1.53673 to \
  4.52203, 2.42703 front fs empty border lc rgb '#6165' lw 0.200001
set object 864 polygon from \
  4.42393, 2.47176 to \
  4.42418, 2.47185 to \
  4.52228, 2.42712 to \
  4.52228, 2.42675 to \
  2.17975, 1.53659 to \
  2.08105, 1.55803 to \
  4.42393, 2.47176 front fs empty border lc rgb '#6165' lw 0.200001
set object 865 polygon from \
  4.32583, 2.51551 to \
  4.32608, 2.5156 to \
  4.42418, 2.47185 to \
  4.42418, 2.47148 to \
  2.08165, 1.5579 to \
  1.98295, 1.57835 to \
  4.32583, 2.51551 front fs empty border lc rgb '#6165' lw 0.200001
set object 866 polygon from \
  4.22773, 2.55827 to \
  4.22798, 2.55837 to \
  4.32608, 2.5156 to \
  4.32608, 2.51523 to \
  1.98355, 1.57822 to \
  1.88485, 1.59769 to \
  4.22773, 2.55827 front fs empty border lc rgb '#6165' lw 0.200001
set object 867 polygon from \
  4.12963, 2.60006 to \
  4.12988, 2.60016 to \
  4.22798, 2.55837 to \
  4.22798, 2.558 to \
  1.88545, 1.59757 to \
  1.78675, 1.61605 to \
  4.12963, 2.60006 front fs empty border lc rgb '#6165' lw 0.200001
set object 868 polygon from \
  4.03153, 2.64087 to \
  4.03178, 2.64097 to \
  4.12988, 2.60016 to \
  4.12988, 2.59979 to \
  1.78735, 1.61593 to \
  1.68865, 1.63343 to \
  4.03153, 2.64087 front fs empty border lc rgb '#6165' lw 0.200001
set object 869 polygon from \
  3.93343, 2.68069 to \
  3.93368, 2.6808 to \
  4.03178, 2.64097 to \
  4.03178, 2.6406 to \
  1.68925, 1.63331 to \
  1.59055, 1.64982 to \
  3.93343, 2.68069 front fs empty border lc rgb '#6165' lw 0.200001
set object 870 polygon from \
  3.83533, 2.71953 to \
  3.83558, 2.71964 to \
  3.93368, 2.6808 to \
  3.93368, 2.68043 to \
  1.59115, 1.64972 to \
  1.49245, 1.66524 to \
  3.83533, 2.71953 front fs empty border lc rgb '#6165' lw 0.200001
set object 871 polygon from \
  3.73723, 2.7574 to \
  3.73748, 2.75751 to \
  3.83558, 2.71964 to \
  3.83558, 2.71928 to \
  1.49305, 1.66514 to \
  1.39435, 1.67967 to \
  3.73723, 2.7574 front fs empty border lc rgb '#6165' lw 0.200001
set object 872 polygon from \
  3.63913, 2.79428 to \
  3.63938, 2.79439 to \
  3.73748, 2.75751 to \
  3.73748, 2.75714 to \
  1.39495, 1.67958 to \
  1.29625, 1.69312 to \
  3.63913, 2.79428 front fs empty border lc rgb '#6165' lw 0.200001
set object 873 polygon from \
  3.54103, 2.83018 to \
  3.54128, 2.8303 to \
  3.63938, 2.79439 to \
  3.63938, 2.79403 to \
  1.29685, 1.69304 to \
  1.19815, 1.7056 to \
  3.54103, 2.83018 front fs empty border lc rgb '#6165' lw 0.200001
set object 874 polygon from \
  3.44293, 2.8651 to \
  3.44318, 2.86522 to \
  3.54128, 2.8303 to \
  3.54128, 2.82993 to \
  1.19875, 1.70551 to \
  1.10005, 1.71709 to \
  3.44293, 2.8651 front fs empty border lc rgb '#6165' lw 0.200001
set object 875 polygon from \
  3.34483, 2.89904 to \
  3.34508, 2.89916 to \
  3.44318, 2.86522 to \
  3.44318, 2.86485 to \
  1.10065, 1.71701 to \
  1.00195, 1.7276 to \
  3.34483, 2.89904 front fs empty border lc rgb '#6165' lw 0.200001
set object 876 polygon from \
  3.24673, 2.932 to \
  3.24698, 2.93212 to \
  3.34508, 2.89916 to \
  3.34508, 2.89879 to \
  1.00255, 1.72753 to \
  0.903846, 1.73713 to \
  3.24673, 2.932 front fs empty border lc rgb '#6165' lw 0.200001
set object 877 polygon from \
  3.14863, 2.96397 to \
  3.14888, 2.9641 to \
  3.24698, 2.93212 to \
  3.24698, 2.93175 to \
  0.904442, 1.73706 to \
  0.805746, 1.74567 to \
  3.14863, 2.96397 front fs empty border lc rgb '#6165' lw 0.200001
set object 878 polygon from \
  3.05053, 2.99497 to \
  3.05078, 2.9951 to \
  3.14888, 2.9641 to \
  3.14888, 2.96373 to \
  0.806342, 1.74561 to \
  0.707646, 1.75324 to \
  3.05053, 2.99497 front fs empty border lc rgb '#6165' lw 0.200001
set object 879 polygon from \
  2.95243, 3.02498 to \
  2.95268, 3.02511 to \
  3.05078, 2.9951 to \
  3.05078, 2.99473 to \
  0.708242, 1.75319 to \
  0.609546, 1.75983 to \
  2.95243, 3.02498 front fs empty border lc rgb '#6165' lw 0.200001
set object 880 polygon from \
  2.85433, 3.05402 to \
  2.85458, 3.05415 to \
  2.95268, 3.02512 to \
  2.95268, 3.02475 to \
  0.610142, 1.75978 to \
  0.511446, 1.76543 to \
  2.85433, 3.05402 front fs empty border lc rgb '#6165' lw 0.200001
set object 881 polygon from \
  2.75623, 3.08207 to \
  2.75648, 3.08221 to \
  2.85458, 3.05415 to \
  2.85458, 3.05378 to \
  0.512042, 1.76539 to \
  0.413346, 1.77006 to \
  2.75623, 3.08207 front fs empty border lc rgb '#6165' lw 0.200001
set object 882 polygon from \
  2.65813, 3.10914 to \
  2.65838, 3.10928 to \
  2.75648, 3.08221 to \
  2.75648, 3.08184 to \
  0.413942, 1.77002 to \
  0.315246, 1.7737 to \
  2.65813, 3.10914 front fs empty border lc rgb '#6165' lw 0.200001
set object 883 polygon from \
  2.56003, 3.13523 to \
  2.56028, 3.13537 to \
  2.65838, 3.10928 to \
  2.65838, 3.10891 to \
  0.315842, 1.77367 to \
  0.217146, 1.77636 to \
  2.56003, 3.13523 front fs empty border lc rgb '#6165' lw 0.200001
set object 884 polygon from \
  2.46193, 3.16034 to \
  2.46218, 3.16049 to \
  2.56028, 3.13537 to \
  2.56028, 3.13501 to \
  0.217742, 1.77634 to \
  0.119046, 1.77804 to \
  2.46193, 3.16034 front fs empty border lc rgb '#6165' lw 0.200001
set object 885 polygon from \
  2.36383, 3.18447 to \
  2.36408, 3.18462 to \
  2.46218, 3.16049 to \
  2.46218, 3.16012 to \
  0.119642, 1.77802 to \
  0.0209452, 1.77874 to \
  2.36383, 3.18447 front fs empty border lc rgb '#6165' lw 0.200001
set object 886 polygon from \
  2.26573, 3.20762 to \
  2.26598, 3.20777 to \
  2.36408, 3.18462 to \
  2.36408, 3.18425 to \
  0.0215419, 1.77873 to \
  -0.0771548, 1.77846 to \
  2.26573, 3.20762 front fs empty border lc rgb '#6165' lw 0.200001
set object 887 polygon from \
  2.16763, 3.22979 to \
  2.16788, 3.22994 to \
  2.26598, 3.20777 to \
  2.26598, 3.2074 to \
  -0.0765581, 1.77846 to \
  -0.175254, 1.7772 to \
  2.16763, 3.22979 front fs empty border lc rgb '#6165' lw 0.200001
set object 888 polygon from \
  2.06953, 3.25097 to \
  2.06978, 3.25112 to \
  2.16788, 3.22994 to \
  2.16788, 3.22957 to \
  -0.174658, 1.7772 to \
  -0.273354, 1.77496 to \
  2.06953, 3.25097 front fs empty border lc rgb '#6165' lw 0.200001
set object 889 polygon from \
  1.97143, 3.27118 to \
  1.97168, 3.27133 to \
  2.06978, 3.25113 to \
  2.06978, 3.25076 to \
  -0.272758, 1.77496 to \
  -0.371454, 1.77173 to \
  1.97143, 3.27118 front fs empty border lc rgb '#6165' lw 0.200001
set object 890 polygon from \
  1.87333, 3.2904 to \
  1.87358, 3.29056 to \
  1.97168, 3.27133 to \
  1.97168, 3.27096 to \
  -0.370858, 1.77174 to \
  -0.469554, 1.76753 to \
  1.87333, 3.2904 front fs empty border lc rgb '#6165' lw 0.200001
set object 891 polygon from \
  1.77523, 3.30864 to \
  1.77548, 3.3088 to \
  1.87358, 3.29056 to \
  1.87358, 3.29019 to \
  -0.468958, 1.76754 to \
  -0.567654, 1.76234 to \
  1.77523, 3.30864 front fs empty border lc rgb '#6165' lw 0.200001
set object 892 polygon from \
  1.67713, 3.32591 to \
  1.67738, 3.32607 to \
  1.77548, 3.3088 to \
  1.77548, 3.30844 to \
  -0.567058, 1.76236 to \
  -0.665754, 1.75617 to \
  1.67713, 3.32591 front fs empty border lc rgb '#6165' lw 0.200001
set object 893 polygon from \
  1.57903, 3.34219 to \
  1.57928, 3.34235 to \
  1.67738, 3.32607 to \
  1.67738, 3.3257 to \
  -0.665158, 1.7562 to \
  -0.763854, 1.74903 to \
  1.57903, 3.34219 front fs empty border lc rgb '#6165' lw 0.200001
set object 894 polygon from \
  1.48093, 3.35749 to \
  1.48118, 3.35765 to \
  1.57928, 3.34235 to \
  1.57928, 3.34198 to \
  -0.763258, 1.74906 to \
  -0.861954, 1.7409 to \
  1.48093, 3.35749 front fs empty border lc rgb '#6165' lw 0.200001
set object 895 polygon from \
  1.38283, 3.3718 to \
  1.38308, 3.37197 to \
  1.48118, 3.35765 to \
  1.48118, 3.35729 to \
  -0.861358, 1.74094 to \
  -0.960054, 1.73179 to \
  1.38283, 3.3718 front fs empty border lc rgb '#6165' lw 0.200001
set object 896 polygon from \
  1.28473, 3.38514 to \
  1.28498, 3.38531 to \
  1.38308, 3.37198 to \
  1.38308, 3.37161 to \
  -0.959458, 1.73183 to \
  -1.05815, 1.7217 to \
  1.28473, 3.38514 front fs empty border lc rgb '#6165' lw 0.200001
set object 897 polygon from \
  1.18663, 3.3975 to \
  1.18688, 3.39767 to \
  1.28498, 3.38532 to \
  1.28498, 3.38495 to \
  -1.05755, 1.72175 to \
  -1.15625, 1.71062 to \
  1.18663, 3.3975 front fs empty border lc rgb '#6165' lw 0.200001
set object 898 polygon from \
  1.08853, 3.40887 to \
  1.08878, 3.40905 to \
  1.18688, 3.39768 to \
  1.18688, 3.39731 to \
  -1.15565, 1.71068 to \
  -1.25435, 1.69857 to \
  1.08853, 3.40887 front fs empty border lc rgb '#6165' lw 0.200001
set object 899 polygon from \
  0.990428, 3.41927 to \
  0.990675, 3.41945 to \
  1.08878, 3.40905 to \
  1.08878, 3.40868 to \
  -1.25375, 1.69864 to \
  -1.35245, 1.68554 to \
  0.990428, 3.41927 front fs empty border lc rgb '#6165' lw 0.200001
set object 900 polygon from \
  0.892327, 3.42868 to \
  0.892575, 3.42887 to \
  0.990675, 3.41945 to \
  0.990675, 3.41908 to \
  -1.35185, 1.68561 to \
  -1.45055, 1.67152 to \
  0.892327, 3.42868 front fs empty border lc rgb '#6165' lw 0.200001
set object 901 polygon from \
  0.794227, 3.43711 to \
  0.794475, 3.4373 to \
  0.892575, 3.42887 to \
  0.892575, 3.4285 to \
  -1.44995, 1.6716 to \
  -1.54865, 1.65653 to \
  0.794227, 3.43711 front fs empty border lc rgb '#6165' lw 0.200001
set object 902 polygon from \
  0.696127, 3.44457 to \
  0.696375, 3.44476 to \
  0.794475, 3.4373 to \
  0.794475, 3.43693 to \
  -1.54805, 1.65661 to \
  -1.64675, 1.64055 to \
  0.696127, 3.44457 front fs empty border lc rgb '#6165' lw 0.200001
set object 903 polygon from \
  0.598026, 3.45104 to \
  0.598275, 3.45123 to \
  0.696375, 3.44476 to \
  0.696375, 3.44439 to \
  -1.64615, 1.64064 to \
  -1.74485, 1.62359 to \
  0.598026, 3.45104 front fs empty border lc rgb '#6165' lw 0.200001
set object 904 polygon from \
  0.499926, 3.45653 to \
  0.500175, 3.45672 to \
  0.598275, 3.45123 to \
  0.598275, 3.45086 to \
  -1.74425, 1.62369 to \
  -1.84295, 1.60565 to \
  0.499926, 3.45653 front fs empty border lc rgb '#6165' lw 0.200001
set object 905 polygon from \
  0.401825, 3.46103 to \
  0.402075, 3.46123 to \
  0.500175, 3.45672 to \
  0.500175, 3.45635 to \
  -1.84235, 1.60575 to \
  -1.94105, 1.58673 to \
  0.401825, 3.46103 front fs empty border lc rgb '#6165' lw 0.200001
set object 906 polygon from \
  0.303724, 3.46456 to \
  0.303975, 3.46476 to \
  0.402075, 3.46123 to \
  0.402075, 3.46086 to \
  -1.94045, 1.58684 to \
  -2.03915, 1.56683 to \
  0.303724, 3.46456 front fs empty border lc rgb '#6165' lw 0.200001
set object 907 polygon from \
  0.205624, 3.46711 to \
  0.205875, 3.46731 to \
  0.303975, 3.46476 to \
  0.303975, 3.46439 to \
  -2.03855, 1.56694 to \
  -2.13725, 1.54595 to \
  0.205624, 3.46711 front fs empty border lc rgb '#6165' lw 0.200001
set object 908 polygon from \
  0.107524, 3.46867 to \
  0.107775, 3.46888 to \
  0.205875, 3.46731 to \
  0.205875, 3.46694 to \
  -2.13665, 1.54607 to \
  -2.23535, 1.52408 to \
  0.107524, 3.46867 front fs empty border lc rgb '#6165' lw 0.200001
set object 909 polygon from \
  0.00942406, 3.46926 to \
  0.00967418, 3.46947 to \
  0.107775, 3.46888 to \
  0.107775, 3.46851 to \
  -2.23475, 1.52421 to \
  -2.33345, 1.50124 to \
  0.00942406, 3.46926 front fs empty border lc rgb '#6165' lw 0.200001
set object 910 polygon from \
  -0.0886755, 3.46886 to \
  -0.0884258, 3.46907 to \
  0.00967403, 3.46947 to \
  0.00967403, 3.4691 to \
  -2.33285, 1.50137 to \
  -2.43155, 1.47742 to \
  -0.0886755, 3.46886 front fs empty border lc rgb '#6165' lw 0.200001
set object 911 polygon from \
  -0.186775, 3.46749 to \
  -0.186525, 3.4677 to \
  -0.0884259, 3.46907 to \
  -0.0884259, 3.46871 to \
  -2.43095, 1.47755 to \
  -2.52965, 1.45261 to \
  -0.186775, 3.46749 front fs empty border lc rgb '#6165' lw 0.200001
set object 912 polygon from \
  -0.284875, 3.46513 to \
  -0.284625, 3.46534 to \
  -0.186525, 3.4677 to \
  -0.186525, 3.46733 to \
  -2.52905, 1.45275 to \
  -2.62775, 1.42682 to \
  -0.284875, 3.46513 front fs empty border lc rgb '#6165' lw 0.200001
set object 913 polygon from \
  -0.382974, 3.46179 to \
  -0.382725, 3.46201 to \
  -0.284625, 3.46534 to \
  -0.284625, 3.46497 to \
  -2.62715, 1.42697 to \
  -2.72585, 1.40005 to \
  -0.382974, 3.46179 front fs empty border lc rgb '#6165' lw 0.200001
set object 914 polygon from \
  -0.481076, 3.45747 to \
  -0.480825, 3.45769 to \
  -0.382725, 3.46201 to \
  -0.382725, 3.46164 to \
  -2.72525, 1.40021 to \
  -2.82395, 1.37231 to \
  -0.481076, 3.45747 front fs empty border lc rgb '#6165' lw 0.200001
set object 915 polygon from \
  -0.579176, 3.45217 to \
  -0.578925, 3.45239 to \
  -0.480825, 3.45769 to \
  -0.480825, 3.45732 to \
  -2.82335, 1.37247 to \
  -2.92205, 1.34358 to \
  -0.579176, 3.45217 front fs empty border lc rgb '#6165' lw 0.200001
set object 916 polygon from \
  -0.677276, 3.44588 to \
  -0.677025, 3.44611 to \
  -0.578925, 3.45239 to \
  -0.578925, 3.45202 to \
  -2.92145, 1.34374 to \
  -3.02015, 1.31386 to \
  -0.677276, 3.44588 front fs empty border lc rgb '#6165' lw 0.200001
set object 917 polygon from \
  -0.775376, 3.43862 to \
  -0.775125, 3.43885 to \
  -0.677025, 3.44611 to \
  -0.677025, 3.44574 to \
  -3.01955, 1.31404 to \
  -3.11825, 1.28317 to \
  -0.775376, 3.43862 front fs empty border lc rgb '#6165' lw 0.200001
set object 918 polygon from \
  -0.873477, 3.43038 to \
  -0.873225, 3.43061 to \
  -0.775125, 3.43885 to \
  -0.775125, 3.43848 to \
  -3.11765, 1.28335 to \
  -3.21635, 1.2515 to \
  -0.873477, 3.43038 front fs empty border lc rgb '#6165' lw 0.200001
set object 919 polygon from \
  -0.971578, 3.42115 to \
  -0.971325, 3.42138 to \
  -0.873225, 3.43061 to \
  -0.873225, 3.43024 to \
  -3.21575, 1.25168 to \
  -3.31445, 1.21885 to \
  -0.971578, 3.42115 front fs empty border lc rgb '#6165' lw 0.200001
set object 920 polygon from \
  -1.06968, 3.41094 to \
  -1.06942, 3.41118 to \
  -0.971325, 3.42139 to \
  -0.971325, 3.42102 to \
  -3.31385, 1.21904 to \
  -3.41255, 1.18521 to \
  -1.06968, 3.41094 front fs empty border lc rgb '#6165' lw 0.200001
set object 921 polygon from \
  -1.16777, 3.39975 to \
  -1.16752, 3.4 to \
  -1.06942, 3.41118 to \
  -1.06942, 3.41081 to \
  -3.41195, 1.18541 to \
  -3.51065, 1.15059 to \
  -1.16777, 3.39975 front fs empty border lc rgb '#6165' lw 0.200001
set object 922 polygon from \
  -1.26588, 3.38759 to \
  -1.26562, 3.38783 to \
  -1.16752, 3.4 to \
  -1.16752, 3.39963 to \
  -3.51005, 1.1508 to \
  -3.60875, 1.115 to \
  -1.26588, 3.38759 front fs empty border lc rgb '#6165' lw 0.200001
set object 923 polygon from \
  -1.36398, 3.37443 to \
  -1.36372, 3.37468 to \
  -1.26562, 3.38783 to \
  -1.26562, 3.38746 to \
  -3.60815, 1.11521 to \
  -3.70685, 1.07842 to \
  -1.36398, 3.37443 front fs empty border lc rgb '#6165' lw 0.200001
set object 924 polygon from \
  -1.46208, 3.3603 to \
  -1.46182, 3.36056 to \
  -1.36372, 3.37468 to \
  -1.36372, 3.37432 to \
  -3.70625, 1.07863 to \
  -3.80495, 1.04086 to \
  -1.46208, 3.3603 front fs empty border lc rgb '#6165' lw 0.200001
set object 925 polygon from \
  -1.56018, 3.34519 to \
  -1.55992, 3.34545 to \
  -1.46182, 3.36056 to \
  -1.46182, 3.36019 to \
  -3.80435, 1.04108 to \
  -3.90305, 1.00232 to \
  -1.56018, 3.34519 front fs empty border lc rgb '#6165' lw 0.200001
set object 926 polygon from \
  -1.65828, 3.3291 to \
  -1.65802, 3.32936 to \
  -1.55992, 3.34545 to \
  -1.55992, 3.34508 to \
  -3.90245, 1.00255 to \
  -4.00115, 0.962794 to \
  -1.65828, 3.3291 front fs empty border lc rgb '#6165' lw 0.200001
set object 927 polygon from \
  -1.75638, 3.31203 to \
  -1.75612, 3.31229 to \
  -1.65802, 3.32936 to \
  -1.65802, 3.32899 to \
  -4.00055, 0.963027 to \
  -4.09925, 0.922292 to \
  -1.75638, 3.31203 front fs empty border lc rgb '#6165' lw 0.200001
set object 928 polygon from \
  -1.85448, 3.29397 to \
  -1.85422, 3.29423 to \
  -1.75612, 3.31229 to \
  -1.75612, 3.31192 to \
  -4.09865, 0.922531 to \
  -4.19735, 0.880809 to \
  -1.85448, 3.29397 front fs empty border lc rgb '#6165' lw 0.200001
set object 929 polygon from \
  -1.95258, 3.27493 to \
  -1.95232, 3.2752 to \
  -1.85422, 3.29424 to \
  -1.85422, 3.29387 to \
  -4.19675, 0.881054 to \
  -4.29545, 0.838345 to \
  -1.95258, 3.27493 front fs empty border lc rgb '#6165' lw 0.200001
set object 930 polygon from \
  -2.05068, 3.25492 to \
  -2.05042, 3.25519 to \
  -1.95232, 3.2752 to \
  -1.95232, 3.27483 to \
  -4.29485, 0.838596 to \
  -4.39355, 0.7949 to \
  -2.05068, 3.25492 front fs empty border lc rgb '#6165' lw 0.200001
set object 931 polygon from \
  -2.14878, 3.23392 to \
  -2.14852, 3.23419 to \
  -2.05042, 3.25519 to \
  -2.05042, 3.25482 to \
  -4.39295, 0.795157 to \
  -4.49165, 0.750474 to \
  -2.14878, 3.23392 front fs empty border lc rgb '#6165' lw 0.200001
set object 932 polygon from \
  -2.24688, 3.21194 to \
  -2.24662, 3.21222 to \
  -2.14852, 3.23419 to \
  -2.14852, 3.23382 to \
  -4.49105, 0.750737 to \
  -4.58975, 0.705067 to \
  -2.24688, 3.21194 front fs empty border lc rgb '#6165' lw 0.200001
set object 933 polygon from \
  -2.34498, 3.18898 to \
  -2.34472, 3.18926 to \
  -2.24662, 3.21222 to \
  -2.24662, 3.21185 to \
  -4.58915, 0.705336 to \
  -4.68785, 0.658679 to \
  -2.34498, 3.18898 front fs empty border lc rgb '#6165' lw 0.200001
set object 934 polygon from \
  -2.44309, 3.16504 to \
  -2.44282, 3.16532 to \
  -2.34472, 3.18926 to \
  -2.34472, 3.18889 to \
  -4.68725, 0.658954 to \
  -4.78595, 0.61131 to \
  -2.44309, 3.16504 front fs empty border lc rgb '#6165' lw 0.200001
set object 935 polygon from \
  -2.54119, 3.14011 to \
  -2.54092, 3.1404 to \
  -2.44282, 3.16532 to \
  -2.44282, 3.16495 to \
  -4.78535, 0.611591 to \
  -4.88405, 0.56296 to \
  -2.54119, 3.14011 front fs empty border lc rgb '#6165' lw 0.200001
set object 936 polygon from \
  -2.63929, 3.11421 to \
  -2.63902, 3.1145 to \
  -2.54092, 3.14041 to \
  -2.54092, 3.14004 to \
  -4.88345, 0.563246 to \
  -4.98215, 0.513629 to \
  -2.63929, 3.11421 front fs empty border lc rgb '#6165' lw 0.200001
set object 937 polygon from \
  -2.73739, 3.08732 to \
  -2.73712, 3.08762 to \
  -2.63902, 3.11451 to \
  -2.63902, 3.11414 to \
  -4.98155, 0.513921 to \
  -5.08025, 0.463317 to \
  -2.73739, 3.08732 front fs empty border lc rgb '#6165' lw 0.200001
set object 938 polygon from \
  -2.83549, 3.05946 to \
  -2.83522, 3.05976 to \
  -2.73712, 3.08762 to \
  -2.73712, 3.08726 to \
  -5.07965, 0.463615 to \
  -5.17835, 0.412024 to \
  -2.83549, 3.05946 front fs empty border lc rgb '#6165' lw 0.200001
set object 939 polygon from \
  -2.9336, 3.03061 to \
  -2.93332, 3.03092 to \
  -2.83522, 3.05976 to \
  -2.83522, 3.05939 to \
  -5.17775, 0.412328 to \
  -5.27645, 0.359749 to \
  -2.9336, 3.03061 front fs empty border lc rgb '#6165' lw 0.200001
set object 940 polygon from \
  -3.0317, 3.00078 to \
  -3.03142, 3.0011 to \
  -2.93332, 3.03092 to \
  -2.93332, 3.03055 to \
  -5.27585, 0.36006 to \
  -5.37455, 0.306494 to \
  -3.0317, 3.00078 front fs empty border lc rgb '#6165' lw 0.200001
set object 941 polygon from \
  -3.1298, 2.96997 to \
  -3.12952, 2.97029 to \
  -3.03142, 3.0011 to \
  -3.03142, 3.00073 to \
  -5.37395, 0.306811 to \
  -5.47265, 0.252258 to \
  -3.1298, 2.96997 front fs empty border lc rgb '#6165' lw 0.200001
set object 942 polygon from \
  -3.2279, 2.93818 to \
  -3.22762, 2.9385 to \
  -3.12952, 2.97029 to \
  -3.12952, 2.96992 to \
  -5.47205, 0.252581 to \
  -5.57075, 0.197041 to \
  -3.2279, 2.93818 front fs empty border lc rgb '#6165' lw 0.200001
set object 943 polygon from \
  -3.326, 2.90541 to \
  -3.32572, 2.90574 to \
  -3.22762, 2.93851 to \
  -3.22762, 2.93814 to \
  -5.57015, 0.19737 to \
  -5.66885, 0.140843 to \
  -3.326, 2.90541 front fs empty border lc rgb '#6165' lw 0.200001
set object 944 polygon from \
  -3.42411, 2.87165 to \
  -3.42382, 2.87199 to \
  -3.32572, 2.90574 to \
  -3.32572, 2.90537 to \
  -5.66825, 0.141178 to \
  -5.76695, 0.0836637 to \
  -3.42411, 2.87165 front fs empty border lc rgb '#6165' lw 0.200001
set object 945 polygon from \
  -3.52221, 2.83692 to \
  -3.52192, 2.83726 to \
  -3.42382, 2.87199 to \
  -3.42382, 2.87162 to \
  -5.76635, 0.0840043 to \
  -5.86505, 0.0255037 to \
  -3.52221, 2.83692 front fs empty border lc rgb '#6165' lw 0.200001
set object 946 polygon from \
  -3.62031, 2.80121 to \
  -3.62002, 2.80155 to \
  -3.52192, 2.83726 to \
  -3.52192, 2.83689 to \
  -5.86445, 0.0258502 to \
  -5.90734, 0 to \
  -5.93535, 0 to \
  -3.62031, 2.80121 front fs empty border lc rgb '#6165' lw 0.200001
set object 947 polygon from \
  -3.71841, 2.76451 to \
  -3.71812, 2.76486 to \
  -3.62002, 2.80155 to \
  -3.62002, 2.80118 to \
  -5.93504, 0 to \
  -5.9844, 0 to \
  -3.71841, 2.76451 front fs empty border lc rgb '#6165' lw 0.200001
set object 948 polygon from \
  -3.81651, 2.72683 to \
  -3.81622, 2.72719 to \
  -3.71812, 2.76486 to \
  -3.71812, 2.76449 to \
  -5.98409, 0 to \
  -6.03345, 0 to \
  -3.81651, 2.72683 front fs empty border lc rgb '#6165' lw 0.200001
set object 949 polygon from \
  -3.91461, 2.68818 to \
  -3.91432, 2.68854 to \
  -3.81622, 2.72719 to \
  -3.81622, 2.72682 to \
  -6.03314, 0 to \
  -6.08249, 0 to \
  -3.91461, 2.68818 front fs empty border lc rgb '#6165' lw 0.200001
set object 950 polygon from \
  -4.01272, 2.64854 to \
  -4.01242, 2.6489 to \
  -3.91432, 2.68854 to \
  -3.91432, 2.68817 to \
  -6.08219, 0 to \
  -6.13154, 0 to \
  -4.01272, 2.64854 front fs empty border lc rgb '#6165' lw 0.200001
set object 951 polygon from \
  -4.11082, 2.60792 to \
  -4.11052, 2.60829 to \
  -4.01242, 2.6489 to \
  -4.01242, 2.64853 to \
  -6.13124, 0 to \
  -6.18059, 0 to \
  -4.11082, 2.60792 front fs empty border lc rgb '#6165' lw 0.200001
set object 952 polygon from \
  -4.20892, 2.56632 to \
  -4.20862, 2.56669 to \
  -4.11052, 2.60829 to \
  -4.11052, 2.60792 to \
  -6.18029, 0 to \
  -6.22964, 0 to \
  -4.20892, 2.56632 front fs empty border lc rgb '#6165' lw 0.200001
set object 953 polygon from \
  -4.30702, 2.52374 to \
  -4.30672, 2.52412 to \
  -4.20862, 2.56669 to \
  -4.20862, 2.56632 to \
  -6.22934, 0 to \
  -6.27868, 0 to \
  -4.30702, 2.52374 front fs empty border lc rgb '#6165' lw 0.200001
set object 954 polygon from \
  -4.40512, 2.48017 to \
  -4.40482, 2.48056 to \
  -4.30672, 2.52412 to \
  -4.30672, 2.52375 to \
  -6.27839, 0 to \
  -6.32773, 0 to \
  -4.40512, 2.48017 front fs empty border lc rgb '#6165' lw 0.200001
set object 955 polygon from \
  -4.50322, 2.43563 to \
  -4.50292, 2.43602 to \
  -4.40482, 2.48056 to \
  -4.40482, 2.48019 to \
  -6.32744, 0 to \
  -6.37678, 0 to \
  -4.50322, 2.43563 front fs empty border lc rgb '#6165' lw 0.200001
set object 956 polygon from \
  -4.60133, 2.3901 to \
  -4.60102, 2.3905 to \
  -4.50292, 2.43602 to \
  -4.50292, 2.43565 to \
  -6.37649, 0 to \
  -6.42583, 0 to \
  -4.60133, 2.3901 front fs empty border lc rgb '#6165' lw 0.200001
set object 957 polygon from \
  -4.69943, 2.3436 to \
  -4.69912, 2.344 to \
  -4.60102, 2.3905 to \
  -4.60102, 2.39013 to \
  -6.42554, 0 to \
  -6.47488, 0 to \
  -4.69943, 2.3436 front fs empty border lc rgb '#6165' lw 0.200001
set object 958 polygon from \
  -4.79753, 2.29611 to \
  -4.79722, 2.29652 to \
  -4.69912, 2.344 to \
  -4.69912, 2.34363 to \
  -6.47459, 0 to \
  -6.52392, 0 to \
  -4.79753, 2.29611 front fs empty border lc rgb '#6165' lw 0.200001
set object 959 polygon from \
  -4.89563, 2.24764 to \
  -4.89532, 2.24805 to \
  -4.79722, 2.29652 to \
  -4.79722, 2.29615 to \
  -6.52364, 0 to \
  -6.57297, 0 to \
  -4.89563, 2.24764 front fs empty border lc rgb '#6165' lw 0.200001
set object 960 polygon from \
  -4.99373, 2.19819 to \
  -4.99342, 2.19861 to \
  -4.89532, 2.24806 to \
  -4.89532, 2.24769 to \
  -6.57269, 0 to \
  -6.62202, 0 to \
  -4.99373, 2.19819 front fs empty border lc rgb '#6165' lw 0.200001
set object 961 polygon from \
  -5.09183, 2.14776 to \
  -5.09152, 2.14819 to \
  -4.99342, 2.19861 to \
  -4.99342, 2.19824 to \
  -6.62174, 0 to \
  -6.67107, 0 to \
  -5.09183, 2.14776 front fs empty border lc rgb '#6165' lw 0.200001
set object 962 polygon from \
  -5.18994, 2.09635 to \
  -5.18962, 2.09678 to \
  -5.09152, 2.14819 to \
  -5.09152, 2.14782 to \
  -6.67079, 0 to \
  -6.72012, 0 to \
  -5.18994, 2.09635 front fs empty border lc rgb '#6165' lw 0.200001
set object 963 polygon from \
  -5.28804, 2.04396 to \
  -5.28772, 2.04439 to \
  -5.18962, 2.09678 to \
  -5.18962, 2.09641 to \
  -6.71984, 0 to \
  -6.76916, 0 to \
  -5.28804, 2.04396 front fs empty border lc rgb '#6165' lw 0.200001
set object 964 polygon from \
  -5.38614, 1.99059 to \
  -5.38582, 1.99103 to \
  -5.28772, 2.04439 to \
  -5.28772, 2.04402 to \
  -6.76889, 0 to \
  -6.81821, 0 to \
  -5.38614, 1.99059 front fs empty border lc rgb '#6165' lw 0.200001
set object 965 polygon from \
  -5.48424, 1.93623 to \
  -5.48392, 1.93668 to \
  -5.38582, 1.99103 to \
  -5.38582, 1.99066 to \
  -6.81794, 0 to \
  -6.86726, 0 to \
  -5.48424, 1.93623 front fs empty border lc rgb '#6165' lw 0.200001
set object 966 polygon from \
  -5.58234, 1.8809 to \
  -5.58202, 1.88135 to \
  -5.48392, 1.93668 to \
  -5.48392, 1.93631 to \
  -6.86699, 0 to \
  -6.91631, 0 to \
  -5.58234, 1.8809 front fs empty border lc rgb '#6165' lw 0.200001
set object 967 polygon from \
  -5.68044, 1.82458 to \
  -5.68012, 1.82504 to \
  -5.58202, 1.88135 to \
  -5.58202, 1.88098 to \
  -6.91604, 0 to \
  -6.96536, 0 to \
  -5.68044, 1.82458 front fs empty border lc rgb '#6165' lw 0.200001
set object 968 polygon from \
  -5.77854, 1.76729 to \
  -5.77822, 1.76774 to \
  -5.68012, 1.82504 to \
  -5.68012, 1.82467 to \
  -6.96509, 0 to \
  -7.0144, 0 to \
  -5.77854, 1.76729 front fs empty border lc rgb '#6165' lw 0.200001
set object 969 polygon from \
  -5.87665, 1.70901 to \
  -5.87632, 1.70947 to \
  -5.77822, 1.76775 to \
  -5.77822, 1.76738 to \
  -7.01414, 0 to \
  -7.06345, 0 to \
  -5.87665, 1.70901 front fs empty border lc rgb '#6165' lw 0.200001
set object 970 polygon from \
  -5.97475, 1.64975 to \
  -5.97442, 1.65022 to \
  -5.87632, 1.70947 to \
  -5.87632, 1.7091 to \
  -7.06319, 0 to \
  -7.1125, 0 to \
  -5.97475, 1.64975 front fs empty border lc rgb '#6165' lw 0.200001
set object 971 polygon from \
  -6.07285, 1.58951 to \
  -6.07252, 1.58998 to \
  -5.97442, 1.65022 to \
  -5.97442, 1.64985 to \
  -7.11224, 0 to \
  -7.16155, 0 to \
  -6.07285, 1.58951 front fs empty border lc rgb '#6165' lw 0.200001
set object 972 polygon from \
  -6.17095, 1.52829 to \
  -6.17062, 1.52877 to \
  -6.07252, 1.58998 to \
  -6.07252, 1.58961 to \
  -7.16129, 0 to \
  -7.2106, 0 to \
  -6.17095, 1.52829 front fs empty border lc rgb '#6165' lw 0.200001
set object 973 polygon from \
  -6.26905, 1.46609 to \
  -6.26872, 1.46657 to \
  -6.17062, 1.52877 to \
  -6.17062, 1.5284 to \
  -7.21034, 0 to \
  -7.25965, 0 to \
  -6.26905, 1.46609 front fs empty border lc rgb '#6165' lw 0.200001
set object 974 polygon from \
  -6.36715, 1.4029 to \
  -6.36682, 1.40339 to \
  -6.26872, 1.46657 to \
  -6.26872, 1.4662 to \
  -7.25939, 0 to \
  -7.30869, 0 to \
  -6.36715, 1.4029 front fs empty border lc rgb '#6165' lw 0.200001
set object 975 polygon from \
  -6.46525, 1.33874 to \
  -6.46492, 1.33923 to \
  -6.36682, 1.40339 to \
  -6.36682, 1.40302 to \
  -7.30844, 0 to \
  -7.35774, 0 to \
  -6.46525, 1.33874 front fs empty border lc rgb '#6165' lw 0.200001
set object 976 polygon from \
  -6.56335, 1.2736 to \
  -6.56302, 1.27409 to \
  -6.46492, 1.33924 to \
  -6.46492, 1.33886 to \
  -7.35749, 0 to \
  -7.40679, 0 to \
  -6.56335, 1.2736 front fs empty border lc rgb '#6165' lw 0.200001
set object 977 polygon from \
  -6.66145, 1.20747 to \
  -6.66112, 1.20797 to \
  -6.56302, 1.2741 to \
  -6.56302, 1.27373 to \
  -7.40654, 0 to \
  -7.45584, 0 to \
  -6.66145, 1.20747 front fs empty border lc rgb '#6165' lw 0.200001
set object 978 polygon from \
  -6.75956, 1.14036 to \
  -6.75922, 1.14087 to \
  -6.66112, 1.20797 to \
  -6.66112, 1.2076 to \
  -7.45559, 0 to \
  -7.50489, 0 to \
  -6.75956, 1.14036 front fs empty border lc rgb '#6165' lw 0.200001
set object 979 polygon from \
  -6.85766, 1.07228 to \
  -6.85732, 1.07279 to \
  -6.75922, 1.14087 to \
  -6.75922, 1.1405 to \
  -7.50464, 0 to \
  -7.55394, 0 to \
  -6.85766, 1.07228 front fs empty border lc rgb '#6165' lw 0.200001
set object 980 polygon from \
  -6.95576, 1.00321 to \
  -6.95542, 1.00373 to \
  -6.85732, 1.07279 to \
  -6.85732, 1.07242 to \
  -7.55369, 0 to \
  -7.60298, 0 to \
  -6.95576, 1.00321 front fs empty border lc rgb '#6165' lw 0.200001
set object 981 polygon from \
  -7.05386, 0.933156 to \
  -7.05352, 0.933676 to \
  -6.95542, 1.00373 to \
  -6.95542, 1.00336 to \
  -7.60274, 0 to \
  -7.65203, 0 to \
  -7.05386, 0.933156 front fs empty border lc rgb '#6165' lw 0.200001
set object 982 polygon from \
  -7.15196, 0.862126 to \
  -7.15162, 0.86265 to \
  -7.05352, 0.933677 to \
  -7.05352, 0.933307 to \
  -7.65179, 0 to \
  -7.70108, 0 to \
  -7.15196, 0.862126 front fs empty border lc rgb '#6165' lw 0.200001
set object 983 polygon from \
  -7.25006, 0.790115 to \
  -7.24972, 0.790643 to \
  -7.15162, 0.862651 to \
  -7.15162, 0.862281 to \
  -7.70084, 0 to \
  -7.75013, 0 to \
  -7.25006, 0.790115 front fs empty border lc rgb '#6165' lw 0.200001
set object 984 polygon from \
  -7.34816, 0.717124 to \
  -7.34782, 0.717656 to \
  -7.24972, 0.790645 to \
  -7.24972, 0.790274 to \
  -7.74989, 0 to \
  -7.79918, 0 to \
  -7.34816, 0.717124 front fs empty border lc rgb '#6165' lw 0.200001
set object 985 polygon from \
  -7.44626, 0.64315 to \
  -7.44592, 0.643687 to \
  -7.34782, 0.717657 to \
  -7.34782, 0.717286 to \
  -7.79894, 0 to \
  -7.84823, 0 to \
  -7.44626, 0.64315 front fs empty border lc rgb '#6165' lw 0.200001
set object 986 polygon from \
  -7.54436, 0.568196 to \
  -7.54402, 0.568737 to \
  -7.44592, 0.643688 to \
  -7.44592, 0.643318 to \
  -7.84799, 0 to \
  -7.89728, 0 to \
  -7.54436, 0.568196 front fs empty border lc rgb '#6165' lw 0.200001
set object 987 polygon from \
  -7.64246, 0.492262 to \
  -7.64212, 0.492806 to \
  -7.54402, 0.568738 to \
  -7.54402, 0.568368 to \
  -7.89704, 0 to \
  -7.94632, 0 to \
  -7.64246, 0.492262 front fs empty border lc rgb '#6165' lw 0.200001
set object 988 polygon from \
  -7.74056, 0.415345 to \
  -7.74022, 0.415895 to \
  -7.64212, 0.492808 to \
  -7.64212, 0.492437 to \
  -7.94609, 0 to \
  -7.99537, 0 to \
  -7.74056, 0.415345 front fs empty border lc rgb '#6165' lw 0.200001
set object 989 polygon from \
  -7.83866, 0.337448 to \
  -7.83832, 0.338002 to \
  -7.74022, 0.415896 to \
  -7.74022, 0.415525 to \
  -7.99514, 0 to \
  -8.04442, 0 to \
  -7.83866, 0.337448 front fs empty border lc rgb '#6165' lw 0.200001
set object 990 polygon from \
  -7.93676, 0.258571 to \
  -7.93642, 0.259128 to \
  -7.83832, 0.338003 to \
  -7.83832, 0.337633 to \
  -8.04419, 0 to \
  -8.09347, 0 to \
  -7.93676, 0.258571 front fs empty border lc rgb '#6165' lw 0.200001
set object 991 polygon from \
  -8.03486, 0.178712 to \
  -8.03452, 0.179273 to \
  -7.93642, 0.259129 to \
  -7.93642, 0.258759 to \
  -8.09324, 0 to \
  -8.14252, 0 to \
  -8.03486, 0.178712 front fs empty border lc rgb '#6165' lw 0.200001
set object 992 polygon from \
  -8.13296, 0.0978723 to \
  -8.13262, 0.098437 to \
  -8.03452, 0.179275 to \
  -8.03452, 0.178904 to \
  -8.14229, 0 to \
  -8.19157, 0 to \
  -8.13296, 0.0978723 front fs empty border lc rgb '#6165' lw 0.200001
set object 993 polygon from \
  -8.23106, 0.0160515 to \
  -8.23072, 0.0166203 to \
  -8.13262, 0.0984385 to \
  -8.13262, 0.0980679 to \
  -8.19134, 0 to \
  -8.24062, 0 to \
  -8.23106, 0.0160515 front fs empty border lc rgb '#6165' lw 0.200001
set object 994 polygon from \
  -8.23072, 0.0166217 to \
  -8.23072, 0.0162511 to \
  -8.24039, 0 to \
  -8.25041, 0 to \
  -8.23072, 0.0166217 front fs empty border lc rgb '#6165' lw 0.200001
plot [-30.9513:46.6043] [-8.68278:95.5107] NaN notitle 

