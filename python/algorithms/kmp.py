# knuth morris pratt pattern matching algorithm

def _partial(pattern):
    """ Calculate partial match table: String -> [Int]"""
    ret = [0]
    for i in range(1, len(pattern)):
        j = ret[i - 1]
        while j > 0 and pattern[j] != pattern[i]:
            j = ret[j - 1]
        ret.append(j + 1 if pattern[j] == pattern[i] else j)
    return ret


def search(text, pattern):
    """
    KMP search main algorithm: String -> String -> [Int]
    Return all the matching position of pattern string P in S
    """
    partial, ret, j = _partial(pattern), [], 0

    for i in range(len(text)):
        while j > 0 and text[i] != pattern[j]:
            j = partial[j - 1]
        if text[i] == pattern[j]:
            j += 1
        if j == len(pattern):
            ret.append(i - (j - 1))
            j = 0

    return ret


def main():
    text = 'flowers of romance'
    flowers = search(text, 'flowers')
    o = search(text, 'o')
    romance = search(text, 'romance')
    revenge = search(text, 'revenge')

    assert (flowers == [0])
    assert (o == [2, 8, 12])
    assert (romance == [11])
    assert (revenge == [])


if __name__ == '__main__':
    main()
