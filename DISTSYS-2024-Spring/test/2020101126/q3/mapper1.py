#!/usr/bin/env python3
import sys
input = sys.stdin.readline

ROOT_NODE = 1
INFINITY = 100

def parse_line(line):
    node, value = line.strip().split('\t')
    value = list(map(int, value.split(' ')))
    return int(node), value[0], value[1:]

def publish(node, distance):
    if distance > INFINITY:
        return
    sys.stdout.write("{v}\t{d}\n".format(v=node, d=distance))

for line in sys.stdin:
    sys.stdout.write(line)
    node, distance, adj = parse_line(line)
    for to in adj:
        publish(to, distance+1)
