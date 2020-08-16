

#ifndef DCM_TYPES_H
#define DCM_TYPES_H


/**************************************************************************************************/
/* Included header files                                                                          */
/**************************************************************************************************/

#include "Rte_Dcm_Type.h"
/**
 * @ingroup DCM_H
 * This define is to be available from Std_Types.h which is included via ComStack_Types.h
 * but in case the projects have legacy Std_Types.h, it would possible that this define probably isn't existing.
 * In those cases, where this define isn't already available, Dcm redefines the same for its usage\n
 *
 *
 * DCM_E_PENDING\n
 *
 *
 */
#ifndef DCM_E_PENDING
#define DCM_E_PENDING               10u
#endif
/**
 * @ingroup DCM_H
 * This define is to be available from Std_Types.h which is included via ComStack_Types.h
 * but in case the projects have legacy Std_Types.h, it would possible that this define probably isn't existing.
 * In those cases, where this define isn't already available, Dcm redefines the same for its usage\n
 *
 *
 * DCM_E_COMPARE_KEY_FAILED\n
 *
 *
 */
#ifndef DCM_E_COMPARE_KEY_FAILED
#define DCM_E_COMPARE_KEY_FAILED    11
#endif
/**
 * @ingroup DCM_H
 * This define is to be available from Std_Types.h which is included via ComStack_Types.h
 * but in case the projects have legacy Std_Types.h, it would possible that this define probably isn't existing.
 * In those cases, where this define isn't already available, Dcm redefines the same for its usage\n
 *
 *
 * DCM_E_SESSION_NOT_ALLOWED\n
 *
 *
 */
#ifndef DCM_E_SESSION_NOT_ALLOWED
#define DCM_E_SESSION_NOT_ALLOWED   4
#endif
/**
 * @ingroup DCM_H
 * This define is to be available from Std_Types.h which is included via ComStack_Types.h
 * but in case the projects have legacy Std_Types.h, it would possible that this define probably isn't existing.
 * In those cases, where this define isn't already available, Dcm redefines the same for its usage\n
 *
 *
 * DCM_E_FORCE_RCRRP\n
 *
 *
 */

#ifndef DCM_E_FORCE_RCRRP
#define DCM_E_FORCE_RCRRP           12
#endif
/**
 * @ingroup DCM_H
 * This define is to be available from Std_Types.h which is included via ComStack_Types.h
 * but in case the projects have legacy Std_Types.h, it would possible that this define probably isn't existing.
 * In those cases, where this define isn't already available, Dcm redefines the same for its usage\n
 *
 *
 * DCM_E_PROTOCOL_NOT_ALLOWED\n
 *
 *
 */
#ifndef DCM_E_PROTOCOL_NOT_ALLOWED
#define DCM_E_PROTOCOL_NOT_ALLOWED  5
#endif
/**
 * @ingroup DCM_H
 * This define is to be available from Std_Types.h which is included via ComStack_Types.h
 * but in case the projects have legacy Std_Types.h, it would possible that this define probably isn't existing.
 * In those cases, where this define isn't already available, Dcm redefines the same for its usage\n
 *
 *
 * DCM_E_REQUEST_NOT_ACCEPTED\n
 *
 *
 */
#ifndef DCM_E_REQUEST_NOT_ACCEPTED
#define DCM_E_REQUEST_NOT_ACCEPTED  8
#endif

/**
 * @ingroup DCM_H
 * This define is to be available from Std_Types.h which is included via ComStack_Types.h
 * but in case the projects have legacy Std_Types.h, it would possible that this define probably isn't existing.
 * In those cases, where this define isn't already available, Dcm redefines the same for its usage\n
 *
 *
 * DCM_E_REQUEST_ENV_NOK\n
 *
 *
 */
#ifndef DCM_E_REQUEST_ENV_NOK
#define DCM_E_REQUEST_ENV_NOK       9u
#endif

/**
 * @ingroup DCM_H
 * This macro will be used by the appl fucntion of RDBI paged buffer type to indicate that the service
 * called from the appl function is successfully executed and the response is filled in the buffer
 *
 *
 * DCM_E_RDBI_DATA_PENDING\n
 *
 *
 */
