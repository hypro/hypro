# settings
set title "PLAD01-DBND42"
set size square
set term pdf font ',10'
set output "PLAD01_DBND42.pdf
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
set xrange [-2.02142:22.2201] 
set yrange [-38.5171:15.896] 

# plotting sets
set object 1 polygon from \
  -0.00129167, 0.0389253 to \
  0.101292, 0.0389253 to \
  0.101292, -0.0787735 to \
  -0.00129167, -0.0787735 to \
  -0.00129167, 0.0389253 front fs empty border lc rgb '#549f' lw 0.1
set object 2 polygon from \
  0.0987083, 0.0559972 to \
  0.201292, 0.0559972 to \
  0.201292, -0.213724 to \
  0.0987083, -0.213724 to \
  0.0987083, 0.0559972 front fs empty border lc rgb '#549f' lw 0.1
set object 3 polygon from \
  0.198708, 0.083294 to \
  0.301292, 0.083294 to \
  0.301292, -0.432517 to \
  0.198708, -0.432517 to \
  0.198708, 0.083294 front fs empty border lc rgb '#549f' lw 0.1
set object 4 polygon from \
  0.298708, 0.119563 to \
  0.401292, 0.119563 to \
  0.401292, -0.727644 to \
  0.298708, -0.727644 to \
  0.298708, 0.119563 front fs empty border lc rgb '#549f' lw 0.1
set object 5 polygon from \
  0.398708, 0.163525 to \
  0.501292, 0.163525 to \
  0.501292, -1.09045 to \
  0.398708, -1.09045 to \
  0.398708, 0.163525 front fs empty border lc rgb '#549f' lw 0.1
set object 6 polygon from \
  0.498708, 0.213918 to \
  0.601292, 0.213918 to \
  0.601292, -1.51175 to \
  0.498708, -1.51175 to \
  0.498708, 0.213918 front fs empty border lc rgb '#549f' lw 0.1
set object 7 polygon from \
  0.598708, 0.269536 to \
  0.701292, 0.269536 to \
  0.701292, -1.98226 to \
  0.598708, -1.98226 to \
  0.598708, 0.269536 front fs empty border lc rgb '#549f' lw 0.1
set object 8 polygon from \
  0.698708, 0.329252 to \
  0.801292, 0.329252 to \
  0.801292, -2.49293 to \
  0.698708, -2.49293 to \
  0.698708, 0.329252 front fs empty border lc rgb '#549f' lw 0.1
set object 9 polygon from \
  0.798708, 0.392034 to \
  0.901292, 0.392034 to \
  0.901292, -3.03521 to \
  0.798708, -3.03521 to \
  0.798708, 0.392034 front fs empty border lc rgb '#549f' lw 0.1
set object 10 polygon from \
  0.898708, 0.456951 to \
  1.00129, 0.456951 to \
  1.00129, -3.60117 to \
  0.898708, -3.60117 to \
  0.898708, 0.456951 front fs empty border lc rgb '#549f' lw 0.1
set object 11 polygon from \
  0.998708, 0.52318 to \
  1.10129, 0.52318 to \
  1.10129, -4.1836 to \
  0.998708, -4.1836 to \
  0.998708, 0.52318 front fs empty border lc rgb '#549f' lw 0.1
set object 12 polygon from \
  1.09871, 0.590112 to \
  1.20129, 0.590112 to \
  1.20129, -4.7762 to \
  1.09871, -4.7762 to \
  1.09871, 0.590112 front fs empty border lc rgb '#549f' lw 0.1
set object 13 polygon from \
  1.19871, 0.657095 to \
  1.30129, 0.657095 to \
  1.30129, -5.3733 to \
  1.19871, -5.3733 to \
  1.19871, 0.657095 front fs empty border lc rgb '#549f' lw 0.1
set object 14 polygon from \
  1.29871, 0.723714 to \
  1.40129, 0.723714 to \
  1.40129, -5.97012 to \
  1.29871, -5.97012 to \
  1.29871, 0.723714 front fs empty border lc rgb '#549f' lw 0.1
set object 15 polygon from \
  1.39871, 0.789461 to \
  1.50129, 0.789461 to \
  1.50129, -6.56248 to \
  1.39871, -6.56248 to \
  1.39871, 0.789461 front fs empty border lc rgb '#549f' lw 0.1
set object 16 polygon from \
  1.49871, 0.853993 to \
  1.60129, 0.853993 to \
  1.60129, -7.14695 to \
  1.49871, -7.14695 to \
  1.49871, 0.853993 front fs empty border lc rgb '#549f' lw 0.1
set object 17 polygon from \
  1.59871, 0.917036 to \
  1.70129, 0.917036 to \
  1.70129, -7.72074 to \
  1.59871, -7.72074 to \
  1.59871, 0.917036 front fs empty border lc rgb '#549f' lw 0.1
set object 18 polygon from \
  1.69871, 0.978385 to \
  1.80129, 0.978385 to \
  1.80129, -8.28163 to \
  1.69871, -8.28163 to \
  1.69871, 0.978385 front fs empty border lc rgb '#549f' lw 0.1
set object 19 polygon from \
  1.79871, 1.03789 to \
  1.90129, 1.03789 to \
  1.90129, -8.82793 to \
  1.79871, -8.82793 to \
  1.79871, 1.03789 front fs empty border lc rgb '#549f' lw 0.1
set object 20 polygon from \
  1.89871, 1.09544 to \
  2.00129, 1.09544 to \
  2.00129, -9.35839 to \
  1.89871, -9.35839 to \
  1.89871, 1.09544 front fs empty border lc rgb '#549f' lw 0.1
set object 21 polygon from \
  1.99871, 1.15099 to \
  2.10129, 1.15099 to \
  2.10129, -9.87217 to \
  1.99871, -9.87217 to \
  1.99871, 1.15099 front fs empty border lc rgb '#549f' lw 0.1
set object 22 polygon from \
  2.09871, 1.2045 to \
  2.20129, 1.2045 to \
  2.20129, -10.3688 to \
  2.09871, -10.3688 to \
  2.09871, 1.2045 front fs empty border lc rgb '#549f' lw 0.1
set object 23 polygon from \
  2.19871, 1.25597 to \
  2.30129, 1.25597 to \
  2.30129, -10.8479 to \
  2.19871, -10.8479 to \
  2.19871, 1.25597 front fs empty border lc rgb '#549f' lw 0.1
set object 24 polygon from \
  2.29871, 1.3055 to \
  2.40129, 1.3055 to \
  2.40129, -11.3098 to \
  2.29871, -11.3098 to \
  2.29871, 1.3055 front fs empty border lc rgb '#549f' lw 0.1
set object 25 polygon from \
  2.39871, 1.35313 to \
  2.50129, 1.35313 to \
  2.50129, -11.7545 to \
  2.39871, -11.7545 to \
  2.39871, 1.35313 front fs empty border lc rgb '#549f' lw 0.1
