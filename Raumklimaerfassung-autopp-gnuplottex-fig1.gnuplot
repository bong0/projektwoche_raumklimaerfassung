set terminal latex
set output 'Raumklimaerfassung-autopp-gnuplottex-fig1.tex'
unset key
  set samples 1024
set format "%g"
set autoscale
set xlabel "Temperatur an $R_1$ [$^{\\degree}C$]"
set ylabel "\\begin{sideways}Ladezeit [$ms$]\\end{sideways}"
f(r) = (((log(1.0/3.0)*r*(1030e-6))*-1)*1000)
plot [0:50] [800:1500] "res/kty_81-121.data" using 1:(f($4)) smooth csplines with lines
