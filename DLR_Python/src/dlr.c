#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string.h>
#include <structmember.h>
#include "DynamsoftCommon.h"
#include "DynamsoftLabelRecognition.h"
#include "DynamsoftBarcodeReader.h"


typedef struct 
{
    PyObject_HEAD
    // handler
    void * hRecognizer;
}DLRObject;

// Inner Functions

static PyObject * CreatePyDMLTSConnectionParameters(DM_LTSConnectionParameters * pParameters)
{
    PyObject * pyParameters = PyDict_New();
    if(pyParameters == NULL)
    { 
        return NULL;     
    }

    PyObject * pyMainServerURL             = Py_BuildValue("s", pParameters->mainServerURL);
    PyObject * pyMainServerURLKey          = Py_BuildValue("s", "MainServerURL");
    PyDict_SetItem(pyParameters, pyMainServerURLKey, pyMainServerURL);
    Py_DECREF(pyMainServerURL);
    Py_DECREF(pyMainServerURLKey);

    PyObject * pyStandbyServerURL           = Py_BuildValue("s", pParameters->standbyServerURL);
    PyObject * pyStandbyServerURLKey        = Py_BuildValue("s", "StandbyServerURL");
    PyDict_SetItem(pyParameters, pyStandbyServerURLKey, pyStandbyServerURL);
    Py_DECREF(pyStandbyServerURL);
    Py_DECREF(pyStandbyServerURLKey);

    PyObject * pyHandshakeCode              = Py_BuildValue("s", pParameters->handshakeCode);
    PyObject * pyHandshakeCodeKey           = Py_BuildValue("s", "HandshakeCode");
    PyDict_SetItem(pyParameters, pyHandshakeCodeKey, pyHandshakeCode);
    Py_DECREF(pyHandshakeCode);
    Py_DECREF(pyHandshakeCodeKey);

    PyObject * pySessionPassword             = Py_BuildValue("s", pParameters->sessionPassword);
    PyObject * pySessionPasswordKey          = Py_BuildValue("s", "SessionPassword");
    PyDict_SetItem(pyParameters, pySessionPasswordKey, pySessionPassword);
    Py_DECREF(pySessionPassword);
    Py_DECREF(pySessionPasswordKey);

    PyObject * pyDeploymentType              = Py_BuildValue("i", pParameters->deploymentType);
    PyObject * pyDeploymentTypeKey           = Py_BuildValue("s", "DeploymentType");
    PyDict_SetItem(pyParameters, pyDeploymentTypeKey, pyDeploymentType);
    Py_DECREF(pyDeploymentType);
    Py_DECREF(pyDeploymentTypeKey);

    PyObject * pyChargeWay              = Py_BuildValue("i", pParameters->chargeWay);
    PyObject * pyChargeWayKey           = Py_BuildValue("s", "ChargeWay");
    PyDict_SetItem(pyParameters, pyChargeWayKey, pyChargeWay);
    Py_DECREF(pyChargeWay);
    Py_DECREF(pyChargeWayKey);

    PyObject * pyUUIDGenerationMethod              = Py_BuildValue("i", pParameters->UUIDGenerationMethod);
    PyObject * pyUUIDGenerationMethodKey           = Py_BuildValue("s", "UUIDGenerationMethod");
    PyDict_SetItem(pyParameters, pyUUIDGenerationMethodKey, pyUUIDGenerationMethod);
    Py_DECREF(pyUUIDGenerationMethod);
    Py_DECREF(pyUUIDGenerationMethodKey);

    PyObject * pyMaxBufferDays              = Py_BuildValue("i", pParameters->maxBufferDays);
    PyObject * pyMaxBufferDaysKey           = Py_BuildValue("s", "MaxBufferDays");
    PyDict_SetItem(pyParameters, pyMaxBufferDaysKey, pyMaxBufferDays);
    Py_DECREF(pyMaxBufferDays);
    Py_DECREF(pyMaxBufferDaysKey);

    PyObject * pyLimitedLicenseModulesCount              = Py_BuildValue("i", pParameters->limitedLicenseModulesCount);
    PyObject * pyLimitedLicenseModulesCountKey           = Py_BuildValue("s", "LimitedLicenseModulesCount");
    PyDict_SetItem(pyParameters, pyLimitedLicenseModulesCountKey, pyLimitedLicenseModulesCount);
    Py_DECREF(pyLimitedLicenseModulesCount);
    Py_DECREF(pyLimitedLicenseModulesCountKey);

    PyObject * pyLimitedLicenseModules            = PyList_New(pParameters->limitedLicenseModulesCount);
    for(int i = 0; i < pParameters->limitedLicenseModulesCount; ++i)
    {
        PyObject * tempLimitedLicenseModule            = Py_BuildValue("i", pParameters->limitedLicenseModules[i]);
        PyList_SetItem(pyLimitedLicenseModules,        i, tempLimitedLicenseModule);
    }
    PyObject * pyLimitedLicenseModulesKey         = Py_BuildValue("s", "LimitedLicenseModules");
    PyDict_SetItem(pyParameters, pyLimitedLicenseModulesKey, pyLimitedLicenseModules);
    Py_DECREF(pyLimitedLicenseModules);
    Py_DECREF(pyLimitedLicenseModulesKey);

    PyObject * pyMaxConcurrentInstanceCount              = Py_BuildValue("i", pParameters->maxConcurrentInstanceCount);
    PyObject * pyMaxConcurrentInstanceCountKey           = Py_BuildValue("s", "MaxConcurrentInstanceCount");
    PyDict_SetItem(pyParameters, pyMaxConcurrentInstanceCountKey, pyMaxConcurrentInstanceCount);
    Py_DECREF(pyMaxConcurrentInstanceCount);
    Py_DECREF(pyMaxConcurrentInstanceCountKey);

    PyObject * pyOrganizationID             = Py_BuildValue("s", pParameters->organizationID);
    PyObject * pyOrganizationIDKey          = Py_BuildValue("s", "OrganizationID");
    PyDict_SetItem(pyParameters, pyOrganizationIDKey, pyOrganizationID);
    Py_DECREF(pyOrganizationID);
    Py_DECREF(pyOrganizationIDKey);

    return pyParameters;
}

DM_LTSConnectionParameters CreateCDMLTSConnectionParameters(PyObject * pyParameters)
{
    DM_LTSConnectionParameters parameters;
    PyObject * pyMainServerURL = PyDict_GetItem(pyParameters, Py_BuildValue("s", "MainServerURL"));
    if(pyMainServerURL != Py_None)
    {
        parameters.mainServerURL = PyUnicode_AsUTF8(pyMainServerURL);
    }
    else
    {
        parameters.mainServerURL = NULL;
    }

    PyObject * pyStandbyServeURL = PyDict_GetItem(pyParameters, Py_BuildValue("s", "StandbyServerURL"));
    if(pyStandbyServeURL != Py_None)
    {
        parameters.standbyServerURL = PyUnicode_AsUTF8(pyStandbyServeURL);
    }
    else
    {
        parameters.standbyServerURL = NULL;
    }
    

    PyObject * pyHandshakeCode = PyDict_GetItem(pyParameters, Py_BuildValue("s", "HandshakeCode"));
    if(pyHandshakeCode != Py_None)
    {
        parameters.handshakeCode = PyUnicode_AsUTF8(pyHandshakeCode);
    }
    else
    {
        parameters.handshakeCode = NULL;
    }   

    PyObject * pySessionPassword = PyDict_GetItem(pyParameters, Py_BuildValue("s", "SessionPassword"));
    if(pySessionPassword != Py_None)
    {
        parameters.sessionPassword = PyUnicode_AsUTF8(pySessionPassword);
    }
    else
    {
        parameters.sessionPassword = NULL;
    }

    parameters.deploymentType = (DM_DeploymentType)PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "DeploymentType")));
    parameters.chargeWay = (DM_ChargeWay)PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "ChargeWay")));
    parameters.UUIDGenerationMethod = (DM_UUIDGenerationMethod)PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "UUIDGenerationMethod")));
    parameters.maxBufferDays = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "MaxBufferDays")));
    parameters.limitedLicenseModulesCount = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "LimitedLicenseModulesCount")));

    if(parameters.limitedLicenseModulesCount != 0)
    {
        parameters.limitedLicenseModules = (DM_LicenseModule*)malloc(sizeof(int) * parameters.limitedLicenseModulesCount);
        PyObject * pyLimitedLicenseModules = PyDict_GetItem(pyParameters, Py_BuildValue("s", "LimitedLicenseModules"));
        for(int i = 0; i < parameters.limitedLicenseModulesCount; ++i)
        {
            parameters.limitedLicenseModules[i] = PyLong_AsLong(PyList_GetItem(pyLimitedLicenseModules, i));
        }
    }
    else
    {
        parameters.limitedLicenseModules = NULL;
    }

    parameters.maxConcurrentInstanceCount = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "MaxConcurrentInstanceCount")));

    PyObject * pyOrganizationID = PyDict_GetItem(pyParameters, Py_BuildValue("s", "OrganizationID"));
    if(pyOrganizationID != Py_None)
    {
        parameters.organizationID = PyUnicode_AsUTF8(pyOrganizationID);
    }
    else
    {
        parameters.organizationID = NULL;
    }

    return parameters;
}

