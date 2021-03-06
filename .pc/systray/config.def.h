/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-14-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#333333";
static const char normbgcolor[]     = "#051121";
static const char normfgcolor[]     = "#ffffff";
static const char selbordercolor[]  = "#09384f";
static const char selbgcolor[]      = "#09384f";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class        instance    title       tags mask     isfloating   monitor */
  { "MPlayer",      NULL,       NULL,       0,            True,    -1 },
  { "Gimp",         NULL,       NULL,       0,            True,    -1 },
  { "Gvolwheel",    NULL,       NULL,       0,            True,    -1 },
  { "trayer",       NULL,       NULL,      ~0,            True,    -1 },
  { "stalonetray",  NULL,       NULL,      ~0,            True,    -1 }
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "TTT",      bstack },
 	{ "===",      bstackhoriz },
  { "[+]",      gaplessgrid },
  { .symbol = NULL,   .arrange = NULL    },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvtc", NULL };
static const char *quitcmd[]  = { "killall", "startdwm", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_x,      killclient,     {0} },
  { MODKEY,                       XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_space,  nextlayout,     {0} },
	{ MODKEY|ShiftMask,             XK_space,  prevlayout,     {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
  { MODKEY|ShiftMask,             XK_r,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = quitcmd } },
  { MODKEY,                       XK_Down,   moveresize,     {.v = (int []){ 0, 25, 0, 0 }}},
  { MODKEY,                       XK_Up,     moveresize,     {.v = (int []){ 0, -25, 0, 0 }}},
  { MODKEY,                       XK_Right,  moveresize,     {.v = (int []){ 25, 0, 0, 0 }}},
  { MODKEY,                       XK_Left,   moveresize,     {.v = (int []){ -25, 0, 0, 0 }}},
  { MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = (int []){ 0, 0, 0, 25 }}},
  { MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = (int []){ 0, 0, 0, -25 }}},
  { MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = (int []){ 0, 0, 25, 0 }}},
  { MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = (int []){ 0, 0, -25, 0 }}},
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

