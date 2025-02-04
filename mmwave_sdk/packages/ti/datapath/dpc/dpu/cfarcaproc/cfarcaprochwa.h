/**
 *   @file  cfarcaprochwa.h
 *
 *   @brief
 *      Implements Data path processing functionality.
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2018 Texas Instruments, Inc.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @defgroup CFARCA_PROC_DPU_EXTERNAL       cfarcaProc DPU External
 */

/**
@defgroup DPU_CFARCAPROC_EXTERNAL_FUNCTION            cfarcaProc DPU External Functions
@ingroup CFARCA_PROC_DPU_EXTERNAL
@brief
*   The section has a list of all the exported API which the applications need to
*   invoke in order to use the cfarcaProc DPU
*/
/**
@defgroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE      cfarcaProc DPU External Data Structures
@ingroup CFARCA_PROC_DPU_EXTERNAL
@brief
*   The section has a list of all the data structures which are exposed to the application
*/
/**
@defgroup DPU_CFARCAPROC_EXTERNAL_DEFINITIONS      cfarcaProc DPU External Definitions
@ingroup CFARCA_PROC_DPU_EXTERNAL
@brief
*   The section has a list of all the data structures which are exposed to the application
*/
/**
@defgroup DPU_CFARCAPROC_ERROR_CODE                   cfarcaProc DPU Error Codes
@ingroup CFARCA_PROC_DPU_EXTERNAL
@brief
*   The section has a list of all the error codes which are generated by the sampleProc DPU
*/

/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/
#ifndef CFARCA_PROC_HWA_H
#define CFARCA_PROC_HWA_H

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* mmWave SDK Driver/Common Include Files */
#include <ti/drivers/hwa/hwa.h>
#include <ti/drivers/edma/edma.h>

#include <ti/drivers/osal/SemaphoreP.h>

