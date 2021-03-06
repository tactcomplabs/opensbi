/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_SCRATCH_H__
#define __SBI_SCRATCH_H__

#include <sbi/riscv_asm.h>

/** Offset of fw_start member in sbi_scratch */
#define SBI_SCRATCH_FW_START_OFFSET		(0 * __SIZEOF_POINTER__)
/** Offset of fw_size member in sbi_scratch */
#define SBI_SCRATCH_FW_SIZE_OFFSET		(1 * __SIZEOF_POINTER__)
/** Offset of next_arg1 member in sbi_scratch */
#define SBI_SCRATCH_NEXT_ARG1_OFFSET		(2 * __SIZEOF_POINTER__)
/** Offset of next_addr member in sbi_scratch */
#define SBI_SCRATCH_NEXT_ADDR_OFFSET		(3 * __SIZEOF_POINTER__)
/** Offset of next_mode member in sbi_scratch */
#define SBI_SCRATCH_NEXT_MODE_OFFSET		(4 * __SIZEOF_POINTER__)
/** Offset of warmboot_addr member in sbi_scratch */
#define SBI_SCRATCH_WARMBOOT_ADDR_OFFSET	(5 * __SIZEOF_POINTER__)
/** Offset of platform_addr member in sbi_scratch */
#define SBI_SCRATCH_PLATFORM_ADDR_OFFSET	(6 * __SIZEOF_POINTER__)
/** Offset of hartid_to_scratch member in sbi_scratch */
#define SBI_SCRATCH_HARTID_TO_SCRATCH_OFFSET	(7 * __SIZEOF_POINTER__)
/** Offset of tmp0 member in sbi_scratch */
#define SBI_SCRATCH_TMP0_OFFSET			(8 * __SIZEOF_POINTER__)

/** sbi_ipi_data is located behind sbi_scratch. This struct is not packed. */
/** Offset of ipi_type in sbi_ipi_data */
#define SBI_IPI_DATA_IPI_TYPE_OFFSET		(15 * __SIZEOF_POINTER__)

#define SBI_SCRATCH_TLB_INFO_OFFSET		(16 * __SIZEOF_POINTER__)
/** Maximum size of sbi_scratch and sbi_ipi_data */
#define SBI_SCRATCH_SIZE			(32 * __SIZEOF_POINTER__)

#ifndef __ASSEMBLY__

#include <sbi/sbi_types.h>
#include <sbi/sbi_ipi.h>

/** Representation of per-HART scratch space */
struct sbi_scratch {
	/** Start (or base) address of firmware linked to OpenSBI library */
	unsigned long fw_start;
	/** Size (in bytes) of firmware linked to OpenSBI library */
	unsigned long fw_size;
	/** Arg1 (or 'a1' register) of next booting stage for this HART */
	unsigned long next_arg1;
	/** Address of next booting stage for this HART */
	unsigned long next_addr;
	/** Priviledge mode of next booting stage for this HART */
	unsigned long next_mode;
	/** Warm boot entry point address for this HART */
	unsigned long warmboot_addr;
	/** Address of sbi_platform */
	unsigned long platform_addr;
	/** Address of HART ID to sbi_scratch conversion function */
	unsigned long hartid_to_scratch;
	/** Temporary storage */
	unsigned long tmp0;
} __packed;

/** Get pointer to sbi_scratch for current HART */
#define sbi_scratch_thishart_ptr()	\
((struct sbi_scratch *)csr_read(CSR_MSCRATCH))

/** Get Arg1 of next booting stage for current HART */
#define sbi_scratch_thishart_arg1_ptr()	\
((void *)(sbi_scratch_thishart_ptr()->next_arg1))

/** Get pointer to sbi_ipi_data from sbi_scratch */
#define sbi_ipi_data_ptr(scratch)      \
((struct sbi_ipi_data *)(void*)scratch + SBI_IPI_DATA_IPI_TYPE_OFFSET)

/** Get pointer to tlb flush info from sbi_scratch */
#define sbi_tlb_info_ptr(scratch)      \
((struct sbi_tlb_info *)(void*)scratch + SBI_SCRATCH_TLB_INFO_OFFSET)

#endif

#endif
