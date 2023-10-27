///
/// Copyright (c) Aerotech, Inc.
///

#ifndef AUTOMATION1STATUSITEM_H_INCLUDED
#define AUTOMATION1STATUSITEM_H_INCLUDED

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Represents an axis based status item that can be retrieved from the Automation1 controller.
typedef enum Automation1AxisStatusItem
{
	/// @brief This item returns the position feedback.
	Automation1AxisStatusItem_PositionFeedback = 0,
	/// @brief This item returns the position command.
	Automation1AxisStatusItem_PositionCommand = 1,
	/// @brief This item returns the position error.
	Automation1AxisStatusItem_PositionError = 2,
	/// @brief This item returns the velocity feedback.
	Automation1AxisStatusItem_VelocityFeedback = 3,
	/// @brief This item returns the commanded velocity of the axis.
	Automation1AxisStatusItem_VelocityCommand = 4,
	/// @brief This item returns the velocity error.
	Automation1AxisStatusItem_VelocityError = 5,
	/// @brief This item returns the value of the acceleration command.
	Automation1AxisStatusItem_AccelerationCommand = 6,
	/// @brief This item returns the current feedback.
	Automation1AxisStatusItem_CurrentFeedback = 7,
	/// @brief This item returns the current command.
	Automation1AxisStatusItem_CurrentCommand = 8,
	/// @brief This item returns the current error.
	Automation1AxisStatusItem_CurrentError = 9,
	/// @brief This item returns the value of analog input 0.
	Automation1AxisStatusItem_AnalogInput0 = 10,
	/// @brief This item returns the value of analog input 1.
	Automation1AxisStatusItem_AnalogInput1 = 11,
	/// @brief This item returns the raw position command.
	Automation1AxisStatusItem_PositionCommandRaw = 12,
	/// @brief This item returns the raw velocity command.
	Automation1AxisStatusItem_VelocityCommandRaw = 13,
	/// @brief This item returns the feedback in encoder counts for the device connected to the Auxiliary input on the drive.
	Automation1AxisStatusItem_AuxiliaryFeedback = 14,
	/// @brief This item returns the value of the 32-bit digital input word that is read from the drive.
	Automation1AxisStatusItem_DigitalInput = 15,
	/// @brief This item returns the value of the 32-bit digital output word that is read from the drive.
	Automation1AxisStatusItem_DigitalOutput = 16,
	/// @brief This item returns the value of the active work offset that is applied to the axis position.
	Automation1AxisStatusItem_WorkOffsetValue = 18,
	/// @brief This item returns the value of analog input 2.
	Automation1AxisStatusItem_AnalogInput2 = 23,
	/// @brief This item returns the value of analog input 3.
	Automation1AxisStatusItem_AnalogInput3 = 24,
	/// @brief This item returns the value of analog output 0.
	Automation1AxisStatusItem_AnalogOutput0 = 31,
	/// @brief This item returns the value of analog output 1.
	Automation1AxisStatusItem_AnalogOutput1 = 32,
	/// @brief This item returns the value of analog output 2.
	Automation1AxisStatusItem_AnalogOutput2 = 33,
	/// @brief This item returns the value of analog output 3.
	Automation1AxisStatusItem_AnalogOutput3 = 34,
	/// @brief This item returns the value of the PSO Status word. The data type of this item is the PsoStatus enum.
	Automation1AxisStatusItem_PsoStatus = 38,
	/// @brief This item returns the coordinated target position command.
	Automation1AxisStatusItem_CoordinatedPositionTarget = 41,
	/// @brief This item returns the value of the Drive Status word. The data type of this item is the DriveStatus enum.
	Automation1AxisStatusItem_DriveStatus = 42,
	/// @brief This item returns the value of the Axis Status word. The data type of this item is the AxisStatus enum.
	Automation1AxisStatusItem_AxisStatus = 43,
	/// @brief This item returns the value of the Axis Fault word. The data type of this item is the AxisFault enum.
	Automation1AxisStatusItem_AxisFault = 44,
	/// @brief This item returns the value of the raw acceleration command.
	Automation1AxisStatusItem_AccelerationCommandRaw = 45,
	/// @brief This item returns the 1D + 2D position calibration contribution with the backlash contribution.
	Automation1AxisStatusItem_PositionCalibrationAll = 50,
	/// @brief This item returns the position feedback with rollover applied.
	Automation1AxisStatusItem_PositionFeedbackRollover = 63,
	/// @brief This item returns the position command with rollover applied.
	Automation1AxisStatusItem_PositionCommandRollover = 64,
	/// @brief This item returns the average velocity feedback.
	Automation1AxisStatusItem_VelocityFeedbackAverage = 65,
	/// @brief This item returns the average current feedback.
	Automation1AxisStatusItem_CurrentFeedbackAverage = 66,
	/// @brief This item returns the value of an axis parameter.
	Automation1AxisStatusItem_AxisParameter = 68,
	/// @brief This item returns the backlash contribution.
	Automation1AxisStatusItem_Backlash = 72,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_HomeState = 73,
	/// @brief This item returns the 2D position calibration contribution.
	Automation1AxisStatusItem_PositionCalibration2D = 74,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_NormalcyDebug = 75,
	/// @brief This item returns the total move time of the last move.
	Automation1AxisStatusItem_TotalMoveTime = 76,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_PositionFeedbackDrive = 77,
	/// @brief This item returns the raw jerk command.
	Automation1AxisStatusItem_JerkCommandRaw = 78,
	/// @brief This item returns the program position command.
	Automation1AxisStatusItem_ProgramPositionCommand = 79,
	/// @brief This item returns the value of the position offset.
	Automation1AxisStatusItem_PositionOffset = 80,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_PositionCommandRawBackwardsDiff = 82,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_VelocityCommandRawBackwardsDiffDelta = 83,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_PositionCommandDrive = 84,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveStatusActual = 85,
	/// @brief This item returns the one-based index of the active work offset for this axis.
	Automation1AxisStatusItem_WorkOffsetIndex = 88,
	/// @brief This item returns the program position feedback.
	Automation1AxisStatusItem_ProgramPositionFeedback = 89,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_JogTrajectoryStatus = 94,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_PingTest = 95,
	/// @brief This item returns the value of the axis acceleration time.
	Automation1AxisStatusItem_AccelerationTime = 109,
	/// @brief This item returns the value of the axis deceleration time.
	Automation1AxisStatusItem_DecelerationTime = 110,
	/// @brief This item returns the value of the axis acceleration rate.
	Automation1AxisStatusItem_AccelerationRate = 111,
	/// @brief This item returns the value of the axis deceleration rate.
	Automation1AxisStatusItem_DecelerationRate = 112,
	/// @brief This item returns the axis acceleration type.
	Automation1AxisStatusItem_AccelerationType = 113,
	/// @brief This item returns the axis deceleration type.
	Automation1AxisStatusItem_DecelerationType = 114,
	/// @brief This item returns the axis acceleration mode.
	Automation1AxisStatusItem_AccelerationMode = 115,
	/// @brief This item returns the axis deceleration mode.
	Automation1AxisStatusItem_DecelerationMode = 116,
	/// @brief This item returns the program position.
	Automation1AxisStatusItem_ProgramPosition = 124,
	/// @brief This item returns the target speed for an axis in a RAPID move.
	Automation1AxisStatusItem_SpeedTarget = 128,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_PositionCommandPacket = 131,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveSmcMotionState = 132,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_PositionCommandRawCal = 140,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_VelocityCommandRawCal = 141,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_VelocityCommandDrive = 142,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_AccelerationCommandDrive = 143,
	/// @brief This item returns the raw value of the galvo laser output.
	Automation1AxisStatusItem_GalvoLaserOutputRaw = 144,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketInt32 = 147,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketInt16 = 148,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketInt8 = 149,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketDouble = 150,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketFloat = 151,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfaceCommandCode = 152,
	/// @brief This item returns the value of the acceleration feedback.
	Automation1AxisStatusItem_AccelerationFeedback = 153,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_AccelerationCommandRawCal = 154,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_PositionCalibrationAllDrive = 155,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_BacklashTarget = 156,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveMotionRate = 158,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveMotionDelay = 159,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_CalibrationAdjustmentValue = 160,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_ServoLoopFeedforwardControlEffortRaw = 162,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketInfoBitValue = 164,
	/// @brief This item returns the value of the acceleration error.
	Automation1AxisStatusItem_AccelerationError = 165,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_SuppressedFaults = 167,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketStreamingData = 168,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_PositionCommandRawUnfiltered = 169,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_TransitionOffsetErrors = 170,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_FreezeVelocityCommand = 179,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_FreezeVelocityFeedback = 180,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_InternalPositionOffsets = 181,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_StatusHighLevelOffsetsLastMsec = 182,
	/// @brief This item returns the program velocity command.
	Automation1AxisStatusItem_ProgramVelocityCommand = 183,
	/// @brief This item returns the program velocity feedback.
	Automation1AxisStatusItem_ProgramVelocityFeedback = 184,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveMotionDelayLive = 185,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveCommunicationDelay = 186,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveCommunicationDelayLive = 187,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketResponseInt32 = 189,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketResponseInt16 = 190,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketResponseInt8 = 191,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketResponseDouble = 192,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketResponseFloat = 193,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketBit = 194,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePacketResponseBit = 195,
	/// @brief This item returns the limited target speed for an axis in a RAPID move.
	Automation1AxisStatusItem_SpeedTargetActual = 196,
	/// @brief This item returns the distance remaining in a coordinated motion.
	Automation1AxisStatusItem_CoordinatedDistanceRemaining = 199,
	/// @brief This item returns the peak current rating of the amplifier.
	Automation1AxisStatusItem_AmplifierPeakCurrent = 211,
	/// @brief This item returns the servo update rate in kilohertz.
	Automation1AxisStatusItem_ServoUpdateRate = 220,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_SafeZoneState = 230,
	/// @brief This item returns the position error of the galvo scanner.
	Automation1AxisStatusItem_PositionErrorGalvo = 235,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_MoveReferencePosition = 237,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_MoveReferenceCutterOffset = 250,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_MoveReferenceCornerOffset = 251,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_MoveReferenceTotalOffset = 252,
	/// @brief This item returns the voltage command for a piezo axis.
	Automation1AxisStatusItem_PiezoVoltageCommand = 262,
	/// @brief This item returns voltage feedback for a piezo axis.
	Automation1AxisStatusItem_PiezoVoltageFeedback = 263,
	/// @brief This item returns the total distance traveled by this axis.
	Automation1AxisStatusItem_DistanceLog = 264,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_MaximumVoltage = 274,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_CommandOutputType = 275,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_AutoFocusError = 295,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_GalvoLaserOutputRawAdvance = 296,
	/// @brief This item returns the time that the Nmark will command the laser to go on relative to the rising edge of the Galvo Laser Output signal.
	Automation1AxisStatusItem_GalvoLaserOnDelay = 297,
	/// @brief This item returns the time that the Nmark will command the laser to go off relative to the falling edge of the Galvo Laser Output signal.
	Automation1AxisStatusItem_GalvoLaserOffDelay = 298,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_CalibrationAdjustmentState = 301,
	/// @brief This item returns the minimum position that is corrected by accuracy calibration.
	Automation1AxisStatusItem_AccuracyCorrectionStartingPosition = 302,
	/// @brief This item returns the maximum position that is corrected by accuracy calibration.
	Automation1AxisStatusItem_AccuracyCorrectionEndingPosition = 303,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveCommandsDelayed = 309,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveCommandsLost = 310,
	/// @brief This item returns the value of the STO Status word. The data type of this item is the StoStatus enum.
	Automation1AxisStatusItem_StoStatus = 327,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveAssert = 336,
	/// @brief This item returns the feedback in encoder counts for the device connected to the Primary input on the drive.
	Automation1AxisStatusItem_PrimaryFeedback = 366,
	/// @brief This item returns the value of the axis acceleration S-curve percentage.
	Automation1AxisStatusItem_AccelerationSCurvePercentage = 371,
	/// @brief This item returns the value of the axis deceleration S-curve percentage.
	Automation1AxisStatusItem_DecelerationSCurvePercentage = 372,
	/// @brief This item returns the size of the drive array buffer.
	Automation1AxisStatusItem_DriveArraySize = 388,
	/// @brief This item returns the distance between the markers of each gantry spar along the linear direction of travel.
	Automation1AxisStatusItem_GantryMarkerDifference = 390,
	/// @brief This item returns the value of the Primary Feedback Status word. The data type of this item is the PrimaryFeedbackStatus enum.
	Automation1AxisStatusItem_PrimaryFeedbackStatus = 392,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_HomeTargetPosition = 398,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_GantryRealignmentMoveTargetPosition = 399,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_GantryDriveControlRealignmentState = 400,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveInterfacePositionCommandPhysical = 434,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1AxisStatusItem_DriveControlReason = 435,
} Automation1AxisStatusItem;

