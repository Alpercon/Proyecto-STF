set multiplot
set size 1,0.5
set title "Función Normal"

set origin 0.0,0.5
plot "normal.txt" with lines title "f(x)" lc rgb '#2c718e'

set title "Función Aproximada mediante STF"
set origin 0.0,0.0
plot "stf.txt" with lines title "f(x)" lc rgb '#5cc863' 


reset
