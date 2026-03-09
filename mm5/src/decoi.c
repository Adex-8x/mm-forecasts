#include <pmdsky.h>
#include <cot.h>
#include "extern.h"

// 0x0231E2FC is Touch Screen
// 0x0231E2B8 is Top Screen
// 0 is white in all, 1 is fade out all, 2 is white out all

// MUST STAY AT 0x23dbb49 FOR OV36

// Keep it non-null to mitigate brute-force
uint8_t __attribute__((section(".PAIN"))) TOP_MAIN_MENU_ID = 102;
uint8_t __attribute__((section(".PAIN"))) TOP_MENU_STATE = 116;
uint8_t __attribute__((section(".PAIN"))) TOP_DBOX_ID = 137;
uint8_t __attribute__((section(".PAIN"))) TOP_DBOX_CASTLE_ID = 212;
uint8_t __attribute__((section(".PAIN"))) TOP_DBOX_SUNKERN_ID = 6;
uint8_t __attribute__((section(".PAIN"))) TOP_DBOX_HIM_ID = 34;
uint8_t __attribute__((section(".PAIN"))) TOP_LAST_RESULT_ID = 231;

char __attribute__((section(".PAIN"))) FILEPATH_TOPSCREEN[] = "/TOP/test.bgp";
char __attribute__((section(".PAIN"))) FILEPATH_TOUCHSCREEN[] = "/TOP/title_0.bgp";
char __attribute__((section(".PAIN"))) INTRO_TEXT[] = "[W:70][FT:0][VR]If you direct your attention up above...[K]\nYou'll find our state-of-the-art chatbots ready\nto answer any and all questions you may have![K]\n\nDon't worry,[W:20][N:0:1][N:1:1][N:2:1] they haven't been\nprogrammed to bite just yet![P]The [CS:K]Minccino[CR] you see above represents our\nfounder and leader,[W:20][N:0:0][VS:1:2] [CS:N]Dr. Martin Castle[CR]![K][VR]\nHe's responsible for (literal) world-shattering\ndiscoveries such as [VS:1:5][TS:16129][CS:B]~5BREDACTED~5D[CR],[W:20] [CS:B]~5BREDACTED~5D[CR],[W:20][TR][VR]\nand most recently,[W:20][TS:16129][VS:1:5] [CS:B]~5BREDACTED~5D[CR][VR][TR]![K]\n\nThe [CS:K]Sunkern[CR] right below him doesn't have a\nnickname;[W:20][N:1:0] her parents weren't too fond of her.[K]\nHer claim to fame is being our lead engineer\nand a rhyming connoisseur![P][N:2:0]With introductions complete,[W:20] please take this\nopportunity to familiarize yourself with\nour mission and modes of operation!";

uint16_t __attribute__((section(".PAIN"))) PORTRAIT_MONSTER_IDS[3] = {582, 191, 581};
uint8_t __attribute__((section(".PAIN"))) PORTRAIT_OFFSETS[3] = {0, 6, 12};

/*
    For the TALK_QUEUE, we'll look at the first two bits to determine what to do.
    - 0b00 = No speaker; end
    - 0b01 = Dr. Castle
    - 0b10 = Sunkern
    - 0b11 = ???
    Is this even really a queue? No but I'm pretending that it is now get out of my house
*/

int __attribute__((section(".PAIN"))) TALK_QUEUE = 4316;
uint8_t __attribute__((section(".PAIN"))) TALK_IDX = 0;
// I don't know why I didn't use a struct for this tbh
uint8_t __attribute__((section(".PAIN"))) INIT_TALK_IDXS[] = {0, 6, 14, 24, 29, 36, 40}; // used to determine which string to begin at
int __attribute__((section(".PAIN"))) TALK_STATES[] = {0b100110011001, 0b1001100111011001, 0b10011001110110011001, 0b1110011001, 0b10011110011001, 0b011001, 0b11011001}; // used to determine speaker order
uint8_t __attribute__((section(".PAIN"))) ALT_TALK_IDXS[] = {44, 46, 50, 54, 56, 36, 40}; // used to determine which string to begin at
int __attribute__((section(".PAIN"))) ALT_TALK_STATES[] = {0b1001, 0b10011001, 0b11011001, 0b1001, 0b011001, 0b011001, 0b11011001}; // used to determine speaker order


