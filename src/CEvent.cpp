#include <CEvent.h>

std::string
CEvent::
keyTypeName(CKeyType type)
{
  switch (type) {
    case CKEY_TYPE_NUL:           return "NUL";
    case CKEY_TYPE_SOH:           return "SOH";
    case CKEY_TYPE_STX:           return "STX";
    case CKEY_TYPE_ETX:           return "ETX";
    case CKEY_TYPE_EOT:           return "EOT";
    case CKEY_TYPE_ENQ:           return "ENQ";
    case CKEY_TYPE_ACK:           return "ACK";
    case CKEY_TYPE_BEL:           return "BEL";
    case CKEY_TYPE_BackSpace:     return "BackSpace";
    case CKEY_TYPE_TAB:           return "Tab";
    case CKEY_TYPE_Tab:           return "Tab";
    case CKEY_TYPE_Backtab:       return "BackTab";
    case CKEY_TYPE_LineFeed:      return "LineFeed";
    case CKEY_TYPE_Clear:         return "Clear";
    case CKEY_TYPE_FF:            return "FF";
    case CKEY_TYPE_Return:        return "Return";
    case CKEY_TYPE_SO:            return "SO";
    case CKEY_TYPE_SI:            return "SI";
    case CKEY_TYPE_DLE:           return "DLE";
    case CKEY_TYPE_DC1:           return "DC1";
    case CKEY_TYPE_DC2:           return "DC2";
    case CKEY_TYPE_Pause:         return "Pause";
    case CKEY_TYPE_Scroll_Lock:   return "Scroll_Lock";
    case CKEY_TYPE_Sys_Req:       return "Sys_Req";
    case CKEY_TYPE_SYN:           return "SYN";
    case CKEY_TYPE_ETB:           return "ETB";
    case CKEY_TYPE_CAN:           return "CAN";
    case CKEY_TYPE_EM:            return "EM";
    case CKEY_TYPE_SUB:           return "SUB";
    case CKEY_TYPE_Escape:        return "Escape";
    case CKEY_TYPE_FS:            return "FS";
    case CKEY_TYPE_GS:            return "GS";
    case CKEY_TYPE_RS:            return "RS";
    case CKEY_TYPE_US:            return "US";

    case CKEY_TYPE_Space:         return "Space";
    case CKEY_TYPE_Exclam:        return "Exclam";
    case CKEY_TYPE_QuoteDbl:      return "QuoteDbl";
    case CKEY_TYPE_NumberSign:    return "NumberSign";
    case CKEY_TYPE_Dollar:        return "Dollar";
    case CKEY_TYPE_Percent:       return "Percent";
    case CKEY_TYPE_Ampersand:     return "Ampersand";
    case CKEY_TYPE_Apostrophe:    return "Apostrophe";
    case CKEY_TYPE_ParenLeft:     return "ParenLeft";
    case CKEY_TYPE_ParenRight:    return "ParenRight";
    case CKEY_TYPE_Asterisk:      return "Asterisk";
    case CKEY_TYPE_Plus:          return "Plus";
    case CKEY_TYPE_Comma:         return "Comma";
    case CKEY_TYPE_Minus:         return "Minus";
    case CKEY_TYPE_Period:        return "Period";
    case CKEY_TYPE_Slash:         return "Slash";
    case CKEY_TYPE_0:             return "0";
    case CKEY_TYPE_1:             return "1";
    case CKEY_TYPE_2:             return "2";
    case CKEY_TYPE_3:             return "3";
    case CKEY_TYPE_4:             return "4";
    case CKEY_TYPE_5:             return "5";
    case CKEY_TYPE_6:             return "6";
    case CKEY_TYPE_7:             return "7";
    case CKEY_TYPE_8:             return "8";
    case CKEY_TYPE_9:             return "9";
    case CKEY_TYPE_Colon:         return "Colon";
    case CKEY_TYPE_Semicolon:     return "Semicolon";
    case CKEY_TYPE_Less:          return "Less";
    case CKEY_TYPE_Equal:         return "Equal";
    case CKEY_TYPE_Greater:       return "Greater";
    case CKEY_TYPE_Question:      return "Question";
    case CKEY_TYPE_At:            return "At";
    case CKEY_TYPE_A:             return "A";
    case CKEY_TYPE_B:             return "B";
    case CKEY_TYPE_C:             return "C";
    case CKEY_TYPE_D:             return "D";
    case CKEY_TYPE_E:             return "E";
    case CKEY_TYPE_F:             return "F";
    case CKEY_TYPE_G:             return "G";
    case CKEY_TYPE_H:             return "H";
    case CKEY_TYPE_I:             return "I";
    case CKEY_TYPE_J:             return "J";
    case CKEY_TYPE_K:             return "K";
    case CKEY_TYPE_L:             return "L";
    case CKEY_TYPE_M:             return "M";
    case CKEY_TYPE_N:             return "N";
    case CKEY_TYPE_O:             return "O";
    case CKEY_TYPE_P:             return "P";
    case CKEY_TYPE_Q:             return "Q";
    case CKEY_TYPE_R:             return "R";
    case CKEY_TYPE_S:             return "S";
    case CKEY_TYPE_T:             return "T";
    case CKEY_TYPE_U:             return "U";
    case CKEY_TYPE_V:             return "V";
    case CKEY_TYPE_W:             return "W";
    case CKEY_TYPE_X:             return "X";
    case CKEY_TYPE_Y:             return "Y";
    case CKEY_TYPE_Z:             return "Z";
    case CKEY_TYPE_a:             return "a";
    case CKEY_TYPE_b:             return "b";
    case CKEY_TYPE_c:             return "c";
    case CKEY_TYPE_d:             return "d";
    case CKEY_TYPE_e:             return "e";
    case CKEY_TYPE_f:             return "f";
    case CKEY_TYPE_g:             return "g";
    case CKEY_TYPE_h:             return "h";
    case CKEY_TYPE_i:             return "i";
    case CKEY_TYPE_j:             return "j";
    case CKEY_TYPE_k:             return "k";
    case CKEY_TYPE_l:             return "l";
    case CKEY_TYPE_m:             return "m";
    case CKEY_TYPE_n:             return "n";
    case CKEY_TYPE_o:             return "o";
    case CKEY_TYPE_p:             return "p";
    case CKEY_TYPE_q:             return "q";
    case CKEY_TYPE_r:             return "r";
    case CKEY_TYPE_s:             return "s";
    case CKEY_TYPE_t:             return "t";
    case CKEY_TYPE_u:             return "u";
    case CKEY_TYPE_v:             return "v";
    case CKEY_TYPE_w:             return "w";
    case CKEY_TYPE_x:             return "x";
    case CKEY_TYPE_y:             return "y";
    case CKEY_TYPE_z:             return "z";
    case CKEY_TYPE_BracketLeft:   return "BracketLeft";
    case CKEY_TYPE_Backslash:     return "Backslash";
    case CKEY_TYPE_BracketRight:  return "BracketRight";
    case CKEY_TYPE_AsciiCircum:   return "AsciiCircum";
    case CKEY_TYPE_Underscore:    return "Underscore";
    case CKEY_TYPE_QuoteLeft:     return "QuoteLeft";
    case CKEY_TYPE_BraceLeft:     return "BraceLeft";
    case CKEY_TYPE_Bar:           return "Bar";
    case CKEY_TYPE_BraceRight:    return "BraceRight";
    case CKEY_TYPE_AsciiTilde:    return "AsciiTilde";
    case CKEY_TYPE_DEL:           return "DEL";

    case CKEY_TYPE_nobreakspace:  return "nobreakspace";
    case CKEY_TYPE_exclamdown:    return "exclamdown";
    case CKEY_TYPE_cent:          return "cent";
    case CKEY_TYPE_sterling:      return "sterling";
    case CKEY_TYPE_currency:      return "currency";
    case CKEY_TYPE_yen:           return "yen";
    case CKEY_TYPE_brokenbar:     return "brokenbar";
    case CKEY_TYPE_section:       return "section";
    case CKEY_TYPE_diaeresis:     return "diaeresis";
    case CKEY_TYPE_copyright:     return "copyright";
    case CKEY_TYPE_ordfeminine:   return "ordfeminine";
    case CKEY_TYPE_guillemotleft: return "guillemotleft";
    case CKEY_TYPE_notsign:       return "notsign";
    case CKEY_TYPE_hyphen:        return "hyphen";
    case CKEY_TYPE_registered:    return "registered";
    case CKEY_TYPE_macron:        return "macron";
    case CKEY_TYPE_degree:        return "degree";
    case CKEY_TYPE_plusminus:     return "plusminus";
    case CKEY_TYPE_twosuperior:   return "twosuperior";
    case CKEY_TYPE_threesuperior: return "threesuperior";
    case CKEY_TYPE_acute:         return "acute";
    case CKEY_TYPE_mu:            return "mu";
    case CKEY_TYPE_paragraph:     return "paragraph";
    case CKEY_TYPE_periodcentered:return "periodcentered";
    case CKEY_TYPE_cedilla:       return "cedilla";
    case CKEY_TYPE_onesuperior:   return "onesuperior";
    case CKEY_TYPE_masculine:     return "masculine";
    case CKEY_TYPE_guillemotright:return "guillemotright";
    case CKEY_TYPE_onequarter:    return "onequarter";
    case CKEY_TYPE_onehalf:       return "onehalf";
    case CKEY_TYPE_threequarters: return "threequarters";
    case CKEY_TYPE_questiondown:  return "questiondown";
    case CKEY_TYPE_Agrave:        return "Agrave";
    case CKEY_TYPE_Aacute:        return "Aacute";
    case CKEY_TYPE_Acircumflex:   return "Acircumflex";
    case CKEY_TYPE_Atilde:        return "Atilde";
    case CKEY_TYPE_Adiaeresis:    return "Adiaeresis";
    case CKEY_TYPE_Aring:         return "Aring";
    case CKEY_TYPE_AE:            return "AE";
    case CKEY_TYPE_Ccedilla:      return "Ccedilla";
    case CKEY_TYPE_Egrave:        return "Egrave";
    case CKEY_TYPE_Eacute:        return "Eacute";
    case CKEY_TYPE_Ecircumflex:   return "Ecircumflex";
    case CKEY_TYPE_Ediaeresis:    return "Ediaeresis";
    case CKEY_TYPE_Igrave:        return "Igrave";
    case CKEY_TYPE_Iacute:        return "Iacute";
    case CKEY_TYPE_Icircumflex:   return "Icircumflex";
    case CKEY_TYPE_Idiaeresis:    return "Idiaeresis";
    case CKEY_TYPE_ETH:           return "ETH";
    case CKEY_TYPE_Ntilde:        return "Ntilde";
    case CKEY_TYPE_Ograve:        return "Ograve";
    case CKEY_TYPE_Oacute:        return "Oacute";
    case CKEY_TYPE_Ocircumflex:   return "Ocircumflex";
    case CKEY_TYPE_Otilde:        return "Otilde";
    case CKEY_TYPE_Odiaeresis:    return "Odiaeresis";
    case CKEY_TYPE_multiply:      return "multiply";
    case CKEY_TYPE_Ooblique:      return "Ooblique";
    case CKEY_TYPE_Ugrave:        return "Ugrave";
    case CKEY_TYPE_Uacute:        return "Uacute";
    case CKEY_TYPE_Ucircumflex:   return "Ucircumflex";
    case CKEY_TYPE_Udiaeresis:    return "Udiaeresis";
    case CKEY_TYPE_Yacute:        return "Yacute";
    case CKEY_TYPE_THORN:         return "THORN";
    case CKEY_TYPE_ssharp:        return "ssharp";
    case CKEY_TYPE_division:      return "division";
    case CKEY_TYPE_ydiaeresis:    return "ydiaeresis";

    case CKEY_TYPE_Home:          return "Home";
    case CKEY_TYPE_Left:          return "Left";
    case CKEY_TYPE_Up:            return "Up";
    case CKEY_TYPE_Right:         return "Right";
    case CKEY_TYPE_Down:          return "Down";
    case CKEY_TYPE_Page_Up:       return "Page_Up";
    case CKEY_TYPE_Page_Down:     return "Page_Down";
    case CKEY_TYPE_End:           return "End";
    case CKEY_TYPE_Begin:         return "Begin";

    case CKEY_TYPE_Select:        return "Select";
    case CKEY_TYPE_Print:         return "Print";
    case CKEY_TYPE_Execute:       return "Execute";
    case CKEY_TYPE_Insert:        return "Insert";
    case CKEY_TYPE_Undo:          return "Undo";
    case CKEY_TYPE_Redo:          return "Redo";
    case CKEY_TYPE_Menu:          return "Menu";
    case CKEY_TYPE_Find:          return "Find";
    case CKEY_TYPE_Cancel:        return "Cancel";
    case CKEY_TYPE_Help:          return "Help";
    case CKEY_TYPE_Break:         return "Break";
    case CKEY_TYPE_Mode_switch:   return "Mode_switch";
    case CKEY_TYPE_Num_Lock:      return "Num_Lock";

    case CKEY_TYPE_KP_Space:      return "KP_Space";
    case CKEY_TYPE_KP_Tab:        return "KP_Tab";
    case CKEY_TYPE_KP_Enter:      return "KP_Enter";
    case CKEY_TYPE_KP_F1:         return "KP_F1";
    case CKEY_TYPE_KP_F2:         return "KP_F2";
    case CKEY_TYPE_KP_F3:         return "KP_F3";
    case CKEY_TYPE_KP_F4:         return "KP_F4";
    case CKEY_TYPE_KP_Home:       return "KP_Home";
    case CKEY_TYPE_KP_Left:       return "KP_Left";
    case CKEY_TYPE_KP_Up:         return "KP_Up";
    case CKEY_TYPE_KP_Right:      return "KP_Right";
    case CKEY_TYPE_KP_Down:       return "KP_Down";
    case CKEY_TYPE_KP_Page_Up:    return "KP_Page_Up";
    case CKEY_TYPE_KP_Page_Down:  return "KP_Page_Down";
    case CKEY_TYPE_KP_End:        return "KP_End";
    case CKEY_TYPE_KP_Begin:      return "KP_Begin";
    case CKEY_TYPE_KP_Insert:     return "KP_Insert";
    case CKEY_TYPE_KP_Delete:     return "KP_Delete";
    case CKEY_TYPE_KP_Equal:      return "KP_Equal";
    case CKEY_TYPE_KP_Multiply:   return "KP_Multiply";
    case CKEY_TYPE_KP_Add:        return "KP_Add";
    case CKEY_TYPE_KP_Separator:  return "KP_Separator";
    case CKEY_TYPE_KP_Subtract:   return "KP_Subtract";
    case CKEY_TYPE_KP_Decimal:    return "KP_Decimal";
    case CKEY_TYPE_KP_Divide:     return "KP_Divide";

    case CKEY_TYPE_F1:            return "F1";
    case CKEY_TYPE_F2:            return "F2";
    case CKEY_TYPE_F3:            return "F3";
    case CKEY_TYPE_F4:            return "F4";
    case CKEY_TYPE_F5:            return "F5";
    case CKEY_TYPE_F6:            return "F6";
    case CKEY_TYPE_F7:            return "F7";
    case CKEY_TYPE_F8:            return "F8";
    case CKEY_TYPE_F9:            return "F9";
    case CKEY_TYPE_F10:           return "F10";
    case CKEY_TYPE_F11:           return "F11";
    case CKEY_TYPE_F12:           return "F12";
    case CKEY_TYPE_F13:           return "F13";
    case CKEY_TYPE_F14:           return "F14";
    case CKEY_TYPE_F15:           return "F15";
    case CKEY_TYPE_F16:           return "F16";
    case CKEY_TYPE_F17:           return "F17";
    case CKEY_TYPE_F18:           return "F18";
    case CKEY_TYPE_F19:           return "F19";
    case CKEY_TYPE_F20:           return "F20";
    case CKEY_TYPE_F21:           return "F21";
    case CKEY_TYPE_F22:           return "F22";
    case CKEY_TYPE_F23:           return "F23";
    case CKEY_TYPE_F24:           return "F24";
    case CKEY_TYPE_F25:           return "F25";
    case CKEY_TYPE_F26:           return "F26";
    case CKEY_TYPE_F27:           return "F27";
    case CKEY_TYPE_F28:           return "F28";
    case CKEY_TYPE_F29:           return "F29";
    case CKEY_TYPE_F30:           return "F30";
    case CKEY_TYPE_F31:           return "F31";
    case CKEY_TYPE_F32:           return "F32";
    case CKEY_TYPE_F33:           return "F33";
    case CKEY_TYPE_F34:           return "F34";
    case CKEY_TYPE_F35:           return "F35";

    case CKEY_TYPE_Shift_L:       return "Shift_L";
    case CKEY_TYPE_Shift_R:       return "Shift_R";
    case CKEY_TYPE_Control_L:     return "Control_L";
    case CKEY_TYPE_Control_R:     return "Control_R";
    case CKEY_TYPE_Caps_Lock:     return "Caps_Lock";
    case CKEY_TYPE_Shift_Lock:    return "Shift_Lock";
    case CKEY_TYPE_Meta_L:        return "Meta_L";
    case CKEY_TYPE_Meta_R:        return "Meta_R";
    case CKEY_TYPE_Alt_L:         return "Alt_L";
    case CKEY_TYPE_Alt_R:         return "Alt_R";
    case CKEY_TYPE_Super_L:       return "Super_L";
    case CKEY_TYPE_Super_R:       return "Super_R";
    case CKEY_TYPE_Hyper_L:       return "Hyper_L";
    case CKEY_TYPE_Hyper_R:       return "Hyper_R";
  }

  return "??";
}

