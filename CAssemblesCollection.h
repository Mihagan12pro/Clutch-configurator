#pragma once
#include "CClutchAssemble.h"
#include<vector>
using namespace std;
#define Assembles CAssemblesCollection 
class CAssemblesCollection
{
	private:
		

		static vector<Assemble> m_assemblesCollection;

		CAssemblesCollection();
		~CAssemblesCollection();

	public:
		enum SelectedAssemble {
			CLT_140NM = 0,
			CLT_250NM = 1,
			CLT_355NM = 2
		};
		static void InitializeAssembles();
		static Assemble GetAssemble(SelectedAssemble selected);
		
		
		static vector<Assemble> GetAllAssembled();


};

