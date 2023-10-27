///
/// Copyright (c) Aerotech, Inc.
///

#ifndef AUTOMATION1DATACOLLECTION_H_INCLUDED
#define AUTOMATION1DATACOLLECTION_H_INCLUDED

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
#include "Automation1DataSignal.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Represents predefined data collection frequencies which correlate to 1 millisecond or sub-millisecond data collect periods.
/// 	Data collection frequency defines how many points will be collection in one second.
typedef enum Automation1DataCollectionFrequency
{
	/// @brief A data collection frequency was not specified or a data collection period was specified that does not
	/// 	correlate to one of predefined data collection frequencies.
	Automation1DataCollectionFrequency_Undefined = 0,
	/// @brief Represents a data collection frequency of 1 kilohertz or a data collection period of 1 millisecond.
	/// 	1000 points will be collected in one second.
	Automation1DataCollectionFrequency_1kHz,
	/// @brief Represents a data collection frequency of 10 kilohertz or a data collection period of 0.1 milliseconds.
	/// 	10,000 points will be collected in one second.
	Automation1DataCollectionFrequency_10kHz,
	/// @brief Represents a data collection frequency of 20 kilohertz or a data collection period of 0.05 milliseconds.
	/// 	20,000 points will be collected in one second.
	Automation1DataCollectionFrequency_20kHz,
	/// @brief Represents a data collection frequency of 100 kilohertz or a data collection period of 0.01 milliseconds.
	/// 	100,000 points will be collected in one second.
	Automation1DataCollectionFrequency_100kHz,
	/// @brief Represents a data collection frequency of 200 kilohertz or a data collection period of 0.005 milliseconds.
	/// 	200,000 points will be collected in one second.
	Automation1DataCollectionFrequency_200kHz,
} Automation1DataCollectionFrequency;

/// @brief Represents the mode that data collection will use when collecting data from an Automation1 controller.
typedef enum Automation1DataCollectionMode
{
	/// @brief Data collection will start, collect a specified number of data points at a specified period, then stop.
	/// 	Data collection can be stopped prematurely by calling Automation1_DataCollection_Stop().
	Automation1DataCollectionMode_Snapshot,
	/// @brief Data collection will start and collect data points forever at a specified period.
	/// 	Continuous data collection can be stopped by calling Automation1_DataCollection_Stop().
	Automation1DataCollectionMode_Continuous,
} Automation1DataCollectionMode;

/// @brief Represents the status of any data collection on an Automation1 controller (both Automation1DataCollectionMode_Snapshot and Automation1DataCollectionMode_Continuous).
typedef struct Automation1DataCollectionStatus
{
	/// @brief Gets the number of points that data collection will collect. In Automation1DataCollectionMode_Snapshot this number is the total number of points to collect.
	/// 	In Automation1DataCollectionMode_Continuous this number is the size of each chunk of continuously collected points.
	int32_t NumberOfPointsToCollect;
	/// @brief Gets the number of points that data collection has collected for all configured data signals.
	int32_t NumberOfCollectedPoints;
	/// @brief Gets the number of points that data collection has collected and retrieved. At certain data collection periods NumberOfRetrievedPoints can be lower than NumberOfCollectedPoints
	/// 	because the points haven't been retrieved from the HyperWire devices yet.
	int32_t NumberOfRetrievedPoints;
	/// @brief Gets whether or not data collection is currently collecting points.
	bool IsCollecting;
	/// @brief Gets whether or not the internal data collection buffer has overflowed and stopped with an error. This can happen in Automation1DataCollectionMode_Continuous
	/// 	if points are not retrieved fast enough and a single chunk of data exceeds NumberOfPointsToCollect.
	bool HasOverflowed;
	/// @brief Gets the current mode of data collection.
	Automation1DataCollectionMode Mode;
} Automation1DataCollectionStatus;

/// @brief A handle representing a configuration of data signals to collect from an Automation1 controller
/// 	To obtain a handle of this type, see Automation1_DataCollectionConfig_Create().
/// 	To add axis, task, or system data signals call the Automation1_DataCollectionConfig_AddAxisDataSignal(),
/// 	Automation1_DataCollectionConfig_AddTaskDataSignal(), and Automation1_DataCollectionConfig_AddSystemDataSignal() functions.
/// 	Make sure to destroy the configuration to avoid leaking memory using the Automation1_DataCollectionConfig_Destroy() function.
typedef struct Automation1DataCollectionConfig_T* Automation1DataCollectionConfig;

