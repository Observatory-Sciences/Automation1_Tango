#ifndef AUTOMATION1COMMAND_H_INCLUDED
#define AUTOMATION1COMMAND_H_INCLUDED

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

/// @brief Executes an AeroScript command on the Automation1 controller on the specified task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] aeroScriptText The null-terminated AeroScript string text to compile and execute.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_Execute(Automation1Controller controller, int32_t executionTaskIndex, const char* aeroScriptText);

/// @brief Executes an AeroScript command on the Automation1 controller on the specified task and returns an AeroScript axis value (which is the index of the axis).
/// 	To get a return value from the AeroScript command, set the value of the AeroScript $areturn[0] property in the AeroScript command.
/// 	For example, you could set aeroScriptText function argument to "$areturn[0]=@1" so that this function sets the aeroScriptAxisIndexOut
/// 	argument to axis index 1 once the AeroScript has finished executing.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] aeroScriptText The null-terminated AeroScript string text to compile and execute.
/// @param[Out] aeroScriptAxisIndexOut The value of the AeroScript $areturn[0] property after the AeroScript command has executed.
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_ExecuteAndReturnAeroScriptAxis(Automation1Controller controller, int32_t executionTaskIndex, const char* aeroScriptText, int32_t* aeroScriptAxisIndexOut);

/// @brief Executes an AeroScript command on the Automation1 controller on the specified task and returns an AeroScript integer value.
/// 	To get a return value from the AeroScript command, set the value of the AeroScript $ireturn[0] property in the AeroScript command.
/// 	For example, you could set the aeroScriptText function argument to "$ireturn[0]=9999" so that this function sets the aeroScriptIntegerOut
/// 	argument to 9999 once the AeroScript has finished executing.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] aeroScriptText The null-terminated AeroScript string text to compile and execute.
/// @param[Out] aeroScriptIntegerOut The value of the AeroScript $ireturn[0] property after the AeroScript command has executed.
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_ExecuteAndReturnAeroScriptInteger(Automation1Controller controller, int32_t executionTaskIndex, const char* aeroScriptText, int64_t* aeroScriptIntegerOut);

/// @brief Executes an AeroScript command on the Automation1 controller on the specified task and returns an AeroScript real value.
/// 	To get a return value from the AeroScript command, set the value of the AeroScript $rreturn[0] property in the AeroScript command.
/// 	For example, you could set the aeroScriptText argument to "$rreturn[0]=0.0001" so that this function sets the aeroScriptRealOut
/// 	argument to 0.0001 once the AeroScript has finished executing.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] aeroScriptText The null-terminated AeroScript string text to compile and execute.
/// @param[Out] aeroScriptRealOut The value of the AeroScript $rreturn[0] property after the AeroScript command has executed.
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_ExecuteAndReturnAeroScriptReal(Automation1Controller controller, int32_t executionTaskIndex, const char* aeroScriptText, double* aeroScriptRealOut);

/// @brief Executes an AeroScript command on the Automation1 controller on the specified task and returns an AeroScript real value.
/// 	To get a return value from the AeroScript command, set the value of the AeroScript $sreturn[0] property in the AeroScript command.
/// 	For example, you could set the aeroScriptText argument to "$sreturn[0]=\"HelloWorld\"" so that this function sets the aeroScriptStringOut
/// 	argument to "HelloWorld" once the AeroScript has finished executing.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] aeroScriptText The null-terminated AeroScript string text to compile and execute.
/// @param[Out] aeroScriptStringOut The null-terminated value of the AeroScript $sreturn[0] property after the AeroScript command has executed.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] aeroScriptStringLength The maximum number of elements to copy into the aeroScriptStringOut argument.
/// 	This must not be great than the length of the aeroScriptStringOut array and must leave space for the null-terminator.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_ExecuteAndReturnAeroScriptString(Automation1Controller controller, int32_t executionTaskIndex, const char* aeroScriptText, char* aeroScriptStringOut, int32_t aeroScriptStringLength);

/// @brief Aborts motion on the specified axes. The controller stops all motion and ramps the axes to zero speed.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] axes The axes to abort. This argument is an array.
/// @param[In] axesLength The number of elements in the axes argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_Abort(Automation1Controller controller, int32_t* axes, int32_t axesLength);

/// @brief Disables the axes so that you cannot command motion.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] axes The axes to disable. This argument is an array.
/// @param[In] axesLength The number of elements in the axes argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_Disable(Automation1Controller controller, int32_t* axes, int32_t axesLength);

/// @brief Gets the value of a specified analog input.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to retrieve the value of the analog input.
/// @param[In] inputNum The number of the analog input to get.
/// @param[Out] returnOut The return value of the AeroScript command (represents an AeroScript real value).
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_AnalogInputGet(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t inputNum, double* returnOut);

/// @brief Gets the value of a specified analog output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to retrieve the value of the analog output.
/// @param[In] outputNum The number of the analog output to get.
/// @param[Out] returnOut The return value of the AeroScript command (represents an AeroScript real value).
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_AnalogOutputGet(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t outputNum, double* returnOut);

/// @brief Sets the value of a specified analog output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the value of the analog output.
/// @param[In] outputNum The number of the analog output to set.
/// @param[In] value The value to set to the specified analog output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_AnalogOutputSet(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t outputNum, double value);

/// @brief Gets the value of a specified digital input.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to retrieve the value of the digital input.
/// @param[In] inputNum The number of the digital input to get.
/// @param[Out] returnOut The return value of the AeroScript command (represents an AeroScript integer value).
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DigitalInputGet(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t inputNum, int64_t* returnOut);

/// @brief Gets the value of a specified digital output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to retrieve the value of the digital output.
/// @param[In] outputNum The number of the digital output to get.
/// @param[Out] returnOut The return value of the AeroScript command (represents an AeroScript integer value).
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DigitalOutputGet(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t outputNum, int64_t* returnOut);

/// @brief Sets the value of a specified digital output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the value of the digital output.
/// @param[In] outputNum The number of the output to set.
/// @param[In] value The value to set to the digital output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DigitalOutputSet(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t outputNum, int64_t value);

/// @brief Gets the value of a specified virtual binary input.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] inputNum The number of the virtual binary input to get.
/// @param[Out] returnOut The return value of the AeroScript command (represents an AeroScript integer value).
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_VirtualBinaryInputGet(Automation1Controller controller, int32_t executionTaskIndex, int64_t inputNum, int64_t* returnOut);

/// @brief Gets the value of a specified virtual binary output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] outputNum The number of the virtual binary output to get.
/// @param[Out] returnOut The return value of the AeroScript command (represents an AeroScript integer value).
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_VirtualBinaryOutputGet(Automation1Controller controller, int32_t executionTaskIndex, int64_t outputNum, int64_t* returnOut);

