# settings
set term pdf
set output "bouncing_ball_supportFunction.pdf
set xtics autofreq
set ytics autofreq
set grid back
# axis settings
set xzeroaxis 
set zeroaxis 
set xtics axis 
set xrange [-5.7874e+15:9.19177e+15] 
set yzeroaxis 
set ytics axis 
set yrange [-2.71819e+15:2.99002e+16] 

# plotting sets
set object 1 polygon from \
  -4.53914e+15, 9.13892e+15 to \
  4.53915e+15, 9.13892e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.13892e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 2 polygon from \
  -4.53914e+15, 9.09353e+15 to \
  -4.44836e+15, 9.18431e+15 to \
  4.53915e+15, 9.18431e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.09353e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 3 polygon from \
  -4.53914e+15, 9.04814e+15 to \
  -4.35757e+15, 9.2297e+15 to \
  4.53915e+15, 9.2297e+15 to \
  4.53915e+15, 9.2297e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.04814e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 4 polygon from \
  -4.53914e+15, 9.00275e+15 to \
  -4.26679e+15, 9.2751e+15 to \
  4.53915e+15, 9.2751e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.00275e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 5 polygon from \
  -4.53914e+15, 8.95736e+15 to \
  -4.17601e+15, 9.32049e+15 to \
  4.53915e+15, 9.32049e+15 to \
  4.53915e+15, 9.32049e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.95736e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 6 polygon from \
  -4.53914e+15, 8.91196e+15 to \
  -4.08522e+15, 9.36588e+15 to \
  4.53915e+15, 9.36588e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.91196e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 7 polygon from \
  -4.53914e+15, 8.86657e+15 to \
  -3.99444e+15, 9.41127e+15 to \
  4.53915e+15, 9.41127e+15 to \
  4.53915e+15, 9.41127e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.86657e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 8 polygon from \
  -4.53914e+15, 8.82118e+15 to \
  -3.90366e+15, 9.45666e+15 to \
  4.53915e+15, 9.45666e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.82118e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 9 polygon from \
  -4.53914e+15, 8.77579e+15 to \
  -3.81288e+15, 9.50205e+15 to \
  4.53915e+15, 9.50205e+15 to \
  4.53915e+15, 9.50205e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.77579e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 10 polygon from \
  -4.53914e+15, 8.7304e+15 to \
  -3.72209e+15, 9.54744e+15 to \
  4.53915e+15, 9.54744e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.7304e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 11 polygon from \
  -4.53914e+15, 8.68501e+15 to \
  -3.63131e+15, 9.59284e+15 to \
  4.53915e+15, 9.59284e+15 to \
  4.53915e+15, 9.59284e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.68501e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 12 polygon from \
  -4.53914e+15, 8.63962e+15 to \
  -3.54053e+15, 9.63823e+15 to \
  4.53915e+15, 9.63823e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.63962e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 13 polygon from \
  -4.53914e+15, 8.59422e+15 to \
  -3.44974e+15, 9.68362e+15 to \
  4.53915e+15, 9.68362e+15 to \
  4.53915e+15, 9.68362e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.59422e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 14 polygon from \
  -4.53914e+15, 8.54883e+15 to \
  -3.35896e+15, 9.72901e+15 to \
  4.53915e+15, 9.72901e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.54883e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 15 polygon from \
  -4.53914e+15, 8.50344e+15 to \
  -3.26818e+15, 9.7744e+15 to \
  4.53915e+15, 9.7744e+15 to \
  4.53915e+15, 9.7744e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.50344e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 16 polygon from \
  -4.53914e+15, 8.45805e+15 to \
  -3.1774e+15, 9.81979e+15 to \
  4.53915e+15, 9.81979e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.45805e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 17 polygon from \
  -4.53914e+15, 8.41266e+15 to \
  -3.08661e+15, 9.86519e+15 to \
  4.53915e+15, 9.86519e+15 to \
  4.53915e+15, 9.86519e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.41266e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 18 polygon from \
  -4.53914e+15, 8.36727e+15 to \
  -2.99583e+15, 9.91058e+15 to \
  4.53915e+15, 9.91058e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.36727e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 19 polygon from \
  -4.53914e+15, 8.32188e+15 to \
  -2.90505e+15, 9.95597e+15 to \
  4.53915e+15, 9.95597e+15 to \
  4.53915e+15, 9.95597e+15 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.32188e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 20 polygon from \
  -4.53914e+15, 8.27648e+15 to \
  -2.81426e+15, 1.00014e+16 to \
  4.53915e+15, 1.00014e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.27648e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 21 polygon from \
  -4.53914e+15, 8.23109e+15 to \
  -2.72348e+15, 1.00468e+16 to \
  4.53915e+15, 1.00468e+16 to \
  4.53915e+15, 1.00468e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.23109e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 22 polygon from \
  -4.53914e+15, 8.1857e+15 to \
  -2.6327e+15, 1.00922e+16 to \
  4.53915e+15, 1.00922e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.1857e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 23 polygon from \
  -4.53914e+15, 8.14031e+15 to \
  -2.54192e+15, 1.01376e+16 to \
  4.53915e+15, 1.01376e+16 to \
  4.53915e+15, 1.01376e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.14031e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 24 polygon from \
  -4.53914e+15, 8.09492e+15 to \
  -2.45113e+15, 1.0183e+16 to \
  4.53915e+15, 1.0183e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.09492e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 25 polygon from \
  -4.53914e+15, 8.04953e+15 to \
  -2.36035e+15, 1.02284e+16 to \
  4.53915e+15, 1.02284e+16 to \
  4.53915e+15, 1.02284e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.04953e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 26 polygon from \
  -4.53914e+15, 8.00414e+15 to \
  -2.26957e+15, 1.02738e+16 to \
  4.53915e+15, 1.02738e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.00414e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 27 polygon from \
  -4.53914e+15, 7.95874e+15 to \
  -2.17878e+15, 1.03191e+16 to \
  4.53915e+15, 1.03191e+16 to \
  4.53915e+15, 1.03191e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.95874e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 28 polygon from \
  -4.53914e+15, 7.91335e+15 to \
  -2.088e+15, 1.03645e+16 to \
  4.53915e+15, 1.03645e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.91335e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 29 polygon from \
  -4.53914e+15, 7.86796e+15 to \
  -1.99722e+15, 1.04099e+16 to \
  4.53915e+15, 1.04099e+16 to \
  4.53915e+15, 1.04099e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.86796e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 30 polygon from \
  -4.53914e+15, 7.82257e+15 to \
  -1.90644e+15, 1.04553e+16 to \
  4.53915e+15, 1.04553e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.82257e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 31 polygon from \
  -4.53914e+15, 7.77718e+15 to \
  -1.81565e+15, 1.05007e+16 to \
  4.53915e+15, 1.05007e+16 to \
  4.53915e+15, 1.05007e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.77718e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 32 polygon from \
  -4.53914e+15, 7.73179e+15 to \
  -1.72487e+15, 1.05461e+16 to \
  4.53915e+15, 1.05461e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.73179e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 33 polygon from \
  -4.53914e+15, 7.6864e+15 to \
  -1.63409e+15, 1.05915e+16 to \
  4.53915e+15, 1.05915e+16 to \
  4.53915e+15, 1.05915e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.6864e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 34 polygon from \
  -4.53914e+15, 7.641e+15 to \
  -1.5433e+15, 1.06369e+16 to \
  4.53915e+15, 1.06369e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.641e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 35 polygon from \
  -4.53914e+15, 7.59561e+15 to \
  -1.45252e+15, 1.06823e+16 to \
  4.53915e+15, 1.06823e+16 to \
  4.53915e+15, 1.06823e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.59561e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 36 polygon from \
  -4.53914e+15, 7.55022e+15 to \
  -1.36174e+15, 1.07277e+16 to \
  4.53915e+15, 1.07277e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.55022e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 37 polygon from \
  -4.53914e+15, 7.50483e+15 to \
  -1.27096e+15, 1.07731e+16 to \
  4.53915e+15, 1.07731e+16 to \
  4.53915e+15, 1.07731e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.50483e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 38 polygon from \
  -4.53914e+15, 7.45944e+15 to \
  -1.18017e+15, 1.08185e+16 to \
  4.53915e+15, 1.08185e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.45944e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 39 polygon from \
  -4.53914e+15, 7.41405e+15 to \
  -1.08939e+15, 1.08638e+16 to \
  4.53915e+15, 1.08638e+16 to \
  4.53915e+15, 1.08638e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.41405e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 40 polygon from \
  -4.53914e+15, 7.36866e+15 to \
  -9.98611e+14, 1.09092e+16 to \
  4.53915e+15, 1.09092e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.36866e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 41 polygon from \
  -4.53914e+15, 7.32326e+15 to \
  -9.07828e+14, 1.09546e+16 to \
  4.53915e+15, 1.09546e+16 to \
  4.53915e+15, 1.09546e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.32326e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 42 polygon from \
  -4.53914e+15, 7.27787e+15 to \
  -8.17045e+14, 1.1e+16 to \
  4.53915e+15, 1.1e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.27787e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 43 polygon from \
  -4.53914e+15, 7.23248e+15 to \
  -7.26263e+14, 1.10454e+16 to \
  4.53915e+15, 1.10454e+16 to \
  4.53915e+15, 1.10454e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.23248e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 44 polygon from \
  -4.53914e+15, 7.18709e+15 to \
  -6.3548e+14, 1.10908e+16 to \
  4.53915e+15, 1.10908e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.18709e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 45 polygon from \
  -4.53914e+15, 7.1417e+15 to \
  -5.44697e+14, 1.11362e+16 to \
  4.53915e+15, 1.11362e+16 to \
  4.53915e+15, 1.11362e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.1417e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 46 polygon from \
  -4.53914e+15, 7.09631e+15 to \
  -4.53914e+14, 1.11816e+16 to \
  4.53915e+15, 1.11816e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.09631e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 47 polygon from \
  -4.53914e+15, 7.05092e+15 to \
  -3.63131e+14, 1.1227e+16 to \
  4.53915e+15, 1.1227e+16 to \
  4.53915e+15, 1.1227e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.05092e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 48 polygon from \
  -4.53914e+15, 7.00552e+15 to \
  -2.72348e+14, 1.12724e+16 to \
  4.53915e+15, 1.12724e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.00552e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 49 polygon from \
  -4.53914e+15, 6.96013e+15 to \
  -1.81565e+14, 1.13178e+16 to \
  4.53915e+15, 1.13178e+16 to \
  4.53915e+15, 1.13178e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.96013e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 50 polygon from \
  -4.53914e+15, 6.91474e+15 to \
  -9.07828e+13, 1.13631e+16 to \
  4.53915e+15, 1.13631e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.91474e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 51 polygon from \
  -4.53914e+15, 6.86935e+15 to \
  94, 1.14085e+16 to \
  4.53915e+15, 1.14085e+16 to \
  4.53915e+15, 1.14085e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.86935e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 52 polygon from \
  -4.53914e+15, 6.82396e+15 to \
  9.07829e+13, 1.14539e+16 to \
  4.53915e+15, 1.14539e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.82396e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 53 polygon from \
  -4.53914e+15, 6.77857e+15 to \
  1.81566e+14, 1.14993e+16 to \
  4.53915e+15, 1.14993e+16 to \
  4.53915e+15, 1.14993e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.77857e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 54 polygon from \
  -4.53914e+15, 6.73318e+15 to \
  2.72349e+14, 1.15447e+16 to \
  4.53915e+15, 1.15447e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.73318e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 55 polygon from \
  -4.53914e+15, 6.68778e+15 to \
  3.63132e+14, 1.15901e+16 to \
  4.53915e+15, 1.15901e+16 to \
  4.53915e+15, 1.15901e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.68778e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 56 polygon from \
  -4.53914e+15, 6.64239e+15 to \
  4.53915e+14, 1.16355e+16 to \
  4.53915e+15, 1.16355e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.64239e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 57 polygon from \
  -4.53914e+15, 6.597e+15 to \
  5.44698e+14, 1.16809e+16 to \
  4.53915e+15, 1.16809e+16 to \
  4.53915e+15, 1.16809e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.597e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 58 polygon from \
  -4.53914e+15, 6.55161e+15 to \
  6.35481e+14, 1.17263e+16 to \
  4.53915e+15, 1.17263e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.55161e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 59 polygon from \
  -4.53914e+15, 6.50622e+15 to \
  7.26264e+14, 1.17717e+16 to \
  4.53915e+15, 1.17717e+16 to \
  4.53915e+15, 1.17717e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.50622e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 60 polygon from \
  -4.53914e+15, 6.46083e+15 to \
  8.17046e+14, 1.18171e+16 to \
  4.53915e+15, 1.18171e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.46083e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 61 polygon from \
  -4.53914e+15, 6.41544e+15 to \
  9.07829e+14, 1.18625e+16 to \
  4.53915e+15, 1.18625e+16 to \
  4.53915e+15, 1.18625e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.41544e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 62 polygon from \
  -4.53914e+15, 6.37004e+15 to \
  9.98612e+14, 1.19078e+16 to \
  4.53915e+15, 1.19078e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.37004e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 63 polygon from \
  -4.53914e+15, 6.32465e+15 to \
  1.0894e+15, 1.19532e+16 to \
  4.53915e+15, 1.19532e+16 to \
  4.53915e+15, 1.19532e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.32465e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 64 polygon from \
  -4.53914e+15, 6.27926e+15 to \
  1.18018e+15, 1.19986e+16 to \
  4.53915e+15, 1.19986e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.27926e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 65 polygon from \
  -4.53914e+15, 6.23387e+15 to \
  1.27097e+15, 1.2044e+16 to \
  4.53915e+15, 1.2044e+16 to \
  4.53915e+15, 1.2044e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.23387e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 66 polygon from \
  -4.53914e+15, 6.18848e+15 to \
  1.36175e+15, 1.20894e+16 to \
  4.53915e+15, 1.20894e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.18848e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 67 polygon from \
  -4.53914e+15, 6.14309e+15 to \
  1.45253e+15, 1.21348e+16 to \
  4.53915e+15, 1.21348e+16 to \
  4.53915e+15, 1.21348e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.14309e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 68 polygon from \
  -4.53914e+15, 6.0977e+15 to \
  1.54331e+15, 1.21802e+16 to \
  4.53915e+15, 1.21802e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.0977e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 69 polygon from \
  -4.53914e+15, 6.0523e+15 to \
  1.6341e+15, 1.22256e+16 to \
  4.53915e+15, 1.22256e+16 to \
  4.53915e+15, 1.22256e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.0523e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 70 polygon from \
  -4.53914e+15, 6.00691e+15 to \
  1.72488e+15, 1.2271e+16 to \
  4.53915e+15, 1.2271e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.00691e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 71 polygon from \
  -4.53914e+15, 5.96152e+15 to \
  1.81566e+15, 1.23164e+16 to \
  4.53915e+15, 1.23164e+16 to \
  4.53915e+15, 1.23164e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.96152e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 72 polygon from \
  -4.53914e+15, 5.91613e+15 to \
  1.90645e+15, 1.23618e+16 to \
  4.53915e+15, 1.23618e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.91613e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 73 polygon from \
  -4.53914e+15, 5.87074e+15 to \
  1.99723e+15, 1.24072e+16 to \
  4.53915e+15, 1.24072e+16 to \
  4.53915e+15, 1.24072e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.87074e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 74 polygon from \
  -4.53914e+15, 5.82535e+15 to \
  2.08801e+15, 1.24525e+16 to \
  4.53915e+15, 1.24525e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.82535e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 75 polygon from \
  -4.53914e+15, 5.77996e+15 to \
  2.17879e+15, 1.24979e+16 to \
  4.53915e+15, 1.24979e+16 to \
  4.53915e+15, 1.24979e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.77996e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 76 polygon from \
  -4.53914e+15, 5.73456e+15 to \
  2.26958e+15, 1.25433e+16 to \
  4.53915e+15, 1.25433e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.73456e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 77 polygon from \
  -4.53914e+15, 5.68917e+15 to \
  2.36036e+15, 1.25887e+16 to \
  4.53915e+15, 1.25887e+16 to \
  4.53915e+15, 1.25887e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.68917e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 78 polygon from \
  -4.53914e+15, 5.64378e+15 to \
  2.45114e+15, 1.26341e+16 to \
  4.53915e+15, 1.26341e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.64378e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 79 polygon from \
  -4.53914e+15, 5.59839e+15 to \
  2.54193e+15, 1.26795e+16 to \
  4.53915e+15, 1.26795e+16 to \
  4.53915e+15, 1.26795e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.59839e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 80 polygon from \
  -4.53914e+15, 5.553e+15 to \
  2.63271e+15, 1.27249e+16 to \
  4.53915e+15, 1.27249e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.553e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 81 polygon from \
  -4.53914e+15, 5.50761e+15 to \
  2.72349e+15, 1.27703e+16 to \
  4.53915e+15, 1.27703e+16 to \
  4.53915e+15, 1.27703e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.50761e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 82 polygon from \
  -4.53914e+15, 5.46222e+15 to \
  2.81427e+15, 1.28157e+16 to \
  4.53915e+15, 1.28157e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.46222e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 83 polygon from \
  -4.53914e+15, 5.41682e+15 to \
  2.90506e+15, 1.28611e+16 to \
  4.53915e+15, 1.28611e+16 to \
  4.53915e+15, 1.28611e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.41682e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 84 polygon from \
  -4.53914e+15, 5.37143e+15 to \
  2.99584e+15, 1.29065e+16 to \
  4.53915e+15, 1.29065e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.37143e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 85 polygon from \
  -4.53914e+15, 5.32604e+15 to \
  3.08662e+15, 1.29518e+16 to \
  4.53915e+15, 1.29518e+16 to \
  4.53915e+15, 1.29518e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.32604e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 86 polygon from \
  -4.53914e+15, 5.28065e+15 to \
  3.17741e+15, 1.29972e+16 to \
  4.53915e+15, 1.29972e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.28065e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 87 polygon from \
  -4.53914e+15, 5.23526e+15 to \
  3.26819e+15, 1.30426e+16 to \
  4.53915e+15, 1.30426e+16 to \
  4.53915e+15, 1.30426e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.23526e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 88 polygon from \
  -4.53914e+15, 5.18987e+15 to \
  3.35897e+15, 1.3088e+16 to \
  4.53915e+15, 1.3088e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.18987e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 89 polygon from \
  -4.53914e+15, 5.14448e+15 to \
  3.44975e+15, 1.31334e+16 to \
  4.53915e+15, 1.31334e+16 to \
  4.53915e+15, 1.31334e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.14448e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 90 polygon from \
  -4.53914e+15, 5.09908e+15 to \
  3.54054e+15, 1.31788e+16 to \
  4.53915e+15, 1.31788e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.09908e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 91 polygon from \
  -4.53914e+15, 5.05369e+15 to \
  3.63132e+15, 1.32242e+16 to \
  4.53915e+15, 1.32242e+16 to \
  4.53915e+15, 1.32242e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.05369e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 92 polygon from \
  -4.53914e+15, 5.0083e+15 to \
  3.7221e+15, 1.32696e+16 to \
  4.53915e+15, 1.32696e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.0083e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 93 polygon from \
  -4.53914e+15, 4.96291e+15 to \
  3.81289e+15, 1.3315e+16 to \
  4.53915e+15, 1.3315e+16 to \
  4.53915e+15, 1.3315e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.96291e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 94 polygon from \
  -4.53914e+15, 4.91752e+15 to \
  3.90367e+15, 1.33604e+16 to \
  4.53915e+15, 1.33604e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.91752e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 95 polygon from \
  -4.53914e+15, 4.87213e+15 to \
  3.99445e+15, 1.34058e+16 to \
  4.53915e+15, 1.34058e+16 to \
  4.53915e+15, 1.34058e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.87213e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 96 polygon from \
  -4.53914e+15, 4.82674e+15 to \
  4.08523e+15, 1.34512e+16 to \
  4.53915e+15, 1.34512e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.82674e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 97 polygon from \
  -4.53914e+15, 4.78134e+15 to \
  4.17602e+15, 1.34965e+16 to \
  4.53915e+15, 1.34965e+16 to \
  4.53915e+15, 1.34965e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.78134e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 98 polygon from \
  -4.53914e+15, 4.73595e+15 to \
  4.2668e+15, 1.35419e+16 to \
  4.53915e+15, 1.35419e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.73595e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 99 polygon from \
  -4.53914e+15, 4.69056e+15 to \
  4.35758e+15, 1.35873e+16 to \
  4.53915e+15, 1.35873e+16 to \
  4.53915e+15, 1.35873e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.69056e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 100 polygon from \
  -4.53914e+15, 4.64517e+15 to \
  4.44837e+15, 1.36327e+16 to \
  4.53915e+15, 1.36327e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.64517e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 101 polygon from \
  -4.53914e+15, 4.59978e+15 to \
  4.53915e+15, 1.36781e+16 to \
  4.53915e+15, 1.36781e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.59978e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 102 polygon from \
  -4.53914e+15, 4.64517e+15 to \
  4.53915e+15, 1.37235e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.64517e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 103 polygon from \
  -4.53914e+15, 4.69056e+15 to \
  4.53915e+15, 1.37689e+16 to \
  4.53915e+15, 1.37689e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.69056e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 104 polygon from \
  -4.53914e+15, 4.73595e+15 to \
  4.53915e+15, 1.38143e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.73595e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 105 polygon from \
  -4.53914e+15, 4.78134e+15 to \
  4.53915e+15, 1.38597e+16 to \
  4.53915e+15, 1.38597e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.78134e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 106 polygon from \
  -4.53914e+15, 4.82674e+15 to \
  4.53915e+15, 1.39051e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.82674e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 107 polygon from \
  -4.53914e+15, 4.87213e+15 to \
  4.53915e+15, 1.39505e+16 to \
  4.53915e+15, 1.39505e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.87213e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 108 polygon from \
  -4.53914e+15, 4.91752e+15 to \
  4.53915e+15, 1.39959e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.91752e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 109 polygon from \
  -4.53914e+15, 4.96291e+15 to \
  4.53915e+15, 1.40412e+16 to \
  4.53915e+15, 1.40412e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.96291e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 110 polygon from \
  -4.53914e+15, 5.0083e+15 to \
  4.53915e+15, 1.40866e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.0083e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 111 polygon from \
  -4.53914e+15, 5.05369e+15 to \
  4.53915e+15, 1.4132e+16 to \
  4.53915e+15, 1.4132e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.05369e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 112 polygon from \
  -4.53914e+15, 5.09908e+15 to \
  4.53915e+15, 1.41774e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.09908e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 113 polygon from \
  -4.53914e+15, 5.14448e+15 to \
  4.53915e+15, 1.42228e+16 to \
  4.53915e+15, 1.42228e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.14448e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 114 polygon from \
  -4.53914e+15, 5.18987e+15 to \
  4.53915e+15, 1.42682e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.18987e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 115 polygon from \
  -4.53914e+15, 5.23526e+15 to \
  4.53915e+15, 1.43136e+16 to \
  4.53915e+15, 1.43136e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.23526e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 116 polygon from \
  -4.53914e+15, 5.28065e+15 to \
  4.53915e+15, 1.4359e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.28065e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 117 polygon from \
  -4.53914e+15, 5.32604e+15 to \
  4.53915e+15, 1.44044e+16 to \
  4.53915e+15, 1.44044e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.32604e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 118 polygon from \
  -4.53914e+15, 5.37143e+15 to \
  4.53915e+15, 1.44498e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.37143e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 119 polygon from \
  -4.53914e+15, 5.41682e+15 to \
  4.53915e+15, 1.44952e+16 to \
  4.53915e+15, 1.44952e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.41682e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 120 polygon from \
  -4.53914e+15, 5.46222e+15 to \
  4.53915e+15, 1.45405e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.46222e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 121 polygon from \
  -4.53914e+15, 5.50761e+15 to \
  4.53915e+15, 1.45859e+16 to \
  4.53915e+15, 1.45859e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.50761e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 122 polygon from \
  -4.53914e+15, 5.553e+15 to \
  4.53915e+15, 1.46313e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.553e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 123 polygon from \
  -4.53914e+15, 5.59839e+15 to \
  4.53915e+15, 1.46767e+16 to \
  4.53915e+15, 1.46767e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.59839e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 124 polygon from \
  -4.53914e+15, 5.64378e+15 to \
  4.53915e+15, 1.47221e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.64378e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 125 polygon from \
  -4.53914e+15, 5.68917e+15 to \
  4.53915e+15, 1.47675e+16 to \
  4.53915e+15, 1.47675e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.68917e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 126 polygon from \
  -4.53914e+15, 5.73456e+15 to \
  4.53915e+15, 1.48129e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.73456e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 127 polygon from \
  -4.53914e+15, 5.77996e+15 to \
  4.53915e+15, 1.48583e+16 to \
  4.53915e+15, 1.48583e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.77996e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 128 polygon from \
  -4.53914e+15, 5.82535e+15 to \
  4.53915e+15, 1.49037e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.82535e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 129 polygon from \
  -4.53914e+15, 5.87074e+15 to \
  4.53915e+15, 1.49491e+16 to \
  4.53915e+15, 1.49491e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.87074e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 130 polygon from \
  -4.53914e+15, 5.91613e+15 to \
  4.53915e+15, 1.49945e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.91613e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 131 polygon from \
  -4.53914e+15, 5.96152e+15 to \
  4.53915e+15, 1.50399e+16 to \
  4.53915e+15, 1.50399e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.96152e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 132 polygon from \
  -4.53914e+15, 6.00691e+15 to \
  4.53915e+15, 1.50852e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.00691e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 133 polygon from \
  -4.53914e+15, 6.0523e+15 to \
  4.53915e+15, 1.51306e+16 to \
  4.53915e+15, 1.51306e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.0523e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 134 polygon from \
  -4.53914e+15, 6.0977e+15 to \
  4.53915e+15, 1.5176e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.0977e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 135 polygon from \
  -4.53914e+15, 6.14309e+15 to \
  4.53915e+15, 1.52214e+16 to \
  4.53915e+15, 1.52214e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.14309e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 136 polygon from \
  -4.53914e+15, 6.18848e+15 to \
  4.53915e+15, 1.52668e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.18848e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 137 polygon from \
  -4.53914e+15, 6.23387e+15 to \
  4.53915e+15, 1.53122e+16 to \
  4.53915e+15, 1.53122e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.23387e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 138 polygon from \
  -4.53914e+15, 6.27926e+15 to \
  4.53915e+15, 1.53576e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.27926e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 139 polygon from \
  -4.53914e+15, 6.32465e+15 to \
  4.53915e+15, 1.5403e+16 to \
  4.53915e+15, 1.5403e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.32465e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 140 polygon from \
  -4.53914e+15, 6.37004e+15 to \
  4.53915e+15, 1.54484e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.37004e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 141 polygon from \
  -4.53914e+15, 6.41544e+15 to \
  4.53915e+15, 1.54938e+16 to \
  4.53915e+15, 1.54938e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.41544e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 142 polygon from \
  -4.53914e+15, 6.46083e+15 to \
  4.53915e+15, 1.55392e+16 to \
  4.53915e+15, 1.55392e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.46083e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 143 polygon from \
  -4.53914e+15, 6.50622e+15 to \
  4.53915e+15, 1.55846e+16 to \
  4.53915e+15, 1.55846e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.50622e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 144 polygon from \
  -4.53914e+15, 6.55161e+15 to \
  4.53915e+15, 1.56299e+16 to \
  4.53915e+15, 1.56299e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.55161e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 145 polygon from \
  -4.53914e+15, 6.597e+15 to \
  4.53915e+15, 1.56753e+16 to \
  4.53915e+15, 1.56753e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.597e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 146 polygon from \
  -4.53914e+15, 6.64239e+15 to \
  4.53915e+15, 1.57207e+16 to \
  4.53915e+15, 1.57207e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.64239e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 147 polygon from \
  -4.53914e+15, 6.68778e+15 to \
  4.53915e+15, 1.57661e+16 to \
  4.53915e+15, 1.57661e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.68778e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 148 polygon from \
  -4.53914e+15, 6.73318e+15 to \
  4.53915e+15, 1.58115e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.73318e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 149 polygon from \
  -4.53914e+15, 6.77857e+15 to \
  4.53915e+15, 1.58569e+16 to \
  4.53915e+15, 1.58569e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.77857e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 150 polygon from \
  -4.53914e+15, 6.82396e+15 to \
  4.53915e+15, 1.59023e+16 to \
  4.53915e+15, 1.59023e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.82396e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 151 polygon from \
  -4.53914e+15, 6.86935e+15 to \
  4.53915e+15, 1.59477e+16 to \
  4.53915e+15, 1.59477e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.86935e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 152 polygon from \
  -4.53914e+15, 6.91474e+15 to \
  4.53915e+15, 1.59931e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.91474e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 153 polygon from \
  -4.53914e+15, 6.96013e+15 to \
  4.53915e+15, 1.60385e+16 to \
  4.53915e+15, 1.60385e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.96013e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 154 polygon from \
  -4.53914e+15, 7.00552e+15 to \
  4.53915e+15, 1.60839e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.00552e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 155 polygon from \
  -4.53914e+15, 7.05092e+15 to \
  4.53915e+15, 1.61292e+16 to \
  4.53915e+15, 1.61292e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.05092e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 156 polygon from \
  -4.53914e+15, 7.09631e+15 to \
  4.53915e+15, 1.61746e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.09631e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 157 polygon from \
  -4.53914e+15, 7.1417e+15 to \
  4.53915e+15, 1.622e+16 to \
  4.53915e+15, 1.622e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.1417e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 158 polygon from \
  -4.53914e+15, 7.18709e+15 to \
  4.53915e+15, 1.62654e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.18709e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 159 polygon from \
  -4.53914e+15, 7.23248e+15 to \
  4.53915e+15, 1.63108e+16 to \
  4.53915e+15, 1.63108e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.23248e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 160 polygon from \
  -4.53914e+15, 7.27787e+15 to \
  4.53915e+15, 1.63562e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.27787e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 161 polygon from \
  -4.53914e+15, 7.32326e+15 to \
  4.53915e+15, 1.64016e+16 to \
  4.53915e+15, 1.64016e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.32326e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 162 polygon from \
  -4.53914e+15, 7.36866e+15 to \
  4.53915e+15, 1.6447e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.36866e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 163 polygon from \
  -4.53914e+15, 7.41405e+15 to \
  4.53915e+15, 1.64924e+16 to \
  4.53915e+15, 1.64924e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.41405e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 164 polygon from \
  -4.53914e+15, 7.45944e+15 to \
  4.53915e+15, 1.65378e+16 to \
  4.53915e+15, 1.65378e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.45944e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 165 polygon from \
  -4.53914e+15, 7.50483e+15 to \
  4.53915e+15, 1.65832e+16 to \
  4.53915e+15, 1.65832e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.50483e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 166 polygon from \
  -4.53914e+15, 7.55022e+15 to \
  4.53915e+15, 1.66286e+16 to \
  4.53915e+15, 1.66286e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.55022e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 167 polygon from \
  -4.53914e+15, 7.59561e+15 to \
  4.53915e+15, 1.66739e+16 to \
  4.53915e+15, 1.66739e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.59561e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 168 polygon from \
  -4.53914e+15, 7.641e+15 to \
  4.53915e+15, 1.67193e+16 to \
  4.53915e+15, 1.67193e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.641e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 169 polygon from \
  -4.53914e+15, 7.6864e+15 to \
  4.53915e+15, 1.67647e+16 to \
  4.53915e+15, 1.67647e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.6864e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 170 polygon from \
  -4.53914e+15, 7.73179e+15 to \
  4.53915e+15, 1.68101e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.73179e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 171 polygon from \
  -4.53914e+15, 7.77718e+15 to \
  4.53915e+15, 1.68555e+16 to \
  4.53915e+15, 1.68555e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.77718e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 172 polygon from \
  -4.53914e+15, 7.82257e+15 to \
  4.53915e+15, 1.69009e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.82257e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 173 polygon from \
  -4.53914e+15, 7.86796e+15 to \
  4.53915e+15, 1.69463e+16 to \
  4.53915e+15, 1.69463e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.86796e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 174 polygon from \
  -4.53914e+15, 7.91335e+15 to \
  4.53915e+15, 1.69917e+16 to \
  4.53915e+15, 1.69917e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.91335e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 175 polygon from \
  -4.53914e+15, 7.95874e+15 to \
  4.53915e+15, 1.70371e+16 to \
  4.53915e+15, 1.70371e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.95874e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 176 polygon from \
  -4.53914e+15, 8.00414e+15 to \
  4.53915e+15, 1.70825e+16 to \
  4.53915e+15, 1.70825e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.00414e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 177 polygon from \
  -4.53914e+15, 8.04953e+15 to \
  4.53915e+15, 1.71279e+16 to \
  4.53915e+15, 1.71279e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.04953e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 178 polygon from \
  -4.53914e+15, 8.09492e+15 to \
  4.53915e+15, 1.71733e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.09492e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 179 polygon from \
  -4.53914e+15, 8.14031e+15 to \
  4.53915e+15, 1.72186e+16 to \
  4.53915e+15, 1.72186e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.14031e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 180 polygon from \
  -4.53914e+15, 8.1857e+15 to \
  4.53915e+15, 1.7264e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.1857e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 181 polygon from \
  -4.53914e+15, 8.23109e+15 to \
  4.53915e+15, 1.73094e+16 to \
  4.53915e+15, 1.73094e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.23109e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 182 polygon from \
  -4.53914e+15, 8.27648e+15 to \
  4.53915e+15, 1.73548e+16 to \
  4.53915e+15, 1.73548e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.27648e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 183 polygon from \
  -4.53914e+15, 8.32188e+15 to \
  4.53915e+15, 1.74002e+16 to \
  4.53915e+15, 1.74002e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.32188e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 184 polygon from \
  -4.53914e+15, 8.36727e+15 to \
  4.53915e+15, 1.74456e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.36727e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 185 polygon from \
  -4.53914e+15, 8.41266e+15 to \
  4.53915e+15, 1.7491e+16 to \
  4.53915e+15, 1.7491e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.41266e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 186 polygon from \
  -4.53914e+15, 8.45805e+15 to \
  4.53915e+15, 1.75364e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.45805e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 187 polygon from \
  -4.53914e+15, 8.50344e+15 to \
  4.53915e+15, 1.75818e+16 to \
  4.53915e+15, 1.75818e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.50344e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 188 polygon from \
  -4.53914e+15, 8.54883e+15 to \
  4.53915e+15, 1.76272e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.54883e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 189 polygon from \
  -4.53914e+15, 8.59422e+15 to \
  4.53915e+15, 1.76726e+16 to \
  4.53915e+15, 1.76726e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.59422e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 190 polygon from \
  -4.53914e+15, 8.63962e+15 to \
  4.53915e+15, 1.77179e+16 to \
  4.53915e+15, 1.77179e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.63962e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 191 polygon from \
  -4.53914e+15, 8.68501e+15 to \
  4.53915e+15, 1.77633e+16 to \
  4.53915e+15, 1.77633e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.68501e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 192 polygon from \
  -4.53914e+15, 8.7304e+15 to \
  4.53915e+15, 1.78087e+16 to \
  4.53915e+15, 1.78087e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.7304e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 193 polygon from \
  -4.53914e+15, 8.77579e+15 to \
  4.53915e+15, 1.78541e+16 to \
  4.53915e+15, 1.78541e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.77579e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 194 polygon from \
  -4.53914e+15, 8.82118e+15 to \
  4.53915e+15, 1.78995e+16 to \
  4.53915e+15, 1.78995e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.82118e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 195 polygon from \
  -4.53914e+15, 8.86657e+15 to \
  4.53915e+15, 1.79449e+16 to \
  4.53915e+15, 1.79449e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.86657e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 196 polygon from \
  -4.53914e+15, 8.91196e+15 to \
  4.53915e+15, 1.79903e+16 to \
  4.53915e+15, 1.79903e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.91196e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 197 polygon from \
  -4.53914e+15, 8.95736e+15 to \
  4.53915e+15, 1.80357e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.95736e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 198 polygon from \
  -4.53914e+15, 9.00275e+15 to \
  4.53915e+15, 1.80811e+16 to \
  4.53915e+15, 1.80811e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.00275e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 199 polygon from \
  -4.53914e+15, 9.04814e+15 to \
  4.53915e+15, 1.81265e+16 to \
  4.53915e+15, 1.81265e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.04814e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 200 polygon from \
  -4.53914e+15, 9.09353e+15 to \
  4.53915e+15, 1.81719e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.09353e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 201 polygon from \
  -4.53914e+15, 9.13892e+15 to \
  4.53915e+15, 1.82173e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.13892e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 202 polygon from \
  -4.53914e+15, 9.18431e+15 to \
  4.53915e+15, 1.82626e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.18431e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 203 polygon from \
  -4.53914e+15, 9.2297e+15 to \
  4.53915e+15, 1.8308e+16 to \
  4.53915e+15, 1.8308e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.2297e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 204 polygon from \
  -4.53914e+15, 9.2751e+15 to \
  4.53915e+15, 1.83534e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.2751e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 205 polygon from \
  -4.53914e+15, 9.32049e+15 to \
  4.53915e+15, 1.83988e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.32049e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 206 polygon from \
  -4.53914e+15, 9.36588e+15 to \
  4.53915e+15, 1.84442e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.36588e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 207 polygon from \
  -4.53914e+15, 9.41127e+15 to \
  4.53915e+15, 1.84896e+16 to \
  4.53915e+15, 1.84896e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.41127e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 208 polygon from \
  -4.53914e+15, 9.45666e+15 to \
  4.53915e+15, 1.8535e+16 to \
  4.53915e+15, 1.8535e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.45666e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 209 polygon from \
  -4.53914e+15, 9.50205e+15 to \
  4.53915e+15, 1.85804e+16 to \
  4.53915e+15, 1.85804e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.50205e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 210 polygon from \
  -4.53914e+15, 9.54744e+15 to \
  4.53915e+15, 1.86258e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.54744e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 211 polygon from \
  -4.53914e+15, 9.59284e+15 to \
  4.53915e+15, 1.86712e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.59284e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 212 polygon from \
  -4.53914e+15, 9.63823e+15 to \
  4.53915e+15, 1.87166e+16 to \
  4.53915e+15, 1.87166e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.63823e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 213 polygon from \
  -4.53914e+15, 9.68362e+15 to \
  4.53915e+15, 1.8762e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.68362e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 214 polygon from \
  -4.53914e+15, 9.72901e+15 to \
  4.53915e+15, 1.88073e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.72901e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 215 polygon from \
  -4.53914e+15, 9.7744e+15 to \
  4.53915e+15, 1.88527e+16 to \
  4.53915e+15, 1.88527e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.7744e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 216 polygon from \
  -4.53914e+15, 9.81979e+15 to \
  4.53915e+15, 1.88981e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.81979e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 217 polygon from \
  -4.53914e+15, 9.86519e+15 to \
  4.53915e+15, 1.89435e+16 to \
  4.53915e+15, 1.89435e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.86519e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 218 polygon from \
  -4.53914e+15, 9.91058e+15 to \
  4.53915e+15, 1.89889e+16 to \
  4.53915e+15, 1.89889e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.91058e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 219 polygon from \
  -4.53914e+15, 9.95597e+15 to \
  4.53915e+15, 1.90343e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.95597e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 220 polygon from \
  -4.53914e+15, 1.00014e+16 to \
  4.53915e+15, 1.90797e+16 to \
  4.53915e+15, 1.90797e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.00014e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 221 polygon from \
  -4.53914e+15, 1.00468e+16 to \
  4.53915e+15, 1.91251e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.00468e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 222 polygon from \
  -4.53914e+15, 1.00922e+16 to \
  4.53915e+15, 1.91705e+16 to \
  4.53915e+15, 1.91705e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.00922e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 223 polygon from \
  -4.53914e+15, 1.01376e+16 to \
  4.53915e+15, 1.92159e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.01376e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 224 polygon from \
  -4.53914e+15, 1.0183e+16 to \
  4.53915e+15, 1.92613e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.0183e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 225 polygon from \
  -4.53914e+15, 1.02284e+16 to \
  4.53915e+15, 1.93066e+16 to \
  4.53915e+15, 1.93066e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.02284e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 226 polygon from \
  -4.53914e+15, 1.02738e+16 to \
  4.53915e+15, 1.9352e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.02738e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 227 polygon from \
  -4.53914e+15, 1.03191e+16 to \
  4.53915e+15, 1.93974e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03191e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 228 polygon from \
  -4.53914e+15, 1.03645e+16 to \
  4.53915e+15, 1.94428e+16 to \
  4.53915e+15, 1.94428e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03645e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 229 polygon from \
  -4.53914e+15, 1.04099e+16 to \
  4.53915e+15, 1.94882e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.04099e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 230 polygon from \
  -4.53914e+15, 1.04553e+16 to \
  4.53915e+15, 1.95336e+16 to \
  4.53915e+15, 1.95336e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.04553e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 231 polygon from \
  -4.53914e+15, 1.05007e+16 to \
  4.53915e+15, 1.9579e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.05007e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 232 polygon from \
  -4.53914e+15, 1.05461e+16 to \
  4.53915e+15, 1.96244e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.05461e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 233 polygon from \
  -4.53914e+15, 1.05915e+16 to \
  4.53915e+15, 1.96698e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.05915e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 234 polygon from \
  -4.53914e+15, 1.06369e+16 to \
  4.53915e+15, 1.97152e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.06369e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 235 polygon from \
  -4.53914e+15, 1.06823e+16 to \
  4.53915e+15, 1.97606e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.06823e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 236 polygon from \
  -4.53914e+15, 1.07277e+16 to \
  4.53915e+15, 1.9806e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.07277e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 237 polygon from \
  -4.53914e+15, 1.07731e+16 to \
  4.53915e+15, 1.98513e+16 to \
  4.53915e+15, 1.98513e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.07731e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 238 polygon from \
  -4.53914e+15, 1.08185e+16 to \
  4.53915e+15, 1.98967e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.08185e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 239 polygon from \
  -4.53914e+15, 1.08638e+16 to \
  4.53915e+15, 1.99421e+16 to \
  4.53915e+15, 1.99421e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.08638e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 240 polygon from \
  -4.53914e+15, 1.09092e+16 to \
  4.53915e+15, 1.99875e+16 to \
  4.53915e+15, 1.99875e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.09092e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 241 polygon from \
  -4.53914e+15, 1.09546e+16 to \
  4.53915e+15, 2.00329e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.09546e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 242 polygon from \
  -4.53914e+15, 1.1e+16 to \
  4.53915e+15, 2.00783e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.1e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 243 polygon from \
  -4.53914e+15, 1.10454e+16 to \
  4.53915e+15, 2.01237e+16 to \
  4.53915e+15, 2.01237e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.10454e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 244 polygon from \
  -4.53914e+15, 1.10908e+16 to \
  4.53915e+15, 2.01691e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.10908e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 245 polygon from \
  -4.53914e+15, 1.11362e+16 to \
  4.53915e+15, 2.02145e+16 to \
  4.53915e+15, 2.02145e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.11362e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 246 polygon from \
  -4.53914e+15, 1.11816e+16 to \
  4.53915e+15, 2.02599e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.11816e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 247 polygon from \
  -4.53914e+15, 1.1227e+16 to \
  4.53915e+15, 2.03053e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.1227e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 248 polygon from \
  -4.53914e+15, 1.12724e+16 to \
  4.53915e+15, 2.03507e+16 to \
  4.53915e+15, 2.03507e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.12724e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 249 polygon from \
  -4.53914e+15, 1.13178e+16 to \
  4.53915e+15, 2.0396e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.13178e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 250 polygon from \
  -4.53914e+15, 1.13631e+16 to \
  4.53915e+15, 2.04414e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.13631e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 251 polygon from \
  -4.53914e+15, 1.14085e+16 to \
  4.53915e+15, 2.04868e+16 to \
  4.53915e+15, 2.04868e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.14085e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 252 polygon from \
  -4.53914e+15, 1.14539e+16 to \
  4.53915e+15, 2.05322e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.14539e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 253 polygon from \
  -4.53914e+15, 1.14993e+16 to \
  4.53915e+15, 2.05776e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.14993e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 254 polygon from \
  -4.53914e+15, 1.15447e+16 to \
  4.53915e+15, 2.0623e+16 to \
  4.53915e+15, 2.0623e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.15447e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 255 polygon from \
  -4.53914e+15, 1.15901e+16 to \
  4.53915e+15, 2.06684e+16 to \
  4.53915e+15, 2.06684e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.15901e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 256 polygon from \
  -4.53914e+15, 1.16355e+16 to \
  4.53915e+15, 2.07138e+16 to \
  4.53915e+15, 2.07138e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.16355e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 257 polygon from \
  -4.53914e+15, 1.16809e+16 to \
  4.53915e+15, 2.07592e+16 to \
  4.53915e+15, 2.07592e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.16809e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 258 polygon from \
  -4.53914e+15, 1.17263e+16 to \
  4.53915e+15, 2.08046e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.17263e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 259 polygon from \
  -4.53914e+15, 1.17717e+16 to \
  4.53915e+15, 2.085e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.17717e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 260 polygon from \
  -4.53914e+15, 1.18171e+16 to \
  4.53915e+15, 2.08954e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.18171e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 261 polygon from \
  -4.53914e+15, 1.18625e+16 to \
  4.53915e+15, 2.09407e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.18625e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 262 polygon from \
  -4.53914e+15, 1.19078e+16 to \
  4.53915e+15, 2.09861e+16 to \
  4.53915e+15, 2.09861e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19078e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 263 polygon from \
  -4.53914e+15, 1.19532e+16 to \
  4.53915e+15, 2.10315e+16 to \
  4.53915e+15, 2.10315e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19532e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 264 polygon from \
  -4.53914e+15, 1.19986e+16 to \
  4.53915e+15, 2.10769e+16 to \
  4.53915e+15, 2.10769e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19986e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 265 polygon from \
  -4.53914e+15, 1.2044e+16 to \
  4.53915e+15, 2.11223e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.2044e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 266 polygon from \
  -4.53914e+15, 1.20894e+16 to \
  4.53915e+15, 2.11677e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.20894e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 267 polygon from \
  -4.53914e+15, 1.21348e+16 to \
  4.53915e+15, 2.12131e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.21348e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 268 polygon from \
  -4.53914e+15, 1.21802e+16 to \
  4.53915e+15, 2.12585e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.21802e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 269 polygon from \
  -4.53914e+15, 1.22256e+16 to \
  4.53915e+15, 2.13039e+16 to \
  4.53915e+15, 2.13039e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.22256e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 270 polygon from \
  -4.53914e+15, 1.2271e+16 to \
  4.53915e+15, 2.13493e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.2271e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 271 polygon from \
  -4.53914e+15, 1.23164e+16 to \
  4.53915e+15, 2.13947e+16 to \
  4.53915e+15, 2.13947e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.23164e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 272 polygon from \
  -4.53914e+15, 1.23618e+16 to \
  4.53915e+15, 2.144e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.23618e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 273 polygon from \
  -4.53914e+15, 1.24072e+16 to \
  4.53915e+15, 2.14854e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.24072e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 274 polygon from \
  -4.53914e+15, 1.24525e+16 to \
  4.53915e+15, 2.15308e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.24525e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 275 polygon from \
  -4.53914e+15, 1.24979e+16 to \
  4.53915e+15, 2.15762e+16 to \
  4.53915e+15, 2.15762e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.24979e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 276 polygon from \
  -4.53914e+15, 1.25433e+16 to \
  4.53915e+15, 2.16216e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.25433e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 277 polygon from \
  -4.53914e+15, 1.25887e+16 to \
  4.53915e+15, 2.1667e+16 to \
  4.53915e+15, 2.1667e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.25887e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 278 polygon from \
  -4.53914e+15, 1.26341e+16 to \
  4.53915e+15, 2.17124e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.26341e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 279 polygon from \
  -4.53914e+15, 1.26795e+16 to \
  4.53915e+15, 2.17578e+16 to \
  4.53915e+15, 2.17578e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.26795e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 280 polygon from \
  -4.53914e+15, 1.27249e+16 to \
  4.53915e+15, 2.18032e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27249e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 281 polygon from \
  -4.53914e+15, 1.27703e+16 to \
  4.53915e+15, 2.18486e+16 to \
  4.53915e+15, 2.18486e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27703e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 282 polygon from \
  -4.53914e+15, 1.28157e+16 to \
  4.53915e+15, 2.1894e+16 to \
  4.53915e+15, 2.1894e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.28157e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 283 polygon from \
  -4.53914e+15, 1.28611e+16 to \
  4.53915e+15, 2.19394e+16 to \
  4.53915e+15, 2.19394e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.28611e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 284 polygon from \
  -4.53914e+15, 1.29065e+16 to \
  4.53915e+15, 2.19847e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.29065e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 285 polygon from \
  -4.53914e+15, 1.29518e+16 to \
  4.53915e+15, 2.20301e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.29518e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 286 polygon from \
  -4.53914e+15, 1.29972e+16 to \
  4.53915e+15, 2.20755e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.29972e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 287 polygon from \
  -4.53914e+15, 1.30426e+16 to \
  4.53915e+15, 2.21209e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.30426e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 288 polygon from \
  -4.53914e+15, 1.3088e+16 to \
  4.53915e+15, 2.21663e+16 to \
  4.53915e+15, 2.21663e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.3088e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 289 polygon from \
  -4.53914e+15, 1.31334e+16 to \
  4.53915e+15, 2.22117e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.31334e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 290 polygon from \
  -4.53914e+15, 1.31788e+16 to \
  4.53915e+15, 2.22571e+16 to \
  4.53915e+15, 2.22571e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.31788e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 291 polygon from \
  -4.53914e+15, 1.32242e+16 to \
  4.53915e+15, 2.23025e+16 to \
  4.53915e+15, 2.23025e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.32242e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 292 polygon from \
  -4.53914e+15, 1.32696e+16 to \
  4.53915e+15, 2.23479e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.32696e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 293 polygon from \
  -4.53914e+15, 1.3315e+16 to \
  4.53915e+15, 2.23933e+16 to \
  4.53915e+15, 2.23933e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.3315e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 294 polygon from \
  -4.53914e+15, 1.33604e+16 to \
  4.53915e+15, 2.24387e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.33604e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 295 polygon from \
  -4.53914e+15, 1.34058e+16 to \
  4.53915e+15, 2.24841e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.34058e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 296 polygon from \
  -4.53914e+15, 1.34512e+16 to \
  4.53915e+15, 2.25294e+16 to \
  4.53915e+15, 2.25294e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.34512e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 297 polygon from \
  -4.53914e+15, 1.34965e+16 to \
  4.53915e+15, 2.25748e+16 to \
  4.53915e+15, 2.25748e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.34965e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 298 polygon from \
  -4.53914e+15, 1.35419e+16 to \
  4.53915e+15, 2.26202e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35419e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 299 polygon from \
  -4.53914e+15, 1.35873e+16 to \
  4.53915e+15, 2.26656e+16 to \
  4.53915e+15, 2.26656e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35873e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 300 polygon from \
  -4.53914e+15, 1.36327e+16 to \
  4.53915e+15, 2.2711e+16 to \
  4.53915e+15, 2.2711e+16 to \
  4.53915e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.36327e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 301 polygon from \
  -4.53914e+15, 3.43088e+15 to \
  7.94351e+15, 3.43088e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.43088e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 302 polygon from \
  -4.53914e+15, 3.35144e+15 to \
  -4.38027e+15, 3.51031e+15 to \
  7.94351e+15, 3.51031e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.35144e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 303 polygon from \
  -4.53914e+15, 3.30605e+15 to \
  -4.25544e+15, 3.58975e+15 to \
  7.94351e+15, 3.58975e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.30605e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 304 polygon from \
  -4.53914e+15, 3.26066e+15 to \
  -4.13062e+15, 3.66918e+15 to \
  7.94351e+15, 3.66918e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.26066e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 305 polygon from \
  -4.53914e+15, 3.21527e+15 to \
  -4.00579e+15, 3.74862e+15 to \
  7.94351e+15, 3.74862e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.21527e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 306 polygon from \
  -4.53914e+15, 3.16988e+15 to \
  -3.88096e+15, 3.82805e+15 to \
  7.94351e+15, 3.82805e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.16988e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 307 polygon from \
  -4.53914e+15, 3.12448e+15 to \
  -3.75614e+15, 3.90749e+15 to \
  7.94351e+15, 3.90749e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.12448e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 308 polygon from \
  -4.53914e+15, 3.07909e+15 to \
  -3.63131e+15, 3.98692e+15 to \
  7.94351e+15, 3.98692e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.07909e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 309 polygon from \
  -4.53914e+15, 3.0337e+15 to \
  -3.50648e+15, 4.06636e+15 to \
  7.94351e+15, 4.06636e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.0337e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 310 polygon from \
  -4.53914e+15, 2.98831e+15 to \
  -3.38166e+15, 4.14579e+15 to \
  7.94351e+15, 4.14579e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.98831e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 311 polygon from \
  -4.53914e+15, 2.94292e+15 to \
  -3.25683e+15, 4.22523e+15 to \
  7.94351e+15, 4.22523e+15 to \
  7.94351e+15, 4.22523e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.94292e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 312 polygon from \
  -4.53914e+15, 2.89753e+15 to \
  -3.132e+15, 4.30466e+15 to \
  7.94351e+15, 4.30466e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.89753e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 313 polygon from \
  -4.53914e+15, 2.85214e+15 to \
  -3.00718e+15, 4.3841e+15 to \
  7.94351e+15, 4.3841e+15 to \
  7.94351e+15, 4.3841e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.85214e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 314 polygon from \
  -4.53914e+15, 2.80674e+15 to \
  -2.88235e+15, 4.46353e+15 to \
  7.94351e+15, 4.46353e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.80674e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 315 polygon from \
  -4.53914e+15, 2.76135e+15 to \
  -2.75753e+15, 4.54297e+15 to \
  7.94351e+15, 4.54297e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.76135e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 316 polygon from \
  -4.53914e+15, 2.71596e+15 to \
  -2.6327e+15, 4.6224e+15 to \
  7.94351e+15, 4.6224e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.71596e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 317 polygon from \
  -4.53914e+15, 2.67057e+15 to \
  -2.50787e+15, 4.70184e+15 to \
  7.94351e+15, 4.70184e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.67057e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 318 polygon from \
  -4.53914e+15, 2.62518e+15 to \
  -2.38305e+15, 4.78127e+15 to \
  7.94351e+15, 4.78127e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.62518e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 319 polygon from \
  -4.53914e+15, 2.57979e+15 to \
  -2.25822e+15, 4.86071e+15 to \
  7.94351e+15, 4.86071e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.57979e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 320 polygon from \
  -4.53914e+15, 2.5344e+15 to \
  -2.13339e+15, 4.94014e+15 to \
  7.94351e+15, 4.94014e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.5344e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 321 polygon from \
  -4.53914e+15, 2.489e+15 to \
  -2.00857e+15, 5.01958e+15 to \
  7.94351e+15, 5.01958e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.489e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 322 polygon from \
  -4.53914e+15, 2.44361e+15 to \
  -1.88374e+15, 5.09901e+15 to \
  7.94351e+15, 5.09901e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.44361e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 323 polygon from \
  -4.53914e+15, 2.39822e+15 to \
  -1.75891e+15, 5.17845e+15 to \
  7.94351e+15, 5.17845e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.39822e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 324 polygon from \
  -4.53914e+15, 2.35283e+15 to \
  -1.63409e+15, 5.25788e+15 to \
  7.94351e+15, 5.25788e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.35283e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 325 polygon from \
  -4.53914e+15, 2.30744e+15 to \
  -1.50926e+15, 5.33732e+15 to \
  7.94351e+15, 5.33732e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.30744e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 326 polygon from \
  -4.53914e+15, 2.26205e+15 to \
  -1.38443e+15, 5.41675e+15 to \
  7.94351e+15, 5.41675e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.26205e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 327 polygon from \
  -4.53914e+15, 2.21665e+15 to \
  -1.25961e+15, 5.49619e+15 to \
  7.94351e+15, 5.49619e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.21665e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 328 polygon from \
  -4.53914e+15, 2.17126e+15 to \
  -1.13478e+15, 5.57562e+15 to \
  7.94351e+15, 5.57562e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.17126e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 329 polygon from \
  -4.53914e+15, 2.12587e+15 to \
  -1.00995e+15, 5.65506e+15 to \
  7.94351e+15, 5.65506e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.12587e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 330 polygon from \
  -4.53914e+15, 2.08048e+15 to \
  -8.85133e+14, 5.73449e+15 to \
  7.94351e+15, 5.73449e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.08048e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 331 polygon from \
  -4.53914e+15, 2.03509e+15 to \
  -7.60306e+14, 5.81393e+15 to \
  7.94351e+15, 5.81393e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.03509e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 332 polygon from \
  -4.53914e+15, 1.9897e+15 to \
  -6.3548e+14, 5.89336e+15 to \
  7.94351e+15, 5.89336e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.9897e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 333 polygon from \
  -4.53914e+15, 1.94431e+15 to \
  -5.10653e+14, 5.9728e+15 to \
  7.94351e+15, 5.9728e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.94431e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 334 polygon from \
  -4.53914e+15, 1.89891e+15 to \
  -3.85827e+14, 6.05223e+15 to \
  7.94351e+15, 6.05223e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.89891e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 335 polygon from \
  -4.53914e+15, 1.85352e+15 to \
  -2.61e+14, 6.13167e+15 to \
  7.94351e+15, 6.13167e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.85352e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 336 polygon from \
  -4.53914e+15, 1.80813e+15 to \
  -1.36174e+14, 6.2111e+15 to \
  7.94351e+15, 6.2111e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.80813e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 337 polygon from \
  -4.53914e+15, 1.76274e+15 to \
  -1.13478e+13, 6.29054e+15 to \
  7.94351e+15, 6.29054e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.76274e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 338 polygon from \
  -4.53914e+15, 1.71735e+15 to \
  1.13479e+14, 6.36997e+15 to \
  7.94351e+15, 6.36997e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.71735e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 339 polygon from \
  -4.53914e+15, 1.67196e+15 to \
  2.38306e+14, 6.44941e+15 to \
  7.94351e+15, 6.44941e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.67196e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 340 polygon from \
  -4.53914e+15, 1.62657e+15 to \
  3.63132e+14, 6.52884e+15 to \
  7.94351e+15, 6.52884e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.62657e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 341 polygon from \
  -4.53914e+15, 1.58117e+15 to \
  4.87959e+14, 6.60828e+15 to \
  7.94351e+15, 6.60828e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.58117e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 342 polygon from \
  -4.53914e+15, 1.53578e+15 to \
  6.12785e+14, 6.68771e+15 to \
  7.94351e+15, 6.68771e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.53578e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 343 polygon from \
  -4.53914e+15, 1.49039e+15 to \
  7.37611e+14, 6.76715e+15 to \
  7.94351e+15, 6.76715e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.49039e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 344 polygon from \
  -4.53914e+15, 1.445e+15 to \
  8.62438e+14, 6.84658e+15 to \
  7.94351e+15, 6.84658e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.445e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 345 polygon from \
  -4.53914e+15, 1.39961e+15 to \
  9.87264e+14, 6.92602e+15 to \
  7.94351e+15, 6.92602e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.39961e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 346 polygon from \
  -4.53914e+15, 1.35422e+15 to \
  1.1121e+15, 7.00545e+15 to \
  7.94351e+15, 7.00545e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35422e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 347 polygon from \
  -4.53914e+15, 1.30883e+15 to \
  1.23692e+15, 7.08489e+15 to \
  7.94351e+15, 7.08489e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.30883e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 348 polygon from \
  -4.53914e+15, 1.26343e+15 to \
  1.36175e+15, 7.16432e+15 to \
  7.94351e+15, 7.16432e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.26343e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 349 polygon from \
  -4.53914e+15, 1.21804e+15 to \
  1.48657e+15, 7.24376e+15 to \
  7.94351e+15, 7.24376e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.21804e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 350 polygon from \
  -4.53914e+15, 1.17265e+15 to \
  1.6114e+15, 7.32319e+15 to \
  7.94351e+15, 7.32319e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.17265e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 351 polygon from \
  -4.53914e+15, 1.12726e+15 to \
  1.73623e+15, 7.40263e+15 to \
  7.94351e+15, 7.40263e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.12726e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 352 polygon from \
  -4.53914e+15, 1.08187e+15 to \
  1.86105e+15, 7.48206e+15 to \
  7.94351e+15, 7.48206e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.08187e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 353 polygon from \
  -4.53914e+15, 1.03648e+15 to \
  1.98588e+15, 7.5615e+15 to \
  7.94351e+15, 7.5615e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03648e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 354 polygon from \
  -4.53914e+15, 9.91082e+14 to \
  2.11071e+15, 7.64093e+15 to \
  7.94351e+15, 7.64093e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.91082e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 355 polygon from \
  -4.53914e+15, 9.4569e+14 to \
  2.23553e+15, 7.72037e+15 to \
  7.94351e+15, 7.72037e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.4569e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 356 polygon from \
  -4.53914e+15, 9.00299e+14 to \
  2.36036e+15, 7.7998e+15 to \
  7.94351e+15, 7.7998e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.00299e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 357 polygon from \
  -4.53914e+15, 8.54907e+14 to \
  2.48519e+15, 7.87924e+15 to \
  7.94351e+15, 7.87924e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.54907e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 358 polygon from \
  -4.53914e+15, 8.09516e+14 to \
  2.61001e+15, 7.95867e+15 to \
  7.94351e+15, 7.95867e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.09516e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 359 polygon from \
  -4.53914e+15, 7.64124e+14 to \
  2.73484e+15, 8.03811e+15 to \
  7.94351e+15, 8.03811e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.64124e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 360 polygon from \
  -4.53914e+15, 7.18733e+14 to \
  2.85967e+15, 8.11754e+15 to \
  7.94351e+15, 8.11754e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.18733e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 361 polygon from \
  -4.53914e+15, 6.73341e+14 to \
  2.98449e+15, 8.19698e+15 to \
  7.94351e+15, 8.19698e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.73341e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 362 polygon from \
  -4.53914e+15, 6.2795e+14 to \
  3.10932e+15, 8.27641e+15 to \
  7.94351e+15, 8.27641e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.2795e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 363 polygon from \
  -4.53914e+15, 5.82559e+14 to \
  3.23415e+15, 8.35585e+15 to \
  7.94351e+15, 8.35585e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.82559e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 364 polygon from \
  -4.53914e+15, 5.37167e+14 to \
  3.35897e+15, 8.43528e+15 to \
  7.94351e+15, 8.43528e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.37167e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 365 polygon from \
  -4.53914e+15, 4.91776e+14 to \
  3.4838e+15, 8.51472e+15 to \
  7.94351e+15, 8.51472e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.91776e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 366 polygon from \
  -4.53914e+15, 4.46384e+14 to \
  3.60862e+15, 8.59415e+15 to \
  7.94351e+15, 8.59415e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.46384e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 367 polygon from \
  -4.53914e+15, 4.00993e+14 to \
  3.73345e+15, 8.67359e+15 to \
  7.94351e+15, 8.67359e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.00993e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 368 polygon from \
  -4.53914e+15, 3.55601e+14 to \
  3.85828e+15, 8.75302e+15 to \
  7.94351e+15, 8.75302e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.55601e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 369 polygon from \
  -4.53914e+15, 3.1021e+14 to \
  3.9831e+15, 8.83246e+15 to \
  7.94351e+15, 8.83246e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.1021e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 370 polygon from \
  -4.53914e+15, 2.64818e+14 to \
  4.10793e+15, 8.91189e+15 to \
  7.94351e+15, 8.91189e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.64818e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 371 polygon from \
  -4.53914e+15, 2.19427e+14 to \
  4.23276e+15, 8.99133e+15 to \
  7.94351e+15, 8.99133e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.19427e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 372 polygon from \
  -4.53914e+15, 1.74036e+14 to \
  4.35758e+15, 9.07076e+15 to \
  7.94351e+15, 9.07076e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.74036e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 373 polygon from \
  -4.53914e+15, 1.28644e+14 to \
  4.48241e+15, 9.1502e+15 to \
  7.94351e+15, 9.1502e+15 to \
  7.94351e+15, 9.1502e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.28644e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 374 polygon from \
  -4.53914e+15, 8.32523e+13 to \
  4.60724e+15, 9.22963e+15 to \
  7.94351e+15, 9.22963e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.32523e+13 front fs empty border lc rgb '#6165' lw 0.200001
