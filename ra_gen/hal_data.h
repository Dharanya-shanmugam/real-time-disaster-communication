/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_ether_api.h"
#include "r_rmac.h"
FSP_HEADER
/** Ether on RMAC Instance. */
extern const ether_instance_t g_ether0;

/** Access the RMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern rmac_instance_ctrl_t g_ether0_ctrl;
extern const ether_cfg_t g_ether0_cfg;

#ifndef NULL
void NULL(ether_callback_args_t *p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
