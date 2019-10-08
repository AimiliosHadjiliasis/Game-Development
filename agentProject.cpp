// agentProject.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <iostream>
using namespace tle;

#define idle 0
#define alert 1
#define dead 2

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

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media

	myEngine->AddMediaFolder( "C:\\Program Files (x86)\\TL-Engine\\Media" );
	//myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder("./media");

	/**** Set up your scene here ****/
	ICamera* camera = myEngine->CreateCamera(kFPS, 0, 35, -60);
	camera->RotateLocalX(20);

	//Floor
	IMesh* mfloor = myEngine->LoadMesh("floor.x");
	IModel* floor = mfloor->CreateModel();

	//Guards:
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

	//State:
	IMesh* mState = myEngine->LoadMesh("state.x");
	IModel* state = mState->CreateModel(0, 5, 0);
	state->Scale(2);
	state->AttachToParent(guard);

	
	float dotProduct;



	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		//------------------------------------------------------//
		//  Varriable that used for the movement of the Models  //
		//------------------------------------------------------//

		float dt = myEngine->Timer();
		float thiefVelocity = 10;
		float thiefStep = thiefVelocity * dt;
		float thiefSteeringVelocity = 200;
		float thiefSteeringStep = thiefSteeringVelocity * dt;
		float guardVelocity = 8;
		float guardStep = guardVelocity * dt;

		//find and calculatethe angles to see if the thief is behind the guard
		calculations(thief, guard, x, y, z, dotProduct);

		//Movement controls of the thief
		thiefMovement(myEngine, thief, thiefStep, thiefSteeringStep);


		switch (guardState)
		{
			case idle:
			{
				state->SetSkin("blue.png");
				guard->ResetOrientation();

				if (sphereToSpereCollisionDetection( thief, guard ,  8, 8) && dotProduct >= 0)
				{
					guardState = alert;
				}

				if (sphereToSpereCollisionDetection(thief, guard, 1, 1))
				{
					guardState = dead;
				}

				break;
			}

			case alert:
			{	
				
				guard->LookAt(thief);
				guard->Scale(4);
				state->SetSkin("red.png");

				guardFollowing(thief, guard, guardStep);


				//Change state:
				//(1) IDLE state if the guard is 12 units away from the thief
				if (!sphereToSpereCollisionDetection(thief, guard, 24, 24))
				{
					guardState = idle;
				}
				//(2) DEAD state if the thief touch the guard
				if (sphereToSpereCollisionDetection(thief, guard, 1, 1))
				{
					guardState = dead;
				}

				break;
			}

			case dead:
			{
				state->SetSkin("purple.png");
				break;
			}
			
			default:
				break;
		}


		//TODO: Make the guard patrol on 3 or more points
		switch (guardPatrollingState)
		{

			case 0:
			{
				guard->MoveZ(0.005);

				if (guard->GetLocalZ() >= 50)
				{
					guardPatrollingState = 1;
				}
				break;
			}
			case 1:
			{	
				
				guard->MoveX(-0.005);
				guard->RotateY(-90);


				if (guard->GetLocalX() <= -50)
				{
					guardPatrollingState = 2;
				}
				break;
			}
			case 2:
			{	

				guard->MoveZ(-0.05);
				guard->RotateLocalY(180);

				if (guard->GetLocalZ() <= 0)
				{
					guardPatrollingState = 3;
				}

				break;
			}
			case 3:
			{

				break;
			}
		default:
			break;
		}

		//Game Keys:
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
