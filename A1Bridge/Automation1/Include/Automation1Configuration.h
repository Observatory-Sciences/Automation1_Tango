///
/// Copyright (c) Aerotech, Inc.
///

#ifndef AUTOMATION1CONFIGURATION_H_INCLUDED
#define AUTOMATION1CONFIGURATION_H_INCLUDED

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

/// @brief Represents a collection of configured parameters that you can get from or set to an Automation1 controller.
///		Configured Parameters are different from active parameters in that they persist between controller resets.
/// 	To obtain a handle of this type, see Automation1_ConfiguredParameters_Create().
///		Use the Automation1_Configuration_GetConfiguredParameters() function to get configured parameters from your controller to this handle.
///		Use the Automation1_Configuration_SetConfiguredParameters() function to set the configured parameters on your controller using the values in this handle.
/// 	Use the Automation1_ConfiguredParameters_Get* and Automation1_ConfiguredParameters_Set* functions to get and set values this configured parameters handle.
/// 	Make sure to destroy the handle when you are done to avoid leaking memory using the Automation1_ConfiguredParameters_Destroy() function.
typedef struct Automation1ConfiguredParameters_T* Automation1ConfiguredParameters;

/// @brief Represents a calibration file that you can get from or set to an Automation1 controller.
///		To obtain a handle of this type, see Automation1_CalibrationFile_Create().
///		Make sure to destroy the handle when you are done to avoid leaking memory using the Automation1_CalibrationFile_Destroy() function.
typedef struct Automation1CalibrationFile_T* Automation1CalibrationFile;

/// @brief Represents a configuration of compiled AeroScript programs, compiled AeroScript libraries, and AeroScript source files that you can get from or set to an Automation1 controller.
///		Compiled AeroScript programs can be configured to automatically load or run on a task whenever the controller starts.
///		Compiled AeroScript libraries can be configured to automatically load and import in other AeroScript programs.
///		AeroScript source files can be configured to be automatically included in other AeroScript programs.
/// 	To obtain a handle of this type, see Automation1_ConfiguredProgramAutomation_Create().
///		Use the Automation1_Configuration_GetConfiguredProgramAutomation() function to get configured program automation from your controller to this handle.
///		Use the Automation1_Configuration_SetConfiguredProgramAutomation() function to set the configured program automation on your controller using the files configured in this handle.
/// 	Make sure to destroy the handle when you are done to avoid leaking memory using the Automation1_ConfiguredProgramAutomation_Destroy() function.
typedef struct Automation1ConfiguredProgramAutomation_T* Automation1ConfiguredProgramAutomation;

/// @brief Gets the configured parameters from an Automation1 controller
///		Configured parameters are different from active parameters in that they persist between controller resets.
///		If configured parameters have not been set, then trying to get them from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsConfiguredParametersSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the configured parameters from.
/// @param[In] configuredParameters The collection of configured parameters to store the controller's configured parameters in.
///		You must first create the handle using Automation1_ConfiguredParameters_Create() before passing it to this function.
///		This function will clear all other configured parameters that are set in this collection and replace them with the configured
///		parameters from the Automation1Controller. 
/// @return Returns true if the configured parameters from the Automation1 controller were retrieved successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetConfiguredParameters(Automation1Controller controller, Automation1ConfiguredParameters configuredParameters);

/// @brief Sets the configured parameters on an Automation1 controller
///		Configured parameters are different from active parameters in that they persist between controller resets.
///		After calling this function to set the configured parameters on your controller, you may have to reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the configured parameters on.
/// @param[In] configuredParameters The collection of configured parameters to set on the Automation1 controller.
/// @return Returns true if the configured parameters from the Automation1 controller were set successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetConfiguredParameters(Automation1Controller controller, Automation1ConfiguredParameters configuredParameters);

/// @brief Gets whether configured parameters on an Automation1 controller have been set.
///		If configured parameters have not been set, then trying to get them from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetConfiguredParameters().
///	@param[In] controller The Automation1 controller to check whether configured parameters have been set on.
/// @param[Out] isConfiguredParametersSetOut Whether configured parameters are set on the specified Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether the configuration was set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsConfiguredParametersSet(Automation1Controller controller, bool* isConfiguredParametersSetOut);

/// @brief Removes the configured parameters that are set on an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configuration from.
/// @return Returns true if the configured parameters were successfully removed from the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveConfiguredParameters(Automation1Controller controller);

