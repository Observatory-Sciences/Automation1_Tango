#ifndef AUTOMATION1ENUM_H_INCLUDED
#define AUTOMATION1ENUM_H_INCLUDED

#if defined(_MSC_VER)
	#if defined(AUTOMATION1_CAPI_EXPORT)
		#define AUTOMATION1_CAPI __declspec(dllexport)
	#else
		#define AUTOMATION1_CAPI __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
	#define AUTOMATION1_CAPI __attribute__((visibility ("default")))
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Represents a drive supplied item that can be retrieved from the Automation1 controller.
typedef enum Automation1DriveItem
{
	/// @brief The "Current Feedback" drive based data item.
	Automation1DriveItem_CurrentFeedback = 7,
	/// @brief The "Current Command" drive based data item.
	Automation1DriveItem_CurrentCommand = 8,
	/// @brief The "Analog Input 0" drive based data item.
	Automation1DriveItem_AnalogInput0 = 10,
	/// @brief The "Analog Input 1" drive based data item.
	Automation1DriveItem_AnalogInput1 = 11,
	/// @brief The "Phase A Current Feedback" drive based data item.
	Automation1DriveItem_PhaseACurrentFeedback = 19,
	/// @brief The "Phase B Current Feedback" drive based data item.
	Automation1DriveItem_PhaseBCurrentFeedback = 20,
	/// @brief The "Encoder Sine" drive based data item.
	Automation1DriveItem_EncoderSine = 21,
	/// @brief The "Encoder Cosine" drive based data item.
	Automation1DriveItem_EncoderCosine = 22,
	/// @brief The "Analog Input 2" drive based data item.
	Automation1DriveItem_AnalogInput2 = 23,
	/// @brief The "Analog Input 3" drive based data item.
	Automation1DriveItem_AnalogInput3 = 24,
	/// @brief The "Loop Transmission Before" drive based data item.
	Automation1DriveItem_LoopTransmissionBefore = 25,
	/// @brief The "Loop Transmission After" drive based data item.
	Automation1DriveItem_LoopTransmissionAfter = 26,
	/// @brief The "Zhs Difference" drive based data item.
	Automation1DriveItem_ZhsDifference = 27,
	/// @brief The "Zhs Sum" drive based data item.
	Automation1DriveItem_ZhsSum = 28,
	/// @brief The "Zhs Unfiltered" drive based data item.
	Automation1DriveItem_ZhsUnfiltered = 29,
	/// @brief The "Zhs Filtered" drive based data item.
	Automation1DriveItem_ZhsFiltered = 30,
	/// @brief The "Analog Output 0" drive based data item.
	Automation1DriveItem_AnalogOutput0 = 31,
	/// @brief The "Analog Output 1" drive based data item.
	Automation1DriveItem_AnalogOutput1 = 32,
	/// @brief The "Analog Output 2" drive based data item.
	Automation1DriveItem_AnalogOutput2 = 33,
	/// @brief The "Analog Output 3" drive based data item.
	Automation1DriveItem_AnalogOutput3 = 34,
	/// @brief The "Drive Memory Int32" drive based data item.
	Automation1DriveItem_DriveMemoryInt32 = 35,
	/// @brief The "Drive Memory Float" drive based data item.
	Automation1DriveItem_DriveMemoryFloat = 36,
	/// @brief The "Drive Memory Double" drive based data item.
	Automation1DriveItem_DriveMemoryDouble = 37,
	/// @brief The "Pso Status" drive based data item.
	Automation1DriveItem_PsoStatus = 38,
	/// @brief The "Drive Timer Debug" drive based data item.
	Automation1DriveItem_DriveTimerDebug = 39,
	/// @brief The "Position Feedback Drive" drive based data item.
	Automation1DriveItem_PositionFeedbackDrive = 77,
	/// @brief The "Position Command Drive" drive based data item.
	Automation1DriveItem_PositionCommandDrive = 84,
	/// @brief The "Drive Memory Int16" drive based data item.
	Automation1DriveItem_DriveMemoryInt16 = 125,
	/// @brief The "Drive Memory Int8" drive based data item.
	Automation1DriveItem_DriveMemoryInt8 = 126,
	/// @brief The "Pso Counter 0" drive based data item.
	Automation1DriveItem_PsoCounter0 = 171,
	/// @brief The "Pso Counter 1" drive based data item.
	Automation1DriveItem_PsoCounter1 = 172,
	/// @brief The "Pso Counter 2" drive based data item.
	Automation1DriveItem_PsoCounter2 = 173,
	/// @brief The "Pso Window 0" drive based data item.
	Automation1DriveItem_PsoWindow0 = 174,
	/// @brief The "Pso Window 1" drive based data item.
	Automation1DriveItem_PsoWindow1 = 175,
	/// @brief The "Drive Data Capture Samples" drive based data item.
	Automation1DriveItem_DriveDataCaptureSamples = 176,
	/// @brief The "Position Command Galvo" drive based data item.
	Automation1DriveItem_PositionCommandGalvo = 178,
	/// @brief The "Primary EnDat Absolute Position" drive based data item.
	Automation1DriveItem_PrimaryEnDatAbsolutePosition = 197,
	/// @brief The "Control Effort" drive based data item.
	Automation1DriveItem_ControlEffort = 201,
	/// @brief The "Phase A Voltage Command" drive based data item.
	Automation1DriveItem_PhaseAVoltageCommand = 208,
	/// @brief The "Phase B Voltage Command" drive based data item.
	Automation1DriveItem_PhaseBVoltageCommand = 209,
	/// @brief The "Phase C Voltage Command" drive based data item.
	Automation1DriveItem_PhaseCVoltageCommand = 210,
	/// @brief The "Amplifier Peak Current" drive based data item.
	Automation1DriveItem_AmplifierPeakCurrent = 211,
	/// @brief The "Fpga Version" drive based data item.
	Automation1DriveItem_FpgaVersion = 212,
	/// @brief The "Drive Type Id" drive based data item.
	Automation1DriveItem_DriveTypeId = 213,
	/// @brief The "Pso Window 0 Array Index" drive based data item.
	Automation1DriveItem_PsoWindow0ArrayIndex = 214,
	/// @brief The "Pso Window 1 Array Index" drive based data item.
	Automation1DriveItem_PsoWindow1ArrayIndex = 215,
	/// @brief The "Pso Distance Array Index" drive based data item.
	Automation1DriveItem_PsoDistanceArrayIndex = 216,
	/// @brief The "Amplifier Temperature" drive based data item.
	Automation1DriveItem_AmplifierTemperature = 217,
	/// @brief The "Pso Bit Array Index" drive based data item.
	Automation1DriveItem_PsoBitArrayIndex = 218,
	/// @brief The "Mx Absolute Position" drive based data item.
	Automation1DriveItem_MxAbsolutePosition = 219,
	/// @brief The "Servo Update Rate" drive based data item.
	Automation1DriveItem_ServoUpdateRate = 220,
	/// @brief The "Settling Time" drive based data item.
	Automation1DriveItem_SettlingTime = 221,
	/// @brief The "Internal Error Code" drive based data item.
	Automation1DriveItem_InternalErrorCode = 222,
	/// @brief The "Firmware Version Major" drive based data item.
	Automation1DriveItem_FirmwareVersionMajor = 223,
	/// @brief The "Firmware Version Minor" drive based data item.
	Automation1DriveItem_FirmwareVersionMinor = 224,
	/// @brief The "Firmware Version Patch" drive based data item.
	Automation1DriveItem_FirmwareVersionPatch = 225,
	/// @brief The "Firmware Version Build" drive based data item.
	Automation1DriveItem_FirmwareVersionBuild = 226,
	/// @brief The "Drive Timer Debug Max" drive based data item.
	Automation1DriveItem_DriveTimerDebugMax = 227,
	/// @brief The "Marker Search Distance" drive based data item.
	Automation1DriveItem_MarkerSearchDistance = 228,
	/// @brief The "Position Feedback Galvo" drive based data item.
	Automation1DriveItem_PositionFeedbackGalvo = 234,
	/// @brief The "Latched Marker Position" drive based data item.
	Automation1DriveItem_LatchedMarkerPosition = 236,
	/// @brief The "Primary Biss Absolute Position" drive based data item.
	Automation1DriveItem_PrimaryBissAbsolutePosition = 255,
	/// @brief The "Fault Position Feedback" drive based data item.
	Automation1DriveItem_FaultPositionFeedback = 258,
	/// @brief The "Motor Commutation Angle" drive based data item.
	Automation1DriveItem_MotorCommutationAngle = 259,
	/// @brief The "Expansion Board Option" drive based data item.
	Automation1DriveItem_ExpansionBoardOption = 260,
	/// @brief The "Bus Voltage" drive based data item.
	Automation1DriveItem_BusVoltage = 261,
	/// @brief The "Piezo Voltage Command" drive based data item.
	Automation1DriveItem_PiezoVoltageCommand = 262,
	/// @brief The "Piezo Voltage Feedback" drive based data item.
	Automation1DriveItem_PiezoVoltageFeedback = 263,
	/// @brief The "Time Since Reset" drive based data item.
	Automation1DriveItem_TimeSinceReset = 273,
	/// @brief The "Maximum Voltage" drive based data item.
	Automation1DriveItem_MaximumVoltage = 274,
	/// @brief The "Command Output Type" drive based data item.
	Automation1DriveItem_CommandOutputType = 275,
	/// @brief The "Drive Feedforward Output" drive based data item.
	Automation1DriveItem_DriveFeedforwardOutput = 290,
	/// @brief The "Last Tick Counter" drive based data item.
	Automation1DriveItem_LastTickCounter = 291,
	/// @brief The "Board Revision" drive based data item.
	Automation1DriveItem_BoardRevision = 292,
	/// @brief The "Galvo Laser Output" drive based data item.
	Automation1DriveItem_GalvoLaserOutput = 294,
	/// @brief The "Galvo Laser Power Correction Output" drive based data item.
	Automation1DriveItem_GalvoLaserPowerCorrectionOutput = 299,
	/// @brief The "Capacitance Sensor Raw Position" drive based data item.
	Automation1DriveItem_CapacitanceSensorRawPosition = 300,
	/// @brief The "Position Calibration Galvo" drive based data item.
	Automation1DriveItem_PositionCalibrationGalvo = 304,
	/// @brief The "Bus Voltage Negative" drive based data item.
	Automation1DriveItem_BusVoltageNegative = 325,
	/// @brief The "Processor Temperature" drive based data item.
	Automation1DriveItem_ProcessorTemperature = 326,
	/// @brief The "Internal Error Timestamp" drive based data item.
	Automation1DriveItem_InternalErrorTimestamp = 328,
	/// @brief The "Analog Sensor Input" drive based data item.
	Automation1DriveItem_AnalogSensorInput = 329,
	/// @brief The "Motor Temperature" drive based data item.
	Automation1DriveItem_MotorTemperature = 330,
	/// @brief The "Primary Biss Status" drive based data item.
	Automation1DriveItem_PrimaryBissStatus = 332,
	/// @brief The "Pso External Sync Frequency" drive based data item.
	Automation1DriveItem_PsoExternalSyncFrequency = 337,
	/// @brief The "Encoder Sine Raw" drive based data item.
	Automation1DriveItem_EncoderSineRaw = 346,
	/// @brief The "Encoder Cosine Raw" drive based data item.
	Automation1DriveItem_EncoderCosineRaw = 347,
	/// @brief The "Fpga Temperature" drive based data item.
	Automation1DriveItem_FpgaTemperature = 353,
	/// @brief The "Primary EnDat Status" drive based data item.
	Automation1DriveItem_PrimaryEnDatStatus = 355,
	/// @brief The "Drive Timer High Priority Thread" drive based data item.
	Automation1DriveItem_DriveTimerHighPriorityThread = 356,
	/// @brief The "Drive Timer Low Priority Thread" drive based data item.
	Automation1DriveItem_DriveTimerLowPriorityThread = 357,
	/// @brief The "Drive Timer Low Priority Packet" drive based data item.
	Automation1DriveItem_DriveTimerLowPriorityPacket = 358,
	/// @brief The "Drive Timer Servo Packet" drive based data item.
	Automation1DriveItem_DriveTimerServoPacket = 359,
	/// @brief The "Drive Timer Servo Thread" drive based data item.
	Automation1DriveItem_DriveTimerServoThread = 360,
	/// @brief The "Drive Timer Current Packet" drive based data item.
	Automation1DriveItem_DriveTimerCurrentPacket = 361,
	/// @brief The "Drive Timer Common Core Thread" drive based data item.
	Automation1DriveItem_DriveTimerCommonCoreThread = 362,
	/// @brief The "Drive Timer Servo Core Packet 0" drive based data item.
	Automation1DriveItem_DriveTimerServoCorePacket0 = 363,
	/// @brief The "Drive Timer Servo Core Packet 1" drive based data item.
	Automation1DriveItem_DriveTimerServoCorePacket1 = 364,
	/// @brief The "Multiplier Option" drive based data item.
	Automation1DriveItem_MultiplierOption = 365,
	/// @brief The "Primary Feedback" drive based data item.
	Automation1DriveItem_PrimaryFeedback = 366,
	/// @brief The "Servo Loop Feedback Input 0" drive based data item.
	Automation1DriveItem_ServoLoopFeedbackInput0 = 367,
	/// @brief The "Servo Loop Feedback Input 1" drive based data item.
	Automation1DriveItem_ServoLoopFeedbackInput1 = 368,
	/// @brief The "Fault Subcode" drive based data item.
	Automation1DriveItem_FaultSubcode = 376,
	/// @brief The "Processor Temperature Max" drive based data item.
	Automation1DriveItem_ProcessorTemperatureMax = 378,
	/// @brief The "Drive Timer HyperWire Dma" drive based data item.
	Automation1DriveItem_DriveTimerHyperWireDma = 381,
	/// @brief The "Amplifier Temperature Max" drive based data item.
	Automation1DriveItem_AmplifierTemperatureMax = 382,
	/// @brief The "Auxiliary EnDat Absolute Position" drive based data item.
	Automation1DriveItem_AuxiliaryEnDatAbsolutePosition = 383,
	/// @brief The "Auxiliary EnDat Status" drive based data item.
	Automation1DriveItem_AuxiliaryEnDatStatus = 384,
	/// @brief The "Auxiliary Biss Absolute Position" drive based data item.
	Automation1DriveItem_AuxiliaryBissAbsolutePosition = 385,
	/// @brief The "Auxiliary Biss Status" drive based data item.
	Automation1DriveItem_AuxiliaryBissStatus = 386,
	/// @brief The "Pso Option" drive based data item.
	Automation1DriveItem_PsoOption = 387,
	/// @brief The "Drive Array Size" drive based data item.
	Automation1DriveItem_DriveArraySize = 388,
	/// @brief The "Rated Motor Supply Voltage Option" drive based data item.
	Automation1DriveItem_RatedMotorSupplyVoltageOption = 389,
	/// @brief The "Absolute Encoder Option" drive based data item.
	Automation1DriveItem_AbsoluteEncoderOption = 391,
	/// @brief The "Primary Feedback Status" drive based data item.
	Automation1DriveItem_PrimaryFeedbackStatus = 392,
	/// @brief The "Auxiliary Feedback Status" drive based data item.
	Automation1DriveItem_AuxiliaryFeedbackStatus = 393,
	/// @brief The "Amplifier Status" drive based data item.
	Automation1DriveItem_AmplifierStatus = 394,
	/// @brief The "Latched Cw Limit Position" drive based data item.
	Automation1DriveItem_LatchedCwLimitPosition = 395,
	/// @brief The "Latched Ccw Limit Position" drive based data item.
	Automation1DriveItem_LatchedCcwLimitPosition = 396,
	/// @brief The "Galvo Laser Fpga Transition Delay" drive based data item.
	Automation1DriveItem_GalvoLaserFpgaTransitionDelay = 397,
	/// @brief The "Piezo Accumulated Charge" drive based data item.
	Automation1DriveItem_PiezoAccumulatedCharge = 401,
	/// @brief The "Piezo Charging Time" drive based data item.
	Automation1DriveItem_PiezoChargingTime = 402,
	/// @brief The "Primary Ssi Absolute Position" drive based data item.
	Automation1DriveItem_PrimarySsiAbsolutePosition = 403,
	/// @brief The "Primary Ssi Status" drive based data item.
	Automation1DriveItem_PrimarySsiStatus = 404,
	/// @brief The "Auxiliary Ssi Absolute Position" drive based data item.
	Automation1DriveItem_AuxiliarySsiAbsolutePosition = 405,
	/// @brief The "Auxiliary Ssi Status" drive based data item.
	Automation1DriveItem_AuxiliarySsiStatus = 406,
	/// @brief The "Pso Distance Active Distance" drive based data item.
	Automation1DriveItem_PsoDistanceActiveDistance = 407,
	/// @brief The "Pso Window 0 Active Lower Bound" drive based data item.
	Automation1DriveItem_PsoWindow0ActiveLowerBound = 408,
	/// @brief The "Pso Window 0 Active Upper Bound" drive based data item.
	Automation1DriveItem_PsoWindow0ActiveUpperBound = 409,
	/// @brief The "Pso Window 1 Active Lower Bound" drive based data item.
	Automation1DriveItem_PsoWindow1ActiveLowerBound = 410,
	/// @brief The "Pso Window 1 Active Upper Bound" drive based data item.
	Automation1DriveItem_PsoWindow1ActiveUpperBound = 411,
	/// @brief The "Pso Waveform Active Total Time" drive based data item.
	Automation1DriveItem_PsoWaveformActiveTotalTime = 412,
	/// @brief The "Pso Waveform Active On Time" drive based data item.
	Automation1DriveItem_PsoWaveformActiveOnTime = 413,
	/// @brief The "Pso Waveform Active Pulse Count" drive based data item.
	Automation1DriveItem_PsoWaveformActivePulseCount = 414,
	/// @brief The "Pso Event Active Bit Value" drive based data item.
	Automation1DriveItem_PsoEventActiveBitValue = 415,
} Automation1DriveItem;

