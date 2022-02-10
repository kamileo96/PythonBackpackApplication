from time import perf_counter
from BackpackSolver import pakuj_plecak
import random, numpy as np, matplotlib.pyplot as plt

def PakujPlecakPy(V, items):
    #na koniec dopisalem sobie w pythonie, zeby zobaczyc jak sie 
    i = 0
    n = len(items)
    if(n==0):
        return items
    s = 0
    maxS = 0
    maxi = 0
    while (i<2**(n)):
        s = 0
        combo = np.binary_repr(i,n)
        j = 0
        for c in combo:
            if(j>=len(items)):
                print(f"{j}, {len(combo)}, {n}, {len(items)}")
            s += int(c)*items[j]
            j+=1
        if(s<=V and s>maxS):
            maxS = s
            maxi = i
        i+=1
    res = []
    j=0
    for c in np.binary_repr(maxi,n):
        if(int(c)):
            res.append(items[j])
        j+=1
    return res
    
def test(V, items, pt):
    start = perf_counter()
    if(pt):
        print("Starting benchmark...")
    results = pakuj_plecak(V, items)
    duration = perf_counter() - start
    if(pt):
        print(f"Using C++ it took {duration:.5f} seconds, for {len(ls)} items:\n")
        print(items)
        print(f'In volume {V}, the maximum volume is {sum(results)}, with the following items:')
        print(results)
    return duration
def testpy(V, items, pt):
    start = perf_counter()
    if(pt):
        print("Starting benchmark...")
    results = PakujPlecakPy(V, items)
    duration = perf_counter() - start
    if(pt):
        print(f"Using PYTHON it took {duration:.5f} seconds, for {len(ls)} items:\n")
        print(items)
        print(f'In volume {V}, the maximum volume is {sum(results)}, with the following items:')
        print(results)
    return duration


if __name__ == "__main__":
    V = 1000
    ls = []
    n = 20
    for i in range(n):
        ls.append(random.randrange(V))
    a = test(V, ls, True)
    a = testpy(V, ls, True)
    
    ts = np.array([])
    tspy = np.array([])
    maxn=26
    maxnpy = 22
    print(f"Running benchmark up to {maxn} items:")
    for n in range(maxn+1):
        ls = []
        for i in range(n):
            ls.append(random.randrange(V))
        ts = np.append(ts, test(V, ls, False))
        if(n<maxnpy):
            tspy = np.append(tspy, testpy(V, ls, False))
        print(f"Completed {n} out of {maxn}", end="\r")
    print("                           ")
    fig, ax = plt.subplots()
    ax.set_yscale('log')
    ax.plot(ts,'.',label='C++')
    ax.plot(tspy,'.',label='Python')
    ax.legend()
    ax.set_title('Calculation time as a function of n. of items in logarithmic scale')
    ax.set_xlabel('n')
    ax.set_ylabel('time[s]')
    plt.show()
