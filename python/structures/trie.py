# Python program for insert and search
# operation in a Trie


class PrefixTrie:

    class PrefixTrieNode:

        # Trie node class
        def __init__(self, alphabet_size=26):
            self.children = [None] * alphabet_size

            # is_end_of_word is True if node represent the end of the word
            self.is_end_of_word = False

    # Trie data structure class
    def __init__(self, get_node=PrefixTrieNode):
        self.get_node = get_node
        self.root = self.get_node()

    def _char_to_index(self, ch):
        # private helper function
        # Converts key current character into index
        # use only 'a' through 'z' and lower case

        return ord(ch)-ord('a')

    def insert(self, key):
        node = self.root
        length = len(key)
        for level in range(length):
            index = self.char_to_index(key[level])

            # if current character is not present
            if not node.children[index]:
                node.children[index] = self.get_node()
            node = node.children[index]

        # mark last node as leaf
        node.is_end_of_word = True

    def find_prefix(self, key):
        # Search key in the trie
        # Returns true if key presents
        # in trie, else false
        node = self.root
        length = len(key)
        for level in range(length):
            index = self.char_to_index(key[level])
            if not node.children[index]:
                return False
            node = node.children[index]

        return (node is not None and node.is_end_of_word)


def main():
    # Input keys (use only 'a' through 'z' and lower case)
    keys = ["the",
            "a",
            "there",
            "anaswe",
            "any",
            "by",
            "their"]
    output = ["Not present in trie",
              "Present in tire"]
    # Trie object
    t = PrefixTrie()

    # Construct trie
    for key in keys:
        t.insert(key)

    # Search for different keys
    print("{} ---- {}".format("the", output[t.find_prefix("the")]))
    print("{} ---- {}".format("these", output[t.find_prefix("these")]))
    print("{} ---- {}".format("their", output[t.find_prefix("their")]))
    print("{} ---- {}".format("thaw", output[t.find_prefix("thaw")]))
    print("{} ---- {}".format("anas", output[t.find_prefix("anas")]))


if __name__ == '__main__':
    main()