/// @brief Represents the type of distance units used for motion.
typedef enum Automation1DistanceUnits
{
	/// @brief Primary units.
	Automation1DistanceUnits_Primary = 0,
	/// @brief Secondary units.
	Automation1DistanceUnits_Secondary = 1,
} Automation1DistanceUnits;

/// @brief Represents the type of time units used for motion.
typedef enum Automation1TimeUnits
{
	/// @brief Feedrates are specified in distance units per second.
	Automation1TimeUnits_Seconds = 0,
	/// @brief Feedrates are specified in distance units per minute.
	Automation1TimeUnits_Minutes = 1,
} Automation1TimeUnits;

/// @brief Represents a motion target mode.
typedef enum Automation1TargetMode
{
	/// @brief Motion target positions are absolute.
	Automation1TargetMode_Incremental = 0,
	/// @brief Motion target positions are relative to the current axis locations.
	Automation1TargetMode_Absolute = 1,
} Automation1TargetMode;

/// @brief Represents a motion waiting mode.
typedef enum Automation1WaitMode
{
	/// @brief Wait for the motion to be done before continuing execution.
	Automation1WaitMode_MotionDone = 1,
	/// @brief Wait for the motion to be done and for the position error to reach a specified value before continuing execution.
	Automation1WaitMode_InPosition = 2,
	/// @brief Wait the minimum quantity of time between motion blocks continuing execution.
	Automation1WaitMode_Auto = 3,
} Automation1WaitMode;

/// @brief Represents the type of normalcy alignment.
typedef enum Automation1NormalcyAlignment
{
	/// @brief Keeps the normalcy axis perpendicular and to the left of the part.
	Automation1NormalcyAlignment_Left = 0,
	/// @brief Keeps the normalcy axis perpendicular and to the right of the part.
	Automation1NormalcyAlignment_Right = 1,
	/// @brief Keeps the normalcy axis at a relative angle to the part.
	Automation1NormalcyAlignment_Relative = 2,
} Automation1NormalcyAlignment;

/// @brief Represents the mode for controlling a laser.
typedef enum Automation1GalvoLaser
{
	/// @brief Manually turns off the laser.
	Automation1GalvoLaser_Off = 0,
	/// @brief Manually turns on the laser.
	Automation1GalvoLaser_On = 1,
	/// @brief Specifies that the laser is automatically controlled.
	Automation1GalvoLaser_Auto = 2,
} Automation1GalvoLaser;

/// @brief Specifies the mode of the wobble pattern.
typedef enum Automation1GalvoWobbleMode
{
	/// @brief The wobble is repeated at a fixed time interval.
	Automation1GalvoWobbleMode_TimeBased = 0,
	/// @brief The wobble is repeated at a fixed vector distance.
	Automation1GalvoWobbleMode_DistanceBased = 1,
} Automation1GalvoWobbleMode;

/// @brief Specifies the type of the wobble pattern.
typedef enum Automation1GalvoWobbleType
{
	/// @brief The pattern uses an ellipse shape.
	Automation1GalvoWobbleType_Ellipse = 0,
	/// @brief The pattern uses a figure 8 shape that is parallel to the vector path.
	Automation1GalvoWobbleType_Figure8Parallel = 1,
	/// @brief The pattern uses a figure 8 shape that is perpendicular to the vector path.
	Automation1GalvoWobbleType_Figure8Perpendicular = 2,
} Automation1GalvoWobbleType;

/// @brief Specifies the motion directions that can generate PSO events.
typedef enum Automation1PsoDistanceAllowedEventDirection
{
	/// @brief PSO events will be generated when the distance counter reaches the configured distance in both directions.
	Automation1PsoDistanceAllowedEventDirection_Both = 0,
	/// @brief PSO events will only be generated when the distance counter reaches the configured distance in the positive direction.
	Automation1PsoDistanceAllowedEventDirection_Positive = 1,
	/// @brief PSO events will only be generated when the distance counter reaches the configured distance in the negative direction.
	Automation1PsoDistanceAllowedEventDirection_Negative = 2,
} Automation1PsoDistanceAllowedEventDirection;

/// @brief Specifies the directions in which exiting the active PSO window will result in the window updating to the next pair of ranges.
typedef enum Automation1PsoWindowUpdateDirection
{
	/// @brief The PSO window range will update when exiting the active window in either direction.
	Automation1PsoWindowUpdateDirection_Both = 0,
	/// @brief The PSO window range will only update when exiting the active window in the positive direction.
	Automation1PsoWindowUpdateDirection_Positive = 1,
	/// @brief The PSO window range will only update when exiting the active window in the negative direction.
	Automation1PsoWindowUpdateDirection_Negative = 2,
} Automation1PsoWindowUpdateDirection;

/// @brief Specifies the conditions that will generate a PSO event when entering or exiting the PSO window.
typedef enum Automation1PsoWindowEventMode
{
	/// @brief An event will not be generated when entering or exiting the window.
	Automation1PsoWindowEventMode_None = 0,
	/// @brief An event will be generated when entering the window.
	Automation1PsoWindowEventMode_Enter = 1,
	/// @brief An event will be generated when exiting the window.
	Automation1PsoWindowEventMode_Exit = 2,
	/// @brief An event will be generated when entering or exiting the window.
	Automation1PsoWindowEventMode_Both = 3,
} Automation1PsoWindowEventMode;

/// @brief Selects the output mode of the PSO waveform module.
typedef enum Automation1PsoWaveformMode
{
	/// @brief Selects a configurable set of pulses as the PSO waveform output.
	Automation1PsoWaveformMode_Pulse = 0,
	/// @brief Selects a configurable PWM output as the PSO waveform output.
	Automation1PsoWaveformMode_Pwm = 1,
	/// @brief Selects a toggling output as the PSO waveform output.
	Automation1PsoWaveformMode_Toggle = 2,
} Automation1PsoWaveformMode;

/// @brief Selects the internal PSO signal to drive onto the active PSO output pin.
typedef enum Automation1PsoOutputSource
{
	/// @brief The PSO output will be active when the PSO waveform output is active.
	Automation1PsoOutputSource_Waveform = 1,
	/// @brief The PSO output will be active when the PSO window output is active.
	Automation1PsoOutputSource_WindowOutput = 2,
	/// @brief The PSO output will be active when the PSO window output is not active.
	Automation1PsoOutputSource_WindowOutputInvert = 3,
	/// @brief The PSO output will be active when the active PSO bit is 1.
	Automation1PsoOutputSource_Bitmap = 4,
} Automation1PsoOutputSource;

/// @brief Represents a type of safe zone.
typedef enum Automation1SafeZoneType
{
	/// @brief Positions will stay outside of the zone.
	Automation1SafeZoneType_NoEnter = 0,
	/// @brief Positions will stay inside the zone.
	Automation1SafeZoneType_NoExit = 1,
	/// @brief Positions will stay outside of the zone and a safe zone axis fault is generated if the safe zone is violated.
	Automation1SafeZoneType_NoEnterAxisFault = 2,
	/// @brief Positions will stay inside the zone and a safe zone axis fault is generated if the safe zone is violated.
	Automation1SafeZoneType_NoExitAxisFault = 3,
} Automation1SafeZoneType;

