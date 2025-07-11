/*******************************************************************************
 * @file
 * @brief SL Status Codes.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_STATUS_H
#define SL_STATUS_H

#include <stdint.h>

/*******************************************************************************
 * @addtogroup status Status Codes
 * @details Status Codes contains error and status code definitions used by
 *          Simplicity SDK software components and stacks. This module also
 *          provides routines to read the string linked with the error and
 *          status codes.
 * @{
 ******************************************************************************/

// -----------------------------------------------------------------------------
// Space Defines

#define SL_STATUS_SPACE_MASK              ((sl_status_t)0xFF00)  ///< sl status space mask.

#define SL_STATUS_GENERIC_SPACE           ((sl_status_t)0x0000)  ///< sl status generic space.

#define SL_STATUS_PLATFORM_1_SPACE        ((sl_status_t)0x0100)  ///< sl status platform 1 space.
#define SL_STATUS_PLATFORM_2_SPACE        ((sl_status_t)0x0200)  ///< sl status platform 2 space.
#define SL_STATUS_HARDWARE_SPACE          ((sl_status_t)0x0300)  ///< sl status hardware space.

#define SL_STATUS_BLUETOOTH_SPACE         ((sl_status_t)0x0400)  ///< sl status bluetooth space.
#define SL_STATUS_BLUETOOTH_MESH_SPACE    ((sl_status_t)0x0500)  ///< sl status bluetooth mesh space.
#define SL_STATUS_CAN_CANOPEN_SPACE       ((sl_status_t)0x0600)  ///< sl status can canopen space.
#define SL_STATUS_CONNECT_SPACE           ((sl_status_t)0x0700)  ///< sl status connect space.
#define SL_STATUS_NET_SUITE_SPACE         ((sl_status_t)0x0800)  ///< sl status net suite space.
#define SL_STATUS_THREAD_SPACE            ((sl_status_t)0x0900)  ///< sl status thread space.
#define SL_STATUS_USB_SPACE               ((sl_status_t)0x0A00)  ///< sl status usb space.
#define SL_STATUS_WIFI_SPACE              ((sl_status_t)0x0B00)  ///< sl status wifi space.
#define SL_STATUS_ZIGBEE_SPACE            ((sl_status_t)0x0C00)  ///< sl status zigbee space.
#define SL_STATUS_Z_WAVE_SPACE            ((sl_status_t)0x0D00)  ///< sl status z wave space.

#define SL_STATUS_GECKO_OS_1_SPACE        ((sl_status_t)0x0E00)  ///< sl status gecko os 1 space.
#define SL_STATUS_GECKO_OS_2_SPACE        ((sl_status_t)0x0F00)  ///< sl status gecko os 2 space.

#define SL_STATUS_BLUETOOTH_CTRL_SPACE    ((sl_status_t)0x1000)  ///< sl status bluetooth ctrl space.
#define SL_STATUS_BLUETOOTH_ATT_SPACE     ((sl_status_t)0x1100)  ///< sl status bluetooth att space.
#define SL_STATUS_BLUETOOTH_SMP_SPACE     ((sl_status_t)0x1200)  ///< sl status bluetooth mesh foundation space.
#define SL_STATUS_BLUETOOTH_MESH_FOUNDATION_SPACE     ((sl_status_t)0x1300)  ///< sl status bluetooth mesh foundation space.

#define SL_STATUS_WISUN_SPACE             ((sl_status_t)0x1400)  ///< sl status wisun space.

#define SL_STATUS_COMPUTE_SPACE           ((sl_status_t)0x1500)  ///< sl status compute space.

// -----------------------------------------------------------------------------
// Status Defines

// -----------------------------------------------------------------------------
// Generic Errors

#define SL_STATUS_OK    ((sl_status_t)0x0000)  ///< No error.
#define SL_STATUS_FAIL  ((sl_status_t)0x0001)  ///< Generic error.

// State Errors
#define SL_STATUS_INVALID_STATE         ((sl_status_t)0x0002)  ///< Generic invalid state error.
#define SL_STATUS_NOT_READY             ((sl_status_t)0x0003)  ///< Module is not ready for requested operation.
#define SL_STATUS_BUSY                  ((sl_status_t)0x0004)  ///< Module is busy and cannot carry out requested operation.
#define SL_STATUS_IN_PROGRESS           ((sl_status_t)0x0005)  ///< Operation is in progress and not yet complete (pass or fail).
#define SL_STATUS_ABORT                 ((sl_status_t)0x0006)  ///< Operation aborted.
#define SL_STATUS_TIMEOUT               ((sl_status_t)0x0007)  ///< Operation timed out.
#define SL_STATUS_PERMISSION            ((sl_status_t)0x0008)  ///< Operation not allowed per permissions.
#define SL_STATUS_WOULD_BLOCK           ((sl_status_t)0x0009)  ///< Non-blocking operation would block.
#define SL_STATUS_IDLE                  ((sl_status_t)0x000A)  ///< Operation/module is Idle, cannot carry requested operation.
#define SL_STATUS_IS_WAITING            ((sl_status_t)0x000B)  ///< Operation cannot be done while construct is waiting.
#define SL_STATUS_NONE_WAITING          ((sl_status_t)0x000C)  ///< No task/construct waiting/pending for that action/event.
#define SL_STATUS_SUSPENDED             ((sl_status_t)0x000D)  ///< Operation cannot be done while construct is suspended.
#define SL_STATUS_NOT_AVAILABLE         ((sl_status_t)0x000E)  ///< Feature not available due to software configuration.
#define SL_STATUS_NOT_SUPPORTED         ((sl_status_t)0x000F)  ///< Feature not supported.
#define SL_STATUS_INITIALIZATION        ((sl_status_t)0x0010)  ///< Initialization failed.
#define SL_STATUS_NOT_INITIALIZED       ((sl_status_t)0x0011)  ///< Module has not been initialized.
#define SL_STATUS_ALREADY_INITIALIZED   ((sl_status_t)0x0012)  ///< Module has already been initialized.
#define SL_STATUS_DELETED               ((sl_status_t)0x0013)  ///< Object/construct has been deleted.
#define SL_STATUS_ISR                   ((sl_status_t)0x0014)  ///< Illegal call from ISR.
#define SL_STATUS_NETWORK_UP            ((sl_status_t)0x0015)  ///< Illegal call because network is up.
#define SL_STATUS_NETWORK_DOWN          ((sl_status_t)0x0016)  ///< Illegal call because network is down.
#define SL_STATUS_NOT_JOINED            ((sl_status_t)0x0017)  ///< Failure due to not being joined in a network.
#define SL_STATUS_NO_BEACONS            ((sl_status_t)0x0018)  ///< Invalid operation as there are no beacons.

// Allocation/ownership Errors
#define SL_STATUS_ALLOCATION_FAILED   ((sl_status_t)0x0019)  ///< Generic allocation error.
#define SL_STATUS_NO_MORE_RESOURCE    ((sl_status_t)0x001A)  ///< No more resource available to perform the operation.
#define SL_STATUS_EMPTY               ((sl_status_t)0x001B)  ///< Item/list/queue is empty.
#define SL_STATUS_FULL                ((sl_status_t)0x001C)  ///< Item/list/queue is full.
#define SL_STATUS_WOULD_OVERFLOW      ((sl_status_t)0x001D)  ///< Item would overflow.
#define SL_STATUS_HAS_OVERFLOWED      ((sl_status_t)0x001E)  ///< Item/list/queue has been overflowed.
#define SL_STATUS_OWNERSHIP           ((sl_status_t)0x001F)  ///< Generic ownership error.
#define SL_STATUS_IS_OWNER            ((sl_status_t)0x0020)  ///< Already/still owning resource.

