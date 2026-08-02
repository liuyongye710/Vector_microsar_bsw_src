# *********************************************************************************************************************
#   COPYRIGHT
#   -------------------------------------------------------------------------------------------------------------------
# 
#                 This software is copyright protected and proprietary to Vector Informatik GmbH.
#                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
#                 All other rights remain with Vector Informatik GmbH.
#   -------------------------------------------------------------------------------------------------------------------
#   FILE DESCRIPTION
#   -------------------------------------------------------------------------------------------------------------------
#           File:  Rte_defs.mak
#         Config:  FAW_MultiCore297_Demo.dpa
#    ECU-Project:  iECU
# 
#      Generator:  MICROSAR RTE Generator Version 4.18.0
#                  RTE Core Version 1.18.0
#        License:  Unlimited license CBD1600956 for China FAW Group Corporation
# 
#    Description:  GNU MAKEFILE (defines)
# *********************************************************************************************************************


RTE_CORE_PATH        =
RTE_OUTPUT_PATH      =

#----------------------------------------------------------------------------------------------------------------------
# MakeSupport usually includes all header-files which were in the same
# directory as the source-files automatically, but to ensure that the
# Asr-Makefiles will also work with other Basic-Make-Packages,
# it is necessary to define all include directories for this Module
#----------------------------------------------------------------------------------------------------------------------
ADDITIONAL_INCLUDES     += $(GENDATA_DIR)\Components
