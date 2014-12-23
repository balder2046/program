#ifndef COMMONDEFINE_H
#define COMMONDEFINE_H
#include <stddef.h>
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) if ((x) != 0) {delete (x);(x) = 0;};
#endif
#ifndef NULL
#define NULL 0
#endif
#ifndef byte
typedef unsigned char byte;
#endif

#endif /* COMMONDEFINE_H */