#ifndef DCM_E_RDBI_DATA_PENDING
#define DCM_E_RDBI_DATA_PENDING  14
#endif
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * RTE version used by DCM
 * DCM_PRV_AR_4_0_2                    0u      RTE Version AR 4.0.2\n
 * DCM_PRV_AR_4_0_2_HYBRID             1u      RTE Version AR 4.0.2 with some extensions from AR 4.0.3 \n
 * DCM_PRV_AR_3_2_1                    2u      RTE version AR 3.2.1\n
 * DCM_PRV_AR_3_1_4                    2u      RTE version AR 3.1.4\n
 */

#define DCM_PRV_AR_4_0_2                    0u              /* RTE Version AR 4.0.2 */
#define DCM_PRV_AR_4_0_2_HYBRID             1u              /* RTE Version AR 4.0.2 with some extensions from AR 4.0.3 */
#define DCM_PRV_AR_3_2_1                    2u              /* RTE version AR 3.2.1 */
#define DCM_PRV_AR_3_1_4                    3u              /* RTE version AR 3.1.4 */



/**
 *  @ingroup DCMCORE_DSLDSD_AUTOSAR
 * This Table of available Negative Response Codes represents the allowed response Codes an AUTOSAR SW Component shall return after a function call.\n
 * For the allowed NRC of the executed Service ID please refer to the
 * specification of the service in ISO14229-1 (UDS) and ISO15031-5 (OBD/CARB)
 * (see chapter 4.2.4 Response code parameter definition Table 12).
 *
 * DCM_E_GENERALREJECT :Indicates that the requested action has been rejected by the application.\n
 * DCM_E_SERVICENOTSUPPORTED:Indicates that the requested action will not be taken because the application does not support the requested service.\n
 * DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT: Indicates that the requested action will not be taken because the length of the received request message does not match the prescribed length for the specified service or the format of the paramters do not match the prescribed format for the specified service.\n
 * DCM_E_SUBFUNCTIONNOTSUPPORTED:indicates that the requested action will not be taken  because the application does not support the service specific parameters of the request message.\n
 * DCM_E_RESPONSETOOLONG:Indicates that the buffer of the lower layer is not large enough to transmit all data of the response.\n
 * DCM_E_BUSYREPEATREQUEST:Indicates that the application is temporarily too busy to perform the requested operation.\n
 * DCM_E_CONDITIONSNOTCORRECT:Indicates that the requested action will not be taken  because the application prerequisite conditions are not met.\n
 * DCM_E_REQUESTSEQUENCEERROR:Indicates that the requested action will not be taken because the application expects a different sequence of request messages or message as sent by the client.\n
 * DCM_E_NORESPONSEFROMSUBNETCOMPONENT : This return value indicates that the requested action cannot be performed because the subnet component did not respond within the specified time. \n
 * DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION : This response code indicates that the requested action will not be taken because a failure condition, identified by a DTC has occurred and that this failure condition prevents the server from performing the requested action.\n
 * DCM_E_REQUESTOUTOFRANGE :Indicates that the requested action will not be taken because the application has detected that the request message contains a parameter which attempts to substitute a value beyond its range of authority\n
 * DCM_E_SECURITYACCESSDENIED:Indicates that the requested action will not be taken because the application's security strategy has not been satisfied by the client.\n
 * DCM_E_INVALIDKEY:indicates that the application has not given security access because the key sent by the client did not match with the key in the application's memory.\n
 * DCM_E_EXCEEDNUMBEROFATTEMPTS:Indicates that the requested action will not be taken because the client has unsuccessfully attempted to gain security access more times than the application's security strategy will allow.\n
 * DCM_E_REQUIREDTIMEDELAYNOTEXPIRED:Indicates that the requested action will not be taken because the client's latest attempt to gain security access was initiated before the application's required timeout period had elapsed.\n
 * DCM_E_UPLOADDOWNLOADNOTACCEPTED :Indicates that an attempt to upload_download to a application's memory cannot be accomplished due to some fault conditions.\n
 * DCM_E_TRANSFERDATASUSPENDED:Indicates that a data transfer operation was halted due to some fault.\n
 * DCM_E_GENERALPROGRAMMINGFAILURE:Indicates that the application detected an error when erasing or programming a memory location in the permanent memory device (e.g. Flash Memory).\n
 * DCM_E_WRONGBLOCKSEQUENCECOUNTER: Indicates that the application detected an error in the  indicates that the application detected an error in the sequence of blockSequenceCounter values.\n
 * DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION:Indicates that the requested action will not be taken because the application does not support the requested sub-function in the session currently active.\n
 * DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION: Indicates that the requested action will not be taken because the application does not support the requested service in the session currently active.
 * DCM_E_RPMTOOHIGH: Indicates that the requested action will not be taken because the application prerequisite condition for RPM is not met (current RPM is above a pre-programmed maximum threshold).\n
 * DCM_E_RPMTOOLOW:Indicates that the requested action will not be taken because the application prerequisite condition for RPM is not met  (current RPM is below a pre-programmed minimum threshold).\n
 * DCM_E_ENGINEISRUNNING:This is required for those actuator tests which cannot be actuated while the Engine is running. This is different from RPM too high negative response, and needs to be allowed.\n
 * DCM_E_ENGINEISNOTRUNNING:This is required for those actuator tests which cannot be actuated unless the Engine is running. This is different from RPM too low negative response, and needs to be allowed.\n
 * DCM_E_ENGINERUNTIMETOOLOW:This return value indicates that the requested action will not be taken because the application prerequisite condition for engine run time is not met (current engine run time is below a preprogrammed limit).\n
 * DCM_E_TEMPERATURETOOHIGH:This return value indicates that the requested action will not be taken because the application prerequisite condition for temperature is not met (current temperature is above a preprogrammed maximum threshold).\n
 * DCM_E_TEMPERATURETOOLOW:This return value indicates that the requested action will not be taken because the application prerequisite condition for temperature is not met (current temperature is below a preprogrammed minimum threshold).\n
 * DCM_E_VEHICLESPEEDTOOHIGH:This return value indicates that the requested action will not be taken  because the application prerequisite condition for vehicle speed is not met (current VS is above a pre-programmed maximum threshold).\n
 * DCM_E_VEHICLESPEEDTOOLOW:This return value indicates that the requested action will not be taken because the application prerequisite condition for vehicle speed is not met (current VS is below a pre-programmed minimum threshold).\n
 * DCM_E_THROTTLE_PEDALTOOHIGH:This return value indicates that the requested action will not be taken because the application prerequisite condition for throttle/pedal position is not met (current TP/APP is above a pre-programmed maximum threshold).\n
 * DCM_E_THROTTLE_PEDALTOOLOW:This return value indicates that the requested action will not be taken because the application prerequisite condition for throttle/pedal position is not met (current TP/APP is below a pre-programmed minimum threshold).\n
 * DCM_E_TRANSMISSIONRANGENOTINNEUTRAL:This return value indicates that the requested action will not be taken because the application prerequisite condition for being in neutral is not met (current transmission range is not in neutral).\n
 * DCM_E_TRANSMISSIONRANGENOTINGEAR:This return value indicates that the requested action will not be taken because the application prerequisite condition for being in gear is not met (current transmission range is not in gear).\n
 * DCM_E_BRAKESWITCH_NOTCLOSED:For safety reasons this is required for certain tests before it begins,and must be maintained for the entire duration of the test.\n
 * DCM_E_SHIFTERLEVERNOTINPARK:For safety reasons, this is required for certain tests before it begins, and must be maintained for the entire duration of the test.\n
 * DCM_E_TORQUECONVERTERCLUTCHLOCKED:This return value indicates that the requested action will not be taken because the application prerequisite condition for torque converter clutch is not met (current TCC status above a pre-programmed limit or locked).\n
 * DCM_E_VOLTAGETOOHIGH:This return value indicates that the requested action will not be taken because the application prerequisite condition for voltage at the primary pin of the application (ECU) is not met (current voltage is above a pre-programmed maximum threshold).\n
 * DCM_E_VOLTAGETOOLOW:This return value indicates that the requested action will not be taken  because the application prerequisite condition for voltage at the primary pin of the application (ECU) is not met (current voltage is below a pre-programmed maximum threshold).\n
 *
 */