/// @brief Gets the value of a specified virtual register input.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] inputNum The number of the virtual register input to get.
/// @param[Out] returnOut The return value of the AeroScript command (represents an AeroScript real value).
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_VirtualRegisterInputGet(Automation1Controller controller, int32_t executionTaskIndex, int64_t inputNum, double* returnOut);

/// @brief Gets the value of a specified virtual register output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] outputNum The number of the virtual register output to get.
/// @param[Out] returnOut The return value of the AeroScript command (represents an AeroScript real value).
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_VirtualRegisterOutputGet(Automation1Controller controller, int32_t executionTaskIndex, int64_t outputNum, double* returnOut);

/// @brief Sets the value of a specified virtual binary input.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] inputNum The number of the virtual binary input to set.
/// @param[In] value The value to set to the virtual binary input.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_VirtualBinaryInputSet(Automation1Controller controller, int32_t executionTaskIndex, int64_t inputNum, int64_t value);

/// @brief Sets the value of a specified virtual binary output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] outputNum The number of the virtual binary output to set.
/// @param[In] value The value to set to the virtual binary output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_VirtualBinaryOutputSet(Automation1Controller controller, int32_t executionTaskIndex, int64_t outputNum, int64_t value);

/// @brief Sets the value of a specified virtual register input.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] inputNum The number of the virtual register input to set.
/// @param[In] value The value to set to the virtual register input.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_VirtualRegisterInputSet(Automation1Controller controller, int32_t executionTaskIndex, int64_t inputNum, double value);

/// @brief Sets the value of a specified virtual register output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] outputNum The number of the virtual register output to set.
/// @param[In] value The value to set to the virtual register output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_VirtualRegisterOutputSet(Automation1Controller controller, int32_t executionTaskIndex, int64_t outputNum, double value);

/// @brief Sets a ramp type along with a ramp type value for accelerations and decelerations separately for an axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the ramp type.
/// @param[In] rampTypeAccel The ramping type to set during accelerations.
/// @param[In] rampTypeArgAccel The ramping type additional argument for accelerations. This is only used when $rampTypeAccel is RampType.SCurve and represents the s-curve percentage.
/// @param[In] rampTypeDecel The ramping type to set during decelerations.
/// @param[In] rampTypeArgDecel The ramping type additional argument for decelerations. This is only used when $rampTypeDecel is RampType.SCurve and represents the s-curve percentage.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupAxisRampType(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1RampType rampTypeAccel, double rampTypeArgAccel, Automation1RampType rampTypeDecel, double rampTypeArgDecel);

/// @brief Sets a ramp value for accelerations and decelerations separately for an axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the ramp value.
/// @param[In] rampModeAccel The ramping mode to set during accelerations.
/// @param[In] rampValueAccel The ramp value to set during accelerations.
/// @param[In] rampModeDecel The ramping mode to set during decelerations.
/// @param[In] rampValueDecel The ramp value to set during decelerations.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupAxisRampValue(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1RampMode rampModeAccel, double rampValueAccel, Automation1RampMode rampModeDecel, double rampValueDecel);

/// @brief Sets the maximum acceleration of coordinated motion on dominant axes on the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] accelLimitNonTangent The maximum acceleration of axes at non-tangent portions of a motion path.
/// @param[In] accelLimitCircular The maximum acceleration of axes at curved parts of a motion path.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupCoordinatedAccelLimit(Automation1Controller controller, int32_t executionTaskIndex, double accelLimitNonTangent, double accelLimitCircular);

/// @brief Sets a coordinated ramp type along with a ramp type value for accelerations and decelerations separately for dominant axes on the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] rampTypeAccel The ramping type to set during accelerations.
/// @param[In] rampTypeArgAccel The ramping type additional argument for accelerations. This is only used when $rampTypeAccel is RampType.SCurve and represents the s-curve percentage.
/// @param[In] rampTypeDecel The ramping type to set during decelerations.
/// @param[In] rampTypeArgDecel The ramping type additional argument for decelerations. This is only used when $rampTypeDecel is RampType.SCurve and represents the s-curve percentage.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupCoordinatedRampType(Automation1Controller controller, int32_t executionTaskIndex, Automation1RampType rampTypeAccel, double rampTypeArgAccel, Automation1RampType rampTypeDecel, double rampTypeArgDecel);

/// @brief Sets a coordinated ramp value for accelerations and decelerations separately for dominant axes on the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] rampModeAccel The ramping mode to set during accelerations.
/// @param[In] rampValueAccel The ramp value to set during accelerations.
/// @param[In] rampModeDecel The ramping mode to set during decelerations.
/// @param[In] rampValueDecel The ramp value to set during decelerations.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupCoordinatedRampValue(Automation1Controller controller, int32_t executionTaskIndex, Automation1RampMode rampModeAccel, double rampValueAccel, Automation1RampMode rampModeDecel, double rampValueDecel);

/// @brief Sets the maximum acceleration of coordinated motion on dependent axes on the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] accelLimitDependent The maximum acceleration of axes at all portions of a motion path.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupDependentCoordinatedAccelLimit(Automation1Controller controller, int32_t executionTaskIndex, double accelLimitDependent);

/// @brief Sets a coordinated ramp rate for accelerations and decelerations separately for dependent axes on the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] rampValueAccel The ramp rate value to set during accelerations.
/// @param[In] rampValueDecel The ramp rate value to set during decelerations.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupDependentCoordinatedRampRate(Automation1Controller controller, int32_t executionTaskIndex, double rampValueAccel, double rampValueDecel);

/// @brief Sets the speed of an axis for MoveRapid() motion.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the speed.
/// @param[In] speed The speed to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupAxisSpeed(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double speed);

/// @brief Sets the coordinated speed for dominant axes on the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] speed The speed to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupCoordinatedSpeed(Automation1Controller controller, int32_t executionTaskIndex, double speed);

/// @brief Sets the coordinated speed for dependent axes on the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] speed The speed to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupDependentCoordinatedSpeed(Automation1Controller controller, int32_t executionTaskIndex, double speed);

/// @brief Sets the target mode of the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] targetMode The target mode to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupTaskTargetMode(Automation1Controller controller, int32_t executionTaskIndex, Automation1TargetMode targetMode);

/// @brief Sets the time units of the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] timeUnits The time units to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupTaskTimeUnits(Automation1Controller controller, int32_t executionTaskIndex, Automation1TimeUnits timeUnits);

/// @brief Sets the distance units of the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] distanceUnits The distance units to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupTaskDistanceUnits(Automation1Controller controller, int32_t executionTaskIndex, Automation1DistanceUnits distanceUnits);

