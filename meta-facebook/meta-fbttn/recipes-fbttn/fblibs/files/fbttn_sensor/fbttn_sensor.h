/*
 *
 * Copyright 2015-present Facebook. All Rights Reserved.
 *
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
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __FBTTN_SENSOR_H__
#define __FBTTN_SENSOR_H__

#include <stdbool.h>
#include <openbmc/ipmi.h>
#include <openbmc/ipmb.h>
#include <facebook/bic.h>
#include <facebook/fbttn_common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SDR_LEN           64
#define MAX_SENSOR_NUM        0xFF
#define MAX_SENSOR_THRESHOLD  8
#define MAX_RETRIES_SDR_INIT  30
#define THERMAL_CONSTANT      255
#define ERR_NOT_READY         -2

typedef struct _sensor_info_t {
  bool valid;
  sdr_full_t sdr;
} sensor_info_t;

/* Enum for type of Upper and Lower threshold values */
enum {
  SENSOR_VALID = 0x0,
  UCR_THRESH = 0x01,
  UNC_THRESH,
  UNR_THRESH,
  LCR_THRESH,
  LNC_THRESH,
  LNR_THRESH,
  POS_HYST,
  NEG_HYST,
};

// Sensors under Bridge IC
enum {
  BIC_SENSOR_MB_OUTLET_TEMP = 0x01,
  BIC_SENSOR_VCCIN_VR_TEMP = 0x02,
  BIC_SENSOR_VCC_GBE_VR_TEMP = 0x03,
  BIC_SENSOR_1V05PCH_VR_TEMP = 0x04,
  BIC_SENSOR_SOC_TEMP = 0x05,
  BIC_SENSOR_MB_INLET_TEMP = 0x07,
  BIC_SENSOR_PCH_TEMP = 0x08,
  BIC_SENSOR_SOC_THERM_MARGIN = 0x09,
  BIC_SENSOR_VDDR_VR_TEMP = 0x0B,
  BIC_SENSOR_SYSTEM_STATUS = 0x10, //Discrete
  BIC_SENSOR_SPS_FW_HLTH = 0x17, //Event-only
  BIC_SENSOR_VCC_GBE_VR_CURR = 0x20,
  BIC_SENSOR_1V05_PCH_VR_CURR = 0x21,
  BIC_SENSOR_VCCIN_VR_POUT = 0x22,
  BIC_SENSOR_VCCIN_VR_CURR = 0x23,
  BIC_SENSOR_VCCIN_VR_VOL = 0x24,
  BIC_SENSOR_INA230_POWER = 0x29,
  BIC_SENSOR_INA230_VOL = 0x2A,
  BIC_SENSOR_POST_ERR = 0x2B, //Event-only
  BIC_SENSOR_SOC_PACKAGE_PWR = 0x2C,
  BIC_SENSOR_SOC_TJMAX = 0x30,
  BIC_SENSOR_VDDR_VR_POUT = 0x32,
  BIC_SENSOR_VDDR_VR_CURR = 0x33,
  BIC_SENSOR_VDDR_VR_VOL = 0x34,
  BIC_SENSOR_VCC_SCSUS_VR_CURR = 0x35,
  BIC_SENSOR_VCC_SCSUS_VR_VOL = 0x36,
  BIC_SENSOR_VCC_SCSUS_VR_TEMP = 0x37,
  BIC_SENSOR_VCC_SCSUS_VR_POUT = 0x38,
  BIC_SENSOR_VCC_GBE_VR_POUT = 0x39,
  BIC_SENSOR_POWER_THRESH_EVENT = 0x3B, //Event-only
  BIC_SENSOR_MACHINE_CHK_ERR = 0x40, //Event-only
  BIC_SENSOR_PCIE_ERR = 0x41, //Event-only
  BIC_SENSOR_1V05_PCH_VR_POUT = 0x42,
  BIC_SENSOR_OTHER_IIO_ERR = 0x43, //Event-only
  BIC_SENSOR_PROC_HOT_EXT = 0x51, //Event-only
  BIC_SENSOR_VCC_GBE_VR_VOL = 0x54,
  BIC_SENSOR_1V05_PCH_VR_VOL = 0x55,
  BIC_SENSOR_POWER_ERR = 0x56, //Event-only
  BIC_SENSOR_MEM_ECC_ERR = 0x63, //Event-only
  BIC_SENSOR_PROC_FAIL = 0x65, //Discrete
  BIC_SENSOR_SYS_BOOT_STAT = 0x7E, //Discrete
  BIC_SENSOR_VR_HOT = 0xB2, //Discrete
  BIC_SENSOR_CPU_DIMM_HOT = 0xB3, //Discrete
  BIC_SENSOR_SOC_DIMMA0_TEMP = 0xB4,
  BIC_SENSOR_SOC_DIMMA1_TEMP = 0xB5,
  BIC_SENSOR_SOC_DIMMB0_TEMP = 0xB6,
  BIC_SENSOR_SOC_DIMMB1_TEMP = 0xB7,
  BIC_SENSOR_P3V3_MB = 0xD0,
  BIC_SENSOR_P12V_MB = 0xD2,
  BIC_SENSOR_P1V05_PCH = 0xD3,
  BIC_SENSOR_P3V3_STBY_MB = 0xD5,
  BIC_SENSOR_P5V_STBY_MB = 0xD6,
  BIC_SENSOR_PV_BAT = 0xD7,
  BIC_SENSOR_PVDDR = 0xD8,
  BIC_SENSOR_PVCC_GBE = 0xD9,
  BIC_SENSOR_CAT_ERR = 0xEB, //Event-only
};

