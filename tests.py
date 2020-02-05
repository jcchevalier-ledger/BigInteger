def bitfield(n):
    bit_array = [int(digit) for digit in bin(n)[2:]]
    while len(bit_array) != 32:
        bit_array = [0] + bit_array
    return bit_array


def test():
    f = open("data.txt", "r")
    results = []
    for element in f:
        number = []
        array = element.split()
        length = array.__len__()
        for i in range(0, length):
            number += bitfield(int(array[i]))
        converted_number = int("".join(str(x) for x in number), 2)
        results.append(converted_number)
    print("a                      =", results[0])
    print("b                      =", results[1])
    print("a * b                  =", results[2])
    print("Expected result        =", results[0] * results[1])
    return 0


if __name__ == "__main__":
    test()
