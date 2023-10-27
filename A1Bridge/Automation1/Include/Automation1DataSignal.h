///
/// Copyright (c) Aerotech, Inc.
///

#ifndef AUTOMATION1DATASIGNAL_H_INCLUDED
#define AUTOMATION1DATASIGNAL_H_INCLUDED

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Represents an axis based data collection signal that can be retrieved from the Automation1 controller.
typedef enum Automation1AxisDataSignal
{
	/// @brief This item returns the position feedback.
	Automation1AxisDataSignal_PositionFeedback = 0,
	/// @brief This item returns the position command.
	Automation1AxisDataSignal_PositionCommand = 1,
	/// @brief This item returns the position error.
	Automation1AxisDataSignal_PositionError = 2,
	/// @brief This item returns the velocity feedback.
	Automation1AxisDataSignal_VelocityFeedback = 3,
	/// @brief This item returns the commanded velocity of the axis.
	Automation1AxisDataSignal_VelocityCommand = 4,
	/// @brief This item returns the velocity error.
	Automation1AxisDataSignal_VelocityError = 5,
	/// @brief This item returns the value of the acceleration command.
	Automation1AxisDataSignal_AccelerationCommand = 6,
	/// @brief This item returns the current error.
	Automation1AxisDataSignal_CurrentError = 9,
	/// @brief This item returns the raw position command.
	Automation1AxisDataSignal_PositionCommandRaw = 12,
	/// @brief This item returns the raw velocity command.
	Automation1AxisDataSignal_VelocityCommandRaw = 13,
	/// @brief This item returns the feedback in encoder counts for the device connected to the Auxiliary input on the drive.
	Automation1AxisDataSignal_AuxiliaryFeedback = 14,
	/// @brief This item returns the value of the 32-bit digital input word that is read from the drive.
	Automation1AxisDataSignal_DigitalInput = 15,
	/// @brief This item returns the value of the 32-bit digital output word that is read from the drive.
	Automation1AxisDataSignal_DigitalOutput = 16,
	/// @brief This item returns the value of the active work offset that is applied to the axis position.
	Automation1AxisDataSignal_WorkOffsetValue = 18,
	/// @brief This item returns the coordinated target position command.
	Automation1AxisDataSignal_CoordinatedPositionTarget = 41,
	/// @brief This item returns the value of the Drive Status word. The data type of this item is the DriveStatus enum.
	Automation1AxisDataSignal_DriveStatus = 42,
	/// @brief This item returns the value of the Axis Status word. The data type of this item is the AxisStatus enum.
	Automation1AxisDataSignal_AxisStatus = 43,
	/// @brief This item returns the value of the Axis Fault word. The data type of this item is the AxisFault enum.
	Automation1AxisDataSignal_AxisFault = 44,
	/// @brief This item returns the value of the raw acceleration command.
	Automation1AxisDataSignal_AccelerationCommandRaw = 45,
	/// @brief This item returns the 1D + 2D position calibration contribution with the backlash contribution.
	Automation1AxisDataSignal_PositionCalibrationAll = 50,
	/// @brief This item returns the position feedback with rollover applied.
	Automation1AxisDataSignal_PositionFeedbackRollover = 63,
	/// @brief This item returns the position command with rollover applied.
	Automation1AxisDataSignal_PositionCommandRollover = 64,
	/// @brief This item returns the average velocity feedback.
	Automation1AxisDataSignal_VelocityFeedbackAverage = 65,
	/// @brief This item returns the average current feedback.
	Automation1AxisDataSignal_CurrentFeedbackAverage = 66,
	/// @brief This item returns the value of an axis parameter.
	Automation1AxisDataSignal_AxisParameter = 68,
	/// @brief This item returns the backlash contribution.
	Automation1AxisDataSignal_Backlash = 72,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_HomeState = 73,
	/// @brief This item returns the 2D position calibration contribution.
	Automation1AxisDataSignal_PositionCalibration2D = 74,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_NormalcyDebug = 75,
	/// @brief This item returns the total move time of the last move.
	Automation1AxisDataSignal_TotalMoveTime = 76,
	/// @brief This item returns the raw jerk command.
	Automation1AxisDataSignal_JerkCommandRaw = 78,
	/// @brief This item returns the program position command.
	Automation1AxisDataSignal_ProgramPositionCommand = 79,
	/// @brief This item returns the value of the position offset.
	Automation1AxisDataSignal_PositionOffset = 80,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PositionCommandRawBackwardsDiff = 82,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_VelocityCommandRawBackwardsDiffDelta = 83,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveStatusActual = 85,
	/// @brief This item returns the one-based index of the active work offset for this axis.
	Automation1AxisDataSignal_WorkOffsetIndex = 88,
	/// @brief This item returns the program position feedback.
	Automation1AxisDataSignal_ProgramPositionFeedback = 89,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_JogTrajectoryStatus = 94,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PingTest = 95,
	/// @brief This item returns the value of the axis acceleration time.
	Automation1AxisDataSignal_AccelerationTime = 109,
	/// @brief This item returns the value of the axis deceleration time.
	Automation1AxisDataSignal_DecelerationTime = 110,
	/// @brief This item returns the value of the axis acceleration rate.
	Automation1AxisDataSignal_AccelerationRate = 111,
	/// @brief This item returns the value of the axis deceleration rate.
	Automation1AxisDataSignal_DecelerationRate = 112,
	/// @brief This item returns the axis acceleration type.
	Automation1AxisDataSignal_AccelerationType = 113,
	/// @brief This item returns the axis deceleration type.
	Automation1AxisDataSignal_DecelerationType = 114,
	/// @brief This item returns the axis acceleration mode.
	Automation1AxisDataSignal_AccelerationMode = 115,
	/// @brief This item returns the axis deceleration mode.
	Automation1AxisDataSignal_DecelerationMode = 116,
	/// @brief This item returns the program position.
	Automation1AxisDataSignal_ProgramPosition = 124,
	/// @brief This item returns the target speed for an axis in a RAPID move.
	Automation1AxisDataSignal_SpeedTarget = 128,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PositionCommandPacket = 131,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveSmcMotionState = 132,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PositionCommandRawCal = 140,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_VelocityCommandRawCal = 141,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_VelocityCommandDrive = 142,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_AccelerationCommandDrive = 143,
	/// @brief This item returns the raw value of the galvo laser output.
	Automation1AxisDataSignal_GalvoLaserOutputRaw = 144,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketInt32 = 147,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketInt16 = 148,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketInt8 = 149,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketDouble = 150,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketFloat = 151,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfaceCommandCode = 152,
	/// @brief This item returns the value of the acceleration feedback.
	Automation1AxisDataSignal_AccelerationFeedback = 153,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_AccelerationCommandRawCal = 154,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PositionCalibrationAllDrive = 155,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_BacklashTarget = 156,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMotionRate = 158,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMotionDelay = 159,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_CalibrationAdjustmentValue = 160,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_ServoLoopFeedforwardControlEffortRaw = 162,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketInfoBitValue = 164,
	/// @brief This item returns the value of the acceleration error.
	Automation1AxisDataSignal_AccelerationError = 165,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_SuppressedFaults = 167,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketStreamingData = 168,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PositionCommandRawUnfiltered = 169,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_TransitionOffsetErrors = 170,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_FreezeVelocityCommand = 179,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_FreezeVelocityFeedback = 180,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_InternalPositionOffsets = 181,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_StatusHighLevelOffsetsLastMsec = 182,
	/// @brief This item returns the program velocity command.
	Automation1AxisDataSignal_ProgramVelocityCommand = 183,
	/// @brief This item returns the program velocity feedback.
	Automation1AxisDataSignal_ProgramVelocityFeedback = 184,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMotionDelayLive = 185,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveCommunicationDelay = 186,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveCommunicationDelayLive = 187,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketResponseInt32 = 189,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketResponseInt16 = 190,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketResponseInt8 = 191,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketResponseDouble = 192,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketResponseFloat = 193,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketBit = 194,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePacketResponseBit = 195,
	/// @brief This item returns the limited target speed for an axis in a RAPID move.
	Automation1AxisDataSignal_SpeedTargetActual = 196,
	/// @brief This item returns the distance remaining in a coordinated motion.
	Automation1AxisDataSignal_CoordinatedDistanceRemaining = 199,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_SafeZoneState = 230,
	/// @brief This item returns the position error of the galvo scanner.
	Automation1AxisDataSignal_PositionErrorGalvo = 235,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_MoveReferencePosition = 237,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_MoveReferenceCutterOffset = 250,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_MoveReferenceCornerOffset = 251,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_MoveReferenceTotalOffset = 252,
	/// @brief This item returns the total distance traveled by this axis.
	Automation1AxisDataSignal_DistanceLog = 264,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_AutoFocusError = 295,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_GalvoLaserOutputRawAdvance = 296,
	/// @brief This item returns the time that the Nmark will command the laser to go on relative to the rising edge of the Galvo Laser Output signal.
	Automation1AxisDataSignal_GalvoLaserOnDelay = 297,
	/// @brief This item returns the time that the Nmark will command the laser to go off relative to the falling edge of the Galvo Laser Output signal.
	Automation1AxisDataSignal_GalvoLaserOffDelay = 298,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_CalibrationAdjustmentState = 301,
	/// @brief This item returns the minimum position that is corrected by accuracy calibration.
	Automation1AxisDataSignal_AccuracyCorrectionStartingPosition = 302,
	/// @brief This item returns the maximum position that is corrected by accuracy calibration.
	Automation1AxisDataSignal_AccuracyCorrectionEndingPosition = 303,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveCommandsDelayed = 309,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveCommandsLost = 310,
	/// @brief This item returns the value of the STO Status word. The data type of this item is the StoStatus enum.
	Automation1AxisDataSignal_StoStatus = 327,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveAssert = 336,
	/// @brief This item returns the feedback in encoder counts for the device connected to the Primary input on the drive.
	Automation1AxisDataSignal_PrimaryFeedback = 366,
	/// @brief This item returns the value of the axis acceleration S-curve percentage.
	Automation1AxisDataSignal_AccelerationSCurvePercentage = 371,
	/// @brief This item returns the value of the axis deceleration S-curve percentage.
	Automation1AxisDataSignal_DecelerationSCurvePercentage = 372,
	/// @brief This item returns the distance between the markers of each gantry spar along the linear direction of travel.
	Automation1AxisDataSignal_GantryMarkerDifference = 390,
	/// @brief This item returns the value of the Primary Feedback Status word. The data type of this item is the PrimaryFeedbackStatus enum.
	Automation1AxisDataSignal_PrimaryFeedbackStatus = 392,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_HomeTargetPosition = 398,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_GantryRealignmentMoveTargetPosition = 399,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_GantryDriveControlRealignmentState = 400,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveInterfacePositionCommandPhysical = 434,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveControlReason = 435,
	/// @brief This item returns the current feedback.
	Automation1AxisDataSignal_CurrentFeedback = 7,
	/// @brief This item returns the current command.
	Automation1AxisDataSignal_CurrentCommand = 8,
	/// @brief This item returns the value of analog input 0.
	Automation1AxisDataSignal_AnalogInput0 = 10,
	/// @brief This item returns the value of analog input 1.
	Automation1AxisDataSignal_AnalogInput1 = 11,
	/// @brief This item returns the phase A current feedback.
	Automation1AxisDataSignal_PhaseACurrentFeedback = 19,
	/// @brief This item returns the phase B current feedback.
	Automation1AxisDataSignal_PhaseBCurrentFeedback = 20,
	/// @brief This item returns the encoder sine value in A/D counts after correction is applied.
	Automation1AxisDataSignal_EncoderSine = 21,
	/// @brief This item returns the encoder cosine value in A/D counts after correction is applied.
	Automation1AxisDataSignal_EncoderCosine = 22,
	/// @brief This item returns the value of analog input 2.
	Automation1AxisDataSignal_AnalogInput2 = 23,
	/// @brief This item returns the value of analog input 3.
	Automation1AxisDataSignal_AnalogInput3 = 24,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_FrequencyResponseBefore = 25,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_FrequencyResponseAfter = 26,
	/// @brief This item returns the value of analog output 0.
	Automation1AxisDataSignal_AnalogOutput0 = 31,
	/// @brief This item returns the value of analog output 1.
	Automation1AxisDataSignal_AnalogOutput1 = 32,
	/// @brief This item returns the value of analog output 2.
	Automation1AxisDataSignal_AnalogOutput2 = 33,
	/// @brief This item returns the value of analog output 3.
	Automation1AxisDataSignal_AnalogOutput3 = 34,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMemoryInt32 = 35,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMemoryFloat = 36,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMemoryDouble = 37,
	/// @brief This item returns the value of the PSO Status word. The data type of this item is the PsoStatus enum.
	Automation1AxisDataSignal_PsoStatus = 38,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerDebug = 39,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PositionFeedbackDrive = 77,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PositionCommandDrive = 84,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMemoryInt16 = 125,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMemoryInt8 = 126,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_ServoRounding = 161,
	/// @brief This item returns the value of PSO counter 0 in counts.
	Automation1AxisDataSignal_PsoCounter0 = 171,
	/// @brief This item returns the value of PSO counter 1 in counts.
	Automation1AxisDataSignal_PsoCounter1 = 172,
	/// @brief This item returns the value of PSO counter 2 in counts.
	Automation1AxisDataSignal_PsoCounter2 = 173,
	/// @brief This item returns the value of the PSO window 0 counter in counts.
	Automation1AxisDataSignal_PsoWindow0 = 174,
	/// @brief This item returns the value of the PSO window 1 counter in counts.
	Automation1AxisDataSignal_PsoWindow1 = 175,
	/// @brief This item returns the number of drive data capture samples that have been acquired.
	Automation1AxisDataSignal_DriveDataCaptureSamples = 176,
	/// @brief This item returns the position command of the galvo scanner.  This value represents the location of scanner within its field-of-view, including calibration, but does not include marking-on-the-fly.
	Automation1AxisDataSignal_PositionCommandGalvo = 178,
	/// @brief This item returns the absolute position in encoder counts for the EnDat encoder connected to the Primary input on the drive.
	Automation1AxisDataSignal_PrimaryEnDatAbsolutePosition = 197,
	/// @brief This item returns the value of the servo loop control effort when used with the MIMO control features.
	Automation1AxisDataSignal_ServoLoopControlEffort = 201,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PhaseAVoltageCommand = 208,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PhaseBVoltageCommand = 209,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PhaseCVoltageCommand = 210,
	/// @brief This item returns the peak current rating of the amplifier.
	Automation1AxisDataSignal_AmplifierPeakCurrent = 211,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_FpgaVersion = 212,
	/// @brief This item returns an ID number identifying the type of drive.
	Automation1AxisDataSignal_DriveTypeId = 213,
	/// @brief This item returns the current array index for window 0 when using the PsoWindowConfigureArrayRanges() function.
	Automation1AxisDataSignal_PsoWindow0ArrayIndex = 214,
	/// @brief This item returns the current array index for window 1 when using the PsoWindowConfigureArrayRanges() function.
	Automation1AxisDataSignal_PsoWindow1ArrayIndex = 215,
	/// @brief This item returns the current array index for the PsoDistanceConfigureArrayDistances() function.
	Automation1AxisDataSignal_PsoDistanceArrayIndex = 216,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_AmplifierTemperature = 217,
	/// @brief This item returns the current array index for the PsoBitmapConfigureArray() function.
	Automation1AxisDataSignal_PsoBitArrayIndex = 218,
	/// @brief This item returns the absolute position in encoder counts for the optional Encoder Multiplier.
	Automation1AxisDataSignal_MxAbsolutePosition = 219,
	/// @brief This item returns the servo update rate in kilohertz.
	Automation1AxisDataSignal_ServoUpdateRate = 220,
	/// @brief This item returns the settling time in milliseconds for the most recently completed move.
	Automation1AxisDataSignal_SettlingTime = 221,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_InternalStatusCode = 222,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_FirmwareVersionMajor = 223,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_FirmwareVersionMinor = 224,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_FirmwareVersionPatch = 225,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_FirmwareVersionBuild = 226,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerDebugMax = 227,
	/// @brief This item returns the distance that was traveled while searching for the marker.
	Automation1AxisDataSignal_MarkerSearchDistance = 228,
	/// @brief This item returns the position feedback of the galvo scanner.  This value represents the location of scanner within its field-of-view, including calibration, but does not include marking-on-the-fly.
	Automation1AxisDataSignal_PositionFeedbackGalvo = 234,
	/// @brief This item returns the position in encoder counts at which the marker was detected during the home cycle.
	Automation1AxisDataSignal_LatchedMarkerPosition = 236,
	/// @brief This item returns the absolute position in encoder counts for the BiSS encoder connected to the Primary input on the drive.
	Automation1AxisDataSignal_PrimaryBissAbsolutePosition = 255,
	/// @brief This item returns the position at which the most recent axis fault occurred.
	Automation1AxisDataSignal_FaultPositionFeedback = 258,
	/// @brief This item returns the angle of commutation for the motor.
	Automation1AxisDataSignal_MotorCommutationAngle = 259,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_ExpansionBoardOption = 260,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_BusVoltage = 261,
	/// @brief This item returns the voltage command for a piezo axis.
	Automation1AxisDataSignal_PiezoVoltageCommand = 262,
	/// @brief This item returns voltage feedback for a piezo axis.
	Automation1AxisDataSignal_PiezoVoltageFeedback = 263,
	/// @brief This item returns the amount of time since the last reset.
	Automation1AxisDataSignal_TimeSinceReset = 273,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_MaximumVoltage = 274,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_CommandOutputType = 275,
	/// @brief This item returns the feedforward contribution to the servo loop output as determined by the drive.
	Automation1AxisDataSignal_ServoLoopFeedforwardControlEffort = 290,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_LastTickCounter = 291,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_BoardRevision = 292,
	/// @brief This item returns the value of the galvo laser output.
	Automation1AxisDataSignal_GalvoLaserOutput = 294,
	/// @brief This item returns the value of the analog output after laser power correction is applied. If laser power correction is not enabled, it will return zero. Refer to Galvo Power Correction Overview for more information.
	Automation1AxisDataSignal_GalvoLaserPowerCorrectionOutput = 299,
	/// @brief This item returns the raw reading from the capacitance sensor feedback device.
	Automation1AxisDataSignal_CapacitanceSensorRawPosition = 300,
	/// @brief This item returns the 2D galvo calibration contribution.
	Automation1AxisDataSignal_PositionCalibrationGalvo = 304,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_BusVoltageNegative = 325,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_ProcessorTemperature = 326,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_InternalStatusTimestamp = 328,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_AnalogSensorInput = 329,
	/// @brief This item returns the motor temperature in degrees Celsius.
	Automation1AxisDataSignal_MotorTemperature = 330,
	/// @brief This item returns the value of the Primary Biss Status word. The data type of this item is the BissStatus enum.
	Automation1AxisDataSignal_PrimaryBissStatus = 332,
	/// @brief This item returns the frequency in kHz of the PSO external sync signal.
	Automation1AxisDataSignal_PsoExternalSyncFrequency = 337,
	/// @brief This item returns the encoder sine value in A/D counts before correction is applied.
	Automation1AxisDataSignal_EncoderSineRaw = 346,
	/// @brief This item returns the encoder cosine value in A/D counts before correction is applied.
	Automation1AxisDataSignal_EncoderCosineRaw = 347,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_FpgaTemperature = 353,
	/// @brief This item returns the value of the Primary EnDat Status word. The data type of this item is the EnDatStatus enum.
	Automation1AxisDataSignal_PrimaryEnDatStatus = 355,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerHighPriorityThread = 356,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerLowPriorityThread = 357,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerLowPriorityPacket = 358,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerServoPacket = 359,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerServoThread = 360,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerCurrentPacket = 361,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerCommonCoreThread = 362,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerServoCorePacket = 363,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_MultiplierOption = 365,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_ServoLoopFeedbackInput0 = 367,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_ServoLoopFeedbackInput1 = 368,
	/// @brief This item returns additional information regarding the cause of an axis fault. The sub-code is not used for every fault.
	Automation1AxisDataSignal_FaultSubcode = 376,
	/// @brief This item returns the maximum temperature in degrees Celsius of all internal processor temperature sensors.
	Automation1AxisDataSignal_ProcessorTemperatureMax = 378,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerHyperWireDma = 381,
	/// @brief This item returns the maximum amplifier heat sink temperature in degrees Celsius.
	Automation1AxisDataSignal_AmplifierTemperatureMax = 382,
	/// @brief This item returns the absolute position in encoder counts for the EnDat encoder connected to the Auxiliary input on the drive.
	Automation1AxisDataSignal_AuxiliaryEnDatAbsolutePosition = 383,
	/// @brief This item returns the value of the Auxiliary EnDat Status word. The data type of this item is the EnDatStatus enum.
	Automation1AxisDataSignal_AuxiliaryEnDatStatus = 384,
	/// @brief This item returns the absolute position in encoder counts for the BiSS encoder connected to the Auxiliary input on the drive.
	Automation1AxisDataSignal_AuxiliaryBissAbsolutePosition = 385,
	/// @brief This item returns the value of the Auxiliary Biss Status word. The data type of this item is the BissStatus enum.
	Automation1AxisDataSignal_AuxiliaryBissStatus = 386,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PsoOption = 387,
	/// @brief This item returns the size of the drive array buffer.
	Automation1AxisDataSignal_DriveArraySize = 388,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_RatedMotorSupplyVoltageOption = 389,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_AbsoluteEncoderOption = 391,
	/// @brief This item returns the value of the Auxiliary Feedback Status word. The data type of this item is the AuxiliaryFeedbackStatus enum.
	Automation1AxisDataSignal_AuxiliaryFeedbackStatus = 393,
	/// @brief This item returns the value of the Amplifier Status word. The data type of this item is the AmplifierStatus enum.
	Automation1AxisDataSignal_AmplifierStatus = 394,
	/// @brief This item returns the position at which the CW limit was detected during execution of the MoveToLimitCw() function.
	Automation1AxisDataSignal_LatchedCwLimitPosition = 395,
	/// @brief This item returns the position at which the CCW limit was detected during execution of the MoveToLimitCcw() function.
	Automation1AxisDataSignal_LatchedCcwLimitPosition = 396,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_GalvoLaserFpgaTransitionDelay = 397,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PiezoAccumulatedCharge = 401,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PiezoChargingTime = 402,
	/// @brief This item returns the absolute position in encoder counts for the SSI encoder connected to the Primary input on the drive.
	Automation1AxisDataSignal_PrimarySsiAbsolutePosition = 403,
	/// @brief This item returns the value of the Primary Ssi Status word. The data type of this item is the SsiStatus enum.
	Automation1AxisDataSignal_PrimarySsiStatus = 404,
	/// @brief This item returns the absolute position in encoder counts for the SSI encoder connected to the Auxiliary input on the drive.
	Automation1AxisDataSignal_AuxiliarySsiAbsolutePosition = 405,
	/// @brief This item returns the value of the Auxiliary Ssi Status word. The data type of this item is the SsiStatus enum.
	Automation1AxisDataSignal_AuxiliarySsiStatus = 406,
	/// @brief This item returns active PSO distance in counts.
	Automation1AxisDataSignal_PsoDistanceActiveDistance = 407,
	/// @brief This item returns the lower bound of the active PSO window 0 range.
	Automation1AxisDataSignal_PsoWindow0ActiveLowerBound = 408,
	/// @brief This item returns the upper bound of the active PSO window 0 range.
	Automation1AxisDataSignal_PsoWindow0ActiveUpperBound = 409,
	/// @brief This item returns the lower bound of the active PSO window 1 range.
	Automation1AxisDataSignal_PsoWindow1ActiveLowerBound = 410,
	/// @brief This item returns the upper bound of the active PSO window 1 range.
	Automation1AxisDataSignal_PsoWindow1ActiveUpperBound = 411,
	/// @brief This item returns the total time of the active PSO waveform configuration.
	Automation1AxisDataSignal_PsoWaveformActiveTotalTime = 412,
	/// @brief This item returns the on time of the active PSO waveform configuration.
	Automation1AxisDataSignal_PsoWaveformActiveOnTime = 413,
	/// @brief This item returns the pulse count of the active PSO waveform configuration.
	Automation1AxisDataSignal_PsoWaveformActivePulseCount = 414,
	/// @brief This item returns the bit value of the active PSO event configuration.
	Automation1AxisDataSignal_PsoEventActiveBitValue = 415,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerDriveBasedControllerOutputDma = 419,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveTimerPcieInboundFsm = 420,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PrimaryFeedbackServo = 425,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_AuxiliaryFeedbackServo = 426,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveStackUsage = 427,
	/// @brief This item returns the estimated temperature of the shunt resistor.
	Automation1AxisDataSignal_ShuntResistorTemperature = 436,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_SyncPortAPosition = 444,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_SyncPortBPosition = 445,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_HighSpeedOutputEncoderPosition = 446,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_AuxiliaryEncoderOutputPosition = 447,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_SyncPortAStatus = 448,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_SyncPortBStatus = 449,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_HighSpeedOutputEncoderStatus = 450,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_AuxiliaryEncoderOutputStatus = 451,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMemoryUInt32 = 454,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMemoryUInt16 = 455,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_DriveMemoryUInt8 = 456,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_CurrentLoopFeedbackControlEffort = 458,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_CurrentLoopFeedforwardControlEffort = 459,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_HighSpeedInput = 460,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PositionCommandEncoder = 461,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1AxisDataSignal_PositionFeedbackEncoder = 462,
	/// @brief This item returns the feedback control contribution to the servo loop output.
	Automation1AxisDataSignal_ServoLoopFeedbackControlEffort = 463,
} Automation1AxisDataSignal;

