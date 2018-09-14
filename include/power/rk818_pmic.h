/*
 * (C) Copyright 2008-2015 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __RK818_PMIC_H__
#define __RK818_PMIC_H__
#include <power/pmic.h>
#include <fdtdec.h>

#define COMPAT_ROCKCHIP_RK818  "rockchip,rk818"
#define RK818_I2C_ADDR 		0x1c
#define RK818_I2C_SPEED		200000
#define RK818_NUM_REGULATORS	14

#define RK818_SECONDS_REG 0x00
#define RK818_MINUTES_REG 0x01
#define RK818_HOURS_REG 0x02
#define RK818_DAYS_REG 0x03
#define RK818_MONTHS_REG 0x04
#define RK818_YEARS_REG 0x05
#define RK818_WEEKS_REG 0x06
#define RK818_ALARM_SECONDS_REG 0x07
#define RK818_ALARM_MINUTES_REG 0x08
#define RK818_ALARM_HOURS_REG 0x09
#define RK818_ALARM_DAYS_REG 0x0a
#define RK818_ALARM_MONTHS_REG 0x0b
#define RK818_ALARM_YEARS_REG 0x0c
#define RK818_RTC_CTRL_REG 0x10
#define RK818_RTC_STATUS_REG 0x11
#define RK818_RTC_INT_REG 0x12
#define RK818_RTC_COMP_LSB_REG 0x13
#define RK818_RTC_COMP_MSB_REG 0x14
#define RK818_CLK32OUT_REG 0x20
#define RK818_VB_MON_REG 0x21
#define RK818_THERMAL_REG 0x22
#define RK818_DCDC_EN_REG 0x23
#define RK818_LDO_EN_REG 0x24
#define RK818_SLEEP_SET_OFF_REG1 0x25
#define RK818_SLEEP_SET_OFF_REG2 0x26
#define RK818_DCDC_UV_STS_REG 0x27
#define RK818_DCDC_UV_ACT_REG 0x28
#define RK818_LDO_UV_STS_REG 0x29
#define RK818_LDO_UV_ACT_REG 0x2a
#define RK818_DCDC_PG_REG 0x2b
#define RK818_LDO_PG_REG 0x2c
#define RK818_VOUT_MON_TDB_REG 0x2d
#define RK818_BUCK1_CONFIG_REG 0x2e
#define RK818_BUCK1_ON_REG 0x2f
#define RK818_BUCK1_SLP_REG 0x30
#define RK818_BUCK2_CONFIG_REG 0x32
#define RK818_BUCK2_ON_REG 0x33
#define RK818_BUCK2_SLP_REG 0x34
#define RK818_BUCK3_CONFIG_REG 0x36
#define RK818_BUCK4_CONFIG_REG 0x37
#define RK818_BUCK4_ON_REG 0x38
#define RK818_BUCK4_SLP_VSEL_REG 0x39
#define RK818_BOOST_CONFIG_REG 0x3a
#define RK818_LDO1_ON_VSEL_REG 0x3b
#define RK818_LDO1_SLP_VSEL_REG 0x3c
#define RK818_LDO2_ON_VSEL_REG 0x3d
#define RK818_LDO2_SLP_VSEL_REG 0x3e
#define RK818_LDO3_ON_VSEL_REG 0x3f
#define RK818_LDO3_SLP_VSEL_REG 0x40
#define RK818_LDO4_ON_VSEL_REG 0x41
#define RK818_LDO4_SLP_VSEL_REG 0x42
#define RK818_LDO5_ON_VSEL_REG 0x43
#define RK818_LDO5_SLP_VSEL_REG 0x44
#define RK818_LDO6_ON_VSEL_REG 0x45
#define RK818_LDO6_SLP_VSEL_REG 0x46
#define RK818_LDO7_ON_VSEL_REG 0x47
#define RK818_LDO7_SLP_VSEL_REG 0x48
#define RK818_LDO8_ON_VSEL_REG 0x49
#define RK818_LDO8_SLP_VSEL_REG 0x4a
#define RK818_BOOST_LDO9_ON_VSEL_REG 0x54
#define RK818_BOOST_LDO9_SLP_VSEL_REG 0x55
#define RK818_DEVCTRL_REG 0x4b
#define RK818_INT_STS_REG1 0X4c
#define RK818_INT_STS_MSK_REG1 0X4d
#define RK818_INT_STS_REG2 0X4e
#define RK818_INT_STS_MSK_REG2 0X4f
#define RK818_IO_POL_REG 0X50
/*
#define USB_CTRL_REG				0xA1
#define CHRG_CTRL_REG1				0xA3
#define GGSTS						0xB1
#define BAT_VOL_REGH				0xC4
#define BAT_VOL_REGL				0xC5
#define  SOC_REG						0xE0
#define VCALIB0_REGH				0xD5
#define VCALIB0_REGL				0xD6
#define VCALIB1_REGH				0xD7
#define VCALIB1_REGL				0xD8
*/
/**********************************************************************/