char __attribute__((section(".PAIN"))) CHATBOT_00[] = "[N:0:4]Have you ever stopped to think how\nit's such a strange time to be alive?[C][VS:1:2]I mean...[K][VR]our world practically revolves\naround mystery dungeons.[C][N:0:0]Can you imagine a world without them?[K]\nIt'd be much more peaceful,[W:20] no?";
char __attribute__((section(".PAIN"))) CHATBOT_01[] = "[N:1:1]I highly doubt there's anything on the\ncontrary to show.";
char __attribute__((section(".PAIN"))) CHATBOT_02[] = "That idea of peace is what fuels [CS:X]DECOI[CR].[K][N:0:1][N:2:1]\nRidding the world of all dungeons![C][N:0:0][N:2:0]If you believe this is some outlandish\ndream,[W:20] try viewing life through our lens.";
char __attribute__((section(".PAIN"))) CHATBOT_03[] = "[N:1:0]We've researched ways to keep the world\nrunning after the [CS:C]Great Cleanse[CR]...[K][N:1:4][W:90][N:1:0][CS:C]~99[CR]";
char __attribute__((section(".PAIN"))) CHATBOT_04[] = "[N:0:1]Indeed![K] We've been in operation for years\nnow,[W:20] making sure to cover all our bases...[C][N:0:4]But while we've proposed our plans to\nsome more...[K][VS:1:3]\"respected\"[VR][W:10] organizations...[C]Every single one rejected to collaborate.[K][N:0:5]\n[VS:1:3]And not always in a nice way,[W:20] too...[VR][C][N:0:0]But then again,[W:20] can you really expect\nglobal change to not rock the boat?";
char __attribute__((section(".PAIN"))) CHATBOT_05[] = "So if anyone gets in our way,[W:20][N:1:15] we won't\nhesitate to go for the throat![N:0:17][N:2:1]";

char __attribute__((section(".PAIN"))) CHATBOT_06[] = "\"In order to destroy all dungeons,[W:20] you\nmust first define how best to explore.\"";
char __attribute__((section(".PAIN"))) CHATBOT_07[] = "- [CS:N]Dr. Martin Castle[CR],\n[CLUM_SET:64][CS:C]The Art of War[CR][C][N:1:1]But yes;[W:10] while our world certainly has no\nshortage of explorers,[W:20] we can do more.";
char __attribute__((section(".PAIN"))) CHATBOT_08[] = "We believe in no such materialistic\ntemptations like treasure or fame.[C]Our [CS:C]Exploration Branch[CR] is simply trained\nto collect as much intel as possible.[C][N:0:4]How do we go about finding new leads?[K]\nWhat kinds of Pok~E9mon live in a dungeon?";
char __attribute__((section(".PAIN"))) CHATBOT_09[] = "[N:2:4][TS:16131][CS:B][VS:1:2]Nnq pseh lqzwinnngoc, ivhvo lf qr fvqh\nfvhwdzvhttu ws wsht qwzht eihvk rdc?[VR][TR][CR]";
char __attribute__((section(".PAIN"))) CHATBOT_10[] = "[N:0:0]To answer all these questions and more,[W:20]\nwe can't be afraid to dirty our hands.";
char __attribute__((section(".PAIN"))) CHATBOT_11[] = "[N:1:0]No matter by dirt or by blood,[W:20] we are\ncertain that everyone understands.";
char __attribute__((section(".PAIN"))) CHATBOT_12[] = "[N:0:4]Or,[W:20] rather--[W:10][N:0:0][VS:1:2]WILL[VR][W:5] understand with time.[K]\nAnd as far as you,[W:20] [jugador]...[C]It takes a truly dedicated explorer for\nsomeone to even access our Top Menu.[C][N:0:1]Who knows?[K] Maybe this branch is just\nthe right fit for someone like you!";
char __attribute__((section(".PAIN"))) CHATBOT_13[] = "[N:1:1]As both a researcher and field operative,[W:20]\nI strongly recommend joining the crew![C]In fact,[W:10] I am currently pursuing a lead\nonly known by seldom few![C][N:1:0][VS:1:3]Alas...[VR][K]without the proper security\nclearance,[W:20][N:1:1] telling would entail killing you.";

