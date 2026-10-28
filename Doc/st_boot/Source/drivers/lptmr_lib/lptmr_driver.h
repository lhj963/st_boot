/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * NXP Confidential. This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */

#ifndef LPTMR_DRIVER_H
#define LPTMR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
//#include "status.h"
#include "device_registers.h"
/*! @file lptmr_driver.h*/

/*!
 * @addtogroup lptmr_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Pulse Counter Input selection
 *  Implements : lptmr_pinselect_t_Class
 */
typedef enum {
    LPTMR_PINSELECT_TRGMUX  = 0x00u, /*!< Count pulses from TRGMUX trigger */
#if FEATURE_LPTMR_HAS_INPUT_ALT1_SELECTION
    LPTMR_PINSELECT_ALT1    = 0x01u, /*!< Count pulses from pin alternative 1 */
#endif
    LPTMR_PINSELECT_ALT2    = 0x02u, /*!< Count pulses from pin alternative 2 */
    LPTMR_PINSELECT_ALT3    = 0x03u  /*!< Count pulses from pin alternative 3 */
} lptmr_pinselect_t;

/*! @brief Pulse Counter input polarity
 *  Implements : lptmr_pinpolarity_t_Class
 */
typedef enum {
    LPTMR_PINPOLARITY_RISING    = 0u, /*!< Count pulse on rising edge */
    LPTMR_PINPOLARITY_FALLING   = 1u  /*!< Count pulse on falling edge */
} lptmr_pinpolarity_t;

/*! @brief Work Mode
 *  Implements : lptmr_workmode_t_Class
 */
typedef enum {
    LPTMR_WORKMODE_TIMER        = 0u, /*!< Timer */
    LPTMR_WORKMODE_PULSECOUNTER = 1u  /*!< Pulse counter */
} lptmr_workmode_t;

/*! @brief Prescaler Selection
 *  Implements : lptmr_prescaler_t_Class
 */
typedef enum {
    LPTMR_PRESCALE_2                        = 0x00u, /*!< Timer mode: prescaler 2, Glitch filter mode: invalid */
    LPTMR_PRESCALE_4_GLITCHFILTER_2         = 0x01u, /*!< Timer mode: prescaler 4, Glitch filter mode: 2 clocks */
    LPTMR_PRESCALE_8_GLITCHFILTER_4         = 0x02u, /*!< Timer mode: prescaler 8, Glitch filter mode: 4 clocks */
    LPTMR_PRESCALE_16_GLITCHFILTER_8        = 0x03u, /*!< Timer mode: prescaler 16, Glitch filter mode: 8 clocks */
    LPTMR_PRESCALE_32_GLITCHFILTER_16       = 0x04u, /*!< Timer mode: prescaler 32, Glitch filter mode: 16 clocks */
    LPTMR_PRESCALE_64_GLITCHFILTER_32       = 0x05u, /*!< Timer mode: prescaler 64, Glitch filter mode: 32 clocks */
    LPTMR_PRESCALE_128_GLITCHFILTER_64      = 0x06u, /*!< Timer mode: prescaler 128, Glitch filter mode: 64 clocks */
    LPTMR_PRESCALE_256_GLITCHFILTER_128     = 0x07u, /*!< Timer mode: prescaler 256, Glitch filter mode: 128 clocks */
    LPTMR_PRESCALE_512_GLITCHFILTER_256     = 0x08u, /*!< Timer mode: prescaler 512, Glitch filter mode: 256 clocks */
    LPTMR_PRESCALE_1024_GLITCHFILTER_512    = 0x09u, /*!< Timer mode: prescaler 1024, Glitch filter mode: 512 clocks */
    LPTMR_PRESCALE_2048_GLITCHFILTER_1024   = 0x0Au, /*!< Timer mode: prescaler 2048, Glitch filter mode: 1024 clocks */
    LPTMR_PRESCALE_4096_GLITCHFILTER_2048   = 0x0Bu, /*!< Timer mode: prescaler 4096, Glitch filter mode: 2048 clocks */
    LPTMR_PRESCALE_8192_GLITCHFILTER_4096   = 0x0Cu, /*!< Timer mode: prescaler 8192, Glitch filter mode: 4096 clocks */
    LPTMR_PRESCALE_16384_GLITCHFILTER_8192  = 0x0Du, /*!< Timer mode: prescaler 16384, Glitch filter mode: 8192 clocks */
    LPTMR_PRESCALE_32768_GLITCHFILTER_16384 = 0x0Eu, /*!< Timer mode: prescaler 32768, Glitch filter mode: 16384 clocks */
    LPTMR_PRESCALE_65536_GLITCHFILTER_32768 = 0x0Fu  /*!< Timer mode: prescaler 65536, Glitch filter mode: 32768 clocks */
} lptmr_prescaler_t;

