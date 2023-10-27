///
/// Copyright (c) Aerotech, Inc.
///

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
	/// @brief Motion target positions are relative to the current axis locations.
	Automation1TargetMode_Incremental = 0,
	/// @brief Motion target positions are absolute.
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

/// @brief Represents the animation type of an App Indicator.
typedef enum Automation1IndicatorAnimationType
{
	/// @brief Solid background using $backgroundColor1 and $foregroundColor1.
	Automation1IndicatorAnimationType_Solid = 0,
	/// @brief Flashes between $backgroundColor1 and transparent with no transition colors between the two. The foreground color is $foregroundColor1 for the full animation.
	Automation1IndicatorAnimationType_Flash = 1,
	/// @brief Flashes between $backgroundColor1 and $backgroundColor2 with no transition colors between the two. Also alternates the $displayText between $foregroundColor1 and $foregroundColor2.
	Automation1IndicatorAnimationType_TwoColorFlash = 2,
	/// @brief Transitions smoothly between $backgroundColor1 and $backgroundColor2 with intermediary colors. Also transitions the $displayText between $foregroundColor1 and $foregroundColor2.
	Automation1IndicatorAnimationType_ColorSweep = 3,
} Automation1IndicatorAnimationType;

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

/// @brief Specifies the conditions that will reset the PSO distance counters.
typedef enum Automation1PsoDistanceCounterResetMask
{
	/// @brief The counters will be held in reset until the first marker is encountered.
	Automation1PsoDistanceCounterResetMask_ResetUntilMarker = 1,
	/// @brief The counters will reset when the marker is encountered.
	Automation1PsoDistanceCounterResetMask_ResetOnMarker = 2,
	/// @brief The counters will be held in reset when the PSO window output is off.
	Automation1PsoDistanceCounterResetMask_ResetOutsideWindow = 4,
	/// @brief The counters will be held in reset when the laser command bit is off.
	Automation1PsoDistanceCounterResetMask_ResetWhenLaserOff = 8,
	/// @brief The counters will be held in reset when the PSO output is off.
	Automation1PsoDistanceCounterResetMask_ResetWhenOutputOff = 16,
} Automation1PsoDistanceCounterResetMask;

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

/// @brief Specifies the conditions that will reset the PSO window counters.
typedef enum Automation1PsoWindowCounterResetMask
{
	/// @brief The counters will be held in reset until the first marker is encountered.
	Automation1PsoWindowCounterResetMask_ResetUntilMarker = 1,
	/// @brief The counters will reset when the marker is encountered.
	Automation1PsoWindowCounterResetMask_ResetOnMarker = 2,
} Automation1PsoWindowCounterResetMask;

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

/// @brief Specifies additional conditions to prevent PSO events from occurring.
typedef enum Automation1PsoEventMask
{
	/// @brief PSO events will not occur when the window output is off.
	Automation1PsoEventMask_WindowMask = 1,
	/// @brief PSO events will not occur when the window output is on.
	Automation1PsoEventMask_WindowMaskInvert = 2,
	/// @brief PSO events will not occur when the laser command bit is off.
	Automation1PsoEventMask_LaserMask = 4,
	/// @brief PSO events will not occur when the active PSO bit is 0.
	Automation1PsoEventMask_BitMask = 8,
} Automation1PsoEventMask;

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

/// @brief Specifies additional conditions to disable the PSO waveform output in pulse mode.
typedef enum Automation1PsoWaveformPulseMask
{
	/// @brief PSO waveform output will be deactivated when the window output is off.
	Automation1PsoWaveformPulseMask_WindowMask = 1,
	/// @brief PSO waveform output will be deactivated when the window output is on.
	Automation1PsoWaveformPulseMask_WindowMaskInvert = 2,
	/// @brief PSO waveform output will be deactivated when the laser command bit is off.
	Automation1PsoWaveformPulseMask_LaserMask = 4,
} Automation1PsoWaveformPulseMask;

/// @brief Specifies the scaling mode of the PSO waveform module.
typedef enum Automation1PsoWaveformScalingMode
{
	/// @brief Applies waveform scaling to the total time and on time parameters.
	Automation1PsoWaveformScalingMode_ScaleTotalTimeAndOnTime = 0,
	/// @brief Applies waveform scaling to the on time parameter only.
	Automation1PsoWaveformScalingMode_ScaleOnTimeOnly = 1,
	/// @brief Applies waveform scaling to the total time parameter only.
	Automation1PsoWaveformScalingMode_ScaleTotalTimeOnly = 2,
} Automation1PsoWaveformScalingMode;

/// @brief Specifies the scaling input signal of the PSO waveform module.
typedef enum Automation1PsoWaveformScalingInput
{
	/// @brief Uses the velocity from the drive pulse stream to determine the waveform scaling value.
	Automation1PsoWaveformScalingInput_DrivePulseStreamVelocity = 0,
	/// @brief Uses analog input 0 to determine the waveform scaling value.
	Automation1PsoWaveformScalingInput_AnalogInput0 = 1,
	/// @brief Uses analog input 1 to determine the waveform scaling value.
	Automation1PsoWaveformScalingInput_AnalogInput1 = 2,
	/// @brief Uses analog input 2 to determine the waveform scaling value.
	Automation1PsoWaveformScalingInput_AnalogInput2 = 3,
	/// @brief Uses analog input 3 to determine the waveform scaling value.
	Automation1PsoWaveformScalingInput_AnalogInput3 = 4,
} Automation1PsoWaveformScalingInput;

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
	/// @brief The PSO output will have a rising edge when a data collection sample is taken.
	Automation1PsoOutputSource_DataCollectionSyncPulse = 5,
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

/// @brief Represents a joystick input.
typedef enum Automation1JoystickInput
{
	/// @brief The first joystick input.
	Automation1JoystickInput_Input0 = 0,
	/// @brief The second joystick input.
	Automation1JoystickInput_Input1 = 1,
	/// @brief The third joystick input.
	Automation1JoystickInput_Input2 = 2,
} Automation1JoystickInput;

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
	/// @brief Snap.
	Automation1FeedforwardGain_GainSff = 4,
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
	/// @brief The controller will use the DriveEncoderOutputConfigureInput() configuration to determine if the output signal is Quadrature or Clock and Direction.
	Automation1EncoderOutputMode_Default = 0,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to Default. Use Default instead of this enum value.
	Automation1EncoderOutputMode_Quadrature = 0,
} Automation1EncoderOutputMode;

/// @brief The signal mode used when DriveEncoderOutputConfigureInput() and DriveEncoderOutputOn() are configured to echo the Pulse Stream signal to an encoder output.
typedef enum Automation1DrivePulseStreamSignalMode
{
	/// @brief Quadrature mode.
	Automation1DrivePulseStreamSignalMode_Quadrature = 0,
	/// @brief Clock and Direction mode.
	Automation1DrivePulseStreamSignalMode_ClockDirection = 1,
} Automation1DrivePulseStreamSignalMode;

/// @brief Specifies the event which causes a new analog output value to be read from the drive array and sent to the output.
typedef enum Automation1AnalogOutputUpdateEvent
{
	/// @brief Updates will occur at a specific rate.
	Automation1AnalogOutputUpdateEvent_Time = 0,
	/// @brief Updates will occur on a PSO event.
	Automation1AnalogOutputUpdateEvent_PsoEvent = 1,
	/// @brief Updates will occur on the rising edge of PSO output.
	Automation1AnalogOutputUpdateEvent_PsoOutput = 2,
} Automation1AnalogOutputUpdateEvent;

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
	/// @brief Position Feedback.
	Automation1DriveDataCaptureInput_PositionFeedback = 7,
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
	/// @brief Auxiliary Marker rising edge.
	Automation1DriveDataCaptureTrigger_AuxiliaryMarkerRisingEdge = 6,
	/// @brief Auxiliary Marker falling edge.
	Automation1DriveDataCaptureTrigger_AuxiliaryMarkerFallingEdge = 7,
} Automation1DriveDataCaptureTrigger;

