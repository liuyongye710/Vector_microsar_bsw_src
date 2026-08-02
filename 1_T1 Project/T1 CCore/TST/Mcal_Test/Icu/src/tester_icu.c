

#include "Icu.h"
#include "console.h"
#include "Icu_Cfg.h"
#include "Gpt_Stm_LLDriver.h"
#include "intc_lld.h"
#include "shell.h"
#include "tester_icu.h"
#include <string.h>
#include "Icu_Gtm_LLDrivers.h"
#include "EMIOS_IC_LLDrivers.h"
#include "Gtm_HAL_Irq.h"
#include "eDma_LLDriver.h"
#include "eTPU_LLDrivers.h"
#include "eTPU_HAL_Irq.h"
#include "tester_icu_etpu.h"
#include "eMIOS_HAL_Irq.h"

#define ICU_TEST_CASE_MAX   sizeof(icu_funcs) / sizeof(IcufuncMachine)
extern VAR(Icu_ModeType, ICU_VAR) eIcu_CurrentMode;
extern CONST(Icu_ConfigType, ICU_CONST) Icu_Cfg;
extern boolean TesterDemoICU;

extern Icu_GetWakeupStatus(VAR(Icu_ChannelType,AUTOMATIC) u16Icu_Channel);
extern ISR(GTM_TIM_0_CH_0_ISR);
extern ISR(GTM_TIM_0_CH_1_ISR);
extern ISR(GTM_TIM_0_CH_2_ISR);
extern ISR(GTM_TIM_0_CH_3_ISR);
extern ISR(GTM_TIM_0_CH_4_ISR);
extern ISR(GTM_TIM_0_CH_5_ISR);
extern ISR(GTM_TIM_0_CH_6_ISR);
extern ISR(GTM_TIM_0_CH_7_ISR);
extern ISR(GTM_TIM_1_CH_0_ISR);
extern ISR(GTM_TIM_1_CH_1_ISR);
extern ISR(GTM_TIM_1_CH_2_ISR);
extern ISR(GTM_TIM_1_CH_3_ISR);
extern ISR(GTM_TIM_1_CH_4_ISR);
extern ISR(GTM_TIM_1_CH_5_ISR);
extern ISR(GTM_TIM_1_CH_6_ISR);
extern ISR(GTM_TIM_1_CH_7_ISR);
extern ISR(GTM_TIM_2_CH_0_ISR);
extern ISR(GTM_TIM_2_CH_1_ISR);
extern ISR(GTM_TIM_2_CH_2_ISR);
extern ISR(GTM_TIM_2_CH_3_ISR);
extern ISR(GTM_TIM_2_CH_4_ISR);
extern ISR(GTM_TIM_2_CH_5_ISR);
extern ISR(GTM_TIM_2_CH_6_ISR);
extern ISR(GTM_TIM_2_CH_7_ISR);
extern ISR(GTM_TIM_3_CH_0_ISR);
extern ISR(GTM_TIM_3_CH_1_ISR);
extern ISR(GTM_TIM_3_CH_2_ISR);
extern ISR(GTM_TIM_3_CH_3_ISR);
extern ISR(GTM_TIM_3_CH_4_ISR);
extern ISR(GTM_TIM_3_CH_5_ISR);
extern ISR(GTM_TIM_3_CH_6_ISR);
extern ISR(GTM_TIM_3_CH_7_ISR);
extern ISR(GTM_TIM_4_CH_0_ISR);
extern ISR(GTM_TIM_4_CH_1_ISR);
extern ISR(GTM_TIM_4_CH_2_ISR);
extern ISR(GTM_TIM_4_CH_3_ISR);
extern ISR(GTM_TIM_4_CH_4_ISR);
extern ISR(GTM_TIM_4_CH_5_ISR);
extern ISR(GTM_TIM_4_CH_6_ISR);
extern ISR(GTM_TIM_4_CH_7_ISR);
extern ISR(GTM_TIM_5_CH_0_ISR);
extern ISR(GTM_TIM_5_CH_1_ISR);
extern ISR(GTM_TIM_5_CH_2_ISR);
extern ISR(GTM_TIM_5_CH_3_ISR);
extern ISR(GTM_TIM_5_CH_4_ISR);
extern ISR(GTM_TIM_5_CH_5_ISR);
extern ISR(GTM_TIM_5_CH_6_ISR);
extern ISR(GTM_TIM_5_CH_7_ISR);
//extern ISR(SIUL2_EIRQ_0_IRQHandler);
//extern ISR(SIUL2_EIRQ_1_IRQHandler);

static uint32 Icu_case_id_10ms = 0U;
static uint32 Icu_case_id_20ms = 0U;
static uint32 Icu_case_id_30ms = 0U;
static uint32 Icu_case_id_main = 0U;


static CONST(IntrId, ICU_CONST) const EMIOS_IRQ_NUM[EMIOS_INSTANCE_MAX][EMIOS_MODULE_CHANNEL_MAX] = {   \
    {   \
        INTR_ID_943,            INTR_ID_944,            INTR_ID_945,            EMIOS0_CH3_IRQ995,      \
        EMIOS0_CH4_IRQ996,      EMIOS0_CH5_IRQ997,      EMIOS0_CH6_IRQ998,      EMIOS0_CH7_IRQ999,      \
        EMIOS0_CH8_IRQ1000,     EMIOS0_CH9_IRQ1001,     EMIOS0_CH10_IRQ1002,    EMIOS0_CH11_IRQ1003,    \
        EMIOS0_CH12_IRQ1004,    EMIOS0_CH13_IRQ1005,    EMIOS0_CH14_IRQ1006,    EMIOS0_CH15_IRQ1007,    \
        EMIOS0_CH16_IRQ1008,    EMIOS0_CH17_IRQ1009,    EMIOS0_CH18_IRQ1010,    EMIOS0_CH19_IRQ1011,    \
        EMIOS0_CH20_IRQ1012,    EMIOS0_CH21_IRQ1013,    EMIOS0_CH22_IRQ1014,    EMIOS0_CH23_IRQ1015,    \
        EMIOS0_CH24_IRQ1016,    EMIOS0_CH25_IRQ1017,    EMIOS0_CH26_IRQ1018,    EMIOS0_CH27_IRQ1019,    \
        EMIOS0_CH28_IRQ1020,    EMIOS0_CH29_IRQ1021,    EMIOS0_CH30_IRQ1022,    EMIOS0_CH31_IRQ1023     \
    },  \
    {   \
        INTR_ID_649,            INTR_ID_650,            INTR_ID_651,            INTR_ID_652,            \
        INTR_ID_653,            INTR_ID_666,            INTR_ID_667,            INTR_ID_668,            \
        INTR_ID_669,            INTR_ID_670,            INTR_ID_671,            INTR_ID_672,            \
        INTR_ID_673,            INTR_ID_676,            INTR_ID_680,            INTR_ID_681,            \
        INTR_ID_682,            INTR_ID_683,            INTR_ID_684,            INTR_ID_704,            \
        INTR_ID_705,            INTR_ID_932,            INTR_ID_933,            INTR_ID_934,            \
        INTR_ID_935,            INTR_ID_936,            INTR_ID_937,            INTR_ID_938,            \
        INTR_ID_939,            INTR_ID_940,            INTR_ID_941,            INTR_ID_942             \
    }   \
};

static CONST(IntrHandle, ICU_CONST) EMIOS_IRQ_Callback[EMIOS_INSTANCE_MAX][EMIOS_MODULE_CHANNEL_MAX] = { \
    {   \
        eMIOS0_CH0_Handler,     eMIOS0_CH1_Handler,     eMIOS0_CH2_Handler,     eMIOS0_CH3_Handler,     \
        eMIOS0_CH4_Handler,     eMIOS0_CH5_Handler,     eMIOS0_CH6_Handler,     eMIOS0_CH7_Handler,     \
        eMIOS0_CH8_Handler,     eMIOS0_CH9_Handler,     eMIOS0_CH10_Handler,    eMIOS0_CH11_Handler,    \
        eMIOS0_CH12_Handler,    eMIOS0_CH13_Handler,    eMIOS0_CH14_Handler,    eMIOS0_CH15_Handler,    \
        eMIOS0_CH16_Handler,    eMIOS0_CH17_Handler,    eMIOS0_CH18_Handler,    eMIOS0_CH19_Handler,    \
        eMIOS0_CH20_Handler,    eMIOS0_CH21_Handler,    eMIOS0_CH22_Handler,    eMIOS0_CH23_Handler,    \
        eMIOS0_CH24_Handler,    eMIOS0_CH25_Handler,    eMIOS0_CH26_Handler,    eMIOS0_CH27_Handler,    \
        eMIOS0_CH28_Handler,    eMIOS0_CH29_Handler,    eMIOS0_CH30_Handler,    eMIOS0_CH31_Handler     \
    },  \
    {   \
        eMIOS1_CH0_Handler,     eMIOS1_CH1_Handler,     eMIOS1_CH2_Handler,     eMIOS1_CH3_Handler,     \
        eMIOS1_CH4_Handler,     eMIOS1_CH5_Handler,     eMIOS1_CH6_Handler,     eMIOS1_CH7_Handler,     \
        eMIOS1_CH8_Handler,     eMIOS1_CH9_Handler,     eMIOS1_CH10_Handler,    eMIOS1_CH11_Handler,    \
        eMIOS1_CH12_Handler,    eMIOS1_CH13_Handler,    eMIOS1_CH14_Handler,    eMIOS1_CH15_Handler,    \
        eMIOS1_CH16_Handler,    eMIOS1_CH17_Handler,    eMIOS1_CH18_Handler,    eMIOS1_CH19_Handler,    \
        eMIOS1_CH20_Handler,    eMIOS1_CH21_Handler,    eMIOS1_CH22_Handler,    eMIOS1_CH23_Handler,    \
        eMIOS1_CH24_Handler,    eMIOS1_CH25_Handler,    eMIOS1_CH26_Handler,    eMIOS1_CH27_Handler,    \
        eMIOS1_CH28_Handler,    eMIOS1_CH29_Handler,    eMIOS1_CH30_Handler,    eMIOS1_CH31_Handler     \
    }   \
};

