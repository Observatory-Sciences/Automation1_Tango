///
/// Copyright (c) Aerotech, Inc.
///

#ifndef AUTOMATION1COMMANDQUEUE_H_INCLUDED
#define AUTOMATION1COMMANDQUEUE_H_INCLUDED

#if defined(_MSC_VER)
	#if defined(AUTOMATION1_CAPI_EXPORT)
		#define AUTOMATION1_CAPI __declspec(dllexport)
	#else
		#define AUTOMATION1_CAPI __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
	#define AUTOMATION1_CAPI __attribute__((visibility ("default")))
#endif

#include <stdint.h>
#include <stdbool.h>
#include "Automation1Controller.h"
#include "Automation1Enum.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Represents the status of a command queue on an Automation1 controller.
typedef struct Automation1CommandQueueStatus
{
	// @brief Gets whether the command queue is currently paused.
	bool IsPaused;
	// @brief Gets whether the command queue is empty, meaning there is no currently executing AeroScript command and there are no other AeroScript commands in the command queue.
	bool IsEmpty;
	// @brief Gets the number of commands the command queue has executed over its entire lifespan. An individual command can contain one or more lines of AeroScript which is possible if you call the Automation1_CommandQueue_Execute() function with a string of AeroScript that contains multiple lines. This status item gets how many individual commands were executed regardless of how many lines of AeroScript each command contained.
	int32_t NumberOfExecutedCommands;
	// @brief Gets the number of commands that have been added to the command queue and have yet to be executed. This count includes the currently executing AeroScript command, if there is one. An individual command can contain one or more lines of AeroScript which is possible if you call the Automation1_CommandQueue_Execute() function with a string of AeroScript that contains multiple lines. This status item gets how many unexecuted commands remain in the command queue regardless of how many lines of AeroScript each command contains.
	int32_t NumberOfUnexecutedCommands;
	// @brief Gets the number of times the command queue has been emptied.
	int32_t NumberOfTimesEmptied;
} Automation1CommandQueueStatus;

/// @brief A handle that represents a command queue on a task on an Automation1 controller.
/// 	See the Automation1_CommandQueue_Begin() function to obtain this type of handle.
/// 	Make sure to call Automation1_CommandQueue_End() to avoid leaking memory when you are done with the command queue.
typedef struct Automation1CommandQueue_T* Automation1CommandQueue;

/// @brief Gets the current status of a command queue.
/// @param[In] commandQueue The command queue to retrieve the status of.
/// @param[Out] commandQueueStatusOut The current status of the command queue. 
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @return Returns true if the status of the command queue was successfully retrieved otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GetStatus(Automation1CommandQueue commandQueue, Automation1CommandQueueStatus* commandQueueStatusOut);

/// @brief Starts a command queue on the specified task.
///		A command queue on a task will store all AeroScript commands added to the command queue and execute them sequentially, in the order they were added.
///		Adding AeroScript commands to the command queue does not block (unless the command queue is full and argument shouldBlockIfFull is true), 
///		instead the AeroScript command is added to the command queue and will be executed in the future once all previously added commands are executed.
///		A command queue is usually used to avoid the communication latency in between AeroScript commands when executing your motion with the Commands API 
///		(such as when using velocity blending where the communication latency will cause deceleration to occur).
///		The specified task can only execute queued commands while the command queue is active; non-queued commands from the Commands API and AeroScript 
///		programs cannot run while the command queue is active.
///		Call Automation1_CommandQueue_End() to avoid leaking memory when you are done with the command queue, to stop the command queue on the specified task, and return the task to normal AeroScript execution.
/// @param[In] controller A handle representing a connection to an Automation1 controller.
/// @param[In] taskIndex The index of the task to create a command queue on.
/// @param[In] commandCapacity The maximum number of unexecuted AeroScript commands that can be stored in the command queue, after which the command queue is full.
///		If the number of unexecuted AeroScript commands in the command queue reaches this number, 
///		the next AeroScript command added will either block until the command can be added (if shouldBlockIfFull is true) or return produce an error (if shouldBlockIfFull is false).
/// @param[In] shouldBlockIfFull Whether or not to block if you add an AeroScript command when the command queue is full. If true,
///		the add will block until the command can be added. If false, an error will be produced.
/// @param[Out] commandQueueOut A handle that represents a command queue on a task on the Automation1 controller. Only use this if the function call was successful.
/// @return Returns true if the creation of the command queue was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_Begin(Automation1Controller controller, int32_t taskIndex, int32_t commandCapacity, bool shouldBlockIfFull, Automation1CommandQueue* commandQueueOut);

/// @brief Waits for the command queue to be empty, blocking until all AeroScript commands added to the command queue have been executed.
/// 	You can use this method to make sure the command queue is no longer executing commands before ending it with Automation1_CommandQueue_End().
/// @param[In] commandQueue The command queue to wait for execution of all AeroScript commands to be completed on.
/// @param[In] millisecondsTimeout The number of milliseconds to wait for the command queue to be empty.
/// 	If the command queue takes longer than this amount of time to be empty, this function will return.
/// 	This function will wait indefinitely for the command queue to be empty if this value is set to - 1.
/// @return Returns true if the command queue has successfully finished executing all of its AeroScript commands or the timeout has been reached, otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_WaitForEmpty(Automation1CommandQueue commandQueue, int32_t millisecondsTimeout);

/// @brief Resumes the execution of queued AeroScript commands from a command queue.
/// @param[In] commandQueue The command queue to start the execution of commands from.
/// @return Returns true if the execution of AeroScript commands has resumed or the command queue was already executing AeroScript commands, otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_Resume(Automation1CommandQueue commandQueue);

/// @brief Pauses the execution of queued AeroScript commands from a command queue. 
///		The currently executing AeroScript command, if any, will complete normally; the command will not be aborted.
/// @param[In] commandQueue The command queue to pause the execution of AeroScript commands on.
/// @return Returns true if the execution of AeroScript commands has paused or the command queue was already paused, otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_Pause(Automation1CommandQueue commandQueue);

/// @brief Stops the command queue on the task and returns the task to normal AeroScript execution.
///		The currently executing AeroScript command, if any, will be aborted. All remaining queued AeroScript commands will be discarded.
///		After calling this function, this command queue handle is no longer usable.
/// @param[In] commandQueue The command queue to end.
/// @param[In] millisecondsTimeout The number of milliseconds to wait to end the command queue.
/// 	If the command queue takes longer than this amount of time to end, the function will fail.
/// 	This function will wait indefinitely for the command queue to end if this value is set to - 1.
/// @return Returns true if the execution of commands from the command queue has stopped otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_End(Automation1CommandQueue commandQueue, int32_t millisecondsTimeout);

/// @brief Adds an AeroScript command containing one or more lines of AeroScript to the command queue.
///		This function does not block (unless the command queue is full and commandQueue argument shouldBlockIfFull was set to true), 
///		instead the AeroScript command is added to the command queue and will be executed in the future once all previously added commands are executed.
/// @param[In] commandQueue The command queue perform this AeroScript command on.
/// @param[In] aeroScriptText The null-terminated AeroScript string text to compile and add to the command queue.
/// @return Returns true if the AeroScript command was compiled and added to the command queue otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_Execute(Automation1CommandQueue commandQueue, const char* aeroScriptText);

/// @brief Adds all AeroScript lines in the specified MDK file to the command queue.
///		The specified MDK file can only contain simple lines of AeroScript; it cannot contain variables, if statements, loops, or other control flow statements.
///		This function blocks and waits until all AeroScript lines are added to the queue, but it does not wait for all AeroScript lines to execute.
///		When this function returns, there might be unexecuted AeroScript lines from the MDK file still in the command queue; 
///		call the Automation1_CommandQueue_WaitForEmpty() function after this function to make sure all AeroScript lines have been executed.
///		If the command queue argument shouldBlockIfFull is false and the command queue fills while reading the MDK file, the function will fail and return false.
///		The AeroScript lines will be added to the command queue as commands containing multiple lines at a time in order to increase throughput.
///     numberOfLinesPerCommand specifies how many file lines to read from the controller file for each individual command.
///		Setting numberOfLinesPerCommand to 1000 will work in most cases, but if the command queue empties before the MDK file is read in its entirety, set it to a higher value. 
/// @param[In] commandQueue The command queue to which the lines of AeroScript from the file will be added and executed.
/// @param[In] mdkFilePath A MDK file that contains AeroScript lines to be executed by the command queue.
/// @param[In] numberOfLinesPerCommand The number of file lines to read from the MDK file for each individual command to add to the command queue. numberOfLinesPerCommand must be greater than one.
/// @return Returns true if the file was compiled and added to the command queue; otherwise, it returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_ExecuteFromMdkFile(Automation1CommandQueue commandQueue, const char* mdkFilePath, int32_t numberOfLinesPerCommand);

/// @brief Adds all AeroScript lines in the specified controller file file to the command queue.
///		The specified controller file can only contain simple lines of AeroScript; it cannot contain variables, if statements, loops, or other control flow statements.
///		This function blocks and waits until all AeroScript lines are added to the queue, but it does not wait for all AeroScript lines to execute.
///		When this function returns, there might be unexecuted AeroScript lines from the controller file still in the command queue; 
//		call the Automation1_CommandQueue_WaitForEmpty() function after this function to make sure all AeroScript lines have been executed.
///		If the command queue argument shouldBlockIfFull is false and the command queue fills while reading the controller file, the function will fail and return false.
///		The AeroScript lines will be added to the command queue as commands containing multiple lines at a time in order to increase throughput.
///     numberOfLinesPerCommand specifies how many file lines to read from the controller file for each individual command.
///		Setting numberOfLinesPerCommand to 1000 will work in most cases, but if the command queue empties before the MDK file is read in its entirety, set it to a higher value. 
/// @param[In] commandQueue The command queue to which the lines of AeroScript from the file will be added and executed.
/// @param[In] controllerFileName A controller file that contains AeroScript lines to be executed by the command queue.
/// @param[In] numberOfLinesPerCommand The number of file lines to read from the controller file for each individual command to add to the command queue. numberOfLinesPerCommand must be greater than one.
/// @return Returns true if the file was compiled and added to the command queue; otherwise, it returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_ExecuteFromControllerFile(Automation1CommandQueue commandQueue, const char* controllerFileName, int32_t numberOfLinesPerCommand);