set object 26 polygon from \
  2.49871, 1.39887 to \
  2.60129, 1.39887 to \
  2.60129, -12.1823 to \
  2.49871, -12.1823 to \
  2.49871, 1.39887 front fs empty border lc rgb '#549f' lw 0.1
set object 27 polygon from \
  2.59871, 1.44278 to \
  2.70129, 1.44278 to \
  2.70129, -12.5939 to \
  2.59871, -12.5939 to \
  2.59871, 1.44278 front fs empty border lc rgb '#549f' lw 0.1
set object 28 polygon from \
  2.69871, 1.48496 to \
  2.80129, 1.48496 to \
  2.80129, -12.9897 to \
  2.69871, -12.9897 to \
  2.69871, 1.48496 front fs empty border lc rgb '#549f' lw 0.1
set object 29 polygon from \
  2.79871, 1.5255 to \
  2.90129, 1.5255 to \
  2.90129, -13.3705 to \
  2.79871, -13.3705 to \
  2.79871, 1.5255 front fs empty border lc rgb '#549f' lw 0.1
set object 30 polygon from \
  2.89871, 1.5649 to \
  3.00129, 1.5649 to \
  3.00129, -13.7372 to \
  2.89871, -13.7372 to \
  2.89871, 1.5649 front fs empty border lc rgb '#549f' lw 0.1
set object 31 polygon from \
  2.99871, 1.60284 to \
  3.10129, 1.60284 to \
  3.10129, -14.0903 to \
  2.99871, -14.0903 to \
  2.99871, 1.60284 front fs empty border lc rgb '#549f' lw 0.1
set object 32 polygon from \
  3.09871, 1.6394 to \
  3.20129, 1.6394 to \
  3.20129, -14.4305 to \
  3.09871, -14.4305 to \
  3.09871, 1.6394 front fs empty border lc rgb '#549f' lw 0.1
set object 33 polygon from \
  3.19871, 1.67465 to \
  3.30129, 1.67465 to \
  3.30129, -14.7584 to \
  3.19871, -14.7584 to \
  3.19871, 1.67465 front fs empty border lc rgb '#549f' lw 0.1
set object 34 polygon from \
  3.29871, 1.70867 to \
  3.40129, 1.70867 to \
  3.40129, -15.0747 to \
  3.29871, -15.0747 to \
  3.29871, 1.70867 front fs empty border lc rgb '#549f' lw 0.1
set object 35 polygon from \
  3.39871, 1.74154 to \
  3.50129, 1.74154 to \
  3.50129, -15.3801 to \
  3.39871, -15.3801 to \
  3.39871, 1.74154 front fs empty border lc rgb '#549f' lw 0.1
set object 36 polygon from \
  3.49871, 1.77333 to \
  3.60129, 1.77333 to \
  3.60129, -15.6753 to \
  3.49871, -15.6753 to \
  3.49871, 1.77333 front fs empty border lc rgb '#549f' lw 0.1
set object 37 polygon from \
  3.59871, 1.8041 to \
  3.70129, 1.8041 to \
  3.70129, -15.9609 to \
  3.59871, -15.9609 to \
  3.59871, 1.8041 front fs empty border lc rgb '#549f' lw 0.1
set object 38 polygon from \
  3.69871, 1.83391 to \
  3.80129, 1.83391 to \
  3.80129, -16.2374 to \
  3.69871, -16.2374 to \
  3.69871, 1.83391 front fs empty border lc rgb '#549f' lw 0.1
set object 39 polygon from \
  3.79871, 1.86282 to \
  3.90129, 1.86282 to \
  3.90129, -16.5053 to \
  3.79871, -16.5053 to \
  3.79871, 1.86282 front fs empty border lc rgb '#549f' lw 0.1
set object 40 polygon from \
  3.89871, 1.89088 to \
  4.00129, 1.89088 to \
  4.00129, -16.7652 to \
  3.89871, -16.7652 to \
  3.89871, 1.89088 front fs empty border lc rgb '#549f' lw 0.1
set object 41 polygon from \
  3.99871, 1.91814 to \
  4.10129, 1.91814 to \
  4.10129, -17.0176 to \
  3.99871, -17.0176 to \
  3.99871, 1.91814 front fs empty border lc rgb '#549f' lw 0.1
set object 42 polygon from \
  4.09871, 1.94463 to \
  4.20129, 1.94463 to \
  4.20129, -17.2627 to \
  4.09871, -17.2627 to \
  4.09871, 1.94463 front fs empty border lc rgb '#549f' lw 0.1
set object 43 polygon from \
  4.19871, 1.97041 to \
  4.30129, 1.97041 to \
  4.30129, -17.5011 to \
  4.19871, -17.5011 to \
  4.19871, 1.97041 front fs empty border lc rgb '#549f' lw 0.1
set object 44 polygon from \
  4.29871, 1.9955 to \
  4.40129, 1.9955 to \
  4.40129, -17.733 to \
  4.29871, -17.733 to \
  4.29871, 1.9955 front fs empty border lc rgb '#549f' lw 0.1
set object 45 polygon from \
  4.39871, 2.01993 to \
  4.50129, 2.01993 to \
  4.50129, -17.9587 to \
  4.39871, -17.9587 to \
  4.39871, 2.01993 front fs empty border lc rgb '#549f' lw 0.1
set object 46 polygon from \
  4.49871, 2.04374 to \
  4.60129, 2.04374 to \
  4.60129, -18.1786 to \
  4.49871, -18.1786 to \
  4.49871, 2.04374 front fs empty border lc rgb '#549f' lw 0.1
set object 47 polygon from \
  4.59871, 2.06694 to \
  4.70129, 2.06694 to \
  4.70129, -18.3928 to \
  4.59871, -18.3928 to \
  4.59871, 2.06694 front fs empty border lc rgb '#549f' lw 0.1
set object 48 polygon from \
  4.69871, 2.08956 to \
  4.80129, 2.08956 to \
  4.80129, -18.6016 to \
  4.69871, -18.6016 to \
  4.69871, 2.08956 front fs empty border lc rgb '#549f' lw 0.1
set object 49 polygon from \
  4.79871, 2.11162 to \
  4.90129, 2.11162 to \
  4.90129, -18.8052 to \
  4.79871, -18.8052 to \
  4.79871, 2.11162 front fs empty border lc rgb '#549f' lw 0.1
set object 50 polygon from \
  4.89871, 2.13314 to \
  5.00129, 2.13314 to \
  5.00129, -19.0038 to \
  4.89871, -19.0038 to \
  4.89871, 2.13314 front fs empty border lc rgb '#549f' lw 0.1
set object 51 polygon from \
  4.99871, 2.15412 to \
  5.10129, 2.15412 to \
  5.10129, -19.1974 to \
  4.99871, -19.1974 to \
  4.99871, 2.15412 front fs empty border lc rgb '#549f' lw 0.1