/*! @brief Clock Source selection
 *  Implements : lptmr_clocksource_t_Class
 */
typedef enum {
    LPTMR_CLOCKSOURCE_SIRCDIV2  = 0x00u, /*!< SIRC clock */
    LPTMR_CLOCKSOURCE_1KHZ_LPO  = 0x01u, /*!< 1kHz LPO clock */
    LPTMR_CLOCKSOURCE_RTC       = 0x02u, /*!< RTC clock */
    LPTMR_CLOCKSOURCE_PCC       = 0x03u  /*!< PCC configured clock */
} lptmr_clocksource_t;

/*!
 * @brief Defines the LPTMR counter units available for configuring or reading the timer compare value.
 *
 * Implements : lptmr_counter_units_t_Class
 */
typedef enum
{
    LPTMR_COUNTER_UNITS_TICKS           = 0x00U,
    LPTMR_COUNTER_UNITS_MICROSECONDS    = 0x01U
} lptmr_counter_units_t;

/*!
 * @brief Defines the configuration structure for LPTMR.
 *
 * Implements : lptmr_config_t_Class
 */
typedef struct
{
    /* General parameters */
    bool dmaRequest;                    /*!< Enable/Disable DMA requests */
    bool interruptEnable;               /*!< Enable/Disable Interrupt */
    bool freeRun;                       /*!< Enable/Disable Free Running Mode */
    lptmr_workmode_t workMode;          /*!< Time/Pulse Counter Mode */
    /* Counter parameters */
    lptmr_clocksource_t clockSelect;    /*!< Clock selection for Timer/Glitch filter */
    lptmr_prescaler_t prescaler;        /*!< Prescaler Selection */
    bool bypassPrescaler;               /*!< Enable/Disable prescaler bypass */
    uint32_t compareValue;              /*!< Compare value */
    lptmr_counter_units_t counterUnits; /*!< Compare value units */
    /* Pulse Counter specific parameters */
    lptmr_pinselect_t pinSelect;        /*!< Pin selection for Pulse-Counter */
    lptmr_pinpolarity_t pinPolarity;    /*!< Pin Polarity for Pulse-Counter */
} lptmr_config_t;

