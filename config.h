/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 6;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 6;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */
static const char *fonts[]          = { "JetBrains Mono Nerd Font:size=10" };
// static const char *fonts[]          = {"FontAwesome:size=12", "Roboto:size=12" };
// static const char *fonts[]          = {  "Roboto:size=12",
// "Noto Color Emoji:pixelsize=12:antialias=true:autohint=true",
// "-*-dejavu sans mono-medium-r-normal-*-10-*-*-*-*-*-*-*"
// };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

static const char col_dark[]        = "#5657F5";
static const char col_light[]       = "#8be9fd";
static const char col_background[]  = "#31313A";
static const char col_background_light[]  = "#5657F5";
static const char white[]           = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { white, col_background, col_background },
	[SchemeSel]  = { white, col_background_light,  col_background_light },
  [SchemeTabActive]  = { white, col_background_light,  col_background_light},
	[SchemeTabInactive]  = { white, col_background,  col_background },
 	[SchemeStatus]  = { white, col_background, "#111111"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { white, col_dark,  "#111111"  }, // Tagbar left selected {text,background,not used but cannot be empty}
  [SchemeTagsNorm]  = { white, col_background,  "#111111"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
};
static const char ptagf[] = "[%s %s]";	/* format of a tag label */
static const char etagf[] = "[%s]";	/* format of an empty tag */
static const int lcaselbl = 0;		/* 1 means make tag label lowercase */	

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Java",     NULL,       NULL,       0,            1,           -1 },
	{ "Galculator",NULL,      NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const unsigned int systraypinning = 2;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

/* Bartabgroups properties */
#define BARTAB_BORDERS 1       // 0 = off, 1 = on
#define BARTAB_BOTTOMBORDER 1  // 0 = off, 1 = on
#define BARTAB_TAGSINDICATOR 1 // 0 = off, 1 = on if >1 client/view tag, 2 = always on
#define BARTAB_TAGSPX 5        // # pixels for tag grid boxes
#define BARTAB_TAGSROWS 3      // # rows in tag grid (9 tags, e.g. 3x3)
static void (*bartabmonfns[])(Monitor *) = { monocle /* , customlayoutfn */ };
static void (*bartabfloatfns[])(Monitor *) = { NULL /* , customlayoutfn */ };

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "shiftview.c"
#include <X11/XF86keysym.h>
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
 	{ "[]=",      tile },    /* first entry is default */
  { "[@]",      spiral },
	// { "[\\]",     dwindle },
	{ "H[]",      deck },
	// { "TTT",      bstack },
	// { "===",      bstackhoriz },
	// { "HHH",      grid },
	// { "###",      nrowgrid },
	// { "---",      horizgrid },
	// { ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	// { ">M>",      centeredfloatingmaster },
	// { "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

	// { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, 
/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tagandview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define BARSHCMD(cmd, signal) SHCMD(cmd "&& pkill -RTMIN+" signal " dwmblocks")

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *applauncher[] = {"rofi", "-modi", "drun", "-show", "drun"};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,                       XK_b,      spawn,          SHCMD("chromium") },
  { MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("librewolf") },
  { MODKEY,                       XK_r,      spawn,          SHCMD("st -e ranger") },
  { MODKEY,                       XK_d,      spawn,          SHCMD("pcmanfm") },

  { Mod1Mask,                     XK_F1,     spawn,          {.v = applauncher } },
  { 0,                            XK_Print,  spawn,          SHCMD("maim -s ~/Pictures/Screenshots/$(date +%s).png") },
  { MODKEY,                       XK_Print,  spawn,          SHCMD("flameshot gui") },
  { MODKEY,                       XK_n,      spawn,          SHCMD("feh --bg-fill --randomize ~/Documents/wallpapers") },
  { MODKEY,                       XK_v,      spawn,          SHCMD("roficlip") },
  { MODKEY|ControlMask,           XK_x,      spawn,          SHCMD("xkill") },
  { Mod1Mask|ControlMask,         XK_Delete, spawn,          SHCMD("st -e htop") },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, BARSHCMD("pamixer --allow-boost -i 5", "10") },
	{ 0,                       XF86XK_AudioLowerVolume, spawn, BARSHCMD("pamixer --allow-boost -d 5", "10") },
	{ 0,                       XF86XK_AudioMute, spawn,        BARSHCMD("pamixer -t", "10") },
  // { Mod1Mask|ShiftMask,           0,         spawn,          SHCMD("pkill -RTMIN+30 dwmblocks") },
  { MODKEY|ShiftMask,             XK_equal,  spawn,          SHCMD("betterlockscreen -l dim") },

	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	// { MODKEY,                       XK_l,      focusstack,     {.i = +1 } },
	// { MODKEY,                       XK_h,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	// { MODKEY|ControlMask,           XK_l,      setmfact,       {.f = +0.05} },
	// { MODKEY|ControlMask,           XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY|ControlMask,           XK_k,      setcfact,       {.f = +0.25} },
	{ MODKEY|ControlMask,           XK_j,      setcfact,       {.f = -0.25} },
  { MODKEY|ControlMask,           XK_o,      setcfact,       {.f =  0.00} },
	// { MODKEY|ShiftMask,             XK_l,      pushup,         {0} },
 //  { MODKEY|ShiftMask,             XK_h,      pushdown,       {0} },
  { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
  { MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ControlMask,   	    	XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_s,      togglefloating, {0} },
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_e,      incnmaster,     {.i = -1 } },
	
	{ MODKEY,                 XK_bracketright, shiftview,      { .i = +1 } },
	{ MODKEY,                 XK_bracketleft,  shiftview,      { .i = -1 } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tagandview,     {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[3]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