/// @brief Gets the configured 1D calibration file from an Automation1 controller.
///		If a configured 1D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsCalibration1DFileSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the 1D calibration file from.
/// @param[In] calibrationFile The 1D calibration file retrieved from the Automation1 controller.
///		You must first create the handle using Automation1_CalibrationFile_Create() before passing it to this function.
///		This function will overwrite any content that already exists in the specified calibration file, replacing it with
///		the contents of the 1D calibration file retrieved from the Automation1 controller.
///		Only use this if the function call was successful.
/// @return Returns true if the 1D calibration file was successfully retrieved from the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetCalibration1DFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Gets the configured 2D calibration file from an Automation1 controller.
///		If a configured 2D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsCalibration2DFileSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the 2D calibration file from.
/// @param[In] calibrationFile The 2D calibration file retrieved from the Automation1 controller.
///		You must first create the handle using Automation1_CalibrationFile_Create() before passing it to this function.
///		This function will overwrite any content that already exists in the specified calibration file, replacing it with
///		the contents of the 2D calibration file retrieved from the Automation1 controller.
///		Only use this if the function call was successful.
/// @return Returns true if the 2D calibration file was successfully retrieved from the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetCalibration2DFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Gets the configured galvo 2D calibration file from an Automation1 controller.
///		If a configured galvo 2D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsGalvo2DCalibrationFileSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the galvo 2D calibration file from.
/// @param[In] calibrationFile The galvo 2D calibration file retrieved from the Automation1 controller.
///		You must first create the handle using Automation1_CalibrationFile_Create() before passing it to this function.
///		This function will overwrite any content that already exists in the specified calibration file, replacing it with
///		the contents of the galvo 2D calibration file retrieved from the Automation1 controller.
///		Only use this if the function call was successful.
/// @return Returns true if the galvo 2D calibration file was successfully retrieved from the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetGalvo2DCalibrationFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Gets the configured galvo power correction file from an Automation1 controller.
///		If a configured galvo power correction file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsGalvoPowerCorrectionFileSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the galvo power correction file from.
/// @param[In] calibrationFile The galvo power correction file retrieved from the Automation1 controller.
///		You must first create the handle using Automation1_CalibrationFile_Create() before passing it to this function.
///		This function will overwrite any content that already exists in the specified calibration file, replacing it with
///		the contents of the galvo power correction file retrieved from the Automation1 controller.
///		Only use this if the function call was successful.
/// @return Returns true if the galvo power correction file was successfully retrieved from the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetGalvoPowerCorrectionFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Sets a configured 1D calibration file on an Automation1 controller.
///		After calling this function to set the configured 1D calibration file on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the 1D calibration file on.
/// @param[In] calibrationFile The 1D calibration file to set on the Automation1 controller.
///		Use the Automation1_CalibrationFile_Create() function to obtain an Automation1CalibrationFile handle.
/// @return Returns true if the 1D calibration file was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetCalibration1DFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Sets a configured 2D calibration file on an Automation1 controller.
///		After calling this function to set the configured 2D calibration file on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the 2D calibration file on.
/// @param[In] calibrationFile The 2D calibration file to set on the Automation1 controller.
///		Use the Automation1_CalibrationFile_Create() function to obtain an Automation1CalibrationFile handle.
/// @return Returns true if the 2D calibration file was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetCalibration2DFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Sets a configured galvo 2D calibration file on an Automation1 controller.
///		After calling this function to set the configured galvo 2D calibration file on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the galvo 2D calibration file on.
/// @param[In] calibrationFile The galvo 2D calibration file to set on the Automation1 controller.
///		Use the Automation1_CalibrationFile_Create() function to obtain an Automation1CalibrationFile handle.
/// @return Returns true if the galvo 2D calibration file was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetGalvo2DCalibrationFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Sets a configured galvo power correction file on an Automation1 controller.
///		After calling this function to set the configured galvo power correction file on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the galvo power correction file on.
/// @param[In] calibrationFile The galvo power correction file to set on the Automation1 controller.
///		Use the Automation1_CalibrationFile_Create() function to obtain an Automation1CalibrationFile handle.
/// @return Returns true if the galvo power correction file was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetGalvoPowerCorrectionFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Gets whether a configured 1D calibration file is set on an Automation1 controller.
///		If a configured 1D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetCalibration1DFile().
/// @param[In] controller The Automation1 controller to get whether a 1D calibration file is set on.
/// @param[Out] isCalibration1DFileSetOut Whether a configured 1D calibration file is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether a configured 1D calibration file is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsCalibration1DFileSet(Automation1Controller controller, bool* isCalibration1DFileSetOut);

