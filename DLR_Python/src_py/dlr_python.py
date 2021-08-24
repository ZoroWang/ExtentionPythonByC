# @Version : 1.2
# @Author : Dynamsoft

from enum import IntEnum
from abc import ABC, abstractmethod
from dlr import DLR

class EnumDLRErrorCode(IntEnum):
    """Error code"""

    DLR_OK = 0  
    DLRERR_UNKNOWN = -10000 
    DLRERR_NO_MEMORY = -10001 
    DLRERR_NULL_POINTER = -10002 
    DLRERR_LICENSE_INVALID = -10003 
    DLRERR_LICENSE_EXPIRED = -10004
    DLRERR_FILE_NOT_FOUND = -10005 
    DLRERR_FILETYPE_NOT_SUPPORTED = -10006 
    DLRERR_BPP_NOT_SUPPORTED = -10007 
    DLRERR_IMAGE_READ_FAILED = -10012
    DLRERR_TIFF_READ_FAILED = -10013
    DLRERR_PDF_READ_FAILED = -10021
    DLRERR_PDF_DLL_MISSING = -10022
    DLRERR_RECOGNITION_TIMEOUT = -10026
    DLRERR_JSON_PARSE_FAILED = -10030 
    DLRERR_JSON_TYPE_INVALID = -10031 
    DLRERR_JSON_KEY_INVALID = -10032 
    DLRERR_JSON_VALUE_INVALID = -10033 
    DLRERR_JSON_NAME_KEY_MISSING = -10034
    DLRERR_JSON_NAME_VALUE_DUPLICATED = -10035
    DLRERR_TEMPLATE_NAME_INVALID = -10036
    DLRERR_PARAMETER_VALUE_INVALID = -10038
    DLRERR_SET_MODE_ARGUMENT_ERROR = -10051
    DLRERR_GET_MODE_ARGUMENT_ERROR = -10055
    DLRERR_CHARACTER_MODEL_FILE_NOT_FOUND = -10100
    DMERR_NO_LICENSE = -20000
    DMERR_HANDSHAKE_CODE_INVALID = -20001
    DMERR_LICENSE_BUFFER_FAILED = -20002
    DMERR_LICENSE_SYNC_FAILED = -20003
    DMERR_DEVICE_NOT_MATCH = -20004
    DMERR_BIND_DEVICE_FAILED = -20005
    DMERR_LICENSE_INTERFACE_CONFLICT = -20006
    DMERR_LICENSE_CLIENT_DLL_MISSING = -20007
    DMERR_INSTANCE_COUNT_OVER_LIMIT = -20008
    DMERR_LICENSE_INIT_SEQUENCE_FAILED = -20009
    DMERR_TRIAL_LICENSE = -20010
    DMERR_FAILED_TO_REACH_LTS = -20200


class EnumDLRImagePixelFormat(IntEnum):
    """Describes the image pixel format."""

    DLR_IPF_BINARY = 0
    DLR_IPF_BINARYINVERTED = 1
    DLR_IPF_GRAYSCALED = 2
    DLR_IPF_NV21 = 3
    DLR_IPF_RGB_565 = 4
    DLR_IPF_RGB_555 = 5
    DLR_IPF_RGB_888 = 6 
    DLR_IPF_ARGB_8888 = 7
    DLR_IPF_RGB_161616 = 8
    DLR_IPF_ARGB_16161616 = 9
    DLR_IPF_ABGR_8888 = 10
    DLR_IPF_ABGR_16161616 = 11
    DLR_IPF_BGR_888 = 12


class EnumDLRGrayscaleTransformationMode(IntEnum):
    """Describes the grayscale transformation mode."""

    DLR_GTM_INVERTED = 0x01
    DLR_GTM_ORIGINAL = 0x02
    DLR_GTM_AUTO = 0x04
    DLR_GTM_REV = 0x80000000
    DLR_GTM_SKIP = 0x00