/// @brief Represents a drive supplied item that can be retrieved from the Automation1 controller.
typedef enum Automation1DriveItem
{
	/// @brief This item returns the phase A current feedback.
	Automation1DriveItem_PhaseACurrentFeedback = 19,
	/// @brief This item returns the phase B current feedback.
	Automation1DriveItem_PhaseBCurrentFeedback = 20,
	/// @brief This item returns the encoder sine value in A/D counts after correction is applied.
	Automation1DriveItem_EncoderSine = 21,
	/// @brief This item returns the encoder cosine value in A/D counts after correction is applied.
	Automation1DriveItem_EncoderCosine = 22,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_FrequencyResponseBefore = 25,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_FrequencyResponseAfter = 26,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveMemoryInt32 = 35,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveMemoryFloat = 36,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveMemoryDouble = 37,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerDebug = 39,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveMemoryInt16 = 125,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveMemoryInt8 = 126,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_ServoRounding = 161,
	/// @brief This item returns the value of PSO counter 0 in counts.
	Automation1DriveItem_PsoCounter0 = 171,
	/// @brief This item returns the value of PSO counter 1 in counts.
	Automation1DriveItem_PsoCounter1 = 172,
	/// @brief This item returns the value of PSO counter 2 in counts.
	Automation1DriveItem_PsoCounter2 = 173,
	/// @brief This item returns the value of the PSO window 0 counter in counts.
	Automation1DriveItem_PsoWindow0 = 174,
	/// @brief This item returns the value of the PSO window 1 counter in counts.
	Automation1DriveItem_PsoWindow1 = 175,
	/// @brief This item returns the number of drive data capture samples that have been acquired.
	Automation1DriveItem_DriveDataCaptureSamples = 176,
	/// @brief This item returns the position command of the galvo scanner.  This value represents the location of scanner within its field-of-view, including calibration, but does not include marking-on-the-fly.
	Automation1DriveItem_PositionCommandGalvo = 178,
	/// @brief This item returns the absolute position in encoder counts for the EnDat encoder connected to the Primary input on the drive.
	Automation1DriveItem_PrimaryEnDatAbsolutePosition = 197,
	/// @brief This item returns the value of the servo loop control effort when used with the MIMO control features.
	Automation1DriveItem_ServoLoopControlEffort = 201,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_PhaseAVoltageCommand = 208,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_PhaseBVoltageCommand = 209,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_PhaseCVoltageCommand = 210,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_FpgaVersion = 212,
	/// @brief This item returns an ID number identifying the type of drive.
	Automation1DriveItem_DriveTypeId = 213,
	/// @brief This item returns the current array index for window 0 when using the PsoWindowConfigureArrayRanges() function.
	Automation1DriveItem_PsoWindow0ArrayIndex = 214,
	/// @brief This item returns the current array index for window 1 when using the PsoWindowConfigureArrayRanges() function.
	Automation1DriveItem_PsoWindow1ArrayIndex = 215,
	/// @brief This item returns the current array index for the PsoDistanceConfigureArrayDistances() function.
	Automation1DriveItem_PsoDistanceArrayIndex = 216,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_AmplifierTemperature = 217,
	/// @brief This item returns the current array index for the PsoBitmapConfigureArray() function.
	Automation1DriveItem_PsoBitArrayIndex = 218,
	/// @brief This item returns the absolute position in encoder counts for the optional Encoder Multiplier.
	Automation1DriveItem_MxAbsolutePosition = 219,
	/// @brief This item returns the settling time in milliseconds for the most recently completed move.
	Automation1DriveItem_SettlingTime = 221,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_InternalStatusCode = 222,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_FirmwareVersionMajor = 223,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_FirmwareVersionMinor = 224,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_FirmwareVersionPatch = 225,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_FirmwareVersionBuild = 226,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerDebugMax = 227,
	/// @brief This item returns the distance that was traveled while searching for the marker.
	Automation1DriveItem_MarkerSearchDistance = 228,
	/// @brief This item returns the position feedback of the galvo scanner.  This value represents the location of scanner within its field-of-view, including calibration, but does not include marking-on-the-fly.
	Automation1DriveItem_PositionFeedbackGalvo = 234,
	/// @brief This item returns the position in encoder counts at which the marker was detected during the home cycle.
	Automation1DriveItem_LatchedMarkerPosition = 236,
	/// @brief This item returns the absolute position in encoder counts for the BiSS encoder connected to the Primary input on the drive.
	Automation1DriveItem_PrimaryBissAbsolutePosition = 255,
	/// @brief This item returns the position at which the most recent axis fault occurred.
	Automation1DriveItem_FaultPositionFeedback = 258,
	/// @brief This item returns the angle of commutation for the motor.
	Automation1DriveItem_MotorCommutationAngle = 259,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_ExpansionBoardOption = 260,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_BusVoltage = 261,
	/// @brief This item returns the amount of time since the last reset.
	Automation1DriveItem_TimeSinceReset = 273,
	/// @brief This item returns the feedforward contribution to the servo loop output as determined by the drive.
	Automation1DriveItem_ServoLoopFeedforwardControlEffort = 290,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_LastTickCounter = 291,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_BoardRevision = 292,
	/// @brief This item returns the value of the galvo laser output.
	Automation1DriveItem_GalvoLaserOutput = 294,
	/// @brief This item returns the value of the analog output after laser power correction is applied. If laser power correction is not enabled, it will return zero. Refer to Galvo Power Correction Overview for more information.
	Automation1DriveItem_GalvoLaserPowerCorrectionOutput = 299,
	/// @brief This item returns the raw reading from the capacitance sensor feedback device.
	Automation1DriveItem_CapacitanceSensorRawPosition = 300,
	/// @brief This item returns the 2D galvo calibration contribution.
	Automation1DriveItem_PositionCalibrationGalvo = 304,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_BusVoltageNegative = 325,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_ProcessorTemperature = 326,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_InternalStatusTimestamp = 328,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_AnalogSensorInput = 329,
	/// @brief This item returns the motor temperature in degrees Celsius.
	Automation1DriveItem_MotorTemperature = 330,
	/// @brief This item returns the value of the Primary Biss Status word. The data type of this item is the BissStatus enum.
	Automation1DriveItem_PrimaryBissStatus = 332,
	/// @brief This item returns the frequency in kHz of the PSO external sync signal.
	Automation1DriveItem_PsoExternalSyncFrequency = 337,
	/// @brief This item returns the encoder sine value in A/D counts before correction is applied.
	Automation1DriveItem_EncoderSineRaw = 346,
	/// @brief This item returns the encoder cosine value in A/D counts before correction is applied.
	Automation1DriveItem_EncoderCosineRaw = 347,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_FpgaTemperature = 353,
	/// @brief This item returns the value of the Primary EnDat Status word. The data type of this item is the EnDatStatus enum.
	Automation1DriveItem_PrimaryEnDatStatus = 355,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerHighPriorityThread = 356,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerLowPriorityThread = 357,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerLowPriorityPacket = 358,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerServoPacket = 359,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerServoThread = 360,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerCurrentPacket = 361,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerCommonCoreThread = 362,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerServoCorePacket = 363,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_MultiplierOption = 365,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_ServoLoopFeedbackInput0 = 367,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_ServoLoopFeedbackInput1 = 368,
	/// @brief This item returns additional information regarding the cause of an axis fault. The sub-code is not used for every fault.
	Automation1DriveItem_FaultSubcode = 376,
	/// @brief This item returns the maximum temperature in degrees Celsius of all internal processor temperature sensors.
	Automation1DriveItem_ProcessorTemperatureMax = 378,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerHyperWireDma = 381,
	/// @brief This item returns the maximum amplifier heat sink temperature in degrees Celsius.
	Automation1DriveItem_AmplifierTemperatureMax = 382,
	/// @brief This item returns the absolute position in encoder counts for the EnDat encoder connected to the Auxiliary input on the drive.
	Automation1DriveItem_AuxiliaryEnDatAbsolutePosition = 383,
	/// @brief This item returns the value of the Auxiliary EnDat Status word. The data type of this item is the EnDatStatus enum.
	Automation1DriveItem_AuxiliaryEnDatStatus = 384,
	/// @brief This item returns the absolute position in encoder counts for the BiSS encoder connected to the Auxiliary input on the drive.
	Automation1DriveItem_AuxiliaryBissAbsolutePosition = 385,
	/// @brief This item returns the value of the Auxiliary Biss Status word. The data type of this item is the BissStatus enum.
	Automation1DriveItem_AuxiliaryBissStatus = 386,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_PsoOption = 387,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_RatedMotorSupplyVoltageOption = 389,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_AbsoluteEncoderOption = 391,
	/// @brief This item returns the value of the Auxiliary Feedback Status word. The data type of this item is the AuxiliaryFeedbackStatus enum.
	Automation1DriveItem_AuxiliaryFeedbackStatus = 393,
	/// @brief This item returns the value of the Amplifier Status word. The data type of this item is the AmplifierStatus enum.
	Automation1DriveItem_AmplifierStatus = 394,
	/// @brief This item returns the position at which the CW limit was detected during execution of the MoveToLimitCw() function.
	Automation1DriveItem_LatchedCwLimitPosition = 395,
	/// @brief This item returns the position at which the CCW limit was detected during execution of the MoveToLimitCcw() function.
	Automation1DriveItem_LatchedCcwLimitPosition = 396,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_GalvoLaserFpgaTransitionDelay = 397,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_PiezoAccumulatedCharge = 401,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_PiezoChargingTime = 402,
	/// @brief This item returns the absolute position in encoder counts for the SSI encoder connected to the Primary input on the drive.
	Automation1DriveItem_PrimarySsiAbsolutePosition = 403,
	/// @brief This item returns the value of the Primary Ssi Status word. The data type of this item is the SsiStatus enum.
	Automation1DriveItem_PrimarySsiStatus = 404,
	/// @brief This item returns the absolute position in encoder counts for the SSI encoder connected to the Auxiliary input on the drive.
	Automation1DriveItem_AuxiliarySsiAbsolutePosition = 405,
	/// @brief This item returns the value of the Auxiliary Ssi Status word. The data type of this item is the SsiStatus enum.
	Automation1DriveItem_AuxiliarySsiStatus = 406,
	/// @brief This item returns active PSO distance in counts.
	Automation1DriveItem_PsoDistanceActiveDistance = 407,
	/// @brief This item returns the lower bound of the active PSO window 0 range.
	Automation1DriveItem_PsoWindow0ActiveLowerBound = 408,
	/// @brief This item returns the upper bound of the active PSO window 0 range.
	Automation1DriveItem_PsoWindow0ActiveUpperBound = 409,
	/// @brief This item returns the lower bound of the active PSO window 1 range.
	Automation1DriveItem_PsoWindow1ActiveLowerBound = 410,
	/// @brief This item returns the upper bound of the active PSO window 1 range.
	Automation1DriveItem_PsoWindow1ActiveUpperBound = 411,
	/// @brief This item returns the total time of the active PSO waveform configuration.
	Automation1DriveItem_PsoWaveformActiveTotalTime = 412,
	/// @brief This item returns the on time of the active PSO waveform configuration.
	Automation1DriveItem_PsoWaveformActiveOnTime = 413,
	/// @brief This item returns the pulse count of the active PSO waveform configuration.
	Automation1DriveItem_PsoWaveformActivePulseCount = 414,
	/// @brief This item returns the bit value of the active PSO event configuration.
	Automation1DriveItem_PsoEventActiveBitValue = 415,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerDriveBasedControllerOutputDma = 419,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveTimerPcieInboundFsm = 420,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_PrimaryFeedbackServo = 425,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_AuxiliaryFeedbackServo = 426,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveStackUsage = 427,
	/// @brief This item returns the estimated temperature of the shunt resistor.
	Automation1DriveItem_ShuntResistorTemperature = 436,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_SyncPortAPosition = 444,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_SyncPortBPosition = 445,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_HighSpeedOutputEncoderPosition = 446,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_AuxiliaryEncoderOutputPosition = 447,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_SyncPortAStatus = 448,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_SyncPortBStatus = 449,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_HighSpeedOutputEncoderStatus = 450,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_AuxiliaryEncoderOutputStatus = 451,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveMemoryUInt32 = 454,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveMemoryUInt16 = 455,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_DriveMemoryUInt8 = 456,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_CurrentLoopFeedbackControlEffort = 458,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_CurrentLoopFeedforwardControlEffort = 459,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_HighSpeedInput = 460,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_PositionCommandEncoder = 461,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1DriveItem_PositionFeedbackEncoder = 462,
	/// @brief This item returns the feedback control contribution to the servo loop output.
	Automation1DriveItem_ServoLoopFeedbackControlEffort = 463,
} Automation1DriveItem;