/* Datapath files */
#include <ti/datapath/dpif/dpif_detmatrix.h>
#include <ti/datapath/dpif/dpif_pointcloud.h>
#include <ti/datapath/dpedma/dpedma.h>
#include <ti/datapath/dpif/dp_error.h>
#include <ti/datapath/dpc/dpu/cfarcaproc/cfarcaproccommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup DPU_CFARCAPROC_EXTERNAL_DEFINITIONS
 *
 @{ */

/*! @brief Number of HWA parameter sets */
#define DPU_CFARCAPROCHWA_NUM_HWA_PARAM_SETS  2U

/*! @brief Alignment for memory allocation purpose of detection matrix.
 *         There is CPU access of detection matrix in the implementation.
 */
#define DPU_CFARCAPROCHWA_DET_MATRIX_BYTE_ALIGNMENT (sizeof(uint16_t))

/*! @brief Alignment for memory allocation purpose. There is CPU access of this buffer
 *         in the implementation.
 */
#define DPU_CFARCAPROCHWA_CFAR_DET_LIST_BYTE_ALIGNMENT    DPIF_CFAR_DET_LIST_CPU_BYTE_ALIGNMENT

/*! @brief Alignment for memory allocation purpose. There is CPU access of this buffer
 *         in the implementation. This is the maximum field size of the
 *         @ref DPU_CFARCAProcHWA_CfarDetOutput structure.
 */
#define DPU_CFARCAPROCHWA_HWA_MEM_OUT_DOPPLER_BYTE_ALIGNMENT    (sizeof(uint32_t))

/*! @brief Alignment for memory allocation purpose. There is CPU access of thi buffers
 *         in the implementation. This is the maximum field size of the
 *         @ref DPU_CFARCAProcHWA_CfarDetOutput structure.
 */
#define DPU_CFARCAPROCHWA_HWA_MEM_OUT_RANGE_BYTE_ALIGNMENT    (sizeof(uint32_t))

/*! @brief Alignment for memory allocation purpose. There is CPU access of this buffer
 *         in the implementation.
 */
#define DPU_CFARCAPROCHWA_DOPPLER_DET_OUT_BIT_MASK_BYTE_ALIGNMENT    (sizeof(uint32_t))

/**
@}
*/

/** @addtogroup DPU_CFARCAPROC_ERROR_CODE
 *  Base error code for the cfarcaProc DPU is defined in the
 *  \include ti/datapath/dpif/dp_error.h
 @{ */

/**
 * @brief   Error Code: Invalid argument
 */
#define DPU_CFARCAPROCHWA_EINVAL                  (DP_ERRNO_CFARCA_PROC_BASE-1)

/**
 * @brief   Error Code: Invalid detection matrix format argument
 */
#define DPU_CFARCAPROCHWA_EINVAL__DET_MATRIX_FORMAT (DP_ERRNO_CFARCA_PROC_BASE-2)

/**
  * @brief   Error Code: Invalid number of param sets
  */
#define DPU_CFARCAPROCHWA_EINVAL__NUM_PARAM_SETS    (DP_ERRNO_CFARCA_PROC_BASE-3)

/**
 * @brief   Error Code: Out of memory when allocating using MemoryP_osal
 */
#define DPU_CFARCAPROCHWA_ENOMEM                  (DP_ERRNO_CFARCA_PROC_BASE-10)

/**
 * @brief   Error Code: HWA input memory for detection matrix is not sufficient.
 */
#define DPU_CFARCAPROCHWA_ENOMEM__DET_MATRIX_EXCEEDS_HWA_INP_MEM  (DP_ERRNO_CFARCA_PROC_BASE-11)

 /**
  * @brief   Error Code: Memory not aligned for detection matrix (detMatrix.data)
  */
#define DPU_CFARCAPROCHWA_ENOMEMALIGN_DET_MATRIX                  (DP_ERRNO_CFARCA_PROC_BASE-12)

/**
 * @brief   Error Code: Memory not aligned for @ref DPU_CFARCAProcHWA_HW_Resources::cfarRngDopSnrList
 */
#define DPU_CFARCAPROCHWA_ENOMEMALIGN_CFAR_DET_LIST               (DP_ERRNO_CFARCA_PROC_BASE-13)

/**
 * @brief   Error Code: Memory not aligned for @ref DPU_CFARCAProcHWA_HW_Resources::hwaMemOutDoppler
 */
#define DPU_CFARCAPROCHWA_ENOMEMALIGN_HWA_MEM_OUT_DOPPLER         (DP_ERRNO_CFARCA_PROC_BASE-14)

/**
 * @brief   Error Code: Memory not aligned for @ref DPU_CFARCAProcHWA_HW_Resources::hwaMemOutRange
 */
#define DPU_CFARCAPROCHWA_ENOMEMALIGN_HWA_MEM_OUT_RANGE           (DP_ERRNO_CFARCA_PROC_BASE-15)

/**
 * @brief   Error Code: Insufficient memory allocated to @ref DPU_CFARCAProcHWA_HW_Resources::cfarDopplerDetOutBitMask.
 */
#define DPU_CFARCAPROCHWA_ENOMEM__INSUFFICIENT_DOP_DET_OUT_BIT_MASK  (DP_ERRNO_CFARCA_PROC_BASE-16)

/**
 * @brief   Error Code: Memory not aligned for @ref DPU_CFARCAProcHWA_HW_Resources::cfarDopplerDetOutBitMask
 */
#define DPU_CFARCAPROCHWA_ENOMEMALIGN_DOPPLER_DET_OUT_BIT_MASK   (DP_ERRNO_CFARCA_PROC_BASE-17)

/**
 * @brief   Error Code: Internal error
 */
#define DPU_CFARCAPROCHWA_EINTERNAL               (DP_ERRNO_CFARCA_PROC_BASE-20)

/**
 * @brief   Error Code: Not implemented
 */
#define DPU_CFARCAPROCHWA_ENOTIMPL                (DP_ERRNO_CFARCA_PROC_BASE-30)

 /**
  * @brief   Error Code: Semaphore error
  */
 #define DPU_CFARCAPROCHWA_ESEMA                   (DP_ERRNO_CFARCA_PROC_BASE-40)

 /**
 @}
 */

 /**
  * @brief
  *  cfarcaProc control command
  *
  * @details
  *  The enum defines the cfarcaProc supported run time command
  *
  *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
  */
 typedef enum DPU_CFARCAProcHWA_Cmd_e
 {

     /*! @brief Command to update CFAR configuration in range domain */
     DPU_CFARCAProcHWA_Cmd_CfarRangeCfg,

     /*! @brief Command to update CFAR configuration in Doppler domain */
     DPU_CFARCAProcHWA_Cmd_CfarDopplerCfg,

     /*! @brief Command to update field of view in range domain, minimum and maximum range limits */
     DPU_CFARCAProcHWA_Cmd_FovRangeCfg,

     /*! @brief Command to update field of view in Doppler domain, minimum and maximum Doppler limits */
     DPU_CFARCAProcHWA_Cmd_FovDopplerCfg
 }DPU_CFARCAProcHWA_Cmd;

/**
 * @brief
 *  CFAR HWA configuration
 *
 * @details
 *  The structure is used to hold the HWA configuration needed for CFAR
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_CFARCAProcHWA_HwaCfarConfig_t
{
    /*! @brief     HWA paramset Start index */
    uint8_t    paramSetStartIdx;

    /*! @brief     number of HWA paramset */
    uint8_t    numParamSet;
}DPU_CFARCAProcHWA_HwaCfarConfig;