set object 52 polygon from \
  4.89742, 2.27136 to \
  5.20258, 2.27136 to \
  5.20258, -19.4908 to \
  4.89742, -19.4908 to \
  4.89742, 2.27136 front fs empty border lc rgb '#549f' lw 0.1
set object 53 polygon from \
  4.99742, 2.43181 to \
  5.30258, 2.43181 to \
  5.30258, -19.818 to \
  4.99742, -19.818 to \
  4.99742, 2.43181 front fs empty border lc rgb '#549f' lw 0.1
set object 54 polygon from \
  5.09742, 2.63988 to \
  5.40258, 2.63988 to \
  5.40258, -20.1803 to \
  5.09742, -20.1803 to \
  5.09742, 2.63988 front fs empty border lc rgb '#549f' lw 0.1
set object 55 polygon from \
  5.19742, 2.87235 to \
  5.50258, 2.87235 to \
  5.50258, -20.5523 to \
  5.19742, -20.5523 to \
  5.19742, 2.87235 front fs empty border lc rgb '#549f' lw 0.1
set object 56 polygon from \
  5.29742, 3.11169 to \
  5.60258, 3.11169 to \
  5.60258, -20.9156 to \
  5.29742, -20.9156 to \
  5.29742, 3.11169 front fs empty border lc rgb '#549f' lw 0.1
set object 57 polygon from \
  5.39742, 3.34504 to \
  5.70258, 3.34504 to \
  5.70258, -21.257 to \
  5.39742, -21.257 to \
  5.39742, 3.34504 front fs empty border lc rgb '#549f' lw 0.1
set object 58 polygon from \
  5.49742, 3.56334 to \
  5.80258, 3.56334 to \
  5.80258, -21.5678 to \
  5.49742, -21.5678 to \
  5.49742, 3.56334 front fs empty border lc rgb '#549f' lw 0.1
set object 59 polygon from \
  5.59742, 3.76055 to \
  5.90258, 3.76055 to \
  5.90258, -21.8426 to \
  5.59742, -21.8426 to \
  5.59742, 3.76055 front fs empty border lc rgb '#549f' lw 0.1
set object 60 polygon from \
  5.69742, 3.93304 to \
  6.00258, 3.93304 to \
  6.00258, -22.0789 to \
  5.69742, -22.0789 to \
  5.69742, 3.93304 front fs empty border lc rgb '#549f' lw 0.1
set object 61 polygon from \
  5.79742, 4.07903 to \
  6.10258, 4.07903 to \
  6.10258, -22.276 to \
  5.79742, -22.276 to \
  5.79742, 4.07903 front fs empty border lc rgb '#549f' lw 0.1
set object 62 polygon from \
  5.89742, 4.19814 to \
  6.20258, 4.19814 to \
  6.20258, -22.4348 to \
  5.89742, -22.4348 to \
  5.89742, 4.19814 front fs empty border lc rgb '#549f' lw 0.1
set object 63 polygon from \
  5.99742, 4.29101 to \
  6.30258, 4.29101 to \
  6.30258, -22.5572 to \
  5.99742, -22.5572 to \
  5.99742, 4.29101 front fs empty border lc rgb '#549f' lw 0.1
set object 64 polygon from \
  6.09742, 4.35904 to \
  6.40258, 4.35904 to \
  6.40258, -22.6458 to \
  6.09742, -22.6458 to \
  6.09742, 4.35904 front fs empty border lc rgb '#549f' lw 0.1
set object 65 polygon from \
  6.19742, 4.4041 to \
  6.50258, 4.4041 to \
  6.50258, -22.7039 to \
  6.19742, -22.7039 to \
  6.19742, 4.4041 front fs empty border lc rgb '#549f' lw 0.1
set object 66 polygon from \
  6.29742, 4.42836 to \
  6.60258, 4.42836 to \
  6.60258, -22.7346 to \
  6.29742, -22.7346 to \
  6.29742, 4.42836 front fs empty border lc rgb '#549f' lw 0.1
set object 67 polygon from \
  6.39742, 4.43414 to \
  6.70258, 4.43414 to \
  6.70258, -22.7414 to \
  6.39742, -22.7414 to \
  6.39742, 4.43414 front fs empty border lc rgb '#549f' lw 0.1
set object 68 polygon from \
  6.49742, 4.43131 to \
  6.80258, 4.43131 to \
  6.80258, -22.7386 to \
  6.49742, -22.7386 to \
  6.49742, 4.43131 front fs empty border lc rgb '#549f' lw 0.1
set object 69 polygon from \
  6.59742, 4.41965 to \
  6.90258, 4.41965 to \
  6.90258, -22.7234 to \
  6.59742, -22.7234 to \
  6.59742, 4.41965 front fs empty border lc rgb '#549f' lw 0.1
set object 70 polygon from \
  6.69742, 4.3944 to \
  7.00258, 4.3944 to \
  7.00258, -22.6909 to \
  6.69742, -22.6909 to \
  6.69742, 4.3944 front fs empty border lc rgb '#549f' lw 0.1
set object 71 polygon from \
  6.79742, 4.35776 to \
  7.10258, 4.35776 to \
  7.10258, -22.6442 to \
  6.79742, -22.6442 to \
  6.79742, 4.35776 front fs empty border lc rgb '#549f' lw 0.1
set object 72 polygon from \
  6.89742, 4.31175 to \
  7.20258, 4.31175 to \
  7.20258, -22.5858 to \
  6.89742, -22.5858 to \
  6.89742, 4.31175 front fs empty border lc rgb '#549f' lw 0.1
set object 73 polygon from \
  6.99742, 4.25824 to \
  7.30258, 4.25824 to \
  7.30258, -22.5182 to \
  6.99742, -22.5182 to \
  6.99742, 4.25824 front fs empty border lc rgb '#549f' lw 0.1
set object 74 polygon from \
  7.09742, 4.1989 to \
  7.40258, 4.1989 to \
  7.40258, -22.4436 to \
  7.09742, -22.4436 to \
  7.09742, 4.1989 front fs empty border lc rgb '#549f' lw 0.1
set object 75 polygon from \
  7.19742, 4.13521 to \
  7.50258, 4.13521 to \
  7.50258, -22.3639 to \
  7.19742, -22.3639 to \
  7.19742, 4.13521 front fs empty border lc rgb '#549f' lw 0.1
set object 76 polygon from \
  7.29742, 4.06848 to \
  7.60258, 4.06848 to \
  7.60258, -22.2806 to \
  7.29742, -22.2806 to \
  7.29742, 4.06848 front fs empty border lc rgb '#549f' lw 0.1
set object 77 polygon from \
  7.39742, 3.99982 to \
  7.70258, 3.99982 to \
  7.70258, -22.1952 to \
  7.39742, -22.1952 to \
  7.39742, 3.99982 front fs empty border lc rgb '#549f' lw 0.1
