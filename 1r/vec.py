from math import sqrt

WIDTH = 1920
HEIGHT = 1080


class Point2d:

    # Magic funcs

    # нет проверки в конструкторе на отрицательные числа
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def __str__(self):
        return f'(x,y): ({self.x}, {self.y})'

    def __repr__(self):
        return f'{self.x}, {self.y}'

    def __len__(self):
        return 2

    def __getitem__(self, index):
        if index == 0:
            return self.x
        if index == 1:
            return self.y
        else:
            raise ValueError("Sequence out of range!")

    def __setitem__(self, index, item):
        if index == 0:
            self.x = item
        if index == 1:
            self.y = item
        else:
            raise ValueError("Sequence out of range!")

    # Properties

    @property
    def x(self):
        return self.__x

    @x.setter
    def x(self, x):
        if not (isinstance(x, int) and 0 < x < WIDTH):
            raise ValueError('x have to be positive')
        self.__x = x
        return self.__x

    @property
    def y(self):
        return self.__y

    @y.setter
    def y(self, y):
        if not (isinstance(y, int) and 0 < y < HEIGHT):
            raise ValueError('y have to be positive')
        self.__y = y
        return self.__y


class Vec2d:
    def __init__(self, *args):
        if len(args) != 2:
            raise ValueError("Wrong amount of agruments!")

        if isinstance(args[0], int) and isinstance(args[1], int):
            self.x = args[0]
            self.y = args[1]
        elif isinstance(args[0], Point2d) and isinstance(args[1], Point2d):
            self.x = args[1].x - args[0].x
            self.y = args[1].y - args[0].y
        else:
            raise ValueError("Wrong type of arguments!")

    # MAGIC FUNC ---

    def __str__(self):
        return f'[x,y]: [{self.x}, {self.y}]'

    def __repr__(self):
        return f'{self.x}, {self.y}'

    def __len__(self):
        return 2

    def __getitem__(self, index):
        if index == 0:
            return self.x
        if index == 1:
            return self.y
        else:
            raise IndexError("Sequence out of range!")

    def __setitem__(self, index, item):
        if index == 0:
            self.x = item
            return self.x
        if index == 1:
            self.y = item
            self.y
        else:
            raise ValueError("Sequence out of range!")

    def __iter__(self):
        yield self.x
        yield self.y

    def __eq__(self, other):
        if isinstance(other, Vec2d):
            return self.x == other.x and self.y == other.y
        return False

    def __abs__(self) -> float:
        return sqrt(self.x ** 2 + self.y ** 2)

    # Properties ---

    @property
    def x(self):
        return self.__x

    @x.setter
    def x(self, x):
        if not (isinstance(x, int)):
            raise ValueError('argument x in vec have to be an integer!')
        self.__x = x
        return self.x

    @property
    def y(self):
        return self.__y

    @y.setter
    def y(self, y):
        if not (isinstance(y, int)):
            raise ValueError('argument y in vec have to be an integer!')
        self.__y = y
        return self.y

    # Math ---

    def __add__(self, other):
        if isinstance(other, int):
            return Vec2d(self.x + other, self.y+other)
        raise ValueError(f"There is no 'add function' overload for {type(other)}")

    def __mul__(self, other):
        if isinstance(other, int):
            return Vec2d(self.x * other, self.y * other)
        raise ValueError(f"There is no 'add function' overload for {type(other)}")

    def __truediv__(self, other):
        if isinstance(other, int) and not (other == 0):
            return Vec2d(self.x / other, self.y / other)

    def dotProduct(self, vec) -> int:
        return (self.x * vec.x) + (self.y * vec.y)

    def crossProduct(self):
        return Vec2d(self.x, -self.y)

    def TripleProduct(self, other):
        # return self.dotProduct(self.crossProduct(self), other)
        return self.dotProduct( other.dotProduct() )

    # class metgods

    @classmethod
    def StaticdotProduct(cls, lhs : "Vec2d", rhs : "Vec2d"):
        if isinstance(lhs, Vec2d) and isinstance(rhs, Vec2d):
            return (lhs.x * rhs.x) + (lhs.y * rhs.y)
        raise ValueError("Dot product require Vec2d")

    @classmethod
    def StaticcrossProduct(cls, vec):
        if isinstance(vec, Vec2d):
            return Vec2d(vec.x, -vec.y)
        raise ValueError("Cross product require Vec2d")



p1 = Point2d( -100, -100 );

x1 = int(input("Entry x: "))
y1 = int(input("Entry y: "))

v = Vec2d(x1, y1)
print(v)

v = v * 2

for a in v:
    print(a)