void FreeDMLTSConnectionParameters(DM_LTSConnectionParameters* parameters)
{
    if(parameters->limitedLicenseModules != NULL)
    {
        free(parameters->limitedLicenseModules); 
        parameters->limitedLicenseModules = NULL;
    }
}

static PyObject * CreatePyReferenceRegion(DLRReferenceRegion referenceRegion)
{
    PyObject * pyReferenceRegion = PyDict_New();
    if(pyReferenceRegion == NULL)
    {
        return NULL;     
    }

    PyObject * pyLocalizationSourceTypeKey            = Py_BuildValue("s", "LocalizationSourceType");
    PyObject * pyLocalizationSourceType               = Py_BuildValue("i", referenceRegion.localizationSourceType);
    PyDict_SetItem(pyReferenceRegion, pyLocalizationSourceTypeKey,           pyLocalizationSourceType);
    Py_DECREF(pyLocalizationSourceTypeKey);
    Py_DECREF(pyLocalizationSourceType);

    PyObject * pyPointsKey   = Py_BuildValue("s", "Points");
    PyObject * pyPoints = PyList_New(4);
    for(int j = 0; j < 4; ++j)
    {
        PyObject * pyPoint = PyDict_New();

        PyObject * pyPointXKey   = Py_BuildValue("s", "X");
        PyObject * pyPointX = Py_BuildValue("i", referenceRegion.points[j].x);
        PyDict_SetItem(pyPoint, pyPointXKey, pyPointX);
        Py_DECREF(pyPointXKey);
        Py_DECREF(pyPointX);

        PyObject * pyPointYKey   = Py_BuildValue("s", "Y");
        PyObject * pyPointY = Py_BuildValue("i", referenceRegion.points[j].y);
        PyDict_SetItem(pyPoint, pyPointYKey, pyPointY);
        Py_DECREF(pyPointYKey);
        Py_DECREF(pyPointY);

        PyList_SetItem(pyPoints, j, pyPoint);
    }
    PyDict_SetItem(pyReferenceRegion, pyPointsKey, pyPoints);
    Py_DECREF(pyPointsKey);
    Py_DECREF(pyPoints);

    PyObject * pyRegionMeasuredByPercentageKey            = Py_BuildValue("s", "RegionMeasuredByPercentage");
    PyObject * pyRegionMeasuredByPercentage               = Py_BuildValue("i", referenceRegion.regionMeasuredByPercentage);
    PyDict_SetItem(pyReferenceRegion, pyRegionMeasuredByPercentageKey,           pyRegionMeasuredByPercentage);
    Py_DECREF(pyRegionMeasuredByPercentageKey);
    Py_DECREF(pyRegionMeasuredByPercentage);

    PyObject * pyRegionPredetectionModesIndexKey            = Py_BuildValue("s", "RegionPredetectionModesIndex");
    PyObject * pyRegionPredetectionModesIndex               = Py_BuildValue("i", referenceRegion.regionMeasuredByPercentage);
    PyDict_SetItem(pyReferenceRegion, pyRegionPredetectionModesIndexKey,           pyRegionPredetectionModesIndex);
    Py_DECREF(pyRegionPredetectionModesIndexKey);
    Py_DECREF(pyRegionPredetectionModesIndex);

    PyObject * pyBarcodeFormatIdsKey            = Py_BuildValue("s", "BarcodeFormatIds");
    PyObject * pyBarcodeFormatIds               = Py_BuildValue("i", referenceRegion.barcodeFormatIds);
    PyDict_SetItem(pyReferenceRegion, pyBarcodeFormatIdsKey,           pyBarcodeFormatIds);
    Py_DECREF(pyBarcodeFormatIdsKey);
    Py_DECREF(pyBarcodeFormatIds);

    PyObject * pyBarcodeFormatIdsKey_2            = Py_BuildValue("s", "BarcodeFormatIds_2");
    PyObject * pyBarcodeFormatIds_2               = Py_BuildValue("i", referenceRegion.barcodeFormatIds_2);
    PyDict_SetItem(pyReferenceRegion, pyBarcodeFormatIdsKey_2,           pyBarcodeFormatIds_2);
    Py_DECREF(pyBarcodeFormatIdsKey_2);
    Py_DECREF(pyBarcodeFormatIds_2);

    PyObject * pyBarcodeTextRegExPatternKey            = Py_BuildValue("s", "BarcodeTextRegExPattern");
    PyObject * pyBarcodeTextRegExPattern               = Py_BuildValue("s", referenceRegion.barcodeTextRegExPattern);
    PyDict_SetItem(pyReferenceRegion, pyBarcodeTextRegExPatternKey,           pyBarcodeTextRegExPattern);
    Py_DECREF(pyBarcodeTextRegExPatternKey);
    Py_DECREF(pyBarcodeTextRegExPattern);

    return pyReferenceRegion;
}

DLRReferenceRegion CreateCReferenceRegion(PyObject * pyReferenceRegion)
{
    DLRReferenceRegion referenceRegion;

    referenceRegion.localizationSourceType = (DLRLocalizationSourceType)PyLong_AsLong(PyDict_GetItem(pyReferenceRegion, Py_BuildValue("s", "LocalizationSourceType"))); 

    PyObject * pyPoints = PyDict_GetItem(pyReferenceRegion, Py_BuildValue("s", "Points"));

    for(int i = 0; i < 4; ++i)
    {
        PyObject * pyPoint = PyList_GetItem(pyPoints, i);
        int x = PyLong_AsLong(PyDict_GetItem(pyPoint, Py_BuildValue("s", "X")));
        int y = PyLong_AsLong(PyDict_GetItem(pyPoint, Py_BuildValue("s", "Y")));
        referenceRegion.points[i].x = x;
        referenceRegion.points[i].y = y;
    }

    referenceRegion.regionMeasuredByPercentage = PyLong_AsLong(PyDict_GetItem(pyReferenceRegion, Py_BuildValue("s", "RegionMeasuredByPercentage"))); 
    referenceRegion.regionPredetectionModesIndex = PyLong_AsLong(PyDict_GetItem(pyReferenceRegion, Py_BuildValue("s", "RegionPredetectionModesIndex"))); 
    referenceRegion.barcodeFormatIds = PyLong_AsLong(PyDict_GetItem(pyReferenceRegion, Py_BuildValue("s", "BarcodeFormatIds"))); 
    referenceRegion.barcodeFormatIds_2 = PyLong_AsLong(PyDict_GetItem(pyReferenceRegion, Py_BuildValue("s", "BarcodeFormatIds_2"))); 

    PyObject * pyBarcodeTextRegExPattern = PyDict_GetItem(pyReferenceRegion, Py_BuildValue("s", "BarcodeTextRegExPattern"));
    char * tempBarcodeTextRegExPattern = PyBytes_AsString(pyBarcodeTextRegExPattern);
    memset(referenceRegion.barcodeTextRegExPattern, 0, 64);
    int len = strlen(tempBarcodeTextRegExPattern);
    memcpy(referenceRegion.barcodeTextRegExPattern, tempBarcodeTextRegExPattern, len);

    return referenceRegion;
}

static PyObject * CreatePyQuadrilateral(DLRQuadrilateral quadrilateral)
{
    PyObject * pyQuadrilateral = PyDict_New();
    if(pyQuadrilateral == NULL)
    {
        return NULL;     
    }
    
    PyObject * pyPoints = PyList_New(4);
    for(int j = 0; j < 4; ++j)
    {
        PyObject * pyPoint = PyDict_New();

        PyObject * pyPointX = Py_BuildValue("i",quadrilateral.points[j].x);
        PyObject * pyPointXKey   = Py_BuildValue("s", "X");
        PyDict_SetItem(pyPoint, pyPointXKey, pyPointX);
        Py_DECREF(pyPointX);
        Py_DECREF(pyPointXKey);

        PyObject * pyPointY = Py_BuildValue("i",quadrilateral.points[j].y);
        PyObject * pyPointYKey   = Py_BuildValue("s", "Y");
        PyDict_SetItem(pyPoint, pyPointYKey, pyPointY);
        Py_DECREF(pyPointY);
        Py_DECREF(pyPointYKey);

        PyList_SetItem(pyPoints, j, pyPoint);
    }
    PyObject * pyPointsKey   = Py_BuildValue("s", "Points");
    PyDict_SetItem(pyQuadrilateral, pyPointsKey, pyPoints);
    Py_DECREF(pyPoints);
    Py_DECREF(pyPointsKey);

    return pyQuadrilateral;
}