set object 78 polygon from \
  7.49742, 3.93018 to \
  7.80258, 3.93018 to \
  7.80258, -22.1089 to \
  7.49742, -22.1089 to \
  7.49742, 3.93018 front fs empty border lc rgb '#549f' lw 0.1
set object 79 polygon from \
  7.59742, 3.86037 to \
  7.90258, 3.86037 to \
  7.90258, -22.0226 to \
  7.59742, -22.0226 to \
  7.59742, 3.86037 front fs empty border lc rgb '#549f' lw 0.1
set object 80 polygon from \
  7.69742, 3.79105 to \
  8.00258, 3.79105 to \
  8.00258, -21.9372 to \
  7.69742, -21.9372 to \
  7.69742, 3.79105 front fs empty border lc rgb '#549f' lw 0.1
set object 81 polygon from \
  7.79742, 3.72275 to \
  8.10258, 3.72275 to \
  8.10258, -21.8532 to \
  7.79742, -21.8532 to \
  7.79742, 3.72275 front fs empty border lc rgb '#549f' lw 0.1
set object 82 polygon from \
  7.89742, 3.65589 to \
  8.20258, 3.65589 to \
  8.20258, -21.7712 to \
  7.89742, -21.7712 to \
  7.89742, 3.65589 front fs empty border lc rgb '#549f' lw 0.1
set object 83 polygon from \
  7.99742, 3.5908 to \
  8.30258, 3.5908 to \
  8.30258, -21.6916 to \
  7.99742, -21.6916 to \
  7.99742, 3.5908 front fs empty border lc rgb '#549f' lw 0.1
set object 84 polygon from \
  8.09742, 3.52774 to \
  8.40258, 3.52774 to \
  8.40258, -21.6146 to \
  8.09742, -21.6146 to \
  8.09742, 3.52774 front fs empty border lc rgb '#549f' lw 0.1
set object 85 polygon from \
  8.19742, 3.46687 to \
  8.50258, 3.46687 to \
  8.50258, -21.5405 to \
  8.19742, -21.5405 to \
  8.19742, 3.46687 front fs empty border lc rgb '#549f' lw 0.1
set object 86 polygon from \
  8.29742, 3.40832 to \
  8.60258, 3.40832 to \
  8.60258, -21.4693 to \
  8.29742, -21.4693 to \
  8.29742, 3.40832 front fs empty border lc rgb '#549f' lw 0.1
set object 87 polygon from \
  8.39742, 3.35215 to \
  8.70258, 3.35215 to \
  8.70258, -21.4011 to \
  8.39742, -21.4011 to \
  8.39742, 3.35215 front fs empty border lc rgb '#549f' lw 0.1
set object 88 polygon from \
  8.49742, 3.29838 to \
  8.80258, 3.29838 to \
  8.80258, -21.3359 to \
  8.49742, -21.3359 to \
  8.49742, 3.29838 front fs empty border lc rgb '#549f' lw 0.1
set object 89 polygon from \
  8.59742, 3.24702 to \
  8.90258, 3.24702 to \
  8.90258, -21.2737 to \
  8.59742, -21.2737 to \
  8.59742, 3.24702 front fs empty border lc rgb '#549f' lw 0.1
set object 90 polygon from \
  8.69742, 3.19803 to \
  9.00258, 3.19803 to \
  9.00258, -21.2145 to \
  8.69742, -21.2145 to \
  8.69742, 3.19803 front fs empty border lc rgb '#549f' lw 0.1
set object 91 polygon from \
  8.79742, 3.15137 to \
  9.10258, 3.15137 to \
  9.10258, -21.1582 to \
  8.79742, -21.1582 to \
  8.79742, 3.15137 front fs empty border lc rgb '#549f' lw 0.1
set object 92 polygon from \
  8.89742, 3.10695 to \
  9.20258, 3.10695 to \
  9.20258, -21.1046 to \
  8.89742, -21.1046 to \
  8.89742, 3.10695 front fs empty border lc rgb '#549f' lw 0.1
set object 93 polygon from \
  8.99742, 3.06472 to \
  9.30258, 3.06472 to \
  9.30258, -21.0537 to \
  8.99742, -21.0537 to \
  8.99742, 3.06472 front fs empty border lc rgb '#549f' lw 0.1
set object 94 polygon from \
  9.09742, 3.02457 to \
  9.40258, 3.02457 to \
  9.40258, -21.0054 to \
  9.09742, -21.0054 to \
  9.09742, 3.02457 front fs empty border lc rgb '#549f' lw 0.1
set object 95 polygon from \
  9.19742, 2.98643 to \
  9.50258, 2.98643 to \
  9.50258, -20.9595 to \
  9.19742, -20.9595 to \
  9.19742, 2.98643 front fs empty border lc rgb '#549f' lw 0.1
set object 96 polygon from \
  9.29742, 2.95021 to \
  9.60258, 2.95021 to \
  9.60258, -20.916 to \
  9.29742, -20.916 to \
  9.29742, 2.95021 front fs empty border lc rgb '#549f' lw 0.1
set object 97 polygon from \
  9.39742, 2.9158 to \
  9.70258, 2.9158 to \
  9.70258, -20.8746 to \
  9.39742, -20.8746 to \
  9.39742, 2.9158 front fs empty border lc rgb '#549f' lw 0.1
set object 98 polygon from \
  9.49742, 2.88312 to \
  9.80258, 2.88312 to \
  9.80258, -20.8354 to \
  9.49742, -20.8354 to \
  9.49742, 2.88312 front fs empty border lc rgb '#549f' lw 0.1
set object 99 polygon from \
  9.59742, 2.85208 to \
  9.90258, 2.85208 to \
  9.90258, -20.7981 to \
  9.59742, -20.7981 to \
  9.59742, 2.85208 front fs empty border lc rgb '#549f' lw 0.1
set object 100 polygon from \
  9.69742, 2.82259 to \
  10.0026, 2.82259 to \
  10.0026, -20.7627 to \
  9.69742, -20.7627 to \
  9.69742, 2.82259 front fs empty border lc rgb '#549f' lw 0.1
set object 101 polygon from \
  9.79742, 2.79458 to \
  10.1026, 2.79458 to \
  10.1026, -20.7291 to \
  9.79742, -20.7291 to \
  9.79742, 2.79458 front fs empty border lc rgb '#549f' lw 0.1
set object 102 polygon from \
  9.89742, 2.76795 to \
  10.2026, 2.76795 to \
  10.2026, -20.6972 to \
  9.89742, -20.6972 to \
  9.89742, 2.76795 front fs empty border lc rgb '#549f' lw 0.1
set object 103 polygon from \
  9.79612, 3.07656 to \
  10.3039, 3.07656 to \
  10.3039, -21.0083 to \
  9.79612, -21.0083 to \
  9.79612, 3.07656 front fs empty border lc rgb '#549f' lw 0.1
set object 104 polygon from \
  9.89612, 3.40582 to \
  10.4039, 3.40582 to \
  10.4039, -21.3482 to \
  9.89612, -21.3482 to \
  9.89612, 3.40582 front fs empty border lc rgb '#549f' lw 0.1