char __attribute__((section(".PAIN"))) CHATBOT_14[] = "[N:0:4]This is a rather broad topic,[W:20]\nbut if we were to sum it all up...[C][N:0:0]The [CS:C]Control Branch[CR] dedicates itself to\nwhat we call \"worldwide maintenance\".[C]Of course,[W:20] keeping the economy afloat\nafter destroying dungeons is important...[C][N:0:1]But there's more![K] Such as creating new\nways to tame dungeon residents!";
char __attribute__((section(".PAIN"))) CHATBOT_15[] = "[N:1:1]And training brave fighters to quell\neven the wrath of world presidents!";
char __attribute__((section(".PAIN"))) CHATBOT_16[] = "[N:0:5][VS:1:4]Hahaha...[VS:1:2][K]while I would like to think\notherwise,[W:20][VR] I know peace is [W:10][VS:1:3]ENFORCED.[VR][C]So yes,[W:20][N:0:2] it wouldn't be out of place to\nprepend \"damage\" to our [CS:C]Control Branch[CR].[C]An unfortunate necessity,[W:20][N:0:4] but a\nnecessity nonetheless.";
char __attribute__((section(".PAIN"))) CHATBOT_17[] = "A rewarding path to take,[W:20] no doubt,[W:10][N:1:0]\nbut it comes bundled with stress.";
char __attribute__((section(".PAIN"))) CHATBOT_18[] = "[N:0:16]Well,[W:20] that's only one part of the branch.[K][VS:1:2]\nPivoting awaaaaaaay from violence...[VR][C][N:0:0]I find dungeon inhabitants fascinating.[K]\nIn fact,[W:20][N:0:11][TS:16131][VS:1:5] [CS:B]~5BREDACTED~5D[CR][VR][W:10][TR] was one himself!";
char __attribute__((section(".PAIN"))) CHATBOT_19[] = "[N:2:2][TS:16131][CS:B][VS:1:2]Zoilrs cxx wiuy ze yhedb ksg bf ynt\ngkmzuv xrik wnnarx ehdvo jrwx ag pi.[VR][TR][CR]";
char __attribute__((section(".PAIN"))) CHATBOT_20[] = "[N:0:17]";
char __attribute__((section(".PAIN"))) CHATBOT_21[] = "[N:1:17]";
char __attribute__((section(".PAIN"))) CHATBOT_22[] = "[W:30][N:0:12]A-[W:10][N:0:0]and THAT'S[W:15] just one example of why\n[CS:X]DECOI[CR] is vital![K] To help those in need![C]And since dungeons corrupt inhabitants\npast the point of any rational thought...[C][N:0:1]We'll help control their hostile nature\nwithout asking![K] No strings attached!";
char __attribute__((section(".PAIN"))) CHATBOT_23[] = "[N:1:1]If you have any ethical concerns,[W:20]\nwe'll be sure to get them all patched.";

char __attribute__((section(".PAIN"))) CHATBOT_24[] = "[N:0:9]We will not settle for anything less\nthan the extinction of mystery dungeons.[C]And I DO[W:10] mean \"extinction\".[K] A dungeon\nis practically a lifeform of its own.[C]We cannot deny that this world has made\nadmirable strides in adapting to them...";
char __attribute__((section(".PAIN"))) CHATBOT_25[] = "[N:1:9]But to remain complacent is equivalent\nto the promotion of mayhem.[C]We aim to pull the problem's roots out;[W:10]\nteams and guilds merely snip the stem.[C][N:1:1]And should you have any doubt,[W:20] I've\ndone research no one can ever condemn.";
char __attribute__((section(".PAIN"))) CHATBOT_26[] = "[N:0:0]Oh,[W:10] you've [N:0:11][VS:1:3]DEFINITELY[VR][W:10] made progress\nin implementing dungeon demolition![C]Being able to craft our own [CS:I]Orbs[CR] was\nthe first major breakthrough,[W:20] sure...[C][VS:1:2]But just recently...![VR][K][N:0:0][W:60][N:0:4][W:90] No,[W:10] I think I'll\nhold off on making that info public.[C][N:0:0]Want to know more?[K][N:0:1] Then consider\njoining the [CS:C]Obliteration Branch[CR]!";
char __attribute__((section(".PAIN"))) CHATBOT_27[] = "The details don't matter all that much\nwhen you're given a big carte blanche.";
char __attribute__((section(".PAIN"))) CHATBOT_28[] = "[N:2:16][TS:16131][CS:B][VS:1:2]Wufw fq gxvo bf yiapxefs hzozpiae\nOHJAFH tozwiemvqk kcxv dmjnf...[N:0:17][N:1:2][C][W:60][N:0:99] [W:30][N:1:12][W:15] [N:1:99][CLUM_SET:4][W:30][N:2:4][W:60]Loh'ui qjhr ZZFAEAZPIP hr hylxy\nlohu tmgw qsakuxef?[VR][TR][CR]";

