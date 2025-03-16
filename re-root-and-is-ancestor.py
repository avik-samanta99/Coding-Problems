class Tree2:
    def __init__(self,parent):
        self.n = len(parent)
        self.root = 0
        self.start,self.end = [-1]*self.n , [-1]*self.n
        # adjList
        self.adjList = [[] for _ in range(self.n)]  
        for child, parent in enumerate(parent):
            if parent != -1:
                self.adjList[child].append(parent)
                self.adjList[parent].append(child)
            else:
                self.root = child
        self.timer = 0
        self.setRoot(self.root)

    def setRoot(self,node):
        self.root = node
        self.timer = 0
        self.dfs(self.root,-1)

    def dfs(self,root,par):
        # before go to adjacents mark the root pos
        self.start[root] = self.timer
        self.timer += 1  # inc for next root
        for child in self.adjList[root]:
            if child != par :
                self.dfs(child,root)
        # after go to all adjacents mark the root pos 
        self.end[root] = self.timer
        self.timer += 1  # inc for next root
    
    def isAncestor(self,u,v):
        if self.start[u] < self.start[v] and self.end[u] > self.end[v]:
            return True
        return False

t = Tree2([-1,0,1,1,3,3,3,1,4,8,9])
print(t.isAncestor(1, 10))
print(t.isAncestor(7, 5))
t.setRoot(7)
print(t.isAncestor(7, 5))
print(t.isAncestor(0, 7))
t.setRoot(0)
print(t.isAncestor(0, 7))