/// @brief Specifies the type of drive array feature to use.
typedef enum Automation1DriveArrayType
{
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
	Automation1PsoDistanceInput_GL4PrimaryFeedbackAxis1 = 100,
	/// @brief GL4 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_GL4PrimaryFeedbackAxis2 = 101,
	/// @brief GL4 Primary Feedback Axis 1 with IFOV input.
	Automation1PsoDistanceInput_GL4IfovFeedbackAxis1 = 102,
	/// @brief GL4 Primary Feedback Axis 2 with IFOV input.
	Automation1PsoDistanceInput_GL4IfovFeedbackAxis2 = 103,
	/// @brief GL4 Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_GL4AuxiliaryFeedbackAxis1 = 104,
	/// @brief GL4 Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_GL4AuxiliaryFeedbackAxis2 = 105,
	/// @brief GL4 Sync Port A.
	Automation1PsoDistanceInput_GL4SyncPortA = 106,
	/// @brief GL4 Sync Port B.
	Automation1PsoDistanceInput_GL4SyncPortB = 107,
	/// @brief GL4 Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_GL4DrivePulseStreamAxis1 = 108,
	/// @brief GL4 Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_GL4DrivePulseStreamAxis2 = 109,
	/// @brief XL4s Primary Feedback.
	Automation1PsoDistanceInput_XL4sPrimaryFeedback = 110,
	/// @brief XL4s Auxiliary Feedback.
	Automation1PsoDistanceInput_XL4sAuxiliaryFeedback = 111,
	/// @brief XL4s Sync Port A.
	Automation1PsoDistanceInput_XL4sSyncPortA = 112,
	/// @brief XL4s Sync Port B.
	Automation1PsoDistanceInput_XL4sSyncPortB = 113,
	/// @brief XL4s Drive Pulse Stream.
	Automation1PsoDistanceInput_XL4sDrivePulseStream = 114,
	/// @brief XR3 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis1 = 115,
	/// @brief XR3 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis2 = 116,
	/// @brief XR3 Primary Feedback Axis 3.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis3 = 117,
	/// @brief XR3 Primary Feedback Axis 4.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis4 = 118,
	/// @brief XR3 Primary Feedback Axis 5.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis5 = 119,
	/// @brief XR3 Primary Feedback Axis 6.
	Automation1PsoDistanceInput_XR3PrimaryFeedbackAxis6 = 120,
	/// @brief XR3 Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis1 = 121,
	/// @brief XR3 Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis2 = 122,
	/// @brief XR3 Auxiliary Feedback Axis 3.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis3 = 123,
	/// @brief XR3 Auxiliary Feedback Axis 4.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis4 = 124,
	/// @brief XR3 Auxiliary Feedback Axis 5.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis5 = 125,
	/// @brief XR3 Auxiliary Feedback Axis 6.
	Automation1PsoDistanceInput_XR3AuxiliaryFeedbackAxis6 = 126,
	/// @brief XR3 Sync Port A.
	Automation1PsoDistanceInput_XR3SyncPortA = 127,
	/// @brief XR3 Sync Port B.
	Automation1PsoDistanceInput_XR3SyncPortB = 128,
	/// @brief XR3 Drive Pulse Stream.
	Automation1PsoDistanceInput_XR3DrivePulseStream = 129,
	/// @brief XC4 Primary Feedback.
	Automation1PsoDistanceInput_XC4PrimaryFeedback = 130,
	/// @brief XC4 Auxiliary Feedback.
	Automation1PsoDistanceInput_XC4AuxiliaryFeedback = 131,
	/// @brief XC4 Sync Port A.
	Automation1PsoDistanceInput_XC4SyncPortA = 132,
	/// @brief XC4 Sync Port B.
	Automation1PsoDistanceInput_XC4SyncPortB = 133,
	/// @brief XC4 Drive Pulse Stream.
	Automation1PsoDistanceInput_XC4DrivePulseStream = 134,
	/// @brief XC4e Primary Feedback.
	Automation1PsoDistanceInput_XC4ePrimaryFeedback = 135,
	/// @brief XC4e Auxiliary Feedback.
	Automation1PsoDistanceInput_XC4eAuxiliaryFeedback = 136,
	/// @brief XC4e Sync Port A.
	Automation1PsoDistanceInput_XC4eSyncPortA = 137,
	/// @brief XC4e Sync Port B.
	Automation1PsoDistanceInput_XC4eSyncPortB = 138,
	/// @brief XC4e Drive Pulse Stream.
	Automation1PsoDistanceInput_XC4eDrivePulseStream = 139,
	/// @brief XC6e Primary Feedback.
	Automation1PsoDistanceInput_XC6ePrimaryFeedback = 140,
	/// @brief XC6e Auxiliary Feedback.
	Automation1PsoDistanceInput_XC6eAuxiliaryFeedback = 141,
	/// @brief XC6e Sync Port A.
	Automation1PsoDistanceInput_XC6eSyncPortA = 142,
	/// @brief XC6e Sync Port B.
	Automation1PsoDistanceInput_XC6eSyncPortB = 143,
	/// @brief XC6e Drive Pulse Stream.
	Automation1PsoDistanceInput_XC6eDrivePulseStream = 144,
	/// @brief XL5e Primary Feedback.
	Automation1PsoDistanceInput_XL5ePrimaryFeedback = 145,
	/// @brief XL5e Auxiliary Feedback.
	Automation1PsoDistanceInput_XL5eAuxiliaryFeedback = 146,
	/// @brief XL5e Sync Port A.
	Automation1PsoDistanceInput_XL5eSyncPortA = 147,
	/// @brief XL5e Sync Port B.
	Automation1PsoDistanceInput_XL5eSyncPortB = 148,
	/// @brief XL5e Drive Pulse Stream.
	Automation1PsoDistanceInput_XL5eDrivePulseStream = 149,
	/// @brief XC2 Primary Feedback.
	Automation1PsoDistanceInput_XC2PrimaryFeedback = 150,
	/// @brief XC2 Auxiliary Feedback.
	Automation1PsoDistanceInput_XC2AuxiliaryFeedback = 151,
	/// @brief XC2 Drive Pulse Stream.
	Automation1PsoDistanceInput_XC2DrivePulseStream = 152,
	/// @brief XC2e Primary Feedback.
	Automation1PsoDistanceInput_XC2ePrimaryFeedback = 153,
	/// @brief XC2e Auxiliary Feedback.
	Automation1PsoDistanceInput_XC2eAuxiliaryFeedback = 154,
	/// @brief XC2e Drive Pulse Stream.
	Automation1PsoDistanceInput_XC2eDrivePulseStream = 155,
	/// @brief XL2e Primary Feedback.
	Automation1PsoDistanceInput_XL2ePrimaryFeedback = 156,
	/// @brief XL2e Auxiliary Feedback.
	Automation1PsoDistanceInput_XL2eAuxiliaryFeedback = 157,
	/// @brief XL2e Sync Port A.
	Automation1PsoDistanceInput_XL2eSyncPortA = 158,
	/// @brief XL2e Sync Port B.
	Automation1PsoDistanceInput_XL2eSyncPortB = 159,
	/// @brief XL2e Drive Pulse Stream.
	Automation1PsoDistanceInput_XL2eDrivePulseStream = 160,
	/// @brief XI4 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_XI4PrimaryFeedbackAxis1 = 161,
	/// @brief XI4 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_XI4PrimaryFeedbackAxis2 = 162,
	/// @brief XI4 Primary Feedback Axis 3.
	Automation1PsoDistanceInput_XI4PrimaryFeedbackAxis3 = 163,
	/// @brief XI4 Primary Feedback Axis 4.
	Automation1PsoDistanceInput_XI4PrimaryFeedbackAxis4 = 164,
	/// @brief XI4 Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedbackAxis1 = 165,
	/// @brief XI4 Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedbackAxis2 = 166,
	/// @brief XI4 Auxiliary Feedback Axis 3.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedbackAxis3 = 167,
	/// @brief XI4 Auxiliary Feedback Axis 4.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedbackAxis4 = 168,
	/// @brief XI4 Sync Port A.
	Automation1PsoDistanceInput_XI4SyncPortA = 169,
	/// @brief XI4 Sync Port B.
	Automation1PsoDistanceInput_XI4SyncPortB = 170,
	/// @brief XI4 Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_XI4DrivePulseStreamAxis1 = 171,
	/// @brief XI4 Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_XI4DrivePulseStreamAxis2 = 172,
	/// @brief XI4 Drive Pulse Stream Axis 3.
	Automation1PsoDistanceInput_XI4DrivePulseStreamAxis3 = 173,
	/// @brief XI4 Drive Pulse Stream Axis 4.
	Automation1PsoDistanceInput_XI4DrivePulseStreamAxis4 = 174,
	/// @brief iXC4 Primary Feedback.
	Automation1PsoDistanceInput_iXC4PrimaryFeedback = 175,
	/// @brief iXC4 Auxiliary Feedback.
	Automation1PsoDistanceInput_iXC4AuxiliaryFeedback = 176,
	/// @brief iXC4 Sync Port A.
	Automation1PsoDistanceInput_iXC4SyncPortA = 177,
	/// @brief iXC4 Sync Port B.
	Automation1PsoDistanceInput_iXC4SyncPortB = 178,
	/// @brief iXC4 Drive Pulse Stream.
	Automation1PsoDistanceInput_iXC4DrivePulseStream = 179,
	/// @brief iXC4e Primary Feedback.
	Automation1PsoDistanceInput_iXC4ePrimaryFeedback = 180,
	/// @brief iXC4e Auxiliary Feedback.
	Automation1PsoDistanceInput_iXC4eAuxiliaryFeedback = 181,
	/// @brief iXC4e Sync Port A.
	Automation1PsoDistanceInput_iXC4eSyncPortA = 182,
	/// @brief iXC4e Sync Port B.
	Automation1PsoDistanceInput_iXC4eSyncPortB = 183,
	/// @brief iXC4e Drive Pulse Stream.
	Automation1PsoDistanceInput_iXC4eDrivePulseStream = 184,
	/// @brief iXC6e Primary Feedback.
	Automation1PsoDistanceInput_iXC6ePrimaryFeedback = 185,
	/// @brief iXC6e Auxiliary Feedback.
	Automation1PsoDistanceInput_iXC6eAuxiliaryFeedback = 186,
	/// @brief iXC6e Sync Port A.
	Automation1PsoDistanceInput_iXC6eSyncPortA = 187,
	/// @brief iXC6e Sync Port B.
	Automation1PsoDistanceInput_iXC6eSyncPortB = 188,
	/// @brief iXC6e Drive Pulse Stream.
	Automation1PsoDistanceInput_iXC6eDrivePulseStream = 189,
	/// @brief iXL5e Primary Feedback.
	Automation1PsoDistanceInput_iXL5ePrimaryFeedback = 190,
	/// @brief iXL5e Auxiliary Feedback.
	Automation1PsoDistanceInput_iXL5eAuxiliaryFeedback = 191,
	/// @brief iXL5e Sync Port A.
	Automation1PsoDistanceInput_iXL5eSyncPortA = 192,
	/// @brief iXL5e Sync Port B.
	Automation1PsoDistanceInput_iXL5eSyncPortB = 193,
	/// @brief iXL5e Drive Pulse Stream.
	Automation1PsoDistanceInput_iXL5eDrivePulseStream = 194,
	/// @brief iXR3 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis1 = 195,
	/// @brief iXR3 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis2 = 196,
	/// @brief iXR3 Primary Feedback Axis 3.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis3 = 197,
	/// @brief iXR3 Primary Feedback Axis 4.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis4 = 198,
	/// @brief iXR3 Primary Feedback Axis 5.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis5 = 199,
	/// @brief iXR3 Primary Feedback Axis 6.
	Automation1PsoDistanceInput_iXR3PrimaryFeedbackAxis6 = 200,
	/// @brief iXR3 Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis1 = 201,
	/// @brief iXR3 Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis2 = 202,
	/// @brief iXR3 Auxiliary Feedback Axis 3.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis3 = 203,
	/// @brief iXR3 Auxiliary Feedback Axis 4.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis4 = 204,
	/// @brief iXR3 Auxiliary Feedback Axis 5.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis5 = 205,
	/// @brief iXR3 Auxiliary Feedback Axis 6.
	Automation1PsoDistanceInput_iXR3AuxiliaryFeedbackAxis6 = 206,
	/// @brief iXR3 Sync Port A.
	Automation1PsoDistanceInput_iXR3SyncPortA = 207,
	/// @brief iXR3 Sync Port B.
	Automation1PsoDistanceInput_iXR3SyncPortB = 208,
	/// @brief iXR3 Drive Pulse Stream.
	Automation1PsoDistanceInput_iXR3DrivePulseStream = 209,
	/// @brief GI4 Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_GI4DrivePulseStreamAxis1 = 210,
	/// @brief GI4 Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_GI4DrivePulseStreamAxis2 = 211,
	/// @brief GI4 Drive Pulse Stream Axis 3.
	Automation1PsoDistanceInput_GI4DrivePulseStreamAxis3 = 212,
	/// @brief iXC2 Primary Feedback.
	Automation1PsoDistanceInput_iXC2PrimaryFeedback = 213,
	/// @brief iXC2 Auxiliary Feedback.
	Automation1PsoDistanceInput_iXC2AuxiliaryFeedback = 214,
	/// @brief iXC2 Drive Pulse Stream.
	Automation1PsoDistanceInput_iXC2DrivePulseStream = 215,
	/// @brief iXC2e Primary Feedback.
	Automation1PsoDistanceInput_iXC2ePrimaryFeedback = 216,
	/// @brief iXC2e Auxiliary Feedback.
	Automation1PsoDistanceInput_iXC2eAuxiliaryFeedback = 217,
	/// @brief iXC2e Drive Pulse Stream.
	Automation1PsoDistanceInput_iXC2eDrivePulseStream = 218,
	/// @brief iXL2e Primary Feedback.
	Automation1PsoDistanceInput_iXL2ePrimaryFeedback = 219,
	/// @brief iXL2e Auxiliary Feedback.
	Automation1PsoDistanceInput_iXL2eAuxiliaryFeedback = 220,
	/// @brief iXL2e Sync Port A.
	Automation1PsoDistanceInput_iXL2eSyncPortA = 221,
	/// @brief iXL2e Sync Port B.
	Automation1PsoDistanceInput_iXL2eSyncPortB = 222,
	/// @brief iXL2e Drive Pulse Stream.
	Automation1PsoDistanceInput_iXL2eDrivePulseStream = 223,
	/// @brief iXI4 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_iXI4PrimaryFeedbackAxis1 = 224,
	/// @brief iXI4 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_iXI4PrimaryFeedbackAxis2 = 225,
	/// @brief iXI4 Primary Feedback Axis 3.
	Automation1PsoDistanceInput_iXI4PrimaryFeedbackAxis3 = 226,
	/// @brief iXI4 Primary Feedback Axis 4.
	Automation1PsoDistanceInput_iXI4PrimaryFeedbackAxis4 = 227,
	/// @brief iXI4 Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_iXI4AuxiliaryFeedbackAxis1 = 228,
	/// @brief iXI4 Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_iXI4AuxiliaryFeedbackAxis2 = 229,
	/// @brief iXI4 Auxiliary Feedback Axis 3.
	Automation1PsoDistanceInput_iXI4AuxiliaryFeedbackAxis3 = 230,
	/// @brief iXI4 Auxiliary Feedback Axis 4.
	Automation1PsoDistanceInput_iXI4AuxiliaryFeedbackAxis4 = 231,
	/// @brief iXI4 Sync Port A.
	Automation1PsoDistanceInput_iXI4SyncPortA = 232,
	/// @brief iXI4 Sync Port B.
	Automation1PsoDistanceInput_iXI4SyncPortB = 233,
	/// @brief iXI4 Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_iXI4DrivePulseStreamAxis1 = 234,
	/// @brief iXI4 Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_iXI4DrivePulseStreamAxis2 = 235,
	/// @brief iXI4 Drive Pulse Stream Axis 3.
	Automation1PsoDistanceInput_iXI4DrivePulseStreamAxis3 = 236,
	/// @brief iXI4 Drive Pulse Stream Axis 4.
	Automation1PsoDistanceInput_iXI4DrivePulseStreamAxis4 = 237,
	/// @brief FLEX Primary Feedback Axis 1.
	Automation1PsoDistanceInput_FLEXPrimaryFeedbackAxis1 = 238,
	/// @brief FLEX Primary Feedback Axis 2.
	Automation1PsoDistanceInput_FLEXPrimaryFeedbackAxis2 = 239,
	/// @brief FLEX Primary Feedback Axis 3.
	Automation1PsoDistanceInput_FLEXPrimaryFeedbackAxis3 = 240,
	/// @brief FLEX Primary Feedback Axis 4.
	Automation1PsoDistanceInput_FLEXPrimaryFeedbackAxis4 = 241,
	/// @brief FLEX Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_FLEXAuxiliaryFeedbackAxis1 = 242,
	/// @brief FLEX Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_FLEXAuxiliaryFeedbackAxis2 = 243,
	/// @brief FLEX Auxiliary Feedback Axis 3.
	Automation1PsoDistanceInput_FLEXAuxiliaryFeedbackAxis3 = 244,
	/// @brief FLEX Auxiliary Feedback Axis 4.
	Automation1PsoDistanceInput_FLEXAuxiliaryFeedbackAxis4 = 245,
	/// @brief FLEX Sync Port A.
	Automation1PsoDistanceInput_FLEXSyncPortA = 246,
	/// @brief FLEX Sync Port B.
	Automation1PsoDistanceInput_FLEXSyncPortB = 247,
	/// @brief FLEX Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_FLEXDrivePulseStreamAxis1 = 248,
	/// @brief FLEX Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_FLEXDrivePulseStreamAxis2 = 249,
	/// @brief FLEX Drive Pulse Stream Axis 3.
	Automation1PsoDistanceInput_FLEXDrivePulseStreamAxis3 = 250,
	/// @brief FLEX Drive Pulse Stream Axis 4.
	Automation1PsoDistanceInput_FLEXDrivePulseStreamAxis4 = 251,
	/// @brief iFLEX Primary Feedback Axis 1.
	Automation1PsoDistanceInput_iFLEXPrimaryFeedbackAxis1 = 252,
	/// @brief iFLEX Primary Feedback Axis 2.
	Automation1PsoDistanceInput_iFLEXPrimaryFeedbackAxis2 = 253,
	/// @brief iFLEX Primary Feedback Axis 3.
	Automation1PsoDistanceInput_iFLEXPrimaryFeedbackAxis3 = 254,
	/// @brief iFLEX Primary Feedback Axis 4.
	Automation1PsoDistanceInput_iFLEXPrimaryFeedbackAxis4 = 255,
	/// @brief iFLEX Auxiliary Feedback Axis 1.
	Automation1PsoDistanceInput_iFLEXAuxiliaryFeedbackAxis1 = 256,
	/// @brief iFLEX Auxiliary Feedback Axis 2.
	Automation1PsoDistanceInput_iFLEXAuxiliaryFeedbackAxis2 = 257,
	/// @brief iFLEX Auxiliary Feedback Axis 3.
	Automation1PsoDistanceInput_iFLEXAuxiliaryFeedbackAxis3 = 258,
	/// @brief iFLEX Auxiliary Feedback Axis 4.
	Automation1PsoDistanceInput_iFLEXAuxiliaryFeedbackAxis4 = 259,
	/// @brief iFLEX Sync Port A.
	Automation1PsoDistanceInput_iFLEXSyncPortA = 260,
	/// @brief iFLEX Sync Port B.
	Automation1PsoDistanceInput_iFLEXSyncPortB = 261,
	/// @brief iFLEX Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_iFLEXDrivePulseStreamAxis1 = 262,
	/// @brief iFLEX Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_iFLEXDrivePulseStreamAxis2 = 263,
	/// @brief iFLEX Drive Pulse Stream Axis 3.
	Automation1PsoDistanceInput_iFLEXDrivePulseStreamAxis3 = 264,
	/// @brief iFLEX Drive Pulse Stream Axis 4.
	Automation1PsoDistanceInput_iFLEXDrivePulseStreamAxis4 = 265,
	/// @brief XA4 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_XA4PrimaryFeedbackAxis1 = 266,
	/// @brief XA4 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_XA4PrimaryFeedbackAxis2 = 267,
	/// @brief XA4 Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_XA4DrivePulseStreamAxis1 = 268,
	/// @brief XA4 Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_XA4DrivePulseStreamAxis2 = 269,
	/// @brief iXA4 Primary Feedback Axis 1.
	Automation1PsoDistanceInput_iXA4PrimaryFeedbackAxis1 = 270,
	/// @brief iXA4 Primary Feedback Axis 2.
	Automation1PsoDistanceInput_iXA4PrimaryFeedbackAxis2 = 271,
	/// @brief iXA4 Drive Pulse Stream Axis 1.
	Automation1PsoDistanceInput_iXA4DrivePulseStreamAxis1 = 272,
	/// @brief iXA4 Drive Pulse Stream Axis 2.
	Automation1PsoDistanceInput_iXA4DrivePulseStreamAxis2 = 273,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to XI4AuxiliaryFeedbackAxis1. Use XI4AuxiliaryFeedbackAxis1 instead of this enum value.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedback1 = 165,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to XI4AuxiliaryFeedbackAxis2. Use XI4AuxiliaryFeedbackAxis2 instead of this enum value.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedback2 = 166,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to XI4AuxiliaryFeedbackAxis3. Use XI4AuxiliaryFeedbackAxis3 instead of this enum value.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedback3 = 167,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to XI4AuxiliaryFeedbackAxis4. Use XI4AuxiliaryFeedbackAxis4 instead of this enum value.
	Automation1PsoDistanceInput_XI4AuxiliaryFeedback4 = 168,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to iXI4AuxiliaryFeedbackAxis1. Use iXI4AuxiliaryFeedbackAxis1 instead of this enum value.
	Automation1PsoDistanceInput_iXI4AuxiliaryFeedback1 = 228,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to iXI4AuxiliaryFeedbackAxis2. Use iXI4AuxiliaryFeedbackAxis2 instead of this enum value.
	Automation1PsoDistanceInput_iXI4AuxiliaryFeedback2 = 229,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to iXI4AuxiliaryFeedbackAxis3. Use iXI4AuxiliaryFeedbackAxis3 instead of this enum value.
	Automation1PsoDistanceInput_iXI4AuxiliaryFeedback3 = 230,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to iXI4AuxiliaryFeedbackAxis4. Use iXI4AuxiliaryFeedbackAxis4 instead of this enum value.
	Automation1PsoDistanceInput_iXI4AuxiliaryFeedback4 = 231,
} Automation1PsoDistanceInput;