DLRQuadrilateral CreateCQuadrilateral(PyObject * pyQuadrilateral)
{
    DLRQuadrilateral quadrilateral;
    PyObject * pyPoints = PyDict_GetItem(pyQuadrilateral, Py_BuildValue("s","Points"));

    for(int m = 0; m < 4; ++m)
    {
        PyObject * pyPoint = PyList_GetItem(pyPoints, m);
        quadrilateral.points[m].x = PyLong_AsLong(PyDict_GetItem(pyPoint, Py_BuildValue("s","X")));
        quadrilateral.points[m].y = PyLong_AsLong(PyDict_GetItem(pyPoint, Py_BuildValue("s","Y")));
    }
    return quadrilateral;
}

static PyObject * CreatePyDLRRuntimeSettings(DLRRuntimeSettings settings)
{
    PyObject * pySettings = PyDict_New();
    if(pySettings == NULL)
    {
        return NULL;     
    }

    PyObject * pyMaxThreadCountKey            = Py_BuildValue("s", "MaxThreadCount");
    PyObject * pyMaxThreadCount               = Py_BuildValue("i", settings.maxThreadCount);
    PyDict_SetItem(pySettings, pyMaxThreadCountKey,           pyMaxThreadCount);
    Py_DECREF(pyMaxThreadCountKey);
    Py_DECREF(pyMaxThreadCount);

    PyObject * pyCharacterModelNameKey            = Py_BuildValue("s", "CharacterModelName");
    PyObject * pyCharacterModelName               = Py_BuildValue("s", settings.characterModelName);
    PyDict_SetItem(pySettings, pyCharacterModelNameKey,           pyCharacterModelName);
    Py_DECREF(pyCharacterModelNameKey);
    Py_DECREF(pyCharacterModelName);

    PyObject * pyLinesCountKey            = Py_BuildValue("s", "LinesCount");
    PyObject * pyLinesCount               = Py_BuildValue("i", settings.linesCount);
    PyDict_SetItem(pySettings, pyLinesCountKey,           pyLinesCount);
    Py_DECREF(pyLinesCountKey);
    Py_DECREF(pyLinesCount);

    PyObject * pyRegionPredetectionModes            = PyList_New(8);
    PyObject * pyGrayscaleTransformationModes            = PyList_New(8);
    for(int i = 0; i < 8; ++i)
    {
        PyObject * pyRegionPredetectionMode                  = Py_BuildValue("i", settings.regionPredetectionModes[i]);
        PyList_SetItem(pyRegionPredetectionModes,        i, pyRegionPredetectionMode);

        PyObject * pyGrayscaleTransformationMode             = Py_BuildValue("i", settings.grayscaleTransformationModes[i]);
        PyList_SetItem(pyGrayscaleTransformationModes,        i, pyGrayscaleTransformationMode);
    }

    PyObject * pyRegionPredetectionModesKey   = Py_BuildValue("s", "RegionPredetectionModes");
    PyDict_SetItem(pySettings, pyRegionPredetectionModesKey,  pyRegionPredetectionModes);
    Py_DECREF(pyRegionPredetectionModesKey);
    Py_DECREF(pyRegionPredetectionModes);

    PyObject * pyGrayscaleTransformationModesKey   = Py_BuildValue("s", "GrayscaleTransformationModes");
    PyDict_SetItem(pySettings, pyGrayscaleTransformationModesKey,  pyGrayscaleTransformationModes);
    Py_DECREF(pyGrayscaleTransformationModesKey);
    Py_DECREF(pyGrayscaleTransformationModes);

    PyObject * pyReferenceRegionKey = Py_BuildValue("s", "ReferenceRegion");
    PyObject * pyReferenceRegion = CreatePyReferenceRegion(settings.referenceRegion);
    PyDict_SetItem(pySettings, pyReferenceRegionKey,  pyReferenceRegion);
    Py_DECREF(pyReferenceRegionKey);
    Py_DECREF(pyReferenceRegion);

    PyObject * pyTextAreaKey = Py_BuildValue("s", "TextArea");
    PyObject * pyTextArea = CreatePyQuadrilateral(settings.textArea);
    PyDict_SetItem(pySettings, pyTextAreaKey,  pyTextArea);
    Py_DECREF(pyTextAreaKey);
    Py_DECREF(pyTextArea);

    return pySettings;
}

DLRRuntimeSettings CreateCDLRRuntimeSettings(PyObject * pySettings)
{
    DLRRuntimeSettings settings;

    settings.maxThreadCount = PyLong_AsLong(PyDict_GetItem(pySettings, Py_BuildValue("s", "MaxThreadCount")));
    
    PyObject * pyCharacterModelName = PyDict_GetItem(pySettings, Py_BuildValue("s", "CharacterModelName"));
    char * tempCharacterModelName = PyBytes_AsString(pyCharacterModelName);
    memset(settings.characterModelName, 0, 64);
    int len = strlen(tempCharacterModelName);
    memcpy(settings.characterModelName, tempCharacterModelName, len);

    settings.linesCount = PyLong_AsLong(PyDict_GetItem(pySettings, Py_BuildValue("s", "LinesCount")));

    PyObject * pyGrayscaleTransformationModes = PyDict_GetItem(pySettings, Py_BuildValue("s", "GrayscaleTransformationModes"));
    PyObject * pyRegionPredetectionModes      = PyDict_GetItem(pySettings, Py_BuildValue("s", "RegionPredetectionModes"));

    for(int i = 0; i < 8; ++i)
    {
        settings.grayscaleTransformationModes[i]  = (DLRGrayscaleTransformationMode)(PyLong_AsLong(PyList_GetItem(pyGrayscaleTransformationModes, i)));
        settings.regionPredetectionModes[i]       = (DLRRegionPredetectionMode)(PyLong_AsLong(PyList_GetItem(pyRegionPredetectionModes, i)));
	}

    PyObject * pyReferenceRegion = PyDict_GetItem(pySettings, Py_BuildValue("s", "ReferenceRegion"));
    settings.referenceRegion = CreateCReferenceRegion(pyReferenceRegion);

    PyObject * pyTextArea = PyDict_GetItem(pySettings, Py_BuildValue("s", "TextArea"));
    settings.textArea = CreateCQuadrilateral(pyTextArea);

    return settings;
}

static PyObject * CreatePyDLRImageData(DLRImageData * pImageData)
{
    PyObject * pyImageData = PyDict_New();

    if(pImageData->bytes != NULL)
    {
        PyObject * pyBytes       = PyByteArray_FromStringAndSize(pImageData->bytes, pImageData->bytesLength);
        PyObject * pyBytesKey    = Py_BuildValue("s", "Bytes");
        PyDict_SetItem(pyImageData, pyBytesKey, pyBytes);
        Py_DECREF(pyBytes);
        Py_DECREF(pyBytesKey);
    }
    else
    {
        //PyObject * pyBytes       = Py_BuildValue("o", NULL);
        PyObject * pyBytesKey    = Py_BuildValue("s", "Bytes");
        PyDict_SetItem(pyImageData, pyBytesKey, Py_None);
        //Py_DECREF(pyBytes);
        Py_DECREF(pyBytesKey);
    }
    

    PyObject * pyWidth      = Py_BuildValue("i", pImageData->width);
    PyObject * pyWidthKey   = Py_BuildValue("s", "Width");
    PyDict_SetItem(pyImageData, pyWidthKey, pyWidth);
    Py_DECREF(pyWidth);
    Py_DECREF(pyWidthKey);

    PyObject * pyHeight      = Py_BuildValue("i", pImageData->height);
    PyObject * pyHeightKey   = Py_BuildValue("s", "Height");
    PyDict_SetItem(pyImageData, pyHeightKey, pyHeight);
    Py_DECREF(pyHeight);
    Py_DECREF(pyHeightKey);

    PyObject * pyStride      = Py_BuildValue("i", pImageData->stride);
    PyObject * pyStrideKey   = Py_BuildValue("s", "Stride");
    PyDict_SetItem(pyImageData, pyStrideKey, pyStride);
    Py_DECREF(pyStride);
    Py_DECREF(pyStrideKey);

    PyObject * pyImagePixelFormat      = Py_BuildValue("i", pImageData->format);
    PyObject * pyImagePixelFormatKey   = Py_BuildValue("s", "ImagePixelFormat");
    PyDict_SetItem(pyImageData, pyImagePixelFormatKey, pyImagePixelFormat);
    Py_DECREF(pyImagePixelFormat);
    Py_DECREF(pyImagePixelFormatKey);

    return pyImageData;
}

