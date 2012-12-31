#!/usr/bin/python

def ack(m, n):
    if m == 0:
        return n + 1
    elif n == 0 and m > 0:
        return ack(m - 1, 1)
    elif n > 0 and m > 0:
        return ack(m - 1, ack(m, n - 1))

def main():
    n = 0
    while(1 == 1):
        ack(3, n)
        print "Last successful number: " + str(n)
        n += 1

main()
