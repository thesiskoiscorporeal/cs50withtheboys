from cs50 import get_float


def main():
    n = coinage(0.25, 0.10, 0.05, 0.01)
    print(n)


def coinage(*denom):
    n = 0
    owed = round(100 * get_positive_float("Change owed: "))  # prompt user for input # round to avoud floating point imprecision
    for i in range(len(denom)):
        while owed >= round(100 * denom[i]):
            n += 1
            owed -= round(100 * denom[i])
    return n


def get_positive_float(prompt):  # define function to only accept positive float input
    while True:
        n = get_float(prompt)
        if n > 0:
            break
    return n


main()
