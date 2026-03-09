import sys
from PIL import Image

DECODE_FAILED = "Image is not binary!"

pixels = list(Image.open(sys.argv[1]).getdata())
message = bytearray()
pos = 7
byte = 0
for r,g,b in pixels:
	if not(r == g and g == b):
		raise ValueError(DECODE_FAILED)
	if r == 0:
		bit = 0b0
	elif r == 255:
		bit = 0b1
	else:
		raise ValueError(DECODE_FAILED)
	
	byte |= (bit << pos)
	pos -= 1
	if pos < 0:
		message.append(byte)
		pos = 7
		byte = 0

print(message.decode())