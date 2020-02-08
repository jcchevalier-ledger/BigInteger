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
    a = results[0]
    b = results[1]
    r = results[2]
    v = results[3]
    n = results[4]
    result = results[5]

    s = a * r * r
    t = (s * v) % r
    m = s + t * n
    u = m / r
    if u >= n:
        u = u - n
    print(int(u))

    s = int(u) * 1
    t = (s * v) % r
    m = s + t * n
    u = m / r
    if u >= n:
        u = u - n
    print(int(u))

    print(result)
    f.close()
    return


if __name__ == "__main__":
    test()
