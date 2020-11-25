#include "string.h"

int sc_chscmp(char left, char right) {
  return left == right;
}

int sc_chicmp(char left, char right) {
  return sc_ch2uc(left) == sc_ch2uc(right);
}

struct String* sc_strnew(struct String* src) {
  if (src) return src;
  struct String* obj = (struct String*)malloc(sizeof(struct String));
  if (obj) { obj->data = NULL; obj->used = obj->size = 0; }
  return obj;
}

struct String* sc_strdel(struct String* src) {
  if (src) {
    if (src->data) { free(src->data); src->data = NULL; }
    src->used = src->size = 0;
    free(src);
    return src;
  }
  return NULL;
}

struct String* sc_strcpy(const char* src, struct String* dst) {
  if (dst && src) { /* copy */
    if (dst->data) free(dst->data);
    dst->used = 0;
    while (*(src + dst->used)) ++dst->used;
    dst->data = (char*)malloc(dst->size = dst->used + 1);
    if (dst->data) {
      char* trav = dst->data;
      while (*src) *trav++ = *src++;
      *trav = 0;
      return dst;
    }
    dst->used = dst->size = 0;
  } else if (src) { /* create */
    struct String* obj = (struct String*)malloc(sizeof(struct String));
    if (obj) {
       obj->data = NULL;
       return sc_strcpy(src, obj);
    }
  }
  return NULL;
}

struct String* sc_strapp(const char* src, struct String* dst) {
  if (dst && src) {
    if (dst->used) { /* append */
      size_t len = 0; while (*(src + len)) ++len;
      dst->data = realloc(dst->data, dst->size = dst->used + len + 1);
      if (dst->data) {
        char* trav = dst->data + dst->used;
        while (*src) *trav++ = *src++;
        *trav = 0; dst->used += len;
        return dst;
      }
      dst->used = dst->size = 0;
    } else /* copy */ return sc_strcpy(src, NULL);
  } else /* create */ return sc_strcpy(src, NULL);
  return NULL;
}

struct String* sc_strins(size_t off, const char* src, struct String* dst) {
  if (dst) {
    if (dst->used) { /* insert */
      size_t len = 0; while (*(src + len)) ++len;
      dst->data = realloc(dst->data, dst->size = dst->used + len + 1);
      if (dst->data) {
        dst->used += len; dst->data[dst->used] = 0;
        for (size_t i = dst->used - 1; i > off; --i) dst->data[i] = dst->data[i - len];
        char* trav = dst->data + off;
        while (*src) *trav++ = *src++;
        return dst;
      }
      dst->used = dst->size = 0;
    } else /* copy */ return sc_strcpy(src, NULL);
  } else /* create */ return sc_strcpy(src, NULL);
  return NULL;
}

struct String* sc_strrep(size_t count, const char* pat, const char* src, struct String* dst, int (*fcmp)(char, char)) {
  if (dst && src && pat) {
    size_t off = 0;
    if (count == -1 && (off = sc_strsch(dst, pat, fcmp)) != -1) {
      size_t len = 0; while (*(pat + len)) ++len;
      sc_strpop(off, len, dst); sc_strins(off, src, dst);
      while ((off = sc_strsch(dst, NULL, fcmp)) != -1) {
        sc_strpop(off, len, dst); sc_strins(off, src, dst);
      }
      return dst;
    } else if (off != -1) {
      size_t i = 0, len = 0; while (*(pat + len)) ++len;
      sc_strpop(off, len, dst); sc_strins(off, src, dst);
      while (++i < count && (off = sc_strsch(dst, NULL, fcmp)) != -1) ++i;
      sc_strpop(off, len, dst); sc_strins(off, src, dst);
      return dst;
    }
  }
  return NULL;
}

struct String* sc_strpop(size_t off, size_t len, struct String* src) {
  if (src) {
    if (src->data <= (src->data + off) && (src->data + src->used) >= (src->data + off + len)) { /* pop */
      size_t i;
      for (i = off; i < src->used; ++i) *(src->data + i) = *(src->data + i + len);
      *(src->data + i) = 0; src->used -= len;
      return src;
    }
  }
  return NULL;
}

int sc_strcmp(struct String* left, const char* right, int (*fcmp)(char, char)) {
  if (left && right) {
    if (left->data) {
      size_t len = 0; while (*(right + len)) ++len;
      if (left->used > len) return 3;
      if (left->used < len) return 2;
      for (size_t i = 0; i < len; ++i) if (fcmp(left->data[i], right[i]) == 0) return 0;
      return 1;
    }
  }
  return -1;
}

struct String* sc_str2uc(struct String* src) {
  if (src && src->data) {
    for (size_t i = 0; i < src->used; ++i) src->data[i] = sc_ch2uc(src->data[i]);
    return src;
  }
  return NULL;
}

struct String* sc_str2lc(struct String* src) {
  if (src && src->data) {
    for (size_t i = 0; i < src->used; ++i) src->data[i] = sc_ch2uc(src->data[i]);
    return src;
  }
  return NULL;
}

size_t sc_strchr(char chr, struct String* src, int (*fcmp)(char, char)) {
  if (src && src->data) for (size_t i = 0; i < src->used; ++i) if (fcmp(src->data[i], chr) == 1) return i;
  return -1;
}

size_t sc_strsch(const char* pat, struct String* src, int (*fcmp)(char, char)) {
  static char* _pat = NULL;
  static size_t len = 0;
  static size_t _matched = 0;

  if (pat) {
    _pat = (char*)pat; _matched = 0;
    len = 0; while (*(_pat + len)) ++len;
  }

  if (src && src->data && _pat && len <= src->used) {
    size_t matched = 0;
    for (size_t i = 0; i <= src->used - len; i++) { 
        size_t j;
        for (j = 0; j < len; j++) if (fcmp(src->data[i + j], _pat[j]) != 1) break;
        if (j == len) { if (++matched > _matched) { ++_matched; return i; } }
    }
  }
  return -1;
}

struct String* sc_strsub(size_t off, size_t len, struct String* src) {
  if (src && src->data) {
    if (off < src->used) {
      struct String* obj = (struct String*)malloc(sizeof(struct String));
      if (obj) {
        if (src->used > (off + len)) obj->used = len;
        else obj->used = src->used - off;
        obj->data = (char*)malloc(obj->size = obj->used + 1);
        if (obj->data) {
          size_t i;
          for (i = 0; i < obj->used; ++i) obj->data[i] = src->data[i + off];
          obj->data[i] = 0;
          return obj;
        }
      }
    }
  }
  return NULL;
}
