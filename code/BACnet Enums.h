#include <stdio.h>
// MAG 260401
// This file is to hold enumerations used by other classes (property, object, devices, etc..)

namespace BACenums {
	// MAG 260409 copied from BACnetObjectType enumeration in 135-2024
	// Note any addenda properties added here:
	enum class BACObj {
		ANALOG_INPUT,					// 0
		ANALOG_OUTPUT,					// 1
		ANALOG_VALUE,					// 2
		BINARY_INPUT,					// 3
		BINARY_OUTPUT,					// 4
		BINARY_VALUE,					// 5
		CALENDAR,						// 6
		COMMAND,						// 7
		DEVICE,							// 8
		EVENT_ENROLLMENT,				// 9
		FILE,							// 10
		GROUP,							// 11
		LOOP,							// 12
		MULTI_STATE_INPUT,				// 13
		MULTI_STATE_OUTPUT,				// 14
		NOTIFICATION_CLASS,				// 15
		PROGRAM,						// 16
		SCHEDULE,						// 17
		AVERAGING,						// 18
		MULTI_STATE_VALUE,				// 19
		TREND_LOG,						// 20
		LIFE_SAFETY_POINT,				// 21
		LIFE_SAFETY_ZONE,				// 22
		ACCUMULATOR,					// 23
		PULSE_CONVERTER,				// 24
		EVENT_LOG,						// 25
		GLOBAL_GROUP,					// 26
		TREND_LOG_MULTIPLE,				// 27
		LOAD_CONTROL,					// 28
		STRUCTURED_VIEW,				// 29
		ACCESS_DOOR,					// 30
		TIMER,							// 31
		ACCESS_CREDENTIAL,				// 32
		ACCESS_POINT,					// 33
		ACCESS_RIGHTS,					// 34
		ACCESS_USER,					// 35
		ACCESS_ZONE,					// 36
		CREDENTIAL_DATA_INPUT,			// 37
		NETWORK_SECURITY,				// 38
		BITSTRING_VALUE,				// 39
		CHARACTERSTRING_VALUE,			// 40
		DATEPATTERN_VALUE,				// 41
		DATE_VALUE,						// 42
		DATETIMEPATTERN_VALUE,			// 43
		DATETIME_VALUE,					// 44
		INTEGER_VALUE,					// 45
		LARGE_ANALOG_VALUE,				// 46
		OCTETSTRING_VALUE,				// 47
		POSITIVE_INTEGER_VALUE,			// 48
		TIMEPATTERN_VALUE,				// 49
		TIME_VALUE,						// 50
		NOTIFICATION_FORWARDER,			// 51
		ALERT_ENROLLMENT,				// 52
		CHANNEL,						// 53
		LIGHTING_OUTPUT,				// 54
		BINARY_LIGHTING_OUTPUT,			// 55
		NETWORK_PORT,					// 56
		ELEVATOR_GROUP,					// 57
		ESCALATOR,						// 58
		LIFT,							// 59
		STAGING,						// 60
		AUDIT_LOG,						// 61
		AUDIT_REPORTER,					// 62
		COLOR,							// 63
		COLOR_TEMPERATURE,				// 64
		ERROR_OBJECT					// 65 MAG not a real object
	};

