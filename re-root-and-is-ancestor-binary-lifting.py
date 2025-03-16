import math


class Tree:
    def __init__(self, parents):
        self.n = len(parents)  # number of nodes
        self.adj = [[] for _ in range(self.n)]  # adjacency list
        root = 0  # default number of the root node

        for child, parent in enumerate(parents):
            if parent != -1:
                self.adj[child].append(parent)
                self.adj[parent].append(child)
            else:
                root = child

        self.depth = [-1] * self.n  # distance from root
        
        # for every node ancestors[i] store all the ancestors
        # of i that have a distance of 2 ** j from node i
        # ancestors[i][2 ** j] would be equal to the 
        # ancestor node of i that has 2 ** j distance from node i
        self.ancestors = [dict() for _ in range(self.n)]
        self.set_root(root)

    def set_root(self, root):
        # it's simple dfs to set new depth and
        # ancestors for every node, but we keep track
        # the nodes that are already in dfs stack
        # stack[i] is equal to the node that is
        # already in dfs stack and has depth of i
        def dfs(node, parent, stack, depth=1):
            stack[depth] = node
            self.depth[node] = depth

            self.ancestors[node].clear()
            for i in range(int(math.log2(depth))):
                self.ancestors[node][2 ** i] = stack[depth - 2 ** i]

            for child in self.adj[node]:
                if child != parent:
                    dfs(child, node, stack, depth + 1)

            stack.pop(depth)

        dfs(root, -1, dict())

    def is_ancestor(self, u, v):
        if self.depth[u] > self.depth[v]:
            return False

        depth_diff = self.depth[v] - self.depth[u]

        curr_node = v
        jump = 2 ** int(math.log2(depth_diff)) if depth_diff > 0 else 0

        while depth_diff > 0:
            if depth_diff - jump >= 0:
                curr_node = self.ancestors[curr_node][jump]
                depth_diff -= jump
            jump >>= 1
        return u == curr_node

t = Tree([-1, 0, 1])
print(t.is_ancestor(0, 1))
t.set_root(1)
print(t.is_ancestor(0, 1))
t.set_root(0)
print(t.is_ancestor(0, 1))
