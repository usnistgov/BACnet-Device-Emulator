// MAG 260402
// This file is to hold label arrays used by other classes (property, object, devices, etc..)
#include <vector>
#include <string>
namespace BAClabels {
	static std::vector<std::string> ObjectLabels = {
		"Analog Input", //0
		"Analog Output", //1
		"Analog Value", //2
		"Binary Input", //3
		"Binary Output", //4
		"Binary Value", //5
		"Calendar", //6
		"Command", //7
		"Device", //8
		"Event Enrollment", //9
		"File", //10
		"Group", //11
		"Loop", //12
		"Multi State Input", //13
		"Multi State Output", //14
		"Notification Class", //15
		"Program", //16
		"Schedule", //17
		"Averaging", //18
		"Multi State Value", //19
		"Trend Log", //20
		"Life Safety Point", //21
		"Life Safety Zone", //22
		"Accumulator", //23
		"Pulse Converter", //24
		"Event Log", //25
		"Global Group", //26
		"Trend Log Multiple", //27
		"Load Control", //28
		"Structured View", //29
		"Access Door", //30
		"Unassigned (Reserved).", //31
		"Access Credential", //32
		"Access Point", //33
		"Access Rights", //34
		"Access User", //35
		"Access Zone", //36
		"Credential Data Input", //37
		"Network Security (Deprecated/Removed).", //38
		"Bitstring Value", //39
		"Characterstring Value", //40
		"Date Pattern Value", //41
		"Date Value", //42
		"Datetime Pattern Value", //43
		"Datetime Value", //44
		"Integer Value", //45
		"Large Analog Value", //46
		"Octetstring Value", //47
		"Positive Integer Value", //48
		"Time Pattern Value", //49
		"Time Value", //50
		"Notification Forwarder", //51
		"Alert Enrollment", //52
		"Channel", //53
		"Lighting Output", //54
		"Binary Lighting Output", //55
		"Network Port", //56
		"Elevator Group", //57
		"Escalator", //58
		"Lift", //59
		"Staging", //60
		"Audit Log", //61
		"Audit Reporter", //62
		"Timer", //63
		"ERROR_OBJECT"				// 64 MAG not a real object
	};  // end ObjectLabels