static CONST(IntrId, ICU_CONST) const ETPU_IRQ_NUM[ETPU_IRQ_INSTANCE_MAX][ETPU_MODULE_CHANNEL_MAX] = {   \
    {   \
        INTR_ID_236,            INTR_ID_237,            INTR_ID_238,            INTR_ID_245,      \
        INTR_ID_246,            INTR_ID_247,            INTR_ID_248,            INTR_ID_249,      \
        INTR_ID_250,            INTR_ID_256,            INTR_ID_257,            INTR_ID_258,    \
        INTR_ID_267,            INTR_ID_276,            INTR_ID_285,            INTR_ID_294,    \
        INTR_ID_322,            INTR_ID_323,            INTR_ID_324,            INTR_ID_325,      \
        INTR_ID_326,            INTR_ID_327,            INTR_ID_328,            INTR_ID_329,      \
        INTR_ID_330,            INTR_ID_331,            INTR_ID_332,            INTR_ID_333,    \
        INTR_ID_334,            INTR_ID_335,            INTR_ID_336,            INTR_ID_337,    \
    },  \
    {   \
        INTR_ID_338,            INTR_ID_339,            INTR_ID_340,            INTR_ID_341,            \
        INTR_ID_342,            INTR_ID_343,            INTR_ID_344,            INTR_ID_345,            \
        INTR_ID_346,            INTR_ID_347,            INTR_ID_348,            INTR_ID_349,            \
        INTR_ID_350,            INTR_ID_351,            INTR_ID_352,            INTR_ID_353,            \
        INTR_ID_354,            INTR_ID_355,            INTR_ID_356,            INTR_ID_357,            \
        INTR_ID_358,            INTR_ID_359,            INTR_ID_360,            INTR_ID_361,            \
        INTR_ID_362,            INTR_ID_363,            INTR_ID_364,            INTR_ID_365,            \
        INTR_ID_366,            INTR_ID_379,            INTR_ID_383,            INTR_ID_387             \
    },   \
    {   \
        INTR_ID_390,            INTR_ID_391,            INTR_ID_392,            INTR_ID_393,            \
        INTR_ID_394,            INTR_ID_395,            INTR_ID_396,            INTR_ID_397,            \
        INTR_ID_398,            INTR_ID_399,            INTR_ID_400,            INTR_ID_401,            \
        INTR_ID_402,            INTR_ID_403,            INTR_ID_404,            INTR_ID_405,            \
        INTR_ID_406,            INTR_ID_407,            INTR_ID_408,            INTR_ID_409,            \
        INTR_ID_410,            INTR_ID_411,            INTR_ID_412,            INTR_ID_413,            \
        INTR_ID_414,            INTR_ID_415,            INTR_ID_419,            INTR_ID_420,            \
        INTR_ID_421,            INTR_ID_422,            INTR_ID_423,            INTR_ID_424             \
    }   \
};

static CONST(IntrHandle, ICU_CONST) ETPU_IRQ_Callback[ETPU_IRQ_INSTANCE_MAX][ETPU_MODULE_CHANNEL_MAX] = { \
    {   \
        eTPUA_CH0_Handler,     eTPUA_CH1_Handler,     eTPUA_CH2_Handler,     eTPUA_CH3_Handler,     \
        eTPUA_CH4_Handler,     eTPUA_CH5_Handler,     eTPUA_CH6_Handler,     eTPUA_CH7_Handler,     \
        eTPUA_CH8_Handler,     eTPUA_CH9_Handler,     eTPUA_CH10_Handler,    eTPUA_CH11_Handler,    \
        eTPUA_CH12_Handler,    eTPUA_CH13_Handler,    eTPUA_CH14_Handler,    eTPUA_CH15_Handler,    \
        eTPUA_CH16_Handler,    eTPUA_CH17_Handler,    eTPUA_CH18_Handler,    eTPUA_CH19_Handler,    \
        eTPUA_CH20_Handler,    eTPUA_CH21_Handler,    eTPUA_CH22_Handler,    eTPUA_CH23_Handler,    \
        eTPUA_CH24_Handler,    eTPUA_CH25_Handler,    eTPUA_CH26_Handler,    eTPUA_CH27_Handler,    \
        eTPUA_CH28_Handler,    eTPUA_CH29_Handler,    eTPUA_CH30_Handler,    eTPUA_CH31_Handler     \
    },  \
    {   \
        eTPUB_CH0_Handler,     eTPUB_CH1_Handler,     eTPUB_CH2_Handler,     eTPUB_CH3_Handler,     \
        eTPUB_CH4_Handler,     eTPUB_CH5_Handler,     eTPUB_CH6_Handler,     eTPUB_CH7_Handler,     \
        eTPUB_CH8_Handler,     eTPUB_CH9_Handler,     eTPUB_CH10_Handler,    eTPUB_CH11_Handler,    \
        eTPUB_CH12_Handler,    eTPUB_CH13_Handler,    eTPUB_CH14_Handler,    eTPUB_CH15_Handler,    \
        eTPUB_CH16_Handler,    eTPUB_CH17_Handler,    eTPUB_CH18_Handler,    eTPUB_CH19_Handler,    \
        eTPUB_CH20_Handler,    eTPUB_CH21_Handler,    eTPUB_CH22_Handler,    eTPUB_CH23_Handler,    \
        eTPUB_CH24_Handler,    eTPUB_CH25_Handler,    eTPUB_CH26_Handler,    eTPUB_CH27_Handler,    \
        eTPUB_CH28_Handler,    eTPUB_CH29_Handler,    eTPUB_CH30_Handler,    eTPUB_CH31_Handler     \
    },  \
    {   \
        eTPUC_CH0_Handler,     eTPUC_CH1_Handler,     eTPUC_CH2_Handler,     eTPUC_CH3_Handler,     \
        eTPUC_CH4_Handler,     eTPUC_CH5_Handler,     eTPUC_CH6_Handler,     eTPUC_CH7_Handler,     \
        eTPUC_CH8_Handler,     eTPUC_CH9_Handler,     eTPUC_CH10_Handler,    eTPUC_CH11_Handler,    \
        eTPUC_CH12_Handler,    eTPUC_CH13_Handler,    eTPUC_CH14_Handler,    eTPUC_CH15_Handler,    \
        eTPUC_CH16_Handler,    eTPUC_CH17_Handler,    eTPUC_CH18_Handler,    eTPUC_CH19_Handler,    \
        eTPUC_CH20_Handler,    eTPUC_CH21_Handler,    eTPUC_CH22_Handler,    eTPUC_CH23_Handler,    \
        eTPUC_CH24_Handler,    eTPUC_CH25_Handler,    eTPUC_CH26_Handler,    eTPUC_CH27_Handler,    \
        eTPUC_CH28_Handler,    eTPUC_CH29_Handler,    eTPUC_CH30_Handler,    eTPUC_CH31_Handler     \
    }   \
};

static IcufuncMachine icu_funcs[] = {
    {"icu_deinit",icu_de_init},
    {"icuinit", icuinit},
    {"icu_01", icu_01},
    {"icu_02", icu_02},
    {"icu_03", icu_03},
    {"icu_04", icu_04},
    {"icu_05", icu_05},
    {"icu_06", icu_06},
    {"icu_07", icu_07},
    {"icu_08", icu_08},
    {"icu_09", icu_09},
    {"icu_10", icu_10},
    {"icu_11", icu_11},
    {"icu_12", icu_12},
    {"icu_13", icu_13},
    {"icu_14", icu_14},
    {"icu_15", icu_15},
    {"icu_16", icu_16},
    {"icu_17", icu_17},
    {"icu_18", icu_18},
    {"icu_19", icu_19},
    {"icu_20", icu_20},
    {"icu_21", icu_21},
    {"icu_22", icu_22},
    {"icu_23", icu_23},
    {"icu_24", icu_24},
    {"icu_25", icu_25},
    {"icu_26", icu_26},
    {"icu_27", icu_27},
    {"icu_28", icu_28},
    {"icu_29", icu_29},
    {"icu_30", icu_30},
    {"icu_31", icu_31},
    {"icu_32", icu_32},
    {"icu_33", icu_33},
    {"icu_34", icu_34},
    {"icu_35", icu_35},
    {"icu_36", icu_36},
    {"icu_37", icu_37},
    {"icu_38", icu_38},
    {"icu_39", icu_39},
    {"icu_40", icu_40},
    {"icu_41", icu_41},
    {"icu_42", icu_42},
    {"icu_43", icu_43},
    {"icu_44", icu_44},
    {"icu_45", icu_45},
    {"icu_46", icu_46},
    {"icu_47", icu_47},
    {"icu_48", icu_48},
    {"icu_49", icu_49},
    {"icu_50", icu_50},
    {"icu_51", icu_51},
    {"icu_52", icu_52},
    {"icu_53", icu_53},
    {"icu_54", icu_54},
    {"icu_55", icu_55},
    {"icu_56", icu_56},
    {"icu_57", icu_57},
    {"icu_58", icu_58},
    {"icu_59", icu_59},
    {"icu_60", icu_60},
    {"icu_61", icu_61},
    {"icu_62", icu_62},
    {"icu_63", icu_63},
    {"icu_64", icu_64},
    {"icu_65", icu_65},
    {"icu_66", icu_66},
    {"icu_67", icu_67},
    {"icu_68", icu_68},
    {"icu_69", icu_69},
    {"icu_70", icu_70},
    {"icu_71", icu_71},
    {"icu_72", icu_72},
    {"icu_73", icu_73},
    {"icu_74", icu_74},
    {"icu_99", icu_99},
	{"icu_100",icu_100},
	{"icu_101",icu_101},
	{"icu_102",icu_102},
	{"icu_103",icu_103},
	{"icu_104",icu_104},
	{"icu_105",icu_105},
	{"icu_106",icu_106},
	{"icu_107",icu_107},
	{"icu_108",icu_108},
	{"icu_109",icu_109},
	{"icu_110",icu_110},
	{"icu_111",icu_111},
	{"icu_112",icu_112},
	{"icu_113",icu_113},
	{"icu_114",icu_114},
	{"icu_115",icu_115},
	{"icu_116",icu_116},
	{"icu_117",icu_117},
	{"icu_118",icu_118},
	{"icu_119",icu_119},
	{"icu_120",icu_120},
	{"icu_121",icu_121},
	{"icu_122",icu_122},
	{"icu_123",icu_123},
	{"icu_124",icu_124},
	{"icu_125",icu_125},
	{"icu_126",icu_126},
	{"icu_127",icu_127},
	{"icu_128",icu_128},
	{"icu_129",icu_129},
	{"icu_130",icu_130},
	{"icu_131",icu_131},
	{"icu_132",icu_132},
	{"icu_133",icu_133},
	{"icu_134",icu_134},
	{"icu_135",icu_135},
	{"icu_136",icu_136},
	{"icu_137",icu_137},
	{"icu_138",icu_138},
	{"icu_139",icu_139},
	{"icu_140",icu_140},
	{"icu_141",icu_141},
	{"icu_142",icu_142},
    {"icu_143"	,icu_143},
    {"icu_144"	,icu_144},
    {"icu_145"	,icu_145},
    {"icu_146"	,icu_146},
    {"icu_147"	,icu_147},
    {"icu_148"	,icu_148},
    {"icu_149"	,icu_149},
    {"icu_150"	,icu_150},
    {"icu_151"	,icu_151},
    {"icu_152"	,icu_152},
    {"icu_153"	,icu_153},
    {"icu_154"	,icu_154},
    {"icu_155"	,icu_155},
    {"icu_156"	,icu_156},
    {"icu_157"	,icu_157},
    {"icu_158"	,icu_158},
    {"icu_159"	,icu_159},
    {"icu_160"	,icu_160},
    {"icu_161"	,icu_161},
    {"icu_162"	,icu_162},
    {"icu_163"	,icu_163},
    {"icu_164"	,icu_164},
    {"icu_165"	,icu_165},
    {"icu_166"	,icu_166},
    {"icu_167"	,icu_167},
    {"icu_168"	,icu_168},
    {"icu_257"	 ,icu_257},
    {"icu_258"	 ,icu_258},
    {"icu_259"	 ,icu_259},
    {"icu_260"	 ,icu_260},
    {"icu_261"	 ,icu_261},
    {"icu_262"	 ,icu_262},
    {"icu_263"	 ,icu_263},
    {"icu_264"	 ,icu_264},
    {"icu_265"	 ,icu_265},
    {"icu_266"	 ,icu_266},
    {"icu_267"	 ,icu_267},
    {"icu_268"	 ,icu_268},
    {"icu_269"	 ,icu_269},
    {"icu_270"	 ,icu_270},
    {"icu_271"	 ,icu_271},
    {"icu_272"	 ,icu_272},
    {"icu_273"	 ,icu_273},
    {"icu_274"	 ,icu_274},
    {"icu_275"	 ,icu_275},
    {"icu_276"	 ,icu_276},
    {"icu_277"	 ,icu_277},
    {"icu_278"	 ,icu_278},
    {"icu_279"	 ,icu_279},
    {"icu_280"	 ,icu_280},
    {"icu_281"	 ,icu_281},
    {"icu_282"	 ,icu_282},
    {"icu_283"	 ,icu_283},
    {"icu_284"	 ,icu_284},
    {"icu_285"	 ,icu_285},
    {"icu_286"	 ,icu_286},
	{"icu_306"	 ,icu_306},
	{"icu_307"	 ,icu_307},
	{"icu_308"	 ,icu_308},
	{"icu_309"	 ,icu_309},
	{"icu_310"	 ,icu_310},
	{"icu_311"	 ,icu_311},
	{"icu_312"	 ,icu_312},
	{"icu_313"	 ,icu_313},
	{"icu_314"	 ,icu_314},
	{"icu_315"	 ,icu_315},
	{"icu_316"	 ,icu_316},
	{"icu_317"	 ,icu_317},
	{"icu_318"	 ,icu_318},
	{"icu_319"	 ,icu_319},
	{"icu_320"	 ,icu_320},
	{"icu_321"	 ,icu_321},
	{"icu_322"	 ,icu_322},
	{"icu_323"	 ,icu_323},
	{"icu_324"	 ,icu_324},
	{"icu_325"	 ,icu_325},
	{"icu_326"	 ,icu_326},
    {"icu_327"	 ,icu_327},
	{"icu_328"	 ,icu_328},
	{"icu_329"	 ,icu_329},
	{"icu_330"	 ,icu_330},
	//{"331"	 ,icu_331},

	ICU_ETPU_TEST
};