/// @brief Specifies the PSO window input settings for each drive.
typedef enum Automation1PsoWindowInput
{
	/// @brief GL4 Primary Feedback Axis 1.
	Automation1PsoWindowInput_GL4PrimaryFeedbackAxis1 = 100,
	/// @brief GL4 Primary Feedback Axis 2.
	Automation1PsoWindowInput_GL4PrimaryFeedbackAxis2 = 101,
	/// @brief GL4 Primary Feedback Axis 1 with IFOV input.
	Automation1PsoWindowInput_GL4IfovFeedbackAxis1 = 102,
	/// @brief GL4 Primary Feedback Axis 2 with IFOV input.
	Automation1PsoWindowInput_GL4IfovFeedbackAxis2 = 103,
	/// @brief GL4 Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_GL4AuxiliaryFeedbackAxis1 = 104,
	/// @brief GL4 Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_GL4AuxiliaryFeedbackAxis2 = 105,
	/// @brief GL4 Sync Port A.
	Automation1PsoWindowInput_GL4SyncPortA = 106,
	/// @brief GL4 Sync Port B.
	Automation1PsoWindowInput_GL4SyncPortB = 107,
	/// @brief GL4 Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_GL4DrivePulseStreamAxis1 = 108,
	/// @brief GL4 Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_GL4DrivePulseStreamAxis2 = 109,
	/// @brief XL4s Primary Feedback.
	Automation1PsoWindowInput_XL4sPrimaryFeedback = 110,
	/// @brief XL4s Auxiliary Feedback.
	Automation1PsoWindowInput_XL4sAuxiliaryFeedback = 111,
	/// @brief XL4s Sync Port A.
	Automation1PsoWindowInput_XL4sSyncPortA = 112,
	/// @brief XL4s Sync Port B.
	Automation1PsoWindowInput_XL4sSyncPortB = 113,
	/// @brief XL4s Drive Pulse Stream.
	Automation1PsoWindowInput_XL4sDrivePulseStream = 114,
	/// @brief XR3 Primary Feedback Axis 1.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis1 = 115,
	/// @brief XR3 Primary Feedback Axis 2.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis2 = 116,
	/// @brief XR3 Primary Feedback Axis 3.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis3 = 117,
	/// @brief XR3 Primary Feedback Axis 4.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis4 = 118,
	/// @brief XR3 Primary Feedback Axis 5.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis5 = 119,
	/// @brief XR3 Primary Feedback Axis 6.
	Automation1PsoWindowInput_XR3PrimaryFeedbackAxis6 = 120,
	/// @brief XR3 Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis1 = 121,
	/// @brief XR3 Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis2 = 122,
	/// @brief XR3 Auxiliary Feedback Axis 3.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis3 = 123,
	/// @brief XR3 Auxiliary Feedback Axis 4.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis4 = 124,
	/// @brief XR3 Auxiliary Feedback Axis 5.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis5 = 125,
	/// @brief XR3 Auxiliary Feedback Axis 6.
	Automation1PsoWindowInput_XR3AuxiliaryFeedbackAxis6 = 126,
	/// @brief XR3 Sync Port A.
	Automation1PsoWindowInput_XR3SyncPortA = 127,
	/// @brief XR3 Sync Port B.
	Automation1PsoWindowInput_XR3SyncPortB = 128,
	/// @brief XR3 Drive Pulse Stream.
	Automation1PsoWindowInput_XR3DrivePulseStream = 129,
	/// @brief XC4 Primary Feedback.
	Automation1PsoWindowInput_XC4PrimaryFeedback = 130,
	/// @brief XC4 Auxiliary Feedback.
	Automation1PsoWindowInput_XC4AuxiliaryFeedback = 131,
	/// @brief XC4 Sync Port A.
	Automation1PsoWindowInput_XC4SyncPortA = 132,
	/// @brief XC4 Sync Port B.
	Automation1PsoWindowInput_XC4SyncPortB = 133,
	/// @brief XC4 Drive Pulse Stream.
	Automation1PsoWindowInput_XC4DrivePulseStream = 134,
	/// @brief XC4e Primary Feedback.
	Automation1PsoWindowInput_XC4ePrimaryFeedback = 135,
	/// @brief XC4e Auxiliary Feedback.
	Automation1PsoWindowInput_XC4eAuxiliaryFeedback = 136,
	/// @brief XC4e Sync Port A.
	Automation1PsoWindowInput_XC4eSyncPortA = 137,
	/// @brief XC4e Sync Port B.
	Automation1PsoWindowInput_XC4eSyncPortB = 138,
	/// @brief XC4e Drive Pulse Stream.
	Automation1PsoWindowInput_XC4eDrivePulseStream = 139,
	/// @brief XC6e Primary Feedback.
	Automation1PsoWindowInput_XC6ePrimaryFeedback = 140,
	/// @brief XC6e Auxiliary Feedback.
	Automation1PsoWindowInput_XC6eAuxiliaryFeedback = 141,
	/// @brief XC6e Sync Port A.
	Automation1PsoWindowInput_XC6eSyncPortA = 142,
	/// @brief XC6e Sync Port B.
	Automation1PsoWindowInput_XC6eSyncPortB = 143,
	/// @brief XC6e Drive Pulse Stream.
	Automation1PsoWindowInput_XC6eDrivePulseStream = 144,
	/// @brief XL5e Primary Feedback.
	Automation1PsoWindowInput_XL5ePrimaryFeedback = 145,
	/// @brief XL5e Auxiliary Feedback.
	Automation1PsoWindowInput_XL5eAuxiliaryFeedback = 146,
	/// @brief XL5e Sync Port A.
	Automation1PsoWindowInput_XL5eSyncPortA = 147,
	/// @brief XL5e Sync Port B.
	Automation1PsoWindowInput_XL5eSyncPortB = 148,
	/// @brief XL5e Drive Pulse Stream.
	Automation1PsoWindowInput_XL5eDrivePulseStream = 149,
	/// @brief XC2 Primary Feedback.
	Automation1PsoWindowInput_XC2PrimaryFeedback = 150,
	/// @brief XC2 Auxiliary Feedback.
	Automation1PsoWindowInput_XC2AuxiliaryFeedback = 151,
	/// @brief XC2 Drive Pulse Stream.
	Automation1PsoWindowInput_XC2DrivePulseStream = 152,
	/// @brief XC2e Primary Feedback.
	Automation1PsoWindowInput_XC2ePrimaryFeedback = 153,
	/// @brief XC2e Auxiliary Feedback.
	Automation1PsoWindowInput_XC2eAuxiliaryFeedback = 154,
	/// @brief XC2e Drive Pulse Stream.
	Automation1PsoWindowInput_XC2eDrivePulseStream = 155,
	/// @brief XL2e Primary Feedback.
	Automation1PsoWindowInput_XL2ePrimaryFeedback = 156,
	/// @brief XL2e Auxiliary Feedback.
	Automation1PsoWindowInput_XL2eAuxiliaryFeedback = 157,
	/// @brief XL2e Sync Port A.
	Automation1PsoWindowInput_XL2eSyncPortA = 158,
	/// @brief XL2e Sync Port B.
	Automation1PsoWindowInput_XL2eSyncPortB = 159,
	/// @brief XL2e Drive Pulse Stream.
	Automation1PsoWindowInput_XL2eDrivePulseStream = 160,
	/// @brief XI4 Primary Feedback Axis 1.
	Automation1PsoWindowInput_XI4PrimaryFeedbackAxis1 = 161,
	/// @brief XI4 Primary Feedback Axis 2.
	Automation1PsoWindowInput_XI4PrimaryFeedbackAxis2 = 162,
	/// @brief XI4 Primary Feedback Axis 3.
	Automation1PsoWindowInput_XI4PrimaryFeedbackAxis3 = 163,
	/// @brief XI4 Primary Feedback Axis 4.
	Automation1PsoWindowInput_XI4PrimaryFeedbackAxis4 = 164,
	/// @brief XI4 Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_XI4AuxiliaryFeedbackAxis1 = 165,
	/// @brief XI4 Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_XI4AuxiliaryFeedbackAxis2 = 166,
	/// @brief XI4 Auxiliary Feedback Axis 3.
	Automation1PsoWindowInput_XI4AuxiliaryFeedbackAxis3 = 167,
	/// @brief XI4 Auxiliary Feedback Axis 4.
	Automation1PsoWindowInput_XI4AuxiliaryFeedbackAxis4 = 168,
	/// @brief XI4 Sync Port A.
	Automation1PsoWindowInput_XI4SyncPortA = 169,
	/// @brief XI4 Sync Port B.
	Automation1PsoWindowInput_XI4SyncPortB = 170,
	/// @brief XI4 Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_XI4DrivePulseStreamAxis1 = 171,
	/// @brief XI4 Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_XI4DrivePulseStreamAxis2 = 172,
	/// @brief XI4 Drive Pulse Stream Axis 3.
	Automation1PsoWindowInput_XI4DrivePulseStreamAxis3 = 173,
	/// @brief XI4 Drive Pulse Stream Axis 4.
	Automation1PsoWindowInput_XI4DrivePulseStreamAxis4 = 174,
	/// @brief iXC4 Primary Feedback.
	Automation1PsoWindowInput_iXC4PrimaryFeedback = 175,
	/// @brief iXC4 Auxiliary Feedback.
	Automation1PsoWindowInput_iXC4AuxiliaryFeedback = 176,
	/// @brief iXC4 Sync Port A.
	Automation1PsoWindowInput_iXC4SyncPortA = 177,
	/// @brief iXC4 Sync Port B.
	Automation1PsoWindowInput_iXC4SyncPortB = 178,
	/// @brief iXC4 Drive Pulse Stream.
	Automation1PsoWindowInput_iXC4DrivePulseStream = 179,
	/// @brief iXC4e Primary Feedback.
	Automation1PsoWindowInput_iXC4ePrimaryFeedback = 180,
	/// @brief iXC4e Auxiliary Feedback.
	Automation1PsoWindowInput_iXC4eAuxiliaryFeedback = 181,
	/// @brief iXC4e Sync Port A.
	Automation1PsoWindowInput_iXC4eSyncPortA = 182,
	/// @brief iXC4e Sync Port B.
	Automation1PsoWindowInput_iXC4eSyncPortB = 183,
	/// @brief iXC4e Drive Pulse Stream.
	Automation1PsoWindowInput_iXC4eDrivePulseStream = 184,
	/// @brief iXC6e Primary Feedback.
	Automation1PsoWindowInput_iXC6ePrimaryFeedback = 185,
	/// @brief iXC6e Auxiliary Feedback.
	Automation1PsoWindowInput_iXC6eAuxiliaryFeedback = 186,
	/// @brief iXC6e Sync Port A.
	Automation1PsoWindowInput_iXC6eSyncPortA = 187,
	/// @brief iXC6e Sync Port B.
	Automation1PsoWindowInput_iXC6eSyncPortB = 188,
	/// @brief iXC6e Drive Pulse Stream.
	Automation1PsoWindowInput_iXC6eDrivePulseStream = 189,
	/// @brief iXL5e Primary Feedback.
	Automation1PsoWindowInput_iXL5ePrimaryFeedback = 190,
	/// @brief iXL5e Auxiliary Feedback.
	Automation1PsoWindowInput_iXL5eAuxiliaryFeedback = 191,
	/// @brief iXL5e Sync Port A.
	Automation1PsoWindowInput_iXL5eSyncPortA = 192,
	/// @brief iXL5e Sync Port B.
	Automation1PsoWindowInput_iXL5eSyncPortB = 193,
	/// @brief iXL5e Drive Pulse Stream.
	Automation1PsoWindowInput_iXL5eDrivePulseStream = 194,
	/// @brief iXR3 Primary Feedback Axis 1.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis1 = 195,
	/// @brief iXR3 Primary Feedback Axis 2.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis2 = 196,
	/// @brief iXR3 Primary Feedback Axis 3.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis3 = 197,
	/// @brief iXR3 Primary Feedback Axis 4.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis4 = 198,
	/// @brief iXR3 Primary Feedback Axis 5.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis5 = 199,
	/// @brief iXR3 Primary Feedback Axis 6.
	Automation1PsoWindowInput_iXR3PrimaryFeedbackAxis6 = 200,
	/// @brief iXR3 Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis1 = 201,
	/// @brief iXR3 Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis2 = 202,
	/// @brief iXR3 Auxiliary Feedback Axis 3.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis3 = 203,
	/// @brief iXR3 Auxiliary Feedback Axis 4.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis4 = 204,
	/// @brief iXR3 Auxiliary Feedback Axis 5.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis5 = 205,
	/// @brief iXR3 Auxiliary Feedback Axis 6.
	Automation1PsoWindowInput_iXR3AuxiliaryFeedbackAxis6 = 206,
	/// @brief iXR3 Sync Port A.
	Automation1PsoWindowInput_iXR3SyncPortA = 207,
	/// @brief iXR3 Sync Port B.
	Automation1PsoWindowInput_iXR3SyncPortB = 208,
	/// @brief iXR3 Drive Pulse Stream.
	Automation1PsoWindowInput_iXR3DrivePulseStream = 209,
	/// @brief GI4 Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_GI4DrivePulseStreamAxis1 = 210,
	/// @brief GI4 Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_GI4DrivePulseStreamAxis2 = 211,
	/// @brief GI4 Drive Pulse Stream Axis 3.
	Automation1PsoWindowInput_GI4DrivePulseStreamAxis3 = 212,
	/// @brief iXC2 Primary Feedback.
	Automation1PsoWindowInput_iXC2PrimaryFeedback = 213,
	/// @brief iXC2 Auxiliary Feedback.
	Automation1PsoWindowInput_iXC2AuxiliaryFeedback = 214,
	/// @brief iXC2 Drive Pulse Stream.
	Automation1PsoWindowInput_iXC2DrivePulseStream = 215,
	/// @brief iXC2e Primary Feedback.
	Automation1PsoWindowInput_iXC2ePrimaryFeedback = 216,
	/// @brief iXC2e Auxiliary Feedback.
	Automation1PsoWindowInput_iXC2eAuxiliaryFeedback = 217,
	/// @brief iXC2e Drive Pulse Stream.
	Automation1PsoWindowInput_iXC2eDrivePulseStream = 218,
	/// @brief iXL2e Primary Feedback.
	Automation1PsoWindowInput_iXL2ePrimaryFeedback = 219,
	/// @brief iXL2e Auxiliary Feedback.
	Automation1PsoWindowInput_iXL2eAuxiliaryFeedback = 220,
	/// @brief iXL2e Sync Port A.
	Automation1PsoWindowInput_iXL2eSyncPortA = 221,
	/// @brief iXL2e Sync Port B.
	Automation1PsoWindowInput_iXL2eSyncPortB = 222,
	/// @brief iXL2e Drive Pulse Stream.
	Automation1PsoWindowInput_iXL2eDrivePulseStream = 223,
	/// @brief iXI4 Primary Feedback Axis 1.
	Automation1PsoWindowInput_iXI4PrimaryFeedbackAxis1 = 224,
	/// @brief iXI4 Primary Feedback Axis 2.
	Automation1PsoWindowInput_iXI4PrimaryFeedbackAxis2 = 225,
	/// @brief iXI4 Primary Feedback Axis 3.
	Automation1PsoWindowInput_iXI4PrimaryFeedbackAxis3 = 226,
	/// @brief iXI4 Primary Feedback Axis 4.
	Automation1PsoWindowInput_iXI4PrimaryFeedbackAxis4 = 227,
	/// @brief iXI4 Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_iXI4AuxiliaryFeedbackAxis1 = 228,
	/// @brief iXI4 Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_iXI4AuxiliaryFeedbackAxis2 = 229,
	/// @brief iXI4 Auxiliary Feedback Axis 3.
	Automation1PsoWindowInput_iXI4AuxiliaryFeedbackAxis3 = 230,
	/// @brief iXI4 Auxiliary Feedback Axis 4.
	Automation1PsoWindowInput_iXI4AuxiliaryFeedbackAxis4 = 231,
	/// @brief iXI4 Sync Port A.
	Automation1PsoWindowInput_iXI4SyncPortA = 232,
	/// @brief iXI4 Sync Port B.
	Automation1PsoWindowInput_iXI4SyncPortB = 233,
	/// @brief iXI4 Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_iXI4DrivePulseStreamAxis1 = 234,
	/// @brief iXI4 Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_iXI4DrivePulseStreamAxis2 = 235,
	/// @brief iXI4 Drive Pulse Stream Axis 3.
	Automation1PsoWindowInput_iXI4DrivePulseStreamAxis3 = 236,
	/// @brief iXI4 Drive Pulse Stream Axis 4.
	Automation1PsoWindowInput_iXI4DrivePulseStreamAxis4 = 237,
	/// @brief FLEX Primary Feedback Axis 1.
	Automation1PsoWindowInput_FLEXPrimaryFeedbackAxis1 = 238,
	/// @brief FLEX Primary Feedback Axis 2.
	Automation1PsoWindowInput_FLEXPrimaryFeedbackAxis2 = 239,
	/// @brief FLEX Primary Feedback Axis 3.
	Automation1PsoWindowInput_FLEXPrimaryFeedbackAxis3 = 240,
	/// @brief FLEX Primary Feedback Axis 4.
	Automation1PsoWindowInput_FLEXPrimaryFeedbackAxis4 = 241,
	/// @brief FLEX Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_FLEXAuxiliaryFeedbackAxis1 = 242,
	/// @brief FLEX Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_FLEXAuxiliaryFeedbackAxis2 = 243,
	/// @brief FLEX Auxiliary Feedback Axis 3.
	Automation1PsoWindowInput_FLEXAuxiliaryFeedbackAxis3 = 244,
	/// @brief FLEX Auxiliary Feedback Axis 4.
	Automation1PsoWindowInput_FLEXAuxiliaryFeedbackAxis4 = 245,
	/// @brief FLEX Sync Port A.
	Automation1PsoWindowInput_FLEXSyncPortA = 246,
	/// @brief FLEX Sync Port B.
	Automation1PsoWindowInput_FLEXSyncPortB = 247,
	/// @brief FLEX Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_FLEXDrivePulseStreamAxis1 = 248,
	/// @brief FLEX Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_FLEXDrivePulseStreamAxis2 = 249,
	/// @brief FLEX Drive Pulse Stream Axis 3.
	Automation1PsoWindowInput_FLEXDrivePulseStreamAxis3 = 250,
	/// @brief FLEX Drive Pulse Stream Axis 4.
	Automation1PsoWindowInput_FLEXDrivePulseStreamAxis4 = 251,
	/// @brief iFLEX Primary Feedback Axis 1.
	Automation1PsoWindowInput_iFLEXPrimaryFeedbackAxis1 = 252,
	/// @brief iFLEX Primary Feedback Axis 2.
	Automation1PsoWindowInput_iFLEXPrimaryFeedbackAxis2 = 253,
	/// @brief iFLEX Primary Feedback Axis 3.
	Automation1PsoWindowInput_iFLEXPrimaryFeedbackAxis3 = 254,
	/// @brief iFLEX Primary Feedback Axis 4.
	Automation1PsoWindowInput_iFLEXPrimaryFeedbackAxis4 = 255,
	/// @brief iFLEX Auxiliary Feedback Axis 1.
	Automation1PsoWindowInput_iFLEXAuxiliaryFeedbackAxis1 = 256,
	/// @brief iFLEX Auxiliary Feedback Axis 2.
	Automation1PsoWindowInput_iFLEXAuxiliaryFeedbackAxis2 = 257,
	/// @brief iFLEX Auxiliary Feedback Axis 3.
	Automation1PsoWindowInput_iFLEXAuxiliaryFeedbackAxis3 = 258,
	/// @brief iFLEX Auxiliary Feedback Axis 4.
	Automation1PsoWindowInput_iFLEXAuxiliaryFeedbackAxis4 = 259,
	/// @brief iFLEX Sync Port A.
	Automation1PsoWindowInput_iFLEXSyncPortA = 260,
	/// @brief iFLEX Sync Port B.
	Automation1PsoWindowInput_iFLEXSyncPortB = 261,
	/// @brief iFLEX Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_iFLEXDrivePulseStreamAxis1 = 262,
	/// @brief iFLEX Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_iFLEXDrivePulseStreamAxis2 = 263,
	/// @brief iFLEX Drive Pulse Stream Axis 3.
	Automation1PsoWindowInput_iFLEXDrivePulseStreamAxis3 = 264,
	/// @brief iFLEX Drive Pulse Stream Axis 4.
	Automation1PsoWindowInput_iFLEXDrivePulseStreamAxis4 = 265,
	/// @brief XA4 Primary Feedback Axis 1.
	Automation1PsoWindowInput_XA4PrimaryFeedbackAxis1 = 266,
	/// @brief XA4 Primary Feedback Axis 2.
	Automation1PsoWindowInput_XA4PrimaryFeedbackAxis2 = 267,
	/// @brief XA4 Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_XA4DrivePulseStreamAxis1 = 268,
	/// @brief XA4 Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_XA4DrivePulseStreamAxis2 = 269,
	/// @brief iXA4 Primary Feedback Axis 1.
	Automation1PsoWindowInput_iXA4PrimaryFeedbackAxis1 = 270,
	/// @brief iXA4 Primary Feedback Axis 2.
	Automation1PsoWindowInput_iXA4PrimaryFeedbackAxis2 = 271,
	/// @brief iXA4 Drive Pulse Stream Axis 1.
	Automation1PsoWindowInput_iXA4DrivePulseStreamAxis1 = 272,
	/// @brief iXA4 Drive Pulse Stream Axis 2.
	Automation1PsoWindowInput_iXA4DrivePulseStreamAxis2 = 273,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to XI4AuxiliaryFeedbackAxis1. Use XI4AuxiliaryFeedbackAxis1 instead of this enum value.
	Automation1PsoWindowInput_XI4AuxiliaryFeedback1 = 165,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to XI4AuxiliaryFeedbackAxis2. Use XI4AuxiliaryFeedbackAxis2 instead of this enum value.
	Automation1PsoWindowInput_XI4AuxiliaryFeedback2 = 166,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to XI4AuxiliaryFeedbackAxis3. Use XI4AuxiliaryFeedbackAxis3 instead of this enum value.
	Automation1PsoWindowInput_XI4AuxiliaryFeedback3 = 167,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to XI4AuxiliaryFeedbackAxis4. Use XI4AuxiliaryFeedbackAxis4 instead of this enum value.
	Automation1PsoWindowInput_XI4AuxiliaryFeedback4 = 168,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to iXI4AuxiliaryFeedbackAxis1. Use iXI4AuxiliaryFeedbackAxis1 instead of this enum value.
	Automation1PsoWindowInput_iXI4AuxiliaryFeedback1 = 228,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to iXI4AuxiliaryFeedbackAxis2. Use iXI4AuxiliaryFeedbackAxis2 instead of this enum value.
	Automation1PsoWindowInput_iXI4AuxiliaryFeedback2 = 229,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to iXI4AuxiliaryFeedbackAxis3. Use iXI4AuxiliaryFeedbackAxis3 instead of this enum value.
	Automation1PsoWindowInput_iXI4AuxiliaryFeedback3 = 230,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to iXI4AuxiliaryFeedbackAxis4. Use iXI4AuxiliaryFeedbackAxis4 instead of this enum value.
	Automation1PsoWindowInput_iXI4AuxiliaryFeedback4 = 231,
} Automation1PsoWindowInput;

