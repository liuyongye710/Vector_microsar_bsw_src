#include "smpu_demo.h"
static const smpu_master_acc_right_t masterAccConfigRW[] =
{
    /* CORE0 */
    {
        .masterNum = SMPU_MASTER_CORE0,
        .accRight = SMPU_RW,
    },
    /* CORE1 */
    {
        .masterNum = SMPU_MASTER_CORE1,
        .accRight = SMPU_RW,
    },
    /* CORE2 */
    {
        .masterNum = SMPU_MASTER_CORE2,
        .accRight = SMPU_RW,
    },
    /* DMA0 */
    {
        .masterNum = SMPU_MASTER_DMA0,
        .accRight = SMPU_RW,
    },
    /* Ethernet */
    {
        .masterNum = SMPU_MASTER_ENET,
        .accRight = SMPU_RW,
    },
    /* FlexRay0 */
    {
        .masterNum = SMPU_MASTER_FLEXRAY0,
        .accRight = SMPU_RW,
    },
    /* DMA1 */
    {
        .masterNum = SMPU_MASTER_DMA1,
        .accRight = SMPU_RW,
    },
    /* FlexRay1 */
    {
        .masterNum = SMPU_MASTER_FLEXRAY1,
        .accRight = SMPU_RW,
    },
    /* HSM */
    {
        .masterNum = SMPU_MASTER_HSM,
        .accRight = SMPU_RW,
    },
    {
        .masterNum = SMPU_MASTER_DEBUG_CORE0,
        .accRight = SMPU_RW,
    },
    {
        .masterNum = SMPU_MASTER_DEBUG_CORE1,
        .accRight = SMPU_RW,
    },
    {
        .masterNum = SMPU_MASTER_DEBUG_CORE2,
        .accRight = SMPU_RW,
    },

};
static const smpu_config_t userConfigSmpu0[] = /* PRQA S 3218 */
{
    /* Region 0 (DCACHE) */
    {
        .startAddr           = SMPU0_START_ADDR,
        .endAddr             = 0x400BFFFFU,
        .masterAccRight      = masterAccConfigRW,
        .cacheInhibitEnable  = 0U,
        .lockConfig          = SMPU_UNLOCK
    },
    /* Region 1 (nonDCACHE) */
    {
        .startAddr           = 0x400C0000U,
        .endAddr             = 0x400DFFFFU,
        .masterAccRight      = masterAccConfigRW,
        .cacheInhibitEnable  = 0U,
        .lockConfig          = SMPU_UNLOCK
    },
    /* Region 2 (DCACHE) */
    {
        .startAddr           = 0x400E0000U,
        .endAddr             = SMPU0_END_ADDR,
        .masterAccRight      = masterAccConfigRW,
        .cacheInhibitEnable  = 0U,
        .lockConfig          = SMPU_UNLOCK
    }
};
static const smpu_config_t userConfigSmpu1[] = /* PRQA S 3218 */
{
    /* Region 0 (DCACHE) */
    {
        .startAddr           = SMPU1_START_ADDR,
        .endAddr             = SMPU1_END_ADDR,
        .masterAccRight      = masterAccConfigRW,
        .cacheInhibitEnable  = 0U,
        .lockConfig          = SMPU_UNLOCK
    },
};

void SMPU_RW_Test(uint32_t instance){
    uint8_t regionCnt0 = 3U;
    uint8_t regionCnt1 = 1U;
	SMPU_LLD_Init(0, regionCnt0, userConfigSmpu0);
	SMPU_LLD_Init(1, regionCnt1, userConfigSmpu1);

}
