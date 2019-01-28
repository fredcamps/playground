from enum import Enum


class Color(Enum):
    RED = 'RED'
    BLACK = 'BLACK'


class Direction(Enum):
    LEFT = 'LEFT'
    RIGHT = 'RIGHT'


class Node:

    def __init__(self, key, value, color=Color.RED):
        self.parent = None
        self.left = None
        self.right = None
        self.color = color
        self.key = key
        self.value = value

    @property
    def is_red(self):
        return self.color == Color.RED


class RedBlackTree:

    def __init__(self, create_node=Node):
        self.root = None
        self._nil = create_node(key=None, value=None, color=Color.BLACK)
        self._create_node = create_node

    def _minimum(self, node):
        if node is None:
            return self._nil
        while node.left != self._nil:
            node = node.left
        return node

    def _predecessor(self, key):
        walk_node = self.root
        tmp_node = self._nil
        if walk_node is None:
            return self._nil
        while walk_node != self._nil:
            tmp_node = walk_node
            if key < walk_node.key:
                walk_node = walk_node.left
            else:
                walk_node = walk_node.right

        return tmp_node

    def _left_rotate(self, node):
        right_child = node.right
        parent = node.parent
        node.right = right_child.left
        if right_child.left != self._nil:
            right_child.left.parent = node

        right_child.parent = parent
        if parent is None:
            self.root = right_child
        elif node == parent.left:
            parent.left = right_child
        else:
            parent.right = right_child

        right_child.left = node
        node.parent = right_child

    def _right_rotate(self, node):
        left_child = node.left
        parent = node.parent
        node.left = left_child.right
        if left_child.right != self._nil:
            left_child.right.parent = node

        left_child.parent = parent
        if parent == self._nil:
            self.root = left_child
        elif node == parent.right:
            parent.right = left_child
        else:
            parent.left = left_child

        left_child.right = node
        node.parent = left_child

    def _transplant(self, x, y):
        if x.parent == self._nil or x.parent is None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.parent = x.parent

    def _insert_fix_up(self, node):
        uncle = None
        while node.parent is not None and node.parent.is_red:
            if node.parent == node.parent.parent.left:
                uncle = node.parent.parent.right
                if uncle.is_red:
                    node.parent.color = Color.BLACK
                    uncle.color = Color.BLACK
                    node.parent.parent.color = Color.RED
                    node = node.parent.parent
                else:
                    if node == node.parent.right:
                        node = node.parent
                        self._left_rotate(node)
                    node.parent.color = Color.BLACK
                    node.parent.parent.color = Color.RED
                    self._right_rotate(node.parent.parent)
            else:
                uncle = node.parent.parent.left
                if uncle.is_red:
                    node.parent.color = Color.BLACK
                    uncle.color = Color.BLACK
                    node.parent.parent.color = Color.RED
                    node = node.parent.parent
                else:
                    if node == node.parent.left:
                        node = node.parent
                        self._right_rotate(node)
                    node.parent.color = Color.BLACK
                    node.parent.parent.color = Color.RED
                    self._left_rotate(node.parent.parent)

        self.root.color = Color.BLACK

    def _delete_fix_up(self, node):
        brother = None
        while node != self.root and not node.is_red:
            if node == node.parent.left:
                brother = node.parent.right
                if brother.is_red:
                    brother.color = Color.BLACK
                    node.parent.color = Color.RED
                    self._left_rotate(node.parent)
                    brother = node.parent.right
                if not brother.left.is_red and not brother.right.is_red:
                    brother.color = Color.RED
                    node = node.parent
                elif not brother.right.is_red:
                    brother.left.color = Color.BLACK
                    brother.color = Color.RED
                    self._right_rotate(brother)
                    brother = node.parent.right
                else:
                    brother.color = node.parent.color
                    node.parent.color = Color.BLACK
                    brother.right.color = Color.BLACK
                    self._left_rotate(node.parent)
                    node = self.root
            else:
                brother = node.parent.left
                if brother.is_red:
                    brother.color = Color.BLACK
                    node.parent.color = Color.RED
                    self._right_rotate(node.parent)
                    brother = node.parent.left
                if not brother.right.is_red and not brother.left.is_red:
                    brother.color = Color.RED
                    node = node.parent
                elif not brother.left.is_red:
                    brother.right.color = Color.BLACK
                    brother.color = Color.RED
                    self._left_rotate(brother)
                    brother = node.parent.left
                else:
                    brother.color = node.parent.color
                    node.parent.color = Color.BLACK
                    brother.left.color = Color.BLACK
                    self._right_rotate(node.parent)
                    node = self.root

        self.root.color.black = Color.BLACK

    def _delete_helper(self, node):
        deleted_key = 0
        walk_node = node
        tmp_color = walk_node.color
        need_fixup_node = self._nil

        if node is None or node == self._nil:
            raise ValueError("Can't delete a sentinel or null node.")

        if node.left == self._nil:
            need_fixup_node = node.right
            self._transplant(node, node.right)
        elif node.right == self._nil:
            need_fixup_node = node.left
            self._transplant(node, node.left)
        else:
            walk_node = self._minimum(node.right)
            tmp_color = walk_node.color
            need_fixup_node = walk_node.right
            if walk_node.parent == node:
                need_fixup_node.parent = walk_node
            else:
                self._transplant(walk_node, walk_node.right)
                walk_node.right = node.right
                walk_node.right.parent = walk_node
            self._transplant(node, walk_node)
            walk_node.left = node.left
            walk_node.left.parent = walk_node
            walk_node.color = node.color

        if tmp_color == Color.BLACK:
            self._delete_fix_up(need_fixup_node)

        deleted_key = node.key
        del node
        return deleted_key

    def _insert_helper(self, node):
        predecessor_node = self._predecessor(node.key)
        if predecessor_node == self._nil:
            self.root = node
        elif node.key > predecessor_node.key:
            predecessor_node.right = node
        else:
            predecessor_node.left = node
        node.parent = predecessor_node
        node.left = self._nil
        node.right = self._nil
        self._insert_fix_up(node)
        return node

    def insert(self, key, value):
        node = self._create_node(key=key, value=value)
        return self._insert_helper(node)

    def delete(self, key):
        to_delete = self.find(key)
        if to_delete == self._nil:
            raise ValueError("key not found for node deletion")

        return self._delete_helper(to_delete)

    def find(self, key):
        walk_node = self.root
        if walk_node is None:
            return self._nil

        while walk_node != self._nil:
            if walk_node.key == key:
                return walk_node

            if walk_node.key > key:
                walk_node = walk_node.left
            else:
                walk_node = walk_node.right

        return walk_node

    def traversal(self):
        print("IN-ORDER TRAVERSAL: ")
        self._in_order_traversal(self.root)
        print("PRE-ORDER TRAVERSAL: ")
        self._pre_order_traversal(self.root)
        print("POST-ORDER TRAVERSAL: ")
        self._post_order_traversal(self.root)

    def _in_order_traversal(self, node):
        if node != self._nil:
            self._in_order_traversal(node.left)
            print(node.key)
            self._in_order_traversal(node.right)

    def _pre_order_traversal(self, node):
        if node != self._nil:
            print(node.key)
            self._pre_order_traversal(node.left)
            self._pre_order_traversal(node.right)

    def _post_order_traversal(self, node):
        if node != self._nil:
            self._post_order_traversal(node.left)
            self._post_order_traversal(node.right)
            print(node.key)


def test():
    tree = RedBlackTree()

    tree.insert(key=7, value='seven')
    tree.insert(key=6, value='six')
    tree.insert(key=5, value='five')
    tree.insert(key=4, value='four')
    tree.insert(key=3, value='three')
    tree.insert(key=2, value='two')
    tree.insert(key=1, value='one')

    print("Showing Red Black Traversal Before Deletion(s): ")
    tree.traversal()

    import pdb; pdb.set_trace()

    tree.delete(key=7)
    tree.delete(key=5)
    tree.delete(key=2)
    tree.delete(key=1)

    print("Showing Red Black Traversal After Deletion(s): ")
    tree.traversal()


if __name__ == '__main__':
    test()