// Invalid Parameters Errors
#define SL_STATUS_INVALID_PARAMETER       ((sl_status_t)0x0021)  ///< Generic invalid argument or consequence of invalid argument.
#define SL_STATUS_NULL_POINTER            ((sl_status_t)0x0022)  ///< Invalid null pointer received as argument.
#define SL_STATUS_INVALID_CONFIGURATION   ((sl_status_t)0x0023)  ///< Invalid configuration provided.
#define SL_STATUS_INVALID_MODE            ((sl_status_t)0x0024)  ///< Invalid mode.
#define SL_STATUS_INVALID_HANDLE          ((sl_status_t)0x0025)  ///< Invalid handle.
#define SL_STATUS_INVALID_TYPE            ((sl_status_t)0x0026)  ///< Invalid type for operation.
#define SL_STATUS_INVALID_INDEX           ((sl_status_t)0x0027)  ///< Invalid index.
#define SL_STATUS_INVALID_RANGE           ((sl_status_t)0x0028)  ///< Invalid range.
#define SL_STATUS_INVALID_KEY             ((sl_status_t)0x0029)  ///< Invalid key.
#define SL_STATUS_INVALID_CREDENTIALS     ((sl_status_t)0x002A)  ///< Invalid credentials.
#define SL_STATUS_INVALID_COUNT           ((sl_status_t)0x002B)  ///< Invalid count.
#define SL_STATUS_INVALID_SIGNATURE       ((sl_status_t)0x002C)  ///< Invalid signature / verification failed.
#define SL_STATUS_NOT_FOUND               ((sl_status_t)0x002D)  ///< Item could not be found.
#define SL_STATUS_ALREADY_EXISTS          ((sl_status_t)0x002E)  ///< Item already exists.

// IO/Communication Errors
#define SL_STATUS_IO                    ((sl_status_t)0x002F)  ///< Generic I/O failure.
#define SL_STATUS_IO_TIMEOUT            ((sl_status_t)0x0030)  ///< I/O failure due to timeout.
#define SL_STATUS_TRANSMIT              ((sl_status_t)0x0031)  ///< Generic transmission error.
#define SL_STATUS_TRANSMIT_UNDERFLOW    ((sl_status_t)0x0032)  ///< Transmit underflowed.
#define SL_STATUS_TRANSMIT_INCOMPLETE   ((sl_status_t)0x0033)  ///< Transmit is incomplete.
#define SL_STATUS_TRANSMIT_BUSY         ((sl_status_t)0x0034)  ///< Transmit is busy.
#define SL_STATUS_RECEIVE               ((sl_status_t)0x0035)  ///< Generic reception error.
#define SL_STATUS_OBJECT_READ           ((sl_status_t)0x0036)  ///< Failed to read on/via given object.
#define SL_STATUS_OBJECT_WRITE          ((sl_status_t)0x0037)  ///< Failed to write on/via given object.
#define SL_STATUS_MESSAGE_TOO_LONG      ((sl_status_t)0x0038)  ///< Message is too long.

// EEPROM/Flash Errors
#define SL_STATUS_EEPROM_MFG_VERSION_MISMATCH     ((sl_status_t)0x0039)  ///< EEPROM MFG version mismatch.
#define SL_STATUS_EEPROM_STACK_VERSION_MISMATCH   ((sl_status_t)0x003A)  ///< EEPROM Stack version mismatch.
#define SL_STATUS_FLASH_WRITE_INHIBITED           ((sl_status_t)0x003B)  ///< Flash write is inhibited.
#define SL_STATUS_FLASH_VERIFY_FAILED             ((sl_status_t)0x003C)  ///< Flash verification failed.
#define SL_STATUS_FLASH_PROGRAM_FAILED            ((sl_status_t)0x003D)  ///< Flash programming failed.
#define SL_STATUS_FLASH_ERASE_FAILED              ((sl_status_t)0x003E)  ///< Flash erase failed.

// MAC Errors
#define SL_STATUS_MAC_NO_DATA                   ((sl_status_t)0x003F)  ///< MAC no data.
#define SL_STATUS_MAC_NO_ACK_RECEIVED           ((sl_status_t)0x0040)  ///< MAC no ACK received.
#define SL_STATUS_MAC_INDIRECT_TIMEOUT          ((sl_status_t)0x0041)  ///< MAC indirect timeout.
#define SL_STATUS_MAC_UNKNOWN_HEADER_TYPE       ((sl_status_t)0x0042)  ///< MAC unknown header type.
#define SL_STATUS_MAC_ACK_HEADER_TYPE           ((sl_status_t)0x0043)  ///< MAC ACK unknown header type.
#define SL_STATUS_MAC_COMMAND_TRANSMIT_FAILURE  ((sl_status_t)0x0044)  ///< MAC command transmit failure.

// CLI_STORAGE Errors
#define SL_STATUS_CLI_STORAGE_NVM_OPEN_ERROR    ((sl_status_t)0x0045)  ///< Error in open NVM

// Security status codes
#define SL_STATUS_SECURITY_IMAGE_CHECKSUM_ERROR ((sl_status_t)0x0046)  ///< Image checksum is not valid.
#define SL_STATUS_SECURITY_DECRYPT_ERROR        ((sl_status_t)0x0047)  ///< Decryption failed

// Command status codes
#define SL_STATUS_COMMAND_IS_INVALID            ((sl_status_t)0x0048)  ///< Command was not recognized
#define SL_STATUS_COMMAND_TOO_LONG              ((sl_status_t)0x0049)  ///< Command or parameter maximum length exceeded
#define SL_STATUS_COMMAND_INCOMPLETE            ((sl_status_t)0x004A)  ///< Data received does not form a complete command

// Misc Errors
#define SL_STATUS_BUS_ERROR                     ((sl_status_t)0x004B)  ///< Bus error, e.g. invalid DMA address

// Unified MAC Errors
#define SL_STATUS_CCA_FAILURE                   ((sl_status_t)0x004C)  ///< CCA failure.

// Scan errors
#define SL_STATUS_MAC_SCANNING                  ((sl_status_t)0x004D)  ///< MAC scanning.
#define SL_STATUS_MAC_INCORRECT_SCAN_TYPE       ((sl_status_t)0x004E)  ///< MAC incorrect scan type.
#define SL_STATUS_INVALID_CHANNEL_MASK          ((sl_status_t)0x004F)  ///< Invalid channel mask.
#define SL_STATUS_BAD_SCAN_DURATION             ((sl_status_t)0x0050)  ///< Bad scan duration.

// MAC transmit related status
#define SL_STATUS_MAC_TRANSMIT_QUEUE_FULL       ((sl_status_t)0x0053)  ///< The MAC transmit queue is full
#define SL_STATUS_TRANSMIT_SCHEDULER_FAIL       ((sl_status_t)0x0054)  ///< The transmit attempt failed because the radio scheduler could not find a slot to transmit this packet in or a higher priority event interrupted it
#define SL_STATUS_TRANSMIT_INVALID_CHANNEL      ((sl_status_t)0x0055)  ///< An unsupported channel setting was specified
#define SL_STATUS_TRANSMIT_INVALID_POWER        ((sl_status_t)0x0056)  ///< An unsupported power setting was specified
#define SL_STATUS_TRANSMIT_ACK_RECEIVED         ((sl_status_t)0x0057)  ///< The expected ACK was received after the last transmission
#define SL_STATUS_TRANSMIT_BLOCKED              ((sl_status_t)0x0058)  ///< The transmit attempt was blocked from going over the air. Typically this is due to the Radio Hold Off (RHO) or Coexistence plugins as they can prevent transmits based on external signals.

