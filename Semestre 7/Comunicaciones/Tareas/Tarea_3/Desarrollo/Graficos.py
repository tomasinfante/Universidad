import numpy as np
import matplotlib.pyplot as plt

W = 0.1

tau = np.linspace(-20, 20, 50000)

# sinc normalizada
def sinc(x):
    return np.where(x == 0, 1, np.sin(np.pi*x)/(np.pi*x))

RY = (1/20) * sinc(W*tau) * np.cos(20*np.pi*W*tau)

plt.figure()
plt.plot(tau, RY)
plt.xlabel(r'$\tau$')
plt.ylabel(r'$R_Y(\tau)$')
plt.title(r'$R_Y(\tau)=\frac{1}{20}\mathrm{sinc}(W\tau)\cos(20\pi W\tau)$')
plt.grid(True)
plt.savefig("Grafico_1.png", dpi = 500)
plt.show()