set object 375 polygon from \
  -4.53914e+15, 3.78608e+13 to \
  4.73206e+15, 9.30907e+15 to \
  7.94351e+15, 9.30907e+15 to \
  7.94351e+15, 9.30907e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.78608e+13 front fs empty border lc rgb '#6165' lw 0.200001
set object 376 polygon from \
  4.85689e+15, 9.3885e+15 to \
  7.94351e+15, 9.3885e+15 to \
  7.94351e+15, 0 to \
  -4.53161e+15, -0 to \
  4.85689e+15, 9.3885e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 377 polygon from \
  4.98172e+15, 9.46794e+15 to \
  7.94351e+15, 9.46794e+15 to \
  7.94351e+15, 9.46794e+15 to \
  7.94351e+15, 0 to \
  -4.48622e+15, -0 to \
  4.98172e+15, 9.46794e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 378 polygon from \
  5.10654e+15, 9.54737e+15 to \
  7.94351e+15, 9.54737e+15 to \
  7.94351e+15, 0 to \
  -4.44083e+15, -0 to \
  5.10654e+15, 9.54737e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 379 polygon from \
  5.23137e+15, 9.62681e+15 to \
  7.94351e+15, 9.62681e+15 to \
  7.94351e+15, 0 to \
  -4.39543e+15, -0 to \
  5.23137e+15, 9.62681e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 380 polygon from \
  5.3562e+15, 9.70624e+15 to \
  7.94351e+15, 9.70624e+15 to \
  7.94351e+15, 0 to \
  -4.35004e+15, -0 to \
  5.3562e+15, 9.70624e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 381 polygon from \
  5.48102e+15, 9.78568e+15 to \
  7.94351e+15, 9.78568e+15 to \
  7.94351e+15, 0 to \
  -4.30465e+15, -0 to \
  5.48102e+15, 9.78568e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 382 polygon from \
  5.60585e+15, 9.86511e+15 to \
  7.94351e+15, 9.86511e+15 to \
  7.94351e+15, 9.86511e+15 to \
  7.94351e+15, 0 to \
  -4.25926e+15, -0 to \
  5.60585e+15, 9.86511e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 383 polygon from \
  5.73067e+15, 9.94455e+15 to \
  7.94351e+15, 9.94455e+15 to \
  7.94351e+15, 0 to \
  -4.21387e+15, -0 to \
  5.73067e+15, 9.94455e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 384 polygon from \
  5.8555e+15, 1.0024e+16 to \
  7.94351e+15, 1.0024e+16 to \
  7.94351e+15, 1.0024e+16 to \
  7.94351e+15, 0 to \
  -4.16848e+15, -0 to \
  5.8555e+15, 1.0024e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 385 polygon from \
  5.98033e+15, 1.01035e+16 to \
  7.94351e+15, 1.01035e+16 to \
  7.94351e+15, 1.01035e+16 to \
  7.94351e+15, 0 to \
  -4.12309e+15, -0 to \
  5.98033e+15, 1.01035e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 386 polygon from \
  6.10515e+15, 1.01829e+16 to \
  7.94351e+15, 1.01829e+16 to \
  7.94351e+15, 1.01829e+16 to \
  7.94351e+15, 0 to \
  -4.07769e+15, -0 to \
  6.10515e+15, 1.01829e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 387 polygon from \
  6.22998e+15, 1.02623e+16 to \
  7.94351e+15, 1.02623e+16 to \
  7.94351e+15, 1.02623e+16 to \
  7.94351e+15, 3.77571e+13 to \
  7.90575e+15, -0 to \
  -4.0323e+15, -0 to \
  6.22998e+15, 1.02623e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 388 polygon from \
  6.35481e+15, 1.03418e+16 to \
  7.94351e+15, 1.03418e+16 to \
  7.94351e+15, 1.03418e+16 to \
  7.94351e+15, 1.17193e+14 to \
  7.82632e+15, -0 to \
  -3.98691e+15, -0 to \
  6.35481e+15, 1.03418e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 389 polygon from \
  6.47963e+15, 1.04212e+16 to \
  7.94351e+15, 1.04212e+16 to \
  7.94351e+15, 1.04212e+16 to \
  7.94351e+15, 1.96628e+14 to \
  7.74688e+15, -0 to \
  -3.94152e+15, -0 to \
  6.47963e+15, 1.04212e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 390 polygon from \
  6.60446e+15, 1.05006e+16 to \
  7.94351e+15, 1.05006e+16 to \
  7.94351e+15, 1.05006e+16 to \
  7.94351e+15, 2.76063e+14 to \
  7.66745e+15, -0 to \
  -3.89613e+15, -0 to \
  6.60446e+15, 1.05006e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 391 polygon from \
  6.72929e+15, 1.05801e+16 to \
  7.94351e+15, 1.05801e+16 to \
  7.94351e+15, 1.05801e+16 to \
  7.94351e+15, 3.55498e+14 to \
  7.58801e+15, -0 to \
  -3.85074e+15, -0 to \
  6.72929e+15, 1.05801e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 392 polygon from \
  6.85411e+15, 1.06595e+16 to \
  7.94351e+15, 1.06595e+16 to \
  7.94351e+15, 1.06595e+16 to \
  7.94351e+15, 4.34933e+14 to \
  7.50858e+15, -0 to \
  -3.80535e+15, -0 to \
  6.85411e+15, 1.06595e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 393 polygon from \
  6.97894e+15, 1.07389e+16 to \
  7.94351e+15, 1.07389e+16 to \
  7.94351e+15, 1.07389e+16 to \
  7.94351e+15, 5.14368e+14 to \
  7.42914e+15, -0 to \
  -3.75995e+15, -0 to \
  6.97894e+15, 1.07389e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 394 polygon from \
  7.10377e+15, 1.08184e+16 to \
  7.94351e+15, 1.08184e+16 to \
  7.94351e+15, 1.08184e+16 to \
  7.94351e+15, 5.93803e+14 to \
  7.34971e+15, -0 to \
  -3.71456e+15, -0 to \
  7.10377e+15, 1.08184e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 395 polygon from \
  7.22859e+15, 1.08978e+16 to \
  7.94351e+15, 1.08978e+16 to \
  7.94351e+15, 1.08978e+16 to \
  7.94351e+15, 6.73238e+14 to \
  7.27027e+15, -0 to \
  -3.66917e+15, -0 to \
  7.22859e+15, 1.08978e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 396 polygon from \
  7.35342e+15, 1.09772e+16 to \
  7.94351e+15, 1.09772e+16 to \
  7.94351e+15, 1.09772e+16 to \
  7.94351e+15, 7.52673e+14 to \
  7.19084e+15, -0 to \
  -3.62378e+15, -0 to \
  7.35342e+15, 1.09772e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 397 polygon from \
  7.47825e+15, 1.10567e+16 to \
  7.94351e+15, 1.10567e+16 to \
  7.94351e+15, 1.10567e+16 to \
  7.94351e+15, 8.32108e+14 to \
  7.1114e+15, -0 to \
  -3.57839e+15, -0 to \
  7.47825e+15, 1.10567e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 398 polygon from \
  7.60307e+15, 1.11361e+16 to \
  7.94351e+15, 1.11361e+16 to \
  7.94351e+15, 1.11361e+16 to \
  7.94351e+15, 9.11543e+14 to \
  7.03197e+15, -0 to \
  -3.533e+15, -0 to \
  7.60307e+15, 1.11361e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 399 polygon from \
  7.7279e+15, 1.12156e+16 to \
  7.94351e+15, 1.12156e+16 to \
  7.94351e+15, 1.12156e+16 to \
  7.94351e+15, 9.90978e+14 to \
  6.95253e+15, -0 to \
  -3.48761e+15, -0 to \
  7.7279e+15, 1.12156e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 400 polygon from \
  7.85272e+15, 1.1295e+16 to \
  7.94351e+15, 1.1295e+16 to \
  7.94351e+15, 1.1295e+16 to \
  7.94351e+15, 1.07042e+15 to \
  6.87309e+15, -0 to \
  -3.44221e+15, -0 to \
  7.85272e+15, 1.1295e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 401 polygon from \
  7.94351e+15, 1.13744e+16 to \
  7.94351e+15, 1.13744e+16 to \
  7.94351e+15, 1.13744e+16 to \
  7.94351e+15, 1.14985e+15 to \
  6.79366e+15, -0 to \
  -3.43087e+15, -0 to \
  7.94351e+15, 1.13744e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 402 polygon from \
  7.94351e+15, 1.14539e+16 to \
  7.94351e+15, 1.14539e+16 to \
  7.94351e+15, 1.14539e+16 to \
  7.94351e+15, 1.10446e+15 to \
  6.83905e+15, -0 to \
  -3.5103e+15, -0 to \
  7.94351e+15, 1.14539e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 403 polygon from \
  7.94351e+15, 1.15333e+16 to \
  7.94351e+15, 1.15333e+16 to \
  7.94351e+15, 1.15333e+16 to \
  7.94351e+15, 1.05907e+15 to \
  6.88444e+15, -0 to \
  -3.58974e+15, -0 to \
  7.94351e+15, 1.15333e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 404 polygon from \
  7.94351e+15, 1.16127e+16 to \
  7.94351e+15, 1.16127e+16 to \
  7.94351e+15, 1.01368e+15 to \
  6.92983e+15, -0 to \
  -3.66917e+15, -0 to \
  7.94351e+15, 1.16127e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 405 polygon from \
  7.94351e+15, 1.16922e+16 to \
  7.94351e+15, 1.16922e+16 to \
  7.94351e+15, 1.16922e+16 to \
  7.94351e+15, 9.68282e+14 to \
  6.97523e+15, -0 to \
  -3.74861e+15, -0 to \
  7.94351e+15, 1.16922e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 406 polygon from \
  7.94351e+15, 1.17716e+16 to \
  7.94351e+15, 1.17716e+16 to \
  7.94351e+15, 1.17716e+16 to \
  7.94351e+15, 9.22891e+14 to \
  7.02062e+15, -0 to \
  -3.82804e+15, -0 to \
  7.94351e+15, 1.17716e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 407 polygon from \
  7.94351e+15, 1.1851e+16 to \
  7.94351e+15, 1.1851e+16 to \
  7.94351e+15, 1.1851e+16 to \
  7.94351e+15, 8.77499e+14 to \
  7.06601e+15, -0 to \
  -3.90748e+15, -0 to \
  7.94351e+15, 1.1851e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 408 polygon from \
  7.94351e+15, 1.19305e+16 to \
  7.94351e+15, 1.19305e+16 to \
  7.94351e+15, 8.32108e+14 to \
  7.1114e+15, -0 to \
  -3.98691e+15, -0 to \
  7.94351e+15, 1.19305e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 409 polygon from \
  7.94351e+15, 1.20099e+16 to \
  7.94351e+15, 1.20099e+16 to \
  7.94351e+15, 7.86716e+14 to \
  7.15679e+15, -0 to \
  -4.06635e+15, -0 to \
  7.94351e+15, 1.20099e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 410 polygon from \
  7.94351e+15, 1.20893e+16 to \
  7.94351e+15, 1.20893e+16 to \
  7.94351e+15, 7.41325e+14 to \
  7.20218e+15, -0 to \
  -4.14578e+15, -0 to \
  7.94351e+15, 1.20893e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 411 polygon from \
  7.94351e+15, 1.21688e+16 to \
  7.94351e+15, 1.21688e+16 to \
  7.94351e+15, 1.21688e+16 to \
  7.94351e+15, 6.95933e+14 to \
  7.24757e+15, -0 to \
  -4.22522e+15, -0 to \
  7.94351e+15, 1.21688e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 412 polygon from \
  7.94351e+15, 1.22482e+16 to \
  7.94351e+15, 1.22482e+16 to \
  7.94351e+15, 1.22482e+16 to \
  7.94351e+15, 6.50542e+14 to \
  7.29297e+15, -0 to \
  -4.30465e+15, -0 to \
  7.94351e+15, 1.22482e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 413 polygon from \
  7.94351e+15, 1.23276e+16 to \
  7.94351e+15, 1.23276e+16 to \
  7.94351e+15, 6.05151e+14 to \
  7.33836e+15, -0 to \
  -4.38409e+15, -0 to \
  7.94351e+15, 1.23276e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 414 polygon from \
  7.94351e+15, 1.24071e+16 to \
  7.94351e+15, 1.24071e+16 to \
  7.94351e+15, 1.24071e+16 to \
  7.94351e+15, 5.59759e+14 to \
  7.38375e+15, -0 to \
  -4.46352e+15, -0 to \
  7.94351e+15, 1.24071e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 415 polygon from \
  -4.53914e+15, 3.81718e+12 to \
  7.94351e+15, 1.24865e+16 to \
  7.94351e+15, 1.24865e+16 to \
  7.94351e+15, 1.24865e+16 to \
  7.94351e+15, 5.14368e+14 to \
  7.42914e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.81718e+12 front fs empty border lc rgb '#6165' lw 0.200001
