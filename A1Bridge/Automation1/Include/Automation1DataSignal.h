#ifndef AUTOMATION1DATASIGNAL_H_INCLUDED
#define AUTOMATION1DATASIGNAL_H_INCLUDED

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Represents an axis based data collection signal that can be retrieved from the Automation1 controller.
typedef enum Automation1AxisDataSignal
{
	/// @brief The "Position Feedback" axis based data signal.
	Automation1AxisDataSignal_PositionFeedback = 0,
	/// @brief The "Position Command" axis based data signal.
	Automation1AxisDataSignal_PositionCommand = 1,
	/// @brief The "Position Error" axis based data signal.
	Automation1AxisDataSignal_PositionError = 2,
	/// @brief The "Velocity Feedback" axis based data signal.
	Automation1AxisDataSignal_VelocityFeedback = 3,
	/// @brief The "Velocity Command" axis based data signal.
	Automation1AxisDataSignal_VelocityCommand = 4,
	/// @brief The "Velocity Error" axis based data signal.
	Automation1AxisDataSignal_VelocityError = 5,
	/// @brief The "Acceleration Command" axis based data signal.
	Automation1AxisDataSignal_AccelerationCommand = 6,
	/// @brief The "Current Error" axis based data signal.
	Automation1AxisDataSignal_CurrentError = 9,
	/// @brief The "Position Command Raw" axis based data signal.
	Automation1AxisDataSignal_PositionCommandRaw = 12,
	/// @brief The "Velocity Command Raw" axis based data signal.
	Automation1AxisDataSignal_VelocityCommandRaw = 13,
	/// @brief The "Auxiliary Feedback" axis based data signal.
	Automation1AxisDataSignal_AuxiliaryFeedback = 14,
	/// @brief The "Digital Input" axis based data signal.
	Automation1AxisDataSignal_DigitalInput = 15,
	/// @brief The "Digital Output" axis based data signal.
	Automation1AxisDataSignal_DigitalOutput = 16,
	/// @brief The "Fixture Offset" axis based data signal.
	Automation1AxisDataSignal_FixtureOffset = 18,
	/// @brief The "Coordinated Position Target" axis based data signal.
	Automation1AxisDataSignal_CoordinatedPositionTarget = 41,
	/// @brief The "Drive Status" axis based data signal.
	Automation1AxisDataSignal_DriveStatus = 42,
	/// @brief The "Axis Status" axis based data signal.
	Automation1AxisDataSignal_AxisStatus = 43,
	/// @brief The "Axis Fault" axis based data signal.
	Automation1AxisDataSignal_AxisFault = 44,
	/// @brief The "Acceleration Command Raw" axis based data signal.
	Automation1AxisDataSignal_AccelerationCommandRaw = 45,
	/// @brief The "Position Calibration All" axis based data signal.
	Automation1AxisDataSignal_PositionCalibrationAll = 50,
	/// @brief The "Position Feedback Rollover" axis based data signal.
	Automation1AxisDataSignal_PositionFeedbackRollover = 63,
	/// @brief The "Position Command Rollover" axis based data signal.
	Automation1AxisDataSignal_PositionCommandRollover = 64,
	/// @brief The "Velocity Feedback Average" axis based data signal.
	Automation1AxisDataSignal_VelocityFeedbackAverage = 65,
	/// @brief The "Current Feedback Average" axis based data signal.
	Automation1AxisDataSignal_CurrentFeedbackAverage = 66,
	/// @brief The "Axis Parameter" axis based data signal.
	Automation1AxisDataSignal_AxisParameter = 68,
	/// @brief The "Backlash" axis based data signal.
	Automation1AxisDataSignal_Backlash = 72,
	/// @brief The "Home State" axis based data signal.
	Automation1AxisDataSignal_HomeState = 73,
	/// @brief The "Position Calibration 2D" axis based data signal.
	Automation1AxisDataSignal_PositionCalibration2D = 74,
	/// @brief The "Normalcy Debug" axis based data signal.
	Automation1AxisDataSignal_NormalcyDebug = 75,
	/// @brief The "Total Move Time" axis based data signal.
	Automation1AxisDataSignal_TotalMoveTime = 76,
	/// @brief The "Jerk Command Raw" axis based data signal.
	Automation1AxisDataSignal_JerkCommandRaw = 78,
	/// @brief The "Program Position Command" axis based data signal.
	Automation1AxisDataSignal_ProgramPositionCommand = 79,
	/// @brief The "Position Offset" axis based data signal.
	Automation1AxisDataSignal_PositionOffset = 80,
	/// @brief The "Position Command Raw Backwards Diff" axis based data signal.
	Automation1AxisDataSignal_PositionCommandRawBackwardsDiff = 82,
	/// @brief The "Velocity Command Raw Backwards Diff Delta" axis based data signal.
	Automation1AxisDataSignal_VelocityCommandRawBackwardsDiffDelta = 83,
	/// @brief The "Drive Status Actual" axis based data signal.
	Automation1AxisDataSignal_DriveStatusActual = 85,
	/// @brief The "Program Position Feedback" axis based data signal.
	Automation1AxisDataSignal_ProgramPositionFeedback = 89,
	/// @brief The "Jog Trajectory Status" axis based data signal.
	Automation1AxisDataSignal_JogTrajectoryStatus = 94,
	/// @brief The "Ping Test" axis based data signal.
	Automation1AxisDataSignal_PingTest = 95,
	/// @brief The "Acceleration Time" axis based data signal.
	Automation1AxisDataSignal_AccelerationTime = 109,
	/// @brief The "Deceleration Time" axis based data signal.
	Automation1AxisDataSignal_DecelerationTime = 110,
	/// @brief The "Acceleration Rate" axis based data signal.
	Automation1AxisDataSignal_AccelerationRate = 111,
	/// @brief The "Deceleration Rate" axis based data signal.
	Automation1AxisDataSignal_DecelerationRate = 112,
	/// @brief The "Acceleration Type" axis based data signal.
	Automation1AxisDataSignal_AccelerationType = 113,
	/// @brief The "Deceleration Type" axis based data signal.
	Automation1AxisDataSignal_DecelerationType = 114,
	/// @brief The "Acceleration Mode" axis based data signal.
	Automation1AxisDataSignal_AccelerationMode = 115,
	/// @brief The "Deceleration Mode" axis based data signal.
	Automation1AxisDataSignal_DecelerationMode = 116,
	/// @brief The "Program Position" axis based data signal.
	Automation1AxisDataSignal_ProgramPosition = 124,
	/// @brief The "Speed Target" axis based data signal.
	Automation1AxisDataSignal_SpeedTarget = 128,
	/// @brief The "Position Command Packet" axis based data signal.
	Automation1AxisDataSignal_PositionCommandPacket = 131,
	/// @brief The "Drive Smc Motion State" axis based data signal.
	Automation1AxisDataSignal_DriveSmcMotionState = 132,
	/// @brief The "Position Command Raw Cal" axis based data signal.
	Automation1AxisDataSignal_PositionCommandRawCal = 140,
	/// @brief The "Velocity Command Raw Cal" axis based data signal.
	Automation1AxisDataSignal_VelocityCommandRawCal = 141,
	/// @brief The "Velocity Command Drive" axis based data signal.
	Automation1AxisDataSignal_VelocityCommandDrive = 142,
	/// @brief The "Acceleration Command Drive" axis based data signal.
	Automation1AxisDataSignal_AccelerationCommandDrive = 143,
	/// @brief The "Galvo Laser Output Raw" axis based data signal.
	Automation1AxisDataSignal_GalvoLaserOutputRaw = 144,
	/// @brief The "Drive Interface Packet Int32" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketInt32 = 147,
	/// @brief The "Drive Interface Packet Int16" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketInt16 = 148,
	/// @brief The "Drive Interface Packet Int8" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketInt8 = 149,
	/// @brief The "Drive Interface Packet Double" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketDouble = 150,
	/// @brief The "Drive Interface Packet Float" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketFloat = 151,
	/// @brief The "Drive Interface Command Code" axis based data signal.
	Automation1AxisDataSignal_DriveInterfaceCommandCode = 152,
	/// @brief The "Acceleration Feedback" axis based data signal.
	Automation1AxisDataSignal_AccelerationFeedback = 153,
	/// @brief The "Acceleration Command Raw Cal" axis based data signal.
	Automation1AxisDataSignal_AccelerationCommandRawCal = 154,
	/// @brief The "Position Calibration All Drive" axis based data signal.
	Automation1AxisDataSignal_PositionCalibrationAllDrive = 155,
	/// @brief The "Backlash Target" axis based data signal.
	Automation1AxisDataSignal_BacklashTarget = 156,
	/// @brief The "Drive Motion Rate" axis based data signal.
	Automation1AxisDataSignal_DriveMotionRate = 158,
	/// @brief The "Drive Motion Delay" axis based data signal.
	Automation1AxisDataSignal_DriveMotionDelay = 159,
	/// @brief The "Calibration Adjustment Value" axis based data signal.
	Automation1AxisDataSignal_CalibrationAdjustmentValue = 160,
	/// @brief The "Servo Rounding" axis based data signal.
	Automation1AxisDataSignal_ServoRounding = 161,
	/// @brief The "Feedforward Current" axis based data signal.
	Automation1AxisDataSignal_FeedforwardCurrent = 162,
	/// @brief The "Drive Interface Packet Info Bit Value" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketInfoBitValue = 164,
	/// @brief The "Acceleration Error" axis based data signal.
	Automation1AxisDataSignal_AccelerationError = 165,
	/// @brief The "Suppressed Faults" axis based data signal.
	Automation1AxisDataSignal_SuppressedFaults = 167,
	/// @brief The "Drive Interface Packet Streaming Data" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketStreamingData = 168,
	/// @brief The "Position Command Raw Unfiltered" axis based data signal.
	Automation1AxisDataSignal_PositionCommandRawUnfiltered = 169,
	/// @brief The "Transition Offset Errors" axis based data signal.
	Automation1AxisDataSignal_TransitionOffsetErrors = 170,
	/// @brief The "Freeze Velocity Command" axis based data signal.
	Automation1AxisDataSignal_FreezeVelocityCommand = 179,
	/// @brief The "Freeze Velocity Feedback" axis based data signal.
	Automation1AxisDataSignal_FreezeVelocityFeedback = 180,
	/// @brief The "Internal Position Offsets" axis based data signal.
	Automation1AxisDataSignal_InternalPositionOffsets = 181,
	/// @brief The "StatusHighLevelOffsetsLastMsec" axis based data signal.
	Automation1AxisDataSignal_StatusHighLevelOffsetsLastMsec = 182,
	/// @brief The "Program Velocity Command" axis based data signal.
	Automation1AxisDataSignal_ProgramVelocityCommand = 183,
	/// @brief The "Program Velocity Feedback" axis based data signal.
	Automation1AxisDataSignal_ProgramVelocityFeedback = 184,
	/// @brief The "Drive Motion Delay Live" axis based data signal.
	Automation1AxisDataSignal_DriveMotionDelayLive = 185,
	/// @brief The "Drive Communication Delay" axis based data signal.
	Automation1AxisDataSignal_DriveCommunicationDelay = 186,
	/// @brief The "Drive Communication Delay Live" axis based data signal.
	Automation1AxisDataSignal_DriveCommunicationDelayLive = 187,
	/// @brief The "Drive Interface Packet Response Int32" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketResponseInt32 = 189,
	/// @brief The "Drive Interface Packet Response Int16" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketResponseInt16 = 190,
	/// @brief The "Drive Interface Packet Response Int8" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketResponseInt8 = 191,
	/// @brief The "Drive Interface Packet Response Double" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketResponseDouble = 192,
	/// @brief The "Drive Interface Packet Response Float" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketResponseFloat = 193,
	/// @brief The "Drive Interface Packet Bit" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketBit = 194,
	/// @brief The "Drive Interface Packet Response Bit" axis based data signal.
	Automation1AxisDataSignal_DriveInterfacePacketResponseBit = 195,
	/// @brief The "Speed Target Actual" axis based data signal.
	Automation1AxisDataSignal_SpeedTargetActual = 196,
	/// @brief The "Coordinated Distance Remaining" axis based data signal.
	Automation1AxisDataSignal_CoordinatedDistanceRemaining = 199,
	/// @brief The "Safe Zone State" axis based data signal.
	Automation1AxisDataSignal_SafeZoneState = 230,
	/// @brief The "Position Error Galvo" axis based data signal.
	Automation1AxisDataSignal_PositionErrorGalvo = 235,
	/// @brief The "Move Reference Position" axis based data signal.
	Automation1AxisDataSignal_MoveReferencePosition = 237,
	/// @brief The "Move Reference Cutter Offset" axis based data signal.
	Automation1AxisDataSignal_MoveReferenceCutterOffset = 250,
	/// @brief The "Move Reference Corner Offset" axis based data signal.
	Automation1AxisDataSignal_MoveReferenceCornerOffset = 251,
	/// @brief The "Move Reference Total Offset" axis based data signal.
	Automation1AxisDataSignal_MoveReferenceTotalOffset = 252,
	/// @brief The "Distance Log" axis based data signal.
	Automation1AxisDataSignal_DistanceLog = 264,
	/// @brief The "AutoFocus Error" axis based data signal.
	Automation1AxisDataSignal_AutoFocusError = 295,
	/// @brief The "Galvo Laser Output Raw Advance" axis based data signal.
	Automation1AxisDataSignal_GalvoLaserOutputRawAdvance = 296,
	/// @brief The "Galvo Laser On Delay" axis based data signal.
	Automation1AxisDataSignal_GalvoLaserOnDelay = 297,
	/// @brief The "Galvo Laser Off Delay" axis based data signal.
	Automation1AxisDataSignal_GalvoLaserOffDelay = 298,
	/// @brief The "Calibration Adjustment State" axis based data signal.
	Automation1AxisDataSignal_CalibrationAdjustmentState = 301,
	/// @brief The "Accuracy Correction Starting Position" axis based data signal.
	Automation1AxisDataSignal_AccuracyCorrectionStartingPosition = 302,
	/// @brief The "Accuracy Correction Ending Position" axis based data signal.
	Automation1AxisDataSignal_AccuracyCorrectionEndingPosition = 303,
	/// @brief The "Drive Commands Delayed" axis based data signal.
	Automation1AxisDataSignal_DriveCommandsDelayed = 309,
	/// @brief The "Drive Commands Lost" axis based data signal.
	Automation1AxisDataSignal_DriveCommandsLost = 310,
	/// @brief The "Sto Status" axis based data signal.
	Automation1AxisDataSignal_StoStatus = 327,
	/// @brief The "Drive Assert" axis based data signal.
	Automation1AxisDataSignal_DriveAssert = 336,
	/// @brief The "Acceleration SCurve Percentage" axis based data signal.
	Automation1AxisDataSignal_AccelerationSCurvePercentage = 371,
	/// @brief The "Deceleration SCurve Percentage" axis based data signal.
	Automation1AxisDataSignal_DecelerationSCurvePercentage = 372,
	/// @brief The "Gantry Marker Difference" axis based data signal.
	Automation1AxisDataSignal_GantryMarkerDifference = 390,
	/// @brief The "Home Target Position" axis based data signal.
	Automation1AxisDataSignal_HomeTargetPosition = 398,
	/// @brief The "Gantry Realignment Move Target Position" axis based data signal.
	Automation1AxisDataSignal_GantryRealignmentMoveTargetPosition = 399,
	/// @brief The "Gantry Drive Control Realignment State" axis based data signal.
	Automation1AxisDataSignal_GantryDriveControlRealignmentState = 400,
	/// @brief The "Current Feedback" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_CurrentFeedback = 7,
	/// @brief The "Current Command" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_CurrentCommand = 8,
	/// @brief The "Analog Input 0" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AnalogInput0 = 10,
	/// @brief The "Analog Input 1" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AnalogInput1 = 11,
	/// @brief The "Phase A Current Feedback" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PhaseACurrentFeedback = 19,
	/// @brief The "Phase B Current Feedback" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PhaseBCurrentFeedback = 20,
	/// @brief The "Encoder Sine" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_EncoderSine = 21,
	/// @brief The "Encoder Cosine" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_EncoderCosine = 22,
	/// @brief The "Analog Input 2" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AnalogInput2 = 23,
	/// @brief The "Analog Input 3" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AnalogInput3 = 24,
	/// @brief The "Loop Transmission Before" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_LoopTransmissionBefore = 25,
	/// @brief The "Loop Transmission After" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_LoopTransmissionAfter = 26,
	/// @brief The "Zhs Difference" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ZhsDifference = 27,
	/// @brief The "Zhs Sum" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ZhsSum = 28,
	/// @brief The "Zhs Unfiltered" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ZhsUnfiltered = 29,
	/// @brief The "Zhs Filtered" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ZhsFiltered = 30,
	/// @brief The "Analog Output 0" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AnalogOutput0 = 31,
	/// @brief The "Analog Output 1" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AnalogOutput1 = 32,
	/// @brief The "Analog Output 2" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AnalogOutput2 = 33,
	/// @brief The "Analog Output 3" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AnalogOutput3 = 34,
	/// @brief The "Drive Memory Int32" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveMemoryInt32 = 35,
	/// @brief The "Drive Memory Float" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveMemoryFloat = 36,
	/// @brief The "Drive Memory Double" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveMemoryDouble = 37,
	/// @brief The "Pso Status" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoStatus = 38,
	/// @brief The "Drive Timer Debug" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerDebug = 39,
	/// @brief The "Position Feedback Drive" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PositionFeedbackDrive = 77,
	/// @brief The "Position Command Drive" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PositionCommandDrive = 84,
	/// @brief The "Drive Memory Int16" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveMemoryInt16 = 125,
	/// @brief The "Drive Memory Int8" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveMemoryInt8 = 126,
	/// @brief The "Pso Counter 0" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoCounter0 = 171,
	/// @brief The "Pso Counter 1" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoCounter1 = 172,
	/// @brief The "Pso Counter 2" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoCounter2 = 173,
	/// @brief The "Pso Window 0" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWindow0 = 174,
	/// @brief The "Pso Window 1" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWindow1 = 175,
	/// @brief The "Drive Data Capture Samples" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveDataCaptureSamples = 176,
	/// @brief The "Position Command Galvo" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PositionCommandGalvo = 178,
	/// @brief The "Primary EnDat Absolute Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PrimaryEnDatAbsolutePosition = 197,
	/// @brief The "Control Effort" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ControlEffort = 201,
	/// @brief The "Phase A Voltage Command" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PhaseAVoltageCommand = 208,
	/// @brief The "Phase B Voltage Command" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PhaseBVoltageCommand = 209,
	/// @brief The "Phase C Voltage Command" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PhaseCVoltageCommand = 210,
	/// @brief The "Amplifier Peak Current" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AmplifierPeakCurrent = 211,
	/// @brief The "Fpga Version" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_FpgaVersion = 212,
	/// @brief The "Drive Type Id" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTypeId = 213,
	/// @brief The "Pso Window 0 Array Index" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWindow0ArrayIndex = 214,
	/// @brief The "Pso Window 1 Array Index" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWindow1ArrayIndex = 215,
	/// @brief The "Pso Distance Array Index" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoDistanceArrayIndex = 216,
	/// @brief The "Amplifier Temperature" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AmplifierTemperature = 217,
	/// @brief The "Pso Bit Array Index" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoBitArrayIndex = 218,
	/// @brief The "Mx Absolute Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_MxAbsolutePosition = 219,
	/// @brief The "Servo Update Rate" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ServoUpdateRate = 220,
	/// @brief The "Settling Time" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_SettlingTime = 221,
	/// @brief The "Internal Error Code" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_InternalErrorCode = 222,
	/// @brief The "Firmware Version Major" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_FirmwareVersionMajor = 223,
	/// @brief The "Firmware Version Minor" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_FirmwareVersionMinor = 224,
	/// @brief The "Firmware Version Patch" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_FirmwareVersionPatch = 225,
	/// @brief The "Firmware Version Build" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_FirmwareVersionBuild = 226,
	/// @brief The "Drive Timer Debug Max" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerDebugMax = 227,
	/// @brief The "Marker Search Distance" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_MarkerSearchDistance = 228,
	/// @brief The "Position Feedback Galvo" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PositionFeedbackGalvo = 234,
	/// @brief The "Latched Marker Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_LatchedMarkerPosition = 236,
	/// @brief The "Primary Biss Absolute Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PrimaryBissAbsolutePosition = 255,
	/// @brief The "Fault Position Feedback" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_FaultPositionFeedback = 258,
	/// @brief The "Motor Commutation Angle" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_MotorCommutationAngle = 259,
	/// @brief The "Expansion Board Option" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ExpansionBoardOption = 260,
	/// @brief The "Bus Voltage" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_BusVoltage = 261,
	/// @brief The "Piezo Voltage Command" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PiezoVoltageCommand = 262,
	/// @brief The "Piezo Voltage Feedback" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PiezoVoltageFeedback = 263,
	/// @brief The "Time Since Reset" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_TimeSinceReset = 273,
	/// @brief The "Maximum Voltage" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_MaximumVoltage = 274,
	/// @brief The "Command Output Type" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_CommandOutputType = 275,
	/// @brief The "Drive Feedforward Output" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveFeedforwardOutput = 290,
	/// @brief The "Last Tick Counter" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_LastTickCounter = 291,
	/// @brief The "Board Revision" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_BoardRevision = 292,
	/// @brief The "Galvo Laser Output" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_GalvoLaserOutput = 294,
	/// @brief The "Galvo Laser Power Correction Output" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_GalvoLaserPowerCorrectionOutput = 299,
	/// @brief The "Capacitance Sensor Raw Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_CapacitanceSensorRawPosition = 300,
	/// @brief The "Position Calibration Galvo" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PositionCalibrationGalvo = 304,
	/// @brief The "Bus Voltage Negative" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_BusVoltageNegative = 325,
	/// @brief The "Processor Temperature" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ProcessorTemperature = 326,
	/// @brief The "Internal Error Timestamp" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_InternalErrorTimestamp = 328,
	/// @brief The "Analog Sensor Input" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AnalogSensorInput = 329,
	/// @brief The "Motor Temperature" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_MotorTemperature = 330,
	/// @brief The "Primary Biss Status" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PrimaryBissStatus = 332,
	/// @brief The "Pso External Sync Frequency" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoExternalSyncFrequency = 337,
	/// @brief The "Encoder Sine Raw" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_EncoderSineRaw = 346,
	/// @brief The "Encoder Cosine Raw" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_EncoderCosineRaw = 347,
	/// @brief The "Fpga Temperature" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_FpgaTemperature = 353,
	/// @brief The "Primary EnDat Status" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PrimaryEnDatStatus = 355,
	/// @brief The "Drive Timer High Priority Thread" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerHighPriorityThread = 356,
	/// @brief The "Drive Timer Low Priority Thread" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerLowPriorityThread = 357,
	/// @brief The "Drive Timer Low Priority Packet" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerLowPriorityPacket = 358,
	/// @brief The "Drive Timer Servo Packet" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerServoPacket = 359,
	/// @brief The "Drive Timer Servo Thread" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerServoThread = 360,
	/// @brief The "Drive Timer Current Packet" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerCurrentPacket = 361,
	/// @brief The "Drive Timer Common Core Thread" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerCommonCoreThread = 362,
	/// @brief The "Drive Timer Servo Core Packet 0" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerServoCorePacket0 = 363,
	/// @brief The "Drive Timer Servo Core Packet 1" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerServoCorePacket1 = 364,
	/// @brief The "Multiplier Option" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_MultiplierOption = 365,
	/// @brief The "Primary Feedback" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PrimaryFeedback = 366,
	/// @brief The "Servo Loop Feedback Input 0" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ServoLoopFeedbackInput0 = 367,
	/// @brief The "Servo Loop Feedback Input 1" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ServoLoopFeedbackInput1 = 368,
	/// @brief The "Fault Subcode" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_FaultSubcode = 376,
	/// @brief The "Processor Temperature Max" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_ProcessorTemperatureMax = 378,
	/// @brief The "Drive Timer HyperWire Dma" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveTimerHyperWireDma = 381,
	/// @brief The "Amplifier Temperature Max" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AmplifierTemperatureMax = 382,
	/// @brief The "Auxiliary EnDat Absolute Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AuxiliaryEnDatAbsolutePosition = 383,
	/// @brief The "Auxiliary EnDat Status" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AuxiliaryEnDatStatus = 384,
	/// @brief The "Auxiliary Biss Absolute Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AuxiliaryBissAbsolutePosition = 385,
	/// @brief The "Auxiliary Biss Status" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AuxiliaryBissStatus = 386,
	/// @brief The "Pso Option" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoOption = 387,
	/// @brief The "Drive Array Size" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_DriveArraySize = 388,
	/// @brief The "Rated Motor Supply Voltage Option" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_RatedMotorSupplyVoltageOption = 389,
	/// @brief The "Absolute Encoder Option" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AbsoluteEncoderOption = 391,
	/// @brief The "Primary Feedback Status" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PrimaryFeedbackStatus = 392,
	/// @brief The "Auxiliary Feedback Status" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AuxiliaryFeedbackStatus = 393,
	/// @brief The "Amplifier Status" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AmplifierStatus = 394,
	/// @brief The "Latched Cw Limit Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_LatchedCwLimitPosition = 395,
	/// @brief The "Latched Ccw Limit Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_LatchedCcwLimitPosition = 396,
	/// @brief The "Galvo Laser Fpga Transition Delay" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_GalvoLaserFpgaTransitionDelay = 397,
	/// @brief The "Piezo Accumulated Charge" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PiezoAccumulatedCharge = 401,
	/// @brief The "Piezo Charging Time" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PiezoChargingTime = 402,
	/// @brief The "Primary Ssi Absolute Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PrimarySsiAbsolutePosition = 403,
	/// @brief The "Primary Ssi Status" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PrimarySsiStatus = 404,
	/// @brief The "Auxiliary Ssi Absolute Position" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AuxiliarySsiAbsolutePosition = 405,
	/// @brief The "Auxiliary Ssi Status" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_AuxiliarySsiStatus = 406,
	/// @brief The "Pso Distance Active Distance" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoDistanceActiveDistance = 407,
	/// @brief The "Pso Window 0 Active Lower Bound" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWindow0ActiveLowerBound = 408,
	/// @brief The "Pso Window 0 Active Upper Bound" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWindow0ActiveUpperBound = 409,
	/// @brief The "Pso Window 1 Active Lower Bound" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWindow1ActiveLowerBound = 410,
	/// @brief The "Pso Window 1 Active Upper Bound" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWindow1ActiveUpperBound = 411,
	/// @brief The "Pso Waveform Active Total Time" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWaveformActiveTotalTime = 412,
	/// @brief The "Pso Waveform Active On Time" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWaveformActiveOnTime = 413,
	/// @brief The "Pso Waveform Active Pulse Count" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoWaveformActivePulseCount = 414,
	/// @brief The "Pso Event Active Bit Value" axis based data signal (this signal comes directly from the drive).
	Automation1AxisDataSignal_PsoEventActiveBitValue = 415,
} Automation1AxisDataSignal;

