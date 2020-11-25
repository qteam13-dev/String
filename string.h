#ifndef SC_INC_STRING
# define SC_INC_STRING

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define sc_chuc(x)  ((x) >= 65 && (x) <= 90)
#define sc_chlc(x)  ((x) >= 97 && (x) <= 122)
#define sc_ch2uc(x) (sc_chlc(x) ? ((x) - 32) : (x))
#define sc_ch2lc(x) (sc_chlc(x) ? ((x) + 32) : (x))

int sc_chscmp(char left, char right);
int sc_chicmp(char left, char right);

typedef struct String {
  char*  data; /* allocated blocks */
  size_t used; /* number of filled blocks */
  size_t size; /* number of allocated blocks */
} String;

struct String* sc_strnew(struct String* src);
struct String* sc_strdel(struct String* src);
struct String* sc_strcpy(const char* src, struct String* dst);
struct String* sc_strapp(const char* src, struct String* dst);
struct String* sc_strins(size_t off, const char* src, struct String* dst);
struct String* sc_strrep(size_t count, const char* pat, const char* src, struct String* dst, int (*fcmp)(char, char));
struct String* sc_strpop(size_t off, size_t len, struct String* src);
int            sc_strcmp(struct String* left, const char* right, int (*fcmp)(char, char));
struct String* sc_str2uc(struct String* src);
struct String* sc_str2lc(struct String* src);
size_t         sc_strchr(char chr, struct String* src,int (*fcmp)(char, char));
size_t         sc_strsch(const char* pat, struct String* src, int (*fcmp)(char, char));
struct String* sc_strsub(size_t off, size_t len, struct String* src);

#ifdef __cplusplus
}
#endif

#endif