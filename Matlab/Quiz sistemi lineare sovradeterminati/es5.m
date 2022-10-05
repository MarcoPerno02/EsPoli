% Il coefficiente angolare della retta che approssima nel senso dei minimi quadrati l'insieme di punti:
% x=[0.2 1.14 0.54 0.87 1.25 2.36 0.19 0.54 0.51 0.33]
% y=[1.25 2.36 2.58 1.87 2.68 3.41 0.65 0.47 1.36 1.25 ]
% vale:
x=[0.2 1.14 0.54 0.87 1.25 2.36 0.19 0.54 0.51 0.33];
y=[1.25 2.36 2.58 1.87 2.68 3.41 0.65 0.47 1.36 1.25 ];
c = polyfit(x, y, 1)