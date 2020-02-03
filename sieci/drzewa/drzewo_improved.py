def make_set(v):
    tree = []
    tree.append(v)

    return tree

def find_set(v,forest):
    for i in range (len(forest)):
        if(v in forest[i]): 
            #print(v)
            return i
        '''for j in range (len(forest[i])):
            if (v == forest[i][j]): return i'''

def union(u,v,forest):
    for i in range (len(forest)):
        if(u in forest[i]):
            indexu = i
    
    for j in range (len(forest)):
        if(v in forest[j]):
            indexv = j

    forest[indexu] += forest[indexv]

    forest[indexv] = [-5]

    return forest

def Kruskal(listaK, vertices):
    final = []
    forest = []

    for i in range (len(vertices)):
        forest.append(make_set(vertices[i]))

    #print(forest)

    sortedlist = sorted(listaK, key=lambda tup: tup[2])

    for i in range (len(sortedlist)):
        if (find_set(sortedlist[i][0],forest)!=find_set(sortedlist[i][1],forest)):
            final.append(sortedlist[i])
            forest = union(sortedlist[i][0],sortedlist[i][1],forest)

    #print(final)

    return final





u1 = (1,2,4)
u2 = (1,8,8)
u3 = (2,3,8)
u4 = (2,8,11)
u5 = (3,9,2)
u6 = (3,6,4)
u7 = (3,4,7)
u8 = (4,6,14)
u9 = (4,5,9)
u10 = (5,6,10)
u11 = (6,7,2)
u12 = (7,9,6)
u13 = (7,8,1)
u14 = (8,9,7)


listaU = [u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12, u13, u14]
v2 = [1,2,3,4,5,6,7,8,9]



k1 = (1,2,1)
k2 = (1,3,2)
k3 = (1,4,2)
k4 = (1,5,4)
k5 = (2,4,4)
k6 = (2,5,5)
k7 = (3,4,3)
k8 = (4,5,3)

listaK = [k1, k2, k3, k4, k5, k6, k7, k8]
vertices = [1, 2, 3, 4, 5]

'''
test1 = []
test1.append([1,2,3])
test1.append([5,6,7])

find_set(5,test1)
'''

#Kruskal(listaK,vertices)
#Kruskal(listaU,v2)

result = Kruskal(listaU,v2)

print(result)

print(sum(k for i, j, k in result))