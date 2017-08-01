#pragma once

#include "common.h"
#include "widget.h"
#include "contentmanager.h"
#include "managed/managedcode.h"

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

		Widget* m_root = nullptr;

		bool m_invalidatedLayout = true;
		bool m_invalidatedRendering = true;

		glm::ivec2 m_windowSize;
		glm::ivec2 m_bufferSize;

		s2::list<Widget*> m_hoveringWidgets;

	public:
		ContentManager Content;
		s2::dict<s2::string, WidgetFactory> WidgetFactories;

		ManagedCode ManagedCode;

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

		virtual void Selector(const s2::string &query, s2::list<Widget*> &out);

		virtual void SetRoot(Widget* root);
		virtual void LoadLayout(const s2::string &filename);
		virtual void LoadStyle(const s2::string &filename);

		virtual bool IsInvalidated();
		virtual void InvalidateLayout();
		virtual void InvalidateRendering();

		virtual void HandleHoverWidgets(Widget* w, const glm::ivec2 &point);
		virtual void CallbackCursorPosition(const glm::ivec2 &point);
		virtual void CallbackMouseButton(int button, int action, int mods);
		virtual void CallbackWindowResized(int width, int height);
		virtual void CallbackFramebufferResized(int width, int height);

		inline NVGcontext* GetNVG() { return m_nvg; } //TODO: Get rid of this function

	protected:
		virtual void InitializeLayout();
		virtual void InitializeRendering();
		virtual void InitializeWindow();

		virtual void CleanupLayout();
		virtual void CleanupRendering();
	};
}
