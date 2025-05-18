#!/usr/bin/env python3
import sys
input = sys.stdin.readline

ROOT_NODE = 1
INFINITY = 100

def parse_line(line):
    node, adj = line.strip().split('\t')
    return int(node), list(map(int, adj.split(' ')))

for line in sys.stdin:
    node, adj = parse_line(line)
    distance = 0 if node == ROOT_NODE else 100

    sys.stdout.write("{v}\t{d} {adj}\n".format(v=node, d=distance, adj=" ".join(map(str, adj))))
    if node == ROOT_NODE:
        for to in adj:
            sys.stdout.write("{v}\t{d}\n".format(v=to, d=distance+1))

