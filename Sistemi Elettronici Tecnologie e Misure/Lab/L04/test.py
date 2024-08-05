
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline
from scipy import signal
from scipy import pi, log10, zeros

Av = 9.33
Ri = 10 * 10**3
Ru = 10**3
C1 = 13.3 * 10**(-9)
C2 = 10.0 * 10**(-9)
f = np.logspace(-1, 8, 10000)
s = 1j * 2 * pi * f
mod = zeros(len(s))

for x in range(len(s)):
    mod[x] = Av * Ri * C1 * (abs(s[x]) / abs(1 + s[x] * Ri * C1)) * (1 / abs(1 + s[x] * Ru * C2))



# Dati
x = np.array([300, 1000, 3000, 10000, 30000, 100000, 300000, 1000000])
y = np.array([6.10, 15.22, 18.32, 17.76, 13.01, 3.64, -7.54, -22.19])

# Trasforma l'asse x con il logaritmo in base 10
x_log = np.log10(x)

# Creazione di una spline cubica
cs = CubicSpline(x_log, y)

# Creazione di nuovi dati più fini per una rappresentazione più fluida
x_new_log = np.linspace(min(x_log), max(x_log), 1000)
x_new = 10 ** x_new_log
y_new = cs(x_new_log)
# Trasforma l'asse x con il logaritmo in base 10
x_new_log_extended = np.linspace(1.5, 7, 1000)  # estendi fino a 10^8
x_new_extended = 10 ** x_new_log_extended
y_new_extended = cs(x_new_log_extended)

# Aggiungi questo codice dopo il plot del Bode Plot
plt.figure()

# Bode Plot
plt.semilogx(f, 20 * log10(mod), label='Bode Plot')

# Interpolazione
plt.semilogx(x_new_extended, y_new_extended, label='Interpolation Based On Our Measurements', linestyle='dashed', color='red')

# Punti originali
plt.scatter(x, y, label='Measurements Data', color='blue')

# Titoli e legenda
plt.title('Bode Plot with Extended Interpolation and Measurements Data')
plt.ylabel('Magnitude (dB)')
plt.xlabel('Frequency (Hz)')
plt.grid(True)
plt.legend()

# Mostra il plot
plt.show()