set object 105 polygon from \
  9.99612, 3.78793 to \
  10.5039, 3.78793 to \
  10.5039, -21.7638 to \
  9.99612, -21.7638 to \
  9.99612, 3.78793 front fs empty border lc rgb '#549f' lw 0.1
set object 106 polygon from \
  10.0961, 4.19752 to \
  10.6039, 4.19752 to \
  10.6039, -22.2351 to \
  10.0961, -22.2351 to \
  10.0961, 4.19752 front fs empty border lc rgb '#549f' lw 0.1
set object 107 polygon from \
  10.1961, 4.6148 to \
  10.7039, 4.6148 to \
  10.7039, -22.7455 to \
  10.1961, -22.7455 to \
  10.1961, 4.6148 front fs empty border lc rgb '#549f' lw 0.1
set object 108 polygon from \
  10.2961, 5.02455 to \
  10.8039, 5.02455 to \
  10.8039, -23.2803 to \
  10.2961, -23.2803 to \
  10.2961, 5.02455 front fs empty border lc rgb '#549f' lw 0.1
set object 109 polygon from \
  10.3961, 5.41535 to \
  10.9039, 5.41535 to \
  10.9039, -23.8273 to \
  10.3961, -23.8273 to \
  10.3961, 5.41535 front fs empty border lc rgb '#549f' lw 0.1
set object 110 polygon from \
  10.4961, 5.77888 to \
  11.0039, 5.77888 to \
  11.0039, -24.376 to \
  10.4961, -24.376 to \
  10.4961, 5.77888 front fs empty border lc rgb '#549f' lw 0.1
set object 111 polygon from \
  10.5961, 6.10934 to \
  11.1039, 6.10934 to \
  11.1039, -24.9179 to \
  10.5961, -24.9179 to \
  10.5961, 6.10934 front fs empty border lc rgb '#549f' lw 0.1
set object 112 polygon from \
  10.6961, 6.40298 to \
  11.2039, 6.40298 to \
  11.2039, -25.4456 to \
  10.6961, -25.4456 to \
  10.6961, 6.40298 front fs empty border lc rgb '#549f' lw 0.1
set object 113 polygon from \
  10.7961, 6.66451 to \
  11.3039, 6.66451 to \
  11.3039, -25.9601 to \
  10.7961, -25.9601 to \
  10.7961, 6.66451 front fs empty border lc rgb '#549f' lw 0.1
set object 114 polygon from \
  10.8961, 6.89224 to \
  11.4039, 6.89224 to \
  11.4039, -26.4558 to \
  10.8961, -26.4558 to \
  10.8961, 6.89224 front fs empty border lc rgb '#549f' lw 0.1
set object 115 polygon from \
  10.9961, 7.10946 to \
  11.5039, 7.10946 to \
  11.5039, -26.9519 to \
  10.9961, -26.9519 to \
  10.9961, 7.10946 front fs empty border lc rgb '#549f' lw 0.1
set object 116 polygon from \
  11.0961, 7.3032 to \
  11.6039, 7.3032 to \
  11.6039, -27.4317 to \
  11.0961, -27.4317 to \
  11.0961, 7.3032 front fs empty border lc rgb '#549f' lw 0.1
set object 117 polygon from \
  11.1961, 7.47233 to \
  11.7039, 7.47233 to \
  11.7039, -27.8903 to \
  11.1961, -27.8903 to \
  11.1961, 7.47233 front fs empty border lc rgb '#549f' lw 0.1
set object 118 polygon from \
  11.2961, 7.61856 to \
  11.8039, 7.61856 to \
  11.8039, -28.326 to \
  11.2961, -28.326 to \
  11.2961, 7.61856 front fs empty border lc rgb '#549f' lw 0.1
set object 119 polygon from \
  11.3961, 7.7436 to \
  11.9039, 7.7436 to \
  11.9039, -28.7373 to \
  11.3961, -28.7373 to \
  11.3961, 7.7436 front fs empty border lc rgb '#549f' lw 0.1
set object 120 polygon from \
  11.4961, 7.84911 to \
  12.0039, 7.84911 to \
  12.0039, -29.1231 to \
  11.4961, -29.1231 to \
  11.4961, 7.84911 front fs empty border lc rgb '#549f' lw 0.1
set object 121 polygon from \
  11.5961, 7.93665 to \
  12.1039, 7.93665 to \
  12.1039, -29.4825 to \
  11.5961, -29.4825 to \
  11.5961, 7.93665 front fs empty border lc rgb '#549f' lw 0.1
set object 122 polygon from \
  11.6961, 8.00766 to \
  12.2039, 8.00766 to \
  12.2039, -29.8146 to \
  11.6961, -29.8146 to \
  11.6961, 8.00766 front fs empty border lc rgb '#549f' lw 0.1
set object 123 polygon from \
  11.7961, 8.06345 to \
  12.3039, 8.06345 to \
  12.3039, -30.119 to \
  11.7961, -30.119 to \
  11.7961, 8.06345 front fs empty border lc rgb '#549f' lw 0.1
set object 124 polygon from \
  11.8961, 8.10519 to \
  12.4039, 8.10519 to \
  12.4039, -30.3954 to \
  11.8961, -30.3954 to \
  11.8961, 8.10519 front fs empty border lc rgb '#549f' lw 0.1
set object 125 polygon from \
  11.9961, 8.14662 to \
  12.5039, 8.14662 to \
  12.5039, -30.6563 to \
  11.9961, -30.6563 to \
  11.9961, 8.14662 front fs empty border lc rgb '#549f' lw 0.1
set object 126 polygon from \
  12.0961, 8.18954 to \
  12.6039, 8.18954 to \
  12.6039, -30.9026 to \
  12.0961, -30.9026 to \
  12.0961, 8.18954 front fs empty border lc rgb '#549f' lw 0.1
set object 127 polygon from \
  12.1961, 8.22464 to \
  12.7039, 8.22464 to \
  12.7039, -31.1245 to \
  12.1961, -31.1245 to \
  12.1961, 8.22464 front fs empty border lc rgb '#549f' lw 0.1
set object 128 polygon from \
  12.2961, 8.25081 to \
  12.8039, 8.25081 to \
  12.8039, -31.3205 to \
  12.2961, -31.3205 to \
  12.2961, 8.25081 front fs empty border lc rgb '#549f' lw 0.1
set object 129 polygon from \
  12.3961, 8.26839 to \
  12.9039, 8.26839 to \
  12.9039, -31.4907 to \
  12.3961, -31.4907 to \
  12.3961, 8.26839 front fs empty border lc rgb '#549f' lw 0.1
set object 130 polygon from \
  12.4961, 8.27862 to \
  13.0039, 8.27862 to \
  13.0039, -31.6367 to \
  12.4961, -31.6367 to \
  12.4961, 8.27862 front fs empty border lc rgb '#549f' lw 0.1