typedef enum
{
    /* Generic error codes */
    STATUS_SUCCESS                         = 0x000U,    /*!< Generic operation success status */
    STATUS_ERROR                           = 0x001U,    /*!< Generic operation failure status */
    STATUS_BUSY                            = 0x002U,    /*!< Generic operation busy status */
    STATUS_TIMEOUT                         = 0x003U,    /*!< Generic operation timeout status */
    STATUS_UNSUPPORTED                     = 0x004U,    /*!< Generic operation unsupported status */
    /* MCU specific error codes */
    STATUS_MCU_GATED_OFF                   = 0x100U,  /*!< Module is gated off */
    STATUS_MCU_TRANSITION_FAILED           = 0x101U,  /*!< Error occurs during transition. */
    STATUS_MCU_INVALID_STATE               = 0x102U,  /*!< Unsupported in current state. */
    STATUS_MCU_NOTIFY_BEFORE_ERROR         = 0x103U,  /*!< Error occurs during send "BEFORE" notification. */
    STATUS_MCU_NOTIFY_AFTER_ERROR          = 0x104U,  /*!< Error occurs during send "AFTER" notification. */
    /* I2C specific error codes */
    STATUS_I2C_RECEIVED_NACK               = 0x200U,  /*!< NACK signal received  */
    STATUS_I2C_TX_UNDERRUN                 = 0x201U,  /*!< TX underrun error */
    STATUS_I2C_RX_OVERRUN                  = 0x202U,  /*!< RX overrun error */
    STATUS_I2C_ARBITRATION_LOST            = 0x203U,  /*!< Arbitration lost */
    STATUS_I2C_ABORTED                     = 0x204U,  /*!< A transfer was aborted */
    STATUS_I2C_BUS_BUSY                    = 0x205U,  /*!< I2C bus is busy, cannot start transfer */
    /* CAN specific error codes */
    STATUS_CAN_BUFF_OUT_OF_RANGE           = 0x300U,  /*!< The specified MB index is out of the configurable range */
    STATUS_CAN_NO_TRANSFER_IN_PROGRESS     = 0x301U,  /*!< There is no transmission or reception in progress */
    /* Security specific error codes */
    STATUS_SEC_SEQUENCE_ERROR              = 0x402U,  /*!< The sequence of commands or subcommands is out of
                                                            sequence */
    STATUS_SEC_KEY_NOT_AVAILABLE           = 0x403U,  /*!< A key is locked due to failed boot measurement or
                                                            an active debugger */
    STATUS_SEC_KEY_INVALID                 = 0x404U,  /*!< A function is called to perform an operation with
                                                            a key that is not allowed for the given operation */
    STATUS_SEC_KEY_EMPTY                   = 0x405U,  /*!< Attempt to use a key that has not been initialized yet */
    STATUS_SEC_NO_SECURE_BOOT              = 0x406U,  /*!< The conditions for a secure boot process are not met */
    STATUS_SEC_KEY_WRITE_PROTECTED         = 0x407U,  /*!< Request for updating a write protected key slot,
                                                            or activating debugger with write protected key(s) */
    STATUS_SEC_KEY_UPDATE_ERROR            = 0x408U,  /*!< Key update did not succeed due to errors in
                                                            verification of the messages */
    STATUS_SEC_RNG_SEED                    = 0x409U,  /*!< Returned by CMD_RND and CMD_DEBUG if the seed has not
                                                            been initialized before */
    STATUS_SEC_NO_DEBUGGING                = 0x40AU,  /*!< DEBUG command authentication failed */
    STATUS_SEC_MEMORY_FAILURE              = 0x40CU,  /*!< General memory technology failure
                                                            (multibit ECC error, common fault detected) */
    STATUS_SEC_HSM_INTERNAL_MEMORY_ERROR   = 0x410U,  /*!< An internal memory error encountered while
                                                           executing the command */
    STATUS_SEC_INVALID_COMMAND             = 0x411U,  /*!< Command value out of range */
    STATUS_SEC_TRNG_ERROR                  = 0x412U,  /*!< One or more statistical tests run on the TRNG output failed */
    STATUS_SEC_HSM_FLASH_BLOCK_ERROR       = 0x413U,  /*!< Error reading, programming or erasing one of the HSM flash blocks */
    STATUS_SEC_INTERNAL_CMD_ERROR          = 0x414U,  /*!< An internal command processor error while executing a command */
    STATUS_SEC_MAC_LENGTH_ERROR            = 0x415U,  /*!< MAC/Message length out of range */
    STATUS_SEC_INVALID_ARG                 = 0x421U,  /*!< Invalid command argument */
    STATUS_SEC_TRNG_CLOCK_ERROR            = 0x423U,  /*!< TRNG not provided with a stable clock */
    /* SPI specific error codes */
    STATUS_SPI_TX_UNDERRUN                 = 0x500U,  /*!< TX underrun error */
    STATUS_SPI_RX_OVERRUN                  = 0x501U,  /*!< RX overrun error */
    STATUS_SPI_ABORTED                     = 0x502U,  /*!< A transfer was aborted */
    /* UART specific error codes */
    STATUS_UART_TX_UNDERRUN                = 0x600U,  /*!< TX underrun error */
    STATUS_UART_RX_OVERRUN                 = 0x601U,  /*!< RX overrun error */
    STATUS_UART_ABORTED                    = 0x602U,  /*!< A transfer was aborted */
	STATUS_UART_FRAMING_ERROR              = 0x603U,  /*!< Framing error */
	STATUS_UART_PARITY_ERROR               = 0x604U,  /*!< Parity error */
	STATUS_UART_NOISE_ERROR                = 0x605U,  /*!< Noise error */
    /* I2S specific error codes */
    STATUS_I2S_TX_UNDERRUN                 = 0x700U,  /*!< TX underrun error */
    STATUS_I2S_RX_OVERRUN                  = 0x701U,  /*!< RX overrun error */
    STATUS_I2S_ABORTED                     = 0x702U,  /*!< A transfer was aborted */
    /* SBC specific error codes */
    SBC_NVN_ERROR                          = 0x801U, /*!< Unsuccessful attempt writing to non volatile memory
                                                          (0x73 and 0x74). Set device to factory settings. */
    SBC_COMM_ERROR                         = 0x802U, /*!< Data transfer was aborted */
    SBC_CMD_ERROR                          = 0x804U, /*!< Wrong command. */
    SBC_ERR_NA                             = 0x808U, /*!< Feature/device not available */
    SBC_MTPNV_LOCKED                       = 0x810U, /*!< Unable to write MTPNV cells, NVMPS = 0 */

    /* FLASH specific error codes */
    STATUS_FLASH_ERROR_ENABLE              = 0x901U, /*!< It's impossible to enable an operation */
    STATUS_FLASH_ERROR_NO_BLOCK            = 0x902U, /*!< No blocks have been enabled for Array Integrity check */
    STATUS_FLASH_INPROGRESS                = 0x903U, /*!< InProgress status */

    /* SAI specific error codes */
    STATUS_SAI_ABORTED                     = 0xA00U, /*!< SAI aborted status */

    /* ENET specific error codes */
    STATUS_ENET_RX_QUEUE_EMPTY             = 0xA01U, /*!< There is no available frame in the receive queue */
    STATUS_ENET_TX_QUEUE_FULL              = 0xA02U, /*!< There is no available space for the frame in the transmit queue */
    STATUS_ENET_BUFF_NOT_FOUND             = 0xA03U, /*!< The specified buffer was not found in the queue */

    /* FCCU specific error codes */
    STATUS_FCCU_ERROR_CONFIG_TIMEOUT       = 0xB01U, /*!< FCCU triggers TimeOut when try to enter in Config State */
    STATUS_FCCU_ERROR_INIT_FCCU            = 0xB02U, /*!< FCCU Initializing FCCU Module */
    STATUS_FCCU_ERROR_SET_CONFIG           = 0xB03U, /*!< FCCU Fail to Enter in Config Mode  */
    STATUS_FCCU_ERROR_SET_NORMAL           = 0xB04U, /*!< FCCU Fail to Enter in Normal Mode  */
    STATUS_FCCU_ERROR_APPLY_NCF_CONFIG     = 0xB05U, /*!< FCCU Fail to set NoCritical Faults  */
    STATUS_FCCU_ERROR_UPDATE_FREEZE        = 0xB06U, /*!< FCCU Fail to update Freez Status registers */
    STATUS_FCCU_ERROR_CLEAR_FREEZE         = 0xB07U, /*!< FCCU Fail to Clear Freez Status registers */
    STATUS_FCCU_ERROR_SET_EOUT             = 0xB08U, /*!< FCCU Fail to Set Eout Configuration */
    STATUS_FCCU_ERROR_FAULT_DETECTED       = 0xB09U, /*!< FCCU Faults Detected */
    STATUS_FCCU_ERROR_OTHER                = 0xB0AU, /*!< FCCU other Error */

    /* EMIOS specific error codes */
    STATUS_EMIOS_WRONG_MODE                = 0xC00U,   /*!< EMIOS unsuccessful attempt selecting wrong mode. */
    STATUS_EMIOS_CNT_BUS_OVERFLOW          = 0xC01U,   /*!< EMIOS counter bus overflow. */
    STATUS_EMIOS_WRONG_CNT_BUS             = 0xC02U,   /*!< EMIOS unsuccessful attempt selecting wrong counter bus. */
    STATUS_EMIOS_ENABLE_GLOBAL_FRZ         = 0xC03U,   /*!< EMIOS must set global allow enter debug mode first. */

    /* EEE specific error codes */
    STATUS_EEE_ERROR_NO_ENOUGH_SPACE       = 0xD00U, /*!< The data is too big to fit in any of the block */
    STATUS_EEE_ERROR_NO_ENOUGH_BLOCK       = 0xD01U, /*!< The block numbers is not enough for round robin */
    STATUS_EEE_ERROR_DATA_NOT_FOUND        = 0xD02U, /*!< The required data is not found in the EEPROM emulation */
    STATUS_EEE_ERROR_NOT_IN_CACHE          = 0xD03U, /*!< The required data is not in the cache table */
    STATUS_EEE_ERROR_PROGRAM_INDICATOR     = 0xD04U, /*!< Failed to make block indicator to non-blank for several times */
    STATUS_EEE_HVOP_INPROGRESS             = 0xD05U, /*!< The high voltage operation is in progress */

    /* uSDHC specific error codes */
    STATUS_USDHC_OUT_OF_RANGE              = 0xE00U,    /*!< The size of data to be sent is larger than maximum size of ADMA table */
    STATUS_USDHC_PREPARE_ADMA_FAILED       = 0xE01U,    /*!< Failed to prepare the ADMA table */

    /* TDM specific error codes */
    STATUS_TDM_DIARY_FULL                  = 0xF01U, /*!< No empty flash left in diary region */

    /* PHY specific error codes */
    STATUS_PHY_ACCESS_FAILED               = 0x1001U, /*!< Could not access PHY registers */
    STATUS_PHY_INCOMPATIBLE_DEVICE         = 0x1002U  /*!< The selected PHY driver is not compatible with the device */
} status_t;


