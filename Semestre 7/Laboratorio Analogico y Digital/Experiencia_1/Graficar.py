import matplotlib.pyplot as plt

freq = []
gain = []
phase = []

with open("bode.txt", "r") as f:
    next(f)
    
    for line in f:
        parts = line.split("\t")
        
        fval = float(parts[0])
        
        values = parts[1].strip()[1:-1]
        g, p = values.split(",")
        
        g = float(g.replace("dB",""))
        p = float(p[:-1])  # quitar símbolo raro de grados
        
        if p > 0:
            p = p - 360
        
        freq.append(fval)
        gain.append(g)
        phase.append(p)

fig, (ax1, ax2) = plt.subplots(2,1)

ax1.semilogx(freq, gain)
ax1.set_ylabel("Ganancia (dB)")
ax1.grid(True, which="both")

ax2.semilogx(freq, phase)
ax2.set_ylabel("Fase (°)")
ax2.set_xlabel("Frecuencia")
ax2.grid(True, which="both")
plt.savefig("Bode", dpi = 500)
plt.show()