#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")
#pragma comment(lib, "netapi32.lib")

#include <vtkAutoInit.h> 

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#include "Dicom.h"

using namespace std;

vtkStandardNewMacro(MouseInteractorStyle);

int main() {
	Dicom dicom("F:/Datasets/CT_face/guoyidan");
	dicom.show();
	return 0;
}