// NVM3 specific errors
#define SL_STATUS_NVM3_ALIGNMENT_INVALID             ((sl_status_t)0x0059)  ///< The initialization was aborted as the NVM3 instance is not aligned properly in memory
#define SL_STATUS_NVM3_SIZE_TOO_SMALL                ((sl_status_t)0x005A)  ///< The initialization was aborted as the size of the NVM3 instance is too small
#define SL_STATUS_NVM3_PAGE_SIZE_NOT_SUPPORTED       ((sl_status_t)0x005B)  ///< The initialization was aborted as the NVM3 page size is not supported
#define SL_STATUS_NVM3_TOKEN_INIT_FAILED             ((sl_status_t)0x005C)  ///< The application that there was an error initializing some of the tokens
#define SL_STATUS_NVM3_OPENED_WITH_OTHER_PARAMETERS  ((sl_status_t)0x005D)  ///< The initialization was aborted as the NVM3 instance was already opened with other parameters
#define SL_STATUS_NVM3_NO_VALID_PAGES                ((sl_status_t)0x005E)  ///< Initialization aborted, no valid page found
#define SL_STATUS_NVM3_OBJECT_SIZE_NOT_SUPPORTED     ((sl_status_t)0x005F)  ///< The object size is not supported
#define SL_STATUS_NVM3_OBJECT_IS_NOT_DATA            ((sl_status_t)0x0060)  ///< Trying to access a data object which is currently a counter object
#define SL_STATUS_NVM3_OBJECT_IS_NOT_A_COUNTER       ((sl_status_t)0x0061)  ///< Trying to access a counter object which is currently a data object
#define SL_STATUS_NVM3_WRITE_DATA_SIZE               ((sl_status_t)0x0062)  ///< The object is too large
#define SL_STATUS_NVM3_READ_DATA_SIZE                ((sl_status_t)0x0063)  ///< Trying to read with a length different from actual object size
#define SL_STATUS_NVM3_INIT_WITH_FULL_NVM            ((sl_status_t)0x0064)  ///< The module was opened with a full NVM
#define SL_STATUS_NVM3_RESIZE_PARAMETER              ((sl_status_t)0x0065)  ///< Illegal parameter
#define SL_STATUS_NVM3_RESIZE_NOT_ENOUGH_SPACE       ((sl_status_t)0x0066)  ///< Not enough NVM to complete resize
#define SL_STATUS_NVM3_ERASE_COUNT_ERROR             ((sl_status_t)0x0067)  ///< Erase counts are not valid
#define SL_STATUS_NVM3_NVM_ACCESS                    ((sl_status_t)0x0068)  ///< A NVM function call was failing
#define SL_STATUS_NVM3_WRITE_TO_NOT_ERASED           ((sl_status_t)0x006D)  ///< Write to memory that is not erased
#define SL_STATUS_NVM3_INVALID_ADDR                  ((sl_status_t)0x006E)  ///< Invalid NVM address
#define SL_STATUS_NVM3_KEY_MISMATCH                  ((sl_status_t)0x006F)  ///< Key validation failure
#define SL_STATUS_NVM3_SIZE_ERROR                    ((sl_status_t)0x0070)  ///< Size mismatch error
#define SL_STATUS_NVM3_EMULATOR                      ((sl_status_t)0x0071)  ///< Emulator error

// Security status codes
#define SL_STATUS_SECURITY_ENCRYPT_ERROR             ((sl_status_t)0x0072)  ///< Encryption failed
#define SL_STATUS_SECURITY_KEY_ERROR                 ((sl_status_t)0x0073)  ///< Error in obtaining crypto key
#define SL_STATUS_SECURITY_RANDOM_NUM_GEN_ERROR      ((sl_status_t)0x0074)  ///< Error in obtaining random number

// Bluetooth status codes
#define SL_STATUS_BT_OUT_OF_BONDS                                                                        ((sl_status_t)0x0402)        ///< Bonding procedure can't be started because device has no space left for bond.
#define SL_STATUS_BT_UNSPECIFIED                                                                         ((sl_status_t)0x0403)        ///< Unspecified error
#define SL_STATUS_BT_HARDWARE                                                                            ((sl_status_t)0x0404)        ///< Hardware failure
#define SL_STATUS_BT_NO_BONDING                                                                          ((sl_status_t)0x0406)        ///< The bonding does not exist.
#define SL_STATUS_BT_CRYPTO                                                                              ((sl_status_t)0x0407)        ///< Error using crypto functions
#define SL_STATUS_BT_DATA_CORRUPTED                                                                      ((sl_status_t)0x0408)        ///< Data was corrupted.
#define SL_STATUS_BT_INVALID_SYNC_HANDLE                                                                 ((sl_status_t)0x040A)        ///< Invalid periodic advertising sync handle
#define SL_STATUS_BT_INVALID_MODULE_ACTION                                                               ((sl_status_t)0x040B)        ///< Bluetooth cannot be used on this hardware
#define SL_STATUS_BT_RADIO                                                                               ((sl_status_t)0x040C)        ///< Error received from radio
#define SL_STATUS_BT_L2CAP_REMOTE_DISCONNECTED                                                           ((sl_status_t)0x040D)        ///< Returned when remote disconnects the connection-oriented channel by sending disconnection request.
#define SL_STATUS_BT_L2CAP_LOCAL_DISCONNECTED                                                            ((sl_status_t)0x040E)        ///< Returned when local host disconnect the connection-oriented channel by sending disconnection request.
#define SL_STATUS_BT_L2CAP_CID_NOT_EXIST                                                                 ((sl_status_t)0x040F)        ///< Returned when local host did not find a connection-oriented channel with given destination CID.
#define SL_STATUS_BT_L2CAP_LE_DISCONNECTED                                                               ((sl_status_t)0x0410)        ///< Returned when connection-oriented channel disconnected due to LE connection is dropped.
#define SL_STATUS_BT_L2CAP_FLOW_CONTROL_VIOLATED                                                         ((sl_status_t)0x0412)        ///< Returned when connection-oriented channel disconnected due to remote end send data even without credit.
#define SL_STATUS_BT_L2CAP_FLOW_CONTROL_CREDIT_OVERFLOWED                                                ((sl_status_t)0x0413)        ///< Returned when connection-oriented channel disconnected due to remote end send flow control credits exceed 65535.
#define SL_STATUS_BT_L2CAP_NO_FLOW_CONTROL_CREDIT                                                        ((sl_status_t)0x0414)        ///< Returned when connection-oriented channel has run out of flow control credit and local application still trying to send data.
#define SL_STATUS_BT_L2CAP_CONNECTION_REQUEST_TIMEOUT                                                    ((sl_status_t)0x0415)        ///< Returned when connection-oriented channel has not received connection response message within maximum timeout.
#define SL_STATUS_BT_L2CAP_INVALID_CID                                                                   ((sl_status_t)0x0416)        ///< Returned when local host received a connection-oriented channel connection response with an invalid destination CID.
#define SL_STATUS_BT_L2CAP_WRONG_STATE                                                                   ((sl_status_t)0x0417)        ///< Returned when local host application tries to send a command which is not suitable for L2CAP channel's current state.
#define SL_STATUS_BT_PS_STORE_FULL                                                                       ((sl_status_t)0x041B)        ///< Flash reserved for PS store is full
#define SL_STATUS_BT_PS_KEY_NOT_FOUND                                                                    ((sl_status_t)0x041C)        ///< PS key not found
#define SL_STATUS_BT_APPLICATION_MISMATCHED_OR_INSUFFICIENT_SECURITY                                     ((sl_status_t)0x041D)        ///< Mismatched or insufficient security level
#define SL_STATUS_BT_APPLICATION_ENCRYPTION_DECRYPTION_ERROR                                             ((sl_status_t)0x041E)        ///< Encryption/decryption operation failed.

