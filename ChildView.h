#pragma once

#include <memory>

namespace sf
{
	class RenderWindow;
	class Clock;
}

class View;

class CChildView : public CWnd
{
public:
	CChildView();
	virtual ~CChildView();

	void Pump();
	static CChildView* s_instance;

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

private:
	std::unique_ptr<sf::RenderWindow> m_window;
	std::unique_ptr<sf::Clock> m_clock;
	std::unique_ptr<View> m_view;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};