char __attribute__((section(".PAIN"))) CHATBOT_29[] = "[N:0:9]That's classified.";
char __attribute__((section(".PAIN"))) CHATBOT_30[] = "[N:1:16]No,[W:10] it just sounds like someone\ncan't swallow their pride.";
char __attribute__((section(".PAIN"))) CHATBOT_31[] = "[N:0:16][VS:1:4]Fiiiiine.[VR][K] About me...[C][TS:16131] [N:0:0][STS][CN][CS:C]About Me[CR][BAR]\n[CN]Language ID: ARM:LE:32:v5t (1.103)[STE][TR][W:30]";
char __attribute__((section(".PAIN"))) CHATBOT_32[] = "Please forgive the doctor's sarcasm,[W:20] as\nhe's not fond of these kinds of talks.[C][N:1:0]But as for me,[W:20] I tend to partake in\ndefenestration and long beach walks.";
char __attribute__((section(".PAIN"))) CHATBOT_33[] = "[TS:16131][CS:B][VS:1:2]V rrfizhoc tcjn tog lrfc evoezht trd...[K][N:2:11]\nQmmei S kfoyd zdoq mry cwdy?[VR][TR][CR]";
char __attribute__((section(".PAIN"))) CHATBOT_34[] = "[N:0:17]W-[W:5]well,[W:20] if you both are going to do it...[C][VS:1:3]I...[K][VS:1:6]erm...[VS:1:2][K][N:0:2][W:90]like coffee and metafiction?[VR]";
char __attribute__((section(".PAIN"))) CHATBOT_35[] = "[N:1:4]Coffee's less of a hobby and\nmore of an addiction.";

char __attribute__((section(".PAIN"))) CHATBOT_36[] = "Well now,[W:20] I suppose this is the end.[K]\nAnd a new beginning,[W:20] soon enough...[C][N:0:1]While I'm afraid we couldn't leak TOO[W:10]\nmuch of our inner workings...[K][N:1:1][N:2:1]thank you![C]Thanks for taking an interest in [CS:X]DECOI[CR]![K]\nSeeing you here just feels like fate!";
char __attribute__((section(".PAIN"))) CHATBOT_37[] = "[N:1:11]Perhaps this will help combat our\nrather high turnover rate...!";
char __attribute__((section(".PAIN"))) CHATBOT_38[] = "[N:0:0]But before we go,[W:20] here's a link to our\napplication form.[K] Please wait...";

char __attribute__((section(".PAIN"))) CHATBOT_39[] = "Oh.[K][N:0:14][VS:1:2] Okay.[VR][K][N:0:15] I see.[K][VS:1:4][N:0:18] How.[K] It.[K][VR][N:0:14] Is.[C]I bet you're fun at restaurants.[K]\nImagine some waiter brings you a menu.[C]Imagine being such a picky eater that\nthe sight of it triggers fight-or-flight.[C]You sorry,[W:20] sentient baked potato.[C][N:0:99]I didn't even want to talk anyway.[K][W:600][VS:1:3][N:0:16] Ahem.[VR][C][N:0:0]Thanks for faking an interest in [CS:X]DECOI[CR].[K]\nSeeing you here just feels like fate.";

char __attribute__((section(".PAIN"))) CHATBOT_40[] = "[N:0:1]All done![K] Don't lose that,[W:20] okay?[C][N:0:4]In fact,[W:20] I'd recommend taking a picture\nof that popup window,[W:20] if you can.[C][N:0:0]The form will ask you some verification\nquestions,[W:20] so keep this info nearby!";
char __attribute__((section(".PAIN"))) CHATBOT_41[] = "[N:1:0]But with all that said,[W:20][VS:1:2] it looks like\nwe must finally say goodbye.[VR]";
char __attribute__((section(".PAIN"))) CHATBOT_42[] = "[N:0:1]Until next time![K] And don't forget...[C][N:0:10][N:1:10][N:2:0][VS:1:4]Nandemodekiru![VR]";
char __attribute__((section(".PAIN"))) CHATBOT_43[] = "[TS:16131][W:30][N:0:99] [W:60][N:1:99] [CLUM_SET:4][TR][W:120][N:2:1][W:90][VS:1:2]Nandemodekiru.[VR][K][TS:16131][N:2:99] [TR][W:60]";

