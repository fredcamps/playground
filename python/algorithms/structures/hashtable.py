class HashTable:

    def __init__(self, size=10):
        self.size = size
        self.keys = [None] * self.size
        self.values = [None] * self.size

    def __getitem__(self, key):
        return self.get(key)

    def __setitem__(self, key, value):
        return self.insert(key, value)

    def __repr__(self):
        for k, v in zip(self.keys, self.values):
            if k is not None:
                print('{0} => {1}'.format(k, v if not None else ''))
        return ''

    def _has_key(self, key):
        return self.keys[key] is not None

    def _hash(self, key):
        return sum([ord(c) for c in key]) % self.size

    def _rehash(self, hashed_key):
        """Method for collision resolution"""
        return (hashed_key + 1) % self.size

    def _find(self, key):
        hashed = self._hash(str(key))
        first_hash = hashed
        value = None
        while self.keys[hashed] is not None and value is None:
            if self.keys[hashed] == key:
                 value = self.values[hashed]
                 break

            hashed = self._rehash(hashed)
            if hashed == first_hash:
                break

        return (hashed, value)

    def insert(self, key, value):
        hashed = self._hash(str(key))
        if not self._has_key(hashed):
            self.keys[hashed] = key
            self.values[hashed] = value
        else:
            while self.keys[hashed] is not None and self.keys[hashed] != key:
                hashed = self._rehash(hashed)

            if self.keys[hashed] is None:
                self.keys[hashed] = key
                self.values[hashed] = value
            else:
                self.values[hashed] = value # replace repeated index

    def get(self, key):
        _, value = self._find(key)
        return value

    def delete(self, key):
        hashed, value = self._find(key)
        if value is None:
            return value

        del self.keys[hashed]
        del self.values[hashed]

        return value


def main():
    hash_table = HashTable()
    hash_table['one'] = -1
    hash_table['one'] = 1
    hash_table['two'] = 2
    hash_table['three'] = 3
    hash_table[1] = 'one'
    hash_table[2] = 'two'
    hash_table[3] = 'three'

    print(hash_table[1])
    print(hash_table[2])
    print(hash_table[3])

    hash_table.delete('three')
    hash_table.delete(3)

    print('--repr--')
    print(hash_table)

if __name__ == '__main__':
    main()