/// @brief Gets whether a configured 2D calibration file is set on an Automation1 controller.
///		If a configured 2D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetCalibration2DFile().
/// @param[In] controller The Automation1 controller to get whether a 2D calibration file is set on.
/// @param[Out] isCalibration2DFileSetOut Whether a configured 2D calibration file is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether a configured 2D calibration file is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsCalibration2DFileSet(Automation1Controller controller, bool* isCalibration2DFileSetOut);

/// @brief Gets whether a configured galvo 2D calibration file is set on an Automation1 controller.
///		If a configured galvo 2D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetGalvo2DCalibrationFile().
/// @param[In] controller The Automation1 controller to get whether a galvo 2D calibration file is set on.
/// @param[Out] isGalvo2DCalibrationFileSetOut Whether a configured galvo 2D calibration file is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether a configured galvo 2D calibration file is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsGalvo2DCalibrationFileSet(Automation1Controller controller, bool* isGalvo2DCalibrationFileSetOut);

/// @brief Gets whether a configured galvo power correction file is set on an Automation1 controller.
///		If a configured galvo power correction file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetGalvoPowerCorrectionFile().
/// @param[In] controller The Automation1 controller to get whether a galvo power correction file is set on.
/// @param[Out] isGalvoPowerCorrectionFileSetOut Whether a configured galvo power correction file is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether a configured galvo power correction file is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsGalvoPowerCorrectionFileSet(Automation1Controller controller, bool* isGalvoPowerCorrectionFileSetOut);

/// @brief Removes the configured 1D calibration file from an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configured 1D calibration file from.
/// @return Returns true if the configured 1D calibration file was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveCalibration1DFile(Automation1Controller controller);

/// @brief Removes the configured 2D calibration file from an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configured 2D calibration file from.
/// @return Returns true if the configured 2D calibration file was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveCalibration2DFile(Automation1Controller controller);

/// @brief Removes the configured galvo 2D calibration file from an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configured galvo 2D calibration file from.
/// @return Returns true if the configured galvo 2D calibration file was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveGalvo2DCalibrationFile(Automation1Controller controller);

/// @brief Removes the configured galvo power correction file from an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configured galvo power correction file from.
/// @return Returns true if the configured galvo power correction file was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveGalvoPowerCorrectionFile(Automation1Controller controller);

/// @brief Gets the configured program automation from an Automation1 controller
///		If program automation has not been configured, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsConfiguredProgramAutomationSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the configured program automation from.
/// @param[In] configuredProgramAutomation The handle to store the controller's configured program automation files in.
///		You must first create the handle using Automation1_ConfiguredProgramAutomation_Create() before passing it to this function.
///		This function will clear all other configured program automation files that are set in this handle and replace them with the
///		configured program automation files from the Automation1Controller. 
/// @return Returns true if the configured program automation from the Automation1 controller was retrieved successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetConfiguredProgramAutomation(Automation1Controller controller, Automation1ConfiguredProgramAutomation configuredProgramAutomation);

/// @brief Sets the configured program automation on an Automation1 controller.
///		After calling this function to set the configured program automation on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the configured program automation on.
/// @param[In] configuredProgramAutomation The configured program automation to set on the Automation1 controller.
///		Use the Automation1_ConfiguredProgramAutomation_Create() function to obtain an Automation1ConfiguredProgramAutomation handle.
/// @return Returns true if the configured program automation was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetConfiguredProgramAutomation(Automation1Controller controller, Automation1ConfiguredProgramAutomation configuredProgramAutomation);

/// @brief Gets whether configured program automation is set on an Automation1 controller.
///		If configured program automation has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetConfiguredProgramAutomation().
/// @param[In] controller The Automation1 controller to get whether configured program automation is set on.
/// @param[Out] isConfigurationSetOut Whether configured program automation is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether configured program automation is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsConfiguredProgramAutomationSet(Automation1Controller controller, bool* isConfigurationSetOut);

/// @brief Removes the configured program automation from an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configured program automation from.
/// @return Returns true if the configured program automation was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveConfiguredProgramAutomation(Automation1Controller controller);

