///
/// Copyright (c) Aerotech, Inc.
///

#ifndef AUTOMATION1PARAMETER_H_INCLUDED
#define AUTOMATION1PARAMETER_H_INCLUDED

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
#include "Automation1ParameterId.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Gets the string value of an active system parameter in use by the Automation1 controller.
/// @param[In] controller The controller to get the system parameter from.
/// @param[In] parameterId The system parameter to get from the controller.
/// @param[Out] valueOut The null-terminated string value of the specified system parameter.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] valueMaxLength The maximum number of elements to copy to the valueOut function argument.
/// 	This must not be greater than the length of the valueOut array.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_GetSystemStringValue(Automation1Controller controller, Automation1SystemParameterId parameterId, char* valueOut, int32_t valueMaxLength);

/// @brief Gets the numeric value of an active system parameter in use by the Automation1 controller.
/// @param[In] controller The controller to get the system parameter from.
/// @param[In] parameterId The system parameter to get from the controller.
/// @param[Out] valueOut The numeric value of the specified system parameter. Only use this if the function call was successful.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_GetSystemValue(Automation1Controller controller, Automation1SystemParameterId parameterId, double* valueOut);

/// @brief Sets the string value of the active system parameter in use by the Automation1 controller.
/// 	Changes to active parameters are not persisted and the active controller parameter values are lost after a controller reset.
/// @param[In] controller The controller to set the system parameter on.
/// @param[In] parameterId The system parameter to set on controller.
/// @param[In] value The null-terminated string value to set the system parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_SetSystemStringValue(Automation1Controller controller, Automation1SystemParameterId parameterId, const char* value);

/// @brief Sets the numeric value of the active system parameter in use by the Automation1 controller.
/// 	Changes to active parameters are not persisted and the active controller parameter values are lost after a controller reset.
/// @param[In] controller The controller to set the system parameter on.
/// @param[In] parameterId The system parameter to set on the controller.
/// @param[In] value The numeric value to set the system parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_SetSystemValue(Automation1Controller controller, Automation1SystemParameterId parameterId, double value);

/// @brief Gets the string value of an active axis parameter on the specified axis in use by the Automation1 controller.
/// @param[In] controller The controller to get the axis parameter from.
/// @param[In] axisIndex The axis to get the axis parameter from.
/// @param[In] parameterId The axis parameter to get from the specified axis.
/// @param[Out] valueOut The null-terminated string value of the specified axis parameter.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] valueMaxLength The maximum number of elements to copy to the valueOut function argument.
/// 	This must not be greater than the length of the valueOut array.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_GetAxisStringValue(Automation1Controller controller, int32_t axisIndex, Automation1AxisParameterId parameterId, char* valueOut, int32_t valueMaxLength);

/// @brief Gets the numeric value of an active axis parameter on the specified axis in use by the Automation1 controller.
/// @param[In] controller The controller to get the axis parameter from.
/// @param[In] axisIndex The axis to get the axis parameter from.
/// @param[In] parameterId The axis parameter to get from the specified axis.
/// @param[Out] valueOut The numeric value of the specified axis parameter. Only use this if the function call was successful.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_GetAxisValue(Automation1Controller controller, int32_t axisIndex, Automation1AxisParameterId parameterId, double* valueOut);

/// @brief Sets the string value of an active axis parameter on the specified axis in use by the Automation1 controller.
/// 	Changes to active parameters are not persisted and the active controller parameter values are lost after a controller reset.
/// @param[In] controller The controller to set the axis parameter on.
/// @param[In] axisIndex The axis to set the axis parameter on.
/// @param[In] parameterId The axis parameter to set on the specified axis.
/// @param[In] value The null-terminated string value to set the specified axis parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_SetAxisStringValue(Automation1Controller controller, int32_t axisIndex, Automation1AxisParameterId parameterId, const char* value);

/// @brief Sets the numeric value of an active axis parameter on the specified axis in use by the Automation1 controller.
/// 	Changes to active parameters are not persisted and the active controller parameter values are lost after a controller reset.
/// @param[In] controller The controller to set the axis parameter on.
/// @param[In] axisIndex The axis to get the axis parameter from.
/// @param[In] parameterId The axis parameter to set on the specified axis.
/// @param[In] value The numeric value to set the specified axis parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_SetAxisValue(Automation1Controller controller, int32_t axisIndex, Automation1AxisParameterId parameterId, double value);

/// @brief Gets the string value of an active task parameter on the specified task in use by the Automation1 controller.
/// @param[In] controller The controller to get the task parameter from.
/// @param[In] taskIndex The task to get the task parameter from.
/// @param[In] parameterId The task parameter to get from the specified task.
/// @param[Out] valueOut The null-terminated string value of the specified task parameter.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] valueMaxLength The maximum number of elements to copy to the valueOut function argument.
/// 	This must not be greater than the length of the valueOut array.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_GetTaskStringValue(Automation1Controller controller, int32_t taskIndex, Automation1TaskParameterId parameterId, char* valueOut, int32_t valueMaxLength);

/// @brief Gets the numeric value of an active task parameter on the specified task in use by the Automation1 controller.
/// @param[In] controller The controller to get the task parameter from.
/// @param[In] taskIndex The task to get the task parameter from.
/// @param[In] parameterId The task parameter to get from the specified task.
/// @param[Out] valueOut The numeric value of the specified task parameter. Only use this if the function call was successful.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_GetTaskValue(Automation1Controller controller, int32_t taskIndex, Automation1TaskParameterId parameterId, double* valueOut);

/// @brief Sets the string value of an active task parameter on the specified task in use by the Automation1 controller.
/// 	Changes to active parameters are not persisted and the active controller parameter values are lost after a controller reset.
/// @param[In] controller The controller to set the task parameter on.
/// @param[In] taskIndex The task to set the task parameter on.
/// @param[In] parameterId The task parameter to set on the specified task.
/// @param[In] value The null-terminated string value to set the task parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_SetTaskStringValue(Automation1Controller controller, int32_t taskIndex, Automation1TaskParameterId parameterId, const char* value);

/// @brief Sets the numeric value of an active task parameter on the specified task in use by the Automation1 controller.
/// 	Changes to active parameters are not persisted and the active controller parameter values are lost after a controller reset.
/// @param[In] controller The controller to set the task parameter on.
/// @param[In] taskIndex The task to set the task parameter on.
/// @param[In] parameterId The task parameter to set on the specified task.
/// @param[In] value The numeric value to set the task parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Parameter_SetTaskValue(Automation1Controller controller, int32_t taskIndex, Automation1TaskParameterId parameterId, double value);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1PARAMETER_H_INCLUDED