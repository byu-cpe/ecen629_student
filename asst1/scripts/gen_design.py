#!/usr/bin/python3
import random
import argparse
import math
import sys

PINS_PER_TILE = 4

class Tile:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.pins = []

class Pin:
    def __init__(self, parent_tile, idx):
        self.tile = parent_tile
        self.idx = idx
        self.used = False

class Net:
    def __init__(self, src_pin, dest_pins):
        self.src_pin = src_pin
        self.dest_pins = dest_pins
    
def distance(pin1, pin2):
    return abs(pin1.tile.x - pin2.tile.x) + abs(pin1.tile.y - pin2.tile.y)

def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("output_file", help = "Output file path")
    parser.add_argument("size", help = "Side size of FPGA")
    # parser.add_argument("tracks", help = "Number of routing tracks")
    parser.add_argument("pin_density", help = "Percentage of tile pins to use")
    # parser.add_argument("flow", choices=[e.value for e in bfasst.flow.Flows])
    # parser.add_argument("--force", action='store_true')
    args = parser.parse_args()

    size = int(args.size)
    num_tiles = size ** 2

    print("-" * 80)
    print("Creating design for " + str(size) + "x" + str(size) + " FPGA")
    print("-" * 80)

    # Initialize FPGA
    tiles = []
    pins = []
    nets = []
    for x in range(size):
        tiles.append([])
        for y in range(size):
            tile = Tile(x, y)
            tiles[x].append(tile)
            for pin_idx in range(PINS_PER_TILE):
                pin = Pin(tile, pin_idx)
                pins.append(pin)
                tile.pins.append(pin)

    # Choose random congestion between 0.3 and 0.5
    # This represents fraction of tile pins that are used
    # congestion = round((random.random() / 5.0) + 0.3, 2)
    congestion = float(args.pin_density)
    print("Pin density set to:", congestion)
    print("-" * 80)

    total_pins = int(num_tiles * PINS_PER_TILE * congestion)
    print("Will target using " + str(total_pins) + " of " + str(num_tiles * PINS_PER_TILE) + " pins")
    print("-" * 80)

    used_pins = 0
    sys.stdout.write("Creating nets")
    while used_pins < total_pins:
        fanout = math.ceil(random.expovariate(1 / 2))
        if used_pins + 1 + fanout > total_pins:
            fanout = max(1, total_pins - used_pins - 1)
        used_pins += (1 + fanout)

        # Pick Source
        src_pin = random.choice([p for p in pins if not p.used])
        src_pin.used = True
        # print("\tSource: (" + str(src_pin.tile.x) + ", " + str(src_pin.tile.y) + ")." + str(src_pin.idx))

        # Pick destinations
        dest_pins = []
        while len(dest_pins) < fanout:
            dest_distance = math.ceil(random.expovariate(1 / 115.0))
            # sys.stdout.write("\tDistance " + str(dest_distance) + ": ")
            possible_dest_pins = [p for p in pins if (not p.used) and p != src_pin and distance(src_pin, p) == dest_distance]
            if len(possible_dest_pins) == 0:
                # sys.stdout.write(" failed\n")
                continue
            dest_pin = random.choice(possible_dest_pins)
            dest_pin.used = True
            # sys.stdout.write("(" + str(dest_pin.tile.x) + ", " + str(dest_pin.tile.y) + ")." + str(dest_pin.idx) + "\n")
            dest_pins.append(dest_pin)

        net = Net(src_pin, dest_pins)
        nets.append(net)
        sys.stdout.write(".")
    print("Done")

    print("-" * 80)
    print("Writing circuit to" , args.output_file)
    with open(args.output_file, 'w') as fp:
        fp.write(str(size) + '\n')
        # fp.write(args.tracks + "\n")
        for net in nets:
            fp.write(str(net.src_pin.tile.x) + " ")
            fp.write(str(net.src_pin.tile.y) + " ")
            fp.write(str(net.src_pin.idx + 1) + " ")
            for pin in net.dest_pins:
                fp.write(str(pin.tile.x) + " ")
                fp.write(str(pin.tile.y) + " ")
                fp.write(str(pin.idx + 1) + " ")
            fp.write('\n')
        fp.write("-1 -1 -1 -1 -1 -1")

    # for i in range(0, 20):  
    #     print(int(random.expovariate( 1 / 3.0)) + 1)
    print("-" * 80)

if __name__ == "__main__":
    main()