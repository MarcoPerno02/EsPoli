import numpy as np
import matplotlib.pyplot as plt
# Filtro passa-basso reale
x = np.array([0.1, 0.3, 2, 5, 9, 12, 15, 15.5, 15.7, 15.9,
             16.1, 16.3, 16.8, 19.8, 22.8, 26.8, 29.8]) * 1000

v_in = np.array([816, 824, 816, 808, 808, 808, 800, 800, 800,
                800, 800, 800, 800, 792, 792, 792, 792])  # * 0.001

delta_v_in = v_in * (1/20 + 0.03)

v_out = np.array([820, 816, 816, 792, 712, 664, 608, 584, 584,
                 584, 584, 584, 568, 528, 480, 424, 408])  # * 0.001
delta_v_out = v_out * (1/20 + 0.03)

Hs = 20*np.log10(v_out/v_in)
delta_Hs = np.abs(Hs * ((delta_v_out / v_out) + (delta_v_in / v_in)))

print(delta_Hs)


plt.errorbar(x, Hs, delta_Hs,
             label='uplims=True, lolims=True', color='blue', ecolor='lightblue', elinewidth=3, capsize=0)
plt.xscale("log", base=10)
plt.title("Filtro passa-basso misurato")
plt.show()

# Filtro passa-alto reale
x = np.array([2, 5, 9, 12, 15, 15.5, 15.7, 15.9, 16.1, 16.3,
             16.8, 19.8, 22.8, 26.8, 29.8, 50, 100, 1000]) * 1000

v_in = np.array([816, 816, 808, 808, 808, 808, 808, 808, 808,
                800, 800, 800, 800, 800, 792, 792, 792, 760])  # * 0.001

delta_v_in = v_in * (1/20 + 0.03)

v_out = np.array([93.6, 226, 376, 456, 520, 536, 536, 536, 536,
                 544, 552, 584, 632, 664, 680, 736, 760, 760])  # * 0.001
delta_v_out = v_out * (1/20 + 0.03)

Hs = 20*np.log10(v_out/v_in)
delta_Hs = np.abs(Hs * ((delta_v_out / v_out) + (delta_v_in / v_in)))

print(delta_Hs)


plt.errorbar(x, Hs, delta_Hs,
             label='uplims=True, lolims=True', color='blue', ecolor='lightblue', elinewidth=3, capsize=0)
plt.xscale("log", base=10)
plt.title("Filtro passa-alto misurato")
plt.show()
