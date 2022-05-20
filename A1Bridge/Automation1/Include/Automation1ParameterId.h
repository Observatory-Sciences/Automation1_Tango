#ifndef AUTOMATION1PARAMETERID_H_INCLUDED
#define AUTOMATION1PARAMETERID_H_INCLUDED

#if defined(__cplusplus)
extern "C"
{
#endif

	/// @brief Represents a controller parameter in the system parameter category.
	typedef enum Automation1SystemParameterId
	{
		/// @brief The DataCollectionPoints system controller parameter.
		Automation1SystemParameterId_DataCollectionPoints = 75,
		/// @brief The DataCollectionItems system controller parameter.
		Automation1SystemParameterId_DataCollectionItems = 76,
		/// @brief The GlobalReals system controller parameter.
		Automation1SystemParameterId_GlobalReals = 93,
		/// @brief The AsciiInterfacePort system controller parameter.
		Automation1SystemParameterId_AsciiInterfacePort = 96,
		/// @brief The AsciiInterfaceSetup system controller parameter.
		Automation1SystemParameterId_AsciiInterfaceSetup = 100,
		/// @brief The RequiredAxes system controller parameter.
		Automation1SystemParameterId_RequiredAxes = 101,
		/// @brief The AsciiInterfaceTerminatingCharacter system controller parameter.
		Automation1SystemParameterId_AsciiInterfaceTerminatingCharacter = 117,
		/// @brief The AsciiInterfaceSuccessCharacter system controller parameter.
		Automation1SystemParameterId_AsciiInterfaceSuccessCharacter = 118,
		/// @brief The AsciiInterfaceInvalidCharacter system controller parameter.
		Automation1SystemParameterId_AsciiInterfaceInvalidCharacter = 119,
		/// @brief The AsciiInterfaceFaultCharacter system controller parameter.
		Automation1SystemParameterId_AsciiInterfaceFaultCharacter = 120,
		/// @brief The GlobalStrings system controller parameter.
		Automation1SystemParameterId_GlobalStrings = 173,
		/// @brief The DependentSpeedScaleFactor system controller parameter.
		Automation1SystemParameterId_DependentSpeedScaleFactor = 214,
		/// @brief The SecondaryUnitsScaleFactor system controller parameter.
		Automation1SystemParameterId_SecondaryUnitsScaleFactor = 263,
		/// @brief The PrimaryUnitsMapping system controller parameter.
		Automation1SystemParameterId_PrimaryUnitsMapping = 264,
		/// @brief The SecondaryUnitsName system controller parameter.
		Automation1SystemParameterId_SecondaryUnitsName = 265,
		/// @brief The EnabledTasks system controller parameter.
		Automation1SystemParameterId_EnabledTasks = 278,
		/// @brief The FaultAckMoveOutOfLimit system controller parameter.
		Automation1SystemParameterId_FaultAckMoveOutOfLimit = 279,
		/// @brief The SoftwareExternalFaultInput system controller parameter.
		Automation1SystemParameterId_SoftwareExternalFaultInput = 348,
		/// @brief The SignalLogSetup system controller parameter.
		Automation1SystemParameterId_SignalLogSetup = 355,
		/// @brief The SignalLogAxes system controller parameter.
		Automation1SystemParameterId_SignalLogAxes = 356,
		/// @brief The SignalLogTasks system controller parameter.
		Automation1SystemParameterId_SignalLogTasks = 357,
		/// @brief The SignalLogFaultMaskTrigger system controller parameter.
		Automation1SystemParameterId_SignalLogFaultMaskTrigger = 358,
		/// @brief The SignalLogSamplePeriod system controller parameter.
		Automation1SystemParameterId_SignalLogSamplePeriod = 359,
		/// @brief The SignalLogPointsBeforeTrigger system controller parameter.
		Automation1SystemParameterId_SignalLogPointsBeforeTrigger = 360,
		/// @brief The SignalLogPointsAfterTrigger system controller parameter.
		Automation1SystemParameterId_SignalLogPointsAfterTrigger = 361,
		/// @brief The IfovConfigurations system controller parameter.
		Automation1SystemParameterId_IfovConfigurations = 391,
		/// @brief The IfovMaximumTime system controller parameter.
		Automation1SystemParameterId_IfovMaximumTime = 393,
		/// @brief The SignalLogItems system controller parameter.
		Automation1SystemParameterId_SignalLogItems = 397,
		/// @brief The GlobalIntegers system controller parameter.
		Automation1SystemParameterId_GlobalIntegers = 482,
		/// @brief The TransformationEnableMode system controller parameter.
		Automation1SystemParameterId_TransformationEnableMode = 492,
		/// @brief The SoftwareEmergencyStopInput system controller parameter.
		Automation1SystemParameterId_SoftwareEmergencyStopInput = 493,
	} Automation1SystemParameterId;

	/// @brief Represents a controller parameter in the axis parameter category.
	typedef enum Automation1AxisParameterId
	{
		/// @brief The AxisName axis controller parameter.
		Automation1AxisParameterId_AxisName = 0,
		/// @brief The AxisType axis controller parameter.
		Automation1AxisParameterId_AxisType = 2,
		/// @brief The ReverseMotionDirection axis controller parameter.
		Automation1AxisParameterId_ReverseMotionDirection = 3,
		/// @brief The CountsPerUnit axis controller parameter.
		Automation1AxisParameterId_CountsPerUnit = 4,
		/// @brief The ServoLoopSetup axis controller parameter.
		Automation1AxisParameterId_ServoLoopSetup = 5,
		/// @brief The FeedforwardGainVff axis controller parameter.
		Automation1AxisParameterId_FeedforwardGainVff = 6,
		/// @brief The FeedforwardGainAff axis controller parameter.
		Automation1AxisParameterId_FeedforwardGainAff = 7,
		/// @brief The ServoLoopGainKv axis controller parameter.
		Automation1AxisParameterId_ServoLoopGainKv = 8,
		/// @brief The ServoLoopFilter00CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter00CoeffN0 = 9,
		/// @brief The ServoLoopFilter00CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter00CoeffN1 = 10,
		/// @brief The ServoLoopFilter00CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter00CoeffN2 = 11,
		/// @brief The ServoLoopFilter00CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter00CoeffD1 = 12,
		/// @brief The ServoLoopFilter00CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter00CoeffD2 = 13,
		/// @brief The ServoLoopFilter01CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter01CoeffN0 = 14,
		/// @brief The ServoLoopFilter01CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter01CoeffN1 = 15,
		/// @brief The ServoLoopFilter01CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter01CoeffN2 = 16,
		/// @brief The ServoLoopFilter01CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter01CoeffD1 = 17,
		/// @brief The ServoLoopFilter01CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter01CoeffD2 = 18,
		/// @brief The RolloverCounts axis controller parameter.
		Automation1AxisParameterId_RolloverCounts = 19,
		/// @brief The CurrentLoopGainKi axis controller parameter.
		Automation1AxisParameterId_CurrentLoopGainKi = 20,
		/// @brief The CurrentLoopGainK axis controller parameter.
		Automation1AxisParameterId_CurrentLoopGainK = 21,
		/// @brief The FaultMask axis controller parameter.
		Automation1AxisParameterId_FaultMask = 22,
		/// @brief The FaultMaskDisable axis controller parameter.
		Automation1AxisParameterId_FaultMaskDisable = 23,
		/// @brief The FaultMaskDecel axis controller parameter.
		Automation1AxisParameterId_FaultMaskDecel = 24,
		/// @brief The BrakeSetup axis controller parameter.
		Automation1AxisParameterId_BrakeSetup = 25,
		/// @brief The FaultMaskOutput axis controller parameter.
		Automation1AxisParameterId_FaultMaskOutput = 26,
		/// @brief The EmergencyStopFaultInput axis controller parameter.
		Automation1AxisParameterId_EmergencyStopFaultInput = 27,
		/// @brief The PositionErrorThreshold axis controller parameter.
		Automation1AxisParameterId_PositionErrorThreshold = 28,
		/// @brief The AverageCurrentThreshold axis controller parameter.
		Automation1AxisParameterId_AverageCurrentThreshold = 29,
		/// @brief The AverageCurrentTime axis controller parameter.
		Automation1AxisParameterId_AverageCurrentTime = 30,
		/// @brief The VelocityCommandThreshold axis controller parameter.
		Automation1AxisParameterId_VelocityCommandThreshold = 31,
		/// @brief The VelocityErrorThreshold axis controller parameter.
		Automation1AxisParameterId_VelocityErrorThreshold = 32,
		/// @brief The SoftwareLimitLow axis controller parameter.
		Automation1AxisParameterId_SoftwareLimitLow = 33,
		/// @brief The SoftwareLimitHigh axis controller parameter.
		Automation1AxisParameterId_SoftwareLimitHigh = 34,
		/// @brief The MaxCurrentClamp axis controller parameter.
		Automation1AxisParameterId_MaxCurrentClamp = 35,
		/// @brief The InPositionDistance axis controller parameter.
		Automation1AxisParameterId_InPositionDistance = 36,
		/// @brief The MotorType axis controller parameter.
		Automation1AxisParameterId_MotorType = 37,
		/// @brief The CommutationOffset axis controller parameter.
		Automation1AxisParameterId_CommutationOffset = 40,
		/// @brief The AutoMsetTime axis controller parameter.
		Automation1AxisParameterId_AutoMsetTime = 41,
		/// @brief The AutoMsetCurrent axis controller parameter.
		Automation1AxisParameterId_AutoMsetCurrent = 42,
		/// @brief The PrimaryFeedbackType axis controller parameter.
		Automation1AxisParameterId_PrimaryFeedbackType = 43,
		/// @brief The FeedbackInput0 axis controller parameter.
		Automation1AxisParameterId_FeedbackInput0 = 44,
		/// @brief The AuxiliaryFeedbackType axis controller parameter.
		Automation1AxisParameterId_AuxiliaryFeedbackType = 45,
		/// @brief The FeedbackInput1 axis controller parameter.
		Automation1AxisParameterId_FeedbackInput1 = 46,
		/// @brief The PrimaryEncoderMultiplicationFactor axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoderMultiplicationFactor = 47,
		/// @brief The PrimaryEncoder0SineGain axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoder0SineGain = 48,
		/// @brief The PrimaryEncoder0SineOffset axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoder0SineOffset = 49,
		/// @brief The PrimaryEncoder0CosineGain axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoder0CosineGain = 50,
		/// @brief The PrimaryEncoder0CosineOffset axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoder0CosineOffset = 51,
		/// @brief The PrimaryEncoder0Phase axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoder0Phase = 52,
		/// @brief The LimitDecelDistance axis controller parameter.
		Automation1AxisParameterId_LimitDecelDistance = 53,
		/// @brief The LimitDebounceTime axis controller parameter.
		Automation1AxisParameterId_LimitDebounceTime = 54,
		/// @brief The EndOfTravelLimitSetup axis controller parameter.
		Automation1AxisParameterId_EndOfTravelLimitSetup = 55,
		/// @brief The BacklashDistance axis controller parameter.
		Automation1AxisParameterId_BacklashDistance = 56,
		/// @brief The FaultOutputSetup axis controller parameter.
		Automation1AxisParameterId_FaultOutputSetup = 57,
		/// @brief The FaultOutputState axis controller parameter.
		Automation1AxisParameterId_FaultOutputState = 58,
		/// @brief The IOSetup axis controller parameter.
		Automation1AxisParameterId_IOSetup = 59,
		/// @brief The BrakeOutput axis controller parameter.
		Automation1AxisParameterId_BrakeOutput = 60,
		/// @brief The ExternalFaultDigitalInput axis controller parameter.
		Automation1AxisParameterId_ExternalFaultDigitalInput = 62,
		/// @brief The BrakeDisableDelay axis controller parameter.
		Automation1AxisParameterId_BrakeDisableDelay = 63,
		/// @brief The MaxJogDistance axis controller parameter.
		Automation1AxisParameterId_MaxJogDistance = 64,
		/// @brief The DefaultAxisSpeed axis controller parameter.
		Automation1AxisParameterId_DefaultAxisSpeed = 65,
		/// @brief The DefaultAxisRampRate axis controller parameter.
		Automation1AxisParameterId_DefaultAxisRampRate = 66,
		/// @brief The AbortDecelRate axis controller parameter.
		Automation1AxisParameterId_AbortDecelRate = 67,
		/// @brief The HomeType axis controller parameter.
		Automation1AxisParameterId_HomeType = 68,
		/// @brief The HomeSetup axis controller parameter.
		Automation1AxisParameterId_HomeSetup = 69,
		/// @brief The HomeSpeed axis controller parameter.
		Automation1AxisParameterId_HomeSpeed = 70,
		/// @brief The HomeOffset axis controller parameter.
		Automation1AxisParameterId_HomeOffset = 71,
		/// @brief The HomeRampRate axis controller parameter.
		Automation1AxisParameterId_HomeRampRate = 72,
		/// @brief The StepperMicrostepsPerStep axis controller parameter.
		Automation1AxisParameterId_StepperMicrostepsPerStep = 77,
		/// @brief The StepperRunningCurrent axis controller parameter.
		Automation1AxisParameterId_StepperRunningCurrent = 78,
		/// @brief The StepperHoldingCurrent axis controller parameter.
		Automation1AxisParameterId_StepperHoldingCurrent = 79,
		/// @brief The LimitDebounceDistance axis controller parameter.
		Automation1AxisParameterId_LimitDebounceDistance = 81,
		/// @brief The ServoLoopFilter02CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter02CoeffN0 = 82,
		/// @brief The ServoLoopFilter02CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter02CoeffN1 = 83,
		/// @brief The ServoLoopFilter02CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter02CoeffN2 = 84,
		/// @brief The ServoLoopFilter02CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter02CoeffD1 = 85,
		/// @brief The ServoLoopFilter02CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter02CoeffD2 = 86,
		/// @brief The ServoLoopFilter03CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter03CoeffN0 = 87,
		/// @brief The ServoLoopFilter03CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter03CoeffN1 = 88,
		/// @brief The ServoLoopFilter03CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter03CoeffN2 = 89,
		/// @brief The ServoLoopFilter03CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter03CoeffD1 = 90,
		/// @brief The ServoLoopFilter03CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter03CoeffD2 = 91,
		/// @brief The MaxJogSpeed axis controller parameter.
		Automation1AxisParameterId_MaxJogSpeed = 92,
		/// @brief The UnitsName axis controller parameter.
		Automation1AxisParameterId_UnitsName = 95,
		/// @brief The PrimaryEnDatEncoderSetup axis controller parameter.
		Automation1AxisParameterId_PrimaryEnDatEncoderSetup = 97,
		/// @brief The PrimaryEnDatEncoderResolution axis controller parameter.
		Automation1AxisParameterId_PrimaryEnDatEncoderResolution = 98,
		/// @brief The PrimaryEnDatEncoderTurns axis controller parameter.
		Automation1AxisParameterId_PrimaryEnDatEncoderTurns = 99,
		/// @brief The JoystickLowSpeed axis controller parameter.
		Automation1AxisParameterId_JoystickLowSpeed = 108,
		/// @brief The JoystickHighSpeed axis controller parameter.
		Automation1AxisParameterId_JoystickHighSpeed = 109,
		/// @brief The HomePositionSet axis controller parameter.
		Automation1AxisParameterId_HomePositionSet = 110,
		/// @brief The FaultMaskDisableDelay axis controller parameter.
		Automation1AxisParameterId_FaultMaskDisableDelay = 113,
		/// @brief The FaultAbortAxes axis controller parameter.
		Automation1AxisParameterId_FaultAbortAxes = 121,
		/// @brief The HarmonicCancellation0Type axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation0Type = 122,
		/// @brief The HarmonicCancellation0Period axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation0Period = 123,
		/// @brief The HarmonicCancellation0Channel axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation0Channel = 124,
		/// @brief The HarmonicCancellation0Gain axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation0Gain = 125,
		/// @brief The HarmonicCancellation0Phase axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation0Phase = 126,
		/// @brief The HarmonicCancellation1Type axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation1Type = 127,
		/// @brief The HarmonicCancellation1Period axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation1Period = 128,
		/// @brief The HarmonicCancellation1Channel axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation1Channel = 129,
		/// @brief The HarmonicCancellation1Gain axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation1Gain = 130,
		/// @brief The HarmonicCancellation1Phase axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation1Phase = 131,
		/// @brief The HarmonicCancellation2Type axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation2Type = 132,
		/// @brief The HarmonicCancellation2Period axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation2Period = 133,
		/// @brief The HarmonicCancellation2Channel axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation2Channel = 134,
		/// @brief The HarmonicCancellation2Gain axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation2Gain = 135,
		/// @brief The HarmonicCancellation2Phase axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation2Phase = 136,
		/// @brief The SoftwareLimitSetup axis controller parameter.
		Automation1AxisParameterId_SoftwareLimitSetup = 137,
		/// @brief The PrimaryEmulatedQuadratureDivider axis controller parameter.
		Automation1AxisParameterId_PrimaryEmulatedQuadratureDivider = 138,
		/// @brief The HarmonicCancellation3Type axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation3Type = 139,
		/// @brief The HarmonicCancellation3Period axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation3Period = 140,
		/// @brief The HarmonicCancellation3Channel axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation3Channel = 141,
		/// @brief The HarmonicCancellation3Gain axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation3Gain = 142,
		/// @brief The HarmonicCancellation3Phase axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation3Phase = 143,
		/// @brief The HarmonicCancellation4Type axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation4Type = 144,
		/// @brief The HarmonicCancellation4Period axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation4Period = 145,
		/// @brief The HarmonicCancellation4Channel axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation4Channel = 146,
		/// @brief The HarmonicCancellation4Gain axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation4Gain = 147,
		/// @brief The HarmonicCancellation4Phase axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellation4Phase = 148,
		/// @brief The EnhancedThroughputChannel axis controller parameter.
		Automation1AxisParameterId_EnhancedThroughputChannel = 149,
		/// @brief The EnhancedThroughputGain axis controller parameter.
		Automation1AxisParameterId_EnhancedThroughputGain = 150,
		/// @brief The HarmonicCancellationSetup axis controller parameter.
		Automation1AxisParameterId_HarmonicCancellationSetup = 151,
		/// @brief The EnhancedThroughputCurrentClamp axis controller parameter.
		Automation1AxisParameterId_EnhancedThroughputCurrentClamp = 152,
		/// @brief The Analog0Filter0CoeffN0 axis controller parameter.
		Automation1AxisParameterId_Analog0Filter0CoeffN0 = 153,
		/// @brief The Analog0Filter0CoeffN1 axis controller parameter.
		Automation1AxisParameterId_Analog0Filter0CoeffN1 = 154,
		/// @brief The Analog0Filter0CoeffN2 axis controller parameter.
		Automation1AxisParameterId_Analog0Filter0CoeffN2 = 155,
		/// @brief The Analog0Filter0CoeffD1 axis controller parameter.
		Automation1AxisParameterId_Analog0Filter0CoeffD1 = 156,
		/// @brief The Analog0Filter0CoeffD2 axis controller parameter.
		Automation1AxisParameterId_Analog0Filter0CoeffD2 = 157,
		/// @brief The Analog0Filter1CoeffN0 axis controller parameter.
		Automation1AxisParameterId_Analog0Filter1CoeffN0 = 158,
		/// @brief The Analog0Filter1CoeffN1 axis controller parameter.
		Automation1AxisParameterId_Analog0Filter1CoeffN1 = 159,
		/// @brief The Analog0Filter1CoeffN2 axis controller parameter.
		Automation1AxisParameterId_Analog0Filter1CoeffN2 = 160,
		/// @brief The Analog0Filter1CoeffD1 axis controller parameter.
		Automation1AxisParameterId_Analog0Filter1CoeffD1 = 161,
		/// @brief The Analog0Filter1CoeffD2 axis controller parameter.
		Automation1AxisParameterId_Analog0Filter1CoeffD2 = 162,
		/// @brief The Analog1Filter0CoeffN0 axis controller parameter.
		Automation1AxisParameterId_Analog1Filter0CoeffN0 = 163,
		/// @brief The Analog1Filter0CoeffN1 axis controller parameter.
		Automation1AxisParameterId_Analog1Filter0CoeffN1 = 164,
		/// @brief The Analog1Filter0CoeffN2 axis controller parameter.
		Automation1AxisParameterId_Analog1Filter0CoeffN2 = 165,
		/// @brief The Analog1Filter0CoeffD1 axis controller parameter.
		Automation1AxisParameterId_Analog1Filter0CoeffD1 = 166,
		/// @brief The Analog1Filter0CoeffD2 axis controller parameter.
		Automation1AxisParameterId_Analog1Filter0CoeffD2 = 167,
		/// @brief The Analog1Filter1CoeffN0 axis controller parameter.
		Automation1AxisParameterId_Analog1Filter1CoeffN0 = 168,
		/// @brief The Analog1Filter1CoeffN1 axis controller parameter.
		Automation1AxisParameterId_Analog1Filter1CoeffN1 = 169,
		/// @brief The Analog1Filter1CoeffN2 axis controller parameter.
		Automation1AxisParameterId_Analog1Filter1CoeffN2 = 170,
		/// @brief The Analog1Filter1CoeffD1 axis controller parameter.
		Automation1AxisParameterId_Analog1Filter1CoeffD1 = 171,
		/// @brief The Analog1Filter1CoeffD2 axis controller parameter.
		Automation1AxisParameterId_Analog1Filter1CoeffD2 = 172,
		/// @brief The DefaultAxisRampMode axis controller parameter.
		Automation1AxisParameterId_DefaultAxisRampMode = 176,
		/// @brief The DefaultAxisRampTime axis controller parameter.
		Automation1AxisParameterId_DefaultAxisRampTime = 177,
		/// @brief The ServoLoopFilterSetup axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilterSetup = 178,
		/// @brief The FeedbackSetup axis controller parameter.
		Automation1AxisParameterId_FeedbackSetup = 179,
		/// @brief The PrimaryEncoderMultiplierSetup axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoderMultiplierSetup = 180,
		/// @brief The FaultSetup axis controller parameter.
		Automation1AxisParameterId_FaultSetup = 181,
		/// @brief The ServoLoopFilter04CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter04CoeffN0 = 182,
		/// @brief The ServoLoopFilter04CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter04CoeffN1 = 183,
		/// @brief The ServoLoopFilter04CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter04CoeffN2 = 184,
		/// @brief The ServoLoopFilter04CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter04CoeffD1 = 185,
		/// @brief The ServoLoopFilter04CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter04CoeffD2 = 186,
		/// @brief The ServoLoopFilter05CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter05CoeffN0 = 187,
		/// @brief The ServoLoopFilter05CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter05CoeffN1 = 188,
		/// @brief The ServoLoopFilter05CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter05CoeffN2 = 189,
		/// @brief The ServoLoopFilter05CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter05CoeffD1 = 190,
		/// @brief The ServoLoopFilter05CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter05CoeffD2 = 191,
		/// @brief The ServoLoopFilter06CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter06CoeffN0 = 192,
		/// @brief The ServoLoopFilter06CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter06CoeffN1 = 193,
		/// @brief The ServoLoopFilter06CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter06CoeffN2 = 194,
		/// @brief The ServoLoopFilter06CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter06CoeffD1 = 195,
		/// @brief The ServoLoopFilter06CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter06CoeffD2 = 196,
		/// @brief The ServoLoopFilter07CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter07CoeffN0 = 197,
		/// @brief The ServoLoopFilter07CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter07CoeffN1 = 198,
		/// @brief The ServoLoopFilter07CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter07CoeffN2 = 199,
		/// @brief The ServoLoopFilter07CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter07CoeffD1 = 200,
		/// @brief The ServoLoopFilter07CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter07CoeffD2 = 201,
		/// @brief The RolloverMode axis controller parameter.
		Automation1AxisParameterId_RolloverMode = 203,
		/// @brief The BrakeEnableDelay axis controller parameter.
		Automation1AxisParameterId_BrakeEnableDelay = 204,
		/// @brief The MaxSpeedClamp axis controller parameter.
		Automation1AxisParameterId_MaxSpeedClamp = 205,
		/// @brief The TrajectoryFirFilter axis controller parameter.
		Automation1AxisParameterId_TrajectoryFirFilter = 206,
		/// @brief The TrajectoryIirFilter axis controller parameter.
		Automation1AxisParameterId_TrajectoryIirFilter = 207,
		/// @brief The CalibrationIirFilter axis controller parameter.
		Automation1AxisParameterId_CalibrationIirFilter = 208,
		/// @brief The BacklashIirFilter axis controller parameter.
		Automation1AxisParameterId_BacklashIirFilter = 209,
		/// @brief The InPositionTime axis controller parameter.
		Automation1AxisParameterId_InPositionTime = 210,
		/// @brief The InPositionTimeoutThreshold axis controller parameter.
		Automation1AxisParameterId_InPositionTimeoutThreshold = 211,
		/// @brief The ServoOutputScaling axis controller parameter.
		Automation1AxisParameterId_ServoOutputScaling = 213,
		/// @brief The ExternalFaultAnalogInput axis controller parameter.
		Automation1AxisParameterId_ExternalFaultAnalogInput = 217,
		/// @brief The ExternalFaultThreshold axis controller parameter.
		Automation1AxisParameterId_ExternalFaultThreshold = 218,
		/// @brief The AnalogFilterSetup axis controller parameter.
		Automation1AxisParameterId_AnalogFilterSetup = 266,
		/// @brief The DefaultAxisRampType axis controller parameter.
		Automation1AxisParameterId_DefaultAxisRampType = 269,
		/// @brief The ServoOutputOffsetA axis controller parameter.
		Automation1AxisParameterId_ServoOutputOffsetA = 270,
		/// @brief The ServoOutputOffsetB axis controller parameter.
		Automation1AxisParameterId_ServoOutputOffsetB = 271,
		/// @brief The CurrentOffsetA axis controller parameter.
		Automation1AxisParameterId_CurrentOffsetA = 276,
		/// @brief The CurrentOffsetB axis controller parameter.
		Automation1AxisParameterId_CurrentOffsetB = 277,
		/// @brief The CommandShaperSetup axis controller parameter.
		Automation1AxisParameterId_CommandShaperSetup = 280,
		/// @brief The CommandShaperTime00 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime00 = 281,
		/// @brief The CommandShaperTime01 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime01 = 282,
		/// @brief The CommandShaperTime02 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime02 = 283,
		/// @brief The CommandShaperTime03 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime03 = 284,
		/// @brief The CommandShaperTime04 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime04 = 285,
		/// @brief The CommandShaperTime05 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime05 = 286,
		/// @brief The CommandShaperTime06 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime06 = 287,
		/// @brief The CommandShaperTime07 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime07 = 288,
		/// @brief The CommandShaperTime08 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime08 = 289,
		/// @brief The CommandShaperTime09 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime09 = 290,
		/// @brief The CommandShaperTime10 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime10 = 291,
		/// @brief The CommandShaperTime11 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime11 = 292,
		/// @brief The CommandShaperTime12 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime12 = 293,
		/// @brief The CommandShaperTime13 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime13 = 294,
		/// @brief The CommandShaperTime14 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime14 = 295,
		/// @brief The CommandShaperTime15 axis controller parameter.
		Automation1AxisParameterId_CommandShaperTime15 = 296,
		/// @brief The CommandShaperCoeff00 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff00 = 297,
		/// @brief The CommandShaperCoeff01 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff01 = 298,
		/// @brief The CommandShaperCoeff02 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff02 = 299,
		/// @brief The CommandShaperCoeff03 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff03 = 300,
		/// @brief The CommandShaperCoeff04 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff04 = 301,
		/// @brief The CommandShaperCoeff05 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff05 = 302,
		/// @brief The CommandShaperCoeff06 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff06 = 303,
		/// @brief The CommandShaperCoeff07 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff07 = 304,
		/// @brief The CommandShaperCoeff08 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff08 = 305,
		/// @brief The CommandShaperCoeff09 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff09 = 306,
		/// @brief The CommandShaperCoeff10 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff10 = 307,
		/// @brief The CommandShaperCoeff11 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff11 = 308,
		/// @brief The CommandShaperCoeff12 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff12 = 309,
		/// @brief The CommandShaperCoeff13 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff13 = 310,
		/// @brief The CommandShaperCoeff14 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff14 = 311,
		/// @brief The CommandShaperCoeff15 axis controller parameter.
		Automation1AxisParameterId_CommandShaperCoeff15 = 312,
		/// @brief The CommandShaper0Type axis controller parameter.
		Automation1AxisParameterId_CommandShaper0Type = 313,
		/// @brief The CommandShaper0Frequency axis controller parameter.
		Automation1AxisParameterId_CommandShaper0Frequency = 314,
		/// @brief The CommandShaper0Damping axis controller parameter.
		Automation1AxisParameterId_CommandShaper0Damping = 315,
		/// @brief The CommandShaper1Type axis controller parameter.
		Automation1AxisParameterId_CommandShaper1Type = 316,
		/// @brief The CommandShaper1Frequency axis controller parameter.
		Automation1AxisParameterId_CommandShaper1Frequency = 317,
		/// @brief The CommandShaper1Damping axis controller parameter.
		Automation1AxisParameterId_CommandShaper1Damping = 318,
		/// @brief The PrimaryBissEncoderSetup axis controller parameter.
		Automation1AxisParameterId_PrimaryBissEncoderSetup = 319,
		/// @brief The PrimaryBissEncoderResolution axis controller parameter.
		Automation1AxisParameterId_PrimaryBissEncoderResolution = 320,
		/// @brief The AutofocusInput axis controller parameter.
		Automation1AxisParameterId_AutofocusInput = 322,
		/// @brief The AutofocusTarget axis controller parameter.
		Automation1AxisParameterId_AutofocusTarget = 323,
		/// @brief The AutofocusDeadband axis controller parameter.
		Automation1AxisParameterId_AutofocusDeadband = 324,
		/// @brief The AutofocusGainKi1 axis controller parameter.
		Automation1AxisParameterId_AutofocusGainKi1 = 325,
		/// @brief The AutofocusGainK axis controller parameter.
		Automation1AxisParameterId_AutofocusGainK = 326,
		/// @brief The AutofocusLimitLow axis controller parameter.
		Automation1AxisParameterId_AutofocusLimitLow = 327,
		/// @brief The AutofocusLimitHigh axis controller parameter.
		Automation1AxisParameterId_AutofocusLimitHigh = 328,
		/// @brief The AutofocusSpeedClamp axis controller parameter.
		Automation1AxisParameterId_AutofocusSpeedClamp = 329,
		/// @brief The AutofocusHoldInput axis controller parameter.
		Automation1AxisParameterId_AutofocusHoldInput = 330,
		/// @brief The AutofocusSetup axis controller parameter.
		Automation1AxisParameterId_AutofocusSetup = 331,
		/// @brief The TrajectoryDelayTime axis controller parameter.
		Automation1AxisParameterId_TrajectoryDelayTime = 333,
		/// @brief The CrossAxisFeedforward00Axis axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward00Axis = 334,
		/// @brief The CrossAxisFeedforward01Axis axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward01Axis = 335,
		/// @brief The CrossAxisFeedforward02Axis axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward02Axis = 336,
		/// @brief The CrossAxisFeedforward03Axis axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward03Axis = 337,
		/// @brief The CrossAxisFeedforward04Axis axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward04Axis = 338,
		/// @brief The CrossAxisFeedforward05Axis axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward05Axis = 339,
		/// @brief The CrossAxisFeedforward00Gain axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward00Gain = 340,
		/// @brief The CrossAxisFeedforward01Gain axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward01Gain = 341,
		/// @brief The CrossAxisFeedforward02Gain axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward02Gain = 342,
		/// @brief The CrossAxisFeedforward03Gain axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward03Gain = 343,
		/// @brief The CrossAxisFeedforward04Gain axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward04Gain = 344,
		/// @brief The CrossAxisFeedforward05Gain axis controller parameter.
		Automation1AxisParameterId_CrossAxisFeedforward05Gain = 345,
		/// @brief The FeedforwardGainPff axis controller parameter.
		Automation1AxisParameterId_FeedforwardGainPff = 346,
		/// @brief The AutofocusInitialRampTime axis controller parameter.
		Automation1AxisParameterId_AutofocusInitialRampTime = 347,
		/// @brief The EndOfTravelCurrentThresholdLow axis controller parameter.
		Automation1AxisParameterId_EndOfTravelCurrentThresholdLow = 350,
		/// @brief The EndOfTravelCurrentThresholdHigh axis controller parameter.
		Automation1AxisParameterId_EndOfTravelCurrentThresholdHigh = 351,
		/// @brief The AutofocusGainKi2 axis controller parameter.
		Automation1AxisParameterId_AutofocusGainKi2 = 352,
		/// @brief The PrimaryEnDatEncoderIncrementalResolution axis controller parameter.
		Automation1AxisParameterId_PrimaryEnDatEncoderIncrementalResolution = 353,
		/// @brief The MarkerSearchThreshold axis controller parameter.
		Automation1AxisParameterId_MarkerSearchThreshold = 354,
		/// @brief The VelocityCommandThresholdBeforeHome axis controller parameter.
		Automation1AxisParameterId_VelocityCommandThresholdBeforeHome = 362,
		/// @brief The PrimaryEncoder1SineGain axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoder1SineGain = 363,
		/// @brief The PrimaryEncoder1SineOffset axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoder1SineOffset = 364,
		/// @brief The PrimaryEncoder1CosineGain axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoder1CosineGain = 365,
		/// @brief The PrimaryEncoder1CosineOffset axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoder1CosineOffset = 366,
		/// @brief The PrimaryEncoder1Phase axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoder1Phase = 367,
		/// @brief The DriveOutputCommandDelay axis controller parameter.
		Automation1AxisParameterId_DriveOutputCommandDelay = 368,
		/// @brief The StepperRunningCurrentDelay axis controller parameter.
		Automation1AxisParameterId_StepperRunningCurrentDelay = 369,
		/// @brief The PrimaryAbsoluteFeedbackOffset axis controller parameter.
		Automation1AxisParameterId_PrimaryAbsoluteFeedbackOffset = 371,
		/// @brief The CapSensorFilterLength axis controller parameter.
		Automation1AxisParameterId_CapSensorFilterLength = 372,
		/// @brief The EnhancedTrackingScale axis controller parameter.
		Automation1AxisParameterId_EnhancedTrackingScale = 373,
		/// @brief The EnhancedTrackingBandwidth axis controller parameter.
		Automation1AxisParameterId_EnhancedTrackingBandwidth = 374,
		/// @brief The Analog0InputOffset axis controller parameter.
		Automation1AxisParameterId_Analog0InputOffset = 375,
		/// @brief The Analog1InputOffset axis controller parameter.
		Automation1AxisParameterId_Analog1InputOffset = 376,
		/// @brief The Analog2InputOffset axis controller parameter.
		Automation1AxisParameterId_Analog2InputOffset = 377,
		/// @brief The Analog3InputOffset axis controller parameter.
		Automation1AxisParameterId_Analog3InputOffset = 378,
		/// @brief The EnhancedTrackingSetup axis controller parameter.
		Automation1AxisParameterId_EnhancedTrackingSetup = 379,
		/// @brief The PrimaryEncoderMarkerAlignment axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoderMarkerAlignment = 380,
		/// @brief The PrimaryEncoderRadiusThresholdLow axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoderRadiusThresholdLow = 381,
		/// @brief The PrimaryEncoderRadiusThresholdHigh axis controller parameter.
		Automation1AxisParameterId_PrimaryEncoderRadiusThresholdHigh = 382,
		/// @brief The ServoLoopGainKsi1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopGainKsi1 = 383,
		/// @brief The ServoLoopGainKsi2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopGainKsi2 = 384,
		/// @brief The PiezoVoltsPerUnit axis controller parameter.
		Automation1AxisParameterId_PiezoVoltsPerUnit = 385,
		/// @brief The PiezoVoltageClampLow axis controller parameter.
		Automation1AxisParameterId_PiezoVoltageClampLow = 386,
		/// @brief The PiezoVoltageClampHigh axis controller parameter.
		Automation1AxisParameterId_PiezoVoltageClampHigh = 387,
		/// @brief The PiezoInitialServoState axis controller parameter.
		Automation1AxisParameterId_PiezoInitialServoState = 389,
		/// @brief The FeedforwardAdvance axis controller parameter.
		Automation1AxisParameterId_FeedforwardAdvance = 390,
		/// @brief The CapSensorSetup axis controller parameter.
		Automation1AxisParameterId_CapSensorSetup = 392,
		/// @brief The CapSensorThresholdLow axis controller parameter.
		Automation1AxisParameterId_CapSensorThresholdLow = 394,
		/// @brief The CapSensorThresholdHigh axis controller parameter.
		Automation1AxisParameterId_CapSensorThresholdHigh = 395,
		/// @brief The FeedforwardGainJff axis controller parameter.
		Automation1AxisParameterId_FeedforwardGainJff = 396,
		/// @brief The CurrentLoopSetup axis controller parameter.
		Automation1AxisParameterId_CurrentLoopSetup = 398,
		/// @brief The TorqueAngleOffset axis controller parameter.
		Automation1AxisParameterId_TorqueAngleOffset = 399,
		/// @brief The AuxiliaryEmulatedQuadratureDivider axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEmulatedQuadratureDivider = 400,
		/// @brief The AuxiliaryEncoderCosineGain axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEncoderCosineGain = 401,
		/// @brief The AuxiliaryEncoderCosineOffset axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEncoderCosineOffset = 402,
		/// @brief The AuxiliaryEncoderMarkerAlignment axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEncoderMarkerAlignment = 403,
		/// @brief The AuxiliaryEncoderMultiplicationFactor axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEncoderMultiplicationFactor = 404,
		/// @brief The AuxiliaryEncoderMultiplierSetup axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEncoderMultiplierSetup = 405,
		/// @brief The AuxiliaryEncoderPhase axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEncoderPhase = 406,
		/// @brief The AuxiliaryEncoderSineGain axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEncoderSineGain = 407,
		/// @brief The AuxiliaryEncoderSineOffset axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEncoderSineOffset = 408,
		/// @brief The AuxiliaryEncoderRadiusThresholdLow axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEncoderRadiusThresholdLow = 409,
		/// @brief The AuxiliaryEncoderRadiusThresholdHigh axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEncoderRadiusThresholdHigh = 410,
		/// @brief The StepperDampingGain axis controller parameter.
		Automation1AxisParameterId_StepperDampingGain = 413,
		/// @brief The StepperDampingCutoffFrequency axis controller parameter.
		Automation1AxisParameterId_StepperDampingCutoffFrequency = 414,
		/// @brief The ServoLoopFilter08CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter08CoeffN0 = 415,
		/// @brief The ServoLoopFilter08CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter08CoeffN1 = 416,
		/// @brief The ServoLoopFilter08CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter08CoeffN2 = 417,
		/// @brief The ServoLoopFilter08CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter08CoeffD1 = 418,
		/// @brief The ServoLoopFilter08CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter08CoeffD2 = 419,
		/// @brief The ServoLoopFilter09CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter09CoeffN0 = 420,
		/// @brief The ServoLoopFilter09CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter09CoeffN1 = 421,
		/// @brief The ServoLoopFilter09CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter09CoeffN2 = 422,
		/// @brief The ServoLoopFilter09CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter09CoeffD1 = 423,
		/// @brief The ServoLoopFilter09CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter09CoeffD2 = 424,
		/// @brief The ServoLoopFilter10CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter10CoeffN0 = 425,
		/// @brief The ServoLoopFilter10CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter10CoeffN1 = 426,
		/// @brief The ServoLoopFilter10CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter10CoeffN2 = 427,
		/// @brief The ServoLoopFilter10CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter10CoeffD1 = 428,
		/// @brief The ServoLoopFilter10CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter10CoeffD2 = 429,
		/// @brief The ServoLoopFilter11CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter11CoeffN0 = 430,
		/// @brief The ServoLoopFilter11CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter11CoeffN1 = 431,
		/// @brief The ServoLoopFilter11CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter11CoeffN2 = 432,
		/// @brief The ServoLoopFilter11CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter11CoeffD1 = 433,
		/// @brief The ServoLoopFilter11CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter11CoeffD2 = 434,
		/// @brief The ServoLoopFilter12CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter12CoeffN0 = 435,
		/// @brief The ServoLoopFilter12CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter12CoeffN1 = 436,
		/// @brief The ServoLoopFilter12CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter12CoeffN2 = 437,
		/// @brief The ServoLoopFilter12CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter12CoeffD1 = 438,
		/// @brief The ServoLoopFilter12CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter12CoeffD2 = 439,
		/// @brief The ServoLoopFilter13CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter13CoeffN0 = 440,
		/// @brief The ServoLoopFilter13CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter13CoeffN1 = 441,
		/// @brief The ServoLoopFilter13CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter13CoeffN2 = 442,
		/// @brief The ServoLoopFilter13CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter13CoeffD1 = 443,
		/// @brief The ServoLoopFilter13CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter13CoeffD2 = 444,
		/// @brief The ServoLoopFilter14CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter14CoeffN0 = 445,
		/// @brief The ServoLoopFilter14CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter14CoeffN1 = 446,
		/// @brief The ServoLoopFilter14CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter14CoeffN2 = 447,
		/// @brief The ServoLoopFilter14CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter14CoeffD1 = 448,
		/// @brief The ServoLoopFilter14CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter14CoeffD2 = 449,
		/// @brief The ServoLoopFilter15CoeffN0 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter15CoeffN0 = 450,
		/// @brief The ServoLoopFilter15CoeffN1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter15CoeffN1 = 451,
		/// @brief The ServoLoopFilter15CoeffN2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter15CoeffN2 = 452,
		/// @brief The ServoLoopFilter15CoeffD1 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter15CoeffD1 = 453,
		/// @brief The ServoLoopFilter15CoeffD2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopFilter15CoeffD2 = 454,
		/// @brief The AutoMsetRampTime axis controller parameter.
		Automation1AxisParameterId_AutoMsetRampTime = 455,
		/// @brief The AutoMsetAngle axis controller parameter.
		Automation1AxisParameterId_AutoMsetAngle = 456,
		/// @brief The StoPulseFilter axis controller parameter.
		Automation1AxisParameterId_StoPulseFilter = 457,
		/// @brief The CommutationInitializationSetup axis controller parameter.
		Automation1AxisParameterId_CommutationInitializationSetup = 458,
		/// @brief The CommutationInitializationAngle axis controller parameter.
		Automation1AxisParameterId_CommutationInitializationAngle = 459,
		/// @brief The FeedforwardFilter00CoeffN0 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter00CoeffN0 = 460,
		/// @brief The FeedforwardFilter00CoeffN1 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter00CoeffN1 = 461,
		/// @brief The FeedforwardFilter00CoeffN2 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter00CoeffN2 = 462,
		/// @brief The FeedforwardFilter00CoeffD1 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter00CoeffD1 = 463,
		/// @brief The FeedforwardFilter00CoeffD2 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter00CoeffD2 = 464,
		/// @brief The FeedforwardFilter01CoeffN0 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter01CoeffN0 = 465,
		/// @brief The FeedforwardFilter01CoeffN1 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter01CoeffN1 = 466,
		/// @brief The FeedforwardFilter01CoeffN2 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter01CoeffN2 = 467,
		/// @brief The FeedforwardFilter01CoeffD1 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter01CoeffD1 = 468,
		/// @brief The FeedforwardFilter01CoeffD2 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter01CoeffD2 = 469,
		/// @brief The FeedforwardFilter02CoeffN0 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter02CoeffN0 = 470,
		/// @brief The FeedforwardFilter02CoeffN1 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter02CoeffN1 = 471,
		/// @brief The FeedforwardFilter02CoeffN2 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter02CoeffN2 = 472,
		/// @brief The FeedforwardFilter02CoeffD1 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter02CoeffD1 = 473,
		/// @brief The FeedforwardFilter02CoeffD2 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter02CoeffD2 = 474,
		/// @brief The FeedforwardFilter03CoeffN0 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter03CoeffN0 = 475,
		/// @brief The FeedforwardFilter03CoeffN1 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter03CoeffN1 = 476,
		/// @brief The FeedforwardFilter03CoeffN2 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter03CoeffN2 = 477,
		/// @brief The FeedforwardFilter03CoeffD1 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter03CoeffD1 = 478,
		/// @brief The FeedforwardFilter03CoeffD2 axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilter03CoeffD2 = 479,
		/// @brief The ServoLoopGainKip2 axis controller parameter.
		Automation1AxisParameterId_ServoLoopGainKip2 = 483,
		/// @brief The ServoLoopGainKip axis controller parameter.
		Automation1AxisParameterId_ServoLoopGainKip = 484,
		/// @brief The ServoLoopGainKpv axis controller parameter.
		Automation1AxisParameterId_ServoLoopGainKpv = 485,
		/// @brief The ServoLoopGainK axis controller parameter.
		Automation1AxisParameterId_ServoLoopGainK = 486,
		/// @brief The ServoLoopGainKiv axis controller parameter.
		Automation1AxisParameterId_ServoLoopGainKiv = 487,
		/// @brief The ServoLoopGainAlpha axis controller parameter.
		Automation1AxisParameterId_ServoLoopGainAlpha = 488,
		/// @brief The ServoLoopGainNormalizationFactor axis controller parameter.
		Automation1AxisParameterId_ServoLoopGainNormalizationFactor = 489,
		/// @brief The CommutationSearchTime axis controller parameter.
		Automation1AxisParameterId_CommutationSearchTime = 490,
		/// @brief The CommutationSearchCurrent axis controller parameter.
		Automation1AxisParameterId_CommutationSearchCurrent = 491,
		/// @brief The VirtualDriveType axis controller parameter.
		Automation1AxisParameterId_VirtualDriveType = 494,
		/// @brief The VirtualDriveStartingAxis axis controller parameter.
		Automation1AxisParameterId_VirtualDriveStartingAxis = 495,
		/// @brief The FeedforwardGainNormalizationFactor axis controller parameter.
		Automation1AxisParameterId_FeedforwardGainNormalizationFactor = 496,
		/// @brief The DefaultAxisSCurvePercentage axis controller parameter.
		Automation1AxisParameterId_DefaultAxisSCurvePercentage = 497,
		/// @brief The FeedforwardFilterSetup axis controller parameter.
		Automation1AxisParameterId_FeedforwardFilterSetup = 499,
		/// @brief The MotorPolePitch axis controller parameter.
		Automation1AxisParameterId_MotorPolePitch = 500,
		/// @brief The PrimaryFeedbackResolution axis controller parameter.
		Automation1AxisParameterId_PrimaryFeedbackResolution = 501,
		/// @brief The AuxiliaryFeedbackResolution axis controller parameter.
		Automation1AxisParameterId_AuxiliaryFeedbackResolution = 502,
		/// @brief The AmplifierEnableOutputMode axis controller parameter.
		Automation1AxisParameterId_AmplifierEnableOutputMode = 503,
		/// @brief The AuxiliaryEnDatEncoderSetup axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEnDatEncoderSetup = 504,
		/// @brief The AuxiliaryEnDatEncoderResolution axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEnDatEncoderResolution = 505,
		/// @brief The AuxiliaryEnDatEncoderTurns axis controller parameter.
		Automation1AxisParameterId_AuxiliaryEnDatEncoderTurns = 506,
		/// @brief The AuxiliaryBissEncoderSetup axis controller parameter.
		Automation1AxisParameterId_AuxiliaryBissEncoderSetup = 507,
		/// @brief The AuxiliaryBissEncoderResolution axis controller parameter.
		Automation1AxisParameterId_AuxiliaryBissEncoderResolution = 508,
		/// @brief The AuxiliaryAbsoluteFeedbackOffset axis controller parameter.
		Automation1AxisParameterId_AuxiliaryAbsoluteFeedbackOffset = 510,
		/// @brief The GantryAxisMask axis controller parameter.
		Automation1AxisParameterId_GantryAxisMask = 511,
		/// @brief The GantryLogicalType axis controller parameter.
		Automation1AxisParameterId_GantryLogicalType = 512,
		/// @brief The GantryMechanicalDesign axis controller parameter.
		Automation1AxisParameterId_GantryMechanicalDesign = 514,
		/// @brief The GantryMisalignmentThreshold axis controller parameter.
		Automation1AxisParameterId_GantryMisalignmentThreshold = 515,
		/// @brief The GantryFeedbackSeparation axis controller parameter.
		Automation1AxisParameterId_GantryFeedbackSeparation = 516,
		/// @brief The AutofocusGainKi3 axis controller parameter.
		Automation1AxisParameterId_AutofocusGainKi3 = 517,
		/// @brief The AutofocusGainKi4 axis controller parameter.
		Automation1AxisParameterId_AutofocusGainKi4 = 518,
		/// @brief The AutofocusGainKi5 axis controller parameter.
		Automation1AxisParameterId_AutofocusGainKi5 = 519,
		/// @brief The AutofocusEncoderScaleFactor axis controller parameter.
		Automation1AxisParameterId_AutofocusEncoderScaleFactor = 520,
		/// @brief The PrimarySsiEncoderSetup axis controller parameter.
		Automation1AxisParameterId_PrimarySsiEncoderSetup = 521,
		/// @brief The PrimarySsiEncoderResolution axis controller parameter.
		Automation1AxisParameterId_PrimarySsiEncoderResolution = 522,
		/// @brief The AuxiliarySsiEncoderSetup axis controller parameter.
		Automation1AxisParameterId_AuxiliarySsiEncoderSetup = 523,
		/// @brief The AuxiliarySsiEncoderResolution axis controller parameter.
		Automation1AxisParameterId_AuxiliarySsiEncoderResolution = 524,
	} Automation1AxisParameterId;

	/// @brief Represents a controller parameter in the task parameter category.
	typedef enum Automation1TaskParameterId
	{
		/// @brief The TaskName task controller parameter.
		Automation1TaskParameterId_TaskName = 1,
		/// @brief The DefaultTaskWaitMode task controller parameter.
		Automation1TaskParameterId_DefaultTaskWaitMode = 73,
		/// @brief The DefaultCoordinatedSCurvePercentage task controller parameter.
		Automation1TaskParameterId_DefaultCoordinatedSCurvePercentage = 74,
		/// @brief The TaskErrorAbortAxes task controller parameter.
		Automation1TaskParameterId_TaskErrorAbortAxes = 94,
		/// @brief The JoystickInput1MinVoltage task controller parameter.
		Automation1TaskParameterId_JoystickInput1MinVoltage = 102,
		/// @brief The JoystickInput1MaxVoltage task controller parameter.
		Automation1TaskParameterId_JoystickInput1MaxVoltage = 103,
		/// @brief The JoystickInput1Deadband task controller parameter.
		Automation1TaskParameterId_JoystickInput1Deadband = 104,
		/// @brief The JoystickInput0MinVoltage task controller parameter.
		Automation1TaskParameterId_JoystickInput0MinVoltage = 105,
		/// @brief The JoystickInput0MaxVoltage task controller parameter.
		Automation1TaskParameterId_JoystickInput0MaxVoltage = 106,
		/// @brief The JoystickInput0Deadband task controller parameter.
		Automation1TaskParameterId_JoystickInput0Deadband = 107,
		/// @brief The TaskTerminationAxes task controller parameter.
		Automation1TaskParameterId_TaskTerminationAxes = 111,
		/// @brief The TaskStopAbortAxes task controller parameter.
		Automation1TaskParameterId_TaskStopAbortAxes = 112,
		/// @brief The DefaultCoordinatedSpeed task controller parameter.
		Automation1TaskParameterId_DefaultCoordinatedSpeed = 114,
		/// @brief The DefaultCoordinatedRampRate task controller parameter.
		Automation1TaskParameterId_DefaultCoordinatedRampRate = 115,
		/// @brief The DefaultDependentCoordinatedRampRate task controller parameter.
		Automation1TaskParameterId_DefaultDependentCoordinatedRampRate = 116,
		/// @brief The DefaultCoordinatedRampMode task controller parameter.
		Automation1TaskParameterId_DefaultCoordinatedRampMode = 174,
		/// @brief The DefaultCoordinatedRampTime task controller parameter.
		Automation1TaskParameterId_DefaultCoordinatedRampTime = 175,
		/// @brief The DefaultDependentCoordinatedSpeed task controller parameter.
		Automation1TaskParameterId_DefaultDependentCoordinatedSpeed = 219,
		/// @brief The DefaultCoordinatedAccelLimit task controller parameter.
		Automation1TaskParameterId_DefaultCoordinatedAccelLimit = 220,
		/// @brief The DefaultDependentCoordinatedAccelLimit task controller parameter.
		Automation1TaskParameterId_DefaultDependentCoordinatedAccelLimit = 221,
		/// @brief The DefaultCoordinatedCircularAccelLimit task controller parameter.
		Automation1TaskParameterId_DefaultCoordinatedCircularAccelLimit = 222,
		/// @brief The CoordinatedAccelLimitSetup task controller parameter.
		Automation1TaskParameterId_CoordinatedAccelLimitSetup = 223,
		/// @brief The MaxLookaheadMoves task controller parameter.
		Automation1TaskParameterId_MaxLookaheadMoves = 224,
		/// @brief The RadiusCorrectionThreshold task controller parameter.
		Automation1TaskParameterId_RadiusCorrectionThreshold = 225,
		/// @brief The RadiusErrorThreshold task controller parameter.
		Automation1TaskParameterId_RadiusErrorThreshold = 226,
		/// @brief The CutterTolerance task controller parameter.
		Automation1TaskParameterId_CutterTolerance = 227,
		/// @brief The FeedholdInput task controller parameter.
		Automation1TaskParameterId_FeedholdInput = 228,
		/// @brief The FeedholdSetup task controller parameter.
		Automation1TaskParameterId_FeedholdSetup = 229,
		/// @brief The MfoAnalogInput task controller parameter.
		Automation1TaskParameterId_MfoAnalogInput = 230,
		/// @brief The SpindleMsoInput task controller parameter.
		Automation1TaskParameterId_SpindleMsoInput = 231,
		/// @brief The SpindleAxis task controller parameter.
		Automation1TaskParameterId_SpindleAxis = 235,
		/// @brief The MotionUpdateRate task controller parameter.
		Automation1TaskParameterId_MotionUpdateRate = 245,
		/// @brief The ExecuteNumLines task controller parameter.
		Automation1TaskParameterId_ExecuteNumLines = 246,
		/// @brief The CoordinatedMoveDurationMinimum task controller parameter.
		Automation1TaskParameterId_CoordinatedMoveDurationMinimum = 247,
		/// @brief The DefaultTaskMotionMode task controller parameter.
		Automation1TaskParameterId_DefaultTaskMotionMode = 248,
		/// @brief The JoystickInput0 task controller parameter.
		Automation1TaskParameterId_JoystickInput0 = 249,
		/// @brief The JoystickInput1 task controller parameter.
		Automation1TaskParameterId_JoystickInput1 = 250,
		/// @brief The JoystickAxesSelect task controller parameter.
		Automation1TaskParameterId_JoystickAxesSelect = 251,
		/// @brief The JoystickSpeedSelect task controller parameter.
		Automation1TaskParameterId_JoystickSpeedSelect = 252,
		/// @brief The JoystickInterlock task controller parameter.
		Automation1TaskParameterId_JoystickInterlock = 253,
		/// @brief The JoystickInput2 task controller parameter.
		Automation1TaskParameterId_JoystickInput2 = 254,
		/// @brief The MfoAnalogMinVoltage task controller parameter.
		Automation1TaskParameterId_MfoAnalogMinVoltage = 255,
		/// @brief The MfoAnalogMaxVoltage task controller parameter.
		Automation1TaskParameterId_MfoAnalogMaxVoltage = 256,
		/// @brief The MfoMaximum task controller parameter.
		Automation1TaskParameterId_MfoMaximum = 257,
		/// @brief The JoystickInput2MinVoltage task controller parameter.
		Automation1TaskParameterId_JoystickInput2MinVoltage = 258,
		/// @brief The JoystickInput2MaxVoltage task controller parameter.
		Automation1TaskParameterId_JoystickInput2MaxVoltage = 259,
		/// @brief The JoystickInput2Deadband task controller parameter.
		Automation1TaskParameterId_JoystickInput2Deadband = 260,
		/// @brief The MfoMinimum task controller parameter.
		Automation1TaskParameterId_MfoMinimum = 261,
		/// @brief The MfoAnalogStep task controller parameter.
		Automation1TaskParameterId_MfoAnalogStep = 262,
		/// @brief The DefaultTaskTargetMode task controller parameter.
		Automation1TaskParameterId_DefaultTaskTargetMode = 267,
		/// @brief The DefaultCoordinatedRampType task controller parameter.
		Automation1TaskParameterId_DefaultCoordinatedRampType = 268,
		/// @brief The DefaultSpindleSpeed task controller parameter.
		Automation1TaskParameterId_DefaultSpindleSpeed = 272,
		/// @brief The MotionInterpolationMode task controller parameter.
		Automation1TaskParameterId_MotionInterpolationMode = 332,
		/// @brief The DefaultTaskTimeUnits task controller parameter.
		Automation1TaskParameterId_DefaultTaskTimeUnits = 349,
		/// @brief The MaxRetraceMoves task controller parameter.
		Automation1TaskParameterId_MaxRetraceMoves = 411,
		/// @brief The ExecuteNumLinesAfterMove task controller parameter.
		Automation1TaskParameterId_ExecuteNumLinesAfterMove = 412,
		/// @brief The StringStackSize task controller parameter.
		Automation1TaskParameterId_StringStackSize = 480,
		/// @brief The StackSize task controller parameter.
		Automation1TaskParameterId_StackSize = 481,
	} Automation1TaskParameterId;

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1PARAMETERID_H_INCLUDED