set object 416 polygon from \
  -4.53914e+15, 8.32523e+13 to \
  7.94351e+15, 1.25659e+16 to \
  7.94351e+15, 1.25659e+16 to \
  7.94351e+15, 1.25659e+16 to \
  7.94351e+15, 4.68976e+14 to \
  7.47453e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.32523e+13 front fs empty border lc rgb '#6165' lw 0.200001
set object 417 polygon from \
  -4.53914e+15, 1.62688e+14 to \
  7.94351e+15, 1.26454e+16 to \
  7.94351e+15, 1.26454e+16 to \
  7.94351e+15, 1.26454e+16 to \
  7.94351e+15, 4.23585e+14 to \
  7.51992e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.62688e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 418 polygon from \
  -4.53914e+15, 2.42123e+14 to \
  7.94351e+15, 1.27248e+16 to \
  7.94351e+15, 1.27248e+16 to \
  7.94351e+15, 3.78193e+14 to \
  7.56531e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.42123e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 419 polygon from \
  -4.53914e+15, 3.21558e+14 to \
  7.94351e+15, 1.28043e+16 to \
  7.94351e+15, 1.28043e+16 to \
  7.94351e+15, 3.32802e+14 to \
  7.61071e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.21558e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 420 polygon from \
  -4.53914e+15, 4.00993e+14 to \
  7.94351e+15, 1.28837e+16 to \
  7.94351e+15, 1.28837e+16 to \
  7.94351e+15, 1.28837e+16 to \
  7.94351e+15, 2.87411e+14 to \
  7.6561e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.00993e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 421 polygon from \
  -4.53914e+15, 4.80428e+14 to \
  7.94351e+15, 1.29631e+16 to \
  7.94351e+15, 1.29631e+16 to \
  7.94351e+15, 1.29631e+16 to \
  7.94351e+15, 2.42019e+14 to \
  7.70149e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.80428e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 422 polygon from \
  -4.53914e+15, 5.59863e+14 to \
  7.94351e+15, 1.30426e+16 to \
  7.94351e+15, 1.30426e+16 to \
  7.94351e+15, 1.30426e+16 to \
  7.94351e+15, 1.96628e+14 to \
  7.74688e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.59863e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 423 polygon from \
  -4.53914e+15, 6.39298e+14 to \
  7.94351e+15, 1.3122e+16 to \
  7.94351e+15, 1.3122e+16 to \
  7.94351e+15, 1.3122e+16 to \
  7.94351e+15, 1.51236e+14 to \
  7.79227e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.39298e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 424 polygon from \
  -4.53914e+15, 7.18733e+14 to \
  7.94351e+15, 1.32014e+16 to \
  7.94351e+15, 1.32014e+16 to \
  7.94351e+15, 1.05845e+14 to \
  7.83766e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.18733e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 425 polygon from \
  -4.53914e+15, 7.98168e+14 to \
  7.94351e+15, 1.32809e+16 to \
  7.94351e+15, 1.32809e+16 to \
  7.94351e+15, 1.32809e+16 to \
  7.94351e+15, 6.04529e+13 to \
  7.88305e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.98168e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 426 polygon from \
  -4.53914e+15, 8.77603e+14 to \
  7.94351e+15, 1.33603e+16 to \
  7.94351e+15, 1.33603e+16 to \
  7.94351e+15, 1.33603e+16 to \
  7.94351e+15, 1.50614e+13 to \
  7.92845e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.77603e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 427 polygon from \
  -4.53914e+15, 9.57038e+14 to \
  7.94351e+15, 1.34397e+16 to \
  7.94351e+15, 1.34397e+16 to \
  7.94351e+15, 1.34397e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.57038e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 428 polygon from \
  -4.53914e+15, 1.03648e+15 to \
  7.94351e+15, 1.35192e+16 to \
  7.94351e+15, 1.35192e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03648e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 429 polygon from \
  -4.53914e+15, 1.11591e+15 to \
  7.94351e+15, 1.35986e+16 to \
  7.94351e+15, 1.35986e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.11591e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 430 polygon from \
  -4.53914e+15, 1.19535e+15 to \
  7.94351e+15, 1.3678e+16 to \
  7.94351e+15, 1.3678e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19535e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 431 polygon from \
  -4.53914e+15, 1.27478e+15 to \
  7.94351e+15, 1.37575e+16 to \
  7.94351e+15, 1.37575e+16 to \
  7.94351e+15, 1.37575e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27478e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 432 polygon from \
  -4.53914e+15, 1.35422e+15 to \
  7.94351e+15, 1.38369e+16 to \
  7.94351e+15, 1.38369e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35422e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 433 polygon from \
  -4.53914e+15, 1.43365e+15 to \
  7.94351e+15, 1.39163e+16 to \
  7.94351e+15, 1.39163e+16 to \
  7.94351e+15, 1.39163e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.43365e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 434 polygon from \
  -4.53914e+15, 1.51309e+15 to \
  7.94351e+15, 1.39958e+16 to \
  7.94351e+15, 1.39958e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.51309e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 435 polygon from \
  -4.53914e+15, 1.59252e+15 to \
  7.94351e+15, 1.40752e+16 to \
  7.94351e+15, 1.40752e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.59252e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 436 polygon from \
  -4.53914e+15, 1.67196e+15 to \
  7.94351e+15, 1.41546e+16 to \
  7.94351e+15, 1.41546e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.67196e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 437 polygon from \
  -4.53914e+15, 1.75139e+15 to \
  7.94351e+15, 1.42341e+16 to \
  7.94351e+15, 1.42341e+16 to \
  7.94351e+15, 1.42341e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.75139e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 438 polygon from \
  -4.53914e+15, 1.83083e+15 to \
  7.94351e+15, 1.43135e+16 to \
  7.94351e+15, 1.43135e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.83083e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 439 polygon from \
  -4.53914e+15, 1.91026e+15 to \
  7.94351e+15, 1.4393e+16 to \
  7.94351e+15, 1.4393e+16 to \
  7.94351e+15, 1.4393e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.91026e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 440 polygon from \
  -4.53914e+15, 1.9897e+15 to \
  7.94351e+15, 1.44724e+16 to \
  7.94351e+15, 1.44724e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.9897e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 441 polygon from \
  -4.53914e+15, 2.06913e+15 to \
  7.94351e+15, 1.45518e+16 to \
  7.94351e+15, 1.45518e+16 to \
  7.94351e+15, 1.45518e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.06913e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 442 polygon from \
  -4.53914e+15, 2.14857e+15 to \
  7.94351e+15, 1.46313e+16 to \
  7.94351e+15, 1.46313e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.14857e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 443 polygon from \
  -4.53914e+15, 2.228e+15 to \
  7.94351e+15, 1.47107e+16 to \
  7.94351e+15, 1.47107e+16 to \
  7.94351e+15, 1.47107e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.228e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 444 polygon from \
  -4.53914e+15, 2.30744e+15 to \
  7.94351e+15, 1.47901e+16 to \
  7.94351e+15, 1.47901e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.30744e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 445 polygon from \
  -4.53914e+15, 2.38687e+15 to \
  7.94351e+15, 1.48696e+16 to \
  7.94351e+15, 1.48696e+16 to \
  7.94351e+15, 1.48696e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.38687e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 446 polygon from \
  -4.53914e+15, 2.46631e+15 to \
  7.94351e+15, 1.4949e+16 to \
  7.94351e+15, 1.4949e+16 to \
  7.94351e+15, 1.4949e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.46631e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 447 polygon from \
  -4.53914e+15, 2.54574e+15 to \
  7.94351e+15, 1.50284e+16 to \
  7.94351e+15, 1.50284e+16 to \
  7.94351e+15, 1.50284e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.54574e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 448 polygon from \
  -4.53914e+15, 2.62518e+15 to \
  7.94351e+15, 1.51079e+16 to \
  7.94351e+15, 1.51079e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.62518e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 449 polygon from \
  -4.53914e+15, 2.70461e+15 to \
  7.94351e+15, 1.51873e+16 to \
  7.94351e+15, 1.51873e+16 to \
  7.94351e+15, 1.51873e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.70461e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 450 polygon from \
  -4.53914e+15, 2.78405e+15 to \
  7.94351e+15, 1.52667e+16 to \
  7.94351e+15, 1.52667e+16 to \
  7.94351e+15, 1.52667e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.78405e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 451 polygon from \
  -4.53914e+15, 2.86348e+15 to \
  7.94351e+15, 1.53462e+16 to \
  7.94351e+15, 1.53462e+16 to \
  7.94351e+15, 1.53462e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.86348e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 452 polygon from \
  -4.53914e+15, 2.94292e+15 to \
  7.94351e+15, 1.54256e+16 to \
  7.94351e+15, 1.54256e+16 to \
  7.94351e+15, 1.54256e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.94292e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 453 polygon from \
  -4.53914e+15, 3.02235e+15 to \
  7.94351e+15, 1.5505e+16 to \
  7.94351e+15, 1.5505e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.02235e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 454 polygon from \
  -4.53914e+15, 3.10179e+15 to \
  7.94351e+15, 1.55845e+16 to \
  7.94351e+15, 1.55845e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.10179e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 455 polygon from \
  -4.53914e+15, 3.18122e+15 to \
  7.94351e+15, 1.56639e+16 to \
  7.94351e+15, 1.56639e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.18122e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 456 polygon from \
  -4.53914e+15, 3.26066e+15 to \
  7.94351e+15, 1.57433e+16 to \
  7.94351e+15, 1.57433e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.26066e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 457 polygon from \
  -4.53914e+15, 3.34009e+15 to \
  7.94351e+15, 1.58228e+16 to \
  7.94351e+15, 1.58228e+16 to \
  7.94351e+15, 1.58228e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.34009e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 458 polygon from \
  -4.53914e+15, 3.41953e+15 to \
  7.94351e+15, 1.59022e+16 to \
  7.94351e+15, 1.59022e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.41953e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 459 polygon from \
  -4.53914e+15, 3.49896e+15 to \
  7.94351e+15, 1.59817e+16 to \
  7.94351e+15, 1.59817e+16 to \
  7.94351e+15, 1.59817e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.49896e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 460 polygon from \
  -4.53914e+15, 3.5784e+15 to \
  7.94351e+15, 1.60611e+16 to \
  7.94351e+15, 1.60611e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.5784e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 461 polygon from \
  -4.53914e+15, 3.65783e+15 to \
  7.94351e+15, 1.61405e+16 to \
  7.94351e+15, 1.61405e+16 to \
  7.94351e+15, 1.61405e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.65783e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 462 polygon from \
  -4.53914e+15, 3.73727e+15 to \
  7.94351e+15, 1.622e+16 to \
  7.94351e+15, 1.622e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.73727e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 463 polygon from \
  -4.53914e+15, 3.8167e+15 to \
  7.94351e+15, 1.62994e+16 to \
  7.94351e+15, 1.62994e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.8167e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 464 polygon from \
  -4.53914e+15, 3.89614e+15 to \
  7.94351e+15, 1.63788e+16 to \
  7.94351e+15, 1.63788e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.89614e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 465 polygon from \
  -4.53914e+15, 3.97557e+15 to \
  7.94351e+15, 1.64583e+16 to \
  7.94351e+15, 1.64583e+16 to \
  7.94351e+15, 1.64583e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.97557e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 466 polygon from \
  -4.53914e+15, 4.05501e+15 to \
  7.94351e+15, 1.65377e+16 to \
  7.94351e+15, 1.65377e+16 to \
  7.94351e+15, 1.65377e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.05501e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 467 polygon from \
  -4.53914e+15, 4.13444e+15 to \
  7.94351e+15, 1.66171e+16 to \
  7.94351e+15, 1.66171e+16 to \
  7.94351e+15, 1.66171e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.13444e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 468 polygon from \
  -4.53914e+15, 4.21388e+15 to \
  7.94351e+15, 1.66966e+16 to \
  7.94351e+15, 1.66966e+16 to \
  7.94351e+15, 1.66966e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.21388e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 469 polygon from \
  -4.53914e+15, 4.29331e+15 to \
  7.94351e+15, 1.6776e+16 to \
  7.94351e+15, 1.6776e+16 to \
  7.94351e+15, 1.6776e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.29331e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 470 polygon from \
  -4.53914e+15, 4.37275e+15 to \
  7.94351e+15, 1.68554e+16 to \
  7.94351e+15, 1.68554e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.37275e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 471 polygon from \
  -4.53914e+15, 4.45218e+15 to \
  7.94351e+15, 1.69349e+16 to \
  7.94351e+15, 1.69349e+16 to \
  7.94351e+15, 1.69349e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.45218e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 472 polygon from \
  -4.53914e+15, 4.53162e+15 to \
  7.94351e+15, 1.70143e+16 to \
  7.94351e+15, 1.70143e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.53162e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 473 polygon from \
  -4.53914e+15, 4.61105e+15 to \
  7.94351e+15, 1.70937e+16 to \
  7.94351e+15, 1.70937e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.61105e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 474 polygon from \
  -4.53914e+15, 4.69049e+15 to \
  7.94351e+15, 1.71732e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.69049e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 475 polygon from \
  -4.53914e+15, 4.76992e+15 to \
  7.94351e+15, 1.72526e+16 to \
  7.94351e+15, 1.72526e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.76992e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 476 polygon from \
  -4.53914e+15, 4.84936e+15 to \
  7.94351e+15, 1.73321e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.84936e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 477 polygon from \
  -4.53914e+15, 4.92879e+15 to \
  7.94351e+15, 1.74115e+16 to \
  7.94351e+15, 1.74115e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.92879e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 478 polygon from \
  -4.53914e+15, 5.00823e+15 to \
  7.94351e+15, 1.74909e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.00823e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 479 polygon from \
  -4.53914e+15, 5.08766e+15 to \
  7.94351e+15, 1.75704e+16 to \
  7.94351e+15, 1.75704e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.08766e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 480 polygon from \
  -4.53914e+15, 5.1671e+15 to \
  7.94351e+15, 1.76498e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.1671e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 481 polygon from \
  -4.53914e+15, 5.24653e+15 to \
  7.94351e+15, 1.77292e+16 to \
  7.94351e+15, 1.77292e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.24653e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 482 polygon from \
  -4.53914e+15, 5.32597e+15 to \
  7.94351e+15, 1.78087e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.32597e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 483 polygon from \
  -4.53914e+15, 5.4054e+15 to \
  7.94351e+15, 1.78881e+16 to \
  7.94351e+15, 1.78881e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.4054e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 484 polygon from \
  -4.53914e+15, 5.48484e+15 to \
  7.94351e+15, 1.79675e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.48484e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 485 polygon from \
  -4.53914e+15, 5.56427e+15 to \
  7.94351e+15, 1.8047e+16 to \
  7.94351e+15, 1.8047e+16 to \
  7.94351e+15, 1.8047e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.56427e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 486 polygon from \
  -4.53914e+15, 5.64371e+15 to \
  7.94351e+15, 1.81264e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.64371e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 487 polygon from \
  -4.53914e+15, 5.72314e+15 to \
  7.94351e+15, 1.82058e+16 to \
  7.94351e+15, 1.82058e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.72314e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 488 polygon from \
  -4.53914e+15, 5.80258e+15 to \
  7.94351e+15, 1.82853e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.80258e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 489 polygon from \
  -4.53914e+15, 5.88201e+15 to \
  7.94351e+15, 1.83647e+16 to \
  7.94351e+15, 1.83647e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.88201e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 490 polygon from \
  -4.53914e+15, 5.96145e+15 to \
  7.94351e+15, 1.84441e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.96145e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 491 polygon from \
  -4.53914e+15, 6.04088e+15 to \
  7.94351e+15, 1.85236e+16 to \
  7.94351e+15, 1.85236e+16 to \
  7.94351e+15, 1.85236e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.04088e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 492 polygon from \
  -4.53914e+15, 6.12032e+15 to \
  7.94351e+15, 1.8603e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.12032e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 493 polygon from \
  -4.53914e+15, 6.19975e+15 to \
  7.94351e+15, 1.86824e+16 to \
  7.94351e+15, 1.86824e+16 to \
  7.94351e+15, 1.86824e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.19975e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 494 polygon from \
  -4.53914e+15, 6.27919e+15 to \
  7.94351e+15, 1.87619e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.27919e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 495 polygon from \
  -4.53914e+15, 6.35862e+15 to \
  7.94351e+15, 1.88413e+16 to \
  7.94351e+15, 1.88413e+16 to \
  7.94351e+15, 1.88413e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.35862e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 496 polygon from \
  -4.53914e+15, 6.43806e+15 to \
  7.94351e+15, 1.89208e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.43806e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 497 polygon from \
  -4.53914e+15, 6.51749e+15 to \
  7.94351e+15, 1.90002e+16 to \
  7.94351e+15, 1.90002e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.51749e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 498 polygon from \
  -4.53914e+15, 6.59693e+15 to \
  7.94351e+15, 1.90796e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.59693e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 499 polygon from \
  -4.53914e+15, 6.67636e+15 to \
  7.94351e+15, 1.91591e+16 to \
  7.94351e+15, 1.91591e+16 to \
  7.94351e+15, 1.91591e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.67636e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 500 polygon from \
  -4.53914e+15, 6.7558e+15 to \
  7.94351e+15, 1.92385e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.7558e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 501 polygon from \
  -4.53914e+15, 6.83523e+15 to \
  7.94351e+15, 1.93179e+16 to \
  7.94351e+15, 1.93179e+16 to \
  7.94351e+15, 1.93179e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.83523e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 502 polygon from \
  -4.53914e+15, 6.91467e+15 to \
  7.94351e+15, 1.93974e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.91467e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 503 polygon from \
  -4.53914e+15, 6.9941e+15 to \
  7.94351e+15, 1.94768e+16 to \
  7.94351e+15, 1.94768e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.9941e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 504 polygon from \
  -4.53914e+15, 7.07354e+15 to \
  7.94351e+15, 1.95562e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.07354e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 505 polygon from \
  -4.53914e+15, 7.15297e+15 to \
  7.94351e+15, 1.96357e+16 to \
  7.94351e+15, 1.96357e+16 to \
  7.94351e+15, 1.96357e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.15297e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 506 polygon from \
  -4.53914e+15, 7.23241e+15 to \
  7.94351e+15, 1.97151e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.23241e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 507 polygon from \
  -4.53914e+15, 7.31184e+15 to \
  7.94351e+15, 1.97945e+16 to \
  7.94351e+15, 1.97945e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.31184e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 508 polygon from \
  -4.53914e+15, 7.39128e+15 to \
  7.94351e+15, 1.9874e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.39128e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 509 polygon from \
  -4.53914e+15, 7.47071e+15 to \
  7.94351e+15, 1.99534e+16 to \
  7.94351e+15, 1.99534e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.47071e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 510 polygon from \
  -4.53914e+15, 7.55015e+15 to \
  7.94351e+15, 2.00328e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.55015e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 511 polygon from \
  -4.53914e+15, 7.62958e+15 to \
  7.94351e+15, 2.01123e+16 to \
  7.94351e+15, 2.01123e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.62958e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 512 polygon from \
  -4.53914e+15, 7.70902e+15 to \
  7.94351e+15, 2.01917e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.70902e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 513 polygon from \
  -4.53914e+15, 7.78845e+15 to \
  7.94351e+15, 2.02711e+16 to \
  7.94351e+15, 2.02711e+16 to \
  7.94351e+15, 2.02711e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.78845e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 514 polygon from \
  -4.53914e+15, 7.86789e+15 to \
  7.94351e+15, 2.03506e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.86789e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 515 polygon from \
  -4.53914e+15, 7.94732e+15 to \
  7.94351e+15, 2.043e+16 to \
  7.94351e+15, 2.043e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.94732e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 516 polygon from \
  -4.53914e+15, 8.02676e+15 to \
  7.94351e+15, 2.05095e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.02676e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 517 polygon from \
  -4.53914e+15, 8.10619e+15 to \
  7.94351e+15, 2.05889e+16 to \
  7.94351e+15, 2.05889e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.10619e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 518 polygon from \
  -4.53914e+15, 8.18563e+15 to \
  7.94351e+15, 2.06683e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.18563e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 519 polygon from \
  -4.53914e+15, 8.26506e+15 to \
  7.94351e+15, 2.07478e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.26506e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 520 polygon from \
  -4.53914e+15, 8.3445e+15 to \
  7.94351e+15, 2.08272e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.3445e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 521 polygon from \
  -4.53914e+15, 8.42393e+15 to \
  7.94351e+15, 2.09066e+16 to \
  7.94351e+15, 2.09066e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.42393e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 522 polygon from \
  -4.53914e+15, 8.50337e+15 to \
  7.94351e+15, 2.09861e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.50337e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 523 polygon from \
  -4.53914e+15, 8.5828e+15 to \
  7.94351e+15, 2.10655e+16 to \
  7.94351e+15, 2.10655e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.5828e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 524 polygon from \
  -4.53914e+15, 8.66224e+15 to \
  7.94351e+15, 2.11449e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.66224e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 525 polygon from \
  -4.53914e+15, 8.74167e+15 to \
  7.94351e+15, 2.12244e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.74167e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 526 polygon from \
  -4.53914e+15, 8.82111e+15 to \
  7.94351e+15, 2.13038e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.82111e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 527 polygon from \
  -4.53914e+15, 8.90054e+15 to \
  7.94351e+15, 2.13832e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.90054e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 528 polygon from \
  -4.53914e+15, 8.97998e+15 to \
  7.94351e+15, 2.14627e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.97998e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 529 polygon from \
  -4.53914e+15, 9.05941e+15 to \
  7.94351e+15, 2.15421e+16 to \
  7.94351e+15, 2.15421e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.05941e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 530 polygon from \
  -4.53914e+15, 9.13885e+15 to \
  7.94351e+15, 2.16215e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.13885e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 531 polygon from \
  -4.53914e+15, 9.21828e+15 to \
  7.94351e+15, 2.1701e+16 to \
  7.94351e+15, 2.1701e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.21828e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 532 polygon from \
  -4.53914e+15, 9.29772e+15 to \
  7.94351e+15, 2.17804e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.29772e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 533 polygon from \
  -4.53914e+15, 9.37715e+15 to \
  7.94351e+15, 2.18598e+16 to \
  7.94351e+15, 2.18598e+16 to \
  7.94351e+15, 2.18598e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.37715e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 534 polygon from \
  -4.53914e+15, 9.45659e+15 to \
  7.94351e+15, 2.19393e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.45659e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 535 polygon from \
  -4.53914e+15, 9.53602e+15 to \
  7.94351e+15, 2.20187e+16 to \
  7.94351e+15, 2.20187e+16 to \
  7.94351e+15, 2.20187e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.53602e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 536 polygon from \
  -4.53914e+15, 9.61546e+15 to \
  7.94351e+15, 2.20982e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.61546e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 537 polygon from \
  -4.53914e+15, 9.6949e+15 to \
  7.94351e+15, 2.21776e+16 to \
  7.94351e+15, 2.21776e+16 to \
  7.94351e+15, 2.21776e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.6949e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 538 polygon from \
  -4.53914e+15, 9.77433e+15 to \
  7.94351e+15, 2.2257e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.77433e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 539 polygon from \
  -4.53914e+15, 9.85377e+15 to \
  7.94351e+15, 2.23365e+16 to \
  7.94351e+15, 2.23365e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.85377e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 540 polygon from \
  -4.53914e+15, 9.9332e+15 to \
  7.94351e+15, 2.24159e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.9332e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 541 polygon from \
  -4.53914e+15, 1.00127e+16 to \
  7.94351e+15, 2.24953e+16 to \
  7.94351e+15, 2.24953e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.00127e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 542 polygon from \
  -4.53914e+15, 1.00921e+16 to \
  7.94351e+15, 2.25748e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.00921e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 543 polygon from \
  -4.53914e+15, 1.01716e+16 to \
  7.94351e+15, 2.26542e+16 to \
  7.94351e+15, 2.26542e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.01716e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 544 polygon from \
  -4.53914e+15, 1.0251e+16 to \
  7.94351e+15, 2.27336e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.0251e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 545 polygon from \
  -4.53914e+15, 1.03304e+16 to \
  7.94351e+15, 2.28131e+16 to \
  7.94351e+15, 2.28131e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03304e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 546 polygon from \
  -4.53914e+15, 1.04099e+16 to \
  7.94351e+15, 2.28925e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.04099e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 547 polygon from \
  -4.53914e+15, 1.04893e+16 to \
  7.94351e+15, 2.29719e+16 to \
  7.94351e+15, 2.29719e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.04893e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 548 polygon from \
  -4.53914e+15, 1.05687e+16 to \
  7.94351e+15, 2.30514e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.05687e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 549 polygon from \
  -4.53914e+15, 1.06482e+16 to \
  7.94351e+15, 2.31308e+16 to \
  7.94351e+15, 2.31308e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.06482e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 550 polygon from \
  -4.53914e+15, 1.07276e+16 to \
  7.94351e+15, 2.32102e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.07276e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 551 polygon from \
  -4.53914e+15, 1.0807e+16 to \
  7.94351e+15, 2.32897e+16 to \
  7.94351e+15, 2.32897e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.0807e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 552 polygon from \
  -4.53914e+15, 1.08865e+16 to \
  7.94351e+15, 2.33691e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.08865e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 553 polygon from \
  -4.53914e+15, 1.09659e+16 to \
  7.94351e+15, 2.34485e+16 to \
  7.94351e+15, 2.34485e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.09659e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 554 polygon from \
  -4.53914e+15, 1.10453e+16 to \
  7.94351e+15, 2.3528e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.10453e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 555 polygon from \
  -4.53914e+15, 1.11248e+16 to \
  7.94351e+15, 2.36074e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.11248e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 556 polygon from \
  -4.53914e+15, 1.12042e+16 to \
  7.94351e+15, 2.36869e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.12042e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 557 polygon from \
  -4.53914e+15, 1.12836e+16 to \
  7.94351e+15, 2.37663e+16 to \
  7.94351e+15, 2.37663e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.12836e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 558 polygon from \
  -4.53914e+15, 1.13631e+16 to \
  7.94351e+15, 2.38457e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.13631e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 559 polygon from \
  -4.53914e+15, 1.14425e+16 to \
  7.94351e+15, 2.39252e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.14425e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 560 polygon from \
  -4.53914e+15, 1.15219e+16 to \
  7.94351e+15, 2.40046e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.15219e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 561 polygon from \
  -4.53914e+15, 1.16014e+16 to \
  7.94351e+15, 2.4084e+16 to \
  7.94351e+15, 2.4084e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.16014e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 562 polygon from \
  -4.53914e+15, 1.16808e+16 to \
  7.94351e+15, 2.41635e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.16808e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 563 polygon from \
  -4.53914e+15, 1.17603e+16 to \
  7.94351e+15, 2.42429e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.17603e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 564 polygon from \
  -4.53914e+15, 1.18397e+16 to \
  7.94351e+15, 2.43223e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.18397e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 565 polygon from \
  -4.53914e+15, 1.19191e+16 to \
  7.94351e+15, 2.44018e+16 to \
  7.94351e+15, 2.44018e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19191e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 566 polygon from \
  -4.53914e+15, 1.19986e+16 to \
  7.94351e+15, 2.44812e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19986e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 567 polygon from \
  -4.53914e+15, 1.2078e+16 to \
  7.94351e+15, 2.45606e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.2078e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 568 polygon from \
  -4.53914e+15, 1.21574e+16 to \
  7.94351e+15, 2.46401e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.21574e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 569 polygon from \
  -4.53914e+15, 1.22369e+16 to \
  7.94351e+15, 2.47195e+16 to \
  7.94351e+15, 2.47195e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.22369e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 570 polygon from \
  -4.53914e+15, 1.23163e+16 to \
  7.94351e+15, 2.47989e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.23163e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 571 polygon from \
  -4.53914e+15, 1.23957e+16 to \
  7.94351e+15, 2.48784e+16 to \
  7.94351e+15, 2.48784e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.23957e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 572 polygon from \
  -4.53914e+15, 1.24752e+16 to \
  7.94351e+15, 2.49578e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.24752e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 573 polygon from \
  -4.53914e+15, 1.25546e+16 to \
  7.94351e+15, 2.50372e+16 to \
  7.94351e+15, 2.50372e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.25546e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 574 polygon from \
  -4.53914e+15, 1.2634e+16 to \
  7.94351e+15, 2.51167e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.2634e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 575 polygon from \
  -4.53914e+15, 1.27135e+16 to \
  7.94351e+15, 2.51961e+16 to \
  7.94351e+15, 2.51961e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27135e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 576 polygon from \
  -4.53914e+15, 1.27929e+16 to \
  7.94351e+15, 2.52756e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27929e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 577 polygon from \
  -4.53914e+15, 1.28723e+16 to \
  7.94351e+15, 2.5355e+16 to \
  7.94351e+15, 2.5355e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.28723e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 578 polygon from \
  -4.53914e+15, 1.29518e+16 to \
  7.94351e+15, 2.54344e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.29518e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 579 polygon from \
  -4.53914e+15, 1.30312e+16 to \
  7.94351e+15, 2.55139e+16 to \
  7.94351e+15, 2.55139e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.30312e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 580 polygon from \
  -4.53914e+15, 1.31106e+16 to \
  7.94351e+15, 2.55933e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.31106e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 581 polygon from \
  -4.53914e+15, 1.31901e+16 to \
  7.94351e+15, 2.56727e+16 to \
  7.94351e+15, 2.56727e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.31901e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 582 polygon from \
  -4.53914e+15, 1.32695e+16 to \
  7.94351e+15, 2.57522e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.32695e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 583 polygon from \
  -4.53914e+15, 1.3349e+16 to \
  7.94351e+15, 2.58316e+16 to \
  7.94351e+15, 2.58316e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.3349e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 584 polygon from \
  -4.53914e+15, 1.34284e+16 to \
  7.94351e+15, 2.5911e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.34284e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 585 polygon from \
  -4.53914e+15, 1.35078e+16 to \
  7.94351e+15, 2.59905e+16 to \
  7.94351e+15, 2.59905e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35078e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 586 polygon from \
  -4.53914e+15, 1.35873e+16 to \
  7.94351e+15, 2.60699e+16 to \
  7.94351e+15, 2.60699e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35873e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 587 polygon from \
  -4.53914e+15, 1.36667e+16 to \
  7.94351e+15, 2.61493e+16 to \
  7.94351e+15, 2.61493e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.36667e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 588 polygon from \
  -4.53914e+15, 1.37461e+16 to \
  7.94351e+15, 2.62288e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.37461e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 589 polygon from \
  -4.53914e+15, 1.38256e+16 to \
  7.94351e+15, 2.63082e+16 to \
  7.94351e+15, 2.63082e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.38256e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 590 polygon from \
  -4.53914e+15, 1.3905e+16 to \
  7.94351e+15, 2.63876e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.3905e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 591 polygon from \
  -4.53914e+15, 1.39844e+16 to \
  7.94351e+15, 2.64671e+16 to \
  7.94351e+15, 2.64671e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.39844e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 592 polygon from \
  -4.53914e+15, 1.40639e+16 to \
  7.94351e+15, 2.65465e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.40639e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 593 polygon from \
  -4.53914e+15, 1.41433e+16 to \
  7.94351e+15, 2.66259e+16 to \
  7.94351e+15, 2.66259e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.41433e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 594 polygon from \
  -4.53914e+15, 1.42227e+16 to \
  7.94351e+15, 2.67054e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.42227e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 595 polygon from \
  -4.53914e+15, 1.43022e+16 to \
  7.94351e+15, 2.67848e+16 to \
  7.94351e+15, 2.67848e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.43022e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 596 polygon from \
  -4.53914e+15, 1.43816e+16 to \
  7.94351e+15, 2.68643e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.43816e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 597 polygon from \
  -4.53914e+15, 1.4461e+16 to \
  7.94351e+15, 2.69437e+16 to \
  7.94351e+15, 2.69437e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.4461e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 598 polygon from \
  -4.53914e+15, 1.45405e+16 to \
  7.94351e+15, 2.70231e+16 to \
  7.94351e+15, 2.70231e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.45405e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 599 polygon from \
  -4.53914e+15, 1.46199e+16 to \
  7.94351e+15, 2.71026e+16 to \
  7.94351e+15, 2.71026e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.46199e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 600 polygon from \
  -4.53914e+15, 1.46993e+16 to \
  7.94351e+15, 2.7182e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.46993e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 601 polygon from \
  -4.53914e+15, 3.43088e+15 to \
  7.94351e+15, 3.43088e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.43088e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 602 polygon from \
  -4.53914e+15, 3.35144e+15 to \
  -4.38027e+15, 3.51031e+15 to \
  7.94351e+15, 3.51031e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.35144e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 603 polygon from \
  -4.53914e+15, 3.30605e+15 to \
  -4.25544e+15, 3.58975e+15 to \
  7.94351e+15, 3.58975e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.30605e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 604 polygon from \
  -4.53914e+15, 3.26066e+15 to \
  -4.13062e+15, 3.66918e+15 to \
  7.94351e+15, 3.66918e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.26066e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 605 polygon from \
  -4.53914e+15, 3.21527e+15 to \
  -4.00579e+15, 3.74862e+15 to \
  7.94351e+15, 3.74862e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.21527e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 606 polygon from \
  -4.53914e+15, 3.16988e+15 to \
  -3.88096e+15, 3.82805e+15 to \
  7.94351e+15, 3.82805e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.16988e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 607 polygon from \
  -4.53914e+15, 3.12448e+15 to \
  -3.75614e+15, 3.90749e+15 to \
  7.94351e+15, 3.90749e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.12448e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 608 polygon from \
  -4.53914e+15, 3.07909e+15 to \
  -3.63131e+15, 3.98692e+15 to \
  7.94351e+15, 3.98692e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.07909e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 609 polygon from \
  -4.53914e+15, 3.0337e+15 to \
  -3.50648e+15, 4.06636e+15 to \
  7.94351e+15, 4.06636e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.0337e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 610 polygon from \
  -4.53914e+15, 2.98831e+15 to \
  -3.38166e+15, 4.14579e+15 to \
  7.94351e+15, 4.14579e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.98831e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 611 polygon from \
  -4.53914e+15, 2.94292e+15 to \
  -3.25683e+15, 4.22523e+15 to \
  7.94351e+15, 4.22523e+15 to \
  7.94351e+15, 4.22523e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.94292e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 612 polygon from \
  -4.53914e+15, 2.89753e+15 to \
  -3.132e+15, 4.30466e+15 to \
  7.94351e+15, 4.30466e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.89753e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 613 polygon from \
  -4.53914e+15, 2.85214e+15 to \
  -3.00718e+15, 4.3841e+15 to \
  7.94351e+15, 4.3841e+15 to \
  7.94351e+15, 4.3841e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.85214e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 614 polygon from \
  -4.53914e+15, 2.80674e+15 to \
  -2.88235e+15, 4.46353e+15 to \
  7.94351e+15, 4.46353e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.80674e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 615 polygon from \
  -4.53914e+15, 2.76135e+15 to \
  -2.75753e+15, 4.54297e+15 to \
  7.94351e+15, 4.54297e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.76135e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 616 polygon from \
  -4.53914e+15, 2.71596e+15 to \
  -2.6327e+15, 4.6224e+15 to \
  7.94351e+15, 4.6224e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.71596e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 617 polygon from \
  -4.53914e+15, 2.67057e+15 to \
  -2.50787e+15, 4.70184e+15 to \
  7.94351e+15, 4.70184e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.67057e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 618 polygon from \
  -4.53914e+15, 2.62518e+15 to \
  -2.38305e+15, 4.78127e+15 to \
  7.94351e+15, 4.78127e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.62518e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 619 polygon from \
  -4.53914e+15, 2.57979e+15 to \
  -2.25822e+15, 4.86071e+15 to \
  7.94351e+15, 4.86071e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.57979e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 620 polygon from \
  -4.53914e+15, 2.5344e+15 to \
  -2.13339e+15, 4.94014e+15 to \
  7.94351e+15, 4.94014e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.5344e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 621 polygon from \
  -4.53914e+15, 2.489e+15 to \
  -2.00857e+15, 5.01958e+15 to \
  7.94351e+15, 5.01958e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.489e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 622 polygon from \
  -4.53914e+15, 2.44361e+15 to \
  -1.88374e+15, 5.09901e+15 to \
  7.94351e+15, 5.09901e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.44361e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 623 polygon from \
  -4.53914e+15, 2.39822e+15 to \
  -1.75891e+15, 5.17845e+15 to \
  7.94351e+15, 5.17845e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.39822e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 624 polygon from \
  -4.53914e+15, 2.35283e+15 to \
  -1.63409e+15, 5.25788e+15 to \
  7.94351e+15, 5.25788e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.35283e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 625 polygon from \
  -4.53914e+15, 2.30744e+15 to \
  -1.50926e+15, 5.33732e+15 to \
  7.94351e+15, 5.33732e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.30744e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 626 polygon from \
  -4.53914e+15, 2.26205e+15 to \
  -1.38443e+15, 5.41675e+15 to \
  7.94351e+15, 5.41675e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.26205e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 627 polygon from \
  -4.53914e+15, 2.21665e+15 to \
  -1.25961e+15, 5.49619e+15 to \
  7.94351e+15, 5.49619e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.21665e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 628 polygon from \
  -4.53914e+15, 2.17126e+15 to \
  -1.13478e+15, 5.57562e+15 to \
  7.94351e+15, 5.57562e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.17126e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 629 polygon from \
  -4.53914e+15, 2.12587e+15 to \
  -1.00995e+15, 5.65506e+15 to \
  7.94351e+15, 5.65506e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.12587e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 630 polygon from \
  -4.53914e+15, 2.08048e+15 to \
  -8.85133e+14, 5.73449e+15 to \
  7.94351e+15, 5.73449e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.08048e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 631 polygon from \
  -4.53914e+15, 2.03509e+15 to \
  -7.60306e+14, 5.81393e+15 to \
  7.94351e+15, 5.81393e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.03509e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 632 polygon from \
  -4.53914e+15, 1.9897e+15 to \
  -6.3548e+14, 5.89336e+15 to \
  7.94351e+15, 5.89336e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.9897e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 633 polygon from \
  -4.53914e+15, 1.94431e+15 to \
  -5.10653e+14, 5.9728e+15 to \
  7.94351e+15, 5.9728e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.94431e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 634 polygon from \
  -4.53914e+15, 1.89891e+15 to \
  -3.85827e+14, 6.05223e+15 to \
  7.94351e+15, 6.05223e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.89891e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 635 polygon from \
  -4.53914e+15, 1.85352e+15 to \
  -2.61e+14, 6.13167e+15 to \
  7.94351e+15, 6.13167e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.85352e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 636 polygon from \
  -4.53914e+15, 1.80813e+15 to \
  -1.36174e+14, 6.2111e+15 to \
  7.94351e+15, 6.2111e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.80813e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 637 polygon from \
  -4.53914e+15, 1.76274e+15 to \
  -1.13478e+13, 6.29054e+15 to \
  7.94351e+15, 6.29054e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.76274e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 638 polygon from \
  -4.53914e+15, 1.71735e+15 to \
  1.13479e+14, 6.36997e+15 to \
  7.94351e+15, 6.36997e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.71735e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 639 polygon from \
  -4.53914e+15, 1.67196e+15 to \
  2.38306e+14, 6.44941e+15 to \
  7.94351e+15, 6.44941e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.67196e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 640 polygon from \
  -4.53914e+15, 1.62657e+15 to \
  3.63132e+14, 6.52884e+15 to \
  7.94351e+15, 6.52884e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.62657e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 641 polygon from \
  -4.53914e+15, 1.58117e+15 to \
  4.87959e+14, 6.60828e+15 to \
  7.94351e+15, 6.60828e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.58117e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 642 polygon from \
  -4.53914e+15, 1.53578e+15 to \
  6.12785e+14, 6.68771e+15 to \
  7.94351e+15, 6.68771e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.53578e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 643 polygon from \
  -4.53914e+15, 1.49039e+15 to \
  7.37611e+14, 6.76715e+15 to \
  7.94351e+15, 6.76715e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.49039e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 644 polygon from \
  -4.53914e+15, 1.445e+15 to \
  8.62438e+14, 6.84658e+15 to \
  7.94351e+15, 6.84658e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.445e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 645 polygon from \
  -4.53914e+15, 1.39961e+15 to \
  9.87264e+14, 6.92602e+15 to \
  7.94351e+15, 6.92602e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.39961e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 646 polygon from \
  -4.53914e+15, 1.35422e+15 to \
  1.1121e+15, 7.00545e+15 to \
  7.94351e+15, 7.00545e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35422e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 647 polygon from \
  -4.53914e+15, 1.30883e+15 to \
  1.23692e+15, 7.08489e+15 to \
  7.94351e+15, 7.08489e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.30883e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 648 polygon from \
  -4.53914e+15, 1.26343e+15 to \
  1.36175e+15, 7.16432e+15 to \
  7.94351e+15, 7.16432e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.26343e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 649 polygon from \
  -4.53914e+15, 1.21804e+15 to \
  1.48657e+15, 7.24376e+15 to \
  7.94351e+15, 7.24376e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.21804e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 650 polygon from \
  -4.53914e+15, 1.17265e+15 to \
  1.6114e+15, 7.32319e+15 to \
  7.94351e+15, 7.32319e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.17265e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 651 polygon from \
  -4.53914e+15, 1.12726e+15 to \
  1.73623e+15, 7.40263e+15 to \
  7.94351e+15, 7.40263e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.12726e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 652 polygon from \
  -4.53914e+15, 1.08187e+15 to \
  1.86105e+15, 7.48206e+15 to \
  7.94351e+15, 7.48206e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.08187e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 653 polygon from \
  -4.53914e+15, 1.03648e+15 to \
  1.98588e+15, 7.5615e+15 to \
  7.94351e+15, 7.5615e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03648e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 654 polygon from \
  -4.53914e+15, 9.91082e+14 to \
  2.11071e+15, 7.64093e+15 to \
  7.94351e+15, 7.64093e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.91082e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 655 polygon from \
  -4.53914e+15, 9.4569e+14 to \
  2.23553e+15, 7.72037e+15 to \
  7.94351e+15, 7.72037e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.4569e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 656 polygon from \
  -4.53914e+15, 9.00299e+14 to \
  2.36036e+15, 7.7998e+15 to \
  7.94351e+15, 7.7998e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.00299e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 657 polygon from \
  -4.53914e+15, 8.54907e+14 to \
  2.48519e+15, 7.87924e+15 to \
  7.94351e+15, 7.87924e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.54907e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 658 polygon from \
  -4.53914e+15, 8.09516e+14 to \
  2.61001e+15, 7.95867e+15 to \
  7.94351e+15, 7.95867e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.09516e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 659 polygon from \
  -4.53914e+15, 7.64124e+14 to \
  2.73484e+15, 8.03811e+15 to \
  7.94351e+15, 8.03811e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.64124e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 660 polygon from \
  -4.53914e+15, 7.18733e+14 to \
  2.85967e+15, 8.11754e+15 to \
  7.94351e+15, 8.11754e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.18733e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 661 polygon from \
  -4.53914e+15, 6.73341e+14 to \
  2.98449e+15, 8.19698e+15 to \
  7.94351e+15, 8.19698e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.73341e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 662 polygon from \
  -4.53914e+15, 6.2795e+14 to \
  3.10932e+15, 8.27641e+15 to \
  7.94351e+15, 8.27641e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.2795e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 663 polygon from \
  -4.53914e+15, 5.82559e+14 to \
  3.23415e+15, 8.35585e+15 to \
  7.94351e+15, 8.35585e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.82559e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 664 polygon from \
  -4.53914e+15, 5.37167e+14 to \
  3.35897e+15, 8.43528e+15 to \
  7.94351e+15, 8.43528e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.37167e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 665 polygon from \
  -4.53914e+15, 4.91776e+14 to \
  3.4838e+15, 8.51472e+15 to \
  7.94351e+15, 8.51472e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.91776e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 666 polygon from \
  -4.53914e+15, 4.46384e+14 to \
  3.60862e+15, 8.59415e+15 to \
  7.94351e+15, 8.59415e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.46384e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 667 polygon from \
  -4.53914e+15, 4.00993e+14 to \
  3.73345e+15, 8.67359e+15 to \
  7.94351e+15, 8.67359e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.00993e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 668 polygon from \
  -4.53914e+15, 3.55601e+14 to \
  3.85828e+15, 8.75302e+15 to \
  7.94351e+15, 8.75302e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.55601e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 669 polygon from \
  -4.53914e+15, 3.1021e+14 to \
  3.9831e+15, 8.83246e+15 to \
  7.94351e+15, 8.83246e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.1021e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 670 polygon from \
  -4.53914e+15, 2.64818e+14 to \
  4.10793e+15, 8.91189e+15 to \
  7.94351e+15, 8.91189e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.64818e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 671 polygon from \
  -4.53914e+15, 2.19427e+14 to \
  4.23276e+15, 8.99133e+15 to \
  7.94351e+15, 8.99133e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.19427e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 672 polygon from \
  -4.53914e+15, 1.74036e+14 to \
  4.35758e+15, 9.07076e+15 to \
  7.94351e+15, 9.07076e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.74036e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 673 polygon from \
  -4.53914e+15, 1.28644e+14 to \
  4.48241e+15, 9.1502e+15 to \
  7.94351e+15, 9.1502e+15 to \
  7.94351e+15, 9.1502e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.28644e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 674 polygon from \
  -4.53914e+15, 8.32523e+13 to \
  4.60724e+15, 9.22963e+15 to \
  7.94351e+15, 9.22963e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.32523e+13 front fs empty border lc rgb '#6165' lw 0.200001