/// @brief Sets the wait mode of the current task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] waitMode The wait mode to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SetupTaskWaitMode(Automation1Controller controller, int32_t executionTaskIndex, Automation1WaitMode waitMode);

/// @brief Enables the axes so that you can command motion.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes to enable.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_Enable(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength);

/// @brief Performs a home cycle by moving the axes to a known hardware reference location. The task waits for completion of the home cycle.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes to home.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_Home(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength);

/// @brief Performs a home cycle by moving the axes to a known hardware reference location. The controller performs the home cycle asynchronously so that the task moves on without waiting for completion.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes to home.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_HomeAsync(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength);

/// @brief Executes an asynchronous point-to-point move to an absolute target-position on the specified axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to perform point-to-point motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] positions The absolute target-positions of the move.
/// @param[In] positionsLength The number of elements in the positions function argument.
/// @param[In] speeds The speeds at which to move the specified axes.
/// @param[In] speedsLength The number of elements in the speeds function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveAbsolute(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* positions, int32_t positionsLength, double* speeds, int32_t speedsLength);

/// @brief Executes a coordinated counterclockwise circular arc move on the specified axes. An arc move creates an arc in vector space using two axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to perform counterclockwise circular motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the circular arc.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] radius The radius of the circular arc.
/// @param[In] coordinatedSpeed The speed of the coordinated circular motion.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveCcwByRadius(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double radius, double coordinatedSpeed);

/// @brief Executes a coordinated counterclockwise circular arc move on the specified axes. An arc move creates an arc in vector space using two axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to perform counterclockwise circular motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the circular arc.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] center The relative offsets of the center point from the starting positions of the axes.
/// @param[In] centerLength The number of elements in the center function argument.
/// @param[In] coordinatedSpeed The speed of the coordinated circular motion.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveCcwByCenter(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double* center, int32_t centerLength, double coordinatedSpeed);

/// @brief Executes a coordinated clockwise circular arc move on the specified axes. An arc move creates an arc in vector space using two axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to perform clockwise circular motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the circular arc.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] radius The radius of the circular arc.
/// @param[In] coordinatedSpeed The speed of the coordinated circular motion.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveCwByRadius(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double radius, double coordinatedSpeed);

/// @brief Executes a coordinated clockwise circular arc move on the specified axes. An arc move creates an arc in vector space using two axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to perform clockwise circular motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the circular arc.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] center The relative offsets of the center point from the starting positions of the axes.
/// @param[In] centerLength The number of elements in the center function argument.
/// @param[In] coordinatedSpeed The speed of the coordinated circular motion.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveCwByCenter(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double* center, int32_t centerLength, double coordinatedSpeed);

/// @brief Commands axes to remain at zero velocity for a quantity of time.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to perform the delay.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] delayTime Total delay time in milliseconds, rounded to the nearest time interval of the MotionUpdateRate parameter.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveDelay(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double delayTime);

/// @brief Executes an asynchronous freerun move on the specified axes. The axes will move indefinitely at the specified velocity.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to perform freerun motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] velocities The velocities at which to move the specified axes. The signs of the velocities specify the directions of motion.
/// @param[In] velocitiesLength The number of elements in the velocities function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveFreerun(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* velocities, int32_t velocitiesLength);

/// @brief Stops an asynchronous freerun move on the specified axes. The axis velocities decelerate to zero.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to stop freerun motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveFreerunStop(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength);

/// @brief Executes an asynchronous point-to-point move by an incremental distance on the specified axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to perform point-to-point motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The distances and directions to move the specified axes relative to the current positions. A distance of zero results in no motion.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] speeds The speeds at which to move the specified axes.
/// @param[In] speedsLength The number of elements in the speeds function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveIncremental(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double* speeds, int32_t speedsLength);

/// @brief Executes a coordinated linear move on the specified axes. A linear move creates a line in vector space on one or more axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to perform linear motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the linear move.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] coordinatedSpeed The speed of the coordinated linear motion.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveLinear(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double coordinatedSpeed);

/// @brief Specifies a single point in an arbitrary motion profile. The point contains the position of one or more axes and a time interval. You must call this function for each point in the motion profile.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes of the motion profile point.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] positions The positions of each axis at the end of the time interval.
/// @param[In] positionsLength The number of elements in the positions function argument.
/// @param[In] time The total time interval of the motion profile point in milliseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MovePt(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* positions, int32_t positionsLength, double time);

/// @brief Specifies a single point in an arbitrary motion profile. The point contains the position and velocity of one or more axes and a time interval. You must call this function for each point in the motion profile.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes of the motion profile point.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] positions The positions of each axis at the end of the time interval.
/// @param[In] positionsLength The number of elements in the positions function argument.
/// @param[In] velocities The velocities, in user units per time base, at which each axis will be moving at the end of the time interval.
/// @param[In] velocitiesLength The number of elements in the velocities function argument.
/// @param[In] time The total time interval of the motion profile point in milliseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MovePvt(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* positions, int32_t positionsLength, double* velocities, int32_t velocitiesLength, double time);

/// @brief Executes a point-to-point rapid move on the specified axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to perform point-to-point rapid motion.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] distances The end points of the rapid move.
/// @param[In] distancesLength The number of elements in the distances function argument.
/// @param[In] speeds The speeds at which to move each of the axes.
/// @param[In] speedsLength The number of elements in the speeds function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveRapid(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* distances, int32_t distancesLength, double* speeds, int32_t speedsLength);

/// @brief Waits for motion to be done on the specified axes and for the axes to be in position. The motion is done when the commanded velocity is at zero. The axes are in position when the position error is at the threshold specified by the InPositionTime and InPositionDistance parameters.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to wait for motion to be done and in position.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_WaitForInPosition(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength);

/// @brief Waits for motion to be done on the specified axes. The motion is done when the commanded velocity is at zero.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to wait for motion to be done.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_WaitForMotionDone(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength);

/// @brief Sets the program positions of the specified axes to the specified values. The controller applies an offset to the current axis positions so that the axes do not move. All moves that specify an absolute target-position will be relative to the new program position.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to set the program positions.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @param[In] programPositions The new program positions to set.
/// @param[In] programPositionsLength The number of elements in the programPositions function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PositionOffsetSet(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength, double* programPositions, int32_t programPositionsLength);

/// @brief Clears the program position offsets on the specified axes. The program positions will be restored to the current axis positions.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to clear the program position offsets.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PositionOffsetClear(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength);

/// @brief Unloads a camming table from the SMC.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] tableNum The table number to remove.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CammingFreeTable(Automation1Controller controller, int32_t executionTaskIndex, int64_t tableNum);