void icu_de_init()
{
    Icu_DeInit();
}

void IcuSignalNotification_0(void)
{
}

void IcuSignalNotification_1(void)
{
}
void IcuSignalNotification_2(void)
{}

void IcuSignalNotification_3(void)
{}
void IcuSignalNotification_4(void)
{}
void IcuSignalNotification_5(void)
{}
void IcuSignalNotification_6(void)
{}
void IcuSignalNotification_7(void)
{}
void IcuSignalNotification_8(void)
{}
void IcuSignalNotification_9(void)
{}
void IcuSignalNotification_10(void)
{}
void IcuSignalNotification_11(void)
{}
void IcuSignalNotification_12(void)
{}
void IcuSignalNotification_13(void)
{}
void IcuSignalNotification_14(void)
{}
void IcuSignalNotification_15(void)
{}
void IcuSignalNotification_16(void)
{}
void IcuSignalNotification_17(void)
{}
void IcuSignalNotification_18(void)
{}
void IcuSignalNotification_19(void)
{}
void IcuSignalNotification_20(void)
{}
void IcuSignalNotification_21(void)
{}
void IcuSignalNotification_22(void)
{}
void IcuSignalNotification_23(void)
{}
void IcuSignalNotification_24(void)
{}
void IcuSignalNotification_25(void)
{}
void IcuSignalNotification_26(void)
{}
void IcuSignalNotification_27(void)
{}
void IcuSignalNotification_28(void)
{}
void IcuSignalNotification_29(void)
{}
void IcuSignalNotification_30(void)
{}
void IcuSignalNotification_31(void)
{}
void IcuSignalNotification_32(void)
{}
void IcuSignalNotification_33(void)
{}
void IcuSignalNotification_34(void)
{}
void IcuSignalNotification_35(void)
{}
void IcuSignalNotification_36(void)
{}
void IcuSignalNotification_37(void)
{}
void IcuSignalNotification_38(void)
{}
void IcuSignalNotification_39(void)
{}
void IcuSignalNotification_40(void)
{}
void IcuSignalNotification_41(void)
{}
void IcuSignalNotification_42(void)
{}
void IcuSignalNotification_43(void)
{}
void IcuSignalNotification_44(void)
{}
void IcuSignalNotification_45(void)
{}
void IcuSignalNotification_46(void)
{}
void IcuSignalNotification_47(void)
{}
void IcuSignalNotification_48(void)
{}
void IcuSignalNotification_49(void)
{}
void IcuSignalNotification_50(void)
{}
void IcuSignalNotification_51(void)
{}
void IcuSignalNotification_52(void)
{}
void IcuSignalNotification_53(void)
{}
void IcuSignalNotification_54(void)
{}
void IcuSignalNotification_55(void)
{}
void IcuSignalNotification_56(void)
{}
void IcuSignalNotification_57(void)
{}
void IcuSignalNotification_58(void)
{}
void IcuSignalNotification_59(void)
{}
void IcuSignalNotification_60(void)
{}
void IcuSignalNotification_61(void)
{}
void IcuSignalNotification_62(void)
{}
void IcuSignalNotification_63(void)
{}
void IcuSignalNotification_64(void)
{}
void IcuSignalNotification_65(void)
{}
void IcuSignalNotification_66(void)
{}
void IcuSignalNotification_67(void)
{}
void IcuSignalNotification_68(void)
{}
void IcuSignalNotification_69(void)
{}
void IcuSignalNotification_70(void)
{}
void IcuSignalNotification_71(void)
{}
void IcuSignalNotification_72(void)
{}
void IcuSignalNotification_73(void)
{}
void IcuSignalNotification_74(void)
{}
void IcuSignalNotification_75(void)
{}
void IcuSignalNotification_76(void)
{}
void IcuSignalNotification_77(void)
{}
void IcuSignalNotification_78(void)
{}
void IcuSignalNotification_79(void)
{}
void IcuSignalNotification_80(void)
{}
void IcuSignalNotification_81(void)
{}
void IcuSignalNotification_82(void)
{}
void IcuSignalNotification_83(void)
{}
void IcuSignalNotification_84(void)
{}
void IcuSignalNotification_85(void)
{}
void IcuSignalNotification_86(void)
{}
void IcuSignalNotification_87(void)
{}
void IcuSignalNotification_88(void)
{}
void IcuSignalNotification_89(void)
{}
void IcuSignalNotification_90(void)
{}
void IcuSignalNotification_91(void)
{}
void IcuSignalNotification_92(void)
{}
void IcuSignalNotification_93(void)
{}
void IcuSignalNotification_94(void)
{}
void IcuSignalNotification_95(void)
{}

void icuinit()
{
    Icu_Test_Demo();
    eMIOS_IC_PinInit(0, 0, 0);
    eMIOS_IC_PinInit(0, 1, 0);
    eMIOS_IC_PinInit(1, 0, 0);
    eMIOS_IC_PinInit(1, 1, 0);
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH8_IRQ61, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH8_IRQ61, &EDMA_Ch8_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH8_IRQ61);
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH12_IRQ65, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH12_IRQ65, &EDMA_Ch12_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH12_IRQ65);
    (void) INTC_LLD_Set_IRQ_Priority(DMA1_CH59_IRQ176, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Handle(DMA1_CH59_IRQ176, &EDMA_Ch123_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA1_CH59_IRQ176);
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH1_IRQ54, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH1_IRQ54, &EDMA_Ch1_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH1_IRQ54);
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH0_IRQ53, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH0_IRQ53, &EDMA_Ch0_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH0_IRQ53);
	(void) INTC_LLD_Set_IRQ_Priority(DMA1_CH50_IRQ167, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Handle(DMA1_CH50_IRQ167, &EDMA_Ch114_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA1_CH50_IRQ167);
    /* emios module init */
    eMios_Module_Init(0, 10);/* prameter 2: 3008:8, 3007:10*/
    eMios_Module_Init(1, 10);/* prameter 2: 3008:8, 3007:10*/
    /* etpu init */
    ETPU_IC_Init();
}

void IcuTimestampNotification_0(void)
{
    PSPRINTF("receipt of notification\n");
}

void IcuTimestampNotification_1(void)
{
    PSPRINTF("receipt of notification\n");
}

void IcuTimestampNotification_2(void)
{}

void Icu_Test_Demo(void)
{
    int i = 0;
    int j = 0;

    INTC_LLD_Set_IRQ_Handle(INTR_ID_749,GTM_TIM_0_CH_0_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_749, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_749);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_750,GTM_TIM_0_CH_1_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_750, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_750);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_751,GTM_TIM_0_CH_2_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_751, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_751);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_752,GTM_TIM_0_CH_3_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_752, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_752);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_753,GTM_TIM_0_CH_4_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_753, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_753);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_754,GTM_TIM_0_CH_5_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_754, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_754);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_755,GTM_TIM_0_CH_6_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_755, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_755);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_756,GTM_TIM_0_CH_7_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_756, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_756);


    INTC_LLD_Set_IRQ_Handle(INTR_ID_757,GTM_TIM_1_CH_0_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_757, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_757);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_758,GTM_TIM_1_CH_1_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_758, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_758);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_759,GTM_TIM_1_CH_2_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_759, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_759);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_760,GTM_TIM_1_CH_3_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_760, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_760);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_761,GTM_TIM_1_CH_4_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_761, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_761);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_762,GTM_TIM_1_CH_5_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_762, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_762);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_763,GTM_TIM_1_CH_6_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_763, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_763);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_764,GTM_TIM_1_CH_7_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_764, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_756);


    INTC_LLD_Set_IRQ_Handle(INTR_ID_765,GTM_TIM_2_CH_0_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_765, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_765);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_766,GTM_TIM_2_CH_1_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_766, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_766);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_767,GTM_TIM_2_CH_2_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_767, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_767);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_768,GTM_TIM_2_CH_3_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_768, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_768);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_769,GTM_TIM_2_CH_4_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_769, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_769);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_770,GTM_TIM_2_CH_5_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_770, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_770);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_771,GTM_TIM_2_CH_6_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_771, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_771);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_772,GTM_TIM_2_CH_7_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_772, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_772);


    INTC_LLD_Set_IRQ_Handle(INTR_ID_773,GTM_TIM_3_CH_0_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_773, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_773);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_774,GTM_TIM_3_CH_1_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_774, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_774);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_775,GTM_TIM_3_CH_2_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_775, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_775);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_776,GTM_TIM_3_CH_3_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_776, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_776);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_777,GTM_TIM_3_CH_4_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_777, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_777);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_778,GTM_TIM_3_CH_5_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_778, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_778);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_779,GTM_TIM_3_CH_6_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_779, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_779);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_780,GTM_TIM_3_CH_7_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_780, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_780);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_867,GTM_TIM_4_CH_0_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_867, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_867);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_868,GTM_TIM_4_CH_1_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_868, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_868);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_869,GTM_TIM_4_CH_2_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_869, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_869);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_870,GTM_TIM_4_CH_3_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_870, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_870);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_871,GTM_TIM_4_CH_4_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_871, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_871);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_872,GTM_TIM_4_CH_5_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_872, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_872);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_873,GTM_TIM_4_CH_6_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_873, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_873);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_874,GTM_TIM_4_CH_7_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_874, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_874);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_875,GTM_TIM_5_CH_0_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_875, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_875);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_876,GTM_TIM_5_CH_1_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_876, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_876);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_877,GTM_TIM_5_CH_2_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_877, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_877);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_878,GTM_TIM_5_CH_3_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_878, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_878);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_879,GTM_TIM_5_CH_4_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_879, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_879);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_880,GTM_TIM_5_CH_5_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_880, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_880);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_881,GTM_TIM_5_CH_6_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_881, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_881);

    INTC_LLD_Set_IRQ_Handle(INTR_ID_882,GTM_TIM_5_CH_7_ISR);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_882, INTR_PRI_50);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_882);

    for(i = 0;i < 2;i++)
    {
        for(j = 0;j < 32; j++)
        {
            eMIOS_LLD_SetIRQ(i,j);
        }
    }

    for( i = 0;i < 3; i++)
    {
        for(j = 0;j < 32; j++)
        {
            eTPU_LLD_SetIRQ(i,j);
        }
    }