	// MAG 260409 copied from BACnetPropertyIdentifier enumeration in 135-2024
	// Note any addenda properties added here:
	// NOTE salted with "en_" due to number of naming conflicts with #define statements
	// NOTE if changing number of entries in this enum also update code in BACnetProperty::GetPropertyType(int obj, int prop)
	enum class BACProp {
		en_ACKED_TRANSITIONS,                              //0
		en_ACK_REQUIRED,                                   //1
		en_ACTION,                                         //2
		en_ACTION_TEXT,                                    //3
		en_ACTIVE_TEXT,                                    //4
		en_ACTIVE_VT_SESSIONS,                             //5
		en_ALARM_VALUE,                                    //6
		en_ALARM_VALUES,                                   //7
		en_ALL,                                            //8
		en_ALL_WRITES_SUCCESSFUL,                          //9
		en_APDU_SEGMENT_TIMEOUT,                           //10
		en_APDU_TIMEOUT,                                   //11
		en_APPLICATION_SOFTWARE_VERSION,                   //12
		en_ARCHIVE,                                        //13
		en_BIAS,                                           //14
		en_CHANGE_OF_STATE_COUNT,                          //15
		en_CHANGE_OF_STATE_TIME,                           //16
		en_NOTIFICATION_CLASS,                             //17
		en_UNASSIGNED18,                                   //18
		en_CONTROLLED_VARIABLE_REFERENCE,                  //19
		en_CONTROLLED_VARIABLE_UNITS,                      //20
		en_CONTROLLED_VARIABLE_VALUE,                      //21
		en_COV_INCREMENT,                                  //22
		en_DATE_LIST,                                      //23
		en_DAYLIGHT_SAVINGS_STATUS,                        //24
		en_DEADBAND,                                       //25
		en_DERIVATIVE_CONSTANT,                            //26
		en_DERIVATIVE_CONSTANT_UNITS,                      //27
		en_DESCRIPTION,                                    //28
		en_DESCRIPTION_OF_HALT,                            //29
		en_DEVICE_ADDRESS_BINDING,                         //30
		en_DEVICE_TYPE,                                    //31
		en_EFFECTIVE_PERIOD,                               //32
		en_ELAPSED_ACTIVE_TIME,                            //33
		en_ERROR_LIMIT,                                    //34
		en_EVENT_ENABLE,                                   //35
		en_EVENT_STATE,                                    //36
		en_EVENT_TYPE,                                     //37
		en_EXCEPTION_SCHEDULE,                             //38
		en_FAULT_VALUES,                                   //39
		en_FEEDBACK_VALUE,                                 //40
		en_FILE_ACCESS_METHOD,                             //41
		en_FILE_SIZE,                                      //42
		en_FILE_TYPE,                                      //43
		en_FIRMWARE_REVISION,                              //44
		en_HIGH_LIMIT,                                     //45
		en_INACTIVE_TEXT,                                  //46
		en_IN_PROCESS,                                     //47
		en_INSTANCE_OF,                                    //48
		en_INTEGRAL_CONSTANT,                              //49
		en_INTEGRAL_CONSTANT_UNITS,                        //50
		en_ISSUE_CONFIRMED_NOTIFICATIONS,                  //51
		en_LIMIT_ENABLE,                                   //52
		en_LIST_OF_GROUP_MEMBERS,                          //53
		en_LIST_OF_OBJECT_PROPERTY_REFERENCES,             //54
		en_LIST_OF_SESSION_KEYS,                           //55
		en_LOCAL_DATE,                                     //56
		en_LOCAL_TIME,                                     //57
		en_LOCATION,                                       //58
		en_LOW_LIMIT,                                      //59
		en_MANIPULATED_VARIABLE_REFERENCE,                 //60
		en_MAXIMUM_OUTPUT,                                 //61
		en_MAX_APDU_LENGTH_ACCEPTED,                       //62
		en_MAX_INFO_FRAMES,                                //63
		en_MAX_MANAGER,                                    //64
		en_MAX_PRES_VALUE,                                 //65
		en_MINIMUM_OFF_TIME,                               //66
		en_MINIMUM_ON_TIME,                                //67
		en_MINIMUM_OUTPUT,                                 //68
		en_MIN_PRES_VALUE,                                 //69
		en_MODEL_NAME,                                     //70
		en_MODIFICATION_DATE,                              //71
		en_NOTIFY_TYPE,                                    //72
		en_NUMBER_OF_APDU_RETRIES,                         //73
		en_NUMBER_OF_STATES,                               //74
		en_OBJECT_IDENTIFIER,                              //75
		en_OBJECT_LIST,                                    //76
		en_OBJECT_NAME,                                    //77
		en_OBJECT_PROPERTY_REFERENCE,                      //78
		en_OBJECT_TYPE,                                    //79
		en_OPTIONAL,                                       //80
		en_OUT_OF_SERVICE,                                 //81
		en_OUTPUT_UNITS,                                   //82
		en_EVENT_PARAMETERS,                               //83
		en_POLARITY,                                       //84
		en_PRESENT_VALUE,                                  //85
		en_PRIORITY,                                       //86
		en_PRIORITY_ARRAY,                                 //87
		en_PRIORITY_FOR_WRITING,                           //88
		en_PROCESS_IDENTIFIER,                             //89
		en_PROGRAM_CHANGE,                                 //90
		en_PROGRAM_LOCATION,                               //91
		en_PROGRAM_STATE,                                  //92
		en_PROPORTIONAL_CONSTANT,                          //93
		en_PROPORTIONAL_CONSTANT_UNITS,                    //94
		en_PROTOCOL_CONFORMANCE_CLASS,                     //95
		en_PROTOCOL_OBJECT_TYPES_SUPPORTED,                //96
		en_PROTOCOL_SERVICES_SUPPORTED,                    //97
		en_PROTOCOL_VERSION,                               //98
		en_READ_ONLY,                                      //99
		en_REASON_FOR_HALT,                                //100
		en_RECIPIENT,                                      //101
		en_RECIPIENT_LIST,                                 //102
		en_RELIABILITY,                                    //103
		en_RELINQUISH_DEFAULT,                             //104
		en_REQUIRED,                                       //105
		en_RESOLUTION,                                     //106
		en_SEGMENTATION_SUPPORTED,                         //107
		en_SETPOINT,                                       //108
		en_SETPOINT_REFERENCE,                             //109
		en_STATE_TEXT,                                     //110
		en_STATUS_FLAGS,                                   //111
		en_SYSTEM_STATUS,                                  //112
		en_TIME_DELAY,                                     //113
		en_TIME_OF_ACTIVE_TIME_RESET,                      //114
		en_TIME_OF_STATE_COUNT_RESET,                      //115
		en_TIME_SYNCHRONIZATION_RECIPIENTS,                //116
		en_UNITS,                                          //117
		en_UPDATE_INTERVAL,                                //118
		en_UTC_OFFSET,                                     //119
		en_VENDOR_IDENTIFIER,                              //120
		en_VENDOR_NAME,                                    //121
		en_VT_CLASSES_SUPPORTED,                           //122
		en_WEEKLY_SCHEDULE,                                //123
		en_ATTEMPTED_SAMPLES,                              //124
		en_AVERAGE_VALUE,                                  //125
		en_BUFFER_SIZE,                                    //126
		en_CLIENT_COV_INCREMENT,                           //127
		en_COV_RESUBSCRIPTION_INTERVAL,                    //128
		en_CURRENT_NOTIFY_TIME,                            //129
		en_EVENT_TIME_STAMPS,                              //130
		en_LOG_BUFFER,                                     //131
		en_LOG_DEVICE_OBJECT_PROPERTY,                     //132
		en_ENABLE,                                         //133
		en_LOG_INTERVAL,                                   //134
		en_MAXIMUM_VALUE,                                  //135
		en_MINIMUM_VALUE,                                  //136
		en_NOTIFICATION_THRESHOLD,                         //137
		en_PREVIOUS_NOTIFY_TIME,                           //138
		en_PROTOCOL_REVISION,                              //139
		en_RECORDS_SINCE_NOTIFICATION,                     //140
		en_RECORD_COUNT,                                   //141
		en_START_TIME,                                     //142
		en_STOP_TIME,                                      //143
		en_STOP_WHEN_FULL,                                 //144
		en_TOTAL_RECORD_COUNT,                             //145
		en_VALID_SAMPLES,                                  //146
		en_WINDOW_INTERVAL,                                //147
		en_WINDOW_SAMPLES,                                 //148
		en_MAXIMUM_VALUE_TIMESTAMP,                        //149
		en_MINIMUM_VALUE_TIMESTAMP,                        //150
		en_VARIANCE_VALUE,                                 //151
		en_ACTIVE_COV_SUBSCRIPTIONS,                       //152
		en_BACKUP_FAILURE_TIMEOUT,                         //153
		en_CONFIGURATION_FILES,                            //154
		en_DATABASE_REVISION,                              //155
		en_DIRECT_READING,                                 //156
		en_LAST_RESTORE_TIME,                              //157
		en_MAINTENANCE_REQUIRED,                           //158
		en_MEMBER_OF,                                      //159
		en_MODE,                                           //160
		en_OPERATION_EXPECTED,                             //161
		en_SETTING,                                        //162
		en_SILENCED,                                       //163
		en_TRACKING_VALUE,                                 //164
		en_ZONE_MEMBERS,                                   //165
		en_LIFE_SAFETY_ALARM_VALUES,                       //166
		en_MAX_SEGMENTS_ACCEPTED,                          //167
		en_PROFILE_NAME,                                   //168
		en_AUTO_SUBORDINATE_DISCOVERY,                     //169
		en_MANUAL_SUBORDINATE_ADDRESS_BINDING,             //170
		en_SUBORDINATE_ADDRESS_BINDING,                    //171
		en_SUBORDINATE_PROXY_ENABLE,                       //172
		en_LAST_NOTIFY_RECORD,                             //173
		en_SCHEDULE_DEFAULT,                               //174
		en_ACCEPTED_MODES,                                 //175
		en_ADJUST_VALUE,                                   //176
		en_COUNT,                                          //177
		en_COUNT_BEFORE_CHANGE,                            //178
		en_COUNT_CHANGE_TIME,                              //179
		en_COV_PERIOD,                                     //180
		en_INPUT_REFERENCE,                                //181
		en_LIMIT_MONITORING_INTERVAL,                      //182
		en_LOGGING_OBJECT,                                 //183
		en_LOGGING_RECORD,                                 //184
		en_PRESCALE,                                       //185
		en_PULSE_RATE,                                     //186
		en_SCALE,                                          //187
		en_SCALE_FACTOR,                                   //188
		en_UPDATE_TIME,                                    //189
		en_VALUE_BEFORE_CHANGE,                            //190
		en_VALUE_SET,                                      //191
		en_VALUE_CHANGE_TIME,                              //192
		en_ALIGN_INTERVALS,                                //193
		en_UNASSIGNED194,                                  //194
		en_INTERVAL_OFFSET,                                //195
		en_LAST_RESTART_REASON,                            //196
		en_LOGGING_TYPE,                                   //197
		en_UNASSIGNED198,                                  //198
		en_UNASSIGNED199,                                  //199
		en_UNASSIGNED200,                                  //200
		en_UNASSIGNED201,                                  //201
		en_RESTART_NOTIFICATION_RECIPIENTS,                //202
		en_TIME_OF_DEVICE_RESTART,                         //203
		en_TIME_SYNCHRONIZATION_INTERVAL,                  //204
		en_TRIGGER,                                        //205
		en_UTC_TIME_SYNCHRONIZATION_RECIPIENTS,            //206
		en_NODE_SUBTYPE,                                   //207
		en_NODE_TYPE,                                      //208
		en_STRUCTURED_OBJECT_LIST,                         //209
		en_SUBORDINATE_ANNOTATIONS,                        //210
		en_SUBORDINATE_LIST,                               //211
		en_ACTUAL_SHED_LEVEL,                              //212
		en_DUTY_WINDOW,                                    //213
		en_EXPECTED_SHED_LEVEL,                            //214
		en_FULL_DUTY_BASELINE,                             //215
		en_UNASSIGNED216,                                  //216
		en_UNASSIGNED217,                                  //217
		en_REQUESTED_SHED_LEVEL,                           //218
		en_SHED_DURATION,                                  //219
		en_SHED_LEVEL_DESCRIPTIONS,                        //220
		en_SHED_LEVELS,                                    //221
		en_STATE_DESCRIPTION,                              //222
		en_UNASSIGNED233,                                  //223
		en_UNASSIGNED234,                                  //224
		en_UNASSIGNED235,                                  //225
		en_DOOR_ALARM_STATE,                               //226
		en_DOOR_EXTENDED_PULSE_TIME,                       //227
		en_DOOR_MEMBERS,                                   //228
		en_DOOR_OPEN_TOO_LONG_TIME,                        //229
		en_DOOR_PULSE_TIME,                                //230
		en_DOOR_STATUS,                                    //231
		en_DOOR_UNLOCK_DELAY_TIME,                         //232
		en_LOCK_STATUS,                                    //233
		en_MASKED_ALARM_VALUES,                            //234
		en_SECURED_STATUS,                                 //235
		en_UNASSIGNED236,                                  //236
		en_UNASSIGNED237,                                  //237
		en_UNASSIGNED238,                                  //238
		en_UNASSIGNED239,                                  //239
		en_UNASSIGNED240,                                  //240
		en_UNASSIGNED241,                                  //241
		en_UNASSIGNED242,                                  //242
		en_UNASSIGNED243,                                  //243
		en_ABSENTEE_LIMIT,                                 //244
		en_ACCESS_ALARM_EVENTS,                            //245
		en_ACCESS_DOORS,                                   //246
		en_ACCESS_EVENT,                                   //247
		en_ACCESS_EVENT_AUTHENTICATION_FACTOR,             //248
		en_ACCESS_EVENT_CREDENTIAL,                        //249
		en_ACCESS_EVENT_TIME,                              //250
		en_ACCESS_TRANSACTION_EVENTS,                      //251
		en_ACCOMPANIMENT,                                  //252
		en_ACCOMPANIMENT_TIME,                             //253
		en_ACTIVATION_TIME,                                //254
		en_ACTIVE_AUTHENTICATION_POLICY,                   //255
		en_ASSIGNED_ACCESS_RIGHTS,                         //256
		en_AUTHENTICATION_FACTORS,                         //257
		en_AUTHENTICATION_POLICY_LIST,                     //258
		en_AUTHENTICATION_POLICY_NAMES,                    //259
		en_AUTHENTICATION_STATUS,                          //260
		en_AUTHORIZATION_MODE,                             //261
		en_BELONGS_TO,                                     //262
		en_CREDENTIAL_DISABLE,                             //263
		en_CREDENTIAL_STATUS,                              //264
		en_CREDENTIALS,                                    //265
		en_CREDENTIALS_IN_ZONE,                            //266
		en_DAYS_REMAINING,                                 //267
		en_ENTRY_POINTS,                                   //268
		en_EXIT_POINTS,                                    //269
		en_EXPIRATION_TIME,                                //270
		en_EXTENDED_TIME_ENABLE,                           //271
		en_FAILED_ATTEMPT_EVENTS,                          //272
		en_FAILED_ATTEMPTS,                                //273
		en_FAILED_ATTEMPTS_TIME,                           //274
		en_LAST_ACCESS_EVENT,                              //275
		en_LAST_ACCESS_POINT,                              //276
		en_LAST_CREDENTIAL_ADDED,                          //277
		en_LAST_CREDENTIAL_ADDED_TIME,                     //278
		en_LAST_CREDENTIAL_REMOVED,                        //279
		en_LAST_CREDENTIAL_REMOVED_TIME,                   //280
		en_LAST_USE_TIME,                                  //281
		en_LOCKOUT,                                        //282
		en_LOCKOUT_RELINQUISH_TIME,                        //283
		en_MASTER_EXEMPTION,                               //284
		en_MAX_FAILED_ATTEMPTS,                            //285
		en_MEMBERS,                                        //286
		en_MUSTER_POINT,                                   //287
		en_NEGATIVE_ACCESS_RULES,                          //288
		en_NUMBER_OF_AUTHENTICATION_POLICIES,              //289
		en_OCCUPANCY_COUNT,                                //290
		en_OCCUPANCY_COUNT_ADJUST,                         //291
		en_OCCUPANCY_COUNT_ENABLE,                         //292
		en_OCCUPANCY_EXEMPTION,                            //293
		en_OCCUPANCY_LOWER_LIMIT,                          //294
		en_OCCUPANCY_LOWER_LIMIT_ENFORCED,                 //295
		en_OCCUPANCY_STATE,                                //296
		en_OCCUPANCY_UPPER_LIMIT,                          //297
		en_OCCUPANCY_UPPER_LIMIT_ENFORCED,                 //298
		en_PASSBACK_EXEMPTION,                             //299
		en_PASSBACK_MODE,                                  //300
		en_PASSBACK_TIMEOUT,                               //301
		en_POSITIVE_ACCESS_RULES,                          //302
		en_REASON_FOR_DISABLE,                             //303
		en_SUPPORTED_FORMATS,                              //304
		en_SUPPORTED_FORMAT_CLASSES,                       //305
		en_THREAT_AUTHORITY,                               //306
		en_THREAT_LEVEL,                                   //307
		en_TRACE_FLAG,                                     //308
		en_TRANSACTION_NOTIFICATION_CLASS,                 //309
		en_USER_EXTERNAL_IDENTIFIER,                       //310
		en_USER_INFORMATION_REFERENCE,                     //311
		en_UNASSIGNED312,                                  //312
		en_UNASSIGNED313,                                  //313
		en_UNASSIGNED314,                                  //314
		en_UNASSIGNED315,                                  //315
		en_UNASSIGNED316,                                  //316
		en_USER_NAME,                                      //317
		en_USER_TYPE,                                      //318
		en_USES_REMAINING,                                 //319
		en_ZONE_FROM,                                      //320
		en_ZONE_TO,                                        //321
		en_ACCESS_EVENT_TAG,                               //322
		en_GLOBAL_IDENTIFIER,                              //323
		en_UNASSIGNED324,                                  //324
		en_UNASSIGNED325,                                  //325
		en_VERIFICATION_TIME,                              //326
		en_UNASSIGNED327,                                  //327
		en_UNASSIGNED328,                                  //328
		en_UNASSIGNED329,                                  //329
		en_UNASSIGNED330,                                  //330
		en_UNASSIGNED331,                                  //331
		en_UNASSIGNED332,                                  //332
		en_UNASSIGNED333,                                  //333
		en_UNASSIGNED334,                                  //334
		en_UNASSIGNED335,                                  //335
		en_UNASSIGNED336,                                  //336
		en_UNASSIGNED337,                                  //337
		en_BACKUP_AND_RESTORE_STATE,                       //338
		en_BACKUP_PREPARATION_TIME,                        //339
		en_RESTORE_COMPLETION_TIME,                        //340
		en_RESTORE_PREPARATION_TIME,                       //341
		en_BIT_MASK,                                       //342
		en_BIT_TEXT,                                       //343
		en_IS_UTC,                                         //344
		en_GROUP_MEMBERS,                                  //345
		en_GROUP_MEMBER_NAMES,                             //346
		en_MEMBER_STATUS_FLAGS,                            //347
		en_REQUESTED_UPDATE_INTERVAL,                      //348
		en_COVU_PERIOD,                                    //349
		en_COVU_RECIPIENTS,                                //350
		en_EVENT_MESSAGE_TEXTS,                            //351
		en_EVENT_MESSAGE_TEXTS_CONFIG,                     //352
		en_EVENT_DETECTION_ENABLE,                         //353
		en_EVENT_ALGORITHM_INHIBIT,                        //354
		en_EVENT_ALGORITHM_INHIBIT_REF,                    //355
		en_TIME_DELAY_NORMAL,                              //356
		en_RELIABILITY_EVALUATION_INHIBIT,                 //357
		en_FAULT_PARAMETERS,                               //358
		en_FAULT_TYPE,                                     //359
		en_LOCAL_FORWARDING_ONLY,                          //360
		en_PROCESS_IDENTIFIER_FILTER,                      //361
		en_SUBSCRIBED_RECIPIENTS,                          //362
		en_PORT_FILTER,                                    //363
		en_AUTHORIZATION_EXEMPTIONS,                       //364
		en_ALLOW_GROUP_DELAY_INHIBIT,                      //365
		en_CHANNEL_NUMBER,                                 //366
		en_CONTROL_GROUPS,                                 //367
		en_EXECUTION_DELAY,                                //368
		en_LAST_PRIORITY,                                  //369
		en_WRITE_STATUS,                                   //370
		en_PROPERTY_LIST,                                  //371
		en_SERIAL_NUMBER,                                  //372
		en_BLINK_WARN_ENABLE,                              //373
		en_DEFAULT_FADE_TIME,                              //374
		en_DEFAULT_RAMP_RATE,                              //375
		en_DEFAULT_STEP_INCREMENT,                         //376
		en_EGRESS_TIME,                                    //377
		en_IN_PROGRESS,                                    //378
		en_INSTANTANEOUS_POWER,                            //379
		en_LIGHTING_COMMAND,                               //380
		en_LIGHTING_COMMAND_DEFAULT_PRIORITY,              //381
		en_MAX_ACTUAL_VALUE,                               //382
		en_MIN_ACTUAL_VALUE,                               //383
		en_POWER,                                          //384
		en_TRANSITION,                                     //385
		en_EGRESS_ACTIVE,                                  //386
		en_INTERFACE_VALUE,                                //387
		en_FAULT_HIGH_LIMIT,                               //388
		en_FAULT_LOW_LIMIT,                                //389
		en_LOW_DIFF_LIMIT,                                 //390
		en_STRIKE_COUNT,                                   //391
		en_TIME_OF_STRIKE_COUNT_RESET,                     //392
		en_DEFAULT_TIMEOUT,                                //393
		en_INITIAL_TIMEOUT,                                //394
		en_LAST_STATE_CHANGE,                              //395
		en_STATE_CHANGE_VALUES,                            //396
		en_TIMER_RUNNING,                                  //397
		en_TIMER_STATE,                                    //398
		en_APDU_LENGTH,                                    //399
		en_IP_ADDRESS,                                     //400
		en_IP_DEFAULT_GATEWAY,                             //401
		en_IP_DHCP_ENABLE,                                 //402
		en_IP_DHCP_LEASE_TIME,                             //403
		en_IP_DHCP_LEASE_TIME_REMAINING,                   //404
		en_IP_DHCP_SERVER,                                 //405
		en_IP_DNS_SERVER,                                  //406
		en_BACNET_IP_GLOBAL_ADDRESS,                       //407
		en_BACNET_IP_MODE,                                 //408
		en_BACNET_IP_MULTICAST_ADDRESS,                    //409
		en_BACNET_IP_NAT_TRAVERSAL,                        //410
		en_IP_SUBNET_MASK,                                 //411
		en_BACNET_IP_UDP_PORT,                             //412
		en_BBMD_ACCEPT_FD_REGISTRATIONS,                   //413
		en_BBMD_BROADCAST_DISTRIBUTION_TABLE,              //414
		en_BBMD_FOREIGN_DEVICE_TABLE,                      //415
		en_CHANGES_PENDING,                                //416
		en_COMMAND,                                        //417
		en_FD_BBMD_ADDRESS,                                //418
		en_FD_SUBSCRIPTION_LIFETIME,                       //419
		en_LINK_SPEED,                                     //420
		en_LINK_SPEEDS,                                    //421
		en_LINK_SPEED_AUTONEGOTIATE,                       //422
		en_MAC_ADDRESS,                                    //423
		en_NETWORK_INTERFACE_NAME,                         //424
		en_NETWORK_NUMBER,                                 //425
		en_NETWORK_NUMBER_QUALITY,                         //426
		en_NETWORK_TYPE,                                   //427
		en_ROUTING_TABLE,                                  //428
		en_VIRTUAL_MAC_ADDRESS_TABLE,                      //429
		en_COMMAND_TIME_ARRAY,                             //430
		en_CURRENT_COMMAND_PRIORITY,                       //431
		en_LAST_COMMAND_TIME,                              //432
		en_VALUE_SOURCE,                                   //433
		en_VALUE_SOURCE_ARRAY,                             //434
		en_BACNET_IPV6_MODE,                               //435
		en_IPV6_ADDRESS,                                   //436
		en_IPV6_PREFIX_LENGTH,                             //437
		en_BACNET_IPV6_UDP_PORT,                           //438
		en_IPV6_DEFAULT_GATEWAY,                           //439
		en_BACNET_IPV6_MULTICAST_ADDRESS,                  //440
		en_IPV6_DNS_SERVER,                                //441
		en_IPV6_AUTO_ADDRESSING_ENABLE,                    //442
		en_IPV6_DHCP_LEASE_TIME,                           //443
		en_IPV6_DHCP_LEASE_TIME_REMAINING,                 //444
		en_IPV6_DHCP_SERVER,                               //445
		en_IPV6_ZONE_INDEX,                                //446
		en_ASSIGNED_LANDING_CALLS,                         //447
		en_CAR_ASSIGNED_DIRECTION,                         //448
		en_CAR_DOOR_COMMAND,                               //449
		en_CAR_DOOR_STATUS,                                //450
		en_CAR_DOOR_TEXT,                                  //451
		en_CAR_DOOR_ZONE,                                  //452
		en_CAR_DRIVE_STATUS,                               //453
		en_CAR_LOAD,                                       //454
		en_CAR_LOAD_UNITS,                                 //455
		en_CAR_MODE,                                       //456
		en_CAR_MOVING_DIRECTION,                           //457
		en_CAR_POSITION,                                   //458
		en_ELEVATOR_GROUP,                                 //459
		en_ENERGY_METER,                                   //460
		en_ENERGY_METER_REF,                               //461
		en_ESCALATOR_MODE,                                 //462
		en_FAULT_SIGNALS,                                  //463
		en_FLOOR_TEXT,                                     //464
		en_GROUP_ID,                                       //465
		en_UNASSIGNED466,                                  //466
		en_GROUP_MODE,                                     //467
		en_HIGHER_DECK,                                    //468
		en_INSTALLATION_ID,                                //469
		en_LANDING_CALLS,                                  //470
		en_LANDING_CALL_CONTROL,                           //471
		en_LANDING_DOOR_STATUS,                            //472
		en_LOWER_DECK,                                     //473
		en_MACHINE_ROOM_ID,                                //474
		en_MAKING_CAR_CALL,                                //475
		en_NEXT_STOPPING_FLOOR,                            //476
		en_OPERATION_DIRECTION,                            //477
		en_PASSENGER_ALARM,                                //478
		en_POWER_MODE,                                     //479
		en_REGISTERED_CAR_CALL,                            //480
		en_ACTIVE_COV_MULTIPLE_SUBSCRIPTIONS,              //481
		en_PROTOCOL_LEVEL,                                 //482
		en_REFERENCE_PORT,                                 //483
		en_DEPLOYED_PROFILE_LOCATION,                      //484
		en_PROFILE_LOCATION,                               //485
		en_TAGS,                                           //486
		en_SUBORDINATE_NODE_TYPES,                         //487
		en_SUBORDINATE_TAGS,                               //488
		en_SUBORDINATE_RELATIONSHIPS,                      //489
		en_DEFAULT_SUBORDINATE_RELATIONSHIP,               //490
		en_REPRESENTS,                                     //491
		en_DEFAULT_PRESENT_VALUE,                          //492
		en_PRESENT_STAGE,                                  //493
		en_STAGES,                                         //494
		en_STAGE_NAMES,                                    //495
		en_TARGET_REFERENCES,                              //496
		en_AUDIT_SOURCE_LEVEL,                             //497
		en_AUDIT_LEVEL,                                    //498
		en_AUDIT_NOTIFICATION_RECIPIENT,                   //499
		en_AUDIT_PRIORITY_FILTER,                          //500
		en_AUDITABLE_OPERATIONS,                           //501
		en_DELETE_ON_FORWARD,                              //502
		en_MAXIMUM_SEND_DELAY,                             //503
		en_MONITORED_OBJECTS,                              //504
		en_SEND_NOW,                                       //505
		en_FLOOR_NUMBER,                                   //506
		en_DEVICE_UUID,                                    //507
		en_ADDITIONAL_REFERENCE_PORTS,                     //508
		en_CERTIFICATE_SIGNING_REQUEST_FILE,               //509
		en_COMMAND_VALIDATION_RESULT,                      //510
		en_ISSUER_CERTIFICATE_FILES,                       //511
		en_MAX_BVLC_LENGTH_ACCEPTED,                       //4194304
		en_MAX_NPDU_LENGTH_ACCEPTED,                       //4194305
		en_OPERATIONAL_CERTIFICATE_FILE,                   //4194306
		en_CURRENT_HEALTH,                                 //4194307
		en_SC_CONNECT_WAIT_TIMEOUT,                        //4194308
		en_SC_DIRECT_CONNECT_ACCEPT_ENABLE,                //4194309
		en_SC_DIRECT_CONNECT_ACCEPT_URIS,                  //4194310
		en_SC_DIRECT_CONNECT_BINDING,                      //4194311
		en_SC_DIRECT_CONNECT_CONNECTION_STATUS,            //4194312
		en_SC_DIRECT_CONNECT_INITIATE_ENABLE,              //4194313
		en_SC_DISCONNECT_WAIT_TIMEOUT,                     //4194314
		en_SC_FAILED_CONNECTION_REQUESTS,                  //4194315
		en_SC_FAILOVER_HUB_CONNECTION_STATUS,              //4194316
		en_SC_FAILOVER_HUB_URI,                            //4194317
		en_SC_HUB_CONNECTOR_STATE,                         //4194318
		en_SC_HUB_FUNCTION_ACCEPT_URIS,                    //4194319
		en_SC_HUB_FUNCTION_BINDING,                        //4194320
		en_SC_HUB_FUNCTION_CONNECTION_STATUS,              //4194321
		en_SC_HUB_FUNCTION_ENABLE,                         //4194322
		en_SC_HEARTBEAT_TIMEOUT,                           //4194323
		en_SC_PRIMARY_HUB_CONNECTION_STATUS,               //4194324
		en_SC_PRIMARY_HUB_URI,                             //4194325
		en_SC_MAXIMUM_RECONNECT_TIME,                      //4194326
		en_SC_MINIMUM_RECONNECT_TIME,                      //4194327
		en_COLOR_OVERRIDE,                                 //4194328
		en_COLOR_REFERENCE,                                //4194329
		en_DEFAULT_COLOR,                                  //4194330
		en_DEFAULT_COLOR_TEMPERATURE,                      //4194331
		en_OVERRIDE_COLOR_REFERENCE,                       //4194332
		en_WRITE_EVERY_SCHEDULED_ACTION,                   //4194333
		en_COLOR_COMMAND,                                  //4194334
		en_HIGH_END_TRIM,                                  //4194335
		en_LOW_END_TRIM,                                   //4194336
		en_TRIM_FADE_TIME,                                 //4194337
		en_DEVICE_ADDRESS_PROXY_ENABLE,                    //4194338
		en_DEVICE_ADDRESS_PROXY_TABLE,                     //4194339
		en_DEVICE_ADDRESS_PROXY_TIMEOUT,                   //4194340
		en_DEFAULT_ON_VALUE,                               //4194341
		en_LAST_ON_VALUE,                                  //4194342
		en_AUTHORIZATION_CACHE,                            //4194343
		en_AUTHORIZATION_GROUPS,                           //4194344
		en_AUTHORIZATION_POLICY,                           //4194345
		en_AUTHORIZATION_SCOPE,                            //4194346
		en_AUTHORIZATION_SERVER,                           //4194347
		en_AUTHORIZATION_STATUS,                           //4194348
		en_MAX_PROXIED_I_AMS_PER_SECOND,                   //4194349
		en_ERROR_PROP										// XXX MAG not a real prop
	};  // end BACnet property list


