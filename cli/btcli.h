#ifndef BTCLI_H
#define BTCLI_H

#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <libgen.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "btpd_if.h"
#include "metainfo.h"
#include "subr.h"
#include "benc.h"
#include "iobuf.h"
#include "queue.h"

extern const char *btpd_dir;
extern struct ipc *ipc;

/* print message to stderr and exit with 1 */
__attribute__((noreturn))
void diemsg(const char *fmt, ...);
/* open and verify communication with btpd instance */
void btpd_connect(void);
/* handle result from ipc error code */
enum ipc_err handle_ipc_res(enum ipc_err err, const char *cmd,
    const char *target);
/* get a character representing the state of a torrent */
char tstate_char(enum ipc_tstate ts);
/* TODO, NOT SURE */
int torrent_spec(char *arg, struct ipc_torrent *tp);

/* pretty print upload/download rate into MB/s or kB/s */
void print_rate(long long rate);
/* pretty print a bytesize into G or M */
void print_size(long long size);
/* pretty print space padded ratio */
void print_ratio(long long part, long long whole);
/* pretty print a percentage */
void print_percent(long long part, long long whole);

/* usage_OPERATION: print usage for the given OPERATION
 * cmd_OPERATION:   parse arguments for the given OPERATION
 */
void usage_add(void);
void cmd_add(int argc, char **argv);
void usage_del(void);
void cmd_del(int argc, char **argv);
void usage_list(void);
void cmd_list(int argc, char **argv);
void usage_stat(void);
void cmd_stat(int argc, char **argv);
void usage_kill(void);
void cmd_kill(int argc, char **argv);
void usage_rate(void);
void cmd_rate(int argc, char **argv);
void usage_start(void);
void cmd_start(int argc, char **argv);
void usage_stop(void);
void cmd_stop(int argc, char **argv);

#endif