/// @brief Represents a task based data collection signal that can be retrieved from the Automation1 controller.
typedef enum Automation1TaskDataSignal
{
	/// @brief The "Program Line Number" task based data signal.
	Automation1TaskDataSignal_ProgramLineNumber = 17,
	/// @brief The "Coordinated Flags" task based data signal.
	Automation1TaskDataSignal_CoordinatedFlags = 40,
	/// @brief The "Coordinated Arc Start Angle" task based data signal.
	Automation1TaskDataSignal_CoordinatedArcStartAngle = 53,
	/// @brief The "Coordinated Arc End Angle" task based data signal.
	Automation1TaskDataSignal_CoordinatedArcEndAngle = 54,
	/// @brief The "Coordinated Arc Radius" task based data signal.
	Automation1TaskDataSignal_CoordinatedArcRadius = 55,
	/// @brief The "Coordinated Arc Radius Error" task based data signal.
	Automation1TaskDataSignal_CoordinatedArcRadiusError = 56,
	/// @brief The "Coordinated Position Command" task based data signal.
	Automation1TaskDataSignal_CoordinatedPositionCommand = 57,
	/// @brief The "Coordinated Speed Command" task based data signal.
	Automation1TaskDataSignal_CoordinatedSpeedCommand = 58,
	/// @brief The "Coordinated Acceleration Command" task based data signal.
	Automation1TaskDataSignal_CoordinatedAccelerationCommand = 59,
	/// @brief The "Coordinated Total Distance" task based data signal.
	Automation1TaskDataSignal_CoordinatedTotalDistance = 60,
	/// @brief The "Coordinated Percent Done" task based data signal.
	Automation1TaskDataSignal_CoordinatedPercentDone = 61,
	/// @brief The "Coordinated Position Command Backwards Diff" task based data signal.
	Automation1TaskDataSignal_CoordinatedPositionCommandBackwardsDiff = 62,
	/// @brief The "Task Parameter" task based data signal.
	Automation1TaskDataSignal_TaskParameter = 69,
	/// @brief The "Task Error" task based data signal.
	Automation1TaskDataSignal_TaskError = 70,
	/// @brief The "Task Warning" task based data signal.
	Automation1TaskDataSignal_TaskWarning = 71,
	/// @brief The "Coordinated Speed Target Actual" task based data signal.
	Automation1TaskDataSignal_CoordinatedSpeedTargetActual = 86,
	/// @brief The "Dependent Coordinated Speed Target Actual" task based data signal.
	Automation1TaskDataSignal_DependentCoordinatedSpeedTargetActual = 87,
	/// @brief The "Active Fixture Offset" task based data signal.
	Automation1TaskDataSignal_ActiveFixtureOffset = 88,
	/// @brief The "Task Status 0" task based data signal.
	Automation1TaskDataSignal_TaskStatus0 = 90,
	/// @brief The "Task Status 1" task based data signal.
	Automation1TaskDataSignal_TaskStatus1 = 91,
	/// @brief The "Task Status 2" task based data signal.
	Automation1TaskDataSignal_TaskStatus2 = 92,
	/// @brief The "Spindle Speed Target" task based data signal.
	Automation1TaskDataSignal_SpindleSpeedTarget = 93,
	/// @brief The "Coordinate System 1 I" task based data signal.
	Automation1TaskDataSignal_CoordinateSystem1I = 96,
	/// @brief The "Coordinate System 1 J" task based data signal.
	Automation1TaskDataSignal_CoordinateSystem1J = 97,
	/// @brief The "Coordinate System 1 K" task based data signal.
	Automation1TaskDataSignal_CoordinateSystem1K = 98,
	/// @brief The "Coordinate System 1 Plane" task based data signal.
	Automation1TaskDataSignal_CoordinateSystem1Plane = 99,
	/// @brief The "Tool Number Active" task based data signal.
	Automation1TaskDataSignal_ToolNumberActive = 100,
	/// @brief The "Mfo" task based data signal.
	Automation1TaskDataSignal_Mfo = 101,
	/// @brief The "Coordinated Speed Target" task based data signal.
	Automation1TaskDataSignal_CoordinatedSpeedTarget = 102,
	/// @brief The "Dependent Coordinated Speed Target" task based data signal.
	Automation1TaskDataSignal_DependentCoordinatedSpeedTarget = 103,
	/// @brief The "Coordinated Acceleration Rate" task based data signal.
	Automation1TaskDataSignal_CoordinatedAccelerationRate = 104,
	/// @brief The "Coordinated Deceleration Rate" task based data signal.
	Automation1TaskDataSignal_CoordinatedDecelerationRate = 105,
	/// @brief The "Coordinated Acceleration Time" task based data signal.
	Automation1TaskDataSignal_CoordinatedAccelerationTime = 106,
	/// @brief The "Coordinated Deceleration Time" task based data signal.
	Automation1TaskDataSignal_CoordinatedDecelerationTime = 107,
	/// @brief The "Task Mode" task based data signal.
	Automation1TaskDataSignal_TaskMode = 108,
	/// @brief The "Task State" task based data signal.
	Automation1TaskDataSignal_TaskState = 117,
	/// @brief The "Task State Internal" task based data signal.
	Automation1TaskDataSignal_TaskStateInternal = 118,
	/// @brief The "Execution Mode" task based data signal.
	Automation1TaskDataSignal_ExecutionMode = 121,
	/// @brief The "Enable Alignment Axes" task based data signal.
	Automation1TaskDataSignal_EnableAlignmentAxes = 127,
	/// @brief The "Queue Status" task based data signal.
	Automation1TaskDataSignal_QueueStatus = 130,
	/// @brief The "Coordinated Galvo Laser Output" task based data signal.
	Automation1TaskDataSignal_CoordinatedGalvoLaserOutput = 133,
	/// @brief The "Coordinated Motion Rate" task based data signal.
	Automation1TaskDataSignal_CoordinatedMotionRate = 145,
	/// @brief The "Coordinated Task Command" task based data signal.
	Automation1TaskDataSignal_CoordinatedTaskCommand = 146,
	/// @brief The "Enable State" task based data signal.
	Automation1TaskDataSignal_EnableState = 166,
	/// @brief The "Lookahead Moves Examined" task based data signal.
	Automation1TaskDataSignal_LookaheadMovesExamined = 200,
	/// @brief The "Profile Control Mask" task based data signal.
	Automation1TaskDataSignal_ProfileControlMask = 231,
	/// @brief The "Coordinated Arc Radius Reciprocal" task based data signal.
	Automation1TaskDataSignal_CoordinatedArcRadiusReciprocal = 253,
	/// @brief The "Motion Engine Stage" task based data signal.
	Automation1TaskDataSignal_MotionEngineStage = 254,
	/// @brief The "Coordinated Time Scale" task based data signal.
	Automation1TaskDataSignal_CoordinatedTimeScale = 256,
	/// @brief The "Coordinated Time Scale Derivative" task based data signal.
	Automation1TaskDataSignal_CoordinatedTimeScaleDerivative = 257,
	/// @brief The "Ifov Speed Scale" task based data signal.
	Automation1TaskDataSignal_IfovSpeedScale = 266,
	/// @brief The "Ifov Speed Scale Average" task based data signal.
	Automation1TaskDataSignal_IfovSpeedScaleAverage = 267,
	/// @brief The "Ifov Generation Frame Counter" task based data signal.
	Automation1TaskDataSignal_IfovGenerationFrameCounter = 268,
	/// @brief The "Ifov Generation Time Original" task based data signal.
	Automation1TaskDataSignal_IfovGenerationTimeOriginal = 269,
	/// @brief The "Ifov Generation Time Modified" task based data signal.
	Automation1TaskDataSignal_IfovGenerationTimeModified = 270,
	/// @brief The "Ifov Coordinated Position Command" task based data signal.
	Automation1TaskDataSignal_IfovCoordinatedPositionCommand = 271,
	/// @brief The "Ifov Coordinated Speed Command" task based data signal.
	Automation1TaskDataSignal_IfovCoordinatedSpeedCommand = 272,
	/// @brief The "Ifov Center Point H" task based data signal.
	Automation1TaskDataSignal_IfovCenterPointH = 276,
	/// @brief The "Ifov Center Point V" task based data signal.
	Automation1TaskDataSignal_IfovCenterPointV = 277,
	/// @brief The "Ifov Trajectory Count" task based data signal.
	Automation1TaskDataSignal_IfovTrajectoryCount = 278,
	/// @brief The "Ifov Trajectory Index" task based data signal.
	Automation1TaskDataSignal_IfovTrajectoryIndex = 279,
	/// @brief The "Ifov Attempt Code" task based data signal.
	Automation1TaskDataSignal_IfovAttemptCode = 280,
	/// @brief The "Ifov Generation Frame Index" task based data signal.
	Automation1TaskDataSignal_IfovGenerationFrameIndex = 281,
	/// @brief The "Ifov Maximum Velocity" task based data signal.
	Automation1TaskDataSignal_IfovMaximumVelocity = 282,
	/// @brief The "Ifov Ideal Velocity" task based data signal.
	Automation1TaskDataSignal_IfovIdealVelocity = 283,
	/// @brief The "Task Internal Debug" task based data signal.
	Automation1TaskDataSignal_TaskInternalDebug = 284,
	/// @brief The "Ifov Coordinated Acceleration Command" task based data signal.
	Automation1TaskDataSignal_IfovCoordinatedAccelerationCommand = 285,
	/// @brief The "Ifov Fov Position H" task based data signal.
	Automation1TaskDataSignal_IfovFovPositionH = 286,
	/// @brief The "Ifov Fov Position V" task based data signal.
	Automation1TaskDataSignal_IfovFovPositionV = 287,
	/// @brief The "Ifov Fov Dimension H" task based data signal.
	Automation1TaskDataSignal_IfovFovDimensionH = 288,
	/// @brief The "Ifov Fov Dimension V" task based data signal.
	Automation1TaskDataSignal_IfovFovDimensionV = 289,
	/// @brief The "Motion Buffer Elements" task based data signal.
	Automation1TaskDataSignal_MotionBufferElements = 311,
	/// @brief The "Motion Buffer Moves" task based data signal.
	Automation1TaskDataSignal_MotionBufferMoves = 312,
	/// @brief The "Motion Line Number" task based data signal.
	Automation1TaskDataSignal_MotionLineNumber = 313,
	/// @brief The "Motion Buffer Retrace Moves" task based data signal.
	Automation1TaskDataSignal_MotionBufferRetraceMoves = 314,
	/// @brief The "Motion Buffer Retrace Elements" task based data signal.
	Automation1TaskDataSignal_MotionBufferRetraceElements = 315,
	/// @brief The "Motion Buffer Index" task based data signal.
	Automation1TaskDataSignal_MotionBufferIndex = 316,
	/// @brief The "Motion Buffer Index Lookahead" task based data signal.
	Automation1TaskDataSignal_MotionBufferIndexLookahead = 317,
	/// @brief The "Motion Buffer Processing Blocked" task based data signal.
	Automation1TaskDataSignal_MotionBufferProcessingBlocked = 318,
	/// @brief The "Active Move Valid" task based data signal.
	Automation1TaskDataSignal_ActiveMoveValid = 319,
	/// @brief The "Task Execution Lines" task based data signal.
	Automation1TaskDataSignal_TaskExecutionLines = 320,
	/// @brief The "Scheduler Task Holds" task based data signal.
	Automation1TaskDataSignal_SchedulerTaskHolds = 321,
	/// @brief The "Scheduler Program Loop Runs" task based data signal.
	Automation1TaskDataSignal_SchedulerProgramLoopRuns = 322,
	/// @brief The "Scheduler Task Blocked" task based data signal.
	Automation1TaskDataSignal_SchedulerTaskBlocked = 323,
	/// @brief The "Critical Sections Active" task based data signal.
	Automation1TaskDataSignal_CriticalSectionsActive = 324,
	/// @brief The "Axes Slowdown Reason" task based data signal.
	Automation1TaskDataSignal_AxesSlowdownReason = 331,
	/// @brief The "Task Execution Time" task based data signal.
	Automation1TaskDataSignal_TaskExecutionTime = 333,
	/// @brief The "Task Execution Time Maximum" task based data signal.
	Automation1TaskDataSignal_TaskExecutionTimeMaximum = 334,
	/// @brief The "Task Execution Lines Maximum" task based data signal.
	Automation1TaskDataSignal_TaskExecutionLinesMaximum = 335,
	/// @brief The "Lookahead Decel Reason" task based data signal.
	Automation1TaskDataSignal_LookaheadDecelReason = 338,
	/// @brief The "Lookahead Decel Moves" task based data signal.
	Automation1TaskDataSignal_LookaheadDecelMoves = 339,
	/// @brief The "Lookahead Decel Distance" task based data signal.
	Automation1TaskDataSignal_LookaheadDecelDistance = 340,
	/// @brief The "Program Counter" task based data signal.
	Automation1TaskDataSignal_ProgramCounter = 341,
	/// @brief The "Stack Pointer" task based data signal.
	Automation1TaskDataSignal_StackPointer = 342,
	/// @brief The "Frame Pointer" task based data signal.
	Automation1TaskDataSignal_FramePointer = 343,
	/// @brief The "String Stack Pointer" task based data signal.
	Automation1TaskDataSignal_StringStackPointer = 344,
	/// @brief The "Program Line Number Source File Id" task based data signal.
	Automation1TaskDataSignal_ProgramLineNumberSourceFileId = 349,
	/// @brief The "Motion Line Number Source File Id" task based data signal.
	Automation1TaskDataSignal_MotionLineNumberSourceFileId = 350,
	/// @brief The "Program Line Number Source Path Id" task based data signal.
	Automation1TaskDataSignal_ProgramLineNumberSourcePathId = 351,
	/// @brief The "Motion Line Number Source Path Id" task based data signal.
	Automation1TaskDataSignal_MotionLineNumberSourcePathId = 352,
	/// @brief The "String Argument Stack Pointer" task based data signal.
	Automation1TaskDataSignal_StringArgumentStackPointer = 354,
	/// @brief The "Coordinated Acceleration SCurve Percentage" task based data signal.
	Automation1TaskDataSignal_CoordinatedAccelerationSCurvePercentage = 369,
	/// @brief The "Coordinated Deceleration SCurve Percentage" task based data signal.
	Automation1TaskDataSignal_CoordinatedDecelerationSCurvePercentage = 370,
	/// @brief The "Dependent Coordinated Acceleration Rate" task based data signal.
	Automation1TaskDataSignal_DependentCoordinatedAccelerationRate = 373,
	/// @brief The "Dependent Coordinated Deceleration Rate" task based data signal.
	Automation1TaskDataSignal_DependentCoordinatedDecelerationRate = 374,
	/// @brief The "Critical Section Timeout" task based data signal.
	Automation1TaskDataSignal_CriticalSectionTimeout = 375,
} Automation1TaskDataSignal;