/// @brief Represents the item to configure for IFOV.
typedef enum Automation1IfovSetupItem
{
	/// @brief Specifies the interpolation that the IFOV algorithm uses to generate motion on the galvo axes and additional axes.
	Automation1IfovSetupItem_InterpolationMode = 0,
	/// @brief Specifies the ramping behavior that the IFOV algorithm uses to decelerate and accelerate the galvo axes and additional axes.
	Automation1IfovSetupItem_TimeScaleRampBehavior = 1,
	/// @brief Specifies the time granularity of the windowing algorithm in milliseconds.
	Automation1IfovSetupItem_TimeGranularity = 2,
} Automation1IfovSetupItem;

/// @brief Specifies the input data source for gearing motion.
typedef enum Automation1GearingSource
{
	/// @brief Use Position Feedback on the leader axis as the source for gearing.
	Automation1GearingSource_PositionFeedback = 0,
	/// @brief Use Position Command on the leader axis as the source for gearing.
	Automation1GearingSource_PositionCommand = 1,
	/// @brief Use Auxiliary Feedback on the leader axis as the source for gearing.
	Automation1GearingSource_AuxiliaryFeedback = 2,
} Automation1GearingSource;

/// @brief Gearing filter configuration option.
typedef enum Automation1GearingFilter
{
	/// @brief No filter is applied to the gearing motion.
	Automation1GearingFilter_None = 1,
	/// @brief Low-pass filter is applied to the gearing motion.
	Automation1GearingFilter_Filtered = 2,
} Automation1GearingFilter;

/// @brief Units for the camming table values.
typedef enum Automation1CammingUnits
{
	/// @brief Primary units.
	Automation1CammingUnits_Primary = 0,
	/// @brief Secondary units.
	Automation1CammingUnits_Secondary = 1,
	/// @brief Values in counts.
	Automation1CammingUnits_Counts = 2,
} Automation1CammingUnits;

/// @brief Interpolation mode for camming.
typedef enum Automation1CammingInterpolation
{
	/// @brief Linear interpolation.
	Automation1CammingInterpolation_Linear = 0,
	/// @brief Cubic interpolation.
	Automation1CammingInterpolation_Cubic = 1,
} Automation1CammingInterpolation;

/// @brief Wrapping mode for the camming table.
typedef enum Automation1CammingWrapping
{
	/// @brief Table leader axis values will not wrap. This is the default controller behavior and is correct for most applications.
	Automation1CammingWrapping_NoWrap = 0,
	/// @brief Table leader axis values wrap creating a cyclic array. This is useful for rotary applications where the first position is 0 degrees and the final position is 360 degrees.
	Automation1CammingWrapping_Wrap = 1,
} Automation1CammingWrapping;

/// @brief Specifies the input data source for camming motion.
typedef enum Automation1CammingSource
{
	/// @brief Use Position Feedback on the leader axis as the source for camming.
	Automation1CammingSource_PositionFeedback = 0,
	/// @brief Use Position Command on the leader axis as the source for camming.
	Automation1CammingSource_PositionCommand = 1,
	/// @brief Use Auxiliary Feedback on the leader axis as the source for camming.
	Automation1CammingSource_AuxiliaryFeedback = 2,
} Automation1CammingSource;

/// @brief Specifies the output signal to generate on the camming follower axis. Also specifies the leader axis and follower axis synchronization to use when camming is enabled.
typedef enum Automation1CammingOutput
{
	/// @brief The follower axis will operate in position-based relative synchronization mode. All camming table values for the follower axis are treated as absolute positions, but the follower axis will remain at the current position when camming is enabled. An offset will be applied to all follower axis positions in the camming table, and the offset is computed based on the current leader axis position and current follower axis position.
	Automation1CammingOutput_RelativePosition = 1,
	/// @brief The follower axis will operate in position-based absolute synchronization mode. All camming table values for the follower axis are treated as absolute positions, and the controller will perform an alignment move on the follower axis when camming is enabled. The controller moves the follower axis to the position specified in the camming table based on the current leader axis position.
	Automation1CammingOutput_AbsolutePosition = 2,
	/// @brief The follower axis will operate in velocity mode. All camming table values for the follower axis are treated as velocities, but the follower axis will remain at the current velocity when camming is enabled. An offset will be applied to all follower axis velocities in the camming table, and the offset is computed based on the current leader axis position and current follower axis velocity.
	Automation1CammingOutput_Velocity = 3,
} Automation1CammingOutput;

/// @brief Type of servo loop gain.
typedef enum Automation1ServoLoopGain
{
	/// @brief Overall servo.
	Automation1ServoLoopGain_GainK = 0,
	/// @brief Velocity loop integral.
	Automation1ServoLoopGain_GainKiv = 1,
	/// @brief Position loop integral.
	Automation1ServoLoopGain_GainKip = 2,
	/// @brief Position scaling.
	Automation1ServoLoopGain_GainKv = 3,
	/// @brief Velocity loop proportional.
	Automation1ServoLoopGain_GainKpv = 4,
	/// @brief Position loop pure integral.
	Automation1ServoLoopGain_GainKip2 = 5,
	/// @brief Parallel integral.
	Automation1ServoLoopGain_GainKsi1 = 6,
	/// @brief Parallel integral.
	Automation1ServoLoopGain_GainKsi2 = 7,
	/// @brief Dual loop scaling.
	Automation1ServoLoopGain_GainAlpha = 8,
} Automation1ServoLoopGain;

/// @brief Type of feedforward gain.
typedef enum Automation1FeedforwardGain
{
	/// @brief Acceleration.
	Automation1FeedforwardGain_GainAff = 0,
	/// @brief Velocity.
	Automation1FeedforwardGain_GainVff = 1,
	/// @brief Jerk.
	Automation1FeedforwardGain_GainJff = 2,
	/// @brief Position.
	Automation1FeedforwardGain_GainPff = 3,
} Automation1FeedforwardGain;

/// @brief The source used as the output channel for encoder echoing.
typedef enum Automation1EncoderOutputChannel
{
	/// @brief Auxiliary channel.
	Automation1EncoderOutputChannel_AuxiliaryEncoder = 0,
	/// @brief Sync Port A channel.
	Automation1EncoderOutputChannel_SyncPortA = 1,
	/// @brief Sync Port B channel.
	Automation1EncoderOutputChannel_SyncPortB = 2,
	/// @brief High Speed Output channel.
	Automation1EncoderOutputChannel_HighSpeedOutputs = 3,
} Automation1EncoderOutputChannel;

/// @brief The source used as the input channel for encoder echoing.
typedef enum Automation1EncoderInputChannel
{
	/// @brief Primary channel.
	Automation1EncoderInputChannel_PrimaryEncoder = 0,
	/// @brief Auxiliary channel.
	Automation1EncoderInputChannel_AuxiliaryEncoder = 1,
	/// @brief Sync Port A channel.
	Automation1EncoderInputChannel_SyncPortA = 2,
	/// @brief Sync Port B channel.
	Automation1EncoderInputChannel_SyncPortB = 3,
	/// @brief Pulse Stream channel.
	Automation1EncoderInputChannel_PulseStream = 4,
} Automation1EncoderInputChannel;

/// @brief The mode used for encoder echoing.
typedef enum Automation1EncoderOutputMode
{
	/// @brief Quadrature mode.
	Automation1EncoderOutputMode_Quadrature = 0,
} Automation1EncoderOutputMode;

/// @brief Specifies the item that will be stored when the Drive Data Capture trigger occurs.
typedef enum Automation1DriveDataCaptureInput
{
	/// @brief Position Command.
	Automation1DriveDataCaptureInput_PositionCommand = 0,
	/// @brief Primary Feedback.
	Automation1DriveDataCaptureInput_PrimaryFeedback = 1,
	/// @brief Auxiliary Feedback.
	Automation1DriveDataCaptureInput_AuxiliaryFeedback = 2,
	/// @brief Analog Input 0.
	Automation1DriveDataCaptureInput_AnalogInput0 = 3,
	/// @brief Analog Input 1.
	Automation1DriveDataCaptureInput_AnalogInput1 = 4,
	/// @brief Analog Input 2.
	Automation1DriveDataCaptureInput_AnalogInput2 = 5,
	/// @brief Analog Input 3.
	Automation1DriveDataCaptureInput_AnalogInput3 = 6,
} Automation1DriveDataCaptureInput;

/// @brief Specifies the event that Drive Data Capture uses to trigger a capture of the configured source signal.
typedef enum Automation1DriveDataCaptureTrigger
{
	/// @brief PSO output rising edge.
	Automation1DriveDataCaptureTrigger_PsoOutput = 0,
	/// @brief PSO event.
	Automation1DriveDataCaptureTrigger_PsoEvent = 1,
	/// @brief High Speed Input 0 rising edge.
	Automation1DriveDataCaptureTrigger_HighSpeedInput0RisingEdge = 2,
	/// @brief High Speed Input 0 falling edge.
	Automation1DriveDataCaptureTrigger_HighSpeedInput0FallingEdge = 3,
	/// @brief High Speed Input 1 rising edge.
	Automation1DriveDataCaptureTrigger_HighSpeedInput1RisingEdge = 4,
	/// @brief High Speed Input 1 falling edge.
	Automation1DriveDataCaptureTrigger_HighSpeedInput1FallingEdge = 5,
} Automation1DriveDataCaptureTrigger;

/// @brief Specifies the type of drive array feature to use.
typedef enum Automation1DriveArrayType
{
	/// @brief 32-bit floating-point values.
	Automation1DriveArrayType_Float32 = 0,
	/// @brief 64-bit floating-point values.
	Automation1DriveArrayType_Float64 = 1,
	/// @brief 32-bit unsigned integer values.
	Automation1DriveArrayType_UInt32 = 2,
	/// @brief 64-bit unsigned integer values.
	Automation1DriveArrayType_UInt64 = 3,
	/// @brief 32-bit signed integer values.
	Automation1DriveArrayType_Int32 = 4,
	/// @brief 64-bit signed integer values.
	Automation1DriveArrayType_Int64 = 5,
	/// @brief 32-bit floating-point voltages.
	Automation1DriveArrayType_AnalogOutputVoltages = 6,
	/// @brief 64-bit floating-point counts.
	Automation1DriveArrayType_DataCapturePositions = 7,
	/// @brief 32-bit unsigned integer bitmaps.
	Automation1DriveArrayType_PsoBitmapBits = 8,
	/// @brief 32-bit unsigned integer counts.
	Automation1DriveArrayType_PsoDistanceEventDistances = 9,
	/// @brief 32-bit floating-point microseconds.
	Automation1DriveArrayType_PsoPulseTimes = 10,
	/// @brief 32-bit unsigned integers.
	Automation1DriveArrayType_PsoPulseCounts = 11,
	/// @brief 32-bit signed integer counts.
	Automation1DriveArrayType_PsoWindowRanges = 12,
} Automation1DriveArrayType;