// Alt text
char __attribute__((section(".PAIN"))) CHATBOT_44[] = "We make dungeons go boom.";
char __attribute__((section(".PAIN"))) CHATBOT_45[] = "[N:1:1]Thus chaos will never bloom!";

char __attribute__((section(".PAIN"))) CHATBOT_46[] = "I might not look that intimidating as\nan explorer,[W:20] but truth be told...[C][N:0:1]I don't think anyone who's been on the\nreceiving end of my [CS:M]Tail Slap[CR] is alive.";
char __attribute__((section(".PAIN"))) CHATBOT_47[] = "Skill Link + Technician + STAB\n[CS:M]Tail Slap[CR] = [CS:B]Unalive[CR]";
char __attribute__((section(".PAIN"))) CHATBOT_48[] = "[N:0:14]That was your laziest rhyme yet.";
char __attribute__((section(".PAIN"))) CHATBOT_49[] = "Wanna[W:10][N:1:15][VS:1:3] BE[N:0:16]T?[VR]";

char __attribute__((section(".PAIN"))) CHATBOT_50[] = "[N:0:4]All things considered,[W:20] we have to accept\nthat we can't control everything.";
char __attribute__((section(".PAIN"))) CHATBOT_51[] = "[N:1:1]But that doesn't mean we DON'T have\nfree will or anything!";
char __attribute__((section(".PAIN"))) CHATBOT_52[] = "[N:0:0]Right![K][N:0:4][VS:1:2] But just imagine if we didn't...[VR][C]That might be my biggest fear,[W:20] honestly.[C]The realization that everything I've done\nis just the whims of someone I can't see.";
char __attribute__((section(".PAIN"))) CHATBOT_53[] = "[N:2:4][TS:16131][CS:B][VS:1:10]...[VR][TR][CR]";

char __attribute__((section(".PAIN"))) CHATBOT_54[] = "One scrapped implementation for\ndungeon demolition involved [CS:M]Explosion[CR].[C]As in,[W:20] we hire a bunch of [CS:K]Electrode[CR] to\nsit on each dungeon floor and...[K][N:0:17][VS:1:3]y'know.[VR]";
char __attribute__((section(".PAIN"))) CHATBOT_55[] = "[N:1:17]Doesn't take an ethics committee to find\nout why we all said \"no\".";

char __attribute__((section(".PAIN"))) CHATBOT_56[] = "[N:0:2]Please pick anything else.[K] I can't stand\ntalking about myself.[C]Why is this option even here?[K]\nJust for me to suffer?";
char __attribute__((section(".PAIN"))) CHATBOT_57[] = "Oh come now,[W:20] surely you've been\nthrough much rougher.";
char __attribute__((section(".PAIN"))) CHATBOT_58[] = "Maybe,[W:20] yeah,[W:10][VS:1:2] but...[VR][K][N:0:5][VS:1:4]\nIt's just...[VR][C][VS:1:10]...[C][N:0:2][W:90][N:0:5][VS:1:2]I don't know.[VR]";

char* __attribute__((section(".PAIN"))) OPTION_TEXT[] = {CHATBOT_00, CHATBOT_01, CHATBOT_02, CHATBOT_03, CHATBOT_04, CHATBOT_05, CHATBOT_06, CHATBOT_07, CHATBOT_08, CHATBOT_09, CHATBOT_10, CHATBOT_11, CHATBOT_12, CHATBOT_13, CHATBOT_14, CHATBOT_15, CHATBOT_16, CHATBOT_17, CHATBOT_18, CHATBOT_19, CHATBOT_20, CHATBOT_21, CHATBOT_22, CHATBOT_23, CHATBOT_24, CHATBOT_25, CHATBOT_26, CHATBOT_27, CHATBOT_28, CHATBOT_29, CHATBOT_30, CHATBOT_31, CHATBOT_32, CHATBOT_33, CHATBOT_34, CHATBOT_35, CHATBOT_36, CHATBOT_37, CHATBOT_38, CHATBOT_39, CHATBOT_40, CHATBOT_41, CHATBOT_42, CHATBOT_43, CHATBOT_44, CHATBOT_45, CHATBOT_46, CHATBOT_47, CHATBOT_48, CHATBOT_49, CHATBOT_50, CHATBOT_51, CHATBOT_52, CHATBOT_53, CHATBOT_54, CHATBOT_55, CHATBOT_56, CHATBOT_57, CHATBOT_58};

