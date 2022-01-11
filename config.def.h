/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const int scalepreview       = 4;        /* Tag preview scaling */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 22;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = {
    "JetBrainsMono NF:pixelsize=13:antialias=true:autohint=true",
    "Noto Color Emoji:pixelsize=13:antialias=true:autohint=true",
};
static const char dmenufont[]       = "JetBrainsMono NF:pixelsize=13:antialias=true:autohint=true";
static const char col_gray1[]       = "#1A1C24";
static const char col_gray2[]       = "#171716";
static const char col_gray3[]       = "#eeeeee";
static const char col_gray4[]       = "#6bd6a3";
static const char col_cyan[]        = "#2e2835";
static const char col_bg[]          = "#09090c";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray4  },
};

/* tagging */
// static const char *tags[] = { "", "", "", "", "", "", "", "", /*, ""*/ };
// static const char *tags[] = { "", "", "", "", "", "", "", /*"", ""*/ };
//static const char *tags[] = { "web", "dev", "term", "file", "data", "sett", "img" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const unsigned int ulinepad	= 0;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 1;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

// static const char *tagsel[][2][2] = {
// 	/*      norm                          sel       */
// 	/*  fg          bg              fg          bg  */
// 	{ { "#f68f00", col_gray1 }, { "#f68f00", col_cyan } },
//     { { "#de3c3c", col_gray1 }, { "#de3c3c", col_cyan } },
// 	{ { "#2eff16", col_gray1 }, { "#2eff16", col_cyan } },
// 	{ { "#4285f4", col_gray1 }, { "#4285f4", col_cyan } },
//     { { "#fff04f", col_gray1 }, { "#fff04f", col_cyan } },
// 	{ { "#ea3ae1", col_gray1 }, { "#ea3ae1", col_cyan } },
// 	{ { "#00c9c9", col_gray1 }, { "#00c9c9", col_cyan } },
// 	{ { "#8900f2", col_gray1 }, { "#8900f2", col_cyan } },
// 	{ { "#ffffff", col_gray1 }, { "#ffffff", col_cyan } },
// };

static const char *tagsel[][2][2] = {
	/*      norm                          sel       */
	/*  fg          bg              fg          bg  */
	{ { col_gray3, col_gray1 }, { col_gray4, col_cyan } },
    { { col_gray3, col_gray1 }, { col_gray4, col_cyan } },
	{ { col_gray3, col_gray1 }, { col_gray4, col_cyan } },
	{ { col_gray3, col_gray1 }, { col_gray4, col_cyan } },
    { { col_gray3, col_gray1 }, { col_gray4, col_cyan } },
	{ { col_gray3, col_gray1 }, { col_gray4, col_cyan } },
	{ { col_gray3, col_gray1 }, { col_gray4, col_cyan } },
	{ { col_gray3, col_gray1 }, { col_gray4, col_cyan } },
	{ { col_gray3, col_gray1 }, { col_gray4, col_cyan } },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Viewnior",  NULL,       NULL,       1 << 6,         0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
    { "><>",      NULL },    /* no layout function means floating behavior */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
};

/* Winicon */
#define ICONSIZE 18   /* icon size in pixels */
#define ICONSPACING 6 /* space (pixels) between icon and title */

/* key definitions */
#define AltMask Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/fish", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run","-l", "10", "-p", "Run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-c", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-p", "Run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[]  = { "rofi","-show", "drun", "-show-icons", NULL };
static const char *stcmd[]  = { "st", NULL };
static const char *kittycmd[]  = { "kitty", NULL };
static const char *rangercmd[]  = { "st", "-e", "ranger", NULL };
// static const char *nmtuicmd[]  = { "st", "-e", "nmtui", NULL };
static const char *bottomcmd[]  = { "st", "-e", "btm", NULL };

/* Actions */
static const char *shutdown[]  = { "sudo", "shutdown", "-h", "now", NULL };
static const char *reboot[]  = { "sudo", "reboot", NULL };
static const char *slock[]  = { "slock", NULL };
static const char *xkill[]  = { "xkill", NULL };
static const char *rofimoji[]  = { "rofimoji", NULL };
static const char *roficalc[]  = { "rofi", "-show", "calc", NULL };

/* Custom scripts */
/* look at the scripts folder */
static const char *dmenuemoji[]  = { "dmenuunicode", NULL };
static const char *print_select[] = { "print_select", NULL };
static const char *print_fullscreen[] = { "print_fullscreen", NULL };
static const char *print_window[] = { "print_window", NULL };
static const char *copygittoken[]  = { "copygittoken", NULL };

/* Move the scripts on scripts folder to /bin */
static const char *volup[] = { "amixer", "-q", "set", "Master", "5%+", NULL };
static const char *voldown[] = { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char *volmute[] = { "amixer", "-q", "set", "Master", "0%", NULL };
static const char *volunmute[] = { "amixer", "-q", "set", "Master", "60%", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = stcmd } },
    { MODKEY|AltMask,               XK_Return, spawn,          {.v = kittycmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = print_select } },
	{ MODKEY|ControlMask,           XK_p,      spawn,          {.v = print_fullscreen } },
	{ MODKEY|ControlMask|ShiftMask, XK_p,      spawn,          {.v = print_window } },
    { MODKEY,                       XK_l,      spawn,          {.v = slock } },
	{ MODKEY|AltMask,               XK_k,      spawn,          {.v = volup } },
    { MODKEY|AltMask,               XK_j,      spawn,          {.v = voldown } },
	{ MODKEY|AltMask,               XK_m,      spawn,          {.v = volmute } },
	{ MODKEY|AltMask,               XK_u,      spawn,          {.v = volunmute } },
	{ MODKEY|AltMask,               XK_f,      spawn,          {.v = rangercmd } },
	{ MODKEY|ControlMask,           XK_m,      spawn,          {.v = bottomcmd } },
	// { MODKEY|ControlMask,           XK_n,      spawn,          {.v = nmtuicmd } },
	{ MODKEY|ControlMask,           XK_s,      spawn,          {.v = shutdown } },
	{ MODKEY|ControlMask,           XK_r,      spawn,          {.v = reboot } },
	{ MODKEY|ControlMask,           XK_g,      spawn,          {.v = copygittoken } },
	{ MODKEY|ControlMask,           XK_e,      spawn,          {.v = rofimoji } },
	{ MODKEY,                       XK_e,      spawn,          {.v = dmenuemoji } },
    { MODKEY|ShiftMask,             XK_c,      spawn,          {.v = roficalc } },
    { MODKEY|ControlMask,           XK_x,      spawn,          {.v = xkill } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_q,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      toggletag,      {.ui = 1} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -2 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +2 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      6)
	TAGKEYS(                        XK_9,                      6)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