/// @brief Specifies the PSO distance input settings for each drive.
typedef enum Automation1PsoDistanceInput
{
	/// @brief GL4 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_GL4PrimaryFeedbackAxis1 = 0,
	/// @brief GL4 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_GL4PrimaryFeedbackAxis2 = 1,
	/// @brief GL4 Primary Feedback Axis 1 with IFOV input.
	Automation1PsoDistanceInput_GL4IfovFeedbackAxis1 = 2,
	/// @brief GL4 Primary Feedback Axis 2 with IFOV input.
	Automation1PsoDistanceInput_GL4IfovFeedbackAxis2 = 3,
	/// @brief GL4 Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_GL4AuxiliaryFeedbackAxis1 = 4,
	/// @brief GL4 Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_GL4AuxiliaryFeedbackAxis2 = 5,
	/// @brief GL4 Sync Port A.
	Automation1PsoDistanceInput_GL4SyncPortA = 6,
	/// @brief GL4 Sync Port B.
	Automation1PsoDistanceInput_GL4SyncPortB = 7,
	/// @brief GL4 Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_GL4DrivePulseStreamAxis1 = 14,
	/// @brief GL4 Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_GL4DrivePulseStreamAxis2 = 15,
	/// @brief XL4s Primary Feedback.
	Automation1PsoDistanceInput_XL4sPrimaryFeedback = 0,
	/// @brief XL4s Auxiliary Feedback.
	Automation1PsoDistanceInput_XL4sAuxiliaryFeedback = 4,
	/// @brief XL4s Sync Port A.
	Automation1PsoDistanceInput_XL4sSyncPortA = 6,
	/// @brief XL4s Sync Port B.
	Automation1PsoDistanceInput_XL4sSyncPortB = 7,
	/// @brief XL4s Drive Pulse Stream.
	Automation1PsoDistanceInput_XL4sDrivePulseStream = 14,
	/// @brief XR3 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis1 = 0,
	/// @brief XR3 Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis1 = 1,
	/// @brief XR3 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis2 = 2,
	/// @brief XR3 Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis2 = 3,
	/// @brief XR3 Primary Feedback Axis 3.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis3 = 4,
	/// @brief XR3 Auxiliary Feedback Axis 3.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis3 = 5,
	/// @brief XR3 Primary Feedback Axis 4.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis4 = 6,
	/// @brief XR3 Auxiliary Feedback Axis 4.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis4 = 7,
	/// @brief XR3 Primary Feedback Axis 5.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis5 = 8,
	/// @brief XR3 Auxiliary Feedback Axis 5.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis5 = 9,
	/// @brief XR3 Primary Feedback Axis 6.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis6 = 10,
	/// @brief XR3 Auxiliary Feedback Axis 6.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis6 = 11,
	/// @brief XR3 Sync Port A.
	Automation1PsoDistanceInput_XR3SyncPortA = 12,
	/// @brief XR3 Sync Port B.
	Automation1PsoDistanceInput_XR3SyncPortB = 13,
	/// @brief XR3 Drive Pulse Stream.
	Automation1PsoDistanceInput_XR3DrivePulseStream = 14,
	/// @brief XC4 Primary Feedback.
	Automation1PsoDistanceInput_XC4PrimaryFeedback = 0,
	/// @brief XC4 Auxiliary Feedback.
	Automation1PsoDistanceInput_XC4AuxiliaryFeedback = 1,
	/// @brief XC4 Sync Port A.
	Automation1PsoDistanceInput_XC4SyncPortA = 2,
	/// @brief XC4 Sync Port B.
	Automation1PsoDistanceInput_XC4SyncPortB = 3,
	/// @brief XC4 Drive Pulse Stream.
	Automation1PsoDistanceInput_XC4DrivePulseStream = 14,
	/// @brief XC4e Primary Feedback.
	Automation1PsoDistanceInput_XC4ePrimaryFeedback = 0,
	/// @brief XC4e Auxiliary Feedback.
	Automation1PsoDistanceInput_XC4eAuxiliaryFeedback = 1,
	/// @brief XC4e Sync Port A.
	Automation1PsoDistanceInput_XC4eSyncPortA = 2,
	/// @brief XC4e Sync Port B.
	Automation1PsoDistanceInput_XC4eSyncPortB = 3,
	/// @brief XC4e Drive Pulse Stream.
	Automation1PsoDistanceInput_XC4eDrivePulseStream = 14,
	/// @brief XC6e Primary Feedback.
	Automation1PsoDistanceInput_XC6ePrimaryFeedback = 0,
	/// @brief XC6e Auxiliary Feedback.
	Automation1PsoDistanceInput_XC6eAuxiliaryFeedback = 1,
	/// @brief XC6e Sync Port A.
	Automation1PsoDistanceInput_XC6eSyncPortA = 2,
	/// @brief XC6e Sync Port B.
	Automation1PsoDistanceInput_XC6eSyncPortB = 3,
	/// @brief XC6e Drive Pulse Stream.
	Automation1PsoDistanceInput_XC6eDrivePulseStream = 14,
	/// @brief XL5e Primary Feedback.
	Automation1PsoDistanceInput_XL5ePrimaryFeedback = 0,
	/// @brief XL5e Auxiliary Feedback.
	Automation1PsoDistanceInput_XL5eAuxiliaryFeedback = 1,
	/// @brief XL5e Sync Port A.
	Automation1PsoDistanceInput_XL5eSyncPortA = 2,
	/// @brief XL5e Sync Port B.
	Automation1PsoDistanceInput_XL5eSyncPortB = 3,
	/// @brief XL5e Drive Pulse Stream.
	Automation1PsoDistanceInput_XL5eDrivePulseStream = 14,
	/// @brief SI4 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_SI4PrimaryFeedbackAxis1 = 0,
	/// @brief SI4 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_SI4PrimaryFeedbackAxis2 = 1,
	/// @brief SI4 Primary Feedback Axis 3.
	Automation1PsoDistanceInput_SI4PrimaryFeedbackAxis3 = 2,
	/// @brief SI4 Primary Feedback Axis 4.
	Automation1PsoDistanceInput_SI4PrimaryFeedbackAxis4 = 3,
	/// @brief SI4 Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_SI4DrivePulseStreamAxis1 = 14,
	/// @brief SI4 Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_SI4DrivePulseStreamAxis2 = 15,
	/// @brief SI4 Drive Pulse Stream Axis 3.
	Automation1PsoDistanceInput_SI4DrivePulseStreamAxis3 = 16,
	/// @brief SI4 Drive Pulse Stream Axis 4.
	Automation1PsoDistanceInput_SI4DrivePulseStreamAxis4 = 17,
	/// @brief XC2 Primary Feedback.
	Automation1PsoDistanceInput_XC2PrimaryFeedback = 0,
	/// @brief XC2 Auxiliary Feedback.
	Automation1PsoDistanceInput_XC2AuxiliaryFeedback = 1,
	/// @brief XC2 Drive Pulse Stream.
	Automation1PsoDistanceInput_XC2DrivePulseStream = 14,
	/// @brief XC2e Primary Feedback.
	Automation1PsoDistanceInput_XC2ePrimaryFeedback = 0,
	/// @brief XC2e Auxiliary Feedback.
	Automation1PsoDistanceInput_XC2eAuxiliaryFeedback = 1,
	/// @brief XC2e Drive Pulse Stream.
	Automation1PsoDistanceInput_XC2eDrivePulseStream = 14,
	/// @brief XL2e Primary Feedback.
	Automation1PsoDistanceInput_XL2ePrimaryFeedback = 0,
	/// @brief XL2e Auxiliary Feedback.
	Automation1PsoDistanceInput_XL2eAuxiliaryFeedback = 1,
	/// @brief XL2e Sync Port A.
	Automation1PsoDistanceInput_XL2eSyncPortA = 2,
	/// @brief XL2e Sync Port B.
	Automation1PsoDistanceInput_XL2eSyncPortB = 3,
	/// @brief XL2e Drive Pulse Stream.
	Automation1PsoDistanceInput_XL2eDrivePulseStream = 14,
	/// @brief XI4 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_XI4PrimaryFeedbackAxis1 = 0,
	/// @brief XI4 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_XI4PrimaryFeedbackAxis2 = 1,
	/// @brief XI4 Primary Feedback Axis 3.
	Automation1PsoDistanceInput_XI4PrimaryFeedbackAxis3 = 2,
	/// @brief XI4 Primary Feedback Axis 4.
	Automation1PsoDistanceInput_XI4PrimaryFeedbackAxis4 = 3,
	/// @brief XI4 Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedback1 = 4,
	/// @brief XI4 Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedback2 = 5,
	/// @brief XI4 Auxiliary Feedback Axis 3.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedback3 = 6,
	/// @brief XI4 Auxiliary Feedback Axis 4.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedback4 = 7,
	/// @brief XI4 Sync Port A.
	Automation1PsoDistanceInput_XI4SyncPortA = 8,
	/// @brief XI4 Sync Port B.
	Automation1PsoDistanceInput_XI4SyncPortB = 9,
	/// @brief XI4 Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_XI4DrivePulseStreamAxis1 = 14,
	/// @brief XI4 Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_XI4DrivePulseStreamAxis2 = 15,
	/// @brief XI4 Drive Pulse Stream Axis 3.
	Automation1PsoDistanceInput_XI4DrivePulseStreamAxis3 = 16,
	/// @brief XI4 Drive Pulse Stream Axis 4.
	Automation1PsoDistanceInput_XI4DrivePulseStreamAxis4 = 17,
	/// @brief iXC4 Primary Feedback.
	Automation1PsoDistanceInput_iXC4PrimaryFeedback = 0,
	/// @brief iXC4 Auxiliary Feedback.
	Automation1PsoDistanceInput_iXC4AuxiliaryFeedback = 1,
	/// @brief iXC4 Sync Port A.
	Automation1PsoDistanceInput_iXC4SyncPortA = 2,
	/// @brief iXC4 Sync Port B.
	Automation1PsoDistanceInput_iXC4SyncPortB = 3,
	/// @brief iXC4 Drive Pulse Stream.
	Automation1PsoDistanceInput_iXC4DrivePulseStream = 14,
	/// @brief iXC4e Primary Feedback.
	Automation1PsoDistanceInput_iXC4ePrimaryFeedback = 0,
	/// @brief iXC4e Auxiliary Feedback.
	Automation1PsoDistanceInput_iXC4eAuxiliaryFeedback = 1,
	/// @brief iXC4e Sync Port A.
	Automation1PsoDistanceInput_iXC4eSyncPortA = 2,
	/// @brief iXC4e Sync Port B.
	Automation1PsoDistanceInput_iXC4eSyncPortB = 3,
	/// @brief iXC4e Drive Pulse Stream.
	Automation1PsoDistanceInput_iXC4eDrivePulseStream = 14,
	/// @brief iXC6e Primary Feedback.
	Automation1PsoDistanceInput_iXC6ePrimaryFeedback = 0,
	/// @brief iXC6e Auxiliary Feedback.
	Automation1PsoDistanceInput_iXC6eAuxiliaryFeedback = 1,
	/// @brief iXC6e Sync Port A.
	Automation1PsoDistanceInput_iXC6eSyncPortA = 2,
	/// @brief iXC6e Sync Port B.
	Automation1PsoDistanceInput_iXC6eSyncPortB = 3,
	/// @brief iXC6e Drive Pulse Stream.
	Automation1PsoDistanceInput_iXC6eDrivePulseStream = 14,
	/// @brief iXL5e Primary Feedback.
	Automation1PsoDistanceInput_iXL5ePrimaryFeedback = 0,
	/// @brief iXL5e Auxiliary Feedback.
	Automation1PsoDistanceInput_iXL5eAuxiliaryFeedback = 1,
	/// @brief iXL5e Sync Port A.
	Automation1PsoDistanceInput_iXL5eSyncPortA = 2,
	/// @brief iXL5e Sync Port B.
	Automation1PsoDistanceInput_iXL5eSyncPortB = 3,
	/// @brief iXL5e Drive Pulse Stream.
	Automation1PsoDistanceInput_iXL5eDrivePulseStream = 14,
	/// @brief iXR3 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis1 = 0,
	/// @brief iXR3 Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis1 = 1,
	/// @brief iXR3 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis2 = 2,
	/// @brief iXR3 Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis2 = 3,
	/// @brief iXR3 Primary Feedback Axis 3.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis3 = 4,
	/// @brief iXR3 Auxiliary Feedback Axis 3.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis3 = 5,
	/// @brief iXR3 Primary Feedback Axis 4.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis4 = 6,
	/// @brief iXR3 Auxiliary Feedback Axis 4.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis4 = 7,
	/// @brief iXR3 Primary Feedback Axis 5.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis5 = 8,
	/// @brief iXR3 Auxiliary Feedback Axis 5.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis5 = 9,
	/// @brief iXR3 Primary Feedback Axis 6.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis6 = 10,
	/// @brief iXR3 Auxiliary Feedback Axis 6.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis6 = 11,
	/// @brief iXR3 Sync Port A.
	Automation1PsoDistanceInput_iXR3SyncPortA = 12,
	/// @brief iXR3 Sync Port B.
	Automation1PsoDistanceInput_iXR3SyncPortB = 13,
	/// @brief iXR3 Drive Pulse Stream.
	Automation1PsoDistanceInput_iXR3DrivePulseStream = 14,
} Automation1PsoDistanceInput;

