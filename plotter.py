import matplotlib.pyplot as plt
def get_cmap(n, name='hsv'):
    '''Returns a function that maps each index in 0, 1, ..., n-1 to a distinct 
    RGB color; the keyword argument name must be a standard mpl colormap name.'''
    return plt.cm.get_cmap(name, n)
t = []
phi = []
count = 0
with open("out.txt") as my_file:
    first_line = my_file.readline().split(" ")[:-1]
    print(first_line)

    count = len(first_line) - 1
    for i in range(count):
        phi.append([])
    print(phi)
    for line in my_file:
        a = line.split(" ")[:-1]
        t.append(float(a[0]))
        for i in range(1, len(a)):
            phi[i-1].append(float(a[i]))

cmap = get_cmap(30)

for i in range(count):
    fig, ax = plt.subplots(1, 1, figsize=(18, 10))
    ax.plot(t, phi[i], linewidth=1, color=cmap(i))
    ax.grid()
    ax.set_xlabel("t", fontsize=20)
    ax.set_ylabel(f"phi_{i+1}", fontsize=20)
    plt.show()