set object 675 polygon from \
  -4.53914e+15, 3.78608e+13 to \
  4.73206e+15, 9.30907e+15 to \
  7.94351e+15, 9.30907e+15 to \
  7.94351e+15, 9.30907e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.78608e+13 front fs empty border lc rgb '#6165' lw 0.200001
set object 676 polygon from \
  4.85689e+15, 9.3885e+15 to \
  7.94351e+15, 9.3885e+15 to \
  7.94351e+15, 0 to \
  -4.53161e+15, -0 to \
  4.85689e+15, 9.3885e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 677 polygon from \
  4.98172e+15, 9.46794e+15 to \
  7.94351e+15, 9.46794e+15 to \
  7.94351e+15, 9.46794e+15 to \
  7.94351e+15, 0 to \
  -4.48622e+15, -0 to \
  4.98172e+15, 9.46794e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 678 polygon from \
  5.10654e+15, 9.54737e+15 to \
  7.94351e+15, 9.54737e+15 to \
  7.94351e+15, 0 to \
  -4.44083e+15, -0 to \
  5.10654e+15, 9.54737e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 679 polygon from \
  5.23137e+15, 9.62681e+15 to \
  7.94351e+15, 9.62681e+15 to \
  7.94351e+15, 0 to \
  -4.39543e+15, -0 to \
  5.23137e+15, 9.62681e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 680 polygon from \
  5.3562e+15, 9.70624e+15 to \
  7.94351e+15, 9.70624e+15 to \
  7.94351e+15, 0 to \
  -4.35004e+15, -0 to \
  5.3562e+15, 9.70624e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 681 polygon from \
  5.48102e+15, 9.78568e+15 to \
  7.94351e+15, 9.78568e+15 to \
  7.94351e+15, 0 to \
  -4.30465e+15, -0 to \
  5.48102e+15, 9.78568e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 682 polygon from \
  5.60585e+15, 9.86511e+15 to \
  7.94351e+15, 9.86511e+15 to \
  7.94351e+15, 9.86511e+15 to \
  7.94351e+15, 0 to \
  -4.25926e+15, -0 to \
  5.60585e+15, 9.86511e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 683 polygon from \
  5.73067e+15, 9.94455e+15 to \
  7.94351e+15, 9.94455e+15 to \
  7.94351e+15, 0 to \
  -4.21387e+15, -0 to \
  5.73067e+15, 9.94455e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 684 polygon from \
  5.8555e+15, 1.0024e+16 to \
  7.94351e+15, 1.0024e+16 to \
  7.94351e+15, 1.0024e+16 to \
  7.94351e+15, 0 to \
  -4.16848e+15, -0 to \
  5.8555e+15, 1.0024e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 685 polygon from \
  5.98033e+15, 1.01035e+16 to \
  7.94351e+15, 1.01035e+16 to \
  7.94351e+15, 1.01035e+16 to \
  7.94351e+15, 0 to \
  -4.12309e+15, -0 to \
  5.98033e+15, 1.01035e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 686 polygon from \
  6.10515e+15, 1.01829e+16 to \
  7.94351e+15, 1.01829e+16 to \
  7.94351e+15, 1.01829e+16 to \
  7.94351e+15, 0 to \
  -4.07769e+15, -0 to \
  6.10515e+15, 1.01829e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 687 polygon from \
  6.22998e+15, 1.02623e+16 to \
  7.94351e+15, 1.02623e+16 to \
  7.94351e+15, 1.02623e+16 to \
  7.94351e+15, 3.77571e+13 to \
  7.90575e+15, -0 to \
  -4.0323e+15, -0 to \
  6.22998e+15, 1.02623e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 688 polygon from \
  6.35481e+15, 1.03418e+16 to \
  7.94351e+15, 1.03418e+16 to \
  7.94351e+15, 1.03418e+16 to \
  7.94351e+15, 1.17193e+14 to \
  7.82632e+15, -0 to \
  -3.98691e+15, -0 to \
  6.35481e+15, 1.03418e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 689 polygon from \
  6.47963e+15, 1.04212e+16 to \
  7.94351e+15, 1.04212e+16 to \
  7.94351e+15, 1.04212e+16 to \
  7.94351e+15, 1.96628e+14 to \
  7.74688e+15, -0 to \
  -3.94152e+15, -0 to \
  6.47963e+15, 1.04212e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 690 polygon from \
  6.60446e+15, 1.05006e+16 to \
  7.94351e+15, 1.05006e+16 to \
  7.94351e+15, 1.05006e+16 to \
  7.94351e+15, 2.76063e+14 to \
  7.66745e+15, -0 to \
  -3.89613e+15, -0 to \
  6.60446e+15, 1.05006e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 691 polygon from \
  6.72929e+15, 1.05801e+16 to \
  7.94351e+15, 1.05801e+16 to \
  7.94351e+15, 1.05801e+16 to \
  7.94351e+15, 3.55498e+14 to \
  7.58801e+15, -0 to \
  -3.85074e+15, -0 to \
  6.72929e+15, 1.05801e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 692 polygon from \
  6.85411e+15, 1.06595e+16 to \
  7.94351e+15, 1.06595e+16 to \
  7.94351e+15, 1.06595e+16 to \
  7.94351e+15, 4.34933e+14 to \
  7.50858e+15, -0 to \
  -3.80535e+15, -0 to \
  6.85411e+15, 1.06595e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 693 polygon from \
  6.97894e+15, 1.07389e+16 to \
  7.94351e+15, 1.07389e+16 to \
  7.94351e+15, 1.07389e+16 to \
  7.94351e+15, 5.14368e+14 to \
  7.42914e+15, -0 to \
  -3.75995e+15, -0 to \
  6.97894e+15, 1.07389e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 694 polygon from \
  7.10377e+15, 1.08184e+16 to \
  7.94351e+15, 1.08184e+16 to \
  7.94351e+15, 1.08184e+16 to \
  7.94351e+15, 5.93803e+14 to \
  7.34971e+15, -0 to \
  -3.71456e+15, -0 to \
  7.10377e+15, 1.08184e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 695 polygon from \
  7.22859e+15, 1.08978e+16 to \
  7.94351e+15, 1.08978e+16 to \
  7.94351e+15, 1.08978e+16 to \
  7.94351e+15, 6.73238e+14 to \
  7.27027e+15, -0 to \
  -3.66917e+15, -0 to \
  7.22859e+15, 1.08978e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 696 polygon from \
  7.35342e+15, 1.09772e+16 to \
  7.94351e+15, 1.09772e+16 to \
  7.94351e+15, 1.09772e+16 to \
  7.94351e+15, 7.52673e+14 to \
  7.19084e+15, -0 to \
  -3.62378e+15, -0 to \
  7.35342e+15, 1.09772e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 697 polygon from \
  7.47825e+15, 1.10567e+16 to \
  7.94351e+15, 1.10567e+16 to \
  7.94351e+15, 1.10567e+16 to \
  7.94351e+15, 8.32108e+14 to \
  7.1114e+15, -0 to \
  -3.57839e+15, -0 to \
  7.47825e+15, 1.10567e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 698 polygon from \
  7.60307e+15, 1.11361e+16 to \
  7.94351e+15, 1.11361e+16 to \
  7.94351e+15, 1.11361e+16 to \
  7.94351e+15, 9.11543e+14 to \
  7.03197e+15, -0 to \
  -3.533e+15, -0 to \
  7.60307e+15, 1.11361e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 699 polygon from \
  7.7279e+15, 1.12156e+16 to \
  7.94351e+15, 1.12156e+16 to \
  7.94351e+15, 1.12156e+16 to \
  7.94351e+15, 9.90978e+14 to \
  6.95253e+15, -0 to \
  -3.48761e+15, -0 to \
  7.7279e+15, 1.12156e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 700 polygon from \
  7.85272e+15, 1.1295e+16 to \
  7.94351e+15, 1.1295e+16 to \
  7.94351e+15, 1.1295e+16 to \
  7.94351e+15, 1.07042e+15 to \
  6.87309e+15, -0 to \
  -3.44221e+15, -0 to \
  7.85272e+15, 1.1295e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 701 polygon from \
  7.94351e+15, 1.13744e+16 to \
  7.94351e+15, 1.13744e+16 to \
  7.94351e+15, 1.13744e+16 to \
  7.94351e+15, 1.14985e+15 to \
  6.79366e+15, -0 to \
  -3.43087e+15, -0 to \
  7.94351e+15, 1.13744e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 702 polygon from \
  7.94351e+15, 1.14539e+16 to \
  7.94351e+15, 1.14539e+16 to \
  7.94351e+15, 1.14539e+16 to \
  7.94351e+15, 1.10446e+15 to \
  6.83905e+15, -0 to \
  -3.5103e+15, -0 to \
  7.94351e+15, 1.14539e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 703 polygon from \
  7.94351e+15, 1.15333e+16 to \
  7.94351e+15, 1.15333e+16 to \
  7.94351e+15, 1.15333e+16 to \
  7.94351e+15, 1.05907e+15 to \
  6.88444e+15, -0 to \
  -3.58974e+15, -0 to \
  7.94351e+15, 1.15333e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 704 polygon from \
  7.94351e+15, 1.16127e+16 to \
  7.94351e+15, 1.16127e+16 to \
  7.94351e+15, 1.01368e+15 to \
  6.92983e+15, -0 to \
  -3.66917e+15, -0 to \
  7.94351e+15, 1.16127e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 705 polygon from \
  7.94351e+15, 1.16922e+16 to \
  7.94351e+15, 1.16922e+16 to \
  7.94351e+15, 1.16922e+16 to \
  7.94351e+15, 9.68282e+14 to \
  6.97523e+15, -0 to \
  -3.74861e+15, -0 to \
  7.94351e+15, 1.16922e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 706 polygon from \
  7.94351e+15, 1.17716e+16 to \
  7.94351e+15, 1.17716e+16 to \
  7.94351e+15, 1.17716e+16 to \
  7.94351e+15, 9.22891e+14 to \
  7.02062e+15, -0 to \
  -3.82804e+15, -0 to \
  7.94351e+15, 1.17716e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 707 polygon from \
  7.94351e+15, 1.1851e+16 to \
  7.94351e+15, 1.1851e+16 to \
  7.94351e+15, 1.1851e+16 to \
  7.94351e+15, 8.77499e+14 to \
  7.06601e+15, -0 to \
  -3.90748e+15, -0 to \
  7.94351e+15, 1.1851e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 708 polygon from \
  7.94351e+15, 1.19305e+16 to \
  7.94351e+15, 1.19305e+16 to \
  7.94351e+15, 8.32108e+14 to \
  7.1114e+15, -0 to \
  -3.98691e+15, -0 to \
  7.94351e+15, 1.19305e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 709 polygon from \
  7.94351e+15, 1.20099e+16 to \
  7.94351e+15, 1.20099e+16 to \
  7.94351e+15, 7.86716e+14 to \
  7.15679e+15, -0 to \
  -4.06635e+15, -0 to \
  7.94351e+15, 1.20099e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 710 polygon from \
  7.94351e+15, 1.20893e+16 to \
  7.94351e+15, 1.20893e+16 to \
  7.94351e+15, 7.41325e+14 to \
  7.20218e+15, -0 to \
  -4.14578e+15, -0 to \
  7.94351e+15, 1.20893e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 711 polygon from \
  7.94351e+15, 1.21688e+16 to \
  7.94351e+15, 1.21688e+16 to \
  7.94351e+15, 1.21688e+16 to \
  7.94351e+15, 6.95933e+14 to \
  7.24757e+15, -0 to \
  -4.22522e+15, -0 to \
  7.94351e+15, 1.21688e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 712 polygon from \
  7.94351e+15, 1.22482e+16 to \
  7.94351e+15, 1.22482e+16 to \
  7.94351e+15, 1.22482e+16 to \
  7.94351e+15, 6.50542e+14 to \
  7.29297e+15, -0 to \
  -4.30465e+15, -0 to \
  7.94351e+15, 1.22482e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 713 polygon from \
  7.94351e+15, 1.23276e+16 to \
  7.94351e+15, 1.23276e+16 to \
  7.94351e+15, 6.05151e+14 to \
  7.33836e+15, -0 to \
  -4.38409e+15, -0 to \
  7.94351e+15, 1.23276e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 714 polygon from \
  7.94351e+15, 1.24071e+16 to \
  7.94351e+15, 1.24071e+16 to \
  7.94351e+15, 1.24071e+16 to \
  7.94351e+15, 5.59759e+14 to \
  7.38375e+15, -0 to \
  -4.46352e+15, -0 to \
  7.94351e+15, 1.24071e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 715 polygon from \
  -4.53914e+15, 3.81718e+12 to \
  7.94351e+15, 1.24865e+16 to \
  7.94351e+15, 1.24865e+16 to \
  7.94351e+15, 1.24865e+16 to \
  7.94351e+15, 5.14368e+14 to \
  7.42914e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.81718e+12 front fs empty border lc rgb '#6165' lw 0.200001
