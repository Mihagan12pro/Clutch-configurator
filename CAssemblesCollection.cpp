#include "pch.h"
#include "CAssemblesCollection.h"


CAssemblesCollection::CAssemblesCollection()
{
	delete this;
}
CAssemblesCollection::~CAssemblesCollection()
{

}

void CAssemblesCollection::InitializeAssembles()
{
	m_assemblesCollection.clear();

	




	Assemble clutch_140NM(L"140NM");
	clutch_140NM.D = 38;
	clutch_140NM.D1 = 34;
	clutch_140NM.b1 = 1;
	clutch_140NM.d1 = 6;
	clutch_140NM.L = 45;
	clutch_140NM.l = 10;
	clutch_140NM.r = 0.2;
	clutch_140NM.f = 0.3;
	clutch_140NM.c = 1;
	clutch_140NM.c1 = 1;
	clutch_140NM.m_gosts1193Top = CGOST1139(6,16,20,4,L"6x16x20x4");
	clutch_140NM.m_gosts1193Bottom = CGOST1139(6,18,22,6, L"6x18x22x6");
	

	Assemble clutch_250NM(L"250NM");
	clutch_250NM.D = 42;
	clutch_250NM.D1 = 37;
	clutch_250NM.b1 = 1.2;
	clutch_250NM.d1 = 6;
	clutch_250NM.L = 50;
	clutch_250NM.l = 12;
	clutch_250NM.r = 0.2;
	clutch_250NM.f = 0.3;
	clutch_250NM.c = 1;
	clutch_250NM.c1 = 1;
	clutch_250NM.m_gosts1193Top = CGOST1139(6,21,25,5,L"6x21x25x5");
	clutch_250NM.m_gosts1193Bottom = CGOST1139(6,23,28,6,L"6x23x28x6");
	



	Assemble clutch_355NM(L"355NM");
	clutch_355NM.D = 48;
	clutch_355NM.D1 = 43;
	clutch_355NM.b1 = 1.2;
	clutch_355NM.d1 = 6;
	clutch_355NM.L = 55;
	clutch_355NM.l = 12;
	clutch_355NM.r = 0.3;
	clutch_355NM.f = 0.4;
	clutch_355NM.c = 1;
	clutch_355NM.c1 = 1;
	clutch_355NM.m_gosts1193Top = CGOST1139(6,23,28,6,L"6x23x28x6");
	clutch_355NM.m_gosts1193Bottom = CGOST1139(6,26,32,6,L"6x23x32x6");
	
	

	
	m_assemblesCollection.push_back(clutch_140NM);
	m_assemblesCollection.push_back(clutch_250NM);
	m_assemblesCollection.push_back(clutch_355NM);
}

Assemble CAssemblesCollection::GetAssemble(SelectedAssemble selected)
{
	return m_assemblesCollection[selected];
}
vector<Assemble> CAssemblesCollection::GetAllAssembles()
{
	return m_assemblesCollection;
}

vector<Assemble> CAssemblesCollection:: m_assemblesCollection;