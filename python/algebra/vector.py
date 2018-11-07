import math


class Vector(object):
    def __init__(self, coordinates):
        try:
            if not coordinates:
                raise ValueError
            self.coordinates = tuple(coordinates)
            self.dimension = len(coordinates)

        except ValueError:
            raise ValueError('The coordinates can\'t be empty')

        except TypeError:
            raise TypeError('The coordinates must be iterable')

    def __str__(self):
        return 'Vector: {}'.format(self.coordinates)

    def __eq__(self, v):
        return self.coordinates == v.coordinates

    def plus(self, v):
        return tuple(["%0.3f" % (x + y) for x, y in zip(self.coordinates, v)])

    def minus(self, v):
        return tuple(["%0.3f" % (x - y) for x, y in zip(self.coordinates, v)])

    def multiply(self, v):
        return tuple(["%0.3f" % x * v for x in self.coordinates])

    def magnitude(self):
        return math.sqrt(sum(x**2 for x in self.coordinates))

    def normalization(self):
        1/self.magnitude()