DLRImageData* CreateCDLRImageData(PyObject * pyImageData)
{
    DLRImageData * pImageData = (DLRImageData*)malloc(sizeof(DLRImageData));

    PyObject * pyBytes = PyDict_GetItem(pyImageData, Py_BuildValue("s","Bytes"));

    if(PyBytes_Check(pyBytes))
    {
        pImageData->bytesLength = (int)PyBytes_Size(pyBytes);
        pImageData->bytes = (unsigned char *)malloc(sizeof(unsigned char) * pImageData->bytesLength);
        memcpy(pImageData->bytes, (unsigned char *)PyBytes_AsString(pyBytes), pImageData->bytesLength);
        // pImageData->bytes = (unsigned char *)PyBytes_AsString(pyBytes);
    }
    else if(PyByteArray_Check(pyBytes))
    {
        pImageData->bytesLength = (int)PyByteArray_Size(pyBytes);
        pImageData->bytes = (unsigned char *)malloc(sizeof(unsigned char) * pImageData->bytesLength);
        memcpy(pImageData->bytes, (unsigned char *)PyByteArray_AsString(pyBytes), pImageData->bytesLength);
        // pImageData->bytes = (unsigned char *)PyByteArray_AsString(pyBytes);
    }
    else if(pyBytes == Py_None)
    {
        pImageData->bytes = NULL;
        pImageData->bytesLength = 0;
    }

    pImageData->format = (DLRImagePixelFormat)PyLong_AsLong(PyDict_GetItem(pyImageData, Py_BuildValue("s","ImagePixelFormat")));
    pImageData->width = PyLong_AsLong(PyDict_GetItem(pyImageData, Py_BuildValue("s","Width")));
    pImageData->height = PyLong_AsLong(PyDict_GetItem(pyImageData, Py_BuildValue("s","Height")));
    pImageData->stride = PyLong_AsLong(PyDict_GetItem(pyImageData, Py_BuildValue("s","Stride")));

    return pImageData;
}

void InnerFreeCDLRImageData(DLRImageData ** ppImageData)
{
    if(ppImageData == NULL || (*ppImageData) == NULL)
    {
        return;
    }

    if((*ppImageData)->bytes != NULL)
    {
        free((*ppImageData)->bytes);
        (*ppImageData)->bytes = NULL;
    }

    free(*ppImageData);
    (*ppImageData) = NULL;
}

static PyObject * CreatePyCharacterResult(PDLRCharacterResult pCharacterResult)
{
    PyObject * pyCharacterResult = PyDict_New();

    if(pyCharacterResult == NULL)
    {
        return NULL;     
    }

    PyObject * pyCharacterHKey   = Py_BuildValue("s", "CharacterH");
    PyObject * pyCharacterH      = Py_BuildValue("C", pCharacterResult->characterH);
    PyDict_SetItem(pyCharacterResult, pyCharacterHKey, pyCharacterH);
    Py_DECREF(pyCharacterHKey);
    Py_DECREF(pyCharacterH);

    PyObject * pyCharacterMKey   = Py_BuildValue("s", "CharacterM");
    PyObject * pyCharacterM      = Py_BuildValue("C", pCharacterResult->characterM);
    PyDict_SetItem(pyCharacterResult, pyCharacterMKey, pyCharacterM);
    Py_DECREF(pyCharacterMKey);
    Py_DECREF(pyCharacterM);

    PyObject * pyCharacterLKey   = Py_BuildValue("s", "CharacterL");
    PyObject * pyCharacterL      = Py_BuildValue("C", pCharacterResult->characterL);
    PyDict_SetItem(pyCharacterResult, pyCharacterLKey, pyCharacterL);
    Py_DECREF(pyCharacterLKey);
    Py_DECREF(pyCharacterL);

    PyObject * pyLocationKey   = Py_BuildValue("s", "Location");
    PyObject * pyLocation      = CreatePyQuadrilateral(pCharacterResult->location);
    PyDict_SetItem(pyCharacterResult, pyLocationKey, pyLocation);
    Py_DECREF(pyLocationKey);
    Py_DECREF(pyLocation);

    return pyCharacterResult;
}

static PyObject * CreatePyLineResult(PDLRLineResult pLineResult)
{
    PyObject * pyLineResult = PyDict_New();

    if(pyLineResult == NULL)
    {
        return NULL;     
    }

    PyObject * pyLineSpecificationNameKey   = Py_BuildValue("s", "LineSpecificationName");
    PyObject * pyLineSpecificationName      = Py_BuildValue("s", pLineResult->lineSpecificationName);
    PyDict_SetItem(pyLineResult, pyLineSpecificationNameKey, pyLineSpecificationName);
    Py_DECREF(pyLineSpecificationNameKey);
    Py_DECREF(pyLineSpecificationName);

    PyObject * pyTextKey   = Py_BuildValue("s", "Text");
    PyObject * pyText      = Py_BuildValue("s", pLineResult->text);
    PyDict_SetItem(pyLineResult, pyTextKey, pyText);
    Py_DECREF(pyTextKey);
    Py_DECREF(pyText);

    PyObject * pyCharacterModelNameKey   = Py_BuildValue("s", "CharacterModelName");
    PyObject * pyCharacterModelName      = Py_BuildValue("s", pLineResult->characterModelName);
    PyDict_SetItem(pyLineResult, pyCharacterModelNameKey, pyCharacterModelName);
    Py_DECREF(pyCharacterModelNameKey);
    Py_DECREF(pyCharacterModelName);

    PyObject * pyLocationKey   = Py_BuildValue("s", "Location");
    PyObject * pyLocation      = CreatePyQuadrilateral(pLineResult->location);
    PyDict_SetItem(pyLineResult, pyLocationKey, pyLocation);
    Py_DECREF(pyLocationKey);
    Py_DECREF(pyLocation);

    PyObject * pyConfidenceKey   = Py_BuildValue("s", "Confidence");
    PyObject * pyConfidence      = Py_BuildValue("i", pLineResult->confidence);
    PyDict_SetItem(pyLineResult, pyConfidenceKey, pyConfidence);
    Py_DECREF(pyConfidenceKey);
    Py_DECREF(pyConfidence);

    int characterResultsCount = pLineResult->characterResultsCount;

    if(characterResultsCount > 0 )
    {
        PyObject * pyCharacterResultsKey   = Py_BuildValue("s", "CharacterResults");
        PyObject * pyCharacterResults = PyList_New(characterResultsCount);
        for(int i = 0; i < characterResultsCount; ++i)
        {
            PyObject * pyCharacterResult = CreatePyCharacterResult(pLineResult->characterResults[i]);
            PyList_SetItem(pyCharacterResults, i, pyCharacterResult);
        }
        PyDict_SetItem(pyLineResult, pyCharacterResultsKey, pyCharacterResults);
        Py_DECREF(pyCharacterResultsKey);
        Py_DECREF(pyCharacterResults);        
    }
    else
    {
        PyObject * pyCharacterResultsKey   = Py_BuildValue("s", "CharacterResults");
        PyObject * pyCharacterResults      = Py_None;
        PyDict_SetItem(pyLineResult, pyCharacterResultsKey, pyCharacterResults);
        Py_DECREF(pyCharacterResultsKey);
        Py_DECREF(pyCharacterResults);  
    }

    return pyLineResult;
}

static PyObject * CreatePyDLRResult(PDLRResult pResult)
{
    PyObject * pyResult = PyDict_New();

    if(pyResult == NULL)
    {
        return NULL;     
    }

    PyObject * pyReferenceRegionNameKey   = Py_BuildValue("s", "ReferenceRegionName");
    PyObject * pyReferenceRegionName      = Py_BuildValue("s", pResult->refereneceRegionName);
    PyDict_SetItem(pyResult, pyReferenceRegionNameKey, pyReferenceRegionName);
    Py_DECREF(pyReferenceRegionNameKey);
    Py_DECREF(pyReferenceRegionName);

    PyObject * pyTextAreaNameKey   = Py_BuildValue("s", "TextAreaName");
    PyObject * pyTextAreaName      = Py_BuildValue("s", pResult->textAreaName);
    PyDict_SetItem(pyResult, pyTextAreaNameKey, pyTextAreaName);
    Py_DECREF(pyTextAreaNameKey);
    Py_DECREF(pyTextAreaName);

    PyObject * pyLocationKey   = Py_BuildValue("s", "Location");
    PyObject * pyLocation      = CreatePyQuadrilateral(pResult->location);
    PyDict_SetItem(pyResult, pyLocationKey, pyLocation);
    Py_DECREF(pyLocationKey);
    Py_DECREF(pyLocation);

    PyObject * pyConfidenceKey   = Py_BuildValue("s", "Confidence");
    PyObject * pyConfidence      = Py_BuildValue("i", pResult->confidence);
    PyDict_SetItem(pyResult, pyConfidenceKey, pyConfidence);
    Py_DECREF(pyConfidenceKey);
    Py_DECREF(pyConfidence);

    PyObject * pyPageNumberKey   = Py_BuildValue("s", "PageNumber");
    PyObject * pyPageNumber      = Py_BuildValue("i", pResult->pageNumber);
    PyDict_SetItem(pyResult, pyPageNumberKey, pyPageNumber);
    Py_DECREF(pyPageNumberKey);
    Py_DECREF(pyPageNumber);

    int lineResultsCount = pResult->lineResultsCount;

    if(lineResultsCount > 0)
    {
        PyObject * pyLineResultList = PyList_New(lineResultsCount);
        for(int i = 0; i < lineResultsCount; ++i)
        {
            PyObject * pyLineResult = CreatePyLineResult(pResult->lineResults[i]);
            PyList_SetItem(pyLineResultList, i, pyLineResult);
        }
        PyObject * pyLineResultsKey   = Py_BuildValue("s", "LineResults");
        PyObject * pyLineResults      = pyLineResultList;
        PyDict_SetItem(pyResult, pyLineResultsKey, pyLineResults);
        Py_DECREF(pyLineResultsKey);
        Py_DECREF(pyLineResults);        
    }
    else
    {
        PyObject * pyLineResultsKey   = Py_BuildValue("s", "LineResults");
        PyObject * pyLineResults      = Py_None;
        PyDict_SetItem(pyResult, pyLineResultsKey, pyLineResults);
        Py_DECREF(pyLineResultsKey);
        Py_DECREF(pyLineResults);  
    }

    return pyResult;
}