char
CEvent::
keyTypeChar(CKeyType type)
{
  switch (type) {
    case CKEY_TYPE_NUL:           return '\0';
    case CKEY_TYPE_SOH:           return '\0';
    case CKEY_TYPE_STX:           return '\0';
    case CKEY_TYPE_ETX:           return '\0';
    case CKEY_TYPE_EOT:           return '\0';
    case CKEY_TYPE_ENQ:           return '\0';
    case CKEY_TYPE_ACK:           return '\0';
    case CKEY_TYPE_BEL:           return '\a';
    case CKEY_TYPE_BackSpace:     return '\b';
    case CKEY_TYPE_TAB:           return '\t';
    case CKEY_TYPE_Tab:           return '\t';
    case CKEY_TYPE_Backtab:       return '\0';
    case CKEY_TYPE_LineFeed:      return '\n';
    case CKEY_TYPE_Clear:         return '\v';
    case CKEY_TYPE_FF:            return '\n';
    case CKEY_TYPE_Return:        return '\n';
    case CKEY_TYPE_SO:            return '\0';
    case CKEY_TYPE_SI:            return '\0';
    case CKEY_TYPE_DLE:           return '\0';
    case CKEY_TYPE_DC1:           return '\0';
    case CKEY_TYPE_DC2:           return '\0';
    case CKEY_TYPE_Pause:         return '\0';
    case CKEY_TYPE_Scroll_Lock:   return '\0';
    case CKEY_TYPE_Sys_Req:       return '\0';
    case CKEY_TYPE_SYN:           return '\0';
    case CKEY_TYPE_ETB:           return '\0';
    case CKEY_TYPE_CAN:           return '\0';
    case CKEY_TYPE_EM:            return '\0';
    case CKEY_TYPE_SUB:           return '\0';
    case CKEY_TYPE_Escape:        return '';
    case CKEY_TYPE_FS:            return '\0';
    case CKEY_TYPE_GS:            return '\0';
    case CKEY_TYPE_RS:            return '\0';
    case CKEY_TYPE_US:            return '\0';

    case CKEY_TYPE_Space:         return ' ';
    case CKEY_TYPE_Exclam:        return '!';
    case CKEY_TYPE_QuoteDbl:      return '\"';
    case CKEY_TYPE_NumberSign:    return '#';
    case CKEY_TYPE_Dollar:        return '$';
    case CKEY_TYPE_Percent:       return '%';
    case CKEY_TYPE_Ampersand:     return '&';
    case CKEY_TYPE_Apostrophe:    return '\'';
    case CKEY_TYPE_ParenLeft:     return '(';
    case CKEY_TYPE_ParenRight:    return ')';
    case CKEY_TYPE_Asterisk:      return '*';
    case CKEY_TYPE_Plus:          return '+';
    case CKEY_TYPE_Comma:         return ',';
    case CKEY_TYPE_Minus:         return '-';
    case CKEY_TYPE_Period:        return '.';
    case CKEY_TYPE_Slash:         return '/';
    case CKEY_TYPE_0:             return '0';
    case CKEY_TYPE_1:             return '1';
    case CKEY_TYPE_2:             return '2';
    case CKEY_TYPE_3:             return '3';
    case CKEY_TYPE_4:             return '4';
    case CKEY_TYPE_5:             return '5';
    case CKEY_TYPE_6:             return '6';
    case CKEY_TYPE_7:             return '7';
    case CKEY_TYPE_8:             return '8';
    case CKEY_TYPE_9:             return '9';
    case CKEY_TYPE_Colon:         return ':';
    case CKEY_TYPE_Semicolon:     return ';';
    case CKEY_TYPE_Less:          return '<';
    case CKEY_TYPE_Equal:         return '=';
    case CKEY_TYPE_Greater:       return '>';
    case CKEY_TYPE_Question:      return '?';
    case CKEY_TYPE_At:            return '@';
    case CKEY_TYPE_A:             return 'A';
    case CKEY_TYPE_B:             return 'B';
    case CKEY_TYPE_C:             return 'C';
    case CKEY_TYPE_D:             return 'D';
    case CKEY_TYPE_E:             return 'E';
    case CKEY_TYPE_F:             return 'F';
    case CKEY_TYPE_G:             return 'G';
    case CKEY_TYPE_H:             return 'H';
    case CKEY_TYPE_I:             return 'I';
    case CKEY_TYPE_J:             return 'J';
    case CKEY_TYPE_K:             return 'K';
    case CKEY_TYPE_L:             return 'L';
    case CKEY_TYPE_M:             return 'M';
    case CKEY_TYPE_N:             return 'N';
    case CKEY_TYPE_O:             return 'O';
    case CKEY_TYPE_P:             return 'P';
    case CKEY_TYPE_Q:             return 'Q';
    case CKEY_TYPE_R:             return 'R';
    case CKEY_TYPE_S:             return 'S';
    case CKEY_TYPE_T:             return 'T';
    case CKEY_TYPE_U:             return 'U';
    case CKEY_TYPE_V:             return 'V';
    case CKEY_TYPE_W:             return 'W';
    case CKEY_TYPE_X:             return 'X';
    case CKEY_TYPE_Y:             return 'Y';
    case CKEY_TYPE_Z:             return 'Z';
    case CKEY_TYPE_a:             return 'a';
    case CKEY_TYPE_b:             return 'b';
    case CKEY_TYPE_c:             return 'c';
    case CKEY_TYPE_d:             return 'd';
    case CKEY_TYPE_e:             return 'e';
    case CKEY_TYPE_f:             return 'f';
    case CKEY_TYPE_g:             return 'g';
    case CKEY_TYPE_h:             return 'h';
    case CKEY_TYPE_i:             return 'i';
    case CKEY_TYPE_j:             return 'j';
    case CKEY_TYPE_k:             return 'k';
    case CKEY_TYPE_l:             return 'l';
    case CKEY_TYPE_m:             return 'm';
    case CKEY_TYPE_n:             return 'n';
    case CKEY_TYPE_o:             return 'o';
    case CKEY_TYPE_p:             return 'p';
    case CKEY_TYPE_q:             return 'q';
    case CKEY_TYPE_r:             return 'r';
    case CKEY_TYPE_s:             return 's';
    case CKEY_TYPE_t:             return 't';
    case CKEY_TYPE_u:             return 'u';
    case CKEY_TYPE_v:             return 'v';
    case CKEY_TYPE_w:             return 'w';
    case CKEY_TYPE_x:             return 'x';
    case CKEY_TYPE_y:             return 'y';
    case CKEY_TYPE_z:             return 'z';
    case CKEY_TYPE_BracketLeft:   return '[';
    case CKEY_TYPE_Backslash:     return '\\';
    case CKEY_TYPE_BracketRight:  return ']';
    case CKEY_TYPE_AsciiCircum:   return '^';
    case CKEY_TYPE_Underscore:    return '_';
    case CKEY_TYPE_QuoteLeft:     return '`';
    case CKEY_TYPE_BraceLeft:     return '{';
    case CKEY_TYPE_Bar:           return '|';
    case CKEY_TYPE_BraceRight:    return '}';
    case CKEY_TYPE_AsciiTilde:    return '~';
    case CKEY_TYPE_DEL:           return '\b';

    case CKEY_TYPE_KP_Space:      return ' ';
    case CKEY_TYPE_KP_Tab:        return '\t';
    case CKEY_TYPE_KP_Enter:      return '\n';
    case CKEY_TYPE_KP_F1:         return '\0';
    case CKEY_TYPE_KP_F2:         return '\0';
    case CKEY_TYPE_KP_F3:         return '\0';
    case CKEY_TYPE_KP_F4:         return '\0';
    case CKEY_TYPE_KP_Home:       return '\0';
    case CKEY_TYPE_KP_Left:       return '\0';
    case CKEY_TYPE_KP_Up:         return '\0';
    case CKEY_TYPE_KP_Right:      return '\0';
    case CKEY_TYPE_KP_Down:       return '\0';
    case CKEY_TYPE_KP_Page_Up:    return '\0';
    case CKEY_TYPE_KP_Page_Down:  return '\0';
    case CKEY_TYPE_KP_End:        return '\0';
    case CKEY_TYPE_KP_Begin:      return '\0';
    case CKEY_TYPE_KP_Insert:     return '\0';
    case CKEY_TYPE_KP_Delete:     return '\0';
    case CKEY_TYPE_KP_Equal:      return '=';
    case CKEY_TYPE_KP_Multiply:   return '*';
    case CKEY_TYPE_KP_Add:        return '+';
    case CKEY_TYPE_KP_Separator:  return '\0';
    case CKEY_TYPE_KP_Subtract:   return '-';
    case CKEY_TYPE_KP_Decimal:    return '\0';
    case CKEY_TYPE_KP_Divide:     return '/';

    case CKEY_TYPE_F1:            return '\0';
    case CKEY_TYPE_F2:            return '\0';
    case CKEY_TYPE_F3:            return '\0';
    case CKEY_TYPE_F4:            return '\0';
    case CKEY_TYPE_F5:            return '\0';
    case CKEY_TYPE_F6:            return '\0';
    case CKEY_TYPE_F7:            return '\0';
    case CKEY_TYPE_F8:            return '\0';
    case CKEY_TYPE_F9:            return '\0';
    case CKEY_TYPE_F10:           return '\0';
    case CKEY_TYPE_F11:           return '\0';
    case CKEY_TYPE_F12:           return '\0';
    case CKEY_TYPE_F13:           return '\0';
    case CKEY_TYPE_F14:           return '\0';
    case CKEY_TYPE_F15:           return '\0';
    case CKEY_TYPE_F16:           return '\0';
    case CKEY_TYPE_F17:           return '\0';
    case CKEY_TYPE_F18:           return '\0';
    case CKEY_TYPE_F19:           return '\0';
    case CKEY_TYPE_F20:           return '\0';
    case CKEY_TYPE_F21:           return '\0';
    case CKEY_TYPE_F22:           return '\0';
    case CKEY_TYPE_F23:           return '\0';
    case CKEY_TYPE_F24:           return '\0';
    case CKEY_TYPE_F25:           return '\0';
    case CKEY_TYPE_F26:           return '\0';
    case CKEY_TYPE_F27:           return '\0';
    case CKEY_TYPE_F28:           return '\0';
    case CKEY_TYPE_F29:           return '\0';
    case CKEY_TYPE_F30:           return '\0';
    case CKEY_TYPE_F31:           return '\0';
    case CKEY_TYPE_F32:           return '\0';
    case CKEY_TYPE_F33:           return '\0';
    case CKEY_TYPE_F34:           return '\0';
    case CKEY_TYPE_F35:           return '\0';

    case CKEY_TYPE_Shift_L:       return '\0';
    case CKEY_TYPE_Shift_R:       return '\0';
    case CKEY_TYPE_Control_L:     return '\0';
    case CKEY_TYPE_Control_R:     return '\0';
    case CKEY_TYPE_Caps_Lock:     return '\0';
    case CKEY_TYPE_Shift_Lock:    return '\0';
    case CKEY_TYPE_Meta_L:        return '\0';
    case CKEY_TYPE_Meta_R:        return '\0';
    case CKEY_TYPE_Alt_L:         return '\0';
    case CKEY_TYPE_Alt_R:         return '\0';
    case CKEY_TYPE_Super_L:       return '\0';
    case CKEY_TYPE_Super_R:       return '\0';
    case CKEY_TYPE_Hyper_L:       return '\0';
    case CKEY_TYPE_Hyper_R:       return '\0';

    default:                      return '\0';
  }

  return '\0';
}