// Bluetooth controller status codes
#define SL_STATUS_BT_CTRL_UNKNOWN_CONNECTION_IDENTIFIER                                                  ((sl_status_t)0x1002)      ///< Connection does not exist, or connection open request was cancelled.
#define SL_STATUS_BT_CTRL_AUTHENTICATION_FAILURE                                                         ((sl_status_t)0x1005)      ///< Pairing or authentication failed due to incorrect results in the pairing or authentication procedure. This could be due to an incorrect PIN or Link Key
#define SL_STATUS_BT_CTRL_PIN_OR_KEY_MISSING                                                             ((sl_status_t)0x1006)      ///< Pairing failed because of missing PIN, or authentication failed because of missing Key
#define SL_STATUS_BT_CTRL_MEMORY_CAPACITY_EXCEEDED                                                       ((sl_status_t)0x1007)      ///< Controller is out of memory.
#define SL_STATUS_BT_CTRL_CONNECTION_TIMEOUT                                                             ((sl_status_t)0x1008)      ///< Link supervision timeout has expired.
#define SL_STATUS_BT_CTRL_CONNECTION_LIMIT_EXCEEDED                                                      ((sl_status_t)0x1009)      ///< Controller is at limit of connections it can support.
#define SL_STATUS_BT_CTRL_SYNCHRONOUS_CONNECTION_LIMIT_EXCEEDED                                          ((sl_status_t)0x100A)     ///< The Synchronous Connection Limit to a Device Exceeded error code indicates that the Controller has reached the limit to the number of synchronous connections that can be achieved to a device.
#define SL_STATUS_BT_CTRL_ACL_CONNECTION_ALREADY_EXISTS                                                  ((sl_status_t)0x100B)     ///< The ACL Connection Already Exists error code indicates that an attempt to create a new ACL Connection to a device when there is already a connection to this device.
#define SL_STATUS_BT_CTRL_COMMAND_DISALLOWED                                                             ((sl_status_t)0x100C)     ///< Command requested cannot be executed because the Controller is in a state where it cannot process this command at this time.
#define SL_STATUS_BT_CTRL_CONNECTION_REJECTED_DUE_TO_LIMITED_RESOURCES                                   ((sl_status_t)0x100D)     ///< The Connection Rejected Due To Limited Resources error code indicates that an incoming connection was rejected due to limited resources.
#define SL_STATUS_BT_CTRL_CONNECTION_REJECTED_DUE_TO_SECURITY_REASONS                                    ((sl_status_t)0x100E)     ///< The Connection Rejected Due To Security Reasons error code indicates that a connection was rejected due to security requirements not being fulfilled, like authentication or pairing.
#define SL_STATUS_BT_CTRL_CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR                                ((sl_status_t)0x100F)     ///< The Connection was rejected because this device does not accept the BD_ADDR. This may be because the device will only accept connections from specific BD_ADDRs.
#define SL_STATUS_BT_CTRL_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED                                             ((sl_status_t)0x1010)     ///< The Connection Accept Timeout has been exceeded for this connection attempt.
#define SL_STATUS_BT_CTRL_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE                                         ((sl_status_t)0x1011)     ///< A feature or parameter value in the HCI command is not supported.
#define SL_STATUS_BT_CTRL_INVALID_COMMAND_PARAMETERS                                                     ((sl_status_t)0x1012)     ///< Command contained invalid parameters.
#define SL_STATUS_BT_CTRL_REMOTE_USER_TERMINATED                                                         ((sl_status_t)0x1013)     ///< User on the remote device terminated the connection.
#define SL_STATUS_BT_CTRL_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES                       ((sl_status_t)0x1014)     ///< The remote device terminated the connection because of low resources
#define SL_STATUS_BT_CTRL_REMOTE_POWERING_OFF                                                            ((sl_status_t)0x1015)     ///< Remote Device Terminated Connection due to Power Off
#define SL_STATUS_BT_CTRL_CONNECTION_TERMINATED_BY_LOCAL_HOST                                            ((sl_status_t)0x1016)     ///< Local device terminated the connection.
#define SL_STATUS_BT_CTRL_REPEATED_ATTEMPTS                                                              ((sl_status_t)0x1017)     ///< The Controller is disallowing an authentication or pairing procedure because too little time has elapsed since the last authentication or pairing attempt failed.
#define SL_STATUS_BT_CTRL_PAIRING_NOT_ALLOWED                                                            ((sl_status_t)0x1018)     ///< The device does not allow pairing. This can be for example, when a device only allows pairing during a certain time window after some user input allows pairing
#define SL_STATUS_BT_CTRL_UNSUPPORTED_REMOTE_FEATURE                                                     ((sl_status_t)0x101A)     ///< The remote device does not support the feature associated with the issued command.
#define SL_STATUS_BT_CTRL_INVALID_LL_PARAMETERS                                                          ((sl_status_t)0x101E)     ///< Indicates that some LMP PDU / LL Control PDU parameters were invalid
#define SL_STATUS_BT_CTRL_UNSPECIFIED_ERROR                                                              ((sl_status_t)0x101F)     ///< No other error code specified is appropriate to use.
#define SL_STATUS_BT_CTRL_LL_RESPONSE_TIMEOUT                                                            ((sl_status_t)0x1022)     ///< Connection terminated due to link-layer procedure timeout.
#define SL_STATUS_BT_CTRL_LL_PROCEDURE_COLLISION                                                         ((sl_status_t)0x1023)     ///< LL procedure has collided with the same transaction or procedure that is already in progress.
#define SL_STATUS_BT_CTRL_ENCRYPTION_MODE_NOT_ACCEPTABLE                                                 ((sl_status_t)0x1025)     ///< The requested encryption mode is not acceptable at this time.
#define SL_STATUS_BT_CTRL_LINK_KEY_CANNOT_BE_CHANGED                                                     ((sl_status_t)0x1026)     ///< Link key cannot be changed because a fixed unit key is being used.
#define SL_STATUS_BT_CTRL_INSTANT_PASSED                                                                 ((sl_status_t)0x1028)     ///< LMP PDU or LL PDU that includes an instant cannot be performed because the instant when this would have occurred has passed.
#define SL_STATUS_BT_CTRL_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED                                            ((sl_status_t)0x1029)     ///< It was not possible to pair as a unit key was requested and it is not supported.
#define SL_STATUS_BT_CTRL_DIFFERENT_TRANSACTION_COLLISION                                                ((sl_status_t)0x102A)     ///< LMP transaction was started that collides with an ongoing transaction.
#define SL_STATUS_BT_CTRL_CHANNEL_ASSESSMENT_NOT_SUPPORTED                                               ((sl_status_t)0x102E)     ///< The Controller cannot perform channel assessment because it is not supported.
#define SL_STATUS_BT_CTRL_INSUFFICIENT_SECURITY                                                          ((sl_status_t)0x102F)     ///< The HCI command or LMP PDU sent is only possible on an encrypted link.
#define SL_STATUS_BT_CTRL_PARAMETER_OUT_OF_MANDATORY_RANGE                                               ((sl_status_t)0x1030)     ///< A parameter value requested is outside the mandatory range of parameters for the given HCI command or LMP PDU.
#define SL_STATUS_BT_CTRL_SIMPLE_PAIRING_NOT_SUPPORTED_BY_HOST                                           ((sl_status_t)0x1037)     ///< The IO capabilities request or response was rejected because the sending Host does not support Secure Simple Pairing even though the receiving Link Manager does.
#define SL_STATUS_BT_CTRL_HOST_BUSY_PAIRING                                                              ((sl_status_t)0x1038)     ///< The Host is busy with another pairing operation and unable to support the requested pairing. The receiving device should retry pairing again later.
#define SL_STATUS_BT_CTRL_CONNECTION_REJECTED_DUE_TO_NO_SUITABLE_CHANNEL_FOUND                           ((sl_status_t)0x1039)     ///< The Controller could not calculate an appropriate value for the Channel selection operation.
#define SL_STATUS_BT_CTRL_CONTROLLER_BUSY                                                                ((sl_status_t)0x103A)     ///< Operation was rejected because the controller is busy and unable to process the request.
#define SL_STATUS_BT_CTRL_UNACCEPTABLE_CONNECTION_INTERVAL                                               ((sl_status_t)0x103B)     ///< Remote device terminated the connection because of an unacceptable connection interval.
#define SL_STATUS_BT_CTRL_ADVERTISING_TIMEOUT                                                            ((sl_status_t)0x103C)     ///< Advertising for a fixed duration completed or, for directed advertising, that advertising completed without a connection being created.
#define SL_STATUS_BT_CTRL_CONNECTION_TERMINATED_DUE_TO_MIC_FAILURE                                       ((sl_status_t)0x103D)     ///< Connection was terminated because the Message Integrity Check (MIC) failed on a received packet.
#define SL_STATUS_BT_CTRL_CONNECTION_FAILED_TO_BE_ESTABLISHED                                            ((sl_status_t)0x103E)     ///< LL initiated a connection but the connection has failed to be established. Controller did not receive any packets from remote end.
#define SL_STATUS_BT_CTRL_MAC_CONNECTION_FAILED                                                          ((sl_status_t)0x103F)     ///< The MAC of the 802.11 AMP was requested to connect to a peer, but the connection failed.
#define SL_STATUS_BT_CTRL_COARSE_CLOCK_ADJUSTMENT_REJECTED_BUT_WILL_TRY_TO_ADJUST_USING_CLOCK_DRAGGING   ((sl_status_t)0x1040)     ///< The master, at this time, is unable to make a coarse adjustment to the piconet clock, using the supplied parameters. Instead the master will attempt to move the clock using clock dragging.
#define SL_STATUS_BT_CTRL_UNKNOWN_ADVERTISING_IDENTIFIER                                                 ((sl_status_t)0x1042)     ///< A command was sent from the Host that should identify an Advertising or Sync handle, but the Advertising or Sync handle does not exist.
#define SL_STATUS_BT_CTRL_LIMIT_REACHED                                                                  ((sl_status_t)0x1043)     ///< Number of operations requested has been reached and has indicated the completion of the activity (e.g., advertising or scanning).
#define SL_STATUS_BT_CTRL_OPERATION_CANCELLED_BY_HOST                                                    ((sl_status_t)0x1044)     ///< A request to the Controller issued by the Host and still pending was successfully canceled.
#define SL_STATUS_BT_CTRL_PACKET_TOO_LONG                                                                ((sl_status_t)0x1045)     ///< An attempt was made to send or receive a packet that exceeds the maximum allowed packet length.
#define SL_STATUS_BT_CTRL_TOO_LATE                                                                       ((sl_status_t)0x1046)     ///< Information was provided too late to the controller.
#define SL_STATUS_BT_CTRL_TOO_EARLY                                                                      ((sl_status_t)0x1047)     ///< Information was provided too early to the controller.
#define SL_STATUS_BT_CTRL_INSUFFICIENT_CHANNELS                                                          ((sl_status_t)0x1048)     ///< Indicates that the result of the requested operation would yield too few physical channels.

