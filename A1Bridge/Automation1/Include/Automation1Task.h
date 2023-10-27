///
/// Copyright (c) Aerotech, Inc.
///

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

/// @brief A handle that represents the arguments provided to a callback by an AeroScript program.
///		This handle will be the first argument provided to your callback function.
///		Use the Automation1_Task_CallbackGetArguments() function to get the values of each argument using this handle.
typedef struct Automation1TaskCallbackArguments_T* Automation1TaskCallbackArguments;

/// @brief A handle that represents the values or error message that will be returned from a callback to an AeroScript program.
///		This handle will be the second argument provided to your callback function.
///		Use the Automation1_Task_CallbackSetReturn() function to set the return values if the callback was successful.
///		Use the Automation1_Task_CallbackSetErrorMessage() function to set the error message if the callback was unsuccessful.
typedef struct Automation1TaskCallbackReturn_T* Automation1TaskCallbackReturn;

/// @brief A function type that represents a callback that can be raised from an AeroScript program.
///		You must return true from this function type if the callback was successful, or return false if the callback was unsuccessful.
///		Use the Automation1_Task_CallbackRegister() function to register an Automation1TaskCallback function so that it can be raised from an AeroScript program.
///		You can only register a callback ID once per task. To change the registration of a callback ID, unregister it first. To do that see Automation1_Task_CallbackUnregister().
///		Use the Automation1_Task_CallbackGetArguments() function to get the arguments from the Automation1TaskCallbackArguments handle.
///		Use the Automation1_Task_CallbackSetReturn() function to set the return values of the Automation1TaskCallbackReturn handle.
///		Use the Automation1_Task_CallbackSetErrorMessage() function to set the error message of the Automation1TaskCallbackReturn handle.
typedef bool(*Automation1TaskCallback)(Automation1TaskCallbackArguments, Automation1TaskCallbackReturn);

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
/// 	After a program is stopped it is unloaded from the task. This function will also end a command queue running on this task.
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

/// @brief Registers a callback that can be raised by an AeroScript program. 
///		You must return true from the handler if the callback was successful, or return false if the callback was unsuccessful.
///		You can only register a callback ID once per task. To change the registration of a callback ID, unregister it first. To do that see Automation1_Task_CallbackUnregister().
/// @param[In] controller The controller to register a callback on.
/// @param[In] taskIndex The task to register a callback on.
/// @param[In] callbackId A number that uniquely identifies the callback per task.
/// @param[In] handler The code to execute when the callback is raised by an AeroScript program on this task.
/// @return Returns true if the callback was registered successfully otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_CallbackRegister(Automation1Controller controller, int32_t taskIndex, int32_t callbackId, Automation1TaskCallback handler);

/// @brief Unregisters a callback on a task.
/// @param[In] controller The controller to unregister a callback on.
/// @param[In] taskIndex The task to unregister a callback on.
/// @param[In] callbackId A number that uniquely identifies the callback per task.
/// @return Returns true if the callback was unregistered successfully otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_CallbackUnregister(Automation1Controller controller, int32_t taskIndex, int32_t callbackId);