CKeyType
CEvent::
charKeyType(char c)
{
  switch (c) {
    case '\0': return CKEY_TYPE_NUL;
    case '\a': return CKEY_TYPE_BEL;
    case '\b': return CKEY_TYPE_BackSpace;
    case '\n': return CKEY_TYPE_Return;
    case '\t': return CKEY_TYPE_Tab;
    case '\v': return CKEY_TYPE_Clear;
    case '': return CKEY_TYPE_Escape;

    case '0' : return CKEY_TYPE_0;
    case '1' : return CKEY_TYPE_1;
    case '2' : return CKEY_TYPE_2;
    case '3' : return CKEY_TYPE_3;
    case '4' : return CKEY_TYPE_4;
    case '5' : return CKEY_TYPE_5;
    case '6' : return CKEY_TYPE_6;
    case '7' : return CKEY_TYPE_7;
    case '8' : return CKEY_TYPE_8;
    case '9' : return CKEY_TYPE_9;

    case 'a' : return CKEY_TYPE_a;
    case 'b' : return CKEY_TYPE_b;
    case 'c' : return CKEY_TYPE_c;
    case 'd' : return CKEY_TYPE_d;
    case 'e' : return CKEY_TYPE_e;
    case 'f' : return CKEY_TYPE_f;
    case 'g' : return CKEY_TYPE_g;
    case 'h' : return CKEY_TYPE_h;
    case 'i' : return CKEY_TYPE_i;
    case 'j' : return CKEY_TYPE_j;
    case 'k' : return CKEY_TYPE_k;
    case 'l' : return CKEY_TYPE_l;
    case 'm' : return CKEY_TYPE_m;
    case 'n' : return CKEY_TYPE_n;
    case 'o' : return CKEY_TYPE_o;
    case 'p' : return CKEY_TYPE_p;
    case 'q' : return CKEY_TYPE_q;
    case 'r' : return CKEY_TYPE_r;
    case 's' : return CKEY_TYPE_s;
    case 't' : return CKEY_TYPE_t;
    case 'u' : return CKEY_TYPE_u;
    case 'v' : return CKEY_TYPE_v;
    case 'w' : return CKEY_TYPE_w;
    case 'x' : return CKEY_TYPE_x;
    case 'y' : return CKEY_TYPE_y;
    case 'z' : return CKEY_TYPE_z;

    case 'A' : return CKEY_TYPE_A;
    case 'B' : return CKEY_TYPE_B;
    case 'C' : return CKEY_TYPE_C;
    case 'D' : return CKEY_TYPE_D;
    case 'E' : return CKEY_TYPE_E;
    case 'F' : return CKEY_TYPE_F;
    case 'G' : return CKEY_TYPE_G;
    case 'H' : return CKEY_TYPE_H;
    case 'I' : return CKEY_TYPE_I;
    case 'J' : return CKEY_TYPE_J;
    case 'K' : return CKEY_TYPE_K;
    case 'L' : return CKEY_TYPE_L;
    case 'M' : return CKEY_TYPE_M;
    case 'N' : return CKEY_TYPE_N;
    case 'O' : return CKEY_TYPE_O;
    case 'P' : return CKEY_TYPE_P;
    case 'Q' : return CKEY_TYPE_Q;
    case 'R' : return CKEY_TYPE_R;
    case 'S' : return CKEY_TYPE_S;
    case 'T' : return CKEY_TYPE_T;
    case 'U' : return CKEY_TYPE_U;
    case 'V' : return CKEY_TYPE_V;
    case 'W' : return CKEY_TYPE_W;
    case 'X' : return CKEY_TYPE_X;
    case 'Y' : return CKEY_TYPE_Y;
    case 'Z' : return CKEY_TYPE_Z;

    case '(' : return CKEY_TYPE_ParenLeft;
    case ')' : return CKEY_TYPE_ParenRight;
    case '[' : return CKEY_TYPE_BracketLeft;
    case ']' : return CKEY_TYPE_BracketRight;
    case '{' : return CKEY_TYPE_BraceLeft;
    case '}' : return CKEY_TYPE_BraceRight;
    case ',' : return CKEY_TYPE_Comma;
    case '.' : return CKEY_TYPE_Period;
    case ';' : return CKEY_TYPE_Semicolon;
    case ':' : return CKEY_TYPE_Colon;
    case '?' : return CKEY_TYPE_Question;
    case '!' : return CKEY_TYPE_Exclam;
    case '>' : return CKEY_TYPE_Greater;
    case '<' : return CKEY_TYPE_Less;
    case '+' : return CKEY_TYPE_Plus;
    case '-' : return CKEY_TYPE_Minus;
    case '*' : return CKEY_TYPE_Asterisk;
    case '/' : return CKEY_TYPE_Slash;
    case '%' : return CKEY_TYPE_Percent;
    case '&' : return CKEY_TYPE_Ampersand;
    case '|' : return CKEY_TYPE_Bar;
    case '^' : return CKEY_TYPE_AsciiCircum;
    case '~' : return CKEY_TYPE_AsciiTilde;
    case '=' : return CKEY_TYPE_Equal;
    case '#' : return CKEY_TYPE_NumberSign;
    case '$' : return CKEY_TYPE_Dollar;
    case '@' : return CKEY_TYPE_At;
    case '\\': return CKEY_TYPE_Backslash;
    case '\'': return CKEY_TYPE_Apostrophe;
    case '\"': return CKEY_TYPE_QuoteDbl;
    case '`' : return CKEY_TYPE_QuoteLeft;
    case ' ' : return CKEY_TYPE_Space;
    case '_' : return CKEY_TYPE_Underscore;

    default:  return CKEY_TYPE_NUL;
  }

  return CKEY_TYPE_NUL;
}