/*!
 *  @brief    Detected object parameters filled by HWA CFAR
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef volatile struct DPU_CFARCAProcHWA_CfarDetOutput_t
{
    uint32_t   noise;           /*!< @brief Noise energy in CFAR cell */
    uint32_t   cellIdx  : 12;   /*!< @brief Sample index (i.e. cell under test index) */
    uint32_t   iterNum  : 12;   /*!< @brief Iteration number (i.e. REG_BCNT counter value) */
    uint32_t   reserved :  8;   /*!< @brief Reserved */
} DPU_CFARCAProcHWA_CfarDetOutput;

/*!
 *  @brief    Field of view indices
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 *
 */
typedef struct DPU_CFARCAProc_FovCfg_t
{
    /*! @brief Minimum value in meters for range, or meters/sec for doppler */
    float min;

    /*! @brief Maximum value in meters for range, or meters/sec for doppler */
    float max;
} DPU_CFARCAProc_FovCfg;

/**
 * @brief
 *  CFARCAProcHWA DPU initial configuration parameters
 *
 * @details
 *  The structure is used to hold the DPU initial configurations.
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_CFARCAProcHWA_InitParams_t
{
    /*! @brief HWA Handle */
    HWA_Handle  hwaHandle;
}DPU_CFARCAProcHWA_InitParams;

/**
 * @brief
 *  CFAR Hardware resources
 *
 * @details
 *  CFAR Hardware resources
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 *
 */