class EnumDLRRegionPredetectionMode(IntEnum):
    """Describes the region predetection mode."""

    DLR_RPM_AUTO = 0x01
    DLR_RPM_GENERAL = 0x02
    DLR_RPM_GENERAL_RGB_CONTRAST = 0x04
    DLR_RPM_GENERAL_GRAY_CONTRAST = 0x08
    DLR_RPM_GENERAL_HSV_CONTRAST = 0x10
    DLR_RPM_REV = 0x80000000
    DLR_RPM_SKIP = 0


class EnumDLRBinarizationMode(IntEnum):
    """Describes the binarization mode."""

    DLR_BM_AUTO = 0x01
    DLR_BM_LOCAL_BLOCK = 0x02
    DLR_BM_THRESHOLD = 0x04
    DLR_BM_REV = 0x80000000
    DLR_BM_SKIP = 0x00


class EnumDLRImagePreprocessingMode(IntEnum):
    """Describes the image preprocessing mode."""

    DLR_IPM_AUTO = 0x01
    DLR_IPM_GENERAL = 0x02
    DLR_IPM_GRAY_EQUALIZE = 0x04
    DLR_IPM_GRAY_SMOOTH = 0x08
    DLR_IPM_SHARPEN_SMOOTH = 0x10
    DLR_IPM_MORPHOLOGY = 0x20
    DLR_IPM_REV = 0x80000000
    DLR_IPM_SKIP = 0x00


class EnumDLRLocalizationSourceType(IntEnum):
    """Describes localization source type."""

    DLR_LST_MANUAL_SPECIFICATION = 0x01
    DLR_LST_PREDETECTED_REGION = 0x02
    DLR_LST_BARCODE = 0x04


class EnumDLRScaleUpMode(IntEnum):
    """Describes scale up mode."""

    DLR_SUM_SKIP = 0x00
    DLR_SUM_AUTO = 0x01
    DLR_SUM_LINEAR_INTERPOLATION = 0x02
    DLR_SUM_NEAREST_NEIGHBOUR_INTERPOLATION = 0x04


class EnumDLRBarcodeFormat(IntEnum):
    """Describes the barcode types in BarcodeFormat group 1."""

    DLR_BF_ALL = -31457281
    DLR_BF_ONED = 0x001007FF
    DLR_BF_GS1_DATABAR = 0x0003F800
    DLR_BF_CODE_39 = 0x1
    DLR_BF_CODE_128 = 0x2
    DLR_BF_CODE_93 = 0x4
    DLR_BF_CODABAR = 0x8
    DLR_BF_ITF = 0x10
    DLR_BF_EAN_13 = 0x20
    DLR_BF_EAN_8 = 0x40
    DLR_BF_UPC_A = 0x80
    DLR_BF_UPC_E = 0x100
    DLR_BF_INDUSTRIAL_25 = 0x200
    DLR_BF_CODE_39_EXTENDED = 0x400
    DLR_BF_GS1_DATABAR_OMNIDIRECTIONAL = 0x800
    DLR_BF_GS1_DATABAR_TRUNCATED = 0x1000
    DLR_BF_GS1_DATABAR_STACKED = 0x2000
    DLR_BF_GS1_DATABAR_STACKED_OMNIDIRECTIONAL = 0x4000
    DLR_BF_GS1_DATABAR_EXPANDED = 0x8000
    DLR_BF_GS1_DATABAR_EXPANDED_STACKED = 0x10000
    DLR_BF_GS1_DATABAR_LIMITED = 0x20000
    DLR_BF_PATCHCODE = 0x00040000
    DLR_BF_PDF417 = 0x02000000
    DLR_BF_QR_CODE = 0x04000000
    DLR_BF_DATAMATRIX = 0x08000000
    DLR_BF_AZTEC = 0x10000000
    DLR_BF_MAXICODE = 0x20000000
    DLR_BF_MICRO_QR = 0x40000000
    DLR_BF_MICRO_PDF417 = 0x00080000
    DLR_BF_GS1_COMPOSITE = 0x80000000
    DLR_BF_MSI_CODE = 0x100000
    DLR_BF_NULL = 0x00