/// @brief Loads a camming table into the SMC.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] tableNum The table number to use. Use this number when using the CammingOn and CammingFreeTable functions.
/// @param[In] leaderValues Array of leader axis position values for the follower axis to track.
/// @param[In] leaderValuesLength The number of elements in the leaderValues function argument.
/// @param[In] followerValues Array of follower axis positions or velocities to use.
/// @param[In] followerValuesLength The number of elements in the followerValues function argument.
/// @param[In] numValues The number of values in the leaderValues and followerValues arrays.
/// @param[In] unitsMode The units of the values in the camming table.
/// @param[In] interpolationMode The interpolation type to use if the position of the leader axis is between two values in the table.
/// @param[In] wrapMode Determines how a leader axis position value outside of the table is treated.
/// @param[In] tableOffset An offset applied to all follower axis position or velocity values in the table.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CammingLoadTableFromArray(Automation1Controller controller, int32_t executionTaskIndex, int64_t tableNum, double* leaderValues, int32_t leaderValuesLength, double* followerValues, int32_t followerValuesLength, int64_t numValues, Automation1CammingUnits unitsMode, Automation1CammingInterpolation interpolationMode, Automation1CammingWrapping wrapMode, double tableOffset);

/// @brief Disables camming on the specified follower axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] followerAxis The follower axis on which to disable camming.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CammingOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t followerAxis);

/// @brief Enables camming on the specified leader axis and follower axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] followerAxis The axis to set as the follower axis.
/// @param[In] leaderAxis The axis to set as the leader axis.
/// @param[In] tableNum The camming table number to use.
/// @param[In] source The signal on the leader axis axis that the follower axis will track.
/// @param[In] output The output signal to generate and the synchronization mode to use on the camming follower axis.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CammingOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t followerAxis, int32_t leaderAxis, int64_t tableNum, Automation1CammingSource source, Automation1CammingOutput output);

/// @brief Disables corner rounding.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CornerRoundingOff(Automation1Controller controller, int32_t executionTaskIndex);

/// @brief Enables corner rounding.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CornerRoundingOn(Automation1Controller controller, int32_t executionTaskIndex);

/// @brief Configures axes to use for corner rounding.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which corner rounding is done.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CornerRoundingSetAxes(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength);

/// @brief Configures the tolerance to use for corner rounding.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] tolerance The rounding tolerance, in user units.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CornerRoundingSetTolerance(Automation1Controller controller, int32_t executionTaskIndex, double tolerance);

/// @brief Disables gearing on an axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] followerAxis The axis on which to disable gearing.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GearingOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t followerAxis);

/// @brief Enables gearing on an axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] followerAxis The axis on which to enable gearing.
/// @param[In] filter Type of filter applied to follower axis motion.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GearingOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t followerAxis, Automation1GearingFilter filter);

/// @brief Configures gearing for an axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] followerAxis Follower axis for the gearing setup.
/// @param[In] leaderAxis Leader axis for the gearing setup.
/// @param[In] gearingSource Input data source for gearing.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GearingSetLeaderAxis(Automation1Controller controller, int32_t executionTaskIndex, int32_t followerAxis, int32_t leaderAxis, Automation1GearingSource gearingSource);

/// @brief Sets the gearing ratio for an axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] followerAxis The axis on which to set the gear ratio.
/// @param[In] gearRatio Ratio to scale the follower axis motion to the leader axis motion (follower axis/leader axis).
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GearingSetRatio(Automation1Controller controller, int32_t executionTaskIndex, int32_t followerAxis, double gearRatio);

/// @brief Disables normalcy mode.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_NormalcyOff(Automation1Controller controller, int32_t executionTaskIndex);

/// @brief Enables normalcy mode.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] normalcyAlignment The type of the normalcy mode.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_NormalcyOn(Automation1Controller controller, int32_t executionTaskIndex, Automation1NormalcyAlignment normalcyAlignment);

/// @brief Configures the axes to use for normalcy mode.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] normalcyAxis The normalcy axis. This must be a dependent type axis.
/// @param[In] planeAxes The axes to use as the X and Y axes of the normalcy plane. These axes must be dominant type axes.
/// @param[In] planeAxesLength The number of elements in the planeAxes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_NormalcySetAxes(Automation1Controller controller, int32_t executionTaskIndex, int32_t normalcyAxis, int32_t* planeAxes, int32_t planeAxesLength);

/// @brief Configures the tolerance to use for normalcy mode.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] tolerance The normalcy mode tolerance, in degrees.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_NormalcySetTolerance(Automation1Controller controller, int32_t executionTaskIndex, double tolerance);

/// @brief Disables velocity profiling mode.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_VelocityBlendingOff(Automation1Controller controller, int32_t executionTaskIndex);

/// @brief Enables velocity profiling mode.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_VelocityBlendingOn(Automation1Controller controller, int32_t executionTaskIndex);

/// @brief Executes an asynchronous move on an axis to move it out of a limit condition.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to perform the move.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveOutOfLimit(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Executes an asynchronous move on an axis to move it into a limit condition in the counterclockwise direction.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to perform the move.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveToLimitCcw(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Executes an asynchronous move on an axis to move it into a limit condition in the clockwise direction.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to perform the move.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_MoveToLimitCw(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Adds a boundary to the specified safe zone.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] zone The index of the safe zone on which to add a boundary.
/// @param[In] axis The axis that represents the boundary to add.
/// @param[In] lowerBound The safe zone lower boundary, specified in user units.
/// @param[In] upperBound The safe zone upper boundary, specified in user units.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SafeZoneBoundaryAdd(Automation1Controller controller, int32_t executionTaskIndex, int64_t zone, int32_t axis, double lowerBound, double upperBound);

/// @brief Removes the specified boundary from the specified safe zone.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] zone The index of the safe zone on which to remove a boundary.
/// @param[In] axis The axis that represents the boundary to remove.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SafeZoneBoundaryRemove(Automation1Controller controller, int32_t executionTaskIndex, int64_t zone, int32_t axis);

/// @brief Removes all boundaries from the specified safe zone.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] zone The index of the safe zone on which to remove all boundaries.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SafeZoneBoundaryRemoveAll(Automation1Controller controller, int32_t executionTaskIndex, int64_t zone);

/// @brief Disables the specified safe zone.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] zone The safe zone to disable.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SafeZoneOff(Automation1Controller controller, int32_t executionTaskIndex, int64_t zone);

/// @brief Enables the specified safe zone.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] zone The safe zone to enable.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SafeZoneOn(Automation1Controller controller, int32_t executionTaskIndex, int64_t zone);

/// @brief Sets the safe zone type for the specified safe zone.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] zone The safe zone on which to set the safe zone type.
/// @param[In] zoneType The safe zone type to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_SafeZoneSetType(Automation1Controller controller, int32_t executionTaskIndex, int64_t zone, Automation1SafeZoneType zoneType);