set object 131 polygon from \
  12.5961, 8.30451 to \
  13.1039, 8.30451 to \
  13.1039, -31.7816 to \
  12.5961, -31.7816 to \
  12.5961, 8.30451 front fs empty border lc rgb '#549f' lw 0.1
set object 132 polygon from \
  12.6961, 8.32737 to \
  13.2039, 8.32737 to \
  13.2039, -31.9072 to \
  12.6961, -31.9072 to \
  12.6961, 8.32737 front fs empty border lc rgb '#549f' lw 0.1
set object 133 polygon from \
  12.7961, 8.34328 to \
  13.3039, 8.34328 to \
  13.3039, -32.0102 to \
  12.7961, -32.0102 to \
  12.7961, 8.34328 front fs empty border lc rgb '#549f' lw 0.1
set object 134 polygon from \
  12.8961, 8.35209 to \
  13.4039, 8.35209 to \
  13.4039, -32.0912 to \
  12.8961, -32.0912 to \
  12.8961, 8.35209 front fs empty border lc rgb '#549f' lw 0.1
set object 135 polygon from \
  12.9961, 8.35369 to \
  13.5039, 8.35369 to \
  13.5039, -32.1509 to \
  12.9961, -32.1509 to \
  12.9961, 8.35369 front fs empty border lc rgb '#549f' lw 0.1
set object 136 polygon from \
  13.0961, 8.35125 to \
  13.6039, 8.35125 to \
  13.6039, -32.1899 to \
  13.0961, -32.1899 to \
  13.0961, 8.35125 front fs empty border lc rgb '#549f' lw 0.1
set object 137 polygon from \
  13.1961, 8.34543 to \
  13.7039, 8.34543 to \
  13.7039, -32.2093 to \
  13.1961, -32.2093 to \
  13.1961, 8.34543 front fs empty border lc rgb '#549f' lw 0.1
set object 138 polygon from \
  13.2961, 8.33222 to \
  13.8039, 8.33222 to \
  13.8039, -32.2099 to \
  13.2961, -32.2099 to \
  13.2961, 8.33222 front fs empty border lc rgb '#549f' lw 0.1
set object 139 polygon from \
  13.3961, 8.31158 to \
  13.9039, 8.31158 to \
  13.9039, -32.207 to \
  13.3961, -32.207 to \
  13.3961, 8.31158 front fs empty border lc rgb '#549f' lw 0.1
set object 140 polygon from \
  13.4961, 8.28357 to \
  14.0039, 8.28357 to \
  14.0039, -32.1897 to \
  13.4961, -32.1897 to \
  13.4961, 8.28357 front fs empty border lc rgb '#549f' lw 0.1
set object 141 polygon from \
  13.5961, 8.24826 to \
  14.1039, 8.24826 to \
  14.1039, -32.1556 to \
  13.5961, -32.1556 to \
  13.5961, 8.24826 front fs empty border lc rgb '#549f' lw 0.1
set object 142 polygon from \
  13.6961, 8.20577 to \
  14.2039, 8.20577 to \
  14.2039, -32.106 to \
  13.6961, -32.106 to \
  13.6961, 8.20577 front fs empty border lc rgb '#549f' lw 0.1
set object 143 polygon from \
  13.7961, 8.15629 to \
  14.3039, 8.15629 to \
  14.3039, -32.042 to \
  13.7961, -32.042 to \
  13.7961, 8.15629 front fs empty border lc rgb '#549f' lw 0.1
set object 144 polygon from \
  13.8961, 8.10003 to \
  14.4039, 8.10003 to \
  14.4039, -31.9647 to \
  13.8961, -31.9647 to \
  13.8961, 8.10003 front fs empty border lc rgb '#549f' lw 0.1
set object 145 polygon from \
  13.9961, 8.03727 to \
  14.5039, 8.03727 to \
  14.5039, -31.8754 to \
  13.9961, -31.8754 to \
  13.9961, 8.03727 front fs empty border lc rgb '#549f' lw 0.1
set object 146 polygon from \
  14.0961, 7.96829 to \
  14.6039, 7.96829 to \
  14.6039, -31.7752 to \
  14.0961, -31.7752 to \
  14.0961, 7.96829 front fs empty border lc rgb '#549f' lw 0.1
set object 147 polygon from \
  14.1961, 7.89345 to \
  14.7039, 7.89345 to \
  14.7039, -31.6652 to \
  14.1961, -31.6652 to \
  14.1961, 7.89345 front fs empty border lc rgb '#549f' lw 0.1
set object 148 polygon from \
  14.2961, 7.81309 to \
  14.8039, 7.81309 to \
  14.8039, -31.5466 to \
  14.2961, -31.5466 to \
  14.2961, 7.81309 front fs empty border lc rgb '#549f' lw 0.1
set object 149 polygon from \
  14.3961, 7.72762 to \
  14.9039, 7.72762 to \
  14.9039, -31.4205 to \
  14.3961, -31.4205 to \
  14.3961, 7.72762 front fs empty border lc rgb '#549f' lw 0.1
set object 150 polygon from \
  14.4961, 7.63745 to \
  15.0039, 7.63745 to \
  15.0039, -31.2881 to \
  14.4961, -31.2881 to \
  14.4961, 7.63745 front fs empty border lc rgb '#549f' lw 0.1
set object 151 polygon from \
  14.5961, 7.54299 to \
  15.1039, 7.54299 to \
  15.1039, -31.1503 to \
  14.5961, -31.1503 to \
  14.5961, 7.54299 front fs empty border lc rgb '#549f' lw 0.1
set object 152 polygon from \
  14.6961, 7.4447 to \
  15.2039, 7.4447 to \
  15.2039, -31.008 to \
  14.6961, -31.008 to \
  14.6961, 7.4447 front fs empty border lc rgb '#549f' lw 0.1
set object 153 polygon from \
  14.7961, 7.34302 to \
  15.3039, 7.34302 to \
  15.3039, -30.8624 to \
  14.7961, -30.8624 to \
  14.7961, 7.34302 front fs empty border lc rgb '#549f' lw 0.1
set object 154 polygon from \
  14.6948, 7.93095 to \
  15.4052, 7.93095 to \
  15.4052, -31.4492 to \
  14.6948, -31.4492 to \
  14.6948, 7.93095 front fs empty border lc rgb '#549f' lw 0.1
set object 155 polygon from \
  14.7948, 8.44464 to \
  15.5052, 8.44464 to \
  15.5052, -31.912 to \
  14.7948, -31.912 to \
  14.7948, 8.44464 front fs empty border lc rgb '#549f' lw 0.1
set object 156 polygon from \
  14.8948, 8.97556 to \
  15.6052, 8.97556 to \
  15.6052, -32.3825 to \
  14.8948, -32.3825 to \
  14.8948, 8.97556 front fs empty border lc rgb '#549f' lw 0.1
