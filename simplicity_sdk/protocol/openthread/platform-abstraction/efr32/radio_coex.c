/*
 *  Copyright (c) 2024, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file implements the OpenThread platform abstraction for radio coex metrics
 *   collection.
 *
 */

 #include <assert.h>
 #include <stdbool.h>
 #include <stdio.h>
 
 #include "radio_coex.h"
 
 #if OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE
 
 static sl_ot_coex_counter_t sl_coex_counter;
 
 static inline void sl_increment_if_no_overflow(uint32_t *var, uint32_t incr, bool *stopped)
 {
     uint32_t old  = *var;
     uint32_t temp = old + incr;
     if (temp < old)
     {
         if (stopped)
             *stopped = true;
     }
     else
     {
         *var = temp;
     }
 }
 
 void sl_rail_util_coex_ot_events(sl_rail_util_coex_ot_event_t event)
 {
     bool                         isTxEvent = (event & SL_RAIL_UTIL_COEX_OT_TX_REQUEST);
     sl_rail_util_coex_ot_event_t coexEvent =
         (event & ~(SL_RAIL_UTIL_COEX_OT_TX_REQUEST | SL_RAIL_UTIL_COEX_OT_RX_REQUEST));
     uint32_t *metrics = isTxEvent ? &sl_coex_counter.metrics.mNumTxRequest : &sl_coex_counter.metrics.mNumRxRequest;
     uint64_t *totalReqToGrantDuration =
         isTxEvent ? &sl_coex_counter.totalTxReqToGrantDuration : &sl_coex_counter.totalRxReqToGrantDuration;
 
     /* clang-format off */
 
     // uint32_t mNumGrantGlitch;                       ///< Not available.
 
     // mNumTxRequest    = mNumTxGrantImmediate + mNumTxGrantWait
     // mNumTxGrantWait  = mNumTxGrantWaitActivated + mNumTxGrantWaitTimeout
     // Same applies for Rx counters.
     
     /* Tx Events*/
     // uint32_t mNumTxRequest;                         ///< Number of Tx Requested = mNumTxGrantImmediate + mNumTxGrantWait.
     // uint32_t mNumTxGrantImmediate;                  ///< Not Available.
     // uint32_t mNumTxGrantWait;                       ///< Number of tx requests while grant was inactive.
     // uint32_t mNumTxGrantWaitActivated;              ///< Number of tx requests while grant was inactive that were ultimately granted.
     // uint32_t mNumTxGrantWaitTimeout;                ///< Number of tx requests while grant was inactive that timed out.
     // uint32_t mNumTxGrantDeactivatedDuringRequest;   ///< Number of tx that were in progress when grant was deactivated.
     // uint32_t mNumTxDelayedGrant;                    ///< Number of tx requests that were not granted within 50us.
     // uint32_t mAvgTxRequestToGrantTime;              ///< Average time in usec from tx request to grant.
     
     /* Rx Events*/
     // uint32_t mNumRxRequest;                         ///< Number of rx requests.
     // uint32_t mNumRxGrantImmediate;                  ///< Number of rx requests while grant was active.
     // uint32_t mNumRxGrantWait;                       ///< Number of rx requests while grant was inactive.
     // uint32_t mNumRxGrantWaitActivated;              ///< Number of rx requests while grant was inactive that were ultimately granted.
     // uint32_t mNumRxGrantWaitTimeout;                ///< Number of rx requests while grant was inactive that timed out.
     // uint32_t mNumRxGrantDeactivatedDuringRequest;   ///< Number of rx that were in progress when grant was deactivated.
     // uint32_t mNumRxDelayedGrant;                    ///< Number of rx requests that were not granted within 50us.
     // uint32_t mAvgRxRequestToGrantTime;              ///< Average time in usec from rx request to grant.
     
     // uint32_t mNumRxGrantNone;                       ///< Number of rx requests that completed without receiving grant.
     // bool     mStopped;
 
     /* clang-format on */
 
     otEXPECT(sl_coex_counter.metrics.mStopped == false);
 
     switch (coexEvent)
     {
     case SL_RAIL_UTIL_COEX_OT_EVENT_GRANTED_IMMEDIATE:
         sl_increment_if_no_overflow(metrics, 1, &sl_coex_counter.metrics.mStopped);
         break;
 
     case SL_RAIL_UTIL_COEX_OT_EVENT_REQUESTED:
         sl_coex_counter.timestamp = otPlatAlarmMicroGetNow();
         sl_increment_if_no_overflow(metrics, 1, &sl_coex_counter.metrics.mStopped);
         break;
 
     case SL_RAIL_UTIL_COEX_OT_EVENT_GRANTED:
     {
         uint64_t reqToGrantDuration = otPlatAlarmMicroGetNow() - sl_coex_counter.timestamp;
         sl_increment_if_no_overflow(metrics, 1, &sl_coex_counter.metrics.mStopped);
 
         if (reqToGrantDuration > 50)
         {
             sl_increment_if_no_overflow(metrics, 1, &sl_coex_counter.metrics.mStopped);
         }
 
         *totalReqToGrantDuration += reqToGrantDuration;
     }
     break;
 
     case SL_RAIL_UTIL_COEX_OT_EVENT_DENIED:
         sl_increment_if_no_overflow(metrics, 1, &sl_coex_counter.metrics.mStopped);
         break;
 
     case SL_RAIL_UTIL_COEX_OT_EVENT_GRANT_ABORTED:
         sl_increment_if_no_overflow(metrics, 1, &sl_coex_counter.metrics.mStopped);
         break;
 
     default:
         break;
     }
 
     sl_increment_if_no_overflow(metrics,
                                 sl_coex_counter.metrics.mNumTxGrantWaitTimeout
                                     + sl_coex_counter.metrics.mNumTxGrantWaitActivated,
                                 &sl_coex_counter.metrics.mStopped);
     if (*metrics != 0)
     {
         sl_coex_counter.metrics.mAvgTxRequestToGrantTime = (uint32_t)(*totalReqToGrantDuration / *metrics);
     }
     else
     {
         sl_coex_counter.metrics.mAvgTxRequestToGrantTime = 0;
     }
 
 exit:
     return;
 }
 
 otError otPlatRadioGetCoexMetrics(otInstance *aInstance, otRadioCoexMetrics *aCoexMetrics)
 {
     OT_UNUSED_VARIABLE(aInstance);
 
     otError error = OT_ERROR_NONE;
 
     otEXPECT_ACTION(aCoexMetrics != NULL, error = OT_ERROR_INVALID_ARGS);
 
     memcpy(aCoexMetrics, &sl_coex_counter.metrics, sizeof(otRadioCoexMetrics));
 
 exit:
     return error;
 }
 
 void sli_radio_coex_reset(void)
 {
     memset(&sl_coex_counter, 0, sizeof(sl_coex_counter));
 }
 
 #else
 
 otError otPlatRadioGetCoexMetrics(otInstance *aInstance, otRadioCoexMetrics *aCoexMetrics)
 {
     OT_UNUSED_VARIABLE(aInstance);
     OT_UNUSED_VARIABLE(aCoexMetrics);
     return OT_ERROR_NOT_IMPLEMENTED;
 }
 #endif // OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE
 