// Bluetooth attribute status codes
#define SL_STATUS_BT_ATT_INVALID_HANDLE                                                                  ((sl_status_t)0x1101)      ///< The attribute handle given was not valid on this server
#define SL_STATUS_BT_ATT_READ_NOT_PERMITTED                                                              ((sl_status_t)0x1102)      ///< The attribute cannot be read
#define SL_STATUS_BT_ATT_WRITE_NOT_PERMITTED                                                             ((sl_status_t)0x1103)      ///< The attribute cannot be written
#define SL_STATUS_BT_ATT_INVALID_PDU                                                                     ((sl_status_t)0x1104)      ///< The attribute PDU was invalid
#define SL_STATUS_BT_ATT_INSUFFICIENT_AUTHENTICATION                                                     ((sl_status_t)0x1105)      ///< The attribute requires authentication before it can be read or written.
#define SL_STATUS_BT_ATT_REQUEST_NOT_SUPPORTED                                                           ((sl_status_t)0x1106)      ///< Attribute Server does not support the request received from the client.
#define SL_STATUS_BT_ATT_INVALID_OFFSET                                                                  ((sl_status_t)0x1107)      ///< Offset specified was past the end of the attribute
#define SL_STATUS_BT_ATT_INSUFFICIENT_AUTHORIZATION                                                      ((sl_status_t)0x1108)      ///< The attribute requires authorization before it can be read or written.
#define SL_STATUS_BT_ATT_PREPARE_QUEUE_FULL                                                              ((sl_status_t)0x1109)      ///< Too many prepare writes have been queued
#define SL_STATUS_BT_ATT_ATT_NOT_FOUND                                                                   ((sl_status_t)0x110A)     ///< No attribute found within the given attribute handle range.
#define SL_STATUS_BT_ATT_ATT_NOT_LONG                                                                    ((sl_status_t)0x110B)     ///< The attribute cannot be read or written using the Read Blob Request
#define SL_STATUS_BT_ATT_INSUFFICIENT_ENC_KEY_SIZE                                                       ((sl_status_t)0x110C)     ///< The Encryption Key Size used for encrypting this link is insufficient.
#define SL_STATUS_BT_ATT_INVALID_ATT_LENGTH                                                              ((sl_status_t)0x110D)     ///< The attribute value length is invalid for the operation
#define SL_STATUS_BT_ATT_UNLIKELY_ERROR                                                                  ((sl_status_t)0x110E)     ///< The attribute request that was requested has encountered an error that was unlikely, and therefore could not be completed as requested.
#define SL_STATUS_BT_ATT_INSUFFICIENT_ENCRYPTION                                                         ((sl_status_t)0x110F)     ///< The attribute requires encryption before it can be read or written.
#define SL_STATUS_BT_ATT_UNSUPPORTED_GROUP_TYPE                                                          ((sl_status_t)0x1110)     ///< The attribute type is not a supported grouping attribute as defined by a higher layer specification.
#define SL_STATUS_BT_ATT_INSUFFICIENT_RESOURCES                                                          ((sl_status_t)0x1111)     ///< Insufficient Resources to complete the request
#define SL_STATUS_BT_ATT_OUT_OF_SYNC                                                                     ((sl_status_t)0x1112)     ///< The server requests the client to rediscover the database.
#define SL_STATUS_BT_ATT_VALUE_NOT_ALLOWED                                                               ((sl_status_t)0x1113)     ///< The attribute parameter value was not allowed.
#define SL_STATUS_BT_ATT_APPLICATION                                                                     ((sl_status_t)0x1180)    ///< When this is returned in a BGAPI response, the application tried to read or write the value of a user attribute from the GATT database.
#define SL_STATUS_BT_ATT_WRITE_REQUEST_REJECTED                                                          ((sl_status_t)0x11FC)    ///< The requested write operation cannot be fulfilled for reasons other than permissions.
#define SL_STATUS_BT_ATT_CLIENT_CHARACTERISTIC_CONFIGURATION_DESCRIPTOR_IMPROPERLY_CONFIGURED            ((sl_status_t)0x11FD)    ///< The Client Characteristic Configuration descriptor is not configured according to the requirements of the profile or service.
#define SL_STATUS_BT_ATT_PROCEDURE_ALREADY_IN_PROGRESS                                                   ((sl_status_t)0x11FE)    ///< The profile or service request cannot be serviced because an operation that has been previously triggered is still in progress.
#define SL_STATUS_BT_ATT_OUT_OF_RANGE                                                                    ((sl_status_t)0x11FF)    ///< The attribute value is out of range as defined by a profile or service specification.

// Bluetooth Security Manager Protocol status codes
#define SL_STATUS_BT_SMP_PASSKEY_ENTRY_FAILED                                                            ((sl_status_t)0x1201)      ///< The user input of passkey failed, for example, the user cancelled the operation
#define SL_STATUS_BT_SMP_OOB_NOT_AVAILABLE                                                               ((sl_status_t)0x1202)      ///< Out of Band data is not available for authentication
#define SL_STATUS_BT_SMP_AUTHENTICATION_REQUIREMENTS                                                     ((sl_status_t)0x1203)      ///< The pairing procedure cannot be performed as authentication requirements cannot be met due to IO capabilities of one or both devices
#define SL_STATUS_BT_SMP_CONFIRM_VALUE_FAILED                                                            ((sl_status_t)0x1204)      ///< The confirm value does not match the calculated compare value
#define SL_STATUS_BT_SMP_PAIRING_NOT_SUPPORTED                                                           ((sl_status_t)0x1205)      ///< Pairing is not supported by the device
#define SL_STATUS_BT_SMP_ENCRYPTION_KEY_SIZE                                                             ((sl_status_t)0x1206)      ///< The resultant encryption key size is insufficient for the security requirements of this device
#define SL_STATUS_BT_SMP_COMMAND_NOT_SUPPORTED                                                           ((sl_status_t)0x1207)      ///< The SMP command received is not supported on this device
#define SL_STATUS_BT_SMP_UNSPECIFIED_REASON                                                              ((sl_status_t)0x1208)      ///< Pairing failed due to an unspecified reason
#define SL_STATUS_BT_SMP_REPEATED_ATTEMPTS                                                               ((sl_status_t)0x1209)      ///< Pairing or authentication procedure is disallowed because too little time has elapsed since last pairing request or security request
#define SL_STATUS_BT_SMP_INVALID_PARAMETERS                                                              ((sl_status_t)0x120A)     ///< The Invalid Parameters error code indicates: the command length is invalid or a parameter is outside of the specified range.
#define SL_STATUS_BT_SMP_DHKEY_CHECK_FAILED                                                              ((sl_status_t)0x120B)     ///< Indicates to the remote device that the DHKey Check value received doesn't match the one calculated by the local device.
#define SL_STATUS_BT_SMP_NUMERIC_COMPARISON_FAILED                                                       ((sl_status_t)0x120C)     ///< Indicates that the confirm values in the numeric comparison protocol do not match.
#define SL_STATUS_BT_SMP_BREDR_PAIRING_IN_PROGRESS                                                       ((sl_status_t)0x120D)     ///< Indicates that the pairing over the LE transport failed due to a Pairing Request sent over the BR/EDR transport in process.
#define SL_STATUS_BT_SMP_CROSS_TRANSPORT_KEY_DERIVATION_GENERATION_NOT_ALLOWED                           ((sl_status_t)0x120E)     ///< Indicates that the BR/EDR Link Key generated on the BR/EDR transport cannot be used to derive and distribute keys for the LE transport.
#define SL_STATUS_BT_SMP_KEY_REJECTED                                                                    ((sl_status_t)0x120F)     ///< Indicates that the device chose not to accept a distributed key.

