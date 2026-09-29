#include "hal_data.h"

#if (1 == BSP_MULTICORE_PROJECT) && BSP_TZ_SECURE_BUILD
bsp_ipc_semaphore_handle_t g_core_start_semaphore =
{
    .semaphore_num = 0
};
#endif

/*******************************************************************************************************************//**
 * Main application entry
 **********************************************************************************************************************/
void hal_entry(void)
{
    /*
     * Ethernet initialization is temporarily disabled.
     * This test checks whether the HardFault is caused by
     * Ethernet initialization or by the application/µT-Kernel.
     */

    /* Start µT-Kernel */
    void knl_start_mtkernel(void);
    knl_start_mtkernel();


    /* Wake up 2nd core if this is first core and we are inside a multicore project. */
#if (0 == _RA_CORE) && (1 == BSP_MULTICORE_PROJECT) && !BSP_TZ_NONSECURE_BUILD

#if BSP_TZ_SECURE_BUILD
    /* Take semaphore so 2nd core can clear it */
    R_BSP_IpcSemaphoreTake(&g_core_start_semaphore);
#endif

    R_BSP_SecondaryCoreStart();

#if BSP_TZ_SECURE_BUILD
    /* Wait for 2nd core to start and clear semaphore */
    while (FSP_ERR_IN_USE == R_BSP_IpcSemaphoreTake(&g_core_start_semaphore))
    {
        ;
    }
#endif

#endif


#if (1 == _RA_CORE) && (1 == BSP_MULTICORE_PROJECT) && BSP_TZ_SECURE_BUILD

    /* Signal to 1st core that 2nd core has started */
    R_BSP_IpcSemaphoreGive(&g_core_start_semaphore);

#endif


#if BSP_TZ_SECURE_BUILD

    /* Enter non-secure code */
    R_BSP_NonSecureEnter();

#endif
}


#if BSP_TZ_SECURE_BUILD

FSP_CPP_HEADER

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable(void);


/* TrustZone Secure Projects require at least one non-secure callable function. */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable(void)
{
    /* Nothing to do */
}

FSP_CPP_FOOTER

#endif