/// @brief Acknowledges all axis faults and clears all task errors.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_AcknowledgeAll(Automation1Controller controller, int32_t executionTaskIndex);

/// @brief Acknowledges faults on axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes The axes on which to acknowledge faults.
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_FaultAcknowledge(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength);

/// @brief Causes faults on an axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to cause faults.
/// @param[In] faultMask The mask of faults to cause on the axis.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_FaultThrow(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t faultMask);

/// @brief Causes a specified task error on a task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] taskIndex The task on which to cause a task error.
/// @param[In] error The task error to cause.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_TaskSetError(Automation1Controller controller, int32_t executionTaskIndex, int64_t taskIndex, int64_t error);

/// @brief Causes a specified task warning on a task.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] taskIndex The task on which to cause a task warning.
/// @param[In] warning The task warning to cause.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_TaskSetWarning(Automation1Controller controller, int32_t executionTaskIndex, int64_t taskIndex, int64_t warning);

/// @brief Specifies the mode in which the laser output signals operate.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the laser 1 pulse width.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoConfigureLaser1PulseWidth(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double time);

/// @brief Specifies the mode in which the laser output signals operate.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the laser 2 pulse width.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoConfigureLaser2PulseWidth(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double time);

/// @brief Specifies when the axis fires the laser relative to when you command the laser to power on and when the axis stops firing the laser relative to when you command the laser to power off.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure laser delays.
/// @param[In] onDelay The delay time, in microseconds, that is necessary for the laser to power on. If your program uses the automatic laser mode, this value must be greater than or equal to -32,768 and less than or equal to 32,767. If your program uses the manual laser mode or if you are operating in IFOV mode, this value be must greater than or equal to -975 and less than or equal to 32,767.
/// @param[In] offDelay The delay time, in microseconds, that is necessary for the laser to power off. This value be must greater than or equal to -975 and less than or equal to 2,000,000.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoConfigureLaserDelays(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double onDelay, double offDelay);

/// @brief Specifies the mode in which the laser output signals operate.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the laser mode.
/// @param[In] laserMode The value of the laser output mode.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoConfigureLaserMode(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t laserMode);

/// @brief Specifies the mode in which the laser output signals operate.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the laser output period.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoConfigureLaserOutputPeriod(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double time);

/// @brief Specifies the mode in which the laser output signals operate.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the standby period.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoConfigureStandbyPeriod(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double time);

/// @brief Specifies the mode in which the laser output signals operate.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the standby pulse width.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoConfigureStandbyPulseWidth(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double time);

/// @brief Specifies the mode in which the laser output signals operate.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the suppression pulse width.
/// @param[In] time The time value in microseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoConfigureSuppressionPulseWidth(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double time);

/// @brief Specifies the mode in which the laser output signals operate.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the encoder scale factor.
/// @param[In] encoderScaleFactor The ratio of scanner counts to encoder counts. This value must be greater than -32,768 and less than 32,767.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoEncoderScaleFactorSet(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double encoderScaleFactor);

/// @brief Specifies how the laser on a galvo axis is controlled.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the laser state.
/// @param[In] laserState The mode to use to control the laser.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoLaserOutput(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1GalvoLaser laserState);

/// @brief Disables the projective transformation on galvo axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The galvo axis on which to disable the projection.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoProjectionOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Enables the projective transformation on galvo axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The galvo axis on which to apply the projection.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoProjectionOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Specifies the projective transformation coefficients that are applied to galvo axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The galvo axis on which the projection is to be applied.
/// @param[In] coefficients The coefficients to use.
/// @param[In] coefficientsLength The number of elements in the coefficients function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoProjectionSetCoefficients(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double* coefficients, int32_t coefficientsLength);

/// @brief Specifies an angle of rotation that is applied to galvo axes.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The galvo axis on which the rotation is to be applied.
/// @param[In] angle The angle in degrees.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoRotationSet(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double angle);

/// @brief Disables the galvo wobble feature.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The galvo axis on which the galvo wobble is to be disabled.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoWobbleOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Enables the galvo wobble feature.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The galvo axis on which the galvo wobble is to be applied.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoWobbleOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Configures the wobble feature, which generates a wobble pattern that is added to the motion command of a galvo axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The galvo axis on which the galvo wobble is to be applied.
/// @param[In] amplitudeParallel The amplitude of the wobble shape parallel to the vector path.
/// @param[In] amplitudePerpendicular The amplitude of the wobble shape perpendicular to the vector path.
/// @param[In] frequency The frequency of the wobble oscillation. Specified in hertz for time-based mode or user units for distance-based mode.
/// @param[In] wobbleMode Specifies whether the wobble is repeated based on a fixed time or a fixed vector distance.
/// @param[In] wobbleType The type of figure that is generated by the wobble.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_GalvoWobbleSetConfiguration(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double amplitudeParallel, double amplitudePerpendicular, double frequency, Automation1GalvoWobbleMode wobbleMode, Automation1GalvoWobbleType wobbleType);

/// @brief Disables Infinite Field of View (IFOV).
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_IfovOff(Automation1Controller controller, int32_t executionTaskIndex);

/// @brief Enables Infinite Field of View (IFOV).
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_IfovOn(Automation1Controller controller, int32_t executionTaskIndex);

/// @brief Configures axes to command in Infinite Field of View (IFOV).
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axisPairH The horizontal axis pair. This pair consists of a galvo axis and its corresponding servo axis.
/// @param[In] axisPairHLength The number of elements in the axisPairH function argument.
/// @param[In] axisPairV The vertical axis pair. This pair consists of a galvo axis and its corresponding servo axis.
/// @param[In] axisPairVLength The number of elements in the axisPairV function argument.
/// @param[In] scaleFactorH Specifies the scaling from the servo axis to the galvo axis in the horizontal axis pair.
/// @param[In] scaleFactorV Specifies the scaling from the servo axis to the galvo axis in the vertical axis pair.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_IfovSetAxisPairs(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axisPairH, int32_t axisPairHLength, int32_t* axisPairV, int32_t axisPairVLength, double scaleFactorH, double scaleFactorV);

/// @brief Configures the field of view size of the galvo head in Infinite Field of View (IFOV).
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] size The field of view size, in user units, of the galvo head.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_IfovSetSize(Automation1Controller controller, int32_t executionTaskIndex, double size);

/// @brief Configures more axes to command in Infinite Field of View (IFOV).
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axes A list of axes to synchronize in Infinite Field of View in addition to those specified in IfovSetAxisPairs().
/// @param[In] axesLength The number of elements in the axes function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_IfovSetSyncAxes(Automation1Controller controller, int32_t executionTaskIndex, int32_t* axes, int32_t axesLength);

