"""
import numpy as np
import matplotlib.pyplot as plt
# Filtro passa-basso reale
x = np.array([0.1, 0.3, 2, 5, 9, 12, 15, 15.5, 15.7, 15.9,
             16.1, 16.3, 16.8, 19.8, 22.8, 26.8, 29.8]) * 1000

Hsarg = np.array([0.0, -0.1, -6.5, -16.2, -27.5, -34.6, -40.5, -
                 41.5, -41.8, -42.4, -42.7, -43.0, -44.0, -48.5, -52.2, -56.0, -59.2])

delta_Hsarg = np.array([0.0, 0.0, 0.3, 0.8, 1.5, 1.9,
                       2.3, 2.4, 2.4, 2.4, 2.4, 2.5, 2.5, 2.9, 3.2, 3.6, 3.9])


plt.errorbar(x, Hsarg, delta_Hsarg,
             label='uplims=True, lolims=True', color='blue', ecolor='lightblue', elinewidth=3, capsize=10)
plt.xscale("log", base=10)
plt.title("Fase Filtro passa-basso misurato")
plt.show()

# Filtro passa-alto reale
x = np.array([2, 5, 9, 12, 15, 15.5, 15.7, 15.9, 16.1, 16.3,
             16.8, 19.8, 22.8, 26.8, 29.8, 50, 100, 1000]) * 1000

Hsarg = np.array([82, 73, 61, 56, 48, 48, 48, 47, 48,
                 46, 47, 40, 37, 33, 32, 22, 9, 0])
delta_Hsarg = np.array([4, 5, 7, 8, 9, 5, 5, 5, 5, 5, 5, 6, 6, 6, 7, 8, 12, 77])

print(delta_Hsarg)


plt.errorbar(x, Hsarg, delta_Hsarg,
             label='uplims=True, lolims=True', color='blue', ecolor='lightblue', elinewidth=3, capsize=10)
plt.xscale("log", base=10)
plt.title("faseFiltro passa-alto misurato")
plt.show()

"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline
from scipy import signal
from scipy import pi, log10, zeros
from scipy.interpolate import InterpolatedUnivariateSpline

R6 = 1 * 10**3
C4 = 10 * 10**(-9)
f = np.logspace(3, 5, 10000)
s = 1j * 2 * pi * f
mod = zeros(len(s))

mod = (R6)/(R6+1/(s * C4))

#mod = np.angle(mod)

# Conversione della fase in gradi
#mod = np.degrees(mod)


# Dati filtro passa basso
x = np.array([2,
5, 
9,
12, 
15,
15.5, 
15.7, 
15.9, 
16.1, 
16.3, 
16.8, 
19.8, 
22.8, 
26.8, 
29.8, 
50,
100])*10e2
y = np.array([-18.8, 
-11.2, 
-6.6, 
-5.0, 
-3.8, 
-3.6, 
-3.6, 
-3.6, 
-3.6, 
-3.3, 
-3.2, 
-2.7, 
-2.0, 
-1.6, 
-1.3, 
-0.6, 
-0.4 ])
delta = np.array([2.6, 
1.5, 
1.2, 
1.1, 
1.1, 
1.1, 
1.1, 
1.1, 
1.1, 
1.1, 
1.1, 
1.0, 
1.0, 
1.0, 
1.0, 
1.0, 
1.0])




# Trasforma l'asse x con il logaritmo in base 10
x_log = np.log10(x)

# Creazione di una spline cubica
cs = InterpolatedUnivariateSpline(x_log, y, k=2)

# Creazione di nuovi dati più fini per una rappresentazione più fluida
x_new_log = np.linspace(min(x_log), max(x_log), 1000)
x_new = 10 ** x_new_log
y_new = cs(x_new_log)
# Trasforma l'asse x con il logaritmo in base 10
x_new_log_extended = np.linspace(3.3, 5, 1000)  # estendi fino a 10^8
x_new_extended = 10 ** x_new_log_extended
y_new_extended = cs(x_new_log_extended)

# Aggiungi questo codice dopo il plot del Bode Plot
plt.figure()

# Bode Plot
plt.semilogx(f, 20*log10(mod), linewidth=2, label='Funizione di trasferimento')

# Interpolazione
plt.semilogx(x_new_extended, y_new_extended, linewidth=1.5, label='Interpolazione calcolata dalle misurazioni', linestyle='dashed', color='red')

# Punti originali
plt.errorbar(x, y, delta, linestyle='None', label='Incertezze', ecolor='red', elinewidth=1, capsize=5)

# Plot dei punti scatter
plt.scatter(x, y, color='green', marker='o', label='Valori misurati')

# Titoli e legenda
plt.title('|H(s)| E Interpolazione - Filtro PassaAlto')
plt.ylabel('Magnitude (dB)')
plt.xlabel('Frequency (Hz)')
plt.grid(True)
plt.legend()

# Mostra il plot
plt.show()
a=4