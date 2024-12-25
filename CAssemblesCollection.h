#pragma once
#include "CClutchAssemble.h"
#include<vector>
using namespace std;
class CAssemblesCollection
{
	private:
		

		static vector<Assemble> m_assemblesCollection;

		CAssemblesCollection();
		~CAssemblesCollection();

	public:
		enum SelectedAssemble {
			CLT_140NM = 0,
			CLT_150NM = 1
		};
		static void InitializeAssembles();
		static Assemble GetAssemble(SelectedAssemble selected);
		



};

