import numpy as np

def fun(x):
	return 1 / (x**4 + 25)

def main():
	with open("torpedo_x.txt", "w") as f:
		t = np.linspace(0, 2, 5)
		x = fun(t)
		for i in range(len(t)):
			print(f"{t[i]} {x[i]}", end=" ", file=f)


def test():
	print(fun(1.75))


if __name__ == "__main__":
	test()