class EnumDLRBarcodeFormat_2(IntEnum):
    """Describes the barcode types in BarcodeFormat group 2."""

    DLR_BF2_NULL = 0x00
    DLR_BF2_POSTALCODE = 0x01F00000
    DLR_BF2_NONSTANDARD_BARCODE = 0x01
    DLR_BF2_USPSINTELLIGENTMAIL = 0x00100000
    DLR_BF2_POSTNET = 0x00200000
    DLR_BF2_PLANET = 0x00400000
    DLR_BF2_AUSTRALIANPOST = 0x00800000
    DLR_BF2_RM4SCC = 0x01000000
    DLR_BF2_DOTCODE = 0x02


class DLRPoint:
    """
    Stores an x- and y-coordinate pair in two-dimensional space.
    
    Attributes:
    -----------
    - x <int> : The X coordinate of the point

    - y <int> : The Y coordinate of the point

    """

    def __init__(self, point):
        ''' Init Function '''
        self.x = point["X"]
        self.y = point["Y"]


    def _convert_to_innner(self):
        point = {}
        point["X"] = self.x
        point["Y"] = self.y
        return point


class DLRImageData:
    """
    Stores the image data.
    
    Attributes:
    -----------
    - bytes <bytearray> : The image data content in a byte array

    - width <int> : The width of the image in pixels

    - height <int> : The height of the image in pixels

    - stride <int> : The stride(or scan width) of the image.

    - format <EnumDLRImagePixelFormat> : The image pixel format used in the image byte array.
    """

    def __init__(self, image_data):
        ''' Init Function '''
        self.bytes = image_data["Bytes"]
        self.width = image_data["Width"]
        self.height = image_data["Height"]
        self.stride = image_data["Stride"]
        self.format = image_data["ImagePixelFormat"]


    def _convert_to_innner(self):
        image_data = {}
        image_data["Bytes"] = self.bytes
        image_data["Width"] = self.width
        image_data["Height"] = self.height
        image_data["Stride"] = self.stride
        image_data["ImagePixelFormat"] =self.format
        return image_data


class DLRQuadrilateral:
    """
    Stores the quadrilateral.

    Attributes:
    -----------
    - point <List[DLRPoint]> : Four vertexes in a clockwise direction of a quadrilateral. Index 0 represents the left-most vertex.
    """

    def __init__(self, quadrilateral):
        ''' Init Function '''
        points = quadrilateral["Points"]
        self.points = []
        for point in points:
            self.points.append(DLRPoint(point))
    

    def _convert_to_innner(self):
        quadrilateral = {}
        points = []
        for point in self.points:
            points.append(point._convert_to_innner())
        quadrilateral["Points"] = points
        return quadrilateral