/// @brief Configures the maximum search time that the controller looks ahead in Infinite Field of View (IFOV).
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] time The time, in milliseconds, that the controller looks ahead.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_IfovSetTime(Automation1Controller controller, int32_t executionTaskIndex, int64_t time);

/// @brief Configures the maximum acceleration of the servo axes while in Infinite Field of View (IFOV).
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] acceleration The maximum acceleration, in user units/second squared, of the servo axes.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_IfovSetTrackingAcceleration(Automation1Controller controller, int32_t executionTaskIndex, double acceleration);

/// @brief Configures the maximum speed of the servo axes while in Infinite Field of View (IFOV).
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] speed The maximum speed, in user units/time base, of the servo axes.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_IfovSetTrackingSpeed(Automation1Controller controller, int32_t executionTaskIndex, double speed);

/// @brief Resets all PSO configuration, which restores all PSO settings to their default values.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to reset the PSO configuration.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoReset(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Configures an array of PSO bit data words, where each word is a 32-bit integer.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the bit data.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first word of bit data is stored.
/// @param[In] numberOfPoints The number of bit data words to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use bit data words after the last word in the array is used, starting over at the first word.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoBitmapConfigureArray(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t enableRepeat);

/// @brief Configures the distance counter tracking directions that will cause PSO distance events.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the distance event directions.
/// @param[In] eventDirection The distance event directions to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoDistanceConfigureAllowedEventDirection(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1PsoDistanceAllowedEventDirection eventDirection);

/// @brief Configures an array of distances in counts that the PSO counter or counters must travel for an event to occur.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the distances.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first distance is stored.
/// @param[In] numberOfDistances The number of distances to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use distances after the last distance in the array is used, starting over at the first distance.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoDistanceConfigureArrayDistances(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfDistances, int64_t enableRepeat);

/// @brief Configures the conditions which will reset the PSO distance counters.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the distance counter reset conditions.
/// @param[In] optionsMask A bitmask of multiple PSO distance counter reset options.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoDistanceConfigureCounterReset(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t optionsMask);

/// @brief Configures the distance in counts that the PSO counter or counters must travel for an event to occur.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the distance.
/// @param[In] distance The distance in counts.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoDistanceConfigureFixedDistance(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t distance);

/// @brief Selects the source of each PSO distance counter.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the distance counter sources.
/// @param[In] inputs An array of one to three input sources, one for each distance counter.
/// @param[In] inputsLength The number of elements in the inputs function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoDistanceConfigureInputs(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1PsoDistanceInput* inputs, int32_t inputsLength);

/// @brief Configures the PSO distance counters to apply an integer scale factor for each tracking input.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the scale factors.
/// @param[In] scaleFactors An array of one to three integer scale factors, one per tracking input.
/// @param[In] scaleFactorsLength The number of elements in the scaleFactors function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoDistanceConfigureScaling(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t* scaleFactors, int32_t scaleFactorsLength);

/// @brief Disables the PSO distance counters, causing them to retain their values and ignore their configured inputs.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to disable the PSO distance counters.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoDistanceCounterOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Enables the PSO distance counters, allowing them to track their configured inputs.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to enable the PSO distance counters.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoDistanceCounterOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Disables PSO distance events.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to disable distance events.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoDistanceEventsOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Enables PSO distance events.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to enable distance events.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoDistanceEventsOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Configures additional conditions to prevent PSO events from occurring.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the event mask conditions.
/// @param[In] eventMask A bitmask of event mask conditions.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoEventConfigureMask(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t eventMask);

/// @brief Immediately halts active continuous PSO events.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to halt the events.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoEventContinuousOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Immediately causes continuous PSO events to occur.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to cause the events.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoEventContinuousOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Immediately causes a single PSO event to occur.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to cause the event.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoEventGenerateSingle(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Disables PSO laser events.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to disable PSO laser events.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoLaserEventsOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Configures the PSO to generate an event when the laser command bit turns on.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to generate laser PSO events.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoLaserEventsOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Selects the output pin on which to drive the PSO output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to select the PSO output pin.
/// @param[In] output The selected output pin.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoOutputConfigureOutput(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1PsoOutputPin output);

/// @brief Selects which internal PSO signal to drive onto the output pin.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to select the PSO output source.
/// @param[In] outputSource The selected output source.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoOutputConfigureSource(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1PsoOutputSource outputSource);

/// @brief Immediately deactivates the PSO output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to deactivate the PSO output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoOutputOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Immediately activates the PSO output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to activate the PSO output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoOutputOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Configures an array of on times for a sequence of waveform module outputs in pulse mode. The on time specifies the active portion of the pulse period.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the on times.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first on time is stored.
/// @param[In] numberOfPoints The number of on times to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use on times after the last on time in the array is used, starting over at the first on time.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigurePulseArrayOnTimes(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t enableRepeat);

/// @brief Configures an array of pulse counts for a sequence of waveform module outputs in pulse mode. The pulse count specifies the number of periods that will be generated from a single PSO event.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the pulse counts.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first pulse count is stored.
/// @param[In] numberOfPoints The number of pulse counts to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use pulse counts after the last pulse count in the array is used, starting over at the first pulse count.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigurePulseArrayCounts(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t enableRepeat);

/// @brief Configures an array of total times for a sequence of waveform module outputs in pulse mode. The total time specifies the full period of the pulse.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the total times.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first total time is stored.
/// @param[In] numberOfPoints The number of total times to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use total times after the last total time in the array is used, starting over at the first total time.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigurePulseArrayTotalTimes(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t enableRepeat);

/// @brief Configures the waveform module to wait for the specified time after a PSO event before beginning to output a waveform.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the waveform output delay.
/// @param[In] delayTime The delay time in microseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigureDelay(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double delayTime);

/// @brief Configures the fixed on time of the waveform module output in pulse mode, which will be applied to all pulses. The on time specifies the active portion of the pulse period.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the on time.
/// @param[In] onTime The on time in microseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigurePulseFixedOnTime(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double onTime);

/// @brief Configures the fixed pulse count of the waveform module output in pulse mode, which will be applied to all pulses. The pulse count specifies the number of periods that will be generated from a single PSO event.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the number of pulses.
/// @param[In] pulseCount The integer number of pulses.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigurePulseFixedCount(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t pulseCount);

/// @brief Configures the fixed total time of the waveform module output in pulse mode, which will be applied to all pulses. The total time specifies the full period of the pulse.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the total time.
/// @param[In] totalTime The total time in microseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigurePulseFixedTotalTime(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double totalTime);

/// @brief Configures additional conditions to disable the PSO waveform output in pulse mode.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure PSO waveform pulse mode masking options.
/// @param[In] pulseMask A bitmask of PSO waveform pulse mode masking options.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigurePulseMask(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t pulseMask);

