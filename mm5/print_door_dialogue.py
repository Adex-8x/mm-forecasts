import io
import sys
from struct import Struct
from zipfile import ZipFile
from ndspy.rom import NintendoDSRom

HIMITSU_STRUCT = Struct("<HHII")
DOOR_BIN = "CUSTOM/NAME/door.bin"
KEY = b"IKNOWTHEDIFFERENCEBETWEENWHATIWANTANDWHATIGOT"

idx = int(sys.argv[2])
if idx not in range(0, 14):
	print("Must provide an index greater than 0 and less than 14!")
	exit(1)

rom = NintendoDSRom.fromFile(sys.argv[1])
door = rom.getFileByName(DOOR_BIN)

if door[0:2] == b"PK":
	doorzip = ZipFile(io.BytesIO(door), "r")
	door = doorzip.read(DOOR_BIN.split("/")[-1], KEY)
	
door = bytearray(door)
size = len(door)
for i in range(size >> 1):
	j = size-1-i
	if i != j:
		door[i] ^= door[j]
		door[j] ^= door[i]
		door[i] ^= door[j]
		door[i] ^= 0xFF
		door[j] ^= 0xFF

start = idx*HIMITSU_STRUCT.size
end = start+HIMITSU_STRUCT.size
first_str_len,second_str_len,first_offset,second_offset = HIMITSU_STRUCT.unpack(door[start:end])
print(door[first_offset:first_offset+first_str_len].decode())
print(door[second_offset:second_offset+second_str_len].decode())