#!/usr/bin/env python3
import sys
input = sys.stdin.readline

ROOT_NODE = 1
INFINITY = 100

def parse_line(line):
    node, value = line.strip().split('\t')
    value = list(map(int, value.split(' ')))
    return int(node), value[0]

def publish(node, distance):
    sys.stdout.write("{v}\t{d}\n".format(v=node, d=distance))

for line in sys.stdin:
    node, distance = parse_line(line)
    if distance > 10:
        continue
    publish(node, distance)

