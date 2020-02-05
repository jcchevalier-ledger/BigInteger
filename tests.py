def bitfield(n):
    bit_array = [int(digit) for digit in bin(n)[2:]]
    while len(bit_array) != 32:
        bit_array = [0] + bit_array
    return bit_array


if __name__ == "__main__":
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
    print("modulo                 =", results[2])
    print("a - b                  =", results[0] - results[1])
    print("result                 =", results[3])
    print("modular addition       =", (results[0] + results[2]) - results[1])
    print("modular substraction   =", (results[0] - results[1]) % results[2])