bool
CEvent::
keyTypeIsAlpha(CKeyType type)
{
  switch (type) {
    case CKEY_TYPE_A: case CKEY_TYPE_B: case CKEY_TYPE_C: case CKEY_TYPE_D:
    case CKEY_TYPE_E: case CKEY_TYPE_F: case CKEY_TYPE_G: case CKEY_TYPE_H:
    case CKEY_TYPE_I: case CKEY_TYPE_J: case CKEY_TYPE_K: case CKEY_TYPE_L:
    case CKEY_TYPE_M: case CKEY_TYPE_N: case CKEY_TYPE_O: case CKEY_TYPE_P:
    case CKEY_TYPE_Q: case CKEY_TYPE_R: case CKEY_TYPE_S: case CKEY_TYPE_T:
    case CKEY_TYPE_U: case CKEY_TYPE_V: case CKEY_TYPE_W: case CKEY_TYPE_X:
    case CKEY_TYPE_Y: case CKEY_TYPE_Z:

    case CKEY_TYPE_a: case CKEY_TYPE_b: case CKEY_TYPE_c: case CKEY_TYPE_d:
    case CKEY_TYPE_e: case CKEY_TYPE_f: case CKEY_TYPE_g: case CKEY_TYPE_h:
    case CKEY_TYPE_i: case CKEY_TYPE_j: case CKEY_TYPE_k: case CKEY_TYPE_l:
    case CKEY_TYPE_m: case CKEY_TYPE_n: case CKEY_TYPE_o: case CKEY_TYPE_p:
    case CKEY_TYPE_q: case CKEY_TYPE_r: case CKEY_TYPE_s: case CKEY_TYPE_t:
    case CKEY_TYPE_u: case CKEY_TYPE_v: case CKEY_TYPE_w: case CKEY_TYPE_x:
    case CKEY_TYPE_y: case CKEY_TYPE_z:
      return true;

    default:
      return false;
  }
}