char __attribute__((section(".PAIN"))) APPLICATION_PROMPT[] = "[STS][FT:2][CN]DECOI Application Form[FT:0][BAR]\n[FT:3][CN]SIGN UP BELOW\n[CN]PLEASE UPLOAD SAVE FILE\n[CN]AND INPUT THE FOLLOWING INFO\n[FT:0][HR][CN]USERNAME: [jugador]\n[CN]SIGN-OFF: [CS:C][joy][CR]\n\n[HR][CN][CS:N]https://forms.gle/TT8BYjAEMdH4tLAM7[CR][STE]";

char __attribute__((section(".PAIN"))) DEFAULT_USERNAME[10] = "Unknown";

char __attribute__((section(".PAIN"))) DEFAULT_TEXT[] = "";

void __attribute__((used))__attribute__((section(".CREATE"))) CustomCreateTopMenu()
{
    struct preprocessor_flags DBOX_PREPROCESSOR_FLAGS = {.flags_1 = 0b1100, .flags_11 = 0b10}; // 0x1018
    struct window_params INITIAL_DBOX_PARAMS = { .x_offset = 0x2, .y_offset = 0x2, .width = 0x1C, .height = 0x14, .box_type = 0xFA };
    struct portrait_params PORTRAIT_PARAMS;
    for(int i = 0; i < 3; i++)
    {
        int portrait_id = CreatePortraitBox(1, 5-i, false);
        InitPortraitParamsWithMonsterId(&PORTRAIT_PARAMS, PORTRAIT_MONSTER_IDS[i]);
        SetPortraitLayout(&PORTRAIT_PARAMS, FACE_POS_STANDARD);
        PORTRAIT_PARAMS.monster_id.val = PORTRAIT_MONSTER_IDS[i];
        PORTRAIT_PARAMS.offset_x = 0;
        PORTRAIT_PARAMS.offset_y = PORTRAIT_OFFSETS[i];
        SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_X, i, portrait_id);
        SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, i, PORTRAIT_MONSTER_IDS[i]);
        SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_HEIGHT, i, PORTRAIT_OFFSETS[i]);
        ShowPortraitInPortraitBox(portrait_id, &PORTRAIT_PARAMS);
    }
    LoadBgpBackground(FILEPATH_TOPSCREEN, 0, 0, 0, 1, true);
    se_Play(9219, 0x100, 0x1F);
    UpdateScreenFadeWrapper(0x0231E2B8, 0, 70);
    TOP_DBOX_ID = CreateDialogueBox(&INITIAL_DBOX_PARAMS);
    SaveScriptVariableValue(NULL, VAR_EVENT_LOCAL, 0);
    SaveScriptVariableValue(NULL, VAR_DUNGEON_EVENT_LOCAL, 0);
    for(int i = 0; i < 6; i++)
        SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_TALK_BIT_FLAG, i, 0);
    ShowStringInDialogueBox(TOP_DBOX_ID, DBOX_PREPROCESSOR_FLAGS, INTRO_TEXT, NULL);
    TOP_MENU_STATE = 0;
    TALK_QUEUE = 0;
}

bool __attribute__((used))__attribute__((section(".UPDATE"))) TOPMENU_GetDsFirmwareNicknameAscii(char* buf)
{
    struct firmware_info firmware_info;
    MemZero(buf, 11);
    GetDsFirmwareInfo(&firmware_info);
    if(firmware_info.nickname_length == 0)
        return false;
    for(int i = 0; i < firmware_info.nickname_length; i++)
    {
        uint16_t nickname_char = firmware_info.nickname[i];
        if(nickname_char == 0)
            break;
        if(nickname_char > 0xFF)
            return false;
        buf[i] = nickname_char;
    }
    return true;
}