set object 716 polygon from \
  -4.53914e+15, 8.32523e+13 to \
  7.94351e+15, 1.25659e+16 to \
  7.94351e+15, 1.25659e+16 to \
  7.94351e+15, 1.25659e+16 to \
  7.94351e+15, 4.68976e+14 to \
  7.47453e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.32523e+13 front fs empty border lc rgb '#6165' lw 0.200001
set object 717 polygon from \
  -4.53914e+15, 1.62688e+14 to \
  7.94351e+15, 1.26454e+16 to \
  7.94351e+15, 1.26454e+16 to \
  7.94351e+15, 1.26454e+16 to \
  7.94351e+15, 4.23585e+14 to \
  7.51992e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.62688e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 718 polygon from \
  -4.53914e+15, 2.42123e+14 to \
  7.94351e+15, 1.27248e+16 to \
  7.94351e+15, 1.27248e+16 to \
  7.94351e+15, 3.78193e+14 to \
  7.56531e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.42123e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 719 polygon from \
  -4.53914e+15, 3.21558e+14 to \
  7.94351e+15, 1.28043e+16 to \
  7.94351e+15, 1.28043e+16 to \
  7.94351e+15, 3.32802e+14 to \
  7.61071e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.21558e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 720 polygon from \
  -4.53914e+15, 4.00993e+14 to \
  7.94351e+15, 1.28837e+16 to \
  7.94351e+15, 1.28837e+16 to \
  7.94351e+15, 1.28837e+16 to \
  7.94351e+15, 2.87411e+14 to \
  7.6561e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.00993e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 721 polygon from \
  -4.53914e+15, 4.80428e+14 to \
  7.94351e+15, 1.29631e+16 to \
  7.94351e+15, 1.29631e+16 to \
  7.94351e+15, 1.29631e+16 to \
  7.94351e+15, 2.42019e+14 to \
  7.70149e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.80428e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 722 polygon from \
  -4.53914e+15, 5.59863e+14 to \
  7.94351e+15, 1.30426e+16 to \
  7.94351e+15, 1.30426e+16 to \
  7.94351e+15, 1.30426e+16 to \
  7.94351e+15, 1.96628e+14 to \
  7.74688e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.59863e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 723 polygon from \
  -4.53914e+15, 6.39298e+14 to \
  7.94351e+15, 1.3122e+16 to \
  7.94351e+15, 1.3122e+16 to \
  7.94351e+15, 1.3122e+16 to \
  7.94351e+15, 1.51236e+14 to \
  7.79227e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.39298e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 724 polygon from \
  -4.53914e+15, 7.18733e+14 to \
  7.94351e+15, 1.32014e+16 to \
  7.94351e+15, 1.32014e+16 to \
  7.94351e+15, 1.05845e+14 to \
  7.83766e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.18733e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 725 polygon from \
  -4.53914e+15, 7.98168e+14 to \
  7.94351e+15, 1.32809e+16 to \
  7.94351e+15, 1.32809e+16 to \
  7.94351e+15, 1.32809e+16 to \
  7.94351e+15, 6.04529e+13 to \
  7.88305e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.98168e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 726 polygon from \
  -4.53914e+15, 8.77603e+14 to \
  7.94351e+15, 1.33603e+16 to \
  7.94351e+15, 1.33603e+16 to \
  7.94351e+15, 1.33603e+16 to \
  7.94351e+15, 1.50614e+13 to \
  7.92845e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.77603e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 727 polygon from \
  -4.53914e+15, 9.57038e+14 to \
  7.94351e+15, 1.34397e+16 to \
  7.94351e+15, 1.34397e+16 to \
  7.94351e+15, 1.34397e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.57038e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 728 polygon from \
  -4.53914e+15, 1.03648e+15 to \
  7.94351e+15, 1.35192e+16 to \
  7.94351e+15, 1.35192e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03648e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 729 polygon from \
  -4.53914e+15, 1.11591e+15 to \
  7.94351e+15, 1.35986e+16 to \
  7.94351e+15, 1.35986e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.11591e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 730 polygon from \
  -4.53914e+15, 1.19535e+15 to \
  7.94351e+15, 1.3678e+16 to \
  7.94351e+15, 1.3678e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19535e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 731 polygon from \
  -4.53914e+15, 1.27478e+15 to \
  7.94351e+15, 1.37575e+16 to \
  7.94351e+15, 1.37575e+16 to \
  7.94351e+15, 1.37575e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27478e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 732 polygon from \
  -4.53914e+15, 1.35422e+15 to \
  7.94351e+15, 1.38369e+16 to \
  7.94351e+15, 1.38369e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35422e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 733 polygon from \
  -4.53914e+15, 1.43365e+15 to \
  7.94351e+15, 1.39163e+16 to \
  7.94351e+15, 1.39163e+16 to \
  7.94351e+15, 1.39163e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.43365e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 734 polygon from \
  -4.53914e+15, 1.51309e+15 to \
  7.94351e+15, 1.39958e+16 to \
  7.94351e+15, 1.39958e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.51309e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 735 polygon from \
  -4.53914e+15, 1.59252e+15 to \
  7.94351e+15, 1.40752e+16 to \
  7.94351e+15, 1.40752e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.59252e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 736 polygon from \
  -4.53914e+15, 1.67196e+15 to \
  7.94351e+15, 1.41546e+16 to \
  7.94351e+15, 1.41546e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.67196e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 737 polygon from \
  -4.53914e+15, 1.75139e+15 to \
  7.94351e+15, 1.42341e+16 to \
  7.94351e+15, 1.42341e+16 to \
  7.94351e+15, 1.42341e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.75139e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 738 polygon from \
  -4.53914e+15, 1.83083e+15 to \
  7.94351e+15, 1.43135e+16 to \
  7.94351e+15, 1.43135e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.83083e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 739 polygon from \
  -4.53914e+15, 1.91026e+15 to \
  7.94351e+15, 1.4393e+16 to \
  7.94351e+15, 1.4393e+16 to \
  7.94351e+15, 1.4393e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.91026e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 740 polygon from \
  -4.53914e+15, 1.9897e+15 to \
  7.94351e+15, 1.44724e+16 to \
  7.94351e+15, 1.44724e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.9897e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 741 polygon from \
  -4.53914e+15, 2.06913e+15 to \
  7.94351e+15, 1.45518e+16 to \
  7.94351e+15, 1.45518e+16 to \
  7.94351e+15, 1.45518e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.06913e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 742 polygon from \
  -4.53914e+15, 2.14857e+15 to \
  7.94351e+15, 1.46313e+16 to \
  7.94351e+15, 1.46313e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.14857e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 743 polygon from \
  -4.53914e+15, 2.228e+15 to \
  7.94351e+15, 1.47107e+16 to \
  7.94351e+15, 1.47107e+16 to \
  7.94351e+15, 1.47107e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.228e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 744 polygon from \
  -4.53914e+15, 2.30744e+15 to \
  7.94351e+15, 1.47901e+16 to \
  7.94351e+15, 1.47901e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.30744e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 745 polygon from \
  -4.53914e+15, 2.38687e+15 to \
  7.94351e+15, 1.48696e+16 to \
  7.94351e+15, 1.48696e+16 to \
  7.94351e+15, 1.48696e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.38687e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 746 polygon from \
  -4.53914e+15, 2.46631e+15 to \
  7.94351e+15, 1.4949e+16 to \
  7.94351e+15, 1.4949e+16 to \
  7.94351e+15, 1.4949e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.46631e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 747 polygon from \
  -4.53914e+15, 2.54574e+15 to \
  7.94351e+15, 1.50284e+16 to \
  7.94351e+15, 1.50284e+16 to \
  7.94351e+15, 1.50284e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.54574e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 748 polygon from \
  -4.53914e+15, 2.62518e+15 to \
  7.94351e+15, 1.51079e+16 to \
  7.94351e+15, 1.51079e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.62518e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 749 polygon from \
  -4.53914e+15, 2.70461e+15 to \
  7.94351e+15, 1.51873e+16 to \
  7.94351e+15, 1.51873e+16 to \
  7.94351e+15, 1.51873e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.70461e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 750 polygon from \
  -4.53914e+15, 2.78405e+15 to \
  7.94351e+15, 1.52667e+16 to \
  7.94351e+15, 1.52667e+16 to \
  7.94351e+15, 1.52667e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.78405e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 751 polygon from \
  -4.53914e+15, 2.86348e+15 to \
  7.94351e+15, 1.53462e+16 to \
  7.94351e+15, 1.53462e+16 to \
  7.94351e+15, 1.53462e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.86348e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 752 polygon from \
  -4.53914e+15, 2.94292e+15 to \
  7.94351e+15, 1.54256e+16 to \
  7.94351e+15, 1.54256e+16 to \
  7.94351e+15, 1.54256e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.94292e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 753 polygon from \
  -4.53914e+15, 3.02235e+15 to \
  7.94351e+15, 1.5505e+16 to \
  7.94351e+15, 1.5505e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.02235e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 754 polygon from \
  -4.53914e+15, 3.10179e+15 to \
  7.94351e+15, 1.55845e+16 to \
  7.94351e+15, 1.55845e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.10179e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 755 polygon from \
  -4.53914e+15, 3.18122e+15 to \
  7.94351e+15, 1.56639e+16 to \
  7.94351e+15, 1.56639e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.18122e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 756 polygon from \
  -4.53914e+15, 3.26066e+15 to \
  7.94351e+15, 1.57433e+16 to \
  7.94351e+15, 1.57433e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.26066e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 757 polygon from \
  -4.53914e+15, 3.34009e+15 to \
  7.94351e+15, 1.58228e+16 to \
  7.94351e+15, 1.58228e+16 to \
  7.94351e+15, 1.58228e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.34009e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 758 polygon from \
  -4.53914e+15, 3.41953e+15 to \
  7.94351e+15, 1.59022e+16 to \
  7.94351e+15, 1.59022e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.41953e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 759 polygon from \
  -4.53914e+15, 3.49896e+15 to \
  7.94351e+15, 1.59817e+16 to \
  7.94351e+15, 1.59817e+16 to \
  7.94351e+15, 1.59817e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.49896e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 760 polygon from \
  -4.53914e+15, 3.5784e+15 to \
  7.94351e+15, 1.60611e+16 to \
  7.94351e+15, 1.60611e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.5784e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 761 polygon from \
  -4.53914e+15, 3.65783e+15 to \
  7.94351e+15, 1.61405e+16 to \
  7.94351e+15, 1.61405e+16 to \
  7.94351e+15, 1.61405e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.65783e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 762 polygon from \
  -4.53914e+15, 3.73727e+15 to \
  7.94351e+15, 1.622e+16 to \
  7.94351e+15, 1.622e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.73727e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 763 polygon from \
  -4.53914e+15, 3.8167e+15 to \
  7.94351e+15, 1.62994e+16 to \
  7.94351e+15, 1.62994e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.8167e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 764 polygon from \
  -4.53914e+15, 3.89614e+15 to \
  7.94351e+15, 1.63788e+16 to \
  7.94351e+15, 1.63788e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.89614e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 765 polygon from \
  -4.53914e+15, 3.97557e+15 to \
  7.94351e+15, 1.64583e+16 to \
  7.94351e+15, 1.64583e+16 to \
  7.94351e+15, 1.64583e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.97557e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 766 polygon from \
  -4.53914e+15, 4.05501e+15 to \
  7.94351e+15, 1.65377e+16 to \
  7.94351e+15, 1.65377e+16 to \
  7.94351e+15, 1.65377e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.05501e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 767 polygon from \
  -4.53914e+15, 4.13444e+15 to \
  7.94351e+15, 1.66171e+16 to \
  7.94351e+15, 1.66171e+16 to \
  7.94351e+15, 1.66171e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.13444e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 768 polygon from \
  -4.53914e+15, 4.21388e+15 to \
  7.94351e+15, 1.66966e+16 to \
  7.94351e+15, 1.66966e+16 to \
  7.94351e+15, 1.66966e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.21388e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 769 polygon from \
  -4.53914e+15, 4.29331e+15 to \
  7.94351e+15, 1.6776e+16 to \
  7.94351e+15, 1.6776e+16 to \
  7.94351e+15, 1.6776e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.29331e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 770 polygon from \
  -4.53914e+15, 4.37275e+15 to \
  7.94351e+15, 1.68554e+16 to \
  7.94351e+15, 1.68554e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.37275e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 771 polygon from \
  -4.53914e+15, 4.45218e+15 to \
  7.94351e+15, 1.69349e+16 to \
  7.94351e+15, 1.69349e+16 to \
  7.94351e+15, 1.69349e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.45218e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 772 polygon from \
  -4.53914e+15, 4.53162e+15 to \
  7.94351e+15, 1.70143e+16 to \
  7.94351e+15, 1.70143e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.53162e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 773 polygon from \
  -4.53914e+15, 4.61105e+15 to \
  7.94351e+15, 1.70937e+16 to \
  7.94351e+15, 1.70937e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.61105e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 774 polygon from \
  -4.53914e+15, 4.69049e+15 to \
  7.94351e+15, 1.71732e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.69049e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 775 polygon from \
  -4.53914e+15, 4.76992e+15 to \
  7.94351e+15, 1.72526e+16 to \
  7.94351e+15, 1.72526e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.76992e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 776 polygon from \
  -4.53914e+15, 4.84936e+15 to \
  7.94351e+15, 1.73321e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.84936e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 777 polygon from \
  -4.53914e+15, 4.92879e+15 to \
  7.94351e+15, 1.74115e+16 to \
  7.94351e+15, 1.74115e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.92879e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 778 polygon from \
  -4.53914e+15, 5.00823e+15 to \
  7.94351e+15, 1.74909e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.00823e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 779 polygon from \
  -4.53914e+15, 5.08766e+15 to \
  7.94351e+15, 1.75704e+16 to \
  7.94351e+15, 1.75704e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.08766e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 780 polygon from \
  -4.53914e+15, 5.1671e+15 to \
  7.94351e+15, 1.76498e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.1671e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 781 polygon from \
  -4.53914e+15, 5.24653e+15 to \
  7.94351e+15, 1.77292e+16 to \
  7.94351e+15, 1.77292e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.24653e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 782 polygon from \
  -4.53914e+15, 5.32597e+15 to \
  7.94351e+15, 1.78087e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.32597e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 783 polygon from \
  -4.53914e+15, 5.4054e+15 to \
  7.94351e+15, 1.78881e+16 to \
  7.94351e+15, 1.78881e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.4054e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 784 polygon from \
  -4.53914e+15, 5.48484e+15 to \
  7.94351e+15, 1.79675e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.48484e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 785 polygon from \
  -4.53914e+15, 5.56427e+15 to \
  7.94351e+15, 1.8047e+16 to \
  7.94351e+15, 1.8047e+16 to \
  7.94351e+15, 1.8047e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.56427e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 786 polygon from \
  -4.53914e+15, 5.64371e+15 to \
  7.94351e+15, 1.81264e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.64371e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 787 polygon from \
  -4.53914e+15, 5.72314e+15 to \
  7.94351e+15, 1.82058e+16 to \
  7.94351e+15, 1.82058e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.72314e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 788 polygon from \
  -4.53914e+15, 5.80258e+15 to \
  7.94351e+15, 1.82853e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.80258e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 789 polygon from \
  -4.53914e+15, 5.88201e+15 to \
  7.94351e+15, 1.83647e+16 to \
  7.94351e+15, 1.83647e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.88201e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 790 polygon from \
  -4.53914e+15, 5.96145e+15 to \
  7.94351e+15, 1.84441e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.96145e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 791 polygon from \
  -4.53914e+15, 6.04088e+15 to \
  7.94351e+15, 1.85236e+16 to \
  7.94351e+15, 1.85236e+16 to \
  7.94351e+15, 1.85236e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.04088e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 792 polygon from \
  -4.53914e+15, 6.12032e+15 to \
  7.94351e+15, 1.8603e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.12032e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 793 polygon from \
  -4.53914e+15, 6.19975e+15 to \
  7.94351e+15, 1.86824e+16 to \
  7.94351e+15, 1.86824e+16 to \
  7.94351e+15, 1.86824e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.19975e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 794 polygon from \
  -4.53914e+15, 6.27919e+15 to \
  7.94351e+15, 1.87619e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.27919e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 795 polygon from \
  -4.53914e+15, 6.35862e+15 to \
  7.94351e+15, 1.88413e+16 to \
  7.94351e+15, 1.88413e+16 to \
  7.94351e+15, 1.88413e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.35862e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 796 polygon from \
  -4.53914e+15, 6.43806e+15 to \
  7.94351e+15, 1.89208e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.43806e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 797 polygon from \
  -4.53914e+15, 6.51749e+15 to \
  7.94351e+15, 1.90002e+16 to \
  7.94351e+15, 1.90002e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.51749e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 798 polygon from \
  -4.53914e+15, 6.59693e+15 to \
  7.94351e+15, 1.90796e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.59693e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 799 polygon from \
  -4.53914e+15, 6.67636e+15 to \
  7.94351e+15, 1.91591e+16 to \
  7.94351e+15, 1.91591e+16 to \
  7.94351e+15, 1.91591e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.67636e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 800 polygon from \
  -4.53914e+15, 6.7558e+15 to \
  7.94351e+15, 1.92385e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.7558e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 801 polygon from \
  -4.53914e+15, 6.83523e+15 to \
  7.94351e+15, 1.93179e+16 to \
  7.94351e+15, 1.93179e+16 to \
  7.94351e+15, 1.93179e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.83523e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 802 polygon from \
  -4.53914e+15, 6.91467e+15 to \
  7.94351e+15, 1.93974e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.91467e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 803 polygon from \
  -4.53914e+15, 6.9941e+15 to \
  7.94351e+15, 1.94768e+16 to \
  7.94351e+15, 1.94768e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.9941e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 804 polygon from \
  -4.53914e+15, 7.07354e+15 to \
  7.94351e+15, 1.95562e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.07354e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 805 polygon from \
  -4.53914e+15, 7.15297e+15 to \
  7.94351e+15, 1.96357e+16 to \
  7.94351e+15, 1.96357e+16 to \
  7.94351e+15, 1.96357e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.15297e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 806 polygon from \
  -4.53914e+15, 7.23241e+15 to \
  7.94351e+15, 1.97151e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.23241e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 807 polygon from \
  -4.53914e+15, 7.31184e+15 to \
  7.94351e+15, 1.97945e+16 to \
  7.94351e+15, 1.97945e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.31184e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 808 polygon from \
  -4.53914e+15, 7.39128e+15 to \
  7.94351e+15, 1.9874e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.39128e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 809 polygon from \
  -4.53914e+15, 7.47071e+15 to \
  7.94351e+15, 1.99534e+16 to \
  7.94351e+15, 1.99534e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.47071e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 810 polygon from \
  -4.53914e+15, 7.55015e+15 to \
  7.94351e+15, 2.00328e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.55015e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 811 polygon from \
  -4.53914e+15, 7.62958e+15 to \
  7.94351e+15, 2.01123e+16 to \
  7.94351e+15, 2.01123e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.62958e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 812 polygon from \
  -4.53914e+15, 7.70902e+15 to \
  7.94351e+15, 2.01917e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.70902e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 813 polygon from \
  -4.53914e+15, 7.78845e+15 to \
  7.94351e+15, 2.02711e+16 to \
  7.94351e+15, 2.02711e+16 to \
  7.94351e+15, 2.02711e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.78845e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 814 polygon from \
  -4.53914e+15, 7.86789e+15 to \
  7.94351e+15, 2.03506e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.86789e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 815 polygon from \
  -4.53914e+15, 7.94732e+15 to \
  7.94351e+15, 2.043e+16 to \
  7.94351e+15, 2.043e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.94732e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 816 polygon from \
  -4.53914e+15, 8.02676e+15 to \
  7.94351e+15, 2.05095e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.02676e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 817 polygon from \
  -4.53914e+15, 8.10619e+15 to \
  7.94351e+15, 2.05889e+16 to \
  7.94351e+15, 2.05889e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.10619e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 818 polygon from \
  -4.53914e+15, 8.18563e+15 to \
  7.94351e+15, 2.06683e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.18563e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 819 polygon from \
  -4.53914e+15, 8.26506e+15 to \
  7.94351e+15, 2.07478e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.26506e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 820 polygon from \
  -4.53914e+15, 8.3445e+15 to \
  7.94351e+15, 2.08272e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.3445e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 821 polygon from \
  -4.53914e+15, 8.42393e+15 to \
  7.94351e+15, 2.09066e+16 to \
  7.94351e+15, 2.09066e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.42393e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 822 polygon from \
  -4.53914e+15, 8.50337e+15 to \
  7.94351e+15, 2.09861e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.50337e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 823 polygon from \
  -4.53914e+15, 8.5828e+15 to \
  7.94351e+15, 2.10655e+16 to \
  7.94351e+15, 2.10655e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.5828e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 824 polygon from \
  -4.53914e+15, 8.66224e+15 to \
  7.94351e+15, 2.11449e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.66224e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 825 polygon from \
  -4.53914e+15, 8.74167e+15 to \
  7.94351e+15, 2.12244e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.74167e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 826 polygon from \
  -4.53914e+15, 8.82111e+15 to \
  7.94351e+15, 2.13038e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.82111e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 827 polygon from \
  -4.53914e+15, 8.90054e+15 to \
  7.94351e+15, 2.13832e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.90054e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 828 polygon from \
  -4.53914e+15, 8.97998e+15 to \
  7.94351e+15, 2.14627e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.97998e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 829 polygon from \
  -4.53914e+15, 9.05941e+15 to \
  7.94351e+15, 2.15421e+16 to \
  7.94351e+15, 2.15421e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.05941e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 830 polygon from \
  -4.53914e+15, 9.13885e+15 to \
  7.94351e+15, 2.16215e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.13885e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 831 polygon from \
  -4.53914e+15, 9.21828e+15 to \
  7.94351e+15, 2.1701e+16 to \
  7.94351e+15, 2.1701e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.21828e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 832 polygon from \
  -4.53914e+15, 9.29772e+15 to \
  7.94351e+15, 2.17804e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.29772e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 833 polygon from \
  -4.53914e+15, 9.37715e+15 to \
  7.94351e+15, 2.18598e+16 to \
  7.94351e+15, 2.18598e+16 to \
  7.94351e+15, 2.18598e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.37715e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 834 polygon from \
  -4.53914e+15, 9.45659e+15 to \
  7.94351e+15, 2.19393e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.45659e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 835 polygon from \
  -4.53914e+15, 9.53602e+15 to \
  7.94351e+15, 2.20187e+16 to \
  7.94351e+15, 2.20187e+16 to \
  7.94351e+15, 2.20187e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.53602e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 836 polygon from \
  -4.53914e+15, 9.61546e+15 to \
  7.94351e+15, 2.20982e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.61546e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 837 polygon from \
  -4.53914e+15, 9.6949e+15 to \
  7.94351e+15, 2.21776e+16 to \
  7.94351e+15, 2.21776e+16 to \
  7.94351e+15, 2.21776e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.6949e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 838 polygon from \
  -4.53914e+15, 9.77433e+15 to \
  7.94351e+15, 2.2257e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.77433e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 839 polygon from \
  -4.53914e+15, 9.85377e+15 to \
  7.94351e+15, 2.23365e+16 to \
  7.94351e+15, 2.23365e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.85377e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 840 polygon from \
  -4.53914e+15, 9.9332e+15 to \
  7.94351e+15, 2.24159e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.9332e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 841 polygon from \
  -4.53914e+15, 1.00127e+16 to \
  7.94351e+15, 2.24953e+16 to \
  7.94351e+15, 2.24953e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.00127e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 842 polygon from \
  -4.53914e+15, 1.00921e+16 to \
  7.94351e+15, 2.25748e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.00921e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 843 polygon from \
  -4.53914e+15, 1.01716e+16 to \
  7.94351e+15, 2.26542e+16 to \
  7.94351e+15, 2.26542e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.01716e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 844 polygon from \
  -4.53914e+15, 1.0251e+16 to \
  7.94351e+15, 2.27336e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.0251e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 845 polygon from \
  -4.53914e+15, 1.03304e+16 to \
  7.94351e+15, 2.28131e+16 to \
  7.94351e+15, 2.28131e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03304e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 846 polygon from \
  -4.53914e+15, 1.04099e+16 to \
  7.94351e+15, 2.28925e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.04099e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 847 polygon from \
  -4.53914e+15, 1.04893e+16 to \
  7.94351e+15, 2.29719e+16 to \
  7.94351e+15, 2.29719e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.04893e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 848 polygon from \
  -4.53914e+15, 1.05687e+16 to \
  7.94351e+15, 2.30514e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.05687e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 849 polygon from \
  -4.53914e+15, 1.06482e+16 to \
  7.94351e+15, 2.31308e+16 to \
  7.94351e+15, 2.31308e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.06482e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 850 polygon from \
  -4.53914e+15, 1.07276e+16 to \
  7.94351e+15, 2.32102e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.07276e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 851 polygon from \
  -4.53914e+15, 1.0807e+16 to \
  7.94351e+15, 2.32897e+16 to \
  7.94351e+15, 2.32897e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.0807e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 852 polygon from \
  -4.53914e+15, 1.08865e+16 to \
  7.94351e+15, 2.33691e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.08865e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 853 polygon from \
  -4.53914e+15, 1.09659e+16 to \
  7.94351e+15, 2.34485e+16 to \
  7.94351e+15, 2.34485e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.09659e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 854 polygon from \
  -4.53914e+15, 1.10453e+16 to \
  7.94351e+15, 2.3528e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.10453e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 855 polygon from \
  -4.53914e+15, 1.11248e+16 to \
  7.94351e+15, 2.36074e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.11248e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 856 polygon from \
  -4.53914e+15, 1.12042e+16 to \
  7.94351e+15, 2.36869e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.12042e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 857 polygon from \
  -4.53914e+15, 1.12836e+16 to \
  7.94351e+15, 2.37663e+16 to \
  7.94351e+15, 2.37663e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.12836e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 858 polygon from \
  -4.53914e+15, 1.13631e+16 to \
  7.94351e+15, 2.38457e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.13631e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 859 polygon from \
  -4.53914e+15, 1.14425e+16 to \
  7.94351e+15, 2.39252e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.14425e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 860 polygon from \
  -4.53914e+15, 1.15219e+16 to \
  7.94351e+15, 2.40046e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.15219e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 861 polygon from \
  -4.53914e+15, 1.16014e+16 to \
  7.94351e+15, 2.4084e+16 to \
  7.94351e+15, 2.4084e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.16014e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 862 polygon from \
  -4.53914e+15, 1.16808e+16 to \
  7.94351e+15, 2.41635e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.16808e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 863 polygon from \
  -4.53914e+15, 1.17603e+16 to \
  7.94351e+15, 2.42429e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.17603e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 864 polygon from \
  -4.53914e+15, 1.18397e+16 to \
  7.94351e+15, 2.43223e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.18397e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 865 polygon from \
  -4.53914e+15, 1.19191e+16 to \
  7.94351e+15, 2.44018e+16 to \
  7.94351e+15, 2.44018e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19191e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 866 polygon from \
  -4.53914e+15, 1.19986e+16 to \
  7.94351e+15, 2.44812e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19986e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 867 polygon from \
  -4.53914e+15, 1.2078e+16 to \
  7.94351e+15, 2.45606e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.2078e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 868 polygon from \
  -4.53914e+15, 1.21574e+16 to \
  7.94351e+15, 2.46401e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.21574e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 869 polygon from \
  -4.53914e+15, 1.22369e+16 to \
  7.94351e+15, 2.47195e+16 to \
  7.94351e+15, 2.47195e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.22369e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 870 polygon from \
  -4.53914e+15, 1.23163e+16 to \
  7.94351e+15, 2.47989e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.23163e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 871 polygon from \
  -4.53914e+15, 1.23957e+16 to \
  7.94351e+15, 2.48784e+16 to \
  7.94351e+15, 2.48784e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.23957e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 872 polygon from \
  -4.53914e+15, 1.24752e+16 to \
  7.94351e+15, 2.49578e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.24752e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 873 polygon from \
  -4.53914e+15, 1.25546e+16 to \
  7.94351e+15, 2.50372e+16 to \
  7.94351e+15, 2.50372e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.25546e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 874 polygon from \
  -4.53914e+15, 1.2634e+16 to \
  7.94351e+15, 2.51167e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.2634e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 875 polygon from \
  -4.53914e+15, 1.27135e+16 to \
  7.94351e+15, 2.51961e+16 to \
  7.94351e+15, 2.51961e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27135e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 876 polygon from \
  -4.53914e+15, 1.27929e+16 to \
  7.94351e+15, 2.52756e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27929e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 877 polygon from \
  -4.53914e+15, 1.28723e+16 to \
  7.94351e+15, 2.5355e+16 to \
  7.94351e+15, 2.5355e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.28723e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 878 polygon from \
  -4.53914e+15, 1.29518e+16 to \
  7.94351e+15, 2.54344e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.29518e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 879 polygon from \
  -4.53914e+15, 1.30312e+16 to \
  7.94351e+15, 2.55139e+16 to \
  7.94351e+15, 2.55139e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.30312e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 880 polygon from \
  -4.53914e+15, 1.31106e+16 to \
  7.94351e+15, 2.55933e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.31106e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 881 polygon from \
  -4.53914e+15, 1.31901e+16 to \
  7.94351e+15, 2.56727e+16 to \
  7.94351e+15, 2.56727e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.31901e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 882 polygon from \
  -4.53914e+15, 1.32695e+16 to \
  7.94351e+15, 2.57522e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.32695e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 883 polygon from \
  -4.53914e+15, 1.3349e+16 to \
  7.94351e+15, 2.58316e+16 to \
  7.94351e+15, 2.58316e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.3349e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 884 polygon from \
  -4.53914e+15, 1.34284e+16 to \
  7.94351e+15, 2.5911e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.34284e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 885 polygon from \
  -4.53914e+15, 1.35078e+16 to \
  7.94351e+15, 2.59905e+16 to \
  7.94351e+15, 2.59905e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35078e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 886 polygon from \
  -4.53914e+15, 1.35873e+16 to \
  7.94351e+15, 2.60699e+16 to \
  7.94351e+15, 2.60699e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35873e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 887 polygon from \
  -4.53914e+15, 1.36667e+16 to \
  7.94351e+15, 2.61493e+16 to \
  7.94351e+15, 2.61493e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.36667e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 888 polygon from \
  -4.53914e+15, 1.37461e+16 to \
  7.94351e+15, 2.62288e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.37461e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 889 polygon from \
  -4.53914e+15, 1.38256e+16 to \
  7.94351e+15, 2.63082e+16 to \
  7.94351e+15, 2.63082e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.38256e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 890 polygon from \
  -4.53914e+15, 1.3905e+16 to \
  7.94351e+15, 2.63876e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.3905e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 891 polygon from \
  -4.53914e+15, 1.39844e+16 to \
  7.94351e+15, 2.64671e+16 to \
  7.94351e+15, 2.64671e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.39844e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 892 polygon from \
  -4.53914e+15, 1.40639e+16 to \
  7.94351e+15, 2.65465e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.40639e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 893 polygon from \
  -4.53914e+15, 1.41433e+16 to \
  7.94351e+15, 2.66259e+16 to \
  7.94351e+15, 2.66259e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.41433e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 894 polygon from \
  -4.53914e+15, 1.42227e+16 to \
  7.94351e+15, 2.67054e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.42227e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 895 polygon from \
  -4.53914e+15, 1.43022e+16 to \
  7.94351e+15, 2.67848e+16 to \
  7.94351e+15, 2.67848e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.43022e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 896 polygon from \
  -4.53914e+15, 1.43816e+16 to \
  7.94351e+15, 2.68643e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.43816e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 897 polygon from \
  -4.53914e+15, 1.4461e+16 to \
  7.94351e+15, 2.69437e+16 to \
  7.94351e+15, 2.69437e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.4461e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 898 polygon from \
  -4.53914e+15, 1.45405e+16 to \
  7.94351e+15, 2.70231e+16 to \
  7.94351e+15, 2.70231e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.45405e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 899 polygon from \
  -4.53914e+15, 1.46199e+16 to \
  7.94351e+15, 2.71026e+16 to \
  7.94351e+15, 2.71026e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.46199e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 900 polygon from \
  -4.53914e+15, 1.46993e+16 to \
  7.94351e+15, 2.7182e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.46993e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 901 polygon from \
  -4.53914e+15, 3.43088e+15 to \
  7.94351e+15, 3.43088e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.43088e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 902 polygon from \
  -4.53914e+15, 3.35144e+15 to \
  -4.38027e+15, 3.51031e+15 to \
  7.94351e+15, 3.51031e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.35144e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 903 polygon from \
  -4.53914e+15, 3.30605e+15 to \
  -4.25544e+15, 3.58975e+15 to \
  7.94351e+15, 3.58975e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.30605e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 904 polygon from \
  -4.53914e+15, 3.26066e+15 to \
  -4.13062e+15, 3.66918e+15 to \
  7.94351e+15, 3.66918e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.26066e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 905 polygon from \
  -4.53914e+15, 3.21527e+15 to \
  -4.00579e+15, 3.74862e+15 to \
  7.94351e+15, 3.74862e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.21527e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 906 polygon from \
  -4.53914e+15, 3.16988e+15 to \
  -3.88096e+15, 3.82805e+15 to \
  7.94351e+15, 3.82805e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.16988e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 907 polygon from \
  -4.53914e+15, 3.12448e+15 to \
  -3.75614e+15, 3.90749e+15 to \
  7.94351e+15, 3.90749e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.12448e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 908 polygon from \
  -4.53914e+15, 3.07909e+15 to \
  -3.63131e+15, 3.98692e+15 to \
  7.94351e+15, 3.98692e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.07909e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 909 polygon from \
  -4.53914e+15, 3.0337e+15 to \
  -3.50648e+15, 4.06636e+15 to \
  7.94351e+15, 4.06636e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.0337e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 910 polygon from \
  -4.53914e+15, 2.98831e+15 to \
  -3.38166e+15, 4.14579e+15 to \
  7.94351e+15, 4.14579e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.98831e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 911 polygon from \
  -4.53914e+15, 2.94292e+15 to \
  -3.25683e+15, 4.22523e+15 to \
  7.94351e+15, 4.22523e+15 to \
  7.94351e+15, 4.22523e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.94292e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 912 polygon from \
  -4.53914e+15, 2.89753e+15 to \
  -3.132e+15, 4.30466e+15 to \
  7.94351e+15, 4.30466e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.89753e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 913 polygon from \
  -4.53914e+15, 2.85214e+15 to \
  -3.00718e+15, 4.3841e+15 to \
  7.94351e+15, 4.3841e+15 to \
  7.94351e+15, 4.3841e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.85214e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 914 polygon from \
  -4.53914e+15, 2.80674e+15 to \
  -2.88235e+15, 4.46353e+15 to \
  7.94351e+15, 4.46353e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.80674e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 915 polygon from \
  -4.53914e+15, 2.76135e+15 to \
  -2.75753e+15, 4.54297e+15 to \
  7.94351e+15, 4.54297e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.76135e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 916 polygon from \
  -4.53914e+15, 2.71596e+15 to \
  -2.6327e+15, 4.6224e+15 to \
  7.94351e+15, 4.6224e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.71596e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 917 polygon from \
  -4.53914e+15, 2.67057e+15 to \
  -2.50787e+15, 4.70184e+15 to \
  7.94351e+15, 4.70184e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.67057e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 918 polygon from \
  -4.53914e+15, 2.62518e+15 to \
  -2.38305e+15, 4.78127e+15 to \
  7.94351e+15, 4.78127e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.62518e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 919 polygon from \
  -4.53914e+15, 2.57979e+15 to \
  -2.25822e+15, 4.86071e+15 to \
  7.94351e+15, 4.86071e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.57979e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 920 polygon from \
  -4.53914e+15, 2.5344e+15 to \
  -2.13339e+15, 4.94014e+15 to \
  7.94351e+15, 4.94014e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.5344e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 921 polygon from \
  -4.53914e+15, 2.489e+15 to \
  -2.00857e+15, 5.01958e+15 to \
  7.94351e+15, 5.01958e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.489e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 922 polygon from \
  -4.53914e+15, 2.44361e+15 to \
  -1.88374e+15, 5.09901e+15 to \
  7.94351e+15, 5.09901e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.44361e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 923 polygon from \
  -4.53914e+15, 2.39822e+15 to \
  -1.75891e+15, 5.17845e+15 to \
  7.94351e+15, 5.17845e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.39822e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 924 polygon from \
  -4.53914e+15, 2.35283e+15 to \
  -1.63409e+15, 5.25788e+15 to \
  7.94351e+15, 5.25788e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.35283e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 925 polygon from \
  -4.53914e+15, 2.30744e+15 to \
  -1.50926e+15, 5.33732e+15 to \
  7.94351e+15, 5.33732e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.30744e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 926 polygon from \
  -4.53914e+15, 2.26205e+15 to \
  -1.38443e+15, 5.41675e+15 to \
  7.94351e+15, 5.41675e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.26205e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 927 polygon from \
  -4.53914e+15, 2.21665e+15 to \
  -1.25961e+15, 5.49619e+15 to \
  7.94351e+15, 5.49619e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.21665e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 928 polygon from \
  -4.53914e+15, 2.17126e+15 to \
  -1.13478e+15, 5.57562e+15 to \
  7.94351e+15, 5.57562e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.17126e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 929 polygon from \
  -4.53914e+15, 2.12587e+15 to \
  -1.00995e+15, 5.65506e+15 to \
  7.94351e+15, 5.65506e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.12587e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 930 polygon from \
  -4.53914e+15, 2.08048e+15 to \
  -8.85133e+14, 5.73449e+15 to \
  7.94351e+15, 5.73449e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.08048e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 931 polygon from \
  -4.53914e+15, 2.03509e+15 to \
  -7.60306e+14, 5.81393e+15 to \
  7.94351e+15, 5.81393e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.03509e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 932 polygon from \
  -4.53914e+15, 1.9897e+15 to \
  -6.3548e+14, 5.89336e+15 to \
  7.94351e+15, 5.89336e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.9897e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 933 polygon from \
  -4.53914e+15, 1.94431e+15 to \
  -5.10653e+14, 5.9728e+15 to \
  7.94351e+15, 5.9728e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.94431e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 934 polygon from \
  -4.53914e+15, 1.89891e+15 to \
  -3.85827e+14, 6.05223e+15 to \
  7.94351e+15, 6.05223e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.89891e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 935 polygon from \
  -4.53914e+15, 1.85352e+15 to \
  -2.61e+14, 6.13167e+15 to \
  7.94351e+15, 6.13167e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.85352e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 936 polygon from \
  -4.53914e+15, 1.80813e+15 to \
  -1.36174e+14, 6.2111e+15 to \
  7.94351e+15, 6.2111e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.80813e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 937 polygon from \
  -4.53914e+15, 1.76274e+15 to \
  -1.13478e+13, 6.29054e+15 to \
  7.94351e+15, 6.29054e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.76274e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 938 polygon from \
  -4.53914e+15, 1.71735e+15 to \
  1.13479e+14, 6.36997e+15 to \
  7.94351e+15, 6.36997e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.71735e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 939 polygon from \
  -4.53914e+15, 1.67196e+15 to \
  2.38306e+14, 6.44941e+15 to \
  7.94351e+15, 6.44941e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.67196e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 940 polygon from \
  -4.53914e+15, 1.62657e+15 to \
  3.63132e+14, 6.52884e+15 to \
  7.94351e+15, 6.52884e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.62657e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 941 polygon from \
  -4.53914e+15, 1.58117e+15 to \
  4.87959e+14, 6.60828e+15 to \
  7.94351e+15, 6.60828e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.58117e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 942 polygon from \
  -4.53914e+15, 1.53578e+15 to \
  6.12785e+14, 6.68771e+15 to \
  7.94351e+15, 6.68771e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.53578e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 943 polygon from \
  -4.53914e+15, 1.49039e+15 to \
  7.37611e+14, 6.76715e+15 to \
  7.94351e+15, 6.76715e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.49039e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 944 polygon from \
  -4.53914e+15, 1.445e+15 to \
  8.62438e+14, 6.84658e+15 to \
  7.94351e+15, 6.84658e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.445e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 945 polygon from \
  -4.53914e+15, 1.39961e+15 to \
  9.87264e+14, 6.92602e+15 to \
  7.94351e+15, 6.92602e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.39961e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 946 polygon from \
  -4.53914e+15, 1.35422e+15 to \
  1.1121e+15, 7.00545e+15 to \
  7.94351e+15, 7.00545e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35422e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 947 polygon from \
  -4.53914e+15, 1.30883e+15 to \
  1.23692e+15, 7.08489e+15 to \
  7.94351e+15, 7.08489e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.30883e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 948 polygon from \
  -4.53914e+15, 1.26343e+15 to \
  1.36175e+15, 7.16432e+15 to \
  7.94351e+15, 7.16432e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.26343e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 949 polygon from \
  -4.53914e+15, 1.21804e+15 to \
  1.48657e+15, 7.24376e+15 to \
  7.94351e+15, 7.24376e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.21804e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 950 polygon from \
  -4.53914e+15, 1.17265e+15 to \
  1.6114e+15, 7.32319e+15 to \
  7.94351e+15, 7.32319e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.17265e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 951 polygon from \
  -4.53914e+15, 1.12726e+15 to \
  1.73623e+15, 7.40263e+15 to \
  7.94351e+15, 7.40263e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.12726e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 952 polygon from \
  -4.53914e+15, 1.08187e+15 to \
  1.86105e+15, 7.48206e+15 to \
  7.94351e+15, 7.48206e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.08187e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 953 polygon from \
  -4.53914e+15, 1.03648e+15 to \
  1.98588e+15, 7.5615e+15 to \
  7.94351e+15, 7.5615e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03648e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 954 polygon from \
  -4.53914e+15, 9.91082e+14 to \
  2.11071e+15, 7.64093e+15 to \
  7.94351e+15, 7.64093e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.91082e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 955 polygon from \
  -4.53914e+15, 9.4569e+14 to \
  2.23553e+15, 7.72037e+15 to \
  7.94351e+15, 7.72037e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.4569e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 956 polygon from \
  -4.53914e+15, 9.00299e+14 to \
  2.36036e+15, 7.7998e+15 to \
  7.94351e+15, 7.7998e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.00299e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 957 polygon from \
  -4.53914e+15, 8.54907e+14 to \
  2.48519e+15, 7.87924e+15 to \
  7.94351e+15, 7.87924e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.54907e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 958 polygon from \
  -4.53914e+15, 8.09516e+14 to \
  2.61001e+15, 7.95867e+15 to \
  7.94351e+15, 7.95867e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.09516e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 959 polygon from \
  -4.53914e+15, 7.64124e+14 to \
  2.73484e+15, 8.03811e+15 to \
  7.94351e+15, 8.03811e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.64124e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 960 polygon from \
  -4.53914e+15, 7.18733e+14 to \
  2.85967e+15, 8.11754e+15 to \
  7.94351e+15, 8.11754e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.18733e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 961 polygon from \
  -4.53914e+15, 6.73341e+14 to \
  2.98449e+15, 8.19698e+15 to \
  7.94351e+15, 8.19698e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.73341e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 962 polygon from \
  -4.53914e+15, 6.2795e+14 to \
  3.10932e+15, 8.27641e+15 to \
  7.94351e+15, 8.27641e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.2795e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 963 polygon from \
  -4.53914e+15, 5.82559e+14 to \
  3.23415e+15, 8.35585e+15 to \
  7.94351e+15, 8.35585e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.82559e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 964 polygon from \
  -4.53914e+15, 5.37167e+14 to \
  3.35897e+15, 8.43528e+15 to \
  7.94351e+15, 8.43528e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.37167e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 965 polygon from \
  -4.53914e+15, 4.91776e+14 to \
  3.4838e+15, 8.51472e+15 to \
  7.94351e+15, 8.51472e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.91776e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 966 polygon from \
  -4.53914e+15, 4.46384e+14 to \
  3.60862e+15, 8.59415e+15 to \
  7.94351e+15, 8.59415e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.46384e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 967 polygon from \
  -4.53914e+15, 4.00993e+14 to \
  3.73345e+15, 8.67359e+15 to \
  7.94351e+15, 8.67359e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.00993e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 968 polygon from \
  -4.53914e+15, 3.55601e+14 to \
  3.85828e+15, 8.75302e+15 to \
  7.94351e+15, 8.75302e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.55601e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 969 polygon from \
  -4.53914e+15, 3.1021e+14 to \
  3.9831e+15, 8.83246e+15 to \
  7.94351e+15, 8.83246e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.1021e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 970 polygon from \
  -4.53914e+15, 2.64818e+14 to \
  4.10793e+15, 8.91189e+15 to \
  7.94351e+15, 8.91189e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.64818e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 971 polygon from \
  -4.53914e+15, 2.19427e+14 to \
  4.23276e+15, 8.99133e+15 to \
  7.94351e+15, 8.99133e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.19427e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 972 polygon from \
  -4.53914e+15, 1.74036e+14 to \
  4.35758e+15, 9.07076e+15 to \
  7.94351e+15, 9.07076e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.74036e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 973 polygon from \
  -4.53914e+15, 1.28644e+14 to \
  4.48241e+15, 9.1502e+15 to \
  7.94351e+15, 9.1502e+15 to \
  7.94351e+15, 9.1502e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.28644e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 974 polygon from \
  -4.53914e+15, 8.32523e+13 to \
  4.60724e+15, 9.22963e+15 to \
  7.94351e+15, 9.22963e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.32523e+13 front fs empty border lc rgb '#6165' lw 0.200001
