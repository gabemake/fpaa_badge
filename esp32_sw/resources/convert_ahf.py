import sys

file = open(sys.argv[1], "r")
outbytes = bytearray()
lines = file.readlines()
for line in lines:
    outbytes.extend(bytearray.fromhex(line))
file.close()
file = open(sys.argv[1] + ".bin", "wb")
file.write(outbytes)
file.close