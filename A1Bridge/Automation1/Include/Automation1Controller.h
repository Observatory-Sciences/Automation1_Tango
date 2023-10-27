///
/// Copyright (c) Aerotech, Inc.
///

#ifndef AUTOMATION1CONTROLLER_H_INCLUDED
#define AUTOMATION1CONTROLLER_H_INCLUDED

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

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief A handle that represents a connection to an Automation1 controller.
/// 	See the Automation1_Connect() functions to obtain this type of handle.
/// 	Make sure to call Automation1_Disconnect() to avoid leaking memory when you are done with the controller.
typedef struct Automation1Controller_T* Automation1Controller;

/// @brief Gets the version of the Automation1 C API.
/// @param[Out] majorVersionOut The major version of the API.
/// @param[Out] minorVersionOut The minor version of the API.
/// @param[Out] patchVersionOut The patch version of the API.
AUTOMATION1_CAPI void Automation1_GetApiVersion(int32_t* majorVersionOut, int32_t* minorVersionOut, int32_t* patchVersionOut);

/// @brief Connects to an Automation1 controller.
/// 	Use this function to connect to a controller when the controller is installed on the same computer and has access control disabled.
/// 	Make sure to call Automation1_Disconnect() to avoid leaking memory when you are done with the controller.
/// @param[Out] controllerOut A handle that represents a connection to an Automation1 controller. Only use this if the function call was successful.
/// @return Returns true if the connection was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Connect(Automation1Controller* controllerOut);

/// @brief Connects to an Automation1 drive-based controller that is connected to the same Windows computer over USB.
/// 	Use this function to connect to a controller when the drive-based controller is connected to the same Windows computer over USB.
/// 	Make sure to call Automation1_Disconnect() to avoid leaking memory when you are done with the controller.
/// @param[Out] controllerOut A handle that represents a connection to an Automation1 controller. Only use this if the function
///		call was successful.
/// @return Returns true if the connection was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConnectWithUsb(Automation1Controller* controllerOut);

/// @brief Connects to an Automation1 controller running on the specified host.
/// 	Use this function to connect to a controller when the controller is installed on a different computer and has access control disabled.
/// @param[In] host The null-terminated host name or host IP address of the Automation1 controller to connect to.
/// @param[Out] controllerOut A handle that represents a connection to an Automation1 controller. Only use this if the function call was successful.
/// @return Returns true if the connection was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConnectWithHost(const char* host, Automation1Controller* controllerOut);

/// @brief Connects to an Automation1 controller, using the specified user name and password.
/// @param[In] userName The null-terminated user name for a user with access to the Automation1 controller.
/// @param[In] password The null-terminated password for the specified user.
/// @param[Out] controllerOut A handle that represents a connection to an Automation1 controller. Only use this if the function call was successful.
/// @return Returns true if the connection was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConnectWithUser(const char* userName, const char* password, Automation1Controller* controllerOut);

/// @brief Connects to an Automation1 controller running on the specified host, using the specified user name and password.
/// 	Use this overload to log in to a controller when the controller is installed on a different computer and has access control enabled.
/// 	Make sure to call Automation1_Disconnect() to avoid leaking memory when you are done with the controller.
/// @param[In] host The null-terminated host name or host IP address of the Automation1 controller to connect to.
/// @param[In] userName The null-terminated user name for a user with access to the Automation1 controller.
/// @param[In] password The null-terminated password for the specified user.
/// @param[Out] controllerOut A handle that represents a connection to an Automation1 controller. Only use this if the function call was successful.
/// @return Returns true if the connection was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConnectWithHostAndUser(const char* host, const char* userName, const char* password, Automation1Controller* controllerOut);

/// @brief Disconnects from the Automation1 controller.
/// 	Disconnecting will not change the running state of the Automation1 controller (i.e. if it has started and is running, it will remain running).
///		After calling this function, this controller handle is no longer usable.
/// @param[In] controller The controller to disconnect from.
/// @return Returns true if controller was successfully disconnected from otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Disconnect(Automation1Controller controller);

/// @brief Starts the Automation1 controller if it is not already running.
/// 	Connecting to the Automation1 controller will not change the running state of the controller so use this function to start the controller after connecting.
/// 	If the controller is already running this function does nothing.
/// 	You can check the state of the Automation1 controller by calling the Automation1_Controller_IsRunning() function.
/// @param[In] controller The controller to start.
/// @return Returns true if the controller successfully started otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Controller_Start(Automation1Controller controller);

/// @brief Stops the Automation1 controller if it is currently running. If the controller is already stopped this function does nothing.
/// 	You will remain connected to the Automation1 controller after you stop it, stopping the Automation1 controller does not change your connection.
/// @param[In] controller The controller to stop.
/// @return Returns true if the controller was successfully stopped otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Controller_Stop(Automation1Controller controller);

/// @brief Resets the Automation1 controller, putting the Automation1 controller into a fresh state and performing any initialization.
/// 	The Automation1 controller will be unavailable while the reset is in progress.
/// @param[In] controller The controller to reset.
/// @return Returns true if the controller successfully reset otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Controller_Reset(Automation1Controller controller);

