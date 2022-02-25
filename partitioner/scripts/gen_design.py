#!/usr/bin/python3
import random
import argparse
import math
import sys


class Block:
    def __init__(self, idx):
        self.idx = idx
        self.nets = []


class Net:
    def __init__(self, idx):
        self.idx = idx
        self.blocks = []

    def add_block(self, block):
        self.blocks.append
        block.nets.append(self)


def distance(pin1, pin2):
    return abs(pin1.tile.x - pin2.tile.x) + abs(pin1.tile.y - pin2.tile.y)


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("output_file", help="Output file path")
    parser.add_argument("num_blocks", type=int)
    parser.add_argument("pins_per_block", type=int)
    parser.add_argument("density", type=float)
    args = parser.parse_args()

    # Create blocks
    blocks_0 = []
    blocks_1 = []
    for i in range(args.num_blocks // 2):
        blocks_0.append(Block(i))
    for i in range(args.num_blocks // 2, args.num_blocks):
        blocks_1.append(Block(i))
    blocks_all = blocks_0 + blocks_1

    # Create nets
    nets = []
    while True:
        net = Net(len(nets))

        # Num blocks this net connects to
        num_blocks = math.ceil(random.expovariate(1 / 1.5) + 1)
        print("Num blocks", num_blocks)

        # Find total pins used
        total_pins = sum([len(b.nets) for b in blocks_all])
        density = total_pins / (args.num_blocks * args.pins_per_block)

        # Find blocks with empty pins
        if density < args.density * 0.5:
            # Phase 1, just choose blocks from block_0
            blocks_avail = [b for b in blocks_0 if len(b.nets) < args.pins_per_block]
        elif density < args.density:
            # Phase 2
            blocks_avail = [b for b in blocks_1 if len(b.nets) < args.pins_per_block]
        # elif density < args.density:
        #     # Phase 3
        #     blocks_avail = [b for b in blocks_1 if len(b.nets) < args.pins_per_block]
        else:
            break

        # Net too big
        if len(blocks_avail) < num_blocks:
            continue

        blocks_for_net = random.sample(blocks_avail, num_blocks)
        for b in blocks_for_net:
            net.add_block(b)
        nets.append(net)

    print("-" * 80)
    print("Writing circuit to", args.output_file)
    with open(args.output_file, "w") as fp:
        for b in blocks_all:
            fp.write(str(len(b.nets)))
            for n in b.nets:
                fp.write(" " + str(n.idx))
            fp.write("\n")

    return

    parser.add_argument("size", help="Side size of FPGA")
    # parser.add_argument("tracks", help = "Number of routing tracks")
    parser.add_argument("pin_density", help="Percentage of tile pins to use")
    # parser.add_argument("flow", choices=[e.value for e in bfasst.flow.Flows])
    # parser.add_argument("--force", action='store_true')

    size = int(args.size)
    num_tiles = size**2

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
    print(
        "Will target using " + str(total_pins) + " of " + str(num_tiles * PINS_PER_TILE) + " pins"
    )
    print("-" * 80)

    used_pins = 0
    sys.stdout.write("Creating nets")
    while used_pins < total_pins:
        fanout = math.ceil(random.expovariate(1 / 2))
        if used_pins + 1 + fanout > total_pins:
            fanout = max(1, total_pins - used_pins - 1)
        used_pins += 1 + fanout

        # Pick Source
        src_pin = random.choice([p for p in pins if not p.used])
        src_pin.used = True
        # print("\tSource: (" + str(src_pin.tile.x) + ", " + str(src_pin.tile.y) + ")." + str(src_pin.idx))

        # Pick destinations
        dest_pins = []
        while len(dest_pins) < fanout:
            dest_distance = math.ceil(random.expovariate(1 / 115.0))
            # sys.stdout.write("\tDistance " + str(dest_distance) + ": ")
            possible_dest_pins = [
                p
                for p in pins
                if (not p.used) and p != src_pin and distance(src_pin, p) == dest_distance
            ]
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

    # for i in range(0, 20):
    #     print(int(random.expovariate( 1 / 3.0)) + 1)
    print("-" * 80)


if __name__ == "__main__":
    main()