/// @brief Represents a task based status item that can be retrieved from the Automation1 controller.
typedef enum Automation1TaskStatusItem
{
	/// @brief This item returns the value of the program line number.
	Automation1TaskStatusItem_ProgramLineNumber = 17,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedFlags = 40,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedArcStartAngle = 53,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedArcEndAngle = 54,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedArcRadius = 55,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedArcRadiusError = 56,
	/// @brief This item returns the coordinated position command.
	Automation1TaskStatusItem_CoordinatedPositionCommand = 57,
	/// @brief This item returns the absolute value of the coordinated velocity command.
	Automation1TaskStatusItem_CoordinatedSpeedCommand = 58,
	/// @brief This item returns the absolute value of the coordinated acceleration command.
	Automation1TaskStatusItem_CoordinatedAccelerationCommand = 59,
	/// @brief This item returns the total distance of the coordinated move.
	Automation1TaskStatusItem_CoordinatedTotalDistance = 60,
	/// @brief This item returns the percentage of the coordinated move that has been completed.
	Automation1TaskStatusItem_CoordinatedPercentDone = 61,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedPositionCommandBackwardsDiff = 62,
	/// @brief This item returns the value of an task parameter.
	Automation1TaskStatusItem_TaskParameter = 69,
	/// @brief This item returns the task error that is currently active, or zero if there is no error.
	Automation1TaskStatusItem_TaskError = 70,
	/// @brief This item returns the task warning that is currently active, or zero if there is no warning.
	Automation1TaskStatusItem_TaskWarning = 71,
	/// @brief This item returns the actual target speed for dominant axes in a coordinated move. The actual target speed may differ from the commanded speed if the move does not reach constant velocity.
	Automation1TaskStatusItem_CoordinatedSpeedTargetActual = 86,
	/// @brief This item returns the actual target speed for dependent axes in a coordinated move. The actual target speed may differ from the commanded speed if the move does not reach constant velocity.
	Automation1TaskStatusItem_DependentCoordinatedSpeedTargetActual = 87,
	/// @brief This item returns the value of the Task Status 0 word. The data type of this item is the TaskStatus0 enum.
	Automation1TaskStatusItem_TaskStatus0 = 90,
	/// @brief This item returns the value of the Task Status 1 word. The data type of this item is the TaskStatus1 enum.
	Automation1TaskStatusItem_TaskStatus1 = 91,
	/// @brief This item returns the value of the Task Status 2 word. The data type of this item is the TaskStatus2 enum.
	Automation1TaskStatusItem_TaskStatus2 = 92,
	/// @brief This item returns the spindle target speed.
	Automation1TaskStatusItem_SpindleSpeedTarget = 93,
	/// @brief This item returns the axis index assigned to the I-axis of coordinate system 1.
	Automation1TaskStatusItem_CoordinateSystem1I = 96,
	/// @brief This item returns the axis index assigned to the J-axis of coordinate system 1.
	Automation1TaskStatusItem_CoordinateSystem1J = 97,
	/// @brief This item returns the axis index assigned to the K-axis of coordinate system 1.
	Automation1TaskStatusItem_CoordinateSystem1K = 98,
	/// @brief This item returns the active plane index for coordinate system 1.
	Automation1TaskStatusItem_CoordinateSystem1Plane = 99,
	/// @brief This item returns the active tool that was set by the T command.
	Automation1TaskStatusItem_ToolNumberActive = 100,
	/// @brief This item returns the MFO value.
	Automation1TaskStatusItem_Mfo = 101,
	/// @brief This item returns the target speed for dominant axes in a coordinated move. The target speed is set using the F command.
	Automation1TaskStatusItem_CoordinatedSpeedTarget = 102,
	/// @brief This item returns the target speed for dependent axes in a coordinated move. The dependent target speed is set using the E command.
	Automation1TaskStatusItem_DependentCoordinatedSpeedTarget = 103,
	/// @brief This item returns the value of the coordinated acceleration rate.
	Automation1TaskStatusItem_CoordinatedAccelerationRate = 104,
	/// @brief This item returns the value of the coordinated deceleration rate.
	Automation1TaskStatusItem_CoordinatedDecelerationRate = 105,
	/// @brief This item returns the value of the coordinated acceleration time.
	Automation1TaskStatusItem_CoordinatedAccelerationTime = 106,
	/// @brief This item returns the value of the coordinated deceleration time.
	Automation1TaskStatusItem_CoordinatedDecelerationTime = 107,
	/// @brief This item returns the value of the Task Mode word. The data type of this item is the TaskMode enum.
	Automation1TaskStatusItem_TaskMode = 108,
	/// @brief This item returns the current Task State.
	Automation1TaskStatusItem_TaskState = 117,
	/// @brief This item returns the current internal task state.
	Automation1TaskStatusItem_TaskStateInternal = 118,
	/// @brief This item returns the task execution mode.
	Automation1TaskStatusItem_ExecutionMode = 121,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_EnableAlignmentAxes = 127,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedGalvoLaserOutput = 133,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedMotionRate = 145,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedTaskCommand = 146,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_EnableState = 166,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_LookaheadMovesExamined = 200,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_ProfileControlMask = 231,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedArcRadiusReciprocal = 253,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_MotionEngineStage = 254,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedTimeScale = 256,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CoordinatedTimeScaleDerivative = 257,
	/// @brief This item returns the instantaneous speed scaling of your marking and non-marking moves in IFOV. A value of 1.0 indicates full programmed speed.
	Automation1TaskStatusItem_IfovSpeedScale = 266,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovSpeedScaleAverage = 267,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovGenerationFrameCounter = 268,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovGenerationTimeOriginal = 269,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovGenerationTimeModified = 270,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovCoordinatedPositionCommand = 271,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovCoordinatedSpeedCommand = 272,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovCenterPointH = 276,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovCenterPointV = 277,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovTrajectoryCount = 278,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovTrajectoryIndex = 279,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovAttemptCode = 280,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovGenerationFrameIndex = 281,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovMaximumVelocity = 282,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovIdealVelocity = 283,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_TaskInternalDebug = 284,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovCoordinatedAccelerationCommand = 285,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovFovPositionH = 286,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovFovPositionV = 287,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovFovDimensionH = 288,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_IfovFovDimensionV = 289,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_MotionBufferElements = 311,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_MotionBufferMoves = 312,
	/// @brief This item returns the program line number of the current move.
	Automation1TaskStatusItem_MotionLineNumber = 313,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_MotionBufferRetraceMoves = 314,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_MotionBufferRetraceElements = 315,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_MotionBufferIndex = 316,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_MotionBufferIndexLookahead = 317,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_MotionBufferProcessingBlocked = 318,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_ActiveMoveValid = 319,
	/// @brief This item returns the number of program lines executed during the last millisecond.
	Automation1TaskStatusItem_TaskExecutionLines = 320,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_SchedulerTaskHolds = 321,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_SchedulerProgramLoopRuns = 322,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_SchedulerTaskBlocked = 323,
	/// @brief This item returns the current number of active critical sections.
	Automation1TaskStatusItem_CriticalSectionsActive = 324,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_AxesSlowdownReason = 331,
	/// @brief This item returns the processor time used by the given task in the current millisecond.
	Automation1TaskStatusItem_TaskExecutionTime = 333,
	/// @brief This item returns the maximum processor time used by the given task.
	Automation1TaskStatusItem_TaskExecutionTimeMaximum = 334,
	/// @brief This item returns the maximum number of program lines executed by the task in a millisecond.
	Automation1TaskStatusItem_TaskExecutionLinesMaximum = 335,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_LookaheadDecelReason = 338,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_LookaheadDecelMoves = 339,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_LookaheadDecelDistance = 340,
	/// @brief This item returns the value of the program counter.
	Automation1TaskStatusItem_ProgramCounter = 341,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_StackPointer = 342,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_FramePointer = 343,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_StringStackPointer = 344,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_ProgramLineNumberSourceFileId = 349,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_MotionLineNumberSourceFileId = 350,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_ProgramLineNumberSourcePathId = 351,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_MotionLineNumberSourcePathId = 352,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_StringArgumentStackPointer = 354,
	/// @brief This item returns the value of the coordinated acceleration S-curve percentage.
	Automation1TaskStatusItem_CoordinatedAccelerationSCurvePercentage = 369,
	/// @brief This item returns the value of the coordinated deceleration S-curve percentage.
	Automation1TaskStatusItem_CoordinatedDecelerationSCurvePercentage = 370,
	/// @brief This item returns the value of the dependent coordinated acceleration rate.
	Automation1TaskStatusItem_DependentCoordinatedAccelerationRate = 373,
	/// @brief This item returns the value of the dependent coordinated deceleration rate.
	Automation1TaskStatusItem_DependentCoordinatedDecelerationRate = 374,
	/// @brief This item returns the current critical section timeout in microseconds.
	Automation1TaskStatusItem_CriticalSectionTimeout = 375,
	/// @brief This item returns the maximum number of commands that can simultaneously fit in the command queue.
	Automation1TaskStatusItem_CommandQueueCapacity = 421,
	/// @brief This item returns the number of commands in the command queue that have not finished executing. This item includes any command that is currently executing, if there is one.
	Automation1TaskStatusItem_CommandQueueUnexecutedCount = 422,
	/// @brief This item returns the number of times that the command queue has become empty.
	Automation1TaskStatusItem_CommandQueueTimesEmptied = 423,
	/// @brief This item returns the number of commands that have been executed from the command queue.
	Automation1TaskStatusItem_CommandQueueExecutedCount = 424,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1TaskStatusItem_CommandQueueLineNumber = 452,
} Automation1TaskStatusItem;