/// @brief Specifies the PSO output pin settings for each drive.
typedef enum Automation1PsoOutputPin
{
	/// @brief GL4 None (default).
	Automation1PsoOutputPin_GL4None = 100,
	/// @brief GL4 Laser Output 0.
	Automation1PsoOutputPin_GL4LaserOutput0 = 101,
	/// @brief XL4s None (default).
	Automation1PsoOutputPin_XL4sNone = 102,
	/// @brief XL4s Laser Output 0.
	Automation1PsoOutputPin_XL4sLaserOutput0 = 103,
	/// @brief XR3 None (default).
	Automation1PsoOutputPin_XR3None = 104,
	/// @brief XR3 PSO Output 1.
	Automation1PsoOutputPin_XR3PsoOutput1 = 105,
	/// @brief XR3 PSO Output 2.
	Automation1PsoOutputPin_XR3PsoOutput2 = 106,
	/// @brief XR3 PSO Output 3.
	Automation1PsoOutputPin_XR3PsoOutput3 = 107,
	/// @brief XC4 Dedicated Output (default).
	Automation1PsoOutputPin_XC4DedicatedOutput = 108,
	/// @brief XC4 Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_XC4AuxiliaryMarkerDifferential = 109,
	/// @brief XC4 Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_XC4AuxiliaryMarkerSingleEnded = 110,
	/// @brief XC4e Dedicated Output (default).
	Automation1PsoOutputPin_XC4eDedicatedOutput = 111,
	/// @brief XC4e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_XC4eAuxiliaryMarkerDifferential = 112,
	/// @brief XC4e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_XC4eAuxiliaryMarkerSingleEnded = 113,
	/// @brief XC6e Dedicated Output (default).
	Automation1PsoOutputPin_XC6eDedicatedOutput = 114,
	/// @brief XC6e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_XC6eAuxiliaryMarkerDifferential = 115,
	/// @brief XC6e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_XC6eAuxiliaryMarkerSingleEnded = 116,
	/// @brief XL5e Dedicated Output (default).
	Automation1PsoOutputPin_XL5eDedicatedOutput = 117,
	/// @brief XL5e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_XL5eAuxiliaryMarkerDifferential = 118,
	/// @brief XL5e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_XL5eAuxiliaryMarkerSingleEnded = 119,
	/// @brief XC2 Dedicated Output (default).
	Automation1PsoOutputPin_XC2DedicatedOutput = 120,
	/// @brief XC2e Dedicated Output (default).
	Automation1PsoOutputPin_XC2eDedicatedOutput = 121,
	/// @brief XL2e Dedicated Output (default).
	Automation1PsoOutputPin_XL2eDedicatedOutput = 122,
	/// @brief XI4 Dedicated Output (default).
	Automation1PsoOutputPin_XI4DedicatedOutput = 123,
	/// @brief iXC4 Dedicated Output (default).
	Automation1PsoOutputPin_iXC4DedicatedOutput = 124,
	/// @brief iXC4 Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_iXC4AuxiliaryMarkerDifferential = 125,
	/// @brief iXC4 Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_iXC4AuxiliaryMarkerSingleEnded = 126,
	/// @brief iXC4e Dedicated Output (default).
	Automation1PsoOutputPin_iXC4eDedicatedOutput = 127,
	/// @brief iXC4e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_iXC4eAuxiliaryMarkerDifferential = 128,
	/// @brief iXC4e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_iXC4eAuxiliaryMarkerSingleEnded = 129,
	/// @brief iXC6e Dedicated Output (default).
	Automation1PsoOutputPin_iXC6eDedicatedOutput = 130,
	/// @brief iXC6e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_iXC6eAuxiliaryMarkerDifferential = 131,
	/// @brief iXC6e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_iXC6eAuxiliaryMarkerSingleEnded = 132,
	/// @brief iXL5e Dedicated Output (default).
	Automation1PsoOutputPin_iXL5eDedicatedOutput = 133,
	/// @brief iXL5e Auxiliary Marker (Differential mode).
	Automation1PsoOutputPin_iXL5eAuxiliaryMarkerDifferential = 134,
	/// @brief iXL5e Auxiliary Marker (Single-ended mode).
	Automation1PsoOutputPin_iXL5eAuxiliaryMarkerSingleEnded = 135,
	/// @brief iXR3 None (default).
	Automation1PsoOutputPin_iXR3None = 136,
	/// @brief iXR3 PSO Output 1.
	Automation1PsoOutputPin_iXR3PsoOutput1 = 137,
	/// @brief iXR3 PSO Output 2.
	Automation1PsoOutputPin_iXR3PsoOutput2 = 138,
	/// @brief iXR3 PSO Output 3.
	Automation1PsoOutputPin_iXR3PsoOutput3 = 139,
	/// @brief GI4 None (default).
	Automation1PsoOutputPin_GI4None = 140,
	/// @brief GI4 Laser Output 0.
	Automation1PsoOutputPin_GI4LaserOutput0 = 141,
	/// @brief iXC2 Dedicated Output (default).
	Automation1PsoOutputPin_iXC2DedicatedOutput = 142,
	/// @brief iXC2e Dedicated Output (default).
	Automation1PsoOutputPin_iXC2eDedicatedOutput = 143,
	/// @brief iXL2e Dedicated Output (default).
	Automation1PsoOutputPin_iXL2eDedicatedOutput = 144,
	/// @brief iXI4 Dedicated Output (default).
	Automation1PsoOutputPin_iXI4DedicatedOutput = 145,
	/// @brief FLEX Dedicated Output (default).
	Automation1PsoOutputPin_FLEXDedicatedOutput = 146,
	/// @brief iFLEX Dedicated Output (default).
	Automation1PsoOutputPin_iFLEXDedicatedOutput = 147,
	/// @brief XA4 Dedicated Output (default).
	Automation1PsoOutputPin_XA4DedicatedOutput = 148,
	/// @brief iXA4 Dedicated Output (default).
	Automation1PsoOutputPin_iXA4DedicatedOutput = 149,
} Automation1PsoOutputPin;

