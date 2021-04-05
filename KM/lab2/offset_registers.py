from matplotlib import pyplot

N = 50000


def get_bit(value, n):
    return (value >> n & 1) != 0


def set_bit(value, n):
    return value | (1 << n)


def clear_bit(value, n):
    return value & ~(1 << n)


class OffsetRegister:

    def __init__(self, initial, i1: int, i2: int, length_bits: int):
        self.current = initial
        self.i1 = i1
        self.i2 = i2
        self.length = length_bits

    def next(self):
        position_first = self.length - self.i1
        position_second = self.length - self.i2
        first = get_bit(self.current, position_first)
        second = get_bit(self.current, position_second)
        new = first ^ second
        last = get_bit(self.current, self.length - 1)
        result = self.current >> 1
        if new:
            result = set_bit(result, self.length - 1)
        self.current = result
        return last


if __name__ == "__main__":
    register = OffsetRegister(16, 5, 3, 5)
    first_register = []
    for i in range(0, N):
        numb = 0
        for j in range(0, 7):
            numb += int(register.next())
            numb = numb << 1
        first_register.append(numb)

    register = OffsetRegister(32, 10, 7, 10)
    second_register = []
    current = 1023
    for i in range(0, N):
        numb = 0
        for j in range(0, 7):
            i = register.next()
            if register.next():
                numb += 1
            numb = numb << 1
        second_register.append(numb)

    res = first_register.copy()
    res.remove(first_register[0])
    res.append(first_register[0])
    pyplot.scatter(res, first_register, 0.1, 'r')
    pyplot.show()

    res = second_register.copy()
    res.remove(second_register[0])
    res.append(second_register[0])
    pyplot.scatter(res, second_register, 0.1, 'r')
    pyplot.show()