// Bluetooth Mesh status codes
#define SL_STATUS_BT_MESH_ALREADY_EXISTS                                                                 ((sl_status_t)0x0501)      ///< Returned when trying to add a key or some other unique resource with an ID which already exists
#define SL_STATUS_BT_MESH_DOES_NOT_EXIST                                                                 ((sl_status_t)0x0502)      ///< Returned when trying to manipulate a key or some other resource with an ID which does not exist
#define SL_STATUS_BT_MESH_LIMIT_REACHED                                                                  ((sl_status_t)0x0503)      ///< Returned when an operation cannot be executed because a pre-configured limit for keys, key bindings, elements, models, virtual addresses, provisioned devices, or provisioning sessions is reached
#define SL_STATUS_BT_MESH_INVALID_ADDRESS                                                                ((sl_status_t)0x0504)      ///< Returned when trying to use a reserved address or add a "pre-provisioned" device using an address already used by some other device
#define SL_STATUS_BT_MESH_MALFORMED_DATA                                                                 ((sl_status_t)0x0505)      ///< In a BGAPI response, the user supplied malformed data; in a BGAPI event, the remote end responded with malformed or unrecognized data
#define SL_STATUS_BT_MESH_ALREADY_INITIALIZED                                                            ((sl_status_t)0x0506)      ///< An attempt was made to initialize a subsystem that was already initialized.
#define SL_STATUS_BT_MESH_NOT_INITIALIZED                                                                ((sl_status_t)0x0507)      ///< An attempt was made to use a subsystem that wasn't initialized yet. Call the subsystem's init function first.
#define SL_STATUS_BT_MESH_NO_FRIEND_OFFER                                                                ((sl_status_t)0x0508)      ///< Returned when trying to establish a friendship as a Low Power Node, but no acceptable friend offer message was received.
#define SL_STATUS_BT_MESH_PROV_LINK_CLOSED                                                               ((sl_status_t)0x0509)      ///< Provisioning link was unexpectedly closed before provisioning was complete.
#define SL_STATUS_BT_MESH_PROV_INVALID_PDU                                                               ((sl_status_t)0x050A)     ///< An unrecognized provisioning PDU was received.
#define SL_STATUS_BT_MESH_PROV_INVALID_PDU_FORMAT                                                        ((sl_status_t)0x050B)     ///< A provisioning PDU with wrong length or containing field values that are out of bounds was received.
#define SL_STATUS_BT_MESH_PROV_UNEXPECTED_PDU                                                            ((sl_status_t)0x050C)     ///< An unexpected (out of sequence) provisioning PDU was received.
#define SL_STATUS_BT_MESH_PROV_CONFIRMATION_FAILED                                                       ((sl_status_t)0x050D)     ///< The computed confirmation value did not match the expected value.
#define SL_STATUS_BT_MESH_PROV_OUT_OF_RESOURCES                                                          ((sl_status_t)0x050E)     ///< Provisioning could not be continued due to insufficient resources.
#define SL_STATUS_BT_MESH_PROV_DECRYPTION_FAILED                                                         ((sl_status_t)0x050F)     ///< The provisioning data block could not be decrypted.
#define SL_STATUS_BT_MESH_PROV_UNEXPECTED_ERROR                                                          ((sl_status_t)0x0510)     ///< An unexpected error happened during provisioning.
#define SL_STATUS_BT_MESH_PROV_CANNOT_ASSIGN_ADDR                                                        ((sl_status_t)0x0511)     ///< Device could not assign unicast addresses to all of its elements.
#define SL_STATUS_BT_MESH_ADDRESS_TEMPORARILY_UNAVAILABLE                                                ((sl_status_t)0x0512)     ///< Returned when trying to reuse an address of a previously deleted device before an IV Index Update has been executed.
#define SL_STATUS_BT_MESH_ADDRESS_ALREADY_USED                                                           ((sl_status_t)0x0513)     ///< Returned when trying to assign an address that is used by one of the devices in the Device Database, or by the Provisioner itself.
#define SL_STATUS_BT_MESH_PUBLISH_NOT_CONFIGURED                                                         ((sl_status_t)0x0514)     ///< Application key or publish address are not set
#define SL_STATUS_BT_MESH_APP_KEY_NOT_BOUND                                                              ((sl_status_t)0x0515)     ///< Application key is not bound to a model

// Bluetooth Mesh foundation status codes
#define SL_STATUS_BT_MESH_FOUNDATION_INVALID_ADDRESS                                                     ((sl_status_t)0x1301)      ///< Returned when address in request was not valid
#define SL_STATUS_BT_MESH_FOUNDATION_INVALID_MODEL                                                       ((sl_status_t)0x1302)      ///< Returned when model identified is not found for a given element
#define SL_STATUS_BT_MESH_FOUNDATION_INVALID_APP_KEY                                                     ((sl_status_t)0x1303)      ///< Returned when the key identified by AppKeyIndex is not stored in the node
#define SL_STATUS_BT_MESH_FOUNDATION_INVALID_NET_KEY                                                     ((sl_status_t)0x1304)      ///< Returned when the key identified by NetKeyIndex is not stored in the node
#define SL_STATUS_BT_MESH_FOUNDATION_INSUFFICIENT_RESOURCES                                              ((sl_status_t)0x1305)      ///< Returned when The node cannot serve the request due to insufficient resources
#define SL_STATUS_BT_MESH_FOUNDATION_KEY_INDEX_EXISTS                                                    ((sl_status_t)0x1306)      ///< Returned when the key identified is already stored in the node and the new NetKey value is different
#define SL_STATUS_BT_MESH_FOUNDATION_INVALID_PUBLISH_PARAMS                                              ((sl_status_t)0x1307)      ///< Returned when the model does not support the publish mechanism
#define SL_STATUS_BT_MESH_FOUNDATION_NOT_SUBSCRIBE_MODEL                                                 ((sl_status_t)0x1308)      ///< Returned when  the model does not support the subscribe mechanism
#define SL_STATUS_BT_MESH_FOUNDATION_STORAGE_FAILURE                                                     ((sl_status_t)0x1309)      ///< Returned when storing of the requested parameters failed
#define SL_STATUS_BT_MESH_FOUNDATION_NOT_SUPPORTED                                                       ((sl_status_t)0x130A)     ///< Returned when requested setting is not supported
#define SL_STATUS_BT_MESH_FOUNDATION_CANNOT_UPDATE                                                       ((sl_status_t)0x130B)     ///< Returned when the requested update operation cannot be performed due to general constraints
#define SL_STATUS_BT_MESH_FOUNDATION_CANNOT_REMOVE                                                       ((sl_status_t)0x130C)     ///< Returned when the requested delete operation cannot be performed due to general constraints
#define SL_STATUS_BT_MESH_FOUNDATION_CANNOT_BIND                                                         ((sl_status_t)0x130D)     ///< Returned when the requested bind operation cannot be performed due to general constraints
#define SL_STATUS_BT_MESH_FOUNDATION_TEMPORARILY_UNABLE                                                  ((sl_status_t)0x130E)     ///< Returned when The node cannot start advertising with Node Identity or Proxy since the maximum number of parallel advertising is reached
#define SL_STATUS_BT_MESH_FOUNDATION_CANNOT_SET                                                          ((sl_status_t)0x130F)     ///< Returned when the requested state cannot be set
#define SL_STATUS_BT_MESH_FOUNDATION_UNSPECIFIED                                                         ((sl_status_t)0x1310)     ///< Returned when an unspecified error took place
#define SL_STATUS_BT_MESH_FOUNDATION_INVALID_BINDING                                                     ((sl_status_t)0x1311)     ///< Returned when the NetKeyIndex and AppKeyIndex combination is not valid for a Config AppKey Update