/// @brief Represents a task based data collection signal that can be retrieved from the Automation1 controller.
typedef enum Automation1TaskDataSignal
{
	/// @brief This item returns the value of the program line number.
	Automation1TaskDataSignal_ProgramLineNumber = 17,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedFlags = 40,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedArcStartAngle = 53,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedArcEndAngle = 54,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedArcRadius = 55,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedArcRadiusError = 56,
	/// @brief This item returns the coordinated position command.
	Automation1TaskDataSignal_CoordinatedPositionCommand = 57,
	/// @brief This item returns the absolute value of the coordinated velocity command.
	Automation1TaskDataSignal_CoordinatedSpeedCommand = 58,
	/// @brief This item returns the absolute value of the coordinated acceleration command.
	Automation1TaskDataSignal_CoordinatedAccelerationCommand = 59,
	/// @brief This item returns the total distance of the coordinated move.
	Automation1TaskDataSignal_CoordinatedTotalDistance = 60,
	/// @brief This item returns the percentage of the coordinated move that has been completed.
	Automation1TaskDataSignal_CoordinatedPercentDone = 61,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedPositionCommandBackwardsDiff = 62,
	/// @brief This item returns the value of an task parameter.
	Automation1TaskDataSignal_TaskParameter = 69,
	/// @brief This item returns the task error that is currently active, or zero if there is no error.
	Automation1TaskDataSignal_TaskError = 70,
	/// @brief This item returns the task warning that is currently active, or zero if there is no warning.
	Automation1TaskDataSignal_TaskWarning = 71,
	/// @brief This item returns the actual target speed for dominant axes in a coordinated move. The actual target speed may differ from the commanded speed if the move does not reach constant velocity.
	Automation1TaskDataSignal_CoordinatedSpeedTargetActual = 86,
	/// @brief This item returns the actual target speed for dependent axes in a coordinated move. The actual target speed may differ from the commanded speed if the move does not reach constant velocity.
	Automation1TaskDataSignal_DependentCoordinatedSpeedTargetActual = 87,
	/// @brief This item returns the value of the Task Status 0 word. The data type of this item is the TaskStatus0 enum.
	Automation1TaskDataSignal_TaskStatus0 = 90,
	/// @brief This item returns the value of the Task Status 1 word. The data type of this item is the TaskStatus1 enum.
	Automation1TaskDataSignal_TaskStatus1 = 91,
	/// @brief This item returns the value of the Task Status 2 word. The data type of this item is the TaskStatus2 enum.
	Automation1TaskDataSignal_TaskStatus2 = 92,
	/// @brief This item returns the spindle target speed.
	Automation1TaskDataSignal_SpindleSpeedTarget = 93,
	/// @brief This item returns the axis index assigned to the I-axis of coordinate system 1.
	Automation1TaskDataSignal_CoordinateSystem1I = 96,
	/// @brief This item returns the axis index assigned to the J-axis of coordinate system 1.
	Automation1TaskDataSignal_CoordinateSystem1J = 97,
	/// @brief This item returns the axis index assigned to the K-axis of coordinate system 1.
	Automation1TaskDataSignal_CoordinateSystem1K = 98,
	/// @brief This item returns the active plane index for coordinate system 1.
	Automation1TaskDataSignal_CoordinateSystem1Plane = 99,
	/// @brief This item returns the active tool that was set by the T command.
	Automation1TaskDataSignal_ToolNumberActive = 100,
	/// @brief This item returns the MFO value.
	Automation1TaskDataSignal_Mfo = 101,
	/// @brief This item returns the target speed for dominant axes in a coordinated move. The target speed is set using the F command.
	Automation1TaskDataSignal_CoordinatedSpeedTarget = 102,
	/// @brief This item returns the target speed for dependent axes in a coordinated move. The dependent target speed is set using the E command.
	Automation1TaskDataSignal_DependentCoordinatedSpeedTarget = 103,
	/// @brief This item returns the value of the coordinated acceleration rate.
	Automation1TaskDataSignal_CoordinatedAccelerationRate = 104,
	/// @brief This item returns the value of the coordinated deceleration rate.
	Automation1TaskDataSignal_CoordinatedDecelerationRate = 105,
	/// @brief This item returns the value of the coordinated acceleration time.
	Automation1TaskDataSignal_CoordinatedAccelerationTime = 106,
	/// @brief This item returns the value of the coordinated deceleration time.
	Automation1TaskDataSignal_CoordinatedDecelerationTime = 107,
	/// @brief This item returns the value of the Task Mode word. The data type of this item is the TaskMode enum.
	Automation1TaskDataSignal_TaskMode = 108,
	/// @brief This item returns the current Task State.
	Automation1TaskDataSignal_TaskState = 117,
	/// @brief This item returns the current internal task state.
	Automation1TaskDataSignal_TaskStateInternal = 118,
	/// @brief This item returns the task execution mode.
	Automation1TaskDataSignal_ExecutionMode = 121,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_EnableAlignmentAxes = 127,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedGalvoLaserOutput = 133,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedMotionRate = 145,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedTaskCommand = 146,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_EnableState = 166,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_LookaheadMovesExamined = 200,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_ProfileControlMask = 231,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedArcRadiusReciprocal = 253,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_MotionEngineStage = 254,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedTimeScale = 256,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CoordinatedTimeScaleDerivative = 257,
	/// @brief This item returns the instantaneous speed scaling of your marking and non-marking moves in IFOV. A value of 1.0 indicates full programmed speed.
	Automation1TaskDataSignal_IfovSpeedScale = 266,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovSpeedScaleAverage = 267,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovGenerationFrameCounter = 268,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovGenerationTimeOriginal = 269,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovGenerationTimeModified = 270,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovCoordinatedPositionCommand = 271,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovCoordinatedSpeedCommand = 272,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovCenterPointH = 276,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovCenterPointV = 277,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovTrajectoryCount = 278,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovTrajectoryIndex = 279,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovAttemptCode = 280,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovGenerationFrameIndex = 281,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovMaximumVelocity = 282,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovIdealVelocity = 283,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_TaskInternalDebug = 284,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovCoordinatedAccelerationCommand = 285,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovFovPositionH = 286,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovFovPositionV = 287,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovFovDimensionH = 288,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_IfovFovDimensionV = 289,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_MotionBufferElements = 311,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_MotionBufferMoves = 312,
	/// @brief This item returns the program line number of the current move.
	Automation1TaskDataSignal_MotionLineNumber = 313,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_MotionBufferRetraceMoves = 314,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_MotionBufferRetraceElements = 315,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_MotionBufferIndex = 316,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_MotionBufferIndexLookahead = 317,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_MotionBufferProcessingBlocked = 318,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_ActiveMoveValid = 319,
	/// @brief This item returns the number of program lines executed during the last millisecond.
	Automation1TaskDataSignal_TaskExecutionLines = 320,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_SchedulerTaskHolds = 321,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_SchedulerProgramLoopRuns = 322,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_SchedulerTaskBlocked = 323,
	/// @brief This item returns the current number of active critical sections.
	Automation1TaskDataSignal_CriticalSectionsActive = 324,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_AxesSlowdownReason = 331,
	/// @brief This item returns the processor time used by the given task in the current millisecond.
	Automation1TaskDataSignal_TaskExecutionTime = 333,
	/// @brief This item returns the maximum processor time used by the given task.
	Automation1TaskDataSignal_TaskExecutionTimeMaximum = 334,
	/// @brief This item returns the maximum number of program lines executed by the task in a millisecond.
	Automation1TaskDataSignal_TaskExecutionLinesMaximum = 335,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_LookaheadDecelReason = 338,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_LookaheadDecelMoves = 339,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_LookaheadDecelDistance = 340,
	/// @brief This item returns the value of the program counter.
	Automation1TaskDataSignal_ProgramCounter = 341,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_StackPointer = 342,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_FramePointer = 343,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_StringStackPointer = 344,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_ProgramLineNumberSourceFileId = 349,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_MotionLineNumberSourceFileId = 350,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_ProgramLineNumberSourcePathId = 351,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_MotionLineNumberSourcePathId = 352,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_StringArgumentStackPointer = 354,
	/// @brief This item returns the value of the coordinated acceleration S-curve percentage.
	Automation1TaskDataSignal_CoordinatedAccelerationSCurvePercentage = 369,
	/// @brief This item returns the value of the coordinated deceleration S-curve percentage.
	Automation1TaskDataSignal_CoordinatedDecelerationSCurvePercentage = 370,
	/// @brief This item returns the value of the dependent coordinated acceleration rate.
	Automation1TaskDataSignal_DependentCoordinatedAccelerationRate = 373,
	/// @brief This item returns the value of the dependent coordinated deceleration rate.
	Automation1TaskDataSignal_DependentCoordinatedDecelerationRate = 374,
	/// @brief This item returns the current critical section timeout in microseconds.
	Automation1TaskDataSignal_CriticalSectionTimeout = 375,
	/// @brief This item returns the maximum number of commands that can simultaneously fit in the command queue.
	Automation1TaskDataSignal_CommandQueueCapacity = 421,
	/// @brief This item returns the number of commands in the command queue that have not finished executing. This item includes any command that is currently executing, if there is one.
	Automation1TaskDataSignal_CommandQueueUnexecutedCount = 422,
	/// @brief This item returns the number of times that the command queue has become empty.
	Automation1TaskDataSignal_CommandQueueTimesEmptied = 423,
	/// @brief This item returns the number of commands that have been executed from the command queue.
	Automation1TaskDataSignal_CommandQueueExecutedCount = 424,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1TaskDataSignal_CommandQueueLineNumber = 452,
} Automation1TaskDataSignal;

