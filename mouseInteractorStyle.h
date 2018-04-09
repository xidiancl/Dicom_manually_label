#pragma once

#include <vtkInteractorStyleTrackballCamera.h>
#include <iostream>

using namespace std;

class MouseInteractorStyle : public vtkInteractorStyleTrackballCamera {
public:
	static MouseInteractorStyle* New();
	vtkTypeMacro(MouseInteractorStyle, vtkInteractorStyleTrackballCamera);

	MouseInteractorStyle() {}
	~MouseInteractorStyle() {}

	virtual void OnLeftButtonDown() {
		down_pos[0] = this->GetInteractor()->GetEventPosition()[0];
		down_pos[1] = this->GetInteractor()->GetEventPosition()[1];
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	}
	virtual void OnLeftButtonUp() {
		up_pos[0] = this->GetInteractor()->GetEventPosition()[0];
		up_pos[1] = this->GetInteractor()->GetEventPosition()[1];
		if (up_pos[0] == down_pos[0] && up_pos[1] == down_pos[1]) {
			cout << "!!!" << endl;
		}
		vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
	}

private:
	int down_pos[2];
	int up_pos[2];
};