/**
 * This return value indicates that the requested action has been rejected
 * by the application. The generalReject return value shall only be
 * implemented in the application if none of the negative return values
 * defined in this document meet the needs of the implementation. At no
 * means shall this return value be a general replacement for the return
 * values defined in this document.
 */
#ifndef DCM_E_GENERALREJECT
#define DCM_E_GENERALREJECT 0x10
#endif
/**
 * This return value indicates that the requested action will not be taken
 * because the application does not support the requested service.
 * The application shall send this return value in case the client has sent
 * a request message with a service identifier, which is either unknown or
 * not supported by the application. Therefore this negative return value is
 * not shown in the list of negative return values to be supported for a
 * diagnostic service, because this negative return value is not applicable
 * for supported services.
 */
#ifndef DCM_E_SERVICENOTSUPPORTED
#define DCM_E_SERVICENOTSUPPORTED 0x11
#endif
/**
 * This return value indicates that the requested action will not be taken
 * because the application does not support the service specific parameters
 * of the request message. The application shall send this return value in
 * case the client has sent a request message with a known and supported
 * service identifier but with "sub function" which is either unknown or not
 * supported.
 */
#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTED
#define DCM_E_SUBFUNCTIONNOTSUPPORTED 0x12
#endif
/**
 * This return value indicates that the requested action will not be taken
 * because the length of the received request message does not match the
 * prescribed length for the specified service or the format of the
 * paramters do not match the prescribed format for the specified service.
 */