/// @brief Specifies the PSO window input settings for each drive.
typedef enum Automation1PsoWindowInput
{
	/// @brief GL4 Primary Feedback Axis 1.
	Automation1PsoWindowInput_GL4PrimaryFeedbackAxis1 = 0,
	/// @brief GL4 Primary Feedback Axis 2.
	Automation1PsoWindowInput_GL4PrimaryFeedbackAxis2 = 1,
	/// @brief GL4 Primary Feedback Axis 1 with IFOV input.
	Automation1PsoWindowInput_GL4IfovFeedbackAxis1 = 2,
	/// @brief GL4 Primary Feedback Axis 2 with IFOV input.
	Automation1PsoWindowInput_GL4IfovFeedbackAxis2 = 3,
	/// @brief GL4 Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_GL4AuxiliaryFeedbackAxis1 = 4,
	/// @brief GL4 Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_GL4AuxiliaryFeedbackAxis2 = 5,
	/// @brief GL4 Sync Port A.
	Automation1PsoWindowInput_GL4SyncPortA = 6,
	/// @brief GL4 Sync Port B.
	Automation1PsoWindowInput_GL4SyncPortB = 7,
	/// @brief GL4 Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_GL4DrivePulseStreamAxis1 = 14,
	/// @brief GL4 Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_GL4DrivePulseStreamAxis2 = 15,
	/// @brief XL4s Primary Feedback.
	Automation1PsoWindowInput_XL4sPrimaryFeedback = 0,
	/// @brief XL4s Auxiliary Feedback.
	Automation1PsoWindowInput_XL4sAuxiliaryFeedback = 4,
	/// @brief XL4s Sync Port A.
	Automation1PsoWindowInput_XL4sSyncPortA = 6,
	/// @brief XL4s Sync Port B.
	Automation1PsoWindowInput_XL4sSyncPortB = 7,
	/// @brief XL4s Drive Pulse Stream.
	Automation1PsoWindowInput_XL4sDrivePulseStream = 14,
	/// @brief XR3 Primary Feedback Axis 1.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis1 = 0,
	/// @brief XR3 Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis1 = 1,
	/// @brief XR3 Primary Feedback Axis 2.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis2 = 2,
	/// @brief XR3 Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis2 = 3,
	/// @brief XR3 Primary Feedback Axis 3.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis3 = 4,
	/// @brief XR3 Auxiliary Feedback Axis 3.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis3 = 5,
	/// @brief XR3 Primary Feedback Axis 4.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis4 = 6,
	/// @brief XR3 Auxiliary Feedback Axis 4.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis4 = 7,
	/// @brief XR3 Primary Feedback Axis 5.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis5 = 8,
	/// @brief XR3 Auxiliary Feedback Axis 5.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis5 = 9,
	/// @brief XR3 Primary Feedback Axis 6.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis6 = 10,
	/// @brief XR3 Auxiliary Feedback Axis 6.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis6 = 11,
	/// @brief XR3 Sync Port A.
	Automation1PsoWindowInput_XR3SyncPortA = 12,
	/// @brief XR3 Sync Port B.
	Automation1PsoWindowInput_XR3SyncPortB = 13,
	/// @brief XR3 Drive Pulse Stream.
	Automation1PsoWindowInput_XR3DrivePulseStream = 14,
	/// @brief XC4 Primary Feedback.
	Automation1PsoWindowInput_XC4PrimaryFeedback = 0,
	/// @brief XC4 Auxiliary Feedback.
	Automation1PsoWindowInput_XC4AuxiliaryFeedback = 1,
	/// @brief XC4 Sync Port A.
	Automation1PsoWindowInput_XC4SyncPortA = 2,
	/// @brief XC4 Sync Port B.
	Automation1PsoWindowInput_XC4SyncPortB = 3,
	/// @brief XC4 Drive Pulse Stream.
	Automation1PsoWindowInput_XC4DrivePulseStream = 14,
	/// @brief XC4e Primary Feedback.
	Automation1PsoWindowInput_XC4ePrimaryFeedback = 0,
	/// @brief XC4e Auxiliary Feedback.
	Automation1PsoWindowInput_XC4eAuxiliaryFeedback = 1,
	/// @brief XC4e Sync Port A.
	Automation1PsoWindowInput_XC4eSyncPortA = 2,
	/// @brief XC4e Sync Port B.
	Automation1PsoWindowInput_XC4eSyncPortB = 3,
	/// @brief XC4e Drive Pulse Stream.
	Automation1PsoWindowInput_XC4eDrivePulseStream = 14,
	/// @brief XC6e Primary Feedback.
	Automation1PsoWindowInput_XC6ePrimaryFeedback = 0,
	/// @brief XC6e Auxiliary Feedback.
	Automation1PsoWindowInput_XC6eAuxiliaryFeedback = 1,
	/// @brief XC6e Sync Port A.
	Automation1PsoWindowInput_XC6eSyncPortA = 2,
	/// @brief XC6e Sync Port B.
	Automation1PsoWindowInput_XC6eSyncPortB = 3,
	/// @brief XC6e Drive Pulse Stream.
	Automation1PsoWindowInput_XC6eDrivePulseStream = 14,
	/// @brief XL5e Primary Feedback.
	Automation1PsoWindowInput_XL5ePrimaryFeedback = 0,
	/// @brief XL5e Auxiliary Feedback.
	Automation1PsoWindowInput_XL5eAuxiliaryFeedback = 1,
	/// @brief XL5e Sync Port A.
	Automation1PsoWindowInput_XL5eSyncPortA = 2,
	/// @brief XL5e Sync Port B.
	Automation1PsoWindowInput_XL5eSyncPortB = 3,
	/// @brief XL5e Drive Pulse Stream.
	Automation1PsoWindowInput_XL5eDrivePulseStream = 14,
	/// @brief SI4 Primary Feedback Axis 1.
	Automation1PsoWindowInput_SI4PrimaryFeedbackAxis1 = 0,
	/// @brief SI4 Primary Feedback Axis 2.
	Automation1PsoWindowInput_SI4PrimaryFeedbackAxis2 = 1,
	/// @brief SI4 Primary Feedback Axis 3.
	Automation1PsoWindowInput_SI4PrimaryFeedbackAxis3 = 2,
	/// @brief SI4 Primary Feedback Axis 4.
	Automation1PsoWindowInput_SI4PrimaryFeedbackAxis4 = 3,
	/// @brief SI4 Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_SI4DrivePulseStreamAxis1 = 14,
	/// @brief SI4 Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_SI4DrivePulseStreamAxis2 = 15,
	/// @brief SI4 Drive Pulse Stream Axis 3.
	Automation1PsoWindowInput_SI4DrivePulseStreamAxis3 = 16,
	/// @brief SI4 Drive Pulse Stream Axis 4.
	Automation1PsoWindowInput_SI4DrivePulseStreamAxis4 = 17,
	/// @brief XC2 Primary Feedback.
	Automation1PsoWindowInput_XC2PrimaryFeedback = 0,
	/// @brief XC2 Auxiliary Feedback.
	Automation1PsoWindowInput_XC2AuxiliaryFeedback = 1,
	/// @brief XC2 Drive Pulse Stream.
	Automation1PsoWindowInput_XC2DrivePulseStream = 14,
	/// @brief XC2e Primary Feedback.
	Automation1PsoWindowInput_XC2ePrimaryFeedback = 0,
	/// @brief XC2e Auxiliary Feedback.
	Automation1PsoWindowInput_XC2eAuxiliaryFeedback = 1,
	/// @brief XC2e Drive Pulse Stream.
	Automation1PsoWindowInput_XC2eDrivePulseStream = 14,
	/// @brief XL2e Primary Feedback.
	Automation1PsoWindowInput_XL2ePrimaryFeedback = 0,
	/// @brief XL2e Auxiliary Feedback.
	Automation1PsoWindowInput_XL2eAuxiliaryFeedback = 1,
	/// @brief XL2e Sync Port A.
	Automation1PsoWindowInput_XL2eSyncPortA = 2,
	/// @brief XL2e Sync Port B.
	Automation1PsoWindowInput_XL2eSyncPortB = 3,
	/// @brief XL2e Drive Pulse Stream.
	Automation1PsoWindowInput_XL2eDrivePulseStream = 14,
	/// @brief XI4 Primary Feedback Axis 1.
	Automation1PsoWindowInput_XI4PrimaryFeedbackAxis1 = 0,
	/// @brief XI4 Primary Feedback Axis 2.
	Automation1PsoWindowInput_XI4PrimaryFeedbackAxis2 = 1,
	/// @brief XI4 Primary Feedback Axis 3.
	Automation1PsoWindowInput_XI4PrimaryFeedbackAxis3 = 2,
	/// @brief XI4 Primary Feedback Axis 4.
	Automation1PsoWindowInput_XI4PrimaryFeedbackAxis4 = 3,
	/// @brief XI4 Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_XI4AuxiliaryFeedback1 = 4,
	/// @brief XI4 Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_XI4AuxiliaryFeedback2 = 5,
	/// @brief XI4 Auxiliary Feedback Axis 3.
	Automation1PsoWindowInput_XI4AuxiliaryFeedback3 = 6,
	/// @brief XI4 Auxiliary Feedback Axis 4.
	Automation1PsoWindowInput_XI4AuxiliaryFeedback4 = 7,
	/// @brief XI4 Sync Port A.
	Automation1PsoWindowInput_XI4SyncPortA = 8,
	/// @brief XI4 Sync Port B.
	Automation1PsoWindowInput_XI4SyncPortB = 9,
	/// @brief XI4 Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_XI4DrivePulseStreamAxis1 = 14,
	/// @brief XI4 Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_XI4DrivePulseStreamAxis2 = 15,
	/// @brief XI4 Drive Pulse Stream Axis 3.
	Automation1PsoWindowInput_XI4DrivePulseStreamAxis3 = 16,
	/// @brief XI4 Drive Pulse Stream Axis 4.
	Automation1PsoWindowInput_XI4DrivePulseStreamAxis4 = 17,
	/// @brief iXC4 Primary Feedback.
	Automation1PsoWindowInput_iXC4PrimaryFeedback = 0,
	/// @brief iXC4 Auxiliary Feedback.
	Automation1PsoWindowInput_iXC4AuxiliaryFeedback = 1,
	/// @brief iXC4 Sync Port A.
	Automation1PsoWindowInput_iXC4SyncPortA = 2,
	/// @brief iXC4 Sync Port B.
	Automation1PsoWindowInput_iXC4SyncPortB = 3,
	/// @brief iXC4 Drive Pulse Stream.
	Automation1PsoWindowInput_iXC4DrivePulseStream = 14,
	/// @brief iXC4e Primary Feedback.
	Automation1PsoWindowInput_iXC4ePrimaryFeedback = 0,
	/// @brief iXC4e Auxiliary Feedback.
	Automation1PsoWindowInput_iXC4eAuxiliaryFeedback = 1,
	/// @brief iXC4e Sync Port A.
	Automation1PsoWindowInput_iXC4eSyncPortA = 2,
	/// @brief iXC4e Sync Port B.
	Automation1PsoWindowInput_iXC4eSyncPortB = 3,
	/// @brief iXC4e Drive Pulse Stream.
	Automation1PsoWindowInput_iXC4eDrivePulseStream = 14,
	/// @brief iXC6e Primary Feedback.
	Automation1PsoWindowInput_iXC6ePrimaryFeedback = 0,
	/// @brief iXC6e Auxiliary Feedback.
	Automation1PsoWindowInput_iXC6eAuxiliaryFeedback = 1,
	/// @brief iXC6e Sync Port A.
	Automation1PsoWindowInput_iXC6eSyncPortA = 2,
	/// @brief iXC6e Sync Port B.
	Automation1PsoWindowInput_iXC6eSyncPortB = 3,
	/// @brief iXC6e Drive Pulse Stream.
	Automation1PsoWindowInput_iXC6eDrivePulseStream = 14,
	/// @brief iXL5e Primary Feedback.
	Automation1PsoWindowInput_iXL5ePrimaryFeedback = 0,
	/// @brief iXL5e Auxiliary Feedback.
	Automation1PsoWindowInput_iXL5eAuxiliaryFeedback = 1,
	/// @brief iXL5e Sync Port A.
	Automation1PsoWindowInput_iXL5eSyncPortA = 2,
	/// @brief iXL5e Sync Port B.
	Automation1PsoWindowInput_iXL5eSyncPortB = 3,
	/// @brief iXL5e Drive Pulse Stream.
	Automation1PsoWindowInput_iXL5eDrivePulseStream = 14,
	/// @brief iXR3 Primary Feedback Axis 1.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis1 = 0,
	/// @brief iXR3 Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis1 = 1,
	/// @brief iXR3 Primary Feedback Axis 2.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis2 = 2,
	/// @brief iXR3 Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis2 = 3,
	/// @brief iXR3 Primary Feedback Axis 3.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis3 = 4,
	/// @brief iXR3 Auxiliary Feedback Axis 3.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis3 = 5,
	/// @brief iXR3 Primary Feedback Axis 4.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis4 = 6,
	/// @brief iXR3 Auxiliary Feedback Axis 4.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis4 = 7,
	/// @brief iXR3 Primary Feedback Axis 5.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis5 = 8,
	/// @brief iXR3 Auxiliary Feedback Axis 5.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis5 = 9,
	/// @brief iXR3 Primary Feedback Axis 6.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis6 = 10,
	/// @brief iXR3 Auxiliary Feedback Axis 6.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis6 = 11,
	/// @brief iXR3 Sync Port A.
	Automation1PsoWindowInput_iXR3SyncPortA = 12,
	/// @brief iXR3 Sync Port B.
	Automation1PsoWindowInput_iXR3SyncPortB = 13,
	/// @brief iXR3 Drive Pulse Stream.
	Automation1PsoWindowInput_iXR3DrivePulseStream = 14,
} Automation1PsoWindowInput;

