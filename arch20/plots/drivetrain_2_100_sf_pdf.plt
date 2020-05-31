# settings
set title "drivetrain-2-100"
set size square
set term pdf font ',10'
set output "drivetrain_2_100.pdf
set xtics autofreq
set ytics autofreq
set bmargin 2
set grid back
# axis settings
set xzeroaxis
set zeroaxis
set xtics axis
set yzeroaxis
set ytics axis
set xrange [-7.11686:0.61426] 
set yrange [-9.5949:105.544] 

# plotting sets
set object 1 polygon from \
  -0.0788021, 0.0199998 to \
  -0.0375973, 0.0199998 to \
  -0.0375973, -4.68776e-07 to \
  -0.0788021, -4.68776e-07 to \
  -0.0788021, 0.0199998 front fs empty border lc rgb '#549f' lw 0.1
set object 2 polygon from \
  -0.108801, 0.039998 to \
  -0.047595, 0.039998 to \
  -0.047595, 0.00999891 to \
  -0.108801, 0.00999891 to \
  -0.108801, 0.039998 front fs empty border lc rgb '#549f' lw 0.1
set object 3 polygon from \
  -0.138794, 0.0599948 to \
  -0.0575912, 0.0599948 to \
  -0.0575912, 0.019997 to \
  -0.138794, 0.019997 to \
  -0.138794, 0.0599948 front fs empty border lc rgb '#549f' lw 0.1
set object 4 polygon from \
  -0.168779, 0.0799905 to \
  -0.0675851, 0.0799905 to \
  -0.0675851, 0.0299939 to \
  -0.168779, 0.0299939 to \
  -0.168779, 0.0799905 front fs empty border lc rgb '#549f' lw 0.1
set object 5 polygon from \
  -0.198754, 0.0999848 to \
  -0.0775757, 0.0999848 to \
  -0.0775757, 0.0399895 to \
  -0.198754, 0.0399895 to \
  -0.198754, 0.0999848 front fs empty border lc rgb '#549f' lw 0.1
set object 6 polygon from \
  -0.228716, 0.119978 to \
  -0.0875622, 0.119978 to \
  -0.0875622, 0.0499839 to \
  -0.228716, 0.0499839 to \
  -0.228716, 0.119978 front fs empty border lc rgb '#549f' lw 0.1
set object 7 polygon from \
  -0.258663, 0.13997 to \
  -0.0975438, 0.13997 to \
  -0.0975438, 0.059977 to \
  -0.258663, 0.059977 to \
  -0.258663, 0.13997 front fs empty border lc rgb '#549f' lw 0.1
set object 8 polygon from \
  -0.288591, 0.15996 to \
  -0.107519, 0.15996 to \
  -0.107519, 0.0699689 to \
  -0.288591, 0.0699689 to \
  -0.288591, 0.15996 front fs empty border lc rgb '#549f' lw 0.1
set object 9 polygon from \
  -0.3185, 0.17995 to \
  -0.117488, 0.17995 to \
  -0.117488, 0.0799595 to \
  -0.3185, 0.0799595 to \
  -0.3185, 0.17995 front fs empty border lc rgb '#549f' lw 0.1
set object 10 polygon from \
  -0.348386, 0.199938 to \
  -0.12745, 0.199938 to \
  -0.12745, 0.0899489 to \
  -0.348386, 0.0899489 to \
  -0.348386, 0.199938 front fs empty border lc rgb '#549f' lw 0.1
set object 11 polygon from \
  -0.378247, 0.219925 to \
  -0.137403, 0.219925 to \
  -0.137403, 0.099937 to \
  -0.378247, 0.099937 to \
  -0.378247, 0.219925 front fs empty border lc rgb '#549f' lw 0.1
set object 12 polygon from \
  -0.40808, 0.23991 to \
  -0.147346, 0.23991 to \
  -0.147346, 0.109924 to \
  -0.40808, 0.109924 to \
  -0.40808, 0.23991 front fs empty border lc rgb '#549f' lw 0.1
set object 13 polygon from \
  -0.437883, 0.259895 to \
  -0.15728, 0.259895 to \
  -0.15728, 0.11991 to \
  -0.437883, 0.11991 to \
  -0.437883, 0.259895 front fs empty border lc rgb '#549f' lw 0.1
set object 14 polygon from \
  -0.467655, 0.279878 to \
  -0.167203, 0.279878 to \
  -0.167203, 0.129894 to \
  -0.467655, 0.129894 to \
  -0.467655, 0.279878 front fs empty border lc rgb '#549f' lw 0.1
set object 15 polygon from \
  -0.497391, 0.29986 to \
  -0.177114, 0.29986 to \
  -0.177114, 0.139877 to \
  -0.497391, 0.139877 to \
  -0.497391, 0.29986 front fs empty border lc rgb '#549f' lw 0.1
set object 16 polygon from \
  -0.527091, 0.31984 to \
  -0.187012, 0.31984 to \
  -0.187012, 0.149859 to \
  -0.527091, 0.149859 to \
  -0.527091, 0.31984 front fs empty border lc rgb '#549f' lw 0.1
set object 17 polygon from \
  -0.556752, 0.33982 to \
  -0.196897, 0.33982 to \
  -0.196897, 0.15984 to \
  -0.556752, 0.15984 to \
  -0.556752, 0.33982 front fs empty border lc rgb '#549f' lw 0.1
set object 18 polygon from \
  -0.586371, 0.359798 to \
  -0.206768, 0.359798 to \
  -0.206768, 0.169819 to \
  -0.586371, 0.169819 to \
  -0.586371, 0.359798 front fs empty border lc rgb '#549f' lw 0.1
set object 19 polygon from \
  -0.615946, 0.379775 to \
  -0.216624, 0.379775 to \
  -0.216624, 0.179797 to \
  -0.615946, 0.179797 to \
  -0.615946, 0.379775 front fs empty border lc rgb '#549f' lw 0.1
set object 20 polygon from \
  -0.645476, 0.39975 to \
  -0.226464, 0.39975 to \
  -0.226464, 0.189774 to \
  -0.645476, 0.189774 to \
  -0.645476, 0.39975 front fs empty border lc rgb '#549f' lw 0.1
set object 21 polygon from \
  -0.674957, 0.419725 to \
  -0.236287, 0.419725 to \
  -0.236287, 0.19975 to \
  -0.674957, 0.19975 to \
  -0.674957, 0.419725 front fs empty border lc rgb '#549f' lw 0.1
set object 22 polygon from \
  -0.704388, 0.439698 to \
  -0.246093, 0.439698 to \
  -0.246093, 0.209724 to \
  -0.704388, 0.209724 to \
  -0.704388, 0.439698 front fs empty border lc rgb '#549f' lw 0.1
set object 23 polygon from \
  -0.733766, 0.45967 to \
  -0.255882, 0.45967 to \
  -0.255882, 0.219697 to \
  -0.733766, 0.219697 to \
  -0.733766, 0.45967 front fs empty border lc rgb '#549f' lw 0.1
set object 24 polygon from \
  -0.76309, 0.47964 to \
  -0.265651, 0.47964 to \
  -0.265651, 0.229669 to \
  -0.76309, 0.229669 to \
  -0.76309, 0.47964 front fs empty border lc rgb '#549f' lw 0.1
set object 25 polygon from \
  -0.792356, 0.49961 to \
  -0.275401, 0.49961 to \
  -0.275401, 0.23964 to \
  -0.792356, 0.23964 to \
  -0.792356, 0.49961 front fs empty border lc rgb '#549f' lw 0.1
set object 26 polygon from \
  -0.821564, 0.519578 to \
  -0.28513, 0.519578 to \
  -0.28513, 0.249609 to \
  -0.821564, 0.249609 to \
  -0.821564, 0.519578 front fs empty border lc rgb '#549f' lw 0.1
set object 27 polygon from \
  -0.850711, 0.539545 to \
  -0.294838, 0.539545 to \
  -0.294838, 0.259577 to \
  -0.850711, 0.259577 to \
  -0.850711, 0.539545 front fs empty border lc rgb '#549f' lw 0.1
set object 28 polygon from \
  -0.879794, 0.55951 to \
  -0.304525, 0.55951 to \
  -0.304525, 0.269544 to \
  -0.879794, 0.269544 to \
  -0.879794, 0.55951 front fs empty border lc rgb '#549f' lw 0.1
set object 29 polygon from \
  -0.908812, 0.579475 to \
  -0.314189, 0.579475 to \
  -0.314189, 0.27951 to \
  -0.908812, 0.27951 to \
  -0.908812, 0.579475 front fs empty border lc rgb '#549f' lw 0.1
set object 30 polygon from \
  -0.937763, 0.599438 to \
  -0.32383, 0.599438 to \
  -0.32383, 0.289474 to \
  -0.937763, 0.289474 to \
  -0.937763, 0.599438 front fs empty border lc rgb '#549f' lw 0.1
set object 31 polygon from \
  -0.966644, 0.6194 to \
  -0.333447, 0.6194 to \
  -0.333447, 0.299437 to \
  -0.966644, 0.299437 to \
  -0.966644, 0.6194 front fs empty border lc rgb '#549f' lw 0.1
set object 32 polygon from \
  -0.995454, 0.63936 to \
  -0.343039, 0.63936 to \
  -0.343039, 0.309399 to \
  -0.995454, 0.309399 to \
  -0.995454, 0.63936 front fs empty border lc rgb '#549f' lw 0.1
set object 33 polygon from \
  -1.02419, 0.65932 to \
  -0.352606, 0.65932 to \
  -0.352606, 0.31936 to \
  -1.02419, 0.31936 to \
  -1.02419, 0.65932 front fs empty border lc rgb '#549f' lw 0.1
set object 34 polygon from \
  -1.05285, 0.679278 to \
  -0.362147, 0.679278 to \
  -0.362147, 0.329319 to \
  -1.05285, 0.329319 to \
  -1.05285, 0.679278 front fs empty border lc rgb '#549f' lw 0.1
set object 35 polygon from \
  -1.08144, 0.699235 to \
  -0.371661, 0.699235 to \
  -0.371661, 0.339277 to \
  -1.08144, 0.339277 to \
  -1.08144, 0.699235 front fs empty border lc rgb '#549f' lw 0.1
set object 36 polygon from \
  -1.10994, 0.71919 to \
  -0.381148, 0.71919 to \
  -0.381148, 0.349234 to \
  -1.10994, 0.349234 to \
  -1.10994, 0.71919 front fs empty border lc rgb '#549f' lw 0.1
set object 37 polygon from \
  -1.13837, 0.739145 to \
  -0.390607, 0.739145 to \
  -0.390607, 0.35919 to \
  -1.13837, 0.35919 to \
  -1.13837, 0.739145 front fs empty border lc rgb '#549f' lw 0.1
set object 38 polygon from \
  -1.16671, 0.759098 to \
  -0.400037, 0.759098 to \
  -0.400037, 0.369144 to \
  -1.16671, 0.369144 to \
  -1.16671, 0.759098 front fs empty border lc rgb '#549f' lw 0.1
set object 39 polygon from \
  -1.19496, 0.77905 to \
  -0.409438, 0.77905 to \
  -0.409438, 0.379097 to \
  -1.19496, 0.379097 to \
  -1.19496, 0.77905 front fs empty border lc rgb '#549f' lw 0.1
set object 40 polygon from \
  -1.22313, 0.799 to \
  -0.418809, 0.799 to \
  -0.418809, 0.389049 to \
  -1.22313, 0.389049 to \
  -1.22313, 0.799 front fs empty border lc rgb '#549f' lw 0.1
set object 41 polygon from \
  -1.25121, 0.81895 to \
  -0.42815, 0.81895 to \
  -0.42815, 0.399 to \
  -1.25121, 0.399 to \
  -1.25121, 0.81895 front fs empty border lc rgb '#549f' lw 0.1
set object 42 polygon from \
  -1.27921, 0.838898 to \
  -0.437459, 0.838898 to \
  -0.437459, 0.408949 to \
  -1.27921, 0.408949 to \
  -1.27921, 0.838898 front fs empty border lc rgb '#549f' lw 0.1
set object 43 polygon from \
  -1.3071, 0.858845 to \
  -0.446737, 0.858845 to \
  -0.446737, 0.418897 to \
  -1.3071, 0.418897 to \
  -1.3071, 0.858845 front fs empty border lc rgb '#549f' lw 0.1
set object 44 polygon from \
  -1.33491, 0.87879 to \
  -0.455982, 0.87879 to \
  -0.455982, 0.428844 to \
  -1.33491, 0.428844 to \
  -1.33491, 0.87879 front fs empty border lc rgb '#549f' lw 0.1
set object 45 polygon from \
  -1.36262, 0.898735 to \
  -0.465194, 0.898735 to \
  -0.465194, 0.43879 to \
  -1.36262, 0.43879 to \
  -1.36262, 0.898735 front fs empty border lc rgb '#549f' lw 0.1
set object 46 polygon from \
  -1.39023, 0.918678 to \
  -0.474373, 0.918678 to \
  -0.474373, 0.448734 to \
  -1.39023, 0.448734 to \
  -1.39023, 0.918678 front fs empty border lc rgb '#549f' lw 0.1
set object 47 polygon from \
  -1.41775, 0.93862 to \
  -0.483517, 0.93862 to \
  -0.483517, 0.458677 to \
  -1.41775, 0.458677 to \
  -1.41775, 0.93862 front fs empty border lc rgb '#549f' lw 0.1
set object 48 polygon from \
  -1.44516, 0.95856 to \
  -0.492627, 0.95856 to \
  -0.492627, 0.468619 to \
  -1.44516, 0.468619 to \
  -1.44516, 0.95856 front fs empty border lc rgb '#549f' lw 0.1
set object 49 polygon from \
  -1.47247, 0.9785 to \
  -0.501702, 0.9785 to \
  -0.501702, 0.47856 to \
  -1.47247, 0.47856 to \
  -1.47247, 0.9785 front fs empty border lc rgb '#549f' lw 0.1
set object 50 polygon from \
  -1.49968, 0.998438 to \
  -0.51074, 0.998438 to \
  -0.51074, 0.488499 to \
  -1.49968, 0.488499 to \
  -1.49968, 0.998438 front fs empty border lc rgb '#549f' lw 0.1
set object 51 polygon from \
  -1.52678, 1.01837 to \
  -0.519743, 1.01837 to \
  -0.519743, 0.498437 to \
  -1.52678, 0.498437 to \
  -1.52678, 1.01837 front fs empty border lc rgb '#549f' lw 0.1
set object 52 polygon from \
  -1.55378, 1.03831 to \
  -0.528708, 1.03831 to \
  -0.528708, 0.508374 to \
  -1.55378, 0.508374 to \
  -1.55378, 1.03831 front fs empty border lc rgb '#549f' lw 0.1
set object 53 polygon from \
  -1.58067, 1.05824 to \
  -0.537636, 1.05824 to \
  -0.537636, 0.51831 to \
  -1.58067, 0.51831 to \
  -1.58067, 1.05824 front fs empty border lc rgb '#549f' lw 0.1
set object 54 polygon from \
  -1.60745, 1.07818 to \
  -0.546526, 1.07818 to \
  -0.546526, 0.528244 to \
  -1.60745, 0.528244 to \
  -1.60745, 1.07818 front fs empty border lc rgb '#549f' lw 0.1
set object 55 polygon from \
  -1.63411, 1.09811 to \
  -0.555378, 1.09811 to \
  -0.555378, 0.538177 to \
  -1.63411, 0.538177 to \
  -1.63411, 1.09811 front fs empty border lc rgb '#549f' lw 0.1
set object 56 polygon from \
  -1.66067, 1.11804 to \
  -0.564191, 1.11804 to \
  -0.564191, 0.548109 to \
  -1.66067, 0.548109 to \
  -1.66067, 1.11804 front fs empty border lc rgb '#549f' lw 0.1
set object 57 polygon from \
  -1.68711, 1.13797 to \
  -0.572964, 1.13797 to \
  -0.572964, 0.55804 to \
  -1.68711, 0.55804 to \
  -1.68711, 1.13797 front fs empty border lc rgb '#549f' lw 0.1
set object 58 polygon from \
  -1.71343, 1.1579 to \
  -0.581697, 1.1579 to \
  -0.581697, 0.567969 to \
  -1.71343, 0.567969 to \
  -1.71343, 1.1579 front fs empty border lc rgb '#549f' lw 0.1
set object 59 polygon from \
  -1.73964, 1.17782 to \
  -0.59039, 1.17782 to \
  -0.59039, 0.577897 to \
  -1.73964, 0.577897 to \
  -1.73964, 1.17782 front fs empty border lc rgb '#549f' lw 0.1
set object 60 polygon from \
  -1.76573, 1.19775 to \
  -0.599042, 1.19775 to \
  -0.599042, 0.587824 to \
  -1.76573, 0.587824 to \
  -1.76573, 1.19775 front fs empty border lc rgb '#549f' lw 0.1
set object 61 polygon from \
  -1.79169, 1.21767 to \
  -0.607652, 1.21767 to \
  -0.607652, 0.59775 to \
  -1.79169, 0.59775 to \
  -1.79169, 1.21767 front fs empty border lc rgb '#549f' lw 0.1
set object 62 polygon from \
  -1.81754, 1.2376 to \
  -0.616221, 1.2376 to \
  -0.616221, 0.607674 to \
  -1.81754, 0.607674 to \
  -1.81754, 1.2376 front fs empty border lc rgb '#549f' lw 0.1
set object 63 polygon from \
  -1.84327, 1.25752 to \
  -0.624747, 1.25752 to \
  -0.624747, 0.617597 to \
  -1.84327, 0.617597 to \
  -1.84327, 1.25752 front fs empty border lc rgb '#549f' lw 0.1
set object 64 polygon from \
  -1.86887, 1.27744 to \
  -0.633231, 1.27744 to \
  -0.633231, 0.627519 to \
  -1.86887, 0.627519 to \
  -1.86887, 1.27744 front fs empty border lc rgb '#549f' lw 0.1
set object 65 polygon from \
  -1.89435, 1.29736 to \
  -0.641671, 1.29736 to \
  -0.641671, 0.63744 to \
  -1.89435, 0.63744 to \
  -1.89435, 1.29736 front fs empty border lc rgb '#549f' lw 0.1
set object 66 polygon from \
  -1.9197, 1.31728 to \
  -0.650068, 1.31728 to \
  -0.650068, 0.647359 to \
  -1.9197, 0.647359 to \
  -1.9197, 1.31728 front fs empty border lc rgb '#549f' lw 0.1
set object 67 polygon from \
  -1.94492, 1.33719 to \
  -0.658421, 1.33719 to \
  -0.658421, 0.657277 to \
  -1.94492, 0.657277 to \
  -1.94492, 1.33719 front fs empty border lc rgb '#549f' lw 0.1
set object 68 polygon from \
  -1.97001, 1.35711 to \
  -0.66673, 1.35711 to \
  -0.66673, 0.667194 to \
  -1.97001, 0.667194 to \
  -1.97001, 1.35711 front fs empty border lc rgb '#549f' lw 0.1
set object 69 polygon from \
  -1.99498, 1.37702 to \
  -0.674994, 1.37702 to \
  -0.674994, 0.67711 to \
  -1.99498, 0.67711 to \
  -1.99498, 1.37702 front fs empty border lc rgb '#549f' lw 0.1
set object 70 polygon from \
  -2.01981, 1.39694 to \
  -0.683213, 1.39694 to \
  -0.683213, 0.687024 to \
  -2.01981, 0.687024 to \
  -2.01981, 1.39694 front fs empty border lc rgb '#549f' lw 0.1
set object 71 polygon from \
  -2.04451, 1.41685 to \
  -0.691386, 1.41685 to \
  -0.691386, 0.696937 to \
  -2.04451, 0.696937 to \
  -2.04451, 1.41685 front fs empty border lc rgb '#549f' lw 0.1
set object 72 polygon from \
  -2.06908, 1.43676 to \
  -0.699513, 1.43676 to \
  -0.699513, 0.706849 to \
  -2.06908, 0.706849 to \
  -2.06908, 1.43676 front fs empty border lc rgb '#549f' lw 0.1
set object 73 polygon from \
  -2.09352, 1.45667 to \
  -0.707594, 1.45667 to \
  -0.707594, 0.71676 to \
  -2.09352, 0.71676 to \
  -2.09352, 1.45667 front fs empty border lc rgb '#549f' lw 0.1
set object 74 polygon from \
  -2.11782, 1.47658 to \
  -0.715628, 1.47658 to \
  -0.715628, 0.726669 to \
  -2.11782, 0.726669 to \
  -2.11782, 1.47658 front fs empty border lc rgb '#549f' lw 0.1
set object 75 polygon from \
  -2.14198, 1.49648 to \
  -0.723616, 1.49648 to \
  -0.723616, 0.736577 to \
  -2.14198, 0.736577 to \
  -2.14198, 1.49648 front fs empty border lc rgb '#549f' lw 0.1
set object 76 polygon from \
  -2.16601, 1.51639 to \
  -0.731555, 1.51639 to \
  -0.731555, 0.746484 to \
  -2.16601, 0.746484 to \
  -2.16601, 1.51639 front fs empty border lc rgb '#549f' lw 0.1
set object 77 polygon from \
  -2.18989, 1.53629 to \
  -0.739448, 1.53629 to \
  -0.739448, 0.75639 to \
  -2.18989, 0.75639 to \
  -2.18989, 1.53629 front fs empty border lc rgb '#549f' lw 0.1
set object 78 polygon from \
  -2.21364, 1.5562 to \
  -0.747292, 1.5562 to \
  -0.747292, 0.766294 to \
  -2.21364, 0.766294 to \
  -2.21364, 1.5562 front fs empty border lc rgb '#549f' lw 0.1
set object 79 polygon from \
  -2.23725, 1.5761 to \
  -0.755088, 1.5761 to \
  -0.755088, 0.776197 to \
  -2.23725, 0.776197 to \
  -2.23725, 1.5761 front fs empty border lc rgb '#549f' lw 0.1
set object 80 polygon from \
  -2.26072, 1.596 to \
  -0.762835, 1.596 to \
  -0.762835, 0.786099 to \
  -2.26072, 0.786099 to \
  -2.26072, 1.596 front fs empty border lc rgb '#549f' lw 0.1
set object 81 polygon from \
  -2.28404, 1.6159 to \
  -0.770534, 1.6159 to \
  -0.770534, 0.796 to \
  -2.28404, 0.796 to \
  -2.28404, 1.6159 front fs empty border lc rgb '#549f' lw 0.1
set object 82 polygon from \
  -2.30723, 1.6358 to \
  -0.778183, 1.6358 to \
  -0.778183, 0.805899 to \
  -2.30723, 0.805899 to \
  -2.30723, 1.6358 front fs empty border lc rgb '#549f' lw 0.1
set object 83 polygon from \
  -2.33027, 1.65569 to \
  -0.785782, 1.65569 to \
  -0.785782, 0.815797 to \
  -2.33027, 0.815797 to \
  -2.33027, 1.65569 front fs empty border lc rgb '#549f' lw 0.1
set object 84 polygon from \
  -2.35316, 1.67559 to \
  -0.793332, 1.67559 to \
  -0.793332, 0.825694 to \
  -2.35316, 0.825694 to \
  -2.35316, 1.67559 front fs empty border lc rgb '#549f' lw 0.1
set object 85 polygon from \
  -2.37591, 1.69548 to \
  -0.800832, 1.69548 to \
  -0.800832, 0.83559 to \
  -2.37591, 0.83559 to \
  -2.37591, 1.69548 front fs empty border lc rgb '#549f' lw 0.1
set object 86 polygon from \
  -2.39851, 1.71538 to \
  -0.808281, 1.71538 to \
  -0.808281, 0.845484 to \
  -2.39851, 0.845484 to \
  -2.39851, 1.71538 front fs empty border lc rgb '#549f' lw 0.1
set object 87 polygon from \
  -2.42097, 1.73527 to \
  -0.81568, 1.73527 to \
  -0.81568, 0.855377 to \
  -2.42097, 0.855377 to \
  -2.42097, 1.73527 front fs empty border lc rgb '#549f' lw 0.1
set object 88 polygon from \
  -2.44328, 1.75516 to \
  -0.823028, 1.75516 to \
  -0.823028, 0.865269 to \
  -2.44328, 0.865269 to \
  -2.44328, 1.75516 front fs empty border lc rgb '#549f' lw 0.1
set object 89 polygon from \
  -2.46544, 1.77505 to \
  -0.830325, 1.77505 to \
  -0.830325, 0.87516 to \
  -2.46544, 0.87516 to \
  -2.46544, 1.77505 front fs empty border lc rgb '#549f' lw 0.1
set object 90 polygon from \
  -2.48746, 1.79494 to \
  -0.837571, 1.79494 to \
  -0.837571, 0.885049 to \
  -2.48746, 0.885049 to \
  -2.48746, 1.79494 front fs empty border lc rgb '#549f' lw 0.1
set object 91 polygon from \
  -2.50932, 1.81482 to \
  -0.844765, 1.81482 to \
  -0.844765, 0.894937 to \
  -2.50932, 0.894937 to \
  -2.50932, 1.81482 front fs empty border lc rgb '#549f' lw 0.1
set object 92 polygon from \
  -2.53103, 1.83471 to \
  -0.851907, 1.83471 to \
  -0.851907, 0.904824 to \
  -2.53103, 0.904824 to \
  -2.53103, 1.83471 front fs empty border lc rgb '#549f' lw 0.1
set object 93 polygon from \
  -2.55259, 1.85459 to \
  -0.858997, 1.85459 to \
  -0.858997, 0.91471 to \
  -2.55259, 0.91471 to \
  -2.55259, 1.85459 front fs empty border lc rgb '#549f' lw 0.1
set object 94 polygon from \
  -2.574, 1.87448 to \
  -0.866035, 1.87448 to \
  -0.866035, 0.924594 to \
  -2.574, 0.924594 to \
  -2.574, 1.87448 front fs empty border lc rgb '#549f' lw 0.1
set object 95 polygon from \
  -2.59526, 1.89436 to \
  -0.873021, 1.89436 to \
  -0.873021, 0.934477 to \
  -2.59526, 0.934477 to \
  -2.59526, 1.89436 front fs empty border lc rgb '#549f' lw 0.1
set object 96 polygon from \
  -2.61637, 1.91424 to \
  -0.879954, 1.91424 to \
  -0.879954, 0.944359 to \
  -2.61637, 0.944359 to \
  -2.61637, 1.91424 front fs empty border lc rgb '#549f' lw 0.1
set object 97 polygon from \
  -2.63732, 1.93412 to \
  -0.886835, 1.93412 to \
  -0.886835, 0.95424 to \
  -2.63732, 0.95424 to \
  -2.63732, 1.93412 front fs empty border lc rgb '#549f' lw 0.1
set object 98 polygon from \
  -2.65812, 1.954 to \
  -0.893662, 1.954 to \
  -0.893662, 0.964119 to \
  -2.65812, 0.964119 to \
  -2.65812, 1.954 front fs empty border lc rgb '#549f' lw 0.1
set object 99 polygon from \
  -2.67877, 1.97387 to \
  -0.900436, 1.97387 to \
  -0.900436, 0.973997 to \
  -2.67877, 0.973997 to \
  -2.67877, 1.97387 front fs empty border lc rgb '#549f' lw 0.1
set object 100 polygon from \
  -2.69926, 1.99375 to \
  -0.907157, 1.99375 to \
  -0.907157, 0.983874 to \
  -2.69926, 0.983874 to \
  -2.69926, 1.99375 front fs empty border lc rgb '#549f' lw 0.1
set object 101 polygon from \
  -2.71959, 2.01362 to \
  -0.913825, 2.01362 to \
  -0.913825, 0.99375 to \
  -2.71959, 0.99375 to \
  -2.71959, 2.01362 front fs empty border lc rgb '#549f' lw 0.1
set object 102 polygon from \
  -2.73977, 2.0335 to \
  -0.920439, 2.0335 to \
  -0.920439, 1.00362 to \
  -2.73977, 1.00362 to \
  -2.73977, 2.0335 front fs empty border lc rgb '#549f' lw 0.1
set object 103 polygon from \
  -2.7598, 2.05337 to \
  -0.926999, 2.05337 to \
  -0.926999, 1.0135 to \
  -2.7598, 1.0135 to \
  -2.7598, 2.05337 front fs empty border lc rgb '#549f' lw 0.1
set object 104 polygon from \
  -2.77967, 2.07324 to \
  -0.933505, 2.07324 to \
  -0.933505, 1.02337 to \
  -2.77967, 1.02337 to \
  -2.77967, 2.07324 front fs empty border lc rgb '#549f' lw 0.1
set object 105 polygon from \
  -2.79938, 2.09311 to \
  -0.939958, 2.09311 to \
  -0.939958, 1.03324 to \
  -2.79938, 1.03324 to \
  -2.79938, 2.09311 front fs empty border lc rgb '#549f' lw 0.1
set object 106 polygon from \
  -2.81893, 2.11298 to \
  -0.946356, 2.11298 to \
  -0.946356, 1.04311 to \
  -2.81893, 1.04311 to \
  -2.81893, 2.11298 front fs empty border lc rgb '#549f' lw 0.1
set object 107 polygon from \
  -2.83833, 2.13284 to \
  -0.9527, 2.13284 to \
  -0.9527, 1.05298 to \
  -2.83833, 1.05298 to \
  -2.83833, 2.13284 front fs empty border lc rgb '#549f' lw 0.1
set object 108 polygon from \
  -2.85757, 2.15271 to \
  -0.958989, 2.15271 to \
  -0.958989, 1.06284 to \
  -2.85757, 1.06284 to \
  -2.85757, 2.15271 front fs empty border lc rgb '#549f' lw 0.1
set object 109 polygon from \
  -2.87665, 2.17257 to \
  -0.965224, 2.17257 to \
  -0.965224, 1.07271 to \
  -2.87665, 1.07271 to \
  -2.87665, 2.17257 front fs empty border lc rgb '#549f' lw 0.1
set object 110 polygon from \
  -2.89557, 2.19244 to \
  -0.971405, 2.19244 to \
  -0.971405, 1.08257 to \
  -2.89557, 1.08257 to \
  -2.89557, 2.19244 front fs empty border lc rgb '#549f' lw 0.1
set object 111 polygon from \
  -2.91434, 2.2123 to \
  -0.97753, 2.2123 to \
  -0.97753, 1.09244 to \
  -2.91434, 1.09244 to \
  -2.91434, 2.2123 front fs empty border lc rgb '#549f' lw 0.1
set object 112 polygon from \
  -2.93294, 2.23216 to \
  -0.983601, 2.23216 to \
  -0.983601, 1.1023 to \
  -2.93294, 1.1023 to \
  -2.93294, 2.23216 front fs empty border lc rgb '#549f' lw 0.1
set object 113 polygon from \
  -2.95139, 2.25202 to \
  -0.989618, 2.25202 to \
  -0.989618, 1.11216 to \
  -2.95139, 1.11216 to \
  -2.95139, 2.25202 front fs empty border lc rgb '#549f' lw 0.1
set object 114 polygon from \
  -2.96968, 2.27188 to \
  -0.995579, 2.27188 to \
  -0.995579, 1.12202 to \
  -2.96968, 1.12202 to \
  -2.96968, 2.27188 front fs empty border lc rgb '#549f' lw 0.1
set object 115 polygon from \
  -2.9878, 2.29173 to \
  -1.00149, 2.29173 to \
  -1.00149, 1.13188 to \
  -2.9878, 1.13188 to \
  -2.9878, 2.29173 front fs empty border lc rgb '#549f' lw 0.1
set object 116 polygon from \
  -3.00577, 2.31159 to \
  -1.00734, 2.31159 to \
  -1.00734, 1.14173 to \
  -3.00577, 1.14173 to \
  -3.00577, 2.31159 front fs empty border lc rgb '#549f' lw 0.1
set object 117 polygon from \
  -3.02358, 2.33144 to \
  -1.01313, 2.33144 to \
  -1.01313, 1.15159 to \
  -3.02358, 1.15159 to \
  -3.02358, 2.33144 front fs empty border lc rgb '#549f' lw 0.1
set object 118 polygon from \
  -3.04123, 2.3513 to \
  -1.01887, 2.3513 to \
  -1.01887, 1.16144 to \
  -3.04123, 1.16144 to \
  -3.04123, 2.3513 front fs empty border lc rgb '#549f' lw 0.1
set object 119 polygon from \
  -3.05871, 2.37115 to \
  -1.02456, 2.37115 to \
  -1.02456, 1.1713 to \
  -3.05871, 1.1713 to \
  -3.05871, 2.37115 front fs empty border lc rgb '#549f' lw 0.1
set object 120 polygon from \
  -3.07604, 2.391 to \
  -1.03019, 2.391 to \
  -1.03019, 1.18115 to \
  -3.07604, 1.18115 to \
  -3.07604, 2.391 front fs empty border lc rgb '#549f' lw 0.1
set object 121 polygon from \
  -3.09321, 2.41085 to \
  -1.03576, 2.41085 to \
  -1.03576, 1.191 to \
  -3.09321, 1.191 to \
  -3.09321, 2.41085 front fs empty border lc rgb '#549f' lw 0.1
set object 122 polygon from \
  -3.11022, 2.4307 to \
  -1.04128, 2.4307 to \
  -1.04128, 1.20085 to \
  -3.11022, 1.20085 to \
  -3.11022, 2.4307 front fs empty border lc rgb '#549f' lw 0.1
set object 123 polygon from \
  -3.12706, 2.45054 to \
  -1.04675, 2.45054 to \
  -1.04675, 1.2107 to \
  -3.12706, 1.2107 to \
  -3.12706, 2.45054 front fs empty border lc rgb '#549f' lw 0.1
set object 124 polygon from \
  -3.14375, 2.47039 to \
  -1.05216, 2.47039 to \
  -1.05216, 1.22054 to \
  -3.14375, 1.22054 to \
  -3.14375, 2.47039 front fs empty border lc rgb '#549f' lw 0.1
set object 125 polygon from \
  -3.16027, 2.49023 to \
  -1.05751, 2.49023 to \
  -1.05751, 1.23039 to \
  -3.16027, 1.23039 to \
  -3.16027, 2.49023 front fs empty border lc rgb '#549f' lw 0.1
set object 126 polygon from \
  -3.17664, 2.51008 to \
  -1.06281, 2.51008 to \
  -1.06281, 1.24023 to \
  -3.17664, 1.24023 to \
  -3.17664, 2.51008 front fs empty border lc rgb '#549f' lw 0.1
set object 127 polygon from \
  -3.19284, 2.52992 to \
  -1.06805, 2.52992 to \
  -1.06805, 1.25008 to \
  -3.19284, 1.25008 to \
  -3.19284, 2.52992 front fs empty border lc rgb '#549f' lw 0.1
set object 128 polygon from \
  -3.20888, 2.54976 to \
  -1.07324, 2.54976 to \
  -1.07324, 1.25992 to \
  -3.20888, 1.25992 to \
  -3.20888, 2.54976 front fs empty border lc rgb '#549f' lw 0.1
set object 129 polygon from \
  -3.22477, 2.5696 to \
  -1.07837, 2.5696 to \
  -1.07837, 1.26976 to \
  -3.22477, 1.26976 to \
  -3.22477, 2.5696 front fs empty border lc rgb '#549f' lw 0.1
set object 130 polygon from \
  -3.24049, 2.58944 to \
  -1.08344, 2.58944 to \
  -1.08344, 1.2796 to \
  -3.24049, 1.2796 to \
  -3.24049, 2.58944 front fs empty border lc rgb '#549f' lw 0.1
set object 131 polygon from \
  -3.25605, 2.60927 to \
  -1.08847, 2.60927 to \
  -1.08847, 1.28944 to \
  -3.25605, 1.28944 to \
  -3.25605, 2.60927 front fs empty border lc rgb '#549f' lw 0.1
set object 132 polygon from \
  -3.27145, 2.62911 to \
  -1.09343, 2.62911 to \
  -1.09343, 1.29927 to \
  -3.27145, 1.29927 to \
  -3.27145, 2.62911 front fs empty border lc rgb '#549f' lw 0.1
set object 133 polygon from \
  -3.28669, 2.64894 to \
  -1.09834, 2.64894 to \
  -1.09834, 1.30911 to \
  -3.28669, 1.30911 to \
  -3.28669, 2.64894 front fs empty border lc rgb '#549f' lw 0.1
set object 134 polygon from \
  -3.30177, 2.66878 to \
  -1.10319, 2.66878 to \
  -1.10319, 1.31894 to \
  -3.30177, 1.31894 to \
  -3.30177, 2.66878 front fs empty border lc rgb '#549f' lw 0.1
set object 135 polygon from \
  -3.31669, 2.68861 to \
  -1.10799, 2.68861 to \
  -1.10799, 1.32878 to \
  -3.31669, 1.32878 to \
  -3.31669, 2.68861 front fs empty border lc rgb '#549f' lw 0.1
set object 136 polygon from \
  -3.33145, 2.70844 to \
  -1.11274, 2.70844 to \
  -1.11274, 1.33861 to \
  -3.33145, 1.33861 to \
  -3.33145, 2.70844 front fs empty border lc rgb '#549f' lw 0.1
set object 137 polygon from \
  -3.34605, 2.72827 to \
  -1.11743, 2.72827 to \
  -1.11743, 1.34844 to \
  -3.34605, 1.34844 to \
  -3.34605, 2.72827 front fs empty border lc rgb '#549f' lw 0.1
set object 138 polygon from \
  -3.36049, 2.7481 to \
  -1.12206, 2.7481 to \
  -1.12206, 1.35827 to \
  -3.36049, 1.35827 to \
  -3.36049, 2.7481 front fs empty border lc rgb '#549f' lw 0.1
set object 139 polygon from \
  -3.37477, 2.76792 to \
  -1.12664, 2.76792 to \
  -1.12664, 1.3681 to \
  -3.37477, 1.3681 to \
  -3.37477, 2.76792 front fs empty border lc rgb '#549f' lw 0.1
set object 140 polygon from \
  -3.38889, 2.78775 to \
  -1.13116, 2.78775 to \
  -1.13116, 1.37792 to \
  -3.38889, 1.37792 to \
  -3.38889, 2.78775 front fs empty border lc rgb '#549f' lw 0.1
set object 141 polygon from \
  -3.40285, 2.80757 to \
  -1.13563, 2.80757 to \
  -1.13563, 1.38775 to \
  -3.40285, 1.38775 to \
  -3.40285, 2.80757 front fs empty border lc rgb '#549f' lw 0.1
set object 142 polygon from \
  -3.41665, 2.8274 to \
  -1.14004, 2.8274 to \
  -1.14004, 1.39757 to \
  -3.41665, 1.39757 to \
  -3.41665, 2.8274 front fs empty border lc rgb '#549f' lw 0.1
set object 143 polygon from \
  -3.43029, 2.84722 to \
  -1.1444, 2.84722 to \
  -1.1444, 1.4074 to \
  -3.43029, 1.4074 to \
  -3.43029, 2.84722 front fs empty border lc rgb '#549f' lw 0.1
set object 144 polygon from \
  -3.44378, 2.86704 to \
  -1.1487, 2.86704 to \
  -1.1487, 1.41722 to \
  -3.44378, 1.41722 to \
  -3.44378, 2.86704 front fs empty border lc rgb '#549f' lw 0.1
set object 145 polygon from \
  -3.4571, 2.88686 to \
  -1.15295, 2.88686 to \
  -1.15295, 1.42704 to \
  -3.4571, 1.42704 to \
  -3.4571, 2.88686 front fs empty border lc rgb '#549f' lw 0.1
set object 146 polygon from \
  -3.47027, 2.90668 to \
  -1.15714, 2.90668 to \
  -1.15714, 1.43686 to \
  -3.47027, 1.43686 to \
  -3.47027, 2.90668 front fs empty border lc rgb '#549f' lw 0.1
set object 147 polygon from \
  -3.48328, 2.92649 to \
  -1.16128, 2.92649 to \
  -1.16128, 1.44668 to \
  -3.48328, 1.44668 to \
  -3.48328, 2.92649 front fs empty border lc rgb '#549f' lw 0.1
set object 148 polygon from \
  -3.49613, 2.94631 to \
  -1.16536, 2.94631 to \
  -1.16536, 1.45649 to \
  -3.49613, 1.45649 to \
  -3.49613, 2.94631 front fs empty border lc rgb '#549f' lw 0.1
set object 149 polygon from \
  -3.50882, 2.96612 to \
  -1.16939, 2.96612 to \
  -1.16939, 1.46631 to \
  -3.50882, 1.46631 to \
  -3.50882, 2.96612 front fs empty border lc rgb '#549f' lw 0.1
set object 150 polygon from \
  -3.52136, 2.98594 to \
  -1.17336, 2.98594 to \
  -1.17336, 1.47612 to \
  -3.52136, 1.47612 to \
  -3.52136, 2.98594 front fs empty border lc rgb '#549f' lw 0.1
set object 151 polygon from \
  -3.53374, 3.00575 to \
  -1.17728, 3.00575 to \
  -1.17728, 1.48594 to \
  -3.53374, 1.48594 to \
  -3.53374, 3.00575 front fs empty border lc rgb '#549f' lw 0.1
set object 152 polygon from \
  -3.54596, 3.02556 to \
  -1.18115, 3.02556 to \
  -1.18115, 1.49575 to \
  -3.54596, 1.49575 to \
  -3.54596, 3.02556 front fs empty border lc rgb '#549f' lw 0.1
set object 153 polygon from \
  -3.55802, 3.04537 to \
  -1.18496, 3.04537 to \
  -1.18496, 1.50556 to \
  -3.55802, 1.50556 to \
  -3.55802, 3.04537 front fs empty border lc rgb '#549f' lw 0.1
set object 154 polygon from \
  -3.56993, 3.06518 to \
  -1.18872, 3.06518 to \
  -1.18872, 1.51537 to \
  -3.56993, 1.51537 to \
  -3.56993, 3.06518 front fs empty border lc rgb '#549f' lw 0.1
set object 155 polygon from \
  -3.58168, 3.08498 to \
  -1.19242, 3.08498 to \
  -1.19242, 1.52518 to \
  -3.58168, 1.52518 to \
  -3.58168, 3.08498 front fs empty border lc rgb '#549f' lw 0.1
set object 156 polygon from \
  -3.59328, 3.10479 to \
  -1.19607, 3.10479 to \
  -1.19607, 1.53498 to \
  -3.59328, 1.53498 to \
  -3.59328, 3.10479 front fs empty border lc rgb '#549f' lw 0.1
set object 157 polygon from \
  -3.60472, 3.12459 to \
  -1.19966, 3.12459 to \
  -1.19966, 1.54479 to \
  -3.60472, 1.54479 to \
  -3.60472, 3.12459 front fs empty border lc rgb '#549f' lw 0.1
set object 158 polygon from \
  -3.61601, 3.1444 to \
  -1.2032, 3.1444 to \
  -1.2032, 1.55459 to \
  -3.61601, 1.55459 to \
  -3.61601, 3.1444 front fs empty border lc rgb '#549f' lw 0.1
set object 159 polygon from \
  -3.62714, 3.1642 to \
  -1.20669, 3.1642 to \
  -1.20669, 1.5644 to \
  -3.62714, 1.5644 to \
  -3.62714, 3.1642 front fs empty border lc rgb '#549f' lw 0.1
set object 160 polygon from \
  -3.63812, 3.184 to \
  -1.21012, 3.184 to \
  -1.21012, 1.5742 to \
  -3.63812, 1.5742 to \
  -3.63812, 3.184 front fs empty border lc rgb '#549f' lw 0.1
set object 161 polygon from \
  -3.64894, 3.2038 to \
  -1.2135, 3.2038 to \
  -1.2135, 1.584 to \
  -3.64894, 1.584 to \
  -3.64894, 3.2038 front fs empty border lc rgb '#549f' lw 0.1
set object 162 polygon from \
  -3.65961, 3.2236 to \
  -1.21683, 3.2236 to \
  -1.21683, 1.5938 to \
  -3.65961, 1.5938 to \
  -3.65961, 3.2236 front fs empty border lc rgb '#549f' lw 0.1
set object 163 polygon from \
  -3.67013, 3.24339 to \
  -1.2201, 3.24339 to \
  -1.2201, 1.6036 to \
  -3.67013, 1.6036 to \
  -3.67013, 3.24339 front fs empty border lc rgb '#549f' lw 0.1
set object 164 polygon from \
  -3.68049, 3.26319 to \
  -1.22332, 3.26319 to \
  -1.22332, 1.61339 to \
  -3.68049, 1.61339 to \
  -3.68049, 3.26319 front fs empty border lc rgb '#549f' lw 0.1
set object 165 polygon from \
  -3.6907, 3.28298 to \
  -1.22649, 3.28298 to \
  -1.22649, 1.62319 to \
  -3.6907, 1.62319 to \
  -3.6907, 3.28298 front fs empty border lc rgb '#549f' lw 0.1
set object 166 polygon from \
  -3.70076, 3.30278 to \
  -1.22961, 3.30278 to \
  -1.22961, 1.63298 to \
  -3.70076, 1.63298 to \
  -3.70076, 3.30278 front fs empty border lc rgb '#549f' lw 0.1
set object 167 polygon from \
  -3.71067, 3.32257 to \
  -1.23267, 3.32257 to \
  -1.23267, 1.64278 to \
  -3.71067, 1.64278 to \
  -3.71067, 3.32257 front fs empty border lc rgb '#549f' lw 0.1
set object 168 polygon from \
  -3.72042, 3.34236 to \
  -1.23568, 3.34236 to \
  -1.23568, 1.65257 to \
  -3.72042, 1.65257 to \
  -3.72042, 3.34236 front fs empty border lc rgb '#549f' lw 0.1
set object 169 polygon from \
  -3.73003, 3.36215 to \
  -1.23863, 3.36215 to \
  -1.23863, 1.66236 to \
  -3.73003, 1.66236 to \
  -3.73003, 3.36215 front fs empty border lc rgb '#549f' lw 0.1
set object 170 polygon from \
  -3.73948, 3.38194 to \
  -1.24154, 3.38194 to \
  -1.24154, 1.67215 to \
  -3.73948, 1.67215 to \
  -3.73948, 3.38194 front fs empty border lc rgb '#549f' lw 0.1
set object 171 polygon from \
  -3.74879, 3.40172 to \
  -1.24439, 3.40172 to \
  -1.24439, 1.68194 to \
  -3.74879, 1.68194 to \
  -3.74879, 3.40172 front fs empty border lc rgb '#549f' lw 0.1
set object 172 polygon from \
  -3.75794, 3.42151 to \
  -1.24719, 3.42151 to \
  -1.24719, 1.69172 to \
  -3.75794, 1.69172 to \
  -3.75794, 3.42151 front fs empty border lc rgb '#549f' lw 0.1
set object 173 polygon from \
  -3.76695, 3.44129 to \
  -1.24994, 3.44129 to \
  -1.24994, 1.70151 to \
  -3.76695, 1.70151 to \
  -3.76695, 3.44129 front fs empty border lc rgb '#549f' lw 0.1
set object 174 polygon from \
  -3.7758, 3.46108 to \
  -1.25263, 3.46108 to \
  -1.25263, 1.71129 to \
  -3.7758, 1.71129 to \
  -3.7758, 3.46108 front fs empty border lc rgb '#549f' lw 0.1
set object 175 polygon from \
  -3.78453, 3.48086 to \
  -1.25528, 3.48086 to \
  -1.25528, 1.72108 to \
  -3.78453, 1.72108 to \
  -3.78453, 3.48086 front fs empty border lc rgb '#549f' lw 0.1
set object 176 polygon from \
  -3.7931, 3.50064 to \
  -1.25785, 3.50064 to \
  -1.25785, 1.73086 to \
  -3.7931, 1.73086 to \
  -3.7931, 3.50064 front fs empty border lc rgb '#549f' lw 0.1
set object 177 polygon from \
  -3.80153, 3.52042 to \
  -1.26038, 3.52042 to \
  -1.26038, 1.74064 to \
  -3.80153, 1.74064 to \
  -3.80153, 3.52042 front fs empty border lc rgb '#549f' lw 0.1
set object 178 polygon from \
  -3.80981, 3.5402 to \
  -1.26285, 3.5402 to \
  -1.26285, 1.75042 to \
  -3.80981, 1.75042 to \
  -3.80981, 3.5402 front fs empty border lc rgb '#549f' lw 0.1
set object 179 polygon from \
  -3.81794, 3.55997 to \
  -1.26528, 3.55997 to \
  -1.26528, 1.7602 to \
  -3.81794, 1.7602 to \
  -3.81794, 3.55997 front fs empty border lc rgb '#549f' lw 0.1
set object 180 polygon from \
  -3.82593, 3.57975 to \
  -1.26765, 3.57975 to \
  -1.26765, 1.76997 to \
  -3.82593, 1.76997 to \
  -3.82593, 3.57975 front fs empty border lc rgb '#549f' lw 0.1
set object 181 polygon from \
  -3.83377, 3.59952 to \
  -1.26997, 3.59952 to \
  -1.26997, 1.77975 to \
  -3.83377, 1.77975 to \
  -3.83377, 3.59952 front fs empty border lc rgb '#549f' lw 0.1
set object 182 polygon from \
  -3.84147, 3.6193 to \
  -1.27224, 3.6193 to \
  -1.27224, 1.78952 to \
  -3.84147, 1.78952 to \
  -3.84147, 3.6193 front fs empty border lc rgb '#549f' lw 0.1
set object 183 polygon from \
  -3.84902, 3.63907 to \
  -1.27446, 3.63907 to \
  -1.27446, 1.7993 to \
  -3.84902, 1.7993 to \
  -3.84902, 3.63907 front fs empty border lc rgb '#549f' lw 0.1
set object 184 polygon from \
  -3.85643, 3.65884 to \
  -1.27663, 3.65884 to \
  -1.27663, 1.80907 to \
  -3.85643, 1.80907 to \
  -3.85643, 3.65884 front fs empty border lc rgb '#549f' lw 0.1
set object 185 polygon from \
  -3.86369, 3.67861 to \
  -1.27875, 3.67861 to \
  -1.27875, 1.81884 to \
  -3.86369, 1.81884 to \
  -3.86369, 3.67861 front fs empty border lc rgb '#549f' lw 0.1
set object 186 polygon from \
  -3.87081, 3.69838 to \
  -1.28082, 3.69838 to \
  -1.28082, 1.82861 to \
  -3.87081, 1.82861 to \
  -3.87081, 3.69838 front fs empty border lc rgb '#549f' lw 0.1
set object 187 polygon from \
  -3.87778, 3.71814 to \
  -1.28284, 3.71814 to \
  -1.28284, 1.83838 to \
  -3.87778, 1.83838 to \
  -3.87778, 3.71814 front fs empty border lc rgb '#549f' lw 0.1
set object 188 polygon from \
  -3.88462, 3.73791 to \
  -1.28481, 3.73791 to \
  -1.28481, 1.84814 to \
  -3.88462, 1.84814 to \
  -3.88462, 3.73791 front fs empty border lc rgb '#549f' lw 0.1
set object 189 polygon from \
  -3.89131, 3.75767 to \
  -1.28673, 3.75767 to \
  -1.28673, 1.85791 to \
  -3.89131, 1.85791 to \
  -3.89131, 3.75767 front fs empty border lc rgb '#549f' lw 0.1
set object 190 polygon from \
  -3.89786, 3.77744 to \
  -1.2886, 3.77744 to \
  -1.2886, 1.86767 to \
  -3.89786, 1.86767 to \
  -3.89786, 3.77744 front fs empty border lc rgb '#549f' lw 0.1
set object 191 polygon from \
  -3.90426, 3.7972 to \
  -1.29043, 3.7972 to \
  -1.29043, 1.87744 to \
  -3.90426, 1.87744 to \
  -3.90426, 3.7972 front fs empty border lc rgb '#549f' lw 0.1
set object 192 polygon from \
  -3.91053, 3.81696 to \
  -1.2922, 3.81696 to \
  -1.2922, 1.8872 to \
  -3.91053, 1.8872 to \
  -3.91053, 3.81696 front fs empty border lc rgb '#549f' lw 0.1
set object 193 polygon from \
  -3.91666, 3.83672 to \
  -1.29393, 3.83672 to \
  -1.29393, 1.89696 to \
  -3.91666, 1.89696 to \
  -3.91666, 3.83672 front fs empty border lc rgb '#549f' lw 0.1
set object 194 polygon from \
  -3.92264, 3.85648 to \
  -1.2956, 3.85648 to \
  -1.2956, 1.90672 to \
  -3.92264, 1.90672 to \
  -3.92264, 3.85648 front fs empty border lc rgb '#549f' lw 0.1
set object 195 polygon from \
  -3.92849, 3.87623 to \
  -1.29723, 3.87623 to \
  -1.29723, 1.91648 to \
  -3.92849, 1.91648 to \
  -3.92849, 3.87623 front fs empty border lc rgb '#549f' lw 0.1
set object 196 polygon from \
  -3.9342, 3.89599 to \
  -1.29881, 3.89599 to \
  -1.29881, 1.92623 to \
  -3.9342, 1.92623 to \
  -3.9342, 3.89599 front fs empty border lc rgb '#549f' lw 0.1
set object 197 polygon from \
  -3.93977, 3.91574 to \
  -1.30034, 3.91574 to \
  -1.30034, 1.93599 to \
  -3.93977, 1.93599 to \
  -3.93977, 3.91574 front fs empty border lc rgb '#549f' lw 0.1
set object 198 polygon from \
  -3.9452, 3.9355 to \
  -1.30182, 3.9355 to \
  -1.30182, 1.94574 to \
  -3.9452, 1.94574 to \
  -3.9452, 3.9355 front fs empty border lc rgb '#549f' lw 0.1
set object 199 polygon from \
  -3.9505, 3.95525 to \
  -1.30326, 3.95525 to \
  -1.30326, 1.9555 to \
  -3.9505, 1.9555 to \
  -3.9505, 3.95525 front fs empty border lc rgb '#549f' lw 0.1
set object 200 polygon from \
  -3.95566, 3.975 to \
  -1.30465, 3.975 to \
  -1.30465, 1.96525 to \
  -3.95566, 1.96525 to \
  -3.95566, 3.975 front fs empty border lc rgb '#549f' lw 0.1
set object 201 polygon from \
  -3.96068, 3.99475 to \
  -1.30599, 3.99475 to \
  -1.30599, 1.975 to \
  -3.96068, 1.975 to \
  -3.96068, 3.99475 front fs empty border lc rgb '#549f' lw 0.1
set object 202 polygon from \
  -3.96556, 4.0145 to \
  -1.30728, 4.0145 to \
  -1.30728, 1.98475 to \
  -3.96556, 1.98475 to \
  -3.96556, 4.0145 front fs empty border lc rgb '#549f' lw 0.1
set object 203 polygon from \
  -3.97031, 4.03424 to \
  -1.30853, 4.03424 to \
  -1.30853, 1.9945 to \
  -3.97031, 1.9945 to \
  -3.97031, 4.03424 front fs empty border lc rgb '#549f' lw 0.1
set object 204 polygon from \
  -3.97493, 4.05399 to \
  -1.30973, 4.05399 to \
  -1.30973, 2.00424 to \
  -3.97493, 2.00424 to \
  -3.97493, 4.05399 front fs empty border lc rgb '#549f' lw 0.1
set object 205 polygon from \
  -3.97941, 4.07373 to \
  -1.31088, 4.07373 to \
  -1.31088, 2.01399 to \
  -3.97941, 2.01399 to \
  -3.97941, 4.07373 front fs empty border lc rgb '#549f' lw 0.1
set object 206 polygon from \
  -3.98376, 4.09348 to \
  -1.31199, 4.09348 to \
  -1.31199, 2.02373 to \
  -3.98376, 2.02373 to \
  -3.98376, 4.09348 front fs empty border lc rgb '#549f' lw 0.1
set object 207 polygon from \
  -3.98797, 4.11322 to \
  -1.31305, 4.11322 to \
  -1.31305, 2.03348 to \
  -3.98797, 2.03348 to \
  -3.98797, 4.11322 front fs empty border lc rgb '#549f' lw 0.1
set object 208 polygon from \
  -3.99205, 4.13296 to \
  -1.31406, 4.13296 to \
  -1.31406, 2.04322 to \
  -3.99205, 2.04322 to \
  -3.99205, 4.13296 front fs empty border lc rgb '#549f' lw 0.1
set object 209 polygon from \
  -3.996, 4.1527 to \
  -1.31503, 4.1527 to \
  -1.31503, 2.05296 to \
  -3.996, 2.05296 to \
  -3.996, 4.1527 front fs empty border lc rgb '#549f' lw 0.1
set object 210 polygon from \
  -3.99982, 4.17244 to \
  -1.31595, 4.17244 to \
  -1.31595, 2.0627 to \
  -3.99982, 2.0627 to \
  -3.99982, 4.17244 front fs empty border lc rgb '#549f' lw 0.1
set object 211 polygon from \
  -4.0035, 4.19217 to \
  -1.31683, 4.19217 to \
  -1.31683, 2.07244 to \
  -4.0035, 2.07244 to \
  -4.0035, 4.19217 front fs empty border lc rgb '#549f' lw 0.1
set object 212 polygon from \
  -4.00706, 4.21191 to \
  -1.31766, 4.21191 to \
  -1.31766, 2.08217 to \
  -4.00706, 2.08217 to \
  -4.00706, 4.21191 front fs empty border lc rgb '#549f' lw 0.1
set object 213 polygon from \
  -4.01048, 4.23164 to \
  -1.31844, 4.23164 to \
  -1.31844, 2.09191 to \
  -4.01048, 2.09191 to \
  -4.01048, 4.23164 front fs empty border lc rgb '#549f' lw 0.1
set object 214 polygon from \
  -4.01378, 4.25138 to \
  -1.31918, 4.25138 to \
  -1.31918, 2.10164 to \
  -4.01378, 2.10164 to \
  -4.01378, 4.25138 front fs empty border lc rgb '#549f' lw 0.1
set object 215 polygon from \
  -4.01694, 4.27111 to \
  -1.31988, 4.27111 to \
  -1.31988, 2.11138 to \
  -4.01694, 2.11138 to \
  -4.01694, 4.27111 front fs empty border lc rgb '#549f' lw 0.1
set object 216 polygon from \
  -4.01998, 4.29084 to \
  -1.32053, 4.29084 to \
  -1.32053, 2.12111 to \
  -4.01998, 2.12111 to \
  -4.01998, 4.29084 front fs empty border lc rgb '#549f' lw 0.1
set object 217 polygon from \
  -4.02289, 4.31057 to \
  -1.32114, 4.31057 to \
  -1.32114, 2.13084 to \
  -4.02289, 2.13084 to \
  -4.02289, 4.31057 front fs empty border lc rgb '#549f' lw 0.1
set object 218 polygon from \
  -4.02567, 4.3303 to \
  -1.3217, 4.3303 to \
  -1.3217, 2.14057 to \
  -4.02567, 2.14057 to \
  -4.02567, 4.3303 front fs empty border lc rgb '#549f' lw 0.1
set object 219 polygon from \
  -4.02832, 4.35002 to \
  -1.32222, 4.35002 to \
  -1.32222, 2.1503 to \
  -4.02832, 2.1503 to \
  -4.02832, 4.35002 front fs empty border lc rgb '#549f' lw 0.1
set object 220 polygon from \
  -4.03085, 4.36975 to \
  -1.32269, 4.36975 to \
  -1.32269, 2.16002 to \
  -4.03085, 2.16002 to \
  -4.03085, 4.36975 front fs empty border lc rgb '#549f' lw 0.1
set object 221 polygon from \
  -4.03325, 4.38947 to \
  -1.32312, 4.38947 to \
  -1.32312, 2.16975 to \
  -4.03325, 2.16975 to \
  -4.03325, 4.38947 front fs empty border lc rgb '#549f' lw 0.1
set object 222 polygon from \
  -4.03552, 4.4092 to \
  -1.32351, 4.4092 to \
  -1.32351, 2.17947 to \
  -4.03552, 2.17947 to \
  -4.03552, 4.4092 front fs empty border lc rgb '#549f' lw 0.1
set object 223 polygon from \
  -4.03767, 4.42892 to \
  -1.32385, 4.42892 to \
  -1.32385, 2.1892 to \
  -4.03767, 2.1892 to \
  -4.03767, 4.42892 front fs empty border lc rgb '#549f' lw 0.1
set object 224 polygon from \
  -4.0397, 4.44864 to \
  -1.32415, 4.44864 to \
  -1.32415, 2.19892 to \
  -4.0397, 2.19892 to \
  -4.0397, 4.44864 front fs empty border lc rgb '#549f' lw 0.1
set object 225 polygon from \
  -4.0416, 4.46836 to \
  -1.32441, 4.46836 to \
  -1.32441, 2.20864 to \
  -4.0416, 2.20864 to \
  -4.0416, 4.46836 front fs empty border lc rgb '#549f' lw 0.1
set object 226 polygon from \
  -4.04338, 4.48808 to \
  -1.32462, 4.48808 to \
  -1.32462, 2.21836 to \
  -4.04338, 2.21836 to \
  -4.04338, 4.48808 front fs empty border lc rgb '#549f' lw 0.1
set object 227 polygon from \
  -4.04503, 4.50779 to \
  -1.32479, 4.50779 to \
  -1.32479, 2.22808 to \
  -4.04503, 2.22808 to \
  -4.04503, 4.50779 front fs empty border lc rgb '#549f' lw 0.1
set object 228 polygon from \
  -4.04656, 4.52751 to \
  -1.32492, 4.52751 to \
  -1.32492, 2.23779 to \
  -4.04656, 2.23779 to \
  -4.04656, 4.52751 front fs empty border lc rgb '#549f' lw 0.1
set object 229 polygon from \
  -4.04797, 4.54722 to \
  -1.32501, 4.54722 to \
  -1.32501, 2.24751 to \
  -4.04797, 2.24751 to \
  -4.04797, 4.54722 front fs empty border lc rgb '#549f' lw 0.1
set object 230 polygon from \
  -4.04926, 4.56694 to \
  -1.32505, 4.56694 to \
  -1.32505, 2.25722 to \
  -4.04926, 2.25722 to \
  -4.04926, 4.56694 front fs empty border lc rgb '#549f' lw 0.1
set object 231 polygon from \
  -4.05043, 4.58665 to \
  -1.32502, 4.58665 to \
  -1.32502, 2.26694 to \
  -4.05043, 2.26694 to \
  -4.05043, 4.58665 front fs empty border lc rgb '#549f' lw 0.1
set object 232 polygon from \
  -4.05148, 4.60636 to \
  -1.32494, 4.60636 to \
  -1.32494, 2.27665 to \
  -4.05148, 2.27665 to \
  -4.05148, 4.60636 front fs empty border lc rgb '#549f' lw 0.1
set object 233 polygon from \
  -4.0524, 4.62607 to \
  -1.32482, 4.62607 to \
  -1.32482, 2.28636 to \
  -4.0524, 2.28636 to \
  -4.0524, 4.62607 front fs empty border lc rgb '#549f' lw 0.1
set object 234 polygon from \
  -4.05321, 4.64578 to \
  -1.32465, 4.64578 to \
  -1.32465, 2.29607 to \
  -4.05321, 2.29607 to \
  -4.05321, 4.64578 front fs empty border lc rgb '#549f' lw 0.1
set object 235 polygon from \
  -4.0539, 4.66548 to \
  -1.32445, 4.66548 to \
  -1.32445, 2.30578 to \
  -4.0539, 2.30578 to \
  -4.0539, 4.66548 front fs empty border lc rgb '#549f' lw 0.1
set object 236 polygon from \
  -4.05447, 4.68519 to \
  -1.3242, 4.68519 to \
  -1.3242, 2.31548 to \
  -4.05447, 2.31548 to \
  -4.05447, 4.68519 front fs empty border lc rgb '#549f' lw 0.1
set object 237 polygon from \
  -4.05492, 4.70489 to \
  -1.32392, 4.70489 to \
  -1.32392, 2.32519 to \
  -4.05492, 2.32519 to \
  -4.05492, 4.70489 front fs empty border lc rgb '#549f' lw 0.1
set object 238 polygon from \
  -4.05526, 4.7246 to \
  -1.32359, 4.7246 to \
  -1.32359, 2.33489 to \
  -4.05526, 2.33489 to \
  -4.05526, 4.7246 front fs empty border lc rgb '#549f' lw 0.1
set object 239 polygon from \
  -4.05548, 4.7443 to \
  -1.32323, 4.7443 to \
  -1.32323, 2.3446 to \
  -4.05548, 2.3446 to \
  -4.05548, 4.7443 front fs empty border lc rgb '#549f' lw 0.1
set object 240 polygon from \
  -4.05558, 4.764 to \
  -1.32282, 4.764 to \
  -1.32282, 2.3543 to \
  -4.05558, 2.3543 to \
  -4.05558, 4.764 front fs empty border lc rgb '#549f' lw 0.1
set object 241 polygon from \
  -4.05558, 4.7837 to \
  -1.32238, 4.7837 to \
  -1.32238, 2.364 to \
  -4.05558, 2.364 to \
  -4.05558, 4.7837 front fs empty border lc rgb '#549f' lw 0.1
set object 242 polygon from \
  -4.05557, 4.8034 to \
  -1.32189, 4.8034 to \
  -1.32189, 2.3737 to \
  -4.05557, 2.3737 to \
  -4.05557, 4.8034 front fs empty border lc rgb '#549f' lw 0.1
set object 243 polygon from \
  -4.05544, 4.82309 to \
  -1.32137, 4.82309 to \
  -1.32137, 2.3834 to \
  -4.05544, 2.3834 to \
  -4.05544, 4.82309 front fs empty border lc rgb '#549f' lw 0.1
set object 244 polygon from \
  -4.0552, 4.84279 to \
  -1.3208, 4.84279 to \
  -1.3208, 2.39309 to \
  -4.0552, 2.39309 to \
  -4.0552, 4.84279 front fs empty border lc rgb '#549f' lw 0.1
set object 245 polygon from \
  -4.05484, 4.86248 to \
  -1.3202, 4.86248 to \
  -1.3202, 2.40279 to \
  -4.05484, 2.40279 to \
  -4.05484, 4.86248 front fs empty border lc rgb '#549f' lw 0.1
set object 246 polygon from \
  -4.05437, 4.88218 to \
  -1.31956, 4.88218 to \
  -1.31956, 2.41248 to \
  -4.05437, 2.41248 to \
  -4.05437, 4.88218 front fs empty border lc rgb '#549f' lw 0.1
set object 247 polygon from \
  -4.05379, 4.90187 to \
  -1.31886, 4.90187 to \
  -1.31886, 2.42218 to \
  -4.05379, 2.42218 to \
  -4.05379, 4.90187 front fs empty border lc rgb '#549f' lw 0.1
set object 248 polygon from \
  -4.05311, 4.92156 to \
  -1.3181, 4.92156 to \
  -1.3181, 2.43187 to \
  -4.05311, 2.43187 to \
  -4.05311, 4.92156 front fs empty border lc rgb '#549f' lw 0.1
set object 249 polygon from \
  -4.05235, 4.94125 to \
  -1.31731, 4.94125 to \
  -1.31731, 2.44156 to \
  -4.05235, 2.44156 to \
  -4.05235, 4.94125 front fs empty border lc rgb '#549f' lw 0.1
set object 250 polygon from \
  -4.05147, 4.96094 to \
  -1.31647, 4.96094 to \
  -1.31647, 2.45125 to \
  -4.05147, 2.45125 to \
  -4.05147, 4.96094 front fs empty border lc rgb '#549f' lw 0.1
set object 251 polygon from \
  -4.05048, 4.98062 to \
  -1.3156, 4.98062 to \
  -1.3156, 2.46094 to \
  -4.05048, 2.46094 to \
  -4.05048, 4.98062 front fs empty border lc rgb '#549f' lw 0.1
set object 252 polygon from \
  -4.04938, 5.00031 to \
  -1.31469, 5.00031 to \
  -1.31469, 2.47062 to \
  -4.04938, 2.47062 to \
  -4.04938, 5.00031 front fs empty border lc rgb '#549f' lw 0.1
set object 253 polygon from \
  -4.04817, 5.01999 to \
  -1.31374, 5.01999 to \
  -1.31374, 2.48031 to \
  -4.04817, 2.48031 to \
  -4.04817, 5.01999 front fs empty border lc rgb '#549f' lw 0.1
set object 254 polygon from \
  -4.04685, 5.03968 to \
  -1.31275, 5.03968 to \
  -1.31275, 2.48999 to \
  -4.04685, 2.48999 to \
  -4.04685, 5.03968 front fs empty border lc rgb '#549f' lw 0.1
set object 255 polygon from \
  -4.04543, 5.05936 to \
  -1.31173, 5.05936 to \
  -1.31173, 2.49968 to \
  -4.04543, 2.49968 to \
  -4.04543, 5.05936 front fs empty border lc rgb '#549f' lw 0.1
set object 256 polygon from \
  -4.04389, 5.07904 to \
  -1.31067, 5.07904 to \
  -1.31067, 2.50936 to \
  -4.04389, 2.50936 to \
  -4.04389, 5.07904 front fs empty border lc rgb '#549f' lw 0.1
set object 257 polygon from \
  -4.04225, 5.09872 to \
  -1.30958, 5.09872 to \
  -1.30958, 2.51904 to \
  -4.04225, 2.51904 to \
  -4.04225, 5.09872 front fs empty border lc rgb '#549f' lw 0.1
set object 258 polygon from \
  -4.0405, 5.1184 to \
  -1.30845, 5.1184 to \
  -1.30845, 2.52872 to \
  -4.0405, 2.52872 to \
  -4.0405, 5.1184 front fs empty border lc rgb '#549f' lw 0.1
set object 259 polygon from \
  -4.03864, 5.13807 to \
  -1.30728, 5.13807 to \
  -1.30728, 2.5384 to \
  -4.03864, 2.5384 to \
  -4.03864, 5.13807 front fs empty border lc rgb '#549f' lw 0.1
set object 260 polygon from \
  -4.03668, 5.15775 to \
  -1.30607, 5.15775 to \
  -1.30607, 2.54807 to \
  -4.03668, 2.54807 to \
  -4.03668, 5.15775 front fs empty border lc rgb '#549f' lw 0.1
set object 261 polygon from \
  -4.03461, 5.17742 to \
  -1.30483, 5.17742 to \
  -1.30483, 2.55775 to \
  -4.03461, 2.55775 to \
  -4.03461, 5.17742 front fs empty border lc rgb '#549f' lw 0.1
set object 262 polygon from \
  -4.03244, 5.1971 to \
  -1.30356, 5.1971 to \
  -1.30356, 2.56742 to \
  -4.03244, 2.56742 to \
  -4.03244, 5.1971 front fs empty border lc rgb '#549f' lw 0.1
set object 263 polygon from \
  -4.03016, 5.21677 to \
  -1.30225, 5.21677 to \
  -1.30225, 2.5771 to \
  -4.03016, 2.5771 to \
  -4.03016, 5.21677 front fs empty border lc rgb '#549f' lw 0.1
set object 264 polygon from \
  -4.02778, 5.23644 to \
  -1.3009, 5.23644 to \
  -1.3009, 2.58677 to \
  -4.02778, 2.58677 to \
  -4.02778, 5.23644 front fs empty border lc rgb '#549f' lw 0.1
set object 265 polygon from \
  -4.02529, 5.25611 to \
  -1.29952, 5.25611 to \
  -1.29952, 2.59644 to \
  -4.02529, 2.59644 to \
  -4.02529, 5.25611 front fs empty border lc rgb '#549f' lw 0.1
set object 266 polygon from \
  -4.0227, 5.27578 to \
  -1.29811, 5.27578 to \
  -1.29811, 2.60611 to \
  -4.0227, 2.60611 to \
  -4.0227, 5.27578 front fs empty border lc rgb '#549f' lw 0.1
set object 267 polygon from \
  -4.02001, 5.29544 to \
  -1.29666, 5.29544 to \
  -1.29666, 2.61578 to \
  -4.02001, 2.61578 to \
  -4.02001, 5.29544 front fs empty border lc rgb '#549f' lw 0.1
set object 268 polygon from \
  -4.01722, 5.31511 to \
  -1.29517, 5.31511 to \
  -1.29517, 2.62544 to \
  -4.01722, 2.62544 to \
  -4.01722, 5.31511 front fs empty border lc rgb '#549f' lw 0.1
set object 269 polygon from \
  -4.01433, 5.33477 to \
  -1.29259, 5.33477 to \
  -1.29259, 2.63511 to \
  -4.01433, 2.63511 to \
  -4.01433, 5.33477 front fs empty border lc rgb '#549f' lw 0.1
set object 270 polygon from \
  -4.0124, 5.35444 to \
  -1.28928, 5.35444 to \
  -1.28928, 2.64477 to \
  -4.0124, 2.64477 to \
  -4.0124, 5.35444 front fs empty border lc rgb '#549f' lw 0.1
set object 271 polygon from \
  -4.01107, 5.3741 to \
  -1.28595, 5.3741 to \
  -1.28595, 2.65444 to \
  -4.01107, 2.65444 to \
  -4.01107, 5.3741 front fs empty border lc rgb '#549f' lw 0.1
set object 272 polygon from \
  -4.00961, 5.39376 to \
  -1.28261, 5.39376 to \
  -1.28261, 2.6641 to \
  -4.00961, 2.6641 to \
  -4.00961, 5.39376 front fs empty border lc rgb '#549f' lw 0.1
set object 273 polygon from \
  -4.00804, 5.41342 to \
  -1.27926, 5.41342 to \
  -1.27926, 2.67376 to \
  -4.00804, 2.67376 to \
  -4.00804, 5.41342 front fs empty border lc rgb '#549f' lw 0.1
set object 274 polygon from \
  -4.00634, 5.43308 to \
  -1.2759, 5.43308 to \
  -1.2759, 2.68342 to \
  -4.00634, 2.68342 to \
  -4.00634, 5.43308 front fs empty border lc rgb '#549f' lw 0.1
set object 275 polygon from \
  -4.00453, 5.45273 to \
  -1.27252, 5.45273 to \
  -1.27252, 2.69308 to \
  -4.00453, 2.69308 to \
  -4.00453, 5.45273 front fs empty border lc rgb '#549f' lw 0.1
set object 276 polygon from \
  -4.0026, 5.47239 to \
  -1.26914, 5.47239 to \
  -1.26914, 2.70273 to \
  -4.0026, 2.70273 to \
  -4.0026, 5.47239 front fs empty border lc rgb '#549f' lw 0.1
set object 277 polygon from \
  -4.00055, 5.49204 to \
  -1.26574, 5.49204 to \
  -1.26574, 2.71239 to \
  -4.00055, 2.71239 to \
  -4.00055, 5.49204 front fs empty border lc rgb '#549f' lw 0.1
set object 278 polygon from \
  -3.99839, 5.5117 to \
  -1.26232, 5.5117 to \
  -1.26232, 2.72204 to \
  -3.99839, 2.72204 to \
  -3.99839, 5.5117 front fs empty border lc rgb '#549f' lw 0.1
set object 279 polygon from \
  -3.99611, 5.53135 to \
  -1.2589, 5.53135 to \
  -1.2589, 2.7317 to \
  -3.99611, 2.7317 to \
  -3.99611, 5.53135 front fs empty border lc rgb '#549f' lw 0.1
set object 280 polygon from \
  -3.99371, 5.551 to \
  -1.25547, 5.551 to \
  -1.25547, 2.74135 to \
  -3.99371, 2.74135 to \
  -3.99371, 5.551 front fs empty border lc rgb '#549f' lw 0.1
set object 281 polygon from \
  -3.9912, 5.57065 to \
  -1.25202, 5.57065 to \
  -1.25202, 2.751 to \
  -3.9912, 2.751 to \
  -3.9912, 5.57065 front fs empty border lc rgb '#549f' lw 0.1
set object 282 polygon from \
  -3.98857, 5.5903 to \
  -1.24856, 5.5903 to \
  -1.24856, 2.76065 to \
  -3.98857, 2.76065 to \
  -3.98857, 5.5903 front fs empty border lc rgb '#549f' lw 0.1
set object 283 polygon from \
  -3.98583, 5.60994 to \
  -1.24509, 5.60994 to \
  -1.24509, 2.7703 to \
  -3.98583, 2.7703 to \
  -3.98583, 5.60994 front fs empty border lc rgb '#549f' lw 0.1
set object 284 polygon from \
  -3.98298, 5.62959 to \
  -1.24162, 5.62959 to \
  -1.24162, 2.77994 to \
  -3.98298, 2.77994 to \
  -3.98298, 5.62959 front fs empty border lc rgb '#549f' lw 0.1
set object 285 polygon from \
  -3.98001, 5.64923 to \
  -1.23813, 5.64923 to \
  -1.23813, 2.78959 to \
  -3.98001, 2.78959 to \
  -3.98001, 5.64923 front fs empty border lc rgb '#549f' lw 0.1
set object 286 polygon from \
  -3.97693, 5.66888 to \
  -1.23463, 5.66888 to \
  -1.23463, 2.79923 to \
  -3.97693, 2.79923 to \
  -3.97693, 5.66888 front fs empty border lc rgb '#549f' lw 0.1
set object 287 polygon from \
  -3.97374, 5.68852 to \
  -1.23112, 5.68852 to \
  -1.23112, 2.80888 to \
  -3.97374, 2.80888 to \
  -3.97374, 5.68852 front fs empty border lc rgb '#549f' lw 0.1
set object 288 polygon from \
  -3.97044, 5.70816 to \
  -1.22761, 5.70816 to \
  -1.22761, 2.81852 to \
  -3.97044, 2.81852 to \
  -3.97044, 5.70816 front fs empty border lc rgb '#549f' lw 0.1
set object 289 polygon from \
  -3.96702, 5.7278 to \
  -1.22408, 5.7278 to \
  -1.22408, 2.82816 to \
  -3.96702, 2.82816 to \
  -3.96702, 5.7278 front fs empty border lc rgb '#549f' lw 0.1
set object 290 polygon from \
  -3.9635, 5.74744 to \
  -1.22054, 5.74744 to \
  -1.22054, 2.8378 to \
  -3.9635, 2.8378 to \
  -3.9635, 5.74744 front fs empty border lc rgb '#549f' lw 0.1
set object 291 polygon from \
  -3.95987, 5.76707 to \
  -1.21699, 5.76707 to \
  -1.21699, 2.84744 to \
  -3.95987, 2.84744 to \
  -3.95987, 5.76707 front fs empty border lc rgb '#549f' lw 0.1
set object 292 polygon from \
  -3.95612, 5.78671 to \
  -1.21344, 5.78671 to \
  -1.21344, 2.85707 to \
  -3.95612, 2.85707 to \
  -3.95612, 5.78671 front fs empty border lc rgb '#549f' lw 0.1
set object 293 polygon from \
  -3.95227, 5.80634 to \
  -1.20988, 5.80634 to \
  -1.20988, 2.86671 to \
  -3.95227, 2.86671 to \
  -3.95227, 5.80634 front fs empty border lc rgb '#549f' lw 0.1
set object 294 polygon from \
  -3.9483, 5.82598 to \
  -1.20631, 5.82598 to \
  -1.20631, 2.87634 to \
  -3.9483, 2.87634 to \
  -3.9483, 5.82598 front fs empty border lc rgb '#549f' lw 0.1
set object 295 polygon from \
  -3.94423, 5.84561 to \
  -1.20274, 5.84561 to \
  -1.20274, 2.88598 to \
  -3.94423, 2.88598 to \
  -3.94423, 5.84561 front fs empty border lc rgb '#549f' lw 0.1
set object 296 polygon from \
  -3.94005, 5.86524 to \
  -1.19916, 5.86524 to \
  -1.19916, 2.89561 to \
  -3.94005, 2.89561 to \
  -3.94005, 5.86524 front fs empty border lc rgb '#549f' lw 0.1
set object 297 polygon from \
  -3.93575, 5.88487 to \
  -1.19558, 5.88487 to \
  -1.19558, 2.90524 to \
  -3.93575, 2.90524 to \
  -3.93575, 5.88487 front fs empty border lc rgb '#549f' lw 0.1
set object 298 polygon from \
  -3.93135, 5.9045 to \
  -1.19199, 5.9045 to \
  -1.19199, 2.91487 to \
  -3.93135, 2.91487 to \
  -3.93135, 5.9045 front fs empty border lc rgb '#549f' lw 0.1
set object 299 polygon from \
  -3.92685, 5.92412 to \
  -1.18839, 5.92412 to \
  -1.18839, 2.9245 to \
  -3.92685, 2.9245 to \
  -3.92685, 5.92412 front fs empty border lc rgb '#549f' lw 0.1
set object 300 polygon from \
  -3.92224, 5.94375 to \
  -1.18478, 5.94375 to \
  -1.18478, 2.93412 to \
  -3.92224, 2.93412 to \
  -3.92224, 5.94375 front fs empty border lc rgb '#549f' lw 0.1
set object 301 polygon from \
  -3.91752, 5.96337 to \
  -1.18118, 5.96337 to \
  -1.18118, 2.94375 to \
  -3.91752, 2.94375 to \
  -3.91752, 5.96337 front fs empty border lc rgb '#549f' lw 0.1
set object 302 polygon from \
  -3.91269, 5.983 to \
  -1.17757, 5.983 to \
  -1.17757, 2.95337 to \
  -3.91269, 2.95337 to \
  -3.91269, 5.983 front fs empty border lc rgb '#549f' lw 0.1
set object 303 polygon from \
  -3.90775, 6.00262 to \
  -1.17397, 6.00262 to \
  -1.17397, 2.963 to \
  -3.90775, 2.963 to \
  -3.90775, 6.00262 front fs empty border lc rgb '#549f' lw 0.1
set object 304 polygon from \
  -3.9027, 6.02224 to \
  -1.17037, 6.02224 to \
  -1.17037, 2.97262 to \
  -3.9027, 2.97262 to \
  -3.9027, 6.02224 front fs empty border lc rgb '#549f' lw 0.1
set object 305 polygon from \
  -3.89755, 6.04186 to \
  -1.16676, 6.04186 to \
  -1.16676, 2.98224 to \
  -3.89755, 2.98224 to \
  -3.89755, 6.04186 front fs empty border lc rgb '#549f' lw 0.1
set object 306 polygon from \
  -3.89228, 6.06148 to \
  -1.16316, 6.06148 to \
  -1.16316, 2.99186 to \
  -3.89228, 2.99186 to \
  -3.89228, 6.06148 front fs empty border lc rgb '#549f' lw 0.1
set object 307 polygon from \
  -3.8869, 6.08109 to \
  -1.15957, 6.08109 to \
  -1.15957, 3.00148 to \
  -3.8869, 3.00148 to \
  -3.8869, 6.08109 front fs empty border lc rgb '#549f' lw 0.1
set object 308 polygon from \
  -3.88141, 6.10071 to \
  -1.15597, 6.10071 to \
  -1.15597, 3.01109 to \
  -3.88141, 3.01109 to \
  -3.88141, 6.10071 front fs empty border lc rgb '#549f' lw 0.1
set object 309 polygon from \
  -3.87582, 6.12032 to \
  -1.15239, 6.12032 to \
  -1.15239, 3.02071 to \
  -3.87582, 3.02071 to \
  -3.87582, 6.12032 front fs empty border lc rgb '#549f' lw 0.1
set object 310 polygon from \
  -3.87011, 6.13994 to \
  -1.1488, 6.13994 to \
  -1.1488, 3.03032 to \
  -3.87011, 3.03032 to \
  -3.87011, 6.13994 front fs empty border lc rgb '#549f' lw 0.1
set object 311 polygon from \
  -3.86429, 6.15955 to \
  -1.14523, 6.15955 to \
  -1.14523, 3.03994 to \
  -3.86429, 3.03994 to \
  -3.86429, 6.15955 front fs empty border lc rgb '#549f' lw 0.1
set object 312 polygon from \
  -3.85837, 6.17916 to \
  -1.14166, 6.17916 to \
  -1.14166, 3.04955 to \
  -3.85837, 3.04955 to \
  -3.85837, 6.17916 front fs empty border lc rgb '#549f' lw 0.1
set object 313 polygon from \
  -3.85233, 6.19877 to \
  -1.1381, 6.19877 to \
  -1.1381, 3.05916 to \
  -3.85233, 3.05916 to \
  -3.85233, 6.19877 front fs empty border lc rgb '#549f' lw 0.1
set object 314 polygon from \
  -3.84618, 6.21838 to \
  -1.13456, 6.21838 to \
  -1.13456, 3.06877 to \
  -3.84618, 3.06877 to \
  -3.84618, 6.21838 front fs empty border lc rgb '#549f' lw 0.1
set object 315 polygon from \
  -3.83991, 6.23798 to \
  -1.13102, 6.23798 to \
  -1.13102, 3.07838 to \
  -3.83991, 3.07838 to \
  -3.83991, 6.23798 front fs empty border lc rgb '#549f' lw 0.1
set object 316 polygon from \
  -3.83354, 6.25759 to \
  -1.12749, 6.25759 to \
  -1.12749, 3.08798 to \
  -3.83354, 3.08798 to \
  -3.83354, 6.25759 front fs empty border lc rgb '#549f' lw 0.1
set object 317 polygon from \
  -3.82706, 6.27719 to \
  -1.12398, 6.27719 to \
  -1.12398, 3.09759 to \
  -3.82706, 3.09759 to \
  -3.82706, 6.27719 front fs empty border lc rgb '#549f' lw 0.1
set object 318 polygon from \
  -3.82046, 6.2968 to \
  -1.12048, 6.2968 to \
  -1.12048, 3.10719 to \
  -3.82046, 3.10719 to \
  -3.82046, 6.2968 front fs empty border lc rgb '#549f' lw 0.1
set object 319 polygon from \
  -3.81375, 6.3164 to \
  -1.11699, 6.3164 to \
  -1.11699, 3.1168 to \
  -3.81375, 3.1168 to \
  -3.81375, 6.3164 front fs empty border lc rgb '#549f' lw 0.1
set object 320 polygon from \
  -3.80693, 6.336 to \
  -1.11352, 6.336 to \
  -1.11352, 3.1264 to \
  -3.80693, 3.1264 to \
  -3.80693, 6.336 front fs empty border lc rgb '#549f' lw 0.1
set object 321 polygon from \
  -3.79999, 6.3556 to \
  -1.11007, 6.3556 to \
  -1.11007, 3.136 to \
  -3.79999, 3.136 to \
  -3.79999, 6.3556 front fs empty border lc rgb '#549f' lw 0.1
set object 322 polygon from \
  -3.79294, 6.3752 to \
  -1.10664, 6.3752 to \
  -1.10664, 3.1456 to \
  -3.79294, 3.1456 to \
  -3.79294, 6.3752 front fs empty border lc rgb '#549f' lw 0.1
set object 323 polygon from \
  -3.78578, 6.39479 to \
  -1.10322, 6.39479 to \
  -1.10322, 3.1552 to \
  -3.78578, 3.1552 to \
  -3.78578, 6.39479 front fs empty border lc rgb '#549f' lw 0.1
set object 324 polygon from \
  -3.7785, 6.41439 to \
  -1.09982, 6.41439 to \
  -1.09982, 3.16479 to \
  -3.7785, 3.16479 to \
  -3.7785, 6.41439 front fs empty border lc rgb '#549f' lw 0.1
set object 325 polygon from \
  -3.77111, 6.43398 to \
  -1.09645, 6.43398 to \
  -1.09645, 3.17439 to \
  -3.77111, 3.17439 to \
  -3.77111, 6.43398 front fs empty border lc rgb '#549f' lw 0.1
set object 326 polygon from \
  -3.7636, 6.45358 to \
  -1.0931, 6.45358 to \
  -1.0931, 3.18398 to \
  -3.7636, 3.18398 to \
  -3.7636, 6.45358 front fs empty border lc rgb '#549f' lw 0.1
set object 327 polygon from \
  -3.75598, 6.47317 to \
  -1.08977, 6.47317 to \
  -1.08977, 3.19358 to \
  -3.75598, 3.19358 to \
  -3.75598, 6.47317 front fs empty border lc rgb '#549f' lw 0.1
set object 328 polygon from \
  -3.74824, 6.49276 to \
  -1.08646, 6.49276 to \
  -1.08646, 3.20317 to \
  -3.74824, 3.20317 to \
  -3.74824, 6.49276 front fs empty border lc rgb '#549f' lw 0.1
set object 329 polygon from \
  -3.74039, 6.51235 to \
  -1.08319, 6.51235 to \
  -1.08319, 3.21276 to \
  -3.74039, 3.21276 to \
  -3.74039, 6.51235 front fs empty border lc rgb '#549f' lw 0.1
set object 330 polygon from \
  -3.73241, 6.53194 to \
  -1.07993, 6.53194 to \
  -1.07993, 3.22235 to \
  -3.73241, 3.22235 to \
  -3.73241, 6.53194 front fs empty border lc rgb '#549f' lw 0.1
set object 331 polygon from \
  -3.72432, 6.55152 to \
  -1.07671, 6.55152 to \
  -1.07671, 3.23194 to \
  -3.72432, 3.23194 to \
  -3.72432, 6.55152 front fs empty border lc rgb '#549f' lw 0.1
set object 332 polygon from \
  -3.71611, 6.57111 to \
  -1.07351, 6.57111 to \
  -1.07351, 3.24152 to \
  -3.71611, 3.24152 to \
  -3.71611, 6.57111 front fs empty border lc rgb '#549f' lw 0.1
set object 333 polygon from \
  -3.70779, 6.59069 to \
  -1.07035, 6.59069 to \
  -1.07035, 3.25111 to \
  -3.70779, 3.25111 to \
  -3.70779, 6.59069 front fs empty border lc rgb '#549f' lw 0.1
set object 334 polygon from \
  -3.69934, 6.61028 to \
  -1.06721, 6.61028 to \
  -1.06721, 3.26069 to \
  -3.69934, 3.26069 to \
  -3.69934, 6.61028 front fs empty border lc rgb '#549f' lw 0.1
set object 335 polygon from \
  -3.69078, 6.62986 to \
  -1.06411, 6.62986 to \
  -1.06411, 3.27028 to \
  -3.69078, 3.27028 to \
  -3.69078, 6.62986 front fs empty border lc rgb '#549f' lw 0.1
set object 336 polygon from \
  -3.68209, 6.64944 to \
  -1.06104, 6.64944 to \
  -1.06104, 3.27986 to \
  -3.68209, 3.27986 to \
  -3.68209, 6.64944 front fs empty border lc rgb '#549f' lw 0.1
set object 337 polygon from \
  -3.67329, 6.66902 to \
  -1.05801, 6.66902 to \
  -1.05801, 3.28944 to \
  -3.67329, 3.28944 to \
  -3.67329, 6.66902 front fs empty border lc rgb '#549f' lw 0.1
set object 338 polygon from \
  -3.66436, 6.6886 to \
  -1.05501, 6.6886 to \
  -1.05501, 3.29902 to \
  -3.66436, 3.29902 to \
  -3.66436, 6.6886 front fs empty border lc rgb '#549f' lw 0.1
set object 339 polygon from \
  -3.65532, 6.70817 to \
  -1.05205, 6.70817 to \
  -1.05205, 3.3086 to \
  -3.65532, 3.3086 to \
  -3.65532, 6.70817 front fs empty border lc rgb '#549f' lw 0.1
set object 340 polygon from \
  -3.64615, 6.72775 to \
  -1.04913, 6.72775 to \
  -1.04913, 3.31817 to \
  -3.64615, 3.31817 to \
  -3.64615, 6.72775 front fs empty border lc rgb '#549f' lw 0.1
set object 341 polygon from \
  -3.63686, 6.74732 to \
  -1.04624, 6.74732 to \
  -1.04624, 3.32775 to \
  -3.63686, 3.32775 to \
  -3.63686, 6.74732 front fs empty border lc rgb '#549f' lw 0.1
set object 342 polygon from \
  -3.62744, 6.7669 to \
  -1.04339, 6.7669 to \
  -1.04339, 3.33732 to \
  -3.62744, 3.33732 to \
  -3.62744, 6.7669 front fs empty border lc rgb '#549f' lw 0.1
set object 343 polygon from \
  -3.61791, 6.78647 to \
  -1.04059, 6.78647 to \
  -1.04059, 3.3469 to \
  -3.61791, 3.3469 to \
  -3.61791, 6.78647 front fs empty border lc rgb '#549f' lw 0.1
set object 344 polygon from \
  -3.60824, 6.80604 to \
  -1.03783, 6.80604 to \
  -1.03783, 3.35647 to \
  -3.60824, 3.35647 to \
  -3.60824, 6.80604 front fs empty border lc rgb '#549f' lw 0.1
set object 345 polygon from \
  -3.59846, 6.82561 to \
  -1.03511, 6.82561 to \
  -1.03511, 3.36604 to \
  -3.59846, 3.36604 to \
  -3.59846, 6.82561 front fs empty border lc rgb '#549f' lw 0.1
set object 346 polygon from \
  -3.58855, 6.84518 to \
  -1.03243, 6.84518 to \
  -1.03243, 3.37561 to \
  -3.58855, 3.37561 to \
  -3.58855, 6.84518 front fs empty border lc rgb '#549f' lw 0.1
set object 347 polygon from \
  -3.57851, 6.86474 to \
  -1.02981, 6.86474 to \
  -1.02981, 3.38518 to \
  -3.57851, 3.38518 to \
  -3.57851, 6.86474 front fs empty border lc rgb '#549f' lw 0.1
set object 348 polygon from \
  -3.56835, 6.88431 to \
  -1.02722, 6.88431 to \
  -1.02722, 3.39474 to \
  -3.56835, 3.39474 to \
  -3.56835, 6.88431 front fs empty border lc rgb '#549f' lw 0.1
set object 349 polygon from \
  -3.55806, 6.90387 to \
  -1.02469, 6.90387 to \
  -1.02469, 3.40431 to \
  -3.55806, 3.40431 to \
  -3.55806, 6.90387 front fs empty border lc rgb '#549f' lw 0.1
set object 350 polygon from \
  -3.54765, 6.92344 to \
  -1.0222, 6.92344 to \
  -1.0222, 3.41387 to \
  -3.54765, 3.41387 to \
  -3.54765, 6.92344 front fs empty border lc rgb '#549f' lw 0.1
set object 351 polygon from \
  -3.53711, 6.943 to \
  -1.01976, 6.943 to \
  -1.01976, 3.42344 to \
  -3.53711, 3.42344 to \
  -3.53711, 6.943 front fs empty border lc rgb '#549f' lw 0.1
set object 352 polygon from \
  -3.52644, 6.96256 to \
  -1.01737, 6.96256 to \
  -1.01737, 3.433 to \
  -3.52644, 3.433 to \
  -3.52644, 6.96256 front fs empty border lc rgb '#549f' lw 0.1
set object 353 polygon from \
  -3.51564, 6.98212 to \
  -1.01503, 6.98212 to \
  -1.01503, 3.44256 to \
  -3.51564, 3.44256 to \
  -3.51564, 6.98212 front fs empty border lc rgb '#549f' lw 0.1
set object 354 polygon from \
  -3.50472, 7.00168 to \
  -1.01275, 7.00168 to \
  -1.01275, 3.45212 to \
  -3.50472, 3.45212 to \
  -3.50472, 7.00168 front fs empty border lc rgb '#549f' lw 0.1
set object 355 polygon from \
  -3.49367, 7.02123 to \
  -1.01051, 7.02123 to \
  -1.01051, 3.46168 to \
  -3.49367, 3.46168 to \
  -3.49367, 7.02123 front fs empty border lc rgb '#549f' lw 0.1
set object 356 polygon from \
  -3.48248, 7.04079 to \
  -1.00833, 7.04079 to \
  -1.00833, 3.47123 to \
  -3.48248, 3.47123 to \
  -3.48248, 7.04079 front fs empty border lc rgb '#549f' lw 0.1
set object 357 polygon from \
  -3.47117, 7.06034 to \
  -1.00621, 7.06034 to \
  -1.00621, 3.48079 to \
  -3.47117, 3.48079 to \
  -3.47117, 7.06034 front fs empty border lc rgb '#549f' lw 0.1
set object 358 polygon from \
  -3.45973, 7.0799 to \
  -1.00414, 7.0799 to \
  -1.00414, 3.49034 to \
  -3.45973, 3.49034 to \
  -3.45973, 7.0799 front fs empty border lc rgb '#549f' lw 0.1
set object 359 polygon from \
  -3.44816, 7.09945 to \
  -1.00212, 7.09945 to \
  -1.00212, 3.4999 to \
  -3.44816, 3.4999 to \
  -3.44816, 7.09945 front fs empty border lc rgb '#549f' lw 0.1
set object 360 polygon from \
  -3.43645, 7.119 to \
  -1.00016, 7.119 to \
  -1.00016, 3.50945 to \
  -3.43645, 3.50945 to \
  -3.43645, 7.119 front fs empty border lc rgb '#549f' lw 0.1
set object 361 polygon from \
  -3.42462, 7.13855 to \
  -0.998263, 7.13855 to \
  -0.998263, 3.519 to \
  -3.42462, 3.519 to \
  -3.42462, 7.13855 front fs empty border lc rgb '#549f' lw 0.1
set object 362 polygon from \
  -3.41266, 7.1581 to \
  -0.996421, 7.1581 to \
  -0.996421, 3.52855 to \
  -3.41266, 3.52855 to \
  -3.41266, 7.1581 front fs empty border lc rgb '#549f' lw 0.1
set object 363 polygon from \
  -3.40056, 7.17764 to \
  -0.994638, 7.17764 to \
  -0.994638, 3.5381 to \
  -3.40056, 3.5381 to \
  -3.40056, 7.17764 front fs empty border lc rgb '#549f' lw 0.1
set object 364 polygon from \
  -3.38833, 7.19719 to \
  -0.992914, 7.19719 to \
  -0.992914, 3.54764 to \
  -3.38833, 3.54764 to \
  -3.38833, 7.19719 front fs empty border lc rgb '#549f' lw 0.1
set object 365 polygon from \
  -3.37598, 7.21673 to \
  -0.991249, 7.21673 to \
  -0.991249, 3.55719 to \
  -3.37598, 3.55719 to \
  -3.37598, 7.21673 front fs empty border lc rgb '#549f' lw 0.1
set object 366 polygon from \
  -3.36349, 7.23628 to \
  -0.989646, 7.23628 to \
  -0.989646, 3.56673 to \
  -3.36349, 3.56673 to \
  -3.36349, 7.23628 front fs empty border lc rgb '#549f' lw 0.1
set object 367 polygon from \
  -3.35086, 7.25582 to \
  -0.988103, 7.25582 to \
  -0.988103, 3.57628 to \
  -3.35086, 3.57628 to \
  -3.35086, 7.25582 front fs empty border lc rgb '#549f' lw 0.1
set object 368 polygon from \
  -3.33811, 7.27536 to \
  -0.986622, 7.27536 to \
  -0.986622, 3.58582 to \
  -3.33811, 3.58582 to \
  -3.33811, 7.27536 front fs empty border lc rgb '#549f' lw 0.1
set object 369 polygon from \
  -3.32522, 7.2949 to \
  -0.985203, 7.2949 to \
  -0.985203, 3.59536 to \
  -3.32522, 3.59536 to \
  -3.32522, 7.2949 front fs empty border lc rgb '#549f' lw 0.1
set object 370 polygon from \
  -3.3122, 7.31444 to \
  -0.983847, 7.31444 to \
  -0.983847, 3.6049 to \
  -3.3122, 3.6049 to \
  -3.3122, 7.31444 front fs empty border lc rgb '#549f' lw 0.1
set object 371 polygon from \
  -3.29905, 7.33397 to \
  -0.982553, 7.33397 to \
  -0.982553, 3.61444 to \
  -3.29905, 3.61444 to \
  -3.29905, 7.33397 front fs empty border lc rgb '#549f' lw 0.1
set object 372 polygon from \
  -3.28577, 7.35351 to \
  -0.981323, 7.35351 to \
  -0.981323, 3.62397 to \
  -3.28577, 3.62397 to \
  -3.28577, 7.35351 front fs empty border lc rgb '#549f' lw 0.1
set object 373 polygon from \
  -3.27235, 7.37304 to \
  -0.980156, 7.37304 to \
  -0.980156, 3.63351 to \
  -3.27235, 3.63351 to \
  -3.27235, 7.37304 front fs empty border lc rgb '#549f' lw 0.1
set object 374 polygon from \
  -3.2588, 7.39258 to \
  -0.979053, 7.39258 to \
  -0.979053, 3.64304 to \
  -3.2588, 3.64304 to \
  -3.2588, 7.39258 front fs empty border lc rgb '#549f' lw 0.1
set object 375 polygon from \
  -3.24512, 7.41211 to \
  -0.976659, 7.41211 to \
  -0.976659, 3.65258 to \
  -3.24512, 3.65258 to \
  -3.24512, 7.41211 front fs empty border lc rgb '#549f' lw 0.1
set object 376 polygon from \
  -3.23267, 7.43164 to \
  -0.972543, 7.43164 to \
  -0.972543, 3.66211 to \
  -3.23267, 3.66211 to \
  -3.23267, 7.43164 front fs empty border lc rgb '#549f' lw 0.1
set object 377 polygon from \
  -3.22186, 7.45117 to \
  -0.96841, 7.45117 to \
  -0.96841, 3.67164 to \
  -3.22186, 3.67164 to \
  -3.22186, 7.45117 front fs empty border lc rgb '#549f' lw 0.1
set object 378 polygon from \
  -3.21101, 7.4707 to \
  -0.96426, 7.4707 to \
  -0.96426, 3.68117 to \
  -3.21101, 3.68117 to \
  -3.21101, 7.4707 front fs empty border lc rgb '#549f' lw 0.1
set object 379 polygon from \
  -3.20011, 7.49022 to \
  -0.960095, 7.49022 to \
  -0.960095, 3.6907 to \
  -3.20011, 3.6907 to \
  -3.20011, 7.49022 front fs empty border lc rgb '#549f' lw 0.1
set object 380 polygon from \
  -3.18915, 7.50975 to \
  -0.955914, 7.50975 to \
  -0.955914, 3.70022 to \
  -3.18915, 3.70022 to \
  -3.18915, 7.50975 front fs empty border lc rgb '#549f' lw 0.1
set object 381 polygon from \
  -3.17814, 7.52927 to \
  -0.951717, 7.52927 to \
  -0.951717, 3.70975 to \
  -3.17814, 3.70975 to \
  -3.17814, 7.52927 front fs empty border lc rgb '#549f' lw 0.1
set object 382 polygon from \
  -3.16709, 7.5488 to \
  -0.947505, 7.5488 to \
  -0.947505, 3.71927 to \
  -3.16709, 3.71927 to \
  -3.16709, 7.5488 front fs empty border lc rgb '#549f' lw 0.1
set object 383 polygon from \
  -3.15598, 7.56832 to \
  -0.943277, 7.56832 to \
  -0.943277, 3.7288 to \
  -3.15598, 3.7288 to \
  -3.15598, 7.56832 front fs empty border lc rgb '#549f' lw 0.1
set object 384 polygon from \
  -3.14482, 7.58784 to \
  -0.939033, 7.58784 to \
  -0.939033, 3.73832 to \
  -3.14482, 3.73832 to \
  -3.14482, 7.58784 front fs empty border lc rgb '#549f' lw 0.1
set object 385 polygon from \
  -3.13362, 7.60736 to \
  -0.934774, 7.60736 to \
  -0.934774, 3.74784 to \
  -3.13362, 3.74784 to \
  -3.13362, 7.60736 front fs empty border lc rgb '#549f' lw 0.1
set object 386 polygon from \
  -3.12236, 7.62688 to \
  -0.930499, 7.62688 to \
  -0.930499, 3.75736 to \
  -3.12236, 3.75736 to \
  -3.12236, 7.62688 front fs empty border lc rgb '#549f' lw 0.1
set object 387 polygon from \
  -3.11105, 7.64639 to \
  -0.926209, 7.64639 to \
  -0.926209, 3.76688 to \
  -3.11105, 3.76688 to \
  -3.11105, 7.64639 front fs empty border lc rgb '#549f' lw 0.1
set object 388 polygon from \
  -3.0997, 7.66591 to \
  -0.921904, 7.66591 to \
  -0.921904, 3.77639 to \
  -3.0997, 3.77639 to \
  -3.0997, 7.66591 front fs empty border lc rgb '#549f' lw 0.1
set object 389 polygon from \
  -3.08829, 7.68542 to \
  -0.917584, 7.68542 to \
  -0.917584, 3.78591 to \
  -3.08829, 3.78591 to \
  -3.08829, 7.68542 front fs empty border lc rgb '#549f' lw 0.1
set object 390 polygon from \
  -3.07684, 7.70494 to \
  -0.913248, 7.70494 to \
  -0.913248, 3.79542 to \
  -3.07684, 3.79542 to \
  -3.07684, 7.70494 front fs empty border lc rgb '#549f' lw 0.1
set object 391 polygon from \
  -3.06533, 7.72445 to \
  -0.908897, 7.72445 to \
  -0.908897, 3.80494 to \
  -3.06533, 3.80494 to \
  -3.06533, 7.72445 front fs empty border lc rgb '#549f' lw 0.1
set object 392 polygon from \
  -3.05378, 7.74396 to \
  -0.904531, 7.74396 to \
  -0.904531, 3.81445 to \
  -3.05378, 3.81445 to \
  -3.05378, 7.74396 front fs empty border lc rgb '#549f' lw 0.1
set object 393 polygon from \
  -3.04218, 7.76347 to \
  -0.90015, 7.76347 to \
  -0.90015, 3.82396 to \
  -3.04218, 3.82396 to \
  -3.04218, 7.76347 front fs empty border lc rgb '#549f' lw 0.1
set object 394 polygon from \
  -3.03053, 7.78298 to \
  -0.895754, 7.78298 to \
  -0.895754, 3.83347 to \
  -3.03053, 3.83347 to \
  -3.03053, 7.78298 front fs empty border lc rgb '#549f' lw 0.1
set object 395 polygon from \
  -3.01884, 7.80248 to \
  -0.891343, 7.80248 to \
  -0.891343, 3.84298 to \
  -3.01884, 3.84298 to \
  -3.01884, 7.80248 front fs empty border lc rgb '#549f' lw 0.1
set object 396 polygon from \
  -3.00709, 7.82199 to \
  -0.886917, 7.82199 to \
  -0.886917, 3.85248 to \
  -3.00709, 3.85248 to \
  -3.00709, 7.82199 front fs empty border lc rgb '#549f' lw 0.1
set object 397 polygon from \
  -2.9953, 7.84149 to \
  -0.882476, 7.84149 to \
  -0.882476, 3.86199 to \
  -2.9953, 3.86199 to \
  -2.9953, 7.84149 front fs empty border lc rgb '#549f' lw 0.1
set object 398 polygon from \
  -2.98346, 7.861 to \
  -0.87802, 7.861 to \
  -0.87802, 3.87149 to \
  -2.98346, 3.87149 to \
  -2.98346, 7.861 front fs empty border lc rgb '#549f' lw 0.1
set object 399 polygon from \
  -2.97157, 7.8805 to \
  -0.87355, 7.8805 to \
  -0.87355, 3.881 to \
  -2.97157, 3.881 to \
  -2.97157, 7.8805 front fs empty border lc rgb '#549f' lw 0.1
set object 400 polygon from \
  -2.95963, 7.9 to \
  -0.869065, 7.9 to \
  -0.869065, 3.8905 to \
  -2.95963, 3.8905 to \
  -2.95963, 7.9 front fs empty border lc rgb '#549f' lw 0.1
set object 401 polygon from \
  -2.94765, 7.9195 to \
  -0.864565, 7.9195 to \
  -0.864565, 3.9 to \
  -2.94765, 3.9 to \
  -2.94765, 7.9195 front fs empty border lc rgb '#549f' lw 0.1
set object 402 polygon from \
  -2.96745, 7.939 to \
  -0.840201, 7.939 to \
  -0.840201, 3.8905 to \
  -2.96745, 3.8905 to \
  -2.96745, 7.939 front fs empty border lc rgb '#549f' lw 0.1
set object 403 polygon from \
  -2.97575, 7.95851 to \
  -0.815281, 7.95851 to \
  -0.815281, 3.9 to \
  -2.97575, 3.9 to \
  -2.97575, 7.95851 front fs empty border lc rgb '#549f' lw 0.1
set object 404 polygon from \
  -2.98499, 7.97801 to \
  -0.78937, 7.97801 to \
  -0.78937, 3.9095 to \
  -2.98499, 3.9095 to \
  -2.98499, 7.97801 front fs empty border lc rgb '#549f' lw 0.1
set object 405 polygon from \
  -2.99514, 7.99752 to \
  -0.762473, 7.99752 to \
  -0.762473, 3.919 to \
  -2.99514, 3.919 to \
  -2.99514, 7.99752 front fs empty border lc rgb '#549f' lw 0.1
set object 406 polygon from \
  -3.00622, 8.01702 to \
  -0.734593, 8.01702 to \
  -0.734593, 3.9285 to \
  -3.00622, 3.9285 to \
  -3.00622, 8.01702 front fs empty border lc rgb '#549f' lw 0.1
set object 407 polygon from \
  -3.01822, 8.03653 to \
  -0.705734, 8.03653 to \
  -0.705734, 3.93801 to \
  -3.01822, 3.93801 to \
  -3.01822, 8.03653 front fs empty border lc rgb '#549f' lw 0.1
set object 408 polygon from \
  -3.03112, 8.05604 to \
  -0.675902, 8.05604 to \
  -0.675902, 3.94751 to \
  -3.03112, 3.94751 to \
  -3.03112, 8.05604 front fs empty border lc rgb '#549f' lw 0.1
set object 409 polygon from \
  -3.04493, 8.07555 to \
  -0.645103, 8.07555 to \
  -0.645103, 3.95702 to \
  -3.04493, 3.95702 to \
  -3.04493, 8.07555 front fs empty border lc rgb '#549f' lw 0.1
set object 410 polygon from \
  -3.05964, 8.09506 to \
  -0.613343, 8.09506 to \
  -0.613343, 3.96653 to \
  -3.05964, 3.96653 to \
  -3.05964, 8.09506 front fs empty border lc rgb '#549f' lw 0.1
set object 411 polygon from \
  -3.07525, 8.11458 to \
  -0.580629, 8.11458 to \
  -0.580629, 3.97604 to \
  -3.07525, 3.97604 to \
  -3.07525, 8.11458 front fs empty border lc rgb '#549f' lw 0.1
set object 412 polygon from \
  -3.09173, 8.13409 to \
  -0.546968, 8.13409 to \
  -0.546968, 3.98555 to \
  -3.09173, 3.98555 to \
  -3.09173, 8.13409 front fs empty border lc rgb '#549f' lw 0.1
set object 413 polygon from \
  -3.10909, 8.15361 to \
  -0.512369, 8.15361 to \
  -0.512369, 3.99506 to \
  -3.10909, 3.99506 to \
  -3.10909, 8.15361 front fs empty border lc rgb '#549f' lw 0.1
set object 414 polygon from \
  -3.12732, 8.17312 to \
  -0.476839, 8.17312 to \
  -0.476839, 4.00457 to \
  -3.12732, 4.00457 to \
  -3.12732, 8.17312 front fs empty border lc rgb '#549f' lw 0.1
set object 415 polygon from \
  -3.14641, 8.19264 to \
  -0.440388, 8.19264 to \
  -0.440388, 4.01409 to \
  -3.14641, 4.01409 to \
  -3.14641, 8.19264 front fs empty border lc rgb '#549f' lw 0.1
set object 416 polygon from \
  -3.16635, 8.21216 to \
  -0.403025, 8.21216 to \
  -0.403025, 4.0236 to \
  -3.16635, 4.0236 to \
  -3.16635, 8.21216 front fs empty border lc rgb '#549f' lw 0.1
set object 417 polygon from \
  -3.18713, 8.23168 to \
  -0.36476, 8.23168 to \
  -0.36476, 4.03312 to \
  -3.18713, 4.03312 to \
  -3.18713, 8.23168 front fs empty border lc rgb '#549f' lw 0.1
set object 418 polygon from \
  -3.20874, 8.2512 to \
  -0.325604, 8.2512 to \
  -0.325604, 4.04264 to \
  -3.20874, 4.04264 to \
  -3.20874, 8.2512 front fs empty border lc rgb '#549f' lw 0.1
set object 419 polygon from \
  -3.23117, 8.27073 to \
  -0.285568, 8.27073 to \
  -0.285568, 4.05216 to \
  -3.23117, 4.05216 to \
  -3.23117, 8.27073 front fs empty border lc rgb '#549f' lw 0.1
set object 420 polygon from \
  -3.2544, 8.29025 to \
  -0.244664, 8.29025 to \
  -0.244664, 4.06168 to \
  -3.2544, 4.06168 to \
  -3.2544, 8.29025 front fs empty border lc rgb '#549f' lw 0.1
set object 421 polygon from \
  -3.27843, 8.30978 to \
  -0.202902, 8.30978 to \
  -0.202902, 4.0712 to \
  -3.27843, 4.0712 to \
  -3.27843, 8.30978 front fs empty border lc rgb '#549f' lw 0.1
set object 422 polygon from \
  -3.30324, 8.3293 to \
  -0.160297, 8.3293 to \
  -0.160297, 4.08072 to \
  -3.30324, 4.08072 to \
  -3.30324, 8.3293 front fs empty border lc rgb '#549f' lw 0.1
set object 423 polygon from \
  -3.32882, 8.34883 to \
  -0.11686, 8.34883 to \
  -0.11686, 4.09025 to \
  -3.32882, 4.09025 to \
  -3.32882, 8.34883 front fs empty border lc rgb '#549f' lw 0.1
set object 424 polygon from \
  -3.35515, 8.36836 to \
  -0.0726062, 8.36836 to \
  -0.0726062, 4.09977 to \
  -3.35515, 4.09977 to \
  -3.35515, 8.36836 front fs empty border lc rgb '#549f' lw 0.1
set object 425 polygon from \
  -3.38223, 8.38789 to \
  -0.03, 8.38789 to \
  -0.03, 4.1093 to \
  -3.38223, 4.1093 to \
  -3.38223, 8.38789 front fs empty border lc rgb '#549f' lw 0.1
set object 426 polygon from \
  -3.41003, 8.40742 to \
  -0.03, 8.40742 to \
  -0.03, 4.11883 to \
  -3.41003, 4.11883 to \
  -3.41003, 8.40742 front fs empty border lc rgb '#549f' lw 0.1
set object 427 polygon from \
  -3.43854, 8.42696 to \
  -0.03, 8.42696 to \
  -0.03, 4.12836 to \
  -3.43854, 4.12836 to \
  -3.43854, 8.42696 front fs empty border lc rgb '#549f' lw 0.1
set object 428 polygon from \
  -3.46776, 8.44649 to \
  -0.03, 8.44649 to \
  -0.03, 4.13789 to \
  -3.46776, 4.13789 to \
  -3.46776, 8.44649 front fs empty border lc rgb '#549f' lw 0.1
set object 429 polygon from \
  -3.49765, 8.46603 to \
  -0.03, 8.46603 to \
  -0.03, 4.14742 to \
  -3.49765, 4.14742 to \
  -3.49765, 8.46603 front fs empty border lc rgb '#549f' lw 0.1
set object 430 polygon from \
  -3.52821, 8.48556 to \
  -0.03, 8.48556 to \
  -0.03, 4.15695 to \
  -3.52821, 4.15695 to \
  -3.52821, 8.48556 front fs empty border lc rgb '#549f' lw 0.1
set object 431 polygon from \
  -3.55942, 8.5051 to \
  -0.03, 8.5051 to \
  -0.03, 4.16649 to \
  -3.55942, 4.16649 to \
  -3.55942, 8.5051 front fs empty border lc rgb '#549f' lw 0.1
set object 432 polygon from \
  -3.59126, 8.52464 to \
  -0.03, 8.52464 to \
  -0.03, 4.17602 to \
  -3.59126, 4.17602 to \
  -3.59126, 8.52464 front fs empty border lc rgb '#549f' lw 0.1
set object 433 polygon from \
  -3.62371, 8.54418 to \
  -0.03, 8.54418 to \
  -0.03, 4.18556 to \
  -3.62371, 4.18556 to \
  -3.62371, 8.54418 front fs empty border lc rgb '#549f' lw 0.1
set object 434 polygon from \
  -3.65676, 8.56372 to \
  -0.03, 8.56372 to \
  -0.03, 4.1951 to \
  -3.65676, 4.1951 to \
  -3.65676, 8.56372 front fs empty border lc rgb '#549f' lw 0.1
set object 435 polygon from \
  -3.69039, 8.58327 to \
  -0.03, 8.58327 to \
  -0.03, 4.20464 to \
  -3.69039, 4.20464 to \
  -3.69039, 8.58327 front fs empty border lc rgb '#549f' lw 0.1
set object 436 polygon from \
  -3.72459, 8.60281 to \
  -0.03, 8.60281 to \
  -0.03, 4.21418 to \
  -3.72459, 4.21418 to \
  -3.72459, 8.60281 front fs empty border lc rgb '#549f' lw 0.1
set object 437 polygon from \
  -3.75932, 8.62236 to \
  -0.03, 8.62236 to \
  -0.03, 4.22372 to \
  -3.75932, 4.22372 to \
  -3.75932, 8.62236 front fs empty border lc rgb '#549f' lw 0.1
set object 438 polygon from \
  -3.79458, 8.6419 to \
  -0.03, 8.6419 to \
  -0.03, 4.23326 to \
  -3.79458, 4.23326 to \
  -3.79458, 8.6419 front fs empty border lc rgb '#549f' lw 0.1
set object 439 polygon from \
  -3.83034, 8.66145 to \
  -0.03, 8.66145 to \
  -0.03, 4.24281 to \
  -3.83034, 4.24281 to \
  -3.83034, 8.66145 front fs empty border lc rgb '#549f' lw 0.1
set object 440 polygon from \
  -3.86658, 8.681 to \
  -0.03, 8.681 to \
  -0.03, 4.25235 to \
  -3.86658, 4.25235 to \
  -3.86658, 8.681 front fs empty border lc rgb '#549f' lw 0.1
set object 441 polygon from \
  -3.90329, 8.70055 to \
  -0.03, 8.70055 to \
  -0.03, 4.2619 to \
  -3.90329, 4.2619 to \
  -3.90329, 8.70055 front fs empty border lc rgb '#549f' lw 0.1
set object 442 polygon from \
  -3.94044, 8.7201 to \
  -0.03, 8.7201 to \
  -0.03, 4.27145 to \
  -3.94044, 4.27145 to \
  -3.94044, 8.7201 front fs empty border lc rgb '#549f' lw 0.1
set object 443 polygon from \
  -3.97802, 8.73966 to \
  -0.03, 8.73966 to \
  -0.03, 4.281 to \
  -3.97802, 4.281 to \
  -3.97802, 8.73966 front fs empty border lc rgb '#549f' lw 0.1
set object 444 polygon from \
  -4.01599, 8.75921 to \
  -0.03, 8.75921 to \
  -0.03, 4.29055 to \
  -4.01599, 4.29055 to \
  -4.01599, 8.75921 front fs empty border lc rgb '#549f' lw 0.1
set object 445 polygon from \
  -4.05435, 8.77877 to \
  -0.03, 8.77877 to \
  -0.03, 4.3001 to \
  -4.05435, 4.3001 to \
  -4.05435, 8.77877 front fs empty border lc rgb '#549f' lw 0.1
set object 446 polygon from \
  -4.09307, 8.79832 to \
  -0.03, 8.79832 to \
  -0.03, 4.30965 to \
  -4.09307, 4.30965 to \
  -4.09307, 8.79832 front fs empty border lc rgb '#549f' lw 0.1
set object 447 polygon from \
  -4.13213, 8.81788 to \
  -0.03, 8.81788 to \
  -0.03, 4.31921 to \
  -4.13213, 4.31921 to \
  -4.13213, 8.81788 front fs empty border lc rgb '#549f' lw 0.1
set object 448 polygon from \
  -4.17151, 8.83744 to \
  -0.03, 8.83744 to \
  -0.03, 4.32876 to \
  -4.17151, 4.32876 to \
  -4.17151, 8.83744 front fs empty border lc rgb '#549f' lw 0.1
set object 449 polygon from \
  -4.21118, 8.857 to \
  -0.03, 8.857 to \
  -0.03, 4.33832 to \
  -4.21118, 4.33832 to \
  -4.21118, 8.857 front fs empty border lc rgb '#549f' lw 0.1
set object 450 polygon from \
  -4.25112, 8.87656 to \
  -0.03, 8.87656 to \
  -0.03, 4.34788 to \
  -4.25112, 4.34788 to \
  -4.25112, 8.87656 front fs empty border lc rgb '#549f' lw 0.1
set object 451 polygon from \
  -4.29132, 8.89613 to \
  -0.03, 8.89613 to \
  -0.03, 4.35744 to \
  -4.29132, 4.35744 to \
  -4.29132, 8.89613 front fs empty border lc rgb '#549f' lw 0.1
set object 452 polygon from \
  -4.33174, 8.91569 to \
  -0.03, 8.91569 to \
  -0.03, 4.367 to \
  -4.33174, 4.367 to \
  -4.33174, 8.91569 front fs empty border lc rgb '#549f' lw 0.1
set object 453 polygon from \
  -4.37237, 8.93526 to \
  -0.03, 8.93526 to \
  -0.03, 4.37656 to \
  -4.37237, 4.37656 to \
  -4.37237, 8.93526 front fs empty border lc rgb '#549f' lw 0.1
set object 454 polygon from \
  -4.41319, 8.95482 to \
  -0.03, 8.95482 to \
  -0.03, 4.38612 to \
  -4.41319, 4.38612 to \
  -4.41319, 8.95482 front fs empty border lc rgb '#549f' lw 0.1
set object 455 polygon from \
  -4.45416, 8.97439 to \
  -0.03, 8.97439 to \
  -0.03, 4.39569 to \
  -4.45416, 4.39569 to \
  -4.45416, 8.97439 front fs empty border lc rgb '#549f' lw 0.1
set object 456 polygon from \
  -4.49528, 8.99396 to \
  -0.03, 8.99396 to \
  -0.03, 4.40525 to \
  -4.49528, 4.40525 to \
  -4.49528, 8.99396 front fs empty border lc rgb '#549f' lw 0.1
set object 457 polygon from \
  -4.53651, 9.01353 to \
  -0.03, 9.01353 to \
  -0.03, 4.41482 to \
  -4.53651, 4.41482 to \
  -4.53651, 9.01353 front fs empty border lc rgb '#549f' lw 0.1
set object 458 polygon from \
  -4.57783, 9.0331 to \
  -0.03, 9.0331 to \
  -0.03, 4.42439 to \
  -4.57783, 4.42439 to \
  -4.57783, 9.0331 front fs empty border lc rgb '#549f' lw 0.1
set object 459 polygon from \
  -4.61923, 9.05268 to \
  -0.03, 9.05268 to \
  -0.03, 4.43396 to \
  -4.61923, 4.43396 to \
  -4.61923, 9.05268 front fs empty border lc rgb '#549f' lw 0.1
set object 460 polygon from \
  -4.66067, 9.07225 to \
  -0.03, 9.07225 to \
  -0.03, 4.44353 to \
  -4.66067, 4.44353 to \
  -4.66067, 9.07225 front fs empty border lc rgb '#549f' lw 0.1
set object 461 polygon from \
  -4.70213, 9.09183 to \
  -0.03, 9.09183 to \
  -0.03, 4.4531 to \
  -4.70213, 4.4531 to \
  -4.70213, 9.09183 front fs empty border lc rgb '#549f' lw 0.1
set object 462 polygon from \
  -4.74359, 9.1114 to \
  -0.03, 9.1114 to \
  -0.03, 4.46267 to \
  -4.74359, 4.46267 to \
  -4.74359, 9.1114 front fs empty border lc rgb '#549f' lw 0.1
set object 463 polygon from \
  -4.78503, 9.13098 to \
  -0.03, 9.13098 to \
  -0.03, 4.47225 to \
  -4.78503, 4.47225 to \
  -4.78503, 9.13098 front fs empty border lc rgb '#549f' lw 0.1
set object 464 polygon from \
  -4.82643, 9.15056 to \
  -0.03, 9.15056 to \
  -0.03, 4.48182 to \
  -4.82643, 4.48182 to \
  -4.82643, 9.15056 front fs empty border lc rgb '#549f' lw 0.1
set object 465 polygon from \
  -4.86776, 9.17014 to \
  -0.03, 9.17014 to \
  -0.03, 4.4914 to \
  -4.86776, 4.4914 to \
  -4.86776, 9.17014 front fs empty border lc rgb '#549f' lw 0.1
set object 466 polygon from \
  -4.90899, 9.18972 to \
  -0.03, 9.18972 to \
  -0.03, 4.50098 to \
  -4.90899, 4.50098 to \
  -4.90899, 9.18972 front fs empty border lc rgb '#549f' lw 0.1
set object 467 polygon from \
  -4.95012, 9.20931 to \
  -0.03, 9.20931 to \
  -0.03, 4.51056 to \
  -4.95012, 4.51056 to \
  -4.95012, 9.20931 front fs empty border lc rgb '#549f' lw 0.1
set object 468 polygon from \
  -4.9911, 9.22889 to \
  -0.03, 9.22889 to \
  -0.03, 4.52014 to \
  -4.9911, 4.52014 to \
  -4.9911, 9.22889 front fs empty border lc rgb '#549f' lw 0.1
set object 469 polygon from \
  -5.03193, 9.24848 to \
  -0.03, 9.24848 to \
  -0.03, 4.52972 to \
  -5.03193, 4.52972 to \
  -5.03193, 9.24848 front fs empty border lc rgb '#549f' lw 0.1
set object 470 polygon from \
  -5.07257, 9.26806 to \
  -0.03, 9.26806 to \
  -0.03, 4.5393 to \
  -5.07257, 4.5393 to \
  -5.07257, 9.26806 front fs empty border lc rgb '#549f' lw 0.1
set object 471 polygon from \
  -5.11301, 9.28765 to \
  -0.03, 9.28765 to \
  -0.03, 4.54889 to \
  -5.11301, 4.54889 to \
  -5.11301, 9.28765 front fs empty border lc rgb '#549f' lw 0.1
set object 472 polygon from \
  -5.15322, 9.30724 to \
  -0.03, 9.30724 to \
  -0.03, 4.55847 to \
  -5.15322, 4.55847 to \
  -5.15322, 9.30724 front fs empty border lc rgb '#549f' lw 0.1
set object 473 polygon from \
  -5.19318, 9.32683 to \
  -0.03, 9.32683 to \
  -0.03, 4.56806 to \
  -5.19318, 4.56806 to \
  -5.19318, 9.32683 front fs empty border lc rgb '#549f' lw 0.1
set object 474 polygon from \
  -5.23287, 9.34642 to \
  -0.03, 9.34642 to \
  -0.03, 4.57765 to \
  -5.23287, 4.57765 to \
  -5.23287, 9.34642 front fs empty border lc rgb '#549f' lw 0.1
set object 475 polygon from \
  -5.27227, 9.36602 to \
  -0.03, 9.36602 to \
  -0.03, 4.58724 to \
  -5.27227, 4.58724 to \
  -5.27227, 9.36602 front fs empty border lc rgb '#549f' lw 0.1
set object 476 polygon from \
  -5.31135, 9.38561 to \
  -0.03, 9.38561 to \
  -0.03, 4.59683 to \
  -5.31135, 4.59683 to \
  -5.31135, 9.38561 front fs empty border lc rgb '#549f' lw 0.1
set object 477 polygon from \
  -5.35009, 9.40521 to \
  -0.03, 9.40521 to \
  -0.03, 4.60642 to \
  -5.35009, 4.60642 to \
  -5.35009, 9.40521 front fs empty border lc rgb '#549f' lw 0.1
set object 478 polygon from \
  -5.38848, 9.4248 to \
  -0.03, 9.4248 to \
  -0.03, 4.61601 to \
  -5.38848, 4.61601 to \
  -5.38848, 9.4248 front fs empty border lc rgb '#549f' lw 0.1
set object 479 polygon from \
  -5.42648, 9.4444 to \
  -0.03, 9.4444 to \
  -0.03, 4.62561 to \
  -5.42648, 4.62561 to \
  -5.42648, 9.4444 front fs empty border lc rgb '#549f' lw 0.1
set object 480 polygon from \
  -5.46409, 9.464 to \
  -0.03, 9.464 to \
  -0.03, 4.6352 to \
  -5.46409, 4.6352 to \
  -5.46409, 9.464 front fs empty border lc rgb '#549f' lw 0.1
set object 481 polygon from \
  -5.50127, 9.4836 to \
  -0.03, 9.4836 to \
  -0.03, 4.6448 to \
  -5.50127, 4.6448 to \
  -5.50127, 9.4836 front fs empty border lc rgb '#549f' lw 0.1
set object 482 polygon from \
  -5.53802, 9.5032 to \
  -0.03, 9.5032 to \
  -0.03, 4.6544 to \
  -5.53802, 4.6544 to \
  -5.53802, 9.5032 front fs empty border lc rgb '#549f' lw 0.1
set object 483 polygon from \
  -5.5743, 9.52281 to \
  -0.03, 9.52281 to \
  -0.03, 4.664 to \
  -5.5743, 4.664 to \
  -5.5743, 9.52281 front fs empty border lc rgb '#549f' lw 0.1
set object 484 polygon from \
  -5.6101, 9.54241 to \
  -0.03, 9.54241 to \
  -0.03, 4.6736 to \
  -5.6101, 4.6736 to \
  -5.6101, 9.54241 front fs empty border lc rgb '#549f' lw 0.1
set object 485 polygon from \
  -5.6454, 9.56202 to \
  -0.03, 9.56202 to \
  -0.03, 4.6832 to \
  -5.6454, 4.6832 to \
  -5.6454, 9.56202 front fs empty border lc rgb '#549f' lw 0.1
set object 486 polygon from \
  -5.68018, 9.58162 to \
  -0.03, 9.58162 to \
  -0.03, 4.6928 to \
  -5.68018, 4.6928 to \
  -5.68018, 9.58162 front fs empty border lc rgb '#549f' lw 0.1
set object 487 polygon from \
  -5.71442, 9.60123 to \
  -0.03, 9.60123 to \
  -0.03, 4.70241 to \
  -5.71442, 4.70241 to \
  -5.71442, 9.60123 front fs empty border lc rgb '#549f' lw 0.1
set object 488 polygon from \
  -5.7481, 9.62084 to \
  -0.03, 9.62084 to \
  -0.03, 4.71201 to \
  -5.7481, 4.71201 to \
  -5.7481, 9.62084 front fs empty border lc rgb '#549f' lw 0.1
set object 489 polygon from \
  -5.78121, 9.64045 to \
  -0.03, 9.64045 to \
  -0.03, 4.72162 to \
  -5.78121, 4.72162 to \
  -5.78121, 9.64045 front fs empty border lc rgb '#549f' lw 0.1
set object 490 polygon from \
  -5.81372, 9.66006 to \
  -0.03, 9.66006 to \
  -0.03, 4.73123 to \
  -5.81372, 4.73123 to \
  -5.81372, 9.66006 front fs empty border lc rgb '#549f' lw 0.1
set object 491 polygon from \
  -5.84562, 9.67968 to \
  -0.03, 9.67968 to \
  -0.03, 4.74084 to \
  -5.84562, 4.74084 to \
  -5.84562, 9.67968 front fs empty border lc rgb '#549f' lw 0.1
set object 492 polygon from \
  -5.87689, 9.69929 to \
  -0.03, 9.69929 to \
  -0.03, 4.75045 to \
  -5.87689, 4.75045 to \
  -5.87689, 9.69929 front fs empty border lc rgb '#549f' lw 0.1
set object 493 polygon from \
  -5.90751, 9.71891 to \
  -0.03, 9.71891 to \
  -0.03, 4.76006 to \
  -5.90751, 4.76006 to \
  -5.90751, 9.71891 front fs empty border lc rgb '#549f' lw 0.1
set object 494 polygon from \
  -5.93747, 9.73852 to \
  -0.03, 9.73852 to \
  -0.03, 4.76967 to \
  -5.93747, 4.76967 to \
  -5.93747, 9.73852 front fs empty border lc rgb '#549f' lw 0.1
set object 495 polygon from \
  -5.96676, 9.75814 to \
  -0.03, 9.75814 to \
  -0.03, 4.77929 to \
  -5.96676, 4.77929 to \
  -5.96676, 9.75814 front fs empty border lc rgb '#549f' lw 0.1
set object 496 polygon from \
  -5.99535, 9.77776 to \
  -0.03, 9.77776 to \
  -0.03, 4.7889 to \
  -5.99535, 4.7889 to \
  -5.99535, 9.77776 front fs empty border lc rgb '#549f' lw 0.1
set object 497 polygon from \
  -6.02323, 9.79738 to \
  -0.03, 9.79738 to \
  -0.03, 4.79852 to \
  -6.02323, 4.79852 to \
  -6.02323, 9.79738 front fs empty border lc rgb '#549f' lw 0.1
set object 498 polygon from \
  -6.05038, 9.817 to \
  -0.03, 9.817 to \
  -0.03, 4.80814 to \
  -6.05038, 4.80814 to \
  -6.05038, 9.817 front fs empty border lc rgb '#549f' lw 0.1
set object 499 polygon from \
  -6.0768, 9.83663 to \
  -0.03, 9.83663 to \
  -0.03, 4.81776 to \
  -6.0768, 4.81776 to \
  -6.0768, 9.83663 front fs empty border lc rgb '#549f' lw 0.1
set object 500 polygon from \
  -6.10246, 9.85625 to \
  -0.03, 9.85625 to \
  -0.03, 4.82738 to \
  -6.10246, 4.82738 to \
  -6.10246, 9.85625 front fs empty border lc rgb '#549f' lw 0.1
set object 501 polygon from \
  -6.12735, 9.87588 to \
  -0.03, 9.87588 to \
  -0.03, 4.837 to \
  -6.12735, 4.837 to \
  -6.12735, 9.87588 front fs empty border lc rgb '#549f' lw 0.1
set object 502 polygon from \
  -6.15147, 9.8955 to \
  -0.03, 9.8955 to \
  -0.03, 4.84662 to \
  -6.15147, 4.84662 to \
  -6.15147, 9.8955 front fs empty border lc rgb '#549f' lw 0.1
set object 503 polygon from \
  -6.17479, 9.91513 to \
  -0.03, 9.91513 to \
  -0.03, 4.85625 to \
  -6.17479, 4.85625 to \
  -6.17479, 9.91513 front fs empty border lc rgb '#549f' lw 0.1
set object 504 polygon from \
  -6.19731, 9.93476 to \
  -0.03, 9.93476 to \
  -0.03, 4.86587 to \
  -6.19731, 4.86587 to \
  -6.19731, 9.93476 front fs empty border lc rgb '#549f' lw 0.1
set object 505 polygon from \
  -6.21901, 9.95439 to \
  -0.03, 9.95439 to \
  -0.03, 4.8755 to \
  -6.21901, 4.8755 to \
  -6.21901, 9.95439 front fs empty border lc rgb '#549f' lw 0.1
set object 506 polygon from \
  -6.23988, 9.97402 to \
  -0.03, 9.97402 to \
  -0.03, 4.88513 to \
  -6.23988, 4.88513 to \
  -6.23988, 9.97402 front fs empty border lc rgb '#549f' lw 0.1
set object 507 polygon from \
  -6.25991, 9.99366 to \
  -0.03, 9.99366 to \
  -0.03, 4.89476 to \
  -6.25991, 4.89476 to \
  -6.25991, 9.99366 front fs empty border lc rgb '#549f' lw 0.1
set object 508 polygon from \
  -6.27909, 10.0133 to \
  -0.03, 10.0133 to \
  -0.03, 4.90439 to \
  -6.27909, 4.90439 to \
  -6.27909, 10.0133 front fs empty border lc rgb '#549f' lw 0.1
set object 509 polygon from \
  -6.29742, 10.0329 to \
  -0.03, 10.0329 to \
  -0.03, 4.91402 to \
  -6.29742, 4.91402 to \
  -6.29742, 10.0329 front fs empty border lc rgb '#549f' lw 0.1
set object 510 polygon from \
  -6.31487, 10.0526 to \
  -0.03, 10.0526 to \
  -0.03, 4.92365 to \
  -6.31487, 4.92365 to \
  -6.31487, 10.0526 front fs empty border lc rgb '#549f' lw 0.1
set object 511 polygon from \
  -6.33145, 10.0722 to \
  -0.03, 10.0722 to \
  -0.03, 4.93329 to \
  -6.33145, 4.93329 to \
  -6.33145, 10.0722 front fs empty border lc rgb '#549f' lw 0.1
set object 512 polygon from \
  -6.34714, 10.0918 to \
  -0.03, 10.0918 to \
  -0.03, 4.94292 to \
  -6.34714, 4.94292 to \
  -6.34714, 10.0918 front fs empty border lc rgb '#549f' lw 0.1
set object 513 polygon from \
  -6.36193, 10.1115 to \
  -0.03, 10.1115 to \
  -0.03, 4.95256 to \
  -6.36193, 4.95256 to \
  -6.36193, 10.1115 front fs empty border lc rgb '#549f' lw 0.1
set object 514 polygon from \
  -6.37582, 10.1311 to \
  -0.03, 10.1311 to \
  -0.03, 4.9622 to \
  -6.37582, 4.9622 to \
  -6.37582, 10.1311 front fs empty border lc rgb '#549f' lw 0.1
set object 515 polygon from \
  -6.38881, 10.1508 to \
  -0.03, 10.1508 to \
  -0.03, 4.97184 to \
  -6.38881, 4.97184 to \
  -6.38881, 10.1508 front fs empty border lc rgb '#549f' lw 0.1
set object 516 polygon from \
  -6.40087, 10.1704 to \
  -0.03, 10.1704 to \
  -0.03, 4.98148 to \
  -6.40087, 4.98148 to \
  -6.40087, 10.1704 front fs empty border lc rgb '#549f' lw 0.1
set object 517 polygon from \
  -6.41202, 10.1901 to \
  -0.03, 10.1901 to \
  -0.03, 4.99112 to \
  -6.41202, 4.99112 to \
  -6.41202, 10.1901 front fs empty border lc rgb '#549f' lw 0.1
set object 518 polygon from \
  -6.42224, 10.2097 to \
  -0.03, 10.2097 to \
  -0.03, 5.00076 to \
  -6.42224, 5.00076 to \
  -6.42224, 10.2097 front fs empty border lc rgb '#549f' lw 0.1
set object 519 polygon from \
  -6.43152, 10.2294 to \
  -0.03, 10.2294 to \
  -0.03, 5.01041 to \
  -6.43152, 5.01041 to \
  -6.43152, 10.2294 front fs empty border lc rgb '#549f' lw 0.1
set object 520 polygon from \
  -6.43988, 10.249 to \
  -0.03, 10.249 to \
  -0.03, 5.02005 to \
  -6.43988, 5.02005 to \
  -6.43988, 10.249 front fs empty border lc rgb '#549f' lw 0.1
set object 521 polygon from \
  -6.44729, 10.2687 to \
  -0.03, 10.2687 to \
  -0.03, 5.0297 to \
  -6.44729, 5.0297 to \
  -6.44729, 10.2687 front fs empty border lc rgb '#549f' lw 0.1
set object 522 polygon from \
  -6.45375, 10.2883 to \
  -0.03, 10.2883 to \
  -0.03, 5.03935 to \
  -6.45375, 5.03935 to \
  -6.45375, 10.2883 front fs empty border lc rgb '#549f' lw 0.1
set object 523 polygon from \
  -6.45927, 10.308 to \
  -0.03, 10.308 to \
  -0.03, 5.049 to \
  -6.45927, 5.049 to \
  -6.45927, 10.308 front fs empty border lc rgb '#549f' lw 0.1
set object 524 polygon from \
  -6.46384, 10.3276 to \
  -0.03, 10.3276 to \
  -0.03, 5.05865 to \
  -6.46384, 5.05865 to \
  -6.46384, 10.3276 front fs empty border lc rgb '#549f' lw 0.1
set object 525 polygon from \
  -6.46746, 10.3473 to \
  -0.03, 10.3473 to \
  -0.03, 5.0683 to \
  -6.46746, 5.0683 to \
  -6.46746, 10.3473 front fs empty border lc rgb '#549f' lw 0.1
set object 526 polygon from \
  -6.47013, 10.3669 to \
  -0.03, 10.3669 to \
  -0.03, 5.07795 to \
  -6.47013, 5.07795 to \
  -6.47013, 10.3669 front fs empty border lc rgb '#549f' lw 0.1
set object 527 polygon from \
  -6.47184, 10.3866 to \
  -0.03, 10.3866 to \
  -0.03, 5.08761 to \
  -6.47184, 5.08761 to \
  -6.47184, 10.3866 front fs empty border lc rgb '#549f' lw 0.1
set object 528 polygon from \
  -6.4726, 10.4062 to \
  -0.03, 10.4062 to \
  -0.03, 5.09726 to \
  -6.4726, 5.09726 to \
  -6.4726, 10.4062 front fs empty border lc rgb '#549f' lw 0.1
set object 529 polygon from \
  -6.4726, 10.4259 to \
  -0.03, 10.4259 to \
  -0.03, 5.10692 to \
  -6.4726, 5.10692 to \
  -6.4726, 10.4259 front fs empty border lc rgb '#549f' lw 0.1
set object 530 polygon from \
  -6.4724, 10.4456 to \
  -0.03, 10.4456 to \
  -0.03, 5.11658 to \
  -6.4724, 5.11658 to \
  -6.4724, 10.4456 front fs empty border lc rgb '#549f' lw 0.1
set object 531 polygon from \
  -6.47125, 10.4652 to \
  -0.03, 10.4652 to \
  -0.03, 5.12624 to \
  -6.47125, 5.12624 to \
  -6.47125, 10.4652 front fs empty border lc rgb '#549f' lw 0.1
set object 532 polygon from \
  -6.46915, 10.4849 to \
  -0.03, 10.4849 to \
  -0.03, 5.1359 to \
  -6.46915, 5.1359 to \
  -6.46915, 10.4849 front fs empty border lc rgb '#549f' lw 0.1
set object 533 polygon from \
  -6.4661, 10.5046 to \
  -0.03, 10.5046 to \
  -0.03, 5.14556 to \
  -6.4661, 5.14556 to \
  -6.4661, 10.5046 front fs empty border lc rgb '#549f' lw 0.1
set object 534 polygon from \
  -6.4621, 10.5242 to \
  -0.03, 10.5242 to \
  -0.03, 5.15522 to \
  -6.4621, 5.15522 to \
  -6.4621, 10.5242 front fs empty border lc rgb '#549f' lw 0.1
set object 535 polygon from \
  -6.45715, 10.5439 to \
  -0.03, 10.5439 to \
  -0.03, 5.16489 to \
  -6.45715, 5.16489 to \
  -6.45715, 10.5439 front fs empty border lc rgb '#549f' lw 0.1
set object 536 polygon from \
  -6.45126, 10.5636 to \
  -0.03, 10.5636 to \
  -0.03, 5.17455 to \
  -6.45126, 5.17455 to \
  -6.45126, 10.5636 front fs empty border lc rgb '#549f' lw 0.1
set object 537 polygon from \
  -6.44444, 10.5832 to \
  -0.03, 10.5832 to \
  -0.03, 5.18422 to \
  -6.44444, 5.18422 to \
  -6.44444, 10.5832 front fs empty border lc rgb '#549f' lw 0.1
set object 538 polygon from \
  -6.43667, 10.6029 to \
  -0.03, 10.6029 to \
  -0.03, 5.19389 to \
  -6.43667, 5.19389 to \
  -6.43667, 10.6029 front fs empty border lc rgb '#549f' lw 0.1
set object 539 polygon from \
  -6.42798, 10.6226 to \
  -0.03, 10.6226 to \
  -0.03, 5.20356 to \
  -6.42798, 5.20356 to \
  -6.42798, 10.6226 front fs empty border lc rgb '#549f' lw 0.1
set object 540 polygon from \
  -6.41836, 10.6422 to \
  -0.03, 10.6422 to \
  -0.03, 5.21323 to \
  -6.41836, 5.21323 to \
  -6.41836, 10.6422 front fs empty border lc rgb '#549f' lw 0.1
set object 541 polygon from \
  -6.40781, 10.6619 to \
  -0.03, 10.6619 to \
  -0.03, 5.2229 to \
  -6.40781, 5.2229 to \
  -6.40781, 10.6619 front fs empty border lc rgb '#549f' lw 0.1
set object 542 polygon from \
  -6.39635, 10.6816 to \
  -0.03, 10.6816 to \
  -0.03, 5.23257 to \
  -6.39635, 5.23257 to \
  -6.39635, 10.6816 front fs empty border lc rgb '#549f' lw 0.1
set object 543 polygon from \
  -6.38399, 10.7013 to \
  -0.03, 10.7013 to \
  -0.03, 5.24225 to \
  -6.38399, 5.24225 to \
  -6.38399, 10.7013 front fs empty border lc rgb '#549f' lw 0.1
set object 544 polygon from \
  -6.37072, 10.721 to \
  -0.03, 10.721 to \
  -0.03, 5.25192 to \
  -6.37072, 5.25192 to \
  -6.37072, 10.721 front fs empty border lc rgb '#549f' lw 0.1
set object 545 polygon from \
  -6.35656, 10.7406 to \
  -0.03, 10.7406 to \
  -0.03, 5.2616 to \
  -6.35656, 5.2616 to \
  -6.35656, 10.7406 front fs empty border lc rgb '#549f' lw 0.1
set object 546 polygon from \
  -6.3415, 10.7603 to \
  -0.03, 10.7603 to \
  -0.03, 5.27128 to \
  -6.3415, 5.27128 to \
  -6.3415, 10.7603 front fs empty border lc rgb '#549f' lw 0.1
set object 547 polygon from \
  -6.32557, 10.78 to \
  -0.03, 10.78 to \
  -0.03, 5.28096 to \
  -6.32557, 5.28096 to \
  -6.32557, 10.78 front fs empty border lc rgb '#549f' lw 0.1
set object 548 polygon from \
  -6.30877, 10.7997 to \
  -0.03, 10.7997 to \
  -0.03, 5.29064 to \
  -6.30877, 5.29064 to \
  -6.30877, 10.7997 front fs empty border lc rgb '#549f' lw 0.1
set object 549 polygon from \
  -6.2911, 10.8194 to \
  -0.03, 10.8194 to \
  -0.03, 5.30032 to \
  -6.2911, 5.30032 to \
  -6.2911, 10.8194 front fs empty border lc rgb '#549f' lw 0.1
set object 550 polygon from \
  -6.27258, 10.8391 to \
  -0.03, 10.8391 to \
  -0.03, 5.31 to \
  -6.27258, 5.31 to \
  -6.27258, 10.8391 front fs empty border lc rgb '#549f' lw 0.1
set object 551 polygon from \
  -6.25322, 10.8588 to \
  -0.03, 10.8588 to \
  -0.03, 5.31969 to \
  -6.25322, 5.31969 to \
  -6.25322, 10.8588 front fs empty border lc rgb '#549f' lw 0.1
set object 552 polygon from \
  -6.23302, 10.8784 to \
  -0.03, 10.8784 to \
  -0.03, 5.32937 to \
  -6.23302, 5.32937 to \
  -6.23302, 10.8784 front fs empty border lc rgb '#549f' lw 0.1
set object 553 polygon from \
  -6.212, 10.8981 to \
  -0.03, 10.8981 to \
  -0.03, 5.33906 to \
  -6.212, 5.33906 to \
  -6.212, 10.8981 front fs empty border lc rgb '#549f' lw 0.1
set object 554 polygon from \
  -6.19017, 10.9178 to \
  -0.03, 10.9178 to \
  -0.03, 5.34875 to \
  -6.19017, 5.34875 to \
  -6.19017, 10.9178 front fs empty border lc rgb '#549f' lw 0.1
set object 555 polygon from \
  -6.16753, 10.9375 to \
  -0.03, 10.9375 to \
  -0.03, 5.35844 to \
  -6.16753, 5.35844 to \
  -6.16753, 10.9375 front fs empty border lc rgb '#549f' lw 0.1
set object 556 polygon from \
  -6.1441, 10.9572 to \
  -0.03, 10.9572 to \
  -0.03, 5.36813 to \
  -6.1441, 5.36813 to \
  -6.1441, 10.9572 front fs empty border lc rgb '#549f' lw 0.1
set object 557 polygon from \
  -6.11989, 10.9769 to \
  -0.03, 10.9769 to \
  -0.03, 5.37782 to \
  -6.11989, 5.37782 to \
  -6.11989, 10.9769 front fs empty border lc rgb '#549f' lw 0.1
set object 558 polygon from \
  -6.09492, 10.9966 to \
  -0.03, 10.9966 to \
  -0.03, 5.38751 to \
  -6.09492, 5.38751 to \
  -6.09492, 10.9966 front fs empty border lc rgb '#549f' lw 0.1
set object 559 polygon from \
  -6.06918, 11.0163 to \
  -0.03, 11.0163 to \
  -0.03, 5.39721 to \
  -6.06918, 5.39721 to \
  -6.06918, 11.0163 front fs empty border lc rgb '#549f' lw 0.1
set object 560 polygon from \
  -6.04271, 11.036 to \
  -0.03, 11.036 to \
  -0.03, 5.4069 to \
  -6.04271, 5.4069 to \
  -6.04271, 11.036 front fs empty border lc rgb '#549f' lw 0.1
set object 561 polygon from \
  -6.0155, 11.0557 to \
  -0.03, 11.0557 to \
  -0.03, 5.4166 to \
  -6.0155, 5.4166 to \
  -6.0155, 11.0557 front fs empty border lc rgb '#549f' lw 0.1
set object 562 polygon from \
  -5.98758, 11.0754 to \
  -0.03, 11.0754 to \
  -0.03, 5.4263 to \
  -5.98758, 5.4263 to \
  -5.98758, 11.0754 front fs empty border lc rgb '#549f' lw 0.1
set object 563 polygon from \
  -5.95895, 11.0951 to \
  -0.03, 11.0951 to \
  -0.03, 5.436 to \
  -5.95895, 5.436 to \
  -5.95895, 11.0951 front fs empty border lc rgb '#549f' lw 0.1
set object 564 polygon from \
  -5.92964, 11.1148 to \
  -0.03, 11.1148 to \
  -0.03, 5.4457 to \
  -5.92964, 5.4457 to \
  -5.92964, 11.1148 front fs empty border lc rgb '#549f' lw 0.1
set object 565 polygon from \
  -5.89964, 11.1345 to \
  -0.03, 11.1345 to \
  -0.03, 5.4554 to \
  -5.89964, 5.4554 to \
  -5.89964, 11.1345 front fs empty border lc rgb '#549f' lw 0.1
set object 566 polygon from \
  -5.86899, 11.1542 to \
  -0.03, 11.1542 to \
  -0.03, 5.4651 to \
  -5.86899, 5.4651 to \
  -5.86899, 11.1542 front fs empty border lc rgb '#549f' lw 0.1
set object 567 polygon from \
  -5.83768, 11.1739 to \
  -0.03, 11.1739 to \
  -0.03, 5.47481 to \
  -5.83768, 5.47481 to \
  -5.83768, 11.1739 front fs empty border lc rgb '#549f' lw 0.1
set object 568 polygon from \
  -5.80574, 11.1936 to \
  -0.03, 11.1936 to \
  -0.03, 5.48451 to \
  -5.80574, 5.48451 to \
  -5.80574, 11.1936 front fs empty border lc rgb '#549f' lw 0.1
set object 569 polygon from \
  -5.77319, 11.2134 to \
  -0.03, 11.2134 to \
  -0.03, 5.49422 to \
  -5.77319, 5.49422 to \
  -5.77319, 11.2134 front fs empty border lc rgb '#549f' lw 0.1
set object 570 polygon from \
  -5.74002, 11.2331 to \
  -0.03, 11.2331 to \
  -0.03, 5.50393 to \
  -5.74002, 5.50393 to \
  -5.74002, 11.2331 front fs empty border lc rgb '#549f' lw 0.1
set object 571 polygon from \
  -5.70627, 11.2528 to \
  -0.03, 11.2528 to \
  -0.03, 5.51364 to \
  -5.70627, 5.51364 to \
  -5.70627, 11.2528 front fs empty border lc rgb '#549f' lw 0.1
set object 572 polygon from \
  -5.67195, 11.2725 to \
  -0.03, 11.2725 to \
  -0.03, 5.52335 to \
  -5.67195, 5.52335 to \
  -5.67195, 11.2725 front fs empty border lc rgb '#549f' lw 0.1
set object 573 polygon from \
  -5.63706, 11.2922 to \
  -0.03, 11.2922 to \
  -0.03, 5.53306 to \
  -5.63706, 5.53306 to \
  -5.63706, 11.2922 front fs empty border lc rgb '#549f' lw 0.1
set object 574 polygon from \
  -5.60164, 11.3119 to \
  -0.03, 11.3119 to \
  -0.03, 5.54277 to \
  -5.60164, 5.54277 to \
  -5.60164, 11.3119 front fs empty border lc rgb '#549f' lw 0.1
set object 575 polygon from \
  -5.56568, 11.3316 to \
  -0.03, 11.3316 to \
  -0.03, 5.55249 to \
  -5.56568, 5.55249 to \
  -5.56568, 11.3316 front fs empty border lc rgb '#549f' lw 0.1
set object 576 polygon from \
  -5.55315, 11.3514 to \
  -0.03, 11.3514 to \
  -0.03, 5.5622 to \
  -5.55315, 5.5622 to \
  -5.55315, 11.3514 front fs empty border lc rgb '#549f' lw 0.1
set object 577 polygon from \
  -5.5687, 11.3711 to \
  -0.03, 11.3711 to \
  -0.03, 5.57192 to \
  -5.5687, 5.57192 to \
  -5.5687, 11.3711 front fs empty border lc rgb '#549f' lw 0.1
set object 578 polygon from \
  -5.58363, 11.3908 to \
  -0.03, 11.3908 to \
  -0.03, 5.58164 to \
  -5.58363, 5.58164 to \
  -5.58363, 11.3908 front fs empty border lc rgb '#549f' lw 0.1
set object 579 polygon from \
  -5.59791, 11.4105 to \
  -0.03, 11.4105 to \
  -0.03, 5.59136 to \
  -5.59791, 5.59136 to \
  -5.59791, 11.4105 front fs empty border lc rgb '#549f' lw 0.1
set object 580 polygon from \
  -5.61154, 11.4302 to \
  -0.03, 11.4302 to \
  -0.03, 5.60108 to \
  -5.61154, 5.60108 to \
  -5.61154, 11.4302 front fs empty border lc rgb '#549f' lw 0.1
set object 581 polygon from \
  -5.62449, 11.45 to \
  -0.03, 11.45 to \
  -0.03, 5.6108 to \
  -5.62449, 5.6108 to \
  -5.62449, 11.45 front fs empty border lc rgb '#549f' lw 0.1
set object 582 polygon from \
  -5.63675, 11.4697 to \
  -0.03, 11.4697 to \
  -0.03, 5.62052 to \
  -5.63675, 5.62052 to \
  -5.63675, 11.4697 front fs empty border lc rgb '#549f' lw 0.1
set object 583 polygon from \
  -5.64831, 11.4894 to \
  -0.03, 11.4894 to \
  -0.03, 5.63025 to \
  -5.64831, 5.63025 to \
  -5.64831, 11.4894 front fs empty border lc rgb '#549f' lw 0.1
set object 584 polygon from \
  -5.65915, 11.5092 to \
  -0.03, 11.5092 to \
  -0.03, 5.63997 to \
  -5.65915, 5.63997 to \
  -5.65915, 11.5092 front fs empty border lc rgb '#549f' lw 0.1
set object 585 polygon from \
  -5.66924, 11.5289 to \
  -0.03, 11.5289 to \
  -0.03, 5.6497 to \
  -5.66924, 5.6497 to \
  -5.66924, 11.5289 front fs empty border lc rgb '#549f' lw 0.1
set object 586 polygon from \
  -5.67858, 11.5486 to \
  -0.03, 11.5486 to \
  -0.03, 5.65943 to \
  -5.67858, 5.65943 to \
  -5.67858, 11.5486 front fs empty border lc rgb '#549f' lw 0.1
set object 587 polygon from \
  -5.68716, 11.5684 to \
  -0.03, 11.5684 to \
  -0.03, 5.66916 to \
  -5.68716, 5.66916 to \
  -5.68716, 11.5684 front fs empty border lc rgb '#549f' lw 0.1
set object 588 polygon from \
  -5.69494, 11.5881 to \
  -0.03, 11.5881 to \
  -0.03, 5.67889 to \
  -5.69494, 5.67889 to \
  -5.69494, 11.5881 front fs empty border lc rgb '#549f' lw 0.1
set object 589 polygon from \
  -5.70193, 11.6078 to \
  -0.03, 11.6078 to \
  -0.03, 5.68862 to \
  -5.70193, 5.68862 to \
  -5.70193, 11.6078 front fs empty border lc rgb '#549f' lw 0.1
set object 590 polygon from \
  -5.70811, 11.6276 to \
  -0.03, 11.6276 to \
  -0.03, 5.69835 to \
  -5.70811, 5.69835 to \
  -5.70811, 11.6276 front fs empty border lc rgb '#549f' lw 0.1
set object 591 polygon from \
  -5.71345, 11.6473 to \
  -0.03, 11.6473 to \
  -0.03, 5.70809 to \
  -5.71345, 5.70809 to \
  -5.71345, 11.6473 front fs empty border lc rgb '#549f' lw 0.1
set object 592 polygon from \
  -5.71795, 11.667 to \
  -0.03, 11.667 to \
  -0.03, 5.71782 to \
  -5.71795, 5.71782 to \
  -5.71795, 11.667 front fs empty border lc rgb '#549f' lw 0.1
set object 593 polygon from \
  -5.7216, 11.6868 to \
  -0.03, 11.6868 to \
  -0.03, 5.72756 to \
  -5.7216, 5.72756 to \
  -5.7216, 11.6868 front fs empty border lc rgb '#549f' lw 0.1
set object 594 polygon from \
  -5.72437, 11.7065 to \
  -0.03, 11.7065 to \
  -0.03, 5.7373 to \
  -5.72437, 5.7373 to \
  -5.72437, 11.7065 front fs empty border lc rgb '#549f' lw 0.1
set object 595 polygon from \
  -5.72626, 11.7263 to \
  -0.03, 11.7263 to \
  -0.03, 5.74704 to \
  -5.72626, 5.74704 to \
  -5.72626, 11.7263 front fs empty border lc rgb '#549f' lw 0.1
set object 596 polygon from \
  -5.72726, 11.746 to \
  -0.03, 11.746 to \
  -0.03, 5.75678 to \
  -5.72726, 5.75678 to \
  -5.72726, 11.746 front fs empty border lc rgb '#549f' lw 0.1
set object 597 polygon from \
  -5.72734, 11.7658 to \
  -0.03, 11.7658 to \
  -0.03, 5.76652 to \
  -5.72734, 5.76652 to \
  -5.72734, 11.7658 front fs empty border lc rgb '#549f' lw 0.1
set object 598 polygon from \
  -5.72734, 11.7855 to \
  -0.03, 11.7855 to \
  -0.03, 5.77626 to \
  -5.72734, 5.77626 to \
  -5.72734, 11.7855 front fs empty border lc rgb '#549f' lw 0.1
set object 599 polygon from \
  -5.72651, 11.8053 to \
  -0.03, 11.8053 to \
  -0.03, 5.78601 to \
  -5.72651, 5.78601 to \
  -5.72651, 11.8053 front fs empty border lc rgb '#549f' lw 0.1
set object 600 polygon from \
  -5.72473, 11.825 to \
  -0.03, 11.825 to \
  -0.03, 5.79575 to \
  -5.72473, 5.79575 to \
  -5.72473, 11.825 front fs empty border lc rgb '#549f' lw 0.1
set object 601 polygon from \
  -5.72201, 11.8448 to \
  -0.03, 11.8448 to \
  -0.03, 5.8055 to \
  -5.72201, 5.8055 to \
  -5.72201, 11.8448 front fs empty border lc rgb '#549f' lw 0.1
set object 602 polygon from \
  -5.71834, 11.8645 to \
  -0.03, 11.8645 to \
  -0.03, 5.81525 to \
  -5.71834, 5.81525 to \
  -5.71834, 11.8645 front fs empty border lc rgb '#549f' lw 0.1
set object 603 polygon from \
  -5.71369, 11.8843 to \
  -0.03, 11.8843 to \
  -0.03, 5.825 to \
  -5.71369, 5.825 to \
  -5.71369, 11.8843 front fs empty border lc rgb '#549f' lw 0.1
set object 604 polygon from \
  -5.70807, 11.904 to \
  -0.03, 11.904 to \
  -0.03, 5.83475 to \
  -5.70807, 5.83475 to \
  -5.70807, 11.904 front fs empty border lc rgb '#549f' lw 0.1
set object 605 polygon from \
  -5.70146, 11.9238 to \
  -0.03, 11.9238 to \
  -0.03, 5.8445 to \
  -5.70146, 5.8445 to \
  -5.70146, 11.9238 front fs empty border lc rgb '#549f' lw 0.1
set object 606 polygon from \
  -5.69385, 11.9435 to \
  -0.03, 11.9435 to \
  -0.03, 5.85425 to \
  -5.69385, 5.85425 to \
  -5.69385, 11.9435 front fs empty border lc rgb '#549f' lw 0.1
set object 607 polygon from \
  -5.68523, 11.9633 to \
  -0.03, 11.9633 to \
  -0.03, 5.86401 to \
  -5.68523, 5.86401 to \
  -5.68523, 11.9633 front fs empty border lc rgb '#549f' lw 0.1
set object 608 polygon from \
  -5.67559, 11.983 to \
  -0.03, 11.983 to \
  -0.03, 5.87376 to \
  -5.67559, 5.87376 to \
  -5.67559, 11.983 front fs empty border lc rgb '#549f' lw 0.1
set object 609 polygon from \
  -5.66493, 12.0028 to \
  -0.03, 12.0028 to \
  -0.03, 5.88352 to \
  -5.66493, 5.88352 to \
  -5.66493, 12.0028 front fs empty border lc rgb '#549f' lw 0.1
set object 610 polygon from \
  -5.65324, 12.0226 to \
  -0.03, 12.0226 to \
  -0.03, 5.89328 to \
  -5.65324, 5.89328 to \
  -5.65324, 12.0226 front fs empty border lc rgb '#549f' lw 0.1
set object 611 polygon from \
  -5.6405, 12.0423 to \
  -0.03, 12.0423 to \
  -0.03, 5.90304 to \
  -5.6405, 5.90304 to \
  -5.6405, 12.0423 front fs empty border lc rgb '#549f' lw 0.1
set object 612 polygon from \
  -5.62671, 12.0621 to \
  -0.03, 12.0621 to \
  -0.03, 5.9128 to \
  -5.62671, 5.9128 to \
  -5.62671, 12.0621 front fs empty border lc rgb '#549f' lw 0.1
set object 613 polygon from \
  -5.61187, 12.0819 to \
  -0.03, 12.0819 to \
  -0.03, 5.92256 to \
  -5.61187, 5.92256 to \
  -5.61187, 12.0819 front fs empty border lc rgb '#549f' lw 0.1
set object 614 polygon from \
  -5.59596, 12.1016 to \
  -0.03, 12.1016 to \
  -0.03, 5.93232 to \
  -5.59596, 5.93232 to \
  -5.59596, 12.1016 front fs empty border lc rgb '#549f' lw 0.1
set object 615 polygon from \
  -5.57899, 12.1214 to \
  -0.03, 12.1214 to \
  -0.03, 5.94209 to \
  -5.57899, 5.94209 to \
  -5.57899, 12.1214 front fs empty border lc rgb '#549f' lw 0.1
set object 616 polygon from \
  -5.56094, 12.1412 to \
  -0.03, 12.1412 to \
  -0.03, 5.95185 to \
  -5.56094, 5.95185 to \
  -5.56094, 12.1412 front fs empty border lc rgb '#549f' lw 0.1
set object 617 polygon from \
  -5.54181, 12.1609 to \
  -0.03, 12.1609 to \
  -0.03, 5.96162 to \
  -5.54181, 5.96162 to \
  -5.54181, 12.1609 front fs empty border lc rgb '#549f' lw 0.1
set object 618 polygon from \
  -5.5216, 12.1807 to \
  -0.03, 12.1807 to \
  -0.03, 5.97139 to \
  -5.5216, 5.97139 to \
  -5.5216, 12.1807 front fs empty border lc rgb '#549f' lw 0.1
set object 619 polygon from \
  -5.50031, 12.2005 to \
  -0.03, 12.2005 to \
  -0.03, 5.98116 to \
  -5.50031, 5.98116 to \
  -5.50031, 12.2005 front fs empty border lc rgb '#549f' lw 0.1
set object 620 polygon from \
  -5.47792, 12.2202 to \
  -0.03, 12.2202 to \
  -0.03, 5.99093 to \
  -5.47792, 5.99093 to \
  -5.47792, 12.2202 front fs empty border lc rgb '#549f' lw 0.1
set object 621 polygon from \
  -5.45443, 12.24 to \
  -0.03, 12.24 to \
  -0.03, 6.0007 to \
  -5.45443, 6.0007 to \
  -5.45443, 12.24 front fs empty border lc rgb '#549f' lw 0.1
set object 622 polygon from \
  -5.42985, 12.2598 to \
  -0.03, 12.2598 to \
  -0.03, 6.01047 to \
  -5.42985, 6.01047 to \
  -5.42985, 12.2598 front fs empty border lc rgb '#549f' lw 0.1
set object 623 polygon from \
  -5.40417, 12.2796 to \
  -0.03, 12.2796 to \
  -0.03, 6.02025 to \
  -5.40417, 6.02025 to \
  -5.40417, 12.2796 front fs empty border lc rgb '#549f' lw 0.1
set object 624 polygon from \
  -5.37739, 12.2994 to \
  -0.03, 12.2994 to \
  -0.03, 6.03002 to \
  -5.37739, 6.03002 to \
  -5.37739, 12.2994 front fs empty border lc rgb '#549f' lw 0.1
set object 625 polygon from \
  -5.3495, 12.3191 to \
  -0.03, 12.3191 to \
  -0.03, 6.0398 to \
  -5.3495, 6.0398 to \
  -5.3495, 12.3191 front fs empty border lc rgb '#549f' lw 0.1
set object 626 polygon from \
  -5.32051, 12.3389 to \
  -0.03, 12.3389 to \
  -0.03, 6.04958 to \
  -5.32051, 6.04958 to \
  -5.32051, 12.3389 front fs empty border lc rgb '#549f' lw 0.1
set object 627 polygon from \
  -5.29042, 12.3587 to \
  -0.03, 12.3587 to \
  -0.03, 6.05936 to \
  -5.29042, 6.05936 to \
  -5.29042, 12.3587 front fs empty border lc rgb '#549f' lw 0.1
set object 628 polygon from \
  -5.25923, 12.3785 to \
  -0.03, 12.3785 to \
  -0.03, 6.06914 to \
  -5.25923, 6.06914 to \
  -5.25923, 12.3785 front fs empty border lc rgb '#549f' lw 0.1
set object 629 polygon from \
  -5.22694, 12.3983 to \
  -0.03, 12.3983 to \
  -0.03, 6.07892 to \
  -5.22694, 6.07892 to \
  -5.22694, 12.3983 front fs empty border lc rgb '#549f' lw 0.1
set object 630 polygon from \
  -5.19354, 12.4181 to \
  -0.03, 12.4181 to \
  -0.03, 6.0887 to \
  -5.19354, 6.0887 to \
  -5.19354, 12.4181 front fs empty border lc rgb '#549f' lw 0.1
set object 631 polygon from \
  -5.15905, 12.4379 to \
  -0.03, 12.4379 to \
  -0.03, 6.09849 to \
  -5.15905, 6.09849 to \
  -5.15905, 12.4379 front fs empty border lc rgb '#549f' lw 0.1
set object 632 polygon from \
  -5.12345, 12.4576 to \
  -0.03, 12.4576 to \
  -0.03, 6.10827 to \
  -5.12345, 6.10827 to \
  -5.12345, 12.4576 front fs empty border lc rgb '#549f' lw 0.1
set object 633 polygon from \
  -5.08677, 12.4774 to \
  -0.03, 12.4774 to \
  -0.03, 6.11806 to \
  -5.08677, 6.11806 to \
  -5.08677, 12.4774 front fs empty border lc rgb '#549f' lw 0.1
set object 634 polygon from \
  -5.049, 12.4972 to \
  -0.03, 12.4972 to \
  -0.03, 6.12785 to \
  -5.049, 6.12785 to \
  -5.049, 12.4972 front fs empty border lc rgb '#549f' lw 0.1
set object 635 polygon from \
  -5.01014, 12.517 to \
  -0.03, 12.517 to \
  -0.03, 6.13764 to \
  -5.01014, 6.13764 to \
  -5.01014, 12.517 front fs empty border lc rgb '#549f' lw 0.1
set object 636 polygon from \
  -4.97019, 12.5368 to \
  -0.03, 12.5368 to \
  -0.03, 6.14743 to \
  -4.97019, 6.14743 to \
  -4.97019, 12.5368 front fs empty border lc rgb '#549f' lw 0.1
set object 637 polygon from \
  -4.92917, 12.5566 to \
  -0.03, 12.5566 to \
  -0.03, 6.15722 to \
  -4.92917, 6.15722 to \
  -4.92917, 12.5566 front fs empty border lc rgb '#549f' lw 0.1
set object 638 polygon from \
  -4.88708, 12.5764 to \
  -0.03, 12.5764 to \
  -0.03, 6.16701 to \
  -4.88708, 6.16701 to \
  -4.88708, 12.5764 front fs empty border lc rgb '#549f' lw 0.1
set object 639 polygon from \
  -4.84393, 12.5962 to \
  -0.03, 12.5962 to \
  -0.03, 6.17681 to \
  -4.84393, 6.17681 to \
  -4.84393, 12.5962 front fs empty border lc rgb '#549f' lw 0.1
set object 640 polygon from \
  -4.79971, 12.616 to \
  -0.03, 12.616 to \
  -0.03, 6.1866 to \
  -4.79971, 6.1866 to \
  -4.79971, 12.616 front fs empty border lc rgb '#549f' lw 0.1
set object 641 polygon from \
  -4.75445, 12.6358 to \
  -0.03, 12.6358 to \
  -0.03, 6.1964 to \
  -4.75445, 6.1964 to \
  -4.75445, 12.6358 front fs empty border lc rgb '#549f' lw 0.1
set object 642 polygon from \
  -4.70814, 12.6556 to \
  -0.03, 12.6556 to \
  -0.03, 6.2062 to \
  -4.70814, 6.2062 to \
  -4.70814, 12.6556 front fs empty border lc rgb '#549f' lw 0.1
set object 643 polygon from \
  -4.66079, 12.6754 to \
  -0.03, 12.6754 to \
  -0.03, 6.216 to \
  -4.66079, 6.216 to \
  -4.66079, 12.6754 front fs empty border lc rgb '#549f' lw 0.1
set object 644 polygon from \
  -4.61242, 12.6952 to \
  -0.03, 12.6952 to \
  -0.03, 6.2258 to \
  -4.61242, 6.2258 to \
  -4.61242, 12.6952 front fs empty border lc rgb '#549f' lw 0.1
set object 645 polygon from \
  -4.56302, 12.715 to \
  -0.03, 12.715 to \
  -0.03, 6.2356 to \
  -4.56302, 6.2356 to \
  -4.56302, 12.715 front fs empty border lc rgb '#549f' lw 0.1
set object 646 polygon from \
  -4.51262, 12.7348 to \
  -0.03, 12.7348 to \
  -0.03, 6.2454 to \
  -4.51262, 6.2454 to \
  -4.51262, 12.7348 front fs empty border lc rgb '#549f' lw 0.1
set object 647 polygon from \
  -4.46122, 12.7546 to \
  -0.03, 12.7546 to \
  -0.03, 6.25521 to \
  -4.46122, 6.25521 to \
  -4.46122, 12.7546 front fs empty border lc rgb '#549f' lw 0.1
set object 648 polygon from \
  -4.40883, 12.7744 to \
  -0.03, 12.7744 to \
  -0.03, 6.26501 to \
  -4.40883, 6.26501 to \
  -4.40883, 12.7744 front fs empty border lc rgb '#549f' lw 0.1
set object 649 polygon from \
  -4.35854, 12.7943 to \
  -0.03, 12.7943 to \
  -0.03, 6.27482 to \
  -4.35854, 6.27482 to \
  -4.35854, 12.7943 front fs empty border lc rgb '#549f' lw 0.1
set object 650 polygon from \
  -4.31188, 12.8141 to \
  -0.03, 12.8141 to \
  -0.03, 6.28463 to \
  -4.31188, 6.28463 to \
  -4.31188, 12.8141 front fs empty border lc rgb '#549f' lw 0.1
set object 651 polygon from \
  -4.26423, 12.8339 to \
  -0.03, 12.8339 to \
  -0.03, 6.29444 to \
  -4.26423, 6.29444 to \
  -4.26423, 12.8339 front fs empty border lc rgb '#549f' lw 0.1
set object 652 polygon from \
  -4.2156, 12.8537 to \
  -0.03, 12.8537 to \
  -0.03, 6.30425 to \
  -4.2156, 6.30425 to \
  -4.2156, 12.8537 front fs empty border lc rgb '#549f' lw 0.1
set object 653 polygon from \
  -4.166, 12.8735 to \
  -0.03, 12.8735 to \
  -0.03, 6.31406 to \
  -4.166, 6.31406 to \
  -4.166, 12.8735 front fs empty border lc rgb '#549f' lw 0.1
set object 654 polygon from \
  -4.11546, 12.8933 to \
  -0.03, 12.8933 to \
  -0.03, 6.32387 to \
  -4.11546, 6.32387 to \
  -4.11546, 12.8933 front fs empty border lc rgb '#549f' lw 0.1
set object 655 polygon from \
  -4.06398, 12.9131 to \
  -0.03, 12.9131 to \
  -0.03, 6.33369 to \
  -4.06398, 6.33369 to \
  -4.06398, 12.9131 front fs empty border lc rgb '#549f' lw 0.1
set object 656 polygon from \
  -4.01157, 12.933 to \
  -0.03, 12.933 to \
  -0.03, 6.3435 to \
  -4.01157, 6.3435 to \
  -4.01157, 12.933 front fs empty border lc rgb '#549f' lw 0.1
set object 657 polygon from \
  -3.95826, 12.9528 to \
  -0.03, 12.9528 to \
  -0.03, 6.35332 to \
  -3.95826, 6.35332 to \
  -3.95826, 12.9528 front fs empty border lc rgb '#549f' lw 0.1
set object 658 polygon from \
  -3.90405, 12.9726 to \
  -0.03, 12.9726 to \
  -0.03, 6.36314 to \
  -3.90405, 6.36314 to \
  -3.90405, 12.9726 front fs empty border lc rgb '#549f' lw 0.1
set object 659 polygon from \
  -3.84896, 12.9924 to \
  -0.03, 12.9924 to \
  -0.03, 6.37296 to \
  -3.84896, 6.37296 to \
  -3.84896, 12.9924 front fs empty border lc rgb '#549f' lw 0.1
set object 660 polygon from \
  -3.79301, 13.0122 to \
  -0.03, 13.0122 to \
  -0.03, 6.38278 to \
  -3.79301, 6.38278 to \
  -3.79301, 13.0122 front fs empty border lc rgb '#549f' lw 0.1
set object 661 polygon from \
  -3.73622, 13.0321 to \
  -0.03, 13.0321 to \
  -0.03, 6.3926 to \
  -3.73622, 6.3926 to \
  -3.73622, 13.0321 front fs empty border lc rgb '#549f' lw 0.1
set object 662 polygon from \
  -3.6786, 13.0519 to \
  -0.03, 13.0519 to \
  -0.03, 6.40242 to \
  -3.6786, 6.40242 to \
  -3.6786, 13.0519 front fs empty border lc rgb '#549f' lw 0.1
set object 663 polygon from \
  -3.62016, 13.0717 to \
  -0.03, 13.0717 to \
  -0.03, 6.41225 to \
  -3.62016, 6.41225 to \
  -3.62016, 13.0717 front fs empty border lc rgb '#549f' lw 0.1
set object 664 polygon from \
  -3.56094, 13.0916 to \
  -0.03, 13.0916 to \
  -0.03, 6.42207 to \
  -3.56094, 6.42207 to \
  -3.56094, 13.0916 front fs empty border lc rgb '#549f' lw 0.1
set object 665 polygon from \
  -3.50093, 13.1114 to \
  -0.03, 13.1114 to \
  -0.03, 6.4319 to \
  -3.50093, 6.4319 to \
  -3.50093, 13.1114 front fs empty border lc rgb '#549f' lw 0.1
set object 666 polygon from \
  -3.44017, 13.1312 to \
  -0.03, 13.1312 to \
  -0.03, 6.44173 to \
  -3.44017, 6.44173 to \
  -3.44017, 13.1312 front fs empty border lc rgb '#549f' lw 0.1
set object 667 polygon from \
  -3.37867, 13.1511 to \
  -0.03, 13.1511 to \
  -0.03, 6.45156 to \
  -3.37867, 6.45156 to \
  -3.37867, 13.1511 front fs empty border lc rgb '#549f' lw 0.1
set object 668 polygon from \
  -3.31645, 13.1709 to \
  -0.03, 13.1709 to \
  -0.03, 6.46139 to \
  -3.31645, 6.46139 to \
  -3.31645, 13.1709 front fs empty border lc rgb '#549f' lw 0.1
set object 669 polygon from \
  -3.25352, 13.1907 to \
  -0.03, 13.1907 to \
  -0.03, 6.47122 to \
  -3.25352, 6.47122 to \
  -3.25352, 13.1907 front fs empty border lc rgb '#549f' lw 0.1
set object 670 polygon from \
  -3.18992, 13.2106 to \
  -0.03, 13.2106 to \
  -0.03, 6.48105 to \
  -3.18992, 6.48105 to \
  -3.18992, 13.2106 front fs empty border lc rgb '#549f' lw 0.1
set object 671 polygon from \
  -3.12734, 13.2304 to \
  -0.03, 13.2304 to \
  -0.03, 6.49089 to \
  -3.12734, 6.49089 to \
  -3.12734, 13.2304 front fs empty border lc rgb '#549f' lw 0.1
set object 672 polygon from \
  -3.06521, 13.2502 to \
  -0.03, 13.2502 to \
  -0.03, 6.50072 to \
  -3.06521, 6.50072 to \
  -3.06521, 13.2502 front fs empty border lc rgb '#549f' lw 0.1
set object 673 polygon from \
  -3.00242, 13.2701 to \
  -0.03, 13.2701 to \
  -0.03, 6.51056 to \
  -3.00242, 6.51056 to \
  -3.00242, 13.2701 front fs empty border lc rgb '#549f' lw 0.1
set object 674 polygon from \
  -2.93901, 13.2899 to \
  -0.03, 13.2899 to \
  -0.03, 6.5204 to \
  -2.93901, 6.5204 to \
  -2.93901, 13.2899 front fs empty border lc rgb '#549f' lw 0.1
set object 675 polygon from \
  -2.87498, 13.3098 to \
  -0.03, 13.3098 to \
  -0.03, 6.53024 to \
  -2.87498, 6.53024 to \
  -2.87498, 13.3098 front fs empty border lc rgb '#549f' lw 0.1
set object 676 polygon from \
  -2.81036, 13.3296 to \
  -0.03, 13.3296 to \
  -0.03, 6.54008 to \
  -2.81036, 6.54008 to \
  -2.81036, 13.3296 front fs empty border lc rgb '#549f' lw 0.1
set object 677 polygon from \
  -2.74518, 13.3495 to \
  -0.03, 13.3495 to \
  -0.03, 6.54992 to \
  -2.74518, 6.54992 to \
  -2.74518, 13.3495 front fs empty border lc rgb '#549f' lw 0.1
set object 678 polygon from \
  -2.67945, 13.3693 to \
  -0.03, 13.3693 to \
  -0.03, 6.55976 to \
  -2.67945, 6.55976 to \
  -2.67945, 13.3693 front fs empty border lc rgb '#549f' lw 0.1
set object 679 polygon from \
  -2.6132, 13.3892 to \
  -0.03, 13.3892 to \
  -0.03, 6.56961 to \
  -2.6132, 6.56961 to \
  -2.6132, 13.3892 front fs empty border lc rgb '#549f' lw 0.1
set object 680 polygon from \
  -2.54645, 13.409 to \
  -0.03, 13.409 to \
  -0.03, 6.57945 to \
  -2.54645, 6.57945 to \
  -2.54645, 13.409 front fs empty border lc rgb '#549f' lw 0.1
set object 681 polygon from \
  -2.47922, 13.4289 to \
  -0.03, 13.4289 to \
  -0.03, 6.5893 to \
  -2.47922, 6.5893 to \
  -2.47922, 13.4289 front fs empty border lc rgb '#549f' lw 0.1
set object 682 polygon from \
  -2.41153, 13.4487 to \
  -0.03, 13.4487 to \
  -0.03, 6.59915 to \
  -2.41153, 6.59915 to \
  -2.41153, 13.4487 front fs empty border lc rgb '#549f' lw 0.1
set object 683 polygon from \
  -2.34342, 13.4686 to \
  -0.03, 13.4686 to \
  -0.03, 6.609 to \
  -2.34342, 6.609 to \
  -2.34342, 13.4686 front fs empty border lc rgb '#549f' lw 0.1
set object 684 polygon from \
  -2.2749, 13.4884 to \
  -0.03, 13.4884 to \
  -0.03, 6.61885 to \
  -2.2749, 6.61885 to \
  -2.2749, 13.4884 front fs empty border lc rgb '#549f' lw 0.1
set object 685 polygon from \
  -2.20599, 13.5083 to \
  -0.03, 13.5083 to \
  -0.03, 6.6287 to \
  -2.20599, 6.6287 to \
  -2.20599, 13.5083 front fs empty border lc rgb '#549f' lw 0.1
set object 686 polygon from \
  -2.13672, 13.5281 to \
  -0.03, 13.5281 to \
  -0.03, 6.63855 to \
  -2.13672, 6.63855 to \
  -2.13672, 13.5281 front fs empty border lc rgb '#549f' lw 0.1
set object 687 polygon from \
  -2.06711, 13.548 to \
  -0.03, 13.548 to \
  -0.03, 6.64841 to \
  -2.06711, 6.64841 to \
  -2.06711, 13.548 front fs empty border lc rgb '#549f' lw 0.1
set object 688 polygon from \
  -1.99718, 13.5678 to \
  -0.03, 13.5678 to \
  -0.03, 6.65826 to \
  -1.99718, 6.65826 to \
  -1.99718, 13.5678 front fs empty border lc rgb '#549f' lw 0.1
set object 689 polygon from \
  -1.92697, 13.5877 to \
  -0.03, 13.5877 to \
  -0.03, 6.66812 to \
  -1.92697, 6.66812 to \
  -1.92697, 13.5877 front fs empty border lc rgb '#549f' lw 0.1
set object 690 polygon from \
  -1.8569, 13.6076 to \
  -0.03, 13.6076 to \
  -0.03, 6.67798 to \
  -1.8569, 6.67798 to \
  -1.8569, 13.6076 front fs empty border lc rgb '#549f' lw 0.1
set object 691 polygon from \
  -1.80689, 13.6274 to \
  -0.03, 13.6274 to \
  -0.03, 6.68784 to \
  -1.80689, 6.68784 to \
  -1.80689, 13.6274 front fs empty border lc rgb '#549f' lw 0.1
set object 692 polygon from \
  -1.75669, 13.6473 to \
  -0.03, 13.6473 to \
  -0.03, 6.6977 to \
  -1.75669, 6.6977 to \
  -1.75669, 13.6473 front fs empty border lc rgb '#549f' lw 0.1
set object 693 polygon from \
  -1.70636, 13.6672 to \
  -0.03, 13.6672 to \
  -0.03, 6.70756 to \
  -1.70636, 6.70756 to \
  -1.70636, 13.6672 front fs empty border lc rgb '#549f' lw 0.1
set object 694 polygon from \
  -1.65591, 13.687 to \
  -0.03, 13.687 to \
  -0.03, 6.71742 to \
  -1.65591, 6.71742 to \
  -1.65591, 13.687 front fs empty border lc rgb '#549f' lw 0.1
set object 695 polygon from \
  -1.60538, 13.7069 to \
  -0.03, 13.7069 to \
  -0.03, 6.72729 to \
  -1.60538, 6.72729 to \
  -1.60538, 13.7069 front fs empty border lc rgb '#549f' lw 0.1
set object 696 polygon from \
  -1.5548, 13.7268 to \
  -0.03, 13.7268 to \
  -0.03, 6.73715 to \
  -1.5548, 6.73715 to \
  -1.5548, 13.7268 front fs empty border lc rgb '#549f' lw 0.1
set object 697 polygon from \
  -1.55791, 13.7466 to \
  -0.03, 13.7466 to \
  -0.03, 6.74702 to \
  -1.55791, 6.74702 to \
  -1.55791, 13.7466 front fs empty border lc rgb '#549f' lw 0.1
set object 698 polygon from \
  -1.57593, 13.7665 to \
  -0.03, 13.7665 to \
  -0.03, 6.75689 to \
  -1.57593, 6.75689 to \
  -1.57593, 13.7665 front fs empty border lc rgb '#549f' lw 0.1
set object 699 polygon from \
  -1.63763, 13.7864 to \
  -0.03, 13.7864 to \
  -0.03, 6.76676 to \
  -1.63763, 6.76676 to \
  -1.63763, 13.7864 front fs empty border lc rgb '#549f' lw 0.1
set object 700 polygon from \
  -1.70283, 13.8062 to \
  -0.03, 13.8062 to \
  -0.03, 6.77663 to \
  -1.70283, 6.77663 to \
  -1.70283, 13.8062 front fs empty border lc rgb '#549f' lw 0.1
set object 701 polygon from \
  -1.7679, 13.8261 to \
  -0.03, 13.8261 to \
  -0.03, 6.7865 to \
  -1.7679, 6.7865 to \
  -1.7679, 13.8261 front fs empty border lc rgb '#549f' lw 0.1
set object 702 polygon from \
  -1.83281, 13.846 to \
  -0.03, 13.846 to \
  -0.03, 6.79637 to \
  -1.83281, 6.79637 to \
  -1.83281, 13.846 front fs empty border lc rgb '#549f' lw 0.1
set object 703 polygon from \
  -1.89753, 13.8659 to \
  -0.03, 13.8659 to \
  -0.03, 6.80625 to \
  -1.89753, 6.80625 to \
  -1.89753, 13.8659 front fs empty border lc rgb '#549f' lw 0.1
set object 704 polygon from \
  -1.96203, 13.8858 to \
  -0.03, 13.8858 to \
  -0.03, 6.81612 to \
  -1.96203, 6.81612 to \
  -1.96203, 13.8858 front fs empty border lc rgb '#549f' lw 0.1
set object 705 polygon from \
  -2.0263, 13.9056 to \
  -0.03, 13.9056 to \
  -0.03, 6.826 to \
  -2.0263, 6.826 to \
  -2.0263, 13.9056 front fs empty border lc rgb '#549f' lw 0.1
set object 706 polygon from \
  -2.09031, 13.9255 to \
  -0.03, 13.9255 to \
  -0.03, 6.83588 to \
  -2.09031, 6.83588 to \
  -2.09031, 13.9255 front fs empty border lc rgb '#549f' lw 0.1
set object 707 polygon from \
  -2.15403, 13.9454 to \
  -0.03, 13.9454 to \
  -0.03, 6.84576 to \
  -2.15403, 6.84576 to \
  -2.15403, 13.9454 front fs empty border lc rgb '#549f' lw 0.1
set object 708 polygon from \
  -2.21745, 13.9653 to \
  -0.03, 13.9653 to \
  -0.03, 6.85564 to \
  -2.21745, 6.85564 to \
  -2.21745, 13.9653 front fs empty border lc rgb '#549f' lw 0.1
set object 709 polygon from \
  -2.28054, 13.9852 to \
  -0.03, 13.9852 to \
  -0.03, 6.86552 to \
  -2.28054, 6.86552 to \
  -2.28054, 13.9852 front fs empty border lc rgb '#549f' lw 0.1
set object 710 polygon from \
  -2.34327, 14.0051 to \
  -0.03, 14.0051 to \
  -0.03, 6.8754 to \
  -2.34327, 6.8754 to \
  -2.34327, 14.0051 front fs empty border lc rgb '#549f' lw 0.1
set object 711 polygon from \
  -2.40563, 14.025 to \
  -0.03, 14.025 to \
  -0.03, 6.88529 to \
  -2.40563, 6.88529 to \
  -2.40563, 14.025 front fs empty border lc rgb '#549f' lw 0.1
set object 712 polygon from \
  -2.46758, 14.0448 to \
  -0.03, 14.0448 to \
  -0.03, 6.89517 to \
  -2.46758, 6.89517 to \
  -2.46758, 14.0448 front fs empty border lc rgb '#549f' lw 0.1
set object 713 polygon from \
  -2.52911, 14.0647 to \
  -0.03, 14.0647 to \
  -0.03, 6.90506 to \
  -2.52911, 6.90506 to \
  -2.52911, 14.0647 front fs empty border lc rgb '#549f' lw 0.1
set object 714 polygon from \
  -2.59019, 14.0846 to \
  -0.03, 14.0846 to \
  -0.03, 6.91495 to \
  -2.59019, 6.91495 to \
  -2.59019, 14.0846 front fs empty border lc rgb '#549f' lw 0.1
set object 715 polygon from \
  -2.65081, 14.1045 to \
  -0.03, 14.1045 to \
  -0.03, 6.92484 to \
  -2.65081, 6.92484 to \
  -2.65081, 14.1045 front fs empty border lc rgb '#549f' lw 0.1
set object 716 polygon from \
  -2.71093, 14.1244 to \
  -0.03, 14.1244 to \
  -0.03, 6.93473 to \
  -2.71093, 6.93473 to \
  -2.71093, 14.1244 front fs empty border lc rgb '#549f' lw 0.1
set object 717 polygon from \
  -2.77054, 14.1443 to \
  -0.03, 14.1443 to \
  -0.03, 6.94462 to \
  -2.77054, 6.94462 to \
  -2.77054, 14.1443 front fs empty border lc rgb '#549f' lw 0.1
set object 718 polygon from \
  -2.82961, 14.1642 to \
  -0.03, 14.1642 to \
  -0.03, 6.95451 to \
  -2.82961, 6.95451 to \
  -2.82961, 14.1642 front fs empty border lc rgb '#549f' lw 0.1
set object 719 polygon from \
  -2.88813, 14.1841 to \
  -0.03, 14.1841 to \
  -0.03, 6.96441 to \
  -2.88813, 6.96441 to \
  -2.88813, 14.1841 front fs empty border lc rgb '#549f' lw 0.1
set object 720 polygon from \
  -2.94607, 14.204 to \
  -0.03, 14.204 to \
  -0.03, 6.9743 to \
  -2.94607, 6.9743 to \
  -2.94607, 14.204 front fs empty border lc rgb '#549f' lw 0.1
set object 721 polygon from \
  -3.00342, 14.2239 to \
  -0.03, 14.2239 to \
  -0.03, 6.9842 to \
  -3.00342, 6.9842 to \
  -3.00342, 14.2239 front fs empty border lc rgb '#549f' lw 0.1
set object 722 polygon from \
  -3.06014, 14.2438 to \
  -0.03, 14.2438 to \
  -0.03, 6.9941 to \
  -3.06014, 6.9941 to \
  -3.06014, 14.2438 front fs empty border lc rgb '#549f' lw 0.1
set object 723 polygon from \
  -3.11622, 14.2637 to \
  -0.03, 14.2637 to \
  -0.03, 7.004 to \
  -3.11622, 7.004 to \
  -3.11622, 14.2637 front fs empty border lc rgb '#549f' lw 0.1
set object 724 polygon from \
  -3.17164, 14.2836 to \
  -0.03, 14.2836 to \
  -0.03, 7.0139 to \
  -3.17164, 7.0139 to \
  -3.17164, 14.2836 front fs empty border lc rgb '#549f' lw 0.1
set object 725 polygon from \
  -3.22639, 14.3035 to \
  -0.03, 14.3035 to \
  -0.03, 7.0238 to \
  -3.22639, 7.0238 to \
  -3.22639, 14.3035 front fs empty border lc rgb '#549f' lw 0.1
set object 726 polygon from \
  -3.28043, 14.3234 to \
  -0.03, 14.3234 to \
  -0.03, 7.0337 to \
  -3.28043, 7.0337 to \
  -3.28043, 14.3234 front fs empty border lc rgb '#549f' lw 0.1
set object 727 polygon from \
  -3.33375, 14.3433 to \
  -0.03, 14.3433 to \
  -0.03, 7.04361 to \
  -3.33375, 7.04361 to \
  -3.33375, 14.3433 front fs empty border lc rgb '#549f' lw 0.1
set object 728 polygon from \
  -3.38634, 14.3632 to \
  -0.03, 14.3632 to \
  -0.03, 7.05351 to \
  -3.38634, 7.05351 to \
  -3.38634, 14.3632 front fs empty border lc rgb '#549f' lw 0.1
set object 729 polygon from \
  -3.43818, 14.3832 to \
  -0.03, 14.3832 to \
  -0.03, 7.06342 to \
  -3.43818, 7.06342 to \
  -3.43818, 14.3832 front fs empty border lc rgb '#549f' lw 0.1
set object 730 polygon from \
  -3.48924, 14.4031 to \
  -0.03, 14.4031 to \
  -0.03, 7.07333 to \
  -3.48924, 7.07333 to \
  -3.48924, 14.4031 front fs empty border lc rgb '#549f' lw 0.1
set object 731 polygon from \
  -3.5395, 14.423 to \
  -0.03, 14.423 to \
  -0.03, 7.08324 to \
  -3.5395, 7.08324 to \
  -3.5395, 14.423 front fs empty border lc rgb '#549f' lw 0.1
set object 732 polygon from \
  -3.58896, 14.4429 to \
  -0.03, 14.4429 to \
  -0.03, 7.09315 to \
  -3.58896, 7.09315 to \
  -3.58896, 14.4429 front fs empty border lc rgb '#549f' lw 0.1
set object 733 polygon from \
  -3.6376, 14.4628 to \
  -0.03, 14.4628 to \
  -0.03, 7.10306 to \
  -3.6376, 7.10306 to \
  -3.6376, 14.4628 front fs empty border lc rgb '#549f' lw 0.1
set object 734 polygon from \
  -3.68539, 14.4827 to \
  -0.03, 14.4827 to \
  -0.03, 7.11297 to \
  -3.68539, 7.11297 to \
  -3.68539, 14.4827 front fs empty border lc rgb '#549f' lw 0.1
set object 735 polygon from \
  -3.73233, 14.5026 to \
  -0.03, 14.5026 to \
  -0.03, 7.12289 to \
  -3.73233, 7.12289 to \
  -3.73233, 14.5026 front fs empty border lc rgb '#549f' lw 0.1
set object 736 polygon from \
  -3.77839, 14.5226 to \
  -0.03, 14.5226 to \
  -0.03, 7.1328 to \
  -3.77839, 7.1328 to \
  -3.77839, 14.5226 front fs empty border lc rgb '#549f' lw 0.1
set object 737 polygon from \
  -3.82356, 14.5425 to \
  -0.03, 14.5425 to \
  -0.03, 7.14272 to \
  -3.82356, 7.14272 to \
  -3.82356, 14.5425 front fs empty border lc rgb '#549f' lw 0.1
set object 738 polygon from \
  -3.86783, 14.5624 to \
  -0.03, 14.5624 to \
  -0.03, 7.15264 to \
  -3.86783, 7.15264 to \
  -3.86783, 14.5624 front fs empty border lc rgb '#549f' lw 0.1
set object 739 polygon from \
  -3.91119, 14.5823 to \
  -0.03, 14.5823 to \
  -0.03, 7.16256 to \
  -3.91119, 7.16256 to \
  -3.91119, 14.5823 front fs empty border lc rgb '#549f' lw 0.1
set object 740 polygon from \
  -3.95361, 14.6022 to \
  -0.03, 14.6022 to \
  -0.03, 7.17248 to \
  -3.95361, 7.17248 to \
  -3.95361, 14.6022 front fs empty border lc rgb '#549f' lw 0.1
set object 741 polygon from \
  -3.99509, 14.6222 to \
  -0.03, 14.6222 to \
  -0.03, 7.1824 to \
  -3.99509, 7.1824 to \
  -3.99509, 14.6222 front fs empty border lc rgb '#549f' lw 0.1
set object 742 polygon from \
  -4.03561, 14.6421 to \
  -0.03, 14.6421 to \
  -0.03, 7.19232 to \
  -4.03561, 7.19232 to \
  -4.03561, 14.6421 front fs empty border lc rgb '#549f' lw 0.1
set object 743 polygon from \
  -4.07515, 14.662 to \
  -0.03, 14.662 to \
  -0.03, 7.20225 to \
  -4.07515, 7.20225 to \
  -4.07515, 14.662 front fs empty border lc rgb '#549f' lw 0.1
set object 744 polygon from \
  -4.11372, 14.682 to \
  -0.03, 14.682 to \
  -0.03, 7.21217 to \
  -4.11372, 7.21217 to \
  -4.11372, 14.682 front fs empty border lc rgb '#549f' lw 0.1
set object 745 polygon from \
  -4.15129, 14.7019 to \
  -0.03, 14.7019 to \
  -0.03, 7.2221 to \
  -4.15129, 7.2221 to \
  -4.15129, 14.7019 front fs empty border lc rgb '#549f' lw 0.1
set object 746 polygon from \
  -4.18786, 14.7218 to \
  -0.03, 14.7218 to \
  -0.03, 7.23203 to \
  -4.18786, 7.23203 to \
  -4.18786, 14.7218 front fs empty border lc rgb '#549f' lw 0.1
set object 747 polygon from \
  -4.22341, 14.7418 to \
  -0.03, 14.7418 to \
  -0.03, 7.24196 to \
  -4.22341, 7.24196 to \
  -4.22341, 14.7418 front fs empty border lc rgb '#549f' lw 0.1
set object 748 polygon from \
  -4.25794, 14.7617 to \
  -0.03, 14.7617 to \
  -0.03, 7.25189 to \
  -4.25794, 7.25189 to \
  -4.25794, 14.7617 front fs empty border lc rgb '#549f' lw 0.1
set object 749 polygon from \
  -4.29143, 14.7816 to \
  -0.03, 14.7816 to \
  -0.03, 7.26182 to \
  -4.29143, 7.26182 to \
  -4.29143, 14.7816 front fs empty border lc rgb '#549f' lw 0.1
set object 750 polygon from \
  -4.32388, 14.8016 to \
  -0.03, 14.8016 to \
  -0.03, 7.27175 to \
  -4.32388, 7.27175 to \
  -4.32388, 14.8016 front fs empty border lc rgb '#549f' lw 0.1
set object 751 polygon from \
  -4.35527, 14.8215 to \
  -0.03, 14.8215 to \
  -0.03, 7.28169 to \
  -4.35527, 7.28169 to \
  -4.35527, 14.8215 front fs empty border lc rgb '#549f' lw 0.1
set object 752 polygon from \
  -4.38561, 14.8414 to \
  -0.03, 14.8414 to \
  -0.03, 7.29162 to \
  -4.38561, 7.29162 to \
  -4.38561, 14.8414 front fs empty border lc rgb '#549f' lw 0.1
set object 753 polygon from \
  -4.41487, 14.8614 to \
  -0.03, 14.8614 to \
  -0.03, 7.30156 to \
  -4.41487, 7.30156 to \
  -4.41487, 14.8614 front fs empty border lc rgb '#549f' lw 0.1
set object 754 polygon from \
  -4.44306, 14.8813 to \
  -0.03, 14.8813 to \
  -0.03, 7.3115 to \
  -4.44306, 7.3115 to \
  -4.44306, 14.8813 front fs empty border lc rgb '#549f' lw 0.1
set object 755 polygon from \
  -4.47017, 14.9013 to \
  -0.03, 14.9013 to \
  -0.03, 7.32144 to \
  -4.47017, 7.32144 to \
  -4.47017, 14.9013 front fs empty border lc rgb '#549f' lw 0.1
set object 756 polygon from \
  -4.49619, 14.9212 to \
  -0.03, 14.9212 to \
  -0.03, 7.33138 to \
  -4.49619, 7.33138 to \
  -4.49619, 14.9212 front fs empty border lc rgb '#549f' lw 0.1
set object 757 polygon from \
  -4.52111, 14.9412 to \
  -0.03, 14.9412 to \
  -0.03, 7.34132 to \
  -4.52111, 7.34132 to \
  -4.52111, 14.9412 front fs empty border lc rgb '#549f' lw 0.1
set object 758 polygon from \
  -4.54494, 14.9611 to \
  -0.03, 14.9611 to \
  -0.03, 7.35126 to \
  -4.54494, 7.35126 to \
  -4.54494, 14.9611 front fs empty border lc rgb '#549f' lw 0.1
set object 759 polygon from \
  -4.56766, 14.9811 to \
  -0.03, 14.9811 to \
  -0.03, 7.36121 to \
  -4.56766, 7.36121 to \
  -4.56766, 14.9811 front fs empty border lc rgb '#549f' lw 0.1
set object 760 polygon from \
  -4.58928, 15.001 to \
  -0.03, 15.001 to \
  -0.03, 7.37115 to \
  -4.58928, 7.37115 to \
  -4.58928, 15.001 front fs empty border lc rgb '#549f' lw 0.1
set object 761 polygon from \
  -4.60979, 15.021 to \
  -0.03, 15.021 to \
  -0.03, 7.3811 to \
  -4.60979, 7.3811 to \
  -4.60979, 15.021 front fs empty border lc rgb '#549f' lw 0.1
set object 762 polygon from \
  -4.62918, 15.0409 to \
  -0.03, 15.0409 to \
  -0.03, 7.39105 to \
  -4.62918, 7.39105 to \
  -4.62918, 15.0409 front fs empty border lc rgb '#549f' lw 0.1
set object 763 polygon from \
  -4.64746, 15.0609 to \
  -0.03, 15.0609 to \
  -0.03, 7.401 to \
  -4.64746, 7.401 to \
  -4.64746, 15.0609 front fs empty border lc rgb '#549f' lw 0.1
set object 764 polygon from \
  -4.66461, 15.0808 to \
  -0.03, 15.0808 to \
  -0.03, 7.41095 to \
  -4.66461, 7.41095 to \
  -4.66461, 15.0808 front fs empty border lc rgb '#549f' lw 0.1
set object 765 polygon from \
  -4.68065, 15.1008 to \
  -0.03, 15.1008 to \
  -0.03, 7.4209 to \
  -4.68065, 7.4209 to \
  -4.68065, 15.1008 front fs empty border lc rgb '#549f' lw 0.1
set object 766 polygon from \
  -4.69557, 15.1207 to \
  -0.03, 15.1207 to \
  -0.03, 7.43085 to \
  -4.69557, 7.43085 to \
  -4.69557, 15.1207 front fs empty border lc rgb '#549f' lw 0.1
set object 767 polygon from \
  -4.70937, 15.1407 to \
  -0.03, 15.1407 to \
  -0.03, 7.44081 to \
  -4.70937, 7.44081 to \
  -4.70937, 15.1407 front fs empty border lc rgb '#549f' lw 0.1
set object 768 polygon from \
  -4.72205, 15.1606 to \
  -0.03, 15.1606 to \
  -0.03, 7.45076 to \
  -4.72205, 7.45076 to \
  -4.72205, 15.1606 front fs empty border lc rgb '#549f' lw 0.1
set object 769 polygon from \
  -4.73361, 15.1806 to \
  -0.03, 15.1806 to \
  -0.03, 7.46072 to \
  -4.73361, 7.46072 to \
  -4.73361, 15.1806 front fs empty border lc rgb '#549f' lw 0.1
set object 770 polygon from \
  -4.74406, 15.2006 to \
  -0.03, 15.2006 to \
  -0.03, 7.47068 to \
  -4.74406, 7.47068 to \
  -4.74406, 15.2006 front fs empty border lc rgb '#549f' lw 0.1
set object 771 polygon from \
  -4.75338, 15.2205 to \
  -0.03, 15.2205 to \
  -0.03, 7.48064 to \
  -4.75338, 7.48064 to \
  -4.75338, 15.2205 front fs empty border lc rgb '#549f' lw 0.1
set object 772 polygon from \
  -4.76159, 15.2405 to \
  -0.03, 15.2405 to \
  -0.03, 7.4906 to \
  -4.76159, 7.4906 to \
  -4.76159, 15.2405 front fs empty border lc rgb '#549f' lw 0.1
set object 773 polygon from \
  -4.76869, 15.2605 to \
  -0.03, 15.2605 to \
  -0.03, 7.50056 to \
  -4.76869, 7.50056 to \
  -4.76869, 15.2605 front fs empty border lc rgb '#549f' lw 0.1
set object 774 polygon from \
  -4.77468, 15.2804 to \
  -0.03, 15.2804 to \
  -0.03, 7.51052 to \
  -4.77468, 7.51052 to \
  -4.77468, 15.2804 front fs empty border lc rgb '#549f' lw 0.1
set object 775 polygon from \
  -4.77957, 15.3004 to \
  -0.03, 15.3004 to \
  -0.03, 7.52049 to \
  -4.77957, 7.52049 to \
  -4.77957, 15.3004 front fs empty border lc rgb '#549f' lw 0.1
set object 776 polygon from \
  -4.78549, 15.3204 to \
  -0.03, 15.3204 to \
  -0.03, 7.53045 to \
  -4.78549, 7.53045 to \
  -4.78549, 15.3204 front fs empty border lc rgb '#549f' lw 0.1
set object 777 polygon from \
  -4.79313, 15.3403 to \
  -0.03, 15.3403 to \
  -0.03, 7.54042 to \
  -4.79313, 7.54042 to \
  -4.79313, 15.3403 front fs empty border lc rgb '#549f' lw 0.1
set object 778 polygon from \
  -4.7998, 15.3603 to \
  -0.03, 15.3603 to \
  -0.03, 7.55039 to \
  -4.7998, 7.55039 to \
  -4.7998, 15.3603 front fs empty border lc rgb '#549f' lw 0.1
set object 779 polygon from \
  -4.80552, 15.3803 to \
  -0.03, 15.3803 to \
  -0.03, 7.56036 to \
  -4.80552, 7.56036 to \
  -4.80552, 15.3803 front fs empty border lc rgb '#549f' lw 0.1
set object 780 polygon from \
  -4.81029, 15.4002 to \
  -0.03, 15.4002 to \
  -0.03, 7.57033 to \
  -4.81029, 7.57033 to \
  -4.81029, 15.4002 front fs empty border lc rgb '#549f' lw 0.1
set object 781 polygon from \
  -4.81411, 15.4202 to \
  -0.03, 15.4202 to \
  -0.03, 7.5803 to \
  -4.81411, 7.5803 to \
  -4.81411, 15.4202 front fs empty border lc rgb '#549f' lw 0.1
set object 782 polygon from \
  -4.81699, 15.4402 to \
  -0.03, 15.4402 to \
  -0.03, 7.59027 to \
  -4.81699, 7.59027 to \
  -4.81699, 15.4402 front fs empty border lc rgb '#549f' lw 0.1
set object 783 polygon from \
  -4.81893, 15.4602 to \
  -0.03, 15.4602 to \
  -0.03, 7.60025 to \
  -4.81893, 7.60025 to \
  -4.81893, 15.4602 front fs empty border lc rgb '#549f' lw 0.1
set object 784 polygon from \
  -4.81996, 15.4802 to \
  -0.03, 15.4802 to \
  -0.03, 7.61022 to \
  -4.81996, 7.61022 to \
  -4.81996, 15.4802 front fs empty border lc rgb '#549f' lw 0.1
set object 785 polygon from \
  -4.82007, 15.5001 to \
  -0.03, 15.5001 to \
  -0.03, 7.6202 to \
  -4.82007, 7.6202 to \
  -4.82007, 15.5001 front fs empty border lc rgb '#549f' lw 0.1
set object 786 polygon from \
  -4.82006, 15.5201 to \
  -0.03, 15.5201 to \
  -0.03, 7.63018 to \
  -4.82006, 7.63018 to \
  -4.82006, 15.5201 front fs empty border lc rgb '#549f' lw 0.1
set object 787 polygon from \
  -4.81926, 15.5401 to \
  -0.03, 15.5401 to \
  -0.03, 7.64016 to \
  -4.81926, 7.64016 to \
  -4.81926, 15.5401 front fs empty border lc rgb '#549f' lw 0.1
set object 788 polygon from \
  -4.81756, 15.5601 to \
  -0.03, 15.5601 to \
  -0.03, 7.65014 to \
  -4.81756, 7.65014 to \
  -4.81756, 15.5601 front fs empty border lc rgb '#549f' lw 0.1
set object 789 polygon from \
  -4.81497, 15.5801 to \
  -0.03, 15.5801 to \
  -0.03, 7.66012 to \
  -4.81497, 7.66012 to \
  -4.81497, 15.5801 front fs empty border lc rgb '#549f' lw 0.1
set object 790 polygon from \
  -4.8115, 15.6001 to \
  -0.03, 15.6001 to \
  -0.03, 7.6701 to \
  -4.8115, 7.6701 to \
  -4.8115, 15.6001 front fs empty border lc rgb '#549f' lw 0.1
set object 791 polygon from \
  -4.80715, 15.6201 to \
  -0.03, 15.6201 to \
  -0.03, 7.68009 to \
  -4.80715, 7.68009 to \
  -4.80715, 15.6201 front fs empty border lc rgb '#549f' lw 0.1
set object 792 polygon from \
  -4.80195, 15.64 to \
  -0.03, 15.64 to \
  -0.03, 7.69007 to \
  -4.80195, 7.69007 to \
  -4.80195, 15.64 front fs empty border lc rgb '#549f' lw 0.1
set object 793 polygon from \
  -4.79589, 15.66 to \
  -0.03, 15.66 to \
  -0.03, 7.70006 to \
  -4.79589, 7.70006 to \
  -4.79589, 15.66 front fs empty border lc rgb '#549f' lw 0.1
set object 794 polygon from \
  -4.78899, 15.68 to \
  -0.03, 15.68 to \
  -0.03, 7.71005 to \
  -4.78899, 7.71005 to \
  -4.78899, 15.68 front fs empty border lc rgb '#549f' lw 0.1
set object 795 polygon from \
  -4.78126, 15.7 to \
  -0.03, 15.7 to \
  -0.03, 7.72004 to \
  -4.78126, 7.72004 to \
  -4.78126, 15.7 front fs empty border lc rgb '#549f' lw 0.1
set object 796 polygon from \
  -4.77271, 15.72 to \
  -0.03, 15.72 to \
  -0.03, 7.73003 to \
  -4.77271, 7.73003 to \
  -4.77271, 15.72 front fs empty border lc rgb '#549f' lw 0.1
set object 797 polygon from \
  -4.76336, 15.74 to \
  -0.03, 15.74 to \
  -0.03, 7.74002 to \
  -4.76336, 7.74002 to \
  -4.76336, 15.74 front fs empty border lc rgb '#549f' lw 0.1
set object 798 polygon from \
  -4.75321, 15.76 to \
  -0.03, 15.76 to \
  -0.03, 7.75001 to \
  -4.75321, 7.75001 to \
  -4.75321, 15.76 front fs empty border lc rgb '#549f' lw 0.1
set object 799 polygon from \
  -4.74227, 15.78 to \
  -0.03, 15.78 to \
  -0.03, 7.76001 to \
  -4.74227, 7.76001 to \
  -4.74227, 15.78 front fs empty border lc rgb '#549f' lw 0.1
set object 800 polygon from \
  -4.73057, 15.8 to \
  -0.03, 15.8 to \
  -0.03, 7.77 to \
  -4.73057, 7.77 to \
  -4.73057, 15.8 front fs empty border lc rgb '#549f' lw 0.1
set object 801 polygon from \
  -4.7181, 15.82 to \
  -0.03, 15.82 to \
  -0.03, 7.78 to \
  -4.7181, 7.78 to \
  -4.7181, 15.82 front fs empty border lc rgb '#549f' lw 0.1
set object 802 polygon from \
  -4.70489, 15.84 to \
  -0.03, 15.84 to \
  -0.03, 7.79 to \
  -4.70489, 7.79 to \
  -4.70489, 15.84 front fs empty border lc rgb '#549f' lw 0.1
set object 803 polygon from \
  -4.69094, 15.86 to \
  -0.03, 15.86 to \
  -0.03, 7.8 to \
  -4.69094, 7.8 to \
  -4.69094, 15.86 front fs empty border lc rgb '#549f' lw 0.1
set object 804 polygon from \
  -4.67628, 15.88 to \
  -0.03, 15.88 to \
  -0.03, 7.81 to \
  -4.67628, 7.81 to \
  -4.67628, 15.88 front fs empty border lc rgb '#549f' lw 0.1
set object 805 polygon from \
  -4.6609, 15.9 to \
  -0.03, 15.9 to \
  -0.03, 7.82 to \
  -4.6609, 7.82 to \
  -4.6609, 15.9 front fs empty border lc rgb '#549f' lw 0.1
set object 806 polygon from \
  -4.64484, 15.92 to \
  -0.03, 15.92 to \
  -0.03, 7.83 to \
  -4.64484, 7.83 to \
  -4.64484, 15.92 front fs empty border lc rgb '#549f' lw 0.1
set object 807 polygon from \
  -4.62809, 15.94 to \
  -0.03, 15.94 to \
  -0.03, 7.84001 to \
  -4.62809, 7.84001 to \
  -4.62809, 15.94 front fs empty border lc rgb '#549f' lw 0.1
set object 808 polygon from \
  -4.61067, 15.96 to \
  -0.03, 15.96 to \
  -0.03, 7.85001 to \
  -4.61067, 7.85001 to \
  -4.61067, 15.96 front fs empty border lc rgb '#549f' lw 0.1
set object 809 polygon from \
  -4.59444, 15.9801 to \
  -0.03, 15.9801 to \
  -0.03, 7.86002 to \
  -4.59444, 7.86002 to \
  -4.59444, 15.9801 front fs empty border lc rgb '#549f' lw 0.1
set object 810 polygon from \
  -4.62153, 16.0001 to \
  -0.03, 16.0001 to \
  -0.03, 7.87003 to \
  -4.62153, 7.87003 to \
  -4.62153, 16.0001 front fs empty border lc rgb '#549f' lw 0.1
set object 811 polygon from \
  -4.64809, 16.0201 to \
  -0.03, 16.0201 to \
  -0.03, 7.88004 to \
  -4.64809, 7.88004 to \
  -4.64809, 16.0201 front fs empty border lc rgb '#549f' lw 0.1
set object 812 polygon from \
  -4.6741, 16.0401 to \
  -0.03, 16.0401 to \
  -0.03, 7.89005 to \
  -4.6741, 7.89005 to \
  -4.6741, 16.0401 front fs empty border lc rgb '#549f' lw 0.1
set object 813 polygon from \
  -4.69954, 16.0601 to \
  -0.03, 16.0601 to \
  -0.03, 7.90006 to \
  -4.69954, 7.90006 to \
  -4.69954, 16.0601 front fs empty border lc rgb '#549f' lw 0.1
set object 814 polygon from \
  -4.72439, 16.0801 to \
  -0.03, 16.0801 to \
  -0.03, 7.91007 to \
  -4.72439, 7.91007 to \
  -4.72439, 16.0801 front fs empty border lc rgb '#549f' lw 0.1
set object 815 polygon from \
  -4.74863, 16.1001 to \
  -0.03, 16.1001 to \
  -0.03, 7.92009 to \
  -4.74863, 7.92009 to \
  -4.74863, 16.1001 front fs empty border lc rgb '#549f' lw 0.1
set object 816 polygon from \
  -4.77225, 16.1202 to \
  -0.03, 16.1202 to \
  -0.03, 7.9301 to \
  -4.77225, 7.9301 to \
  -4.77225, 16.1202 front fs empty border lc rgb '#549f' lw 0.1
set object 817 polygon from \
  -4.79522, 16.1402 to \
  -0.03, 16.1402 to \
  -0.03, 7.94012 to \
  -4.79522, 7.94012 to \
  -4.79522, 16.1402 front fs empty border lc rgb '#549f' lw 0.1
set object 818 polygon from \
  -4.81754, 16.1602 to \
  -0.03, 16.1602 to \
  -0.03, 7.95014 to \
  -4.81754, 7.95014 to \
  -4.81754, 16.1602 front fs empty border lc rgb '#549f' lw 0.1
set object 819 polygon from \
  -4.83918, 16.1802 to \
  -0.03, 16.1802 to \
  -0.03, 7.96016 to \
  -4.83918, 7.96016 to \
  -4.83918, 16.1802 front fs empty border lc rgb '#549f' lw 0.1
set object 820 polygon from \
  -4.86014, 16.2002 to \
  -0.03, 16.2002 to \
  -0.03, 7.97018 to \
  -4.86014, 7.97018 to \
  -4.86014, 16.2002 front fs empty border lc rgb '#549f' lw 0.1
set object 821 polygon from \
  -4.88038, 16.2203 to \
  -0.03, 16.2203 to \
  -0.03, 7.9802 to \
  -4.88038, 7.9802 to \
  -4.88038, 16.2203 front fs empty border lc rgb '#549f' lw 0.1
set object 822 polygon from \
  -4.8999, 16.2403 to \
  -0.03, 16.2403 to \
  -0.03, 7.99022 to \
  -4.8999, 7.99022 to \
  -4.8999, 16.2403 front fs empty border lc rgb '#549f' lw 0.1
set object 823 polygon from \
  -4.91869, 16.2603 to \
  -0.03, 16.2603 to \
  -0.03, 8.00025 to \
  -4.91869, 8.00025 to \
  -4.91869, 16.2603 front fs empty border lc rgb '#549f' lw 0.1
set object 824 polygon from \
  -4.93672, 16.2804 to \
  -0.03, 16.2804 to \
  -0.03, 8.01027 to \
  -4.93672, 8.01027 to \
  -4.93672, 16.2804 front fs empty border lc rgb '#549f' lw 0.1
set object 825 polygon from \
  -4.95397, 16.3004 to \
  -0.03, 16.3004 to \
  -0.03, 8.0203 to \
  -4.95397, 8.0203 to \
  -4.95397, 16.3004 front fs empty border lc rgb '#549f' lw 0.1
set object 826 polygon from \
  -4.97045, 16.3204 to \
  -0.03, 16.3204 to \
  -0.03, 8.03033 to \
  -4.97045, 8.03033 to \
  -4.97045, 16.3204 front fs empty border lc rgb '#549f' lw 0.1
set object 827 polygon from \
  -4.98612, 16.3405 to \
  -0.03, 16.3405 to \
  -0.03, 8.04036 to \
  -4.98612, 8.04036 to \
  -4.98612, 16.3405 front fs empty border lc rgb '#549f' lw 0.1
set object 828 polygon from \
  -5.00098, 16.3605 to \
  -0.03, 16.3605 to \
  -0.03, 8.05039 to \
  -5.00098, 8.05039 to \
  -5.00098, 16.3605 front fs empty border lc rgb '#549f' lw 0.1
set object 829 polygon from \
  -5.01501, 16.3805 to \
  -0.03, 16.3805 to \
  -0.03, 8.06042 to \
  -5.01501, 8.06042 to \
  -5.01501, 16.3805 front fs empty border lc rgb '#549f' lw 0.1
set object 830 polygon from \
  -5.0282, 16.4006 to \
  -0.03, 16.4006 to \
  -0.03, 8.07045 to \
  -5.0282, 8.07045 to \
  -5.0282, 16.4006 front fs empty border lc rgb '#549f' lw 0.1
set object 831 polygon from \
  -5.04054, 16.4206 to \
  -0.03, 16.4206 to \
  -0.03, 8.08049 to \
  -5.04054, 8.08049 to \
  -5.04054, 16.4206 front fs empty border lc rgb '#549f' lw 0.1
set object 832 polygon from \
  -5.052, 16.4406 to \
  -0.03, 16.4406 to \
  -0.03, 8.09052 to \
  -5.052, 8.09052 to \
  -5.052, 16.4406 front fs empty border lc rgb '#549f' lw 0.1
set object 833 polygon from \
  -5.06259, 16.4607 to \
  -0.03, 16.4607 to \
  -0.03, 8.10056 to \
  -5.06259, 8.10056 to \
  -5.06259, 16.4607 front fs empty border lc rgb '#549f' lw 0.1
set object 834 polygon from \
  -5.07228, 16.4807 to \
  -0.03, 16.4807 to \
  -0.03, 8.1106 to \
  -5.07228, 8.1106 to \
  -5.07228, 16.4807 front fs empty border lc rgb '#549f' lw 0.1
set object 835 polygon from \
  -5.08106, 16.5008 to \
  -0.03, 16.5008 to \
  -0.03, 8.12064 to \
  -5.08106, 8.12064 to \
  -5.08106, 16.5008 front fs empty border lc rgb '#549f' lw 0.1
set object 836 polygon from \
  -5.08893, 16.5208 to \
  -0.03, 16.5208 to \
  -0.03, 8.13068 to \
  -5.08893, 8.13068 to \
  -5.08893, 16.5208 front fs empty border lc rgb '#549f' lw 0.1
set object 837 polygon from \
  -5.09586, 16.5409 to \
  -0.03, 16.5409 to \
  -0.03, 8.14072 to \
  -5.09586, 8.14072 to \
  -5.09586, 16.5409 front fs empty border lc rgb '#549f' lw 0.1
set object 838 polygon from \
  -5.10186, 16.5609 to \
  -0.03, 16.5609 to \
  -0.03, 8.15076 to \
  -5.10186, 8.15076 to \
  -5.10186, 16.5609 front fs empty border lc rgb '#549f' lw 0.1
set object 839 polygon from \
  -5.1069, 16.581 to \
  -0.03, 16.581 to \
  -0.03, 8.16081 to \
  -5.1069, 8.16081 to \
  -5.1069, 16.581 front fs empty border lc rgb '#549f' lw 0.1
set object 840 polygon from \
  -5.11098, 16.601 to \
  -0.03, 16.601 to \
  -0.03, 8.17085 to \
  -5.11098, 8.17085 to \
  -5.11098, 16.601 front fs empty border lc rgb '#549f' lw 0.1
set object 841 polygon from \
  -5.1141, 16.6211 to \
  -0.03, 16.6211 to \
  -0.03, 8.1809 to \
  -5.1141, 8.1809 to \
  -5.1141, 16.6211 front fs empty border lc rgb '#549f' lw 0.1
set object 842 polygon from \
  -5.11623, 16.6411 to \
  -0.03, 16.6411 to \
  -0.03, 8.19095 to \
  -5.11623, 8.19095 to \
  -5.11623, 16.6411 front fs empty border lc rgb '#549f' lw 0.1
set object 843 polygon from \
  -5.11737, 16.6612 to \
  -0.03, 16.6612 to \
  -0.03, 8.201 to \
  -5.11737, 8.201 to \
  -5.11737, 16.6612 front fs empty border lc rgb '#549f' lw 0.1
set object 844 polygon from \
  -5.11752, 16.6812 to \
  -0.03, 16.6812 to \
  -0.03, 8.21105 to \
  -5.11752, 8.21105 to \
  -5.11752, 16.6812 front fs empty border lc rgb '#549f' lw 0.1
set object 845 polygon from \
  -5.11752, 16.7013 to \
  -0.03, 16.7013 to \
  -0.03, 8.2211 to \
  -5.11752, 8.2211 to \
  -5.11752, 16.7013 front fs empty border lc rgb '#549f' lw 0.1
set object 846 polygon from \
  -5.11666, 16.7213 to \
  -0.03, 16.7213 to \
  -0.03, 8.23115 to \
  -5.11666, 8.23115 to \
  -5.11666, 16.7213 front fs empty border lc rgb '#549f' lw 0.1
set object 847 polygon from \
  -5.11478, 16.7414 to \
  -0.03, 16.7414 to \
  -0.03, 8.24121 to \
  -5.11478, 8.24121 to \
  -5.11478, 16.7414 front fs empty border lc rgb '#549f' lw 0.1
set object 848 polygon from \
  -5.11189, 16.7614 to \
  -0.03, 16.7614 to \
  -0.03, 8.25126 to \
  -5.11189, 8.25126 to \
  -5.11189, 16.7614 front fs empty border lc rgb '#549f' lw 0.1
set object 849 polygon from \
  -5.10797, 16.7815 to \
  -0.03, 16.7815 to \
  -0.03, 8.26132 to \
  -5.10797, 8.26132 to \
  -5.10797, 16.7815 front fs empty border lc rgb '#549f' lw 0.1
set object 850 polygon from \
  -5.10301, 16.8016 to \
  -0.03, 16.8016 to \
  -0.03, 8.27138 to \
  -5.10301, 8.27138 to \
  -5.10301, 16.8016 front fs empty border lc rgb '#549f' lw 0.1
set object 851 polygon from \
  -5.09702, 16.8216 to \
  -0.03, 16.8216 to \
  -0.03, 8.28144 to \
  -5.09702, 8.28144 to \
  -5.09702, 16.8216 front fs empty border lc rgb '#549f' lw 0.1
set object 852 polygon from \
  -5.08998, 16.8417 to \
  -0.03, 16.8417 to \
  -0.03, 8.2915 to \
  -5.08998, 8.2915 to \
  -5.08998, 16.8417 front fs empty border lc rgb '#549f' lw 0.1
set object 853 polygon from \
  -5.08189, 16.8618 to \
  -0.03, 16.8618 to \
  -0.03, 8.30156 to \
  -5.08189, 8.30156 to \
  -5.08189, 16.8618 front fs empty border lc rgb '#549f' lw 0.1
set object 854 polygon from \
  -5.07275, 16.8818 to \
  -0.03, 16.8818 to \
  -0.03, 8.31162 to \
  -5.07275, 8.31162 to \
  -5.07275, 16.8818 front fs empty border lc rgb '#549f' lw 0.1
set object 855 polygon from \
  -5.06256, 16.9019 to \
  -0.03, 16.9019 to \
  -0.03, 8.32169 to \
  -5.06256, 8.32169 to \
  -5.06256, 16.9019 front fs empty border lc rgb '#549f' lw 0.1
set object 856 polygon from \
  -5.0513, 16.922 to \
  -0.03, 16.922 to \
  -0.03, 8.33175 to \
  -5.0513, 8.33175 to \
  -5.0513, 16.922 front fs empty border lc rgb '#549f' lw 0.1
set object 857 polygon from \
  -5.03898, 16.942 to \
  -0.03, 16.942 to \
  -0.03, 8.34182 to \
  -5.03898, 8.34182 to \
  -5.03898, 16.942 front fs empty border lc rgb '#549f' lw 0.1
set object 858 polygon from \
  -5.0256, 16.9621 to \
  -0.03, 16.9621 to \
  -0.03, 8.35189 to \
  -5.0256, 8.35189 to \
  -5.0256, 16.9621 front fs empty border lc rgb '#549f' lw 0.1
set object 859 polygon from \
  -5.01115, 16.9822 to \
  -0.03, 16.9822 to \
  -0.03, 8.36196 to \
  -5.01115, 8.36196 to \
  -5.01115, 16.9822 front fs empty border lc rgb '#549f' lw 0.1
set object 860 polygon from \
  -4.99564, 17.0022 to \
  -0.03, 17.0022 to \
  -0.03, 8.37203 to \
  -4.99564, 8.37203 to \
  -4.99564, 17.0022 front fs empty border lc rgb '#549f' lw 0.1
set object 861 polygon from \
  -4.97906, 17.0223 to \
  -0.03, 17.0223 to \
  -0.03, 8.3821 to \
  -4.97906, 8.3821 to \
  -4.97906, 17.0223 front fs empty border lc rgb '#549f' lw 0.1
set object 862 polygon from \
  -4.96258, 17.0424 to \
  -0.03, 17.0424 to \
  -0.03, 8.39217 to \
  -4.96258, 8.39217 to \
  -4.96258, 17.0424 front fs empty border lc rgb '#549f' lw 0.1
set object 863 polygon from \
  -4.95219, 17.0625 to \
  -0.03, 17.0625 to \
  -0.03, 8.40225 to \
  -4.95219, 8.40225 to \
  -4.95219, 17.0625 front fs empty border lc rgb '#549f' lw 0.1
set object 864 polygon from \
  -4.94062, 17.0826 to \
  -0.03, 17.0826 to \
  -0.03, 8.41232 to \
  -4.94062, 8.41232 to \
  -4.94062, 17.0826 front fs empty border lc rgb '#549f' lw 0.1
set object 865 polygon from \
  -4.92788, 17.1026 to \
  -0.03, 17.1026 to \
  -0.03, 8.4224 to \
  -4.92788, 8.4224 to \
  -4.92788, 17.1026 front fs empty border lc rgb '#549f' lw 0.1
set object 866 polygon from \
  -4.91397, 17.1227 to \
  -0.03, 17.1227 to \
  -0.03, 8.43248 to \
  -4.91397, 8.43248 to \
  -4.91397, 17.1227 front fs empty border lc rgb '#549f' lw 0.1
set object 867 polygon from \
  -4.89889, 17.1428 to \
  -0.03, 17.1428 to \
  -0.03, 8.44256 to \
  -4.89889, 8.44256 to \
  -4.89889, 17.1428 front fs empty border lc rgb '#549f' lw 0.1
set object 868 polygon from \
  -4.88265, 17.1629 to \
  -0.03, 17.1629 to \
  -0.03, 8.45264 to \
  -4.88265, 8.45264 to \
  -4.88265, 17.1629 front fs empty border lc rgb '#549f' lw 0.1
set object 869 polygon from \
  -4.86525, 17.183 to \
  -0.03, 17.183 to \
  -0.03, 8.46272 to \
  -4.86525, 8.46272 to \
  -4.86525, 17.183 front fs empty border lc rgb '#549f' lw 0.1
set object 870 polygon from \
  -4.84669, 17.2031 to \
  -0.03, 17.2031 to \
  -0.03, 8.4728 to \
  -4.84669, 8.4728 to \
  -4.84669, 17.2031 front fs empty border lc rgb '#549f' lw 0.1
set object 871 polygon from \
  -4.82698, 17.2232 to \
  -0.03, 17.2232 to \
  -0.03, 8.48289 to \
  -4.82698, 8.48289 to \
  -4.82698, 17.2232 front fs empty border lc rgb '#549f' lw 0.1
set object 872 polygon from \
  -4.80613, 17.2432 to \
  -0.03, 17.2432 to \
  -0.03, 8.49297 to \
  -4.80613, 8.49297 to \
  -4.80613, 17.2432 front fs empty border lc rgb '#549f' lw 0.1
set object 873 polygon from \
  -4.78414, 17.2633 to \
  -0.03, 17.2633 to \
  -0.03, 8.50306 to \
  -4.78414, 8.50306 to \
  -4.78414, 17.2633 front fs empty border lc rgb '#549f' lw 0.1
set object 874 polygon from \
  -4.76101, 17.2834 to \
  -0.03, 17.2834 to \
  -0.03, 8.51315 to \
  -4.76101, 8.51315 to \
  -4.76101, 17.2834 front fs empty border lc rgb '#549f' lw 0.1
set object 875 polygon from \
  -4.73677, 17.3035 to \
  -0.03, 17.3035 to \
  -0.03, 8.52324 to \
  -4.73677, 8.52324 to \
  -4.73677, 17.3035 front fs empty border lc rgb '#549f' lw 0.1
set object 876 polygon from \
  -4.7114, 17.3236 to \
  -0.03, 17.3236 to \
  -0.03, 8.53333 to \
  -4.7114, 8.53333 to \
  -4.7114, 17.3236 front fs empty border lc rgb '#549f' lw 0.1
set object 877 polygon from \
  -4.68493, 17.3437 to \
  -0.03, 17.3437 to \
  -0.03, 8.54342 to \
  -4.68493, 8.54342 to \
  -4.68493, 17.3437 front fs empty border lc rgb '#549f' lw 0.1
set object 878 polygon from \
  -4.65737, 17.3638 to \
  -0.03, 17.3638 to \
  -0.03, 8.55351 to \
  -4.65737, 8.55351 to \
  -4.65737, 17.3638 front fs empty border lc rgb '#549f' lw 0.1
set object 879 polygon from \
  -4.62871, 17.3839 to \
  -0.03, 17.3839 to \
  -0.03, 8.56361 to \
  -4.62871, 8.56361 to \
  -4.62871, 17.3839 front fs empty border lc rgb '#549f' lw 0.1
set object 880 polygon from \
  -4.59897, 17.404 to \
  -0.03, 17.404 to \
  -0.03, 8.5737 to \
  -4.59897, 8.5737 to \
  -4.59897, 17.404 front fs empty border lc rgb '#549f' lw 0.1
set object 881 polygon from \
  -4.56817, 17.4241 to \
  -0.03, 17.4241 to \
  -0.03, 8.5838 to \
  -4.56817, 8.5838 to \
  -4.56817, 17.4241 front fs empty border lc rgb '#549f' lw 0.1
set object 882 polygon from \
  -4.53631, 17.4442 to \
  -0.03, 17.4442 to \
  -0.03, 8.5939 to \
  -4.53631, 8.5939 to \
  -4.53631, 17.4442 front fs empty border lc rgb '#549f' lw 0.1
set object 883 polygon from \
  -4.5034, 17.4643 to \
  -0.03, 17.4643 to \
  -0.03, 8.604 to \
  -4.5034, 8.604 to \
  -4.5034, 17.4643 front fs empty border lc rgb '#549f' lw 0.1
set object 884 polygon from \
  -4.46946, 17.4844 to \
  -0.03, 17.4844 to \
  -0.03, 8.6141 to \
  -4.46946, 8.6141 to \
  -4.46946, 17.4844 front fs empty border lc rgb '#549f' lw 0.1
set object 885 polygon from \
  -4.4345, 17.5045 to \
  -0.03, 17.5045 to \
  -0.03, 8.6242 to \
  -4.4345, 8.6242 to \
  -4.4345, 17.5045 front fs empty border lc rgb '#549f' lw 0.1
set object 886 polygon from \
  -4.39853, 17.5246 to \
  -0.03, 17.5246 to \
  -0.03, 8.6343 to \
  -4.39853, 8.6343 to \
  -4.39853, 17.5246 front fs empty border lc rgb '#549f' lw 0.1
set object 887 polygon from \
  -4.36157, 17.5447 to \
  -0.03, 17.5447 to \
  -0.03, 8.64441 to \
  -4.36157, 8.64441 to \
  -4.36157, 17.5447 front fs empty border lc rgb '#549f' lw 0.1
set object 888 polygon from \
  -4.32363, 17.5648 to \
  -0.03, 17.5648 to \
  -0.03, 8.65451 to \
  -4.32363, 8.65451 to \
  -4.32363, 17.5648 front fs empty border lc rgb '#549f' lw 0.1
set object 889 polygon from \
  -4.28473, 17.585 to \
  -0.03, 17.585 to \
  -0.03, 8.66462 to \
  -4.28473, 8.66462 to \
  -4.28473, 17.585 front fs empty border lc rgb '#549f' lw 0.1
set object 890 polygon from \
  -4.24487, 17.6051 to \
  -0.03, 17.6051 to \
  -0.03, 8.67473 to \
  -4.24487, 8.67473 to \
  -4.24487, 17.6051 front fs empty border lc rgb '#549f' lw 0.1
set object 891 polygon from \
  -4.20408, 17.6252 to \
  -0.03, 17.6252 to \
  -0.03, 8.68484 to \
  -4.20408, 8.68484 to \
  -4.20408, 17.6252 front fs empty border lc rgb '#549f' lw 0.1
set object 892 polygon from \
  -4.16238, 17.6453 to \
  -0.03, 17.6453 to \
  -0.03, 8.69495 to \
  -4.16238, 8.69495 to \
  -4.16238, 17.6453 front fs empty border lc rgb '#549f' lw 0.1
set object 893 polygon from \
  -4.11977, 17.6654 to \
  -0.03, 17.6654 to \
  -0.03, 8.70506 to \
  -4.11977, 8.70506 to \
  -4.11977, 17.6654 front fs empty border lc rgb '#549f' lw 0.1
set object 894 polygon from \
  -4.07628, 17.6855 to \
  -0.03, 17.6855 to \
  -0.03, 8.71517 to \
  -4.07628, 8.71517 to \
  -4.07628, 17.6855 front fs empty border lc rgb '#549f' lw 0.1
set object 895 polygon from \
  -4.03192, 17.7056 to \
  -0.03, 17.7056 to \
  -0.03, 8.72529 to \
  -4.03192, 8.72529 to \
  -4.03192, 17.7056 front fs empty border lc rgb '#549f' lw 0.1
set object 896 polygon from \
  -3.98671, 17.7258 to \
  -0.03, 17.7258 to \
  -0.03, 8.7354 to \
  -3.98671, 8.7354 to \
  -3.98671, 17.7258 front fs empty border lc rgb '#549f' lw 0.1
set object 897 polygon from \
  -3.94067, 17.7459 to \
  -0.03, 17.7459 to \
  -0.03, 8.74552 to \
  -3.94067, 8.74552 to \
  -3.94067, 17.7459 front fs empty border lc rgb '#549f' lw 0.1
set object 898 polygon from \
  -3.89382, 17.766 to \
  -0.03, 17.766 to \
  -0.03, 8.75564 to \
  -3.89382, 8.75564 to \
  -3.89382, 17.766 front fs empty border lc rgb '#549f' lw 0.1
set object 899 polygon from \
  -3.84617, 17.7861 to \
  -0.03, 17.7861 to \
  -0.03, 8.76576 to \
  -3.84617, 8.76576 to \
  -3.84617, 17.7861 front fs empty border lc rgb '#549f' lw 0.1
set object 900 polygon from \
  -3.79775, 17.8062 to \
  -0.03, 17.8062 to \
  -0.03, 8.77588 to \
  -3.79775, 8.77588 to \
  -3.79775, 17.8062 front fs empty border lc rgb '#549f' lw 0.1
set object 901 polygon from \
  -3.74857, 17.8264 to \
  -0.03, 17.8264 to \
  -0.03, 8.786 to \
  -3.74857, 8.786 to \
  -3.74857, 17.8264 front fs empty border lc rgb '#549f' lw 0.1
set object 902 polygon from \
  -3.69866, 17.8465 to \
  -0.03, 17.8465 to \
  -0.03, 8.79612 to \
  -3.69866, 8.79612 to \
  -3.69866, 17.8465 front fs empty border lc rgb '#549f' lw 0.1
set object 903 polygon from \
  -3.64804, 17.8666 to \
  -0.03, 17.8666 to \
  -0.03, 8.80625 to \
  -3.64804, 8.80625 to \
  -3.64804, 17.8666 front fs empty border lc rgb '#549f' lw 0.1
set object 904 polygon from \
  -3.59672, 17.8868 to \
  -0.03, 17.8868 to \
  -0.03, 8.81637 to \
  -3.59672, 8.81637 to \
  -3.59672, 17.8868 front fs empty border lc rgb '#549f' lw 0.1
set object 905 polygon from \
  -3.54472, 17.9069 to \
  -0.03, 17.9069 to \
  -0.03, 8.8265 to \
  -3.54472, 8.8265 to \
  -3.54472, 17.9069 front fs empty border lc rgb '#549f' lw 0.1
set object 906 polygon from \
  -3.49208, 17.927 to \
  -0.03, 17.927 to \
  -0.03, 8.83663 to \
  -3.49208, 8.83663 to \
  -3.49208, 17.927 front fs empty border lc rgb '#549f' lw 0.1
set object 907 polygon from \
  -3.43881, 17.9472 to \
  -0.03, 17.9472 to \
  -0.03, 8.84676 to \
  -3.43881, 8.84676 to \
  -3.43881, 17.9472 front fs empty border lc rgb '#549f' lw 0.1
set object 908 polygon from \
  -3.38493, 17.9673 to \
  -0.03, 17.9673 to \
  -0.03, 8.85689 to \
  -3.38493, 8.85689 to \
  -3.38493, 17.9673 front fs empty border lc rgb '#549f' lw 0.1
set object 909 polygon from \
  -3.33046, 17.9874 to \
  -0.03, 17.9874 to \
  -0.03, 8.86702 to \
  -3.33046, 8.86702 to \
  -3.33046, 17.9874 front fs empty border lc rgb '#549f' lw 0.1
set object 910 polygon from \
  -3.27543, 18.0076 to \
  -0.03, 18.0076 to \
  -0.03, 8.87715 to \
  -3.27543, 8.87715 to \
  -3.27543, 18.0076 front fs empty border lc rgb '#549f' lw 0.1
set object 911 polygon from \
  -3.21986, 18.0277 to \
  -0.03, 18.0277 to \
  -0.03, 8.88729 to \
  -3.21986, 8.88729 to \
  -3.21986, 18.0277 front fs empty border lc rgb '#549f' lw 0.1
set object 912 polygon from \
  -3.16378, 18.0478 to \
  -0.03, 18.0478 to \
  -0.03, 8.89742 to \
  -3.16378, 8.89742 to \
  -3.16378, 18.0478 front fs empty border lc rgb '#549f' lw 0.1
set object 913 polygon from \
  -3.1072, 18.068 to \
  -0.03, 18.068 to \
  -0.03, 8.90756 to \
  -3.1072, 8.90756 to \
  -3.1072, 18.068 front fs empty border lc rgb '#549f' lw 0.1
set object 914 polygon from \
  -3.05014, 18.0881 to \
  -0.03, 18.0881 to \
  -0.03, 8.9177 to \
  -3.05014, 8.9177 to \
  -3.05014, 18.0881 front fs empty border lc rgb '#549f' lw 0.1
set object 915 polygon from \
  -2.99264, 18.1083 to \
  -0.03, 18.1083 to \
  -0.03, 8.92784 to \
  -2.99264, 8.92784 to \
  -2.99264, 18.1083 front fs empty border lc rgb '#549f' lw 0.1
set object 916 polygon from \
  -2.93472, 18.1284 to \
  -0.03, 18.1284 to \
  -0.03, 8.93798 to \
  -2.93472, 8.93798 to \
  -2.93472, 18.1284 front fs empty border lc rgb '#549f' lw 0.1
set object 917 polygon from \
  -2.8764, 18.1486 to \
  -0.03, 18.1486 to \
  -0.03, 8.94812 to \
  -2.8764, 8.94812 to \
  -2.8764, 18.1486 front fs empty border lc rgb '#549f' lw 0.1
set object 918 polygon from \
  -2.8177, 18.1687 to \
  -0.03, 18.1687 to \
  -0.03, 8.95826 to \
  -2.8177, 8.95826 to \
  -2.8177, 18.1687 front fs empty border lc rgb '#549f' lw 0.1
set object 919 polygon from \
  -2.75864, 18.1889 to \
  -0.03, 18.1889 to \
  -0.03, 8.96841 to \
  -2.75864, 8.96841 to \
  -2.75864, 18.1889 front fs empty border lc rgb '#549f' lw 0.1
set object 920 polygon from \
  -2.69927, 18.209 to \
  -0.03, 18.209 to \
  -0.03, 8.97855 to \
  -2.69927, 8.97855 to \
  -2.69927, 18.209 front fs empty border lc rgb '#549f' lw 0.1
set object 921 polygon from \
  -2.63958, 18.2292 to \
  -0.03, 18.2292 to \
  -0.03, 8.9887 to \
  -2.63958, 8.9887 to \
  -2.63958, 18.2292 front fs empty border lc rgb '#549f' lw 0.1
set object 922 polygon from \
  -2.57962, 18.2493 to \
  -0.03, 18.2493 to \
  -0.03, 8.99885 to \
  -2.57962, 8.99885 to \
  -2.57962, 18.2493 front fs empty border lc rgb '#549f' lw 0.1
set object 923 polygon from \
  -2.51941, 18.2695 to \
  -0.03, 18.2695 to \
  -0.03, 9.009 to \
  -2.51941, 9.009 to \
  -2.51941, 18.2695 front fs empty border lc rgb '#549f' lw 0.1
set object 924 polygon from \
  -2.45896, 18.2896 to \
  -0.03, 18.2896 to \
  -0.03, 9.01915 to \
  -2.45896, 9.01915 to \
  -2.45896, 18.2896 front fs empty border lc rgb '#549f' lw 0.1
set object 925 polygon from \
  -2.39832, 18.3098 to \
  -0.03, 18.3098 to \
  -0.03, 9.0293 to \
  -2.39832, 9.0293 to \
  -2.39832, 18.3098 front fs empty border lc rgb '#549f' lw 0.1
set object 926 polygon from \
  -2.33749, 18.3299 to \
  -0.03, 18.3299 to \
  -0.03, 9.03945 to \
  -2.33749, 9.03945 to \
  -2.33749, 18.3299 front fs empty border lc rgb '#549f' lw 0.1
set object 927 polygon from \
  -2.2765, 18.3501 to \
  -0.03, 18.3501 to \
  -0.03, 9.04961 to \
  -2.2765, 9.04961 to \
  -2.2765, 18.3501 front fs empty border lc rgb '#549f' lw 0.1
set object 928 polygon from \
  -2.21539, 18.3702 to \
  -0.03, 18.3702 to \
  -0.03, 9.05976 to \
  -2.21539, 9.05976 to \
  -2.21539, 18.3702 front fs empty border lc rgb '#549f' lw 0.1
set object 929 polygon from \
  -2.15417, 18.3904 to \
  -0.03, 18.3904 to \
  -0.03, 9.06992 to \
  -2.15417, 9.06992 to \
  -2.15417, 18.3904 front fs empty border lc rgb '#549f' lw 0.1
set object 930 polygon from \
  -2.09287, 18.4106 to \
  -0.03, 18.4106 to \
  -0.03, 9.08008 to \
  -2.09287, 9.08008 to \
  -2.09287, 18.4106 front fs empty border lc rgb '#549f' lw 0.1
set object 931 polygon from \
  -2.03152, 18.4307 to \
  -0.03, 18.4307 to \
  -0.03, 9.09024 to \
  -2.03152, 9.09024 to \
  -2.03152, 18.4307 front fs empty border lc rgb '#549f' lw 0.1
set object 932 polygon from \
  -1.97013, 18.4509 to \
  -0.03, 18.4509 to \
  -0.03, 9.1004 to \
  -1.97013, 9.1004 to \
  -1.97013, 18.4509 front fs empty border lc rgb '#549f' lw 0.1
set object 933 polygon from \
  -1.90874, 18.4711 to \
  -0.03, 18.4711 to \
  -0.03, 9.11056 to \
  -1.90874, 9.11056 to \
  -1.90874, 18.4711 front fs empty border lc rgb '#549f' lw 0.1
set object 934 polygon from \
  -1.84736, 18.4912 to \
  -0.03, 18.4912 to \
  -0.03, 9.12072 to \
  -1.84736, 9.12072 to \
  -1.84736, 18.4912 front fs empty border lc rgb '#549f' lw 0.1
set object 935 polygon from \
  -1.78603, 18.5114 to \
  -0.03, 18.5114 to \
  -0.03, 9.13089 to \
  -1.78603, 9.13089 to \
  -1.78603, 18.5114 front fs empty border lc rgb '#549f' lw 0.1
set object 936 polygon from \
  -1.72476, 18.5316 to \
  -0.03, 18.5316 to \
  -0.03, 9.14105 to \
  -1.72476, 9.14105 to \
  -1.72476, 18.5316 front fs empty border lc rgb '#549f' lw 0.1
set object 937 polygon from \
  -1.66359, 18.5517 to \
  -0.03, 18.5517 to \
  -0.03, 9.15122 to \
  -1.66359, 9.15122 to \
  -1.66359, 18.5517 front fs empty border lc rgb '#549f' lw 0.1
set object 938 polygon from \
  -1.60253, 18.5719 to \
  -0.03, 18.5719 to \
  -0.03, 9.16139 to \
  -1.60253, 9.16139 to \
  -1.60253, 18.5719 front fs empty border lc rgb '#549f' lw 0.1
set object 939 polygon from \
  -1.54161, 18.5921 to \
  -0.03, 18.5921 to \
  -0.03, 9.17156 to \
  -1.54161, 9.17156 to \
  -1.54161, 18.5921 front fs empty border lc rgb '#549f' lw 0.1
set object 940 polygon from \
  -1.48086, 18.6122 to \
  -0.03, 18.6122 to \
  -0.03, 9.18173 to \
  -1.48086, 9.18173 to \
  -1.48086, 18.6122 front fs empty border lc rgb '#549f' lw 0.1
set object 941 polygon from \
  -1.42029, 18.6324 to \
  -0.03, 18.6324 to \
  -0.03, 9.1919 to \
  -1.42029, 9.1919 to \
  -1.42029, 18.6324 front fs empty border lc rgb '#549f' lw 0.1
set object 942 polygon from \
  -1.35993, 18.6526 to \
  -0.03, 18.6526 to \
  -0.03, 9.20207 to \
  -1.35993, 9.20207 to \
  -1.35993, 18.6526 front fs empty border lc rgb '#549f' lw 0.1
set object 943 polygon from \
  -1.2998, 18.6728 to \
  -0.03, 18.6728 to \
  -0.03, 9.21225 to \
  -1.2998, 9.21225 to \
  -1.2998, 18.6728 front fs empty border lc rgb '#549f' lw 0.1
set object 944 polygon from \
  -1.23994, 18.693 to \
  -0.03, 18.693 to \
  -0.03, 9.22242 to \
  -1.23994, 9.22242 to \
  -1.23994, 18.693 front fs empty border lc rgb '#549f' lw 0.1
set object 945 polygon from \
  -1.18035, 18.7131 to \
  -0.03, 18.7131 to \
  -0.03, 9.2326 to \
  -1.18035, 9.2326 to \
  -1.18035, 18.7131 front fs empty border lc rgb '#549f' lw 0.1
set object 946 polygon from \
  -1.12106, 18.7333 to \
  -0.03, 18.7333 to \
  -0.03, 9.24278 to \
  -1.12106, 9.24278 to \
  -1.12106, 18.7333 front fs empty border lc rgb '#549f' lw 0.1
set object 947 polygon from \
  -1.0621, 18.7535 to \
  -0.03, 18.7535 to \
  -0.03, 9.25296 to \
  -1.0621, 9.25296 to \
  -1.0621, 18.7535 front fs empty border lc rgb '#549f' lw 0.1
set object 948 polygon from \
  -1.00349, 18.7737 to \
  -0.03, 18.7737 to \
  -0.03, 9.26314 to \
  -1.00349, 9.26314 to \
  -1.00349, 18.7737 front fs empty border lc rgb '#549f' lw 0.1
set object 949 polygon from \
  -0.967563, 18.7939 to \
  -0.03, 18.7939 to \
  -0.03, 9.27332 to \
  -0.967563, 9.27332 to \
  -0.967563, 18.7939 front fs empty border lc rgb '#549f' lw 0.1
set object 950 polygon from \
  -0.940446, 18.8141 to \
  -0.03, 18.8141 to \
  -0.03, 9.2835 to \
  -0.940446, 9.2835 to \
  -0.940446, 18.8141 front fs empty border lc rgb '#549f' lw 0.1
set object 951 polygon from \
  -0.913135, 18.8343 to \
  -0.03, 18.8343 to \
  -0.03, 9.29369 to \
  -0.913135, 9.29369 to \
  -0.913135, 18.8343 front fs empty border lc rgb '#549f' lw 0.1
set object 952 polygon from \
  -0.885628, 18.8544 to \
  -0.03, 18.8544 to \
  -0.03, 9.30387 to \
  -0.885628, 9.30387 to \
  -0.885628, 18.8544 front fs empty border lc rgb '#549f' lw 0.1
set object 953 polygon from \
  -0.877506, 18.8746 to \
  -0.03, 18.8746 to \
  -0.03, 9.31406 to \
  -0.877506, 9.31406 to \
  -0.877506, 18.8746 front fs empty border lc rgb '#549f' lw 0.1
set object 954 polygon from \
  -0.898669, 18.8948 to \
  -0.03, 18.8948 to \
  -0.03, 9.32425 to \
  -0.898669, 9.32425 to \
  -0.898669, 18.8948 front fs empty border lc rgb '#549f' lw 0.1
set object 955 polygon from \
  -0.918963, 18.915 to \
  -0.03, 18.915 to \
  -0.03, 9.33444 to \
  -0.918963, 9.33444 to \
  -0.918963, 18.915 front fs empty border lc rgb '#549f' lw 0.1
set object 956 polygon from \
  -0.938366, 18.9352 to \
  -0.03, 18.9352 to \
  -0.03, 9.34463 to \
  -0.938366, 9.34463 to \
  -0.938366, 18.9352 front fs empty border lc rgb '#549f' lw 0.1
set object 957 polygon from \
  -0.956857, 18.9554 to \
  -0.03, 18.9554 to \
  -0.03, 9.35482 to \
  -0.956857, 9.35482 to \
  -0.956857, 18.9554 front fs empty border lc rgb '#549f' lw 0.1
set object 958 polygon from \
  -0.989868, 18.9756 to \
  -0.03, 18.9756 to \
  -0.03, 9.36501 to \
  -0.989868, 9.36501 to \
  -0.989868, 18.9756 front fs empty border lc rgb '#549f' lw 0.1
set object 959 polygon from \
  -1.02858, 18.9958 to \
  -0.03, 18.9958 to \
  -0.03, 9.37521 to \
  -1.02858, 9.37521 to \
  -1.02858, 18.9958 front fs empty border lc rgb '#549f' lw 0.1
set object 960 polygon from \
  -1.0664, 19.016 to \
  -0.03, 19.016 to \
  -0.03, 9.3854 to \
  -1.0664, 9.3854 to \
  -1.0664, 19.016 front fs empty border lc rgb '#549f' lw 0.1
set object 961 polygon from \
  -1.10331, 19.0362 to \
  -0.03, 19.0362 to \
  -0.03, 9.3956 to \
  -1.10331, 9.3956 to \
  -1.10331, 19.0362 front fs empty border lc rgb '#549f' lw 0.1
set object 962 polygon from \
  -1.13929, 19.0564 to \
  -0.03, 19.0564 to \
  -0.03, 9.4058 to \
  -1.13929, 9.4058 to \
  -1.13929, 19.0564 front fs empty border lc rgb '#549f' lw 0.1
set object 963 polygon from \
  -1.17432, 19.0766 to \
  -0.03, 19.0766 to \
  -0.03, 9.416 to \
  -1.17432, 9.416 to \
  -1.17432, 19.0766 front fs empty border lc rgb '#549f' lw 0.1
set object 964 polygon from \
  -1.20839, 19.0968 to \
  -0.03, 19.0968 to \
  -0.03, 9.4262 to \
  -1.20839, 9.4262 to \
  -1.20839, 19.0968 front fs empty border lc rgb '#549f' lw 0.1
set object 965 polygon from \
  -1.24149, 19.117 to \
  -0.03, 19.117 to \
  -0.03, 9.4364 to \
  -1.24149, 9.4364 to \
  -1.24149, 19.117 front fs empty border lc rgb '#549f' lw 0.1
set object 966 polygon from \
  -1.2736, 19.1372 to \
  -0.03, 19.1372 to \
  -0.03, 9.4466 to \
  -1.2736, 9.4466 to \
  -1.2736, 19.1372 front fs empty border lc rgb '#549f' lw 0.1
set object 967 polygon from \
  -1.30472, 19.1574 to \
  -0.03, 19.1574 to \
  -0.03, 9.45681 to \
  -1.30472, 9.45681 to \
  -1.30472, 19.1574 front fs empty border lc rgb '#549f' lw 0.1
set object 968 polygon from \
  -1.33481, 19.1776 to \
  -0.03, 19.1776 to \
  -0.03, 9.46701 to \
  -1.33481, 9.46701 to \
  -1.33481, 19.1776 front fs empty border lc rgb '#549f' lw 0.1
set object 969 polygon from \
  -1.36388, 19.1979 to \
  -0.03, 19.1979 to \
  -0.03, 9.47722 to \
  -1.36388, 9.47722 to \
  -1.36388, 19.1979 front fs empty border lc rgb '#549f' lw 0.1
set object 970 polygon from \
  -1.39191, 19.2181 to \
  -0.03, 19.2181 to \
  -0.03, 9.48743 to \
  -1.39191, 9.48743 to \
  -1.39191, 19.2181 front fs empty border lc rgb '#549f' lw 0.1
set object 971 polygon from \
  -1.41889, 19.2383 to \
  -0.03, 19.2383 to \
  -0.03, 9.49764 to \
  -1.41889, 9.49764 to \
  -1.41889, 19.2383 front fs empty border lc rgb '#549f' lw 0.1
set object 972 polygon from \
  -1.44481, 19.2585 to \
  -0.03, 19.2585 to \
  -0.03, 9.50785 to \
  -1.44481, 9.50785 to \
  -1.44481, 19.2585 front fs empty border lc rgb '#549f' lw 0.1
set object 973 polygon from \
  -1.46966, 19.2787 to \
  -0.03, 19.2787 to \
  -0.03, 9.51806 to \
  -1.46966, 9.51806 to \
  -1.46966, 19.2787 front fs empty border lc rgb '#549f' lw 0.1
set object 974 polygon from \
  -1.49342, 19.2989 to \
  -0.03, 19.2989 to \
  -0.03, 9.52827 to \
  -1.49342, 9.52827 to \
  -1.49342, 19.2989 front fs empty border lc rgb '#549f' lw 0.1
set object 975 polygon from \
  -1.5161, 19.3191 to \
  -0.03, 19.3191 to \
  -0.03, 9.53849 to \
  -1.5161, 9.53849 to \
  -1.5161, 19.3191 front fs empty border lc rgb '#549f' lw 0.1
set object 976 polygon from \
  -1.54304, 19.3394 to \
  -0.03, 19.3394 to \
  -0.03, 9.5487 to \
  -1.54304, 9.5487 to \
  -1.54304, 19.3394 front fs empty border lc rgb '#549f' lw 0.1
set object 977 polygon from \
  -1.57214, 19.3596 to \
  -0.03, 19.3596 to \
  -0.03, 9.55892 to \
  -1.57214, 9.55892 to \
  -1.57214, 19.3596 front fs empty border lc rgb '#549f' lw 0.1
set object 978 polygon from \
  -1.60012, 19.3798 to \
  -0.03, 19.3798 to \
  -0.03, 9.56914 to \
  -1.60012, 9.56914 to \
  -1.60012, 19.3798 front fs empty border lc rgb '#549f' lw 0.1
set object 979 polygon from \
  -1.62696, 19.4 to \
  -0.03, 19.4 to \
  -0.03, 9.57936 to \
  -1.62696, 9.57936 to \
  -1.62696, 19.4 front fs empty border lc rgb '#549f' lw 0.1
set object 980 polygon from \
  -1.65267, 19.4202 to \
  -0.03, 19.4202 to \
  -0.03, 9.58958 to \
  -1.65267, 9.58958 to \
  -1.65267, 19.4202 front fs empty border lc rgb '#549f' lw 0.1
set object 981 polygon from \
  -1.67722, 19.4405 to \
  -0.03, 19.4405 to \
  -0.03, 9.5998 to \
  -1.67722, 9.5998 to \
  -1.67722, 19.4405 front fs empty border lc rgb '#549f' lw 0.1
set object 982 polygon from \
  -1.70062, 19.4607 to \
  -0.03, 19.4607 to \
  -0.03, 9.61002 to \
  -1.70062, 9.61002 to \
  -1.70062, 19.4607 front fs empty border lc rgb '#549f' lw 0.1
set object 983 polygon from \
  -1.72287, 19.4809 to \
  -0.03, 19.4809 to \
  -0.03, 9.62025 to \
  -1.72287, 9.62025 to \
  -1.72287, 19.4809 front fs empty border lc rgb '#549f' lw 0.1
set object 984 polygon from \
  -1.74395, 19.5012 to \
  -0.03, 19.5012 to \
  -0.03, 9.63047 to \
  -1.74395, 9.63047 to \
  -1.74395, 19.5012 front fs empty border lc rgb '#549f' lw 0.1
set object 985 polygon from \
  -1.76387, 19.5214 to \
  -0.03, 19.5214 to \
  -0.03, 9.6407 to \
  -1.76387, 9.6407 to \
  -1.76387, 19.5214 front fs empty border lc rgb '#549f' lw 0.1
set object 986 polygon from \
  -1.78262, 19.5416 to \
  -0.03, 19.5416 to \
  -0.03, 9.65093 to \
  -1.78262, 9.65093 to \
  -1.78262, 19.5416 front fs empty border lc rgb '#549f' lw 0.1
set object 987 polygon from \
  -1.80019, 19.5619 to \
  -0.03, 19.5619 to \
  -0.03, 9.66116 to \
  -1.80019, 9.66116 to \
  -1.80019, 19.5619 front fs empty border lc rgb '#549f' lw 0.1
set object 988 polygon from \
  -1.81659, 19.5821 to \
  -0.03, 19.5821 to \
  -0.03, 9.67139 to \
  -1.81659, 9.67139 to \
  -1.81659, 19.5821 front fs empty border lc rgb '#549f' lw 0.1
set object 989 polygon from \
  -1.83182, 19.6023 to \
  -0.03, 19.6023 to \
  -0.03, 9.68162 to \
  -1.83182, 9.68162 to \
  -1.83182, 19.6023 front fs empty border lc rgb '#549f' lw 0.1
set object 990 polygon from \
  -1.84587, 19.6226 to \
  -0.03, 19.6226 to \
  -0.03, 9.69185 to \
  -1.84587, 9.69185 to \
  -1.84587, 19.6226 front fs empty border lc rgb '#549f' lw 0.1
set object 991 polygon from \
  -1.85874, 19.6428 to \
  -0.03, 19.6428 to \
  -0.03, 9.70209 to \
  -1.85874, 9.70209 to \
  -1.85874, 19.6428 front fs empty border lc rgb '#549f' lw 0.1
set object 992 polygon from \
  -1.87043, 19.663 to \
  -0.03, 19.663 to \
  -0.03, 9.71232 to \
  -1.87043, 9.71232 to \
  -1.87043, 19.663 front fs empty border lc rgb '#549f' lw 0.1
set object 993 polygon from \
  -1.88095, 19.6833 to \
  -0.03, 19.6833 to \
  -0.03, 9.72256 to \
  -1.88095, 9.72256 to \
  -1.88095, 19.6833 front fs empty border lc rgb '#549f' lw 0.1
set object 994 polygon from \
  -1.89029, 19.7035 to \
  -0.03, 19.7035 to \
  -0.03, 9.7328 to \
  -1.89029, 9.7328 to \
  -1.89029, 19.7035 front fs empty border lc rgb '#549f' lw 0.1
set object 995 polygon from \
  -1.89846, 19.7238 to \
  -0.03, 19.7238 to \
  -0.03, 9.74304 to \
  -1.89846, 9.74304 to \
  -1.89846, 19.7238 front fs empty border lc rgb '#549f' lw 0.1
set object 996 polygon from \
  -1.90546, 19.744 to \
  -0.03, 19.744 to \
  -0.03, 9.75328 to \
  -1.90546, 9.75328 to \
  -1.90546, 19.744 front fs empty border lc rgb '#549f' lw 0.1
set object 997 polygon from \
  -1.91129, 19.7643 to \
  -0.03, 19.7643 to \
  -0.03, 9.76352 to \
  -1.91129, 9.76352 to \
  -1.91129, 19.7643 front fs empty border lc rgb '#549f' lw 0.1
set object 998 polygon from \
  -1.91596, 19.7845 to \
  -0.03, 19.7845 to \
  -0.03, 9.77376 to \
  -1.91596, 9.77376 to \
  -1.91596, 19.7845 front fs empty border lc rgb '#549f' lw 0.1
set object 999 polygon from \
  -1.91947, 19.8048 to \
  -0.03, 19.8048 to \
  -0.03, 9.78401 to \
  -1.91947, 9.78401 to \
  -1.91947, 19.8048 front fs empty border lc rgb '#549f' lw 0.1
set object 1000 polygon from \
  -1.92182, 19.825 to \
  -0.03, 19.825 to \
  -0.03, 9.79425 to \
  -1.92182, 9.79425 to \
  -1.92182, 19.825 front fs empty border lc rgb '#549f' lw 0.1
set object 1001 polygon from \
  -1.92303, 19.8453 to \
  -0.03, 19.8453 to \
  -0.03, 9.8045 to \
  -1.92303, 9.8045 to \
  -1.92303, 19.8453 front fs empty border lc rgb '#549f' lw 0.1
set object 1002 polygon from \
  -1.9231, 19.8655 to \
  -0.03, 19.8655 to \
  -0.03, 9.81475 to \
  -1.9231, 9.81475 to \
  -1.9231, 19.8655 front fs empty border lc rgb '#549f' lw 0.1
set object 1003 polygon from \
  -1.92309, 19.8858 to \
  -0.03, 19.8858 to \
  -0.03, 9.825 to \
  -1.92309, 9.825 to \
  -1.92309, 19.8858 front fs empty border lc rgb '#549f' lw 0.1
set object 1004 polygon from \
  -1.92202, 19.906 to \
  -0.03, 19.906 to \
  -0.03, 9.83525 to \
  -1.92202, 9.83525 to \
  -1.92202, 19.906 front fs empty border lc rgb '#549f' lw 0.1
set object 1005 polygon from \
  -1.91982, 19.9263 to \
  -0.03, 19.9263 to \
  -0.03, 9.8455 to \
  -1.91982, 9.8455 to \
  -1.91982, 19.9263 front fs empty border lc rgb '#549f' lw 0.1
set object 1006 polygon from \
  -1.9165, 19.9465 to \
  -0.03, 19.9465 to \
  -0.03, 9.85575 to \
  -1.9165, 9.85575 to \
  -1.9165, 19.9465 front fs empty border lc rgb '#549f' lw 0.1
set object 1007 polygon from \
  -1.91207, 19.9668 to \
  -0.03, 19.9668 to \
  -0.03, 9.86601 to \
  -1.91207, 9.86601 to \
  -1.91207, 19.9668 front fs empty border lc rgb '#549f' lw 0.1
set object 1008 polygon from \
  -1.90653, 19.987 to \
  -0.03, 19.987 to \
  -0.03, 9.87626 to \
  -1.90653, 9.87626 to \
  -1.90653, 19.987 front fs empty border lc rgb '#549f' lw 0.1
set object 1009 polygon from \
  -1.8999, 20.0073 to \
  -0.03, 20.0073 to \
  -0.03, 9.88652 to \
  -1.8999, 9.88652 to \
  -1.8999, 20.0073 front fs empty border lc rgb '#549f' lw 0.1
set object 1010 polygon from \
  -1.89219, 20.0276 to \
  -0.03, 20.0276 to \
  -0.03, 9.89678 to \
  -1.89219, 9.89678 to \
  -1.89219, 20.0276 front fs empty border lc rgb '#549f' lw 0.1
set object 1011 polygon from \
  -1.8834, 20.0478 to \
  -0.03, 20.0478 to \
  -0.03, 9.90704 to \
  -1.8834, 9.90704 to \
  -1.8834, 20.0478 front fs empty border lc rgb '#549f' lw 0.1
set object 1012 polygon from \
  -1.87355, 20.0681 to \
  -0.03, 20.0681 to \
  -0.03, 9.9173 to \
  -1.87355, 9.9173 to \
  -1.87355, 20.0681 front fs empty border lc rgb '#549f' lw 0.1
set object 1013 polygon from \
  -1.86264, 20.0884 to \
  -0.03, 20.0884 to \
  -0.03, 9.92756 to \
  -1.86264, 9.92756 to \
  -1.86264, 20.0884 front fs empty border lc rgb '#549f' lw 0.1
set object 1014 polygon from \
  -1.8507, 20.1086 to \
  -0.03, 20.1086 to \
  -0.03, 9.93782 to \
  -1.8507, 9.93782 to \
  -1.8507, 20.1086 front fs empty border lc rgb '#549f' lw 0.1
set object 1015 polygon from \
  -1.83773, 20.1289 to \
  -0.03, 20.1289 to \
  -0.03, 9.94809 to \
  -1.83773, 9.94809 to \
  -1.83773, 20.1289 front fs empty border lc rgb '#549f' lw 0.1
set object 1016 polygon from \
  -1.82375, 20.1492 to \
  -0.03, 20.1492 to \
  -0.03, 9.95835 to \
  -1.82375, 9.95835 to \
  -1.82375, 20.1492 front fs empty border lc rgb '#549f' lw 0.1
set object 1017 polygon from \
  -1.80877, 20.1694 to \
  -0.03, 20.1694 to \
  -0.03, 9.96862 to \
  -1.80877, 9.96862 to \
  -1.80877, 20.1694 front fs empty border lc rgb '#549f' lw 0.1
set object 1018 polygon from \
  -1.81661, 20.1897 to \
  -0.03, 20.1897 to \
  -0.03, 9.97889 to \
  -1.81661, 9.97889 to \
  -1.81661, 20.1897 front fs empty border lc rgb '#549f' lw 0.1
set object 1019 polygon from \
  -1.84504, 20.21 to \
  -0.03, 20.21 to \
  -0.03, 9.98916 to \
  -1.84504, 9.98916 to \
  -1.84504, 20.21 front fs empty border lc rgb '#549f' lw 0.1
set object 1020 polygon from \
  -1.87305, 20.2302 to \
  -0.03, 20.2302 to \
  -0.03, 9.99943 to \
  -1.87305, 9.99943 to \
  -1.87305, 20.2302 front fs empty border lc rgb '#549f' lw 0.1
set object 1021 polygon from \
  -1.90061, 20.2505 to \
  -0.03, 20.2505 to \
  -0.03, 10.0097 to \
  -1.90061, 10.0097 to \
  -1.90061, 20.2505 front fs empty border lc rgb '#549f' lw 0.1
set object 1022 polygon from \
  -1.9277, 20.2708 to \
  -0.03, 20.2708 to \
  -0.03, 10.02 to \
  -1.9277, 10.02 to \
  -1.9277, 20.2708 front fs empty border lc rgb '#549f' lw 0.1
set object 1023 polygon from \
  -1.95431, 20.2911 to \
  -0.03, 20.2911 to \
  -0.03, 10.0302 to \
  -1.95431, 10.0302 to \
  -1.95431, 20.2911 front fs empty border lc rgb '#549f' lw 0.1
set object 1024 polygon from \
  -1.98042, 20.3114 to \
  -0.03, 20.3114 to \
  -0.03, 10.0405 to \
  -1.98042, 10.0405 to \
  -1.98042, 20.3114 front fs empty border lc rgb '#549f' lw 0.1
set object 1025 polygon from \
  -2.00603, 20.3316 to \
  -0.03, 20.3316 to \
  -0.03, 10.0508 to \
  -2.00603, 10.0508 to \
  -2.00603, 20.3316 front fs empty border lc rgb '#549f' lw 0.1
set object 1026 polygon from \
  -2.03113, 20.3519 to \
  -0.03, 20.3519 to \
  -0.03, 10.0611 to \
  -2.03113, 10.0611 to \
  -2.03113, 20.3519 front fs empty border lc rgb '#549f' lw 0.1
set object 1027 polygon from \
  -2.05568, 20.3722 to \
  -0.03, 20.3722 to \
  -0.03, 10.0714 to \
  -2.05568, 10.0714 to \
  -2.05568, 20.3722 front fs empty border lc rgb '#549f' lw 0.1
set object 1028 polygon from \
  -2.07969, 20.3925 to \
  -0.03, 20.3925 to \
  -0.03, 10.0816 to \
  -2.07969, 10.0816 to \
  -2.07969, 20.3925 front fs empty border lc rgb '#549f' lw 0.1
set object 1029 polygon from \
  -2.10314, 20.4128 to \
  -0.03, 20.4128 to \
  -0.03, 10.0919 to \
  -2.10314, 10.0919 to \
  -2.10314, 20.4128 front fs empty border lc rgb '#549f' lw 0.1
set object 1030 polygon from \
  -2.12602, 20.4331 to \
  -0.03, 20.4331 to \
  -0.03, 10.1022 to \
  -2.12602, 10.1022 to \
  -2.12602, 20.4331 front fs empty border lc rgb '#549f' lw 0.1
set object 1031 polygon from \
  -2.14831, 20.4534 to \
  -0.03, 20.4534 to \
  -0.03, 10.1125 to \
  -2.14831, 10.1125 to \
  -2.14831, 20.4534 front fs empty border lc rgb '#549f' lw 0.1
set object 1032 polygon from \
  -2.17, 20.4736 to \
  -0.03, 20.4736 to \
  -0.03, 10.1228 to \
  -2.17, 10.1228 to \
  -2.17, 20.4736 front fs empty border lc rgb '#549f' lw 0.1
set object 1033 polygon from \
  -2.19107, 20.4939 to \
  -0.03, 20.4939 to \
  -0.03, 10.1331 to \
  -2.19107, 10.1331 to \
  -2.19107, 20.4939 front fs empty border lc rgb '#549f' lw 0.1
set object 1034 polygon from \
  -2.21152, 20.5142 to \
  -0.03, 20.5142 to \
  -0.03, 10.1433 to \
  -2.21152, 10.1433 to \
  -2.21152, 20.5142 front fs empty border lc rgb '#549f' lw 0.1
set object 1035 polygon from \
  -2.23133, 20.5345 to \
  -0.03, 20.5345 to \
  -0.03, 10.1536 to \
  -2.23133, 10.1536 to \
  -2.23133, 20.5345 front fs empty border lc rgb '#549f' lw 0.1
set object 1036 polygon from \
  -2.25049, 20.5548 to \
  -0.03, 20.5548 to \
  -0.03, 10.1639 to \
  -2.25049, 10.1639 to \
  -2.25049, 20.5548 front fs empty border lc rgb '#549f' lw 0.1
set object 1037 polygon from \
  -2.26898, 20.5751 to \
  -0.03, 20.5751 to \
  -0.03, 10.1742 to \
  -2.26898, 10.1742 to \
  -2.26898, 20.5751 front fs empty border lc rgb '#549f' lw 0.1
set object 1038 polygon from \
  -2.2868, 20.5954 to \
  -0.03, 20.5954 to \
  -0.03, 10.1845 to \
  -2.2868, 10.1845 to \
  -2.2868, 20.5954 front fs empty border lc rgb '#549f' lw 0.1
set object 1039 polygon from \
  -2.30393, 20.6157 to \
  -0.03, 20.6157 to \
  -0.03, 10.1948 to \
  -2.30393, 10.1948 to \
  -2.30393, 20.6157 front fs empty border lc rgb '#549f' lw 0.1
set object 1040 polygon from \
  -2.32036, 20.636 to \
  -0.03, 20.636 to \
  -0.03, 10.2051 to \
  -2.32036, 10.2051 to \
  -2.32036, 20.636 front fs empty border lc rgb '#549f' lw 0.1
set object 1041 polygon from \
  -2.33608, 20.6563 to \
  -0.03, 20.6563 to \
  -0.03, 10.2154 to \
  -2.33608, 10.2154 to \
  -2.33608, 20.6563 front fs empty border lc rgb '#549f' lw 0.1
set object 1042 polygon from \
  -2.35107, 20.6766 to \
  -0.03, 20.6766 to \
  -0.03, 10.2257 to \
  -2.35107, 10.2257 to \
  -2.35107, 20.6766 front fs empty border lc rgb '#549f' lw 0.1
set object 1043 polygon from \
  -2.36533, 20.6969 to \
  -0.03, 20.6969 to \
  -0.03, 10.236 to \
  -2.36533, 10.236 to \
  -2.36533, 20.6969 front fs empty border lc rgb '#549f' lw 0.1
set object 1044 polygon from \
  -2.37884, 20.7172 to \
  -0.03, 20.7172 to \
  -0.03, 10.2463 to \
  -2.37884, 10.2463 to \
  -2.37884, 20.7172 front fs empty border lc rgb '#549f' lw 0.1
set object 1045 polygon from \
  -2.3916, 20.7375 to \
  -0.03, 20.7375 to \
  -0.03, 10.2566 to \
  -2.3916, 10.2566 to \
  -2.3916, 20.7375 front fs empty border lc rgb '#549f' lw 0.1
set object 1046 polygon from \
  -2.40359, 20.7578 to \
  -0.03, 20.7578 to \
  -0.03, 10.2669 to \
  -2.40359, 10.2669 to \
  -2.40359, 20.7578 front fs empty border lc rgb '#549f' lw 0.1
set object 1047 polygon from \
  -2.4148, 20.7781 to \
  -0.03, 20.7781 to \
  -0.03, 10.2772 to \
  -2.4148, 10.2772 to \
  -2.4148, 20.7781 front fs empty border lc rgb '#549f' lw 0.1
set object 1048 polygon from \
  -2.42523, 20.7984 to \
  -0.03, 20.7984 to \
  -0.03, 10.2875 to \
  -2.42523, 10.2875 to \
  -2.42523, 20.7984 front fs empty border lc rgb '#549f' lw 0.1
set object 1049 polygon from \
  -2.43485, 20.8188 to \
  -0.03, 20.8188 to \
  -0.03, 10.2978 to \
  -2.43485, 10.2978 to \
  -2.43485, 20.8188 front fs empty border lc rgb '#549f' lw 0.1
set object 1050 polygon from \
  -2.44623, 20.8391 to \
  -0.03, 20.8391 to \
  -0.03, 10.3081 to \
  -2.44623, 10.3081 to \
  -2.44623, 20.8391 front fs empty border lc rgb '#549f' lw 0.1
set object 1051 polygon from \
  -2.4579, 20.8594 to \
  -0.03, 20.8594 to \
  -0.03, 10.3184 to \
  -2.4579, 10.3184 to \
  -2.4579, 20.8594 front fs empty border lc rgb '#549f' lw 0.1
set object 1052 polygon from \
  -2.46874, 20.8797 to \
  -0.03, 20.8797 to \
  -0.03, 10.3287 to \
  -2.46874, 10.3287 to \
  -2.46874, 20.8797 front fs empty border lc rgb '#549f' lw 0.1
set object 1053 polygon from \
  -2.47874, 20.9 to \
  -0.03, 20.9 to \
  -0.03, 10.3391 to \
  -2.47874, 10.3391 to \
  -2.47874, 20.9 front fs empty border lc rgb '#549f' lw 0.1
set object 1054 polygon from \
  -2.48789, 20.9203 to \
  -0.03, 20.9203 to \
  -0.03, 10.3494 to \
  -2.48789, 10.3494 to \
  -2.48789, 20.9203 front fs empty border lc rgb '#549f' lw 0.1
set object 1055 polygon from \
  -2.49618, 20.9406 to \
  -0.03, 20.9406 to \
  -0.03, 10.3597 to \
  -2.49618, 10.3597 to \
  -2.49618, 20.9406 front fs empty border lc rgb '#549f' lw 0.1
set object 1056 polygon from \
  -2.5096, 20.961 to \
  -0.03, 20.961 to \
  -0.03, 10.37 to \
  -2.5096, 10.37 to \
  -2.5096, 20.961 front fs empty border lc rgb '#549f' lw 0.1
set object 1057 polygon from \
  -2.52288, 20.9813 to \
  -0.03, 20.9813 to \
  -0.03, 10.3803 to \
  -2.52288, 10.3803 to \
  -2.52288, 20.9813 front fs empty border lc rgb '#549f' lw 0.1
set object 1058 polygon from \
  -2.53528, 21.0016 to \
  -0.03, 21.0016 to \
  -0.03, 10.3906 to \
  -2.53528, 10.3906 to \
  -2.53528, 21.0016 front fs empty border lc rgb '#549f' lw 0.1
set object 1059 polygon from \
  -2.5468, 21.0219 to \
  -0.03, 21.0219 to \
  -0.03, 10.401 to \
  -2.5468, 10.401 to \
  -2.5468, 21.0219 front fs empty border lc rgb '#549f' lw 0.1
set object 1060 polygon from \
  -2.55742, 21.0422 to \
  -0.03, 21.0422 to \
  -0.03, 10.4113 to \
  -2.55742, 10.4113 to \
  -2.55742, 21.0422 front fs empty border lc rgb '#549f' lw 0.1
set object 1061 polygon from \
  -2.56715, 21.0626 to \
  -0.03, 21.0626 to \
  -0.03, 10.4216 to \
  -2.56715, 10.4216 to \
  -2.56715, 21.0626 front fs empty border lc rgb '#549f' lw 0.1
set object 1062 polygon from \
  -2.57596, 21.0829 to \
  -0.03, 21.0829 to \
  -0.03, 10.4319 to \
  -2.57596, 10.4319 to \
  -2.57596, 21.0829 front fs empty border lc rgb '#549f' lw 0.1
set object 1063 polygon from \
  -2.58386, 21.1032 to \
  -0.03, 21.1032 to \
  -0.03, 10.4422 to \
  -2.58386, 10.4422 to \
  -2.58386, 21.1032 front fs empty border lc rgb '#549f' lw 0.1
set object 1064 polygon from \
  -2.59319, 21.1236 to \
  -0.03, 21.1236 to \
  -0.03, 10.4526 to \
  -2.59319, 10.4526 to \
  -2.59319, 21.1236 front fs empty border lc rgb '#549f' lw 0.1
set object 1065 polygon from \
  -2.6035, 21.1439 to \
  -0.03, 21.1439 to \
  -0.03, 10.4629 to \
  -2.6035, 10.4629 to \
  -2.6035, 21.1439 front fs empty border lc rgb '#549f' lw 0.1
set object 1066 polygon from \
  -2.61294, 21.1642 to \
  -0.03, 21.1642 to \
  -0.03, 10.4732 to \
  -2.61294, 10.4732 to \
  -2.61294, 21.1642 front fs empty border lc rgb '#549f' lw 0.1
set object 1067 polygon from \
  -2.62151, 21.1846 to \
  -0.03, 21.1846 to \
  -0.03, 10.4836 to \
  -2.62151, 10.4836 to \
  -2.62151, 21.1846 front fs empty border lc rgb '#549f' lw 0.1
set object 1068 polygon from \
  -2.62919, 21.2049 to \
  -0.03, 21.2049 to \
  -0.03, 10.4939 to \
  -2.62919, 10.4939 to \
  -2.62919, 21.2049 front fs empty border lc rgb '#549f' lw 0.1
set object 1069 polygon from \
  -2.63599, 21.2252 to \
  -0.03, 21.2252 to \
  -0.03, 10.5042 to \
  -2.63599, 10.5042 to \
  -2.63599, 21.2252 front fs empty border lc rgb '#549f' lw 0.1
set object 1070 polygon from \
  -2.64699, 21.2456 to \
  -0.03, 21.2456 to \
  -0.03, 10.5146 to \
  -2.64699, 10.5146 to \
  -2.64699, 21.2456 front fs empty border lc rgb '#549f' lw 0.1
set object 1071 polygon from \
  -2.68485, 21.2659 to \
  -0.03, 21.2659 to \
  -0.03, 10.5249 to \
  -2.68485, 10.5249 to \
  -2.68485, 21.2659 front fs empty border lc rgb '#549f' lw 0.1
set object 1072 polygon from \
  -2.7217, 21.2862 to \
  -0.03, 21.2862 to \
  -0.03, 10.5352 to \
  -2.7217, 10.5352 to \
  -2.7217, 21.2862 front fs empty border lc rgb '#549f' lw 0.1
set object 1073 polygon from \
  -2.75752, 21.3066 to \
  -0.03, 21.3066 to \
  -0.03, 10.5456 to \
  -2.75752, 10.5456 to \
  -2.75752, 21.3066 front fs empty border lc rgb '#549f' lw 0.1
set object 1074 polygon from \
  -2.79228, 21.3269 to \
  -0.03, 21.3269 to \
  -0.03, 10.5559 to \
  -2.79228, 10.5559 to \
  -2.79228, 21.3269 front fs empty border lc rgb '#549f' lw 0.1
set object 1075 polygon from \
  -2.82597, 21.3473 to \
  -0.03, 21.3473 to \
  -0.03, 10.5662 to \
  -2.82597, 10.5662 to \
  -2.82597, 21.3473 front fs empty border lc rgb '#549f' lw 0.1
set object 1076 polygon from \
  -2.85856, 21.3676 to \
  -0.03, 21.3676 to \
  -0.03, 10.5766 to \
  -2.85856, 10.5766 to \
  -2.85856, 21.3676 front fs empty border lc rgb '#549f' lw 0.1
set object 1077 polygon from \
  -2.89002, 21.388 to \
  -0.03, 21.388 to \
  -0.03, 10.5869 to \
  -2.89002, 10.5869 to \
  -2.89002, 21.388 front fs empty border lc rgb '#549f' lw 0.1
set object 1078 polygon from \
  -2.92035, 21.4083 to \
  -0.03, 21.4083 to \
  -0.03, 10.5973 to \
  -2.92035, 10.5973 to \
  -2.92035, 21.4083 front fs empty border lc rgb '#549f' lw 0.1
set object 1079 polygon from \
  -2.94951, 21.4287 to \
  -0.03, 21.4287 to \
  -0.03, 10.6076 to \
  -2.94951, 10.6076 to \
  -2.94951, 21.4287 front fs empty border lc rgb '#549f' lw 0.1
set object 1080 polygon from \
  -2.97749, 21.449 to \
  -0.03, 21.449 to \
  -0.03, 10.618 to \
  -2.97749, 10.618 to \
  -2.97749, 21.449 front fs empty border lc rgb '#549f' lw 0.1
set object 1081 polygon from \
  -3.00428, 21.4694 to \
  -0.03, 21.4694 to \
  -0.03, 10.6283 to \
  -3.00428, 10.6283 to \
  -3.00428, 21.4694 front fs empty border lc rgb '#549f' lw 0.1
set object 1082 polygon from \
  -3.02985, 21.4897 to \
  -0.03, 21.4897 to \
  -0.03, 10.6386 to \
  -3.02985, 10.6386 to \
  -3.02985, 21.4897 front fs empty border lc rgb '#549f' lw 0.1
set object 1083 polygon from \
  -3.05419, 21.5101 to \
  -0.03, 21.5101 to \
  -0.03, 10.649 to \
  -3.05419, 10.649 to \
  -3.05419, 21.5101 front fs empty border lc rgb '#549f' lw 0.1
set object 1084 polygon from \
  -3.07728, 21.5304 to \
  -0.03, 21.5304 to \
  -0.03, 10.6593 to \
  -3.07728, 10.6593 to \
  -3.07728, 21.5304 front fs empty border lc rgb '#549f' lw 0.1
set object 1085 polygon from \
  -3.09911, 21.5508 to \
  -0.03, 21.5508 to \
  -0.03, 10.6697 to \
  -3.09911, 10.6697 to \
  -3.09911, 21.5508 front fs empty border lc rgb '#549f' lw 0.1
set object 1086 polygon from \
  -3.11967, 21.5711 to \
  -0.03, 21.5711 to \
  -0.03, 10.6801 to \
  -3.11967, 10.6801 to \
  -3.11967, 21.5711 front fs empty border lc rgb '#549f' lw 0.1
set object 1087 polygon from \
  -3.13893, 21.5915 to \
  -0.03, 21.5915 to \
  -0.03, 10.6904 to \
  -3.13893, 10.6904 to \
  -3.13893, 21.5915 front fs empty border lc rgb '#549f' lw 0.1
set object 1088 polygon from \
  -3.15689, 21.6118 to \
  -0.03, 21.6118 to \
  -0.03, 10.7008 to \
  -3.15689, 10.7008 to \
  -3.15689, 21.6118 front fs empty border lc rgb '#549f' lw 0.1
set object 1089 polygon from \
  -3.17353, 21.6322 to \
  -0.03, 21.6322 to \
  -0.03, 10.7111 to \
  -3.17353, 10.7111 to \
  -3.17353, 21.6322 front fs empty border lc rgb '#549f' lw 0.1
set object 1090 polygon from \
  -3.18885, 21.6526 to \
  -0.03, 21.6526 to \
  -0.03, 10.7215 to \
  -3.18885, 10.7215 to \
  -3.18885, 21.6526 front fs empty border lc rgb '#549f' lw 0.1
set object 1091 polygon from \
  -3.20283, 21.6729 to \
  -0.03, 21.6729 to \
  -0.03, 10.7318 to \
  -3.20283, 10.7318 to \
  -3.20283, 21.6729 front fs empty border lc rgb '#549f' lw 0.1
set object 1092 polygon from \
  -3.21547, 21.6933 to \
  -0.03, 21.6933 to \
  -0.03, 10.7422 to \
  -3.21547, 10.7422 to \
  -3.21547, 21.6933 front fs empty border lc rgb '#549f' lw 0.1
set object 1093 polygon from \
  -3.22675, 21.7137 to \
  -0.03, 21.7137 to \
  -0.03, 10.7526 to \
  -3.22675, 10.7526 to \
  -3.22675, 21.7137 front fs empty border lc rgb '#549f' lw 0.1
set object 1094 polygon from \
  -3.23667, 21.734 to \
  -0.03, 21.734 to \
  -0.03, 10.7629 to \
  -3.23667, 10.7629 to \
  -3.23667, 21.734 front fs empty border lc rgb '#549f' lw 0.1
set object 1095 polygon from \
  -3.24522, 21.7544 to \
  -0.03, 21.7544 to \
  -0.03, 10.7733 to \
  -3.24522, 10.7733 to \
  -3.24522, 21.7544 front fs empty border lc rgb '#549f' lw 0.1
set object 1096 polygon from \
  -3.25239, 21.7748 to \
  -0.03, 21.7748 to \
  -0.03, 10.7837 to \
  -3.25239, 10.7837 to \
  -3.25239, 21.7748 front fs empty border lc rgb '#549f' lw 0.1
set object 1097 polygon from \
  -3.25819, 21.7951 to \
  -0.03, 21.7951 to \
  -0.03, 10.794 to \
  -3.25819, 10.794 to \
  -3.25819, 21.7951 front fs empty border lc rgb '#549f' lw 0.1
set object 1098 polygon from \
  -3.2626, 21.8155 to \
  -0.03, 21.8155 to \
  -0.03, 10.8044 to \
  -3.2626, 10.8044 to \
  -3.2626, 21.8155 front fs empty border lc rgb '#549f' lw 0.1
set object 1099 polygon from \
  -3.26563, 21.8359 to \
  -0.03, 21.8359 to \
  -0.03, 10.8148 to \
  -3.26563, 10.8148 to \
  -3.26563, 21.8359 front fs empty border lc rgb '#549f' lw 0.1
set object 1100 polygon from \
  -3.26726, 21.8562 to \
  -0.03, 21.8562 to \
  -0.03, 10.8251 to \
  -3.26726, 10.8251 to \
  -3.26726, 21.8562 front fs empty border lc rgb '#549f' lw 0.1
set object 1101 polygon from \
  -3.26751, 21.8766 to \
  -0.03, 21.8766 to \
  -0.03, 10.8355 to \
  -3.26751, 10.8355 to \
  -3.26751, 21.8766 front fs empty border lc rgb '#549f' lw 0.1
set object 1102 polygon from \
  -3.26751, 21.897 to \
  -0.03, 21.897 to \
  -0.03, 10.8459 to \
  -3.26751, 10.8459 to \
  -3.26751, 21.897 front fs empty border lc rgb '#549f' lw 0.1
set object 1103 polygon from \
  -3.26636, 21.9174 to \
  -0.03, 21.9174 to \
  -0.03, 10.8562 to \
  -3.26636, 10.8562 to \
  -3.26636, 21.9174 front fs empty border lc rgb '#549f' lw 0.1
set object 1104 polygon from \
  -3.26382, 21.9378 to \
  -0.03, 21.9378 to \
  -0.03, 10.8666 to \
  -3.26382, 10.8666 to \
  -3.26382, 21.9378 front fs empty border lc rgb '#549f' lw 0.1
set object 1105 polygon from \
  -3.25989, 21.9581 to \
  -0.03, 21.9581 to \
  -0.03, 10.877 to \
  -3.25989, 10.877 to \
  -3.25989, 21.9581 front fs empty border lc rgb '#549f' lw 0.1
set object 1106 polygon from \
  -3.25457, 21.9785 to \
  -0.03, 21.9785 to \
  -0.03, 10.8874 to \
  -3.25457, 10.8874 to \
  -3.25457, 21.9785 front fs empty border lc rgb '#549f' lw 0.1
set object 1107 polygon from \
  -3.24787, 21.9989 to \
  -0.03, 21.9989 to \
  -0.03, 10.8978 to \
  -3.24787, 10.8978 to \
  -3.24787, 21.9989 front fs empty border lc rgb '#549f' lw 0.1
set object 1108 polygon from \
  -3.23979, 22.0193 to \
  -0.03, 22.0193 to \
  -0.03, 10.9081 to \
  -3.23979, 10.9081 to \
  -3.23979, 22.0193 front fs empty border lc rgb '#549f' lw 0.1
set object 1109 polygon from \
  -3.23033, 22.0397 to \
  -0.03, 22.0397 to \
  -0.03, 10.9185 to \
  -3.23033, 10.9185 to \
  -3.23033, 22.0397 front fs empty border lc rgb '#549f' lw 0.1
set object 1110 polygon from \
  -3.2195, 22.0601 to \
  -0.03, 22.0601 to \
  -0.03, 10.9289 to \
  -3.2195, 10.9289 to \
  -3.2195, 22.0601 front fs empty border lc rgb '#549f' lw 0.1
set object 1111 polygon from \
  -3.2073, 22.0805 to \
  -0.03, 22.0805 to \
  -0.03, 10.9393 to \
  -3.2073, 10.9393 to \
  -3.2073, 22.0805 front fs empty border lc rgb '#549f' lw 0.1
set object 1112 polygon from \
  -3.19375, 22.1008 to \
  -0.03, 22.1008 to \
  -0.03, 10.9497 to \
  -3.19375, 10.9497 to \
  -3.19375, 22.1008 front fs empty border lc rgb '#549f' lw 0.1
set object 1113 polygon from \
  -3.17885, 22.1212 to \
  -0.03, 22.1212 to \
  -0.03, 10.9601 to \
  -3.17885, 10.9601 to \
  -3.17885, 22.1212 front fs empty border lc rgb '#549f' lw 0.1
set object 1114 polygon from \
  -3.16261, 22.1416 to \
  -0.03, 22.1416 to \
  -0.03, 10.9704 to \
  -3.16261, 10.9704 to \
  -3.16261, 22.1416 front fs empty border lc rgb '#549f' lw 0.1
set object 1115 polygon from \
  -3.14504, 22.162 to \
  -0.03, 22.162 to \
  -0.03, 10.9808 to \
  -3.14504, 10.9808 to \
  -3.14504, 22.162 front fs empty border lc rgb '#549f' lw 0.1
set object 1116 polygon from \
  -3.12615, 22.1824 to \
  -0.03, 22.1824 to \
  -0.03, 10.9912 to \
  -3.12615, 10.9912 to \
  -3.12615, 22.1824 front fs empty border lc rgb '#549f' lw 0.1
set object 1117 polygon from \
  -3.10595, 22.2028 to \
  -0.03, 22.2028 to \
  -0.03, 11.0016 to \
  -3.10595, 11.0016 to \
  -3.10595, 22.2028 front fs empty border lc rgb '#549f' lw 0.1
set object 1118 polygon from \
  -3.08446, 22.2232 to \
  -0.03, 22.2232 to \
  -0.03, 11.012 to \
  -3.08446, 11.012 to \
  -3.08446, 22.2232 front fs empty border lc rgb '#549f' lw 0.1
set object 1119 polygon from \
  -3.06169, 22.2436 to \
  -0.03, 22.2436 to \
  -0.03, 11.0224 to \
  -3.06169, 11.0224 to \
  -3.06169, 22.2436 front fs empty border lc rgb '#549f' lw 0.1
set object 1120 polygon from \
  -3.03765, 22.264 to \
  -0.03, 22.264 to \
  -0.03, 11.0328 to \
  -3.03765, 11.0328 to \
  -3.03765, 22.264 front fs empty border lc rgb '#549f' lw 0.1
set object 1121 polygon from \
  -3.01236, 22.2844 to \
  -0.03, 22.2844 to \
  -0.03, 11.0432 to \
  -3.01236, 11.0432 to \
  -3.01236, 22.2844 front fs empty border lc rgb '#549f' lw 0.1
set object 1122 polygon from \
  -2.98583, 22.3048 to \
  -0.03, 22.3048 to \
  -0.03, 11.0536 to \
  -2.98583, 11.0536 to \
  -2.98583, 22.3048 front fs empty border lc rgb '#549f' lw 0.1
set object 1123 polygon from \
  -2.95809, 22.3252 to \
  -0.03, 22.3252 to \
  -0.03, 11.064 to \
  -2.95809, 11.064 to \
  -2.95809, 22.3252 front fs empty border lc rgb '#549f' lw 0.1
set object 1124 polygon from \
  -2.92914, 22.3456 to \
  -0.03, 22.3456 to \
  -0.03, 11.0744 to \
  -2.92914, 11.0744 to \
  -2.92914, 22.3456 front fs empty border lc rgb '#549f' lw 0.1
set object 1125 polygon from \
  -2.89901, 22.366 to \
  -0.03, 22.366 to \
  -0.03, 11.0848 to \
  -2.89901, 11.0848 to \
  -2.89901, 22.366 front fs empty border lc rgb '#549f' lw 0.1
set object 1126 polygon from \
  -2.86771, 22.3864 to \
  -0.03, 22.3864 to \
  -0.03, 11.0952 to \
  -2.86771, 11.0952 to \
  -2.86771, 22.3864 front fs empty border lc rgb '#549f' lw 0.1
set object 1127 polygon from \
  -2.83527, 22.4068 to \
  -0.03, 22.4068 to \
  -0.03, 11.1056 to \
  -2.83527, 11.1056 to \
  -2.83527, 22.4068 front fs empty border lc rgb '#549f' lw 0.1
set object 1128 polygon from \
  -2.8017, 22.4272 to \
  -0.03, 22.4272 to \
  -0.03, 11.116 to \
  -2.8017, 11.116 to \
  -2.8017, 22.4272 front fs empty border lc rgb '#549f' lw 0.1
set object 1129 polygon from \
  -2.76703, 22.4477 to \
  -0.03, 22.4477 to \
  -0.03, 11.1264 to \
  -2.76703, 11.1264 to \
  -2.76703, 22.4477 front fs empty border lc rgb '#549f' lw 0.1
set object 1130 polygon from \
  -2.73128, 22.4681 to \
  -0.03, 22.4681 to \
  -0.03, 11.1368 to \
  -2.73128, 11.1368 to \
  -2.73128, 22.4681 front fs empty border lc rgb '#549f' lw 0.1
set object 1131 polygon from \
  -2.69517, 22.4885 to \
  -0.03, 22.4885 to \
  -0.03, 11.1472 to \
  -2.69517, 11.1472 to \
  -2.69517, 22.4885 front fs empty border lc rgb '#549f' lw 0.1
set object 1132 polygon from \
  -2.7063, 22.5089 to \
  -0.03, 22.5089 to \
  -0.03, 11.1576 to \
  -2.7063, 11.1576 to \
  -2.7063, 22.5089 front fs empty border lc rgb '#549f' lw 0.1
set object 1133 polygon from \
  -2.71675, 22.5293 to \
  -0.03, 22.5293 to \
  -0.03, 11.1681 to \
  -2.71675, 11.1681 to \
  -2.71675, 22.5293 front fs empty border lc rgb '#549f' lw 0.1
set object 1134 polygon from \
  -2.72651, 22.5497 to \
  -0.03, 22.5497 to \
  -0.03, 11.1785 to \
  -2.72651, 11.1785 to \
  -2.72651, 22.5497 front fs empty border lc rgb '#549f' lw 0.1
set object 1135 polygon from \
  -2.73559, 22.5701 to \
  -0.03, 22.5701 to \
  -0.03, 11.1889 to \
  -2.73559, 11.1889 to \
  -2.73559, 22.5701 front fs empty border lc rgb '#549f' lw 0.1
set object 1136 polygon from \
  -2.744, 22.5906 to \
  -0.03, 22.5906 to \
  -0.03, 11.1993 to \
  -2.744, 11.1993 to \
  -2.744, 22.5906 front fs empty border lc rgb '#549f' lw 0.1
set object 1137 polygon from \
  -2.75175, 22.611 to \
  -0.03, 22.611 to \
  -0.03, 11.2097 to \
  -2.75175, 11.2097 to \
  -2.75175, 22.611 front fs empty border lc rgb '#549f' lw 0.1
set object 1138 polygon from \
  -2.75884, 22.6314 to \
  -0.03, 22.6314 to \
  -0.03, 11.2201 to \
  -2.75884, 11.2201 to \
  -2.75884, 22.6314 front fs empty border lc rgb '#549f' lw 0.1
set object 1139 polygon from \
  -2.76528, 22.6518 to \
  -0.03, 22.6518 to \
  -0.03, 11.2306 to \
  -2.76528, 11.2306 to \
  -2.76528, 22.6518 front fs empty border lc rgb '#549f' lw 0.1
set object 1140 polygon from \
  -2.77107, 22.6722 to \
  -0.03, 22.6722 to \
  -0.03, 11.241 to \
  -2.77107, 11.241 to \
  -2.77107, 22.6722 front fs empty border lc rgb '#549f' lw 0.1
set object 1141 polygon from \
  -2.77623, 22.6927 to \
  -0.03, 22.6927 to \
  -0.03, 11.2514 to \
  -2.77623, 11.2514 to \
  -2.77623, 22.6927 front fs empty border lc rgb '#549f' lw 0.1
set object 1142 polygon from \
  -2.78076, 22.7131 to \
  -0.03, 22.7131 to \
  -0.03, 11.2618 to \
  -2.78076, 11.2618 to \
  -2.78076, 22.7131 front fs empty border lc rgb '#549f' lw 0.1
set object 1143 polygon from \
  -2.78468, 22.7335 to \
  -0.03, 22.7335 to \
  -0.03, 11.2722 to \
  -2.78468, 11.2722 to \
  -2.78468, 22.7335 front fs empty border lc rgb '#549f' lw 0.1
set object 1144 polygon from \
  -2.78798, 22.754 to \
  -0.03, 22.754 to \
  -0.03, 11.2827 to \
  -2.78798, 11.2827 to \
  -2.78798, 22.754 front fs empty border lc rgb '#549f' lw 0.1
set object 1145 polygon from \
  -2.79068, 22.7744 to \
  -0.03, 22.7744 to \
  -0.03, 11.2931 to \
  -2.79068, 11.2931 to \
  -2.79068, 22.7744 front fs empty border lc rgb '#549f' lw 0.1
set object 1146 polygon from \
  -2.79279, 22.7948 to \
  -0.03, 22.7948 to \
  -0.03, 11.3035 to \
  -2.79279, 11.3035 to \
  -2.79279, 22.7948 front fs empty border lc rgb '#549f' lw 0.1
set object 1147 polygon from \
  -2.79432, 22.8153 to \
  -0.03, 22.8153 to \
  -0.03, 11.314 to \
  -2.79432, 11.314 to \
  -2.79432, 22.8153 front fs empty border lc rgb '#549f' lw 0.1
set object 1148 polygon from \
  -2.79528, 22.8357 to \
  -0.03, 22.8357 to \
  -0.03, 11.3244 to \
  -2.79528, 11.3244 to \
  -2.79528, 22.8357 front fs empty border lc rgb '#549f' lw 0.1
set object 1149 polygon from \
  -2.79567, 22.8561 to \
  -0.03, 22.8561 to \
  -0.03, 11.3348 to \
  -2.79567, 11.3348 to \
  -2.79567, 22.8561 front fs empty border lc rgb '#549f' lw 0.1
set object 1150 polygon from \
  -2.79566, 22.8766 to \
  -0.03, 22.8766 to \
  -0.03, 11.3453 to \
  -2.79566, 11.3453 to \
  -2.79566, 22.8766 front fs empty border lc rgb '#549f' lw 0.1
set object 1151 polygon from \
  -2.7955, 22.897 to \
  -0.03, 22.897 to \
  -0.03, 11.3557 to \
  -2.7955, 11.3557 to \
  -2.7955, 22.897 front fs empty border lc rgb '#549f' lw 0.1
set object 1152 polygon from \
  -2.7948, 22.9174 to \
  -0.03, 22.9174 to \
  -0.03, 11.3661 to \
  -2.7948, 11.3661 to \
  -2.7948, 22.9174 front fs empty border lc rgb '#549f' lw 0.1
set object 1153 polygon from \
  -2.79357, 22.9379 to \
  -0.03, 22.9379 to \
  -0.03, 11.3766 to \
  -2.79357, 11.3766 to \
  -2.79357, 22.9379 front fs empty border lc rgb '#549f' lw 0.1
set object 1154 polygon from \
  -2.79181, 22.9583 to \
  -0.03, 22.9583 to \
  -0.03, 11.387 to \
  -2.79181, 11.387 to \
  -2.79181, 22.9583 front fs empty border lc rgb '#549f' lw 0.1
set object 1155 polygon from \
  -2.78955, 22.9788 to \
  -0.03, 22.9788 to \
  -0.03, 11.3974 to \
  -2.78955, 11.3974 to \
  -2.78955, 22.9788 front fs empty border lc rgb '#549f' lw 0.1
set object 1156 polygon from \
  -2.78679, 22.9992 to \
  -0.03, 22.9992 to \
  -0.03, 11.4079 to \
  -2.78679, 11.4079 to \
  -2.78679, 22.9992 front fs empty border lc rgb '#549f' lw 0.1
set object 1157 polygon from \
  -2.78355, 23.0197 to \
  -0.03, 23.0197 to \
  -0.03, 11.4183 to \
  -2.78355, 11.4183 to \
  -2.78355, 23.0197 front fs empty border lc rgb '#549f' lw 0.1
set object 1158 polygon from \
  -2.8131, 23.0401 to \
  -0.03, 23.0401 to \
  -0.03, 11.4288 to \
  -2.8131, 11.4288 to \
  -2.8131, 23.0401 front fs empty border lc rgb '#549f' lw 0.1
set object 1159 polygon from \
  -2.86217, 23.0606 to \
  -0.03, 23.0606 to \
  -0.03, 11.4392 to \
  -2.86217, 11.4392 to \
  -2.86217, 23.0606 front fs empty border lc rgb '#549f' lw 0.1
set object 1160 polygon from \
  -2.91077, 23.081 to \
  -0.03, 23.081 to \
  -0.03, 11.4497 to \
  -2.91077, 11.4497 to \
  -2.91077, 23.081 front fs empty border lc rgb '#549f' lw 0.1
set object 1161 polygon from \
  -2.95887, 23.1015 to \
  -0.03, 23.1015 to \
  -0.03, 11.4601 to \
  -2.95887, 11.4601 to \
  -2.95887, 23.1015 front fs empty border lc rgb '#549f' lw 0.1
set object 1162 polygon from \
  -3.00646, 23.1219 to \
  -0.03, 23.1219 to \
  -0.03, 11.4705 to \
  -3.00646, 11.4705 to \
  -3.00646, 23.1219 front fs empty border lc rgb '#549f' lw 0.1
set object 1163 polygon from \
  -3.0535, 23.1424 to \
  -0.03, 23.1424 to \
  -0.03, 11.481 to \
  -3.0535, 11.481 to \
  -3.0535, 23.1424 front fs empty border lc rgb '#549f' lw 0.1
set object 1164 polygon from \
  -3.09999, 23.1628 to \
  -0.03, 23.1628 to \
  -0.03, 11.4914 to \
  -3.09999, 11.4914 to \
  -3.09999, 23.1628 front fs empty border lc rgb '#549f' lw 0.1
set object 1165 polygon from \
  -3.1459, 23.1833 to \
  -0.03, 23.1833 to \
  -0.03, 11.5019 to \
  -3.1459, 11.5019 to \
  -3.1459, 23.1833 front fs empty border lc rgb '#549f' lw 0.1
set object 1166 polygon from \
  -3.19121, 23.2037 to \
  -0.03, 23.2037 to \
  -0.03, 11.5124 to \
  -3.19121, 11.5124 to \
  -3.19121, 23.2037 front fs empty border lc rgb '#549f' lw 0.1
set object 1167 polygon from \
  -3.23589, 23.2242 to \
  -0.03, 23.2242 to \
  -0.03, 11.5228 to \
  -3.23589, 11.5228 to \
  -3.23589, 23.2242 front fs empty border lc rgb '#549f' lw 0.1
set object 1168 polygon from \
  -3.27994, 23.2446 to \
  -0.03, 23.2446 to \
  -0.03, 11.5333 to \
  -3.27994, 11.5333 to \
  -3.27994, 23.2446 front fs empty border lc rgb '#549f' lw 0.1
set object 1169 polygon from \
  -3.32332, 23.2651 to \
  -0.03, 23.2651 to \
  -0.03, 11.5437 to \
  -3.32332, 11.5437 to \
  -3.32332, 23.2651 front fs empty border lc rgb '#549f' lw 0.1
set object 1170 polygon from \
  -3.36602, 23.2856 to \
  -0.03, 23.2856 to \
  -0.03, 11.5542 to \
  -3.36602, 11.5542 to \
  -3.36602, 23.2856 front fs empty border lc rgb '#549f' lw 0.1
set object 1171 polygon from \
  -3.40802, 23.306 to \
  -0.03, 23.306 to \
  -0.03, 11.5646 to \
  -3.40802, 11.5646 to \
  -3.40802, 23.306 front fs empty border lc rgb '#549f' lw 0.1
set object 1172 polygon from \
  -3.44931, 23.3265 to \
  -0.03, 23.3265 to \
  -0.03, 11.5751 to \
  -3.44931, 11.5751 to \
  -3.44931, 23.3265 front fs empty border lc rgb '#549f' lw 0.1
set object 1173 polygon from \
  -3.48985, 23.347 to \
  -0.03, 23.347 to \
  -0.03, 11.5856 to \
  -3.48985, 11.5856 to \
  -3.48985, 23.347 front fs empty border lc rgb '#549f' lw 0.1
set object 1174 polygon from \
  -3.52963, 23.3674 to \
  -0.03, 23.3674 to \
  -0.03, 11.596 to \
  -3.52963, 11.596 to \
  -3.52963, 23.3674 front fs empty border lc rgb '#549f' lw 0.1
set object 1175 polygon from \
  -3.56864, 23.3879 to \
  -0.03, 23.3879 to \
  -0.03, 11.6065 to \
  -3.56864, 11.6065 to \
  -3.56864, 23.3879 front fs empty border lc rgb '#549f' lw 0.1
set object 1176 polygon from \
  -3.60686, 23.4084 to \
  -0.03, 23.4084 to \
  -0.03, 11.617 to \
  -3.60686, 11.617 to \
  -3.60686, 23.4084 front fs empty border lc rgb '#549f' lw 0.1
set object 1177 polygon from \
  -3.64426, 23.4288 to \
  -0.03, 23.4288 to \
  -0.03, 11.6274 to \
  -3.64426, 11.6274 to \
  -3.64426, 23.4288 front fs empty border lc rgb '#549f' lw 0.1
set object 1178 polygon from \
  -3.68083, 23.4493 to \
  -0.03, 23.4493 to \
  -0.03, 11.6379 to \
  -3.68083, 11.6379 to \
  -3.68083, 23.4493 front fs empty border lc rgb '#549f' lw 0.1
set object 1179 polygon from \
  -3.71656, 23.4698 to \
  -0.03, 23.4698 to \
  -0.03, 11.6484 to \
  -3.71656, 11.6484 to \
  -3.71656, 23.4698 front fs empty border lc rgb '#549f' lw 0.1
set object 1180 polygon from \
  -3.75142, 23.4902 to \
  -0.03, 23.4902 to \
  -0.03, 11.6588 to \
  -3.75142, 11.6588 to \
  -3.75142, 23.4902 front fs empty border lc rgb '#549f' lw 0.1
set object 1181 polygon from \
  -3.7854, 23.5107 to \
  -0.03, 23.5107 to \
  -0.03, 11.6693 to \
  -3.7854, 11.6693 to \
  -3.7854, 23.5107 front fs empty border lc rgb '#549f' lw 0.1
set object 1182 polygon from \
  -3.81848, 23.5312 to \
  -0.03, 23.5312 to \
  -0.03, 11.6798 to \
  -3.81848, 11.6798 to \
  -3.81848, 23.5312 front fs empty border lc rgb '#549f' lw 0.1
set object 1183 polygon from \
  -3.85066, 23.5517 to \
  -0.03, 23.5517 to \
  -0.03, 11.6902 to \
  -3.85066, 11.6902 to \
  -3.85066, 23.5517 front fs empty border lc rgb '#549f' lw 0.1
set object 1184 polygon from \
  -3.8819, 23.5722 to \
  -0.03, 23.5722 to \
  -0.03, 11.7007 to \
  -3.8819, 11.7007 to \
  -3.8819, 23.5722 front fs empty border lc rgb '#549f' lw 0.1
set object 1185 polygon from \
  -3.9122, 23.5926 to \
  -0.03, 23.5926 to \
  -0.03, 11.7112 to \
  -3.9122, 11.7112 to \
  -3.9122, 23.5926 front fs empty border lc rgb '#549f' lw 0.1
set object 1186 polygon from \
  -3.94155, 23.6131 to \
  -0.03, 23.6131 to \
  -0.03, 11.7217 to \
  -3.94155, 11.7217 to \
  -3.94155, 23.6131 front fs empty border lc rgb '#549f' lw 0.1
set object 1187 polygon from \
  -3.97073, 23.6336 to \
  -0.03, 23.6336 to \
  -0.03, 11.7322 to \
  -3.97073, 11.7322 to \
  -3.97073, 23.6336 front fs empty border lc rgb '#549f' lw 0.1
set object 1188 polygon from \
  -4.00369, 23.6541 to \
  -0.03, 23.6541 to \
  -0.03, 11.7426 to \
  -4.00369, 11.7426 to \
  -4.00369, 23.6541 front fs empty border lc rgb '#549f' lw 0.1
set object 1189 polygon from \
  -4.03562, 23.6746 to \
  -0.03, 23.6746 to \
  -0.03, 11.7531 to \
  -4.03562, 11.7531 to \
  -4.03562, 23.6746 front fs empty border lc rgb '#549f' lw 0.1
set object 1190 polygon from \
  -4.0665, 23.6951 to \
  -0.03, 23.6951 to \
  -0.03, 11.7636 to \
  -4.0665, 11.7636 to \
  -4.0665, 23.6951 front fs empty border lc rgb '#549f' lw 0.1
set object 1191 polygon from \
  -4.09632, 23.7156 to \
  -0.03, 23.7156 to \
  -0.03, 11.7741 to \
  -4.09632, 11.7741 to \
  -4.09632, 23.7156 front fs empty border lc rgb '#549f' lw 0.1
set object 1192 polygon from \
  -4.12507, 23.736 to \
  -0.03, 23.736 to \
  -0.03, 11.7846 to \
  -4.12507, 11.7846 to \
  -4.12507, 23.736 front fs empty border lc rgb '#549f' lw 0.1
set object 1193 polygon from \
  -4.15304, 23.7565 to \
  -0.03, 23.7565 to \
  -0.03, 11.7951 to \
  -4.15304, 11.7951 to \
  -4.15304, 23.7565 front fs empty border lc rgb '#549f' lw 0.1
set object 1194 polygon from \
  -4.18984, 23.777 to \
  -0.03, 23.777 to \
  -0.03, 11.8055 to \
  -4.18984, 11.8055 to \
  -4.18984, 23.777 front fs empty border lc rgb '#549f' lw 0.1
set object 1195 polygon from \
  -4.22563, 23.7975 to \
  -0.03, 23.7975 to \
  -0.03, 11.816 to \
  -4.22563, 11.816 to \
  -4.22563, 23.7975 front fs empty border lc rgb '#549f' lw 0.1
set object 1196 polygon from \
  -4.2604, 23.818 to \
  -0.03, 23.818 to \
  -0.03, 11.8265 to \
  -4.2604, 11.8265 to \
  -4.2604, 23.818 front fs empty border lc rgb '#549f' lw 0.1
set object 1197 polygon from \
  -4.29414, 23.8385 to \
  -0.03, 23.8385 to \
  -0.03, 11.837 to \
  -4.29414, 11.837 to \
  -4.29414, 23.8385 front fs empty border lc rgb '#549f' lw 0.1
set object 1198 polygon from \
  -4.32682, 23.859 to \
  -0.03, 23.859 to \
  -0.03, 11.8475 to \
  -4.32682, 11.8475 to \
  -4.32682, 23.859 front fs empty border lc rgb '#549f' lw 0.1
set object 1199 polygon from \
  -4.35844, 23.8795 to \
  -0.03, 23.8795 to \
  -0.03, 11.858 to \
  -4.35844, 11.858 to \
  -4.35844, 23.8795 front fs empty border lc rgb '#549f' lw 0.1
set object 1200 polygon from \
  -4.38899, 23.9 to \
  -0.03, 23.9 to \
  -0.03, 11.8685 to \
  -4.38899, 11.8685 to \
  -4.38899, 23.9 front fs empty border lc rgb '#549f' lw 0.1
set object 1201 polygon from \
  -4.41846, 23.9205 to \
  -0.03, 23.9205 to \
  -0.03, 11.879 to \
  -4.41846, 11.879 to \
  -4.41846, 23.9205 front fs empty border lc rgb '#549f' lw 0.1
set object 1202 polygon from \
  -4.44683, 23.941 to \
  -0.03, 23.941 to \
  -0.03, 11.8895 to \
  -4.44683, 11.8895 to \
  -4.44683, 23.941 front fs empty border lc rgb '#549f' lw 0.1
set object 1203 polygon from \
  -4.47409, 23.9615 to \
  -0.03, 23.9615 to \
  -0.03, 11.9 to \
  -4.47409, 11.9 to \
  -4.47409, 23.9615 front fs empty border lc rgb '#549f' lw 0.1
set object 1204 polygon from \
  -4.50024, 23.982 to \
  -0.03, 23.982 to \
  -0.03, 11.9105 to \
  -4.50024, 11.9105 to \
  -4.50024, 23.982 front fs empty border lc rgb '#549f' lw 0.1
set object 1205 polygon from \
  -4.52526, 24.0025 to \
  -0.03, 24.0025 to \
  -0.03, 11.921 to \
  -4.52526, 11.921 to \
  -4.52526, 24.0025 front fs empty border lc rgb '#549f' lw 0.1
set object 1206 polygon from \
  -4.54915, 24.023 to \
  -0.03, 24.023 to \
  -0.03, 11.9315 to \
  -4.54915, 11.9315 to \
  -4.54915, 24.023 front fs empty border lc rgb '#549f' lw 0.1
set object 1207 polygon from \
  -4.57189, 24.0435 to \
  -0.03, 24.0435 to \
  -0.03, 11.942 to \
  -4.57189, 11.942 to \
  -4.57189, 24.0435 front fs empty border lc rgb '#549f' lw 0.1
set object 1208 polygon from \
  -4.59347, 24.064 to \
  -0.03, 24.064 to \
  -0.03, 11.9525 to \
  -4.59347, 11.9525 to \
  -4.59347, 24.064 front fs empty border lc rgb '#549f' lw 0.1
set object 1209 polygon from \
  -4.6139, 24.0846 to \
  -0.03, 24.0846 to \
  -0.03, 11.963 to \
  -4.6139, 11.963 to \
  -4.6139, 24.0846 front fs empty border lc rgb '#549f' lw 0.1
set object 1210 polygon from \
  -4.63316, 24.1051 to \
  -0.03, 24.1051 to \
  -0.03, 11.9735 to \
  -4.63316, 11.9735 to \
  -4.63316, 24.1051 front fs empty border lc rgb '#549f' lw 0.1
set object 1211 polygon from \
  -4.65124, 24.1256 to \
  -0.03, 24.1256 to \
  -0.03, 11.984 to \
  -4.65124, 11.984 to \
  -4.65124, 24.1256 front fs empty border lc rgb '#549f' lw 0.1
set object 1212 polygon from \
  -4.66815, 24.1461 to \
  -0.03, 24.1461 to \
  -0.03, 11.9945 to \
  -4.66815, 11.9945 to \
  -4.66815, 24.1461 front fs empty border lc rgb '#549f' lw 0.1
set object 1213 polygon from \
  -4.68387, 24.1666 to \
  -0.03, 24.1666 to \
  -0.03, 12.0051 to \
  -4.68387, 12.0051 to \
  -4.68387, 24.1666 front fs empty border lc rgb '#549f' lw 0.1
set object 1214 polygon from \
  -4.69839, 24.1871 to \
  -0.03, 24.1871 to \
  -0.03, 12.0156 to \
  -4.69839, 12.0156 to \
  -4.69839, 24.1871 front fs empty border lc rgb '#549f' lw 0.1
set object 1215 polygon from \
  -4.71172, 24.2076 to \
  -0.03, 24.2076 to \
  -0.03, 12.0261 to \
  -4.71172, 12.0261 to \
  -4.71172, 24.2076 front fs empty border lc rgb '#549f' lw 0.1
set object 1216 polygon from \
  -4.72385, 24.2282 to \
  -0.03, 24.2282 to \
  -0.03, 12.0366 to \
  -4.72385, 12.0366 to \
  -4.72385, 24.2282 front fs empty border lc rgb '#549f' lw 0.1
set object 1217 polygon from \
  -4.73478, 24.2487 to \
  -0.03, 24.2487 to \
  -0.03, 12.0471 to \
  -4.73478, 12.0471 to \
  -4.73478, 24.2487 front fs empty border lc rgb '#549f' lw 0.1
set object 1218 polygon from \
  -4.7445, 24.2692 to \
  -0.03, 24.2692 to \
  -0.03, 12.0576 to \
  -4.7445, 12.0576 to \
  -4.7445, 24.2692 front fs empty border lc rgb '#549f' lw 0.1
set object 1219 polygon from \
  -4.75301, 24.2897 to \
  -0.03, 24.2897 to \
  -0.03, 12.0682 to \
  -4.75301, 12.0682 to \
  -4.75301, 24.2897 front fs empty border lc rgb '#549f' lw 0.1
set object 1220 polygon from \
  -4.76031, 24.3102 to \
  -0.03, 24.3102 to \
  -0.03, 12.0787 to \
  -4.76031, 12.0787 to \
  -4.76031, 24.3102 front fs empty border lc rgb '#549f' lw 0.1
set object 1221 polygon from \
  -4.7664, 24.3308 to \
  -0.03, 24.3308 to \
  -0.03, 12.0892 to \
  -4.7664, 12.0892 to \
  -4.7664, 24.3308 front fs empty border lc rgb '#549f' lw 0.1
set object 1222 polygon from \
  -4.77127, 24.3513 to \
  -0.03, 24.3513 to \
  -0.03, 12.0997 to \
  -4.77127, 12.0997 to \
  -4.77127, 24.3513 front fs empty border lc rgb '#549f' lw 0.1
set object 1223 polygon from \
  -4.77493, 24.3718 to \
  -0.03, 24.3718 to \
  -0.03, 12.1102 to \
  -4.77493, 12.1102 to \
  -4.77493, 24.3718 front fs empty border lc rgb '#549f' lw 0.1
set object 1224 polygon from \
  -4.77738, 24.3924 to \
  -0.03, 24.3924 to \
  -0.03, 12.1208 to \
  -4.77738, 12.1208 to \
  -4.77738, 24.3924 front fs empty border lc rgb '#549f' lw 0.1
set object 1225 polygon from \
  -4.77861, 24.4129 to \
  -0.03, 24.4129 to \
  -0.03, 12.1313 to \
  -4.77861, 12.1313 to \
  -4.77861, 24.4129 front fs empty border lc rgb '#549f' lw 0.1
set object 1226 polygon from \
  -4.77863, 24.4334 to \
  -0.03, 24.4334 to \
  -0.03, 12.1418 to \
  -4.77863, 12.1418 to \
  -4.77863, 24.4334 front fs empty border lc rgb '#549f' lw 0.1
set object 1227 polygon from \
  -4.77863, 24.454 to \
  -0.03, 24.454 to \
  -0.03, 12.1524 to \
  -4.77863, 12.1524 to \
  -4.77863, 24.454 front fs empty border lc rgb '#549f' lw 0.1
set object 1228 polygon from \
  -4.77744, 24.4745 to \
  -0.03, 24.4745 to \
  -0.03, 12.1629 to \
  -4.77744, 12.1629 to \
  -4.77744, 24.4745 front fs empty border lc rgb '#549f' lw 0.1
set object 1229 polygon from \
  -4.77504, 24.495 to \
  -0.03, 24.495 to \
  -0.03, 12.1734 to \
  -4.77504, 12.1734 to \
  -4.77504, 24.495 front fs empty border lc rgb '#549f' lw 0.1
set object 1230 polygon from \
  -4.77144, 24.5156 to \
  -0.03, 24.5156 to \
  -0.03, 12.184 to \
  -4.77144, 12.184 to \
  -4.77144, 24.5156 front fs empty border lc rgb '#549f' lw 0.1
set object 1231 polygon from \
  -4.76664, 24.5361 to \
  -0.03, 24.5361 to \
  -0.03, 12.1945 to \
  -4.76664, 12.1945 to \
  -4.76664, 24.5361 front fs empty border lc rgb '#549f' lw 0.1
set object 1232 polygon from \
  -4.76064, 24.5566 to \
  -0.03, 24.5566 to \
  -0.03, 12.205 to \
  -4.76064, 12.205 to \
  -4.76064, 24.5566 front fs empty border lc rgb '#549f' lw 0.1
set object 1233 polygon from \
  -4.75344, 24.5772 to \
  -0.03, 24.5772 to \
  -0.03, 12.2156 to \
  -4.75344, 12.2156 to \
  -4.75344, 24.5772 front fs empty border lc rgb '#549f' lw 0.1
set object 1234 polygon from \
  -4.74506, 24.5977 to \
  -0.03, 24.5977 to \
  -0.03, 12.2261 to \
  -4.74506, 12.2261 to \
  -4.74506, 24.5977 front fs empty border lc rgb '#549f' lw 0.1
set object 1235 polygon from \
  -4.7355, 24.6183 to \
  -0.03, 24.6183 to \
  -0.03, 12.2366 to \
  -4.7355, 12.2366 to \
  -4.7355, 24.6183 front fs empty border lc rgb '#549f' lw 0.1
set object 1236 polygon from \
  -4.72475, 24.6388 to \
  -0.03, 24.6388 to \
  -0.03, 12.2472 to \
  -4.72475, 12.2472 to \
  -4.72475, 24.6388 front fs empty border lc rgb '#549f' lw 0.1
set object 1237 polygon from \
  -4.71284, 24.6594 to \
  -0.03, 24.6594 to \
  -0.03, 12.2577 to \
  -4.71284, 12.2577 to \
  -4.71284, 24.6594 front fs empty border lc rgb '#549f' lw 0.1
set object 1238 polygon from \
  -4.69977, 24.6799 to \
  -0.03, 24.6799 to \
  -0.03, 12.2683 to \
  -4.69977, 12.2683 to \
  -4.69977, 24.6799 front fs empty border lc rgb '#549f' lw 0.1
set object 1239 polygon from \
  -4.68553, 24.7005 to \
  -0.03, 24.7005 to \
  -0.03, 12.2788 to \
  -4.68553, 12.2788 to \
  -4.68553, 24.7005 front fs empty border lc rgb '#549f' lw 0.1
set object 1240 polygon from \
  -4.67016, 24.721 to \
  -0.03, 24.721 to \
  -0.03, 12.2894 to \
  -4.67016, 12.2894 to \
  -4.67016, 24.721 front fs empty border lc rgb '#549f' lw 0.1
set object 1241 polygon from \
  -4.65364, 24.7416 to \
  -0.03, 24.7416 to \
  -0.03, 12.2999 to \
  -4.65364, 12.2999 to \
  -4.65364, 24.7416 front fs empty border lc rgb '#549f' lw 0.1
set object 1242 polygon from \
  -4.63599, 24.7621 to \
  -0.03, 24.7621 to \
  -0.03, 12.3104 to \
  -4.63599, 12.3104 to \
  -4.63599, 24.7621 front fs empty border lc rgb '#549f' lw 0.1
set object 1243 polygon from \
  -4.61722, 24.7827 to \
  -0.03, 24.7827 to \
  -0.03, 12.321 to \
  -4.61722, 12.321 to \
  -4.61722, 24.7827 front fs empty border lc rgb '#549f' lw 0.1
set object 1244 polygon from \
  -4.59734, 24.8032 to \
  -0.03, 24.8032 to \
  -0.03, 12.3315 to \
  -4.59734, 12.3315 to \
  -4.59734, 24.8032 front fs empty border lc rgb '#549f' lw 0.1
set object 1245 polygon from \
  -4.57636, 24.8238 to \
  -0.03, 24.8238 to \
  -0.03, 12.3421 to \
  -4.57636, 12.3421 to \
  -4.57636, 24.8238 front fs empty border lc rgb '#549f' lw 0.1
set object 1246 polygon from \
  -4.55429, 24.8443 to \
  -0.03, 24.8443 to \
  -0.03, 12.3527 to \
  -4.55429, 12.3527 to \
  -4.55429, 24.8443 front fs empty border lc rgb '#549f' lw 0.1
set object 1247 polygon from \
  -4.53114, 24.8649 to \
  -0.03, 24.8649 to \
  -0.03, 12.3632 to \
  -4.53114, 12.3632 to \
  -4.53114, 24.8649 front fs empty border lc rgb '#549f' lw 0.1
set object 1248 polygon from \
  -4.50692, 24.8854 to \
  -0.03, 24.8854 to \
  -0.03, 12.3738 to \
  -4.50692, 12.3738 to \
  -4.50692, 24.8854 front fs empty border lc rgb '#549f' lw 0.1
set object 1249 polygon from \
  -4.48165, 24.906 to \
  -0.03, 24.906 to \
  -0.03, 12.3843 to \
  -4.48165, 12.3843 to \
  -4.48165, 24.906 front fs empty border lc rgb '#549f' lw 0.1
set object 1250 polygon from \
  -4.45534, 24.9266 to \
  -0.03, 24.9266 to \
  -0.03, 12.3949 to \
  -4.45534, 12.3949 to \
  -4.45534, 24.9266 front fs empty border lc rgb '#549f' lw 0.1
set object 1251 polygon from \
  -4.428, 24.9471 to \
  -0.03, 24.9471 to \
  -0.03, 12.4054 to \
  -4.428, 12.4054 to \
  -4.428, 24.9471 front fs empty border lc rgb '#549f' lw 0.1
set object 1252 polygon from \
  -4.40162, 24.9677 to \
  -0.03, 24.9677 to \
  -0.03, 12.416 to \
  -4.40162, 12.416 to \
  -4.40162, 24.9677 front fs empty border lc rgb '#549f' lw 0.1
set object 1253 polygon from \
  -4.37629, 24.9883 to \
  -0.03, 24.9883 to \
  -0.03, 12.4266 to \
  -4.37629, 12.4266 to \
  -4.37629, 24.9883 front fs empty border lc rgb '#549f' lw 0.1
set object 1254 polygon from \
  -4.34989, 25.0088 to \
  -0.03, 25.0088 to \
  -0.03, 12.4371 to \
  -4.34989, 12.4371 to \
  -4.34989, 25.0088 front fs empty border lc rgb '#549f' lw 0.1
set object 1255 polygon from \
  -4.32242, 25.0294 to \
  -0.03, 25.0294 to \
  -0.03, 12.4477 to \
  -4.32242, 12.4477 to \
  -4.32242, 25.0294 front fs empty border lc rgb '#549f' lw 0.1
set object 1256 polygon from \
  -4.2939, 25.05 to \
  -0.03, 25.05 to \
  -0.03, 12.4583 to \
  -4.2939, 12.4583 to \
  -4.2939, 25.05 front fs empty border lc rgb '#549f' lw 0.1
set object 1257 polygon from \
  -4.2701, 25.0705 to \
  -0.03, 25.0705 to \
  -0.03, 12.4688 to \
  -4.2701, 12.4688 to \
  -4.2701, 25.0705 front fs empty border lc rgb '#549f' lw 0.1
set object 1258 polygon from \
  -4.2464, 25.0911 to \
  -0.03, 25.0911 to \
  -0.03, 12.4794 to \
  -4.2464, 12.4794 to \
  -4.2464, 25.0911 front fs empty border lc rgb '#549f' lw 0.1
set object 1259 polygon from \
  -4.22172, 25.1117 to \
  -0.03, 25.1117 to \
  -0.03, 12.49 to \
  -4.22172, 12.49 to \
  -4.22172, 25.1117 front fs empty border lc rgb '#549f' lw 0.1
set object 1260 polygon from \
  -4.19607, 25.1322 to \
  -0.03, 25.1322 to \
  -0.03, 12.5005 to \
  -4.19607, 12.5005 to \
  -4.19607, 25.1322 front fs empty border lc rgb '#549f' lw 0.1
set object 1261 polygon from \
  -4.16947, 25.1528 to \
  -0.03, 25.1528 to \
  -0.03, 12.5111 to \
  -4.16947, 12.5111 to \
  -4.16947, 25.1528 front fs empty border lc rgb '#549f' lw 0.1
set object 1262 polygon from \
  -4.14194, 25.1734 to \
  -0.03, 25.1734 to \
  -0.03, 12.5217 to \
  -4.14194, 12.5217 to \
  -4.14194, 25.1734 front fs empty border lc rgb '#549f' lw 0.1
set object 1263 polygon from \
  -4.11348, 25.194 to \
  -0.03, 25.194 to \
  -0.03, 12.5322 to \
  -4.11348, 12.5322 to \
  -4.11348, 25.194 front fs empty border lc rgb '#549f' lw 0.1
set object 1264 polygon from \
  -4.08411, 25.2146 to \
  -0.03, 25.2146 to \
  -0.03, 12.5428 to \
  -4.08411, 12.5428 to \
  -4.08411, 25.2146 front fs empty border lc rgb '#549f' lw 0.1
set object 1265 polygon from \
  -4.05385, 25.2351 to \
  -0.03, 25.2351 to \
  -0.03, 12.5534 to \
  -4.05385, 12.5534 to \
  -4.05385, 25.2351 front fs empty border lc rgb '#549f' lw 0.1
set object 1266 polygon from \
  -4.02271, 25.2557 to \
  -0.03, 25.2557 to \
  -0.03, 12.564 to \
  -4.02271, 12.564 to \
  -4.02271, 25.2557 front fs empty border lc rgb '#549f' lw 0.1
set object 1267 polygon from \
  -3.99072, 25.2763 to \
  -0.03, 25.2763 to \
  -0.03, 12.5746 to \
  -3.99072, 12.5746 to \
  -3.99072, 25.2763 front fs empty border lc rgb '#549f' lw 0.1
set object 1268 polygon from \
  -3.95788, 25.2969 to \
  -0.03, 25.2969 to \
  -0.03, 12.5851 to \
  -3.95788, 12.5851 to \
  -3.95788, 25.2969 front fs empty border lc rgb '#549f' lw 0.1
set object 1269 polygon from \
  -3.92422, 25.3175 to \
  -0.03, 25.3175 to \
  -0.03, 12.5957 to \
  -3.92422, 12.5957 to \
  -3.92422, 25.3175 front fs empty border lc rgb '#549f' lw 0.1
set object 1270 polygon from \
  -3.88975, 25.3381 to \
  -0.03, 25.3381 to \
  -0.03, 12.6063 to \
  -3.88975, 12.6063 to \
  -3.88975, 25.3381 front fs empty border lc rgb '#549f' lw 0.1
set object 1271 polygon from \
  -3.85449, 25.3587 to \
  -0.03, 25.3587 to \
  -0.03, 12.6169 to \
  -3.85449, 12.6169 to \
  -3.85449, 25.3587 front fs empty border lc rgb '#549f' lw 0.1
set object 1272 polygon from \
  -3.81846, 25.3792 to \
  -0.03, 25.3792 to \
  -0.03, 12.6275 to \
  -3.81846, 12.6275 to \
  -3.81846, 25.3792 front fs empty border lc rgb '#549f' lw 0.1
set object 1273 polygon from \
  -3.78167, 25.3998 to \
  -0.03, 25.3998 to \
  -0.03, 12.6381 to \
  -3.78167, 12.6381 to \
  -3.78167, 25.3998 front fs empty border lc rgb '#549f' lw 0.1
set object 1274 polygon from \
  -3.74415, 25.4204 to \
  -0.03, 25.4204 to \
  -0.03, 12.6486 to \
  -3.74415, 12.6486 to \
  -3.74415, 25.4204 front fs empty border lc rgb '#549f' lw 0.1
set object 1275 polygon from \
  -3.7059, 25.441 to \
  -0.03, 25.441 to \
  -0.03, 12.6592 to \
  -3.7059, 12.6592 to \
  -3.7059, 25.441 front fs empty border lc rgb '#549f' lw 0.1
set object 1276 polygon from \
  -3.66696, 25.4616 to \
  -0.03, 25.4616 to \
  -0.03, 12.6698 to \
  -3.66696, 12.6698 to \
  -3.66696, 25.4616 front fs empty border lc rgb '#549f' lw 0.1
set object 1277 polygon from \
  -3.62734, 25.4822 to \
  -0.03, 25.4822 to \
  -0.03, 12.6804 to \
  -3.62734, 12.6804 to \
  -3.62734, 25.4822 front fs empty border lc rgb '#549f' lw 0.1
set object 1278 polygon from \
  -3.58705, 25.5028 to \
  -0.03, 25.5028 to \
  -0.03, 12.691 to \
  -3.58705, 12.691 to \
  -3.58705, 25.5028 front fs empty border lc rgb '#549f' lw 0.1
set object 1279 polygon from \
  -3.54612, 25.5234 to \
  -0.03, 25.5234 to \
  -0.03, 12.7016 to \
  -3.54612, 12.7016 to \
  -3.54612, 25.5234 front fs empty border lc rgb '#549f' lw 0.1
set object 1280 polygon from \
  -3.50457, 25.544 to \
  -0.03, 25.544 to \
  -0.03, 12.7122 to \
  -3.50457, 12.7122 to \
  -3.50457, 25.544 front fs empty border lc rgb '#549f' lw 0.1
set object 1281 polygon from \
  -3.46242, 25.5646 to \
  -0.03, 25.5646 to \
  -0.03, 12.7228 to \
  -3.46242, 12.7228 to \
  -3.46242, 25.5646 front fs empty border lc rgb '#549f' lw 0.1
set object 1282 polygon from \
  -3.41968, 25.5852 to \
  -0.03, 25.5852 to \
  -0.03, 12.7334 to \
  -3.41968, 12.7334 to \
  -3.41968, 25.5852 front fs empty border lc rgb '#549f' lw 0.1
set object 1283 polygon from \
  -3.37638, 25.6058 to \
  -0.03, 25.6058 to \
  -0.03, 12.744 to \
  -3.37638, 12.744 to \
  -3.37638, 25.6058 front fs empty border lc rgb '#549f' lw 0.1
set object 1284 polygon from \
  -3.33253, 25.6264 to \
  -0.03, 25.6264 to \
  -0.03, 12.7546 to \
  -3.33253, 12.7546 to \
  -3.33253, 25.6264 front fs empty border lc rgb '#549f' lw 0.1
set object 1285 polygon from \
  -3.28816, 25.647 to \
  -0.03, 25.647 to \
  -0.03, 12.7652 to \
  -3.28816, 12.7652 to \
  -3.28816, 25.647 front fs empty border lc rgb '#549f' lw 0.1
set object 1286 polygon from \
  -3.24328, 25.6676 to \
  -0.03, 25.6676 to \
  -0.03, 12.7758 to \
  -3.24328, 12.7758 to \
  -3.24328, 25.6676 front fs empty border lc rgb '#549f' lw 0.1
set object 1287 polygon from \
  -3.19792, 25.6882 to \
  -0.03, 25.6882 to \
  -0.03, 12.7864 to \
  -3.19792, 12.7864 to \
  -3.19792, 25.6882 front fs empty border lc rgb '#549f' lw 0.1
set object 1288 polygon from \
  -3.1521, 25.7088 to \
  -0.03, 25.7088 to \
  -0.03, 12.797 to \
  -3.1521, 12.797 to \
  -3.1521, 25.7088 front fs empty border lc rgb '#549f' lw 0.1
set object 1289 polygon from \
  -3.11972, 25.7295 to \
  -0.03, 25.7295 to \
  -0.03, 12.8076 to \
  -3.11972, 12.8076 to \
  -3.11972, 25.7295 front fs empty border lc rgb '#549f' lw 0.1
set object 1290 polygon from \
  -3.11964, 25.7501 to \
  -0.03, 25.7501 to \
  -0.03, 12.8182 to \
  -3.11964, 12.8182 to \
  -3.11964, 25.7501 front fs empty border lc rgb '#549f' lw 0.1
set object 1291 polygon from \
  -3.11885, 25.7707 to \
  -0.03, 25.7707 to \
  -0.03, 12.8288 to \
  -3.11885, 12.8288 to \
  -3.11885, 25.7707 front fs empty border lc rgb '#549f' lw 0.1
set object 1292 polygon from \
  -3.11735, 25.7913 to \
  -0.03, 25.7913 to \
  -0.03, 12.8394 to \
  -3.11735, 12.8394 to \
  -3.11735, 25.7913 front fs empty border lc rgb '#549f' lw 0.1
set object 1293 polygon from \
  -3.11511, 25.8119 to \
  -0.03, 25.8119 to \
  -0.03, 12.8501 to \
  -3.11511, 12.8501 to \
  -3.11511, 25.8119 front fs empty border lc rgb '#549f' lw 0.1
set object 1294 polygon from \
  -3.11214, 25.8325 to \
  -0.03, 25.8325 to \
  -0.03, 12.8607 to \
  -3.11214, 12.8607 to \
  -3.11214, 25.8325 front fs empty border lc rgb '#549f' lw 0.1
set object 1295 polygon from \
  -3.10842, 25.8531 to \
  -0.03, 25.8531 to \
  -0.03, 12.8713 to \
  -3.10842, 12.8713 to \
  -3.10842, 25.8531 front fs empty border lc rgb '#549f' lw 0.1
set object 1296 polygon from \
  -3.10394, 25.8738 to \
  -0.03, 25.8738 to \
  -0.03, 12.8819 to \
  -3.10394, 12.8819 to \
  -3.10394, 25.8738 front fs empty border lc rgb '#549f' lw 0.1
set object 1297 polygon from \
  -3.09869, 25.8944 to \
  -0.03, 25.8944 to \
  -0.03, 12.8925 to \
  -3.09869, 12.8925 to \
  -3.09869, 25.8944 front fs empty border lc rgb '#549f' lw 0.1
set object 1298 polygon from \
  -3.09267, 25.915 to \
  -0.03, 25.915 to \
  -0.03, 12.9031 to \
  -3.09267, 12.9031 to \
  -3.09267, 25.915 front fs empty border lc rgb '#549f' lw 0.1
set object 1299 polygon from \
  -3.08585, 25.9356 to \
  -0.03, 25.9356 to \
  -0.03, 12.9138 to \
  -3.08585, 12.9138 to \
  -3.08585, 25.9356 front fs empty border lc rgb '#549f' lw 0.1
set object 1300 polygon from \
  -3.07824, 25.9562 to \
  -0.03, 25.9562 to \
  -0.03, 12.9244 to \
  -3.07824, 12.9244 to \
  -3.07824, 25.9562 front fs empty border lc rgb '#549f' lw 0.1
set object 1301 polygon from \
  -3.06983, 25.9769 to \
  -0.03, 25.9769 to \
  -0.03, 12.935 to \
  -3.06983, 12.935 to \
  -3.06983, 25.9769 front fs empty border lc rgb '#549f' lw 0.1
set object 1302 polygon from \
  -3.06061, 25.9975 to \
  -0.03, 25.9975 to \
  -0.03, 12.9456 to \
  -3.06061, 12.9456 to \
  -3.06061, 25.9975 front fs empty border lc rgb '#549f' lw 0.1
set object 1303 polygon from \
  -3.05056, 26.0181 to \
  -0.03, 26.0181 to \
  -0.03, 12.9562 to \
  -3.05056, 12.9562 to \
  -3.05056, 26.0181 front fs empty border lc rgb '#549f' lw 0.1
set object 1304 polygon from \
  -3.03969, 26.0388 to \
  -0.03, 26.0388 to \
  -0.03, 12.9669 to \
  -3.03969, 12.9669 to \
  -3.03969, 26.0388 front fs empty border lc rgb '#549f' lw 0.1
set object 1305 polygon from \
  -3.02799, 26.0594 to \
  -0.03, 26.0594 to \
  -0.03, 12.9775 to \
  -3.02799, 12.9775 to \
  -3.02799, 26.0594 front fs empty border lc rgb '#549f' lw 0.1
set object 1306 polygon from \
  -3.01545, 26.08 to \
  -0.03, 26.08 to \
  -0.03, 12.9881 to \
  -3.01545, 12.9881 to \
  -3.01545, 26.08 front fs empty border lc rgb '#549f' lw 0.1
set object 1307 polygon from \
  -3.00207, 26.1007 to \
  -0.03, 26.1007 to \
  -0.03, 12.9988 to \
  -3.00207, 12.9988 to \
  -3.00207, 26.1007 front fs empty border lc rgb '#549f' lw 0.1
set object 1308 polygon from \
  -2.98783, 26.1213 to \
  -0.03, 26.1213 to \
  -0.03, 13.0094 to \
  -2.98783, 13.0094 to \
  -2.98783, 26.1213 front fs empty border lc rgb '#549f' lw 0.1
set object 1309 polygon from \
  -3.00216, 26.1419 to \
  -0.03, 26.1419 to \
  -0.03, 13.02 to \
  -3.00216, 13.02 to \
  -3.00216, 26.1419 front fs empty border lc rgb '#549f' lw 0.1
set object 1310 polygon from \
  -3.0383, 26.1626 to \
  -0.03, 26.1626 to \
  -0.03, 13.0307 to \
  -3.0383, 13.0307 to \
  -3.0383, 26.1626 front fs empty border lc rgb '#549f' lw 0.1
set object 1311 polygon from \
  -3.07333, 26.1832 to \
  -0.03, 26.1832 to \
  -0.03, 13.0413 to \
  -3.07333, 13.0413 to \
  -3.07333, 26.1832 front fs empty border lc rgb '#549f' lw 0.1
set object 1312 polygon from \
  -3.10723, 26.2038 to \
  -0.03, 26.2038 to \
  -0.03, 13.0519 to \
  -3.10723, 13.0519 to \
  -3.10723, 26.2038 front fs empty border lc rgb '#549f' lw 0.1
set object 1313 polygon from \
  -3.13996, 26.2245 to \
  -0.03, 26.2245 to \
  -0.03, 13.0626 to \
  -3.13996, 13.0626 to \
  -3.13996, 26.2245 front fs empty border lc rgb '#549f' lw 0.1
set object 1314 polygon from \
  -3.17152, 26.2451 to \
  -0.03, 26.2451 to \
  -0.03, 13.0732 to \
  -3.17152, 13.0732 to \
  -3.17152, 26.2451 front fs empty border lc rgb '#549f' lw 0.1
set object 1315 polygon from \
  -3.20188, 26.2658 to \
  -0.03, 26.2658 to \
  -0.03, 13.0838 to \
  -3.20188, 13.0838 to \
  -3.20188, 26.2658 front fs empty border lc rgb '#549f' lw 0.1
set object 1316 polygon from \
  -3.23103, 26.2864 to \
  -0.03, 26.2864 to \
  -0.03, 13.0945 to \
  -3.23103, 13.0945 to \
  -3.23103, 26.2864 front fs empty border lc rgb '#549f' lw 0.1
set object 1317 polygon from \
  -3.25895, 26.3071 to \
  -0.03, 26.3071 to \
  -0.03, 13.1051 to \
  -3.25895, 13.1051 to \
  -3.25895, 26.3071 front fs empty border lc rgb '#549f' lw 0.1
set object 1318 polygon from \
  -3.28562, 26.3277 to \
  -0.03, 26.3277 to \
  -0.03, 13.1158 to \
  -3.28562, 13.1158 to \
  -3.28562, 26.3277 front fs empty border lc rgb '#549f' lw 0.1
set object 1319 polygon from \
  -3.31103, 26.3484 to \
  -0.03, 26.3484 to \
  -0.03, 13.1264 to \
  -3.31103, 13.1264 to \
  -3.31103, 26.3484 front fs empty border lc rgb '#549f' lw 0.1
set object 1320 polygon from \
  -3.33517, 26.369 to \
  -0.03, 26.369 to \
  -0.03, 13.1371 to \
  -3.33517, 13.1371 to \
  -3.33517, 26.369 front fs empty border lc rgb '#549f' lw 0.1
set object 1321 polygon from \
  -3.35801, 26.3897 to \
  -0.03, 26.3897 to \
  -0.03, 13.1477 to \
  -3.35801, 13.1477 to \
  -3.35801, 26.3897 front fs empty border lc rgb '#549f' lw 0.1
set object 1322 polygon from \
  -3.37954, 26.4103 to \
  -0.03, 26.4103 to \
  -0.03, 13.1583 to \
  -3.37954, 13.1583 to \
  -3.37954, 26.4103 front fs empty border lc rgb '#549f' lw 0.1
set object 1323 polygon from \
  -3.39976, 26.431 to \
  -0.03, 26.431 to \
  -0.03, 13.169 to \
  -3.39976, 13.169 to \
  -3.39976, 26.431 front fs empty border lc rgb '#549f' lw 0.1
set object 1324 polygon from \
  -3.41866, 26.4516 to \
  -0.03, 26.4516 to \
  -0.03, 13.1796 to \
  -3.41866, 13.1796 to \
  -3.41866, 26.4516 front fs empty border lc rgb '#549f' lw 0.1
set object 1325 polygon from \
  -3.43621, 26.4723 to \
  -0.03, 26.4723 to \
  -0.03, 13.1903 to \
  -3.43621, 13.1903 to \
  -3.43621, 26.4723 front fs empty border lc rgb '#549f' lw 0.1
set object 1326 polygon from \
  -3.45242, 26.4929 to \
  -0.03, 26.4929 to \
  -0.03, 13.201 to \
  -3.45242, 13.201 to \
  -3.45242, 26.4929 front fs empty border lc rgb '#549f' lw 0.1
set object 1327 polygon from \
  -3.46727, 26.5136 to \
  -0.03, 26.5136 to \
  -0.03, 13.2116 to \
  -3.46727, 13.2116 to \
  -3.46727, 26.5136 front fs empty border lc rgb '#549f' lw 0.1
set object 1328 polygon from \
  -3.48075, 26.5342 to \
  -0.03, 26.5342 to \
  -0.03, 13.2223 to \
  -3.48075, 13.2223 to \
  -3.48075, 26.5342 front fs empty border lc rgb '#549f' lw 0.1
set object 1329 polygon from \
  -3.49624, 26.5549 to \
  -0.03, 26.5549 to \
  -0.03, 13.2329 to \
  -3.49624, 13.2329 to \
  -3.49624, 26.5549 front fs empty border lc rgb '#549f' lw 0.1
set object 1330 polygon from \
  -3.51046, 26.5756 to \
  -0.03, 26.5756 to \
  -0.03, 13.2436 to \
  -3.51046, 13.2436 to \
  -3.51046, 26.5756 front fs empty border lc rgb '#549f' lw 0.1
set object 1331 polygon from \
  -3.52333, 26.5962 to \
  -0.03, 26.5962 to \
  -0.03, 13.2542 to \
  -3.52333, 13.2542 to \
  -3.52333, 26.5962 front fs empty border lc rgb '#549f' lw 0.1
set object 1332 polygon from \
  -3.53484, 26.6169 to \
  -0.03, 26.6169 to \
  -0.03, 13.2649 to \
  -3.53484, 13.2649 to \
  -3.53484, 26.6169 front fs empty border lc rgb '#549f' lw 0.1
set object 1333 polygon from \
  -3.54499, 26.6376 to \
  -0.03, 26.6376 to \
  -0.03, 13.2756 to \
  -3.54499, 13.2756 to \
  -3.54499, 26.6376 front fs empty border lc rgb '#549f' lw 0.1
set object 1334 polygon from \
  -3.55377, 26.6582 to \
  -0.03, 26.6582 to \
  -0.03, 13.2862 to \
  -3.55377, 13.2862 to \
  -3.55377, 26.6582 front fs empty border lc rgb '#549f' lw 0.1
set object 1335 polygon from \
  -3.56117, 26.6789 to \
  -0.03, 26.6789 to \
  -0.03, 13.2969 to \
  -3.56117, 13.2969 to \
  -3.56117, 26.6789 front fs empty border lc rgb '#549f' lw 0.1
set object 1336 polygon from \
  -3.5672, 26.6996 to \
  -0.03, 26.6996 to \
  -0.03, 13.3076 to \
  -3.5672, 13.3076 to \
  -3.5672, 26.6996 front fs empty border lc rgb '#549f' lw 0.1
set object 1337 polygon from \
  -3.57184, 26.7202 to \
  -0.03, 26.7202 to \
  -0.03, 13.3182 to \
  -3.57184, 13.3182 to \
  -3.57184, 26.7202 front fs empty border lc rgb '#549f' lw 0.1
set object 1338 polygon from \
  -3.5751, 26.7409 to \
  -0.03, 26.7409 to \
  -0.03, 13.3289 to \
  -3.5751, 13.3289 to \
  -3.5751, 26.7409 front fs empty border lc rgb '#549f' lw 0.1
set object 1339 polygon from \
  -3.57698, 26.7616 to \
  -0.03, 26.7616 to \
  -0.03, 13.3396 to \
  -3.57698, 13.3396 to \
  -3.57698, 26.7616 front fs empty border lc rgb '#549f' lw 0.1
set object 1340 polygon from \
  -3.59419, 26.7822 to \
  -0.03, 26.7822 to \
  -0.03, 13.3502 to \
  -3.59419, 13.3502 to \
  -3.59419, 26.7822 front fs empty border lc rgb '#549f' lw 0.1
set object 1341 polygon from \
  -3.63155, 26.8029 to \
  -0.03, 26.8029 to \
  -0.03, 13.3609 to \
  -3.63155, 13.3609 to \
  -3.63155, 26.8029 front fs empty border lc rgb '#549f' lw 0.1
set object 1342 polygon from \
  -3.66808, 26.8236 to \
  -0.03, 26.8236 to \
  -0.03, 13.3716 to \
  -3.66808, 13.3716 to \
  -3.66808, 26.8236 front fs empty border lc rgb '#549f' lw 0.1
set object 1343 polygon from \
  -3.70376, 26.8443 to \
  -0.03, 26.8443 to \
  -0.03, 13.3822 to \
  -3.70376, 13.3822 to \
  -3.70376, 26.8443 front fs empty border lc rgb '#549f' lw 0.1
set object 1344 polygon from \
  -3.73859, 26.865 to \
  -0.03, 26.865 to \
  -0.03, 13.3929 to \
  -3.73859, 13.3929 to \
  -3.73859, 26.865 front fs empty border lc rgb '#549f' lw 0.1
set object 1345 polygon from \
  -3.77255, 26.8856 to \
  -0.03, 26.8856 to \
  -0.03, 13.4036 to \
  -3.77255, 13.4036 to \
  -3.77255, 26.8856 front fs empty border lc rgb '#549f' lw 0.1
set object 1346 polygon from \
  -3.80565, 26.9063 to \
  -0.03, 26.9063 to \
  -0.03, 13.4143 to \
  -3.80565, 13.4143 to \
  -3.80565, 26.9063 front fs empty border lc rgb '#549f' lw 0.1
set object 1347 polygon from \
  -3.83787, 26.927 to \
  -0.03, 26.927 to \
  -0.03, 13.425 to \
  -3.83787, 13.425 to \
  -3.83787, 26.927 front fs empty border lc rgb '#549f' lw 0.1
set object 1348 polygon from \
  -3.86922, 26.9477 to \
  -0.03, 26.9477 to \
  -0.03, 13.4356 to \
  -3.86922, 13.4356 to \
  -3.86922, 26.9477 front fs empty border lc rgb '#549f' lw 0.1
set object 1349 polygon from \
  -3.89967, 26.9684 to \
  -0.03, 26.9684 to \
  -0.03, 13.4463 to \
  -3.89967, 13.4463 to \
  -3.89967, 26.9684 front fs empty border lc rgb '#549f' lw 0.1
set object 1350 polygon from \
  -3.92925, 26.9891 to \
  -0.03, 26.9891 to \
  -0.03, 13.457 to \
  -3.92925, 13.457 to \
  -3.92925, 26.9891 front fs empty border lc rgb '#549f' lw 0.1
set object 1351 polygon from \
  -3.95792, 27.0098 to \
  -0.03, 27.0098 to \
  -0.03, 13.4677 to \
  -3.95792, 13.4677 to \
  -3.95792, 27.0098 front fs empty border lc rgb '#549f' lw 0.1
set object 1352 polygon from \
  -3.98571, 27.0304 to \
  -0.03, 27.0304 to \
  -0.03, 13.4784 to \
  -3.98571, 13.4784 to \
  -3.98571, 27.0304 front fs empty border lc rgb '#549f' lw 0.1
set object 1353 polygon from \
  -4.01259, 27.0511 to \
  -0.03, 27.0511 to \
  -0.03, 13.4891 to \
  -4.01259, 13.4891 to \
  -4.01259, 27.0511 front fs empty border lc rgb '#549f' lw 0.1
set object 1354 polygon from \
  -4.03858, 27.0718 to \
  -0.03, 27.0718 to \
  -0.03, 13.4997 to \
  -4.03858, 13.4997 to \
  -4.03858, 27.0718 front fs empty border lc rgb '#549f' lw 0.1
set object 1355 polygon from \
  -4.06366, 27.0925 to \
  -0.03, 27.0925 to \
  -0.03, 13.5104 to \
  -4.06366, 13.5104 to \
  -4.06366, 27.0925 front fs empty border lc rgb '#549f' lw 0.1
set object 1356 polygon from \
  -4.08783, 27.1132 to \
  -0.03, 27.1132 to \
  -0.03, 13.5211 to \
  -4.08783, 13.5211 to \
  -4.08783, 27.1132 front fs empty border lc rgb '#549f' lw 0.1
set object 1357 polygon from \
  -4.1111, 27.1339 to \
  -0.03, 27.1339 to \
  -0.03, 13.5318 to \
  -4.1111, 13.5318 to \
  -4.1111, 27.1339 front fs empty border lc rgb '#549f' lw 0.1
set object 1358 polygon from \
  -4.13347, 27.1546 to \
  -0.03, 27.1546 to \
  -0.03, 13.5425 to \
  -4.13347, 13.5425 to \
  -4.13347, 27.1546 front fs empty border lc rgb '#549f' lw 0.1
set object 1359 polygon from \
  -4.15492, 27.1753 to \
  -0.03, 27.1753 to \
  -0.03, 13.5532 to \
  -4.15492, 13.5532 to \
  -4.15492, 27.1753 front fs empty border lc rgb '#549f' lw 0.1
set object 1360 polygon from \
  -4.17547, 27.196 to \
  -0.03, 27.196 to \
  -0.03, 13.5639 to \
  -4.17547, 13.5639 to \
  -4.17547, 27.196 front fs empty border lc rgb '#549f' lw 0.1
set object 1361 polygon from \
  -4.19511, 27.2167 to \
  -0.03, 27.2167 to \
  -0.03, 13.5746 to \
  -4.19511, 13.5746 to \
  -4.19511, 27.2167 front fs empty border lc rgb '#549f' lw 0.1
set object 1362 polygon from \
  -4.21385, 27.2374 to \
  -0.03, 27.2374 to \
  -0.03, 13.5853 to \
  -4.21385, 13.5853 to \
  -4.21385, 27.2374 front fs empty border lc rgb '#549f' lw 0.1
set object 1363 polygon from \
  -4.23168, 27.2581 to \
  -0.03, 27.2581 to \
  -0.03, 13.596 to \
  -4.23168, 13.596 to \
  -4.23168, 27.2581 front fs empty border lc rgb '#549f' lw 0.1
set object 1364 polygon from \
  -4.24862, 27.2788 to \
  -0.03, 27.2788 to \
  -0.03, 13.6067 to \
  -4.24862, 13.6067 to \
  -4.24862, 27.2788 front fs empty border lc rgb '#549f' lw 0.1
set object 1365 polygon from \
  -4.26465, 27.2995 to \
  -0.03, 27.2995 to \
  -0.03, 13.6174 to \
  -4.26465, 13.6174 to \
  -4.26465, 27.2995 front fs empty border lc rgb '#549f' lw 0.1
set object 1366 polygon from \
  -4.27978, 27.3202 to \
  -0.03, 27.3202 to \
  -0.03, 13.6281 to \
  -4.27978, 13.6281 to \
  -4.27978, 27.3202 front fs empty border lc rgb '#549f' lw 0.1
set object 1367 polygon from \
  -4.29402, 27.3409 to \
  -0.03, 27.3409 to \
  -0.03, 13.6388 to \
  -4.29402, 13.6388 to \
  -4.29402, 27.3409 front fs empty border lc rgb '#549f' lw 0.1
set object 1368 polygon from \
  -4.30737, 27.3616 to \
  -0.03, 27.3616 to \
  -0.03, 13.6495 to \
  -4.30737, 13.6495 to \
  -4.30737, 27.3616 front fs empty border lc rgb '#549f' lw 0.1
set object 1369 polygon from \
  -4.31983, 27.3824 to \
  -0.03, 27.3824 to \
  -0.03, 13.6602 to \
  -4.31983, 13.6602 to \
  -4.31983, 27.3824 front fs empty border lc rgb '#549f' lw 0.1
set object 1370 polygon from \
  -4.33141, 27.4031 to \
  -0.03, 27.4031 to \
  -0.03, 13.6709 to \
  -4.33141, 13.6709 to \
  -4.33141, 27.4031 front fs empty border lc rgb '#549f' lw 0.1
set object 1371 polygon from \
  -4.34212, 27.4238 to \
  -0.03, 27.4238 to \
  -0.03, 13.6816 to \
  -4.34212, 13.6816 to \
  -4.34212, 27.4238 front fs empty border lc rgb '#549f' lw 0.1
set object 1372 polygon from \
  -4.35195, 27.4445 to \
  -0.03, 27.4445 to \
  -0.03, 13.6923 to \
  -4.35195, 13.6923 to \
  -4.35195, 27.4445 front fs empty border lc rgb '#549f' lw 0.1
set object 1373 polygon from \
  -4.36091, 27.4652 to \
  -0.03, 27.4652 to \
  -0.03, 13.7031 to \
  -4.36091, 13.7031 to \
  -4.36091, 27.4652 front fs empty border lc rgb '#549f' lw 0.1
set object 1374 polygon from \
  -4.36901, 27.4859 to \
  -0.03, 27.4859 to \
  -0.03, 13.7138 to \
  -4.36901, 13.7138 to \
  -4.36901, 27.4859 front fs empty border lc rgb '#549f' lw 0.1
set object 1375 polygon from \
  -4.37625, 27.5066 to \
  -0.03, 27.5066 to \
  -0.03, 13.7245 to \
  -4.37625, 13.7245 to \
  -4.37625, 27.5066 front fs empty border lc rgb '#549f' lw 0.1
set object 1376 polygon from \
  -4.38265, 27.5274 to \
  -0.03, 27.5274 to \
  -0.03, 13.7352 to \
  -4.38265, 13.7352 to \
  -4.38265, 27.5274 front fs empty border lc rgb '#549f' lw 0.1
set object 1377 polygon from \
  -4.3882, 27.5481 to \
  -0.03, 27.5481 to \
  -0.03, 13.7459 to \
  -4.3882, 13.7459 to \
  -4.3882, 27.5481 front fs empty border lc rgb '#549f' lw 0.1
set object 1378 polygon from \
  -4.39291, 27.5688 to \
  -0.03, 27.5688 to \
  -0.03, 13.7566 to \
  -4.39291, 13.7566 to \
  -4.39291, 27.5688 front fs empty border lc rgb '#549f' lw 0.1
set object 1379 polygon from \
  -4.3968, 27.5895 to \
  -0.03, 27.5895 to \
  -0.03, 13.7674 to \
  -4.3968, 13.7674 to \
  -4.3968, 27.5895 front fs empty border lc rgb '#549f' lw 0.1
set object 1380 polygon from \
  -4.39987, 27.6102 to \
  -0.03, 27.6102 to \
  -0.03, 13.7781 to \
  -4.39987, 13.7781 to \
  -4.39987, 27.6102 front fs empty border lc rgb '#549f' lw 0.1
set object 1381 polygon from \
  -4.40213, 27.631 to \
  -0.03, 27.631 to \
  -0.03, 13.7888 to \
  -4.40213, 13.7888 to \
  -4.40213, 27.631 front fs empty border lc rgb '#549f' lw 0.1
set object 1382 polygon from \
  -4.40358, 27.6517 to \
  -0.03, 27.6517 to \
  -0.03, 13.7995 to \
  -4.40358, 13.7995 to \
  -4.40358, 27.6517 front fs empty border lc rgb '#549f' lw 0.1
set object 1383 polygon from \
  -4.40423, 27.6724 to \
  -0.03, 27.6724 to \
  -0.03, 13.8102 to \
  -4.40423, 13.8102 to \
  -4.40423, 27.6724 front fs empty border lc rgb '#549f' lw 0.1
set object 1384 polygon from \
  -4.40423, 27.6932 to \
  -0.03, 27.6932 to \
  -0.03, 13.821 to \
  -4.40423, 13.821 to \
  -4.40423, 27.6932 front fs empty border lc rgb '#549f' lw 0.1
set object 1385 polygon from \
  -4.4041, 27.7139 to \
  -0.03, 27.7139 to \
  -0.03, 13.8317 to \
  -4.4041, 13.8317 to \
  -4.4041, 27.7139 front fs empty border lc rgb '#549f' lw 0.1
set object 1386 polygon from \
  -4.40319, 27.7346 to \
  -0.03, 27.7346 to \
  -0.03, 13.8424 to \
  -4.40319, 13.8424 to \
  -4.40319, 27.7346 front fs empty border lc rgb '#549f' lw 0.1
set object 1387 polygon from \
  -4.40152, 27.7554 to \
  -0.03, 27.7554 to \
  -0.03, 13.8532 to \
  -4.40152, 13.8532 to \
  -4.40152, 27.7554 front fs empty border lc rgb '#549f' lw 0.1
set object 1388 polygon from \
  -4.39909, 27.7761 to \
  -0.03, 27.7761 to \
  -0.03, 13.8639 to \
  -4.39909, 13.8639 to \
  -4.39909, 27.7761 front fs empty border lc rgb '#549f' lw 0.1
set object 1389 polygon from \
  -4.39591, 27.7968 to \
  -0.03, 27.7968 to \
  -0.03, 13.8746 to \
  -4.39591, 13.8746 to \
  -4.39591, 27.7968 front fs empty border lc rgb '#549f' lw 0.1
set object 1390 polygon from \
  -4.39199, 27.8176 to \
  -0.03, 27.8176 to \
  -0.03, 13.8854 to \
  -4.39199, 13.8854 to \
  -4.39199, 27.8176 front fs empty border lc rgb '#549f' lw 0.1
set object 1391 polygon from \
  -4.38734, 27.8383 to \
  -0.03, 27.8383 to \
  -0.03, 13.8961 to \
  -4.38734, 13.8961 to \
  -4.38734, 27.8383 front fs empty border lc rgb '#549f' lw 0.1
set object 1392 polygon from \
  -4.38198, 27.859 to \
  -0.03, 27.859 to \
  -0.03, 13.9068 to \
  -4.38198, 13.9068 to \
  -4.38198, 27.859 front fs empty border lc rgb '#549f' lw 0.1
set object 1393 polygon from \
  -4.37591, 27.8798 to \
  -0.03, 27.8798 to \
  -0.03, 13.9176 to \
  -4.37591, 13.9176 to \
  -4.37591, 27.8798 front fs empty border lc rgb '#549f' lw 0.1
set object 1394 polygon from \
  -4.36915, 27.9005 to \
  -0.03, 27.9005 to \
  -0.03, 13.9283 to \
  -4.36915, 13.9283 to \
  -4.36915, 27.9005 front fs empty border lc rgb '#549f' lw 0.1
set object 1395 polygon from \
  -4.36171, 27.9213 to \
  -0.03, 27.9213 to \
  -0.03, 13.939 to \
  -4.36171, 13.939 to \
  -4.36171, 27.9213 front fs empty border lc rgb '#549f' lw 0.1
set object 1396 polygon from \
  -4.35359, 27.942 to \
  -0.03, 27.942 to \
  -0.03, 13.9498 to \
  -4.35359, 13.9498 to \
  -4.35359, 27.942 front fs empty border lc rgb '#549f' lw 0.1
set object 1397 polygon from \
  -4.34481, 27.9628 to \
  -0.03, 27.9628 to \
  -0.03, 13.9605 to \
  -4.34481, 13.9605 to \
  -4.34481, 27.9628 front fs empty border lc rgb '#549f' lw 0.1
set object 1398 polygon from \
  -4.36708, 27.9835 to \
  -0.03, 27.9835 to \
  -0.03, 13.9713 to \
  -4.36708, 13.9713 to \
  -4.36708, 27.9835 front fs empty border lc rgb '#549f' lw 0.1
set object 1399 polygon from \
  -4.39678, 28.0043 to \
  -0.03, 28.0043 to \
  -0.03, 13.982 to \
  -4.39678, 13.982 to \
  -4.39678, 28.0043 front fs empty border lc rgb '#549f' lw 0.1
set object 1400 polygon from \
  -4.42579, 28.025 to \
  -0.03, 28.025 to \
  -0.03, 13.9928 to \
  -4.42579, 13.9928 to \
  -4.42579, 28.025 front fs empty border lc rgb '#549f' lw 0.1
set object 1401 polygon from \
  -4.4541, 28.0458 to \
  -0.03, 28.0458 to \
  -0.03, 14.0035 to \
  -4.4541, 14.0035 to \
  -4.4541, 28.0458 front fs empty border lc rgb '#549f' lw 0.1
set object 1402 polygon from \
  -4.48168, 28.0665 to \
  -0.03, 28.0665 to \
  -0.03, 14.0142 to \
  -4.48168, 14.0142 to \
  -4.48168, 28.0665 front fs empty border lc rgb '#549f' lw 0.1
set object 1403 polygon from \
  -4.50851, 28.0873 to \
  -0.03, 28.0873 to \
  -0.03, 14.025 to \
  -4.50851, 14.025 to \
  -4.50851, 28.0873 front fs empty border lc rgb '#549f' lw 0.1
set object 1404 polygon from \
  -4.53458, 28.108 to \
  -0.03, 28.108 to \
  -0.03, 14.0357 to \
  -4.53458, 14.0357 to \
  -4.53458, 28.108 front fs empty border lc rgb '#549f' lw 0.1
set object 1405 polygon from \
  -4.55988, 28.1288 to \
  -0.03, 28.1288 to \
  -0.03, 14.0465 to \
  -4.55988, 14.0465 to \
  -4.55988, 28.1288 front fs empty border lc rgb '#549f' lw 0.1
set object 1406 polygon from \
  -4.58437, 28.1495 to \
  -0.03, 28.1495 to \
  -0.03, 14.0573 to \
  -4.58437, 14.0573 to \
  -4.58437, 28.1495 front fs empty border lc rgb '#549f' lw 0.1
set object 1407 polygon from \
  -4.60806, 28.1703 to \
  -0.03, 28.1703 to \
  -0.03, 14.068 to \
  -4.60806, 14.068 to \
  -4.60806, 28.1703 front fs empty border lc rgb '#549f' lw 0.1
set object 1408 polygon from \
  -4.63091, 28.191 to \
  -0.03, 28.191 to \
  -0.03, 14.0788 to \
  -4.63091, 14.0788 to \
  -4.63091, 28.191 front fs empty border lc rgb '#549f' lw 0.1
set object 1409 polygon from \
  -4.65292, 28.2118 to \
  -0.03, 28.2118 to \
  -0.03, 14.0895 to \
  -4.65292, 14.0895 to \
  -4.65292, 28.2118 front fs empty border lc rgb '#549f' lw 0.1
set object 1410 polygon from \
  -4.67407, 28.2326 to \
  -0.03, 28.2326 to \
  -0.03, 14.1003 to \
  -4.67407, 14.1003 to \
  -4.67407, 28.2326 front fs empty border lc rgb '#549f' lw 0.1
set object 1411 polygon from \
  -4.69434, 28.2533 to \
  -0.03, 28.2533 to \
  -0.03, 14.111 to \
  -4.69434, 14.111 to \
  -4.69434, 28.2533 front fs empty border lc rgb '#549f' lw 0.1
set object 1412 polygon from \
  -4.71371, 28.2741 to \
  -0.03, 28.2741 to \
  -0.03, 14.1218 to \
  -4.71371, 14.1218 to \
  -4.71371, 28.2741 front fs empty border lc rgb '#549f' lw 0.1
set object 1413 polygon from \
  -4.73219, 28.2949 to \
  -0.03, 28.2949 to \
  -0.03, 14.1326 to \
  -4.73219, 14.1326 to \
  -4.73219, 28.2949 front fs empty border lc rgb '#549f' lw 0.1
set object 1414 polygon from \
  -4.74974, 28.3156 to \
  -0.03, 28.3156 to \
  -0.03, 14.1433 to \
  -4.74974, 14.1433 to \
  -4.74974, 28.3156 front fs empty border lc rgb '#549f' lw 0.1
set object 1415 polygon from \
  -4.76635, 28.3364 to \
  -0.03, 28.3364 to \
  -0.03, 14.1541 to \
  -4.76635, 14.1541 to \
  -4.76635, 28.3364 front fs empty border lc rgb '#549f' lw 0.1
set object 1416 polygon from \
  -4.78202, 28.3572 to \
  -0.03, 28.3572 to \
  -0.03, 14.1649 to \
  -4.78202, 14.1649 to \
  -4.78202, 28.3572 front fs empty border lc rgb '#549f' lw 0.1
set object 1417 polygon from \
  -4.79673, 28.3779 to \
  -0.03, 28.3779 to \
  -0.03, 14.1756 to \
  -4.79673, 14.1756 to \
  -4.79673, 28.3779 front fs empty border lc rgb '#549f' lw 0.1
set object 1418 polygon from \
  -4.81046, 28.3987 to \
  -0.03, 28.3987 to \
  -0.03, 14.1864 to \
  -4.81046, 14.1864 to \
  -4.81046, 28.3987 front fs empty border lc rgb '#549f' lw 0.1
set object 1419 polygon from \
  -4.82321, 28.4195 to \
  -0.03, 28.4195 to \
  -0.03, 14.1972 to \
  -4.82321, 14.1972 to \
  -4.82321, 28.4195 front fs empty border lc rgb '#549f' lw 0.1
set object 1420 polygon from \
  -4.83495, 28.4402 to \
  -0.03, 28.4402 to \
  -0.03, 14.2079 to \
  -4.83495, 14.2079 to \
  -4.83495, 28.4402 front fs empty border lc rgb '#549f' lw 0.1
set object 1421 polygon from \
  -4.84569, 28.461 to \
  -0.03, 28.461 to \
  -0.03, 14.2187 to \
  -4.84569, 14.2187 to \
  -4.84569, 28.461 front fs empty border lc rgb '#549f' lw 0.1
set object 1422 polygon from \
  -4.8554, 28.4818 to \
  -0.03, 28.4818 to \
  -0.03, 14.2295 to \
  -4.8554, 14.2295 to \
  -4.8554, 28.4818 front fs empty border lc rgb '#549f' lw 0.1
set object 1423 polygon from \
  -4.86409, 28.5026 to \
  -0.03, 28.5026 to \
  -0.03, 14.2402 to \
  -4.86409, 14.2402 to \
  -4.86409, 28.5026 front fs empty border lc rgb '#549f' lw 0.1
set object 1424 polygon from \
  -4.87173, 28.5234 to \
  -0.03, 28.5234 to \
  -0.03, 14.251 to \
  -4.87173, 14.251 to \
  -4.87173, 28.5234 front fs empty border lc rgb '#549f' lw 0.1
set object 1425 polygon from \
  -4.87832, 28.5441 to \
  -0.03, 28.5441 to \
  -0.03, 14.2618 to \
  -4.87832, 14.2618 to \
  -4.87832, 28.5441 front fs empty border lc rgb '#549f' lw 0.1
set object 1426 polygon from \
  -4.88385, 28.5649 to \
  -0.03, 28.5649 to \
  -0.03, 14.2726 to \
  -4.88385, 14.2726 to \
  -4.88385, 28.5649 front fs empty border lc rgb '#549f' lw 0.1
set object 1427 polygon from \
  -4.88831, 28.5857 to \
  -0.03, 28.5857 to \
  -0.03, 14.2834 to \
  -4.88831, 14.2834 to \
  -4.88831, 28.5857 front fs empty border lc rgb '#549f' lw 0.1
set object 1428 polygon from \
  -4.8917, 28.6065 to \
  -0.03, 28.6065 to \
  -0.03, 14.2941 to \
  -4.8917, 14.2941 to \
  -4.8917, 28.6065 front fs empty border lc rgb '#549f' lw 0.1
set object 1429 polygon from \
  -4.89399, 28.6273 to \
  -0.03, 28.6273 to \
  -0.03, 14.3049 to \
  -4.89399, 14.3049 to \
  -4.89399, 28.6273 front fs empty border lc rgb '#549f' lw 0.1
set object 1430 polygon from \
  -4.8952, 28.6481 to \
  -0.03, 28.6481 to \
  -0.03, 14.3157 to \
  -4.8952, 14.3157 to \
  -4.8952, 28.6481 front fs empty border lc rgb '#549f' lw 0.1
set object 1431 polygon from \
  -4.89531, 28.6689 to \
  -0.03, 28.6689 to \
  -0.03, 14.3265 to \
  -4.89531, 14.3265 to \
  -4.89531, 28.6689 front fs empty border lc rgb '#549f' lw 0.1
set object 1432 polygon from \
  -4.89531, 28.6896 to \
  -0.03, 28.6896 to \
  -0.03, 14.3373 to \
  -4.89531, 14.3373 to \
  -4.89531, 28.6896 front fs empty border lc rgb '#549f' lw 0.1
set object 1433 polygon from \
  -4.89431, 28.7104 to \
  -0.03, 28.7104 to \
  -0.03, 14.3481 to \
  -4.89431, 14.3481 to \
  -4.89431, 28.7104 front fs empty border lc rgb '#549f' lw 0.1
set object 1434 polygon from \
  -4.89221, 28.7312 to \
  -0.03, 28.7312 to \
  -0.03, 14.3588 to \
  -4.89221, 14.3588 to \
  -4.89221, 28.7312 front fs empty border lc rgb '#549f' lw 0.1
set object 1435 polygon from \
  -4.88898, 28.752 to \
  -0.03, 28.752 to \
  -0.03, 14.3696 to \
  -4.88898, 14.3696 to \
  -4.88898, 28.752 front fs empty border lc rgb '#549f' lw 0.1
set object 1436 polygon from \
  -4.88464, 28.7728 to \
  -0.03, 28.7728 to \
  -0.03, 14.3804 to \
  -4.88464, 14.3804 to \
  -4.88464, 28.7728 front fs empty border lc rgb '#549f' lw 0.1
set object 1437 polygon from \
  -4.88795, 28.7936 to \
  -0.03, 28.7936 to \
  -0.03, 14.3912 to \
  -4.88795, 14.3912 to \
  -4.88795, 28.7936 front fs empty border lc rgb '#549f' lw 0.1
set object 1438 polygon from \
  -4.89238, 28.8144 to \
  -0.03, 28.8144 to \
  -0.03, 14.402 to \
  -4.89238, 14.402 to \
  -4.89238, 28.8144 front fs empty border lc rgb '#549f' lw 0.1
set object 1439 polygon from \
  -4.8957, 28.8352 to \
  -0.03, 28.8352 to \
  -0.03, 14.4128 to \
  -4.8957, 14.4128 to \
  -4.8957, 28.8352 front fs empty border lc rgb '#549f' lw 0.1
set object 1440 polygon from \
  -4.89792, 28.856 to \
  -0.03, 28.856 to \
  -0.03, 14.4236 to \
  -4.89792, 14.4236 to \
  -4.89792, 28.856 front fs empty border lc rgb '#549f' lw 0.1
set object 1441 polygon from \
  -4.89931, 28.8768 to \
  -0.03, 28.8768 to \
  -0.03, 14.4344 to \
  -4.89931, 14.4344 to \
  -4.89931, 28.8768 front fs empty border lc rgb '#549f' lw 0.1
set object 1442 polygon from \
  -4.9078, 28.8976 to \
  -0.03, 28.8976 to \
  -0.03, 14.4452 to \
  -4.9078, 14.4452 to \
  -4.9078, 28.8976 front fs empty border lc rgb '#549f' lw 0.1
set object 1443 polygon from \
  -4.91514, 28.9184 to \
  -0.03, 28.9184 to \
  -0.03, 14.456 to \
  -4.91514, 14.456 to \
  -4.91514, 28.9184 front fs empty border lc rgb '#549f' lw 0.1
set object 1444 polygon from \
  -4.92132, 28.9392 to \
  -0.03, 28.9392 to \
  -0.03, 14.4668 to \
  -4.92132, 14.4668 to \
  -4.92132, 28.9392 front fs empty border lc rgb '#549f' lw 0.1
set object 1445 polygon from \
  -4.92633, 28.96 to \
  -0.03, 28.96 to \
  -0.03, 14.4776 to \
  -4.92633, 14.4776 to \
  -4.92633, 28.96 front fs empty border lc rgb '#549f' lw 0.1
set object 1446 polygon from \
  -4.93017, 28.9808 to \
  -0.03, 28.9808 to \
  -0.03, 14.4884 to \
  -4.93017, 14.4884 to \
  -4.93017, 28.9808 front fs empty border lc rgb '#549f' lw 0.1
set object 1447 polygon from \
  -4.93284, 29.0016 to \
  -0.03, 29.0016 to \
  -0.03, 14.4992 to \
  -4.93284, 14.4992 to \
  -4.93284, 29.0016 front fs empty border lc rgb '#549f' lw 0.1
set object 1448 polygon from \
  -4.93433, 29.0224 to \
  -0.03, 29.0224 to \
  -0.03, 14.51 to \
  -4.93433, 14.51 to \
  -4.93433, 29.0224 front fs empty border lc rgb '#549f' lw 0.1
set object 1449 polygon from \
  -4.93465, 29.0433 to \
  -0.03, 29.0433 to \
  -0.03, 14.5208 to \
  -4.93465, 14.5208 to \
  -4.93465, 29.0433 front fs empty border lc rgb '#549f' lw 0.1
set object 1450 polygon from \
  -4.93465, 29.0641 to \
  -0.03, 29.0641 to \
  -0.03, 14.5316 to \
  -4.93465, 14.5316 to \
  -4.93465, 29.0641 front fs empty border lc rgb '#549f' lw 0.1
set object 1451 polygon from \
  -4.93379, 29.0849 to \
  -0.03, 29.0849 to \
  -0.03, 14.5424 to \
  -4.93379, 14.5424 to \
  -4.93379, 29.0849 front fs empty border lc rgb '#549f' lw 0.1
set object 1452 polygon from \
  -4.93175, 29.1057 to \
  -0.03, 29.1057 to \
  -0.03, 14.5532 to \
  -4.93175, 14.5532 to \
  -4.93175, 29.1057 front fs empty border lc rgb '#549f' lw 0.1
set object 1453 polygon from \
  -4.92853, 29.1265 to \
  -0.03, 29.1265 to \
  -0.03, 14.5641 to \
  -4.92853, 14.5641 to \
  -4.92853, 29.1265 front fs empty border lc rgb '#549f' lw 0.1
set object 1454 polygon from \
  -4.92413, 29.1473 to \
  -0.03, 29.1473 to \
  -0.03, 14.5749 to \
  -4.92413, 14.5749 to \
  -4.92413, 29.1473 front fs empty border lc rgb '#549f' lw 0.1
set object 1455 polygon from \
  -4.91856, 29.1681 to \
  -0.03, 29.1681 to \
  -0.03, 14.5857 to \
  -4.91856, 14.5857 to \
  -4.91856, 29.1681 front fs empty border lc rgb '#549f' lw 0.1
set object 1456 polygon from \
  -4.91182, 29.189 to \
  -0.03, 29.189 to \
  -0.03, 14.5965 to \
  -4.91182, 14.5965 to \
  -4.91182, 29.189 front fs empty border lc rgb '#549f' lw 0.1
set object 1457 polygon from \
  -4.9039, 29.2098 to \
  -0.03, 29.2098 to \
  -0.03, 14.6073 to \
  -4.9039, 14.6073 to \
  -4.9039, 29.2098 front fs empty border lc rgb '#549f' lw 0.1
set object 1458 polygon from \
  -4.89481, 29.2306 to \
  -0.03, 29.2306 to \
  -0.03, 14.6181 to \
  -4.89481, 14.6181 to \
  -4.89481, 29.2306 front fs empty border lc rgb '#549f' lw 0.1
set object 1459 polygon from \
  -4.88455, 29.2514 to \
  -0.03, 29.2514 to \
  -0.03, 14.629 to \
  -4.88455, 14.629 to \
  -4.88455, 29.2514 front fs empty border lc rgb '#549f' lw 0.1
set object 1460 polygon from \
  -4.87314, 29.2722 to \
  -0.03, 29.2722 to \
  -0.03, 14.6398 to \
  -4.87314, 14.6398 to \
  -4.87314, 29.2722 front fs empty border lc rgb '#549f' lw 0.1
set object 1461 polygon from \
  -4.86056, 29.2931 to \
  -0.03, 29.2931 to \
  -0.03, 14.6506 to \
  -4.86056, 14.6506 to \
  -4.86056, 29.2931 front fs empty border lc rgb '#549f' lw 0.1
set object 1462 polygon from \
  -4.84684, 29.3139 to \
  -0.03, 29.3139 to \
  -0.03, 14.6614 to \
  -4.84684, 14.6614 to \
  -4.84684, 29.3139 front fs empty border lc rgb '#549f' lw 0.1
set object 1463 polygon from \
  -4.83196, 29.3347 to \
  -0.03, 29.3347 to \
  -0.03, 14.6722 to \
  -4.83196, 14.6722 to \
  -4.83196, 29.3347 front fs empty border lc rgb '#549f' lw 0.1
set object 1464 polygon from \
  -4.81595, 29.3556 to \
  -0.03, 29.3556 to \
  -0.03, 14.6831 to \
  -4.81595, 14.6831 to \
  -4.81595, 29.3556 front fs empty border lc rgb '#549f' lw 0.1
set object 1465 polygon from \
  -4.7988, 29.3764 to \
  -0.03, 29.3764 to \
  -0.03, 14.6939 to \
  -4.7988, 14.6939 to \
  -4.7988, 29.3764 front fs empty border lc rgb '#549f' lw 0.1
set object 1466 polygon from \
  -4.78053, 29.3972 to \
  -0.03, 29.3972 to \
  -0.03, 14.7047 to \
  -4.78053, 14.7047 to \
  -4.78053, 29.3972 front fs empty border lc rgb '#549f' lw 0.1
set object 1467 polygon from \
  -4.76114, 29.4181 to \
  -0.03, 29.4181 to \
  -0.03, 14.7156 to \
  -4.76114, 14.7156 to \
  -4.76114, 29.4181 front fs empty border lc rgb '#549f' lw 0.1
set object 1468 polygon from \
  -4.74331, 29.4389 to \
  -0.03, 29.4389 to \
  -0.03, 14.7264 to \
  -4.74331, 14.7264 to \
  -4.74331, 29.4389 front fs empty border lc rgb '#549f' lw 0.1
set object 1469 polygon from \
  -4.72511, 29.4597 to \
  -0.03, 29.4597 to \
  -0.03, 14.7372 to \
  -4.72511, 14.7372 to \
  -4.72511, 29.4597 front fs empty border lc rgb '#549f' lw 0.1
set object 1470 polygon from \
  -4.70579, 29.4806 to \
  -0.03, 29.4806 to \
  -0.03, 14.7481 to \
  -4.70579, 14.7481 to \
  -4.70579, 29.4806 front fs empty border lc rgb '#549f' lw 0.1
set object 1471 polygon from \
  -4.68535, 29.5014 to \
  -0.03, 29.5014 to \
  -0.03, 14.7589 to \
  -4.68535, 14.7589 to \
  -4.68535, 29.5014 front fs empty border lc rgb '#549f' lw 0.1
set object 1472 polygon from \
  -4.66379, 29.5222 to \
  -0.03, 29.5222 to \
  -0.03, 14.7697 to \
  -4.66379, 14.7697 to \
  -4.66379, 29.5222 front fs empty border lc rgb '#549f' lw 0.1
set object 1473 polygon from \
  -4.64113, 29.5431 to \
  -0.03, 29.5431 to \
  -0.03, 14.7806 to \
  -4.64113, 14.7806 to \
  -4.64113, 29.5431 front fs empty border lc rgb '#549f' lw 0.1
set object 1474 polygon from \
  -4.61738, 29.5639 to \
  -0.03, 29.5639 to \
  -0.03, 14.7914 to \
  -4.61738, 14.7914 to \
  -4.61738, 29.5639 front fs empty border lc rgb '#549f' lw 0.1
set object 1475 polygon from \
  -4.59254, 29.5848 to \
  -0.03, 29.5848 to \
  -0.03, 14.8022 to \
  -4.59254, 14.8022 to \
  -4.59254, 29.5848 front fs empty border lc rgb '#549f' lw 0.1
set object 1476 polygon from \
  -4.56662, 29.6056 to \
  -0.03, 29.6056 to \
  -0.03, 14.8131 to \
  -4.56662, 14.8131 to \
  -4.56662, 29.6056 front fs empty border lc rgb '#549f' lw 0.1
set object 1477 polygon from \
  -4.53965, 29.6265 to \
  -0.03, 29.6265 to \
  -0.03, 14.8239 to \
  -4.53965, 14.8239 to \
  -4.53965, 29.6265 front fs empty border lc rgb '#549f' lw 0.1
set object 1478 polygon from \
  -4.51162, 29.6473 to \
  -0.03, 29.6473 to \
  -0.03, 14.8348 to \
  -4.51162, 14.8348 to \
  -4.51162, 29.6473 front fs empty border lc rgb '#549f' lw 0.1
set object 1479 polygon from \
  -4.48254, 29.6682 to \
  -0.03, 29.6682 to \
  -0.03, 14.8456 to \
  -4.48254, 14.8456 to \
  -4.48254, 29.6682 front fs empty border lc rgb '#549f' lw 0.1
set object 1480 polygon from \
  -4.45244, 29.689 to \
  -0.03, 29.689 to \
  -0.03, 14.8565 to \
  -4.45244, 14.8565 to \
  -4.45244, 29.689 front fs empty border lc rgb '#549f' lw 0.1
set object 1481 polygon from \
  -4.42133, 29.7099 to \
  -0.03, 29.7099 to \
  -0.03, 14.8673 to \
  -4.42133, 14.8673 to \
  -4.42133, 29.7099 front fs empty border lc rgb '#549f' lw 0.1
set object 1482 polygon from \
  -4.38921, 29.7307 to \
  -0.03, 29.7307 to \
  -0.03, 14.8781 to \
  -4.38921, 14.8781 to \
  -4.38921, 29.7307 front fs empty border lc rgb '#549f' lw 0.1
set object 1483 polygon from \
  -4.3561, 29.7516 to \
  -0.03, 29.7516 to \
  -0.03, 14.889 to \
  -4.3561, 14.889 to \
  -4.3561, 29.7516 front fs empty border lc rgb '#549f' lw 0.1
set object 1484 polygon from \
  -4.32202, 29.7724 to \
  -0.03, 29.7724 to \
  -0.03, 14.8998 to \
  -4.32202, 14.8998 to \
  -4.32202, 29.7724 front fs empty border lc rgb '#549f' lw 0.1
set object 1485 polygon from \
  -4.28697, 29.7933 to \
  -0.03, 29.7933 to \
  -0.03, 14.9107 to \
  -4.28697, 14.9107 to \
  -4.28697, 29.7933 front fs empty border lc rgb '#549f' lw 0.1
set object 1486 polygon from \
  -4.25098, 29.8141 to \
  -0.03, 29.8141 to \
  -0.03, 14.9216 to \
  -4.25098, 14.9216 to \
  -4.25098, 29.8141 front fs empty border lc rgb '#549f' lw 0.1
set object 1487 polygon from \
  -4.21406, 29.835 to \
  -0.03, 29.835 to \
  -0.03, 14.9324 to \
  -4.21406, 14.9324 to \
  -4.21406, 29.835 front fs empty border lc rgb '#549f' lw 0.1
set object 1488 polygon from \
  -4.17623, 29.8558 to \
  -0.03, 29.8558 to \
  -0.03, 14.9433 to \
  -4.17623, 14.9433 to \
  -4.17623, 29.8558 front fs empty border lc rgb '#549f' lw 0.1
set object 1489 polygon from \
  -4.1375, 29.8767 to \
  -0.03, 29.8767 to \
  -0.03, 14.9541 to \
  -4.1375, 14.9541 to \
  -4.1375, 29.8767 front fs empty border lc rgb '#549f' lw 0.1
set object 1490 polygon from \
  -4.09789, 29.8976 to \
  -0.03, 29.8976 to \
  -0.03, 14.965 to \
  -4.09789, 14.965 to \
  -4.09789, 29.8976 front fs empty border lc rgb '#549f' lw 0.1
set object 1491 polygon from \
  -4.05742, 29.9184 to \
  -0.03, 29.9184 to \
  -0.03, 14.9758 to \
  -4.05742, 14.9758 to \
  -4.05742, 29.9184 front fs empty border lc rgb '#549f' lw 0.1
set object 1492 polygon from \
  -4.0161, 29.9393 to \
  -0.03, 29.9393 to \
  -0.03, 14.9867 to \
  -4.0161, 14.9867 to \
  -4.0161, 29.9393 front fs empty border lc rgb '#549f' lw 0.1
set object 1493 polygon from \
  -3.97395, 29.9602 to \
  -0.03, 29.9602 to \
  -0.03, 14.9976 to \
  -3.97395, 14.9976 to \
  -3.97395, 29.9602 front fs empty border lc rgb '#549f' lw 0.1
set object 1494 polygon from \
  -3.93099, 29.981 to \
  -0.03, 29.981 to \
  -0.03, 15.0084 to \
  -3.93099, 15.0084 to \
  -3.93099, 29.981 front fs empty border lc rgb '#549f' lw 0.1
set object 1495 polygon from \
  -3.88724, 30.0019 to \
  -0.03, 30.0019 to \
  -0.03, 15.0193 to \
  -3.88724, 15.0193 to \
  -3.88724, 30.0019 front fs empty border lc rgb '#549f' lw 0.1
set object 1496 polygon from \
  -3.84272, 30.0228 to \
  -0.03, 30.0228 to \
  -0.03, 15.0302 to \
  -3.84272, 15.0302 to \
  -3.84272, 30.0228 front fs empty border lc rgb '#549f' lw 0.1
set object 1497 polygon from \
  -3.79744, 30.0436 to \
  -0.03, 30.0436 to \
  -0.03, 15.041 to \
  -3.79744, 15.041 to \
  -3.79744, 30.0436 front fs empty border lc rgb '#549f' lw 0.1
set object 1498 polygon from \
  -3.75144, 30.0645 to \
  -0.03, 30.0645 to \
  -0.03, 15.0519 to \
  -3.75144, 15.0519 to \
  -3.75144, 30.0645 front fs empty border lc rgb '#549f' lw 0.1
set object 1499 polygon from \
  -3.70472, 30.0854 to \
  -0.03, 30.0854 to \
  -0.03, 15.0628 to \
  -3.70472, 15.0628 to \
  -3.70472, 30.0854 front fs empty border lc rgb '#549f' lw 0.1
set object 1500 polygon from \
  -3.6573, 30.1062 to \
  -0.03, 30.1062 to \
  -0.03, 15.0736 to \
  -3.6573, 15.0736 to \
  -3.6573, 30.1062 front fs empty border lc rgb '#549f' lw 0.1
set object 1501 polygon from \
  -3.60922, 30.1271 to \
  -0.03, 30.1271 to \
  -0.03, 15.0845 to \
  -3.60922, 15.0845 to \
  -3.60922, 30.1271 front fs empty border lc rgb '#549f' lw 0.1
set object 1502 polygon from \
  -3.56048, 30.148 to \
  -0.03, 30.148 to \
  -0.03, 15.0954 to \
  -3.56048, 15.0954 to \
  -3.56048, 30.148 front fs empty border lc rgb '#549f' lw 0.1
set object 1503 polygon from \
  -3.51111, 30.1689 to \
  -0.03, 30.1689 to \
  -0.03, 15.1062 to \
  -3.51111, 15.1062 to \
  -3.51111, 30.1689 front fs empty border lc rgb '#549f' lw 0.1
set object 1504 polygon from \
  -3.46114, 30.1898 to \
  -0.03, 30.1898 to \
  -0.03, 15.1171 to \
  -3.46114, 15.1171 to \
  -3.46114, 30.1898 front fs empty border lc rgb '#549f' lw 0.1
set object 1505 polygon from \
  -3.41057, 30.2106 to \
  -0.03, 30.2106 to \
  -0.03, 15.128 to \
  -3.41057, 15.128 to \
  -3.41057, 30.2106 front fs empty border lc rgb '#549f' lw 0.1
set object 1506 polygon from \
  -3.35944, 30.2315 to \
  -0.03, 30.2315 to \
  -0.03, 15.1389 to \
  -3.35944, 15.1389 to \
  -3.35944, 30.2315 front fs empty border lc rgb '#549f' lw 0.1
set object 1507 polygon from \
  -3.30777, 30.2524 to \
  -0.03, 30.2524 to \
  -0.03, 15.1498 to \
  -3.30777, 15.1498 to \
  -3.30777, 30.2524 front fs empty border lc rgb '#549f' lw 0.1
set object 1508 polygon from \
  -3.25557, 30.2733 to \
  -0.03, 30.2733 to \
  -0.03, 15.1606 to \
  -3.25557, 15.1606 to \
  -3.25557, 30.2733 front fs empty border lc rgb '#549f' lw 0.1
set object 1509 polygon from \
  -3.20288, 30.2942 to \
  -0.03, 30.2942 to \
  -0.03, 15.1715 to \
  -3.20288, 15.1715 to \
  -3.20288, 30.2942 front fs empty border lc rgb '#549f' lw 0.1
set object 1510 polygon from \
  -3.14971, 30.3151 to \
  -0.03, 30.3151 to \
  -0.03, 15.1824 to \
  -3.14971, 15.1824 to \
  -3.14971, 30.3151 front fs empty border lc rgb '#549f' lw 0.1
set object 1511 polygon from \
  -3.09609, 30.336 to \
  -0.03, 30.336 to \
  -0.03, 15.1933 to \
  -3.09609, 15.1933 to \
  -3.09609, 30.336 front fs empty border lc rgb '#549f' lw 0.1
set object 1512 polygon from \
  -3.04203, 30.3568 to \
  -0.03, 30.3568 to \
  -0.03, 15.2042 to \
  -3.04203, 15.2042 to \
  -3.04203, 30.3568 front fs empty border lc rgb '#549f' lw 0.1
set object 1513 polygon from \
  -2.98757, 30.3777 to \
  -0.03, 30.3777 to \
  -0.03, 15.2151 to \
  -2.98757, 15.2151 to \
  -2.98757, 30.3777 front fs empty border lc rgb '#549f' lw 0.1
set object 1514 polygon from \
  -2.94312, 30.3986 to \
  -0.03, 30.3986 to \
  -0.03, 15.2259 to \
  -2.94312, 15.2259 to \
  -2.94312, 30.3986 front fs empty border lc rgb '#549f' lw 0.1
set object 1515 polygon from \
  -2.92534, 30.4195 to \
  -0.03, 30.4195 to \
  -0.03, 15.2368 to \
  -2.92534, 15.2368 to \
  -2.92534, 30.4195 front fs empty border lc rgb '#549f' lw 0.1
set object 1516 polygon from \
  -2.90708, 30.4404 to \
  -0.03, 30.4404 to \
  -0.03, 15.2477 to \
  -2.90708, 15.2477 to \
  -2.90708, 30.4404 front fs empty border lc rgb '#549f' lw 0.1
set object 1517 polygon from \
  -2.88833, 30.4613 to \
  -0.03, 30.4613 to \
  -0.03, 15.2586 to \
  -2.88833, 15.2586 to \
  -2.88833, 30.4613 front fs empty border lc rgb '#549f' lw 0.1
set object 1518 polygon from \
  -2.86909, 30.4822 to \
  -0.03, 30.4822 to \
  -0.03, 15.2695 to \
  -2.86909, 15.2695 to \
  -2.86909, 30.4822 front fs empty border lc rgb '#549f' lw 0.1
set object 1519 polygon from \
  -2.84935, 30.5031 to \
  -0.03, 30.5031 to \
  -0.03, 15.2804 to \
  -2.84935, 15.2804 to \
  -2.84935, 30.5031 front fs empty border lc rgb '#549f' lw 0.1
set object 1520 polygon from \
  -2.8291, 30.524 to \
  -0.03, 30.524 to \
  -0.03, 15.2913 to \
  -2.8291, 15.2913 to \
  -2.8291, 30.524 front fs empty border lc rgb '#549f' lw 0.1
set object 1521 polygon from \
  -2.80835, 30.5449 to \
  -0.03, 30.5449 to \
  -0.03, 15.3022 to \
  -2.80835, 15.3022 to \
  -2.80835, 30.5449 front fs empty border lc rgb '#549f' lw 0.1
set object 1522 polygon from \
  -2.78707, 30.5658 to \
  -0.03, 30.5658 to \
  -0.03, 15.3131 to \
  -2.78707, 15.3131 to \
  -2.78707, 30.5658 front fs empty border lc rgb '#549f' lw 0.1
set object 1523 polygon from \
  -2.76527, 30.5867 to \
  -0.03, 30.5867 to \
  -0.03, 15.324 to \
  -2.76527, 15.324 to \
  -2.76527, 30.5867 front fs empty border lc rgb '#549f' lw 0.1
set object 1524 polygon from \
  -2.74294, 30.6076 to \
  -0.03, 30.6076 to \
  -0.03, 15.3349 to \
  -2.74294, 15.3349 to \
  -2.74294, 30.6076 front fs empty border lc rgb '#549f' lw 0.1
set object 1525 polygon from \
  -2.72008, 30.6285 to \
  -0.03, 30.6285 to \
  -0.03, 15.3458 to \
  -2.72008, 15.3458 to \
  -2.72008, 30.6285 front fs empty border lc rgb '#549f' lw 0.1
set object 1526 polygon from \
  -2.69668, 30.6494 to \
  -0.03, 30.6494 to \
  -0.03, 15.3567 to \
  -2.69668, 15.3567 to \
  -2.69668, 30.6494 front fs empty border lc rgb '#549f' lw 0.1
set object 1527 polygon from \
  -2.67274, 30.6703 to \
  -0.03, 30.6703 to \
  -0.03, 15.3676 to \
  -2.67274, 15.3676 to \
  -2.67274, 30.6703 front fs empty border lc rgb '#549f' lw 0.1
set object 1528 polygon from \
  -2.64825, 30.6912 to \
  -0.03, 30.6912 to \
  -0.03, 15.3785 to \
  -2.64825, 15.3785 to \
  -2.64825, 30.6912 front fs empty border lc rgb '#549f' lw 0.1
set object 1529 polygon from \
  -2.6232, 30.7122 to \
  -0.03, 30.7122 to \
  -0.03, 15.3894 to \
  -2.6232, 15.3894 to \
  -2.6232, 30.7122 front fs empty border lc rgb '#549f' lw 0.1
set object 1530 polygon from \
  -2.5976, 30.7331 to \
  -0.03, 30.7331 to \
  -0.03, 15.4003 to \
  -2.5976, 15.4003 to \
  -2.5976, 30.7331 front fs empty border lc rgb '#549f' lw 0.1
set object 1531 polygon from \
  -2.57144, 30.754 to \
  -0.03, 30.754 to \
  -0.03, 15.4112 to \
  -2.57144, 15.4112 to \
  -2.57144, 30.754 front fs empty border lc rgb '#549f' lw 0.1
set object 1532 polygon from \
  -2.54472, 30.7749 to \
  -0.03, 30.7749 to \
  -0.03, 15.4221 to \
  -2.54472, 15.4221 to \
  -2.54472, 30.7749 front fs empty border lc rgb '#549f' lw 0.1
set object 1533 polygon from \
  -2.51743, 30.7958 to \
  -0.03, 30.7958 to \
  -0.03, 15.4331 to \
  -2.51743, 15.4331 to \
  -2.51743, 30.7958 front fs empty border lc rgb '#549f' lw 0.1
set object 1534 polygon from \
  -2.48958, 30.8167 to \
  -0.03, 30.8167 to \
  -0.03, 15.444 to \
  -2.48958, 15.444 to \
  -2.48958, 30.8167 front fs empty border lc rgb '#549f' lw 0.1
set object 1535 polygon from \
  -2.46115, 30.8376 to \
  -0.03, 30.8376 to \
  -0.03, 15.4549 to \
  -2.46115, 15.4549 to \
  -2.46115, 30.8376 front fs empty border lc rgb '#549f' lw 0.1
set object 1536 polygon from \
  -2.43215, 30.8586 to \
  -0.03, 30.8586 to \
  -0.03, 15.4658 to \
  -2.43215, 15.4658 to \
  -2.43215, 30.8586 front fs empty border lc rgb '#549f' lw 0.1
set object 1537 polygon from \
  -2.40258, 30.8795 to \
  -0.03, 30.8795 to \
  -0.03, 15.4767 to \
  -2.40258, 15.4767 to \
  -2.40258, 30.8795 front fs empty border lc rgb '#549f' lw 0.1
set object 1538 polygon from \
  -2.37243, 30.9004 to \
  -0.03, 30.9004 to \
  -0.03, 15.4876 to \
  -2.37243, 15.4876 to \
  -2.37243, 30.9004 front fs empty border lc rgb '#549f' lw 0.1
set object 1539 polygon from \
  -2.3417, 30.9213 to \
  -0.03, 30.9213 to \
  -0.03, 15.4986 to \
  -2.3417, 15.4986 to \
  -2.3417, 30.9213 front fs empty border lc rgb '#549f' lw 0.1
set object 1540 polygon from \
  -2.31039, 30.9422 to \
  -0.03, 30.9422 to \
  -0.03, 15.5095 to \
  -2.31039, 15.5095 to \
  -2.31039, 30.9422 front fs empty border lc rgb '#549f' lw 0.1
set object 1541 polygon from \
  -2.27851, 30.9632 to \
  -0.03, 30.9632 to \
  -0.03, 15.5204 to \
  -2.27851, 15.5204 to \
  -2.27851, 30.9632 front fs empty border lc rgb '#549f' lw 0.1
set object 1542 polygon from \
  -2.24604, 30.9841 to \
  -0.03, 30.9841 to \
  -0.03, 15.5313 to \
  -2.24604, 15.5313 to \
  -2.24604, 30.9841 front fs empty border lc rgb '#549f' lw 0.1
set object 1543 polygon from \
  -2.23619, 31.005 to \
  -0.03, 31.005 to \
  -0.03, 15.5422 to \
  -2.23619, 15.5422 to \
  -2.23619, 31.005 front fs empty border lc rgb '#549f' lw 0.1
set object 1544 polygon from \
  -2.25126, 31.026 to \
  -0.03, 31.026 to \
  -0.03, 15.5532 to \
  -2.25126, 15.5532 to \
  -2.25126, 31.026 front fs empty border lc rgb '#549f' lw 0.1
set object 1545 polygon from \
  -2.26524, 31.0469 to \
  -0.03, 31.0469 to \
  -0.03, 15.5641 to \
  -2.26524, 15.5641 to \
  -2.26524, 31.0469 front fs empty border lc rgb '#549f' lw 0.1
set object 1546 polygon from \
  -2.27811, 31.0678 to \
  -0.03, 31.0678 to \
  -0.03, 15.575 to \
  -2.27811, 15.575 to \
  -2.27811, 31.0678 front fs empty border lc rgb '#549f' lw 0.1
set object 1547 polygon from \
  -2.28987, 31.0888 to \
  -0.03, 31.0888 to \
  -0.03, 15.586 to \
  -2.28987, 15.586 to \
  -2.28987, 31.0888 front fs empty border lc rgb '#549f' lw 0.1
set object 1548 polygon from \
  -2.3005, 31.1097 to \
  -0.03, 31.1097 to \
  -0.03, 15.5969 to \
  -2.3005, 15.5969 to \
  -2.3005, 31.1097 front fs empty border lc rgb '#549f' lw 0.1
set object 1549 polygon from \
  -2.30998, 31.1306 to \
  -0.03, 31.1306 to \
  -0.03, 15.6078 to \
  -2.30998, 15.6078 to \
  -2.30998, 31.1306 front fs empty border lc rgb '#549f' lw 0.1
set object 1550 polygon from \
  -2.3183, 31.1516 to \
  -0.03, 31.1516 to \
  -0.03, 15.6188 to \
  -2.3183, 15.6188 to \
  -2.3183, 31.1516 front fs empty border lc rgb '#549f' lw 0.1
set object 1551 polygon from \
  -2.32545, 31.1725 to \
  -0.03, 31.1725 to \
  -0.03, 15.6297 to \
  -2.32545, 15.6297 to \
  -2.32545, 31.1725 front fs empty border lc rgb '#549f' lw 0.1
set object 1552 polygon from \
  -2.33141, 31.1934 to \
  -0.03, 31.1934 to \
  -0.03, 15.6406 to \
  -2.33141, 15.6406 to \
  -2.33141, 31.1934 front fs empty border lc rgb '#549f' lw 0.1
set object 1553 polygon from \
  -2.33618, 31.2144 to \
  -0.03, 31.2144 to \
  -0.03, 15.6516 to \
  -2.33618, 15.6516 to \
  -2.33618, 31.2144 front fs empty border lc rgb '#549f' lw 0.1
set object 1554 polygon from \
  -2.33975, 31.2353 to \
  -0.03, 31.2353 to \
  -0.03, 15.6625 to \
  -2.33975, 15.6625 to \
  -2.33975, 31.2353 front fs empty border lc rgb '#549f' lw 0.1
set object 1555 polygon from \
  -2.3421, 31.2563 to \
  -0.03, 31.2563 to \
  -0.03, 15.6734 to \
  -2.3421, 15.6734 to \
  -2.3421, 31.2563 front fs empty border lc rgb '#549f' lw 0.1
set object 1556 polygon from \
  -2.34323, 31.2772 to \
  -0.03, 31.2772 to \
  -0.03, 15.6844 to \
  -2.34323, 15.6844 to \
  -2.34323, 31.2772 front fs empty border lc rgb '#549f' lw 0.1
set object 1557 polygon from \
  -2.34323, 31.2982 to \
  -0.03, 31.2982 to \
  -0.03, 15.6953 to \
  -2.34323, 15.6953 to \
  -2.34323, 31.2982 front fs empty border lc rgb '#549f' lw 0.1
set object 1558 polygon from \
  -2.34312, 31.3191 to \
  -0.03, 31.3191 to \
  -0.03, 15.7063 to \
  -2.34312, 15.7063 to \
  -2.34312, 31.3191 front fs empty border lc rgb '#549f' lw 0.1
set object 1559 polygon from \
  -2.34179, 31.3401 to \
  -0.03, 31.3401 to \
  -0.03, 15.7172 to \
  -2.34179, 15.7172 to \
  -2.34179, 31.3401 front fs empty border lc rgb '#549f' lw 0.1
set object 1560 polygon from \
  -2.3392, 31.361 to \
  -0.03, 31.361 to \
  -0.03, 15.7282 to \
  -2.3392, 15.7282 to \
  -2.3392, 31.361 front fs empty border lc rgb '#549f' lw 0.1
set object 1561 polygon from \
  -2.33537, 31.382 to \
  -0.03, 31.382 to \
  -0.03, 15.7391 to \
  -2.33537, 15.7391 to \
  -2.33537, 31.382 front fs empty border lc rgb '#549f' lw 0.1
set object 1562 polygon from \
  -2.33029, 31.4029 to \
  -0.03, 31.4029 to \
  -0.03, 15.75 to \
  -2.33029, 15.75 to \
  -2.33029, 31.4029 front fs empty border lc rgb '#549f' lw 0.1
set object 1563 polygon from \
  -2.32405, 31.4239 to \
  -0.03, 31.4239 to \
  -0.03, 15.761 to \
  -2.32405, 15.761 to \
  -2.32405, 31.4239 front fs empty border lc rgb '#549f' lw 0.1
set object 1564 polygon from \
  -2.31942, 31.4448 to \
  -0.03, 31.4448 to \
  -0.03, 15.7719 to \
  -2.31942, 15.7719 to \
  -2.31942, 31.4448 front fs empty border lc rgb '#549f' lw 0.1
set object 1565 polygon from \
  -2.31354, 31.4658 to \
  -0.03, 31.4658 to \
  -0.03, 15.7829 to \
  -2.31354, 15.7829 to \
  -2.31354, 31.4658 front fs empty border lc rgb '#549f' lw 0.1
set object 1566 polygon from \
  -2.3064, 31.4867 to \
  -0.03, 31.4867 to \
  -0.03, 15.7939 to \
  -2.3064, 15.7939 to \
  -2.3064, 31.4867 front fs empty border lc rgb '#549f' lw 0.1
set object 1567 polygon from \
  -2.29931, 31.5077 to \
  -0.03, 31.5077 to \
  -0.03, 15.8048 to \
  -2.29931, 15.8048 to \
  -2.29931, 31.5077 front fs empty border lc rgb '#549f' lw 0.1
set object 1568 polygon from \
  -2.29334, 31.5286 to \
  -0.03, 31.5286 to \
  -0.03, 15.8158 to \
  -2.29334, 15.8158 to \
  -2.29334, 31.5286 front fs empty border lc rgb '#549f' lw 0.1
set object 1569 polygon from \
  -2.28609, 31.5496 to \
  -0.03, 31.5496 to \
  -0.03, 15.8267 to \
  -2.28609, 15.8267 to \
  -2.28609, 31.5496 front fs empty border lc rgb '#549f' lw 0.1
set object 1570 polygon from \
  -2.27759, 31.5706 to \
  -0.03, 31.5706 to \
  -0.03, 15.8377 to \
  -2.27759, 15.8377 to \
  -2.27759, 31.5706 front fs empty border lc rgb '#549f' lw 0.1
set object 1571 polygon from \
  -2.27429, 31.5915 to \
  -0.03, 31.5915 to \
  -0.03, 15.8486 to \
  -2.27429, 15.8486 to \
  -2.27429, 31.5915 front fs empty border lc rgb '#549f' lw 0.1
set object 1572 polygon from \
  -2.30025, 31.6125 to \
  -0.03, 31.6125 to \
  -0.03, 15.8596 to \
  -2.30025, 15.8596 to \
  -2.30025, 31.6125 front fs empty border lc rgb '#549f' lw 0.1
set object 1573 polygon from \
  -2.32523, 31.6335 to \
  -0.03, 31.6335 to \
  -0.03, 15.8706 to \
  -2.32523, 15.8706 to \
  -2.32523, 31.6335 front fs empty border lc rgb '#549f' lw 0.1
set object 1574 polygon from \
  -2.34923, 31.6544 to \
  -0.03, 31.6544 to \
  -0.03, 15.8815 to \
  -2.34923, 15.8815 to \
  -2.34923, 31.6544 front fs empty border lc rgb '#549f' lw 0.1
set object 1575 polygon from \
  -2.37224, 31.6754 to \
  -0.03, 31.6754 to \
  -0.03, 15.8925 to \
  -2.37224, 15.8925 to \
  -2.37224, 31.6754 front fs empty border lc rgb '#549f' lw 0.1
set object 1576 polygon from \
  -2.39425, 31.6964 to \
  -0.03, 31.6964 to \
  -0.03, 15.9035 to \
  -2.39425, 15.9035 to \
  -2.39425, 31.6964 front fs empty border lc rgb '#549f' lw 0.1
set object 1577 polygon from \
  -2.41527, 31.7173 to \
  -0.03, 31.7173 to \
  -0.03, 15.9144 to \
  -2.41527, 15.9144 to \
  -2.41527, 31.7173 front fs empty border lc rgb '#549f' lw 0.1
set object 1578 polygon from \
  -2.43528, 31.7383 to \
  -0.03, 31.7383 to \
  -0.03, 15.9254 to \
  -2.43528, 15.9254 to \
  -2.43528, 31.7383 front fs empty border lc rgb '#549f' lw 0.1
set object 1579 polygon from \
  -2.45429, 31.7593 to \
  -0.03, 31.7593 to \
  -0.03, 15.9364 to \
  -2.45429, 15.9364 to \
  -2.45429, 31.7593 front fs empty border lc rgb '#549f' lw 0.1
set object 1580 polygon from \
  -2.4723, 31.7802 to \
  -0.03, 31.7802 to \
  -0.03, 15.9473 to \
  -2.4723, 15.9473 to \
  -2.4723, 31.7802 front fs empty border lc rgb '#549f' lw 0.1
set object 1581 polygon from \
  -2.4893, 31.8012 to \
  -0.03, 31.8012 to \
  -0.03, 15.9583 to \
  -2.4893, 15.9583 to \
  -2.4893, 31.8012 front fs empty border lc rgb '#549f' lw 0.1
set object 1582 polygon from \
  -2.5053, 31.8222 to \
  -0.03, 31.8222 to \
  -0.03, 15.9693 to \
  -2.5053, 15.9693 to \
  -2.5053, 31.8222 front fs empty border lc rgb '#549f' lw 0.1
set object 1583 polygon from \
  -2.52028, 31.8432 to \
  -0.03, 31.8432 to \
  -0.03, 15.9802 to \
  -2.52028, 15.9802 to \
  -2.52028, 31.8432 front fs empty border lc rgb '#549f' lw 0.1
set object 1584 polygon from \
  -2.53426, 31.8642 to \
  -0.03, 31.8642 to \
  -0.03, 15.9912 to \
  -2.53426, 15.9912 to \
  -2.53426, 31.8642 front fs empty border lc rgb '#549f' lw 0.1
set object 1585 polygon from \
  -2.54723, 31.8851 to \
  -0.03, 31.8851 to \
  -0.03, 16.0022 to \
  -2.54723, 16.0022 to \
  -2.54723, 31.8851 front fs empty border lc rgb '#549f' lw 0.1
set object 1586 polygon from \
  -2.5592, 31.9061 to \
  -0.03, 31.9061 to \
  -0.03, 16.0132 to \
  -2.5592, 16.0132 to \
  -2.5592, 31.9061 front fs empty border lc rgb '#549f' lw 0.1
set object 1587 polygon from \
  -2.57016, 31.9271 to \
  -0.03, 31.9271 to \
  -0.03, 16.0242 to \
  -2.57016, 16.0242 to \
  -2.57016, 31.9271 front fs empty border lc rgb '#549f' lw 0.1
set object 1588 polygon from \
  -2.58012, 31.9481 to \
  -0.03, 31.9481 to \
  -0.03, 16.0351 to \
  -2.58012, 16.0351 to \
  -2.58012, 31.9481 front fs empty border lc rgb '#549f' lw 0.1
set object 1589 polygon from \
  -2.58907, 31.9691 to \
  -0.03, 31.9691 to \
  -0.03, 16.0461 to \
  -2.58907, 16.0461 to \
  -2.58907, 31.9691 front fs empty border lc rgb '#549f' lw 0.1
set object 1590 polygon from \
  -2.59704, 31.9901 to \
  -0.03, 31.9901 to \
  -0.03, 16.0571 to \
  -2.59704, 16.0571 to \
  -2.59704, 31.9901 front fs empty border lc rgb '#549f' lw 0.1
set object 1591 polygon from \
  -2.60401, 32.0111 to \
  -0.03, 32.0111 to \
  -0.03, 16.0681 to \
  -2.60401, 16.0681 to \
  -2.60401, 32.0111 front fs empty border lc rgb '#549f' lw 0.1
set object 1592 polygon from \
  -2.60999, 32.032 to \
  -0.03, 32.032 to \
  -0.03, 16.0791 to \
  -2.60999, 16.0791 to \
  -2.60999, 32.032 front fs empty border lc rgb '#549f' lw 0.1
set object 1593 polygon from \
  -2.615, 32.053 to \
  -0.03, 32.053 to \
  -0.03, 16.0901 to \
  -2.615, 16.0901 to \
  -2.615, 32.053 front fs empty border lc rgb '#549f' lw 0.1
set object 1594 polygon from \
  -2.61902, 32.074 to \
  -0.03, 32.074 to \
  -0.03, 16.101 to \
  -2.61902, 16.101 to \
  -2.61902, 32.074 front fs empty border lc rgb '#549f' lw 0.1
set object 1595 polygon from \
  -2.62207, 32.095 to \
  -0.03, 32.095 to \
  -0.03, 16.112 to \
  -2.62207, 16.112 to \
  -2.62207, 32.095 front fs empty border lc rgb '#549f' lw 0.1
set object 1596 polygon from \
  -2.62416, 32.116 to \
  -0.03, 32.116 to \
  -0.03, 16.123 to \
  -2.62416, 16.123 to \
  -2.62416, 32.116 front fs empty border lc rgb '#549f' lw 0.1
set object 1597 polygon from \
  -2.62528, 32.137 to \
  -0.03, 32.137 to \
  -0.03, 16.134 to \
  -2.62528, 16.134 to \
  -2.62528, 32.137 front fs empty border lc rgb '#549f' lw 0.1
set object 1598 polygon from \
  -2.62546, 32.158 to \
  -0.03, 32.158 to \
  -0.03, 16.145 to \
  -2.62546, 16.145 to \
  -2.62546, 32.158 front fs empty border lc rgb '#549f' lw 0.1
set object 1599 polygon from \
  -2.62545, 32.179 to \
  -0.03, 32.179 to \
  -0.03, 16.156 to \
  -2.62545, 16.156 to \
  -2.62545, 32.179 front fs empty border lc rgb '#549f' lw 0.1
set object 1600 polygon from \
  -2.62469, 32.2 to \
  -0.03, 32.2 to \
  -0.03, 16.167 to \
  -2.62469, 16.167 to \
  -2.62469, 32.2 front fs empty border lc rgb '#549f' lw 0.1
set object 1601 polygon from \
  -2.62298, 32.221 to \
  -0.03, 32.221 to \
  -0.03, 16.178 to \
  -2.62298, 16.178 to \
  -2.62298, 32.221 front fs empty border lc rgb '#549f' lw 0.1
set object 1602 polygon from \
  -2.62035, 32.242 to \
  -0.03, 32.242 to \
  -0.03, 16.189 to \
  -2.62035, 16.189 to \
  -2.62035, 32.242 front fs empty border lc rgb '#549f' lw 0.1
set object 1603 polygon from \
  -2.6168, 32.263 to \
  -0.03, 32.263 to \
  -0.03, 16.2 to \
  -2.6168, 16.2 to \
  -2.6168, 32.263 front fs empty border lc rgb '#549f' lw 0.1
set object 1604 polygon from \
  -2.61234, 32.284 to \
  -0.03, 32.284 to \
  -0.03, 16.211 to \
  -2.61234, 16.211 to \
  -2.61234, 32.284 front fs empty border lc rgb '#549f' lw 0.1
set object 1605 polygon from \
  -2.60699, 32.305 to \
  -0.03, 32.305 to \
  -0.03, 16.222 to \
  -2.60699, 16.222 to \
  -2.60699, 32.305 front fs empty border lc rgb '#549f' lw 0.1
set object 1606 polygon from \
  -2.60074, 32.326 to \
  -0.03, 32.326 to \
  -0.03, 16.233 to \
  -2.60074, 16.233 to \
  -2.60074, 32.326 front fs empty border lc rgb '#549f' lw 0.1
set object 1607 polygon from \
  -2.59362, 32.347 to \
  -0.03, 32.347 to \
  -0.03, 16.244 to \
  -2.59362, 16.244 to \
  -2.59362, 32.347 front fs empty border lc rgb '#549f' lw 0.1
set object 1608 polygon from \
  -2.58563, 32.368 to \
  -0.03, 32.368 to \
  -0.03, 16.255 to \
  -2.58563, 16.255 to \
  -2.58563, 32.368 front fs empty border lc rgb '#549f' lw 0.1
set object 1609 polygon from \
  -2.57678, 32.3891 to \
  -0.03, 32.3891 to \
  -0.03, 16.266 to \
  -2.57678, 16.266 to \
  -2.57678, 32.3891 front fs empty border lc rgb '#549f' lw 0.1
set object 1610 polygon from \
  -2.5671, 32.4101 to \
  -0.03, 32.4101 to \
  -0.03, 16.277 to \
  -2.5671, 16.277 to \
  -2.5671, 32.4101 front fs empty border lc rgb '#549f' lw 0.1
set object 1611 polygon from \
  -2.55658, 32.4311 to \
  -0.03, 32.4311 to \
  -0.03, 16.288 to \
  -2.55658, 16.288 to \
  -2.55658, 32.4311 front fs empty border lc rgb '#549f' lw 0.1
set object 1612 polygon from \
  -2.54524, 32.4521 to \
  -0.03, 32.4521 to \
  -0.03, 16.299 to \
  -2.54524, 16.299 to \
  -2.54524, 32.4521 front fs empty border lc rgb '#549f' lw 0.1
set object 1613 polygon from \
  -2.55198, 32.4731 to \
  -0.03, 32.4731 to \
  -0.03, 16.3101 to \
  -2.55198, 16.3101 to \
  -2.55198, 32.4731 front fs empty border lc rgb '#549f' lw 0.1
set object 1614 polygon from \
  -2.5814, 32.4941 to \
  -0.03, 32.4941 to \
  -0.03, 16.3211 to \
  -2.5814, 16.3211 to \
  -2.5814, 32.4941 front fs empty border lc rgb '#549f' lw 0.1
set object 1615 polygon from \
  -2.61038, 32.5151 to \
  -0.03, 32.5151 to \
  -0.03, 16.3321 to \
  -2.61038, 16.3321 to \
  -2.61038, 32.5151 front fs empty border lc rgb '#549f' lw 0.1
set object 1616 polygon from \
  -2.63889, 32.5362 to \
  -0.03, 32.5362 to \
  -0.03, 16.3431 to \
  -2.63889, 16.3431 to \
  -2.63889, 32.5362 front fs empty border lc rgb '#549f' lw 0.1
set object 1617 polygon from \
  -2.66692, 32.5572 to \
  -0.03, 32.5572 to \
  -0.03, 16.3541 to \
  -2.66692, 16.3541 to \
  -2.66692, 32.5572 front fs empty border lc rgb '#549f' lw 0.1
set object 1618 polygon from \
  -2.69444, 32.5782 to \
  -0.03, 32.5782 to \
  -0.03, 16.3651 to \
  -2.69444, 16.3651 to \
  -2.69444, 32.5782 front fs empty border lc rgb '#549f' lw 0.1
set object 1619 polygon from \
  -2.72144, 32.5992 to \
  -0.03, 32.5992 to \
  -0.03, 16.3762 to \
  -2.72144, 16.3762 to \
  -2.72144, 32.5992 front fs empty border lc rgb '#549f' lw 0.1
set object 1620 polygon from \
  -2.74791, 32.6202 to \
  -0.03, 32.6202 to \
  -0.03, 16.3872 to \
  -2.74791, 16.3872 to \
  -2.74791, 32.6202 front fs empty border lc rgb '#549f' lw 0.1
set object 1621 polygon from \
  -2.77383, 32.6413 to \
  -0.03, 32.6413 to \
  -0.03, 16.3982 to \
  -2.77383, 16.3982 to \
  -2.77383, 32.6413 front fs empty border lc rgb '#549f' lw 0.1
set object 1622 polygon from \
  -2.80145, 32.6623 to \
  -0.03, 32.6623 to \
  -0.03, 16.4092 to \
  -2.80145, 16.4092 to \
  -2.80145, 32.6623 front fs empty border lc rgb '#549f' lw 0.1
set object 1623 polygon from \
  -2.83628, 32.6833 to \
  -0.03, 32.6833 to \
  -0.03, 16.4202 to \
  -2.83628, 16.4202 to \
  -2.83628, 32.6833 front fs empty border lc rgb '#549f' lw 0.1
set object 1624 polygon from \
  -2.87047, 32.7044 to \
  -0.03, 32.7044 to \
  -0.03, 16.4313 to \
  -2.87047, 16.4313 to \
  -2.87047, 32.7044 front fs empty border lc rgb '#549f' lw 0.1
set object 1625 polygon from \
  -2.90399, 32.7254 to \
  -0.03, 32.7254 to \
  -0.03, 16.4423 to \
  -2.90399, 16.4423 to \
  -2.90399, 32.7254 front fs empty border lc rgb '#549f' lw 0.1
set object 1626 polygon from \
  -2.93681, 32.7464 to \
  -0.03, 32.7464 to \
  -0.03, 16.4533 to \
  -2.93681, 16.4533 to \
  -2.93681, 32.7464 front fs empty border lc rgb '#549f' lw 0.1
set object 1627 polygon from \
  -2.96894, 32.7675 to \
  -0.03, 32.7675 to \
  -0.03, 16.4644 to \
  -2.96894, 16.4644 to \
  -2.96894, 32.7675 front fs empty border lc rgb '#549f' lw 0.1
set object 1628 polygon from \
  -3.00034, 32.7885 to \
  -0.03, 32.7885 to \
  -0.03, 16.4754 to \
  -3.00034, 16.4754 to \
  -3.00034, 32.7885 front fs empty border lc rgb '#549f' lw 0.1
set object 1629 polygon from \
  -3.031, 32.8095 to \
  -0.03, 32.8095 to \
  -0.03, 16.4864 to \
  -3.031, 16.4864 to \
  -3.031, 32.8095 front fs empty border lc rgb '#549f' lw 0.1
set object 1630 polygon from \
  -3.0609, 32.8306 to \
  -0.03, 32.8306 to \
  -0.03, 16.4975 to \
  -3.0609, 16.4975 to \
  -3.0609, 32.8306 front fs empty border lc rgb '#549f' lw 0.1
set object 1631 polygon from \
  -3.09003, 32.8516 to \
  -0.03, 32.8516 to \
  -0.03, 16.5085 to \
  -3.09003, 16.5085 to \
  -3.09003, 32.8516 front fs empty border lc rgb '#549f' lw 0.1
set object 1632 polygon from \
  -3.11837, 32.8726 to \
  -0.03, 32.8726 to \
  -0.03, 16.5195 to \
  -3.11837, 16.5195 to \
  -3.11837, 32.8726 front fs empty border lc rgb '#549f' lw 0.1
set object 1633 polygon from \
  -3.1459, 32.8937 to \
  -0.03, 32.8937 to \
  -0.03, 16.5306 to \
  -3.1459, 16.5306 to \
  -3.1459, 32.8937 front fs empty border lc rgb '#549f' lw 0.1
set object 1634 polygon from \
  -3.17261, 32.9147 to \
  -0.03, 32.9147 to \
  -0.03, 16.5416 to \
  -3.17261, 16.5416 to \
  -3.17261, 32.9147 front fs empty border lc rgb '#549f' lw 0.1
set object 1635 polygon from \
  -3.19848, 32.9358 to \
  -0.03, 32.9358 to \
  -0.03, 16.5526 to \
  -3.19848, 16.5526 to \
  -3.19848, 32.9358 front fs empty border lc rgb '#549f' lw 0.1
set object 1636 polygon from \
  -3.2235, 32.9568 to \
  -0.03, 32.9568 to \
  -0.03, 16.5637 to \
  -3.2235, 16.5637 to \
  -3.2235, 32.9568 front fs empty border lc rgb '#549f' lw 0.1
set object 1637 polygon from \
  -3.24837, 32.9779 to \
  -0.03, 32.9779 to \
  -0.03, 16.5747 to \
  -3.24837, 16.5747 to \
  -3.24837, 32.9779 front fs empty border lc rgb '#549f' lw 0.1
set object 1638 polygon from \
  -3.27325, 32.9989 to \
  -0.03, 32.9989 to \
  -0.03, 16.5858 to \
  -3.27325, 16.5858 to \
  -3.27325, 32.9989 front fs empty border lc rgb '#549f' lw 0.1
set object 1639 polygon from \
  -3.29722, 33.02 to \
  -0.03, 33.02 to \
  -0.03, 16.5968 to \
  -3.29722, 16.5968 to \
  -3.29722, 33.02 front fs empty border lc rgb '#549f' lw 0.1
set object 1640 polygon from \
  -3.32029, 33.041 to \
  -0.03, 33.041 to \
  -0.03, 16.6079 to \
  -3.32029, 16.6079 to \
  -3.32029, 33.041 front fs empty border lc rgb '#549f' lw 0.1
set object 1641 polygon from \
  -3.34243, 33.0621 to \
  -0.03, 33.0621 to \
  -0.03, 16.6189 to \
  -3.34243, 16.6189 to \
  -3.34243, 33.0621 front fs empty border lc rgb '#549f' lw 0.1
set object 1642 polygon from \
  -3.36363, 33.0831 to \
  -0.03, 33.0831 to \
  -0.03, 16.6299 to \
  -3.36363, 16.6299 to \
  -3.36363, 33.0831 front fs empty border lc rgb '#549f' lw 0.1
set object 1643 polygon from \
  -3.38387, 33.1042 to \
  -0.03, 33.1042 to \
  -0.03, 16.641 to \
  -3.38387, 16.641 to \
  -3.38387, 33.1042 front fs empty border lc rgb '#549f' lw 0.1
set object 1644 polygon from \
  -3.40316, 33.1252 to \
  -0.03, 33.1252 to \
  -0.03, 16.652 to \
  -3.40316, 16.652 to \
  -3.40316, 33.1252 front fs empty border lc rgb '#549f' lw 0.1
set object 1645 polygon from \
  -3.42146, 33.1463 to \
  -0.03, 33.1463 to \
  -0.03, 16.6631 to \
  -3.42146, 16.6631 to \
  -3.42146, 33.1463 front fs empty border lc rgb '#549f' lw 0.1
set object 1646 polygon from \
  -3.43878, 33.1673 to \
  -0.03, 33.1673 to \
  -0.03, 16.6742 to \
  -3.43878, 16.6742 to \
  -3.43878, 33.1673 front fs empty border lc rgb '#549f' lw 0.1
set object 1647 polygon from \
  -3.4551, 33.1884 to \
  -0.03, 33.1884 to \
  -0.03, 16.6852 to \
  -3.4551, 16.6852 to \
  -3.4551, 33.1884 front fs empty border lc rgb '#549f' lw 0.1
set object 1648 polygon from \
  -3.47041, 33.2094 to \
  -0.03, 33.2094 to \
  -0.03, 16.6963 to \
  -3.47041, 16.6963 to \
  -3.47041, 33.2094 front fs empty border lc rgb '#549f' lw 0.1
set object 1649 polygon from \
  -3.4847, 33.2305 to \
  -0.03, 33.2305 to \
  -0.03, 16.7073 to \
  -3.4847, 16.7073 to \
  -3.4847, 33.2305 front fs empty border lc rgb '#549f' lw 0.1
set object 1650 polygon from \
  -3.49796, 33.2516 to \
  -0.03, 33.2516 to \
  -0.03, 16.7184 to \
  -3.49796, 16.7184 to \
  -3.49796, 33.2516 front fs empty border lc rgb '#549f' lw 0.1
set object 1651 polygon from \
  -3.51017, 33.2726 to \
  -0.03, 33.2726 to \
  -0.03, 16.7294 to \
  -3.51017, 16.7294 to \
  -3.51017, 33.2726 front fs empty border lc rgb '#549f' lw 0.1
set object 1652 polygon from \
  -3.52134, 33.2937 to \
  -0.03, 33.2937 to \
  -0.03, 16.7405 to \
  -3.52134, 16.7405 to \
  -3.52134, 33.2937 front fs empty border lc rgb '#549f' lw 0.1
set object 1653 polygon from \
  -3.53145, 33.3148 to \
  -0.03, 33.3148 to \
  -0.03, 16.7516 to \
  -3.53145, 16.7516 to \
  -3.53145, 33.3148 front fs empty border lc rgb '#549f' lw 0.1
set object 1654 polygon from \
  -3.54049, 33.3358 to \
  -0.03, 33.3358 to \
  -0.03, 16.7626 to \
  -3.54049, 16.7626 to \
  -3.54049, 33.3358 front fs empty border lc rgb '#549f' lw 0.1
set object 1655 polygon from \
  -3.54846, 33.3569 to \
  -0.03, 33.3569 to \
  -0.03, 16.7737 to \
  -3.54846, 16.7737 to \
  -3.54846, 33.3569 front fs empty border lc rgb '#549f' lw 0.1
set object 1656 polygon from \
  -3.55934, 33.378 to \
  -0.03, 33.378 to \
  -0.03, 16.7848 to \
  -3.55934, 16.7848 to \
  -3.55934, 33.378 front fs empty border lc rgb '#549f' lw 0.1
set object 1657 polygon from \
  -3.56964, 33.399 to \
  -0.03, 33.399 to \
  -0.03, 16.7958 to \
  -3.56964, 16.7958 to \
  -3.56964, 33.399 front fs empty border lc rgb '#549f' lw 0.1
set object 1658 polygon from \
  -3.5789, 33.4201 to \
  -0.03, 33.4201 to \
  -0.03, 16.8069 to \
  -3.5789, 16.8069 to \
  -3.5789, 33.4201 front fs empty border lc rgb '#549f' lw 0.1
set object 1659 polygon from \
  -3.58713, 33.4412 to \
  -0.03, 33.4412 to \
  -0.03, 16.818 to \
  -3.58713, 16.818 to \
  -3.58713, 33.4412 front fs empty border lc rgb '#549f' lw 0.1
set object 1660 polygon from \
  -3.59432, 33.4622 to \
  -0.03, 33.4622 to \
  -0.03, 16.829 to \
  -3.59432, 16.829 to \
  -3.59432, 33.4622 front fs empty border lc rgb '#549f' lw 0.1
set object 1661 polygon from \
  -3.60047, 33.4833 to \
  -0.03, 33.4833 to \
  -0.03, 16.8401 to \
  -3.60047, 16.8401 to \
  -3.60047, 33.4833 front fs empty border lc rgb '#549f' lw 0.1
set object 1662 polygon from \
  -3.60555, 33.5044 to \
  -0.03, 33.5044 to \
  -0.03, 16.8512 to \
  -3.60555, 16.8512 to \
  -3.60555, 33.5044 front fs empty border lc rgb '#549f' lw 0.1
set object 1663 polygon from \
  -3.60958, 33.5255 to \
  -0.03, 33.5255 to \
  -0.03, 16.8622 to \
  -3.60958, 16.8622 to \
  -3.60958, 33.5255 front fs empty border lc rgb '#549f' lw 0.1
set object 1664 polygon from \
  -3.61254, 33.5466 to \
  -0.03, 33.5466 to \
  -0.03, 16.8733 to \
  -3.61254, 16.8733 to \
  -3.61254, 33.5466 front fs empty border lc rgb '#549f' lw 0.1
set object 1665 polygon from \
  -3.61442, 33.5676 to \
  -0.03, 33.5676 to \
  -0.03, 16.8844 to \
  -3.61442, 16.8844 to \
  -3.61442, 33.5676 front fs empty border lc rgb '#549f' lw 0.1
set object 1666 polygon from \
  -3.61522, 33.5887 to \
  -0.03, 33.5887 to \
  -0.03, 16.8955 to \
  -3.61522, 16.8955 to \
  -3.61522, 33.5887 front fs empty border lc rgb '#549f' lw 0.1
set object 1667 polygon from \
  -3.61522, 33.6098 to \
  -0.03, 33.6098 to \
  -0.03, 16.9066 to \
  -3.61522, 16.9066 to \
  -3.61522, 33.6098 front fs empty border lc rgb '#549f' lw 0.1
set object 1668 polygon from \
  -3.61494, 33.6309 to \
  -0.03, 33.6309 to \
  -0.03, 16.9176 to \
  -3.61494, 16.9176 to \
  -3.61494, 33.6309 front fs empty border lc rgb '#549f' lw 0.1
set object 1669 polygon from \
  -3.61358, 33.652 to \
  -0.03, 33.652 to \
  -0.03, 16.9287 to \
  -3.61358, 16.9287 to \
  -3.61358, 33.652 front fs empty border lc rgb '#549f' lw 0.1
set object 1670 polygon from \
  -3.61112, 33.6731 to \
  -0.03, 33.6731 to \
  -0.03, 16.9398 to \
  -3.61112, 16.9398 to \
  -3.61112, 33.6731 front fs empty border lc rgb '#549f' lw 0.1
set object 1671 polygon from \
  -3.60756, 33.6942 to \
  -0.03, 33.6942 to \
  -0.03, 16.9509 to \
  -3.60756, 16.9509 to \
  -3.60756, 33.6942 front fs empty border lc rgb '#549f' lw 0.1
set object 1672 polygon from \
  -3.60291, 33.7152 to \
  -0.03, 33.7152 to \
  -0.03, 16.962 to \
  -3.60291, 16.962 to \
  -3.60291, 33.7152 front fs empty border lc rgb '#549f' lw 0.1
set object 1673 polygon from \
  -3.59716, 33.7363 to \
  -0.03, 33.7363 to \
  -0.03, 16.9731 to \
  -3.59716, 16.9731 to \
  -3.59716, 33.7363 front fs empty border lc rgb '#549f' lw 0.1
set object 1674 polygon from \
  -3.59031, 33.7574 to \
  -0.03, 33.7574 to \
  -0.03, 16.9841 to \
  -3.59031, 16.9841 to \
  -3.59031, 33.7574 front fs empty border lc rgb '#549f' lw 0.1
set object 1675 polygon from \
  -3.58235, 33.7785 to \
  -0.03, 33.7785 to \
  -0.03, 16.9952 to \
  -3.58235, 16.9952 to \
  -3.58235, 33.7785 front fs empty border lc rgb '#549f' lw 0.1
set object 1676 polygon from \
  -3.5733, 33.7996 to \
  -0.03, 33.7996 to \
  -0.03, 17.0063 to \
  -3.5733, 17.0063 to \
  -3.5733, 33.7996 front fs empty border lc rgb '#549f' lw 0.1
set object 1677 polygon from \
  -3.56313, 33.8207 to \
  -0.03, 33.8207 to \
  -0.03, 17.0174 to \
  -3.56313, 17.0174 to \
  -3.56313, 33.8207 front fs empty border lc rgb '#549f' lw 0.1
set object 1678 polygon from \
  -3.56058, 33.8418 to \
  -0.03, 33.8418 to \
  -0.03, 17.0285 to \
  -3.56058, 17.0285 to \
  -3.56058, 33.8418 front fs empty border lc rgb '#549f' lw 0.1
set object 1679 polygon from \
  -3.55827, 33.8629 to \
  -0.03, 33.8629 to \
  -0.03, 17.0396 to \
  -3.55827, 17.0396 to \
  -3.55827, 33.8629 front fs empty border lc rgb '#549f' lw 0.1
set object 1680 polygon from \
  -3.55481, 33.884 to \
  -0.03, 33.884 to \
  -0.03, 17.0507 to \
  -3.55481, 17.0507 to \
  -3.55481, 33.884 front fs empty border lc rgb '#549f' lw 0.1
set object 1681 polygon from \
  -3.5502, 33.9051 to \
  -0.03, 33.9051 to \
  -0.03, 17.0618 to \
  -3.5502, 17.0618 to \
  -3.5502, 33.9051 front fs empty border lc rgb '#549f' lw 0.1
set object 1682 polygon from \
  -3.54445, 33.9262 to \
  -0.03, 33.9262 to \
  -0.03, 17.0729 to \
  -3.54445, 17.0729 to \
  -3.54445, 33.9262 front fs empty border lc rgb '#549f' lw 0.1
set object 1683 polygon from \
  -3.53755, 33.9473 to \
  -0.03, 33.9473 to \
  -0.03, 17.084 to \
  -3.53755, 17.084 to \
  -3.53755, 33.9473 front fs empty border lc rgb '#549f' lw 0.1
set object 1684 polygon from \
  -3.5295, 33.9684 to \
  -0.03, 33.9684 to \
  -0.03, 17.0951 to \
  -3.5295, 17.0951 to \
  -3.5295, 33.9684 front fs empty border lc rgb '#549f' lw 0.1
set object 1685 polygon from \
  -3.5203, 33.9895 to \
  -0.03, 33.9895 to \
  -0.03, 17.1062 to \
  -3.5203, 17.1062 to \
  -3.5203, 33.9895 front fs empty border lc rgb '#549f' lw 0.1
set object 1686 polygon from \
  -3.50995, 34.0106 to \
  -0.03, 34.0106 to \
  -0.03, 17.1173 to \
  -3.50995, 17.1173 to \
  -3.50995, 34.0106 front fs empty border lc rgb '#549f' lw 0.1
set object 1687 polygon from \
  -3.49846, 34.0317 to \
  -0.03, 34.0317 to \
  -0.03, 17.1284 to \
  -3.49846, 17.1284 to \
  -3.49846, 34.0317 front fs empty border lc rgb '#549f' lw 0.1
set object 1688 polygon from \
  -3.48582, 34.0528 to \
  -0.03, 34.0528 to \
  -0.03, 17.1395 to \
  -3.48582, 17.1395 to \
  -3.48582, 34.0528 front fs empty border lc rgb '#549f' lw 0.1
set object 1689 polygon from \
  -3.47205, 34.074 to \
  -0.03, 34.074 to \
  -0.03, 17.1506 to \
  -3.47205, 17.1506 to \
  -3.47205, 34.074 front fs empty border lc rgb '#549f' lw 0.1
set object 1690 polygon from \
  -3.45713, 34.0951 to \
  -0.03, 34.0951 to \
  -0.03, 17.1617 to \
  -3.45713, 17.1617 to \
  -3.45713, 34.0951 front fs empty border lc rgb '#549f' lw 0.1
set object 1691 polygon from \
  -3.44107, 34.1162 to \
  -0.03, 34.1162 to \
  -0.03, 17.1728 to \
  -3.44107, 17.1728 to \
  -3.44107, 34.1162 front fs empty border lc rgb '#549f' lw 0.1
set object 1692 polygon from \
  -3.42389, 34.1373 to \
  -0.03, 34.1373 to \
  -0.03, 17.1839 to \
  -3.42389, 17.1839 to \
  -3.42389, 34.1373 front fs empty border lc rgb '#549f' lw 0.1
set object 1693 polygon from \
  -3.40557, 34.1584 to \
  -0.03, 34.1584 to \
  -0.03, 17.1951 to \
  -3.40557, 17.1951 to \
  -3.40557, 34.1584 front fs empty border lc rgb '#549f' lw 0.1
set object 1694 polygon from \
  -3.38614, 34.1795 to \
  -0.03, 34.1795 to \
  -0.03, 17.2062 to \
  -3.38614, 17.2062 to \
  -3.38614, 34.1795 front fs empty border lc rgb '#549f' lw 0.1
set object 1695 polygon from \
  -3.36558, 34.2006 to \
  -0.03, 34.2006 to \
  -0.03, 17.2173 to \
  -3.36558, 17.2173 to \
  -3.36558, 34.2006 front fs empty border lc rgb '#549f' lw 0.1
set object 1696 polygon from \
  -3.34392, 34.2218 to \
  -0.03, 34.2218 to \
  -0.03, 17.2284 to \
  -3.34392, 17.2284 to \
  -3.34392, 34.2218 front fs empty border lc rgb '#549f' lw 0.1
set object 1697 polygon from \
  -3.32115, 34.2429 to \
  -0.03, 34.2429 to \
  -0.03, 17.2395 to \
  -3.32115, 17.2395 to \
  -3.32115, 34.2429 front fs empty border lc rgb '#549f' lw 0.1
set object 1698 polygon from \
  -3.29729, 34.264 to \
  -0.03, 34.264 to \
  -0.03, 17.2506 to \
  -3.29729, 17.2506 to \
  -3.29729, 34.264 front fs empty border lc rgb '#549f' lw 0.1
set object 1699 polygon from \
  -3.27234, 34.2851 to \
  -0.03, 34.2851 to \
  -0.03, 17.2618 to \
  -3.27234, 17.2618 to \
  -3.27234, 34.2851 front fs empty border lc rgb '#549f' lw 0.1
set object 1700 polygon from \
  -3.2463, 34.3062 to \
  -0.03, 34.3062 to \
  -0.03, 17.2729 to \
  -3.2463, 17.2729 to \
  -3.2463, 34.3062 front fs empty border lc rgb '#549f' lw 0.1
set object 1701 polygon from \
  -3.21919, 34.3274 to \
  -0.03, 34.3274 to \
  -0.03, 17.284 to \
  -3.21919, 17.284 to \
  -3.21919, 34.3274 front fs empty border lc rgb '#549f' lw 0.1
set object 1702 polygon from \
  -3.19102, 34.3485 to \
  -0.03, 34.3485 to \
  -0.03, 17.2951 to \
  -3.19102, 17.2951 to \
  -3.19102, 34.3485 front fs empty border lc rgb '#549f' lw 0.1
set object 1703 polygon from \
  -3.1618, 34.3696 to \
  -0.03, 34.3696 to \
  -0.03, 17.3062 to \
  -3.1618, 17.3062 to \
  -3.1618, 34.3696 front fs empty border lc rgb '#549f' lw 0.1
set object 1704 polygon from \
  -3.13153, 34.3908 to \
  -0.03, 34.3908 to \
  -0.03, 17.3174 to \
  -3.13153, 17.3174 to \
  -3.13153, 34.3908 front fs empty border lc rgb '#549f' lw 0.1
set object 1705 polygon from \
  -3.10022, 34.4119 to \
  -0.03, 34.4119 to \
  -0.03, 17.3285 to \
  -3.10022, 17.3285 to \
  -3.10022, 34.4119 front fs empty border lc rgb '#549f' lw 0.1
set object 1706 polygon from \
  -3.0679, 34.433 to \
  -0.03, 34.433 to \
  -0.03, 17.3396 to \
  -3.0679, 17.3396 to \
  -3.0679, 34.433 front fs empty border lc rgb '#549f' lw 0.1
set object 1707 polygon from \
  -3.03456, 34.4542 to \
  -0.03, 34.4542 to \
  -0.03, 17.3508 to \
  -3.03456, 17.3508 to \
  -3.03456, 34.4542 front fs empty border lc rgb '#549f' lw 0.1
set object 1708 polygon from \
  -3.00023, 34.4753 to \
  -0.03, 34.4753 to \
  -0.03, 17.3619 to \
  -3.00023, 17.3619 to \
  -3.00023, 34.4753 front fs empty border lc rgb '#549f' lw 0.1
set object 1709 polygon from \
  -2.96491, 34.4964 to \
  -0.03, 34.4964 to \
  -0.03, 17.373 to \
  -2.96491, 17.373 to \
  -2.96491, 34.4964 front fs empty border lc rgb '#549f' lw 0.1
set object 1710 polygon from \
  -2.92862, 34.5176 to \
  -0.03, 34.5176 to \
  -0.03, 17.3842 to \
  -2.92862, 17.3842 to \
  -2.92862, 34.5176 front fs empty border lc rgb '#549f' lw 0.1
set object 1711 polygon from \
  -2.89136, 34.5387 to \
  -0.03, 34.5387 to \
  -0.03, 17.3953 to \
  -2.89136, 17.3953 to \
  -2.89136, 34.5387 front fs empty border lc rgb '#549f' lw 0.1
set object 1712 polygon from \
  -2.85316, 34.5598 to \
  -0.03, 34.5598 to \
  -0.03, 17.4064 to \
  -2.85316, 17.4064 to \
  -2.85316, 34.5598 front fs empty border lc rgb '#549f' lw 0.1
set object 1713 polygon from \
  -2.81403, 34.581 to \
  -0.03, 34.581 to \
  -0.03, 17.4176 to \
  -2.81403, 17.4176 to \
  -2.81403, 34.581 front fs empty border lc rgb '#549f' lw 0.1
set object 1714 polygon from \
  -2.77399, 34.6021 to \
  -0.03, 34.6021 to \
  -0.03, 17.4287 to \
  -2.77399, 17.4287 to \
  -2.77399, 34.6021 front fs empty border lc rgb '#549f' lw 0.1
set object 1715 polygon from \
  -2.73304, 34.6233 to \
  -0.03, 34.6233 to \
  -0.03, 17.4398 to \
  -2.73304, 17.4398 to \
  -2.73304, 34.6233 front fs empty border lc rgb '#549f' lw 0.1
set object 1716 polygon from \
  -2.6912, 34.6444 to \
  -0.03, 34.6444 to \
  -0.03, 17.451 to \
  -2.6912, 17.451 to \
  -2.6912, 34.6444 front fs empty border lc rgb '#549f' lw 0.1
set object 1717 polygon from \
  -2.6485, 34.6656 to \
  -0.03, 34.6656 to \
  -0.03, 17.4621 to \
  -2.6485, 17.4621 to \
  -2.6485, 34.6656 front fs empty border lc rgb '#549f' lw 0.1
set object 1718 polygon from \
  -2.60494, 34.6867 to \
  -0.03, 34.6867 to \
  -0.03, 17.4733 to \
  -2.60494, 17.4733 to \
  -2.60494, 34.6867 front fs empty border lc rgb '#549f' lw 0.1
set object 1719 polygon from \
  -2.56054, 34.7079 to \
  -0.03, 34.7079 to \
  -0.03, 17.4844 to \
  -2.56054, 17.4844 to \
  -2.56054, 34.7079 front fs empty border lc rgb '#549f' lw 0.1
set object 1720 polygon from \
  -2.51533, 34.729 to \
  -0.03, 34.729 to \
  -0.03, 17.4956 to \
  -2.51533, 17.4956 to \
  -2.51533, 34.729 front fs empty border lc rgb '#549f' lw 0.1
set object 1721 polygon from \
  -2.46931, 34.7502 to \
  -0.03, 34.7502 to \
  -0.03, 17.5067 to \
  -2.46931, 17.5067 to \
  -2.46931, 34.7502 front fs empty border lc rgb '#549f' lw 0.1
set object 1722 polygon from \
  -2.4225, 34.7713 to \
  -0.03, 34.7713 to \
  -0.03, 17.5178 to \
  -2.4225, 17.5178 to \
  -2.4225, 34.7713 front fs empty border lc rgb '#549f' lw 0.1
set object 1723 polygon from \
  -2.37494, 34.7925 to \
  -0.03, 34.7925 to \
  -0.03, 17.529 to \
  -2.37494, 17.529 to \
  -2.37494, 34.7925 front fs empty border lc rgb '#549f' lw 0.1
set object 1724 polygon from \
  -2.32662, 34.8136 to \
  -0.03, 34.8136 to \
  -0.03, 17.5401 to \
  -2.32662, 17.5401 to \
  -2.32662, 34.8136 front fs empty border lc rgb '#549f' lw 0.1
set object 1725 polygon from \
  -2.27757, 34.8348 to \
  -0.03, 34.8348 to \
  -0.03, 17.5513 to \
  -2.27757, 17.5513 to \
  -2.27757, 34.8348 front fs empty border lc rgb '#549f' lw 0.1
set object 1726 polygon from \
  -2.22782, 34.8559 to \
  -0.03, 34.8559 to \
  -0.03, 17.5625 to \
  -2.22782, 17.5625 to \
  -2.22782, 34.8559 front fs empty border lc rgb '#549f' lw 0.1
set object 1727 polygon from \
  -2.17738, 34.8771 to \
  -0.03, 34.8771 to \
  -0.03, 17.5736 to \
  -2.17738, 17.5736 to \
  -2.17738, 34.8771 front fs empty border lc rgb '#549f' lw 0.1
set object 1728 polygon from \
  -2.12626, 34.8982 to \
  -0.03, 34.8982 to \
  -0.03, 17.5848 to \
  -2.12626, 17.5848 to \
  -2.12626, 34.8982 front fs empty border lc rgb '#549f' lw 0.1
set object 1729 polygon from \
  -2.0745, 34.9194 to \
  -0.03, 34.9194 to \
  -0.03, 17.5959 to \
  -2.0745, 17.5959 to \
  -2.0745, 34.9194 front fs empty border lc rgb '#549f' lw 0.1
set object 1730 polygon from \
  -2.02211, 34.9406 to \
  -0.03, 34.9406 to \
  -0.03, 17.6071 to \
  -2.02211, 17.6071 to \
  -2.02211, 34.9406 front fs empty border lc rgb '#549f' lw 0.1
set object 1731 polygon from \
  -1.9691, 34.9617 to \
  -0.03, 34.9617 to \
  -0.03, 17.6182 to \
  -1.9691, 17.6182 to \
  -1.9691, 34.9617 front fs empty border lc rgb '#549f' lw 0.1
set object 1732 polygon from \
  -1.91552, 34.9829 to \
  -0.03, 34.9829 to \
  -0.03, 17.6294 to \
  -1.91552, 17.6294 to \
  -1.91552, 34.9829 front fs empty border lc rgb '#549f' lw 0.1
set object 1733 polygon from \
  -1.86136, 35.0041 to \
  -0.03, 35.0041 to \
  -0.03, 17.6406 to \
  -1.86136, 17.6406 to \
  -1.86136, 35.0041 front fs empty border lc rgb '#549f' lw 0.1
set object 1734 polygon from \
  -1.80666, 35.0252 to \
  -0.03, 35.0252 to \
  -0.03, 17.6517 to \
  -1.80666, 17.6517 to \
  -1.80666, 35.0252 front fs empty border lc rgb '#549f' lw 0.1
set object 1735 polygon from \
  -1.75144, 35.0464 to \
  -0.03, 35.0464 to \
  -0.03, 17.6629 to \
  -1.75144, 17.6629 to \
  -1.75144, 35.0464 front fs empty border lc rgb '#549f' lw 0.1
set object 1736 polygon from \
  -1.69571, 35.0676 to \
  -0.03, 35.0676 to \
  -0.03, 17.6741 to \
  -1.69571, 17.6741 to \
  -1.69571, 35.0676 front fs empty border lc rgb '#549f' lw 0.1
set object 1737 polygon from \
  -1.63951, 35.0887 to \
  -0.03, 35.0887 to \
  -0.03, 17.6852 to \
  -1.63951, 17.6852 to \
  -1.63951, 35.0887 front fs empty border lc rgb '#549f' lw 0.1
set object 1738 polygon from \
  -1.58285, 35.1099 to \
  -0.03, 35.1099 to \
  -0.03, 17.6964 to \
  -1.58285, 17.6964 to \
  -1.58285, 35.1099 front fs empty border lc rgb '#549f' lw 0.1
set object 1739 polygon from \
  -1.52576, 35.1311 to \
  -0.03, 35.1311 to \
  -0.03, 17.7076 to \
  -1.52576, 17.7076 to \
  -1.52576, 35.1311 front fs empty border lc rgb '#549f' lw 0.1
set object 1740 polygon from \
  -1.46825, 35.1522 to \
  -0.03, 35.1522 to \
  -0.03, 17.7187 to \
  -1.46825, 17.7187 to \
  -1.46825, 35.1522 front fs empty border lc rgb '#549f' lw 0.1
set object 1741 polygon from \
  -1.41036, 35.1734 to \
  -0.03, 35.1734 to \
  -0.03, 17.7299 to \
  -1.41036, 17.7299 to \
  -1.41036, 35.1734 front fs empty border lc rgb '#549f' lw 0.1
set object 1742 polygon from \
  -1.3521, 35.1946 to \
  -0.03, 35.1946 to \
  -0.03, 17.7411 to \
  -1.3521, 17.7411 to \
  -1.3521, 35.1946 front fs empty border lc rgb '#549f' lw 0.1
set object 1743 polygon from \
  -1.2935, 35.2158 to \
  -0.03, 35.2158 to \
  -0.03, 17.7522 to \
  -1.2935, 17.7522 to \
  -1.2935, 35.2158 front fs empty border lc rgb '#549f' lw 0.1
set object 1744 polygon from \
  -1.23458, 35.237 to \
  -0.03, 35.237 to \
  -0.03, 17.7634 to \
  -1.23458, 17.7634 to \
  -1.23458, 35.237 front fs empty border lc rgb '#549f' lw 0.1
set object 1745 polygon from \
  -1.17537, 35.2581 to \
  -0.03, 35.2581 to \
  -0.03, 17.7746 to \
  -1.17537, 17.7746 to \
  -1.17537, 35.2581 front fs empty border lc rgb '#549f' lw 0.1
set object 1746 polygon from \
  -1.11588, 35.2793 to \
  -0.03, 35.2793 to \
  -0.03, 17.7858 to \
  -1.11588, 17.7858 to \
  -1.11588, 35.2793 front fs empty border lc rgb '#549f' lw 0.1
set object 1747 polygon from \
  -1.09208, 35.3005 to \
  -0.03, 35.3005 to \
  -0.03, 17.797 to \
  -1.09208, 17.797 to \
  -1.09208, 35.3005 front fs empty border lc rgb '#549f' lw 0.1
set object 1748 polygon from \
  -1.1244, 35.3217 to \
  -0.03, 35.3217 to \
  -0.03, 17.8081 to \
  -1.1244, 17.8081 to \
  -1.1244, 35.3217 front fs empty border lc rgb '#549f' lw 0.1
set object 1749 polygon from \
  -1.17381, 35.3429 to \
  -0.03, 35.3429 to \
  -0.03, 17.8193 to \
  -1.17381, 17.8193 to \
  -1.17381, 35.3429 front fs empty border lc rgb '#549f' lw 0.1
set object 1750 polygon from \
  -1.22284, 35.3641 to \
  -0.03, 35.3641 to \
  -0.03, 17.8305 to \
  -1.22284, 17.8305 to \
  -1.22284, 35.3641 front fs empty border lc rgb '#549f' lw 0.1
set object 1751 polygon from \
  -1.27146, 35.3853 to \
  -0.03, 35.3853 to \
  -0.03, 17.8417 to \
  -1.27146, 17.8417 to \
  -1.27146, 35.3853 front fs empty border lc rgb '#549f' lw 0.1
set object 1752 polygon from \
  -1.31964, 35.4064 to \
  -0.03, 35.4064 to \
  -0.03, 17.8529 to \
  -1.31964, 17.8529 to \
  -1.31964, 35.4064 front fs empty border lc rgb '#549f' lw 0.1
set object 1753 polygon from \
  -1.36734, 35.4276 to \
  -0.03, 35.4276 to \
  -0.03, 17.8641 to \
  -1.36734, 17.8641 to \
  -1.36734, 35.4276 front fs empty border lc rgb '#549f' lw 0.1
set object 1754 polygon from \
  -1.41454, 35.4488 to \
  -0.03, 35.4488 to \
  -0.03, 17.8752 to \
  -1.41454, 17.8752 to \
  -1.41454, 35.4488 front fs empty border lc rgb '#549f' lw 0.1
set object 1755 polygon from \
  -1.46236, 35.47 to \
  -0.03, 35.47 to \
  -0.03, 17.8864 to \
  -1.46236, 17.8864 to \
  -1.46236, 35.47 front fs empty border lc rgb '#549f' lw 0.1
set object 1756 polygon from \
  -1.51255, 35.4912 to \
  -0.03, 35.4912 to \
  -0.03, 17.8976 to \
  -1.51255, 17.8976 to \
  -1.51255, 35.4912 front fs empty border lc rgb '#549f' lw 0.1
set object 1757 polygon from \
  -1.56213, 35.5124 to \
  -0.03, 35.5124 to \
  -0.03, 17.9088 to \
  -1.56213, 17.9088 to \
  -1.56213, 35.5124 front fs empty border lc rgb '#549f' lw 0.1
set object 1758 polygon from \
  -1.61107, 35.5336 to \
  -0.03, 35.5336 to \
  -0.03, 17.92 to \
  -1.61107, 17.92 to \
  -1.61107, 35.5336 front fs empty border lc rgb '#549f' lw 0.1
set object 1759 polygon from \
  -1.65934, 35.5548 to \
  -0.03, 35.5548 to \
  -0.03, 17.9312 to \
  -1.65934, 17.9312 to \
  -1.65934, 35.5548 front fs empty border lc rgb '#549f' lw 0.1
set object 1760 polygon from \
  -1.70691, 35.576 to \
  -0.03, 35.576 to \
  -0.03, 17.9424 to \
  -1.70691, 17.9424 to \
  -1.70691, 35.576 front fs empty border lc rgb '#549f' lw 0.1
set object 1761 polygon from \
  -1.75374, 35.5972 to \
  -0.03, 35.5972 to \
  -0.03, 17.9536 to \
  -1.75374, 17.9536 to \
  -1.75374, 35.5972 front fs empty border lc rgb '#549f' lw 0.1
set object 1762 polygon from \
  -1.79981, 35.6184 to \
  -0.03, 35.6184 to \
  -0.03, 17.9648 to \
  -1.79981, 17.9648 to \
  -1.79981, 35.6184 front fs empty border lc rgb '#549f' lw 0.1
set object 1763 polygon from \
  -1.84509, 35.6396 to \
  -0.03, 35.6396 to \
  -0.03, 17.976 to \
  -1.84509, 17.976 to \
  -1.84509, 35.6396 front fs empty border lc rgb '#549f' lw 0.1
set object 1764 polygon from \
  -1.88955, 35.6608 to \
  -0.03, 35.6608 to \
  -0.03, 17.9872 to \
  -1.88955, 17.9872 to \
  -1.88955, 35.6608 front fs empty border lc rgb '#549f' lw 0.1
set object 1765 polygon from \
  -1.93316, 35.682 to \
  -0.03, 35.682 to \
  -0.03, 17.9984 to \
  -1.93316, 17.9984 to \
  -1.93316, 35.682 front fs empty border lc rgb '#549f' lw 0.1
set object 1766 polygon from \
  -1.97589, 35.7032 to \
  -0.03, 35.7032 to \
  -0.03, 18.0096 to \
  -1.97589, 18.0096 to \
  -1.97589, 35.7032 front fs empty border lc rgb '#549f' lw 0.1
set object 1767 polygon from \
  -2.01772, 35.7244 to \
  -0.03, 35.7244 to \
  -0.03, 18.0208 to \
  -2.01772, 18.0208 to \
  -2.01772, 35.7244 front fs empty border lc rgb '#549f' lw 0.1
set object 1768 polygon from \
  -2.0634, 35.7456 to \
  -0.03, 35.7456 to \
  -0.03, 18.032 to \
  -2.0634, 18.032 to \
  -2.0634, 35.7456 front fs empty border lc rgb '#549f' lw 0.1
set object 1769 polygon from \
  -2.11129, 35.7669 to \
  -0.03, 35.7669 to \
  -0.03, 18.0432 to \
  -2.11129, 18.0432 to \
  -2.11129, 35.7669 front fs empty border lc rgb '#549f' lw 0.1
set object 1770 polygon from \
  -2.15847, 35.7881 to \
  -0.03, 35.7881 to \
  -0.03, 18.0544 to \
  -2.15847, 18.0544 to \
  -2.15847, 35.7881 front fs empty border lc rgb '#549f' lw 0.1
set object 1771 polygon from \
  -2.20491, 35.8093 to \
  -0.03, 35.8093 to \
  -0.03, 18.0656 to \
  -2.20491, 18.0656 to \
  -2.20491, 35.8093 front fs empty border lc rgb '#549f' lw 0.1
set object 1772 polygon from \
  -2.25059, 35.8305 to \
  -0.03, 35.8305 to \
  -0.03, 18.0768 to \
  -2.25059, 18.0768 to \
  -2.25059, 35.8305 front fs empty border lc rgb '#549f' lw 0.1
set object 1773 polygon from \
  -2.2955, 35.8517 to \
  -0.03, 35.8517 to \
  -0.03, 18.0881 to \
  -2.2955, 18.0881 to \
  -2.2955, 35.8517 front fs empty border lc rgb '#549f' lw 0.1
set object 1774 polygon from \
  -2.33962, 35.8729 to \
  -0.03, 35.8729 to \
  -0.03, 18.0993 to \
  -2.33962, 18.0993 to \
  -2.33962, 35.8729 front fs empty border lc rgb '#549f' lw 0.1
set object 1775 polygon from \
  -2.38293, 35.8941 to \
  -0.03, 35.8941 to \
  -0.03, 18.1105 to \
  -2.38293, 18.1105 to \
  -2.38293, 35.8941 front fs empty border lc rgb '#549f' lw 0.1
set object 1776 polygon from \
  -2.42542, 35.9154 to \
  -0.03, 35.9154 to \
  -0.03, 18.1217 to \
  -2.42542, 18.1217 to \
  -2.42542, 35.9154 front fs empty border lc rgb '#549f' lw 0.1
set object 1777 polygon from \
  -2.46707, 35.9366 to \
  -0.03, 35.9366 to \
  -0.03, 18.1329 to \
  -2.46707, 18.1329 to \
  -2.46707, 35.9366 front fs empty border lc rgb '#549f' lw 0.1
set object 1778 polygon from \
  -2.50786, 35.9578 to \
  -0.03, 35.9578 to \
  -0.03, 18.1441 to \
  -2.50786, 18.1441 to \
  -2.50786, 35.9578 front fs empty border lc rgb '#549f' lw 0.1
set object 1779 polygon from \
  -2.54778, 35.979 to \
  -0.03, 35.979 to \
  -0.03, 18.1554 to \
  -2.54778, 18.1554 to \
  -2.54778, 35.979 front fs empty border lc rgb '#549f' lw 0.1
set object 1780 polygon from \
  -2.58681, 36.0002 to \
  -0.03, 36.0002 to \
  -0.03, 18.1666 to \
  -2.58681, 18.1666 to \
  -2.58681, 36.0002 front fs empty border lc rgb '#549f' lw 0.1
set object 1781 polygon from \
  -2.62495, 36.0215 to \
  -0.03, 36.0215 to \
  -0.03, 18.1778 to \
  -2.62495, 18.1778 to \
  -2.62495, 36.0215 front fs empty border lc rgb '#549f' lw 0.1
set object 1782 polygon from \
  -2.66217, 36.0427 to \
  -0.03, 36.0427 to \
  -0.03, 18.189 to \
  -2.66217, 18.189 to \
  -2.66217, 36.0427 front fs empty border lc rgb '#549f' lw 0.1
set object 1783 polygon from \
  -2.69846, 36.0639 to \
  -0.03, 36.0639 to \
  -0.03, 18.2002 to \
  -2.69846, 18.2002 to \
  -2.69846, 36.0639 front fs empty border lc rgb '#549f' lw 0.1
set object 1784 polygon from \
  -2.73381, 36.0852 to \
  -0.03, 36.0852 to \
  -0.03, 18.2115 to \
  -2.73381, 18.2115 to \
  -2.73381, 36.0852 front fs empty border lc rgb '#549f' lw 0.1
set object 1785 polygon from \
  -2.76821, 36.1064 to \
  -0.03, 36.1064 to \
  -0.03, 18.2227 to \
  -2.76821, 18.2227 to \
  -2.76821, 36.1064 front fs empty border lc rgb '#549f' lw 0.1
set object 1786 polygon from \
  -2.80164, 36.1276 to \
  -0.03, 36.1276 to \
  -0.03, 18.2339 to \
  -2.80164, 18.2339 to \
  -2.80164, 36.1276 front fs empty border lc rgb '#549f' lw 0.1
set object 1787 polygon from \
  -2.8341, 36.1489 to \
  -0.03, 36.1489 to \
  -0.03, 18.2452 to \
  -2.8341, 18.2452 to \
  -2.8341, 36.1489 front fs empty border lc rgb '#549f' lw 0.1
set object 1788 polygon from \
  -2.86557, 36.1701 to \
  -0.03, 36.1701 to \
  -0.03, 18.2564 to \
  -2.86557, 18.2564 to \
  -2.86557, 36.1701 front fs empty border lc rgb '#549f' lw 0.1
set object 1789 polygon from \
  -2.89603, 36.1913 to \
  -0.03, 36.1913 to \
  -0.03, 18.2676 to \
  -2.89603, 18.2676 to \
  -2.89603, 36.1913 front fs empty border lc rgb '#549f' lw 0.1
set object 1790 polygon from \
  -2.92549, 36.2126 to \
  -0.03, 36.2126 to \
  -0.03, 18.2789 to \
  -2.92549, 18.2789 to \
  -2.92549, 36.2126 front fs empty border lc rgb '#549f' lw 0.1
set object 1791 polygon from \
  -2.95393, 36.2338 to \
  -0.03, 36.2338 to \
  -0.03, 18.2901 to \
  -2.95393, 18.2901 to \
  -2.95393, 36.2338 front fs empty border lc rgb '#549f' lw 0.1
set object 1792 polygon from \
  -2.98135, 36.255 to \
  -0.03, 36.255 to \
  -0.03, 18.3013 to \
  -2.98135, 18.3013 to \
  -2.98135, 36.255 front fs empty border lc rgb '#549f' lw 0.1
set object 1793 polygon from \
  -3.00772, 36.2763 to \
  -0.03, 36.2763 to \
  -0.03, 18.3126 to \
  -3.00772, 18.3126 to \
  -3.00772, 36.2763 front fs empty border lc rgb '#549f' lw 0.1
set object 1794 polygon from \
  -3.03305, 36.2975 to \
  -0.03, 36.2975 to \
  -0.03, 18.3238 to \
  -3.03305, 18.3238 to \
  -3.03305, 36.2975 front fs empty border lc rgb '#549f' lw 0.1
set object 1795 polygon from \
  -3.05733, 36.3188 to \
  -0.03, 36.3188 to \
  -0.03, 18.335 to \
  -3.05733, 18.335 to \
  -3.05733, 36.3188 front fs empty border lc rgb '#549f' lw 0.1
set object 1796 polygon from \
  -3.08054, 36.34 to \
  -0.03, 36.34 to \
  -0.03, 18.3463 to \
  -3.08054, 18.3463 to \
  -3.08054, 36.34 front fs empty border lc rgb '#549f' lw 0.1
set object 1797 polygon from \
  -3.10269, 36.3613 to \
  -0.03, 36.3613 to \
  -0.03, 18.3575 to \
  -3.10269, 18.3575 to \
  -3.10269, 36.3613 front fs empty border lc rgb '#549f' lw 0.1
set object 1798 polygon from \
  -3.12377, 36.3825 to \
  -0.03, 36.3825 to \
  -0.03, 18.3688 to \
  -3.12377, 18.3688 to \
  -3.12377, 36.3825 front fs empty border lc rgb '#549f' lw 0.1
set object 1799 polygon from \
  -3.14377, 36.4038 to \
  -0.03, 36.4038 to \
  -0.03, 18.38 to \
  -3.14377, 18.38 to \
  -3.14377, 36.4038 front fs empty border lc rgb '#549f' lw 0.1
set object 1800 polygon from \
  -3.16268, 36.425 to \
  -0.03, 36.425 to \
  -0.03, 18.3913 to \
  -3.16268, 18.3913 to \
  -3.16268, 36.425 front fs empty border lc rgb '#549f' lw 0.1
set object 1801 polygon from \
  -3.1805, 36.4463 to \
  -0.03, 36.4463 to \
  -0.03, 18.4025 to \
  -3.1805, 18.4025 to \
  -3.1805, 36.4463 front fs empty border lc rgb '#549f' lw 0.1
set object 1802 polygon from \
  -3.19723, 36.4675 to \
  -0.03, 36.4675 to \
  -0.03, 18.4137 to \
  -3.19723, 18.4137 to \
  -3.19723, 36.4675 front fs empty border lc rgb '#549f' lw 0.1
set object 1803 polygon from \
  -3.21286, 36.4888 to \
  -0.03, 36.4888 to \
  -0.03, 18.425 to \
  -3.21286, 18.425 to \
  -3.21286, 36.4888 front fs empty border lc rgb '#549f' lw 0.1
set object 1804 polygon from \
  -3.2274, 36.51 to \
  -0.03, 36.51 to \
  -0.03, 18.4362 to \
  -3.2274, 18.4362 to \
  -3.2274, 36.51 front fs empty border lc rgb '#549f' lw 0.1
set object 1805 polygon from \
  -3.24082, 36.5313 to \
  -0.03, 36.5313 to \
  -0.03, 18.4475 to \
  -3.24082, 18.4475 to \
  -3.24082, 36.5313 front fs empty border lc rgb '#549f' lw 0.1
set object 1806 polygon from \
  -3.25315, 36.5525 to \
  -0.03, 36.5525 to \
  -0.03, 18.4588 to \
  -3.25315, 18.4588 to \
  -3.25315, 36.5525 front fs empty border lc rgb '#549f' lw 0.1
set object 1807 polygon from \
  -3.26437, 36.5738 to \
  -0.03, 36.5738 to \
  -0.03, 18.47 to \
  -3.26437, 18.47 to \
  -3.26437, 36.5738 front fs empty border lc rgb '#549f' lw 0.1
set object 1808 polygon from \
  -3.27447, 36.595 to \
  -0.03, 36.595 to \
  -0.03, 18.4813 to \
  -3.27447, 18.4813 to \
  -3.27447, 36.595 front fs empty border lc rgb '#549f' lw 0.1
set object 1809 polygon from \
  -3.28347, 36.6163 to \
  -0.03, 36.6163 to \
  -0.03, 18.4925 to \
  -3.28347, 18.4925 to \
  -3.28347, 36.6163 front fs empty border lc rgb '#549f' lw 0.1
set object 1810 polygon from \
  -3.29137, 36.6376 to \
  -0.03, 36.6376 to \
  -0.03, 18.5038 to \
  -3.29137, 18.5038 to \
  -3.29137, 36.6376 front fs empty border lc rgb '#549f' lw 0.1
set object 1811 polygon from \
  -3.29815, 36.6588 to \
  -0.03, 36.6588 to \
  -0.03, 18.515 to \
  -3.29815, 18.515 to \
  -3.29815, 36.6588 front fs empty border lc rgb '#549f' lw 0.1
set object 1812 polygon from \
  -3.30383, 36.6801 to \
  -0.03, 36.6801 to \
  -0.03, 18.5263 to \
  -3.30383, 18.5263 to \
  -3.30383, 36.6801 front fs empty border lc rgb '#549f' lw 0.1
set object 1813 polygon from \
  -3.3084, 36.7014 to \
  -0.03, 36.7014 to \
  -0.03, 18.5376 to \
  -3.3084, 18.5376 to \
  -3.3084, 36.7014 front fs empty border lc rgb '#549f' lw 0.1
set object 1814 polygon from \
  -3.31186, 36.7226 to \
  -0.03, 36.7226 to \
  -0.03, 18.5488 to \
  -3.31186, 18.5488 to \
  -3.31186, 36.7226 front fs empty border lc rgb '#549f' lw 0.1
set object 1815 polygon from \
  -3.31423, 36.7439 to \
  -0.03, 36.7439 to \
  -0.03, 18.5601 to \
  -3.31423, 18.5601 to \
  -3.31423, 36.7439 front fs empty border lc rgb '#549f' lw 0.1
set object 1816 polygon from \
  -3.31549, 36.7652 to \
  -0.03, 36.7652 to \
  -0.03, 18.5714 to \
  -3.31549, 18.5714 to \
  -3.31549, 36.7652 front fs empty border lc rgb '#549f' lw 0.1
set object 1817 polygon from \
  -3.31566, 36.7864 to \
  -0.03, 36.7864 to \
  -0.03, 18.5826 to \
  -3.31566, 18.5826 to \
  -3.31566, 36.7864 front fs empty border lc rgb '#549f' lw 0.1
set object 1818 polygon from \
  -3.31566, 36.8077 to \
  -0.03, 36.8077 to \
  -0.03, 18.5939 to \
  -3.31566, 18.5939 to \
  -3.31566, 36.8077 front fs empty border lc rgb '#549f' lw 0.1
set object 1819 polygon from \
  -3.31474, 36.829 to \
  -0.03, 36.829 to \
  -0.03, 18.6052 to \
  -3.31474, 18.6052 to \
  -3.31474, 36.829 front fs empty border lc rgb '#549f' lw 0.1
set object 1820 polygon from \
  -3.32008, 36.8502 to \
  -0.03, 36.8502 to \
  -0.03, 18.6164 to \
  -3.32008, 18.6164 to \
  -3.32008, 36.8502 front fs empty border lc rgb '#549f' lw 0.1
set object 1821 polygon from \
  -3.32583, 36.8715 to \
  -0.03, 36.8715 to \
  -0.03, 18.6277 to \
  -3.32583, 18.6277 to \
  -3.32583, 36.8715 front fs empty border lc rgb '#549f' lw 0.1
set object 1822 polygon from \
  -3.33052, 36.8928 to \
  -0.03, 36.8928 to \
  -0.03, 18.639 to \
  -3.33052, 18.639 to \
  -3.33052, 36.8928 front fs empty border lc rgb '#549f' lw 0.1
set object 1823 polygon from \
  -3.33418, 36.9141 to \
  -0.03, 36.9141 to \
  -0.03, 18.6502 to \
  -3.33418, 18.6502 to \
  -3.33418, 36.9141 front fs empty border lc rgb '#549f' lw 0.1
set object 1824 polygon from \
  -3.33679, 36.9354 to \
  -0.03, 36.9354 to \
  -0.03, 18.6615 to \
  -3.33679, 18.6615 to \
  -3.33679, 36.9354 front fs empty border lc rgb '#549f' lw 0.1
set object 1825 polygon from \
  -3.33836, 36.9566 to \
  -0.03, 36.9566 to \
  -0.03, 18.6728 to \
  -3.33836, 18.6728 to \
  -3.33836, 36.9566 front fs empty border lc rgb '#549f' lw 0.1
set object 1826 polygon from \
  -3.3389, 36.9779 to \
  -0.03, 36.9779 to \
  -0.03, 18.6841 to \
  -3.3389, 18.6841 to \
  -3.3389, 36.9779 front fs empty border lc rgb '#549f' lw 0.1
set object 1827 polygon from \
  -3.3389, 36.9992 to \
  -0.03, 36.9992 to \
  -0.03, 18.6954 to \
  -3.3389, 18.6954 to \
  -3.3389, 36.9992 front fs empty border lc rgb '#549f' lw 0.1
set object 1828 polygon from \
  -3.33842, 37.0205 to \
  -0.03, 37.0205 to \
  -0.03, 18.7066 to \
  -3.33842, 18.7066 to \
  -3.33842, 37.0205 front fs empty border lc rgb '#549f' lw 0.1
set object 1829 polygon from \
  -3.33691, 37.0418 to \
  -0.03, 37.0418 to \
  -0.03, 18.7179 to \
  -3.33691, 18.7179 to \
  -3.33691, 37.0418 front fs empty border lc rgb '#549f' lw 0.1
set object 1830 polygon from \
  -3.33438, 37.0631 to \
  -0.03, 37.0631 to \
  -0.03, 18.7292 to \
  -3.33438, 18.7292 to \
  -3.33438, 37.0631 front fs empty border lc rgb '#549f' lw 0.1
set object 1831 polygon from \
  -3.33084, 37.0844 to \
  -0.03, 37.0844 to \
  -0.03, 18.7405 to \
  -3.33084, 18.7405 to \
  -3.33084, 37.0844 front fs empty border lc rgb '#549f' lw 0.1
set object 1832 polygon from \
  -3.3263, 37.1056 to \
  -0.03, 37.1056 to \
  -0.03, 18.7518 to \
  -3.3263, 18.7518 to \
  -3.3263, 37.1056 front fs empty border lc rgb '#549f' lw 0.1
set object 1833 polygon from \
  -3.32075, 37.1269 to \
  -0.03, 37.1269 to \
  -0.03, 18.7631 to \
  -3.32075, 18.7631 to \
  -3.32075, 37.1269 front fs empty border lc rgb '#549f' lw 0.1
set object 1834 polygon from \
  -3.31422, 37.1482 to \
  -0.03, 37.1482 to \
  -0.03, 18.7743 to \
  -3.31422, 18.7743 to \
  -3.31422, 37.1482 front fs empty border lc rgb '#549f' lw 0.1
set object 1835 polygon from \
  -3.30671, 37.1695 to \
  -0.03, 37.1695 to \
  -0.03, 18.7856 to \
  -3.30671, 18.7856 to \
  -3.30671, 37.1695 front fs empty border lc rgb '#549f' lw 0.1
set object 1836 polygon from \
  -3.29822, 37.1908 to \
  -0.03, 37.1908 to \
  -0.03, 18.7969 to \
  -3.29822, 18.7969 to \
  -3.29822, 37.1908 front fs empty border lc rgb '#549f' lw 0.1
set object 1837 polygon from \
  -3.28876, 37.2121 to \
  -0.03, 37.2121 to \
  -0.03, 18.8082 to \
  -3.28876, 18.8082 to \
  -3.28876, 37.2121 front fs empty border lc rgb '#549f' lw 0.1
set object 1838 polygon from \
  -3.27835, 37.2334 to \
  -0.03, 37.2334 to \
  -0.03, 18.8195 to \
  -3.27835, 18.8195 to \
  -3.27835, 37.2334 front fs empty border lc rgb '#549f' lw 0.1
set object 1839 polygon from \
  -3.26698, 37.2547 to \
  -0.03, 37.2547 to \
  -0.03, 18.8308 to \
  -3.26698, 18.8308 to \
  -3.26698, 37.2547 front fs empty border lc rgb '#549f' lw 0.1
set object 1840 polygon from \
  -3.25468, 37.276 to \
  -0.03, 37.276 to \
  -0.03, 18.8421 to \
  -3.25468, 18.8421 to \
  -3.25468, 37.276 front fs empty border lc rgb '#549f' lw 0.1
set object 1841 polygon from \
  -3.24451, 37.2973 to \
  -0.03, 37.2973 to \
  -0.03, 18.8534 to \
  -3.24451, 18.8534 to \
  -3.24451, 37.2973 front fs empty border lc rgb '#549f' lw 0.1
set object 1842 polygon from \
  -3.23397, 37.3186 to \
  -0.03, 37.3186 to \
  -0.03, 18.8647 to \
  -3.23397, 18.8647 to \
  -3.23397, 37.3186 front fs empty border lc rgb '#549f' lw 0.1
set object 1843 polygon from \
  -3.22242, 37.3399 to \
  -0.03, 37.3399 to \
  -0.03, 18.876 to \
  -3.22242, 18.876 to \
  -3.22242, 37.3399 front fs empty border lc rgb '#549f' lw 0.1
set object 1844 polygon from \
  -3.20989, 37.3612 to \
  -0.03, 37.3612 to \
  -0.03, 18.8873 to \
  -3.20989, 18.8873 to \
  -3.20989, 37.3612 front fs empty border lc rgb '#549f' lw 0.1
set object 1845 polygon from \
  -3.19639, 37.3825 to \
  -0.03, 37.3825 to \
  -0.03, 18.8986 to \
  -3.19639, 18.8986 to \
  -3.19639, 37.3825 front fs empty border lc rgb '#549f' lw 0.1
set object 1846 polygon from \
  -3.18191, 37.4038 to \
  -0.03, 37.4038 to \
  -0.03, 18.9099 to \
  -3.18191, 18.9099 to \
  -3.18191, 37.4038 front fs empty border lc rgb '#549f' lw 0.1
set object 1847 polygon from \
  -3.16648, 37.4251 to \
  -0.03, 37.4251 to \
  -0.03, 18.9212 to \
  -3.16648, 18.9212 to \
  -3.16648, 37.4251 front fs empty border lc rgb '#549f' lw 0.1
set object 1848 polygon from \
  -3.15011, 37.4464 to \
  -0.03, 37.4464 to \
  -0.03, 18.9325 to \
  -3.15011, 18.9325 to \
  -3.15011, 37.4464 front fs empty border lc rgb '#549f' lw 0.1
set object 1849 polygon from \
  -3.1328, 37.4678 to \
  -0.03, 37.4678 to \
  -0.03, 18.9438 to \
  -3.1328, 18.9438 to \
  -3.1328, 37.4678 front fs empty border lc rgb '#549f' lw 0.1
set object 1850 polygon from \
  -3.11457, 37.4891 to \
  -0.03, 37.4891 to \
  -0.03, 18.9551 to \
  -3.11457, 18.9551 to \
  -3.11457, 37.4891 front fs empty border lc rgb '#549f' lw 0.1
set object 1851 polygon from \
  -3.09544, 37.5104 to \
  -0.03, 37.5104 to \
  -0.03, 18.9664 to \
  -3.09544, 18.9664 to \
  -3.09544, 37.5104 front fs empty border lc rgb '#549f' lw 0.1
set object 1852 polygon from \
  -3.0754, 37.5317 to \
  -0.03, 37.5317 to \
  -0.03, 18.9777 to \
  -3.0754, 18.9777 to \
  -3.0754, 37.5317 front fs empty border lc rgb '#549f' lw 0.1
set object 1853 polygon from \
  -3.05448, 37.553 to \
  -0.03, 37.553 to \
  -0.03, 18.9891 to \
  -3.05448, 18.9891 to \
  -3.05448, 37.553 front fs empty border lc rgb '#549f' lw 0.1
set object 1854 polygon from \
  -3.03269, 37.5743 to \
  -0.03, 37.5743 to \
  -0.03, 19.0004 to \
  -3.03269, 19.0004 to \
  -3.03269, 37.5743 front fs empty border lc rgb '#549f' lw 0.1
set object 1855 polygon from \
  -3.01005, 37.5956 to \
  -0.03, 37.5956 to \
  -0.03, 19.0117 to \
  -3.01005, 19.0117 to \
  -3.01005, 37.5956 front fs empty border lc rgb '#549f' lw 0.1
set object 1856 polygon from \
  -2.98656, 37.617 to \
  -0.03, 37.617 to \
  -0.03, 19.023 to \
  -2.98656, 19.023 to \
  -2.98656, 37.617 front fs empty border lc rgb '#549f' lw 0.1
set object 1857 polygon from \
  -2.96224, 37.6383 to \
  -0.03, 37.6383 to \
  -0.03, 19.0343 to \
  -2.96224, 19.0343 to \
  -2.96224, 37.6383 front fs empty border lc rgb '#549f' lw 0.1
set object 1858 polygon from \
  -2.93711, 37.6596 to \
  -0.03, 37.6596 to \
  -0.03, 19.0456 to \
  -2.93711, 19.0456 to \
  -2.93711, 37.6596 front fs empty border lc rgb '#549f' lw 0.1
set object 1859 polygon from \
  -2.91118, 37.6809 to \
  -0.03, 37.6809 to \
  -0.03, 19.057 to \
  -2.91118, 19.057 to \
  -2.91118, 37.6809 front fs empty border lc rgb '#549f' lw 0.1
set object 1860 polygon from \
  -2.88446, 37.7022 to \
  -0.03, 37.7022 to \
  -0.03, 19.0683 to \
  -2.88446, 19.0683 to \
  -2.88446, 37.7022 front fs empty border lc rgb '#549f' lw 0.1
set object 1861 polygon from \
  -2.85698, 37.7236 to \
  -0.03, 37.7236 to \
  -0.03, 19.0796 to \
  -2.85698, 19.0796 to \
  -2.85698, 37.7236 front fs empty border lc rgb '#549f' lw 0.1
set object 1862 polygon from \
  -2.82874, 37.7449 to \
  -0.03, 37.7449 to \
  -0.03, 19.0909 to \
  -2.82874, 19.0909 to \
  -2.82874, 37.7449 front fs empty border lc rgb '#549f' lw 0.1
set object 1863 polygon from \
  -2.79976, 37.7662 to \
  -0.03, 37.7662 to \
  -0.03, 19.1022 to \
  -2.79976, 19.1022 to \
  -2.79976, 37.7662 front fs empty border lc rgb '#549f' lw 0.1
set object 1864 polygon from \
  -2.77006, 37.7876 to \
  -0.03, 37.7876 to \
  -0.03, 19.1136 to \
  -2.77006, 19.1136 to \
  -2.77006, 37.7876 front fs empty border lc rgb '#549f' lw 0.1
set object 1865 polygon from \
  -2.73966, 37.8089 to \
  -0.03, 37.8089 to \
  -0.03, 19.1249 to \
  -2.73966, 19.1249 to \
  -2.73966, 37.8089 front fs empty border lc rgb '#549f' lw 0.1
set object 1866 polygon from \
  -2.70857, 37.8302 to \
  -0.03, 37.8302 to \
  -0.03, 19.1362 to \
  -2.70857, 19.1362 to \
  -2.70857, 37.8302 front fs empty border lc rgb '#549f' lw 0.1
set object 1867 polygon from \
  -2.6768, 37.8516 to \
  -0.03, 37.8516 to \
  -0.03, 19.1476 to \
  -2.6768, 19.1476 to \
  -2.6768, 37.8516 front fs empty border lc rgb '#549f' lw 0.1
set object 1868 polygon from \
  -2.64438, 37.8729 to \
  -0.03, 37.8729 to \
  -0.03, 19.1589 to \
  -2.64438, 19.1589 to \
  -2.64438, 37.8729 front fs empty border lc rgb '#549f' lw 0.1
set object 1869 polygon from \
  -2.61133, 37.8942 to \
  -0.03, 37.8942 to \
  -0.03, 19.1702 to \
  -2.61133, 19.1702 to \
  -2.61133, 37.8942 front fs empty border lc rgb '#549f' lw 0.1
set object 1870 polygon from \
  -2.57765, 37.9156 to \
  -0.03, 37.9156 to \
  -0.03, 19.1816 to \
  -2.57765, 19.1816 to \
  -2.57765, 37.9156 front fs empty border lc rgb '#549f' lw 0.1
set object 1871 polygon from \
  -2.54337, 37.9369 to \
  -0.03, 37.9369 to \
  -0.03, 19.1929 to \
  -2.54337, 19.1929 to \
  -2.54337, 37.9369 front fs empty border lc rgb '#549f' lw 0.1
set object 1872 polygon from \
  -2.50851, 37.9582 to \
  -0.03, 37.9582 to \
  -0.03, 19.2042 to \
  -2.50851, 19.2042 to \
  -2.50851, 37.9582 front fs empty border lc rgb '#549f' lw 0.1
set object 1873 polygon from \
  -2.47307, 37.9796 to \
  -0.03, 37.9796 to \
  -0.03, 19.2156 to \
  -2.47307, 19.2156 to \
  -2.47307, 37.9796 front fs empty border lc rgb '#549f' lw 0.1
set object 1874 polygon from \
  -2.43709, 38.0009 to \
  -0.03, 38.0009 to \
  -0.03, 19.2269 to \
  -2.43709, 19.2269 to \
  -2.43709, 38.0009 front fs empty border lc rgb '#549f' lw 0.1
set object 1875 polygon from \
  -2.40058, 38.0223 to \
  -0.03, 38.0223 to \
  -0.03, 19.2382 to \
  -2.40058, 19.2382 to \
  -2.40058, 38.0223 front fs empty border lc rgb '#549f' lw 0.1
set object 1876 polygon from \
  -2.39455, 38.0436 to \
  -0.03, 38.0436 to \
  -0.03, 19.2496 to \
  -2.39455, 19.2496 to \
  -2.39455, 38.0436 front fs empty border lc rgb '#549f' lw 0.1
set object 1877 polygon from \
  -2.39921, 38.065 to \
  -0.03, 38.065 to \
  -0.03, 19.2609 to \
  -2.39921, 19.2609 to \
  -2.39921, 38.065 front fs empty border lc rgb '#549f' lw 0.1
set object 1878 polygon from \
  -2.40303, 38.0863 to \
  -0.03, 38.0863 to \
  -0.03, 19.2723 to \
  -2.40303, 19.2723 to \
  -2.40303, 38.0863 front fs empty border lc rgb '#549f' lw 0.1
set object 1879 polygon from \
  -2.40601, 38.1077 to \
  -0.03, 38.1077 to \
  -0.03, 19.2836 to \
  -2.40601, 19.2836 to \
  -2.40601, 38.1077 front fs empty border lc rgb '#549f' lw 0.1
set object 1880 polygon from \
  -2.40813, 38.129 to \
  -0.03, 38.129 to \
  -0.03, 19.295 to \
  -2.40813, 19.295 to \
  -2.40813, 38.129 front fs empty border lc rgb '#549f' lw 0.1
set object 1881 polygon from \
  -2.41239, 38.1504 to \
  -0.03, 38.1504 to \
  -0.03, 19.3063 to \
  -2.41239, 19.3063 to \
  -2.41239, 38.1504 front fs empty border lc rgb '#549f' lw 0.1
set object 1882 polygon from \
  -2.42325, 38.1717 to \
  -0.03, 38.1717 to \
  -0.03, 19.3176 to \
  -2.42325, 19.3176 to \
  -2.42325, 38.1717 front fs empty border lc rgb '#549f' lw 0.1
set object 1883 polygon from \
  -2.43325, 38.1931 to \
  -0.03, 38.1931 to \
  -0.03, 19.329 to \
  -2.43325, 19.329 to \
  -2.43325, 38.1931 front fs empty border lc rgb '#549f' lw 0.1
set object 1884 polygon from \
  -2.44238, 38.2144 to \
  -0.03, 38.2144 to \
  -0.03, 19.3403 to \
  -2.44238, 19.3403 to \
  -2.44238, 38.2144 front fs empty border lc rgb '#549f' lw 0.1
set object 1885 polygon from \
  -2.45062, 38.2358 to \
  -0.03, 38.2358 to \
  -0.03, 19.3517 to \
  -2.45062, 19.3517 to \
  -2.45062, 38.2358 front fs empty border lc rgb '#549f' lw 0.1
set object 1886 polygon from \
  -2.45796, 38.2571 to \
  -0.03, 38.2571 to \
  -0.03, 19.3631 to \
  -2.45796, 19.3631 to \
  -2.45796, 38.2571 front fs empty border lc rgb '#549f' lw 0.1
set object 1887 polygon from \
  -2.4644, 38.2785 to \
  -0.03, 38.2785 to \
  -0.03, 19.3744 to \
  -2.4644, 19.3744 to \
  -2.4644, 38.2785 front fs empty border lc rgb '#549f' lw 0.1
set object 1888 polygon from \
  -2.46991, 38.2998 to \
  -0.03, 38.2998 to \
  -0.03, 19.3858 to \
  -2.46991, 19.3858 to \
  -2.46991, 38.2998 front fs empty border lc rgb '#549f' lw 0.1
set object 1889 polygon from \
  -2.47449, 38.3212 to \
  -0.03, 38.3212 to \
  -0.03, 19.3971 to \
  -2.47449, 19.3971 to \
  -2.47449, 38.3212 front fs empty border lc rgb '#549f' lw 0.1
set object 1890 polygon from \
  -2.47814, 38.3426 to \
  -0.03, 38.3426 to \
  -0.03, 19.4085 to \
  -2.47814, 19.4085 to \
  -2.47814, 38.3426 front fs empty border lc rgb '#549f' lw 0.1
set object 1891 polygon from \
  -2.48083, 38.3639 to \
  -0.03, 38.3639 to \
  -0.03, 19.4198 to \
  -2.48083, 19.4198 to \
  -2.48083, 38.3639 front fs empty border lc rgb '#549f' lw 0.1
set object 1892 polygon from \
  -2.48257, 38.3853 to \
  -0.03, 38.3853 to \
  -0.03, 19.4312 to \
  -2.48257, 19.4312 to \
  -2.48257, 38.3853 front fs empty border lc rgb '#549f' lw 0.1
set object 1893 polygon from \
  -2.48334, 38.4067 to \
  -0.03, 38.4067 to \
  -0.03, 19.4426 to \
  -2.48334, 19.4426 to \
  -2.48334, 38.4067 front fs empty border lc rgb '#549f' lw 0.1
set object 1894 polygon from \
  -2.48334, 38.428 to \
  -0.03, 38.428 to \
  -0.03, 19.4539 to \
  -2.48334, 19.4539 to \
  -2.48334, 38.428 front fs empty border lc rgb '#549f' lw 0.1
set object 1895 polygon from \
  -2.48313, 38.4494 to \
  -0.03, 38.4494 to \
  -0.03, 19.4653 to \
  -2.48313, 19.4653 to \
  -2.48313, 38.4494 front fs empty border lc rgb '#549f' lw 0.1
set object 1896 polygon from \
  -2.48194, 38.4708 to \
  -0.03, 38.4708 to \
  -0.03, 19.4767 to \
  -2.48194, 19.4767 to \
  -2.48194, 38.4708 front fs empty border lc rgb '#549f' lw 0.1
set object 1897 polygon from \
  -2.47977, 38.4921 to \
  -0.03, 38.4921 to \
  -0.03, 19.488 to \
  -2.47977, 19.488 to \
  -2.47977, 38.4921 front fs empty border lc rgb '#549f' lw 0.1
set object 1898 polygon from \
  -2.47659, 38.5135 to \
  -0.03, 38.5135 to \
  -0.03, 19.4994 to \
  -2.47659, 19.4994 to \
  -2.47659, 38.5135 front fs empty border lc rgb '#549f' lw 0.1
set object 1899 polygon from \
  -2.47242, 38.5349 to \
  -0.03, 38.5349 to \
  -0.03, 19.5108 to \
  -2.47242, 19.5108 to \
  -2.47242, 38.5349 front fs empty border lc rgb '#549f' lw 0.1
set object 1900 polygon from \
  -2.46723, 38.5562 to \
  -0.03, 38.5562 to \
  -0.03, 19.5221 to \
  -2.46723, 19.5221 to \
  -2.46723, 38.5562 front fs empty border lc rgb '#549f' lw 0.1
set object 1901 polygon from \
  -2.46104, 38.5776 to \
  -0.03, 38.5776 to \
  -0.03, 19.5335 to \
  -2.46104, 19.5335 to \
  -2.46104, 38.5776 front fs empty border lc rgb '#549f' lw 0.1
set object 1902 polygon from \
  -2.45382, 38.599 to \
  -0.03, 38.599 to \
  -0.03, 19.5449 to \
  -2.45382, 19.5449 to \
  -2.45382, 38.599 front fs empty border lc rgb '#549f' lw 0.1
set object 1903 polygon from \
  -2.44559, 38.6204 to \
  -0.03, 38.6204 to \
  -0.03, 19.5562 to \
  -2.44559, 19.5562 to \
  -2.44559, 38.6204 front fs empty border lc rgb '#549f' lw 0.1
set object 1904 polygon from \
  -2.43633, 38.6418 to \
  -0.03, 38.6418 to \
  -0.03, 19.5676 to \
  -2.43633, 19.5676 to \
  -2.43633, 38.6418 front fs empty border lc rgb '#549f' lw 0.1
set object 1905 polygon from \
  -2.42605, 38.6631 to \
  -0.03, 38.6631 to \
  -0.03, 19.579 to \
  -2.42605, 19.579 to \
  -2.42605, 38.6631 front fs empty border lc rgb '#549f' lw 0.1
set object 1906 polygon from \
  -2.41473, 38.6845 to \
  -0.03, 38.6845 to \
  -0.03, 19.5904 to \
  -2.41473, 19.5904 to \
  -2.41473, 38.6845 front fs empty border lc rgb '#549f' lw 0.1
set object 1907 polygon from \
  -2.40239, 38.7059 to \
  -0.03, 38.7059 to \
  -0.03, 19.6018 to \
  -2.40239, 19.6018 to \
  -2.40239, 38.7059 front fs empty border lc rgb '#549f' lw 0.1
set object 1908 polygon from \
  -2.38901, 38.7273 to \
  -0.03, 38.7273 to \
  -0.03, 19.6131 to \
  -2.38901, 19.6131 to \
  -2.38901, 38.7273 front fs empty border lc rgb '#549f' lw 0.1
set object 1909 polygon from \
  -2.3746, 38.7487 to \
  -0.03, 38.7487 to \
  -0.03, 19.6245 to \
  -2.3746, 19.6245 to \
  -2.3746, 38.7487 front fs empty border lc rgb '#549f' lw 0.1
set object 1910 polygon from \
  -2.35915, 38.7701 to \
  -0.03, 38.7701 to \
  -0.03, 19.6359 to \
  -2.35915, 19.6359 to \
  -2.35915, 38.7701 front fs empty border lc rgb '#549f' lw 0.1
set object 1911 polygon from \
  -2.34267, 38.7915 to \
  -0.03, 38.7915 to \
  -0.03, 19.6473 to \
  -2.34267, 19.6473 to \
  -2.34267, 38.7915 front fs empty border lc rgb '#549f' lw 0.1
set object 1912 polygon from \
  -2.32516, 38.8128 to \
  -0.03, 38.8128 to \
  -0.03, 19.6587 to \
  -2.32516, 19.6587 to \
  -2.32516, 38.8128 front fs empty border lc rgb '#549f' lw 0.1
set object 1913 polygon from \
  -2.30662, 38.8342 to \
  -0.03, 38.8342 to \
  -0.03, 19.6701 to \
  -2.30662, 19.6701 to \
  -2.30662, 38.8342 front fs empty border lc rgb '#549f' lw 0.1
set object 1914 polygon from \
  -2.28705, 38.8556 to \
  -0.03, 38.8556 to \
  -0.03, 19.6814 to \
  -2.28705, 19.6814 to \
  -2.28705, 38.8556 front fs empty border lc rgb '#549f' lw 0.1
set object 1915 polygon from \
  -2.26905, 38.877 to \
  -0.03, 38.877 to \
  -0.03, 19.6928 to \
  -2.26905, 19.6928 to \
  -2.26905, 38.877 front fs empty border lc rgb '#549f' lw 0.1
set object 1916 polygon from \
  -2.25048, 38.8984 to \
  -0.03, 38.8984 to \
  -0.03, 19.7042 to \
  -2.25048, 19.7042 to \
  -2.25048, 38.8984 front fs empty border lc rgb '#549f' lw 0.1
set object 1917 polygon from \
  -2.23092, 38.9198 to \
  -0.03, 38.9198 to \
  -0.03, 19.7156 to \
  -2.23092, 19.7156 to \
  -2.23092, 38.9198 front fs empty border lc rgb '#549f' lw 0.1
set object 1918 polygon from \
  -2.21037, 38.9412 to \
  -0.03, 38.9412 to \
  -0.03, 19.727 to \
  -2.21037, 19.727 to \
  -2.21037, 38.9412 front fs empty border lc rgb '#549f' lw 0.1
set object 1919 polygon from \
  -2.18883, 38.9626 to \
  -0.03, 38.9626 to \
  -0.03, 19.7384 to \
  -2.18883, 19.7384 to \
  -2.18883, 38.9626 front fs empty border lc rgb '#549f' lw 0.1
set object 1920 polygon from \
  -2.16631, 38.984 to \
  -0.03, 38.984 to \
  -0.03, 19.7498 to \
  -2.16631, 19.7498 to \
  -2.16631, 38.984 front fs empty border lc rgb '#549f' lw 0.1
set object 1921 polygon from \
  -2.14281, 39.0054 to \
  -0.03, 39.0054 to \
  -0.03, 19.7612 to \
  -2.14281, 19.7612 to \
  -2.14281, 39.0054 front fs empty border lc rgb '#549f' lw 0.1
set object 1922 polygon from \
  -2.11832, 39.0268 to \
  -0.03, 39.0268 to \
  -0.03, 19.7726 to \
  -2.11832, 19.7726 to \
  -2.11832, 39.0268 front fs empty border lc rgb '#549f' lw 0.1
set object 1923 polygon from \
  -2.09287, 39.0482 to \
  -0.03, 39.0482 to \
  -0.03, 19.784 to \
  -2.09287, 19.784 to \
  -2.09287, 39.0482 front fs empty border lc rgb '#549f' lw 0.1
set object 1924 polygon from \
  -2.06644, 39.0696 to \
  -0.03, 39.0696 to \
  -0.03, 19.7954 to \
  -2.06644, 19.7954 to \
  -2.06644, 39.0696 front fs empty border lc rgb '#549f' lw 0.1
set object 1925 polygon from \
  -2.03905, 39.091 to \
  -0.03, 39.091 to \
  -0.03, 19.8068 to \
  -2.03905, 19.8068 to \
  -2.03905, 39.091 front fs empty border lc rgb '#549f' lw 0.1
set object 1926 polygon from \
  -2.01071, 39.1124 to \
  -0.03, 39.1124 to \
  -0.03, 19.8182 to \
  -2.01071, 19.8182 to \
  -2.01071, 39.1124 front fs empty border lc rgb '#549f' lw 0.1
set object 1927 polygon from \
  -1.98141, 39.1338 to \
  -0.03, 39.1338 to \
  -0.03, 19.8296 to \
  -1.98141, 19.8296 to \
  -1.98141, 39.1338 front fs empty border lc rgb '#549f' lw 0.1
set object 1928 polygon from \
  -1.95117, 39.1552 to \
  -0.03, 39.1552 to \
  -0.03, 19.841 to \
  -1.95117, 19.841 to \
  -1.95117, 39.1552 front fs empty border lc rgb '#549f' lw 0.1
set object 1929 polygon from \
  -1.91999, 39.1767 to \
  -0.03, 39.1767 to \
  -0.03, 19.8524 to \
  -1.91999, 19.8524 to \
  -1.91999, 39.1767 front fs empty border lc rgb '#549f' lw 0.1
set object 1930 polygon from \
  -1.88788, 39.1981 to \
  -0.03, 39.1981 to \
  -0.03, 19.8638 to \
  -1.88788, 19.8638 to \
  -1.88788, 39.1981 front fs empty border lc rgb '#549f' lw 0.1
set object 1931 polygon from \
  -1.85485, 39.2195 to \
  -0.03, 39.2195 to \
  -0.03, 19.8752 to \
  -1.85485, 19.8752 to \
  -1.85485, 39.2195 front fs empty border lc rgb '#549f' lw 0.1
set object 1932 polygon from \
  -1.82091, 39.2409 to \
  -0.03, 39.2409 to \
  -0.03, 19.8866 to \
  -1.82091, 19.8866 to \
  -1.82091, 39.2409 front fs empty border lc rgb '#549f' lw 0.1
set object 1933 polygon from \
  -1.78607, 39.2623 to \
  -0.03, 39.2623 to \
  -0.03, 19.8981 to \
  -1.78607, 19.8981 to \
  -1.78607, 39.2623 front fs empty border lc rgb '#549f' lw 0.1
set object 1934 polygon from \
  -1.77396, 39.2837 to \
  -0.03, 39.2837 to \
  -0.03, 19.9095 to \
  -1.77396, 19.9095 to \
  -1.77396, 39.2837 front fs empty border lc rgb '#549f' lw 0.1
set object 1935 polygon from \
  -1.76657, 39.3051 to \
  -0.03, 39.3051 to \
  -0.03, 19.9209 to \
  -1.76657, 19.9209 to \
  -1.76657, 39.3051 front fs empty border lc rgb '#549f' lw 0.1
set object 1936 polygon from \
  -1.758, 39.3266 to \
  -0.03, 39.3266 to \
  -0.03, 19.9323 to \
  -1.758, 19.9323 to \
  -1.758, 39.3266 front fs empty border lc rgb '#549f' lw 0.1
set object 1937 polygon from \
  -1.74825, 39.348 to \
  -0.03, 39.348 to \
  -0.03, 19.9437 to \
  -1.74825, 19.9437 to \
  -1.74825, 39.348 front fs empty border lc rgb '#549f' lw 0.1
set object 1938 polygon from \
  -1.73733, 39.3694 to \
  -0.03, 39.3694 to \
  -0.03, 19.9551 to \
  -1.73733, 19.9551 to \
  -1.73733, 39.3694 front fs empty border lc rgb '#549f' lw 0.1
set object 1939 polygon from \
  -1.72525, 39.3908 to \
  -0.03, 39.3908 to \
  -0.03, 19.9666 to \
  -1.72525, 19.9666 to \
  -1.72525, 39.3908 front fs empty border lc rgb '#549f' lw 0.1
set object 1940 polygon from \
  -1.71202, 39.4122 to \
  -0.03, 39.4122 to \
  -0.03, 19.978 to \
  -1.71202, 19.978 to \
  -1.71202, 39.4122 front fs empty border lc rgb '#549f' lw 0.1
set object 1941 polygon from \
  -1.69766, 39.4337 to \
  -0.03, 39.4337 to \
  -0.03, 19.9894 to \
  -1.69766, 19.9894 to \
  -1.69766, 39.4337 front fs empty border lc rgb '#549f' lw 0.1
set object 1942 polygon from \
  -1.68217, 39.4551 to \
  -0.03, 39.4551 to \
  -0.03, 20.0008 to \
  -1.68217, 20.0008 to \
  -1.68217, 39.4551 front fs empty border lc rgb '#549f' lw 0.1
set object 1943 polygon from \
  -1.66558, 39.4765 to \
  -0.03, 39.4765 to \
  -0.03, 20.0122 to \
  -1.66558, 20.0122 to \
  -1.66558, 39.4765 front fs empty border lc rgb '#549f' lw 0.1
set object 1944 polygon from \
  -1.64789, 39.498 to \
  -0.03, 39.498 to \
  -0.03, 20.0237 to \
  -1.64789, 20.0237 to \
  -1.64789, 39.498 front fs empty border lc rgb '#549f' lw 0.1
set object 1945 polygon from \
  -1.62912, 39.5194 to \
  -0.03, 39.5194 to \
  -0.03, 20.0351 to \
  -1.62912, 20.0351 to \
  -1.62912, 39.5194 front fs empty border lc rgb '#549f' lw 0.1
set object 1946 polygon from \
  -1.60929, 39.5408 to \
  -0.03, 39.5408 to \
  -0.03, 20.0465 to \
  -1.60929, 20.0465 to \
  -1.60929, 39.5408 front fs empty border lc rgb '#549f' lw 0.1
set object 1947 polygon from \
  -1.58842, 39.5623 to \
  -0.03, 39.5623 to \
  -0.03, 20.058 to \
  -1.58842, 20.058 to \
  -1.58842, 39.5623 front fs empty border lc rgb '#549f' lw 0.1
set object 1948 polygon from \
  -1.56652, 39.5837 to \
  -0.03, 39.5837 to \
  -0.03, 20.0694 to \
  -1.56652, 20.0694 to \
  -1.56652, 39.5837 front fs empty border lc rgb '#549f' lw 0.1
set object 1949 polygon from \
  -1.54361, 39.6051 to \
  -0.03, 39.6051 to \
  -0.03, 20.0808 to \
  -1.54361, 20.0808 to \
  -1.54361, 39.6051 front fs empty border lc rgb '#549f' lw 0.1
set object 1950 polygon from \
  -1.51971, 39.6266 to \
  -0.03, 39.6266 to \
  -0.03, 20.0923 to \
  -1.51971, 20.0923 to \
  -1.51971, 39.6266 front fs empty border lc rgb '#549f' lw 0.1
set object 1951 polygon from \
  -1.49484, 39.648 to \
  -0.03, 39.648 to \
  -0.03, 20.1037 to \
  -1.49484, 20.1037 to \
  -1.49484, 39.648 front fs empty border lc rgb '#549f' lw 0.1
set object 1952 polygon from \
  -1.46902, 39.6694 to \
  -0.03, 39.6694 to \
  -0.03, 20.1151 to \
  -1.46902, 20.1151 to \
  -1.46902, 39.6694 front fs empty border lc rgb '#549f' lw 0.1
set object 1953 polygon from \
  -1.44227, 39.6909 to \
  -0.03, 39.6909 to \
  -0.03, 20.1266 to \
  -1.44227, 20.1266 to \
  -1.44227, 39.6909 front fs empty border lc rgb '#549f' lw 0.1
set object 1954 polygon from \
  -1.41461, 39.7123 to \
  -0.03, 39.7123 to \
  -0.03, 20.138 to \
  -1.41461, 20.138 to \
  -1.41461, 39.7123 front fs empty border lc rgb '#549f' lw 0.1
set object 1955 polygon from \
  -1.38606, 39.7338 to \
  -0.03, 39.7338 to \
  -0.03, 20.1494 to \
  -1.38606, 20.1494 to \
  -1.38606, 39.7338 front fs empty border lc rgb '#549f' lw 0.1
set object 1956 polygon from \
  -1.35666, 39.7552 to \
  -0.03, 39.7552 to \
  -0.03, 20.1609 to \
  -1.35666, 20.1609 to \
  -1.35666, 39.7552 front fs empty border lc rgb '#549f' lw 0.1
set object 1957 polygon from \
  -1.32641, 39.7767 to \
  -0.03, 39.7767 to \
  -0.03, 20.1723 to \
  -1.32641, 20.1723 to \
  -1.32641, 39.7767 front fs empty border lc rgb '#549f' lw 0.1
set object 1958 polygon from \
  -1.29535, 39.7981 to \
  -0.03, 39.7981 to \
  -0.03, 20.1838 to \
  -1.29535, 20.1838 to \
  -1.29535, 39.7981 front fs empty border lc rgb '#549f' lw 0.1
set object 1959 polygon from \
  -1.2635, 39.8196 to \
  -0.03, 39.8196 to \
  -0.03, 20.1952 to \
  -1.2635, 20.1952 to \
  -1.2635, 39.8196 front fs empty border lc rgb '#549f' lw 0.1
set object 1960 polygon from \
  -1.24382, 39.841 to \
  -0.03, 39.841 to \
  -0.03, 20.2067 to \
  -1.24382, 20.2067 to \
  -1.24382, 39.841 front fs empty border lc rgb '#549f' lw 0.1
set object 1961 polygon from \
  -1.26228, 39.8625 to \
  -0.03, 39.8625 to \
  -0.03, 20.2181 to \
  -1.26228, 20.2181 to \
  -1.26228, 39.8625 front fs empty border lc rgb '#549f' lw 0.1
set object 1962 polygon from \
  -1.28029, 39.8839 to \
  -0.03, 39.8839 to \
  -0.03, 20.2295 to \
  -1.28029, 20.2295 to \
  -1.28029, 39.8839 front fs empty border lc rgb '#549f' lw 0.1
set object 1963 polygon from \
  -1.29787, 39.9054 to \
  -0.03, 39.9054 to \
  -0.03, 20.241 to \
  -1.29787, 20.241 to \
  -1.29787, 39.9054 front fs empty border lc rgb '#549f' lw 0.1
set object 1964 polygon from \
  -1.31501, 39.9268 to \
  -0.03, 39.9268 to \
  -0.03, 20.2524 to \
  -1.31501, 20.2524 to \
  -1.31501, 39.9268 front fs empty border lc rgb '#549f' lw 0.1
set object 1965 polygon from \
  -1.33173, 39.9483 to \
  -0.03, 39.9483 to \
  -0.03, 20.2639 to \
  -1.33173, 20.2639 to \
  -1.33173, 39.9483 front fs empty border lc rgb '#549f' lw 0.1
set object 1966 polygon from \
  -1.34801, 39.9697 to \
  -0.03, 39.9697 to \
  -0.03, 20.2754 to \
  -1.34801, 20.2754 to \
  -1.34801, 39.9697 front fs empty border lc rgb '#549f' lw 0.1
set object 1967 polygon from \
  -1.36388, 39.9912 to \
  -0.03, 39.9912 to \
  -0.03, 20.2868 to \
  -1.36388, 20.2868 to \
  -1.36388, 39.9912 front fs empty border lc rgb '#549f' lw 0.1
set object 1968 polygon from \
  -1.37934, 40.0126 to \
  -0.03, 40.0126 to \
  -0.03, 20.2983 to \
  -1.37934, 20.2983 to \
  -1.37934, 40.0126 front fs empty border lc rgb '#549f' lw 0.1
set object 1969 polygon from \
  -1.39438, 40.0341 to \
  -0.03, 40.0341 to \
  -0.03, 20.3097 to \
  -1.39438, 20.3097 to \
  -1.39438, 40.0341 front fs empty border lc rgb '#549f' lw 0.1
set object 1970 polygon from \
  -1.40902, 40.0556 to \
  -0.03, 40.0556 to \
  -0.03, 20.3212 to \
  -1.40902, 20.3212 to \
  -1.40902, 40.0556 front fs empty border lc rgb '#549f' lw 0.1
set object 1971 polygon from \
  -1.42327, 40.077 to \
  -0.03, 40.077 to \
  -0.03, 20.3326 to \
  -1.42327, 20.3326 to \
  -1.42327, 40.077 front fs empty border lc rgb '#549f' lw 0.1
set object 1972 polygon from \
  -1.43713, 40.0985 to \
  -0.03, 40.0985 to \
  -0.03, 20.3441 to \
  -1.43713, 20.3441 to \
  -1.43713, 40.0985 front fs empty border lc rgb '#549f' lw 0.1
set object 1973 polygon from \
  -1.45061, 40.12 to \
  -0.03, 40.12 to \
  -0.03, 20.3556 to \
  -1.45061, 20.3556 to \
  -1.45061, 40.12 front fs empty border lc rgb '#549f' lw 0.1
set object 1974 polygon from \
  -1.4637, 40.1414 to \
  -0.03, 40.1414 to \
  -0.03, 20.367 to \
  -1.4637, 20.367 to \
  -1.4637, 40.1414 front fs empty border lc rgb '#549f' lw 0.1
set object 1975 polygon from \
  -1.47643, 40.1629 to \
  -0.03, 40.1629 to \
  -0.03, 20.3785 to \
  -1.47643, 20.3785 to \
  -1.47643, 40.1629 front fs empty border lc rgb '#549f' lw 0.1
set object 1976 polygon from \
  -1.4888, 40.1844 to \
  -0.03, 40.1844 to \
  -0.03, 20.39 to \
  -1.4888, 20.39 to \
  -1.4888, 40.1844 front fs empty border lc rgb '#549f' lw 0.1
set object 1977 polygon from \
  -1.50081, 40.2058 to \
  -0.03, 40.2058 to \
  -0.03, 20.4014 to \
  -1.50081, 20.4014 to \
  -1.50081, 40.2058 front fs empty border lc rgb '#549f' lw 0.1
set object 1978 polygon from \
  -1.51248, 40.2273 to \
  -0.03, 40.2273 to \
  -0.03, 20.4129 to \
  -1.51248, 20.4129 to \
  -1.51248, 40.2273 front fs empty border lc rgb '#549f' lw 0.1
set object 1979 polygon from \
  -1.5238, 40.2488 to \
  -0.03, 40.2488 to \
  -0.03, 20.4244 to \
  -1.5238, 20.4244 to \
  -1.5238, 40.2488 front fs empty border lc rgb '#549f' lw 0.1
set object 1980 polygon from \
  -1.56863, 40.2702 to \
  -0.03, 40.2702 to \
  -0.03, 20.4358 to \
  -1.56863, 20.4358 to \
  -1.56863, 40.2702 front fs empty border lc rgb '#549f' lw 0.1
set object 1981 polygon from \
  -1.61639, 40.2917 to \
  -0.03, 40.2917 to \
  -0.03, 20.4473 to \
  -1.61639, 20.4473 to \
  -1.61639, 40.2917 front fs empty border lc rgb '#549f' lw 0.1
set object 1982 polygon from \
  -1.66378, 40.3132 to \
  -0.03, 40.3132 to \
  -0.03, 20.4588 to \
  -1.66378, 20.4588 to \
  -1.66378, 40.3132 front fs empty border lc rgb '#549f' lw 0.1
set object 1983 polygon from \
  -1.71078, 40.3347 to \
  -0.03, 40.3347 to \
  -0.03, 20.4702 to \
  -1.71078, 20.4702 to \
  -1.71078, 40.3347 front fs empty border lc rgb '#549f' lw 0.1
set object 1984 polygon from \
  -1.75737, 40.3562 to \
  -0.03, 40.3562 to \
  -0.03, 20.4817 to \
  -1.75737, 20.4817 to \
  -1.75737, 40.3562 front fs empty border lc rgb '#549f' lw 0.1
set object 1985 polygon from \
  -1.80352, 40.3776 to \
  -0.03, 40.3776 to \
  -0.03, 20.4932 to \
  -1.80352, 20.4932 to \
  -1.80352, 40.3776 front fs empty border lc rgb '#549f' lw 0.1
set object 1986 polygon from \
  -1.84921, 40.3991 to \
  -0.03, 40.3991 to \
  -0.03, 20.5047 to \
  -1.84921, 20.5047 to \
  -1.84921, 40.3991 front fs empty border lc rgb '#549f' lw 0.1
set object 1987 polygon from \
  -1.89442, 40.4206 to \
  -0.03, 40.4206 to \
  -0.03, 20.5162 to \
  -1.89442, 20.5162 to \
  -1.89442, 40.4206 front fs empty border lc rgb '#549f' lw 0.1
set object 1988 polygon from \
  -1.93913, 40.4421 to \
  -0.03, 40.4421 to \
  -0.03, 20.5276 to \
  -1.93913, 20.5276 to \
  -1.93913, 40.4421 front fs empty border lc rgb '#549f' lw 0.1
set object 1989 polygon from \
  -1.98332, 40.4636 to \
  -0.03, 40.4636 to \
  -0.03, 20.5391 to \
  -1.98332, 20.5391 to \
  -1.98332, 40.4636 front fs empty border lc rgb '#549f' lw 0.1
set object 1990 polygon from \
  -2.02697, 40.4851 to \
  -0.03, 40.4851 to \
  -0.03, 20.5506 to \
  -2.02697, 20.5506 to \
  -2.02697, 40.4851 front fs empty border lc rgb '#549f' lw 0.1
set object 1991 polygon from \
  -2.07005, 40.5066 to \
  -0.03, 40.5066 to \
  -0.03, 20.5621 to \
  -2.07005, 20.5621 to \
  -2.07005, 40.5066 front fs empty border lc rgb '#549f' lw 0.1
set object 1992 polygon from \
  -2.11255, 40.528 to \
  -0.03, 40.528 to \
  -0.03, 20.5736 to \
  -2.11255, 20.5736 to \
  -2.11255, 40.528 front fs empty border lc rgb '#549f' lw 0.1
set object 1993 polygon from \
  -2.15445, 40.5495 to \
  -0.03, 40.5495 to \
  -0.03, 20.5851 to \
  -2.15445, 20.5851 to \
  -2.15445, 40.5495 front fs empty border lc rgb '#549f' lw 0.1
set object 1994 polygon from \
  -2.19572, 40.571 to \
  -0.03, 40.571 to \
  -0.03, 20.5965 to \
  -2.19572, 20.5965 to \
  -2.19572, 40.571 front fs empty border lc rgb '#549f' lw 0.1
set object 1995 polygon from \
  -2.23635, 40.5925 to \
  -0.03, 40.5925 to \
  -0.03, 20.608 to \
  -2.23635, 20.608 to \
  -2.23635, 40.5925 front fs empty border lc rgb '#549f' lw 0.1
set object 1996 polygon from \
  -2.27631, 40.614 to \
  -0.03, 40.614 to \
  -0.03, 20.6195 to \
  -2.27631, 20.6195 to \
  -2.27631, 40.614 front fs empty border lc rgb '#549f' lw 0.1
set object 1997 polygon from \
  -2.31559, 40.6355 to \
  -0.03, 40.6355 to \
  -0.03, 20.631 to \
  -2.31559, 20.631 to \
  -2.31559, 40.6355 front fs empty border lc rgb '#549f' lw 0.1
set object 1998 polygon from \
  -2.35417, 40.657 to \
  -0.03, 40.657 to \
  -0.03, 20.6425 to \
  -2.35417, 20.6425 to \
  -2.35417, 40.657 front fs empty border lc rgb '#549f' lw 0.1
set object 1999 polygon from \
  -2.39203, 40.6785 to \
  -0.03, 40.6785 to \
  -0.03, 20.654 to \
  -2.39203, 20.654 to \
  -2.39203, 40.6785 front fs empty border lc rgb '#549f' lw 0.1
set object 2000 polygon from \
  -2.42916, 40.7 to \
  -0.03, 40.7 to \
  -0.03, 20.6655 to \
  -2.42916, 20.6655 to \
  -2.42916, 40.7 front fs empty border lc rgb '#549f' lw 0.1
set object 2001 polygon from \
  -2.46553, 40.7215 to \
  -0.03, 40.7215 to \
  -0.03, 20.677 to \
  -2.46553, 20.677 to \
  -2.46553, 40.7215 front fs empty border lc rgb '#549f' lw 0.1
set object 2002 polygon from \
  -2.50112, 40.743 to \
  -0.03, 40.743 to \
  -0.03, 20.6885 to \
  -2.50112, 20.6885 to \
  -2.50112, 40.743 front fs empty border lc rgb '#549f' lw 0.1
set object 2003 polygon from \
  -2.53593, 40.7645 to \
  -0.03, 40.7645 to \
  -0.03, 20.7 to \
  -2.53593, 20.7 to \
  -2.53593, 40.7645 front fs empty border lc rgb '#549f' lw 0.1
set object 2004 polygon from \
  -2.56993, 40.786 to \
  -0.03, 40.786 to \
  -0.03, 20.7115 to \
  -2.56993, 20.7115 to \
  -2.56993, 40.786 front fs empty border lc rgb '#549f' lw 0.1
set object 2005 polygon from \
  -2.60311, 40.8075 to \
  -0.03, 40.8075 to \
  -0.03, 20.723 to \
  -2.60311, 20.723 to \
  -2.60311, 40.8075 front fs empty border lc rgb '#549f' lw 0.1
set object 2006 polygon from \
  -2.63546, 40.829 to \
  -0.03, 40.829 to \
  -0.03, 20.7345 to \
  -2.63546, 20.7345 to \
  -2.63546, 40.829 front fs empty border lc rgb '#549f' lw 0.1
set object 2007 polygon from \
  -2.66695, 40.8505 to \
  -0.03, 40.8505 to \
  -0.03, 20.746 to \
  -2.66695, 20.746 to \
  -2.66695, 40.8505 front fs empty border lc rgb '#549f' lw 0.1
set object 2008 polygon from \
  -2.69757, 40.872 to \
  -0.03, 40.872 to \
  -0.03, 20.7575 to \
  -2.69757, 20.7575 to \
  -2.69757, 40.872 front fs empty border lc rgb '#549f' lw 0.1
set object 2009 polygon from \
  -2.72731, 40.8936 to \
  -0.03, 40.8936 to \
  -0.03, 20.769 to \
  -2.72731, 20.769 to \
  -2.72731, 40.8936 front fs empty border lc rgb '#549f' lw 0.1
set object 2010 polygon from \
  -2.75616, 40.9151 to \
  -0.03, 40.9151 to \
  -0.03, 20.7805 to \
  -2.75616, 20.7805 to \
  -2.75616, 40.9151 front fs empty border lc rgb '#549f' lw 0.1
set object 2011 polygon from \
  -2.78409, 40.9366 to \
  -0.03, 40.9366 to \
  -0.03, 20.792 to \
  -2.78409, 20.792 to \
  -2.78409, 40.9366 front fs empty border lc rgb '#549f' lw 0.1
set object 2012 polygon from \
  -2.81111, 40.9581 to \
  -0.03, 40.9581 to \
  -0.03, 20.8035 to \
  -2.81111, 20.8035 to \
  -2.81111, 40.9581 front fs empty border lc rgb '#549f' lw 0.1
set object 2013 polygon from \
  -2.83718, 40.9796 to \
  -0.03, 40.9796 to \
  -0.03, 20.8151 to \
  -2.83718, 20.8151 to \
  -2.83718, 40.9796 front fs empty border lc rgb '#549f' lw 0.1
set object 2014 polygon from \
  -2.86231, 41.0011 to \
  -0.03, 41.0011 to \
  -0.03, 20.8266 to \
  -2.86231, 20.8266 to \
  -2.86231, 41.0011 front fs empty border lc rgb '#549f' lw 0.1
set object 2015 polygon from \
  -2.88649, 41.0226 to \
  -0.03, 41.0226 to \
  -0.03, 20.8381 to \
  -2.88649, 20.8381 to \
  -2.88649, 41.0226 front fs empty border lc rgb '#549f' lw 0.1
set object 2016 polygon from \
  -2.90969, 41.0442 to \
  -0.03, 41.0442 to \
  -0.03, 20.8496 to \
  -2.90969, 20.8496 to \
  -2.90969, 41.0442 front fs empty border lc rgb '#549f' lw 0.1
set object 2017 polygon from \
  -2.93191, 41.0657 to \
  -0.03, 41.0657 to \
  -0.03, 20.8611 to \
  -2.93191, 20.8611 to \
  -2.93191, 41.0657 front fs empty border lc rgb '#549f' lw 0.1
set object 2018 polygon from \
  -2.95314, 41.0872 to \
  -0.03, 41.0872 to \
  -0.03, 20.8726 to \
  -2.95314, 20.8726 to \
  -2.95314, 41.0872 front fs empty border lc rgb '#549f' lw 0.1
set object 2019 polygon from \
  -2.97337, 41.1087 to \
  -0.03, 41.1087 to \
  -0.03, 20.8842 to \
  -2.97337, 20.8842 to \
  -2.97337, 41.1087 front fs empty border lc rgb '#549f' lw 0.1
set object 2020 polygon from \
  -2.99259, 41.1302 to \
  -0.03, 41.1302 to \
  -0.03, 20.8957 to \
  -2.99259, 20.8957 to \
  -2.99259, 41.1302 front fs empty border lc rgb '#549f' lw 0.1
set object 2021 polygon from \
  -3.0108, 41.1518 to \
  -0.03, 41.1518 to \
  -0.03, 20.9072 to \
  -3.0108, 20.9072 to \
  -3.0108, 41.1518 front fs empty border lc rgb '#549f' lw 0.1
set object 2022 polygon from \
  -3.02797, 41.1733 to \
  -0.03, 41.1733 to \
  -0.03, 20.9187 to \
  -3.02797, 20.9187 to \
  -3.02797, 41.1733 front fs empty border lc rgb '#549f' lw 0.1
set object 2023 polygon from \
  -3.04412, 41.1948 to \
  -0.03, 41.1948 to \
  -0.03, 20.9302 to \
  -3.04412, 20.9302 to \
  -3.04412, 41.1948 front fs empty border lc rgb '#549f' lw 0.1
set object 2024 polygon from \
  -3.05922, 41.2164 to \
  -0.03, 41.2164 to \
  -0.03, 20.9418 to \
  -3.05922, 20.9418 to \
  -3.05922, 41.2164 front fs empty border lc rgb '#549f' lw 0.1
set object 2025 polygon from \
  -3.07328, 41.2379 to \
  -0.03, 41.2379 to \
  -0.03, 20.9533 to \
  -3.07328, 20.9533 to \
  -3.07328, 41.2379 front fs empty border lc rgb '#549f' lw 0.1
set object 2026 polygon from \
  -3.08628, 41.2594 to \
  -0.03, 41.2594 to \
  -0.03, 20.9648 to \
  -3.08628, 20.9648 to \
  -3.08628, 41.2594 front fs empty border lc rgb '#549f' lw 0.1
set object 2027 polygon from \
  -3.09822, 41.281 to \
  -0.03, 41.281 to \
  -0.03, 20.9764 to \
  -3.09822, 20.9764 to \
  -3.09822, 41.281 front fs empty border lc rgb '#549f' lw 0.1
set object 2028 polygon from \
  -3.10936, 41.3025 to \
  -0.03, 41.3025 to \
  -0.03, 20.9879 to \
  -3.10936, 20.9879 to \
  -3.10936, 41.3025 front fs empty border lc rgb '#549f' lw 0.1
set object 2029 polygon from \
  -3.11975, 41.324 to \
  -0.03, 41.324 to \
  -0.03, 20.9994 to \
  -3.11975, 20.9994 to \
  -3.11975, 41.324 front fs empty border lc rgb '#549f' lw 0.1
set object 2030 polygon from \
  -3.12906, 41.3456 to \
  -0.03, 41.3456 to \
  -0.03, 21.011 to \
  -3.12906, 21.011 to \
  -3.12906, 41.3456 front fs empty border lc rgb '#549f' lw 0.1
set object 2031 polygon from \
  -3.13729, 41.3671 to \
  -0.03, 41.3671 to \
  -0.03, 21.0225 to \
  -3.13729, 21.0225 to \
  -3.13729, 41.3671 front fs empty border lc rgb '#549f' lw 0.1
set object 2032 polygon from \
  -3.14443, 41.3886 to \
  -0.03, 41.3886 to \
  -0.03, 21.034 to \
  -3.14443, 21.034 to \
  -3.14443, 41.3886 front fs empty border lc rgb '#549f' lw 0.1
set object 2033 polygon from \
  -3.15048, 41.4102 to \
  -0.03, 41.4102 to \
  -0.03, 21.0456 to \
  -3.15048, 21.0456 to \
  -3.15048, 41.4102 front fs empty border lc rgb '#549f' lw 0.1
set object 2034 polygon from \
  -3.15545, 41.4317 to \
  -0.03, 41.4317 to \
  -0.03, 21.0571 to \
  -3.15545, 21.0571 to \
  -3.15545, 41.4317 front fs empty border lc rgb '#549f' lw 0.1
set object 2035 polygon from \
  -3.15932, 41.4533 to \
  -0.03, 41.4533 to \
  -0.03, 21.0686 to \
  -3.15932, 21.0686 to \
  -3.15932, 41.4533 front fs empty border lc rgb '#549f' lw 0.1
set object 2036 polygon from \
  -3.16211, 41.4748 to \
  -0.03, 41.4748 to \
  -0.03, 21.0802 to \
  -3.16211, 21.0802 to \
  -3.16211, 41.4748 front fs empty border lc rgb '#549f' lw 0.1
set object 2037 polygon from \
  -3.16381, 41.4964 to \
  -0.03, 41.4964 to \
  -0.03, 21.0917 to \
  -3.16381, 21.0917 to \
  -3.16381, 41.4964 front fs empty border lc rgb '#549f' lw 0.1
set object 2038 polygon from \
  -3.16442, 41.5179 to \
  -0.03, 41.5179 to \
  -0.03, 21.1033 to \
  -3.16442, 21.1033 to \
  -3.16442, 41.5179 front fs empty border lc rgb '#549f' lw 0.1
set object 2039 polygon from \
  -3.16442, 41.5395 to \
  -0.03, 41.5395 to \
  -0.03, 21.1148 to \
  -3.16442, 21.1148 to \
  -3.16442, 41.5395 front fs empty border lc rgb '#549f' lw 0.1
set object 2040 polygon from \
  -3.16394, 41.561 to \
  -0.03, 41.561 to \
  -0.03, 21.1264 to \
  -3.16394, 21.1264 to \
  -3.16394, 41.561 front fs empty border lc rgb '#549f' lw 0.1
set object 2041 polygon from \
  -3.16238, 41.5826 to \
  -0.03, 41.5826 to \
  -0.03, 21.1379 to \
  -3.16238, 21.1379 to \
  -3.16238, 41.5826 front fs empty border lc rgb '#549f' lw 0.1
set object 2042 polygon from \
  -3.15974, 41.6041 to \
  -0.03, 41.6041 to \
  -0.03, 21.1494 to \
  -3.15974, 21.1494 to \
  -3.15974, 41.6041 front fs empty border lc rgb '#549f' lw 0.1
set object 2043 polygon from \
  -3.15603, 41.6257 to \
  -0.03, 41.6257 to \
  -0.03, 21.161 to \
  -3.15603, 21.161 to \
  -3.15603, 41.6257 front fs empty border lc rgb '#549f' lw 0.1
set object 2044 polygon from \
  -3.15123, 41.6472 to \
  -0.03, 41.6472 to \
  -0.03, 21.1725 to \
  -3.15123, 21.1725 to \
  -3.15123, 41.6472 front fs empty border lc rgb '#549f' lw 0.1
set object 2045 polygon from \
  -3.14537, 41.6688 to \
  -0.03, 41.6688 to \
  -0.03, 21.1841 to \
  -3.14537, 21.1841 to \
  -3.14537, 41.6688 front fs empty border lc rgb '#549f' lw 0.1
set object 2046 polygon from \
  -3.14043, 41.6903 to \
  -0.03, 41.6903 to \
  -0.03, 21.1957 to \
  -3.14043, 21.1957 to \
  -3.14043, 41.6903 front fs empty border lc rgb '#549f' lw 0.1
set object 2047 polygon from \
  -3.13555, 41.7119 to \
  -0.03, 41.7119 to \
  -0.03, 21.2072 to \
  -3.13555, 21.2072 to \
  -3.13555, 41.7119 front fs empty border lc rgb '#549f' lw 0.1
set object 2048 polygon from \
  -3.13084, 41.7334 to \
  -0.03, 41.7334 to \
  -0.03, 21.2188 to \
  -3.13084, 21.2188 to \
  -3.13084, 41.7334 front fs empty border lc rgb '#549f' lw 0.1
set object 2049 polygon from \
  -3.13485, 41.755 to \
  -0.03, 41.755 to \
  -0.03, 21.2303 to \
  -3.13485, 21.2303 to \
  -3.13485, 41.755 front fs empty border lc rgb '#549f' lw 0.1
set object 2050 polygon from \
  -3.13778, 41.7766 to \
  -0.03, 41.7766 to \
  -0.03, 21.2419 to \
  -3.13778, 21.2419 to \
  -3.13778, 41.7766 front fs empty border lc rgb '#549f' lw 0.1
set object 2051 polygon from \
  -3.13964, 41.7981 to \
  -0.03, 41.7981 to \
  -0.03, 21.2534 to \
  -3.13964, 21.2534 to \
  -3.13964, 41.7981 front fs empty border lc rgb '#549f' lw 0.1
set object 2052 polygon from \
  -3.14042, 41.8197 to \
  -0.03, 41.8197 to \
  -0.03, 21.265 to \
  -3.14042, 21.265 to \
  -3.14042, 41.8197 front fs empty border lc rgb '#549f' lw 0.1
set object 2053 polygon from \
  -3.14041, 41.8413 to \
  -0.03, 41.8413 to \
  -0.03, 21.2766 to \
  -3.14041, 21.2766 to \
  -3.14041, 41.8413 front fs empty border lc rgb '#549f' lw 0.1
set object 2054 polygon from \
  -3.14012, 41.8628 to \
  -0.03, 41.8628 to \
  -0.03, 21.2881 to \
  -3.14012, 21.2881 to \
  -3.14012, 41.8628 front fs empty border lc rgb '#549f' lw 0.1
set object 2055 polygon from \
  -3.13875, 41.8844 to \
  -0.03, 41.8844 to \
  -0.03, 21.2997 to \
  -3.13875, 21.2997 to \
  -3.13875, 41.8844 front fs empty border lc rgb '#549f' lw 0.1
set object 2056 polygon from \
  -3.13631, 41.906 to \
  -0.03, 41.906 to \
  -0.03, 21.3113 to \
  -3.13631, 21.3113 to \
  -3.13631, 41.906 front fs empty border lc rgb '#549f' lw 0.1
set object 2057 polygon from \
  -3.1328, 41.9275 to \
  -0.03, 41.9275 to \
  -0.03, 21.3228 to \
  -3.1328, 21.3228 to \
  -3.1328, 41.9275 front fs empty border lc rgb '#549f' lw 0.1
set object 2058 polygon from \
  -3.12824, 41.9491 to \
  -0.03, 41.9491 to \
  -0.03, 21.3344 to \
  -3.12824, 21.3344 to \
  -3.12824, 41.9491 front fs empty border lc rgb '#549f' lw 0.1
set object 2059 polygon from \
  -3.12261, 41.9707 to \
  -0.03, 41.9707 to \
  -0.03, 21.346 to \
  -3.12261, 21.346 to \
  -3.12261, 41.9707 front fs empty border lc rgb '#549f' lw 0.1
set object 2060 polygon from \
  -3.11594, 41.9922 to \
  -0.03, 41.9922 to \
  -0.03, 21.3575 to \
  -3.11594, 21.3575 to \
  -3.11594, 41.9922 front fs empty border lc rgb '#549f' lw 0.1
set object 2061 polygon from \
  -3.10822, 42.0138 to \
  -0.03, 42.0138 to \
  -0.03, 21.3691 to \
  -3.10822, 21.3691 to \
  -3.10822, 42.0138 front fs empty border lc rgb '#549f' lw 0.1
set object 2062 polygon from \
  -3.09947, 42.0354 to \
  -0.03, 42.0354 to \
  -0.03, 21.3807 to \
  -3.09947, 21.3807 to \
  -3.09947, 42.0354 front fs empty border lc rgb '#549f' lw 0.1
set object 2063 polygon from \
  -3.08968, 42.057 to \
  -0.03, 42.057 to \
  -0.03, 21.3922 to \
  -3.08968, 21.3922 to \
  -3.08968, 42.057 front fs empty border lc rgb '#549f' lw 0.1
set object 2064 polygon from \
  -3.07886, 42.0786 to \
  -0.03, 42.0786 to \
  -0.03, 21.4038 to \
  -3.07886, 21.4038 to \
  -3.07886, 42.0786 front fs empty border lc rgb '#549f' lw 0.1
set object 2065 polygon from \
  -3.06704, 42.1001 to \
  -0.03, 42.1001 to \
  -0.03, 21.4154 to \
  -3.06704, 21.4154 to \
  -3.06704, 42.1001 front fs empty border lc rgb '#549f' lw 0.1
set object 2066 polygon from \
  -3.0542, 42.1217 to \
  -0.03, 42.1217 to \
  -0.03, 21.427 to \
  -3.0542, 21.427 to \
  -3.0542, 42.1217 front fs empty border lc rgb '#549f' lw 0.1
set object 2067 polygon from \
  -3.04037, 42.1433 to \
  -0.03, 42.1433 to \
  -0.03, 21.4386 to \
  -3.04037, 21.4386 to \
  -3.04037, 42.1433 front fs empty border lc rgb '#549f' lw 0.1
set object 2068 polygon from \
  -3.02554, 42.1649 to \
  -0.03, 42.1649 to \
  -0.03, 21.4501 to \
  -3.02554, 21.4501 to \
  -3.02554, 42.1649 front fs empty border lc rgb '#549f' lw 0.1
set object 2069 polygon from \
  -3.00974, 42.1865 to \
  -0.03, 42.1865 to \
  -0.03, 21.4617 to \
  -3.00974, 21.4617 to \
  -3.00974, 42.1865 front fs empty border lc rgb '#549f' lw 0.1
set object 2070 polygon from \
  -2.99297, 42.2081 to \
  -0.03, 42.2081 to \
  -0.03, 21.4733 to \
  -2.99297, 21.4733 to \
  -2.99297, 42.2081 front fs empty border lc rgb '#549f' lw 0.1
set object 2071 polygon from \
  -2.97525, 42.2297 to \
  -0.03, 42.2297 to \
  -0.03, 21.4849 to \
  -2.97525, 21.4849 to \
  -2.97525, 42.2297 front fs empty border lc rgb '#549f' lw 0.1
set object 2072 polygon from \
  -2.95657, 42.2512 to \
  -0.03, 42.2512 to \
  -0.03, 21.4965 to \
  -2.95657, 21.4965 to \
  -2.95657, 42.2512 front fs empty border lc rgb '#549f' lw 0.1
set object 2073 polygon from \
  -2.93697, 42.2728 to \
  -0.03, 42.2728 to \
  -0.03, 21.5081 to \
  -2.93697, 21.5081 to \
  -2.93697, 42.2728 front fs empty border lc rgb '#549f' lw 0.1
set object 2074 polygon from \
  -2.91644, 42.2944 to \
  -0.03, 42.2944 to \
  -0.03, 21.5196 to \
  -2.91644, 21.5196 to \
  -2.91644, 42.2944 front fs empty border lc rgb '#549f' lw 0.1
set object 2075 polygon from \
  -2.895, 42.316 to \
  -0.03, 42.316 to \
  -0.03, 21.5312 to \
  -2.895, 21.5312 to \
  -2.895, 42.316 front fs empty border lc rgb '#549f' lw 0.1
set object 2076 polygon from \
  -2.87267, 42.3376 to \
  -0.03, 42.3376 to \
  -0.03, 21.5428 to \
  -2.87267, 21.5428 to \
  -2.87267, 42.3376 front fs empty border lc rgb '#549f' lw 0.1
set object 2077 polygon from \
  -2.84945, 42.3592 to \
  -0.03, 42.3592 to \
  -0.03, 21.5544 to \
  -2.84945, 21.5544 to \
  -2.84945, 42.3592 front fs empty border lc rgb '#549f' lw 0.1
set object 2078 polygon from \
  -2.82537, 42.3808 to \
  -0.03, 42.3808 to \
  -0.03, 21.566 to \
  -2.82537, 21.566 to \
  -2.82537, 42.3808 front fs empty border lc rgb '#549f' lw 0.1
set object 2079 polygon from \
  -2.80043, 42.4024 to \
  -0.03, 42.4024 to \
  -0.03, 21.5776 to \
  -2.80043, 21.5776 to \
  -2.80043, 42.4024 front fs empty border lc rgb '#549f' lw 0.1
set object 2080 polygon from \
  -2.77627, 42.424 to \
  -0.03, 42.424 to \
  -0.03, 21.5892 to \
  -2.77627, 21.5892 to \
  -2.77627, 42.424 front fs empty border lc rgb '#549f' lw 0.1
set object 2081 polygon from \
  -2.75788, 42.4456 to \
  -0.03, 42.4456 to \
  -0.03, 21.6008 to \
  -2.75788, 21.6008 to \
  -2.75788, 42.4456 front fs empty border lc rgb '#549f' lw 0.1
set object 2082 polygon from \
  -2.7387, 42.4672 to \
  -0.03, 42.4672 to \
  -0.03, 21.6124 to \
  -2.7387, 21.6124 to \
  -2.7387, 42.4672 front fs empty border lc rgb '#549f' lw 0.1
set object 2083 polygon from \
  -2.71875, 42.4888 to \
  -0.03, 42.4888 to \
  -0.03, 21.624 to \
  -2.71875, 21.624 to \
  -2.71875, 42.4888 front fs empty border lc rgb '#549f' lw 0.1
set object 2084 polygon from \
  -2.69805, 42.5104 to \
  -0.03, 42.5104 to \
  -0.03, 21.6356 to \
  -2.69805, 21.6356 to \
  -2.69805, 42.5104 front fs empty border lc rgb '#549f' lw 0.1
set object 2085 polygon from \
  -2.67662, 42.532 to \
  -0.03, 42.532 to \
  -0.03, 21.6472 to \
  -2.67662, 21.6472 to \
  -2.67662, 42.532 front fs empty border lc rgb '#549f' lw 0.1
set object 2086 polygon from \
  -2.65446, 42.5536 to \
  -0.03, 42.5536 to \
  -0.03, 21.6588 to \
  -2.65446, 21.6588 to \
  -2.65446, 42.5536 front fs empty border lc rgb '#549f' lw 0.1
set object 2087 polygon from \
  -2.6316, 42.5752 to \
  -0.03, 42.5752 to \
  -0.03, 21.6704 to \
  -2.6316, 21.6704 to \
  -2.6316, 42.5752 front fs empty border lc rgb '#549f' lw 0.1
set object 2088 polygon from \
  -2.60804, 42.5968 to \
  -0.03, 42.5968 to \
  -0.03, 21.682 to \
  -2.60804, 21.682 to \
  -2.60804, 42.5968 front fs empty border lc rgb '#549f' lw 0.1
set object 2089 polygon from \
  -2.61968, 42.6185 to \
  -0.03, 42.6185 to \
  -0.03, 21.6936 to \
  -2.61968, 21.6936 to \
  -2.61968, 42.6185 front fs empty border lc rgb '#549f' lw 0.1
set object 2090 polygon from \
  -2.63472, 42.6401 to \
  -0.03, 42.6401 to \
  -0.03, 21.7052 to \
  -2.63472, 21.7052 to \
  -2.63472, 42.6401 front fs empty border lc rgb '#549f' lw 0.1
set object 2091 polygon from \
  -2.64921, 42.6617 to \
  -0.03, 42.6617 to \
  -0.03, 21.7168 to \
  -2.64921, 21.7168 to \
  -2.64921, 42.6617 front fs empty border lc rgb '#549f' lw 0.1
set object 2092 polygon from \
  -2.66312, 42.6833 to \
  -0.03, 42.6833 to \
  -0.03, 21.7284 to \
  -2.66312, 21.7284 to \
  -2.66312, 42.6833 front fs empty border lc rgb '#549f' lw 0.1
set object 2093 polygon from \
  -2.67644, 42.7049 to \
  -0.03, 42.7049 to \
  -0.03, 21.7401 to \
  -2.67644, 21.7401 to \
  -2.67644, 42.7049 front fs empty border lc rgb '#549f' lw 0.1
set object 2094 polygon from \
  -2.68917, 42.7265 to \
  -0.03, 42.7265 to \
  -0.03, 21.7517 to \
  -2.68917, 21.7517 to \
  -2.68917, 42.7265 front fs empty border lc rgb '#549f' lw 0.1
set object 2095 polygon from \
  -2.70129, 42.7481 to \
  -0.03, 42.7481 to \
  -0.03, 21.7633 to \
  -2.70129, 21.7633 to \
  -2.70129, 42.7481 front fs empty border lc rgb '#549f' lw 0.1
set object 2096 polygon from \
  -2.71278, 42.7698 to \
  -0.03, 42.7698 to \
  -0.03, 21.7749 to \
  -2.71278, 21.7749 to \
  -2.71278, 42.7698 front fs empty border lc rgb '#549f' lw 0.1
set object 2097 polygon from \
  -2.72363, 42.7914 to \
  -0.03, 42.7914 to \
  -0.03, 21.7865 to \
  -2.72363, 21.7865 to \
  -2.72363, 42.7914 front fs empty border lc rgb '#549f' lw 0.1
set object 2098 polygon from \
  -2.73383, 42.813 to \
  -0.03, 42.813 to \
  -0.03, 21.7981 to \
  -2.73383, 21.7981 to \
  -2.73383, 42.813 front fs empty border lc rgb '#549f' lw 0.1
set object 2099 polygon from \
  -2.74337, 42.8346 to \
  -0.03, 42.8346 to \
  -0.03, 21.8098 to \
  -2.74337, 21.8098 to \
  -2.74337, 42.8346 front fs empty border lc rgb '#549f' lw 0.1
set object 2100 polygon from \
  -2.75224, 42.8562 to \
  -0.03, 42.8562 to \
  -0.03, 21.8214 to \
  -2.75224, 21.8214 to \
  -2.75224, 42.8562 front fs empty border lc rgb '#549f' lw 0.1
set object 2101 polygon from \
  -2.76042, 42.8779 to \
  -0.03, 42.8779 to \
  -0.03, 21.833 to \
  -2.76042, 21.833 to \
  -2.76042, 42.8779 front fs empty border lc rgb '#549f' lw 0.1
set object 2102 polygon from \
  -2.7679, 42.8995 to \
  -0.03, 42.8995 to \
  -0.03, 21.8446 to \
  -2.7679, 21.8446 to \
  -2.7679, 42.8995 front fs empty border lc rgb '#549f' lw 0.1
set object 2103 polygon from \
  -2.77468, 42.9211 to \
  -0.03, 42.9211 to \
  -0.03, 21.8562 to \
  -2.77468, 21.8562 to \
  -2.77468, 42.9211 front fs empty border lc rgb '#549f' lw 0.1
set object 2104 polygon from \
  -2.78073, 42.9428 to \
  -0.03, 42.9428 to \
  -0.03, 21.8679 to \
  -2.78073, 21.8679 to \
  -2.78073, 42.9428 front fs empty border lc rgb '#549f' lw 0.1
set object 2105 polygon from \
  -2.78605, 42.9644 to \
  -0.03, 42.9644 to \
  -0.03, 21.8795 to \
  -2.78605, 21.8795 to \
  -2.78605, 42.9644 front fs empty border lc rgb '#549f' lw 0.1
set object 2106 polygon from \
  -2.79064, 42.986 to \
  -0.03, 42.986 to \
  -0.03, 21.8911 to \
  -2.79064, 21.8911 to \
  -2.79064, 42.986 front fs empty border lc rgb '#549f' lw 0.1
set object 2107 polygon from \
  -2.79447, 43.0077 to \
  -0.03, 43.0077 to \
  -0.03, 21.9028 to \
  -2.79447, 21.9028 to \
  -2.79447, 43.0077 front fs empty border lc rgb '#549f' lw 0.1
set object 2108 polygon from \
  -2.79754, 43.0293 to \
  -0.03, 43.0293 to \
  -0.03, 21.9144 to \
  -2.79754, 21.9144 to \
  -2.79754, 43.0293 front fs empty border lc rgb '#549f' lw 0.1
set object 2109 polygon from \
  -2.79984, 43.0509 to \
  -0.03, 43.0509 to \
  -0.03, 21.926 to \
  -2.79984, 21.926 to \
  -2.79984, 43.0509 front fs empty border lc rgb '#549f' lw 0.1
set object 2110 polygon from \
  -2.80135, 43.0726 to \
  -0.03, 43.0726 to \
  -0.03, 21.9377 to \
  -2.80135, 21.9377 to \
  -2.80135, 43.0726 front fs empty border lc rgb '#549f' lw 0.1
set object 2111 polygon from \
  -2.80208, 43.0942 to \
  -0.03, 43.0942 to \
  -0.03, 21.9493 to \
  -2.80208, 21.9493 to \
  -2.80208, 43.0942 front fs empty border lc rgb '#549f' lw 0.1
set object 2112 polygon from \
  -2.80208, 43.1158 to \
  -0.03, 43.1158 to \
  -0.03, 21.9609 to \
  -2.80208, 21.9609 to \
  -2.80208, 43.1158 front fs empty border lc rgb '#549f' lw 0.1
set object 2113 polygon from \
  -2.80201, 43.1375 to \
  -0.03, 43.1375 to \
  -0.03, 21.9726 to \
  -2.80201, 21.9726 to \
  -2.80201, 43.1375 front fs empty border lc rgb '#549f' lw 0.1
set object 2114 polygon from \
  -2.80113, 43.1591 to \
  -0.03, 43.1591 to \
  -0.03, 21.9842 to \
  -2.80113, 21.9842 to \
  -2.80113, 43.1591 front fs empty border lc rgb '#549f' lw 0.1
set object 2115 polygon from \
  -2.79944, 43.1808 to \
  -0.03, 43.1808 to \
  -0.03, 21.9958 to \
  -2.79944, 21.9958 to \
  -2.79944, 43.1808 front fs empty border lc rgb '#549f' lw 0.1
set object 2116 polygon from \
  -2.79692, 43.2024 to \
  -0.03, 43.2024 to \
  -0.03, 22.0075 to \
  -2.79692, 22.0075 to \
  -2.79692, 43.2024 front fs empty border lc rgb '#549f' lw 0.1
set object 2117 polygon from \
  -2.79357, 43.2241 to \
  -0.03, 43.2241 to \
  -0.03, 22.0191 to \
  -2.79357, 22.0191 to \
  -2.79357, 43.2241 front fs empty border lc rgb '#549f' lw 0.1
set object 2118 polygon from \
  -2.78939, 43.2457 to \
  -0.03, 43.2457 to \
  -0.03, 22.0308 to \
  -2.78939, 22.0308 to \
  -2.78939, 43.2457 front fs empty border lc rgb '#549f' lw 0.1
set object 2119 polygon from \
  -2.78435, 43.2674 to \
  -0.03, 43.2674 to \
  -0.03, 22.0424 to \
  -2.78435, 22.0424 to \
  -2.78435, 43.2674 front fs empty border lc rgb '#549f' lw 0.1
set object 2120 polygon from \
  -2.77847, 43.289 to \
  -0.03, 43.289 to \
  -0.03, 22.0541 to \
  -2.77847, 22.0541 to \
  -2.77847, 43.289 front fs empty border lc rgb '#549f' lw 0.1
set object 2121 polygon from \
  -2.77173, 43.3107 to \
  -0.03, 43.3107 to \
  -0.03, 22.0657 to \
  -2.77173, 22.0657 to \
  -2.77173, 43.3107 front fs empty border lc rgb '#549f' lw 0.1
set object 2122 polygon from \
  -2.76413, 43.3323 to \
  -0.03, 43.3323 to \
  -0.03, 22.0773 to \
  -2.76413, 22.0773 to \
  -2.76413, 43.3323 front fs empty border lc rgb '#549f' lw 0.1
set object 2123 polygon from \
  -2.75566, 43.354 to \
  -0.03, 43.354 to \
  -0.03, 22.089 to \
  -2.75566, 22.089 to \
  -2.75566, 43.354 front fs empty border lc rgb '#549f' lw 0.1
set object 2124 polygon from \
  -2.74632, 43.3756 to \
  -0.03, 43.3756 to \
  -0.03, 22.1006 to \
  -2.74632, 22.1006 to \
  -2.74632, 43.3756 front fs empty border lc rgb '#549f' lw 0.1
set object 2125 polygon from \
  -2.7361, 43.3973 to \
  -0.03, 43.3973 to \
  -0.03, 22.1123 to \
  -2.7361, 22.1123 to \
  -2.7361, 43.3973 front fs empty border lc rgb '#549f' lw 0.1
set object 2126 polygon from \
  -2.725, 43.4189 to \
  -0.03, 43.4189 to \
  -0.03, 22.124 to \
  -2.725, 22.124 to \
  -2.725, 43.4189 front fs empty border lc rgb '#549f' lw 0.1
set object 2127 polygon from \
  -2.71301, 43.4406 to \
  -0.03, 43.4406 to \
  -0.03, 22.1356 to \
  -2.71301, 22.1356 to \
  -2.71301, 43.4406 front fs empty border lc rgb '#549f' lw 0.1
set object 2128 polygon from \
  -2.70014, 43.4622 to \
  -0.03, 43.4622 to \
  -0.03, 22.1473 to \
  -2.70014, 22.1473 to \
  -2.70014, 43.4622 front fs empty border lc rgb '#549f' lw 0.1
set object 2129 polygon from \
  -2.68638, 43.4839 to \
  -0.03, 43.4839 to \
  -0.03, 22.1589 to \
  -2.68638, 22.1589 to \
  -2.68638, 43.4839 front fs empty border lc rgb '#549f' lw 0.1
set object 2130 polygon from \
  -2.67421, 43.5056 to \
  -0.03, 43.5056 to \
  -0.03, 22.1706 to \
  -2.67421, 22.1706 to \
  -2.67421, 43.5056 front fs empty border lc rgb '#549f' lw 0.1
set object 2131 polygon from \
  -2.66228, 43.5272 to \
  -0.03, 43.5272 to \
  -0.03, 22.1822 to \
  -2.66228, 22.1822 to \
  -2.66228, 43.5272 front fs empty border lc rgb '#549f' lw 0.1
set object 2132 polygon from \
  -2.6495, 43.5489 to \
  -0.03, 43.5489 to \
  -0.03, 22.1939 to \
  -2.6495, 22.1939 to \
  -2.6495, 43.5489 front fs empty border lc rgb '#549f' lw 0.1
set object 2133 polygon from \
  -2.63615, 43.5706 to \
  -0.03, 43.5706 to \
  -0.03, 22.2056 to \
  -2.63615, 22.2056 to \
  -2.63615, 43.5706 front fs empty border lc rgb '#549f' lw 0.1
set object 2134 polygon from \
  -2.62206, 43.5922 to \
  -0.03, 43.5922 to \
  -0.03, 22.2172 to \
  -2.62206, 22.2172 to \
  -2.62206, 43.5922 front fs empty border lc rgb '#549f' lw 0.1
set object 2135 polygon from \
  -2.60712, 43.6139 to \
  -0.03, 43.6139 to \
  -0.03, 22.2289 to \
  -2.60712, 22.2289 to \
  -2.60712, 43.6139 front fs empty border lc rgb '#549f' lw 0.1
set object 2136 polygon from \
  -2.59131, 43.6356 to \
  -0.03, 43.6356 to \
  -0.03, 22.2406 to \
  -2.59131, 22.2406 to \
  -2.59131, 43.6356 front fs empty border lc rgb '#549f' lw 0.1
set object 2137 polygon from \
  -2.57465, 43.6572 to \
  -0.03, 43.6572 to \
  -0.03, 22.2522 to \
  -2.57465, 22.2522 to \
  -2.57465, 43.6572 front fs empty border lc rgb '#549f' lw 0.1
set object 2138 polygon from \
  -2.55713, 43.6789 to \
  -0.03, 43.6789 to \
  -0.03, 22.2639 to \
  -2.55713, 22.2639 to \
  -2.55713, 43.6789 front fs empty border lc rgb '#549f' lw 0.1
set object 2139 polygon from \
  -2.53874, 43.7006 to \
  -0.03, 43.7006 to \
  -0.03, 22.2756 to \
  -2.53874, 22.2756 to \
  -2.53874, 43.7006 front fs empty border lc rgb '#549f' lw 0.1
set object 2140 polygon from \
  -2.51949, 43.7222 to \
  -0.03, 43.7222 to \
  -0.03, 22.2872 to \
  -2.51949, 22.2872 to \
  -2.51949, 43.7222 front fs empty border lc rgb '#549f' lw 0.1
set object 2141 polygon from \
  -2.49938, 43.7439 to \
  -0.03, 43.7439 to \
  -0.03, 22.2989 to \
  -2.49938, 22.2989 to \
  -2.49938, 43.7439 front fs empty border lc rgb '#549f' lw 0.1
set object 2142 polygon from \
  -2.47841, 43.7656 to \
  -0.03, 43.7656 to \
  -0.03, 22.3106 to \
  -2.47841, 22.3106 to \
  -2.47841, 43.7656 front fs empty border lc rgb '#549f' lw 0.1
set object 2143 polygon from \
  -2.45658, 43.7873 to \
  -0.03, 43.7873 to \
  -0.03, 22.3222 to \
  -2.45658, 22.3222 to \
  -2.45658, 43.7873 front fs empty border lc rgb '#549f' lw 0.1
set object 2144 polygon from \
  -2.43389, 43.809 to \
  -0.03, 43.809 to \
  -0.03, 22.3339 to \
  -2.43389, 22.3339 to \
  -2.43389, 43.809 front fs empty border lc rgb '#549f' lw 0.1
set object 2145 polygon from \
  -2.41033, 43.8306 to \
  -0.03, 43.8306 to \
  -0.03, 22.3456 to \
  -2.41033, 22.3456 to \
  -2.41033, 43.8306 front fs empty border lc rgb '#549f' lw 0.1
set object 2146 polygon from \
  -2.38593, 43.8523 to \
  -0.03, 43.8523 to \
  -0.03, 22.3573 to \
  -2.38593, 22.3573 to \
  -2.38593, 43.8523 front fs empty border lc rgb '#549f' lw 0.1
set object 2147 polygon from \
  -2.37179, 43.874 to \
  -0.03, 43.874 to \
  -0.03, 22.369 to \
  -2.37179, 22.369 to \
  -2.37179, 43.874 front fs empty border lc rgb '#549f' lw 0.1
set object 2148 polygon from \
  -2.37956, 43.8957 to \
  -0.03, 43.8957 to \
  -0.03, 22.3806 to \
  -2.37956, 22.3806 to \
  -2.37956, 43.8957 front fs empty border lc rgb '#549f' lw 0.1
set object 2149 polygon from \
  -2.38598, 43.9174 to \
  -0.03, 43.9174 to \
  -0.03, 22.3923 to \
  -2.38598, 22.3923 to \
  -2.38598, 43.9174 front fs empty border lc rgb '#549f' lw 0.1
set object 2150 polygon from \
  -2.39103, 43.9391 to \
  -0.03, 43.9391 to \
  -0.03, 22.404 to \
  -2.39103, 22.404 to \
  -2.39103, 43.9391 front fs empty border lc rgb '#549f' lw 0.1
set object 2151 polygon from \
  -2.39473, 43.9608 to \
  -0.03, 43.9608 to \
  -0.03, 22.4157 to \
  -2.39473, 22.4157 to \
  -2.39473, 43.9608 front fs empty border lc rgb '#549f' lw 0.1
set object 2152 polygon from \
  -2.39707, 43.9824 to \
  -0.03, 43.9824 to \
  -0.03, 22.4274 to \
  -2.39707, 22.4274 to \
  -2.39707, 43.9824 front fs empty border lc rgb '#549f' lw 0.1
set object 2153 polygon from \
  -2.39803, 44.0041 to \
  -0.03, 44.0041 to \
  -0.03, 22.4391 to \
  -2.39803, 22.4391 to \
  -2.39803, 44.0041 front fs empty border lc rgb '#549f' lw 0.1
set object 2154 polygon from \
  -2.39803, 44.0258 to \
  -0.03, 44.0258 to \
  -0.03, 22.4507 to \
  -2.39803, 22.4507 to \
  -2.39803, 44.0258 front fs empty border lc rgb '#549f' lw 0.1
set object 2155 polygon from \
  -2.39763, 44.0475 to \
  -0.03, 44.0475 to \
  -0.03, 22.4624 to \
  -2.39763, 22.4624 to \
  -2.39763, 44.0475 front fs empty border lc rgb '#549f' lw 0.1
set object 2156 polygon from \
  -2.39587, 44.0692 to \
  -0.03, 44.0692 to \
  -0.03, 22.4741 to \
  -2.39587, 22.4741 to \
  -2.39587, 44.0692 front fs empty border lc rgb '#549f' lw 0.1
set object 2157 polygon from \
  -2.39273, 44.0909 to \
  -0.03, 44.0909 to \
  -0.03, 22.4858 to \
  -2.39273, 22.4858 to \
  -2.39273, 44.0909 front fs empty border lc rgb '#549f' lw 0.1
set object 2158 polygon from \
  -2.38823, 44.1126 to \
  -0.03, 44.1126 to \
  -0.03, 22.4975 to \
  -2.38823, 22.4975 to \
  -2.38823, 44.1126 front fs empty border lc rgb '#549f' lw 0.1
set object 2159 polygon from \
  -2.38237, 44.1343 to \
  -0.03, 44.1343 to \
  -0.03, 22.5092 to \
  -2.38237, 22.5092 to \
  -2.38237, 44.1343 front fs empty border lc rgb '#549f' lw 0.1
set object 2160 polygon from \
  -2.37515, 44.156 to \
  -0.03, 44.156 to \
  -0.03, 22.5209 to \
  -2.37515, 22.5209 to \
  -2.37515, 44.156 front fs empty border lc rgb '#549f' lw 0.1
set object 2161 polygon from \
  -2.36657, 44.1777 to \
  -0.03, 44.1777 to \
  -0.03, 22.5326 to \
  -2.36657, 22.5326 to \
  -2.36657, 44.1777 front fs empty border lc rgb '#549f' lw 0.1
set object 2162 polygon from \
  -2.35664, 44.1994 to \
  -0.03, 44.1994 to \
  -0.03, 22.5443 to \
  -2.35664, 22.5443 to \
  -2.35664, 44.1994 front fs empty border lc rgb '#549f' lw 0.1
set object 2163 polygon from \
  -2.34537, 44.2211 to \
  -0.03, 44.2211 to \
  -0.03, 22.556 to \
  -2.34537, 22.556 to \
  -2.34537, 44.2211 front fs empty border lc rgb '#549f' lw 0.1
set object 2164 polygon from \
  -2.33276, 44.2428 to \
  -0.03, 44.2428 to \
  -0.03, 22.5677 to \
  -2.33276, 22.5677 to \
  -2.33276, 44.2428 front fs empty border lc rgb '#549f' lw 0.1
set object 2165 polygon from \
  -2.31883, 44.2645 to \
  -0.03, 44.2645 to \
  -0.03, 22.5794 to \
  -2.31883, 22.5794 to \
  -2.31883, 44.2645 front fs empty border lc rgb '#549f' lw 0.1
set object 2166 polygon from \
  -2.30357, 44.2862 to \
  -0.03, 44.2862 to \
  -0.03, 22.5911 to \
  -2.30357, 22.5911 to \
  -2.30357, 44.2862 front fs empty border lc rgb '#549f' lw 0.1
set object 2167 polygon from \
  -2.287, 44.3079 to \
  -0.03, 44.3079 to \
  -0.03, 22.6028 to \
  -2.287, 22.6028 to \
  -2.287, 44.3079 front fs empty border lc rgb '#549f' lw 0.1
set object 2168 polygon from \
  -2.26913, 44.3296 to \
  -0.03, 44.3296 to \
  -0.03, 22.6145 to \
  -2.26913, 22.6145 to \
  -2.26913, 44.3296 front fs empty border lc rgb '#549f' lw 0.1
set object 2169 polygon from \
  -2.24997, 44.3514 to \
  -0.03, 44.3514 to \
  -0.03, 22.6262 to \
  -2.24997, 22.6262 to \
  -2.24997, 44.3514 front fs empty border lc rgb '#549f' lw 0.1
set object 2170 polygon from \
  -2.22953, 44.3731 to \
  -0.03, 44.3731 to \
  -0.03, 22.6379 to \
  -2.22953, 22.6379 to \
  -2.22953, 44.3731 front fs empty border lc rgb '#549f' lw 0.1
set object 2171 polygon from \
  -2.20783, 44.3948 to \
  -0.03, 44.3948 to \
  -0.03, 22.6496 to \
  -2.20783, 22.6496 to \
  -2.20783, 44.3948 front fs empty border lc rgb '#549f' lw 0.1
set object 2172 polygon from \
  -2.18487, 44.4165 to \
  -0.03, 44.4165 to \
  -0.03, 22.6613 to \
  -2.18487, 22.6613 to \
  -2.18487, 44.4165 front fs empty border lc rgb '#549f' lw 0.1
set object 2173 polygon from \
  -2.16068, 44.4382 to \
  -0.03, 44.4382 to \
  -0.03, 22.6731 to \
  -2.16068, 22.6731 to \
  -2.16068, 44.4382 front fs empty border lc rgb '#549f' lw 0.1
set object 2174 polygon from \
  -2.13528, 44.4599 to \
  -0.03, 44.4599 to \
  -0.03, 22.6848 to \
  -2.13528, 22.6848 to \
  -2.13528, 44.4599 front fs empty border lc rgb '#549f' lw 0.1
set object 2175 polygon from \
  -2.10866, 44.4816 to \
  -0.03, 44.4816 to \
  -0.03, 22.6965 to \
  -2.10866, 22.6965 to \
  -2.10866, 44.4816 front fs empty border lc rgb '#549f' lw 0.1
set object 2176 polygon from \
  -2.08086, 44.5034 to \
  -0.03, 44.5034 to \
  -0.03, 22.7082 to \
  -2.08086, 22.7082 to \
  -2.08086, 44.5034 front fs empty border lc rgb '#549f' lw 0.1
set object 2177 polygon from \
  -2.05189, 44.5251 to \
  -0.03, 44.5251 to \
  -0.03, 22.7199 to \
  -2.05189, 22.7199 to \
  -2.05189, 44.5251 front fs empty border lc rgb '#549f' lw 0.1
set object 2178 polygon from \
  -2.02177, 44.5468 to \
  -0.03, 44.5468 to \
  -0.03, 22.7316 to \
  -2.02177, 22.7316 to \
  -2.02177, 44.5468 front fs empty border lc rgb '#549f' lw 0.1
set object 2179 polygon from \
  -1.99052, 44.5685 to \
  -0.03, 44.5685 to \
  -0.03, 22.7434 to \
  -1.99052, 22.7434 to \
  -1.99052, 44.5685 front fs empty border lc rgb '#549f' lw 0.1
set object 2180 polygon from \
  -1.95815, 44.5902 to \
  -0.03, 44.5902 to \
  -0.03, 22.7551 to \
  -1.95815, 22.7551 to \
  -1.95815, 44.5902 front fs empty border lc rgb '#549f' lw 0.1
set object 2181 polygon from \
  -1.9247, 44.612 to \
  -0.03, 44.612 to \
  -0.03, 22.7668 to \
  -1.9247, 22.7668 to \
  -1.9247, 44.612 front fs empty border lc rgb '#549f' lw 0.1
set object 2182 polygon from \
  -1.89017, 44.6337 to \
  -0.03, 44.6337 to \
  -0.03, 22.7785 to \
  -1.89017, 22.7785 to \
  -1.89017, 44.6337 front fs empty border lc rgb '#549f' lw 0.1
set object 2183 polygon from \
  -1.8546, 44.6554 to \
  -0.03, 44.6554 to \
  -0.03, 22.7902 to \
  -1.8546, 22.7902 to \
  -1.8546, 44.6554 front fs empty border lc rgb '#549f' lw 0.1
set object 2184 polygon from \
  -1.85212, 44.6772 to \
  -0.03, 44.6772 to \
  -0.03, 22.802 to \
  -1.85212, 22.802 to \
  -1.85212, 44.6772 front fs empty border lc rgb '#549f' lw 0.1
set object 2185 polygon from \
  -1.86581, 44.6989 to \
  -0.03, 44.6989 to \
  -0.03, 22.8137 to \
  -1.86581, 22.8137 to \
  -1.86581, 44.6989 front fs empty border lc rgb '#549f' lw 0.1
set object 2186 polygon from \
  -1.87874, 44.7206 to \
  -0.03, 44.7206 to \
  -0.03, 22.8254 to \
  -1.87874, 22.8254 to \
  -1.87874, 44.7206 front fs empty border lc rgb '#549f' lw 0.1
set object 2187 polygon from \
  -1.89091, 44.7424 to \
  -0.03, 44.7424 to \
  -0.03, 22.8372 to \
  -1.89091, 22.8372 to \
  -1.89091, 44.7424 front fs empty border lc rgb '#549f' lw 0.1
set object 2188 polygon from \
  -1.90234, 44.7641 to \
  -0.03, 44.7641 to \
  -0.03, 22.8489 to \
  -1.90234, 22.8489 to \
  -1.90234, 44.7641 front fs empty border lc rgb '#549f' lw 0.1
set object 2189 polygon from \
  -1.91302, 44.7858 to \
  -0.03, 44.7858 to \
  -0.03, 22.8606 to \
  -1.91302, 22.8606 to \
  -1.91302, 44.7858 front fs empty border lc rgb '#549f' lw 0.1
set object 2190 polygon from \
  -1.92297, 44.8076 to \
  -0.03, 44.8076 to \
  -0.03, 22.8724 to \
  -1.92297, 22.8724 to \
  -1.92297, 44.8076 front fs empty border lc rgb '#549f' lw 0.1
set object 2191 polygon from \
  -1.93219, 44.8293 to \
  -0.03, 44.8293 to \
  -0.03, 22.8841 to \
  -1.93219, 22.8841 to \
  -1.93219, 44.8293 front fs empty border lc rgb '#549f' lw 0.1
set object 2192 polygon from \
  -1.9407, 44.851 to \
  -0.03, 44.851 to \
  -0.03, 22.8958 to \
  -1.9407, 22.8958 to \
  -1.9407, 44.851 front fs empty border lc rgb '#549f' lw 0.1
set object 2193 polygon from \
  -1.94849, 44.8728 to \
  -0.03, 44.8728 to \
  -0.03, 22.9076 to \
  -1.94849, 22.9076 to \
  -1.94849, 44.8728 front fs empty border lc rgb '#549f' lw 0.1
set object 2194 polygon from \
  -1.95559, 44.8945 to \
  -0.03, 44.8945 to \
  -0.03, 22.9193 to \
  -1.95559, 22.9193 to \
  -1.95559, 44.8945 front fs empty border lc rgb '#549f' lw 0.1
set object 2195 polygon from \
  -1.96199, 44.9163 to \
  -0.03, 44.9163 to \
  -0.03, 22.931 to \
  -1.96199, 22.931 to \
  -1.96199, 44.9163 front fs empty border lc rgb '#549f' lw 0.1
set object 2196 polygon from \
  -1.96771, 44.938 to \
  -0.03, 44.938 to \
  -0.03, 22.9428 to \
  -1.96771, 22.9428 to \
  -1.96771, 44.938 front fs empty border lc rgb '#549f' lw 0.1
set object 2197 polygon from \
  -1.97275, 44.9598 to \
  -0.03, 44.9598 to \
  -0.03, 22.9545 to \
  -1.97275, 22.9545 to \
  -1.97275, 44.9598 front fs empty border lc rgb '#549f' lw 0.1
set object 2198 polygon from \
  -1.97713, 44.9815 to \
  -0.03, 44.9815 to \
  -0.03, 22.9663 to \
  -1.97713, 22.9663 to \
  -1.97713, 44.9815 front fs empty border lc rgb '#549f' lw 0.1
set object 2199 polygon from \
  -1.98086, 45.0033 to \
  -0.03, 45.0033 to \
  -0.03, 22.978 to \
  -1.98086, 22.978 to \
  -1.98086, 45.0033 front fs empty border lc rgb '#549f' lw 0.1
set object 2200 polygon from \
  -1.98395, 45.025 to \
  -0.03, 45.025 to \
  -0.03, 22.9898 to \
  -1.98395, 22.9898 to \
  -1.98395, 45.025 front fs empty border lc rgb '#549f' lw 0.1
set object 2201 polygon from \
  -1.98641, 45.0468 to \
  -0.03, 45.0468 to \
  -0.03, 23.0015 to \
  -1.98641, 23.0015 to \
  -1.98641, 45.0468 front fs empty border lc rgb '#549f' lw 0.1
set object 2202 polygon from \
  -1.98825, 45.0685 to \
  -0.03, 45.0685 to \
  -0.03, 23.0132 to \
  -1.98825, 23.0132 to \
  -1.98825, 45.0685 front fs empty border lc rgb '#549f' lw 0.1
set object 2203 polygon from \
  -1.98948, 45.0903 to \
  -0.03, 45.0903 to \
  -0.03, 23.025 to \
  -1.98948, 23.025 to \
  -1.98948, 45.0903 front fs empty border lc rgb '#549f' lw 0.1
set object 2204 polygon from \
  -1.99215, 45.112 to \
  -0.03, 45.112 to \
  -0.03, 23.0367 to \
  -1.99215, 23.0367 to \
  -1.99215, 45.112 front fs empty border lc rgb '#549f' lw 0.1
set object 2205 polygon from \
  -2.04076, 45.1338 to \
  -0.03, 45.1338 to \
  -0.03, 23.0485 to \
  -2.04076, 23.0485 to \
  -2.04076, 45.1338 front fs empty border lc rgb '#549f' lw 0.1
set object 2206 polygon from \
  -2.08897, 45.1555 to \
  -0.03, 45.1555 to \
  -0.03, 23.0603 to \
  -2.08897, 23.0603 to \
  -2.08897, 45.1555 front fs empty border lc rgb '#549f' lw 0.1
set object 2207 polygon from \
  -2.13673, 45.1773 to \
  -0.03, 45.1773 to \
  -0.03, 23.072 to \
  -2.13673, 23.072 to \
  -2.13673, 45.1773 front fs empty border lc rgb '#549f' lw 0.1
set object 2208 polygon from \
  -2.18403, 45.199 to \
  -0.03, 45.199 to \
  -0.03, 23.0838 to \
  -2.18403, 23.0838 to \
  -2.18403, 45.199 front fs empty border lc rgb '#549f' lw 0.1
set object 2209 polygon from \
  -2.23085, 45.2208 to \
  -0.03, 45.2208 to \
  -0.03, 23.0955 to \
  -2.23085, 23.0955 to \
  -2.23085, 45.2208 front fs empty border lc rgb '#549f' lw 0.1
set object 2210 polygon from \
  -2.27717, 45.2426 to \
  -0.03, 45.2426 to \
  -0.03, 23.1073 to \
  -2.27717, 23.1073 to \
  -2.27717, 45.2426 front fs empty border lc rgb '#549f' lw 0.1
set object 2211 polygon from \
  -2.32297, 45.2643 to \
  -0.03, 45.2643 to \
  -0.03, 23.119 to \
  -2.32297, 23.119 to \
  -2.32297, 45.2643 front fs empty border lc rgb '#549f' lw 0.1
set object 2212 polygon from \
  -2.36822, 45.2861 to \
  -0.03, 45.2861 to \
  -0.03, 23.1308 to \
  -2.36822, 23.1308 to \
  -2.36822, 45.2861 front fs empty border lc rgb '#549f' lw 0.1
set object 2213 polygon from \
  -2.41292, 45.3079 to \
  -0.03, 45.3079 to \
  -0.03, 23.1426 to \
  -2.41292, 23.1426 to \
  -2.41292, 45.3079 front fs empty border lc rgb '#549f' lw 0.1
set object 2214 polygon from \
  -2.45704, 45.3296 to \
  -0.03, 45.3296 to \
  -0.03, 23.1543 to \
  -2.45704, 23.1543 to \
  -2.45704, 45.3296 front fs empty border lc rgb '#549f' lw 0.1
set object 2215 polygon from \
  -2.50055, 45.3514 to \
  -0.03, 45.3514 to \
  -0.03, 23.1661 to \
  -2.50055, 23.1661 to \
  -2.50055, 45.3514 front fs empty border lc rgb '#549f' lw 0.1
set object 2216 polygon from \
  -2.54345, 45.3732 to \
  -0.03, 45.3732 to \
  -0.03, 23.1779 to \
  -2.54345, 23.1779 to \
  -2.54345, 45.3732 front fs empty border lc rgb '#549f' lw 0.1
set object 2217 polygon from \
  -2.58571, 45.3949 to \
  -0.03, 45.3949 to \
  -0.03, 23.1896 to \
  -2.58571, 23.1896 to \
  -2.58571, 45.3949 front fs empty border lc rgb '#549f' lw 0.1
set object 2218 polygon from \
  -2.62732, 45.4167 to \
  -0.03, 45.4167 to \
  -0.03, 23.2014 to \
  -2.62732, 23.2014 to \
  -2.62732, 45.4167 front fs empty border lc rgb '#549f' lw 0.1
set object 2219 polygon from \
  -2.66825, 45.4385 to \
  -0.03, 45.4385 to \
  -0.03, 23.2132 to \
  -2.66825, 23.2132 to \
  -2.66825, 45.4385 front fs empty border lc rgb '#549f' lw 0.1
set object 2220 polygon from \
  -2.70848, 45.4603 to \
  -0.03, 45.4603 to \
  -0.03, 23.2249 to \
  -2.70848, 23.2249 to \
  -2.70848, 45.4603 front fs empty border lc rgb '#549f' lw 0.1
set object 2221 polygon from \
  -2.74801, 45.482 to \
  -0.03, 45.482 to \
  -0.03, 23.2367 to \
  -2.74801, 23.2367 to \
  -2.74801, 45.482 front fs empty border lc rgb '#549f' lw 0.1
set object 2222 polygon from \
  -2.78681, 45.5038 to \
  -0.03, 45.5038 to \
  -0.03, 23.2485 to \
  -2.78681, 23.2485 to \
  -2.78681, 45.5038 front fs empty border lc rgb '#549f' lw 0.1
set object 2223 polygon from \
  -2.82486, 45.5256 to \
  -0.03, 45.5256 to \
  -0.03, 23.2602 to \
  -2.82486, 23.2602 to \
  -2.82486, 45.5256 front fs empty border lc rgb '#549f' lw 0.1
set object 2224 polygon from \
  -2.86214, 45.5474 to \
  -0.03, 45.5474 to \
  -0.03, 23.272 to \
  -2.86214, 23.272 to \
  -2.86214, 45.5474 front fs empty border lc rgb '#549f' lw 0.1
set object 2225 polygon from \
  -2.89865, 45.5691 to \
  -0.03, 45.5691 to \
  -0.03, 23.2838 to \
  -2.89865, 23.2838 to \
  -2.89865, 45.5691 front fs empty border lc rgb '#549f' lw 0.1
set object 2226 polygon from \
  -2.93435, 45.5909 to \
  -0.03, 45.5909 to \
  -0.03, 23.2956 to \
  -2.93435, 23.2956 to \
  -2.93435, 45.5909 front fs empty border lc rgb '#549f' lw 0.1
set object 2227 polygon from \
  -2.96925, 45.6127 to \
  -0.03, 45.6127 to \
  -0.03, 23.3074 to \
  -2.96925, 23.3074 to \
  -2.96925, 45.6127 front fs empty border lc rgb '#549f' lw 0.1
set object 2228 polygon from \
  -3.00331, 45.6345 to \
  -0.03, 45.6345 to \
  -0.03, 23.3191 to \
  -3.00331, 23.3191 to \
  -3.00331, 45.6345 front fs empty border lc rgb '#549f' lw 0.1
set object 2229 polygon from \
  -3.03653, 45.6563 to \
  -0.03, 45.6563 to \
  -0.03, 23.3309 to \
  -3.03653, 23.3309 to \
  -3.03653, 45.6563 front fs empty border lc rgb '#549f' lw 0.1
set object 2230 polygon from \
  -3.06888, 45.6781 to \
  -0.03, 45.6781 to \
  -0.03, 23.3427 to \
  -3.06888, 23.3427 to \
  -3.06888, 45.6781 front fs empty border lc rgb '#549f' lw 0.1
set object 2231 polygon from \
  -3.10036, 45.6999 to \
  -0.03, 45.6999 to \
  -0.03, 23.3545 to \
  -3.10036, 23.3545 to \
  -3.10036, 45.6999 front fs empty border lc rgb '#549f' lw 0.1
set object 2232 polygon from \
  -3.13094, 45.7216 to \
  -0.03, 45.7216 to \
  -0.03, 23.3663 to \
  -3.13094, 23.3663 to \
  -3.13094, 45.7216 front fs empty border lc rgb '#549f' lw 0.1
set object 2233 polygon from \
  -3.16062, 45.7434 to \
  -0.03, 45.7434 to \
  -0.03, 23.3781 to \
  -3.16062, 23.3781 to \
  -3.16062, 45.7434 front fs empty border lc rgb '#549f' lw 0.1
set object 2234 polygon from \
  -3.18938, 45.7652 to \
  -0.03, 45.7652 to \
  -0.03, 23.3898 to \
  -3.18938, 23.3898 to \
  -3.18938, 45.7652 front fs empty border lc rgb '#549f' lw 0.1
set object 2235 polygon from \
  -3.2172, 45.787 to \
  -0.03, 45.787 to \
  -0.03, 23.4016 to \
  -3.2172, 23.4016 to \
  -3.2172, 45.787 front fs empty border lc rgb '#549f' lw 0.1
set object 2236 polygon from \
  -3.24408, 45.8088 to \
  -0.03, 45.8088 to \
  -0.03, 23.4134 to \
  -3.24408, 23.4134 to \
  -3.24408, 45.8088 front fs empty border lc rgb '#549f' lw 0.1
set object 2237 polygon from \
  -3.26999, 45.8306 to \
  -0.03, 45.8306 to \
  -0.03, 23.4252 to \
  -3.26999, 23.4252 to \
  -3.26999, 45.8306 front fs empty border lc rgb '#549f' lw 0.1
set object 2238 polygon from \
  -3.29493, 45.8524 to \
  -0.03, 45.8524 to \
  -0.03, 23.437 to \
  -3.29493, 23.437 to \
  -3.29493, 45.8524 front fs empty border lc rgb '#549f' lw 0.1
set object 2239 polygon from \
  -3.31889, 45.8742 to \
  -0.03, 45.8742 to \
  -0.03, 23.4488 to \
  -3.31889, 23.4488 to \
  -3.31889, 45.8742 front fs empty border lc rgb '#549f' lw 0.1
set object 2240 polygon from \
  -3.34184, 45.896 to \
  -0.03, 45.896 to \
  -0.03, 23.4606 to \
  -3.34184, 23.4606 to \
  -3.34184, 45.896 front fs empty border lc rgb '#549f' lw 0.1
set object 2241 polygon from \
  -3.36379, 45.9178 to \
  -0.03, 45.9178 to \
  -0.03, 23.4724 to \
  -3.36379, 23.4724 to \
  -3.36379, 45.9178 front fs empty border lc rgb '#549f' lw 0.1
set object 2242 polygon from \
  -3.38472, 45.9396 to \
  -0.03, 45.9396 to \
  -0.03, 23.4842 to \
  -3.38472, 23.4842 to \
  -3.38472, 45.9396 front fs empty border lc rgb '#549f' lw 0.1
set object 2243 polygon from \
  -3.40461, 45.9614 to \
  -0.03, 45.9614 to \
  -0.03, 23.496 to \
  -3.40461, 23.496 to \
  -3.40461, 45.9614 front fs empty border lc rgb '#549f' lw 0.1
set object 2244 polygon from \
  -3.42347, 45.9832 to \
  -0.03, 45.9832 to \
  -0.03, 23.5078 to \
  -3.42347, 23.5078 to \
  -3.42347, 45.9832 front fs empty border lc rgb '#549f' lw 0.1
set object 2245 polygon from \
  -3.44127, 46.005 to \
  -0.03, 46.005 to \
  -0.03, 23.5196 to \
  -3.44127, 23.5196 to \
  -3.44127, 46.005 front fs empty border lc rgb '#549f' lw 0.1
set object 2246 polygon from \
  -3.45802, 46.0268 to \
  -0.03, 46.0268 to \
  -0.03, 23.5314 to \
  -3.45802, 23.5314 to \
  -3.45802, 46.0268 front fs empty border lc rgb '#549f' lw 0.1
set object 2247 polygon from \
  -3.47369, 46.0486 to \
  -0.03, 46.0486 to \
  -0.03, 23.5432 to \
  -3.47369, 23.5432 to \
  -3.47369, 46.0486 front fs empty border lc rgb '#549f' lw 0.1
set object 2248 polygon from \
  -3.48829, 46.0704 to \
  -0.03, 46.0704 to \
  -0.03, 23.555 to \
  -3.48829, 23.555 to \
  -3.48829, 46.0704 front fs empty border lc rgb '#549f' lw 0.1
set object 2249 polygon from \
  -3.50181, 46.0923 to \
  -0.03, 46.0923 to \
  -0.03, 23.5668 to \
  -3.50181, 23.5668 to \
  -3.50181, 46.0923 front fs empty border lc rgb '#549f' lw 0.1
set object 2250 polygon from \
  -3.51423, 46.1141 to \
  -0.03, 46.1141 to \
  -0.03, 23.5786 to \
  -3.51423, 23.5786 to \
  -3.51423, 46.1141 front fs empty border lc rgb '#549f' lw 0.1
set object 2251 polygon from \
  -3.52555, 46.1359 to \
  -0.03, 46.1359 to \
  -0.03, 23.5904 to \
  -3.52555, 23.5904 to \
  -3.52555, 46.1359 front fs empty border lc rgb '#549f' lw 0.1
set object 2252 polygon from \
  -3.53577, 46.1577 to \
  -0.03, 46.1577 to \
  -0.03, 23.6022 to \
  -3.53577, 23.6022 to \
  -3.53577, 46.1577 front fs empty border lc rgb '#549f' lw 0.1
set object 2253 polygon from \
  -3.54488, 46.1795 to \
  -0.03, 46.1795 to \
  -0.03, 23.6141 to \
  -3.54488, 23.6141 to \
  -3.54488, 46.1795 front fs empty border lc rgb '#549f' lw 0.1
set object 2254 polygon from \
  -3.55287, 46.2013 to \
  -0.03, 46.2013 to \
  -0.03, 23.6259 to \
  -3.55287, 23.6259 to \
  -3.55287, 46.2013 front fs empty border lc rgb '#549f' lw 0.1
set object 2255 polygon from \
  -3.55974, 46.2231 to \
  -0.03, 46.2231 to \
  -0.03, 23.6377 to \
  -3.55974, 23.6377 to \
  -3.55974, 46.2231 front fs empty border lc rgb '#549f' lw 0.1
set object 2256 polygon from \
  -3.56548, 46.245 to \
  -0.03, 46.245 to \
  -0.03, 23.6495 to \
  -3.56548, 23.6495 to \
  -3.56548, 46.245 front fs empty border lc rgb '#549f' lw 0.1
set object 2257 polygon from \
  -3.57009, 46.2668 to \
  -0.03, 46.2668 to \
  -0.03, 23.6613 to \
  -3.57009, 23.6613 to \
  -3.57009, 46.2668 front fs empty border lc rgb '#549f' lw 0.1
set object 2258 polygon from \
  -3.57357, 46.2886 to \
  -0.03, 46.2886 to \
  -0.03, 23.6731 to \
  -3.57357, 23.6731 to \
  -3.57357, 46.2886 front fs empty border lc rgb '#549f' lw 0.1
set object 2259 polygon from \
  -3.57591, 46.3104 to \
  -0.03, 46.3104 to \
  -0.03, 23.685 to \
  -3.57591, 23.685 to \
  -3.57591, 46.3104 front fs empty border lc rgb '#549f' lw 0.1
set object 2260 polygon from \
  -3.57712, 46.3323 to \
  -0.03, 46.3323 to \
  -0.03, 23.6968 to \
  -3.57712, 23.6968 to \
  -3.57712, 46.3323 front fs empty border lc rgb '#549f' lw 0.1
set object 2261 polygon from \
  -3.57718, 46.3541 to \
  -0.03, 46.3541 to \
  -0.03, 23.7086 to \
  -3.57718, 23.7086 to \
  -3.57718, 46.3541 front fs empty border lc rgb '#549f' lw 0.1
set object 2262 polygon from \
  -3.57718, 46.3759 to \
  -0.03, 46.3759 to \
  -0.03, 23.7204 to \
  -3.57718, 23.7204 to \
  -3.57718, 46.3759 front fs empty border lc rgb '#549f' lw 0.1
set object 2263 polygon from \
  -3.5761, 46.3977 to \
  -0.03, 46.3977 to \
  -0.03, 23.7322 to \
  -3.5761, 23.7322 to \
  -3.5761, 46.3977 front fs empty border lc rgb '#549f' lw 0.1
set object 2264 polygon from \
  -3.57388, 46.4196 to \
  -0.03, 46.4196 to \
  -0.03, 23.7441 to \
  -3.57388, 23.7441 to \
  -3.57388, 46.4196 front fs empty border lc rgb '#549f' lw 0.1
set object 2265 polygon from \
  -3.57051, 46.4414 to \
  -0.03, 46.4414 to \
  -0.03, 23.7559 to \
  -3.57051, 23.7559 to \
  -3.57051, 46.4414 front fs empty border lc rgb '#549f' lw 0.1
set object 2266 polygon from \
  -3.56601, 46.4632 to \
  -0.03, 46.4632 to \
  -0.03, 23.7677 to \
  -3.56601, 23.7677 to \
  -3.56601, 46.4632 front fs empty border lc rgb '#549f' lw 0.1
set object 2267 polygon from \
  -3.56036, 46.4851 to \
  -0.03, 46.4851 to \
  -0.03, 23.7796 to \
  -3.56036, 23.7796 to \
  -3.56036, 46.4851 front fs empty border lc rgb '#549f' lw 0.1
set object 2268 polygon from \
  -3.55357, 46.5069 to \
  -0.03, 46.5069 to \
  -0.03, 23.7914 to \
  -3.55357, 23.7914 to \
  -3.55357, 46.5069 front fs empty border lc rgb '#549f' lw 0.1
set object 2269 polygon from \
  -3.54564, 46.5287 to \
  -0.03, 46.5287 to \
  -0.03, 23.8032 to \
  -3.54564, 23.8032 to \
  -3.54564, 46.5287 front fs empty border lc rgb '#549f' lw 0.1
set object 2270 polygon from \
  -3.53657, 46.5506 to \
  -0.03, 46.5506 to \
  -0.03, 23.8151 to \
  -3.53657, 23.8151 to \
  -3.53657, 46.5506 front fs empty border lc rgb '#549f' lw 0.1
set object 2271 polygon from \
  -3.52661, 46.5724 to \
  -0.03, 46.5724 to \
  -0.03, 23.8269 to \
  -3.52661, 23.8269 to \
  -3.52661, 46.5724 front fs empty border lc rgb '#549f' lw 0.1
set object 2272 polygon from \
  -3.52139, 46.5942 to \
  -0.03, 46.5942 to \
  -0.03, 23.8387 to \
  -3.52139, 23.8387 to \
  -3.52139, 46.5942 front fs empty border lc rgb '#549f' lw 0.1
set object 2273 polygon from \
  -3.52453, 46.6161 to \
  -0.03, 46.6161 to \
  -0.03, 23.8506 to \
  -3.52453, 23.8506 to \
  -3.52453, 46.6161 front fs empty border lc rgb '#549f' lw 0.1
set object 2274 polygon from \
  -3.53074, 46.6379 to \
  -0.03, 46.6379 to \
  -0.03, 23.8624 to \
  -3.53074, 23.8624 to \
  -3.53074, 46.6379 front fs empty border lc rgb '#549f' lw 0.1
set object 2275 polygon from \
  -3.53724, 46.6598 to \
  -0.03, 46.6598 to \
  -0.03, 23.8742 to \
  -3.53724, 23.8742 to \
  -3.53724, 46.6598 front fs empty border lc rgb '#549f' lw 0.1
set object 2276 polygon from \
  -3.54259, 46.6816 to \
  -0.03, 46.6816 to \
  -0.03, 23.8861 to \
  -3.54259, 23.8861 to \
  -3.54259, 46.6816 front fs empty border lc rgb '#549f' lw 0.1
set object 2277 polygon from \
  -3.5468, 46.7035 to \
  -0.03, 46.7035 to \
  -0.03, 23.8979 to \
  -3.5468, 23.8979 to \
  -3.5468, 46.7035 front fs empty border lc rgb '#549f' lw 0.1
set object 2278 polygon from \
  -3.54986, 46.7253 to \
  -0.03, 46.7253 to \
  -0.03, 23.9098 to \
  -3.54986, 23.9098 to \
  -3.54986, 46.7253 front fs empty border lc rgb '#549f' lw 0.1
set object 2279 polygon from \
  -3.55178, 46.7472 to \
  -0.03, 46.7472 to \
  -0.03, 23.9216 to \
  -3.55178, 23.9216 to \
  -3.55178, 46.7472 front fs empty border lc rgb '#549f' lw 0.1
set object 2280 polygon from \
  -3.55256, 46.769 to \
  -0.03, 46.769 to \
  -0.03, 23.9335 to \
  -3.55256, 23.9335 to \
  -3.55256, 46.769 front fs empty border lc rgb '#549f' lw 0.1
set object 2281 polygon from \
  -3.55256, 46.7909 to \
  -0.03, 46.7909 to \
  -0.03, 23.9453 to \
  -3.55256, 23.9453 to \
  -3.55256, 46.7909 front fs empty border lc rgb '#549f' lw 0.1
set object 2282 polygon from \
  -3.55221, 46.8127 to \
  -0.03, 46.8127 to \
  -0.03, 23.9571 to \
  -3.55221, 23.9571 to \
  -3.55221, 46.8127 front fs empty border lc rgb '#549f' lw 0.1
set object 2283 polygon from \
  -3.55071, 46.8346 to \
  -0.03, 46.8346 to \
  -0.03, 23.969 to \
  -3.55071, 23.969 to \
  -3.55071, 46.8346 front fs empty border lc rgb '#549f' lw 0.1
set object 2284 polygon from \
  -3.54809, 46.8564 to \
  -0.03, 46.8564 to \
  -0.03, 23.9808 to \
  -3.54809, 23.9808 to \
  -3.54809, 46.8564 front fs empty border lc rgb '#549f' lw 0.1
set object 2285 polygon from \
  -3.54433, 46.8783 to \
  -0.03, 46.8783 to \
  -0.03, 23.9927 to \
  -3.54433, 23.9927 to \
  -3.54433, 46.8783 front fs empty border lc rgb '#549f' lw 0.1
set object 2286 polygon from \
  -3.53945, 46.9001 to \
  -0.03, 46.9001 to \
  -0.03, 24.0046 to \
  -3.53945, 24.0046 to \
  -3.53945, 46.9001 front fs empty border lc rgb '#549f' lw 0.1
set object 2287 polygon from \
  -3.53344, 46.922 to \
  -0.03, 46.922 to \
  -0.03, 24.0164 to \
  -3.53344, 24.0164 to \
  -3.53344, 46.922 front fs empty border lc rgb '#549f' lw 0.1
set object 2288 polygon from \
  -3.52632, 46.9438 to \
  -0.03, 46.9438 to \
  -0.03, 24.0283 to \
  -3.52632, 24.0283 to \
  -3.52632, 46.9438 front fs empty border lc rgb '#549f' lw 0.1
set object 2289 polygon from \
  -3.51809, 46.9657 to \
  -0.03, 46.9657 to \
  -0.03, 24.0401 to \
  -3.51809, 24.0401 to \
  -3.51809, 46.9657 front fs empty border lc rgb '#549f' lw 0.1
set object 2290 polygon from \
  -3.50875, 46.9876 to \
  -0.03, 46.9876 to \
  -0.03, 24.052 to \
  -3.50875, 24.052 to \
  -3.50875, 46.9876 front fs empty border lc rgb '#549f' lw 0.1
set object 2291 polygon from \
  -3.49831, 47.0094 to \
  -0.03, 47.0094 to \
  -0.03, 24.0638 to \
  -3.49831, 24.0638 to \
  -3.49831, 47.0094 front fs empty border lc rgb '#549f' lw 0.1
set object 2292 polygon from \
  -3.48679, 47.0313 to \
  -0.03, 47.0313 to \
  -0.03, 24.0757 to \
  -3.48679, 24.0757 to \
  -3.48679, 47.0313 front fs empty border lc rgb '#549f' lw 0.1
set object 2293 polygon from \
  -3.47418, 47.0532 to \
  -0.03, 47.0532 to \
  -0.03, 24.0876 to \
  -3.47418, 24.0876 to \
  -3.47418, 47.0532 front fs empty border lc rgb '#549f' lw 0.1
set object 2294 polygon from \
  -3.46049, 47.075 to \
  -0.03, 47.075 to \
  -0.03, 24.0994 to \
  -3.46049, 24.0994 to \
  -3.46049, 47.075 front fs empty border lc rgb '#549f' lw 0.1
set object 2295 polygon from \
  -3.44573, 47.0969 to \
  -0.03, 47.0969 to \
  -0.03, 24.1113 to \
  -3.44573, 24.1113 to \
  -3.44573, 47.0969 front fs empty border lc rgb '#549f' lw 0.1
set object 2296 polygon from \
  -3.42992, 47.1188 to \
  -0.03, 47.1188 to \
  -0.03, 24.1232 to \
  -3.42992, 24.1232 to \
  -3.42992, 47.1188 front fs empty border lc rgb '#549f' lw 0.1
set object 2297 polygon from \
  -3.41305, 47.1406 to \
  -0.03, 47.1406 to \
  -0.03, 24.135 to \
  -3.41305, 24.135 to \
  -3.41305, 47.1406 front fs empty border lc rgb '#549f' lw 0.1
set object 2298 polygon from \
  -3.39515, 47.1625 to \
  -0.03, 47.1625 to \
  -0.03, 24.1469 to \
  -3.39515, 24.1469 to \
  -3.39515, 47.1625 front fs empty border lc rgb '#549f' lw 0.1
set object 2299 polygon from \
  -3.37621, 47.1844 to \
  -0.03, 47.1844 to \
  -0.03, 24.1588 to \
  -3.37621, 24.1588 to \
  -3.37621, 47.1844 front fs empty border lc rgb '#549f' lw 0.1
set object 2300 polygon from \
  -3.35626, 47.2063 to \
  -0.03, 47.2063 to \
  -0.03, 24.1706 to \
  -3.35626, 24.1706 to \
  -3.35626, 47.2063 front fs empty border lc rgb '#549f' lw 0.1
set object 2301 polygon from \
  -3.3353, 47.2281 to \
  -0.03, 47.2281 to \
  -0.03, 24.1825 to \
  -3.3353, 24.1825 to \
  -3.3353, 47.2281 front fs empty border lc rgb '#549f' lw 0.1
set object 2302 polygon from \
  -3.31334, 47.25 to \
  -0.03, 47.25 to \
  -0.03, 24.1944 to \
  -3.31334, 24.1944 to \
  -3.31334, 47.25 front fs empty border lc rgb '#549f' lw 0.1
set object 2303 polygon from \
  -3.2904, 47.2719 to \
  -0.03, 47.2719 to \
  -0.03, 24.2062 to \
  -3.2904, 24.2062 to \
  -3.2904, 47.2719 front fs empty border lc rgb '#549f' lw 0.1
set object 2304 polygon from \
  -3.26649, 47.2938 to \
  -0.03, 47.2938 to \
  -0.03, 24.2181 to \
  -3.26649, 24.2181 to \
  -3.26649, 47.2938 front fs empty border lc rgb '#549f' lw 0.1
set object 2305 polygon from \
  -3.24161, 47.3156 to \
  -0.03, 47.3156 to \
  -0.03, 24.23 to \
  -3.24161, 24.23 to \
  -3.24161, 47.3156 front fs empty border lc rgb '#549f' lw 0.1
set object 2306 polygon from \
  -3.21579, 47.3375 to \
  -0.03, 47.3375 to \
  -0.03, 24.2419 to \
  -3.21579, 24.2419 to \
  -3.21579, 47.3375 front fs empty border lc rgb '#549f' lw 0.1
set object 2307 polygon from \
  -3.18904, 47.3594 to \
  -0.03, 47.3594 to \
  -0.03, 24.2538 to \
  -3.18904, 24.2538 to \
  -3.18904, 47.3594 front fs empty border lc rgb '#549f' lw 0.1
set object 2308 polygon from \
  -3.16137, 47.3813 to \
  -0.03, 47.3813 to \
  -0.03, 24.2656 to \
  -3.16137, 24.2656 to \
  -3.16137, 47.3813 front fs empty border lc rgb '#549f' lw 0.1
set object 2309 polygon from \
  -3.1328, 47.4032 to \
  -0.03, 47.4032 to \
  -0.03, 24.2775 to \
  -3.1328, 24.2775 to \
  -3.1328, 47.4032 front fs empty border lc rgb '#549f' lw 0.1
set object 2310 polygon from \
  -3.10333, 47.4251 to \
  -0.03, 47.4251 to \
  -0.03, 24.2894 to \
  -3.10333, 24.2894 to \
  -3.10333, 47.4251 front fs empty border lc rgb '#549f' lw 0.1
set object 2311 polygon from \
  -3.073, 47.447 to \
  -0.03, 47.447 to \
  -0.03, 24.3013 to \
  -3.073, 24.3013 to \
  -3.073, 47.447 front fs empty border lc rgb '#549f' lw 0.1
set object 2312 polygon from \
  -3.0418, 47.4688 to \
  -0.03, 47.4688 to \
  -0.03, 24.3132 to \
  -3.0418, 24.3132 to \
  -3.0418, 47.4688 front fs empty border lc rgb '#549f' lw 0.1
set object 2313 polygon from \
  -3.00976, 47.4907 to \
  -0.03, 47.4907 to \
  -0.03, 24.3251 to \
  -3.00976, 24.3251 to \
  -3.00976, 47.4907 front fs empty border lc rgb '#549f' lw 0.1
set object 2314 polygon from \
  -2.97689, 47.5126 to \
  -0.03, 47.5126 to \
  -0.03, 24.3369 to \
  -2.97689, 24.3369 to \
  -2.97689, 47.5126 front fs empty border lc rgb '#549f' lw 0.1
set object 2315 polygon from \
  -2.94321, 47.5345 to \
  -0.03, 47.5345 to \
  -0.03, 24.3488 to \
  -2.94321, 24.3488 to \
  -2.94321, 47.5345 front fs empty border lc rgb '#549f' lw 0.1
set object 2316 polygon from \
  -2.90874, 47.5564 to \
  -0.03, 47.5564 to \
  -0.03, 24.3607 to \
  -2.90874, 24.3607 to \
  -2.90874, 47.5564 front fs empty border lc rgb '#549f' lw 0.1
set object 2317 polygon from \
  -2.87349, 47.5783 to \
  -0.03, 47.5783 to \
  -0.03, 24.3726 to \
  -2.87349, 24.3726 to \
  -2.87349, 47.5783 front fs empty border lc rgb '#549f' lw 0.1
set object 2318 polygon from \
  -2.83748, 47.6002 to \
  -0.03, 47.6002 to \
  -0.03, 24.3845 to \
  -2.83748, 24.3845 to \
  -2.83748, 47.6002 front fs empty border lc rgb '#549f' lw 0.1
set object 2319 polygon from \
  -2.80073, 47.6221 to \
  -0.03, 47.6221 to \
  -0.03, 24.3964 to \
  -2.80073, 24.3964 to \
  -2.80073, 47.6221 front fs empty border lc rgb '#549f' lw 0.1
set object 2320 polygon from \
  -2.76325, 47.644 to \
  -0.03, 47.644 to \
  -0.03, 24.4083 to \
  -2.76325, 24.4083 to \
  -2.76325, 47.644 front fs empty border lc rgb '#549f' lw 0.1
set object 2321 polygon from \
  -2.72507, 47.6659 to \
  -0.03, 47.6659 to \
  -0.03, 24.4202 to \
  -2.72507, 24.4202 to \
  -2.72507, 47.6659 front fs empty border lc rgb '#549f' lw 0.1
set object 2322 polygon from \
  -2.6862, 47.6878 to \
  -0.03, 47.6878 to \
  -0.03, 24.4321 to \
  -2.6862, 24.4321 to \
  -2.6862, 47.6878 front fs empty border lc rgb '#549f' lw 0.1
set object 2323 polygon from \
  -2.64665, 47.7097 to \
  -0.03, 47.7097 to \
  -0.03, 24.444 to \
  -2.64665, 24.444 to \
  -2.64665, 47.7097 front fs empty border lc rgb '#549f' lw 0.1
set object 2324 polygon from \
  -2.60646, 47.7316 to \
  -0.03, 47.7316 to \
  -0.03, 24.4559 to \
  -2.60646, 24.4559 to \
  -2.60646, 47.7316 front fs empty border lc rgb '#549f' lw 0.1
set object 2325 polygon from \
  -2.56564, 47.7535 to \
  -0.03, 47.7535 to \
  -0.03, 24.4678 to \
  -2.56564, 24.4678 to \
  -2.56564, 47.7535 front fs empty border lc rgb '#549f' lw 0.1
set object 2326 polygon from \
  -2.5242, 47.7754 to \
  -0.03, 47.7754 to \
  -0.03, 24.4797 to \
  -2.5242, 24.4797 to \
  -2.5242, 47.7754 front fs empty border lc rgb '#549f' lw 0.1
set object 2327 polygon from \
  -2.48217, 47.7973 to \
  -0.03, 47.7973 to \
  -0.03, 24.4916 to \
  -2.48217, 24.4916 to \
  -2.48217, 47.7973 front fs empty border lc rgb '#549f' lw 0.1
set object 2328 polygon from \
  -2.43957, 47.8192 to \
  -0.03, 47.8192 to \
  -0.03, 24.5035 to \
  -2.43957, 24.5035 to \
  -2.43957, 47.8192 front fs empty border lc rgb '#549f' lw 0.1
set object 2329 polygon from \
  -2.39642, 47.8412 to \
  -0.03, 47.8412 to \
  -0.03, 24.5154 to \
  -2.39642, 24.5154 to \
  -2.39642, 47.8412 front fs empty border lc rgb '#549f' lw 0.1
set object 2330 polygon from \
  -2.35273, 47.8631 to \
  -0.03, 47.8631 to \
  -0.03, 24.5273 to \
  -2.35273, 24.5273 to \
  -2.35273, 47.8631 front fs empty border lc rgb '#549f' lw 0.1
set object 2331 polygon from \
  -2.30852, 47.885 to \
  -0.03, 47.885 to \
  -0.03, 24.5392 to \
  -2.30852, 24.5392 to \
  -2.30852, 47.885 front fs empty border lc rgb '#549f' lw 0.1
set object 2332 polygon from \
  -2.26382, 47.9069 to \
  -0.03, 47.9069 to \
  -0.03, 24.5511 to \
  -2.26382, 24.5511 to \
  -2.26382, 47.9069 front fs empty border lc rgb '#549f' lw 0.1
set object 2333 polygon from \
  -2.21865, 47.9288 to \
  -0.03, 47.9288 to \
  -0.03, 24.5631 to \
  -2.21865, 24.5631 to \
  -2.21865, 47.9288 front fs empty border lc rgb '#549f' lw 0.1
set object 2334 polygon from \
  -2.17303, 47.9507 to \
  -0.03, 47.9507 to \
  -0.03, 24.575 to \
  -2.17303, 24.575 to \
  -2.17303, 47.9507 front fs empty border lc rgb '#549f' lw 0.1
set object 2335 polygon from \
  -2.12697, 47.9726 to \
  -0.03, 47.9726 to \
  -0.03, 24.5869 to \
  -2.12697, 24.5869 to \
  -2.12697, 47.9726 front fs empty border lc rgb '#549f' lw 0.1
set object 2336 polygon from \
  -2.10792, 47.9946 to \
  -0.03, 47.9946 to \
  -0.03, 24.5988 to \
  -2.10792, 24.5988 to \
  -2.10792, 47.9946 front fs empty border lc rgb '#549f' lw 0.1
set object 2337 polygon from \
  -2.11061, 48.0165 to \
  -0.03, 48.0165 to \
  -0.03, 24.6107 to \
  -2.11061, 24.6107 to \
  -2.11061, 48.0165 front fs empty border lc rgb '#549f' lw 0.1
set object 2338 polygon from \
  -2.11275, 48.0384 to \
  -0.03, 48.0384 to \
  -0.03, 24.6226 to \
  -2.11275, 24.6226 to \
  -2.11275, 48.0384 front fs empty border lc rgb '#549f' lw 0.1
set object 2339 polygon from \
  -2.11432, 48.0603 to \
  -0.03, 48.0603 to \
  -0.03, 24.6346 to \
  -2.11432, 24.6346 to \
  -2.11432, 48.0603 front fs empty border lc rgb '#549f' lw 0.1
set object 2340 polygon from \
  -2.11532, 48.0823 to \
  -0.03, 48.0823 to \
  -0.03, 24.6465 to \
  -2.11532, 24.6465 to \
  -2.11532, 48.0823 front fs empty border lc rgb '#549f' lw 0.1
set object 2341 polygon from \
  -2.11572, 48.1042 to \
  -0.03, 48.1042 to \
  -0.03, 24.6584 to \
  -2.11572, 24.6584 to \
  -2.11572, 48.1042 front fs empty border lc rgb '#549f' lw 0.1
set object 2342 polygon from \
  -2.11573, 48.1261 to \
  -0.03, 48.1261 to \
  -0.03, 24.6703 to \
  -2.11573, 24.6703 to \
  -2.11573, 48.1261 front fs empty border lc rgb '#549f' lw 0.1
set object 2343 polygon from \
  -2.11553, 48.148 to \
  -0.03, 48.148 to \
  -0.03, 24.6822 to \
  -2.11553, 24.6822 to \
  -2.11553, 48.148 front fs empty border lc rgb '#549f' lw 0.1
set object 2344 polygon from \
  -2.11472, 48.17 to \
  -0.03, 48.17 to \
  -0.03, 24.6942 to \
  -2.11472, 24.6942 to \
  -2.11472, 48.17 front fs empty border lc rgb '#549f' lw 0.1
set object 2345 polygon from \
  -2.1133, 48.1919 to \
  -0.03, 48.1919 to \
  -0.03, 24.7061 to \
  -2.1133, 24.7061 to \
  -2.1133, 48.1919 front fs empty border lc rgb '#549f' lw 0.1
set object 2346 polygon from \
  -2.11124, 48.2138 to \
  -0.03, 48.2138 to \
  -0.03, 24.718 to \
  -2.11124, 24.718 to \
  -2.11124, 48.2138 front fs empty border lc rgb '#549f' lw 0.1
set object 2347 polygon from \
  -2.10854, 48.2358 to \
  -0.03, 48.2358 to \
  -0.03, 24.73 to \
  -2.10854, 24.73 to \
  -2.10854, 48.2358 front fs empty border lc rgb '#549f' lw 0.1
set object 2348 polygon from \
  -2.10519, 48.2577 to \
  -0.03, 48.2577 to \
  -0.03, 24.7419 to \
  -2.10519, 24.7419 to \
  -2.10519, 48.2577 front fs empty border lc rgb '#549f' lw 0.1
set object 2349 polygon from \
  -2.10118, 48.2796 to \
  -0.03, 48.2796 to \
  -0.03, 24.7538 to \
  -2.10118, 24.7538 to \
  -2.10118, 48.2796 front fs empty border lc rgb '#549f' lw 0.1
set object 2350 polygon from \
  -2.09651, 48.3016 to \
  -0.03, 48.3016 to \
  -0.03, 24.7658 to \
  -2.09651, 24.7658 to \
  -2.09651, 48.3016 front fs empty border lc rgb '#549f' lw 0.1
set object 2351 polygon from \
  -2.09115, 48.3235 to \
  -0.03, 48.3235 to \
  -0.03, 24.7777 to \
  -2.09115, 24.7777 to \
  -2.09115, 48.3235 front fs empty border lc rgb '#549f' lw 0.1
set object 2352 polygon from \
  -2.08512, 48.3454 to \
  -0.03, 48.3454 to \
  -0.03, 24.7896 to \
  -2.08512, 24.7896 to \
  -2.08512, 48.3454 front fs empty border lc rgb '#549f' lw 0.1
set object 2353 polygon from \
  -2.07838, 48.3674 to \
  -0.03, 48.3674 to \
  -0.03, 24.8016 to \
  -2.07838, 24.8016 to \
  -2.07838, 48.3674 front fs empty border lc rgb '#549f' lw 0.1
set object 2354 polygon from \
  -2.07095, 48.3893 to \
  -0.03, 48.3893 to \
  -0.03, 24.8135 to \
  -2.07095, 24.8135 to \
  -2.07095, 48.3893 front fs empty border lc rgb '#549f' lw 0.1
set object 2355 polygon from \
  -2.06281, 48.4113 to \
  -0.03, 48.4113 to \
  -0.03, 24.8254 to \
  -2.06281, 24.8254 to \
  -2.06281, 48.4113 front fs empty border lc rgb '#549f' lw 0.1
set object 2356 polygon from \
  -2.05396, 48.4332 to \
  -0.03, 48.4332 to \
  -0.03, 24.8374 to \
  -2.05396, 24.8374 to \
  -2.05396, 48.4332 front fs empty border lc rgb '#549f' lw 0.1
set object 2357 polygon from \
  -2.04438, 48.4552 to \
  -0.03, 48.4552 to \
  -0.03, 24.8493 to \
  -2.04438, 24.8493 to \
  -2.04438, 48.4552 front fs empty border lc rgb '#549f' lw 0.1
set object 2358 polygon from \
  -2.03408, 48.4771 to \
  -0.03, 48.4771 to \
  -0.03, 24.8613 to \
  -2.03408, 24.8613 to \
  -2.03408, 48.4771 front fs empty border lc rgb '#549f' lw 0.1
set object 2359 polygon from \
  -2.02305, 48.4991 to \
  -0.03, 48.4991 to \
  -0.03, 24.8732 to \
  -2.02305, 24.8732 to \
  -2.02305, 48.4991 front fs empty border lc rgb '#549f' lw 0.1
set object 2360 polygon from \
  -2.01128, 48.521 to \
  -0.03, 48.521 to \
  -0.03, 24.8852 to \
  -2.01128, 24.8852 to \
  -2.01128, 48.521 front fs empty border lc rgb '#549f' lw 0.1
set object 2361 polygon from \
  -2.03536, 48.543 to \
  -0.03, 48.543 to \
  -0.03, 24.8971 to \
  -2.03536, 24.8971 to \
  -2.03536, 48.543 front fs empty border lc rgb '#549f' lw 0.1
set object 2362 polygon from \
  -2.07338, 48.5649 to \
  -0.03, 48.5649 to \
  -0.03, 24.909 to \
  -2.07338, 24.909 to \
  -2.07338, 48.5649 front fs empty border lc rgb '#549f' lw 0.1
set object 2363 polygon from \
  -2.11034, 48.5869 to \
  -0.03, 48.5869 to \
  -0.03, 24.921 to \
  -2.11034, 24.921 to \
  -2.11034, 48.5869 front fs empty border lc rgb '#549f' lw 0.1
set object 2364 polygon from \
  -2.14621, 48.6088 to \
  -0.03, 48.6088 to \
  -0.03, 24.9329 to \
  -2.14621, 24.9329 to \
  -2.14621, 48.6088 front fs empty border lc rgb '#549f' lw 0.1
set object 2365 polygon from \
  -2.18096, 48.6308 to \
  -0.03, 48.6308 to \
  -0.03, 24.9449 to \
  -2.18096, 24.9449 to \
  -2.18096, 48.6308 front fs empty border lc rgb '#549f' lw 0.1
set object 2366 polygon from \
  -2.21459, 48.6527 to \
  -0.03, 48.6527 to \
  -0.03, 24.9569 to \
  -2.21459, 24.9569 to \
  -2.21459, 48.6527 front fs empty border lc rgb '#549f' lw 0.1
set object 2367 polygon from \
  -2.24707, 48.6747 to \
  -0.03, 48.6747 to \
  -0.03, 24.9688 to \
  -2.24707, 24.9688 to \
  -2.24707, 48.6747 front fs empty border lc rgb '#549f' lw 0.1
set object 2368 polygon from \
  -2.27838, 48.6966 to \
  -0.03, 48.6966 to \
  -0.03, 24.9808 to \
  -2.27838, 24.9808 to \
  -2.27838, 48.6966 front fs empty border lc rgb '#549f' lw 0.1
set object 2369 polygon from \
  -2.3085, 48.7186 to \
  -0.03, 48.7186 to \
  -0.03, 24.9927 to \
  -2.3085, 24.9927 to \
  -2.3085, 48.7186 front fs empty border lc rgb '#549f' lw 0.1
set object 2370 polygon from \
  -2.33743, 48.7406 to \
  -0.03, 48.7406 to \
  -0.03, 25.0047 to \
  -2.33743, 25.0047 to \
  -2.33743, 48.7406 front fs empty border lc rgb '#549f' lw 0.1
set object 2371 polygon from \
  -2.36514, 48.7625 to \
  -0.03, 48.7625 to \
  -0.03, 25.0166 to \
  -2.36514, 25.0166 to \
  -2.36514, 48.7625 front fs empty border lc rgb '#549f' lw 0.1
set object 2372 polygon from \
  -2.39162, 48.7845 to \
  -0.03, 48.7845 to \
  -0.03, 25.0286 to \
  -2.39162, 25.0286 to \
  -2.39162, 48.7845 front fs empty border lc rgb '#549f' lw 0.1
set object 2373 polygon from \
  -2.41685, 48.8065 to \
  -0.03, 48.8065 to \
  -0.03, 25.0406 to \
  -2.41685, 25.0406 to \
  -2.41685, 48.8065 front fs empty border lc rgb '#549f' lw 0.1
set object 2374 polygon from \
  -2.44083, 48.8284 to \
  -0.03, 48.8284 to \
  -0.03, 25.0525 to \
  -2.44083, 25.0525 to \
  -2.44083, 48.8284 front fs empty border lc rgb '#549f' lw 0.1
set object 2375 polygon from \
  -2.46353, 48.8504 to \
  -0.03, 48.8504 to \
  -0.03, 25.0645 to \
  -2.46353, 25.0645 to \
  -2.46353, 48.8504 front fs empty border lc rgb '#549f' lw 0.1
set object 2376 polygon from \
  -2.48496, 48.8724 to \
  -0.03, 48.8724 to \
  -0.03, 25.0765 to \
  -2.48496, 25.0765 to \
  -2.48496, 48.8724 front fs empty border lc rgb '#549f' lw 0.1
set object 2377 polygon from \
  -2.50509, 48.8943 to \
  -0.03, 48.8943 to \
  -0.03, 25.0884 to \
  -2.50509, 25.0884 to \
  -2.50509, 48.8943 front fs empty border lc rgb '#549f' lw 0.1
set object 2378 polygon from \
  -2.52392, 48.9163 to \
  -0.03, 48.9163 to \
  -0.03, 25.1004 to \
  -2.52392, 25.1004 to \
  -2.52392, 48.9163 front fs empty border lc rgb '#549f' lw 0.1
set object 2379 polygon from \
  -2.54144, 48.9383 to \
  -0.03, 48.9383 to \
  -0.03, 25.1124 to \
  -2.54144, 25.1124 to \
  -2.54144, 48.9383 front fs empty border lc rgb '#549f' lw 0.1
set object 2380 polygon from \
  -2.55763, 48.9603 to \
  -0.03, 48.9603 to \
  -0.03, 25.1243 to \
  -2.55763, 25.1243 to \
  -2.55763, 48.9603 front fs empty border lc rgb '#549f' lw 0.1
set object 2381 polygon from \
  -2.57251, 48.9822 to \
  -0.03, 48.9822 to \
  -0.03, 25.1363 to \
  -2.57251, 25.1363 to \
  -2.57251, 48.9822 front fs empty border lc rgb '#549f' lw 0.1
set object 2382 polygon from \
  -2.58604, 49.0042 to \
  -0.03, 49.0042 to \
  -0.03, 25.1483 to \
  -2.58604, 25.1483 to \
  -2.58604, 49.0042 front fs empty border lc rgb '#549f' lw 0.1
set object 2383 polygon from \
  -2.59825, 49.0262 to \
  -0.03, 49.0262 to \
  -0.03, 25.1602 to \
  -2.59825, 25.1602 to \
  -2.59825, 49.0262 front fs empty border lc rgb '#549f' lw 0.1
set object 2384 polygon from \
  -2.6091, 49.0482 to \
  -0.03, 49.0482 to \
  -0.03, 25.1722 to \
  -2.6091, 25.1722 to \
  -2.6091, 49.0482 front fs empty border lc rgb '#549f' lw 0.1
set object 2385 polygon from \
  -2.61861, 49.0701 to \
  -0.03, 49.0701 to \
  -0.03, 25.1842 to \
  -2.61861, 25.1842 to \
  -2.61861, 49.0701 front fs empty border lc rgb '#549f' lw 0.1
set object 2386 polygon from \
  -2.62678, 49.0921 to \
  -0.03, 49.0921 to \
  -0.03, 25.1962 to \
  -2.62678, 25.1962 to \
  -2.62678, 49.0921 front fs empty border lc rgb '#549f' lw 0.1
set object 2387 polygon from \
  -2.63359, 49.1141 to \
  -0.03, 49.1141 to \
  -0.03, 25.2082 to \
  -2.63359, 25.2082 to \
  -2.63359, 49.1141 front fs empty border lc rgb '#549f' lw 0.1
set object 2388 polygon from \
  -2.63905, 49.1361 to \
  -0.03, 49.1361 to \
  -0.03, 25.2201 to \
  -2.63905, 25.2201 to \
  -2.63905, 49.1361 front fs empty border lc rgb '#549f' lw 0.1
set object 2389 polygon from \
  -2.64315, 49.1581 to \
  -0.03, 49.1581 to \
  -0.03, 25.2321 to \
  -2.64315, 25.2321 to \
  -2.64315, 49.1581 front fs empty border lc rgb '#549f' lw 0.1
set object 2390 polygon from \
  -2.64591, 49.1801 to \
  -0.03, 49.1801 to \
  -0.03, 25.2441 to \
  -2.64591, 25.2441 to \
  -2.64591, 49.1801 front fs empty border lc rgb '#549f' lw 0.1
set object 2391 polygon from \
  -2.64731, 49.2021 to \
  -0.03, 49.2021 to \
  -0.03, 25.2561 to \
  -2.64731, 25.2561 to \
  -2.64731, 49.2021 front fs empty border lc rgb '#549f' lw 0.1
set object 2392 polygon from \
  -2.64737, 49.224 to \
  -0.03, 49.224 to \
  -0.03, 25.2681 to \
  -2.64737, 25.2681 to \
  -2.64737, 49.224 front fs empty border lc rgb '#549f' lw 0.1
set object 2393 polygon from \
  -2.64737, 49.246 to \
  -0.03, 49.246 to \
  -0.03, 25.2801 to \
  -2.64737, 25.2801 to \
  -2.64737, 49.246 front fs empty border lc rgb '#549f' lw 0.1
set object 2394 polygon from \
  -2.64608, 49.268 to \
  -0.03, 49.268 to \
  -0.03, 25.292 to \
  -2.64608, 25.292 to \
  -2.64608, 49.268 front fs empty border lc rgb '#549f' lw 0.1
set object 2395 polygon from \
  -2.64345, 49.29 to \
  -0.03, 49.29 to \
  -0.03, 25.304 to \
  -2.64345, 25.304 to \
  -2.64345, 49.29 front fs empty border lc rgb '#549f' lw 0.1
set object 2396 polygon from \
  -2.63949, 49.312 to \
  -0.03, 49.312 to \
  -0.03, 25.316 to \
  -2.63949, 25.316 to \
  -2.63949, 49.312 front fs empty border lc rgb '#549f' lw 0.1
set object 2397 polygon from \
  -2.6342, 49.334 to \
  -0.03, 49.334 to \
  -0.03, 25.328 to \
  -2.6342, 25.328 to \
  -2.6342, 49.334 front fs empty border lc rgb '#549f' lw 0.1
set object 2398 polygon from \
  -2.62759, 49.356 to \
  -0.03, 49.356 to \
  -0.03, 25.34 to \
  -2.62759, 25.34 to \
  -2.62759, 49.356 front fs empty border lc rgb '#549f' lw 0.1
set object 2399 polygon from \
  -2.61967, 49.378 to \
  -0.03, 49.378 to \
  -0.03, 25.352 to \
  -2.61967, 25.352 to \
  -2.61967, 49.378 front fs empty border lc rgb '#549f' lw 0.1
set object 2400 polygon from \
  -2.61044, 49.4 to \
  -0.03, 49.4 to \
  -0.03, 25.364 to \
  -2.61044, 25.364 to \
  -2.61044, 49.4 front fs empty border lc rgb '#549f' lw 0.1
set object 2401 polygon from \
  -2.59992, 49.422 to \
  -0.03, 49.422 to \
  -0.03, 25.376 to \
  -2.59992, 25.376 to \
  -2.59992, 49.422 front fs empty border lc rgb '#549f' lw 0.1
set object 2402 polygon from \
  -2.58811, 49.444 to \
  -0.03, 49.444 to \
  -0.03, 25.388 to \
  -2.58811, 25.388 to \
  -2.58811, 49.444 front fs empty border lc rgb '#549f' lw 0.1
set object 2403 polygon from \
  -2.57502, 49.466 to \
  -0.03, 49.466 to \
  -0.03, 25.4 to \
  -2.57502, 25.4 to \
  -2.57502, 49.466 front fs empty border lc rgb '#549f' lw 0.1
set object 2404 polygon from \
  -2.56067, 49.488 to \
  -0.03, 49.488 to \
  -0.03, 25.412 to \
  -2.56067, 25.412 to \
  -2.56067, 49.488 front fs empty border lc rgb '#549f' lw 0.1
set object 2405 polygon from \
  -2.54508, 49.51 to \
  -0.03, 49.51 to \
  -0.03, 25.424 to \
  -2.54508, 25.424 to \
  -2.54508, 49.51 front fs empty border lc rgb '#549f' lw 0.1
set object 2406 polygon from \
  -2.5653, 49.532 to \
  -0.03, 49.532 to \
  -0.03, 25.436 to \
  -2.5653, 25.436 to \
  -2.5653, 49.532 front fs empty border lc rgb '#549f' lw 0.1
set object 2407 polygon from \
  -2.58772, 49.554 to \
  -0.03, 49.554 to \
  -0.03, 25.448 to \
  -2.58772, 25.448 to \
  -2.58772, 49.554 front fs empty border lc rgb '#549f' lw 0.1
set object 2408 polygon from \
  -2.60926, 49.576 to \
  -0.03, 49.576 to \
  -0.03, 25.46 to \
  -2.60926, 25.46 to \
  -2.60926, 49.576 front fs empty border lc rgb '#549f' lw 0.1
set object 2409 polygon from \
  -2.6299, 49.5981 to \
  -0.03, 49.5981 to \
  -0.03, 25.472 to \
  -2.6299, 25.472 to \
  -2.6299, 49.5981 front fs empty border lc rgb '#549f' lw 0.1
set object 2410 polygon from \
  -2.64964, 49.6201 to \
  -0.03, 49.6201 to \
  -0.03, 25.484 to \
  -2.64964, 25.484 to \
  -2.64964, 49.6201 front fs empty border lc rgb '#549f' lw 0.1
set object 2411 polygon from \
  -2.6685, 49.6421 to \
  -0.03, 49.6421 to \
  -0.03, 25.496 to \
  -2.6685, 25.496 to \
  -2.6685, 49.6421 front fs empty border lc rgb '#549f' lw 0.1
set object 2412 polygon from \
  -2.68646, 49.6641 to \
  -0.03, 49.6641 to \
  -0.03, 25.508 to \
  -2.68646, 25.508 to \
  -2.68646, 49.6641 front fs empty border lc rgb '#549f' lw 0.1
set object 2413 polygon from \
  -2.70353, 49.6861 to \
  -0.03, 49.6861 to \
  -0.03, 25.5201 to \
  -2.70353, 25.5201 to \
  -2.70353, 49.6861 front fs empty border lc rgb '#549f' lw 0.1
set object 2414 polygon from \
  -2.71971, 49.7081 to \
  -0.03, 49.7081 to \
  -0.03, 25.5321 to \
  -2.71971, 25.5321 to \
  -2.71971, 49.7081 front fs empty border lc rgb '#549f' lw 0.1
set object 2415 polygon from \
  -2.735, 49.7301 to \
  -0.03, 49.7301 to \
  -0.03, 25.5441 to \
  -2.735, 25.5441 to \
  -2.735, 49.7301 front fs empty border lc rgb '#549f' lw 0.1
set object 2416 polygon from \
  -2.74941, 49.7522 to \
  -0.03, 49.7522 to \
  -0.03, 25.5561 to \
  -2.74941, 25.5561 to \
  -2.74941, 49.7522 front fs empty border lc rgb '#549f' lw 0.1
set object 2417 polygon from \
  -2.76293, 49.7742 to \
  -0.03, 49.7742 to \
  -0.03, 25.5681 to \
  -2.76293, 25.5681 to \
  -2.76293, 49.7742 front fs empty border lc rgb '#549f' lw 0.1
set object 2418 polygon from \
  -2.77557, 49.7962 to \
  -0.03, 49.7962 to \
  -0.03, 25.5801 to \
  -2.77557, 25.5801 to \
  -2.77557, 49.7962 front fs empty border lc rgb '#549f' lw 0.1
set object 2419 polygon from \
  -2.78734, 49.8182 to \
  -0.03, 49.8182 to \
  -0.03, 25.5922 to \
  -2.78734, 25.5922 to \
  -2.78734, 49.8182 front fs empty border lc rgb '#549f' lw 0.1
set object 2420 polygon from \
  -2.79824, 49.8403 to \
  -0.03, 49.8403 to \
  -0.03, 25.6042 to \
  -2.79824, 25.6042 to \
  -2.79824, 49.8403 front fs empty border lc rgb '#549f' lw 0.1
set object 2421 polygon from \
  -2.80826, 49.8623 to \
  -0.03, 49.8623 to \
  -0.03, 25.6162 to \
  -2.80826, 25.6162 to \
  -2.80826, 49.8623 front fs empty border lc rgb '#549f' lw 0.1
set object 2422 polygon from \
  -2.81743, 49.8843 to \
  -0.03, 49.8843 to \
  -0.03, 25.6282 to \
  -2.81743, 25.6282 to \
  -2.81743, 49.8843 front fs empty border lc rgb '#549f' lw 0.1
set object 2423 polygon from \
  -2.82573, 49.9063 to \
  -0.03, 49.9063 to \
  -0.03, 25.6402 to \
  -2.82573, 25.6402 to \
  -2.82573, 49.9063 front fs empty border lc rgb '#549f' lw 0.1
set object 2424 polygon from \
  -2.83318, 49.9284 to \
  -0.03, 49.9284 to \
  -0.03, 25.6523 to \
  -2.83318, 25.6523 to \
  -2.83318, 49.9284 front fs empty border lc rgb '#549f' lw 0.1
set object 2425 polygon from \
  -2.83978, 49.9504 to \
  -0.03, 49.9504 to \
  -0.03, 25.6643 to \
  -2.83978, 25.6643 to \
  -2.83978, 49.9504 front fs empty border lc rgb '#549f' lw 0.1
set object 2426 polygon from \
  -2.84555, 49.9724 to \
  -0.03, 49.9724 to \
  -0.03, 25.6763 to \
  -2.84555, 25.6763 to \
  -2.84555, 49.9724 front fs empty border lc rgb '#549f' lw 0.1
set object 2427 polygon from \
  -2.85047, 49.9945 to \
  -0.03, 49.9945 to \
  -0.03, 25.6884 to \
  -2.85047, 25.6884 to \
  -2.85047, 49.9945 front fs empty border lc rgb '#549f' lw 0.1
set object 2428 polygon from \
  -2.85458, 50.0165 to \
  -0.03, 50.0165 to \
  -0.03, 25.7004 to \
  -2.85458, 25.7004 to \
  -2.85458, 50.0165 front fs empty border lc rgb '#549f' lw 0.1
set object 2429 polygon from \
  -2.85786, 50.0385 to \
  -0.03, 50.0385 to \
  -0.03, 25.7124 to \
  -2.85786, 25.7124 to \
  -2.85786, 50.0385 front fs empty border lc rgb '#549f' lw 0.1
set object 2430 polygon from \
  -2.86032, 50.0606 to \
  -0.03, 50.0606 to \
  -0.03, 25.7245 to \
  -2.86032, 25.7245 to \
  -2.86032, 50.0606 front fs empty border lc rgb '#549f' lw 0.1
set object 2431 polygon from \
  -2.86199, 50.0826 to \
  -0.03, 50.0826 to \
  -0.03, 25.7365 to \
  -2.86199, 25.7365 to \
  -2.86199, 50.0826 front fs empty border lc rgb '#549f' lw 0.1
set object 2432 polygon from \
  -2.86285, 50.1046 to \
  -0.03, 50.1046 to \
  -0.03, 25.7485 to \
  -2.86285, 25.7485 to \
  -2.86285, 50.1046 front fs empty border lc rgb '#549f' lw 0.1
set object 2433 polygon from \
  -2.86293, 50.1267 to \
  -0.03, 50.1267 to \
  -0.03, 25.7606 to \
  -2.86293, 25.7606 to \
  -2.86293, 50.1267 front fs empty border lc rgb '#549f' lw 0.1
set object 2434 polygon from \
  -2.86293, 50.1487 to \
  -0.03, 50.1487 to \
  -0.03, 25.7726 to \
  -2.86293, 25.7726 to \
  -2.86293, 50.1487 front fs empty border lc rgb '#549f' lw 0.1
set object 2435 polygon from \
  -2.86223, 50.1708 to \
  -0.03, 50.1708 to \
  -0.03, 25.7846 to \
  -2.86223, 25.7846 to \
  -2.86223, 50.1708 front fs empty border lc rgb '#549f' lw 0.1
set object 2436 polygon from \
  -2.86076, 50.1928 to \
  -0.03, 50.1928 to \
  -0.03, 25.7967 to \
  -2.86076, 25.7967 to \
  -2.86076, 50.1928 front fs empty border lc rgb '#549f' lw 0.1
set object 2437 polygon from \
  -2.85853, 50.2149 to \
  -0.03, 50.2149 to \
  -0.03, 25.8087 to \
  -2.85853, 25.8087 to \
  -2.85853, 50.2149 front fs empty border lc rgb '#549f' lw 0.1
set object 2438 polygon from \
  -2.85555, 50.2369 to \
  -0.03, 50.2369 to \
  -0.03, 25.8208 to \
  -2.85555, 25.8208 to \
  -2.85555, 50.2369 front fs empty border lc rgb '#549f' lw 0.1
set object 2439 polygon from \
  -2.85183, 50.259 to \
  -0.03, 50.259 to \
  -0.03, 25.8328 to \
  -2.85183, 25.8328 to \
  -2.85183, 50.259 front fs empty border lc rgb '#549f' lw 0.1
set object 2440 polygon from \
  -2.84738, 50.281 to \
  -0.03, 50.281 to \
  -0.03, 25.8449 to \
  -2.84738, 25.8449 to \
  -2.84738, 50.281 front fs empty border lc rgb '#549f' lw 0.1
set object 2441 polygon from \
  -2.8422, 50.3031 to \
  -0.03, 50.3031 to \
  -0.03, 25.8569 to \
  -2.8422, 25.8569 to \
  -2.8422, 50.3031 front fs empty border lc rgb '#549f' lw 0.1
set object 2442 polygon from \
  -2.83632, 50.3251 to \
  -0.03, 50.3251 to \
  -0.03, 25.8689 to \
  -2.83632, 25.8689 to \
  -2.83632, 50.3251 front fs empty border lc rgb '#549f' lw 0.1
set object 2443 polygon from \
  -2.82975, 50.3472 to \
  -0.03, 50.3472 to \
  -0.03, 25.881 to \
  -2.82975, 25.881 to \
  -2.82975, 50.3472 front fs empty border lc rgb '#549f' lw 0.1
set object 2444 polygon from \
  -2.82248, 50.3692 to \
  -0.03, 50.3692 to \
  -0.03, 25.893 to \
  -2.82248, 25.893 to \
  -2.82248, 50.3692 front fs empty border lc rgb '#549f' lw 0.1
set object 2445 polygon from \
  -2.81454, 50.3913 to \
  -0.03, 50.3913 to \
  -0.03, 25.9051 to \
  -2.81454, 25.9051 to \
  -2.81454, 50.3913 front fs empty border lc rgb '#549f' lw 0.1
set object 2446 polygon from \
  -2.80594, 50.4133 to \
  -0.03, 50.4133 to \
  -0.03, 25.9172 to \
  -2.80594, 25.9172 to \
  -2.80594, 50.4133 front fs empty border lc rgb '#549f' lw 0.1
set object 2447 polygon from \
  -2.79669, 50.4354 to \
  -0.03, 50.4354 to \
  -0.03, 25.9292 to \
  -2.79669, 25.9292 to \
  -2.79669, 50.4354 front fs empty border lc rgb '#549f' lw 0.1
set object 2448 polygon from \
  -2.78679, 50.4574 to \
  -0.03, 50.4574 to \
  -0.03, 25.9413 to \
  -2.78679, 25.9413 to \
  -2.78679, 50.4574 front fs empty border lc rgb '#549f' lw 0.1
set object 2449 polygon from \
  -2.77627, 50.4795 to \
  -0.03, 50.4795 to \
  -0.03, 25.9533 to \
  -2.77627, 25.9533 to \
  -2.77627, 50.4795 front fs empty border lc rgb '#549f' lw 0.1
set object 2450 polygon from \
  -2.76514, 50.5016 to \
  -0.03, 50.5016 to \
  -0.03, 25.9654 to \
  -2.76514, 25.9654 to \
  -2.76514, 50.5016 front fs empty border lc rgb '#549f' lw 0.1
set object 2451 polygon from \
  -2.7534, 50.5236 to \
  -0.03, 50.5236 to \
  -0.03, 25.9774 to \
  -2.7534, 25.9774 to \
  -2.7534, 50.5236 front fs empty border lc rgb '#549f' lw 0.1
set object 2452 polygon from \
  -2.74107, 50.5457 to \
  -0.03, 50.5457 to \
  -0.03, 25.9895 to \
  -2.74107, 25.9895 to \
  -2.74107, 50.5457 front fs empty border lc rgb '#549f' lw 0.1
set object 2453 polygon from \
  -2.72817, 50.5678 to \
  -0.03, 50.5678 to \
  -0.03, 26.0016 to \
  -2.72817, 26.0016 to \
  -2.72817, 50.5678 front fs empty border lc rgb '#549f' lw 0.1
set object 2454 polygon from \
  -2.7147, 50.5898 to \
  -0.03, 50.5898 to \
  -0.03, 26.0136 to \
  -2.7147, 26.0136 to \
  -2.7147, 50.5898 front fs empty border lc rgb '#549f' lw 0.1
set object 2455 polygon from \
  -2.70068, 50.6119 to \
  -0.03, 50.6119 to \
  -0.03, 26.0257 to \
  -2.70068, 26.0257 to \
  -2.70068, 50.6119 front fs empty border lc rgb '#549f' lw 0.1
set object 2456 polygon from \
  -2.68613, 50.634 to \
  -0.03, 50.634 to \
  -0.03, 26.0378 to \
  -2.68613, 26.0378 to \
  -2.68613, 50.634 front fs empty border lc rgb '#549f' lw 0.1
set object 2457 polygon from \
  -2.67105, 50.656 to \
  -0.03, 50.656 to \
  -0.03, 26.0498 to \
  -2.67105, 26.0498 to \
  -2.67105, 50.656 front fs empty border lc rgb '#549f' lw 0.1
set object 2458 polygon from \
  -2.65546, 50.6781 to \
  -0.03, 50.6781 to \
  -0.03, 26.0619 to \
  -2.65546, 26.0619 to \
  -2.65546, 50.6781 front fs empty border lc rgb '#549f' lw 0.1
set object 2459 polygon from \
  -2.66714, 50.7002 to \
  -0.03, 50.7002 to \
  -0.03, 26.074 to \
  -2.66714, 26.074 to \
  -2.66714, 50.7002 front fs empty border lc rgb '#549f' lw 0.1
set object 2460 polygon from \
  -2.68908, 50.7223 to \
  -0.03, 50.7223 to \
  -0.03, 26.086 to \
  -2.68908, 26.086 to \
  -2.68908, 50.7223 front fs empty border lc rgb '#549f' lw 0.1
set object 2461 polygon from \
  -2.71023, 50.7443 to \
  -0.03, 50.7443 to \
  -0.03, 26.0981 to \
  -2.71023, 26.0981 to \
  -2.71023, 50.7443 front fs empty border lc rgb '#549f' lw 0.1
set object 2462 polygon from \
  -2.73057, 50.7664 to \
  -0.03, 50.7664 to \
  -0.03, 26.1102 to \
  -2.73057, 26.1102 to \
  -2.73057, 50.7664 front fs empty border lc rgb '#549f' lw 0.1
set object 2463 polygon from \
  -2.7501, 50.7885 to \
  -0.03, 50.7885 to \
  -0.03, 26.1222 to \
  -2.7501, 26.1222 to \
  -2.7501, 50.7885 front fs empty border lc rgb '#549f' lw 0.1
set object 2464 polygon from \
  -2.76879, 50.8106 to \
  -0.03, 50.8106 to \
  -0.03, 26.1343 to \
  -2.76879, 26.1343 to \
  -2.76879, 50.8106 front fs empty border lc rgb '#549f' lw 0.1
set object 2465 polygon from \
  -2.78664, 50.8326 to \
  -0.03, 50.8326 to \
  -0.03, 26.1464 to \
  -2.78664, 26.1464 to \
  -2.78664, 50.8326 front fs empty border lc rgb '#549f' lw 0.1
set object 2466 polygon from \
  -2.80362, 50.8547 to \
  -0.03, 50.8547 to \
  -0.03, 26.1585 to \
  -2.80362, 26.1585 to \
  -2.80362, 50.8547 front fs empty border lc rgb '#549f' lw 0.1
set object 2467 polygon from \
  -2.81973, 50.8768 to \
  -0.03, 50.8768 to \
  -0.03, 26.1706 to \
  -2.81973, 26.1706 to \
  -2.81973, 50.8768 front fs empty border lc rgb '#549f' lw 0.1
set object 2468 polygon from \
  -2.83494, 50.8989 to \
  -0.03, 50.8989 to \
  -0.03, 26.1826 to \
  -2.83494, 26.1826 to \
  -2.83494, 50.8989 front fs empty border lc rgb '#549f' lw 0.1
set object 2469 polygon from \
  -2.84926, 50.921 to \
  -0.03, 50.921 to \
  -0.03, 26.1947 to \
  -2.84926, 26.1947 to \
  -2.84926, 50.921 front fs empty border lc rgb '#549f' lw 0.1
set object 2470 polygon from \
  -2.86267, 50.9431 to \
  -0.03, 50.9431 to \
  -0.03, 26.2068 to \
  -2.86267, 26.2068 to \
  -2.86267, 50.9431 front fs empty border lc rgb '#549f' lw 0.1
set object 2471 polygon from \
  -2.87515, 50.9652 to \
  -0.03, 50.9652 to \
  -0.03, 26.2189 to \
  -2.87515, 26.2189 to \
  -2.87515, 50.9652 front fs empty border lc rgb '#549f' lw 0.1
set object 2472 polygon from \
  -2.8898, 50.9872 to \
  -0.03, 50.9872 to \
  -0.03, 26.231 to \
  -2.8898, 26.231 to \
  -2.8898, 50.9872 front fs empty border lc rgb '#549f' lw 0.1
set object 2473 polygon from \
  -2.90694, 51.0093 to \
  -0.03, 51.0093 to \
  -0.03, 26.2431 to \
  -2.90694, 26.2431 to \
  -2.90694, 51.0093 front fs empty border lc rgb '#549f' lw 0.1
set object 2474 polygon from \
  -2.92308, 51.0314 to \
  -0.03, 51.0314 to \
  -0.03, 26.2551 to \
  -2.92308, 26.2551 to \
  -2.92308, 51.0314 front fs empty border lc rgb '#549f' lw 0.1
set object 2475 polygon from \
  -2.93821, 51.0535 to \
  -0.03, 51.0535 to \
  -0.03, 26.2672 to \
  -2.93821, 26.2672 to \
  -2.93821, 51.0535 front fs empty border lc rgb '#549f' lw 0.1
set object 2476 polygon from \
  -2.95232, 51.0756 to \
  -0.03, 51.0756 to \
  -0.03, 26.2793 to \
  -2.95232, 26.2793 to \
  -2.95232, 51.0756 front fs empty border lc rgb '#549f' lw 0.1
set object 2477 polygon from \
  -2.96539, 51.0977 to \
  -0.03, 51.0977 to \
  -0.03, 26.2914 to \
  -2.96539, 26.2914 to \
  -2.96539, 51.0977 front fs empty border lc rgb '#549f' lw 0.1
set object 2478 polygon from \
  -2.97742, 51.1198 to \
  -0.03, 51.1198 to \
  -0.03, 26.3035 to \
  -2.97742, 26.3035 to \
  -2.97742, 51.1198 front fs empty border lc rgb '#549f' lw 0.1
set object 2479 polygon from \
  -2.9884, 51.1419 to \
  -0.03, 51.1419 to \
  -0.03, 26.3156 to \
  -2.9884, 26.3156 to \
  -2.9884, 51.1419 front fs empty border lc rgb '#549f' lw 0.1
set object 2480 polygon from \
  -2.99832, 51.164 to \
  -0.03, 51.164 to \
  -0.03, 26.3277 to \
  -2.99832, 26.3277 to \
  -2.99832, 51.164 front fs empty border lc rgb '#549f' lw 0.1
set object 2481 polygon from \
  -3.00717, 51.1861 to \
  -0.03, 51.1861 to \
  -0.03, 26.3398 to \
  -3.00717, 26.3398 to \
  -3.00717, 51.1861 front fs empty border lc rgb '#549f' lw 0.1
set object 2482 polygon from \
  -3.01495, 51.2082 to \
  -0.03, 51.2082 to \
  -0.03, 26.3519 to \
  -3.01495, 26.3519 to \
  -3.01495, 51.2082 front fs empty border lc rgb '#549f' lw 0.1
set object 2483 polygon from \
  -3.02804, 51.2303 to \
  -0.03, 51.2303 to \
  -0.03, 26.364 to \
  -3.02804, 26.364 to \
  -3.02804, 51.2303 front fs empty border lc rgb '#549f' lw 0.1
set object 2484 polygon from \
  -3.04581, 51.2524 to \
  -0.03, 51.2524 to \
  -0.03, 26.3761 to \
  -3.04581, 26.3761 to \
  -3.04581, 51.2524 front fs empty border lc rgb '#549f' lw 0.1
set object 2485 polygon from \
  -3.06253, 51.2745 to \
  -0.03, 51.2745 to \
  -0.03, 26.3882 to \
  -3.06253, 26.3882 to \
  -3.06253, 51.2745 front fs empty border lc rgb '#549f' lw 0.1
set object 2486 polygon from \
  -3.07818, 51.2966 to \
  -0.03, 51.2966 to \
  -0.03, 26.4003 to \
  -3.07818, 26.4003 to \
  -3.07818, 51.2966 front fs empty border lc rgb '#549f' lw 0.1
set object 2487 polygon from \
  -3.09276, 51.3187 to \
  -0.03, 51.3187 to \
  -0.03, 26.4124 to \
  -3.09276, 26.4124 to \
  -3.09276, 51.3187 front fs empty border lc rgb '#549f' lw 0.1
set object 2488 polygon from \
  -3.10625, 51.3408 to \
  -0.03, 51.3408 to \
  -0.03, 26.4245 to \
  -3.10625, 26.4245 to \
  -3.10625, 51.3408 front fs empty border lc rgb '#549f' lw 0.1
set object 2489 polygon from \
  -3.11866, 51.363 to \
  -0.03, 51.363 to \
  -0.03, 26.4366 to \
  -3.11866, 26.4366 to \
  -3.11866, 51.363 front fs empty border lc rgb '#549f' lw 0.1
set object 2490 polygon from \
  -3.12998, 51.3851 to \
  -0.03, 51.3851 to \
  -0.03, 26.4487 to \
  -3.12998, 26.4487 to \
  -3.12998, 51.3851 front fs empty border lc rgb '#549f' lw 0.1
set object 2491 polygon from \
  -3.14019, 51.4072 to \
  -0.03, 51.4072 to \
  -0.03, 26.4608 to \
  -3.14019, 26.4608 to \
  -3.14019, 51.4072 front fs empty border lc rgb '#549f' lw 0.1
set object 2492 polygon from \
  -3.14929, 51.4293 to \
  -0.03, 51.4293 to \
  -0.03, 26.4729 to \
  -3.14929, 26.4729 to \
  -3.14929, 51.4293 front fs empty border lc rgb '#549f' lw 0.1
set object 2493 polygon from \
  -3.15728, 51.4514 to \
  -0.03, 51.4514 to \
  -0.03, 26.4851 to \
  -3.15728, 26.4851 to \
  -3.15728, 51.4514 front fs empty border lc rgb '#549f' lw 0.1
set object 2494 polygon from \
  -3.16415, 51.4735 to \
  -0.03, 51.4735 to \
  -0.03, 26.4972 to \
  -3.16415, 26.4972 to \
  -3.16415, 51.4735 front fs empty border lc rgb '#549f' lw 0.1
set object 2495 polygon from \
  -3.1699, 51.4956 to \
  -0.03, 51.4956 to \
  -0.03, 26.5093 to \
  -3.1699, 26.5093 to \
  -3.1699, 51.4956 front fs empty border lc rgb '#549f' lw 0.1
set object 2496 polygon from \
  -3.17453, 51.5178 to \
  -0.03, 51.5178 to \
  -0.03, 26.5214 to \
  -3.17453, 26.5214 to \
  -3.17453, 51.5178 front fs empty border lc rgb '#549f' lw 0.1
set object 2497 polygon from \
  -3.17802, 51.5399 to \
  -0.03, 51.5399 to \
  -0.03, 26.5335 to \
  -3.17802, 26.5335 to \
  -3.17802, 51.5399 front fs empty border lc rgb '#549f' lw 0.1
set object 2498 polygon from \
  -3.18039, 51.562 to \
  -0.03, 51.562 to \
  -0.03, 26.5456 to \
  -3.18039, 26.5456 to \
  -3.18039, 51.562 front fs empty border lc rgb '#549f' lw 0.1
set object 2499 polygon from \
  -3.18162, 51.5841 to \
  -0.03, 51.5841 to \
  -0.03, 26.5578 to \
  -3.18162, 26.5578 to \
  -3.18162, 51.5841 front fs empty border lc rgb '#549f' lw 0.1
set object 2500 polygon from \
  -3.18171, 51.6063 to \
  -0.03, 51.6063 to \
  -0.03, 26.5699 to \
  -3.18171, 26.5699 to \
  -3.18171, 51.6063 front fs empty border lc rgb '#549f' lw 0.1
set object 2501 polygon from \
  -3.18171, 51.6284 to \
  -0.03, 51.6284 to \
  -0.03, 26.582 to \
  -3.18171, 26.582 to \
  -3.18171, 51.6284 front fs empty border lc rgb '#549f' lw 0.1
set object 2502 polygon from \
  -3.18067, 51.6505 to \
  -0.03, 51.6505 to \
  -0.03, 26.5941 to \
  -3.18067, 26.5941 to \
  -3.18067, 51.6505 front fs empty border lc rgb '#549f' lw 0.1
set object 2503 polygon from \
  -3.1785, 51.6726 to \
  -0.03, 51.6726 to \
  -0.03, 26.6062 to \
  -3.1785, 26.6062 to \
  -3.1785, 51.6726 front fs empty border lc rgb '#549f' lw 0.1
set object 2504 polygon from \
  -3.17519, 51.6948 to \
  -0.03, 51.6948 to \
  -0.03, 26.6184 to \
  -3.17519, 26.6184 to \
  -3.17519, 51.6948 front fs empty border lc rgb '#549f' lw 0.1
set object 2505 polygon from \
  -3.17074, 51.7169 to \
  -0.03, 51.7169 to \
  -0.03, 26.6305 to \
  -3.17074, 26.6305 to \
  -3.17074, 51.7169 front fs empty border lc rgb '#549f' lw 0.1
set object 2506 polygon from \
  -3.16516, 51.739 to \
  -0.03, 51.739 to \
  -0.03, 26.6426 to \
  -3.16516, 26.6426 to \
  -3.16516, 51.739 front fs empty border lc rgb '#549f' lw 0.1
set object 2507 polygon from \
  -3.15845, 51.7612 to \
  -0.03, 51.7612 to \
  -0.03, 26.6548 to \
  -3.15845, 26.6548 to \
  -3.15845, 51.7612 front fs empty border lc rgb '#549f' lw 0.1
set object 2508 polygon from \
  -3.15062, 51.7833 to \
  -0.03, 51.7833 to \
  -0.03, 26.6669 to \
  -3.15062, 26.6669 to \
  -3.15062, 51.7833 front fs empty border lc rgb '#549f' lw 0.1
set object 2509 polygon from \
  -3.14166, 51.8054 to \
  -0.03, 51.8054 to \
  -0.03, 26.679 to \
  -3.14166, 26.679 to \
  -3.14166, 51.8054 front fs empty border lc rgb '#549f' lw 0.1
set object 2510 polygon from \
  -3.13157, 51.8276 to \
  -0.03, 51.8276 to \
  -0.03, 26.6912 to \
  -3.13157, 26.6912 to \
  -3.13157, 51.8276 front fs empty border lc rgb '#549f' lw 0.1
set object 2511 polygon from \
  -3.12037, 51.8497 to \
  -0.03, 51.8497 to \
  -0.03, 26.7033 to \
  -3.12037, 26.7033 to \
  -3.12037, 51.8497 front fs empty border lc rgb '#549f' lw 0.1
set object 2512 polygon from \
  -3.10806, 51.8718 to \
  -0.03, 51.8718 to \
  -0.03, 26.7154 to \
  -3.10806, 26.7154 to \
  -3.10806, 51.8718 front fs empty border lc rgb '#549f' lw 0.1
set object 2513 polygon from \
  -3.09465, 51.894 to \
  -0.03, 51.894 to \
  -0.03, 26.7276 to \
  -3.09465, 26.7276 to \
  -3.09465, 51.894 front fs empty border lc rgb '#549f' lw 0.1
set object 2514 polygon from \
  -3.08013, 51.9161 to \
  -0.03, 51.9161 to \
  -0.03, 26.7397 to \
  -3.08013, 26.7397 to \
  -3.08013, 51.9161 front fs empty border lc rgb '#549f' lw 0.1
set object 2515 polygon from \
  -3.06452, 51.9383 to \
  -0.03, 51.9383 to \
  -0.03, 26.7518 to \
  -3.06452, 26.7518 to \
  -3.06452, 51.9383 front fs empty border lc rgb '#549f' lw 0.1
set object 2516 polygon from \
  -3.04782, 51.9604 to \
  -0.03, 51.9604 to \
  -0.03, 26.764 to \
  -3.04782, 26.764 to \
  -3.04782, 51.9604 front fs empty border lc rgb '#549f' lw 0.1
set object 2517 polygon from \
  -3.03005, 51.9826 to \
  -0.03, 51.9826 to \
  -0.03, 26.7761 to \
  -3.03005, 26.7761 to \
  -3.03005, 51.9826 front fs empty border lc rgb '#549f' lw 0.1
set object 2518 polygon from \
  -3.0112, 52.0047 to \
  -0.03, 52.0047 to \
  -0.03, 26.7883 to \
  -3.0112, 26.7883 to \
  -3.0112, 52.0047 front fs empty border lc rgb '#549f' lw 0.1
set object 2519 polygon from \
  -2.99129, 52.0269 to \
  -0.03, 52.0269 to \
  -0.03, 26.8004 to \
  -2.99129, 26.8004 to \
  -2.99129, 52.0269 front fs empty border lc rgb '#549f' lw 0.1
set object 2520 polygon from \
  -2.97034, 52.049 to \
  -0.03, 52.049 to \
  -0.03, 26.8126 to \
  -2.97034, 26.8126 to \
  -2.97034, 52.049 front fs empty border lc rgb '#549f' lw 0.1
set object 2521 polygon from \
  -2.94833, 52.0712 to \
  -0.03, 52.0712 to \
  -0.03, 26.8247 to \
  -2.94833, 26.8247 to \
  -2.94833, 52.0712 front fs empty border lc rgb '#549f' lw 0.1
set object 2522 polygon from \
  -2.9253, 52.0933 to \
  -0.03, 52.0933 to \
  -0.03, 26.8368 to \
  -2.9253, 26.8368 to \
  -2.9253, 52.0933 front fs empty border lc rgb '#549f' lw 0.1
set object 2523 polygon from \
  -2.90125, 52.1155 to \
  -0.03, 52.1155 to \
  -0.03, 26.849 to \
  -2.90125, 26.849 to \
  -2.90125, 52.1155 front fs empty border lc rgb '#549f' lw 0.1
set object 2524 polygon from \
  -2.87649, 52.1376 to \
  -0.03, 52.1376 to \
  -0.03, 26.8611 to \
  -2.87649, 26.8611 to \
  -2.87649, 52.1376 front fs empty border lc rgb '#549f' lw 0.1
set object 2525 polygon from \
  -2.85291, 52.1598 to \
  -0.03, 52.1598 to \
  -0.03, 26.8733 to \
  -2.85291, 26.8733 to \
  -2.85291, 52.1598 front fs empty border lc rgb '#549f' lw 0.1
set object 2526 polygon from \
  -2.82829, 52.1819 to \
  -0.03, 52.1819 to \
  -0.03, 26.8855 to \
  -2.82829, 26.8855 to \
  -2.82829, 52.1819 front fs empty border lc rgb '#549f' lw 0.1
set object 2527 polygon from \
  -2.80266, 52.2041 to \
  -0.03, 52.2041 to \
  -0.03, 26.8976 to \
  -2.80266, 26.8976 to \
  -2.80266, 52.2041 front fs empty border lc rgb '#549f' lw 0.1
set object 2528 polygon from \
  -2.77602, 52.2262 to \
  -0.03, 52.2262 to \
  -0.03, 26.9098 to \
  -2.77602, 26.9098 to \
  -2.77602, 52.2262 front fs empty border lc rgb '#549f' lw 0.1
set object 2529 polygon from \
  -2.74838, 52.2484 to \
  -0.03, 52.2484 to \
  -0.03, 26.9219 to \
  -2.74838, 26.9219 to \
  -2.74838, 52.2484 front fs empty border lc rgb '#549f' lw 0.1
set object 2530 polygon from \
  -2.71976, 52.2706 to \
  -0.03, 52.2706 to \
  -0.03, 26.9341 to \
  -2.71976, 26.9341 to \
  -2.71976, 52.2706 front fs empty border lc rgb '#549f' lw 0.1
set object 2531 polygon from \
  -2.69017, 52.2927 to \
  -0.03, 52.2927 to \
  -0.03, 26.9462 to \
  -2.69017, 26.9462 to \
  -2.69017, 52.2927 front fs empty border lc rgb '#549f' lw 0.1
set object 2532 polygon from \
  -2.65962, 52.3149 to \
  -0.03, 52.3149 to \
  -0.03, 26.9584 to \
  -2.65962, 26.9584 to \
  -2.65962, 52.3149 front fs empty border lc rgb '#549f' lw 0.1
set object 2533 polygon from \
  -2.62812, 52.3371 to \
  -0.03, 52.3371 to \
  -0.03, 26.9706 to \
  -2.62812, 26.9706 to \
  -2.62812, 52.3371 front fs empty border lc rgb '#549f' lw 0.1
set object 2534 polygon from \
  -2.5957, 52.3592 to \
  -0.03, 52.3592 to \
  -0.03, 26.9827 to \
  -2.5957, 26.9827 to \
  -2.5957, 52.3592 front fs empty border lc rgb '#549f' lw 0.1
set object 2535 polygon from \
  -2.56236, 52.3814 to \
  -0.03, 52.3814 to \
  -0.03, 26.9949 to \
  -2.56236, 26.9949 to \
  -2.56236, 52.3814 front fs empty border lc rgb '#549f' lw 0.1
set object 2536 polygon from \
  -2.52812, 52.4036 to \
  -0.03, 52.4036 to \
  -0.03, 27.0071 to \
  -2.52812, 27.0071 to \
  -2.52812, 52.4036 front fs empty border lc rgb '#549f' lw 0.1
set object 2537 polygon from \
  -2.49299, 52.4257 to \
  -0.03, 52.4257 to \
  -0.03, 27.0192 to \
  -2.49299, 27.0192 to \
  -2.49299, 52.4257 front fs empty border lc rgb '#549f' lw 0.1
set object 2538 polygon from \
  -2.45699, 52.4479 to \
  -0.03, 52.4479 to \
  -0.03, 27.0314 to \
  -2.45699, 27.0314 to \
  -2.45699, 52.4479 front fs empty border lc rgb '#549f' lw 0.1
set object 2539 polygon from \
  -2.42014, 52.4701 to \
  -0.03, 52.4701 to \
  -0.03, 27.0436 to \
  -2.42014, 27.0436 to \
  -2.42014, 52.4701 front fs empty border lc rgb '#549f' lw 0.1
set object 2540 polygon from \
  -2.38245, 52.4923 to \
  -0.03, 52.4923 to \
  -0.03, 27.0557 to \
  -2.38245, 27.0557 to \
  -2.38245, 52.4923 front fs empty border lc rgb '#549f' lw 0.1
set object 2541 polygon from \
  -2.34394, 52.5144 to \
  -0.03, 52.5144 to \
  -0.03, 27.0679 to \
  -2.34394, 27.0679 to \
  -2.34394, 52.5144 front fs empty border lc rgb '#549f' lw 0.1
set object 2542 polygon from \
  -2.30464, 52.5366 to \
  -0.03, 52.5366 to \
  -0.03, 27.0801 to \
  -2.30464, 27.0801 to \
  -2.30464, 52.5366 front fs empty border lc rgb '#549f' lw 0.1
set object 2543 polygon from \
  -2.26454, 52.5588 to \
  -0.03, 52.5588 to \
  -0.03, 27.0922 to \
  -2.26454, 27.0922 to \
  -2.26454, 52.5588 front fs empty border lc rgb '#549f' lw 0.1
set object 2544 polygon from \
  -2.22368, 52.581 to \
  -0.03, 52.581 to \
  -0.03, 27.1044 to \
  -2.22368, 27.1044 to \
  -2.22368, 52.581 front fs empty border lc rgb '#549f' lw 0.1
set object 2545 polygon from \
  -2.18207, 52.6031 to \
  -0.03, 52.6031 to \
  -0.03, 27.1166 to \
  -2.18207, 27.1166 to \
  -2.18207, 52.6031 front fs empty border lc rgb '#549f' lw 0.1
set object 2546 polygon from \
  -2.13974, 52.6253 to \
  -0.03, 52.6253 to \
  -0.03, 27.1288 to \
  -2.13974, 27.1288 to \
  -2.13974, 52.6253 front fs empty border lc rgb '#549f' lw 0.1
set object 2547 polygon from \
  -2.09669, 52.6475 to \
  -0.03, 52.6475 to \
  -0.03, 27.141 to \
  -2.09669, 27.141 to \
  -2.09669, 52.6475 front fs empty border lc rgb '#549f' lw 0.1
set object 2548 polygon from \
  -2.05296, 52.6697 to \
  -0.03, 52.6697 to \
  -0.03, 27.1531 to \
  -2.05296, 27.1531 to \
  -2.05296, 52.6697 front fs empty border lc rgb '#549f' lw 0.1
set object 2549 polygon from \
  -2.00856, 52.6919 to \
  -0.03, 52.6919 to \
  -0.03, 27.1653 to \
  -2.00856, 27.1653 to \
  -2.00856, 52.6919 front fs empty border lc rgb '#549f' lw 0.1
set object 2550 polygon from \
  -1.9635, 52.7141 to \
  -0.03, 52.7141 to \
  -0.03, 27.1775 to \
  -1.9635, 27.1775 to \
  -1.9635, 52.7141 front fs empty border lc rgb '#549f' lw 0.1
set object 2551 polygon from \
  -1.91782, 52.7363 to \
  -0.03, 52.7363 to \
  -0.03, 27.1897 to \
  -1.91782, 27.1897 to \
  -1.91782, 52.7363 front fs empty border lc rgb '#549f' lw 0.1
set object 2552 polygon from \
  -1.87153, 52.7584 to \
  -0.03, 52.7584 to \
  -0.03, 27.2019 to \
  -1.87153, 27.2019 to \
  -1.87153, 52.7584 front fs empty border lc rgb '#549f' lw 0.1
set object 2553 polygon from \
  -1.82466, 52.7806 to \
  -0.03, 52.7806 to \
  -0.03, 27.2141 to \
  -1.82466, 27.2141 to \
  -1.82466, 52.7806 front fs empty border lc rgb '#549f' lw 0.1
set object 2554 polygon from \
  -1.77722, 52.8028 to \
  -0.03, 52.8028 to \
  -0.03, 27.2262 to \
  -1.77722, 27.2262 to \
  -1.77722, 52.8028 front fs empty border lc rgb '#549f' lw 0.1
set object 2555 polygon from \
  -1.72924, 52.825 to \
  -0.03, 52.825 to \
  -0.03, 27.2384 to \
  -1.72924, 27.2384 to \
  -1.72924, 52.825 front fs empty border lc rgb '#549f' lw 0.1
set object 2556 polygon from \
  -1.68073, 52.8472 to \
  -0.03, 52.8472 to \
  -0.03, 27.2506 to \
  -1.68073, 27.2506 to \
  -1.68073, 52.8472 front fs empty border lc rgb '#549f' lw 0.1
set object 2557 polygon from \
  -1.63173, 52.8694 to \
  -0.03, 52.8694 to \
  -0.03, 27.2628 to \
  -1.63173, 27.2628 to \
  -1.63173, 52.8694 front fs empty border lc rgb '#549f' lw 0.1
set object 2558 polygon from \
  -1.58225, 52.8916 to \
  -0.03, 52.8916 to \
  -0.03, 27.275 to \
  -1.58225, 27.275 to \
  -1.58225, 52.8916 front fs empty border lc rgb '#549f' lw 0.1
set object 2559 polygon from \
  -1.55434, 52.9138 to \
  -0.03, 52.9138 to \
  -0.03, 27.2872 to \
  -1.55434, 27.2872 to \
  -1.55434, 52.9138 front fs empty border lc rgb '#549f' lw 0.1
set object 2560 polygon from \
  -1.54069, 52.936 to \
  -0.03, 52.936 to \
  -0.03, 27.2994 to \
  -1.54069, 27.2994 to \
  -1.54069, 52.936 front fs empty border lc rgb '#549f' lw 0.1
set object 2561 polygon from \
  -1.52671, 52.9582 to \
  -0.03, 52.9582 to \
  -0.03, 27.3116 to \
  -1.52671, 27.3116 to \
  -1.52671, 52.9582 front fs empty border lc rgb '#549f' lw 0.1
set object 2562 polygon from \
  -1.51239, 52.9804 to \
  -0.03, 52.9804 to \
  -0.03, 27.3238 to \
  -1.51239, 27.3238 to \
  -1.51239, 52.9804 front fs empty border lc rgb '#549f' lw 0.1
set object 2563 polygon from \
  -1.49773, 53.0026 to \
  -0.03, 53.0026 to \
  -0.03, 27.336 to \
  -1.49773, 27.336 to \
  -1.49773, 53.0026 front fs empty border lc rgb '#549f' lw 0.1
set object 2564 polygon from \
  -1.48271, 53.0248 to \
  -0.03, 53.0248 to \
  -0.03, 27.3482 to \
  -1.48271, 27.3482 to \
  -1.48271, 53.0248 front fs empty border lc rgb '#549f' lw 0.1
set object 2565 polygon from \
  -1.46734, 53.047 to \
  -0.03, 53.047 to \
  -0.03, 27.3604 to \
  -1.46734, 27.3604 to \
  -1.46734, 53.047 front fs empty border lc rgb '#549f' lw 0.1
set object 2566 polygon from \
  -1.4516, 53.0692 to \
  -0.03, 53.0692 to \
  -0.03, 27.3726 to \
  -1.4516, 27.3726 to \
  -1.4516, 53.0692 front fs empty border lc rgb '#549f' lw 0.1
set object 2567 polygon from \
  -1.43549, 53.0914 to \
  -0.03, 53.0914 to \
  -0.03, 27.3848 to \
  -1.43549, 27.3848 to \
  -1.43549, 53.0914 front fs empty border lc rgb '#549f' lw 0.1
set object 2568 polygon from \
  -1.41901, 53.1136 to \
  -0.03, 53.1136 to \
  -0.03, 27.397 to \
  -1.41901, 27.397 to \
  -1.41901, 53.1136 front fs empty border lc rgb '#549f' lw 0.1
set object 2569 polygon from \
  -1.40214, 53.1359 to \
  -0.03, 53.1359 to \
  -0.03, 27.4092 to \
  -1.40214, 27.4092 to \
  -1.40214, 53.1359 front fs empty border lc rgb '#549f' lw 0.1
set object 2570 polygon from \
  -1.38488, 53.1581 to \
  -0.03, 53.1581 to \
  -0.03, 27.4214 to \
  -1.38488, 27.4214 to \
  -1.38488, 53.1581 front fs empty border lc rgb '#549f' lw 0.1
set object 2571 polygon from \
  -1.37414, 53.1803 to \
  -0.03, 53.1803 to \
  -0.03, 27.4336 to \
  -1.37414, 27.4336 to \
  -1.37414, 53.1803 front fs empty border lc rgb '#549f' lw 0.1
set object 2572 polygon from \
  -1.40806, 53.2025 to \
  -0.03, 53.2025 to \
  -0.03, 27.4458 to \
  -1.40806, 27.4458 to \
  -1.40806, 53.2025 front fs empty border lc rgb '#549f' lw 0.1
set object 2573 polygon from \
  -1.44147, 53.2247 to \
  -0.03, 53.2247 to \
  -0.03, 27.4581 to \
  -1.44147, 27.4581 to \
  -1.44147, 53.2247 front fs empty border lc rgb '#549f' lw 0.1
set object 2574 polygon from \
  -1.47435, 53.2469 to \
  -0.03, 53.2469 to \
  -0.03, 27.4703 to \
  -1.47435, 27.4703 to \
  -1.47435, 53.2469 front fs empty border lc rgb '#549f' lw 0.1
set object 2575 polygon from \
  -1.50665, 53.2691 to \
  -0.03, 53.2691 to \
  -0.03, 27.4825 to \
  -1.50665, 27.4825 to \
  -1.50665, 53.2691 front fs empty border lc rgb '#549f' lw 0.1
set object 2576 polygon from \
  -1.53837, 53.2914 to \
  -0.03, 53.2914 to \
  -0.03, 27.4947 to \
  -1.53837, 27.4947 to \
  -1.53837, 53.2914 front fs empty border lc rgb '#549f' lw 0.1
set object 2577 polygon from \
  -1.56946, 53.3136 to \
  -0.03, 53.3136 to \
  -0.03, 27.5069 to \
  -1.56946, 27.5069 to \
  -1.56946, 53.3136 front fs empty border lc rgb '#549f' lw 0.1
set object 2578 polygon from \
  -1.5999, 53.3358 to \
  -0.03, 53.3358 to \
  -0.03, 27.5191 to \
  -1.5999, 27.5191 to \
  -1.5999, 53.3358 front fs empty border lc rgb '#549f' lw 0.1
set object 2579 polygon from \
  -1.62966, 53.358 to \
  -0.03, 53.358 to \
  -0.03, 27.5314 to \
  -1.62966, 27.5314 to \
  -1.62966, 53.358 front fs empty border lc rgb '#549f' lw 0.1
set object 2580 polygon from \
  -1.65872, 53.3803 to \
  -0.03, 53.3803 to \
  -0.03, 27.5436 to \
  -1.65872, 27.5436 to \
  -1.65872, 53.3803 front fs empty border lc rgb '#549f' lw 0.1
set object 2581 polygon from \
  -1.68705, 53.4025 to \
  -0.03, 53.4025 to \
  -0.03, 27.5558 to \
  -1.68705, 27.5558 to \
  -1.68705, 53.4025 front fs empty border lc rgb '#549f' lw 0.1
set object 2582 polygon from \
  -1.71463, 53.4247 to \
  -0.03, 53.4247 to \
  -0.03, 27.568 to \
  -1.71463, 27.568 to \
  -1.71463, 53.4247 front fs empty border lc rgb '#549f' lw 0.1
set object 2583 polygon from \
  -1.74143, 53.4469 to \
  -0.03, 53.4469 to \
  -0.03, 27.5802 to \
  -1.74143, 27.5802 to \
  -1.74143, 53.4469 front fs empty border lc rgb '#549f' lw 0.1
set object 2584 polygon from \
  -1.76743, 53.4692 to \
  -0.03, 53.4692 to \
  -0.03, 27.5925 to \
  -1.76743, 27.5925 to \
  -1.76743, 53.4692 front fs empty border lc rgb '#549f' lw 0.1
set object 2585 polygon from \
  -1.7926, 53.4914 to \
  -0.03, 53.4914 to \
  -0.03, 27.6047 to \
  -1.7926, 27.6047 to \
  -1.7926, 53.4914 front fs empty border lc rgb '#549f' lw 0.1
set object 2586 polygon from \
  -1.81693, 53.5136 to \
  -0.03, 53.5136 to \
  -0.03, 27.6169 to \
  -1.81693, 27.6169 to \
  -1.81693, 53.5136 front fs empty border lc rgb '#549f' lw 0.1
set object 2587 polygon from \
  -1.84038, 53.5359 to \
  -0.03, 53.5359 to \
  -0.03, 27.6292 to \
  -1.84038, 27.6292 to \
  -1.84038, 53.5359 front fs empty border lc rgb '#549f' lw 0.1
set object 2588 polygon from \
  -1.86293, 53.5581 to \
  -0.03, 53.5581 to \
  -0.03, 27.6414 to \
  -1.86293, 27.6414 to \
  -1.86293, 53.5581 front fs empty border lc rgb '#549f' lw 0.1
set object 2589 polygon from \
  -1.88457, 53.5803 to \
  -0.03, 53.5803 to \
  -0.03, 27.6536 to \
  -1.88457, 27.6536 to \
  -1.88457, 53.5803 front fs empty border lc rgb '#549f' lw 0.1
set object 2590 polygon from \
  -1.90527, 53.6026 to \
  -0.03, 53.6026 to \
  -0.03, 27.6659 to \
  -1.90527, 27.6659 to \
  -1.90527, 53.6026 front fs empty border lc rgb '#549f' lw 0.1
set object 2591 polygon from \
  -1.92654, 53.6248 to \
  -0.03, 53.6248 to \
  -0.03, 27.6781 to \
  -1.92654, 27.6781 to \
  -1.92654, 53.6248 front fs empty border lc rgb '#549f' lw 0.1
set object 2592 polygon from \
  -1.94813, 53.647 to \
  -0.03, 53.647 to \
  -0.03, 27.6903 to \
  -1.94813, 27.6903 to \
  -1.94813, 53.647 front fs empty border lc rgb '#549f' lw 0.1
set object 2593 polygon from \
  -1.96877, 53.6693 to \
  -0.03, 53.6693 to \
  -0.03, 27.7026 to \
  -1.96877, 27.7026 to \
  -1.96877, 53.6693 front fs empty border lc rgb '#549f' lw 0.1
set object 2594 polygon from \
  -1.98847, 53.6915 to \
  -0.03, 53.6915 to \
  -0.03, 27.7148 to \
  -1.98847, 27.7148 to \
  -1.98847, 53.6915 front fs empty border lc rgb '#549f' lw 0.1
set object 2595 polygon from \
  -2.02685, 53.7138 to \
  -0.03, 53.7138 to \
  -0.03, 27.727 to \
  -2.02685, 27.727 to \
  -2.02685, 53.7138 front fs empty border lc rgb '#549f' lw 0.1
set object 2596 polygon from \
  -2.06778, 53.736 to \
  -0.03, 53.736 to \
  -0.03, 27.7393 to \
  -2.06778, 27.7393 to \
  -2.06778, 53.736 front fs empty border lc rgb '#549f' lw 0.1
set object 2597 polygon from \
  -2.108, 53.7583 to \
  -0.03, 53.7583 to \
  -0.03, 27.7515 to \
  -2.108, 27.7515 to \
  -2.108, 53.7583 front fs empty border lc rgb '#549f' lw 0.1
set object 2598 polygon from \
  -2.14748, 53.7805 to \
  -0.03, 53.7805 to \
  -0.03, 27.7638 to \
  -2.14748, 27.7638 to \
  -2.14748, 53.7805 front fs empty border lc rgb '#549f' lw 0.1
set object 2599 polygon from \
  -2.18621, 53.8028 to \
  -0.03, 53.8028 to \
  -0.03, 27.776 to \
  -2.18621, 27.776 to \
  -2.18621, 53.8028 front fs empty border lc rgb '#549f' lw 0.1
set object 2600 polygon from \
  -2.22418, 53.825 to \
  -0.03, 53.825 to \
  -0.03, 27.7883 to \
  -2.22418, 27.7883 to \
  -2.22418, 53.825 front fs empty border lc rgb '#549f' lw 0.1
set object 2601 polygon from \
  -2.26136, 53.8473 to \
  -0.03, 53.8473 to \
  -0.03, 27.8005 to \
  -2.26136, 27.8005 to \
  -2.26136, 53.8473 front fs empty border lc rgb '#549f' lw 0.1
set object 2602 polygon from \
  -2.29774, 53.8695 to \
  -0.03, 53.8695 to \
  -0.03, 27.8127 to \
  -2.29774, 27.8127 to \
  -2.29774, 53.8695 front fs empty border lc rgb '#549f' lw 0.1
set object 2603 polygon from \
  -2.3333, 53.8918 to \
  -0.03, 53.8918 to \
  -0.03, 27.825 to \
  -2.3333, 27.825 to \
  -2.3333, 53.8918 front fs empty border lc rgb '#549f' lw 0.1
set object 2604 polygon from \
  -2.36804, 53.914 to \
  -0.03, 53.914 to \
  -0.03, 27.8372 to \
  -2.36804, 27.8372 to \
  -2.36804, 53.914 front fs empty border lc rgb '#549f' lw 0.1
set object 2605 polygon from \
  -2.40193, 53.9363 to \
  -0.03, 53.9363 to \
  -0.03, 27.8495 to \
  -2.40193, 27.8495 to \
  -2.40193, 53.9363 front fs empty border lc rgb '#549f' lw 0.1
set object 2606 polygon from \
  -2.43497, 53.9585 to \
  -0.03, 53.9585 to \
  -0.03, 27.8618 to \
  -2.43497, 27.8618 to \
  -2.43497, 53.9585 front fs empty border lc rgb '#549f' lw 0.1
set object 2607 polygon from \
  -2.46714, 53.9808 to \
  -0.03, 53.9808 to \
  -0.03, 27.874 to \
  -2.46714, 27.874 to \
  -2.46714, 53.9808 front fs empty border lc rgb '#549f' lw 0.1
set object 2608 polygon from \
  -2.49842, 54.003 to \
  -0.03, 54.003 to \
  -0.03, 27.8863 to \
  -2.49842, 27.8863 to \
  -2.49842, 54.003 front fs empty border lc rgb '#549f' lw 0.1
set object 2609 polygon from \
  -2.52881, 54.0253 to \
  -0.03, 54.0253 to \
  -0.03, 27.8985 to \
  -2.52881, 27.8985 to \
  -2.52881, 54.0253 front fs empty border lc rgb '#549f' lw 0.1
set object 2610 polygon from \
  -2.55829, 54.0476 to \
  -0.03, 54.0476 to \
  -0.03, 27.9108 to \
  -2.55829, 27.9108 to \
  -2.55829, 54.0476 front fs empty border lc rgb '#549f' lw 0.1
set object 2611 polygon from \
  -2.58685, 54.0698 to \
  -0.03, 54.0698 to \
  -0.03, 27.923 to \
  -2.58685, 27.923 to \
  -2.58685, 54.0698 front fs empty border lc rgb '#549f' lw 0.1
set object 2612 polygon from \
  -2.61449, 54.0921 to \
  -0.03, 54.0921 to \
  -0.03, 27.9353 to \
  -2.61449, 27.9353 to \
  -2.61449, 54.0921 front fs empty border lc rgb '#549f' lw 0.1
set object 2613 polygon from \
  -2.64118, 54.1144 to \
  -0.03, 54.1144 to \
  -0.03, 27.9476 to \
  -2.64118, 27.9476 to \
  -2.64118, 54.1144 front fs empty border lc rgb '#549f' lw 0.1
set object 2614 polygon from \
  -2.66901, 54.1366 to \
  -0.03, 54.1366 to \
  -0.03, 27.9598 to \
  -2.66901, 27.9598 to \
  -2.66901, 54.1366 front fs empty border lc rgb '#549f' lw 0.1
set object 2615 polygon from \
  -2.69607, 54.1589 to \
  -0.03, 54.1589 to \
  -0.03, 27.9721 to \
  -2.69607, 27.9721 to \
  -2.69607, 54.1589 front fs empty border lc rgb '#549f' lw 0.1
set object 2616 polygon from \
  -2.72213, 54.1812 to \
  -0.03, 54.1812 to \
  -0.03, 27.9844 to \
  -2.72213, 27.9844 to \
  -2.72213, 54.1812 front fs empty border lc rgb '#549f' lw 0.1
set object 2617 polygon from \
  -2.74719, 54.2034 to \
  -0.03, 54.2034 to \
  -0.03, 27.9966 to \
  -2.74719, 27.9966 to \
  -2.74719, 54.2034 front fs empty border lc rgb '#549f' lw 0.1
set object 2618 polygon from \
  -2.77123, 54.2257 to \
  -0.03, 54.2257 to \
  -0.03, 28.0089 to \
  -2.77123, 28.0089 to \
  -2.77123, 54.2257 front fs empty border lc rgb '#549f' lw 0.1
set object 2619 polygon from \
  -2.79426, 54.248 to \
  -0.03, 54.248 to \
  -0.03, 28.0212 to \
  -2.79426, 28.0212 to \
  -2.79426, 54.248 front fs empty border lc rgb '#549f' lw 0.1
set object 2620 polygon from \
  -2.81625, 54.2703 to \
  -0.03, 54.2703 to \
  -0.03, 28.0334 to \
  -2.81625, 28.0334 to \
  -2.81625, 54.2703 front fs empty border lc rgb '#549f' lw 0.1
set object 2621 polygon from \
  -2.83721, 54.2925 to \
  -0.03, 54.2925 to \
  -0.03, 28.0457 to \
  -2.83721, 28.0457 to \
  -2.83721, 54.2925 front fs empty border lc rgb '#549f' lw 0.1
set object 2622 polygon from \
  -2.85712, 54.3148 to \
  -0.03, 54.3148 to \
  -0.03, 28.058 to \
  -2.85712, 28.058 to \
  -2.85712, 54.3148 front fs empty border lc rgb '#549f' lw 0.1
set object 2623 polygon from \
  -2.87599, 54.3371 to \
  -0.03, 54.3371 to \
  -0.03, 28.0702 to \
  -2.87599, 28.0702 to \
  -2.87599, 54.3371 front fs empty border lc rgb '#549f' lw 0.1
set object 2624 polygon from \
  -2.89381, 54.3594 to \
  -0.03, 54.3594 to \
  -0.03, 28.0825 to \
  -2.89381, 28.0825 to \
  -2.89381, 54.3594 front fs empty border lc rgb '#549f' lw 0.1
set object 2625 polygon from \
  -2.91057, 54.3816 to \
  -0.03, 54.3816 to \
  -0.03, 28.0948 to \
  -2.91057, 28.0948 to \
  -2.91057, 54.3816 front fs empty border lc rgb '#549f' lw 0.1
set object 2626 polygon from \
  -2.92627, 54.4039 to \
  -0.03, 54.4039 to \
  -0.03, 28.1071 to \
  -2.92627, 28.1071 to \
  -2.92627, 54.4039 front fs empty border lc rgb '#549f' lw 0.1
set object 2627 polygon from \
  -2.94091, 54.4262 to \
  -0.03, 54.4262 to \
  -0.03, 28.1194 to \
  -2.94091, 28.1194 to \
  -2.94091, 54.4262 front fs empty border lc rgb '#549f' lw 0.1
set object 2628 polygon from \
  -2.95449, 54.4485 to \
  -0.03, 54.4485 to \
  -0.03, 28.1316 to \
  -2.95449, 28.1316 to \
  -2.95449, 54.4485 front fs empty border lc rgb '#549f' lw 0.1
set object 2629 polygon from \
  -2.967, 54.4708 to \
  -0.03, 54.4708 to \
  -0.03, 28.1439 to \
  -2.967, 28.1439 to \
  -2.967, 54.4708 front fs empty border lc rgb '#549f' lw 0.1
set object 2630 polygon from \
  -2.97843, 54.4931 to \
  -0.03, 54.4931 to \
  -0.03, 28.1562 to \
  -2.97843, 28.1562 to \
  -2.97843, 54.4931 front fs empty border lc rgb '#549f' lw 0.1
set object 2631 polygon from \
  -2.9888, 54.5154 to \
  -0.03, 54.5154 to \
  -0.03, 28.1685 to \
  -2.9888, 28.1685 to \
  -2.9888, 54.5154 front fs empty border lc rgb '#549f' lw 0.1
set object 2632 polygon from \
  -2.9981, 54.5376 to \
  -0.03, 54.5376 to \
  -0.03, 28.1808 to \
  -2.9981, 28.1808 to \
  -2.9981, 54.5376 front fs empty border lc rgb '#549f' lw 0.1
set object 2633 polygon from \
  -3.00633, 54.5599 to \
  -0.03, 54.5599 to \
  -0.03, 28.1931 to \
  -3.00633, 28.1931 to \
  -3.00633, 54.5599 front fs empty border lc rgb '#549f' lw 0.1
set object 2634 polygon from \
  -3.01349, 54.5822 to \
  -0.03, 54.5822 to \
  -0.03, 28.2053 to \
  -3.01349, 28.2053 to \
  -3.01349, 54.5822 front fs empty border lc rgb '#549f' lw 0.1
set object 2635 polygon from \
  -3.01958, 54.6045 to \
  -0.03, 54.6045 to \
  -0.03, 28.2176 to \
  -3.01958, 28.2176 to \
  -3.01958, 54.6045 front fs empty border lc rgb '#549f' lw 0.1
set object 2636 polygon from \
  -3.0246, 54.6268 to \
  -0.03, 54.6268 to \
  -0.03, 28.2299 to \
  -3.0246, 28.2299 to \
  -3.0246, 54.6268 front fs empty border lc rgb '#549f' lw 0.1
set object 2637 polygon from \
  -3.02856, 54.6491 to \
  -0.03, 54.6491 to \
  -0.03, 28.2422 to \
  -3.02856, 28.2422 to \
  -3.02856, 54.6491 front fs empty border lc rgb '#549f' lw 0.1
set object 2638 polygon from \
  -3.03147, 54.6714 to \
  -0.03, 54.6714 to \
  -0.03, 28.2545 to \
  -3.03147, 28.2545 to \
  -3.03147, 54.6714 front fs empty border lc rgb '#549f' lw 0.1
set object 2639 polygon from \
  -3.03331, 54.6937 to \
  -0.03, 54.6937 to \
  -0.03, 28.2668 to \
  -3.03331, 28.2668 to \
  -3.03331, 54.6937 front fs empty border lc rgb '#549f' lw 0.1
set object 2640 polygon from \
  -3.0341, 54.716 to \
  -0.03, 54.716 to \
  -0.03, 28.2791 to \
  -3.0341, 28.2791 to \
  -3.0341, 54.716 front fs empty border lc rgb '#549f' lw 0.1
set object 2641 polygon from \
  -3.0341, 54.7383 to \
  -0.03, 54.7383 to \
  -0.03, 28.2914 to \
  -3.0341, 28.2914 to \
  -3.0341, 54.7383 front fs empty border lc rgb '#549f' lw 0.1
set object 2642 polygon from \
  -3.03384, 54.7606 to \
  -0.03, 54.7606 to \
  -0.03, 28.3037 to \
  -3.03384, 28.3037 to \
  -3.03384, 54.7606 front fs empty border lc rgb '#549f' lw 0.1
set object 2643 polygon from \
  -3.03254, 54.7829 to \
  -0.03, 54.7829 to \
  -0.03, 28.316 to \
  -3.03254, 28.316 to \
  -3.03254, 54.7829 front fs empty border lc rgb '#549f' lw 0.1
set object 2644 polygon from \
  -3.0302, 54.8052 to \
  -0.03, 54.8052 to \
  -0.03, 28.3283 to \
  -3.0302, 28.3283 to \
  -3.0302, 54.8052 front fs empty border lc rgb '#549f' lw 0.1
set object 2645 polygon from \
  -3.02683, 54.8275 to \
  -0.03, 54.8275 to \
  -0.03, 28.3406 to \
  -3.02683, 28.3406 to \
  -3.02683, 54.8275 front fs empty border lc rgb '#549f' lw 0.1
set object 2646 polygon from \
  -3.02244, 54.8498 to \
  -0.03, 54.8498 to \
  -0.03, 28.3529 to \
  -3.02244, 28.3529 to \
  -3.02244, 54.8498 front fs empty border lc rgb '#549f' lw 0.1
set object 2647 polygon from \
  -3.01703, 54.8721 to \
  -0.03, 54.8721 to \
  -0.03, 28.3652 to \
  -3.01703, 28.3652 to \
  -3.01703, 54.8721 front fs empty border lc rgb '#549f' lw 0.1
set object 2648 polygon from \
  -3.01061, 54.8944 to \
  -0.03, 54.8944 to \
  -0.03, 28.3775 to \
  -3.01061, 28.3775 to \
  -3.01061, 54.8944 front fs empty border lc rgb '#549f' lw 0.1
set object 2649 polygon from \
  -3.00318, 54.9168 to \
  -0.03, 54.9168 to \
  -0.03, 28.3898 to \
  -3.00318, 28.3898 to \
  -3.00318, 54.9168 front fs empty border lc rgb '#549f' lw 0.1
set object 2650 polygon from \
  -2.99476, 54.9391 to \
  -0.03, 54.9391 to \
  -0.03, 28.4021 to \
  -2.99476, 28.4021 to \
  -2.99476, 54.9391 front fs empty border lc rgb '#549f' lw 0.1
set object 2651 polygon from \
  -2.98536, 54.9614 to \
  -0.03, 54.9614 to \
  -0.03, 28.4144 to \
  -2.98536, 28.4144 to \
  -2.98536, 54.9614 front fs empty border lc rgb '#549f' lw 0.1
set object 2652 polygon from \
  -2.97499, 54.9837 to \
  -0.03, 54.9837 to \
  -0.03, 28.4267 to \
  -2.97499, 28.4267 to \
  -2.97499, 54.9837 front fs empty border lc rgb '#549f' lw 0.1
set object 2653 polygon from \
  -2.96365, 55.006 to \
  -0.03, 55.006 to \
  -0.03, 28.4391 to \
  -2.96365, 28.4391 to \
  -2.96365, 55.006 front fs empty border lc rgb '#549f' lw 0.1
set object 2654 polygon from \
  -2.95136, 55.0283 to \
  -0.03, 55.0283 to \
  -0.03, 28.4514 to \
  -2.95136, 28.4514 to \
  -2.95136, 55.0283 front fs empty border lc rgb '#549f' lw 0.1
set object 2655 polygon from \
  -2.93812, 55.0506 to \
  -0.03, 55.0506 to \
  -0.03, 28.4637 to \
  -2.93812, 28.4637 to \
  -2.93812, 55.0506 front fs empty border lc rgb '#549f' lw 0.1
set object 2656 polygon from \
  -2.92395, 55.073 to \
  -0.03, 55.073 to \
  -0.03, 28.476 to \
  -2.92395, 28.476 to \
  -2.92395, 55.073 front fs empty border lc rgb '#549f' lw 0.1
set object 2657 polygon from \
  -2.90887, 55.0953 to \
  -0.03, 55.0953 to \
  -0.03, 28.4883 to \
  -2.90887, 28.4883 to \
  -2.90887, 55.0953 front fs empty border lc rgb '#549f' lw 0.1
set object 2658 polygon from \
  -2.89287, 55.1176 to \
  -0.03, 55.1176 to \
  -0.03, 28.5006 to \
  -2.89287, 28.5006 to \
  -2.89287, 55.1176 front fs empty border lc rgb '#549f' lw 0.1
set object 2659 polygon from \
  -2.87599, 55.1399 to \
  -0.03, 55.1399 to \
  -0.03, 28.513 to \
  -2.87599, 28.513 to \
  -2.87599, 55.1399 front fs empty border lc rgb '#549f' lw 0.1
set object 2660 polygon from \
  -2.85822, 55.1623 to \
  -0.03, 55.1623 to \
  -0.03, 28.5253 to \
  -2.85822, 28.5253 to \
  -2.85822, 55.1623 front fs empty border lc rgb '#549f' lw 0.1
set object 2661 polygon from \
  -2.83958, 55.1846 to \
  -0.03, 55.1846 to \
  -0.03, 28.5376 to \
  -2.83958, 28.5376 to \
  -2.83958, 55.1846 front fs empty border lc rgb '#549f' lw 0.1
set object 2662 polygon from \
  -2.82009, 55.2069 to \
  -0.03, 55.2069 to \
  -0.03, 28.5499 to \
  -2.82009, 28.5499 to \
  -2.82009, 55.2069 front fs empty border lc rgb '#549f' lw 0.1
set object 2663 polygon from \
  -2.79976, 55.2292 to \
  -0.03, 55.2292 to \
  -0.03, 28.5622 to \
  -2.79976, 28.5622 to \
  -2.79976, 55.2292 front fs empty border lc rgb '#549f' lw 0.1
set object 2664 polygon from \
  -2.7786, 55.2516 to \
  -0.03, 55.2516 to \
  -0.03, 28.5746 to \
  -2.7786, 28.5746 to \
  -2.7786, 55.2516 front fs empty border lc rgb '#549f' lw 0.1
set object 2665 polygon from \
  -2.75663, 55.2739 to \
  -0.03, 55.2739 to \
  -0.03, 28.5869 to \
  -2.75663, 28.5869 to \
  -2.75663, 55.2739 front fs empty border lc rgb '#549f' lw 0.1
set object 2666 polygon from \
  -2.73387, 55.2962 to \
  -0.03, 55.2962 to \
  -0.03, 28.5992 to \
  -2.73387, 28.5992 to \
  -2.73387, 55.2962 front fs empty border lc rgb '#549f' lw 0.1
set object 2667 polygon from \
  -2.71033, 55.3186 to \
  -0.03, 55.3186 to \
  -0.03, 28.6116 to \
  -2.71033, 28.6116 to \
  -2.71033, 55.3186 front fs empty border lc rgb '#549f' lw 0.1
set object 2668 polygon from \
  -2.68603, 55.3409 to \
  -0.03, 55.3409 to \
  -0.03, 28.6239 to \
  -2.68603, 28.6239 to \
  -2.68603, 55.3409 front fs empty border lc rgb '#549f' lw 0.1
set object 2669 polygon from \
  -2.66097, 55.3632 to \
  -0.03, 55.3632 to \
  -0.03, 28.6362 to \
  -2.66097, 28.6362 to \
  -2.66097, 55.3632 front fs empty border lc rgb '#549f' lw 0.1
set object 2670 polygon from \
  -2.63519, 55.3856 to \
  -0.03, 55.3856 to \
  -0.03, 28.6486 to \
  -2.63519, 28.6486 to \
  -2.63519, 55.3856 front fs empty border lc rgb '#549f' lw 0.1
set object 2671 polygon from \
  -2.62878, 55.4079 to \
  -0.03, 55.4079 to \
  -0.03, 28.6609 to \
  -2.62878, 28.6609 to \
  -2.62878, 55.4079 front fs empty border lc rgb '#549f' lw 0.1
set object 2672 polygon from \
  -2.64532, 55.4302 to \
  -0.03, 55.4302 to \
  -0.03, 28.6732 to \
  -2.64532, 28.6732 to \
  -2.64532, 55.4302 front fs empty border lc rgb '#549f' lw 0.1
set object 2673 polygon from \
  -2.66132, 55.4526 to \
  -0.03, 55.4526 to \
  -0.03, 28.6856 to \
  -2.66132, 28.6856 to \
  -2.66132, 55.4526 front fs empty border lc rgb '#549f' lw 0.1
set object 2674 polygon from \
  -2.67677, 55.4749 to \
  -0.03, 55.4749 to \
  -0.03, 28.6979 to \
  -2.67677, 28.6979 to \
  -2.67677, 55.4749 front fs empty border lc rgb '#549f' lw 0.1
set object 2675 polygon from \
  -2.69167, 55.4973 to \
  -0.03, 55.4973 to \
  -0.03, 28.7102 to \
  -2.69167, 28.7102 to \
  -2.69167, 55.4973 front fs empty border lc rgb '#549f' lw 0.1
set object 2676 polygon from \
  -2.70599, 55.5196 to \
  -0.03, 55.5196 to \
  -0.03, 28.7226 to \
  -2.70599, 28.7226 to \
  -2.70599, 55.5196 front fs empty border lc rgb '#549f' lw 0.1
set object 2677 polygon from \
  -2.71972, 55.542 to \
  -0.03, 55.542 to \
  -0.03, 28.7349 to \
  -2.71972, 28.7349 to \
  -2.71972, 55.542 front fs empty border lc rgb '#549f' lw 0.1
set object 2678 polygon from \
  -2.73553, 55.5643 to \
  -0.03, 55.5643 to \
  -0.03, 28.7473 to \
  -2.73553, 28.7473 to \
  -2.73553, 55.5643 front fs empty border lc rgb '#549f' lw 0.1
set object 2679 polygon from \
  -2.75683, 55.5867 to \
  -0.03, 55.5867 to \
  -0.03, 28.7596 to \
  -2.75683, 28.7596 to \
  -2.75683, 55.5867 front fs empty border lc rgb '#549f' lw 0.1
set object 2680 polygon from \
  -2.77742, 55.609 to \
  -0.03, 55.609 to \
  -0.03, 28.772 to \
  -2.77742, 28.772 to \
  -2.77742, 55.609 front fs empty border lc rgb '#549f' lw 0.1
set object 2681 polygon from \
  -2.79728, 55.6314 to \
  -0.03, 55.6314 to \
  -0.03, 28.7843 to \
  -2.79728, 28.7843 to \
  -2.79728, 55.6314 front fs empty border lc rgb '#549f' lw 0.1
set object 2682 polygon from \
  -2.81641, 55.6537 to \
  -0.03, 55.6537 to \
  -0.03, 28.7966 to \
  -2.81641, 28.7966 to \
  -2.81641, 55.6537 front fs empty border lc rgb '#549f' lw 0.1
set object 2683 polygon from \
  -2.83479, 55.6761 to \
  -0.03, 55.6761 to \
  -0.03, 28.809 to \
  -2.83479, 28.809 to \
  -2.83479, 55.6761 front fs empty border lc rgb '#549f' lw 0.1
set object 2684 polygon from \
  -2.8524, 55.6984 to \
  -0.03, 55.6984 to \
  -0.03, 28.8213 to \
  -2.8524, 28.8213 to \
  -2.8524, 55.6984 front fs empty border lc rgb '#549f' lw 0.1
set object 2685 polygon from \
  -2.86923, 55.7208 to \
  -0.03, 55.7208 to \
  -0.03, 28.8337 to \
  -2.86923, 28.8337 to \
  -2.86923, 55.7208 front fs empty border lc rgb '#549f' lw 0.1
set object 2686 polygon from \
  -2.88755, 55.7431 to \
  -0.03, 55.7431 to \
  -0.03, 28.8461 to \
  -2.88755, 28.8461 to \
  -2.88755, 55.7431 front fs empty border lc rgb '#549f' lw 0.1
set object 2687 polygon from \
  -2.91214, 55.7655 to \
  -0.03, 55.7655 to \
  -0.03, 28.8584 to \
  -2.91214, 28.8584 to \
  -2.91214, 55.7655 front fs empty border lc rgb '#549f' lw 0.1
set object 2688 polygon from \
  -2.93597, 55.7878 to \
  -0.03, 55.7878 to \
  -0.03, 28.8708 to \
  -2.93597, 28.8708 to \
  -2.93597, 55.7878 front fs empty border lc rgb '#549f' lw 0.1
set object 2689 polygon from \
  -2.95904, 55.8102 to \
  -0.03, 55.8102 to \
  -0.03, 28.8831 to \
  -2.95904, 28.8831 to \
  -2.95904, 55.8102 front fs empty border lc rgb '#549f' lw 0.1
set object 2690 polygon from \
  -2.98133, 55.8326 to \
  -0.03, 55.8326 to \
  -0.03, 28.8955 to \
  -2.98133, 28.8955 to \
  -2.98133, 55.8326 front fs empty border lc rgb '#549f' lw 0.1
set object 2691 polygon from \
  -3.00282, 55.8549 to \
  -0.03, 55.8549 to \
  -0.03, 28.9078 to \
  -3.00282, 28.9078 to \
  -3.00282, 55.8549 front fs empty border lc rgb '#549f' lw 0.1
set object 2692 polygon from \
  -3.02349, 55.8773 to \
  -0.03, 55.8773 to \
  -0.03, 28.9202 to \
  -3.02349, 28.9202 to \
  -3.02349, 55.8773 front fs empty border lc rgb '#549f' lw 0.1
set object 2693 polygon from \
  -3.04335, 55.8997 to \
  -0.03, 55.8997 to \
  -0.03, 28.9326 to \
  -3.04335, 28.9326 to \
  -3.04335, 55.8997 front fs empty border lc rgb '#549f' lw 0.1
set object 2694 polygon from \
  -3.06236, 55.922 to \
  -0.03, 55.922 to \
  -0.03, 28.9449 to \
  -3.06236, 28.9449 to \
  -3.06236, 55.922 front fs empty border lc rgb '#549f' lw 0.1
set object 2695 polygon from \
  -3.08052, 55.9444 to \
  -0.03, 55.9444 to \
  -0.03, 28.9573 to \
  -3.08052, 28.9573 to \
  -3.08052, 55.9444 front fs empty border lc rgb '#549f' lw 0.1
set object 2696 polygon from \
  -3.09782, 55.9668 to \
  -0.03, 55.9668 to \
  -0.03, 28.9697 to \
  -3.09782, 28.9697 to \
  -3.09782, 55.9668 front fs empty border lc rgb '#549f' lw 0.1
set object 2697 polygon from \
  -3.11424, 55.9891 to \
  -0.03, 55.9891 to \
  -0.03, 28.982 to \
  -3.11424, 28.982 to \
  -3.11424, 55.9891 front fs empty border lc rgb '#549f' lw 0.1
set object 2698 polygon from \
  -3.12977, 56.0115 to \
  -0.03, 56.0115 to \
  -0.03, 28.9944 to \
  -3.12977, 28.9944 to \
  -3.12977, 56.0115 front fs empty border lc rgb '#549f' lw 0.1
set object 2699 polygon from \
  -3.1444, 56.0339 to \
  -0.03, 56.0339 to \
  -0.03, 29.0068 to \
  -3.1444, 29.0068 to \
  -3.1444, 56.0339 front fs empty border lc rgb '#549f' lw 0.1
set object 2700 polygon from \
  -3.15812, 56.0563 to \
  -0.03, 56.0563 to \
  -0.03, 29.0191 to \
  -3.15812, 29.0191 to \
  -3.15812, 56.0563 front fs empty border lc rgb '#549f' lw 0.1
set object 2701 polygon from \
  -3.17092, 56.0786 to \
  -0.03, 56.0786 to \
  -0.03, 29.0315 to \
  -3.17092, 29.0315 to \
  -3.17092, 56.0786 front fs empty border lc rgb '#549f' lw 0.1
set object 2702 polygon from \
  -3.18278, 56.101 to \
  -0.03, 56.101 to \
  -0.03, 29.0439 to \
  -3.18278, 29.0439 to \
  -3.18278, 56.101 front fs empty border lc rgb '#549f' lw 0.1
set object 2703 polygon from \
  -3.1937, 56.1234 to \
  -0.03, 56.1234 to \
  -0.03, 29.0562 to \
  -3.1937, 29.0562 to \
  -3.1937, 56.1234 front fs empty border lc rgb '#549f' lw 0.1
set object 2704 polygon from \
  -3.20366, 56.1458 to \
  -0.03, 56.1458 to \
  -0.03, 29.0686 to \
  -3.20366, 29.0686 to \
  -3.20366, 56.1458 front fs empty border lc rgb '#549f' lw 0.1
set object 2705 polygon from \
  -3.21267, 56.1681 to \
  -0.03, 56.1681 to \
  -0.03, 29.081 to \
  -3.21267, 29.081 to \
  -3.21267, 56.1681 front fs empty border lc rgb '#549f' lw 0.1
set object 2706 polygon from \
  -3.2207, 56.1905 to \
  -0.03, 56.1905 to \
  -0.03, 29.0934 to \
  -3.2207, 29.0934 to \
  -3.2207, 56.1905 front fs empty border lc rgb '#549f' lw 0.1
set object 2707 polygon from \
  -3.22775, 56.2129 to \
  -0.03, 56.2129 to \
  -0.03, 29.1058 to \
  -3.22775, 29.1058 to \
  -3.22775, 56.2129 front fs empty border lc rgb '#549f' lw 0.1
set object 2708 polygon from \
  -3.23381, 56.2353 to \
  -0.03, 56.2353 to \
  -0.03, 29.1181 to \
  -3.23381, 29.1181 to \
  -3.23381, 56.2353 front fs empty border lc rgb '#549f' lw 0.1
set object 2709 polygon from \
  -3.23887, 56.2577 to \
  -0.03, 56.2577 to \
  -0.03, 29.1305 to \
  -3.23887, 29.1305 to \
  -3.23887, 56.2577 front fs empty border lc rgb '#549f' lw 0.1
set object 2710 polygon from \
  -3.24293, 56.2801 to \
  -0.03, 56.2801 to \
  -0.03, 29.1429 to \
  -3.24293, 29.1429 to \
  -3.24293, 56.2801 front fs empty border lc rgb '#549f' lw 0.1
set object 2711 polygon from \
  -3.24598, 56.3025 to \
  -0.03, 56.3025 to \
  -0.03, 29.1553 to \
  -3.24598, 29.1553 to \
  -3.24598, 56.3025 front fs empty border lc rgb '#549f' lw 0.1
set object 2712 polygon from \
  -3.24801, 56.3248 to \
  -0.03, 56.3248 to \
  -0.03, 29.1677 to \
  -3.24801, 29.1677 to \
  -3.24801, 56.3248 front fs empty border lc rgb '#549f' lw 0.1
set object 2713 polygon from \
  -3.24902, 56.3472 to \
  -0.03, 56.3472 to \
  -0.03, 29.1801 to \
  -3.24902, 29.1801 to \
  -3.24902, 56.3472 front fs empty border lc rgb '#549f' lw 0.1
set object 2714 polygon from \
  -3.24902, 56.3696 to \
  -0.03, 56.3696 to \
  -0.03, 29.1924 to \
  -3.24902, 29.1924 to \
  -3.24902, 56.3696 front fs empty border lc rgb '#549f' lw 0.1
set object 2715 polygon from \
  -3.249, 56.392 to \
  -0.03, 56.392 to \
  -0.03, 29.2048 to \
  -3.249, 29.2048 to \
  -3.249, 56.392 front fs empty border lc rgb '#549f' lw 0.1
set object 2716 polygon from \
  -3.24795, 56.4144 to \
  -0.03, 56.4144 to \
  -0.03, 29.2172 to \
  -3.24795, 29.2172 to \
  -3.24795, 56.4144 front fs empty border lc rgb '#549f' lw 0.1
set object 2717 polygon from \
  -3.24586, 56.4368 to \
  -0.03, 56.4368 to \
  -0.03, 29.2296 to \
  -3.24586, 29.2296 to \
  -3.24586, 56.4368 front fs empty border lc rgb '#549f' lw 0.1
set object 2718 polygon from \
  -3.24272, 56.4592 to \
  -0.03, 56.4592 to \
  -0.03, 29.242 to \
  -3.24272, 29.242 to \
  -3.24272, 56.4592 front fs empty border lc rgb '#549f' lw 0.1
set object 2719 polygon from \
  -3.23854, 56.4816 to \
  -0.03, 56.4816 to \
  -0.03, 29.2544 to \
  -3.23854, 29.2544 to \
  -3.23854, 56.4816 front fs empty border lc rgb '#549f' lw 0.1
set object 2720 polygon from \
  -3.23331, 56.504 to \
  -0.03, 56.504 to \
  -0.03, 29.2668 to \
  -3.23331, 29.2668 to \
  -3.23331, 56.504 front fs empty border lc rgb '#549f' lw 0.1
set object 2721 polygon from \
  -3.22703, 56.5264 to \
  -0.03, 56.5264 to \
  -0.03, 29.2792 to \
  -3.22703, 29.2792 to \
  -3.22703, 56.5264 front fs empty border lc rgb '#549f' lw 0.1
set object 2722 polygon from \
  -3.21969, 56.5488 to \
  -0.03, 56.5488 to \
  -0.03, 29.2916 to \
  -3.21969, 29.2916 to \
  -3.21969, 56.5488 front fs empty border lc rgb '#549f' lw 0.1
set object 2723 polygon from \
  -3.21129, 56.5712 to \
  -0.03, 56.5712 to \
  -0.03, 29.304 to \
  -3.21129, 29.304 to \
  -3.21129, 56.5712 front fs empty border lc rgb '#549f' lw 0.1
set object 2724 polygon from \
  -3.20184, 56.5936 to \
  -0.03, 56.5936 to \
  -0.03, 29.3164 to \
  -3.20184, 29.3164 to \
  -3.20184, 56.5936 front fs empty border lc rgb '#549f' lw 0.1
set object 2725 polygon from \
  -3.19133, 56.616 to \
  -0.03, 56.616 to \
  -0.03, 29.3288 to \
  -3.19133, 29.3288 to \
  -3.19133, 56.616 front fs empty border lc rgb '#549f' lw 0.1
set object 2726 polygon from \
  -3.17976, 56.6384 to \
  -0.03, 56.6384 to \
  -0.03, 29.3412 to \
  -3.17976, 29.3412 to \
  -3.17976, 56.6384 front fs empty border lc rgb '#549f' lw 0.1
set object 2727 polygon from \
  -3.16714, 56.6608 to \
  -0.03, 56.6608 to \
  -0.03, 29.3536 to \
  -3.16714, 29.3536 to \
  -3.16714, 56.6608 front fs empty border lc rgb '#549f' lw 0.1
set object 2728 polygon from \
  -3.15345, 56.6832 to \
  -0.03, 56.6832 to \
  -0.03, 29.366 to \
  -3.15345, 29.366 to \
  -3.15345, 56.6832 front fs empty border lc rgb '#549f' lw 0.1
set object 2729 polygon from \
  -3.13871, 56.7057 to \
  -0.03, 56.7057 to \
  -0.03, 29.3784 to \
  -3.13871, 29.3784 to \
  -3.13871, 56.7057 front fs empty border lc rgb '#549f' lw 0.1
set object 2730 polygon from \
  -3.12292, 56.7281 to \
  -0.03, 56.7281 to \
  -0.03, 29.3908 to \
  -3.12292, 29.3908 to \
  -3.12292, 56.7281 front fs empty border lc rgb '#549f' lw 0.1
set object 2731 polygon from \
  -3.10607, 56.7505 to \
  -0.03, 56.7505 to \
  -0.03, 29.4032 to \
  -3.10607, 29.4032 to \
  -3.10607, 56.7505 front fs empty border lc rgb '#549f' lw 0.1
set object 2732 polygon from \
  -3.08818, 56.7729 to \
  -0.03, 56.7729 to \
  -0.03, 29.4156 to \
  -3.08818, 29.4156 to \
  -3.08818, 56.7729 front fs empty border lc rgb '#549f' lw 0.1
set object 2733 polygon from \
  -3.06924, 56.7953 to \
  -0.03, 56.7953 to \
  -0.03, 29.4281 to \
  -3.06924, 29.4281 to \
  -3.06924, 56.7953 front fs empty border lc rgb '#549f' lw 0.1
set object 2734 polygon from \
  -3.04925, 56.8177 to \
  -0.03, 56.8177 to \
  -0.03, 29.4405 to \
  -3.04925, 29.4405 to \
  -3.04925, 56.8177 front fs empty border lc rgb '#549f' lw 0.1
set object 2735 polygon from \
  -3.02823, 56.8401 to \
  -0.03, 56.8401 to \
  -0.03, 29.4529 to \
  -3.02823, 29.4529 to \
  -3.02823, 56.8401 front fs empty border lc rgb '#549f' lw 0.1
set object 2736 polygon from \
  -3.00617, 56.8626 to \
  -0.03, 56.8626 to \
  -0.03, 29.4653 to \
  -3.00617, 29.4653 to \
  -3.00617, 56.8626 front fs empty border lc rgb '#549f' lw 0.1
set object 2737 polygon from \
  -2.98309, 56.885 to \
  -0.03, 56.885 to \
  -0.03, 29.4777 to \
  -2.98309, 29.4777 to \
  -2.98309, 56.885 front fs empty border lc rgb '#549f' lw 0.1
set object 2738 polygon from \
  -2.95944, 56.9074 to \
  -0.03, 56.9074 to \
  -0.03, 29.4901 to \
  -2.95944, 29.4901 to \
  -2.95944, 56.9074 front fs empty border lc rgb '#549f' lw 0.1
set object 2739 polygon from \
  -2.93914, 56.9298 to \
  -0.03, 56.9298 to \
  -0.03, 29.5026 to \
  -2.93914, 29.5026 to \
  -2.93914, 56.9298 front fs empty border lc rgb '#549f' lw 0.1
set object 2740 polygon from \
  -2.91781, 56.9523 to \
  -0.03, 56.9523 to \
  -0.03, 29.515 to \
  -2.91781, 29.515 to \
  -2.91781, 56.9523 front fs empty border lc rgb '#549f' lw 0.1
set object 2741 polygon from \
  -2.89547, 56.9747 to \
  -0.03, 56.9747 to \
  -0.03, 29.5274 to \
  -2.89547, 29.5274 to \
  -2.89547, 56.9747 front fs empty border lc rgb '#549f' lw 0.1
set object 2742 polygon from \
  -2.87211, 56.9971 to \
  -0.03, 56.9971 to \
  -0.03, 29.5398 to \
  -2.87211, 29.5398 to \
  -2.87211, 56.9971 front fs empty border lc rgb '#549f' lw 0.1
set object 2743 polygon from \
  -2.84774, 57.0195 to \
  -0.03, 57.0195 to \
  -0.03, 29.5522 to \
  -2.84774, 29.5522 to \
  -2.84774, 57.0195 front fs empty border lc rgb '#549f' lw 0.1
set object 2744 polygon from \
  -2.82237, 57.042 to \
  -0.03, 57.042 to \
  -0.03, 29.5647 to \
  -2.82237, 29.5647 to \
  -2.82237, 57.042 front fs empty border lc rgb '#549f' lw 0.1
set object 2745 polygon from \
  -2.79601, 57.0644 to \
  -0.03, 57.0644 to \
  -0.03, 29.5771 to \
  -2.79601, 29.5771 to \
  -2.79601, 57.0644 front fs empty border lc rgb '#549f' lw 0.1
set object 2746 polygon from \
  -2.76865, 57.0868 to \
  -0.03, 57.0868 to \
  -0.03, 29.5895 to \
  -2.76865, 29.5895 to \
  -2.76865, 57.0868 front fs empty border lc rgb '#549f' lw 0.1
set object 2747 polygon from \
  -2.74031, 57.1093 to \
  -0.03, 57.1093 to \
  -0.03, 29.602 to \
  -2.74031, 29.602 to \
  -2.74031, 57.1093 front fs empty border lc rgb '#549f' lw 0.1
set object 2748 polygon from \
  -2.711, 57.1317 to \
  -0.03, 57.1317 to \
  -0.03, 29.6144 to \
  -2.711, 29.6144 to \
  -2.711, 57.1317 front fs empty border lc rgb '#549f' lw 0.1
set object 2749 polygon from \
  -2.68071, 57.1541 to \
  -0.03, 57.1541 to \
  -0.03, 29.6268 to \
  -2.68071, 29.6268 to \
  -2.68071, 57.1541 front fs empty border lc rgb '#549f' lw 0.1
set object 2750 polygon from \
  -2.64947, 57.1766 to \
  -0.03, 57.1766 to \
  -0.03, 29.6393 to \
  -2.64947, 29.6393 to \
  -2.64947, 57.1766 front fs empty border lc rgb '#549f' lw 0.1
set object 2751 polygon from \
  -2.61728, 57.199 to \
  -0.03, 57.199 to \
  -0.03, 29.6517 to \
  -2.61728, 29.6517 to \
  -2.61728, 57.199 front fs empty border lc rgb '#549f' lw 0.1
set object 2752 polygon from \
  -2.58415, 57.2214 to \
  -0.03, 57.2214 to \
  -0.03, 29.6641 to \
  -2.58415, 29.6641 to \
  -2.58415, 57.2214 front fs empty border lc rgb '#549f' lw 0.1
set object 2753 polygon from \
  -2.55009, 57.2439 to \
  -0.03, 57.2439 to \
  -0.03, 29.6766 to \
  -2.55009, 29.6766 to \
  -2.55009, 57.2439 front fs empty border lc rgb '#549f' lw 0.1
set object 2754 polygon from \
  -2.51511, 57.2663 to \
  -0.03, 57.2663 to \
  -0.03, 29.689 to \
  -2.51511, 29.689 to \
  -2.51511, 57.2663 front fs empty border lc rgb '#549f' lw 0.1
set object 2755 polygon from \
  -2.47922, 57.2888 to \
  -0.03, 57.2888 to \
  -0.03, 29.7014 to \
  -2.47922, 29.7014 to \
  -2.47922, 57.2888 front fs empty border lc rgb '#549f' lw 0.1
set object 2756 polygon from \
  -2.44344, 57.3112 to \
  -0.03, 57.3112 to \
  -0.03, 29.7139 to \
  -2.44344, 29.7139 to \
  -2.44344, 57.3112 front fs empty border lc rgb '#549f' lw 0.1
set object 2757 polygon from \
  -2.40725, 57.3337 to \
  -0.03, 57.3337 to \
  -0.03, 29.7263 to \
  -2.40725, 29.7263 to \
  -2.40725, 57.3337 front fs empty border lc rgb '#549f' lw 0.1
set object 2758 polygon from \
  -2.37019, 57.3561 to \
  -0.03, 57.3561 to \
  -0.03, 29.7388 to \
  -2.37019, 29.7388 to \
  -2.37019, 57.3561 front fs empty border lc rgb '#549f' lw 0.1
set object 2759 polygon from \
  -2.33226, 57.3786 to \
  -0.03, 57.3786 to \
  -0.03, 29.7512 to \
  -2.33226, 29.7512 to \
  -2.33226, 57.3786 front fs empty border lc rgb '#549f' lw 0.1
set object 2760 polygon from \
  -2.29349, 57.401 to \
  -0.03, 57.401 to \
  -0.03, 29.7637 to \
  -2.29349, 29.7637 to \
  -2.29349, 57.401 front fs empty border lc rgb '#549f' lw 0.1
set object 2761 polygon from \
  -2.25389, 57.4235 to \
  -0.03, 57.4235 to \
  -0.03, 29.7761 to \
  -2.25389, 29.7761 to \
  -2.25389, 57.4235 front fs empty border lc rgb '#549f' lw 0.1
set object 2762 polygon from \
  -2.21347, 57.4459 to \
  -0.03, 57.4459 to \
  -0.03, 29.7885 to \
  -2.21347, 29.7885 to \
  -2.21347, 57.4459 front fs empty border lc rgb '#549f' lw 0.1
set object 2763 polygon from \
  -2.17224, 57.4684 to \
  -0.03, 57.4684 to \
  -0.03, 29.801 to \
  -2.17224, 29.801 to \
  -2.17224, 57.4684 front fs empty border lc rgb '#549f' lw 0.1
set object 2764 polygon from \
  -2.13022, 57.4908 to \
  -0.03, 57.4908 to \
  -0.03, 29.8134 to \
  -2.13022, 29.8134 to \
  -2.13022, 57.4908 front fs empty border lc rgb '#549f' lw 0.1
set object 2765 polygon from \
  -2.08743, 57.5133 to \
  -0.03, 57.5133 to \
  -0.03, 29.8259 to \
  -2.08743, 29.8259 to \
  -2.08743, 57.5133 front fs empty border lc rgb '#549f' lw 0.1
set object 2766 polygon from \
  -2.04387, 57.5357 to \
  -0.03, 57.5357 to \
  -0.03, 29.8384 to \
  -2.04387, 29.8384 to \
  -2.04387, 57.5357 front fs empty border lc rgb '#549f' lw 0.1
set object 2767 polygon from \
  -1.99957, 57.5582 to \
  -0.03, 57.5582 to \
  -0.03, 29.8508 to \
  -1.99957, 29.8508 to \
  -1.99957, 57.5582 front fs empty border lc rgb '#549f' lw 0.1
set object 2768 polygon from \
  -1.95454, 57.5806 to \
  -0.03, 57.5806 to \
  -0.03, 29.8633 to \
  -1.95454, 29.8633 to \
  -1.95454, 57.5806 front fs empty border lc rgb '#549f' lw 0.1
set object 2769 polygon from \
  -1.90879, 57.6031 to \
  -0.03, 57.6031 to \
  -0.03, 29.8757 to \
  -1.90879, 29.8757 to \
  -1.90879, 57.6031 front fs empty border lc rgb '#549f' lw 0.1
set object 2770 polygon from \
  -1.86235, 57.6256 to \
  -0.03, 57.6256 to \
  -0.03, 29.8882 to \
  -1.86235, 29.8882 to \
  -1.86235, 57.6256 front fs empty border lc rgb '#549f' lw 0.1
set object 2771 polygon from \
  -1.81524, 57.648 to \
  -0.03, 57.648 to \
  -0.03, 29.9006 to \
  -1.81524, 29.9006 to \
  -1.81524, 57.648 front fs empty border lc rgb '#549f' lw 0.1
set object 2772 polygon from \
  -1.76746, 57.6705 to \
  -0.03, 57.6705 to \
  -0.03, 29.9131 to \
  -1.76746, 29.9131 to \
  -1.76746, 57.6705 front fs empty border lc rgb '#549f' lw 0.1
set object 2773 polygon from \
  -1.71903, 57.693 to \
  -0.03, 57.693 to \
  -0.03, 29.9256 to \
  -1.71903, 29.9256 to \
  -1.71903, 57.693 front fs empty border lc rgb '#549f' lw 0.1
set object 2774 polygon from \
  -1.66998, 57.7154 to \
  -0.03, 57.7154 to \
  -0.03, 29.938 to \
  -1.66998, 29.938 to \
  -1.66998, 57.7154 front fs empty border lc rgb '#549f' lw 0.1
set object 2775 polygon from \
  -1.62033, 57.7379 to \
  -0.03, 57.7379 to \
  -0.03, 29.9505 to \
  -1.62033, 29.9505 to \
  -1.62033, 57.7379 front fs empty border lc rgb '#549f' lw 0.1
set object 2776 polygon from \
  -1.57008, 57.7604 to \
  -0.03, 57.7604 to \
  -0.03, 29.963 to \
  -1.57008, 29.963 to \
  -1.57008, 57.7604 front fs empty border lc rgb '#549f' lw 0.1
set object 2777 polygon from \
  -1.51927, 57.7828 to \
  -0.03, 57.7828 to \
  -0.03, 29.9754 to \
  -1.51927, 29.9754 to \
  -1.51927, 57.7828 front fs empty border lc rgb '#549f' lw 0.1
set object 2778 polygon from \
  -1.4679, 57.8053 to \
  -0.03, 57.8053 to \
  -0.03, 29.9879 to \
  -1.4679, 29.9879 to \
  -1.4679, 57.8053 front fs empty border lc rgb '#549f' lw 0.1
set object 2779 polygon from \
  -1.41601, 57.8278 to \
  -0.03, 57.8278 to \
  -0.03, 30.0004 to \
  -1.41601, 30.0004 to \
  -1.41601, 57.8278 front fs empty border lc rgb '#549f' lw 0.1
set object 2780 polygon from \
  -1.37153, 57.8503 to \
  -0.03, 57.8503 to \
  -0.03, 30.0128 to \
  -1.37153, 30.0128 to \
  -1.37153, 57.8503 front fs empty border lc rgb '#549f' lw 0.1
set object 2781 polygon from \
  -1.32716, 57.8727 to \
  -0.03, 57.8727 to \
  -0.03, 30.0253 to \
  -1.32716, 30.0253 to \
  -1.32716, 57.8727 front fs empty border lc rgb '#549f' lw 0.1
set object 2782 polygon from \
  -1.28212, 57.8952 to \
  -0.03, 57.8952 to \
  -0.03, 30.0378 to \
  -1.28212, 30.0378 to \
  -1.28212, 57.8952 front fs empty border lc rgb '#549f' lw 0.1
set object 2783 polygon from \
  -1.23643, 57.9177 to \
  -0.03, 57.9177 to \
  -0.03, 30.0502 to \
  -1.23643, 30.0502 to \
  -1.23643, 57.9177 front fs empty border lc rgb '#549f' lw 0.1
set object 2784 polygon from \
  -1.19013, 57.9402 to \
  -0.03, 57.9402 to \
  -0.03, 30.0627 to \
  -1.19013, 30.0627 to \
  -1.19013, 57.9402 front fs empty border lc rgb '#549f' lw 0.1
set object 2785 polygon from \
  -1.14325, 57.9626 to \
  -0.03, 57.9626 to \
  -0.03, 30.0752 to \
  -1.14325, 30.0752 to \
  -1.14325, 57.9626 front fs empty border lc rgb '#549f' lw 0.1
set object 2786 polygon from \
  -1.09581, 57.9851 to \
  -0.03, 57.9851 to \
  -0.03, 30.0877 to \
  -1.09581, 30.0877 to \
  -1.09581, 57.9851 front fs empty border lc rgb '#549f' lw 0.1
set object 2787 polygon from \
  -1.04786, 58.0076 to \
  -0.03, 58.0076 to \
  -0.03, 30.1002 to \
  -1.04786, 30.1002 to \
  -1.04786, 58.0076 front fs empty border lc rgb '#549f' lw 0.1
set object 2788 polygon from \
  -0.999409, 58.0301 to \
  -0.03, 58.0301 to \
  -0.03, 30.1126 to \
  -0.999409, 30.1126 to \
  -0.999409, 58.0301 front fs empty border lc rgb '#549f' lw 0.1
set object 2789 polygon from \
  -0.950502, 58.0526 to \
  -0.03, 58.0526 to \
  -0.03, 30.1251 to \
  -0.950502, 30.1251 to \
  -0.950502, 58.0526 front fs empty border lc rgb '#549f' lw 0.1
set object 2790 polygon from \
  -0.901169, 58.0751 to \
  -0.03, 58.0751 to \
  -0.03, 30.1376 to \
  -0.901169, 30.1376 to \
  -0.901169, 58.0751 front fs empty border lc rgb '#549f' lw 0.1
set object 2791 polygon from \
  -0.851441, 58.0976 to \
  -0.03, 58.0976 to \
  -0.03, 30.1501 to \
  -0.851441, 30.1501 to \
  -0.851441, 58.0976 front fs empty border lc rgb '#549f' lw 0.1
set object 2792 polygon from \
  -0.801351, 58.12 to \
  -0.03, 58.12 to \
  -0.03, 30.1626 to \
  -0.801351, 30.1626 to \
  -0.801351, 58.12 front fs empty border lc rgb '#549f' lw 0.1
set object 2793 polygon from \
  -0.750932, 58.1425 to \
  -0.03, 58.1425 to \
  -0.03, 30.1751 to \
  -0.750932, 30.1751 to \
  -0.750932, 58.1425 front fs empty border lc rgb '#549f' lw 0.1
set object 2794 polygon from \
  -0.713905, 58.165 to \
  -0.03, 58.165 to \
  -0.03, 30.1875 to \
  -0.713905, 30.1875 to \
  -0.713905, 58.165 front fs empty border lc rgb '#549f' lw 0.1
set object 2795 polygon from \
  -0.732805, 58.1875 to \
  -0.03, 58.1875 to \
  -0.03, 30.2 to \
  -0.732805, 30.2 to \
  -0.732805, 58.1875 front fs empty border lc rgb '#549f' lw 0.1
set object 2796 polygon from \
  -0.78913, 58.21 to \
  -0.03, 58.21 to \
  -0.03, 30.2125 to \
  -0.78913, 30.2125 to \
  -0.78913, 58.21 front fs empty border lc rgb '#549f' lw 0.1
set object 2797 polygon from \
  -0.845254, 58.2325 to \
  -0.03, 58.2325 to \
  -0.03, 30.225 to \
  -0.845254, 30.225 to \
  -0.845254, 58.2325 front fs empty border lc rgb '#549f' lw 0.1
set object 2798 polygon from \
  -0.901141, 58.255 to \
  -0.03, 58.255 to \
  -0.03, 30.2375 to \
  -0.901141, 30.2375 to \
  -0.901141, 58.255 front fs empty border lc rgb '#549f' lw 0.1
set object 2799 polygon from \
  -0.956766, 58.2775 to \
  -0.03, 58.2775 to \
  -0.03, 30.25 to \
  -0.956766, 30.25 to \
  -0.956766, 58.2775 front fs empty border lc rgb '#549f' lw 0.1
set object 2800 polygon from \
  -1.01211, 58.3 to \
  -0.03, 58.3 to \
  -0.03, 30.2625 to \
  -1.01211, 30.2625 to \
  -1.01211, 58.3 front fs empty border lc rgb '#549f' lw 0.1
set object 2801 polygon from \
  -1.06714, 58.3225 to \
  -0.03, 58.3225 to \
  -0.03, 30.275 to \
  -1.06714, 30.275 to \
  -1.06714, 58.3225 front fs empty border lc rgb '#549f' lw 0.1
set object 2802 polygon from \
  -1.12185, 58.345 to \
  -0.03, 58.345 to \
  -0.03, 30.2875 to \
  -1.12185, 30.2875 to \
  -1.12185, 58.345 front fs empty border lc rgb '#549f' lw 0.1
set object 2803 polygon from \
  -1.17621, 58.3675 to \
  -0.03, 58.3675 to \
  -0.03, 30.3 to \
  -1.17621, 30.3 to \
  -1.17621, 58.3675 front fs empty border lc rgb '#549f' lw 0.1
set object 2804 polygon from \
  -1.23019, 58.39 to \
  -0.03, 58.39 to \
  -0.03, 30.3125 to \
  -1.23019, 30.3125 to \
  -1.23019, 58.39 front fs empty border lc rgb '#549f' lw 0.1
set object 2805 polygon from \
  -1.28378, 58.4125 to \
  -0.03, 58.4125 to \
  -0.03, 30.325 to \
  -1.28378, 30.325 to \
  -1.28378, 58.4125 front fs empty border lc rgb '#549f' lw 0.1
set object 2806 polygon from \
  -1.33696, 58.435 to \
  -0.03, 58.435 to \
  -0.03, 30.3375 to \
  -1.33696, 30.3375 to \
  -1.33696, 58.435 front fs empty border lc rgb '#549f' lw 0.1
set object 2807 polygon from \
  -1.38969, 58.4575 to \
  -0.03, 58.4575 to \
  -0.03, 30.35 to \
  -1.38969, 30.35 to \
  -1.38969, 58.4575 front fs empty border lc rgb '#549f' lw 0.1
set object 2808 polygon from \
  -1.44197, 58.48 to \
  -0.03, 58.48 to \
  -0.03, 30.3625 to \
  -1.44197, 30.3625 to \
  -1.44197, 58.48 front fs empty border lc rgb '#549f' lw 0.1
set object 2809 polygon from \
  -1.49376, 58.5026 to \
  -0.03, 58.5026 to \
  -0.03, 30.375 to \
  -1.49376, 30.375 to \
  -1.49376, 58.5026 front fs empty border lc rgb '#549f' lw 0.1
set object 2810 polygon from \
  -1.54505, 58.5251 to \
  -0.03, 58.5251 to \
  -0.03, 30.3875 to \
  -1.54505, 30.3875 to \
  -1.54505, 58.5251 front fs empty border lc rgb '#549f' lw 0.1
set object 2811 polygon from \
  -1.59583, 58.5476 to \
  -0.03, 58.5476 to \
  -0.03, 30.4 to \
  -1.59583, 30.4 to \
  -1.59583, 58.5476 front fs empty border lc rgb '#549f' lw 0.1
set object 2812 polygon from \
  -1.64605, 58.5701 to \
  -0.03, 58.5701 to \
  -0.03, 30.4125 to \
  -1.64605, 30.4125 to \
  -1.64605, 58.5701 front fs empty border lc rgb '#549f' lw 0.1
set object 2813 polygon from \
  -1.69572, 58.5926 to \
  -0.03, 58.5926 to \
  -0.03, 30.4251 to \
  -1.69572, 30.4251 to \
  -1.69572, 58.5926 front fs empty border lc rgb '#549f' lw 0.1
set object 2814 polygon from \
  -1.7448, 58.6151 to \
  -0.03, 58.6151 to \
  -0.03, 30.4376 to \
  -1.7448, 30.4376 to \
  -1.7448, 58.6151 front fs empty border lc rgb '#549f' lw 0.1
set object 2815 polygon from \
  -1.79328, 58.6376 to \
  -0.03, 58.6376 to \
  -0.03, 30.4501 to \
  -1.79328, 30.4501 to \
  -1.79328, 58.6376 front fs empty border lc rgb '#549f' lw 0.1
set object 2816 polygon from \
  -1.84113, 58.6602 to \
  -0.03, 58.6602 to \
  -0.03, 30.4626 to \
  -1.84113, 30.4626 to \
  -1.84113, 58.6602 front fs empty border lc rgb '#549f' lw 0.1
set object 2817 polygon from \
  -1.88834, 58.6827 to \
  -0.03, 58.6827 to \
  -0.03, 30.4751 to \
  -1.88834, 30.4751 to \
  -1.88834, 58.6827 front fs empty border lc rgb '#549f' lw 0.1
set object 2818 polygon from \
  -1.9349, 58.7052 to \
  -0.03, 58.7052 to \
  -0.03, 30.4876 to \
  -1.9349, 30.4876 to \
  -1.9349, 58.7052 front fs empty border lc rgb '#549f' lw 0.1
set object 2819 polygon from \
  -1.98077, 58.7277 to \
  -0.03, 58.7277 to \
  -0.03, 30.5002 to \
  -1.98077, 30.5002 to \
  -1.98077, 58.7277 front fs empty border lc rgb '#549f' lw 0.1
set object 2820 polygon from \
  -2.02594, 58.7503 to \
  -0.03, 58.7503 to \
  -0.03, 30.5127 to \
  -2.02594, 30.5127 to \
  -2.02594, 58.7503 front fs empty border lc rgb '#549f' lw 0.1
set object 2821 polygon from \
  -2.0704, 58.7728 to \
  -0.03, 58.7728 to \
  -0.03, 30.5252 to \
  -2.0704, 30.5252 to \
  -2.0704, 58.7728 front fs empty border lc rgb '#549f' lw 0.1
set object 2822 polygon from \
  -2.11413, 58.7953 to \
  -0.03, 58.7953 to \
  -0.03, 30.5377 to \
  -2.11413, 30.5377 to \
  -2.11413, 58.7953 front fs empty border lc rgb '#549f' lw 0.1
set object 2823 polygon from \
  -2.1571, 58.8178 to \
  -0.03, 58.8178 to \
  -0.03, 30.5502 to \
  -2.1571, 30.5502 to \
  -2.1571, 58.8178 front fs empty border lc rgb '#549f' lw 0.1
set object 2824 polygon from \
  -2.19931, 58.8404 to \
  -0.03, 58.8404 to \
  -0.03, 30.5628 to \
  -2.19931, 30.5628 to \
  -2.19931, 58.8404 front fs empty border lc rgb '#549f' lw 0.1
set object 2825 polygon from \
  -2.24074, 58.8629 to \
  -0.03, 58.8629 to \
  -0.03, 30.5753 to \
  -2.24074, 30.5753 to \
  -2.24074, 58.8629 front fs empty border lc rgb '#549f' lw 0.1
set object 2826 polygon from \
  -2.28136, 58.8854 to \
  -0.03, 58.8854 to \
  -0.03, 30.5878 to \
  -2.28136, 30.5878 to \
  -2.28136, 58.8854 front fs empty border lc rgb '#549f' lw 0.1
set object 2827 polygon from \
  -2.32117, 58.908 to \
  -0.03, 58.908 to \
  -0.03, 30.6004 to \
  -2.32117, 30.6004 to \
  -2.32117, 58.908 front fs empty border lc rgb '#549f' lw 0.1
set object 2828 polygon from \
  -2.36014, 58.9305 to \
  -0.03, 58.9305 to \
  -0.03, 30.6129 to \
  -2.36014, 30.6129 to \
  -2.36014, 58.9305 front fs empty border lc rgb '#549f' lw 0.1
set object 2829 polygon from \
  -2.39827, 58.953 to \
  -0.03, 58.953 to \
  -0.03, 30.6254 to \
  -2.39827, 30.6254 to \
  -2.39827, 58.953 front fs empty border lc rgb '#549f' lw 0.1
set object 2830 polygon from \
  -2.43554, 58.9756 to \
  -0.03, 58.9756 to \
  -0.03, 30.638 to \
  -2.43554, 30.638 to \
  -2.43554, 58.9756 front fs empty border lc rgb '#549f' lw 0.1
set object 2831 polygon from \
  -2.47193, 58.9981 to \
  -0.03, 58.9981 to \
  -0.03, 30.6505 to \
  -2.47193, 30.6505 to \
  -2.47193, 58.9981 front fs empty border lc rgb '#549f' lw 0.1
set object 2832 polygon from \
  -2.50743, 59.0206 to \
  -0.03, 59.0206 to \
  -0.03, 30.663 to \
  -2.50743, 30.663 to \
  -2.50743, 59.0206 front fs empty border lc rgb '#549f' lw 0.1
set object 2833 polygon from \
  -2.54203, 59.0432 to \
  -0.03, 59.0432 to \
  -0.03, 30.6756 to \
  -2.54203, 30.6756 to \
  -2.54203, 59.0432 front fs empty border lc rgb '#549f' lw 0.1
set object 2834 polygon from \
  -2.57572, 59.0657 to \
  -0.03, 59.0657 to \
  -0.03, 30.6881 to \
  -2.57572, 30.6881 to \
  -2.57572, 59.0657 front fs empty border lc rgb '#549f' lw 0.1
set object 2835 polygon from \
  -2.60848, 59.0883 to \
  -0.03, 59.0883 to \
  -0.03, 30.7006 to \
  -2.60848, 30.7006 to \
  -2.60848, 59.0883 front fs empty border lc rgb '#549f' lw 0.1
set object 2836 polygon from \
  -2.64029, 59.1108 to \
  -0.03, 59.1108 to \
  -0.03, 30.7132 to \
  -2.64029, 30.7132 to \
  -2.64029, 59.1108 front fs empty border lc rgb '#549f' lw 0.1
set object 2837 polygon from \
  -2.67116, 59.1334 to \
  -0.03, 59.1334 to \
  -0.03, 30.7257 to \
  -2.67116, 30.7257 to \
  -2.67116, 59.1334 front fs empty border lc rgb '#549f' lw 0.1
set object 2838 polygon from \
  -2.70107, 59.1559 to \
  -0.03, 59.1559 to \
  -0.03, 30.7383 to \
  -2.70107, 30.7383 to \
  -2.70107, 59.1559 front fs empty border lc rgb '#549f' lw 0.1
set object 2839 polygon from \
  -2.73, 59.1785 to \
  -0.03, 59.1785 to \
  -0.03, 30.7508 to \
  -2.73, 30.7508 to \
  -2.73, 59.1785 front fs empty border lc rgb '#549f' lw 0.1
set object 2840 polygon from \
  -2.75794, 59.201 to \
  -0.03, 59.201 to \
  -0.03, 30.7634 to \
  -2.75794, 30.7634 to \
  -2.75794, 59.201 front fs empty border lc rgb '#549f' lw 0.1
set object 2841 polygon from \
  -2.7849, 59.2236 to \
  -0.03, 59.2236 to \
  -0.03, 30.7759 to \
  -2.7849, 30.7759 to \
  -2.7849, 59.2236 front fs empty border lc rgb '#549f' lw 0.1
set object 2842 polygon from \
  -2.81085, 59.2461 to \
  -0.03, 59.2461 to \
  -0.03, 30.7884 to \
  -2.81085, 30.7884 to \
  -2.81085, 59.2461 front fs empty border lc rgb '#549f' lw 0.1
set object 2843 polygon from \
  -2.83579, 59.2687 to \
  -0.03, 59.2687 to \
  -0.03, 30.801 to \
  -2.83579, 30.801 to \
  -2.83579, 59.2687 front fs empty border lc rgb '#549f' lw 0.1
set object 2844 polygon from \
  -2.85972, 59.2912 to \
  -0.03, 59.2912 to \
  -0.03, 30.8135 to \
  -2.85972, 30.8135 to \
  -2.85972, 59.2912 front fs empty border lc rgb '#549f' lw 0.1
set object 2845 polygon from \
  -2.88261, 59.3138 to \
  -0.03, 59.3138 to \
  -0.03, 30.8261 to \
  -2.88261, 30.8261 to \
  -2.88261, 59.3138 front fs empty border lc rgb '#549f' lw 0.1
set object 2846 polygon from \
  -2.90448, 59.3363 to \
  -0.03, 59.3363 to \
  -0.03, 30.8387 to \
  -2.90448, 30.8387 to \
  -2.90448, 59.3363 front fs empty border lc rgb '#549f' lw 0.1
set object 2847 polygon from \
  -2.9253, 59.3589 to \
  -0.03, 59.3589 to \
  -0.03, 30.8512 to \
  -2.9253, 30.8512 to \
  -2.9253, 59.3589 front fs empty border lc rgb '#549f' lw 0.1
set object 2848 polygon from \
  -2.94507, 59.3814 to \
  -0.03, 59.3814 to \
  -0.03, 30.8638 to \
  -2.94507, 30.8638 to \
  -2.94507, 59.3814 front fs empty border lc rgb '#549f' lw 0.1
set object 2849 polygon from \
  -2.96379, 59.404 to \
  -0.03, 59.404 to \
  -0.03, 30.8763 to \
  -2.96379, 30.8763 to \
  -2.96379, 59.404 front fs empty border lc rgb '#549f' lw 0.1
set object 2850 polygon from \
  -2.98146, 59.4266 to \
  -0.03, 59.4266 to \
  -0.03, 30.8889 to \
  -2.98146, 30.8889 to \
  -2.98146, 59.4266 front fs empty border lc rgb '#549f' lw 0.1
set object 2851 polygon from \
  -2.99806, 59.4491 to \
  -0.03, 59.4491 to \
  -0.03, 30.9014 to \
  -2.99806, 30.9014 to \
  -2.99806, 59.4491 front fs empty border lc rgb '#549f' lw 0.1
set object 2852 polygon from \
  -3.0162, 59.4717 to \
  -0.03, 59.4717 to \
  -0.03, 30.914 to \
  -3.0162, 30.914 to \
  -3.0162, 59.4717 front fs empty border lc rgb '#549f' lw 0.1
set object 2853 polygon from \
  -3.03574, 59.4943 to \
  -0.03, 59.4943 to \
  -0.03, 30.9266 to \
  -3.03574, 30.9266 to \
  -3.03574, 59.4943 front fs empty border lc rgb '#549f' lw 0.1
set object 2854 polygon from \
  -3.05422, 59.5168 to \
  -0.03, 59.5168 to \
  -0.03, 30.9391 to \
  -3.05422, 30.9391 to \
  -3.05422, 59.5168 front fs empty border lc rgb '#549f' lw 0.1
set object 2855 polygon from \
  -3.07164, 59.5394 to \
  -0.03, 59.5394 to \
  -0.03, 30.9517 to \
  -3.07164, 30.9517 to \
  -3.07164, 59.5394 front fs empty border lc rgb '#549f' lw 0.1
set object 2856 polygon from \
  -3.08799, 59.562 to \
  -0.03, 59.562 to \
  -0.03, 30.9643 to \
  -3.08799, 30.9643 to \
  -3.08799, 59.562 front fs empty border lc rgb '#549f' lw 0.1
set object 2857 polygon from \
  -3.10327, 59.5845 to \
  -0.03, 59.5845 to \
  -0.03, 30.9768 to \
  -3.10327, 30.9768 to \
  -3.10327, 59.5845 front fs empty border lc rgb '#549f' lw 0.1
set object 2858 polygon from \
  -3.11746, 59.6071 to \
  -0.03, 59.6071 to \
  -0.03, 30.9894 to \
  -3.11746, 30.9894 to \
  -3.11746, 59.6071 front fs empty border lc rgb '#549f' lw 0.1
set object 2859 polygon from \
  -3.13057, 59.6297 to \
  -0.03, 59.6297 to \
  -0.03, 31.002 to \
  -3.13057, 31.002 to \
  -3.13057, 59.6297 front fs empty border lc rgb '#549f' lw 0.1
set object 2860 polygon from \
  -3.1426, 59.6523 to \
  -0.03, 59.6523 to \
  -0.03, 31.0145 to \
  -3.1426, 31.0145 to \
  -3.1426, 59.6523 front fs empty border lc rgb '#549f' lw 0.1
set object 2861 polygon from \
  -3.15353, 59.6748 to \
  -0.03, 59.6748 to \
  -0.03, 31.0271 to \
  -3.15353, 31.0271 to \
  -3.15353, 59.6748 front fs empty border lc rgb '#549f' lw 0.1
set object 2862 polygon from \
  -3.16337, 59.6974 to \
  -0.03, 59.6974 to \
  -0.03, 31.0397 to \
  -3.16337, 31.0397 to \
  -3.16337, 59.6974 front fs empty border lc rgb '#549f' lw 0.1
set object 2863 polygon from \
  -3.17213, 59.72 to \
  -0.03, 59.72 to \
  -0.03, 31.0522 to \
  -3.17213, 31.0522 to \
  -3.17213, 59.72 front fs empty border lc rgb '#549f' lw 0.1
set object 2864 polygon from \
  -3.17978, 59.7426 to \
  -0.03, 59.7426 to \
  -0.03, 31.0648 to \
  -3.17978, 31.0648 to \
  -3.17978, 59.7426 front fs empty border lc rgb '#549f' lw 0.1
set object 2865 polygon from \
  -3.18634, 59.7651 to \
  -0.03, 59.7651 to \
  -0.03, 31.0774 to \
  -3.18634, 31.0774 to \
  -3.18634, 59.7651 front fs empty border lc rgb '#549f' lw 0.1
set object 2866 polygon from \
  -3.19181, 59.7877 to \
  -0.03, 59.7877 to \
  -0.03, 31.09 to \
  -3.19181, 31.09 to \
  -3.19181, 59.7877 front fs empty border lc rgb '#549f' lw 0.1
set object 2867 polygon from \
  -3.19618, 59.8103 to \
  -0.03, 59.8103 to \
  -0.03, 31.1026 to \
  -3.19618, 31.1026 to \
  -3.19618, 59.8103 front fs empty border lc rgb '#549f' lw 0.1
set object 2868 polygon from \
  -3.19946, 59.8329 to \
  -0.03, 59.8329 to \
  -0.03, 31.1151 to \
  -3.19946, 31.1151 to \
  -3.19946, 59.8329 front fs empty border lc rgb '#549f' lw 0.1
set object 2869 polygon from \
  -3.20252, 59.8555 to \
  -0.03, 59.8555 to \
  -0.03, 31.1277 to \
  -3.20252, 31.1277 to \
  -3.20252, 59.8555 front fs empty border lc rgb '#549f' lw 0.1
set object 2870 polygon from \
  -3.20455, 59.8781 to \
  -0.03, 59.8781 to \
  -0.03, 31.1403 to \
  -3.20455, 31.1403 to \
  -3.20455, 59.8781 front fs empty border lc rgb '#549f' lw 0.1
set object 2871 polygon from \
  -3.2055, 59.9007 to \
  -0.03, 59.9007 to \
  -0.03, 31.1529 to \
  -3.2055, 31.1529 to \
  -3.2055, 59.9007 front fs empty border lc rgb '#549f' lw 0.1
set object 2872 polygon from \
  -3.2055, 59.9232 to \
  -0.03, 59.9232 to \
  -0.03, 31.1655 to \
  -3.2055, 31.1655 to \
  -3.2055, 59.9232 front fs empty border lc rgb '#549f' lw 0.1
set object 2873 polygon from \
  -3.20536, 59.9458 to \
  -0.03, 59.9458 to \
  -0.03, 31.1781 to \
  -3.20536, 31.1781 to \
  -3.20536, 59.9458 front fs empty border lc rgb '#549f' lw 0.1
set object 2874 polygon from \
  -3.20414, 59.9684 to \
  -0.03, 59.9684 to \
  -0.03, 31.1906 to \
  -3.20414, 31.1906 to \
  -3.20414, 59.9684 front fs empty border lc rgb '#549f' lw 0.1
set object 2875 polygon from \
  -3.20184, 59.991 to \
  -0.03, 59.991 to \
  -0.03, 31.2032 to \
  -3.20184, 31.2032 to \
  -3.20184, 59.991 front fs empty border lc rgb '#549f' lw 0.1
set object 2876 polygon from \
  -3.19847, 60.0136 to \
  -0.03, 60.0136 to \
  -0.03, 31.2158 to \
  -3.19847, 31.2158 to \
  -3.19847, 60.0136 front fs empty border lc rgb '#549f' lw 0.1
set object 2877 polygon from \
  -3.19404, 60.0362 to \
  -0.03, 60.0362 to \
  -0.03, 31.2284 to \
  -3.19404, 31.2284 to \
  -3.19404, 60.0362 front fs empty border lc rgb '#549f' lw 0.1
set object 2878 polygon from \
  -3.18854, 60.0588 to \
  -0.03, 60.0588 to \
  -0.03, 31.241 to \
  -3.18854, 31.241 to \
  -3.18854, 60.0588 front fs empty border lc rgb '#549f' lw 0.1
set object 2879 polygon from \
  -3.18199, 60.0814 to \
  -0.03, 60.0814 to \
  -0.03, 31.2536 to \
  -3.18199, 31.2536 to \
  -3.18199, 60.0814 front fs empty border lc rgb '#549f' lw 0.1
set object 2880 polygon from \
  -3.17439, 60.104 to \
  -0.03, 60.104 to \
  -0.03, 31.2662 to \
  -3.17439, 31.2662 to \
  -3.17439, 60.104 front fs empty border lc rgb '#549f' lw 0.1
set object 2881 polygon from \
  -3.16574, 60.1266 to \
  -0.03, 60.1266 to \
  -0.03, 31.2788 to \
  -3.16574, 31.2788 to \
  -3.16574, 60.1266 front fs empty border lc rgb '#549f' lw 0.1
set object 2882 polygon from \
  -3.15606, 60.1492 to \
  -0.03, 60.1492 to \
  -0.03, 31.2914 to \
  -3.15606, 31.2914 to \
  -3.15606, 60.1492 front fs empty border lc rgb '#549f' lw 0.1
set object 2883 polygon from \
  -3.14535, 60.1718 to \
  -0.03, 60.1718 to \
  -0.03, 31.304 to \
  -3.14535, 31.304 to \
  -3.14535, 60.1718 front fs empty border lc rgb '#549f' lw 0.1
set object 2884 polygon from \
  -3.13362, 60.1944 to \
  -0.03, 60.1944 to \
  -0.03, 31.3166 to \
  -3.13362, 31.3166 to \
  -3.13362, 60.1944 front fs empty border lc rgb '#549f' lw 0.1
set object 2885 polygon from \
  -3.12087, 60.217 to \
  -0.03, 60.217 to \
  -0.03, 31.3292 to \
  -3.12087, 31.3292 to \
  -3.12087, 60.217 front fs empty border lc rgb '#549f' lw 0.1
set object 2886 polygon from \
  -3.10712, 60.2396 to \
  -0.03, 60.2396 to \
  -0.03, 31.3418 to \
  -3.10712, 31.3418 to \
  -3.10712, 60.2396 front fs empty border lc rgb '#549f' lw 0.1
set object 2887 polygon from \
  -3.09238, 60.2622 to \
  -0.03, 60.2622 to \
  -0.03, 31.3544 to \
  -3.09238, 31.3544 to \
  -3.09238, 60.2622 front fs empty border lc rgb '#549f' lw 0.1
set object 2888 polygon from \
  -3.07666, 60.2848 to \
  -0.03, 60.2848 to \
  -0.03, 31.367 to \
  -3.07666, 31.367 to \
  -3.07666, 60.2848 front fs empty border lc rgb '#549f' lw 0.1
set object 2889 polygon from \
  -3.05996, 60.3075 to \
  -0.03, 60.3075 to \
  -0.03, 31.3796 to \
  -3.05996, 31.3796 to \
  -3.05996, 60.3075 front fs empty border lc rgb '#549f' lw 0.1
set object 2890 polygon from \
  -3.0423, 60.3301 to \
  -0.03, 60.3301 to \
  -0.03, 31.3922 to \
  -3.0423, 31.3922 to \
  -3.0423, 60.3301 front fs empty border lc rgb '#549f' lw 0.1
set object 2891 polygon from \
  -3.02368, 60.3527 to \
  -0.03, 60.3527 to \
  -0.03, 31.4048 to \
  -3.02368, 31.4048 to \
  -3.02368, 60.3527 front fs empty border lc rgb '#549f' lw 0.1
set object 2892 polygon from \
  -3.00413, 60.3753 to \
  -0.03, 60.3753 to \
  -0.03, 31.4174 to \
  -3.00413, 31.4174 to \
  -3.00413, 60.3753 front fs empty border lc rgb '#549f' lw 0.1
set object 2893 polygon from \
  -2.98365, 60.3979 to \
  -0.03, 60.3979 to \
  -0.03, 31.4301 to \
  -2.98365, 31.4301 to \
  -2.98365, 60.3979 front fs empty border lc rgb '#549f' lw 0.1
set object 2894 polygon from \
  -2.96225, 60.4205 to \
  -0.03, 60.4205 to \
  -0.03, 31.4427 to \
  -2.96225, 31.4427 to \
  -2.96225, 60.4205 front fs empty border lc rgb '#549f' lw 0.1
set object 2895 polygon from \
  -2.93995, 60.4431 to \
  -0.03, 60.4431 to \
  -0.03, 31.4553 to \
  -2.93995, 31.4553 to \
  -2.93995, 60.4431 front fs empty border lc rgb '#549f' lw 0.1
set object 2896 polygon from \
  -2.91675, 60.4658 to \
  -0.03, 60.4658 to \
  -0.03, 31.4679 to \
  -2.91675, 31.4679 to \
  -2.91675, 60.4658 front fs empty border lc rgb '#549f' lw 0.1
set object 2897 polygon from \
  -2.89268, 60.4884 to \
  -0.03, 60.4884 to \
  -0.03, 31.4805 to \
  -2.89268, 31.4805 to \
  -2.89268, 60.4884 front fs empty border lc rgb '#549f' lw 0.1
set object 2898 polygon from \
  -2.86775, 60.511 to \
  -0.03, 60.511 to \
  -0.03, 31.4931 to \
  -2.86775, 31.4931 to \
  -2.86775, 60.511 front fs empty border lc rgb '#549f' lw 0.1
set object 2899 polygon from \
  -2.84196, 60.5336 to \
  -0.03, 60.5336 to \
  -0.03, 31.5058 to \
  -2.84196, 31.5058 to \
  -2.84196, 60.5336 front fs empty border lc rgb '#549f' lw 0.1
set object 2900 polygon from \
  -2.8256, 60.5563 to \
  -0.03, 60.5563 to \
  -0.03, 31.5184 to \
  -2.8256, 31.5184 to \
  -2.8256, 60.5563 front fs empty border lc rgb '#549f' lw 0.1
set object 2901 polygon from \
  -2.81509, 60.5789 to \
  -0.03, 60.5789 to \
  -0.03, 31.531 to \
  -2.81509, 31.531 to \
  -2.81509, 60.5789 front fs empty border lc rgb '#549f' lw 0.1
set object 2902 polygon from \
  -2.80377, 60.6015 to \
  -0.03, 60.6015 to \
  -0.03, 31.5436 to \
  -2.80377, 31.5436 to \
  -2.80377, 60.6015 front fs empty border lc rgb '#549f' lw 0.1
set object 2903 polygon from \
  -2.79167, 60.6241 to \
  -0.03, 60.6241 to \
  -0.03, 31.5562 to \
  -2.79167, 31.5562 to \
  -2.79167, 60.6241 front fs empty border lc rgb '#549f' lw 0.1
set object 2904 polygon from \
  -2.77878, 60.6468 to \
  -0.03, 60.6468 to \
  -0.03, 31.5689 to \
  -2.77878, 31.5689 to \
  -2.77878, 60.6468 front fs empty border lc rgb '#549f' lw 0.1
set object 2905 polygon from \
  -2.76512, 60.6694 to \
  -0.03, 60.6694 to \
  -0.03, 31.5815 to \
  -2.76512, 31.5815 to \
  -2.76512, 60.6694 front fs empty border lc rgb '#549f' lw 0.1
set object 2906 polygon from \
  -2.7507, 60.692 to \
  -0.03, 60.692 to \
  -0.03, 31.5941 to \
  -2.7507, 31.5941 to \
  -2.7507, 60.692 front fs empty border lc rgb '#549f' lw 0.1
set object 2907 polygon from \
  -2.73554, 60.7147 to \
  -0.03, 60.7147 to \
  -0.03, 31.6068 to \
  -2.73554, 31.6068 to \
  -2.73554, 60.7147 front fs empty border lc rgb '#549f' lw 0.1
set object 2908 polygon from \
  -2.71965, 60.7373 to \
  -0.03, 60.7373 to \
  -0.03, 31.6194 to \
  -2.71965, 31.6194 to \
  -2.71965, 60.7373 front fs empty border lc rgb '#549f' lw 0.1
set object 2909 polygon from \
  -2.70304, 60.7599 to \
  -0.03, 60.7599 to \
  -0.03, 31.632 to \
  -2.70304, 31.632 to \
  -2.70304, 60.7599 front fs empty border lc rgb '#549f' lw 0.1
set object 2910 polygon from \
  -2.68573, 60.7826 to \
  -0.03, 60.7826 to \
  -0.03, 31.6447 to \
  -2.68573, 31.6447 to \
  -2.68573, 60.7826 front fs empty border lc rgb '#549f' lw 0.1
set object 2911 polygon from \
  -2.66773, 60.8052 to \
  -0.03, 60.8052 to \
  -0.03, 31.6573 to \
  -2.66773, 31.6573 to \
  -2.66773, 60.8052 front fs empty border lc rgb '#549f' lw 0.1
set object 2912 polygon from \
  -2.64905, 60.8278 to \
  -0.03, 60.8278 to \
  -0.03, 31.6699 to \
  -2.64905, 31.6699 to \
  -2.64905, 60.8278 front fs empty border lc rgb '#549f' lw 0.1
set object 2913 polygon from \
  -2.6297, 60.8505 to \
  -0.03, 60.8505 to \
  -0.03, 31.6826 to \
  -2.6297, 31.6826 to \
  -2.6297, 60.8505 front fs empty border lc rgb '#549f' lw 0.1
set object 2914 polygon from \
  -2.60971, 60.8731 to \
  -0.03, 60.8731 to \
  -0.03, 31.6952 to \
  -2.60971, 31.6952 to \
  -2.60971, 60.8731 front fs empty border lc rgb '#549f' lw 0.1
set object 2915 polygon from \
  -2.58909, 60.8958 to \
  -0.03, 60.8958 to \
  -0.03, 31.7078 to \
  -2.58909, 31.7078 to \
  -2.58909, 60.8958 front fs empty border lc rgb '#549f' lw 0.1
set object 2916 polygon from \
  -2.56785, 60.9184 to \
  -0.03, 60.9184 to \
  -0.03, 31.7205 to \
  -2.56785, 31.7205 to \
  -2.56785, 60.9184 front fs empty border lc rgb '#549f' lw 0.1
set object 2917 polygon from \
  -2.546, 60.9411 to \
  -0.03, 60.9411 to \
  -0.03, 31.7331 to \
  -2.546, 31.7331 to \
  -2.546, 60.9411 front fs empty border lc rgb '#549f' lw 0.1
set object 2918 polygon from \
  -2.52356, 60.9637 to \
  -0.03, 60.9637 to \
  -0.03, 31.7458 to \
  -2.52356, 31.7458 to \
  -2.52356, 60.9637 front fs empty border lc rgb '#549f' lw 0.1
set object 2919 polygon from \
  -2.50055, 60.9864 to \
  -0.03, 60.9864 to \
  -0.03, 31.7584 to \
  -2.50055, 31.7584 to \
  -2.50055, 60.9864 front fs empty border lc rgb '#549f' lw 0.1
set object 2920 polygon from \
  -2.47698, 61.009 to \
  -0.03, 61.009 to \
  -0.03, 31.7711 to \
  -2.47698, 31.7711 to \
  -2.47698, 61.009 front fs empty border lc rgb '#549f' lw 0.1
set object 2921 polygon from \
  -2.45286, 61.0317 to \
  -0.03, 61.0317 to \
  -0.03, 31.7837 to \
  -2.45286, 31.7837 to \
  -2.45286, 61.0317 front fs empty border lc rgb '#549f' lw 0.1
set object 2922 polygon from \
  -2.42822, 61.0543 to \
  -0.03, 61.0543 to \
  -0.03, 31.7963 to \
  -2.42822, 31.7963 to \
  -2.42822, 61.0543 front fs empty border lc rgb '#549f' lw 0.1
set object 2923 polygon from \
  -2.40306, 61.077 to \
  -0.03, 61.077 to \
  -0.03, 31.809 to \
  -2.40306, 31.809 to \
  -2.40306, 61.077 front fs empty border lc rgb '#549f' lw 0.1
set object 2924 polygon from \
  -2.40546, 61.0996 to \
  -0.03, 61.0996 to \
  -0.03, 31.8216 to \
  -2.40546, 31.8216 to \
  -2.40546, 61.0996 front fs empty border lc rgb '#549f' lw 0.1
set object 2925 polygon from \
  -2.42427, 61.1223 to \
  -0.03, 61.1223 to \
  -0.03, 31.8343 to \
  -2.42427, 31.8343 to \
  -2.42427, 61.1223 front fs empty border lc rgb '#549f' lw 0.1
set object 2926 polygon from \
  -2.44236, 61.1449 to \
  -0.03, 61.1449 to \
  -0.03, 31.847 to \
  -2.44236, 31.847 to \
  -2.44236, 61.1449 front fs empty border lc rgb '#549f' lw 0.1
set object 2927 polygon from \
  -2.45979, 61.1676 to \
  -0.03, 61.1676 to \
  -0.03, 31.8596 to \
  -2.45979, 31.8596 to \
  -2.45979, 61.1676 front fs empty border lc rgb '#549f' lw 0.1
set object 2928 polygon from \
  -2.47673, 61.1902 to \
  -0.03, 61.1902 to \
  -0.03, 31.8723 to \
  -2.47673, 31.8723 to \
  -2.47673, 61.1902 front fs empty border lc rgb '#549f' lw 0.1
set object 2929 polygon from \
  -2.4929, 61.2129 to \
  -0.03, 61.2129 to \
  -0.03, 31.8849 to \
  -2.4929, 31.8849 to \
  -2.4929, 61.2129 front fs empty border lc rgb '#549f' lw 0.1
set object 2930 polygon from \
  -2.50829, 61.2356 to \
  -0.03, 61.2356 to \
  -0.03, 31.8976 to \
  -2.50829, 31.8976 to \
  -2.50829, 61.2356 front fs empty border lc rgb '#549f' lw 0.1
set object 2931 polygon from \
  -2.52289, 61.2582 to \
  -0.03, 61.2582 to \
  -0.03, 31.9102 to \
  -2.52289, 31.9102 to \
  -2.52289, 61.2582 front fs empty border lc rgb '#549f' lw 0.1
set object 2932 polygon from \
  -2.53667, 61.2809 to \
  -0.03, 61.2809 to \
  -0.03, 31.9229 to \
  -2.53667, 31.9229 to \
  -2.53667, 61.2809 front fs empty border lc rgb '#549f' lw 0.1
set object 2933 polygon from \
  -2.54964, 61.3036 to \
  -0.03, 61.3036 to \
  -0.03, 31.9356 to \
  -2.54964, 31.9356 to \
  -2.54964, 61.3036 front fs empty border lc rgb '#549f' lw 0.1
set object 2934 polygon from \
  -2.56178, 61.3262 to \
  -0.03, 61.3262 to \
  -0.03, 31.9482 to \
  -2.56178, 31.9482 to \
  -2.56178, 61.3262 front fs empty border lc rgb '#549f' lw 0.1
set object 2935 polygon from \
  -2.57307, 61.3489 to \
  -0.03, 61.3489 to \
  -0.03, 31.9609 to \
  -2.57307, 31.9609 to \
  -2.57307, 61.3489 front fs empty border lc rgb '#549f' lw 0.1
set object 2936 polygon from \
  -2.5835, 61.3716 to \
  -0.03, 61.3716 to \
  -0.03, 31.9736 to \
  -2.5835, 31.9736 to \
  -2.5835, 61.3716 front fs empty border lc rgb '#549f' lw 0.1
set object 2937 polygon from \
  -2.59306, 61.3942 to \
  -0.03, 61.3942 to \
  -0.03, 31.9862 to \
  -2.59306, 31.9862 to \
  -2.59306, 61.3942 front fs empty border lc rgb '#549f' lw 0.1
set object 2938 polygon from \
  -2.60174, 61.4169 to \
  -0.03, 61.4169 to \
  -0.03, 31.9989 to \
  -2.60174, 31.9989 to \
  -2.60174, 61.4169 front fs empty border lc rgb '#549f' lw 0.1
set object 2939 polygon from \
  -2.60953, 61.4396 to \
  -0.03, 61.4396 to \
  -0.03, 32.0116 to \
  -2.60953, 32.0116 to \
  -2.60953, 61.4396 front fs empty border lc rgb '#549f' lw 0.1
set object 2940 polygon from \
  -2.61642, 61.4623 to \
  -0.03, 61.4623 to \
  -0.03, 32.0242 to \
  -2.61642, 32.0242 to \
  -2.61642, 61.4623 front fs empty border lc rgb '#549f' lw 0.1
set object 2941 polygon from \
  -2.62239, 61.4849 to \
  -0.03, 61.4849 to \
  -0.03, 32.0369 to \
  -2.62239, 32.0369 to \
  -2.62239, 61.4849 front fs empty border lc rgb '#549f' lw 0.1
set object 2942 polygon from \
  -2.62745, 61.5076 to \
  -0.03, 61.5076 to \
  -0.03, 32.0496 to \
  -2.62745, 32.0496 to \
  -2.62745, 61.5076 front fs empty border lc rgb '#549f' lw 0.1
set object 2943 polygon from \
  -2.63158, 61.5303 to \
  -0.03, 61.5303 to \
  -0.03, 32.0622 to \
  -2.63158, 32.0622 to \
  -2.63158, 61.5303 front fs empty border lc rgb '#549f' lw 0.1
set object 2944 polygon from \
  -2.63476, 61.553 to \
  -0.03, 61.553 to \
  -0.03, 32.0749 to \
  -2.63476, 32.0749 to \
  -2.63476, 61.553 front fs empty border lc rgb '#549f' lw 0.1
set object 2945 polygon from \
  -2.637, 61.5756 to \
  -0.03, 61.5756 to \
  -0.03, 32.0876 to \
  -2.637, 32.0876 to \
  -2.637, 61.5756 front fs empty border lc rgb '#549f' lw 0.1
set object 2946 polygon from \
  -2.63828, 61.5983 to \
  -0.03, 61.5983 to \
  -0.03, 32.1003 to \
  -2.63828, 32.1003 to \
  -2.63828, 61.5983 front fs empty border lc rgb '#549f' lw 0.1
set object 2947 polygon from \
  -2.63861, 61.621 to \
  -0.03, 61.621 to \
  -0.03, 32.113 to \
  -2.63861, 32.113 to \
  -2.63861, 61.621 front fs empty border lc rgb '#549f' lw 0.1
set object 2948 polygon from \
  -2.63861, 61.6437 to \
  -0.03, 61.6437 to \
  -0.03, 32.1256 to \
  -2.63861, 32.1256 to \
  -2.63861, 61.6437 front fs empty border lc rgb '#549f' lw 0.1
set object 2949 polygon from \
  -2.63796, 61.6664 to \
  -0.03, 61.6664 to \
  -0.03, 32.1383 to \
  -2.63796, 32.1383 to \
  -2.63796, 61.6664 front fs empty border lc rgb '#549f' lw 0.1
set object 2950 polygon from \
  -2.63634, 61.6891 to \
  -0.03, 61.6891 to \
  -0.03, 32.151 to \
  -2.63634, 32.151 to \
  -2.63634, 61.6891 front fs empty border lc rgb '#549f' lw 0.1
set object 2951 polygon from \
  -2.63374, 61.7118 to \
  -0.03, 61.7118 to \
  -0.03, 32.1637 to \
  -2.63374, 32.1637 to \
  -2.63374, 61.7118 front fs empty border lc rgb '#549f' lw 0.1
set object 2952 polygon from \
  -2.63015, 61.7344 to \
  -0.03, 61.7344 to \
  -0.03, 32.1764 to \
  -2.63015, 32.1764 to \
  -2.63015, 61.7344 front fs empty border lc rgb '#549f' lw 0.1
set object 2953 polygon from \
  -2.62557, 61.7571 to \
  -0.03, 61.7571 to \
  -0.03, 32.1891 to \
  -2.62557, 32.1891 to \
  -2.62557, 61.7571 front fs empty border lc rgb '#549f' lw 0.1
set object 2954 polygon from \
  -2.61999, 61.7798 to \
  -0.03, 61.7798 to \
  -0.03, 32.2017 to \
  -2.61999, 32.2017 to \
  -2.61999, 61.7798 front fs empty border lc rgb '#549f' lw 0.1
set object 2955 polygon from \
  -2.61342, 61.8025 to \
  -0.03, 61.8025 to \
  -0.03, 32.2144 to \
  -2.61342, 32.2144 to \
  -2.61342, 61.8025 front fs empty border lc rgb '#549f' lw 0.1
set object 2956 polygon from \
  -2.60584, 61.8252 to \
  -0.03, 61.8252 to \
  -0.03, 32.2271 to \
  -2.60584, 32.2271 to \
  -2.60584, 61.8252 front fs empty border lc rgb '#549f' lw 0.1
set object 2957 polygon from \
  -2.59726, 61.8479 to \
  -0.03, 61.8479 to \
  -0.03, 32.2398 to \
  -2.59726, 32.2398 to \
  -2.59726, 61.8479 front fs empty border lc rgb '#549f' lw 0.1
set object 2958 polygon from \
  -2.58767, 61.8706 to \
  -0.03, 61.8706 to \
  -0.03, 32.2525 to \
  -2.58767, 32.2525 to \
  -2.58767, 61.8706 front fs empty border lc rgb '#549f' lw 0.1
set object 2959 polygon from \
  -2.57707, 61.8933 to \
  -0.03, 61.8933 to \
  -0.03, 32.2652 to \
  -2.57707, 32.2652 to \
  -2.57707, 61.8933 front fs empty border lc rgb '#549f' lw 0.1
set object 2960 polygon from \
  -2.56546, 61.916 to \
  -0.03, 61.916 to \
  -0.03, 32.2779 to \
  -2.56546, 32.2779 to \
  -2.56546, 61.916 front fs empty border lc rgb '#549f' lw 0.1
set object 2961 polygon from \
  -2.55283, 61.9387 to \
  -0.03, 61.9387 to \
  -0.03, 32.2906 to \
  -2.55283, 32.2906 to \
  -2.55283, 61.9387 front fs empty border lc rgb '#549f' lw 0.1
set object 2962 polygon from \
  -2.5392, 61.9614 to \
  -0.03, 61.9614 to \
  -0.03, 32.3033 to \
  -2.5392, 32.3033 to \
  -2.5392, 61.9614 front fs empty border lc rgb '#549f' lw 0.1
set object 2963 polygon from \
  -2.52456, 61.9841 to \
  -0.03, 61.9841 to \
  -0.03, 32.316 to \
  -2.52456, 32.316 to \
  -2.52456, 61.9841 front fs empty border lc rgb '#549f' lw 0.1
set object 2964 polygon from \
  -2.5089, 62.0068 to \
  -0.03, 62.0068 to \
  -0.03, 32.3287 to \
  -2.5089, 32.3287 to \
  -2.5089, 62.0068 front fs empty border lc rgb '#549f' lw 0.1
set object 2965 polygon from \
  -2.49224, 62.0295 to \
  -0.03, 62.0295 to \
  -0.03, 32.3414 to \
  -2.49224, 32.3414 to \
  -2.49224, 62.0295 front fs empty border lc rgb '#549f' lw 0.1
set object 2966 polygon from \
  -2.47457, 62.0522 to \
  -0.03, 62.0522 to \
  -0.03, 32.3541 to \
  -2.47457, 32.3541 to \
  -2.47457, 62.0522 front fs empty border lc rgb '#549f' lw 0.1
set object 2967 polygon from \
  -2.4559, 62.0749 to \
  -0.03, 62.0749 to \
  -0.03, 32.3668 to \
  -2.4559, 32.3668 to \
  -2.4559, 62.0749 front fs empty border lc rgb '#549f' lw 0.1
set object 2968 polygon from \
  -2.43623, 62.0976 to \
  -0.03, 62.0976 to \
  -0.03, 32.3795 to \
  -2.43623, 32.3795 to \
  -2.43623, 62.0976 front fs empty border lc rgb '#549f' lw 0.1
set object 2969 polygon from \
  -2.41556, 62.1204 to \
  -0.03, 62.1204 to \
  -0.03, 32.3922 to \
  -2.41556, 32.3922 to \
  -2.41556, 62.1204 front fs empty border lc rgb '#549f' lw 0.1
set object 2970 polygon from \
  -2.39389, 62.1431 to \
  -0.03, 62.1431 to \
  -0.03, 32.4049 to \
  -2.39389, 32.4049 to \
  -2.39389, 62.1431 front fs empty border lc rgb '#549f' lw 0.1
set object 2971 polygon from \
  -2.37124, 62.1658 to \
  -0.03, 62.1658 to \
  -0.03, 32.4176 to \
  -2.37124, 32.4176 to \
  -2.37124, 62.1658 front fs empty border lc rgb '#549f' lw 0.1
set object 2972 polygon from \
  -2.34761, 62.1885 to \
  -0.03, 62.1885 to \
  -0.03, 32.4303 to \
  -2.34761, 32.4303 to \
  -2.34761, 62.1885 front fs empty border lc rgb '#549f' lw 0.1
set object 2973 polygon from \
  -2.323, 62.2112 to \
  -0.03, 62.2112 to \
  -0.03, 32.4431 to \
  -2.323, 32.4431 to \
  -2.323, 62.2112 front fs empty border lc rgb '#549f' lw 0.1
set object 2974 polygon from \
  -2.29742, 62.2339 to \
  -0.03, 62.2339 to \
  -0.03, 32.4558 to \
  -2.29742, 32.4558 to \
  -2.29742, 62.2339 front fs empty border lc rgb '#549f' lw 0.1
set object 2975 polygon from \
  -2.27087, 62.2566 to \
  -0.03, 62.2566 to \
  -0.03, 32.4685 to \
  -2.27087, 32.4685 to \
  -2.27087, 62.2566 front fs empty border lc rgb '#549f' lw 0.1
set object 2976 polygon from \
  -2.24337, 62.2794 to \
  -0.03, 62.2794 to \
  -0.03, 32.4812 to \
  -2.24337, 32.4812 to \
  -2.24337, 62.2794 front fs empty border lc rgb '#549f' lw 0.1
set object 2977 polygon from \
  -2.21491, 62.3021 to \
  -0.03, 62.3021 to \
  -0.03, 32.4939 to \
  -2.21491, 32.4939 to \
  -2.21491, 62.3021 front fs empty border lc rgb '#549f' lw 0.1
set object 2978 polygon from \
  -2.18552, 62.3248 to \
  -0.03, 62.3248 to \
  -0.03, 32.5066 to \
  -2.18552, 32.5066 to \
  -2.18552, 62.3248 front fs empty border lc rgb '#549f' lw 0.1
set object 2979 polygon from \
  -2.1552, 62.3475 to \
  -0.03, 62.3475 to \
  -0.03, 32.5194 to \
  -2.1552, 32.5194 to \
  -2.1552, 62.3475 front fs empty border lc rgb '#549f' lw 0.1
set object 2980 polygon from \
  -2.13245, 62.3703 to \
  -0.03, 62.3703 to \
  -0.03, 32.5321 to \
  -2.13245, 32.5321 to \
  -2.13245, 62.3703 front fs empty border lc rgb '#549f' lw 0.1
set object 2981 polygon from \
  -2.13067, 62.393 to \
  -0.03, 62.393 to \
  -0.03, 32.5448 to \
  -2.13067, 32.5448 to \
  -2.13067, 62.393 front fs empty border lc rgb '#549f' lw 0.1
set object 2982 polygon from \
  -2.12761, 62.4157 to \
  -0.03, 62.4157 to \
  -0.03, 32.5575 to \
  -2.12761, 32.5575 to \
  -2.12761, 62.4157 front fs empty border lc rgb '#549f' lw 0.1
set object 2983 polygon from \
  -2.12433, 62.4384 to \
  -0.03, 62.4384 to \
  -0.03, 32.5702 to \
  -2.12433, 32.5702 to \
  -2.12433, 62.4384 front fs empty border lc rgb '#549f' lw 0.1
set object 2984 polygon from \
  -2.12146, 62.4612 to \
  -0.03, 62.4612 to \
  -0.03, 32.583 to \
  -2.12146, 32.583 to \
  -2.12146, 62.4612 front fs empty border lc rgb '#549f' lw 0.1
set object 2985 polygon from \
  -2.11734, 62.4839 to \
  -0.03, 62.4839 to \
  -0.03, 32.5957 to \
  -2.11734, 32.5957 to \
  -2.11734, 62.4839 front fs empty border lc rgb '#549f' lw 0.1
set object 2986 polygon from \
  -2.11198, 62.5066 to \
  -0.03, 62.5066 to \
  -0.03, 32.6084 to \
  -2.11198, 32.6084 to \
  -2.11198, 62.5066 front fs empty border lc rgb '#549f' lw 0.1
set object 2987 polygon from \
  -2.1054, 62.5294 to \
  -0.03, 62.5294 to \
  -0.03, 32.6212 to \
  -2.1054, 32.6212 to \
  -2.1054, 62.5294 front fs empty border lc rgb '#549f' lw 0.1
set object 2988 polygon from \
  -2.0976, 62.5521 to \
  -0.03, 62.5521 to \
  -0.03, 32.6339 to \
  -2.0976, 32.6339 to \
  -2.0976, 62.5521 front fs empty border lc rgb '#549f' lw 0.1
set object 2989 polygon from \
  -2.0886, 62.5748 to \
  -0.03, 62.5748 to \
  -0.03, 32.6466 to \
  -2.0886, 32.6466 to \
  -2.0886, 62.5748 front fs empty border lc rgb '#549f' lw 0.1
set object 2990 polygon from \
  -2.0784, 62.5976 to \
  -0.03, 62.5976 to \
  -0.03, 32.6594 to \
  -2.0784, 32.6594 to \
  -2.0784, 62.5976 front fs empty border lc rgb '#549f' lw 0.1
set object 2991 polygon from \
  -2.06701, 62.6203 to \
  -0.03, 62.6203 to \
  -0.03, 32.6721 to \
  -2.06701, 32.6721 to \
  -2.06701, 62.6203 front fs empty border lc rgb '#549f' lw 0.1
set object 2992 polygon from \
  -2.05446, 62.643 to \
  -0.03, 62.643 to \
  -0.03, 32.6848 to \
  -2.05446, 32.6848 to \
  -2.05446, 62.643 front fs empty border lc rgb '#549f' lw 0.1
set object 2993 polygon from \
  -2.04076, 62.6658 to \
  -0.03, 62.6658 to \
  -0.03, 32.6976 to \
  -2.04076, 32.6976 to \
  -2.04076, 62.6658 front fs empty border lc rgb '#549f' lw 0.1
set object 2994 polygon from \
  -2.02591, 62.6885 to \
  -0.03, 62.6885 to \
  -0.03, 32.7103 to \
  -2.02591, 32.7103 to \
  -2.02591, 62.6885 front fs empty border lc rgb '#549f' lw 0.1
set object 2995 polygon from \
  -2.00994, 62.7113 to \
  -0.03, 62.7113 to \
  -0.03, 32.723 to \
  -2.00994, 32.723 to \
  -2.00994, 62.7113 front fs empty border lc rgb '#549f' lw 0.1
set object 2996 polygon from \
  -1.99286, 62.734 to \
  -0.03, 62.734 to \
  -0.03, 32.7358 to \
  -1.99286, 32.7358 to \
  -1.99286, 62.734 front fs empty border lc rgb '#549f' lw 0.1
set object 2997 polygon from \
  -1.97468, 62.7568 to \
  -0.03, 62.7568 to \
  -0.03, 32.7485 to \
  -1.97468, 32.7485 to \
  -1.97468, 62.7568 front fs empty border lc rgb '#549f' lw 0.1
set object 2998 polygon from \
  -1.95544, 62.7795 to \
  -0.03, 62.7795 to \
  -0.03, 32.7613 to \
  -1.95544, 32.7613 to \
  -1.95544, 62.7795 front fs empty border lc rgb '#549f' lw 0.1
set object 2999 polygon from \
  -1.93513, 62.8023 to \
  -0.03, 62.8023 to \
  -0.03, 32.774 to \
  -1.93513, 32.774 to \
  -1.93513, 62.8023 front fs empty border lc rgb '#549f' lw 0.1
set object 3000 polygon from \
  -1.91379, 62.825 to \
  -0.03, 62.825 to \
  -0.03, 32.7868 to \
  -1.91379, 32.7868 to \
  -1.91379, 62.825 front fs empty border lc rgb '#549f' lw 0.1
set object 3001 polygon from \
  -1.89144, 62.8478 to \
  -0.03, 62.8478 to \
  -0.03, 32.7995 to \
  -1.89144, 32.7995 to \
  -1.89144, 62.8478 front fs empty border lc rgb '#549f' lw 0.1
set object 3002 polygon from \
  -1.86808, 62.8705 to \
  -0.03, 62.8705 to \
  -0.03, 32.8122 to \
  -1.86808, 32.8122 to \
  -1.86808, 62.8705 front fs empty border lc rgb '#549f' lw 0.1
set object 3003 polygon from \
  -1.84375, 62.8933 to \
  -0.03, 62.8933 to \
  -0.03, 32.825 to \
  -1.84375, 32.825 to \
  -1.84375, 62.8933 front fs empty border lc rgb '#549f' lw 0.1
set object 3004 polygon from \
  -1.81846, 62.916 to \
  -0.03, 62.916 to \
  -0.03, 32.8377 to \
  -1.81846, 32.8377 to \
  -1.81846, 62.916 front fs empty border lc rgb '#549f' lw 0.1
set object 3005 polygon from \
  -1.79225, 62.9388 to \
  -0.03, 62.9388 to \
  -0.03, 32.8505 to \
  -1.79225, 32.8505 to \
  -1.79225, 62.9388 front fs empty border lc rgb '#549f' lw 0.1
set object 3006 polygon from \
  -1.76512, 62.9615 to \
  -0.03, 62.9615 to \
  -0.03, 32.8633 to \
  -1.76512, 32.8633 to \
  -1.76512, 62.9615 front fs empty border lc rgb '#549f' lw 0.1
set object 3007 polygon from \
  -1.7371, 62.9843 to \
  -0.03, 62.9843 to \
  -0.03, 32.876 to \
  -1.7371, 32.876 to \
  -1.7371, 62.9843 front fs empty border lc rgb '#549f' lw 0.1
set object 3008 polygon from \
  -1.70822, 63.007 to \
  -0.03, 63.007 to \
  -0.03, 32.8888 to \
  -1.70822, 32.8888 to \
  -1.70822, 63.007 front fs empty border lc rgb '#549f' lw 0.1
set object 3009 polygon from \
  -1.67851, 63.0298 to \
  -0.03, 63.0298 to \
  -0.03, 32.9015 to \
  -1.67851, 32.9015 to \
  -1.67851, 63.0298 front fs empty border lc rgb '#549f' lw 0.1
set object 3010 polygon from \
  -1.64798, 63.0526 to \
  -0.03, 63.0526 to \
  -0.03, 32.9143 to \
  -1.64798, 32.9143 to \
  -1.64798, 63.0526 front fs empty border lc rgb '#549f' lw 0.1
set object 3011 polygon from \
  -1.61666, 63.0753 to \
  -0.03, 63.0753 to \
  -0.03, 32.927 to \
  -1.61666, 32.927 to \
  -1.61666, 63.0753 front fs empty border lc rgb '#549f' lw 0.1
set object 3012 polygon from \
  -1.58521, 63.0981 to \
  -0.03, 63.0981 to \
  -0.03, 32.9398 to \
  -1.58521, 32.9398 to \
  -1.58521, 63.0981 front fs empty border lc rgb '#549f' lw 0.1
set object 3013 polygon from \
  -1.55468, 63.1209 to \
  -0.03, 63.1209 to \
  -0.03, 32.9526 to \
  -1.55468, 32.9526 to \
  -1.55468, 63.1209 front fs empty border lc rgb '#549f' lw 0.1
set object 3014 polygon from \
  -1.52336, 63.1436 to \
  -0.03, 63.1436 to \
  -0.03, 32.9653 to \
  -1.52336, 32.9653 to \
  -1.52336, 63.1436 front fs empty border lc rgb '#549f' lw 0.1
set object 3015 polygon from \
  -1.4935, 63.1664 to \
  -0.03, 63.1664 to \
  -0.03, 32.9781 to \
  -1.4935, 32.9781 to \
  -1.4935, 63.1664 front fs empty border lc rgb '#549f' lw 0.1
set object 3016 polygon from \
  -1.50974, 63.1892 to \
  -0.03, 63.1892 to \
  -0.03, 32.9909 to \
  -1.50974, 32.9909 to \
  -1.50974, 63.1892 front fs empty border lc rgb '#549f' lw 0.1
set object 3017 polygon from \
  -1.52542, 63.2119 to \
  -0.03, 63.2119 to \
  -0.03, 33.0036 to \
  -1.52542, 33.0036 to \
  -1.52542, 63.2119 front fs empty border lc rgb '#549f' lw 0.1
set object 3018 polygon from \
  -1.54055, 63.2347 to \
  -0.03, 63.2347 to \
  -0.03, 33.0164 to \
  -1.54055, 33.0164 to \
  -1.54055, 63.2347 front fs empty border lc rgb '#549f' lw 0.1
set object 3019 polygon from \
  -1.55513, 63.2575 to \
  -0.03, 63.2575 to \
  -0.03, 33.0292 to \
  -1.55513, 33.0292 to \
  -1.55513, 63.2575 front fs empty border lc rgb '#549f' lw 0.1
set object 3020 polygon from \
  -1.56916, 63.2803 to \
  -0.03, 63.2803 to \
  -0.03, 33.0419 to \
  -1.56916, 33.0419 to \
  -1.56916, 63.2803 front fs empty border lc rgb '#549f' lw 0.1
set object 3021 polygon from \
  -1.58265, 63.303 to \
  -0.03, 63.303 to \
  -0.03, 33.0547 to \
  -1.58265, 33.0547 to \
  -1.58265, 63.303 front fs empty border lc rgb '#549f' lw 0.1
set object 3022 polygon from \
  -1.59561, 63.3258 to \
  -0.03, 63.3258 to \
  -0.03, 33.0675 to \
  -1.59561, 33.0675 to \
  -1.59561, 63.3258 front fs empty border lc rgb '#549f' lw 0.1
set object 3023 polygon from \
  -1.60804, 63.3486 to \
  -0.03, 63.3486 to \
  -0.03, 33.0802 to \
  -1.60804, 33.0802 to \
  -1.60804, 63.3486 front fs empty border lc rgb '#549f' lw 0.1
set object 3024 polygon from \
  -1.61995, 63.3714 to \
  -0.03, 63.3714 to \
  -0.03, 33.093 to \
  -1.61995, 33.093 to \
  -1.61995, 63.3714 front fs empty border lc rgb '#549f' lw 0.1
set object 3025 polygon from \
  -1.63135, 63.3941 to \
  -0.03, 63.3941 to \
  -0.03, 33.1058 to \
  -1.63135, 33.1058 to \
  -1.63135, 63.3941 front fs empty border lc rgb '#549f' lw 0.1
set object 3026 polygon from \
  -1.64225, 63.4169 to \
  -0.03, 63.4169 to \
  -0.03, 33.1186 to \
  -1.64225, 33.1186 to \
  -1.64225, 63.4169 front fs empty border lc rgb '#549f' lw 0.1
set object 3027 polygon from \
  -1.65264, 63.4397 to \
  -0.03, 63.4397 to \
  -0.03, 33.1314 to \
  -1.65264, 33.1314 to \
  -1.65264, 63.4397 front fs empty border lc rgb '#549f' lw 0.1
set object 3028 polygon from \
  -1.66254, 63.4625 to \
  -0.03, 63.4625 to \
  -0.03, 33.1441 to \
  -1.66254, 33.1441 to \
  -1.66254, 63.4625 front fs empty border lc rgb '#549f' lw 0.1
set object 3029 polygon from \
  -1.67195, 63.4853 to \
  -0.03, 63.4853 to \
  -0.03, 33.1569 to \
  -1.67195, 33.1569 to \
  -1.67195, 63.4853 front fs empty border lc rgb '#549f' lw 0.1
set object 3030 polygon from \
  -1.68089, 63.5081 to \
  -0.03, 63.5081 to \
  -0.03, 33.1697 to \
  -1.68089, 33.1697 to \
  -1.68089, 63.5081 front fs empty border lc rgb '#549f' lw 0.1
set object 3031 polygon from \
  -1.68936, 63.5309 to \
  -0.03, 63.5309 to \
  -0.03, 33.1825 to \
  -1.68936, 33.1825 to \
  -1.68936, 63.5309 front fs empty border lc rgb '#549f' lw 0.1
set object 3032 polygon from \
  -1.69737, 63.5536 to \
  -0.03, 63.5536 to \
  -0.03, 33.1953 to \
  -1.69737, 33.1953 to \
  -1.69737, 63.5536 front fs empty border lc rgb '#549f' lw 0.1
set object 3033 polygon from \
  -1.70492, 63.5764 to \
  -0.03, 63.5764 to \
  -0.03, 33.2081 to \
  -1.70492, 33.2081 to \
  -1.70492, 63.5764 front fs empty border lc rgb '#549f' lw 0.1
set object 3034 polygon from \
  -1.71203, 63.5992 to \
  -0.03, 63.5992 to \
  -0.03, 33.2208 to \
  -1.71203, 33.2208 to \
  -1.71203, 63.5992 front fs empty border lc rgb '#549f' lw 0.1
set object 3035 polygon from \
  -1.7187, 63.622 to \
  -0.03, 63.622 to \
  -0.03, 33.2336 to \
  -1.7187, 33.2336 to \
  -1.7187, 63.622 front fs empty border lc rgb '#549f' lw 0.1
set object 3036 polygon from \
  -1.72494, 63.6448 to \
  -0.03, 63.6448 to \
  -0.03, 33.2464 to \
  -1.72494, 33.2464 to \
  -1.72494, 63.6448 front fs empty border lc rgb '#549f' lw 0.1
set object 3037 polygon from \
  -1.73342, 63.6676 to \
  -0.03, 63.6676 to \
  -0.03, 33.2592 to \
  -1.73342, 33.2592 to \
  -1.73342, 63.6676 front fs empty border lc rgb '#549f' lw 0.1
set object 3038 polygon from \
  -1.77593, 63.6904 to \
  -0.03, 63.6904 to \
  -0.03, 33.272 to \
  -1.77593, 33.272 to \
  -1.77593, 63.6904 front fs empty border lc rgb '#549f' lw 0.1
set object 3039 polygon from \
  -1.81788, 63.7132 to \
  -0.03, 63.7132 to \
  -0.03, 33.2848 to \
  -1.81788, 33.2848 to \
  -1.81788, 63.7132 front fs empty border lc rgb '#549f' lw 0.1
set object 3040 polygon from \
  -1.85921, 63.736 to \
  -0.03, 63.736 to \
  -0.03, 33.2976 to \
  -1.85921, 33.2976 to \
  -1.85921, 63.736 front fs empty border lc rgb '#549f' lw 0.1
set object 3041 polygon from \
  -1.89992, 63.7588 to \
  -0.03, 63.7588 to \
  -0.03, 33.3104 to \
  -1.89992, 33.3104 to \
  -1.89992, 63.7588 front fs empty border lc rgb '#549f' lw 0.1
set object 3042 polygon from \
  -1.93998, 63.7816 to \
  -0.03, 63.7816 to \
  -0.03, 33.3232 to \
  -1.93998, 33.3232 to \
  -1.93998, 63.7816 front fs empty border lc rgb '#549f' lw 0.1
set object 3043 polygon from \
  -1.97937, 63.8044 to \
  -0.03, 63.8044 to \
  -0.03, 33.336 to \
  -1.97937, 33.336 to \
  -1.97937, 63.8044 front fs empty border lc rgb '#549f' lw 0.1
set object 3044 polygon from \
  -2.01808, 63.8272 to \
  -0.03, 63.8272 to \
  -0.03, 33.3488 to \
  -2.01808, 33.3488 to \
  -2.01808, 63.8272 front fs empty border lc rgb '#549f' lw 0.1
set object 3045 polygon from \
  -2.05607, 63.85 to \
  -0.03, 63.85 to \
  -0.03, 33.3616 to \
  -2.05607, 33.3616 to \
  -2.05607, 63.85 front fs empty border lc rgb '#549f' lw 0.1
set object 3046 polygon from \
  -2.09334, 63.8728 to \
  -0.03, 63.8728 to \
  -0.03, 33.3744 to \
  -2.09334, 33.3744 to \
  -2.09334, 63.8728 front fs empty border lc rgb '#549f' lw 0.1
set object 3047 polygon from \
  -2.12987, 63.8956 to \
  -0.03, 63.8956 to \
  -0.03, 33.3872 to \
  -2.12987, 33.3872 to \
  -2.12987, 63.8956 front fs empty border lc rgb '#549f' lw 0.1
set object 3048 polygon from \
  -2.16563, 63.9184 to \
  -0.03, 63.9184 to \
  -0.03, 33.4 to \
  -2.16563, 33.4 to \
  -2.16563, 63.9184 front fs empty border lc rgb '#549f' lw 0.1
set object 3049 polygon from \
  -2.2006, 63.9413 to \
  -0.03, 63.9413 to \
  -0.03, 33.4128 to \
  -2.2006, 33.4128 to \
  -2.2006, 63.9413 front fs empty border lc rgb '#549f' lw 0.1
set object 3050 polygon from \
  -2.23478, 63.9641 to \
  -0.03, 63.9641 to \
  -0.03, 33.4256 to \
  -2.23478, 33.4256 to \
  -2.23478, 63.9641 front fs empty border lc rgb '#549f' lw 0.1
set object 3051 polygon from \
  -2.26814, 63.9869 to \
  -0.03, 63.9869 to \
  -0.03, 33.4384 to \
  -2.26814, 33.4384 to \
  -2.26814, 63.9869 front fs empty border lc rgb '#549f' lw 0.1
set object 3052 polygon from \
  -2.30066, 64.0097 to \
  -0.03, 64.0097 to \
  -0.03, 33.4512 to \
  -2.30066, 33.4512 to \
  -2.30066, 64.0097 front fs empty border lc rgb '#549f' lw 0.1
set object 3053 polygon from \
  -2.33234, 64.0325 to \
  -0.03, 64.0325 to \
  -0.03, 33.4641 to \
  -2.33234, 33.4641 to \
  -2.33234, 64.0325 front fs empty border lc rgb '#549f' lw 0.1
set object 3054 polygon from \
  -2.36314, 64.0553 to \
  -0.03, 64.0553 to \
  -0.03, 33.4769 to \
  -2.36314, 33.4769 to \
  -2.36314, 64.0553 front fs empty border lc rgb '#549f' lw 0.1
set object 3055 polygon from \
  -2.39306, 64.0781 to \
  -0.03, 64.0781 to \
  -0.03, 33.4897 to \
  -2.39306, 33.4897 to \
  -2.39306, 64.0781 front fs empty border lc rgb '#549f' lw 0.1
set object 3056 polygon from \
  -2.42208, 64.101 to \
  -0.03, 64.101 to \
  -0.03, 33.5025 to \
  -2.42208, 33.5025 to \
  -2.42208, 64.101 front fs empty border lc rgb '#549f' lw 0.1
set object 3057 polygon from \
  -2.45019, 64.1238 to \
  -0.03, 64.1238 to \
  -0.03, 33.5153 to \
  -2.45019, 33.5153 to \
  -2.45019, 64.1238 front fs empty border lc rgb '#549f' lw 0.1
set object 3058 polygon from \
  -2.47737, 64.1466 to \
  -0.03, 64.1466 to \
  -0.03, 33.5281 to \
  -2.47737, 33.5281 to \
  -2.47737, 64.1466 front fs empty border lc rgb '#549f' lw 0.1
set object 3059 polygon from \
  -2.5036, 64.1694 to \
  -0.03, 64.1694 to \
  -0.03, 33.541 to \
  -2.5036, 33.541 to \
  -2.5036, 64.1694 front fs empty border lc rgb '#549f' lw 0.1
set object 3060 polygon from \
  -2.52888, 64.1923 to \
  -0.03, 64.1923 to \
  -0.03, 33.5538 to \
  -2.52888, 33.5538 to \
  -2.52888, 64.1923 front fs empty border lc rgb '#549f' lw 0.1
set object 3061 polygon from \
  -2.55319, 64.2151 to \
  -0.03, 64.2151 to \
  -0.03, 33.5666 to \
  -2.55319, 33.5666 to \
  -2.55319, 64.2151 front fs empty border lc rgb '#549f' lw 0.1
set object 3062 polygon from \
  -2.57652, 64.2379 to \
  -0.03, 64.2379 to \
  -0.03, 33.5794 to \
  -2.57652, 33.5794 to \
  -2.57652, 64.2379 front fs empty border lc rgb '#549f' lw 0.1
set object 3063 polygon from \
  -2.59885, 64.2607 to \
  -0.03, 64.2607 to \
  -0.03, 33.5922 to \
  -2.59885, 33.5922 to \
  -2.59885, 64.2607 front fs empty border lc rgb '#549f' lw 0.1
set object 3064 polygon from \
  -2.62017, 64.2836 to \
  -0.03, 64.2836 to \
  -0.03, 33.6051 to \
  -2.62017, 33.6051 to \
  -2.62017, 64.2836 front fs empty border lc rgb '#549f' lw 0.1
set object 3065 polygon from \
  -2.64232, 64.3064 to \
  -0.03, 64.3064 to \
  -0.03, 33.6179 to \
  -2.64232, 33.6179 to \
  -2.64232, 64.3064 front fs empty border lc rgb '#549f' lw 0.1
set object 3066 polygon from \
  -2.66383, 64.3292 to \
  -0.03, 64.3292 to \
  -0.03, 33.6307 to \
  -2.66383, 33.6307 to \
  -2.66383, 64.3292 front fs empty border lc rgb '#549f' lw 0.1
set object 3067 polygon from \
  -2.68436, 64.3521 to \
  -0.03, 64.3521 to \
  -0.03, 33.6436 to \
  -2.68436, 33.6436 to \
  -2.68436, 64.3521 front fs empty border lc rgb '#549f' lw 0.1
set object 3068 polygon from \
  -2.70389, 64.3749 to \
  -0.03, 64.3749 to \
  -0.03, 33.6564 to \
  -2.70389, 33.6564 to \
  -2.70389, 64.3749 front fs empty border lc rgb '#549f' lw 0.1
set object 3069 polygon from \
  -2.72241, 64.3977 to \
  -0.03, 64.3977 to \
  -0.03, 33.6692 to \
  -2.72241, 33.6692 to \
  -2.72241, 64.3977 front fs empty border lc rgb '#549f' lw 0.1
set object 3070 polygon from \
  -2.73991, 64.4206 to \
  -0.03, 64.4206 to \
  -0.03, 33.6821 to \
  -2.73991, 33.6821 to \
  -2.73991, 64.4206 front fs empty border lc rgb '#549f' lw 0.1
set object 3071 polygon from \
  -2.75638, 64.4434 to \
  -0.03, 64.4434 to \
  -0.03, 33.6949 to \
  -2.75638, 33.6949 to \
  -2.75638, 64.4434 front fs empty border lc rgb '#549f' lw 0.1
set object 3072 polygon from \
  -2.77182, 64.4662 to \
  -0.03, 64.4662 to \
  -0.03, 33.7077 to \
  -2.77182, 33.7077 to \
  -2.77182, 64.4662 front fs empty border lc rgb '#549f' lw 0.1
set object 3073 polygon from \
  -2.78773, 64.4891 to \
  -0.03, 64.4891 to \
  -0.03, 33.7206 to \
  -2.78773, 33.7206 to \
  -2.78773, 64.4891 front fs empty border lc rgb '#549f' lw 0.1
set object 3074 polygon from \
  -2.80258, 64.5119 to \
  -0.03, 64.5119 to \
  -0.03, 33.7334 to \
  -2.80258, 33.7334 to \
  -2.80258, 64.5119 front fs empty border lc rgb '#549f' lw 0.1
set object 3075 polygon from \
  -2.81638, 64.5348 to \
  -0.03, 64.5348 to \
  -0.03, 33.7462 to \
  -2.81638, 33.7462 to \
  -2.81638, 64.5348 front fs empty border lc rgb '#549f' lw 0.1
set object 3076 polygon from \
  -2.82911, 64.5576 to \
  -0.03, 64.5576 to \
  -0.03, 33.7591 to \
  -2.82911, 33.7591 to \
  -2.82911, 64.5576 front fs empty border lc rgb '#549f' lw 0.1
set object 3077 polygon from \
  -2.84076, 64.5805 to \
  -0.03, 64.5805 to \
  -0.03, 33.7719 to \
  -2.84076, 33.7719 to \
  -2.84076, 64.5805 front fs empty border lc rgb '#549f' lw 0.1
set object 3078 polygon from \
  -2.85132, 64.6033 to \
  -0.03, 64.6033 to \
  -0.03, 33.7848 to \
  -2.85132, 33.7848 to \
  -2.85132, 64.6033 front fs empty border lc rgb '#549f' lw 0.1
set object 3079 polygon from \
  -2.8608, 64.6262 to \
  -0.03, 64.6262 to \
  -0.03, 33.7976 to \
  -2.8608, 33.7976 to \
  -2.8608, 64.6262 front fs empty border lc rgb '#549f' lw 0.1
set object 3080 polygon from \
  -2.86918, 64.649 to \
  -0.03, 64.649 to \
  -0.03, 33.8105 to \
  -2.86918, 33.8105 to \
  -2.86918, 64.649 front fs empty border lc rgb '#549f' lw 0.1
set object 3081 polygon from \
  -2.87646, 64.6719 to \
  -0.03, 64.6719 to \
  -0.03, 33.8233 to \
  -2.87646, 33.8233 to \
  -2.87646, 64.6719 front fs empty border lc rgb '#549f' lw 0.1
set object 3082 polygon from \
  -2.88264, 64.6947 to \
  -0.03, 64.6947 to \
  -0.03, 33.8361 to \
  -2.88264, 33.8361 to \
  -2.88264, 64.6947 front fs empty border lc rgb '#549f' lw 0.1
set object 3083 polygon from \
  -2.8877, 64.7176 to \
  -0.03, 64.7176 to \
  -0.03, 33.849 to \
  -2.8877, 33.849 to \
  -2.8877, 64.7176 front fs empty border lc rgb '#549f' lw 0.1
set object 3084 polygon from \
  -2.89165, 64.7404 to \
  -0.03, 64.7404 to \
  -0.03, 33.8618 to \
  -2.89165, 33.8618 to \
  -2.89165, 64.7404 front fs empty border lc rgb '#549f' lw 0.1
set object 3085 polygon from \
  -2.89448, 64.7633 to \
  -0.03, 64.7633 to \
  -0.03, 33.8747 to \
  -2.89448, 33.8747 to \
  -2.89448, 64.7633 front fs empty border lc rgb '#549f' lw 0.1
set object 3086 polygon from \
  -2.89619, 64.7861 to \
  -0.03, 64.7861 to \
  -0.03, 33.8876 to \
  -2.89619, 33.8876 to \
  -2.89619, 64.7861 front fs empty border lc rgb '#549f' lw 0.1
set object 3087 polygon from \
  -2.89678, 64.809 to \
  -0.03, 64.809 to \
  -0.03, 33.9004 to \
  -2.89678, 33.9004 to \
  -2.89678, 64.809 front fs empty border lc rgb '#549f' lw 0.1
set object 3088 polygon from \
  -2.89678, 64.8318 to \
  -0.03, 64.8318 to \
  -0.03, 33.9133 to \
  -2.89678, 33.9133 to \
  -2.89678, 64.8318 front fs empty border lc rgb '#549f' lw 0.1
set object 3089 polygon from \
  -2.89624, 64.8547 to \
  -0.03, 64.8547 to \
  -0.03, 33.9261 to \
  -2.89624, 33.9261 to \
  -2.89624, 64.8547 front fs empty border lc rgb '#549f' lw 0.1
set object 3090 polygon from \
  -2.89458, 64.8776 to \
  -0.03, 64.8776 to \
  -0.03, 33.939 to \
  -2.89458, 33.939 to \
  -2.89458, 64.8776 front fs empty border lc rgb '#549f' lw 0.1
set object 3091 polygon from \
  -2.89179, 64.9004 to \
  -0.03, 64.9004 to \
  -0.03, 33.9518 to \
  -2.89179, 33.9518 to \
  -2.89179, 64.9004 front fs empty border lc rgb '#549f' lw 0.1
set object 3092 polygon from \
  -2.88788, 64.9233 to \
  -0.03, 64.9233 to \
  -0.03, 33.9647 to \
  -2.88788, 33.9647 to \
  -2.88788, 64.9233 front fs empty border lc rgb '#549f' lw 0.1
set object 3093 polygon from \
  -2.88363, 64.9462 to \
  -0.03, 64.9462 to \
  -0.03, 33.9776 to \
  -2.88363, 33.9776 to \
  -2.88363, 64.9462 front fs empty border lc rgb '#549f' lw 0.1
set object 3094 polygon from \
  -2.88298, 64.969 to \
  -0.03, 64.969 to \
  -0.03, 33.9904 to \
  -2.88298, 33.9904 to \
  -2.88298, 64.969 front fs empty border lc rgb '#549f' lw 0.1
set object 3095 polygon from \
  -2.88122, 64.9919 to \
  -0.03, 64.9919 to \
  -0.03, 34.0033 to \
  -2.88122, 34.0033 to \
  -2.88122, 64.9919 front fs empty border lc rgb '#549f' lw 0.1
set object 3096 polygon from \
  -2.87838, 65.0148 to \
  -0.03, 65.0148 to \
  -0.03, 34.0162 to \
  -2.87838, 34.0162 to \
  -2.87838, 65.0148 front fs empty border lc rgb '#549f' lw 0.1
set object 3097 polygon from \
  -2.87444, 65.0376 to \
  -0.03, 65.0376 to \
  -0.03, 34.029 to \
  -2.87444, 34.029 to \
  -2.87444, 65.0376 front fs empty border lc rgb '#549f' lw 0.1
set object 3098 polygon from \
  -2.86942, 65.0605 to \
  -0.03, 65.0605 to \
  -0.03, 34.0419 to \
  -2.86942, 34.0419 to \
  -2.86942, 65.0605 front fs empty border lc rgb '#549f' lw 0.1
set object 3099 polygon from \
  -2.86332, 65.0834 to \
  -0.03, 65.0834 to \
  -0.03, 34.0548 to \
  -2.86332, 34.0548 to \
  -2.86332, 65.0834 front fs empty border lc rgb '#549f' lw 0.1
set object 3100 polygon from \
  -2.85614, 65.1063 to \
  -0.03, 65.1063 to \
  -0.03, 34.0676 to \
  -2.85614, 34.0676 to \
  -2.85614, 65.1063 front fs empty border lc rgb '#549f' lw 0.1
set object 3101 polygon from \
  -2.84789, 65.1291 to \
  -0.03, 65.1291 to \
  -0.03, 34.0805 to \
  -2.84789, 34.0805 to \
  -2.84789, 65.1291 front fs empty border lc rgb '#549f' lw 0.1
set object 3102 polygon from \
  -2.83857, 65.152 to \
  -0.03, 65.152 to \
  -0.03, 34.0934 to \
  -2.83857, 34.0934 to \
  -2.83857, 65.152 front fs empty border lc rgb '#549f' lw 0.1
set object 3103 polygon from \
  -2.82819, 65.1749 to \
  -0.03, 65.1749 to \
  -0.03, 34.1062 to \
  -2.82819, 34.1062 to \
  -2.82819, 65.1749 front fs empty border lc rgb '#549f' lw 0.1
set object 3104 polygon from \
  -2.81677, 65.1978 to \
  -0.03, 65.1978 to \
  -0.03, 34.1191 to \
  -2.81677, 34.1191 to \
  -2.81677, 65.1978 front fs empty border lc rgb '#549f' lw 0.1
set object 3105 polygon from \
  -2.80429, 65.2206 to \
  -0.03, 65.2206 to \
  -0.03, 34.132 to \
  -2.80429, 34.132 to \
  -2.80429, 65.2206 front fs empty border lc rgb '#549f' lw 0.1
set object 3106 polygon from \
  -2.79441, 65.2435 to \
  -0.03, 65.2435 to \
  -0.03, 34.1449 to \
  -2.79441, 34.1449 to \
  -2.79441, 65.2435 front fs empty border lc rgb '#549f' lw 0.1
set object 3107 polygon from \
  -2.79182, 65.2664 to \
  -0.03, 65.2664 to \
  -0.03, 34.1578 to \
  -2.79182, 34.1578 to \
  -2.79182, 65.2664 front fs empty border lc rgb '#549f' lw 0.1
set object 3108 polygon from \
  -2.78817, 65.2893 to \
  -0.03, 65.2893 to \
  -0.03, 34.1706 to \
  -2.78817, 34.1706 to \
  -2.78817, 65.2893 front fs empty border lc rgb '#549f' lw 0.1
set object 3109 polygon from \
  -2.78344, 65.3122 to \
  -0.03, 65.3122 to \
  -0.03, 34.1835 to \
  -2.78344, 34.1835 to \
  -2.78344, 65.3122 front fs empty border lc rgb '#549f' lw 0.1
set object 3110 polygon from \
  -2.77766, 65.3351 to \
  -0.03, 65.3351 to \
  -0.03, 34.1964 to \
  -2.77766, 34.1964 to \
  -2.77766, 65.3351 front fs empty border lc rgb '#549f' lw 0.1
set object 3111 polygon from \
  -2.77082, 65.358 to \
  -0.03, 65.358 to \
  -0.03, 34.2093 to \
  -2.77082, 34.2093 to \
  -2.77082, 65.358 front fs empty border lc rgb '#549f' lw 0.1
set object 3112 polygon from \
  -2.76294, 65.3808 to \
  -0.03, 65.3808 to \
  -0.03, 34.2222 to \
  -2.76294, 34.2222 to \
  -2.76294, 65.3808 front fs empty border lc rgb '#549f' lw 0.1
set object 3113 polygon from \
  -2.75402, 65.4037 to \
  -0.03, 65.4037 to \
  -0.03, 34.2351 to \
  -2.75402, 34.2351 to \
  -2.75402, 65.4037 front fs empty border lc rgb '#549f' lw 0.1
set object 3114 polygon from \
  -2.74407, 65.4266 to \
  -0.03, 65.4266 to \
  -0.03, 34.2479 to \
  -2.74407, 34.2479 to \
  -2.74407, 65.4266 front fs empty border lc rgb '#549f' lw 0.1
set object 3115 polygon from \
  -2.73309, 65.4495 to \
  -0.03, 65.4495 to \
  -0.03, 34.2608 to \
  -2.73309, 34.2608 to \
  -2.73309, 65.4495 front fs empty border lc rgb '#549f' lw 0.1
set object 3116 polygon from \
  -2.7211, 65.4724 to \
  -0.03, 65.4724 to \
  -0.03, 34.2737 to \
  -2.7211, 34.2737 to \
  -2.7211, 65.4724 front fs empty border lc rgb '#549f' lw 0.1
set object 3117 polygon from \
  -2.70811, 65.4953 to \
  -0.03, 65.4953 to \
  -0.03, 34.2866 to \
  -2.70811, 34.2866 to \
  -2.70811, 65.4953 front fs empty border lc rgb '#549f' lw 0.1
set object 3118 polygon from \
  -2.69412, 65.5182 to \
  -0.03, 65.5182 to \
  -0.03, 34.2995 to \
  -2.69412, 34.2995 to \
  -2.69412, 65.5182 front fs empty border lc rgb '#549f' lw 0.1
set object 3119 polygon from \
  -2.67915, 65.5411 to \
  -0.03, 65.5411 to \
  -0.03, 34.3124 to \
  -2.67915, 34.3124 to \
  -2.67915, 65.5411 front fs empty border lc rgb '#549f' lw 0.1
set object 3120 polygon from \
  -2.6632, 65.564 to \
  -0.03, 65.564 to \
  -0.03, 34.3253 to \
  -2.6632, 34.3253 to \
  -2.6632, 65.564 front fs empty border lc rgb '#549f' lw 0.1
set object 3121 polygon from \
  -2.64629, 65.5869 to \
  -0.03, 65.5869 to \
  -0.03, 34.3382 to \
  -2.64629, 34.3382 to \
  -2.64629, 65.5869 front fs empty border lc rgb '#549f' lw 0.1
set object 3122 polygon from \
  -2.62844, 65.6098 to \
  -0.03, 65.6098 to \
  -0.03, 34.3511 to \
  -2.62844, 34.3511 to \
  -2.62844, 65.6098 front fs empty border lc rgb '#549f' lw 0.1
set object 3123 polygon from \
  -2.6098, 65.6327 to \
  -0.03, 65.6327 to \
  -0.03, 34.364 to \
  -2.6098, 34.364 to \
  -2.6098, 65.6327 front fs empty border lc rgb '#549f' lw 0.1
set object 3124 polygon from \
  -2.59058, 65.6556 to \
  -0.03, 65.6556 to \
  -0.03, 34.3769 to \
  -2.59058, 34.3769 to \
  -2.59058, 65.6556 front fs empty border lc rgb '#549f' lw 0.1
set object 3125 polygon from \
  -2.57045, 65.6785 to \
  -0.03, 65.6785 to \
  -0.03, 34.3898 to \
  -2.57045, 34.3898 to \
  -2.57045, 65.6785 front fs empty border lc rgb '#549f' lw 0.1
set object 3126 polygon from \
  -2.54943, 65.7014 to \
  -0.03, 65.7014 to \
  -0.03, 34.4027 to \
  -2.54943, 34.4027 to \
  -2.54943, 65.7014 front fs empty border lc rgb '#549f' lw 0.1
set object 3127 polygon from \
  -2.52753, 65.7243 to \
  -0.03, 65.7243 to \
  -0.03, 34.4156 to \
  -2.52753, 34.4156 to \
  -2.52753, 65.7243 front fs empty border lc rgb '#549f' lw 0.1
set object 3128 polygon from \
  -2.50476, 65.7472 to \
  -0.03, 65.7472 to \
  -0.03, 34.4285 to \
  -2.50476, 34.4285 to \
  -2.50476, 65.7472 front fs empty border lc rgb '#549f' lw 0.1
set object 3129 polygon from \
  -2.48113, 65.7702 to \
  -0.03, 65.7702 to \
  -0.03, 34.4414 to \
  -2.48113, 34.4414 to \
  -2.48113, 65.7702 front fs empty border lc rgb '#549f' lw 0.1
set object 3130 polygon from \
  -2.45667, 65.7931 to \
  -0.03, 65.7931 to \
  -0.03, 34.4543 to \
  -2.45667, 34.4543 to \
  -2.45667, 65.7931 front fs empty border lc rgb '#549f' lw 0.1
set object 3131 polygon from \
  -2.43139, 65.816 to \
  -0.03, 65.816 to \
  -0.03, 34.4672 to \
  -2.43139, 34.4672 to \
  -2.43139, 65.816 front fs empty border lc rgb '#549f' lw 0.1
set object 3132 polygon from \
  -2.40531, 65.8389 to \
  -0.03, 65.8389 to \
  -0.03, 34.4801 to \
  -2.40531, 34.4801 to \
  -2.40531, 65.8389 front fs empty border lc rgb '#549f' lw 0.1
set object 3133 polygon from \
  -2.37843, 65.8618 to \
  -0.03, 65.8618 to \
  -0.03, 34.4931 to \
  -2.37843, 34.4931 to \
  -2.37843, 65.8618 front fs empty border lc rgb '#549f' lw 0.1
set object 3134 polygon from \
  -2.35079, 65.8847 to \
  -0.03, 65.8847 to \
  -0.03, 34.506 to \
  -2.35079, 34.506 to \
  -2.35079, 65.8847 front fs empty border lc rgb '#549f' lw 0.1
set object 3135 polygon from \
  -2.32238, 65.9076 to \
  -0.03, 65.9076 to \
  -0.03, 34.5189 to \
  -2.32238, 34.5189 to \
  -2.32238, 65.9076 front fs empty border lc rgb '#549f' lw 0.1
set object 3136 polygon from \
  -2.29324, 65.9306 to \
  -0.03, 65.9306 to \
  -0.03, 34.5318 to \
  -2.29324, 34.5318 to \
  -2.29324, 65.9306 front fs empty border lc rgb '#549f' lw 0.1
set object 3137 polygon from \
  -2.26338, 65.9535 to \
  -0.03, 65.9535 to \
  -0.03, 34.5447 to \
  -2.26338, 34.5447 to \
  -2.26338, 65.9535 front fs empty border lc rgb '#549f' lw 0.1
set object 3138 polygon from \
  -2.23281, 65.9764 to \
  -0.03, 65.9764 to \
  -0.03, 34.5576 to \
  -2.23281, 34.5576 to \
  -2.23281, 65.9764 front fs empty border lc rgb '#549f' lw 0.1
set object 3139 polygon from \
  -2.23801, 65.9993 to \
  -0.03, 65.9993 to \
  -0.03, 34.5706 to \
  -2.23801, 34.5706 to \
  -2.23801, 65.9993 front fs empty border lc rgb '#549f' lw 0.1
set object 3140 polygon from \
  -2.24435, 66.0223 to \
  -0.03, 66.0223 to \
  -0.03, 34.5835 to \
  -2.24435, 34.5835 to \
  -2.24435, 66.0223 front fs empty border lc rgb '#549f' lw 0.1
set object 3141 polygon from \
  -2.2502, 66.0452 to \
  -0.03, 66.0452 to \
  -0.03, 34.5964 to \
  -2.2502, 34.5964 to \
  -2.2502, 66.0452 front fs empty border lc rgb '#549f' lw 0.1
set object 3142 polygon from \
  -2.25554, 66.0681 to \
  -0.03, 66.0681 to \
  -0.03, 34.6093 to \
  -2.25554, 34.6093 to \
  -2.25554, 66.0681 front fs empty border lc rgb '#549f' lw 0.1
set object 3143 polygon from \
  -2.26036, 66.091 to \
  -0.03, 66.091 to \
  -0.03, 34.6222 to \
  -2.26036, 34.6222 to \
  -2.26036, 66.091 front fs empty border lc rgb '#549f' lw 0.1
set object 3144 polygon from \
  -2.26466, 66.114 to \
  -0.03, 66.114 to \
  -0.03, 34.6352 to \
  -2.26466, 34.6352 to \
  -2.26466, 66.114 front fs empty border lc rgb '#549f' lw 0.1
set object 3145 polygon from \
  -2.26841, 66.1369 to \
  -0.03, 66.1369 to \
  -0.03, 34.6481 to \
  -2.26841, 34.6481 to \
  -2.26841, 66.1369 front fs empty border lc rgb '#549f' lw 0.1
set object 3146 polygon from \
  -2.27161, 66.1598 to \
  -0.03, 66.1598 to \
  -0.03, 34.661 to \
  -2.27161, 34.661 to \
  -2.27161, 66.1598 front fs empty border lc rgb '#549f' lw 0.1
set object 3147 polygon from \
  -2.27426, 66.1828 to \
  -0.03, 66.1828 to \
  -0.03, 34.674 to \
  -2.27426, 34.674 to \
  -2.27426, 66.1828 front fs empty border lc rgb '#549f' lw 0.1
set object 3148 polygon from \
  -2.27633, 66.2057 to \
  -0.03, 66.2057 to \
  -0.03, 34.6869 to \
  -2.27633, 34.6869 to \
  -2.27633, 66.2057 front fs empty border lc rgb '#549f' lw 0.1
set object 3149 polygon from \
  -2.27782, 66.2286 to \
  -0.03, 66.2286 to \
  -0.03, 34.6998 to \
  -2.27782, 34.6998 to \
  -2.27782, 66.2286 front fs empty border lc rgb '#549f' lw 0.1
set object 3150 polygon from \
  -2.27872, 66.2516 to \
  -0.03, 66.2516 to \
  -0.03, 34.7128 to \
  -2.27872, 34.7128 to \
  -2.27872, 66.2516 front fs empty border lc rgb '#549f' lw 0.1
set object 3151 polygon from \
  -2.27902, 66.2745 to \
  -0.03, 66.2745 to \
  -0.03, 34.7257 to \
  -2.27902, 34.7257 to \
  -2.27902, 66.2745 front fs empty border lc rgb '#549f' lw 0.1
set object 3152 polygon from \
  -2.27902, 66.2974 to \
  -0.03, 66.2974 to \
  -0.03, 34.7386 to \
  -2.27902, 34.7386 to \
  -2.27902, 66.2974 front fs empty border lc rgb '#549f' lw 0.1
set object 3153 polygon from \
  -2.27871, 66.3204 to \
  -0.03, 66.3204 to \
  -0.03, 34.7516 to \
  -2.27871, 34.7516 to \
  -2.27871, 66.3204 front fs empty border lc rgb '#549f' lw 0.1
set object 3154 polygon from \
  -2.27778, 66.3433 to \
  -0.03, 66.3433 to \
  -0.03, 34.7645 to \
  -2.27778, 34.7645 to \
  -2.27778, 66.3433 front fs empty border lc rgb '#549f' lw 0.1
set object 3155 polygon from \
  -2.27622, 66.3663 to \
  -0.03, 66.3663 to \
  -0.03, 34.7774 to \
  -2.27622, 34.7774 to \
  -2.27622, 66.3663 front fs empty border lc rgb '#549f' lw 0.1
set object 3156 polygon from \
  -2.27403, 66.3892 to \
  -0.03, 66.3892 to \
  -0.03, 34.7904 to \
  -2.27403, 34.7904 to \
  -2.27403, 66.3892 front fs empty border lc rgb '#549f' lw 0.1
set object 3157 polygon from \
  -2.27119, 66.4122 to \
  -0.03, 66.4122 to \
  -0.03, 34.8033 to \
  -2.27119, 34.8033 to \
  -2.27119, 66.4122 front fs empty border lc rgb '#549f' lw 0.1
set object 3158 polygon from \
  -2.26769, 66.4351 to \
  -0.03, 66.4351 to \
  -0.03, 34.8163 to \
  -2.26769, 34.8163 to \
  -2.26769, 66.4351 front fs empty border lc rgb '#549f' lw 0.1
set object 3159 polygon from \
  -2.26353, 66.4581 to \
  -0.03, 66.4581 to \
  -0.03, 34.8292 to \
  -2.26353, 34.8292 to \
  -2.26353, 66.4581 front fs empty border lc rgb '#549f' lw 0.1
set object 3160 polygon from \
  -2.2587, 66.481 to \
  -0.03, 66.481 to \
  -0.03, 34.8422 to \
  -2.2587, 34.8422 to \
  -2.2587, 66.481 front fs empty border lc rgb '#549f' lw 0.1
set object 3161 polygon from \
  -2.2532, 66.504 to \
  -0.03, 66.504 to \
  -0.03, 34.8551 to \
  -2.2532, 34.8551 to \
  -2.2532, 66.504 front fs empty border lc rgb '#549f' lw 0.1
set object 3162 polygon from \
  -2.247, 66.5269 to \
  -0.03, 66.5269 to \
  -0.03, 34.868 to \
  -2.247, 34.868 to \
  -2.247, 66.5269 front fs empty border lc rgb '#549f' lw 0.1
set object 3163 polygon from \
  -2.24012, 66.5499 to \
  -0.03, 66.5499 to \
  -0.03, 34.881 to \
  -2.24012, 34.881 to \
  -2.24012, 66.5499 front fs empty border lc rgb '#549f' lw 0.1
set object 3164 polygon from \
  -2.23253, 66.5728 to \
  -0.03, 66.5728 to \
  -0.03, 34.8939 to \
  -2.23253, 34.8939 to \
  -2.23253, 66.5728 front fs empty border lc rgb '#549f' lw 0.1
set object 3165 polygon from \
  -2.22424, 66.5958 to \
  -0.03, 66.5958 to \
  -0.03, 34.9069 to \
  -2.22424, 34.9069 to \
  -2.22424, 66.5958 front fs empty border lc rgb '#549f' lw 0.1
set object 3166 polygon from \
  -2.21524, 66.6187 to \
  -0.03, 66.6187 to \
  -0.03, 34.9199 to \
  -2.21524, 34.9199 to \
  -2.21524, 66.6187 front fs empty border lc rgb '#549f' lw 0.1
set object 3167 polygon from \
  -2.20552, 66.6417 to \
  -0.03, 66.6417 to \
  -0.03, 34.9328 to \
  -2.20552, 34.9328 to \
  -2.20552, 66.6417 front fs empty border lc rgb '#549f' lw 0.1
set object 3168 polygon from \
  -2.19507, 66.6646 to \
  -0.03, 66.6646 to \
  -0.03, 34.9458 to \
  -2.19507, 34.9458 to \
  -2.19507, 66.6646 front fs empty border lc rgb '#549f' lw 0.1
set object 3169 polygon from \
  -2.1839, 66.6876 to \
  -0.03, 66.6876 to \
  -0.03, 34.9587 to \
  -2.1839, 34.9587 to \
  -2.1839, 66.6876 front fs empty border lc rgb '#549f' lw 0.1
set object 3170 polygon from \
  -2.17199, 66.7106 to \
  -0.03, 66.7106 to \
  -0.03, 34.9717 to \
  -2.17199, 34.9717 to \
  -2.17199, 66.7106 front fs empty border lc rgb '#549f' lw 0.1
set object 3171 polygon from \
  -2.15934, 66.7335 to \
  -0.03, 66.7335 to \
  -0.03, 34.9846 to \
  -2.15934, 34.9846 to \
  -2.15934, 66.7335 front fs empty border lc rgb '#549f' lw 0.1
set object 3172 polygon from \
  -2.14595, 66.7565 to \
  -0.03, 66.7565 to \
  -0.03, 34.9976 to \
  -2.14595, 34.9976 to \
  -2.14595, 66.7565 front fs empty border lc rgb '#549f' lw 0.1
set object 3173 polygon from \
  -2.13182, 66.7795 to \
  -0.03, 66.7795 to \
  -0.03, 35.0106 to \
  -2.13182, 35.0106 to \
  -2.13182, 66.7795 front fs empty border lc rgb '#549f' lw 0.1
set object 3174 polygon from \
  -2.11693, 66.8024 to \
  -0.03, 66.8024 to \
  -0.03, 35.0235 to \
  -2.11693, 35.0235 to \
  -2.11693, 66.8024 front fs empty border lc rgb '#549f' lw 0.1
set object 3175 polygon from \
  -2.10129, 66.8254 to \
  -0.03, 66.8254 to \
  -0.03, 35.0365 to \
  -2.10129, 35.0365 to \
  -2.10129, 66.8254 front fs empty border lc rgb '#549f' lw 0.1
set object 3176 polygon from \
  -2.08489, 66.8484 to \
  -0.03, 66.8484 to \
  -0.03, 35.0495 to \
  -2.08489, 35.0495 to \
  -2.08489, 66.8484 front fs empty border lc rgb '#549f' lw 0.1
set object 3177 polygon from \
  -2.06773, 66.8713 to \
  -0.03, 66.8713 to \
  -0.03, 35.0624 to \
  -2.06773, 35.0624 to \
  -2.06773, 66.8713 front fs empty border lc rgb '#549f' lw 0.1
set object 3178 polygon from \
  -2.04982, 66.8943 to \
  -0.03, 66.8943 to \
  -0.03, 35.0754 to \
  -2.04982, 35.0754 to \
  -2.04982, 66.8943 front fs empty border lc rgb '#549f' lw 0.1
set object 3179 polygon from \
  -2.03114, 66.9173 to \
  -0.03, 66.9173 to \
  -0.03, 35.0884 to \
  -2.03114, 35.0884 to \
  -2.03114, 66.9173 front fs empty border lc rgb '#549f' lw 0.1
set object 3180 polygon from \
  -2.01169, 66.9403 to \
  -0.03, 66.9403 to \
  -0.03, 35.1013 to \
  -2.01169, 35.1013 to \
  -2.01169, 66.9403 front fs empty border lc rgb '#549f' lw 0.1
set object 3181 polygon from \
  -2.01919, 66.9632 to \
  -0.03, 66.9632 to \
  -0.03, 35.1143 to \
  -2.01919, 35.1143 to \
  -2.01919, 66.9632 front fs empty border lc rgb '#549f' lw 0.1
set object 3182 polygon from \
  -2.03819, 66.9862 to \
  -0.03, 66.9862 to \
  -0.03, 35.1273 to \
  -2.03819, 35.1273 to \
  -2.03819, 66.9862 front fs empty border lc rgb '#549f' lw 0.1
set object 3183 polygon from \
  -2.05606, 67.0092 to \
  -0.03, 67.0092 to \
  -0.03, 35.1402 to \
  -2.05606, 35.1402 to \
  -2.05606, 67.0092 front fs empty border lc rgb '#549f' lw 0.1
set object 3184 polygon from \
  -2.07279, 67.0322 to \
  -0.03, 67.0322 to \
  -0.03, 35.1532 to \
  -2.07279, 35.1532 to \
  -2.07279, 67.0322 front fs empty border lc rgb '#549f' lw 0.1
set object 3185 polygon from \
  -2.08837, 67.0551 to \
  -0.03, 67.0551 to \
  -0.03, 35.1662 to \
  -2.08837, 35.1662 to \
  -2.08837, 67.0551 front fs empty border lc rgb '#549f' lw 0.1
set object 3186 polygon from \
  -2.10279, 67.0781 to \
  -0.03, 67.0781 to \
  -0.03, 35.1792 to \
  -2.10279, 35.1792 to \
  -2.10279, 67.0781 front fs empty border lc rgb '#549f' lw 0.1
set object 3187 polygon from \
  -2.11602, 67.1011 to \
  -0.03, 67.1011 to \
  -0.03, 35.1922 to \
  -2.11602, 35.1922 to \
  -2.11602, 67.1011 front fs empty border lc rgb '#549f' lw 0.1
set object 3188 polygon from \
  -2.12806, 67.1241 to \
  -0.03, 67.1241 to \
  -0.03, 35.2051 to \
  -2.12806, 35.2051 to \
  -2.12806, 67.1241 front fs empty border lc rgb '#549f' lw 0.1
set object 3189 polygon from \
  -2.13889, 67.1471 to \
  -0.03, 67.1471 to \
  -0.03, 35.2181 to \
  -2.13889, 35.2181 to \
  -2.13889, 67.1471 front fs empty border lc rgb '#549f' lw 0.1
set object 3190 polygon from \
  -2.14851, 67.1701 to \
  -0.03, 67.1701 to \
  -0.03, 35.2311 to \
  -2.14851, 35.2311 to \
  -2.14851, 67.1701 front fs empty border lc rgb '#549f' lw 0.1
set object 3191 polygon from \
  -2.1569, 67.1931 to \
  -0.03, 67.1931 to \
  -0.03, 35.2441 to \
  -2.1569, 35.2441 to \
  -2.1569, 67.1931 front fs empty border lc rgb '#549f' lw 0.1
set object 3192 polygon from \
  -2.16406, 67.216 to \
  -0.03, 67.216 to \
  -0.03, 35.2571 to \
  -2.16406, 35.2571 to \
  -2.16406, 67.216 front fs empty border lc rgb '#549f' lw 0.1
set object 3193 polygon from \
  -2.16998, 67.239 to \
  -0.03, 67.239 to \
  -0.03, 35.2701 to \
  -2.16998, 35.2701 to \
  -2.16998, 67.239 front fs empty border lc rgb '#549f' lw 0.1
set object 3194 polygon from \
  -2.17465, 67.262 to \
  -0.03, 67.262 to \
  -0.03, 35.283 to \
  -2.17465, 35.283 to \
  -2.17465, 67.262 front fs empty border lc rgb '#549f' lw 0.1
set object 3195 polygon from \
  -2.17806, 67.285 to \
  -0.03, 67.285 to \
  -0.03, 35.296 to \
  -2.17806, 35.296 to \
  -2.17806, 67.285 front fs empty border lc rgb '#549f' lw 0.1
set object 3196 polygon from \
  -2.18021, 67.308 to \
  -0.03, 67.308 to \
  -0.03, 35.309 to \
  -2.18021, 35.309 to \
  -2.18021, 67.308 front fs empty border lc rgb '#549f' lw 0.1
set object 3197 polygon from \
  -2.18109, 67.331 to \
  -0.03, 67.331 to \
  -0.03, 35.322 to \
  -2.18109, 35.322 to \
  -2.18109, 67.331 front fs empty border lc rgb '#549f' lw 0.1
set object 3198 polygon from \
  -2.1843, 67.354 to \
  -0.03, 67.354 to \
  -0.03, 35.335 to \
  -2.1843, 35.335 to \
  -2.1843, 67.354 front fs empty border lc rgb '#549f' lw 0.1
set object 3199 polygon from \
  -2.1868, 67.377 to \
  -0.03, 67.377 to \
  -0.03, 35.348 to \
  -2.1868, 35.348 to \
  -2.1868, 67.377 front fs empty border lc rgb '#549f' lw 0.1
set object 3200 polygon from \
  -2.18804, 67.4 to \
  -0.03, 67.4 to \
  -0.03, 35.361 to \
  -2.18804, 35.361 to \
  -2.18804, 67.4 front fs empty border lc rgb '#549f' lw 0.1
set object 3201 polygon from \
  -2.18804, 67.423 to \
  -0.03, 67.423 to \
  -0.03, 35.374 to \
  -2.18804, 35.374 to \
  -2.18804, 67.423 front fs empty border lc rgb '#549f' lw 0.1
set object 3202 polygon from \
  -2.18799, 67.446 to \
  -0.03, 67.446 to \
  -0.03, 35.387 to \
  -2.18799, 35.387 to \
  -2.18799, 67.446 front fs empty border lc rgb '#549f' lw 0.1
set object 3203 polygon from \
  -2.18666, 67.469 to \
  -0.03, 67.469 to \
  -0.03, 35.4 to \
  -2.18666, 35.4 to \
  -2.18666, 67.469 front fs empty border lc rgb '#549f' lw 0.1
set object 3204 polygon from \
  -2.18405, 67.492 to \
  -0.03, 67.492 to \
  -0.03, 35.413 to \
  -2.18405, 35.413 to \
  -2.18405, 67.492 front fs empty border lc rgb '#549f' lw 0.1
set object 3205 polygon from \
  -2.18015, 67.515 to \
  -0.03, 67.515 to \
  -0.03, 35.426 to \
  -2.18015, 35.426 to \
  -2.18015, 67.515 front fs empty border lc rgb '#549f' lw 0.1
set object 3206 polygon from \
  -2.17496, 67.538 to \
  -0.03, 67.538 to \
  -0.03, 35.439 to \
  -2.17496, 35.439 to \
  -2.17496, 67.538 front fs empty border lc rgb '#549f' lw 0.1
set object 3207 polygon from \
  -2.16848, 67.561 to \
  -0.03, 67.561 to \
  -0.03, 35.452 to \
  -2.16848, 35.452 to \
  -2.16848, 67.561 front fs empty border lc rgb '#549f' lw 0.1
set object 3208 polygon from \
  -2.16071, 67.584 to \
  -0.03, 67.584 to \
  -0.03, 35.465 to \
  -2.16071, 35.465 to \
  -2.16071, 67.584 front fs empty border lc rgb '#549f' lw 0.1
set object 3209 polygon from \
  -2.15166, 67.6071 to \
  -0.03, 67.6071 to \
  -0.03, 35.478 to \
  -2.15166, 35.478 to \
  -2.15166, 67.6071 front fs empty border lc rgb '#549f' lw 0.1
set object 3210 polygon from \
  -2.14133, 67.6301 to \
  -0.03, 67.6301 to \
  -0.03, 35.491 to \
  -2.14133, 35.491 to \
  -2.14133, 67.6301 front fs empty border lc rgb '#549f' lw 0.1
set object 3211 polygon from \
  -2.12971, 67.6531 to \
  -0.03, 67.6531 to \
  -0.03, 35.504 to \
  -2.12971, 35.504 to \
  -2.12971, 67.6531 front fs empty border lc rgb '#549f' lw 0.1
set object 3212 polygon from \
  -2.11683, 67.6761 to \
  -0.03, 67.6761 to \
  -0.03, 35.517 to \
  -2.11683, 35.517 to \
  -2.11683, 67.6761 front fs empty border lc rgb '#549f' lw 0.1
set object 3213 polygon from \
  -2.10267, 67.6991 to \
  -0.03, 67.6991 to \
  -0.03, 35.5301 to \
  -2.10267, 35.5301 to \
  -2.10267, 67.6991 front fs empty border lc rgb '#549f' lw 0.1
set object 3214 polygon from \
  -2.08724, 67.7221 to \
  -0.03, 67.7221 to \
  -0.03, 35.5431 to \
  -2.08724, 35.5431 to \
  -2.08724, 67.7221 front fs empty border lc rgb '#549f' lw 0.1
set object 3215 polygon from \
  -2.07159, 67.7451 to \
  -0.03, 67.7451 to \
  -0.03, 35.5561 to \
  -2.07159, 35.5561 to \
  -2.07159, 67.7451 front fs empty border lc rgb '#549f' lw 0.1
set object 3216 polygon from \
  -2.05595, 67.7682 to \
  -0.03, 67.7682 to \
  -0.03, 35.5691 to \
  -2.05595, 35.5691 to \
  -2.05595, 67.7682 front fs empty border lc rgb '#549f' lw 0.1
set object 3217 polygon from \
  -2.03906, 67.7912 to \
  -0.03, 67.7912 to \
  -0.03, 35.5821 to \
  -2.03906, 35.5821 to \
  -2.03906, 67.7912 front fs empty border lc rgb '#549f' lw 0.1
set object 3218 polygon from \
  -2.02092, 67.8142 to \
  -0.03, 67.8142 to \
  -0.03, 35.5951 to \
  -2.02092, 35.5951 to \
  -2.02092, 67.8142 front fs empty border lc rgb '#549f' lw 0.1
set object 3219 polygon from \
  -2.00154, 67.8372 to \
  -0.03, 67.8372 to \
  -0.03, 35.6082 to \
  -2.00154, 35.6082 to \
  -2.00154, 67.8372 front fs empty border lc rgb '#549f' lw 0.1
set object 3220 polygon from \
  -1.98092, 67.8603 to \
  -0.03, 67.8603 to \
  -0.03, 35.6212 to \
  -1.98092, 35.6212 to \
  -1.98092, 67.8603 front fs empty border lc rgb '#549f' lw 0.1
set object 3221 polygon from \
  -1.95909, 67.8833 to \
  -0.03, 67.8833 to \
  -0.03, 35.6342 to \
  -1.95909, 35.6342 to \
  -1.95909, 67.8833 front fs empty border lc rgb '#549f' lw 0.1
set object 3222 polygon from \
  -1.93605, 67.9063 to \
  -0.03, 67.9063 to \
  -0.03, 35.6472 to \
  -1.93605, 35.6472 to \
  -1.93605, 67.9063 front fs empty border lc rgb '#549f' lw 0.1
set object 3223 polygon from \
  -1.91182, 67.9293 to \
  -0.03, 67.9293 to \
  -0.03, 35.6602 to \
  -1.91182, 35.6602 to \
  -1.91182, 67.9293 front fs empty border lc rgb '#549f' lw 0.1
set object 3224 polygon from \
  -1.88641, 67.9524 to \
  -0.03, 67.9524 to \
  -0.03, 35.6733 to \
  -1.88641, 35.6733 to \
  -1.88641, 67.9524 front fs empty border lc rgb '#549f' lw 0.1
set object 3225 polygon from \
  -1.86937, 67.9754 to \
  -0.03, 67.9754 to \
  -0.03, 35.6863 to \
  -1.86937, 35.6863 to \
  -1.86937, 67.9754 front fs empty border lc rgb '#549f' lw 0.1
set object 3226 polygon from \
  -1.88481, 67.9984 to \
  -0.03, 67.9984 to \
  -0.03, 35.6993 to \
  -1.88481, 35.6993 to \
  -1.88481, 67.9984 front fs empty border lc rgb '#549f' lw 0.1
set object 3227 polygon from \
  -1.89943, 68.0215 to \
  -0.03, 68.0215 to \
  -0.03, 35.7124 to \
  -1.89943, 35.7124 to \
  -1.89943, 68.0215 front fs empty border lc rgb '#549f' lw 0.1
set object 3228 polygon from \
  -1.91325, 68.0445 to \
  -0.03, 68.0445 to \
  -0.03, 35.7254 to \
  -1.91325, 35.7254 to \
  -1.91325, 68.0445 front fs empty border lc rgb '#549f' lw 0.1
set object 3229 polygon from \
  -1.92625, 68.0675 to \
  -0.03, 68.0675 to \
  -0.03, 35.7384 to \
  -1.92625, 35.7384 to \
  -1.92625, 68.0675 front fs empty border lc rgb '#549f' lw 0.1
set object 3230 polygon from \
  -1.93844, 68.0906 to \
  -0.03, 68.0906 to \
  -0.03, 35.7515 to \
  -1.93844, 35.7515 to \
  -1.93844, 68.0906 front fs empty border lc rgb '#549f' lw 0.1
set object 3231 polygon from \
  -1.94983, 68.1136 to \
  -0.03, 68.1136 to \
  -0.03, 35.7645 to \
  -1.94983, 35.7645 to \
  -1.94983, 68.1136 front fs empty border lc rgb '#549f' lw 0.1
set object 3232 polygon from \
  -1.96042, 68.1366 to \
  -0.03, 68.1366 to \
  -0.03, 35.7775 to \
  -1.96042, 35.7775 to \
  -1.96042, 68.1366 front fs empty border lc rgb '#549f' lw 0.1
set object 3233 polygon from \
  -1.97022, 68.1597 to \
  -0.03, 68.1597 to \
  -0.03, 35.7906 to \
  -1.97022, 35.7906 to \
  -1.97022, 68.1597 front fs empty border lc rgb '#549f' lw 0.1
set object 3234 polygon from \
  -1.97923, 68.1827 to \
  -0.03, 68.1827 to \
  -0.03, 35.8036 to \
  -1.97923, 35.8036 to \
  -1.97923, 68.1827 front fs empty border lc rgb '#549f' lw 0.1
set object 3235 polygon from \
  -1.98745, 68.2058 to \
  -0.03, 68.2058 to \
  -0.03, 35.8166 to \
  -1.98745, 35.8166 to \
  -1.98745, 68.2058 front fs empty border lc rgb '#549f' lw 0.1
set object 3236 polygon from \
  -1.9949, 68.2288 to \
  -0.03, 68.2288 to \
  -0.03, 35.8297 to \
  -1.9949, 35.8297 to \
  -1.9949, 68.2288 front fs empty border lc rgb '#549f' lw 0.1
set object 3237 polygon from \
  -2.00158, 68.2519 to \
  -0.03, 68.2519 to \
  -0.03, 35.8427 to \
  -2.00158, 35.8427 to \
  -2.00158, 68.2519 front fs empty border lc rgb '#549f' lw 0.1
set object 3238 polygon from \
  -2.00749, 68.2749 to \
  -0.03, 68.2749 to \
  -0.03, 35.8558 to \
  -2.00749, 35.8558 to \
  -2.00749, 68.2749 front fs empty border lc rgb '#549f' lw 0.1
set object 3239 polygon from \
  -2.01264, 68.298 to \
  -0.03, 68.298 to \
  -0.03, 35.8688 to \
  -2.01264, 35.8688 to \
  -2.01264, 68.298 front fs empty border lc rgb '#549f' lw 0.1
set object 3240 polygon from \
  -2.01704, 68.321 to \
  -0.03, 68.321 to \
  -0.03, 35.8819 to \
  -2.01704, 35.8819 to \
  -2.01704, 68.321 front fs empty border lc rgb '#549f' lw 0.1
set object 3241 polygon from \
  -2.02071, 68.3441 to \
  -0.03, 68.3441 to \
  -0.03, 35.8949 to \
  -2.02071, 35.8949 to \
  -2.02071, 68.3441 front fs empty border lc rgb '#549f' lw 0.1
set object 3242 polygon from \
  -2.02363, 68.3671 to \
  -0.03, 68.3671 to \
  -0.03, 35.9079 to \
  -2.02363, 35.9079 to \
  -2.02363, 68.3671 front fs empty border lc rgb '#549f' lw 0.1
set object 3243 polygon from \
  -2.02584, 68.3902 to \
  -0.03, 68.3902 to \
  -0.03, 35.921 to \
  -2.02584, 35.921 to \
  -2.02584, 68.3902 front fs empty border lc rgb '#549f' lw 0.1
set object 3244 polygon from \
  -2.02732, 68.4132 to \
  -0.03, 68.4132 to \
  -0.03, 35.934 to \
  -2.02732, 35.934 to \
  -2.02732, 68.4132 front fs empty border lc rgb '#549f' lw 0.1
set object 3245 polygon from \
  -2.0281, 68.4363 to \
  -0.03, 68.4363 to \
  -0.03, 35.9471 to \
  -2.0281, 35.9471 to \
  -2.0281, 68.4363 front fs empty border lc rgb '#549f' lw 0.1
set object 3246 polygon from \
  -2.02819, 68.4593 to \
  -0.03, 68.4593 to \
  -0.03, 35.9602 to \
  -2.02819, 35.9602 to \
  -2.02819, 68.4593 front fs empty border lc rgb '#549f' lw 0.1
set object 3247 polygon from \
  -2.02818, 68.4824 to \
  -0.03, 68.4824 to \
  -0.03, 35.9732 to \
  -2.02818, 35.9732 to \
  -2.02818, 68.4824 front fs empty border lc rgb '#549f' lw 0.1
set object 3248 polygon from \
  -2.02758, 68.5054 to \
  -0.03, 68.5054 to \
  -0.03, 35.9863 to \
  -2.02758, 35.9863 to \
  -2.02758, 68.5054 front fs empty border lc rgb '#549f' lw 0.1
set object 3249 polygon from \
  -2.0263, 68.5285 to \
  -0.03, 68.5285 to \
  -0.03, 35.9993 to \
  -2.0263, 35.9993 to \
  -2.0263, 68.5285 front fs empty border lc rgb '#549f' lw 0.1
set object 3250 polygon from \
  -2.02436, 68.5516 to \
  -0.03, 68.5516 to \
  -0.03, 36.0124 to \
  -2.02436, 36.0124 to \
  -2.02436, 68.5516 front fs empty border lc rgb '#549f' lw 0.1
set object 3251 polygon from \
  -2.02176, 68.5746 to \
  -0.03, 68.5746 to \
  -0.03, 36.0254 to \
  -2.02176, 36.0254 to \
  -2.02176, 68.5746 front fs empty border lc rgb '#549f' lw 0.1
set object 3252 polygon from \
  -2.01851, 68.5977 to \
  -0.03, 68.5977 to \
  -0.03, 36.0385 to \
  -2.01851, 36.0385 to \
  -2.01851, 68.5977 front fs empty border lc rgb '#549f' lw 0.1
set object 3253 polygon from \
  -2.01464, 68.6208 to \
  -0.03, 68.6208 to \
  -0.03, 36.0516 to \
  -2.01464, 36.0516 to \
  -2.01464, 68.6208 front fs empty border lc rgb '#549f' lw 0.1
set object 3254 polygon from \
  -2.01015, 68.6438 to \
  -0.03, 68.6438 to \
  -0.03, 36.0646 to \
  -2.01015, 36.0646 to \
  -2.01015, 68.6438 front fs empty border lc rgb '#549f' lw 0.1
set object 3255 polygon from \
  -2.00504, 68.6669 to \
  -0.03, 68.6669 to \
  -0.03, 36.0777 to \
  -2.00504, 36.0777 to \
  -2.00504, 68.6669 front fs empty border lc rgb '#549f' lw 0.1
set object 3256 polygon from \
  -1.99935, 68.69 to \
  -0.03, 68.69 to \
  -0.03, 36.0908 to \
  -1.99935, 36.0908 to \
  -1.99935, 68.69 front fs empty border lc rgb '#549f' lw 0.1
set object 3257 polygon from \
  -1.99674, 68.713 to \
  -0.03, 68.713 to \
  -0.03, 36.1038 to \
  -1.99674, 36.1038 to \
  -1.99674, 68.713 front fs empty border lc rgb '#549f' lw 0.1
set object 3258 polygon from \
  -2.03738, 68.7361 to \
  -0.03, 68.7361 to \
  -0.03, 36.1169 to \
  -2.03738, 36.1169 to \
  -2.03738, 68.7361 front fs empty border lc rgb '#549f' lw 0.1
set object 3259 polygon from \
  -2.0776, 68.7592 to \
  -0.03, 68.7592 to \
  -0.03, 36.13 to \
  -2.0776, 36.13 to \
  -2.0776, 68.7592 front fs empty border lc rgb '#549f' lw 0.1
set object 3260 polygon from \
  -2.11736, 68.7823 to \
  -0.03, 68.7823 to \
  -0.03, 36.143 to \
  -2.11736, 36.143 to \
  -2.11736, 68.7823 front fs empty border lc rgb '#549f' lw 0.1
set object 3261 polygon from \
  -2.15665, 68.8053 to \
  -0.03, 68.8053 to \
  -0.03, 36.1561 to \
  -2.15665, 36.1561 to \
  -2.15665, 68.8053 front fs empty border lc rgb '#549f' lw 0.1
set object 3262 polygon from \
  -2.19545, 68.8284 to \
  -0.03, 68.8284 to \
  -0.03, 36.1692 to \
  -2.19545, 36.1692 to \
  -2.19545, 68.8284 front fs empty border lc rgb '#549f' lw 0.1
set object 3263 polygon from \
  -2.23374, 68.8515 to \
  -0.03, 68.8515 to \
  -0.03, 36.1822 to \
  -2.23374, 36.1822 to \
  -2.23374, 68.8515 front fs empty border lc rgb '#549f' lw 0.1
set object 3264 polygon from \
  -2.2715, 68.8746 to \
  -0.03, 68.8746 to \
  -0.03, 36.1953 to \
  -2.2715, 36.1953 to \
  -2.2715, 68.8746 front fs empty border lc rgb '#549f' lw 0.1
set object 3265 polygon from \
  -2.30872, 68.8976 to \
  -0.03, 68.8976 to \
  -0.03, 36.2084 to \
  -2.30872, 36.2084 to \
  -2.30872, 68.8976 front fs empty border lc rgb '#549f' lw 0.1
set object 3266 polygon from \
  -2.34537, 68.9207 to \
  -0.03, 68.9207 to \
  -0.03, 36.2215 to \
  -2.34537, 36.2215 to \
  -2.34537, 68.9207 front fs empty border lc rgb '#549f' lw 0.1
set object 3267 polygon from \
  -2.38144, 68.9438 to \
  -0.03, 68.9438 to \
  -0.03, 36.2346 to \
  -2.38144, 36.2346 to \
  -2.38144, 68.9438 front fs empty border lc rgb '#549f' lw 0.1
set object 3268 polygon from \
  -2.4169, 68.9669 to \
  -0.03, 68.9669 to \
  -0.03, 36.2476 to \
  -2.4169, 36.2476 to \
  -2.4169, 68.9669 front fs empty border lc rgb '#549f' lw 0.1
set object 3269 polygon from \
  -2.45175, 68.99 to \
  -0.03, 68.99 to \
  -0.03, 36.2607 to \
  -2.45175, 36.2607 to \
  -2.45175, 68.99 front fs empty border lc rgb '#549f' lw 0.1
set object 3270 polygon from \
  -2.48596, 69.0131 to \
  -0.03, 69.0131 to \
  -0.03, 36.2738 to \
  -2.48596, 36.2738 to \
  -2.48596, 69.0131 front fs empty border lc rgb '#549f' lw 0.1
set object 3271 polygon from \
  -2.51952, 69.0362 to \
  -0.03, 69.0362 to \
  -0.03, 36.2869 to \
  -2.51952, 36.2869 to \
  -2.51952, 69.0362 front fs empty border lc rgb '#549f' lw 0.1
set object 3272 polygon from \
  -2.55241, 69.0592 to \
  -0.03, 69.0592 to \
  -0.03, 36.3 to \
  -2.55241, 36.3 to \
  -2.55241, 69.0592 front fs empty border lc rgb '#549f' lw 0.1
set object 3273 polygon from \
  -2.58461, 69.0823 to \
  -0.03, 69.0823 to \
  -0.03, 36.3131 to \
  -2.58461, 36.3131 to \
  -2.58461, 69.0823 front fs empty border lc rgb '#549f' lw 0.1
set object 3274 polygon from \
  -2.61611, 69.1054 to \
  -0.03, 69.1054 to \
  -0.03, 36.3261 to \
  -2.61611, 36.3261 to \
  -2.61611, 69.1054 front fs empty border lc rgb '#549f' lw 0.1
set object 3275 polygon from \
  -2.64689, 69.1285 to \
  -0.03, 69.1285 to \
  -0.03, 36.3392 to \
  -2.64689, 36.3392 to \
  -2.64689, 69.1285 front fs empty border lc rgb '#549f' lw 0.1
set object 3276 polygon from \
  -2.67693, 69.1516 to \
  -0.03, 69.1516 to \
  -0.03, 36.3523 to \
  -2.67693, 36.3523 to \
  -2.67693, 69.1516 front fs empty border lc rgb '#549f' lw 0.1
set object 3277 polygon from \
  -2.70622, 69.1747 to \
  -0.03, 69.1747 to \
  -0.03, 36.3654 to \
  -2.70622, 36.3654 to \
  -2.70622, 69.1747 front fs empty border lc rgb '#549f' lw 0.1
set object 3278 polygon from \
  -2.73474, 69.1978 to \
  -0.03, 69.1978 to \
  -0.03, 36.3785 to \
  -2.73474, 36.3785 to \
  -2.73474, 69.1978 front fs empty border lc rgb '#549f' lw 0.1
set object 3279 polygon from \
  -2.76247, 69.2209 to \
  -0.03, 69.2209 to \
  -0.03, 36.3916 to \
  -2.76247, 36.3916 to \
  -2.76247, 69.2209 front fs empty border lc rgb '#549f' lw 0.1
set object 3280 polygon from \
  -2.78941, 69.244 to \
  -0.03, 69.244 to \
  -0.03, 36.4047 to \
  -2.78941, 36.4047 to \
  -2.78941, 69.244 front fs empty border lc rgb '#549f' lw 0.1
set object 3281 polygon from \
  -2.81553, 69.2671 to \
  -0.03, 69.2671 to \
  -0.03, 36.4178 to \
  -2.81553, 36.4178 to \
  -2.81553, 69.2671 front fs empty border lc rgb '#549f' lw 0.1
set object 3282 polygon from \
  -2.84083, 69.2902 to \
  -0.03, 69.2902 to \
  -0.03, 36.4309 to \
  -2.84083, 36.4309 to \
  -2.84083, 69.2902 front fs empty border lc rgb '#549f' lw 0.1
set object 3283 polygon from \
  -2.86528, 69.3133 to \
  -0.03, 69.3133 to \
  -0.03, 36.444 to \
  -2.86528, 36.444 to \
  -2.86528, 69.3133 front fs empty border lc rgb '#549f' lw 0.1
set object 3284 polygon from \
  -2.88888, 69.3364 to \
  -0.03, 69.3364 to \
  -0.03, 36.4571 to \
  -2.88888, 36.4571 to \
  -2.88888, 69.3364 front fs empty border lc rgb '#549f' lw 0.1
set object 3285 polygon from \
  -2.91161, 69.3595 to \
  -0.03, 69.3595 to \
  -0.03, 36.4702 to \
  -2.91161, 36.4702 to \
  -2.91161, 69.3595 front fs empty border lc rgb '#549f' lw 0.1
set object 3286 polygon from \
  -2.93346, 69.3826 to \
  -0.03, 69.3826 to \
  -0.03, 36.4833 to \
  -2.93346, 36.4833 to \
  -2.93346, 69.3826 front fs empty border lc rgb '#549f' lw 0.1
set object 3287 polygon from \
  -2.95441, 69.4057 to \
  -0.03, 69.4057 to \
  -0.03, 36.4964 to \
  -2.95441, 36.4964 to \
  -2.95441, 69.4057 front fs empty border lc rgb '#549f' lw 0.1
set object 3288 polygon from \
  -2.97446, 69.4288 to \
  -0.03, 69.4288 to \
  -0.03, 36.5095 to \
  -2.97446, 36.5095 to \
  -2.97446, 69.4288 front fs empty border lc rgb '#549f' lw 0.1
set object 3289 polygon from \
  -2.99359, 69.452 to \
  -0.03, 69.452 to \
  -0.03, 36.5226 to \
  -2.99359, 36.5226 to \
  -2.99359, 69.452 front fs empty border lc rgb '#549f' lw 0.1
set object 3290 polygon from \
  -3.01178, 69.4751 to \
  -0.03, 69.4751 to \
  -0.03, 36.5357 to \
  -3.01178, 36.5357 to \
  -3.01178, 69.4751 front fs empty border lc rgb '#549f' lw 0.1
set object 3291 polygon from \
  -3.02903, 69.4982 to \
  -0.03, 69.4982 to \
  -0.03, 36.5488 to \
  -3.02903, 36.5488 to \
  -3.02903, 69.4982 front fs empty border lc rgb '#549f' lw 0.1
set object 3292 polygon from \
  -3.05096, 69.5213 to \
  -0.03, 69.5213 to \
  -0.03, 36.5619 to \
  -3.05096, 36.5619 to \
  -3.05096, 69.5213 front fs empty border lc rgb '#549f' lw 0.1
set object 3293 polygon from \
  -3.07203, 69.5444 to \
  -0.03, 69.5444 to \
  -0.03, 36.5751 to \
  -3.07203, 36.5751 to \
  -3.07203, 69.5444 front fs empty border lc rgb '#549f' lw 0.1
set object 3294 polygon from \
  -3.0921, 69.5675 to \
  -0.03, 69.5675 to \
  -0.03, 36.5882 to \
  -3.0921, 36.5882 to \
  -3.0921, 69.5675 front fs empty border lc rgb '#549f' lw 0.1
set object 3295 polygon from \
  -3.11114, 69.5906 to \
  -0.03, 69.5906 to \
  -0.03, 36.6013 to \
  -3.11114, 36.6013 to \
  -3.11114, 69.5906 front fs empty border lc rgb '#549f' lw 0.1
set object 3296 polygon from \
  -3.12916, 69.6138 to \
  -0.03, 69.6138 to \
  -0.03, 36.6144 to \
  -3.12916, 36.6144 to \
  -3.12916, 69.6138 front fs empty border lc rgb '#549f' lw 0.1
set object 3297 polygon from \
  -3.14615, 69.6369 to \
  -0.03, 69.6369 to \
  -0.03, 36.6275 to \
  -3.14615, 36.6275 to \
  -3.14615, 69.6369 front fs empty border lc rgb '#549f' lw 0.1
set object 3298 polygon from \
  -3.16209, 69.66 to \
  -0.03, 69.66 to \
  -0.03, 36.6406 to \
  -3.16209, 36.6406 to \
  -3.16209, 69.66 front fs empty border lc rgb '#549f' lw 0.1
set object 3299 polygon from \
  -3.17698, 69.6831 to \
  -0.03, 69.6831 to \
  -0.03, 36.6538 to \
  -3.17698, 36.6538 to \
  -3.17698, 69.6831 front fs empty border lc rgb '#549f' lw 0.1
set object 3300 polygon from \
  -3.19081, 69.7063 to \
  -0.03, 69.7063 to \
  -0.03, 36.6669 to \
  -3.19081, 36.6669 to \
  -3.19081, 69.7063 front fs empty border lc rgb '#549f' lw 0.1
set object 3301 polygon from \
  -3.20357, 69.7294 to \
  -0.03, 69.7294 to \
  -0.03, 36.68 to \
  -3.20357, 36.68 to \
  -3.20357, 69.7294 front fs empty border lc rgb '#549f' lw 0.1
set object 3302 polygon from \
  -3.21527, 69.7525 to \
  -0.03, 69.7525 to \
  -0.03, 36.6931 to \
  -3.21527, 36.6931 to \
  -3.21527, 69.7525 front fs empty border lc rgb '#549f' lw 0.1
set object 3303 polygon from \
  -3.22588, 69.7756 to \
  -0.03, 69.7756 to \
  -0.03, 36.7062 to \
  -3.22588, 36.7062 to \
  -3.22588, 69.7756 front fs empty border lc rgb '#549f' lw 0.1
set object 3304 polygon from \
  -3.23542, 69.7988 to \
  -0.03, 69.7988 to \
  -0.03, 36.7194 to \
  -3.23542, 36.7194 to \
  -3.23542, 69.7988 front fs empty border lc rgb '#549f' lw 0.1
set object 3305 polygon from \
  -3.24386, 69.8219 to \
  -0.03, 69.8219 to \
  -0.03, 36.7325 to \
  -3.24386, 36.7325 to \
  -3.24386, 69.8219 front fs empty border lc rgb '#549f' lw 0.1
set object 3306 polygon from \
  -3.25122, 69.845 to \
  -0.03, 69.845 to \
  -0.03, 36.7456 to \
  -3.25122, 36.7456 to \
  -3.25122, 69.845 front fs empty border lc rgb '#549f' lw 0.1
set object 3307 polygon from \
  -3.25748, 69.8682 to \
  -0.03, 69.8682 to \
  -0.03, 36.7588 to \
  -3.25748, 36.7588 to \
  -3.25748, 69.8682 front fs empty border lc rgb '#549f' lw 0.1
set object 3308 polygon from \
  -3.26264, 69.8913 to \
  -0.03, 69.8913 to \
  -0.03, 36.7719 to \
  -3.26264, 36.7719 to \
  -3.26264, 69.8913 front fs empty border lc rgb '#549f' lw 0.1
set object 3309 polygon from \
  -3.2667, 69.9144 to \
  -0.03, 69.9144 to \
  -0.03, 36.785 to \
  -3.2667, 36.785 to \
  -3.2667, 69.9144 front fs empty border lc rgb '#549f' lw 0.1
set object 3310 polygon from \
  -3.26966, 69.9376 to \
  -0.03, 69.9376 to \
  -0.03, 36.7982 to \
  -3.26966, 36.7982 to \
  -3.26966, 69.9376 front fs empty border lc rgb '#549f' lw 0.1
set object 3311 polygon from \
  -3.27151, 69.9607 to \
  -0.03, 69.9607 to \
  -0.03, 36.8113 to \
  -3.27151, 36.8113 to \
  -3.27151, 69.9607 front fs empty border lc rgb '#549f' lw 0.1
set object 3312 polygon from \
  -3.27226, 69.9838 to \
  -0.03, 69.9838 to \
  -0.03, 36.8244 to \
  -3.27226, 36.8244 to \
  -3.27226, 69.9838 front fs empty border lc rgb '#549f' lw 0.1
set object 3313 polygon from \
  -3.27654, 70.007 to \
  -0.03, 70.007 to \
  -0.03, 36.8376 to \
  -3.27654, 36.8376 to \
  -3.27654, 70.007 front fs empty border lc rgb '#549f' lw 0.1
set object 3314 polygon from \
  -3.28016, 70.0301 to \
  -0.03, 70.0301 to \
  -0.03, 36.8507 to \
  -3.28016, 36.8507 to \
  -3.28016, 70.0301 front fs empty border lc rgb '#549f' lw 0.1
set object 3315 polygon from \
  -3.2827, 70.0533 to \
  -0.03, 70.0533 to \
  -0.03, 36.8638 to \
  -3.2827, 36.8638 to \
  -3.2827, 70.0533 front fs empty border lc rgb '#549f' lw 0.1
set object 3316 polygon from \
  -3.28415, 70.0764 to \
  -0.03, 70.0764 to \
  -0.03, 36.877 to \
  -3.28415, 36.877 to \
  -3.28415, 70.0764 front fs empty border lc rgb '#549f' lw 0.1
set object 3317 polygon from \
  -3.28452, 70.0996 to \
  -0.03, 70.0996 to \
  -0.03, 36.8901 to \
  -3.28452, 36.8901 to \
  -3.28452, 70.0996 front fs empty border lc rgb '#549f' lw 0.1
set object 3318 polygon from \
  -3.28452, 70.1227 to \
  -0.03, 70.1227 to \
  -0.03, 36.9033 to \
  -3.28452, 36.9033 to \
  -3.28452, 70.1227 front fs empty border lc rgb '#549f' lw 0.1
set object 3319 polygon from \
  -3.2838, 70.1459 to \
  -0.03, 70.1459 to \
  -0.03, 36.9164 to \
  -3.2838, 36.9164 to \
  -3.2838, 70.1459 front fs empty border lc rgb '#549f' lw 0.1
set object 3320 polygon from \
  -3.28199, 70.169 to \
  -0.03, 70.169 to \
  -0.03, 36.9296 to \
  -3.28199, 36.9296 to \
  -3.28199, 70.169 front fs empty border lc rgb '#549f' lw 0.1
set object 3321 polygon from \
  -3.28612, 70.1922 to \
  -0.03, 70.1922 to \
  -0.03, 36.9427 to \
  -3.28612, 36.9427 to \
  -3.28612, 70.1922 front fs empty border lc rgb '#549f' lw 0.1
set object 3322 polygon from \
  -3.29189, 70.2153 to \
  -0.03, 70.2153 to \
  -0.03, 36.9558 to \
  -3.29189, 36.9558 to \
  -3.29189, 70.2153 front fs empty border lc rgb '#549f' lw 0.1
set object 3323 polygon from \
  -3.29656, 70.2385 to \
  -0.03, 70.2385 to \
  -0.03, 36.969 to \
  -3.29656, 36.969 to \
  -3.29656, 70.2385 front fs empty border lc rgb '#549f' lw 0.1
set object 3324 polygon from \
  -3.30011, 70.2616 to \
  -0.03, 70.2616 to \
  -0.03, 36.9821 to \
  -3.30011, 36.9821 to \
  -3.30011, 70.2616 front fs empty border lc rgb '#549f' lw 0.1
set object 3325 polygon from \
  -3.30256, 70.2848 to \
  -0.03, 70.2848 to \
  -0.03, 36.9953 to \
  -3.30256, 36.9953 to \
  -3.30256, 70.2848 front fs empty border lc rgb '#549f' lw 0.1
set object 3326 polygon from \
  -3.3039, 70.3079 to \
  -0.03, 70.3079 to \
  -0.03, 37.0085 to \
  -3.3039, 37.0085 to \
  -3.3039, 70.3079 front fs empty border lc rgb '#549f' lw 0.1
set object 3327 polygon from \
  -3.30413, 70.3311 to \
  -0.03, 70.3311 to \
  -0.03, 37.0216 to \
  -3.30413, 37.0216 to \
  -3.30413, 70.3311 front fs empty border lc rgb '#549f' lw 0.1
set object 3328 polygon from \
  -3.30413, 70.3542 to \
  -0.03, 70.3542 to \
  -0.03, 37.0348 to \
  -3.30413, 37.0348 to \
  -3.30413, 70.3542 front fs empty border lc rgb '#549f' lw 0.1
set object 3329 polygon from \
  -3.30324, 70.3774 to \
  -0.03, 70.3774 to \
  -0.03, 37.0479 to \
  -3.30324, 37.0479 to \
  -3.30324, 70.3774 front fs empty border lc rgb '#549f' lw 0.1
set object 3330 polygon from \
  -3.30125, 70.4006 to \
  -0.03, 70.4006 to \
  -0.03, 37.0611 to \
  -3.30125, 37.0611 to \
  -3.30125, 70.4006 front fs empty border lc rgb '#549f' lw 0.1
set object 3331 polygon from \
  -3.29815, 70.4237 to \
  -0.03, 70.4237 to \
  -0.03, 37.0742 to \
  -3.29815, 37.0742 to \
  -3.29815, 70.4237 front fs empty border lc rgb '#549f' lw 0.1
set object 3332 polygon from \
  -3.29394, 70.4469 to \
  -0.03, 70.4469 to \
  -0.03, 37.0874 to \
  -3.29394, 37.0874 to \
  -3.29394, 70.4469 front fs empty border lc rgb '#549f' lw 0.1
set object 3333 polygon from \
  -3.28864, 70.4701 to \
  -0.03, 70.4701 to \
  -0.03, 37.1006 to \
  -3.28864, 37.1006 to \
  -3.28864, 70.4701 front fs empty border lc rgb '#549f' lw 0.1
set object 3334 polygon from \
  -3.28223, 70.4932 to \
  -0.03, 70.4932 to \
  -0.03, 37.1137 to \
  -3.28223, 37.1137 to \
  -3.28223, 70.4932 front fs empty border lc rgb '#549f' lw 0.1
set object 3335 polygon from \
  -3.27472, 70.5164 to \
  -0.03, 70.5164 to \
  -0.03, 37.1269 to \
  -3.27472, 37.1269 to \
  -3.27472, 70.5164 front fs empty border lc rgb '#549f' lw 0.1
set object 3336 polygon from \
  -3.26612, 70.5396 to \
  -0.03, 70.5396 to \
  -0.03, 37.1401 to \
  -3.26612, 37.1401 to \
  -3.26612, 70.5396 front fs empty border lc rgb '#549f' lw 0.1
set object 3337 polygon from \
  -3.25643, 70.5627 to \
  -0.03, 70.5627 to \
  -0.03, 37.1532 to \
  -3.25643, 37.1532 to \
  -3.25643, 70.5627 front fs empty border lc rgb '#549f' lw 0.1
set object 3338 polygon from \
  -3.24566, 70.5859 to \
  -0.03, 70.5859 to \
  -0.03, 37.1664 to \
  -3.24566, 37.1664 to \
  -3.24566, 70.5859 front fs empty border lc rgb '#549f' lw 0.1
set object 3339 polygon from \
  -3.23381, 70.6091 to \
  -0.03, 70.6091 to \
  -0.03, 37.1796 to \
  -3.23381, 37.1796 to \
  -3.23381, 70.6091 front fs empty border lc rgb '#549f' lw 0.1
set object 3340 polygon from \
  -3.22089, 70.6323 to \
  -0.03, 70.6323 to \
  -0.03, 37.1927 to \
  -3.22089, 37.1927 to \
  -3.22089, 70.6323 front fs empty border lc rgb '#549f' lw 0.1
set object 3341 polygon from \
  -3.2069, 70.6554 to \
  -0.03, 70.6554 to \
  -0.03, 37.2059 to \
  -3.2069, 37.2059 to \
  -3.2069, 70.6554 front fs empty border lc rgb '#549f' lw 0.1
set object 3342 polygon from \
  -3.19186, 70.6786 to \
  -0.03, 70.6786 to \
  -0.03, 37.2191 to \
  -3.19186, 37.2191 to \
  -3.19186, 70.6786 front fs empty border lc rgb '#549f' lw 0.1
set object 3343 polygon from \
  -3.17576, 70.7018 to \
  -0.03, 70.7018 to \
  -0.03, 37.2322 to \
  -3.17576, 37.2322 to \
  -3.17576, 70.7018 front fs empty border lc rgb '#549f' lw 0.1
set object 3344 polygon from \
  -3.15862, 70.725 to \
  -0.03, 70.725 to \
  -0.03, 37.2454 to \
  -3.15862, 37.2454 to \
  -3.15862, 70.725 front fs empty border lc rgb '#549f' lw 0.1
set object 3345 polygon from \
  -3.14045, 70.7481 to \
  -0.03, 70.7481 to \
  -0.03, 37.2586 to \
  -3.14045, 37.2586 to \
  -3.14045, 70.7481 front fs empty border lc rgb '#549f' lw 0.1
set object 3346 polygon from \
  -3.12124, 70.7713 to \
  -0.03, 70.7713 to \
  -0.03, 37.2718 to \
  -3.12124, 37.2718 to \
  -3.12124, 70.7713 front fs empty border lc rgb '#549f' lw 0.1
set object 3347 polygon from \
  -3.10103, 70.7945 to \
  -0.03, 70.7945 to \
  -0.03, 37.285 to \
  -3.10103, 37.285 to \
  -3.10103, 70.7945 front fs empty border lc rgb '#549f' lw 0.1
set object 3348 polygon from \
  -3.0798, 70.8177 to \
  -0.03, 70.8177 to \
  -0.03, 37.2981 to \
  -3.0798, 37.2981 to \
  -3.0798, 70.8177 front fs empty border lc rgb '#549f' lw 0.1
set object 3349 polygon from \
  -3.05758, 70.8409 to \
  -0.03, 70.8409 to \
  -0.03, 37.3113 to \
  -3.05758, 37.3113 to \
  -3.05758, 70.8409 front fs empty border lc rgb '#549f' lw 0.1
set object 3350 polygon from \
  -3.03438, 70.8641 to \
  -0.03, 70.8641 to \
  -0.03, 37.3245 to \
  -3.03438, 37.3245 to \
  -3.03438, 70.8641 front fs empty border lc rgb '#549f' lw 0.1
set object 3351 polygon from \
  -3.01019, 70.8873 to \
  -0.03, 70.8873 to \
  -0.03, 37.3377 to \
  -3.01019, 37.3377 to \
  -3.01019, 70.8873 front fs empty border lc rgb '#549f' lw 0.1
set object 3352 polygon from \
  -2.98505, 70.9104 to \
  -0.03, 70.9104 to \
  -0.03, 37.3509 to \
  -2.98505, 37.3509 to \
  -2.98505, 70.9104 front fs empty border lc rgb '#549f' lw 0.1
set object 3353 polygon from \
  -2.95895, 70.9336 to \
  -0.03, 70.9336 to \
  -0.03, 37.3641 to \
  -2.95895, 37.3641 to \
  -2.95895, 70.9336 front fs empty border lc rgb '#549f' lw 0.1
set object 3354 polygon from \
  -2.93192, 70.9568 to \
  -0.03, 70.9568 to \
  -0.03, 37.3772 to \
  -2.93192, 37.3772 to \
  -2.93192, 70.9568 front fs empty border lc rgb '#549f' lw 0.1
set object 3355 polygon from \
  -2.90396, 70.98 to \
  -0.03, 70.98 to \
  -0.03, 37.3904 to \
  -2.90396, 37.3904 to \
  -2.90396, 70.98 front fs empty border lc rgb '#549f' lw 0.1
set object 3356 polygon from \
  -2.87509, 71.0032 to \
  -0.03, 71.0032 to \
  -0.03, 37.4036 to \
  -2.87509, 37.4036 to \
  -2.87509, 71.0032 front fs empty border lc rgb '#549f' lw 0.1
set object 3357 polygon from \
  -2.84532, 71.0264 to \
  -0.03, 71.0264 to \
  -0.03, 37.4168 to \
  -2.84532, 37.4168 to \
  -2.84532, 71.0264 front fs empty border lc rgb '#549f' lw 0.1
set object 3358 polygon from \
  -2.81466, 71.0496 to \
  -0.03, 71.0496 to \
  -0.03, 37.43 to \
  -2.81466, 37.43 to \
  -2.81466, 71.0496 front fs empty border lc rgb '#549f' lw 0.1
set object 3359 polygon from \
  -2.78313, 71.0728 to \
  -0.03, 71.0728 to \
  -0.03, 37.4432 to \
  -2.78313, 37.4432 to \
  -2.78313, 71.0728 front fs empty border lc rgb '#549f' lw 0.1
set object 3360 polygon from \
  -2.75075, 71.096 to \
  -0.03, 71.096 to \
  -0.03, 37.4564 to \
  -2.75075, 37.4564 to \
  -2.75075, 71.096 front fs empty border lc rgb '#549f' lw 0.1
set object 3361 polygon from \
  -2.71753, 71.1192 to \
  -0.03, 71.1192 to \
  -0.03, 37.4696 to \
  -2.71753, 37.4696 to \
  -2.71753, 71.1192 front fs empty border lc rgb '#549f' lw 0.1
set object 3362 polygon from \
  -2.68348, 71.1424 to \
  -0.03, 71.1424 to \
  -0.03, 37.4828 to \
  -2.68348, 37.4828 to \
  -2.68348, 71.1424 front fs empty border lc rgb '#549f' lw 0.1
set object 3363 polygon from \
  -2.64863, 71.1656 to \
  -0.03, 71.1656 to \
  -0.03, 37.496 to \
  -2.64863, 37.496 to \
  -2.64863, 71.1656 front fs empty border lc rgb '#549f' lw 0.1
set object 3364 polygon from \
  -2.61298, 71.1888 to \
  -0.03, 71.1888 to \
  -0.03, 37.5092 to \
  -2.61298, 37.5092 to \
  -2.61298, 71.1888 front fs empty border lc rgb '#549f' lw 0.1
set object 3365 polygon from \
  -2.57656, 71.212 to \
  -0.03, 71.212 to \
  -0.03, 37.5224 to \
  -2.57656, 37.5224 to \
  -2.57656, 71.212 front fs empty border lc rgb '#549f' lw 0.1
set object 3366 polygon from \
  -2.53937, 71.2352 to \
  -0.03, 71.2352 to \
  -0.03, 37.5356 to \
  -2.53937, 37.5356 to \
  -2.53937, 71.2352 front fs empty border lc rgb '#549f' lw 0.1
set object 3367 polygon from \
  -2.50144, 71.2584 to \
  -0.03, 71.2584 to \
  -0.03, 37.5488 to \
  -2.50144, 37.5488 to \
  -2.50144, 71.2584 front fs empty border lc rgb '#549f' lw 0.1
set object 3368 polygon from \
  -2.46279, 71.2816 to \
  -0.03, 71.2816 to \
  -0.03, 37.562 to \
  -2.46279, 37.562 to \
  -2.46279, 71.2816 front fs empty border lc rgb '#549f' lw 0.1
set object 3369 polygon from \
  -2.42344, 71.3049 to \
  -0.03, 71.3049 to \
  -0.03, 37.5752 to \
  -2.42344, 37.5752 to \
  -2.42344, 71.3049 front fs empty border lc rgb '#549f' lw 0.1
set object 3370 polygon from \
  -2.38339, 71.3281 to \
  -0.03, 71.3281 to \
  -0.03, 37.5884 to \
  -2.38339, 37.5884 to \
  -2.38339, 71.3281 front fs empty border lc rgb '#549f' lw 0.1
set object 3371 polygon from \
  -2.34267, 71.3513 to \
  -0.03, 71.3513 to \
  -0.03, 37.6016 to \
  -2.34267, 37.6016 to \
  -2.34267, 71.3513 front fs empty border lc rgb '#549f' lw 0.1
set object 3372 polygon from \
  -2.3013, 71.3745 to \
  -0.03, 71.3745 to \
  -0.03, 37.6148 to \
  -2.3013, 37.6148 to \
  -2.3013, 71.3745 front fs empty border lc rgb '#549f' lw 0.1
set object 3373 polygon from \
  -2.2593, 71.3977 to \
  -0.03, 71.3977 to \
  -0.03, 37.6281 to \
  -2.2593, 37.6281 to \
  -2.2593, 71.3977 front fs empty border lc rgb '#549f' lw 0.1
set object 3374 polygon from \
  -2.21668, 71.4209 to \
  -0.03, 71.4209 to \
  -0.03, 37.6413 to \
  -2.21668, 37.6413 to \
  -2.21668, 71.4209 front fs empty border lc rgb '#549f' lw 0.1
set object 3375 polygon from \
  -2.17347, 71.4441 to \
  -0.03, 71.4441 to \
  -0.03, 37.6545 to \
  -2.17347, 37.6545 to \
  -2.17347, 71.4441 front fs empty border lc rgb '#549f' lw 0.1
set object 3376 polygon from \
  -2.12968, 71.4674 to \
  -0.03, 71.4674 to \
  -0.03, 37.6677 to \
  -2.12968, 37.6677 to \
  -2.12968, 71.4674 front fs empty border lc rgb '#549f' lw 0.1
set object 3377 polygon from \
  -2.08534, 71.4906 to \
  -0.03, 71.4906 to \
  -0.03, 37.6809 to \
  -2.08534, 37.6809 to \
  -2.08534, 71.4906 front fs empty border lc rgb '#549f' lw 0.1
set object 3378 polygon from \
  -2.04046, 71.5138 to \
  -0.03, 71.5138 to \
  -0.03, 37.6941 to \
  -2.04046, 37.6941 to \
  -2.04046, 71.5138 front fs empty border lc rgb '#549f' lw 0.1
set object 3379 polygon from \
  -1.99506, 71.537 to \
  -0.03, 71.537 to \
  -0.03, 37.7074 to \
  -1.99506, 37.7074 to \
  -1.99506, 71.537 front fs empty border lc rgb '#549f' lw 0.1
set object 3380 polygon from \
  -1.94917, 71.5603 to \
  -0.03, 71.5603 to \
  -0.03, 37.7206 to \
  -1.94917, 37.7206 to \
  -1.94917, 71.5603 front fs empty border lc rgb '#549f' lw 0.1
set object 3381 polygon from \
  -1.90281, 71.5835 to \
  -0.03, 71.5835 to \
  -0.03, 37.7338 to \
  -1.90281, 37.7338 to \
  -1.90281, 71.5835 front fs empty border lc rgb '#549f' lw 0.1
set object 3382 polygon from \
  -1.85598, 71.6067 to \
  -0.03, 71.6067 to \
  -0.03, 37.747 to \
  -1.85598, 37.747 to \
  -1.85598, 71.6067 front fs empty border lc rgb '#549f' lw 0.1
set object 3383 polygon from \
  -1.80873, 71.6299 to \
  -0.03, 71.6299 to \
  -0.03, 37.7602 to \
  -1.80873, 37.7602 to \
  -1.80873, 71.6299 front fs empty border lc rgb '#549f' lw 0.1
set object 3384 polygon from \
  -1.76106, 71.6532 to \
  -0.03, 71.6532 to \
  -0.03, 37.7735 to \
  -1.76106, 37.7735 to \
  -1.76106, 71.6532 front fs empty border lc rgb '#549f' lw 0.1
set object 3385 polygon from \
  -1.71299, 71.6764 to \
  -0.03, 71.6764 to \
  -0.03, 37.7867 to \
  -1.71299, 37.7867 to \
  -1.71299, 71.6764 front fs empty border lc rgb '#549f' lw 0.1
set object 3386 polygon from \
  -1.66456, 71.6996 to \
  -0.03, 71.6996 to \
  -0.03, 37.7999 to \
  -1.66456, 37.7999 to \
  -1.66456, 71.6996 front fs empty border lc rgb '#549f' lw 0.1
set object 3387 polygon from \
  -1.66487, 71.7229 to \
  -0.03, 71.7229 to \
  -0.03, 37.8132 to \
  -1.66487, 37.8132 to \
  -1.66487, 71.7229 front fs empty border lc rgb '#549f' lw 0.1
set object 3388 polygon from \
  -1.66488, 71.7461 to \
  -0.03, 71.7461 to \
  -0.03, 37.8264 to \
  -1.66488, 37.8264 to \
  -1.66488, 71.7461 front fs empty border lc rgb '#549f' lw 0.1
set object 3389 polygon from \
  -1.66479, 71.7693 to \
  -0.03, 71.7693 to \
  -0.03, 37.8396 to \
  -1.66479, 37.8396 to \
  -1.66479, 71.7693 front fs empty border lc rgb '#549f' lw 0.1
set object 3390 polygon from \
  -1.66422, 71.7926 to \
  -0.03, 71.7926 to \
  -0.03, 37.8529 to \
  -1.66422, 37.8529 to \
  -1.66422, 71.7926 front fs empty border lc rgb '#549f' lw 0.1
set object 3391 polygon from \
  -1.66317, 71.8158 to \
  -0.03, 71.8158 to \
  -0.03, 37.8661 to \
  -1.66317, 37.8661 to \
  -1.66317, 71.8158 front fs empty border lc rgb '#549f' lw 0.1
set object 3392 polygon from \
  -1.66162, 71.839 to \
  -0.03, 71.839 to \
  -0.03, 37.8793 to \
  -1.66162, 37.8793 to \
  -1.66162, 71.839 front fs empty border lc rgb '#549f' lw 0.1
set object 3393 polygon from \
  -1.65956, 71.8623 to \
  -0.03, 71.8623 to \
  -0.03, 37.8926 to \
  -1.65956, 37.8926 to \
  -1.65956, 71.8623 front fs empty border lc rgb '#549f' lw 0.1
set object 3394 polygon from \
  -1.65698, 71.8855 to \
  -0.03, 71.8855 to \
  -0.03, 37.9058 to \
  -1.65698, 37.9058 to \
  -1.65698, 71.8855 front fs empty border lc rgb '#549f' lw 0.1
set object 3395 polygon from \
  -1.65387, 71.9088 to \
  -0.03, 71.9088 to \
  -0.03, 37.919 to \
  -1.65387, 37.919 to \
  -1.65387, 71.9088 front fs empty border lc rgb '#549f' lw 0.1
set object 3396 polygon from \
  -1.65022, 71.932 to \
  -0.03, 71.932 to \
  -0.03, 37.9323 to \
  -1.65022, 37.9323 to \
  -1.65022, 71.932 front fs empty border lc rgb '#549f' lw 0.1
set object 3397 polygon from \
  -1.64602, 71.9553 to \
  -0.03, 71.9553 to \
  -0.03, 37.9455 to \
  -1.64602, 37.9455 to \
  -1.64602, 71.9553 front fs empty border lc rgb '#549f' lw 0.1
set object 3398 polygon from \
  -1.64126, 71.9785 to \
  -0.03, 71.9785 to \
  -0.03, 37.9588 to \
  -1.64126, 37.9588 to \
  -1.64126, 71.9785 front fs empty border lc rgb '#549f' lw 0.1
set object 3399 polygon from \
  -1.63593, 72.0018 to \
  -0.03, 72.0018 to \
  -0.03, 37.972 to \
  -1.63593, 37.972 to \
  -1.63593, 72.0018 front fs empty border lc rgb '#549f' lw 0.1
set object 3400 polygon from \
  -1.63003, 72.025 to \
  -0.03, 72.025 to \
  -0.03, 37.9853 to \
  -1.63003, 37.9853 to \
  -1.63003, 72.025 front fs empty border lc rgb '#549f' lw 0.1
set object 3401 polygon from \
  -1.62354, 72.0483 to \
  -0.03, 72.0483 to \
  -0.03, 37.9985 to \
  -1.62354, 37.9985 to \
  -1.62354, 72.0483 front fs empty border lc rgb '#549f' lw 0.1
set object 3402 polygon from \
  -1.61646, 72.0715 to \
  -0.03, 72.0715 to \
  -0.03, 38.0117 to \
  -1.61646, 38.0117 to \
  -1.61646, 72.0715 front fs empty border lc rgb '#549f' lw 0.1
set object 3403 polygon from \
  -1.60877, 72.0948 to \
  -0.03, 72.0948 to \
  -0.03, 38.025 to \
  -1.60877, 38.025 to \
  -1.60877, 72.0948 front fs empty border lc rgb '#549f' lw 0.1
set object 3404 polygon from \
  -1.65031, 72.118 to \
  -0.03, 72.118 to \
  -0.03, 38.0382 to \
  -1.65031, 38.0382 to \
  -1.65031, 72.118 front fs empty border lc rgb '#549f' lw 0.1
set object 3405 polygon from \
  -1.69198, 72.1413 to \
  -0.03, 72.1413 to \
  -0.03, 38.0515 to \
  -1.69198, 38.0515 to \
  -1.69198, 72.1413 front fs empty border lc rgb '#549f' lw 0.1
set object 3406 polygon from \
  -1.73277, 72.1645 to \
  -0.03, 72.1645 to \
  -0.03, 38.0648 to \
  -1.73277, 38.0648 to \
  -1.73277, 72.1645 front fs empty border lc rgb '#549f' lw 0.1
set object 3407 polygon from \
  -1.77265, 72.1878 to \
  -0.03, 72.1878 to \
  -0.03, 38.078 to \
  -1.77265, 38.078 to \
  -1.77265, 72.1878 front fs empty border lc rgb '#549f' lw 0.1
set object 3408 polygon from \
  -1.8116, 72.211 to \
  -0.03, 72.211 to \
  -0.03, 38.0913 to \
  -1.8116, 38.0913 to \
  -1.8116, 72.211 front fs empty border lc rgb '#549f' lw 0.1
set object 3409 polygon from \
  -1.84958, 72.2343 to \
  -0.03, 72.2343 to \
  -0.03, 38.1045 to \
  -1.84958, 38.1045 to \
  -1.84958, 72.2343 front fs empty border lc rgb '#549f' lw 0.1
set object 3410 polygon from \
  -1.88658, 72.2576 to \
  -0.03, 72.2576 to \
  -0.03, 38.1178 to \
  -1.88658, 38.1178 to \
  -1.88658, 72.2576 front fs empty border lc rgb '#549f' lw 0.1
set object 3411 polygon from \
  -1.92327, 72.2808 to \
  -0.03, 72.2808 to \
  -0.03, 38.131 to \
  -1.92327, 38.131 to \
  -1.92327, 72.2808 front fs empty border lc rgb '#549f' lw 0.1
set object 3412 polygon from \
  -1.96001, 72.3041 to \
  -0.03, 72.3041 to \
  -0.03, 38.1443 to \
  -1.96001, 38.1443 to \
  -1.96001, 72.3041 front fs empty border lc rgb '#549f' lw 0.1
set object 3413 polygon from \
  -1.9957, 72.3274 to \
  -0.03, 72.3274 to \
  -0.03, 38.1576 to \
  -1.9957, 38.1576 to \
  -1.9957, 72.3274 front fs empty border lc rgb '#549f' lw 0.1
set object 3414 polygon from \
  -2.03033, 72.3506 to \
  -0.03, 72.3506 to \
  -0.03, 38.1708 to \
  -2.03033, 38.1708 to \
  -2.03033, 72.3506 front fs empty border lc rgb '#549f' lw 0.1
set object 3415 polygon from \
  -2.06387, 72.3739 to \
  -0.03, 72.3739 to \
  -0.03, 38.1841 to \
  -2.06387, 38.1841 to \
  -2.06387, 72.3739 front fs empty border lc rgb '#549f' lw 0.1
set object 3416 polygon from \
  -2.09631, 72.3972 to \
  -0.03, 72.3972 to \
  -0.03, 38.1974 to \
  -2.09631, 38.1974 to \
  -2.09631, 72.3972 front fs empty border lc rgb '#549f' lw 0.1
set object 3417 polygon from \
  -2.12762, 72.4204 to \
  -0.03, 72.4204 to \
  -0.03, 38.2106 to \
  -2.12762, 38.2106 to \
  -2.12762, 72.4204 front fs empty border lc rgb '#549f' lw 0.1
set object 3418 polygon from \
  -2.15778, 72.4437 to \
  -0.03, 72.4437 to \
  -0.03, 38.2239 to \
  -2.15778, 38.2239 to \
  -2.15778, 72.4437 front fs empty border lc rgb '#549f' lw 0.1
set object 3419 polygon from \
  -2.18678, 72.467 to \
  -0.03, 72.467 to \
  -0.03, 38.2372 to \
  -2.18678, 38.2372 to \
  -2.18678, 72.467 front fs empty border lc rgb '#549f' lw 0.1
set object 3420 polygon from \
  -2.2146, 72.4903 to \
  -0.03, 72.4903 to \
  -0.03, 38.2504 to \
  -2.2146, 38.2504 to \
  -2.2146, 72.4903 front fs empty border lc rgb '#549f' lw 0.1
set object 3421 polygon from \
  -2.24123, 72.5135 to \
  -0.03, 72.5135 to \
  -0.03, 38.2637 to \
  -2.24123, 38.2637 to \
  -2.24123, 72.5135 front fs empty border lc rgb '#549f' lw 0.1
set object 3422 polygon from \
  -2.26664, 72.5368 to \
  -0.03, 72.5368 to \
  -0.03, 38.277 to \
  -2.26664, 38.277 to \
  -2.26664, 72.5368 front fs empty border lc rgb '#549f' lw 0.1
set object 3423 polygon from \
  -2.29083, 72.5601 to \
  -0.03, 72.5601 to \
  -0.03, 38.2902 to \
  -2.29083, 38.2902 to \
  -2.29083, 72.5601 front fs empty border lc rgb '#549f' lw 0.1
set object 3424 polygon from \
  -2.31378, 72.5834 to \
  -0.03, 72.5834 to \
  -0.03, 38.3035 to \
  -2.31378, 38.3035 to \
  -2.31378, 72.5834 front fs empty border lc rgb '#549f' lw 0.1
set object 3425 polygon from \
  -2.33547, 72.6066 to \
  -0.03, 72.6066 to \
  -0.03, 38.3168 to \
  -2.33547, 38.3168 to \
  -2.33547, 72.6066 front fs empty border lc rgb '#549f' lw 0.1
set object 3426 polygon from \
  -2.35589, 72.6299 to \
  -0.03, 72.6299 to \
  -0.03, 38.3301 to \
  -2.35589, 38.3301 to \
  -2.35589, 72.6299 front fs empty border lc rgb '#549f' lw 0.1
set object 3427 polygon from \
  -2.37504, 72.6532 to \
  -0.03, 72.6532 to \
  -0.03, 38.3434 to \
  -2.37504, 38.3434 to \
  -2.37504, 72.6532 front fs empty border lc rgb '#549f' lw 0.1
set object 3428 polygon from \
  -2.3929, 72.6765 to \
  -0.03, 72.6765 to \
  -0.03, 38.3566 to \
  -2.3929, 38.3566 to \
  -2.3929, 72.6765 front fs empty border lc rgb '#549f' lw 0.1
set object 3429 polygon from \
  -2.40945, 72.6998 to \
  -0.03, 72.6998 to \
  -0.03, 38.3699 to \
  -2.40945, 38.3699 to \
  -2.40945, 72.6998 front fs empty border lc rgb '#549f' lw 0.1
set object 3430 polygon from \
  -2.4247, 72.7231 to \
  -0.03, 72.7231 to \
  -0.03, 38.3832 to \
  -2.4247, 38.3832 to \
  -2.4247, 72.7231 front fs empty border lc rgb '#549f' lw 0.1
set object 3431 polygon from \
  -2.43864, 72.7464 to \
  -0.03, 72.7464 to \
  -0.03, 38.3965 to \
  -2.43864, 38.3965 to \
  -2.43864, 72.7464 front fs empty border lc rgb '#549f' lw 0.1
set object 3432 polygon from \
  -2.45125, 72.7696 to \
  -0.03, 72.7696 to \
  -0.03, 38.4098 to \
  -2.45125, 38.4098 to \
  -2.45125, 72.7696 front fs empty border lc rgb '#549f' lw 0.1
set object 3433 polygon from \
  -2.46253, 72.7929 to \
  -0.03, 72.7929 to \
  -0.03, 38.4231 to \
  -2.46253, 38.4231 to \
  -2.46253, 72.7929 front fs empty border lc rgb '#549f' lw 0.1
set object 3434 polygon from \
  -2.47247, 72.8162 to \
  -0.03, 72.8162 to \
  -0.03, 38.4363 to \
  -2.47247, 38.4363 to \
  -2.47247, 72.8162 front fs empty border lc rgb '#549f' lw 0.1
set object 3435 polygon from \
  -2.48108, 72.8395 to \
  -0.03, 72.8395 to \
  -0.03, 38.4496 to \
  -2.48108, 38.4496 to \
  -2.48108, 72.8395 front fs empty border lc rgb '#549f' lw 0.1
set object 3436 polygon from \
  -2.48834, 72.8628 to \
  -0.03, 72.8628 to \
  -0.03, 38.4629 to \
  -2.48834, 38.4629 to \
  -2.48834, 72.8628 front fs empty border lc rgb '#549f' lw 0.1
set object 3437 polygon from \
  -2.49425, 72.8861 to \
  -0.03, 72.8861 to \
  -0.03, 38.4762 to \
  -2.49425, 38.4762 to \
  -2.49425, 72.8861 front fs empty border lc rgb '#549f' lw 0.1
set object 3438 polygon from \
  -2.49881, 72.9094 to \
  -0.03, 72.9094 to \
  -0.03, 38.4895 to \
  -2.49881, 38.4895 to \
  -2.49881, 72.9094 front fs empty border lc rgb '#549f' lw 0.1
set object 3439 polygon from \
  -2.50203, 72.9327 to \
  -0.03, 72.9327 to \
  -0.03, 38.5028 to \
  -2.50203, 38.5028 to \
  -2.50203, 72.9327 front fs empty border lc rgb '#549f' lw 0.1
set object 3440 polygon from \
  -2.50389, 72.956 to \
  -0.03, 72.956 to \
  -0.03, 38.5161 to \
  -2.50389, 38.5161 to \
  -2.50389, 72.956 front fs empty border lc rgb '#549f' lw 0.1
set object 3441 polygon from \
  -2.5044, 72.9793 to \
  -0.03, 72.9793 to \
  -0.03, 38.5294 to \
  -2.5044, 38.5294 to \
  -2.5044, 72.9793 front fs empty border lc rgb '#549f' lw 0.1
set object 3442 polygon from \
  -2.5044, 73.0026 to \
  -0.03, 73.0026 to \
  -0.03, 38.5427 to \
  -2.5044, 38.5427 to \
  -2.5044, 73.0026 front fs empty border lc rgb '#549f' lw 0.1
set object 3443 polygon from \
  -2.50356, 73.0259 to \
  -0.03, 73.0259 to \
  -0.03, 38.556 to \
  -2.50356, 38.556 to \
  -2.50356, 73.0259 front fs empty border lc rgb '#549f' lw 0.1
set object 3444 polygon from \
  -2.50138, 73.0492 to \
  -0.03, 73.0492 to \
  -0.03, 38.5693 to \
  -2.50138, 38.5693 to \
  -2.50138, 73.0492 front fs empty border lc rgb '#549f' lw 0.1
set object 3445 polygon from \
  -2.49785, 73.0725 to \
  -0.03, 73.0725 to \
  -0.03, 38.5826 to \
  -2.49785, 38.5826 to \
  -2.49785, 73.0725 front fs empty border lc rgb '#549f' lw 0.1
set object 3446 polygon from \
  -2.49298, 73.0958 to \
  -0.03, 73.0958 to \
  -0.03, 38.5959 to \
  -2.49298, 38.5959 to \
  -2.49298, 73.0958 front fs empty border lc rgb '#549f' lw 0.1
set object 3447 polygon from \
  -2.48678, 73.1191 to \
  -0.03, 73.1191 to \
  -0.03, 38.6092 to \
  -2.48678, 38.6092 to \
  -2.48678, 73.1191 front fs empty border lc rgb '#549f' lw 0.1
set object 3448 polygon from \
  -2.50496, 73.1424 to \
  -0.03, 73.1424 to \
  -0.03, 38.6225 to \
  -2.50496, 38.6225 to \
  -2.50496, 73.1424 front fs empty border lc rgb '#549f' lw 0.1
set object 3449 polygon from \
  -2.52571, 73.1658 to \
  -0.03, 73.1658 to \
  -0.03, 38.6358 to \
  -2.52571, 38.6358 to \
  -2.52571, 73.1658 front fs empty border lc rgb '#549f' lw 0.1
set object 3450 polygon from \
  -2.54556, 73.1891 to \
  -0.03, 73.1891 to \
  -0.03, 38.6491 to \
  -2.54556, 38.6491 to \
  -2.54556, 73.1891 front fs empty border lc rgb '#549f' lw 0.1
set object 3451 polygon from \
  -2.5645, 73.2124 to \
  -0.03, 73.2124 to \
  -0.03, 38.6624 to \
  -2.5645, 38.6624 to \
  -2.5645, 73.2124 front fs empty border lc rgb '#549f' lw 0.1
set object 3452 polygon from \
  -2.58253, 73.2357 to \
  -0.03, 73.2357 to \
  -0.03, 38.6757 to \
  -2.58253, 38.6757 to \
  -2.58253, 73.2357 front fs empty border lc rgb '#549f' lw 0.1
set object 3453 polygon from \
  -2.59966, 73.259 to \
  -0.03, 73.259 to \
  -0.03, 38.6891 to \
  -2.59966, 38.6891 to \
  -2.59966, 73.259 front fs empty border lc rgb '#549f' lw 0.1
set object 3454 polygon from \
  -2.61588, 73.2823 to \
  -0.03, 73.2823 to \
  -0.03, 38.7024 to \
  -2.61588, 38.7024 to \
  -2.61588, 73.2823 front fs empty border lc rgb '#549f' lw 0.1
set object 3455 polygon from \
  -2.6312, 73.3056 to \
  -0.03, 73.3056 to \
  -0.03, 38.7157 to \
  -2.6312, 38.7157 to \
  -2.6312, 73.3056 front fs empty border lc rgb '#549f' lw 0.1
set object 3456 polygon from \
  -2.64561, 73.329 to \
  -0.03, 73.329 to \
  -0.03, 38.729 to \
  -2.64561, 38.729 to \
  -2.64561, 73.329 front fs empty border lc rgb '#549f' lw 0.1
set object 3457 polygon from \
  -2.65912, 73.3523 to \
  -0.03, 73.3523 to \
  -0.03, 38.7423 to \
  -2.65912, 38.7423 to \
  -2.65912, 73.3523 front fs empty border lc rgb '#549f' lw 0.1
set object 3458 polygon from \
  -2.67172, 73.3756 to \
  -0.03, 73.3756 to \
  -0.03, 38.7556 to \
  -2.67172, 38.7556 to \
  -2.67172, 73.3756 front fs empty border lc rgb '#549f' lw 0.1
set object 3459 polygon from \
  -2.68343, 73.3989 to \
  -0.03, 73.3989 to \
  -0.03, 38.769 to \
  -2.68343, 38.769 to \
  -2.68343, 73.3989 front fs empty border lc rgb '#549f' lw 0.1
set object 3460 polygon from \
  -2.69425, 73.4223 to \
  -0.03, 73.4223 to \
  -0.03, 38.7823 to \
  -2.69425, 38.7823 to \
  -2.69425, 73.4223 front fs empty border lc rgb '#549f' lw 0.1
set object 3461 polygon from \
  -2.70417, 73.4456 to \
  -0.03, 73.4456 to \
  -0.03, 38.7956 to \
  -2.70417, 38.7956 to \
  -2.70417, 73.4456 front fs empty border lc rgb '#549f' lw 0.1
set object 3462 polygon from \
  -2.71321, 73.4689 to \
  -0.03, 73.4689 to \
  -0.03, 38.8089 to \
  -2.71321, 38.8089 to \
  -2.71321, 73.4689 front fs empty border lc rgb '#549f' lw 0.1
set object 3463 polygon from \
  -2.72136, 73.4922 to \
  -0.03, 73.4922 to \
  -0.03, 38.8222 to \
  -2.72136, 38.8222 to \
  -2.72136, 73.4922 front fs empty border lc rgb '#549f' lw 0.1
set object 3464 polygon from \
  -2.73104, 73.5156 to \
  -0.03, 73.5156 to \
  -0.03, 38.8356 to \
  -2.73104, 38.8356 to \
  -2.73104, 73.5156 front fs empty border lc rgb '#549f' lw 0.1
set object 3465 polygon from \
  -2.7414, 73.5389 to \
  -0.03, 73.5389 to \
  -0.03, 38.8489 to \
  -2.7414, 38.8489 to \
  -2.7414, 73.5389 front fs empty border lc rgb '#549f' lw 0.1
set object 3466 polygon from \
  -2.75084, 73.5622 to \
  -0.03, 73.5622 to \
  -0.03, 38.8622 to \
  -2.75084, 38.8622 to \
  -2.75084, 73.5622 front fs empty border lc rgb '#549f' lw 0.1
set object 3467 polygon from \
  -2.75935, 73.5856 to \
  -0.03, 73.5856 to \
  -0.03, 38.8756 to \
  -2.75935, 38.8756 to \
  -2.75935, 73.5856 front fs empty border lc rgb '#549f' lw 0.1
set object 3468 polygon from \
  -2.76694, 73.6089 to \
  -0.03, 73.6089 to \
  -0.03, 38.8889 to \
  -2.76694, 38.8889 to \
  -2.76694, 73.6089 front fs empty border lc rgb '#549f' lw 0.1
set object 3469 polygon from \
  -2.77362, 73.6322 to \
  -0.03, 73.6322 to \
  -0.03, 38.9022 to \
  -2.77362, 38.9022 to \
  -2.77362, 73.6322 front fs empty border lc rgb '#549f' lw 0.1
set object 3470 polygon from \
  -2.77938, 73.6556 to \
  -0.03, 73.6556 to \
  -0.03, 38.9156 to \
  -2.77938, 38.9156 to \
  -2.77938, 73.6556 front fs empty border lc rgb '#549f' lw 0.1
set object 3471 polygon from \
  -2.78424, 73.6789 to \
  -0.03, 73.6789 to \
  -0.03, 38.9289 to \
  -2.78424, 38.9289 to \
  -2.78424, 73.6789 front fs empty border lc rgb '#549f' lw 0.1
set object 3472 polygon from \
  -2.7882, 73.7022 to \
  -0.03, 73.7022 to \
  -0.03, 38.9422 to \
  -2.7882, 38.9422 to \
  -2.7882, 73.7022 front fs empty border lc rgb '#549f' lw 0.1
set object 3473 polygon from \
  -2.79127, 73.7256 to \
  -0.03, 73.7256 to \
  -0.03, 38.9556 to \
  -2.79127, 38.9556 to \
  -2.79127, 73.7256 front fs empty border lc rgb '#549f' lw 0.1
set object 3474 polygon from \
  -2.79345, 73.7489 to \
  -0.03, 73.7489 to \
  -0.03, 38.9689 to \
  -2.79345, 38.9689 to \
  -2.79345, 73.7489 front fs empty border lc rgb '#549f' lw 0.1
set object 3475 polygon from \
  -2.79474, 73.7723 to \
  -0.03, 73.7723 to \
  -0.03, 38.9822 to \
  -2.79474, 38.9822 to \
  -2.79474, 73.7723 front fs empty border lc rgb '#549f' lw 0.1
set object 3476 polygon from \
  -2.79516, 73.7956 to \
  -0.03, 73.7956 to \
  -0.03, 38.9956 to \
  -2.79516, 38.9956 to \
  -2.79516, 73.7956 front fs empty border lc rgb '#549f' lw 0.1
set object 3477 polygon from \
  -2.79516, 73.819 to \
  -0.03, 73.819 to \
  -0.03, 39.0089 to \
  -2.79516, 39.0089 to \
  -2.79516, 73.819 front fs empty border lc rgb '#549f' lw 0.1
set object 3478 polygon from \
  -2.79471, 73.8423 to \
  -0.03, 73.8423 to \
  -0.03, 39.0223 to \
  -2.79471, 39.0223 to \
  -2.79471, 73.8423 front fs empty border lc rgb '#549f' lw 0.1
set object 3479 polygon from \
  -2.79341, 73.8657 to \
  -0.03, 73.8657 to \
  -0.03, 39.0356 to \
  -2.79341, 39.0356 to \
  -2.79341, 73.8657 front fs empty border lc rgb '#549f' lw 0.1
set object 3480 polygon from \
  -2.79125, 73.889 to \
  -0.03, 73.889 to \
  -0.03, 39.049 to \
  -2.79125, 39.049 to \
  -2.79125, 73.889 front fs empty border lc rgb '#549f' lw 0.1
set object 3481 polygon from \
  -2.78825, 73.9124 to \
  -0.03, 73.9124 to \
  -0.03, 39.0623 to \
  -2.78825, 39.0623 to \
  -2.78825, 73.9124 front fs empty border lc rgb '#549f' lw 0.1
set object 3482 polygon from \
  -2.78442, 73.9357 to \
  -0.03, 73.9357 to \
  -0.03, 39.0756 to \
  -2.78442, 39.0756 to \
  -2.78442, 73.9357 front fs empty border lc rgb '#549f' lw 0.1
set object 3483 polygon from \
  -2.77976, 73.9591 to \
  -0.03, 73.9591 to \
  -0.03, 39.089 to \
  -2.77976, 39.089 to \
  -2.77976, 73.9591 front fs empty border lc rgb '#549f' lw 0.1
set object 3484 polygon from \
  -2.77429, 73.9824 to \
  -0.03, 73.9824 to \
  -0.03, 39.1023 to \
  -2.77429, 39.1023 to \
  -2.77429, 73.9824 front fs empty border lc rgb '#549f' lw 0.1
set object 3485 polygon from \
  -2.76801, 74.0058 to \
  -0.03, 74.0058 to \
  -0.03, 39.1157 to \
  -2.76801, 39.1157 to \
  -2.76801, 74.0058 front fs empty border lc rgb '#549f' lw 0.1
set object 3486 polygon from \
  -2.76093, 74.0291 to \
  -0.03, 74.0291 to \
  -0.03, 39.1291 to \
  -2.76093, 39.1291 to \
  -2.76093, 74.0291 front fs empty border lc rgb '#549f' lw 0.1
set object 3487 polygon from \
  -2.75307, 74.0525 to \
  -0.03, 74.0525 to \
  -0.03, 39.1424 to \
  -2.75307, 39.1424 to \
  -2.75307, 74.0525 front fs empty border lc rgb '#549f' lw 0.1
set object 3488 polygon from \
  -2.74443, 74.0758 to \
  -0.03, 74.0758 to \
  -0.03, 39.1558 to \
  -2.74443, 39.1558 to \
  -2.74443, 74.0758 front fs empty border lc rgb '#549f' lw 0.1
set object 3489 polygon from \
  -2.73503, 74.0992 to \
  -0.03, 74.0992 to \
  -0.03, 39.1691 to \
  -2.73503, 39.1691 to \
  -2.73503, 74.0992 front fs empty border lc rgb '#549f' lw 0.1
set object 3490 polygon from \
  -2.72488, 74.1226 to \
  -0.03, 74.1226 to \
  -0.03, 39.1825 to \
  -2.72488, 39.1825 to \
  -2.72488, 74.1226 front fs empty border lc rgb '#549f' lw 0.1
set object 3491 polygon from \
  -2.71399, 74.1459 to \
  -0.03, 74.1459 to \
  -0.03, 39.1958 to \
  -2.71399, 39.1958 to \
  -2.71399, 74.1459 front fs empty border lc rgb '#549f' lw 0.1
set object 3492 polygon from \
  -2.70237, 74.1693 to \
  -0.03, 74.1693 to \
  -0.03, 39.2092 to \
  -2.70237, 39.2092 to \
  -2.70237, 74.1693 front fs empty border lc rgb '#549f' lw 0.1
set object 3493 polygon from \
  -2.69003, 74.1927 to \
  -0.03, 74.1927 to \
  -0.03, 39.2226 to \
  -2.69003, 39.2226 to \
  -2.69003, 74.1927 front fs empty border lc rgb '#549f' lw 0.1
set object 3494 polygon from \
  -2.67699, 74.216 to \
  -0.03, 74.216 to \
  -0.03, 39.2359 to \
  -2.67699, 39.2359 to \
  -2.67699, 74.216 front fs empty border lc rgb '#549f' lw 0.1
set object 3495 polygon from \
  -2.66325, 74.2394 to \
  -0.03, 74.2394 to \
  -0.03, 39.2493 to \
  -2.66325, 39.2493 to \
  -2.66325, 74.2394 front fs empty border lc rgb '#549f' lw 0.1
set object 3496 polygon from \
  -2.64884, 74.2628 to \
  -0.03, 74.2628 to \
  -0.03, 39.2627 to \
  -2.64884, 39.2627 to \
  -2.64884, 74.2628 front fs empty border lc rgb '#549f' lw 0.1
set object 3497 polygon from \
  -2.63376, 74.2861 to \
  -0.03, 74.2861 to \
  -0.03, 39.276 to \
  -2.63376, 39.276 to \
  -2.63376, 74.2861 front fs empty border lc rgb '#549f' lw 0.1
set object 3498 polygon from \
  -2.61803, 74.3095 to \
  -0.03, 74.3095 to \
  -0.03, 39.2894 to \
  -2.61803, 39.2894 to \
  -2.61803, 74.3095 front fs empty border lc rgb '#549f' lw 0.1
set object 3499 polygon from \
  -2.60165, 74.3329 to \
  -0.03, 74.3329 to \
  -0.03, 39.3028 to \
  -2.60165, 39.3028 to \
  -2.60165, 74.3329 front fs empty border lc rgb '#549f' lw 0.1
set object 3500 polygon from \
  -2.59091, 74.3563 to \
  -0.03, 74.3563 to \
  -0.03, 39.3161 to \
  -2.59091, 39.3161 to \
  -2.59091, 74.3563 front fs empty border lc rgb '#549f' lw 0.1
set object 3501 polygon from \
  -2.58107, 74.3796 to \
  -0.03, 74.3796 to \
  -0.03, 39.3295 to \
  -2.58107, 39.3295 to \
  -2.58107, 74.3796 front fs empty border lc rgb '#549f' lw 0.1
set object 3502 polygon from \
  -2.57059, 74.403 to \
  -0.03, 74.403 to \
  -0.03, 39.3429 to \
  -2.57059, 39.3429 to \
  -2.57059, 74.403 front fs empty border lc rgb '#549f' lw 0.1
set object 3503 polygon from \
  -2.55949, 74.4264 to \
  -0.03, 74.4264 to \
  -0.03, 39.3562 to \
  -2.55949, 39.3562 to \
  -2.55949, 74.4264 front fs empty border lc rgb '#549f' lw 0.1
set object 3504 polygon from \
  -2.54778, 74.4498 to \
  -0.03, 74.4498 to \
  -0.03, 39.3696 to \
  -2.54778, 39.3696 to \
  -2.54778, 74.4498 front fs empty border lc rgb '#549f' lw 0.1
set object 3505 polygon from \
  -2.53547, 74.4731 to \
  -0.03, 74.4731 to \
  -0.03, 39.383 to \
  -2.53547, 39.383 to \
  -2.53547, 74.4731 front fs empty border lc rgb '#549f' lw 0.1
set object 3506 polygon from \
  -2.52258, 74.4965 to \
  -0.03, 74.4965 to \
  -0.03, 39.3964 to \
  -2.52258, 39.3964 to \
  -2.52258, 74.4965 front fs empty border lc rgb '#549f' lw 0.1
set object 3507 polygon from \
  -2.50911, 74.5199 to \
  -0.03, 74.5199 to \
  -0.03, 39.4098 to \
  -2.50911, 39.4098 to \
  -2.50911, 74.5199 front fs empty border lc rgb '#549f' lw 0.1
set object 3508 polygon from \
  -2.49509, 74.5433 to \
  -0.03, 74.5433 to \
  -0.03, 39.4231 to \
  -2.49509, 39.4231 to \
  -2.49509, 74.5433 front fs empty border lc rgb '#549f' lw 0.1
set object 3509 polygon from \
  -2.50807, 74.5667 to \
  -0.03, 74.5667 to \
  -0.03, 39.4365 to \
  -2.50807, 39.4365 to \
  -2.50807, 74.5667 front fs empty border lc rgb '#549f' lw 0.1
set object 3510 polygon from \
  -2.53329, 74.5901 to \
  -0.03, 74.5901 to \
  -0.03, 39.4499 to \
  -2.53329, 39.4499 to \
  -2.53329, 74.5901 front fs empty border lc rgb '#549f' lw 0.1
set object 3511 polygon from \
  -2.55773, 74.6135 to \
  -0.03, 74.6135 to \
  -0.03, 39.4633 to \
  -2.55773, 39.4633 to \
  -2.55773, 74.6135 front fs empty border lc rgb '#549f' lw 0.1
set object 3512 polygon from \
  -2.58137, 74.6368 to \
  -0.03, 74.6368 to \
  -0.03, 39.4767 to \
  -2.58137, 39.4767 to \
  -2.58137, 74.6368 front fs empty border lc rgb '#549f' lw 0.1
set object 3513 polygon from \
  -2.6042, 74.6602 to \
  -0.03, 74.6602 to \
  -0.03, 39.4901 to \
  -2.6042, 39.4901 to \
  -2.6042, 74.6602 front fs empty border lc rgb '#549f' lw 0.1
set object 3514 polygon from \
  -2.6262, 74.6836 to \
  -0.03, 74.6836 to \
  -0.03, 39.5034 to \
  -2.6262, 39.5034 to \
  -2.6262, 74.6836 front fs empty border lc rgb '#549f' lw 0.1
set object 3515 polygon from \
  -2.64735, 74.707 to \
  -0.03, 74.707 to \
  -0.03, 39.5168 to \
  -2.64735, 39.5168 to \
  -2.64735, 74.707 front fs empty border lc rgb '#549f' lw 0.1
set object 3516 polygon from \
  -2.66765, 74.7304 to \
  -0.03, 74.7304 to \
  -0.03, 39.5302 to \
  -2.66765, 39.5302 to \
  -2.66765, 74.7304 front fs empty border lc rgb '#549f' lw 0.1
set object 3517 polygon from \
  -2.68707, 74.7538 to \
  -0.03, 74.7538 to \
  -0.03, 39.5436 to \
  -2.68707, 39.5436 to \
  -2.68707, 74.7538 front fs empty border lc rgb '#549f' lw 0.1
set object 3518 polygon from \
  -2.70561, 74.7772 to \
  -0.03, 74.7772 to \
  -0.03, 39.557 to \
  -2.70561, 39.557 to \
  -2.70561, 74.7772 front fs empty border lc rgb '#549f' lw 0.1
set object 3519 polygon from \
  -2.72325, 74.8006 to \
  -0.03, 74.8006 to \
  -0.03, 39.5704 to \
  -2.72325, 39.5704 to \
  -2.72325, 74.8006 front fs empty border lc rgb '#549f' lw 0.1
set object 3520 polygon from \
  -2.73998, 74.824 to \
  -0.03, 74.824 to \
  -0.03, 39.5838 to \
  -2.73998, 39.5838 to \
  -2.73998, 74.824 front fs empty border lc rgb '#549f' lw 0.1
set object 3521 polygon from \
  -2.75579, 74.8474 to \
  -0.03, 74.8474 to \
  -0.03, 39.5972 to \
  -2.75579, 39.5972 to \
  -2.75579, 74.8474 front fs empty border lc rgb '#549f' lw 0.1
set object 3522 polygon from \
  -2.77066, 74.8708 to \
  -0.03, 74.8708 to \
  -0.03, 39.6106 to \
  -2.77066, 39.6106 to \
  -2.77066, 74.8708 front fs empty border lc rgb '#549f' lw 0.1
set object 3523 polygon from \
  -2.78458, 74.8942 to \
  -0.03, 74.8942 to \
  -0.03, 39.624 to \
  -2.78458, 39.624 to \
  -2.78458, 74.8942 front fs empty border lc rgb '#549f' lw 0.1
set object 3524 polygon from \
  -2.79754, 74.9176 to \
  -0.03, 74.9176 to \
  -0.03, 39.6374 to \
  -2.79754, 39.6374 to \
  -2.79754, 74.9176 front fs empty border lc rgb '#549f' lw 0.1
set object 3525 polygon from \
  -2.80954, 74.941 to \
  -0.03, 74.941 to \
  -0.03, 39.6508 to \
  -2.80954, 39.6508 to \
  -2.80954, 74.941 front fs empty border lc rgb '#549f' lw 0.1
set object 3526 polygon from \
  -2.82056, 74.9644 to \
  -0.03, 74.9644 to \
  -0.03, 39.6642 to \
  -2.82056, 39.6642 to \
  -2.82056, 74.9644 front fs empty border lc rgb '#549f' lw 0.1
set object 3527 polygon from \
  -2.83059, 74.9878 to \
  -0.03, 74.9878 to \
  -0.03, 39.6776 to \
  -2.83059, 39.6776 to \
  -2.83059, 74.9878 front fs empty border lc rgb '#549f' lw 0.1
set object 3528 polygon from \
  -2.83963, 75.0112 to \
  -0.03, 75.0112 to \
  -0.03, 39.691 to \
  -2.83963, 39.691 to \
  -2.83963, 75.0112 front fs empty border lc rgb '#549f' lw 0.1
set object 3529 polygon from \
  -2.84766, 75.0347 to \
  -0.03, 75.0347 to \
  -0.03, 39.7044 to \
  -2.84766, 39.7044 to \
  -2.84766, 75.0347 front fs empty border lc rgb '#549f' lw 0.1
set object 3530 polygon from \
  -2.85468, 75.0581 to \
  -0.03, 75.0581 to \
  -0.03, 39.7178 to \
  -2.85468, 39.7178 to \
  -2.85468, 75.0581 front fs empty border lc rgb '#549f' lw 0.1
set object 3531 polygon from \
  -2.86068, 75.0815 to \
  -0.03, 75.0815 to \
  -0.03, 39.7312 to \
  -2.86068, 39.7312 to \
  -2.86068, 75.0815 front fs empty border lc rgb '#549f' lw 0.1
set object 3532 polygon from \
  -2.86565, 75.1049 to \
  -0.03, 75.1049 to \
  -0.03, 39.7446 to \
  -2.86565, 39.7446 to \
  -2.86565, 75.1049 front fs empty border lc rgb '#549f' lw 0.1
set object 3533 polygon from \
  -2.86958, 75.1283 to \
  -0.03, 75.1283 to \
  -0.03, 39.7581 to \
  -2.86958, 39.7581 to \
  -2.86958, 75.1283 front fs empty border lc rgb '#549f' lw 0.1
set object 3534 polygon from \
  -2.87248, 75.1517 to \
  -0.03, 75.1517 to \
  -0.03, 39.7715 to \
  -2.87248, 39.7715 to \
  -2.87248, 75.1517 front fs empty border lc rgb '#549f' lw 0.1
set object 3535 polygon from \
  -2.87708, 75.1751 to \
  -0.03, 75.1751 to \
  -0.03, 39.7849 to \
  -2.87708, 39.7849 to \
  -2.87708, 75.1751 front fs empty border lc rgb '#549f' lw 0.1
set object 3536 polygon from \
  -2.88908, 75.1986 to \
  -0.03, 75.1986 to \
  -0.03, 39.7983 to \
  -2.88908, 39.7983 to \
  -2.88908, 75.1986 front fs empty border lc rgb '#549f' lw 0.1
set object 3537 polygon from \
  -2.90005, 75.222 to \
  -0.03, 75.222 to \
  -0.03, 39.8117 to \
  -2.90005, 39.8117 to \
  -2.90005, 75.222 front fs empty border lc rgb '#549f' lw 0.1
set object 3538 polygon from \
  -2.90998, 75.2454 to \
  -0.03, 75.2454 to \
  -0.03, 39.8251 to \
  -2.90998, 39.8251 to \
  -2.90998, 75.2454 front fs empty border lc rgb '#549f' lw 0.1
set object 3539 polygon from \
  -2.91885, 75.2688 to \
  -0.03, 75.2688 to \
  -0.03, 39.8386 to \
  -2.91885, 39.8386 to \
  -2.91885, 75.2688 front fs empty border lc rgb '#549f' lw 0.1
set object 3540 polygon from \
  -2.92666, 75.2923 to \
  -0.03, 75.2923 to \
  -0.03, 39.852 to \
  -2.92666, 39.852 to \
  -2.92666, 75.2923 front fs empty border lc rgb '#549f' lw 0.1
set object 3541 polygon from \
  -2.93341, 75.3157 to \
  -0.03, 75.3157 to \
  -0.03, 39.8654 to \
  -2.93341, 39.8654 to \
  -2.93341, 75.3157 front fs empty border lc rgb '#549f' lw 0.1
set object 3542 polygon from \
  -2.93908, 75.3391 to \
  -0.03, 75.3391 to \
  -0.03, 39.8788 to \
  -2.93908, 39.8788 to \
  -2.93908, 75.3391 front fs empty border lc rgb '#549f' lw 0.1
set object 3543 polygon from \
  -2.94368, 75.3625 to \
  -0.03, 75.3625 to \
  -0.03, 39.8922 to \
  -2.94368, 39.8922 to \
  -2.94368, 75.3625 front fs empty border lc rgb '#549f' lw 0.1
set object 3544 polygon from \
  -2.94719, 75.386 to \
  -0.03, 75.386 to \
  -0.03, 39.9057 to \
  -2.94719, 39.9057 to \
  -2.94719, 75.386 front fs empty border lc rgb '#549f' lw 0.1
set object 3545 polygon from \
  -2.94962, 75.4094 to \
  -0.03, 75.4094 to \
  -0.03, 39.9191 to \
  -2.94962, 39.9191 to \
  -2.94962, 75.4094 front fs empty border lc rgb '#549f' lw 0.1
set object 3546 polygon from \
  -2.95096, 75.4328 to \
  -0.03, 75.4328 to \
  -0.03, 39.9325 to \
  -2.95096, 39.9325 to \
  -2.95096, 75.4328 front fs empty border lc rgb '#549f' lw 0.1
set object 3547 polygon from \
  -2.95121, 75.4563 to \
  -0.03, 75.4563 to \
  -0.03, 39.946 to \
  -2.95121, 39.946 to \
  -2.95121, 75.4563 front fs empty border lc rgb '#549f' lw 0.1
set object 3548 polygon from \
  -2.95121, 75.4797 to \
  -0.03, 75.4797 to \
  -0.03, 39.9594 to \
  -2.95121, 39.9594 to \
  -2.95121, 75.4797 front fs empty border lc rgb '#549f' lw 0.1
set object 3549 polygon from \
  -2.95037, 75.5031 to \
  -0.03, 75.5031 to \
  -0.03, 39.9728 to \
  -2.95037, 39.9728 to \
  -2.95037, 75.5031 front fs empty border lc rgb '#549f' lw 0.1
set object 3550 polygon from \
  -2.94843, 75.5266 to \
  -0.03, 75.5266 to \
  -0.03, 39.9863 to \
  -2.94843, 39.9863 to \
  -2.94843, 75.5266 front fs empty border lc rgb '#549f' lw 0.1
set object 3551 polygon from \
  -2.94539, 75.55 to \
  -0.03, 75.55 to \
  -0.03, 39.9997 to \
  -2.94539, 39.9997 to \
  -2.94539, 75.55 front fs empty border lc rgb '#549f' lw 0.1
set object 3552 polygon from \
  -2.94125, 75.5734 to \
  -0.03, 75.5734 to \
  -0.03, 40.0131 to \
  -2.94125, 40.0131 to \
  -2.94125, 75.5734 front fs empty border lc rgb '#549f' lw 0.1
set object 3553 polygon from \
  -2.93602, 75.5969 to \
  -0.03, 75.5969 to \
  -0.03, 40.0266 to \
  -2.93602, 40.0266 to \
  -2.93602, 75.5969 front fs empty border lc rgb '#549f' lw 0.1
set object 3554 polygon from \
  -2.92969, 75.6203 to \
  -0.03, 75.6203 to \
  -0.03, 40.04 to \
  -2.92969, 40.04 to \
  -2.92969, 75.6203 front fs empty border lc rgb '#549f' lw 0.1
set object 3555 polygon from \
  -2.92226, 75.6438 to \
  -0.03, 75.6438 to \
  -0.03, 40.0534 to \
  -2.92226, 40.0534 to \
  -2.92226, 75.6438 front fs empty border lc rgb '#549f' lw 0.1
set object 3556 polygon from \
  -2.91374, 75.6672 to \
  -0.03, 75.6672 to \
  -0.03, 40.0669 to \
  -2.91374, 40.0669 to \
  -2.91374, 75.6672 front fs empty border lc rgb '#549f' lw 0.1
set object 3557 polygon from \
  -2.90413, 75.6907 to \
  -0.03, 75.6907 to \
  -0.03, 40.0803 to \
  -2.90413, 40.0803 to \
  -2.90413, 75.6907 front fs empty border lc rgb '#549f' lw 0.1
set object 3558 polygon from \
  -2.89343, 75.7141 to \
  -0.03, 75.7141 to \
  -0.03, 40.0938 to \
  -2.89343, 40.0938 to \
  -2.89343, 75.7141 front fs empty border lc rgb '#549f' lw 0.1
set object 3559 polygon from \
  -2.88425, 75.7376 to \
  -0.03, 75.7376 to \
  -0.03, 40.1072 to \
  -2.88425, 40.1072 to \
  -2.88425, 75.7376 front fs empty border lc rgb '#549f' lw 0.1
set object 3560 polygon from \
  -2.87455, 75.761 to \
  -0.03, 75.761 to \
  -0.03, 40.1207 to \
  -2.87455, 40.1207 to \
  -2.87455, 75.761 front fs empty border lc rgb '#549f' lw 0.1
set object 3561 polygon from \
  -2.86378, 75.7845 to \
  -0.03, 75.7845 to \
  -0.03, 40.1341 to \
  -2.86378, 40.1341 to \
  -2.86378, 75.7845 front fs empty border lc rgb '#549f' lw 0.1
set object 3562 polygon from \
  -2.85193, 75.8079 to \
  -0.03, 75.8079 to \
  -0.03, 40.1475 to \
  -2.85193, 40.1475 to \
  -2.85193, 75.8079 front fs empty border lc rgb '#549f' lw 0.1
set object 3563 polygon from \
  -2.83901, 75.8314 to \
  -0.03, 75.8314 to \
  -0.03, 40.161 to \
  -2.83901, 40.161 to \
  -2.83901, 75.8314 front fs empty border lc rgb '#549f' lw 0.1
set object 3564 polygon from \
  -2.82502, 75.8548 to \
  -0.03, 75.8548 to \
  -0.03, 40.1744 to \
  -2.82502, 40.1744 to \
  -2.82502, 75.8548 front fs empty border lc rgb '#549f' lw 0.1
set object 3565 polygon from \
  -2.80997, 75.8783 to \
  -0.03, 75.8783 to \
  -0.03, 40.1879 to \
  -2.80997, 40.1879 to \
  -2.80997, 75.8783 front fs empty border lc rgb '#549f' lw 0.1
set object 3566 polygon from \
  -2.79386, 75.9017 to \
  -0.03, 75.9017 to \
  -0.03, 40.2014 to \
  -2.79386, 40.2014 to \
  -2.79386, 75.9017 front fs empty border lc rgb '#549f' lw 0.1
set object 3567 polygon from \
  -2.7767, 75.9252 to \
  -0.03, 75.9252 to \
  -0.03, 40.2148 to \
  -2.7767, 40.2148 to \
  -2.7767, 75.9252 front fs empty border lc rgb '#549f' lw 0.1
set object 3568 polygon from \
  -2.75849, 75.9486 to \
  -0.03, 75.9486 to \
  -0.03, 40.2283 to \
  -2.75849, 40.2283 to \
  -2.75849, 75.9486 front fs empty border lc rgb '#549f' lw 0.1
set object 3569 polygon from \
  -2.73924, 75.9721 to \
  -0.03, 75.9721 to \
  -0.03, 40.2417 to \
  -2.73924, 40.2417 to \
  -2.73924, 75.9721 front fs empty border lc rgb '#549f' lw 0.1
set object 3570 polygon from \
  -2.71895, 75.9956 to \
  -0.03, 75.9956 to \
  -0.03, 40.2552 to \
  -2.71895, 40.2552 to \
  -2.71895, 75.9956 front fs empty border lc rgb '#549f' lw 0.1
set object 3571 polygon from \
  -2.69764, 76.019 to \
  -0.03, 76.019 to \
  -0.03, 40.2686 to \
  -2.69764, 40.2686 to \
  -2.69764, 76.019 front fs empty border lc rgb '#549f' lw 0.1
set object 3572 polygon from \
  -2.67531, 76.0425 to \
  -0.03, 76.0425 to \
  -0.03, 40.2821 to \
  -2.67531, 40.2821 to \
  -2.67531, 76.0425 front fs empty border lc rgb '#549f' lw 0.1
set object 3573 polygon from \
  -2.65197, 76.066 to \
  -0.03, 76.066 to \
  -0.03, 40.2956 to \
  -2.65197, 40.2956 to \
  -2.65197, 76.066 front fs empty border lc rgb '#549f' lw 0.1
set object 3574 polygon from \
  -2.62762, 76.0894 to \
  -0.03, 76.0894 to \
  -0.03, 40.309 to \
  -2.62762, 40.309 to \
  -2.62762, 76.0894 front fs empty border lc rgb '#549f' lw 0.1
set object 3575 polygon from \
  -2.60228, 76.1129 to \
  -0.03, 76.1129 to \
  -0.03, 40.3225 to \
  -2.60228, 40.3225 to \
  -2.60228, 76.1129 front fs empty border lc rgb '#549f' lw 0.1
set object 3576 polygon from \
  -2.57596, 76.1364 to \
  -0.03, 76.1364 to \
  -0.03, 40.336 to \
  -2.57596, 40.336 to \
  -2.57596, 76.1364 front fs empty border lc rgb '#549f' lw 0.1
set object 3577 polygon from \
  -2.54867, 76.1598 to \
  -0.03, 76.1598 to \
  -0.03, 40.3494 to \
  -2.54867, 40.3494 to \
  -2.54867, 76.1598 front fs empty border lc rgb '#549f' lw 0.1
set object 3578 polygon from \
  -2.52042, 76.1833 to \
  -0.03, 76.1833 to \
  -0.03, 40.3629 to \
  -2.52042, 40.3629 to \
  -2.52042, 76.1833 front fs empty border lc rgb '#549f' lw 0.1
set object 3579 polygon from \
  -2.49122, 76.2068 to \
  -0.03, 76.2068 to \
  -0.03, 40.3764 to \
  -2.49122, 40.3764 to \
  -2.49122, 76.2068 front fs empty border lc rgb '#549f' lw 0.1
set object 3580 polygon from \
  -2.46108, 76.2303 to \
  -0.03, 76.2303 to \
  -0.03, 40.3898 to \
  -2.46108, 40.3898 to \
  -2.46108, 76.2303 front fs empty border lc rgb '#549f' lw 0.1
set object 3581 polygon from \
  -2.43001, 76.2537 to \
  -0.03, 76.2537 to \
  -0.03, 40.4033 to \
  -2.43001, 40.4033 to \
  -2.43001, 76.2537 front fs empty border lc rgb '#549f' lw 0.1
set object 3582 polygon from \
  -2.39804, 76.2772 to \
  -0.03, 76.2772 to \
  -0.03, 40.4168 to \
  -2.39804, 40.4168 to \
  -2.39804, 76.2772 front fs empty border lc rgb '#549f' lw 0.1
set object 3583 polygon from \
  -2.36516, 76.3007 to \
  -0.03, 76.3007 to \
  -0.03, 40.4302 to \
  -2.36516, 40.4302 to \
  -2.36516, 76.3007 front fs empty border lc rgb '#549f' lw 0.1
set object 3584 polygon from \
  -2.3314, 76.3242 to \
  -0.03, 76.3242 to \
  -0.03, 40.4437 to \
  -2.3314, 40.4437 to \
  -2.3314, 76.3242 front fs empty border lc rgb '#549f' lw 0.1
set object 3585 polygon from \
  -2.29678, 76.3476 to \
  -0.03, 76.3476 to \
  -0.03, 40.4572 to \
  -2.29678, 40.4572 to \
  -2.29678, 76.3476 front fs empty border lc rgb '#549f' lw 0.1
set object 3586 polygon from \
  -2.2613, 76.3711 to \
  -0.03, 76.3711 to \
  -0.03, 40.4707 to \
  -2.2613, 40.4707 to \
  -2.2613, 76.3711 front fs empty border lc rgb '#549f' lw 0.1
set object 3587 polygon from \
  -2.22497, 76.3946 to \
  -0.03, 76.3946 to \
  -0.03, 40.4842 to \
  -2.22497, 40.4842 to \
  -2.22497, 76.3946 front fs empty border lc rgb '#549f' lw 0.1
set object 3588 polygon from \
  -2.18783, 76.4181 to \
  -0.03, 76.4181 to \
  -0.03, 40.4976 to \
  -2.18783, 40.4976 to \
  -2.18783, 76.4181 front fs empty border lc rgb '#549f' lw 0.1
set object 3589 polygon from \
  -2.14988, 76.4416 to \
  -0.03, 76.4416 to \
  -0.03, 40.5111 to \
  -2.14988, 40.5111 to \
  -2.14988, 76.4416 front fs empty border lc rgb '#549f' lw 0.1
set object 3590 polygon from \
  -2.11114, 76.4651 to \
  -0.03, 76.4651 to \
  -0.03, 40.5246 to \
  -2.11114, 40.5246 to \
  -2.11114, 76.4651 front fs empty border lc rgb '#549f' lw 0.1
set object 3591 polygon from \
  -2.07162, 76.4886 to \
  -0.03, 76.4886 to \
  -0.03, 40.5381 to \
  -2.07162, 40.5381 to \
  -2.07162, 76.4886 front fs empty border lc rgb '#549f' lw 0.1
set object 3592 polygon from \
  -2.03135, 76.512 to \
  -0.03, 76.512 to \
  -0.03, 40.5516 to \
  -2.03135, 40.5516 to \
  -2.03135, 76.512 front fs empty border lc rgb '#549f' lw 0.1
set object 3593 polygon from \
  -1.99034, 76.5355 to \
  -0.03, 76.5355 to \
  -0.03, 40.5651 to \
  -1.99034, 40.5651 to \
  -1.99034, 76.5355 front fs empty border lc rgb '#549f' lw 0.1
set object 3594 polygon from \
  -1.94861, 76.559 to \
  -0.03, 76.559 to \
  -0.03, 40.5785 to \
  -1.94861, 40.5785 to \
  -1.94861, 76.559 front fs empty border lc rgb '#549f' lw 0.1
set object 3595 polygon from \
  -1.90618, 76.5825 to \
  -0.03, 76.5825 to \
  -0.03, 40.592 to \
  -1.90618, 40.592 to \
  -1.90618, 76.5825 front fs empty border lc rgb '#549f' lw 0.1
set object 3596 polygon from \
  -1.86307, 76.606 to \
  -0.03, 76.606 to \
  -0.03, 40.6055 to \
  -1.86307, 40.6055 to \
  -1.86307, 76.606 front fs empty border lc rgb '#549f' lw 0.1
set object 3597 polygon from \
  -1.8193, 76.6295 to \
  -0.03, 76.6295 to \
  -0.03, 40.619 to \
  -1.8193, 40.619 to \
  -1.8193, 76.6295 front fs empty border lc rgb '#549f' lw 0.1
set object 3598 polygon from \
  -1.77488, 76.653 to \
  -0.03, 76.653 to \
  -0.03, 40.6325 to \
  -1.77488, 40.6325 to \
  -1.77488, 76.653 front fs empty border lc rgb '#549f' lw 0.1
set object 3599 polygon from \
  -1.72984, 76.6765 to \
  -0.03, 76.6765 to \
  -0.03, 40.646 to \
  -1.72984, 40.646 to \
  -1.72984, 76.6765 front fs empty border lc rgb '#549f' lw 0.1
set object 3600 polygon from \
  -1.6842, 76.7 to \
  -0.03, 76.7 to \
  -0.03, 40.6595 to \
  -1.6842, 40.6595 to \
  -1.6842, 76.7 front fs empty border lc rgb '#549f' lw 0.1
set object 3601 polygon from \
  -1.63797, 76.7235 to \
  -0.03, 76.7235 to \
  -0.03, 40.673 to \
  -1.63797, 40.673 to \
  -1.63797, 76.7235 front fs empty border lc rgb '#549f' lw 0.1
set object 3602 polygon from \
  -1.59119, 76.747 to \
  -0.03, 76.747 to \
  -0.03, 40.6865 to \
  -1.59119, 40.6865 to \
  -1.59119, 76.747 front fs empty border lc rgb '#549f' lw 0.1
set object 3603 polygon from \
  -1.54387, 76.7705 to \
  -0.03, 76.7705 to \
  -0.03, 40.7 to \
  -1.54387, 40.7 to \
  -1.54387, 76.7705 front fs empty border lc rgb '#549f' lw 0.1
set object 3604 polygon from \
  -1.49602, 76.794 to \
  -0.03, 76.794 to \
  -0.03, 40.7135 to \
  -1.49602, 40.7135 to \
  -1.49602, 76.794 front fs empty border lc rgb '#549f' lw 0.1
set object 3605 polygon from \
  -1.44768, 76.8175 to \
  -0.03, 76.8175 to \
  -0.03, 40.727 to \
  -1.44768, 40.727 to \
  -1.44768, 76.8175 front fs empty border lc rgb '#549f' lw 0.1
set object 3606 polygon from \
  -1.39887, 76.841 to \
  -0.03, 76.841 to \
  -0.03, 40.7405 to \
  -1.39887, 40.7405 to \
  -1.39887, 76.841 front fs empty border lc rgb '#549f' lw 0.1
set object 3607 polygon from \
  -1.34961, 76.8645 to \
  -0.03, 76.8645 to \
  -0.03, 40.754 to \
  -1.34961, 40.754 to \
  -1.34961, 76.8645 front fs empty border lc rgb '#549f' lw 0.1
set object 3608 polygon from \
  -1.29991, 76.888 to \
  -0.03, 76.888 to \
  -0.03, 40.7675 to \
  -1.29991, 40.7675 to \
  -1.29991, 76.888 front fs empty border lc rgb '#549f' lw 0.1
set object 3609 polygon from \
  -1.24981, 76.9116 to \
  -0.03, 76.9116 to \
  -0.03, 40.781 to \
  -1.24981, 40.781 to \
  -1.24981, 76.9116 front fs empty border lc rgb '#549f' lw 0.1
set object 3610 polygon from \
  -1.19933, 76.9351 to \
  -0.03, 76.9351 to \
  -0.03, 40.7945 to \
  -1.19933, 40.7945 to \
  -1.19933, 76.9351 front fs empty border lc rgb '#549f' lw 0.1
set object 3611 polygon from \
  -1.15047, 76.9586 to \
  -0.03, 76.9586 to \
  -0.03, 40.808 to \
  -1.15047, 40.808 to \
  -1.15047, 76.9586 front fs empty border lc rgb '#549f' lw 0.1
set object 3612 polygon from \
  -1.10207, 76.9821 to \
  -0.03, 76.9821 to \
  -0.03, 40.8215 to \
  -1.10207, 40.8215 to \
  -1.10207, 76.9821 front fs empty border lc rgb '#549f' lw 0.1
set object 3613 polygon from \
  -1.05336, 77.0056 to \
  -0.03, 77.0056 to \
  -0.03, 40.8351 to \
  -1.05336, 40.8351 to \
  -1.05336, 77.0056 front fs empty border lc rgb '#549f' lw 0.1
set object 3614 polygon from \
  -1.00435, 77.0291 to \
  -0.03, 77.0291 to \
  -0.03, 40.8486 to \
  -1.00435, 40.8486 to \
  -1.00435, 77.0291 front fs empty border lc rgb '#549f' lw 0.1
set object 3615 polygon from \
  -0.962519, 77.0526 to \
  -0.03, 77.0526 to \
  -0.03, 40.8621 to \
  -0.962519, 40.8621 to \
  -0.962519, 77.0526 front fs empty border lc rgb '#549f' lw 0.1
set object 3616 polygon from \
  -0.949819, 77.0762 to \
  -0.03, 77.0762 to \
  -0.03, 40.8756 to \
  -0.949819, 40.8756 to \
  -0.949819, 77.0762 front fs empty border lc rgb '#549f' lw 0.1
set object 3617 polygon from \
  -0.936877, 77.0997 to \
  -0.03, 77.0997 to \
  -0.03, 40.8891 to \
  -0.936877, 40.8891 to \
  -0.936877, 77.0997 front fs empty border lc rgb '#549f' lw 0.1
set object 3618 polygon from \
  -0.923685, 77.1232 to \
  -0.03, 77.1232 to \
  -0.03, 40.9026 to \
  -0.923685, 40.9026 to \
  -0.923685, 77.1232 front fs empty border lc rgb '#549f' lw 0.1
set object 3619 polygon from \
  -0.910237, 77.1467 to \
  -0.03, 77.1467 to \
  -0.03, 40.9162 to \
  -0.910237, 40.9162 to \
  -0.910237, 77.1467 front fs empty border lc rgb '#549f' lw 0.1
set object 3620 polygon from \
  -0.896526, 77.1703 to \
  -0.03, 77.1703 to \
  -0.03, 40.9297 to \
  -0.896526, 40.9297 to \
  -0.896526, 77.1703 front fs empty border lc rgb '#549f' lw 0.1
set object 3621 polygon from \
  -0.920965, 77.1938 to \
  -0.03, 77.1938 to \
  -0.03, 40.9432 to \
  -0.920965, 40.9432 to \
  -0.920965, 77.1938 front fs empty border lc rgb '#549f' lw 0.1
set object 3622 polygon from \
  -0.95764, 77.2173 to \
  -0.03, 77.2173 to \
  -0.03, 40.9567 to \
  -0.95764, 40.9567 to \
  -0.95764, 77.2173 front fs empty border lc rgb '#549f' lw 0.1
set object 3623 polygon from \
  -0.993909, 77.2408 to \
  -0.03, 77.2408 to \
  -0.03, 40.9702 to \
  -0.993909, 40.9702 to \
  -0.993909, 77.2408 front fs empty border lc rgb '#549f' lw 0.1
set object 3624 polygon from \
  -1.02974, 77.2644 to \
  -0.03, 77.2644 to \
  -0.03, 40.9838 to \
  -1.02974, 40.9838 to \
  -1.02974, 77.2644 front fs empty border lc rgb '#549f' lw 0.1
set object 3625 polygon from \
  -1.06511, 77.2879 to \
  -0.03, 77.2879 to \
  -0.03, 40.9973 to \
  -1.06511, 40.9973 to \
  -1.06511, 77.2879 front fs empty border lc rgb '#549f' lw 0.1
set object 3626 polygon from \
  -1.09998, 77.3114 to \
  -0.03, 77.3114 to \
  -0.03, 41.0108 to \
  -1.09998, 41.0108 to \
  -1.09998, 77.3114 front fs empty border lc rgb '#549f' lw 0.1
set object 3627 polygon from \
  -1.13433, 77.335 to \
  -0.03, 77.335 to \
  -0.03, 41.0244 to \
  -1.13433, 41.0244 to \
  -1.13433, 77.335 front fs empty border lc rgb '#549f' lw 0.1
set object 3628 polygon from \
  -1.16813, 77.3585 to \
  -0.03, 77.3585 to \
  -0.03, 41.0379 to \
  -1.16813, 41.0379 to \
  -1.16813, 77.3585 front fs empty border lc rgb '#549f' lw 0.1
set object 3629 polygon from \
  -1.20136, 77.382 to \
  -0.03, 77.382 to \
  -0.03, 41.0514 to \
  -1.20136, 41.0514 to \
  -1.20136, 77.382 front fs empty border lc rgb '#549f' lw 0.1
set object 3630 polygon from \
  -1.23398, 77.4056 to \
  -0.03, 77.4056 to \
  -0.03, 41.065 to \
  -1.23398, 41.065 to \
  -1.23398, 77.4056 front fs empty border lc rgb '#549f' lw 0.1
set object 3631 polygon from \
  -1.26596, 77.4291 to \
  -0.03, 77.4291 to \
  -0.03, 41.0785 to \
  -1.26596, 41.0785 to \
  -1.26596, 77.4291 front fs empty border lc rgb '#549f' lw 0.1
set object 3632 polygon from \
  -1.29729, 77.4526 to \
  -0.03, 77.4526 to \
  -0.03, 41.092 to \
  -1.29729, 41.092 to \
  -1.29729, 77.4526 front fs empty border lc rgb '#549f' lw 0.1
set object 3633 polygon from \
  -1.32794, 77.4762 to \
  -0.03, 77.4762 to \
  -0.03, 41.1056 to \
  -1.32794, 41.1056 to \
  -1.32794, 77.4762 front fs empty border lc rgb '#549f' lw 0.1
set object 3634 polygon from \
  -1.35787, 77.4997 to \
  -0.03, 77.4997 to \
  -0.03, 41.1191 to \
  -1.35787, 41.1191 to \
  -1.35787, 77.4997 front fs empty border lc rgb '#549f' lw 0.1
set object 3635 polygon from \
  -1.38707, 77.5233 to \
  -0.03, 77.5233 to \
  -0.03, 41.1326 to \
  -1.38707, 41.1326 to \
  -1.38707, 77.5233 front fs empty border lc rgb '#549f' lw 0.1
set object 3636 polygon from \
  -1.43169, 77.5468 to \
  -0.03, 77.5468 to \
  -0.03, 41.1462 to \
  -1.43169, 41.1462 to \
  -1.43169, 77.5468 front fs empty border lc rgb '#549f' lw 0.1
set object 3637 polygon from \
  -1.47675, 77.5704 to \
  -0.03, 77.5704 to \
  -0.03, 41.1597 to \
  -1.47675, 41.1597 to \
  -1.47675, 77.5704 front fs empty border lc rgb '#549f' lw 0.1
set object 3638 polygon from \
  -1.52119, 77.5939 to \
  -0.03, 77.5939 to \
  -0.03, 41.1733 to \
  -1.52119, 41.1733 to \
  -1.52119, 77.5939 front fs empty border lc rgb '#549f' lw 0.1
set object 3639 polygon from \
  -1.56501, 77.6175 to \
  -0.03, 77.6175 to \
  -0.03, 41.1868 to \
  -1.56501, 41.1868 to \
  -1.56501, 77.6175 front fs empty border lc rgb '#549f' lw 0.1
set object 3640 polygon from \
  -1.60817, 77.641 to \
  -0.03, 77.641 to \
  -0.03, 41.2004 to \
  -1.60817, 41.2004 to \
  -1.60817, 77.641 front fs empty border lc rgb '#549f' lw 0.1
set object 3641 polygon from \
  -1.65066, 77.6646 to \
  -0.03, 77.6646 to \
  -0.03, 41.2139 to \
  -1.65066, 41.2139 to \
  -1.65066, 77.6646 front fs empty border lc rgb '#549f' lw 0.1
set object 3642 polygon from \
  -1.69246, 77.6881 to \
  -0.03, 77.6881 to \
  -0.03, 41.2274 to \
  -1.69246, 41.2274 to \
  -1.69246, 77.6881 front fs empty border lc rgb '#549f' lw 0.1
set object 3643 polygon from \
  -1.73355, 77.7117 to \
  -0.03, 77.7117 to \
  -0.03, 41.241 to \
  -1.73355, 41.241 to \
  -1.73355, 77.7117 front fs empty border lc rgb '#549f' lw 0.1
set object 3644 polygon from \
  -1.77393, 77.7352 to \
  -0.03, 77.7352 to \
  -0.03, 41.2545 to \
  -1.77393, 41.2545 to \
  -1.77393, 77.7352 front fs empty border lc rgb '#549f' lw 0.1
set object 3645 polygon from \
  -1.81356, 77.7588 to \
  -0.03, 77.7588 to \
  -0.03, 41.2681 to \
  -1.81356, 41.2681 to \
  -1.81356, 77.7588 front fs empty border lc rgb '#549f' lw 0.1
set object 3646 polygon from \
  -1.85244, 77.7823 to \
  -0.03, 77.7823 to \
  -0.03, 41.2817 to \
  -1.85244, 41.2817 to \
  -1.85244, 77.7823 front fs empty border lc rgb '#549f' lw 0.1
set object 3647 polygon from \
  -1.89055, 77.8059 to \
  -0.03, 77.8059 to \
  -0.03, 41.2952 to \
  -1.89055, 41.2952 to \
  -1.89055, 77.8059 front fs empty border lc rgb '#549f' lw 0.1
set object 3648 polygon from \
  -1.92787, 77.8294 to \
  -0.03, 77.8294 to \
  -0.03, 41.3088 to \
  -1.92787, 41.3088 to \
  -1.92787, 77.8294 front fs empty border lc rgb '#549f' lw 0.1
set object 3649 polygon from \
  -1.96439, 77.853 to \
  -0.03, 77.853 to \
  -0.03, 41.3223 to \
  -1.96439, 41.3223 to \
  -1.96439, 77.853 front fs empty border lc rgb '#549f' lw 0.1
set object 3650 polygon from \
  -2.0001, 77.8766 to \
  -0.03, 77.8766 to \
  -0.03, 41.3359 to \
  -2.0001, 41.3359 to \
  -2.0001, 77.8766 front fs empty border lc rgb '#549f' lw 0.1
set object 3651 polygon from \
  -2.03497, 77.9001 to \
  -0.03, 77.9001 to \
  -0.03, 41.3494 to \
  -2.03497, 41.3494 to \
  -2.03497, 77.9001 front fs empty border lc rgb '#549f' lw 0.1
set object 3652 polygon from \
  -2.069, 77.9237 to \
  -0.03, 77.9237 to \
  -0.03, 41.363 to \
  -2.069, 41.363 to \
  -2.069, 77.9237 front fs empty border lc rgb '#549f' lw 0.1
set object 3653 polygon from \
  -2.10217, 77.9473 to \
  -0.03, 77.9473 to \
  -0.03, 41.3766 to \
  -2.10217, 41.3766 to \
  -2.10217, 77.9473 front fs empty border lc rgb '#549f' lw 0.1
set object 3654 polygon from \
  -2.13448, 77.9708 to \
  -0.03, 77.9708 to \
  -0.03, 41.3901 to \
  -2.13448, 41.3901 to \
  -2.13448, 77.9708 front fs empty border lc rgb '#549f' lw 0.1
set object 3655 polygon from \
  -2.1659, 77.9944 to \
  -0.03, 77.9944 to \
  -0.03, 41.4037 to \
  -2.1659, 41.4037 to \
  -2.1659, 77.9944 front fs empty border lc rgb '#549f' lw 0.1
set object 3656 polygon from \
  -2.19643, 78.018 to \
  -0.03, 78.018 to \
  -0.03, 41.4173 to \
  -2.19643, 41.4173 to \
  -2.19643, 78.018 front fs empty border lc rgb '#549f' lw 0.1
set object 3657 polygon from \
  -2.22606, 78.0415 to \
  -0.03, 78.0415 to \
  -0.03, 41.4308 to \
  -2.22606, 41.4308 to \
  -2.22606, 78.0415 front fs empty border lc rgb '#549f' lw 0.1
set object 3658 polygon from \
  -2.25477, 78.0651 to \
  -0.03, 78.0651 to \
  -0.03, 41.4444 to \
  -2.25477, 41.4444 to \
  -2.25477, 78.0651 front fs empty border lc rgb '#549f' lw 0.1
set object 3659 polygon from \
  -2.28256, 78.0887 to \
  -0.03, 78.0887 to \
  -0.03, 41.458 to \
  -2.28256, 41.458 to \
  -2.28256, 78.0887 front fs empty border lc rgb '#549f' lw 0.1
set object 3660 polygon from \
  -2.30941, 78.1123 to \
  -0.03, 78.1123 to \
  -0.03, 41.4715 to \
  -2.30941, 41.4715 to \
  -2.30941, 78.1123 front fs empty border lc rgb '#549f' lw 0.1
set object 3661 polygon from \
  -2.33532, 78.1358 to \
  -0.03, 78.1358 to \
  -0.03, 41.4851 to \
  -2.33532, 41.4851 to \
  -2.33532, 78.1358 front fs empty border lc rgb '#549f' lw 0.1
set object 3662 polygon from \
  -2.36028, 78.1594 to \
  -0.03, 78.1594 to \
  -0.03, 41.4987 to \
  -2.36028, 41.4987 to \
  -2.36028, 78.1594 front fs empty border lc rgb '#549f' lw 0.1
set object 3663 polygon from \
  -2.38428, 78.183 to \
  -0.03, 78.183 to \
  -0.03, 41.5122 to \
  -2.38428, 41.5122 to \
  -2.38428, 78.183 front fs empty border lc rgb '#549f' lw 0.1
set object 3664 polygon from \
  -2.40731, 78.2066 to \
  -0.03, 78.2066 to \
  -0.03, 41.5258 to \
  -2.40731, 41.5258 to \
  -2.40731, 78.2066 front fs empty border lc rgb '#549f' lw 0.1
set object 3665 polygon from \
  -2.42937, 78.2301 to \
  -0.03, 78.2301 to \
  -0.03, 41.5394 to \
  -2.42937, 41.5394 to \
  -2.42937, 78.2301 front fs empty border lc rgb '#549f' lw 0.1
set object 3666 polygon from \
  -2.45044, 78.2537 to \
  -0.03, 78.2537 to \
  -0.03, 41.553 to \
  -2.45044, 41.553 to \
  -2.45044, 78.2537 front fs empty border lc rgb '#549f' lw 0.1
set object 3667 polygon from \
  -2.47053, 78.2773 to \
  -0.03, 78.2773 to \
  -0.03, 41.5666 to \
  -2.47053, 41.5666 to \
  -2.47053, 78.2773 front fs empty border lc rgb '#549f' lw 0.1
set object 3668 polygon from \
  -2.48963, 78.3009 to \
  -0.03, 78.3009 to \
  -0.03, 41.5801 to \
  -2.48963, 41.5801 to \
  -2.48963, 78.3009 front fs empty border lc rgb '#549f' lw 0.1
set object 3669 polygon from \
  -2.50773, 78.3245 to \
  -0.03, 78.3245 to \
  -0.03, 41.5937 to \
  -2.50773, 41.5937 to \
  -2.50773, 78.3245 front fs empty border lc rgb '#549f' lw 0.1
set object 3670 polygon from \
  -2.52533, 78.3481 to \
  -0.03, 78.3481 to \
  -0.03, 41.6073 to \
  -2.52533, 41.6073 to \
  -2.52533, 78.3481 front fs empty border lc rgb '#549f' lw 0.1
set object 3671 polygon from \
  -2.54467, 78.3717 to \
  -0.03, 78.3717 to \
  -0.03, 41.6209 to \
  -2.54467, 41.6209 to \
  -2.54467, 78.3717 front fs empty border lc rgb '#549f' lw 0.1
set object 3672 polygon from \
  -2.563, 78.3952 to \
  -0.03, 78.3952 to \
  -0.03, 41.6345 to \
  -2.563, 41.6345 to \
  -2.563, 78.3952 front fs empty border lc rgb '#549f' lw 0.1
set object 3673 polygon from \
  -2.58032, 78.4188 to \
  -0.03, 78.4188 to \
  -0.03, 41.6481 to \
  -2.58032, 41.6481 to \
  -2.58032, 78.4188 front fs empty border lc rgb '#549f' lw 0.1
set object 3674 polygon from \
  -2.5966, 78.4424 to \
  -0.03, 78.4424 to \
  -0.03, 41.6616 to \
  -2.5966, 41.6616 to \
  -2.5966, 78.4424 front fs empty border lc rgb '#549f' lw 0.1
set object 3675 polygon from \
  -2.61186, 78.466 to \
  -0.03, 78.466 to \
  -0.03, 41.6752 to \
  -2.61186, 41.6752 to \
  -2.61186, 78.466 front fs empty border lc rgb '#549f' lw 0.1
set object 3676 polygon from \
  -2.62609, 78.4896 to \
  -0.03, 78.4896 to \
  -0.03, 41.6888 to \
  -2.62609, 41.6888 to \
  -2.62609, 78.4896 front fs empty border lc rgb '#549f' lw 0.1
set object 3677 polygon from \
  -2.63928, 78.5132 to \
  -0.03, 78.5132 to \
  -0.03, 41.7024 to \
  -2.63928, 41.7024 to \
  -2.63928, 78.5132 front fs empty border lc rgb '#549f' lw 0.1
set object 3678 polygon from \
  -2.65143, 78.5368 to \
  -0.03, 78.5368 to \
  -0.03, 41.716 to \
  -2.65143, 41.716 to \
  -2.65143, 78.5368 front fs empty border lc rgb '#549f' lw 0.1
set object 3679 polygon from \
  -2.66254, 78.5604 to \
  -0.03, 78.5604 to \
  -0.03, 41.7296 to \
  -2.66254, 41.7296 to \
  -2.66254, 78.5604 front fs empty border lc rgb '#549f' lw 0.1
set object 3680 polygon from \
  -2.67262, 78.584 to \
  -0.03, 78.584 to \
  -0.03, 41.7432 to \
  -2.67262, 41.7432 to \
  -2.67262, 78.584 front fs empty border lc rgb '#549f' lw 0.1
set object 3681 polygon from \
  -2.68164, 78.6076 to \
  -0.03, 78.6076 to \
  -0.03, 41.7568 to \
  -2.68164, 41.7568 to \
  -2.68164, 78.6076 front fs empty border lc rgb '#549f' lw 0.1
set object 3682 polygon from \
  -2.68963, 78.6312 to \
  -0.03, 78.6312 to \
  -0.03, 41.7704 to \
  -2.68963, 41.7704 to \
  -2.68963, 78.6312 front fs empty border lc rgb '#549f' lw 0.1
set object 3683 polygon from \
  -2.69657, 78.6548 to \
  -0.03, 78.6548 to \
  -0.03, 41.784 to \
  -2.69657, 41.784 to \
  -2.69657, 78.6548 front fs empty border lc rgb '#549f' lw 0.1
set object 3684 polygon from \
  -2.70247, 78.6784 to \
  -0.03, 78.6784 to \
  -0.03, 41.7976 to \
  -2.70247, 41.7976 to \
  -2.70247, 78.6784 front fs empty border lc rgb '#549f' lw 0.1
set object 3685 polygon from \
  -2.70733, 78.702 to \
  -0.03, 78.702 to \
  -0.03, 41.8112 to \
  -2.70733, 41.8112 to \
  -2.70733, 78.702 front fs empty border lc rgb '#549f' lw 0.1
set object 3686 polygon from \
  -2.71115, 78.7256 to \
  -0.03, 78.7256 to \
  -0.03, 41.8248 to \
  -2.71115, 41.8248 to \
  -2.71115, 78.7256 front fs empty border lc rgb '#549f' lw 0.1
set object 3687 polygon from \
  -2.71394, 78.7492 to \
  -0.03, 78.7492 to \
  -0.03, 41.8384 to \
  -2.71394, 41.8384 to \
  -2.71394, 78.7492 front fs empty border lc rgb '#549f' lw 0.1
set object 3688 polygon from \
  -2.71569, 78.7728 to \
  -0.03, 78.7728 to \
  -0.03, 41.852 to \
  -2.71569, 41.852 to \
  -2.71569, 78.7728 front fs empty border lc rgb '#549f' lw 0.1
set object 3689 polygon from \
  -2.71641, 78.7965 to \
  -0.03, 78.7965 to \
  -0.03, 41.8656 to \
  -2.71641, 41.8656 to \
  -2.71641, 78.7965 front fs empty border lc rgb '#549f' lw 0.1
set object 3690 polygon from \
  -2.71641, 78.8201 to \
  -0.03, 78.8201 to \
  -0.03, 41.8792 to \
  -2.71641, 41.8792 to \
  -2.71641, 78.8201 front fs empty border lc rgb '#549f' lw 0.1
set object 3691 polygon from \
  -2.7161, 78.8437 to \
  -0.03, 78.8437 to \
  -0.03, 41.8928 to \
  -2.7161, 41.8928 to \
  -2.7161, 78.8437 front fs empty border lc rgb '#549f' lw 0.1
set object 3692 polygon from \
  -2.71477, 78.8673 to \
  -0.03, 78.8673 to \
  -0.03, 41.9064 to \
  -2.71477, 41.9064 to \
  -2.71477, 78.8673 front fs empty border lc rgb '#549f' lw 0.1
set object 3693 polygon from \
  -2.71242, 78.8909 to \
  -0.03, 78.8909 to \
  -0.03, 41.9201 to \
  -2.71242, 41.9201 to \
  -2.71242, 78.8909 front fs empty border lc rgb '#549f' lw 0.1
set object 3694 polygon from \
  -2.70906, 78.9145 to \
  -0.03, 78.9145 to \
  -0.03, 41.9337 to \
  -2.70906, 41.9337 to \
  -2.70906, 78.9145 front fs empty border lc rgb '#549f' lw 0.1
set object 3695 polygon from \
  -2.7047, 78.9381 to \
  -0.03, 78.9381 to \
  -0.03, 41.9473 to \
  -2.7047, 41.9473 to \
  -2.7047, 78.9381 front fs empty border lc rgb '#549f' lw 0.1
set object 3696 polygon from \
  -2.69934, 78.9618 to \
  -0.03, 78.9618 to \
  -0.03, 41.9609 to \
  -2.69934, 41.9609 to \
  -2.69934, 78.9618 front fs empty border lc rgb '#549f' lw 0.1
set object 3697 polygon from \
  -2.69298, 78.9854 to \
  -0.03, 78.9854 to \
  -0.03, 41.9745 to \
  -2.69298, 41.9745 to \
  -2.69298, 78.9854 front fs empty border lc rgb '#549f' lw 0.1
set object 3698 polygon from \
  -2.68565, 79.009 to \
  -0.03, 79.009 to \
  -0.03, 41.9881 to \
  -2.68565, 41.9881 to \
  -2.68565, 79.009 front fs empty border lc rgb '#549f' lw 0.1
set object 3699 polygon from \
  -2.67733, 79.0326 to \
  -0.03, 79.0326 to \
  -0.03, 42.0018 to \
  -2.67733, 42.0018 to \
  -2.67733, 79.0326 front fs empty border lc rgb '#549f' lw 0.1
set object 3700 polygon from \
  -2.66805, 79.0563 to \
  -0.03, 79.0563 to \
  -0.03, 42.0154 to \
  -2.66805, 42.0154 to \
  -2.66805, 79.0563 front fs empty border lc rgb '#549f' lw 0.1
set object 3701 polygon from \
  -2.6578, 79.0799 to \
  -0.03, 79.0799 to \
  -0.03, 42.029 to \
  -2.6578, 42.029 to \
  -2.6578, 79.0799 front fs empty border lc rgb '#549f' lw 0.1
set object 3702 polygon from \
  -2.64661, 79.1035 to \
  -0.03, 79.1035 to \
  -0.03, 42.0426 to \
  -2.64661, 42.0426 to \
  -2.64661, 79.1035 front fs empty border lc rgb '#549f' lw 0.1
set object 3703 polygon from \
  -2.63448, 79.1271 to \
  -0.03, 79.1271 to \
  -0.03, 42.0562 to \
  -2.63448, 42.0562 to \
  -2.63448, 79.1271 front fs empty border lc rgb '#549f' lw 0.1
set object 3704 polygon from \
  -2.62142, 79.1508 to \
  -0.03, 79.1508 to \
  -0.03, 42.0699 to \
  -2.62142, 42.0699 to \
  -2.62142, 79.1508 front fs empty border lc rgb '#549f' lw 0.1
set object 3705 polygon from \
  -2.60744, 79.1744 to \
  -0.03, 79.1744 to \
  -0.03, 42.0835 to \
  -2.60744, 42.0835 to \
  -2.60744, 79.1744 front fs empty border lc rgb '#549f' lw 0.1
set object 3706 polygon from \
  -2.59255, 79.198 to \
  -0.03, 79.198 to \
  -0.03, 42.0971 to \
  -2.59255, 42.0971 to \
  -2.59255, 79.198 front fs empty border lc rgb '#549f' lw 0.1
set object 3707 polygon from \
  -2.57677, 79.2217 to \
  -0.03, 79.2217 to \
  -0.03, 42.1108 to \
  -2.57677, 42.1108 to \
  -2.57677, 79.2217 front fs empty border lc rgb '#549f' lw 0.1
set object 3708 polygon from \
  -2.56905, 79.2453 to \
  -0.03, 79.2453 to \
  -0.03, 42.1244 to \
  -2.56905, 42.1244 to \
  -2.56905, 79.2453 front fs empty border lc rgb '#549f' lw 0.1
set object 3709 polygon from \
  -2.56172, 79.2689 to \
  -0.03, 79.2689 to \
  -0.03, 42.138 to \
  -2.56172, 42.138 to \
  -2.56172, 79.2689 front fs empty border lc rgb '#549f' lw 0.1
set object 3710 polygon from \
  -2.5535, 79.2926 to \
  -0.03, 79.2926 to \
  -0.03, 42.1517 to \
  -2.5535, 42.1517 to \
  -2.5535, 79.2926 front fs empty border lc rgb '#549f' lw 0.1
set object 3711 polygon from \
  -2.54439, 79.3162 to \
  -0.03, 79.3162 to \
  -0.03, 42.1653 to \
  -2.54439, 42.1653 to \
  -2.54439, 79.3162 front fs empty border lc rgb '#549f' lw 0.1
set object 3712 polygon from \
  -2.53439, 79.3398 to \
  -0.03, 79.3398 to \
  -0.03, 42.1789 to \
  -2.53439, 42.1789 to \
  -2.53439, 79.3398 front fs empty border lc rgb '#549f' lw 0.1
set object 3713 polygon from \
  -2.52353, 79.3635 to \
  -0.03, 79.3635 to \
  -0.03, 42.1926 to \
  -2.52353, 42.1926 to \
  -2.52353, 79.3635 front fs empty border lc rgb '#549f' lw 0.1
set object 3714 polygon from \
  -2.5118, 79.3871 to \
  -0.03, 79.3871 to \
  -0.03, 42.2062 to \
  -2.5118, 42.2062 to \
  -2.5118, 79.3871 front fs empty border lc rgb '#549f' lw 0.1
set object 3715 polygon from \
  -2.49923, 79.4108 to \
  -0.03, 79.4108 to \
  -0.03, 42.2198 to \
  -2.49923, 42.2198 to \
  -2.49923, 79.4108 front fs empty border lc rgb '#549f' lw 0.1
set object 3716 polygon from \
  -2.48583, 79.4344 to \
  -0.03, 79.4344 to \
  -0.03, 42.2335 to \
  -2.48583, 42.2335 to \
  -2.48583, 79.4344 front fs empty border lc rgb '#549f' lw 0.1
set object 3717 polygon from \
  -2.47161, 79.4581 to \
  -0.03, 79.4581 to \
  -0.03, 42.2471 to \
  -2.47161, 42.2471 to \
  -2.47161, 79.4581 front fs empty border lc rgb '#549f' lw 0.1
set object 3718 polygon from \
  -2.45657, 79.4817 to \
  -0.03, 79.4817 to \
  -0.03, 42.2608 to \
  -2.45657, 42.2608 to \
  -2.45657, 79.4817 front fs empty border lc rgb '#549f' lw 0.1
set object 3719 polygon from \
  -2.44074, 79.5054 to \
  -0.03, 79.5054 to \
  -0.03, 42.2744 to \
  -2.44074, 42.2744 to \
  -2.44074, 79.5054 front fs empty border lc rgb '#549f' lw 0.1
set object 3720 polygon from \
  -2.42413, 79.529 to \
  -0.03, 79.529 to \
  -0.03, 42.2881 to \
  -2.42413, 42.2881 to \
  -2.42413, 79.529 front fs empty border lc rgb '#549f' lw 0.1
set object 3721 polygon from \
  -2.40675, 79.5527 to \
  -0.03, 79.5527 to \
  -0.03, 42.3017 to \
  -2.40675, 42.3017 to \
  -2.40675, 79.5527 front fs empty border lc rgb '#549f' lw 0.1
set object 3722 polygon from \
  -2.42634, 79.5763 to \
  -0.03, 79.5763 to \
  -0.03, 42.3153 to \
  -2.42634, 42.3153 to \
  -2.42634, 79.5763 front fs empty border lc rgb '#549f' lw 0.1
set object 3723 polygon from \
  -2.44933, 79.6 to \
  -0.03, 79.6 to \
  -0.03, 42.329 to \
  -2.44933, 42.329 to \
  -2.44933, 79.6 front fs empty border lc rgb '#549f' lw 0.1
set object 3724 polygon from \
  -2.47176, 79.6236 to \
  -0.03, 79.6236 to \
  -0.03, 42.3426 to \
  -2.47176, 42.3426 to \
  -2.47176, 79.6236 front fs empty border lc rgb '#549f' lw 0.1
set object 3725 polygon from \
  -2.49364, 79.6473 to \
  -0.03, 79.6473 to \
  -0.03, 42.3563 to \
  -2.49364, 42.3563 to \
  -2.49364, 79.6473 front fs empty border lc rgb '#549f' lw 0.1
set object 3726 polygon from \
  -2.51494, 79.6709 to \
  -0.03, 79.6709 to \
  -0.03, 42.37 to \
  -2.51494, 42.37 to \
  -2.51494, 79.6709 front fs empty border lc rgb '#549f' lw 0.1
set object 3727 polygon from \
  -2.53564, 79.6946 to \
  -0.03, 79.6946 to \
  -0.03, 42.3836 to \
  -2.53564, 42.3836 to \
  -2.53564, 79.6946 front fs empty border lc rgb '#549f' lw 0.1
set object 3728 polygon from \
  -2.55573, 79.7182 to \
  -0.03, 79.7182 to \
  -0.03, 42.3973 to \
  -2.55573, 42.3973 to \
  -2.55573, 79.7182 front fs empty border lc rgb '#549f' lw 0.1
set object 3729 polygon from \
  -2.57521, 79.7419 to \
  -0.03, 79.7419 to \
  -0.03, 42.4109 to \
  -2.57521, 42.4109 to \
  -2.57521, 79.7419 front fs empty border lc rgb '#549f' lw 0.1
set object 3730 polygon from \
  -2.59404, 79.7656 to \
  -0.03, 79.7656 to \
  -0.03, 42.4246 to \
  -2.59404, 42.4246 to \
  -2.59404, 79.7656 front fs empty border lc rgb '#549f' lw 0.1
set object 3731 polygon from \
  -2.61223, 79.7892 to \
  -0.03, 79.7892 to \
  -0.03, 42.4382 to \
  -2.61223, 42.4382 to \
  -2.61223, 79.7892 front fs empty border lc rgb '#549f' lw 0.1
set object 3732 polygon from \
  -2.62975, 79.8129 to \
  -0.03, 79.8129 to \
  -0.03, 42.4519 to \
  -2.62975, 42.4519 to \
  -2.62975, 79.8129 front fs empty border lc rgb '#549f' lw 0.1
set object 3733 polygon from \
  -2.64659, 79.8366 to \
  -0.03, 79.8366 to \
  -0.03, 42.4656 to \
  -2.64659, 42.4656 to \
  -2.64659, 79.8366 front fs empty border lc rgb '#549f' lw 0.1
set object 3734 polygon from \
  -2.66273, 79.8602 to \
  -0.03, 79.8602 to \
  -0.03, 42.4792 to \
  -2.66273, 42.4792 to \
  -2.66273, 79.8602 front fs empty border lc rgb '#549f' lw 0.1
set object 3735 polygon from \
  -2.67817, 79.8839 to \
  -0.03, 79.8839 to \
  -0.03, 42.4929 to \
  -2.67817, 42.4929 to \
  -2.67817, 79.8839 front fs empty border lc rgb '#549f' lw 0.1
set object 3736 polygon from \
  -2.6929, 79.9076 to \
  -0.03, 79.9076 to \
  -0.03, 42.5066 to \
  -2.6929, 42.5066 to \
  -2.6929, 79.9076 front fs empty border lc rgb '#549f' lw 0.1
set object 3737 polygon from \
  -2.70689, 79.9312 to \
  -0.03, 79.9312 to \
  -0.03, 42.5202 to \
  -2.70689, 42.5202 to \
  -2.70689, 79.9312 front fs empty border lc rgb '#549f' lw 0.1
set object 3738 polygon from \
  -2.72013, 79.9549 to \
  -0.03, 79.9549 to \
  -0.03, 42.5339 to \
  -2.72013, 42.5339 to \
  -2.72013, 79.9549 front fs empty border lc rgb '#549f' lw 0.1
set object 3739 polygon from \
  -2.73262, 79.9786 to \
  -0.03, 79.9786 to \
  -0.03, 42.5476 to \
  -2.73262, 42.5476 to \
  -2.73262, 79.9786 front fs empty border lc rgb '#549f' lw 0.1
set object 3740 polygon from \
  -2.74434, 80.0023 to \
  -0.03, 80.0023 to \
  -0.03, 42.5612 to \
  -2.74434, 42.5612 to \
  -2.74434, 80.0023 front fs empty border lc rgb '#549f' lw 0.1
set object 3741 polygon from \
  -2.75528, 80.0259 to \
  -0.03, 80.0259 to \
  -0.03, 42.5749 to \
  -2.75528, 42.5749 to \
  -2.75528, 80.0259 front fs empty border lc rgb '#549f' lw 0.1
set object 3742 polygon from \
  -2.76543, 80.0496 to \
  -0.03, 80.0496 to \
  -0.03, 42.5886 to \
  -2.76543, 42.5886 to \
  -2.76543, 80.0496 front fs empty border lc rgb '#549f' lw 0.1
set object 3743 polygon from \
  -2.77477, 80.0733 to \
  -0.03, 80.0733 to \
  -0.03, 42.6022 to \
  -2.77477, 42.6022 to \
  -2.77477, 80.0733 front fs empty border lc rgb '#549f' lw 0.1
set object 3744 polygon from \
  -2.7833, 80.097 to \
  -0.03, 80.097 to \
  -0.03, 42.6159 to \
  -2.7833, 42.6159 to \
  -2.7833, 80.097 front fs empty border lc rgb '#549f' lw 0.1
set object 3745 polygon from \
  -2.791, 80.1206 to \
  -0.03, 80.1206 to \
  -0.03, 42.6296 to \
  -2.791, 42.6296 to \
  -2.791, 80.1206 front fs empty border lc rgb '#549f' lw 0.1
set object 3746 polygon from \
  -2.79787, 80.1443 to \
  -0.03, 80.1443 to \
  -0.03, 42.6433 to \
  -2.79787, 42.6433 to \
  -2.79787, 80.1443 front fs empty border lc rgb '#549f' lw 0.1
set object 3747 polygon from \
  -2.8039, 80.168 to \
  -0.03, 80.168 to \
  -0.03, 42.657 to \
  -2.8039, 42.657 to \
  -2.8039, 80.168 front fs empty border lc rgb '#549f' lw 0.1
set object 3748 polygon from \
  -2.80907, 80.1917 to \
  -0.03, 80.1917 to \
  -0.03, 42.6706 to \
  -2.80907, 42.6706 to \
  -2.80907, 80.1917 front fs empty border lc rgb '#549f' lw 0.1
set object 3749 polygon from \
  -2.81338, 80.2154 to \
  -0.03, 80.2154 to \
  -0.03, 42.6843 to \
  -2.81338, 42.6843 to \
  -2.81338, 80.2154 front fs empty border lc rgb '#549f' lw 0.1
set object 3750 polygon from \
  -2.81903, 80.2391 to \
  -0.03, 80.2391 to \
  -0.03, 42.698 to \
  -2.81903, 42.698 to \
  -2.81903, 80.2391 front fs empty border lc rgb '#549f' lw 0.1
set object 3751 polygon from \
  -2.83035, 80.2628 to \
  -0.03, 80.2628 to \
  -0.03, 42.7117 to \
  -2.83035, 42.7117 to \
  -2.83035, 80.2628 front fs empty border lc rgb '#549f' lw 0.1
set object 3752 polygon from \
  -2.84081, 80.2864 to \
  -0.03, 80.2864 to \
  -0.03, 42.7254 to \
  -2.84081, 42.7254 to \
  -2.84081, 80.2864 front fs empty border lc rgb '#549f' lw 0.1
set object 3753 polygon from \
  -2.85039, 80.3101 to \
  -0.03, 80.3101 to \
  -0.03, 42.7391 to \
  -2.85039, 42.7391 to \
  -2.85039, 80.3101 front fs empty border lc rgb '#549f' lw 0.1
set object 3754 polygon from \
  -2.85908, 80.3338 to \
  -0.03, 80.3338 to \
  -0.03, 42.7527 to \
  -2.85908, 42.7527 to \
  -2.85908, 80.3338 front fs empty border lc rgb '#549f' lw 0.1
set object 3755 polygon from \
  -2.86687, 80.3575 to \
  -0.03, 80.3575 to \
  -0.03, 42.7664 to \
  -2.86687, 42.7664 to \
  -2.86687, 80.3575 front fs empty border lc rgb '#549f' lw 0.1
set object 3756 polygon from \
  -2.87375, 80.3812 to \
  -0.03, 80.3812 to \
  -0.03, 42.7801 to \
  -2.87375, 42.7801 to \
  -2.87375, 80.3812 front fs empty border lc rgb '#549f' lw 0.1
set object 3757 polygon from \
  -2.87971, 80.4049 to \
  -0.03, 80.4049 to \
  -0.03, 42.7938 to \
  -2.87971, 42.7938 to \
  -2.87971, 80.4049 front fs empty border lc rgb '#549f' lw 0.1
set object 3758 polygon from \
  -2.88475, 80.4286 to \
  -0.03, 80.4286 to \
  -0.03, 42.8075 to \
  -2.88475, 42.8075 to \
  -2.88475, 80.4286 front fs empty border lc rgb '#549f' lw 0.1
set object 3759 polygon from \
  -2.88885, 80.4523 to \
  -0.03, 80.4523 to \
  -0.03, 42.8212 to \
  -2.88885, 42.8212 to \
  -2.88885, 80.4523 front fs empty border lc rgb '#549f' lw 0.1
set object 3760 polygon from \
  -2.89202, 80.476 to \
  -0.03, 80.476 to \
  -0.03, 42.8349 to \
  -2.89202, 42.8349 to \
  -2.89202, 80.476 front fs empty border lc rgb '#549f' lw 0.1
set object 3761 polygon from \
  -2.89423, 80.4997 to \
  -0.03, 80.4997 to \
  -0.03, 42.8486 to \
  -2.89423, 42.8486 to \
  -2.89423, 80.4997 front fs empty border lc rgb '#549f' lw 0.1
set object 3762 polygon from \
  -2.89549, 80.5234 to \
  -0.03, 80.5234 to \
  -0.03, 42.8623 to \
  -2.89549, 42.8623 to \
  -2.89549, 80.5234 front fs empty border lc rgb '#549f' lw 0.1
set object 3763 polygon from \
  -2.89579, 80.5471 to \
  -0.03, 80.5471 to \
  -0.03, 42.876 to \
  -2.89579, 42.876 to \
  -2.89579, 80.5471 front fs empty border lc rgb '#549f' lw 0.1
set object 3764 polygon from \
  -2.89579, 80.5708 to \
  -0.03, 80.5708 to \
  -0.03, 42.8897 to \
  -2.89579, 42.8897 to \
  -2.89579, 80.5708 front fs empty border lc rgb '#549f' lw 0.1
set object 3765 polygon from \
  -2.89512, 80.5945 to \
  -0.03, 80.5945 to \
  -0.03, 42.9034 to \
  -2.89512, 42.9034 to \
  -2.89512, 80.5945 front fs empty border lc rgb '#549f' lw 0.1
set object 3766 polygon from \
  -2.89348, 80.6182 to \
  -0.03, 80.6182 to \
  -0.03, 42.9171 to \
  -2.89348, 42.9171 to \
  -2.89348, 80.6182 front fs empty border lc rgb '#549f' lw 0.1
set object 3767 polygon from \
  -2.89086, 80.6419 to \
  -0.03, 80.6419 to \
  -0.03, 42.9308 to \
  -2.89086, 42.9308 to \
  -2.89086, 80.6419 front fs empty border lc rgb '#549f' lw 0.1
set object 3768 polygon from \
  -2.89022, 80.6656 to \
  -0.03, 80.6656 to \
  -0.03, 42.9445 to \
  -2.89022, 42.9445 to \
  -2.89022, 80.6656 front fs empty border lc rgb '#549f' lw 0.1
set object 3769 polygon from \
  -2.88992, 80.6894 to \
  -0.03, 80.6894 to \
  -0.03, 42.9582 to \
  -2.88992, 42.9582 to \
  -2.88992, 80.6894 front fs empty border lc rgb '#549f' lw 0.1
set object 3770 polygon from \
  -2.88868, 80.7131 to \
  -0.03, 80.7131 to \
  -0.03, 42.9719 to \
  -2.88868, 42.9719 to \
  -2.88868, 80.7131 front fs empty border lc rgb '#549f' lw 0.1
set object 3771 polygon from \
  -2.8865, 80.7368 to \
  -0.03, 80.7368 to \
  -0.03, 42.9856 to \
  -2.8865, 42.9856 to \
  -2.8865, 80.7368 front fs empty border lc rgb '#549f' lw 0.1
set object 3772 polygon from \
  -2.88336, 80.7605 to \
  -0.03, 80.7605 to \
  -0.03, 42.9993 to \
  -2.88336, 42.9993 to \
  -2.88336, 80.7605 front fs empty border lc rgb '#549f' lw 0.1
set object 3773 polygon from \
  -2.87927, 80.7842 to \
  -0.03, 80.7842 to \
  -0.03, 43.0131 to \
  -2.87927, 43.0131 to \
  -2.87927, 80.7842 front fs empty border lc rgb '#549f' lw 0.1
set object 3774 polygon from \
  -2.87422, 80.8079 to \
  -0.03, 80.8079 to \
  -0.03, 43.0268 to \
  -2.87422, 43.0268 to \
  -2.87422, 80.8079 front fs empty border lc rgb '#549f' lw 0.1
set object 3775 polygon from \
  -2.86821, 80.8316 to \
  -0.03, 80.8316 to \
  -0.03, 43.0405 to \
  -2.86821, 43.0405 to \
  -2.86821, 80.8316 front fs empty border lc rgb '#549f' lw 0.1
set object 3776 polygon from \
  -2.86123, 80.8554 to \
  -0.03, 80.8554 to \
  -0.03, 43.0542 to \
  -2.86123, 43.0542 to \
  -2.86123, 80.8554 front fs empty border lc rgb '#549f' lw 0.1
set object 3777 polygon from \
  -2.85328, 80.8791 to \
  -0.03, 80.8791 to \
  -0.03, 43.0679 to \
  -2.85328, 43.0679 to \
  -2.85328, 80.8791 front fs empty border lc rgb '#549f' lw 0.1
set object 3778 polygon from \
  -2.84436, 80.9028 to \
  -0.03, 80.9028 to \
  -0.03, 43.0816 to \
  -2.84436, 43.0816 to \
  -2.84436, 80.9028 front fs empty border lc rgb '#549f' lw 0.1
set object 3779 polygon from \
  -2.83446, 80.9265 to \
  -0.03, 80.9265 to \
  -0.03, 43.0954 to \
  -2.83446, 43.0954 to \
  -2.83446, 80.9265 front fs empty border lc rgb '#549f' lw 0.1
set object 3780 polygon from \
  -2.82359, 80.9503 to \
  -0.03, 80.9503 to \
  -0.03, 43.1091 to \
  -2.82359, 43.1091 to \
  -2.82359, 80.9503 front fs empty border lc rgb '#549f' lw 0.1
set object 3781 polygon from \
  -2.81174, 80.974 to \
  -0.03, 80.974 to \
  -0.03, 43.1228 to \
  -2.81174, 43.1228 to \
  -2.81174, 80.974 front fs empty border lc rgb '#549f' lw 0.1
set object 3782 polygon from \
  -2.7989, 80.9977 to \
  -0.03, 80.9977 to \
  -0.03, 43.1365 to \
  -2.7989, 43.1365 to \
  -2.7989, 80.9977 front fs empty border lc rgb '#549f' lw 0.1
set object 3783 polygon from \
  -2.7851, 81.0214 to \
  -0.03, 81.0214 to \
  -0.03, 43.1502 to \
  -2.7851, 43.1502 to \
  -2.7851, 81.0214 front fs empty border lc rgb '#549f' lw 0.1
set object 3784 polygon from \
  -2.77031, 81.0452 to \
  -0.03, 81.0452 to \
  -0.03, 43.164 to \
  -2.77031, 43.164 to \
  -2.77031, 81.0452 front fs empty border lc rgb '#549f' lw 0.1
set object 3785 polygon from \
  -2.75454, 81.0689 to \
  -0.03, 81.0689 to \
  -0.03, 43.1777 to \
  -2.75454, 43.1777 to \
  -2.75454, 81.0689 front fs empty border lc rgb '#549f' lw 0.1
set object 3786 polygon from \
  -2.7378, 81.0926 to \
  -0.03, 81.0926 to \
  -0.03, 43.1914 to \
  -2.7378, 43.1914 to \
  -2.7378, 81.0926 front fs empty border lc rgb '#549f' lw 0.1
set object 3787 polygon from \
  -2.72008, 81.1164 to \
  -0.03, 81.1164 to \
  -0.03, 43.2052 to \
  -2.72008, 43.2052 to \
  -2.72008, 81.1164 front fs empty border lc rgb '#549f' lw 0.1
set object 3788 polygon from \
  -2.70138, 81.1401 to \
  -0.03, 81.1401 to \
  -0.03, 43.2189 to \
  -2.70138, 43.2189 to \
  -2.70138, 81.1401 front fs empty border lc rgb '#549f' lw 0.1
set object 3789 polygon from \
  -2.68172, 81.1638 to \
  -0.03, 81.1638 to \
  -0.03, 43.2326 to \
  -2.68172, 43.2326 to \
  -2.68172, 81.1638 front fs empty border lc rgb '#549f' lw 0.1
set object 3790 polygon from \
  -2.66109, 81.1876 to \
  -0.03, 81.1876 to \
  -0.03, 43.2464 to \
  -2.66109, 43.2464 to \
  -2.66109, 81.1876 front fs empty border lc rgb '#549f' lw 0.1
set object 3791 polygon from \
  -2.63949, 81.2113 to \
  -0.03, 81.2113 to \
  -0.03, 43.2601 to \
  -2.63949, 43.2601 to \
  -2.63949, 81.2113 front fs empty border lc rgb '#549f' lw 0.1
set object 3792 polygon from \
  -2.61694, 81.235 to \
  -0.03, 81.235 to \
  -0.03, 43.2738 to \
  -2.61694, 43.2738 to \
  -2.61694, 81.235 front fs empty border lc rgb '#549f' lw 0.1
set object 3793 polygon from \
  -2.59342, 81.2588 to \
  -0.03, 81.2588 to \
  -0.03, 43.2876 to \
  -2.59342, 43.2876 to \
  -2.59342, 81.2588 front fs empty border lc rgb '#549f' lw 0.1
set object 3794 polygon from \
  -2.56896, 81.2825 to \
  -0.03, 81.2825 to \
  -0.03, 43.3013 to \
  -2.56896, 43.3013 to \
  -2.56896, 81.2825 front fs empty border lc rgb '#549f' lw 0.1
set object 3795 polygon from \
  -2.54355, 81.3063 to \
  -0.03, 81.3063 to \
  -0.03, 43.315 to \
  -2.54355, 43.315 to \
  -2.54355, 81.3063 front fs empty border lc rgb '#549f' lw 0.1
set object 3796 polygon from \
  -2.51721, 81.33 to \
  -0.03, 81.33 to \
  -0.03, 43.3288 to \
  -2.51721, 43.3288 to \
  -2.51721, 81.33 front fs empty border lc rgb '#549f' lw 0.1
set object 3797 polygon from \
  -2.48992, 81.3538 to \
  -0.03, 81.3538 to \
  -0.03, 43.3425 to \
  -2.48992, 43.3425 to \
  -2.48992, 81.3538 front fs empty border lc rgb '#549f' lw 0.1
set object 3798 polygon from \
  -2.46172, 81.3775 to \
  -0.03, 81.3775 to \
  -0.03, 43.3563 to \
  -2.46172, 43.3563 to \
  -2.46172, 81.3775 front fs empty border lc rgb '#549f' lw 0.1
set object 3799 polygon from \
  -2.43259, 81.4013 to \
  -0.03, 81.4013 to \
  -0.03, 43.37 to \
  -2.43259, 43.37 to \
  -2.43259, 81.4013 front fs empty border lc rgb '#549f' lw 0.1
set object 3800 polygon from \
  -2.40256, 81.425 to \
  -0.03, 81.425 to \
  -0.03, 43.3838 to \
  -2.40256, 43.3838 to \
  -2.40256, 81.425 front fs empty border lc rgb '#549f' lw 0.1
set object 3801 polygon from \
  -2.38394, 81.4488 to \
  -0.03, 81.4488 to \
  -0.03, 43.3975 to \
  -2.38394, 43.3975 to \
  -2.38394, 81.4488 front fs empty border lc rgb '#549f' lw 0.1
set object 3802 polygon from \
  -2.37013, 81.4725 to \
  -0.03, 81.4725 to \
  -0.03, 43.4112 to \
  -2.37013, 43.4112 to \
  -2.37013, 81.4725 front fs empty border lc rgb '#549f' lw 0.1
set object 3803 polygon from \
  -2.35501, 81.4963 to \
  -0.03, 81.4963 to \
  -0.03, 43.425 to \
  -2.35501, 43.425 to \
  -2.35501, 81.4963 front fs empty border lc rgb '#549f' lw 0.1
set object 3804 polygon from \
  -2.33859, 81.52 to \
  -0.03, 81.52 to \
  -0.03, 43.4387 to \
  -2.33859, 43.4387 to \
  -2.33859, 81.52 front fs empty border lc rgb '#549f' lw 0.1
set object 3805 polygon from \
  -2.32089, 81.5438 to \
  -0.03, 81.5438 to \
  -0.03, 43.4525 to \
  -2.32089, 43.4525 to \
  -2.32089, 81.5438 front fs empty border lc rgb '#549f' lw 0.1
set object 3806 polygon from \
  -2.30192, 81.5675 to \
  -0.03, 81.5675 to \
  -0.03, 43.4663 to \
  -2.30192, 43.4663 to \
  -2.30192, 81.5675 front fs empty border lc rgb '#549f' lw 0.1
set object 3807 polygon from \
  -2.28167, 81.5913 to \
  -0.03, 81.5913 to \
  -0.03, 43.48 to \
  -2.28167, 43.48 to \
  -2.28167, 81.5913 front fs empty border lc rgb '#549f' lw 0.1
set object 3808 polygon from \
  -2.26018, 81.615 to \
  -0.03, 81.615 to \
  -0.03, 43.4938 to \
  -2.26018, 43.4938 to \
  -2.26018, 81.615 front fs empty border lc rgb '#549f' lw 0.1
set object 3809 polygon from \
  -2.23745, 81.6388 to \
  -0.03, 81.6388 to \
  -0.03, 43.5075 to \
  -2.23745, 43.5075 to \
  -2.23745, 81.6388 front fs empty border lc rgb '#549f' lw 0.1
set object 3810 polygon from \
  -2.2135, 81.6626 to \
  -0.03, 81.6626 to \
  -0.03, 43.5213 to \
  -2.2135, 43.5213 to \
  -2.2135, 81.6626 front fs empty border lc rgb '#549f' lw 0.1
set object 3811 polygon from \
  -2.18833, 81.6863 to \
  -0.03, 81.6863 to \
  -0.03, 43.535 to \
  -2.18833, 43.535 to \
  -2.18833, 81.6863 front fs empty border lc rgb '#549f' lw 0.1
set object 3812 polygon from \
  -2.16198, 81.7101 to \
  -0.03, 81.7101 to \
  -0.03, 43.5488 to \
  -2.16198, 43.5488 to \
  -2.16198, 81.7101 front fs empty border lc rgb '#549f' lw 0.1
set object 3813 polygon from \
  -2.13457, 81.7339 to \
  -0.03, 81.7339 to \
  -0.03, 43.5626 to \
  -2.13457, 43.5626 to \
  -2.13457, 81.7339 front fs empty border lc rgb '#549f' lw 0.1
set object 3814 polygon from \
  -2.10607, 81.7576 to \
  -0.03, 81.7576 to \
  -0.03, 43.5763 to \
  -2.10607, 43.5763 to \
  -2.10607, 81.7576 front fs empty border lc rgb '#549f' lw 0.1
set object 3815 polygon from \
  -2.07642, 81.7814 to \
  -0.03, 81.7814 to \
  -0.03, 43.5901 to \
  -2.07642, 43.5901 to \
  -2.07642, 81.7814 front fs empty border lc rgb '#549f' lw 0.1
set object 3816 polygon from \
  -2.04563, 81.8052 to \
  -0.03, 81.8052 to \
  -0.03, 43.6039 to \
  -2.04563, 43.6039 to \
  -2.04563, 81.8052 front fs empty border lc rgb '#549f' lw 0.1
set object 3817 polygon from \
  -2.01372, 81.8289 to \
  -0.03, 81.8289 to \
  -0.03, 43.6176 to \
  -2.01372, 43.6176 to \
  -2.01372, 81.8289 front fs empty border lc rgb '#549f' lw 0.1
set object 3818 polygon from \
  -1.98072, 81.8527 to \
  -0.03, 81.8527 to \
  -0.03, 43.6314 to \
  -1.98072, 43.6314 to \
  -1.98072, 81.8527 front fs empty border lc rgb '#549f' lw 0.1
set object 3819 polygon from \
  -1.94664, 81.8765 to \
  -0.03, 81.8765 to \
  -0.03, 43.6452 to \
  -1.94664, 43.6452 to \
  -1.94664, 81.8765 front fs empty border lc rgb '#549f' lw 0.1
set object 3820 polygon from \
  -1.91151, 81.9003 to \
  -0.03, 81.9003 to \
  -0.03, 43.6589 to \
  -1.91151, 43.6589 to \
  -1.91151, 81.9003 front fs empty border lc rgb '#549f' lw 0.1
set object 3821 polygon from \
  -1.87534, 81.924 to \
  -0.03, 81.924 to \
  -0.03, 43.6727 to \
  -1.87534, 43.6727 to \
  -1.87534, 81.924 front fs empty border lc rgb '#549f' lw 0.1
set object 3822 polygon from \
  -1.83817, 81.9478 to \
  -0.03, 81.9478 to \
  -0.03, 43.6865 to \
  -1.83817, 43.6865 to \
  -1.83817, 81.9478 front fs empty border lc rgb '#549f' lw 0.1
set object 3823 polygon from \
  -1.80002, 81.9716 to \
  -0.03, 81.9716 to \
  -0.03, 43.7002 to \
  -1.80002, 43.7002 to \
  -1.80002, 81.9716 front fs empty border lc rgb '#549f' lw 0.1
set object 3824 polygon from \
  -1.7609, 81.9954 to \
  -0.03, 81.9954 to \
  -0.03, 43.714 to \
  -1.7609, 43.714 to \
  -1.7609, 81.9954 front fs empty border lc rgb '#549f' lw 0.1
set object 3825 polygon from \
  -1.72085, 82.0191 to \
  -0.03, 82.0191 to \
  -0.03, 43.7278 to \
  -1.72085, 43.7278 to \
  -1.72085, 82.0191 front fs empty border lc rgb '#549f' lw 0.1
set object 3826 polygon from \
  -1.67989, 82.0429 to \
  -0.03, 82.0429 to \
  -0.03, 43.7416 to \
  -1.67989, 43.7416 to \
  -1.67989, 82.0429 front fs empty border lc rgb '#549f' lw 0.1
set object 3827 polygon from \
  -1.63927, 82.0667 to \
  -0.03, 82.0667 to \
  -0.03, 43.7554 to \
  -1.63927, 43.7554 to \
  -1.63927, 82.0667 front fs empty border lc rgb '#549f' lw 0.1
set object 3828 polygon from \
  -1.59851, 82.0905 to \
  -0.03, 82.0905 to \
  -0.03, 43.7691 to \
  -1.59851, 43.7691 to \
  -1.59851, 82.0905 front fs empty border lc rgb '#549f' lw 0.1
set object 3829 polygon from \
  -1.5569, 82.1143 to \
  -0.03, 82.1143 to \
  -0.03, 43.7829 to \
  -1.5569, 43.7829 to \
  -1.5569, 82.1143 front fs empty border lc rgb '#549f' lw 0.1
set object 3830 polygon from \
  -1.51449, 82.1381 to \
  -0.03, 82.1381 to \
  -0.03, 43.7967 to \
  -1.51449, 43.7967 to \
  -1.51449, 82.1381 front fs empty border lc rgb '#549f' lw 0.1
set object 3831 polygon from \
  -1.47129, 82.1619 to \
  -0.03, 82.1619 to \
  -0.03, 43.8105 to \
  -1.47129, 43.8105 to \
  -1.47129, 82.1619 front fs empty border lc rgb '#549f' lw 0.1
set object 3832 polygon from \
  -1.42734, 82.1856 to \
  -0.03, 82.1856 to \
  -0.03, 43.8243 to \
  -1.42734, 43.8243 to \
  -1.42734, 82.1856 front fs empty border lc rgb '#549f' lw 0.1
set object 3833 polygon from \
  -1.38267, 82.2094 to \
  -0.03, 82.2094 to \
  -0.03, 43.8381 to \
  -1.38267, 43.8381 to \
  -1.38267, 82.2094 front fs empty border lc rgb '#549f' lw 0.1
set object 3834 polygon from \
  -1.3373, 82.2332 to \
  -0.03, 82.2332 to \
  -0.03, 43.8518 to \
  -1.3373, 43.8518 to \
  -1.3373, 82.2332 front fs empty border lc rgb '#549f' lw 0.1
set object 3835 polygon from \
  -1.29127, 82.257 to \
  -0.03, 82.257 to \
  -0.03, 43.8656 to \
  -1.29127, 43.8656 to \
  -1.29127, 82.257 front fs empty border lc rgb '#549f' lw 0.1
set object 3836 polygon from \
  -1.2446, 82.2808 to \
  -0.03, 82.2808 to \
  -0.03, 43.8794 to \
  -1.2446, 43.8794 to \
  -1.2446, 82.2808 front fs empty border lc rgb '#549f' lw 0.1
set object 3837 polygon from \
  -1.19733, 82.3046 to \
  -0.03, 82.3046 to \
  -0.03, 43.8932 to \
  -1.19733, 43.8932 to \
  -1.19733, 82.3046 front fs empty border lc rgb '#549f' lw 0.1
set object 3838 polygon from \
  -1.14948, 82.3284 to \
  -0.03, 82.3284 to \
  -0.03, 43.907 to \
  -1.14948, 43.907 to \
  -1.14948, 82.3284 front fs empty border lc rgb '#549f' lw 0.1
set object 3839 polygon from \
  -1.14647, 82.3522 to \
  -0.03, 82.3522 to \
  -0.03, 43.9208 to \
  -1.14647, 43.9208 to \
  -1.14647, 82.3522 front fs empty border lc rgb '#549f' lw 0.1
set object 3840 polygon from \
  -1.15057, 82.376 to \
  -0.03, 82.376 to \
  -0.03, 43.9346 to \
  -1.15057, 43.9346 to \
  -1.15057, 82.376 front fs empty border lc rgb '#549f' lw 0.1
set object 3841 polygon from \
  -1.15427, 82.3998 to \
  -0.03, 82.3998 to \
  -0.03, 43.9484 to \
  -1.15427, 43.9484 to \
  -1.15427, 82.3998 front fs empty border lc rgb '#549f' lw 0.1
set object 3842 polygon from \
  -1.15766, 82.4236 to \
  -0.03, 82.4236 to \
  -0.03, 43.9622 to \
  -1.15766, 43.9622 to \
  -1.15766, 82.4236 front fs empty border lc rgb '#549f' lw 0.1
set object 3843 polygon from \
  -1.1608, 82.4474 to \
  -0.03, 82.4474 to \
  -0.03, 43.976 to \
  -1.1608, 43.976 to \
  -1.1608, 82.4474 front fs empty border lc rgb '#549f' lw 0.1
set object 3844 polygon from \
  -1.16359, 82.4712 to \
  -0.03, 82.4712 to \
  -0.03, 43.9898 to \
  -1.16359, 43.9898 to \
  -1.16359, 82.4712 front fs empty border lc rgb '#549f' lw 0.1
set object 3845 polygon from \
  -1.16604, 82.495 to \
  -0.03, 82.495 to \
  -0.03, 44.0036 to \
  -1.16604, 44.0036 to \
  -1.16604, 82.495 front fs empty border lc rgb '#549f' lw 0.1
set object 3846 polygon from \
  -1.16883, 82.5188 to \
  -0.03, 82.5188 to \
  -0.03, 44.0174 to \
  -1.16883, 44.0174 to \
  -1.16883, 82.5188 front fs empty border lc rgb '#549f' lw 0.1
set object 3847 polygon from \
  -1.22072, 82.5426 to \
  -0.03, 82.5426 to \
  -0.03, 44.0312 to \
  -1.22072, 44.0312 to \
  -1.22072, 82.5426 front fs empty border lc rgb '#549f' lw 0.1
set object 3848 polygon from \
  -1.27234, 82.5664 to \
  -0.03, 82.5664 to \
  -0.03, 44.045 to \
  -1.27234, 44.045 to \
  -1.27234, 82.5664 front fs empty border lc rgb '#549f' lw 0.1
set object 3849 polygon from \
  -1.32364, 82.5903 to \
  -0.03, 82.5903 to \
  -0.03, 44.0588 to \
  -1.32364, 44.0588 to \
  -1.32364, 82.5903 front fs empty border lc rgb '#549f' lw 0.1
set object 3850 polygon from \
  -1.37461, 82.6141 to \
  -0.03, 82.6141 to \
  -0.03, 44.0726 to \
  -1.37461, 44.0726 to \
  -1.37461, 82.6141 front fs empty border lc rgb '#549f' lw 0.1
set object 3851 polygon from \
  -1.42522, 82.6379 to \
  -0.03, 82.6379 to \
  -0.03, 44.0864 to \
  -1.42522, 44.0864 to \
  -1.42522, 82.6379 front fs empty border lc rgb '#549f' lw 0.1
set object 3852 polygon from \
  -1.47544, 82.6617 to \
  -0.03, 82.6617 to \
  -0.03, 44.1002 to \
  -1.47544, 44.1002 to \
  -1.47544, 82.6617 front fs empty border lc rgb '#549f' lw 0.1
set object 3853 polygon from \
  -1.52527, 82.6855 to \
  -0.03, 82.6855 to \
  -0.03, 44.1141 to \
  -1.52527, 44.1141 to \
  -1.52527, 82.6855 front fs empty border lc rgb '#549f' lw 0.1
set object 3854 polygon from \
  -1.57467, 82.7093 to \
  -0.03, 82.7093 to \
  -0.03, 44.1279 to \
  -1.57467, 44.1279 to \
  -1.57467, 82.7093 front fs empty border lc rgb '#549f' lw 0.1
set object 3855 polygon from \
  -1.62363, 82.7331 to \
  -0.03, 82.7331 to \
  -0.03, 44.1417 to \
  -1.62363, 44.1417 to \
  -1.62363, 82.7331 front fs empty border lc rgb '#549f' lw 0.1
set object 3856 polygon from \
  -1.67212, 82.757 to \
  -0.03, 82.757 to \
  -0.03, 44.1555 to \
  -1.67212, 44.1555 to \
  -1.67212, 82.757 front fs empty border lc rgb '#549f' lw 0.1
set object 3857 polygon from \
  -1.72013, 82.7808 to \
  -0.03, 82.7808 to \
  -0.03, 44.1693 to \
  -1.72013, 44.1693 to \
  -1.72013, 82.7808 front fs empty border lc rgb '#549f' lw 0.1
set object 3858 polygon from \
  -1.76764, 82.8046 to \
  -0.03, 82.8046 to \
  -0.03, 44.1831 to \
  -1.76764, 44.1831 to \
  -1.76764, 82.8046 front fs empty border lc rgb '#549f' lw 0.1
set object 3859 polygon from \
  -1.81462, 82.8284 to \
  -0.03, 82.8284 to \
  -0.03, 44.197 to \
  -1.81462, 44.197 to \
  -1.81462, 82.8284 front fs empty border lc rgb '#549f' lw 0.1
set object 3860 polygon from \
  -1.86106, 82.8523 to \
  -0.03, 82.8523 to \
  -0.03, 44.2108 to \
  -1.86106, 44.2108 to \
  -1.86106, 82.8523 front fs empty border lc rgb '#549f' lw 0.1
set object 3861 polygon from \
  -1.90694, 82.8761 to \
  -0.03, 82.8761 to \
  -0.03, 44.2246 to \
  -1.90694, 44.2246 to \
  -1.90694, 82.8761 front fs empty border lc rgb '#549f' lw 0.1
set object 3862 polygon from \
  -1.95223, 82.8999 to \
  -0.03, 82.8999 to \
  -0.03, 44.2384 to \
  -1.95223, 44.2384 to \
  -1.95223, 82.8999 front fs empty border lc rgb '#549f' lw 0.1
set object 3863 polygon from \
  -1.99692, 82.9237 to \
  -0.03, 82.9237 to \
  -0.03, 44.2522 to \
  -1.99692, 44.2522 to \
  -1.99692, 82.9237 front fs empty border lc rgb '#549f' lw 0.1
set object 3864 polygon from \
  -2.04099, 82.9476 to \
  -0.03, 82.9476 to \
  -0.03, 44.2661 to \
  -2.04099, 44.2661 to \
  -2.04099, 82.9476 front fs empty border lc rgb '#549f' lw 0.1
set object 3865 polygon from \
  -2.08442, 82.9714 to \
  -0.03, 82.9714 to \
  -0.03, 44.2799 to \
  -2.08442, 44.2799 to \
  -2.08442, 82.9714 front fs empty border lc rgb '#549f' lw 0.1
set object 3866 polygon from \
  -2.12719, 82.9952 to \
  -0.03, 82.9952 to \
  -0.03, 44.2937 to \
  -2.12719, 44.2937 to \
  -2.12719, 82.9952 front fs empty border lc rgb '#549f' lw 0.1
set object 3867 polygon from \
  -2.16928, 83.0191 to \
  -0.03, 83.0191 to \
  -0.03, 44.3076 to \
  -2.16928, 44.3076 to \
  -2.16928, 83.0191 front fs empty border lc rgb '#549f' lw 0.1
set object 3868 polygon from \
  -2.21068, 83.0429 to \
  -0.03, 83.0429 to \
  -0.03, 44.3214 to \
  -2.21068, 44.3214 to \
  -2.21068, 83.0429 front fs empty border lc rgb '#549f' lw 0.1
set object 3869 polygon from \
  -2.25137, 83.0667 to \
  -0.03, 83.0667 to \
  -0.03, 44.3352 to \
  -2.25137, 44.3352 to \
  -2.25137, 83.0667 front fs empty border lc rgb '#549f' lw 0.1
set object 3870 polygon from \
  -2.29133, 83.0906 to \
  -0.03, 83.0906 to \
  -0.03, 44.3491 to \
  -2.29133, 44.3491 to \
  -2.29133, 83.0906 front fs empty border lc rgb '#549f' lw 0.1
set object 3871 polygon from \
  -2.33055, 83.1144 to \
  -0.03, 83.1144 to \
  -0.03, 44.3629 to \
  -2.33055, 44.3629 to \
  -2.33055, 83.1144 front fs empty border lc rgb '#549f' lw 0.1
set object 3872 polygon from \
  -2.369, 83.1382 to \
  -0.03, 83.1382 to \
  -0.03, 44.3767 to \
  -2.369, 44.3767 to \
  -2.369, 83.1382 front fs empty border lc rgb '#549f' lw 0.1
set object 3873 polygon from \
  -2.40667, 83.1621 to \
  -0.03, 83.1621 to \
  -0.03, 44.3906 to \
  -2.40667, 44.3906 to \
  -2.40667, 83.1621 front fs empty border lc rgb '#549f' lw 0.1
set object 3874 polygon from \
  -2.44355, 83.1859 to \
  -0.03, 83.1859 to \
  -0.03, 44.4044 to \
  -2.44355, 44.4044 to \
  -2.44355, 83.1859 front fs empty border lc rgb '#549f' lw 0.1
set object 3875 polygon from \
  -2.47963, 83.2098 to \
  -0.03, 83.2098 to \
  -0.03, 44.4182 to \
  -2.47963, 44.4182 to \
  -2.47963, 83.2098 front fs empty border lc rgb '#549f' lw 0.1
set object 3876 polygon from \
  -2.51487, 83.2336 to \
  -0.03, 83.2336 to \
  -0.03, 44.4321 to \
  -2.51487, 44.4321 to \
  -2.51487, 83.2336 front fs empty border lc rgb '#549f' lw 0.1
set object 3877 polygon from \
  -2.54928, 83.2575 to \
  -0.03, 83.2575 to \
  -0.03, 44.4459 to \
  -2.54928, 44.4459 to \
  -2.54928, 83.2575 front fs empty border lc rgb '#549f' lw 0.1
set object 3878 polygon from \
  -2.58284, 83.2813 to \
  -0.03, 83.2813 to \
  -0.03, 44.4598 to \
  -2.58284, 44.4598 to \
  -2.58284, 83.2813 front fs empty border lc rgb '#549f' lw 0.1
set object 3879 polygon from \
  -2.61552, 83.3052 to \
  -0.03, 83.3052 to \
  -0.03, 44.4736 to \
  -2.61552, 44.4736 to \
  -2.61552, 83.3052 front fs empty border lc rgb '#549f' lw 0.1
set object 3880 polygon from \
  -2.64733, 83.329 to \
  -0.03, 83.329 to \
  -0.03, 44.4875 to \
  -2.64733, 44.4875 to \
  -2.64733, 83.329 front fs empty border lc rgb '#549f' lw 0.1
set object 3881 polygon from \
  -2.67824, 83.3529 to \
  -0.03, 83.3529 to \
  -0.03, 44.5013 to \
  -2.67824, 44.5013 to \
  -2.67824, 83.3529 front fs empty border lc rgb '#549f' lw 0.1
set object 3882 polygon from \
  -2.70825, 83.3767 to \
  -0.03, 83.3767 to \
  -0.03, 44.5151 to \
  -2.70825, 44.5151 to \
  -2.70825, 83.3767 front fs empty border lc rgb '#549f' lw 0.1
set object 3883 polygon from \
  -2.73733, 83.4006 to \
  -0.03, 83.4006 to \
  -0.03, 44.529 to \
  -2.73733, 44.529 to \
  -2.73733, 83.4006 front fs empty border lc rgb '#549f' lw 0.1
set object 3884 polygon from \
  -2.76549, 83.4244 to \
  -0.03, 83.4244 to \
  -0.03, 44.5428 to \
  -2.76549, 44.5428 to \
  -2.76549, 83.4244 front fs empty border lc rgb '#549f' lw 0.1
set object 3885 polygon from \
  -2.7927, 83.4483 to \
  -0.03, 83.4483 to \
  -0.03, 44.5567 to \
  -2.7927, 44.5567 to \
  -2.7927, 83.4483 front fs empty border lc rgb '#549f' lw 0.1
set object 3886 polygon from \
  -2.81896, 83.4721 to \
  -0.03, 83.4721 to \
  -0.03, 44.5706 to \
  -2.81896, 44.5706 to \
  -2.81896, 83.4721 front fs empty border lc rgb '#549f' lw 0.1
set object 3887 polygon from \
  -2.84426, 83.496 to \
  -0.03, 83.496 to \
  -0.03, 44.5844 to \
  -2.84426, 44.5844 to \
  -2.84426, 83.496 front fs empty border lc rgb '#549f' lw 0.1
set object 3888 polygon from \
  -2.86858, 83.5198 to \
  -0.03, 83.5198 to \
  -0.03, 44.5983 to \
  -2.86858, 44.5983 to \
  -2.86858, 83.5198 front fs empty border lc rgb '#549f' lw 0.1
set object 3889 polygon from \
  -2.89192, 83.5437 to \
  -0.03, 83.5437 to \
  -0.03, 44.6121 to \
  -2.89192, 44.6121 to \
  -2.89192, 83.5437 front fs empty border lc rgb '#549f' lw 0.1
set object 3890 polygon from \
  -2.91426, 83.5676 to \
  -0.03, 83.5676 to \
  -0.03, 44.626 to \
  -2.91426, 44.626 to \
  -2.91426, 83.5676 front fs empty border lc rgb '#549f' lw 0.1
set object 3891 polygon from \
  -2.9356, 83.5914 to \
  -0.03, 83.5914 to \
  -0.03, 44.6398 to \
  -2.9356, 44.6398 to \
  -2.9356, 83.5914 front fs empty border lc rgb '#549f' lw 0.1
set object 3892 polygon from \
  -2.95594, 83.6153 to \
  -0.03, 83.6153 to \
  -0.03, 44.6537 to \
  -2.95594, 44.6537 to \
  -2.95594, 83.6153 front fs empty border lc rgb '#549f' lw 0.1
set object 3893 polygon from \
  -2.97526, 83.6392 to \
  -0.03, 83.6392 to \
  -0.03, 44.6676 to \
  -2.97526, 44.6676 to \
  -2.97526, 83.6392 front fs empty border lc rgb '#549f' lw 0.1
set object 3894 polygon from \
  -2.99355, 83.663 to \
  -0.03, 83.663 to \
  -0.03, 44.6814 to \
  -2.99355, 44.6814 to \
  -2.99355, 83.663 front fs empty border lc rgb '#549f' lw 0.1
set object 3895 polygon from \
  -3.01081, 83.6869 to \
  -0.03, 83.6869 to \
  -0.03, 44.6953 to \
  -3.01081, 44.6953 to \
  -3.01081, 83.6869 front fs empty border lc rgb '#549f' lw 0.1
set object 3896 polygon from \
  -3.02703, 83.7108 to \
  -0.03, 83.7108 to \
  -0.03, 44.7092 to \
  -3.02703, 44.7092 to \
  -3.02703, 83.7108 front fs empty border lc rgb '#549f' lw 0.1
set object 3897 polygon from \
  -3.04221, 83.7346 to \
  -0.03, 83.7346 to \
  -0.03, 44.723 to \
  -3.04221, 44.723 to \
  -3.04221, 83.7346 front fs empty border lc rgb '#549f' lw 0.1
set object 3898 polygon from \
  -3.05634, 83.7585 to \
  -0.03, 83.7585 to \
  -0.03, 44.7369 to \
  -3.05634, 44.7369 to \
  -3.05634, 83.7585 front fs empty border lc rgb '#549f' lw 0.1
set object 3899 polygon from \
  -3.06942, 83.7824 to \
  -0.03, 83.7824 to \
  -0.03, 44.7508 to \
  -3.06942, 44.7508 to \
  -3.06942, 83.7824 front fs empty border lc rgb '#549f' lw 0.1
set object 3900 polygon from \
  -3.08144, 83.8063 to \
  -0.03, 83.8063 to \
  -0.03, 44.7646 to \
  -3.08144, 44.7646 to \
  -3.08144, 83.8063 front fs empty border lc rgb '#549f' lw 0.1
set object 3901 polygon from \
  -3.0924, 83.8301 to \
  -0.03, 83.8301 to \
  -0.03, 44.7785 to \
  -3.0924, 44.7785 to \
  -3.0924, 83.8301 front fs empty border lc rgb '#549f' lw 0.1
set object 3902 polygon from \
  -3.10229, 83.854 to \
  -0.03, 83.854 to \
  -0.03, 44.7924 to \
  -3.10229, 44.7924 to \
  -3.10229, 83.854 front fs empty border lc rgb '#549f' lw 0.1
set object 3903 polygon from \
  -3.11112, 83.8779 to \
  -0.03, 83.8779 to \
  -0.03, 44.8062 to \
  -3.11112, 44.8062 to \
  -3.11112, 83.8779 front fs empty border lc rgb '#549f' lw 0.1
set object 3904 polygon from \
  -3.11887, 83.9018 to \
  -0.03, 83.9018 to \
  -0.03, 44.8201 to \
  -3.11887, 44.8201 to \
  -3.11887, 83.9018 front fs empty border lc rgb '#549f' lw 0.1
set object 3905 polygon from \
  -3.12555, 83.9256 to \
  -0.03, 83.9256 to \
  -0.03, 44.834 to \
  -3.12555, 44.834 to \
  -3.12555, 83.9256 front fs empty border lc rgb '#549f' lw 0.1
set object 3906 polygon from \
  -3.13116, 83.9495 to \
  -0.03, 83.9495 to \
  -0.03, 44.8479 to \
  -3.13116, 44.8479 to \
  -3.13116, 83.9495 front fs empty border lc rgb '#549f' lw 0.1
set object 3907 polygon from \
  -3.1357, 83.9734 to \
  -0.03, 83.9734 to \
  -0.03, 44.8618 to \
  -3.1357, 44.8618 to \
  -3.1357, 83.9734 front fs empty border lc rgb '#549f' lw 0.1
set object 3908 polygon from \
  -3.13916, 83.9973 to \
  -0.03, 83.9973 to \
  -0.03, 44.8756 to \
  -3.13916, 44.8756 to \
  -3.13916, 83.9973 front fs empty border lc rgb '#549f' lw 0.1
set object 3909 polygon from \
  -3.14155, 84.0212 to \
  -0.03, 84.0212 to \
  -0.03, 44.8895 to \
  -3.14155, 44.8895 to \
  -3.14155, 84.0212 front fs empty border lc rgb '#549f' lw 0.1
set object 3910 polygon from \
  -3.14286, 84.0451 to \
  -0.03, 84.0451 to \
  -0.03, 44.9034 to \
  -3.14286, 44.9034 to \
  -3.14286, 84.0451 front fs empty border lc rgb '#549f' lw 0.1
set object 3911 polygon from \
  -3.14311, 84.069 to \
  -0.03, 84.069 to \
  -0.03, 44.9173 to \
  -3.14311, 44.9173 to \
  -3.14311, 84.069 front fs empty border lc rgb '#549f' lw 0.1
set object 3912 polygon from \
  -3.14311, 84.0928 to \
  -0.03, 84.0928 to \
  -0.03, 44.9312 to \
  -3.14311, 44.9312 to \
  -3.14311, 84.0928 front fs empty border lc rgb '#549f' lw 0.1
set object 3913 polygon from \
  -3.14228, 84.1167 to \
  -0.03, 84.1167 to \
  -0.03, 44.9451 to \
  -3.14228, 44.9451 to \
  -3.14228, 84.1167 front fs empty border lc rgb '#549f' lw 0.1
set object 3914 polygon from \
  -3.14038, 84.1406 to \
  -0.03, 84.1406 to \
  -0.03, 44.9589 to \
  -3.14038, 44.9589 to \
  -3.14038, 84.1406 front fs empty border lc rgb '#549f' lw 0.1
set object 3915 polygon from \
  -3.13742, 84.1645 to \
  -0.03, 84.1645 to \
  -0.03, 44.9728 to \
  -3.13742, 44.9728 to \
  -3.13742, 84.1645 front fs empty border lc rgb '#549f' lw 0.1
set object 3916 polygon from \
  -3.1334, 84.1884 to \
  -0.03, 84.1884 to \
  -0.03, 44.9867 to \
  -3.1334, 44.9867 to \
  -3.1334, 84.1884 front fs empty border lc rgb '#549f' lw 0.1
set object 3917 polygon from \
  -3.12832, 84.2123 to \
  -0.03, 84.2123 to \
  -0.03, 45.0006 to \
  -3.12832, 45.0006 to \
  -3.12832, 84.2123 front fs empty border lc rgb '#549f' lw 0.1
set object 3918 polygon from \
  -3.12218, 84.2362 to \
  -0.03, 84.2362 to \
  -0.03, 45.0145 to \
  -3.12218, 45.0145 to \
  -3.12218, 84.2362 front fs empty border lc rgb '#549f' lw 0.1
set object 3919 polygon from \
  -3.115, 84.2601 to \
  -0.03, 84.2601 to \
  -0.03, 45.0284 to \
  -3.115, 45.0284 to \
  -3.115, 84.2601 front fs empty border lc rgb '#549f' lw 0.1
set object 3920 polygon from \
  -3.10813, 84.284 to \
  -0.03, 84.284 to \
  -0.03, 45.0423 to \
  -3.10813, 45.0423 to \
  -3.10813, 84.284 front fs empty border lc rgb '#549f' lw 0.1
set object 3921 polygon from \
  -3.10813, 84.3079 to \
  -0.03, 84.3079 to \
  -0.03, 45.0562 to \
  -3.10813, 45.0562 to \
  -3.10813, 84.3079 front fs empty border lc rgb '#549f' lw 0.1
set object 3922 polygon from \
  -3.10807, 84.3318 to \
  -0.03, 84.3318 to \
  -0.03, 45.0701 to \
  -3.10807, 45.0701 to \
  -3.10807, 84.3318 front fs empty border lc rgb '#549f' lw 0.1
set object 3923 polygon from \
  -3.10701, 84.3557 to \
  -0.03, 84.3557 to \
  -0.03, 45.084 to \
  -3.10701, 45.084 to \
  -3.10701, 84.3557 front fs empty border lc rgb '#549f' lw 0.1
set object 3924 polygon from \
  -3.10864, 84.3796 to \
  -0.03, 84.3796 to \
  -0.03, 45.0979 to \
  -3.10864, 45.0979 to \
  -3.10864, 84.3796 front fs empty border lc rgb '#549f' lw 0.1
set object 3925 polygon from \
  -3.10921, 84.4035 to \
  -0.03, 84.4035 to \
  -0.03, 45.1118 to \
  -3.10921, 45.1118 to \
  -3.10921, 84.4035 front fs empty border lc rgb '#549f' lw 0.1
set object 3926 polygon from \
  -3.1092, 84.4274 to \
  -0.03, 84.4274 to \
  -0.03, 45.1257 to \
  -3.1092, 45.1257 to \
  -3.1092, 84.4274 front fs empty border lc rgb '#549f' lw 0.1
set object 3927 polygon from \
  -3.10871, 84.4513 to \
  -0.03, 84.4513 to \
  -0.03, 45.1396 to \
  -3.10871, 45.1396 to \
  -3.10871, 84.4513 front fs empty border lc rgb '#549f' lw 0.1
set object 3928 polygon from \
  -3.10716, 84.4752 to \
  -0.03, 84.4752 to \
  -0.03, 45.1535 to \
  -3.10716, 45.1535 to \
  -3.10716, 84.4752 front fs empty border lc rgb '#549f' lw 0.1
set object 3929 polygon from \
  -3.10456, 84.4992 to \
  -0.03, 84.4992 to \
  -0.03, 45.1674 to \
  -3.10456, 45.1674 to \
  -3.10456, 84.4992 front fs empty border lc rgb '#549f' lw 0.1
set object 3930 polygon from \
  -3.10091, 84.5231 to \
  -0.03, 84.5231 to \
  -0.03, 45.1813 to \
  -3.10091, 45.1813 to \
  -3.10091, 84.5231 front fs empty border lc rgb '#549f' lw 0.1
set object 3931 polygon from \
  -3.09621, 84.547 to \
  -0.03, 84.547 to \
  -0.03, 45.1952 to \
  -3.09621, 45.1952 to \
  -3.09621, 84.547 front fs empty border lc rgb '#549f' lw 0.1
set object 3932 polygon from \
  -3.09048, 84.5709 to \
  -0.03, 84.5709 to \
  -0.03, 45.2091 to \
  -3.09048, 45.2091 to \
  -3.09048, 84.5709 front fs empty border lc rgb '#549f' lw 0.1
set object 3933 polygon from \
  -3.0837, 84.5948 to \
  -0.03, 84.5948 to \
  -0.03, 45.2231 to \
  -3.0837, 45.2231 to \
  -3.0837, 84.5948 front fs empty border lc rgb '#549f' lw 0.1
set object 3934 polygon from \
  -3.0759, 84.6187 to \
  -0.03, 84.6187 to \
  -0.03, 45.237 to \
  -3.0759, 45.237 to \
  -3.0759, 84.6187 front fs empty border lc rgb '#549f' lw 0.1
set object 3935 polygon from \
  -3.06707, 84.6426 to \
  -0.03, 84.6426 to \
  -0.03, 45.2509 to \
  -3.06707, 45.2509 to \
  -3.06707, 84.6426 front fs empty border lc rgb '#549f' lw 0.1
set object 3936 polygon from \
  -3.05723, 84.6666 to \
  -0.03, 84.6666 to \
  -0.03, 45.2648 to \
  -3.05723, 45.2648 to \
  -3.05723, 84.6666 front fs empty border lc rgb '#549f' lw 0.1
set object 3937 polygon from \
  -3.04637, 84.6905 to \
  -0.03, 84.6905 to \
  -0.03, 45.2787 to \
  -3.04637, 45.2787 to \
  -3.04637, 84.6905 front fs empty border lc rgb '#549f' lw 0.1
set object 3938 polygon from \
  -3.03451, 84.7144 to \
  -0.03, 84.7144 to \
  -0.03, 45.2926 to \
  -3.03451, 45.2926 to \
  -3.03451, 84.7144 front fs empty border lc rgb '#549f' lw 0.1
set object 3939 polygon from \
  -3.02166, 84.7383 to \
  -0.03, 84.7383 to \
  -0.03, 45.3066 to \
  -3.02166, 45.3066 to \
  -3.02166, 84.7383 front fs empty border lc rgb '#549f' lw 0.1
set object 3940 polygon from \
  -3.00782, 84.7623 to \
  -0.03, 84.7623 to \
  -0.03, 45.3205 to \
  -3.00782, 45.3205 to \
  -3.00782, 84.7623 front fs empty border lc rgb '#549f' lw 0.1
set object 3941 polygon from \
  -2.993, 84.7862 to \
  -0.03, 84.7862 to \
  -0.03, 45.3344 to \
  -2.993, 45.3344 to \
  -2.993, 84.7862 front fs empty border lc rgb '#549f' lw 0.1
set object 3942 polygon from \
  -2.97721, 84.8101 to \
  -0.03, 84.8101 to \
  -0.03, 45.3483 to \
  -2.97721, 45.3483 to \
  -2.97721, 84.8101 front fs empty border lc rgb '#549f' lw 0.1
set object 3943 polygon from \
  -2.96047, 84.834 to \
  -0.03, 84.834 to \
  -0.03, 45.3622 to \
  -2.96047, 45.3622 to \
  -2.96047, 84.834 front fs empty border lc rgb '#549f' lw 0.1
set object 3944 polygon from \
  -2.94278, 84.858 to \
  -0.03, 84.858 to \
  -0.03, 45.3762 to \
  -2.94278, 45.3762 to \
  -2.94278, 84.858 front fs empty border lc rgb '#549f' lw 0.1
set object 3945 polygon from \
  -2.92414, 84.8819 to \
  -0.03, 84.8819 to \
  -0.03, 45.3901 to \
  -2.92414, 45.3901 to \
  -2.92414, 84.8819 front fs empty border lc rgb '#549f' lw 0.1
set object 3946 polygon from \
  -2.90458, 84.9058 to \
  -0.03, 84.9058 to \
  -0.03, 45.404 to \
  -2.90458, 45.404 to \
  -2.90458, 84.9058 front fs empty border lc rgb '#549f' lw 0.1
set object 3947 polygon from \
  -2.88411, 84.9298 to \
  -0.03, 84.9298 to \
  -0.03, 45.418 to \
  -2.88411, 45.418 to \
  -2.88411, 84.9298 front fs empty border lc rgb '#549f' lw 0.1
set object 3948 polygon from \
  -2.86273, 84.9537 to \
  -0.03, 84.9537 to \
  -0.03, 45.4319 to \
  -2.86273, 45.4319 to \
  -2.86273, 84.9537 front fs empty border lc rgb '#549f' lw 0.1
set object 3949 polygon from \
  -2.84046, 84.9776 to \
  -0.03, 84.9776 to \
  -0.03, 45.4458 to \
  -2.84046, 45.4458 to \
  -2.84046, 84.9776 front fs empty border lc rgb '#549f' lw 0.1
set object 3950 polygon from \
  -2.81731, 85.0016 to \
  -0.03, 85.0016 to \
  -0.03, 45.4598 to \
  -2.81731, 45.4598 to \
  -2.81731, 85.0016 front fs empty border lc rgb '#549f' lw 0.1
set object 3951 polygon from \
  -2.7933, 85.0255 to \
  -0.03, 85.0255 to \
  -0.03, 45.4737 to \
  -2.7933, 45.4737 to \
  -2.7933, 85.0255 front fs empty border lc rgb '#549f' lw 0.1
set object 3952 polygon from \
  -2.76843, 85.0494 to \
  -0.03, 85.0494 to \
  -0.03, 45.4876 to \
  -2.76843, 45.4876 to \
  -2.76843, 85.0494 front fs empty border lc rgb '#549f' lw 0.1
set object 3953 polygon from \
  -2.74272, 85.0734 to \
  -0.03, 85.0734 to \
  -0.03, 45.5016 to \
  -2.74272, 45.5016 to \
  -2.74272, 85.0734 front fs empty border lc rgb '#549f' lw 0.1
set object 3954 polygon from \
  -2.71619, 85.0973 to \
  -0.03, 85.0973 to \
  -0.03, 45.5155 to \
  -2.71619, 45.5155 to \
  -2.71619, 85.0973 front fs empty border lc rgb '#549f' lw 0.1
set object 3955 polygon from \
  -2.68885, 85.1213 to \
  -0.03, 85.1213 to \
  -0.03, 45.5294 to \
  -2.68885, 45.5294 to \
  -2.68885, 85.1213 front fs empty border lc rgb '#549f' lw 0.1
set object 3956 polygon from \
  -2.66071, 85.1452 to \
  -0.03, 85.1452 to \
  -0.03, 45.5434 to \
  -2.66071, 45.5434 to \
  -2.66071, 85.1452 front fs empty border lc rgb '#549f' lw 0.1
set object 3957 polygon from \
  -2.63179, 85.1692 to \
  -0.03, 85.1692 to \
  -0.03, 45.5573 to \
  -2.63179, 45.5573 to \
  -2.63179, 85.1692 front fs empty border lc rgb '#549f' lw 0.1
set object 3958 polygon from \
  -2.6021, 85.1931 to \
  -0.03, 85.1931 to \
  -0.03, 45.5713 to \
  -2.6021, 45.5713 to \
  -2.6021, 85.1931 front fs empty border lc rgb '#549f' lw 0.1
set object 3959 polygon from \
  -2.57167, 85.2171 to \
  -0.03, 85.2171 to \
  -0.03, 45.5852 to \
  -2.57167, 45.5852 to \
  -2.57167, 85.2171 front fs empty border lc rgb '#549f' lw 0.1
set object 3960 polygon from \
  -2.5405, 85.241 to \
  -0.03, 85.241 to \
  -0.03, 45.5992 to \
  -2.5405, 45.5992 to \
  -2.5405, 85.241 front fs empty border lc rgb '#549f' lw 0.1
set object 3961 polygon from \
  -2.50861, 85.265 to \
  -0.03, 85.265 to \
  -0.03, 45.6131 to \
  -2.50861, 45.6131 to \
  -2.50861, 85.265 front fs empty border lc rgb '#549f' lw 0.1
set object 3962 polygon from \
  -2.47602, 85.2889 to \
  -0.03, 85.2889 to \
  -0.03, 45.627 to \
  -2.47602, 45.627 to \
  -2.47602, 85.2889 front fs empty border lc rgb '#549f' lw 0.1
set object 3963 polygon from \
  -2.44928, 85.3129 to \
  -0.03, 85.3129 to \
  -0.03, 45.641 to \
  -2.44928, 45.641 to \
  -2.44928, 85.3129 front fs empty border lc rgb '#549f' lw 0.1
set object 3964 polygon from \
  -2.42262, 85.3368 to \
  -0.03, 85.3368 to \
  -0.03, 45.6549 to \
  -2.42262, 45.6549 to \
  -2.42262, 85.3368 front fs empty border lc rgb '#549f' lw 0.1
set object 3965 polygon from \
  -2.39535, 85.3608 to \
  -0.03, 85.3608 to \
  -0.03, 45.6689 to \
  -2.39535, 45.6689 to \
  -2.39535, 85.3608 front fs empty border lc rgb '#549f' lw 0.1
set object 3966 polygon from \
  -2.36748, 85.3847 to \
  -0.03, 85.3847 to \
  -0.03, 45.6829 to \
  -2.36748, 45.6829 to \
  -2.36748, 85.3847 front fs empty border lc rgb '#549f' lw 0.1
set object 3967 polygon from \
  -2.33905, 85.4087 to \
  -0.03, 85.4087 to \
  -0.03, 45.6968 to \
  -2.33905, 45.6968 to \
  -2.33905, 85.4087 front fs empty border lc rgb '#549f' lw 0.1
set object 3968 polygon from \
  -2.31006, 85.4326 to \
  -0.03, 85.4326 to \
  -0.03, 45.7108 to \
  -2.31006, 45.7108 to \
  -2.31006, 85.4326 front fs empty border lc rgb '#549f' lw 0.1
set object 3969 polygon from \
  -2.28052, 85.4566 to \
  -0.03, 85.4566 to \
  -0.03, 45.7247 to \
  -2.28052, 45.7247 to \
  -2.28052, 85.4566 front fs empty border lc rgb '#549f' lw 0.1
set object 3970 polygon from \
  -2.25046, 85.4806 to \
  -0.03, 85.4806 to \
  -0.03, 45.7387 to \
  -2.25046, 45.7387 to \
  -2.25046, 85.4806 front fs empty border lc rgb '#549f' lw 0.1
set object 3971 polygon from \
  -2.21989, 85.5045 to \
  -0.03, 85.5045 to \
  -0.03, 45.7526 to \
  -2.21989, 45.7526 to \
  -2.21989, 85.5045 front fs empty border lc rgb '#549f' lw 0.1
set object 3972 polygon from \
  -2.18883, 85.5285 to \
  -0.03, 85.5285 to \
  -0.03, 45.7666 to \
  -2.18883, 45.7666 to \
  -2.18883, 85.5285 front fs empty border lc rgb '#549f' lw 0.1
set object 3973 polygon from \
  -2.1573, 85.5525 to \
  -0.03, 85.5525 to \
  -0.03, 45.7806 to \
  -2.1573, 45.7806 to \
  -2.1573, 85.5525 front fs empty border lc rgb '#549f' lw 0.1
set object 3974 polygon from \
  -2.1253, 85.5764 to \
  -0.03, 85.5764 to \
  -0.03, 45.7945 to \
  -2.1253, 45.7945 to \
  -2.1253, 85.5764 front fs empty border lc rgb '#549f' lw 0.1
set object 3975 polygon from \
  -2.12262, 85.6004 to \
  -0.03, 85.6004 to \
  -0.03, 45.8085 to \
  -2.12262, 45.8085 to \
  -2.12262, 85.6004 front fs empty border lc rgb '#549f' lw 0.1
set object 3976 polygon from \
  -2.13522, 85.6244 to \
  -0.03, 85.6244 to \
  -0.03, 45.8225 to \
  -2.13522, 45.8225 to \
  -2.13522, 85.6244 front fs empty border lc rgb '#549f' lw 0.1
set object 3977 polygon from \
  -2.14718, 85.6483 to \
  -0.03, 85.6483 to \
  -0.03, 45.8364 to \
  -2.14718, 45.8364 to \
  -2.14718, 85.6483 front fs empty border lc rgb '#549f' lw 0.1
set object 3978 polygon from \
  -2.15849, 85.6723 to \
  -0.03, 85.6723 to \
  -0.03, 45.8504 to \
  -2.15849, 45.8504 to \
  -2.15849, 85.6723 front fs empty border lc rgb '#549f' lw 0.1
set object 3979 polygon from \
  -2.16912, 85.6963 to \
  -0.03, 85.6963 to \
  -0.03, 45.8644 to \
  -2.16912, 45.8644 to \
  -2.16912, 85.6963 front fs empty border lc rgb '#549f' lw 0.1
set object 3980 polygon from \
  -2.17906, 85.7203 to \
  -0.03, 85.7203 to \
  -0.03, 45.8783 to \
  -2.17906, 45.8783 to \
  -2.17906, 85.7203 front fs empty border lc rgb '#549f' lw 0.1
set object 3981 polygon from \
  -2.18831, 85.7442 to \
  -0.03, 85.7442 to \
  -0.03, 45.8923 to \
  -2.18831, 45.8923 to \
  -2.18831, 85.7442 front fs empty border lc rgb '#549f' lw 0.1
set object 3982 polygon from \
  -2.19685, 85.7682 to \
  -0.03, 85.7682 to \
  -0.03, 45.9063 to \
  -2.19685, 45.9063 to \
  -2.19685, 85.7682 front fs empty border lc rgb '#549f' lw 0.1
set object 3983 polygon from \
  -2.20467, 85.7922 to \
  -0.03, 85.7922 to \
  -0.03, 45.9202 to \
  -2.20467, 45.9202 to \
  -2.20467, 85.7922 front fs empty border lc rgb '#549f' lw 0.1
set object 3984 polygon from \
  -2.21175, 85.8162 to \
  -0.03, 85.8162 to \
  -0.03, 45.9342 to \
  -2.21175, 45.9342 to \
  -2.21175, 85.8162 front fs empty border lc rgb '#549f' lw 0.1
set object 3985 polygon from \
  -2.21809, 85.8401 to \
  -0.03, 85.8401 to \
  -0.03, 45.9482 to \
  -2.21809, 45.9482 to \
  -2.21809, 85.8401 front fs empty border lc rgb '#549f' lw 0.1
set object 3986 polygon from \
  -2.22367, 85.8641 to \
  -0.03, 85.8641 to \
  -0.03, 45.9622 to \
  -2.22367, 45.9622 to \
  -2.22367, 85.8641 front fs empty border lc rgb '#549f' lw 0.1
set object 3987 polygon from \
  -2.22848, 85.8881 to \
  -0.03, 85.8881 to \
  -0.03, 45.9762 to \
  -2.22848, 45.9762 to \
  -2.22848, 85.8881 front fs empty border lc rgb '#549f' lw 0.1
set object 3988 polygon from \
  -2.23251, 85.9121 to \
  -0.03, 85.9121 to \
  -0.03, 45.9901 to \
  -2.23251, 45.9901 to \
  -2.23251, 85.9121 front fs empty border lc rgb '#549f' lw 0.1
set object 3989 polygon from \
  -2.23575, 85.9361 to \
  -0.03, 85.9361 to \
  -0.03, 46.0041 to \
  -2.23575, 46.0041 to \
  -2.23575, 85.9361 front fs empty border lc rgb '#549f' lw 0.1
set object 3990 polygon from \
  -2.2382, 85.9601 to \
  -0.03, 85.9601 to \
  -0.03, 46.0181 to \
  -2.2382, 46.0181 to \
  -2.2382, 85.9601 front fs empty border lc rgb '#549f' lw 0.1
set object 3991 polygon from \
  -2.23983, 85.9841 to \
  -0.03, 85.9841 to \
  -0.03, 46.0321 to \
  -2.23983, 46.0321 to \
  -2.23983, 85.9841 front fs empty border lc rgb '#549f' lw 0.1
set object 3992 polygon from \
  -2.24065, 86.008 to \
  -0.03, 86.008 to \
  -0.03, 46.0461 to \
  -2.24065, 46.0461 to \
  -2.24065, 86.008 front fs empty border lc rgb '#549f' lw 0.1
set object 3993 polygon from \
  -2.24065, 86.032 to \
  -0.03, 86.032 to \
  -0.03, 46.0601 to \
  -2.24065, 46.0601 to \
  -2.24065, 86.032 front fs empty border lc rgb '#549f' lw 0.1
set object 3994 polygon from \
  -2.24064, 86.056 to \
  -0.03, 86.056 to \
  -0.03, 46.074 to \
  -2.24064, 46.074 to \
  -2.24064, 86.056 front fs empty border lc rgb '#549f' lw 0.1
set object 3995 polygon from \
  -2.2398, 86.08 to \
  -0.03, 86.08 to \
  -0.03, 46.088 to \
  -2.2398, 46.088 to \
  -2.2398, 86.08 front fs empty border lc rgb '#549f' lw 0.1
set object 3996 polygon from \
  -2.23811, 86.104 to \
  -0.03, 86.104 to \
  -0.03, 46.102 to \
  -2.23811, 46.102 to \
  -2.23811, 86.104 front fs empty border lc rgb '#549f' lw 0.1
set object 3997 polygon from \
  -2.23557, 86.128 to \
  -0.03, 86.128 to \
  -0.03, 46.116 to \
  -2.23557, 46.116 to \
  -2.23557, 86.128 front fs empty border lc rgb '#549f' lw 0.1
set object 3998 polygon from \
  -2.23218, 86.152 to \
  -0.03, 86.152 to \
  -0.03, 46.13 to \
  -2.23218, 46.13 to \
  -2.23218, 86.152 front fs empty border lc rgb '#549f' lw 0.1
set object 3999 polygon from \
  -2.22792, 86.176 to \
  -0.03, 86.176 to \
  -0.03, 46.144 to \
  -2.22792, 46.144 to \
  -2.22792, 86.176 front fs empty border lc rgb '#549f' lw 0.1
set object 4000 polygon from \
  -2.22279, 86.2 to \
  -0.03, 86.2 to \
  -0.03, 46.158 to \
  -2.22279, 46.158 to \
  -2.22279, 86.2 front fs empty border lc rgb '#549f' lw 0.1
set object 4001 polygon from \
  -2.21678, 86.224 to \
  -0.03, 86.224 to \
  -0.03, 46.172 to \
  -2.21678, 46.172 to \
  -2.21678, 86.224 front fs empty border lc rgb '#549f' lw 0.1
set object 4002 polygon from \
  -2.2099, 86.248 to \
  -0.03, 86.248 to \
  -0.03, 46.186 to \
  -2.2099, 46.186 to \
  -2.2099, 86.248 front fs empty border lc rgb '#549f' lw 0.1
set object 4003 polygon from \
  -2.20213, 86.272 to \
  -0.03, 86.272 to \
  -0.03, 46.2 to \
  -2.20213, 46.2 to \
  -2.20213, 86.272 front fs empty border lc rgb '#549f' lw 0.1
set object 4004 polygon from \
  -2.19347, 86.296 to \
  -0.03, 86.296 to \
  -0.03, 46.214 to \
  -2.19347, 46.214 to \
  -2.19347, 86.296 front fs empty border lc rgb '#549f' lw 0.1
set object 4005 polygon from \
  -2.18391, 86.32 to \
  -0.03, 86.32 to \
  -0.03, 46.228 to \
  -2.18391, 46.228 to \
  -2.18391, 86.32 front fs empty border lc rgb '#549f' lw 0.1
set object 4006 polygon from \
  -2.17346, 86.344 to \
  -0.03, 86.344 to \
  -0.03, 46.242 to \
  -2.17346, 46.242 to \
  -2.17346, 86.344 front fs empty border lc rgb '#549f' lw 0.1
set object 4007 polygon from \
  -2.16211, 86.368 to \
  -0.03, 86.368 to \
  -0.03, 46.256 to \
  -2.16211, 46.256 to \
  -2.16211, 86.368 front fs empty border lc rgb '#549f' lw 0.1
set object 4008 polygon from \
  -2.14985, 86.392 to \
  -0.03, 86.392 to \
  -0.03, 46.27 to \
  -2.14985, 46.27 to \
  -2.14985, 86.392 front fs empty border lc rgb '#549f' lw 0.1
set object 4009 polygon from \
  -2.13669, 86.4161 to \
  -0.03, 86.4161 to \
  -0.03, 46.284 to \
  -2.13669, 46.284 to \
  -2.13669, 86.4161 front fs empty border lc rgb '#549f' lw 0.1
set object 4010 polygon from \
  -2.12263, 86.4401 to \
  -0.03, 86.4401 to \
  -0.03, 46.298 to \
  -2.12263, 46.298 to \
  -2.12263, 86.4401 front fs empty border lc rgb '#549f' lw 0.1
set object 4011 polygon from \
  -2.10766, 86.4641 to \
  -0.03, 86.4641 to \
  -0.03, 46.312 to \
  -2.10766, 46.312 to \
  -2.10766, 86.4641 front fs empty border lc rgb '#549f' lw 0.1
set object 4012 polygon from \
  -2.09178, 86.4881 to \
  -0.03, 86.4881 to \
  -0.03, 46.326 to \
  -2.09178, 46.326 to \
  -2.09178, 86.4881 front fs empty border lc rgb '#549f' lw 0.1
set object 4013 polygon from \
  -2.075, 86.5121 to \
  -0.03, 86.5121 to \
  -0.03, 46.3401 to \
  -2.075, 46.3401 to \
  -2.075, 86.5121 front fs empty border lc rgb '#549f' lw 0.1
set object 4014 polygon from \
  -2.05731, 86.5361 to \
  -0.03, 86.5361 to \
  -0.03, 46.3541 to \
  -2.05731, 46.3541 to \
  -2.05731, 86.5361 front fs empty border lc rgb '#549f' lw 0.1
set object 4015 polygon from \
  -2.03872, 86.5601 to \
  -0.03, 86.5601 to \
  -0.03, 46.3681 to \
  -2.03872, 46.3681 to \
  -2.03872, 86.5601 front fs empty border lc rgb '#549f' lw 0.1
set object 4016 polygon from \
  -2.01923, 86.5842 to \
  -0.03, 86.5842 to \
  -0.03, 46.3821 to \
  -2.01923, 46.3821 to \
  -2.01923, 86.5842 front fs empty border lc rgb '#549f' lw 0.1
set object 4017 polygon from \
  -1.99883, 86.6082 to \
  -0.03, 86.6082 to \
  -0.03, 46.3961 to \
  -1.99883, 46.3961 to \
  -1.99883, 86.6082 front fs empty border lc rgb '#549f' lw 0.1
set object 4018 polygon from \
  -1.97754, 86.6322 to \
  -0.03, 86.6322 to \
  -0.03, 46.4101 to \
  -1.97754, 46.4101 to \
  -1.97754, 86.6322 front fs empty border lc rgb '#549f' lw 0.1
set object 4019 polygon from \
  -1.98584, 86.6562 to \
  -0.03, 86.6562 to \
  -0.03, 46.4242 to \
  -1.98584, 46.4242 to \
  -1.98584, 86.6562 front fs empty border lc rgb '#549f' lw 0.1
set object 4020 polygon from \
  -1.99673, 86.6803 to \
  -0.03, 86.6803 to \
  -0.03, 46.4382 to \
  -1.99673, 46.4382 to \
  -1.99673, 86.6803 front fs empty border lc rgb '#549f' lw 0.1
set object 4021 polygon from \
  -2.00634, 86.7043 to \
  -0.03, 86.7043 to \
  -0.03, 46.4522 to \
  -2.00634, 46.4522 to \
  -2.00634, 86.7043 front fs empty border lc rgb '#549f' lw 0.1
set object 4022 polygon from \
  -2.01468, 86.7283 to \
  -0.03, 86.7283 to \
  -0.03, 46.4662 to \
  -2.01468, 46.4662 to \
  -2.01468, 86.7283 front fs empty border lc rgb '#549f' lw 0.1
set object 4023 polygon from \
  -2.02174, 86.7523 to \
  -0.03, 86.7523 to \
  -0.03, 46.4802 to \
  -2.02174, 46.4802 to \
  -2.02174, 86.7523 front fs empty border lc rgb '#549f' lw 0.1
set object 4024 polygon from \
  -2.02753, 86.7764 to \
  -0.03, 86.7764 to \
  -0.03, 46.4943 to \
  -2.02753, 46.4943 to \
  -2.02753, 86.7764 front fs empty border lc rgb '#549f' lw 0.1
set object 4025 polygon from \
  -2.03203, 86.8004 to \
  -0.03, 86.8004 to \
  -0.03, 46.5083 to \
  -2.03203, 46.5083 to \
  -2.03203, 86.8004 front fs empty border lc rgb '#549f' lw 0.1
set object 4026 polygon from \
  -2.03525, 86.8244 to \
  -0.03, 86.8244 to \
  -0.03, 46.5223 to \
  -2.03525, 46.5223 to \
  -2.03525, 86.8244 front fs empty border lc rgb '#549f' lw 0.1
set object 4027 polygon from \
  -2.0372, 86.8485 to \
  -0.03, 86.8485 to \
  -0.03, 46.5364 to \
  -2.0372, 46.5364 to \
  -2.0372, 86.8485 front fs empty border lc rgb '#549f' lw 0.1
set object 4028 polygon from \
  -2.03787, 86.8725 to \
  -0.03, 86.8725 to \
  -0.03, 46.5504 to \
  -2.03787, 46.5504 to \
  -2.03787, 86.8725 front fs empty border lc rgb '#549f' lw 0.1
set object 4029 polygon from \
  -2.03787, 86.8965 to \
  -0.03, 86.8965 to \
  -0.03, 46.5644 to \
  -2.03787, 46.5644 to \
  -2.03787, 86.8965 front fs empty border lc rgb '#549f' lw 0.1
set object 4030 polygon from \
  -2.03815, 86.9206 to \
  -0.03, 86.9206 to \
  -0.03, 46.5785 to \
  -2.03815, 46.5785 to \
  -2.03815, 86.9206 front fs empty border lc rgb '#549f' lw 0.1
set object 4031 polygon from \
  -2.03888, 86.9446 to \
  -0.03, 86.9446 to \
  -0.03, 46.5925 to \
  -2.03888, 46.5925 to \
  -2.03888, 86.9446 front fs empty border lc rgb '#549f' lw 0.1
set object 4032 polygon from \
  -2.03888, 86.9686 to \
  -0.03, 86.9686 to \
  -0.03, 46.6065 to \
  -2.03888, 46.6065 to \
  -2.03888, 86.9686 front fs empty border lc rgb '#549f' lw 0.1
set object 4033 polygon from \
  -2.03835, 86.9927 to \
  -0.03, 86.9927 to \
  -0.03, 46.6206 to \
  -2.03835, 46.6206 to \
  -2.03835, 86.9927 front fs empty border lc rgb '#549f' lw 0.1
set object 4034 polygon from \
  -2.03656, 87.0167 to \
  -0.03, 87.0167 to \
  -0.03, 46.6346 to \
  -2.03656, 46.6346 to \
  -2.03656, 87.0167 front fs empty border lc rgb '#549f' lw 0.1
set object 4035 polygon from \
  -2.03351, 87.0408 to \
  -0.03, 87.0408 to \
  -0.03, 46.6486 to \
  -2.03351, 46.6486 to \
  -2.03351, 87.0408 front fs empty border lc rgb '#549f' lw 0.1
set object 4036 polygon from \
  -2.02921, 87.0648 to \
  -0.03, 87.0648 to \
  -0.03, 46.6627 to \
  -2.02921, 46.6627 to \
  -2.02921, 87.0648 front fs empty border lc rgb '#549f' lw 0.1
set object 4037 polygon from \
  -2.02367, 87.0889 to \
  -0.03, 87.0889 to \
  -0.03, 46.6767 to \
  -2.02367, 46.6767 to \
  -2.02367, 87.0889 front fs empty border lc rgb '#549f' lw 0.1
set object 4038 polygon from \
  -2.01688, 87.1129 to \
  -0.03, 87.1129 to \
  -0.03, 46.6908 to \
  -2.01688, 46.6908 to \
  -2.01688, 87.1129 front fs empty border lc rgb '#549f' lw 0.1
set object 4039 polygon from \
  -2.00887, 87.137 to \
  -0.03, 87.137 to \
  -0.03, 46.7048 to \
  -2.00887, 46.7048 to \
  -2.00887, 87.137 front fs empty border lc rgb '#549f' lw 0.1
set object 4040 polygon from \
  -1.99963, 87.161 to \
  -0.03, 87.161 to \
  -0.03, 46.7189 to \
  -1.99963, 46.7189 to \
  -1.99963, 87.161 front fs empty border lc rgb '#549f' lw 0.1
set object 4041 polygon from \
  -1.98918, 87.1851 to \
  -0.03, 87.1851 to \
  -0.03, 46.7329 to \
  -1.98918, 46.7329 to \
  -1.98918, 87.1851 front fs empty border lc rgb '#549f' lw 0.1
set object 4042 polygon from \
  -1.97752, 87.2091 to \
  -0.03, 87.2091 to \
  -0.03, 46.7469 to \
  -1.97752, 46.7469 to \
  -1.97752, 87.2091 front fs empty border lc rgb '#549f' lw 0.1
set object 4043 polygon from \
  -1.96468, 87.2332 to \
  -0.03, 87.2332 to \
  -0.03, 46.761 to \
  -1.96468, 46.761 to \
  -1.96468, 87.2332 front fs empty border lc rgb '#549f' lw 0.1
set object 4044 polygon from \
  -1.95065, 87.2572 to \
  -0.03, 87.2572 to \
  -0.03, 46.775 to \
  -1.95065, 46.775 to \
  -1.95065, 87.2572 front fs empty border lc rgb '#549f' lw 0.1
set object 4045 polygon from \
  -1.93545, 87.2813 to \
  -0.03, 87.2813 to \
  -0.03, 46.7891 to \
  -1.93545, 46.7891 to \
  -1.93545, 87.2813 front fs empty border lc rgb '#549f' lw 0.1
set object 4046 polygon from \
  -1.92129, 87.3053 to \
  -0.03, 87.3053 to \
  -0.03, 46.8032 to \
  -1.92129, 46.8032 to \
  -1.92129, 87.3053 front fs empty border lc rgb '#549f' lw 0.1
set object 4047 polygon from \
  -1.90617, 87.3294 to \
  -0.03, 87.3294 to \
  -0.03, 46.8172 to \
  -1.90617, 46.8172 to \
  -1.90617, 87.3294 front fs empty border lc rgb '#549f' lw 0.1
set object 4048 polygon from \
  -1.88994, 87.3534 to \
  -0.03, 87.3534 to \
  -0.03, 46.8313 to \
  -1.88994, 46.8313 to \
  -1.88994, 87.3534 front fs empty border lc rgb '#549f' lw 0.1
set object 4049 polygon from \
  -1.8726, 87.3775 to \
  -0.03, 87.3775 to \
  -0.03, 46.8453 to \
  -1.8726, 46.8453 to \
  -1.8726, 87.3775 front fs empty border lc rgb '#549f' lw 0.1
set object 4050 polygon from \
  -1.85417, 87.4016 to \
  -0.03, 87.4016 to \
  -0.03, 46.8594 to \
  -1.85417, 46.8594 to \
  -1.85417, 87.4016 front fs empty border lc rgb '#549f' lw 0.1
set object 4051 polygon from \
  -1.83466, 87.4256 to \
  -0.03, 87.4256 to \
  -0.03, 46.8734 to \
  -1.83466, 46.8734 to \
  -1.83466, 87.4256 front fs empty border lc rgb '#549f' lw 0.1
set object 4052 polygon from \
  -1.8141, 87.4497 to \
  -0.03, 87.4497 to \
  -0.03, 46.8875 to \
  -1.8141, 46.8875 to \
  -1.8141, 87.4497 front fs empty border lc rgb '#549f' lw 0.1
set object 4053 polygon from \
  -1.7925, 87.4738 to \
  -0.03, 87.4738 to \
  -0.03, 46.9016 to \
  -1.7925, 46.9016 to \
  -1.7925, 87.4738 front fs empty border lc rgb '#549f' lw 0.1
set object 4054 polygon from \
  -1.76988, 87.4978 to \
  -0.03, 87.4978 to \
  -0.03, 46.9156 to \
  -1.76988, 46.9156 to \
  -1.76988, 87.4978 front fs empty border lc rgb '#549f' lw 0.1
set object 4055 polygon from \
  -1.74626, 87.5219 to \
  -0.03, 87.5219 to \
  -0.03, 46.9297 to \
  -1.74626, 46.9297 to \
  -1.74626, 87.5219 front fs empty border lc rgb '#549f' lw 0.1
set object 4056 polygon from \
  -1.72166, 87.546 to \
  -0.03, 87.546 to \
  -0.03, 46.9438 to \
  -1.72166, 46.9438 to \
  -1.72166, 87.546 front fs empty border lc rgb '#549f' lw 0.1
set object 4057 polygon from \
  -1.6961, 87.57 to \
  -0.03, 87.57 to \
  -0.03, 46.9578 to \
  -1.6961, 46.9578 to \
  -1.6961, 87.57 front fs empty border lc rgb '#549f' lw 0.1
set object 4058 polygon from \
  -1.66959, 87.5941 to \
  -0.03, 87.5941 to \
  -0.03, 46.9719 to \
  -1.66959, 46.9719 to \
  -1.66959, 87.5941 front fs empty border lc rgb '#549f' lw 0.1
set object 4059 polygon from \
  -1.64218, 87.6182 to \
  -0.03, 87.6182 to \
  -0.03, 46.986 to \
  -1.64218, 46.986 to \
  -1.64218, 87.6182 front fs empty border lc rgb '#549f' lw 0.1
set object 4060 polygon from \
  -1.65269, 87.6423 to \
  -0.03, 87.6423 to \
  -0.03, 47 to \
  -1.65269, 47 to \
  -1.65269, 87.6423 front fs empty border lc rgb '#549f' lw 0.1
set object 4061 polygon from \
  -1.66846, 87.6663 to \
  -0.03, 87.6663 to \
  -0.03, 47.0141 to \
  -1.66846, 47.0141 to \
  -1.66846, 87.6663 front fs empty border lc rgb '#549f' lw 0.1
set object 4062 polygon from \
  -1.68361, 87.6904 to \
  -0.03, 87.6904 to \
  -0.03, 47.0282 to \
  -1.68361, 47.0282 to \
  -1.68361, 87.6904 front fs empty border lc rgb '#549f' lw 0.1
set object 4063 polygon from \
  -1.69815, 87.7145 to \
  -0.03, 87.7145 to \
  -0.03, 47.0422 to \
  -1.69815, 47.0422 to \
  -1.69815, 87.7145 front fs empty border lc rgb '#549f' lw 0.1
set object 4064 polygon from \
  -1.71208, 87.7386 to \
  -0.03, 87.7386 to \
  -0.03, 47.0563 to \
  -1.71208, 47.0563 to \
  -1.71208, 87.7386 front fs empty border lc rgb '#549f' lw 0.1
set object 4065 polygon from \
  -1.72541, 87.7626 to \
  -0.03, 87.7626 to \
  -0.03, 47.0704 to \
  -1.72541, 47.0704 to \
  -1.72541, 87.7626 front fs empty border lc rgb '#549f' lw 0.1
set object 4066 polygon from \
  -1.73814, 87.7867 to \
  -0.03, 87.7867 to \
  -0.03, 47.0845 to \
  -1.73814, 47.0845 to \
  -1.73814, 87.7867 front fs empty border lc rgb '#549f' lw 0.1
set object 4067 polygon from \
  -1.75027, 87.8108 to \
  -0.03, 87.8108 to \
  -0.03, 47.0986 to \
  -1.75027, 47.0986 to \
  -1.75027, 87.8108 front fs empty border lc rgb '#549f' lw 0.1
set object 4068 polygon from \
  -1.76183, 87.8349 to \
  -0.03, 87.8349 to \
  -0.03, 47.1126 to \
  -1.76183, 47.1126 to \
  -1.76183, 87.8349 front fs empty border lc rgb '#549f' lw 0.1
set object 4069 polygon from \
  -1.7728, 87.859 to \
  -0.03, 87.859 to \
  -0.03, 47.1267 to \
  -1.7728, 47.1267 to \
  -1.7728, 87.859 front fs empty border lc rgb '#549f' lw 0.1
set object 4070 polygon from \
  -1.7832, 87.8831 to \
  -0.03, 87.8831 to \
  -0.03, 47.1408 to \
  -1.7832, 47.1408 to \
  -1.7832, 87.8831 front fs empty border lc rgb '#549f' lw 0.1
set object 4071 polygon from \
  -1.79303, 87.9072 to \
  -0.03, 87.9072 to \
  -0.03, 47.1549 to \
  -1.79303, 47.1549 to \
  -1.79303, 87.9072 front fs empty border lc rgb '#549f' lw 0.1
set object 4072 polygon from \
  -1.8023, 87.9312 to \
  -0.03, 87.9312 to \
  -0.03, 47.169 to \
  -1.8023, 47.169 to \
  -1.8023, 87.9312 front fs empty border lc rgb '#549f' lw 0.1
set object 4073 polygon from \
  -1.81102, 87.9553 to \
  -0.03, 87.9553 to \
  -0.03, 47.1831 to \
  -1.81102, 47.1831 to \
  -1.81102, 87.9553 front fs empty border lc rgb '#549f' lw 0.1
set object 4074 polygon from \
  -1.81919, 87.9794 to \
  -0.03, 87.9794 to \
  -0.03, 47.1971 to \
  -1.81919, 47.1971 to \
  -1.81919, 87.9794 front fs empty border lc rgb '#549f' lw 0.1
set object 4075 polygon from \
  -1.82682, 88.0035 to \
  -0.03, 88.0035 to \
  -0.03, 47.2112 to \
  -1.82682, 47.2112 to \
  -1.82682, 88.0035 front fs empty border lc rgb '#549f' lw 0.1
set object 4076 polygon from \
  -1.83392, 88.0276 to \
  -0.03, 88.0276 to \
  -0.03, 47.2253 to \
  -1.83392, 47.2253 to \
  -1.83392, 88.0276 front fs empty border lc rgb '#549f' lw 0.1
set object 4077 polygon from \
  -1.8405, 88.0517 to \
  -0.03, 88.0517 to \
  -0.03, 47.2394 to \
  -1.8405, 47.2394 to \
  -1.8405, 88.0517 front fs empty border lc rgb '#549f' lw 0.1
set object 4078 polygon from \
  -1.84656, 88.0758 to \
  -0.03, 88.0758 to \
  -0.03, 47.2535 to \
  -1.84656, 47.2535 to \
  -1.84656, 88.0758 front fs empty border lc rgb '#549f' lw 0.1
set object 4079 polygon from \
  -1.85212, 88.0999 to \
  -0.03, 88.0999 to \
  -0.03, 47.2676 to \
  -1.85212, 47.2676 to \
  -1.85212, 88.0999 front fs empty border lc rgb '#549f' lw 0.1
set object 4080 polygon from \
  -1.85718, 88.124 to \
  -0.03, 88.124 to \
  -0.03, 47.2817 to \
  -1.85718, 47.2817 to \
  -1.85718, 88.124 front fs empty border lc rgb '#549f' lw 0.1
set object 4081 polygon from \
  -1.86175, 88.1481 to \
  -0.03, 88.1481 to \
  -0.03, 47.2958 to \
  -1.86175, 47.2958 to \
  -1.86175, 88.1481 front fs empty border lc rgb '#549f' lw 0.1
set object 4082 polygon from \
  -1.86583, 88.1722 to \
  -0.03, 88.1722 to \
  -0.03, 47.3099 to \
  -1.86583, 47.3099 to \
  -1.86583, 88.1722 front fs empty border lc rgb '#549f' lw 0.1
set object 4083 polygon from \
  -1.86945, 88.1963 to \
  -0.03, 88.1963 to \
  -0.03, 47.324 to \
  -1.86945, 47.324 to \
  -1.86945, 88.1963 front fs empty border lc rgb '#549f' lw 0.1
set object 4084 polygon from \
  -1.8726, 88.2204 to \
  -0.03, 88.2204 to \
  -0.03, 47.3381 to \
  -1.8726, 47.3381 to \
  -1.8726, 88.2204 front fs empty border lc rgb '#549f' lw 0.1
set object 4085 polygon from \
  -1.8753, 88.2445 to \
  -0.03, 88.2445 to \
  -0.03, 47.3522 to \
  -1.8753, 47.3522 to \
  -1.8753, 88.2445 front fs empty border lc rgb '#549f' lw 0.1
set object 4086 polygon from \
  -1.87755, 88.2686 to \
  -0.03, 88.2686 to \
  -0.03, 47.3663 to \
  -1.87755, 47.3663 to \
  -1.87755, 88.2686 front fs empty border lc rgb '#549f' lw 0.1
set object 4087 polygon from \
  -1.87937, 88.2927 to \
  -0.03, 88.2927 to \
  -0.03, 47.3804 to \
  -1.87937, 47.3804 to \
  -1.87937, 88.2927 front fs empty border lc rgb '#549f' lw 0.1
set object 4088 polygon from \
  -1.88077, 88.3168 to \
  -0.03, 88.3168 to \
  -0.03, 47.3945 to \
  -1.88077, 47.3945 to \
  -1.88077, 88.3168 front fs empty border lc rgb '#549f' lw 0.1
set object 4089 polygon from \
  -1.88175, 88.341 to \
  -0.03, 88.341 to \
  -0.03, 47.4086 to \
  -1.88175, 47.4086 to \
  -1.88175, 88.341 front fs empty border lc rgb '#549f' lw 0.1
set object 4090 polygon from \
  -1.91155, 88.3651 to \
  -0.03, 88.3651 to \
  -0.03, 47.4227 to \
  -1.91155, 47.4227 to \
  -1.91155, 88.3651 front fs empty border lc rgb '#549f' lw 0.1
set object 4091 polygon from \
  -1.94958, 88.3892 to \
  -0.03, 88.3892 to \
  -0.03, 47.4368 to \
  -1.94958, 47.4368 to \
  -1.94958, 88.3892 front fs empty border lc rgb '#549f' lw 0.1
set object 4092 polygon from \
  -1.98701, 88.4133 to \
  -0.03, 88.4133 to \
  -0.03, 47.4509 to \
  -1.98701, 47.4509 to \
  -1.98701, 88.4133 front fs empty border lc rgb '#549f' lw 0.1
set object 4093 polygon from \
  -2.02384, 88.4374 to \
  -0.03, 88.4374 to \
  -0.03, 47.4651 to \
  -2.02384, 47.4651 to \
  -2.02384, 88.4374 front fs empty border lc rgb '#549f' lw 0.1
set object 4094 polygon from \
  -2.06004, 88.4615 to \
  -0.03, 88.4615 to \
  -0.03, 47.4792 to \
  -2.06004, 47.4792 to \
  -2.06004, 88.4615 front fs empty border lc rgb '#549f' lw 0.1
set object 4095 polygon from \
  -2.09559, 88.4856 to \
  -0.03, 88.4856 to \
  -0.03, 47.4933 to \
  -2.09559, 47.4933 to \
  -2.09559, 88.4856 front fs empty border lc rgb '#549f' lw 0.1
set object 4096 polygon from \
  -2.13047, 88.5098 to \
  -0.03, 88.5098 to \
  -0.03, 47.5074 to \
  -2.13047, 47.5074 to \
  -2.13047, 88.5098 front fs empty border lc rgb '#549f' lw 0.1
set object 4097 polygon from \
  -2.16467, 88.5339 to \
  -0.03, 88.5339 to \
  -0.03, 47.5215 to \
  -2.16467, 47.5215 to \
  -2.16467, 88.5339 front fs empty border lc rgb '#549f' lw 0.1
set object 4098 polygon from \
  -2.19816, 88.558 to \
  -0.03, 88.558 to \
  -0.03, 47.5356 to \
  -2.19816, 47.5356 to \
  -2.19816, 88.558 front fs empty border lc rgb '#549f' lw 0.1
set object 4099 polygon from \
  -2.23094, 88.5821 to \
  -0.03, 88.5821 to \
  -0.03, 47.5498 to \
  -2.23094, 47.5498 to \
  -2.23094, 88.5821 front fs empty border lc rgb '#549f' lw 0.1
set object 4100 polygon from \
  -2.26297, 88.6063 to \
  -0.03, 88.6063 to \
  -0.03, 47.5639 to \
  -2.26297, 47.5639 to \
  -2.26297, 88.6063 front fs empty border lc rgb '#549f' lw 0.1
set object 4101 polygon from \
  -2.29426, 88.6304 to \
  -0.03, 88.6304 to \
  -0.03, 47.578 to \
  -2.29426, 47.578 to \
  -2.29426, 88.6304 front fs empty border lc rgb '#549f' lw 0.1
set object 4102 polygon from \
  -2.32477, 88.6545 to \
  -0.03, 88.6545 to \
  -0.03, 47.5921 to \
  -2.32477, 47.5921 to \
  -2.32477, 88.6545 front fs empty border lc rgb '#549f' lw 0.1
set object 4103 polygon from \
  -2.35449, 88.6786 to \
  -0.03, 88.6786 to \
  -0.03, 47.6062 to \
  -2.35449, 47.6062 to \
  -2.35449, 88.6786 front fs empty border lc rgb '#549f' lw 0.1
set object 4104 polygon from \
  -2.3834, 88.7028 to \
  -0.03, 88.7028 to \
  -0.03, 47.6204 to \
  -2.3834, 47.6204 to \
  -2.3834, 88.7028 front fs empty border lc rgb '#549f' lw 0.1
set object 4105 polygon from \
  -2.4115, 88.7269 to \
  -0.03, 88.7269 to \
  -0.03, 47.6345 to \
  -2.4115, 47.6345 to \
  -2.4115, 88.7269 front fs empty border lc rgb '#549f' lw 0.1
set object 4106 polygon from \
  -2.43876, 88.751 to \
  -0.03, 88.751 to \
  -0.03, 47.6486 to \
  -2.43876, 47.6486 to \
  -2.43876, 88.751 front fs empty border lc rgb '#549f' lw 0.1
set object 4107 polygon from \
  -2.46517, 88.7752 to \
  -0.03, 88.7752 to \
  -0.03, 47.6628 to \
  -2.46517, 47.6628 to \
  -2.46517, 88.7752 front fs empty border lc rgb '#549f' lw 0.1
set object 4108 polygon from \
  -2.49072, 88.7993 to \
  -0.03, 88.7993 to \
  -0.03, 47.6769 to \
  -2.49072, 47.6769 to \
  -2.49072, 88.7993 front fs empty border lc rgb '#549f' lw 0.1
set object 4109 polygon from \
  -2.51539, 88.8234 to \
  -0.03, 88.8234 to \
  -0.03, 47.691 to \
  -2.51539, 47.691 to \
  -2.51539, 88.8234 front fs empty border lc rgb '#549f' lw 0.1
set object 4110 polygon from \
  -2.53917, 88.8476 to \
  -0.03, 88.8476 to \
  -0.03, 47.7052 to \
  -2.53917, 47.7052 to \
  -2.53917, 88.8476 front fs empty border lc rgb '#549f' lw 0.1
set object 4111 polygon from \
  -2.56204, 88.8717 to \
  -0.03, 88.8717 to \
  -0.03, 47.7193 to \
  -2.56204, 47.7193 to \
  -2.56204, 88.8717 front fs empty border lc rgb '#549f' lw 0.1
set object 4112 polygon from \
  -2.58399, 88.8958 to \
  -0.03, 88.8958 to \
  -0.03, 47.7334 to \
  -2.58399, 47.7334 to \
  -2.58399, 88.8958 front fs empty border lc rgb '#549f' lw 0.1
set object 4113 polygon from \
  -2.60502, 88.92 to \
  -0.03, 88.92 to \
  -0.03, 47.7476 to \
  -2.60502, 47.7476 to \
  -2.60502, 88.92 front fs empty border lc rgb '#549f' lw 0.1
set object 4114 polygon from \
  -2.6251, 88.9441 to \
  -0.03, 88.9441 to \
  -0.03, 47.7617 to \
  -2.6251, 47.7617 to \
  -2.6251, 88.9441 front fs empty border lc rgb '#549f' lw 0.1
set object 4115 polygon from \
  -2.64423, 88.9683 to \
  -0.03, 88.9683 to \
  -0.03, 47.7758 to \
  -2.64423, 47.7758 to \
  -2.64423, 88.9683 front fs empty border lc rgb '#549f' lw 0.1
set object 4116 polygon from \
  -2.66239, 88.9924 to \
  -0.03, 88.9924 to \
  -0.03, 47.79 to \
  -2.66239, 47.79 to \
  -2.66239, 88.9924 front fs empty border lc rgb '#549f' lw 0.1
set object 4117 polygon from \
  -2.67958, 89.0166 to \
  -0.03, 89.0166 to \
  -0.03, 47.8041 to \
  -2.67958, 47.8041 to \
  -2.67958, 89.0166 front fs empty border lc rgb '#549f' lw 0.1
set object 4118 polygon from \
  -2.69579, 89.0407 to \
  -0.03, 89.0407 to \
  -0.03, 47.8183 to \
  -2.69579, 47.8183 to \
  -2.69579, 89.0407 front fs empty border lc rgb '#549f' lw 0.1
set object 4119 polygon from \
  -2.711, 89.0649 to \
  -0.03, 89.0649 to \
  -0.03, 47.8324 to \
  -2.711, 47.8324 to \
  -2.711, 89.0649 front fs empty border lc rgb '#549f' lw 0.1
set object 4120 polygon from \
  -2.72521, 89.089 to \
  -0.03, 89.089 to \
  -0.03, 47.8466 to \
  -2.72521, 47.8466 to \
  -2.72521, 89.089 front fs empty border lc rgb '#549f' lw 0.1
set object 4121 polygon from \
  -2.7384, 89.1132 to \
  -0.03, 89.1132 to \
  -0.03, 47.8607 to \
  -2.7384, 47.8607 to \
  -2.7384, 89.1132 front fs empty border lc rgb '#549f' lw 0.1
set object 4122 polygon from \
  -2.75058, 89.1373 to \
  -0.03, 89.1373 to \
  -0.03, 47.8748 to \
  -2.75058, 47.8748 to \
  -2.75058, 89.1373 front fs empty border lc rgb '#549f' lw 0.1
set object 4123 polygon from \
  -2.76174, 89.1615 to \
  -0.03, 89.1615 to \
  -0.03, 47.889 to \
  -2.76174, 47.889 to \
  -2.76174, 89.1615 front fs empty border lc rgb '#549f' lw 0.1
set object 4124 polygon from \
  -2.77186, 89.1856 to \
  -0.03, 89.1856 to \
  -0.03, 47.9031 to \
  -2.77186, 47.9031 to \
  -2.77186, 89.1856 front fs empty border lc rgb '#549f' lw 0.1
set object 4125 polygon from \
  -2.78094, 89.2098 to \
  -0.03, 89.2098 to \
  -0.03, 47.9173 to \
  -2.78094, 47.9173 to \
  -2.78094, 89.2098 front fs empty border lc rgb '#549f' lw 0.1
set object 4126 polygon from \
  -2.78897, 89.2339 to \
  -0.03, 89.2339 to \
  -0.03, 47.9315 to \
  -2.78897, 47.9315 to \
  -2.78897, 89.2339 front fs empty border lc rgb '#549f' lw 0.1
set object 4127 polygon from \
  -2.79596, 89.2581 to \
  -0.03, 89.2581 to \
  -0.03, 47.9456 to \
  -2.79596, 47.9456 to \
  -2.79596, 89.2581 front fs empty border lc rgb '#549f' lw 0.1
set object 4128 polygon from \
  -2.80189, 89.2822 to \
  -0.03, 89.2822 to \
  -0.03, 47.9598 to \
  -2.80189, 47.9598 to \
  -2.80189, 89.2822 front fs empty border lc rgb '#549f' lw 0.1
set object 4129 polygon from \
  -2.80677, 89.3064 to \
  -0.03, 89.3064 to \
  -0.03, 47.9739 to \
  -2.80677, 47.9739 to \
  -2.80677, 89.3064 front fs empty border lc rgb '#549f' lw 0.1
set object 4130 polygon from \
  -2.81058, 89.3306 to \
  -0.03, 89.3306 to \
  -0.03, 47.9881 to \
  -2.81058, 47.9881 to \
  -2.81058, 89.3306 front fs empty border lc rgb '#549f' lw 0.1
set object 4131 polygon from \
  -2.81332, 89.3547 to \
  -0.03, 89.3547 to \
  -0.03, 48.0022 to \
  -2.81332, 48.0022 to \
  -2.81332, 89.3547 front fs empty border lc rgb '#549f' lw 0.1
set object 4132 polygon from \
  -2.815, 89.3789 to \
  -0.03, 89.3789 to \
  -0.03, 48.0164 to \
  -2.815, 48.0164 to \
  -2.815, 89.3789 front fs empty border lc rgb '#549f' lw 0.1
set object 4133 polygon from \
  -2.81561, 89.4031 to \
  -0.03, 89.4031 to \
  -0.03, 48.0306 to \
  -2.81561, 48.0306 to \
  -2.81561, 89.4031 front fs empty border lc rgb '#549f' lw 0.1
set object 4134 polygon from \
  -2.81561, 89.4272 to \
  -0.03, 89.4272 to \
  -0.03, 48.0447 to \
  -2.81561, 48.0447 to \
  -2.81561, 89.4272 front fs empty border lc rgb '#549f' lw 0.1
set object 4135 polygon from \
  -2.81514, 89.4514 to \
  -0.03, 89.4514 to \
  -0.03, 48.0589 to \
  -2.81514, 48.0589 to \
  -2.81514, 89.4514 front fs empty border lc rgb '#549f' lw 0.1
set object 4136 polygon from \
  -2.81361, 89.4756 to \
  -0.03, 89.4756 to \
  -0.03, 48.0731 to \
  -2.81361, 48.0731 to \
  -2.81361, 89.4756 front fs empty border lc rgb '#549f' lw 0.1
set object 4137 polygon from \
  -2.81901, 89.4997 to \
  -0.03, 89.4997 to \
  -0.03, 48.0872 to \
  -2.81901, 48.0872 to \
  -2.81901, 89.4997 front fs empty border lc rgb '#549f' lw 0.1
set object 4138 polygon from \
  -2.82594, 89.5239 to \
  -0.03, 89.5239 to \
  -0.03, 48.1014 to \
  -2.82594, 48.1014 to \
  -2.82594, 89.5239 front fs empty border lc rgb '#549f' lw 0.1
set object 4139 polygon from \
  -2.83182, 89.5481 to \
  -0.03, 89.5481 to \
  -0.03, 48.1156 to \
  -2.83182, 48.1156 to \
  -2.83182, 89.5481 front fs empty border lc rgb '#549f' lw 0.1
set object 4140 polygon from \
  -2.83665, 89.5723 to \
  -0.03, 89.5723 to \
  -0.03, 48.1297 to \
  -2.83665, 48.1297 to \
  -2.83665, 89.5723 front fs empty border lc rgb '#549f' lw 0.1
set object 4141 polygon from \
  -2.84041, 89.5964 to \
  -0.03, 89.5964 to \
  -0.03, 48.1439 to \
  -2.84041, 48.1439 to \
  -2.84041, 89.5964 front fs empty border lc rgb '#549f' lw 0.1
set object 4142 polygon from \
  -2.84312, 89.6206 to \
  -0.03, 89.6206 to \
  -0.03, 48.1581 to \
  -2.84312, 48.1581 to \
  -2.84312, 89.6206 front fs empty border lc rgb '#549f' lw 0.1
set object 4143 polygon from \
  -2.84477, 89.6448 to \
  -0.03, 89.6448 to \
  -0.03, 48.1722 to \
  -2.84477, 48.1722 to \
  -2.84477, 89.6448 front fs empty border lc rgb '#549f' lw 0.1
set object 4144 polygon from \
  -2.84535, 89.669 to \
  -0.03, 89.669 to \
  -0.03, 48.1864 to \
  -2.84535, 48.1864 to \
  -2.84535, 89.669 front fs empty border lc rgb '#549f' lw 0.1
set object 4145 polygon from \
  -2.84535, 89.6931 to \
  -0.03, 89.6931 to \
  -0.03, 48.2006 to \
  -2.84535, 48.2006 to \
  -2.84535, 89.6931 front fs empty border lc rgb '#549f' lw 0.1
set object 4146 polygon from \
  -2.84488, 89.7173 to \
  -0.03, 89.7173 to \
  -0.03, 48.2148 to \
  -2.84488, 48.2148 to \
  -2.84488, 89.7173 front fs empty border lc rgb '#549f' lw 0.1
set object 4147 polygon from \
  -2.84335, 89.7415 to \
  -0.03, 89.7415 to \
  -0.03, 48.229 to \
  -2.84335, 48.229 to \
  -2.84335, 89.7415 front fs empty border lc rgb '#549f' lw 0.1
set object 4148 polygon from \
  -2.84076, 89.7657 to \
  -0.03, 89.7657 to \
  -0.03, 48.2431 to \
  -2.84076, 48.2431 to \
  -2.84076, 89.7657 front fs empty border lc rgb '#549f' lw 0.1
set object 4149 polygon from \
  -2.83711, 89.7899 to \
  -0.03, 89.7899 to \
  -0.03, 48.2573 to \
  -2.83711, 48.2573 to \
  -2.83711, 89.7899 front fs empty border lc rgb '#549f' lw 0.1
set object 4150 polygon from \
  -2.83241, 89.8141 to \
  -0.03, 89.8141 to \
  -0.03, 48.2715 to \
  -2.83241, 48.2715 to \
  -2.83241, 89.8141 front fs empty border lc rgb '#549f' lw 0.1
set object 4151 polygon from \
  -2.82667, 89.8383 to \
  -0.03, 89.8383 to \
  -0.03, 48.2857 to \
  -2.82667, 48.2857 to \
  -2.82667, 89.8383 front fs empty border lc rgb '#549f' lw 0.1
set object 4152 polygon from \
  -2.81987, 89.8624 to \
  -0.03, 89.8624 to \
  -0.03, 48.2999 to \
  -2.81987, 48.2999 to \
  -2.81987, 89.8624 front fs empty border lc rgb '#549f' lw 0.1
set object 4153 polygon from \
  -2.81204, 89.8866 to \
  -0.03, 89.8866 to \
  -0.03, 48.3141 to \
  -2.81204, 48.3141 to \
  -2.81204, 89.8866 front fs empty border lc rgb '#549f' lw 0.1
set object 4154 polygon from \
  -2.80317, 89.9108 to \
  -0.03, 89.9108 to \
  -0.03, 48.3282 to \
  -2.80317, 48.3282 to \
  -2.80317, 89.9108 front fs empty border lc rgb '#549f' lw 0.1
set object 4155 polygon from \
  -2.79326, 89.935 to \
  -0.03, 89.935 to \
  -0.03, 48.3424 to \
  -2.79326, 48.3424 to \
  -2.79326, 89.935 front fs empty border lc rgb '#549f' lw 0.1
set object 4156 polygon from \
  -2.78233, 89.9592 to \
  -0.03, 89.9592 to \
  -0.03, 48.3566 to \
  -2.78233, 48.3566 to \
  -2.78233, 89.9592 front fs empty border lc rgb '#549f' lw 0.1
set object 4157 polygon from \
  -2.77039, 89.9834 to \
  -0.03, 89.9834 to \
  -0.03, 48.3708 to \
  -2.77039, 48.3708 to \
  -2.77039, 89.9834 front fs empty border lc rgb '#549f' lw 0.1
set object 4158 polygon from \
  -2.75743, 90.0076 to \
  -0.03, 90.0076 to \
  -0.03, 48.385 to \
  -2.75743, 48.385 to \
  -2.75743, 90.0076 front fs empty border lc rgb '#549f' lw 0.1
set object 4159 polygon from \
  -2.74475, 90.0318 to \
  -0.03, 90.0318 to \
  -0.03, 48.3992 to \
  -2.74475, 48.3992 to \
  -2.74475, 90.0318 front fs empty border lc rgb '#549f' lw 0.1
set object 4160 polygon from \
  -2.73233, 90.056 to \
  -0.03, 90.056 to \
  -0.03, 48.4134 to \
  -2.73233, 48.4134 to \
  -2.73233, 90.056 front fs empty border lc rgb '#549f' lw 0.1
set object 4161 polygon from \
  -2.71887, 90.0802 to \
  -0.03, 90.0802 to \
  -0.03, 48.4276 to \
  -2.71887, 48.4276 to \
  -2.71887, 90.0802 front fs empty border lc rgb '#549f' lw 0.1
set object 4162 polygon from \
  -2.70438, 90.1044 to \
  -0.03, 90.1044 to \
  -0.03, 48.4418 to \
  -2.70438, 48.4418 to \
  -2.70438, 90.1044 front fs empty border lc rgb '#549f' lw 0.1
set object 4163 polygon from \
  -2.68887, 90.1286 to \
  -0.03, 90.1286 to \
  -0.03, 48.456 to \
  -2.68887, 48.456 to \
  -2.68887, 90.1286 front fs empty border lc rgb '#549f' lw 0.1
set object 4164 polygon from \
  -2.67235, 90.1528 to \
  -0.03, 90.1528 to \
  -0.03, 48.4702 to \
  -2.67235, 48.4702 to \
  -2.67235, 90.1528 front fs empty border lc rgb '#549f' lw 0.1
set object 4165 polygon from \
  -2.65725, 90.177 to \
  -0.03, 90.177 to \
  -0.03, 48.4844 to \
  -2.65725, 48.4844 to \
  -2.65725, 90.177 front fs empty border lc rgb '#549f' lw 0.1
set object 4166 polygon from \
  -2.64414, 90.2012 to \
  -0.03, 90.2012 to \
  -0.03, 48.4986 to \
  -2.64414, 48.4986 to \
  -2.64414, 90.2012 front fs empty border lc rgb '#549f' lw 0.1
set object 4167 polygon from \
  -2.63005, 90.2254 to \
  -0.03, 90.2254 to \
  -0.03, 48.5128 to \
  -2.63005, 48.5128 to \
  -2.63005, 90.2254 front fs empty border lc rgb '#549f' lw 0.1
set object 4168 polygon from \
  -2.61498, 90.2496 to \
  -0.03, 90.2496 to \
  -0.03, 48.527 to \
  -2.61498, 48.527 to \
  -2.61498, 90.2496 front fs empty border lc rgb '#549f' lw 0.1
set object 4169 polygon from \
  -2.59895, 90.2739 to \
  -0.03, 90.2739 to \
  -0.03, 48.5412 to \
  -2.59895, 48.5412 to \
  -2.59895, 90.2739 front fs empty border lc rgb '#549f' lw 0.1
set object 4170 polygon from \
  -2.58197, 90.2981 to \
  -0.03, 90.2981 to \
  -0.03, 48.5554 to \
  -2.58197, 48.5554 to \
  -2.58197, 90.2981 front fs empty border lc rgb '#549f' lw 0.1
set object 4171 polygon from \
  -2.56404, 90.3223 to \
  -0.03, 90.3223 to \
  -0.03, 48.5696 to \
  -2.56404, 48.5696 to \
  -2.56404, 90.3223 front fs empty border lc rgb '#549f' lw 0.1
set object 4172 polygon from \
  -2.54519, 90.3465 to \
  -0.03, 90.3465 to \
  -0.03, 48.5838 to \
  -2.54519, 48.5838 to \
  -2.54519, 90.3465 front fs empty border lc rgb '#549f' lw 0.1
set object 4173 polygon from \
  -2.52542, 90.3707 to \
  -0.03, 90.3707 to \
  -0.03, 48.5981 to \
  -2.52542, 48.5981 to \
  -2.52542, 90.3707 front fs empty border lc rgb '#549f' lw 0.1
set object 4174 polygon from \
  -2.50474, 90.3949 to \
  -0.03, 90.3949 to \
  -0.03, 48.6123 to \
  -2.50474, 48.6123 to \
  -2.50474, 90.3949 front fs empty border lc rgb '#549f' lw 0.1
set object 4175 polygon from \
  -2.48317, 90.4191 to \
  -0.03, 90.4191 to \
  -0.03, 48.6265 to \
  -2.48317, 48.6265 to \
  -2.48317, 90.4191 front fs empty border lc rgb '#549f' lw 0.1
set object 4176 polygon from \
  -2.46071, 90.4434 to \
  -0.03, 90.4434 to \
  -0.03, 48.6407 to \
  -2.46071, 48.6407 to \
  -2.46071, 90.4434 front fs empty border lc rgb '#549f' lw 0.1
set object 4177 polygon from \
  -2.43739, 90.4676 to \
  -0.03, 90.4676 to \
  -0.03, 48.6549 to \
  -2.43739, 48.6549 to \
  -2.43739, 90.4676 front fs empty border lc rgb '#549f' lw 0.1
set object 4178 polygon from \
  -2.41322, 90.4918 to \
  -0.03, 90.4918 to \
  -0.03, 48.6691 to \
  -2.41322, 48.6691 to \
  -2.41322, 90.4918 front fs empty border lc rgb '#549f' lw 0.1
set object 4179 polygon from \
  -2.38821, 90.516 to \
  -0.03, 90.516 to \
  -0.03, 48.6834 to \
  -2.38821, 48.6834 to \
  -2.38821, 90.516 front fs empty border lc rgb '#549f' lw 0.1
set object 4180 polygon from \
  -2.36238, 90.5403 to \
  -0.03, 90.5403 to \
  -0.03, 48.6976 to \
  -2.36238, 48.6976 to \
  -2.36238, 90.5403 front fs empty border lc rgb '#549f' lw 0.1
set object 4181 polygon from \
  -2.33574, 90.5645 to \
  -0.03, 90.5645 to \
  -0.03, 48.7118 to \
  -2.33574, 48.7118 to \
  -2.33574, 90.5645 front fs empty border lc rgb '#549f' lw 0.1
set object 4182 polygon from \
  -2.30831, 90.5887 to \
  -0.03, 90.5887 to \
  -0.03, 48.726 to \
  -2.30831, 48.726 to \
  -2.30831, 90.5887 front fs empty border lc rgb '#549f' lw 0.1
set object 4183 polygon from \
  -2.28011, 90.6129 to \
  -0.03, 90.6129 to \
  -0.03, 48.7402 to \
  -2.28011, 48.7402 to \
  -2.28011, 90.6129 front fs empty border lc rgb '#549f' lw 0.1
set object 4184 polygon from \
  -2.25114, 90.6372 to \
  -0.03, 90.6372 to \
  -0.03, 48.7545 to \
  -2.25114, 48.7545 to \
  -2.25114, 90.6372 front fs empty border lc rgb '#549f' lw 0.1
set object 4185 polygon from \
  -2.22143, 90.6614 to \
  -0.03, 90.6614 to \
  -0.03, 48.7687 to \
  -2.22143, 48.7687 to \
  -2.22143, 90.6614 front fs empty border lc rgb '#549f' lw 0.1
set object 4186 polygon from \
  -2.191, 90.6856 to \
  -0.03, 90.6856 to \
  -0.03, 48.7829 to \
  -2.191, 48.7829 to \
  -2.191, 90.6856 front fs empty border lc rgb '#549f' lw 0.1
set object 4187 polygon from \
  -2.15985, 90.7099 to \
  -0.03, 90.7099 to \
  -0.03, 48.7972 to \
  -2.15985, 48.7972 to \
  -2.15985, 90.7099 front fs empty border lc rgb '#549f' lw 0.1
set object 4188 polygon from \
  -2.12802, 90.7341 to \
  -0.03, 90.7341 to \
  -0.03, 48.8114 to \
  -2.12802, 48.8114 to \
  -2.12802, 90.7341 front fs empty border lc rgb '#549f' lw 0.1
set object 4189 polygon from \
  -2.09551, 90.7583 to \
  -0.03, 90.7583 to \
  -0.03, 48.8256 to \
  -2.09551, 48.8256 to \
  -2.09551, 90.7583 front fs empty border lc rgb '#549f' lw 0.1
set object 4190 polygon from \
  -2.06235, 90.7826 to \
  -0.03, 90.7826 to \
  -0.03, 48.8399 to \
  -2.06235, 48.8399 to \
  -2.06235, 90.7826 front fs empty border lc rgb '#549f' lw 0.1
set object 4191 polygon from \
  -2.02855, 90.8068 to \
  -0.03, 90.8068 to \
  -0.03, 48.8541 to \
  -2.02855, 48.8541 to \
  -2.02855, 90.8068 front fs empty border lc rgb '#549f' lw 0.1
set object 4192 polygon from \
  -1.99414, 90.831 to \
  -0.03, 90.831 to \
  -0.03, 48.8683 to \
  -1.99414, 48.8683 to \
  -1.99414, 90.831 front fs empty border lc rgb '#549f' lw 0.1
set object 4193 polygon from \
  -1.97102, 90.8553 to \
  -0.03, 90.8553 to \
  -0.03, 48.8826 to \
  -1.97102, 48.8826 to \
  -1.97102, 90.8553 front fs empty border lc rgb '#549f' lw 0.1
set object 4194 polygon from \
  -1.97321, 90.8795 to \
  -0.03, 90.8795 to \
  -0.03, 48.8968 to \
  -1.97321, 48.8968 to \
  -1.97321, 90.8795 front fs empty border lc rgb '#549f' lw 0.1
set object 4195 polygon from \
  -1.97495, 90.9038 to \
  -0.03, 90.9038 to \
  -0.03, 48.911 to \
  -1.97495, 48.911 to \
  -1.97495, 90.9038 front fs empty border lc rgb '#549f' lw 0.1
set object 4196 polygon from \
  -1.97623, 90.928 to \
  -0.03, 90.928 to \
  -0.03, 48.9253 to \
  -1.97623, 48.9253 to \
  -1.97623, 90.928 front fs empty border lc rgb '#549f' lw 0.1
set object 4197 polygon from \
  -1.97703, 90.9523 to \
  -0.03, 90.9523 to \
  -0.03, 48.9395 to \
  -1.97703, 48.9395 to \
  -1.97703, 90.9523 front fs empty border lc rgb '#549f' lw 0.1
set object 4198 polygon from \
  -1.97735, 90.9765 to \
  -0.03, 90.9765 to \
  -0.03, 48.9538 to \
  -1.97735, 48.9538 to \
  -1.97735, 90.9765 front fs empty border lc rgb '#549f' lw 0.1
set object 4199 polygon from \
  -1.97735, 91.0008 to \
  -0.03, 91.0008 to \
  -0.03, 48.968 to \
  -1.97735, 48.968 to \
  -1.97735, 91.0008 front fs empty border lc rgb '#549f' lw 0.1
set object 4200 polygon from \
  -1.97718, 91.025 to \
  -0.03, 91.025 to \
  -0.03, 48.9823 to \
  -1.97718, 48.9823 to \
  -1.97718, 91.025 front fs empty border lc rgb '#549f' lw 0.1
set object 4201 polygon from \
  -1.9765, 91.0493 to \
  -0.03, 91.0493 to \
  -0.03, 48.9965 to \
  -1.9765, 48.9965 to \
  -1.9765, 91.0493 front fs empty border lc rgb '#549f' lw 0.1
set object 4202 polygon from \
  -1.97531, 91.0735 to \
  -0.03, 91.0735 to \
  -0.03, 49.0107 to \
  -1.97531, 49.0107 to \
  -1.97531, 91.0735 front fs empty border lc rgb '#549f' lw 0.1
set object 4203 polygon from \
  -1.9736, 91.0978 to \
  -0.03, 91.0978 to \
  -0.03, 49.025 to \
  -1.9736, 49.025 to \
  -1.9736, 91.0978 front fs empty border lc rgb '#549f' lw 0.1
set object 4204 polygon from \
  -1.97136, 91.122 to \
  -0.03, 91.122 to \
  -0.03, 49.0392 to \
  -1.97136, 49.0392 to \
  -1.97136, 91.122 front fs empty border lc rgb '#549f' lw 0.1
set object 4205 polygon from \
  -1.96858, 91.1463 to \
  -0.03, 91.1463 to \
  -0.03, 49.0535 to \
  -1.96858, 49.0535 to \
  -1.96858, 91.1463 front fs empty border lc rgb '#549f' lw 0.1
set object 4206 polygon from \
  -1.96525, 91.1705 to \
  -0.03, 91.1705 to \
  -0.03, 49.0678 to \
  -1.96525, 49.0678 to \
  -1.96525, 91.1705 front fs empty border lc rgb '#549f' lw 0.1
set object 4207 polygon from \
  -1.96136, 91.1948 to \
  -0.03, 91.1948 to \
  -0.03, 49.082 to \
  -1.96136, 49.082 to \
  -1.96136, 91.1948 front fs empty border lc rgb '#549f' lw 0.1
set object 4208 polygon from \
  -1.95691, 91.219 to \
  -0.03, 91.219 to \
  -0.03, 49.0963 to \
  -1.95691, 49.0963 to \
  -1.95691, 91.219 front fs empty border lc rgb '#549f' lw 0.1
set object 4209 polygon from \
  -1.95188, 91.2433 to \
  -0.03, 91.2433 to \
  -0.03, 49.1105 to \
  -1.95188, 49.1105 to \
  -1.95188, 91.2433 front fs empty border lc rgb '#549f' lw 0.1
set object 4210 polygon from \
  -1.94626, 91.2676 to \
  -0.03, 91.2676 to \
  -0.03, 49.1248 to \
  -1.94626, 49.1248 to \
  -1.94626, 91.2676 front fs empty border lc rgb '#549f' lw 0.1
set object 4211 polygon from \
  -1.94006, 91.2918 to \
  -0.03, 91.2918 to \
  -0.03, 49.139 to \
  -1.94006, 49.139 to \
  -1.94006, 91.2918 front fs empty border lc rgb '#549f' lw 0.1
set object 4212 polygon from \
  -1.93326, 91.3161 to \
  -0.03, 91.3161 to \
  -0.03, 49.1533 to \
  -1.93326, 49.1533 to \
  -1.93326, 91.3161 front fs empty border lc rgb '#549f' lw 0.1
set object 4213 polygon from \
  -1.92585, 91.3404 to \
  -0.03, 91.3404 to \
  -0.03, 49.1676 to \
  -1.92585, 49.1676 to \
  -1.92585, 91.3404 front fs empty border lc rgb '#549f' lw 0.1
set object 4214 polygon from \
  -1.91783, 91.3646 to \
  -0.03, 91.3646 to \
  -0.03, 49.1818 to \
  -1.91783, 49.1818 to \
  -1.91783, 91.3646 front fs empty border lc rgb '#549f' lw 0.1
set object 4215 polygon from \
  -1.90919, 91.3889 to \
  -0.03, 91.3889 to \
  -0.03, 49.1961 to \
  -1.90919, 49.1961 to \
  -1.90919, 91.3889 front fs empty border lc rgb '#549f' lw 0.1
set object 4216 polygon from \
  -1.89992, 91.4132 to \
  -0.03, 91.4132 to \
  -0.03, 49.2104 to \
  -1.89992, 49.2104 to \
  -1.89992, 91.4132 front fs empty border lc rgb '#549f' lw 0.1
set object 4217 polygon from \
  -1.89002, 91.4374 to \
  -0.03, 91.4374 to \
  -0.03, 49.2246 to \
  -1.89002, 49.2246 to \
  -1.89002, 91.4374 front fs empty border lc rgb '#549f' lw 0.1
set object 4218 polygon from \
  -1.87948, 91.4617 to \
  -0.03, 91.4617 to \
  -0.03, 49.2389 to \
  -1.87948, 49.2389 to \
  -1.87948, 91.4617 front fs empty border lc rgb '#549f' lw 0.1
set object 4219 polygon from \
  -1.86829, 91.486 to \
  -0.03, 91.486 to \
  -0.03, 49.2532 to \
  -1.86829, 49.2532 to \
  -1.86829, 91.486 front fs empty border lc rgb '#549f' lw 0.1
set object 4220 polygon from \
  -1.85646, 91.5103 to \
  -0.03, 91.5103 to \
  -0.03, 49.2674 to \
  -1.85646, 49.2674 to \
  -1.85646, 91.5103 front fs empty border lc rgb '#549f' lw 0.1
set object 4221 polygon from \
  -1.84397, 91.5345 to \
  -0.03, 91.5345 to \
  -0.03, 49.2817 to \
  -1.84397, 49.2817 to \
  -1.84397, 91.5345 front fs empty border lc rgb '#549f' lw 0.1
set object 4222 polygon from \
  -1.83082, 91.5588 to \
  -0.03, 91.5588 to \
  -0.03, 49.296 to \
  -1.83082, 49.296 to \
  -1.83082, 91.5588 front fs empty border lc rgb '#549f' lw 0.1
set object 4223 polygon from \
  -1.817, 91.5831 to \
  -0.03, 91.5831 to \
  -0.03, 49.3102 to \
  -1.817, 49.3102 to \
  -1.817, 91.5831 front fs empty border lc rgb '#549f' lw 0.1
set object 4224 polygon from \
  -1.80252, 91.6074 to \
  -0.03, 91.6074 to \
  -0.03, 49.3245 to \
  -1.80252, 49.3245 to \
  -1.80252, 91.6074 front fs empty border lc rgb '#549f' lw 0.1
set object 4225 polygon from \
  -1.78736, 91.6316 to \
  -0.03, 91.6316 to \
  -0.03, 49.3388 to \
  -1.78736, 49.3388 to \
  -1.78736, 91.6316 front fs empty border lc rgb '#549f' lw 0.1
set object 4226 polygon from \
  -1.77342, 91.6559 to \
  -0.03, 91.6559 to \
  -0.03, 49.3531 to \
  -1.77342, 49.3531 to \
  -1.77342, 91.6559 front fs empty border lc rgb '#549f' lw 0.1
set object 4227 polygon from \
  -1.75987, 91.6802 to \
  -0.03, 91.6802 to \
  -0.03, 49.3674 to \
  -1.75987, 49.3674 to \
  -1.75987, 91.6802 front fs empty border lc rgb '#549f' lw 0.1
set object 4228 polygon from \
  -1.77966, 91.7045 to \
  -0.03, 91.7045 to \
  -0.03, 49.3816 to \
  -1.77966, 49.3816 to \
  -1.77966, 91.7045 front fs empty border lc rgb '#549f' lw 0.1
set object 4229 polygon from \
  -1.80818, 91.7288 to \
  -0.03, 91.7288 to \
  -0.03, 49.3959 to \
  -1.80818, 49.3959 to \
  -1.80818, 91.7288 front fs empty border lc rgb '#549f' lw 0.1
set object 4230 polygon from \
  -1.83671, 91.7531 to \
  -0.03, 91.7531 to \
  -0.03, 49.4102 to \
  -1.83671, 49.4102 to \
  -1.83671, 91.7531 front fs empty border lc rgb '#549f' lw 0.1
set object 4231 polygon from \
  -1.86424, 91.7774 to \
  -0.03, 91.7774 to \
  -0.03, 49.4245 to \
  -1.86424, 49.4245 to \
  -1.86424, 91.7774 front fs empty border lc rgb '#549f' lw 0.1
set object 4232 polygon from \
  -1.89076, 91.8016 to \
  -0.03, 91.8016 to \
  -0.03, 49.4388 to \
  -1.89076, 49.4388 to \
  -1.89076, 91.8016 front fs empty border lc rgb '#549f' lw 0.1
set object 4233 polygon from \
  -1.91623, 91.8259 to \
  -0.03, 91.8259 to \
  -0.03, 49.4531 to \
  -1.91623, 49.4531 to \
  -1.91623, 91.8259 front fs empty border lc rgb '#549f' lw 0.1
set object 4234 polygon from \
  -1.94064, 91.8502 to \
  -0.03, 91.8502 to \
  -0.03, 49.4673 to \
  -1.94064, 49.4673 to \
  -1.94064, 91.8502 front fs empty border lc rgb '#549f' lw 0.1
set object 4235 polygon from \
  -1.96398, 91.8745 to \
  -0.03, 91.8745 to \
  -0.03, 49.4816 to \
  -1.96398, 49.4816 to \
  -1.96398, 91.8745 front fs empty border lc rgb '#549f' lw 0.1
set object 4236 polygon from \
  -1.98622, 91.8988 to \
  -0.03, 91.8988 to \
  -0.03, 49.4959 to \
  -1.98622, 49.4959 to \
  -1.98622, 91.8988 front fs empty border lc rgb '#549f' lw 0.1
set object 4237 polygon from \
  -2.00734, 91.9231 to \
  -0.03, 91.9231 to \
  -0.03, 49.5102 to \
  -2.00734, 49.5102 to \
  -2.00734, 91.9231 front fs empty border lc rgb '#549f' lw 0.1
set object 4238 polygon from \
  -2.02734, 91.9474 to \
  -0.03, 91.9474 to \
  -0.03, 49.5245 to \
  -2.02734, 49.5245 to \
  -2.02734, 91.9474 front fs empty border lc rgb '#549f' lw 0.1
set object 4239 polygon from \
  -2.04618, 91.9717 to \
  -0.03, 91.9717 to \
  -0.03, 49.5388 to \
  -2.04618, 49.5388 to \
  -2.04618, 91.9717 front fs empty border lc rgb '#549f' lw 0.1
set object 4240 polygon from \
  -2.06387, 91.996 to \
  -0.03, 91.996 to \
  -0.03, 49.5531 to \
  -2.06387, 49.5531 to \
  -2.06387, 91.996 front fs empty border lc rgb '#549f' lw 0.1
set object 4241 polygon from \
  -2.08037, 92.0203 to \
  -0.03, 92.0203 to \
  -0.03, 49.5674 to \
  -2.08037, 49.5674 to \
  -2.08037, 92.0203 front fs empty border lc rgb '#549f' lw 0.1
set object 4242 polygon from \
  -2.09568, 92.0446 to \
  -0.03, 92.0446 to \
  -0.03, 49.5817 to \
  -2.09568, 49.5817 to \
  -2.09568, 92.0446 front fs empty border lc rgb '#549f' lw 0.1
set object 4243 polygon from \
  -2.10979, 92.0689 to \
  -0.03, 92.0689 to \
  -0.03, 49.596 to \
  -2.10979, 49.596 to \
  -2.10979, 92.0689 front fs empty border lc rgb '#549f' lw 0.1
set object 4244 polygon from \
  -2.12268, 92.0932 to \
  -0.03, 92.0932 to \
  -0.03, 49.6103 to \
  -2.12268, 49.6103 to \
  -2.12268, 92.0932 front fs empty border lc rgb '#549f' lw 0.1
set object 4245 polygon from \
  -2.13434, 92.1175 to \
  -0.03, 92.1175 to \
  -0.03, 49.6246 to \
  -2.13434, 49.6246 to \
  -2.13434, 92.1175 front fs empty border lc rgb '#549f' lw 0.1
set object 4246 polygon from \
  -2.14476, 92.1418 to \
  -0.03, 92.1418 to \
  -0.03, 49.6389 to \
  -2.14476, 49.6389 to \
  -2.14476, 92.1418 front fs empty border lc rgb '#549f' lw 0.1
set object 4247 polygon from \
  -2.15393, 92.1661 to \
  -0.03, 92.1661 to \
  -0.03, 49.6532 to \
  -2.15393, 49.6532 to \
  -2.15393, 92.1661 front fs empty border lc rgb '#549f' lw 0.1
set object 4248 polygon from \
  -2.16184, 92.1904 to \
  -0.03, 92.1904 to \
  -0.03, 49.6675 to \
  -2.16184, 49.6675 to \
  -2.16184, 92.1904 front fs empty border lc rgb '#549f' lw 0.1
set object 4249 polygon from \
  -2.16848, 92.2148 to \
  -0.03, 92.2148 to \
  -0.03, 49.6818 to \
  -2.16848, 49.6818 to \
  -2.16848, 92.2148 front fs empty border lc rgb '#549f' lw 0.1
set object 4250 polygon from \
  -2.17385, 92.2391 to \
  -0.03, 92.2391 to \
  -0.03, 49.6961 to \
  -2.17385, 49.6961 to \
  -2.17385, 92.2391 front fs empty border lc rgb '#549f' lw 0.1
set object 4251 polygon from \
  -2.17793, 92.2634 to \
  -0.03, 92.2634 to \
  -0.03, 49.7104 to \
  -2.17793, 49.7104 to \
  -2.17793, 92.2634 front fs empty border lc rgb '#549f' lw 0.1
set object 4252 polygon from \
  -2.18073, 92.2877 to \
  -0.03, 92.2877 to \
  -0.03, 49.7247 to \
  -2.18073, 49.7247 to \
  -2.18073, 92.2877 front fs empty border lc rgb '#549f' lw 0.1
set object 4253 polygon from \
  -2.18224, 92.312 to \
  -0.03, 92.312 to \
  -0.03, 49.7391 to \
  -2.18224, 49.7391 to \
  -2.18224, 92.312 front fs empty border lc rgb '#549f' lw 0.1
set object 4254 polygon from \
  -2.18245, 92.3363 to \
  -0.03, 92.3363 to \
  -0.03, 49.7534 to \
  -2.18245, 49.7534 to \
  -2.18245, 92.3363 front fs empty border lc rgb '#549f' lw 0.1
set object 4255 polygon from \
  -2.18245, 92.3606 to \
  -0.03, 92.3606 to \
  -0.03, 49.7677 to \
  -2.18245, 49.7677 to \
  -2.18245, 92.3606 front fs empty border lc rgb '#549f' lw 0.1
set object 4256 polygon from \
  -2.18136, 92.385 to \
  -0.03, 92.385 to \
  -0.03, 49.782 to \
  -2.18136, 49.782 to \
  -2.18136, 92.385 front fs empty border lc rgb '#549f' lw 0.1
set object 4257 polygon from \
  -2.17898, 92.4093 to \
  -0.03, 92.4093 to \
  -0.03, 49.7963 to \
  -2.17898, 49.7963 to \
  -2.17898, 92.4093 front fs empty border lc rgb '#549f' lw 0.1
set object 4258 polygon from \
  -2.17528, 92.4336 to \
  -0.03, 92.4336 to \
  -0.03, 49.8106 to \
  -2.17528, 49.8106 to \
  -2.17528, 92.4336 front fs empty border lc rgb '#549f' lw 0.1
set object 4259 polygon from \
  -2.17029, 92.4579 to \
  -0.03, 92.4579 to \
  -0.03, 49.825 to \
  -2.17029, 49.825 to \
  -2.17029, 92.4579 front fs empty border lc rgb '#549f' lw 0.1
set object 4260 polygon from \
  -2.16399, 92.4823 to \
  -0.03, 92.4823 to \
  -0.03, 49.8393 to \
  -2.16399, 49.8393 to \
  -2.16399, 92.4823 front fs empty border lc rgb '#549f' lw 0.1
set object 4261 polygon from \
  -2.15639, 92.5066 to \
  -0.03, 92.5066 to \
  -0.03, 49.8536 to \
  -2.15639, 49.8536 to \
  -2.15639, 92.5066 front fs empty border lc rgb '#549f' lw 0.1
set object 4262 polygon from \
  -2.14749, 92.5309 to \
  -0.03, 92.5309 to \
  -0.03, 49.8679 to \
  -2.14749, 49.8679 to \
  -2.14749, 92.5309 front fs empty border lc rgb '#549f' lw 0.1
set object 4263 polygon from \
  -2.13729, 92.5552 to \
  -0.03, 92.5552 to \
  -0.03, 49.8822 to \
  -2.13729, 49.8822 to \
  -2.13729, 92.5552 front fs empty border lc rgb '#549f' lw 0.1
set object 4264 polygon from \
  -2.12581, 92.5796 to \
  -0.03, 92.5796 to \
  -0.03, 49.8966 to \
  -2.12581, 49.8966 to \
  -2.12581, 92.5796 front fs empty border lc rgb '#549f' lw 0.1
set object 4265 polygon from \
  -2.11303, 92.6039 to \
  -0.03, 92.6039 to \
  -0.03, 49.9109 to \
  -2.11303, 49.9109 to \
  -2.11303, 92.6039 front fs empty border lc rgb '#549f' lw 0.1
set object 4266 polygon from \
  -2.09897, 92.6282 to \
  -0.03, 92.6282 to \
  -0.03, 49.9252 to \
  -2.09897, 49.9252 to \
  -2.09897, 92.6282 front fs empty border lc rgb '#549f' lw 0.1
set object 4267 polygon from \
  -2.08364, 92.6526 to \
  -0.03, 92.6526 to \
  -0.03, 49.9396 to \
  -2.08364, 49.9396 to \
  -2.08364, 92.6526 front fs empty border lc rgb '#549f' lw 0.1
set object 4268 polygon from \
  -2.06704, 92.6769 to \
  -0.03, 92.6769 to \
  -0.03, 49.9539 to \
  -2.06704, 49.9539 to \
  -2.06704, 92.6769 front fs empty border lc rgb '#549f' lw 0.1
set object 4269 polygon from \
  -2.04918, 92.7012 to \
  -0.03, 92.7012 to \
  -0.03, 49.9682 to \
  -2.04918, 49.9682 to \
  -2.04918, 92.7012 front fs empty border lc rgb '#549f' lw 0.1
set object 4270 polygon from \
  -2.03271, 92.7256 to \
  -0.03, 92.7256 to \
  -0.03, 49.9826 to \
  -2.03271, 49.9826 to \
  -2.03271, 92.7256 front fs empty border lc rgb '#549f' lw 0.1
set object 4271 polygon from \
  -2.04955, 92.7499 to \
  -0.03, 92.7499 to \
  -0.03, 49.9969 to \
  -2.04955, 49.9969 to \
  -2.04955, 92.7499 front fs empty border lc rgb '#549f' lw 0.1
set object 4272 polygon from \
  -2.06549, 92.7742 to \
  -0.03, 92.7742 to \
  -0.03, 50.0112 to \
  -2.06549, 50.0112 to \
  -2.06549, 92.7742 front fs empty border lc rgb '#549f' lw 0.1
set object 4273 polygon from \
  -2.08054, 92.7986 to \
  -0.03, 92.7986 to \
  -0.03, 50.0256 to \
  -2.08054, 50.0256 to \
  -2.08054, 92.7986 front fs empty border lc rgb '#549f' lw 0.1
set object 4274 polygon from \
  -2.0947, 92.8229 to \
  -0.03, 92.8229 to \
  -0.03, 50.0399 to \
  -2.0947, 50.0399 to \
  -2.0947, 92.8229 front fs empty border lc rgb '#549f' lw 0.1
set object 4275 polygon from \
  -2.10796, 92.8473 to \
  -0.03, 92.8473 to \
  -0.03, 50.0542 to \
  -2.10796, 50.0542 to \
  -2.10796, 92.8473 front fs empty border lc rgb '#549f' lw 0.1
set object 4276 polygon from \
  -2.12034, 92.8716 to \
  -0.03, 92.8716 to \
  -0.03, 50.0686 to \
  -2.12034, 50.0686 to \
  -2.12034, 92.8716 front fs empty border lc rgb '#549f' lw 0.1
set object 4277 polygon from \
  -2.13182, 92.896 to \
  -0.03, 92.896 to \
  -0.03, 50.0829 to \
  -2.13182, 50.0829 to \
  -2.13182, 92.896 front fs empty border lc rgb '#549f' lw 0.1
set object 4278 polygon from \
  -2.14242, 92.9203 to \
  -0.03, 92.9203 to \
  -0.03, 50.0973 to \
  -2.14242, 50.0973 to \
  -2.14242, 92.9203 front fs empty border lc rgb '#549f' lw 0.1
set object 4279 polygon from \
  -2.15214, 92.9447 to \
  -0.03, 92.9447 to \
  -0.03, 50.1116 to \
  -2.15214, 50.1116 to \
  -2.15214, 92.9447 front fs empty border lc rgb '#549f' lw 0.1
set object 4280 polygon from \
  -2.16097, 92.969 to \
  -0.03, 92.969 to \
  -0.03, 50.126 to \
  -2.16097, 50.126 to \
  -2.16097, 92.969 front fs empty border lc rgb '#549f' lw 0.1
set object 4281 polygon from \
  -2.16893, 92.9934 to \
  -0.03, 92.9934 to \
  -0.03, 50.1403 to \
  -2.16893, 50.1403 to \
  -2.16893, 92.9934 front fs empty border lc rgb '#549f' lw 0.1
set object 4282 polygon from \
  -2.17602, 93.0177 to \
  -0.03, 93.0177 to \
  -0.03, 50.1546 to \
  -2.17602, 50.1546 to \
  -2.17602, 93.0177 front fs empty border lc rgb '#549f' lw 0.1
set object 4283 polygon from \
  -2.18224, 93.0421 to \
  -0.03, 93.0421 to \
  -0.03, 50.169 to \
  -2.18224, 50.169 to \
  -2.18224, 93.0421 front fs empty border lc rgb '#549f' lw 0.1
set object 4284 polygon from \
  -2.18761, 93.0664 to \
  -0.03, 93.0664 to \
  -0.03, 50.1833 to \
  -2.18761, 50.1833 to \
  -2.18761, 93.0664 front fs empty border lc rgb '#549f' lw 0.1
set object 4285 polygon from \
  -2.19211, 93.0908 to \
  -0.03, 93.0908 to \
  -0.03, 50.1977 to \
  -2.19211, 50.1977 to \
  -2.19211, 93.0908 front fs empty border lc rgb '#549f' lw 0.1
set object 4286 polygon from \
  -2.19577, 93.1151 to \
  -0.03, 93.1151 to \
  -0.03, 50.2121 to \
  -2.19577, 50.2121 to \
  -2.19577, 93.1151 front fs empty border lc rgb '#549f' lw 0.1
set object 4287 polygon from \
  -2.19859, 93.1395 to \
  -0.03, 93.1395 to \
  -0.03, 50.2264 to \
  -2.19859, 50.2264 to \
  -2.19859, 93.1395 front fs empty border lc rgb '#549f' lw 0.1
set object 4288 polygon from \
  -2.20057, 93.1638 to \
  -0.03, 93.1638 to \
  -0.03, 50.2408 to \
  -2.20057, 50.2408 to \
  -2.20057, 93.1638 front fs empty border lc rgb '#549f' lw 0.1
set object 4289 polygon from \
  -2.20172, 93.1882 to \
  -0.03, 93.1882 to \
  -0.03, 50.2551 to \
  -2.20172, 50.2551 to \
  -2.20172, 93.1882 front fs empty border lc rgb '#549f' lw 0.1
set object 4290 polygon from \
  -2.20206, 93.2126 to \
  -0.03, 93.2126 to \
  -0.03, 50.2695 to \
  -2.20206, 50.2695 to \
  -2.20206, 93.2126 front fs empty border lc rgb '#549f' lw 0.1
set object 4291 polygon from \
  -2.20205, 93.2369 to \
  -0.03, 93.2369 to \
  -0.03, 50.2838 to \
  -2.20205, 50.2838 to \
  -2.20205, 93.2369 front fs empty border lc rgb '#549f' lw 0.1
set object 4292 polygon from \
  -2.20158, 93.2613 to \
  -0.03, 93.2613 to \
  -0.03, 50.2982 to \
  -2.20158, 50.2982 to \
  -2.20158, 93.2613 front fs empty border lc rgb '#549f' lw 0.1
set object 4293 polygon from \
  -2.2003, 93.2857 to \
  -0.03, 93.2857 to \
  -0.03, 50.3126 to \
  -2.2003, 50.3126 to \
  -2.2003, 93.2857 front fs empty border lc rgb '#549f' lw 0.1
set object 4294 polygon from \
  -2.19823, 93.31 to \
  -0.03, 93.31 to \
  -0.03, 50.3269 to \
  -2.19823, 50.3269 to \
  -2.19823, 93.31 front fs empty border lc rgb '#549f' lw 0.1
set object 4295 polygon from \
  -2.19538, 93.3344 to \
  -0.03, 93.3344 to \
  -0.03, 50.3413 to \
  -2.19538, 50.3413 to \
  -2.19538, 93.3344 front fs empty border lc rgb '#549f' lw 0.1
set object 4296 polygon from \
  -2.19175, 93.3588 to \
  -0.03, 93.3588 to \
  -0.03, 50.3557 to \
  -2.19175, 50.3557 to \
  -2.19175, 93.3588 front fs empty border lc rgb '#549f' lw 0.1
set object 4297 polygon from \
  -2.18736, 93.3831 to \
  -0.03, 93.3831 to \
  -0.03, 50.37 to \
  -2.18736, 50.37 to \
  -2.18736, 93.3831 front fs empty border lc rgb '#549f' lw 0.1
set object 4298 polygon from \
  -2.18222, 93.4075 to \
  -0.03, 93.4075 to \
  -0.03, 50.3844 to \
  -2.18222, 50.3844 to \
  -2.18222, 93.4075 front fs empty border lc rgb '#549f' lw 0.1
set object 4299 polygon from \
  -2.17634, 93.4319 to \
  -0.03, 93.4319 to \
  -0.03, 50.3988 to \
  -2.17634, 50.3988 to \
  -2.17634, 93.4319 front fs empty border lc rgb '#549f' lw 0.1
set object 4300 polygon from \
  -2.16973, 93.4563 to \
  -0.03, 93.4563 to \
  -0.03, 50.4131 to \
  -2.16973, 50.4131 to \
  -2.16973, 93.4563 front fs empty border lc rgb '#549f' lw 0.1
set object 4301 polygon from \
  -2.1624, 93.4806 to \
  -0.03, 93.4806 to \
  -0.03, 50.4275 to \
  -2.1624, 50.4275 to \
  -2.1624, 93.4806 front fs empty border lc rgb '#549f' lw 0.1
set object 4302 polygon from \
  -2.15437, 93.505 to \
  -0.03, 93.505 to \
  -0.03, 50.4419 to \
  -2.15437, 50.4419 to \
  -2.15437, 93.505 front fs empty border lc rgb '#549f' lw 0.1
set object 4303 polygon from \
  -2.14564, 93.5294 to \
  -0.03, 93.5294 to \
  -0.03, 50.4562 to \
  -2.14564, 50.4562 to \
  -2.14564, 93.5294 front fs empty border lc rgb '#549f' lw 0.1
set object 4304 polygon from \
  -2.13623, 93.5538 to \
  -0.03, 93.5538 to \
  -0.03, 50.4706 to \
  -2.13623, 50.4706 to \
  -2.13623, 93.5538 front fs empty border lc rgb '#549f' lw 0.1
set object 4305 polygon from \
  -2.12616, 93.5781 to \
  -0.03, 93.5781 to \
  -0.03, 50.485 to \
  -2.12616, 50.485 to \
  -2.12616, 93.5781 front fs empty border lc rgb '#549f' lw 0.1
set object 4306 polygon from \
  -2.11543, 93.6025 to \
  -0.03, 93.6025 to \
  -0.03, 50.4994 to \
  -2.11543, 50.4994 to \
  -2.11543, 93.6025 front fs empty border lc rgb '#549f' lw 0.1
set object 4307 polygon from \
  -2.10406, 93.6269 to \
  -0.03, 93.6269 to \
  -0.03, 50.5138 to \
  -2.10406, 50.5138 to \
  -2.10406, 93.6269 front fs empty border lc rgb '#549f' lw 0.1
set object 4308 polygon from \
  -2.0948, 93.6513 to \
  -0.03, 93.6513 to \
  -0.03, 50.5281 to \
  -2.0948, 50.5281 to \
  -2.0948, 93.6513 front fs empty border lc rgb '#549f' lw 0.1
set object 4309 polygon from \
  -2.12801, 93.6757 to \
  -0.03, 93.6757 to \
  -0.03, 50.5425 to \
  -2.12801, 50.5425 to \
  -2.12801, 93.6757 front fs empty border lc rgb '#549f' lw 0.1
set object 4310 polygon from \
  -2.16078, 93.7001 to \
  -0.03, 93.7001 to \
  -0.03, 50.5569 to \
  -2.16078, 50.5569 to \
  -2.16078, 93.7001 front fs empty border lc rgb '#549f' lw 0.1
set object 4311 polygon from \
  -2.19309, 93.7245 to \
  -0.03, 93.7245 to \
  -0.03, 50.5713 to \
  -2.19309, 50.5713 to \
  -2.19309, 93.7245 front fs empty border lc rgb '#549f' lw 0.1
set object 4312 polygon from \
  -2.22491, 93.7488 to \
  -0.03, 93.7488 to \
  -0.03, 50.5857 to \
  -2.22491, 50.5857 to \
  -2.22491, 93.7488 front fs empty border lc rgb '#549f' lw 0.1
set object 4313 polygon from \
  -2.25623, 93.7732 to \
  -0.03, 93.7732 to \
  -0.03, 50.6001 to \
  -2.25623, 50.6001 to \
  -2.25623, 93.7732 front fs empty border lc rgb '#549f' lw 0.1
set object 4314 polygon from \
  -2.28703, 93.7976 to \
  -0.03, 93.7976 to \
  -0.03, 50.6144 to \
  -2.28703, 50.6144 to \
  -2.28703, 93.7976 front fs empty border lc rgb '#549f' lw 0.1
set object 4315 polygon from \
  -2.31729, 93.822 to \
  -0.03, 93.822 to \
  -0.03, 50.6288 to \
  -2.31729, 50.6288 to \
  -2.31729, 93.822 front fs empty border lc rgb '#549f' lw 0.1
set object 4316 polygon from \
  -2.34701, 93.8464 to \
  -0.03, 93.8464 to \
  -0.03, 50.6432 to \
  -2.34701, 50.6432 to \
  -2.34701, 93.8464 front fs empty border lc rgb '#549f' lw 0.1
set object 4317 polygon from \
  -2.37616, 93.8708 to \
  -0.03, 93.8708 to \
  -0.03, 50.6576 to \
  -2.37616, 50.6576 to \
  -2.37616, 93.8708 front fs empty border lc rgb '#549f' lw 0.1
set object 4318 polygon from \
  -2.40472, 93.8952 to \
  -0.03, 93.8952 to \
  -0.03, 50.672 to \
  -2.40472, 50.672 to \
  -2.40472, 93.8952 front fs empty border lc rgb '#549f' lw 0.1
set object 4319 polygon from \
  -2.43268, 93.9196 to \
  -0.03, 93.9196 to \
  -0.03, 50.6864 to \
  -2.43268, 50.6864 to \
  -2.43268, 93.9196 front fs empty border lc rgb '#549f' lw 0.1
set object 4320 polygon from \
  -2.46003, 93.944 to \
  -0.03, 93.944 to \
  -0.03, 50.7008 to \
  -2.46003, 50.7008 to \
  -2.46003, 93.944 front fs empty border lc rgb '#549f' lw 0.1
set object 4321 polygon from \
  -2.48674, 93.9684 to \
  -0.03, 93.9684 to \
  -0.03, 50.7152 to \
  -2.48674, 50.7152 to \
  -2.48674, 93.9684 front fs empty border lc rgb '#549f' lw 0.1
set object 4322 polygon from \
  -2.51281, 93.9928 to \
  -0.03, 93.9928 to \
  -0.03, 50.7296 to \
  -2.51281, 50.7296 to \
  -2.51281, 93.9928 front fs empty border lc rgb '#549f' lw 0.1
set object 4323 polygon from \
  -2.53822, 94.0172 to \
  -0.03, 94.0172 to \
  -0.03, 50.744 to \
  -2.53822, 50.744 to \
  -2.53822, 94.0172 front fs empty border lc rgb '#549f' lw 0.1
set object 4324 polygon from \
  -2.56295, 94.0416 to \
  -0.03, 94.0416 to \
  -0.03, 50.7584 to \
  -2.56295, 50.7584 to \
  -2.56295, 94.0416 front fs empty border lc rgb '#549f' lw 0.1
set object 4325 polygon from \
  -2.58699, 94.066 to \
  -0.03, 94.066 to \
  -0.03, 50.7728 to \
  -2.58699, 50.7728 to \
  -2.58699, 94.066 front fs empty border lc rgb '#549f' lw 0.1
set object 4326 polygon from \
  -2.61032, 94.0904 to \
  -0.03, 94.0904 to \
  -0.03, 50.7872 to \
  -2.61032, 50.7872 to \
  -2.61032, 94.0904 front fs empty border lc rgb '#549f' lw 0.1
set object 4327 polygon from \
  -2.63293, 94.1148 to \
  -0.03, 94.1148 to \
  -0.03, 50.8016 to \
  -2.63293, 50.8016 to \
  -2.63293, 94.1148 front fs empty border lc rgb '#549f' lw 0.1
set object 4328 polygon from \
  -2.6548, 94.1392 to \
  -0.03, 94.1392 to \
  -0.03, 50.816 to \
  -2.6548, 50.816 to \
  -2.6548, 94.1392 front fs empty border lc rgb '#549f' lw 0.1
set object 4329 polygon from \
  -2.67592, 94.1637 to \
  -0.03, 94.1637 to \
  -0.03, 50.8304 to \
  -2.67592, 50.8304 to \
  -2.67592, 94.1637 front fs empty border lc rgb '#549f' lw 0.1
set object 4330 polygon from \
  -2.69629, 94.1881 to \
  -0.03, 94.1881 to \
  -0.03, 50.8448 to \
  -2.69629, 50.8448 to \
  -2.69629, 94.1881 front fs empty border lc rgb '#549f' lw 0.1
set object 4331 polygon from \
  -2.71587, 94.2125 to \
  -0.03, 94.2125 to \
  -0.03, 50.8592 to \
  -2.71587, 50.8592 to \
  -2.71587, 94.2125 front fs empty border lc rgb '#549f' lw 0.1
set object 4332 polygon from \
  -2.73467, 94.2369 to \
  -0.03, 94.2369 to \
  -0.03, 50.8736 to \
  -2.73467, 50.8736 to \
  -2.73467, 94.2369 front fs empty border lc rgb '#549f' lw 0.1
set object 4333 polygon from \
  -2.75266, 94.2613 to \
  -0.03, 94.2613 to \
  -0.03, 50.8881 to \
  -2.75266, 50.8881 to \
  -2.75266, 94.2613 front fs empty border lc rgb '#549f' lw 0.1
set object 4334 polygon from \
  -2.76984, 94.2857 to \
  -0.03, 94.2857 to \
  -0.03, 50.9025 to \
  -2.76984, 50.9025 to \
  -2.76984, 94.2857 front fs empty border lc rgb '#549f' lw 0.1
set object 4335 polygon from \
  -2.7862, 94.3101 to \
  -0.03, 94.3101 to \
  -0.03, 50.9169 to \
  -2.7862, 50.9169 to \
  -2.7862, 94.3101 front fs empty border lc rgb '#549f' lw 0.1
set object 4336 polygon from \
  -2.80171, 94.3346 to \
  -0.03, 94.3346 to \
  -0.03, 50.9313 to \
  -2.80171, 50.9313 to \
  -2.80171, 94.3346 front fs empty border lc rgb '#549f' lw 0.1
set object 4337 polygon from \
  -2.81638, 94.359 to \
  -0.03, 94.359 to \
  -0.03, 50.9457 to \
  -2.81638, 50.9457 to \
  -2.81638, 94.359 front fs empty border lc rgb '#549f' lw 0.1
set object 4338 polygon from \
  -2.83019, 94.3834 to \
  -0.03, 94.3834 to \
  -0.03, 50.9601 to \
  -2.83019, 50.9601 to \
  -2.83019, 94.3834 front fs empty border lc rgb '#549f' lw 0.1
set object 4339 polygon from \
  -2.84312, 94.4078 to \
  -0.03, 94.4078 to \
  -0.03, 50.9746 to \
  -2.84312, 50.9746 to \
  -2.84312, 94.4078 front fs empty border lc rgb '#549f' lw 0.1
set object 4340 polygon from \
  -2.85517, 94.4323 to \
  -0.03, 94.4323 to \
  -0.03, 50.989 to \
  -2.85517, 50.989 to \
  -2.85517, 94.4323 front fs empty border lc rgb '#549f' lw 0.1
set object 4341 polygon from \
  -2.86633, 94.4567 to \
  -0.03, 94.4567 to \
  -0.03, 51.0034 to \
  -2.86633, 51.0034 to \
  -2.86633, 94.4567 front fs empty border lc rgb '#549f' lw 0.1
set object 4342 polygon from \
  -2.87659, 94.4811 to \
  -0.03, 94.4811 to \
  -0.03, 51.0178 to \
  -2.87659, 51.0178 to \
  -2.87659, 94.4811 front fs empty border lc rgb '#549f' lw 0.1
set object 4343 polygon from \
  -2.88594, 94.5055 to \
  -0.03, 94.5055 to \
  -0.03, 51.0322 to \
  -2.88594, 51.0322 to \
  -2.88594, 94.5055 front fs empty border lc rgb '#549f' lw 0.1
set object 4344 polygon from \
  -2.89438, 94.53 to \
  -0.03, 94.53 to \
  -0.03, 51.0467 to \
  -2.89438, 51.0467 to \
  -2.89438, 94.53 front fs empty border lc rgb '#549f' lw 0.1
set object 4345 polygon from \
  -2.90188, 94.5544 to \
  -0.03, 94.5544 to \
  -0.03, 51.0611 to \
  -2.90188, 51.0611 to \
  -2.90188, 94.5544 front fs empty border lc rgb '#549f' lw 0.1
set object 4346 polygon from \
  -2.90845, 94.5788 to \
  -0.03, 94.5788 to \
  -0.03, 51.0755 to \
  -2.90845, 51.0755 to \
  -2.90845, 94.5788 front fs empty border lc rgb '#549f' lw 0.1
set object 4347 polygon from \
  -2.91407, 94.6033 to \
  -0.03, 94.6033 to \
  -0.03, 51.09 to \
  -2.91407, 51.09 to \
  -2.91407, 94.6033 front fs empty border lc rgb '#549f' lw 0.1
set object 4348 polygon from \
  -2.91874, 94.6277 to \
  -0.03, 94.6277 to \
  -0.03, 51.1044 to \
  -2.91874, 51.1044 to \
  -2.91874, 94.6277 front fs empty border lc rgb '#549f' lw 0.1
set object 4349 polygon from \
  -2.92886, 94.6521 to \
  -0.03, 94.6521 to \
  -0.03, 51.1188 to \
  -2.92886, 51.1188 to \
  -2.92886, 94.6521 front fs empty border lc rgb '#549f' lw 0.1
set object 4350 polygon from \
  -2.94142, 94.6766 to \
  -0.03, 94.6766 to \
  -0.03, 51.1333 to \
  -2.94142, 51.1333 to \
  -2.94142, 94.6766 front fs empty border lc rgb '#549f' lw 0.1
set object 4351 polygon from \
  -2.95306, 94.701 to \
  -0.03, 94.701 to \
  -0.03, 51.1477 to \
  -2.95306, 51.1477 to \
  -2.95306, 94.701 front fs empty border lc rgb '#549f' lw 0.1
set object 4352 polygon from \
  -2.96682, 94.7254 to \
  -0.03, 94.7254 to \
  -0.03, 51.1621 to \
  -2.96682, 51.1621 to \
  -2.96682, 94.7254 front fs empty border lc rgb '#549f' lw 0.1
set object 4353 polygon from \
  -2.98169, 94.7499 to \
  -0.03, 94.7499 to \
  -0.03, 51.1766 to \
  -2.98169, 51.1766 to \
  -2.98169, 94.7499 front fs empty border lc rgb '#549f' lw 0.1
set object 4354 polygon from \
  -2.99556, 94.7743 to \
  -0.03, 94.7743 to \
  -0.03, 51.191 to \
  -2.99556, 51.191 to \
  -2.99556, 94.7743 front fs empty border lc rgb '#549f' lw 0.1
set object 4355 polygon from \
  -3.00842, 94.7988 to \
  -0.03, 94.7988 to \
  -0.03, 51.2054 to \
  -3.00842, 51.2054 to \
  -3.00842, 94.7988 front fs empty border lc rgb '#549f' lw 0.1
set object 4356 polygon from \
  -3.02026, 94.8232 to \
  -0.03, 94.8232 to \
  -0.03, 51.2199 to \
  -3.02026, 51.2199 to \
  -3.02026, 94.8232 front fs empty border lc rgb '#549f' lw 0.1
set object 4357 polygon from \
  -3.03107, 94.8477 to \
  -0.03, 94.8477 to \
  -0.03, 51.2343 to \
  -3.03107, 51.2343 to \
  -3.03107, 94.8477 front fs empty border lc rgb '#549f' lw 0.1
set object 4358 polygon from \
  -3.04086, 94.8721 to \
  -0.03, 94.8721 to \
  -0.03, 51.2488 to \
  -3.04086, 51.2488 to \
  -3.04086, 94.8721 front fs empty border lc rgb '#549f' lw 0.1
set object 4359 polygon from \
  -3.04961, 94.8966 to \
  -0.03, 94.8966 to \
  -0.03, 51.2632 to \
  -3.04961, 51.2632 to \
  -3.04961, 94.8966 front fs empty border lc rgb '#549f' lw 0.1
set object 4360 polygon from \
  -3.05732, 94.921 to \
  -0.03, 94.921 to \
  -0.03, 51.2777 to \
  -3.05732, 51.2777 to \
  -3.05732, 94.921 front fs empty border lc rgb '#549f' lw 0.1
set object 4361 polygon from \
  -3.06398, 94.9455 to \
  -0.03, 94.9455 to \
  -0.03, 51.2921 to \
  -3.06398, 51.2921 to \
  -3.06398, 94.9455 front fs empty border lc rgb '#549f' lw 0.1
set object 4362 polygon from \
  -3.0696, 94.9699 to \
  -0.03, 94.9699 to \
  -0.03, 51.3065 to \
  -3.0696, 51.3065 to \
  -3.0696, 94.9699 front fs empty border lc rgb '#549f' lw 0.1
set object 4363 polygon from \
  -3.07417, 94.9944 to \
  -0.03, 94.9944 to \
  -0.03, 51.321 to \
  -3.07417, 51.321 to \
  -3.07417, 94.9944 front fs empty border lc rgb '#549f' lw 0.1
set object 4364 polygon from \
  -3.07768, 95.0188 to \
  -0.03, 95.0188 to \
  -0.03, 51.3354 to \
  -3.07768, 51.3354 to \
  -3.07768, 95.0188 front fs empty border lc rgb '#549f' lw 0.1
set object 4365 polygon from \
  -3.08014, 95.0433 to \
  -0.03, 95.0433 to \
  -0.03, 51.3499 to \
  -3.08014, 51.3499 to \
  -3.08014, 95.0433 front fs empty border lc rgb '#549f' lw 0.1
set object 4366 polygon from \
  -3.08154, 95.0677 to \
  -0.03, 95.0677 to \
  -0.03, 51.3644 to \
  -3.08154, 51.3644 to \
  -3.08154, 95.0677 front fs empty border lc rgb '#549f' lw 0.1
set object 4367 polygon from \
  -3.08188, 95.0922 to \
  -0.03, 95.0922 to \
  -0.03, 51.3788 to \
  -3.08188, 51.3788 to \
  -3.08188, 95.0922 front fs empty border lc rgb '#549f' lw 0.1
set object 4368 polygon from \
  -3.08188, 95.1166 to \
  -0.03, 95.1166 to \
  -0.03, 51.3933 to \
  -3.08188, 51.3933 to \
  -3.08188, 95.1166 front fs empty border lc rgb '#549f' lw 0.1
set object 4369 polygon from \
  -3.08116, 95.1411 to \
  -0.03, 95.1411 to \
  -0.03, 51.4077 to \
  -3.08116, 51.4077 to \
  -3.08116, 95.1411 front fs empty border lc rgb '#549f' lw 0.1
set object 4370 polygon from \
  -3.07938, 95.1656 to \
  -0.03, 95.1656 to \
  -0.03, 51.4222 to \
  -3.07938, 51.4222 to \
  -3.07938, 95.1656 front fs empty border lc rgb '#549f' lw 0.1
set object 4371 polygon from \
  -3.07654, 95.19 to \
  -0.03, 95.19 to \
  -0.03, 51.4366 to \
  -3.07654, 51.4366 to \
  -3.07654, 95.19 front fs empty border lc rgb '#549f' lw 0.1
set object 4372 polygon from \
  -3.07264, 95.2145 to \
  -0.03, 95.2145 to \
  -0.03, 51.4511 to \
  -3.07264, 51.4511 to \
  -3.07264, 95.2145 front fs empty border lc rgb '#549f' lw 0.1
set object 4373 polygon from \
  -3.06768, 95.239 to \
  -0.03, 95.239 to \
  -0.03, 51.4656 to \
  -3.06768, 51.4656 to \
  -3.06768, 95.239 front fs empty border lc rgb '#549f' lw 0.1
set object 4374 polygon from \
  -3.06167, 95.2634 to \
  -0.03, 95.2634 to \
  -0.03, 51.48 to \
  -3.06167, 51.48 to \
  -3.06167, 95.2634 front fs empty border lc rgb '#549f' lw 0.1
set object 4375 polygon from \
  -3.0546, 95.2879 to \
  -0.03, 95.2879 to \
  -0.03, 51.4945 to \
  -3.0546, 51.4945 to \
  -3.0546, 95.2879 front fs empty border lc rgb '#549f' lw 0.1
set object 4376 polygon from \
  -3.04648, 95.3124 to \
  -0.03, 95.3124 to \
  -0.03, 51.509 to \
  -3.04648, 51.509 to \
  -3.04648, 95.3124 front fs empty border lc rgb '#549f' lw 0.1
set object 4377 polygon from \
  -3.03731, 95.3368 to \
  -0.03, 95.3368 to \
  -0.03, 51.5234 to \
  -3.03731, 51.5234 to \
  -3.03731, 95.3368 front fs empty border lc rgb '#549f' lw 0.1
set object 4378 polygon from \
  -3.0271, 95.3613 to \
  -0.03, 95.3613 to \
  -0.03, 51.5379 to \
  -3.0271, 51.5379 to \
  -3.0271, 95.3613 front fs empty border lc rgb '#549f' lw 0.1
set object 4379 polygon from \
  -3.01585, 95.3858 to \
  -0.03, 95.3858 to \
  -0.03, 51.5524 to \
  -3.01585, 51.5524 to \
  -3.01585, 95.3858 front fs empty border lc rgb '#549f' lw 0.1
set object 4380 polygon from \
  -3.00625, 95.4103 to \
  -0.03, 95.4103 to \
  -0.03, 51.5668 to \
  -3.00625, 51.5668 to \
  -3.00625, 95.4103 front fs empty border lc rgb '#549f' lw 0.1
set object 4381 polygon from \
  -2.99793, 95.4347 to \
  -0.03, 95.4347 to \
  -0.03, 51.5813 to \
  -2.99793, 51.5813 to \
  -2.99793, 95.4347 front fs empty border lc rgb '#549f' lw 0.1
set object 4382 polygon from \
  -2.98857, 95.4592 to \
  -0.03, 95.4592 to \
  -0.03, 51.5958 to \
  -2.98857, 51.5958 to \
  -2.98857, 95.4592 front fs empty border lc rgb '#549f' lw 0.1
set object 4383 polygon from \
  -2.97816, 95.4837 to \
  -0.03, 95.4837 to \
  -0.03, 51.6102 to \
  -2.97816, 51.6102 to \
  -2.97816, 95.4837 front fs empty border lc rgb '#549f' lw 0.1
set object 4384 polygon from \
  -2.9667, 95.5082 to \
  -0.03, 95.5082 to \
  -0.03, 51.6247 to \
  -2.9667, 51.6247 to \
  -2.9667, 95.5082 front fs empty border lc rgb '#549f' lw 0.1
set object 4385 polygon from \
  -2.95421, 95.5326 to \
  -0.03, 95.5326 to \
  -0.03, 51.6392 to \
  -2.95421, 51.6392 to \
  -2.95421, 95.5326 front fs empty border lc rgb '#549f' lw 0.1
set object 4386 polygon from \
  -2.94069, 95.5571 to \
  -0.03, 95.5571 to \
  -0.03, 51.6537 to \
  -2.94069, 51.6537 to \
  -2.94069, 95.5571 front fs empty border lc rgb '#549f' lw 0.1
set object 4387 polygon from \
  -2.92614, 95.5816 to \
  -0.03, 95.5816 to \
  -0.03, 51.6682 to \
  -2.92614, 51.6682 to \
  -2.92614, 95.5816 front fs empty border lc rgb '#549f' lw 0.1
set object 4388 polygon from \
  -2.91057, 95.6061 to \
  -0.03, 95.6061 to \
  -0.03, 51.6826 to \
  -2.91057, 51.6826 to \
  -2.91057, 95.6061 front fs empty border lc rgb '#549f' lw 0.1
set object 4389 polygon from \
  -2.89398, 95.6306 to \
  -0.03, 95.6306 to \
  -0.03, 51.6971 to \
  -2.89398, 51.6971 to \
  -2.89398, 95.6306 front fs empty border lc rgb '#549f' lw 0.1
set object 4390 polygon from \
  -2.87638, 95.6551 to \
  -0.03, 95.6551 to \
  -0.03, 51.7116 to \
  -2.87638, 51.7116 to \
  -2.87638, 95.6551 front fs empty border lc rgb '#549f' lw 0.1
set object 4391 polygon from \
  -2.85778, 95.6796 to \
  -0.03, 95.6796 to \
  -0.03, 51.7261 to \
  -2.85778, 51.7261 to \
  -2.85778, 95.6796 front fs empty border lc rgb '#549f' lw 0.1
set object 4392 polygon from \
  -2.83819, 95.704 to \
  -0.03, 95.704 to \
  -0.03, 51.7406 to \
  -2.83819, 51.7406 to \
  -2.83819, 95.704 front fs empty border lc rgb '#549f' lw 0.1
set object 4393 polygon from \
  -2.8176, 95.7285 to \
  -0.03, 95.7285 to \
  -0.03, 51.7551 to \
  -2.8176, 51.7551 to \
  -2.8176, 95.7285 front fs empty border lc rgb '#549f' lw 0.1
set object 4394 polygon from \
  -2.79604, 95.753 to \
  -0.03, 95.753 to \
  -0.03, 51.7695 to \
  -2.79604, 51.7695 to \
  -2.79604, 95.753 front fs empty border lc rgb '#549f' lw 0.1
set object 4395 polygon from \
  -2.77351, 95.7775 to \
  -0.03, 95.7775 to \
  -0.03, 51.784 to \
  -2.77351, 51.784 to \
  -2.77351, 95.7775 front fs empty border lc rgb '#549f' lw 0.1
set object 4396 polygon from \
  -2.75002, 95.802 to \
  -0.03, 95.802 to \
  -0.03, 51.7985 to \
  -2.75002, 51.7985 to \
  -2.75002, 95.802 front fs empty border lc rgb '#549f' lw 0.1
set object 4397 polygon from \
  -2.72558, 95.8265 to \
  -0.03, 95.8265 to \
  -0.03, 51.813 to \
  -2.72558, 51.813 to \
  -2.72558, 95.8265 front fs empty border lc rgb '#549f' lw 0.1
set object 4398 polygon from \
  -2.70019, 95.851 to \
  -0.03, 95.851 to \
  -0.03, 51.8275 to \
  -2.70019, 51.8275 to \
  -2.70019, 95.851 front fs empty border lc rgb '#549f' lw 0.1
set object 4399 polygon from \
  -2.67388, 95.8755 to \
  -0.03, 95.8755 to \
  -0.03, 51.842 to \
  -2.67388, 51.842 to \
  -2.67388, 95.8755 front fs empty border lc rgb '#549f' lw 0.1
set object 4400 polygon from \
  -2.64665, 95.9 to \
  -0.03, 95.9 to \
  -0.03, 51.8565 to \
  -2.64665, 51.8565 to \
  -2.64665, 95.9 front fs empty border lc rgb '#549f' lw 0.1
set object 4401 polygon from \
  -2.61851, 95.9245 to \
  -0.03, 95.9245 to \
  -0.03, 51.871 to \
  -2.61851, 51.871 to \
  -2.61851, 95.9245 front fs empty border lc rgb '#549f' lw 0.1
set object 4402 polygon from \
  -2.58948, 95.949 to \
  -0.03, 95.949 to \
  -0.03, 51.8855 to \
  -2.58948, 51.8855 to \
  -2.58948, 95.949 front fs empty border lc rgb '#549f' lw 0.1
plot - NaN notitle

