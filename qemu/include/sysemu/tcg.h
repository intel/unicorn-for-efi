/*
 * QEMU TCG support
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 */

#ifndef SYSEMU_TCG_H
#define SYSEMU_TCG_H

#include "uc_priv.h"

void tcg_exec_init(struct uc_struct *uc, unsigned long tb_size);

uc_err tcg_set_native_thunks(uc_engine *uc,
                             uc_cb_is_native_t is_native,
                             uc_cb_call_native_t call_native);

void tcg_get_code_gen_buf(struct uc_struct *uc,
                          void **code_gen_buf,
                          size_t *code_gen_size);

#endif
