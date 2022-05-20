#ifndef AUTOMATION1STATUSITEM_H_INCLUDED
#define AUTOMATION1STATUSITEM_H_INCLUDED

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Represents an axis based status item that can be retrieved from the Automation1 controller.
typedef enum Automation1AxisStatusItem
{
	/// @brief The "Position Feedback" axis based status item.
	Automation1AxisStatusItem_PositionFeedback = 0,
	/// @brief The "Position Command" axis based status item.
	Automation1AxisStatusItem_PositionCommand = 1,
	/// @brief The "Position Error" axis based status item.
	Automation1AxisStatusItem_PositionError = 2,
	/// @brief The "Velocity Feedback" axis based status item.
	Automation1AxisStatusItem_VelocityFeedback = 3,
	/// @brief The "Velocity Command" axis based status item.
	Automation1AxisStatusItem_VelocityCommand = 4,
	/// @brief The "Velocity Error" axis based status item.
	Automation1AxisStatusItem_VelocityError = 5,
	/// @brief The "Acceleration Command" axis based status item.
	Automation1AxisStatusItem_AccelerationCommand = 6,
	/// @brief The "Current Feedback" axis based status item.
	Automation1AxisStatusItem_CurrentFeedback = 7,
	/// @brief The "Current Command" axis based status item.
	Automation1AxisStatusItem_CurrentCommand = 8,
	/// @brief The "Current Error" axis based status item.
	Automation1AxisStatusItem_CurrentError = 9,
	/// @brief The "Analog Input 0" axis based status item.
	Automation1AxisStatusItem_AnalogInput0 = 10,
	/// @brief The "Analog Input 1" axis based status item.
	Automation1AxisStatusItem_AnalogInput1 = 11,
	/// @brief The "Position Command Raw" axis based status item.
	Automation1AxisStatusItem_PositionCommandRaw = 12,
	/// @brief The "Velocity Command Raw" axis based status item.
	Automation1AxisStatusItem_VelocityCommandRaw = 13,
	/// @brief The "Auxiliary Feedback" axis based status item.
	Automation1AxisStatusItem_AuxiliaryFeedback = 14,
	/// @brief The "Digital Input" axis based status item.
	Automation1AxisStatusItem_DigitalInput = 15,
	/// @brief The "Digital Output" axis based status item.
	Automation1AxisStatusItem_DigitalOutput = 16,
	/// @brief The "Fixture Offset" axis based status item.
	Automation1AxisStatusItem_FixtureOffset = 18,
	/// @brief The "Analog Input 2" axis based status item.
	Automation1AxisStatusItem_AnalogInput2 = 23,
	/// @brief The "Analog Input 3" axis based status item.
	Automation1AxisStatusItem_AnalogInput3 = 24,
	/// @brief The "Analog Output 0" axis based status item.
	Automation1AxisStatusItem_AnalogOutput0 = 31,
	/// @brief The "Analog Output 1" axis based status item.
	Automation1AxisStatusItem_AnalogOutput1 = 32,
	/// @brief The "Analog Output 2" axis based status item.
	Automation1AxisStatusItem_AnalogOutput2 = 33,
	/// @brief The "Analog Output 3" axis based status item.
	Automation1AxisStatusItem_AnalogOutput3 = 34,
	/// @brief The "Coordinated Position Target" axis based status item.
	Automation1AxisStatusItem_CoordinatedPositionTarget = 41,
	/// @brief The "Drive Status" axis based status item.
	Automation1AxisStatusItem_DriveStatus = 42,
	/// @brief The "Axis Status" axis based status item.
	Automation1AxisStatusItem_AxisStatus = 43,
	/// @brief The "Axis Fault" axis based status item.
	Automation1AxisStatusItem_AxisFault = 44,
	/// @brief The "Acceleration Command Raw" axis based status item.
	Automation1AxisStatusItem_AccelerationCommandRaw = 45,
	/// @brief The "Position Calibration All" axis based status item.
	Automation1AxisStatusItem_PositionCalibrationAll = 50,
	/// @brief The "Position Feedback Rollover" axis based status item.
	Automation1AxisStatusItem_PositionFeedbackRollover = 63,
	/// @brief The "Position Command Rollover" axis based status item.
	Automation1AxisStatusItem_PositionCommandRollover = 64,
	/// @brief The "Velocity Feedback Average" axis based status item.
	Automation1AxisStatusItem_VelocityFeedbackAverage = 65,
	/// @brief The "Current Feedback Average" axis based status item.
	Automation1AxisStatusItem_CurrentFeedbackAverage = 66,
	/// @brief The "Axis Parameter" axis based status item.
	Automation1AxisStatusItem_AxisParameter = 68,
	/// @brief The "Backlash" axis based status item.
	Automation1AxisStatusItem_Backlash = 72,
	/// @brief The "Home State" axis based status item.
	Automation1AxisStatusItem_HomeState = 73,
	/// @brief The "Position Calibration 2D" axis based status item.
	Automation1AxisStatusItem_PositionCalibration2D = 74,
	/// @brief The "Normalcy Debug" axis based status item.
	Automation1AxisStatusItem_NormalcyDebug = 75,
	/// @brief The "Total Move Time" axis based status item.
	Automation1AxisStatusItem_TotalMoveTime = 76,
	/// @brief The "Position Feedback Drive" axis based status item.
	Automation1AxisStatusItem_PositionFeedbackDrive = 77,
	/// @brief The "Jerk Command Raw" axis based status item.
	Automation1AxisStatusItem_JerkCommandRaw = 78,
	/// @brief The "Program Position Command" axis based status item.
	Automation1AxisStatusItem_ProgramPositionCommand = 79,
	/// @brief The "Position Offset" axis based status item.
	Automation1AxisStatusItem_PositionOffset = 80,
	/// @brief The "Position Command Raw Backwards Diff" axis based status item.
	Automation1AxisStatusItem_PositionCommandRawBackwardsDiff = 82,
	/// @brief The "Velocity Command Raw Backwards Diff Delta" axis based status item.
	Automation1AxisStatusItem_VelocityCommandRawBackwardsDiffDelta = 83,
	/// @brief The "Position Command Drive" axis based status item.
	Automation1AxisStatusItem_PositionCommandDrive = 84,
	/// @brief The "Drive Status Actual" axis based status item.
	Automation1AxisStatusItem_DriveStatusActual = 85,
	/// @brief The "Program Position Feedback" axis based status item.
	Automation1AxisStatusItem_ProgramPositionFeedback = 89,
	/// @brief The "Jog Trajectory Status" axis based status item.
	Automation1AxisStatusItem_JogTrajectoryStatus = 94,
	/// @brief The "Ping Test" axis based status item.
	Automation1AxisStatusItem_PingTest = 95,
	/// @brief The "Acceleration Time" axis based status item.
	Automation1AxisStatusItem_AccelerationTime = 109,
	/// @brief The "Deceleration Time" axis based status item.
	Automation1AxisStatusItem_DecelerationTime = 110,
	/// @brief The "Acceleration Rate" axis based status item.
	Automation1AxisStatusItem_AccelerationRate = 111,
	/// @brief The "Deceleration Rate" axis based status item.
	Automation1AxisStatusItem_DecelerationRate = 112,
	/// @brief The "Acceleration Type" axis based status item.
	Automation1AxisStatusItem_AccelerationType = 113,
	/// @brief The "Deceleration Type" axis based status item.
	Automation1AxisStatusItem_DecelerationType = 114,
	/// @brief The "Acceleration Mode" axis based status item.
	Automation1AxisStatusItem_AccelerationMode = 115,
	/// @brief The "Deceleration Mode" axis based status item.
	Automation1AxisStatusItem_DecelerationMode = 116,
	/// @brief The "Program Position" axis based status item.
	Automation1AxisStatusItem_ProgramPosition = 124,
	/// @brief The "Speed Target" axis based status item.
	Automation1AxisStatusItem_SpeedTarget = 128,
	/// @brief The "Position Command Packet" axis based status item.
	Automation1AxisStatusItem_PositionCommandPacket = 131,
	/// @brief The "Drive Smc Motion State" axis based status item.
	Automation1AxisStatusItem_DriveSmcMotionState = 132,
	/// @brief The "Position Command Raw Cal" axis based status item.
	Automation1AxisStatusItem_PositionCommandRawCal = 140,
	/// @brief The "Velocity Command Raw Cal" axis based status item.
	Automation1AxisStatusItem_VelocityCommandRawCal = 141,
	/// @brief The "Velocity Command Drive" axis based status item.
	Automation1AxisStatusItem_VelocityCommandDrive = 142,
	/// @brief The "Acceleration Command Drive" axis based status item.
	Automation1AxisStatusItem_AccelerationCommandDrive = 143,
	/// @brief The "Galvo Laser Output Raw" axis based status item.
	Automation1AxisStatusItem_GalvoLaserOutputRaw = 144,
	/// @brief The "Drive Interface Packet Int32" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketInt32 = 147,
	/// @brief The "Drive Interface Packet Int16" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketInt16 = 148,
	/// @brief The "Drive Interface Packet Int8" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketInt8 = 149,
	/// @brief The "Drive Interface Packet Double" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketDouble = 150,
	/// @brief The "Drive Interface Packet Float" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketFloat = 151,
	/// @brief The "Drive Interface Command Code" axis based status item.
	Automation1AxisStatusItem_DriveInterfaceCommandCode = 152,
	/// @brief The "Acceleration Feedback" axis based status item.
	Automation1AxisStatusItem_AccelerationFeedback = 153,
	/// @brief The "Acceleration Command Raw Cal" axis based status item.
	Automation1AxisStatusItem_AccelerationCommandRawCal = 154,
	/// @brief The "Position Calibration All Drive" axis based status item.
	Automation1AxisStatusItem_PositionCalibrationAllDrive = 155,
	/// @brief The "Backlash Target" axis based status item.
	Automation1AxisStatusItem_BacklashTarget = 156,
	/// @brief The "Drive Motion Rate" axis based status item.
	Automation1AxisStatusItem_DriveMotionRate = 158,
	/// @brief The "Drive Motion Delay" axis based status item.
	Automation1AxisStatusItem_DriveMotionDelay = 159,
	/// @brief The "Calibration Adjustment Value" axis based status item.
	Automation1AxisStatusItem_CalibrationAdjustmentValue = 160,
	/// @brief The "Servo Rounding" axis based status item.
	Automation1AxisStatusItem_ServoRounding = 161,
	/// @brief The "Feedforward Current" axis based status item.
	Automation1AxisStatusItem_FeedforwardCurrent = 162,
	/// @brief The "Drive Interface Packet Info Bit Value" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketInfoBitValue = 164,
	/// @brief The "Acceleration Error" axis based status item.
	Automation1AxisStatusItem_AccelerationError = 165,
	/// @brief The "Suppressed Faults" axis based status item.
	Automation1AxisStatusItem_SuppressedFaults = 167,
	/// @brief The "Drive Interface Packet Streaming Data" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketStreamingData = 168,
	/// @brief The "Position Command Raw Unfiltered" axis based status item.
	Automation1AxisStatusItem_PositionCommandRawUnfiltered = 169,
	/// @brief The "Transition Offset Errors" axis based status item.
	Automation1AxisStatusItem_TransitionOffsetErrors = 170,
	/// @brief The "Freeze Velocity Command" axis based status item.
	Automation1AxisStatusItem_FreezeVelocityCommand = 179,
	/// @brief The "Freeze Velocity Feedback" axis based status item.
	Automation1AxisStatusItem_FreezeVelocityFeedback = 180,
	/// @brief The "Internal Position Offsets" axis based status item.
	Automation1AxisStatusItem_InternalPositionOffsets = 181,
	/// @brief The "StatusHighLevelOffsetsLastMsec" axis based status item.
	Automation1AxisStatusItem_StatusHighLevelOffsetsLastMsec = 182,
	/// @brief The "Program Velocity Command" axis based status item.
	Automation1AxisStatusItem_ProgramVelocityCommand = 183,
	/// @brief The "Program Velocity Feedback" axis based status item.
	Automation1AxisStatusItem_ProgramVelocityFeedback = 184,
	/// @brief The "Drive Motion Delay Live" axis based status item.
	Automation1AxisStatusItem_DriveMotionDelayLive = 185,
	/// @brief The "Drive Communication Delay" axis based status item.
	Automation1AxisStatusItem_DriveCommunicationDelay = 186,
	/// @brief The "Drive Communication Delay Live" axis based status item.
	Automation1AxisStatusItem_DriveCommunicationDelayLive = 187,
	/// @brief The "Drive Interface Packet Response Int32" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketResponseInt32 = 189,
	/// @brief The "Drive Interface Packet Response Int16" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketResponseInt16 = 190,
	/// @brief The "Drive Interface Packet Response Int8" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketResponseInt8 = 191,
	/// @brief The "Drive Interface Packet Response Double" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketResponseDouble = 192,
	/// @brief The "Drive Interface Packet Response Float" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketResponseFloat = 193,
	/// @brief The "Drive Interface Packet Bit" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketBit = 194,
	/// @brief The "Drive Interface Packet Response Bit" axis based status item.
	Automation1AxisStatusItem_DriveInterfacePacketResponseBit = 195,
	/// @brief The "Speed Target Actual" axis based status item.
	Automation1AxisStatusItem_SpeedTargetActual = 196,
	/// @brief The "Coordinated Distance Remaining" axis based status item.
	Automation1AxisStatusItem_CoordinatedDistanceRemaining = 199,
	/// @brief The "Amplifier Peak Current" axis based status item.
	Automation1AxisStatusItem_AmplifierPeakCurrent = 211,
	/// @brief The "Servo Update Rate" axis based status item.
	Automation1AxisStatusItem_ServoUpdateRate = 220,
	/// @brief The "Safe Zone State" axis based status item.
	Automation1AxisStatusItem_SafeZoneState = 230,
	/// @brief The "Move Reference Position" axis based status item.
	Automation1AxisStatusItem_MoveReferencePosition = 237,
	/// @brief The "Move Reference Cutter Offset" axis based status item.
	Automation1AxisStatusItem_MoveReferenceCutterOffset = 250,
	/// @brief The "Move Reference Corner Offset" axis based status item.
	Automation1AxisStatusItem_MoveReferenceCornerOffset = 251,
	/// @brief The "Move Reference Total Offset" axis based status item.
	Automation1AxisStatusItem_MoveReferenceTotalOffset = 252,
	/// @brief The "Piezo Voltage Command" axis based status item.
	Automation1AxisStatusItem_PiezoVoltageCommand = 262,
	/// @brief The "Piezo Voltage Feedback" axis based status item.
	Automation1AxisStatusItem_PiezoVoltageFeedback = 263,
	/// @brief The "Distance Log" axis based status item.
	Automation1AxisStatusItem_DistanceLog = 264,
	/// @brief The "Maximum Voltage" axis based status item.
	Automation1AxisStatusItem_MaximumVoltage = 274,
	/// @brief The "Command Output Type" axis based status item.
	Automation1AxisStatusItem_CommandOutputType = 275,
	/// @brief The "AutoFocus Error" axis based status item.
	Automation1AxisStatusItem_AutoFocusError = 295,
	/// @brief The "Galvo Laser Output Raw Advance" axis based status item.
	Automation1AxisStatusItem_GalvoLaserOutputRawAdvance = 296,
	/// @brief The "Galvo Laser On Delay" axis based status item.
	Automation1AxisStatusItem_GalvoLaserOnDelay = 297,
	/// @brief The "Galvo Laser Off Delay" axis based status item.
	Automation1AxisStatusItem_GalvoLaserOffDelay = 298,
	/// @brief The "Calibration Adjustment State" axis based status item.
	Automation1AxisStatusItem_CalibrationAdjustmentState = 301,
	/// @brief The "Accuracy Correction Starting Position" axis based status item.
	Automation1AxisStatusItem_AccuracyCorrectionStartingPosition = 302,
	/// @brief The "Accuracy Correction Ending Position" axis based status item.
	Automation1AxisStatusItem_AccuracyCorrectionEndingPosition = 303,
	/// @brief The "Drive Commands Delayed" axis based status item.
	Automation1AxisStatusItem_DriveCommandsDelayed = 309,
	/// @brief The "Drive Commands Lost" axis based status item.
	Automation1AxisStatusItem_DriveCommandsLost = 310,
	/// @brief The "Sto Status" axis based status item.
	Automation1AxisStatusItem_StoStatus = 327,
	/// @brief The "Drive Assert" axis based status item.
	Automation1AxisStatusItem_DriveAssert = 336,
	/// @brief The "Acceleration SCurve Percentage" axis based status item.
	Automation1AxisStatusItem_AccelerationSCurvePercentage = 371,
	/// @brief The "Deceleration SCurve Percentage" axis based status item.
	Automation1AxisStatusItem_DecelerationSCurvePercentage = 372,
	/// @brief The "Drive Array Size" axis based status item.
	Automation1AxisStatusItem_DriveArraySize = 388,
	/// @brief The "Gantry Marker Difference" axis based status item.
	Automation1AxisStatusItem_GantryMarkerDifference = 390,
	/// @brief The "Home Target Position" axis based status item.
	Automation1AxisStatusItem_HomeTargetPosition = 398,
	/// @brief The "Gantry Realignment Move Target Position" axis based status item.
	Automation1AxisStatusItem_GantryRealignmentMoveTargetPosition = 399,
	/// @brief The "Gantry Drive Control Realignment State" axis based status item.
	Automation1AxisStatusItem_GantryDriveControlRealignmentState = 400,
} Automation1AxisStatusItem;

