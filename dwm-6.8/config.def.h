//#define LAPTOP
#define BROWSER "firefox"
#ifdef LAPTOP
    #include <X11/XF86keysym.h>
#endif
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=16" };
static const char dmenufont[]       = "monospace:size=16";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ BROWSER,    NULL,       NULL,       0,            0,           -1 },
	{ "Telegram", NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	//{ Mod1Mask,                     XK_F4,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
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
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
/* my custom binds */
	{ MODKEY,                       XK_End,    spawn,          {.v = (const char*[]){ "wpctl", "set-mute", "@DEFAULT_SINK@", "toggle", NULL } } },
	{ MODKEY,                       XK_minus,  spawn,          {.v = (const char*[]){ "wpctl", "set-volume", "@DEFAULT_SINK@", "5%-", NULL } } },
	{ MODKEY,                       XK_equal,  spawn,          {.v = (const char*[]){ "wpctl", "set-volume", "@DEFAULT_SINK@", "5%+", NULL } } },
#ifndef LAPTOP
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = (const char *[]){ "xrandr", "--output", "HDMI-A-0", "--mode", "1920x1080", "--rate", "100", "--output", "DisplayPort-0", "--mode", "1440x900", "--rate", "74.98", "--left-of", "HDMI-A-0",  NULL } } },
	{ MODKEY,                       XK_p,      spawn,          {.v = (const char *[]){ "xrandr", "--output", "DisplayPort-0", "--off", "--output", "HDMI-A-0", "--mode", "1920x1080", "--rate", "100", NULL } } },
	{ ControlMask,                  XK_Pause,  spawn,          SHCMD("sleep 0.2 && systemctl suspend") },
#else
	{ 0,                            XF86XK_AudioMute,       spawn,          {.v = (const char*[]){ "wpctl", "set-mute", "@DEFAULT_SINK@", "toggle", NULL } } },
	{ 0,                            XF86XK_AudioLowerVolume,spawn,          {.v = (const char*[]){ "wpctl", "set-volume", "@DEFAULT_SINK@", "5%-", NULL } } },
	{ 0,                            XF86XK_AudioRaiseVolume,spawn,          {.v = (const char*[]){ "wpctl", "set-volume", "@DEFAULT_SINK@", "5%+", NULL } } },
#endif
	{ MODKEY,                       XK_Scroll_Lock, spawn,     SHCMD("beep; systemctl poweroff") },
	{ 0,                            XK_Print,  spawn,          SHCMD("maim | tee ~/Pictures/Screenshots/$(date '+%y%m%d-%H%M-%S').png | xclip -selection clipboard -target image/png") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("maim --select | tee ~/Pictures/Screenshots/$(date '+%y%m%d-%H%M-%S').png | xclip -selection clipboard -target image/png") },
	{ MODKEY,                       XK_Page_Down,spawn,        SHCMD("wpctl set-mute @DEFAULT_SOURCE@ 1 ; beep") },
	{ MODKEY,                       XK_Page_Up,spawn,          SHCMD("wpctl set-mute @DEFAULT_SOURCE@ 0") },
	//{ MODKEY,                       XK_Return, spawn,          SHCMD("") },
	{ MODKEY,                       XK_F1,     spawn,          {.v = (const char*[]){ BROWSER, "--new-window", NULL } } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = (const char *[]){ BROWSER, "--new-window", "https://dl.nure.ua/my/courses.php", "https://gemini.google.com/app", NULL } } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = (const char*[]){ "Telegram", NULL } } },
	{ MODKEY,                       XK_F4,     spawn,          {.v = (const char *[]){ BROWSER, "--new-tab", "https://cist.nure.ua/ias/app/tt/f?p=778:2:2502439617492007::NO:::#", NULL } } },
	{ MODKEY,                       XK_e,      spawn,          {.v = (const char*[]){ "Thunar", NULL } } },
	{ MODKEY,                       XK_Escape, spawn,          {.v = (const char*[]){ "setxkbmap", "-layout", "us,ru", "-option", "grp:caps_toggle",  NULL } } },
	{ MODKEY|ShiftMask,             XK_Escape, spawn,          {.v = (const char*[]){ "setxkbmap", "-layout", "us,ua", "-option", "grp:caps_toggle",  NULL } } },
/* end of custom binds */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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
