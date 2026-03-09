import re

ACTOR_PLAYER_ROUTINE = """def 4 for actor(ACTOR_PLAYER) {
    Lock(9);
    Lock(11);
    Lock(14);
    Lock(15);
    Lock(23);
    Lock(20);
    Lock(8);
    Lock(5);
    Lock(4);
    Lock(9);
    Lock(6);
    Lock(6);
    Lock(5);
    Lock(18);
    Lock(5);
    Lock(14);
    Lock(3);
    Lock(5);
    Lock(2);
    Lock(5);
    Lock(20);
    Lock(23);
    Lock(5);
    Lock(5);
    Lock(14);
    Lock(23);
    Lock(8);
    Lock(1);
    Lock(20);
    Lock(9);
    Lock(23);
    Lock(1);
    Lock(14);
    Lock(20);
    Lock(1);
    Lock(14);
    Lock(4);
    Lock(23);
    Lock(8);
    Lock(1);
    Lock(20);
    Lock(9);
    Lock(7);
    Lock(15);
    Lock(20);
    hold;
}"""

LOCK_PATTERN = re.compile("Lock\((\d+)\);")
message = "".join([chr(0x40 + int(lock_id)) for lock_id in LOCK_PATTERN.findall(ACTOR_PLAYER_ROUTINE)])
print(message)