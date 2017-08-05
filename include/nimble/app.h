#pragma once

#include "common.h"
#include "widget.h"
#include "contentmanager.h"
#include "utils/localization.h"
#include "widgets/page.h"

struct GLFWwindow;
struct lay_context;
struct NVGcontext;

namespace na
{
	class Application
	{
	friend class Widget;
	friend class ContentManager;

	protected:
		lay_context* m_layout = nullptr;
		GLFWwindow* m_window = nullptr;
		NVGcontext* m_nvg = nullptr;

		bool m_initializedLayout = false;
		bool m_initializedRendering = false;
		bool m_initializedWindow = false;

		s2::list<PageWidget*> m_pages;
		s2::list<PageAction> m_pageQueue;

		bool m_invalidatedLayout = true;
		bool m_invalidatedRendering = true;

		glm::ivec2 m_windowSize;
		glm::ivec2 m_bufferSize;

		glm::ivec2 m_lastCursorPos = glm::ivec2(-1, -1);
		s2::list<Widget*> m_hoveringWidgets;
		Widget* m_focusWidget = nullptr;

	public:
		ContentManager Content;
		s2::dict<s2::string, WidgetFactory> WidgetFactories;

	public:
		Application();
		virtual ~Application();

		virtual void Run();
		virtual void DoLayout();
		virtual void Draw();
		virtual void Frame();

		virtual void OnLoad();

		virtual void SetWindowSize(const glm::ivec2 &size);
		virtual float GetPixelScale();

		virtual void HandlePageQueue();
		virtual void PushPage(PageWidget* page);
		virtual void PopPage();

		virtual bool IsInvalidated();
		virtual void InvalidateLayout();
		virtual void InvalidateRendering();

		virtual void HandleHoverWidgets(Widget* w, const glm::ivec2 &point);
		virtual void InvalidateInputWidgets();

		inline Widget* GetFocusWidget() { return m_focusWidget; }
		virtual void SetFocusWidget(Widget* w);

		virtual void CallbackCursorPosition(const glm::ivec2 &point);
		virtual void CallbackMouseButton(int button, int action, int mods);
		virtual void CallbackWindowResized(int width, int height);
		virtual void CallbackFramebufferResized(int width, int height);
		virtual void CallbackKey(int key, int scancode, int action, int mods);
		virtual void CallbackCharMods(unsigned int ch, int mods);

		inline NVGcontext* GetNVG() { return m_nvg; } //TODO: Get rid of this function

	protected:
		virtual void InitializeLayout();
		virtual void InitializeRendering();
		virtual void InitializeWindow();

		virtual void CleanupLayout();
		virtual void CleanupRendering();
	};
}