/// @brief Gets the arguments provided to a callback by an AeroScript program.
/// @param[In] callbackArguments The callback arguments handle that is provided to a callback function.
/// @param[Out] taskIndexOut The task that this callback was raised on.
/// @param[Out] callbackIdOut The unique identifier of this callback on the task that it was raised on.
/// @param[Out] aeroScriptIntegersOut The array of integer values provided to the callback by an AeroScript program.
/// @param[Out] aeroScriptIntegersLengthOut The length of the aeroScriptIntegersOut array.
///		This argument will be set to the exact length if the aeroScriptIntegersOut argument is null.
///		If the aeroScriptIntegersOut argument is not null, this will be set to the number of integers that was actually copied into aeroScriptIntegersOut.
///		To avoid calling this function twice to get the exact size, set this parameter based on number of integers you would typically provide to your callback.
/// @param[Out] aeroScriptRealsOut The array of real values provided to the callback by an AeroScript program.
/// @param[Out] aeroScriptRealsLengthOut The length of the aeroScriptRealsOut array.
///		This argument will be set to the exact length if the aeroScriptRealsOut argument is null.
///		If the aeroScriptRealsOut argument is not null, this will be set to the number of reals that was actually copied into aeroScriptRealsOut.
///		To avoid calling this function twice to get the exact size, set this parameter based on number of reals you would typically provide to your callback.
/// @param[Out] aeroScriptStringsOut The array of string values provided to the callback by an AeroScript program.
///		AeroScript strings will be null-terminated and stored in succession based on the maxAeroScriptStringLengthOut argument.
///		The number of strings that will be copied is based on the aeroScriptStringsLengthOut argument.
///		The length of each string in aeroScriptStringsOut is based on the maxAeroScriptStringLengthOut argument.
///		Thus, the number of bytes that will be copied into this array is the product of the aeroScriptStringsLengthOut and maxAeroScriptStringLengthOut arguments.
///		Set this argument to null to get the exact values for the aeroScriptStringLengthsOut and maxAeroScriptStringLengthOut arguments.
/// @param[Out] aeroScriptStringsLengthOut The length of the aeroScriptStringsOut array.
///		This argument will be set to the exact length if the aeroScriptStringsOut argument is null.
///		If the aeroScriptStringsOut argument is not null, this will be set to the number of strings that was actually copied into aeroScriptStringsOut.
///		To avoid calling this function twice to get the exact size, set this parameter based on number of strings you would typically provide to your callback.
/// @param[Out] maxAeroScriptStringLengthOut The maximum length of each AeroScript string (including the null-terminator).
///		This argument will be set to the exact length if the aeroScriptStringsOut argument is null.
///		If aeroScriptStringsOut is not null, this will be set to the actual max string length that was used to copy strings into aeroScriptStringsOut.
///		To avoid calling this function twice to get the exact size, set this parameter to 1000 characters.
/// @return Returns true if all arguments were copied successfully otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_CallbackGetArguments(Automation1TaskCallbackArguments callbackArguments, int32_t* taskIndexOut, int32_t* callbackIdOut, int64_t* aeroScriptIntegersOut, int32_t* aeroScriptIntegersLengthOut, double* aeroScriptRealsOut, int32_t* aeroScriptRealsLengthOut, char* aeroScriptStringsOut, int32_t* aeroScriptStringsLengthOut, int32_t* maxAeroScriptStringLengthOut);

/// @brief Sets the values to return to an AeroScript program when this callback succeeds.
///		These values will only be returned to an AeroScript program if the callback that sets these values returns true.
/// @param[In] callbackReturn The callback return handle that is provided to a callback function.
/// @param[In] aeroScriptIntegers The array of integers to return to an AeroScript program.
/// @param[In] aeroScriptIntegersLength The length of the aeroScriptIntegers array.
/// @param[In] aeroScriptReals The array of reals to return to an AeroScript program.
/// @param[In] aeroScriptRealsLength The length of the aeroScriptReals array.
/// @param[In] aeroScriptStrings The array of null-terminated strings to return to an AeroScript program.
/// @param[In] aeroScriptStringsLength The length of the aeroScriptStrings array.
/// @return Returns true if the return values were set successfully otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_CallbackSetReturn(Automation1TaskCallbackReturn callbackReturn, int64_t* aeroScriptIntegers, int32_t aeroScriptIntegersLength, double* aeroScriptReals, int32_t aeroScriptRealsLength, const char** aeroScriptStrings, int32_t aeroScriptStringsLength);

/// @brief Sets the error message to return to an AeroScript program when this callback fails.
///		This error message will only be returned to an AeroScript program if the callback that sets the error message returns false.
/// @param[In] callbackReturn The callback return handle that is provided to a callback function.
/// @param[In] errorMessage The null-terminated string that will be displayed in the error message of an AeroScript program.
/// @return Returns true if the error message was set successfully otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Task_CallbackSetErrorMessage(Automation1TaskCallbackReturn callbackReturn, const char* errorMessage);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1TASK_H_INCLUDED