CKeyType
CEvent::
keyTypeToUpper(CKeyType type)
{
  switch (type) {
    case CKEY_TYPE_a: case CKEY_TYPE_b: case CKEY_TYPE_c: case CKEY_TYPE_d:
    case CKEY_TYPE_e: case CKEY_TYPE_f: case CKEY_TYPE_g: case CKEY_TYPE_h:
    case CKEY_TYPE_i: case CKEY_TYPE_j: case CKEY_TYPE_k: case CKEY_TYPE_l:
    case CKEY_TYPE_m: case CKEY_TYPE_n: case CKEY_TYPE_o: case CKEY_TYPE_p:
    case CKEY_TYPE_q: case CKEY_TYPE_r: case CKEY_TYPE_s: case CKEY_TYPE_t:
    case CKEY_TYPE_u: case CKEY_TYPE_v: case CKEY_TYPE_w: case CKEY_TYPE_x:
    case CKEY_TYPE_y: case CKEY_TYPE_z:
      return (CKeyType)(int(type) + 32);
    default:
      return type;
  }
}

CKeyType
CEvent::
keyTypeToLower(CKeyType type)
{
  switch (type) {
    case CKEY_TYPE_A: case CKEY_TYPE_B: case CKEY_TYPE_C: case CKEY_TYPE_D:
    case CKEY_TYPE_E: case CKEY_TYPE_F: case CKEY_TYPE_G: case CKEY_TYPE_H:
    case CKEY_TYPE_I: case CKEY_TYPE_J: case CKEY_TYPE_K: case CKEY_TYPE_L:
    case CKEY_TYPE_M: case CKEY_TYPE_N: case CKEY_TYPE_O: case CKEY_TYPE_P:
    case CKEY_TYPE_Q: case CKEY_TYPE_R: case CKEY_TYPE_S: case CKEY_TYPE_T:
    case CKEY_TYPE_U: case CKEY_TYPE_V: case CKEY_TYPE_W: case CKEY_TYPE_X:
    case CKEY_TYPE_Y: case CKEY_TYPE_Z:
      return (CKeyType)(int(type) - 32);
    default:
      return type;
  }
}