#ifndef DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT 0x13
#endif

/**
 * This return value indicates that the buffer of the lower layer is not
 * large enough to transmit all data of the response.
 */
#ifndef DCM_E_RESPONSETOOLONG
#define DCM_E_RESPONSETOOLONG 0x14
#endif
/**
 * This return value indicates that the application is temporarily too busy
 * to perform the requested operation. In this circumstance the client shall
 * perform repetition of the "identical request message" or "another request
 * message". The repetition of the request shall be delayed by a time
 * specified in the respective implementation documents.
 * Example: In a multi-client environment the diagnostic request of one
 * client might be blocked temporarily by a NRC 0x21 while a different
 * client finishes a diagnostic task.
 * Note: If the application is able to perform the diagnostic task but needs
 * additional time to finish the task and prepare the response, the NRC 0x78
 * shall be used instead of NRC 0x21. This return value is in general supported
 * by each diagnostic service, as not otherwise stated in the data link
 * specific implementation document, therefore it is not listed in the list
 * of applicable return values of the diagnostic services.
 */
#ifndef DCM_E_BUSYREPEATREQUEST
#define DCM_E_BUSYREPEATREQUEST 0x21
#endif
/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite conditions are not met.
 */
#ifndef DCM_E_CONDITIONSNOTCORRECT
#define DCM_E_CONDITIONSNOTCORRECT 0x22
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application expects a different sequence of request messages
 * or message as sent by the client. This may occur when sequence sensitive
 * requests are issued in the wrong order.
 * EXAMPLE A successful SecurityAccess service specifies a sequence of
 * requestSeed and sendKey as susb-fuctions in the request messages. If the
 * sequence is sent different by the client the application shall send a
 * negative response message with the negative return value 0x24-
 * requestSequenceError.
 */
#ifndef DCM_E_REQUESTSEQUENCEERROR
#define DCM_E_REQUESTSEQUENCEERROR 0x24
#endif
/**
 * This return value indicates that the requested action cannot be performed
 * because the subnet component did not respond within the specified time.
 */

#ifndef DCM_E_NORESPONSEFROMSUBNETCOMPONENT
#define DCM_E_NORESPONSEFROMSUBNETCOMPONENT 0x25
#endif

/**
 * This response code indicates that the requested action will not be taken
 * because a failure condition, identified by a DTC has occurred and that this
 * failure condition prevents the server from performing the requested action.
 */