static PyObject * CreatePyDLRResults(DLRResultArray* pResultArray)
{
    int resultsCount = pResultArray->resultsCount;
    PDLRResult* results = pResultArray->results;

    PyObject * pyResultList = PyList_New(resultsCount);

    if(pyResultList == NULL)
    {
        return NULL;
    }

    for(int i = 0; i < resultsCount; ++i)
    {
        PyObject * pyResult = CreatePyDLRResult(results[i]);

        PyList_SetItem(pyResultList, i, pyResult);
    }

    return pyResultList;
}

OneDCodeDetails * CreateCOneDCodeDetails(PyObject * pyDetailedResult)
{
    OneDCodeDetails * pDetails = (OneDCodeDetails *)malloc(sizeof(OneDCodeDetails));

    PyObject * pyModuleSize      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "ModuleSize"));
    PyObject * pyStartCharsBytes = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "StartCharsBytes"));
    PyObject * pyStopCharsBytes  = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "StopCharsBytes"));
    PyObject * pyCheckDigitBytes = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "CheckDigitBytes"));
    PyObject * pyStartPatternRange  = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "StartPatternRange"));
    PyObject * pyMiddlePatternRange = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "MiddlePatternRange"));
    PyObject * pyEndPatternRange    = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "EndPatternRange"));

    pDetails->moduleSize = PyLong_AsLong(pyModuleSize);

    pDetails->startCharsBytesLength = (int)PyByteArray_Size(pyStartCharsBytes);
    pDetails->startCharsBytes = (unsigned char *)malloc(sizeof(unsigned char) * pDetails->startCharsBytesLength);
    memcpy(pDetails->startCharsBytes, (unsigned char *)PyByteArray_AsString(pyStartCharsBytes), pDetails->startCharsBytesLength);

    pDetails->stopCharsBytesLength = (int)PyByteArray_Size(pyStopCharsBytes);
    pDetails->stopCharsBytes = (unsigned char *)malloc(sizeof(unsigned char) * pDetails->stopCharsBytesLength);
    memcpy(pDetails->stopCharsBytes, (unsigned char *)PyByteArray_AsString(pyStopCharsBytes), pDetails->stopCharsBytesLength);

    pDetails->checkDigitBytesLength = (int)PyByteArray_Size(pyCheckDigitBytes);
    pDetails->checkDigitBytes = (unsigned char *)malloc(sizeof(unsigned char) * pDetails->checkDigitBytesLength);
    memcpy(pDetails->checkDigitBytes, (unsigned char *)PyByteArray_AsString(pyCheckDigitBytes), pDetails->checkDigitBytesLength);

    for(int i = 0; i < 2; ++i)
    {
        pDetails->startPatternRange[i] = (float)PyFloat_AsDouble(PyList_GetItem(pyStartPatternRange, i));
        pDetails->middlePatternRange[i] = (float)PyFloat_AsDouble(PyList_GetItem(pyMiddlePatternRange, i));
        pDetails->endPatternRange[i] = (float)PyFloat_AsDouble(PyList_GetItem(pyEndPatternRange, i));
    }

    return pDetails;
}

void InnerFreeCOneDCodeDetails(OneDCodeDetails ** ppDetails)
{
    if(ppDetails == NULL || (*ppDetails) == NULL)
    {
        return;
    }

    if((*ppDetails)->startCharsBytes != NULL)
    {
        free((*ppDetails)->startCharsBytes);
        (*ppDetails)->startCharsBytes = NULL;
    }

    if((*ppDetails)->stopCharsBytes != NULL)
    {
        free((*ppDetails)->stopCharsBytes);
        (*ppDetails)->stopCharsBytes = NULL;
    }

    if((*ppDetails)->checkDigitBytes != NULL)
    {
        free((*ppDetails)->checkDigitBytes);
        (*ppDetails)->checkDigitBytes = NULL;
    }

    free(*ppDetails);
    (*ppDetails) = NULL;
}

QRCodeDetails * CreateCQRCodeDetails(PyObject * pyDetailedResult)
{
    QRCodeDetails * pDetails = (QRCodeDetails *)malloc(sizeof(QRCodeDetails));

    PyObject * pyModuleSize      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "ModuleSize"));
    PyObject * pyRows      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Rows"));
    PyObject * pyColumns      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Columns"));
    PyObject * pyVersion      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Version"));
    PyObject * pyErrorCorrectionLevel      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "ErrorCorrectionLevel"));
    PyObject * pyModel      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Model"));
    PyObject * pyMode      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Mode"));
    PyObject * pyPage      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Page"));
    PyObject * pyTotalPage      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "TotalPage"));
    PyObject * pyParityData      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "ParityData"));

    pDetails->moduleSize = PyLong_AsLong(pyModuleSize);
    pDetails->rows = PyLong_AsLong(pyRows);
    pDetails->columns = PyLong_AsLong(pyColumns);
    pDetails->version = PyLong_AsLong(pyVersion);
    pDetails->errorCorrectionLevel = PyLong_AsLong(pyErrorCorrectionLevel);
    pDetails->model = PyLong_AsLong(pyModel);
    pDetails->mode = PyLong_AsLong(pyMode);
    pDetails->page = PyLong_AsLong(pyPage);
    pDetails->totalPage = PyLong_AsLong(pyTotalPage);
    pDetails->parityData = PyLong_AsLong(pyParityData);

    return pDetails;
}

void InnerFreeCQRCodeDetails(QRCodeDetails ** ppDetails)
{
    if(ppDetails == NULL || (*ppDetails) == NULL)
    {
        return;
    }

    free(*ppDetails);
    (*ppDetails) = NULL;
}

DataMatrixDetails * CreateCDataMatrixDetails(PyObject * pyDetailedResult)
{
    DataMatrixDetails * pDetails = (DataMatrixDetails *)malloc(sizeof(DataMatrixDetails));

    PyObject * pyModuleSize      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "ModuleSize"));
    PyObject * pyRows      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Rows"));
    PyObject * pyColumns      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Columns"));
    PyObject * pyDataRegionRows      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "DataRegionRows"));
    PyObject * pyDataRegionColumns      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "DataRegionColumns"));
    PyObject * pyDataRegionNumber      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "DataRegionNumber"));

    pDetails->moduleSize = PyLong_AsLong(pyModuleSize);
    pDetails->rows = PyLong_AsLong(pyRows);
    pDetails->columns = PyLong_AsLong(pyColumns);
    pDetails->dataRegionRows = PyLong_AsLong(pyDataRegionRows);
    pDetails->dataRegionColumns = PyLong_AsLong(pyDataRegionColumns);
    pDetails->dataRegionNumber = PyLong_AsLong(pyDataRegionNumber);

    return pDetails;
}

void InnerFreeCDataMatrixDetails(DataMatrixDetails ** ppDetails)
{
    if(ppDetails == NULL || (*ppDetails) == NULL)
    {
        return;
    }

    free(*ppDetails);
    (*ppDetails) = NULL;
}

PDF417Details * CreateCPDF417Details(PyObject * pyDetailedResult)
{
    PDF417Details * pDetails = (PDF417Details *)malloc(sizeof(PDF417Details));

    PyObject * pyModuleSize      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "ModuleSize"));
    PyObject * pyRows      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Rows"));
    PyObject * pyColumns      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Columns"));
    PyObject * pyErrorCorrectionLevel      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "ErrorCorrectionLevel"));

    pDetails->moduleSize = PyLong_AsLong(pyModuleSize);
    pDetails->rows = PyLong_AsLong(pyRows);
    pDetails->columns = PyLong_AsLong(pyColumns);
    pDetails->errorCorrectionLevel = PyLong_AsLong(pyErrorCorrectionLevel);

    return pDetails;
}

void InnerFreeCPDF417Details(PDF417Details ** ppDetails)
{
    if(ppDetails == NULL || (*ppDetails) == NULL)
    {
        return;
    }

    free(*ppDetails);
    (*ppDetails) = NULL;
}