/// @brief Creates a new Automation1ConfiguredParameters handle.
///		Make sure to call Automation1_ConfiguredParameters_Destroy() to avoid leaking memory when you are done using this handle.
/// @param[Out] configuredParametersOut The created Automation1ConfiguredParameters handle. Only use this if the function call was successful.
/// @return Returns true if the Automation1ConfiguredParameters handle was created successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_Create(Automation1ConfiguredParameters* configuredParametersOut);

/// @brief Destroys the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The Automation1ConfiguredParameters handle to destroy.
/// @return Returns true if the handle was successfully destroyed otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_Destroy(Automation1ConfiguredParameters configuredParameters);

/// @brief Gets the string value of a configured system parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the system parameter from.
/// @param[In] parameterId The system parameter to get the value of.
/// @param[Out] valueOut The null-terminated string value of the specified system parameter.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] valueMaxLength The maximum number of elements to copy to the valueOut function argument.
/// 	This must not be greater than the length of the valueOut array.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetSystemStringValue(Automation1ConfiguredParameters configuredParameters, Automation1SystemParameterId parameterId, char* valueOut, int32_t valueMaxLength);

/// @brief Gets the numeric value of a configured system parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the system parameter from.
/// @param[In] parameterId The system parameter to get the value of.
/// @param[Out] valueOut The numeric value of the specified system parameter. Only use this if the function call was successful.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetSystemValue(Automation1ConfiguredParameters configuredParameters, Automation1SystemParameterId parameterId, double* valueOut);

/// @brief Sets the string value of a configured system parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the system parameter on.
/// @param[In] parameterId The system parameter to set the value of.
/// @param[In] value The null-terminated string value to set the specified system parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetSystemStringValue(Automation1ConfiguredParameters configuredParameters, Automation1SystemParameterId parameterId, const char* value);

/// @brief Sets the numeric value of a configured system parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the system parameter on.
/// @param[In] parameterId The system parameter to set the value of.
/// @param[In] value The numeric value to set the specified system parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetSystemValue(Automation1ConfiguredParameters configuredParameters, Automation1SystemParameterId parameterId, double value);

/// @brief Gets the string value of a configured axis parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the axis parameter from.
/// @param[In] axisIndex The axis to get the parameter from.
/// @param[In] parameterId The axis parameter to get the value of.
/// @param[Out] valueOut The null-terminated string value of the specified axis parameter.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] valueMaxLength The maximum number of elements to copy to the valueOut function argument.
/// 	This must not be greater than the length of the valueOut array.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetAxisStringValue(Automation1ConfiguredParameters configuredParameters, int32_t axisIndex, Automation1AxisParameterId parameterId, char* valueOut, int32_t valueMaxLength);

/// @brief Gets the numeric value of a configured axis parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the axis parameter from.
/// @param[In] axisIndex The axis to get the parameter from.
/// @param[In] parameterId The axis parameter to get the value of.
/// @param[Out] valueOut The numeric value of the specified axis parameter. Only use this if the function call was successful.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetAxisValue(Automation1ConfiguredParameters configuredParameters, int32_t axisIndex, Automation1AxisParameterId parameterId, double* valueOut);

/// @brief Sets the string value of a configured axis parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the axis parameter on.
/// @param[In] axisIndex The axis to set the parameter on.
/// @param[In] parameterId The axis parameter to set the value of.
/// @param[In] value The null-terminated string value to set the specified axis parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetAxisStringValue(Automation1ConfiguredParameters configuredParameters, int32_t axisIndex, Automation1AxisParameterId parameterId, const char* value);

/// @brief Sets the numeric value of a configured axis parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the axis parameter on.
/// @param[In] axisIndex The axis to set the parameter on.
/// @param[In] parameterId The axis parameter to set the value of.
/// @param[In] value The numeric value to set the specified axis parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetAxisValue(Automation1ConfiguredParameters configuredParameters, int32_t axisIndex, Automation1AxisParameterId parameterId, double value);

/// @brief Gets the string value of a configured task parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the task parameter from.
/// @param[In] taskIndex The task to get the parameter from.
/// @param[In] parameterId The task parameter to get the value of.
/// @param[Out] valueOut The null-terminated string value of the specified task parameter.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] valueMaxLength The maximum number of elements to copy to the valueOut function argument.
/// 	This must not be greater than the length of the valueOut array.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetTaskStringValue(Automation1ConfiguredParameters configuredParameters, int32_t taskIndex, Automation1TaskParameterId parameterId, char* valueOut, int32_t valueMaxLength);