/// @brief Represents a system based data collection signal that can be retrieved from the Automation1 controller.
typedef enum Automation1SystemDataSignal
{
	/// @brief This item returns the value of a 16-bit virtual binary input word.
	Automation1SystemDataSignal_VirtualBinaryInput = 46,
	/// @brief This item returns the value of a 16-bit virtual binary output word.
	Automation1SystemDataSignal_VirtualBinaryOutput = 47,
	/// @brief This item returns the value of a virtual register input.
	Automation1SystemDataSignal_VirtualRegisterInput = 48,
	/// @brief This item returns the value of a virtual register output.
	Automation1SystemDataSignal_VirtualRegisterOutput = 49,
	/// @brief This item returns the value of a system timer.
	Automation1SystemDataSignal_Timer = 51,
	/// @brief This item returns the value of a system performance timer.
	Automation1SystemDataSignal_TimerPerformance = 52,
	/// @brief This item returns the value of a global real.
	Automation1SystemDataSignal_GlobalReal = 67,
	/// @brief This item returns the number of times that the Automation1 did not have sufficient time to complete all of its operations. Refer to Optimizing Automation1 Performance for instructions about how to optimize the controller settings and prevent this problem.
	Automation1SystemDataSignal_CommunicationRealTimeErrors = 81,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_LibraryCommand = 119,
	/// @brief This item returns the data collection sample time.
	Automation1SystemDataSignal_DataCollectionSampleTime = 120,
	/// @brief This item returns the data collection sample index.
	Automation1SystemDataSignal_DataCollectionSampleIndex = 129,
	/// @brief This item returns a boolean value that indicates if the connection is established.
	Automation1SystemDataSignal_ModbusClientConnected = 134,
	/// @brief This item returns a boolean value that indicates if the connection is established.
	Automation1SystemDataSignal_ModbusServerConnected = 135,
	/// @brief This item returns the value of the last system error code to occur on this connection.
	Automation1SystemDataSignal_ModbusClientError = 136,
	/// @brief This item returns the value of the last system error code to occur on this connection.
	Automation1SystemDataSignal_ModbusServerError = 137,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_StopWatchTimer = 157,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_ScopetrigId = 163,
	/// @brief This item returns the estimated SMC processor usage as a percentage.
	Automation1SystemDataSignal_EstimatedProcessorUsage = 177,
	/// @brief This item returns the value of the Data Collection Flags word. The data type of this item is the DataCollectionFlags enum.
	Automation1SystemDataSignal_DataCollectionStatus = 188,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_SignalLogState = 198,
	/// @brief This item returns the mask of violated safe zones. Once a zone is violated it will remain violated until any one of the axes in the safe zone is moved again.
	Automation1SystemDataSignal_SafeZoneViolationMask = 207,
	/// @brief This item returns the mask of active safe zones.
	Automation1SystemDataSignal_SafeZoneActiveMask = 229,
	/// @brief This item returns the current state of the Modbus Client Input Words I/O.
	Automation1SystemDataSignal_ModbusClientInputWords = 240,
	/// @brief This item returns the current state of the Modbus Client Output Words I/O.
	Automation1SystemDataSignal_ModbusClientOutputWords = 241,
	/// @brief This item returns the current state of the Modbus Client Input Bits I/O.
	Automation1SystemDataSignal_ModbusClientInputBits = 242,
	/// @brief This item returns the current state of the Modbus Client Output Bits I/O.
	Automation1SystemDataSignal_ModbusClientOutputBits = 243,
	/// @brief This item returns the current state of the Modbus Client Output Bits Status I/O.
	Automation1SystemDataSignal_ModbusClientOutputBitsStatus = 244,
	/// @brief This item returns the current state of the Modbus Client Output Words Status I/O.
	Automation1SystemDataSignal_ModbusClientOutputWordsStatus = 245,
	/// @brief This item returns the current state of the Modbus Server Input Words I/O.
	Automation1SystemDataSignal_ModbusServerInputWords = 246,
	/// @brief This item returns the current state of the Modbus Server Output Words I/O.
	Automation1SystemDataSignal_ModbusServerOutputWords = 247,
	/// @brief This item returns the current state of the Modbus Server Input Bits I/O.
	Automation1SystemDataSignal_ModbusServerInputBits = 248,
	/// @brief This item returns the current state of the Modbus Server Output Bits I/O.
	Automation1SystemDataSignal_ModbusServerOutputBits = 249,
	/// @brief This item returns the value of a system parameter.
	Automation1SystemDataSignal_SystemParameter = 265,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_ThermoCompSensorTemperature = 305,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_ThermoCompControllingTemperature = 306,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_ThermoCompCompensatingTemperature = 307,
	/// @brief If non-zero, the ThermoComp status word is masked with this value.
	Automation1SystemDataSignal_ThermoCompStatus = 308,
	/// @brief This item returns the value of a global integer.
	Automation1SystemDataSignal_GlobalInteger = 345,
	/// @brief This item returns the mask of axes that we are communicating with.
	Automation1SystemDataSignal_AliveAxesMask = 348,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_SignalLogPointsStored = 377,
	/// @brief This item returns the warning generated during controller initialization, or zero if there is no warning.
	Automation1SystemDataSignal_ControllerInitializationWarning = 379,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_StopWatchTimerMin = 416,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_StopWatchTimerMax = 417,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_StopWatchTimerAvg = 418,
	/// @brief This item indicates if the controller has been configured to run the EtherCAT stack.
	Automation1SystemDataSignal_EthercatEnabled = 428,
	/// @brief This item returns the value of the last system error code to occur in the EtherCAT stack.
	Automation1SystemDataSignal_EthercatError = 429,
	/// @brief This item returns the value of the Tx PDO slot specified.
	Automation1SystemDataSignal_EthercatTxPdo = 430,
	/// @brief This item returns the size of the data in the Tx PDO channel as the number of bytes.
	Automation1SystemDataSignal_EthercatTxPdoSize = 431,
	/// @brief This item returns the value of the Rx PDO slot specified.
	Automation1SystemDataSignal_EthercatRxPdo = 432,
	/// @brief This item returns the size of the data in the Rx PDO channel as the number of bytes.
	Automation1SystemDataSignal_EthercatRxPdoSize = 433,
	/// @brief This item returns the current state of the EtherCAT stack.
	Automation1SystemDataSignal_EthercatState = 437,
	/// @brief This item indicates if the controller has been configured to run the Modbus Client.
	Automation1SystemDataSignal_ModbusClientEnabled = 438,
	/// @brief This item indicates if the controller has been configured to run the Modbus Server.
	Automation1SystemDataSignal_ModbusServerEnabled = 439,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_HyperWireExternalSynchronizationActive = 440,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_HyperWireExternalSynchronizationFrequency = 441,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_HyperWireExternalSynchronizationLagging = 442,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_HyperWireExternalSynchronizationAdjustmentNanoseconds = 443,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_CallbackSlotProcessingState = 453,
	/// @brief This signal is internal. Do not use this signal unless Aerotech personnel instructs you to do so. Aerotech might change or remove this signal without warning.
	Automation1SystemDataSignal_ControllerAssertCount = 457,
} Automation1SystemDataSignal;

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1DATASIGNAL_H_INCLUDED