#ifndef DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION
#define DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION 0x26
#endif


/**
 * This return value indicates that the requested action will not be taken
 * because the application has detected that the request message contains a
 * parameter which attempts to substitute a value beyond its range of
 * authority (e.g. attempting to substitute a data byte of 111 when the data
 * is only defined to 100), or which attempts to access a dataIdentifier-
 * routineIdentifer that is not supported or not supported in active session.
 * This return value shall be implemented for all services, which allow the
 * client to read data write data, or adjust functions by data in the
 * application.
 */
#ifndef DCM_E_REQUESTOUTOFRANGE
#define DCM_E_REQUESTOUTOFRANGE 0x31
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application's security strategy has not been satisfied by the
 * client. The application shall send this return value if one of the
 * following cases occur:
 * - the test conditions of the application are not met,
 * - the required message sequence e.g. DiagnosticSessionControl,
 *   securityAccess is not met,
 * - the client has sent a request message which requires an unlocked
 *   application.
 * Beside the mandatory use of this negative return value as specified in
 * the applicable services within this standard, this negative return value
 * can also be used for any case where security is required and is not yet
 * granted to perform the required service.
 */
#ifndef DCM_E_SECURITYACCESSDENIED
#define DCM_E_SECURITYACCESSDENIED 0x33
#endif

/**
 * This return value indicates that the application has not given security
 * access because the key sent by the client did not match with the key in
 * the application's memory. This counts as an attempt to gain security.
 * The application shall remain locked and increment is internal
 * securityAccessFailed counter.
 */
#ifndef DCM_E_INVALIDKEY
#define DCM_E_INVALIDKEY 0x35
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the client has unsuccessfully attempted to gain security access
 * more times than the application's security strategy will allow.
 */
#ifndef DCM_E_EXCEEDNUMBEROFATTEMPTS
#define DCM_E_EXCEEDNUMBEROFATTEMPTS 0x36
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the client's latest attempt to gain security access was initiated
 * before the application's required timeout period had elapsed.
 */
#ifndef DCM_E_REQUIREDTIMEDELAYNOTEXPIRED
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED 0x37
#endif

/**
 * This return value indicates that an attempt to upload_download to a
 * application's memory cannot be accomplished due to some fault conditions.
 */
#ifndef DCM_E_UPLOADDOWNLOADNOTACCEPTED
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED 0x70
#endif

/**
 * This return value indicates that a data transfer operation was halted due
 * to some fault.
 */
#ifndef DCM_E_TRANSFERDATASUSPENDED
#define DCM_E_TRANSFERDATASUSPENDED 0x71
#endif

/**
 * This return value indicates that the application detected an error when
 * erasing or programming a memory location in the permanent memory device
 * (e.g. Flash Memory).
 */
#ifndef DCM_E_GENERALPROGRAMMINGFAILURE
#define DCM_E_GENERALPROGRAMMINGFAILURE 0x72
#endif

/**
 * This return value indicates that the application detected an error in the
 * sequence of blockSequenceCounter values. Note that the repetition of a
 * TransferData request message with a blockSequenceCounter equal to the one
 * included in the previous TransferData request message shall be accepted
 * by the application.
 */
#ifndef DCM_E_WRONGBLOCKSEQUENCECOUNTER
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER 0x73
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application does not support the requested sub-function in
 * the session currently active. This return value shall only be used when
 * the requested subfunction is known to be supported in another session,
 * otherwise return value SFNS (subFunctionNotSupported) shall be used.
 * This return value shall be supported by each diagnostic service with a
 * sub-function parameter, if not otherwise stated in the data link specific
 * implementation document, therefore it is not listed in the list of
 * applicable return values of the diagnostic services.
 */
#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION 0x7E
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application does not support the requested service in the
 * session currently active. This return value shall only be used when the
 * requested service is known to be supported in another session, otherwise
 * return value SNS (serviceNotSupported) shall be used. This return value
 * is in general supported by each diagnostic service, as not otherwise
 * stated in the data link specific implementation document, therefore it is
 * not listed in the list of applicable return values of the diagnostic
 * services.
 */