AztecDetails * CreateCAztecDetails(PyObject * pyDetailedResult)
{
    AztecDetails * pDetails = (AztecDetails *)malloc(sizeof(AztecDetails));

    PyObject * pyModuleSize      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "ModuleSize"));
    PyObject * pyRows      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Rows"));
    PyObject * pyColumns      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "Columns"));
    PyObject * pyLayerNumber      = PyDict_GetItem(pyDetailedResult, Py_BuildValue("s", "LayerNumber"));

    pDetails->moduleSize = PyLong_AsLong(pyModuleSize);
    pDetails->rows = PyLong_AsLong(pyRows);
    pDetails->columns = PyLong_AsLong(pyColumns);
    pDetails->layerNumber = PyLong_AsLong(pyLayerNumber);

    return pDetails;
}

void InnerFreeCAztecDetails(AztecDetails ** ppDetails)
{
    if(ppDetails == NULL || (*ppDetails) == NULL)
    {
        return;
    }

    free(*ppDetails);
    (*ppDetails) = NULL;
}

void * CreateCDetailedResult(PyObject * pyDetailedResult, int format, int format2)
{
    void * pDetailedResult = NULL;

    if((format & BF_ONED) != 0)
    {
        pDetailedResult = (void *)CreateCOneDCodeDetails(pyDetailedResult);
    }
    else if(format == BF_QR_CODE)
    {
        pDetailedResult = (void *)CreateCQRCodeDetails(pyDetailedResult);
    }
    else if(format == BF_DATAMATRIX)
    {
        pDetailedResult = (void *)CreateCDataMatrixDetails(pyDetailedResult);
    }
    else if(format == BF_PDF417)
    {
        pDetailedResult = (void *)CreateCPDF417Details(pyDetailedResult);
    }
    else if(format == BF_AZTEC)
    {
        pDetailedResult = (void *)CreateCAztecDetails(pyDetailedResult);
    }

    return pDetailedResult;
}

void InnerFreeCDetailedResult(void* pDetailedResult, int format, int format2)
{
    if((format & BF_ONED) != 0)
    {
        InnerFreeCOneDCodeDetails(&pDetailedResult);
    }
    else if(format == BF_QR_CODE)
    {
        InnerFreeCQRCodeDetails(&pDetailedResult);
    }
    else if(format == BF_DATAMATRIX)
    {
        InnerFreeCDataMatrixDetails(&pDetailedResult);
    }
    else if(format == BF_PDF417)
    {
        InnerFreeCPDF417Details(&pDetailedResult);
    }
    else if(format == BF_AZTEC)
    {
        InnerFreeCAztecDetails(&pDetailedResult);
    }

}

SamplingImageData CreateCSamplingImageData(PyObject * pySamplingImageData)
{
    SamplingImageData samplingImage;

    PyObject * pyWidth = PyDict_GetItem(pySamplingImageData, Py_BuildValue("s", "Width"));
    PyObject * pyHeight = PyDict_GetItem(pySamplingImageData, Py_BuildValue("s", "Height"));

    samplingImage.width = PyLong_AsLong(pyWidth);
    samplingImage.height = PyLong_AsLong(pyHeight);

    PyObject * pyBytes = PyDict_GetItem(pySamplingImageData, Py_BuildValue("s", "Bytes"));
    samplingImage.bytes = (unsigned char *)malloc(sizeof(unsigned char) * samplingImage.width * samplingImage.height);
    memcpy(samplingImage.bytes, (unsigned char *)PyBytes_AsString(pyBytes), samplingImage.width * samplingImage.height);

    return samplingImage;
}

void InnerFreeCSamplingImageData(SamplingImageData* pSamplingImage)
{
    if(pSamplingImage->bytes != NULL)
    {
        free(pSamplingImage->bytes);
        pSamplingImage->bytes = NULL;
    }
}

LocalizationResult * CreateCLocalizationResult(PyObject * pyLocalizationResult)
{
    LocalizationResult * pLocalizationResult = (LocalizationResult*)malloc(sizeof(LocalizationResult));

    pLocalizationResult->terminatePhase = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "TerminatePhase")));
    pLocalizationResult->barcodeFormat = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "BarcodeFormat")));

    PyObject * pyBarcodeFormatString = PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "BarcodeFormatString"));
    if(pyBarcodeFormatString == Py_None)
    {
        pLocalizationResult->barcodeFormatString = NULL;
    }
    else
    {
        pLocalizationResult->barcodeFormatString = PyBytes_AsString(pyBarcodeFormatString);
    }

    pLocalizationResult->barcodeFormat_2 = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "BarcodeFormat_2")));

    PyObject * pyBarcodeFormatString_2 = PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "BarcodeFormatString_2"));
    if(pyBarcodeFormatString_2 == Py_None)
    {
        pLocalizationResult->barcodeFormatString_2 = NULL;
    }
    else
    {
        pLocalizationResult->barcodeFormatString_2 = PyBytes_AsString(pyBarcodeFormatString_2);
    }
    
    pLocalizationResult->x1 = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "X1")));
    pLocalizationResult->y1 = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "Y1")));
    pLocalizationResult->x2 = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "X2")));
    pLocalizationResult->y2 = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "Y2")));
    pLocalizationResult->x3 = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "X3")));
    pLocalizationResult->y3 = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "Y3")));
    pLocalizationResult->x4 = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "X4")));
    pLocalizationResult->y4 = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "Y4")));
    pLocalizationResult->angle = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "Angle")));
    pLocalizationResult->moduleSize = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "ModuleSize")));
    pLocalizationResult->pageNumber = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "PageNumber")));

    PyObject * pyRegionName = PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "RegionName"));
    if(pyRegionName == Py_None)
    {
        pLocalizationResult->regionName = NULL;
    }
    else
    {
        pLocalizationResult->regionName = PyBytes_AsString(pyRegionName);
    }

    PyObject * pyDocumentName = PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "DocumentName"));
    if(pyDocumentName == Py_None)
    {
        pLocalizationResult->documentName = NULL;
    }
    else
    {
        pLocalizationResult->documentName = PyBytes_AsString(pyDocumentName);
    }

    pLocalizationResult->resultCoordinateType = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "ResultCoordinateType")));

    pLocalizationResult->accompanyingTextBytes = NULL;
    pLocalizationResult->accompanyingTextBytesLength = 0;
    pLocalizationResult->confidence = PyLong_AsLong(PyDict_GetItem(pyLocalizationResult, Py_BuildValue("s", "Confidence")));

    return pLocalizationResult;
}

void InnerFreeCLocalizationResult(LocalizationResult ** ppLocalizationResult)
{
    if(ppLocalizationResult == NULL || (*ppLocalizationResult) == NULL)
    {
        return;
    }

    free(*ppLocalizationResult);
    (*ppLocalizationResult) = NULL;
}

ExtendedResult * CreateCExtendedResult(PyObject * pyExtendedResult)
{
    ExtendedResult * pExtendedResult = (ExtendedResult *)malloc(sizeof(ExtendedResult));

    PyObject * pyResultType = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "ResultType"));
    pExtendedResult->resultType = PyLong_AsLong(pyResultType);

    PyObject * pyBarcodeFormat = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "BarcodeFormat"));
    pExtendedResult->barcodeFormat = PyLong_AsLong(pyBarcodeFormat);

    PyObject * pyBarcodeFormatString = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "BarcodeFormatString"));
    pExtendedResult->barcodeFormatString = PyBytes_AsString(pyBarcodeFormatString);

    PyObject * pyBarcodeFormat_2 = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "BarcodeFormat_2"));
    pExtendedResult->barcodeFormat_2 = PyLong_AsLong(pyBarcodeFormat_2);

    PyObject * pyBarcodeFormatString_2 = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "BarcodeFormatString_2"));
    pExtendedResult->barcodeFormatString_2 = PyBytes_AsString(pyBarcodeFormatString_2);

    PyObject * pyConfidence = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "Confidence"));
    pExtendedResult->confidence = PyLong_AsLong(pyConfidence);

    PyObject * pyBytes = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "Bytes"));
    pExtendedResult->bytesLength = (int)PyBytes_Size(pyBytes);
    pExtendedResult->bytes = (unsigned char *)malloc(sizeof(unsigned char) * pExtendedResult->bytesLength);
    memcpy(pExtendedResult->bytes, (unsigned char *)PyBytes_AsString(pyBytes), pExtendedResult->bytesLength);

    pExtendedResult->accompanyingTextBytes = NULL;
    pExtendedResult->accompanyingTextBytesLength = 0;

    PyObject * pyDeformation = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "Deformation"));
    pExtendedResult->deformation = PyLong_AsLong(pyDeformation);

    PyObject * pyDetailedResult = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "DetailedResult"));
    void* pDetailedResult = CreateCDetailedResult(pyDetailedResult, pExtendedResult->barcodeFormat, pExtendedResult->barcodeFormat_2);
    pExtendedResult->detailedResult = pDetailedResult;

    PyObject * pyClarity = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "Clarity"));
    pExtendedResult->clarity = PyLong_AsLong(pyClarity);

    PyObject * pySamplingImage = PyDict_GetItem(pyExtendedResult, Py_BuildValue("s", "SamplingImage"));
    pExtendedResult->samplingImage = CreateCSamplingImageData(pySamplingImage);

    return pExtendedResult;
}

