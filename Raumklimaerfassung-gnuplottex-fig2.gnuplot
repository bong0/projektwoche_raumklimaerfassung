set terminal latex
set output 'Raumklimaerfassung-gnuplottex-fig2.tex'
unset key
set samples 1024
set format "%g"
set yrange [0:50]
set xrange [0:2.5]
set xlabel "Ladezeit [s]"
set ylabel "\\begin{sideways}Temperatur [^{\\degree}C]\\end{sideways}"
set multiplot
a = 0.018771
b = 6.96983
c =  822.037
T(t) = (( -(b/(2.0)) + sqrt( (b*b)/4 + ( t/( 1.03e-3*log(3.0) ) -c )*a ) )/a)
plot T(x)
plot T(x)-7 lt 4
unset multiplot
