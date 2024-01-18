/* rvl/dwc.h
 *   by Alex Chadwick
 * 
 * Copyright (C) 2014, Alex Chadwick
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* definitions of symbols inferred to exist in a dwc header file for which the
 * brainslug symbol information is available. */
 
#ifndef _RVL_DWC_H_
#define _RVL_DWC_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* DWC is the online matchmaking library. */
typedef enum DWC_LogType_t {
    DWC_Info = 1 << 0,
    DWC_Error = 1 << 1,
    DWC_Debug = 1 << 2,
    DWC_Warn = 1 << 3,
    DWC_Acheck = 1 << 4,
    DWC_Login = 1 << 5,
    DWC_Match_NN = 1 << 6,
    DWC_Match_GT2 = 1 << 7,
    DWC_Transport = 1 << 8,
    DWC_QR2_Req = 1 << 9,
    DWC_SB_Update = 1 << 10,
    DWC_Send = 1 << 15,
    DWC_Recv = 1 << 16,
    DWC_Update_SV = 1 << 17,
    DWC_ConnectInet = 1 << 18,
    DWC_Auth = 1 << 24,
    DWC_Ac = 1 << 25,
    DWC_Bm = 1 << 26,
    DWC_Util = 1 << 27,
    DWC_Option_CF = 1 << 28,
    DWC_Option_ConnTest = 1 << 29,
    DWC_Gamespy = 1 << 31,
    DWC_Unknown,
} DWC_LogType_t;

#ifdef __GNUC__
#ifndef __ATTRIBUTE_PRINTF
#define __ATTRIBUTE_PRINTF(str, args) \
    __attribute__ ((format (printf, str, args)))
#endif
#endif

/* or together bits in DWC_LogType_t to set which messages to allow. */
void DWC_SetLogMask(DWC_LogType_t log_mask);
void DWC_Log(DWC_LogType_t category, const char *format, ...)
    __ATTRIBUTE_PRINTF(2, 3);
int DWC_LoginAsync(void *r3, int r4, void (*r5)(int, int, void *), void *r6);

struct dwc_buddy {
    uint8_t _unk0[0x4 - 0x0];
    uint32_t pid;
    uint8_t _unk8[0xc - 0x8];
};
uint8_t dwc_get_friend_status(const struct dwc_buddy *buddy, uint8_t *loc, int *loc_length);

bool DWC_SetupGameServer(int player_count, void (*r4)(void *), void *r5, int r6, int r7, void (*r8)(void *), uint8_t *r9, void *r10);
bool DWC_ConnectToGameServerAsync (int player_count, void (*r4)(void *), void *r5, int r6, int r7, void (*r8)(void *), uint8_t *r9, void *r10);
int dwc_send_status_record(int type, uint32_t pid, uint32_t ip, uint16_t port, const uint32_t *packet, size_t packet_len_in_words);
int dwc_process_status_record(int type, uint32_t pid, uint32_t ip, uint16_t port, const uint32_t *packet, size_t packet_len_in_words);
void dwc_unknown_800ccc38(void);
extern uint32_t dwc_unknown_800d577c[];
int dwc_qr2_init(uint32_t pid);
int DWCi_SBUpdateAsync(uint32_t pid);
int dwc_init_gt2_socket(void);
void dwc_think(int);

#endif /* _RVL_DWC_H_ */