set object 157 polygon from \
  14.9948, 9.48816 to \
  15.7052, 9.48816 to \
  15.7052, -32.8229 to \
  14.9948, -32.8229 to \
  14.9948, 9.48816 front fs empty border lc rgb '#549f' lw 0.1
set object 158 polygon from \
  15.0948, 9.95762 to \
  15.8052, 9.95762 to \
  15.8052, -33.2075 to \
  15.0948, -33.2075 to \
  15.0948, 9.95762 front fs empty border lc rgb '#549f' lw 0.1
set object 159 polygon from \
  15.1948, 10.3677 to \
  15.9052, 10.3677 to \
  15.9052, -33.5198 to \
  15.1948, -33.5198 to \
  15.1948, 10.3677 front fs empty border lc rgb '#549f' lw 0.1
set object 160 polygon from \
  15.2948, 10.7088 to \
  16.0052, 10.7088 to \
  16.0052, -33.751 to \
  15.2948, -33.751 to \
  15.2948, 10.7088 front fs empty border lc rgb '#549f' lw 0.1
set object 161 polygon from \
  15.3948, 10.9766 to \
  16.1052, 10.9766 to \
  16.1052, -33.8978 to \
  15.3948, -33.8978 to \
  15.3948, 10.9766 front fs empty border lc rgb '#549f' lw 0.1
set object 162 polygon from \
  15.4948, 11.1706 to \
  16.2052, 11.1706 to \
  16.2052, -33.961 to \
  15.4948, -33.961 to \
  15.4948, 11.1706 front fs empty border lc rgb '#549f' lw 0.1
set object 163 polygon from \
  15.5948, 11.2932 to \
  16.3052, 11.2932 to \
  16.3052, -33.9827 to \
  15.5948, -33.9827 to \
  15.5948, 11.2932 front fs empty border lc rgb '#549f' lw 0.1
set object 164 polygon from \
  15.6948, 11.3488 to \
  16.4052, 11.3488 to \
  16.4052, -33.9616 to \
  15.6948, -33.9616 to \
  15.6948, 11.3488 front fs empty border lc rgb '#549f' lw 0.1
set object 165 polygon from \
  15.7948, 11.3615 to \
  16.5052, 11.3615 to \
  16.5052, -33.867 to \
  15.7948, -33.867 to \
  15.7948, 11.3615 front fs empty border lc rgb '#549f' lw 0.1
set object 166 polygon from \
  15.8948, 11.3516 to \
  16.6052, 11.3516 to \
  16.6052, -33.7061 to \
  15.8948, -33.7061 to \
  15.8948, 11.3516 front fs empty border lc rgb '#549f' lw 0.1
set object 167 polygon from \
  15.9948, 11.2871 to \
  16.7052, 11.2871 to \
  16.7052, -33.4871 to \
  15.9948, -33.4871 to \
  15.9948, 11.2871 front fs empty border lc rgb '#549f' lw 0.1
set object 168 polygon from \
  16.0948, 11.1748 to \
  16.8052, 11.1748 to \
  16.8052, -33.218 to \
  16.0948, -33.218 to \
  16.0948, 11.1748 front fs empty border lc rgb '#549f' lw 0.1
set object 169 polygon from \
  16.1948, 11.0216 to \
  16.9052, 11.0216 to \
  16.9052, -32.9071 to \
  16.1948, -32.9071 to \
  16.1948, 11.0216 front fs empty border lc rgb '#549f' lw 0.1
set object 170 polygon from \
  16.2948, 10.8341 to \
  17.0052, 10.8341 to \
  17.0052, -32.5622 to \
  16.2948, -32.5622 to \
  16.2948, 10.8341 front fs empty border lc rgb '#549f' lw 0.1
set object 171 polygon from \
  16.3948, 10.6186 to \
  17.1052, 10.6186 to \
  17.1052, -32.1904 to \
  16.3948, -32.1904 to \
  16.3948, 10.6186 front fs empty border lc rgb '#549f' lw 0.1
set object 172 polygon from \
  16.4948, 10.3808 to \
  17.2052, 10.3808 to \
  17.2052, -31.7985 to \
  16.4948, -31.7985 to \
  16.4948, 10.3808 front fs empty border lc rgb '#549f' lw 0.1
set object 173 polygon from \
  16.5948, 10.1261 to \
  17.3052, 10.1261 to \
  17.3052, -31.3924 to \
  16.5948, -31.3924 to \
  16.5948, 10.1261 front fs empty border lc rgb '#549f' lw 0.1
set object 174 polygon from \
  16.6948, 9.85913 to \
  17.4052, 9.85913 to \
  17.4052, -30.9774 to \
  16.6948, -30.9774 to \
  16.6948, 9.85913 front fs empty border lc rgb '#549f' lw 0.1
set object 175 polygon from \
  16.7948, 9.58404 to \
  17.5052, 9.58404 to \
  17.5052, -30.5583 to \
  16.7948, -30.5583 to \
  16.7948, 9.58404 front fs empty border lc rgb '#549f' lw 0.1
set object 176 polygon from \
  16.8948, 9.30443 to \
  17.6052, 9.30443 to \
  17.6052, -30.1389 to \
  16.8948, -30.1389 to \
  16.8948, 9.30443 front fs empty border lc rgb '#549f' lw 0.1
set object 177 polygon from \
  16.9948, 9.02336 to \
  17.7052, 9.02336 to \
  17.7052, -29.7226 to \
  16.9948, -29.7226 to \
  16.9948, 9.02336 front fs empty border lc rgb '#549f' lw 0.1
set object 178 polygon from \
  17.0948, 8.74342 to \
  17.8052, 8.74342 to \
  17.8052, -29.3121 to \
  17.0948, -29.3121 to \
  17.0948, 8.74342 front fs empty border lc rgb '#549f' lw 0.1
set object 179 polygon from \
  17.1948, 8.46676 to \
  17.9052, 8.46676 to \
  17.9052, -28.9098 to \
  17.1948, -28.9098 to \
  17.1948, 8.46676 front fs empty border lc rgb '#549f' lw 0.1
set object 180 polygon from \
  17.2948, 8.19509 to \
  18.0052, 8.19509 to \
  18.0052, -28.5174 to \
  17.2948, -28.5174 to \
  17.2948, 8.19509 front fs empty border lc rgb '#549f' lw 0.1
set object 181 polygon from \
  17.3948, 7.92981 to \
  18.1052, 7.92981 to \
  18.1052, -28.1363 to \
  17.3948, -28.1363 to \
  17.3948, 7.92981 front fs empty border lc rgb '#549f' lw 0.1
set object 182 polygon from \
  17.4948, 7.67197 to \
  18.2052, 7.67197 to \
  18.2052, -27.7675 to \
  17.4948, -27.7675 to \
  17.4948, 7.67197 front fs empty border lc rgb '#549f' lw 0.1
