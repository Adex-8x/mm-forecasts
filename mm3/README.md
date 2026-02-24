# Forbidden File
> *I have learned. I have understood. And above all else, I have had fun.*

The very first FORECAST! As such, this is the most standalone, rudimentary, and guessworky of the bunch. It can be easily cheesed, though despite this, it had significantly fewer solvers compared to the following FORECAST.

Recommended Resources:
- [CyberChef](https://gchq.github.io/CyberChef/)
- [ndstool](https://github.com/blocksds/ndstool)
- [SkyTemple](https://skytemple.org/)
- [SSB File Format](https://projectpokemon.org/home/docs/mystery-dungeon-nds/pmd2-ssb-r49/)
- [SSB Opcodes](https://wiki.skytemple.org/index.php/List_of_Opcodes)

## Solution
### Starting Out
If I were to tell you—a MysteryMail 3 participant in 2022—that the organizers planted a secret somewhere in the ROM, where would you first look? Well, there are quite a number of files within an NDS ROM, so it might be best to rule out what *shouldn't* be possible. First off, it *should* be well-hidden enough such that one of your fellow participants can't accidentally edit or delete the secret in SkyTemple itself. Or at the very least, niche enough that most participants wouldn't think to do it by accident. They're on a strict 47-hour time limit, after all.

Right off the bat, this should eliminate the actual core function behind MysteryMail: SSB files. An SSB file contains the underlying "script" code that makes cutscenes tick; anything written in [ExplorerScript](https://explorerscript.skytemple.org/en/stable/) gets compiled to a `.ssb` file. The way MysteryMail works, an [Xdelta](https://en.wikipedia.org/wiki/Xdelta) patch is passed from participant to participant, but with all scripts prior to the previous participants cleared of all contents. For example, Participant 3 would be able to see Participant 2's script code, but Participant 1's script would be mostly empty.

Emphasis on the *mostly*. Participants are allowed to keep debug print opcodes intact, so long as they aren't anything spoilery. While this does mean that it's unlikely for the organizer-made scene to hide a secret, a message still could've been left to help guide us in the right direction!

### Acting In Good Faith
So opening up `MYSTERY/initial.ssb`, we see the following:
```js
debug_Print("Let's do this!");
debug_Print("An important reminder: Keys can only be found in dungeons.");
```
Dungeons? But this is the community event that explicitly bans dungeons...

A cursory glance of the dungeons in the ROM doesn't reveal anything glaring. Maybe we have to enter a specific dungeon? Let's try entering Dungeon 0 in any script of our choice...
```js
main_EnterDungeon(0, 0);
main_EnterDungeon(-1, 0);
hold;
```
And...we get...

![alt text](./cart_removed.png "Bold red text over a black background stating, \"There is nothing for you here.\" The bottom-right corner of the image contains barely legible text: \"thefirstnewactorintheactorlist\"")

A crash! So was this just a red herring? Entering any other dungeon gives the same result...but we can make out some text on the bottom-right of the image: `thefirstnewactorintheactorlist`.

Let's trust the overly-cryptic crash screen for now. The first actor in the Actor List for NA ROMs is 386, which in the specific case of MM3, belongs to `NPC_MARCUS`.

Now, still under the assumption that you were a MysteryMail 3 participant, this might've immediately raised some suspicion. For one, "Marcus" was the protagonist of the previous event. What's more, this actor doesn't actually appear to be used in any Acting Scene!

~~...at least, if you participated on or before Scene 22. The participant of that scene decided to include `NPC_MARCUS`, who subsequently overtook the role as the protagonist. Cool.~~

Additionally, you could've noticed that when we crash on this screen, the game flashes white for a brief moment before displaying the image. This is usually a telltale sign of the game cartridge being ejected, and sure enough, we can find the above image in SkyTemple under `Misc. Graphics -> cart_removed.at`. This is rarely changed in hacks, so its use here, especially when intentionally crashing upon dungeon entry, at least indicates *something* is afoot.

Either way, this is something to work with! Maybe `Marcus`, `NPC_MARCUS`, or `thefirstnewactorintheactorlist` is our key? But that still leaves us the questions of:
- What are we trying to decrypt?
- What sort of encryption are we working with?

These questions ultimately leave us with needing to investigate more of the ROM. We could think to investigate Flygon's (the species of `NPC_MARCUS`) data, items, or Text Strings...but there's actually one script that is very likely untouched by participants due to the way MysteryMail works.

### The Big Bad Unionall
The script file [`COMMON/unionall.ssb`](https://wiki.skytemple.org/index.php/Unionall) is responsible for all of the core control flow in the game. It's always loaded during Ground Mode and decides when to play cutscenes. You can think of it like the scripting backbone that keeps PMD2 from turning to jelly. It's essential for any hack to function, and in the case of MysteryMail, can be *completely* ignored by participants. They don't have to worry about control flow, just their own Acting Scene. This is a relief for many, since Unionall is generally disliked by the community for being so cumbersome to interpret and edit.

However, the event organizers definitely had to set up Unionall in a certain way to actually make the hack function. It's not likely that a participant would waste any of their precious 47 hours staring at something they shouldn't edit, which makes for a good hiding spot!

We don't really have anything in particular to go off of other than a hunch disguised as a dream, so just scrolling willy-nilly, we eventually come across something suspicious in the coroutine `EVENT_DIVIDE`:
```js
debug_Print("Xuxwg Jworrpegg");
debug_Print("Rrg BH, Tsnva LO, Difwr");
debug_Print("P htv'k cgba shcm'g nzbgn aiva av. T'dw uxlr xqklbak detx ocwax, avykgu kz zwfxtfjz nztg lwprxbvl ghkey, dnh Z nif hgsc wmdwfoin opx hyqaz.");
debug_Print("Aliu fciyqfz, B yirmdtxe vqbdbbx ul xfis cpobp ifw ypriqey t fxnapzsi avmamni gsoe bg fx. P'q gmzfz iecug ustihll M'vg tzipivr yvvlwklxa adav mvvg yhvo lkds.");
debug_Print("Rwt A dgva na kztg aa epwsu cc voetvbbx qwj t upx. Tz dsroi phg pvftr whc? Ekmvvc esr, hm amik, A wbr'p kphk. Z waef veoxaspz ggx zmsocw mumjg jx grqq.");
debug_Print("\"Bm cow pwjs bg mtso yw dw lbqa mqks, jqzisc aem ce xg ftfl.\"");
debug_Print("Rte kztg M're ykwkbrg hpl qy hyta gnm, P xmqec B'z kkipz hf jhku mt. Txfvllagz px ribwl zi bege gzkx yvv sqfs ipikhg.");
```
Looks like we've found our ciphertext! But what sort of cipher is this?

This is admittedly pretty guessworky to figure out, but at least we have the knowledge that the cipher is alphabetic and requires a key. Shoving this into some generic cipher-detector site, we get good odds of it being a [Vigenère cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher), which seems to fit what we need.

Let's try `thefirstnewactorintheactorlist` as the key, since it seems suspicious enough for not being space-delimited. Switching over to CyberChef, selecting "Vigenère Decode", and we get...
```
Entry Seventeen
Day OO, Month XX, Sandy
I don't know what's wrong with me. I've been sitting here alone, trying to remember what happened today, but I can only remember one thing.
This morning, I remember rubbing my eyes awake and finding a stranger sitting next to me. I'm being vague because I've already forgotten what they look like.
All I know is that we ended up chatting for a bit. Or maybe the whole day? Either way, of what, I don't know. I only remember one single thing he said.
"If you wish to talk to me some more, simply act on my name."
Now that I've written all of this out, I think I'm going to burn it. Rereading it makes me feel sick for some reason.
```
Yay, plaintext! By the looks of it, it's a diary entry. From who? A participant may have been able to deduce that this was Bwaix, depending on if her diary schtick still persisted by the time their turn came up. But if not, it didn't matter too much anyway—what *does* matter is the stranger that the writer describes. It wouldn't be a farfetched guess to assume that this stranger is `NPC_MARCUS`, due to the key alluding to his placement in the Actor List.

That leaves us with his strange quote: "If you wish to talk to me some more, simply act on my name." *Act* on his name? How so?

This is yet another sad instance of ~~careful wording~~ guesswork, with most emphasis on the term "act." Browsing the list of SSB opcodes, we do get some hits for "act":
- `supervision_ExecuteActing`
- `supervision_ExecuteActingSub`

Both opcodes play an Acting Scene. Maybe "act on my name," meant to call one of the two opcodes using `marcus` as the scene name? It seems unlikely to do anything worthwhile, considering there doesn't appear to be any `marcus` scene viewable in SkyTemple...but the worst that could happen is a crash, so why not?
```js
coro EVENT_DIVIDE {
    supervision_ExecuteActing(LEVEL_MYSTERY, "marcus", 0);
	// ... more code
}
```
Let's start the game in the SkyTemple Debugger and watch the Debug Log, which is the window at the very bottom. We'll know that a scene fails to load if only its `.ssa` is logged, but not its `.ssb`.
```
Ground Event >> Ground Start
Ground Event >> SSB Load SCRIPT/COMMON/unionall.ssb for hanger 0
Ground Event >> Ground Map Change
Ground Event >> SSX Load SCRIPT/MYSTERY/enter.sse for hanger 1
Ground Event >> SSB Load SCRIPT/MYSTERY/enter00.ssb for hanger 1
Ground Event >> SSX Load SCRIPT/MYSTERY/marcus.403 for hanger 3
Ground Event >> SSB Load SCRIPT/MYSTERY/marcus.ssb for hanger 3
```
Oh! An SSB file was found, and we can actually see a scene playing! Looks like this secret cutscene is our prize for completing this event's FORECAST!

## Design
Well, we've solved the FORECAST! The end result just seems to be a hidden script. but out of curiosity, how does it even work under the hood? Is it able to be exploited in some aspects?

Embarassingly so, yes.

### 403: SSA Not Found
The biggest thing that sticks out is the fact that, instead of `marcus.ssa` loading, we actually had `marcus.403` pop up.

If you only had to remember one thing from reading these writeups, it's this: *File extensions are only a suggestion!*

The `.403` extension is just a way to deceive SkyTemple into not showing the `marcus.ssb` script. In truth, it's just an SSA file. And not a particularly interesting one at that, seeing as it only has `NPC_MARCUS` as the only actor. The real meat and bones is found in the SSB file.

However, it's not like anyone can rename their `.ssa` files to `.403` and the game will magically understand how to interpret it. A bit of custom code had to be written to fully make this sneaky little trick work, and here it is!
```arm
.definelabel StationLoadHangerSSA, 0x022E4C3C
.definelabel strcmp, 0x0208982C

; Overlay11
.org StationLoadHangerSSA
.area 0x4
	bl NewExtensionHook
.endarea

; Overlay36
NewExtensionHook:
	push r0,r2,r14
	add r0,r13,#0xC
	ldr r1,=SPECIAL_STR
	bl strcmp
	cmp r0,#0
	ldrne r1,=0x023196C4
	ldreq r1,=NEW_FORMAT
	pop r0,r2,r15
.pool

SPECIAL_STR:
	.asciiz "marcus"
	.align
NEW_FORMAT:
	.asciiz "SCRIPT/%s/%s.403"
	.align
.endarea
```
Nothing fancy, but it gets the job done well enough. If the scene's name is equal to `marcus` (scene names get converted to all lowercase at runtime), then the game will use the format string `SCRIPT/%s/%s.403` rather than `SCRIPT/%s/%s.ssa`.

### 11621: Opcode Not Found
"Hang on just a second," I hear you begin to deduce, "if all you did was make the game accept a different file extension, then I can just change `.403` to `.ssa` and open `marcus.ssb` in SkyTemple!"

And yes, you *can* do exactly that!

![alt text](./keyerror.png "An uncaught exception in SkyTemple consisting of several lines of traceback, boiling down to \"KeyError: 11621\"")

...though it's not like it'd be that easy!

We get a spooky-looking error that ultimately culminates to a `KeyError: 11621`. Participants of this event and later ones might recognize 11621 as the magic number needed to enable custom dialogue box formats. There isn't much importance to 11621 as a number itself—it's somewhat of an homage to [another hack](https://hacks.skytemple.org/h/fragments3) that also displayed 11621 in an error, given that the hack outright encrypted one of its secret scripts! ~~I bet you can guess the cipher used.~~

However, this script doesn't opt for such drastic measures. Analyzing the above error, we see that it failed inside `_read_single_op_code` on [line 233](https://github.com/SkyTemple/skytemple-files/blob/386f8988d12f7a2568b857ce9870cdaf16962eb1/skytemple_files/script/ssb/model.py#L233). At the time of writing this, we can see that this line of code attempts to look up an SSB opcode by its ID. In other words, SkyTemple's decompiler encountered an opcode with the ID 11621, and consequently gave up because it doesn't have any opcode associated with that value!

We can also safely guess how many parameters this custom opcode expects: 0. A cursory glance at `RunNextOpcode` doesn't show any hooks or anything of the sort. ~~And besides, this event took place before custom opcodes were even attempted.~~ With all this in mind, we can write a quick and dirty script that adds 11621 as a new opcode, then decompiles `marcus.ssb`.

Running it, we get...`KeyError: 11622`. Huh. Looks like there are multiple custom opcodes. Let's just add that one as well and pray for success? Now we've got `decompile_marcus_ssb.py`, and running this script will...successfully produce a `marcus.exps`!

Checking the start of the EXPS, we see:
```js
def 0 {
    UNK_11621();
    Null();
    sound_Stop();
    clear $SCENARIO_TALK_BIT_FLAG;
    screen_FadeOutAll(1, 0);
    screen2_FadeOut(1, 0);
    back2_SetMode(0);
	// blah blah more code
```
`Null` (ID 0) is a valid opcode; it just does nothing. What's more likely than the challenge designer placing `UNK_11621` and `Null` is actually having `UNK_11621` take a single parameter of 0. And as the challenge designer, that's exactly what I did: Edit SkyTemple's `pmd2scriptdata.xml` to add a new opcode such that SkyTemple would accept it in compilation. And it works the opposite way as well—editing `pmd2scriptdata.xml` is a valid way to get SkyTemple to decompile `marcus.ssb`! No code needed after all!

So with that, we've cracked this challenge in half!

### Get In The Hex Editor, Marcus
There's actually one last little detail about `marcus.ssb` that the decompilation fails to show ~~or at least, decompilation using the current version of `skytemple-files`~~. An actual participant's first instinct on seeing the decompilation error likely wouldn't be to immediately write a Python script—how about just checking `marcus.ssb` in a hex editor?

```
00001af0: 533a 323a 335d 4265 2073 6565 696e 6720  S:2:3]Be seeing 
00001b00: 796f 752e 5b56 525d 0044 6561 7220 6f74  you.[VR].Dear ot
00001b10: 6865 7277 6f72 6c64 6c79 2070 6c61 7965  herworldly playe
00001b20: 722c 2061 7265 2079 6f75 2063 6865 6174  r, are you cheat
00001b30: 696e 673f 0054 6865 206f 6e6c 7920 7761  ing?.The only wa
00001b40: 7920 796f 7520 6361 6e20 7365 6520 7468  y you can see th
00001b50: 6973 2069 7320 6279 2075 6e69 6e74 656e  is is by uninten
00001b60: 6465 6420 6d65 616e 732e 2059 6f75 2061  ded means. You a
00001b70: 6c6d 6f73 7420 6365 7274 6169 6e6c 7920  lmost certainly 
00001b80: 756e 7061 636b 6564 2074 6865 2052 4f4d  unpacked the ROM
00001b90: 2061 6e64 2073 6561 7263 6865 6420 666f   and searched fo
00001ba0: 7220 7468 6973 2066 696c 652e 204f 7220  r this file. Or 
00001bb0: 7065 7268 6170 7320 796f 7527 7265 206a  perhaps you're j
00001bc0: 7573 7420 7573 696e 6720 6120 6865 7820  ust using a hex 
00001bd0: 6564 6974 6f72 3f00 5765 6c6c 2c20 4920  editor?.Well, I 
00001be0: 7375 7070 6f73 6520 6974 2063 616e 2774  suppose it can't
00001bf0: 2062 6520 6865 6c70 6564 2e20 4920 444f   be helped. I DO
00001c00: 2068 6f70 6520 796f 7527 7265 206e 6f74   hope you're not
00001c10: 2069 6e76 6573 7469 6761 7469 6e67 2074   investigating t
00001c20: 6869 7320 7768 696c 6520 6974 2773 2079  his while it's y
00001c30: 6f75 7220 7475 726e 2c20 6174 206c 6561  our turn, at lea
00001c40: 7374 2e00 416e 7977 6179 2c20 7461 6b65  st..Anyway, take
00001c50: 2061 2068 696b 652e 2e2e 4d61 7269 7573   a hike...Marius
00001c60: 2c20 4972 646b 7769 6120 6f72 2054 6563  , Irdkwia or Tec
00001c70: 6874 6963 6b73 2e00 416e 6420 6966 2069  hticks..And if i
00001c80: 7427 7320 736f 6d65 6f6e 6520 656c 7365  t's someone else
00001c90: 2c20 636f 6e67 7261 7475 6c61 7469 6f6e  , congratulation
00001ca0: 7321 2059 6f75 2772 6520 7374 696c 6c20  s! You're still 
00001cb0: 6368 6561 7469 6e67 2e00                 cheating..
```
Indeed, it can't be helped; nothing can escape the eyes of a hex editor. You don't even *need* to decompile `marcus.ssb` to get all of its strings, since they're all just stored as uncompressed plaintext. A pretty big way to cheese the challenge, but at least it was recognized.

Oversight aside, there *is* something spooky about this string. If you managed to decompile `marcus.ssb` using SkyTemple in some form, this string is mysteriously nowhere to be found. What gives? Is it truly called in the script anywhere?

As it turns out, it is! Checking the [SSB file format](https://projectpokemon.org/home/docs/mystery-dungeon-nds/pmd2-ssb-r49/), we can see just how many strings the script contains. The halfwords at ofsets 0x0 and 0x2 look to be what we want. In `marcus.ssb`, this turns out to be values 0x42 and 0x0, respectively. Counting up our strings in our EXPS, we're definitely short a few.

Turns out, decompilation is a pretty tough job. Decompiling from raw SSB to ExplorerScript has historically always been something of an uphill battle. It's pretty effective and *does* work flawlessly for all base game scripts, but hackers can structure their scripts in ways that the original developers may not have intended. And keep in mind, ExplorerScript is just a user-friendly representation of what SSB *could* have looked like from the original devs' perspective. Nowhere in ROM can we find opcode names that reference `for` or `while` loops. But ExplorerScript still implements them without the use of custom ASM. For constructs like these, it relies on the underlying `Branch` opcodes, of which there are a handful.

So what if we want to see these raw `Branch` opcodes? We don't necessarily have to stare at a hex editor—in `decompile_marcus_ssb.py`, we can change `ssb.to_explorerscript()` to `ssb.to_ssb_script()`. SsbScript is an intermediary between raw SSB and ExplorerScript. It's *much* closer to the raw SSB and doesn't try to make assumptions about fancy flow control constructs. It just reads the raw opcodes and makes them look pretty. Naturally, the decompilation is less likely to fail as a result. If we give it a try...

```js
def 1 for actor ACTOR_NPC_MARCUS {
	// blah blah blah, pretend there's a bunch of code here and also pretend the repo's owner doesn't use targeted routines a bit too much for their own good
    Slide2PositionOffset(1, 1, 0);
    Wait(2);
    flag_CalcValue($LOCAL0, 2, 1);
    @label_23;
    BranchValue($LOCAL0, 4, 86, @label_24);
    Hold();
    UNK_11621();
    Null();
    debug_Print('Dear otherworldly player, are you cheating?');
    debug_Print('The only way you can see this is by unintended means. You almost certainly unpacked the ROM and searched for this file. Or perhaps you\'re just using a hex editor?');
    debug_Print('Well, I suppose it can\'t be helped. I DO hope you\'re not investigating this while it\'s your turn, at least.');
    debug_Print('Anyway, take a hike...Marius, Irdkwia or Techticks.');
    debug_Print('And if it\'s someone else, congratulations! You\'re still cheating.');
}
```
Hey look, there are the super secret strings! The reason for the decompilation flub also becomes somewhat apparent. These debug prints occured after a `Hold` opcode, which, in most sane scripts, marks the end of a routine. But it looks like we have some trailing opcodes after it that can *never* get accessed throughout the script's flow control, hence their omission. Honest enough of a mistake, really.

But don't think that the ExplorerScript decompiler immediately gives up once it finds an opcode like `Hold` or `End`. After all, sometimes scripts *need* to place opcodes after one of them, such as when it uses the opcode `Call`. Where else is a script going to store a local function, after all?

## Solvers
Congratulations to the whopping two solvers! Who could've seen these two coming?
- [irdkwia](https://github.com/irdkwia)
	- Went above and beyond by producing a valid decompilation of `marcus.ssb`!
- [techticks](https://github.com/tech-ticks)
	- Went above and beyond by solving the FORECAST during his 47-hour period! The last part of his scene even directly references `marcus.ssb`!


## Miscellaneous Shenanigans
The following event, MM4, doesn't have a FORECAST, but it *does* have new instances of `marcus.403` and `marcus.ssb`. These aren't particularly important for Lore ™ since the script basically states that Marcus has left the building.

## Takeaways
- **Denoting Completion:** You might have noticed that there wasn't an actual way for a participant to *prove* that they completed this FORECAST. And what counts as completion, anyway? Viewing the script? But what if someone views it in a hex editor? It's a bit of a mess, but that's somewhat expected for the first attempt at something like this. Next time, we should have clear-cut way to discern if someone finished!
- **Avoiding Cheese:** A hex editor trumps all. No file can truly escape it, so the best you can do is make the human using it have a miserable time. Next time, maybe introduce some form of encryption or compression?
- **More Hints:** There's a weird, not-so-fine balance of wanting participants to uncover a secret of yours, but not wanting to announce it to the whole world ~~unless you go the full CTF route~~. It's no longer a secret in that case. Given that only two people solved this FORECAST, more could definitely be done next time to hint at the existence of a secret.
- **Script Manipulation:** We managed to hide several `debug_Print` opcodes in what was otherwise a successful ExplorerScript decompilation. Maybe this could be exploited further in the future to do more devious things?
- **Challenge Structure:** Too much guesswork. Tone that down. Maybe.