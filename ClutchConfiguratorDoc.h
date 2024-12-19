
// ClutchConfiguratorDoc.h: интерфейс класса CClutchConfiguratorDoc 
//


#pragma once
class CAssembleTree;
class CClutchConfiguratorView;
class CMainFrame;
namespace selected
{
	enum SelectedAssemble {
		first = 0,
	};
}
class CClutchConfiguratorDoc : public CDocument
{
protected: // создать только из сериализации
	CClutchConfiguratorDoc() noexcept;
	DECLARE_DYNCREATE(CClutchConfiguratorDoc)

// Атрибуты
public:
	
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	
	virtual ~CClutchConfiguratorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	selected::SelectedAssemble m_selectedAssemble = selected::first;
	CAssembleTree* m_pAssembleTree;
	CClutchConfiguratorView* m_pClutchConfigView;

	friend class CMainFrame;
	friend class CClutchConfiguratorView;
// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
