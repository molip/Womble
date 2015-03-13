#include "stdafx.h"
#include "ChildView.h"
#include "View.h"

#define _OLD_MSC_VER _MSC_VER
#undef _MSC_VER
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#define _MSC_VER _OLD_MSC_VER 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
//	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CChildView* CChildView::s_instance;

CChildView::CChildView()
{
	s_instance = this;
}

CChildView::~CChildView()
{
	s_instance = nullptr;
}

void CChildView::Pump()
{
	sf::Event event;
	if (m_window)
		while (m_window->pollEvent(event));
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	auto sz = m_window->getSize();
	glViewport(0, 0, sz.x, sz.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, sz.x / (double)sz.y, 1, 1000);

	double aspect = sz.x / (double)sz.y;
	glOrtho(-2 * aspect, 2 * aspect, -2, 2, -1000, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_view->Draw(*m_window);

	m_window->display();
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	CWnd::OnTimer(nIDEvent);

	float tDelta = m_clock->restart().asSeconds();
	m_view->Update(tDelta);
	Invalidate();
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (cx && cy && !m_window)
	{
		m_window = std::make_unique<sf::RenderWindow>(GetSafeHwnd());
		m_clock = std::make_unique<sf::Clock>();
		m_view = std::make_unique<View>();
		SetTimer(1, 1000 / 30, nullptr);
	}

	//if (m_window)
	//{
	//	sf::Event event;
	//	event.type = sf::Event::Resized;
	//	event.size.width = cx;
	//	event.size.height = cy;
	//	m_window->fi
	//}
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}
