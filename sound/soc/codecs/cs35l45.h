/* SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause */
/*
 * cs35l45.h - CS35L45 ALSA SoC audio driver
 *
 * Copyright 2019-2022 Cirrus Logic, Inc.
 *
 * Author: James Schulman <james.schulman@cirrus.com>
 *
 */

#ifndef CS35L45_H
#define CS35L45_H

#include <linux/pm_runtime.h>
#include <linux/regmap.h>
#include <linux/regulator/consumer.h>

#define CS35L45_DEVID				0x00000000
#define CS35L45_REVID				0x00000004
#define CS35L45_RELID				0x0000000C
#define CS35L45_OTPID				0x00000010
#define CS35L45_SFT_RESET			0x00000020
#define CS35L45_GLOBAL_ENABLES			0x00002014
#define CS35L45_BLOCK_ENABLES			0x00002018
#define CS35L45_BLOCK_ENABLES2			0x0000201C
#define CS35L45_ERROR_RELEASE			0x00002034
#define CS35L45_REFCLK_INPUT			0x00002C04
#define CS35L45_GLOBAL_SAMPLE_RATE		0x00002C0C
#define CS35L45_BOOST_CCM_CFG			0x00003808
#define CS35L45_BOOST_DCM_CFG			0x0000380C
#define CS35L45_BOOST_OV_CFG			0x0000382C
#define CS35L45_ASP_ENABLES1			0x00004800
#define CS35L45_ASP_CONTROL1			0x00004804
#define CS35L45_ASP_CONTROL2			0x00004808
#define CS35L45_ASP_CONTROL3			0x0000480C
#define CS35L45_ASP_FRAME_CONTROL1		0x00004810
#define CS35L45_ASP_FRAME_CONTROL2		0x00004814
#define CS35L45_ASP_FRAME_CONTROL5		0x00004820
#define CS35L45_ASP_DATA_CONTROL1		0x00004830
#define CS35L45_ASP_DATA_CONTROL5		0x00004840
#define CS35L45_DACPCM1_INPUT			0x00004C00
#define CS35L45_ASPTX1_INPUT			0x00004C20
#define CS35L45_ASPTX2_INPUT			0x00004C24
#define CS35L45_ASPTX3_INPUT			0x00004C28
#define CS35L45_ASPTX4_INPUT			0x00004C2C
#define CS35L45_ASPTX5_INPUT			0x00004C30
#define CS35L45_LDPM_CONFIG			0x00006404
#define CS35L45_AMP_PCM_CONTROL			0x00007000
#define CS35L45_AMP_PCM_HPF_TST			0x00007004
#define CS35L45_IRQ1_EINT_4			0x0000E01C
#define CS35L45_LASTREG				0x0000E01C

/* SFT_RESET */
#define CS35L45_SOFT_RESET_TRIGGER		0x5A000000

/* GLOBAL_ENABLES */
#define CS35L45_GLOBAL_EN_SHIFT			0
#define CS35L45_GLOBAL_EN_MASK			BIT(0)

/* BLOCK_ENABLES */
#define CS35L45_IMON_EN_SHIFT			13
#define CS35L45_VMON_EN_SHIFT			12
#define CS35L45_VDD_BSTMON_EN_SHIFT		9
#define CS35L45_VDD_BATTMON_EN_SHIFT		8
#define CS35L45_BST_EN_SHIFT			4
#define CS35L45_BST_EN_MASK			GENMASK(5, 4)

#define CS35L45_BST_DISABLE_FET_ON              0x01

/* BLOCK_ENABLES2 */
#define CS35L45_ASP_EN_SHIFT			27

/* ERROR_RELEASE */
#define CS35L45_GLOBAL_ERR_RLS_MASK		BIT(11)

/* REFCLK_INPUT */
#define CS35L45_PLL_FORCE_EN_SHIFT		16
#define CS35L45_PLL_FORCE_EN_MASK		BIT(16)
#define CS35L45_PLL_OPEN_LOOP_SHIFT		11
#define CS35L45_PLL_OPEN_LOOP_MASK		BIT(11)
#define CS35L45_PLL_REFCLK_FREQ_SHIFT		5
#define CS35L45_PLL_REFCLK_FREQ_MASK		GENMASK(10, 5)
#define CS35L45_PLL_REFCLK_EN_SHIFT		4
#define CS35L45_PLL_REFCLK_EN_MASK		BIT(4)
#define CS35L45_PLL_REFCLK_SEL_SHIFT		0
#define CS35L45_PLL_REFCLK_SEL_MASK		GENMASK(2, 0)

#define CS35L45_PLL_REFCLK_SEL_BCLK		0x0

/* GLOBAL_SAMPLE_RATE */
#define CS35L45_GLOBAL_FS_SHIFT			0
#define CS35L45_GLOBAL_FS_MASK			GENMASK(4, 0)

#define CS35L45_48P0_KHZ			0x03
#define CS35L45_96P0_KHZ			0x04
#define CS35L45_44P100_KHZ			0x0B
#define CS35L45_88P200_KHZ			0x0C

/* ASP_ENABLES_1 */
#define CS35L45_ASP_RX2_EN_SHIFT		17
#define CS35L45_ASP_RX1_EN_SHIFT		16
#define CS35L45_ASP_TX5_EN_SHIFT		4
#define CS35L45_ASP_TX4_EN_SHIFT		3
#define CS35L45_ASP_TX3_EN_SHIFT		2
#define CS35L45_ASP_TX2_EN_SHIFT		1
#define CS35L45_ASP_TX1_EN_SHIFT		0