bool
CEvent::
keyTypeIsDigit(CKeyType type)
{
  switch (type) {
    case CKEY_TYPE_0: case CKEY_TYPE_1: case CKEY_TYPE_2: case CKEY_TYPE_3:
    case CKEY_TYPE_4: case CKEY_TYPE_5: case CKEY_TYPE_6: case CKEY_TYPE_7:
    case CKEY_TYPE_8: case CKEY_TYPE_9:
     return true;

    default:
      return false;
  }
}

const std::string &
CKeyEvent::
getEscapeText() const
{
  return getEscapeTextCSI();
}

const std::string &
CKeyEvent::
getEscapeText(CKeyType type)
{
  return getEscapeTextCSI(type);
}

const std::string &
CKeyEvent::
getEscapeTextCSI() const
{
  if (! text_.empty())
    return text_;

  return getEscapeTextCSI(type_);
}

const std::string &
CKeyEvent::
getEscapeTextCSI(CKeyType type)
{
  static std::string str;

  switch (type) {
    case CKEY_TYPE_Up:        str = "[A";   break;
    case CKEY_TYPE_Down:      str = "[B";   break;
    case CKEY_TYPE_Right:     str = "[C";   break;
    case CKEY_TYPE_Left:      str = "[D";   break;
    case CKEY_TYPE_Home:      str = "[H";   break;
    case CKEY_TYPE_End:       str = "[F";   break;
    case CKEY_TYPE_Page_Up:   str = "[5~";  break;
    case CKEY_TYPE_Page_Down: str = "[6~";  break;
    case CKEY_TYPE_Insert:    str = "[2~";  break;
    case CKEY_TYPE_F1:        str = "OP";   break;
    case CKEY_TYPE_F2:        str = "OQ";   break;
    case CKEY_TYPE_F3:        str = "OR";   break;
    case CKEY_TYPE_F4:        str = "OS";   break;
    case CKEY_TYPE_F5:        str = "[15~"; break;
    case CKEY_TYPE_F6:        str = "[17~"; break;
    case CKEY_TYPE_F7:        str = "[18~"; break;
    case CKEY_TYPE_F8:        str = "[19~"; break;
    case CKEY_TYPE_F9:        str = "[20~"; break;
    case CKEY_TYPE_F10:       str = "[22~"; break;
    case CKEY_TYPE_F11:       str = "[23~"; break;
    case CKEY_TYPE_F12:       str = "[24~"; break;
    default:                  str = "";       break;
  }

  return str;
}

