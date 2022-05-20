#ifndef AUTOMATION1TASK_H_INCLUDED
#define AUTOMATION1TASK_H_INCLUDED

#if defined(_MSC_VER)
	#if defined(AUTOMATION1_CAPI_EXPORT)
		#define AUTOMATION1_CAPI __declspec(dllexport)
	#else
		#define AUTOMATION1_CAPI __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
	#define AUTOMATION1_CAPI __attribute__((visibility ("default")))
#endif

#include <stdbool.h>
#include <stdint.h>
#include "Automation1Controller.h"
#include "Automation1Enum.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Represents the status of a controller task on an Automation1 controller.
typedef struct Automation1TaskStatus
{
	/// @brief The task index corresponding to this status.
	int32_t TaskIndex;
	/// @brief The error on the task, if any. This will be zero if there is no error.
	int32_t Error;
	/// @brief The human readable error message corresponding to the error on the task, if any.
	/// 	This string will be empty if there is no error on the task.
	char ErrorMessage[2048];
	/// @brief The warning on the task, if any. This will be zero if there is no warning.
	int32_t Warning;
	/// @brief The human readable warning message corresponding to the warning on the task, if any.
	/// 	This string will be empty if there is no warning on the task.
	char WarningMessage[2048];
	/// @brief The state of execution for the task.
	Automation1TaskState TaskState;
	/// @brief The value of the task mode on the task.
	Automation1TaskMode TaskMode;
	/// @brief The null-terminated name of the compiled AeroScript file for the program that is loaded or running on the task.
	/// 	This string will be empty if no program is loaded.
	char AeroScriptSourceFileName[1024];
	/// @brief The null-terminated name of the compiled AeroScript file for the program that is loaded or running on the task.
	/// 	The name will be empty if no program is loaded.
	char CompiledAeroScriptFileName[1024];
} Automation1TaskStatus;

/// @brief Gets the current status of one or more tasks.
/// @param[In] controller The controller to get the array of task status from.
/// @param[Out] taskStatusArrayOut The out array of task status that was obtained from the controller.
/// 	The size of this array determines which tasks to obtain status for. For example, if this array has a size of 3, the status for task 0, task 1,
/// 	and task 2 are obtained from the controller and populated into the taskStatusArrayOut argument in that order.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] taskStatusArrayLength The maximum number of elements to copy to the taskStatusArrayOut argument.
///		This must not be greater than the length of the taskStatusArrayOut array.
/// @return Returns true if the task status was successfully obtained otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_GetStatus(Automation1Controller controller, Automation1TaskStatus* taskStatusArrayOut, int32_t taskStatusArrayLength);

/// @brief Runs the specified controller file as an AeroScript program on this task. If the controller file is an AeroScript source file then the file will first be compiled.
/// 	Running a program will automatically load the program and begin program execution on this task. This function waits for the program to load and start but it does not
/// 	wait for the program to complete.
/// 	The AeroScript program must exist as a controller file on the Automation1 controller.
/// 	AeroScript libraries cannot be run on a task, the controller file must be an AeroScript program (either a source program file or a compiled program file).
/// @param[In] controller The controller to run the program on.
/// @param[In] taskIndex The task to run the program on.
/// @param[In] controllerFileName The null-terminated name of the controller file that is the AeroScript program to run on this task (source program file or compiled program file).
/// @return Returns true if the program was successfully started on the specified task otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_ProgramRun(Automation1Controller controller, int32_t taskIndex, const char* controllerFileName);

/// @brief Loads the specified controller file as an AeroScript program on this task. If the controller file is an AeroScript source file then the file will first be compiled.
/// 	Loading does not start the program, you must call Automation1_Task_ProgramStart() to begin program execution on this task.
/// 	The AeroScript program must exist as a controller file on the Automation1 controller.
/// 	AeroScript libraries cannot be loaded on a task, the controller file must be an AeroScript program (either a source program file or a compiled program file).
/// @param[In] controller The controller to load the program onto.
/// @param[In] taskIndex The task to load the program onto.
/// @param[In] controllerFileName The null-terminated name of the controller file that is the AeroScript program to load on this task (source program file or compiled program file).
/// @return Returns true if the program was successfully loaded onto the specified task otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_ProgramLoad(Automation1Controller controller, int32_t taskIndex, const char* controllerFileName);

