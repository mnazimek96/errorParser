/* 
 * errors_list.h
 *
 *
 * generated on: 29/10/2020 14:49:51
 * Author: mikey
 */

#ifndef ERRORS_LIST_H_
#define ERRORS_LIST_H_

typedef struct {
	uint8_t id;	/* == array index */
	uint8_t bitfield;	/* range up to 15, as registers are 16 bit */
	uint8_t type:2;
	uint8_t seriousness:2;
	uint16_t code:12;	/* range up to 4095 */
	volatile uint16_t * reg;	/* reg to store error (if active or not) */
	volatile uint16_t * mem_reg;	/* reg to indicate if error has already been put into memory */
} error_t;

static const error_t errors[ERROR_NO] = {
	{FAULTS_0_DEPL_DEFAULT,                   0,  1,  0,  10,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_RETR_DEFAULT,                   1,  1,  0,  11,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_MOTOR_SUPPLY,                   2,  1,  0,  20,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_MOTOR_OR_STEP,                  3,  1,  0,  21,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_MOT_OPEN_CIR,                   4,  1,  0,  22,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_FRICTION,                       5,  1,  0,  23,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_OC_RETR,                        6,  1,  0,  24,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_OC_DEPL,                        7,  1,  0,  25,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_ENCODER,                        8,  1,  0,  31,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_ENC_PLS_NEQ,                    9,  1,  0,  32,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_ENC_PLS_LOST,                   10, 1,  0,  33,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_ENC_POLARITY,                   11, 1,  2,  34,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_INSTALLATION,                   12, 1,  2,  35,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_DC_REL_LV_SIG,                  13, 1,  0,  40,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_DC_REL_MOT_SPLY,                14, 1,  0,  41,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_0_REL_ZERO_VEL,                   15, 1,  0,  42,  &error_regs.faults0,   &error_eeprom_regs.faults0,      },
	{FAULTS_1_REL_OP_AUTH,                    0,  1,  0,  43,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_SIG_CONFLICT_DEPL_OR_RETRLCK,   1,  1,  0,  50,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_SIG_CONFLICT_DEPL_OR_CLOS,      2,  1,  0,  51,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_SIG_CONFLICT_DEPL_OR_LCK_OUT,   3,  1,  0,  52,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_SIG_CONFLICT_OPEN_OR_RETRLCK,   4,  1,  0,  53,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_SIG_CONFLICT_OPEN_OR_CLOS,      5,  1,  0,  54,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_SIG_CONFLICT_OPEN_OR_LCK_OUT,   6,  1,  0,  55,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_SIG_CONFLICT_OPEN_OR_MOT_SPLY,  7,  1,  0,  56,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_SIG_CONFLICT_OPEN_OR_PLATE,     8,  1,  0,  57,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_CLUTCH,                         9,  1,  0,  58,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_SIG_CONFLICT_LCK_OUT,           10, 1,  0,  59,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_SIG_CONFLICT_RETRLCK,           11, 1,  0,  60,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_CLOS_SAFETY,                    12, 1,  0,  61,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_LCK_OUT_NEQ,                    13, 1,  0,  62,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_CLOS_NEQ,                       14, 1,  0,  63,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_1_CLUTCH_NEQ,                     15, 1,  0,  64,  &error_regs.faults1,   &error_eeprom_regs.faults1,      },
	{FAULTS_2_CLUTCH_SAFETY,                  0,  1,  0,  65,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{FAULTS_2_DEPL_SENS,                      1,  1,  0,  66,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{FAULTS_2_SCU,                            2,  1,  0,  80,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{FAULTS_2_SELFTEST,                       3,  1,  0,  81,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{FAULTS_2_COMMUNICATION,                  4,  1,  0,  82,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{FAULTS_2_MEMORY,                         5,  1,  0,  83,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{FAULTS_2_INT_MOT_CTRL,                   6,  1,  0,  84,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{FAULTS_2_INT_CURR_SENS,                  7,  1,  0,  85,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{FAULTS_2_IO,                             8,  1,  0,  86,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{FAULTS_2_TCMS,                           9,  1,  0,  87,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{FAULTS_2_INT_MOT_HEAT,                   10, 1,  2,  88,  &error_regs.faults2,   &error_eeprom_regs.faults2,      },
	{WARNINGS_0_ENC_PLS_NEQ,                  0,  0,  3,  200, &error_regs.warnings0, &error_eeprom_regs.warnings0,    },
	{WARNINGS_0_ENC_PLS_LOSS,                 1,  0,  3,  201, &error_regs.warnings0, &error_eeprom_regs.warnings0,    },
	{WARNINGS_0_ENC_PLS_FALSE,                2,  0,  3,  202, &error_regs.warnings0, &error_eeprom_regs.warnings0,    },
	{WARNINGS_0_FRICTION,                     3,  0,  3,  203, &error_regs.warnings0, &error_eeprom_regs.warnings0,    },
	{WARNINGS_0_DEPL_TIME,                    4,  0,  3,  204, &error_regs.warnings0, &error_eeprom_regs.warnings0,    },
	{WARNINGS_0_RETR_TIME,                    5,  0,  3,  205, &error_regs.warnings0, &error_eeprom_regs.warnings0,    },
	{WARNINGS_0_TEMP,                         6,  0,  3,  206, &error_regs.warnings0, &error_eeprom_regs.warnings0,    },
	{INFO_0_DEPL_OBSTR,                       0,  3,  2,  401, &error_regs.infos0,    &error_eeprom_regs.infos0,       },
	{INFO_0_RETR_OBSTR,                       1,  3,  2,  402, &error_regs.infos0,    &error_eeprom_regs.infos0,       },
	{INFO_0_GO_TO_LCK,                        2,  3,  0,  403, &error_regs.infos0,    &error_eeprom_regs.infos0,       },
	{INFO_0_IN_LCK_OUT,                       3,  3,  2,  404, &error_regs.infos0,    &error_eeprom_regs.infos0,       },
	{ALARMS_0_DEPL_OBSTR,                     0,  2,  2,  600, &error_regs.alarms0,   &error_eeprom_regs.alarms0,      },
	{ALARMS_0_RETR_OBSTR,                     1,  2,  2,  601, &error_regs.alarms0,   &error_eeprom_regs.alarms0,      },
	{ALARMS_0_GO_TO_LCK,                      2,  2,  0,  601, &error_regs.alarms0,   &error_eeprom_regs.alarms0,      },
};

#else
#error This file must be included only once
#endif /* ERRORS_LIST_H_ */