#define CHRG_COMP_REG1			0x99
#define CHRG_COMP_REG2			0x9A
#define SUP_STS_REG			0xA0
#define USB_CTRL_REG			0xA1
#define CHRG_CTRL_REG1			0xA3
#define CHRG_CTRL_REG2			0xA4
#define CHRG_CTRL_REG3			0xA5
#define BAT_CTRL_REG			0xA6
#define BAT_HTS_TS1_REG			0xA8
#define BAT_LTS_TS1_REG			0xA9
#define BAT_HTS_TS2_REG			0xAA
#define BAT_LTS_TS2_REG			0xAB


#define TS_CTRL_REG			0xAC
#define ADC_CTRL_REG			0xAD

#define ON_SOURCE			0xAE
#define OFF_SOURCE			0xAF

#define GGCON				0xB0
#define GGSTS				0xB1
#define FRAME_SMP_INTERV_REG		0xB2
#define AUTO_SLP_CUR_THR_REG		0xB3

#define GASCNT_CAL_REG3			0xB4
#define GASCNT_CAL_REG2			0xB5
#define GASCNT_CAL_REG1			0xB6
#define GASCNT_CAL_REG0			0xB7
#define GASCNT3				0xB8
#define GASCNT2				0xB9
#define GASCNT1				0xBA
#define GASCNT0				0xBB

#define BAT_CUR_AVG_REGH		0xBC
#define BAT_CUR_AVG_REGL		0xBD

#define TS1_ADC_REGH			0xBE
#define TS1_ADC_REGL			0xBF
#define TS2_ADC_REGH			0xC0
#define TS2_ADC_REGL			0xC1

#define BAT_OCV_REGH			0xC2
#define BAT_OCV_REGL			0xC3
#define BAT_VOL_REGH			0xC4
#define BAT_VOL_REGL			0xC5

#define RELAX_ENTRY_THRES_REGH		0xC6
#define RELAX_ENTRY_THRES_REGL		0xC7
#define RELAX_EXIT_THRES_REGH		0xC8
#define RELAX_EXIT_THRES_REGL		0xC9

#define RELAX_VOL1_REGH			0xCA
#define RELAX_VOL1_REGL			0xCB
#define RELAX_VOL2_REGH			0xCC
#define RELAX_VOL2_REGL			0xCD

#define BAT_CUR_R_CALC_REGH		0xCE
#define BAT_CUR_R_CALC_REGL		0xCF
#define BAT_VOL_R_CALC_REGH		0xD0
#define BAT_VOL_R_CALC_REGL		0xD1

#define CAL_OFFSET_REGH			0xD2
#define CAL_OFFSET_REGL			0xD3

#define NON_ACT_TIMER_CNT_REG		0xD4

#define VCALIB0_REGH			0xD5
#define VCALIB0_REGL			0xD6
#define VCALIB1_REGH			0xD7
#define VCALIB1_REGL			0xD8

#define IOFFSET_REGH			0xDD
#define IOFFSET_REGL			0xDE
/*0xE0 ~0xF2  data register,*/
#define SOC_REG				0xE0
#define REMAIN_CAP_REG3			0xE1
#define REMAIN_CAP_REG2			0xE2
#define REMAIN_CAP_REG1			0xE3
#define REMAIN_CAP_REG0			0xE4

#define UPDAT_LEVE_REG			0xE5

#define NEW_FCC_REG3			0xE6
#define NEW_FCC_REG2			0xE7
#define NEW_FCC_REG1			0xE8
#define NEW_FCC_REG0			0xE9

#define NON_ACT_TIMER_CNT_REG_SAVE 	0xEA
#define CV_VOL_VALID_REG		0xEB
#define REBOOT_CNT_REG			0xEC
#define PCB_IOFFSET_REG			0xED
#define MISC_MARK_REG			0xEE

struct pmic_rk818 {
	struct pmic *pmic;
	int node;	/*device tree node*/
};

#endif