/// @brief Gets whether or not the Automation1 controller has started and is currently running (i.e. running AeroScript programs or performing motion).
/// 	If the controller is running you can safely execute commands on the controller, run programs, etc.
/// @param[In] controller The controller to check.
/// @param[Out] isRunningOut Whether or not the controller is currently running. Only use this if the function call was successful.
/// @return Returns true if the function was able to get the state of the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Controller_IsRunning(Automation1Controller controller, bool* isRunningOut);

/// @brief Gets the number of axes that are available on the connected Automation1 controller.
///		Different Automation1 controllers will have a different supported axis count.
/// @param controller[In] The connected controller to query.
/// @return Returns the number of axes that are available on the connected Automation1 controller.
AUTOMATION1_CAPI int32_t Automation1_Controller_AvailableAxisCount(Automation1Controller controller);

/// @brief Gets the number of tasks that are available on the connected Automation1 controller.
///		Different Automation1 controllers will have a different supported task count.
/// @param controller[In] The connected controller to query.
/// @return Returns the number of tasks that are available on the connected Autoamtion1 controller.
AUTOMATION1_CAPI int32_t Automation1_Controller_AvailableTaskCount(Automation1Controller controller);

/// @brief Gets the corresponding axis index of the specified axis name on the connected Automation1 controller.
///	@param controller[In] The connected controller to query.
/// @param axisName[In] The null-terminated name of the axis that will have its index retrieved.
/// @param axisIndexOut[Out] The index of the axis corresponding to the specified axis name. Only use this if the function call was successful.
///		This argument must have memory preallocated before passing it into this function.
/// @return Returns true if the function was able to get the axis index corresponding to the specified axis name otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Controller_GetAxisIndexFromAxisName(Automation1Controller controller, const char* axisName, int32_t* axisIndexOut);

/// @brief Gets the corresponding task index of the specified task name on the connected Automation1 controller.
///	@param controller[In] The connected controller to query.
/// @param taskName[In] The null-terminated name of the task that will have its index retrieved.
/// @param taskIndexOut[Out] The index of the task corresponding to the specified task name. Only use this if the function call was successful.
///		This argument must have memory preallocated before passing it into this function.
/// @return Returns true if the function was able to get the task index corresponding to the specified task name otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Controller_GetTaskIndexFromTaskName(Automation1Controller controller, const char* taskName, int32_t* taskIndexOut);

/// @brief Gets the name of the connected Automation1 controller.
/// @param controller[In] The connected controller to query.
/// @param nameOut[Out] A character array to store the controller name in.
///		This argument must have memory preallocated before passing it into this function.
/// @param nameLength[Out] The maximum number of elements to copy into the nameOut argument.
///		This must not be greater than the length of the nameOut array.
/// @return Returns true if the function was able to get the name of the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Controller_Name(Automation1Controller controller, char* nameOut, int32_t nameLength);

/// @brief Gets the serial number of the connected Automation1 controller.
/// @param controller[In] The connected controller to query.
/// @param serialNumberOut[Out] A character array to store the serial number in.
///		This argument must have memory preallocated before passing it into this function.
/// @param serialNumberLength[Out] The maximum number of elements to copy into the serialNumberOut argument.
///		This must not be greater than the length of the serialNumberOut array.
/// @return Returns true if the function was able to get the serial number of the controller otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Controller_SerialNumber(Automation1Controller controller, char* serialNumberOut, int32_t serialNumberLength);

/// @brief Downloads a machine controller definition (.mcd) file from the controller and saves it to the specified MDK file path. 
///		A downloaded machine controller definition file can contain both controller configuration and controller files. 
///		This file can be uploaded to any controller to copy this controller's configuration and files.
/// 	When using this function, at least one of the parameters shouldIncludeFiles and shouldIncludeConfiguration must be true.
/// @param controller[In] The controller to get the machine controller definition file from.
/// @param mdkFilePathToMcd[In] The MDK file path to save the downloaded machine controller definition (.mcd) file.
/// @param shouldIncludeFiles[In] Whether or not controller files should be included in the download.
/// @param shouldIncludeConfiguration[In] Whether or not controller configuration should be included in the download.
/// @return Returns true if the controller operation was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Controller_DownloadMcdToFile(Automation1Controller controller, const char* mdkFilePathToMcd, bool shouldIncludeFiles, bool shouldIncludeConfiguration);

/// @brief Uploads the machine controller definition (.mcd) file to the controller from the specified MDK file path.
///		When using this function, at least one of the parameters shouldIncludeFiles and shouldIncludeConfiguration must be true.
///		Before calling this function, make sure there is nothing important on the controller that could be overwritten 
///		or erased. Consider downloading a machine controller definition file as a backup before uploading a different 
///		machine controller definition that may overwrite data.
/// @param controller[In] The controller to upload the machine controller definition file to.
/// @param mdkFilePathToMcd[In] The MDK file path of the machine controller definition to upload.
/// @param shouldIncludeFiles[In] Whether or not controller files should be included in the upload.
/// @param shouldIncludeConfiguration[In] Whether or not controller configuration should be included in the upload.
/// @param eraseController[In] Whether or not the controller should be erased before uploading the new files.
///		When set to true, this operation is effectively a restoration of the controller.
/// @return Returns true if the controller operation was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Controller_UploadMcdToController(Automation1Controller controller, const char* mdkFilePathToMcd, bool shouldIncludeFiles, bool shouldIncludeConfiguration, bool eraseController);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1CONTROLLER_H_INCLUDED