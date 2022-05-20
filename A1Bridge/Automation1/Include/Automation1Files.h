#ifndef AUTOMATION1FILES_H_INCLUDED
#define AUTOMATION1FILES_H_INCLUDED

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

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Gets the names of all controller files (including their paths) on the Automation1 controller.
///		You may use this function by providing reasonable estimate for the fileNamesLengthOut and maxFileNameLengthOut arguments
///		or you can obtain their exact values by first calling this function with the fileNamesOut argument set to null.
///		If other processes are working with controller files between the first function call and the second function
///		call, the exact values may not be correct and you may not get all the files on the controller.
/// @param controller[In] The controller to get the file names from.
/// @param fileNamesOut[Out] The array to store the file names. File names will be null-terminated and will
///		be stored in succession based on the maxFileNameLengthOut argument. The number of files that will be copied
///		is based on the fileNamesLengthOut argument.
///		Set this argument to null to get the exact values for the fileNamesLengthOut and maxFileNameLengthOut arguments.
/// @param fileNamesLengthOut[Out] The length of the fileNamesOut argument.
///		This argument will be set to the exact length if the fileNamesOut argument is null.
///		To avoid calling this function twice to get the exact size, set this parameter based on your usage of
///		controller files.
///		If fileNamesOut is not null, this will be set to the number of files that was actually copied
///		into fileNamesOut.
/// @param maxFileNameLengthOut[Out] The maximum length of the file name (including the null-terminator).
///		This argument will be set to the exact length if fileNamesOut argument is null.
///		To avoid calling this function twice to get the exact size, set this parameter to 1000 characters.
///		If fileNamesOut is not null, this will be set to the actual max file name length that was
///		used to copy file names into fileNamesOut.
/// @return Returns true if the controller operation was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Files_GetAllFiles(Automation1Controller controller, char* fileNamesOut, int32_t* fileNamesLengthOut, int32_t* maxFileNameLengthOut);

/// @brief Writes the content of a controller file on the Automation1 controller. This will overwrite any existing file with the same file name.
/// @param controller[In] The controller to write the file to.
/// @param controllerFileName[In] The null-terminated name of the controller file to write.
/// @param fileContent[In] The byte array of content to write to the file.
/// @param fileContentLength[In] The length of the fileContent argument.
/// @return Returns true if the controller operation was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Files_WriteBytes(Automation1Controller controller, const char* controllerFileName, const uint8_t* fileContent, int32_t fileContentLength);

/// @brief Gets the file content of a controller file from the Automation1 controller.
///		You may use this function by providing a reasonable estimate for the fileContentLengthOut argument or you can
///		obtain the exact value by first calling this function with the fileContentOut argument set to null.
///		If other processes are working with controller files between the first function call and the second function
///		call, the exact file length may not be correct and you may not get all the content of the file.
/// @param controller[In] The controller to get the file content from.
/// @param controllerFileName[In] The null-terminated name of the controller file.
/// @param fileContentOut[Out] The byte array to store the file content in.
///		Set this argument to null to get the exact value for the fileContentLengthOut argument.
/// @param fileContentLengthOut[Out] The length of the fileContentOut argument.
///		This argument will be set to the exact length if fileContentOut argument is null.
///		To avoid calling this function twice to get the exact size, set this parameter based on your usage of
///		controller files.
///		If fileContentOut is not null, this will be set to the number of bytes that was actually copied into
///		fileContentOut.
/// @return Returns true if the controller operation was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Files_ReadBytes(Automation1Controller controller, const char* controllerFileName, uint8_t* fileContentOut, int32_t* fileContentLengthOut);

/// @brief Deletes a controller file on the Automation1 controller. If the file doesn't exist, this function will succeed.
/// @param controller[In] The controller to delete the file on.
/// @param controllerFileName[In] The null-terminated name of the controller file to delete.
/// @return Returns true if the controller operation was successful otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Files_Delete(Automation1Controller controller, const char* controllerFileName);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1FILES_H_INCLUDED