/// @brief Represents a task based status item that can be retrieved from the Automation1 controller.
typedef enum Automation1TaskStatusItem
{
	/// @brief The "Program Line Number" task based status item.
	Automation1TaskStatusItem_ProgramLineNumber = 17,
	/// @brief The "Coordinated Flags" task based status item.
	Automation1TaskStatusItem_CoordinatedFlags = 40,
	/// @brief The "Coordinated Arc Start Angle" task based status item.
	Automation1TaskStatusItem_CoordinatedArcStartAngle = 53,
	/// @brief The "Coordinated Arc End Angle" task based status item.
	Automation1TaskStatusItem_CoordinatedArcEndAngle = 54,
	/// @brief The "Coordinated Arc Radius" task based status item.
	Automation1TaskStatusItem_CoordinatedArcRadius = 55,
	/// @brief The "Coordinated Arc Radius Error" task based status item.
	Automation1TaskStatusItem_CoordinatedArcRadiusError = 56,
	/// @brief The "Coordinated Position Command" task based status item.
	Automation1TaskStatusItem_CoordinatedPositionCommand = 57,
	/// @brief The "Coordinated Speed Command" task based status item.
	Automation1TaskStatusItem_CoordinatedSpeedCommand = 58,
	/// @brief The "Coordinated Acceleration Command" task based status item.
	Automation1TaskStatusItem_CoordinatedAccelerationCommand = 59,
	/// @brief The "Coordinated Total Distance" task based status item.
	Automation1TaskStatusItem_CoordinatedTotalDistance = 60,
	/// @brief The "Coordinated Percent Done" task based status item.
	Automation1TaskStatusItem_CoordinatedPercentDone = 61,
	/// @brief The "Coordinated Position Command Backwards Diff" task based status item.
	Automation1TaskStatusItem_CoordinatedPositionCommandBackwardsDiff = 62,
	/// @brief The "Task Parameter" task based status item.
	Automation1TaskStatusItem_TaskParameter = 69,
	/// @brief The "Task Error" task based status item.
	Automation1TaskStatusItem_TaskError = 70,
	/// @brief The "Task Warning" task based status item.
	Automation1TaskStatusItem_TaskWarning = 71,
	/// @brief The "Coordinated Speed Target Actual" task based status item.
	Automation1TaskStatusItem_CoordinatedSpeedTargetActual = 86,
	/// @brief The "Dependent Coordinated Speed Target Actual" task based status item.
	Automation1TaskStatusItem_DependentCoordinatedSpeedTargetActual = 87,
	/// @brief The "Active Fixture Offset" task based status item.
	Automation1TaskStatusItem_ActiveFixtureOffset = 88,
	/// @brief The "Task Status 0" task based status item.
	Automation1TaskStatusItem_TaskStatus0 = 90,
	/// @brief The "Task Status 1" task based status item.
	Automation1TaskStatusItem_TaskStatus1 = 91,
	/// @brief The "Task Status 2" task based status item.
	Automation1TaskStatusItem_TaskStatus2 = 92,
	/// @brief The "Spindle Speed Target" task based status item.
	Automation1TaskStatusItem_SpindleSpeedTarget = 93,
	/// @brief The "Coordinate System 1 I" task based status item.
	Automation1TaskStatusItem_CoordinateSystem1I = 96,
	/// @brief The "Coordinate System 1 J" task based status item.
	Automation1TaskStatusItem_CoordinateSystem1J = 97,
	/// @brief The "Coordinate System 1 K" task based status item.
	Automation1TaskStatusItem_CoordinateSystem1K = 98,
	/// @brief The "Coordinate System 1 Plane" task based status item.
	Automation1TaskStatusItem_CoordinateSystem1Plane = 99,
	/// @brief The "Tool Number Active" task based status item.
	Automation1TaskStatusItem_ToolNumberActive = 100,
	/// @brief The "Mfo" task based status item.
	Automation1TaskStatusItem_Mfo = 101,
	/// @brief The "Coordinated Speed Target" task based status item.
	Automation1TaskStatusItem_CoordinatedSpeedTarget = 102,
	/// @brief The "Dependent Coordinated Speed Target" task based status item.
	Automation1TaskStatusItem_DependentCoordinatedSpeedTarget = 103,
	/// @brief The "Coordinated Acceleration Rate" task based status item.
	Automation1TaskStatusItem_CoordinatedAccelerationRate = 104,
	/// @brief The "Coordinated Deceleration Rate" task based status item.
	Automation1TaskStatusItem_CoordinatedDecelerationRate = 105,
	/// @brief The "Coordinated Acceleration Time" task based status item.
	Automation1TaskStatusItem_CoordinatedAccelerationTime = 106,
	/// @brief The "Coordinated Deceleration Time" task based status item.
	Automation1TaskStatusItem_CoordinatedDecelerationTime = 107,
	/// @brief The "Task Mode" task based status item.
	Automation1TaskStatusItem_TaskMode = 108,
	/// @brief The "Task State" task based status item.
	Automation1TaskStatusItem_TaskState = 117,
	/// @brief The "Task State Internal" task based status item.
	Automation1TaskStatusItem_TaskStateInternal = 118,
	/// @brief The "Execution Mode" task based status item.
	Automation1TaskStatusItem_ExecutionMode = 121,
	/// @brief The "Enable Alignment Axes" task based status item.
	Automation1TaskStatusItem_EnableAlignmentAxes = 127,
	/// @brief The "Queue Status" task based status item.
	Automation1TaskStatusItem_QueueStatus = 130,
	/// @brief The "Coordinated Galvo Laser Output" task based status item.
	Automation1TaskStatusItem_CoordinatedGalvoLaserOutput = 133,
	/// @brief The "Coordinated Motion Rate" task based status item.
	Automation1TaskStatusItem_CoordinatedMotionRate = 145,
	/// @brief The "Coordinated Task Command" task based status item.
	Automation1TaskStatusItem_CoordinatedTaskCommand = 146,
	/// @brief The "Enable State" task based status item.
	Automation1TaskStatusItem_EnableState = 166,
	/// @brief The "Lookahead Moves Examined" task based status item.
	Automation1TaskStatusItem_LookaheadMovesExamined = 200,
	/// @brief The "Profile Control Mask" task based status item.
	Automation1TaskStatusItem_ProfileControlMask = 231,
	/// @brief The "Coordinated Arc Radius Reciprocal" task based status item.
	Automation1TaskStatusItem_CoordinatedArcRadiusReciprocal = 253,
	/// @brief The "Motion Engine Stage" task based status item.
	Automation1TaskStatusItem_MotionEngineStage = 254,
	/// @brief The "Coordinated Time Scale" task based status item.
	Automation1TaskStatusItem_CoordinatedTimeScale = 256,
	/// @brief The "Coordinated Time Scale Derivative" task based status item.
	Automation1TaskStatusItem_CoordinatedTimeScaleDerivative = 257,
	/// @brief The "Ifov Speed Scale" task based status item.
	Automation1TaskStatusItem_IfovSpeedScale = 266,
	/// @brief The "Ifov Speed Scale Average" task based status item.
	Automation1TaskStatusItem_IfovSpeedScaleAverage = 267,
	/// @brief The "Ifov Generation Frame Counter" task based status item.
	Automation1TaskStatusItem_IfovGenerationFrameCounter = 268,
	/// @brief The "Ifov Generation Time Original" task based status item.
	Automation1TaskStatusItem_IfovGenerationTimeOriginal = 269,
	/// @brief The "Ifov Generation Time Modified" task based status item.
	Automation1TaskStatusItem_IfovGenerationTimeModified = 270,
	/// @brief The "Ifov Coordinated Position Command" task based status item.
	Automation1TaskStatusItem_IfovCoordinatedPositionCommand = 271,
	/// @brief The "Ifov Coordinated Speed Command" task based status item.
	Automation1TaskStatusItem_IfovCoordinatedSpeedCommand = 272,
	/// @brief The "Ifov Center Point H" task based status item.
	Automation1TaskStatusItem_IfovCenterPointH = 276,
	/// @brief The "Ifov Center Point V" task based status item.
	Automation1TaskStatusItem_IfovCenterPointV = 277,
	/// @brief The "Ifov Trajectory Count" task based status item.
	Automation1TaskStatusItem_IfovTrajectoryCount = 278,
	/// @brief The "Ifov Trajectory Index" task based status item.
	Automation1TaskStatusItem_IfovTrajectoryIndex = 279,
	/// @brief The "Ifov Attempt Code" task based status item.
	Automation1TaskStatusItem_IfovAttemptCode = 280,
	/// @brief The "Ifov Generation Frame Index" task based status item.
	Automation1TaskStatusItem_IfovGenerationFrameIndex = 281,
	/// @brief The "Ifov Maximum Velocity" task based status item.
	Automation1TaskStatusItem_IfovMaximumVelocity = 282,
	/// @brief The "Ifov Ideal Velocity" task based status item.
	Automation1TaskStatusItem_IfovIdealVelocity = 283,
	/// @brief The "Task Internal Debug" task based status item.
	Automation1TaskStatusItem_TaskInternalDebug = 284,
	/// @brief The "Ifov Coordinated Acceleration Command" task based status item.
	Automation1TaskStatusItem_IfovCoordinatedAccelerationCommand = 285,
	/// @brief The "Ifov Fov Position H" task based status item.
	Automation1TaskStatusItem_IfovFovPositionH = 286,
	/// @brief The "Ifov Fov Position V" task based status item.
	Automation1TaskStatusItem_IfovFovPositionV = 287,
	/// @brief The "Ifov Fov Dimension H" task based status item.
	Automation1TaskStatusItem_IfovFovDimensionH = 288,
	/// @brief The "Ifov Fov Dimension V" task based status item.
	Automation1TaskStatusItem_IfovFovDimensionV = 289,
	/// @brief The "Motion Buffer Elements" task based status item.
	Automation1TaskStatusItem_MotionBufferElements = 311,
	/// @brief The "Motion Buffer Moves" task based status item.
	Automation1TaskStatusItem_MotionBufferMoves = 312,
	/// @brief The "Motion Line Number" task based status item.
	Automation1TaskStatusItem_MotionLineNumber = 313,
	/// @brief The "Motion Buffer Retrace Moves" task based status item.
	Automation1TaskStatusItem_MotionBufferRetraceMoves = 314,
	/// @brief The "Motion Buffer Retrace Elements" task based status item.
	Automation1TaskStatusItem_MotionBufferRetraceElements = 315,
	/// @brief The "Motion Buffer Index" task based status item.
	Automation1TaskStatusItem_MotionBufferIndex = 316,
	/// @brief The "Motion Buffer Index Lookahead" task based status item.
	Automation1TaskStatusItem_MotionBufferIndexLookahead = 317,
	/// @brief The "Motion Buffer Processing Blocked" task based status item.
	Automation1TaskStatusItem_MotionBufferProcessingBlocked = 318,
	/// @brief The "Active Move Valid" task based status item.
	Automation1TaskStatusItem_ActiveMoveValid = 319,
	/// @brief The "Task Execution Lines" task based status item.
	Automation1TaskStatusItem_TaskExecutionLines = 320,
	/// @brief The "Scheduler Task Holds" task based status item.
	Automation1TaskStatusItem_SchedulerTaskHolds = 321,
	/// @brief The "Scheduler Program Loop Runs" task based status item.
	Automation1TaskStatusItem_SchedulerProgramLoopRuns = 322,
	/// @brief The "Scheduler Task Blocked" task based status item.
	Automation1TaskStatusItem_SchedulerTaskBlocked = 323,
	/// @brief The "Critical Sections Active" task based status item.
	Automation1TaskStatusItem_CriticalSectionsActive = 324,
	/// @brief The "Axes Slowdown Reason" task based status item.
	Automation1TaskStatusItem_AxesSlowdownReason = 331,
	/// @brief The "Task Execution Time" task based status item.
	Automation1TaskStatusItem_TaskExecutionTime = 333,
	/// @brief The "Task Execution Time Maximum" task based status item.
	Automation1TaskStatusItem_TaskExecutionTimeMaximum = 334,
	/// @brief The "Task Execution Lines Maximum" task based status item.
	Automation1TaskStatusItem_TaskExecutionLinesMaximum = 335,
	/// @brief The "Lookahead Decel Reason" task based status item.
	Automation1TaskStatusItem_LookaheadDecelReason = 338,
	/// @brief The "Lookahead Decel Moves" task based status item.
	Automation1TaskStatusItem_LookaheadDecelMoves = 339,
	/// @brief The "Lookahead Decel Distance" task based status item.
	Automation1TaskStatusItem_LookaheadDecelDistance = 340,
	/// @brief The "Program Counter" task based status item.
	Automation1TaskStatusItem_ProgramCounter = 341,
	/// @brief The "Stack Pointer" task based status item.
	Automation1TaskStatusItem_StackPointer = 342,
	/// @brief The "Frame Pointer" task based status item.
	Automation1TaskStatusItem_FramePointer = 343,
	/// @brief The "String Stack Pointer" task based status item.
	Automation1TaskStatusItem_StringStackPointer = 344,
	/// @brief The "Program Line Number Source File Id" task based status item.
	Automation1TaskStatusItem_ProgramLineNumberSourceFileId = 349,
	/// @brief The "Motion Line Number Source File Id" task based status item.
	Automation1TaskStatusItem_MotionLineNumberSourceFileId = 350,
	/// @brief The "Program Line Number Source Path Id" task based status item.
	Automation1TaskStatusItem_ProgramLineNumberSourcePathId = 351,
	/// @brief The "Motion Line Number Source Path Id" task based status item.
	Automation1TaskStatusItem_MotionLineNumberSourcePathId = 352,
	/// @brief The "String Argument Stack Pointer" task based status item.
	Automation1TaskStatusItem_StringArgumentStackPointer = 354,
	/// @brief The "Coordinated Acceleration SCurve Percentage" task based status item.
	Automation1TaskStatusItem_CoordinatedAccelerationSCurvePercentage = 369,
	/// @brief The "Coordinated Deceleration SCurve Percentage" task based status item.
	Automation1TaskStatusItem_CoordinatedDecelerationSCurvePercentage = 370,
	/// @brief The "Dependent Coordinated Acceleration Rate" task based status item.
	Automation1TaskStatusItem_DependentCoordinatedAccelerationRate = 373,
	/// @brief The "Dependent Coordinated Deceleration Rate" task based status item.
	Automation1TaskStatusItem_DependentCoordinatedDecelerationRate = 374,
	/// @brief The "Critical Section Timeout" task based status item.
	Automation1TaskStatusItem_CriticalSectionTimeout = 375,
} Automation1TaskStatusItem;