// -----------------------------------------------------------------------------
// Wi-Fi Errors

#define SL_STATUS_WIFI_INVALID_KEY                         ((sl_status_t)0x0B01)  ///< Invalid firmware keyset
#define SL_STATUS_WIFI_FIRMWARE_DOWNLOAD_TIMEOUT           ((sl_status_t)0x0B02)  ///< The firmware download took too long
#define SL_STATUS_WIFI_UNSUPPORTED_MESSAGE_ID              ((sl_status_t)0x0B03)  ///< Unknown request ID or wrong interface ID used
#define SL_STATUS_WIFI_WARNING                             ((sl_status_t)0x0B04)  ///< The request is successful but some parameters have been ignored
#define SL_STATUS_WIFI_NO_PACKET_TO_RECEIVE                ((sl_status_t)0x0B05)  ///< No Packets waiting to be received
#define SL_STATUS_WIFI_SLEEP_GRANTED                       ((sl_status_t)0x0B08)  ///< The sleep mode is granted
#define SL_STATUS_WIFI_SLEEP_NOT_GRANTED                   ((sl_status_t)0x0B09)  ///< The WFx does not go back to sleep
#define SL_STATUS_WIFI_SECURE_LINK_MAC_KEY_ERROR           ((sl_status_t)0x0B10)  ///< The SecureLink MAC key was not found
#define SL_STATUS_WIFI_SECURE_LINK_MAC_KEY_ALREADY_BURNED  ((sl_status_t)0x0B11)  ///< The SecureLink MAC key is already installed in OTP
#define SL_STATUS_WIFI_SECURE_LINK_RAM_MODE_NOT_ALLOWED    ((sl_status_t)0x0B12)  ///< The SecureLink MAC key cannot be installed in RAM
#define SL_STATUS_WIFI_SECURE_LINK_FAILED_UNKNOWN_MODE     ((sl_status_t)0x0B13)  ///< The SecureLink MAC key installation failed
#define SL_STATUS_WIFI_SECURE_LINK_EXCHANGE_FAILED         ((sl_status_t)0x0B14)  ///< SecureLink key (re)negotiation failed
#define SL_STATUS_WIFI_WRONG_STATE                         ((sl_status_t)0x0B18)  ///< The device is in an inappropriate state to perform the request
#define SL_STATUS_WIFI_CHANNEL_NOT_ALLOWED                 ((sl_status_t)0x0B19)  ///< The request failed due to regulatory limitations
#define SL_STATUS_WIFI_NO_MATCHING_AP                      ((sl_status_t)0x0B1A)  ///< The connection request failed because no suitable AP was found
#define SL_STATUS_WIFI_CONNECTION_ABORTED                  ((sl_status_t)0x0B1B)  ///< The connection request was aborted by host
#define SL_STATUS_WIFI_CONNECTION_TIMEOUT                  ((sl_status_t)0x0B1C)  ///< The connection request failed because of a timeout
#define SL_STATUS_WIFI_CONNECTION_REJECTED_BY_AP           ((sl_status_t)0x0B1D)  ///< The connection request failed because the AP rejected the device
#define SL_STATUS_WIFI_CONNECTION_AUTH_FAILURE             ((sl_status_t)0x0B1E)  ///< The connection request failed because the WPA handshake did not complete successfully
#define SL_STATUS_WIFI_RETRY_EXCEEDED                      ((sl_status_t)0x0B1F)  ///< The request failed because the retry limit was exceeded
#define SL_STATUS_WIFI_TX_LIFETIME_EXCEEDED                ((sl_status_t)0x0B20)  ///< The request failed because the MSDU life time was exceeded

// -----------------------------------------------------------------------------

// MVP Driver and MVP Math status codes
#define SL_STATUS_COMPUTE_DRIVER_FAULT                      ((sl_status_t)0x1501)   ///< Critical fault
#define SL_STATUS_COMPUTE_DRIVER_ALU_NAN                    ((sl_status_t)0x1502)   ///< ALU operation output NaN
#define SL_STATUS_COMPUTE_DRIVER_ALU_OVERFLOW               ((sl_status_t)0x1503)   ///< ALU numeric overflow
#define SL_STATUS_COMPUTE_DRIVER_ALU_UNDERFLOW              ((sl_status_t)0x1504)   ///< ALU numeric underflow
#define SL_STATUS_COMPUTE_DRIVER_STORE_CONVERSION_OVERFLOW  ((sl_status_t)0x1505)   ///< Overflow during array store
#define SL_STATUS_COMPUTE_DRIVER_STORE_CONVERSION_UNDERFLOW ((sl_status_t)0x1506)   ///< Underflow during array store conversion
#define SL_STATUS_COMPUTE_DRIVER_STORE_CONVERSION_INFINITY  ((sl_status_t)0x1507)   ///< Infinity encountered during array store conversion
#define SL_STATUS_COMPUTE_DRIVER_STORE_CONVERSION_NAN       ((sl_status_t)0x1508)   ///< NaN encountered during array store conversion

#define SL_STATUS_COMPUTE_MATH_NAN                          ((sl_status_t)0x1512)   ///< MATH NaN encountered
#define SL_STATUS_COMPUTE_MATH_INFINITY                     ((sl_status_t)0x1513)   ///< MATH Infinity encountered
#define SL_STATUS_COMPUTE_MATH_OVERFLOW                     ((sl_status_t)0x1514)   ///< MATH numeric overflow
#define SL_STATUS_COMPUTE_MATH_UNDERFLOW                    ((sl_status_t)0x1515)   ///< MATH numeric underflow

// Zigbee status codes

