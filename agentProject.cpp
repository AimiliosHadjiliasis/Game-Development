// agentProject.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
using namespace tle;

// Definitions for guard state:
#define idle 0
#define alert 1
#define dead 2
#define win 3

// Definitions for the guard movement state:
#define up 0
#define left 1
#define down 2
#define leftTwo 3
#define downTwo 4
#define rightTwo 5

// Definitions for the guard speed:
#define creep 0
#define walk 1
#define run 2

void speedOfThief(I3DEngine* myEngine, int& thiefSpeed, float& thiefVelocity)
{
	switch (thiefSpeed)
	{
	case creep:
	{
		thiefVelocity = 2;

		//Change State:
		if (myEngine->KeyHit(Key_1))
		{
			thiefSpeed = walk;
		}
		if (myEngine->KeyHit(Key_2))
		{
			thiefSpeed = run;
		}
		break;
	}
	case walk:
	{
		thiefVelocity = 5;

		//Change State:
		if (myEngine->KeyHit(Key_0))
		{
			thiefSpeed = creep;
		}
		if (myEngine->KeyHit(Key_2))
		{
			thiefSpeed = run;
		}
		break;
	}
	case run:
	{
		thiefVelocity = 10;

		//Change State:
		if (myEngine->KeyHit(Key_0))
		{
			thiefSpeed = creep;
		}
		if (myEngine->KeyHit(Key_1))
		{
			thiefSpeed = walk;
		}
		break;
	}
	default:
		break;
	}
}
void thiefMovement(I3DEngine* myEngine, IModel* thief, float& thiefStep, float& thiefSteeringStep)
{
	//Thief controls:
	//Frontwords:
	if (myEngine->KeyHeld(Key_W))
	{
		thief->MoveLocalZ(thiefStep);
	}
	//Backwords:
	if (myEngine->KeyHeld(Key_S))
	{
		thief->MoveLocalZ(-thiefStep);
	}

	//Steering:
	//(1) Leftwords:
	if (myEngine->KeyHeld(Key_A))
	{
		thief->RotateY(-thiefSteeringStep);
	}
	//(2) Rightwords:
	if (myEngine->KeyHeld(Key_D))
	{
		thief->RotateY(thiefSteeringStep);
	}
}
void calculations(IModel* thief, IModel* guard, float &x, float &y, float &z, float &dotProduct)
{
	//Calculate facing vector (orientation) of the guard
	float matrix[16];
	guard->GetMatrix(matrix);
	x = matrix[8];
	y = matrix[9];
	z = matrix[10];


	//Calculate the vector from the guard to the player:
	float thiefX = thief->GetLocalX();
	float thiefY = thief->GetLocalY();
	float thiefZ = thief->GetLocalZ();

	float guardX = guard->GetLocalX();
	float guardY = guard->GetLocalY();
	float guardZ = guard->GetLocalZ();

	float dx = thiefX - guardX;
	float dy = thiefY - guardY;
	float dz = thiefZ - guardZ;

	float vecThiefAndGuard = sqrt((dx*dx) + (dy*dy) + (dz*dz));

	//Calculate dot product: (of guards facing vector and the vector between the guard and the thief)
	dotProduct = (dx*x + dy * y + dz * z);
	//cout << dotProduct << endl;
}
bool sphereToSpereCollisionDetection(IModel* Model1, IModel* Model2, float RadiusOne, float RadiusTwo)
{
	/*
	Gennerally this is the collision function that
	checks and return true or false idepence if a collision happens.
	This collision function checks the collision between
	the hover and all the objects in the map.
	*/

	bool collision = false;
	//location of model1
	float p1x = Model1->GetX();
	float p1y = Model1->GetY();
	float p1z = Model1->GetZ();

	//location of model2
	float p2x = Model2->GetX();
	float p2y = Model2->GetY();
	float p2z = Model2->GetZ();

	//distance model1 and model2
	float dx = p1x - p2x;
	float dy = p1y - p2y;
	float dz = p1z - p2z;
	float collisionDistance = sqrt(dx*dx + dy * dy + dz * dz);

	if (collisionDistance <= (RadiusOne + RadiusTwo)) {
		collision = true;
	}
	return collision;
}
void guardFollowing(IModel* thief, IModel* guard, float& guardStep)
{
	float thiefCurrentX = thief->GetLocalX();
	float thiefCurrentY = thief->GetLocalY();
	float thiefCurrentZ = thief->GetLocalZ();
	//Make the guard follow the thief
	//(1) The guard follow the thief on Z-axis
	if (guard->GetLocalZ() <= thiefCurrentZ)
	{
		guard->MoveZ(guardStep);
	}
	if (guard->GetLocalZ() >= thiefCurrentZ)
	{
		guard->MoveZ(-guardStep);
	}
	//(2) The guard follow the thief on x-axis
	if (guard->GetLocalX() <= thiefCurrentX)
	{
		guard->MoveX(guardStep);
	}
	if (guard->GetLocalX() >= thiefCurrentX)
	{
		guard->MoveX(-guardStep);
	}
}
void gameKeys(I3DEngine * myEngine, IModel* guard, int& guardState, int& guardPatrollingState, IModel* thief,IModel* state)
{
	//	Game Keys:
	//----------------------
	//(1) Game Reset:
	if (myEngine->KeyHit(Key_R))
	{
		guard->SetPosition(0, 0, 0);
		guard->ResetOrientation();
		guardState = idle;
		guardPatrollingState = up;
		thief->ResetOrientation();
		thief->SetPosition(40, 0, 0);
		state->SetSkin("blue.png");
	}

	//(2) Exit Game:
	if (myEngine->KeyHit(Key_Escape))
	{
		myEngine->Stop();
	}
}
void patrolling(int& guardPatrollingState, IModel* guard, float& guardStep)
{
	switch (guardPatrollingState)
	{
	case up:
	{
		guard->MoveZ(guardStep);

		if (guard->GetLocalZ() >= 50)
		{
			guardPatrollingState = left;
		}
		break;
	}
	case left:
	{
		guard->MoveX(-guardStep);
		guard->RotateY(-90);

		if (guard->GetLocalX() <= -50)
		{
			guardPatrollingState = down;
		}
		break;
	}
	case down:
	{
		guard->MoveZ(-guardStep);
		guard->RotateLocalY(180);

		if (guard->GetLocalZ() <= 0)
		{
			guardPatrollingState = leftTwo;
		}

		break;
	}
	case leftTwo:
	{
		guard->MoveX(-guardStep);
		guard->RotateLocalY(-90);

		if (guard->GetLocalX() <= -100)
		{
			guardPatrollingState = downTwo;
		}
		break;
	}
	case downTwo:
	{
		guard->MoveZ(-guardStep);
		guard->RotateLocalY(180);

		if (guard->GetLocalZ() <= -50)
		{
			guardPatrollingState = rightTwo;
		}
		break;
	}
	case rightTwo:
	{
		guard->MoveX(guardStep);
		guard->RotateLocalY(90);

		if (guard->GetLocalX() >= 0)
		{
			guardPatrollingState = up;
		}

		break;
	}
	default:
		break;
	}
}
void idleUpdate(int& guardPatrollingState, IModel* guard, float guardStep)
{
	patrolling(guardPatrollingState, guard, guardStep);
	guard->ResetOrientation();

}
void idleTransition(int& thiefSpeed, IModel* thief, IModel* guard, float radiusToLocate, float dotProduct, 
	int& guardState, float radiusToLocateIfThiefRuns, IModel* square[], int radiusToDie, IModel* state)
{
	if (thiefSpeed != creep)
	{
		//Change state to alert if the guard is close to the thief:
		if (sphereToSpereCollisionDetection(thief, guard, radiusToLocate, radiusToLocate) && dotProduct >= 0)
		{	
			state->SetSkin("red.png");
			guardState = alert;
		}

		//Change state to alert if the guard is close to the thief:
		//(But the thief is running)
		if (thiefSpeed = run)
		{
			if (sphereToSpereCollisionDetection(thief, guard, radiusToLocateIfThiefRuns, radiusToLocateIfThiefRuns) && dotProduct >= 0)
			{	
				state->SetSkin("red.png");
				guardState = alert;
			}
		}

		//Change state to alert if the guard is in the noizy area:
		for (int i = 0; i < 4; i++)
		{
			if (sphereToSpereCollisionDetection(thief, square[i], 4, 4)
				&& sphereToSpereCollisionDetection(square[i], guard, 15, 15) && dotProduct >= 0)
			{
				guardState = alert;
			}
		}
	}


	//Change state if the thief touch the guard:
	if (sphereToSpereCollisionDetection(thief, guard, radiusToDie, radiusToDie))
	{
		guardState = dead;
	}
}
void alertUpdate(IModel* thief, IModel* guard, float guardStep)
{
	guardFollowing(thief, guard, guardStep);
	guard->LookAt(thief);
	guard->Scale(4);
}
void alertTransition(IModel* thief, IModel* guard, int radiusToLeave, IModel* state, int& guardState, 
	int radiusToDie, float dotProduct)
{
	//Change state:
	//(1) IDLE state if the guard is 12 units away from the thief
	if (!sphereToSpereCollisionDetection(thief, guard, radiusToLeave, radiusToLeave))
	{
		state->SetSkin("blue.png");
		guardState = idle;
	}
	//(2) DEAD state if the thief touch the guard
	if (sphereToSpereCollisionDetection(thief, guard, radiusToDie, radiusToDie))
	{
		state->SetSkin("purple.png");
		guardState = dead;
	}
	//(3) WIN state if the thief touch the guard
	if (sphereToSpereCollisionDetection(thief, guard, radiusToDie, radiusToDie) && dotProduct >= 0)
	{
		state->SetSkin("violet.png");
		guardState = win;
	}


}
void stateOfTheGuard(int& guardState, IModel* thief, IModel* guard, int radiusToLeave, IModel* state, 
	int radiusToDie, float dotProduct, int& guardPatrollingState, float guardStep, int& thiefSpeed, int radiusToLocate,
	int radiusToLocateIfThiefRuns, IModel* square[])
{

	switch (guardState)
	{
	case idle:
	{
		idleUpdate(guardPatrollingState, guard, guardStep);
		idleTransition(thiefSpeed, thief, guard, radiusToLocate, dotProduct, guardState, radiusToLocateIfThiefRuns, square, radiusToDie, state);
		break;
	}

	case alert:
	{
		alertUpdate(thief, guard, guardStep);
		alertTransition(thief, guard, radiusToLeave, state, guardState, radiusToDie, dotProduct);
		break;
	}

	case dead:
	{

		break;
	}

	case win:
	{

		break;
	}
	default:
		break;
	}


}
void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	//Folders for meshes and models:
	//myEngine->AddMediaFolder("C:\\Program Files (x86)\\TL-Engine\\Media");
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder(".\\models");


	//--------------------------------------------------------//
	//                Code that executed once                 //
	//--------------------------------------------------------//

	//Camera:
	ICamera* camera = myEngine->CreateCamera(kManual, 0 , 10 ,-20);
	camera->RotateLocalX(20);

	//Floor:
	IMesh* mfloor = myEngine->LoadMesh("floor.x");
	IModel* floor = mfloor->CreateModel(0, -0.1f, 0);

	//Squares(Areas):
	IMesh* msquare = myEngine->LoadMesh("Square.x");
	IModel* square[4];
	square[0] = msquare->CreateModel(20, -5, 20);
	square[1] = msquare->CreateModel(20, -5, 0);
	square[2] = msquare->CreateModel(20, -5, 10);
	square[3] = msquare->CreateModel(20, -5, -5);

	//Set skin for the boxes and rotate them so they are visible:
	for (int i = 0; i < 4; i++)
	{
		square[i]->SetSkin("red.png");
		square[i]->RotateX(90);
	}

	//Guard:
	IMesh* mGuard = myEngine->LoadMesh("casual_A.x");
	IModel* guard = mGuard->CreateModel();
	guard->Scale(4);
	float x;
	float y;
	float z;
	int guardState = 0;
	int guardPatrollingState = 0;
	

	//Thief:
	IMesh* mThief = myEngine->LoadMesh("sierra.x");
	IModel* thief = mThief->CreateModel(40, 0, 0);
	thief->Scale(4);
	int thiefSpeed = walk;
	float thiefVelocity;
	camera->AttachToParent(thief);
	//State:
	IMesh* mState = myEngine->LoadMesh("state.x");
	IModel* state = mState->CreateModel(0, 5, 0);
	state->Scale(2);
	state->AttachToParent(guard);
	state->SetSkin("blue.png");

	//Grid ( help for locating things )
	//IMesh* mGrid = myEngine->LoadMesh("grid.x");
	//IModel* grid = mGrid->CreateModel();

	float dotProduct;
	float radiusToLeave = 24.0;
	float radiusToDie = 1.0;
	float radiusToLocate = 5;
	float radiusToLocateIfThiefRuns = 15;


	//-----------------------------------------------------//
	//            Code that executed every frame           //
	//-----------------------------------------------------//
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		//Function that determines what is the speed of velocity of the guard:
		speedOfThief(myEngine, thiefSpeed, thiefVelocity);

		//------------------------------------------------------//
		//  Varriable that used for the movement of the Models  //
		//------------------------------------------------------//
		float dt = myEngine->Timer();
		float thiefStep = thiefVelocity * dt;
		float thiefSteeringVelocity = 200;
		float thiefSteeringStep = thiefSteeringVelocity * dt;
		float guardVelocity = 15;
		float guardStep = guardVelocity * dt;

		//Find and calculatethe angles to see if the thief is behind the guard:
		calculations(thief, guard, x, y, z, dotProduct);

		//Movement controls of the thief:
		thiefMovement(myEngine, thief, thiefStep, thiefSteeringStep);

		//Contol the state of the guard
		stateOfTheGuard(guardState, thief, guard, radiusToLeave, state, radiusToDie, dotProduct, guardPatrollingState, 
			guardStep, thiefSpeed, radiusToLocate,radiusToLocateIfThiefRuns, square);

		//Key Controls of the game:
		gameKeys(myEngine, guard, guardState, guardPatrollingState, thief, state);
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