/* ASP_CONTROL2 */
#define CS35L45_ASP_WIDTH_RX_SHIFT		24
#define CS35L45_ASP_WIDTH_RX_MASK		GENMASK(31, 24)
#define CS35L45_ASP_WIDTH_TX_SHIFT		16
#define CS35L45_ASP_WIDTH_TX_MASK		GENMASK(23, 16)
#define CS35L45_ASP_FMT_SHIFT			8
#define CS35L45_ASP_FMT_MASK			GENMASK(10, 8)
#define CS35L45_ASP_BCLK_INV_SHIFT		6
#define CS35L45_ASP_BCLK_INV_MASK		BIT(6)
#define CS35L45_ASP_FSYNC_INV_SHIFT		2
#define CS35L45_ASP_FSYNC_INV_MASK		BIT(2)

#define CS35l45_ASP_FMT_DSP_A			0
#define CS35L45_ASP_FMT_I2S			2

/* ASP_CONTROL3 */
#define CS35L45_ASP_DOUT_HIZ_CTRL_SHIFT		0
#define CS35L45_ASP_DOUT_HIZ_CTRL_MASK		GENMASK(1, 0)

/* ASP_FRAME_CONTROL1 */
#define CS35L45_ASP_TX4_SLOT_SHIFT		24
#define CS35L45_ASP_TX4_SLOT_MASK		GENMASK(29, 24)
#define CS35L45_ASP_TX3_SLOT_SHIFT		16
#define CS35L45_ASP_TX3_SLOT_MASK		GENMASK(21, 16)
#define CS35L45_ASP_TX2_SLOT_SHIFT		8
#define CS35L45_ASP_TX2_SLOT_MASK		GENMASK(13, 8)
#define CS35L45_ASP_TX1_SLOT_SHIFT		0
#define CS35L45_ASP_TX1_SLOT_MASK		GENMASK(5, 0)

#define CS35L45_ASP_TX_ALL_SLOTS		(CS35L45_ASP_TX4_SLOT_MASK | \
						CS35L45_ASP_TX3_SLOT_MASK  | \
						CS35L45_ASP_TX2_SLOT_MASK  | \
						CS35L45_ASP_TX1_SLOT_MASK)
/* ASP_FRAME_CONTROL5 */
#define CS35L45_ASP_RX2_SLOT_SHIFT		8
#define CS35L45_ASP_RX2_SLOT_MASK		GENMASK(13, 8)
#define CS35L45_ASP_RX1_SLOT_SHIFT		0
#define CS35L45_ASP_RX1_SLOT_MASK		GENMASK(5, 0)

#define CS35L45_ASP_RX_ALL_SLOTS		(CS35L45_ASP_RX2_SLOT_MASK | \
						CS35L45_ASP_RX1_SLOT_MASK)

/* ASP_DATA_CONTROL1 */
/* ASP_DATA_CONTROL5 */
#define CS35L45_ASP_WL_SHIFT			0
#define CS35L45_ASP_WL_MASK			GENMASK(5, 0)

/* AMP_PCM_CONTROL */
#define CS35L45_AMP_VOL_PCM_SHIFT		0
#define CS35L45_AMP_VOL_PCM_WIDTH		11

/* AMP_PCM_HPF_TST */
#define CS35l45_HPF_DEFAULT			0x00000000
#define CS35L45_HPF_44P1			0x000108BD
#define CS35L45_HPF_88P2			0x0001045F

/* IRQ1_EINT_4 */
#define CS35L45_OTP_BOOT_DONE_STS_MASK		BIT(1)
#define CS35L45_OTP_BUSY_MASK			BIT(0)

/* Mixer sources */
#define CS35L45_PCM_SRC_MASK			0x7F
#define CS35L45_PCM_SRC_ZERO			0x00
#define CS35L45_PCM_SRC_ASP_RX1			0x08
#define CS35L45_PCM_SRC_ASP_RX2			0x09
#define CS35L45_PCM_SRC_VMON			0x18
#define CS35L45_PCM_SRC_IMON			0x19
#define CS35L45_PCM_SRC_ERR_VOL			0x20
#define CS35L45_PCM_SRC_CLASSH_TGT		0x21
#define CS35L45_PCM_SRC_VDD_BATTMON		0x28
#define CS35L45_PCM_SRC_VDD_BSTMON		0x29
#define CS35L45_PCM_SRC_TEMPMON			0x3A
#define CS35L45_PCM_SRC_INTERPOLATOR		0x40
#define CS35L45_PCM_SRC_IL_TARGET		0x48

#define CS35L45_RESET_HOLD_US			2000
#define CS35L45_RESET_US			2000
#define CS35L45_POST_GLOBAL_EN_US		5000
#define CS35L45_PRE_GLOBAL_DIS_US		3000

#define CS35L45_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
			 SNDRV_PCM_FMTBIT_S24_3LE| \
			 SNDRV_PCM_FMTBIT_S24_LE)

#define CS35L45_RATES (SNDRV_PCM_RATE_44100 | \
		       SNDRV_PCM_RATE_48000 | \
		       SNDRV_PCM_RATE_88200 | \
		       SNDRV_PCM_RATE_96000)

struct cs35l45_private {
	struct device *dev;
	struct regmap *regmap;
	struct gpio_desc *reset_gpio;
	struct regulator *vdd_batt;
	struct regulator *vdd_a;
	bool initialized;
	bool sysclk_set;
	u8 slot_width;
	u8 slot_count;
};

extern const struct dev_pm_ops cs35l45_pm_ops;
extern const struct regmap_config cs35l45_i2c_regmap;
extern const struct regmap_config cs35l45_spi_regmap;
int cs35l45_apply_patch(struct cs35l45_private *cs43l45);
unsigned int cs35l45_get_clk_freq_id(unsigned int freq);
int cs35l45_probe(struct cs35l45_private *cs35l45);
int cs35l45_remove(struct cs35l45_private *cs35l45);

#endif /* CS35L45_H */