set object 183 polygon from \
  17.5948, 7.42237 to \
  18.3052, 7.42237 to \
  18.3052, -27.4118 to \
  17.5948, -27.4118 to \
  17.5948, 7.42237 front fs empty border lc rgb '#549f' lw 0.1
set object 184 polygon from \
  17.6948, 7.18156 to \
  18.4052, 7.18156 to \
  18.4052, -27.0696 to \
  17.6948, -27.0696 to \
  17.6948, 7.18156 front fs empty border lc rgb '#549f' lw 0.1
set object 185 polygon from \
  17.7948, 6.94992 to \
  18.5052, 6.94992 to \
  18.5052, -26.7411 to \
  17.7948, -26.7411 to \
  17.7948, 6.94992 front fs empty border lc rgb '#549f' lw 0.1
set object 186 polygon from \
  17.8948, 6.72763 to \
  18.6052, 6.72763 to \
  18.6052, -26.4265 to \
  17.8948, -26.4265 to \
  17.8948, 6.72763 front fs empty border lc rgb '#549f' lw 0.1
set object 187 polygon from \
  17.9948, 6.51475 to \
  18.7052, 6.51475 to \
  18.7052, -26.1255 to \
  17.9948, -26.1255 to \
  17.9948, 6.51475 front fs empty border lc rgb '#549f' lw 0.1
set object 188 polygon from \
  18.0948, 6.31124 to \
  18.8052, 6.31124 to \
  18.8052, -25.838 to \
  18.0948, -25.838 to \
  18.0948, 6.31124 front fs empty border lc rgb '#549f' lw 0.1
set object 189 polygon from \
  18.1948, 6.11696 to \
  18.9052, 6.11696 to \
  18.9052, -25.5638 to \
  18.1948, -25.5638 to \
  18.1948, 6.11696 front fs empty border lc rgb '#549f' lw 0.1
set object 190 polygon from \
  18.2948, 5.93171 to \
  19.0052, 5.93171 to \
  19.0052, -25.3023 to \
  18.2948, -25.3023 to \
  18.2948, 5.93171 front fs empty border lc rgb '#549f' lw 0.1
set object 191 polygon from \
  18.3948, 5.75522 to \
  19.1052, 5.75522 to \
  19.1052, -25.0533 to \
  18.3948, -25.0533 to \
  18.3948, 5.75522 front fs empty border lc rgb '#549f' lw 0.1
set object 192 polygon from \
  18.4948, 5.58721 to \
  19.2052, 5.58721 to \
  19.2052, -24.8162 to \
  18.4948, -24.8162 to \
  18.4948, 5.58721 front fs empty border lc rgb '#549f' lw 0.1
set object 193 polygon from \
  18.5948, 5.42735 to \
  19.3052, 5.42735 to \
  19.3052, -24.5906 to \
  18.5948, -24.5906 to \
  18.5948, 5.42735 front fs empty border lc rgb '#549f' lw 0.1
set object 194 polygon from \
  18.6948, 5.27531 to \
  19.4052, 5.27531 to \
  19.4052, -24.3759 to \
  18.6948, -24.3759 to \
  18.6948, 5.27531 front fs empty border lc rgb '#549f' lw 0.1
set object 195 polygon from \
  18.7948, 5.13074 to \
  19.5052, 5.13074 to \
  19.5052, -24.1717 to \
  18.7948, -24.1717 to \
  18.7948, 5.13074 front fs empty border lc rgb '#549f' lw 0.1
set object 196 polygon from \
  18.8948, 4.9933 to \
  19.6052, 4.9933 to \
  19.6052, -23.9775 to \
  18.8948, -23.9775 to \
  18.8948, 4.9933 front fs empty border lc rgb '#549f' lw 0.1
set object 197 polygon from \
  18.9948, 4.86264 to \
  19.7052, 4.86264 to \
  19.7052, -23.7927 to \
  18.9948, -23.7927 to \
  18.9948, 4.86264 front fs empty border lc rgb '#549f' lw 0.1
set object 198 polygon from \
  19.0948, 4.73843 to \
  19.8052, 4.73843 to \
  19.8052, -23.617 to \
  19.0948, -23.617 to \
  19.0948, 4.73843 front fs empty border lc rgb '#549f' lw 0.1
set object 199 polygon from \
  19.1948, 4.62034 to \
  19.9052, 4.62034 to \
  19.9052, -23.4499 to \
  19.1948, -23.4499 to \
  19.1948, 4.62034 front fs empty border lc rgb '#549f' lw 0.1
set object 200 polygon from \
  19.2948, 4.50805 to \
  20, 4.50805 to \
  20, -23.2909 to \
  19.2948, -23.2909 to \
  19.2948, 4.50805 front fs empty border lc rgb '#549f' lw 0.1
set object 201 polygon from \
  19.3948, 4.40126 to \
  20, 4.40126 to \
  20, -23.1395 to \
  19.3948, -23.1395 to \
  19.3948, 4.40126 front fs empty border lc rgb '#549f' lw 0.1
set object 202 polygon from \
  19.4948, 4.29968 to \
  20, 4.29968 to \
  20, -22.9955 to \
  19.4948, -22.9955 to \
  19.4948, 4.29968 front fs empty border lc rgb '#549f' lw 0.1
set object 203 polygon from \
  19.5948, 4.20304 to \
  20.1, 4.20304 to \
  20.1, -22.8585 to \
  19.5948, -22.8585 to \
  19.5948, 4.20304 front fs empty border lc rgb '#549f' lw 0.1
set object 204 polygon from \
  19.6948, 4.11107 to \
  20.2, 4.11107 to \
  20.2, -22.728 to \
  19.6948, -22.728 to \
  19.6948, 4.11107 front fs empty border lc rgb '#549f' lw 0.1
set object 205 polygon from \
  19.5935, 4.59247 to \
  20, 4.59247 to \
  20, -23.2118 to \
  19.5935, -23.2118 to \
  19.5935, 4.59247 front fs empty border lc rgb '#549f' lw 0.1
set object 206 polygon from \
  19.6935, 5.02799 to \
  20, 5.02799 to \
  20, -23.6262 to \
  19.6935, -23.6262 to \
  19.6935, 5.02799 front fs empty border lc rgb '#549f' lw 0.1
set object 207 polygon from \
  19.7935, 5.51379 to \
  20, 5.51379 to \
  20, -24.1147 to \
  19.7935, -24.1147 to \
  19.7935, 5.51379 front fs empty border lc rgb '#549f' lw 0.1
set object 208 polygon from \
  19.8935, 6.02169 to \
  20, 6.02169 to \
  20, -24.6547 to \
  19.8935, -24.6547 to \
  19.8935, 6.02169 front fs empty border lc rgb '#549f' lw 0.1
set object 209 polygon from \
  19.9935, 6.52985 to \
  20, 6.52985 to \
  20, -25.227 to \
  19.9935, -25.227 to \
  19.9935, 6.52985 front fs empty border lc rgb '#549f' lw 0.1
plot - NaN notitle