void __attribute__((used))__attribute__((section(".UPDATE"))) ResetChatbots(bool update_portraits)
{
                struct preprocessor_flags dbox_flags = {.flags_1 = 0b0010, .flags_11 = 0b00};
                struct portrait_params PORTRAIT_PARAMS;
                ShowStringInDialogueBox(TOP_DBOX_CASTLE_ID, dbox_flags, DEFAULT_TEXT, NULL);
                ShowStringInDialogueBox(TOP_DBOX_SUNKERN_ID, dbox_flags, DEFAULT_TEXT, NULL);
                ShowStringInDialogueBox(TOP_DBOX_HIM_ID, dbox_flags, DEFAULT_TEXT, NULL);
                if(update_portraits)
                {
                    for(int i = 0; i < 3; i++)
                    {
                        int portrait_id = LoadScriptVariableValueAtIndex(NULL, VAR_POSITION_X, i);
                        InitPortraitParamsWithMonsterId(&PORTRAIT_PARAMS, PORTRAIT_MONSTER_IDS[i]);
                        SetPortraitLayout(&PORTRAIT_PARAMS, FACE_POS_STANDARD);
                        PORTRAIT_PARAMS.monster_id.val = PORTRAIT_MONSTER_IDS[i];
                        PORTRAIT_PARAMS.offset_x = 0;
                        PORTRAIT_PARAMS.offset_y = PORTRAIT_OFFSETS[i];
                        ShowPortraitInPortraitBox(portrait_id, &PORTRAIT_PARAMS);
                    }
                }
}