class DLRReferenceRegion:
    """
    Stores the region info.

    Attributes:
    -----------
    - localization_source_type <EnumDLRLocalizationSourceType> : The source type used to localize the reference region(s).
        - Value range : A value of the DLRLocalizationSourceType Enumeration items.
        - Default value : DLR_LST_MANUAL_SPECIFICATION

    - points <List[DLRPoint]> : Four vertexes in a clockwise direction of a quadrilateral. Index 0 represents the left-most vertex.
        - Remarks : 
            - It works only when localizationSourceType is settings to DLR_LST_MANUAL_SPECIFICATION.
            - The library will localize reference region(s) based on the quadrilateral set by current setting.
   
    - region_measured_by_percentage <int> : Whether or not to use percentage to measure the coordinate.
        - Value range : [0, 1]
        - Default value : 1
        - Remarks : 
            - It works only when localizationSourceType is settings to DLR_LST_MANUAL_SPECIFICATION.
            - 0: not by percentage
            - 1: by percentage
            - When it's set to 1, the values of points indicate percentage (from 0 to 100); Otherwise, they indicate coordinates in pixel.

    - region_predetection_modes_index <int> : The index of a specific region predetection mode in the regionPredetectionModes parameter.
        - Value range : [-1, 0x7fffffff]
        - Default value : -1
        - Remarks : 
            - It works only when localizationSourceType is settings to DLR_LST_PREDETECTED_REGION.
            - The library will localize reference region(s) based on the detected regions from the specified region predetection mode.
    
    - barcode_format_ids <int> : The formats of the barcode in BarcodeFormat group 1.
        - Value range : A combined value of DLRBarcodeFormat Enumeration items.
        - Default value : DLR_BF_ALL
        - Remarks : 
            - Barcode formats in DLRBarcodeFormat group 1 can be combined.
            - It works only when localizationSourceType is settings to DLR_LST_BARCODE.
            - The library will localize reference region(s) based on the barcodes whose format meets current setting.

    - barcode_format_ids_2 <int> : The formats of the barcode in BarcodeFormat group 2.
        - Value range : A combined value of DLRBarcodeFormat_2 Enumeration items.
        - Default value : DLR_BF_ALL
        - Remarks : 
            - Barcode formats in DLRBarcodeFormat group 2 can be combined.
            - It works only when localizationSourceType is settings to DLR_LST_BARCODE.
            - The library will localize reference region(s) based on the barcodes whose format meets current setting.

    - barcode_text_regex_pattern <str> : The regular express pattern of barcode text.
        - Value range : A combined value of DLRBarcodeFormat_2 Enumeration items.
        - Remarks : 
            - It works only when localizationSourceType is settings to DLR_LST_BARCODE.
            - The library will localize reference region(s) based on the barcodes whose format meets current setting.
    
    """

    def __init__(self, reference_region):
        ''' Init Function '''

        self.localization_source_type = reference_region["LocalizationSourceType"]
        points = reference_region["Points"]
        self.points = []
        for point in points:
            self.points.append(DLRPoint(point))
        
        self.region_measured_by_percentage = reference_region["RegionMeasuredByPercentage"]
        self.region_predetection_modes_index = reference_region["RegionPredetectionModesIndex"]
        self.barcode_format_ids = reference_region["BarcodeFormatIds"]
        self.barcode_format_ids_2 = reference_region["BarcodeFormatIds_2"]
        self.barcode_text_regex_pattern = reference_region["BarcodeTextRegExPattern"]
    

    def _convert_to_innner(self):
        reference_region = {}

        reference_region["LocalizationSourceType"] = self.localization_source_type
        points = []
        for point in self.points:
            points.append(point._convert_to_innner())
        reference_region["Points"] = points

        reference_region["RegionMeasuredByPercentage"] = self.region_measured_by_percentage
        reference_region["RegionPredetectionModesIndex"] = self.region_predetection_modes_index
        reference_region["BarcodeFormatIds"] = self.barcode_format_ids
        reference_region["BarcodeFormatIds_2"] = self.barcode_format_ids_2
        reference_region["BarcodeTextRegExPattern"] = self.barcode_text_regex_pattern
        return reference_region


