#ifndef BTPD_BENC_H
#define BTPD_BENC_H

/* Unused */
enum be_type {
    BE_ANY,
    BE_DCT,
    BE_INT,
    BE_LST,
    BE_STR
};

/* PARAM p is the beginning of a message candidate.
 * PARAM len is expected length of message.
 * Determines if input describes a valid bencode message.
 * Returns 0 if so, otherwise returns EINVAL.
 */
int benc_validate(const char *p, size_t len);

/* Unreachable */
int benc_dct_chk(const char *p, int count, ...);

/* Determines if passed token indicates type list,
 * dictionary, integer or byte string, respectively.
 * Notice that benc_islst(p) also checks for dictionary token.
 */
int benc_islst(const char *p);
int benc_isdct(const char *p);
int benc_isint(const char *p);
int benc_isstr(const char *p);

/* Compares two byte strings. 
 *          / 0 if they are equal
 * Returns { -1 if str1 shorter than str2
 *          \ 1 otherwise
 */
int benc_strcmp(const char *str1, const char *str2);

/* Returns length of a byte string, length of other type
 * or returns number of elements in a list or dictionary, respectively.
 */
size_t benc_strlen(const char *p);
size_t benc_length(const char *p);
size_t benc_nelems(const char *p);

/* Returns position of next element in list or dictionary.
 * Begin by calling benc_first(p) to check empty cases.
 */
const char *benc_first(const char *p);
const char *benc_next(const char *p);

/* PARAM len CHANGES TO size of byte string as declared by its key.
 * PARAM next CHANGES TO beginning of next element in list/dictionary, if any.
 * Returns decoded integer, starting position of string data, the decoded string
 * or the decoded string with appended null terminator, respectively.
 */
long long benc_int(const char *p, const char **next);
const char *benc_mem(const char *p, size_t *len, const char **next);
char *benc_mema(const char *p, size_t *len, const char **next);
char *benc_str(const char *p, size_t *len, const char **next);

/* PARAM len CHANGES TO size of byte string as declared by its key.
 * Searches bencode dictioanry for key.
 * Returns matching value if found, otherwise returns some null value.
 */
const char *benc_dget_any(const char *p, const char *key);
const char *benc_dget_lst(const char *p, const char *key);
const char *benc_dget_dct(const char *p, const char *key);
long long benc_dget_int(const char *p, const char *key);
const char *benc_dget_mem(const char *p, const char *key, size_t *len);
char *benc_dget_mema(const char *p, const char *key, size_t *len);
char *benc_dget_str(const char *p, const char *key, size_t *len);

#endif