/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
/*!
 * @name LPTMR Driver Functions
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize a configuration structure with default values.
 *
 * @param[out] config - Pointer to the configuration structure to be initialized
 */
void LPTMR_DRV_InitConfigStruct(lptmr_config_t * const config);

/*!
 * @brief Initialize a LPTMR instance with values from an input configuration structure.
 *
 * When (counterUnits == LPTMR_COUNTER_UNITS_MICROSECONDS) the function will
 * automatically configure the timer for the input compareValue in microseconds.
 * The input parameters for 'prescaler' and 'bypassPrescaler' will be ignored - their values
 * will be adapted by the function, to best fit the input compareValue
 * (in microseconds) for the operating clock frequency.
 *
 * LPTMR_COUNTER_UNITS_MICROSECONDS may only be used for LPTMR_WORKMODE_TIMER mode.
 * Otherwise the function shall not convert 'compareValue' in ticks
 * and this is likely to cause erroneous behavior.
 *
 * When (counterUnits == LPTMR_COUNTER_UNITS_TICKS) the function will use the
 * 'prescaler' and 'bypassPrescaler' provided in the input configuration structure.
 *
 * @param[in] instance     - LPTMR instance number
 * @param[in] config       - Pointer to the input configuration structure
 * @param[in] startCounter - Flag for starting the counter immediately after configuration
 */