set object 975 polygon from \
  -4.53914e+15, 3.78608e+13 to \
  4.73206e+15, 9.30907e+15 to \
  7.94351e+15, 9.30907e+15 to \
  7.94351e+15, 9.30907e+15 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.78608e+13 front fs empty border lc rgb '#6165' lw 0.200001
set object 976 polygon from \
  4.85689e+15, 9.3885e+15 to \
  7.94351e+15, 9.3885e+15 to \
  7.94351e+15, 0 to \
  -4.53161e+15, -0 to \
  4.85689e+15, 9.3885e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 977 polygon from \
  4.98172e+15, 9.46794e+15 to \
  7.94351e+15, 9.46794e+15 to \
  7.94351e+15, 9.46794e+15 to \
  7.94351e+15, 0 to \
  -4.48622e+15, -0 to \
  4.98172e+15, 9.46794e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 978 polygon from \
  5.10654e+15, 9.54737e+15 to \
  7.94351e+15, 9.54737e+15 to \
  7.94351e+15, 0 to \
  -4.44083e+15, -0 to \
  5.10654e+15, 9.54737e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 979 polygon from \
  5.23137e+15, 9.62681e+15 to \
  7.94351e+15, 9.62681e+15 to \
  7.94351e+15, 0 to \
  -4.39543e+15, -0 to \
  5.23137e+15, 9.62681e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 980 polygon from \
  5.3562e+15, 9.70624e+15 to \
  7.94351e+15, 9.70624e+15 to \
  7.94351e+15, 0 to \
  -4.35004e+15, -0 to \
  5.3562e+15, 9.70624e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 981 polygon from \
  5.48102e+15, 9.78568e+15 to \
  7.94351e+15, 9.78568e+15 to \
  7.94351e+15, 0 to \
  -4.30465e+15, -0 to \
  5.48102e+15, 9.78568e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 982 polygon from \
  5.60585e+15, 9.86511e+15 to \
  7.94351e+15, 9.86511e+15 to \
  7.94351e+15, 9.86511e+15 to \
  7.94351e+15, 0 to \
  -4.25926e+15, -0 to \
  5.60585e+15, 9.86511e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 983 polygon from \
  5.73067e+15, 9.94455e+15 to \
  7.94351e+15, 9.94455e+15 to \
  7.94351e+15, 0 to \
  -4.21387e+15, -0 to \
  5.73067e+15, 9.94455e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 984 polygon from \
  5.8555e+15, 1.0024e+16 to \
  7.94351e+15, 1.0024e+16 to \
  7.94351e+15, 1.0024e+16 to \
  7.94351e+15, 0 to \
  -4.16848e+15, -0 to \
  5.8555e+15, 1.0024e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 985 polygon from \
  5.98033e+15, 1.01035e+16 to \
  7.94351e+15, 1.01035e+16 to \
  7.94351e+15, 1.01035e+16 to \
  7.94351e+15, 0 to \
  -4.12309e+15, -0 to \
  5.98033e+15, 1.01035e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 986 polygon from \
  6.10515e+15, 1.01829e+16 to \
  7.94351e+15, 1.01829e+16 to \
  7.94351e+15, 1.01829e+16 to \
  7.94351e+15, 0 to \
  -4.07769e+15, -0 to \
  6.10515e+15, 1.01829e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 987 polygon from \
  6.22998e+15, 1.02623e+16 to \
  7.94351e+15, 1.02623e+16 to \
  7.94351e+15, 1.02623e+16 to \
  7.94351e+15, 3.77571e+13 to \
  7.90575e+15, -0 to \
  -4.0323e+15, -0 to \
  6.22998e+15, 1.02623e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 988 polygon from \
  6.35481e+15, 1.03418e+16 to \
  7.94351e+15, 1.03418e+16 to \
  7.94351e+15, 1.03418e+16 to \
  7.94351e+15, 1.17193e+14 to \
  7.82632e+15, -0 to \
  -3.98691e+15, -0 to \
  6.35481e+15, 1.03418e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 989 polygon from \
  6.47963e+15, 1.04212e+16 to \
  7.94351e+15, 1.04212e+16 to \
  7.94351e+15, 1.04212e+16 to \
  7.94351e+15, 1.96628e+14 to \
  7.74688e+15, -0 to \
  -3.94152e+15, -0 to \
  6.47963e+15, 1.04212e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 990 polygon from \
  6.60446e+15, 1.05006e+16 to \
  7.94351e+15, 1.05006e+16 to \
  7.94351e+15, 1.05006e+16 to \
  7.94351e+15, 2.76063e+14 to \
  7.66745e+15, -0 to \
  -3.89613e+15, -0 to \
  6.60446e+15, 1.05006e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 991 polygon from \
  6.72929e+15, 1.05801e+16 to \
  7.94351e+15, 1.05801e+16 to \
  7.94351e+15, 1.05801e+16 to \
  7.94351e+15, 3.55498e+14 to \
  7.58801e+15, -0 to \
  -3.85074e+15, -0 to \
  6.72929e+15, 1.05801e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 992 polygon from \
  6.85411e+15, 1.06595e+16 to \
  7.94351e+15, 1.06595e+16 to \
  7.94351e+15, 1.06595e+16 to \
  7.94351e+15, 4.34933e+14 to \
  7.50858e+15, -0 to \
  -3.80535e+15, -0 to \
  6.85411e+15, 1.06595e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 993 polygon from \
  6.97894e+15, 1.07389e+16 to \
  7.94351e+15, 1.07389e+16 to \
  7.94351e+15, 1.07389e+16 to \
  7.94351e+15, 5.14368e+14 to \
  7.42914e+15, -0 to \
  -3.75995e+15, -0 to \
  6.97894e+15, 1.07389e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 994 polygon from \
  7.10377e+15, 1.08184e+16 to \
  7.94351e+15, 1.08184e+16 to \
  7.94351e+15, 1.08184e+16 to \
  7.94351e+15, 5.93803e+14 to \
  7.34971e+15, -0 to \
  -3.71456e+15, -0 to \
  7.10377e+15, 1.08184e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 995 polygon from \
  7.22859e+15, 1.08978e+16 to \
  7.94351e+15, 1.08978e+16 to \
  7.94351e+15, 1.08978e+16 to \
  7.94351e+15, 6.73238e+14 to \
  7.27027e+15, -0 to \
  -3.66917e+15, -0 to \
  7.22859e+15, 1.08978e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 996 polygon from \
  7.35342e+15, 1.09772e+16 to \
  7.94351e+15, 1.09772e+16 to \
  7.94351e+15, 1.09772e+16 to \
  7.94351e+15, 7.52673e+14 to \
  7.19084e+15, -0 to \
  -3.62378e+15, -0 to \
  7.35342e+15, 1.09772e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 997 polygon from \
  7.47825e+15, 1.10567e+16 to \
  7.94351e+15, 1.10567e+16 to \
  7.94351e+15, 1.10567e+16 to \
  7.94351e+15, 8.32108e+14 to \
  7.1114e+15, -0 to \
  -3.57839e+15, -0 to \
  7.47825e+15, 1.10567e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 998 polygon from \
  7.60307e+15, 1.11361e+16 to \
  7.94351e+15, 1.11361e+16 to \
  7.94351e+15, 1.11361e+16 to \
  7.94351e+15, 9.11543e+14 to \
  7.03197e+15, -0 to \
  -3.533e+15, -0 to \
  7.60307e+15, 1.11361e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 999 polygon from \
  7.7279e+15, 1.12156e+16 to \
  7.94351e+15, 1.12156e+16 to \
  7.94351e+15, 1.12156e+16 to \
  7.94351e+15, 9.90978e+14 to \
  6.95253e+15, -0 to \
  -3.48761e+15, -0 to \
  7.7279e+15, 1.12156e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1000 polygon from \
  7.85272e+15, 1.1295e+16 to \
  7.94351e+15, 1.1295e+16 to \
  7.94351e+15, 1.1295e+16 to \
  7.94351e+15, 1.07042e+15 to \
  6.87309e+15, -0 to \
  -3.44221e+15, -0 to \
  7.85272e+15, 1.1295e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1001 polygon from \
  7.94351e+15, 1.13744e+16 to \
  7.94351e+15, 1.13744e+16 to \
  7.94351e+15, 1.13744e+16 to \
  7.94351e+15, 1.14985e+15 to \
  6.79366e+15, -0 to \
  -3.43087e+15, -0 to \
  7.94351e+15, 1.13744e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1002 polygon from \
  7.94351e+15, 1.14539e+16 to \
  7.94351e+15, 1.14539e+16 to \
  7.94351e+15, 1.14539e+16 to \
  7.94351e+15, 1.10446e+15 to \
  6.83905e+15, -0 to \
  -3.5103e+15, -0 to \
  7.94351e+15, 1.14539e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1003 polygon from \
  7.94351e+15, 1.15333e+16 to \
  7.94351e+15, 1.15333e+16 to \
  7.94351e+15, 1.15333e+16 to \
  7.94351e+15, 1.05907e+15 to \
  6.88444e+15, -0 to \
  -3.58974e+15, -0 to \
  7.94351e+15, 1.15333e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1004 polygon from \
  7.94351e+15, 1.16127e+16 to \
  7.94351e+15, 1.16127e+16 to \
  7.94351e+15, 1.01368e+15 to \
  6.92983e+15, -0 to \
  -3.66917e+15, -0 to \
  7.94351e+15, 1.16127e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1005 polygon from \
  7.94351e+15, 1.16922e+16 to \
  7.94351e+15, 1.16922e+16 to \
  7.94351e+15, 1.16922e+16 to \
  7.94351e+15, 9.68282e+14 to \
  6.97523e+15, -0 to \
  -3.74861e+15, -0 to \
  7.94351e+15, 1.16922e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1006 polygon from \
  7.94351e+15, 1.17716e+16 to \
  7.94351e+15, 1.17716e+16 to \
  7.94351e+15, 1.17716e+16 to \
  7.94351e+15, 9.22891e+14 to \
  7.02062e+15, -0 to \
  -3.82804e+15, -0 to \
  7.94351e+15, 1.17716e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1007 polygon from \
  7.94351e+15, 1.1851e+16 to \
  7.94351e+15, 1.1851e+16 to \
  7.94351e+15, 1.1851e+16 to \
  7.94351e+15, 8.77499e+14 to \
  7.06601e+15, -0 to \
  -3.90748e+15, -0 to \
  7.94351e+15, 1.1851e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1008 polygon from \
  7.94351e+15, 1.19305e+16 to \
  7.94351e+15, 1.19305e+16 to \
  7.94351e+15, 8.32108e+14 to \
  7.1114e+15, -0 to \
  -3.98691e+15, -0 to \
  7.94351e+15, 1.19305e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1009 polygon from \
  7.94351e+15, 1.20099e+16 to \
  7.94351e+15, 1.20099e+16 to \
  7.94351e+15, 7.86716e+14 to \
  7.15679e+15, -0 to \
  -4.06635e+15, -0 to \
  7.94351e+15, 1.20099e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1010 polygon from \
  7.94351e+15, 1.20893e+16 to \
  7.94351e+15, 1.20893e+16 to \
  7.94351e+15, 7.41325e+14 to \
  7.20218e+15, -0 to \
  -4.14578e+15, -0 to \
  7.94351e+15, 1.20893e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1011 polygon from \
  7.94351e+15, 1.21688e+16 to \
  7.94351e+15, 1.21688e+16 to \
  7.94351e+15, 1.21688e+16 to \
  7.94351e+15, 6.95933e+14 to \
  7.24757e+15, -0 to \
  -4.22522e+15, -0 to \
  7.94351e+15, 1.21688e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1012 polygon from \
  7.94351e+15, 1.22482e+16 to \
  7.94351e+15, 1.22482e+16 to \
  7.94351e+15, 1.22482e+16 to \
  7.94351e+15, 6.50542e+14 to \
  7.29297e+15, -0 to \
  -4.30465e+15, -0 to \
  7.94351e+15, 1.22482e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1013 polygon from \
  7.94351e+15, 1.23276e+16 to \
  7.94351e+15, 1.23276e+16 to \
  7.94351e+15, 6.05151e+14 to \
  7.33836e+15, -0 to \
  -4.38409e+15, -0 to \
  7.94351e+15, 1.23276e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1014 polygon from \
  7.94351e+15, 1.24071e+16 to \
  7.94351e+15, 1.24071e+16 to \
  7.94351e+15, 1.24071e+16 to \
  7.94351e+15, 5.59759e+14 to \
  7.38375e+15, -0 to \
  -4.46352e+15, -0 to \
  7.94351e+15, 1.24071e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1015 polygon from \
  -4.53914e+15, 3.81718e+12 to \
  7.94351e+15, 1.24865e+16 to \
  7.94351e+15, 1.24865e+16 to \
  7.94351e+15, 1.24865e+16 to \
  7.94351e+15, 5.14368e+14 to \
  7.42914e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.81718e+12 front fs empty border lc rgb '#6165' lw 0.200001
