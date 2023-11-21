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