void LPTMR_DRV_Init(const uint32_t instance,
                    const lptmr_config_t * const config,
                    const bool startCounter);

/*!
 * @brief Configure a LPTMR instance.
 *
 * When (counterUnits == LPTMR_COUNTER_UNITS_MICROSECONDS) the function will
 * automatically configure the timer for the input compareValue in microseconds.
 * The input parameters for 'prescaler' and 'bypassPrescaler' will be ignored - their values
 * will be adapted by the function, to best fit the input compareValue
 * (in microseconds) for the operating clock frequency.
 *
 * LPTMR_COUNTER_UNITS_MICROSECONDS may only be used for LPTMR_WORKMODE_TIMER mode.
 * Otherwise the function shall not convert 'compareValue' in ticks
 * and this is likely to cause erroneous behavior.
 *
 * When (counterUnits == LPTMR_COUNTER_UNITS_TICKS) the function will use the
 * 'prescaler' and 'bypassPrescaler' provided in the input configuration structure.
 *
 * @param[in] instance - LPTMR instance number
 * @param[in] config   - Pointer to the input configuration structure
 */
void LPTMR_DRV_SetConfig(const uint32_t instance,
                         const lptmr_config_t * const config);

/*!
 * @brief Get the current configuration of a LPTMR instance.
 *
 * @param[in] instance - LPTMR instance number
 * @param[out] config  - Pointer to the output configuration structure
 */
void LPTMR_DRV_GetConfig(const uint32_t instance,
                         lptmr_config_t * const config);

/*!
 * @brief De-initialize a LPTMR instance
 *
 * @param[in] instance - LPTMR instance number
 */
void LPTMR_DRV_Deinit(const uint32_t instance);

