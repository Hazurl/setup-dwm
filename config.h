/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int gappx     = 5;                 /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const unsigned int systrayoutterspacing = 10;   /* systray outter spacing */
static const unsigned int systrayiconsize = 20;			 /* systray icon size */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int force_bar_height   = 24;
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[] = {"Fira Mono:style=Regular:size=10", "Symbols Nerd Font:size=12"};
#define QUOTED_(x) #x
#define QUOTED(x) QUOTED_(x)
#define dmenufont "Fira Mono:style=Regular:size=10"

static const char col_themed_Background[] = "#282a36";
static const char col_themed_CurrentLine[] = "#44475a";
static const char col_themed_Foreground[] = "#f8f8f2";
static const char col_themed_Comment[] = "#6272a4";
static const char col_themed_Cyan[] = "#8be9fd";
static const char col_themed_Green[] = "#50fa7b";
static const char col_themed_Orange[] = "#ffb86c";
static const char col_themed_Pink[] = "#ff79c6";
static const char col_themed_Purple[] = "#bd93f9";
static const char col_themed_Red[] = "#ff5555";
static const char col_themed_Yellow[] = "#f1fa8c";
static const char *colors[][4]      = {
	/*               fg         bg         border     float */
	[SchemeNorm] = { col_themed_Foreground, col_themed_Background, col_themed_Comment, col_themed_Pink },
	[SchemeSel] =  { col_themed_Foreground, col_themed_Comment, col_themed_Purple, col_themed_Purple },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isfakefullscreen monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           0,               -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           1,               -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-bw", "1", "-i", "-c", "-l", "30", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *dmenulayoutcmd[] = { "echo", "\"[]= Tiled~0\n><> Floating~1\n[M] Monocle~2\"", "|", "dmenu", "-d", "'~'", "-bw", "1", "-i", "-c", "-l", "30", "-m", dmenumon, "-fn", QUOTED(dmenufont), NULL };
static const char *termcmd[]  = { "termite", NULL };
static const char *layoutmenu_cmd = "cat <<EOF | xmenu\n[]= Tiled Layout	0\n><> Floating Layout	1\n[M] Monocle Layout	2\nEOF";
static const char *volup[] = {"pavolume", "volup", NULL};
static const char *voldown[] = {"pavolume", "voldown", NULL};
static const char *volmutetoggle[] = {"pavolume", "mutetoggle", NULL};
static const char *lightup[] = {"light", "-A", "10", NULL};
static const char *lightdown[] = {"light", "-U", "10", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             					XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY | ShiftMask,           XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             					XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_o,      layoutdmenu,    {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_agrave, view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave, tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_semicolon, focusmon,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,      {.i = +1 } },
	{0, 														XF86XK_AudioRaiseVolume, spawn, {.v = volup}},
	{0, 														XF86XK_AudioLowerVolume, spawn, {.v = voldown}},
	{0, 														XF86XK_AudioMute, spawn, 				{.v = volmutetoggle}},
	{0, 														XF86XK_MonBrightnessUp, spawn, 	{.v = lightup}},
	{0, 														XF86XK_MonBrightnessDown, spawn,{.v = lightdown}},
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_eacute,                 1)
	TAGKEYS(                        XK_quotedbl,               2)
	TAGKEYS(                        XK_apostrophe,             3)
	TAGKEYS(                        XK_parenleft,              4)
	TAGKEYS(                        XK_minus,                  5)
	TAGKEYS(                        XK_egrave,                 6)
	TAGKEYS(                        XK_underscore,             7)
	TAGKEYS(                        XK_ccedilla,               8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_s, scratchpad_show, {0} },
	{ MODKEY|ShiftMask,             XK_s, scratchpad_hide, {0} },
	{ MODKEY,                       XK_d,scratchpad_remove,{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        layoutxmenu,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

