//
// Camera enumerate
//

#include "Camera.h"

#ifdef _MSC_VER
#pragma comment(lib, "strmiids.lib")

#ifndef SAFE_RELEASE
#define SAFE_RELEASE( p ) if(p)p->Release()
#endif

int Camera::EnumDevices(PENUMDEVICE pCallback, void* pItem)
{
	int nDevice = 0;
	HRESULT			hr				= S_OK;

	// System device enumerators
	ICreateDevEnum	*pDevEnum		= NULL;
	IEnumMoniker	*pEnum			= NULL;
	IMoniker		*pMoniker		= NULL;

	CoInitialize(NULL);

	// Create system device enumerator
	hr = CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, reinterpret_cast<void**>(&pDevEnum) );
	if (FAILED(hr)) {
		return 0;
	}

	// create enumerator for video capture devices
	hr = pDevEnum->CreateClassEnumerator( CLSID_VideoInputDeviceCategory, &pEnum, 0 );
	if (SUCCEEDED(hr)) 
	{
		IBindCtx* pbcfull = NULL;

		// Enumerate through the devices and print friendly name
		while ( (pEnum->Next( 1, &pMoniker, NULL ) == S_OK))
		{	
			VARIANT var;
			IPropertyBag *pPropertyBag;
			char szCameraName[200];

			// FrienlyName : The name of the device
			var.vt = VT_BSTR;

			// Bind to IPropertyBag
			pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropertyBag);
			
			// Reference: https://msdn.microsoft.com/en-us/library/windows/desktop/dd377566(v=vs.85).aspx
			hr = pPropertyBag->Read(L"Description", &var, 0);	// "FriendlyName", "DevicePath", "Description"
			if (FAILED(hr))
			{
				pPropertyBag->Read(L"FriendlyName", &var, 0);
			}
			WideCharToMultiByte(CP_ACP, 0, var.bstrVal, -1,szCameraName, sizeof(szCameraName), 0, 0);
			if (pCallback != NULL) {
				(*pCallback)(pItem, szCameraName);
			}
			VariantClear(&var);

			// Release resource
			pPropertyBag->Release();

			nDevice++;

			SAFE_RELEASE( pMoniker );
		}
	}
	return nDevice; // returns count of camera
}
#else	// Other plathome 
int Camera::EnumDevices(PENUMDEVICE pCallback, void* pItem)
{
	int nDevice = 0;
	returnnDevice;
}
#endif
