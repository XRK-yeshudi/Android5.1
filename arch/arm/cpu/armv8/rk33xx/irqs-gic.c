/*
 * (C) Copyright 2008 Fuzhou Rockchip Electronics Co., Ltd
 * Peter, Software Engineering, <superpeter.cai@gmail.com>.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <asm/io.h>
#include <asm/arch/rkplat.h>


typedef enum INT_TRIG {
	INT_LEVEL_TRIG,
	INT_EDGE_TRIG
} eINT_TRIG;

typedef enum INT_SECURE {
	INT_SECURE,
	INT_NOSECURE
} eINT_SECURE;

typedef enum INT_SIGTYPE {
	INT_SIGTYPE_IRQ,
	INT_SIGTYPE_FIQ
} eINT_SIGTYPE;


/* get interrupt id */
static inline uint32 gic_irq_getid(void)
{
	return readl(RKIO_GICC_PHYS + GICC_IAR) & 0x3ff; /* bit9 - bit0*/
}

/* finish interrupt server */
static inline void gic_irq_finish_server(uint32 nintid)
{
	writel(nintid, RKIO_GICC_PHYS + GICC_EOIR);
}

static int gic_irq_set_trig(int irq, eINT_TRIG ntrig)
{
	uint32 M, N;
	uint32 reg;

	if (irq >= NR_GIC_IRQS)
		return -1;

	M = irq / 16;
	N = irq % 16;

	reg = readl(RKIO_GICD_PHYS + GICD_ICFGR + 4 * M);
	if (ntrig == INT_LEVEL_TRIG)
		writel(reg & (~(1 << (2 * N + 1))), RKIO_GICD_PHYS + GICD_ICFGR + 4 * M);
	else
		writel(reg | (1 << (2 * N + 1)), RKIO_GICD_PHYS + GICD_ICFGR + 4 * M);

	return 0;
}


/* irq set pending */
__maybe_unused static int gic_irq_set_pending(int irq)
{
	uint32 M, N;

	if (irq >= NR_GIC_IRQS)
		return -1;

	M = irq / 32;
	N = irq % 32;
	writel(0x1 << N, RKIO_GICD_PHYS + GICD_ISPENDR + 4 * M);

	return 0;
}


/* irq clear pending */
__maybe_unused static int gic_irq_clear_pending(int irq)
{
	uint32 M, N;

	if (irq >= NR_GIC_IRQS)
		return -1;

	M = irq / 32;
	N = irq % 32;
	writel(0x1 << N, RKIO_GICD_PHYS + GICD_ICPENDR + 4 * M);

	return 0;
}


__maybe_unused static int gic_irq_set_secure(int irq, eINT_SECURE nsecure)
{
	uint32 M, N;

	if (irq >= NR_GIC_IRQS)
		return -1;

	M = irq / 32;
	N = irq % 32;
	writel(nsecure << N, RKIO_GICD_PHYS + GICD_ISENABLER + 4 * M);

	return 0;
}


static uint8 g_gic_cpumask = 1;
static void gic_get_cpumask(void)
{
	uint32 mask, i;

	for (i = mask = 0; i < 32; i += 4) {
		mask = readl(RKIO_GICD_PHYS + GICD_ITARGETSR + i);
		mask |= mask >> 16;
		mask |= mask >> 8;
		if (mask)
			break;
	}

	if (!mask)
		printf("GIC CPU mask not found.\n");

	g_gic_cpumask = mask;
	debug("GIC CPU mask = 0x%p\n", gic_get_cpumask);
}


/* enable irq handler */
static int gic_handler_enable(int irq)
{
	uint32 shift = (irq % 4) * 8;
	uint32 offset = (irq / 4);
	uint32 M, N;
	uint32 reg;

	if (irq >= NR_GIC_IRQS)
		return -1;

	M = irq / 32;
	N = irq % 32;

	reg = readl(RKIO_GICC_PHYS + GICC_CTLR);
	writel(reg & (~0x08), RKIO_GICC_PHYS + GICC_CTLR);

	writel(0x1 << N, RKIO_GICD_PHYS + GICD_ISENABLER + 4 * M);
	reg = readl(RKIO_GICD_PHYS + GICD_ITARGETSR + 4 * offset);
	reg &= ~(0xFF << shift);
	reg |= (g_gic_cpumask << shift);
	writel(reg, RKIO_GICD_PHYS + GICD_ITARGETSR + 4 * offset);

	return 0;
}


/* disable irq handler */
static int gic_handler_disable(int irq)
{
	uint32 M, N;

	if (irq >= NR_GIC_IRQS)
		return -1;

	M = irq / 32;
	N = irq % 32;
	writel(0x1 << N, RKIO_GICD_PHYS + GICD_ICENABLER + 4 * M);

	return 0;
}

/**
 *	irq_set_type - set the irq trigger type for an irq
 *	@irq:	irq number
 *	@type:	IRQ_TYPE_{LEVEL,EDGE}_* value - see asm/arch/irq.h
 */
static int gic_set_irq_type(int irq, unsigned int type)
{
	unsigned int int_type;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
	case IRQ_TYPE_EDGE_FALLING:
		int_type = INT_EDGE_TRIG;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
	case IRQ_TYPE_LEVEL_LOW:
		int_type = INT_LEVEL_TRIG;
		break;
	default:
		return -1;
	}

	gic_irq_set_trig(irq, int_type);

	return 0;
}


static struct irq_chip gic_irq_chip = {
	.name			= (const char *)"gic",

	.irq_disable		= gic_handler_disable,
	.irq_enable		= gic_handler_enable,

	.irq_set_type		= gic_set_irq_type,
};