/// @brief Gets the numeric value of a configured task parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the task parameter from.
/// @param[In] taskIndex The task to get the parameter from.
/// @param[In] parameterId The task parameter to get the value of.
/// @param[Out] valueOut The numeric value of the specified task parameter. Only use this if the function call was successful.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetTaskValue(Automation1ConfiguredParameters configuredParameters, int32_t taskIndex, Automation1TaskParameterId parameterId, double* valueOut);

/// @brief Sets the string value of a configured task parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the task parameter on.
/// @param[In] taskIndex The task to set the parameter on.
/// @param[In] parameterId The task parameter to set the value of.
/// @param[In] value The null-terminated string value to set the specified task parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetTaskStringValue(Automation1ConfiguredParameters configuredParameters, int32_t taskIndex, Automation1TaskParameterId parameterId, const char* value);

/// @brief Sets the numeric value of a configured task parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the task parameter on.
/// @param[In] taskIndex The task to set the parameter on.
/// @param[In] parameterId The task parameter to set the value of.
/// @param[In] value The numeric value to set the specified task parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetTaskValue(Automation1ConfiguredParameters configuredParameters, int32_t taskIndex, Automation1TaskParameterId parameterId, double value);

/// @brief Creates a new Automation1CalibrationFile handle.
///		Make sure to call Automation1_CalibrationFile_Destroy() to avoid leaking memory when you are done using this handle.
/// @param[Out] calibrationFileOut The created Automation1CalibrationFile handle. Only use this if the function call was successful.
/// @return Returns true if the Automation1CalibrationFile handle was created successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CalibrationFile_Create(Automation1CalibrationFile* calibrationFileOut);

/// @brief Destroys the Automation1CalibrationFile handle.
/// @param[In] calibrationFile The Automation1CalibrationFile handle to destroy.
/// @return Returns true if the handle was successfully destroyed otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CalibrationFile_Destroy(Automation1CalibrationFile calibrationFile);

/// @brief Gets the content of a calibration file as an array of bytes.
/// @param[In] calibrationFile The calibration file to get the content from.
/// @param[Out] calibrationFileContentOut The content of the calibration file as an array of bytes.
/// @param[Out] calibrationFileContentLengthOut The length of the calibrationFileContentOut array.
///		This argument will be set to the exact length if the calibrationFileContentOut argument is null.
///		If the calibrationFileContentOut argument is not null, this will be set to the number of bytes that was actually copied into calibrationFileContentOut.
/// @return Returns true if the content was successfully copied to the specified array otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CalibrationFile_GetContent(Automation1CalibrationFile calibrationFile, uint8_t* calibrationFileContentOut, int32_t* calibrationFileContentLengthOut);

/// @brief Sets the content of a calibration file from an array of bytes.
/// @param[In] calibrationFile The calibration file to set the content of.
/// @param[In] calibrationFileContent The array of bytes to set as the content of the calibration file.
/// @param[In] calibrationFileContentLength The length of the calibrationFileContent array.
/// @return Returns true if the calibration file's content was successfully set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CalibrationFile_SetContent(Automation1CalibrationFile calibrationFile, uint8_t* calibrationFileContent, int32_t calibrationFileContentLength);

/// @brief Creates a new Automation1ConfiguredProgramAutomation handle.
///		Make sure to call Automation1_ConfiguredProgramAutomation_Destroy() to avoid leaking memory when you are done using this handle.
/// @param[Out] configuredProgramAutomationOut The created Automation1ConfiguredProgramAutomation handle. Only use this if the function call was successful.
/// @return Returns true if the Automation1ConfiguredProgramAutomation handle was created successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_Create(Automation1ConfiguredProgramAutomation* configuredProgramAutomationOut);

/// @brief Destroys the Automation1ConfiguredProgramAutomation handle.
/// @param[In] configuredProgramAutomation The Automation1ConfiguredProgramAutomation handle to destroy.
/// @return Returns true if the handle was successfully destroyed otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_Destroy(Automation1ConfiguredProgramAutomation configuredProgramAutomation);

