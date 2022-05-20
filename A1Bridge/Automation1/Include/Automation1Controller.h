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
/// @param controller The connected controller to query.
/// @return Returns the number of axes that are available on the connected Automation1 controller.
AUTOMATION1_CAPI int32_t Automation1_Controller_AvailableAxisCount(Automation1Controller controller);

/// @brief Gets the number of tasks that are available on the connected Automation1 controller.
///		Different Automation1 controllers will have a different supported task count.
/// @param controller The connected controller to query.
/// @return Returns the number of tasks that are available on the connected Autoamtion1 controller.
AUTOMATION1_CAPI int32_t Automation1_Controller_AvailableTaskCount(Automation1Controller controller);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1CONTROLLER_H_INCLUDED