typedef struct DPU_CFARCAProcHWA_Resources_t
{
    /*! @brief     EDMA Handle */
    EDMA_Handle         edmaHandle;

    /*! @brief     EDMA configuration for CFAR data In */
    DPEDMA_ChanCfg       edmaHwaIn;

    /*! @brief     EDMA configuration for EDMA In to  trigger HWA*/
    DPEDMA_ChanCfg       edmaHwaInSignature;

    /*! @brief     HWA Configuration */
    DPU_CFARCAProcHWA_HwaCfarConfig   hwaCfg;

    /*! @brief Pointer to range/Doppler log2 magnitude detection matrix. The data buffer
     *         must be aligned to @ref DPU_CFARCAPROCHWA_DET_MATRIX_BYTE_ALIGNMENT */
    DPIF_DetMatrix      detMatrix;

    /*! @brief Pointer to CFAR output list, must be aligned to
     *         @ref DPU_CFARCAPROCHWA_CFAR_DET_LIST_BYTE_ALIGNMENT */
    DPIF_CFARDetList *cfarRngDopSnrList;

    /*! @brief Number of elements of type DPIF_cfarDetList of CFAR output list */
    uint32_t cfarRngDopSnrListSize;

    /*! @brief HWA scratch memory to page-in detection matrix. Note two contiguous M
     *         memory banks (of the 4 banks) could be allocated to this. */
    uint16_t  *hwaMemInp;

    /*! @brief Number of elements of type uint16_t of HWA memory to hold detection matrix
     *         (associated with @ref hwaMemInp) */
    uint32_t   hwaMemInpSize;

    /*! @brief HWA scratch memory for producing intermediate cfar detection list in Doppler domain,
     *         cannot be overlaid with other HWA scratch memory inputs specified in this
     *         structure. Must be different memory bank than bank(s) of @ref hwaMemInpSize.
     *         Must be aligned to @ref DPU_CFARCAPROCHWA_HWA_MEM_OUT_DOPPLER_BYTE_ALIGNMENT.
     *         Note this need not be the start of a HWA memory bank but typically it is,
     *         and is therefore naturally aligned to this alignment requirement. */
    DPU_CFARCAProcHWA_CfarDetOutput *hwaMemOutDoppler;

    /*! @brief Number of elements of type @ref DPU_CFARCAProcHWA_CfarDetOutput of
     *         HWA memory for cfar detection list in Doppler domain */
    uint32_t hwaMemOutDopplerSize;

    /*! @brief HWA scratch memory for producing intermediate cfar detection list in Range domain,
     *         cannot be overlaid with other HWA scratch memory inputs for this DPU.
     *         Must be different memory bank than bank(s) of @ref hwaMemInp.
     *         Must be aligned to @ref DPU_CFARCAPROCHWA_HWA_MEM_OUT_RANGE_BYTE_ALIGNMENT.
     *         Note this need not be the start of a HWA memory bank but typically it is,
     *         and is therefore naturally aligned to this alignment requirement */
    DPU_CFARCAProcHWA_CfarDetOutput *hwaMemOutRange;

    /*! @brief Number of elements of type @ref DPU_CFARCAProcHWA_CfarDetOutput of
     *         HWA memory for cfar detection list in Range domain */
    uint32_t hwaMemOutRangeSize;

    /*! @brief Scratch memory for Doppler cfar detection bit mask. Must be aligned to
     *         @ref DPU_CFARCAPROCHWA_DOPPLER_DET_OUT_BIT_MASK_BYTE_ALIGNMENT */
    uint32_t *cfarDopplerDetOutBitMask;

    /*! @brief Number of elements of type uint32_t of scratch memory for bit mask
     *         of Doppler cfar detections.
     *         Must be >= (numRangeBins * numDoppplerBins) / 32 */
    uint32_t cfarDopplerDetOutBitMaskSize;
} DPU_CFARCAProcHWA_HW_Resources;

/**
 * @brief
 *  HWA CFAR dynamic configuration
 *
 * @details
 *  The structure is used to hold the dynamic configuration used for CFAR
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 *
 */
typedef struct DPU_CFARCAProcHWA_DynamicConfig_t
{
    /*! @brief      CFAR configuration in range direction */
    DPU_CFARCAProc_CfarCfg *cfarCfgRange;

    /*! @brief      CFAR configuration in Doppler direction */
    DPU_CFARCAProc_CfarCfg *cfarCfgDoppler;

    /*! @brief      Field of view configuration in range domain */
    DPU_CFARCAProc_FovCfg *fovRange;

    /*! @brief      Field of view configuration in Doppler domain */
    DPU_CFARCAProc_FovCfg *fovDoppler;
} DPU_CFARCAProcHWA_DynamicConfig;

/**
 * @brief
 *  HWA CFAR static configuration
 *
 * @details
 *  The structure is used to hold the static configuration used for CFAR.
 * The following condition must be satisfied:
 *
 *    @verbatim
      numRangeBins * numDopplerBins * sizeof(uint16_t) <= 32 KB (two HWA memory banks)
      @endverbatim
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_CFARCAProcHWA_StaticConfig_t
{
    /*! @brief  Log2 of number of doppler bins */
    uint8_t     log2NumDopplerBins;

    /*! @brief  Number of range bins */
    uint16_t    numRangeBins;

    /*! @brief  Number of doppler bins */
    uint16_t    numDopplerBins;

    /*! @brief  Range conversion factor for FFT range index to meters */
    float       rangeStep;

    /*! @brief  Doppler conversion factor for Doppler FFT index to m/s */
    float       dopplerStep;

} DPU_CFARCAProcHWA_StaticConfig;

/**
 * @brief
 *  HWA CFAR configuration
 *
 * @details
 *  The structure is used to hold the HWA configuration used for CFAR
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 *
 */
typedef struct DPU_CFARCAProcHWA_Config_t
{
    /*! @brief  Hardware resources */
    DPU_CFARCAProcHWA_HW_Resources res;

    /*! @brief  Dynamic configuration */
    DPU_CFARCAProcHWA_DynamicConfig dynCfg;

    /*! @brief  Static configuration */
    DPU_CFARCAProcHWA_StaticConfig staticCfg;
}DPU_CFARCAProcHWA_Config;