/// @brief Disables the external sync option for the waveform module.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to disable external sync option.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformExternalSyncOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Configures the waveform module to wait for the rising edge of the external sync signal before beginning to output a waveform.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to enable external sync option.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformExternalSyncOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Disables the waveform module, preventing PSO events from triggering it.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to disable the waveform module.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Enables the waveform module, allowing PSO events to trigger it.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to enable the waveform module.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Configures an array of window range pairs each consisting of a lower bound followed by an upper bound.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the window ranges.
/// @param[In] windowNumber The number of the window on which to configure the ranges.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the lower bound of the first range pair is stored.
/// @param[In] numberOfRanges The number of range value pairs to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use range pairs after the last range pair in the array is used, starting over at the first range pair.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWindowConfigureArrayRanges(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t windowNumber, int64_t driveArrayStartAddress, int64_t numberOfRanges, int64_t enableRepeat);

/// @brief Configures the conditions which will reset the PSO window counters.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the window counter reset conditions.
/// @param[In] optionsMask A bitmask of multiple PSO window counter reset options.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWindowConfigureCounterReset(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t optionsMask);

/// @brief Configures the conditions which will generate PSO window events.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the window event conditions.
/// @param[In] eventMode The specified window event mode.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWindowConfigureEvents(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1PsoWindowEventMode eventMode);

/// @brief Configures a fixed window range consisting of a lower bound and an upper bound for the specified window.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the window range.
/// @param[In] windowNumber The number of the window on which to configure the range.
/// @param[In] lowerBound The value for the window range lower bound.
/// @param[In] upperBound The value for the window range upper bound.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWindowConfigureFixedRange(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t windowNumber, int64_t lowerBound, int64_t upperBound);

/// @brief Selects the source of the specified window counter.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to select the window counter input source.
/// @param[In] windowNumber The window number for which to select the counter input source.
/// @param[In] input The window counter input source.
/// @param[In] reverseDirection Configures the window counter to count in the opposite direction of its input source.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWindowConfigureInput(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t windowNumber, Automation1PsoWindowInput input, int64_t reverseDirection);

/// @brief Disables the specified window output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to disable the window output.
/// @param[In] windowNumber The number of the window on which to disable the output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWindowOutputOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t windowNumber);

/// @brief Enables the specified window output.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to enable the window output.
/// @param[In] windowNumber The number of the window on which to enable the output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWindowOutputOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t windowNumber);

/// @brief Sets the specified window counter to the specified value.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the window counter.
/// @param[In] windowNumber The number of the window on which to set the counter.
/// @param[In] value The new counter value.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWindowCounterSetValue(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t windowNumber, int64_t value);

/// @brief Configures the array of window range pairs to update when exiting the active window range in specific directions.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the window array update direction.
/// @param[In] windowNumber The number of the window on which to configure the array update direction.
/// @param[In] windowUpdateDirection Mode selection to select the active window range exit directions on which to update the window range.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWindowConfigureArrayUpdateDirection(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t windowNumber, Automation1PsoWindowUpdateDirection windowUpdateDirection);

/// @brief Checks for a valid configuration of pulse mode parameters and applies the configuration to the waveform module.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to apply the pulse configuration.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformApplyPulseConfiguration(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Configures the fixed total time of the waveform module output in PWM mode. The total time specifies the full period of the PWM signal.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the total time.
/// @param[In] totalTime The total time in microseconds.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigurePwmTotalTime(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double totalTime);

/// @brief Configures an array of on times for a sequence of waveform module outputs in PWM mode. The on time specifies the variable active portion of the PWM signal.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the on times.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first on time is stored.
/// @param[In] numberOfPoints The number of on times to be read from the drive array.
/// @param[In] enableRepeat Configures PSO to continue to use on times after the last on time in the array is used, starting over at the first on time.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigurePwmOnTimes(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints, int64_t enableRepeat);

/// @brief Checks for a valid configuration of PWM mode parameters and applies the configuration to the waveform module.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to apply the PWM configuration.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformApplyPwmConfiguration(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Selects the output mode of the waveform module.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to select the output mode of the waveform module.
/// @param[In] waveformMode Mode selection for the waveform module output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigureMode(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1PsoWaveformMode waveformMode);

/// @brief Allows or prevents the waveform module from outputting truncated waveform outputs in pulse mode.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the pulse truncation prevention feature.
/// @param[In] preventTruncation Configures the waveform module to not allow the generation of truncated waveform outputs in pulse mode.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_PsoWaveformConfigurePulseTruncation(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t preventTruncation);

/// @brief Sets the specified feedforward gain values on the specified axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the gain values.
/// @param[In] feedforwardGains An array of feedforward gains to set.
/// @param[In] feedforwardGainsLength The number of elements in the feedforwardGains function argument.
/// @param[In] feedforwardGainValues An array of feedforward gain values to set.
/// @param[In] feedforwardGainValuesLength The number of elements in the feedforwardGainValues function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_TuningSetFeedforwardGains(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1FeedforwardGain* feedforwardGains, int32_t feedforwardGainsLength, double* feedforwardGainValues, int32_t feedforwardGainValuesLength);

/// @brief Generates an open-loop current command at a fixed electrical angle.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to command current.
/// @param[In] current The current to output, specified in amperes.
/// @param[In] angle The electrical angle, specified in degrees. 360 degrees is one electrical commutation cycle of the motor.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_TuningSetMotorAngle(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double current, double angle);

/// @brief Generates an open-loop current command at a rotating electrical angle.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to command current.
/// @param[In] current The current to output, specified in amperes.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_TuningSetMotorCurrent(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double current);

/// @brief Sets the specified servo loop gain values on the specified axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the gain values.
/// @param[In] servoGains An array of servo loop gains to set.
/// @param[In] servoGainsLength The number of elements in the servoGains function argument.
/// @param[In] servoGainValues An array of servo loop gain values to set.
/// @param[In] servoGainValuesLength The number of elements in the servoGainValues function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_TuningSetServoLoopGains(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1ServoLoopGain* servoGains, int32_t servoGainsLength, double* servoGainValues, int32_t servoGainValuesLength);

/// @brief Disable a C transformation. This will stop running inverse and forward computations for this transformation.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] transformationName The name specified in the C Transformation configuration.
/// 	This string argument must be null terminated.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CTransformationDisable(Automation1Controller controller, int32_t executionTaskIndex, const char* transformationName);