/// @brief Adds a compiled AeroScript program to automatically load or run on the specified task whenever the controller starts.
///		Whenever the controller starts, the specified compiled AeroScript program will automatically load or run on the specified task.
///		Only one compiled AeroScript program can be configured to automatically load or run on each task. This function will fail if a compiled
///		AeroScript program is already configured to automatically load or run on the specificied task. To change the compiled AeroScript program that is
///		configured to automatically load or run on a task, first call Automation1_ConfiguredProgramAutomation_RemoveCompiledProgram().
/// @param[In] configuredProgramAutomation The configuration in which to add a compiled AeroScript program to automatically load or run.
/// @param[In] taskIndex The task that the compiled AeroScript program should automatically load or run on.
/// @param[In] shouldRun Whether the compiled AeroScript program should automatically run on the specified task whenever the controller starts.
///		If this argument is set to true, the program will automatically run whenever the controller starts, otherwise the program will only be loaded
///		whenever the controller starts.
/// @param[In] controllerFileName The compiled AeroScript program to automatically load or run whenever the controller starts.
/// @return Returns true if the compiled AeroScript program was successfully added, otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_AddCompiledProgram(Automation1ConfiguredProgramAutomation configuredProgramAutomation, int32_t taskIndex, bool shouldRun, const char* controllerFileName);

/// @brief Removes a compiled AeroScript program from being automatically loaded or run on the specified task whenever the controller starts.
/// @param[In] configuredProgramAutomation The configuration from which to remove a compiled AeroScript program from being automatically loaded or run.
/// @param[In] taskIndex The task from which to remove the compiled AeroScript program from being automatically loaded or run on.
/// @return Returns true if the compiled AeroScript program was successfully removed, otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_RemoveCompiledProgram(Automation1ConfiguredProgramAutomation configuredProgramAutomation, int32_t taskIndex);

/// @brief Gets the controller file names of all compiled AeroScript programs that are configured to load or run.
///		Since the maximum number of tasks on any Automation1 controller is 32, and only one compiled AeroScript program can be configured to a task at a time, this function will
///		return arrays of length 32.
/// @param[In] configuredProgramAutomation The configuration from which to get the compiled AeroScript programs that are configured to be automatically loaded or run.
/// @param[Out] shouldRunOut An array of length 32 that indicates whether each compiled AeroScript program should automatically run on the corresponding task.
/// @param[Out] controllerFileNamesOut The array to store the controller file names of compiled AeroScript programs that are configured to automatically load or run.
///		The controller file names will be null-terminated and will be stored in succession based on the maxControllerFileNameLengthOut argument. 
///		The number of controller file names that will be copied is 32, one corresponding to each task.
///		Set this argument to null to get the exact values for the maxControllerFileNameLengthOut argument.
/// @param[Out] maxControllerFileNameLengthOut The maximum length of the controller file name (including the null-terminator).
///		This argument will be set to the exact length if the controllerFileNamesOut argument is null.
///		To avoid calling this function twice to get the exact size, set this parameter to 1000 characters.
///		If controllerFileNamesOut is not null, this will be set to the actual max controller file name length that was used to copy file names into controllerFileNamesOut.
/// @return Returns true if the compiled AeroScript program was successfully retrieved or no compiled AeroScript program was configured, otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_GetCompiledPrograms(Automation1ConfiguredProgramAutomation configuredProgramAutomation, bool* shouldRunOut, char* controllerFileNamesOut, int32_t* maxControllerFileNameLengthOut);

/// @brief Adds an AeroScript source file to be automatically included.
/// @param[In] configuredProgramAutomation The configuration to add the AeroScript source file to.
/// @param[In] controllerFileName The null-terminated name of the AeroScript source file to automatically include.
/// @return Returns true if the AeroScript source file was successfully added, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_AddProgramSourceFile(Automation1ConfiguredProgramAutomation configuredProgramAutomation, const char* controllerFileName);

/// @brief Removes an AeroScript source file that is configured to be automatically included.
/// @param[In] configuredProgramAutomation The configuration to remove the AeroScript source file from.
/// @param[In] controllerFileName The null-terminated name of the AeroScript source file to remove.
/// @return Returns true if the AeroScript source file was successfully removed, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_RemoveProgramSourceFile(Automation1ConfiguredProgramAutomation configuredProgramAutomation, const char* controllerFileName);