void InnerFreeCExtendedResult(ExtendedResult ** ppExtendedResult)
{
    if(ppExtendedResult == NULL || (*ppExtendedResult) == NULL)
    {
        return;
    }

    free((*ppExtendedResult)->bytes);

    InnerFreeCDetailedResult(&((*ppExtendedResult)->detailedResult), (*ppExtendedResult)->barcodeFormat, (*ppExtendedResult)->barcodeFormat_2);

    InnerFreeCSamplingImageData(&((*ppExtendedResult)->samplingImage));

    free(*ppExtendedResult);
    (*ppExtendedResult) = NULL;
}

TextResult* CreateCTextResult(PyObject * pyTextResult)
{
    TextResult* pTextResult = (TextResult*)malloc(sizeof(TextResult));

    PyObject * pyBarcodeFormat = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "BarcodeFormat"));
    pTextResult->barcodeFormat = PyLong_AsLong(pyBarcodeFormat);

    PyObject * pyBarcodeFormatString = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "BarcodeFormatString"));
    pTextResult->barcodeFormatString = PyBytes_AsString(pyBarcodeFormatString);

    PyObject * pyBarcodeFormat_2 = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "BarcodeFormat_2"));
    pTextResult->barcodeFormat_2 = PyLong_AsLong(pyBarcodeFormat_2);

    PyObject * pyBarcodeFormatString_2 = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "BarcodeFormatString_2"));
    pTextResult->barcodeFormatString_2 = PyBytes_AsString(pyBarcodeFormatString_2);

    PyObject * pyBarcodeText = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "BarcodeText"));
    pTextResult->barcodeText = PyBytes_AsString(pyBarcodeText);

    PyObject * pyBarcodeBytes = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "BarcodeBytes"));
    pTextResult->barcodeBytesLength = (int)PyBytes_Size(pyBarcodeBytes);
    pTextResult->barcodeBytes = (unsigned char *)malloc(sizeof(unsigned char) * pTextResult->barcodeBytesLength);
    memcpy(pTextResult->barcodeBytes, (unsigned char *)PyBytes_AsString(pyBarcodeBytes), pTextResult->barcodeBytesLength);

    PyObject * pyLocalizationResult = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "LocalizationResult"));
    pTextResult->localizationResult = CreateCLocalizationResult(pyLocalizationResult);

    PyObject * pyDetailedResult = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "DetailedResult"));

    void* pDetailedResult = CreateCDetailedResult(pyDetailedResult, pTextResult->barcodeFormat, pTextResult->barcodeFormat_2);
    pTextResult->detailedResult = pDetailedResult;

    PyObject * pyExtendedResultList = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "ExtendedResults"));
    pTextResult->resultsCount = PyList_Size(pyExtendedResultList);

    pTextResult->results = (PExtendedResult*)malloc(sizeof(PExtendedResult) * pTextResult->resultsCount);

    for(int i = 0; i < pTextResult->resultsCount; ++i)
    {
        PyObject * pyExtendedResult = PyList_GetItem(pyExtendedResultList, i);
        pTextResult->results[i] = CreateCExtendedResult(pyExtendedResult);
    }

    PyObject * pyException = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "Exception"));
    pTextResult->exception = PyBytes_AsString(pyException);

    PyObject * pyIsDPM = PyDict_GetItem(pyTextResult, Py_BuildValue("s", "IsDPM"));
    pTextResult->isDPM = PyLong_AsLong(pyIsDPM);

    return pTextResult;
}

void InnerFreeCTextResult(TextResult** ppTextResult)
{
    if(ppTextResult == NULL || (*ppTextResult) == NULL)
    {
        return;
    }

    free((*ppTextResult)->barcodeBytes);

    InnerFreeCLocalizationResult(&((*ppTextResult)->localizationResult));
    InnerFreeCDetailedResult(&((*ppTextResult)->detailedResult), (*ppTextResult)->barcodeFormat, (*ppTextResult)->barcodeFormat_2);

    for(int i = 0; i < (*ppTextResult)->resultsCount; ++i)
    {
        PExtendedResult pExtendedResult = (*ppTextResult)->results[i];
        InnerFreeCExtendedResult(&pExtendedResult);
    }
    free((*ppTextResult)->results);

    free(*ppTextResult);
    (*ppTextResult) = NULL;
}

TextResultArray* CreateCTextResultArray(PyObject * pyTextResultArray)
{
    TextResultArray* pTextResultArray = (TextResultArray*)malloc(sizeof(TextResultArray));

    pTextResultArray->resultsCount = PyList_Size(pyTextResultArray);
    pTextResultArray->results = (PTextResult*)malloc(sizeof(PTextResult) * pTextResultArray->resultsCount);
    for(int i = 0; i < pTextResultArray->resultsCount; ++i)
    {
        PyObject * pyTextResult = PyList_GetItem(pyTextResultArray, i);
        pTextResultArray->results[i] = CreateCTextResult(pyTextResult);
    }

    return pTextResultArray;
}

void InnerFreeCTextResultArray(TextResultArray** ppTextResultArray)
{
    if(ppTextResultArray == NULL || (*ppTextResultArray) == NULL)
    {
        return;
    }

    for(int i = 0; i < (*ppTextResultArray)->resultsCount; ++i)
    {
        PTextResult pTextResult = (*ppTextResultArray)->results[i];
        InnerFreeCTextResult(&pTextResult);
    }    

    free((*ppTextResultArray)->results);

    free(*ppTextResultArray);
    (*ppTextResultArray) = NULL;
}

// Export Functions

static PyObject * CreateInstance(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;

    self->hRecognizer = DLR_CreateInstance();
    Py_RETURN_NONE;
}

static PyObject * DestoryInstance(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;
    if(self->hRecognizer != NULL)
        DLR_DestroyInstance(self->hRecognizer);
    self->hRecognizer = NULL;

    Py_RETURN_NONE;
}

static PyObject * GetDLRVersion(PyObject *obj, PyObject *args)
{
    const char * version = DLR_GetVersion();
	return Py_BuildValue("s", version);
}

static PyObject * GetErrorString(PyObject *obj, PyObject *args)
{
	int errorCode = 0;
	if (!PyArg_ParseTuple(args, "i", &errorCode))
	{
		Py_RETURN_NONE;
	}

	const char* errorString = DLR_GetErrorString(errorCode);
	return Py_BuildValue("s", errorString);
}

static PyObject * InitLicense(PyObject *obj, PyObject *args)
{
	DLRObject* self = (DLRObject*)obj;

    char *pLicense = NULL;

	if (!PyArg_ParseTuple(args, "s", &pLicense))
    {
		Py_RETURN_NONE;
    }

    int errorCode = DLR_InitLicense(self->hRecognizer, pLicense);

    return Py_BuildValue("i", errorCode);
}

static PyObject * InitLicenseFromLTS(PyObject * obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;

    PyObject * pyParameters;
    if (!PyArg_ParseTuple(args, "O", &pyParameters))
    {
		Py_RETURN_NONE;
    }

    DM_LTSConnectionParameters parameters = CreateCDMLTSConnectionParameters(pyParameters);

    char errorBuffer[512];
    int ret = DLR_InitLicenseFromLTS(&parameters, errorBuffer, 512);

    FreeDMLTSConnectionParameters(&parameters);

    const char* errorString = DLR_GetErrorString(ret);
    if(ret == DLR_OK)
    {
        return Py_BuildValue("(i,s)", ret, errorString);
    }
    else
    {
        return Py_BuildValue("(i,s)", ret, errorBuffer);
    }
}

static PyObject * InitLTSConnectionParameters(PyObject *obj, PyObject *args)
{
    DM_LTSConnectionParameters parameters;
    int errorCode = DLR_InitLTSConnectionParameters(&parameters);

    PyObject * pyParameters = CreatePyDMLTSConnectionParameters(&parameters);

    return pyParameters;
}

static PyObject * GetRuntimeSettings(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;
    DLRRuntimeSettings settings;

    int errorCode = DLR_GetRuntimeSettings(self->hRecognizer, &settings);

    PyObject * pySettings = CreatePyDLRRuntimeSettings(settings);

    return pySettings;
}

static PyObject * UpdateRuntimeSettings(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;
    PyObject *pyParameters;
    if (!PyArg_ParseTuple(args, "O", &pyParameters))
    {
		Py_RETURN_NONE;
    }
    
    DLRRuntimeSettings settings = CreateCDLRRuntimeSettings(pyParameters);
    char szErrorMsgBuffer[256];
    int errorCode = DLR_UpdateRuntimeSettings(self->hRecognizer, &settings, szErrorMsgBuffer, 256);
	return Py_BuildValue("(i,s)", errorCode, szErrorMsgBuffer);
}

static PyObject * ResetRuntimeSettings(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;

    int errorCode = DLR_ResetRuntimeSettings(self->hRecognizer);

    return Py_BuildValue("i", errorCode);
}

