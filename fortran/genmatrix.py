import sys, random

def random_matrix(m, n):
    return [[random.random() for i in range(n)] for j in range(m)]

if __name__ == "__main__":
    n = int(sys.argv[1])
    print (n)
    print (", ".join(str(e) for e in sum(random_matrix(n, n), [])))
    print (", ".join(str(e) for e in sum(random_matrix(n, n), [])))
