#include "pch.h"
#include "CClutchAssembler.h"
#include<cmath>

CClutchAssembler::CClutchAssembler()
{

}

CClutchAssembler::CClutchAssembler(Assemble assemble, GOST gost)
{
	m_assemble = assemble;
	D  = assemble.GetD();
	L  = assemble.GetL();
	l  = assemble.Getl();
	b1 = assemble.Getb1();
	D1 = assemble.GetD1();
	//d  = assemble.Getd();
	c  = assemble.Getc();
	d1 = assemble.Getd1();
	c1 = assemble.Getc1();
	//D2 = assemble.GetD2();
	//b  = assemble.Getb();
	r  = assemble.Getr();
	f  = assemble.Getf();

	UpdateGOST(gost);

	
}

void CClutchAssembler::BuildAssemble()
{
	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!m_pKompasApp5)
	{
		// �������� CLSID ��� ������
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) 
		{
			m_pKompasApp5 = nullptr;
			return;
		}
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) 
		{
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				m_pKompasApp5 = nullptr;
				return;
			}
		}

		// �������� ��������� ���������� ������
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&m_pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	// ������ ������ �������
	m_pKompasApp5->Visible = true;

	CreateCollar();
	CreateRing();
	CreateScrew();
	DoAssemble();
}

void CClutchAssembler::CreateCollar()
{
	m_pDoc3D = m_pKompasApp5->Document3D();

	m_pDoc3D->Create(false, true);

	m_pPart = m_pDoc3D->GetPart(pTop_Part);


	ksEntityPtr pSketch1 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch1Def = pSketch1->GetDefinition();

	//�������� 1 ������
	pSketch1Def->SetPlane(m_pPart->GetDefaultEntity(XOZ));
	pSketch1->Create();

	m_pDoc2D = pSketch1Def->BeginEdit();


	m_pDoc2D->ksLineSeg(0, 0, 0, D/2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(0, D / 2,L,D/2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(L, D / 2,L,0,MAIN_LINE);
	m_pDoc2D->ksLineSeg(L, 0,0,0,MAIN_LINE);

	m_pDoc2D->ksLineSeg(0, 0, -10, 0, HATCH_LINE);

	pSketch1Def->EndEdit();

	ksEntityPtr pRotate1 = m_pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotate1Def = pRotate1->GetDefinition();

	//������������ ���������
	pRotate1Def->SetSketch(pSketch1);
	pRotate1Def->SetSideParam(TRUE, 360);
	pRotate1->Create();

	//�������� 2 ������
	ksEntityPtr pSketch2 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch2Def = pSketch2->GetDefinition();

	pSketch2Def->SetPlane(m_pPart->GetDefaultEntity(XOZ));
	pSketch2->Create();

	m_pDoc2D = pSketch2Def->BeginEdit();

	m_pDoc2D->ksLineSeg(0, 0, 0, d / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(0, d / 2, L, d / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(L, d / 2, L, 0, MAIN_LINE);
	m_pDoc2D->ksLineSeg(L, 0, 0, 0, MAIN_LINE);

	m_pDoc2D->ksLineSeg(0, 0, -100, 0, HATCH_LINE);

	pSketch2Def->EndEdit();

	//��������� ���������
	ksEntityPtr pCutRotate1 = m_pPart->NewEntity(o3d_cutRotated);
	ksCutRotatedDefinitionPtr pCutRotate1Def = pCutRotate1->GetDefinition();

	pCutRotate1Def->SetSideParam(TRUE, 360);
	pCutRotate1Def->SetSketch(pSketch2);

	pCutRotate1->Create();

	//�������� 3 ������
	ksEntityPtr pSketch3 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch3Def = pSketch3->GetDefinition();
	pSketch3Def->SetPlane(m_pPart->GetDefaultEntity(ZOY));

	pSketch3->Create();

	m_pDoc2D = pSketch3Def->BeginEdit();

	m_pDoc2D->ksLineSeg(-b / 2, 0, -b / 2, D2 / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(-b / 2, D2 / 2, b / 2, D2 / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(b / 2, D2 / 2, b / 2, 0, MAIN_LINE);
	m_pDoc2D->ksLineSeg(-b / 2, 0, b / 2, 0, MAIN_LINE);
	pSketch3Def->EndEdit();

	//��������� ������������� 1
	ksEntityPtr pCutExtrusion1 = m_pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutExtrusion1Def = pCutExtrusion1->GetDefinition();

	pCutExtrusion1Def->SetSketch(pSketch3);
	pCutExtrusion1Def->SetSideParam(true, etThroughAll, 0, 0, false);
	pCutExtrusion1Def->directionType = dtNormal;

	pCutExtrusion1->Create();

	//�������� ����� 1
	ksEntityPtr pChamfer1 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer1Def = pChamfer1->GetDefinition();

	pChamfer1Def->tangent = true;
	pChamfer1Def->SetChamferParam(true, c, c);

	ksEntityCollectionPtr pEdges = m_pPart->EntityCollection(o3d_edge);
	ksEntityCollectionPtr pChamfers = pChamfer1Def->array();
	pChamfers->Clear();

	pEdges->SelectByPoint(0, d / 2, 0);

	pChamfers->Add(pEdges->GetByIndex(0));

	pChamfer1->Create();

	//�������� ����� 2
	ksEntityPtr pChamfer2 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer2Def = pChamfer2->GetDefinition();

	pChamfer2Def->tangent = true;
	pChamfer2Def->SetChamferParam(true, c, c);

	pEdges = m_pPart->EntityCollection(o3d_edge);
	pChamfers = pChamfer2Def->array();
	pChamfers->Clear();

	pEdges->SelectByPoint(L, D / 2, 0);


	pChamfers->Add(pEdges->GetByIndex(0));

	pChamfer2->Create();

	//�������� ����� 3
	ksEntityPtr pChamfer3 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer3Def = pChamfer3->GetDefinition();

	pChamfer3Def->tangent = true;
	pChamfer3Def->SetChamferParam(true, c, c);

	pEdges = m_pPart->EntityCollection(o3d_edge);
	pChamfers = pChamfer3Def->array();
	pChamfers->Clear();

	pEdges->SelectByPoint(L, d / 2, 0);

	pChamfers->Add(pEdges->GetByIndex(0));

	pChamfer3->Create();

	//�������� ����� 4
	ksEntityPtr pChamfer4 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer4Def = pChamfer4->GetDefinition();

	pChamfer4Def->tangent = true;
	pChamfer4Def->SetChamferParam(true, c, c);

	pEdges = m_pPart->EntityCollection(o3d_edge);
	pChamfers = pChamfer4Def->array();
	pChamfers->Clear();

	pEdges->SelectByPoint(0, D / 2, 0);

	pChamfers->Add(pEdges->GetByIndex(0));

	pChamfer4->Create();

	//�������� ����� 5
	ksEntityPtr pChamfer5 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer5Def = pChamfer5->GetDefinition();

	pChamfer5Def->SetChamferParam(true, f, f);
	pEdges = m_pPart->EntityCollection(o3d_edge);
	pChamfers = pChamfer5Def->array();
	pChamfers->Clear();

	for (int i = 0;i < pEdges->GetCount();i++)
	{
		ksEntityPtr ed = pEdges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();

		if (def->GetOwnerEntity() == pCutExtrusion1)
		{
			ksVertexDefinitionPtr vert = def->GetVertex(true);
			double x, y, z;
			vert->GetPoint(&x, &y, &z);
			if (x != 0 && fabs(y) < d / 2)
			{
				pChamfers->Add(ed);
			}
		}

		pChamfer5->Create();
	}
	//�������� ����������
	ksEntityPtr pFillet1 = m_pPart->NewEntity(o3d_fillet);
	ksFilletDefinitionPtr pFillet1Def = pFillet1->GetDefinition();

	pFillet1Def->radius = r;

	ksEntityCollectionPtr pFillets = pFillet1Def->array();
	pFillets->Clear();


	for (int i = 0; i < pEdges->GetCount(); i++)
	{
		ksEntityPtr ed = pEdges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();

		if (def->GetOwnerEntity() == pCutExtrusion1)
		{
			ksVertexDefinitionPtr vert = def->GetVertex(true);
			double x, y, z;
			if (vert != NULL)
			{
				vert->GetPoint(&x, &y, &z);

				if (x >= c && y == -D2/2)
				{
					if (x == L)
					{
						pEdges->SelectByPoint(L - c, y, z);
						pFillets->Add(pEdges->GetByIndex(0));
					}
				}
			}
		}
	}
	pFillet1->Create();

	//���������� ������
	ksEntityPtr pMirrorCopy = m_pPart->NewEntity(o3d_mirrorOperation);
	ksMirrorCopyDefinitionPtr pMirrorCopyDef = pMirrorCopy->GetDefinition();

	pMirrorCopyDef->SetPlane(m_pPart->GetDefaultEntity(XOY));
	
	pEdges = ksEntityCollectionPtr(pMirrorCopyDef->GetOperationArray());
	pEdges->Clear();

	pEdges->Add(pFillet1);//���������� ���������� � ���������� ������

	pMirrorCopy->Create();

	pEdges->Clear();

	//������ �� ��������������� �����
	ksEntityPtr pCircularCopy1 = m_pPart->NewEntity(o3d_circularCopy);
	ksCircularCopyDefinitionPtr pCircularCopy1Def = pCircularCopy1->GetDefinition();

	pCircularCopy1Def->SetCopyParamAlongDir(2, 45, FALSE, FALSE);
	
	
	pEdges = ksEntityCollectionPtr(pCircularCopy1Def->GetOperationArray());

	pCircularCopy1Def->SetAxis(m_pPart->GetDefaultEntity(o3d_axisOX));

	pEdges->Add(pCutExtrusion1);
	pEdges->Add(pFillet1);
	pEdges->Add(pChamfer5);
	pEdges->Add(pMirrorCopy);
	

	pCircularCopy1->Create();

	//�������� ������ 4
	ksEntityPtr pSketch4 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch4Def = pSketch4->GetDefinition();

	pSketch4Def->SetPlane(m_pPart->GetDefaultEntity(YOX));


	m_pDoc2D = pSketch4Def->BeginEdit();
	
	m_pDoc2D->ksLineSeg(l-c1*2,D/2, l,D/2,MAIN_LINE);
	m_pDoc2D->ksLineSeg(l,D / 2,l,0,MAIN_LINE);
	m_pDoc2D->ksLineSeg(l - c1 * 2, 0, l, 0, MAIN_LINE);
	m_pDoc2D->ksLineSeg(l - c1 * 2, D/2, l - c1 * 2, 0, MAIN_LINE);
	
	m_pDoc2D->ksLineSeg(l,-D/2,l,10,HATCH_LINE);
	pSketch4Def->EndEdit();

	pSketch4->Create();

	//������������ ��������� 
	ksEntityPtr pCutRotate2 = m_pPart->NewEntity(o3d_cutRotated);
	ksCutRotatedDefinitionPtr pCutRotate2Def = pCutRotate2->GetDefinition();

	pCutRotate2Def->SetSketch(pSketch4);
	pCutRotate2Def->SetSideParam(TRUE,360);


	pCutRotate2->Create();

	//�������� ����� 6
	ksEntityPtr pChamfer6 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer6Def = pChamfer6->GetDefinition();

	pEdges = m_pPart->EntityCollection(o3d_edge);
	pChamfers = pChamfer6Def->array();
	pChamfers->Clear();

	pChamfer6Def->tangent = true;
	pChamfer6Def->SetChamferParam(true, c1, c1);

	for (int i = 0; i < pEdges->GetCount(); i++)
	{
		ksEntityPtr ed = pEdges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();

		if (def->GetOwnerEntity() == pCutRotate2)
		{
			ksVertexDefinitionPtr vert = def->GetVertex(true);
			double x, y, z;
			vert->GetPoint(&x,&y,&z);


			if (y==D/2)
			{
				pEdges->SelectByPoint(x,y,z);

				ed = pEdges->GetByIndex(0);
				pChamfers->Add(ed);

				pEdges->SelectByPoint(x+b1/2, y, z);

				ed = pEdges->GetByIndex(1);
				pChamfers->Add(ed);

			}
		}
	}
	pChamfer6->Create();

	//�������� ������ 5
	ksEntityPtr pSketch5 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch5Def = pSketch5->GetDefinition();

	pSketch5Def->SetPlane(m_pPart->GetDefaultEntity(XOY));

	m_pDoc2D = pSketch5Def->BeginEdit();

	m_pDoc2D->ksLineSeg(l-b1/2,-D/2,l + b1 / 2,-D/2,MAIN_LINE);
	m_pDoc2D->ksLineSeg(l+ b1 / 2, -D / 2,l + b1 / 2,-D1/2,MAIN_LINE);
	m_pDoc2D->ksLineSeg(l + b1 / 2, -D1 / 2, l - b1/2,-D1/2,MAIN_LINE);
	m_pDoc2D->ksLineSeg(l - b1/2, -D / 2, l-b1/2, -D1 / 2, MAIN_LINE);
	
	m_pDoc2D->ksLineSeg(0, 0, l,0, HATCH_LINE);
	pSketch5Def->EndEdit();

	pSketch5->Create();

	//������������  ��������� 3
	ksEntityPtr pCutRotate3 = m_pPart->NewEntity(o3d_cutRotated);
	ksCutRotatedDefinitionPtr pCutRotate3Def = pCutRotate3->GetDefinition();

	pCutRotate3Def->SetSketch(pSketch5);
	pCutRotate3Def->SetSideParam(TRUE, 360);

	pCutRotate3->Create();

	//�������� ��������� ����������� ������
	ksEntityPtr pThread = m_pPart->NewEntity(o3d_thread);
	ksThreadDefinitionPtr pThreadDef = pThread->GetDefinition();
	pThreadDef -> PutallLength(TRUE);
	pThreadDef -> Putlength(D);
	pThreadDef -> PutautoDefinDr(TRUE);
	
	ksEntityCollectionPtr pFaces = m_pPart ->EntityCollection(o3d_face);
	

	for (int i = 0; i < pFaces->GetCount(); i++)
	{
		ksEntityPtr face = pFaces->GetByIndex(i);
		ksFaceDefinitionPtr def = face->GetDefinition();
	
		if (def->GetOwnerEntity()==pCutRotate2)
		{
			face->Update();
			face->Putname("HoleForScrew");
			pThreadDef->SetBaseObject(face);
		}
	}
	pThread->Create();
	m_pDoc3D->SaveAs(m_collarName);
	m_pDoc3D->close();
}

void CClutchAssembler::CreateRing()
{
	
	m_pDoc3D = m_pKompasApp5->Document3D();
	m_pDoc3D->Create(false, true);
	m_pPart = m_pDoc3D->GetPart(pTop_Part);

	ksEntityPtr pSketch1 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch1Def = pSketch1->GetDefinition();

	pSketch1Def->SetPlane(m_pPart->GetDefaultEntity(XOY));

	m_pDoc2D = pSketch1Def->BeginEdit();

	
	pSketch1->Create();

	m_pDoc2D -> ksLineSeg(-b1/2,D1/2,	b1/2,D1/2,	MAIN_LINE);
	m_pDoc2D -> ksLineSeg( b1/2,D1/2,	b1/2,D/2,	MAIN_LINE);
	m_pDoc2D -> ksLineSeg(-b1/2,D/2,	b1/2,D/2,	MAIN_LINE);
	m_pDoc2D->ksLineSeg(-b1 / 2, D1 / 2, -b1 / 2, D / 2, MAIN_LINE);


	m_pDoc2D->ksLineSeg(0,0,100,0, HATCH_LINE);

	pSketch1Def->EndEdit();


	ksEntityPtr pRotate1 = m_pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotate1Def = pRotate1->GetDefinition();

	pRotate1Def->SetSketch(pSketch1);
	pRotate1Def->SetSideParam(TRUE,360);

	pRotate1->Create();

	
	m_pDoc3D->SaveAs(m_ringName);
	m_pDoc3D->close();
}


void   CClutchAssembler::CreateScrew()
{
	m_pDoc3D = m_pKompasApp5->Document3D();

	m_pDoc3D->Create(false, true);

	m_pPart = m_pDoc3D->GetPart(pTop_Part);


	ksEntityPtr pSketch1 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch1Def = pSketch1->GetDefinition();

	
	pSketch1Def->SetPlane(m_pPart->GetDefaultEntity(ZOY));
	pSketch1->Create();
	m_pDoc2D = pSketch1Def->BeginEdit();

	m_pDoc2D->ksLineSeg(0,0,0,d1/2-c1,MAIN_LINE);
	m_pDoc2D->ksLineSeg(0,d1/2-c1,D/2-d/2,d1/2-c1,MAIN_LINE);
	m_pDoc2D->ksLineSeg(D / 2 - d / 2, d1 / 2 - c1, D / 2 - d / 2,0,MAIN_LINE);
	m_pDoc2D->ksLineSeg(D / 2 - d / 2, 0,0,0,MAIN_LINE);

	m_pDoc2D->ksLineSeg(0,0,100,0,HATCH_LINE);

	pSketch1Def->EndEdit();

	ksEntityPtr pRotation1 = m_pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotation1Def = pRotation1->GetDefinition();

	pRotation1Def->SetSketch(pSketch1);
	pRotation1Def->SetSideParam(true,360);

	pRotation1->Create();


	ksEntityPtr pSketch2 = m_pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch2Def = pSketch2->GetDefinition();

	pSketch2Def->SetPlane(m_pPart->GetDefaultEntity(ZOY));
	pSketch2->Create();


	m_pDoc2D = pSketch2Def->BeginEdit();

	
	m_pDoc2D->ksLineSeg(0, b1 / 2, (D / 2) - (D1 / 2), b1 / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg( (D / 2) - (D1 / 2), b1 / 2, (D / 2) - (D1 / 2),-b1/2, MAIN_LINE);
	m_pDoc2D->ksLineSeg(0, b1 / 2, 0, -b1 / 2, MAIN_LINE);
	m_pDoc2D->ksLineSeg((D / 2) - (D1 / 2),-b1/2, 0,-b1/2,MAIN_LINE);
	pSketch2Def->EndEdit();

	ksEntityPtr pCutExtrusion = m_pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pCutExtrusionDef = pCutExtrusion->GetDefinition();

	pCutExtrusionDef->SetSketch(pSketch2);
	pCutExtrusionDef->SetSideParam(true, etThroughAll, 0, 0, false);
	pCutExtrusionDef->directionType = dtBoth;


	pCutExtrusion->Create();


	

	ksEntityPtr pChamfer1 = m_pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer1Def = pChamfer1->GetDefinition();
	
	pChamfer1Def->SetChamferParam(true,1,tan((60*3.14/180))*1);
	pChamfer1Def -> tangent = true;

	ksEntityCollectionPtr pEdges = m_pPart->EntityCollection(o3d_edge);
	ksEntityCollectionPtr pChamfers = pChamfer1Def->array();
	pChamfers->Clear();

	pEdges->SelectByPoint(d1 / 2 - c1,0, -((D / 2) - (d / 2)));



	pChamfers->Add(pEdges->GetByIndex(0));


	pChamfer1->Create();

	ksEntityPtr pThread = m_pPart->NewEntity(o3d_thread);
	ksThreadDefinitionPtr pThreadDef = pThread->GetDefinition();
	pThreadDef->PutallLength(TRUE);
	pThreadDef->Putlength((D / 2) - (d / 2));
	pThreadDef->PutautoDefinDr(TRUE);

	ksEntityCollectionPtr pFaces = m_pPart->EntityCollection(o3d_face);


	for (int i = 0; i < pFaces->GetCount(); i++)
	{
		ksEntityPtr face = pFaces->GetByIndex(i);
		ksFaceDefinitionPtr def = face->GetDefinition();

		if (def->GetOwnerEntity() == pRotation1)
		{
			
			face->Update();
			//face->Putname(SCREW_BODY);
			pThreadDef->SetBaseObject(face);
			n2 = i;
		}
		

	}
	pThread->Create();


	m_pDoc3D->SaveAs(m_screwName);
	m_pDoc3D->close();
}

void  CClutchAssembler::DoAssemble()
{
	ksPartPtr pCollar, pRing, pScrew;

	ksEntityPtr pCollarHoleForScrewEdge, pScrewEdge;
	ksEntityPtr pCollarHoleForRingEdge, pRingEdge;
	ksEntityPtr pScrewHoleForRingEdge;

	ksEntityPtr pCollarHoleForRingFace, pRingFace;

	ksEntityCollectionPtr pCollarFaces, pRingFaces, pScrewFaces;
	ksEntityCollectionPtr pCollarEdges, pRingEdges, pScrewEdges;


	m_pDoc3D = m_pKompasApp5->Document3D();

	m_pDoc3D->Create(false, false);

	m_pPart = m_pDoc3D->GetPart(pTop_Part);

	
	m_pDoc3D ->  SetPartFromFile(m_collarName, m_pPart, true);
	m_pDoc3D ->  SetPartFromFile(m_ringName, m_pPart, true);
	m_pDoc3D -> SetPartFromFile(m_screwName, m_pPart, true);

	pCollar = m_pDoc3D -> GetPart(0);
	pRing = m_pDoc3D -> GetPart(1);
	pScrew = m_pDoc3D -> GetPart(2);


	pCollarFaces = pCollar -> EntityCollection(o3d_face);
	pRingFaces = pRing -> EntityCollection(o3d_face);
	pScrewFaces = pScrew -> EntityCollection(o3d_face);

	pCollarEdges = pCollar->EntityCollection(o3d_edge);
	pRingEdges = pRing->EntityCollection(o3d_edge);
	pScrewEdges = pScrew->EntityCollection(o3d_edge);

	pCollarEdges->SelectByPoint(l - b1 / 2, 0, D1 / 2);
	pCollarHoleForRingEdge = pCollarEdges->First();

	pRingEdges->SelectByPoint(b1 / 2,0,D1/2);
	pRingEdge = pRingEdges->First();

	m_pDoc3D->AddMateConstraint(mc_Concentric, pRingEdge, pCollarHoleForRingEdge, 1, 1, 0);




	pScrewEdges->SelectByPoint(0, (d1 / 2) - c1, 0);
	pScrewEdge= pScrewEdges->First();
	pCollarEdges->Clear();

	pCollarFaces = pCollar->EntityCollection(o3d_face);
	pCollarFaces->SelectByPoint(l - c1 * 2,c1-D1 / 2, 0);
	
	

	pCollarHoleForScrewEdge = pCollarFaces->First();

	m_pDoc3D->AddMateConstraint(mc_Concentric, pScrewEdge, pCollarHoleForScrewEdge, 1, 1, 0);

	pCollarFaces->Clear();
	pCollarFaces = pCollar->EntityCollection(o3d_face);
	pRingFaces = pRing->EntityCollection(o3d_face);

	
	
	pCollarFaces->SelectByPoint(l - b1 / 2, 0, -c1+D/2);
	//pCollarFaces->SelectByPoint(0, 0, -c1 + D / 2);
	pCollarHoleForRingFace = pCollarFaces->First();

	

	pRingFaces->SelectByPoint(b1/2.f, 0.5 * (0.5 * D + D1 * 0.5), 0);
	pRingFace = pRingFaces->First();
	
	
	m_pDoc3D->AddMateConstraint(mc_Coincidence, pRingFace, pCollarHoleForRingFace, -1, 1, 0);
	
	


	pScrewEdges -> Clear();
	pScrewEdges = pScrew->EntityCollection(o3d_edge);

	pScrewEdges->SelectByPoint(0,-b1/2, -(D / 2) + (D1 / 2));
	pScrewEdge = pScrewEdges->First();

	pRingFaces->Clear();
	pRingFaces = pRing->EntityCollection(o3d_face);

	pRingFaces->SelectByPoint(0, D/2, 0);
	pRingFace = pRingFaces->First();

	m_pDoc3D->AddMateConstraint(mc_Perpendicular, pScrewEdge, pRingFace, 1, 1, 0);



	//l-c1*2,D/2
	pScrewFaces = pScrew->EntityCollection(o3d_face);
	pCollarFaces = pCollar->EntityCollection(o3d_face);
	 
	pCollarFaces->SelectByPoint(l - c1 * 2,D / 2-c,0);
	pScrewFaces->SelectByPoint(0, 0.5*d1-c1, -0.25*(D-d));

	ksEntityPtr pCollarForScrewEdge,pScrewForCollarFace;
	

	pCollarForScrewEdge = pCollarFaces->First();
	pScrewForCollarFace= pScrewFaces->First();

	m_pDoc3D->AddMateConstraint(mc_Concentric, pCollarForScrewEdge, pScrewForCollarFace, -1, -1, 0);
	//(D/2)-(D1/2)
	 
	pRingFaces = pRing->EntityCollection(o3d_face);
	pScrewFaces = pScrew->EntityCollection(o3d_face);

	pScrewFaces->SelectByPoint(0, 0, (D1 / 2) - (D / 2));
	pScrewForCollarFace = pScrewFaces->First();

	pRingFaces->SelectByPoint(0,D1/2,0);
	pRingFace = pRingFaces->First();

	m_pDoc3D->AddMateConstraint(mc_Tangency, pRingFace, pScrewForCollarFace, -1, 1, 0);

	
	//mc_Tangency - �������

	//pScrewFaces->Clear();
	//pScrewFaces = pScrew->EntityCollection(o3d_face);
	///*pScrewFaces->SelectByPoint(0,D*0.5-D1*0.5, 0);*/
	//pScrewFaces->SelectByPoint(0,1.01* b1/2, 0);
	//pScrewEdge = pScrewFaces->First();

	//pRingFaces->Clear();
	//pRingFaces = pRing->EntityCollection(o3d_face);

	//pRingFaces->SelectByPoint(0, D / 2, 0);
	//pRingFace = pRingFaces->First();
	//m_pDoc3D->AddMateConstraint(mc_Tangency,  pScrewEdge, pRingFace,1, 0, NULL);
	//	
	//

	m_pDoc3D -> RebuildDocument();

	m_pDoc3D->SaveAs(m_assembleName	);
}

Assemble CClutchAssembler::GetAssemble()
{
	return m_assemble;
}

void CClutchAssembler::SetFolderName(const char*  save)
{
	CClutchAssembler::m_saveFolder = _bstr_t(save);
}

void CClutchAssembler::SetCollarName(const char* name)
{
	CClutchAssembler::m_collarName = m_saveFolder+"\\" + _bstr_t(name);
}

void CClutchAssembler::SetRingName(const char* name)
{
	CClutchAssembler::m_ringName = m_saveFolder + "\\" + _bstr_t(name);
}

void CClutchAssembler::SetScrewName(const char* name)
{
	CClutchAssembler::m_screwName = m_saveFolder + "\\" + _bstr_t(name);
}

void CClutchAssembler::SetAssembleName(const char* name)
{
	CClutchAssembler::m_assembleName = m_saveFolder + "\\" + _bstr_t(name);
}

GOST CClutchAssembler::GetGOST()
{
	return m_gost;
}
void CClutchAssembler::UpdateGOST(GOST gost)
{
	m_gost = gost;

	d = m_assemble.GetGOST1139(gost).Getd();
	D2 = m_assemble.GetGOST1139(gost).GetD2();
	b = m_assemble.GetGOST1139(gost).Getb();


}
//Assembles::SelectedAssemble CClutchAssembler::SelectedAssemble()
//{
//	return m_selected;
//}

_bstr_t CClutchAssembler::m_saveFolder = _bstr_t("");
_bstr_t CClutchAssembler::m_collarName = _bstr_t("");
_bstr_t CClutchAssembler::m_ringName = _bstr_t("");
_bstr_t CClutchAssembler::m_screwName = _bstr_t("");
_bstr_t CClutchAssembler::m_assembleName = _bstr_t("");
GOST CClutchAssembler::m_gost;
//Assembles::SelectedAssemble CClutchAssembler::m_selected = CAssemblesCollection::CLT_140NM;