set object 1016 polygon from \
  -4.53914e+15, 8.32523e+13 to \
  7.94351e+15, 1.25659e+16 to \
  7.94351e+15, 1.25659e+16 to \
  7.94351e+15, 1.25659e+16 to \
  7.94351e+15, 4.68976e+14 to \
  7.47453e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.32523e+13 front fs empty border lc rgb '#6165' lw 0.200001
set object 1017 polygon from \
  -4.53914e+15, 1.62688e+14 to \
  7.94351e+15, 1.26454e+16 to \
  7.94351e+15, 1.26454e+16 to \
  7.94351e+15, 1.26454e+16 to \
  7.94351e+15, 4.23585e+14 to \
  7.51992e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.62688e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1018 polygon from \
  -4.53914e+15, 2.42123e+14 to \
  7.94351e+15, 1.27248e+16 to \
  7.94351e+15, 1.27248e+16 to \
  7.94351e+15, 3.78193e+14 to \
  7.56531e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.42123e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1019 polygon from \
  -4.53914e+15, 3.21558e+14 to \
  7.94351e+15, 1.28043e+16 to \
  7.94351e+15, 1.28043e+16 to \
  7.94351e+15, 3.32802e+14 to \
  7.61071e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.21558e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1020 polygon from \
  -4.53914e+15, 4.00993e+14 to \
  7.94351e+15, 1.28837e+16 to \
  7.94351e+15, 1.28837e+16 to \
  7.94351e+15, 1.28837e+16 to \
  7.94351e+15, 2.87411e+14 to \
  7.6561e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.00993e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1021 polygon from \
  -4.53914e+15, 4.80428e+14 to \
  7.94351e+15, 1.29631e+16 to \
  7.94351e+15, 1.29631e+16 to \
  7.94351e+15, 1.29631e+16 to \
  7.94351e+15, 2.42019e+14 to \
  7.70149e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.80428e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1022 polygon from \
  -4.53914e+15, 5.59863e+14 to \
  7.94351e+15, 1.30426e+16 to \
  7.94351e+15, 1.30426e+16 to \
  7.94351e+15, 1.30426e+16 to \
  7.94351e+15, 1.96628e+14 to \
  7.74688e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.59863e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1023 polygon from \
  -4.53914e+15, 6.39298e+14 to \
  7.94351e+15, 1.3122e+16 to \
  7.94351e+15, 1.3122e+16 to \
  7.94351e+15, 1.3122e+16 to \
  7.94351e+15, 1.51236e+14 to \
  7.79227e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.39298e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1024 polygon from \
  -4.53914e+15, 7.18733e+14 to \
  7.94351e+15, 1.32014e+16 to \
  7.94351e+15, 1.32014e+16 to \
  7.94351e+15, 1.05845e+14 to \
  7.83766e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.18733e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1025 polygon from \
  -4.53914e+15, 7.98168e+14 to \
  7.94351e+15, 1.32809e+16 to \
  7.94351e+15, 1.32809e+16 to \
  7.94351e+15, 1.32809e+16 to \
  7.94351e+15, 6.04529e+13 to \
  7.88305e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.98168e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1026 polygon from \
  -4.53914e+15, 8.77603e+14 to \
  7.94351e+15, 1.33603e+16 to \
  7.94351e+15, 1.33603e+16 to \
  7.94351e+15, 1.33603e+16 to \
  7.94351e+15, 1.50614e+13 to \
  7.92845e+15, -0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.77603e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1027 polygon from \
  -4.53914e+15, 9.57038e+14 to \
  7.94351e+15, 1.34397e+16 to \
  7.94351e+15, 1.34397e+16 to \
  7.94351e+15, 1.34397e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.57038e+14 front fs empty border lc rgb '#6165' lw 0.200001
