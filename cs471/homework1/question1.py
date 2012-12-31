#!/usr/bin/python

def gcdR(i, j):
    if i == j:
        return i
    elif i > j:
        i = j if i % j == 0 else i % j
        return gcdR(i, j)
    else:
        j = i if j % i == 0 else j % i
        return gcdR(i, j)

def main():
    print "The GCD of 100 and 247 is " + str(gcdR(100, 247))
    print "The GCD of 16 and 32 is " + str(gcdR(16, 32))
    print "The GCD of 22 and 3456 is " + str(gcdR(22, 3456))
    
main()
