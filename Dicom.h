#pragma once

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDICOMImageReader.h>
#include <vtkVolume16Reader.h>
#include <vtkMarchingCubes.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcistrmf.h>

#include "MouseInteractorStyle.h"
#include "Utils.h"

class Dicom {
public:
	Dicom();
	Dicom(std::string path);
	~Dicom();

	void show();

private:
	std::string dicom_folder;
	int series_id;
};
