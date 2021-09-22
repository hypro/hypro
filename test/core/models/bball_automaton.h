auto autString = R"HYPROAUT(
hybrid reachability {

 state var x,v

 setting
 {
  fixed steps 0.01
  time 3
  remainder estimation 1e-5
  identity precondition
  gnuplot octagon v,x
  fixed orders 5
  cutoff 1e-15
  precision 128
  output bouncing_ball
  max jumps 3
  print on
 }

 modes
 {
  l0
  {
   poly ode 1
   {
    x' = v
    v' = -9.81
   }

   inv
   {
    x >= 0
   }
  }
 }

 jumps
 {
  l0 -> l0
  guard { x = 0 v <= 0 }
  reset { v' := -0.75*v }
  parallelotope aggregation {}
 }

 init
 {
  l0
  {
   x in [10,10.2]
   v in [0,1]
  }
 }
}

)HYPROAUT";