/// @brief Starts or resumes the currently loaded AeroScript program on this task, beginning program execution. A  program must be loaded on to
/// 	this task to be able to start or resume it. To load a program, call Automation1_Task_ProgramLoad. This function waits for the loaded program
/// 	to start but it does not wait for the program to complete.
/// @param[In] controller The controller to start or resume the program on.
/// @param[In] taskIndex The task to start or resume the program on.
/// @return Returns true if the program successfully started or resumed otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_ProgramStart(Automation1Controller controller, int32_t taskIndex);

/// @brief Stops the currently running AeroScript program on this task, terminating program execution.
/// 	This function will wait for the specified amount of time for the loaded program to stop. If the timeout is set to -1, this function will wait indefinitely.
/// 	This function will also stop queue mode and buffered run mode. After a program is stopped it is unloaded from the task.
/// @param[In] controller The controller to stop the program on.
/// @param[In] taskIndex The task to stop the program on.
/// @param[In] millisecondsTimeout The number of milliseconds to wait to stop the program on this task.
/// 	If the program takes longer than this amount of time to stop, the function will fail.
/// 	This function will wait indefinitely for the loaded program to stop if this value is set to - 1.
/// @return Returns true if the program stopped successfully before the specified amount of time otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_ProgramStop(Automation1Controller controller, int32_t taskIndex, int32_t millisecondsTimeout);

/// @brief Pauses the currently running AeroScript program on this task, suspending program execution.
/// 	This function will wait for the specified amount of time for the loaded program to pause. If the timeout is set to -1, this function will wait indefinitely.
/// 	To resume program execution, call Automation1_Task_ProgramStart().
/// @param[In] controller The controller to pause the program on.
/// @param[In] taskIndex The task to pause the program on.
/// @param[In] millisecondsTimeout The number of milliseconds to wait to pause the program on this task.
/// 	If the program takes longer than this amount of time to stop, the function will fail.
/// 	This function will wait indefinitely for the loaded program to stop if this value is set to - 1.
/// @return Returns true if the program paused successfully before the specified amount of time otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_ProgramPause(Automation1Controller controller, int32_t taskIndex, int32_t millisecondsTimeout);

/// @brief Performs a single line of program execution on the currently paused AeroScript program on this task, stepping into any function calls.
/// 	This function can only be called if there is an AeroScript program loaded on this task and it is paused.
/// @param[In] controller The controller to execute the single line of program execution on.
/// @param[In] taskIndex The task to execute the single line of program execution on.
/// @return Returns true if the single line of program execution executed successfully otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_DebugStepInto(Automation1Controller controller, int32_t taskIndex);

/// @brief Performs a single line of program execution on the currently paused AeroScript program on this task, stepping over any function calls.
/// 	This function can only be called if there is an AeroScript program loaded on this task and it is paused.
/// @param[In] controller The controller to execute the single line of program execution on.
/// @param[In] taskIndex The task to execute the single line of program execution on.
/// @return Returns true if the single line of program execution executed successfully otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_DebugStepOver(Automation1Controller controller, int32_t taskIndex);

/// @brief Performs execution on the currently paused AeroScript program on this task, stepping out of the current function call.
/// 	This function can only be called if there is an AeroScript program loaded on this task and it is paused.
/// @param[In] controller The controller to execute the single line of program execution on.
/// @param[In] taskIndex The task to execute the single line of program execution on.
/// @return Returns true if the single line of program execution executed successfully otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_DebugStepOut(Automation1Controller controller, int32_t taskIndex);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1TASK_H_INCLUDED