/// @brief Selects whether autofocus will run in continuous focus mode or single focus mode.
typedef enum Automation1AutofocusFocusMode
{
	/// @brief The autofocus routine runs continuously until you turn off autofocus.
	Automation1AutofocusFocusMode_Continuous = 0,
	/// @brief The autofocus routine automatically turns off when the input that is specified by the AutofocusInput parameter is within the specified deadband of the AutofocusDeadband parameter.
	Automation1AutofocusFocusMode_Single = 1,
} Automation1AutofocusFocusMode;

/// @brief A controller signal used for analog output axis tracking.
typedef enum Automation1AnalogOutputAxisTrackingItem
{
	/// @brief The analog output will track the Position Command item in user units.
	Automation1AnalogOutputAxisTrackingItem_PositionCommand = 1,
	/// @brief The analog output will track the Position Feedback item in user units.
	Automation1AnalogOutputAxisTrackingItem_PositionFeedback = 2,
	/// @brief The analog output will track the Velocity Command item in user units per second.
	Automation1AnalogOutputAxisTrackingItem_VelocityCommand = 3,
	/// @brief The analog output will track the Velocity Feedback item in user units per second.
	Automation1AnalogOutputAxisTrackingItem_VelocityFeedback = 4,
	/// @brief The analog output will track the Current Command item in amps.
	Automation1AnalogOutputAxisTrackingItem_CurrentCommand = 5,
	/// @brief The analog output will track the Current Feedback item in amps.
	Automation1AnalogOutputAxisTrackingItem_CurrentFeedback = 6,
	/// @brief The analog output will track the Acceleration Command item in user units per second squared.
	Automation1AnalogOutputAxisTrackingItem_AccelerationCommand = 7,
	/// @brief The analog output will track the Position Error item in user units.
	Automation1AnalogOutputAxisTrackingItem_PositionError = 8,
	/// @brief The analog output will track the Piezo Voltage Command item in volts.
	Automation1AnalogOutputAxisTrackingItem_PiezoVoltageCommand = 9,
	/// @brief The analog output will track the vector speed in user units per second.
	Automation1AnalogOutputAxisTrackingItem_VectorSpeedCommand = 10,
} Automation1AnalogOutputAxisTrackingItem;