//      GTMINT.GTMMCR.B.MDIS = 0;
//      GTM_CMU.GCLK_NUM.R = 6;
//      GTM_CMU.GCLK_DEN.R = 1;
//      GTM_CMU.CLK_EN.B.EN_CLK0 = 0b10;


}
FUNC(status_t, ICU_CODE) eMIOS_LLD_SetIRQ
(
    VAR(uint8_t, AUTOMATIC) emiosIndex, \
    VAR(uint8_t, AUTOMATIC) ChanNum \
)
{
    VAR(status_t, AUTOMATIC) ret = STATUS_ERROR;
    VAR(IntrId,   AUTOMATIC) irq_num;

    /*Check Module ID*/
    DEV_ASSERT((uint8)emiosIndex < (uint8)EMIOS_INSTANCE_MAX);

    if ((emiosIndex < (uint8)EMIOS_INSTANCE_MAX) && (ChanNum < (uint8)EMIOS_MODULE_CHANNEL_MAX))
    {
        ret = STATUS_SUCCESS;
    }

    if (ret == STATUS_SUCCESS)
    {
        irq_num = EMIOS_IRQ_NUM[emiosIndex][ChanNum];
        (void)INTC_LLD_Set_IRQ_Handle((IntrId)irq_num, \
            (IntrHandle)EMIOS_IRQ_Callback[emiosIndex][ChanNum]);
        (void)INTC_LLD_Set_IRQ_Enable((IntrId)irq_num);
        (void)INTC_LLD_Set_IRQ_Priority((IntrId)irq_num, INTR_PRI_51);
    }

    return ret;
}

FUNC(status_t, ICU_CODE) eTPU_LLD_SetIRQ
(
    VAR(uint8_t, AUTOMATIC) etpuIndex, \
    VAR(uint8_t, AUTOMATIC) ChanNum \
)
{
    VAR(status_t, AUTOMATIC) ret = STATUS_ERROR;
    VAR(IntrId,   AUTOMATIC) irq_num;

    /*Check Module ID*/
    DEV_ASSERT((uint8)etpuIndex < (uint8)ETPU_IRQ_INSTANCE_MAX);

    if ((etpuIndex < (uint8)ETPU_IRQ_INSTANCE_MAX) && (ChanNum < (uint8)ETPU_MODULE_CHANNEL_MAX))
    {
        ret = STATUS_SUCCESS;
    }

    if (ret == STATUS_SUCCESS)
    {
        irq_num = ETPU_IRQ_NUM[etpuIndex][ChanNum];
        (void)INTC_LLD_Set_IRQ_Handle((IntrId)irq_num, \
            (IntrHandle)ETPU_IRQ_Callback[etpuIndex][ChanNum]);
        (void)INTC_LLD_Set_IRQ_Enable((IntrId)irq_num);
        (void)INTC_LLD_Set_IRQ_Priority((IntrId)irq_num, INTR_PRI_51);
    }

    return ret;
}

void icu_01(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_Init(&Icu_Cfg);
    PSPRINTF("icu_01 is OK if ReportError is not printed\n");
}

void icu_02(void)
{
    Icu_Init(NULL_PTR);
    PSPRINTF("icu_02 is OK if ReportError is not printed\n");
}

void icu_03(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_DeInit();
    Icu_DeInit();
    PSPRINTF("icu_03 is OK if ReportError is not printed\n");
}

void icu_04(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(2);
    PSPRINTF("icu_04 is OK if ReportError is not printed\n");
}

void icu_05(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(1);
    if (eIcu_CurrentMode == 1)
    {
        PSPRINTF("icu_05 is ok\n");
    }
    else{
        PSPRINTF("icu_05 is not ok\n");
    }
    
}

void icu_06(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_DisableWakeup(100);
    PSPRINTF("icu_06 is OK if ReportError is not printed\n");
}