/**
 * @brief
 *  Output parameters populated during Processing time
 *
 * @details
 *  The structure is used to hold the output parameters
 *
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_CFARCAProcHWA_OutParams_t
{
    /*! @brief     CFARCAProc statistics */
    DPU_CFARCAProc_Stats stats;

    /*! @brief      Number of CFAR detected points*/
    uint32_t numCfarDetectedPoints;
}DPU_CFARCAProcHWA_OutParams;

/**
 * @brief
 *  CFARHwa DPU Handle
 *
 *
 *  \ingroup DPU_CFARCAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef void* DPU_CFARCAProcHWA_Handle;

/**
 *  @b Description
 *  @n
 *      The function is CFARCAProcHWA DPU initialization function. It allocates memory to store
 *  its internal data object and returns a handle if it executes successfully.
 *
 *  @param[in]  initCfg                 Pointer to initialization configuration
 *
 *  @param[in]  errCode                 Pointer to errCode generates from the API
 *
 *  \ingroup    DPU_CFARCAPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - valid CFARCAProcHWA handle
 *  @retval
 *      Error       - NULL
 */
DPU_CFARCAProcHWA_Handle DPU_CFARCAProcHWA_init
(
    DPU_CFARCAProcHWA_InitParams *initCfg,
    int32_t*            errCode
);

/**
 *  @b Description
 *  @n
 *      The function is CFARCAProcHWA DPU configuration function. It saves buffer pointer and configurations
 *  including system resources and configures EDMA for runtime range processing.
 *
 *  @pre    DPU_CFARCAProcHWA_init() has been called
 *
 *  @param[in]  handle                  CFARCAProcHWA DPU handle
 *  @param[in]  cfarHwaCfg              Pointer to CFARCAProcHWA configuration data structure
 *
 *  \ingroup    DPU_CFARCAPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t DPU_CFARCAProcHWA_config
(
    DPU_CFARCAProcHWA_Handle      handle,
    DPU_CFARCAProcHWA_Config      *cfarHwaCfg
);

/**
 *  @b Description
 *  @n
 *      The function is CFARCAProcHWA DPU process function. It performs CFAR detection using HWA
 *
 *  @pre    DPU_CFARCAProcHWA_init() has been called
 *
 *  @param[in]  handle                  CFARCAProcHWA DPU handle
 *  @param[in]  outParams               DPU output parameters
 *
 *  \ingroup    DPU_CFARCAPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success = 0
 *  @retval
 *      Error  != 0
 */
int32_t DPU_CFARCAProcHWA_process
(
    DPU_CFARCAProcHWA_Handle   handle,
    DPU_CFARCAProcHWA_OutParams  *outParams
);

/**
 *  @b Description
 *  @n
 *      The function is CFARCAProcHWA DPU control function.
 *
 *  @pre     DPU_CFARCAProcHWA_init() has been called
 *
 *  @param[in]  handle           CFARCAProcHWA DPU handle
 *  @param[in]  cmd              CFARCAProcHWA DPU control command
 *  @param[in]  arg              CFARCAProcHWA DPU control argument pointer
 *  @param[in]  argSize          CFARCAProcHWA DPU control argument size
 *
 *  \ingroup    DPU_CFARCAPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t DPU_CFARCAProcHWA_control
(
    DPU_CFARCAProcHWA_Handle handle,
    DPU_CFARCAProcHWA_Cmd cmd,
    void *arg,
    uint32_t argSize
);

/**
 *  @b Description
 *  @n
 *      The function is CFARCAProcHWA DPU deinitialization function. It frees up the
 *   resources allocated during initialization.
 *
 *  @pre    DPU_CFARCAProcHWA_init() has been called
 *
 *  @param[in]  handle           CFARCAProcHWA DPU handle
 *
 *  \ingroup    DPU_CFARCAPROC_EXTERNAL_FUNCTION
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t DPU_CFARCAProcHWA_deinit
(
    DPU_CFARCAProcHWA_Handle handle
);

#ifdef __cplusplus
}
#endif

#endif
