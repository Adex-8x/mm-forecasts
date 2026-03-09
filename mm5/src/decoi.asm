.nds
.include "symbols.asm"

.open "arm9.bin", arm9_start
    .org GenerateDailyMissions
    .area 0x0205eac4-GenerateDailyMissions+0x4
        bx r14
        ldr r2,=SPOOKY_TEXT
        b ShowStringInDialogueBox
    SPOOKY_TEXT:
        .ascii "[TS:16139] [VS:1:20][FT:2][CN]DECOI[TS:0][VR][W:100][TS:16136]",10,"[FT:3] [STS][CN]TOP MENU ACCESS GRANTED[W:100][HR][FT:0][BAR][STE][W:90][TS:16137]",10
        .ascii "[HR][STS][CN]User: [jugador][STE] [W:90][HR] [HR][STS][CN]Login: [CS:C][joy][CR][BAR][STE][W:90][TS:16136]",10," [STS][CN]Finished reading C patch section from ov 1:",10,"[CN].text.ov.1.CREATETOPMENU 0x23310e8[STE][W:45]",10," [STS][CN]Finished reading C patch section from ov 1:",10,"[CN].text.ov.1.UPDATETOPMENU 0x2331788[BAR][STE][W:90]",10,10
        .ascii "[TS:16129][VS:1:6][FT:3][CN]PLEASE ADVANCE WHEN READY[VS:1:3][P][TS:7957][VS:3:2][FT:0]Welcome![K] The simple fact that you are reading",10
        .ascii "this message stands as a testament to your",10,"unwavering will and boundless skill.[K]",10,10
        .ascii "As you may have surmised already,[W:20] you have",10,"just passed the entrance exam to join the",10
        .ascii "[FT:2]Dungeon Exploration, Control,",10,"& Obliteration Initiative[FT:0].[K]",10
        .ascii "Otherwise abbreviated as simply [CS:X]DECOI[CR]",10,"(pronounced \"decoy\").[P]"
        .asciiz "[TS:16129][VS:1:4][FT:3][CN]PLEASE COME IN[K]",10,"[CN]MAKE YOURSELF AT HOME[VR][TR]"
        .pool
            .word 0xDEADBEEF
    .endarea


    .org 0x02046864
    .area 0x4
        bl 0x02062BB8
    .endarea

    .org 0x0204686c
    .area 0x4
        bl CreateDialogueBoxAndDecrypt
    .endarea

    .org 0x02062BB8
    .area 0x02062d3c-0x02062BB8+0x4
        ldr r0,=SPECIAL_WINDOW_PARAMS
        bx r14
    CreateDialogueBoxAndDecrypt:
        push r4,r5,r14
        sub r13,r13,#0x54
        bl CreateDialogueBox
        mov r4,r0
        mov r0,r13
        bl GetDsFirmwareInfo
        mov r5,#0
        ldrh r12,[r13,#0x52] ; Length
        ldrh r1,[r13,#0x1C]
        add r0,r13,#0x1E
        b message_loop_next_iter
    message_loop:
        ldrh r2,[r0],#0x2
        cmp r2,#0
        beq message_sanity_check
        eor r1,r1,r2
    message_loop_next_iter:
        cmp r5,r12
        addlt r5,r5,#0x1
        blt message_loop
    message_sanity_check:
        ldr r0,=#53180
        cmp r0,r1
        beq message_ok
    message_incorrect:
        bl CardPullOut
        b message_incorrect
    message_ok:
        mov r0,#1
        bl LoadStaffont
    ; Time to decrypt the custom Top Menu...
        mov r5,#0
    addr_loop:
        ldr r0,=ADDR_LIST
        add r1,r0,#4
        ldr r1,[r1,r5, lsl #0x2]
        ldr r0,[r0,r5, lsl #0x2]
        cmp r0,#0
        moveq r0,r4
        addeq r13,r13,#0x54
        popeq r4,r5,r15
        add r5,r5,#2
        bl DecoiDecryption
        b addr_loop
    ADDR_LIST:
        .word GenerateDailyMissions+0x4, 0x0205E9D0
        .word 0x23310e8, 0x2331288
        .word 0x2331788, 0x2331dd8
        .word 0x233250c, 0x2334ed2
        .word 0x0, 0x0

    DecoiDecryption: ; r0: start, r1: end, ret: sum
        push r4-r6,r14
        sub r13,r13,#0x54
        mov r4,r0
        mov r5,r1
        mov r0,r13
        bl GetDsFirmwareInfo
        ldrh r6,[r13,#0x52] ; Length
        lsl r6,r6,#0x1
        add r0,r13,#0x1C
        mov r1,#0x0
    decryption_loop:
        ldrh r2,[r0,r1]
        ldrh r3,[r4]
        eor r2,r2,r3
        strh r2,[r4],#0x2
        add r1,r1,#0x2
        cmp r1,r6
        movge r1,#0x0
        cmp r4,r5
        ble decryption_loop
        add r13,r13,#0x54
        pop r4-r6,r15
    .pool
    SPECIAL_WINDOW_PARAMS:
        .word UpdateDialogueBox
        .byte 0x2
        .byte 0x2
        .byte 0x1C
        .byte 0x14
        .byte 0x00
        .byte 0xFA
        .fill 0x6, 0x0
    .endarea

    .org 0x020469b8 ; Flags
    .area 0x4
        .word 0x1018
    .endarea

    .org 0x02046910
    .area 0x4
        bl GenerateDailyMissions+0x4
    .endarea
.close


.open "overlay0.bin", overlay0_start
    .org 0x022be924 ; randint
    .area 0x4
        mov r0,#0
    .endarea

    .org 0x022be1a4 ; bgm
    .area 0x4
        nop
    .endarea
    
    .org 0x022be27c ; creates wifi box
    .area 0x4
        nop
    .endarea

    .org 0x022be950 ; load bgp background
    .area 0x4
        nop
    .endarea
.close

.open "overlay1.bin", overlay1_start
    ; Maybe repurpose this
        .org CreateMainMenus
        .area 0x4; 0x0233257c-CreateMainMenus+0x4
            b CustomCreateTopMenu
        .endarea

        ; UpdateManyMenus
        .org 0x02331784
        .area 0x4; 0x02332504-0x02331784+0x4
            b CustomUpdateTopMenu
        .endarea

    .org 0x0232fcd8
    .area 0x4
        bl LoadBgpBackground
    .endarea

    .org 0x02330174
    .area 0x4
        bl LoadBgpBackground
    .endarea

    .org 0x0232f798
    .area 0x4
        bl LoadBgpBackground
    .endarea

    .org 0x0232f2e4
    .area 0x4
        bl LoadBgpBackground
    .endarea

    .org 0x0232f318
    .area 0x4
        bl LoadBgpBackground
    .endarea

    .org 0x02330a84
    .area 0x4
        bl LoadBgpBackground
    .endarea

    .org 0x0232FC70
    .area 0x10
        nop
        nop
        nop
        nop
    .endarea

    .org 0x0232FCA4
    .area 0xC
        nop
        nop
        mov r0,#0x0
    .endarea
.close
