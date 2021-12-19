import heapq
import random

S = 0

class G:
   V = []
   E = []
   W = []

def dijkstra(D, F, G):
   H = []
   D = ['inf' for i in range(G.V)]
   F = [-1 for i in range(G.V)]
   heapq.heappush(H, (D[S], S)); 

   for i in G:
      (d, u) = heapq.heappop(H);
      for p in G:
         v = G.V[p]
         w = G.W[p]
         if D[u] + w < D[v]:
            D[v] = D[u] + w
            F[v] = u
            heapq.heappush(H, (D[v], v))
   return D, F  

(a, b) = dijkstra(G)
print(a, "\n")