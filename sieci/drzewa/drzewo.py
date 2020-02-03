import heapq


#def extract_min(Q):
    

def heapsearch(v, O):
    for i in range(len(O)):
        if (v==O[i]):
            return i

def adj(u,listaU):
    index = []

    first = [x[0] for x in listaU]
    second = [x[1] for x in listaU]

    #print(first)
    #print(second)

    for i in range(len(first)):
        if first[i] != second[i]:
            if(first[i]==u):
                index.append((second[i],i))
            
            if(second[i]==u):
                index.append((first[i],i))

    return index

def Prim(listaU, vertices, r):
    
    final = []

    Q = vertices

    #print("r= ",r)

    length = len(vertices)

    #heapq.heapify(Q)


    key = []

    for i in range(length):
        key.append(9999)

    key[0] = 0

    pi = []

    for i in range(length):
        pi.append(None)

    pi[r] = None

    O = []
    for i in range(length):
        O.append((key[i],vertices[i],pi[i]))
    
    heapq.heapify(O)

    #print(Q)
    #print(O)

    #print(heapq.heappop(O))


    while(O):
        u = heapq.heappop(O)
        final.append(u)
        #print(u)
        current = vertices.index(u[1])
        Q.remove(u[1])

        key.remove(key[current])
        #pi.remove(pi[current])

        adjusted = adj(u[1], listaU)

        for i in range(len(adjusted)):
            if(adjusted[i][0] in Q and listaU[adjusted[i][1]][2]<key[heapsearch(adjusted[i][0],Q)]):
                #print("hehe:",heapsearch(adjusted[i][0],Q))
                pi[heapsearch(adjusted[i][0],Q)] = u[1]
                key[heapsearch(adjusted[i][0],Q)] = listaU[adjusted[i][1]][2]
                #final.append(listaU[adjusted[i][1]])

        O = []
        for i in range(len(key)):
            O.append((key[i],Q[i],pi[i]))
    
        heapq.heapify(O)

        #print(O)
        #O = None
        
    final.remove(final[0])
    return final


k1 = (1,2,1)
k2 = (1,3,2)
k3 = (1,4,2)
k4 = (1,5,4)
k5 = (2,4,4)
k6 = (2,5,5)
k7 = (3,4,3)
k8 = (4,5,3)

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


listaK = [k1, k2, k3, k4, k5, k6, k7, k8]
vertices = [1, 2, 3, 4, 5]

listaU = [u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12, u13, u14]
v2 = [1,2,3,4,5,6,7,8,9]


#print(Prim(listaU, v2, v2[0]))

listaU = [u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12, u13, u14]
v2 = [1,2,3,4,5,6,7,8,9]

result = Prim(listaU, v2, v2[0])

print(result)

print(sum(i for i, j, k in result))




