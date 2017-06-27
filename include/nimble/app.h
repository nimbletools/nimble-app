#pragma once

#include "common.h"
#include "widget.h"

class GLFWwindow;
struct lay_context;
struct NVGcontext;

namespace na
{
	class Application
	{
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

		int m_width = 1024;
		int m_height = 768;

	public:
		Application();
		virtual ~Application();

		virtual void Run();
		virtual void DoLayout();
		virtual void Draw();
		virtual void Frame();

		virtual void InvalidateLayout();
		virtual void InvalidateRendering();

		virtual bool IsInvalidated();

	protected:
		virtual void InitializeLayout();
		virtual void InitializeRendering();
		virtual void InitializeWindow();

		virtual void CleanupLayout();
		virtual void CleanupRendering();
	};
}