#ifndef DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION 0x7F
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for RPM is not met
 * (current RPM is above a pre-programmed maximum threshold).
 */
#ifndef DCM_E_RPMTOOHIGH
#define DCM_E_RPMTOOHIGH 0x81
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for RPM is not met
 * (current RPM is below a pre-programmed minimum threshold).
 */
#ifndef DCM_E_RPMTOOLOW
#define DCM_E_RPMTOOLOW 0x82
#endif

/**
 * This is required for those actuator tests which cannot be actuated while
 * the Engine is running. This is different from RPM too high negative
 * response, and needs to be allowed.
 */
#ifndef DCM_E_ENGINEISRUNNING
#define DCM_E_ENGINEISRUNNING 0x83
#endif

/**
 * This is required for those actuator tests which cannot be actuated unless
 * the Engine is running. This is different from RPM too low negative
 * response, and needs to be allowed.
 */
#ifndef DCM_E_ENGINEISNOTRUNNING
#define DCM_E_ENGINEISNOTRUNNING  0x84
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for engine run time is not
 * met (current engine run time is below a preprogrammed limit).
 */
#ifndef DCM_E_ENGINERUNTIMETOOLOW
#define DCM_E_ENGINERUNTIMETOOLOW 0x85
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for temperature is not met
 * (current temperature is above a preprogrammed maximum threshold).
 */
#ifndef DCM_E_TEMPERATURETOOHIGH
#define DCM_E_TEMPERATURETOOHIGH 0x86
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for temperature is not met
 * (current temperature is below a preprogrammed minimum threshold).
 */
#ifndef DCM_E_TEMPERATURETOOLOW
#define DCM_E_TEMPERATURETOOLOW 0x87
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for vehicle speed is not
 * met (current VS is above a pre-programmed maximum threshold).
 */
#ifndef DCM_E_VEHICLESPEEDTOOHIGH
#define DCM_E_VEHICLESPEEDTOOHIGH 0x88
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for vehicle speed is not
 * met (current VS is below a pre-programmed minimum threshold).
 */
#ifndef DCM_E_VEHICLESPEEDTOOLOW
#define DCM_E_VEHICLESPEEDTOOLOW 0x89
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for throttle/pedal
 * position is not met (current TP/APP is above a pre-programmed maximum
 * threshold).
 */
#ifndef DCM_E_THROTTLE_PEDALTOOHIGH
#define DCM_E_THROTTLE_PEDALTOOHIGH 0x8A
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for throttle/pedal
 * position is not met (current TP/APP is below a pre-programmed minimum
 * threshold).
 */
#ifndef DCM_E_THROTTLE_PEDALTOOLOW
#define DCM_E_THROTTLE_PEDALTOOLOW 0x8B
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for being in neutral is
 * not met (current transmission range is not in neutral).
 */
#ifndef DCM_E_TRANSMISSIONRANGENOTINNEUTRAL
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL 0x8C
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for being in gear is not
 * met (current transmission range is not in gear).
 */
#ifndef DCM_E_TRANSMISSIONRANGENOTINGEAR
#define DCM_E_TRANSMISSIONRANGENOTINGEAR 0x8D
#endif
/**
 * For safety reasons this is required for certain tests before it begins,
 * and must be maintained for the entire duration of the test.
 */
#ifndef DCM_E_BRAKESWITCH_NOTCLOSED
#define DCM_E_BRAKESWITCH_NOTCLOSED 0x8F
#endif

/**
 * For safety reasons, this is required for certain tests before it begins,
 * and must be maintained for the entire duration of the test.
 */
#ifndef DCM_E_SHIFTERLEVERNOTINPARK
#define DCM_E_SHIFTERLEVERNOTINPARK 0x90
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for torque converter
 * clutch is not met (current TCC status above a pre-programmed limit or
 * locked).
 */
#ifndef DCM_E_TORQUECONVERTERCLUTCHLOCKED
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED 0x91
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for voltage at the primary
 * pin of the application (ECU) is not met (current voltage is above a pre-
 * programmed maximum threshold).
 */