/// @brief Creates a new data collection configuration handle.
/// 	Make sure to call Automation1_DataCollectionConfig_Destroy() to avoid leaking memory when you are done with the configuration.
/// @param[In] frequency The frequency of data collection (the number of points to collect in one second).
/// @param[In] numberOfPointsToCollect The number of points to collect for each configured data signal.
/// @param[Out] configOut The created data collection configuration handle. Only use this if the function call was successful.
/// @return Returns true if the configuration was successfully created otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollectionConfig_Create(Automation1DataCollectionFrequency frequency, int32_t numberOfPointsToCollect, Automation1DataCollectionConfig* configOut);

/// @brief Creates a new data collection configuration handle.
/// 	Make sure to call Automation1_DataCollectionConfig_Destroy() to avoid leaking memory when you are done with the configuration.
/// @param[In] period The time in milliseconds between each point being collected.
/// @param[In] numberOfPointsToCollect The number of points to collect for each configured data signal.
/// @param[Out] configOut The created data collection configuration handle. Only use this if the function call was successful.
/// @return Returns true if the configuration was successfully created otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollectionConfig_CreateWithPeriod(double period, int32_t numberOfPointsToCollect, Automation1DataCollectionConfig* configOut);

/// @brief Destroys the data collection configuration handle.
/// @param[In] config The data collection configuration to destroy.
/// @return Returns true if the configuration handle was destroyed otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollectionConfig_Destroy(Automation1DataCollectionConfig config);

/// @brief Adds an axis based data signal to be collected on a specific axis on the Automation1 controller.
/// @param[In] config The data collection configuration to add the axis based data signal to.
/// @param[In] axisIndex The axis to collect the data signal on.
/// @param[In] axisSignal The axis based data signal to collect.
/// @param[In] argument The argument for the data signal, if unsure set this to zero.
/// @return Returns true if the data signal was successfully added to the configuration otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollectionConfig_AddAxisDataSignal(Automation1DataCollectionConfig config, int32_t axisIndex, Automation1AxisDataSignal axisSignal, int32_t argument);

/// @brief Adds a task based data signal to be collected on a specific task on the Automation1 controller.
/// @param[In] config The data collection configuration to add the task based data signal to.
/// @param[In] taskIndex The task to collect the data signal on.
/// @param[In] taskSignal The task based data signal to collect.
/// @param[In] argument The argument for the data signal, if unsure set this to zero.
/// @return Returns true if the data signal was successfully added to the configuration otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollectionConfig_AddTaskDataSignal(Automation1DataCollectionConfig config, int32_t taskIndex, Automation1TaskDataSignal taskSignal, int32_t argument);

/// @brief Adds a system based data signal to be collected on the Automation1 controller.
/// @param[In] config The data collection configuration to add the system based data signal to.
/// @param[In] systemSignal The system based data signal to collect.
/// @param[In] argument The argument for the data signal, if unsure set this to zero.
/// @return Returns true if the data signal was successfully added to the configuration otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollectionConfig_AddSystemDataSignal(Automation1DataCollectionConfig config, Automation1SystemDataSignal systemSignal, int32_t argument);

/// @brief Removes all data signals from the data collection configuration so that they will not be collected from the Automation1 controller.
/// @param[In] config The data collection configuration to remove all data signals from.
/// @return Returns true if the data signals were successfully cleared otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollectionConfig_ClearAllDataSignals(Automation1DataCollectionConfig config);

/// @brief Gets the current status of any data collection (both Automation1DataCollectionMode_Snapshot and Automation1DataCollectionMode_Continuous).
/// @param[In] controller The Automation1 controller where data collection is running.
/// @param[Out] statusOut The current status of any data collection. Only use this if the function call was successful.
/// 	This argument must have memory preallocated before passing it into this function.
/// @return Returns true if the status of data collection was successful obtained otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollection_GetStatus(Automation1Controller controller, Automation1DataCollectionStatus* statusOut);

/// @brief Starts data collection on the Automation1 controller with the specified mode and using the specified data collection configuration.
/// 	This function waits for data collection to start but it does not wait for data collection to complete.
/// 	You can stop data collection by calling the Automation1_DataCollection_Stop() function and you can get the collected data by calling the
/// 	Automation1_DataCollection_GetResults() function.
/// @param[In] controller The Automation1 controller to start data collection on.
/// @param[In] config What data to collect and at what frequency.
/// @param[In] collectionMode The data collection mode to start.
/// @return Returns true if data collection was successfully started on the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollection_Start(Automation1Controller controller, Automation1DataCollectionConfig config, Automation1DataCollectionMode collectionMode);

/// @brief Stops all data collection on the Automation1 controller, regardless of who started it.
/// @param[In] controller The Automation1 controller to stop data collection on.
/// @return Returns true if data collection was successfully stopped otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollection_Stop(Automation1Controller controller);

