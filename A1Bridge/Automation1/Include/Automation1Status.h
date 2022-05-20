#ifndef AUTOMATION1STATUS_H_INCLUDED
#define AUTOMATION1STATUS_H_INCLUDED

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
#include "Automation1StatusItem.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Represents a configuration of status items to retrieve from an Automation1 controller using the Automation1_Status_GetResults() function.
/// 	To obtain a handle of this type, see Automation1_StatusConfig_Create().
/// 	To add axis, task, or system status items call the Automation1_StatusConfig_AddAxisStatusItem(),
/// 	Automation1_StatusConfig_AddTaskStatusItem(), and Automation1_StatusConfig_AddSystemStatusItem() functions.
/// 	Make sure to destroy the configuration to avoid leaking memory using the Automation1_StatusConfig_Destroy() function.
typedef struct Automation1StatusConfig_T* Automation1StatusConfig;

/// @brief Creates a new status configuration handle.
/// 	Make sure to call Automation1_StatusConfig_Destroy() to avoid leaking memory when you are done with the configuration.
/// @param[Out] configOut The created status configuration handle. Only use this if the function call was successful.
/// @return Returns true if the configuration was successfully created otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_StatusConfig_Create(Automation1StatusConfig* configOut);

/// @brief Destroys the status configuration handle.
/// @param[In] config The status configuration to destroy.
/// @return Returns true if the configuration handle was destroyed otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_StatusConfig_Destroy(Automation1StatusConfig config);

/// @brief Adds an axis based status item to be retrieved on a specific axis on the Automation1 controller.
/// @param[In] config The configuration to add the status item to.
/// @param[In] axisIndex The axis to retrieve the status item on.
/// @param[In] axisStatusItem The axis based status item to retrieve.
/// @param[In] argument The argument for the status item, if unsure set this to zero.
/// @return Returns true if the status item was successfully added to the configuration.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_StatusConfig_AddAxisStatusItem(Automation1StatusConfig config, int32_t axisIndex, Automation1AxisStatusItem axisStatusItem, int32_t argument);

/// @brief Adds a task based status item to be retrieved on a specific task on the Automation1 controller.
/// @param[In] config The configuration to add the status item to.
/// @param[In] taskIndex The task to retrieve the status item on.
/// @param[In] taskStatusItem The task based status item to retrieve.
/// @param[In] argument The argument for the status item, if unsure set this to zero.
/// @return Returns true if the status item was successfully added to the configuration.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_StatusConfig_AddTaskStatusItem(Automation1StatusConfig config, int32_t taskIndex, Automation1TaskStatusItem taskStatusItem, int32_t argument);

/// @brief Adds a system based status item to be retrieved on the Automation1 controller.
/// @param[In] config The configuration to add the status item to.
/// @param[In] systemStatusItem The system based status item to retrieve.
/// @param[In] argument The argument for the status item, if unsure set this to zero.
/// @return Returns true if the status item was successfully added to the configuration.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_StatusConfig_AddSystemStatusItem(Automation1StatusConfig config, Automation1SystemStatusItem systemStatusItem, int32_t argument);

/// @brief Removes all status items from the status configuration so that they will not be retrieved from the Automation1 controller.
/// @param[In] config The status configuration to remove all status items from.
/// @return Returns true if the status items were successfully cleared otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_StatusConfig_ClearAllStatusItems(Automation1StatusConfig config);

/// @brief Gets results for status from the Automation1 controller.
/// 	Retrieving status is not real-time and there is variable latency when calling this function.
/// @param[In] controller The Automation1 controller to retrieve status from.
/// @param[In] config What status items to retrieve from the controller.
/// @param[Out] allResultsOut The out array of status results that were retrieved from the controller.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] allResultsMaxLength The maximum number of elements to copy to the allResultsOut argument.
/// 	The length must be at least equal to the number of status items configured and must not be greater than the length of the allResultsOut array.
/// @return Returns true if results from status were retrieved successfully otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Status_GetResults(Automation1Controller controller, Automation1StatusConfig config, double* allResultsOut, int32_t allResultsMaxLength);

/// @brief Gets the value for a single axis-based status item out of the already retrieved status results.
/// 	To retrieve status from an Automation1 controller see Automation1_Status_GetResults().
/// @param[In] config The configuration that was used to retrieve status.
/// @param[In] allResults The array of already retrieved status results from the controller.
/// @param[In] allResultsLength The number of elements in the allResults argument.
/// @param[In] axisIndex The axis the status item was retrieved on.
/// @param[In] axisStatusItem The axis-based status item to get.
/// @param[In] argument The argument for the status item.
/// @param[Out] axisResultOut The result that was retrieved for the status item on the specified axis (this is copied from the allResults array).
/// 	Only use this if the function call was successful.
/// @return Returns true if the axis result was successfully obtained otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Status_GetAxisResult(Automation1StatusConfig config, double* allResults, int32_t allResultsLength, int32_t axisIndex, Automation1AxisStatusItem axisStatusItem, int32_t argument, double* axisResultOut);

/// @brief Gets the value for a single task-based status item out of the already retrieved status results.
/// 	To retrieve status from an Automation1 controller see Automation1_Status_GetResults().
/// @param[In] config The configuration that was used to retrieve status.
/// @param[In] allResults The array of already retrieved status results from the controller.
/// @param[In] allResultsLength The number of elements in the allResults argument.
/// @param[In] taskIndex The task the status item was retrieved on.
/// @param[In] taskStatusItem The task-based status item to get.
/// @param[In] argument The argument for the status item.
/// @param[Out] taskResultOut The result that was retrieved for the status item on the specified task (this is copied from the allResults array).
/// 	Only use this if the function call was successful.
/// @return Returns true if the task result was successfully obtained otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Status_GetTaskResult(Automation1StatusConfig config, double* allResults, int32_t allResultsLength, int32_t taskIndex, Automation1TaskStatusItem taskStatusItem, int32_t argument, double* taskResultOut);

/// @brief Gets the value for a single system based status item out of the already retrieved status results.
/// 	To retrieve status from an Automation1 controller see Automation1_Status_GetResults().
/// @param[In] config The configuration that was used to retrieve status.
/// @param[In] allResults The array of already retrieved status results from the controller.
/// @param[In] allResultsLength The number of elements in the allResults argument.
/// @param[In] systemStatusItem The system based status item to get.
/// @param[In] argument The argument for the status item.
/// @param[Out] systemResultOut The system result that was retrieved (this is copied from the allResults array).
/// 	Only use this if the function call was successful.
/// @return Returns true if the system result was successfully obtained otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Status_GetSystemResult(Automation1StatusConfig config, double* allResults, int32_t allResultsLength, Automation1SystemStatusItem systemStatusItem, int32_t argument, double* systemResultOut);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1STATUS_H_INCLUDED