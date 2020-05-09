from cs50 import get_int


def main():  # define main function
    height = get_height()
    for h in range(height):  # funky stuff
        print(" " * (height - 1 - h), end="")
        print("#" * (h + 1), end="")
        print("  ", end="")
        print("#" * (h + 1), end="")
        print("")


def get_height():  # define function to get height between 1 and 8 inclusive
    while True:
        n = get_int("Height:")
        if n > 0 and n < 9:
            return(n)


main()  # call main function