/// @brief A controller signal used for analog output vector tracking.
typedef enum Automation1AnalogOutputVectorTrackingItem
{
	/// @brief The analog output will track the Position Command item in primary units.
	Automation1AnalogOutputVectorTrackingItem_PositionCommand = 0,
	/// @brief The analog output will track the Position Feedback item in primary units.
	Automation1AnalogOutputVectorTrackingItem_PositionFeedback = 1,
	/// @brief The analog output will track the Velocity Command item in primary units per second.
	Automation1AnalogOutputVectorTrackingItem_VelocityCommand = 2,
	/// @brief The analog output will track the Velocity Feedback item in primary units per second.
	Automation1AnalogOutputVectorTrackingItem_VelocityFeedback = 3,
} Automation1AnalogOutputVectorTrackingItem;

/// @brief Represents a data collection file type.
typedef enum Automation1DataCollectionFileType
{
	/// @brief The Automation1 Plot file type.
	Automation1DataCollectionFileType_Plt = 0,
	/// @brief The CSV file type.
	Automation1DataCollectionFileType_Csv = 1,
	/// @brief The JSON file type.
	Automation1DataCollectionFileType_Json = 2,
} Automation1DataCollectionFileType;

/// @brief Represents a frequency response file type.
typedef enum Automation1FrequencyResponseFileType
{
	/// @brief The Automation1 Frequency Response file type.
	Automation1FrequencyResponseFileType_Fr = 0,
	/// @brief The CSV file type.
	Automation1FrequencyResponseFileType_Csv = 1,
	/// @brief The JSON file type.
	Automation1FrequencyResponseFileType_Json = 2,
} Automation1FrequencyResponseFileType;

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
	/// @brief This task has an active command queue that is currently running.
	Automation1TaskState_QueueRunning = 9,
	/// @brief This task has an active command queue that is currently paused.
	Automation1TaskState_QueuePaused = 10,
} Automation1TaskState;

/// @brief Represents the motor type
typedef enum Automation1MotorType
{
	/// @brief AC Brushless Linear
	Automation1MotorType_ACBrushlessLinear = 0,
	/// @brief AC Brushless Rotary
	Automation1MotorType_ACBrushlessRotary = 1,
	/// @brief DC Brush
	Automation1MotorType_DCBrush = 2,
	/// @brief Stepper Motor
	Automation1MotorType_StepperMotor = 3,
	/// @brief Three Phase Stepper
	Automation1MotorType_ThreePhaseStepper = 4,
	/// @brief 2-Phase AC Brushless
	Automation1MotorType_TwoPhaseACBrushless = 6,
	/// @brief Piezo Actuator
	Automation1MotorType_PiezoActuator = 8,
	/// @brief Galvo
	Automation1MotorType_Galvo = 9,
} Automation1MotorType;

/// @brief Represents the home type
typedef enum Automation1HomeType
{
	/// @brief Home Past Limit to Marker
	Automation1HomeType_PastLimittoMarker = 0,
	/// @brief Home to Limit and Reverse to Marker
	Automation1HomeType_ToLimitandReversetoMarker = 1,
	/// @brief Home to Marker Only
	Automation1HomeType_ToMarkerOnly = 2,
	/// @brief Home to Limit Only
	Automation1HomeType_ToLimitOnly = 3,
	/// @brief Home at Current Position
	Automation1HomeType_AtCurrentPosition = 4,
	/// @brief Home at Current Position Feedback
	Automation1HomeType_AtCurrentPositionFeedback = 5,
	/// @brief Home at Current Position Absolute
	Automation1HomeType_AtCurrentPositionAbsolute = 6,
} Automation1HomeType;

/// @brief Represents the feedback type on the primary connector
typedef enum Automation1PrimaryFeedbackType
{
	/// @brief None
	Automation1PrimaryFeedbackType_None = 0,
	/// @brief Incremental Encoder (Square-Wave)
	Automation1PrimaryFeedbackType_IncrementalEncoderSquareWave = 1,
	/// @brief Incremental Encoder (Sine-Wave)
	Automation1PrimaryFeedbackType_IncrementalEncoderSineWave = 2,
	/// @brief Absolute Encoder (EnDat with Sine-Wave Incremental)
	Automation1PrimaryFeedbackType_AbsoluteEncoderEnDatwithSineWaveIncremental = 3,
	/// @brief Absolute Encoder (EnDat)
	Automation1PrimaryFeedbackType_AbsoluteEncoderEnDat = 4,
	/// @brief Hall-Effect Switches
	Automation1PrimaryFeedbackType_HallEffectSwitches = 5,
	/// @brief Absolute Encoder (SSI)
	Automation1PrimaryFeedbackType_AbsoluteEncoderSSI = 6,
	/// @brief Absolute Encoder (BiSS)
	Automation1PrimaryFeedbackType_AbsoluteEncoderBiSS = 9,
	/// @brief Absolute Encoder (BiSS with Sine-Wave Incremental)
	Automation1PrimaryFeedbackType_AbsoluteEncoderBiSSwithSineWaveIncremental = 10,
	/// @brief Capacitance Sensor
	Automation1PrimaryFeedbackType_CapacitanceSensor = 11,
} Automation1PrimaryFeedbackType;

/// @brief Represents the feedback type on the auxiliary connector
typedef enum Automation1AuxiliaryFeedbackType
{
	/// @brief None
	Automation1AuxiliaryFeedbackType_None = 0,
	/// @brief Incremental Encoder (Square-Wave)
	Automation1AuxiliaryFeedbackType_IncrementalEncoderSquareWave = 1,
	/// @brief Incremental Encoder (Sine-Wave)
	Automation1AuxiliaryFeedbackType_IncrementalEncoderSineWave = 2,
	/// @brief Absolute Encoder (EnDat)
	Automation1AuxiliaryFeedbackType_AbsoluteEncoderEnDat = 4,
	/// @brief Absolute Encoder (SSI)
	Automation1AuxiliaryFeedbackType_AbsoluteEncoderSSI = 6,
	/// @brief Absolute Encoder (BiSS)
	Automation1AuxiliaryFeedbackType_AbsoluteEncoderBiSS = 9,
} Automation1AuxiliaryFeedbackType;

/// @brief Represents the piezo default servo state.
typedef enum Automation1PiezoDefaultServoState
{
	/// @brief Servo Off
	Automation1PiezoDefaultServoState_Off = 0,
	/// @brief Servo On
	Automation1PiezoDefaultServoState_On = 1,
} Automation1PiezoDefaultServoState;