/// @brief Gets the list of AeroScript source file that are configured to be automatically included.
/// @param[In] configuredProgramAutomation The configuration to get the AeroScript source files from.
/// @param controllerFileNamesOut[Out] The array to store the controller file names of AeroScript source files that are configured to be automatically included.
///		The controller file names will be null-terminated and will be stored in succession based on the maxControllerFileNameLengthOut argument. 
///		The number of controller file names that will be copied is based on the controllerFileNamesLengthOut argument.
///		Set this argument to null to get the exact values for the controllerFileNamesLengthOut and maxControllerFileNameLengthOut arguments.
/// @param controllerFileNamesLengthOut[Out] The length of the controllerFileNamesOut argument.
///		This argument will be set to the exact length if the controllerFileNamesOut argument is null.
///		If controllerFileNamesOut is not null, this will be set to the number of controller file names that were actually copied into controllerFileNamesOut.
/// @param maxControllerFileNameLengthOut[Out] The maximum length of the controller file name (including the null-terminator).
///		This argument will be set to the exact length if the controllerFileNamesOut argument is null.
///		To avoid calling this function twice to get the exact size, set this parameter to 1000 characters.
///		If controllerFileNamesOut is not null, this will be set to the actual max controller file name length that was used to copy file names into controllerFileNamesOut.
/// @return Returns true if the names of the AeroScript source files configured to be automatically included were succesfully retrieved, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_GetProgramSourceFiles(Automation1ConfiguredProgramAutomation configuredProgramAutomation, char* controllerFileNamesOut, int32_t* controllerFileNamesLengthOut, int32_t* maxControllerFileNameLengthOut);

/// @brief Adds a compiled AeroScript library to be automatically loaded.
/// @param[In] configuredProgramAutomation The configuration to add the compiled AeroScript library to.
/// @param[In] shouldAutoImport Whether the compiled AeroScript library should be automatically imported.
///		If this argument is set to true, AeroScript programs do not need to import the library to make use of any items it exposes.
/// @param[In] controllerFileName The null-terminated name of the compiled AeroScript library to load.
/// @return Returns true if the compiled AeroScript library was successfully added, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_AddCompiledLibrary(Automation1ConfiguredProgramAutomation configuredProgramAutomation, bool shouldAutoImport, const char* controllerFileName);

/// @brief Removes a compiled AeroScript library from being automatically loaded.
/// @param[In] configuredProgramAutomation The configuration to remove the compiled AeroScript library from.
/// @param[In] controllerFileName The null-terminated name of the compiled AeroScript library to remove.
/// @return Returns true if the compiled AeroScript library was successfully removed, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_RemoveCompiledLibrary(Automation1ConfiguredProgramAutomation configuredProgramAutomation, const char* controllerFileName);

/// @brief Gets the list of compiled AeroScript libraries that are configured to be automatically loaded.
/// @param[In] configuredProgramAutomation The configuration to get the compiled AeroScript libraries from.
/// @param[Out] shouldAutoImportOut An array that indicates whether each compiled AeroScript library should be automatically imported.
///		The length of this array will be the same as the number of controller file names copied into the controllerFileNamesOut argument.
///		This argument must have memory preallocated before passing it to this function. The length of this array must be greater than or
///		equal to the controllerFileNamesLengthOut argument.
/// @param[Out] controllerFileNamesOut The array to store the controller file names of compiled AeroScript libraries that are configured to be loaded.
///		The controller file names will be null-terminated and will be stored in succession based on the maxControllerFileNameLengthOut argument. 
///		The number of controller file names that will be copied is based on the controllerFileNamesLengthOut argument.
///		Set this argument to null to get the exact values for the controllerFileNamesLengthOut and maxControllerFileNameLengthOut arguments.
/// @param[Out] controllerFileNamesLengthOut The length of the controllerFileNamesOut argument.
///		This argument will be set to the exact length if the controllerFileNamesOut argument is null.
///		If controllerFileNamesOut is not null, this will be set to the number of controller file names that were actually copied into controllerFileNamesOut.
/// @param[Out] maxControllerFileNameLengthOut The maximum length of the controller file name (including the null-terminator).
///		This argument will be set to the exact length if the controllerFileNamesOut argument is null.
///		To avoid calling this function twice to get the exact size, set this parameter to 1000 characters.
///		If controllerFileNamesOut is not null, this will be set to the actual max controller file name length that was used to copy file names into controllerFileNamesOut.
/// @return Returns true if the names of the compiled AeroScript libraries configured to be loaded were succesfully retrieved, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_GetCompiledLibraries(Automation1ConfiguredProgramAutomation configuredProgramAutomation, bool* shouldAutoImportOut, char* controllerFileNamesOut, int32_t* controllerFileNamesLengthOut, int32_t* maxControllerFileNameLengthOut);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1CONFIGURATION_H_INCLUDED
