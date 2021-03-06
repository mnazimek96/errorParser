/* 
 * errors_list.h
 *
 *
 * generated on: 04/11/2020 07:30:15
 * Author: mikey
 */

#ifndef ERRORS_LIST_H_
#define ERRORS_LIST_H_

typedef struct {
	uint8_t bitfield:4;          /* bitfield in 16-bit register */
	uint8_t seriousness:2;
	uint16_t code:12;            /* range up to 4095 */
	volatile uint16_t * reg;     /* reg to store error (if active or not) */
	volatile uint16_t * mem_reg; /* reg to indicate if error has already been put into memory */
	uint8_t not_functional:1;    /* result: gf not functional */
	uint8_t safe_state:1;        /* result: SAFE STATE */
	uint8_t need_lck_out:1;      /* result: Gap Filler need to be switched to lock-out urgently */
} error_t;

static const error_t errors[ERROR_NO] = {
	ERROR_CFG_FAULTS_0_DEPL_DEFAULT                      ,
	ERROR_CFG_FAULTS_0_RETR_DEFAULT                      ,
	ERROR_CFG_FAULTS_0_MOTOR_SUPPLY                      ,
	ERROR_CFG_FAULTS_0_MOTOR_OR_STEP                     ,
	ERROR_CFG_FAULTS_0_MOT_OPEN_CIR                      ,
	ERROR_CFG_FAULTS_0_FRICTION                          ,
	ERROR_CFG_FAULTS_0_OC_RETR                           ,
	ERROR_CFG_FAULTS_0_OC_DEPL                           ,
	ERROR_CFG_FAULTS_0_ENCODER                           ,
	ERROR_CFG_FAULTS_0_ENC_PLS_NEQ                       ,
	ERROR_CFG_FAULTS_0_ENC_PLS_LOST                      ,
	ERROR_CFG_FAULTS_0_ENC_POLARITY                      ,
	ERROR_CFG_FAULTS_0_INSTALLATION                      ,
	ERROR_CFG_FAULTS_0_DC_REL_LV_SIG                     ,
	ERROR_CFG_FAULTS_0_DC_REL_MOT_SPLY                   ,
	ERROR_CFG_FAULTS_0_REL_ZERO_VEL                      ,
	ERROR_CFG_FAULTS_1_REL_OP_AUTH                       ,
	ERROR_CFG_FAULTS_1_SIG_CONFLICT_DEPL_OR_RETRLCK      ,
	ERROR_CFG_FAULTS_1_SIG_CONFLICT_DEPL_OR_CLOS         ,
	ERROR_CFG_FAULTS_1_SIG_CONFLICT_DEPL_OR_LCK_OUT      ,
	ERROR_CFG_FAULTS_1_SIG_CONFLICT_OPEN_OR_RETRLCK      ,
	ERROR_CFG_FAULTS_1_SIG_CONFLICT_OPEN_OR_CLOS         ,
	ERROR_CFG_FAULTS_1_SIG_CONFLICT_OPEN_OR_LCK_OUT      ,
	ERROR_CFG_FAULTS_1_SIG_CONFLICT_OPEN_OR_MOT_SPLY     ,
	ERROR_CFG_FAULTS_1_SIG_CONFLICT_OPEN_OR_PLATE        ,
	ERROR_CFG_FAULTS_1_CLUTCH                            ,
	ERROR_CFG_FAULTS_1_SIG_CONFLICT_LCK_OUT              ,
	ERROR_CFG_FAULTS_1_SIG_CONFLICT_RETRLCK              ,
	ERROR_CFG_FAULTS_1_CLOS_SAFETY                       ,
	ERROR_CFG_FAULTS_1_LCK_OUT_NEQ                       ,
	ERROR_CFG_FAULTS_1_CLOS_NEQ                          ,
	ERROR_CFG_FAULTS_1_CLUTCH_NEQ                        ,
	ERROR_CFG_FAULTS_2_CLUTCH_SAFETY                     ,
	ERROR_CFG_FAULTS_2_DEPL_SENS                         ,
	ERROR_CFG_FAULTS_2_SCU                               ,
	ERROR_CFG_FAULTS_2_SELFTEST                          ,
	ERROR_CFG_FAULTS_2_COMMUNICATION                     ,
	ERROR_CFG_FAULTS_2_MEMORY                            ,
	ERROR_CFG_FAULTS_2_INT_MOT_CTRL                      ,
	ERROR_CFG_FAULTS_2_INT_CURR_SENS                     ,
	ERROR_CFG_FAULTS_2_IO                                ,
	ERROR_CFG_FAULTS_2_TCMS                              ,
	ERROR_CFG_FAULTS_2_INT_MOT_HEAT                      ,
	ERROR_CFG_WARNINGS_0_ENC_PLS_NEQ                     ,
	ERROR_CFG_WARNINGS_0_ENC_PLS_LOSS                    ,
	ERROR_CFG_WARNINGS_0_ENC_PLS_FALSE                   ,
	ERROR_CFG_WARNINGS_0_FRICTION                        ,
	ERROR_CFG_WARNINGS_0_DEPL_TIME                       ,
	ERROR_CFG_WARNINGS_0_RETR_TIME                       ,
	ERROR_CFG_WARNINGS_0_TEMP                            ,
	ERROR_CFG_INFO_0_DEPL_OBSTR                          ,
	ERROR_CFG_INFO_0_RETR_OBSTR                          ,
	ERROR_CFG_INFO_0_GO_TO_LCK                           ,
	ERROR_CFG_INFO_0_IN_LCK_OUT                          ,
	ERROR_CFG_ALARMS_0_DEPL_OBSTR                        ,
	ERROR_CFG_ALARMS_0_RETR_OBSTR                        ,
	ERROR_CFG_ALARMS_0_GO_TO_LCK                         ,
};

#else
#error This file must be included only once
#endif /* ERRORS_LIST_H_ */