/// @brief Specifies the PSO output pin settings for each drive.
typedef enum Automation1PsoOutputPin
{
	/// @brief GL4 None (default).
	Automation1PsoOutputPin_GL4None = 0,
	/// @brief GL4 Laser Output 0.
	Automation1PsoOutputPin_GL4LaserOutput0 = 1,
	/// @brief XL4s None (default).
	Automation1PsoOutputPin_XL4sNone = 0,
	/// @brief XL4s Laser Output 0.
	Automation1PsoOutputPin_XL4sLaserOutput0 = 1,
	/// @brief XR3 None (default).
	Automation1PsoOutputPin_XR3None = 0,
	/// @brief XR3 PSO Output 1.
	Automation1PsoOutputPin_XR3PsoOutput1 = 1,
	/// @brief XR3 PSO Output 2.
	Automation1PsoOutputPin_XR3PsoOutput2 = 2,
	/// @brief XR3 PSO Output 3.
	Automation1PsoOutputPin_XR3PsoOutput3 = 3,
	/// @brief XC4 Dedicated Output (default).
	Automation1PsoOutputPin_XC4DedicatedOutput = 0,
	/// @brief XC4 Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_XC4AuxiliaryMarkerDifferential = 1,
	/// @brief XC4 Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_XC4AuxiliaryMarkerSingleEnded = 2,
	/// @brief XC4e Dedicated Output (default).
	Automation1PsoOutputPin_XC4eDedicatedOutput = 0,
	/// @brief XC4e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_XC4eAuxiliaryMarkerDifferential = 1,
	/// @brief XC4e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_XC4eAuxiliaryMarkerSingleEnded = 2,
	/// @brief XC6e Dedicated Output (default).
	Automation1PsoOutputPin_XC6eDedicatedOutput = 0,
	/// @brief XC6e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_XC6eAuxiliaryMarkerDifferential = 1,
	/// @brief XC6e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_XC6eAuxiliaryMarkerSingleEnded = 2,
	/// @brief XL5e Dedicated Output (default).
	Automation1PsoOutputPin_XL5eDedicatedOutput = 0,
	/// @brief XL5e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_XL5eAuxiliaryMarkerDifferential = 1,
	/// @brief XL5e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_XL5eAuxiliaryMarkerSingleEnded = 2,
	/// @brief SI4 Dedicated Output (default).
	Automation1PsoOutputPin_SI4DedicatedOutput = 0,
	/// @brief XC2 Dedicated Output (default).
	Automation1PsoOutputPin_XC2DedicatedOutput = 0,
	/// @brief XC2e Dedicated Output (default).
	Automation1PsoOutputPin_XC2eDedicatedOutput = 0,
	/// @brief XL2e Dedicated Output (default).
	Automation1PsoOutputPin_XL2eDedicatedOutput = 0,
	/// @brief XI4 Dedicated Output (default).
	Automation1PsoOutputPin_XI4DedicatedOutput = 0,
	/// @brief iXC4 Dedicated Output (default).
	Automation1PsoOutputPin_iXC4DedicatedOutput = 0,
	/// @brief iXC4 Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_iXC4AuxiliaryMarkerDifferential = 1,
	/// @brief iXC4 Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_iXC4AuxiliaryMarkerSingleEnded = 2,
	/// @brief iXC4e Dedicated Output (default).
	Automation1PsoOutputPin_iXC4eDedicatedOutput = 0,
	/// @brief iXC4e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_iXC4eAuxiliaryMarkerDifferential = 1,
	/// @brief iXC4e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_iXC4eAuxiliaryMarkerSingleEnded = 2,
	/// @brief iXC6e Dedicated Output (default).
	Automation1PsoOutputPin_iXC6eDedicatedOutput = 0,
	/// @brief iXC6e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_iXC6eAuxiliaryMarkerDifferential = 1,
	/// @brief iXC6e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_iXC6eAuxiliaryMarkerSingleEnded = 2,
	/// @brief iXL5e Dedicated Output (default).
	Automation1PsoOutputPin_iXL5eDedicatedOutput = 0,
	/// @brief iXL5e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_iXL5eAuxiliaryMarkerDifferential = 1,
	/// @brief iXL5e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_iXL5eAuxiliaryMarkerSingleEnded = 2,
	/// @brief iXR3 None (default).
	Automation1PsoOutputPin_iXR3None = 0,
	/// @brief iXR3 PSO Output 1.
	Automation1PsoOutputPin_iXR3PsoOutput1 = 1,
	/// @brief iXR3 PSO Output 2.
	Automation1PsoOutputPin_iXR3PsoOutput2 = 2,
	/// @brief iXR3 PSO Output 3.
	Automation1PsoOutputPin_iXR3PsoOutput3 = 3,
} Automation1PsoOutputPin;

/// @brief This value represents information about the state of this task.
typedef enum Automation1TaskState
{
	/// @brief The Controller Plus Option is not installed. You cannot use this task.
	Automation1TaskState_Unavailable = 0,
	/// @brief This task was disabled by the EnabledTasks parameter.
	Automation1TaskState_Inactive = 1,
	/// @brief No program is associated or running.
	Automation1TaskState_Idle = 2,
	/// @brief A program is associated but not running.
	Automation1TaskState_ProgramReady = 3,
	/// @brief A program is associated and running.
	Automation1TaskState_ProgramRunning = 4,
	/// @brief A program is associated, was run, and feedhold is active. This state is active from the moment the motion begins to decelerate due to a feedhold until the moment the motion begins to accelerate back to speed due to a feedhold release.
	Automation1TaskState_ProgramFeedhold = 5,
	/// @brief A program is associated, was run, and was paused.
	Automation1TaskState_ProgramPaused = 6,
	/// @brief A program is associated, was run, and completed.(1)
	Automation1TaskState_ProgramComplete = 7,
	/// @brief A task error occurred on this task.
	Automation1TaskState_Error = 8,
	/// @brief This task is operating in queue mode.
	Automation1TaskState_Queue = 9,
} Automation1TaskState;

/// @brief Represents the motor type
typedef enum Automation1MotorType
{
	/// @brief 
	Automation1MotorType_ACBrushlessLinear = 0,
	/// @brief 
	Automation1MotorType_ACBrushlessRotary = 1,
	/// @brief 
	Automation1MotorType_DCBrush = 2,
	/// @brief 
	Automation1MotorType_StepperMotor = 3,
	/// @brief 
	Automation1MotorType_TwoPhaseACBrushless = 6,
	/// @brief 
	Automation1MotorType_PiezoActuator = 8,
	/// @brief 
	Automation1MotorType_Galvo = 9,
} Automation1MotorType;

/// @brief Represents the home type
typedef enum Automation1HomeType
{
	/// @brief 
	Automation1HomeType_PastLimittoMarker = 0,
	/// @brief 
	Automation1HomeType_ToLimitandReversetoMarker = 1,
	/// @brief 
	Automation1HomeType_ToMarkerOnly = 2,
	/// @brief 
	Automation1HomeType_ToLimitOnly = 3,
	/// @brief 
	Automation1HomeType_AtCurrentPosition = 4,
	/// @brief 
	Automation1HomeType_AtCurrentPositionFeedback = 5,
	/// @brief 
	Automation1HomeType_AtCurrentPositionAbsolute = 6,
} Automation1HomeType;

/// @brief Represents the feedback type on the primary connector
typedef enum Automation1PrimaryFeedbackType
{
	/// @brief 
	Automation1PrimaryFeedbackType_None = 0,
	/// @brief 
	Automation1PrimaryFeedbackType_IncrementalEncoderSquareWave = 1,
	/// @brief 
	Automation1PrimaryFeedbackType_IncrementalEncoderSineWave = 2,
	/// @brief 
	Automation1PrimaryFeedbackType_AbsoluteEncoderEnDatwithSineWaveIncremental = 3,
	/// @brief 
	Automation1PrimaryFeedbackType_AbsoluteEncoderEnDat = 4,
	/// @brief 
	Automation1PrimaryFeedbackType_HallEffectSwitches = 5,
	/// @brief 
	Automation1PrimaryFeedbackType_AbsoluteEncoderSSI = 6,
	/// @brief 
	Automation1PrimaryFeedbackType_AbsoluteEncoderBiSS = 9,
	/// @brief 
	Automation1PrimaryFeedbackType_CapacitanceSensor = 11,
} Automation1PrimaryFeedbackType;

/// @brief Represents the feedback type on the auxiliary connector
typedef enum Automation1AuxiliaryFeedbackType
{
	/// @brief 
	Automation1AuxiliaryFeedbackType_None = 0,
	/// @brief 
	Automation1AuxiliaryFeedbackType_IncrementalEncoderSquareWave = 1,
	/// @brief 
	Automation1AuxiliaryFeedbackType_IncrementalEncoderSineWave = 2,
	/// @brief 
	Automation1AuxiliaryFeedbackType_AbsoluteEncoderEnDat = 4,
	/// @brief 
	Automation1AuxiliaryFeedbackType_AbsoluteEncoderSSI = 6,
	/// @brief 
	Automation1AuxiliaryFeedbackType_AbsoluteEncoderBiSS = 9,
} Automation1AuxiliaryFeedbackType;

/// @brief Represents a set of queue status
typedef enum Automation1QueueStatus
{
	/// @brief 
	Automation1QueueStatus_QueueModeActive = 1 << 0,
	/// @brief The Queue buffer for this task is empty.
	Automation1QueueStatus_QueueBufferEmpty = 1 << 1,
	/// @brief The Queue buffer for this task is full.
	Automation1QueueStatus_QueueBufferFull = 1 << 2,
	/// @brief The Queue buffer for this task started.
	Automation1QueueStatus_QueueBufferStarted = 1 << 3,
	/// @brief The Queue buffer for this task was paused.
	Automation1QueueStatus_QueueBufferPaused = 1 << 4,
	/// @brief The given task is executing a large program line-by-line in queue mode.
	Automation1QueueStatus_QueueLargeProgramExecuting = 1 << 5,
} Automation1QueueStatus;

/// @brief Represents the piezo default servo state.
typedef enum Automation1PiezoDefaultServoState
{
	/// @brief 
	Automation1PiezoDefaultServoState_Off = 0,
	/// @brief 
	Automation1PiezoDefaultServoState_On = 1,
} Automation1PiezoDefaultServoState;

