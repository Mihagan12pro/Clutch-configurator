#pragma once
#include "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\Include\ksConstants.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\Include\ksConstants3D.h"
#import "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\lib\kAPI5.tlb"
#include<string>
#include"CClutchAssemble.h"


using namespace Kompas6API5;


#define MAIN_LINE  1
#define HATCH_LINE 3

#define XOZ o3d_planeXOZ
#define ZOX o3d_planeXOZ

#define XOY o3d_planeXOY
#define YOX o3d_planeXOY

#define YOZ o3d_planeYOZ
#define ZOY o3d_planeYOZ


#define COLLAR_HOLE_FOR_SCREW "HoleForScrew"
#define SCREW_BODY "ScrewBody"


class CClutchAssembler
{

	public:
		void BuildAssemble();
		CClutchAssembler(Assemble assemble);
	protected:
		KompasObjectPtr m_pKompasApp5;
		

		ksPartPtr m_pPart;
		ksDocument3DPtr m_pDoc3D;
		ksDocument2DPtr m_pDoc2D;

		int n1, n2;


		double D, L, l, b1, D1, d, c, d1, c1, D2, b, r, f;


		void CreateCollar();//Создание втулки
		void CreateRing();//Создание кольца
		void CreateScrew();//Создание винта

		void DoAssemble();
	private:
		static _bstr_t m_saveFolder;
		static _bstr_t m_collarName;
		static _bstr_t m_ringName;
		static _bstr_t m_screwName;
public:
	 static void SetFolderName(const char*save);
	 static void SetCollarName(const char* name);
	 static void SetRingName(const char* name);
	 static void SetScrewName(const char* name);

	 static CString GetFolderName();
	 static CString GetCollarName();
	 static CString GetRingName();
	 static CString GetScrewName();
};