class DLRRuntimeSettings:
    """
    Defines a struct to configure the runtime settings. These settings control the recognition process.

    Attributes:
    -----------
    - max_thread_count <int> : Sets the number of the threads the algorithm will use to recognize label.
        - Value range : [1, 4]
        - Default value : 4
        - Remarks : 
            - To keep a balance between speed and quality, the library concurrently runs four different threads by default.

    - character_model_name <str> : Sets the name of the CharacterModel.
        - Value range : ["Letter", "NumberLetter", "NumberUppercase", "Number"] or other customized character model name.
    
    - lines_count <int> : Sets the text lines count of the text area.
        - Value range : [0, 200]
        - Default value : 0
        - Remarks : 
            - 0: line count is not certain.
    
    - region_predetection_modes <List[EnumDLRRegionPredetectionMode]> : Sets the region predetection modes.
        - Value range : Each array item can be any one of the DLRRegionPredetectionMode Enumeration items.
        - Default value : [DLR_RPM_GENERAL,DLR_RPM_SKIP,DLR_RPM_SKIP,DLR_RPM_SKIP,DLR_RPM_SKIP,DLR_RPM_SKIP,DLR_RPM_SKIP,DLR_RPM_SKIP]
        - Remarks : 
            - The array index represents the priority of the item. The smaller index is, the higher priority is.

    - reference_region <class DLRReferenceRegion> : Sets the reference region to search for text.

    - text_area <class DLRQuadrilateral> : Sets the text area relative to the reference region.

    - grayscale_transformation_modes <List[DLRGrayscaleTransformationMode]> : Sets the mode and priority for the grayscale image conversion.
        - Value range : Each array item can be any one of the DLRGrayscaleTransformationMode Enumeration items.
        - Default value : [DLR_GTM_ORIGINAL,DLR_GTM_SKIP,DLR_GTM_SKIP,DLR_GTM_SKIP,DLR_GTM_SKIP,DLR_GTM_SKIP,DLR_GTM_SKIP,DLR_GTM_SKIP]
        - Remarks : 
            - The array index represents the priority of the item. The smaller index is, the higher priority is.
    """

    def __init__(self, settings):
        ''' Init Function '''
        self.max_thread_count = settings["MaxThreadCount"]
        self.character_model_name = settings["CharacterModelName"]
        self.lines_count = settings["LinesCount"]
        self.region_predetection_modes = settings["RegionPredetectionModes"]
        self.reference_region = settings["ReferenceRegion"]
        self.text_area = settings["TextArea"]
        self.grayscale_transformation_modes = settings["GrayscaleTransformationModes"]


    def _convert_to_innner(self):
        settings = {}
        settings["MaxThreadCount"] = self.max_thread_count
        settings["CharacterModelName"] = self.character_model_name
        settings["LinesCount"] = self.lines_count
        settings["RegionPredetectionModes"] = self.region_predetection_modes
        settings["ReferenceRegion"] = self.reference_region
        settings["TextArea"] = self.text_area
        settings["GrayscaleTransformationModes"] = self.grayscale_transformation_modes
        return settings

    
    def update_settings(self, settings):
        settings["MaxThreadCount"] = self.max_thread_count
        settings["CharacterModelName"] = self.character_model_name
        settings["LinesCount"] = self.lines_count
        settings["RegionPredetectionModes"] = self.region_predetection_modes
        settings["ReferenceRegion"] = self.reference_region
        settings["TextArea"] = self.text_area
        settings["GrayscaleTransformationModes"] = self.grayscale_transformation_modes


class DLRCharacterResult:
    """
    Stores character result.

    Attributes:
    -----------
    character_H <char> : The recognized character with highest confidence.
    
    character_M <char> : The recognized character with middle confidence.
    
    character_L <char> : The recognized character with lowest confidence.
    
    location <class DLRQuadrilateral> : The location of current character.
    """

    def __init__(self, character_result):
        self.character_H = character_result["CharacterH"]
        self.character_M = character_result["CharacterM"]
        self.character_L = character_result["CharacterL"]
        self.location = DLRQuadrilateral(character_result["Location"])


class DLRLineResult:
    """
    Stores line result.

    Attributes:
    -----------
    line_specification_name <str> : The name of the line specification used to recognize current line result.
    
    text <str> : The recognized text, ends by '\0'.
    
    character_model_name <str> : The character model used to recognize the text.
    
    location <class DLRQuadrilateral> : The localization of current line.
    
    confidence <int> : The confidence of the result.
    
    character_results <List[DLRCharacterResult]> : The character results array.
    """

    def __init__(self, line_result):
        self.line_specification_name = line_result["LineSpecificationName"]
        self.text = line_result["Text"]
        self.character_model_name = line_result["CharacterModelName"]
        self.location = DLRQuadrilateral(line_result["Location"])
        self.confidence = line_result["Confidence"]

        character_results = line_result["CharacterResults"]
        if type(character_results) is list:
            self.character_results = []
            length = len(character_results)
            for character_result in character_results:
                self.character_results.append(DLRCharacterResult(character_result))
        else:
            self.character_results = None


