#include "libMUSCLE/muscle.h"
#include <stdio.h>

namespace muscle {

static TLS<char[64]> szMsg;

// Define XXXToStr(XXX x) functions for each enum type XXX.
#define s(t)	const char *t##ToStr(t x) { switch (x) { case t##_Undefined: return "Undefined";
#define c(t, x)	case t##_##x: return #x;
#define e(t)	} sprintf(szMsg.get(), #t "_%d", x); return szMsg.get(); }
#include "libMUSCLE/enums.h"

// Define StrToXXX(const char *Str) functions for each enum type XXX.
#define s(t)	t StrTo##t(const char *Str) { if (0) ;
#define c(t, x)	else if (0 == stricmp(#x, Str)) return t##_##x;
#define e(t)	Quit("Invalid value %s for type %s", Str, #t); return t##_Undefined; }
#include "libMUSCLE/enums.h"
} 