/// @brief Adds the Disable command to the command queue.
///		Disables the axes so that you cannot command motion.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes to disable.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_Disable(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the DriveBrakeOff command to the command queue.
///		Disengages the brake output and allows the axis to move freely.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disengage the brake.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveBrakeOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveBrakeOn command to the command queue.
///		Engages the brake output and prevents the axis from moving freely.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to engage the brake.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveBrakeOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveDataCaptureConfigureArray command to the command queue.
///		Configures the drive array for drive data capture.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the drive array for drive data capture.
/// @param[In] configurationNumber The data capture configuration number. When capturing one input signal on the specified axis, specify a value of 0. When capturing two input signals on the specified axis, specify 0 for the first signal and 1 for the second signal.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first drive data capture value will be written.
/// @param[In] numberOfPoints The number of points that will be written to the drive array by drive data capture.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveDataCaptureConfigureArray(Automation1CommandQueue commandQueue, int32_t axis, int64_t configurationNumber, int64_t driveArrayStartAddress, int64_t numberOfPoints);

/// @brief Adds the DriveDataCaptureConfigureInput command to the command queue.
///		Selects the signal that will be stored by drive data capture.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to select the drive data capture signal.
/// @param[In] configurationNumber The data capture configuration number. When capturing one input signal on the specified axis, specify a value of 0. When capturing two input signals on the specified axis, specify 0 for the first signal and 1 for the second signal.
/// @param[In] input The input signal for drive data capture.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveDataCaptureConfigureInput(Automation1CommandQueue commandQueue, int32_t axis, int64_t configurationNumber, Automation1DriveDataCaptureInput input);

/// @brief Adds the DriveDataCaptureConfigureTrigger command to the command queue.
///		Selects the event that will trigger drive data capture.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to select the drive data capture trigger.
/// @param[In] configurationNumber The data capture configuration number. When capturing one input signal on the specified axis, specify a value of 0. When capturing two input signals on the specified axis, specify 0 for the first signal and 1 for the second signal.
/// @param[In] trigger The trigger event for drive data capture.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveDataCaptureConfigureTrigger(Automation1CommandQueue commandQueue, int32_t axis, int64_t configurationNumber, Automation1DriveDataCaptureTrigger trigger);

/// @brief Adds the DriveDataCaptureOff command to the command queue.
///		Disables drive data capture of configured inputs.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable drive data capture.
/// @param[In] configurationNumber The data capture configuration number. When capturing one input signal on the specified axis, specify a value of 0. When capturing two input signals on the specified axis, specify 0 for the first signal and 1 for the second signal.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveDataCaptureOff(Automation1CommandQueue commandQueue, int32_t axis, int64_t configurationNumber);

/// @brief Adds the DriveDataCaptureOn command to the command queue.
///		Enables drive data capture of configured inputs.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable drive data capture.
/// @param[In] configurationNumber The data capture configuration number. When capturing one input signal on the specified axis, specify a value of 0. When capturing two input signals on the specified axis, specify 0 for the first signal and 1 for the second signal.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveDataCaptureOn(Automation1CommandQueue commandQueue, int32_t axis, int64_t configurationNumber);

/// @brief Adds the DriveEncoderOutputConfigureDivider command to the command queue.
///		Applies a divider on the specified output channel, lowering the frequency of output signals.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the configuration.
/// @param[In] outputChannel The outgoing encoder channel.
/// @param[In] outputDivider The divider to apply to encoder output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveEncoderOutputConfigureDivider(Automation1CommandQueue commandQueue, int32_t axis, Automation1EncoderOutputChannel outputChannel, int64_t outputDivider);

/// @brief Adds the DriveEncoderOutputConfigureInput command to the command queue.
///		Configures an output channel to echo encoder signals from the specified input channel.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the configuration.
/// @param[In] outputChannel The outgoing encoder channel.
/// @param[In] inputChannel The incoming encoder channel.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveEncoderOutputConfigureInput(Automation1CommandQueue commandQueue, int32_t axis, Automation1EncoderOutputChannel outputChannel, Automation1EncoderInputChannel inputChannel);

/// @brief Adds the DriveEncoderOutputOff command to the command queue.
///		Disables encoder output on the specified output channel.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable encoder output.
/// @param[In] outputChannel The outgoing encoder channel.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveEncoderOutputOff(Automation1CommandQueue commandQueue, int32_t axis, Automation1EncoderOutputChannel outputChannel);

/// @brief Adds the DriveEncoderOutputOn command to the command queue.
///		Enables encoder output on the specified output channel.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable encoder output.
/// @param[In] outputChannel The outgoing encoder channel.
/// @param[In] outputMode This argument is unused and will be removed in the next major version of Automation1 software. You must specify EncoderOutputMode.Default.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveEncoderOutputOn(Automation1CommandQueue commandQueue, int32_t axis, Automation1EncoderOutputChannel outputChannel, Automation1EncoderOutputMode outputMode);

/// @brief Adds the DrivePulseStreamConfigure command to the command queue.
///		Configures pulse streaming mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] outputAxis The output axis on which to configure pulse streaming mode.
/// @param[In] inputAxes An array of one or more axes which will be tracked.
/// @param[In] inputAxesLength The number of elements in the inputAxes function argument.
/// @param[In] inputScaleFactors An array of scale factors to apply to each axis in the $inputAxes array.
/// @param[In] inputScaleFactorsLength The number of elements in the inputScaleFactors function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DrivePulseStreamConfigure(Automation1CommandQueue commandQueue, int32_t outputAxis, int32_t* inputAxes, int32_t inputAxesLength, double* inputScaleFactors, int32_t inputScaleFactorsLength);

/// @brief Adds the DrivePulseStreamConfigure command to the command queue.
///		Configures pulse streaming mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] outputAxis The output axis on which to configure pulse streaming mode.
/// @param[In] inputAxes An array of one or more axes which will be tracked.
/// @param[In] inputAxesLength The number of elements in the inputAxes function argument.
/// @param[In] inputScaleFactors An array of scale factors to apply to each axis in the $inputAxes array.
/// @param[In] inputScaleFactorsLength The number of elements in the inputScaleFactors function argument.
/// @param[In] signalMode The signal mode used when DriveEncoderOutputConfigureInput() and DriveEncoderOutputOn() are configured to echo the Pulse Stream signal to an encoder output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DrivePulseStreamConfigureWithSignalMode(Automation1CommandQueue commandQueue, int32_t outputAxis, int32_t* inputAxes, int32_t inputAxesLength, double* inputScaleFactors, int32_t inputScaleFactorsLength, Automation1DrivePulseStreamSignalMode signalMode);

/// @brief Adds the DrivePulseStreamOff command to the command queue.
///		Disables pulse streaming mode on an axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] outputAxis The axis on which to disable pulse streaming mode.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DrivePulseStreamOff(Automation1CommandQueue commandQueue, int32_t outputAxis);

/// @brief Adds the DrivePulseStreamOn command to the command queue.
///		Enables pulse streaming mode on an axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] outputAxis The axis on which to enable pulse streaming mode.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DrivePulseStreamOn(Automation1CommandQueue commandQueue, int32_t outputAxis);

/// @brief Adds the DriveSetAuxiliaryFeedback command to the command queue.
///		Sets the auxiliary feedback of the axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the auxiliary feedback.
/// @param[In] auxiliaryFeedback The feedback value to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveSetAuxiliaryFeedback(Automation1CommandQueue commandQueue, int32_t axis, double auxiliaryFeedback);

/// @brief Adds the DriveSetPositionCommand command to the command queue.
///		Sets the position command value of the specified axis at the servo loop level and adjusts the position feedback for position error.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the position command.
/// @param[In] positionCommandValue The position command value to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveSetPositionCommand(Automation1CommandQueue commandQueue, int32_t axis, double positionCommandValue);

/// @brief Adds the DriveSetPositionFeedback command to the command queue.
///		Sets the position command and the position feedback value of the specified axis at the servo loop level.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the position command.
/// @param[In] positionFeedbackValue The position feedback value to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveSetPositionFeedback(Automation1CommandQueue commandQueue, int32_t axis, double positionFeedbackValue);

/// @brief Adds the CammingFreeTable command to the command queue.
///		Unloads a camming table from the SMC.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] tableNum The camming table number to remove. This value must be greater than or equal to 0 and less than or equal to 99.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CammingFreeTable(Automation1CommandQueue commandQueue, int64_t tableNum);

/// @brief Adds the CammingLoadTableFromArray command to the command queue.
///		Loads a camming table into the SMC.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] tableNum The camming table number to use. This value must be greater than or equal to 0 and less than or equal to 99. Use this number when using the CammingOn() and CammingFreeTable() functions.
/// @param[In] leaderValues Array of leader axis position values for the follower axis to track.
/// @param[In] leaderValuesLength The number of elements in the leaderValues function argument.
/// @param[In] followerValues Array of follower axis positions or velocities to use.
/// @param[In] followerValuesLength The number of elements in the followerValues function argument.
/// @param[In] numValues The number of values in the leaderValues and followerValues arrays.
/// @param[In] unitsMode The units of the values in the camming table.
/// @param[In] interpolationMode The interpolation type to use if the position of the leader axis is between two values in the table.
/// @param[In] wrapMode Determines how a leader axis position value outside of the table is treated.
/// @param[In] tableOffset An offset applied to all follower axis position or velocity values in the table.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CammingLoadTableFromArray(Automation1CommandQueue commandQueue, int64_t tableNum, double* leaderValues, int32_t leaderValuesLength, double* followerValues, int32_t followerValuesLength, int64_t numValues, Automation1CammingUnits unitsMode, Automation1CammingInterpolation interpolationMode, Automation1CammingWrapping wrapMode, double tableOffset);

/// @brief Adds the CammingOff command to the command queue.
///		Disables camming on the specified follower axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] followerAxis The follower axis on which to disable camming.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CammingOff(Automation1CommandQueue commandQueue, int32_t followerAxis);

/// @brief Adds the CammingOn command to the command queue.
///		Enables camming on the specified leader axis and follower axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] followerAxis The axis to set as the follower axis.
/// @param[In] leaderAxis The axis to set as the leader axis.
/// @param[In] tableNum The camming table number to use. This value must be greater than or equal to 0 and less than or equal to 99.
/// @param[In] source The signal on the leader axis that the follower axis will track.
/// @param[In] output The output signal to generate and the synchronization mode to use on the camming follower axis.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CammingOn(Automation1CommandQueue commandQueue, int32_t followerAxis, int32_t leaderAxis, int64_t tableNum, Automation1CammingSource source, Automation1CammingOutput output);

/// @brief Adds the CornerRoundingOff command to the command queue.
///		Disables corner rounding.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CornerRoundingOff(Automation1CommandQueue commandQueue);

/// @brief Adds the CornerRoundingOn command to the command queue.
///		Enables corner rounding.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CornerRoundingOn(Automation1CommandQueue commandQueue);