set object 1028 polygon from \
  -4.53914e+15, 1.03648e+15 to \
  7.94351e+15, 1.35192e+16 to \
  7.94351e+15, 1.35192e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03648e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1029 polygon from \
  -4.53914e+15, 1.11591e+15 to \
  7.94351e+15, 1.35986e+16 to \
  7.94351e+15, 1.35986e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.11591e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1030 polygon from \
  -4.53914e+15, 1.19535e+15 to \
  7.94351e+15, 1.3678e+16 to \
  7.94351e+15, 1.3678e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19535e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1031 polygon from \
  -4.53914e+15, 1.27478e+15 to \
  7.94351e+15, 1.37575e+16 to \
  7.94351e+15, 1.37575e+16 to \
  7.94351e+15, 1.37575e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27478e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1032 polygon from \
  -4.53914e+15, 1.35422e+15 to \
  7.94351e+15, 1.38369e+16 to \
  7.94351e+15, 1.38369e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35422e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1033 polygon from \
  -4.53914e+15, 1.43365e+15 to \
  7.94351e+15, 1.39163e+16 to \
  7.94351e+15, 1.39163e+16 to \
  7.94351e+15, 1.39163e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.43365e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1034 polygon from \
  -4.53914e+15, 1.51309e+15 to \
  7.94351e+15, 1.39958e+16 to \
  7.94351e+15, 1.39958e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.51309e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1035 polygon from \
  -4.53914e+15, 1.59252e+15 to \
  7.94351e+15, 1.40752e+16 to \
  7.94351e+15, 1.40752e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.59252e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1036 polygon from \
  -4.53914e+15, 1.67196e+15 to \
  7.94351e+15, 1.41546e+16 to \
  7.94351e+15, 1.41546e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.67196e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1037 polygon from \
  -4.53914e+15, 1.75139e+15 to \
  7.94351e+15, 1.42341e+16 to \
  7.94351e+15, 1.42341e+16 to \
  7.94351e+15, 1.42341e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.75139e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1038 polygon from \
  -4.53914e+15, 1.83083e+15 to \
  7.94351e+15, 1.43135e+16 to \
  7.94351e+15, 1.43135e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.83083e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1039 polygon from \
  -4.53914e+15, 1.91026e+15 to \
  7.94351e+15, 1.4393e+16 to \
  7.94351e+15, 1.4393e+16 to \
  7.94351e+15, 1.4393e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.91026e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1040 polygon from \
  -4.53914e+15, 1.9897e+15 to \
  7.94351e+15, 1.44724e+16 to \
  7.94351e+15, 1.44724e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.9897e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1041 polygon from \
  -4.53914e+15, 2.06913e+15 to \
  7.94351e+15, 1.45518e+16 to \
  7.94351e+15, 1.45518e+16 to \
  7.94351e+15, 1.45518e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.06913e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1042 polygon from \
  -4.53914e+15, 2.14857e+15 to \
  7.94351e+15, 1.46313e+16 to \
  7.94351e+15, 1.46313e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.14857e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1043 polygon from \
  -4.53914e+15, 2.228e+15 to \
  7.94351e+15, 1.47107e+16 to \
  7.94351e+15, 1.47107e+16 to \
  7.94351e+15, 1.47107e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.228e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1044 polygon from \
  -4.53914e+15, 2.30744e+15 to \
  7.94351e+15, 1.47901e+16 to \
  7.94351e+15, 1.47901e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.30744e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1045 polygon from \
  -4.53914e+15, 2.38687e+15 to \
  7.94351e+15, 1.48696e+16 to \
  7.94351e+15, 1.48696e+16 to \
  7.94351e+15, 1.48696e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.38687e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1046 polygon from \
  -4.53914e+15, 2.46631e+15 to \
  7.94351e+15, 1.4949e+16 to \
  7.94351e+15, 1.4949e+16 to \
  7.94351e+15, 1.4949e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.46631e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1047 polygon from \
  -4.53914e+15, 2.54574e+15 to \
  7.94351e+15, 1.50284e+16 to \
  7.94351e+15, 1.50284e+16 to \
  7.94351e+15, 1.50284e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.54574e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1048 polygon from \
  -4.53914e+15, 2.62518e+15 to \
  7.94351e+15, 1.51079e+16 to \
  7.94351e+15, 1.51079e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.62518e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1049 polygon from \
  -4.53914e+15, 2.70461e+15 to \
  7.94351e+15, 1.51873e+16 to \
  7.94351e+15, 1.51873e+16 to \
  7.94351e+15, 1.51873e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.70461e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1050 polygon from \
  -4.53914e+15, 2.78405e+15 to \
  7.94351e+15, 1.52667e+16 to \
  7.94351e+15, 1.52667e+16 to \
  7.94351e+15, 1.52667e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.78405e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1051 polygon from \
  -4.53914e+15, 2.86348e+15 to \
  7.94351e+15, 1.53462e+16 to \
  7.94351e+15, 1.53462e+16 to \
  7.94351e+15, 1.53462e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.86348e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1052 polygon from \
  -4.53914e+15, 2.94292e+15 to \
  7.94351e+15, 1.54256e+16 to \
  7.94351e+15, 1.54256e+16 to \
  7.94351e+15, 1.54256e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 2.94292e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1053 polygon from \
  -4.53914e+15, 3.02235e+15 to \
  7.94351e+15, 1.5505e+16 to \
  7.94351e+15, 1.5505e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.02235e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1054 polygon from \
  -4.53914e+15, 3.10179e+15 to \
  7.94351e+15, 1.55845e+16 to \
  7.94351e+15, 1.55845e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.10179e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1055 polygon from \
  -4.53914e+15, 3.18122e+15 to \
  7.94351e+15, 1.56639e+16 to \
  7.94351e+15, 1.56639e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.18122e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1056 polygon from \
  -4.53914e+15, 3.26066e+15 to \
  7.94351e+15, 1.57433e+16 to \
  7.94351e+15, 1.57433e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.26066e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1057 polygon from \
  -4.53914e+15, 3.34009e+15 to \
  7.94351e+15, 1.58228e+16 to \
  7.94351e+15, 1.58228e+16 to \
  7.94351e+15, 1.58228e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.34009e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1058 polygon from \
  -4.53914e+15, 3.41953e+15 to \
  7.94351e+15, 1.59022e+16 to \
  7.94351e+15, 1.59022e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.41953e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1059 polygon from \
  -4.53914e+15, 3.49896e+15 to \
  7.94351e+15, 1.59817e+16 to \
  7.94351e+15, 1.59817e+16 to \
  7.94351e+15, 1.59817e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.49896e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1060 polygon from \
  -4.53914e+15, 3.5784e+15 to \
  7.94351e+15, 1.60611e+16 to \
  7.94351e+15, 1.60611e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.5784e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1061 polygon from \
  -4.53914e+15, 3.65783e+15 to \
  7.94351e+15, 1.61405e+16 to \
  7.94351e+15, 1.61405e+16 to \
  7.94351e+15, 1.61405e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.65783e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1062 polygon from \
  -4.53914e+15, 3.73727e+15 to \
  7.94351e+15, 1.622e+16 to \
  7.94351e+15, 1.622e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.73727e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1063 polygon from \
  -4.53914e+15, 3.8167e+15 to \
  7.94351e+15, 1.62994e+16 to \
  7.94351e+15, 1.62994e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.8167e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1064 polygon from \
  -4.53914e+15, 3.89614e+15 to \
  7.94351e+15, 1.63788e+16 to \
  7.94351e+15, 1.63788e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.89614e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1065 polygon from \
  -4.53914e+15, 3.97557e+15 to \
  7.94351e+15, 1.64583e+16 to \
  7.94351e+15, 1.64583e+16 to \
  7.94351e+15, 1.64583e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 3.97557e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1066 polygon from \
  -4.53914e+15, 4.05501e+15 to \
  7.94351e+15, 1.65377e+16 to \
  7.94351e+15, 1.65377e+16 to \
  7.94351e+15, 1.65377e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.05501e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1067 polygon from \
  -4.53914e+15, 4.13444e+15 to \
  7.94351e+15, 1.66171e+16 to \
  7.94351e+15, 1.66171e+16 to \
  7.94351e+15, 1.66171e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.13444e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1068 polygon from \
  -4.53914e+15, 4.21388e+15 to \
  7.94351e+15, 1.66966e+16 to \
  7.94351e+15, 1.66966e+16 to \
  7.94351e+15, 1.66966e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.21388e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1069 polygon from \
  -4.53914e+15, 4.29331e+15 to \
  7.94351e+15, 1.6776e+16 to \
  7.94351e+15, 1.6776e+16 to \
  7.94351e+15, 1.6776e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.29331e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1070 polygon from \
  -4.53914e+15, 4.37275e+15 to \
  7.94351e+15, 1.68554e+16 to \
  7.94351e+15, 1.68554e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.37275e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1071 polygon from \
  -4.53914e+15, 4.45218e+15 to \
  7.94351e+15, 1.69349e+16 to \
  7.94351e+15, 1.69349e+16 to \
  7.94351e+15, 1.69349e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.45218e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1072 polygon from \
  -4.53914e+15, 4.53162e+15 to \
  7.94351e+15, 1.70143e+16 to \
  7.94351e+15, 1.70143e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.53162e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1073 polygon from \
  -4.53914e+15, 4.61105e+15 to \
  7.94351e+15, 1.70937e+16 to \
  7.94351e+15, 1.70937e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.61105e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1074 polygon from \
  -4.53914e+15, 4.69049e+15 to \
  7.94351e+15, 1.71732e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.69049e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1075 polygon from \
  -4.53914e+15, 4.76992e+15 to \
  7.94351e+15, 1.72526e+16 to \
  7.94351e+15, 1.72526e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.76992e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1076 polygon from \
  -4.53914e+15, 4.84936e+15 to \
  7.94351e+15, 1.73321e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.84936e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1077 polygon from \
  -4.53914e+15, 4.92879e+15 to \
  7.94351e+15, 1.74115e+16 to \
  7.94351e+15, 1.74115e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 4.92879e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1078 polygon from \
  -4.53914e+15, 5.00823e+15 to \
  7.94351e+15, 1.74909e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.00823e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1079 polygon from \
  -4.53914e+15, 5.08766e+15 to \
  7.94351e+15, 1.75704e+16 to \
  7.94351e+15, 1.75704e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.08766e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1080 polygon from \
  -4.53914e+15, 5.1671e+15 to \
  7.94351e+15, 1.76498e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.1671e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1081 polygon from \
  -4.53914e+15, 5.24653e+15 to \
  7.94351e+15, 1.77292e+16 to \
  7.94351e+15, 1.77292e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.24653e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1082 polygon from \
  -4.53914e+15, 5.32597e+15 to \
  7.94351e+15, 1.78087e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.32597e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1083 polygon from \
  -4.53914e+15, 5.4054e+15 to \
  7.94351e+15, 1.78881e+16 to \
  7.94351e+15, 1.78881e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.4054e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1084 polygon from \
  -4.53914e+15, 5.48484e+15 to \
  7.94351e+15, 1.79675e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.48484e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1085 polygon from \
  -4.53914e+15, 5.56427e+15 to \
  7.94351e+15, 1.8047e+16 to \
  7.94351e+15, 1.8047e+16 to \
  7.94351e+15, 1.8047e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.56427e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1086 polygon from \
  -4.53914e+15, 5.64371e+15 to \
  7.94351e+15, 1.81264e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.64371e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1087 polygon from \
  -4.53914e+15, 5.72314e+15 to \
  7.94351e+15, 1.82058e+16 to \
  7.94351e+15, 1.82058e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.72314e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1088 polygon from \
  -4.53914e+15, 5.80258e+15 to \
  7.94351e+15, 1.82853e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.80258e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1089 polygon from \
  -4.53914e+15, 5.88201e+15 to \
  7.94351e+15, 1.83647e+16 to \
  7.94351e+15, 1.83647e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.88201e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1090 polygon from \
  -4.53914e+15, 5.96145e+15 to \
  7.94351e+15, 1.84441e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 5.96145e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1091 polygon from \
  -4.53914e+15, 6.04088e+15 to \
  7.94351e+15, 1.85236e+16 to \
  7.94351e+15, 1.85236e+16 to \
  7.94351e+15, 1.85236e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.04088e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1092 polygon from \
  -4.53914e+15, 6.12032e+15 to \
  7.94351e+15, 1.8603e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.12032e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1093 polygon from \
  -4.53914e+15, 6.19975e+15 to \
  7.94351e+15, 1.86824e+16 to \
  7.94351e+15, 1.86824e+16 to \
  7.94351e+15, 1.86824e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.19975e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1094 polygon from \
  -4.53914e+15, 6.27919e+15 to \
  7.94351e+15, 1.87619e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.27919e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1095 polygon from \
  -4.53914e+15, 6.35862e+15 to \
  7.94351e+15, 1.88413e+16 to \
  7.94351e+15, 1.88413e+16 to \
  7.94351e+15, 1.88413e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.35862e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1096 polygon from \
  -4.53914e+15, 6.43806e+15 to \
  7.94351e+15, 1.89208e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.43806e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1097 polygon from \
  -4.53914e+15, 6.51749e+15 to \
  7.94351e+15, 1.90002e+16 to \
  7.94351e+15, 1.90002e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.51749e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1098 polygon from \
  -4.53914e+15, 6.59693e+15 to \
  7.94351e+15, 1.90796e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.59693e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1099 polygon from \
  -4.53914e+15, 6.67636e+15 to \
  7.94351e+15, 1.91591e+16 to \
  7.94351e+15, 1.91591e+16 to \
  7.94351e+15, 1.91591e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.67636e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1100 polygon from \
  -4.53914e+15, 6.7558e+15 to \
  7.94351e+15, 1.92385e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.7558e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1101 polygon from \
  -4.53914e+15, 6.83523e+15 to \
  7.94351e+15, 1.93179e+16 to \
  7.94351e+15, 1.93179e+16 to \
  7.94351e+15, 1.93179e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.83523e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1102 polygon from \
  -4.53914e+15, 6.91467e+15 to \
  7.94351e+15, 1.93974e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.91467e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1103 polygon from \
  -4.53914e+15, 6.9941e+15 to \
  7.94351e+15, 1.94768e+16 to \
  7.94351e+15, 1.94768e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 6.9941e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1104 polygon from \
  -4.53914e+15, 7.07354e+15 to \
  7.94351e+15, 1.95562e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.07354e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1105 polygon from \
  -4.53914e+15, 7.15297e+15 to \
  7.94351e+15, 1.96357e+16 to \
  7.94351e+15, 1.96357e+16 to \
  7.94351e+15, 1.96357e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.15297e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1106 polygon from \
  -4.53914e+15, 7.23241e+15 to \
  7.94351e+15, 1.97151e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.23241e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1107 polygon from \
  -4.53914e+15, 7.31184e+15 to \
  7.94351e+15, 1.97945e+16 to \
  7.94351e+15, 1.97945e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.31184e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1108 polygon from \
  -4.53914e+15, 7.39128e+15 to \
  7.94351e+15, 1.9874e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.39128e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1109 polygon from \
  -4.53914e+15, 7.47071e+15 to \
  7.94351e+15, 1.99534e+16 to \
  7.94351e+15, 1.99534e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.47071e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1110 polygon from \
  -4.53914e+15, 7.55015e+15 to \
  7.94351e+15, 2.00328e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.55015e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1111 polygon from \
  -4.53914e+15, 7.62958e+15 to \
  7.94351e+15, 2.01123e+16 to \
  7.94351e+15, 2.01123e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.62958e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1112 polygon from \
  -4.53914e+15, 7.70902e+15 to \
  7.94351e+15, 2.01917e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.70902e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1113 polygon from \
  -4.53914e+15, 7.78845e+15 to \
  7.94351e+15, 2.02711e+16 to \
  7.94351e+15, 2.02711e+16 to \
  7.94351e+15, 2.02711e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.78845e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1114 polygon from \
  -4.53914e+15, 7.86789e+15 to \
  7.94351e+15, 2.03506e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.86789e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1115 polygon from \
  -4.53914e+15, 7.94732e+15 to \
  7.94351e+15, 2.043e+16 to \
  7.94351e+15, 2.043e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 7.94732e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1116 polygon from \
  -4.53914e+15, 8.02676e+15 to \
  7.94351e+15, 2.05095e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.02676e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1117 polygon from \
  -4.53914e+15, 8.10619e+15 to \
  7.94351e+15, 2.05889e+16 to \
  7.94351e+15, 2.05889e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.10619e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1118 polygon from \
  -4.53914e+15, 8.18563e+15 to \
  7.94351e+15, 2.06683e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.18563e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1119 polygon from \
  -4.53914e+15, 8.26506e+15 to \
  7.94351e+15, 2.07478e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.26506e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1120 polygon from \
  -4.53914e+15, 8.3445e+15 to \
  7.94351e+15, 2.08272e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.3445e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1121 polygon from \
  -4.53914e+15, 8.42393e+15 to \
  7.94351e+15, 2.09066e+16 to \
  7.94351e+15, 2.09066e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.42393e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1122 polygon from \
  -4.53914e+15, 8.50337e+15 to \
  7.94351e+15, 2.09861e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.50337e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1123 polygon from \
  -4.53914e+15, 8.5828e+15 to \
  7.94351e+15, 2.10655e+16 to \
  7.94351e+15, 2.10655e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.5828e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1124 polygon from \
  -4.53914e+15, 8.66224e+15 to \
  7.94351e+15, 2.11449e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.66224e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1125 polygon from \
  -4.53914e+15, 8.74167e+15 to \
  7.94351e+15, 2.12244e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.74167e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1126 polygon from \
  -4.53914e+15, 8.82111e+15 to \
  7.94351e+15, 2.13038e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.82111e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1127 polygon from \
  -4.53914e+15, 8.90054e+15 to \
  7.94351e+15, 2.13832e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.90054e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1128 polygon from \
  -4.53914e+15, 8.97998e+15 to \
  7.94351e+15, 2.14627e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 8.97998e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1129 polygon from \
  -4.53914e+15, 9.05941e+15 to \
  7.94351e+15, 2.15421e+16 to \
  7.94351e+15, 2.15421e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.05941e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1130 polygon from \
  -4.53914e+15, 9.13885e+15 to \
  7.94351e+15, 2.16215e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.13885e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1131 polygon from \
  -4.53914e+15, 9.21828e+15 to \
  7.94351e+15, 2.1701e+16 to \
  7.94351e+15, 2.1701e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.21828e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1132 polygon from \
  -4.53914e+15, 9.29772e+15 to \
  7.94351e+15, 2.17804e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.29772e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1133 polygon from \
  -4.53914e+15, 9.37715e+15 to \
  7.94351e+15, 2.18598e+16 to \
  7.94351e+15, 2.18598e+16 to \
  7.94351e+15, 2.18598e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.37715e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1134 polygon from \
  -4.53914e+15, 9.45659e+15 to \
  7.94351e+15, 2.19393e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.45659e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1135 polygon from \
  -4.53914e+15, 9.53602e+15 to \
  7.94351e+15, 2.20187e+16 to \
  7.94351e+15, 2.20187e+16 to \
  7.94351e+15, 2.20187e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.53602e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1136 polygon from \
  -4.53914e+15, 9.61546e+15 to \
  7.94351e+15, 2.20982e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.61546e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1137 polygon from \
  -4.53914e+15, 9.6949e+15 to \
  7.94351e+15, 2.21776e+16 to \
  7.94351e+15, 2.21776e+16 to \
  7.94351e+15, 2.21776e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.6949e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1138 polygon from \
  -4.53914e+15, 9.77433e+15 to \
  7.94351e+15, 2.2257e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.77433e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1139 polygon from \
  -4.53914e+15, 9.85377e+15 to \
  7.94351e+15, 2.23365e+16 to \
  7.94351e+15, 2.23365e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.85377e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1140 polygon from \
  -4.53914e+15, 9.9332e+15 to \
  7.94351e+15, 2.24159e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 9.9332e+15 front fs empty border lc rgb '#6165' lw 0.200001
set object 1141 polygon from \
  -4.53914e+15, 1.00127e+16 to \
  7.94351e+15, 2.24953e+16 to \
  7.94351e+15, 2.24953e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.00127e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1142 polygon from \
  -4.53914e+15, 1.00921e+16 to \
  7.94351e+15, 2.25748e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.00921e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1143 polygon from \
  -4.53914e+15, 1.01716e+16 to \
  7.94351e+15, 2.26542e+16 to \
  7.94351e+15, 2.26542e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.01716e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1144 polygon from \
  -4.53914e+15, 1.0251e+16 to \
  7.94351e+15, 2.27336e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.0251e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1145 polygon from \
  -4.53914e+15, 1.03304e+16 to \
  7.94351e+15, 2.28131e+16 to \
  7.94351e+15, 2.28131e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.03304e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1146 polygon from \
  -4.53914e+15, 1.04099e+16 to \
  7.94351e+15, 2.28925e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.04099e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1147 polygon from \
  -4.53914e+15, 1.04893e+16 to \
  7.94351e+15, 2.29719e+16 to \
  7.94351e+15, 2.29719e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.04893e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1148 polygon from \
  -4.53914e+15, 1.05687e+16 to \
  7.94351e+15, 2.30514e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.05687e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1149 polygon from \
  -4.53914e+15, 1.06482e+16 to \
  7.94351e+15, 2.31308e+16 to \
  7.94351e+15, 2.31308e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.06482e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1150 polygon from \
  -4.53914e+15, 1.07276e+16 to \
  7.94351e+15, 2.32102e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.07276e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1151 polygon from \
  -4.53914e+15, 1.0807e+16 to \
  7.94351e+15, 2.32897e+16 to \
  7.94351e+15, 2.32897e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.0807e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1152 polygon from \
  -4.53914e+15, 1.08865e+16 to \
  7.94351e+15, 2.33691e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.08865e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1153 polygon from \
  -4.53914e+15, 1.09659e+16 to \
  7.94351e+15, 2.34485e+16 to \
  7.94351e+15, 2.34485e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.09659e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1154 polygon from \
  -4.53914e+15, 1.10453e+16 to \
  7.94351e+15, 2.3528e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.10453e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1155 polygon from \
  -4.53914e+15, 1.11248e+16 to \
  7.94351e+15, 2.36074e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.11248e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1156 polygon from \
  -4.53914e+15, 1.12042e+16 to \
  7.94351e+15, 2.36869e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.12042e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1157 polygon from \
  -4.53914e+15, 1.12836e+16 to \
  7.94351e+15, 2.37663e+16 to \
  7.94351e+15, 2.37663e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.12836e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1158 polygon from \
  -4.53914e+15, 1.13631e+16 to \
  7.94351e+15, 2.38457e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.13631e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1159 polygon from \
  -4.53914e+15, 1.14425e+16 to \
  7.94351e+15, 2.39252e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.14425e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1160 polygon from \
  -4.53914e+15, 1.15219e+16 to \
  7.94351e+15, 2.40046e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.15219e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1161 polygon from \
  -4.53914e+15, 1.16014e+16 to \
  7.94351e+15, 2.4084e+16 to \
  7.94351e+15, 2.4084e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.16014e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1162 polygon from \
  -4.53914e+15, 1.16808e+16 to \
  7.94351e+15, 2.41635e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.16808e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1163 polygon from \
  -4.53914e+15, 1.17603e+16 to \
  7.94351e+15, 2.42429e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.17603e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1164 polygon from \
  -4.53914e+15, 1.18397e+16 to \
  7.94351e+15, 2.43223e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.18397e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1165 polygon from \
  -4.53914e+15, 1.19191e+16 to \
  7.94351e+15, 2.44018e+16 to \
  7.94351e+15, 2.44018e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19191e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1166 polygon from \
  -4.53914e+15, 1.19986e+16 to \
  7.94351e+15, 2.44812e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.19986e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1167 polygon from \
  -4.53914e+15, 1.2078e+16 to \
  7.94351e+15, 2.45606e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.2078e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1168 polygon from \
  -4.53914e+15, 1.21574e+16 to \
  7.94351e+15, 2.46401e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.21574e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1169 polygon from \
  -4.53914e+15, 1.22369e+16 to \
  7.94351e+15, 2.47195e+16 to \
  7.94351e+15, 2.47195e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.22369e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1170 polygon from \
  -4.53914e+15, 1.23163e+16 to \
  7.94351e+15, 2.47989e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.23163e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1171 polygon from \
  -4.53914e+15, 1.23957e+16 to \
  7.94351e+15, 2.48784e+16 to \
  7.94351e+15, 2.48784e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.23957e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1172 polygon from \
  -4.53914e+15, 1.24752e+16 to \
  7.94351e+15, 2.49578e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.24752e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1173 polygon from \
  -4.53914e+15, 1.25546e+16 to \
  7.94351e+15, 2.50372e+16 to \
  7.94351e+15, 2.50372e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.25546e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1174 polygon from \
  -4.53914e+15, 1.2634e+16 to \
  7.94351e+15, 2.51167e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.2634e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1175 polygon from \
  -4.53914e+15, 1.27135e+16 to \
  7.94351e+15, 2.51961e+16 to \
  7.94351e+15, 2.51961e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27135e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1176 polygon from \
  -4.53914e+15, 1.27929e+16 to \
  7.94351e+15, 2.52756e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.27929e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1177 polygon from \
  -4.53914e+15, 1.28723e+16 to \
  7.94351e+15, 2.5355e+16 to \
  7.94351e+15, 2.5355e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.28723e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1178 polygon from \
  -4.53914e+15, 1.29518e+16 to \
  7.94351e+15, 2.54344e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.29518e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1179 polygon from \
  -4.53914e+15, 1.30312e+16 to \
  7.94351e+15, 2.55139e+16 to \
  7.94351e+15, 2.55139e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.30312e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1180 polygon from \
  -4.53914e+15, 1.31106e+16 to \
  7.94351e+15, 2.55933e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.31106e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1181 polygon from \
  -4.53914e+15, 1.31901e+16 to \
  7.94351e+15, 2.56727e+16 to \
  7.94351e+15, 2.56727e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.31901e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1182 polygon from \
  -4.53914e+15, 1.32695e+16 to \
  7.94351e+15, 2.57522e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.32695e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1183 polygon from \
  -4.53914e+15, 1.3349e+16 to \
  7.94351e+15, 2.58316e+16 to \
  7.94351e+15, 2.58316e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.3349e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1184 polygon from \
  -4.53914e+15, 1.34284e+16 to \
  7.94351e+15, 2.5911e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.34284e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1185 polygon from \
  -4.53914e+15, 1.35078e+16 to \
  7.94351e+15, 2.59905e+16 to \
  7.94351e+15, 2.59905e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35078e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1186 polygon from \
  -4.53914e+15, 1.35873e+16 to \
  7.94351e+15, 2.60699e+16 to \
  7.94351e+15, 2.60699e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.35873e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1187 polygon from \
  -4.53914e+15, 1.36667e+16 to \
  7.94351e+15, 2.61493e+16 to \
  7.94351e+15, 2.61493e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.36667e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1188 polygon from \
  -4.53914e+15, 1.37461e+16 to \
  7.94351e+15, 2.62288e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.37461e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1189 polygon from \
  -4.53914e+15, 1.38256e+16 to \
  7.94351e+15, 2.63082e+16 to \
  7.94351e+15, 2.63082e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.38256e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1190 polygon from \
  -4.53914e+15, 1.3905e+16 to \
  7.94351e+15, 2.63876e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.3905e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1191 polygon from \
  -4.53914e+15, 1.39844e+16 to \
  7.94351e+15, 2.64671e+16 to \
  7.94351e+15, 2.64671e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.39844e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1192 polygon from \
  -4.53914e+15, 1.40639e+16 to \
  7.94351e+15, 2.65465e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.40639e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1193 polygon from \
  -4.53914e+15, 1.41433e+16 to \
  7.94351e+15, 2.66259e+16 to \
  7.94351e+15, 2.66259e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.41433e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1194 polygon from \
  -4.53914e+15, 1.42227e+16 to \
  7.94351e+15, 2.67054e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.42227e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1195 polygon from \
  -4.53914e+15, 1.43022e+16 to \
  7.94351e+15, 2.67848e+16 to \
  7.94351e+15, 2.67848e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.43022e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1196 polygon from \
  -4.53914e+15, 1.43816e+16 to \
  7.94351e+15, 2.68643e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.43816e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1197 polygon from \
  -4.53914e+15, 1.4461e+16 to \
  7.94351e+15, 2.69437e+16 to \
  7.94351e+15, 2.69437e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.4461e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1198 polygon from \
  -4.53914e+15, 1.45405e+16 to \
  7.94351e+15, 2.70231e+16 to \
  7.94351e+15, 2.70231e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.45405e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1199 polygon from \
  -4.53914e+15, 1.46199e+16 to \
  7.94351e+15, 2.71026e+16 to \
  7.94351e+15, 2.71026e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.46199e+16 front fs empty border lc rgb '#6165' lw 0.200001
set object 1200 polygon from \
  -4.53914e+15, 1.46993e+16 to \
  7.94351e+15, 2.7182e+16 to \
  7.94351e+15, 0 to \
  -4.53914e+15, -0 to \
  -4.53914e+15, 1.46993e+16 front fs empty border lc rgb '#6165' lw 0.200001
plot [-5.7874e+15:9.19177e+15] [-2.71819e+15:2.99002e+16] NaN notitle 

