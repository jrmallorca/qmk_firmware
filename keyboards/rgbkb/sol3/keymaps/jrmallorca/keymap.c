#include QMK_KEYBOARD_H

#include "oneshot.h"

// Define layers
#define LA_DEF  DF(DEFAULT)
#define LA_SYM  MO(SYM)
#define LA_NAV  MO(NAV)
#define LA_MNAV MO(MOUSE_NAV)
#define LA_NUM  MO(NUM)
#define LA_GAME DF(GAME)
#define LA_KEEB MO(KEYBOARD)

// Define keys
#define O_LSFT OSM(MOD_LSFT)

#define S_LBRC S(KC_LBRC)
#define S_RBRC S(KC_RBRC)
#define S_LABK S(KC_COMM)
#define S_RABK S(KC_DOT)

#define K_QSTN S(KC_SLSH)
#define K_PIPE S(KC_NUBS)
#define K_USCR S(KC_MINS)
#define K_AT   S(KC_QUOT)
#define K_PLUS S(KC_EQL)
#define K_CLN  S(KC_SCLN)
#define K_TLDE S(KC_NUHS)

#define K_HOME G(KC_LEFT)
#define K_END  G(KC_RGHT)
#define K_TABL G(S(KC_LBRC))
#define K_TABR G(S(KC_RBRC))
#define K_SPCL A(G(KC_LEFT))
#define K_SPCR A(G(KC_RGHT))

enum sol_layers {
    DEFAULT,
    SYM,
    NAV,
    MOUSE_NAV,
    NUM,
    GAME,
    KEYBOARD,
};

enum sol_keycodes {
    // Disables touch processing
    TCH_TOG = SAFE_RANGE,
    MENU_BTN,
    MENU_UP,
    MENU_DN,
    RGB_RST,

    // Custom oneshot mod implementation with no timers.
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Default (COLEMAKDH)
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │Reset │  │Reset │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   Q  │   W  │   F  │   P  │   B  │Power │  │L_KEEB│   J  │   L  │   U  │   Y  │   '  │Delete│
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │Escape│   A  │   R  │   S  │   T  │   G  │ Wake │  │L_DEF │   M  │   N  │   E  │   I  │   O  │ BSPC │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │   Z  │   X  │   C  │   D  │   V  │Sleep │  │L_GAME│   K  │   H  │   ,  │   .  │   ?  │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │L_NAV │      │      │  │      │      │L_SYM │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┤Space ├──────┤  ├──────┤Enter ├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │OSHIFT│  │CAPWRD│      │
 *                                    └──────┴──────┘  └──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │                              │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┘                              └──────┴──────┴──────┴──────┴──────┘
 */

