/*
 * (C) Copyright 2012 SAMSUNG Electronics
 * Jaehoon Chung <jh80.chung@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <common.h>
#include <malloc.h>
#include <sdhci.h>
#include <asm/arch/mmc.h>
//#include <asm/arch/clk.h>

static char *S5P_NAME = "SAMSUNG SDHCI";
static void s5p_sdhci_set_control_reg(struct sdhci_host *host)
{
	unsigned long val, ctrl;
	/*
	 * SELCLKPADDS[17:16]
	 * 00 = 2mA
	 * 01 = 4mA
	 * 10 = 7mA
	 * 11 = 9mA
	 */
	sdhci_writel(host, SDHCI_CTRL4_DRIVE_MASK(0x3), SDHCI_CONTROL4);

	val = sdhci_readl(host, SDHCI_CONTROL2);
	val &= SDHCI_CTRL2_SELBASECLK_SHIFT;

	val |=	SDHCI_CTRL2_ENSTAASYNCCLR |
		SDHCI_CTRL2_ENCMDCNFMSK |
		SDHCI_CTRL2_ENFBCLKRX |
		SDHCI_CTRL2_ENCLKOUTHOLD;
	printf("s5p_sdhci	SDHCI_CONTROL4	addr=%x\n", host->ioaddr + SDHCI_CONTROL4);
	printf("s5p_sdhci_set_control_reg	SDHCI_CONTROL4	val=%x\n", val);

	sdhci_writel(host, val, SDHCI_CONTROL2);

	/*
	 * FCSEL3[31] FCSEL2[23] FCSEL1[15] FCSEL0[7]
	 * FCSel[1:0] : Rx Feedback Clock Delay Control
	 *	Inverter delay means10ns delay if SDCLK 50MHz setting
	 *	01 = Delay1 (basic delay)
	 *	11 = Delay2 (basic delay + 2ns)
	 *	00 = Delay3 (inverter delay)
	 *	10 = Delay4 (inverter delay + 2ns)
	 */
	val = SDHCI_CTRL3_FCSEL0 | SDHCI_CTRL3_FCSEL1;
	printf("s5p_sdhci	SDHCI_CONTROL3	addr=%x\n", host->ioaddr + SDHCI_CONTROL3);
	printf("s5p_sdhci_set_control_reg	SDHCI_CONTROL3	val=%x\n", val);
	sdhci_writel(host, val, SDHCI_CONTROL3);

	/*
	 * SELBASECLK[5:4]
	 * 00/01 = HCLK
	 * 10 = EPLL
	 * 11 = XTI or XEXTCLK
	 */
	ctrl = sdhci_readl(host, SDHCI_CONTROL2);
	ctrl &= ~SDHCI_CTRL2_SELBASECLK_MASK(0x3);
	ctrl |= SDHCI_CTRL2_SELBASECLK_MASK(0x2);
	printf("s5p_sdhci	SDHCI_CONTROL2	addr=%x\n", host->ioaddr + SDHCI_CONTROL2);
	printf("s5p_sdhci_set_control_reg	SDHCI_CONTROL2	val=%x\n", ctrl);
	sdhci_writel(host, ctrl, SDHCI_CONTROL2);
}


void set_mmc_clk(int dev_index, unsigned int div)
{
	/* Do NOTHING */
	
}

int s5p_sdhci_init(u32 regbase, int index, int bus_width)
{
	printf("s5p_sdhci_init	start\n");

	struct sdhci_host *host = NULL;
	host = (struct sdhci_host *)malloc(sizeof(struct sdhci_host));
	if (!host) {
		printf("sdhci__host malloc fail!\n");
		return 1;
	}

	host->name = S5P_NAME;
	host->ioaddr = (void *)regbase;
	printf("s5p_sdhci_init	host->ioaddr%x\n", host->ioaddr);

	host->quirks = SDHCI_QUIRK_NO_HISPD_BIT | SDHCI_QUIRK_BROKEN_VOLTAGE |
		SDHCI_QUIRK_BROKEN_R1B | SDHCI_QUIRK_32BIT_DMA_ADDR |
		SDHCI_QUIRK_WAIT_SEND_CMD;
	printf("s5p_sdhci_init	host->quirks%x\n", host->quirks);
	host->voltages = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195;
	printf("s5p_sdhci_init	host->voltages%x\n", host->voltages);
	host->version = sdhci_readw(host, SDHCI_HOST_VERSION);
	printf("s5p_sdhci_init	host->version%x\n", host->version);

	host->set_control_reg = &s5p_sdhci_set_control_reg;
	host->set_clock = set_mmc_clk;
	host->index = index;
	printf("s5p_sdhci_init	host->index%x\n", host->index);

	host->host_caps = MMC_MODE_HC;
	printf("s5p_sdhci_init	host->host_caps%x\n", host->host_caps);

	add_sdhci(host, 52000000, 400000);
	printf("s5p_sdhci_init	end\n");
	return 0;
}