#define SL_STATUS_ZIGBEE_PACKET_HANDOFF_DROPPED                ((sl_status_t)0x0C01)  ///< Packet is dropped by packet-handoff callbacks
#define SL_STATUS_ZIGBEE_DELIVERY_FAILED                       ((sl_status_t)0x0C02)  ///< The APS layer attempted to send or deliver a message and failed
#define SL_STATUS_ZIGBEE_MAX_MESSAGE_LIMIT_REACHED             ((sl_status_t)0x0C03)  ///< The maximum number of in-flight messages ::EMBER_APS_UNICAST_MESSAGE_COUNT has been reached
#define SL_STATUS_ZIGBEE_BINDING_IS_ACTIVE                     ((sl_status_t)0x0C04)  ///< The application is trying to delete or overwrite a binding that is in use
#define SL_STATUS_ZIGBEE_ADDRESS_TABLE_ENTRY_IS_ACTIVE         ((sl_status_t)0x0C05)  ///< The application is trying to overwrite an address table entry that is in use
#define SL_STATUS_ZIGBEE_MOVE_FAILED                           ((sl_status_t)0x0C06)  ///< After moving, a mobile node's attempt to re-establish contact with the network failed
#define SL_STATUS_ZIGBEE_NODE_ID_CHANGED                       ((sl_status_t)0x0C07)  ///< The local node ID has changed. The application can get the new node ID by calling ::sl_zigbee_get_node_id()
#define SL_STATUS_ZIGBEE_INVALID_SECURITY_LEVEL                ((sl_status_t)0x0C08)  ///< The chosen security level is not supported by the stack
#define SL_STATUS_ZIGBEE_IEEE_ADDRESS_DISCOVERY_IN_PROGRESS    ((sl_status_t)0x0C09)  ///< An error occurred when trying to encrypt at the APS Level
#define SL_STATUS_ZIGBEE_APS_ENCRYPTION_ERROR                  ((sl_status_t)0x0C0A)  ///< An error occurred when trying to encrypt at the APS Level
#define SL_STATUS_ZIGBEE_SECURITY_STATE_NOT_SET                ((sl_status_t)0x0C0B)  ///< There was an attempt to form or join a network with security without calling ::sl_zigbee_set_initial_security_state() first
#define SL_STATUS_ZIGBEE_TOO_SOON_FOR_SWITCH_KEY               ((sl_status_t)0x0C0C)  ///< There was an attempt to broadcast a key switch too quickly after broadcasting the next network key. The Trust Center must wait at least a period equal to the broadcast timeout so that all routers have a chance to receive the broadcast of the new network key
#define SL_STATUS_ZIGBEE_SIGNATURE_VERIFY_FAILURE              ((sl_status_t)0x0C0D)  ///< The received signature corresponding to the message that was passed to the CBKE Library failed verification and is not valid
#define SL_STATUS_ZIGBEE_KEY_NOT_AUTHORIZED                    ((sl_status_t)0x0C0E)  ///< The message could not be sent because the link key corresponding to the destination is not authorized for use in APS data messages
#define SL_STATUS_ZIGBEE_BINDING_HAS_CHANGED                   ((sl_status_t)0x0C0F)  ///< The application tried to use a binding that has been remotely modified and the change has not yet been reported to the application
#define SL_STATUS_ZIGBEE_TRUST_CENTER_SWAP_EUI_HAS_CHANGED     ((sl_status_t)0x0C10)  ///< The EUI of the Trust center has changed due to a successful rejoin after TC Swapout
#define SL_STATUS_ZIGBEE_TRUST_CENTER_SWAP_EUI_HAS_NOT_CHANGED ((sl_status_t)0x0C11)  ///< A Trust Center Swapout Rejoin has occurred without the EUI of the TC changing
#define SL_STATUS_ZIGBEE_INSUFFICIENT_RANDOM_DATA              ((sl_status_t)0x0C12)  ///< An attempt to generate random bytes failed because of insufficient random data from the radio
#define SL_STATUS_ZIGBEE_SOURCE_ROUTE_FAILURE                  ((sl_status_t)0x0C13)  ///< A Zigbee route error command frame was received indicating that a source routed message from this node failed en route
#define SL_STATUS_ZIGBEE_MANY_TO_ONE_ROUTE_FAILURE             ((sl_status_t)0x0C14)  ///< A Zigbee route error command frame was received indicating that a message sent to this node along a many-to-one route failed en route
#define SL_STATUS_ZIGBEE_STACK_AND_HARDWARE_MISMATCH           ((sl_status_t)0x0C15)  ///< A critical and fatal error indicating that the version of the stack trying to run does not match with the chip it's running on
#define SL_STATUS_ZIGBEE_PAN_ID_CHANGED                        ((sl_status_t)0x0C16)  ///< The local PAN ID has changed. The application can get the new PAN ID by calling ::emberGetPanId()
#define SL_STATUS_ZIGBEE_CHANNEL_CHANGED                       ((sl_status_t)0x0C17)  ///< The channel has changed.
#define SL_STATUS_ZIGBEE_NETWORK_OPENED                        ((sl_status_t)0x0C18)  ///< The network has been opened for joining.
#define SL_STATUS_ZIGBEE_NETWORK_CLOSED                        ((sl_status_t)0x0C19)  ///< The network has been closed for joining.
#define SL_STATUS_ZIGBEE_RECEIVED_KEY_IN_THE_CLEAR             ((sl_status_t)0x0C1A)  ///< An attempt was made to join a Secured Network using a pre-configured key, but the Trust Center sent back a Network Key in-the-clear when an encrypted Network Key was required. (::EMBER_REQUIRE_ENCRYPTED_KEY)
#define SL_STATUS_ZIGBEE_NO_NETWORK_KEY_RECEIVED               ((sl_status_t)0x0C1B)  ///< An attempt was made to join a Secured Network, but the device did not receive a Network Key.
#define SL_STATUS_ZIGBEE_NO_LINK_KEY_RECEIVED                  ((sl_status_t)0x0C1C)  ///< After a device joined a Secured Network, a Link Key was requested (::EMBER_GET_LINK_KEY_WHEN_JOINING) but no response was ever received.
#define SL_STATUS_ZIGBEE_PRECONFIGURED_KEY_REQUIRED            ((sl_status_t)0x0C1D)  ///< An attempt was made to join a Secured Network without a pre-configured key, but the Trust Center sent encrypted data using a pre-configured key.
#define SL_STATUS_ZIGBEE_EZSP_ERROR                            ((sl_status_t)0x0C1E)  ///< A Zigbee EZSP error has occured. Track the origin and corresponding EzspStatus for more info.
#define SL_STATUS_ZIGBEE_ID_DISCOVERY_FAILED                   ((sl_status_t)0x0C1F)  ///< Node ID discovery failed.
#define SL_STATUS_ZIGBEE_NO_APS_ACK                            ((sl_status_t)0x0C20)  ///< Message was sent but no APS ACK received.
#define SL_STATUS_ZIGBEE_APS_MESSAGE_CANCELED                  ((sl_status_t)0x0C21)  ///< APS message was canceled.
#define SL_STATUS_ZIGBEE_ID_DISCOVERY_NOT_ENABLED              ((sl_status_t)0x0C22)  ///< Node ID discovery not enabled.
#define SL_STATUS_ZIGBEE_ID_DISCOVERY_UNDERWAY                 ((sl_status_t)0x0C23)  ///< Message was not sent, Node ID discovery is underway.
#define SL_STATUS_ZIGBEE_SEND_UNICAST_ROUTE_DISCOVERY_UNDERWAY ((sl_status_t)0x0C24)  ///< The message was not sent because a route discovery is currently underway. There is no route to the target until the route discovery completes.
#define SL_STATUS_ZIGBEE_SEND_UNICAST_FAILURE                  ((sl_status_t)0x0C25)  ///< Radius is 0 or message has been dropped because route request failed or failed to submit message to tx queue.
#define SL_STATUS_ZIGBEE_SEND_UNICAST_NO_ROUTE                 ((sl_status_t)0x0C26)  ///< No active route to the destination.
#define SL_STATUS_ZIGBEE_BROADCAST_TO_SLEEPY_CHILDREN_TIMEOUT  ((sl_status_t)0x0C27)  ///< Broadcast message timeout while waiting for sleepy children to poll.
#define SL_STATUS_ZIGBEE_BROADCAST_RELAY_FAILED                ((sl_status_t)0x0C28)  ///< Expected a neighbor to relay the message, but none did.

// -----------------------------------------------------------------------------
// Data Types
/** @brief define global status variable. */
typedef uint32_t sl_status_t;

// -----------------------------------------------------------------------------
// Functions

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************
 *                                      sl_status_get_string_n()
 *
 * @brief    Get a copy of the status string associated to the status code passed, up to
 *           'buffer_length' length, if the string associated to the status code is enabled. If not,
 *           the error code number, in hex, prefixed by "SL_STATUS_" will be copied in the buffer
 *           instead.
 *           For example, the buffer would either contain "SL_STATUS_FAIL" if that status string is
 *           enabled, or "SL_STATUS_0x0001" if the string is disabled, as SL_STATUS_FAIL's
 *           value is 0x0001.
 *
 * @param    status         The status code from which to obtain the status string.
 *
 * @param    buffer         Pointer to a buffer in which the status string will be copied. A terminating
 *                          null-character will be appended after the copied status string.
 *
 * @param    buffer_length  Maximum number of characters that can be written in the buffer, including the
 *                          terminating null-character. If the status string would be longer than the
 *                          available length, it will be truncated and a null-terminating character will
 *                          be the last character contained in the buffer.
 *
 * @return                  The number of characters that would have been written if the buffer_length had been
 *                          sufficiently large, not counting the terminating null character.
 *                          If the status code is invalid, 0 or a negative number is returned.
 *                          Notice that only when this returned value is strictly positive and less than
 *                          buffer_length, the status string has been completely written in the buffer.
 *******************************************************************************************************/
int32_t sl_status_get_string_n(sl_status_t status, char *buffer, uint32_t buffer_length);

/********************************************************************************************************
 *                                         sl_status_print()
 *
 * @brief    Print, through printf, the string associated to the passed status code. If the string
 *           associated to the status code is enabled, the status string will be printed, for example
 *           "SL_STATUS_OK". If the string associated to the status code is disabled, the status number,
 *           in hex, prefixed by "SL_STATUS_" will be printed instead, for example "SL_STATUS_0x0000",
 *           as SL_STATUS_OK's value is 0x0000.
 *
 * @param    status         The status code of which to print the status string.
 *******************************************************************************************************/
void sl_status_print(sl_status_t status);

#ifdef __cplusplus
}
#endif

/** @} (end addtogroup status) */

#endif /* SL_STATUS_H */