void icu_07(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_EnableWakeup(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_07 is OK if ReportError is not printed\n");
}

void icu_08(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_EnableWakeup(100);
    PSPRINTF("icu_08 is OK if ReportError is not printed\n");
}
void icu_09(void)
{
    Icu_CheckWakeup(0);
    Icu_Init(&Icu_Cfg);
    PSPRINTF("icu_09 is OK if ReportError is not printed\n");
}

void icu_10(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(1,ICU_FALLING_EDGE);
    PSPRINTF("icu_10 is OK if ReportError is not printed\n");
}

void icu_11(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(1,ICU_FALLING_EDGE);
    Icu_SetActivationCondition(1,ICU_FALLING_EDGE);
    PSPRINTF("icu_11 is OK if ReportError is not printed\n");
}

void icu_12(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(100,0);
    PSPRINTF("icu_12 is OK if ReportError is not printed\n");
}

void icu_13(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(8,7);
    PSPRINTF("icu_13 is OK if ReportError is not printed\n");
}

void icu_14(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_14 is OK if ReportError is not printed\n");
}

void icu_15(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_DisableNotification(100);
    PSPRINTF("icu_15 is OK if ReportError is not printed\n");
}

void icu_16(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_EnableNotification(100);
    PSPRINTF("icu_16 is OK if ReportError is not printed\n");
}

void icu_17(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_GetInputState(100);
    PSPRINTF("icu_17 is OK if ReportError is not printed\n");
}

void icu_18(void)
{
    Icu_InputStateType type = ICU_IDLE;
    Icu_Init(&Icu_Cfg);
    type = Icu_GetInputState(100);
    PSPRINTF("%d\n",type);
}

void icu_19(void)
{
    uint32 BufferPtr[10];
    Icu_Init(&Icu_Cfg);
    Icu_StartTimestamp(100,BufferPtr,10,100);
    PSPRINTF("icu_19 is OK if ReportError is not printed\n");
}

void icu_20(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_StopTimestamp(100);
    PSPRINTF("icu_20 is OK if ReportError is not printed\n");
}

void icu_21(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_StopTimestamp(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_21 is OK if ReportError is not printed\n");
}

void icu_22(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_GetTimestampIndex(100);
    PSPRINTF("icu_22 is OK if ReportError is not printed\n");
}

void icu_23(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_GetTimestampIndex(3);
    PSPRINTF("icu_23 is OK if ReportError is not printed\n");
}

void icu_24(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_ResetEdgeCount(100);
    PSPRINTF("icu_24 is OK if ReportError is not printed\n");
}

void icu_25(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_ResetEdgeCount(2);
    PSPRINTF("icu_25 is OK if ReportError is not printed\n");
}

void icu_26(void)
{
    Icu_Init(&Icu_Cfg);

    Icu_EnableEdgeCount(100);
    PSPRINTF("icu_26 is OK if ReportError is not printed\n");
}

void icu_27(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_EnableEdgeCount(2);
    PSPRINTF("icu_27 is OK if ReportError is not printed\n");
}

void icu_28(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_EnableEdgeDetection(100);
    PSPRINTF("icu_28 is OK if ReportError is not printed\n");
}

void icu_29(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_EnableEdgeDetection(3);
    PSPRINTF("icu_29 is OK if ReportError is not printed\n");
}

void icu_30(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_DisableEdgeDetection(100);
    PSPRINTF("icu_30 is OK if ReportError is not printed\n");
}

void icu_31(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_31 is OK if ReportError is not printed\n");
}

void icu_32(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_DisableEdgeCount(100);
    PSPRINTF("icu_32 is OK if ReportError is not printed\n");
}

void icu_33(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_DisableEdgeCount(2);
    PSPRINTF("icu_33 is OK if ReportError is not printed\n");
}

void icu_34(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_GetEdgeNumbers(100);
    PSPRINTF("icu_34 is OK if ReportError is not printed\n");
}

void icu_35(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_GetEdgeNumbers(2);
    PSPRINTF("icu_35 is OK if ReportError is not printed\n");
}

void icu_36(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_36 is OK if ReportError is not printed\n");
}

void icu_37(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(100);
    PSPRINTF("icu_37 is OK if ReportError is not printed\n");
}

void icu_38(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(1);
    PSPRINTF("icu_38 is OK if ReportError is not printed\n");
}

void icu_39(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_StopSignalMeasurement(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_39 is OK if ReportError is not printed\n");
}

void icu_40(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_StopSignalMeasurement(100);
    PSPRINTF("icu_40 is OK if ReportError is not printed\n");
}

void icu_41(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_StopSignalMeasurement(2);
    PSPRINTF("icu_41 is OK if ReportError is not printed\n");
}


void icu_42(void)
{
    Icu_ValueType type = 0;
    Icu_Init(&Icu_Cfg);
    type = Icu_GetTimeElapsed(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("%d\n",type);
}

void icu_43(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_GetTimeElapsed(100);
    PSPRINTF("icu_43 is OK if ReportError is not printed\n");
}

void icu_44(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_GetTimeElapsed(2);
    PSPRINTF("icu_44 is OK if ReportError is not printed\n");
}

void icu_45(void)
{
    Icu_ValueType type = 0;
    Icu_Init(&Icu_Cfg);
    type = Icu_GetTimeElapsed(100);
    PSPRINTF("%d\n",type);
}

void icu_46(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_GetDutyCycleValues(100,&DutyCycle);
    PSPRINTF("icu_46 is OK if ReportError is not printed\n");
}

void icu_47(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_GetDutyCycleValues(2,&DutyCycle);
    PSPRINTF("icu_47 is OK if ReportError is not printed\n");
}

/*****************************************FUNCTION_TEST****************************************************/

void icu_48(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(16);
    Icu_EnableEdgeCount(16);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(16);
    EdgeNumber = Icu_GetEdgeNumbers(16);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_49(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(15);
    Icu_EnableEdgeCount(15);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(15);
    EdgeNumber = Icu_GetEdgeNumbers(15);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_50(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(17);
    Icu_EnableEdgeCount(17);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(17);
    EdgeNumber = Icu_GetEdgeNumbers(17);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_51(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Gpt_Stm_LLD_DelayMs(STM1,500U);
    Icu_GetDutyCycleValues(9,&DutyCycle);
    Icu_StopSignalMeasurement(9);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_52(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(10);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(10,&DutyCycle);
    Icu_StopSignalMeasurement(10);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_53(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(9,&DutyCycle);
    Icu_StopSignalMeasurement(9);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_54(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(10);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(10,&DutyCycle);
    Icu_StopSignalMeasurement(10);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_55(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(9,&DutyCycle);
    Icu_StopSignalMeasurement(9);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_56(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(10);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(10,&DutyCycle);
    Icu_StopSignalMeasurement(10);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_57(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(46);
    Icu_EnableEdgeCount(46);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(46);
    EdgeNumber = Icu_GetEdgeNumbers(46);
    PSPRINTF("%d\n",EdgeNumber);
}


void icu_58(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(47);
    Icu_EnableEdgeCount(47);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(47);
    EdgeNumber = Icu_GetEdgeNumbers(47);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_59(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(2);
    Icu_EnableEdgeCount(2);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(2);
    EdgeNumber = Icu_GetEdgeNumbers(2);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_60(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(18);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(18,&DutyCycle);
    Icu_StopSignalMeasurement(18);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_61(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(19);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(19,&DutyCycle);
    Icu_StopSignalMeasurement(19);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_62(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(18);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(18,&DutyCycle);
    Icu_StopSignalMeasurement(18);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_63(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(19);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(19,&DutyCycle);
    Icu_StopSignalMeasurement(19);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_64(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(18);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(18,&DutyCycle);
    Icu_StopSignalMeasurement(18);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_65(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(19);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(19,&DutyCycle);
    Icu_StopSignalMeasurement(19);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_66(void)
{
    Icu_EdgeNumberType EdgeNumber0 = 0;
    Icu_EdgeNumberType EdgeNumber1 = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(16);
    Icu_ResetEdgeCount(46);
    Icu_EnableEdgeCount(16);
    Icu_EnableEdgeCount(46);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(16);
    Icu_DisableEdgeCount(46);
    EdgeNumber0 = Icu_GetEdgeNumbers(16);
    EdgeNumber1 = Icu_GetEdgeNumbers(46);
    PSPRINTF("%d %d\n",EdgeNumber0,EdgeNumber1);
}

void icu_67(void)
{
    Icu_EdgeNumberType EdgeNumber0 = 0;
    Icu_EdgeNumberType EdgeNumber1 = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(17);
    Icu_ResetEdgeCount(2);
    Icu_EnableEdgeCount(17);
    Icu_EnableEdgeCount(2);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(17);
    Icu_DisableEdgeCount(2);
    EdgeNumber0 = Icu_GetEdgeNumbers(17);
    EdgeNumber1 = Icu_GetEdgeNumbers(2);
    PSPRINTF("%d %d\n",EdgeNumber0,EdgeNumber1);
}

void icu_68(void)
{
    Icu_EdgeNumberType EdgeNumber0 = 0;
    Icu_EdgeNumberType EdgeNumber1 = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(15);
    Icu_ResetEdgeCount(47);
    Icu_EnableEdgeCount(15);
    Icu_EnableEdgeCount(47);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(15);
    Icu_DisableEdgeCount(47);
    EdgeNumber0 = Icu_GetEdgeNumbers(15);
    EdgeNumber1 = Icu_GetEdgeNumbers(47);
    PSPRINTF("%d %d\n",EdgeNumber0,EdgeNumber1);
}

void icu_69(void)
{

    Icu_DutyCycleType DutyCycle0 = {0};
    Icu_DutyCycleType DutyCycle1 = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Icu_StartSignalMeasurement(18);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(9,&DutyCycle1);
    Icu_GetDutyCycleValues(18,&DutyCycle0);
    Icu_StopSignalMeasurement(9);
    Icu_StopSignalMeasurement(18);
    PSPRINTF("%d %d %d %d\n",DutyCycle0.ActiveTime,DutyCycle0.PeriodTime,DutyCycle1.ActiveTime,DutyCycle1.PeriodTime);
}

void icu_70(void)
{
    Icu_DutyCycleType DutyCycle0 = {0};
    Icu_DutyCycleType DutyCycle1 = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(10);
    Icu_StartSignalMeasurement(19);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(10,&DutyCycle1);
    Icu_GetDutyCycleValues(19,&DutyCycle0);
    Icu_StopSignalMeasurement(10);
    Icu_StopSignalMeasurement(19);
    PSPRINTF("%d %d %d %d\n",DutyCycle0.ActiveTime,DutyCycle0.PeriodTime,DutyCycle1.ActiveTime,DutyCycle1.PeriodTime);
}

void icu_71(void)
{
    Icu_DutyCycleType DutyCycle0 = {0};
    Icu_DutyCycleType DutyCycle1 = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Icu_StartSignalMeasurement(18);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(9,&DutyCycle1);
    Icu_GetDutyCycleValues(18,&DutyCycle0);
    Icu_StopSignalMeasurement(9);
    Icu_StopSignalMeasurement(18);
    PSPRINTF("%d %d %d %d\n",DutyCycle0.ActiveTime,DutyCycle0.PeriodTime,DutyCycle1.ActiveTime,DutyCycle1.PeriodTime);
}

void icu_72(void)
{
    Icu_DutyCycleType DutyCycle0 = {0};
    Icu_DutyCycleType DutyCycle1 = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(10);
    Icu_StartSignalMeasurement(19);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(10,&DutyCycle1);
    Icu_GetDutyCycleValues(19,&DutyCycle0);
    Icu_StopSignalMeasurement(10);
    Icu_StopSignalMeasurement(19);
    PSPRINTF("%d %d %d %d\n",DutyCycle0.ActiveTime,DutyCycle0.PeriodTime,DutyCycle1.ActiveTime,DutyCycle1.PeriodTime);
}

void icu_73(void)
{
    Icu_DutyCycleType DutyCycle0 = {0};
    Icu_DutyCycleType DutyCycle1 = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Icu_StartSignalMeasurement(18);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(9,&DutyCycle1);
    Icu_GetDutyCycleValues(18,&DutyCycle0);
    Icu_StopSignalMeasurement(9);
    Icu_StopSignalMeasurement(18);
    PSPRINTF("%d %d %d %d\n",DutyCycle0.ActiveTime,DutyCycle0.PeriodTime,DutyCycle1.ActiveTime,DutyCycle1.PeriodTime);
}

void icu_74(void)
{
    Icu_DutyCycleType DutyCycle0 = {0};
    Icu_DutyCycleType DutyCycle1 = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(10);
    Icu_StartSignalMeasurement(19);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(10,&DutyCycle1);
    Icu_GetDutyCycleValues(19,&DutyCycle0);
    Icu_StopSignalMeasurement(10);
    Icu_StopSignalMeasurement(19);
    PSPRINTF("%d %d %d %d\n",DutyCycle0.ActiveTime,DutyCycle0.PeriodTime,DutyCycle1.ActiveTime,DutyCycle1.PeriodTime);
}


void icu_99(void)
{
   VAR(uint32, AUTOMATIC) u32Icu_state = 0U;
   Icu_Init(&Icu_Cfg);
   Icu_EnableEdgeDetection(3);
   u32Icu_state = Icu_GetInputState(3);
   PSPRINTF("%d\n",u32Icu_state);
   Gpt_Stm_LLD_DelayMs(STM1,10U);
   Icu_EnableNotification(3);
   u32Icu_state = Icu_GetInputState(3);
   PSPRINTF("%d\n",u32Icu_state);
   Gpt_Stm_LLD_DelayMs(STM1,30U);
   u32Icu_state = Icu_GetInputState(3);
   PSPRINTF("%d\n",u32Icu_state);
   Icu_SetActivationCondition(3,ICU_FALLING_EDGE);
   Icu_EnableNotification(3);
   Gpt_Stm_LLD_DelayMs(STM1,10U);
   u32Icu_state = Icu_GetInputState(3);
   PSPRINTF("%d\n",u32Icu_state);
   Icu_DeInit();
}

void icu_100(void)
{
   VAR(uint32, AUTOMATIC) u32Icu_state = 0U;
   Icu_Init(&Icu_Cfg);
   Icu_EnableEdgeDetection(4);
   u32Icu_state = Icu_GetInputState(4);
   PSPRINTF("%d\n",u32Icu_state);
   Gpt_Stm_LLD_DelayMs(STM1,10U);
   Icu_EnableNotification(4);
   u32Icu_state = Icu_GetInputState(4);
   PSPRINTF("%d\n",u32Icu_state);
   Gpt_Stm_LLD_DelayMs(STM1,30U);
   u32Icu_state = Icu_GetInputState(4);
   PSPRINTF("%d\n",u32Icu_state);
   Icu_SetActivationCondition(4,ICU_RISING_EDGE);
   Icu_EnableNotification(4);
   Gpt_Stm_LLD_DelayMs(STM1,10U);
   u32Icu_state = Icu_GetInputState(4);
   PSPRINTF("%d\n",u32Icu_state);
   Icu_DeInit();
}

void icu_101(void)
{
   VAR(uint32, AUTOMATIC) u32Icu_state = 0U;
   Icu_Init(&Icu_Cfg);
   Icu_EnableEdgeDetection(5);
   u32Icu_state = Icu_GetInputState(5);
   PSPRINTF("%d\n",u32Icu_state);
   Gpt_Stm_LLD_DelayMs(STM1,10U);
   Icu_EnableNotification(5);
   u32Icu_state = Icu_GetInputState(5);
   PSPRINTF("%d\n",u32Icu_state);
   Gpt_Stm_LLD_DelayMs(STM1,30U);
   u32Icu_state = Icu_GetInputState(5);
   PSPRINTF("%d\n",u32Icu_state);
   Icu_SetActivationCondition(5,ICU_BOTH_EDGES);
   Icu_EnableNotification(5);
   Gpt_Stm_LLD_DelayMs(STM1,10U);
   u32Icu_state = Icu_GetInputState(5);
   PSPRINTF("%d\n",u32Icu_state);
   Icu_DeInit();
}

void icu_102(void)
{
   VAR(boolean, AUTOMATIC) bstatus = FALSE;
   Icu_Init(&Icu_Cfg);
   Icu_SetActivationCondition(15,ICU_RISING_EDGE);
   Icu_EnableNotification(15);
   Icu_EnableWakeup(15);
   bstatus = Icu_GetWakeupStatus(15);
   PSPRINTF("%s  is E_OK, bstatus:%d\r\n",__FUNCTION__,bstatus);
   Icu_DeInit();
}

void icu_103(void)
{
   VAR(boolean, AUTOMATIC) bstatus = FALSE;
   Icu_Init(&Icu_Cfg);
   Icu_SetActivationCondition(15,ICU_RISING_EDGE);
   Icu_EnableNotification(15);
   Icu_EnableWakeup(15);
   bstatus = Icu_GetWakeupStatus(15);
   PSPRINTF("%s  is E_OK, bstatus:%d\r\n",__FUNCTION__,bstatus);
   Icu_DisableWakeup(15);
   bstatus = Icu_GetWakeupStatus(15);
   PSPRINTF("%s  is E_OK, bstatus:%d\r\n",__FUNCTION__,bstatus);
   Icu_DeInit();
}

void icu_104(void)
{
   Icu_Init(&Icu_Cfg);
   Icu_SetMode(ICU_MODE_NORMAL);
   Icu_SetActivationCondition(15,ICU_RISING_EDGE);
   Icu_EnableNotification(15);
   Icu_EnableWakeup(15);
   Icu_EnableEdgeCount(15);
   Icu_SetMode(ICU_MODE_SLEEP);
   Gpt_Stm_LLD_DelayMs(STM1,100U);
   Icu_CheckWakeup(0);
   PSPRINTF("icu_104 is OK\n");
   Icu_DeInit();
}

void icu_105(void)
{
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value = 0U;
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value1 = 0U;
    Icu_Init(&Icu_Cfg);
    /*SignalMeasurement  LowTime*/
    Icu_StartSignalMeasurement(11);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value = Icu_GetTimeElapsed(11);
    PSPRINTF("%d\n",u32Icu_value);
    Icu_StopSignalMeasurement(11);
    u32Icu_value = Icu_GetTimeElapsed(11);
    PSPRINTF("%d\n",u32Icu_value);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value1 = Icu_GetTimeElapsed(11);
    PSPRINTF("%d\n",u32Icu_value1);/*0*/

    if (u32Icu_value && (u32Icu_value1 == 0))
    {
        PSPRINTF("elapse test ok\n");
    }
    else
    {
        PSPRINTF("elapse test not ok\n");
    }
}

void icu_106(void)
{
    /*SignalMeasurement  periodTime both edges*/
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value = 0U;
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value1 = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(12);
    Gpt_Stm_LLD_DelayMs(STM1,500U);
    u32Icu_value = Icu_GetTimeElapsed(12);
    PSPRINTF("%d\n",u32Icu_value);
    Icu_StopSignalMeasurement(12);
    u32Icu_value = Icu_GetTimeElapsed(12);
    PSPRINTF("%d\n",u32Icu_value);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value1 = Icu_GetTimeElapsed(12);
    PSPRINTF("%d\n",u32Icu_value1);/*0*/

    if (u32Icu_value && (u32Icu_value1 == 0))
    {
        PSPRINTF("elapse test ok\n");
    }
    else
    {
        PSPRINTF("elapse test not ok\n");
    }
}

void icu_107(void)
{
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value = 0U;
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value1 = 0U;
    Icu_Init(&Icu_Cfg);
    /*SignalMeasurement  highTime*/
    Icu_StartSignalMeasurement(13);
    Gpt_Stm_LLD_DelayMs(STM1,500U);
    u32Icu_value = Icu_GetTimeElapsed(13);
    PSPRINTF("%d\n",u32Icu_value);/*0*/
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_StopSignalMeasurement(13);
    u32Icu_value = Icu_GetTimeElapsed(13);
    PSPRINTF("%d\n",u32Icu_value);/*0*/
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value1 = Icu_GetTimeElapsed(13);
    PSPRINTF("%d\n",u32Icu_value1);/*0*/


}

void icu_108(void)
{
    uint32 BufferPtr[10];
    uint32 i = 0;
    uint32 delay = 500U;
    VAR(Icu_IndexType, AUTOMATIC) u16Icu_value = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(6,ICU_FALLING_EDGE);
    Icu_StartTimestamp(6,BufferPtr,10,100);
    Gpt_Stm_LLD_DelayMs(STM1,delay);
    Icu_StopTimestamp(6);
    u16Icu_value = Icu_GetTimestampIndex(6);
    PSPRINTF("index:%d, timestamp: ",u16Icu_value);
    for(i=0; i<u16Icu_value; i++)
    {
    	PSPRINTF("%lu ", BufferPtr[i]);
    }
    PSPRINTF("\r\n");
    if (((BufferPtr[1] - BufferPtr[0]) > (0.9*1000)) && ((BufferPtr[1] - BufferPtr[0]) < (1.1*1000)))
    {
        PSPRINTF("timestamp test ok\r\n");
    }
    else
    {
        PSPRINTF("timestamp test not ok\r\n");
    }
    Icu_DeInit();
}

void icu_109(void)
{
    uint32 BufferPtr[10];
    uint32 i = 0;
    uint32 delay = 500U;
    VAR(Icu_IndexType, AUTOMATIC) u16Icu_value = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(7,ICU_RISING_EDGE);
    Icu_StartTimestamp(7,BufferPtr,10,100);
    Gpt_Stm_LLD_DelayMs(STM1,delay);
    Icu_StopTimestamp(7);
    u16Icu_value = Icu_GetTimestampIndex(7);
    PSPRINTF("index:%d, timestamp: ",u16Icu_value);
    for(i=0; i<u16Icu_value; i++)
    {
    	PSPRINTF("%lu ", BufferPtr[i]);
    }
    PSPRINTF("\r\n");
    if (((BufferPtr[1] - BufferPtr[0]) > (0.9*1000)) && ((BufferPtr[1] - BufferPtr[0]) < (1.1*1000)))
    {
        PSPRINTF("timestamp test ok\r\n");
    }
    else
    {
        PSPRINTF("timestamp test not ok\r\n");
    }
    Icu_DeInit();
}

void icu_110(void)
{
    uint32 BufferPtr[10];
    uint32 i = 0;
    uint32 delay = 500U;
    VAR(Icu_IndexType, AUTOMATIC) u16Icu_value = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(8,ICU_BOTH_EDGES);
    Icu_StartTimestamp(8,BufferPtr,10,100);
    Gpt_Stm_LLD_DelayMs(STM1,delay);
    Icu_StopTimestamp(8);
    u16Icu_value = Icu_GetTimestampIndex(8);
    PSPRINTF("index:%d, timestamp: ",u16Icu_value);
    for(i=0; i<u16Icu_value; i++)
    {
    	PSPRINTF("%lu ", BufferPtr[i]);
    }
    PSPRINTF("\r\n");
    if (((BufferPtr[2] - BufferPtr[0]) > (0.9*1000)) && ((BufferPtr[2] - BufferPtr[0]) < (1.1*1000)))
    {
        PSPRINTF("timestamp test ok\r\n");
    }
    else
    {
        PSPRINTF("timestamp test not ok\r\n");
    }
    Icu_DeInit();

}

void icu_111(void)
{
    VAR(Icu_EdgeNumberType, AUTOMATIC) u16Icu_value = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_EnableEdgeCount(2);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(2);
    u16Icu_value = Icu_GetEdgeNumbers(2);
    PSPRINTF("%d\n",u16Icu_value);
    Icu_ResetEdgeCount(2);
    u16Icu_value = Icu_GetEdgeNumbers(2);
    PSPRINTF("%d\n",u16Icu_value);
}

void icu_112(void)
{
   Icu_SetMode(ICU_MODE_NORMAL);
   PSPRINTF("icu_112 is OK if ReportError is not printed\n");
}

void icu_113(void)
{
  Icu_Init(&Icu_Cfg);
  Icu_SetActivationCondition(14,ICU_FALLING_EDGE);/*not wakeup capable*/
  Icu_SetMode(ICU_MODE_SLEEP);
  Icu_EnableWakeup(14);
  PSPRINTF("icu_113 is OK if ReportError is not printed\n");
}

void icu_114(void)
{
  Icu_DeInit();
  Icu_DisableWakeup(IcuConf_IcuChannel_IcuChannel_0);
  PSPRINTF("icu_114 is OK if ReportError is not printed\n");
}

void icu_115(void)
{
    Icu_DeInit();
    Icu_EnableWakeup(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_115 is OK if ReportError is not printed\n");
}

void icu_116(void)
{
    Icu_DeInit();
    Icu_SetActivationCondition(IcuConf_IcuChannel_IcuChannel_0,ICU_FALLING_EDGE);
    PSPRINTF("icu_116 is OK if ReportError is not printed\n");
}

void icu_117(void)
{
    Icu_DeInit();
    Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_117 is OK if ReportError is not printed\n");
}

void icu_118(void)
{
    Icu_DeInit();
    Icu_GetInputState(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_118 is OK if ReportError is not printed\n");   
}

void icu_119(void)
{
    uint32 BufferPtr[10];
    Icu_DeInit();
    Icu_StartTimestamp(IcuConf_IcuChannel_IcuChannel_0,BufferPtr,10,100);
    PSPRINTF("icu_119 is OK if ReportError is not printed\n");
}

void icu_120(void)
{
	Icu_DeInit();
    Icu_StartTimestamp(IcuConf_IcuChannel_IcuChannel_0,NULL_PTR,5U,3U);
    PSPRINTF("icu_120 is OK if ReportError is not printed\n");
}

void icu_121(void)
{
    uint32 BufferPtr[10];
    Icu_DeInit();
    Icu_StartTimestamp(IcuConf_IcuChannel_IcuChannel_0,BufferPtr,0U,3U);
    PSPRINTF("icu_121 is OK if ReportError is not printed\n");
}

void icu_122(void)
{
    Icu_DeInit();
    Icu_StopTimestamp(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_122 is OK if ReportError is not printed\n");  
}

void icu_123(void)
{
    VAR(Icu_IndexType, AUTOMATIC) u16Icu_value = 0U;
    Icu_DeInit();
    u16Icu_value = Icu_GetTimestampIndex(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("%d\n",u16Icu_value); /*0*/
}

void icu_124(void)
{
    Icu_DeInit();
    Icu_ResetEdgeCount(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_124 is OK if ReportError is not printed\n");    
}

void icu_125(void)
{
    Icu_DeInit();
    Icu_EnableEdgeCount(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_125 is OK if ReportError is not printed\n");     
}

void icu_126(void)
{
    VAR(Icu_IndexType, AUTOMATIC) u16Icu_value = 0U;
    Icu_DeInit();
    u16Icu_value = Icu_GetEdgeNumbers(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("%d\n",u16Icu_value); /*0*/
}

void icu_127(void)
{
    VAR(Icu_ValueType, AUTOMATIC) u16Icu_value = 0U;
    Icu_DeInit();
    u16Icu_value = Icu_GetTimeElapsed(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("%d\n",u16Icu_value); /*0*/
}

void icu_128(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_DeInit();
    Icu_GetDutyCycleValues(IcuConf_IcuChannel_IcuChannel_0,&DutyCycle);
    PSPRINTF("icu_128 is OK if ReportError is not printed\n");
}

void icu_129(void)
{
    Icu_DeInit();
    Icu_StartSignalMeasurement(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_129 is OK if ReportError is not printed\n");    
}

void icu_130(void)
{
    Icu_DeInit();
    Icu_StopSignalMeasurement(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_130 is OK if ReportError is not printed\n");    
}

void icu_131(void)
{
    Icu_DeInit();
    Icu_EnableEdgeDetection(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_131 is OK if ReportError is not printed\n");    
}

void icu_132(void)
{
    Icu_DeInit();
    Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("icu_132 is OK if ReportError is not printed\n");  
}

void icu_133(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_0);
    Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_0);
    Icu_DeInit();
    PSPRINTF("icu_133 is OK if ReportError is not printed\n");  
}

void icu_134(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_DisableWakeup(IcuConf_IcuChannel_IcuChannel_0);
    Icu_DeInit();
    PSPRINTF("icu_134 is OK if ReportError is not printed\n");  
}

void icu_135(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_EnableEdgeCount(46);
    Icu_DisableEdgeCount(46);
    Icu_DeInit();
    PSPRINTF("icu_135 is OK if ReportError is not printed\n");  
}

void icu_136(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(IcuConf_IcuChannel_IcuChannel_0);
    Icu_StopSignalMeasurement(IcuConf_IcuChannel_IcuChannel_0);
    Icu_DeInit();
    PSPRINTF("icu_136 is OK if ReportError is not printed\n"); 
}

void icu_137(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_EnableWakeup(14);/*no wakeup capable*/
    PSPRINTF("icu_137 is OK if ReportError is not printed\n"); 
}

void icu_138(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(IcuConf_IcuChannel_IcuChannel_0,ICU_RISING_EDGE);
    PSPRINTF("icu_138 is OK if ReportError is not printed\n");
}

/*emios*/
void icu_139(void)
{
	Icu_EdgeNumberType EdgeNumber = 0;
	Icu_Init(&Icu_Cfg);
	Icu_SetMode(0);
	Icu_ResetEdgeCount(2);
	Icu_EnableEdgeCount(2);
	Gpt_Stm_LLD_DelayMs(STM1,100U);
	Icu_DisableEdgeCount(2);
	EdgeNumber = Icu_GetEdgeNumbers(2);
	PSPRINTF("%d\n",EdgeNumber);
}

void icu_140(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(IcuConf_IcuChannel_IcuChannel_0);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(IcuConf_IcuChannel_IcuChannel_0,&DutyCycle);
    Icu_StopSignalMeasurement(IcuConf_IcuChannel_IcuChannel_0);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

// void icu_141(void)
// {
//     uint32 BufferPtr[10];
//     uint32 i = 0;
//     uint32 delay = 500U;
//     VAR(Icu_IndexType, AUTOMATIC) u16Icu_value = 0U;
//     Icu_Init(&Icu_Cfg);
//     Icu_SetActivationCondition(1,ICU_FALLING_EDGE);
//     Icu_StartTimestamp(1,BufferPtr,10,100);
//     Gpt_Stm_LLD_DelayMs(STM1,delay);
//     Icu_StopTimestamp(1);
//     u16Icu_value = Icu_GetTimestampIndex(1);
//     PSPRINTF("index:%d, timestamp: ",u16Icu_value);
//     for(i=0; i<u16Icu_value; i++)
//     {
//     	PSPRINTF("%lu ", BufferPtr[i]);
//     }
//     PSPRINTF("\r\n");
//     if (((BufferPtr[1] - BufferPtr[0]) > (0.9*1000)) && ((BufferPtr[1] - BufferPtr[0]) < (1.1*1000)))
//     {
//         PSPRINTF("timestamp test ok\r\n");
//     }
//     else
//     {
//         PSPRINTF("timestamp test not ok\r\n");
//     }
//     Icu_DeInit();
// }

// static volatile int SignalMeasurement_flag = 0;
// void IcueMiosignalNotification_0(void)
// {
// 	Icu_DutyCycleType DutyCycle = {0};

// 	SignalMeasurement_flag ++;
// 	if ((SignalMeasurement_flag %20) == 0 )
// 	{
// 		Icu_GetDutyCycleValues(1,&DutyCycle);

// 		PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
// 		if (SignalMeasurement_flag >= 100)
// 		{
// 			Icu_StopSignalMeasurement(31);
// 			SignalMeasurement_flag= 0;
// 		}
// 	}
// }
// void icu_142(void)
// {

// //    Icu_DutyCycleType DutyCycle = {0};
// //    Icu_Init(&Icu_Cfg);
// //    Icu_StartSignalMeasurement(31);
// //    //SignalMeasurement_flag == 0;
// //    //while(SignalMeasurement_flag == 0);
// //    //Gpt_Stm_LLD_DelayMs(STM1,5000U);
//     Icu_DutyCycleType DutyCycle = {0};
//     Icu_Init(&Icu_Cfg);
//     Icu_StartSignalMeasurement(0);
//     Gpt_Stm_LLD_DelayMs(STM1,100U);
//     Icu_GetDutyCycleValues(0,&DutyCycle);
//     //Icu_StopSignalMeasurement(0);
//     PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);

// }

// void icu_143(void)
// {
//     Icu_EdgeNumberType EdgeNumber = 0;
//     Icu_Init(&Icu_Cfg);
//     Icu_SetMode(0);
//     Icu_ResetEdgeCount(22);
//     Icu_EnableEdgeCount(22);
//     Gpt_Stm_LLD_DelayMs(STM1,100U);
//     Icu_DisableEdgeCount(22);
//     EdgeNumber = Icu_GetEdgeNumbers(22);
//     PSPRINTF("%d\n",EdgeNumber);
// }

// void icu_144(void)
// {
//     Icu_EdgeNumberType EdgeNumber = 0;
//     Icu_Init(&Icu_Cfg);
//     Icu_SetMode(0);
//     Icu_ResetEdgeCount(23);
//     Icu_EnableEdgeCount(23);
//     Gpt_Stm_LLD_DelayMs(STM1,100U);
//     Icu_DisableEdgeCount(23);
//     EdgeNumber = Icu_GetEdgeNumbers(23);
//     PSPRINTF("%d\n",EdgeNumber);
// }

// void icu_145(void)
// {
//     Icu_EdgeNumberType EdgeNumber = 0;
//     Icu_Init(&Icu_Cfg);
//     Icu_SetMode(0);
//     Icu_ResetEdgeCount(24);
//     Icu_EnableEdgeCount(24);
//     Gpt_Stm_LLD_DelayMs(STM1,100U);
//     Icu_DisableEdgeCount(24);
//     EdgeNumber = Icu_GetEdgeNumbers(24);
//     PSPRINTF("%d\n",EdgeNumber);
// }

// void icu_146(void)
// {
//     Icu_EdgeNumberType EdgeNumber = 0;
//     Icu_Init(&Icu_Cfg);
//     Icu_SetMode(0);
//     Icu_ResetEdgeCount(25);
//     Icu_EnableEdgeCount(25);
//     Gpt_Stm_LLD_DelayMs(STM1,100U);
//     Icu_DisableEdgeCount(25);
//     EdgeNumber = Icu_GetEdgeNumbers(25);
//     PSPRINTF("%d\n",EdgeNumber);
// }
/*Ver1.6 project service*/

void icu_141(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(0);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(0,&DutyCycle);
    Icu_StopSignalMeasurement(0);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_142(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(1);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(1,&DutyCycle);
    Icu_StopSignalMeasurement(1);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_143(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(2);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(2,&DutyCycle);
    Icu_StopSignalMeasurement(2);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_144(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(3);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(3,&DutyCycle);
    Icu_StopSignalMeasurement(3);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_145(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(4);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(4,&DutyCycle);
    Icu_StopSignalMeasurement(4);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_146(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(5);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(5,&DutyCycle);
    Icu_StopSignalMeasurement(5);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}



/*Ver1.6 project service end*/
void icu_147(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(26);
    Icu_EnableEdgeCount(26);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(26);
    EdgeNumber = Icu_GetEdgeNumbers(26);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_148(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(27);
    Icu_EnableEdgeCount(27);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(27);
    EdgeNumber = Icu_GetEdgeNumbers(27);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_149(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(28);
    Icu_EnableEdgeCount(28);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(28);
    EdgeNumber = Icu_GetEdgeNumbers(28);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_150(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(29);
    Icu_EnableEdgeCount(29);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(29);
    EdgeNumber = Icu_GetEdgeNumbers(29);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_151(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(30);
    Icu_EnableEdgeCount(30);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(30);
    EdgeNumber = Icu_GetEdgeNumbers(30);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_152(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(31);
    Icu_EnableEdgeCount(31);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(31);
    EdgeNumber = Icu_GetEdgeNumbers(31);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_153(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(32);
    Icu_EnableEdgeCount(32);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(32);
    EdgeNumber = Icu_GetEdgeNumbers(32);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_154(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(33);
    Icu_EnableEdgeCount(33);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(33);
    EdgeNumber = Icu_GetEdgeNumbers(33);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_155(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(34);
    Icu_EnableEdgeCount(34);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(34);
    EdgeNumber = Icu_GetEdgeNumbers(34);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_156(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(35);
    Icu_EnableEdgeCount(35);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(35);
    EdgeNumber = Icu_GetEdgeNumbers(35);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_157(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(36);
    Icu_EnableEdgeCount(36);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(36);
    EdgeNumber = Icu_GetEdgeNumbers(36);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_158(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(37);
    Icu_EnableEdgeCount(37);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(37);
    EdgeNumber = Icu_GetEdgeNumbers(37);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_159(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(38);
    Icu_EnableEdgeCount(38);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(38);
    EdgeNumber = Icu_GetEdgeNumbers(38);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_160(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(39);
    Icu_EnableEdgeCount(39);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(39);
    EdgeNumber = Icu_GetEdgeNumbers(39);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_161(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(40);
    Icu_EnableEdgeCount(40);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(40);
    EdgeNumber = Icu_GetEdgeNumbers(40);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_162(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(41);
    Icu_EnableEdgeCount(41);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(41);
    EdgeNumber = Icu_GetEdgeNumbers(41);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_163(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(42);
    Icu_EnableEdgeCount(42);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(42);
    EdgeNumber = Icu_GetEdgeNumbers(42);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_164(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(43);
    Icu_EnableEdgeCount(43);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(43);
    EdgeNumber = Icu_GetEdgeNumbers(43);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_165(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(44);
    Icu_EnableEdgeCount(44);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(44);
    EdgeNumber = Icu_GetEdgeNumbers(44);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_166(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(45);
    Icu_EnableEdgeCount(45);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(45);
    EdgeNumber = Icu_GetEdgeNumbers(45);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_167(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(46);
    Icu_EnableEdgeCount(46);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(46);
    EdgeNumber = Icu_GetEdgeNumbers(46);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_168(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(47);
    Icu_EnableEdgeCount(47);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(47);
    EdgeNumber = Icu_GetEdgeNumbers(47);
    PSPRINTF("%d\n",EdgeNumber);
}

/*EMIOS*/
void icu_258(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(3);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(3,&DutyCycle);
    Icu_StopSignalMeasurement(3);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}
void icu_259(void)
{
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value = 0U;
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value1 = 0U;
    Icu_Init(&Icu_Cfg);
    /*SignalMeasurement  LowTime*/
    Icu_StartSignalMeasurement(24);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value = Icu_GetTimeElapsed(24);
    PSPRINTF("%d\n",u32Icu_value);
    Icu_StopSignalMeasurement(24);
    u32Icu_value = Icu_GetTimeElapsed(24);
    PSPRINTF("%d\n",u32Icu_value);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value1 = Icu_GetTimeElapsed(24);
    PSPRINTF("%d\n",u32Icu_value1);/*0*/

    if (u32Icu_value && (u32Icu_value1 == 0))
    {
        PSPRINTF("elapse test ok\n");
    }
    else
    {
        PSPRINTF("elapse test not ok\n");
    }
}

void icu_260(void)
{
    uint32 BufferPtr[10];
    uint32 i = 0;
    uint32 delay = 500U;
    VAR(Icu_IndexType, AUTOMATIC) u16Icu_value = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(4,ICU_FALLING_EDGE);
    Icu_StartTimestamp(4,BufferPtr,10,100);
    Gpt_Stm_LLD_DelayMs(STM1,delay);
    Icu_StopTimestamp(4);
    u16Icu_value = Icu_GetTimestampIndex(4);
    PSPRINTF("index:%d, timestamp: ",u16Icu_value);
    for(i=0; i<u16Icu_value; i++)
    {
    	PSPRINTF("%lu ", BufferPtr[i]);
    }
    PSPRINTF("\r\n");
    
    Icu_DeInit();
}

void icu_261(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(1);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(1,&DutyCycle);
    Icu_StopSignalMeasurement(1);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_262(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(5);
    Gpt_Stm_LLD_DelayMs(STM1,500U);
    Icu_GetDutyCycleValues(5,&DutyCycle);
    //Icu_StopSignalMeasurement(5);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_263(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(6);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(6,&DutyCycle);
    Icu_StopSignalMeasurement(6);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_264(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(7);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(7,&DutyCycle);
    Icu_StopSignalMeasurement(7);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_265(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(8);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(8,&DutyCycle);
    Icu_StopSignalMeasurement(8);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_266(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(9,&DutyCycle);
    Icu_StopSignalMeasurement(9);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}


void icu_267(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(10);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(10,&DutyCycle);
    Icu_StopSignalMeasurement(10);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_268(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(11);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(11,&DutyCycle);
    Icu_StopSignalMeasurement(11);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_269(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(12);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(12,&DutyCycle);
    Icu_StopSignalMeasurement(12);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_270(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(13);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(13,&DutyCycle);
    Icu_StopSignalMeasurement(13);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_271(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(14);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(14,&DutyCycle);
    Icu_StopSignalMeasurement(14);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_272(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(15);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(15,&DutyCycle);
    Icu_StopSignalMeasurement(15);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_273(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(16);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(16,&DutyCycle);
    Icu_StopSignalMeasurement(16);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_274(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(17);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(17,&DutyCycle);
    Icu_StopSignalMeasurement(17);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_275(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(18);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(18,&DutyCycle);
    Icu_StopSignalMeasurement(18);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_276(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(19);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(19,&DutyCycle);
    Icu_StopSignalMeasurement(19);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_277(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(20);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(20,&DutyCycle);
    Icu_StopSignalMeasurement(20);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_278(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(21);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(21,&DutyCycle);
    Icu_StopSignalMeasurement(21);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_279(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(22);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(22,&DutyCycle);
    Icu_StopSignalMeasurement(22);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_280(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(23);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(23,&DutyCycle);
    Icu_StopSignalMeasurement(23);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_281(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(25);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(25,&DutyCycle);
    Icu_StopSignalMeasurement(25);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}
/*emios end*/
void icu_282(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(26);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(26,&DutyCycle);
    Icu_StopSignalMeasurement(26);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_283(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(27);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(27,&DutyCycle);
    Icu_StopSignalMeasurement(27);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_284(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(28);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(28,&DutyCycle);
    Icu_StopSignalMeasurement(28);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_285(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(29);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(29,&DutyCycle);
    Icu_StopSignalMeasurement(29);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_286(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(3);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(3,&DutyCycle);
    Icu_StopSignalMeasurement(3);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

/*add Ver1.5*/

void icu_306(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(0);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(0,&DutyCycle);
    Icu_StopSignalMeasurement(0);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_307(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(1);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(1,&DutyCycle);
    Icu_StopSignalMeasurement(1);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_308(void)
{


    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value = 0U;
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value1 = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(2);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value = Icu_GetTimeElapsed(2);
    PSPRINTF("%d\n",u32Icu_value);
    Icu_StopSignalMeasurement(2);
    u32Icu_value = Icu_GetTimeElapsed(2);
    PSPRINTF("%d\n",u32Icu_value);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value1 = Icu_GetTimeElapsed(2);
    PSPRINTF("%d\n",u32Icu_value1);/*0*/

    if (u32Icu_value && (u32Icu_value1 == 0))
    {
        PSPRINTF("elapse test ok\n");
    }
    else
    {
        PSPRINTF("elapse test not ok\n");
    }
}

void icu_309(void)
{
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value = 0U;
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value1 = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(3);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value = Icu_GetTimeElapsed(3);
    PSPRINTF("%d\n",u32Icu_value);
    Icu_StopSignalMeasurement(3);
    u32Icu_value = Icu_GetTimeElapsed(3);
    PSPRINTF("%d\n",u32Icu_value);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value1 = Icu_GetTimeElapsed(3);
    PSPRINTF("%d\n",u32Icu_value1);/*0*/

    if (u32Icu_value && (u32Icu_value1 == 0))
    {
        PSPRINTF("elapse test ok\n");
    }
    else
    {
        PSPRINTF("elapse test not ok\n");
    }
}

void icu_310(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(4);
    Gpt_Stm_LLD_DelayMs(STM1,1100U);
    Icu_GetDutyCycleValues(4,&DutyCycle);
    Icu_StopSignalMeasurement(4);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_311(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(5);
    Gpt_Stm_LLD_DelayMs(STM1,1100U);
    Icu_GetDutyCycleValues(5,&DutyCycle);
    Icu_StopSignalMeasurement(5);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_312(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(6);
    Gpt_Stm_LLD_DelayMs(STM1,1100U);
    Icu_GetDutyCycleValues(6,&DutyCycle);
    Icu_StopSignalMeasurement(6);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_313(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(7);
    Gpt_Stm_LLD_DelayMs(STM1,1100U);
    Icu_GetDutyCycleValues(7,&DutyCycle);
    Icu_StopSignalMeasurement(7);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_314(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(8);
    Gpt_Stm_LLD_DelayMs(STM1,1100U);
    Icu_GetDutyCycleValues(8,&DutyCycle);
    Icu_StopSignalMeasurement(8);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_315(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Gpt_Stm_LLD_DelayMs(STM1,1100U);
    Icu_GetDutyCycleValues(9,&DutyCycle);
    Icu_StopSignalMeasurement(9);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_316(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(10);
    Gpt_Stm_LLD_DelayMs(STM1,1100U);
    Icu_GetDutyCycleValues(10,&DutyCycle);
    Icu_StopSignalMeasurement(10);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_317(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(11);
    Gpt_Stm_LLD_DelayMs(STM1,5500U);
    Icu_GetDutyCycleValues(11,&DutyCycle);
    Icu_StopSignalMeasurement(11);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_318(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(12);
    Gpt_Stm_LLD_DelayMs(STM1,5500U);
    Icu_GetDutyCycleValues(12,&DutyCycle);
    Icu_StopSignalMeasurement(12);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_319(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(13);
    Gpt_Stm_LLD_DelayMs(STM1,5500U);
    Icu_GetDutyCycleValues(13,&DutyCycle);
    Icu_StopSignalMeasurement(13);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_320(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(14);
    Gpt_Stm_LLD_DelayMs(STM1,5500U);
    Icu_GetDutyCycleValues(14,&DutyCycle);
    Icu_StopSignalMeasurement(14);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_321(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(15);
    Gpt_Stm_LLD_DelayMs(STM1,5500U);
    Icu_GetDutyCycleValues(15,&DutyCycle);
    Icu_StopSignalMeasurement(15);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_322(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(16);
    Gpt_Stm_LLD_DelayMs(STM1,5500U);
    Icu_GetDutyCycleValues(16,&DutyCycle);
    Icu_StopSignalMeasurement(16);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_323(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(17);
    Gpt_Stm_LLD_DelayMs(STM1,5500U);
    Icu_GetDutyCycleValues(17,&DutyCycle);
    Icu_StopSignalMeasurement(17);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_324(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(18);
    Gpt_Stm_LLD_DelayMs(STM1,5500U);
    Icu_GetDutyCycleValues(18,&DutyCycle);
    Icu_StopSignalMeasurement(18);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
}

void icu_325(void)
{
    uint32 BufferPtr[10];
    uint32 i = 0;
    uint32 delay = 500U;
    VAR(Icu_IndexType, AUTOMATIC) u16Icu_value = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(0,ICU_FALLING_EDGE);
    Icu_StartTimestamp(0,BufferPtr,10,100);
    Gpt_Stm_LLD_DelayMs(STM1,delay);
    Icu_StopTimestamp(0);
    u16Icu_value = Icu_GetTimestampIndex(0);
    PSPRINTF("index:%d, timestamp: ",u16Icu_value);
    for(i=0; i<u16Icu_value; i++)
    {
    	PSPRINTF("%lu ", BufferPtr[i]);
    }
    PSPRINTF("\r\n");
    if (((BufferPtr[1] - BufferPtr[0]) > (0.9*1000)) && ((BufferPtr[1] - BufferPtr[0]) < (1.1*1000)))
    {
        PSPRINTF("timestamp test ok\r\n");
    }
    else
    {
        PSPRINTF("timestamp test not ok\r\n");
    }
    Icu_DeInit();
}

void icu_326(void)
{
	   VAR(boolean, AUTOMATIC) bstatus = FALSE;
	   Icu_Init(&Icu_Cfg);
	   Icu_SetActivationCondition(1,ICU_RISING_EDGE);
	   Icu_EnableNotification(1);
	   Icu_EnableWakeup(1);
	   bstatus = Icu_GetWakeupStatus(1);
	   PSPRINTF("%s  is E_OK, bstatus:%d\r\n",__FUNCTION__,bstatus);
	   Icu_DeInit();
}

void icu_327(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_CheckWakeup(100);
    PSPRINTF("icu_327 is OK if ReportError is not printed\n");
}

void icu_328(void)
{
	Icu_DutyCycleType DutyCycle = {0};
    Icu_InputStateType type = ICU_IDLE;
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(9,&DutyCycle);
    Icu_StopSignalMeasurement(9);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    type = Icu_GetInputState(9);
    PSPRINTF("%d\n",type);
}

void icu_329(void)
{
    Icu_Init(&Icu_Cfg);
    Icu_GetVersionInfo(NULL_PTR);
    PSPRINTF("icu_329 is OK if ReportError is not printed\n");
}

void icu_330(void)
{
    Std_VersionInfoType versioninfo;
    Icu_Init(&Icu_Cfg);
    Icu_GetVersionInfo(&versioninfo);
    PSPRINTF("icu_330 is OK, vendorID:%d\n moduleID:%d\n sw_major_version:%d\n sw_minor_version:%d\n sw_patch_version:%d\n", versioninfo.vendorID, versioninfo.moduleID, versioninfo.sw_major_version, versioninfo.sw_minor_version, versioninfo.sw_patch_version);
}

// void icu_331(void)
// {
//     Icu_Init(&Icu_Cfg);
//     Icu_StartSignalMeasurement(10);
//     Icu_StartSignalMeasurement(9);
//     Icu_case_id_10ms = 331;
//     TesterDemoICU = TRUE;
//     Icu_case_id_main = 1;
// }

// void icu_331_1(void)
// {
//     Icu_DutyCycleType DutyCycle = {0};
   

//     if(Icu_GetInputState(10) != ICU_ACTIVE)
//     {
//     	return;
//     }
//     //Icu_StopSignalMeasurement(10);
//     Icu_GetDutyCycleValues(10,&DutyCycle);
//     //Icu_StartSignalMeasurement(10);
//     PSPRINTF("gpt_callback:%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
// }

// void ICU_GPT_Callback_10ms_Function()
// {
//     switch (Icu_case_id_10ms)
//     {
//         case 331:
//         {
//             icu_331_1();
//             break;
//         }
//         default:
//         {
//             /**/
//             break;
//         }
//     }
// }

// void ICU_GPT_Callback_20ms_Function()
// {
//     switch (Icu_case_id_20ms)
//     {
//         case 332:
//         {
//             //icu_332_1();
//             break;
//         }
//         default:
//         {
//             /**/
//             break;
//         }
//     }
// }

// void ICU_GPT_Callback_30ms_Function()
// {
//     switch (Icu_case_id_30ms)
//     {
//         case 333:
//         {
//             //icu_333_1();
//             break;
//         }
//         default:
//         {
//             /**/
//             break;
//         }
//     }
// }
// void icu_main()
// {
//     if(Icu_case_id_main == 1)
//     {
//         Icu_DutyCycleType DutyCycle = {0};
//         if(Icu_GetInputState(9) != ICU_ACTIVE)
//         {
//         	return;
//         }
//        // Icu_StopSignalMeasurement(9);
//         Icu_GetDutyCycleValues(9,&DutyCycle);
//         //Icu_StartSignalMeasurement(9);
//         PSPRINTF("main:%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
//     }
// }


int icu_func(int argc, char *agrv[])
{

    if ((argc > 3) || (argc < 2)) {
        PSPRINTF("error: The number of parameters exceeds 3 or is less than 2\n");
        return 1;
    }

    if (argc == 2)
    {
        if (!strcmp(agrv[1], "help"))
        {
            PSPRINTF("help ----- CMD ------- ID of the test case\r\n");
                    
            for(uint16 i = 0; i < ICU_TEST_CASE_MAX; i++)
            {
                PSPRINTF("%s\n", icu_funcs[i].name);
            }
        }
        else
        {
            for(uint16 i = 0; i < ICU_TEST_CASE_MAX; i++)
            {
                if(!strcmp(agrv[1], icu_funcs[i].name))
                {
                    icu_funcs[i].icufunc();
                    return 0;
                }
            }
            PSPRINTF("error: Input invalid parameters[%s], please Use the 'Icu_test help' command to see the supported test instructions\n", agrv[1]);
        }
    }
    return 0;

}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), icu_test, icu_func, deint or number of test case);
