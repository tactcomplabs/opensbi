/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_IPI_H__
#define __SBI_IPI_H__

#include <sbi/sbi_types.h>

#define SBI_IPI_EVENT_SOFT			0x1
#define SBI_IPI_EVENT_FENCE_I			0x2
#define SBI_IPI_EVENT_SFENCE_VMA		0x4
#define SBI_IPI_EVENT_SFENCE_VMA_ASID		0x8
#define SBI_IPI_EVENT_HALT			0x10

struct sbi_scratch;

struct sbi_ipi_data {
	unsigned long ipi_type;
};

struct sbi_tlb_info {
	unsigned long start;
	unsigned long size;
	unsigned long asid;
};

int sbi_ipi_send_many(struct sbi_scratch *scratch,
		      ulong *pmask, u32 event, void *data);

void sbi_ipi_clear_smode(struct sbi_scratch *scratch);

void sbi_ipi_process(struct sbi_scratch *scratch);

int sbi_ipi_init(struct sbi_scratch *scratch, bool cold_boot);

#endif