/*!
 * @brief Set the compare value in counter tick units, for a LPTMR instance.
 *
 * @param[in] instance            - LPTMR instance number
 * @param[in] compareValueByCount - The compare value in counter ticks, to be written
 * @return Operation status:
 * - STATUS_SUCCESS: completed successfully
 * - STATUS_ERROR: cannot reconfigure compare value (TCF not set)
 * - STATUS_TIMEOUT: compare value greater then current counter value
 */
status_t LPTMR_DRV_SetCompareValueByCount(const uint32_t instance,
                                          const uint16_t compareValueByCount);

/*!
 * @brief Get the compare value in counter tick units, of a LPTMR instance.
 *
 * @param[in] instance             - LPTMR instance number
 * @param[out] compareValueByCount - Pointer to current compare value, in counter ticks
 */
void LPTMR_DRV_GetCompareValueByCount(const uint32_t instance,
                                      uint16_t * const compareValueByCount);

/*!
 * @brief Set the compare value for Timer Mode in microseconds, for a LPTMR instance.
 *
 * @param[in] instance       - LPTMR peripheral instance number
 * @param[in] compareValueUs - Compare value in microseconds
 * @return Operation status:
 * - STATUS_SUCCESS: completed successfully
 * - STATUS_ERROR: cannot reconfigure compare value
 * - STATUS_TIMEOUT: compare value greater then current counter value
 */
status_t LPTMR_DRV_SetCompareValueByUs(const uint32_t instance,
                                       const uint32_t compareValueUs);

/*!
 * @brief Get the compare value in microseconds, of a LPTMR instance.
 *
 * @param[in] instance        - LPTMR instance number
 * @param[out] compareValueUs - Pointer to current compare value, in microseconds
 */
void LPTMR_DRV_GetCompareValueByUs(const uint32_t instance,
                                   uint32_t * const compareValueUs);

/*!
 * @brief Get the current state of the Compare Flag of a LPTMR instance.
 *
 * @param[in] instance - LPTMR instance number
 * @return The state of the Compare Flag
 */
bool LPTMR_DRV_GetCompareFlag(const uint32_t instance);

/*!
 * @brief Clear the Compare Flag of a LPTMR instance.
 *
 * @param[in] instance - LPTMR instance number
 */
void LPTMR_DRV_ClearCompareFlag(const uint32_t instance);

/*!
 * @brief Get the run state of a LPTMR instance.
 *
 * @param[in] instance - LPTMR instance number
 * @return The run state of the LPTMR instance:
 *  - true: Timer/Counter started
 *  - false: Timer/Counter stopped
 */
bool LPTMR_DRV_IsRunning(const uint32_t instance);

/*!
 * @brief Enable/disable the LPTMR interrupt.
 *
 * @param[in] instance        - LPTMR instance number
 * @param[in] enableInterrupt - The new state of the LPTMR interrupt enable flag.
 */
void LPTMR_DRV_SetInterrupt(const uint32_t instance,
                            const bool enableInterrupt);

/*!
 * @brief Get the current counter value in counter tick units.
 *
 * @param[in] instance - LPTMR instance number
 * @return The current counter value
 */
uint16_t LPTMR_DRV_GetCounterValueByCount(const uint32_t instance);

/*!
 * @brief Enable the LPTMR / Start the counter
 *
 * @param[in] instance - LPTMR instance number
 */
void LPTMR_DRV_StartCounter(const uint32_t instance);

/*!
 * @brief Disable the LPTMR / Stop the counter
 *
 * @param[in] instance - LPTMR instance number
 */
void LPTMR_DRV_StopCounter(const uint32_t instance);

/*!
 * @brief Set the Input Pin configuration for Pulse Counter mode
 *
 * @param[in] instance    - LPTMR instance number
 * @param[in] pinSelect   - LPTMR pin selection
 * @param[in] pinPolarity - Polarity on which to increment counter (rising/falling edge)
 */
void LPTMR_DRV_SetPinConfiguration(const uint32_t instance,
                                   const lptmr_pinselect_t pinSelect,
                                   const lptmr_pinpolarity_t pinPolarity);

#if defined(__cplusplus)
}
#endif

/*! @}*/

/*! @}*/

#endif /* LPTMR_DRIVER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
