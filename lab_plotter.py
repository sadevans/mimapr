import matplotlib.pyplot as plt


with open('lin_40.txt') as f:
    lines = f.readlines()
    x = [float(line.split()[0]) for line in lines]
    anal = [float(line.split()[2]) for line in lines]
    solv = [float(line.split()[4]) for line in lines]
    abs = [float(line.split()[6]) for line in lines]


# Plotting both the curves simultaneously
plt.plot(x[:-1], anal[:-1], color='r', label='Аналитическое решение')
plt.plot(x[:-1], solv[:-1], color='g', label='МКЭ-решение')

# Naming the x-axis, y-axis and the whole graph
# plt.xlabel("Angle")
# plt.ylabel("Magnitude")
plt.title("Резльтат работы пррограммы для 20 КЭ")

# Adding legend, which helps us recognize the curve according to it's color
plt.legend()

# To load the display window
plt.show()