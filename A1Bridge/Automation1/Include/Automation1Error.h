#ifndef AUTOMATION1ERROR_H_INCLUDED
#define AUTOMATION1ERROR_H_INCLUDED

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

/// @brief Gets the last Automation1 error number that occurred on the calling thread.
/// 	Subsequent Automation1 C API function calls executing on the same thread may change this value. Make sure
/// 	to check if a function call succeeded and if it didn't call this function immediately.
/// @return Returns a number representing an Automation1 error.
AUTOMATION1_CAPI int32_t Automation1_GetLastError();

/// @brief Gets a human readable error message corresponding to the last Automation1 error that occurred on the calling thread.
/// 	Subsequent Automation1 C API function calls executing on the same thread may change this value. Make sure
/// 	to check if a function call succeeded and if it didn't call this function immediately.
/// @param[Out] errorMessageOut A character array to store the human readable error message in.
/// 	This argument must have memory preallocated before passing it into this function.
/// @param[In] errorMessageMaxLength The maximum number of elements to copy into the errorMessageOut argument.
/// 	This must not be greater than the length of the errorMessageOut array.
AUTOMATION1_CAPI void Automation1_GetLastErrorMessage(char* errorMessageOut, int32_t errorMessageMaxLength);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a Controller error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a Controller error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerError(int32_t errorNumber);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a ControllerArgument error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a ControllerArgument error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerArgumentError(int32_t errorNumber);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a ControllerOperation error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a ControllerOperation error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerOperationError(int32_t errorNumber);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a ControllerAxisAbort error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a ControllerAxisAbort error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerAxisAbortError(int32_t errorNumber);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a ControllerAxisFault error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a ControllerAxisFault error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerAxisFaultError(int32_t errorNumber);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a ControllerCommunication error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a ControllerCommunication error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerCommunicationError(int32_t errorNumber);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a ControllerDisconnected error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a ControllerDisconnected error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerDisconnectedError(int32_t errorNumber);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a ControllerState error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a ControllerState error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerStateError(int32_t errorNumber);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a ControllerStopped error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a ControllerStopped error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerStoppedError(int32_t errorNumber);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a ControllerInternal error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a ControllerInternal error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerInternalError(int32_t errorNumber);

/// @brief Checks to see if the Automation1 error number passed in qualifies as a ControllerUser error type.
/// 	Automation1 error types are hierarchical so be sure to handle them in the right order (most specific to least).
/// 	For example, you should always check to see if an error number is a ControllerCommunication error type before
/// 	checking to see if it's a Controller error type.
/// @param[In] errorNumber The Automation1 error number to check.
/// @return Returns true if the error number qualifies as a ControllerUser error type otherwise returns false.
AUTOMATION1_CAPI bool Automation1_IsControllerUserError(int32_t errorNumber);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1ERROR_H_INCLUDED