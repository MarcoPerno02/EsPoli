%Si costruisca la parabola p(x) approssimante nel senso dei minimi quadrati la nuvola di punti con coordinate
%x=[-2 -1.3 -1 -0.7 -0.4 -0.1]
%y=[0.3 0.5 1.5 1.3 0.8 0.1]
%Quanto vale, approssimando, la quantita' |p(3)-1.5|?
x=[-2 -1.3 -1 -0.7 -0.4 -0.1];
y=[0.3 0.5 1.5 1.3 0.8 0.1];
c = polyfit(x, y, 2);
abs(polyval(c, 3)-1.5)