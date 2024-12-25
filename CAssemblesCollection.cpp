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

	Assemble clutch_140NM(38, 45, 10, 1, 34, 16, 1, 6, 1, 20, 2, 0.2, 0.3);
	m_assemblesCollection.push_back(clutch_140NM);
}

Assemble CAssemblesCollection::GetAssemble(SelectedAssemble selected)
{
	return m_assemblesCollection[selected];
}

vector<Assemble> CAssemblesCollection:: m_assemblesCollection;