    [DEFAULT] = LAYOUT(
        _______, _______, _______, _______, _______, _______, QK_BOOT,                   QK_BOOT, _______, _______, _______, _______, _______, _______,
        KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   , KC_PWR ,                   LA_KEEB, KC_J   , KC_L   , KC_U   , KC_Y   , KC_QUOT, KC_DEL ,
        KC_ESC , KC_A   , KC_R   , KC_S   , KC_T   , KC_G   , KC_WAKE,                   LA_DEF , KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , KC_BSPC,
        _______, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   , KC_SLEP,                   LA_GAME, KC_K   , KC_H   , KC_COMM, KC_DOT , K_QSTN , _______,
        _______, _______, _______, _______, LA_NAV , KC_SPC , _______, O_LSFT , CAPSWRD, _______, KC_ENT , LA_SYM , _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/* SYM
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │   !  │   "  │   £  │   $  │   +  │      │  │      │   =  │   %  │   ^  │   &  │   *  │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │   /  │   :  │   _  │   -  │   ;  │   #  │      │  │      │   ~  │ CTRL │ SHFT │ ALT  │ CMD  │  \   │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │   @  │   <  │   [  │   (  │   {  │   |  │      │  │      │   `  │   }  │   )  │   ]  │   >  │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┤      ├──────┤  ├──────┤      ├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │      │  │      │      │
 *                                    └──────┴──────┘  └──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │                              │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┘                              └──────┴──────┴──────┴──────┴──────┘
 */

    [SYM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), K_PLUS , _______,                   _______, KC_EQL , S(KC_5), S(KC_6), S(KC_7), S(KC_8), _______,
        KC_SLSH, K_CLN  , K_USCR , KC_MINS, KC_SCLN, KC_NUHS, _______,                   _______, K_TLDE , OS_CTRL, OS_SHFT, OS_ALT , OS_CMD , KC_NUBS,
        K_AT   , S_LABK , KC_LBRC, S(KC_9), S_LBRC , K_PIPE , _______,                   _______, KC_GRV , S_RBRC , S(KC_0), KC_RBRC, S_RABK , _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                                                                                                                        
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/* NAV
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │  │      │      │ HOME │  UP  │ END  │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │ CMD  │ ALT  │ SHFT │ CTRL │      │      │  │      │      │ LEFT │ DOWN │RIGHT │ PGUP │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │L_MNAV│ TABL │ SPCL │ SPCR │ TABR │      │      │  │      │      │      │      │      │ PGDN │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┤      ├──────┤  ├──────┤      ├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │      │  │      │      │
 *                                    └──────┴──────┘  └──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │                              │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┘                              └──────┴──────┴──────┴──────┴──────┘
 */

    [NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, K_HOME , KC_UP  , K_END  , _______, _______,
        _______, OS_CMD , OS_ALT , OS_SHFT, OS_CTRL, _______, _______,                   _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, _______,
        LA_MNAV, K_TABL , K_SPCL , K_SPCR , K_TABR , _______, _______,                   _______, _______, _______, _______, _______, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                                                                                                                        
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/* MOUSE_NAV
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │  │      │      │MOUS_1│MOUS_U│MOUS_2│      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │ CMD  │ ALT  │ SHFT │ CTRL │      │      │  │      │      │MOUS_L│MOUS_D│MOUS_R│SCRL_U│      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │  │      │      │SCRL_L│      │SCRL_R│SCRL_D│      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┤      ├──────┤  ├──────┤      ├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │      │  │      │      │
 *                                    └──────┴──────┘  └──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │                              │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┘                              └──────┴──────┴──────┴──────┴──────┘
 */

    [MOUSE_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,
        _______, OS_CMD , OS_ALT , OS_SHFT, OS_CTRL, _______, _______,                   _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______,
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, KC_WH_L, _______, KC_WH_R, KC_WH_D, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                                                                                                                        
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/* NUM
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │  1   │  2   │  3   │  4   │  5   │      │  │      │  6   │  7   │  8   │  9   │  0   │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │ CMD  │ ALT  │ SHFT │ CTRL │ F11  │      │  │      │ F12  │ CTRL │ SHFT │ ALT  │ CMD  │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │  F1  │  F2  │  F3  │  F4  │  F5  │      │  │      │  F6  │  F7  │  F8  │  F9  │ F10  │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┤      ├──────┤  ├──────┤      ├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │      │  │      │      │
 *                                    └──────┴──────┘  └──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │                              │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┘                              └──────┴──────┴──────┴──────┴──────┘
 */

    [NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______,                   _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
        _______, OS_CMD , OS_ALT , OS_SHFT, OS_CTRL, KC_F11 , _______,                   _______, KC_F12 , OS_CTRL, OS_SHFT, OS_ALT , OS_CMD , _______,
        _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,                   _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                                                                                                                        
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/* Game (COLEMAKDH)
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   Q  │   W  │   F  │   P  │   B  │      │  │      │   J  │   L  │   U  │   Y  │   '  │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │   A  │   R  │   S  │   T  │   G  │      │  │      │   M  │   N  │   E  │   I  │   O  │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ SHFT │   Z  │   X  │   C  │   D  │   V  │      │  │      │   K  │   H  │   ,  │   .  │   /  │ SHFT │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ CTRL │ GUI  │ ALT  │      │      │      │      │  │      │      │      │      │ ALT  │ GUI  │ CTRL │
 * └──────┴──────┴──────┴──────┴──────┤      ├──────┤  ├──────┤      ├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │      │  │      │      │
 *                                    └──────┴──────┘  └──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │                              │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┘                              └──────┴──────┴──────┴──────┴──────┘
 */

    [GAME] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   , _______,                   _______, KC_J   , KC_L   , KC_U   , KC_Y   , KC_QUOT, _______,
        _______, KC_A   , KC_R   , KC_S   , KC_T   , KC_G   , _______,                   _______, KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , _______,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   , _______,                   _______, KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LALT, KC_RGUI, KC_RCTL,

        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/* Keyboard RGB settings
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │      │  │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │ SAT- │BRIGT+│ SAT+ │      │      │  │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │ HUE- │BRIGT-│ HUE- │      │      │  │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │EFFCT-│ RST  │EFFCT+│      │      │  │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │MODE- │TOGGLE│MODE+ │      │      │  │      │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┤      ├──────┤  ├──────┤      ├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │      │  │      │      │
 *                                    └──────┴──────┘  └──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                │      │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │                              │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┘                              └──────┴──────┴──────┴──────┴──────┘
 */

    [KEYBOARD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_SAD, RGB_VAI, RGB_SAI, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_HUD, RGB_VAD, RGB_HUI, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_SPD, RGB_RST, RGB_SPI, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_RMOD,RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                                                                                                                        
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode)
    {
        case MENU_BTN:
            if (record->event.pressed) {
                rgb_menu_selection();
            }
            return false;
        case MENU_UP:
            if (record->event.pressed) {
                rgb_menu_action(true);
            }
            return false;
        case MENU_DN:
            if (record->event.pressed) {
                rgb_menu_action(false);
            }
            return false;
        case RGB_RST:
            if (record->event.pressed) {
                eeconfig_update_rgb_matrix_default();
            }
            return false;
        case TCH_TOG:
            if (record->event.pressed) {
                touch_encoder_toggle();
            }
            return false;  // Skip all further processing of this key
        default:
            update_oneshot(
                &os_shft_state, KC_LSFT, OS_SHFT,
                keycode, record
            );
            update_oneshot(
                &os_ctrl_state, KC_LCTL, OS_CTRL,
                keycode, record
            );
            update_oneshot(
                &os_alt_state, KC_LALT, OS_ALT,
                keycode, record
            );
            update_oneshot(
                &os_cmd_state, KC_LCMD, OS_CMD,
                keycode, record
            );
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}

void render_layer_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case DEFAULT:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case SYM:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case NAV:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case MOUSE_NAV:
            oled_write_ln_P(PSTR("Mouse Navigation"), false);
            break;
        case NUM:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case GAME:
            oled_write_ln_P(PSTR("Game"), false);
            break;
        case KEYBOARD:
            oled_write_ln_P(PSTR("KEYBOARD"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}
