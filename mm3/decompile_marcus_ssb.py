import sys
from ndspy.rom import NintendoDSRom
from skytemple_files.script.ssb.handler import SsbHandler
from skytemple_files.common.util import get_ppmdu_config_for_rom
from skytemple_files.common.ppmdu_config.script_data import Pmd2ScriptOpCode

MAGIC_OPCODE_ID = 11621
SPOOKY_SCRIPT = "SCRIPT/MYSTERY/marcus.ssb"

rom = NintendoDSRom.fromFile(sys.argv[1])

config = get_ppmdu_config_for_rom(rom)
opcodes = config.script_data.op_codes
for op_id in range(MAGIC_OPCODE_ID, MAGIC_OPCODE_ID+2):
	opcodes.append(Pmd2ScriptOpCode(op_id, f"UNK_{op_id}", 0, -1, 0, 0, [], None))
with config.script_data.modify() as storage:
	storage.op_codes = opcodes

ssb = SsbHandler.deserialize(rom.getFileByName(SPOOKY_SCRIPT), config)
exps, _ = ssb.to_explorerscript() # or ssb.to_ssb_script()
with open("marcus.exps", "w") as f:
	f.write(exps)