/// @brief Adds the CornerRoundingSetAxes command to the command queue.
///		Configures axes to use for corner rounding.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which corner rounding is done.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CornerRoundingSetAxes(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the CornerRoundingSetTolerance command to the command queue.
///		Configures the tolerance to use for corner rounding.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] tolerance The rounding tolerance, in user units.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CornerRoundingSetTolerance(Automation1CommandQueue commandQueue, double tolerance);

/// @brief Adds the GearingOff command to the command queue.
///		Disables gearing on an axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] followerAxis The axis on which to disable gearing.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GearingOff(Automation1CommandQueue commandQueue, int32_t followerAxis);

/// @brief Adds the GearingOn command to the command queue.
///		Enables gearing on an axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] followerAxis The axis on which to enable gearing.
/// @param[In] filter Type of filter applied to follower axis motion.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GearingOn(Automation1CommandQueue commandQueue, int32_t followerAxis, Automation1GearingFilter filter);

/// @brief Adds the GearingSetLeaderAxis command to the command queue.
///		Configures gearing for an axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] followerAxis Follower axis for the gearing setup.
/// @param[In] leaderAxis Leader axis for the gearing setup.
/// @param[In] gearingSource Input data source for gearing.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GearingSetLeaderAxis(Automation1CommandQueue commandQueue, int32_t followerAxis, int32_t leaderAxis, Automation1GearingSource gearingSource);

/// @brief Adds the GearingSetRatio command to the command queue.
///		Sets the gearing ratio for an axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] followerAxis The axis on which to set the gear ratio.
/// @param[In] gearRatio The scale factor applied to the motion of the follower axis, specified as the ratio of follower axis counts to leader axis counts. A negative gear ratio will cause the follower axis to move in the opposite direction of the motion of the leader axis.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GearingSetRatio(Automation1CommandQueue commandQueue, int32_t followerAxis, double gearRatio);

/// @brief Adds the MoveOutOfLimit command to the command queue.
///		Executes an asynchronous move on an axis to move it out of a limit condition.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to perform the move.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveOutOfLimit(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the MoveToLimitCcw command to the command queue.
///		Executes an asynchronous move on an axis to move it into a limit condition in the counterclockwise direction.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to perform the move.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveToLimitCcw(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the MoveToLimitCw command to the command queue.
///		Executes an asynchronous move on an axis to move it into a limit condition in the clockwise direction.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to perform the move.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveToLimitCw(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the NormalcyOff command to the command queue.
///		Disables normalcy mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_NormalcyOff(Automation1CommandQueue commandQueue);

/// @brief Adds the NormalcyOn command to the command queue.
///		Enables normalcy mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] normalcyAlignment The type of the normalcy mode.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_NormalcyOn(Automation1CommandQueue commandQueue, Automation1NormalcyAlignment normalcyAlignment);

/// @brief Adds the NormalcySetAxes command to the command queue.
///		Configures the axes to use for normalcy mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] normalcyAxis The normalcy axis. This must be a dependent type axis.
/// @param[In] planeAxes The axes to use as the X and Y axes of the normalcy plane. These axes must be dominant type axes.
/// @param[In] planeAxesLength The number of elements in the planeAxes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_NormalcySetAxes(Automation1CommandQueue commandQueue, int32_t normalcyAxis, int32_t* planeAxes, int32_t planeAxesLength);

/// @brief Adds the NormalcySetTolerance command to the command queue.
///		Configures the tolerance to use for normalcy mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] tolerance The normalcy mode tolerance, in degrees.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_NormalcySetTolerance(Automation1CommandQueue commandQueue, double tolerance);

/// @brief Adds the VelocityBlendingOff command to the command queue.
///		Disables velocity profiling mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_VelocityBlendingOff(Automation1CommandQueue commandQueue);

/// @brief Adds the VelocityBlendingOn command to the command queue.
///		Enables velocity profiling mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_VelocityBlendingOn(Automation1CommandQueue commandQueue);

/// @brief Adds the TuningSetFeedforwardGains command to the command queue.
///		Sets the specified feedforward gain values on the specified axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the gain values.
/// @param[In] feedforwardGains An array of feedforward gains to set.
/// @param[In] feedforwardGainsLength The number of elements in the feedforwardGains function argument.
/// @param[In] feedforwardGainValues An array of feedforward gain values to set.
/// @param[In] feedforwardGainValuesLength The number of elements in the feedforwardGainValues function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_TuningSetFeedforwardGains(Automation1CommandQueue commandQueue, int32_t axis, Automation1FeedforwardGain* feedforwardGains, int32_t feedforwardGainsLength, double* feedforwardGainValues, int32_t feedforwardGainValuesLength);

/// @brief Adds the TuningSetMotorAngle command to the command queue.
///		Generates an open-loop current command at a fixed electrical angle.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to command current.
/// @param[In] current The current to output, specified in amperes.
/// @param[In] angle The electrical angle, specified in degrees. 360 degrees is one electrical commutation cycle of the motor.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_TuningSetMotorAngle(Automation1CommandQueue commandQueue, int32_t axis, double current, double angle);

/// @brief Adds the TuningSetMotorCurrent command to the command queue.
///		Generates an open-loop current command at a rotating electrical angle.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to command current.
/// @param[In] current The current to output, specified in amperes.
/// @param[In] duration The amount of time to output current, specified in milliseconds. Specify 0 to output current continuously.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_TuningSetMotorCurrent(Automation1CommandQueue commandQueue, int32_t axis, double current, int64_t duration);

/// @brief Adds the TuningSetServoLoopGains command to the command queue.
///		Sets the specified servo loop gain values on the specified axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the gain values.
/// @param[In] servoGains An array of servo loop gains to set.
/// @param[In] servoGainsLength The number of elements in the servoGains function argument.
/// @param[In] servoGainValues An array of servo loop gain values to set.
/// @param[In] servoGainValuesLength The number of elements in the servoGainValues function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_TuningSetServoLoopGains(Automation1CommandQueue commandQueue, int32_t axis, Automation1ServoLoopGain* servoGains, int32_t servoGainsLength, double* servoGainValues, int32_t servoGainValuesLength);

/// @brief Adds the GalvoConfigureLaser1PulseWidth command to the command queue.
///		Specifies the pulse width, in microseconds, of the O1 signal.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the laser 1 pulse width.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoConfigureLaser1PulseWidth(Automation1CommandQueue commandQueue, int32_t axis, double time);

/// @brief Adds the GalvoConfigureLaser2PulseWidth command to the command queue.
///		Specifies the pulse width, in microseconds, of the O2 signal.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the laser 2 pulse width.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoConfigureLaser2PulseWidth(Automation1CommandQueue commandQueue, int32_t axis, double time);

/// @brief Adds the GalvoConfigureLaserDelays command to the command queue.
///		Specifies when the axis fires the laser relative to when you command the laser to power on and when the axis stops firing the laser relative to when you command the laser to power off.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure laser delays.
/// @param[In] onDelay The delay time, in microseconds, that is necessary for the laser to power on. If your program uses the automatic laser mode, this value must be greater than or equal to -32,768 and less than or equal to 32,767. If your program uses the manual laser mode or if you are operating in IFOV mode, this value be must greater than or equal to -975 and less than or equal to 32,767.
/// @param[In] offDelay The delay time, in microseconds, that is necessary for the laser to power off. This value be must greater than or equal to -975 and less than or equal to 2,000,000.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoConfigureLaserDelays(Automation1CommandQueue commandQueue, int32_t axis, double onDelay, double offDelay);

/// @brief Adds the GalvoConfigureLaserMode command to the command queue.
///		Specifies the mode in which the laser output signals operate.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the laser mode.
/// @param[In] laserMode The value of the laser output mode.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoConfigureLaserMode(Automation1CommandQueue commandQueue, int32_t axis, int64_t laserMode);

/// @brief Adds the GalvoConfigureLaserOutputPeriod command to the command queue.
///		Specifies the period, in microseconds, of the O1 and O2 signals.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the laser output period.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoConfigureLaserOutputPeriod(Automation1CommandQueue commandQueue, int32_t axis, double time);

/// @brief Adds the GalvoConfigureStandbyPeriod command to the command queue.
///		Specifies the period, in microseconds, of the standby signals.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the standby period.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoConfigureStandbyPeriod(Automation1CommandQueue commandQueue, int32_t axis, double time);

/// @brief Adds the GalvoConfigureStandbyPulseWidth command to the command queue.
///		Specifies the pulse width, in microseconds, of the standby signals.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the standby pulse width.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoConfigureStandbyPulseWidth(Automation1CommandQueue commandQueue, int32_t axis, double time);

/// @brief Adds the GalvoConfigureSuppressionPulseWidth command to the command queue.
///		Specifies the pulse width, in microseconds, of the suppression signal.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the suppression pulse width.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoConfigureSuppressionPulseWidth(Automation1CommandQueue commandQueue, int32_t axis, double time);

/// @brief Adds the GalvoEncoderScaleFactorSet command to the command queue.
///		Enables "marking on the fly" functionality.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the encoder scale factor.
/// @param[In] encoderScaleFactor The ratio of scanner counts to encoder counts. This value must be greater than -32,768 and less than 32,767.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoEncoderScaleFactorSet(Automation1CommandQueue commandQueue, int32_t axis, double encoderScaleFactor);

/// @brief Adds the GalvoLaserOutput command to the command queue.
///		Specifies how the laser on a galvo axis is controlled.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the laser state.
/// @param[In] laserState The mode to use to control the laser.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoLaserOutput(Automation1CommandQueue commandQueue, int32_t axis, Automation1GalvoLaser laserState);

/// @brief Adds the GalvoProjectionOff command to the command queue.
///		Disables the projective transformation on galvo axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The galvo axis on which to disable the projection.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoProjectionOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the GalvoProjectionOn command to the command queue.
///		Enables the projective transformation on galvo axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The galvo axis on which to apply the projection.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoProjectionOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the GalvoProjectionSetCoefficients command to the command queue.
///		Specifies the projective transformation coefficients that are applied to galvo axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The galvo axis on which the projection is to be applied.
/// @param[In] coefficients The coefficients to use.
/// @param[In] coefficientsLength The number of elements in the coefficients function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoProjectionSetCoefficients(Automation1CommandQueue commandQueue, int32_t axis, double* coefficients, int32_t coefficientsLength);

/// @brief Adds the GalvoRotationSet command to the command queue.
///		Specifies an angle of rotation that is applied to galvo axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The galvo axis on which the rotation is to be applied.
/// @param[In] angle The angle in degrees.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoRotationSet(Automation1CommandQueue commandQueue, int32_t axis, double angle);

