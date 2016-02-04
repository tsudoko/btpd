#ifndef BTPD_ACTIVE_H
#define BTPD_ACTIVE_H

/* add a torrent using its hash */
void active_add(const uint8_t *hash);
/* del a torrent using its hash */
void active_del(const uint8_t *hash);
/* remove link to the active file */
void active_clear(void);
/* activate all torrents */
void active_start(void);

#endif
