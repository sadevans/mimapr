import matplotlib.pyplot as plt

t = []
phi = []
count = 0
with open("out.txt") as my_file:
    first_line = my_file.readline().split(" ")[:-1]

    count = len(first_line) - 1
    for i in range(count):
        phi.append([])
    for line in my_file:
        a = line.split(" ")[:-1]
        t.append(float(a[0]))
        for i in range(1, len(a)):
            phi[i-1].append(float(a[i]))

fig, ax = plt.subplots(1, 1, figsize=(10, 10))
#for i in range(count):
ax.plot(t, phi[0], linewidth=1, label = r'$\varphi_1$', color="purple")
ax.plot(t, phi[2], linewidth=1, label = r'$\varphi_3$', color="blue")
ax.plot(t, phi[4], linewidth=1, label = r'$\varphi_5$', color="red")

ax.grid()
ax.legend()
ax.set_xlabel("t", fontsize=20)
ax.set_ylabel("value", fontsize=20)
plt.savefig(f'./figs/graph.png')

plt.show()