/// @brief Adds the GalvoWobbleOff command to the command queue.
///		Disables the galvo wobble feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The galvo axis on which the galvo wobble is to be disabled.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoWobbleOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the GalvoWobbleOn command to the command queue.
///		Enables the galvo wobble feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The galvo axis on which the galvo wobble is to be applied.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoWobbleOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the GalvoWobbleSetConfiguration command to the command queue.
///		Configures the wobble feature, which generates a wobble pattern that is added to the motion command of a galvo axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The galvo axis on which the galvo wobble is to be applied.
/// @param[In] amplitudeParallel The amplitude of the wobble shape parallel to the vector path.
/// @param[In] amplitudePerpendicular The amplitude of the wobble shape perpendicular to the vector path.
/// @param[In] frequency The frequency of the wobble oscillation. Specified in hertz for time-based mode or user units for distance-based mode.
/// @param[In] wobbleMode Specifies whether the wobble is repeated based on a fixed time or a fixed vector distance.
/// @param[In] wobbleType The type of figure that is generated by the wobble.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_GalvoWobbleSetConfiguration(Automation1CommandQueue commandQueue, int32_t axis, double amplitudeParallel, double amplitudePerpendicular, double frequency, Automation1GalvoWobbleMode wobbleMode, Automation1GalvoWobbleType wobbleType);

/// @brief Adds the IfovOff command to the command queue.
///		Disables Infinite Field of View (IFOV).
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_IfovOff(Automation1CommandQueue commandQueue);

/// @brief Adds the IfovOn command to the command queue.
///		Enables Infinite Field of View (IFOV).
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_IfovOn(Automation1CommandQueue commandQueue);

/// @brief Adds the IfovSetAxisPairs command to the command queue.
///		Configures axes to command in Infinite Field of View (IFOV).
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axisPairH The horizontal axis pair. This pair consists of a galvo axis and its corresponding servo axis.
/// @param[In] axisPairHLength The number of elements in the axisPairH function argument.
/// @param[In] axisPairV The vertical axis pair. This pair consists of a galvo axis and its corresponding servo axis.
/// @param[In] axisPairVLength The number of elements in the axisPairV function argument.
/// @param[In] scaleFactorH Specifies the scaling from the servo axis to the galvo axis in the horizontal axis pair.
/// @param[In] scaleFactorV Specifies the scaling from the servo axis to the galvo axis in the vertical axis pair.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_IfovSetAxisPairs(Automation1CommandQueue commandQueue, int32_t* axisPairH, int32_t axisPairHLength, int32_t* axisPairV, int32_t axisPairVLength, double scaleFactorH, double scaleFactorV);

/// @brief Adds the IfovSetSize command to the command queue.
///		Configures the field of view size of the galvo head in Infinite Field of View (IFOV).
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] size The field of view size, in user units, of the galvo head.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_IfovSetSize(Automation1CommandQueue commandQueue, double size);

/// @brief Adds the IfovSetSyncAxes command to the command queue.
///		Configures more axes to command in Infinite Field of View (IFOV).
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes A list of axes to synchronize in Infinite Field of View in addition to those specified in IfovSetAxisPairs().
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_IfovSetSyncAxes(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the IfovSetTime command to the command queue.
///		Configures the maximum search time that the controller looks ahead in Infinite Field of View (IFOV).
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] time The time, in milliseconds, that the controller looks ahead.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_IfovSetTime(Automation1CommandQueue commandQueue, int64_t time);

/// @brief Adds the IfovSetTrackingAcceleration command to the command queue.
///		Configures the maximum acceleration of the servo axes while in Infinite Field of View (IFOV).
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] acceleration The maximum acceleration, in user units/second squared, of the servo axes.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_IfovSetTrackingAcceleration(Automation1CommandQueue commandQueue, double acceleration);

/// @brief Adds the IfovSetTrackingSpeed command to the command queue.
///		Configures the maximum speed of the servo axes while in Infinite Field of View (IFOV).
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] speed The maximum speed, in user units/time base, of the servo axes.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_IfovSetTrackingSpeed(Automation1CommandQueue commandQueue, double speed);

/// @brief Adds the SetupAxisRampType command to the command queue.
///		Sets a ramp type along with a ramp type value for accelerations and decelerations separately for an axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the ramp type.
/// @param[In] rampTypeAccel The ramping type to set during accelerations.
/// @param[In] rampTypeArgAccel The ramping type additional argument for accelerations. This is only used when $rampTypeAccel is RampType.SCurve and represents the s-curve percentage.
/// @param[In] rampTypeDecel The ramping type to set during decelerations.
/// @param[In] rampTypeArgDecel The ramping type additional argument for decelerations. This is only used when $rampTypeDecel is RampType.SCurve and represents the s-curve percentage.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupAxisRampType(Automation1CommandQueue commandQueue, int32_t axis, Automation1RampType rampTypeAccel, double rampTypeArgAccel, Automation1RampType rampTypeDecel, double rampTypeArgDecel);

/// @brief Adds the SetupAxisRampValue command to the command queue.
///		Sets a ramp value for accelerations and decelerations separately for an axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the ramp value.
/// @param[In] rampModeAccel The ramping mode to set during accelerations.
/// @param[In] rampValueAccel The ramp value to set during accelerations.
/// @param[In] rampModeDecel The ramping mode to set during decelerations.
/// @param[In] rampValueDecel The ramp value to set during decelerations.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupAxisRampValue(Automation1CommandQueue commandQueue, int32_t axis, Automation1RampMode rampModeAccel, double rampValueAccel, Automation1RampMode rampModeDecel, double rampValueDecel);

/// @brief Adds the SetupAxisSpeed command to the command queue.
///		Sets the speed of an axis for MoveRapid() motion.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the speed.
/// @param[In] speed The speed to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupAxisSpeed(Automation1CommandQueue commandQueue, int32_t axis, double speed);

/// @brief Adds the SetupCoordinatedAccelLimit command to the command queue.
///		Sets the maximum acceleration of coordinated motion on dominant axes on the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] accelLimitNonTangent The maximum acceleration of axes at non-tangent portions of a motion path.
/// @param[In] accelLimitCircular The maximum acceleration of axes at curved parts of a motion path.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupCoordinatedAccelLimit(Automation1CommandQueue commandQueue, double accelLimitNonTangent, double accelLimitCircular);

/// @brief Adds the SetupCoordinatedRampType command to the command queue.
///		Sets a coordinated ramp type along with a ramp type value for accelerations and decelerations separately for dominant axes on the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] rampTypeAccel The ramping type to set during accelerations.
/// @param[In] rampTypeArgAccel The ramping type additional argument for accelerations. This is only used when $rampTypeAccel is RampType.SCurve and represents the s-curve percentage.
/// @param[In] rampTypeDecel The ramping type to set during decelerations.
/// @param[In] rampTypeArgDecel The ramping type additional argument for decelerations. This is only used when $rampTypeDecel is RampType.SCurve and represents the s-curve percentage.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupCoordinatedRampType(Automation1CommandQueue commandQueue, Automation1RampType rampTypeAccel, double rampTypeArgAccel, Automation1RampType rampTypeDecel, double rampTypeArgDecel);

/// @brief Adds the SetupCoordinatedRampValue command to the command queue.
///		Sets a coordinated ramp value for accelerations and decelerations separately for dominant axes on the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] rampModeAccel The ramping mode to set during accelerations.
/// @param[In] rampValueAccel The ramp value to set during accelerations.
/// @param[In] rampModeDecel The ramping mode to set during decelerations.
/// @param[In] rampValueDecel The ramp value to set during decelerations.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupCoordinatedRampValue(Automation1CommandQueue commandQueue, Automation1RampMode rampModeAccel, double rampValueAccel, Automation1RampMode rampModeDecel, double rampValueDecel);

/// @brief Adds the SetupCoordinatedSpeed command to the command queue.
///		Sets the coordinated speed for dominant axes on the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] speed The speed to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupCoordinatedSpeed(Automation1CommandQueue commandQueue, double speed);

/// @brief Adds the SetupDependentCoordinatedAccelLimit command to the command queue.
///		Sets the maximum acceleration of coordinated motion on dependent axes on the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] accelLimitDependent The maximum acceleration of axes at all portions of a motion path.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupDependentCoordinatedAccelLimit(Automation1CommandQueue commandQueue, double accelLimitDependent);

/// @brief Adds the SetupDependentCoordinatedRampRate command to the command queue.
///		Sets a coordinated ramp rate for accelerations and decelerations separately for dependent axes on the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] rampValueAccel The ramp rate value to set during accelerations.
/// @param[In] rampValueDecel The ramp rate value to set during decelerations.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupDependentCoordinatedRampRate(Automation1CommandQueue commandQueue, double rampValueAccel, double rampValueDecel);

/// @brief Adds the SetupDependentCoordinatedSpeed command to the command queue.
///		Sets the coordinated speed for dependent axes on the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] speed The speed to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupDependentCoordinatedSpeed(Automation1CommandQueue commandQueue, double speed);

/// @brief Adds the SetupTaskDistanceUnits command to the command queue.
///		Sets the distance units of the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] distanceUnits The distance units to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupTaskDistanceUnits(Automation1CommandQueue commandQueue, Automation1DistanceUnits distanceUnits);

/// @brief Adds the SetupTaskTargetMode command to the command queue.
///		Sets the target mode of the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] targetMode The target mode to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupTaskTargetMode(Automation1CommandQueue commandQueue, Automation1TargetMode targetMode);

/// @brief Adds the SetupTaskTimeUnits command to the command queue.
///		Sets the time units of the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] timeUnits The time units to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupTaskTimeUnits(Automation1CommandQueue commandQueue, Automation1TimeUnits timeUnits);

/// @brief Adds the SetupTaskWaitMode command to the command queue.
///		Sets the wait mode of the current task.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] waitMode The wait mode to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SetupTaskWaitMode(Automation1CommandQueue commandQueue, Automation1WaitMode waitMode);

/// @brief Adds the SafeZoneBoundaryAdd command to the command queue.
///		Adds a boundary to the specified safe zone.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] zone The index of the safe zone on which to add a boundary.
/// @param[In] axis The axis that represents the boundary to add.
/// @param[In] lowerBound The safe zone lower boundary, specified in user units.
/// @param[In] upperBound The safe zone upper boundary, specified in user units.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SafeZoneBoundaryAdd(Automation1CommandQueue commandQueue, int64_t zone, int32_t axis, double lowerBound, double upperBound);

/// @brief Adds the SafeZoneBoundaryRemove command to the command queue.
///		Removes the specified boundary from the specified safe zone.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] zone The index of the safe zone on which to remove a boundary.
/// @param[In] axis The axis that represents the boundary to remove.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SafeZoneBoundaryRemove(Automation1CommandQueue commandQueue, int64_t zone, int32_t axis);