static PyObject * SetModeArgument(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;
    char * pModesName;
    int index;
    char * pArgumentName;
    char * pArgumentValue;
    if (!PyArg_ParseTuple(args, "siss", &pModesName, &index, &pArgumentName, &pArgumentValue))
    {
		Py_RETURN_NONE;
    }
    char szErrorMsgBuffer[256];
    int errorCode = DLR_SetModeArgument(self->hRecognizer, pModesName, index, pArgumentName, pArgumentValue, szErrorMsgBuffer, 256);
    return Py_BuildValue("(i,s)", errorCode, szErrorMsgBuffer);
}

static PyObject * GetModeArgument(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;
    char * pModesName;
    int index;
    char * pArgumentName;
    if (!PyArg_ParseTuple(args, "sis", &pModesName, &index, &pArgumentName))
    {
		Py_RETURN_NONE;
    }
    char szErrorMsgBuffer[256];
    char pArgumentValue[512];
    int errorCode = DLR_GetModeArgument(self->hRecognizer, pModesName, index, pArgumentName, pArgumentValue, 512, szErrorMsgBuffer, 256);
    if(errorCode != 0)
    {
		return Py_BuildValue("(i,s)", errorCode, szErrorMsgBuffer);
    }
    else
    {
		return Py_BuildValue("s", pArgumentValue);
    }
}

static PyObject * ClearAppendedSettings(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;

    int errorCode = DLR_ClearAppendedSettings(self->hRecognizer);

    const char* errorString = DLR_GetErrorString(errorCode);

    return Py_BuildValue("(i,s)", errorCode, errorString);
}

static PyObject * AppendSettingsFromString(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;
    char * pTemplateStr = NULL;

    if(!PyArg_ParseTuple(args, "s", &pTemplateStr))
    {
        Py_RETURN_NONE;
    }

    char errorMsg[512];

    int errorCode = DLR_AppendSettingsFromString(self->hRecognizer, pTemplateStr, errorMsg, 512);
    return Py_BuildValue("(i,s)", errorCode, errorMsg);
}

static PyObject * AppendSettingsFromFile(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;
    char * pFilePath = NULL;

    if(!PyArg_ParseTuple(args, "s", &pFilePath))
    {
        Py_RETURN_NONE;
    }

    char errorMsg[512];

    int errorCode = DLR_AppendSettingsFromFile(self->hRecognizer, pFilePath, errorMsg, 512);
    return Py_BuildValue("(i,s)", errorCode, errorMsg);
}

static PyObject * OutputSettingsToFile(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;

    char * pFilePath = NULL;
    char * pTemplateName = NULL;

    if (!PyArg_ParseTuple(args, "ss", &pFilePath, &pTemplateName))
    {
		Py_RETURN_NONE;
    }

    int ret = DLR_OutputSettingsToFile(self->hRecognizer, pFilePath, pTemplateName);
    const char* errorString = DLR_GetErrorString(ret);

    return Py_BuildValue("(i,s)", ret, errorString);
}

static PyObject * RecognizeByBuffer(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;

    PyObject * pyImageData;
    char * pTemplateName = NULL;

    if(!PyArg_ParseTuple(args, "Os", &pyImageData, pTemplateName))
    {
        Py_RETURN_NONE;        
    }

    DLRImageData * pImageData = CreateCDLRImageData(pyImageData);

    int ret = DLR_RecognizeByBuffer(self->hRecognizer, pImageData, pTemplateName);

    InnerFreeCDLRImageData(&pImageData);

    const char* errorString = DLR_GetErrorString(ret);

    return Py_BuildValue("(i,s)",  ret, errorString);
}

static PyObject * RecognizeByFile(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;

    char * pFilePath = NULL;
    char * pTemplateName = NULL;

    if(!PyArg_ParseTuple(args, "ss", &pFilePath, &pTemplateName))
    {
        Py_RETURN_NONE;
    }

    int ret = DLR_RecognizeByFile(self->hRecognizer, pFilePath, pTemplateName);

    const char* errorString = DLR_GetErrorString(ret);

    return Py_BuildValue("(i,s)", ret, errorString);
}

static PyObject * GetAllDLRResults(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;

    DLRResultArray * pResultArray = NULL;

    int ret = DLR_GetAllDLRResults(self->hRecognizer, &pResultArray);

    if (pResultArray == NULL || pResultArray->resultsCount == 0)
	{
		Py_RETURN_NONE;
	}
    else
    {
        PyObject * pyResultList = CreatePyDLRResults(pResultArray);
        DLR_FreeDLRResults(&pResultArray);
        if(pyResultList == NULL)
		{
			Py_RETURN_NONE;
		}
		else
		{
			return pyResultList;
		}
    }
    Py_RETURN_NONE;
}

static PyObject * UpdateReferenceRegionFromBarcodeResults(PyObject *obj, PyObject *args)
{
    DLRObject* self = (DLRObject*)obj;

    PyObject * pyBarcodeResults;
    char * pTemplateName = NULL;

    if(!PyArg_ParseTuple(args, "Os", &pyBarcodeResults, &pTemplateName))
    {
        Py_RETURN_NONE;
    }
    TextResultArray * pBarcodeResults = CreateCTextResultArray(pyBarcodeResults);
    int ret = DLR_UpdateReferenceRegionFromBarcodeResults(self->hRecognizer, pBarcodeResults, pTemplateName);

    InnerFreeCTextResultArray(&pBarcodeResults);

    const char* errorString = DLR_GetErrorString(ret);

    return Py_BuildValue("(i,s)", ret, errorString);
}

//Init
static PyObject * DLR_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    DLRObject* self;

    self = (DLRObject*)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->hRecognizer = NULL;
    }

    return (PyObject *)self;
}

static int DLR_init(DLRObject* self, PyObject *args, PyObject *kwds)
{
    return 0;
}

//Free
static void FreeDLR(DLRObject* self)
{
    if(self->hRecognizer != NULL)
        DLR_DestroyInstance(self->hRecognizer);
    self->hRecognizer = NULL;
}

//module destructer
static void DLR_dealloc(DLRObject* self)
{
    FreeDLR(self);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyMemberDef DLR_members[] = {
    {NULL}
};

//Register methods, all export methods should be in this list.
static PyMethodDef DLR_methods[] =
{
{"CreateInstance", CreateInstance, METH_VARARGS, NULL},
{"DestoryInstance", DestoryInstance, METH_VARARGS, NULL},
{"GetDLRVersion", GetDLRVersion, METH_VARARGS, NULL},
{"GetErrorString", GetErrorString, METH_VARARGS, NULL},
{"InitLicense", InitLicense, METH_VARARGS, NULL},
{"InitLicenseFromLTS", InitLicenseFromLTS, METH_VARARGS, NULL},
{"InitLTSConnectionParameters", InitLTSConnectionParameters, METH_VARARGS, NULL},
{"GetRuntimeSettings", GetRuntimeSettings, METH_VARARGS, NULL},
{"UpdateRuntimeSettings", UpdateRuntimeSettings, METH_VARARGS, NULL},
{"ResetRuntimeSettings", ResetRuntimeSettings, METH_VARARGS, NULL},
{"SetModeArgument", SetModeArgument, METH_VARARGS, NULL},
{"GetModeArgument", GetModeArgument, METH_VARARGS, NULL},
{"ClearAppendedSettings", ClearAppendedSettings, METH_VARARGS, NULL},
{"AppendSettingsFromString", AppendSettingsFromString, METH_VARARGS, NULL},
{"AppendSettingsFromFile", AppendSettingsFromFile, METH_VARARGS, NULL},
{"OutputSettingsToFile", OutputSettingsToFile, METH_VARARGS, NULL},
{"RecognizeByBuffer", RecognizeByBuffer, METH_VARARGS, NULL},
{"RecognizeByFile", RecognizeByFile, METH_VARARGS, NULL},
{"GetAllDLRResults", GetAllDLRResults, METH_VARARGS, NULL},
{"UpdateReferenceRegionFromBarcodeResults", UpdateReferenceRegionFromBarcodeResults, METH_VARARGS, NULL},
{NULL, NULL, 0, NULL}
};

static PyTypeObject DLRType = 
{
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "dlr.DLR",
    .tp_doc = "Dynamsoft Label Recognition",
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_basicsize = sizeof(DLRObject),
    .tp_new = DLR_new,
    .tp_init = (initproc)DLR_init,
    .tp_methods = DLR_methods,
    .tp_dealloc = (destructor)DLR_dealloc,
    .tp_members = DLR_members,
};

static struct PyModuleDef dlrmodule = 
{
    PyModuleDef_HEAD_INIT,
    .m_name = "dlr",
    .m_doc = "Extension with Dynamsoft Label Recognition.",
    .m_size = -1,
};

//module init
PyMODINIT_FUNC
PyInit_dlr(void)
{
    PyObject *m;
    if(PyType_Ready(&DLRType) < 0)
        return NULL;

    m = PyModule_Create(&dlrmodule);
    if(m == NULL)
        return NULL;        

    Py_INCREF(&DLRType);
    if(PyModule_AddObject(m, "DLR", (PyObject*)&DLRType) < 0)
    {
        Py_DECREF(&DLRType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}