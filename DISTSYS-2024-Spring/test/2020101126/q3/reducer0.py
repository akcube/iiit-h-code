#!/usr/bin/env python3
import sys
input = sys.stdin.readline

ROOT_NODE = 1
INFINITY = 100

def parse_line(line):
    node, value = line.strip().split('\t')
    value = list(map(int, value.split(' ')))
    if len(value) == 1:
        return int(node), value[0], None
    return int(node), value[0], ' '.join(map(str, value[1:]))

current_node, current_distance, current_adj = None, None, None

def publish():
    if(current_node == None):
        return
    sys.stdout.write("{v}\t{d} {adj}\n".format(v=current_node,
                                             d=current_distance,
                                             adj=current_adj))

for line in sys.stdin:
    node, distance, adj = parse_line(line)
    if node == current_node:
        current_distance = min(current_distance, distance)
        current_adj = adj if current_adj is None else current_adj
    else:
        publish()
        current_node, current_distance, current_adj = node, distance, adj
publish()