/// @brief Adds the SafeZoneBoundaryRemoveAll command to the command queue.
///		Removes all boundaries from the specified safe zone.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] zone The index of the safe zone on which to remove all boundaries.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SafeZoneBoundaryRemoveAll(Automation1CommandQueue commandQueue, int64_t zone);

/// @brief Adds the SafeZoneOff command to the command queue.
///		Disables the specified safe zone.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] zone The safe zone to disable.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SafeZoneOff(Automation1CommandQueue commandQueue, int64_t zone);

/// @brief Adds the SafeZoneOn command to the command queue.
///		Enables the specified safe zone.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] zone The safe zone to enable.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SafeZoneOn(Automation1CommandQueue commandQueue, int64_t zone);

/// @brief Adds the SafeZoneSetType command to the command queue.
///		Sets the safe zone type for the specified safe zone.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] zone The safe zone on which to set the safe zone type.
/// @param[In] zoneType The safe zone type to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_SafeZoneSetType(Automation1CommandQueue commandQueue, int64_t zone, Automation1SafeZoneType zoneType);

/// @brief Adds the CTransformationDisable command to the command queue.
///		Disable a C transformation. This will stop running inverse and forward computations for this transformation.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] transformationName The name specified in the C Transformation configuration.
///		This string argument must be null terminated.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CTransformationDisable(Automation1CommandQueue commandQueue, const char* transformationName);

/// @brief Adds the CTransformationEnable command to the command queue.
///		Enable a C transformation. This will begin running inverse and forward computations for the specified transformation. All axes part of the transformation must be enabled at any time the transformation is enabled. If the transformation is enabled while there is synchronous motion on the same task, then the motion program will wait for motion to complete before enabling the transformation.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] transformationName The name specified in the C Transformation configuration.
///		This string argument must be null terminated.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CTransformationEnable(Automation1CommandQueue commandQueue, const char* transformationName);

/// @brief Adds the CTransformationSetInputAxes command to the command queue.
///		Set the input axes of a C transformation.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] transformationName The name specified in the C Transformation configuration.
///		This string argument must be null terminated.
/// @param[In] inputAxes The input axes of the transformation. Motion from these axes are input to the transformation.
/// @param[In] inputAxesLength The number of elements in the inputAxes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CTransformationSetInputAxes(Automation1CommandQueue commandQueue, const char* transformationName, int32_t* inputAxes, int32_t inputAxesLength);

/// @brief Adds the CTransformationSetOutputAxes command to the command queue.
///		Set the output axes of a C transformation.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] transformationName The name specified in the C Transformation configuration.
///		This string argument must be null terminated.
/// @param[In] outputAxes The output axes of the transformation. The transformation outputs motion to these axes.
/// @param[In] outputAxesLength The number of elements in the outputAxes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CTransformationSetOutputAxes(Automation1CommandQueue commandQueue, const char* transformationName, int32_t* outputAxes, int32_t outputAxesLength);

/// @brief Adds the CTransformationSetProperty command to the command queue.
///		Call the OnSetProperty() C function defined in a C transformation.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] transformationName The name specified in the C Transformation configuration.
///		This string argument must be null terminated.
/// @param[In] property The property argument provided to the OnSetProperty() C function.
///		This string argument must be null terminated.
/// @param[In] value The value argument provided to the OnSetProperty() C function.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CTransformationSetProperty(Automation1CommandQueue commandQueue, const char* transformationName, const char* property, double value);

/// @brief Adds the CalibrationLoad command to the command queue.
///		Loads and activates the specified axis calibration file or galvo power correction file.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] calibrationType The type of calibration that the specified file represents.
/// @param[In] controllerFileName The path to the file to be loaded as a calibration file.
///		This string argument must be null terminated.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CalibrationLoad(Automation1CommandQueue commandQueue, Automation1CalibrationType calibrationType, const char* controllerFileName);

/// @brief Adds the CalibrationUnload command to the command queue.
///		Deactivates and unloads the calibration for the specified calibration type.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] calibrationType The type of calibration to be unloaded.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_CalibrationUnload(Automation1CommandQueue commandQueue, Automation1CalibrationType calibrationType);

/// @brief Adds the DriveAnalogAccelerationFeedforwardConfigureInput command to the command queue.
///		Configures the relationship between the acceleration feedforward and analog input voltage, where Acceleration Feedforward = (Analog Input Voltage - ($inputOffset / 1000)) x $inputScale.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the configuration for the Drive Analog Acceleration Feedforward feature.
/// @param[In] analogInputNum The analog input signal used in the acceleration feedforward computation.
/// @param[In] inputScale The scale value used in the acceleration feedforward computation to convert from volts to units/second^2.
/// @param[In] inputOffset The offset value in millivolts used in the acceleration feedforward computation. This argument has a minimum value of -1000 and a maximum value of 1000.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogAccelerationFeedforwardConfigureInput(Automation1CommandQueue commandQueue, int32_t axis, int64_t analogInputNum, double inputScale, double inputOffset);

/// @brief Adds the DriveAnalogAccelerationFeedforwardOff command to the command queue.
///		Disables the Drive Analog Acceleration Feedforward feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable the Drive Analog Acceleration Feedforward feature.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogAccelerationFeedforwardOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveAnalogAccelerationFeedforwardOn command to the command queue.
///		Enables the Drive Analog Acceleration Feedforward feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable the Drive Analog Acceleration Feedforward feature.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogAccelerationFeedforwardOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveAnalogCurrentControlConfigureInput command to the command queue.
///		Configures the relationship between the output current and analog input voltage, where Current = (Analog Input Voltage - ($inputOffset / 1000)) x $inputScale.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the configuration for the Drive Analog Current Control feature.
/// @param[In] analogInputNum The analog input signal used in the current computation.
/// @param[In] digitalInputNum The digital input signal used to enable and disable the axis.
/// @param[In] inputScale The scale value used in the current computation to convert from volts to amps.
/// @param[In] inputOffset The offset value in millivolts used in the current computation. This argument has a minimum value of -1000 and a maximum value of 1000.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogCurrentControlConfigureInput(Automation1CommandQueue commandQueue, int32_t axis, int64_t analogInputNum, int64_t digitalInputNum, double inputScale, double inputOffset);

/// @brief Adds the DriveAnalogCurrentControlOff command to the command queue.
///		Disables the Drive Analog Current Control feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable the Drive Analog Current Control feature.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogCurrentControlOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveAnalogCurrentControlOn command to the command queue.
///		Enables the Drive Analog Current Control feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable the Drive Analog Current Control feature.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogCurrentControlOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveAnalogPositionControlConfigureInput command to the command queue.
///		Configures the relationship between the output position and analog input voltage, where Position = (Analog Input Voltage - $inputOffset) x $inputScale + (Starting Position). Starting Position is the position of the axis at the time DriveAnalogPositionControlOn() is called.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the configuration for the Drive Analog Position Control feature.
/// @param[In] inputNum The analog input signal used in the position computation.
/// @param[In] inputScale The scale value used in the position computation.
/// @param[In] inputOffset The offset value used in the position computation.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogPositionControlConfigureInput(Automation1CommandQueue commandQueue, int32_t axis, int64_t inputNum, double inputScale, double inputOffset);

/// @brief Adds the DriveAnalogPositionControlConfigureSpeedClamp command to the command queue.
///		Configures the maximum speed at which the controller commands the axis to move using the Drive Analog Position Control feature. If you do not use this function, then the controller does not limit the maximum speed.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the configuration for the Drive Analog Position Control feature.
/// @param[In] maxSpeed The speed in user units per second. If you specify a value of 0 for this argument, then the controller does not limit the maximum speed.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogPositionControlConfigureSpeedClamp(Automation1CommandQueue commandQueue, int32_t axis, double maxSpeed);

/// @brief Adds the DriveAnalogPositionControlOff command to the command queue.
///		Disable the Drive Analog Position Control feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable the Drive Analog Position Control feature.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogPositionControlOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveAnalogPositionControlOn command to the command queue.
///		Enable the Drive Analog Position Control feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable the Drive Analog Position Control feature.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogPositionControlOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveAnalogVelocityControlConfigureInput command to the command queue.
///		Configures the relationship between the output velocity and analog input voltage, where Velocity = (Analog Input Voltage - ($inputOffset / 1000)) x $inputScale.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the configuration for the Drive Analog Velocity Control feature.
/// @param[In] analogInputNum The analog input signal used in the velocity computation.
/// @param[In] digitalInputNum The digital input signal used to enable and disable the axis.
/// @param[In] inputScale The scale value used in the velocity computation to convert from volts to units/second.
/// @param[In] inputOffset The offset value in millivolts used in the velocity computation. This argument has a minimum value of -1000 and a maximum value of 1000.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogVelocityControlConfigureInput(Automation1CommandQueue commandQueue, int32_t axis, int64_t analogInputNum, int64_t digitalInputNum, double inputScale, double inputOffset);

/// @brief Adds the DriveAnalogVelocityControlOff command to the command queue.
///		Disables the Drive Analog Velocity Control feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable the Drive Analog Current Control feature.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogVelocityControlOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveAnalogVelocityControlOn command to the command queue.
///		Enables the Drive Analog Velocity Control feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable the Drive Analog Velocity Control feature.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogVelocityControlOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveAnalogVelocityFeedforwardConfigureInput command to the command queue.
///		Configures the relationship between the velocity feedforward and analog input voltage, where Velocity Feedforward = (Analog Input Voltage - ($inputOffset / 1000)) x $inputScale.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the configuration for the Drive Analog Velocity Feedforward feature.
/// @param[In] analogInputNum The analog input signal used in the velocity feedforward computation.
/// @param[In] inputScale The scale value used in the velocity feedforward computation to convert from volts to units/second.
/// @param[In] inputOffset The offset value in millivolts used in the velocity feedforward computation. This argument has a minimum value of -1000 and a maximum value of 1000.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogVelocityFeedforwardConfigureInput(Automation1CommandQueue commandQueue, int32_t axis, int64_t analogInputNum, double inputScale, double inputOffset);

/// @brief Adds the DriveAnalogVelocityFeedforwardOff command to the command queue.
///		Disables the Drive Analog Velocity Feedforward feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable the Drive Analog Velocity Feedforward feature.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogVelocityFeedforwardOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the DriveAnalogVelocityFeedforwardOn command to the command queue.
///		Enables the Drive Analog Velocity Feedforward feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable the Drive Analog Velocity Feedforward feature.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DriveAnalogVelocityFeedforwardOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the AutofocusOff command to the command queue.
///		Disables autofocus on an axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable autofocus.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_AutofocusOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the AutofocusOn command to the command queue.
///		Enables autofocus on an axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable autofocus.
/// @param[In] focusMode Selects if autofocus will run in continuous focus or single focus mode.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_AutofocusOn(Automation1CommandQueue commandQueue, int32_t axis, Automation1AutofocusFocusMode focusMode);

