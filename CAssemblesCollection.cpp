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

	/*Assemble clutch_140NM(38, 45, 10, 1, 34, 16, 1, 6, 1, 20, 2, 0.2, 0.3);
	Assemble clutch_250NM(42, 50, 12, 1.2, 37, 18, 1, 6, 1, 25, 2.25, 0.2, 0.3);*/




	Assemble clutch_140NM;
	Assemble clutch_250NM;
	Assemble clutch_355NM;

	
	

	
	m_assemblesCollection.push_back(clutch_140NM);
	m_assemblesCollection.push_back(clutch_250NM);
	m_assemblesCollection.push_back(clutch_355NM);
}

Assemble CAssemblesCollection::GetAssemble(SelectedAssemble selected)
{
	return m_assemblesCollection[selected];
}

vector<Assemble> CAssemblesCollection:: m_assemblesCollection;