	static std::vector<std::string> PropertyLabels = {
		"acked_transitions",						//0
		"ack_required",								//1
		"action",									//2
		"action_text",								//3
		"active_text",								//4
		"active_vt_sessions",						//5
		"alarm_value",								//6
		"alarm_values",								//7
		"all",										//8
		"all_writes_successful",					//9
		"apdu_segment_timeout",						//10
		"apdu_timeout",								//11
		"application_software_version",				//12
		"archive",									//13
		"bias",										//14
		"change_of_state_count",					//15
		"change_of_state_time",						//16
		"notification_class",						//17
		"not_used_18",								//18
		"controlled_variable_reference",			//19
		"controlled_variable_units",				//20
		"controlled_variable_value",				//21
		"cov_increment",							//22
		"date_list",								//23
		"daylight_savings_status",					//24
		"deadband",									//25
		"derivative_constant",						//26
		"derivative_constant_units",				//27
		"description",								//28
		"description_of_halt",						//29
		"device_address_binding",					//30
		"device_type",								//31
		"effective_period",							//32
		"elapsed_active_time",						//33
		"error_limit",								//34
		"event_enable",								//35
		"event_state",								//36
		"event_type",								//37
		"exception_schedule",						//38
		"fault_values",								//39
		"feedback_value",							//40
		"file_access_method",						//41
		"file_size",								//42
		"file_type",								//43
		"firmware_revision",						//44
		"high_limit",								//45
		"inactive_text",							//46
		"in_process",								//47
		"instance_of",								//48
		"integral_constant",						//49
		"integral_constant_units",					//50
		"issue_confirmed_notifications",			//51
		"limit_enable",								//52
		"group_members",							//53
		"list_of_object_property_references",		//54
		"list_of_session_keys",						//55
		"local_date",								//56
		"local_time",								//57
		"location",									//58
		"low_limit",								//59
		"manipulated_variable_reference",			//60
		"maximum_output",							//61
		"max_apdu_length_accepted",					//62
		"max_info_frames",							//63
		"max_master",								//64
		"max_pres_value",							//65
		"minimum_off_time",							//66
		"minimum_on_time",							//67
		"minimum_output",							//68
		"min_pres_value",							//69
		"model_name",								//70
		"modification_date",						//71
		"notify_type",								//72
		"number_of_apdu_retries",					//73
		"number_of_states",							//74
		"object_identifier",						//75
		"object_list",								//76
		"object_name",								//77
		"object_property_reference",				//78
		"object_type",								//79
		"isoptional",								//80
		"out_of_service",							//81
		"output_units",								//82
		"event_parameters",							//83
		"polarity",									//84
		"present_value",							//85
		"priority",									//86
		"priority_array",							//87
		"priority_for_writing",						//88
		"process_identifier",						//89
		"program_change",							//90
		"program_location",							//91
		"program_state",							//92
		"proportional_constant",					//93
		"proportional_constant_units",				//94
		"protocol_conformance_class",				//95
		"protocol_object_types_supported",			//96
		"protocol_services_supported",				//97
		"protocol_version",							//98
		"read_only",								//99
		"reason_for_halt",							//100
		"recipient",								//101
		"recipient_list",							//102
		"reliability",								//103
		"relinquish_default",						//104
		"required",									//105
		"resolution",								//106
		"segmentation_supported",					//107
		"setpoint",									//108
		"setpoint_reference",						//109
		"state_text",								//110
		"status_flags",								//111
		"system_status",							//112
		"time_delay",								//113
		"time_of_active_time_reset",				//114
		"time_of_state_count_reset",				//115
		"time_synchronization_recipients",			//116
		"units",									//117
		"update_interval",							//118
		"utc_offset",								//119
		"vendor_identifier",						//120
		"vendor_name",								//121
		"vt_classes_supported",						//122
		"weekly_schedule",							//123
		"attempted_samples",						//124
		"average_value",							//125
		"buffer_size",								//126
		"client_cov_increment",						//127
		"cov_resubscription_interval",				//128
		"not_used_129",								//129
		"event_time_stamps",						//130
		"log_buffer",								//131
		"log_device_object_property",				//132
		"enable",									//133
		"log_interval",								//134
		"maximum_value",							//135
		"minimum_value",							//136
		"notification_threshold",					//137
		"not_used_138",								//138
		"protocol_revision",						//139
		"records_since_notification",				//140
		"record_count",								//141
		"start_time",								//142
		"stop_time",								//143
		"stop_when_full",							//144
		"total_record_count",						//145
		"valid_samples",							//146
		"window_interval",							//147
		"window_samples",							//148
		"maximum_value_timestamp",					//149
		"minimum_value_timestamp",					//150
		"variance_value",							//151
		"active_cov_subscriptions",					//152
		"backup_failure_timeout",					//153
		"configuration_files",						//154
		"database_revision",						//155
		"direct_reading",							//156
		"last_restore_time",						//157
		"maintenance_required",						//158
		"member_of",								//159
		"mode",										//160
		"operation_expected",						//161
		"setting",									//162
		"silenced",									//163
		"tracking_value",							//164
		"zone_members",								//165
		"life_safety_alarm_values",					//166
		"max_segments_accepted",					//167
		"profile_name",								//168
		"auto_slave_discovery",						//169
		"manual_slave_address_binding",				//170
		"slave_address_binding",					//171
		"slave_proxy_enable",						//172
		"last_notify_record",						//173
		"schedule_default",							//174
		"accepted_modes",							//175
		"adjust_value",								//176
		"count",									//177
		"count_before_change",						//178
		"count_change_time",						//179
		"cov_period",								//180
		"input_reference",							//181
		"limit_monitoring_interval",				//182
		"logging_object",							//183
		"logging_record",							//184
		"prescale",									//185
		"pulse_rate",								//186
		"scale",									//187
		"scale_factor",								//188
		"update_time",								//189
		"value_before_change",						//190
		"value_set",								//191
		"value_change_time",						//192
		"align_intervals",							//193
		"group_member_names",						//194
		"interval_offset",							//195
		"last_restart_reason",						//196
		"logging_type",								//197
		"member_status_flags",						//198
		"notification_period",						//199
		"previous_notify_record",					//200
		"requested_update_interval",				//201
		"restart_notification_recipients",			//202
		"time_of_device_restart",					//203
		"time_synchronization_interval",			//204
		"trigger",									//205
		"utc_time_synchronization_recipients",		//206
		"node_subtype",								//207
		"node_type",								//208
		"structured_object_list",					//209
		"subordinate_annotations",					//210
		"subordinate_list",							//211
		"actual_shed_level",						//212
		"duty_window",								//213
		"expected_shed_level",						//214
		"full_duty_baseline",						//215
		"blink_priority_threshold",					//216
		"blink_time",								//217
		"requested_shed_level",						//218
		"shed_duration",							//219
		"shed_level_descriptions",					//220
		"shed_levels",								//221
		"state_description",						//222
		"fade_time",								//223
		"lighting_command",							//224
		"lighting_command_priority",				//225
		"door_alarm_state",							//226
		"door_extended_pulse_time",					//227
		"door_members",								//228
		"door_open_too_long_time",					//229
		"door_pulse_time",							//230
		"door_status",								//231
		"door_unlock_delay_time",					//232
		"lock_status",								//233
		"masked_alarm_values",						//234
		"secured_status",							//235
		"off_delay",								//236
		"on_delay",									//237
		"power",									//238
		"power_on_value",							//239
		"progress_value",							//240
		"ramp_rate",								//241
		"step_increment",							//242
		"system_failure_value",						//243
		"absentee_limit",							//244
		"access_alarm_events",						//245
		"access_doors",								//246
		"access_event",								//247
		"access_event_authentication_factor",		//248
		"access_event_credential",					//249
		"access_event_time",						//250
		"access-event-time",						// 250
		"access-transaction-events",				// 251
		"accompaniment",							// 252
		"accompaniment-time",						// 253
		"activation-time",							// 254
		"active-authentication-policy",				// 255
		"assigned-access-rights",					// 256
		"authentication-factors",					// 257
		"authentication-policy-list",				// 258
		"authentication-policy-names",				// 259
		"authentication-status",					// 260
		"authorization-mode",						// 261
		"belongs-to",								// 262
		"credential-disable",						// 263
		"credential-status",						// 264
		"credentials",								// 265
		"credentials-in-zone",						// 266
		"days-remaining",							// 267
		"entry-points",								// 268
		"exit-points",								// 269
		"expiry-time",								// 270
		"extended-time-enable",						// 271
		"failed-attempt-events",					// 272
		"failed-attempts",							// 273
		"failed-attempts-time",						// 274
		"last-access-event",						// 275
		"last-access-point",						// 276
		"last-credential-added",					// 277
		"last-credential-added-time",				// 278
		"last-credential-removed",					// 279
		"last-credential-removed-time",				// 280
		"last-use-time",							// 281
		"lockout",									// 282
		"lockout-relinquish-time",					// 283
		"master-exemption",							// 284
		"max-failed-attempts",						// 285
		"members",									// 286
		"muster-point",								// 287
		"negative-access-rules",					// 288
		"number-of-authentication-policies",		// 289
		"occupancy-count",							// 290
		"occupancy-count-adjust",					// 291
		"occupancy-count-enable",					// 292
		"occupancy-exemption",						// 293
		"occupancy-lower-limit",					// 294
		"occupancy-lower-limit-enforced",			// 295
		"occupancy-state",							// 296
		"occupancy-upper-limit",					// 297
		"occupancy-upper-limit-enforced",			// 298
		"passback-exemption",						// 299
		"passback-mode",							// 300
		"passback-timeout",							// 301
		"positive-access-rules",					// 302
		"reason-for-disable",						// 303
		"supported-formats",						// 304
		"supported-format-classes",					// 305
		"threat-authority",							// 306
		"threat-level",								// 307
		"trace-flag",								// 308
		"transaction-notification-class",			// 309
		"user-external-identifier",					// 310
		"user-information-reference",				// 311
		"unassigned312",							// 312
		"unassigned313",							// 313
		"unassigned314",							// 314
		"unassigned315",							// 315
		"unassigned316",							// 316
		"user-name",								// 317
		"user-type",								// 318
		"uses-remaining",							// 319
		"zone-from",								// 320
		"zone-to",									// 321
		"access-event-tag",							// 322
		"global-identifier",						// 323
		"unassigned324",							// 324
		"unassigned325",							// 325
		"verification-time",						// 326
		"base-device-security-policy",				// 327
		"distribution-key-revision",				// 328
		"do-not-hide",								// 329
		"key-sets",									// 330
		"last-key-server",							// 331
		"network-access-security-policies",			// 332
		"packet-reorder-time",						// 333
		"security-pdu-timeout",						// 334
		"security-time-window",						// 335
		"supported-security-algorithms",			// 336
		"update-key-set-timeout",					// 337
		"backup-and-restore-state",					// 338
		"backup-preparation-time",					// 339
		"restore-completion-time",					// 340
		"restore-preparation-time",					// 341
		"bit-mask",									// 342
		"bit-text",									// 343
		"is-utc",									// 344
		"group-members",							// 345
		"group-member-names",						// 346
		"member-status-flags",						// 347
		"requested-update-interval",				// 348
		"covu-period",								// 349
		"covu-recipients",							// 350
		"event-message-texts",						// 351
		"event-message-texts-config",				// 352
		"event-detection-enable",					// 353
		"event-algorithm-inhibit",					// 354
		"event-algorithm-inhibit-ref",				// 355
		"time-delay-normal",						// 356
		"reliability-evaluation-inhibit",			// 357
		"fault-parameters",							// 358
		"fault-type",								// 359
		"local-forwarding-only",					// 360
		"process-identifier-filter",				// 361
		"subscribed-recipients",					// 362
		"port-filter",								// 363
		"authorization-exemptions",					// 364
		"allow-group-delay-inhibit",				// 365
		"channel-number",							// 366
		"control-groups",							// 367
		"execution-delay",							// 368
		"last-priority",							// 369
		"write-status",								// 370
		"property-list",							// 371
		"serial-number",							// 372
		"blink-warn-enable",						// 373
		"default-fade-time",						// 374
		"default-ramp-rate",						// 375
		"default-step-increment",					// 376
		"egress-time",								// 377
		"in-progress",								// 378
		"instantaneous-power",						// 379
		"lighting-command",							// 380
		"lighting-command-default-priority",		// 381
		"max-actual-value",							// 382
		"min-actual-value",							// 383
		"power",									// 384
		"transition",								// 385
		"egress-active",							// 386
	};
} // end namespace