/// @brief Represents a system based status item that can be retrieved from the Automation1 controller.
typedef enum Automation1SystemStatusItem
{
	/// @brief The "Virtual Binary Input" system based status item.
	Automation1SystemStatusItem_VirtualBinaryInput = 46,
	/// @brief The "Virtual Binary Output" system based status item.
	Automation1SystemStatusItem_VirtualBinaryOutput = 47,
	/// @brief The "Virtual Register Input" system based status item.
	Automation1SystemStatusItem_VirtualRegisterInput = 48,
	/// @brief The "Virtual Register Output" system based status item.
	Automation1SystemStatusItem_VirtualRegisterOutput = 49,
	/// @brief The "Timer" system based status item.
	Automation1SystemStatusItem_Timer = 51,
	/// @brief The "Timer Performance" system based status item.
	Automation1SystemStatusItem_TimerPerformance = 52,
	/// @brief The "Global Real" system based status item.
	Automation1SystemStatusItem_GlobalReal = 67,
	/// @brief The "Communication Real Time Errors" system based status item.
	Automation1SystemStatusItem_CommunicationRealTimeErrors = 81,
	/// @brief The "Library Command" system based status item.
	Automation1SystemStatusItem_LibraryCommand = 119,
	/// @brief The "Data Collection Sample Time" system based status item.
	Automation1SystemStatusItem_DataCollectionSampleTime = 120,
	/// @brief The "Data Collection Sample Index" system based status item.
	Automation1SystemStatusItem_DataCollectionSampleIndex = 129,
	/// @brief The "Pc Modbus Client Connected" system based status item.
	Automation1SystemStatusItem_PcModbusClientConnected = 134,
	/// @brief The "Pc Modbus Server Connected" system based status item.
	Automation1SystemStatusItem_PcModbusServerConnected = 135,
	/// @brief The "Pc Modbus Client Error Code" system based status item.
	Automation1SystemStatusItem_PcModbusClientErrorCode = 136,
	/// @brief The "Pc Modbus Server Error Code" system based status item.
	Automation1SystemStatusItem_PcModbusServerErrorCode = 137,
	/// @brief The "Pc Modbus Client Error Location" system based status item.
	Automation1SystemStatusItem_PcModbusClientErrorLocation = 138,
	/// @brief The "Pc Modbus Server Error Location" system based status item.
	Automation1SystemStatusItem_PcModbusServerErrorLocation = 139,
	/// @brief The "Stop Watch Timer" system based status item.
	Automation1SystemStatusItem_StopWatchTimer = 157,
	/// @brief The "Scopetrig Id" system based status item.
	Automation1SystemStatusItem_ScopetrigId = 163,
	/// @brief The "Estimated Processor Usage" system based status item.
	Automation1SystemStatusItem_EstimatedProcessorUsage = 177,
	/// @brief The "Data Collection Status" system based status item.
	Automation1SystemStatusItem_DataCollectionStatus = 188,
	/// @brief The "Signal Log State" system based status item.
	Automation1SystemStatusItem_SignalLogState = 198,
	/// @brief The "Fieldbus Connected" system based status item.
	Automation1SystemStatusItem_FieldbusConnected = 202,
	/// @brief The "Fieldbus Error Code" system based status item.
	Automation1SystemStatusItem_FieldbusErrorCode = 203,
	/// @brief The "Fieldbus Error Location" system based status item.
	Automation1SystemStatusItem_FieldbusErrorLocation = 204,
	/// @brief The "Fieldbus Active Connections" system based status item.
	Automation1SystemStatusItem_FieldbusActiveConnections = 205,
	/// @brief The "Fieldbus Inactive Connections" system based status item.
	Automation1SystemStatusItem_FieldbusInactiveConnections = 206,
	/// @brief The "Safe Zone Violation Mask" system based status item.
	Automation1SystemStatusItem_SafeZoneViolationMask = 207,
	/// @brief The "Safe Zone Active Mask" system based status item.
	Automation1SystemStatusItem_SafeZoneActiveMask = 229,
	/// @brief The "Fieldbus Inputs" system based status item.
	Automation1SystemStatusItem_FieldbusInputs = 238,
	/// @brief The "Fieldbus Outputs" system based status item.
	Automation1SystemStatusItem_FieldbusOutputs = 239,
	/// @brief The "Modbus Client Input Words" system based status item.
	Automation1SystemStatusItem_ModbusClientInputWords = 240,
	/// @brief The "Modbus Client Output Words" system based status item.
	Automation1SystemStatusItem_ModbusClientOutputWords = 241,
	/// @brief The "Modbus Client Input Bits" system based status item.
	Automation1SystemStatusItem_ModbusClientInputBits = 242,
	/// @brief The "Modbus Client Output Bits" system based status item.
	Automation1SystemStatusItem_ModbusClientOutputBits = 243,
	/// @brief The "Modbus Client Output Status Bits" system based status item.
	Automation1SystemStatusItem_ModbusClientOutputStatusBits = 244,
	/// @brief The "Modbus Client Output Status Words" system based status item.
	Automation1SystemStatusItem_ModbusClientOutputStatusWords = 245,
	/// @brief The "Modbus Server Input Words" system based status item.
	Automation1SystemStatusItem_ModbusServerInputWords = 246,
	/// @brief The "Modbus Server Output Words" system based status item.
	Automation1SystemStatusItem_ModbusServerOutputWords = 247,
	/// @brief The "Modbus Server Input Bits" system based status item.
	Automation1SystemStatusItem_ModbusServerInputBits = 248,
	/// @brief The "Modbus Server Output Bits" system based status item.
	Automation1SystemStatusItem_ModbusServerOutputBits = 249,
	/// @brief The "System Parameter" system based status item.
	Automation1SystemStatusItem_SystemParameter = 265,
	/// @brief The "ThermoComp Sensor Temperature" system based status item.
	Automation1SystemStatusItem_ThermoCompSensorTemperature = 305,
	/// @brief The "ThermoComp Controlling Temperature" system based status item.
	Automation1SystemStatusItem_ThermoCompControllingTemperature = 306,
	/// @brief The "ThermoComp Compensating Temperature" system based status item.
	Automation1SystemStatusItem_ThermoCompCompensatingTemperature = 307,
	/// @brief The "ThermoComp Status" system based status item.
	Automation1SystemStatusItem_ThermoCompStatus = 308,
	/// @brief The "Global Integer" system based status item.
	Automation1SystemStatusItem_GlobalInteger = 345,
	/// @brief The "Alive Axes Mask" system based status item.
	Automation1SystemStatusItem_AliveAxesMask = 348,
	/// @brief The "Signal Log Points Stored" system based status item.
	Automation1SystemStatusItem_SignalLogPointsStored = 377,
	/// @brief The "Controller Initialization Warning" system based status item.
	Automation1SystemStatusItem_ControllerInitializationWarning = 379,
} Automation1SystemStatusItem;

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1STATUSITEM_H_INCLUDED