/// @brief Gets results from data collection from the Automation1 controller. This function can return data from completed data collection or from data collection that is still
/// 	occurring. This function waits for data collection to collect the specified number of points, blocking until they are available, and then returns them.
///		The allResultsOut argument will be populated with all the points for the first data signal, then all the points for the second data signal, and so on.
/// 	To get the results for a specific data signal see the Automation1_DataCollection_GetAxisResults(), Automation1_DataCollection_GetTaskResults(),
/// 	and Automation1_DataCollection_GetSystemResults() functions.
/// @param[In] controller The Automation1 controller to collect results from.
/// @param[In] config The configuration that was used to start data collection.
/// @param[Out] allResultsOut The out array of data collection results that were collected from the controller.
///		This will be populated with all the points for the first data signal, then all the points for the second data signal, and so on.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] allResultsMaxLength The maximum number of elements to copy to the allResultsOut argument.
/// 	This length divided by the number of configured data signals determines how many points per data signal to get from the controller. If the array length
/// 	provided is smaller than the number of available points then an equal number of points for each data signal will populate the allResultsOut array.
/// 	For example, if there are 4 data signals and 100 points collected for each data signal but this length is set to 200 array elements, the allResultsOut
/// 	array will be populated with the first 50 points for data signal 1, the first 50 points for data signal 2, and so on.
/// 	This must be divisible by the number of signals and must not be greater than the length of the allResultsOut array.
/// @return Returns true if results from data collection were collected successfully otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollection_GetResults(Automation1Controller controller, Automation1DataCollectionConfig config, double* allResultsOut, int32_t allResultsMaxLength);

/// @brief Copies the results for a single axis-based data signal out of the already collected data collection results.
/// 	To collect data collection results from an Automation1 controller see Automation1_DataCollection_GetResults().
/// @param[In] config The configuration that was used to start data collection.
/// @param[In] allResults The array of already collected data collection results.
/// @param[In] allResultsLength The number of elements in the allResults argument.
/// @param[In] axisIndex The axis the data signal was collected on.
/// @param[In] axisSignal The axis-based data signal to copy the results of.
/// @param[In] argument The argument for the data signal.
/// @param[Out] axisResultsOut The out array of axis results that were collected for the data signal on the specified axis (these are copied from the allResults array).
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] axisResultsMaxLength The maximum number of elements to copy to the axisResultsOut argument. This must not be greater than the length of the axisResultsOut array.
/// @return Returns true if the axis results were successfully copied from the allResults argument otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollection_GetAxisResults(Automation1DataCollectionConfig config, double* allResults, int32_t allResultsLength, int32_t axisIndex, Automation1AxisDataSignal axisSignal, int32_t argument, double* axisResultsOut, int32_t axisResultsMaxLength);

/// @brief Copies the results for a single task-based data signal out of the already collected data collection results.
/// 	To collect data collection results see Automation1_DataCollection_GetResults().
/// @param[In] config The configuration that was used to start data collection.
/// @param[In] allResults The array of already collected data collection results.
/// @param[In] allResultsLength The number of elements in the allResults argument.
/// @param[In] taskIndex The task the data signal was collected on.
/// @param[In] taskSignal The task-based data signal to copy the results of.
/// @param[In] argument The argument for the data signal.
/// @param[Out] taskResultsOut The out array of task results that were collected for the data signal on the specified task (these are copied from the allResults array).
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] taskResultsMaxLength The maximum number of elements to copy to the taskResultsOut argument. This must not be greater than the length of the taskResultsOut array.
/// @return Returns true if the task results were successfully copied from the allResults argument otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollection_GetTaskResults(Automation1DataCollectionConfig config, double* allResults, int32_t allResultsLength, int32_t taskIndex, Automation1TaskDataSignal taskSignal, int32_t argument, double* taskResultsOut, int32_t taskResultsMaxLength);

/// @brief Copies the results for a single system-based data signal out of the already collected data collection results.
/// 	To collect data collection results see Automation1_DataCollection_GetResults().
/// @param[In] config The configuration that was used to start data collection.
/// @param[In] allResults The array of already collected data collection results.
/// @param[In] allResultsLength The number of elements in the allResults argument.
/// @param[In] systemSignal The system-based data signal to copy the results of.
/// @param[In] argument The argument for the data signal.
/// @param[Out] systemResultsOut The out array of system results that were collected for the data signal (these are copied from the allResults array).
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] systemResultsMaxLength The maximum number of elements to copy to the systemResultsOut argument. This must not be greater than the length of the systemResultsOut array.
/// @return Returns true if the system results were successfully copied from the allResults argument otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_DataCollection_GetSystemResults(Automation1DataCollectionConfig config, double* allResults, int32_t allResultsLength, Automation1SystemDataSignal systemSignal, int32_t argument, double* systemResultsOut, int32_t systemResultsMaxLength);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1DATACOLLECTION_H_INCLUDED