class DLRResult:
    """
    Stores result.

    Attributes:
    -----------
    reference_region_name <str> : The name of the reference region used to recognize current result.

    text_area_name <str> : The name of the text area used to recognize current result.

    location <class DLRQuadrilateral> : The localization result.

    confidence <int> : The confidence of the result.

    line_results <List[DLRLineResult]> : The line results array.

    page_number <int> : Page number.
    """

    def __init__(self, result):
        self.reference_region_name = result["ReferenceRegionName"]
        self.textAreaName = result["TextAreaName"]
        self.location = DLRQuadrilateral(result["Location"])
        self.confidence = result["Confidence"]
        self.page_number = result["PageNumber"]

        line_results = result["LineResults"]
        if type(line_results) is list:
            self.line_results = []
            length = len(line_results)
            for line_result in line_results:
                self.line_results.append(DLRLineResult(line_result))
        else:
            self.line_results = None


class DLRLTSConnectionParameters:
    """ Stores License Tracking Server connection parameters. """

    def __init__(self, parameters):
        ''' Init Function '''
        self.main_server_url = parameters["MainServerURL"]
        self.standby_server_url = parameters["StandbyServerURL"]
        self.handshake_code = parameters["HandshakeCode"]
        self.session_password = parameters["SessionPassword"]
        self.deployment_type = parameters["DeploymentType"]
        self.charge_way = parameters["ChargeWay"]
        self.uuid_generation_method = parameters["UUIDGenerationMethod"]
        self.max_buffer_days = parameters["MaxBufferDays"]
        self.limited_license_modules = parameters["LimitedLicenseModules"]
        self.max_concurrent_instance_count = parameters["MaxConcurrentInstanceCount"]
        self.organization_id = parameters["OrganizationID"]
        self.products = parameters["Products"]

    def update_parameters(self, parameters):
        ''' update parameters '''
        parameters["MainServerURL"] = self.main_server_url
        parameters["StandbyServerURL"] = self.standby_server_url
        parameters["HandshakeCode"] = self.handshake_code
        parameters["SessionPassword"] = self.session_password
        parameters["DeploymentType"] = self.deployment_type
        parameters["ChargeWay"] = self.charge_way
        parameters["UUIDGenerationMethod"] = self.uuid_generation_method
        parameters["MaxBufferDays"] = self.max_buffer_days
        parameters["LimitedLicenseModulesCount"] = len(self.limited_license_modules)
        parameters["LimitedLicenseModules"] = self.limited_license_modules
        parameters["MaxConcurrentInstanceCount"] = self.max_concurrent_instance_count
        parameters["OrganizationID"] = self.organization_id
        parameters["Products"] = self.products


class LabelRecognitionError(Exception):

    def __init__(self, error_message):
        super().__init__(self)
        self.error_info = error_message
    
    def __str__(self):
        return self.error_info