/// @brief Adds the PsoBitmapConfigureArray command to the command queue.
///		Configures an array of PSO bit data words, where each word is a 32-bit integer.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the bit data.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first word of bit data is stored.
/// @param[In] numberOfPoints The number of bit data words to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use bit data words after the last word in the array is used, starting over at the first word.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoBitmapConfigureArray(Automation1CommandQueue commandQueue, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t enableRepeat);

/// @brief Adds the PsoDistanceConfigureAllowedEventDirection command to the command queue.
///		Configures the distance counter tracking directions that will cause PSO distance events.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the distance event directions.
/// @param[In] eventDirection The distance event directions to set.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoDistanceConfigureAllowedEventDirection(Automation1CommandQueue commandQueue, int32_t axis, Automation1PsoDistanceAllowedEventDirection eventDirection);

/// @brief Adds the PsoDistanceConfigureArrayDistances command to the command queue.
///		Configures an array of distances in counts that the PSO counter or counters must travel for an event to occur.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the distances.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first distance is stored.
/// @param[In] numberOfDistances The number of distances to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use distances after the last distance in the array is used, starting over at the first distance.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoDistanceConfigureArrayDistances(Automation1CommandQueue commandQueue, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfDistances, int64_t enableRepeat);

/// @brief Adds the PsoDistanceConfigureCounterReset command to the command queue.
///		Configures the conditions which will reset the PSO distance counters.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the distance counter reset conditions.
/// @param[In] optionsMask A bitmask of PSO distance counter reset options. Use the values from the PsoDistanceCounterResetMask enum.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoDistanceConfigureCounterReset(Automation1CommandQueue commandQueue, int32_t axis, int64_t optionsMask);

/// @brief Adds the PsoDistanceConfigureFixedDistance command to the command queue.
///		Configures the distance in counts that the PSO counter or counters must travel for an event to occur.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the distance.
/// @param[In] distance The distance in counts.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoDistanceConfigureFixedDistance(Automation1CommandQueue commandQueue, int32_t axis, int64_t distance);

/// @brief Adds the PsoDistanceConfigureInputs command to the command queue.
///		Selects the source of each PSO distance counter.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the distance counter sources.
/// @param[In] inputs An array of one to three input sources, one for each distance counter.
/// @param[In] inputsLength The number of elements in the inputs function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoDistanceConfigureInputs(Automation1CommandQueue commandQueue, int32_t axis, Automation1PsoDistanceInput* inputs, int32_t inputsLength);

/// @brief Adds the PsoDistanceConfigureScaling command to the command queue.
///		Configures the PSO distance counters to apply an integer scale factor for each tracking input.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the scale factors.
/// @param[In] scaleFactors An array of one to three integer scale factors, one per tracking input.
/// @param[In] scaleFactorsLength The number of elements in the scaleFactors function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoDistanceConfigureScaling(Automation1CommandQueue commandQueue, int32_t axis, int64_t* scaleFactors, int32_t scaleFactorsLength);

/// @brief Adds the PsoDistanceCounterOff command to the command queue.
///		Disables the PSO distance counters, causing them to retain their values and ignore their configured inputs.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable the PSO distance counters.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoDistanceCounterOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoDistanceCounterOn command to the command queue.
///		Enables the PSO distance counters, allowing them to track their configured inputs.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable the PSO distance counters.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoDistanceCounterOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoDistanceEventsOff command to the command queue.
///		Disables PSO distance events.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable distance events.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoDistanceEventsOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoDistanceEventsOn command to the command queue.
///		Enables PSO distance events.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable distance events.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoDistanceEventsOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoEventConfigureMask command to the command queue.
///		Configures additional conditions to prevent PSO events from occurring.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the event mask conditions.
/// @param[In] eventMask A bitmask of event mask conditions. Use the values from the PsoEventMask enum.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoEventConfigureMask(Automation1CommandQueue commandQueue, int32_t axis, int64_t eventMask);

/// @brief Adds the PsoEventContinuousOff command to the command queue.
///		Immediately halts active continuous PSO events.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to halt the events.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoEventContinuousOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoEventContinuousOn command to the command queue.
///		Immediately causes continuous PSO events to occur.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to cause the events.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoEventContinuousOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoEventGenerateSingle command to the command queue.
///		Immediately causes a single PSO event to occur.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to cause the event.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoEventGenerateSingle(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoLaserEventsOff command to the command queue.
///		Disables PSO laser events.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable PSO laser events.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoLaserEventsOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoLaserEventsOn command to the command queue.
///		Configures the PSO to generate an event when the laser command bit turns on.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to generate laser PSO events.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoLaserEventsOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoOutputConfigureOutput command to the command queue.
///		Selects the output pin on which to drive the PSO output.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to select the PSO output pin.
/// @param[In] output The selected output pin.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoOutputConfigureOutput(Automation1CommandQueue commandQueue, int32_t axis, Automation1PsoOutputPin output);

/// @brief Adds the PsoOutputConfigureSource command to the command queue.
///		Selects which internal PSO signal to drive onto the output pin.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to select the PSO output source.
/// @param[In] outputSource The selected output source.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoOutputConfigureSource(Automation1CommandQueue commandQueue, int32_t axis, Automation1PsoOutputSource outputSource);

/// @brief Adds the PsoOutputOff command to the command queue.
///		Immediately deactivates the PSO output.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to deactivate the PSO output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoOutputOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoOutputOn command to the command queue.
///		Immediately activates the PSO output.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to activate the PSO output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoOutputOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoReset command to the command queue.
///		Resets all PSO configuration, which restores all PSO settings to their default values.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to reset the PSO configuration.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoReset(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoWaveformApplyPulseConfiguration command to the command queue.
///		Checks for a valid configuration of pulse mode parameters and applies the configuration to the waveform module.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the pulse configuration.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformApplyPulseConfiguration(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoWaveformApplyPwmConfiguration command to the command queue.
///		Checks for a valid configuration of PWM mode parameters and applies the configuration to the waveform module.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the PWM configuration.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformApplyPwmConfiguration(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoWaveformConfigureDelay command to the command queue.
///		Configures the waveform module to wait for the specified time after a PSO event before beginning to output a waveform.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the waveform output delay.
/// @param[In] delayTime The delay time in microseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigureDelay(Automation1CommandQueue commandQueue, int32_t axis, double delayTime);

/// @brief Adds the PsoWaveformConfigureMode command to the command queue.
///		Selects the output mode of the waveform module.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to select the output mode of the waveform module.
/// @param[In] waveformMode Mode selection for the waveform module output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigureMode(Automation1CommandQueue commandQueue, int32_t axis, Automation1PsoWaveformMode waveformMode);

/// @brief Adds the PsoWaveformConfigurePulseArrayCounts command to the command queue.
///		Configures an array of pulse counts for a sequence of waveform module outputs in pulse mode. The pulse count specifies the number of periods that will be generated from a single PSO event.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the pulse counts.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first pulse count is stored.
/// @param[In] numberOfPoints The number of pulse counts to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use pulse counts after the last pulse count in the array is used, starting over at the first pulse count.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePulseArrayCounts(Automation1CommandQueue commandQueue, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t enableRepeat);

/// @brief Adds the PsoWaveformConfigurePulseArrayOnTimes command to the command queue.
///		Configures an array of on times for a sequence of waveform module outputs in pulse mode. The on time specifies the active portion of the pulse period.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the on times.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first on time is stored.
/// @param[In] numberOfPoints The number of on times to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use on times after the last on time in the array is used, starting over at the first on time.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePulseArrayOnTimes(Automation1CommandQueue commandQueue, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t enableRepeat);

/// @brief Adds the PsoWaveformConfigurePulseArrayTotalTimes command to the command queue.
///		Configures an array of total times for a sequence of waveform module outputs in pulse mode. The total time specifies the full period of the pulse.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the total times.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first total time is stored.
/// @param[In] numberOfPoints The number of total times to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use total times after the last total time in the array is used, starting over at the first total time.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePulseArrayTotalTimes(Automation1CommandQueue commandQueue, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t enableRepeat);

/// @brief Adds the PsoWaveformConfigurePulseEventQueue command to the command queue.
///		Configures the maximum number of events in the queue. Each event in the queue will cause a PSO waveform pulse generation to occur after the active waveform period completes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the queue for the PSO waveform pulse event.
/// @param[In] maxQueuedEvents The maximum number of events to put in the queue.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePulseEventQueue(Automation1CommandQueue commandQueue, int32_t axis, int64_t maxQueuedEvents);

/// @brief Adds the PsoWaveformConfigurePulseFixedCount command to the command queue.
///		Configures the fixed pulse count of the waveform module output in pulse mode, which will be applied to all pulses. The pulse count specifies the number of periods that will be generated from a single PSO event.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the number of pulses.
/// @param[In] pulseCount The integer number of pulses.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePulseFixedCount(Automation1CommandQueue commandQueue, int32_t axis, int64_t pulseCount);

/// @brief Adds the PsoWaveformConfigurePulseFixedOnTime command to the command queue.
///		Configures the fixed on time of the waveform module output in pulse mode, which will be applied to all pulses. The on time specifies the active portion of the pulse period.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the on time.
/// @param[In] onTime The on time in microseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePulseFixedOnTime(Automation1CommandQueue commandQueue, int32_t axis, double onTime);

/// @brief Adds the PsoWaveformConfigurePulseFixedTotalTime command to the command queue.
///		Configures the fixed total time of the waveform module output in pulse mode, which will be applied to all pulses. The total time specifies the full period of the pulse.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the total time.
/// @param[In] totalTime The total time in microseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePulseFixedTotalTime(Automation1CommandQueue commandQueue, int32_t axis, double totalTime);

/// @brief Adds the PsoWaveformConfigurePulseMask command to the command queue.
///		Configures additional conditions to disable the PSO waveform output in pulse mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure PSO waveform pulse mode masking options.
/// @param[In] pulseMask A bitmask of PSO waveform pulse mode masking options. Use the values from the PsoWaveformPulseMask enum.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePulseMask(Automation1CommandQueue commandQueue, int32_t axis, int64_t pulseMask);