/// @brief Represents PSO status
typedef enum Automation1PsoStatus
{
	/// @brief The Waveform module is actively generating a waveform.
	Automation1PsoStatus_WaveformActive = 1 << 4,
	/// @brief The state of the Bit module output.
	Automation1PsoStatus_BitOutputActive = 1 << 5,
	/// @brief The state of the Window 1 module output.
	Automation1PsoStatus_Window1OutputActive = 1 << 6,
	/// @brief The state of the Window 2 module output.
	Automation1PsoStatus_Window2OutputActive = 1 << 7,
	/// @brief The state of the Output module output.
	Automation1PsoStatus_OutputActive = 1 << 10,
	/// @brief The state of the external synchronization input that is used with the PsoPulseExternalSyncOn function.
	Automation1PsoStatus_ExternalSyncInput = 1 << 11,
	/// @brief The Distance module attempted to load a new array mode distance when no new distance values were available. The distance counters are disabled until new distance values are specified.
	Automation1PsoStatus_DistanceArrayDepleted = 1 << 12,
	/// @brief The Window 1 module attempted to load a new array mode window range when no new range values were available. The window output is disabled until new range values are specified.
	Automation1PsoStatus_Window1ArrayDepleted = 1 << 13,
	/// @brief The Window 2 module attempted to load a new array mode window range when no new range values were available. The window output is disabled until new range values are specified.
	Automation1PsoStatus_Window2ArrayDepleted = 1 << 14,
	/// @brief The Bit module attempted to load a new bit value when no new bit values were available. The bit output is disabled until new range values are specified.
	Automation1PsoStatus_BitArrayDepleted = 1 << 15,
	/// @brief The Waveform module attempted to load a new array mode parameter value when no new parameter values were available. The waveform module is disabled until new parameter values are specified.
	Automation1PsoStatus_WaveformArrayDepleted = 1 << 16,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been obsoleted by DistanceArrayDepleted. Use DistanceArrayDepleted instead of this enum value.
	Automation1PsoStatus_DistanceFifoEmpty = 1 << 0,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been obsoleted by WaveformArrayDepleted. Use WaveformArrayDepleted instead of this enum value.
	Automation1PsoStatus_LaserFifoEmpty = 1 << 1,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been obsoleted by Window1ArrayDepleted. Use Window1ArrayDepleted instead of this enum value.
	Automation1PsoStatus_Window1FifoEmpty = 1 << 2,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been obsoleted by Window2ArrayDepleted. Use Window2ArrayDepleted instead of this enum value.
	Automation1PsoStatus_Window2FifoEmpty = 1 << 3,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been obsoleted by WaveformActive. Use WaveformActive instead of this enum value.
	Automation1PsoStatus_FiringActivePulseGen1 = 1 << 4,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been obsoleted by WaveformActive. Use WaveformActive instead of this enum value.
	Automation1PsoStatus_FiringActivePulseGenerator1 = 1 << 4,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been removed because the feature does not exist in Automation1. This bit is now used for BitOutputActive.
	Automation1PsoStatus_FiringActivePulseGen2 = 1 << 5,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been removed because the feature does not exist in Automation1. This bit is now used for BitOutputActive.
	Automation1PsoStatus_FiringActivePulseGenerator2 = 1 << 5,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to Window1OutputActive. Use Window1OutputActive instead of this enum value.
	Automation1PsoStatus_InsideWindow1 = 1 << 6,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to Window2OutputActive. Use Window2OutputActive instead of this enum value.
	Automation1PsoStatus_InsideWindow2 = 1 << 7,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been removed because the feature does not exist in Automation1.
	Automation1PsoStatus_PsoInterlock = 1 << 8,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been obsoleted by OutputActive. Use OutputActive instead of this enum value.
	Automation1PsoStatus_PsoOutput1Status = 1 << 9,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been removed because the feature does not exist in Automation1. This bit is now used for OutputActive.
	Automation1PsoStatus_PsoOutput2Status = 1 << 10,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to ExternalSyncInput. Use ExternalSyncInput instead of this enum value.
	Automation1PsoStatus_PsoExtSync = 1 << 11,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to ExternalSyncInput. Use ExternalSyncInput instead of this enum value.
	Automation1PsoStatus_PsoExternalSyncInput = 1 << 11,
} Automation1PsoStatus;

/// @brief Represents the Safe Torque Off (STO) status for an axis.
typedef enum Automation1StoStatus
{
	/// @brief Safe Torque Off (STO) channel 1 hardware is activated and preventing torque.
	Automation1StoStatus_Sto1Activated = 1 << 0,
	/// @brief Power has been removed from the Safe Torque Off (STO) channel 1 input. Torque on the motor will be prevented after the hardware time delay.
	Automation1StoStatus_Sto1Event = 1 << 1,
	/// @brief Safe Torque Off (STO) channel 2 hardware is activated and preventing torque.
	Automation1StoStatus_Sto2Activated = 1 << 2,
	/// @brief Power has been removed from the Safe Torque Off (STO) channel 2 input. Torque on the motor will be prevented after the hardware time delay.
	Automation1StoStatus_Sto2Event = 1 << 3,
	/// @brief The Safe Torque Off (STO) diagnostic check has detected a hardware problem on an STO channel and is preventing torque on the motor.
	Automation1StoStatus_StoCrossCheckFault = 1 << 4,
} Automation1StoStatus;

/// @brief Represents BiSS status
typedef enum Automation1BissStatus
{
	/// @brief 
	Automation1BissStatus_CrcError = 1 << 0,
	/// @brief 
	Automation1BissStatus_EncoderWarning = 1 << 1,
	/// @brief 
	Automation1BissStatus_EncoderError = 1 << 2,
	/// @brief 
	Automation1BissStatus_TimeoutError = 1 << 3,
} Automation1BissStatus;

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
	/// @brief The motion on this axis is the input to a kinematic transformation.
	Automation1AxisStatus_TransformationInput = 1 << 20,
	/// @brief The motion on this axis is the output of a kinematic transformation.
	Automation1AxisStatus_TransformationOutput = 1 << 21,
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
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CalibrationEnabled1D. Use CalibrationEnabled1D instead of this enum value.
	Automation1AxisStatus_CalEnabled1D = 1 << 14,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CalibrationEnabled2D. Use CalibrationEnabled2D instead of this enum value.
	Automation1AxisStatus_CalEnabled2D = 1 << 15,
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
	/// @brief The amplifier temperature is not within the operating range or the shunt resistor temperature has exceeded the maximum threshold. This fault occurs at amplifier temperatures less than 0° C or greater than 75° C and shunt resistor temperatures greater than 200° C.
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
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to PositionErrorFault. Use PositionErrorFault instead of this enum value.
	Automation1AxisFault_PositionError = 1 << 0,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to OverCurrentFault. Use OverCurrentFault instead of this enum value.
	Automation1AxisFault_OverCurrent = 1 << 1,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CwEndOfTravelLimitFault. Use CwEndOfTravelLimitFault instead of this enum value.
	Automation1AxisFault_CwEotLimit = 1 << 2,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CcwEndOfTravelLimitFault. Use CcwEndOfTravelLimitFault instead of this enum value.
	Automation1AxisFault_CcwEotLimit = 1 << 3,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CwSoftwareLimitFault. Use CwSoftwareLimitFault instead of this enum value.
	Automation1AxisFault_CwSoftLimit = 1 << 4,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CcwSoftwareLimitFault. Use CcwSoftwareLimitFault instead of this enum value.
	Automation1AxisFault_CcwSoftLimit = 1 << 5,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to FeedbackInput0Fault. Use FeedbackInput0Fault instead of this enum value.
	Automation1AxisFault_FbkInput0 = 1 << 7,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to FeedbackInput1Fault. Use FeedbackInput1Fault instead of this enum value.
	Automation1AxisFault_FbkInput1 = 1 << 8,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to HallSensorFault. Use HallSensorFault instead of this enum value.
	Automation1AxisFault_HallFault = 1 << 9,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to MaxVelocityCommandFault. Use MaxVelocityCommandFault instead of this enum value.
	Automation1AxisFault_MaxVelocity = 1 << 10,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to EmergencyStopFault. Use EmergencyStopFault instead of this enum value.
	Automation1AxisFault_EstopFault = 1 << 11,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to VelocityErrorFault. Use VelocityErrorFault instead of this enum value.
	Automation1AxisFault_VelocityError = 1 << 12,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to MotorTemperatureFault. Use MotorTemperatureFault instead of this enum value.
	Automation1AxisFault_MotorTemp = 1 << 17,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to AmplifierTemperatureFault. Use AmplifierTemperatureFault instead of this enum value.
	Automation1AxisFault_AmplifierTemp = 1 << 18,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to GantryMisalignmentFault. Use GantryMisalignmentFault instead of this enum value.
	Automation1AxisFault_MisalignmentFault = 1 << 22,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to FeedbackScalingFault. Use FeedbackScalingFault instead of this enum value.
	Automation1AxisFault_FbkScalingFault = 1 << 23,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to MarkerSearchFault. Use MarkerSearchFault instead of this enum value.
	Automation1AxisFault_MrkSearchFault = 1 << 24,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to InPositionTimeoutFault. Use InPositionTimeoutFault instead of this enum value.
	Automation1AxisFault_InPosTimeout = 1 << 26,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to VoltageClampFault. Use VoltageClampFault instead of this enum value.
	Automation1AxisFault_VoltageClamp = 1 << 27,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to MotorSupplyFault. Use MotorSupplyFault instead of this enum value.
	Automation1AxisFault_MotorSupply = 1 << 28,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to InternalFault. Use InternalFault instead of this enum value.
	Automation1AxisFault_Internal = 1 << 30,
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
	/// @brief The amplifier associated with this physical axis is active and outputting current to the attached motor.
	Automation1DriveStatus_AmplifierActive = 1 << 13,
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
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CwEndOfTravelLimitInput. Use CwEndOfTravelLimitInput instead of this enum value.
	Automation1DriveStatus_CwEotLimit = 1 << 1,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CcwEndOfTravelLimitInput. Use CcwEndOfTravelLimitInput instead of this enum value.
	Automation1DriveStatus_CcwEotLimit = 1 << 2,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to HomeLimitInput. Use HomeLimitInput instead of this enum value.
	Automation1DriveStatus_HomeLimit = 1 << 3,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to EmergencyStopInput. Use EmergencyStopInput instead of this enum value.
	Automation1DriveStatus_EstopInput = 1 << 10,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to GalvoCalibrationEnabled. Use GalvoCalibrationEnabled instead of this enum value.
	Automation1DriveStatus_GalvoCalEnabled = 1 << 20,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to ProgrammingFlash. Use ProgrammingFlash instead of this enum value.
	Automation1DriveStatus_ProgramFlash = 1 << 22,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to AccelerationPhase. Use AccelerationPhase instead of this enum value.
	Automation1DriveStatus_AccelPhase = 1 << 27,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to DecelerationPhase. Use DecelerationPhase instead of this enum value.
	Automation1DriveStatus_DecelPhase = 1 << 28,
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
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to SynchronizedFunctionExecuting. Use SynchronizedFunctionExecuting instead of this enum value.
	Automation1TaskStatus0_SyncFunctionExecuting = 1 << 27,
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
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CutterOffsetsEnablingPositive. Use CutterOffsetsEnablingPositive instead of this enum value.
	Automation1TaskStatus1_CutterOffsetsEnablingPos = 1 << 9,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CutterOffsetsEnablingNegative. Use CutterOffsetsEnablingNegative instead of this enum value.
	Automation1TaskStatus1_CutterOffsetsEnablingNeg = 1 << 10,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to SynchronizedFunctionPending. Use SynchronizedFunctionPending instead of this enum value.
	Automation1TaskStatus1_SyncFunctionPending = 1 << 17,
} Automation1TaskStatus1;