int __attribute__((used))__attribute__((section(".UPDATE"))) CustomUpdateTopMenu()
{
    switch(TOP_MENU_STATE)
    {
        case 0: // Initial textbox
            if(!IsDialogueBoxActive(TOP_DBOX_ID))
            {
                CloseDialogueBox(TOP_DBOX_ID);
                LoadBgpBackground(FILEPATH_TOUCHSCREEN, 0, 0, 0, 1, false);
                TextboxTransparent();
                TOP_MENU_STATE++;
            }
            break;
        case 1: // After initial textbox; set up stuff
            struct simple_menu_id_item simple_options[6];
            struct window_params menu_params = { .x_offset = 4, .y_offset = 9, .width = 0x18, .box_type = 0xFF };
            struct window_flags menu_flags = { .a_accept = true, .b_cancel = false, .se_on = true, .partial_menu = true};
            struct window_params chatbot_dbox_params = { .x_offset = 0x6, .y_offset = 0x1, .width = 0x19, .screen = 0x1, .height = 0x4, .box_type = 0xFA };
            for(int i = 0; i < 6; i++)
            {
                simple_options[i].string_id = i+491;
                simple_options[i]._padding = 0;
                simple_options[i].result_value = i;
            }
            simple_options[6].string_id = NULL;
            simple_options[6]._padding = NULL;
            simple_options[6].result_value = NULL;
            TOP_MAIN_MENU_ID = CreateSimpleMenuFromStringIds(&menu_params, menu_flags, NULL, simple_options, 7);
            TOP_DBOX_CASTLE_ID = CreateDialogueBox(&chatbot_dbox_params);
            chatbot_dbox_params.y_offset = 0x7;
            TOP_DBOX_SUNKERN_ID = CreateDialogueBox(&chatbot_dbox_params);
            chatbot_dbox_params.y_offset = 0xD;
            TOP_DBOX_HIM_ID = CreateDialogueBox(&chatbot_dbox_params);
            PlayBgmByIdVolumeVeneer(194, 0, 255);
            TOP_MENU_STATE++;
            break;
        case 2: // Main menu loop
            if(!IsSimpleMenuActive(TOP_MAIN_MENU_ID))
            {
                TOP_LAST_RESULT_ID = GetSimpleMenuResult(TOP_MAIN_MENU_ID);
                if(TOP_LAST_RESULT_ID >= 5)
                    CloseSimpleMenu(TOP_MAIN_MENU_ID);
                else
                    SaveScriptVariableValue(NULL, VAR_EVENT_LOCAL, 1);
                if(LoadScriptVariableValueAtIndex(NULL, VAR_SCENARIO_TALK_BIT_FLAG, TOP_LAST_RESULT_ID) == 0)
                {
                    TALK_QUEUE = TALK_STATES[TOP_LAST_RESULT_ID];
                    TALK_IDX = INIT_TALK_IDXS[TOP_LAST_RESULT_ID];
                }
                else
                {
                    TALK_QUEUE = ALT_TALK_STATES[TOP_LAST_RESULT_ID];
                    TALK_IDX = ALT_TALK_IDXS[TOP_LAST_RESULT_ID];
                }
                if(TALK_IDX == 36)
                {
                    if(LoadScriptVariableValue(NULL, VAR_EVENT_LOCAL) == 0)
                        OPTION_TEXT[TALK_IDX] = CHATBOT_39; // If you exited without pressing anything
                    ChangeVolumeBgm(30, 0);
                }
                SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_TALK_BIT_FLAG, TOP_LAST_RESULT_ID, 1);
                TOP_MENU_STATE++;
            }
            break;
        case 3: // Speaker queue!
            int current_talk_candidate = TALK_QUEUE & 0b11;
            struct preprocessor_flags dbox_flags = {.flags_1 = 0b1110, .flags_11 = 0b10};
            if(current_talk_candidate != 0b00)
            {
                switch(current_talk_candidate)
                {
                    case 0b01:
                        TOP_DBOX_ID = TOP_DBOX_CASTLE_ID;
                        break;
                    case 0b10:
                        TOP_DBOX_ID = TOP_DBOX_SUNKERN_ID;
                        break;
                    default:
                        TOP_DBOX_ID = TOP_DBOX_HIM_ID;
                        break;
                }
                ShowStringInDialogueBox(TOP_DBOX_ID, dbox_flags, OPTION_TEXT[TALK_IDX], NULL);
                TOP_MENU_STATE++;
            }
            else if(TOP_LAST_RESULT_ID < 5)
            {
                ResetChatbots(true);
                ResumeSimpleMenu(TOP_MAIN_MENU_ID);
                TOP_MENU_STATE--;
            }
            else if(LoadScriptVariableValue(NULL, VAR_DUNGEON_EVENT_LOCAL) != 581)
            {
                // Show appplication prompt
                StopBgmCommand();
                struct preprocessor_flags link_flags;
                struct window_params link_params = { .x_offset = 0x2, .y_offset = 0x2, .width = 0x1C, .height = 0x14, .box_type = 0xFF };
                struct clock_info clock_info;
                struct firmware_info firmware_info;
                int link_box_id = CreateDialogueBox(&link_params);
                ShowStringInDialogueBox(link_box_id, link_flags, APPLICATION_PROMPT, NULL);
                TALK_QUEUE = TALK_STATES[TOP_LAST_RESULT_ID+1];
                TALK_IDX = INIT_TALK_IDXS[TOP_LAST_RESULT_ID+1];
                // Save stuff
                GetDsFirmwareInfo(&firmware_info);
                GetCurrentClockInfo(&clock_info);
                if(TOPMENU_GetDsFirmwareNicknameAscii(FILEPATH_TOUCHSCREEN))
                    SaveScriptVariableValueBytes(VAR_HERO_FIRST_NAME, FILEPATH_TOUCHSCREEN, 10);
                else
                    SaveScriptVariableValueBytes(VAR_HERO_FIRST_NAME, DEFAULT_USERNAME, 10);
                SaveScriptVariableValue(NULL, VAR_DUNGEON_ENTER, clock_info.second);
                SaveScriptVariableValue(NULL, VAR_DUNGEON_ENTER_MODE, clock_info.minute);
                SaveScriptVariableValue(NULL, VAR_DUNGEON_ENTER_INDEX, clock_info.hour);
                SaveScriptVariableValue(NULL, VAR_GROUND_ENTER, clock_info.day);
                SaveScriptVariableValue(NULL, VAR_GROUND_GETOUT, clock_info.month);
                SaveScriptVariableValue(NULL, VAR_GROUND_MAP, clock_info.year);
                int check1 = firmware_info.message[0];
                int check2 = LoadScriptVariableValueAtIndex(NULL, VAR_HERO_FIRST_NAME, 0);
                int current;
                for(int i = 1; i < firmware_info.message_length; i++)
                {
                    current = firmware_info.message[i];
                    if(current == 0)
                        break;
                    check1 ^= current;
                }
                for(int i = 1; i < 10; i++)
                {
                    current = LoadScriptVariableValueAtIndex(NULL, VAR_HERO_FIRST_NAME, i);
                    if(current == 0)
                        break;
                    check2 += current;
                }
                SaveScriptVariableValue(NULL, VAR_CONDITION, check1);
                SaveScriptVariableValue(NULL, VAR_RECYCLE_COUNT, check1^check2);
                SaveScriptVariableValue(NULL, VAR_DUNGEON_EVENT_LOCAL, 581);
                NoteSaveBase(3);
            }
            else
            {
                ResetChatbots(false);
                TOP_MENU_STATE = 5;
            }
            break;
        case 4: // Wait for current chatbot to finish
            if(!IsDialogueBoxActive(TOP_DBOX_ID))
            {
                TOP_MENU_STATE--;
                TALK_QUEUE >>= 2;
                TALK_IDX++;
            }
            break;
        case 5:
            WaitForever();
            break;
    }
    return 0;
}