enum{
  IOM_SENSOR_INTEL_TEMP = 0x81,
  IOM_SENSOR_HSC_POWER = 0x83,
  IOM_SENSOR_HSC_VOLT = 0x84,
  IOM_SENSOR_HSC_CURR = 0x85,
  IOM_SENSOR_M2_1_TEMP = 0x86,
  IOM_SENSOR_M2_2_TEMP = 0x87,
  IOM_SENSOR_ADC_12V = 0x88,
  IOM_SENSOR_ADC_P5V_STBY = 0x89,
  IOM_SENSOR_ADC_P3V3_STBY = 0x8A,
  IOM_SENSOR_ADC_P1V8_STBY = 0x8B,
  IOM_SENSOR_ADC_P2V5_STBY = 0x8C,
  IOM_SENSOR_ADC_P1V2_STBY = 0x8D,
  IOM_SENSOR_ADC_P1V15_STBY = 0X8E,
  IOM_SENSOR_ADC_P3V3 = 0x8F,
  IOM_SENSOR_ADC_P1V8 = 0x90,
  IOM_SENSOR_ADC_P1V5 = 0x91,
  IOM_SENSOR_ADC_P0V975 = 0x92,
  IOM_SENSOR_ADC_P3V3_M2 = 0x93,
};

enum{
  DPB_SENSOR_12V_POWER_CLIP = 0x94,
  DPB_SENSOR_P12V_CLIP = 0x95,
  DPB_SENSOR_12V_CURR_CLIP = 0x96,
  DPB_SENSOR_FAN0_FRONT = 0x97,
  DPB_SENSOR_FAN1_FRONT = 0x98,
  DPB_SENSOR_FAN2_FRONT = 0x99,
  DPB_SENSOR_FAN3_FRONT = 0x9A,
  DPB_SENSOR_FAN0_REAR = 0x9B,
  DPB_SENSOR_FAN1_REAR = 0x9C,
  DPB_SENSOR_FAN2_REAR = 0x9D,
  DPB_SENSOR_FAN3_REAR = 0x9E,
  DPB_SENSOR_FAN_STATUS = 0x0A, //Discrete
};

enum{
  MEZZ_SENSOR_TEMP = 0x82,
};
extern const uint8_t bic_sensor_list[];

extern const uint8_t bic_discrete_list[];

extern const uint8_t iom_sensor_list[];

extern const uint8_t dpb_sensor_list[];

extern const uint8_t dpb_discrete_list[];

extern const uint8_t nic_sensor_list[];

//extern float nic_sensor_threshold[MAX_SENSOR_NUM][MAX_SENSOR_THRESHOLD + 1];

extern size_t bic_sensor_cnt;

extern size_t bic_discrete_cnt;

extern size_t iom_sensor_cnt;

extern size_t dpb_sensor_cnt;

extern size_t dpb_discrete_cnt;

extern size_t nic_sensor_cnt;

int fbttn_sensor_read(uint8_t fru, uint8_t sensor_num, void *value);
int fbttn_sensor_name(uint8_t fru, uint8_t sensor_num, char *name);
int fbttn_sensor_units(uint8_t fru, uint8_t sensor_num, char *units);
int fbttn_sensor_sdr_path(uint8_t fru, char *path);
int fbttn_sensor_threshold(uint8_t fru, uint8_t sensor_num, uint8_t thresh, float *value);
int fbttn_sensor_sdr_init(uint8_t fru, sensor_info_t *sinfo);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __FBTTN_SENSOR_H__ */