/// @brief Adds the PsoWaveformConfigurePulseTruncation command to the command queue.
///		Allows or prevents the waveform module from outputting truncated waveform outputs in pulse mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the pulse truncation prevention feature.
/// @param[In] preventTruncation Configures the waveform module to not allow the generation of truncated waveform outputs in pulse mode.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePulseTruncation(Automation1CommandQueue commandQueue, int32_t axis, int64_t preventTruncation);

/// @brief Adds the PsoWaveformConfigurePwmOnTimes command to the command queue.
///		Configures an array of on times for a sequence of waveform module outputs in PWM mode. The on time specifies the variable active portion of the PWM signal.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the on times.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first on time is stored.
/// @param[In] numberOfPoints The number of on times to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use on times after the last on time in the array is used, starting over at the first on time.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePwmOnTimes(Automation1CommandQueue commandQueue, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t enableRepeat);

/// @brief Adds the PsoWaveformConfigurePwmTotalTime command to the command queue.
///		Configures the fixed total time of the waveform module output in PWM mode. The total time specifies the full period of the PWM signal.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the total time.
/// @param[In] totalTime The total time in microseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformConfigurePwmTotalTime(Automation1CommandQueue commandQueue, int32_t axis, double totalTime);

/// @brief Adds the PsoWaveformExternalSyncOff command to the command queue.
///		Disables the external sync option for the waveform module.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable external sync option.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformExternalSyncOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoWaveformExternalSyncOn command to the command queue.
///		Configures the waveform module to wait for the rising edge of the external sync signal before beginning to output a waveform.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable external sync option.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformExternalSyncOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoWaveformOff command to the command queue.
///		Disables the waveform module, preventing PSO events from triggering it.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable the waveform module.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoWaveformOn command to the command queue.
///		Enables the waveform module, allowing PSO events to trigger it.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable the waveform module.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoWaveformScalingConfigure command to the command queue.
///		Specifies the configuration of the optional PSO waveform scaling feature.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure PSO waveform scaling.
/// @param[In] scalingMode Specifies the waveform parameters to which to apply the PSO waveform scaling.
/// @param[In] scalingInput Specifies the input to the PSO waveform scaling.
/// @param[In] inputRange Specifies the range of values in which the configured input will be used to calculate the scale factor to apply to the waveform parameters.
/// @param[In] inputRangeLength The number of elements in the inputRange function argument.
/// @param[In] scaleFactorRange Specifies the valid range of scale factor outputs from the PSO waveform scaling feature.
/// @param[In] scaleFactorRangeLength The number of elements in the scaleFactorRange function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformScalingConfigure(Automation1CommandQueue commandQueue, int32_t axis, Automation1PsoWaveformScalingMode scalingMode, Automation1PsoWaveformScalingInput scalingInput, double* inputRange, int32_t inputRangeLength, double* scaleFactorRange, int32_t scaleFactorRangeLength);

/// @brief Adds the PsoWaveformScalingOff command to the command queue.
///		Deactivates PSO waveform scaling.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to deactivate PSO waveform scaling.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformScalingOff(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoWaveformScalingOn command to the command queue.
///		Activates PSO waveform scaling.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to activate PSO waveform scaling.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWaveformScalingOn(Automation1CommandQueue commandQueue, int32_t axis);

/// @brief Adds the PsoWindowConfigureArrayRanges command to the command queue.
///		Configures an array of window range pairs each consisting of a lower bound followed by an upper bound.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the window ranges.
/// @param[In] windowNumber The number of the window on which to configure the ranges.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the lower bound of the first range pair is stored.
/// @param[In] numberOfRanges The number of range value pairs to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use range pairs after the last range pair in the array is used, starting over at the first range pair.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWindowConfigureArrayRanges(Automation1CommandQueue commandQueue, int32_t axis, int64_t windowNumber, int64_t driveArrayStartAddress, int64_t numberOfRanges, int64_t enableRepeat);

/// @brief Adds the PsoWindowConfigureArrayUpdateDirection command to the command queue.
///		Configures the array of window range pairs to update when exiting the active window range in specific directions.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the window array update direction.
/// @param[In] windowNumber The number of the window on which to configure the array update direction.
/// @param[In] windowUpdateDirection Mode selection to select the active window range exit directions on which to update the window range.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWindowConfigureArrayUpdateDirection(Automation1CommandQueue commandQueue, int32_t axis, int64_t windowNumber, Automation1PsoWindowUpdateDirection windowUpdateDirection);

/// @brief Adds the PsoWindowConfigureCounterReset command to the command queue.
///		Configures the conditions which will reset the PSO window counters.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the window counter reset conditions.
/// @param[In] optionsMask A bitmask of PSO window counter reset options. Use the values from the PsoWindowCounterResetMask enum.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWindowConfigureCounterReset(Automation1CommandQueue commandQueue, int32_t axis, int64_t optionsMask);

/// @brief Adds the PsoWindowConfigureEvents command to the command queue.
///		Configures the conditions which will generate PSO window events.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the window event conditions.
/// @param[In] eventMode The specified window event mode.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWindowConfigureEvents(Automation1CommandQueue commandQueue, int32_t axis, Automation1PsoWindowEventMode eventMode);

/// @brief Adds the PsoWindowConfigureFixedRange command to the command queue.
///		Configures a fixed window range consisting of a lower bound and an upper bound for the specified window.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to configure the window range.
/// @param[In] windowNumber The number of the window on which to configure the range.
/// @param[In] lowerBound The value for the window range lower bound.
/// @param[In] upperBound The value for the window range upper bound.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWindowConfigureFixedRange(Automation1CommandQueue commandQueue, int32_t axis, int64_t windowNumber, int64_t lowerBound, int64_t upperBound);

/// @brief Adds the PsoWindowConfigureInput command to the command queue.
///		Selects the source of the specified window counter.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to select the window counter input source.
/// @param[In] windowNumber The window number for which to select the counter input source.
/// @param[In] input The window counter input source.
/// @param[In] reverseDirection Configures the window counter to count in the opposite direction of its input source.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWindowConfigureInput(Automation1CommandQueue commandQueue, int32_t axis, int64_t windowNumber, Automation1PsoWindowInput input, int64_t reverseDirection);

/// @brief Adds the PsoWindowCounterSetValue command to the command queue.
///		Sets the specified window counter to the specified value.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the window counter.
/// @param[In] windowNumber The number of the window on which to set the counter.
/// @param[In] value The new counter value.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWindowCounterSetValue(Automation1CommandQueue commandQueue, int32_t axis, int64_t windowNumber, int64_t value);

/// @brief Adds the PsoWindowOutputOff command to the command queue.
///		Disables the specified window output.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to disable the window output.
/// @param[In] windowNumber The number of the window on which to disable the output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWindowOutputOff(Automation1CommandQueue commandQueue, int32_t axis, int64_t windowNumber);

/// @brief Adds the PsoWindowOutputOn command to the command queue.
///		Enables the specified window output.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to enable the window output.
/// @param[In] windowNumber The number of the window on which to enable the output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PsoWindowOutputOn(Automation1CommandQueue commandQueue, int32_t axis, int64_t windowNumber);

/// @brief Adds the AnalogOutputConfigureArrayMode command to the command queue.
///		Configures the specified analog output to use values from the drive array.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the configuration.
/// @param[In] outputNum The number of the analog output to configure.
/// @param[In] updateEvent The event which causes a new analog output value to be read from the drive array.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first analog output value is stored.
/// @param[In] numberOfPoints The number of analog output values to read from the drive array.
/// @param[In] divisor Divides the default update event rate by the specified integer if $updateEvent is set to Time.
/// @param[In] enableRepeat Configures the specified analog output to start over at the first analog output value after the last value in the drive array is used.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_AnalogOutputConfigureArrayMode(Automation1CommandQueue commandQueue, int32_t axis, int64_t outputNum, Automation1AnalogOutputUpdateEvent updateEvent, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t divisor, int64_t enableRepeat);

/// @brief Adds the AnalogOutputConfigureAxisTrackingMode command to the command queue.
///		Configures an analog output to be dependent on a specified real-time internal servo loop value of a single axis.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] outputAxis The axis on which to update the analog output.
/// @param[In] outputNum The index of the analog output to update.
/// @param[In] trackingItem A servo loop value, such as position command, to track.
/// @param[In] scaleFactor The scale factor applied to the analog output.
/// @param[In] offset This value is applied with the tracking value to the analog output. Use this argument if you want to track position on a stage where the position can never be negative. The units are volts.
/// @param[In] minVoltage The minimum voltage that the analog output will be set to.
/// @param[In] maxVoltage The maximum voltage that the analog output will be set to.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_AnalogOutputConfigureAxisTrackingMode(Automation1CommandQueue commandQueue, int32_t outputAxis, int64_t outputNum, Automation1AnalogOutputAxisTrackingItem trackingItem, double scaleFactor, double offset, double minVoltage, double maxVoltage);

/// @brief Adds the AnalogOutputConfigureDefaultMode command to the command queue.
///		Restores the analog output configuration to the default operating mode.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to apply the configuration.
/// @param[In] outputNum The number of the analog output to configure.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_AnalogOutputConfigureDefaultMode(Automation1CommandQueue commandQueue, int32_t axis, int64_t outputNum);

/// @brief Adds the AnalogOutputConfigureVectorTrackingMode command to the command queue.
///		Configures an analog output to be dependent on the square root of the sum of squares of a specified real-time internal servo loop value of multiple axes. The tracked value is always positive or zero.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] outputAxis The axis on which to update the analog output.
/// @param[In] outputNum The index of the analog output to update.
/// @param[In] inputAxes An array of axes from which to read the $trackingItem from, vectorizing the result, in order to update the analog output.
/// @param[In] inputAxesLength The number of elements in the inputAxes function argument.
/// @param[In] trackingItem A servo loop value, such as position command, to track.
/// @param[In] scaleFactor The scale factor applied to the analog output.
/// @param[In] offset This value is applied with the tracking value to the analog output. Use this argument if you want to track position on a stage where the position can never be negative. The units are volts.
/// @param[In] minVoltage The minimum voltage that the analog output will be set to.
/// @param[In] maxVoltage The maximum voltage that the analog output will be set to.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_AnalogOutputConfigureVectorTrackingMode(Automation1CommandQueue commandQueue, int32_t outputAxis, int64_t outputNum, int32_t* inputAxes, int32_t inputAxesLength, Automation1AnalogOutputVectorTrackingItem trackingItem, double scaleFactor, double offset, double minVoltage, double maxVoltage);

/// @brief Adds the AnalogOutputSet command to the command queue.
///		Sets the value of a specified analog output.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the value of the analog output.
/// @param[In] outputNum The number of the analog output to set.
/// @param[In] value The value to set to the specified analog output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_AnalogOutputSet(Automation1CommandQueue commandQueue, int32_t axis, int64_t outputNum, double value);