	// NOTE list copied from BACdll, list and numbering are NOT part of the BACnet standard
	// NOTE salted with "en_" due to number of naming conflicts with #define statements
	// Based on BACnetPropertyIdentifier enumerated list in 135-2012
	enum class BACPropType {
		en_There_Is_No_Zero,
		en_Any				, // 1
		en_BACnetAccessCredentialDisable				, // 2
		en_BACnetAccessEvent				, // 3
		en_BACnetAccessPassbackMode				, // 4
		en_BACnetAccessThreatLevel				, // 5
		en_BACnetAccessUserType				, // 6
		en_BACnetAccessZoneOccupancyState				, // 7
		en_BACnetAccumulatorRecord				, // 8
		en_BACnetAction				, // 9
		en_BACnetAddressBinding,				 // 10
		en_BACnetARRAY_F3_of_BACnetTimeStamp,				 // 11
		en_BACnetSecurityKeySet,				 // 12
		en_BACnetARRAY_3_of_BACnetTimeStamp,				 // 13
		en_BACnetARRAY_3_of_CharacterString,				 // 14
		en_BACnetARRAY_3_of_Unsigned,				 // 15
		en_BACnetARRAY_7_of_BACnetDailySchedule,				 // 16
		en_BACnetARRAY_N_of_BACnetAccessRule,				 // 17
		en_BACnetARRAY_N_of_BACnetActionList,				 // 18
		en_BACnetARRAY_N_of_BACnetAssignedAccessRights,				 // 19
		en_BACnetARRAY_N_of_BACnetAuthenticationFactorFormat,				 // 20
		en_BACnetARRAY_N_of_BACnetAuthenticationPolicy,				 // 21
		en_BACnetARRAY_N_of_BACnetCredentialAuthenticationFactor,				 // 22
		en_BACnetARRAY_N_of_BACnetDeviceObjectPropertyReference,				 // 23
		en_BACnetARRAY_N_of_BACnetDeviceObjectReference,				 // 24
		en_BACnetNetworkSecurityPolicy,				 // 25
		en_BACnetARRAY_N_of_BACnetObjectIdentifier,				 // 26
		en_BACnetARRAY_N_of_BACnetOptionalCharacterString,				 // 27
		en_BACnetARRAY_N_of_BACnetPropertyAccessResult,				 // 28
		en_BACnetARRAY_N_of_BIT_STRING,				 // 29
		en_BACnetARRAY_N_of_BOOLEAN,				 // 30
		en_BACnetARRAY_N_of_CharacterString,				 // 31
		en_BACnetARRAY_N_of_Unsigned,				 // 32
		en_BACnetARRAY_N_of,				 // 33
		en_BACnetARRAY_N_of_BACnetSpecialEvent,				 // 34
		en_BACnetAuthenticationFactor,				 // 35
		en_BACnetAuthenticationStatus,				 // 36
		en_BACnetAuthorizationMode,				 // 37
		en_BACnetBackupState,				 // 38
		en_BACnetBinaryPV,				 // 39
		en_BACnetClientCOV,				 // 40
		en_BACnetDateRange,				 // 41
		en_BACnetDateTime,				 // 42
		en_BACnetDeviceObjectPropertyReference,				 // 43
		en_BACnetDeviceObjectReference,				 // 44
		en_BACnetDeviceStatus,				 // 45
		en_BACnetDoorAlarmState,				 // 46
		en_BACnetDoorSecuredStatus,				 // 47
		en_BACnetDoorStatus,				 // 48
		en_BACnetDoorValue,				 // 49
		en_BACnetEngineeringUnits,				 // 50
		en_BACnetEventParameter,				 // 51
		en_BACnetEventState,				 // 52
		en_BACnetEventTransitionBits,				 // 53
		en_BACnetEventType,				 // 54
		en_BACnetFileAccessMethod,				 // 55
		en_BACnetLifeSafetyMode,				 // 56
		en_BACnetLifeSafetyOperation,				 // 57
		en_BACnetLifeSafetyState,				 // 58
		en_BACnetLimitEnable,				 // 59
		en_BACnetLockStatus,				 // 60
		en_BACnetLoggingType,				 // 61
		en_BACnetMaintenance,				 // 62
		en_BACnetNodeType,				 // 63
		en_BACnetNotifyType,				 // 64
		en_BACnetObjectIdentifier,				 // 65
		en_BACnetObjectPropertyReference,				 // 66
		en_BACnetObjectType,				 // 67
		en_BACnetObjectTypesSupported,				 // 68
		en_BACnetPolarity,				 // 69
		en_BACnetPrescale,				 // 70
		en_BACnetPriorityArray,				 // 71
		en_BACnetProgramError,				 // 72
		en_BACnetProgramRequest,				 // 73
		en_BACnetProgramState,				 // 74
		en_BACnetReliability,				 // 75
		en_BACnetRestartReason,				 // 76
		en_BACnetScale,				 // 77
		en_BACnetSecurityLevel,				 // 78
		en_BACnetSegmentation,				 // 79
		en_BACnetServicesSupported,				 // 80
		en_BACnetSetpointReference,				 // 81
		en_BACnetShedLevel,				 // 82
		en_BACnetShedState,				 // 83
		en_BACnetSilencedState,				 // 84
		en_BACnetStatusFlags,				 // 85
		en_BACnetTimeStamp,				 // 86
		en_BIT_STRING,				 // 87
		en_BOOLEAN,				 // 88
		en_CharacterString,				 // 89
		en_Date,				 // 90
		en_Double,				 // 91
		en_INTEGER,				 // 92
		en_List_of_BACnetAccessCredentialDisableReason,				 // 93
		en_List_of_BACnetAccessEvent,				 // 94
		en_List_of_BACnetAccessZoneOccupancyState,				 // 95
		en_List_of_BACnetAddressBinding,				 // 96
		en_List_of_BACnetCalendarEntry,				 // 97
		en_List_of_BACnetCOVSubscription,				 // 98
		en_List_of_BACnetDestination,				 // 99
		en_List_of_BACnetDeviceObjectPropertyReference,					// 100
		en_List_of_BACnetDeviceObjectReference,					// 101
		en_List_of_BACnetDoorAlarmState,				// 102
		en_List_of_BACnetEventLogRecord,				// 103
		en_List_of_BACnetLifeSafetyMode,				// 104
		en_List_of_BACnetLifeSafetyState,				// 105
		en_List_of_BACnetLogMultipleRecord,					// 106
		en_List_of_BACnetLogRecord,					// 107
		en_List_of_BACnetRecipient,					// 108
		en_List_of_BACnetVTClass,				// 109
		en_List_of_BACnetVTSession,					// 110
		en_List_of_ReadAccessResult,				// 111
		en_List_of_ReadAccessSpecification,					// 112
		en_List_of_Unsigned,				// 113
		en_List_of_Unsigned8,				// 114
		en_OCTET_STRING,				// 115
		en_REAL,				// 116
		en_Time,				// 117
		en_Unsigned_1to16,				// 118
		en_Unsigned_1to127,					// 119
		en_Unsigned_1to16b,					// 120
		en_Unsigned,				// 121
		en_Unsigned16,				// 122
		en_Unsigned32,				// 123
		en_Unsigned8,				// 124
		en_List_of_BACnetAuthorizationExemption,				// 125
		en_BACnetFaultType,					// 126
		en_BACnetFaultParameter,				// 127
		en_BACnetEventStatus,				// 128
		en_BACnetEventNotificationSubscription,					// 129
		en_BACnetProcessIdSelection,				// 130
		en_BACnetPortPermission,				// 131
		en_BACnetLightingCommand,				// 132
		en_BACnetLightingInProgress,				// 133
		en_BACnetLightingTransition,				// 134
		en_BACnetChannelValue,				// 135
		en_BACnetWriteStatus,				// 136
		ERROR_TYPE_NOT_SUPPORTED, // 137? use for indicating type not supported error
		ERROR_NOT_ENUM       // 138? use for indicating other error
	};  // end BACnet property TYPE

}