/// @brief Represents an axis status
typedef enum Automation1AxisStatus
{
	/// @brief The axis is homed.
	Automation1AxisStatus_Homed = 1 << 0,
	/// @brief The axis is performing coordinated (LINEAR, CW, CCW, BEZIER), RAPID, or PVT motion.
	Automation1AxisStatus_Profiling = 1 << 1,
	/// @brief The controller finished waiting for motion on this axis to complete. The behavior of this bit depends on the selected wait mode. When in Wait Mode Motion Done, this bit will mimic the Motion Done bit, but when in Wait Mode In Position, this bit will not be active until both the Motion Done bit and the In Position bit are both active.
	Automation1AxisStatus_WaitDone = 1 << 2,
	/// @brief Motion on the axis is controlled from the SMC.
	Automation1AxisStatus_CommandValid = 1 << 3,
	/// @brief The axis is currently homing.
	Automation1AxisStatus_Homing = 1 << 4,
	/// @brief The axis is currently enabling.
	Automation1AxisStatus_Enabling = 1 << 5,
	/// @brief This bit represents internal status.
	Automation1AxisStatus_JogGenerating = 1 << 7,
	/// @brief The axis is performing asynchronous motion (MoveIncremental(), MoveAbsolute(), MoveFreerun()).
	Automation1AxisStatus_Jogging = 1 << 8,
	/// @brief The SMC sent a command to the drive that will cause the drive to take control of the motion, but the drive has not yet done so.
	Automation1AxisStatus_DrivePending = 1 << 9,
	/// @brief The SMC sent an abort command to the drive, but the drive has not yet started the abort.
	Automation1AxisStatus_DriveAbortPending = 1 << 10,
	/// @brief Trajectory filtering is enabled for this axis using either the TrajectoryIIRFilter or TrajectoryFIRFilter parameters.
	Automation1AxisStatus_TrajectoryFiltering = 1 << 11,
	/// @brief Infinite Field of View (IFOV) is enabled for this axis. Enable IFOV by issuing the IFOV ON command. Disable IFOV by issuing the IFOV OFF command.
	Automation1AxisStatus_IfovEnabled = 1 << 12,
	/// @brief A physical drive is associated with this axis. Axes with no drive attached will clear this bit and operate as virtual axes.
	Automation1AxisStatus_NotVirtual = 1 << 13,
	/// @brief The specified 1D calibration file contains a calibration table that corrects this axis. The state of this bit is not affected by the CALENABLE or CALDISABLE commands.
	Automation1AxisStatus_CalibrationEnabled1D = 1 << 14,
	/// @brief The specified 2D calibration file contains a calibration table that corrects this axis. The state of this bit is not affected by the CALENABLE or CALDISABLE commands.
	Automation1AxisStatus_CalibrationEnabled2D = 1 << 15,
	/// @brief The axis is currently controlled by camming or gearing.
	Automation1AxisStatus_CammingGearingControl = 1 << 16,
	/// @brief The axis is currently performing motion under control of the JOYSTICK command.
	Automation1AxisStatus_JoystickControl = 1 << 17,
	/// @brief Backlash compensation is enabled for this axis using the BacklashDistance parameter or the BACKLASH ON command.
	Automation1AxisStatus_BacklashActive = 1 << 18,
	/// @brief A Gain Mapping table was specified for this axis.
	Automation1AxisStatus_GainMappingEnabled = 1 << 19,
	/// @brief Motion on this axis is done, meaning that the velocity command reached zero.
	Automation1AxisStatus_MotionDone = 1 << 22,
	/// @brief Motion on this axis is being clamped due to a software limit clamp or safe zone. Refer to the SoftwareLimitSetup parameter, and the Safe zone overview.
	Automation1AxisStatus_MotionClamped = 1 << 23,
	/// @brief This axis is part of a gantry pair and the gantry is correctly aligned. This bit will not be active until the gantry axes have been homed.
	Automation1AxisStatus_GantryAligned = 1 << 24,
	/// @brief The axis is currently performing gantry realignment motion due to Theta axis misalignment caused by drive motion.
	Automation1AxisStatus_GantryDriveControlRealigning = 1 << 25,
	/// @brief The ThermoComp feature is currently turned on.
	Automation1AxisStatus_ThermoCompEnabled = 1 << 27,
} Automation1AxisStatus;

/// @brief Represents the faults of an axis
typedef enum Automation1AxisFault
{
	/// @brief The absolute value of the difference between the position command and the position feedback exceeded the threshold specified by the PositionErrorThreshold parameter.
	Automation1AxisFault_PositionErrorFault = 1 << 0,
	/// @brief The average motor current exceeded the threshold specified by the AverageCurrentThreshold and AverageCurrentTime parameters.
	Automation1AxisFault_OverCurrentFault = 1 << 1,
	/// @brief The axis encountered the clockwise (positive) end-of-travel limit switch.
	Automation1AxisFault_CwEndOfTravelLimitFault = 1 << 2,
	/// @brief The axis encountered the counter-clockwise (negative) end-of-travel limit switch.
	Automation1AxisFault_CcwEndOfTravelLimitFault = 1 << 3,
	/// @brief The axis was commanded to move beyond the position specified by the SoftwareLimitHigh parameter.
	Automation1AxisFault_CwSoftwareLimitFault = 1 << 4,
	/// @brief The axis was commanded to move beyond the position specified by the SoftwareLimitLow parameter.
	Automation1AxisFault_CcwSoftwareLimitFault = 1 << 5,
	/// @brief The amplifier for this axis exceeded its maximum current rating or experienced an internal error.
	Automation1AxisFault_AmplifierFault = 1 << 6,
	/// @brief The drive detected a problem with the feedback device specified by the FeedbackInput0 parameter. Or, the drive detected an invalid feedback configuration.
	Automation1AxisFault_FeedbackInput0Fault = 1 << 7,
	/// @brief The drive detected a problem with the feedback device specified by the FeedbackInput1 parameter. Or, the drive detected an invalid feedback configuration.
	Automation1AxisFault_FeedbackInput1Fault = 1 << 8,
	/// @brief The drive detected an invalid state (all high or all low) for the Hall-effect sensor inputs on this axis.
	Automation1AxisFault_HallSensorFault = 1 << 9,
	/// @brief The commanded velocity is more than the velocity command threshold. Before the axis is homed, this threshold is specified by the VelocityCommandThresholdBeforeHome parameter. After the axis is homed, this threshold is specified by the VelocityCommandThreshold parameter.
	Automation1AxisFault_MaxVelocityCommandFault = 1 << 10,
	/// @brief The emergency stop sense input, specified by the ESTOPFaultInput or SoftwareESTOPInput parameter, was triggered, or the controller detected a fault condition in the Safe Torque Off (STO) hardware.
	Automation1AxisFault_EmergencyStopFault = 1 << 11,
	/// @brief The absolute value of the difference between the velocity command and the velocity feedback exceeded the threshold specified by the VelocityErrorThreshold parameter.
	Automation1AxisFault_VelocityErrorFault = 1 << 12,
	/// @brief The external fault input, specified by the ExternalFaultAnalogInput, ExternalFaultDigitalInput, or SoftwareExternalFaultInput parameter, was triggered.
	Automation1AxisFault_ExternalFault = 1 << 15,
	/// @brief The motor thermistor input was triggered, which indicates that the motor exceeded its maximum recommended operating temperature.
	Automation1AxisFault_MotorTemperatureFault = 1 << 17,
	/// @brief The amplifier temperature is not within the operating range. This fault occurs at temperatures less than 0° C or greater than 75° C.
	Automation1AxisFault_AmplifierTemperatureFault = 1 << 18,
	/// @brief The encoder fault input on the motor feedback connector was triggered.
	Automation1AxisFault_EncoderFault = 1 << 19,
	/// @brief The position command or position feedback of the rotary gantry axis exceeded the value specified by the GantryMisalignmentThreshold parameter.
	Automation1AxisFault_GantryMisalignmentFault = 1 << 22,
	/// @brief The difference between the position feedback and the scaled (adjusted by GainKv) velocity feedback exceeds the threshold specified by the PositionErrorThreshold parameter.
	Automation1AxisFault_FeedbackScalingFault = 1 << 23,
	/// @brief The distance that the axis moved while searching for the marker exceeded the threshold specified by the MarkerSearchThreshold parameter.
	Automation1AxisFault_MarkerSearchFault = 1 << 24,
	/// @brief The axis decelerated to a stop because the motion violated a safe zone.
	Automation1AxisFault_SafeZoneFault = 1 << 25,
	/// @brief The axis did not achieve in position status in the period specified by the InPositionDisableTimeout parameter.
	Automation1AxisFault_InPositionTimeoutFault = 1 << 26,
	/// @brief The commanded voltage output exceeded the value of the PiezoVoltageClampLow or PiezoVoltageClampHigh parameter.
	Automation1AxisFault_VoltageClampFault = 1 << 27,
	/// @brief The motor power supply output has exceeded the allowable power or temperature threshold.
	Automation1AxisFault_MotorSupplyFault = 1 << 28,
	/// @brief The drive encountered an internal error that caused it to disable. Contact Aerotech Global Technical Support.
	Automation1AxisFault_InternalFault = 1 << 30,
} Automation1AxisFault;

/// @brief Represents the drive status bits
typedef enum Automation1DriveStatus
{
	/// @brief The axis is enabled.
	Automation1DriveStatus_Enabled = 1 << 0,
	/// @brief This represents the state of the CW end of travel limit input. It is affected by the active polarity, which is configured by the EndOfTravelLimitSetup parameter.
	Automation1DriveStatus_CwEndOfTravelLimitInput = 1 << 1,
	/// @brief This represents the state of the CCW end of travel limit input. It is affected by the active polarity, which is configured by the EndOfTravelLimitSetup parameter.
	Automation1DriveStatus_CcwEndOfTravelLimitInput = 1 << 2,
	/// @brief This represents the state of the home limit input. It is affected by the active polarity, which is configured by the EndOfTravelLimitSetup parameter.
	Automation1DriveStatus_HomeLimitInput = 1 << 3,
	/// @brief This represents the state of the marker input.
	Automation1DriveStatus_MarkerInput = 1 << 4,
	/// @brief This represents the state of the Hall-effect sensor A input.
	Automation1DriveStatus_HallAInput = 1 << 5,
	/// @brief This represents the state of the Hall-effect sensor B input.
	Automation1DriveStatus_HallBInput = 1 << 6,
	/// @brief This represents the state of the Hall-effect sensor C input.
	Automation1DriveStatus_HallCInput = 1 << 7,
	/// @brief An error condition is present on the Sine encoder input of the position feedback device.
	Automation1DriveStatus_SineEncoderError = 1 << 8,
	/// @brief An error condition is present on the Cosine encoder input of the position feedback device.
	Automation1DriveStatus_CosineEncoderError = 1 << 9,
	/// @brief This represents the state of the emergency stop sense input.
	Automation1DriveStatus_EmergencyStopInput = 1 << 10,
	/// @brief State of the dedicated brake output.
	Automation1DriveStatus_BrakeOutput = 1 << 11,
	/// @brief Galvo Power Correction is configured on this axis.
	Automation1DriveStatus_GalvoPowerCorrection = 1 << 12,
	/// @brief The drive detected that no motor supply voltage is present.
	Automation1DriveStatus_NoMotorSupply = 1 << 14,
	/// @brief For piezo drives, the controller clamps the motor output to the value of the PiezoVoltageClampLow or the PiezoVoltageClampHigh parameter. For all other drives, the controller clamps the motor output to the value of the MaxCurrentClamp parameter.
	Automation1DriveStatus_CurrentClamp = 1 << 15,
	/// @brief The position of the marker is latched.
	Automation1DriveStatus_MarkerLatch = 1 << 16,
	/// @brief The motor output is being limited to prevent damage to the amplifier.
	Automation1DriveStatus_PowerLimiting = 1 << 17,
	/// @brief The specified 2D calibration file contains a galvo calibration table that corrects this axis.
	Automation1DriveStatus_GalvoCalibrationEnabled = 1 << 20,
	/// @brief The axis is operating under control of the AUTOFOCUS loop.
	Automation1DriveStatus_AutofocusActive = 1 << 21,
	/// @brief The drive is programming its internal flash memory.
	Automation1DriveStatus_ProgrammingFlash = 1 << 22,
	/// @brief The axis is operating under servo control.
	Automation1DriveStatus_ServoControl = 1 << 24,
	/// @brief The axis is considered to be in position as configured by the InPositionDistance and InPositionTime parameters.
	Automation1DriveStatus_InPosition = 1 << 25,
	/// @brief The axis is performing drive generated motion.
	Automation1DriveStatus_MoveActive = 1 << 26,
	/// @brief The axis is accelerating.
	Automation1DriveStatus_AccelerationPhase = 1 << 27,
	/// @brief The axis is decelerating.
	Automation1DriveStatus_DecelerationPhase = 1 << 28,
	/// @brief The on-board encoder multiplier detected that the input signals may be exceeding the maximum input range, which results in clipping of the encoder signals.
	Automation1DriveStatus_EncoderClipping = 1 << 29,
	/// @brief The axis is operating in dual-loop mode using two different feedback devices.
	Automation1DriveStatus_DualLoopActive = 1 << 30,
} Automation1DriveStatus;

/// @brief Represents a set of task status
typedef enum Automation1TaskStatus0
{
	/// @brief A program is associated with this task.
	Automation1TaskStatus0_ProgramAssociated = 1 << 0,
	/// @brief An immediate command is executing.
	Automation1TaskStatus0_ImmediateExecuting = 1 << 3,
	/// @brief Return motion is executing due to an TaskInterruptMotionOff() function.
	Automation1TaskStatus0_ReturnMotionExecuting = 1 << 4,
	/// @brief The program is reset.
	Automation1TaskStatus0_ProgramReset = 1 << 8,
	/// @brief One or more axes are decelerating due to an abort, task stop, task error, feedhold, onerror, or retrace direction reversal that occurs during a RAPID, LINEAR, CW, CCW, or BEZIER motion.
	Automation1TaskStatus0_PendingAxesStop = 1 << 9,
	/// @brief Bit turns on as soon as motion begins to decelerate due to a feedhold. Bit turns off when motion begins to accelerate back to speed due to a feedhold release. The FeedholdAxesStopped bit of Task Status 1 indicates when deceleration due to a feedhold stops.
	Automation1TaskStatus0_FeedholdActive = 1 << 11,
	/// @brief A callback command was issued and is waiting for a front-end application to acknowledge the command.
	Automation1TaskStatus0_CallbackHoldActive = 1 << 12,
	/// @brief A callback command was issued and is waiting for a front-end application to handle the command.
	Automation1TaskStatus0_CallbackResponding = 1 << 13,
	/// @brief The spindle is currently active.
	Automation1TaskStatus0_SpindleActive = 1 << 14,
	/// @brief Retrace is active.
	Automation1TaskStatus0_Retrace = 1 << 19,
	/// @brief Interrupt motion is active.
	Automation1TaskStatus0_InterruptMotionActive = 1 << 21,
	/// @brief The task is executing a JoystickRun() function.
	Automation1TaskStatus0_JoystickActive = 1 << 22,
	/// @brief Corner rounding is enabled.
	Automation1TaskStatus0_CornerRounding = 1 << 23,
	/// @brief The joystick is using the low speed mode.
	Automation1TaskStatus0_JoystickLowSpeedActive = 1 << 25,
	/// @brief A synchronized function is executing.
	Automation1TaskStatus0_SynchronizedFunctionExecuting = 1 << 27,
	/// @brief The task has control restrictions enabled.
	Automation1TaskStatus0_TaskControlRestricted = 1 << 29,
} Automation1TaskStatus0;