/// @brief Enable a C transformation. This will begin running inverse and forward computations for the specified transformation. All axes part of the transformation must be enabled at any time the transformation is enabled. If the transformation is enabled while there is synchronous motion on the same task, then the motion program will wait for motion to complete before enabling the transformation.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] transformationName The name specified in the C Transformation configuration.
/// 	This string argument must be null terminated.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CTransformationEnable(Automation1Controller controller, int32_t executionTaskIndex, const char* transformationName);

/// @brief Call the OnGetProperty() C function defined in a C transformation.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] transformationName The name specified in the C Transformation configuration.
/// 	This string argument must be null terminated.
/// @param[In] property The property argument provided to the OnGetProperty() C function.
/// 	This string argument must be null terminated.
/// @param[Out] returnOut The return value of the AeroScript command (represents an AeroScript real value).
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CTransformationGetProperty(Automation1Controller controller, int32_t executionTaskIndex, const char* transformationName, const char* property, double* returnOut);

/// @brief Call the OnSetProperty() C function defined in a C transformation.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] transformationName The name specified in the C Transformation configuration.
/// 	This string argument must be null terminated.
/// @param[In] property The property argument provided to the OnSetProperty() C function.
/// 	This string argument must be null terminated.
/// @param[In] value The value argument provided to the OnSetProperty() C function.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_CTransformationSetProperty(Automation1Controller controller, int32_t executionTaskIndex, const char* transformationName, const char* property, double value);

/// @brief Gets the specified drive item from the specified axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis from which to retrieve the drive item value.
/// @param[In] driveItem The drive item to retrieve.
/// @param[In] additionalData Additional data for the specified drive item. This argument is required by some drive items.
/// @param[Out] returnOut The return value of the AeroScript command (represents an AeroScript real value).
/// 	Only use this if the function call was successful.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveGetItem(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1DriveItem driveItem, int64_t additionalData, double* returnOut);

/// @brief Enables drive data capture of configured inputs.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to enable drive data capture.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveDataCaptureOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Disables drive data capture of configured inputs.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to disables drive data capture.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveDataCaptureOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Configures the drive array for drive data capture.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to configure the drive array for drive data capture.
/// @param[In] driveArrayStartAddress The byte-addressable index of the drive array where the first drive data capture value will be written.
/// @param[In] numberOfPoints The number of points that will be written to the drive array by drive data capture.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveDataCaptureConfigureArray(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, int64_t driveArrayStartAddress, int64_t numberOfPoints);

/// @brief Selects the signal that will be stored by drive data capture.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to select the drive data capture signal.
/// @param[In] input The input signal for drive data capture.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveDataCaptureConfigureInput(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1DriveDataCaptureInput input);

/// @brief Selects the event that will trigger drive data capture.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to select the drive data capture trigger.
/// @param[In] trigger The trigger event for drive data capture.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveDataCaptureConfigureTrigger(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1DriveDataCaptureTrigger trigger);

/// @brief Engages the brake output and prevents the axis from moving freely.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to engage the brake.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveBrakeOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Disengages the brake output and allows the axis to move freely.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to disengage the brake.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveBrakeOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis);

/// @brief Configures pulse streaming mode.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] outputAxis The output axis on which to configure pulse streaming mode.
/// @param[In] inputAxes An array of one or more axes which will be tracked.
/// @param[In] inputAxesLength The number of elements in the inputAxes function argument.
/// @param[In] inputScaleFactors An array of scale factors to apply to each axis in the $inputAxes array.
/// @param[In] inputScaleFactorsLength The number of elements in the inputScaleFactors function argument.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DrivePulseStreamConfigure(Automation1Controller controller, int32_t executionTaskIndex, int32_t outputAxis, int32_t* inputAxes, int32_t inputAxesLength, double* inputScaleFactors, int32_t inputScaleFactorsLength);

/// @brief Enables pulse streaming mode on an axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] outputAxis The axis on which to enable pulse streaming mode.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DrivePulseStreamOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t outputAxis);

/// @brief Disables pulse streaming mode on an axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] outputAxis The axis on which to disable pulse streaming mode.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DrivePulseStreamOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t outputAxis);

/// @brief Writes the contents of an AeroScript array variable to the drive array.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to write the drive array.
/// @param[In] values The AeroScript array variable from which to write data to the drive array.
/// @param[In] valuesLength The number of elements in the values function argument.
/// @param[In] startAddress Byte-addressable index of the drive array from which to begin writing data.
/// @param[In] numElements The number of drive array elements to write.
/// @param[In] driveArrayType The underlying data type to write to the drive array.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveArrayWrite(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double* values, int32_t valuesLength, int64_t startAddress, int64_t numElements, Automation1DriveArrayType driveArrayType);

/// @brief Sets the position command of the axis at the servo loop level and adjusts the position feedback for position error.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the position command.
/// @param[In] positionCommand The position command to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveSetPositionCommand(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double positionCommand);

/// @brief Sets the position command and the position feedback of the axis at the servo loop level.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the position command.
/// @param[In] positionFeedback The position feedback to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveSetPositionFeedback(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double positionFeedback);

/// @brief Sets the auxiliary feedback of the axis.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to set the auxiliary feedback.
/// @param[In] auxiliaryFeedback The feedback value to set.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveSetAuxiliaryFeedback(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, double auxiliaryFeedback);

/// @brief Disables encoder output on the specified output channel.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to disable encoder output.
/// @param[In] outputChannel The outgoing encoder channel.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveEncoderOutputOff(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1EncoderOutputChannel outputChannel);

/// @brief Enables encoder output on the specified output channel, with the corresponding mode.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to enable encoder output.
/// @param[In] outputChannel The outgoing encoder channel.
/// @param[In] outputMode The mode of encoder output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveEncoderOutputOn(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1EncoderOutputChannel outputChannel, Automation1EncoderOutputMode outputMode);

/// @brief Configures an output channel to echo encoder signals from the specified input channel.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to apply the configuration.
/// @param[In] outputChannel The outgoing encoder channel.
/// @param[In] inputChannel The incoming encoder channel.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveEncoderOutputConfigureInput(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1EncoderOutputChannel outputChannel, Automation1EncoderInputChannel inputChannel);

/// @brief Applies a divider on the specified output channel, lowering the frequency of output signals.
/// @param[In] controller The Automation1 controller to perform this AeroScript command on.
/// @param[In] executionTaskIndex The index of the task to execute the AeroScript command on.
/// @param[In] axis The axis on which to apply the configuration.
/// @param[In] outputChannel The outgoing encoder channel.
/// @param[In] outputDivider The divider to apply to encoder output.
/// @return Returns true if the AeroScript command executed successfully on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Command_DriveEncoderOutputConfigureDivider(Automation1Controller controller, int32_t executionTaskIndex, int32_t axis, Automation1EncoderOutputChannel outputChannel, int64_t outputDivider);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1COMMAND_H_INCLUDED