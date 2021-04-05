from main_generator import Generator
import numpy as np
from matplotlib import pyplot

M1 = 75
M2 = 1_269_565_489_152  # 1051 * 2^(25+1) * 18
M1_2 = 64
M2_2 = 314_041

A1 = 16
A1_2 = 17
A2 = 181
A2_2 = 378

C1 = 7
C1_2 = 11
C2 = 7
C2_2 = 11

N = 100_000


class MarsallieGenerator:

    def __init__(self, n, a1, c1, a2, c2, m1, m2, x01, x02):
        self.first_sensor = Generator(m1, x01, a1, c1)
        self.second_sensor = Generator(m2, x02, a2, c2)
        self.n = n
        self.table = self.generate()

    def generate(self):
        result = []
        for i in range(0, self.n):
            result.append(self.first_sensor.next())
        return result

    def next(self):
        rand_index = int(self.second_sensor.next() * self.n)
        element = self.table[rand_index]
        self.table[rand_index] = self.first_sensor.next()
        return element


if __name__ == '__main__':
    generator_1 = MarsallieGenerator(N, A1, C1, A1_2, C1_2, M1, M1_2, 52, 35)
    result_first = []
    with open('marsalie1.txt', 'w') as file_1:
        for _ in range(N):
            randint = generator_1.next()
            result_first.append(randint)
            print(randint, file=file_1)

    res = result_first.copy()
    res.remove(result_first[0])
    res.append(result_first[0])
    pyplot.scatter(res, result_first, 0.1, 'r')
    pyplot.show()