const std::string &
CKeyEvent::
getEscapeTextSS3() const
{
  if (! text_.empty())
    return text_;

  return getEscapeTextSS3(type_);
}

const std::string &
CKeyEvent::
getEscapeTextSS3(CKeyType type)
{
  static std::string str;

  switch (type) {
    case CKEY_TYPE_Up:        str = "OA";   break;
    case CKEY_TYPE_Down:      str = "OB";   break;
    case CKEY_TYPE_Right:     str = "OC";   break;
    case CKEY_TYPE_Left:      str = "OD";   break;
    case CKEY_TYPE_Home:      str = "OH";   break;
    case CKEY_TYPE_End:       str = "OF";   break;
    case CKEY_TYPE_Page_Up:   str = "[5~";  break;
    case CKEY_TYPE_Page_Down: str = "[6~";  break;
    case CKEY_TYPE_Insert:    str = "[2~";  break;
    case CKEY_TYPE_F1:        str = "OP";   break;
    case CKEY_TYPE_F2:        str = "OQ";   break;
    case CKEY_TYPE_F3:        str = "OR";   break;
    case CKEY_TYPE_F4:        str = "OS";   break;
    case CKEY_TYPE_F5:        str = "[15~"; break;
    case CKEY_TYPE_F6:        str = "[17~"; break;
    case CKEY_TYPE_F7:        str = "[18~"; break;
    case CKEY_TYPE_F8:        str = "[19~"; break;
    case CKEY_TYPE_F9:        str = "[20~"; break;
    case CKEY_TYPE_F10:       str = "[22~"; break;
    case CKEY_TYPE_F11:       str = "[23~"; break;
    case CKEY_TYPE_F12:       str = "[24~"; break;
    default:                  str = "";       break;
  }

  return str;
}
