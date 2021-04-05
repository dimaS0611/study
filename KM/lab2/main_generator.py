from matplotlib import pyplot

M1 = 71
# i simple number after 1000 = 1171
M2 = 1_414_520_635_392  # 1051 * 2^(25 + 1) * 18

A1 = 7
B1 = 9

A2 = 1051 * 4 * 3 + 1
B2 = 9


class Generator:
    def __init__(self, m: int, x0: int, a: int, c: int):
        self.current = x0
        self.m = m
        self.a = a
        self.c = c

    def next(self):
        self.current = (self.current * self.a + self.c) % self.m
        return self.current / self.m


if __name__ == '__main__':
    generator_1 = Generator(M1, 52, A1, B1)
    result_second = []
    with open('main1.txt', 'w') as file_1:
        for _ in range(1000):
            randint = generator_1.next()
            result_second.append(randint)
            print(randint, file=file_1)

    generator_2 = Generator(M2, 1_269_565_489_152, A2, B2)
    result_second = []

    with open('main2.txt', 'w') as file_2:
        for _ in range(20000):
            randint = generator_2.next()
            result_second.append(randint)
            print(randint, file=file_2)

    res = result_second.copy()
    res.remove(result_second[0])
    res.append(result_second[0])
    pyplot.scatter(res, result_second, 0.1, 'r')
    pyplot.show()
