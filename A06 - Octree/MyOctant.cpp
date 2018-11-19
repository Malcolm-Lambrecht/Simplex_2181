#include "MyOctant.h"
using namespace Simplex;
static uint m_uOctantCount;
//  MyOctant
void MyOctant::Init(void)
{
	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();
	//IsColliding();
	
	for (uint i = 0; i < 8; i++)
	{
		m_pChild[i] = nullptr;
	}
}

void MyOctant::SetMyDimensions()
{
	//foreach because it wont be a continuous line of indices, only the things inside the bit
	
}

void MyOctant::setEntityList(std::vector<uint> n)
{
	m_EntityList = n;	
}

MyOctant::MyOctant(std::vector<uint> list, uint mLevel,uint eCount)
{
	Init();
	
	setEntityList(list);
	m_uMaxLevel = mLevel;
	//std::cout << "right constructor: " << m_uMaxLevel << " max levels" << std::endl;
	std::vector<MyEntity*> l_Entity_List = m_pEntityMngr->GetEntityList();
	uint iEntityCount = l_Entity_List.size();
	std::vector<vector3> v3MaxMin_list;
	for (uint i = 0; i < iEntityCount; ++i)
	{
		MyRigidBody* pRG = l_Entity_List[i]->GetRigidBody();
		vector3 v3Min = pRG->GetMinGlobal();
		vector3 v3Max = pRG->GetMaxGlobal();
		v3MaxMin_list.push_back(v3Min);
		v3MaxMin_list.push_back(v3Max);
	}

	m_pRigidBody = new MyRigidBody(v3MaxMin_list);
	m_pRigidBody->MakeCubic();
	m_uID = m_uOctantCount;
	Subdivide();
}

MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
{
	Init();
	
	std::vector<vector3> v3MaxMin_list;
	v3MaxMin_list.push_back(a_v3Center - vector3(a_fSize));
	v3MaxMin_list.push_back(a_v3Center + vector3(a_fSize));
	m_pRigidBody = new MyRigidBody(v3MaxMin_list);
	m_uOctantCount++;
	m_uID = m_uOctantCount; 	
}

void MyOctant::Subdivide()
{
	//check for number of objects in the division to return
	if (m_uLevel >= m_uMaxLevel || m_EntityList.size() < m_uIdealEntityCount) {
		//call something that adds dimensions here
		//the reasoning here is that if it wont be subdivided it will need to set the dimensions on the objects it contains
		for each (uint u in m_EntityList)
		{
			m_pEntityMngr->AddDimension(u, m_uID);
		}
		return;
	}

	m_uChildren = 8; //has children if its getting subdivided

	vector3 v3Center = m_pRigidBody->GetCenterLocal();
	vector3 v3HalfWidth = m_pRigidBody->GetHalfWidth();
	float fSize = (v3HalfWidth.x) / 2.0f;
	float fCenters = fSize;

	m_pChild[0] = new MyOctant(v3Center + vector3(fCenters, fCenters, fCenters), fSize);
	m_pChild[1] = new MyOctant(v3Center + vector3(-fCenters, fCenters, fCenters), fSize);
	m_pChild[2] = new MyOctant(v3Center + vector3(-fCenters, -fCenters, fCenters), fSize);
	m_pChild[3] = new MyOctant(v3Center + vector3(fCenters, -fCenters, fCenters), fSize);

	m_pChild[4] = new MyOctant(v3Center + vector3(fCenters, fCenters, -fCenters), fSize);
	m_pChild[5] = new MyOctant(v3Center + vector3(-fCenters, fCenters, -fCenters), fSize);
	m_pChild[6] = new MyOctant(v3Center + vector3(-fCenters, -fCenters, -fCenters), fSize);
	m_pChild[7] = new MyOctant(v3Center + vector3(fCenters, -fCenters, -fCenters), fSize);

	//split the m_EntityList between all of the children
	for each (uint index in m_EntityList)
	{
		//std::cout << index << " entity loop thing" << std::endl;
		for (int i = 0; i < 8; i++) 
		{
			//m_pChild[i]->m_pRigidBody->IsColliding(m_pEntityMngr->GetEntity(index)->GetRigidBody())
			if (m_pChild[i]->m_pRigidBody->IsColliding(m_pEntityMngr->GetEntity(index)->GetRigidBody()))//if the thing is colliding with a child add it to that childs list
			{
				m_pChild[i]->m_EntityList.push_back(index);
			}
		}
	}

	//init some stuff on each child, like parent etc.
	for (uint i = 0; i < 8; i++)
	{
		m_pChild[i]->m_uLevel = m_uLevel + 1;
		m_pChild[i]->m_pParent = this;
		m_pChild[i]->m_uMaxLevel = this->m_uMaxLevel;
		m_pChild[i]->Subdivide();
	}
}

void MyOctant::Swap(MyOctant& other)
{
	std::swap(m_EntityList, other.m_EntityList);
	std::swap(m_EntityList, other.m_EntityList);
}
void MyOctant::Release(void) //BEEF THIS UP
{
	if (m_uChildren > 0) {
		for (int i = 0; i < m_uChildren; i++) {
			if (m_pChild[i]) {
				SafeDelete(m_pChild[i]);
			}
		}
	}
	m_EntityList.clear();
}
void Simplex::MyOctant::ToggleDisplay(void)
{
	m_bDisplay = !m_bDisplay;
}
void Simplex::MyOctant::ToggleDisplay(bool state)
{
	m_bDisplay = state;
}
void Simplex::MyOctant::Display(void)
{
	if (!m_bDisplay) { return; } //dont display if its turned off
	if (m_uChildren > 0) { 
		for (uint i = 0; i < 8; i++)
		{
			if (m_pChild[i])
				m_pChild[i]->Display();
		}	
	}
	else {
		m_pRigidBody->AddToRenderList();
	}//dont display if has children, prevents wierd overlapping
	
	
	//m_pMeshMngr->AddWireCubeToRenderList(glm::scale(vector3(70)), C_BLUE);
}
void Simplex::MyOctant::IsColliding(void)
{
	std::vector<MyEntity*> l_Entity_List = m_pEntityMngr->GetEntityList();
	uint iEntityCount = l_Entity_List.size();
	for (uint i = 0; i < iEntityCount; ++i)
	{
		MyRigidBody* pRB = l_Entity_List[i]->GetRigidBody();
		if (pRB->IsColliding(m_pRigidBody))
		{
			l_Entity_List[i]->AddDimension(m_uID);
		}
	}
}
MyOctant::MyOctant(MyOctant const& other)
{
	m_EntityList = other.m_EntityList;
	m_EntityList = other.m_EntityList;
}
MyOctant& MyOctant::operator=(MyOctant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
MyOctant::~MyOctant() { Release(); };
//Accessors
//--- Non Standard Singleton Methods