/// @brief Represents a system based status item that can be retrieved from the Automation1 controller.
typedef enum Automation1SystemStatusItem
{
	/// @brief This item returns the value of a 16-bit virtual binary input word.
	Automation1SystemStatusItem_VirtualBinaryInput = 46,
	/// @brief This item returns the value of a 16-bit virtual binary output word.
	Automation1SystemStatusItem_VirtualBinaryOutput = 47,
	/// @brief This item returns the value of a virtual register input.
	Automation1SystemStatusItem_VirtualRegisterInput = 48,
	/// @brief This item returns the value of a virtual register output.
	Automation1SystemStatusItem_VirtualRegisterOutput = 49,
	/// @brief This item returns the value of a system timer.
	Automation1SystemStatusItem_Timer = 51,
	/// @brief This item returns the value of a system performance timer.
	Automation1SystemStatusItem_TimerPerformance = 52,
	/// @brief This item returns the value of a global real.
	Automation1SystemStatusItem_GlobalReal = 67,
	/// @brief This item returns the number of times that the Automation1 did not have sufficient time to complete all of its operations. Refer to Optimizing Automation1 Performance for instructions about how to optimize the controller settings and prevent this problem.
	Automation1SystemStatusItem_CommunicationRealTimeErrors = 81,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_LibraryCommand = 119,
	/// @brief This item returns the data collection sample time.
	Automation1SystemStatusItem_DataCollectionSampleTime = 120,
	/// @brief This item returns the data collection sample index.
	Automation1SystemStatusItem_DataCollectionSampleIndex = 129,
	/// @brief This item returns a boolean value that indicates if the connection is established.
	Automation1SystemStatusItem_ModbusClientConnected = 134,
	/// @brief This item returns a boolean value that indicates if the connection is established.
	Automation1SystemStatusItem_ModbusServerConnected = 135,
	/// @brief This item returns the value of the last system error code to occur on this connection.
	Automation1SystemStatusItem_ModbusClientError = 136,
	/// @brief This item returns the value of the last system error code to occur on this connection.
	Automation1SystemStatusItem_ModbusServerError = 137,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_StopWatchTimer = 157,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_ScopetrigId = 163,
	/// @brief This item returns the estimated SMC processor usage as a percentage.
	Automation1SystemStatusItem_EstimatedProcessorUsage = 177,
	/// @brief This item returns the value of the Data Collection Flags word. The data type of this item is the DataCollectionFlags enum.
	Automation1SystemStatusItem_DataCollectionStatus = 188,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_SignalLogState = 198,
	/// @brief This item returns the mask of violated safe zones. Once a zone is violated it will remain violated until any one of the axes in the safe zone is moved again.
	Automation1SystemStatusItem_SafeZoneViolationMask = 207,
	/// @brief This item returns the mask of active safe zones.
	Automation1SystemStatusItem_SafeZoneActiveMask = 229,
	/// @brief This item returns the current state of the Modbus Client Input Words I/O.
	Automation1SystemStatusItem_ModbusClientInputWords = 240,
	/// @brief This item returns the current state of the Modbus Client Output Words I/O.
	Automation1SystemStatusItem_ModbusClientOutputWords = 241,
	/// @brief This item returns the current state of the Modbus Client Input Bits I/O.
	Automation1SystemStatusItem_ModbusClientInputBits = 242,
	/// @brief This item returns the current state of the Modbus Client Output Bits I/O.
	Automation1SystemStatusItem_ModbusClientOutputBits = 243,
	/// @brief This item returns the current state of the Modbus Client Output Bits Status I/O.
	Automation1SystemStatusItem_ModbusClientOutputBitsStatus = 244,
	/// @brief This item returns the current state of the Modbus Client Output Words Status I/O.
	Automation1SystemStatusItem_ModbusClientOutputWordsStatus = 245,
	/// @brief This item returns the current state of the Modbus Server Input Words I/O.
	Automation1SystemStatusItem_ModbusServerInputWords = 246,
	/// @brief This item returns the current state of the Modbus Server Output Words I/O.
	Automation1SystemStatusItem_ModbusServerOutputWords = 247,
	/// @brief This item returns the current state of the Modbus Server Input Bits I/O.
	Automation1SystemStatusItem_ModbusServerInputBits = 248,
	/// @brief This item returns the current state of the Modbus Server Output Bits I/O.
	Automation1SystemStatusItem_ModbusServerOutputBits = 249,
	/// @brief This item returns the value of a system parameter.
	Automation1SystemStatusItem_SystemParameter = 265,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_ThermoCompSensorTemperature = 305,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_ThermoCompControllingTemperature = 306,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_ThermoCompCompensatingTemperature = 307,
	/// @brief If non-zero, the ThermoComp status word is masked with this value.
	Automation1SystemStatusItem_ThermoCompStatus = 308,
	/// @brief This item returns the value of a global integer.
	Automation1SystemStatusItem_GlobalInteger = 345,
	/// @brief This item returns the mask of axes that we are communicating with.
	Automation1SystemStatusItem_AliveAxesMask = 348,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_SignalLogPointsStored = 377,
	/// @brief This item returns the warning generated during controller initialization, or zero if there is no warning.
	Automation1SystemStatusItem_ControllerInitializationWarning = 379,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_StopWatchTimerMin = 416,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_StopWatchTimerMax = 417,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_StopWatchTimerAvg = 418,
	/// @brief This item indicates if the controller has been configured to run the EtherCAT stack.
	Automation1SystemStatusItem_EthercatEnabled = 428,
	/// @brief This item returns the value of the last system error code to occur in the EtherCAT stack.
	Automation1SystemStatusItem_EthercatError = 429,
	/// @brief This item returns the value of the Tx PDO slot specified.
	Automation1SystemStatusItem_EthercatTxPdo = 430,
	/// @brief This item returns the size of the data in the Tx PDO channel as the number of bytes.
	Automation1SystemStatusItem_EthercatTxPdoSize = 431,
	/// @brief This item returns the value of the Rx PDO slot specified.
	Automation1SystemStatusItem_EthercatRxPdo = 432,
	/// @brief This item returns the size of the data in the Rx PDO channel as the number of bytes.
	Automation1SystemStatusItem_EthercatRxPdoSize = 433,
	/// @brief This item returns the current state of the EtherCAT stack.
	Automation1SystemStatusItem_EthercatState = 437,
	/// @brief This item indicates if the controller has been configured to run the Modbus Client.
	Automation1SystemStatusItem_ModbusClientEnabled = 438,
	/// @brief This item indicates if the controller has been configured to run the Modbus Server.
	Automation1SystemStatusItem_ModbusServerEnabled = 439,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_HyperWireExternalSynchronizationActive = 440,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_HyperWireExternalSynchronizationFrequency = 441,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_HyperWireExternalSynchronizationLagging = 442,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_HyperWireExternalSynchronizationAdjustmentNanoseconds = 443,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_CallbackSlotProcessingState = 453,
	/// @brief This item is internal. Do not use this item unless Aerotech personnel instructs you to do so. Aerotech might change or remove this item without warning.
	Automation1SystemStatusItem_ControllerAssertCount = 457,
} Automation1SystemStatusItem;

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1STATUSITEM_H_INCLUDED
