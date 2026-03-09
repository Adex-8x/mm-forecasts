import sys
from ndspy.rom import NintendoDSRom
from skytemple_files.script.ssb.handler import SsbHandler
from skytemple_files.common.util import get_ppmdu_config_for_rom

NAME_CHECK_SCRIPT = "SCRIPT/MYSTERY/check.ssb"
ONAMAEWA_BIN = "CUSTOM/NAME/onamaewa.bin"

rom = NintendoDSRom.fromFile(sys.argv[1])
config = get_ppmdu_config_for_rom(rom)
ssb = SsbHandler.deserialize(rom.getFileByName(NAME_CHECK_SCRIPT), config)
key = ssb.constants[0].encode()
onamaewa = bytearray(rom.getFileByName(ONAMAEWA_BIN))

for i in range(len(onamaewa)):
	onamaewa[i] ^= key[i]
	
unk_message = bytearray()
for i in range(0xC, len(onamaewa), 0xD):
	if onamaewa[i] != 0:
		unk_message.append(0x40 + onamaewa[i])

print(unk_message.decode())