/// @brief Represents a system based data collection signal that can be retrieved from the Automation1 controller.
typedef enum Automation1SystemDataSignal
{
	/// @brief The "Virtual Binary Input" system based data signal.
	Automation1SystemDataSignal_VirtualBinaryInput = 46,
	/// @brief The "Virtual Binary Output" system based data signal.
	Automation1SystemDataSignal_VirtualBinaryOutput = 47,
	/// @brief The "Virtual Register Input" system based data signal.
	Automation1SystemDataSignal_VirtualRegisterInput = 48,
	/// @brief The "Virtual Register Output" system based data signal.
	Automation1SystemDataSignal_VirtualRegisterOutput = 49,
	/// @brief The "Timer" system based data signal.
	Automation1SystemDataSignal_Timer = 51,
	/// @brief The "Timer Performance" system based data signal.
	Automation1SystemDataSignal_TimerPerformance = 52,
	/// @brief The "Global Real" system based data signal.
	Automation1SystemDataSignal_GlobalReal = 67,
	/// @brief The "Communication Real Time Errors" system based data signal.
	Automation1SystemDataSignal_CommunicationRealTimeErrors = 81,
	/// @brief The "Library Command" system based data signal.
	Automation1SystemDataSignal_LibraryCommand = 119,
	/// @brief The "Data Collection Sample Time" system based data signal.
	Automation1SystemDataSignal_DataCollectionSampleTime = 120,
	/// @brief The "Data Collection Sample Index" system based data signal.
	Automation1SystemDataSignal_DataCollectionSampleIndex = 129,
	/// @brief The "Pc Modbus Client Connected" system based data signal.
	Automation1SystemDataSignal_PcModbusClientConnected = 134,
	/// @brief The "Pc Modbus Server Connected" system based data signal.
	Automation1SystemDataSignal_PcModbusServerConnected = 135,
	/// @brief The "Pc Modbus Client Error Code" system based data signal.
	Automation1SystemDataSignal_PcModbusClientErrorCode = 136,
	/// @brief The "Pc Modbus Server Error Code" system based data signal.
	Automation1SystemDataSignal_PcModbusServerErrorCode = 137,
	/// @brief The "Pc Modbus Client Error Location" system based data signal.
	Automation1SystemDataSignal_PcModbusClientErrorLocation = 138,
	/// @brief The "Pc Modbus Server Error Location" system based data signal.
	Automation1SystemDataSignal_PcModbusServerErrorLocation = 139,
	/// @brief The "Stop Watch Timer" system based data signal.
	Automation1SystemDataSignal_StopWatchTimer = 157,
	/// @brief The "Scopetrig Id" system based data signal.
	Automation1SystemDataSignal_ScopetrigId = 163,
	/// @brief The "Estimated Processor Usage" system based data signal.
	Automation1SystemDataSignal_EstimatedProcessorUsage = 177,
	/// @brief The "Data Collection Status" system based data signal.
	Automation1SystemDataSignal_DataCollectionStatus = 188,
	/// @brief The "Signal Log State" system based data signal.
	Automation1SystemDataSignal_SignalLogState = 198,
	/// @brief The "Fieldbus Connected" system based data signal.
	Automation1SystemDataSignal_FieldbusConnected = 202,
	/// @brief The "Fieldbus Error Code" system based data signal.
	Automation1SystemDataSignal_FieldbusErrorCode = 203,
	/// @brief The "Fieldbus Error Location" system based data signal.
	Automation1SystemDataSignal_FieldbusErrorLocation = 204,
	/// @brief The "Fieldbus Active Connections" system based data signal.
	Automation1SystemDataSignal_FieldbusActiveConnections = 205,
	/// @brief The "Fieldbus Inactive Connections" system based data signal.
	Automation1SystemDataSignal_FieldbusInactiveConnections = 206,
	/// @brief The "Safe Zone Violation Mask" system based data signal.
	Automation1SystemDataSignal_SafeZoneViolationMask = 207,
	/// @brief The "Safe Zone Active Mask" system based data signal.
	Automation1SystemDataSignal_SafeZoneActiveMask = 229,
	/// @brief The "Fieldbus Inputs" system based data signal.
	Automation1SystemDataSignal_FieldbusInputs = 238,
	/// @brief The "Fieldbus Outputs" system based data signal.
	Automation1SystemDataSignal_FieldbusOutputs = 239,
	/// @brief The "Modbus Client Input Words" system based data signal.
	Automation1SystemDataSignal_ModbusClientInputWords = 240,
	/// @brief The "Modbus Client Output Words" system based data signal.
	Automation1SystemDataSignal_ModbusClientOutputWords = 241,
	/// @brief The "Modbus Client Input Bits" system based data signal.
	Automation1SystemDataSignal_ModbusClientInputBits = 242,
	/// @brief The "Modbus Client Output Bits" system based data signal.
	Automation1SystemDataSignal_ModbusClientOutputBits = 243,
	/// @brief The "Modbus Client Output Status Bits" system based data signal.
	Automation1SystemDataSignal_ModbusClientOutputStatusBits = 244,
	/// @brief The "Modbus Client Output Status Words" system based data signal.
	Automation1SystemDataSignal_ModbusClientOutputStatusWords = 245,
	/// @brief The "Modbus Server Input Words" system based data signal.
	Automation1SystemDataSignal_ModbusServerInputWords = 246,
	/// @brief The "Modbus Server Output Words" system based data signal.
	Automation1SystemDataSignal_ModbusServerOutputWords = 247,
	/// @brief The "Modbus Server Input Bits" system based data signal.
	Automation1SystemDataSignal_ModbusServerInputBits = 248,
	/// @brief The "Modbus Server Output Bits" system based data signal.
	Automation1SystemDataSignal_ModbusServerOutputBits = 249,
	/// @brief The "System Parameter" system based data signal.
	Automation1SystemDataSignal_SystemParameter = 265,
	/// @brief The "ThermoComp Sensor Temperature" system based data signal.
	Automation1SystemDataSignal_ThermoCompSensorTemperature = 305,
	/// @brief The "ThermoComp Controlling Temperature" system based data signal.
	Automation1SystemDataSignal_ThermoCompControllingTemperature = 306,
	/// @brief The "ThermoComp Compensating Temperature" system based data signal.
	Automation1SystemDataSignal_ThermoCompCompensatingTemperature = 307,
	/// @brief The "ThermoComp Status" system based data signal.
	Automation1SystemDataSignal_ThermoCompStatus = 308,
	/// @brief The "Global Integer" system based data signal.
	Automation1SystemDataSignal_GlobalInteger = 345,
	/// @brief The "Alive Axes Mask" system based data signal.
	Automation1SystemDataSignal_AliveAxesMask = 348,
	/// @brief The "Signal Log Points Stored" system based data signal.
	Automation1SystemDataSignal_SignalLogPointsStored = 377,
	/// @brief The "Controller Initialization Warning" system based data signal.
	Automation1SystemDataSignal_ControllerInitializationWarning = 379,
} Automation1SystemDataSignal;

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1DATASIGNAL_H_INCLUDED