/// @brief Represents a set of task status
typedef enum Automation1TaskStatus2
{
	/// @brief Parts scaling is active.
	Automation1TaskStatus2_ScalingActive = 1 << 3,
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

/// @brief Represents a motion ramping type.
typedef enum Automation1RampType
{
	/// @brief Linear-based acceleration and deceleration.
	Automation1RampType_Linear = 0,
	/// @brief S-curve-based acceleration and deceleration.
	Automation1RampType_SCurve = 1,
	/// @brief Sine-based acceleration and deceleration.
	Automation1RampType_Sine = 2,
} Automation1RampType;

/// @brief Represents a motion ramping mode.
typedef enum Automation1RampMode
{
	/// @brief Rate-based acceleration and deceleration.
	Automation1RampMode_Rate = 0,
	/// @brief Time-based acceleration and deceleration.
	Automation1RampMode_Time = 1,
} Automation1RampMode;

/// @brief Specifies the type of calibration that will be performed by a calibration action.
typedef enum Automation1CalibrationType
{
	/// @brief 1D Axis Calibration.
	Automation1CalibrationType_AxisCalibration1D = 0,
	/// @brief 2D Axis Calibration.
	Automation1CalibrationType_AxisCalibration2D = 1,
	/// @brief Galvo 2D Axis Calibration.
	Automation1CalibrationType_Galvo2DAxisCalibration = 2,
	/// @brief Galvo Power Correction.
	Automation1CalibrationType_GalvoPowerCorrection = 3,
} Automation1CalibrationType;

/// @brief Represents the first feedback input
typedef enum Automation1FeedbackInput0
{
	/// @brief Position Command
	Automation1FeedbackInput0_PositionCommand = 0,
	/// @brief Primary Feedback
	Automation1FeedbackInput0_PrimaryFeedback = 1,
	/// @brief Auxiliary Feedback
	Automation1FeedbackInput0_AuxiliaryFeedback = 2,
	/// @brief Analog Input 0
	Automation1FeedbackInput0_AnalogInput0 = 3,
	/// @brief Analog Input 1
	Automation1FeedbackInput0_AnalogInput1 = 4,
	/// @brief Analog Input 2
	Automation1FeedbackInput0_AnalogInput2 = 5,
	/// @brief Analog Input 3
	Automation1FeedbackInput0_AnalogInput3 = 6,
} Automation1FeedbackInput0;

/// @brief Represents the second feedback input
typedef enum Automation1FeedbackInput1
{
	/// @brief Position Command
	Automation1FeedbackInput1_PositionCommand = 0,
	/// @brief Primary Feedback
	Automation1FeedbackInput1_PrimaryFeedback = 1,
	/// @brief Auxiliary Feedback
	Automation1FeedbackInput1_AuxiliaryFeedback = 2,
	/// @brief Analog Input 0
	Automation1FeedbackInput1_AnalogInput0 = 3,
	/// @brief Analog Input 1
	Automation1FeedbackInput1_AnalogInput1 = 4,
	/// @brief Analog Input 2
	Automation1FeedbackInput1_AnalogInput2 = 5,
	/// @brief Analog Input 3
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
	/// @brief Use the MultisinePlus disturbance.
	Automation1TuningDisturbanceType_MultisinePlus = 6,
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

/// @brief Represents EnDat status
typedef enum Automation1EnDatStatus
{
	/// @brief 
	Automation1EnDatStatus_CrcError = 1 << 0,
	/// @brief 
	Automation1EnDatStatus_ReceiveError = 1 << 1,
	/// @brief 
	Automation1EnDatStatus_TimeoutError = 1 << 2,
} Automation1EnDatStatus;

/// @brief Represents the primary feedback connector status bits
typedef enum Automation1PrimaryFeedbackStatus
{
	/// @brief This represents the state of the CW end of travel limit input. It is affected by the active polarity, which is configured by the EndOfTravelLimitSetup parameter.
	Automation1PrimaryFeedbackStatus_CwEndOfTravelLimitInput = 1 << 0,
	/// @brief This represents the state of the CW end of travel limit input. It is affected by the active polarity, which is configured by the EndOfTravelLimitSetup parameter.
	Automation1PrimaryFeedbackStatus_CcwEndOfTravelLimitInput = 1 << 1,
	/// @brief This represents the state of the home limit input. It is affected by the active polarity, which is configured by the EndOfTravelLimitSetup parameter.
	Automation1PrimaryFeedbackStatus_HomeLimitInput = 1 << 2,
	/// @brief This represents the state of the marker input.
	Automation1PrimaryFeedbackStatus_MarkerInput = 1 << 3,
	/// @brief An error condition is present on the Sine encoder input of the feedback device.
	Automation1PrimaryFeedbackStatus_SineEncoderError = 1 << 4,
	/// @brief An error condition is present on the Cosine encoder input of the feedback device.
	Automation1PrimaryFeedbackStatus_CosineEncoderError = 1 << 5,
	/// @brief The position of the marker is latched.
	Automation1PrimaryFeedbackStatus_MarkerLatch = 1 << 6,
	/// @brief The on-board encoder multiplier detected that the input signals may be exceeding the maximum input range, which results in clipping of the encoder signals.
	Automation1PrimaryFeedbackStatus_EncoderClipping = 1 << 7,
	/// @brief This represents the state of the Hall A input.
	Automation1PrimaryFeedbackStatus_HallAInput = 1 << 8,
	/// @brief This represents the state of the Hall B input.
	Automation1PrimaryFeedbackStatus_HallBInput = 1 << 9,
	/// @brief This represents the state of the Hall C input.
	Automation1PrimaryFeedbackStatus_HallCInput = 1 << 10,
	/// @brief This represents the state of the CW end of travel limit input at the primary feedback connector. It is not affected by the active polarity.
	Automation1PrimaryFeedbackStatus_RawCwEndOfTravelLimitInput = 1 << 11,
	/// @brief This represents the state of the CW end of travel limit input at the primary feedback connector. It is not affected by the active polarity.
	Automation1PrimaryFeedbackStatus_RawCcwEndOfTravelLimitInput = 1 << 12,
	/// @brief This represents the state of the home limit input at the primary feedback connector. It is not affected by the active polarity.
	Automation1PrimaryFeedbackStatus_RawHomeLimitInput = 1 << 13,
	/// @brief The on-board encoder multiplier detected that the quadrature generation logic exceeded the maximum rate.
	Automation1PrimaryFeedbackStatus_MxQuadratureWarning = 1 << 14,
	/// @brief The on-board encoder multiplier detected that overflow occurred in the quadrature generation logic.
	Automation1PrimaryFeedbackStatus_MxQuadratureError = 1 << 15,
	/// @brief This represents the state of the square wave cosine input or the digital interpretation of the sine wave cosine input from the feedback device.
	Automation1PrimaryFeedbackStatus_DigitalCosineInput = 1 << 16,
	/// @brief This represents the state of the square wave sine input or the digital interpretation of the sine wave sine input from the feedback device.
	Automation1PrimaryFeedbackStatus_DigitalSineInput = 1 << 17,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CwEndOfTravelLimitInput. Use CwEndOfTravelLimitInput instead of this enum value.
	Automation1PrimaryFeedbackStatus_CwEotLimit = 1 << 0,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to CcwEndOfTravelLimitInput. Use CcwEndOfTravelLimitInput instead of this enum value.
	Automation1PrimaryFeedbackStatus_CcwEotLimit = 1 << 1,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to HomeLimitInput. Use HomeLimitInput instead of this enum value.
	Automation1PrimaryFeedbackStatus_HomeLimit = 1 << 2,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to RawCwEndOfTravelLimitInput. Use RawCwEndOfTravelLimitInput instead of this enum value.
	Automation1PrimaryFeedbackStatus_RawCwEotLimit = 1 << 11,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to RawCcwEndOfTravelLimitInput. Use RawCcwEndOfTravelLimitInput instead of this enum value.
	Automation1PrimaryFeedbackStatus_RawCcwEotLimit = 1 << 12,
	/// @brief This enum value is deprecated and will be removed in the next major version of Automation1 software. This enum value has been renamed to RawHomeLimitInput. Use RawHomeLimitInput instead of this enum value.
	Automation1PrimaryFeedbackStatus_RawHomeLimit = 1 << 13,
} Automation1PrimaryFeedbackStatus;

/// @brief Represents the auxiliary feedback connector status bits
typedef enum Automation1AuxiliaryFeedbackStatus
{
	/// @brief This represents the state of the marker input.
	Automation1AuxiliaryFeedbackStatus_MarkerInput = 1 << 0,
	/// @brief An error condition is present on the Sine encoder input of the feedback device.
	Automation1AuxiliaryFeedbackStatus_SineEncoderError = 1 << 1,
	/// @brief An error condition is present on the Cosine encoder input of the feedback device.
	Automation1AuxiliaryFeedbackStatus_CosineEncoderError = 1 << 2,
	/// @brief The position of the marker is latched.
	Automation1AuxiliaryFeedbackStatus_MarkerLatch = 1 << 3,
	/// @brief The on-board encoder multiplier detected that the input signals may be exceeding the maximum input range, which results in clipping of the encoder signals.
	Automation1AuxiliaryFeedbackStatus_EncoderClipping = 1 << 4,
	/// @brief The on-board encoder multiplier detected that the maximum quadrature generation rate has been exceeded.
	Automation1AuxiliaryFeedbackStatus_MxQuadratureWarning = 1 << 5,
	/// @brief The on-board encoder multiplier detected that the quadrature generation logic has experienced overflow.
	Automation1AuxiliaryFeedbackStatus_MxQuadratureError = 1 << 6,
	/// @brief This represents the state of the square wave cosine input or the digital interpretation of the sine wave cosine input from the feedback device.
	Automation1AuxiliaryFeedbackStatus_DigitalCosineInput = 1 << 7,
	/// @brief This represents the state of the square wave sine input or the digital interpretation of the sine wave sine input from the feedback device.
	Automation1AuxiliaryFeedbackStatus_DigitalSineInput = 1 << 8,
} Automation1AuxiliaryFeedbackStatus;

/// @brief Represents the amplifier status bits
typedef enum Automation1AmplifierStatus
{
	/// @brief The amplifier is active and outputting current to the attached motor.
	Automation1AmplifierStatus_Active = 1 << 0,
	/// @brief The amplifier detected that no motor supply voltage is present.
	Automation1AmplifierStatus_NoMotorSupply = 1 << 2,
	/// @brief The amplifier output is being clamped because the current command is more than the value of the MaxCurrentClamp parameter.
	Automation1AmplifierStatus_CurrentClamp = 1 << 3,
	/// @brief The amplifier power limiting on phase A has been active for an extended period. This causes an amplifier fault.
	Automation1AmplifierStatus_PowerLimitingA = 1 << 4,
	/// @brief The amplifier power limiting on phase B has been active for an extended period. This causes an amplifier fault.
	Automation1AmplifierStatus_PowerLimitingB = 1 << 5,
	/// @brief The amplifier power limiting on phase C has been active for an extended period. This causes an amplifier fault.
	Automation1AmplifierStatus_PowerLimitingC = 1 << 6,
	/// @brief The amplifier output on phase A is being limited to prevent damage to the hardware.
	Automation1AmplifierStatus_PowerLimitingAUnfiltered = 1 << 7,
	/// @brief The amplifier output on phase B is being limited to prevent damage to the hardware.
	Automation1AmplifierStatus_PowerLimitingBUnfiltered = 1 << 8,
	/// @brief The amplifier output on phase C is being limited to prevent damage to the hardware.
	Automation1AmplifierStatus_PowerLimitingCUnfiltered = 1 << 9,
	/// @brief The amplifier bus voltage is more than the maximum rated value.
	Automation1AmplifierStatus_BusOverVoltage = 1 << 10,
	/// @brief The amplifier output on one or more phases is being clamped to the minimum or maximum voltage.
	Automation1AmplifierStatus_VoltageClamped = 1 << 11,
	/// @brief The amplifier shunt circuit is active to keep the internal bus voltage within safe levels.
	Automation1AmplifierStatus_ShuntOn = 1 << 12,
} Automation1AmplifierStatus;

/// @brief Represents SSI status
typedef enum Automation1SsiStatus
{
	/// @brief 
	Automation1SsiStatus_TimeoutError = 1 << 0,
	/// @brief 
	Automation1SsiStatus_ParityError = 1 << 1,
} Automation1SsiStatus;

/// @brief Specifies the external signal with which to externally synchronize HyperWire.
typedef enum Automation1HyperWireExternalSynchronizationSignal
{
	/// @brief External synchronization is disabled.
	Automation1HyperWireExternalSynchronizationSignal_None = 0,
	/// @brief External synchronization is enabled with the EtherCAT SYNC0 signal.
	Automation1HyperWireExternalSynchronizationSignal_EthercatSync0 = 1,
} Automation1HyperWireExternalSynchronizationSignal;


#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1ENUM_H_INCLUDED
