auto autString = R"HYPROAUT(
hybrid reachability
{
 state var x,y,z

 setting
 {
  fixed steps 0.01
  time 3
  remainder estimation 1e-5
  identity precondition
  gnuplot octagon x,y
  QR precondition
  adaptive orders { min 3, max 11}
  fixed orders 5
  cutoff 1e-15
  precision 128
  output testautomaton
  max jumps 3
  print on
 }

 modes
 {
  l0
  {
   poly ode 1
   {
    x' = 1
    y' = 2*x
    z' = 2*x - 3 - 4*y - z
   }

   inv
   {
    x >= 0
    y in [2,3]
   }
  }

  l1
  {
   poly ode 1
   {
    x' = 1
    y' = 1
    z' = 1
   }
  }

  l2
  {
   poly ode 1
   {
    x' = 1
    y' = 1
    z' = 1
   }
   inv
   {
   }
  }
 }

 jumps
 {
  l0 -> l0
  guard { x = 0 y <= 0 }
  reset { y' := -0.75*y }
  parallelotope aggregation {}

  l0 -> l0
  guard { x = 0 y <= 0 }
  reset { y' := -0.75*y }
  parallelotope aggregation {}

  l0 -> l1
  guard { x in [2,3] }
  reset { y' := -0.75*y }
  parallelotope aggregation {}
 }

 init
 {
  l0
  {
   x in [10,10.2]
   y in [0,0]
   z in [1,1]
  }
 }

}

#unsafe set
#{
#  l
#  {
#   #x in [4,6]
#   #y in [-2.5,0]
#  }
#}
)HYPROAUT";