#ifndef DCM_E_VOLTAGETOOHIGH
#define DCM_E_VOLTAGETOOHIGH 0x92
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite condition for voltage at the primary
 * pin of the application (ECU) is not met (current voltage is below a pre-
 * programmed maximum threshold).
 */
#ifndef DCM_E_VOLTAGETOOLOW
#define DCM_E_VOLTAGETOOLOW 0x93
#endif

/**
 *  @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_OpStatusType :
 * DCM_INITIAL\n
 * DCM_PENDING\n
 * DCM_CANCEL\n
 * DCM_FORCE_RCRRP_OK\n
 * Dcm_OpStatusType :At first call of an operation using the Dcm_OpStatusType,the DCM call the operation with OpStatus = DCM_INITIAL\n
 * if the value DCM_E_FORCE_RCRRP is returned from an operation using Dcm_OpStatusType,the DCM shall invoke the transmit request for RCR-RP (NRC 0x78 transmission)
 * the DCM shall invoke the transmit request for RCR-RP (NRC 0x78 transmission)
 * and the DCM shall not realize further invokation of the operation till RCR-RP is transmitted.
 * the DCM calls, from Dcm_MainFunction, the operation again with OpStatus = DCM_FORCE_RCRRP_OK.
 * If a DCM_E_PENDING value is returned from an operation using the Dcm_OpStatusType,
 * the DCM call the operation on each Dcm_MainFunction call with OpStatus = DCM_PENDING until E_OK return.
 */


#ifndef DCM_INITIAL
#define DCM_INITIAL 0x00    /* Indicates the initial call to the operation */
#endif

#ifndef DCM_PENDING
#define DCM_PENDING 0x01    /* Indicates that a pending return has been done on the previous call of the operation */
#endif

#ifndef DCM_CANCEL
#define DCM_CANCEL  0x02    /* Indicates that the DCM requests to cancel the pending operation */
#endif

#ifndef DCM_FORCE_RCRRP_OK
#define DCM_FORCE_RCRRP_OK  0x03    /* Confirm a response pending transmission */
#endif


/* Service OpStatus value : Service State for doing the checks */

/**
 *  @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Dcm_OpStatusType :
 *  DCM_CHECKDATA \n
 *  The OpStatus will be updated to DCM_CHECKDATA after the basic checks are successfully completed in the DCM_INITIAL.\n
 *  In this state Furthermore service related checks are done.\n
 *  If all the checks are done successfully then the statemachine will be updated to DCM_PROCESSSERVICE\n
 *  else if Pending is returned by any of the API's then the  return value will be updated to DCM_E_PENDING\n
 *  else if any of the checks fail then the return value will be updated to E_NOT_OK\n
 */


#ifndef DCM_CHECKDATA
#define DCM_CHECKDATA 0x04
#endif

/* Service OpStatus Value: Service State for doing the Processing */

/**
 *  @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Dcm_OpStatusType :
 *  DCM_PROCESSSERVICE \n
 *  The OpStatus will be updated to DCM_PROCESSSERVICE after the basic checks are successfully completed in the DCM_CHECKDATA.\n
 *  In this State the Service will be processed.\n
 *  On successful completion the return value will be updated to E_OK\n
 *  else if Pending is returned by any of the API's then the  return value will be updated to DCM_E_PENDING\n
 *  else if any of the checks fail then the return value will be updated to E_NOT_OK\n
*/

#ifndef DCM_PROCESSSERVICE
#define DCM_PROCESSSERVICE  0x05
#endif


/* FC_VariationPoint_START */
                /*Obsolete*/
#ifndef     DCM_AR_4_0_2
#define     DCM_AR_4_0_2                DCM_PRV_AR_4_0_2
#endif
#ifndef     DCM_AR_4_0_2_HYBRID
#define     DCM_AR_4_0_2_HYBRID         DCM_PRV_AR_4_0_2_HYBRID
#endif
#ifndef     DCM_AR_3_2_1
#define     DCM_AR_3_2_1                DCM_PRV_AR_3_2_1
#endif

/* FC_VariationPoint_END */



#endif
/* DCM_TYPES_H */