/// @brief Adds the DigitalOutputSet command to the command queue.
///		Sets the value of a specified digital output.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axis The axis on which to set the value of the digital output.
/// @param[In] outputNum The number of the output to set.
/// @param[In] value The value to set to the digital output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_DigitalOutputSet(Automation1CommandQueue commandQueue, int32_t axis, int64_t outputNum, int64_t value);

/// @brief Adds the VirtualBinaryInputSet command to the command queue.
///		Sets the value of a specified virtual binary input.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] inputNum The number of the virtual binary input to set.
/// @param[In] value The value to set to the virtual binary input.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_VirtualBinaryInputSet(Automation1CommandQueue commandQueue, int64_t inputNum, int64_t value);

/// @brief Adds the VirtualBinaryOutputSet command to the command queue.
///		Sets the value of a specified virtual binary output.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] outputNum The number of the virtual binary output to set.
/// @param[In] value The value to set to the virtual binary output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_VirtualBinaryOutputSet(Automation1CommandQueue commandQueue, int64_t outputNum, int64_t value);

/// @brief Adds the VirtualRegisterInputSet command to the command queue.
///		Sets the value of a specified virtual register input.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] inputNum The number of the virtual register input to set.
/// @param[In] value The value to set to the virtual register input.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_VirtualRegisterInputSet(Automation1CommandQueue commandQueue, int64_t inputNum, double value);

/// @brief Adds the VirtualRegisterOutputSet command to the command queue.
///		Sets the value of a specified virtual register output.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] outputNum The number of the virtual register output to set.
/// @param[In] value The value to set to the virtual register output.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_VirtualRegisterOutputSet(Automation1CommandQueue commandQueue, int64_t outputNum, double value);

/// @brief Adds the Dwell command to the command queue.
///		Suspends the execution of the task for a specified quantity of time.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] dwellTime The quantity of time to suspend the task, in seconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_Dwell(Automation1CommandQueue commandQueue, double dwellTime);

/// @brief Adds the Enable command to the command queue.
///		Enables the axes so that you can command motion.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes to enable.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_Enable(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the Home command to the command queue.
///		Performs a home cycle by moving the axes to a known hardware reference location. The task waits for completion of the home cycle.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes to home.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_Home(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the HomeAsync command to the command queue.
///		Performs a home cycle by moving the axes to a known hardware reference location. The controller performs the home cycle asynchronously so that the task moves on without waiting for completion.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes to home.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_HomeAsync(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the MoveAbsolute command to the command queue.
///		Executes an asynchronous point-to-point move to an absolute target-position on the specified axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to perform point-to-point motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] positions The absolute target-positions of the move.
/// @param[In] positionsLength The number of elements in the positions function argument.
/// @param[In] speeds The speeds at which to move the specified axes.
/// @param[In] speedsLength The number of elements in the speeds function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveAbsolute(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* positions, int32_t positionsLength, double* speeds, int32_t speedsLength);

/// @brief Adds the MoveCcw command to the command queue.
///		Executes a coordinated counterclockwise circular arc move on the specified axes. An arc move creates an arc in vector space using two axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to perform counterclockwise circular motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the circular arc.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] radius The radius of the circular arc.
/// @param[In] coordinatedSpeed The speed of the coordinated circular motion.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveCcwByRadius(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double radius, double coordinatedSpeed);

/// @brief Adds the MoveCcw command to the command queue.
///		Executes a coordinated counterclockwise circular arc move on the specified axes. An arc move creates an arc in vector space using two axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to perform counterclockwise circular motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the circular arc.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] center The relative offsets of the center point from the starting positions of the axes.
/// @param[In] centerLength The number of elements in the center function argument.
/// @param[In] coordinatedSpeed The speed of the coordinated circular motion.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveCcwByCenter(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double* center, int32_t centerLength, double coordinatedSpeed);

/// @brief Adds the MoveCw command to the command queue.
///		Executes a coordinated clockwise circular arc move on the specified axes. An arc move creates an arc in vector space using two axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to perform clockwise circular motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the circular arc.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] radius The radius of the circular arc.
/// @param[In] coordinatedSpeed The speed of the coordinated circular motion.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveCwByRadius(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double radius, double coordinatedSpeed);

/// @brief Adds the MoveCw command to the command queue.
///		Executes a coordinated clockwise circular arc move on the specified axes. An arc move creates an arc in vector space using two axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to perform clockwise circular motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the circular arc.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] center The relative offsets of the center point from the starting positions of the axes.
/// @param[In] centerLength The number of elements in the center function argument.
/// @param[In] coordinatedSpeed The speed of the coordinated circular motion.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveCwByCenter(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double* center, int32_t centerLength, double coordinatedSpeed);

/// @brief Adds the MoveDelay command to the command queue.
///		Commands axes to remain at zero velocity for a quantity of time.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to perform the delay.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] delayTime Total delay time in milliseconds, rounded to the nearest time interval of the MotionUpdateRate parameter.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveDelay(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double delayTime);

/// @brief Adds the MoveFreerun command to the command queue.
///		Executes an asynchronous freerun move on the specified axes. The axes will move indefinitely at the specified velocity.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to perform freerun motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] velocities The velocities at which to move the specified axes. The signs of the velocities specify the directions of motion.
/// @param[In] velocitiesLength The number of elements in the velocities function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveFreerun(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* velocities, int32_t velocitiesLength);

/// @brief Adds the MoveFreerunStop command to the command queue.
///		Stops an asynchronous freerun move on the specified axes. The axis velocities decelerate to zero.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to stop freerun motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveFreerunStop(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the MoveIncremental command to the command queue.
///		Executes an asynchronous point-to-point move by an incremental distance on the specified axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to perform point-to-point motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The distances and directions to move the specified axes relative to the current positions. A distance of zero results in no motion.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] speeds The speeds at which to move the specified axes.
/// @param[In] speedsLength The number of elements in the speeds function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveIncremental(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double* speeds, int32_t speedsLength);

/// @brief Adds the MoveLinear command to the command queue.
///		Executes a coordinated linear move on the specified axes. A linear move creates a line in vector space on one or more axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to perform linear motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the linear move.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] coordinatedSpeed The speed of the coordinated linear motion.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveLinear(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double coordinatedSpeed);

/// @brief Adds the MovePt command to the command queue.
///		Specifies a single point in an arbitrary motion profile. The point contains the position of one or more axes and a time interval. You must call this function for each point in the motion profile.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes of the motion profile point.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] positions The positions of each axis at the end of the time interval.
/// @param[In] positionsLength The number of elements in the positions function argument.
/// @param[In] time The total time interval of the motion profile point in milliseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MovePt(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* positions, int32_t positionsLength, double time);

/// @brief Adds the MovePvt command to the command queue.
///		Specifies a single point in an arbitrary motion profile. The point contains the position and velocity of one or more axes and a time interval. You must call this function for each point in the motion profile.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes of the motion profile point.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] positions The positions of each axis at the end of the time interval.
/// @param[In] positionsLength The number of elements in the positions function argument.
/// @param[In] velocities The velocities, in user units per time base, at which each axis will be moving at the end of the time interval.
/// @param[In] velocitiesLength The number of elements in the velocities function argument.
/// @param[In] time The total time interval of the motion profile point in milliseconds.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MovePvt(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* positions, int32_t positionsLength, double* velocities, int32_t velocitiesLength, double time);

/// @brief Adds the MoveRapid command to the command queue.
///		Executes a point-to-point rapid move on the specified axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to perform point-to-point rapid motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the rapid move.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] speeds The speeds at which to move each of the axes.
/// @param[In] speedsLength The number of elements in the speeds function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_MoveRapid(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double* speeds, int32_t speedsLength);

/// @brief Adds the PositionOffsetClear command to the command queue.
///		Clears the program position offsets on the specified axes. The program positions will be restored to the current axis positions.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to clear the program position offsets.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PositionOffsetClear(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the PositionOffsetSet command to the command queue.
///		Sets the program positions of the specified axes to the specified values. The controller applies an offset to the current axis positions so that the axes do not move. All moves that specify an absolute target-position will be relative to the new program position.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to set the program positions.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] programPositions The new program positions to set.
/// @param[In] programPositionsLength The number of elements in the programPositions function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_PositionOffsetSet(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength, double* programPositions, int32_t programPositionsLength);

/// @brief Adds the WaitForInPosition command to the command queue.
///		Waits for motion to be done on the specified axes and for the axes to be in position. The motion is done when the commanded velocity is at zero. The axes are in position when the position error is at the threshold specified by the InPositionTime and InPositionDistance parameters.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to wait for motion to be done and in position.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_WaitForInPosition(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the WaitForMotionDone command to the command queue.
///		Waits for motion to be done on the specified axes. The motion is done when the commanded velocity is at zero.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to wait for motion to be done.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_WaitForMotionDone(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the WorkOffsetConfigureOffset command to the command queue.
///		Configures the specified work offset on the specified axes and values. Previously configured axes will retain their values unless overwritten.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] offsetNumber The index of the work offset to configure. An integer between and including 1 and 100.
/// @param[In] axes The axes on which to configure work offset values.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] programPositions The program positions to set as the work offset origin.
/// @param[In] programPositionsLength The number of elements in the programPositions function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_WorkOffsetConfigureOffset(Automation1CommandQueue commandQueue, int64_t offsetNumber, int32_t* axes, int32_t axesLength, double* programPositions, int32_t programPositionsLength);

/// @brief Adds the WorkOffsetDisable command to the command queue.
///		Deactivates work offsets for all axes on the controller.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] axes The axes on which to disable work offsets.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_WorkOffsetDisable(Automation1CommandQueue commandQueue, int32_t* axes, int32_t axesLength);

/// @brief Adds the WorkOffsetEnable command to the command queue.
///		Activates the specified work offset and applies offsets to the specified axes.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @param[In] offsetNumber The index of the work offset to enable. An integer between and including 1 and 100.
/// @param[In] axes The axes on which to enable the specified work offset.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_WorkOffsetEnable(Automation1CommandQueue commandQueue, int64_t offsetNumber, int32_t* axes, int32_t axesLength);

/// @brief Adds the WorkOffsetResetConfiguration command to the command queue.
///		Erases the work offset configurations on all axes. All work offsets must first be disabled.
/// 	Executes on this command queue's task.
/// @param[In] commandQueue The command queue to add this AeroScript command to.
/// @return Returns true if the AeroScript command was successfully added to the command queue.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CommandQueue_WorkOffsetResetConfiguration(Automation1CommandQueue commandQueue);


#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1COMMANDQUEUE_H_INCLUDED
