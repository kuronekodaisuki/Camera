//
// Camera.h for Camera enumeration
//

#include <opencv2/highgui/highgui.hpp>

#ifdef _MSC_VER
#include <windows.h>
#include <dshow.h>
#endif

using namespace cv;

typedef bool (*PENUMDEVICE)(void *pItem, char *pDeviceName);

class Camera: public VideoCapture
{
public:
	static int EnumDevices(PENUMDEVICE pCallback, void *pItem);

	/*
		Usage:
		
		// enum callback function 
		static int enumCamera(void* pItem, char *pName)
		{
			printf("%s\n", pName);
			return 0;
		}

		int main()
		{
			int cameraCount;
			cameraCount = Camera::EnumDevices((PENUMDEVICE)&enumCamera, NULL);
		}
	*/
};