class LabelRecognition:
    """
    Defines a class that provides functions for recognizing labels in images. This is the main interface for recognizing labels.
    
    Attributes:
    -----------
    - version <str> : The Dynamsoft Label Recognition - Python Edition version
    - dlr_version <str> : The Dynamsoft Label Recognition version

    Methods:
    -----------
    - Common Functions
        - get_error_string(error_code)
    - License Functions
        - init_license(dbr_license)
        - init_license_from_lts(lts_connection_parameters)
        - init_lts_connection_parameters() 
    - Runtime Settings Functions
        - get_runtime_settings()
        - update_runtime_settings(settings)
        - reset_runtime_settings()
        - set_mode_argument(modes_name, index, argument_name, argument_value)
        - get_mode_argument(modes_name, index, argument_name)
    """

    __dlr__ = DLR()

    def __init__(self):
        self.__dlr = DLR()
        self.__dlr.CreateInstance()
        self.dlr_version = self.__dlr.GetDLRVersion()

    def __del__(self):
        self.__dlr.DestoryInstance()

    def get_error_string(self, error_code):
        '''Get the detailed error message by error code.
            :param error_code <int> : Error code
            :return error_string <str> : The detailed error message
        '''
        error_string = self.__dlr.GetErrorString(error_code)
        return error_string
    
    def init_license(self, dlr_license):
        '''Reads product key and activates the SDK. 
            :param dlr_license <std> : The product keys.
            :return error <tuple> :error_code = error[0], error_message = error[1], if error_code != EnumErrorCode.DLR_OK, 
                you can get the detailed error message by error_message.
        '''
        error = self.__dlr.InitLicense(dlr_license)
        return error
    
    @staticmethod
    def init_lts_connection_parameters():
        '''
        '''
        cp_parameters = LabelRecognition.__dlr__.InitLTSConnectionParameters()
        parameters = DLRLTSConnectionParameters(cp_parameters)
        return parameters

    @staticmethod
    def init_license_from_lts(lts_connection_parameters):
        ''' Initializes the barcode reader license and connects to the specified server for online verification.
            :param lts_connection_parameters <DLRLTSConnectionParameters> : The struct DMLTSConnectionParameters with customized settings.
            :return error <tuple> : error_code = error[0], error_message = error[1], if error_code != EnumDLRErrorCode.DLR_OK, 
                you can get the detailed error message by error_message. 
            :exception LabelRecognitionError : If error happens, this function will throw a LabelRecognitionError exception that can report the detailed error message.
        '''
        cp_parameters = LabelRecognition.__dlr__.InitLTSConnectionParameters()
        lts_connection_parameters.update_parameters(cp_parameters)
        error = LabelRecognition.__dlr__.InitLicenseFromLTS(cp_parameters)
        if error[0] == EnumDLRErrorCode.DMERR_LICENSE_INTERFACE_CONFLICT:
            raise LabelRecognitionError(error[1])
        else:
            return error

    def get_runtime_settings(self):
        '''Get current runtime settings.
            :return runtime_settings <class DLRRuntimeSettings> : The DLRRuntimeSettings object of current runtime settings.
        '''
        cp_settings = self.__dlr.GetRuntimeSettings()
        settings = DLRRuntimeSettings(cp_settings)
        return settings

    def update_runtime_settings(self, settings):
        ''' Update runtime settings with a DLRRuntimeSettings object
            :param settings <class DLRRuntimeSettings> : a DLRRuntimeSettings object.
            :return error         <tuple> : error_code = error[0], error_message = error[1], if error_code != EnumErrorCode.DLR_OK, 
                you can get the detailed error message by error_message.
        '''
        cp_settings = self.__dlr.GetRuntimeSettings()

        settings.update_settings(cp_settings)
        error = self.__dlr.UpdateRuntimeSettings(cp_settings)
        return error


    def reset_runtime_settings(self):
        ''' Resets all parameters to default values. '''
        self.__dlr.ResetRuntimeSettings()


    def set_mode_argument(self, modes_name, index, argument_name, argument_value):
        ''' Sets the optional argument for a specified mode in Modes(Mode) parameters. 
            :param modes_name     <str>   : The modes(mode) parameter name to set argument.
            :param index          <int>   : The array index of modes parameter to indicate a specific mode.
            :param argument_name  <str>   : The name of the argument to set.
            :param argument_value <str>   : The value of the argument to set.
            :return error         <tuple> : error_code = error[0], error_message = error[1], if error_code != EnumErrorCode.DLR_OK, 
                you can get the detailed error message by error_message.
        '''
        error = self.__dlr.SetModeArgument(modes_name, index, argument_name, argument_value)
        return error


    def get_mode_argument(self, modes_name, index, argument_name):
        ''' Gets the optional argument for a specified mode in Modes(Mode) parameters. 
            :param modes_name      <str> : The modes(mode) parameter name to get argument.
            :param index           <int> : The array index of modes parameter to indicate a specific mode.
            :param argument_name   <str> : The name of the argument to get.
            :return argument_value <str> : The value of the argument to get.
            :exception LabelRecognitionError : If error happens, this function will throw a LabelRecognitionError exception that can report the detailed error message.
        '''
        return_value = self.__dlr.GetModeArgument(modes_name, index, argument_name)
        if type(return_value) is str:
            return return_value
        else:
            error_code = return_value[0]
            error_message = return_value[1]
            raise LabelRecognitionError(error_message)

    def clear_appended_settings(self):
        '''Clear all template settings.
        '''
        error = self._dlr_ClearAppendedSettings()
        return error

    def append_settings_from_string(self, json_string):
        ''' Appends DLRParameter settings in a string to the SDK object.
            :param json_string <str> : A json string that represents the content of the settings.
            :return error <tuple> : error_code = error[0], error_message = error[1], if error_code != EnumErrorCode.DLR_OK, 
                you can get the detailed error message by error_message.
        '''
        error = self.__dlr.AppendSettingsFromString(json_string)
        return error

    def append_settings_from_file(self, json_file):
        ''' Appends DLRParameter settings in a string to the SDK object.
            :param json_file <str> : A json string that represents the content of the settings.
            :return error <tuple> : error_code = error[0], error_message = error[1], if error_code != EnumErrorCode.DLR_OK, 
                you can get the detailed error message by error_message.
        '''
        error = self.__dlr.AppendSettingsFromFile(json_file)
        return error

    def output_settings_to_file(self, file_path, template_name):
        '''Output DLRParameter settings into a file(JSON file).
            :param file_path <str> : The output file path which stores settings.
            :param template_name <str> : The name of the template which is to be output.
            :return error <tuple> : error_code = error[0], error_message = error[1], if error_code != EnumErrorCode.DLR_OK, 
                you can get the detailed error message by error_message.
        '''
        error = self.__dlr.OutputSettingsToFile(file_path, template_name)
        return error

    def recognize_by_buffer(self, image_data, template_name):
        '''Recognizes text from memory buffer containing image pixels in defined format.
            :param image_data <class DLRImageData> : A object of DLRImageData that represents an image.
            :param template_name <str> : The template name.
            :return results <list[class DLRResult]> : All results.
            :exception LabelRecognitionError : If error happens, this function will throw a LabelRecognitionError exception that can report the detailed error message.
        '''
        inner_image_data = image_data._convert_to_innner()
        error = self.__dlr.RecognizeByBuffer(inner_image_data, template_name)

        if error[0] == EnumDLRErrorCode.DLR_OK:
            cp_results = self.__dlr.GetAllDLRResults()

            results = []
            if type(cp_results) is list:
                for cp_result in cp_results:
                    results.append(DLRResult(cp_result))
                return results
            else:
                return None
        else:
            raise LabelRecognitionError(error[1])

    def recognize_by_file(self, image_file, template_name):
        '''Recognizes text from a specified image file.
            :param image_file <str> : A string defining the file name.
            :param template_name <str> : The template name.
            :return results <list[class DLRResult]> : All results.
            :exception LabelRecognitionError : If error happens, this function will throw a LabelRecognitionError exception that can report the detailed error message.
        '''
        error = self.__dlr.RecognizeByFile(image_file, template_name)

        if error[0] == EnumDLRErrorCode.DLR_OK:
            cp_results = self.__dlr.GetAllDLRResults()

            results = []
            if type(cp_results) is list:
                for cp_result in cp_results:
                    results.append(DLRResult(cp_result))
                return results
            else:
                return None
        else:
            raise LabelRecognitionError(error[1])

    def update_reference_region_from_barcode_results(self, barcode_results, template_name):
        ''' Updates reference region which is defined with source type DLR_LST_BARCODE
            :param barcode_results <list[TextResult]> : The barcode results used to localize reference region.
            :param template_name : The template name.
            :return error <tuple> : error_code = error[0], error_message = error[1], if error_code != EnumErrorCode.DLR_OK, 
                you can get the detailed error message by error_message.
        '''
        error = self.__dlr.UpdateReferenceRegionFromBarcodeResults(barcode_results, template_name)
        return error