/// @brief Represents a set of task status
typedef enum Automation1TaskStatus1
{
	/// @brief An asynchronous motion is aborting.
	Automation1TaskStatus1_AsyncSmcMotionAbortPending = 1 << 1,
	/// @brief A retrace operation was requested.
	Automation1TaskStatus1_RetraceRequested = 1 << 3,
	/// @brief An MSO change was issued.
	Automation1TaskStatus1_MsoChange = 1 << 4,
	/// @brief A spindle is in feedhold.
	Automation1TaskStatus1_SpindleFeedhold = 1 << 5,
	/// @brief Bit turns on as soon as deceleration due to a feedhold ends. Bit turns off when motion begins to accelerate back to speed due to a feedhold release. The FeedholdActive bit of Task Status 0 indicates when a feedhold is issued.
	Automation1TaskStatus1_FeedholdAxesStopped = 1 << 6,
	/// @brief Cutter radius compensation is performing a lead-on move.
	Automation1TaskStatus1_CutterRadiusEnabling = 1 << 7,
	/// @brief Cutter radius compensation is performing a lead-off move.
	Automation1TaskStatus1_CutterRadiusDisabling = 1 << 8,
	/// @brief Cutter offset compensation is performing a lead-on positive move.
	Automation1TaskStatus1_CutterOffsetsEnablingPositive = 1 << 9,
	/// @brief Cutter offset compensation is performing a lead-on negative move.
	Automation1TaskStatus1_CutterOffsetsEnablingNegative = 1 << 10,
	/// @brief Cutter offset compensation is performing a lead-off move.
	Automation1TaskStatus1_CutterOffsetsDisabling = 1 << 11,
	/// @brief An onerror handler is pending.
	Automation1TaskStatus1_OnErrorHandlerPending = 1 << 13,
	/// @brief An onerror handler is executing.
	Automation1TaskStatus1_OnErrorHandlerExecuting = 1 << 14,
	/// @brief A program stop is pending.
	Automation1TaskStatus1_ProgramStopPending = 1 << 16,
	/// @brief A synchronized function is pending.
	Automation1TaskStatus1_SynchronizedFunctionPending = 1 << 17,
	/// @brief The MfoMinimum parameter is negative.
	Automation1TaskStatus1_NoMfoFloor = 1 << 18,
	/// @brief This bit represents internal status.
	Automation1TaskStatus1_Interrupted = 1 << 19,
	/// @brief This bit represents internal status.
	Automation1TaskStatus1_IfovBufferHold = 1 << 25,
} Automation1TaskStatus1;

/// @brief Represents a set of task status
typedef enum Automation1TaskStatus2
{
	/// @brief Parts scaling is active.
	Automation1TaskStatus2_ScalingActive = 1 << 3,
	/// @brief Fixture offsets are active.
	Automation1TaskStatus2_OffsetFixtureActive = 1 << 4,
	/// @brief Profile motion is active.
	Automation1TaskStatus2_ProfileActive = 1 << 5,
	/// @brief The motion mode is Rapid (G0).
	Automation1TaskStatus2_MotionModeRapid = 1 << 6,
	/// @brief The motion mode is Linear (G1).
	Automation1TaskStatus2_MotionModeLinear = 1 << 7,
	/// @brief MovePvt() motion is being executed.
	Automation1TaskStatus2_MotionPvt = 1 << 8,
	/// @brief The task is actively velocity profiling.
	Automation1TaskStatus2_MotionContinuousActive = 1 << 9,
	/// @brief Positive cutter offset compensation is active.
	Automation1TaskStatus2_CutterOffsetsActivePos = 1 << 12,
	/// @brief Cutter radius compensation left is active.
	Automation1TaskStatus2_CutterRadiusActiveLeft = 1 << 13,
	/// @brief Cutter radius compensation right is active.
	Automation1TaskStatus2_CutterRadiusActiveRight = 1 << 14,
	/// @brief Negative cutter offset compensation is active.
	Automation1TaskStatus2_CutterOffsetsActiveNeg = 1 << 15,
	/// @brief Normalcy left is active.
	Automation1TaskStatus2_NormalcyActiveLeft = 1 << 16,
	/// @brief Normalcy right is active.
	Automation1TaskStatus2_NormalcyActiveRight = 1 << 17,
	/// @brief A normalcy alignment move is being performed.
	Automation1TaskStatus2_NormalcyAlignment = 1 << 18,
	/// @brief The motion mode is CW (G2).
	Automation1TaskStatus2_MotionModeCw = 1 << 19,
	/// @brief The motion mode is CCW (G3).
	Automation1TaskStatus2_MotionModeCcw = 1 << 20,
	/// @brief Feedrate limiting is active.
	Automation1TaskStatus2_LimitFeedrateActive = 1 << 21,
	/// @brief MFO limiting is active.
	Automation1TaskStatus2_LimitMfoActive = 1 << 22,
	/// @brief Coordinate System 1 Plane 1 is active.
	Automation1TaskStatus2_Coord1Plane1 = 1 << 23,
	/// @brief Coordinate System 1 Plane 2 is active.
	Automation1TaskStatus2_Coord1Plane2 = 1 << 24,
	/// @brief Coordinate System 1 Plane 3 is active.
	Automation1TaskStatus2_Coord1Plane3 = 1 << 25,
	/// @brief Coordinate System 2 Plane 1 is active.
	Automation1TaskStatus2_Coord2Plane1 = 1 << 26,
	/// @brief Coordinate System 2 Plane 2 is active.
	Automation1TaskStatus2_Coord2Plane2 = 1 << 27,
	/// @brief Coordinate System 2 Plane 3 is active.
	Automation1TaskStatus2_Coord2Plane3 = 1 << 28,
} Automation1TaskStatus2;

/// @brief Represents a set of task status
typedef enum Automation1TaskMode
{
	/// @brief Secondary units mode is in use.
	Automation1TaskMode_Secondary = 1 << 0,
	/// @brief Absolute programming mode is in use.
	Automation1TaskMode_Absolute = 1 << 1,
	/// @brief The acceleration type is configured for linear ramping.
	Automation1TaskMode_AccelTypeLinear = 1 << 2,
	/// @brief The acceleration mode is rate-based.
	Automation1TaskMode_AccelModeRate = 1 << 3,
	/// @brief Inverse dominance (G98) mode is active.
	Automation1TaskMode_InverseDominance = 1 << 4,
	/// @brief Motion continuous (VelocityBlendingOn()) mode is active.
	Automation1TaskMode_MotionContinuous = 1 << 5,
	/// @brief Spindles will abort on a program stop (G101).
	Automation1TaskMode_SpindleStopOnProgramHalt = 1 << 7,
	/// @brief Optional Pause mode is active (G114).
	Automation1TaskMode_OptionalPause = 1 << 9,
	/// @brief The acceleration type is configured for S-curve ramping.
	Automation1TaskMode_AccelTypeSCurve = 1 << 10,
	/// @brief MFO Lock mode is active (M48).
	Automation1TaskMode_MfoLock = 1 << 11,
	/// @brief MSO Lock mode is active (M50).
	Automation1TaskMode_MsoLock = 1 << 12,
	/// @brief The deceleration type is configured for linear ramping.
	Automation1TaskMode_DecelTypeLinear = 1 << 13,
	/// @brief The deceleration type is configured for S-curve ramping.
	Automation1TaskMode_DecelTypeSCurve = 1 << 14,
	/// @brief Programmed feed rates are specified in inverse time units (G93).
	Automation1TaskMode_ProgramFeedrateInverseTime = 1 << 16,
	/// @brief Programmed feed rates are specified in units per spindle revolution (G95).
	Automation1TaskMode_ProgramFeedrateUnitsPerSpindleRev = 1 << 17,
	/// @brief The deceleration mode is rate-based.
	Automation1TaskMode_DecelModeRate = 1 << 24,
	/// @brief MFO will affect asynchronous motion (G121).
	Automation1TaskMode_MfoActiveOnJog = 1 << 26,
	/// @brief The wait for in-position wait mode is active.
	Automation1TaskMode_WaitForInPos = 1 << 27,
	/// @brief When this bit is true the time units are minutes. When this bit is false the time units are seconds.
	Automation1TaskMode_Minutes = 1 << 28,
	/// @brief The automatic wait mode is active.
	Automation1TaskMode_WaitAuto = 1 << 30,
} Automation1TaskMode;

/// @brief Represents the ramp type in AeroScript
typedef enum Automation1RampType
{
	/// @brief 
	Automation1RampType_Linear = 0,
	/// @brief 
	Automation1RampType_SCurve = 1,
	/// @brief 
	Automation1RampType_Sine = 2,
} Automation1RampType;

/// @brief Represents the ramp mode in AeroScript
typedef enum Automation1RampMode
{
	/// @brief 
	Automation1RampMode_Rate = 0,
	/// @brief 
	Automation1RampMode_Time = 1,
} Automation1RampMode;

/// @brief Represents the first feedback input
typedef enum Automation1FeedbackInput0
{
	/// @brief 
	Automation1FeedbackInput0_PositionCommand = 0,
	/// @brief 
	Automation1FeedbackInput0_PrimaryFeedback = 1,
	/// @brief 
	Automation1FeedbackInput0_AuxiliaryFeedback = 2,
	/// @brief 
	Automation1FeedbackInput0_AnalogInput0 = 3,
	/// @brief 
	Automation1FeedbackInput0_AnalogInput1 = 4,
	/// @brief 
	Automation1FeedbackInput0_AnalogInput2 = 5,
	/// @brief 
	Automation1FeedbackInput0_AnalogInput3 = 6,
} Automation1FeedbackInput0;

/// @brief Represents the second feedback input
typedef enum Automation1FeedbackInput1
{
	/// @brief 
	Automation1FeedbackInput1_PositionCommand = 0,
	/// @brief 
	Automation1FeedbackInput1_PrimaryFeedback = 1,
	/// @brief 
	Automation1FeedbackInput1_AuxiliaryFeedback = 2,
	/// @brief 
	Automation1FeedbackInput1_AnalogInput0 = 3,
	/// @brief 
	Automation1FeedbackInput1_AnalogInput1 = 4,
	/// @brief 
	Automation1FeedbackInput1_AnalogInput2 = 5,
	/// @brief 
	Automation1FeedbackInput1_AnalogInput3 = 6,
} Automation1FeedbackInput1;

/// @brief The type of disturbance to use when measuring a frequency response.
typedef enum Automation1TuningDisturbanceType
{
	/// @brief Use a sinusoid disturbance.
	Automation1TuningDisturbanceType_Sinusoid = 1,
	/// @brief Use a white noise disturbance.
	Automation1TuningDisturbanceType_WhiteNoise = 2,
	/// @brief Use the drive array to define a custom disturbance.
	Automation1TuningDisturbanceType_DriveArray = 5,
} Automation1TuningDisturbanceType;

/// @brief The type of frequency response to measure.
typedef enum Automation1TuningMeasurementType
{
	/// @brief Measure the open loop response of the servo loop.
	Automation1TuningMeasurementType_ServoOpenLoop = 0,
	/// @brief Measure the open loop response of the current loop.
	Automation1TuningMeasurementType_CurrentOpenLoop = 2,
	/// @brief Measure the open loop response of the auto-focus loop.
	Automation1TuningMeasurementType_AutoFocusOpenLoop = 3,
} Automation1TuningMeasurementType;

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1ENUM_H_INCLUDED