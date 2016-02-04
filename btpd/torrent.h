#ifndef BTPD_TORRENT_H
#define BTPD_TORRENT_H

#define PIECE_BLOCKLEN (1 << 14)
#define RELPATH_SIZE SHAHEXSIZE

enum torrent_state {
    T_STARTING,
    T_LEECH,
    T_SEED,
    T_STOPPING,
    T_GHOST
};

struct torrent {
    struct tlib *tl;

    enum torrent_state state;
    int delete;

    struct content *cm;
    struct trackers *tr;
    struct net *net;

    off_t total_length;
    off_t piece_length;
    uint32_t npieces;
    unsigned nfiles;
    struct mi_file *files;
    size_t pieces_off;

    BTPDQ_ENTRY(torrent) entry;
};

BTPDQ_HEAD(torrent_tq, torrent);

/* get current number of torrents */
unsigned torrent_count(void);
/* get current number of ghosts
 * TODO, what is a ghost? 
 */
unsigned torrent_ghosts(void);
/* get reference to struct of all torrents */
const struct torrent_tq *torrent_get_all(void);
/* get reference to torrent by its number */
struct torrent *torrent_by_num(unsigned num);
/* get reference to torrent by its info hash */
struct torrent *torrent_by_hash(const uint8_t *hash);

/* start torrent and return error status from IPC */
enum ipc_err torrent_start(struct tlib *tl);
/* stop torrent and optionally delete torrent*/
void torrent_stop(struct torrent *tp, int delete);

/* check active, haunting, and startable status */
int torrent_active(struct tlib *tl);
int torrent_haunting(struct tlib *tl);
int torrent_startable(struct tlib *tl);

/* get size of torrent piece at index 'piece' */
off_t torrent_piece_size(struct torrent *tp, uint32_t piece);
/* get number of blocks in a piece */
uint32_t torrent_piece_blocks(struct torrent *tp, uint32_t piece);
/* TODO, not sure about this one */
uint32_t torrent_block_size(struct torrent *tp, uint32_t piece,
    uint32_t nblocks, uint32_t block);
/* get the name of a torrent */
const char *torrent_name(struct torrent *tp);

/* TODO, not sure about this one */
void torrent_on_tick_all(void);

#endif
